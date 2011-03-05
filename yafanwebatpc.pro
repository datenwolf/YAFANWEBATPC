#-------------------------------------------------
#
# Project created by QtCreator 2011-03-04T07:39:41
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = yafanwebatpc
TEMPLATE = app


SOURCES += main.cpp\
        clientwidget.cpp \
    spaceobject.cpp

HEADERS  += clientwidget.h \
    spaceobject.h

CONFIG(debug, debug|release) {
# here comes debug specific statements
} else {
# here comes release specific statements
DEFINES += QT_NO_DEBUG_OUTPUT
}
