TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../rapidjson

SOURCES += \
        main.cpp \
    parser.cpp

HEADERS += \
    parser.h
