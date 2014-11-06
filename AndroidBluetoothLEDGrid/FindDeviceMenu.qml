import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    anchors.fill:parent
    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "#202020";
        }
        GradientStop {
            position: 1.00;
            color: "#494949";
        }
    }
    id:topRect

    ListModel {
        id: deviceModel
    }
    Connections{
        target: LedBoardManager
        onFoundLedBoard:{
            console.log("Found " + dname, dmac);
            deviceModel.append({"deviceName":dname,"deviceAddress":dmac});
        }
        onFinishedScanning:{
           busy.running = false;
           console.log("Finished scanning");
        }
        onConnectedToLedBoard:{
            console.log("Connected to " + deviceID);
            topRect.visible = false;
            boardView.visible = true;
        }
    }

    property string deviceID: ""

    Rectangle{
        anchors.top: busy.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: button.top
        color: "transparent"
        border.color: "transparent"
        clip: true
        radius: 4
        ListView{
            id:deviceList
            anchors.fill: parent
            highlightFollowsCurrentItem: true
            focus: true
            model: deviceModel
            highlight: Rectangle { color: "lightsteelblue"; width: parent.width; height: 360; radius: 5 }
            delegate: Rectangle {
                id: deviceDelegate
                width: parent.width
                height: 480

                clip: true
                color: "black"
                opacity: .6
                border.color: "white"
                border.width: 2
                anchors.margins: 1
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        deviceList.currentIndex = index;
                        deviceID = deviceName;
                    }
                }

                property alias deviceId: bttext.text

                Text {
                    id: bttext
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.verticalCenter
                    color: "steelblue"
                    text: deviceName ? deviceName : name
                    font.pixelSize:120
                    horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    id: details
                    anchors.top: bttext.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 120

                    text: deviceAddress
                    horizontalAlignment: Text.AlignHCenter
                    color:"white"
                    font.pixelSize: 80

                }
                Rectangle{
                    id:connectButton
                    visible: (index == deviceList.currentIndex)
                    height: parent.height/4
                    width: parent.width/4
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    color: "green"
                    border.color: "white"
                    border.width: 2
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            LedBoardManager.connectToBoard(deviceName,deviceAddress);
                        }
                    }
                    Text {
                        id: connectText
                        anchors.fill: parent
                        text: "Connect"
                        horizontalAlignment: Text.AlignHCenter
                        color:"yellow"
                        font.pixelSize: height * .7

                    }
                }
            }
        }
    }
    Rectangle{
        id: button

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        anchors.bottom: parent.bottom
        height: parent.height/12
        border.color: "white"
        enabled : !busy.running
        color: enabled ? "darkblue":"darkgrey"
        radius: 60
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("Scanning for LEDBoards:");
                deviceModel.clear();
                LedBoardManager.findLedBoard();
                busy.running = true;
            }
        }

        Text{
            anchors.fill: parent
            color: button.enabled ? "yellow":"black"
            text: deviceID == "" ? "Search for Devices" :("Connect To " +deviceID)
            font.pixelSize: height *.4
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    Rectangle {
        id: busy
        width: topRect.width
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: topRect.top;
        anchors.topMargin: 20
        height: text.height*1.2;
        color: "#1c56f3"
        border.width: 4
        border.color: "black"
        visible: true
        property bool running: false
        Text {
            id: text
            text: busy.running ? "Scanning":"Choose a Device"
            color: busy.running ? "black":"white"
            font.bold: true
            font.pointSize:40
            anchors.centerIn: parent
        }

        SequentialAnimation on color {
            id: busyThrobber
            running: busy.running
            onStopped: {
                busy.color = "#1c56f3";
            }

            ColorAnimation { easing.type: Easing.InOutSine; from: "#1c56f3"; to: "white"; duration: 1000; }
            ColorAnimation { easing.type: Easing.InOutSine; to: "#1c56f3"; from: "white"; duration: 1000 }
            loops: Animation.Infinite
        }
    }
}
