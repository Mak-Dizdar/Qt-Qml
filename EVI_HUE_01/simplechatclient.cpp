#include "simplechatclient.h"

#include <QVBoxLayout>

SimpleChatClient::SimpleChatClient(QWidget *parent)
    : QMainWindow(parent)
{
    m_chatClient = new chatclientwebconnect(this);

    //create widgets
    this->headerLabel=new QLabel("WebSocket Chat Client");
    this->hostLabel=new QLabel ("Host:") ;
    this->serverAddressLineEdit=new QLineEdit();
    this->chatWindowTextEdit=new QTextEdit();
    this->usernameLineEdit=new QLineEdit();
    this->messageLineEdit=new QLineEdit();
    this->connectPushButton=new QPushButton("Connect");
    this->disconnectPushButton=new QPushButton("Disconnect");
    this->statePushButton=new QPushButton("State");
    this->sendPushButton=new QPushButton("Send");

    //positioning
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* hostLayout = new QHBoxLayout();
    QHBoxLayout* connectButtonsLayout = new QHBoxLayout();
    QHBoxLayout* messageLayout = new QHBoxLayout();

    hostLayout->addWidget(hostLabel);
    hostLayout->addWidget(serverAddressLineEdit);

    connectButtonsLayout->addWidget(connectPushButton);
    connectButtonsLayout->addWidget(disconnectPushButton);
    connectButtonsLayout->addWidget(statePushButton);

    messageLayout->addWidget(usernameLineEdit);
    messageLayout->addWidget(messageLineEdit);
    messageLayout->addWidget(sendPushButton);

    mainLayout->addWidget(headerLabel);
    mainLayout->addLayout(hostLayout);
    mainLayout->addLayout(connectButtonsLayout);
    mainLayout->addWidget(chatWindowTextEdit);
    mainLayout->addLayout(messageLayout);

    QWidget* mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);

    //websocket functionality
    connect(m_chatClient,&chatclientwebconnect::connectedToServer, this, &SimpleChatClient::handleConnect);
    connect(m_chatClient,&chatclientwebconnect::disconnectedFromServer, this, &SimpleChatClient::handleDisconnect);
    connect(m_chatClient,&chatclientwebconnect::messageReceived, this, &SimpleChatClient::handleMessageReceived);

    //connect button signals
    connect(this->connectPushButton,&QPushButton::clicked,this, &SimpleChatClient::onConnectButtonClicked);
    connect(this->disconnectPushButton, &QPushButton::clicked,this,&SimpleChatClient::onDisconnectButtonClicked);
    connect(this->statePushButton, &QPushButton::clicked, this, &SimpleChatClient::onStateButtonClicked);
    connect(this->sendPushButton, &QPushButton::clicked, this, &SimpleChatClient::onSendButtonClicked);

    this->headerLabel->setStyleSheet("font-weight: bold; font-size: 17px");
    this->setStyleSheet("QLineEdit { font-size: 15px }");
    this->setStyleSheet("QPushButton { font-size: 16px}");

    //initial state of buttons
    this->disconnectPushButton->setEnabled(false);
    this->connectPushButton->setEnabled(true);
    this->connectPushButton->setStyleSheet("background-color:red");

    this->serverAddressLineEdit->setText("ws://localhost:1234");
    this->usernameLineEdit->setText("Riegler");

    this->chatWindowTextEdit->setReadOnly(true);

    //this->showFullScreen();
    qDebug() << "SimpleChatClient constructor done";
}

void SimpleChatClient::handleConnect(){
    qDebug() << "handleConnect called";
    this->connectPushButton->setEnabled(false);
    this->disconnectPushButton->setEnabled(true);
    this->connectPushButton->setStyleSheet("background-color:green");
    this->chatWindowTextEdit->append("CONNECTED");
}

void SimpleChatClient::handleDisconnect(){
    qDebug() << "handleDisconnect called";
    this->disconnectPushButton->setEnabled(false);
    this->connectPushButton->setEnabled(true);
    this->connectPushButton->setStyleSheet("background-color:red");
    this->chatWindowTextEdit->append("DISCONNECTED");
}

void SimpleChatClient::handleMessageReceived(QString message){
    qDebug() << "handleMessageReceived called";
    this->chatWindowTextEdit->append(message);
}

void SimpleChatClient::onConnectButtonClicked(){
    qDebug() << "connectButtonClicked";
    QString host = this->serverAddressLineEdit->text();
    if(host!=nullptr){
        m_chatClient->connectToServer(host);
    }else{
        this->chatWindowTextEdit->append("No server entered");
    }

}
void SimpleChatClient::onDisconnectButtonClicked(){
    qDebug() << "disconnectButtonClicked";
    m_chatClient->disconnectFromServer();
}
void SimpleChatClient::onSendButtonClicked(){
    qDebug() << "sendButtonClicked";
    QString message = this->messageLineEdit->text();
    QString name = this->usernameLineEdit->text();
    QString sendstring;
    if(name != nullptr){
        sendstring += name;
    }else{
        sendstring += "<empty>";
    }
    sendstring += ": ";
    if(message != nullptr){
        sendstring += message;
    }
    m_chatClient->sendMessage(sendstring);
    this->chatWindowTextEdit->append(sendstring);
    //clear input
    this->messageLineEdit->setText("");
}
void SimpleChatClient::onStateButtonClicked(){
    qDebug() << "stateButtonClicked";
    this->chatWindowTextEdit->append(this->m_chatClient->getConnectionState());
}

SimpleChatClient::~SimpleChatClient()
{
}

