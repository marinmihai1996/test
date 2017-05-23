#include "dialogprivate.h"
#include "ui_dialogprivate.h"

DialogPrivate::DialogPrivate(Client* mClient, QString ClientName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPrivate)
{
    ui->setupUi(this);
    this->setFixedSize(711 ,448);
    ui->label_2->setText(ClientName);
    QPixmap pix("D:/test/Client/sendimage");
        ui->sendiomage->setPixmap(pix);
		myClient = mClient;
		mUsername = ClientName;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(repeat()));
	timer->start(1000);
}

DialogPrivate::~DialogPrivate()
{
    delete ui;
}

void DialogPrivate::on_pushButton_clicked()
{
    //ia textu si il trimite
    OutChat.append(ui->lineEdit->text());
	ui->textBrowser->setText(OutChat);
	std::string name;
	QString qs = mUsername;

}

void DialogPrivate::repeat()
{

	if (myClient->mSemafor == true)
	{
		std::string str = myClient->mMessageSaved;
		QString qs = QString::fromStdString(str);
		OutChat.append(qs);
		ui->textBrowser->setText(OutChat);
		myClient->mSemafor = false;
		myClient->mMessageSaved = "";
	}

}