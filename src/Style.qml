import QtQuick 2.12

///@brief allows to customize a project
QtObject {
    id: root

    /// @brief name of the project
    property string name: ""

    /// @brief absolute path for the projec
    property string projectRootPath: ""

    /// @brief absolute path for the QRC file
    property string qrcPath: ""
}
