#include "dialoggroup.h"
#include "ui_dialoggroup.h"
#include <QMessageBox>
#include<QTgui>
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

DialogGroup::DialogGroup(Client* mClient, const QString &arg1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGroup)
{
    ui->setupUi(this);
    this->setFixedSize(690 ,450);
    ui->label_3->setText(arg1);
	//myClient = mClient;
    QPixmap pix("C:/Users/Maria/Documents/git/test/ClientQt/ClientQt");
        ui->sendiomage->setPixmap(pix);
		myClient = mClient;
		QString qs = arg1;
		std::string GroupName = qs.toLocal8Bit().constData();
		mGroupName = arg1;
	//	
   /*   ui->comboBox->addItem("grup1");
        ui->comboBox_2->addItem("user1");*/

		std::string Group = myClient->getAllGroups();

		vector<string> tokens = split(Group, '.');
		//std::cout << "The members are: " << std::endl;
		for (int i = 1; i < tokens.size(); i++) {
			string st = tokens[i];
			qs= QString::fromStdString(st);
			ui->comboBox->addItem(qs);
		}

		myClient->SeeMemeberList(GroupName);
		Sleep(1000);
		std::string Members = myClient->getMembers();

		vector<string> tokens2 = split(Members, '.');
		//std::cout << "The members are: " << std::endl;
		for (int i = 2; i < tokens2.size(); i++) {
			string st = tokens2[i];
			qs = QString::fromStdString(st);
			ui->comboBox_2->addItem(qs);
		}
		//pune ownerul
	/*	if (myClient->getStatut() == Client::owner)
		{
			string st = myClient->getUsername();
			qs = QString::fromStdString(st);
			ui->comboBox_3->addItem(qs);
		}*/
		//pune admin

		myClient->SeeAdminList(GroupName);
		Sleep(1000);
		std::string Admins = myClient->getMembers();

		vector<string> tokens3 = split(Admins, '.');
		//std::cout << "The members are: " << std::endl;
		int j = 1;
		if (myClient->getStatut() == Client::owner) { j = 2; };
		for (int i = j; i < tokens3.size(); i++) {
			string st = tokens3[i];
			qs = QString::fromStdString(st);
			ui->comboBox_3->addItem(qs);
		}

		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(repeat()));
		timer->start(1000);
}


DialogGroup::~DialogGroup()
{
   // delete ui;
}

//void DialogGroup::on_sendButton_pressed()
//{
//     QMessageBox::information(this,"Server Message","button was pressed");
//}


void DialogGroup::on_comboBox_activated(const QString &arg1)
{
      //afisare grupuri si selectare grup cu arg1
	  this->hide();
	DialogGroup mAnother(myClient, arg1);
	mAnother.setModal(true);
	mAnother.exec();
	this->close();
}

void DialogGroup::on_pushButton_2_clicked()
{
//	myClient->InChat = false;
    this->close();
}

void DialogGroup::on_sendButton_clicked()
{
    //ia textul si il trimite
	QString qs=mGroupName;
	//
	std::string mesaj = "chatg.";
	std::string qss = qs.toLocal8Bit().constData();
	mesaj.append(qss);
	mesaj.append(".");	
	QString qs2 = ui->lineEdit->text();
	std::string tex = qs2.toLocal8Bit().constData();
	mesaj.append(std::to_string( myClient->ID));
	mesaj.append(".");
	mesaj.append(tex);
	myClient->SendString(mesaj,true);

	QString qst;
	qst = QString::fromStdString(myClient->getUsername());
	OutChat.append(qst);
	OutChat.append(": ");
	OutChat.append(ui->lineEdit->text());
	OutChat.append("\n");
   ui->textBrowser->setText(OutChat);
   ui->lineEdit->clear();
}

void DialogGroup::afiseazaText(std::string text)
{
	QString qs;
	qs = QString::fromStdString(text);
	OutChat.append("qs");
	ui->textBrowser->setText(OutChat);
}

void DialogGroup::on_comboBox_2_activated(const QString &arg1)
{
   //deschide chat privat cu x

  //this->hide();
  // mDialogPrivate=new DialogPrivate(arg1,this);
  //mDialogPrivate->show();
  // this->close();
}

void DialogGroup::on_comboBox_3_activated(const QString &arg1)
{
    mDialogPrivate=new DialogPrivate(myClient,arg1,this);

    mDialogPrivate->show();
}


void DialogGroup::on_adminButton_clicked()
{
    //QMessageBox::information(this,"Server Message","You are not Admin/Owner");
	std::string adm = "admin";
	if (myClient->getStatut() == Client::owner || myClient->getStatut() == Client::admin)
	{
		mAdmin = new AdminOptions(myClient,mGroupName, this);
		mAdmin->show();
	}
	else
	{
		QMessageBox::information(this, "Server Message", "You don't have the Rights");
	}


}

void DialogGroup::on_adminButton_2_clicked()
{
//	myClient->InChat = false;
    //paraseste grupul
	if (myClient->getStatut() == Client::owner)
	{
		QMessageBox::information(this, "Server Message", "You can't leave this group");
	}
	else
	{
		QString qs = mGroupName;
		std::string groupName = qs.toLocal8Bit().constData();
		std::string message = "kickmember.";
		message.append(std::to_string(myClient->ID));
		message.append(".");
		message.append(groupName);
		message.append(".");
		message.append(std::to_string(myClient->ID));
		message.append(".");
		message.append("leave");
		myClient->SendString(message, true);
		QMessageBox::information(this, "Server Message", "You Left the group");
		this->close();
	}
}


void DialogGroup::repeat()
{
	
	if (myClient->mSemafor == true)
	{
		std::string str= myClient->mMessageSaved;
		QString qs = QString::fromStdString(str);
		OutChat.append(qs);
		ui->textBrowser->setText(OutChat);
		myClient->mSemafor = false;
		myClient->mMessageSaved = "";
	}
	
}
void on_comboBox_2_activated(const QString &arg1)
{


}