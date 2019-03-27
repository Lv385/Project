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
            width : friendList.width
            height: 40

            Rectangle {
                id: friendField
                Layout.fillHeight: true
                Layout.fillWidth: true

                color:friendFieldMouseArea.containsMouse? friendMouseAreaColor : friendListColor
                MouseArea {
                   id: friendFieldMouseArea
                   hoverEnabled: true
                   anchors.fill: friendField


                                    onClicked: {
                                        friendField.color = choosenFriendColor
                                        friendName.color = mainTextCOlor
                                        console.log("On " + friendName.text + " clicked")

                                    }
                                   onExited :  {
                                 friendField.color=friendListColor
                                  friendName.color=borderColor
                                   }
                                }



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
                    width: 20
                    height: 12
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 25
                    color: friend.status ? onlineFriendColor : offlineFriendColor
                    radius: 15
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
}
