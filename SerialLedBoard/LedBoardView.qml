import QtQuick 2.3
import QtQuick.Controls 1.2
Rectangle {
    //LED grid
    Rectangle
    {
        id: square
        width: ScreenHeight - topBar.height
        height: square.width
        x: ((ScreenWidth - sideBar.width)/2 - square.width/2)
        y: topBar.height
        color: Qt.rgba(.7,.7,.7,1)
        Connections{
            target: SerialLedBoard
            onLedSet:
            {
                //console.log("led number ", ((row*32) + col));
                var item_found = ledBoard.itemAt(((row*32) + col));
                item_found.color = ledcolor;
            }
        }

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
            pinch.maximumX: ScreenWidth - (square.width*.6)
            pinch.maximumY: ScreenHeight- (square.height*.6)
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
                id:ledBoard
                Rectangle
                {
                    objectName:("led" + index.toString())
                    width: square.width/32
                    height: square.height/32
                    color: 'blue'
                    radius: width*0.5
                    MouseArea
                    {
                        anchors.fill: parent
                        onPressed: {
                            parent.color = 'red';
                            var row = Math.floor(index/32);
                            var col = index % 32;
                         //   console.log("sending led @ Rx" + row + " Cx" + col);
                         //   LedBoardManager.sendLedSet(row, col, Qt.rgba(211,0,214,255));
                        }

                    }
                }
            }
        }

    }

    //top bar
    Rectangle
    {
        id: topBar
        width: ScreenWidth
        height: ScreenHeight/11
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
        width: ScreenWidth/11
        height: ScreenHeight- topBar.height
        x: ScreenWidth - sideBar.width
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
