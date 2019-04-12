import QtQuick 2.4

RegisterPageForm {


    buttonSignUp.onClicked: {
		registerNewUser(registerUsername.text, registerPassword.text, registerPassword2.text)
    }

    buttonCancel.onClicked: {
        stackView.pop()
    }
    Connections{
        target: guiManager
        onOpenMainPage: {
			runIndicator = false
            stackView.push("MainPage.qml")
        }
		onOpenFailed: {
            popup.popMessage = text + " failed!"
            popup.open()
		}
    }
}
