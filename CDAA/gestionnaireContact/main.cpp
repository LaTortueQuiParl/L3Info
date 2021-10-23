#include "contact.h"
#include "date.h"
#include <iostream>
#include <string>

int RATE = 0; // Nombre de tests rate
int REUSSI = 0; // Nombre de tests reussi

using namespace std;


/**
 * @brief genericTestOutputFormat Renvoie sur std::cout si le test est reussi ou non
 * @param classTest Le nom de la classe que l'on teste
 * @param s Le test que l'on effectue
 * @param test Le résultat du test effectue
 */
void genericTestOutputFormat(string classTest, string s, bool test){
    if (test==1){
        cout << "Test de la classe " << classTest << ": " << s << " succeeded" << endl;
        REUSSI++;
        } else {
        cout << "Test " << classTest << " " << s << " failed" << endl;
        RATE++;
    }
}

/**
 * @brief testContact
 * @param p Le contact que l'on teste
 * Cette fonction teste les différentes méthodes de Contact
 */

void testContact(Contact &p){
    // Récupération de données
    string classTest = "Contact";
    genericTestOutputFormat(classTest, "recuperation du nom,", p.getNom() == "Nom");
    genericTestOutputFormat(classTest, "recuperation du prenom,", p.getPrenom() == "Prenom");
    genericTestOutputFormat(classTest, "recuperation de l'entreprise,", p.getEntreprise() == "Entreprise");
    genericTestOutputFormat(classTest, "recuperation du telephone,", p.getTelephone() == "06 52 48 61 34");
    genericTestOutputFormat(classTest, "recuperation de la photo,", p.getPhoto() == "photo.jpg");
    genericTestOutputFormat(classTest, "recuperation du mail,", p.getMail() == "mail");
    Date now = Date(time(nullptr));
    string nowS = to_string(now.getJour()) + "/" + to_string(now.getMois()) + "/" + to_string(now.getAnnee());
    genericTestOutputFormat(classTest, "recuperation de la date,", p.getDateCrea() == nowS);
    now.~Date();

    cout << endl; // Saut à la ligne pour que ce soit plus digeste

    // Modifications de données
    p.setNom("Nom2");
    p.setPrenom("Prenom2");
    p.setEntreprise("Entreprise2");
    p.setTelephone("06 45 79 85 31");
    p.setPhoto("photo2.jpg");
    p.setMail("mail2");
    p.setDateCrea(25, 12, 2021);
    genericTestOutputFormat(classTest, "modification du nom,", p.getNom() == "Nom2");
    genericTestOutputFormat(classTest, "modification du prenom,", p.getPrenom() == "Prenom2");
    genericTestOutputFormat(classTest, "modification de l'entreprise,", p.getEntreprise() == "Entreprise2");
    genericTestOutputFormat(classTest, "modification du telephone,", p.getTelephone() == "06 45 79 85 31");
    genericTestOutputFormat(classTest, "modification de la photo,", p.getPhoto() == "photo2.jpg");
    genericTestOutputFormat(classTest, "modification du mail,", p.getMail() == "mail2");

    cout << endl; // Saut à la ligne pour que ce soit plus digeste
}

int main()
{
    Contact p = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    //Interaction i = Interaction("rdv", p);
    testContact(p);
    cout << "Nombre de tests: " << RATE + REUSSI << "\nNombre de tests valides: " << REUSSI << "\nNombre de tests rate: " << RATE << endl;
    p.~Contact();
    //i.~Interaction();
    return 0;
}
