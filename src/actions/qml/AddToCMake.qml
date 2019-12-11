import QtQuick 2.4
import OnceAgain 1.0

PythonAction {
    name: "AddToCMake"

    pythonFileName: "addtocmake.py"
    property string cmakeFilePath: ""
    property string cmakeVariable: ""
    property string cmakeLine: ""
}
