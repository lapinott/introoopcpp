#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* Classe représentant les "fleurs".
 * Une instance de cette classe hors Bouquet est un exemple / une catégorie
 * un type de de fleurs.
 * Les fleurs "réelles" sont les instances présentes dans les bouquets.
 */
class Fleur
{
  /*******************************************
   * Complétez le programme à partir d'ici.
   *******************************************/
private:

    string nom;
    string couleur;
    double prix_base;
    bool parfum_;
    bool promotion;

public:

    Fleur (string nom, string couleur, double prix_base, bool parfum_ = false, bool promotion = false) :
        nom{nom},
        couleur{couleur},
        prix_base{prix_base},
        parfum_{parfum_},
        promotion{promotion}
    {}

    double prix () const {
        return this -> promotion ? this -> prix_base / 2 : this -> prix_base;
    }

    double parfum () const {
        return this -> parfum_;
    }

    string getNom () const {
        return this -> nom;
    }

    string getCouleur () const {
        return this -> couleur;
    }

    ostream& affiche(ostream& sortie) const {
        if (this -> parfum_) return sortie << this -> nom << " " << this -> couleur << " parfumée, prix : " << this -> prix() << " CHF";
        else return sortie << this -> nom << " " << this -> couleur << ", prix : " << this -> prix() << " CHF";
    }

    /*bool operator == (Fleur& f) {
        return this -> nom == f.nom && this -> couleur == f.couleur && this -> parfum_ == f.parfum_;
    }*/
};

bool operator == (const Fleur& f1, const Fleur& f2) {
    return f1.getNom() == f2.getNom() && f1.getCouleur() == f2.getCouleur() && f1.parfum() == f2.parfum();
}


ostream& operator << (ostream& os, Fleur& f) {
    f.affiche(os);
    return os;
}

class Bouquet {

private:

    vector<Fleur> bouquet;

public:

    bool parfum () const {
        for (Fleur f : this -> bouquet) {
            if (f.parfum()) return true;
        }
        return false;
    }

    double prix () const {
        double somme = 0;
        for (Fleur f : this -> bouquet) {
            somme += f.prix();
        }
        return this -> parfum() ? somme * 2 : somme;
    }

    void affiche (ostream& os) const {
        if (this -> bouquet.size() == 0) os << "Encore aucune fleur dans le bouquet !";
        else {
            if (this -> parfum()) os << "Bouquet parfumé composé de :" << endl;
            else os << "Bouquet composé de :" << endl;
            for (Fleur f : this -> bouquet) {
                f.affiche(os);
                os << endl;
            }
            os << "Prix total : " << this -> prix() << " CHF" << endl;
        }
    }

    Bouquet& operator += (Fleur f) {
        this -> bouquet.push_back(f);
        return *this;
    }

    Bouquet& operator -= (Fleur f) {
        for (unsigned int i = 0; i < this -> bouquet.size(); i++) {
            if (this -> bouquet[i] == f) {
                this -> bouquet.erase(this -> bouquet.begin() + i);
                i--;
            }
        }
        return *this;
    }
};

Bouquet& operator + (Bouquet& b, Fleur f) {
    return b += f;
}

Bouquet& operator - (Bouquet& b, Fleur f) {
    return b -= f;
}

ostream& operator << (ostream& os, Bouquet& b) {
    b.affiche(os);
    return os;
}


/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Fleur r1("Rose", "jaune", 1.5); // exemple de rose jaune inodore
  cout << r1 << endl;

  Fleur r2("Rose", "jaune", 3.0, true); // exemple de rose jaune parfumée
  Fleur r3("Rose", "rouge", 2.0, true, true); // exemple de rose rouge parfumée en promo
  Bouquet b1;
  b1 += r1; // ajoute une fleur de type r1
  b1 += r1; // ajoute aurte une fleur de type r1
  b1 += r2;
  b1 += r3;
  cout << b1 << endl;

  b1 = b1 - r1; // supprime toutes les fleurs de même type que r1
  cout << b1 << endl;

  Bouquet b2;
  b2 = b1 + r1; // remet une fleur de type r1
  cout << b2 << endl;

  // supprime toutes les fleurs parfumées
  b2 -= r2;
  b2 -= r3;
  cout << b2;

  return 0;
}
