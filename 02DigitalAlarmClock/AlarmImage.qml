import QtQuick 2.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

    Item{
        id: alarmImage
        width: parent.width
        height: parent.height
        property alias alarmAnimations : alarmAnimations
        Image{
            id: alarmImageIcon
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            z:5
            scale: 1
            source: "img/iconAlarm.png"
            PropertyAnimation on scale {
                id: alarmImageScaleUp
                from: 1
                to: appWindow.height/128
                duration: 800 //ms
            }
            PropertyAnimation on scale {
                id: alarmImageScaleDown
                from: appWindow.height/128
                to: 1
                duration: 800 //ms
            }
        }
        Rectangle{
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            z:4
            scale: 0
            radius: 1000
            width: alarmImageIcon.width
            height: alarmImageIcon.height
            color: "red"
            PropertyAnimation on scale {
                id: alarmImageBgScaleUp
                from: 0
                to: appWindow.height/128
                duration: 800 //ms
            }
            PropertyAnimation on scale {
                id: alarmImageBgScaleDown
                from: appWindow.height/128
                to: 0
                duration: 800 //ms
            }
        }
        Rectangle{
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: parent.height
            z:3
            color: "white"

            ColorAnimation on color {
                id: alarmImageBgColourToYellow
                from: "white"
                to: "yellow"
                duration: 800
            }
            ColorAnimation on color{
                id: alarmImageBgColourToWhite
                from: "yellow"
                to: "white"
                duration: 800
            }
        }

        MouseArea{
            width: parent.width
            height: parent.height
            onClicked: {
                //stop alarm
                alarmAnimations.stop()
                //show alarm page
                lightingPage.visible = false;
                alarmImagePage.visible = false;
                alarmPage.visible = true;
                timePage.visible = false;
                navBarLabel.text = "Alarm-Einstellung"
            }

        }
        Timer{
            id: alarmAnimations
            interval: 1000 //ms
            repeat: true
            running: false
            triggeredOnStart: false //timer is only started when needed
            property bool toggle: true
            onTriggered: {
                if(toggle){
                    alarmImageBgColourToYellow.start()
                    alarmImageBgScaleUp.start()
                    alarmImageScaleUp.start()
                    toggle = false
                }else{
                    alarmImageBgColourToWhite.start()
                    alarmImageBgScaleDown.start()
                    alarmImageScaleDown.start()
                    toggle = true
                }

            }
        }

    }


