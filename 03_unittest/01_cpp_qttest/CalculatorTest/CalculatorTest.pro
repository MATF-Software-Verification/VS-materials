QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tst_calculatortest.cpp \
    ../Calculator/calculator.cpp

HEADERS += \
    ../Calculator/calculator.h


QMAKE_CXXFLAGS += -g -Wall -O0 --coverage

LIBS += -lgcov


