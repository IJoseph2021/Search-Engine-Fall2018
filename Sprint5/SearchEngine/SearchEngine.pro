TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
<<<<<<< HEAD
    StemmerFiles/porter2_stemmer.cpp \
    main.cpp

DISTFILES += \
    porter2_stemmer/diffs.txt

HEADERS += \
    porter2_stemmer/util/hash.h \
    porter2_stemmer/util/string_view.h \
    porter2_stemmer/porter2_stemmer.h \
    StemmerFiles/util/hash.h \
    StemmerFiles/util/string_view.h \
    StemmerFiles/porter2_stemmer.h
=======
        main.cpp

HEADERS += \
    indexerface.h \
    avltree.h
>>>>>>> feature/indexer-Data-Structures
