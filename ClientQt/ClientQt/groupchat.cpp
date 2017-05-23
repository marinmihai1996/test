#include "groupchat.h"
#include "ui_groupchat.h"

GroupChat::GroupChat(Client* mClient,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);
	myClient = mClient;
}

GroupChat::~GroupChat()
{
    delete ui;
}
