import QtQuick 2.12
import QtQuick.Controls 2.5

LoginPageForm {
    id: rect
    buttonLogIn.onClicked: {
        runIndicator = true		     
		loginUser(loginUsername.text, loginPassword.text)   
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

    buttonRegister.onClicked: {
        stackView.push("RegisterPage.qml")
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
