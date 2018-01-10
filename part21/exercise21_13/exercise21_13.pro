TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic

DESTDIR = ../bin

SOURCES += main.cpp \
    ../../part11/exercise11_8/src/punctstream.cpp \
    Clear_punctstream.cpp

HEADERS += \
    ../../part11/exercise11_8/src/punctstream.hpp \
    Clear_punctstream.hpp
