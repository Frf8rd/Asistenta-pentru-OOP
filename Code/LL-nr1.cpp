#include <iostream>
#include <string>
using namespace std;

class Restaurant {
private:
    int id; // ID unic pentru restaurant
    string nume;
    string locatie;
    int anInfiintare;
    double numarClienti;
    string tipBucatarie;

public:
    // Constructor implicit
    Restaurant() {
        id = 0;
        nume = "Necunoscut";
        locatie = "Necunoscut";
        anInfiintare = 0;
        numarClienti = 0.0;
        tipBucatarie = "Necunoscut";
    }

    // Constructor cu parametri
    Restaurant(int id_, string n, string loc, int an, double clienti, string tipBuc) {
        id = id_;
        nume = n;
        locatie = loc;
        anInfiintare = an;
        numarClienti = clienti;
        tipBucatarie = tipBuc;
    }

    // Constructor de copiere
    Restaurant(const Restaurant &r) {
        id = r.id + 1;
        nume = r.nume;
        locatie = r.locatie;
        anInfiintare = r.anInfiintare;
        numarClienti = r.numarClienti;
        tipBucatarie = r.tipBucatarie;
    }

    // Destructor
    ~Restaurant() {
        cout << "Obiectul cu ID-ul " << id << " (" << nume << ", " << locatie << ") a fost distrus!" << endl;
    }

    // Metode pentru interogarea atributelor
    int getId() const { return id; }
    string getNume() const { return nume; }
    string getLocatie() const { return locatie; }
    int getAnInfiintare() const { return anInfiintare; }
    double getNumarClienti() const { return numarClienti; }
    string getTipBucatarie() const { return tipBucatarie; }

    // Metode pentru modificarea atributelor
    void setId(int id_) { id = id_; }
    void setNume(string n) { nume = n; }
    void setLocatie(string loc) { locatie = loc; }
    void setAnInfiintare(int an) { anInfiintare = an; }
    void setNumarClienti(double clienti) { numarClienti = clienti; }
    void setTipBucatarie(string tip) { tipBucatarie = tip; }

    // Metoda pentru a afisa informatiile restaurantului
    void afiseazaInfo() const {
        cout << "ID: " << id << endl;
        cout << "Nume: " << nume << endl;
        cout << "Locatie: " << locatie << endl;
        cout << "An Infiintare: " << anInfiintare << endl;
        cout << "Numar Clienti: " << numarClienti << endl;
        cout << "Tip Bucatarie: " << tipBucatarie << endl;
    }

    // Metoda pentru a adauga clienti
    void adaugaClienti(double clienti) {
        numarClienti += clienti;
    }
};

int main() {
    // Crearea unui obiect utilizand constructorul cu parametri
    Restaurant r1(1, "Crème de la Crème", "Chisinau", 2010, 25000, "Cofetărie");
    r1.afiseazaInfo();

    // Modificarea unui atribut
    r1.setNumarClienti(27000);
    cout << "\nDupa actualizare:\n";
    r1.afiseazaInfo();

    // Crearea unui obiect utilizand constructorul de copiere
    Restaurant r2 = r1;
    cout << "\nObiectul copiat:\n";
    r2.afiseazaInfo();

    // Adaugarea de clienti
    r1.adaugaClienti(1500);
    cout << "\nDupa adaugarea de clienti:\n";
    r1.afiseazaInfo();

    return 0;
}








