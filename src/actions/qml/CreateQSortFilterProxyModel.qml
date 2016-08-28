import QtQuick 2.4
import OnceAgain 1.0

CreateQObject {
    id: root
    name: "QSortFilterProxyModel"
    description: "Creates a QSortFilterProxyModel"
    baseClass: "QSortFilterProxyModel"
    cppTemplate: ":/templates/qt/models/QSortFilterProxyModel.cpp"
    headerTemplate: ":/templates/qt/models/QSortFilterProxyModel.h"
    explicit: true
}
