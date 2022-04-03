#ifndef CUSTOMLOGGER_H
#define CUSTOMLOGGER_H
#include<QString>
#include<QDateTime>
#include<QFile>
#include <QTextStream>

class CustomLogger
{
public:
    CustomLogger();

    static void customLog(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};

#endif // CUSTOMLOGGER_H
