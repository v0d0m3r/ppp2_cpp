TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic -O0

SOURCES += \
    calculator10.cpp

HEADERS += \
    Pair.hpp
