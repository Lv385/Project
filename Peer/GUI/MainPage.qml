import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12


MainPageForm {

    background: Rectangle {
        color: backGroundColor

    }

    FriendListDelegateModel {
        id: friendModel
        visualModel.model: guiManager.friend_model
    }

    MessageListDelegateModel {
        id: messageModel
        visualModel.model: guiManager.message_model
    }

    Button {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 18
        anchors.topMargin: 30
        width: 120
        height: 26

        onClicked: friendRequestList.open()
        Text {
            text: "\uf007"
            anchors.right: parent.right
            font.pointSize: 14
            font.family: "fontawesome"
            color: friendListColor
        }
        background: Rectangle
        {
            color: backGroundColor
        }


        Dialog {
            id: friendRequestList
            background: Rectangle {
                color: backGroundColor
                border.color: friendListColor
            }
            x: 0
            y: 25
            height: 300
            width: parent.width



            Label {
                text: "Lorem ipsum dolor sit amet..."

            }
        }
    }

    Component {
        id: highlightBar
        Rectangle {
            width: friendList.width; height: 40
            color: friendMouseAreaColor
            y: friendList.currentItem.y;
        }
    }

    friendList.focus: true
    friendList.highlight: highlightBar
    friendList.highlightFollowsCurrentItem: false


    friendList.model: friendModel.visualModel

    messageList.model: messageModel.visualModel
    messageList.spacing: 10



    sendButton.onClicked: {
        guiManager.newMessage(messageField.text)
        messageField.text = "";
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
