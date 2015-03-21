#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

protected:

    const string nom_;
    int niveau_;
    int points_de_vie_;
    int force_;
    int position_;

public:

    Creature (const string& nom, const int& niveau, const int& pv, const int& force, const int& position = 0) :
        nom_{nom}, niveau_{niveau}, points_de_vie_{pv}, force_{force}, position_{position} {}

    bool vivant () const {
        return this -> points_de_vie_ > 0;
    }

    int points_attaque () const {
        return this -> vivant() ? this -> force_ * this -> niveau_ : 0;
    }

    void deplacer (const int& montant) {
        if (this -> vivant()) this -> position_ += montant;
    }

    void adieux () const {
        cout << this -> nom_ << " n'est plus!" << endl;
    }

    void faiblir (const int& montant) {
        this -> points_de_vie_ -= montant;
        if (this -> points_de_vie_ <= 0) {
            this -> points_de_vie_ = 0;
            this -> adieux();
        }
    }

    void afficher () {
        cout << this -> nom_ << ", niveau: " << this -> niveau_ << ", points de vie: " << this -> points_de_vie_
            << ", force: " << this -> force_ << ", points d'attaque: " << this -> points_attaque() << ", position: " << this -> position_ << endl;
    }

    int position () const {
        return this -> position_;
    }
};

class Dragon : public Creature {

private:

    int portee_flamme_;

public:

    Dragon (const string& nom, const int& niveau, const int& pv, const int& force, const int& portee_flamme, const int& position = 0) :
        Creature (nom, niveau, pv, force, position), portee_flamme_{portee_flamme} {}

    void voler (const int& pos) {
        if (this -> vivant()) this -> position_ = pos;
    }

    void souffle_sur (Creature& bete) {
        if (this -> vivant() && bete.vivant() && distance(this -> position_, bete.position()) <= this -> portee_flamme_) {
            bete.faiblir(this -> points_attaque());
            this -> faiblir(distance(this -> position_, bete.position()));
            if (this -> vivant() && !bete.vivant()) this -> niveau_ += 1;
        }
    }
};

class Hydre : public Creature {

private:

    int longeur_cou_;
    int dose_poison_;

public:

    Hydre (const string& nom, const int& niveau, const int& pv, const int& force, const int& longueur_cou, const int& dose_poison, const int& position = 0) :
        Creature (nom, niveau, pv, force, position), longeur_cou_{longueur_cou}, dose_poison_{dose_poison} {}

    void empoisonne (Creature& bete) {
        if (this -> vivant() && bete.vivant() && distance(this -> position_, bete.position()) <= this -> longeur_cou_) {
            bete.faiblir(this -> points_attaque() + this -> dose_poison_);
            if (!bete.vivant()) this -> niveau_ += 1;
        }
    }
};

void combat (Dragon& d, Hydre& h) {
    if (d.vivant() && h.vivant()) {
        h.empoisonne(d);
        d.souffle_sur(h);
    }
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}
