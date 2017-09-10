TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic -O0

DESTDIR = ../bin

SOURCES += main.cpp

HEADERS += \
    ../main_vector/Allocator.hpp \
    ../main_vector/Vector_base.hpp \
    ../main_vector/Vector.hpp \
    Vector_small.hpp
