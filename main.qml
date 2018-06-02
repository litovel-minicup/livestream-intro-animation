import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1280
    height: 1000
    title: qsTr("Hello World")

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton |Qt.RightButton
        onClicked: {
            logo.animate()
//            if(mouse.button === Qt.LeftButton)
//                canvas.inter = 1
//            else
//                canvas.inter = 0
        }
    }

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
//        opacity: 0

        transform: Rotation {
            id: logoTransform
            origin.x: logo.width / 2
            origin.y: 0

            angle: 0
            axis { x: 0; y: 1; z: 0 }
        }

        onAnimate: {
            if(canvas.interpolation == 1.)
                canvas.interpolation = 0
            else
                canvas.interpolation = 1
        }
    }

    Canvas {
        id: canvas

        property real interpolation: 0
        property real rotationAngle: 0

        width: parent.width
        height: parent.height

        onInterpolationChanged: requestPaint()

//        transform: Rotation {
//            id: piecesTransform
//            origin.x: 650
//            origin.y: 295

//            angle: 0
//            axis { x: 0; y: 0; z: 1 }
//        }

        Behavior on interpolation {
            NumberAnimation {
                duration: 1000
                easing.type: Easing.OutQuad
            }
        }

        NumberAnimation {
            target: canvas
            running: true
            loops: Animation.Infinite
            property: "rotationAngle"
            duration: 80000
            from: 0;
            to: 360
        }

        onRotationAngleChanged: requestPaint()

        onPaint: {
            var ctx = canvas.getContext("2d");
            var triangles = pieceManager.interpolated(canvas.interpolation);

            ctx.clearRect(0, 0, canvas.width, canvas.height)
            var centerPoint = Qt.point(650, 295 + 120)
            ctx.translate(centerPoint.x, centerPoint.y)
            ctx.rotate((Math.PI / 180) * 0.5)
            ctx.translate(-centerPoint.x, -centerPoint.y)

            for(var i in triangles) {
                var singleTriangle = triangles[i]
                var trianglePoints = singleTriangle.points
                ctx.fillStyle = singleTriangle.color

                ctx.beginPath()
                ctx.moveTo(trianglePoints[0].x, trianglePoints[0].y)
                ctx.lineTo(trianglePoints[1].x, trianglePoints[1].y)
                ctx.lineTo(trianglePoints[2].x, trianglePoints[2].y)
                ctx.lineTo(trianglePoints[0].x, trianglePoints[0].y)

                ctx.fill()
                ctx.closePath()
            }
        }
    }
}
