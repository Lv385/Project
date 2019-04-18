import QtQuick 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
//import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    property alias visualModel: visualMessageModel

    DelegateModel {
            id: visualMessageModel
            delegate: messageDelegate
        }

    Component {
        id: messageDelegate

        Column {
            anchors.right: sentByMe ? parent.right : undefined
            spacing: 6

            readonly property bool sentByMe: message.owner_id === guiManager.my_id   

            Rectangle {
                anchors.right: sentByMe ? parent.right : undefined
                width: Math.min(messageText.implicitWidth + 24, messageList.width)
                height: messageText.implicitHeight + 24
                color: sentByMe ? "lightgrey" : "steelblue"
                radius: 10

                Label {
                    id: messageText
                    text: message.data
                    color: sentByMe ? "black" : "white"
                    anchors.fill: parent
                    anchors.margins: 12
                    wrapMode: Label.Wrap
                }
            }

            Label {
                id: timestampText
                text: message.date + " " + message.time   //add date after fixing
                color: "lightgrey"
                anchors.right: sentByMe ? parent.right : undefined

				BusyIndicator {
					id: messageIndicator
					x: -18
					width: 10
					height: 10
					running: !message.sent_status
					style: BusyIndicatorStyle {
						indicator: Image {
							visible: control.running
							source: "qrc:/loading-icon2.png"
							RotationAnimator on rotation {
								running: control.running
								loops: Animation.Infinite
								duration: 2000
								from: 0 ; to: 360
							}
						}
					}
				}
            }


        }
    }
}
