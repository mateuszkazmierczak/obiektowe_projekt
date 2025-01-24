#ifndef KIEROWCA_H
#define KIEROWCA_H

#include "Osoba.h"

class Kierowca : public Osoba {
public:
    QString prawoJazdy;
    QDateTime dataUzyskaniaPrawaJazdy;

    Kierowca(QString i, QString n, QDateTime d, QString p, QDateTime u);

    void edytujKierowce();

    static void dodajKierowce(std::vector<Kierowca> &kierowcy);
};

#endif // KIEROWCA_H
