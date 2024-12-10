import os
import re
import sys
from pathlib import Path

def process_files(folder_path):
    """
    Process .h and .hpp files to gather class names with the ACLASS() macro
    and their corresponding file names.
    """
    macro_pattern = re.compile(r"^\s*ACLASS\(\s*\)\s*$")  # Matches 'ACLASS()' on a line
    class_pattern = re.compile(r"^\s*class\s+(\w+)\s*")   # Matches 'class ClassName'
    
    class_file_map = {}

    for file_name in os.listdir(folder_path):
        if file_name.endswith('.h') or file_name.endswith('.hpp'):
            file_path = os.path.join(folder_path, file_name)

            with open(file_path, 'r') as file:
                content = file.readlines()  # Read file line by line for easier processing

            for i, line in enumerate(content):
                if macro_pattern.match(line.strip()):  # If the macro is found
                    for next_line in content[i + 1:]:  # Look for the next class declaration
                        next_line = next_line.strip()
                        if next_line:
                            match = class_pattern.match(next_line)
                            if match:  # If a class definition is found
                                class_name = match.group(1)
                                class_file_map[class_name] = file_name  # Map the class to the file
                            break
    return class_file_map

def generate_init_file(classes, output_path):
    """Generate a file like Init.txt based on gathered classes."""

    output_dir = os.path.dirname(output_path)
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    with open(output_path, 'w') as file:
        # Write the fixed header
        file.write("// IMPORTANT: This File should be generated at build time and not edited by hand\n\n")
        file.write('#include "Init.h"\n\n')
        for file_name in classes:
            file.write(f'#include "Scripts/{file_name}_generated.h"\n')
        file.write('\n#include <Core/AloeEngine.h>\n')
        file.write('#include <Core/Script.h>\n\n')
        file.write('#include <string>\n\n')

        file.write("namespace Aloe\n{\n")
        file.write("    typedef Script* (*AddComponentFn)(Entity entity);\n")
        file.write("    typedef void (*DrawInterfaceFn)(Entity entity);\n")
        file.write("    typedef bool (*HasComponentFn)(Entity entity);\n\n")

        # Generate s_addComponentFnMap
        file.write("    std::unordered_map<std::string, AddComponentFn> s_addComponentFnMap =\n    {\n")
        for cls in classes:
            file.write(f'        {{ "{cls}", Reflect{cls}::AddComponent }},\n')
        file.write("    };\n\n")

        # Generate s_drawInterfaceFnMap
        file.write("    std::unordered_map<std::string, DrawInterfaceFn> s_drawInterfaceFnMap =\n    {\n")
        for cls in classes:
            file.write(f'        {{ "{cls}", Reflect{cls}::DrawInterface }},\n')
        file.write("    };\n\n")

        # Generate s_hasComponentFnMap
        file.write("    std::unordered_map<std::string, HasComponentFn> s_hasComponentFnMap =\n    {\n")
        for cls in classes:
            file.write(f'        {{ "{cls}", Reflect{cls}::HasComponent }},\n')
        file.write("    };\n\n")

        # Generate s_scriptsList
        file.write("    std::vector<std::string> s_scriptsList =\n    {\n")
        for cls in classes:
            file.write(f'        "{cls}",\n')
        file.write("    };\n\n")

        # Write the remaining fixed content
        file.write("    void Initialize()\n    {\n")
        for cls in classes:
            file.write(f"        Reflect{cls}::Initialize();\n")
        file.write("    }\n\n")

        file.write("    void GetScriptList(std::vector<std::string>* out)\n    {\n")
        file.write("        *out = s_scriptsList;\n")
        file.write("    }\n\n")

        file.write("    void InitImGuiContext(void* context)\n    {\n")
        file.write("        ImGui::SetCurrentContext((ImGuiContext*)context);\n")
        file.write("    }\n\n")

        file.write("    void DrawInterfaceFromString(std::string scriptName, Entity entity)\n    {\n")
        file.write("        if (s_drawInterfaceFnMap.find(scriptName) == s_drawInterfaceFnMap.end())\n        {\n")
        file.write('            printf("\\n Script Module Error (DrawInterface = %s): Component doesn\'t exist", scriptName.c_str());\n')
        file.write("        }\n")
        file.write("        return s_drawInterfaceFnMap[scriptName](entity);\n")
        file.write("    }\n\n")

        file.write("    Script* AddComponentFromString(std::string scriptName, Entity entity)\n    {\n")
        file.write("        if (s_addComponentFnMap.find(scriptName) == s_addComponentFnMap.end())\n        {\n")
        file.write('            printf("\\n Script Module Error (AddComponent = %s): Component doesn\'t exist", scriptName.c_str());\n')
        file.write("        }\n")
        file.write("        return s_addComponentFnMap[scriptName](entity);\n")
        file.write("    }\n\n")

        file.write("    bool HasComponentFromString(std::string scriptName, Entity entity)\n    {\n")
        file.write("        if (s_hasComponentFnMap.find(scriptName) == s_hasComponentFnMap.end())\n        {\n")
        file.write('            printf("\\n Script Module Error (HasComponent = %s): Component doesn\'t exist", scriptName.c_str());\n')
        file.write("        }\n")
        file.write("        return s_hasComponentFnMap[scriptName](entity);\n")
        file.write("    }\n")
        file.write("}\n")


def process_aparam_variables(folder_path, out_classes_params):
    """Process .h and .hpp files to gather variables marked with APARAM()."""
    class_pattern = re.compile(r"^\s*class\s+(\w+)\s*")  # Matches 'class ClassName'
    aparam_pattern = re.compile(r"^\s*APARAM\(\)\s*;?")  # Matches 'APARAM()'
    variable_pattern = re.compile(r"^\s*(\w+)\s+(\w+)\s*(=.*)?;")  # Matches 'type variable;' or 'type variable = value;'

    current_class = None

    for file_name in os.listdir(folder_path):
        if file_name.endswith('.h') or file_name.endswith('.hpp'):
            file_path = os.path.join(folder_path, file_name)

            with open(file_path, 'r') as file:
                content = file.readlines()

            for i, line in enumerate(content):
                class_match = class_pattern.match(line.strip())
                if class_match:
                    current_class = class_match.group(1)
                    out_classes_params[current_class] = []
                elif current_class and aparam_pattern.match(line.strip()):  # Found APARAM()
                    # Check the next non-empty line for a variable definition
                    for next_line in content[i + 1:]:
                        next_line = next_line.strip()
                        if next_line:  # Skip empty lines
                            variable_match = variable_pattern.match(next_line)
                            if variable_match:
                                var_type, var_name = variable_match.groups()[:2]  # Only take type and name
                                out_classes_params[current_class].append((var_type, var_name))
                            break

def generate_script_files(classes_params, class_file_map, output_dir):
    """
    Generate individual script files for each class based on their variables.

    Args:
        classes_params (dict): A dictionary where keys are class names and values are lists of (type, variable) tuples.
        class_file_map (dict): A mapping of class names to the files they are defined in.
        output_dir (str): The directory to save the generated files.
    """
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for cls, params in classes_params.items():
        # Get the original file for the class
        original_file = class_file_map.get(cls, None)
        if not original_file:
            print(f"Warning: No file found for class {cls}. Skipping.")
            continue

        # Define the file name for the generated header
        file_path = os.path.join(output_dir, f"{cls}_generated.h")

        with open(file_path, 'w') as file:
            file.write("// TODO: This File should be generated at build time and not edited by hand\n\n")
            file.write(f'#include "{original_file}"\n\n')  # Use the original file
            file.write("#include <Scene/Entity.h>\n#include <Scene/Scene.h>\n")
            file.write("#include <imgui.h>\n\n")

            file.write(f"namespace Aloe\n{{\n    namespace Reflect{cls}\n    {{\n")
            file.write("        bool s_initialized = false;\n\n")
            file.write("        void Initialize()\n        {\n")
            file.write("            if (s_initialized) return;\n")
            file.write("            s_initialized = true;\n        }\n\n")

            file.write("        Script* AddComponent(Entity entity)\n        {\n")
            file.write(f"            {cls}& Script = entity.AddComponent<{cls}>();\n")
            file.write("            return &Script;\n")
            file.write("        }\n\n")

            file.write("        bool HasComponent(Entity entity)\n        {\n")
            file.write(f"            return entity.HasComponent<{cls}>();\n")
            file.write("        }\n\n")

            file.write("        void DrawInterface(Entity entity)\n        {\n")
            file.write(f"            {cls}& component = entity.GetComponent<{cls}>();\n")
            for var_type, var_name in params:
                if var_type == "float":
                    file.write(f'            ImGui::SliderFloat("{var_name}", &component.{var_name}, -1000, 1000);\n')
                elif var_type == "int":
                    file.write(f'            ImGui::SliderInt("{var_name}", &component.{var_name}, -1000, 1000);\n')
            file.write("        }\n    }\n}\n\n")


if __name__ == "__main__":

    print("Starting Code Generation...")

    # Ensure proper arguments are provided
    if len(sys.argv) != 3:
        print("Usage: python code_gen.py <generated_path> <scripts_path>")
        sys.exit(1)

    generated_path = sys.argv[1]
    scripts_path = sys.argv[2]

    # Validate the input paths
    if not os.path.isdir(scripts_path):
        print(f"Error: The scripts path '{scripts_path}' is not a valid directory.")
        sys.exit(1)

    if not os.path.isdir(generated_path):
        print(f"Error: The generated path '{generated_path}' is not a valid directory.")
        sys.exit(1)

    # Step 1: Gather classes and the files they are defined in
    class_file_map = process_files(scripts_path)
    if not class_file_map:
        print("No classes with ACLASS() macro found.")
        sys.exit(1)

    print("Classes and their files:", class_file_map)

    # Step 2: Process variables marked with APARAM()
    classes_params = {}
    process_aparam_variables(scripts_path, classes_params)

    print("Classes with APARAM() variables:", classes_params)

    # Step 3: Generate individual files for each class
    script_output_dir = os.path.join(generated_path, "Scripts")
    generate_script_files(classes_params, class_file_map, script_output_dir)

    # Step 4: Generate Init_generated.cpp
    # Collect all class names for the Init file
    class_names = list(class_file_map.keys())
    init_file_path = os.path.join(generated_path, "Init_generated.cpp")
    generate_init_file(class_names, init_file_path)

    print("Code generation complete!")


