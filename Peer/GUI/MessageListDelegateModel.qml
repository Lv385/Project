import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item {
    property alias visualModel: visualMessageModel

    DelegateModel {
            id: visualMessageModel
            delegate: messageDelegate
        }

    Component {
        id: messageDelegate

        Column {
            anchors.right: sentByMe ? parent.right : undefined
            spacing: 6

            readonly property bool sentByMe: message.owner_id === guiManager.my_id   

            Rectangle {
                anchors.right: sentByMe ? parent.right : undefined
                width: Math.min(messageText.implicitWidth + 24, messageList.width)
                height: messageText.implicitHeight + 24
                color: sentByMe ? "lightgrey" : "steelblue"
                radius: height / 4

                Label {
                    id: messageText
                    text: message.data
                    color: sentByMe ? "black" : "white"
                    anchors.fill: parent
                    anchors.margins: 12
                    wrapMode: Label.Wrap
                }
            }

            Label {
                id: timestampText
                text: message.date + " " + message.time   //add date after fixing
                color: "lightgrey"
                anchors.right: sentByMe ? parent.right : undefined
            }
        }
    }
}
