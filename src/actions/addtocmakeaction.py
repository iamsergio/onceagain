
def execute_action():
    cmakeFilePath = get_property('cmakeFilePath')

    if not cmakeFilePath:
        print("AddToCMake: Could not determine CMakeLists.txt. Skipping.")
        return False

    # TODO

    return True


execute_action()
