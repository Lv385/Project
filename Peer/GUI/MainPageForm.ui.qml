import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    property alias friendList: friendList
    property alias messageList: messageList
    property alias sendButton: sendButton
    property alias messageField: messageField
    property alias rectangleX: rectangle.x

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
                id: enterLoginField
                x: 9
                y: 9
                width: 155
                height: 32
                Layout.fillWidth: true
                placeholderText: qsTr("Enter login")
                wrapMode: TextArea.Wrap
            }
            Button {
                id: findButton1
                x: 209
                y: 13
                width: 60
                height: 25
                text: qsTr("Search")
                focusPolicy: Qt.WheelFocus
                enabled: messageField.length > 0
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
        y: 54
        width: 520
        height: 511

        ListView {
            id: messageList
            x: 0
            y: 0
            width: 519
            height: 470
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
            height: 10
            Layout.fillWidth: true

            Rectangle {
                x: -12
                y: -35
                width: 519
                height: 96
                color: friendMouseAreaColor
            }

            TextArea {
                id: messageField
                x: 5
                y: -12
                width: 394
                height: 52
                Layout.fillWidth: false
                placeholderText: qsTr("Compose message")
                wrapMode: TextArea.Wrap
            }

            Button {
                id: sendButton
                x: 417
                y: -4
                width: 82
                height: 28
                text: qsTr("Send")
                enabled: messageField.length > 0
            }
        }
    }
}












/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
