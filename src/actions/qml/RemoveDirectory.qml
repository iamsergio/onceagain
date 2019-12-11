import QtQuick 2.4
import OnceAgain 1.0

PythonAction {
    name: "RemoveDirectory"

    pythonFileName: "removedirectory.py";
    property string folderName: ""
    property bool removeItself: false
}
