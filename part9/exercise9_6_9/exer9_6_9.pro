TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++14 -Wextra --pedantic

SOURCES += main.cpp \
    book.cpp \
    chrono.cpp \
    library.cpp \
    patron.cpp

HEADERS += \
    book.h \
    chrono.h \
    library.h \
    patron.h
