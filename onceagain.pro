TEMPLATE = app
TARGET = onceagain

INCLUDEPATH += . $$PWD/src/ $$PWD/src/utils/ $$PWD/src/actions/

SOURCES += src/main.cpp \
           src/action.cpp \
           src/kernel.cpp \
           src/script.cpp \
           src/scriptmodel.cpp \
           src/scriptproxymodel.cpp \
           src/mainwindow.cpp \
           src/actions/createfolderaction.cpp \
           src/actions/createfileaction.cpp \
           src/actions/openeditor.cpp \
           src/actions/removedirectory.cpp \
           src/actions/removefileaction.cpp \
           src/actions/runcommand.cpp \
           src/utils/fileutils.cpp \
           src/utils/stringutils.cpp \
           src/utils/cmakeutils.cpp


QT += widgets quick

HEADERS += src/action.h \
           src/kernel.h \
           src/script.h \
           src/scriptmodel.h \
           src/scriptproxymodel.h \
           src/mainwindow.h \
           src/actions/createfolderaction.h \
           src/actions/createfileaction.h \
           src/actions/openeditor.h \
           src/actions/removedirectory.h \
           src/actions/removefileaction.h \
           src/actions/runcommand.h \
           src/utils/fileutils.h \
           src/utils/stringutils.h \
           src/utils/cmakeutils.h \

RESOURCES += resources.qrc
