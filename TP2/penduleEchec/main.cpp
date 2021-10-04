#include "penduleechec.h"
#include "horlogeseule.h"
#include <QApplication>

#include <QMessageBox>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	PenduleEchec pendule;
	pendule.show();

	QMessageBox msgBox;
	msgBox.setText("Le décompte est arrivé à sa fin");

	return app.exec();
}
