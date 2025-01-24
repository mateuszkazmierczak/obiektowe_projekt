#include "MainWindow.h"
#include "RentalManager.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      wypozyczalnia("Domyślna Wypożyczalnia", "Domyślny Adres")
{
    // Layout
    QVBoxLayout *layout = new QVBoxLayout;

    setWindowTitle(wypozyczalnia.nazwa + " - " + wypozyczalnia.adres);

    //
    // 1. Sekcja Osób
    //
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

    QPushButton *clearPersonSelectionButton = new QPushButton("Odznacz osobę", this);
    layout->addWidget(clearPersonSelectionButton);
    connect(clearPersonSelectionButton, &QPushButton::clicked, this, &MainWindow::on_clearPersonSelection_clicked);

    //
    // 2. Sekcja Kierowców
    //
    driverListWidget = new QListWidget(this);
    layout->addWidget(driverListWidget);

    QPushButton *addDriverButton = new QPushButton("Dodaj kierowcę", this);
    layout->addWidget(addDriverButton);
    connect(addDriverButton, &QPushButton::clicked, this, &MainWindow::on_addDriverButton_clicked);

    QPushButton *editDriverButton = new QPushButton("Edytuj kierowcę", this);
    layout->addWidget(editDriverButton);
    connect(editDriverButton, &QPushButton::clicked, this, &MainWindow::on_editDriverButton_clicked);

    QPushButton *deleteDriverButton = new QPushButton("Usuń kierowcę", this);
    layout->addWidget(deleteDriverButton);
    connect(deleteDriverButton, &QPushButton::clicked, this, &MainWindow::on_deleteDriverButton_clicked);

    QPushButton *clearDriverSelectionButton = new QPushButton("Odznacz kierowcę", this);
    layout->addWidget(clearDriverSelectionButton);
    connect(clearDriverSelectionButton, &QPushButton::clicked, this, &MainWindow::on_clearDriverSelection_clicked);

    //
    // 3. Sekcja Samochodów
    //
    carListWidget = new QListWidget(this);
    layout->addWidget(carListWidget);

    QPushButton *addCarButton = new QPushButton("Dodaj samochód", this);
    layout->addWidget(addCarButton);
    connect(addCarButton, &QPushButton::clicked, this, &MainWindow::on_addCarButton_clicked);

    QPushButton *searchCarButton = new QPushButton("Szukaj samochodu", this);
    layout->addWidget(searchCarButton);
    connect(searchCarButton, &QPushButton::clicked, this, &MainWindow::on_searchCarButton_clicked);

    QPushButton *editCarButton = new QPushButton("Edytuj samochód", this);
    layout->addWidget(editCarButton);
    connect(editCarButton, &QPushButton::clicked, this, &MainWindow::on_editCarButton_clicked);

    QPushButton *deleteCarButton = new QPushButton("Usuń samochód", this);
    layout->addWidget(deleteCarButton);
    connect(deleteCarButton, &QPushButton::clicked, this, &MainWindow::on_deleteCarButton_clicked);

    //
    // 4. Sekcja wypożyczania/zwrotów
    //
    QPushButton *rentButton = new QPushButton("Wypożycz", this);
    layout->addWidget(rentButton);
    connect(rentButton, &QPushButton::clicked, this, &MainWindow::on_rentButton_clicked);

    QPushButton *returnButton = new QPushButton("Zwróć", this);
    layout->addWidget(returnButton);
    connect(returnButton, &QPushButton::clicked, this, &MainWindow::on_returnButton_clicked);

    QPushButton *editRentalButton = new QPushButton("Edytuj wypożyczenie", this);
    layout->addWidget(editRentalButton);
    connect(editRentalButton, &QPushButton::clicked, this, &MainWindow::on_editWypozyczenieButton_clicked);

    //
    // 5. Edycja danych wypożyczalni
    //
    QPushButton *editWypozyczalniaButton = new QPushButton("Edytuj wypożyczalnię", this);
    layout->addWidget(editWypozyczalniaButton);
    connect(editWypozyczalniaButton, &QPushButton::clicked, this, &MainWindow::on_editRentalButton_clicked);

    // Kontener
    QWidget *container = new QWidget;
    container->setLayout(layout);
    setCentralWidget(container);

    // SINGLETON
    RentalManager::instance().initializeData();

    // Zaktualizuj listy
    updatePersonList();
    updateDriverList();
    updateCarList();
}

//
// 1. Osoby (slots)
//
void MainWindow::on_addPersonButton_clicked() {
    // Dodajemy do Singletona
    Osoba::dodajOsobe(RentalManager::instance().osoby);
    updatePersonList();
}

void MainWindow::on_searchPersonButton_clicked() {
    auto &osoby = RentalManager::instance().osoby;
    if (osoby.empty()) {
        QMessageBox::information(this, "Brak danych", "Lista osób jest pusta.");
        return;
    }
    osoby.front().szukajOsobe(osoby);
}

void MainWindow::on_editPersonButton_clicked() {
    QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
    if (!selectedPersonItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz osobę z listy."));
        return;
    }
    auto &osoby = RentalManager::instance().osoby;
    int personIndex = personListWidget->row(selectedPersonItem);
    osoby[personIndex].edytujOsobe();
    updatePersonList();
}

void MainWindow::on_deletePersonButton_clicked() {
    QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
    if (!selectedPersonItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz osobę z listy."));
        return;
    }
    auto &osoby = RentalManager::instance().osoby;
    int personIndex = personListWidget->row(selectedPersonItem);
    osoby[personIndex].usunOsobe(osoby);
    updatePersonList();
}

void MainWindow::on_clearPersonSelection_clicked() {
    personListWidget->clearSelection();
    personListWidget->setCurrentItem(nullptr);
}

//
// 2. Kierowcy (slots)
//
void MainWindow::on_addDriverButton_clicked() {
    Kierowca::dodajKierowce(RentalManager::instance().kierowcy);
    updateDriverList();
}

void MainWindow::on_editDriverButton_clicked() {
    QListWidgetItem *selectedDriverItem = driverListWidget->currentItem();
    if (!selectedDriverItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz kierowcę z listy."));
        return;
    }
    auto &kierowcy = RentalManager::instance().kierowcy;
    int driverIndex = driverListWidget->row(selectedDriverItem);
    kierowcy[driverIndex].edytujKierowce();
    updateDriverList();
}

void MainWindow::on_deleteDriverButton_clicked() {
    QListWidgetItem *selectedDriverItem = driverListWidget->currentItem();
    if (!selectedDriverItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz kierowcę z listy."));
        return;
    }
    auto &kierowcy = RentalManager::instance().kierowcy;
    int driverIndex = driverListWidget->row(selectedDriverItem);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Usuń kierowcę",
                                  "Czy na pewno chcesz usunąć tego kierowcę?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        kierowcy.erase(kierowcy.begin() + driverIndex);
        QMessageBox::information(this, "Usuń kierowcę",
                                 "Kierowca został usunięty.");
    }
    updateDriverList();
}

void MainWindow::on_clearDriverSelection_clicked() {
    driverListWidget->clearSelection();
    driverListWidget->setCurrentItem(nullptr);
}

//
// 3. Samochody (slots)
//
void MainWindow::on_addCarButton_clicked() {
    Samochod::dodajSamochod(RentalManager::instance().samochody);
    updateCarList();
}

void MainWindow::on_searchCarButton_clicked() {
    auto &samochody = RentalManager::instance().samochody;
    if (samochody.empty()) {
        QMessageBox::information(this, "Brak danych", "Lista samochodów jest pusta.");
        return;
    }
    samochody.front().szukajSamochod(samochody);
}

void MainWindow::on_editCarButton_clicked() {
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }
    auto &samochody = RentalManager::instance().samochody;
    int carIndex = carListWidget->row(selectedCarItem);
    samochody[carIndex].edytujSamochod();
    updateCarList();
}

void MainWindow::on_deleteCarButton_clicked() {
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }
    auto &samochody = RentalManager::instance().samochody;
    int carIndex = carListWidget->row(selectedCarItem);
    samochody[carIndex].usunSamochod(samochody);
    updateCarList();
}

//
// 4. Wypożyczanie i zwrot
//
void MainWindow::on_rentButton_clicked() {
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }

    QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
    QListWidgetItem *selectedDriverItem = driverListWidget->currentItem();

    bool osobaSelected = (selectedPersonItem != nullptr);
    bool kierowcaSelected = (selectedDriverItem != nullptr);

    if (osobaSelected && kierowcaSelected) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Wybierz tylko jedną opcję: albo osobę, albo kierowcę."));
        return;
    }

    if (!osobaSelected && !kierowcaSelected) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Musisz wybrać osobę lub kierowcę."));
        return;
    }

    auto &samochody = RentalManager::instance().samochody;
    auto &osoby = RentalManager::instance().osoby;
    auto &kierowcy = RentalManager::instance().kierowcy;
    auto &wypozyczenia = RentalManager::instance().wypozyczenia;

    int carIndex = carListWidget->row(selectedCarItem);
    QString carDetails = selectedCarItem->text();

    // Sprawdź, czy już wynajęty
    auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                           [&](const Wypozyczenie &w) {
        return carToString(w.samochod) == carDetails;
    });
    if (it != wypozyczenia.end()) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Ten samochód jest już wynajęty."));
        return;
    }

    // Daty
    QString startStr = QInputDialog::getText(this, "Data rozpoczęcia",
                                             "Podaj datę rozpoczęcia (YYYY-MM-DD):");
    QDate startDate = QDate::fromString(startStr, "yyyy-MM-dd");
    if (!startDate.isValid()) {
        QMessageBox::warning(this, tr("Błąd"), tr("Niepoprawna data rozpoczęcia."));
        return;
    }

    QString endStr = QInputDialog::getText(this, "Data zakończenia",
                                           "Podaj datę zakończenia (YYYY-MM-DD):");
    QDate endDate = QDate::fromString(endStr, "yyyy-MM-dd");
    if (!endDate.isValid() || endDate < startDate) {
        QMessageBox::warning(this, tr("Błąd"), tr("Niepoprawna data zakończenia."));
        return;
    }

    QStringList insuranceOptions;
    insuranceOptions << "Tak" << "Nie";
    bool ok;
    QString insuranceChoice = QInputDialog::getItem(
        this, "Ubezpieczenie dodatkowe",
        "Czy chcesz ubezpieczenie dodatkowe?",
        insuranceOptions, 0, false, &ok
    );
    if (!ok) return;
    bool additionalInsurance = (insuranceChoice == "Tak");

    if (osobaSelected) {
        int personIndex = personListWidget->row(selectedPersonItem);
        Wypozyczenie w(osoby[personIndex], samochody[carIndex],
                       QDateTime(startDate), QDateTime(endDate),
                       additionalInsurance);
        wypozyczenia.push_back(w);

        QMessageBox::information(
            this, tr("Wynajem samochodu"),
            tr("Wynajęto samochód dla: %1 %2\nSamochód: %3\nUbezpieczenie dodatkowe: %4")
                .arg(osoby[personIndex].imie)
                .arg(osoby[personIndex].nazwisko)
                .arg(carDetails)
                .arg(additionalInsurance ? "Tak" : "Nie")
        );
    } else {
        int driverIndex = driverListWidget->row(selectedDriverItem);
        Wypozyczenie w(kierowcy[driverIndex], samochody[carIndex],
                       QDateTime(startDate), QDateTime(endDate),
                       additionalInsurance);
        wypozyczenia.push_back(w);

        QMessageBox::information(
            this, tr("Wynajem samochodu"),
            tr("Wynajęto samochód dla: %1 %2 (Kierowca)\nSamochód: %3\nUbezpieczenie dodatkowe: %4")
                .arg(kierowcy[driverIndex].imie)
                .arg(kierowcy[driverIndex].nazwisko)
                .arg(carDetails)
                .arg(additionalInsurance ? "Tak" : "Nie")
        );
    }

    // Oznacz wypożyczony (szare tło)
    selectedCarItem->setBackground(Qt::lightGray);
}

void MainWindow::on_returnButton_clicked() {
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }

    QString carDetails = selectedCarItem->text();
    auto &wypozyczenia = RentalManager::instance().wypozyczenia;

    // Szukamy wypożyczenia
    auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                           [&](const Wypozyczenie &w) {
        return carToString(w.samochod) == carDetails;
    });

    if (it == wypozyczenia.end()) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Ten samochód nie jest wynajęty."));
        return;
    }

    wypozyczenia.erase(it);
    selectedCarItem->setBackground(Qt::transparent);

    QMessageBox::information(this, tr("Zwrot samochodu"),
                             tr("Zwrócono samochód: %1").arg(carDetails));
}

void MainWindow::on_editWypozyczenieButton_clicked() {
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }

    QString carDetails = selectedCarItem->text();
    auto &wypozyczenia = RentalManager::instance().wypozyczenia;

    auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                           [&](Wypozyczenie &w) {
        return carToString(w.samochod) == carDetails;
    });

    if (it == wypozyczenia.end()) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Ten samochód nie jest wynajęty."));
        return;
    }

    it->edytujWypozyczenie();
}

void MainWindow::on_editRentalButton_clicked() {
    // Edytuj obiekt wypożyczalni
    wypozyczalnia.edytujWypozyczalnie();
    setWindowTitle(wypozyczalnia.nazwa + " - " + wypozyczalnia.adres);
}

//
// Metody do odświeżania list
//
void MainWindow::updatePersonList() {
    personListWidget->clear();
    auto &osoby = RentalManager::instance().osoby;
    for (const Osoba &osoba : osoby) {
        personListWidget->addItem(osoba.imie + " " + osoba.nazwisko);
    }
}

void MainWindow::updateDriverList() {
    driverListWidget->clear();
    auto &kierowcy = RentalManager::instance().kierowcy;
    for (const Kierowca &k : kierowcy) {
        driverListWidget->addItem(k.imie + " " + k.nazwisko + " | PJ: " + k.prawoJazdy);
    }
}

void MainWindow::updateCarList() {
    carListWidget->clear();
    auto &samochody = RentalManager::instance().samochody;
    auto &wypozyczenia = RentalManager::instance().wypozyczenia;

    for (const auto &s : samochody) {
        QListWidgetItem *item = new QListWidgetItem(carToString(s), carListWidget);

        // Sprawdzamy, czy samochód jest aktualnie wynajęty
        auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                               [&](const Wypozyczenie &w) {
            return carToString(w.samochod) == carToString(s);
        });
        if (it != wypozyczenia.end()) {
            item->setBackground(Qt::lightGray);
        }
    }
}

QString MainWindow::carToString(const Samochod &samochod) {
    return QString("%1 %2 (%3) (%4) %5 %6")
        .arg(QString::fromStdString(samochod.marka))
        .arg(QString::fromStdString(samochod.model))
        .arg(samochod.rokProdukcji)
        .arg(samochod.przebieg)
        .arg(QString::fromStdString(samochod.vin))
        .arg(QString::fromStdString(samochod.rejestracja));
}
