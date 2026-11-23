import ast
from pathlib import Path

import pytest

from openpilot.cereal import custom, log
from openpilot.cereal.services import SERVICE_LIST

REPO = Path(__file__).resolve().parents[3]
SOURCE = REPO / 'openpilot'
SCHEMAS = {'log': log, 'custom': custom}
EVENT_FIELDS = set(log.Event.schema.fields)
RECORDER_ONLY_SERVICES = {'modelIdentity': 'logMessage'}


def _python_files():
  return sorted(p for p in SOURCE.rglob('*.py') if '__pycache__' not in p.parts and 'vendor' not in p.parts)


def _imports_schema(tree: ast.AST) -> dict[str, str]:
  names = {}
  for node in ast.walk(tree):
    if isinstance(node, ast.ImportFrom) and node.module == 'openpilot.cereal':
      names.update({alias.asname or alias.name: alias.name for alias in node.names if alias.name in SCHEMAS})
  return names


def _rebound_names(tree: ast.AST) -> set[str]:
  names = {n.id for n in ast.walk(tree) if isinstance(n, ast.Name) and isinstance(n.ctx, ast.Store)}
  names.update(a.arg for n in ast.walk(tree) if isinstance(n, ast.arguments) for a in n.args + n.kwonlyargs + n.posonlyargs)
  return names


def _literal_strings(node: ast.AST) -> list[str]:
  if isinstance(node, (ast.List, ast.Tuple)):
    return [e.value for e in node.elts if isinstance(e, ast.Constant) and isinstance(e.value, str)]
  return []


def _scan():
  unknown_types, unknown_events, unknown_services = [], [], []
  for path in _python_files():
    tree = ast.parse(path.read_text(encoding='utf-8'), filename=str(path))
    rebound = _rebound_names(tree)
    schema_names = {alias: name for alias, name in _imports_schema(tree).items() if alias not in rebound}
    for node in ast.walk(tree):
      where = f'{path.relative_to(REPO)}:{getattr(node, "lineno", 0)}'
      if isinstance(node, ast.Attribute) and isinstance(node.value, ast.Name) and node.value.id in schema_names:
        if not hasattr(SCHEMAS[schema_names[node.value.id]], node.attr):
          unknown_types.append(f'{where} {node.value.id}.{node.attr} is not in the capnp schema')
      elif isinstance(node, ast.Call) and isinstance(node.func, ast.Attribute):
        if node.func.attr == 'new_message' and isinstance(node.func.value, ast.Name) and node.func.value.id == 'messaging':
          if node.args and isinstance(node.args[0], ast.Constant) and isinstance(node.args[0].value, str):
            if node.args[0].value not in EVENT_FIELDS and node.args[0].value not in RECORDER_ONLY_SERVICES:
              unknown_events.append(f'{where} messaging.new_message({node.args[0].value!r}) has no Event field')
      if isinstance(node, ast.Call):
        callee = node.func.attr if isinstance(node.func, ast.Attribute) else getattr(node.func, 'id', '')
        if callee in ('SubMaster', 'PubMaster') and node.args:
          for service in _literal_strings(node.args[0]):
            if service not in SERVICE_LIST:
              unknown_services.append(f'{where} {callee} uses unknown service {service!r}')
  return unknown_types, unknown_events, unknown_services


@pytest.fixture(scope='module')
def scan():
  return _scan()


def test_schemas_expose_expected_roots():
  assert hasattr(log, 'Event') and hasattr(custom, 'StarPilotCarState')
  assert EVENT_FIELDS


@pytest.mark.parametrize('service', sorted(SERVICE_LIST))
def test_service_has_event_field(service):
  carrier = RECORDER_ONLY_SERVICES.get(service, service)
  assert carrier in EVENT_FIELDS, f'service {service} in services.py has no Event field {carrier} in log.capnp'


def test_recorder_only_services_are_still_registered():
  assert set(RECORDER_ONLY_SERVICES) <= set(SERVICE_LIST)


def test_event_union_ordinals_are_unique():
  ordinals = [field.proto.ordinal.explicit for field in log.Event.schema.fields.values() if field.proto.which() == 'slot']
  assert len(ordinals) == len(set(ordinals))


def test_python_references_exist_in_schema(scan):
  unknown_types, _, _ = scan
  assert not unknown_types, 'code uses capnp types that do not exist:\n' + '\n'.join(unknown_types)


def test_new_message_targets_are_event_fields(scan):
  _, unknown_events, _ = scan
  assert not unknown_events, '\n'.join(unknown_events)


def test_pubsub_services_are_registered(scan):
  _, _, unknown_services = scan
  assert not unknown_services, '\n'.join(unknown_services)
