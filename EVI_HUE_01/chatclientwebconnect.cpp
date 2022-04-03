#include "chatclientwebconnect.h"

#include <QtWebSockets>
#include <QtCore>

chatclientwebconnect::chatclientwebconnect(QObject* parent) : QObject(parent){
    //init signals for connect/disconnect from server
    //message received can only be set after a server was connected
    connect(&m_qchatWebSocket,&QWebSocket::connected,this,&chatclientwebconnect::onConnected);
    connect(&m_qchatWebSocket, &QWebSocket::disconnected, this, &chatclientwebconnect::onDisconnected);
}

void chatclientwebconnect::connectToServer(QString url){
    m_qchatWebSocket.open(QUrl(url));
    qDebug() << "opened connection to " + url;
}

void chatclientwebconnect::onConnected(){
    m_isConnected = true;
    //callback for successful connection
    emit connectedToServer();
    connect(&m_qchatWebSocket, &QWebSocket::textMessageReceived,this,&chatclientwebconnect::onMessageReceived);
    qDebug() << "server connected";
}

void chatclientwebconnect::onDisconnected(){
    qDebug() << "server disconnected";
    emit disconnectedFromServer();
}

void chatclientwebconnect::onMessageReceived(QString message){
    emit messageReceived(message);
    qDebug() << "Received message: " << message;
}

void chatclientwebconnect::disconnectFromServer(){
    m_qchatWebSocket.close();
    qDebug() << "closed connection";
}

void chatclientwebconnect::sendMessage(QString message){
    qDebug() << "Sent message: " << message;
    m_qchatWebSocket.sendTextMessage(message);
}
QString chatclientwebconnect::getConnectionState(){
    switch(m_qchatWebSocket.state()){
    case QAbstractSocket::UnconnectedState:
        return "Unconnected";
    case QAbstractSocket::HostLookupState:
        return "host lookup";
    case QAbstractSocket::ConnectingState:
        return "Connecting";
    case QAbstractSocket::ConnectedState:
        return "Connected";
    case QAbstractSocket::BoundState:
        return "Bound";
    case QAbstractSocket::ListeningState:
        return "Listening";
    case QAbstractSocket::ClosingState:
        return "Closing";
    default:
        return "Invalid";
    }
}
