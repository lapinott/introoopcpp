#include <iostream>
#include <iomanip> // pour setfill
#include <string>
#include <vector>
using namespace std;

typedef string Day; // type pour définir les jous

void print_time(double); // fonction utile pour afficher les heures

class Time
/* Représente le jour et l'heure d'un évènement.
 * Les heures sont représentées en double depuis minuit.
 * Par exemple 14:30 est représenté 14.5.
 * La fonction-outil print_time permet d'afficher de telles heures.
 */
{
public:
  // Constructeur à partir du jour et de l'heure
  Time(Day jour, double heure)
    : day_(jour), hour_(heure) {
  }

  // Affichage
  void print() const {
    cout << day_ << " à ";
    print_time(hour_);
  }

  // Pour connaître le jour
  Day day() const {
    return day_;
  }

  // Pour connaître l'heure
  double hour() const {
    return hour_;
  }

private:
  Day day_;
  double hour_;
};

/* Fonction outil pour afficher les temps représentés en double
 * comme indiqué ci-dessus.
 */
void print_time(double t)
{
  cout << setfill('0') << setw(2) << int(t)
       << setfill('0') << setw(1) << ":"
       << setfill('0') << setw(2) << int(60.0 * (t - int(t)));
}

/* Type utilisé pour identifier les cours.
 * Chaque cours aura en effet un identificateur unique ; par exemple "CS-101".
 */
typedef string CourseId;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/


    cout << ", durée ";


    cout << ". crédits : ";


      cout << "Aucun cours n'est compatible avec la sélection de cours." << endl;


    cout << "Total de crédits   : ";
    cout << "Charge journalière : ";
    cout << "Suggestions :" << endl;


/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Quelques activités
  Activity physicsLecture  ("Central Hall", "lundi",  9.25, 1.75);
  Activity physicsExercises("Central 101" , "lundi", 14.00, 2.00);

  Activity historyLecture  ("North Hall", "lundi", 10.25, 1.75);
  Activity historyExercises("East 201"  , "mardi",  9.00, 2.00);

  Activity financeLecture  ("South Hall",  "vendredi", 14.00, 2.00);
  Activity financeExercises("Central 105", "vendredi", 16.00, 1.00);

  // On affiche quelques informations sur ces activités
  cout << "L'activité physicsLecture a lieu ";
  physicsLecture.print();
  cout << "." << endl;

  cout << "L'activité historyLecture a lieu ";
  historyLecture.print();
  cout << "." << endl;

  if (physicsLecture.conflicts(historyLecture)) {
    cout << "physicsLecture est en conflit avec historyLecture."
         << endl;
  } else {
    cout << "physicsLecture n'est pas en conflit avec historyLecture."
         << endl;
  }
  cout << endl;

  // Création d'un plan d'étude
  StudyPlan studyPlan;
  Course physics("PHY-101", "Physique", physicsLecture, physicsExercises, 4);
  studyPlan.add_course(physics);
  Course history("HIS-101", "Histoire", historyLecture, historyExercises, 4);
  studyPlan.add_course(history);
  Course finance("ECN-214", "Finance" , financeLecture, financeExercises, 3);
  studyPlan.add_course(finance);

  // Première tentative d'emploi du temps
  Schedule schedule1(studyPlan);
  schedule1.add_course(finance.getId());
  cout << "Emploi du temps 1 :" << endl;
  schedule1.print();

  /* On ne sait pas encore très bien quoi faire : on essaye donc
   * sur une copie de l'emploi du temps précédent.
   */
  Schedule schedule2(schedule1);
  schedule2.add_course(history.getId());
  cout << "Emploi du temps 2 :" << endl;
  schedule2.print();

  // Un troisième essai
  Schedule schedule3(studyPlan);
  schedule3.add_course(physics.getId());
  cout << "Emploi du temps 3 :" << endl;
  schedule3.print();

  return 0;
}
