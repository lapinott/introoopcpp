#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;

/*******************************************
 * Completez le programme à partir d'ici.
 *******************************************/

class Mise {

protected:

    int mise_;

public:

    Mise (int mise) : mise_{mise} {}

    int mise() const {
        return this -> mise_;
    }

    virtual int gain (int tirage) const;
};

class Pleine : public Mise {

private:

    constexpr static int facteur = 35;
    int n;

public:

    Pleine (int mise, int n) : Mise(mise), n{n} {}

    virtual int gain (int tirage) const override final {
        if (tirage == this -> n) return this -> mise_ * this -> facteur;
        else return 0;
    }
};

class Rouges : public Mise {

private:

    array<int, 18> rouges {{1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}};

public:

    Rouges (int mise) : Mise(mise) {}

    virtual int gain (int tirage) const override final {
        if (this -> rouge(tirage)) return this -> mise_;
        else return 0;
    }

    bool rouge (int element) const {
        for (unsigned int i = 0; i < this -> rouges.size(); i++) {
            if (this -> rouges[i] == element) return true;
        }
        return false;
    }
};

class Joueur {

private:

    string nom_;
    Mise* strategie;

public:

    Joueur (string nom) : nom_{nom}, strategie{nullptr} {}
    Joueur operator = (Joueur j) = delete;

    string nom() const {
        return this -> nom_;
    }

    void set_strategie (Mise* strategie) {
        this -> strategie = strategie;
    }

    int mise () const {
        return this -> strategie == nullptr ? 0 : this -> strategie -> mise();
    }

    int gain (int tirage) const {
        return this -> strategie == nullptr ? 0 : this -> strategie -> gain(tirage);
    }
};

class Roulette {

protected:

    vector<const Joueur*> vj;
    int n;
    int gain;

public:

    virtual void participe (Joueur& j) {
        bool found = false;
        for (const Joueur* jj : this -> vj) {
            if (jj == &j) found = true;
        }
        if (!found) this -> vj.push_back(&j);
    }

    int tirage () const {
        return this -> n;
    }

    int nombre_participants () const {
        return this -> vj.size();
    }

    void rien_ne_va_plus (int valeur) {
        this -> gain = 0;
        this -> n = valeur;
        this -> gain_maison();
    }

    virtual int perte_mise (int mise_originale) const = 0;

    int gain_maison () {
        for (const Joueur* j : this -> vj) {
            if (j -> gain(this -> n) == 0) this -> gain += this -> perte_mise(j -> mise());
            else this -> gain -= j -> gain(this -> n);
        }
    }

    virtual void afficher (ostream& out) const = 0;

    void annoncer () const {
        cout << "Croupier : le numéro du tirage est le ";
        cout << this -> n << endl;
        for (const Joueur* j : this -> vj) {
            if (j -> gain(this -> n) == 0) cout << "Le joueur " << j -> nom() << " a misé " << j -> mise() << " et perd " << this -> perte_mise(j -> mise()) << endl;
            else cout << "Le joueur " << j -> nom() << " a misé " << j -> mise() << " et gagne " << j -> gain(this -> n) << endl;
        }
        cout << "Gain/perte du casino : " << this -> gain << endl;
    }
};

class RouletteFrancaise : public Roulette {

public:

    RouletteFrancaise () : Roulette() {}

    RouletteFrancaise (RouletteFrancaise& r) = delete;
    RouletteFrancaise operator = (RouletteFrancaise& r) = delete;

    virtual int perte_mise (int mise_originale) const {
        return mise_originale;
    }

    virtual void afficher (ostream& out) const {
        out << "Roulette française";
    }
};

class RouletteAnglaise : public Roulette {

public:

    RouletteAnglaise () : Roulette() {}

    RouletteAnglaise (RouletteAnglaise& r) = delete;
    RouletteAnglaise operator = (RouletteAnglaise& r) = delete;

    virtual void participe (Joueur j) {
        if (this -> vj.size() < 10) this -> vj.push_back(&j);
    }

    virtual int perte_mise (int mise_originale) const {
        return mise_originale / 2;
    }

    virtual void afficher (ostream& out) const {
        out << "Roulette anglaise";
    }
};

ostream& operator << (ostream& os, Roulette& r) {
    r.afficher (os);
    return os;
}

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

void simuler_jeu(Roulette& jeu)
{
  cout << jeu << " :" << endl;
  for (int tirage : array<int, 3>({ 12, 1, 31 })) {
    jeu.rien_ne_va_plus(tirage);
    jeu.annoncer();
    cout << endl;
  }
  cout << endl;
}

int main()
{
  Joueur joueur1("Dupond");
  Joueur joueur2("Dupont");
  Joueur joueur3("Dupond"); // un AUTRE joueur, du même nom

  Pleine p1(100, 1); // miser 100 jetons sur le 1
  Rouges p2(30);     // miser  30 jetons sur les rouges
  Pleine p3(20, 13); // miser  20 jetons sur le 13

  joueur1.set_strategie(&p1);
  joueur2.set_strategie(&p2);
  joueur3.set_strategie(&p3);

  RouletteAnglaise  jeu1;
  RouletteFrancaise jeu2;

  for (auto jeu : array<Roulette*, 2>({ &jeu1, &jeu2 })) {
    jeu->participe(joueur1);
    jeu->participe(joueur2);
    jeu->participe(joueur3); // c'est un autre joueur
    jeu->participe(joueur2); // c'est déjà un joueur du jeu
    simuler_jeu(*jeu);
  }

  return 0;
}
