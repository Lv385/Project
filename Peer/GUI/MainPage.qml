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

    Component {
        id: highlightBar
        Rectangle {
            width: friendList.width; height: 40
            color: friendMouseAreaColor
            y: friendList.currentItem.y;
            //Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
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
