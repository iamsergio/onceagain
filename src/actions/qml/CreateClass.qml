import QtQuick 2.4
import OnceAgain 1.0

Action {
    id: root
    property string className: ""
    property bool camelCaseFileName: false
    property bool explicit: false
    property string template: ""
    property var includes: []

    property string cppFolder: ""
    property string headerFolder: cppFolder
    property string licenseHeader: ""
    property string ctorArguments: ""
    property string implCtorArguments: ""
    property string baseClass: ""
    property string ctorInitList: ""
    property string macros: ""

    property string cppTemplate: ":/templates/cpp/class.cpp"
    property string headerTemplate: ":/templates/cpp/class.h"

    hiddenProperties: ["cppFolder", "headerFolder", "template", "camelCaseFileName",
                       "licenseHeader", "ctorArguments", "includes", "explicit",
                       "baseClass", "ctorInitList", "macros", "implCtorArguments", "headerTemplate", "cppTemplate"]
    readonly property string filename: camelCaseFileName ? className : className.toLowerCase()
    readonly property string headerFileName: filename.length > 0 ? filename + ".h"
                                                                 : ""
    readonly property string cppFileName: filename.length > 0 ? filename + ".cpp"
                                                              : ""
    readonly property string includeGuard: className.toUpperCase()

    function includesText() {
        if (root.includes.length == 0)
            return ""

        var text = "\n"

        for (var i = 0; i < root.includes.length; ++i) {
            text += "#include " + root.includes[i] + "\n"
        }

        return text;
    }

    function baseClassText()
    {
        if (!root.baseClass)
            return ""

        return " : public " + root.baseClass
    }

    function macrosText()
    {
        return root.macros ? "    %1\n".arg(root.macros): ""
    }

    function explicitText()
    {
        return root.explicit ? "explicit " : ""
    }

    function ctorInitListText()
    {
        return root.ctorInitList ? "\n    : %1".arg(root.ctorInitList) : ""
    }

    CreateFile {
        fileName: cppFolder + cppFileName
        contents: _file.read(cppTemplate).arg(root.headerFileName)
                                         .arg(root.className)
                                         .arg(root.licenseHeader)
                                         .arg(root.implCtorArguments)
                                         .arg(ctorInitListText())
    }

    CreateFile {
        fileName: headerFolder + headerFileName
        contents: _file.read(headerTemplate).arg(root.includeGuard)
                                            .arg(root.className)
                                            .arg(root.licenseHeader)
                                            .arg(baseClassText())
                                            .arg(explicitText())
                                            .arg(includesText())
                                            .arg(root.ctorArguments)
                                            .arg(macrosText())
    }
}
