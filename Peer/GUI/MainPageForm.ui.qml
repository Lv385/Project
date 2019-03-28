import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    property alias friendList: friendList
    property alias messageList: messageList
    property alias messageField: messageField
    property alias rectangleX: rectangle.x
    property alias buttonRequests: buttonRequests
    property alias friendRequestDialog: friendRequestDialog
    property alias friendRequestList: friendRequestList
    property alias findButton: findButton
    property alias findUserField: findUserField

    Pane {
        id: pane1
        x: 0
        y: 0
        width: 283
        height: 54

        Rectangle {
            id: rectangle
            x: -12
            y: -12
            width: 283
            height: 54
            color: friendMouseAreaColor

            TextArea {
                id: findUserField
                x: 9
                y: 9
                width: 180
                height: 32
                Layout.fillWidth: true
                placeholderText: qsTr("Enter user login")
                wrapMode: TextArea.Wrap
            }
            Button {
                id: findButton
                x: 200
                y: 13
                width: 70
                height: 25
                text: qsTr("Add friend")
                focusPolicy: Qt.WheelFocus
                enabled: findUserField.length > 0
            }
        }
    }

    Rectangle {
        x: friendList.x
        y: friendList.y
        width: friendList.width
        height: friendList.height
        color: friendListColor
    }

    ListView {
        id: friendList
        x: 0
        y: 54
        width: 283
        height: 582
        highlightRangeMode: ListView.ApplyRange
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds
        orientation: ListView.Vertical
    }

    ColumnLayout {
        id: columnLayout
        x: 283
        y: 100
        width: 520
        height: 465

        ListView {
            id: messageList
            x: 0
            y: 0
            width: 519
            height: 470
            highlightRangeMode: ListView.ApplyRange
            orientation: ListView.Vertical
            cacheBuffer: 318
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12

            ScrollBar.vertical: ScrollBar {
                anchors.left: parent.right
            }
        }

        Pane {
            id: pane
            y: 536
            width: 519
            height: 100
            Layout.fillWidth: true

            Rectangle {
                x: -12
                y: -35
                width: 519
                height: 90
                color: friendMouseAreaColor
            }

            TextField {
                id: messageField
                x: 5
                y: -20
                width: 480
                height: 52
                Layout.fillWidth: false
                placeholderText: qsTr("Compose message")
                wrapMode: TextArea.Wrap
            }
        }
    }

    Button {
        id: buttonRequests
        x: 601
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 18
        anchors.topMargin: 30
        width: 21
        height: 26

        Text {
            text: "\uf007"
            anchors.right: parent.right
            font.pointSize: 14
            font.family: "fontawesome"
            color: friendListColor
        }
        background: Rectangle {
            color: backGroundColor
        }

        Dialog {
            id: friendRequestDialog
            background: Rectangle {
                color: backGroundColor
                border.color: friendListColor
            }
            x: -130
            y: 25
            height: 300
            width: 150

            Label {
                id: friendRequestLabel
                text: "Friend requests"
                color: mainTextCOlor
            }

            ListView {
                id: friendRequestList
                anchors.fill: parent
                highlightRangeMode: ListView.ApplyRange
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                orientation: ListView.Vertical
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
