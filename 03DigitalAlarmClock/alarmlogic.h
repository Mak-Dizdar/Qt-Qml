#ifndef ALARMLOGIC_H
#define ALARMLOGIC_H

#include <QObject>
#include <qtimer.h>

class AlarmLogic : public QObject
{
    Q_OBJECT
public:
    explicit AlarmLogic(QObject *parent = nullptr);
public slots:
    void setAlarm(QString hours, QString minutes);

signals:
    void triggerAlarm();
    void timeChanged(QString time, QString date);
private:
    QTimer* clockTimer;
    QString hours;
    QString minutes;

    void checkForAlarm();
    void updateTime();

};

#endif // ALARMLOGIC_H
