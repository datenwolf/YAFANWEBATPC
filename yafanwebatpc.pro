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
    spaceobject.cpp \
    server.cpp

HEADERS  += clientwidget.h \
    spaceobject.h \
    server.h

CONFIG(debug, debug|release) {
# here comes debug specific statements
QMAKE_CXXFLAGS += -g -pg
} else {
# here comes release specific statements
DEFINES += QT_NO_DEBUG_OUTPUT
QMAKE_CXXFLAGS += -O3
}

CONFIG(textureflip) {
DEFINES += CFG_TEXTURE_FLIP
}

OTHER_FILES += \
    testsuite.sh \
    translate.sh \
    de_DE.ts \
    languages.list
TRANSLATIONS += \
    de_DE.ts
CODECFORTR = UTF-8
