#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
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
    void edytujOsobe() {
        cout << "Edytuj osobe." << endl;
    }
    void usunOsobe() {
        cout << "Usun osobe." << endl;
    }
    void dodajOsobe() {
        cout << "Dodaj osobe." << endl;
    }
};

class Kierowca : public Osoba {
public:
    string prawoJazdy;
    string dataUzyskaniaPrawaJazdy;

    Kierowca(string i, string n, time_t d, string p, string u) {
        imie = i;
        nazwisko = n;
        dataUrodzenia = d;
        prawoJazdy = p;
        dataUzyskaniaPrawaJazdy = u;
    }

    void edytujKierowce() {
        cout << "Kierowca: " << imie << " " << nazwisko << ", Prawo jazdy: " << prawoJazdy << dataUzyskaniaPrawaJazdy <<  endl;
    }
};

class Samochod {
public:
    string marka;
    string model;
    int rokProdukcji;
    int przebieg;
    string vin;
    string rejestracja;

    Samochod(string m, string mo, int r, int p, string v, string re) : marka(m), model(mo), rokProdukcji(r), przebieg(p), vin(v), rejestracja(re) {}

    void edytujSamochod() {
        cout << "Edytuj samochod." << endl;
    }
    void usunSamochod() {
        cout << "Usun samochod." << endl;
    }
    void dodajSamochod() {
        cout << "Dodaj samochod." << endl;
    }
    void szukajSamochod() {
        cout << "Szukaj samochod." << endl;
    }
};

class Wypozyczenia {
public:
    Osoba osoba;
    Samochod samochod;
    time_t dataStartu;
    time_t dataKonca;
    bool dodatkoweUbezpieczenie;

    Wypozyczenia(Osoba o, Samochod s, time_t ds, time_t dk, bool du) 
        : osoba(o), samochod(s), dataStartu(ds), dataKonca(dk), dodatkoweUbezpieczenie(du) {}

    void wyswietlWypozyczenie() {
        cout << "Wypożyczenie: " << osoba.imie << " " << osoba.nazwisko << ", Samochód: " 
             << samochod.marka << " " << samochod.model << ", Data startu: " << ctime(&dataStartu) 
             << ", Data końca: " << ctime(&dataKonca) << ", Dodatkowe ubezpieczenie: " 
             << (dodatkoweUbezpieczenie ? "Tak" : "Nie") << endl;
    }
    void rozpocznijWypozyczenie() {
        cout << "Rozpocznij wypożyczenie." << endl;
    }
    void zakonczWypozyczenie() {
        cout << "Zakończ wypożyczenie." << endl;
    }
    void edytujWypozyczenie() {
        cout << "Edytuj wypożyczenie." << endl;
    }
};

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QListWidget *carList = new QListWidget(this);
        QPushButton *rentButton = new QPushButton("Wypożycz", this);

        vector<Samochod> samochody = {
            Samochod("Toyota", "Corolla", 2020,180000, "gjrnel433", "KR12345"),
            Samochod("Honda", "Civic", 2019, 10000, "gd3333333", "PO12345"),
            Samochod("Ford", "Focus", 2018, 20000, "123456789", "KR12345"),
        };

        for (const auto &samochod : samochody) {
            carList->addItem(QString("%1 %2 (%3) (%4) %5 %6")
                .arg(QString::fromStdString(samochod.marka))
                .arg(QString::fromStdString(samochod.model))
                .arg(samochod.rokProdukcji)
                .arg(samochod.przebieg)
                .arg(QString::fromStdString(samochod.vin))
                .arg(QString::fromStdString(samochod.rejestracja)));
        }
        layout->addWidget(carList);
        layout->addWidget(rentButton);

        connect(rentButton, &QPushButton::clicked, [carList]() {
            QListWidgetItem *selectedItem = carList->currentItem();
            if (selectedItem) {
                QMessageBox::information(nullptr, "Wypożyczono", "Wypożyczono samochód: " + selectedItem->text());
            } else {
                QMessageBox::warning(nullptr, "Błąd", "Nie wybrano samochodu.");
            }
        });

        setLayout(layout);
        setWindowTitle("Wypożyczalnia Samochodów");
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}