set(ONCEAGAIN_SRCS
    action.cpp
    actions/addtocmakeaction.cpp
    actions/addtocmakeaction.h
    actions/addtoqrcaction.cpp
    actions/addtoqrcaction.h
    actions/createclassaction.cpp
    actions/createfileaction.cpp
    actions/createfolderaction.cpp
    actions/openeditor.cpp
    actions/openexplorer.cpp
    actions/pythonaction.cpp
    actions/removedirectory.cpp
    actions/removefileaction.cpp
    actions/runcommand.cpp
    kernel.cpp
    main.cpp
    mainwindow.cpp
    script.cpp
    scriptmodel.cpp
    scriptproxymodel.cpp
    utils/cmakeutils.cpp
    utils/fileutils.cpp
    utils/stringutils.cpp
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../resources.qrc)

add_definitions(-DQT_NO_KEYWORDS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})
add_executable(onceagain ${ONCEAGAIN_SRCS} ${RESOURCES})
target_link_libraries(onceagain Qt5::Widgets Qt5::Quick KDAB::kddockwidgets ${PYTHON_LIBRARIES})
