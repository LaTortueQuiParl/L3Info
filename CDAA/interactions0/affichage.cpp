#include "affichage.h"

Affichage::Affichage(QWidget *parent)
    : QWidget(parent)
{
    //on donne une taille par défaut à notre widget (en pixels) (largeur, hauteur)
    setFixedSize(300,300);
}
