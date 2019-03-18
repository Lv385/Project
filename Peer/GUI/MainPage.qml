import QtQuick 2.4
import QtQuick.Controls 2.3

Page {
    id: rect

    property string userName: ""

    Button {
        onClicked: stackView.pop()
    }

    background: Rectangle {
        color: backGroundColor
    }

    Text {
        id: welcomeText
        text: "Hi " + userName
        anchors.centerIn: parent
        font.pointSize: 22
        color: mainTextCOlor
    }
}
