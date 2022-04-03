import QtQuick 2.7
import QtQuick.Window 2.14
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
                onCheckedChanged: {
                    if(alarmActivateSwitch.checked){
                        timer.setAlarm(hoursTumbler.currentIndex.toString(),minutesTumbler.currentIndex.toString())
                        console.log("Alarm switch checked");
                    }
                }
            }
        }
    }

    Connections{
        target: timer
        onTriggerAlarm: {
            alarmActivateSwitch.checked = false
        }
    }


}
