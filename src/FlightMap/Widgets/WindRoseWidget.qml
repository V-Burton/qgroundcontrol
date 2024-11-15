import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.12

import QGroundControl.Controls 1.0
import QGroundControl.ScreenTools 1.0
import QGroundControl.Vehicle 1.0
import QGroundControl.Palette 1.0
import QGroundControl.FactSystem 1.0

Item {
    id: root
    width: size
    height: size

    property var windFactGroup: null
    property real size: ScreenTools.defaultFontPixelHeight * 10

    QGCPalette { id: qgcPal }

    Rectangle {
        anchors.fill: parent
        color: qgcPal.window
        radius: width / 2
        border.color: qgcPal.text
        border.width: 1

        // Points cardinaux
        Repeater {
            model: [
                { text: "N", angle: 0 },
                { text: "E", angle: 90 },
                { text: "S", angle: 180 },
                { text: "W", angle: 270 }
            ]

            QGCLabel {
                anchors.centerIn: parent
                transform: [
                    Translate {
                        x: (parent.width * 0.4) * Math.sin(modelData.angle * Math.PI / 180)
                        y: -(parent.width * 0.4) * Math.cos(modelData.angle * Math.PI / 180)
                    }
                ]
                text: modelData.text
                color: qgcPal.text
                font.pointSize: ScreenTools.defaultFontPointSize * 0.8
            }
        }

        // Lignes des points cardinaux
        Repeater {
            model: 4
            Rectangle {
                anchors.centerIn: parent
                height: parent.height * 0.8
                width: 1
                color: qgcPal.text
                opacity: 0.3
                rotation: index * 90
                transformOrigin: Item.Center
            }
        }

        // Flèche du vent
        Item {
            id: windArrow
            anchors.centerIn: parent
            width: parent.width * 0.3  // Réduction de la taille
            height: width
            rotation: 180

            Shape {
                anchors.fill: parent
                ShapePath {
                    strokeWidth: 2
                    strokeColor: qgcPal.colorOrange
                    fillColor: qgcPal.colorOrange
                    startX: windArrow.width / 2
                    startY: 0
                    PathLine { x: windArrow.width; y: windArrow.height }
                    PathLine { x: windArrow.width / 2; y: windArrow.height * 0.8 }
                    PathLine { x: 0; y: windArrow.height }
                    PathLine { x: windArrow.width / 2; y: 0 }
                }
            }
        }

        // Vitesse du vent
        QGCLabel {
            anchors.centerIn: parent
            text: {
                if (windFactGroup && windFactGroup.speed2D.value) {
                    return windFactGroup.speed2D.value.toFixed(1) + " m/s"
                }
                return "0.0 m/s"
            }
            font.pointSize: ScreenTools.defaultFontPointSize
            color: qgcPal.text
            
        }

        // État
        QGCLabel {
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: parent.height * 0.1
            }
            text: windFactGroup ? "Live" : "No Data"
            color: windFactGroup ? qgcPal.colorGreen : qgcPal.colorOrange
            font.pointSize: ScreenTools.defaultFontPointSize * 0.8
        }
    }

    Component.onCompleted: {
        console.log("WindRoseWidget completed")
        console.log("Wind FactGroup:", windFactGroup ? "available" : "null")
        console.log("WindRoseWidget base dimensions:", width, height)
    }

    onWindFactGroupChanged: {
        console.log("Wind FactGroup changed:", 
            windFactGroup ? {
                hasSpeed2D: windFactGroup.speed2D ? "yes" : "no",
                speed2DValue: windFactGroup.speed2D ? windFactGroup.speed2D.value : "N/A",
                hasDirection: windFactGroup.horizontalDirection ? "yes" : "no",
                directionValue: windFactGroup.horizontalDirection ? windFactGroup.horizontalDirection.value : "N/A"
            } : "null")
    }
}