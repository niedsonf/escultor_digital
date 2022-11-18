TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cutvoxel.cpp \
        figurageometrica.cpp \
        interpreter.cpp \
        main.cpp \
        putvoxel.cpp \
        sculptor.cpp

HEADERS += \
    cutvoxel.h \
    figurageometrica.h \
    interpreter.h \
    putvoxel.h \
    sculptor.h \
    voxel.h
