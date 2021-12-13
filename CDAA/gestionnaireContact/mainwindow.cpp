#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->InteractionWidget->setCurrentWidget(ui->contactAffichageTab);
    ui->stackedWidget->setCurrentWidget(ui->affichContactWidget);

    this->db = new GestionBDD();


    this->gestCont = new GestionContacts();
    Contact* c1 = new Contact("moi", "toi", "entre", "0625142514", "D:\\Images\\iconediscord.jpg", "mail@mail.com");
    Contact* c2 = new Contact("Nous galaga", "Vous", "psy", "0636253625", "D:\\Images\\iconediscordgit.jpg", "mail@mail.com");
    Contact* c3 = new Contact("papi", "mami", "psy", "0669586958", "", "mail@mail.com");
    Contact* c4 = new Contact("pipi", "caca", "entre", "0647584758", "", "mail@mail.com");
    gestCont->addContact(*c1);
    gestCont->addContact(*c2);
    gestCont->addContact(*c3);
    gestCont->addContact(*c4);

    Interaction* i1 = new Interaction("Je ne sais pas", *c1);
    Interaction* i2 = new Interaction("2eme interaction", *c1);
    Interaction* i3 = new Interaction("Ah bon ?", *c2);
    Interaction* i4 = new Interaction("Pour Sur", *c3);
    c1->getInteractions()->addInteraction(*i1);
    c1->getInteractions()->addInteraction(*i2);
    c2->getInteractions()->addInteraction(*i3);
    c3->getInteractions()->addInteraction(*i4);

    this->gestInter = new GestionInteractions();

    for(auto v:gestCont->getContacts()){
        for(auto i:v->getInteractions()->getInteractions()){
            gestInter->addInteraction(*i);
        }
    }

    this->gestTodos = new GestionTodos();

    remplissageListContact();
    remplissageListInteraction();

    QObject::connect(ui->ajoutContactButton,SIGNAL(clicked()),this,SLOT(ouvrirajoutContactDialog()));
    QObject::connect(ui->ajoutInteractionButton,SIGNAL(clicked()),this,SLOT(ouvrirajoutInteractionDialog()));

    QObject::connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(recherchContactButton()));
    QObject::connect(ui->modifPPButton,SIGNAL(clicked()),this,SLOT(modifPPButton()));
    QObject::connect(ui->retourContactButton,SIGNAL(clicked()),this,SLOT(retourWidgetContact()));
    QObject::connect(ui->saveModifContactButton,SIGNAL(clicked()),this,SLOT(saveModif()));
    QObject::connect(ui->suppContactButton,SIGNAL(clicked()),this,SLOT(suppContact()));
    QObject::connect(ui->suppInterractionButton,SIGNAL(clicked()),this,SLOT(suppInteraction()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

GestionBDD *MainWindow::getDb() const
{
    return db;
}

void MainWindow::remplissageListContact()
{
    ui->contactListWidget->clear();
    for(auto v:gestCont->getContacts()){
        ui->contactListWidget->addItem(QString::fromStdString(v->getNom()+ " "+ v->getPrenom()+ " ["+v->getTelephone()+"]"));
    }
}

void MainWindow::remplissageListInteraction()
{
    ui->InteractionListWidget->clear();
    for(auto v:gestInter->getInteractions()){
        ui->InteractionListWidget->addItem(QString::fromStdString(v->getContenu()+ " ("+ v->getContact()->getNom()+" "+v->getContact()->getPrenom()+")"));
    }
    /*for(auto v:gestTodos->getTodos()){
        ui->InteractionListWidget->addItem(QString::fromStdString("@Todo "+v->getContenu()));
    }*/
}

void MainWindow::modifPPButton()
{
    int h = ui->PPLabel->height();
    int w = ui->PPLabel->width();
    imgContact = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    QPixmap p = imgContact;
    ui->PPLabel->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::recherchContactButton()
{
    ui->contactListWidget->clear();
    if(!ui->contactSearchBar->text().isEmpty()){
        for(auto v:gestCont->getContacts()){
            switch(ui->comboBox->currentIndex()){
            case 0:
                if(v->getNom() == ui->contactSearchBar->text().toStdString()){
                    ui->contactListWidget->addItem(QString::fromStdString(v->getNom()+ " "+v->getPrenom()+ " ["+v->getTelephone()+"]"));
                }
                break;
            case 1:
                if(v->getPrenom() == ui->contactSearchBar->text().toStdString()){
                    ui->contactListWidget->addItem(QString::fromStdString(v->getNom()+ " "+v->getPrenom()+ " ["+v->getTelephone()+"]"));
                }
                break;
            case 2:
                if(v->getEntreprise() == ui->contactSearchBar->text().toStdString()){
                    ui->contactListWidget->addItem(QString::fromStdString(v->getNom()+ " "+v->getPrenom()+ " ["+v->getTelephone()+"]"));
                }
                break;
            }

        }
    }else{
        remplissageListContact();
    }
}

void MainWindow::retourWidgetContact()
{
    ui->stackedWidget->setCurrentIndex(0);
    imgContact="./Images/PPDefault.jpg";
}

void MainWindow::saveModif()
{
    if(ui->nomLineEdit->isModified() || ui->prNomLineEdit->isModified() || ui->entrepriseLineEdit->isModified() || ui->mailLineEdit->isModified()){
        contactCourant->setNom(ui->nomLineEdit->text().toStdString());
        contactCourant->setPrenom(ui->prNomLineEdit->text().toStdString());
        contactCourant->setEntreprise(ui->entrepriseLineEdit->text().toStdString());
        contactCourant->setTelephone(ui->tLPhoneLineEdit->text().toStdString());
        contactCourant->setMail(ui->mailLineEdit->text().toStdString());
    }
    contactCourant->setPhoto(imgContact.toStdString());
    imgContact="./Images/PPDefault.jpg";
}

void MainWindow::suppContact()
{
    gestCont->supprContact(*contactCourant);
    contactCourant->~Contact();
    ui->suppContactButton->setEnabled(false);
    remplissageListContact();
}

void MainWindow::on_contactListWidget_itemDoubleClicked(QListWidgetItem* item)
{
    ui->stackedWidget->setCurrentIndex(1);
    QStringList split = item->text().split(" [");
    split.pop_front();
    QString test = split.join(" ");
    test.remove(test.size()-1,1);
    for(auto v:gestCont->getContacts()){
        if(v->getTelephone() == test.toStdString()){
            contactCourant=v;
            break;
        }
    }

    ui->nomLineEdit->setText(QString::fromStdString(contactCourant->getNom()));
    ui->prNomLineEdit->setText(QString::fromStdString(contactCourant->getPrenom()));
    ui->entrepriseLineEdit->setText(QString::fromStdString(contactCourant->getEntreprise()));
    ui->tLPhoneLineEdit->setText(QString::fromStdString(contactCourant->getTelephone()));
    ui->mailLineEdit->setText(QString::fromStdString(contactCourant->getMail()));
    QPixmap p = QString::fromStdString(contactCourant->getPhoto());
    ui->PPLabel->setPixmap(p.scaled(ui->PPLabel->width(),ui->PPLabel->height(),Qt::KeepAspectRatio));

    ui->InteractionContactListWidget->clear();
    for(auto v:contactCourant->getInteractions()->getInteractions()){
        ui->InteractionContactListWidget->addItem(QString::fromStdString(v->getContenu()));
    }
}


void MainWindow::on_contactListWidget_itemClicked(QListWidgetItem* item)
{
    QStringList split = item->text().split(" [");
    split.pop_front();
    QString test = split.join(" ");
    test.remove(test.size()-1,1);
    for(auto v:gestCont->getContacts()){
        if(v->getTelephone() == test.toStdString()){
            contactCourant=v;
            break;
        }
    }
    ui->suppContactButton->setEnabled(true);
}

void MainWindow::ouvrirajoutContactDialog()
{
    this->acd = new AjoutContactDialog(this,gestCont);
    acd->exec();
}

void MainWindow::ouvrirajoutInteractionDialog()
{
    this->aid = new ajoutInteractionDialog(this,gestInter,gestCont);
    aid->exec();
}

void MainWindow::suppInteraction()
{
    gestInter->supprInteraction(*interactionCourant);
    interactionCourant->~Interaction();
    ui->suppInterractionButton->setEnabled(false);
    remplissageListInteraction();
}


void MainWindow::on_InteractionListWidget_itemClicked(QListWidgetItem *item)
{
    QStringList split = item->text().split(" (");
    split.pop_back();
    QString test = split.at(0);
    for(auto v:gestInter->getInteractions()){
        if(v->getContenu()==test.toStdString()){
            interactionCourant = v;
            break;
        }
    }
    ui->suppInterractionButton->setEnabled(true);
}

