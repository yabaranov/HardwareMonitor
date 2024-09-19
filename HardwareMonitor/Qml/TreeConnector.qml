import QtQuick

Canvas {
   id: treeConnector
   width: parent.width
   height: parent.height

   property int depth
   property real indent
   property real indicatorX
   property real indicatorWidth
   property real iconX

   onPaint: {
      var ctx = treeConnector.getContext("2d");
      ctx.clearRect(0, 0, treeConnector.width, treeConnector.height);
      ctx.strokeStyle = "black";
      ctx.lineWidth = 1;
      ctx.setLineDash([1, 1]);

      if(column === 0) {       
         ctx.beginPath();

         var dist = treeConnector.indicatorWidth / 2
         for (var i = 0; i <= depth; i++) {
            ctx.moveTo((i * treeConnector.indent) + dist, 0);
            ctx.lineTo((i * treeConnector.indent) + dist, treeConnector.height);
         }

         ctx.moveTo(treeConnector.indicatorX + treeConnector.indicatorWidth / 2, treeConnector.height / 2);
         ctx.lineTo(treeConnector.iconX, treeConnector.height / 2);
         
         ctx.stroke();
      }
   }
}
