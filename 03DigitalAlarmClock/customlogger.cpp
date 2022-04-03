#include "customlogger.h"

static const QString logfile = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd_hh-mm-ss") + ".log";

CustomLogger::CustomLogger()
{}

void CustomLogger::customLog(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QDateTime currTime = QDateTime::currentDateTime();
    QString prefix = currTime.toString("yyyy-MM-dd_hh-mm-ss.zzz");
    QString label;
    switch(type){
    case QtDebugMsg:
            label = " Debug: ";
            break;
        case QtInfoMsg:
            label = " Info: ";
            break;
        case QtWarningMsg:
            label = " Warning: ";
            break;
        case QtCriticalMsg:
            label = " Critical: ";
            break;
        case QtFatalMsg:
            label = " Fatal: ";
            break;
        default:
            label = " Undefined: ";
            break;
    }
    QString output = prefix+label+msg;
    fprintf(stdout,"%s\n", output.toLocal8Bit().data());
    fflush(stdout);

    QFile f(logfile);
    if(f.open(QIODevice::WriteOnly | QIODevice::Append)){
        QTextStream stream(&f);
        stream << output << Qt::endl;
    }else{
        fprintf(stderr, "Could not open logfile");
    }
    f.close();

}
