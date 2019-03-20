import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12

import Friends 1.0

MainPageForm {

    background: Rectangle {
        color: backGroundColor
    }

    FriendListDelegateModel {
        id: delegateModelId
        visualModel.model: guiManager.friendModel
        listView: parent.listView
        //deleteFriendButton.onClicked: guiManager.deleteFriend(object)
    }

    friendList.model: delegateModelId.visualModel
    friendList.spacing: 5


    addButton.onClicked: {
        guiManager.newFriend()
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
