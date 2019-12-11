import QtQuick 2.4
import OnceAgain 1.0

PythonAction {
    name: "AddToQRC"

    pythonFileName: "addtoqrc.py"
    property string qrcFilePath: ""
    property string qrcLine: ""
}
