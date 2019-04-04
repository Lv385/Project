import QtQuick 2.12
import QtQuick.Controls 2.5

LoginPageForm {
    id: rect
    buttonLogIn.onClicked: {
        runIndicator = true
		guiManager.LogIn(loginUsername.text)
        stackView.push("MainPage.qml")
    }

    buttonRegister.onClicked: {
        stackView.push("RegisterPage.qml")
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
