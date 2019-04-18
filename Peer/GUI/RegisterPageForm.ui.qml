import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Page {
    id: registerPage

    property string uname: ""
    property string pword: ""
    property alias buttonSignUp: buttonSignUp
    property alias buttonCancel: buttonCancel
	property alias registerUsername: registerUsername 
	property alias registerPassword: registerPassword 
	property alias registerPassword2: registerPassword2

    background: Rectangle {
        color: backGroundColor
    }

    Text {
        id: signupText
        text: qsTr("Sign Up")
        font.pointSize: 24
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        color: mainTextCOlor
    }

    ColumnLayout {
        anchors.top: signupText.bottom
        anchors.topMargin: 30
        width: 320
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        TextField {
            id: registerUsername
            placeholderText: qsTr("User name")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextCOlor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
			selectByMouse: true
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"

                Text {
                    text: "\uf007"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }

        TextField {
            id: registerPassword
            placeholderText: qsTr("Password")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextCOlor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
			selectByMouse: true
            echoMode: TextField.PasswordEchoOnEdit
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"
                Text {
                    text: "\uf023"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }

        TextField {
            id: registerPassword2
            placeholderText: qsTr("Confirm Password")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextCOlor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
			selectByMouse: true
            echoMode: TextField.PasswordEchoOnEdit
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"
                Text {
                    text: "\uf023"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }

        Button {
            id: buttonSignUp
            width: 323
            implicitWidth: parent.width
            text: qsTr("Sign Up")
            focusPolicy: Qt.StrongFocus
            font.pointSize: 16
            focus: true

            contentItem: Text {
                font: buttonSignUp.font
                color: "#ffffff"
                text: buttonSignUp.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                color: mainAppColor
                opacity: buttonSignUp.down ? 0.7 : 1
                radius: height / 3
                border.color: mainAppColor
            }
        }

        Button {
            id: buttonCancel
            implicitWidth: parent.width
            text: qsTr("Cancel")
            display: AbstractButton.IconOnly
            focusPolicy: Qt.NoFocus
            Layout.fillWidth: false
            font.pointSize: 16

            contentItem: Text {
                text: buttonCancel.text
                font: buttonCancel.font
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                color: "transparent" //"#6fda9c"
                opacity: buttonCancel.down ? 0.7 : 1
                radius: height / 3
                border.color: mainAppColor
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
