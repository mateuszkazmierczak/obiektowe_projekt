QT += core testlib
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
TARGET = WypozyczalniaTests

SOURCES += \
    test_rental.cpp \
    ../Osoba.cpp \
    ../Kierowca.cpp \
    ../Samochod.cpp \
    ../Wypozyczenie.cpp \
    ../Wypozyczalnia.cpp \
    ../RentalManager.cpp

INCLUDEPATH += ..
