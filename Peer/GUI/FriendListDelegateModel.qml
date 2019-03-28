import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item {
    property alias visualModel: visualFriendModel
    property ListView list

    DelegateModel {
        id: visualFriendModel
        delegate: friendDelegate
    }



    Component {
        id: friendDelegate

        Item {
            id: friendField
            height: 40
            width : friendList.width
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: friendName
                text: friend.login
                color: borderColor
                font.pixelSize: 13
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.margins: 20
            }

            Rectangle {
                id: onlineStatus
                width: 20
                height: 12
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 25
                color: friend.status ? onlineFriendColor : offlineFriendColor
                radius: 15
            }

            MouseArea {
                id: friendFieldMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: friendField.ListView.view.currentIndex = index
            }


            Button {
                id: deleteFriendButtonId
                anchors { top: parent.top; right: parent.right }
                height: parent.height / 2
                background:
                    Rectangle  {
                    color: "transparent"
                }

                Text {
                    text: "X"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                width: height
                onClicked: guiManager.deleteFriend(friend)
            }


        }
    }
}
