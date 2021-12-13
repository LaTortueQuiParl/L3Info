#ifndef AJOUTCONTACTDIALOG_H
#define AJOUTCONTACTDIALOG_H

#include <QDialog>
#include "gestioncontacts.h"
#include "gestionbdd.h"

namespace Ui {
class AjoutContactDialog;
}

class AjoutContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutContactDialog(QWidget *parent = nullptr, GestionContacts* gestCont = nullptr, GestionBDD* bdd = nullptr);
    ~AjoutContactDialog();

    void clearFenetre();

private:
    Ui::AjoutContactDialog *ui;
    GestionContacts* gesCont;
    GestionBDD* baseDD;
    QString img;

public slots:
    void AjoutPPButton();
    void ValidAjoutContactButton();
    void AnnulButton();
};

#endif // AJOUTCONTACTDIALOG_H
