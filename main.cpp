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
};

class Samochod {
public:
    string marka;
    string model;
    int rokProdukcji;

    Samochod(string m, string mo, int r) : marka(m), model(mo), rokProdukcji(r) {}
};

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QListWidget *carList = new QListWidget(this);
        QPushButton *rentButton = new QPushButton("Wypożycz", this);

        vector<Samochod> samochody = {
            Samochod("Toyota", "Corolla", 2020),
            Samochod("Honda", "Civic", 2019),
            Samochod("Ford", "Focus", 2018)
        };

        for (const auto &samochod : samochody) {
            carList->addItem(QString::fromStdString(samochod.marka + " " + samochod.model + " (" + to_string(samochod.rokProdukcji) + ")"));
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