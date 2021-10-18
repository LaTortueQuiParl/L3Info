//#include "mainwindow.h"
#include "contact.h"
#include <QtDebug>
//#include <QApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    Contact p1 = Contact("Nom", "Prenom", "Entreprise", "06 52 48 61 34", "photo.jpg", "mail");
    qDebug() << QString::fromStdString(p1.getNom());
    p1.setNom("NomModifie");
    qDebug() << QString::fromStdString(p1.getNom());
    std::cout << p1.getDateCrea() << std::endl;
    p1.~Contact();
    return 0;
}
