import ast
from pathlib import Path

import pytest

REPO = Path(__file__).resolve().parents[3]
SOURCE = REPO / 'openpilot'
MOVED_PACKAGES = ('cereal', 'common', 'selfdrive', 'system', 'starpilot')
COMPILED_SUFFIXES = ('.py', '.pyx', '.so', '.pxd')
PROCESS_CONFIG = SOURCE / 'system' / 'manager' / 'process_config.py'
PYTHON_PROCESS_CLASSES = ('PythonProcess', 'DaemonProcess', 'ModeldProcess', 'JetlinkProcess')


def _registered_modules() -> list[tuple[str, str]]:
  tree = ast.parse(PROCESS_CONFIG.read_text(encoding='utf-8'))
  found: list[tuple[str, str]] = []
  for node in ast.walk(tree):
    if isinstance(node, ast.Call) and isinstance(node.func, ast.Name) and node.func.id in PYTHON_PROCESS_CLASSES:
      name, module = node.args[0], node.args[1]
      if not (isinstance(name, ast.Constant) and isinstance(module, ast.Constant)):
        raise AssertionError(f'process_config.py:{node.lineno} is not a literal registration')
      if not (isinstance(name.value, str) and isinstance(module.value, str)):
        raise AssertionError(f'process_config.py:{node.lineno} is not a string registration')
      found.append((name.value, module.value))
  return found


def _module_exists(dotted: str) -> bool:
  target = REPO.joinpath(*dotted.split('.'))
  if target.is_dir():
    return True
  return any(target.with_suffix(suffix).exists() for suffix in COMPILED_SUFFIXES) or bool(list(target.parent.glob(f'{target.name}.*.so')))


def _catches_import_error(node: ast.Try) -> bool:
  names = {'ImportError', 'ModuleNotFoundError', 'Exception', 'BaseException'}
  for handler in node.handlers:
    if handler.type is None:
      return True
    caught = handler.type.elts if isinstance(handler.type, ast.Tuple) else [handler.type]
    if any(isinstance(c, ast.Name) and c.id in names for c in caught):
      return True
  return False


def _absolute_imports(path: Path):
  tree = ast.parse(path.read_text(encoding='utf-8'), filename=str(path))
  optional: set[int] = set()
  for node in ast.walk(tree):
    if isinstance(node, ast.Try) and _catches_import_error(node):
      optional.update(id(child) for stmt in node.body for child in ast.walk(stmt))
  for node in ast.walk(tree):
    if id(node) in optional:
      continue
    if isinstance(node, ast.Import):
      for alias in node.names:
        yield node.lineno, alias.name
    elif isinstance(node, ast.ImportFrom) and node.level == 0 and node.module:
      yield node.lineno, node.module


def _python_files():
  return sorted(p for p in SOURCE.rglob('*.py') if '__pycache__' not in p.parts and 'vendor' not in p.parts)


def _scan():
  legacy, unresolved = [], []
  for path in _python_files():
    try:
      imports = list(_absolute_imports(path))
    except SyntaxError as e:
      unresolved.append(f'{path.relative_to(REPO)}: syntax error {e}')
      continue
    for lineno, module in imports:
      top = module.split('.')[0]
      where = f'{path.relative_to(REPO)}:{lineno}'
      if top in MOVED_PACKAGES:
        legacy.append(f'{where} imports {module} (use openpilot.{module})')
      elif top == 'openpilot' and not _module_exists(module):
        unresolved.append(f'{where} imports missing module {module}')
  return legacy, unresolved


@pytest.fixture(scope='module')
def scan():
  return _scan()


def test_no_pre_nesting_import_names(scan):
  legacy, _ = scan
  assert not legacy, 'imports still use the layout from before the move into openpilot/:\n' + '\n'.join(legacy)


def test_every_openpilot_import_resolves(scan):
  _, unresolved = scan
  assert not unresolved, 'openpilot imports that do not resolve to a file:\n' + '\n'.join(unresolved)


def test_process_registrations_are_found():
  assert len(_registered_modules()) >= 50


@pytest.mark.parametrize('name,module', _registered_modules(), ids=lambda v: str(v))
def test_managed_process_module_exists(name, module):
  assert module.split('.')[0] == 'openpilot', f'{name} registered with pre-nesting name {module}'
  assert _module_exists(module), f'{name} registered module {module} has no file'
