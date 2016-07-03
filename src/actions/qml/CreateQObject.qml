import QtQuick 2.4
import OnceAgain 1.0

CreateClass {
    id: root
    macros: "Q_OBJECT"
    ctorArguments: "QObject *parent = nullptr"
    implCtorArguments: "QObject *parent"
    ctorInitList: "QObject(parent)"
    baseClass: "QObject"
    includes: [ "<QObject>" ]
    explicit: true
}
