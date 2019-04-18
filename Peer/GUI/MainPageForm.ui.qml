import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtMultimedia 5.12


Page {
    id: page

    property alias friendList: friendList
    property alias messageList: messageList
    property alias messageField: messageField
    property alias rectangleX: rectangle.x
    //property alias buttonRequests: buttonRequests
    property alias friendRequestDialog: friendRequestDialog
    property alias friendRequestList: friendRequestList
    property alias findButton: findButton
    property alias findUserField: findUserField
    property alias drawer: drawer
    property alias menuButton: menuButton
    property alias friendReqMA: friendReqMA
    property alias editProfileMA: editProfileMA
    property alias editProfileMenu: editProfileMenu
    property alias settingsMenu: settingsMenu
    property alias settingsMA: settingsMA
	property alias logoutMA: logoutMA
	property alias messageSound: messageSound
	property alias friendSound: friendSound

	SoundEffect {
		id: messageSound
		source: "qrc:/message_sound.wav"
		}

	SoundEffect {
		id: friendSound
		source: "qrc:/friend_sound.wav"
		}

    Pane {
        id: pane1
        x: 0
        y: 0
        width: 283
        height: 54

        Rectangle {
            id: rectangle
            x: pane1.x - 12
            y: pane1.y - 12
            width: pane1.width
            height: pane1.height
            color: friendListColor

            TextField {
                id: findUserField
                x: 40
                y: 11
                width: 230
                height: 32
                Layout.fillWidth: true
                placeholderText: qsTr("Enter user login")
                wrapMode: TextArea.Wrap
                background: Rectangle {
                    color: friendMouseAreaColor
                }
            }

            Button {
                id: findButton
                x: 241
                y: 11
                width: 32
                height: 32
                text: qsTr("Add friend")
                enabled: findUserField.length > 0
                background: Rectangle {
                    color: friendListColor
                }

                Text {
                    text: "\uf055"
                    anchors.right: parent.right
                    font.pointSize: 20
                    font.family: "fontawesome"
                    color: backGroundColor
                }
            }
        }
    }
    ToolButton {
        id: menuButton
        y: findUserField.y + 2
        x: 2
        z: 1
        height: findUserField.height
        width: height
        Text {
            x: 7
            text: "\uf0c9"
            font.pointSize: 20
            font.family: "fontawesome"
            color: backGroundColor

					Text {
			text: guiManager.unread_requests ? guiManager.unread_requests : ""
			color: friendListColor
            font.pointSize: 6
			anchors.right: parent.right
			anchors.bottom: parent.bottom 
			clip: false
			Rectangle {
				z: -1
				height: parent.height + 5
				width: (parent.width == 0) ? 0 : (parent.width < parent.height) ? parent.height + 7 : parent.width + 7   //  =)
				anchors.verticalCenter: parent.verticalCenter
				anchors.horizontalCenter: parent.horizontalCenter
				color: borderColor
				radius: width
			}
		}
        }



        background: Rectangle {
            color: friendListColor
        }

        Drawer {
            id: drawer
            width: friendList.width
            height: window.height
            background: Rectangle {
                color: friendListColor

                Rectangle {
                    x: 0
                    y: 320
                    width: friendList.width
                    height: 30
                    id: friendReqButton
                    color: friendMouseAreaColor

                    Text {
                        text: "\uf007"
                        font.pointSize: 15
                        font.family: "fontawesome"
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5

								Text {
			text: guiManager.unread_requests ? guiManager.unread_requests : ""
			color: friendListColor
            font.pointSize: 5
			anchors.right: parent.right
			anchors.bottom: parent.bottom 
			clip: false
			Rectangle {
				z: -1
				height: parent.height + 5
				width: (parent.width == 0) ? 0 : (parent.width < parent.height) ? parent.height + 7 : parent.width + 7   //  =)
				anchors.verticalCenter: parent.verticalCenter
				anchors.horizontalCenter: parent.horizontalCenter
				color: borderColor
				radius: width
			}
		}
                    }

                    Text {
                        text: "Friend requests"
                        font.bold: true
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                    }

                    MouseArea {
                        id: friendReqMA
                        anchors.fill: parent
                    }

                    Dialog {
                        id: friendRequestDialog
                        title: "Friend requests"
                        background: Rectangle {
                            color: friendListColor
                            border.color: friendMouseAreaColor
                            anchors.verticalCenter: window.verticalCenter
                        }
                        modal: true
                        height: 300
                        width: 250
                        x: (window.width - width) / 2
                        y: (window.height - height) / 2
                        parent: ApplicationWindow.overlay

                        ListView {
                            id: friendRequestList
                            anchors.fill: parent
                            highlightRangeMode: ListView.ApplyRange
                            flickableDirection: Flickable.VerticalFlick
                            boundsBehavior: Flickable.StopAtBounds
                            orientation: ListView.Vertical
                        }
                    }
                }
                Rectangle {
                    x: 0
                    y: 350
                    width: friendList.width
                    id: editProfileButton
                    height: 30
                    color: friendMouseAreaColor

                    Text {
                        text: "\uf044"
                        font.pointSize: 15
                        font.family: "fontawesome"
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }

                    Text {
                        text: "Edit profile"
                        font.bold: true
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                    }
                    MouseArea {
                        id: editProfileMA
                        anchors.fill: parent
                    }

                    Menu {
                        id: editProfileMenu
                        y: findButton.height

                        MenuItem {
                            text: "New..."
                        }
                        MenuItem {
                            text: "Open..."
                        }
                        MenuItem {
                            text: "Save"
                        }
                    }
                }
                Rectangle {
                    x: 0
                    y: 380
                    width: friendList.width
                    id: settingsButton
                    height: 30
                    color: friendMouseAreaColor

                    Text {
                        text: "\uf013"
                        font.pointSize: 15
                        font.family: "fontawesome"
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }

                    Text {
                        text: "Settings"
                        font.bold: true
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 30	
					}
                  
				  MouseArea {
                        id: settingsMA
                        anchors.fill: parent
                    }

                    Menu {
                        id: settingsMenu
                        y: findButton.height

                        MenuItem {
                            text: "New..."
                        }
                        MenuItem {
                            text: "Open..."
                        }
                        MenuItem {
                            text: "Save"
                        }
                    }
                }
				
				Rectangle {
                    x: 0
                    y: 410
                    width: friendList.width
                    id: logoutButton
                    height: 30
                    color: friendMouseAreaColor

					Text {
                        text: "\uf057"
                        font.pointSize: 15
                        font.family: "fontawesome"
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                    }

                    Text {
                        text: "Logout"
                        font.bold: true
                        color: backGroundColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 30
					}

                    MouseArea {
                        id: logoutMA
                        anchors.fill: parent
                    }
				}

            Image {
                id: logo
                width: parent.width
                source: "qrc:/user.png"
                fillMode: implicitWidth > width ? Image.PreserveAspectFit : Image.Pad
            }
        }
    }
}


    Rectangle {
        x: friendList.x
        y: friendList.y
        width: friendList.width
        height: friendList.height
        color: friendListColor
    }

    ListView {
        id: friendList
        x: 0
        y: 54
        width: 283
        height: parent.height
        highlightRangeMode: ListView.ApplyRange
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds
        orientation: ListView.Vertical
    }

    ColumnLayout {
        id: columnLayout
        width: page.width - 330
        height:page.height-150
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.topMargin: 70
		anchors.rightMargin: 20


        ListView {
            id: messageList
            x: 0
            y: 0
            width: columnLayout.width
            height: columnLayout.height
            highlightRangeMode: ListView.ApplyRange
            orientation: ListView.Vertical
            cacheBuffer: 318
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12

            ScrollBar.vertical: ScrollBar {
                anchors.left: parent.right
            }
        }

        Pane {
            id: pane
            anchors.bottom:window.bottom
			anchors.right:window.right
			parent: window.overlay
            width: parent.width-friendList.width
            height: 70
            Layout.fillWidth: true
            focus: true 

            TextField {
                id: messageField
                anchors.bottom: window.bottom
				anchors.right:window.right
				//parent: window.overlay
                width: window.width-friendList.width
                height: 70
                focus: true
                Layout.fillWidth: true
                placeholderText: qsTr("Compose message")
                wrapMode: TextField.Wrap
                background: Rectangle {
                color: friendMouseAreaColor
                }
            }
        }
    }


    /*  Button {
        id: buttonRequests
        x: 601
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 18
        anchors.topMargin: 30
        width: 21
        height: 26

        Text {
            text: "\uf007"
            anchors.right: parent.right
            font.pointSize: 18
            font.family: "fontawesome"
            color: friendListColor
        }
        background: Rectangle {
            color: backGroundColor
        }
    }*/
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
