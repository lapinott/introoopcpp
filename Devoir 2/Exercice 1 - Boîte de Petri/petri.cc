#include <iostream>
#include <utility> // pour la fonction swap
#include <string>
#include <vector>
using namespace std;

class Cellule
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

private:

    string nom;
    double taille;
    int energie;
    string couleur;

public:

    /*Cellule (string nom = "Pyrobacculum", double taille = 10, int energie = 5, string couleur = "verte") {
        this -> nom = nom;
        this -> taille = taille;
        this -> energie = energie;
        this -> couleur = couleur;
    }*/

    Cellule (string nom = "Pyrobacculum", double taille = 10, int energie = 5, string couleur = "verte") : nom{nom}, taille{taille}, energie{energie}, couleur{couleur} {}

    Cellule (Cellule const& c) : nom{c.nom}, taille{c.taille}, energie{c.energie}, couleur{c.couleur} {}

    void affiche () {
        cout << this -> nom << ", taille = " << this -> taille << " microns, énergie = " << this -> energie << ", couleur = " << this -> couleur << endl;
    }

    Cellule division () {
        Cellule newCell = *this;
        //Cellule newCell = Cellule (this -> nom, this -> taille, this -> energie, this -> couleur);
        this -> energie -= 1;
        if (newCell.couleur == "verte") newCell.couleur = "bleue";
        else if (newCell.couleur == "bleue") newCell.couleur = "rouge";
        else if (newCell.couleur == "rouge") newCell.couleur = "rose bonbon";
        else if (newCell.couleur == "violet") newCell.couleur = "verte";
        else newCell.couleur += " fluo";
        return newCell;
    }

    int getEnergie() {
        return this -> energie;
    }
};

class Petri {

private:

    vector<Cellule> population;

public:

    void ajouter (Cellule cellule) {
        this -> population.push_back(cellule);
    }

    void affiche () {
        for (Cellule cellule : this -> population) {
            cellule.affiche();
        }
    }

    void evolue () {

        int populationSize = this -> population.size();

        for (int i = 0; i < populationSize; i++) {
            Cellule newCell = this -> population[i].division();
            this -> ajouter (newCell);
        }

        populationSize = this -> population.size();

        for (Cellule c : this -> population) {
            if (this -> population[i].getEnergie() <= 0) {
                swap();
                this -> population.pop_back();
                //this -> population.erase(this -> population.begin() + i);
            }
        }

        for (int i = 0; i < populationSize; i++) {
            if (this -> population[i].getEnergie() <= 0) {
                //swap(this -> population[i], this -> population.back());
                //this -> population.pop_back();
                this -> population.erase(this -> population.begin() + i);
            }
        }
    }
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Petri assiette;

  assiette.ajouter(Cellule());
  assiette.ajouter(Cellule("PiliIV", 4, 1, "jaune"));
  cout << "Population avant évolution :" << endl;
  assiette.affiche();

  assiette.evolue();
  cout << "Population après évolution :" << endl;
  assiette.affiche();

  return 0;
}
