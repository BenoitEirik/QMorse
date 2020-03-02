import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.2
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12



Page {
    width: parent.width
    height: parent.height

    title: qsTr("QMorse")

    property int txtToMorse: 0
    property int morseToTxt: 1
    property int swapMode: txtToMorse
    property string tmpTxtSwaping: ""
    property string tmpMorseSwaping: ""

    header: ToolBar{
        RowLayout {
            anchors.fill: parent
            Text {
                text: swapMode == txtToMorse ? qsTr("Langage") : qsTr("Morse")
                Layout.preferredWidth: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                color: "white"
            }

            ToolButton {
                id: swapButton
                Image {
                    source: "qrc:/images/white/baseline_swap_horiz_white_48dp.png"
                    width: parent.height * 0.7
                    height: parent.height * 0.7
                    anchors.centerIn: parent
                }
                Layout.alignment: Qt.AlignHCenter
                onReleased: {
                    if (swapMode == txtToMorse)
                    {
                        swapMode = morseToTxt;
                        tmpTxtSwaping = input.text;
                        input.text = tmpMorseSwaping;
                    }
                    else if (swapMode == morseToTxt)
                    {
                        swapMode = txtToMorse;
                        tmpMorseSwaping = input.text;
                        input.text = tmpTxtSwaping;
                    }
                }
            }

            Text {
                text: swapMode == txtToMorse ? qsTr("Morse") : qsTr("Langage")
                Layout.preferredWidth: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                color: "white"
            }
        }
    }

    Pane {
        id: root
        anchors.fill: parent
        GridLayout {
            anchors.fill: parent
            anchors.margins: 20
            rowSpacing: 20
            columnSpacing: 20
            flow:  width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom
            RectangularGlow {
                width: rectInput.width
                height: rectInput.height
                glowRadius: input.activeFocus == true ? 2 : 0.1
                spread: 0
                color: "grey"
                cornerRadius: rectInput.radius
            }
            Rectangle {
                id: rectInput
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "white"
                border.width: 1
                border.color: "white"
                radius: 10
                Text {
                    text: swapMode == txtToMorse ? qsTr("Type your message here")
                                                 : qsTr("Type your coded message\ne.g. .../---/.../")
                    color: "grey"
                    font: input.font
                    topPadding: 18
                    leftPadding: 10
                    visible: !input.text
                }
                Flickable {
                    anchors.fill: parent
                    flickableDirection: Flickable.VerticalFlick
                    TextArea.flickable: TextArea {
                        id: input
                        textMargin: 10
                        background: Rectangle {
                            color: "Transparent"
                        }
                        wrapMode: TextArea.Wrap

                        inputMethodHints: Qt.ImhSensitiveData
                        onTextChanged : {
                            // TEST console.log("TextChanged : input.text = ", input.text,"\n");
                            if (swapMode == txtToMorse)
                            {
                                output.text = comMorse.codingStringMorse(input.text);
                            }
                            else if (swapMode == morseToTxt)
                            {
                                output.text = comMorse.dcodingStringMorse(input.text);
                            }
                        }
                    }
                }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "white"
                border.width: 1
                border.color: "#795548"
                radius: 10
                Flickable {
                    anchors.fill: parent
                    flickableDirection: Flickable.VerticalFlick
                    TextArea.flickable: TextArea {
                        id: output
                        textMargin: 10
                        readOnly: true
                        font.bold: true
                        background: Rectangle {
                            color: "Transparent"
                        }
                        inputMethodHints: Qt.ImhSensitiveData
                        wrapMode: TextArea.Wrap
                    }
                }
            }
        }
    }

}
