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
        height: parent.height * 0.5
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
                Layout.fillHeight: true
                Layout.fillWidth: true
                SwitchDelegate{
                    id: led1switch
                    width: parent.width
                    text:"LED1  "
                    Layout.alignment: "AlignCenter"
                    checked: false
                    opacity: led1switch.checked ? 1 : 0.5
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onCheckedChanged: {
                        sensor.setGreenLED(checked)
                    }
                }
                Image{
                    source: "img/btnLightingGreen.png"
                    id: led1img
                    opacity: led1switch.checked ? 1 : 0.5
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }



            }
            RowLayout{
                width: parent.width
                height: parent.height
                Layout.alignment: "AlignCenter"

                Layout.fillHeight: true
                Layout.fillWidth: true
                SwitchDelegate{
                    id: led2switch
                    width: parent.width
                    text:"LED2  "
                    Layout.alignment: "AlignCenter"
                    checked: false
                    opacity: led2switch.checked ? 1 : 0.5
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onCheckedChanged: {
                        sensor.setOrangeLED(checked)
                    }
                }
                Image{
                    source: "img/btnLightingYellow.png"
                    id: led2img
                    opacity: led2switch.checked ? 1 : 0.5
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            }
            RowLayout{
                width: parent.width
                height: parent.height
                Layout.alignment: "AlignCenter"

                Layout.fillHeight: true
                Layout.fillWidth: true
                SwitchDelegate{
                    id: led3switch
                    width: parent.width
                    text:"LED3  "
                    Layout.alignment: "AlignCenter"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    checked: false
                    opacity: led3switch.checked ? 1 : 0.5
                    onCheckedChanged: {
                        sensor.setRedLED(checked)
                    }
                }
                Image{
                    source: "img/btnLightingRed.png"
                    id: led3img
                    opacity: led3switch.checked ? 1 : 0.5
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            }


        }


    }

}
