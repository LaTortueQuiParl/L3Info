#include "ajoutinteractiondialog.h"
#include "ui_ajoutinteractiondialog.h"
#include <QString>

ajoutInteractionDialog::ajoutInteractionDialog(QWidget *parent, GestionInteractions* gi, GestionContacts* gc, GestionBDD* bdd) :
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
    QStringList split = ui->contactConnectComboBox->currentText().split(" [");
    split.pop_front();
    QString test = split.join(" ");
    test.remove(test.size()-1,1);
    Contact* c;
    for(auto v:gestCont->getContacts()){
        if(v->getTelephone() == test.toStdString()){
            c = v;
            break;
        }
    }
    Interaction* i = new Interaction(qs.toStdString(),*c);

    baseDD->insertData(*i);
    gestInter->addInteraction(*i);
    for(auto v:gestCont->getContacts()){
        if(v->getTelephone() == test.toStdString()){
            v->getInteractions()->addInteraction(*i);
        }
    }
    this->close();
}
