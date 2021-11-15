/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *AnnulButtonAC;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *nomLabel;
    QLineEdit *nomLineEdit;
    QLabel *prNomLabel;
    QLineEdit *prNomLineEdit;
    QLabel *entrepriseLabel;
    QLineEdit *entrepriseLineEdit;
    QLabel *mailLabel;
    QLineEdit *mailLineEdit;
    QLabel *tLPhoneLabel;
    QLineEdit *tLPhoneLineEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(320, 240);
        AnnulButtonAC = new QDialogButtonBox(Dialog);
        AnnulButtonAC->setObjectName(QString::fromUtf8("AnnulButtonAC"));
        AnnulButtonAC->setGeometry(QRect(10, 200, 301, 32));
        AnnulButtonAC->setOrientation(Qt::Horizontal);
        AnnulButtonAC->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(Dialog);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(29, 19, 271, 161));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        nomLabel = new QLabel(formLayoutWidget);
        nomLabel->setObjectName(QString::fromUtf8("nomLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nomLabel);

        nomLineEdit = new QLineEdit(formLayoutWidget);
        nomLineEdit->setObjectName(QString::fromUtf8("nomLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nomLineEdit);

        prNomLabel = new QLabel(formLayoutWidget);
        prNomLabel->setObjectName(QString::fromUtf8("prNomLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, prNomLabel);

        prNomLineEdit = new QLineEdit(formLayoutWidget);
        prNomLineEdit->setObjectName(QString::fromUtf8("prNomLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, prNomLineEdit);

        entrepriseLabel = new QLabel(formLayoutWidget);
        entrepriseLabel->setObjectName(QString::fromUtf8("entrepriseLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, entrepriseLabel);

        entrepriseLineEdit = new QLineEdit(formLayoutWidget);
        entrepriseLineEdit->setObjectName(QString::fromUtf8("entrepriseLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, entrepriseLineEdit);

        mailLabel = new QLabel(formLayoutWidget);
        mailLabel->setObjectName(QString::fromUtf8("mailLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, mailLabel);

        mailLineEdit = new QLineEdit(formLayoutWidget);
        mailLineEdit->setObjectName(QString::fromUtf8("mailLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, mailLineEdit);

        tLPhoneLabel = new QLabel(formLayoutWidget);
        tLPhoneLabel->setObjectName(QString::fromUtf8("tLPhoneLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, tLPhoneLabel);

        tLPhoneLineEdit = new QLineEdit(formLayoutWidget);
        tLPhoneLineEdit->setObjectName(QString::fromUtf8("tLPhoneLineEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, tLPhoneLineEdit);


        retranslateUi(Dialog);
        QObject::connect(AnnulButtonAC, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(AnnulButtonAC, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        nomLabel->setText(QApplication::translate("Dialog", "Nom", nullptr));
        prNomLabel->setText(QApplication::translate("Dialog", "Pr\303\251nom", nullptr));
        entrepriseLabel->setText(QApplication::translate("Dialog", "Entreprise", nullptr));
        mailLabel->setText(QApplication::translate("Dialog", "Mail", nullptr));
        tLPhoneLabel->setText(QApplication::translate("Dialog", "T\303\251l\303\251phone", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
