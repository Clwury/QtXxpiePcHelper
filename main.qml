import QtQuick 2.0

Item {

    Loader {
        id: loader
//        width: parent.width
//        height: parent.height
        anchors.centerIn: parent
    }
    Component.onCompleted: {
        console.log("loader大小", loader.width, loader.height)
        loader.sourceComponent = loginPage
    }

    // 登录页面
    Component {
        id: loginPage
        Login {
            width: 400
            height: 300
            anchors.centerIn: parent
        }
    }

    // 主页面
    Component {
        id: homePage
        Home {
//            width: 1200
//            height: 900
//            anchors.centerIn: parent
        }
    }
}

