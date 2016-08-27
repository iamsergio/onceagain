import QtQuick 2.4
import OnceAgain 1.0

CreateQObject {
    id: root
    macros: "Q_OBJECT"
    ctorArguments: "QWidget *parent = nullptr"
    implCtorArguments: "QWidget *parent"
    ctorInitList: "QWidget(parent)"
    baseClass: "QWidget"
    includes: [ "<QWidget>" ]
    explicit: true
}
