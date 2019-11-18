QT       += core gui widgets

TARGET = QSensor_system
TEMPLATE = app


SOURCES += main.cpp\
        klasaglowna.cpp \
    shader_loader.cpp \
    kamera_loader.cpp \
    opengl_framework.cpp \
    wizualizacja_3d.cpp \
    model_loader.cpp \
    obiekt_loader.cpp \
    sztuczny_horyzont.cpp \
    linia_czasu.cpp \
    terminal.cpp

HEADERS  += klasaglowna.h \
    shader_loader.h \
    kamera_loader.h \
    opengl_framework.h \
    wizualizacja_3d.h \
    model_loader.h \
    obiekt_loader.h \
    sztuczny_horyzont.h \
    linia_czasu.h \
    terminal.h

FORMS    += klasaglowna.ui

RESOURCES += \
    zasoby.qrc

LIBS += -lSOIL -lopengl32 -lassimp
