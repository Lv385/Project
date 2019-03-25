import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Item {
    property alias visualModel: visualModelId
    property ListView listView
    //property alias deleteFriendButton: deleteFriendButtonId

    DelegateModel {
        id: visualModelId
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
                border.color: borderColor
                border.width: 1
                color:friendFieldMouseArea.containsMouse? friendMouseAreaColor : friendListColor

                Text {
                    id: friendName
                    text: object.login
                    color: borderColor
                    font.pixelSize: 13
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.margins: 20

                }
                MouseArea {
                    id: friendFieldMouseArea
                    hoverEnabled: true
                    anchors.fill: friendField

                    onPressed: {
                        friendField.color = choosenFriendColor
                        friendName.color = mainTextCOlor
                        when (MouseArea.onClicked===true)
                        MouseArea.onExited===false
                        when
                    }
                   onReleased:  {
                   friendField.color=friendListColor
                   friendName.color=borderColor
                   }
                }


                Rectangle {
                    width: 20
                    height: 12
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 25
                    color: object.status ? onlineFriendColor : offlineFriendColor
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
                        font: control.font
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    width: height
                    onClicked: guiManager.deleteFriend(object)


                }
            }

        }
    }
}
