TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    mock_clock.cpp \
    play_time.cpp \
    second_clock.cpp \
    system_clock.cpp

HEADERS += \
    mock_clock.h \
    play_time.h \
    second_clock.h \
    system_clock.h
