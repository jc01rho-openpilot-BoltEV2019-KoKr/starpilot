import ast
from pathlib import Path

MPC_SCONSCRIPT_PATHS = (
  Path("selfdrive/controls/lib/lateral_mpc_lib/SConscript"),
  Path("selfdrive/controls/lib/longitudinal_mpc_lib/SConscript"),
)


def test_acados_pxd_template_is_generation_dependency():
  # Given: an MPC SConscript that generates acados_solver.pxd.
  for sconscript_path in MPC_SCONSCRIPT_PATHS:
    module = ast.parse(sconscript_path.read_text())
    source_list = next(
      node.value
      for node in module.body
      if isinstance(node, ast.Assign)
      and any(isinstance(target, ast.Name) and target.id == "source_list" for target in node.targets)
    )
    assert isinstance(source_list, ast.List)

    # When: its generation inputs are inspected.
    dependencies = {
      part.value
      for element in source_list.elts
      if isinstance(element, ast.JoinedStr)
      for part in element.values
      if isinstance(part, ast.Constant) and isinstance(part.value, str)
    }

    # Then: changes to the pxd template must invalidate generated acados_solver.pxd.
    assert "/acados_solver.in.pxd" in dependencies, sconscript_path
