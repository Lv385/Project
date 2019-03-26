import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item {
    property alias visualModel: visualFriendModel

    DelegateModel {
            id: visualFriendModel
            delegate: friendDelegate
        }

    Component {
        id: friendDelegate

        RowLayout {
            id: row1
            width: 200
            height: 40

            spacing: 10

            Rectangle {
                id: friendField
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: friend.status ? "#2aa32a" : "#d85454"

                Text {
                    text: friend.login
                    color: "#ffffff"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Button {
                    id: deleteFriendButtonId
                    anchors { top: parent.top; right: parent.right }
                    height: parent.height / 2
                    width: height
                    onClicked: guiManager.deleteFriend(friend)
                }
            }

        }
    }
}
