#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Wypozyczalnia {
public:
    string nazwa;
    string adres;

    void edytujWypozyczalnie() {
        cout << "Edytowanie danych wypożyczalni." << endl;
    }
};

class Osoba {
public:
    string imie;
    string nazwisko;
    time_t dataUrodzenia;

    void szukajOsobe() {
        cout << "Szukaj osoby." << endl;
    }

    void dodajOsobe() {
        cout << "Dodaj osobę." << endl;
    }

    void usunOsobe() {
        cout << "Usuń osobę." << endl;
    }

    void edytujOsobe() {
        cout << "Edytuj dane osoby." << endl;
    }
};


class Kierowca : public Osoba {
public:
    string numerPrawaJazdy;
    time_t dataUzyskaniaPrawka;

    void edytujKierowce() {
        cout << "Edytuj dane kierowcy." << endl;
    }
};

class Samochod {
public:
    string marka;
    string model;
    int rocznik;
    int przebieg;
    string vin;
    string rejestracja;

    void szukajSamochod() {
        cout << "Szukaj samochodu." << endl;
    }

    void dodajSamochod() {
        cout << "Dodaj samochód." << endl;
    }

    void usunSamochod() {
        cout << "Usuń samochód." << endl;
    }

    void edytujSamochod() {
        cout << "Edytuj dane samochodu." << endl;
    }
};

class Wypozyczenia {
public:
    time_t start;
    time_t koniec;
    bool dodatkoweUbezpieczenie;

    void rozpocznijWypozyczenie() {
        cout << "Rozpoczęcie wypożyczenia." << endl;
    }

    void zakonczWypozyczenie() {
        cout << "Zakończenie wypożyczenia." << endl;
    }

    void edytujWypozyczenie() {
        cout << "Edytuj wypożyczenie." << endl;
    }
};

int main() {
    Wypozyczalnia wyp;
    wyp.nazwa = "Wypożyczalnia A";
    wyp.adres = "Warszawa, ul. Prosta 1";
    wyp.edytujWypozyczalnie();

    Osoba osoba;
    osoba.imie = "Jan";
    osoba.nazwisko = "Kowalski";
    osoba.szukajOsobe();

    Kierowca kierowca;
    kierowca.imie = "Anna";
    kierowca.nazwisko = "Nowak";
    kierowca.numerPrawaJazdy = "XYZ123456";
    kierowca.edytujKierowce();

    Samochod samochod;
    samochod.marka = "Toyota";
    samochod.model = "Corolla";
    samochod.rocznik = 2020;
    samochod.rejestracja = "WX12345";
    samochod.edytujSamochod();

    Wypozyczenia wypozyczenie;
    wypozyczenie.dodatkoweUbezpieczenie = true;
    wypozyczenie.rozpocznijWypozyczenie();

    return 0;
}
