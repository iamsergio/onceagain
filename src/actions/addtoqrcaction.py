import os

def execute_action():
    qrcFilePath = get_property('qrcFilePath')
    lineToAdd = get_property('qrcLine')

    if not qrcFilePath:
        print("AddToQRC: Could not determine qrc. Skipping.")
        return False

    if not lineToAdd:
        print("AddToQRC: You need to specify a line to add")
        return False

    if not os.path.exists(qrcFilePath) or not os.path.isfile(qrcFilePath):
        print("AddToQRC: File " + qrcFilePath + " doesn't exist")
        return False

    f = open(qrcFilePath, 'r')
    lines = f.readlines()
    f.close()

    newlines = []
    for line in lines:
        newlines.append(line)
        if line.startswith("<qresource prefix="):
            newlines.append(lineToAdd + '\n')

    f = open(qrcFilePath, 'w')
    f.writelines(newlines)
    f.close()

    return True

execute_action()
