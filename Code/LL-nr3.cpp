#include <iostream>
#include <fstream>
#include <string>
#include <cmath>  // pentru funcția abs

// Clasa de bază pentru Vehicul
class Vehicul {
protected:
    std::string numarInmatriculare;
    int oraIntrare;
    int minutIntrare;
    int oraIesire;
    int minutIesire;

public:
    Vehicul(std::string numar, int oraIn, int minutIn, int oraOut, int minutOut)
        : numarInmatriculare(numar), oraIntrare(oraIn), minutIntrare(minutIn), oraIesire(oraOut), minutIesire(minutOut) {}

    int calculeazaTimpParcare() {
        int timpIntrareInMinute = oraIntrare * 60 + minutIntrare;
        int timpIesireInMinute = oraIesire * 60 + minutIesire;
        return abs(timpIesireInMinute - timpIntrareInMinute);
    }

    virtual double calculeazaTarif() = 0;  // metodă virtuală pentru calculul tarifului

    // Metodă pentru a obține numărul de înmatriculare
    std::string getNumarInmatriculare() const {
        return numarInmatriculare;
    }

    // Destructor virtual
    virtual ~Vehicul() {}
};

// Clasa derivată pentru Masina
class Masina : public Vehicul {
public:
    Masina(std::string numar, int oraIn, int minutIn, int oraOut, int minutOut)
        : Vehicul(numar, oraIn, minutIn, oraOut, minutOut) {}

    double calculeazaTarif() override {
        int timp = calculeazaTimpParcare();
        return timp * 5.0;  // 5 lei pe oră
    }
};

// Clasa derivată pentru Motocicleta
class Motocicleta : public Vehicul {
public:
    Motocicleta(std::string numar, int oraIn, int minutIn, int oraOut, int minutOut)
        : Vehicul(numar, oraIn, minutIn, oraOut, minutOut) {}

    double calculeazaTarif() override {
        int timp = calculeazaTimpParcare();
        return timp * 3.0;  // 3 lei pe oră
    }
};

// Clasa derivată pentru Camion
class Camion : public Vehicul {
public:
    Camion(std::string numar, int oraIn, int minutIn, int oraOut, int minutOut)
        : Vehicul(numar, oraIn, minutIn, oraOut, minutOut) {}

    double calculeazaTarif() override {
        int timp = calculeazaTimpParcare();
        return timp * 10.0;  // 10 lei pe oră
    }
};

// Clasa derivată pentru Bicicleta
class Bicicleta : public Vehicul {
public:
    Bicicleta(std::string numar, int oraIn, int minutIn, int oraOut, int minutOut)
        : Vehicul(numar, oraIn, minutIn, oraOut, minutOut) {}

    double calculeazaTarif() override {
        int timp = calculeazaTimpParcare();
        if (timp <= 120)  // 2 ore gratuite
            return 0.0;
        else
            return (timp - 120) * 2.0;  // 2 lei pe oră după 2 ore
    }
};

#define MAX_VEHICULE 100

int main() {
    std::ifstream fisier("parcare.txt");
    std::string tipVehicul, numarInmatriculare;
    int oraIn, minutIn, oraOut, minutOut;
    
    Vehicul* vehicule[MAX_VEHICULE];
    int numarVehicule = 0;

    // Citirea datelor din fișier și instanțierea obiectelor
    while (fisier >> tipVehicul >> numarInmatriculare >> oraIn >> minutIn >> oraOut >> minutOut) {
        if (tipVehicul == "Masina") {
            vehicule[numarVehicule++] = new Masina(numarInmatriculare, oraIn, minutIn, oraOut, minutOut);
        } else if (tipVehicul == "Motocicleta") {
            vehicule[numarVehicule++] = new Motocicleta(numarInmatriculare, oraIn, minutIn, oraOut, minutOut);
        } else if (tipVehicul == "Camion") {
            vehicule[numarVehicule++] = new Camion(numarInmatriculare, oraIn, minutIn, oraOut, minutOut);
        } else if (tipVehicul == "Bicicleta") {
            vehicule[numarVehicule++] = new Bicicleta(numarInmatriculare, oraIn, minutIn, oraOut, minutOut);
        }
    }

    fisier.close();

    // Calcularea și afișarea tarifelor
    for (int i = 0; i < numarVehicule; i++) {
        int timp = vehicule[i]->calculeazaTimpParcare();
        double tarif = vehicule[i]->calculeazaTarif();
        std::cout << "Vehicul: " << typeid(*vehicule[i]).name()
                  << " | Nr. Inmatriculare: " << vehicule[i]->getNumarInmatriculare()
                  << " | Timp: " << timp << " minute"
                  << " | Tarif: " << tarif << " lei\n";
        delete vehicule[i];  // Eliberăm memoria
    }

    return 0;
}
