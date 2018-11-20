TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../rapidjson
INCLUDEPATH += $$PWD/../../JSON

SOURCES += \
    StemmerFiles/porter2_stemmer.cpp \
    main.cpp \
    docu.cpp \
    word.cpp \
    stopper.cpp \
    avlindex.cpp \
    parser.cpp

DISTFILES += \
    porter2_stemmer/diffs.txt \
    ../StopWordList.txt

HEADERS += \
    StemmerFiles/util/hash.h \
    StemmerFiles/util/string_view.h \
    StemmerFiles/porter2_stemmer.h \
    avltree.h \
    indexerface.h \
    docu.h \
    word.h \
    stopper.h \
    avlindex.h \
    hashindex.h \
    parser.h

HEADERS += \
    indexerface.h \
    avltree.h
