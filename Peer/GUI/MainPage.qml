import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12


MainPageForm {

    background: Rectangle {
        color: backGroundColor
        Text
        {
            padding: 10
            text: qsTr("Contacts")
            color: friendListColor
            font.pixelSize: 23
            horizontalAlignment: Text.AlignJustify
            verticalAlignment: Text.AlignVCenter
            font.family: "fontawesome"
        }
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
