import QtQuick 2.4
import OnceAgain 1.0

import "qrc:///src/actions/qml"

PythonAction {
    id: root
    property string className: ""
    property bool camelCaseFileName: _style.camelCaseFileNames
    property bool explicit: false
    property string template: ""
    property var includes: []

    property string licenseHeader: ""
    property string ctorArguments: ""
    property string implCtorArguments: ""
    property string baseClass: ""
    property string ctorInitList: ""
    property bool isQObject: false
    property string namespace: ""
    property bool usesPragmaOnce: true

    property string cmakeliststxt: _file.firstCMakeFileFrom(_baseTarget)
    property string cmakeVariable: _style.defaultCMakeVariable
    property string cmakeLine: _style.defaultCMakeLine

    hiddenProperties: ["template", "camelCaseFileName",
                       "licenseHeader", "ctorArguments", "includes", "explicit",
                       "ctorInitList", "implCtorArguments"]
    readonly property string filename: camelCaseFileName ? className : className.toLowerCase()
    readonly property string headerFileName: filename.length > 0 ? filename + ".h"
                                                                 : ""
    readonly property string cppFileName: filename.length > 0 ? filename + ".cpp"
                                                              : ""
    readonly property string includeGuard: className.toUpperCase()
    readonly property string baseTarget: _baseTarget

    pythonFileName: "createclass.py"

    function includesText() {
        if (root.includes.length == 0)
            return ""

        var text = "\n"

        for (var i = 0; i < root.includes.length; ++i) {
            text += "#include " + root.includes[i] + "\n"
        }

        return text;
    }

    AddToCMake {
        cmakeFilePath: root.cmakeliststxt
        cmakeVariable: root.cmakeVariable
        cmakeLine: root.cmakeLine.arg(root.cppFileName)
    }
}
