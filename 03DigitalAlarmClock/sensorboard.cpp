#include "sensorboard.h"

#include <QFileInfo>
#include <QDebug>
#include <QProcess>
#include <QTimer>

SensorBoard::SensorBoard()
{
    onTimer = new QTimer(this);
    offTimer = new QTimer(this);

#ifdef RASPI
    gpioPathPattern = "/sys/class/gpio/gpio%1/value";
    tempPathPattern = "/sys/bus/w1/devices/28-000008f679ce/w1_slave";  // TODO: change this to your temperature-sensor path
    setupLedsAndSwitches();
#endif
}

SensorBoard::~SensorBoard()
{
#ifdef RASPI
    switch1File->close();
    switch2File->close();
    switch1File->deleteLater();
    switch2File->deleteLater();
#endif
}

void SensorBoard::processOn(){
    if(ledGreen){
        setGreenLED(true);
    }
    if(ledRed){
        setRedLED(true);
    }
    if(ledYellow){
        setOrangeLED(true);
    }
    if(!offTimer->isActive()){
        offTimer->setSingleShot(true);
        offTimer->start(1000);
    }
}
void SensorBoard::processOff(){
    if(ledGreen){
        setGreenLED(false);
    }
    if(ledRed){
        setRedLED(false);
    }
    if(ledYellow){
        setOrangeLED(false);
    }
}

void SensorBoard::setAlarm(bool alarmActive){
    alarmActivated = alarmActive;
    qDebug() << "setAlarm" << alarmActive;
    //stop timers
    if(onTimer->isActive()){
        onTimer->stop();
    }
    if(offTimer->isActive()){
        offTimer->stop();
    }
    //disconnect so we dont have slots being used double or triple
    onTimer->disconnect();
    offTimer->disconnect();
    if(alarmActivated){
        //reconnect
        connect(onTimer, &QTimer::timeout, this, &SensorBoard::processOn);
        connect(offTimer, &QTimer::timeout, this, &SensorBoard::processOff);
        //start the first timer
        onTimer->start(2000);
    }else{
        //restore initial state
        setGreenLED(ledGreen);
        setRedLED(ledRed);
        setOrangeLED(ledYellow);
    }

}

int SensorBoard::setupLedsAndSwitches()
{
#ifdef RASPI
    int retVal = 0;
    // GPIO-Script setupLedsAndSwitches.sh ausfuehren
    if (!QFileInfo::exists("/sys/class/gpio/gpio17/")) {
        qDebug() << "executing GPIO setup script";
        retVal = QProcess::execute("/bin/sh", QStringList() << "/home/root/setupLedsSwitch.sh");
        if (retVal!=0) {
            qDebug() << "error at executing setupLedsSwitch.sh: Missing file?";
        }
    }

    // Setup QSocketNotifier fuer Taster-Events
    this->setupSwitch1Notifier();
    this->setupSwitch2Notifier();

    return retVal;
#else
    return 0;
#endif
}

void SensorBoard::setupSwitch1Notifier()
{
#ifdef RASPI
    this->switch1File = new QFile(gpioPathPattern.arg(5));
    this->switch1state = this->getButtonSwitch1();

    if (this->switch1File->open(QFile::ReadOnly)) {
        this->switch1File->readAll();
        qDebug() << "Set up SocketNotifier for " << this->switch1File->fileName();
        this->switch1Notifier = new QSocketNotifier(this->switch1File->handle(),QSocketNotifier::Read);
        //this->switch1Notifier->setEnabled(true);

        connect(this->switch1Notifier,SIGNAL(activated(int)), this, SLOT(switch1NotifierActivated()));
    }
#endif
}

void SensorBoard::setupSwitch2Notifier()
{
#ifdef RASPI
    this->switch2File = new QFile(gpioPathPattern.arg(6));
    this->switch2state = this->getButtonSwitch2();

    if (this->switch2File->open(QFile::ReadOnly)) {
        this->switch2File->readAll();
        qDebug() << "Set up SocketNotifier for " << this->switch2File->fileName();
        this->switch2Notifier = new QSocketNotifier(this->switch2File->handle(),QSocketNotifier::Read);

        connect(this->switch2Notifier,SIGNAL(activated(int)), this, SLOT(switch2NotifierActivated()));
    }
#endif
}


void SensorBoard::setGreenLED(bool active)
{
    qDebug() << "setGreenLed" << active;
    if(!alarmActivated) {
        ledGreen = active;}
#ifdef RASPI
    this->writeFile(gpioPathPattern.arg(17),active);
#endif
}

void SensorBoard::setOrangeLED(bool active)
{
    qDebug() << "setOrangeLed" << active;
    if(!alarmActivated) {
        ledYellow = active;}
#ifdef RASPI
    this->writeFile(gpioPathPattern.arg(27),active);
#endif
}

void SensorBoard::setRedLED(bool active)
{
    qDebug() << "setRedLed" << active;
    if(!alarmActivated) {
        ledRed = active;}
#ifdef RASPI
    this->writeFile(gpioPathPattern.arg(22),active);
#endif
}

int SensorBoard::getButtonSwitch1()
{
#ifdef RASPI
    return this->readFile(gpioPathPattern.arg(5)).toInt();
#else
    return 42;
#endif
}

int SensorBoard::getButtonSwitch2()
{
#ifdef RASPI
    return this->readFile(gpioPathPattern.arg(6)).toInt();
#endif
}

/// Hier gibt es eine blockierende und nicht blockierende Variante (im Code als Kommentar gekennzeichnet)
/// Die blockierende Variente liefert einen Rueckgabewert zurueck.
/// Die nicht blockierende Variante liefert immer 0 als Rueckgabewert zurueck und
/// emmitiert ein Signal in temperatureAvailable(), sobald das Ergebnis verfuegbar ist.
/// Nicht-blockierend aber trotzdem gekapselt in einem Funktionsaufruf ist
/// in C++ Qt moeglich mit Futures, z.B. mit QtPromise: https://qtpromise.netlify.app/qtpromise/getting-started.html#example
double SensorBoard::getTemperature()
{
#ifdef RASPI
    double retVal = 0.0;

    if (QFileInfo::exists(tempPathPattern))
    {
        QString program = "cat";
        QStringList arguments = {tempPathPattern};
        QProcess* myProcess = new QProcess();
        myProcess->start(program,arguments);
        // nicht blockierende Variante (=asynchrone Ausfuehrung)
        connect(myProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [=](){
            QString output(myProcess->readAllStandardOutput()); // output should be sth like: 37 02 4b 46 7f ff 09 10 61 : crc=61 YES\n37 02 4b 46 7f ff 09 10 61 t=35437
            myProcess->deleteLater();
            emit temperatureAvailable(parseTemperatureProcessOutput(output));
        });

        // blockierende Variante (=synchrone Ausfuehrung), Problem: Buttons in der GUI sind waehrend waitforFinished() nicht benutzbar da Main-Event-Loop nicht ausgefuehrt wird.
        //        myProcess->waitForFinished(); // blockiert die Main-Event-Loop bis das Ergebnis vorliegt
        //        QString output(myProcess->readAllStandardOutput()); // output should be sth like: 37 02 4b 46 7f ff 09 10 61 : crc=61 YES\n37 02 4b 46 7f ff 09 10 61 t=35437
        //        retVal = parseTemperatureProcessOutput(output);
        //        myProcess->deleteLater();
    }
    return retVal;
#else
    return 0;
#endif
}

void SensorBoard::getCPUload()
{
#ifdef RASPI
    // top -n 1 -b | awk '/^%Cpu/{print $2}'
    // Pipes | koennen nicht als QProcess-Argumente uebergeben werden, darum muss das gesamte Kommando der bash uebergeben werden, siehe https://stackoverflow.com/questions/20901884/piping-or-command-chaining-with-qprocess
    QString program = "bash";
    QStringList arguments = {"-c", "top -n 1 -b | awk '/^%Cpu/{print $2}'"};
    QProcess* myProcess = new QProcess();
    myProcess->start(program,arguments);
    // nicht blockierende Variante (=asynchrone Ausfuehrung)
    connect(myProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](){
        QString output(myProcess->readAllStandardOutput()); // output should be sth like: 37 02 4b 46 7f ff 09 10 61 : crc=61 YES\n37 02 4b 46 7f ff 09 10 61 t=35437
        //qDebug() << "cpuloadavailable: " << output;
        myProcess->deleteLater();
        emit cpuLoadAvailable(output.toDouble());
    });
#endif
}

double SensorBoard::parseTemperatureProcessOutput(QString output)
{
#ifdef RASPI
    QStringList list = output.split("t="); // get access to the number after "t="
    if (list.size()>1)
    {
        return list[1].toInt()*1.0/1000;
    }
    return 0;
#else
    return 0;
#endif
}


void SensorBoard::switch1NotifierActivated()
{
#ifdef RASPI
    int buttonValue = getButtonSwitch1();
    if (this->switch1state != buttonValue) // Steigende/fallende Flanke detektieren
    {
        this->switch1state = buttonValue;
        qDebug() << "switch1NotifierActivated: " << buttonValue;
        emit buttonSwitch1Changed(buttonValue);
    }
#endif
}

void SensorBoard::switch2NotifierActivated()
{
#ifdef RASPI
    int buttonValue = getButtonSwitch2();
    if (this->switch2state != buttonValue) // Steigende/fallende Flanke detektieren
    {
        this->switch2state = buttonValue;
        qDebug() << "switch2NotifierActivated: " << buttonValue;
        emit buttonSwitch2Changed(buttonValue);
    }
#endif
}

void SensorBoard::writeFile(QString path, bool value)
{
#ifdef RASPI
    QFile file(path);
    if (!file.open(QFile::WriteOnly))
    {
        qCritical() << file.errorString();
        Q_ASSERT(false);
    }
    file.write(QString::number((int)value).toUtf8());
    file.close();
#endif
}

QString SensorBoard::readFile(QString path)
{
#ifdef RASPI
    QFile file(path);
    QTextStream textStream(&file);
    QString fileContent;
    if (!file.open(QFile::ReadOnly))
    {
        qCritical() << file.errorString();
        Q_ASSERT(false);
    }
    fileContent = textStream.readAll();
    file.close();
    return fileContent;
#else
    return "";
#endif
}





