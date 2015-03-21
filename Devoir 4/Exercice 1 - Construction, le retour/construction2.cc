#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

class Piece {

private:

    string nom;

public:

    Piece (const string& nom) : nom{nom} {}

    void afficher (ostream& os) const {
        os << "\"" << this -> nom << "\"";
    }
};

class Simple : public Piece {

private:

    string orientation;

public:

    Simple (const string& nom, const string& orientation = "") : Piece(nom), orientation{orientation} {}

    string getOrientation() const {
        return this -> orientation;
    }

    void afficher (ostream& os) const {
        Piece::afficher(os);
        if (this -> getOrientation() != "") os << " orienté vers la " << this -> getOrientation();
        os << endl;
    }
};

class Composee : public Piece {

private:

    vector<Simple> pieces;

public:

    Composee (const string& nom) : Piece(nom) {}

    void construire (Simple s) {
        this -> pieces.push_back(s);
    }

    void afficher (ostream& os) const {
        Piece::afficher(os);
        os << " composée de :" << endl;
        for (Simple s : this -> pieces) {
            os << "    * pièce simple ";
            s.afficher(os);
        }
    }
};

ostream& operator << (ostream& os, Simple& s) {
    os << "pièce simple ";
    s.afficher(os);
    return os;
}

ostream& operator << (ostream& os, Composee& c) {
    os << "pièce ";
    c.afficher(os);
    return os;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

// Sans polymorphisme, c'est difficile de faire autrement :-(...
template <typename T>
void ajouterComposant(T composant, unsigned int nb)
{
  cout << ' ' << nb << " exemplaire";
  if (nb > 1) cout << 's';
  cout << " de " << composant;
}

int main()
{
  cout << "Nous fabriquons une boîte de jeu contenant :" << endl;
  ajouterComposant(Simple("brique standard"), 59);

  // Déclare une pièce composée dont le nom est «porte»
  Composee porte("porte");

  // Une porte est constituée...
  //  ...d'un cadran de porte orienté à gauche
  porte.construire(Simple("cadran porte", "gauche"));
  //  ...et d'un battant orienté à gauche
  porte.construire(Simple("battant", "gauche"));

  // La boite de jeu a pour 2e composant la porte
  ajouterComposant(porte, 1);

  // Déclare une pièce composée dont le nom est «fenêtre»
  Composee fenetre("fenetre");

  // Une fenêtre est constituée...
  //  ...d'un cadran de fenêtre (sans orientation)
  fenetre.construire(Simple("cadran fenetre"));
  //  ...d'un volet orienté à gauche
  fenetre.construire(Simple("volet", "gauche"));
  //  ...d'un volet orienté à droite
  fenetre.construire(Simple("volet", "droite"));

  // La boite de jeu a en plus deux fenêtres
  ajouterComposant(fenetre, 2);

  return 0;
}
