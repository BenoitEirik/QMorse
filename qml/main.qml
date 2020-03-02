// Thanks to ekke (Ekkehard Gentz) @ekkescorner
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.12
import StatusBar 0.1

//#41CD52

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("QMorse")
    color: "#41CD52"

    StatusBar {
        theme: StatusBar.Light
        color: "#0E9A1F"
    }

    property bool flashTurn: false

    // fills iPhone and iPad devices screen totally
    // ATTENTION: if only setting flags: Qt.MaximizeUsingFullscreenGeometryHint
    // it will work on iOS and Android, but on Android the BACK key wasn't detected anymore
    // so it's important to set both flags
    // found this in JP Nurmis Statusbar project
    flags: Qt.platform.os === "ios"? Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint : Qt.Window

    header:
    ToolBar {
        contentHeight: toolButton.implicitHeight
        RowLayout {
            anchors.fill: parent

            ToolButton {
                id: toolButton
                Image {
                    source: stackView.depth > 1 ? "qrc:/images/white/baseline_arrow_back_ios_white_18dp.png"
                                                : "qrc:/images/white/baseline_menu_white_18dp.png"
                    anchors.centerIn: parent
                    width: parent.height * 0.6
                    height: parent.width * 0.6
                }
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                text: stackView.currentItem.title
                font.pixelSize: 20
                color: "white"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                Image {
                    source: "qrc:/images/white/baseline_more_vert_white_48.png"
                    anchors.centerIn: parent
                    width: parent.height * 0.6
                    height: parent.width * 0.6
                }
                onClicked: {
                    flashTurn = !flashTurn;
                }
            }
        }
    }

    Camera {
        id: camera
        flash.mode: flashTurn == true ? Camera.FlashVideoLight : Camera.FlashOff
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Image {
            id: backgroundDraw
            source: "qrc:/images/QMorse2.png"
            width: parent.width
            height: parent.width
        }

        Column {
            anchors.bottom: parent.Bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: backgroundDraw.bottom

            ItemDelegate {
                text: qsTr("International Morse Code")
                width: parent.width
                onClicked: {
                    stackView.push("MorseCode.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {
                    stackView.push("Settings.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.qml"
        anchors.fill: parent
    }

    Keys.onReleased: {
        console.log(stackView.depth);
        switch (event.key) {
            case Qt.Key_Escape:
            case Qt.Key_Back: {
                if (stackView.depth == 1)
                {
                    Qt.quit();
                }
                break;
            }
            default: break;
        }
    }
}
