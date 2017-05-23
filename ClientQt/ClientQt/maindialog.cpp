#include "maindialog.h"
#include "ui_maindialog.h"
#include <QMessageBox>
#include "dialoggroup.h"
#include "dialog.h"
using namespace std;
#include<vector>
static vector<string> split(const string &text, char sep) {
	vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

MainDialog::MainDialog(Client* mClient,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    this->setFixedSize(550 ,270);
	myClient = mClient;

	//ia grupurile
	std::string message = "seegrouplist.";
	message.append(std::to_string(myClient->ID));
	myClient->SendString(message,true);
	Sleep(500);
	std::string Group = myClient->getAllGroups();

	vector<string> tokens = split(Group, '.');

	for (int i = 1; i < tokens.size(); i++) {
		string st = tokens[i];
		QString qs=QString::fromStdString(st);;
		ui->Groups->addItem(qs);
	}

	message = "seeinvitation.";
	message.append(std::to_string(myClient->ID));
	myClient->SendString(message, true);
	Sleep(500);
	std::string Invitations = myClient->getAllinvits();
	vector<string> tokenss = split(Invitations, '.');

	for (int i = 0; i < tokenss.size(); i++) {
		string st = tokenss[i];
		QString qs = QString::fromStdString(st);;
		ui->Invitations->addItem(qs);
	}

}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_Groups_activated(const QString &arg1)
{
	QString qs=arg1;
	std::string nume = qs.toLocal8Bit().constData();
	myClient->ConnectToGroup(nume);
	if (myClient->OKforGroup)
	{
		myClient->InChat = true;
		DialogGroup mDialogGroup(myClient,arg1);
		mDialogGroup.setModal(true);
		mDialogGroup.exec();
	}
}
void MainDialog::on_pushButton_clicked()
{
	QString qs = ui->NumeGrup->text();
	QString Num = qs;
	ui->NumeGrup->clear();
	std::string nume;
	nume = qs.toLocal8Bit().constData();
	myClient->CreateGroup(nume);
	Sleep(1000);
	if (myClient->GroupCreated == true)
	{
		ui->Groups->addItem(Num);
		QMessageBox::information(this, "Server Message", "Group Created");
	}
	else
	{
		QMessageBox::information(this, "Server Message", "The group couldn't be created");
	}
}



void MainDialog::on_NumeGrup_returnPressed()
{
	QString qs = ui->NumeGrup->text();
    ui->NumeGrup->clear();
	std::string nume;
	nume= qs.toLocal8Bit().constData();
	myClient->CreateGroup(nume);
	Sleep(1000);
	if (myClient->GroupCreated == true)
	{ui->Groups->addItem(qs);
		QMessageBox::information(this, "Server Message", "Group Created");
	}
	else
	{
		QMessageBox::information(this, "Server Message", "The name is taken! Choose another one!");
	}

}

void MainDialog::on_Messages_activated(const QString &arg1)
{
    //vede direct mesajul

}

void MainDialog::on_Invitations_activated(const QString &arg1)
{
      Dialog mDialog1(arg1,myClient);
      mDialog1.setModal(true);
      mDialog1.exec();
	  std::string message = "seegrouplist.";
	  message.append(std::to_string(myClient->ID));
	  myClient->SendString(message, true);
	  Sleep(500);
	  std::string Group = myClient->getAllGroups();

	  vector<string> tokens = split(Group, '.');

	  for (int i = tokens.size()-1; i < tokens.size(); i++) {
		  string st = tokens[i];
		  QString qs = QString::fromStdString(st);;
		  ui->Groups->addItem(qs);
	  }
}

void MainDialog::on_Invitations_activated(int index)
{
	
	ui->Invitations->removeItem(index);

}

