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
    parser.cpp \
    hashindex.cpp

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
    parser.h \
    hashtable.h

HEADERS += \
    indexerface.h \
    avltree.h

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../myhtml/lib/release/ -lmyhtml
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../myhtml/lib/debug/ -lmyhtml
#else:unix: LIBS += -L$$PWD/../../myhtml/lib/ -lmyhtml

#INCLUDEPATH += $$PWD/../../myhtml/include
#DEPENDPATH += $$PWD/../../myhtml/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../htmlParser/lib/release/ -lmyhtml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../htmlParser/lib/debug/ -lmyhtml
else:unix: LIBS += -L$$PWD/../../htmlParser/lib/ -lmyhtml

INCLUDEPATH += $$PWD/../../htmlParser/include
DEPENDPATH += $$PWD/../../htmlParser/include
