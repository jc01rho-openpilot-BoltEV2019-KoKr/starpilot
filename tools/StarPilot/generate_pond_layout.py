import os
import re
import sys
import json
import ast

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../'))

CATEGORIES = [
    {"file": "lateral_settings.cc", "name": "Lateral (Steering)", "icon": "bi-arrows-move"},
    {"file": "longitudinal_settings.cc", "name": "Longitudinal (Speed & Following)", "icon": "bi-speedometer2"},
    {"file": "visual_settings.cc", "name": "Visual (Display & UI)", "icon": "bi-eye"},
    {"file": "sounds_settings.cc", "name": "Sounds & Alerts", "icon": "bi-volume-up"},
    {"file": "vehicle_settings.cc", "name": "Vehicle", "icon": "bi-car-front"},
    {"file": "device_settings.cc", "name": "Device & Data", "icon": "bi-hdd"},
    {"file": "model_settings.cc", "name": "Model & Customization", "icon": "bi-cpu"},
]

DROPDOWN_MAPPING = {
    "SelectModel": {
        "key": "Model",
        "options_endpoint": "/api/models/installed"
    }
}

PARENT_KEYS_MAPPING = {
    "device_settings.cc": {
        "deviceManagementKeys": "DeviceManagement",
        "screenKeys": "ScreenManagement"
    },
    "lateral_settings.cc": {
        "advancedLateralTuneKeys": "AdvancedLateralTune",
        "aolKeys": "AlwaysOnLateral",
        "laneChangeKeys": "LaneChanges",
        "lateralTuneKeys": "LateralTune",
        "qolKeys": "QOLLateral"
    },
    "longitudinal_settings.cc": {
        "advancedLongitudinalTuneKeys": "AdvancedLongitudinalTune",
        "aggressivePersonalityKeys": "AggressivePersonalityProfile",
        "conditionalExperimentalKeys": "ConditionalExperimental",
        "curveSpeedKeys": "CurveSpeedControl",
        "customDrivingPersonalityKeys": "CustomDrivingPersonality",
        "longitudinalTuneKeys": "LongitudinalTune",
        "qolKeys": "QOLLongitudinal",
        "relaxedPersonalityKeys": "RelaxedPersonalityProfile",
        "speedLimitControllerKeys": "SpeedLimitController",
        "standardPersonalityKeys": "StandardPersonalityProfile",
        "trafficPersonalityKeys": "TrafficPersonalityProfile"
    },
    "sounds_settings.cc": {
        "alertVolumeControlKeys": "AlertVolumeControl",
        "customAlertsKeys": "CustomAlerts"
    },
    "theme_settings.cc": {
        "customThemeKeys": "CustomTheme"
    },
    "visual_settings.cc": {
        "advancedCustomOnroadUIKeys": "AdvancedCustomUI",
        "customOnroadUIKeys": "CustomUI",
        "developerMetricKeys": "DeveloperMetrics",
        "developerSidebarKeys": "DeveloperSidebar",
        "developerUIKeys": "DeveloperUI",
        "developerWidgetKeys": "DeveloperWidgets",
        "modelUIKeys": "ModelUI",
        "navigationUIKeys": "NavigationUI",
        "qualityOfLifeKeys": "QOLVisuals"
    },
    "vehicle_settings.cc": {}
}

ALL_PARENT_KEYS = set()
for cmap in PARENT_KEYS_MAPPING.values():
    for parent in cmap.values():
        ALL_PARENT_KEYS.add(parent)

def get_variables_data():
    filepath = os.path.join(REPO_ROOT, "frogpilot/common/frogpilot_variables.py")
    excluded = set()
    defaults = {}
    if not os.path.exists(filepath):
        return excluded, defaults

    with open(filepath, 'r', encoding='utf-8') as f:
        tree = ast.parse(f.read())

    def parse_params_list(value_node):
        try:
            if isinstance(value_node, ast.List):
                for elt in value_node.elts:
                    if isinstance(elt, ast.Tuple) and len(elt.elts) >= 2:
                        key_node = elt.elts[0]
                        val_node = elt.elts[1]
                        if isinstance(key_node, ast.Constant):
                            key = key_node.value
                            if isinstance(val_node, ast.Constant):
                                val = val_node.value
                                if isinstance(val, (str, bytes)):
                                    v = val.decode('utf-8') if isinstance(val, bytes) else str(val)
                                    if v in ("0", "1"):
                                        defaults[key] = "bool"
                                    elif "." in v and v.replace(".", "", 1).isdigit():
                                        defaults[key] = "float"
                                    elif v.isdigit():
                                        defaults[key] = "int"
                                    else:
                                        defaults[key] = "string"
                                else:
                                    defaults[key] = "unknown"
                            else:
                                defaults[key] = "unknown"
        except:
            pass

    for node in tree.body:
        if isinstance(node, ast.Assign):
            for target in node.targets:
                if getattr(target, 'id', '') == 'EXCLUDED_KEYS':
                    try:
                        excluded = ast.literal_eval(node.value)
                    except:
                        pass
                elif getattr(target, 'id', '') == 'frogpilot_default_params':
                    parse_params_list(node.value)
        elif isinstance(node, ast.AnnAssign):
            if getattr(node.target, 'id', '') == 'frogpilot_default_params':
                parse_params_list(node.value)

    return excluded, defaults

EXCLUDED_KEYS, DEFAULT_TYPES = get_variables_data()

def get_param_type(key):
    return DEFAULT_TYPES.get(key, "unknown")

def extract_bracket_block(text, start_idx):
    if text[start_idx] != '{': return ""
    depth = 0
    in_str = False
    escape = False
    for i in range(start_idx, len(text)):
        char = text[i]
        if escape:
            escape = False
            continue
        if char == '\\':
            escape = True
            continue
        if char == '"':
            in_str = not in_str
            continue
        if not in_str:
            if char == '{': depth += 1
            elif char == '}':
                depth -= 1
                if depth == 0:
                    return text[start_idx:i+1]
    return ""

def parse_cpp_file(filename):
    filepath = os.path.join(REPO_ROOT, "frogpilot/ui/qt/offroad", filename)
    if not os.path.exists(filepath): return []

    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    vector_match = re.search(r'const std::vector<std::tuple<QString,\s*QString,\s*QString,\s*QString>> \w+\s*\{', content)
    if not vector_match: return []

    start_idx = vector_match.end() - 1
    vector_content = extract_bracket_block(content, start_idx)

    local_parent_map = PARENT_KEYS_MAPPING.get(filename, {})
    child_to_parent = {}

    header_filename = filename.replace(".cc", ".h")
    header_filepath = os.path.join(REPO_ROOT, "frogpilot/ui/qt/offroad", header_filename)
    full_source = content
    if os.path.exists(header_filepath):
        with open(header_filepath, 'r', encoding='utf-8') as fh:
            full_source += "\n" + fh.read()

    for qset_match in re.finditer(r'QSet<QString>\s+(\w+)\s*(?:=\s*)?\{([^}]+)\};', full_source):
        qset_name = qset_match.group(1)
        if qset_name in local_parent_map:
            parent_key = local_parent_map[qset_name]
            children_str = qset_match.group(2)
            children = [c.strip().strip('"') for c in children_str.split(',') if c.strip()]
            for child in children:
                child_to_parent[child] = parent_key

    items = []

    idx = 0
    while True:
        idx = vector_content.find('{"', idx)
        if idx == -1: break

        block = extract_bracket_block(vector_content, idx)
        if not block:
            idx += 1
            continue

        row_match = re.search(r'\{"([A-Za-z0-9_]+)"\s*,\s*(.*?)\s*\}$', block, re.DOTALL)
        if not row_match:
            idx += len(block)
            continue

        key = row_match.group(1)
        rest = row_match.group(2)
        idx += len(block)

        if key in EXCLUDED_KEYS or key.startswith("IgnoreMe"):
            continue

        strings = re.findall(r'tr\("((?:[^"\\]|\\.)+)"\)|"((?:[^"\\]|\\.)+)"', rest)
        valid_strings = [s[0] or s[1] for s in strings if s[0] or s[1]]

        if not valid_strings: continue

        title = valid_strings[0]
        desc = valid_strings[1] if len(valid_strings) > 1 else ""
        options_endpoint = None

        if key in DROPDOWN_MAPPING:
            m = DROPDOWN_MAPPING[key]
            key = m["key"]
            widget_type = "dropdown"
            options_endpoint = m["options_endpoint"]
            data_type = "string"
        else:
            data_type = get_param_type(key)
            if data_type == "unknown": continue
            widget_type = "toggle"
            min_val, max_val, step = None, None, None

        for i in range(1, 10):
            placeholder = f"%{i}"
            if placeholder in desc and len(valid_strings) > i + 1:
                desc = desc.replace(placeholder, valid_strings[i + 1])

        desc = re.sub(r'<br\s*/?>', '\n', desc, flags=re.IGNORECASE)
        desc = re.sub(r'<[^>]+>', '', desc)
        desc = desc.replace('\\"', '"').strip()
        title = re.sub(r'\s*\(\s*Default:\s*%\d\s*\)', '', title)
        title = re.sub(r'%\d', '', title).strip()
        desc = re.sub(r'\s*\(\s*Default:\s*%\d\s*\)', '', desc)
        desc = re.sub(r'%\d', '', desc).strip()

        if widget_type == "toggle":
            snippet_match = None
            qset_name = ""
            if key in child_to_parent:
                parent_k = child_to_parent[key]
                for q, pk in local_parent_map.items():
                    if pk == parent_k:
                        qset_name = q
                        break

            # Let's match the original's regex for finding the Toggle = assignment line
            search_patterns = [r'param\s*==\s*"' + key + r'"']
            if qset_name:
                search_patterns.append(r'(?:' + qset_name + r'\.contains\(param\))')

            for pattern in search_patterns:
                match = re.search(pattern + r'.*?[a-zA-Z]+Toggle\s*=\s*(.*?);', content, re.DOTALL)
                if match:
                    snippet_match = match
                    break

            if snippet_match:
                assignment = snippet_match.group(1)
                if "FrogPilotParamValueControl" in assignment or "FrogPilotParamValueButtonControl" in assignment:
                    widget_type = "numeric"
                    if data_type in ("string", "bool", "unknown"):
                        data_type = "float"

                    if qset_name == "alertVolumeControlKeys":
                        if key in ["WarningImmediateVolume", "WarningSoftVolume"]:
                            min_val, max_val, step = "25", "101", "1"
                        else:
                            min_val, max_val, step = "0", "101", "1"
                    else:
                        args_match = re.search(r'Control[^(]*\(([^;]+)\)', assignment)
                        if args_match:
                            args_str = args_match.group(1)
                            num_match = re.search(r'icon\s*,\s*([-\d.]+)\s*,\s*([-\d.]+)\s*,(?:[^,]*,){2}\s*([-\d.]+)', args_str)
                            if num_match:
                                min_val, max_val, step = num_match.group(1), num_match.group(2), num_match.group(3)
                            else:
                                num_match = re.search(r'icon\s*,\s*([-\d.]+)\s*,\s*([-\d.]+)', args_str)
                                if num_match:
                                    min_val, max_val = num_match.group(1), num_match.group(2)
                            step_match = re.search(r'(?:std::map<float,\s*QString>\(\)|[a-zA-Z0-9_]+Labels)\s*,\s*([-\d.]+)', args_str)
                            if step_match:
                                step = step_match.group(1)

        precision = None
        precision_match = re.search(r"QString::number\([^,]+,\s*'f'\s*,\s*(\d+)\)", rest)
        if precision_match:
            precision = int(precision_match.group(1))

        if data_type == "float" and step and float(step).is_integer():
             data_type = "int"

        s = {
            "key": key,
            "label": title,
            "description": desc,
            "data_type": data_type,
            "ui_type": widget_type
        }
        if widget_type == "numeric":
            if min_val is not None: s["min"] = float(min_val)
            if max_val is not None: s["max"] = float(max_val)
            if step is not None: s["step"] = float(step)
            if precision is not None: s["precision"] = precision
        elif widget_type == "dropdown":
            if options_endpoint: s["options_endpoint"] = options_endpoint
        if key in child_to_parent: s["parent_key"] = child_to_parent[key]
        if key in ALL_PARENT_KEYS: s["is_parent_toggle"] = True

        items.append(s)

    return items

def main():
    layout = []
    for cat in CATEGORIES:
        items = parse_cpp_file(cat["file"])
        if items:
            layout.append({
                "name": cat["name"],
                "icon": cat["icon"],
                "params": items
            })
    output_path = os.path.join(REPO_ROOT, "frogpilot/system/the_pond/assets/components/tools/device_settings_layout.json")
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(layout, f, indent=2)

if __name__ == '__main__':
    main()
