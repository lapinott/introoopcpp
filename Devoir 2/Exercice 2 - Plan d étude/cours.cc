#include <iostream>
#include <iomanip> // pour setfill
#include <string>
#include <vector>
using namespace std;

typedef string Day; // type pour d�finir les jous

void print_time(double); // fonction utile pour afficher les heures

class Time
/* Repr�sente le jour et l'heure d'un �v�nement.
 * Les heures sont repr�sent�es en double depuis minuit.
 * Par exemple 14:30 est repr�sent� 14.5.
 * La fonction-outil print_time permet d'afficher de telles heures.
 */
{
public:
  // Constructeur � partir du jour et de l'heure
  Time(Day jour, double heure)
    : day_(jour), hour_(heure) {
  }

  // Affichage
  void print() const {
    cout << day_ << " � ";
    print_time(hour_);
  }

  // Pour conna�tre le jour
  Day day() const {
    return day_;
  }

  // Pour conna�tre l'heure
  double hour() const {
    return hour_;
  }

private:
  Day day_;
  double hour_;
};

/* Fonction outil pour afficher les temps repr�sent�s en double
 * comme indiqu� ci-dessus.
 */
void print_time(double t)
{
  cout << setfill('0') << setw(2) << int(t)
       << setfill('0') << setw(1) << ":"
       << setfill('0') << setw(2) << int(60.0 * (t - int(t)));
}

/* Type utilis� pour identifier les cours.
 * Chaque cours aura en effet un identificateur unique ; par exemple "CS-101".
 */
typedef string CourseId;

/*******************************************
 * Compl�tez le programme � partir d'ici.
 *******************************************/

class Activity {

private:

    string lieu;
    double duree;
    Time horraire;

public:

    Activity (const string& lieu, const Day& jour, const double& heure, const double& duree) : lieu{lieu}, horraire{jour, heure}, duree{duree} {}
    //Activity () : horraire("", 0.) {};
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
                a.horraire.hour() < this -> horraire.hour() && a.horraire.hour() + a.getDuration() > this -> horraire.hour() ||
                this -> horraire.hour() < a.horraire.hour() && this -> horraire.hour() + this -> getDuration() > a.horraire.hour() ||
                a.horraire.hour() == this -> horraire.hour()
            )
        ) return true;
        else return false;
    }

    void print () const {
        cout << "le ";
        this -> horraire.print();
        cout << " en " << this -> lieu << ", dur�e ";
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
        cout << ". cr�dits : " << this -> credits;
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
        for (CourseId cId : vid) {
            if (findCourse(cId).conflicts(findCourse(id))) return true;
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
        for (const Course* cp : this -> vcp) {
            if (!this -> conflicts(cp -> getId(), vid)) {
                cp -> print();
                cout << endl;
                ++compatible;
            }
        }
        if (!compatible) cout << "Aucun cours n'est compatible avec la s�lection de cours." << endl;
    }
};

class Schedule {

private:

    vector<CourseId> cours;
    const StudyPlan* plan;

public:

    Schedule (const StudyPlan& plan) : plan{&plan} {}

    bool add_course (CourseId cId) {

        if (!this -> plan -> conflicts(cId, this -> cours)) {
            this -> cours.push_back(cId);
            return true;
        }
        else return false;
    }

    double computeDailyWorkload () const {
        double workload = 0.;
        for (const CourseId cId : this -> cours) {
            workload += this -> plan -> workload(cId);
        }
        return workload / 5;
    }

    int computeTotalCredits () const {
        int credits = 0;
        for (const CourseId cId : this -> cours) {
            credits += this -> plan -> credits(cId);
        }
        return credits;
    }

    void print () const {
        for (const CourseId cId : this -> cours) {
            this -> plan -> print(cId);
            cout << endl;
        }
        cout << "Total de cr�dits   : " << this -> computeTotalCredits() << endl;
        cout << "Charge journali�re : ";
        print_time(this -> computeDailyWorkload());
        cout << endl;
        cout << "Suggestions :" << endl;
        this -> plan -> printCourseSuggestions(this -> cours);
        cout << endl;
    }
};


/*******************************************
 * Ne rien modifier apr�s cette ligne.
 *******************************************/

int main()
{
  // Quelques activit�s
  Activity physicsLecture  ("Central Hall", "lundi",  9.25, 1.75);
  Activity physicsExercises("Central 101" , "lundi", 14.00, 2.00);

  Activity historyLecture  ("North Hall", "lundi", 10.25, 1.75);
  Activity historyExercises("East 201"  , "mardi",  9.00, 2.00);

  Activity financeLecture  ("South Hall",  "vendredi", 14.00, 2.00);
  Activity financeExercises("Central 105", "vendredi", 16.00, 1.00);

  // On affiche quelques informations sur ces activit�s
  cout << "L'activit� physicsLecture a lieu ";
  physicsLecture.print();
  cout << "." << endl;

  cout << "L'activit� historyLecture a lieu ";
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

  // Cr�ation d'un plan d'�tude
  StudyPlan studyPlan;
  Course physics("PHY-101", "Physique", physicsLecture, physicsExercises, 4);
  studyPlan.add_course(physics);
  Course history("HIS-101", "Histoire", historyLecture, historyExercises, 4);
  studyPlan.add_course(history);
  Course finance("ECN-214", "Finance" , financeLecture, financeExercises, 3);
  studyPlan.add_course(finance);

  // Premi�re tentative d'emploi du temps
  Schedule schedule1(studyPlan);
  schedule1.add_course(finance.getId());
  cout << "Emploi du temps 1 :" << endl;
  schedule1.print();

  /* On ne sait pas encore tr�s bien quoi faire : on essaye donc
   * sur une copie de l'emploi du temps pr�c�dent.
   */
  Schedule schedule2(schedule1);
  schedule2.add_course(history.getId());
  cout << "Emploi du temps 2 :" << endl;
  schedule2.print();

  // Un troisi�me essai
  Schedule schedule3(studyPlan);
  schedule3.add_course(physics.getId());
  cout << "Emploi du temps 3 :" << endl;
  schedule3.print();

  return 0;
}
