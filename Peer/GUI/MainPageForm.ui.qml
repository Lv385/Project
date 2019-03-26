import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    property alias friendList: friendList
    property alias addButton: addButton
    property alias messageList: messageList
    property alias sendButton: sendButton
    property alias messageField: messageField

    ListView {
        id: friendList
        x: 24
        y: 85
        width: 130
        height: 324
    }

    Button {
        id: addButton
        x: 160
        y: 369
        text: qsTr("Add")
    }

    ColumnLayout {
        id: columnLayout
        x: 265
        y: 85
        width: 348
        height: 324

        ListView {
            id: messageList
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
            Layout.fillWidth: true

            RowLayout {
                width: parent.width

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: messageField.length > 0
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
