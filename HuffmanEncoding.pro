TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        huffman.cpp \
        main.cpp

HEADERS += \
    EncodedData.h \
    huffman.h \
    treenode.h

DISTFILES += \
    ../../Stanford/CS 106b/CS106b Assignments/starter-assign7/res/constitution.txt
