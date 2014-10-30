import QtQuick 2.1
import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.0

ApplicationWindow
{
    title: "F0T0N2"
    id: mainWindow
    width: Screen.width
    height: Screen.height
    visible: true
    color: "black"

    //LED grid
    Rectangle
    {
        id: square
        width: Screen.height - topBar.height
        height: square.width
        x: ((Screen.width - sideBar.width)/2 - square.width/2)
        y: topBar.height
        color: Qt.rgba(.7,.7,.7,1)

        PinchArea
        {
            id: area
            anchors.fill: parent
            pinch.target: square
            pinch.minimumScale: 1
            pinch.maximumScale: 1.7
            pinch.dragAxis: Pinch.XAndYAxis
            pinch.minimumX: (-square.width/5)
            pinch.minimumY: (-square.height/5)
            pinch.maximumX: Screen.width - (square.width*.6)
            pinch.maximumY: Screen.height - (square.height*.6)
        }

        //Individual LEDs
        Grid
        {
            id: gridLED
            anchors.fill: square
            rows: 32
            columns: 32

            Repeater
            {
                model: 1024

                Rectangle
                {
                    width: square.width/32
                    height: square.height/32
                    color: 'blue'
                    radius: width*0.5
                    MouseArea
                    {
                        anchors.fill: parent
                        onPressed: { parent.color = 'red' }
                    }
                }
            }
        }

    }

    //top bar
    Rectangle
    {
        id: topBar
        width: Screen.width
        height: Screen.height/11
        gradient: Gradient
        {
                 GradientStop { position: 0.0; color: Qt.rgba(.5,.5,.5,1) }
                 GradientStop { position: 1.0; color: Qt.rgba(.7,.7,.7,1) }
        }
        //Top Buttons
        Row
        {
            anchors.horizontalCenter: parent
            spacing: 0

            Button
            {
                id: colorButton0
                height: topBar.height
                width: topBar.width/6
                text: "color 1"
            }
            Button
            {
                id: colorButton1
                height: topBar.height
                width: topBar.width/6
                text: "color 2"
            }
            Button
            {
                id: colorButton2
                height: topBar.height
                width: topBar.width/6
                text: "color 3"
            }
            Button
            {
                id: colorButton3
                height: topBar.height
                width: topBar.width/6
                text: "color 4"
            }
            Button
            {
                id: colorButton4
                height: topBar.height
                width: topBar.width/6
                text: "color 5"
            }
            Button
            {
                id: colorButton5
                height: topBar.height
                width: topBar.width/6
                text: "color 6"
            }
        }
    }

    //side bar
    Rectangle
    {
        id: sideBar
        width: Screen.width/11
        height: Screen.height - topBar.height
        x: Screen.width - sideBar.width
        y: topBar.height

        //horizontal gradient
        Rectangle
        {
            id: horizGradient
            width: parent.height
            height: parent.width
            anchors.centerIn: parent
            rotation: 90
            gradient: Gradient
            {
                     GradientStop { position: 0.0; color: Qt.rgba(.5,.5,.5,1) }
                     GradientStop { position: 1.0; color: Qt.rgba(.7,.7,.7,1) }
            }
        }
        //side buttons
        Column
        {
             anchors.verticalCenter: parent
             spacing: 0

             Rectangle{height: sideBar.height/10; width: sideBar.width; color: "transparent"}

             Button
             {
                id: clearButton
                height: sideBar.height/10
                width: sideBar.width
                text: "Clear"
             }
             Rectangle{height: sideBar.height/10; width: sideBar.width; color: "transparent"}
             Button
             {
                id: nextButton
                height: sideBar.height/10; width: sideBar.width
                text: "Next"
             }
             Button
             {
                id: prevButton
                height: sideBar.height/10; width: sideBar.width
                text: "Prev"
             }
            Rectangle{height: sideBar.height/5; width: sideBar.width; color: "transparent"}
            Button
            {
                id: addButton
                height: sideBar.height/10; width: sideBar.width
                text: "Clear"
            }
            Button
            {

                id: deleteButton
                height: sideBar.height/10; width: sideBar.width
                text: "Delete"
            }

        }
    }


}
