import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12
import Qt.labs.settings 1.0


	MainPageForm {
		background: Rectangle {
        color: backGroundColor
    }

	  Settings {
        id: settings
        property string style: "Default"
    }

	    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            listView.currentIndex = -1
        }
		}
		    Shortcut {
        sequence: "Menu"
        onActivated: optionsMenu.open()
    }
	  

           ToolButton {
                icon.name: "menu"
				id: menuButton
				y: findUserField.y-3
				height:findUserField.height+5
				width: height
                onClicked: drawer.open()
				icon.source: "qrc:/menu_icon.png"
				background: Rectangle {
				color: friendListColor
				}

                 Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height
        interactive: stackView.depth === 1
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

    FriendRequestListDelegateModel {
        id: friendRequestModel
        visualModel.model: guiManager.friend_request_model
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

    friendRequestList.model: friendRequestModel.visualModel

    findButton.onClicked: {
        guiManager.newFriend(findUserField.text)
        findUserField.text = ""
    }

    buttonRequests.onClicked: {
        friendRequestDialog.open()
    }

    messageField.onEditingFinished: {
        if(messageField.text != "") {
			guiManager.SendMessage(messageField.text)
            messageField.text = "";
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
