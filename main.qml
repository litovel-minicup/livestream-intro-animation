import QtQuick 2.9
import QtQuick.Window 2.2
import TriangleContainer 1.0

Window {
    visible: true
    width: 1280
    height: 1000
    title: qsTr("Hello World")

    Image {
        id: logo

        signal animate

        z: 1
        source: "qrc:/logo.svg"
        width: 400
        height: 600
        fillMode: Image.PreserveAspectFit

        sourceSize: Qt.size(400, 600)
        opacity: 0

        anchors.centerIn: parent
    }

    MouseArea {
        property bool inverted: false

        anchors.fill: parent
        onClicked: {
            triangles.interpolate(inverted)
            inverted = !inverted
        }
    }

    TriangleContainer {
        id: triangles

        width: parent.width
        height: parent.height

        transform: Rotation {
            id: piecesTransform
            origin.x: 650
            origin.y: 295 + 120

            angle: 0
            axis { x: 0; y: 0; z: 1 }
        }


        NumberAnimation {
            target: piecesTransform
            property: "angle"
            duration: 60000
            running: true
            loops: Animation.Infinite
            from: 0
            to: 360
        }

    }
}
