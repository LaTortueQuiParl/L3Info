#include "penduleechec.h"
#include <QHBoxLayout>

PenduleEchec::PenduleEchec(QWidget *parent) : QWidget(parent)
{
	QHBoxLayout * penduleLayout = new QHBoxLayout();

	horloge0 = new HorlogeSeule(this);
	horloge1 = new HorlogeSeule(this);

	penduleLayout->addWidget(horloge0);
	penduleLayout->addWidget(horloge1);

	//mainLayout->addLayout(boutons);

	setLayout(penduleLayout);
}
