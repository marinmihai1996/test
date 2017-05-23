/********************************************************************************
** Form generated from reading UI file 'dialogprivate.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPRIVATE_H
#define UI_DIALOGPRIVATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_DialogPrivate
{
public:
    QPushButton *sendButton;
    QLineEdit *lineEdit;
    QLabel *sendiomage;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *DialogPrivate)
    {
        if (DialogPrivate->objectName().isEmpty())
            DialogPrivate->setObjectName(QStringLiteral("DialogPrivate"));
        DialogPrivate->resize(711, 448);
        sendButton = new QPushButton(DialogPrivate);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(560, 360, 131, 71));
        sendButton->setStyleSheet(QLatin1String("background-color: transparent;\n"
"font: 75 18pt \"MS Shell Dlg 2\";"));
        sendButton->setAutoDefault(false);
        lineEdit = new QLineEdit(DialogPrivate);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 360, 521, 71));
        lineEdit->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        sendiomage = new QLabel(DialogPrivate);
        sendiomage->setObjectName(QStringLiteral("sendiomage"));
        sendiomage->setGeometry(QRect(560, 360, 131, 71));
        label = new QLabel(DialogPrivate);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 5, 361, 51));
        label->setStyleSheet(QStringLiteral("font: 22pt \"MS Shell Dlg 2\";"));
        label_2 = new QLabel(DialogPrivate);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(400, 0, 291, 61));
        label_2->setStyleSheet(QStringLiteral("font: 22pt \"MS Shell Dlg 2\";"));
        pushButton = new QPushButton(DialogPrivate);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(560, 360, 131, 71));
        pushButton->setStyleSheet(QStringLiteral("background-color: transparent;"));
        textBrowser = new QTextBrowser(DialogPrivate);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 60, 671, 281));

        retranslateUi(DialogPrivate);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), pushButton, SLOT(animateClick()));

        sendButton->setDefault(false);


        QMetaObject::connectSlotsByName(DialogPrivate);
    } // setupUi

    void retranslateUi(QDialog *DialogPrivate)
    {
        DialogPrivate->setWindowTitle(QApplication::translate("DialogPrivate", "Dialog", Q_NULLPTR));
        sendButton->setText(QString());
        sendiomage->setText(QString());
        label->setText(QApplication::translate("DialogPrivate", "You are in private chat with:", Q_NULLPTR));
        label_2->setText(QString());
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogPrivate: public Ui_DialogPrivate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPRIVATE_H
