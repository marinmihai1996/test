/********************************************************************************
** Form generated from reading UI file 'dialoggroup.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGGROUP_H
#define UI_DIALOGGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_DialogGroup
{
public:
    QPushButton *sendButton;
    QLabel *sendiomage;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser;
    QComboBox *comboBox_2;
    QLabel *label_4;
    QComboBox *comboBox_3;
    QPushButton *adminButton;
    QPushButton *adminButton_2;

    void setupUi(QDialog *DialogGroup)
    {
        if (DialogGroup->objectName().isEmpty())
            DialogGroup->setObjectName(QStringLiteral("DialogGroup"));
        DialogGroup->resize(690, 450);
        DialogGroup->setStyleSheet(QStringLiteral(""));
        sendButton = new QPushButton(DialogGroup);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(550, 370, 131, 71));
        sendButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 75 18pt \"MS Shell Dlg 2\";"));
        sendButton->setAutoDefault(false);
        sendiomage = new QLabel(DialogGroup);
        sendiomage->setObjectName(QStringLiteral("sendiomage"));
        sendiomage->setGeometry(QRect(550, 370, 131, 71));
        label = new QLabel(DialogGroup);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(550, 50, 131, 20));
        label->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        label->setAlignment(Qt::AlignCenter);
        comboBox = new QComboBox(DialogGroup);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(550, 90, 131, 25));
        comboBox->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        label_2 = new QLabel(DialogGroup);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(550, 130, 131, 21));
        label_2->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        label_2->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(DialogGroup);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 370, 521, 71));
        lineEdit->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        label_3 = new QLabel(DialogGroup);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 0, 521, 51));
        label_3->setStyleSheet(QStringLiteral("font: 28pt \"MS Shell Dlg 2\";"));
        label_3->setAlignment(Qt::AlignCenter);
        pushButton_2 = new QPushButton(DialogGroup);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(550, 10, 131, 27));
        pushButton_2->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        pushButton_2->setAutoDefault(false);
        textBrowser = new QTextBrowser(DialogGroup);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 50, 521, 301));
        comboBox_2 = new QComboBox(DialogGroup);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(550, 170, 131, 25));
        comboBox_2->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox_2->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        label_4 = new QLabel(DialogGroup);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(550, 210, 131, 21));
        label_4->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        label_4->setAlignment(Qt::AlignCenter);
        comboBox_3 = new QComboBox(DialogGroup);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(550, 240, 131, 25));
        comboBox_3->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox_3->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        adminButton = new QPushButton(DialogGroup);
        adminButton->setObjectName(QStringLiteral("adminButton"));
        adminButton->setGeometry(QRect(550, 280, 131, 27));
        adminButton->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        adminButton->setAutoDefault(false);
        adminButton_2 = new QPushButton(DialogGroup);
        adminButton_2->setObjectName(QStringLiteral("adminButton_2"));
        adminButton_2->setGeometry(QRect(550, 320, 131, 27));
        adminButton_2->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        adminButton_2->setAutoDefault(false);
        sendiomage->raise();
        sendButton->raise();
        label->raise();
        comboBox->raise();
        label_2->raise();
        lineEdit->raise();
        label_3->raise();
        pushButton_2->raise();
        textBrowser->raise();
        comboBox_2->raise();
        label_4->raise();
        comboBox_3->raise();
        adminButton->raise();
        adminButton_2->raise();

        retranslateUi(DialogGroup);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), sendButton, SLOT(animateClick()));

        sendButton->setDefault(false);


        QMetaObject::connectSlotsByName(DialogGroup);
    } // setupUi

    void retranslateUi(QDialog *DialogGroup)
    {
        DialogGroup->setWindowTitle(QApplication::translate("DialogGroup", "Dialog", Q_NULLPTR));
        sendButton->setText(QString());
        sendiomage->setText(QString());
        label->setText(QApplication::translate("DialogGroup", "Change Group:", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogGroup", "Members:", Q_NULLPTR));
        label_3->setText(QString());
        pushButton_2->setText(QApplication::translate("DialogGroup", "Go Back", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogGroup", "Admins:", Q_NULLPTR));
        adminButton->setText(QApplication::translate("DialogGroup", "Admin Options", Q_NULLPTR));
        adminButton_2->setText(QApplication::translate("DialogGroup", "Leave Group", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogGroup: public Ui_DialogGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGGROUP_H
