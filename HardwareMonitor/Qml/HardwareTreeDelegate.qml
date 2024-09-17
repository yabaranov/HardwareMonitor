import QtQuick

Item {
   id: hardwareTreeDelegate
                                
   required property TreeView treeView              
   required property bool isTreeNode               
   required property bool expanded              
   required property int hasChildren                
   required property int depth

   readonly property real indent: treeView.indent
   readonly property real padding: treeView.padding  

   implicitWidth: hardwareTreeDelegate.padding + label.x + label.implicitWidth + hardwareTreeDelegate.padding
   implicitHeight: label.implicitHeight

   TreeConnector {
      id: treeConnector
      depth: hardwareTreeDelegate.depth
      indent: hardwareTreeDelegate.indent
      padding: hardwareTreeDelegate.padding
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
      x: hardwareTreeDelegate.padding + (hardwareTreeDelegate.depth * hardwareTreeDelegate.indent)
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
      x: hardwareTreeDelegate.isTreeNode ? icon.x + hardwareTreeDelegate.indent : hardwareTreeDelegate.padding
      anchors.verticalCenter: parent.verticalCenter
      width: hardwareTreeDelegate.width - hardwareTreeDelegate.padding - x
      elide: Text.ElideRight
      text: model.display
   }         
}
