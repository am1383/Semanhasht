import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: screen.width
    height: screen.height
    visible: true
    Material.background: "white"//"#212128"
    Material.accent: Material.Indigo
    //title: qsTr("Semanhasht")

    property string start: ""
    property string end: ""
    property int c1: -1
    property int c2: -1
    property int them: 1

    Drawer {
        id: drawer
        width: root.width / 3.5
        height: root.height

        Rectangle {
            id: startHintText
            width: parent.width
            height: 30
            visible: startTF.text === "" ? true : false
            //anchors.left: startTF.left
            Label {
                id: st1
                text: "Type your origin or"
                anchors.left: parent.left
                anchors.leftMargin: 60
            }
            Label {
                text: "select it on the map."
                anchors.left: st1.right
                anchors.leftMargin: 7
                color: "blue"
                MouseArea {
                    anchors.fill: parent
                    onClicked: drawer.close()
                }
            }
        }

        TextField {
            id: startTF
            anchors.top: startHintText.bottom
            anchors.topMargin: 7
            text: start
            width: parent.width/1.3
            anchors.left: parent.left
            anchors.leftMargin: 60

            Label {
                id: originStationError
                text: "There is no station with this name !"
                color: "red"
                visible: c1 == -1 && startTF.text !== "" ? true : false
                anchors.top: parent.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
            }

            Rectangle {
                width: 20
                height: 20
                radius: 10
                //color: "black"
                border.color: "black"
                anchors.right: startTF.left
                anchors.rightMargin: 20
                anchors.verticalCenter: startTF.verticalCenter
                Rectangle {
                    width: 8
                    height: 8
                    radius: 4
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 25
                }

                Rectangle {
                    width: 8
                    height: 8
                    radius: 4
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 43
                }

                Rectangle {
                    width: 8
                    height: 8
                    radius: 4
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 60
                }
            }

            onTextChanged:{
                c1 = semanhasht.check_station_validation(startTF.text)//console.log ("hi")
            }
        }
        TextField {
            id: endTF
            anchors.top: startTF.bottom
            anchors.topMargin: 28
            text: end
            width: parent.width/1.3
            anchors.left: parent.left
            anchors.leftMargin: 60

            Label {
                id: destinationStationError
                text: "There is no station with this name !"
                color: "red"
                visible: c2 == -1 && endTF.text !== "" ? true : false
                anchors.top: parent.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
            }

            Image {
                id: destinationIMG
                source: "img/destination.png"
                anchors.right: parent.left
                anchors.rightMargin: 7
                anchors.verticalCenter: parent.verticalCenter
            }

            onTextChanged:{
                c2 = semanhasht.check_station_validation(endTF.text)//console.log ("hi")
            }
        }

        Rectangle {
            id: endHintText
            anchors.top: endTF.bottom
            anchors.topMargin: 10
            width: parent.width
            height: 30
            visible: endTF.text === "" ? true : false
            
            Label {
                id: et1
                text: "Type your destination or"
                anchors.left: parent.left
                anchors.leftMargin: 40
            }

            Label {
                text: "select it on the map."
                anchors.left: et1.right
                anchors.leftMargin: 7
                color: "blue"
                MouseArea {
                    anchors.fill: parent
                    onClicked: drawer.close()
                }
            }
        }

        RadioButton {
            id: currently
            anchors.left: endTF.left
            anchors.leftMargin: 20
            anchors.top: endTF.bottom
            anchors.topMargin: 30
            checked: true
            text: qsTr("Now")
        }

        RadioButton {
            id: anotherTime
            text: qsTr("In another time:")
            anchors.verticalCenter: currently.verticalCenter
            anchors.left: currently.right
            anchors.leftMargin: 30
        }

        TextField {
            id: hourTF
            visible:  anotherTime.checked ? true : false
            height: 40
            width: 50
            anchors.left: currently.left
            anchors.leftMargin: 50
            anchors.top: currently.bottom
            anchors.topMargin: 15
            validator: RegularExpressionValidator {regularExpression:/^[0-9]{1,2}$/}
            Label{
                text: "hour  :"
                font.bold: true
                anchors.right: hourTF.left
                anchors.rightMargin: 7
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        TextField {
            id: minutTF
            visible:  anotherTime.checked ? true : false
            height: 40
            width: 50
            anchors.left: hourTF.right
            anchors.leftMargin: 70
            anchors.verticalCenter: hourTF.verticalCenter
            validator: RegularExpressionValidator {regularExpression:/^[0-9]{1,2}$/}
            Label{
                text: "minute  :"
                font.bold: true
                anchors.right: minutTF.left
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: timemas
            visible: false
            anchors.top: minutTF.bottom
            anchors.topMargin: 10
            width: parent.width
            height: 120
            radius: 2
            border.color: "black"
            color: "#00BCD4"//"#3F51B5"
            Label {
                id : timePathLb
                text: ""
                color: "white"
                font.bold: true
                font.pixelSize: 20
                wrapMode: Text.WordWrap
                anchors.fill: parent
            }
        }

        Rectangle {
            id: costmas
            visible: false
            anchors.top: timemas.bottom
            width: parent.width
            height: 120
            radius: 2
            border.color: "black"
            color: "#00BCD4"//"#3F51B5"
            Label {
                id : costPathLb
                text: ""
                color: "white"
                font.bold: true
                font.pixelSize: 20
                wrapMode: Text.WordWrap
                anchors.fill: parent
            }
        }

        Rectangle {
            id: distmas
            visible: false
            anchors.top: costmas.bottom
            width: parent.width
            height: 120
            radius: 2
            border.color: "black"
            color: "#00BCD4"//"#3F51B5"
            Label {
                id : distPathLb
                text: ""
                color: "white"
                font.bold: true
                font.pixelSize: 20
                wrapMode: Text.WordWrap
                anchors.fill: parent
            }
        }
    }

    header: ToolBar{
        //Material.background: Material.Pink//"Black"//Material.BlueGrey
        height: 50

        ToolButton {
            anchors.left: parent.left
            icon.source: "img/openDrawer.png"
            onClicked: drawer.open()
        }

    }

    Image {
        id: entrancePic
        source: "img/PublicTransportation.jpeg"
        width: parent.width
        height: parent.height
        z: 50

        Label {
            text: "Semanhasht"
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            font.italic: true
            font.bold: true
            font.pixelSize: 40
        }

        AnimatedImage {
            source: "img/loading.gif"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 70
            width: 80
            height: 80
        }

        Timer {
            id: timer
            interval: 2500
            running: true
            repeat: false
            onTriggered: {
                entrancePic.visible = false
            }
        }
    }

    Component.onCompleted: {
        mainLoad.source = "qrc:/Semanhasht/qml/map.qml"
    }

    Loader {
        id: mainLoad
        width: parent.width
        height: parent.height
    }
}

