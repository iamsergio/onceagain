import QtQuick 2.4
import OnceAgain 1.0

CreateClass {
    id: root
    isQObject: true
    ctorArguments: "QObject *parent = nullptr"
    implCtorArguments: "QObject *parent"
    ctorInitList: "%1(parent)".arg(baseClass)
    baseClass: "QObject"
    includes: [ "<%1>".arg(baseClass) ]
    explicit: true
}
