import QtQuick 2.9
import QtQuick.Window 2.2
import TriangleContainer 1.0
import QtGraphicalEffects 1.0

Window {
    id: window

    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    FontLoader {
        source: "qrc:/Montserrat-ExtraLight.ttf"
    }

    FontLoader {
        source: "qrc:/Montserrat-Medium.ttf"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: triangles.animate()
    }

    Image {
        id: logo

        z: 1
        opacity: 0
        source: "qrc:/logo.svg"
        width: 400
        height: 600
        fillMode: Image.PreserveAspectFit

        sourceSize: Qt.size(400, 600)

        anchors.centerIn: parent
    }


    Item {
        id: logoContainer

        readonly property real scale: 0.5
        readonly property size originalSize: Qt.size(957, 720)

        z: 1
        width: originalSize.width * scale
        height: originalSize.height * scale
        anchors.centerIn: parent

        Image {
            id: logoMain

            z: 2
//            opacity: 0.5
            source: "qrc:/logo_main_part.svg"
            fillMode: Image.PreserveAspectFit

            sourceSize: Qt.size(
                            logoContainer.originalSize.width * scale,
                            logoContainer.originalSize.height * scale)

            anchors.fill: parent
        }

        Rectangle {
            id: logOColoredoOverlay

            z: 3
            width: logoOverlay.width
            height: width
            radius: width
            color: "#BCBCBC"  //BCBCBC
            x: 250 - width / 2
            y: 157  - height / 2

        }

        Rectangle {
            id: logoOverlay

            z: 3
            width: 0    // 317
            height: width
            radius: width
            color: "#1C70B7"  //BCBCBC
            x: 250 - width / 2
            y: 157  - height / 2

        }

        Rectangle {
            id: logoOverlayMask
            z: 3
            color: "white"
            width: 0
            height: width
            radius: width
            anchors.centerIn: logoOverlay
        }

        Image {
            id: logoLeft

            z: 1
            source: "qrc:/logo_left_part.svg"
            width: logoMain.width
            height: logoMain.height
            fillMode: logoMain.fillMode

            sourceSize: logoMain.sourceSize
        }

        Image {
            id: logoRight

            z: 1
            source: "qrc:/logo_right_part.svg"
            width: logoMain.width
            height: logoMain.height
            fillMode: logoMain.fillMode

            sourceSize: logoMain.sourceSize
        }

        Image {
            id: logoBottom

            z: 1
            source: "qrc:/logo_bottom_part.svg"
            width: logoMain.width
            height: logoMain.height
            fillMode: logoMain.fillMode

            sourceSize: logoMain.sourceSize
        }
    }

    Item {
        id: textAligner

        x: 630
        y: 555
        width: 1
        height: 1
    }

    Item {
        id: titleText
        width: textSonik.width + textPonik.width
        height: textSonik.height
//        opacity: 0
        clip: true

        anchors.topMargin: (-titleText.height - subtextClipper.height) / 2
        anchors.top: textAligner.top
        anchors.horizontalCenter: textAligner.horizontalCenter

        Item {
            width: textSonik.width + textPonik.width
            height: textSonik.height
            anchors.left: parent.left

            Text {
                id: textSonik
                text: "SONY"
                antialiasing: true
                font.family: "Montserrat ExtraLight"
                font.pixelSize: 60
            }

            Text {
                id: textPonik
                text: "PONY"
                antialiasing: true
                font.family: "Montserrat"
                font.pixelSize: textSonik.font.pixelSize
                anchors.left: textSonik.right
            }
        }
    }

    Item {
        id: subtextClipper
        width: subtext.width
        height: subtext.height
        clip: true

        anchors.top: titleText.bottom
        anchors.horizontalCenter: titleText.horizontalCenter
        anchors.topMargin: - textSonik.font.pixelSize / 10

        Text {
            id: subtext
            text: "LIVESTREAM DESIGN"
            antialiasing: true
            font.family: "Montserrat ExtraLight"
            font.pixelSize: textSonik.font.pixelSize * 0.394
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "white"
        anchors.bottom: textAligner.top
        anchors.bottomMargin: titleText.anchors.topMargin
    }

    TriangleContainer {
        id: triangles

        readonly property real timeWarp: 1.35

        signal animate

        y: -titleText.anchors.topMargin

        width: parent.width
        height: parent.height
        transform: Rotation {
            id: piecesTransform
            origin.x: 650
            origin.y: 295

            angle: 60
            axis { x: 0; y: 0; z: 1 }
        }

        onAnimate: SequentialAnimation {
            NumberAnimation { duration: 5000 }

            ParallelAnimation {
                NumberAnimation {
                    target: logoLeft
                    property: "x"
                    to: 98
                    duration: 350 * triangles.timeWarp
                    easing.type: Easing.OutCubic
                }

                NumberAnimation {
                    target: logoRight
                    property: "x"
                    to: -75
                    duration: 350 * triangles.timeWarp
                    easing.type: Easing.OutCubic
                }

                NumberAnimation {
                    target: logoBottom
                    property: "y"
                    to: -50
                    duration: 350 * triangles.timeWarp
                    easing.type: Easing.OutCubic
                }

                NumberAnimation {
                    target: logoOverlay
                    property: "width"
                    to: 317
                    duration: 650 * triangles.timeWarp
                    easing.type: Easing.OutCubic
                }

                SequentialAnimation {
                    NumberAnimation { duration: 300 * triangles.timeWarp }
                    ParallelAnimation {
                        NumberAnimation {
                            target: logoOverlay
                            property: "opacity"
                            to: 0
                            duration: 550 * triangles.timeWarp
                        }

                        NumberAnimation {
                            target: logoOverlayMask
                            property: "width"
                            to: 300
                            duration: 650 * triangles.timeWarp
                            easing.type: Easing.OutCubic
                        }
                    }
                    ScriptAction { script: {
                        logoMain.visible = false;
                        logoLeft.visible = false;
                        logoBottom.visible = false;
                        logoRight.visible = false
                    }}

                    ParallelAnimation {
                        NumberAnimation {
                            target: logoOverlay
                            property: "width"
                            to: 167
                            duration: 650
                            easing.type: Easing.OutCubic
                        }

                        NumberAnimation {
                            target: logoOverlayMask
                            property: "width"
                            to: 150
                            duration: 650
                            easing.type: Easing.OutCubic
                        }

                        SequentialAnimation {
            //            running: true
                        ParallelAnimation {
                            NumberAnimation {
                                id: rotationAnimation
                                target: piecesTransform
                                property: "angle"
                                duration: 200000 * (2/360)
                                from: 48
                                to: 46
                            }
                            SequentialAnimation {
                                NumberAnimation { duration: 800 }
                                ScriptAction { script:
                                    triangles.interpolateToDisAsm(piecesTransform.angle, false) }
                            }
                        }
                        ParallelAnimation {
                            NumberAnimation {
                                target: piecesTransform
                                property: "angle"
                                duration: 200000 * (4/360)
                                from: 46
                                to: 42
                            }

                            SequentialAnimation {
                                NumberAnimation { duration: 1800 }
                                SequentialAnimation {
                                NumberAnimation {
                                    target: logOColoredoOverlay
                                    property: "opacity"
                                    to: 0
                                    duration: 400
                                }

                                NumberAnimation {
                                    target: logoOverlayMask
                                    property: "opacity"
                                    to: 0
                                    duration: 0
                                }
                                }
                            }
                        }
                        ScriptAction { script: triangles.interpolateToAsm(piecesTransform.angle, false) }
                        NumberAnimation { duration: 1600 }
                        SequentialAnimation {
                           NumberAnimation {
                               target: titleText
                               property: "anchors.topMargin"
                               duration: 550
                               easing.type: Easing.OutCubic
                               to: 0
                           }

                           NumberAnimation {
                               target: subtext
                               property: "y"
                               duration: 250
                               easing.type: Easing.InOutQuad
                               to: 0
                           }
                       }
                    }
                    }
                }
            }

            SequentialAnimation {
                NumberAnimation { duration: 1400 }
                NumberAnimation {
                    targets: [triangles, subtext, textPonik, textSonik]
                    property: "opacity"
                    to: 0
                    duration: 450
                }
            }
        }

    }
}
