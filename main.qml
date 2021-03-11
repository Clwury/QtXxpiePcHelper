import QtQuick 2.12
//import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
//import QtQuick.Controls.Material 2.12
//import io.qt.examples.backend 1.0
//import io.qt.examples.randomnumbergenerator 1.0
//import MainWindow 1.0
//import Charts 1.0

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
//    width: 200
//    height: 200



    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
            console.log(clickPos)
        }
        onPositionChanged: {
            let delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
//            console.log("主窗口位置", mainWindow.point())
            mainWindow.setPoint(delta)
//            console.log("滑动距离", delta)
        }

    }

    Rectangle {

        width: parent.width
        height: parent.height
        color: '#d1d1d1'

//        PieChart {
//            id: aPieChart
//            anchors.centerIn: parent
//            width: 100; height: 100
//            name: "A simple pie chart"
//            color: "red"
//        }

//        Text {
//            anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 20 }
//            text: aPieChart.name
//        }

        Rectangle {

            id: rootArea
            width: parent.width * 2 / 3
            height: parent.height * 2 / 3
            color: "#d1d1d1"
            anchors.centerIn: parent

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: {
                    console.log('text rectangle clicked')
                    mouse.accepted = false
                }
            }

            Image {
                id: logo
                source: "images/ic_login_logo--imgs.png"
                width: parent.width * 2 / 3
                fillMode: Image.PreserveAspectFit
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ColumnLayout {

                id: columnLayout
                anchors.top: logo.bottom
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter

//                Component.onCompleted: {
//                    console.log(logo)
//                    console.log(parent)
//                }

//                Rectangle {
//                    width: parent.width
//                    height: parent.height
//                    Layout.preferredWidth: rootArea.width
//                    Layout.alignment: Qt.AlignCen`ter
//                    color: "#1A01CC"
//                }

                TextField {
                    id: telNumInput
                    placeholderText: qsTr("请输入")
                    text: "18390216081"
//                    text: mainWindow.userName()
//                    width: parent.width
                    Layout.preferredWidth: logo.width

//                    onEditingFinished: mainWindow.setUserName(text)
                }

                TextField {
                    id: passwordInput
                    placeholderText: qsTr("请输入密码")
                    text: "123456"
//                    width: parent.width
                    Layout.preferredWidth: logo.width


//                    anchors.top: telNumInput.bottom
//                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Button {
                    id: loginBtn
                    text: qsTr("login")
//                    width: parent.width / 2
                    Layout.alignment: Qt.AlignHCenter

                    onClicked: mainWindow.login(telNumInput.text, passwordInput.text)
//                    anchors.top: passwordInput.bottom
//                    anchors.horizontalCenter: parent.horizontalCenter
                }

            }
//            Rectangle {

//                width: parent.width
//                height: parent.height / 4
//                color: 'red'

//                TextField {
//                    text: mainWindow.userName()
//                    anchors.fill: parent
//                    anchors.verticalCenter: parent
//                    anchors.horizontalCenter: parent
//                    anchors.margins: 2
//                    font.pointSize: 10
//                    placeholderText: qsTr("请输入手机号")
//                    selectByMouse: true

//                    onEditingFinished: mainWindow.setUserName(text)
//                }

//                TextField {

//                    id: textField
//                    text: qsTr("text Field")

//                }

//                TextField {
//                    id: root

//                    property color checkedColor: "#D5DBDB"

//                    signal doubleClicked(var/*MouseEvent*/ event)

//                    placeholderText: qsTr("请输入内容")
//                    font.family: "Arial"
//                    font.pixelSize: 15
//                    font.weight: Font.Thin
//                    antialiasing: true

//                    background: Rectangle {
//                        implicitWidth: 213
//                        implicitHeight: 42
//                        radius: 8
//                        color: root.enabled ? "transparent" : "#F4F6F6"
//                        border.color: root.enabled ? root.checkedColor : "#D5DBDB"
//                        border.width: 2
//                        opacity: root.enabled ? 1 : 0.7

//                        layer.enabled: root.hovered
//                        layer.effect: DropShadow {
//                            id: dropShadow
//                            transparentBorder: true
//                            color: root.checkedColor
//                            samples: 10 /*20*/
//                        }
//                    }

//                    cursorDelegate: Rectangle {
//                        width: 1
//                        height: parent.height * 0.4
//                        color: root.checkedColor
//                        visible: root.focus

//                        Timer {
//                            interval: 600
//                            repeat: true
//                            running: root.focus
//                            onRunningChanged: parent.visible = running
//                            onTriggered: parent.visible = !parent.visible
//                        }
//                    }

//                    onDoubleClicked: selectAll()

//                    /* note: This signal was introduced in QtQuick.Controls 2.1 (Qt 5.8). */
//                    onPressed: {
//                        _private.mouseEvent = event
//                        _private.isCheckDoubleClickedEvent++

//                        if (! _checkDoubleClickedEventTimer.running)
//                            _checkDoubleClickedEventTimer.restart()
//                    }

//                    /* Private */
//                    Item {
//                        id: _private
//                        property int isCheckDoubleClickedEvent: 0
//                        property var/*MouseEvent*/ mouseEvent

//                        Timer {
//                            id: _checkDoubleClickedEventTimer
//                            running: false
//                            repeat: false
//                            interval: 180
//                            onTriggered: {
//                                if (_private.isCheckDoubleClickedEvent >= 2) {
//                                    /* Double Clicked Event */
//                                    root.doubleClicked(_private.mouseEvent)
//                                }

//                                stop()
//                                _private.isCheckDoubleClickedEvent = 0
//                            }
//                        }
//                    }
//                }
//            }

        }


//        MouseArea {
//            anchors.fill: parent
//            propagateComposedEvents: true
//            onClicked: {
//                console.log('text rectangle clicked')
//                mouse.accepted = false
//            }
//        }
    }
    Component.onCompleted: {
        if (Qt.platform.os == "windows") {
            console.log("platfrom win")
        } else {
            console.log("platfrom mac")
        }
    }
}
//}
