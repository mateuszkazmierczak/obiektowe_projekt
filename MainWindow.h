#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include "Wypozyczalnia.h"
#include "Samochod.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // Person (Osoba) slots
    void on_addPersonButton_clicked();
    void on_searchPersonButton_clicked();
    void on_editPersonButton_clicked();
    void on_deletePersonButton_clicked();
    void on_clearPersonSelection_clicked();

    // Driver (Kierowca) slots
    void on_addDriverButton_clicked();
    void on_editDriverButton_clicked();
    void on_deleteDriverButton_clicked();
    void on_clearDriverSelection_clicked();

    // Car (Samochod) slots
    void on_addCarButton_clicked();
    void on_searchCarButton_clicked();
    void on_editCarButton_clicked();
    void on_deleteCarButton_clicked();

    // Rent & Return
    void on_rentButton_clicked();
    void on_returnButton_clicked();
    void on_editWypozyczenieButton_clicked();

    // Edit rental place
    void on_editRentalButton_clicked();

private:
    // Listy GUI
    QListWidget *personListWidget;
    QListWidget *driverListWidget;
    QListWidget *carListWidget;

    Wypozyczalnia wypozyczalnia;

    // Metody do odświeżania list
    void updatePersonList();
    void updateDriverList();
    void updateCarList();

    // Metoda pomocnicza formatująca dane samochodu
    QString carToString(const Samochod &samochod);
};

#endif // MAINWINDOW_H
