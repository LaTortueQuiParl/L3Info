#include "contact.h"
#include "date.h"
#include "interaction.h"
#include <iostream>
#include <string>

int RATE = 0; // Nombre de tests rate
int REUSSI = 0; // Nombre de tests reussi

using namespace std;

template <typename T>
/**
 * @brief genericTestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param s Le test que l'on effectue
 * @param a Le premier élément à comparer avec le second
 * @param b Le second élément à comparer avec le premier
 * Function uses a tupename template to compare result of a method giving back a basic string and a string
 */
void genericTestOutputFormatForString(string classTest, string s, T a, string b){
    if (a == b){
        cout << "Test de la classe " << classTest << ": " << s << " succeeded" << endl;
        REUSSI++;
        } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test " << classTest << " " << s << " failed" << endl;
        cout << "First member is: " << a << "\nSecond member is: " << b << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        RATE++;
    }
}

template <class C>
/**
 * @brief genericTestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param s Le test que l'on effectue
 * @param a
 * Function uses a class template to compare is two instances are the same. The class must have the '==' operator overloaded
 */
void genericTestOutputFormatForClass(string classTest, string s, C a, C b){
    if (a == b){
        cout << "Test de la classe " << classTest << ": " << s << " succeeded" << endl;
        REUSSI++;
        } else {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Test " << classTest << " " << s << " failed" << endl;
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

    genericTestOutputFormatForString(classTest, "recuperation du nom,", p.getNom(), "Nom");
    genericTestOutputFormatForString(classTest, "recuperation du prenom,", p.getPrenom(), "Prenom");
    genericTestOutputFormatForString(classTest, "recuperation de l'entreprise,", p.getEntreprise(), "Entreprise");
    genericTestOutputFormatForString(classTest, "recuperation du telephone,", p.getTelephone(), "06 52 48 61 34");
    genericTestOutputFormatForString(classTest, "recuperation de la photo,", p.getPhoto(), "photo.jpg");
    genericTestOutputFormatForString(classTest, "recuperation du mail,", p.getMail(), "mail");
    Date now = Date();
    string nowS = to_string(now.getJour()) + "/" + to_string(now.getMois()) + "/" + to_string(now.getAnnee());
    genericTestOutputFormatForString(classTest, "recuperation de la date,", p.getDateCrea(), nowS);
    now.~Date();

    cout << endl; // Saut à la ligne pour que ce soit plus digeste

    // Modifications de données
    p.setNom("Nom2");
    p.setPrenom("Prenom2");
    p.setEntreprise("Entreprise2");
    p.setTelephone("06 45 79 85 31");
    p.setPhoto("photo2.jpg");
    p.setMail("mail2");
    genericTestOutputFormatForString(classTest, "modification du nom,", p.getNom(), "Nom2");
    genericTestOutputFormatForString(classTest, "modification du prenom,", p.getPrenom(), "Prenom2");
    genericTestOutputFormatForString(classTest, "modification de l'entreprise,", p.getEntreprise(), "Entreprise2");
    genericTestOutputFormatForString(classTest, "modification du telephone,", p.getTelephone(), "06 45 79 85 31");
    genericTestOutputFormatForString(classTest, "modification de la photo,", p.getPhoto(), "photo2.jpg");
    genericTestOutputFormatForString(classTest, "modification du mail,", p.getMail(), "mail2");

    cout << endl; // Saut à la ligne pour que ce soit plus digeste
}

/**
 * @brief testInteraction Test des différentes méthodes d'Interaction.
 */
void testInteraction(){

    string classTest = "interaction";
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    Interaction i = Interaction("rdv aujourd'hui par tél., RAS", p);

    // Récupération de données
    Date now = Date();
    string nowS = to_string(now.getJour()) + "/" + to_string(now.getMois()) + "/" + to_string(now.getAnnee());

    genericTestOutputFormatForString(classTest, "recuperation du contenu,", i.getContenu(), "rdv aujourd'hui par tél., RAS");
    genericTestOutputFormatForString(classTest, "recuperation de la date,", i.getDateCreation(), nowS);
    genericTestOutputFormatForClass(classTest, "recuperation du contact,", *i.getContact(), p);

    now.~Date();

    cout << endl; // Saut à la ligne pour que ce soit plus digeste

    // Modifications de données
    i.setContenu("rdv interessant");
    genericTestOutputFormatForString(classTest, "recuperation du contenu,", i.getContenu(), "rdv interessant");

    p.~Contact();

    cout << endl; // Saut à la ligne pour que ce soit plus digeste
}

int main()
{
    testContact();
    testInteraction();
    cout << "Nombre de tests: " << RATE + REUSSI << "\nNombre de tests valides: " << REUSSI << "\nNombre de tests rate: " << RATE << endl;
    //i.~Interaction();
    return 0;
}
