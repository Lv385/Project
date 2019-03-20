import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item {
    property alias visualModel: visualModelId
    property ListView listView
    //property alias deleteFriendButton: deleteFriendButtonId

    DelegateModel {
            id: visualModelId
            delegate: friendDelegate
        }

    Component {
        id: friendDelegate

        RowLayout {
            id: row1
            width: 200
            height: 40

            spacing: 10

            Rectangle{
                id: friendField
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: object.status ? "#2aa32a" : "#d85454"

                Text {
                    text: object.login
                    color: "#ffffff"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Button {
                    id: deleteFriendButtonId
                    anchors { top: parent.top; right: parent.right }
                    height: parent.height / 2
                    width: height
                    onClicked: guiManager.deleteFriend(object)
                }
            }

        }
    }
}
