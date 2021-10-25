#include "contact.h"
#include "date.h"
#include "interaction.h"
#include "gestioncontacts.h"
#include <iostream>
#include <string>

int RATE = 0; // Nombre de tests rate
int REUSSI = 0; // Nombre de tests reussi

using namespace std;

template <class T>
bool compareListContact(list<T> a, list<T> b){
    if (a.size() != b.size())
        return false;
     auto it1 = a.begin();
     auto it2 = b.begin();
     while(it1 != a.end() && it2 != b.end()){
         if (*it1 == *it2){
             it1++;
             it2++;
             continue;
         }
         return false;
     }
     return true;
}

template <class C>
/**
 * @brief genericTestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param a le premier élément à comparer avec le second
 * @param b le second élément à comparer avec le premier
 * @param verbose permet de dire si on affiche tous les tests qui on été validés. les tests raté sont toujours affichés. verbose est mis à "flase" par défaut
 */
void genericTestOutputFormat(string classTest, string s, C a, C b, bool verbose = false){
    if (a == b){
        if (verbose == true){
            cout << "Test de la classe " << classTest << ", " << s << " succeeded" << endl;
            cout << "First member is: " << a << "\nSecond member is: " << b << endl;
        }
        REUSSI++;
        } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test " << classTest << ", " << s << ", failed" << endl;
        cout << "First member is: " << a << "\nSecond member is: " << b << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        RATE++;
    }
}

template <class C>
/**
 * @brief genericTestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param a La première liste de classe à comparer
 * @param b La deuxième liste de classe à comparer
 * @param verbose permet de dire si on affiche tous les tests qui on été validés. les tests raté sont toujours affichés. verbose est mis à "flase" par défaut
 * Cette fonction permet de comparer 2 liste dont les éléments sont des classe en surchargeant la fonction par défaut
 */
void genericTestOutputFormat(string classTest, string s, list<C> a, list<C> b, bool verbose = false){
    if (compareListContact(a, b) == true){
        if (verbose == true){
            cout << "Test de la classe, " << classTest << ", " << s << ", succeeded" << endl;
            cout << "First member is: {\n";
            for (auto i : a)
                cout << i << "\n";
            cout << "}\nSecond member is: {\n";
            for (auto j : b)
                cout << j << "\n";
            cout << "}" << endl;
            }
        REUSSI++;
        } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test " << classTest << ", " << s << ", failed" << endl;
        cout << "First member is: {\n";
        for (auto i : a)
            cout << i << "\n";
        cout << "}\nSecond member is: {\n";
        for (auto j : b)
            cout << j << "\n";
        cout << "}" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        RATE++;
    }
}

/**
 * @brief genericTestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param s Le test que l'on effectue
 * @param a le premier élément à comparer avec le second
 * @param b le second élément à comparer avec le premier
 * @param verbose permet de dire si on affiche tous les tests qui on été validés. les tests raté sont toujours affichés. verbose est mis à "flase" par défaut
 * Surcharge de la fonction qui test lorsque 2 types sont identique pour pouvoir cast en string le résultat des getters
 */
void genericTestOutputFormat(string classTest, string s, string a, string b, bool verbose = false){
    if (a == b){
        if (verbose == true){
            cout << "Test de la classe, " << classTest << ", " << s << " succeeded" << endl;
            cout << "First member is: " << a << "\nSecond member is: " << b << endl;
        }
        REUSSI++;
    } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test de la classe, " << classTest << ", " << s << " failed" << endl;
        cout << "First member is: " << a << "\nSecond member is: " << b << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        RATE++;
    }
}

/**
 * @brief testContact Test des différentes méthodes de Contact.
 */
void testContact(){
    // Generic tests
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    Interaction i = Interaction("rdv aujourd'hui par tél., RAS", p);

    // Récupération de données
    string classTest = "Contact";

    genericTestOutputFormat(classTest, "recuperation du nom", p.getNom(), "Nom");
    genericTestOutputFormat(classTest, "recuperation du prenom", p.getPrenom(), "Prenom");
    genericTestOutputFormat(classTest, "recuperation de l'entreprise", p.getEntreprise(), "Entreprise");
    genericTestOutputFormat(classTest, "recuperation du telephone", p.getTelephone(), "06 52 48 61 34");
    genericTestOutputFormat(classTest, "recuperation de la photo", p.getPhoto(), "photo.jpg");
    genericTestOutputFormat(classTest, "recuperation du mail", p.getMail(), "mail");
    Date now = Date();
    genericTestOutputFormat(classTest, "recuperation de la date", p.getDateCrea(), now);
    now.~Date();


    // Modifications de données
    p.setNom("Nom2");
    p.setPrenom("Prenom2");
    p.setEntreprise("Entreprise2");
    p.setTelephone("06 45 79 85 31");
    p.setPhoto("photo2.jpg");
    p.setMail("mail2");
    genericTestOutputFormat(classTest, "modification du nom", p.getNom(), "Nom2");
    genericTestOutputFormat(classTest, "modification du prenom", p.getPrenom(), "Prenom2");
    genericTestOutputFormat(classTest, "modification de l'entreprise", p.getEntreprise(), "Entreprise2");
    genericTestOutputFormat(classTest, "modification du telephone", p.getTelephone(), "06 45 79 85 31");
    genericTestOutputFormat(classTest, "modification de la photo", p.getPhoto(), "photo2.jpg");
    genericTestOutputFormat(classTest, "modification du mail", p.getMail(), "mail2");
}

/**
 * @brief testInteraction permet de tester les méthodes d'intéractions
 */
void testInteraction(){

    string classTest = "interaction";
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    Interaction i = Interaction("rdv aujourd'hui par tél., RAS", p);

    // Récupération de données
    Date now = Date();
    string nowS = to_string(now.getJour()) + "/" + to_string(now.getMois()) + "/" + to_string(now.getAnnee());

    genericTestOutputFormat(classTest, "recuperation du contenu", i.getContenu(), "rdv aujourd'hui par tél., RAS");
    genericTestOutputFormat(classTest, "recuperation de la date", i.getDateCreation(), now);
    genericTestOutputFormat(classTest, "recuperation du contact", *i.getContact(), p);
    now.~Date();

    // Modifications de données
    i.setContenu("rdv interessant");
    genericTestOutputFormat(classTest, "recuperation du contenu", i.getContenu(), "rdv interessant");

    p.~Contact();
}

/**
 * @brief testTodo permet de tester les méthodes de Todo
 */
void testTodo(){
    string classTest = "todo";
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    Interaction i = Interaction("rdv aujourd'hui par tél., RAS", p);
    Date now = Date();
    Todo t = Todo("Rappeler", &i, &now);

    // Test des getter
    genericTestOutputFormat(classTest, "recuperation du contenu", t.getContenu(), "Rappeler");
    genericTestOutputFormat(classTest, "recuperation du contenu du tag", t.getDeadline(), now);
    genericTestOutputFormat(classTest, "recuperation de l'interaction", *t.getInteraction(), i);
    genericTestOutputFormat(classTest, "recuperation du tag de t", t.getTag(), true);


    // Test des setter
    t.setContenu("Rendez-vous");
    genericTestOutputFormat(classTest, "modification du contenu", t.getContenu(), "Rendez-vous");

    Date demain = Date(26, 10, 2021);
    t.setDeadline(demain);
    genericTestOutputFormat(classTest, "modification de la deadline", t.getDeadline(), demain);

    Todo t1 = Todo("Rentrez a la maison", &i);
    genericTestOutputFormat(classTest, "modification du tag", t1.getTag(), false);
    t1.setDeadline(now);
    genericTestOutputFormat(classTest, "recuperation du contenu du tag", t1.getDeadline(), now);
    genericTestOutputFormat(classTest, "modification du tag de t1", t1.getTag(), true);
}

/**
 * @brief testGestionContact permet de tester la classe gestion contact
 */
void testGestionContacts(){
    string classTest = "gestionContact";
    Contact p1 = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Contact p2 = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    Contact p3 = Contact("Florian", "Polier", "Netsle", "06 42 57 98 31", "photoFlorian.jpg", "florian.polier@mail.com");
    //Contact p4 = Contact("Mathias", "Fareau", "Axe", "06 52 46 80 13", "photoMathias.jpg", "mathias.flareau@mail.com");
    //Contact p5 = Contact("Alexandre", "Nirula", "Yamaha", "06 98 46 20 38", "photoAlexandre.jpg", "alexandre.nirula@mail.com");
    GestionContacts gc = GestionContacts();

    Date now = Date();

    genericTestOutputFormat(classTest, "recuperation de la liste de contact", gc.getContacts(), {});
    genericTestOutputFormat(classTest, "récupération de la date de la derniere suppression", gc.getDerniereSuppr(), now);

    gc.addContact(p1);
    genericTestOutputFormat(classTest, "ajout d'un contact dans la list", gc.getContacts(), {p1});

    list<Contact> lp = {p1, p2};
    gc.setContacts(lp);
    genericTestOutputFormat(classTest, "remplacement de la liste par une nouvelle", gc.getContacts(), lp);

    gc.supprContact(p2);
    genericTestOutputFormat(classTest, "suppression du contact p1 de la liste", gc.getContacts(), {p1});
    genericTestOutputFormat(classTest, "vérification de la mise à jour de la date de dernière suppression", gc.getDerniereSuppr(), now);

    gc.addContact(p3);
    gc.addContact(p2);
    gc.addContact(p1);
    genericTestOutputFormat(classTest, "ajout d'un contact dans la list", gc.getContacts(), {p1, p3, p2});
}

/**
 * @brief testGestionInteractions test mes dofférentes ùéthodes de GestionInteractions
 */
void testGestionInteractions(){
    string classTest = "gestionInteractions";

    Contact p1 = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Interaction i1 = Interaction("Rendez-vous", p1);
    Interaction i2 = Interaction("Rappeler", p1);

    GestionInteractions gi = GestionInteractions();
    Date now = Date();

    genericTestOutputFormat(classTest, "recuperation de gestionInteraction apres creation", gi.getInteractions(), {});
    genericTestOutputFormat(classTest, "recuperation de la date de derniere suppression", gi.getDernModif(), now);

    gi.addInteraction(i1);
    genericTestOutputFormat(classTest, "recuperation d'une interaction ajoutee", gi.getInteractions(), {i1});

    gi.setInteractions({i2, i1});
    genericTestOutputFormat(classTest, "recuperation d'une liste d'interaction", gi.getInteractions(), {i2, i1});

    gi.supprInteraction(i1);
    genericTestOutputFormat(classTest, "suppression d'une interaction", gi.getInteractions(), {i2});

    gi.addInteraction(i1);
    gi.addInteraction(i2);
    genericTestOutputFormat(classTest, "suppression d'une interaction", gi.getInteractions(), {i2, i1});
}

/**
* @brief testGestionTodos permet de faire des tests sur gestionTodos
*/
void testGestionTodos(){
    string classTest = "gestionTodos";
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    Interaction i = Interaction("rdv aujourd'hui par tél., RAS", p);
    GestionTodos gt = GestionTodos();
    Todo t = Todo("manger", &i);
    Todo t1 = Todo("boire", &i);
    const Date hier = Date(24, 10, 2021);
    Todo t2 = Todo("dormir", &i);

    genericTestOutputFormat(classTest, "recuperation de la list apres initialisation", gt.getTodos(), {});

    gt.addTodo(t);
    genericTestOutputFormat(classTest, "ajout d'un todo", gt.getTodos(), {t});

    gt.setTodos({t2, t1});
    genericTestOutputFormat(classTest, "remplacement de la liste des todos", gt.getTodos(), {t2, t1});

    gt.supprTodo(t1);
    genericTestOutputFormat(classTest, "suppression d'un todo", gt.getTodos(), {t2});

    gt.addTodo(t1);
    gt.addTodo(t2);
    genericTestOutputFormat(classTest, "remplacement de la liste des todos", gt.getTodos(), {t2, t1});
}

int main()
{
    testContact(); // Tests de la classe contact
    testInteraction(); // Tests de la classe interaction
    testTodo(); // Tests de la classe Todo
    testGestionContacts(); // Tests de la classe GestionContacts
    testGestionInteractions(); // Tests de la classe GestionsInteractions
    testGestionTodos(); // Tests de la class GestionTodos
    cout << "Nombre de tests: " << RATE + REUSSI << "\nNombre de tests valides: " << REUSSI << "\nNombre de tests rate: " << RATE << endl;
    return 0;
}
