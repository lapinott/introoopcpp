#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/

    Brique (Forme forme, Couleur couleur) : forme{forme}, couleur{couleur} {}

    ostream& afficher(ostream& sortie) const {
        if (this -> couleur != "") return sortie << "(" << this -> forme << ", " << this -> couleur << ")";
        else return sortie << this -> forme;
    }
};

ostream& operator << (ostream& os, Brique b) {
    return b.afficher(os);
}

class Construction
{
  friend class Grader;

private:

    vector<vector<vector<Brique>>> contenu;

public:

    Construction (Brique b) {
        this -> contenu = vector<vector<vector<Brique>>>(1, vector<vector<Brique>>(1, vector<Brique>(1, b)));
        /*this -> contenu.reserve(1);
        this -> contenu[0].reserve(1);
        this -> contenu[0][0].reserve(1);
        this -> contenu[0][0].push_back(b);*/
    }

    ostream& afficher(ostream& sortie) const {
        for (int i = contenu.size(); i > 0; i--) {
            sortie << "Couche " << (i - 1) << " :" << endl;
            for (int j = 0; j < contenu[i-1].size(); j++) {
                for (int k = 0; k < contenu[i-1][j].size(); k++) {
                    contenu[i-1][j][k].afficher(sortie);
                    if (k < contenu[i-1][j].size() - 1) sortie << " ";
                }
                sortie << endl;
            }
        }
        return sortie;
    }

    Construction& operator ^= (const Construction& b) {
        for (vector<vector<Brique>> layer : b.contenu) {
            this -> contenu.push_back(layer);
        }
        return *this;
        //this -> contenu += c.contenu;
        //this -> contenu.push_back(c.contenu);
    }

    Construction& operator -= (const Construction& b) {
        if (b.contenu.size() > this -> contenu.size()) return *this;

        /*int hauteur_max = this -> contenu.size();
        int couche = 0;
        for (vector<vector<Brique>> layer : b.contenu) {
            if (couche <= hauteur_max) {
                for (vector<Brique> row : layer) {
                    this -> contenu[couche].push_back(row);
                }
            } else break;
            ++couche;
        }*/

        for (int i = 0; i < this -> contenu.size(); i++) {
            for (int j = 0; j < b.contenu[0].size(); j++) {
                this -> contenu[i].push_back(b.contenu[i][j]);
            }
        }
        return *this;
    }

    Construction& operator += (const Construction& b) {
        if (b.contenu.size() > this -> contenu.size()) return *this;
        if (b.contenu[0].size() > this -> contenu[0].size()) return *this;
        for (int i = 0; i < this -> contenu.size(); i++) {
            for (int j = 0; j < this -> contenu[0].size(); j++) {
                for (int k = 0; k < b.contenu[0][0].size(); k++) {
                    this -> contenu[i][j].push_back(b.contenu[i][j][k]);
                }
            }
        }
        return *this;
    }
};

ostream& operator << (ostream& os, const Construction& c) {
    return c.afficher(os);
}

Construction& operator ^ (Construction a, const Construction& b) {
    a ^= b;
    return a;
}

Construction& operator - (Construction a, const Construction& b) {
    a -= b;
    return a;
}

Construction& operator + (Construction a, const Construction& b) {
    a += b;
    return a;
}

const Construction operator*(unsigned int n, Construction const& a)
{
    Construction a0 = a;
    Construction an = a;
    for (int i = 0; i < n - 1; i++) {
        an = an + a0;
    }
    return an;
}

const Construction operator/(unsigned int n, Construction const& a)
{
    Construction a0 = a;
    Construction an = a;
    for (int i = 0; i < n - 1; i++) {
        an = an ^ a0;
    }
    return an;
}

const Construction operator%(unsigned int n, Construction const& a)
{
    Construction a0 = a;
    Construction an = a;
    for (int i = 0; i < n - 1; i++) {
        an = an - a0;
    }
    return an;
}

/*
int main() {

    Brique b("Rombicuboctaèdre", "Vert fluo");
    Construction sphinx(b);
    Construction sphinx2(b);
    sphinx2 ^= sphinx;
    Construction sphinx3 = sphinx2;
    sphinx3 -= sphinx2;
    Construction sphinx4 = sphinx3;
    sphinx4 += sphinx3;
    cout << sphinx;
    cout << "-----------" << endl;
    cout << sphinx2;
    cout << "-----------" << endl;
    cout << sphinx3;
    cout << "-----------" << endl;
    cout << sphinx4;
    return 0;
}
*/

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
