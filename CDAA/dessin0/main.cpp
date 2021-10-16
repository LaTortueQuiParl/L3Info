#include <QApplication>

#include "mainwidget.h"
#include "affichage.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//un widget tout simple (vide)
	mainWidget main;
	main.show();

	Affichage aff;
	aff.show ();

	QObject::connect(&main, SIGNAL(newEvent(QString)), &aff, SLOT(recvData(QString)));

	//comme les 2 widgets ne sont pas corrélés, comment arrêter l'application en fermant un seul widget ?
	//réponse : en passant par la QApplication, mais c'est mal conçu...

	return app.exec();
}
