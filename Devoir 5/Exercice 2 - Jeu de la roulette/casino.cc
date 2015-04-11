#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;

/*******************************************
 * Completez le programme à partir d'ici.
 *******************************************/


  1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36

    cout << "Croupier : le numéro du tirage est le "

      cout << "Le joueur "
           << " a misé "
           << " et ";

        cout << "perd "
        cout << "gagne "

    cout << "Gain/perte du casino : "

    out << "Roulette anglaise";

    out << "Roulette française";


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
