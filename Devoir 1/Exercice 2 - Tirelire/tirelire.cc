#include <iostream>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/

class Tirelire {

private:

    double montant;

public:

    double getMontant () {
        return this -> montant;
    }

    void afficher () {
        if (this -> montant == 0.) cout << "Vous etes sans le sous." << endl;
        else cout << "Vous avez : " << this -> montant << " euros dans votre tirelire." << endl;
    }

    void secouer () {
        if (this -> montant > 0.) cout << "Bing bing" << endl;
    }

    void remplir (double desSousSous) {
        if (desSousSous >= 0.) this -> montant += desSousSous;
    }

    void vider () {
        this -> montant = 0.;
    }

    void puiser (double desSousSous) {
        if (desSousSous > 0. && desSousSous > this -> montant) this -> montant = 0.;
        else if (desSousSous > 0.) this -> montant -= desSousSous;
    }

    bool montant_suffisant (double budget, double& solde) {
        if (budget > 0.) {
            if (budget <= this -> montant) {
                solde = this -> montant - budget;
                return true;
            }
            else {
                solde = budget - this -> montant;
                return false;
            }
        }
        else {
            solde = this -> montant;
            return true;
        }
    }

    double calculerSolde (double budget) {
        if (budget > 0.) return this -> montant - budget;
        else return this -> montant;
    }
};
//       =()=
//   ,/'\_||_
//   ( (___  `.
//   `\./  `=='
//          |||
//          |||
//          |||
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Tirelire piggy;

  piggy.vider();
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(20.0);
  piggy.secouer();
  piggy.afficher();

  piggy.remplir(550.0);
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(10.0);
  piggy.puiser(5.0);
  piggy.afficher();

  cout << endl;

  // le budget de vos vacances de rève.
  double budget;

  cout << "Donnez le budget de vos vacances : ";
  cin >> budget;

  // ce qui resterait dans la tirelire après les
  // vacances
  double solde(0.0);

  if (piggy.montant_suffisant(budget, solde)) {
    cout << "Vous êtes assez riche pour partir en vacances !"
         << endl
         << "Il vous restera " << solde << " euros"
         << " à la rentrée." << endl << endl;
    piggy.puiser(budget);
  } else {
    cout << "Il vous manque " << solde << " euros"
         << " pour partir en vacances !" << endl << endl;
  }
  return 0;
}
