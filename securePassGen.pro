# -------------------------------------------------
# Project created by QtCreator 2010-03-29T08:15:58
# James P. Parziale
# This file may be distributed under the terms of the GNU Public License.
# -------------------------------------------------
TARGET = securePassGen
TEMPLATE = app
INCLUDEPATH += ../Tools/
CONFIG -= debug \
    release \
    debug_and_release \
    debug_and_release_target
SOURCES += main.cpp \
    mainwindow.cpp \
    about.cpp \
    securePassGen.cpp
HEADERS += mainwindow.h \
    about.h
FORMS += securePassGen.ui \
    about.ui
OTHER_FILES += make_qt.sh
RC_FILE = securePassGen.rc
RESOURCES += securePassGen.qrc
QT += core \
    gui \
    widgets
