#include "RentalManager.h"

void RentalManager::initializeData()
{
    // Przykładowe osoby
    osoby.push_back(Osoba("Jan", "Kowalski", QDateTime(QDate(1990,1,1))));
    osoby.push_back(Osoba("Anna", "Nowak", QDateTime(QDate(1985,5,12))));
    osoby.push_back(Osoba("Piotr", "Zielinski", QDateTime(QDate(1978,10,30))));

    // Przykładowi kierowcy
    kierowcy.push_back(Kierowca("Adam", "Malinowski",
                                QDateTime(QDate(1980,4,20)),
                                "PJ12345",
                                QDateTime(QDate(1998,5,5))));
    kierowcy.push_back(Kierowca("Beata", "Kamińska",
                                QDateTime(QDate(1992,7,15)),
                                "PJ67890",
                                QDateTime(QDate(2012,9,1))));

    // Przykładowe samochody
    samochody.push_back(Samochod("Toyota", "Corolla", 2015, 60000,
                                 "VIN1234ABCD", "KR12345"));
    samochody.push_back(Samochod("Volkswagen", "Golf", 2018, 30000,
                                 "VIN5678EFGH", "WA12345"));
    samochody.push_back(Samochod("Skoda", "Octavia", 2020, 10000,
                                 "VIN9012IJKL", "PO12345"));
}
