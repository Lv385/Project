import QtQuick 2.12
import QtQuick.Controls 2.5

LoginPageForm {
    id: rect
	
	  Keys.onPressed: {
	  if (event.key === Qt.Key_Return) {
      loginUser(loginUsername.text, loginPassword.text)        
		}
	  }

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
		onLogInFailed: {
            popup.popMessage = "Log in failed!"
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
