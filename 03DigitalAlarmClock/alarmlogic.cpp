#include "alarmlogic.h"

#include <QDateTime>
#include <QDebug>

AlarmLogic::AlarmLogic(QObject *parent) : QObject(parent)
{
    clockTimer = new QTimer();
    hours = "invalid";
    minutes = "invalid";
    connect(clockTimer, &QTimer::timeout,this,&AlarmLogic::checkForAlarm);
    connect(clockTimer, &QTimer::timeout, this, &AlarmLogic::updateTime);
    clockTimer->start(1000);
}

void AlarmLogic::checkForAlarm(){
   QDateTime currTime = QDateTime::currentDateTime();
   if(this->hours == currTime.toString("h") && this->minutes == currTime.toString("m")){
       qDebug() << "alarm triggered";
       emit triggerAlarm();
       this->hours = "invalid";
       this->minutes = "invalid";
   }
}

void AlarmLogic::setAlarm(QString hours, QString minutes){
    qDebug() << "time for alarm set to" << hours << ":" << minutes;
    this->hours = hours;
    this->minutes = minutes;
}

void AlarmLogic::updateTime(){
    QDateTime currTime = QDateTime::currentDateTime();
    QString date = currTime.toString("dddd, dd.MM.yyyy");
    QString time = currTime.toString("hh:mm:ss");
    emit timeChanged(time,date);

}

