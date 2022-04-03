#ifndef CHATCLIENTWEBCONNECT_H
#define CHATCLIENTWEBCONNECT_H


#include <QtCore>
#include <QtCore/QObject>
#include <QtWebSockets>


class chatclientwebconnect : public QObject
{
    Q_OBJECT
public:
    chatclientwebconnect(QObject* parent);

    void connectToServer(QString url);
    void onConnected();
    void onDisconnected();
    void onMessageReceived(QString message);
    void disconnectFromServer();
    void sendMessage(QString message);
    QString getConnectionState();
    virtual ~chatclientwebconnect() {}
private:
    QWebSocket m_qchatWebSocket;
    bool m_isConnected;
signals:
    void connectedToServer();
    void disconnectedFromServer();
    void messageReceived(QString message);
};

#endif // CHATCLIENTWEBCONNECT_H
