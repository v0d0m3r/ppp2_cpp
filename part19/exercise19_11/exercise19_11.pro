TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic -O0

DESTDIR = ../bin

SOURCES += \
    Test_facilities.cpp \
    counted_ptr_test.cpp

HEADERS += \
    Counted_ptr.hpp \
    Test_facilities.hpp
