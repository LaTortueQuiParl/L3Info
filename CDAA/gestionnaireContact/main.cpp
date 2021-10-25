#include "contact.h"
#include "date.h"
#include "interaction.h"
#include "gestioncontacts.h"
#include <iostream>
#include <string>

int RATE = 0; // Nombre de tests rate
int REUSSI = 0; // Nombre de tests reussi

using namespace std;

bool compareListContact(list<Contact> a, list<Contact> b){
    if (a.size() != b.size())
        return false;
    list<Contact>::iterator it1 = a.begin();
    list<Contact>::iterator it2 = b.begin();
    while(it1 != a.end() && it2 != b.begin()){
        if (*it1 == *it2)
            continue;
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
        if (verbose == true)
            cout << "Test de la classe " << classTest << ", " << s << " succeeded" << endl;
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
        if (verbose == true)
            cout << "Test de la classe, " << classTest << ", " << s << ", succeeded" << endl;
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
        if (verbose == true)
                cout << "Test de la classe, " << classTest << ", " << s << " succeeded" << endl;
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
    string nowS = to_string(now.getJour()) + "/" + to_string(now.getMois()) + "/" + to_string(now.getAnnee());
    genericTestOutputFormat(classTest, "recuperation de la date", p.getDateCrea(), nowS);
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
    genericTestOutputFormat(classTest, "recuperation de la date", i.getDateCreation(), nowS);
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
    Todo t = Todo("Rappeler", "16/10/2021", "date", &i);

    // Test des getter
    genericTestOutputFormat(classTest, "recuperation du contenu", t.getContenu(), "Rappeler");
    genericTestOutputFormat(classTest, "recuperation du contenu du tag", t.getContenuTag(), "16/10/2021");
    genericTestOutputFormat(classTest, "recuperation de l'interaction", *t.getInteraction(), i);
    genericTestOutputFormat(classTest, "recuperation du tag", t.getTag(), "@date"); // C'est perturbant de dire que le tag c'est "date" et quand tu le récupère c'est "@date"


    // Test des setter
    t.setContenu("Rendez-vous");
    t.setContenuTag("17/10/2021");
    t.setTag("newTag");
    genericTestOutputFormat(classTest, "modification du conten,", t.getContenu(), "Rendez-vous");
    genericTestOutputFormat(classTest, "modification du contenu du tag", t.getContenuTag(), "17/10/2021");
    genericTestOutputFormat(classTest, "modification du tag", t.getTag(), "newTag");
}

/**
 * @brief testGestionContact permet de tester la classe gestion contact
 */
void testGestionContact(){
    string classTest = "gestionContact";
    Contact p1 = Contact("Thomas", "Ratu", "Total", "06 52 48 61 34", "photoThoms.jpg", "thomas.rate@mail.com");
    Contact p2 = Contact("Jules", "Siba", "Cafe", "06 46 87 31 57", "photoJules.jpg", "jules.siba@mail.com");
    Contact p3 = Contact("Florian", "Polier", "Netsle", "06 42 57 98 31", "photoFlorian.jpg", "florian.polier@mail.com");
    Contact p4 = Contact("Mathias", "Fareau", "Axe", "06 52 46 80 13", "photoMathias.jpg", "mathias.flareau@mail.com");
    Contact p5 = Contact("Alexandre", "Nirula", "Yamaha", "06 98 46 20 38", "photoAlexandre.jpg", "alexandre.nirula@mail.com");
    GestionContacts gc = GestionContacts();

    Date now = Date();
    string nowS = to_string(now.getJour()) + "/" + to_string(now.getMois()) + "/" + to_string(now.getAnnee());

    genericTestOutputFormat(classTest, "recuperation de la liste de contact", gc.getContacts(), {});
    genericTestOutputFormat(classTest, "récupération de la date de la derniere suppression", gc.getDerniereSuppr(), nowS);

    gc.addContact(p1);
    genericTestOutputFormat(classTest, "ajout d'un contact dans la list", gc.getContacts(), {p1});

    list<Contact> lp = {p1, p2};
    gc.setContacts(lp);
    genericTestOutputFormat(classTest, "remplacement de la liste par une nouvelle", gc.getContacts(), lp);

    gc.supprContact(p2);
    genericTestOutputFormat(classTest, "suppression du contact p1 de la liste", gc.getContacts(), {p1});
    genericTestOutputFormat(classTest, "vérification de la mise à jour de la date de dernière suppression", gc.getDerniereSuppr(), nowS);
}

int main()
{
    testContact(); // Tests de la classe contact
    testInteraction(); // Tests de la classe interaction
    testTodo(); // Tests de la classe Todo
    testGestionContact(); // Tests de la classe GestionContacts
    cout << "Nombre de tests: " << RATE + REUSSI << "\nNombre de tests valides: " << REUSSI << "\nNombre de tests rate: " << RATE << endl;
    return 0;
}
