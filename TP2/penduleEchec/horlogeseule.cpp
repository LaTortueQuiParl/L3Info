#include <QVBoxLayout>
#include <QHBoxLayout>

#include "horlogeseule.h"

HorlogeSeule::HorlogeSeule(QWidget *parent)
	: QWidget(parent)
{
	compteur = 10;

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updatingTimer()));

	texte = new QLabel("Compteur :", this);

	valeur = new QLabel(this);
	valeur->setNum((int)compteur);

	start = new QPushButton("Démarrer", this);
	connect(start, SIGNAL(clicked()), this, SLOT(demarrer()));

	stop = new QPushButton("Arrêter", this);
	connect(stop, SIGNAL(clicked()), this, SLOT(arreter()));

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

void HorlogeSeule::demarrer()
{
	timer->start(1000);
}

void HorlogeSeule::arreter()
{
	timer->stop();
}

void HorlogeSeule::updatingTimer()
{
	compteur--;
	if (compteur == 0)
		emit finDecompte();
	else
		valeur->setNum((int)compteur);
}

