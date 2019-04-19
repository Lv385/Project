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
                font.pointSize: 11
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.margins: 20
            }

			Text {
				id: numUnreadMessgs
				text: friend.unread_msgs ? friend.unread_msgs : ""
				color: friendListColor
                font.pointSize: 8
				anchors.right: parent.right
				anchors.verticalCenter: parent.verticalCenter
				anchors.margins: 30
				clip: false
				Rectangle {
					id: unreadMessages
					z: -1
					height: parent.height + 5
					width: (parent.width == 0) ? 0 : (parent.width < parent.height) ? parent.height + 7 : parent.width + 7   //  =)
					anchors.verticalCenter: parent.verticalCenter
					anchors.horizontalCenter: parent.horizontalCenter
					color: borderColor
					radius: width
				}
			}

            Rectangle {
                id: onlineStatus
                width: 8
                height: parent.height - 1
				border.width: 1
				border.color: "black"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                color: friend.status ? onlineFriendColor : offlineFriendColor
            }

            MouseArea {
                id: friendFieldMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    friendField.ListView.view.currentIndex = index
					guiManager.selected_friend_id = friend.id
                }
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
                onClicked: {
					guiManager.friend_to_delete = friend.login
					deleteConfirmation.open()
				}
            }

			 Dialog {
                id: deleteConfirmation
                title: "Delete confirmation"
                background: Rectangle {
                    color: friendListColor
                    border.color: friendMouseAreaColor
                    anchors.verticalCenter: window.verticalCenter
                }
                modal: true
                height: 150
                width: 350
                x: (window.width - width) / 2
                y: (window.height - height) / 2
                parent: ApplicationWindow.overlay

			    Column {
                    spacing: 20
                    anchors.fill: parent
                    Label {
                        text: "Are you sure to delete " + guiManager.friend_to_delete + " from your friend list?"
						color: mainTextCOlor
						font.pixelSize: 12
                    }
					Row {
						x: 100
						spacing: 5
						Button {
							text: "Yes"
							onClicked: {
								guiManager.DeleteFriend(guiManager.friend_to_delete)
								deleteConfirmation.close()
							}
						}
						Button {
							text: "No"
							onClicked: {								
								guiManager.friend_to_delete = ""
								deleteConfirmation.close()
							}
						}
					}

                }
            }

        }
    }
}
