import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12

import Friends 1.0

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
        id: delegateModelId
        visualModel.model: guiManager.friendModel
        listView1: parent.friendList
        //deleteFriendButton.onClicked: guiManager.deleteFriend(object)
    }

    friendList.model: delegateModelId.visualModel

    addButton.onClicked: {
        guiManager.newFriend()
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
