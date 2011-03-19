#-------------------------------------------------
#
# Project created by QtCreator 2011-03-04T07:39:41
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = yafanwebatpc
TEMPLATE = app

LIBS += -lglut
SOURCES += main.cpp\
        clientwidget.cpp \
    spaceobject.cpp \
    server.cpp \
    connection.cpp \
    loopbackconnection.cpp \
    glspaceobject.cpp

HEADERS  += clientwidget.h \
    spaceobject.h \
    server.h \
    global_defines.h \
    connection.h \
    loopbackconnection.h \
    glspaceobject.h

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

CONFIG(qtToTextureFlip){
    DEFINES += QT_TO_TEXTURE_FLIP
}

TRANSLATIONS += $$system(cat languages.list)

OTHER_FILES += \
    testsuite.sh \
    translate.sh \
    get_impact.sh \
    languages.list \
    hud.png \
    $${TRANSLATIONS}
CODECFORTR = UTF-8

COPY_FILES = $${OTHER_FILES}

QMAKE_POST_LINK += $$quote(./translate.sh $${PWD}/$$escape_expand(\\n\\t))
QMAKE_POST_LINK += $$quote(./get_impact.sh $$escape_expand(\\n\\t))
for(FILE,COPY_FILES){
    QMAKE_PRE_LINK += $$quote(test "_$${PWD}_" = "_$${OUT_PWD}_" || cp $${PWD}/$${FILE} $${OUT_PWD}/$$escape_expand(\\n\\t))
}
