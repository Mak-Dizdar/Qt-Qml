import QtQuick 2.7
import QtQuick.Window 2.14
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ApplicationWindow{
    id: appWindow
    height: 480
    width: 640
    minimumHeight: 480
    minimumWidth: 640
    visible: true
    title: "Digital Alarm Clock"


    Connections{
        target: timer
        onTimeChanged: {
            timePage.time = time
            timePage.date = date
        }
    }



    //header
    header: ToolBar{
        RowLayout{
            anchors.fill: parent
            ToolButton{
                Image{
                    width: parent.width
                    height: parent.height
                    source: "img/btnDrawer.png"
                }
                onClicked:{
                    menuDrawer.position === 0 ? menuDrawer.open() : menuDrawer.close()
                }
            }

            // Text - leider off center da der Button nicht mitgerechnet wird beim Alignment
            Label{
                id: navBarLabel
                text: "Aktuelle Uhrzeit"
                horizontalAlignment: "AlignHCenter"
                verticalAlignment: "AlignVCenter"
                Layout.fillWidth: true
                font.bold: true
            }
        }
    }
    //navigationsmenue
    Drawer{
        id: menuDrawer
        height: appWindow.height
        width: appWindow.width * 0.4

        ColumnLayout{
            anchors.fill: parent
            Button{
                Layout.fillWidth: true
                Layout.fillHeight: true
                Image{
                    id: btnTimeImg
                    source: "img/btnTime.png"
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text{
                    text: "Uhrzeit"
                    font.family: "Helvetica"
                    font.pixelSize: 25
                    leftPadding: 10
                    anchors.left: btnTimeImg.right
                    anchors.verticalCenter: parent.verticalCenter
                }
                palette{
                    button: "white"
                }
                onClicked: {
                    menuDrawer.close()
                    //show only one page
                    lightingPage.visible = false;
                    alarmPage.visible = false;
                    timePage.visible = true;
                    navBarLabel.text = "Aktuelle Uhrzeit"
                }
            }
            Button{
                Layout.fillWidth: true
                Layout.fillHeight: true
                Image{
                    id: btnAlarmImg
                    source: "img/btnAlarm.png"
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text{
                    text: "Alarm-Einstellung"
                    font.family: "Helvetica"
                    font.pixelSize: 25
                    leftPadding: 10
                    anchors.left: btnAlarmImg.right
                    anchors.verticalCenter: parent.verticalCenter
                }
                palette{
                    button: "white"
                }
                onClicked: {
                    menuDrawer.close()
                    //show only one page
                    lightingPage.visible = false;
                    alarmPage.visible = true;
                    timePage.visible = false;
                    navBarLabel.text = "Alarm-Einstellung"
                }
            }
            Button{
                Layout.fillWidth: true
                Layout.fillHeight: true
                Image{
                    id: btnLighting
                    source: "img/btnLighting.png"
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text{
                    text: "Beleuchtung"
                    font.family: "Helvetica"
                    font.pixelSize: 25
                    leftPadding: 10
                    anchors.left: btnLighting.right
                    anchors.verticalCenter: parent.verticalCenter
                }
                palette{
                    button: "white"
                }
                onClicked: {
                    menuDrawer.close()
                    //show only one page
                    lightingPage.visible = true;
                    alarmPage.visible = false;
                    timePage.visible = false;
                    navBarLabel.text = "LEDs"
                }
            }
        }
    }

    Image{
        id: backgroundImage
        width: parent.width
        height: parent.height
        state: "background1"
        source: "img/background1.jpg"
        PropertyAnimation on opacity {
            id: backgroundImageFadeIn
            from: 0
            to: 1
            duration: 500
        }
        PropertyAnimation on opacity {
            id: backgroundImageFadeOut
            from: 1
            to: 0
            duration: 500
        }
    }

    Connections{
        target: timer
        property int ctr: 0
        onTimeChanged: {
            if(ctr == 5){
                ctr = 0
                backgroundImageFadeOut.start()
                backgroundImageFadeInStartTimer.start()
            }else{
                ctr++
            }
        }
    }

    Timer{
        id: backgroundImageFadeInStartTimer
        interval: 500 //ms
        repeat: false
        running: false
        triggeredOnStart: false //timer is only started when needed by backgroundImageChangeTimer
        onTriggered: {
            backgroundImageFadeIn.start()
            //swap the background picture
            //the images do give an error, however this is due to the colourspace used
            //thus it is not really relevant for the scope of this exercise
            if(backgroundImage.state == "background1"){
                backgroundImage.state = "background2"
                backgroundImage.source = "img/background2.jpg"
            }else if(backgroundImage.state == "background2"){
                backgroundImage.state = "background1"
                backgroundImage.source = "img/background1.jpg"
            }
        }

    }

    //change visibility for alarm
    Connections{
        target: timer
        onTriggerAlarm: {
            alarmImagePage.visible = true;
            timePage.visible = false
            alarmPage.visible = false
            lightingPage.visible = false
        }
    }

    //stop alarm with button 1
    Connections{
        target: sensor
        onButtonSwitch1Changed:{
            alarmImagePage.stopAlarm()
            console.log("Alarm stopped with button");
        }
    }
    //change with button 2
    Connections{
        target: sensor
        onButtonSwitch2Changed:{
			if(value == 1){
				if(timePage.visible){ // 1 -> 2
					timePage.visible = false
					alarmPage.visible = true
					lightingPage.visible = false
					navBarLabel.text = "Alarm-Einstellung"
				}else if(alarmPage.visible){
					timePage.visible = false
					alarmPage.visible = false
					lightingPage.visible = true
					navBarLabel.text = "LEDs"
				}else if(lightingPage.visible){
					timePage.visible = true
					alarmPage.visible = false
					lightingPage.visible = false
					navBarLabel.text = "Aktuelle Uhrzeit"
				}else{
					console.log("Button pressed during alarm");
				}
			}
		}
    }

    property alias alarm: alarmImagePage.visible
    AlarmImage{
        visible: false
        id: alarmImagePage
    }

    Lighting{
        id: lightingPage
    }
    Alarm{
        id: alarmPage
    }
    Time{
        id: timePage
    }
}
