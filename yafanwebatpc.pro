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
    server.h \
    global_defines.h

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

TRANSLATIONS += \
    de_DE.ts

OTHER_FILES += \
    testsuite.sh \
    translate.sh \
    languages.list \
    $${TRANSLATIONS}
CODECFORTR = UTF-8

COPY_FILES = $${OTHER_FILES}

QMAKE_POST_LINK += $$quote(./translate.sh $${PWD}/$$escape_expand(\\n\\t))
for(FILE,COPY_FILES){
    QMAKE_PRE_LINK += $$quote(cp $${PWD}/$${FILE} $${OUT_PWD}/$$escape_expand(\\n\\t))
}
