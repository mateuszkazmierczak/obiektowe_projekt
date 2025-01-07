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
#include <algorithm>

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
    QDateTime dataUzyskaniaPrawaJazdy;

    Kierowca(QString i, QString n, QDateTime d, QString p, QDateTime u)
        : Osoba(i, n, d), prawoJazdy(p), dataUzyskaniaPrawaJazdy(u) {}

    void edytujKierowce() {
        edytujOsobe();
        QString newPrawoJazdy = QInputDialog::getText(nullptr, "Edytuj kierowcę", "Nowy numer prawa jazdy:", QLineEdit::Normal, prawoJazdy);
        QString newDataUzyskaniaStr = QInputDialog::getText(nullptr, "Edytuj kierowcę", "Data uzyskania prawa jazdy (YYYY-MM-DD):", QLineEdit::Normal, dataUzyskaniaPrawaJazdy.toString("yyyy-MM-dd"));
        QDate newDataUzyskania = QDate::fromString(newDataUzyskaniaStr, "yyyy-MM-dd");
        if (!newPrawoJazdy.isEmpty() && newDataUzyskania.isValid()) {
            prawoJazdy = newPrawoJazdy;
            dataUzyskaniaPrawaJazdy = QDateTime(newDataUzyskania);
            QMessageBox::information(nullptr, "Edytuj kierowcę", "Dane kierowcy zostały zaktualizowane.");
        }
    }

    static void dodajKierowce(vector<Kierowca> &kierowcy) {
        QString newImie = QInputDialog::getText(nullptr, "Dodaj kierowcę", "Imię:");
        if (newImie.isEmpty()) return;

        QString newNazwisko = QInputDialog::getText(nullptr, "Dodaj kierowcę", "Nazwisko:");
        if (newNazwisko.isEmpty()) return;

        QDate newDataUrodzenia = QDate::fromString(QInputDialog::getText(nullptr, "Dodaj kierowcę", "Data urodzenia (YYYY-MM-DD):"), "yyyy-MM-dd");
        if (!newDataUrodzenia.isValid()) {
            QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data urodzenia.");
            return;
        }

        QString newPrawoJazdy = QInputDialog::getText(nullptr, "Dodaj kierowcę", "Numer prawa jazdy:");
        if (newPrawoJazdy.isEmpty()) return;

        QDate newDataUzyskania = QDate::fromString(QInputDialog::getText(nullptr, "Dodaj kierowcę", "Data uzyskania prawa jazdy (YYYY-MM-DD):"), "yyyy-MM-dd");
        if (!newDataUzyskania.isValid()) {
            QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data uzyskania prawa jazdy.");
            return;
        }

        kierowcy.push_back(Kierowca(newImie, newNazwisko, QDateTime(newDataUrodzenia), newPrawoJazdy, QDateTime(newDataUzyskania)));
        QMessageBox::information(nullptr, "Dodaj kierowcę", "Nowy kierowca został dodany.");
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

    Samochod(string m, string mo, int r, int p, string v, string re)
        : marka(m), model(mo), rokProdukcji(r), przebieg(p), vin(v), rejestracja(re) {}

    void edytujSamochod() {
        QString newMarka = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowa marka:", QLineEdit::Normal, QString::fromStdString(marka));
        QString newModel = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy model:", QLineEdit::Normal, QString::fromStdString(model));
        QString newRokProdukcji = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy rok produkcji:", QLineEdit::Normal, QString::number(rokProdukcji));
        QString newPrzebieg = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy przebieg:", QLineEdit::Normal, QString::number(przebieg));
        QString newVin = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy VIN:", QLineEdit::Normal, QString::fromStdString(vin));
        QString newRejestracja = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowa rejestracja:", QLineEdit::Normal, QString::fromStdString(rejestracja));

        if (!newMarka.isEmpty() && !newModel.isEmpty() && !newRokProdukcji.isEmpty() && !newPrzebieg.isEmpty() && !newVin.isEmpty() && !newRejestracja.isEmpty()) {
            marka = newMarka.toStdString();
            model = newModel.toStdString();
            rokProdukcji = newRokProdukcji.toInt();
            przebieg = newPrzebieg.toInt();
            vin = newVin.toStdString();
            rejestracja = newRejestracja.toStdString();
            QMessageBox::information(nullptr, "Edytuj samochód", "Dane samochodu zostały zaktualizowane.");
        }
    }

    void usunSamochod(vector<Samochod> &samochody) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Usuń samochód", "Czy na pewno chcesz usunąć ten samochód?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            auto it = std::find_if(samochody.begin(), samochody.end(), [this](const Samochod &s) {
                return s.marka == this->marka && s.model == this->model && s.rokProdukcji == this->rokProdukcji;
            });
            if (it != samochody.end()) {
                samochody.erase(it);
                QMessageBox::information(nullptr, "Usuń samochód", "Samochód został usunięty.");
            }
        }
    }

    static void dodajSamochod(vector<Samochod> &samochody) {
        QString newMarka = QInputDialog::getText(nullptr, "Dodaj samochód", "Marka:");
        if (newMarka.isEmpty()) return;

        QString newModel = QInputDialog::getText(nullptr, "Dodaj samochód", "Model:");
        if (newModel.isEmpty()) return;

        QString newRokProdukcji = QInputDialog::getText(nullptr, "Dodaj samochód", "Rok produkcji:");
        if (newRokProdukcji.isEmpty()) return;

        QString newPrzebieg = QInputDialog::getText(nullptr, "Dodaj samochód", "Przebieg:");
        if (newPrzebieg.isEmpty()) return;

        QString newVin = QInputDialog::getText(nullptr, "Dodaj samochód", "VIN:");
        if (newVin.isEmpty()) return;

        QString newRejestracja = QInputDialog::getText(nullptr, "Dodaj samochód", "Rejestracja:");
        if (newRejestracja.isEmpty()) return;

        samochody.push_back(Samochod(newMarka.toStdString(), newModel.toStdString(), newRokProdukcji.toInt(), newPrzebieg.toInt(), newVin.toStdString(), newRejestracja.toStdString()));
        QMessageBox::information(nullptr, "Dodaj samochód", "Nowy samochód został dodany.");
    }

    void szukajSamochod(vector<Samochod> &samochody) {
        QString searchMarka = QInputDialog::getText(nullptr, "Szukaj samochodu", "Podaj markę:");
        if (!searchMarka.isEmpty()) {
            for (const auto &samochod : samochody) {
                if (QString::fromStdString(samochod.marka) == searchMarka) {
                    QMessageBox::information(nullptr, "Wynik wyszukiwania", "Znaleziono samochód: " + QString::fromStdString(samochod.marka) + " " + QString::fromStdString(samochod.model));
                    return;
                }
            }
            QMessageBox::information(nullptr, "Wynik wyszukiwania", "Nie znaleziono samochodu o marce: " + searchMarka);
        }
    }
};

class Wypozyczalnia {
public:
    QString nazwa;
    QString adres;

    Wypozyczalnia(QString n, QString a) : nazwa(n), adres(a) {}
    virtual ~Wypozyczalnia() = default;

    virtual void edytujWypozyczalnie() {
        QString newNazwa = QInputDialog::getText(nullptr, "Edytuj wypożyczalnię", "Nowa nazwa:", QLineEdit::Normal, nazwa);
        QString newAdres = QInputDialog::getText(nullptr, "Edytuj wypożyczalnię", "Nowy adres:", QLineEdit::Normal, adres);
        if (!newNazwa.isEmpty() && !newAdres.isEmpty()) {
            nazwa = newNazwa;
            adres = newAdres;
            QMessageBox::information(nullptr, "Edytuj wypożyczalnię", "Dane wypożyczalni zostały zaktualizowane.");
        }
    }
};

class Wypozyczenie {
public:
    Osoba osoba;
    Samochod samochod;
    QDateTime dataStart;
    QDateTime dataEnd;
    bool additionalInsurance;

    Wypozyczenie(const Osoba &o, const Samochod &s, const QDateTime &start, const QDateTime &end, bool insurance)
        : osoba(o), samochod(s), dataStart(start), dataEnd(end), additionalInsurance(insurance) {}

    void edytujWypozyczenie() {
        // Prompt for new start date
        QString startStr = QInputDialog::getText(nullptr, "Edytuj wypożyczenie", "Nowa data rozpoczęcia (YYYY-MM-DD):", QLineEdit::Normal, dataStart.date().toString("yyyy-MM-dd"));
        QDate newStartDate = QDate::fromString(startStr, "yyyy-MM-dd");
        if (!newStartDate.isValid()) {
            QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data rozpoczęcia.");
            return;
        }

        // Prompt for new end date
        QString endStr = QInputDialog::getText(nullptr, "Edytuj wypożyczenie", "Nowa data zakończenia (YYYY-MM-DD):", QLineEdit::Normal, dataEnd.date().toString("yyyy-MM-dd"));
        QDate newEndDate = QDate::fromString(endStr, "yyyy-MM-dd");
        if (!newEndDate.isValid() || newEndDate < newStartDate) {
            QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data zakończenia.");
            return;
        }

        // Prompt for new insurance option
        QStringList insuranceOptions;
        insuranceOptions << "Tak" << "Nie";
        bool ok;
        QString currentInsurance = additionalInsurance ? "Tak" : "Nie";
        QString insuranceChoice = QInputDialog::getItem(nullptr, "Edytuj wypożyczenie", "Ubezpieczenie dodatkowe:", insuranceOptions, insuranceOptions.indexOf(currentInsurance), false, &ok);
        if (!ok) return;
        bool newInsurance = (insuranceChoice == "Tak");

        // Update fields
        dataStart = QDateTime(newStartDate);
        dataEnd = QDateTime(newEndDate);
        additionalInsurance = newInsurance;

        QMessageBox::information(nullptr, "Edytuj wypożyczenie", "Dane wypożyczenia zostały zaktualizowane.");
    }
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent), wypozyczalnia("Domyślna Wypożyczalnia", "Domyślny Adres") {
        QVBoxLayout *layout = new QVBoxLayout;

        setWindowTitle(wypozyczalnia.nazwa + " - " + wypozyczalnia.adres);

        // Person list widgets
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

        // Driver list widgets
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

        // Car list widgets
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

        // rental and return buttons
        QPushButton *rentButton = new QPushButton("Wypożycz", this);
        layout->addWidget(rentButton);
        connect(rentButton, &QPushButton::clicked, this, &MainWindow::on_rentButton_clicked);

        QPushButton *returnButton = new QPushButton("Zwróć", this);
        layout->addWidget(returnButton);
        connect(returnButton, &QPushButton::clicked, this, &MainWindow::on_returnButton_clicked);

        // New: Edit rental button
        QPushButton *editRentalButton = new QPushButton("Edytuj wypożyczenie", this);
        layout->addWidget(editRentalButton);
        connect(editRentalButton, &QPushButton::clicked, this, &MainWindow::on_editWypozyczenieButton_clicked);

        // Edit rental place (wypożyczalnia)
        QPushButton *editWypozyczalniaButton = new QPushButton("Edytuj wypożyczalnię", this);
        layout->addWidget(editWypozyczalniaButton);
        connect(editWypozyczalniaButton, &QPushButton::clicked, this, &MainWindow::on_editRentalButton_clicked);

        QWidget *container = new QWidget;
        container->setLayout(layout);
        setCentralWidget(container);

        // Initialize with some data
        initializeData();
        updatePersonList();
        updateDriverList();
        updateCarList();
    }

private slots:
    // Person slots
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

    void on_clearPersonSelection_clicked() {
        personListWidget->clearSelection();
        personListWidget->setCurrentItem(nullptr);  // ensures no current item
    }

    // Driver (Kierowca) slots
    void on_addDriverButton_clicked() {
        Kierowca::dodajKierowce(kierowcy);
        updateDriverList();
    }

    void on_editDriverButton_clicked() {
        QListWidgetItem *selectedDriverItem = driverListWidget->currentItem();
        if (!selectedDriverItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz kierowcę z listy."));
            return;
        }
        int driverIndex = driverListWidget->row(selectedDriverItem);
        kierowcy[driverIndex].edytujKierowce();
        updateDriverList();
    }

    void on_deleteDriverButton_clicked() {
        QListWidgetItem *selectedDriverItem = driverListWidget->currentItem();
        if (!selectedDriverItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz kierowcę z listy."));
            return;
        }
        int driverIndex = driverListWidget->row(selectedDriverItem);

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Usuń kierowcę", "Czy na pewno chcesz usunąć tego kierowcę?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            kierowcy.erase(kierowcy.begin() + driverIndex);
            QMessageBox::information(this, "Usuń kierowcę", "Kierowca został usunięty.");
        }
        updateDriverList();
    }

    void on_clearDriverSelection_clicked() {
        driverListWidget->clearSelection();
        driverListWidget->setCurrentItem(nullptr);  // ensures no current item
    }

    // Car slots
    void on_addCarButton_clicked() {
        Samochod::dodajSamochod(samochody);
        updateCarList();
    }

    void on_searchCarButton_clicked() {
        if (samochody.empty()) {
            QMessageBox::information(this, "Brak danych", "Lista samochodów jest pusta.");
            return;
        }
        samochody.front().szukajSamochod(samochody);
    }

    void on_editCarButton_clicked() {
        QListWidgetItem *selectedCarItem = carListWidget->currentItem();
        if (!selectedCarItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
            return;
        }
        int carIndex = carListWidget->row(selectedCarItem);
        samochody[carIndex].edytujSamochod();
        updateCarList();
    }

    void on_deleteCarButton_clicked() {
        QListWidgetItem *selectedCarItem = carListWidget->currentItem();
        if (!selectedCarItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
            return;
        }
        int carIndex = carListWidget->row(selectedCarItem);
        samochody[carIndex].usunSamochod(samochody);
        updateCarList();
    }

    // Rent and return
    void on_rentButton_clicked() {
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
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz tylko jedną opcję: albo osobę, albo kierowcę."));
            return;
        }

        if (!osobaSelected && !kierowcaSelected) {
            QMessageBox::warning(this, tr("Błąd"), tr("Musisz wybrać osobę lub kierowcę."));
            return;
        }

        int carIndex = carListWidget->row(selectedCarItem);

        // Check if already rented
        QString carDetails = selectedCarItem->text();
        auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(), [&](const Wypozyczenie &w) {
            return carToString(w.samochod) == carDetails;
        });
        if (it != wypozyczenia.end()) {
            QMessageBox::warning(this, tr("Błąd"), tr("Ten samochód jest już wynajęty."));
            return;
        }

        // Gather rental data
        QString startStr = QInputDialog::getText(this, "Data rozpoczęcia", "Podaj datę rozpoczęcia (YYYY-MM-DD):");
        QDate startDate = QDate::fromString(startStr, "yyyy-MM-dd");
        if (!startDate.isValid()) {
            QMessageBox::warning(this, tr("Błąd"), tr("Niepoprawna data rozpoczęcia."));
            return;
        }

        QString endStr = QInputDialog::getText(this, "Data zakończenia", "Podaj datę zakończenia (YYYY-MM-DD):");
        QDate endDate = QDate::fromString(endStr, "yyyy-MM-dd");
        if (!endDate.isValid() || endDate < startDate) {
            QMessageBox::warning(this, tr("Błąd"), tr("Niepoprawna data zakończenia."));
            return;
        }

        QStringList insuranceOptions;
        insuranceOptions << "Tak" << "Nie";
        bool ok;
        QString insuranceChoice = QInputDialog::getItem(this, "Ubezpieczenie dodatkowe", "Czy chcesz ubezpieczenie dodatkowe?", insuranceOptions, 0, false, &ok);
        if (!ok) return;

        bool additionalInsurance = (insuranceChoice == "Tak");

        if (osobaSelected) {
            int personIndex = personListWidget->row(selectedPersonItem);
            Wypozyczenie w(osoby[personIndex], samochody[carIndex], QDateTime(startDate), QDateTime(endDate), additionalInsurance);
            wypozyczenia.push_back(w);

            QMessageBox::information(this, tr("Wynajem samochodu"), tr("Wynajęto samochód dla: %1 %2\nSamochód: %3\nUbezpieczenie dodatkowe: %4")
                .arg(osoby[personIndex].imie)
                .arg(osoby[personIndex].nazwisko)
                .arg(carDetails)
                .arg(additionalInsurance ? "Tak" : "Nie"));
        } else {
            int driverIndex = driverListWidget->row(selectedDriverItem);
            Wypozyczenie w(kierowcy[driverIndex], samochody[carIndex], QDateTime(startDate), QDateTime(endDate), additionalInsurance);
            wypozyczenia.push_back(w);

            QMessageBox::information(this, tr("Wynajem samochodu"), tr("Wynajęto samochód dla: %1 %2 (Kierowca)\nSamochód: %3\nUbezpieczenie dodatkowe: %4")
                .arg(kierowcy[driverIndex].imie)
                .arg(kierowcy[driverIndex].nazwisko)
                .arg(carDetails)
                .arg(additionalInsurance ? "Tak" : "Nie"));
        }

        // Gray out the rented car
        selectedCarItem->setBackground(Qt::lightGray);
    }

    void on_returnButton_clicked() {
        QListWidgetItem *selectedCarItem = carListWidget->currentItem();
        if (!selectedCarItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
            return;
        }

        QString carDetails = selectedCarItem->text();

        // Find the rental
        auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(), [&](const Wypozyczenie &w) {
            return carToString(w.samochod) == carDetails;
        });

        if (it == wypozyczenia.end()) {
            QMessageBox::warning(this, tr("Błąd"), tr("Ten samochód nie jest wynajęty."));
            return;
        }

        // Return the car
        wypozyczenia.erase(it);

        // Enable the returned car
        selectedCarItem->setBackground(Qt::transparent);

        QMessageBox::information(this, tr("Zwrot samochodu"), tr("Zwrócono samochód: %1").arg(carDetails));
    }

    void on_editWypozyczenieButton_clicked() {
        QListWidgetItem *selectedCarItem = carListWidget->currentItem();
        if (!selectedCarItem) {
            QMessageBox::warning(this, tr("Błąd"), tr("Wybierz samochód z listy."));
            return;
        }

        QString carDetails = selectedCarItem->text();

        // Find the rental associated with this car
        auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(), [&](Wypozyczenie &w) {
            return carToString(w.samochod) == carDetails;
        });

        if (it == wypozyczenia.end()) {
            QMessageBox::warning(this, tr("Błąd"), tr("Ten samochód nie jest wynajęty."));
            return;
        }

        it->edytujWypozyczenie();
    }

    void on_editRentalButton_clicked() {
        wypozyczalnia.edytujWypozyczalnie();
        setWindowTitle(wypozyczalnia.nazwa + " - " + wypozyczalnia.adres);
    }

private:
    QListWidget *personListWidget;
    QListWidget *driverListWidget;
    QListWidget *carListWidget;
    vector<Osoba> osoby;
    vector<Kierowca> kierowcy;
    vector<Samochod> samochody;
    vector<Wypozyczenie> wypozyczenia;
    Wypozyczalnia wypozyczalnia;

    void updatePersonList() {
        personListWidget->clear();
        for (const Osoba &osoba : osoby) {
            personListWidget->addItem(osoba.imie + " " + osoba.nazwisko);
        }
    }

    void updateDriverList() {
        driverListWidget->clear();
        for (const Kierowca &k : kierowcy) {
            driverListWidget->addItem(k.imie + " " + k.nazwisko + " | PJ: " + k.prawoJazdy);
        }
    }

    void updateCarList() {
        carListWidget->clear();
        for (const auto &samochod : samochody) {
            QListWidgetItem *item = new QListWidgetItem(carToString(samochod), carListWidget);
            // Check if this car is currently rented
            auto it = std::find_if(wypozyczenia.begin(), wypozyczenia.end(), [&](const Wypozyczenie &w) {
                return carToString(w.samochod) == item->text();
            });
            if (it != wypozyczenia.end()) {
                item->setBackground(Qt::lightGray);
            }
        }
    }

    QString carToString(const Samochod &samochod) {
        return QString("%1 %2 (%3) (%4) %5 %6")
            .arg(QString::fromStdString(samochod.marka))
            .arg(QString::fromStdString(samochod.model))
            .arg(samochod.rokProdukcji)
            .arg(samochod.przebieg)
            .arg(QString::fromStdString(samochod.vin))
            .arg(QString::fromStdString(samochod.rejestracja));
    }

    void initializeData() {
        // Add some sample persons
        osoby.push_back(Osoba("Jan", "Kowalski", QDateTime(QDate(1990,1,1))));
        osoby.push_back(Osoba("Anna", "Nowak", QDateTime(QDate(1985,5,12))));
        osoby.push_back(Osoba("Piotr", "Zielinski", QDateTime(QDate(1978,10,30))));

        // Add some sample drivers
        kierowcy.push_back(Kierowca("Adam", "Malinowski", QDateTime(QDate(1980,4,20)), "PJ12345", QDateTime(QDate(1998,5,5))));
        kierowcy.push_back(Kierowca("Beata", "Kamińska", QDateTime(QDate(1992,7,15)), "PJ67890", QDateTime(QDate(2012,9,1))));

        // Add some sample cars
        samochody.push_back(Samochod("Toyota", "Corolla", 2015, 60000, "VIN1234ABCD", "KR12345"));
        samochody.push_back(Samochod("Volkswagen", "Golf", 2018, 30000, "VIN5678EFGH", "WA12345"));
        samochody.push_back(Samochod("Skoda", "Octavia", 2020, 10000, "VIN9012IJKL", "PO12345"));
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(400, 700);
    mainWindow.show();

    return app.exec();
}
