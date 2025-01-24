#include <QtTest>          
#include "../Osoba.h"      
#include "../Samochod.h"
#include "../RentalManager.h"

// Klasa testowa
class TestRental : public QObject
{
    Q_OBJECT

private slots:

    void testOsobaConstructor();
    void testSamochodConstructor();
    void testRentalManagerInitializeData();
};

// --- Implementacje testów ---
void TestRental::testOsobaConstructor()
{
    // GIVEN:
    QString imie = "Jan";
    QString nazwisko = "Kowalski";
    QDateTime data(QDate(1990, 1, 1));

    // WHEN:
    Osoba o(imie, nazwisko, data);

    // THEN (sprawdzamy asercjami QTest):
    QCOMPARE(o.imie, imie);
    QCOMPARE(o.nazwisko, nazwisko);
    QCOMPARE(o.dataUrodzenia, data);
}

void TestRental::testSamochodConstructor()
{
    // GIVEN
    std::string marka = "Toyota";
    std::string model = "Corolla";
    int rok = 2015;
    int przebieg = 60000;
    std::string vin = "VIN1234ABCD";
    std::string rejestracja = "KR12345";

    // WHEN
    Samochod s(marka, model, rok, przebieg, vin, rejestracja);

    // THEN
    QCOMPARE(s.marka, marka);
    QCOMPARE(s.model, model);
    QCOMPARE(s.rokProdukcji, rok);
    QCOMPARE(s.przebieg, przebieg);
    QCOMPARE(s.vin, vin);
    QCOMPARE(s.rejestracja, rejestracja);
}

void TestRental::testRentalManagerInitializeData()
{
    RentalManager::instance().osoby.clear();
    RentalManager::instance().kierowcy.clear();
    RentalManager::instance().samochody.clear();
    RentalManager::instance().wypozyczenia.clear();

    // WHEN:
    RentalManager::instance().initializeData();

    // THEN (zakładamy, że initializeData() dodaje 3 osoby, 2 kierowców, 3 samochody itd.)
    QVERIFY(!RentalManager::instance().osoby.empty());
    QVERIFY(!RentalManager::instance().samochody.empty());

    // Ewentualnie konkretne sprawdzenie liczby instancji:
    QCOMPARE((int)RentalManager::instance().osoby.size(), 3);
    QCOMPARE((int)RentalManager::instance().kierowcy.size(), 2);
    QCOMPARE((int)RentalManager::instance().samochody.size(), 3);
}

QTEST_APPLESS_MAIN(TestRental)

#include "test_rental.moc"
