#include "contact.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    Contact p1 = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    std::cout << p1 << std::endl;
    p1.~Contact();
    return 0;
}
