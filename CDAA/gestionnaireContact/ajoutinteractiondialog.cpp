#include "ajoutinteractiondialog.h"
#include "ui_ajoutinteractiondialog.h"
#include <QString>

ajoutInteractionDialog::ajoutInteractionDialog(QWidget *parent, GestionInteractions* gi, GestionContacts* gc) :
    QDialog(parent),
    ui(new Ui::ajoutInteractionDialog)
{
    ui->setupUi(this);
    this->gestInter = gi;
    this->gestCont = gc;

    for(auto v:gestCont->getContacts()){
        ui->contactConnectComboBox->addItem(QString::fromStdString(v->getNom()+" "+v->getPrenom()+" ["+v->getTelephone()+"]"));
    }
}

ajoutInteractionDialog::~ajoutInteractionDialog()
{
    delete ui;
}

void ajoutInteractionDialog::ajoutInteractionButton()
{
    QString qs = ui->interactionPlainTextEdit->toPlainText();
}
