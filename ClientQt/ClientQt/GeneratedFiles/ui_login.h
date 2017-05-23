/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogIn
{
public:
    QAction *actionSing_Up;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionSelect_All;
    QAction *actionPaste;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *LogIn)
    {
        if (LogIn->objectName().isEmpty())
            LogIn->setObjectName(QStringLiteral("LogIn"));
        LogIn->resize(350, 500);
        actionSing_Up = new QAction(LogIn);
        actionSing_Up->setObjectName(QStringLiteral("actionSing_Up"));
        actionExit = new QAction(LogIn);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionUndo = new QAction(LogIn);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(LogIn);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionCut = new QAction(LogIn);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(LogIn);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionSelect_All = new QAction(LogIn);
        actionSelect_All->setObjectName(QStringLiteral("actionSelect_All"));
        actionPaste = new QAction(LogIn);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        centralWidget = new QWidget(LogIn);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 250, 130, 40));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        QIcon icon;
        icon.addFile(QStringLiteral("chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(16, 16));
        pushButton->setAutoDefault(true);
        pushButton->setFlat(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 70, 91, 23));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 160, 91, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 320, 211, 41));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(240, 330, 71, 21));
        label_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 330, 71, 21));
        QFont font;
        font.setKerning(true);
        pushButton_2->setFont(font);
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2->setFocusPolicy(Qt::StrongFocus);
        pushButton_2->setStyleSheet(QStringLiteral("background-color: transparent;"));
        pushButton_2->setAutoDefault(false);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 100, 261, 41));
        lineEdit->setStyleSheet(QStringLiteral("font: 14pt \"Times New Roman\";"));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(50, 190, 261, 41));
        lineEdit_2->setStyleSheet(QStringLiteral("font: 14pt \"Times New Roman\";"));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        LogIn->setCentralWidget(centralWidget);
        label_4->raise();
        pushButton_2->raise();
        pushButton->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        lineEdit->raise();
        lineEdit_2->raise();
        statusBar = new QStatusBar(LogIn);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LogIn->setStatusBar(statusBar);
        menuBar = new QMenuBar(LogIn);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 350, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        LogIn->setMenuBar(menuBar);
        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSing_Up);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(LogIn);

        pushButton->setDefault(true);
        pushButton_2->setDefault(true);


        QMetaObject::connectSlotsByName(LogIn);
    } // setupUi

    void retranslateUi(QMainWindow *LogIn)
    {
        LogIn->setWindowTitle(QApplication::translate("LogIn", "LogIn", Q_NULLPTR));
        actionSing_Up->setText(QApplication::translate("LogIn", "Sing Up", Q_NULLPTR));
        actionExit->setText(QApplication::translate("LogIn", "Exit", Q_NULLPTR));
        actionUndo->setText(QApplication::translate("LogIn", "Undo", Q_NULLPTR));
        actionRedo->setText(QApplication::translate("LogIn", "Redo", Q_NULLPTR));
        actionCut->setText(QApplication::translate("LogIn", "Cut", Q_NULLPTR));
        actionCopy->setText(QApplication::translate("LogIn", "Copy", Q_NULLPTR));
        actionSelect_All->setText(QApplication::translate("LogIn", "Select All", Q_NULLPTR));
        actionPaste->setText(QApplication::translate("LogIn", "Paste", Q_NULLPTR));
        pushButton->setText(QApplication::translate("LogIn", "Log In", Q_NULLPTR));
        label->setText(QApplication::translate("LogIn", "<html><head/><body><p><span style=\" font-size:14pt;\">Username:</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("LogIn", "<html><head/><body><p><span style=\" font-size:14pt;\">Password:</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("LogIn", "<html><head/><body><p><span style=\" font-size:12pt;\">Don't you have an account?</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("LogIn", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; text-decoration: underline; color:#0000ff;\">Sing Up</span></p></body></html>", Q_NULLPTR));
        pushButton_2->setText(QString());
        menuFile->setTitle(QApplication::translate("LogIn", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogIn: public Ui_LogIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
