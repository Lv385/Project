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

    friendList.model: friendModel.visualModel
    friendList.spacing: 5

    messageList.model: messageModel.visualModel
    messageList.spacing: 10

    addButton.onClicked: {
        guiManager.newFriend()
    }

    sendButton.onClicked: {
        guiManager.newMessage(messageField.text)
        messageField.text = "";
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
