#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlQuery>

GestionBDD *MainWindow::getDb() const
{
    return db;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->db = new GestionBDD();

    this->setupModel("Contact",
                     QStringList() << "Id"
                                   << "Nom"
                                   << "Prenom"
                                   << "Entreprise"
                                   << "Telephone"
                                   << "Photo"
                                   << "Mail"
                     );
    this->createUI();
}

void MainWindow::setupModel(const QString table, QStringList attributs){
    modelContact = new QSqlTableModel(this);
    modelContact->setTable(table);

    for (int i = 0, j = 0; i < modelContact->columnCount(); i++, j++){
        modelContact->setHeaderData(i, Qt::Horizontal, attributs[j]);
    }
    modelContact->setSort(0, Qt::AscendingOrder);

}

void MainWindow::createUI()
{
    ui->tableView->setModel(modelContact);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    modelContact->select();
}

MainWindow::~MainWindow()
{
    delete ui;
}


