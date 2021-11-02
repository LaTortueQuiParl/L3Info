#include "contact.h"
#include "date.h"
#include "interaction.h"
#include "gestioncontacts.h"
#include <iostream>
#include <string>
#include <functional>

//#include "mainwindow.h"
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
 * @param verbose permet de dire si on affiche tous les tests qui on été validés. les tests raté sont toujours affichés. verbose est mis à "flase" par défaut
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
                cout << i << "\n";
            cout << "}\nSecond member is: {\n";
            for (auto j : b)
                cout << j << "\n";
            cout << "}" << endl;
            }
        REUSSI++;
        } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test " << classTest << ", " << testName << ", failed" << endl;
        cout << "Premier membre est: {\n";
        for (auto i : a)
            cout << i << "\n";
        cout << "}\nSecond membre est: {\n";
        for (auto j : b)
            cout << j << "\n";
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
            cerr << "Test de la classe, GestionContact : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false) {
        cerr << "Test de la classe, GestionContact, " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
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
            cerr << "Test de la classe, GestionInteraction : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false) {
        cerr << "Test de la classe, GestionInteraction, " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
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
            cerr << "Test de la classe, GestionTodo : " << testName << ". A attrape une exception car " << e.what() << endl;
    }
    if (caught == false) {
        cerr << "Test de la classe, GestionTodos, " << testName << " aurait du attraper une exception mais ne l'a pas fait" << endl;
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
        Date d = Date(Largs.at(0), Largs.at(1) , Largs.at(2));
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
    ExceptionTestOutputFormat("contact sans photo", {"Nom", "Prenom", "Entreprise", "06 52 48 61 34", "", "mail"});
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

    try {
        i2.setDateCreation(Date(25, 12, 2021)); // Ne devrait pas lancer d'exception
    }  catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }
    TestOutputFormat(classTest, "comparaison entre une intreaction créée aujourd'hui et une le 25/12/2021", i<i2, true);
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

    // Test des setter
    t.setContenu("Rendez-vous");
    TestOutputFormat(classTest, "modification du contenu", t.getContenu(), "Rendez-vous");

    Date demain;
    try {
        demain = Date(26, 10, 2021); // Ne devrait pas lancer d'exception
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
    //Contact p4 = Contact("Mathias", "Fareau", "Axe", "06 52 46 80 13", "photoMathias.jpg", "mathias.flareau@mail.com");
    //Contact p5 = Contact("Alexandre", "Nirula", "Yamaha", "06 98 46 20 38", "photoAlexandre.jpg", "alexandre.nirula@mail.com");
    GestionContacts gc = GestionContacts();

    Date now = Date();

    TestOutputFormat(classTest, "Initialisation la liste de contact", gc.getContacts(), {});
    TestOutputFormat(classTest, "Initialisation la date de la derniere suppression", gc.getDerniereSuppr(), now);

    try {
        gc.addContact(p1); // Should not throw exception
    }  catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }

    TestOutputFormat(classTest, "ajout d'un contact dans la list", gc.getContacts(), {p1});

    list<Contact> lp = {p1, p2};
    gc.setContacts(lp);
    TestOutputFormat(classTest, "remplacement de la liste par une nouvelle", gc.getContacts(), lp);

    gc.supprContact(p2);
    TestOutputFormat(classTest, "suppression du contact p1 de la liste", gc.getContacts(), {p1});
    TestOutputFormat(classTest, "vérification de la mise à jour de la date de dernière suppression", gc.getDerniereSuppr(), now);

    gc.addContact(p3);
    gc.addContact(p2);

    ExceptionTestOutputFormat("ajout d'un contact deja dans la liste", &p1, &gc, "add");
    TestOutputFormat(classTest, "verification que l'ajout d'un contact deja dans la liste ne la modifie pas", gc.getContacts(), {p1, p3, p2});
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

    TestOutputFormat(classTest, "recuperation d'une interaction ajoutee", gi.getInteractions(), {i1});

    gi.setInteractions({i2, i1});
    TestOutputFormat(classTest, "recuperation d'une liste d'interaction", gi.getInteractions(), {i2, i1});

    gi.supprInteraction(i1);
    TestOutputFormat(classTest, "suppression d'une interaction", gi.getInteractions(), {i2});

    gi.addInteraction(i1);

    ExceptionTestOutputFormat("Ajout d'une interaction deja dans la liste", &i2, &gi, "add");
    TestOutputFormat(classTest, "verification que l'ajout d'une interaction deja dans la liste ne la modifie pas", gi.getInteractions(), {i2, i1});
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

    try {
        gt.addTodo(t); // Should not raise exception
    } catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }
    TestOutputFormat(classTest, "ajout d'un todo", gt.getTodos(), {&t});

    gt.setTodos({&t2, &t1});
    TestOutputFormat(classTest, "remplacement de la liste des todos", gt.getTodos(), {&t2, &t1});

    gt.supprTodo(t1);
    TestOutputFormat(classTest, "suppression d'un todo", gt.getTodos(), {&t2});

    try {
        gt.addTodo(t1); // Should not raise exception
    }  catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }
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
    TestOutputFormat(classTest, "verification que l'ajout dans la liste d'un todo deja dans la liste mais qui a une date qui est differente d'aujourd'hui est bien ajoute", gt.getTodos(), {&t2, &t1, &t3});

    Todo t4 = Todo("boire", &i, Date(5, 10, 2021));
    t4.setDeadline(Date());
    ExceptionTestOutputFormat("Ajout d'un todo initialisé differement mais modifier pour être le même qu'un dans la liste", &t4, &gt, "add");

    TestOutputFormat(classTest, "verification que l'ajout dans la liste d'un autre todo, initialisé avec une date mais dont la deadline a change pour aujourd'hui n'est pas ajoute", gt.getTodos(), {&t2, &t1, &t3});


    ExceptionTestOutputFormat("supression d'un todo qui n'est pas dans la liste", &t4, &gt, "suppr");
    TestOutputFormat(classTest, "verification que la supression d'un element qui n'est pas dans la liste ne la modifie pas", gt.getTodos(), {&t2, &t1, &t3});
}

int main(int argc, char** argv)
{
    testContact(); // Tests de la classe contact
    testInteraction(); // Tests de la classe interaction
    testTodo(); // Tests de la classe Todo
    testDate(); // Tests de la classe Date
    testGestionContacts(); // Tests de la classe GestionContacts
    testGestionInteractions(); // Tests de la classe GestionsInteractions
    testGestionTodos(); // Tests de la class GestionTodos
    cout << "Nombre de tests: " + to_string(RATE + REUSSI) + "\nNombre de tests valides: " + to_string(REUSSI)
                  + "\nNombre de tests rate: " + to_string(RATE) << endl;
    return 0;
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
