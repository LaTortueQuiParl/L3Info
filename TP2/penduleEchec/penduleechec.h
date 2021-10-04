#ifndef PENDULEECHEC_H
#define PENDULEECHEC_H

#include <QObject>
#include <QWidget>

#include "horlogeseule.h"

class PenduleEchec : public QWidget
{
	Q_OBJECT
private:

	HorlogeSeule * horloge0;
	HorlogeSeule * horloge1;

public:
	explicit PenduleEchec(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PENDULEECHEC_H
