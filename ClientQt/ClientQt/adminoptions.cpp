#include "adminoptions.h"
#include "ui_adminoptions.h"
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

AdminOptions::AdminOptions(Client* mClient,QString numeGrup ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOptions)
{
    ui->setupUi(this);
    this->setFixedSize(300 ,400);
	myClient = mClient;
	mGroupName = numeGrup;
	std::string GroupName=numeGrup.toLocal8Bit().constData();
	myClient->SeeAdminList(GroupName);
	Sleep(1000);
	std::string Admins = myClient->getMembers();
	QString qs;
	vector<string> tokens3 = split(Admins, '.');
	//std::cout << "The members are: " << std::endl;
	int j = 1;
	if (myClient->getStatut() == Client::owner) { j = 2; };
	for (int i = j; i < tokens3.size(); i++) {
		string st = tokens3[i];
		qs = QString::fromStdString(st);
		ui->comboBox_3->addItem(qs);
	}

	myClient->SeeMemeberList(GroupName);
	Sleep(1000);
	std::string Members = myClient->getMembers();

	vector<string> tokens2 = split(Members, '.');
	//std::cout << "The members are: " << std::endl;
	for (int i = 2; i < tokens2.size(); i++) {
		string st = tokens2[i];
		qs = QString::fromStdString(st);
		ui->comboBox->addItem(qs);
		ui->comboBox_2->addItem(qs);
	}
}

AdminOptions::~AdminOptions()
{
    delete ui;
}

void AdminOptions::on_comboBox_activated(const QString &arg1)
{
    //il scoate pe arg1 din grup
	QString numeGrup = mGroupName;
	std::string groupName = numeGrup.toLocal8Bit().constData();
	QString qs = arg1;
	std::string username= qs.toLocal8Bit().constData();
	std::string message = "kickmember.";
	message.append(std::to_string(myClient->ID));
	message.append(".");
	message.append(groupName);
	message.append(".");
	message.append(username);
	message.append(".");
	message.append("kick");
	myClient->SendString(message, true);

}
void AdminOptions::on_comboBox_activated(int index)
{
	ui->comboBox->removeItem(index);
}
void AdminOptions::on_comboBox_2_activated(const QString &arg1)
{
    //il face admin pe arg1
	ui->comboBox_3->addItem(arg1);
	QString numeGrup = mGroupName;
	std::string groupName = numeGrup.toLocal8Bit().constData();
	QString qs = arg1;
	std::string username = qs.toLocal8Bit().constData();
	std::string message = "makeadmin.";
	message.append(std::to_string(myClient->ID));
	message.append(".");
	message.append(groupName);
	message.append(".");
	message.append(username);	
	myClient->SendString(message, true);
}

void AdminOptions::on_comboBox_3_activated(int index)
{
	ui->comboBox_3->removeItem(index);
}
void AdminOptions::on_pushButton_2_clicked()
{
	QString qs=ui->lineEdit->text();
	ui->lineEdit->clear();
	std::string username = qs.toLocal8Bit().constData();
	QString numeGrup = mGroupName;
	std::string groupName = numeGrup.toLocal8Bit().constData();
std:string aux = "inviteclient";
	aux.append(".");
	aux.append(std::to_string(myClient->ID));

	aux.append(".");
	aux.append(username);
	aux.append(".");
	aux.append(groupName);
	myClient->SendString(aux, true);
	ui->lineEdit->clear();
}

void AdminOptions::on_pushButton_clicked()
{
	QString numeGrup = mGroupName;
	std::string groupName = numeGrup.toLocal8Bit().constData();
	string message = "deleteGroup.";
	message.append(std::to_string(myClient->ID));
	message.append(".");
	message.append(groupName);
	myClient->SendString(message, true);
	this->close();
}
void AdminOptions::on_comboBox_3_activated(const QString &arg1)
{
	QString numeGrup = mGroupName;
	std::string groupName = numeGrup.toLocal8Bit().constData();
	QString qs = arg1;
	std::string username = qs.toLocal8Bit().constData();
	string Message = "downgradeadmin.";
	Message.append(std::to_string(myClient->ID));
	Message.append(".");
	Message.append(groupName);
	Message.append(".");
	Message.append(username);
	myClient->SendString(Message, true);

}