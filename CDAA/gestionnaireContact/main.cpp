#include "contact.h"
#include "date.h"
#include "interaction.h"
#include "gestioncontacts.h"
#include "gestionbdd.h"
#include <iostream>
#include <string>
#include <functional>

#include "mainwindow.h"
#include <QApplication>

using namespace std;

int RATE = 0; // Nombre de tests rate
int REUSSI = 0; // Nombre de tests reussi

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
 * @brief TestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param a le premier élément à comparer avec le second
 * @param b le second élément à comparer avec le premier
 * @param verbose permet de dire si on affiche tous les tests qui on été validés. les tests raté sont toujours affichés. verbose est mis à "false" par défaut
 */
void TestOutputFormat(string classTest, string testName, C a, C b, bool verbose = false){
    if (a == b){
        if (verbose == true){
            cout << "Test de la classe " << classTest << ", " << testName << " succeeded" << endl;
            cout << "First member is: " << a << "\nSecond member is: " << b << endl;
        }
        REUSSI++;
        } else {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Test " << classTest << ", " << testName << ", failed" << endl;
            cout << "Premier membre est: " << a << "\nSecond membre est: " << b << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        RATE++;
    }
}

template <class C>
/**
 * @brief TestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param a La première liste de classe à comparer
 * @param b La deuxième liste de classe à comparer
 * @param verbose permet de dire si on affiche tous les tests qui on été validés. les tests raté sont toujours affichés. verbose est mis à "flase" par défaut
 * Cette fonction permet de comparer 2 liste dont les éléments sont des classe en surchargeant la fonction par défaut
 */
void TestOutputFormat(string classTest, string testName, list<C> a, list<C> b, bool verbose = false){
    if (compareListContact(a, b) == true){
        if (verbose == true){
            cout << "Test de la classe, " << classTest << ", " << testName << ", succeeded" << endl;
            cout << "First member is: {\n";
            for (auto i : a)
                cout << *i << "\n";
            cout << "}\nSecond member is: {\n";
            for (auto j : b)
                cout << *j << "\n";
            cout << "}" << endl;
            }
        REUSSI++;
        } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test " << classTest << ", " << testName << ", failed" << endl;
        cout << "Premier membre est: {\n";
        for (auto i : a)
            cout << *i << "\n";
        cout << "}\nSecond membre est: {\n";
        for (auto j : b)
            cout << *j << "\n";
        cout << "}" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        RATE++;
    }
}

/**
 * @brief TestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param s Le test que l'on effectue
 * @param a le premier élément à comparer avec le second
 * @param b le second élément à comparer avec le premier
 * @param verbose permet de dire si on affiche tous les tests qui on été validés. les tests raté sont toujours affichés. verbose est mis à "flase" par défaut
 * Surcharge de la fonction qui test lorsque 2 types sont identique pour pouvoir cast en string le résultat des getters
 */
void TestOutputFormat(string classTest, string testName, string a, string b, bool verbose = false){
    if (a == b){
        if (verbose == true){
            cout << "Test de la classe, " << classTest << ", " << testName << " succeeded" << endl;
            cout << "Premier membre est: " << a << "\nSecond membre est: " << b << endl;
        }
        REUSSI++;
    } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test de la classe, " << classTest << ", " << testName << " failed" << endl;
        cout << "First member is: " << a << "\nSecond member is: " << b << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        RATE++;
    }
}

/**
 * @brief ExceptionTestOutputFormat teste les exceptionsf de gestion interaction
 * @param testName Le nom du test
 * @param cont Le contact avec laquelle on teste
 * @param gest Le gestion contact
 * @param method La méthode que l'on veut utiliser
 * @param showForbiddenEntries Pour afficher les exceptions
 */
void ExceptionTestOutputFormat(string testName, Contact *cont, GestionContacts *gest, string method, bool showForbiddenEntries = false){
    bool caught = false;
    try {
        if (method == "add")
            gest->addContact(*cont);
        else if (method == "suppr")
            gest->supprContact(*cont);
    }  catch (const invalid_argument &e) {
        REUSSI++;
        caught = true;
        if (showForbiddenEntries == true)
            cerr << "Test de la classe gestionContact : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false) {
        cerr << "Test de la classe gestionContact, " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
        RATE++;
    }
}

/**
 * @brief ExceptionTestOutputFormat teste les exceptionsf de gestion interaction
 * @param testName Le nom du test
 * @param inter L'interaction avec laquelle on teste
 * @param gest Le gestion interaction
 * @param method La méthode que l'on veut utiliser
 * @param showForbiddenEntries Pour afficher les exceptions
 */
void ExceptionTestOutputFormat(string testName, Interaction *inter, GestionInteractions *gest, string method, bool showForbiddenEntries = false){
    bool caught = false;
    try {
        if (method == "add")
            gest->addInteraction(*inter);
        else if (method == "suppr")
            gest->supprInteraction(*inter);
    }  catch (const invalid_argument &e) {
        REUSSI++;
        caught = true;
        if (showForbiddenEntries == true)
            cerr << "Test de la class gestionInteraction : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false) {
        cerr << "Test de la classe gestionInteraction, " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
        RATE++;
    }
}

/**
 * @brief ExceptionTestOutputFormat teste les exceptionsf de gestion interaction
 * @param testName Le nom du test
 * @param todo L'interaction avec laquelle on teste
 * @param gest Le gestion interaction
 * @param method La méthode que l'on veut utiliser
 * @param showForbiddenEntries Pour montrer les interactions
 */
void ExceptionTestOutputFormat(string testName, Todo *todo, GestionTodos *gest, string method, bool showForbiddenEntries = false){
    bool caught = false;
    try {
        if (method == "add")
            gest->addTodo(*todo);
        else if (method == "suppr")
            gest->supprTodo(*todo);
    }  catch (const invalid_argument &e) {
        REUSSI++;
        caught = true;
        if (showForbiddenEntries == true)
            cerr << "Test de la classe gestionTodo : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false) {
        cerr << "Test de la classe gestionTodos, " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
        RATE++;
    }
}

/**
 * @brief ExceptionTestOutputFormat permet de mettre en evidence que créer une date avec des arguments invalide renvoie une erreur
 * @param testName Le nom du test
 * @param Largs La liste d'arguments pour le constructeur de date
 * @param showForbiddenEntries permet de montrer le message d'erreur
 */
void ExceptionTestOutputFormat(string testName, vector<int> Largs, bool showForbiddenEntries = false){
    bool caught = false;
    try {
        Date(Largs.at(0), Largs.at(1) , Largs.at(2));
    }  catch (const invalid_argument &e) {
        REUSSI++;
        caught = true;
        if (showForbiddenEntries == true)
            cerr << "Test du constructeur de la classe Date : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false){
        cerr << "Test du constructeur de la classe Date : " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
        RATE++;
    }
}

/**
 * @brief ExceptionTestOutputFormat permet de mettre en évidence que créer un contact avec des arguments invalide renvoie une erreur
 * @param testName Le nom du test
 * @param Largs La liste d'arguments pour le constructeur de date
 * @param showForbiddenEntries permet de montrer le message d'erreur
 */
void ExceptionTestOutputFormat(string testName, vector<string> Largs, bool showForbiddenEntries = false){
    bool caught = false;
    try {
        Contact d = Contact(Largs.at(0), Largs.at(1), Largs.at(2), Largs.at(3), Largs.at(4), Largs.at(5));
    }  catch (const invalid_argument &e) {
        REUSSI++;
        caught = true;
        if (showForbiddenEntries == true)
            cerr << "Test du constructeur de la classe Contact : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false){
        cerr << "Test du constructeur de la classe Contact : " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
        RATE++;
    }
}

/**
 * @brief ExceptionTestOutputFormat permet de mettre en évidence que créer une interaction avec des arguments invalide renvoie une erreur
 * @param testName Le nom du test
 * @param contenu Le contenu de l'interaction
 * @param c Le contact dont l'interaction avec lequel on interagit
 * @param showForbiddenEntries permet de montrer le message d'erreur
 */
void ExceptionTestOutputFormat(string testName, string contenu, Contact *c, bool showForbiddenEntries = false){
    bool caught = false;
    try {
        Interaction i = Interaction(contenu, *c);
    }  catch (const invalid_argument &e) {
        REUSSI++;
        caught = true;
        if (showForbiddenEntries == true)
            cerr << "Test du constructeur de la classe Interaction : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false){
        cerr << "Test du constructeur de la classe Interaction : " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
        RATE++;
    }
}

/**
 * @brief ExceptionTestOutputFormat permet de mettre en évidence que créer un todo avec des arguments invalide renvoie une erreur
 * @param testName Le nom du test
 * @param contenu Le contenu de l'interaction
 * @param i L'interaction dont le todo est issu
 * @param la date pour laquelle est l'interaction, par défaut la date courante
 * @param showForbiddenEntries permet de montrer le message d'erreur
 */
void ExceptionTestOutputFormat(string testName, string contenu, Interaction *i, Date d = Date(), bool showForbiddenEntries = false){
    bool caught = false;
    try {
        Todo t = Todo(contenu, i, d);
    }  catch (const invalid_argument &e) {
        REUSSI++;
        caught = true;
        if (showForbiddenEntries == true)
            cerr << "Test du constructeur de la classe Todo : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false){
        cerr << "Test du constructeur de la classe Todo : " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
        RATE++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                    Tests objets                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief testContact Test des différentes méthodes de Contact.
 */
void testContact(){
    // Generic tests
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    Interaction i = Interaction("rdv aujourd'hui par tél., RAS", p);

    // Récupération de données
    string classTest = "Contact";

    TestOutputFormat(classTest, "recuperation du nom", p.getNom(), "Nom");
    TestOutputFormat(classTest, "recuperation du prenom", p.getPrenom(), "Prenom");
    TestOutputFormat(classTest, "recuperation de l'entreprise", p.getEntreprise(), "Entreprise");
    TestOutputFormat(classTest, "recuperation du telephone", p.getTelephone(), "06 52 48 61 34");
    TestOutputFormat(classTest, "recuperation de la photo", p.getPhoto(), "photo.jpg");
    TestOutputFormat(classTest, "recuperation du mail", p.getMail(), "mail");
    Date now = Date();
    TestOutputFormat(classTest, "recuperation de la date", p.getDateCrea(), now);
    now.~Date();


    // Modifications de données
    p.setNom("Nom2");
    p.setPrenom("Prenom2");
    p.setEntreprise("Entreprise2");
    p.setTelephone("06 45 79 85 31");
    p.setPhoto("photo2.jpg");
    p.setMail("mail2");
    TestOutputFormat(classTest, "modification du nom", p.getNom(), "Nom2");
    TestOutputFormat(classTest, "modification du prenom", p.getPrenom(), "Prenom2");
    TestOutputFormat(classTest, "modification de l'entreprise", p.getEntreprise(), "Entreprise2");
    TestOutputFormat(classTest, "modification du telephone", p.getTelephone(), "06 45 79 85 31");
    TestOutputFormat(classTest, "modification de la photo", p.getPhoto(), "photo2.jpg");
    TestOutputFormat(classTest, "modification du mail", p.getMail(), "mail2");

    ExceptionTestOutputFormat("contact sans nom", {"", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail"});
    ExceptionTestOutputFormat("contact sans prenom", {"Nom", "", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail"});
    ExceptionTestOutputFormat("contact sans entreprise", {"Nom", "Prenom", "", "06 52 48 61 34", "photo.jpg", "mail"});
    ExceptionTestOutputFormat("contact sans numero", {"Nom", "Prenom", "Entreprise", "", "photo.jpg", "mail"});
    //ExceptionTestOutputFormat("contact sans photo", {"Nom", "Prenom", "Entreprise", "06 52 48 61 34", "", "mail"});
    ExceptionTestOutputFormat("contact sans mail", {"Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", ""});

    ExceptionTestOutputFormat("numero a 8 chiffres", {"Nom", "Prenom", "Entreprise", "06 48 61 34", "photo.jpg", "mail"});
    ExceptionTestOutputFormat("numero avec une lettre", {"Nom", "Prenom", "Entreprise", "06 l8 46 61 34", "photo.jpg", "mail"});

    p.setTelephone("0645134579");
    TestOutputFormat(classTest, "numero ou il manque tous les espaces", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("06451345 79");
    TestOutputFormat(classTest, "numero ou il n'y a que le dernier espace", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("064513 45 79");
    TestOutputFormat(classTest, "numero ou il y a 2 espaces", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("0645 13 45 79");
    TestOutputFormat(classTest, "numero ou il y a 3 espaces", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("0645 13 45 79");
    TestOutputFormat(classTest, "numero ou il manque le premier espace", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("06 4513 45 79");
    TestOutputFormat(classTest, "numero ou il manque le second espace", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("06 45 1345 79");
    TestOutputFormat(classTest, "numero ou il manque le troisieme espace", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("06 45 13 4579");
    TestOutputFormat(classTest, "numero ou il manque le quatrieme espace", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("06 4 5 13 45 79");
    TestOutputFormat(classTest, "numero ou il y a un espace en trop", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("0 6 4 5 13 45 79");
    TestOutputFormat(classTest, "numero ou il y a 2 espace en trop", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("06 451 3 45 79");
    TestOutputFormat(classTest, "numero ou il y a un espace au mauvais endroit", p.getTelephone(), "06 45 13 45 79");

    p.setTelephone("06 451 3 4579");
    TestOutputFormat(classTest, "numero ou il y a un espace au mauvais endroit et il en manque 1", p.getTelephone(), "06 45 13 45 79");

    /*
    Contact p2 = Contact("Nom2", "Prenom2", "Entreprise2", "06 48 31 55 46", "photo.jpg", "mail");
    Interaction i2 = Interaction("rdv demain par tél., RAS", p2);
    p.getInteractions().addInteraction(i2);
    cout << p.getInteractions().getInteractions().front()->getContenu();
    TestOutputFormat(classTest, "ajout d'une interaction dans le contact", p.getInteractions().getInteractions().front()->getContenu(), i.getContenu());
    */
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

    TestOutputFormat(classTest, "recuperation du contenu", i.getContenu(), "rdv aujourd'hui par tél., RAS");
    TestOutputFormat(classTest, "recuperation de la date", i.getDateCreation(), now);
    TestOutputFormat(classTest, "recuperation du contact", *i.getContact(), p);
    now.~Date();

    // Modifications de données
    i.setContenu("rdv interessant");
    TestOutputFormat(classTest, "recuperation du contenu", i.getContenu(), "rdv interessant");

    Interaction i2 = Interaction("apel aujourd'hui par tél., interessant", p);

    i2.setDateCreation(Date(25, 12, 2021)); // Ne devrait pas lancer d'exception
    TestOutputFormat(classTest, "comparaison entre une intreaction créée aujourd'hui et une le 25/12/2021", i<i2, true);

    ExceptionTestOutputFormat("interaction qui n'a pas de contenu", "", &p);

    p.setNom("Nom2");
    TestOutputFormat(classTest, "Changement du contact associe au todo doit etre modifie aussi dans l'interaction", i.getContact()->getNom(), p.getNom());

}

/**
 * @brief testTodo permet de tester les méthodes de Todo
 */
void testTodo(){
    string classTest = "todo";
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    Interaction i = Interaction("rdv aujourd'hui par tél., RAS", p);
    Date now = Date();
    Todo t = Todo("Rappeler", &i, Date());

    // Test des getter
    TestOutputFormat(classTest, "test d'initialisatiion, recuperation du contenu", t.getContenu(), "Rappeler");
    TestOutputFormat(classTest, "test d'initialisatiion, recuperation du contenu du tag", t.getDeadline(), now);
    TestOutputFormat(classTest, "test d'initialisatiion, recuperation de l'interaction", *t.getInteraction(), i);
    TestOutputFormat(classTest, "test d'initialisatiion, recuperation du tag de t", t.getTag(), true);

    i.setContenu("meeting");
    TestOutputFormat(classTest, "modification de l'interaction liee au Todo doit modifier la todo", t.getInteraction()->getContenu(), i.getContenu());
    // Test des setter
    t.setContenu("Rendez-vous");
    TestOutputFormat(classTest, "modification du contenu", t.getContenu(), "Rendez-vous");

    Date demain;
    try {
        demain = Date(26, 10, 2023); // Ne devrait pas lancer d'exception
    }  catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }
    t.setDeadline(demain);
    TestOutputFormat(classTest, "modification de la deadline", t.getDeadline(), demain);

    Todo t1 = Todo("Rentrez a la maison", &i);
    TestOutputFormat(classTest, "modification du tag", t1.getTag(), false);

    t1.setDeadline(now);
    TestOutputFormat(classTest, "modification de la deadline", t1.getDeadline() == demain, false);
    TestOutputFormat(classTest, "modification du tag de t1, bool tag", t1.getTag(), true);

    ExceptionTestOutputFormat("todo avec un contenu vide", "", &i);
    ExceptionTestOutputFormat("todo avec une pour date hier", "contenu", &i, Date(1, 10, 2021));

}

/**
 * @brief testDate permet de tester les méthodes de Date
 */
void testDate(){
    string classTest = "Date";
    time_t t = time(nullptr);
    tm* date = localtime(&t);
    Date d = Date();
    TestOutputFormat(classTest, "Initialisation par defaut, annee de la date courante", d.getAnnee(), date->tm_year + 1900);
    TestOutputFormat(classTest, "Initialisation par defaut, mois de la date courante", d.getMois(), date->tm_mon + 1);
    TestOutputFormat(classTest, "Initialisation par defaut, jour de la date courante", d.getJour(), date->tm_mday);

    Date noel2021 = Date(25, 12, 2021);
    TestOutputFormat(classTest, "Initialisation custom, annee de noel 2021", noel2021.getAnnee(), 2021);
    TestOutputFormat(classTest, "Initialisation custom, mois de noel 2021", noel2021.getMois(), 12);
    TestOutputFormat(classTest, "Initialisation custom, jour de noel 2021", noel2021.getJour(), 25);

    Date nouvelAn2022 = Date(01, 01, 2022);
    TestOutputFormat(classTest, "comparaison entre la date de noel 2021 et nouvel an 2022", noel2021 < nouvelAn2022, true);
    TestOutputFormat(classTest, "comparaison entre nouvel an 2022 et la date de noel 2021", nouvelAn2022 < noel2021, false);

    Date premierFevrier2022 = Date(01, 02, 2022);
    TestOutputFormat(classTest, "comparaison entre 01/02/2022 et 01/01/2022", nouvelAn2022 < premierFevrier2022, true);

    Date deuxJanvier2022 = Date(2, 1, 2022);
    TestOutputFormat(classTest, "comparaison entre 01/01/2022 et 02/01/2022", nouvelAn2022 < deuxJanvier2022, true);

    ExceptionTestOutputFormat("Creation de la date 32/01/2021", {32, 1, 2021});
    ExceptionTestOutputFormat("Creation de la date 32/01/2021", {4, 45, 2021});
    ExceptionTestOutputFormat("Creation de la date 32/01/2021", {30, 2, 2021});
    ExceptionTestOutputFormat("Creation de la date 32/01/2021", {29, 2, 2022});
    ExceptionTestOutputFormat("Creation de la date 32/01/2021", {31, 4, 2022});
}

/**
 * @brief testGestionContact permet de tester la classe gestion contact
 */
void testGestionContacts(){
    string classTest = "gestionContact";
    Contact p1 = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Contact p2 = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    Contact p3 = Contact("Florian", "Polier", "Netsle", "06 42 57 98 31", "photoFlorian.jpg", "florian.polier@mail.com");
    Contact p4 = Contact("Mathias", "Fareau", "Axe", "06 52 46 80 13", "photoMathias.jpg", "mathias.flareau@mail.com");
    GestionContacts gc = GestionContacts();

    Date now = Date();

    TestOutputFormat(classTest, "Initialisation la liste de contact", gc.getContacts(), {});
    TestOutputFormat(classTest, "Initialisation la date de la derniere suppression", gc.getDerniereSuppr(), now);

    try {
        gc.addContact(p1); // Should not throw exception
    }  catch (const invalid_argument &e) {
        cerr << "Premier ajout d'un contact " << e.what() << endl;
    }

    TestOutputFormat(classTest, "ajout d'un contact dans la list", gc.getContacts(), {&p1});

    list<Contact*> lp1 = {&p1, &p2};
    gc.setContacts(lp1);
    TestOutputFormat(classTest, "remplacement de la liste par une nouvelle qui a 2 contact ayant la meme date de creation", gc.getContacts(), lp1);

    Contact pers2 = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    pers2.setDateCrea(Date(25, 12, 2022));
    list<Contact*> lp2 = {&p1, &pers2};
    gc.setContacts(lp2);
    TestOutputFormat(classTest, "remplacement de la liste par une nouvelle qui a 2 contact ayant deux dates de creation differentes, triee", gc.getContacts(), lp2);

    list<Contact*> lp3 = {&pers2, &p1};
    gc.setContacts(lp3);
    lp3.sort([] (Contact *c1, Contact *c2){
        return (*c1).getDateCrea() < (*c2).getDateCrea();
    });
    TestOutputFormat(classTest, "remplacement de la liste par une nouvelle qui a 2 contact ayant deux dates de creation differentes, non triee", gc.getContacts(), lp3);

    gc.setContacts(lp1);
    gc.supprContact(p2);
    TestOutputFormat(classTest, "suppression du contact p1 de la liste", gc.getContacts(), {&p1});
    TestOutputFormat(classTest, "vérification de la mise à jour de la date de dernière suppression", gc.getDerniereSuppr(), now);

    gc.addContact(p3);
    gc.addContact(p2);
    ExceptionTestOutputFormat("ajout d'un contact deja dans la liste", &p1, &gc, "add");
    TestOutputFormat(classTest, "verification que l'ajout d'un contact deja dans la liste ne la modifie pas", gc.getContacts(), {&p1, &p3, &p2});

    ExceptionTestOutputFormat("suppression de contact qui n'est pas dans la liste", &p4, &gc, "suppr");
    TestOutputFormat(classTest, "verification que la suppression d'un contact qui n'est pas dans la liste ne la modifie pas", gc.getContacts(), {&p1, &p3, &p2});

    p1.setNom("Julien");
    TestOutputFormat(classTest, "verification que la modification d'un contact dans la liste est synchronise", gc.getContacts(), {&p1, &p3, &p2});
    ExceptionTestOutputFormat("ajout du contact deja dans la liste dont le nom a ete modifie", &p1, &gc, "add");

    Contact p5 = Contact("Romain", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    p5.setNom("Julien");
    ExceptionTestOutputFormat("ajout d'un contact deja dans la liste mais qui a ete cree comme different", &p5, &gc, "add");

    Contact p6 = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    ExceptionTestOutputFormat("ajout d'un contact qui a les memes attribus qu'un contact dans la liste", &p6, &gc, "add");
    TestOutputFormat(classTest, "verification que l'ajout d'un contact qui a les memes attributs qu'un contact dans la liste est refuse", gc.getContacts(),{&p1, &p3, &p2});

    ExceptionTestOutputFormat("suppression d'un contact qui a les memes attribus q'un contact dans la liste", &p6, &gc, "suppr");
    TestOutputFormat(classTest, "verification que la suppression d'un contact qui a lese memes attributs qu'un contact dans la liste ne la modifie pas", gc.getContacts(), {&p1, &p3, &p2});

    gc.supprContact(p2);
    Contact p7 = Contact("Alexandre", "Nirula", "Yamaha", "06 98 46 20 38", "photoAlexandre.jpg", "alexandre.nirula@mail.com");
    p7.setDateCrea(Date(25,12,2021));
    gc.addContact(p7);
    gc.addContact(p2);
    TestOutputFormat(classTest, "insertion d'un contact avec une date de creation plus avancees que les autres contact", gc.getContacts(), {&p1, &p3, &p2, &p7});
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

    TestOutputFormat(classTest, "Initialisation, recuperation de gestionInteraction apres creation", gi.getInteractions(), {});
    TestOutputFormat(classTest, "Initialisation, recuperation de la date de derniere suppression", gi.getDernModif(), now);

    try {
        gi.addInteraction(i1); // Should not throw exception
    } catch(const invalid_argument &e){
        cerr << e.what() << endl;
    }

    TestOutputFormat(classTest, "recuperation d'une interaction ajoutee", gi.getInteractions(), {&i1});

    gi.setInteractions({&i2, &i1});
    TestOutputFormat(classTest, "recuperation d'une liste d'interaction", gi.getInteractions(), {&i2, &i1});

    gi.supprInteraction(i1);
    TestOutputFormat(classTest, "suppression d'une interaction", gi.getInteractions(), {&i2});

    gi.addInteraction(i1);

    ExceptionTestOutputFormat("Ajout d'une interaction deja dans la liste", &i2, &gi, "add");
    TestOutputFormat(classTest, "verification que l'ajout d'une interaction deja dans la liste ne la modifie pas", gi.getInteractions(), {&i2, &i1});

    Interaction i3 = Interaction("Rappeler", p1);
    ExceptionTestOutputFormat("ajout d'une interaction qui a les memes attributs qu'une interaction dans la liste", &i3, &gi, "add");
    TestOutputFormat(classTest, "verification que l'ajout d'une interaction qui a les memes attribus qu'une interaction dans la liste ne la modifie pas", gi.getInteractions(), {&i2, &i1});

    ExceptionTestOutputFormat("suppression d'une interaction qui n'est pas dans la liste mais qui a les memes attributs qu'une interaction dans la liste", &i3, &gi, "suppr");
    TestOutputFormat(classTest, "verification que la suppression d'une interaction qui a les memes attribus qu'une interaction dans la liste ne la modifie pas", gi.getInteractions(), {&i2, &i1});

    Interaction i4 = Interaction("interaction!", p1);
    ExceptionTestOutputFormat("suppression d'une interaction qui n'est pas dans la liste", &i4, &gi, "suppr");
    TestOutputFormat(classTest, "verification que la suppression d'une interaction qui n'est pas dans la liste ne la modifie pas", gi.getInteractions(), {&i2, &i1});

    i2.setDateCreation(Date(25, 12, 2021));
    list<Interaction*> li = {&i1, &i2};
    gi.setInteractions(li);
    TestOutputFormat(classTest, "remplacement de la liste par une liste d'interaction triee", gi.getInteractions(), li);

    list<Interaction*> li2 = {&i2, &i1};
    gi.setInteractions(li2);
    li2.sort([] (Interaction* i1, Interaction* i2){
        return i1->getDateCreation() < i2->getDateCreation();
    });
    TestOutputFormat(classTest, "remplacement de la liste par une liste d'interaction non triee", gi.getInteractions(), li2);

    Interaction i5 = Interaction("travailler", p1);
    i5.setDateCreation(Date(24, 12, 2021));
    gi.addInteraction(i5);
    TestOutputFormat(classTest, "ajout d'une interaction qui n'a pas ete creee en dernier", gi.getInteractions(), {&i1, &i5, &i2});
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
    //const Date hier = Date(24, 10, 2021);
    Todo t2 = Todo("dormir", &i);

    TestOutputFormat(classTest, "recuperation de la list apres initialisation", gt.getTodos(), {});

    gt.addTodo(t); // Should not raise exception
    TestOutputFormat(classTest, "ajout d'un todo", gt.getTodos(), {&t});

    gt.setTodos({&t2, &t1});
    TestOutputFormat(classTest, "remplacement de la liste des todos", gt.getTodos(), {&t2, &t1});

    gt.supprTodo(t1);
    TestOutputFormat(classTest, "suppression d'un todo", gt.getTodos(), {&t2});

    gt.addTodo(t1); // Should not raise exception
    ExceptionTestOutputFormat("ajout d'un todo deja dans la liste", &t2, &gt, "add");
    TestOutputFormat(classTest, "remplacement de la liste des todos", gt.getTodos(), {&t2, &t1});

    try {
        t2.setDeadline(Date(25, 12, 2021));
    }  catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }
    TestOutputFormat(classTest, "Changement de deadline d'un todo dans la liste", gt.getTodos(), {&t2, &t1});

    Todo t3 = Todo("boire", &i);
    try {
        t3.setDeadline(Date(25, 12, 2021));
        gt.addTodo(t3);
    }  catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }
    TestOutputFormat(classTest, "verification que l'ajout dans la liste d'un todo deja dans la liste mais qui a une date qui est differente d'aujourd'hui est bien ajoute", gt.getTodos(), {&t1, &t2, &t3});

    Todo t4 = Todo("boire", &i);
    ExceptionTestOutputFormat("Ajout d'un todo avec les memes attributs d'un deja dans la liste", &t4, &gt, "add");
    TestOutputFormat(classTest, "verification que l'ajout dans la liste d'un autre todo avec les memes attributs qu'un todo dans la liste n'est pas ajoute", gt.getTodos(), {&t1, &t2, &t3});

    Todo t5 = Todo("detente", &i);
    ExceptionTestOutputFormat("suppression d'un todo qui n'est pas dans la liste", &t5, &gt, "suppr");
    TestOutputFormat(classTest, "verification que la suppression d'un todo qui n'est pas dans la liste ne la modifie pas", gt.getTodos(), {&t1, &t2, &t3});

    ExceptionTestOutputFormat("suppression d'un todo qui n'est pas dans la liste mais qui a les memes attribu qu'un todo dans la liste", &t4, &gt, "suppr");
    TestOutputFormat(classTest, "verification que la suppression d'un element qui n'est pas dans la liste mais qui a les memes attributs qu'un todo dans la listene la modifie pas", gt.getTodos(), {&t1, &t2, &t3});

    t5.setDeadline(Date(25,12,2021));
    list<Todo*> lt = {&t4, &t5};
    gt.setTodos(lt);
    TestOutputFormat(classTest, "remplacement de la liste de todo par une liste de todo triee", gt.getTodos(), lt);

    list<Todo*> lt2 = {&t5, &t4};
    gt.setTodos(lt2);
    lt2.sort([] (Todo* t1, Todo* t2){
        return t1->getDeadline() < t2->getDeadline();
    });
    TestOutputFormat(classTest, "remplacement de la liste de todo par une liste de todo non triee", gt.getTodos(), lt2);

    Todo t6 = Todo("revenir", &i, Date(24,12,2021));
    gt.addTodo(t6);
    TestOutputFormat(classTest, "ajout d'un todo qui n'a pas la deadline la plus vieille", gt.getTodos(), {&t4, &t6, &t5});
}

/**
 * @brief testsObjets Les tests sur la partie c++ du projet
 */
void testsObjets(){
    testContact(); // Tests de la classe contact
    testInteraction(); // Tests de la classe interaction
    testTodo(); // Tests de la classe Todo
    testDate(); // Tests de la classe Date
    //testGestionContacts(); // Tests de la classe GestionContacts
    //testGestionInteractions(); // Tests de la classe GestionsInteractions
    //testGestionTodos(); // Tests de la class GestionTodos

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                    Base de donnée                                                               ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief checkSelect permet de vérifier la bonne sélection d'un sélect dans la table contact
 * @param nomTest Le nom du test que l'on effectue
 * @param resSelect Le résultat du select
 * @param listeContact Les contacts que le sélect devrait renvoyer
 */
void checkSelect(string nomTest, list<Contact> resSelect, list<Contact> listeContact){
    if (resSelect.size() != listeContact.size()){
        RATE++;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Fail du test: " << nomTest << endl << "La selection contient moins de contact que ce qui a ete insere" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return;
    }
    for (list<Contact>::iterator select = resSelect.begin(), contact = listeContact.begin(); select != resSelect.end(); select++, contact++){
        if (!(*select == *contact)){
            RATE++;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Fail du test: " << nomTest << endl << "Le select ne contient pas le contact" << endl;
            cout << "Select:  " << *select << endl << "Contact: " << *contact << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return;
        }
    }
    REUSSI++;
}

/**
 * @brief checkSelect permet de vérifier la bonne sélection d'un sélect dans la table interaction
 * @param nomTest Le nom du test que l'on effectue
 * @param resSelect Le résultat du select
 * @param listeInteraction Les Interactions que le sélect devrait renvoyer
 */
void checkSelect(string nomTest, list<Interaction> resSelect, list<Interaction> listInteraction){
    if (resSelect.size() != listInteraction.size()){
        RATE++;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Fail du test: " << nomTest << endl << "La selection contient moins d'interaction que ce qui a ete insere" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return;
    }
    for (list<Interaction>::iterator select = resSelect.begin(), interaction = listInteraction.begin(); select != resSelect.end(); select++, interaction++){

        if ((*select).getContenu() != (*interaction).getContenu() || !((*select).getDateCreation() == (*interaction).getDateCreation())){
            RATE++;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Fail du test: " << nomTest << endl << "Le select ne contient pas l'interaction" << endl;
            cout << "Select:  " << *select << endl << "Interaction: " << *interaction << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return;
        }
    }
    REUSSI++;
}

/**
 * @brief checkSelect permet de vérifier la bonne sélection d'un sélect dans la table todo
 * @param nomTest Le nom du test que l'on effectue
 * @param resSelect Le résultat du select
 * @param listeTodo Les Todos que le sélect devrait renvoyer
 */
void checkSelect(string nomTest, list<Todo> resSelect, list<Todo> listeTodo){
    if (resSelect.size() != listeTodo.size()){
        RATE++;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Fail du test: " << nomTest << endl << "La selection contient moins de todo que ce qui a ete insere" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return;
    }
    for (list<Todo>::iterator select = resSelect.begin(), todo = listeTodo.begin(); select != resSelect.end(); select++, todo++){
        if (!(*select == *todo)){
            RATE++;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Fail du test: " << nomTest << endl << "Le select ne contient pas le todo" << endl;
            cout << "Select:  " << *select << endl << "Todo: " << *todo << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return;
        }
    }
    REUSSI++;
}

/**
 * @brief checkTables permet de vérifier de l'insertion d'un Contact dans la base de donnée en faisant un select manuellement dessus et le comparant à ce qui a été inséré
 * @param nomTest Le nom du test
 * @param gdb La base de donnée
 * @param lContenu La liste de contact insérée
 */
void checkTables(string nomTest, GestionBDD *gdb, list<Contact> lContenu){
    QSqlQuery q("SELECT nom, prenom, entreprise, telephone, photo, mail FROM Contact");
    if (!q.exec())
        throw invalid_argument("Impossible de faire un select sur la table Contact");
    else{
        for (auto c = lContenu.begin(); q.next() == true; c++){
            //cout << "Dans le " + nomTest + " " << endl << "Il y a " + to_string(gdb->countTable("Contact")) + " element dans la table Contact" << endl << *c << endl;
            if (q.value(0).toString().toStdString() != c->getNom() ||
                q.value(1).toString().toStdString() != c->getPrenom() ||
                q.value(2).toString().toStdString() != c->getEntreprise() ||
                q.value(3).toString().toStdString() != c->getTelephone() ||
                q.value(4).toString().toStdString() != c->getPhoto() ||
                q.value(5).toString().toStdString() != c->getMail()
                    ){
                RATE++;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "Fail du test " << nomTest << " : La table ne contient pas d'element correspondant au contact" << endl;
                cout << "query || contact" << endl;
                cout << q.value(0).toString().toStdString() << " || " << c->getNom() << endl;
                cout << q.value(1).toString().toStdString() << " || " << c->getPrenom() << endl;
                cout << q.value(2).toString().toStdString() << " || " << c->getEntreprise() << endl;
                cout << q.value(3).toString().toStdString() << " || " << c->getTelephone() << endl;
                cout << q.value(4).toString().toStdString() << " || " << c->getPhoto() << endl;
                cout << q.value(5).toString().toStdString() << " || " << c->getMail() << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                return;
            }
        }
    }
    REUSSI++;
    gdb->clearTables(); // Il faut nettoyer les tables sinon les éléments de la liste ne correspondent pas à ceux de la table et faussent les résultats
}

/**
 * @brief checkTables permet de vérifier de l'insertion d'une Interaction dans la base de donnée en faisant un select manuellement dessus et le comparant à ce qui a été inséré
 * @param nomTest Le nom du test
 * @param gdb La base de donnée
 * @param lInteraction La liste d'interaction insérée
 */
void checkTables(string nomTest, GestionBDD *gdb, list<Interaction> lInteraction){
    QSqlQuery q("SELECT * FROM Interaction");
    if (!q.exec())
        throw invalid_argument("Impossible de faire un select sur la table Interaction");
    else{
        for (list<Interaction>::iterator i = lInteraction.begin(); q.next() == true; i++){
            map<string, list<string>> tmp;
            tmp["id"] = {q.value(3).toString().toStdString()};
            Contact contact = gdb->selectQueryContact(tmp).front();
            if (q.value(1).toString().toStdString() != i->getContenu() ||
                q.value(2).toString().toStdString() != i->getDateCreation().affichage() ||
                !(contact == *(i->getContact()))
                    ){
                RATE++;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "Fail du test " << nomTest << " : La table ne contient pas d'element correspondant a l'interaction" << endl;
                cout << "Valeures e la query || Valeures de l'interaction" << endl;
                cout << "Contenu: " << q.value(1).toString().toStdString()  << " || " << i->getContenu() << endl;
                cout << "Date: " << q.value(2).toString().toStdString()  << " || " << i->getDateCreation().affichage() << endl;
                cout << "Contact: " << contact  << " || " << i->getContact() << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                gdb->clearTables();
                return;
            }
        }
    }
    REUSSI++;
    gdb->clearTables(); // Il faut nettoyer les tables sinon les éléments de la liste ne correspondent pas à ceux de la table et faussent les résultats
}

/**
 * @brief checkTables Vérifie le contenu de la table Todo
 * @param nomTest Le nom du test
 * @param gdb La base de donnée
 * @param lTodo La liste contenant les todos
 */
void checkTables(string nomTest, GestionBDD *gdb, list<Todo> lTodo){
    QSqlQuery q("SELECT * FROM Todo");
    if (!q.exec())
        throw invalid_argument("Impossible de faire un select sur la table Todo");
    else{
        for (list<Todo>::iterator todo = lTodo.begin(); q.next() == true; todo++){
            if (q.value(1).toString().toStdString() != todo->getContenu() ||
                q.value(2).toString().toStdString() != todo->getDeadline().affichage() //||
                //q.value(3).toString().toStdString() != todo->().affichage() ||
                    ){
                RATE++;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "Fail du test " << nomTest << " : La table ne contient pas d'element correspondant a l'interaction" << endl;
                cout << "Valeures e la query || Valeures de l'interaction" << endl;
                cout << "Contenu: " << q.value(1).toString().toStdString()  << " || " << todo->getContenu() << endl;
                cout << "Date: " << q.value(2).toString().toStdString()  << " || " << todo->getDeadline().affichage() << endl;
                //cout << "Contact: " << contact  << " || " << todo->getContact() << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                gdb->clearTables();
                return;
            }
        }
    }
    REUSSI++;
    gdb->clearTables(); // Il faut nettoyer les tables sinon les éléments de la liste ne correspondent pas à ceux de la table et faussent les résultats
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                    Tests d'insertions                                                           ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief unitTestInsert Test sur 1 insert dans Contact
 * @param c Le contact que l'on insère dans la base de donnée
 */
void testUniqueInsertContact(GestionBDD *gdb, Contact c){
    gdb->insertData(c);
    checkTables("Unique insert Contact", gdb, {c});
}

/**
 * @brief testMultipleInsert test sur plusieurs insertions dans Contact
 * @param l Liste contenant les contacts
 */
void testMultipleInsertContact(GestionBDD *gdb, list<Contact> lContact){
    for (auto &it : lContact)
        gdb->insertData(it);
    checkTables("Multiple insert Contact", gdb, lContact);
}

/**
 * @brief testUniqueInsertInteraction teste la méthode insertData de GestionBDD en insérant une unique interaction
 * @param gdb La base de donnée
 * @param i L'interaction que l'on insère
 */
void testUniqueInsertInteraction(GestionBDD *gdb, Interaction i){
    gdb->insertData(*i.getContact());
    gdb->insertData(i);
    checkTables("Unique insert Interaction", gdb, {i});
}

/**
 * @brief testMultipleInsertInteraction teste la méthode insertData en insérant plusieurs interactions
 * @param gdb La base de donnée
 * @param lInteraction Liste contenant les interactions
 */
void testMultipleInsertInteraction(GestionBDD *gdb, list<Interaction> lInteraction){
    for (auto &it : lInteraction){
        gdb->insertData(*it.getContact());
        gdb->insertData(it);
    }
    checkTables("Insertion de plusieurs interactions", gdb, lInteraction);
}

/**
 * @brief testUniqueInsertTodo teste la méthode insertData en insérant un Todo
 * @param gdb La base de donnée
 * @param t Le todo que l'on insère
 */
void testUniqueInsertTodo(GestionBDD *gdb, Todo t){
    gdb->insertData(*t.getInteraction()->getContact());
    gdb->insertData(*t.getInteraction());
    gdb->insertData(t);
    checkTables("Unique insert Todo", gdb, {t});
}

/**
 * @brief testMultipleInsertTodo teste la méthode insertData en insérant plusieurs Todo
 * @param gdb La base de donnée
 * @param listeTodo Liste contenant tous les Todo
 */
void testMultipleInsertTodo(GestionBDD *gdb, list<Todo> listeTodo){
    for (auto &it : listeTodo){
        gdb->insertData(*it.getInteraction()->getContact());
        gdb->insertData(*it.getInteraction());
        gdb->insertData(it);
    }
    checkTables("Insertion de plusieurs Todo", gdb, listeTodo);
}

/**
 * @brief testInsert sont les tests qui concernent les insertions
 * @param gdb La base de donnée
 */
void testInsert(GestionBDD *gdb){
    Contact thomas = Contact("Ratu", "Thomas", "Total", "06 52 48 61 34", "photoThomas.jpg", "thomas.rate@mail.com");
    Contact jules = Contact("Siba", "Jules", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    Interaction tel = Interaction("rdv aujourd'hui par tel., RAS", thomas);
    Interaction visite = Interaction("visite en visio, rappeler", jules);
    Todo attendreAppel = Todo("Attendre d'etre rappele", &tel);
    Todo appel = Todo("Appeler dans 2 jours si il n'y a pas de nouvelle", &visite);

    testUniqueInsertContact(gdb, thomas);
    testMultipleInsertContact(gdb, {thomas, jules});
    testUniqueInsertInteraction(gdb, tel);
    testMultipleInsertInteraction(gdb, {tel, visite});
    testUniqueInsertTodo(gdb, attendreAppel);
    testMultipleInsertTodo(gdb, {attendreAppel, appel});
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                    Tests de selection                                                           ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief testSelectStarContact Execute une selection avec * pour recuperer tous les contacts dans la bdd
 * @param gdb La base de donnée
 * @param contactBDD Les contacts dans la base de donnée
 */
void testSelectStar(GestionBDD *gdb, list<Contact> contactBDD){
    list<Contact> result = gdb->selectQueryContact();
    checkSelect("Select tout de Contact sans condition", result, contactBDD);
}

/**
 * @brief testSelectStarContact Execute une selection avec * pour recuperer tous les contacts dans la bdd
 * @param gdb La base de donnée
 * @param interactionBDD Les contacts dans la base de donnée
 */
void testSelectStar(GestionBDD *gdb, list<Interaction> interactionBDD){
    list<Interaction> result = gdb->selectQueryInteraction();
    checkSelect("Select tout de Interaction sans condition", result, interactionBDD);
}

/**
 * @brief testSelectStarContact Execute une selection avec * pour recuperer tous les contacts dans la bdd
 * @param gdb La base de donnée
 * @param todoBDD Les contacts dans la base de donnée
 */
void testSelectStar(GestionBDD *gdb, list<Todo> todoBDD){
    list<Todo> result = gdb->selectQueryTodo();
    checkSelect("Select tout de Todo sans condition", result, todoBDD);
}

/**
 * @brief testSelectUniqueContactCondition execute un sélect dans la base de donnée avec une condition alors qu'elle ne contient que 1 contact
 * @param gdb La base de donnée
 * @param table La table dans laquelle on exécute un sélect
 * @param condition La condition pour sélectionner le bon contact
 * @param contactBDD Le contact dans la base de donnée
 * @param nomTest Le nom du test
 */
void testSelectUniqueContactCondition(GestionBDD *gdb, map<string, list<string>> condition, list<Contact> contactBDD, string nomTest){
    list<Contact> result= gdb->selectQueryContact(condition);
    checkSelect(nomTest, result, contactBDD);
}

/**
 * @brief testSelectPlusieursContactCondition execute un sélect dans la base de donnée avec une/des contision(s) alors qu'elle contient plusieurs contact
 * @param gdb La base de donnée
 * @param table La table dans laquelle on fait un sélect
 * @param condition La/les condition(s) pou récupérer les contacts
 * @param contactBDD Les contacts qui sont dans la base de donnée
 * @param nomTest Le nom du test
 */
void testSelectPlusieursContactCondition(GestionBDD *gdb, map<string, list<string>> condition, list<Contact> contactBDD, string nomTest){
    list<Contact> result = gdb->selectQueryContact(condition);
    checkSelect(nomTest, result, contactBDD);
}

void testSelectUniqueInteractionCondition(GestionBDD *gdb, map<string, list<string>> condition, list<Interaction> interactionBDD, string nomTest){
    list<Interaction> res = gdb->selectQueryInteraction(condition);
    checkSelect(nomTest, res, interactionBDD);
}

void testSelectUniqueTodoCondition(GestionBDD *gdb, map<string, list<string>> condition, list<Todo> todoBDD, string nomTest){
    list<Todo> res = gdb->selectQueryTodo(condition);
    checkSelect(nomTest, res, todoBDD);
}

/**
 * @brief testSelect sont les tests qui concernent les selections
 * @param gdb La base de donnée
 */
void testSelect(GestionBDD *gdb){
    Contact thomas = Contact("Ratu", "Thomas", "Total", "06 52 48 61 34", "photoThomas.jpg", "thomas.ratu@mail.com");
    Contact jules = Contact("Siba", "Jules", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    list<Contact> lContactBDD = {thomas};

    Interaction tel = Interaction("rdv aujourd'hui par tel., RAS", thomas);
    Interaction meeting = Interaction("meeting avec les devs", thomas);
    list<Interaction> lInteractionBDD = {tel, meeting};

    Todo attendreAppel = Todo("Attendre d'etre rappele", &tel);
    Todo appel = Todo("Appeler dans 2 jours si il n'y a pas de nouvelle", &tel);
    Todo edt = Todo("Faire un emploi du temps", &meeting, Date(14,12,2021));
    list<Todo> lTodoBDD = {attendreAppel, appel, edt};

    gdb->insertData(thomas);
    gdb->insertData(tel);
    gdb->insertData(meeting);
    gdb->insertData(attendreAppel);
    gdb->insertData(appel);
    gdb->insertData(edt);

    testSelectStar(gdb, lContactBDD);

    gdb->insertData(jules);
    lContactBDD.push_back(jules);
    testSelectStar(gdb, lContactBDD);

    testSelectStar(gdb, lInteractionBDD);
    testSelectStar(gdb, lTodoBDD);

    testSelectUniqueContactCondition(gdb, {{"nom", {"Ratu"}}}, {thomas}, "Select avec condition sur le nom");
    testSelectUniqueContactCondition(gdb, {{"prenom", {"Thomas"}}}, {thomas}, "Select avec condition sur le prenom");
    testSelectUniqueContactCondition(gdb, {{"entreprise", {"Total"}}}, {thomas}, "Select avec condition sur le entreprise");
    testSelectUniqueContactCondition(gdb, {{"telephone", {"06 52 48 61 34"}}}, {thomas}, "Select avec condition sur le telephone");
    testSelectUniqueContactCondition(gdb, {{"photo", {"photoThomas.jpg"}}}, {thomas}, "Select avec condition sur le photo");
    testSelectUniqueContactCondition(gdb, {{"mail", {"thomas.ratu@mail.com"}}}, {thomas}, "Select avec condition sur le mail");
    testSelectUniqueContactCondition(gdb, {{"nom", {"Ratu"}},
                                                      {"prenom", {"Thomas"}},
                                                      {"entreprise", {"Total"}},
                                                      {"telephone", {"06 52 48 61 34"}},
                                                      {"photo", {"photoThomas.jpg"}},
                                                      {"mail", {"thomas.ratu@mail.com"}}},
                                     {thomas}, "Select avec condition sur le nom, prenom, entreprise, tehelphone, photo, mail");
    testSelectUniqueContactCondition(gdb, {{"nom", {"Siba"}}}, {jules}, "Select avec condition sur le nom");
    testSelectUniqueContactCondition(gdb, {{"id", {"1"}}}, {thomas}, "Select avec condition sur l'id");

    testSelectPlusieursContactCondition(gdb, {{"nom", {"Ratu", "Siba"}}}, {thomas, jules}, "Select avec des conditions sur 2 contact differents");

    testSelectUniqueInteractionCondition(gdb, {{"contenu", {"rdv aujourd''hui par tel., RAS"}}}, {tel}, "Select Interaction avec condition sur le contenu");
    testSelectUniqueInteractionCondition(gdb, {{"idContact", {"1"}}}, {tel, meeting}, "Select Interaction avec condition sur le contact");
    testSelectUniqueInteractionCondition(gdb, {{"id", {"1"}}}, {tel}, "Select Interaction avec condition sur l'id");

    testSelectUniqueTodoCondition(gdb, {{"contenu", {"Attendre d''etre rappele"}}}, {attendreAppel}, "Select Todo avec condition sur le contenu");
    testSelectUniqueTodoCondition(gdb, {{"deadline", {attendreAppel.getDeadline().affichage()}}}, {attendreAppel, appel}, "Select Todo avec condition sur la date");
    testSelectUniqueTodoCondition(gdb, {{"idInteraction", {"1"}}}, {attendreAppel, appel}, "Select Todo avec condition sur l'id de l'interaction qui vaut 1");
    testSelectUniqueTodoCondition(gdb, {{"idInteraction", {"2"}}}, {edt}, "Select Todo avec condition sur l'id de l'interaction qui vaut 2");

    //testSelectUniqueTodoCondition(gdb, {{"idContact", {"1"}}}, lTodoBDD, "Select Todo avec condition sur l'id du contact qui vaut 1");

    gdb->clearTables();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                    Tests de modification                                                        ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief testUpdateChangementNomContact teste de changer tous les contacts
 * @param gdb La base de donnée
 * @param nomTable Le nom de la table
 * @param modifications La modification à faire
 */
void testUpdateChangementNomContact(GestionBDD *gdb){
    Contact thomas = Contact("Ratu", "Thomas", "Total", "06 52 48 61 34", "photoThomas.jpg", "thomas.ratu@mail.com");
    Contact jules = Contact("Siba", "Jules", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");

    map<string, string> modif;
    modif["Prenom"] = "Thomy";

    gdb->insertData(thomas);
    gdb->insertData(jules);
    gdb->updateData("Contact", modif);

    thomas.setPrenom("Thomy");
    jules.setPrenom("Thomy");

    checkTables("Changement du nom de tous les contacts en Thomy", gdb, {thomas, jules});
}

/**
 * @brief testUpdateChangementNomThomas test une update sur le contact Thomas uniquement
 * @param gdb La base de donnée
 * @param nomTable Le nom de la table
 * @param modifications La modification à faire
 * @param conditions Les conditions pour ne modifier que Thomas
 */
void testUpdateChangementNomThomas(GestionBDD *gdb){
    Contact thomas = Contact("Ratu", "Thomas", "Total", "06 52 48 61 34", "photoThomas.jpg", "thomas.ratu@mail.com");
    Contact jules = Contact("Siba", "Jules", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");

    map<string, string> modif;
    modif["Prenom"] = "Thomy";
    map<string, list<string>> conditions;
    conditions["Nom"] = {"Ratu"};

    gdb->insertData(thomas);
    gdb->insertData(jules);
    gdb->updateData("Contact", modif, conditions);

    thomas.setPrenom("Thomy");

    checkTables("Changement du nom de Thomas en Thomy", gdb, {thomas, jules});
}

/**
 * @brief testUpdate Les tests pour les updates dans SQL
 * @param gdb La base de donnée
 */
void testUpdate(GestionBDD *gdb){
    testUpdateChangementNomContact(gdb);
    testUpdateChangementNomThomas(gdb);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                    Tests de requete spéciales                                                   ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void testNombreContact(GestionBDD *gdb){
    Contact p1 = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Contact p2 = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    Contact p3 = Contact("Florian", "Polier", "Netsle", "06 42 57 98 31", "photoFlorian.jpg", "florian.polier@mail.com");
    Contact p4 = Contact("Mathias", "Fareau", "Axe", "06 52 46 80 13", "photoMathias.jpg", "mathias.flareau@mail.com");
    gdb->insertData(p1);
    gdb->insertData(p2);
    gdb->insertData(p3);
    gdb->insertData(p4);
    int nbContact = gdb->countTable("Contact");
    if (nbContact == 4)
        REUSSI++;
    else
        RATE++;
    gdb->clearTables();
}

void testInteractionEntreDeuxDates(GestionBDD *gdb){
    Contact p1 = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Contact p2 = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");

    Interaction tel("rdv par telephone", p1);
    Interaction meeting("meeting avec les devs", p2);
    Interaction compta("demande d'info pour la comptabilite", p1);
    Interaction recap("recap de la journee", p1);
    Interaction presentation("presentation du projet", p2);
    Interaction edt("creation de l'emploi du temps", p2);

    tel.setDateCreation(Date(1, 2, 2021));
    meeting.setDateCreation(Date(16, 11, 2021));
    compta.setDateCreation(Date(20, 12, 2021));
    recap.setDateCreation(Date(3, 3, 2022));
    presentation.setDateCreation(Date(12, 12, 2021));
    edt.setDateCreation(Date(15, 12, 2021));

    gdb->insertData(p1);
    gdb->insertData(p2);
    gdb->insertData(tel);
    gdb->insertData(meeting);
    gdb->insertData(compta);
    gdb->insertData(recap);
    gdb->insertData(presentation);
    gdb->insertData(edt);

    list<Interaction> res = gdb->selectInteractionEntreDeuxDates(Date(1, 12, 2021), Date(1, 1, 2022));
    checkSelect("Selection d'interaction comprise entre 2 dates", res, {compta, presentation, edt});

}

void testTodoEntreDeuxDatesPourUnContact(GestionBDD *gdb){
    Contact thomas = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Contact jules = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");

    Interaction tel("rdv par telephone", thomas);
    Interaction compta("demande d'info pour la comptabilite", thomas);
    Interaction recap("recap de la journee", thomas);
    Interaction meeting("meeting avec les devs", jules);
    Interaction presentation("presentation du projet", jules);
    Interaction edt("creation de l'emploi du temps", jules);

    tel.setDateCreation(Date(10, 10, 2021));
    compta.setDateCreation(Date(20, 12, 2021));
    meeting.setDateCreation(Date(16, 11, 2021));
    presentation.setDateCreation(Date(12, 12, 2021));
    edt.setDateCreation(Date(15, 12, 2021));

    Todo todoCompta = Todo("faire compta", &compta, Date(8, 1, 2022));
    Todo rappeler = Todo("Rappeler", &tel, Date(16, 10, 2022));
    Todo confirmer = Todo("confirmer commande n°xyz", &tel);
    Todo todoEdt = Todo("faire l'emploi du temps", &meeting, Date(15, 12, 2021));
    Todo retard = Todo("Finir ce qui n'a pas ete fini dans la journee", &recap, Date(14, 12, 2021));

    list<Contact> lContact = {thomas, jules};
    list<Interaction> lInter = {tel, meeting, compta, recap, presentation, edt};
    list<Todo> lTodo = {todoCompta, rappeler, confirmer, todoEdt, retard};
    for (auto &it : lContact)
        gdb->insertData(it);
    for (auto &it : lInter)
        gdb->insertData(it);
    for (auto &it : lTodo)
        gdb->insertData(it);

    list<Todo> res = gdb->selectTodoEntreDeuxDatesPourContact(Date(10, 12, 2021), Date(21, 12, 2021), &thomas);
    checkSelect("Todo entre 10 et 21 decembre 2021 de thomas", res, {confirmer, retard});
}

void testTodoEntreDeuxDatesPourTousContact(GestionBDD *gdb){
    Contact thomas = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Contact jules = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");

    Interaction tel("rdv par telephone", thomas);
    Interaction compta("demande d'info pour la comptabilite", thomas);
    Interaction recap("recap de la journee", thomas);
    Interaction meeting("meeting avec les devs", jules);
    Interaction presentation("presentation du projet", jules);
    Interaction edt("creation de l'emploi du temps", jules);

    tel.setDateCreation(Date(10, 10, 2021));
    compta.setDateCreation(Date(20, 12, 2021));
    meeting.setDateCreation(Date(16, 11, 2021));
    presentation.setDateCreation(Date(12, 12, 2021));
    edt.setDateCreation(Date(15, 12, 2021));

    Todo todoCompta = Todo("faire compta", &compta, Date(8, 1, 2022));
    Todo rappeler = Todo("Rappeler", &tel, Date(16, 10, 2021));
    Todo confirmer = Todo("confirmer commande n°xyz", &tel);
    Todo todoEdt = Todo("faire l'emploi du temps", &meeting, Date(15, 12, 2021));
    Todo retard = Todo("Finir ce qui n'a pas ete fini dans la journee", &recap, Date(13, 12, 2021));

    list<Contact> lContact = {thomas, jules};
    list<Interaction> lInter = {tel, meeting, compta, recap, presentation, edt};
    list<Todo> lTodo = {todoCompta, rappeler, confirmer, todoEdt, retard};
    for (auto it : lContact)
        gdb->insertData(it);
    for (auto it : lInter)
        gdb->insertData(it);
    for (auto it : lTodo)
        gdb->insertData(it);

    list<Todo> res = gdb->selectTodoEntreDeuxDatesPourContact(Date(10, 12, 2021), Date(21, 12, 2021));
    checkSelect("Todo entre 10 et 21 decembre de thomas", res, {confirmer, todoEdt, retard});
}

void testRequetesSpeciales(GestionBDD *gdb){
    testNombreContact(gdb);
    testInteractionEntreDeuxDates(gdb);
    //testTodoEntreDeuxDatesPourUnContact(gdb);
    //testTodoEntreDeuxDatesPourTousContact(gdb);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                    Main                                                                         ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief testsDB Les tests sur la partie base de donnée
 */
void testsDB(GestionBDD *gdb){
    //gdb->recreateTable();
    gdb->clearTables();
    testInsert(gdb);
    testSelect(gdb);
    testUpdate(gdb);
    testRequetesSpeciales(gdb);
    gdb->getDb().close();
}

/**
 * @brief tests permet de lancer la testsuite
 * @param gdb La base de donnée
 */
void tests(GestionBDD *gdb){
    testsDB(gdb);
    testsObjets();
    cout << "Nombre de tests: " + to_string(RATE + REUSSI) + "\nNombre de tests valides: " + to_string(REUSSI)
                  + "\nNombre de tests rate: " + to_string(RATE) << endl;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //tests(w.getDb());
    w.show();
    return a.exec();
    //return 0;
}
