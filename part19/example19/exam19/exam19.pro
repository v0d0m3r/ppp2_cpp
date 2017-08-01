TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14 --pedantic -O0

SOURCES += main.cpp \
    Vector_easy.cpp

HEADERS += \
    Vector_easy.hpp
