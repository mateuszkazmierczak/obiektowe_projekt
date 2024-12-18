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

    void szukajOsobe(vector<Osoba> &osoby) {
        QString searchImie = QInputDialog::getText(nullptr, "Szukaj osoby", "Podaj imię:");
        if (!searchImie.isEmpty()) {
            for (const auto &osoba : osoby) {
                if (osoba.imie == searchImie) {
                    QMessageBox::information(nullptr, "Wynik wyszukiwania", "Znaleziono osobę: " + osoba.imie + " " + osoba.nazwisko);
                    return;
                }
            }
            QMessageBox::information(nullptr, "Wynik wyszukiwania", "Nie znaleziono osoby o imieniu: " + searchImie);
        }
    }

    void edytujOsobe() {
        QString newImie = QInputDialog::getText(nullptr, "Edytuj osobę", "Nowe imię:", QLineEdit::Normal, imie);
        QString newNazwisko = QInputDialog::getText(nullptr, "Edytuj osobę", "Nowe nazwisko:", QLineEdit::Normal, nazwisko);
        if (!newImie.isEmpty() && !newNazwisko.isEmpty()) {
            imie = newImie;
            nazwisko = newNazwisko;
            QMessageBox::information(nullptr, "Edytuj osobę", "Dane osoby zostały zaktualizowane.");
        }
    }

    void usunOsobe(vector<Osoba> &osoby) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Usuń osobę", "Czy na pewno chcesz usunąć tę osobę?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            auto it = std::find_if(osoby.begin(), osoby.end(), [this](const Osoba &o) {
                return o.imie == this->imie && o.nazwisko == this->nazwisko;
            });
            if (it != osoby.end()) {
                osoby.erase(it);
                QMessageBox::information(nullptr, "Usuń osobę", "Osoba została usunięta.");
            }
        }
    }

    static void dodajOsobe(vector<Osoba> &osoby) {
        QString newImie = QInputDialog::getText(nullptr, "Dodaj osobę", "Imię:");
        if (newImie.isEmpty()) return;

        QString newNazwisko = QInputDialog::getText(nullptr, "Dodaj osobę", "Nazwisko:");
        if (newNazwisko.isEmpty()) return;

        QDate newDataUrodzenia = QDate::fromString(QInputDialog::getText(nullptr, "Dodaj osobę", "Data urodzenia (YYYY-MM-DD):"), "yyyy-MM-dd");
        if (!newDataUrodzenia.isValid()) {
            QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data urodzenia.");
            return;
        }

        osoby.push_back(Osoba(newImie, newNazwisko, QDateTime(newDataUrodzenia)));
        QMessageBox::information(nullptr, "Dodaj osobę", "Nowa osoba została dodana.");
    }
};

class Kierowca : public Osoba {
public:
    QString prawoJazdy;
    QString dataUzyskaniaPrawaJazdy;

    Kierowca(QString i, QString n, QDateTime d, QString p, QString u) : Osoba(i, n, d), prawoJazdy(p), dataUzyskaniaPrawaJazdy(u) {}

    void edytujKierowce() {
        edytujOsobe();
        QString newPrawoJazdy = QInputDialog::getText(nullptr, "Edytuj kierowcę", "Nowy numer prawa jazdy:", QLineEdit::Normal, prawoJazdy);
        if (!newPrawoJazdy.isEmpty()) {
            prawoJazdy = newPrawoJazdy;
            QMessageBox::information(nullptr, "Edytuj kierowcę", "Dane kierowcy zostały zaktualizowane.");
        }
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

        QPushButton *searchPersonButton = new QPushButton("Szukaj osoby", this);
        layout->addWidget(searchPersonButton);
        connect(searchPersonButton, &QPushButton::clicked, this, &MainWindow::on_searchPersonButton_clicked);

        QPushButton *editPersonButton = new QPushButton("Edytuj osobę", this);
        layout->addWidget(editPersonButton);
        connect(editPersonButton, &QPushButton::clicked, this, &MainWindow::on_editPersonButton_clicked);

        QPushButton *deletePersonButton = new QPushButton("Usuń osobę", this);
        layout->addWidget(deletePersonButton);
        connect(deletePersonButton, &QPushButton::clicked, this, &MainWindow::on_deletePersonButton_clicked);

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
        Osoba::dodajOsobe(osoby);
        updatePersonList();
    }

    void on_searchPersonButton_clicked() {
        if (osoby.empty()) {
            QMessageBox::information(this, "Brak danych", "Lista osób jest pusta.");
            return;
        }
        osoby.front().szukajOsobe(osoby);
    }

    void on_editPersonButton_clicked() {
        QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
        if (!selectedPersonItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz osobę z listy."));
            return;
        }
        int personIndex = personListWidget->row(selectedPersonItem);
        osoby[personIndex].edytujOsobe();
        updatePersonList();
    }

    void on_deletePersonButton_clicked() {
        QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
        if (!selectedPersonItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz osobę z listy."));
            return;
        }
        int personIndex = personListWidget->row(selectedPersonItem);
        osoby[personIndex].usunOsobe(osoby);
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
        selectedCarItem->setBackground(Qt::lightGray);

        QMessageBox::information(this, tr("Wynajem samochodu"), tr("Wynajęto samochód dla: %1\nSamochód: %2")
            .arg(personDetails)
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
    mainWindow.resize(400, 500);
    mainWindow.show();

    return app.exec();
}

#include "main.moc"