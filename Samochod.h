#ifndef SAMOCHOD_H
#define SAMOCHOD_H

#include <QString>
#include <vector>
#include <algorithm>

class Samochod {
public:
    std::string marka;
    std::string model;
    int rokProdukcji;
    int przebieg;
    std::string vin;
    std::string rejestracja;

    Samochod(std::string m, std::string mo, int r, int p, std::string v, std::string re);

    void edytujSamochod();
    void usunSamochod(std::vector<Samochod> &samochody);
    void szukajSamochod(std::vector<Samochod> &samochody);

    static void dodajSamochod(std::vector<Samochod> &samochody);
};

#endif // SAMOCHOD_H
