import os, shutil

def execute_action():
    folderName = get_property('folderName')
    removeItself =  get_property('removeItself')

    if not folderName:
        print("RemoveDirectory: Folder name is empty")
        return False

    isAbsolute = os.path.abspath(folderName) == folderName
    if not isAbsolute:
        print("RemoveDirectory: Only absolute paths accepted")
        return False

    if os.path.exists(folderName):    
        shutil.rmtree(folderName)

    if not removeItself:
        if not os.mkdir(folderName):
            return False

    return True

execute_action()
