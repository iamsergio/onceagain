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

    /// @brief filenames are generated with camel case
    property bool camelCaseFileNames: true

    /// @brief the default cmake variable name that holds the sources
    property string defaultCMakeVariable: ""

    /// @brief the default cmake like to add to the cmake variable
    property string defaultCMakeLine: "    %1"

    /// @brief the default namespace to uses
    property string defaultNamespace: ""
}
