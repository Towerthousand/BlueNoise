QT -= gui

TARGET = BlueNoise
CONFIG -= app_bundle

TEMPLATE = app

include(../VBE-Scenegraph/VBE-Scenegraph.pri)
include(../VBE-Profiler/VBE-Profiler.pri)
include(../VBE/VBE.pri)

LIBS += -lGLEW -lGL -lSDL2
QMAKE_CXXFLAGS += -std=c++0x -fno-exceptions

INCLUDEPATH += .

SOURCES += main.cpp \
    commons.cpp \
    Scene.cpp \
    Noise.cpp \
    MyProfiler.cpp

HEADERS += \
    commons.hpp \
    Scene.hpp \
    Noise.hpp \
    MyProfiler.hpp

OTHER_FILES += \
    assets/shaders/tex.frag \
    assets/shaders/tex.vert

