import QtQuick 2.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id: alarmRoot
    visible: false
    width: parent.width
    height: parent.height

    Rectangle{
        width: parent.width * 0.4
        height: parent.height * 0.8
        radius: 5
        color: "white"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter


        ColumnLayout{
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter


            RowLayout{
                width: parent.width
                height: parent.height
                Layout.alignment: "AlignCenter"
                spacing: 15

                Tumbler{
                    id: hoursTumbler
                    model: 24
                    font.pixelSize: height * 0.1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Tumbler{
                    id: minutesTumbler
                    model: 60
                    font.pixelSize: height * 0.1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            }
            SwitchDelegate{
                id: alarmActivateSwitch
                Layout.fillHeight: true
                Layout.fillWidth: true
                text:"Alarm aktivieren  "
                Layout.alignment: "AlignCenter"
                font.pixelSize: height * 0.25
                checked: false
            }
        }
    }

    Timer{
        id: alarmTimer
        interval: 1000 //Check every second if an Alarm should be started
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            if(alarmActivateSwitch.checked){
                //check to trigger alarm
                var currHour = new Date().toLocaleTimeString(Qt.locale("de_DE"),"h")
                var currMinute = new Date().toLocaleTimeString(Qt.locale("de_DE"),"m")
                if(hoursTumbler.currentIndex.toString() === currHour && minutesTumbler.currentIndex.toString() === currMinute){
                    //trigger alarm
                    alarmImagePage.visible = true
                    timePage.visible = false
                    alarmPage.visible = false
                    lightingPage.visible = false
                    alarmImagePage.alarmAnimations.start()
                    alarmActivateSwitch.checked = false;
                }
            }

        }

    }

}
