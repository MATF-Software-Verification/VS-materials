QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_mock_clock.cpp \
    ../play_time_refactored/mock_clock.cpp \
    ../play_time_refactored/play_time.cpp \
    ../play_time_refactored/second_clock.cpp \
    ../play_time_refactored/system_clock.cpp

HEADERS += \
    ../play_time_refactored/mock_clock.h \
    ../play_time_refactored/play_time.h \
    ../play_time_refactored/second_clock.h \
    ../play_time_refactored/system_clock.h
