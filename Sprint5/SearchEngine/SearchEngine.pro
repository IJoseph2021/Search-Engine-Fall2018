TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    StemmerFiles/porter2_stemmer.cpp \
    main.cpp \
    docu.cpp \
    word.cpp

DISTFILES += \
    porter2_stemmer/diffs.txt

HEADERS += \
    StemmerFiles/util/hash.h \
    StemmerFiles/util/string_view.h \
    StemmerFiles/porter2_stemmer.h \
    avltree.h \
    indexerface.h \
    docu.h \
    word.h

HEADERS += \
    indexerface.h \
    avltree.h
