import QtQuick 2.4

RegisterPageForm {


    buttonSignUp.onClicked: {
        stackView.replace("MainPage.qml")
    }

    buttonCancel.onClicked: {
        stackView.pop()
    }

}
