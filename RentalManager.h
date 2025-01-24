#ifndef RENTALMANAGER_H
#define RENTALMANAGER_H

#include <vector>
#include "Osoba.h"
#include "Kierowca.h"
#include "Samochod.h"
#include "Wypozyczenie.h"

/**
 * Singleton zarządzający globalnymi danymi wypożyczalni.
 */
class RentalManager
{
public:
    // Funkcja statyczna zapewniająca dostęp do singletonu
    static RentalManager& instance() {
        static RentalManager s_instance; 
        return s_instance;
    }

    // Usuń kopiowanie i przenoszenie (cecha typowa dla Singleton):
    RentalManager(const RentalManager&) = delete;
    RentalManager(RentalManager&&) = delete;
    RentalManager& operator=(const RentalManager&) = delete;
    RentalManager& operator=(RentalManager&&) = delete;

    // Kolekcje dostępne publicznie:
    std::vector<Osoba> osoby;
    std::vector<Kierowca> kierowcy;
    std::vector<Samochod> samochody;
    std::vector<Wypozyczenie> wypozyczenia;

    // Metoda inicjalizująca przykładowe dane:
    void initializeData();

private:
    // Prywatny konstruktor:
    RentalManager() = default;
};

#endif // RENTALMANAGER_H
