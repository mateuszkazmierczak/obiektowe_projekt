#include "Wypozyczenie.h"
#include <QInputDialog>
#include <QMessageBox>

Wypozyczenie::Wypozyczenie(const Osoba &o, const Samochod &s,
                           const QDateTime &start, const QDateTime &end,
                           bool insurance)
    : osoba(o), samochod(s), dataStart(start), dataEnd(end), additionalInsurance(insurance)
{}

void Wypozyczenie::edytujWypozyczenie() {
    // Prompt for new start date
    QString startStr = QInputDialog::getText(nullptr, "Edytuj wypożyczenie",
                                             "Nowa data rozpoczęcia (YYYY-MM-DD):",
                                             QLineEdit::Normal, dataStart.date().toString("yyyy-MM-dd"));
    QDate newStartDate = QDate::fromString(startStr, "yyyy-MM-dd");
    if (!newStartDate.isValid()) {
        QMessageBox::warning(nullptr, "Błąd", "Niepoprawna data rozpoczęcia.");
        return;
    }

    // Prompt for new end date
    QString endStr = QInputDialog::getText(nullptr, "Edytuj wypożyczenie",
                                           "Nowa data zakończenia (YYYY-MM-DD):",
                                           QLineEdit::Normal, dataEnd.date().toString("yyyy-MM-dd"));
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
    QString insuranceChoice = QInputDialog::getItem(
        nullptr, "Edytuj wypożyczenie", "Ubezpieczenie dodatkowe:",
        insuranceOptions, insuranceOptions.indexOf(currentInsurance), false, &ok
    );
    if (!ok) return;

    bool newInsurance = (insuranceChoice == "Tak");

    // Update fields
    dataStart = QDateTime(newStartDate);
    dataEnd = QDateTime(newEndDate);
    additionalInsurance = newInsurance;

    QMessageBox::information(nullptr, "Edytuj wypożyczenie",
                             "Dane wypożyczenia zostały zaktualizowane.");
}
