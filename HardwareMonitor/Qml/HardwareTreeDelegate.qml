import QtQuick

Item {
   id: hardwareTreeDelegate
                                
   required property TreeView treeView              
   required property bool isTreeNode               
   required property bool expanded              
   required property int hasChildren                
   required property int depth

   readonly property real indent: treeView.indent

   implicitWidth: label.x + label.implicitWidth
   implicitHeight: label.implicitHeight

   TreeConnector {
      id: treeConnector
      depth: hardwareTreeDelegate.depth
      indent: hardwareTreeDelegate.indent
      indicatorX: indicator.x
      indicatorWidth: indicator.width
      iconX: icon.x
   }

   onYChanged: {
      treeConnector.requestPaint();
   }
          
   TapHandler {
      onTapped: treeView.toggleExpanded(row)
   }

   Image {
      id: indicator
      visible: hardwareTreeDelegate.isTreeNode && hardwareTreeDelegate.hasChildren
      x: hardwareTreeDelegate.depth * hardwareTreeDelegate.indent
      anchors.verticalCenter: parent.verticalCenter         
      source: treeView.src + (hardwareTreeDelegate.expanded ? treeView.off : treeView.on)
   }  

   Image {
      id: icon
      visible: hardwareTreeDelegate.isTreeNode && hardwareTreeDelegate.hasChildren
      x: indicator.x + hardwareTreeDelegate.indent - (icon.width - indicator.width) / 2
      anchors.verticalCenter: parent.verticalCenter
      source: treeView.src + model.icon
   }  

   Text {
      id: label
      x: hardwareTreeDelegate.isTreeNode ? icon.x + hardwareTreeDelegate.indent : 0
      anchors.verticalCenter: parent.verticalCenter
      width: hardwareTreeDelegate.width - x
      elide: Text.ElideRight
      text: model.display
   }         
}
