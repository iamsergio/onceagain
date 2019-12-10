
def execute_action():
    cmakeFilePath = get_property('cmakeFilePath')

    if not qrcFilePath:
        print("AddToQRC: Could not determine qrc. Skipping.")
        return False

    # TODO
    return True


execute_action()
