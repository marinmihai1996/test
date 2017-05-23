#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QString NumeGrup, Client* mClient,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(400 ,200);
    ui->label_3->setText(NumeGrup);
	myClient = mClient;
	qs = NumeGrup;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
   //accepta invitatie
	std::string group = qs.toLocal8Bit().constData();
	std::string message = "joingroup.";
	message.append(group);
	message.append(".");
	message.append(std::to_string(myClient->ID));
	myClient->SendString(message, true);


	myClient->ProcessInvitation(myClient->getCale(), group);
	this->close();
}

void Dialog::on_pushButton_3_clicked()
{
	std::string group = qs.toLocal8Bit().constData();
	myClient->ProcessInvitation(myClient->getCale(), group);
	this->close();
}
