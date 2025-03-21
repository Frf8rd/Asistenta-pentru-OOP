#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>  
#include <typeinfo>

class IVehicul {
public:
    virtual int calculeazaTimp() const = 0;
    virtual double calculeazaTarif() const = 0;
    virtual ~IVehicul() {}
};


class Vehicul : public IVehicul {
protected:
    std::string numarInmatriculare;
    int oraIntrare;
    int minutIntrare;
    int oraIesire;
    int minutIesire;

public:
    Vehicul(std::string numar, int oraIn, int minutIn, int oraOut, int minutOut)
        : numarInmatriculare(numar), oraIntrare(oraIn), minutIntrare(minutIn), oraIesire(oraOut), minutIesire(minutOut) {}

    int calculeazaTimp() const override {
        int timpIntrareInMinute = oraIntrare * 60 + minutIntrare;
        int timpIesireInMinute = oraIesire * 60 + minutIesire;
        return abs(timpIesireInMinute - timpIntrareInMinute);
    }

    std::string getNumarInmatriculare() const {
        return numarInmatriculare;
    }
};


class Masina : public Vehicul {
public:
    using Vehicul::Vehicul;
    double calculeazaTarif() const override {
        return calculeazaTimp() * 5.0;
    }
};

class Motocicleta : public Vehicul {
public:
    using Vehicul::Vehicul;
    double calculeazaTarif() const override {
        return calculeazaTimp() * 3.0;
    }
};

class Camion : public Vehicul {
public:
    using Vehicul::Vehicul;
    double calculeazaTarif() const override {
        return calculeazaTimp() * 10.0;
    }
};

class Bicicleta : public Vehicul {
public:
    using Vehicul::Vehicul;
    double calculeazaTarif() const override {
        int timp = calculeazaTimp();
        return (timp <= 120) ? 0.0 : (timp - 120) * 2.0;
    }
};

int main() {
    std::ifstream fisier("parcare.txt");
    std::string tipVehicul, numarInmatriculare;
    int oraIn, minutIn, oraOut, minutOut;
    
    std::vector<IVehicul*> vehicule;


    while (fisier >> tipVehicul >> numarInmatriculare >> oraIn >> minutIn >> oraOut >> minutOut) {
        if (tipVehicul == "Masina") {
            vehicule.push_back(new Masina(numarInmatriculare, oraIn, minutIn, oraOut, minutOut));
        } else if (tipVehicul == "Motocicleta") {
            vehicule.push_back(new Motocicleta(numarInmatriculare, oraIn, minutIn, oraOut, minutOut));
        } else if (tipVehicul == "Camion") {
            vehicule.push_back(new Camion(numarInmatriculare, oraIn, minutIn, oraOut, minutOut));
        } else if (tipVehicul == "Bicicleta") {
            vehicule.push_back(new Bicicleta(numarInmatriculare, oraIn, minutIn, oraOut, minutOut));
        }
    }

    fisier.close();


    for (const auto& vehicul : vehicule) {
        std::string tip = typeid(*vehicul).name();
        tip = tip.substr(6); 
        
        std::cout << "Vehicul: " << tip
                  << " | Nr. Inmatriculare: " << static_cast<Vehicul*>(vehicul)->getNumarInmatriculare()
                  << " | Timp: " << vehicul->calculeazaTimp() << " minute"
                  << " | Tarif: " << vehicul->calculeazaTarif() << " lei\n";
    }

  
    for (auto& vehicul : vehicule) {
        delete vehicul;
    }

    return 0;
}
