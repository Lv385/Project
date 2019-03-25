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
    property color  onlineFriendColor: "#AED581"
    property color  offlineFriendColor: "#FFAB91"
    property color borderColor: "#4E342E"

    FontLoader {
        id: fontAwesome
        name: "fontawesome"
        source: "qrc:/fontawesome-webfont.ttf"
    }

    // Main stackview
    StackView{
        id: stackView
        focus: true
        anchors.fill: parent
    }

    // Replace this with some other action that changes the source.
    Component.onCompleted: stackView.push("LoginPage.qml")

}
