#include <QApplication>
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QDateTime>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

class Osoba {
public:
    QString imie;
    QString nazwisko;
    QDateTime dataUrodzenia;

    Osoba(QString i, QString n, QDateTime d) : imie(i), nazwisko(n), dataUrodzenia(d) {}

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
    QString prawoJazdy;
    QString dataUzyskaniaPrawaJazdy;

    Kierowca(QString i, QString n, QDateTime d, QString p, QString u) : Osoba(i, n, d), prawoJazdy(p), dataUzyskaniaPrawaJazdy(u) {}

    void edytujKierowce() {
        cout << "Edytuj kierowce." << endl;
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
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        QVBoxLayout *layout = new QVBoxLayout;

        personListWidget = new QListWidget(this);
        layout->addWidget(personListWidget);

        QPushButton *addPersonButton = new QPushButton("Dodaj osobę", this);
        layout->addWidget(addPersonButton);
        connect(addPersonButton, &QPushButton::clicked, this, &MainWindow::on_addPersonButton_clicked);

        carListWidget = new QListWidget(this);
        layout->addWidget(carListWidget);

        QPushButton *rentButton = new QPushButton("Wypożycz", this);
        layout->addWidget(rentButton);
        connect(rentButton, &QPushButton::clicked, this, &MainWindow::on_rentButton_clicked);

        vector<Samochod> samochody = {
            Samochod("Toyota", "Corolla", 2020, 180000, "gjrnel433", "KR12345"),
            Samochod("Honda", "Civic", 2019, 10000, "gd3333333", "PO12345"),
            Samochod("Ford", "Focus", 2018, 20000, "123456789", "KR12345"),
        };

        for (const auto &samochod : samochody) {
            carListWidget->addItem(QString("%1 %2 (%3) (%4) %5 %6")
                .arg(QString::fromStdString(samochod.marka))
                .arg(QString::fromStdString(samochod.model))
                .arg(samochod.rokProdukcji)
                .arg(samochod.przebieg)
                .arg(QString::fromStdString(samochod.vin))
                .arg(QString::fromStdString(samochod.rejestracja)));
        }

        QWidget *container = new QWidget;
        container->setLayout(layout);
        setCentralWidget(container);

        updatePersonList();
    }

private slots:
    void on_addPersonButton_clicked() {
        bool ok;
        QString imie = QInputDialog::getText(this, tr("Dodaj osobę"), tr("Imię:"), QLineEdit::Normal, "", &ok);
        if (!ok || imie.isEmpty()) return;

        QString nazwisko = QInputDialog::getText(this, tr("Dodaj osobę"), tr("Nazwisko:"), QLineEdit::Normal, "", &ok);
        if (!ok || nazwisko.isEmpty()) return;

        QDateTime dataUrodzenia = QDateTime::currentDateTime(); // For simplicity, using current date-time

        osoby.push_back(Osoba(imie, nazwisko, dataUrodzenia));
        updatePersonList();
    }

    void on_rentButton_clicked() {
        QListWidgetItem *selectedCarItem = carListWidget->currentItem();
        if (!selectedCarItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
            return;
        }

        QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
        if (!selectedPersonItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz osobę z listy."));
            return;
        }

        QString carDetails = selectedCarItem->text();
        if (rentedCars.find(carDetails) != rentedCars.end()) {
            QMessageBox::warning(this, tr("Błąd"), tr("Ten samochód jest już wynajęty."));
            return;
        }

        int personIndex = personListWidget->row(selectedPersonItem);
        Osoba &osoba = osoby[personIndex];

        QString personDetails = osoba.imie + " " + osoba.nazwisko;

        // Save rental data to file
        ofstream file("baza.txt", ios::app);
        if (file.is_open()) {
            file << "Osoba: " << personDetails.toStdString() << ", Samochód: " << carDetails.toStdString() << "\n";
            file.close();
        } else {
            QMessageBox::warning(this, tr("Błąd"), tr("Nie można otworzyć pliku baza.txt."));
        }

        rentedCars.insert(carDetails);

        // Gray out the rented car
        selectedCarItem->setFlags(selectedCarItem->flags() & ~Qt::ItemIsEnabled);

        QMessageBox::information(this, tr("Wynajem samochodu"), tr("Wynajmij samochód dla: %1 %2\nSamochód: %3")
            .arg(osoba.imie)
            .arg(osoba.nazwisko)
            .arg(carDetails));
    }

private:
    QListWidget *personListWidget;
    QListWidget *carListWidget;
    vector<Osoba> osoby;
    unordered_set<QString> rentedCars;

    void updatePersonList() {
        personListWidget->clear();
        for (const Osoba &osoba : osoby) {
            personListWidget->addItem(osoba.imie + " " + osoba.nazwisko);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Wypożyczalnia Samochodów");
    mainWindow.resize(400, 300);
    mainWindow.show();

    return app.exec();
}

#include "main.moc"