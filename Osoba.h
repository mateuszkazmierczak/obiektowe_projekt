#ifndef OSOBA_H
#define OSOBA_H

#include <QString>
#include <QDateTime>
#include <vector>

class Osoba {
public:
    QString imie;
    QString nazwisko;
    QDateTime dataUrodzenia;

    Osoba(QString i, QString n, QDateTime d);
    
    // Metody do obsługi Osoby
    void szukajOsobe(std::vector<Osoba> &osoby);
    void edytujOsobe();
    void usunOsobe(std::vector<Osoba> &osoby);

    static void dodajOsobe(std::vector<Osoba> &osoby);
};

#endif // OSOBA_H
