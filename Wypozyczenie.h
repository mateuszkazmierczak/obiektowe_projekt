#ifndef WYPOZYCZENIE_H
#define WYPOZYCZENIE_H

#include <QDateTime>
#include "Osoba.h"
#include "Samochod.h"

class Wypozyczenie {
public:
    Osoba osoba;         // lub Kierowca – ale tutaj mamy pewną abstrakcję przez dziedziczenie
    Samochod samochod;
    QDateTime dataStart;
    QDateTime dataEnd;
    bool additionalInsurance;

    Wypozyczenie(const Osoba &o, const Samochod &s, const QDateTime &start, const QDateTime &end, bool insurance);

    void edytujWypozyczenie();
};

#endif // WYPOZYCZENIE_H
