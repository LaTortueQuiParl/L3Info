#ifndef AJOUTINTERACTIONDIALOG_H
#define AJOUTINTERACTIONDIALOG_H

#include <QDialog>
#include "gestioninteractions.h"
#include "gestioncontacts.h"
#include "gestionbdd.h"

namespace Ui {
class ajoutInteractionDialog;
}

class ajoutInteractionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutInteractionDialog(QWidget *parent = nullptr, GestionInteractions* gi = nullptr, GestionContacts* gc = nullptr, GestionBDD* bdd = nullptr);
    ~ajoutInteractionDialog();

private:
    Ui::ajoutInteractionDialog *ui;
    GestionInteractions* gestInter;
    GestionContacts* gestCont;
    GestionBDD* baseDD;

public slots:
    void ajoutInteractionButton();
};

#endif // AJOUTINTERACTIONDIALOG_H
