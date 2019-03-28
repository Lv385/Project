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

    property color backGroundColor : "#263238"
    property color topLoginPageColor: "#FFA726"
    property color mainAppColor: "#455A64"
    property color mainTextCOlor: "#64FFDA"
    property color friendListColor: "#37474F"
    property color friendMouseAreaColor: "#78909C"
    property color choosenFriendColor: "#00BFA5"
    property color onlineFriendColor: "#AED581"
    property color offlineFriendColor: "#FFAB91"
    property color borderColor: "#FFB74D"


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
            color: backGroundColor
        }
        y: (rootWindow.height - 60)
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
        Text {
            id: message
            anchors.centerIn: parent
            font.pointSize: 12
            color: mainTextCOlor
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
