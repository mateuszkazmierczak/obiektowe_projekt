#include "Wypozyczalnia.h"
#include <QInputDialog>
#include <QMessageBox>

Wypozyczalnia::Wypozyczalnia(QString n, QString a)
    : nazwa(n), adres(a)
{}

void Wypozyczalnia::edytujWypozyczalnie() {
    QString newNazwa = QInputDialog::getText(nullptr, "Edytuj wypożyczalnię",
                                             "Nowa nazwa:", QLineEdit::Normal, nazwa);
    QString newAdres = QInputDialog::getText(nullptr, "Edytuj wypożyczalnię",
                                            "Nowy adres:", QLineEdit::Normal, adres);
    if (!newNazwa.isEmpty() && !newAdres.isEmpty()) {
        nazwa = newNazwa;
        adres = newAdres;
        QMessageBox::information(nullptr, "Edytuj wypożyczalnię",
                                 "Dane wypożyczalni zostały zaktualizowane.");
    }
}
