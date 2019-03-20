import QtQuick 2.4
import QtQuick.Controls 2.3

Page {
    property alias friendList: friendList
    property alias addButton: addButton

    ListView {
        id: friendList
        x: 24
        y: 85
        width: 130
        height: 324
    }

    Button {
        id: addButton
        x: 160
        y: 323
        text: qsTr("Add")
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
