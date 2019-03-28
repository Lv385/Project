import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.LocalStorage 2.12


ApplicationWindow {
    id: rootWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("MesX")

    property color backGroundColor : "#3E2723"
    property color mainAppColor: "#D7CCC8"
    property color mainTextCOlor: "#f0f0f0"
    property color friendListColor: "#A1887F"
    property color friendMouseAreaColor: "#8D6E63"
    property color choosenFriendColor: "#5D4037"
    property color onlineFriendColor: "#AED581"
    property color offlineFriendColor: "#FFAB91"
    property color borderColor: "#4E342E"

    FontLoader {
        id: fontAwesome
        name: "fontawesome"
        source: "qrc:/fontawesome-webfont.ttf"
    }

    // Main stackview
    StackView {
        id: stackView
        focus: true
        anchors.fill: parent
    }

    // Replace this with some other action that changes the source.
    Component.onCompleted: stackView.push("LoginPage.qml")

    //Popup to show messages or warnings on the bottom postion of the screen
    Popup {
        id: popup
        property alias popMessage: message.text

        background: Rectangle {
            implicitWidth: rootWindow.width
            implicitHeight: 60
            color: popupBackGroundColor
        }
        y: (rootWindow.height - 60)
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
        Text {
            id: message
            anchors.centerIn: parent
            font.pointSize: 12
            color: popupTextCOlor
        }
        onOpened: popupClose.start()
    }

    // Popup will be closed automatically in 2 seconds after its opened
    Timer {
        id: popupClose
        interval: 2000
        onTriggered: popup.close()
    }
}
