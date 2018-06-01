import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1280
    height: 720
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

        anchors.centerIn: parent
//        opacity: 0

        transform: Rotation {
            id: logoTransform
            origin.x: logo.width / 2
            origin.y: 0

            angle: 0
            axis { x: 0; y: 1; z: 0 }
        }

        onAnimate: SequentialAnimation {
//            NumberAnimation { id: animation; target: logoTransform; property: "angle";
//                duration: 6000; from: 0;to: 360 * 5; easing.type: Easing.InCubic }
            ScriptAction { script: canvas.inter = 1 }
        }
    }

    Canvas {
        id: canvas

        property real inter: 0.

        anchors.fill: parent

        Behavior on inter{
            NumberAnimation { duration: 900; easing.type: Easing.InCubic }
        }

        onInterChanged: requestPaint()

        onPaint: {
            var destPoints = [
                Qt.point(100, 150),
                Qt.point(250, 150),
                Qt.point(150, 250),

                        Qt.point(100+ 200, 150),
                        Qt.point(250+150, 150),
                        Qt.point(150+190, 250)
            ]

            var srcPoints = [
                Qt.point(logo.x + logo.width / 2 + 50, logo.y + logo.height / 2 + 60),
                Qt.point(logo.x + logo.width / 2, logo.y + logo.height / 2),
                Qt.point(logo.x + logo.width / 2 - 50, logo.y + logo.height / 2),

                Qt.point(logo.x + logo.width / 2 + 150, logo.y + logo.height / 2+ 40),
                Qt.point(logo.x + logo.width / 2, logo.y + logo.height / 2),
                Qt.point(logo.x + logo.width / 2 - 20, logo.y + logo.height / 2)
            ]

            var ctx = canvas.getContext("2d")
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            var colors = ["black", "red"]
            for(var j = 0; j < 2; j++) {
                var points = []

                for(var i = 0; i < 3; i++) {
                    var key = j * 3 + i
                    points[i] = srcPoints[key]
                    points[i].x += (destPoints[key].x - srcPoints[key].x) * canvas.inter
                    points[i].y += (destPoints[key].y - srcPoints[key].y) * canvas.inter
                }

                ctx.fillStyle = colors[j]

                ctx.beginPath()
                ctx.moveTo(points[0].x, points[0].y)

                for(var i in points) {
                    if(i === 0)
                        continue
                    ctx.lineTo(points[i].x, points[i].y)
                }
                ctx.lineTo(points[0].x, points[0].y)
                ctx.fill()
            }
        }
    }
}
