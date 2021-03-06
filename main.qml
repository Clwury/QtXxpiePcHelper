import QtQuick 2.12
//import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import io.qt.examples.backend 1.0
//import io.qt.examples.randomnumbergenerator 1.0
import Charts 1.0

//Window {
//    width: 640
//    height: 480
//    visible: true
//    title: qsTr("Hello World")
//    Rectangle {
//        width: parent.width / 2
//        height: parent.height / 2
//        y: parent.height / 2
//        color: "red"
//        Text {
//            id: name
//            text: qsTr("Hello World")
//            anchors.centerIn: parent
//        }
//        TapHandler {
//            onTapped: parent.color = "blue"
//        }
//        focus: true
//        Keys.onPressed: {
//            if (event.key === Qt.Key_Return) {
//                color = "red";
//                event.accepted = true;
//            }
//        }
//    }
//    Rectangle {
//        width: parent.width / 2
//        height: parent.height / 2
//        x: parent.width / 2
//        color: "lightgray"

//        property int animatedValue: 0
//        SequentialAnimation on animatedValue {
//            loops: Animation.Infinite
//            PropertyAnimation { to: 150; duration: 10000 }
//            PropertyAnimation { to: 0; duration: 10000 }
//        }
//        Text {
//            anchors.centerIn: parent
//            text: parent.animatedValue
//        }
//    }
//    Column {
//        width: 180
//        height: 180
//        padding: 1.5
//        topPadding: 10.0
//        bottomPadding: 10.0
//        spacing: 5

//        MessageLabel{
//            width: parent.width - 2
//            msgType: "debug"
//        }
//        MessageLabel {
//            width: parent.width - 2
//            message: "This is a warning!"
//            msgType: "warning"
//        }
//        MessageLabel {
//            width: parent.width - 2
//            message: "A critical warning!"
//            msgType: "critical"
//        }
//    }
//    Image {
//        x: parent.width * 0.75 - 16
//        y: parent.height * 0.75 - 16
//        width: 32
//        height: 32
//        source: "https://common.xxpie.com/icon_black_small_logo.png"
//    }
//}
//Window {
//    title: qsTr("Hello World")
//    width: 640
//    height: 480
//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("File")
//            MenuItem {
//                text: qsTr("&Open")
//                onTriggered: console.log("Open action triggered");
//            }
//            MenuItem {
//                text: qsTr("Exit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }
//    Button {
//        text: qsTr("Hello World")
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.verticalCenter: parent.verticalCenter
//    }
//}
//ApplicationWindow {
//    id: root
//    width: 300
//    height: 480
//    visible: true

////    BackEnd {
////        id: backend
////    }

////    TextField {
////        text: backend.userName
////        placeholderText: qsTr("UserName")
////        anchors.centerIn: parent

////        onEditingFinished: backend.userName = text
////    }

//    Rectangle {
//        RandomNumberGenerator on width { maxValue: 300 }

//        height: 100
//        color: "red"
//    }
//}
//Window {
//    visible: true
//    color: 'red'
Item {
    width: 400
    height: 300

    Rectangle {

        width: parent.width
        height: parent.height
        color: '#d1d1d1'

        PieChart {
            id: aPieChart
            anchors.centerIn: parent
            width: 100; height: 100
            name: "A simple pie chart"
            color: "red"
        }

        Text {
            anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 20 }
            text: aPieChart.name
        }
    }
}
//}
