#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <vector>
#include "Osoba.h"
#include "Kierowca.h"
#include "Samochod.h"
#include "Wypozyczenie.h"
#include "Wypozyczalnia.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    
private slots:
    // Metody slotów z Twojego kodu
    void on_addPersonButton_clicked();
    void on_searchPersonButton_clicked();
    void on_editPersonButton_clicked();
    void on_deletePersonButton_clicked();
    void on_clearPersonSelection_clicked();

    void on_addDriverButton_clicked();
    void on_editDriverButton_clicked();
    void on_deleteDriverButton_clicked();
    void on_clearDriverSelection_clicked();

    void on_addCarButton_clicked();
    void on_searchCarButton_clicked();
    void on_editCarButton_clicked();
    void on_deleteCarButton_clicked();

    void on_rentButton_clicked();
    void on_returnButton_clicked();
    void on_editWypozyczenieButton_clicked();
    void on_editRentalButton_clicked();

private:
    QListWidget *personListWidget;
    QListWidget *driverListWidget;
    QListWidget *carListWidget;

    std::vector<Osoba> osoby;
    std::vector<Kierowca> kierowcy;
    std::vector<Samochod> samochody;
    std::vector<Wypozyczenie> wypozyczenia;

    Wypozyczalnia wypozyczalnia;

    void updatePersonList();
    void updateDriverList();
    void updateCarList();
    QString carToString(const Samochod &samochod);
    void initializeData();
};

#endif // MAINWINDOW_H
