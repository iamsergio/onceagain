
def execute_action():
    cmakeFilePath = get_property('cmakeFilePath')
    lineToAdd = get_property('cmakeLine')
    cmakeVariable = get_property('cmakeVariable')

    if not cmakeFilePath:
        print("AddToCMake: Could not determine CMakeLists.txt. Skipping.")
        return False

    if not lineToAdd:
        print("AddToCMake: You need to specify a line to add")
        return False

    if not cmakeVariable:
        print("AddToCMake: You need to specify a cmake variable name")
        return False

    f = open(cmakeFilePath, 'r')
    lines = f.readlines()
    f.close()

    newlines = []
    for line in lines:
        newlines.append(line)
        if line.startswith("set(" + cmakeVariable):
            newlines.append(lineToAdd + '\n')

    f = open(cmakeFilePath, 'w')
    f.writelines(newlines)
    f.close()

    return True

execute_action()
