#include "MainWindow.h"

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
    // Główny layout dla centralnego widgetu
    QVBoxLayout *layout = new QVBoxLayout;

    // Ustaw tytuł okna (na podstawie nazwy wypożyczalni)
    setWindowTitle(wypozyczalnia.nazwa + " - " + wypozyczalnia.adres);

    //
    // 1. Sekcja Osób (QListWidget + przyciski)
    //
    personListWidget = new QListWidget(this);
    layout->addWidget(personListWidget);

    QPushButton *addPersonButton = new QPushButton("Dodaj osobę", this);
    layout->addWidget(addPersonButton);
    connect(addPersonButton, &QPushButton::clicked,
            this, &MainWindow::on_addPersonButton_clicked);

    QPushButton *searchPersonButton = new QPushButton("Szukaj osoby", this);
    layout->addWidget(searchPersonButton);
    connect(searchPersonButton, &QPushButton::clicked,
            this, &MainWindow::on_searchPersonButton_clicked);

    QPushButton *editPersonButton = new QPushButton("Edytuj osobę", this);
    layout->addWidget(editPersonButton);
    connect(editPersonButton, &QPushButton::clicked,
            this, &MainWindow::on_editPersonButton_clicked);

    QPushButton *deletePersonButton = new QPushButton("Usuń osobę", this);
    layout->addWidget(deletePersonButton);
    connect(deletePersonButton, &QPushButton::clicked,
            this, &MainWindow::on_deletePersonButton_clicked);

    QPushButton *clearPersonSelectionButton = new QPushButton("Odznacz osobę", this);
    layout->addWidget(clearPersonSelectionButton);
    connect(clearPersonSelectionButton, &QPushButton::clicked,
            this, &MainWindow::on_clearPersonSelection_clicked);

    //
    // 2. Sekcja Kierowców (QListWidget + przyciski)
    //
    driverListWidget = new QListWidget(this);
    layout->addWidget(driverListWidget);

    QPushButton *addDriverButton = new QPushButton("Dodaj kierowcę", this);
    layout->addWidget(addDriverButton);
    connect(addDriverButton, &QPushButton::clicked,
            this, &MainWindow::on_addDriverButton_clicked);

    QPushButton *editDriverButton = new QPushButton("Edytuj kierowcę", this);
    layout->addWidget(editDriverButton);
    connect(editDriverButton, &QPushButton::clicked,
            this, &MainWindow::on_editDriverButton_clicked);

    QPushButton *deleteDriverButton = new QPushButton("Usuń kierowcę", this);
    layout->addWidget(deleteDriverButton);
    connect(deleteDriverButton, &QPushButton::clicked,
            this, &MainWindow::on_deleteDriverButton_clicked);

    QPushButton *clearDriverSelectionButton = new QPushButton("Odznacz kierowcę", this);
    layout->addWidget(clearDriverSelectionButton);
    connect(clearDriverSelectionButton, &QPushButton::clicked,
            this, &MainWindow::on_clearDriverSelection_clicked);

    //
    // 3. Sekcja Samochodów (QListWidget + przyciski)
    //
    carListWidget = new QListWidget(this);
    layout->addWidget(carListWidget);

    QPushButton *addCarButton = new QPushButton("Dodaj samochód", this);
    layout->addWidget(addCarButton);
    connect(addCarButton, &QPushButton::clicked,
            this, &MainWindow::on_addCarButton_clicked);

    QPushButton *searchCarButton = new QPushButton("Szukaj samochodu", this);
    layout->addWidget(searchCarButton);
    connect(searchCarButton, &QPushButton::clicked,
            this, &MainWindow::on_searchCarButton_clicked);

    QPushButton *editCarButton = new QPushButton("Edytuj samochód", this);
    layout->addWidget(editCarButton);
    connect(editCarButton, &QPushButton::clicked,
            this, &MainWindow::on_editCarButton_clicked);

    QPushButton *deleteCarButton = new QPushButton("Usuń samochód", this);
    layout->addWidget(deleteCarButton);
    connect(deleteCarButton, &QPushButton::clicked,
            this, &MainWindow::on_deleteCarButton_clicked);

    //
    // 4. Sekcja wypożyczania/zwrotów (przyciski)
    //
    QPushButton *rentButton = new QPushButton("Wypożycz", this);
    layout->addWidget(rentButton);
    connect(rentButton, &QPushButton::clicked,
            this, &MainWindow::on_rentButton_clicked);

    QPushButton *returnButton = new QPushButton("Zwróć", this);
    layout->addWidget(returnButton);
    connect(returnButton, &QPushButton::clicked,
            this, &MainWindow::on_returnButton_clicked);

    // Nowy przycisk do edycji wypożyczenia
    QPushButton *editRentalButton = new QPushButton("Edytuj wypożyczenie", this);
    layout->addWidget(editRentalButton);
    connect(editRentalButton, &QPushButton::clicked,
            this, &MainWindow::on_editWypozyczenieButton_clicked);

    //
    // 5. Edycja danych wypożyczalni
    //
    QPushButton *editWypozyczalniaButton = new QPushButton("Edytuj wypożyczalnię", this);
    layout->addWidget(editWypozyczalniaButton);
    connect(editWypozyczalniaButton, &QPushButton::clicked,
            this, &MainWindow::on_editRentalButton_clicked);

    // Dodanie wszystkiego do centralnego widgetu
    QWidget *container = new QWidget;
    container->setLayout(layout);
    setCentralWidget(container);

    // Inicjalizacja przykładowych danych i aktualizacja widoków
    initializeData();
    updatePersonList();
    updateDriverList();
    updateCarList();
}

//
// Metoda inicjalizująca przykładowe dane.
//
void MainWindow::initializeData()
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

//
// Sloty związane z Osobami
//
void MainWindow::on_addPersonButton_clicked()
{
    Osoba::dodajOsobe(osoby);
    updatePersonList();
}

void MainWindow::on_searchPersonButton_clicked()
{
    if (osoby.empty()) {
        QMessageBox::information(this, "Brak danych", "Lista osób jest pusta.");
        return;
    }
    // Wyszukiwanie robi metoda w klasie Osoba, np. osoby.front().szukajOsobe()
    // aby skorzystać z QInputDialog:
    osoby.front().szukajOsobe(osoby);
}

void MainWindow::on_editPersonButton_clicked()
{
    QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
    if (!selectedPersonItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz osobę z listy."));
        return;
    }
    int personIndex = personListWidget->row(selectedPersonItem);
    osoby[personIndex].edytujOsobe();
    updatePersonList();
}

void MainWindow::on_deletePersonButton_clicked()
{
    QListWidgetItem *selectedPersonItem = personListWidget->currentItem();
    if (!selectedPersonItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz osobę z listy."));
        return;
    }
    int personIndex = personListWidget->row(selectedPersonItem);
    osoby[personIndex].usunOsobe(osoby);
    updatePersonList();
}

void MainWindow::on_clearPersonSelection_clicked()
{
    personListWidget->clearSelection();
    personListWidget->setCurrentItem(nullptr);  // brak zaznaczenia
}

//
// Sloty związane z Kierowcami
//
void MainWindow::on_addDriverButton_clicked()
{
    Kierowca::dodajKierowce(kierowcy);
    updateDriverList();
}

void MainWindow::on_editDriverButton_clicked()
{
    QListWidgetItem *selectedDriverItem = driverListWidget->currentItem();
    if (!selectedDriverItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz kierowcę z listy."));
        return;
    }
    int driverIndex = driverListWidget->row(selectedDriverItem);
    kierowcy[driverIndex].edytujKierowce();
    updateDriverList();
}

void MainWindow::on_deleteDriverButton_clicked()
{
    QListWidgetItem *selectedDriverItem = driverListWidget->currentItem();
    if (!selectedDriverItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz kierowcę z listy."));
        return;
    }
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

void MainWindow::on_clearDriverSelection_clicked()
{
    driverListWidget->clearSelection();
    driverListWidget->setCurrentItem(nullptr);
}

//
// Sloty związane z Samochodami
//
void MainWindow::on_addCarButton_clicked()
{
    Samochod::dodajSamochod(samochody);
    updateCarList();
}

void MainWindow::on_searchCarButton_clicked()
{
    if (samochody.empty()) {
        QMessageBox::information(this, "Brak danych", "Lista samochodów jest pusta.");
        return;
    }
    // Analogicznie jak przy osobach, metoda w klasie Samochod
    samochody.front().szukajSamochod(samochody);
}

void MainWindow::on_editCarButton_clicked()
{
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }
    int carIndex = carListWidget->row(selectedCarItem);
    samochody[carIndex].edytujSamochod();
    updateCarList();
}

void MainWindow::on_deleteCarButton_clicked()
{
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }
    int carIndex = carListWidget->row(selectedCarItem);
    samochody[carIndex].usunSamochod(samochody);
    updateCarList();
}

//
// Sloty wypożyczania i zwrotu
//
void MainWindow::on_rentButton_clicked()
{
    // Musimy mieć wybrany samochód i osobę LUB kierowcę (ale nie obie naraz).
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

    // Indeks samochodu
    int carIndex = carListWidget->row(selectedCarItem);

    // Sprawdź, czy samochód nie jest już wynajęty
    QString carDetails = selectedCarItem->text();
    auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                           [&](const Wypozyczenie &w) {
        return carToString(w.samochod) == carDetails;
    });
    if (it != wypozyczenia.end()) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Ten samochód jest już wynajęty."));
        return;
    }

    // Pytamy o daty wypożyczenia
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

    // Pytamy o ubezpieczenie dodatkowe
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

    // Tworzymy Wypozyczenie
    if (osobaSelected) {
        int personIndex = personListWidget->row(selectedPersonItem);
        Wypozyczenie w(osoby[personIndex],
                       samochody[carIndex],
                       QDateTime(startDate),
                       QDateTime(endDate),
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
    } else { // kierowcaSelected
        int driverIndex = driverListWidget->row(selectedDriverItem);
        Wypozyczenie w(kierowcy[driverIndex],
                       samochody[carIndex],
                       QDateTime(startDate),
                       QDateTime(endDate),
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

    // Oznacz samochód w liście jako wypożyczony (np. szarym tłem)
    selectedCarItem->setBackground(Qt::lightGray);
}

void MainWindow::on_returnButton_clicked()
{
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }

    QString carDetails = selectedCarItem->text();

    // Znajdź wypożyczenie pasujące do tego samochodu
    auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                           [&](const Wypozyczenie &w) {
        return carToString(w.samochod) == carDetails;
    });

    if (it == wypozyczenia.end()) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Ten samochód nie jest wynajęty."));
        return;
    }

    // Usuwamy z vectora wypożyczeń
    wypozyczenia.erase(it);

    // Przywracamy wygląd samochodu
    selectedCarItem->setBackground(Qt::transparent);

    QMessageBox::information(this, tr("Zwrot samochodu"),
                             tr("Zwrócono samochód: %1").arg(carDetails));
}

void MainWindow::on_editWypozyczenieButton_clicked()
{
    // Edytujemy istniejące wypożyczenie powiązane z wybranym samochodem
    QListWidgetItem *selectedCarItem = carListWidget->currentItem();
    if (!selectedCarItem) {
        QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
        return;
    }

    QString carDetails = selectedCarItem->text();

    // Znajdź to wypożyczenie
    auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                           [&](Wypozyczenie &w) {
        return carToString(w.samochod) == carDetails;
    });

    if (it == wypozyczenia.end()) {
        QMessageBox::warning(this, tr("Błąd"),
                             tr("Ten samochód nie jest wynajęty."));
        return;
    }

    // Wywołaj metodę edytującą
    it->edytujWypozyczenie();
}

void MainWindow::on_editRentalButton_clicked()
{
    // Edycja danych obiektu klasy Wypozyczalnia
    wypozyczalnia.edytujWypozyczalnie();
    // Zaktualizuj tytuł okna
    setWindowTitle(wypozyczalnia.nazwa + " - " + wypozyczalnia.adres);
}

//
// Metody pomocnicze do odświeżania list
//
void MainWindow::updatePersonList()
{
    personListWidget->clear();
    for (const Osoba &osoba : osoby) {
        personListWidget->addItem(osoba.imie + " " + osoba.nazwisko);
    }
}

void MainWindow::updateDriverList()
{
    driverListWidget->clear();
    for (const Kierowca &k : kierowcy) {
        // Wyświetlamy imię, nazwisko oraz np. numer prawa jazdy
        driverListWidget->addItem(k.imie + " " + k.nazwisko + " | PJ: " + k.prawoJazdy);
    }
}

void MainWindow::updateCarList()
{
    carListWidget->clear();
    for (const auto &samochod : samochody) {
        QListWidgetItem *item = new QListWidgetItem(carToString(samochod), carListWidget);

        // Jeśli ten samochód jest obecnie wynajęty, oznacz go w liście
        auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(),
                               [&](const Wypozyczenie &w) {
            return carToString(w.samochod) == item->text();
        });
        if (it != wypozyczenia.end()) {
            item->setBackground(Qt::lightGray);
        }
    }
}

//
// Metoda formatująca informacje o samochodzie
//
QString MainWindow::carToString(const Samochod &samochod)
{
    return QString("%1 %2 (%3) (%4) %5 %6")
        .arg(QString::fromStdString(samochod.marka))
        .arg(QString::fromStdString(samochod.model))
        .arg(samochod.rokProdukcji)
        .arg(samochod.przebieg)
        .arg(QString::fromStdString(samochod.vin))
        .arg(QString::fromStdString(samochod.rejestracja));
}
