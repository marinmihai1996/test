#include "singup.h"
#include "ui_singup.h"
#include <QMessageBox>
SingUp::SingUp(Client* mClient,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingUp)  
{
    ui->setupUi(this);
    this->setFixedSize(800,375);
    QPixmap pix("D:/test/Client/letschat.png");
        ui->imagine->setPixmap(pix);
		myClient = mClient;
}

SingUp::~SingUp()
{
    delete ui;
}


void SingUp::on_pushButton_clicked()
{
	QString qs1,qs2;
	qs1 = ui->lineEdit_2->text();
	std::string password = qs1.toLocal8Bit().constData();
	qs2 = ui->lineEdit_3->text();
	std::string password2 = qs2.toLocal8Bit().constData();
	if (password != password2)
	{
		QMessageBox::information(this, "Server Message", "The passwords are not the same");
	}
	else
	{
		QString qs;
		qs = ui->lineEdit->text();
		std::string username = qs.toLocal8Bit().constData();
		myClient->SingUp(username,password);
		QMessageBox::information(this, "Server Message", "You are registred");
	}
    this->close();
}
