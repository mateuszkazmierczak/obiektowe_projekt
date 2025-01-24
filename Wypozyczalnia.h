#ifndef WYPOZYCZALNIA_H
#define WYPOZYCZALNIA_H

#include <QString>

class Wypozyczalnia {
public:
    QString nazwa;
    QString adres;

    Wypozyczalnia(QString n, QString a);
    virtual ~Wypozyczalnia() = default;

    virtual void edytujWypozyczalnie();
};

#endif // WYPOZYCZALNIA_H
