QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtProject
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Osoba.cpp \
    Kierowca.cpp \
    Samochod.cpp \
    Wypozyczenie.cpp \
    Wypozyczalnia.cpp

HEADERS += \
    MainWindow.h \
    Osoba.h \
    Kierowca.h \
    Samochod.h \
    Wypozyczenie.h \
    Wypozyczalnia.h
