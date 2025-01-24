#include "Samochod.h"
#include <QInputDialog>
#include <QMessageBox>

Samochod::Samochod(std::string m, std::string mo, int r, int p, std::string v, std::string re)
    : marka(m), model(mo), rokProdukcji(r), przebieg(p), vin(v), rejestracja(re) {}

void Samochod::edytujSamochod() {
    QString newMarka = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowa marka:",
                                             QLineEdit::Normal, QString::fromStdString(marka));
    QString newModel = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy model:",
                                             QLineEdit::Normal, QString::fromStdString(model));
    QString newRokProdukcji = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy rok produkcji:",
                                                    QLineEdit::Normal, QString::number(rokProdukcji));
    QString newPrzebieg = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy przebieg:",
                                                QLineEdit::Normal, QString::number(przebieg));
    QString newVin = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowy VIN:",
                                           QLineEdit::Normal, QString::fromStdString(vin));
    QString newRejestracja = QInputDialog::getText(nullptr, "Edytuj samochód", "Nowa rejestracja:",
                                                   QLineEdit::Normal, QString::fromStdString(rejestracja));

    if (!newMarka.isEmpty() && !newModel.isEmpty() &&
        !newRokProdukcji.isEmpty() && !newPrzebieg.isEmpty() &&
        !newVin.isEmpty() && !newRejestracja.isEmpty()) {
        marka = newMarka.toStdString();
        model = newModel.toStdString();
        rokProdukcji = newRokProdukcji.toInt();
        przebieg = newPrzebieg.toInt();
        vin = newVin.toStdString();
        rejestracja = newRejestracja.toStdString();
        QMessageBox::information(nullptr, "Edytuj samochód",
                                 "Dane samochodu zostały zaktualizowane.");
    }
}

void Samochod::usunSamochod(std::vector<Samochod> &samochody) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Usuń samochód",
                                  "Czy na pewno chcesz usunąć ten samochód?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        auto it = std::find_if(samochody.begin(), samochody.end(), [this](const Samochod &s) {
            return s.marka == this->marka && s.model == this->model && s.rokProdukcji == this->rokProdukcji;
        });
        if (it != samochody.end()) {
            samochody.erase(it);
            QMessageBox::information(nullptr, "Usuń samochód",
                                     "Samochód został usunięty.");
        }
    }
}

void Samochod::dodajSamochod(std::vector<Samochod> &samochody) {
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

    samochody.push_back(Samochod(
        newMarka.toStdString(),
        newModel.toStdString(),
        newRokProdukcji.toInt(),
        newPrzebieg.toInt(),
        newVin.toStdString(),
        newRejestracja.toStdString()
    ));

    QMessageBox::information(nullptr, "Dodaj samochód",
                             "Nowy samochód został dodany.");
}

void Samochod::szukajSamochod(std::vector<Samochod> &samochody) {
    QString searchMarka = QInputDialog::getText(nullptr, "Szukaj samochodu", "Podaj markę:");
    if (!searchMarka.isEmpty()) {
        for (const auto &samochod : samochody) {
            if (QString::fromStdString(samochod.marka) == searchMarka) {
                QMessageBox::information(nullptr, "Wynik wyszukiwania",
                                         "Znaleziono samochód: " +
                                         QString::fromStdString(samochod.marka) + " " +
                                         QString::fromStdString(samochod.model));
                return;
            }
        }
        QMessageBox::information(nullptr, "Wynik wyszukiwania",
                                 "Nie znaleziono samochodu o marce: " + searchMarka);
    }
}
