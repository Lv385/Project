import QtQuick 2.4
import QtQuick.Controls 2.3

LoginPageForm {
    id: rect
    buttonLogIn.onClicked: {
        guiManager.logIn2()
        stackView.push("MainPage.qml", {"userName": loginUsername.text})
    }

}


