import QtQuick 2.1
import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.0

Window
{
    title: "F0T0N2"
    id: mainWindow
    width: ScreenWidth
    height: ScreenHeight
    visible: true
    color: "black"
    FindDeviceMenu{
        anchors.fill: parent
    }
    LedBoardView{
        id:boardView
        anchors.fill: parent
        visible: false
    }
}
