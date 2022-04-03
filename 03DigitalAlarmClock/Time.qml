import QtQuick 2.0

Item {
    id: timeRoot
    visible: true
    width: parent.width
    height: parent.height


    property alias date: timeDisplayDate.text
    property alias time: timeDisplayTime.text

    Text {
        id: timeDisplayTime
        text: qsTr("Uhrzeit")
        font.family: "Helvetica"
        font.pixelSize: parent.height*0.1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: timeDisplayDate.height/2
    }
    Text {
        id: timeDisplayDate
        text: qsTr("Datum")
        font.family: "Helvetica"
        font.pixelSize: parent.height*0.05
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: timeDisplayTime.bottom
    }
}

