#include "Kierowca.h"
#include <QInputDialog>
#include <QMessageBox>

Kierowca::Kierowca(QString i, QString n, QDateTime d, QString p, QDateTime u)
    : Osoba(i, n, d), prawoJazdy(p), dataUzyskaniaPrawaJazdy(u) {}

void Kierowca::edytujKierowce() {
    edytujOsobe();  // wywołujemy metodę z klasy bazowej
    QString newPrawoJazdy = QInputDialog::getText(nullptr, "Edytuj kierowcę",
                                                  "Nowy numer prawa jazdy:",
                                                  QLineEdit::Normal, prawoJazdy);
    QString newDataUzyskaniaStr = QInputDialog::getText(nullptr, "Edytuj kierowcę",
                                                        "Data uzyskania prawa jazdy (YYYY-MM-DD):",
                                                        QLineEdit::Normal,
                                                        dataUzyskaniaPrawaJazdy.toString("yyyy-MM-dd"));
    QDate newDataUzyskania = QDate::fromString(newDataUzyskaniaStr, "yyyy-MM-dd");
    if (!newPrawoJazdy.isEmpty() && newDataUzyskania.isValid()) {
        prawoJazdy = newPrawoJazdy;
        dataUzyskaniaPrawaJazdy = QDateTime(newDataUzyskania);
        QMessageBox::information(nullptr, "Edytuj kierowcę",
                                 "Dane kierowcy zostały zaktualizowane.");
    }
}

void Kierowca::dodajKierowce(std::vector<Kierowca> &kierowcy) {
    QString newImie = QInputDialog::getText(nullptr, "Dodaj kierowcę", "Imię:");
    if (newImie.isEmpty()) return;

    QString newNazwisko = QInputDialog::getText(nullptr, "Dodaj kierowcę", "Nazwisko:");
    if (newNazwisko.isEmpty()) return;

    QDate newDataUrodzenia = QDate::fromString(
        QInputDialog::getText(nullptr, "Dodaj kierowcę", "Data urodzenia (YYYY-MM-DD):"),
        "yyyy-MM-dd");
    if (!newDataUrodzenia.isValid()) {
        QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data urodzenia.");
        return;
    }

    QString newPrawoJazdy = QInputDialog::getText(nullptr, "Dodaj kierowcę", "Numer prawa jazdy:");
    if (newPrawoJazdy.isEmpty()) return;

    QDate newDataUzyskania = QDate::fromString(
        QInputDialog::getText(nullptr, "Dodaj kierowcę", "Data uzyskania prawa jazdy (YYYY-MM-DD):"),
        "yyyy-MM-dd");
    if (!newDataUzyskania.isValid()) {
        QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data uzyskania prawa jazdy.");
        return;
    }

    kierowcy.push_back(
        Kierowca(newImie, newNazwisko, QDateTime(newDataUrodzenia), newPrawoJazdy, QDateTime(newDataUzyskania))
    );
    QMessageBox::information(nullptr, "Dodaj kierowcę",
                             "Nowy kierowca został dodany.");
}
