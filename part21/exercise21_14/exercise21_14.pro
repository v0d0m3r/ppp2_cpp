TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic

DESTDIR = ../bin

SOURCES += main.cpp \
    ../../part11/exercise11_8/src/punctstream.cpp \
    ../exercise21_13/Clear_punctstream.cpp

HEADERS += \
    ../../part11/exercise11_8/src/punctstream.hpp \
    ../exercise21_13/Clear_punctstream.hpp \
    Finder.hpp
