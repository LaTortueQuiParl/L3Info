#include "horlogeseule.h"
#include <QApplication>

#include <QMessageBox>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	HorlogeSeule horloge0;
	HorlogeSeule horloge1;

	horloge0.show();
	horloge1.show();

	QMessageBox msgBox;
	msgBox.setText("Le décompte est arrivé à sa fin");

	QObject::connect(&horloge0, SIGNAL(finDecompte()), &msgBox, SLOT(exec()));
	QObject::connect(&horloge0, SIGNAL(finDecompte()), &app, SLOT(quit()));

	return app.exec();
}
