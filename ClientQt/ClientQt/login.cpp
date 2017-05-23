#include "login.h"
#include "ui_login.h"
#include "singup.h"
#include <QMainWindow>
#include "maindialog.h"
#include <QMessageBox>

LogIn::LogIn(Client* mClient, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    this->setFixedSize(350,500);
	myClient = mClient;
	

}

LogIn::~LogIn()
{

    delete ui;
}

void LogIn::on_pushButton_2_clicked()
{
    this->hide();
    SingUp mSingup(myClient);
    mSingup.setModal(true);
    mSingup.exec();
    this->show();

}



void LogIn::on_pushButton_clicked()
{
	QString qs;
	qs = ui->lineEdit->text();
	std::string username = qs.toLocal8Bit().constData();
	qs = ui->lineEdit_2->text();
	std::string password = qs.toLocal8Bit().constData();

	//if(myClient->LogIn(username,password))
	
	myClient->LogIn(username, password);
	if (myClient->OkSingUp == true)
	{
		this->hide();
		MainDialog mMainDialog(myClient);
		mMainDialog.setModal(true);
		mMainDialog.exec();
		this->close();
	}
	else{ QMessageBox::information(this, "Error", "Wrong username or password"); }

}

void LogIn::on_actionExit_triggered()
{
    this->close();
}

void LogIn::on_actionSing_Up_triggered()
{
    this->hide();
    SingUp mSingup(myClient);
    mSingup.setModal(true);
    mSingup.exec();
    this->show();
}


