#include "Osoba.h"
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>

Osoba::Osoba(QString i, QString n, QDateTime d)
    : imie(i), nazwisko(n), dataUrodzenia(d) {}

void Osoba::szukajOsobe(std::vector<Osoba> &osoby) {
    QString searchImie = QInputDialog::getText(nullptr, "Szukaj osoby", "Podaj imię:");
    if (!searchImie.isEmpty()) {
        for (const auto &osoba : osoby) {
            if (osoba.imie == searchImie) {
                QMessageBox::information(nullptr, "Wynik wyszukiwania",
                                         "Znaleziono osobę: " + osoba.imie + " " + osoba.nazwisko);
                return;
            }
        }
        QMessageBox::information(nullptr, "Wynik wyszukiwania",
                                 "Nie znaleziono osoby o imieniu: " + searchImie);
    }
}

void Osoba::edytujOsobe() {
    QString newImie = QInputDialog::getText(nullptr, "Edytuj osobę", "Nowe imię:",
                                           QLineEdit::Normal, imie);
    QString newNazwisko = QInputDialog::getText(nullptr, "Edytuj osobę", "Nowe nazwisko:",
                                                QLineEdit::Normal, nazwisko);
    if (!newImie.isEmpty() && !newNazwisko.isEmpty()) {
        imie = newImie;
        nazwisko = newNazwisko;
        QMessageBox::information(nullptr, "Edytuj osobę",
                                 "Dane osoby zostały zaktualizowane.");
    }
}

void Osoba::usunOsobe(std::vector<Osoba> &osoby) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Usuń osobę",
                                  "Czy na pewno chcesz usunąć tę osobę?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        auto it = std::find_if(osoby.begin(), osoby.end(), [this](const Osoba &o) {
            return o.imie == this->imie && o.nazwisko == this->nazwisko;
        });
        if (it != osoby.end()) {
            osoby.erase(it);
            QMessageBox::information(nullptr, "Usuń osobę",
                                     "Osoba została usunięta.");
        }
    }
}

void Osoba::dodajOsobe(std::vector<Osoba> &osoby) {
    QString newImie = QInputDialog::getText(nullptr, "Dodaj osobę", "Imię:");
    if (newImie.isEmpty()) return;

    QString newNazwisko = QInputDialog::getText(nullptr, "Dodaj osobę", "Nazwisko:");
    if (newNazwisko.isEmpty()) return;

    QDate newDataUrodzenia = QDate::fromString(
        QInputDialog::getText(nullptr, "Dodaj osobę", "Data urodzenia (YYYY-MM-DD):"),
        "yyyy-MM-dd");
    if (!newDataUrodzenia.isValid()) {
        QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data urodzenia.");
        return;
    }

    osoby.push_back(Osoba(newImie, newNazwisko, QDateTime(newDataUrodzenia)));
    QMessageBox::information(nullptr, "Dodaj osobę", "Nowa osoba została dodana.");
}
