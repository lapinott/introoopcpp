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

class Activity {

private:

    string lieu;
    double duree;
    Time horraire;

public:

    Activity (const string& lieu, const Day& jour, const double& heure, const double& duree) : lieu{lieu}, horraire{jour, heure}, duree{duree} {}
    Activity () : horraire("", 0.) {};
    Activity (const Activity& a) = delete;
    Activity operator = (Activity& a) = delete;

    string getLocation () const {
        return this -> lieu;
    }

    Time getTime () const {
        return this -> horraire;
    }

    double getDuration () const {
        return this -> duree;
    }

    bool conflicts (const Activity& a) const {
        if (
            a.horraire.day() == this -> horraire.day() &&
            (
                a.horraire.hour() + a.getDuration() > this -> horraire.hour() ||
                this -> horraire.hour() + this -> getDuration() > a.horraire.hour()
            )
        ) return true;
        else return false;
    }

    void print () const {
        cout << "le ";
        this -> horraire.print();
        cout << " en " << this -> lieu << ", durée ";
        print_time(this -> duree);
    }
};

class Course {

private:

    CourseId id;
    string nom;
    Activity cours;
    Activity ex;
    int credits;

public:

    Course (const CourseId& id, const string& nom, const Activity& cours, const Activity& ex, const int& credits) :
            id{id},
            nom{nom},
            cours{cours.getLocation(), cours.getTime().day(), cours.getTime().hour(), cours.getDuration()},
            ex{ex.getLocation(), ex.getTime().day(), ex.getTime().hour(), ex.getDuration()},
            credits{credits}
    {
        cout << "Nouveau cours : " << this -> id << endl;
    }

    Course (const Course& c) = delete;
    Course operator = (Course& c) = delete;

    ~Course () {
        cout << "Suppression du cours : " << this -> id << endl;
    }

    CourseId getId () const {
        return this -> id;
    }

    string getTitle () const {
        return this -> nom;
    }

    int getCredits () const {
        return this -> credits;
    }

    double workload () const {
        return this -> cours.getDuration() + ex.getDuration();
    }

    bool conflicts (const Activity& a) const {
        if (cours.conflicts(a) || ex.conflicts(a)) return true;
        else return false;
    }

    bool conflicts (const Course& c) const {
        if (this -> conflicts(c.cours) || this -> conflicts(c.ex)) return true;
        else return false;
    }

    void print () const {
        cout << this -> id << ": " << this -> nom << " - cours ";
        this -> cours.print();
        cout << ", exercices ";
        this -> ex.print();
        cout << ". crédits : " << this -> credits;
    }
};

class StudyPlan {

private:

    vector<const Course*> vcp;

    const Course& findCourse (const CourseId& cId) const {
        for (const Course* cp : this -> vcp) {
            if (cp -> getId() == cId) return *cp;
        }
    }

public:

    void add_course (const Course& c) {
        this -> vcp.push_back (&c);
    }

    bool conflicts (const CourseId id, vector<CourseId> vid) const {
        for (const Course* cp : this -> vcp) {
            if (cp -> getId() == id) {
                for (const Course* cp2 : this -> vcp) {
                    for (CourseId cId : vid) {
                        if (
                            cp2 -> getId() == cId &&
                            cp2 -> getId() != id &&
                            cp -> conflicts(*cp2)
                        ) return true;
                    }
                }
                break;
            }
        }
        return false;
    }

    void print (const CourseId& cId) const {
        for (const Course* cp : this -> vcp) {
            if (cp -> getId() == cId) cp -> print();
        }
    }

    int credits (const CourseId& cId) const {
        for (const Course* cp : this -> vcp) {
            if (cp -> getId() == cId) return cp -> getCredits();
        }
        return 0;
    }

    double workload (const CourseId& cId) const {
        for (const Course* cp : this -> vcp) {
            if (cp -> getId() == cId) return cp -> workload();
        }
        return 0.d;
    }

    void printCourseSuggestions (vector<CourseId> vid) const {
        int compatible = 0;
        bool conflit = false;
        for (const Course* cp : this -> vcp) {
            for (const CourseId cId : vid) {
                if (this -> conflicts(cId, vid)) conflit = true;
            }
            if (!conflit) {
                cp -> print();
                cout << endl;
                ++compatible;
                break;
            }
            else conflit = false;
        }
        if (!compatible) cout << "Aucun cours n'est compatible avec la sélection de cours." << endl;
    }
};

class Schedule {
    // Hello World
};






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
