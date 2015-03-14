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
    }

    ostream& afficher(ostream& sortie) const {
        for (i = contenu.size(); i > 0; i--) {
            sortie << "Couche " << (i - 1) << endl;
            for (j = 0; j < contenu[i-1].size(); j++) {
                for (k = 0; k < contenu[i-1][j].size(); k++) {
                    contenu[i-1][j][k].afficher(sortie);
                    if (k < contenu[i-1][j].size() - 1) sortie << " ";
                }
                sortie << endl;
            }
        }
    }
};

const Construction operator*(unsigned int n, Construction const& a)
{
}

const Construction operator/(unsigned int n, Construction const& a)
{
}

const Construction operator%(unsigned int n, Construction const& a)
{
}

int main() {


    return 0;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

/*int main()
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
}*/
