#include <QVBoxLayout>
#include <QHBoxLayout>

#include "horlogeseule.h"

HorlogeSeule::HorlogeSeule(QWidget *parent)
	: QWidget(parent)
{
	compteur = 100;

	texte = new QLabel("Compteur :", this);

	valeur = new QLabel(this);
	valeur->setNum((int)compteur);

	start = new QPushButton("Démarrer", this);

	stop = new QPushButton("Arrêter", this);

	QVBoxLayout * mainLayout = new QVBoxLayout(this);

	QHBoxLayout * textes = new QHBoxLayout();
	QHBoxLayout * boutons = new QHBoxLayout();

	textes->addWidget(texte);
	textes->addWidget(valeur);
	boutons->addWidget(start);
	boutons->addWidget(stop);

	mainLayout->addLayout(textes);
	mainLayout->addLayout(boutons);

	setLayout(mainLayout);
}

HorlogeSeule::~HorlogeSeule()
{

}
