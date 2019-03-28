import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item {
    property alias visualModel: visualRequestModel

    DelegateModel {
        id: visualRequestModel
        delegate: friendRequestDelegate
    }

    Component {
        id: friendRequestDelegate

        Item {
            id: friendField
            height: 40
            width : friendRequestList.width
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: friendName
                text: friend_request.login
                color: borderColor
                font.pixelSize: 13
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }

            Button {
                id: buttonRejectRequest
                anchors { verticalCenter: parent.verticalCenter; right: parent.right }
                height: parent.height / 2
                background:
                    Rectangle  {
                    color: offlineFriendColor
                }
                Text {
                    text: "-"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                width: height
                onClicked: guiManager.deleteFriendRiequest(friend_request)
            }

            Button {
                id: buttonAcceptRequest
                anchors { verticalCenter: parent.verticalCenter; right: buttonRejectRequest.left }
                height: parent.height / 2
                background:
                    Rectangle  {
                    color: onlineFriendColor
                }
                Text {
                    text: "+"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                width: height
                onClicked: guiManager.deleteFriendRiequest(friend_request)
            }
        }
    }
}
