#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

class Patient {

private:

	double masse;
	double hauteur;

public:

	Patient () {}

	void init (double poids, double taille) {
		double p = poids < 0 || taille < 0 ? 0. : poids;
		double t = poids < 0 || taille < 0 ? 0. : taille;
		this -> masse = p;
		this -> hauteur = t;
	}

	double imc () {
		return this -> hauteur == 0. ? 0. : this -> poids() / (this -> taille() * this -> taille());
	}

	void afficher () {
		cout << "Patient : " << poids() << " kg pour " << taille() << " m" << endl;
	}

	double poids () {
	    return this -> masse;
	}

	double taille () {
		return this -> hauteur;
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
  Patient quidam;
  double poids, taille;
  do {
    cout << "Entrez un poids (kg) et une taille (m) : ";
    cin >> poids >> taille;
    quidam.init(poids, taille);
    quidam.afficher();
    cout << "IMC : " << quidam.imc() << endl;
  } while (poids * taille != 0.0);
  return 0;
}
