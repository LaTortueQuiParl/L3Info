#include "ajoutcontactdialog.h"
#include "ui_ajoutcontactdialog.h"
#include <QFileDialog>
#include <QDebug>

AjoutContactDialog::AjoutContactDialog(QWidget *parent, GestionContacts* gestCont, GestionBDD* bdd) :
    QDialog(parent),
    ui(new Ui::AjoutContactDialog)
{
    ui->setupUi(this);
    gesCont = gestCont;
    baseDD = bdd;

    QObject::connect(ui->ajoutPPbutton,SIGNAL(clicked()),this,SLOT(AjoutPPButton()));
    QObject::connect(ui->validAjoutContactButton,SIGNAL(clicked()),this,SLOT(ValidAjoutContactButton()));
    QObject::connect(ui->annulAjoutContactButton,SIGNAL(clicked()),this,SLOT(AnnulButton()));
}

AjoutContactDialog::~AjoutContactDialog()
{
    delete ui;
}

void AjoutContactDialog::clearFenetre()
{
    this->img = "./Images/PPDefault.jpg";
    QPixmap p = img;
    ui->PPImgLabel->setPixmap(p.scaled(ui->PPImgLabel->width(),ui->PPImgLabel->height(),Qt::KeepAspectRatio));
    ui->nomLineEdit->setText("");
    ui->prNomLineEdit->setText("");
    ui->entrepriseLineEdit->setText("");
    ui->mailLineEdit->setText("");
    ui->tLPhoneLineEdit->setText("");
}

void AjoutContactDialog::AjoutPPButton()
{
    int h = ui->PPImgLabel->height();
    int w = ui->PPImgLabel->width();
    img = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    QPixmap p = img;
    ui->PPImgLabel->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
}

void AjoutContactDialog::ValidAjoutContactButton()
{
    if(ui->nomLineEdit->text().isEmpty() || ui->prNomLineEdit->text().isEmpty() || ui->entrepriseLineEdit->text().isEmpty()){

    }else{
        Contact* c = new Contact("a","b","c","0000000000","","e");
        c->setNom(ui->nomLineEdit->text().toStdString());
        c->setPrenom(ui->prNomLineEdit->text().toStdString());
        c->setEntreprise(ui->entrepriseLineEdit->text().toStdString());
        c->setMail(ui->mailLineEdit->text().toStdString());
        c->setTelephone(ui->tLPhoneLineEdit->text().toStdString());
        c->setPhoto(img.toStdString());

        this->gesCont->addContact(*c);
        baseDD->insertData(*c);
    }
    this->clearFenetre();
    this->close();
}

void AjoutContactDialog::AnnulButton()
{
    this->clearFenetre();
    this->close();
}


