#include <vector>
#include <iostream>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme à partir d'ici.
 *******************************************/

class Affichable {

public:

    virtual void affiche (ostream& os) const = 0;
};

class OptionVoyage : public Affichable {

private:

    string _nom;
    double _prix;

public:

    OptionVoyage (string nom, double prix) : _nom{nom}, _prix{prix} {}

    string nom() const {
        return this -> _nom;
    }

    virtual double prix() const {
        return this -> _prix;
    }

    void affiche (ostream& os) const {
        os << nom() << " ->  " << this -> prix() << " CHF";
    }
};

class Sejour : public virtual OptionVoyage {

private:

    int nb_nuits;
    double prix_nuit;

public:

    Sejour (string nom, double prix, int nb_nuits, double prix_nuit) : OptionVoyage(nom, prix), nb_nuits{nb_nuits}, prix_nuit{prix_nuit} {}

    virtual double prix() const override {
        return OptionVoyage::prix() + this -> nb_nuits * this -> prix_nuit;
    }
};

class Transport : public virtual OptionVoyage {

private:

    bool l;
    constexpr static double TARIF_LONG = 1500.0;
    constexpr static double TARIF_BASE = 200.0;

public:

    Transport (string nom, double prix, bool l = false) : OptionVoyage(nom, prix), l{l} {}

    virtual double prix() const override {
        return OptionVoyage::prix() + (this -> l ? this -> TARIF_LONG : this -> TARIF_BASE);
    }
};

class OptionCombinee : public Sejour, public Transport {

public:

    OptionCombinee (string nom, double prix, int nb_nuits, double prix_nuit, double l = false) : OptionVoyage(nom, prix), Sejour(nom, prix, nb_nuits, prix_nuit), Transport(nom, prix, l) {}

    virtual double prix () const override final {
        return 0.75 * (Sejour::prix() + Transport::prix());
    }
};

class KitVoyage : public Affichable {

private:

    vector<const OptionVoyage*> vov;
    string depart;
    string destination;

public:

    KitVoyage (string depart, string destination) : depart{depart}, destination{destination} {}

    double prix () const {
        double somme = 0;
        for (const OptionVoyage* ov : this -> vov) {
            somme += ov -> prix();
        }
        return somme;
    }

    void ajouter_option (OptionVoyage& ov) {
        this -> vov.push_back(&ov);
    }

    void annuler () {
        this -> vov.clear();
    }

    void affiche (ostream& os) const {
        if (this -> vov.empty()) {
            os << "Voyage de " << this -> depart << " à " << this -> destination << ": vous n'avez rien réservé !" << endl;
        }
        else {
            os << "Voyage de " << this -> depart << " à " << this -> destination << ", avec pour options :" << endl;
            for (const OptionVoyage* ov : this -> vov) {
                os << "- ";
                ov -> affiche(os);
                os << endl;
            }
            os << "Prix total : " << this -> prix() << " CHF" << endl;
        }
    }
};

ostream& operator << (ostream& os, Affichable& a) {
    a.affiche(os);
    return os;
}


/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Transport transp1("Trajet en train", 50.0);
  Transport transp2("Trajet en avion", 50.0, true);

  Sejour sejour1("Hotel 3* : Les amandiers ", 40.0, 5, 100.0);
  Sejour sejour2("Hotel 4* : Ambassador Plazza  ", 100.0, 2, 250.0);

  OptionCombinee combi("Hotel 4* : Ambassador Plazza et trajet en avion",
                       100.0, 2, 250.0, true);

  KitVoyage kit1("Zurich", "Paris");
  kit1.ajouter_option(transp1);
  kit1.ajouter_option(sejour1);
  cout << kit1 << endl;

  KitVoyage kit2("Zurich", "New York");
  kit2.ajouter_option(transp2);
  kit2.ajouter_option(sejour2);
  cout << kit2 << endl;

  KitVoyage kit3("Zurich", "New York");
  kit3.ajouter_option(combi);
  cout << kit3 << endl;

  kit1.annuler();
  kit2.annuler();
  cout << kit1 << endl;
  cout << kit2 << endl;

  return 0;

}
