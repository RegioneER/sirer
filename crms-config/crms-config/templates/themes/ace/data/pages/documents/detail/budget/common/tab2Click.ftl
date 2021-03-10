
$("#tab2").click(function(){
	rimuoviTotali();
    var lastCol=-1;
    var lastRow=-1;
    var data=$('#example').data('handsontable').getData();
    for(var i=0;i<data[0].length;i++){
        if(data[0][i]!==null && data[0][i]!==undefined && data[0][i]!==''){
            lastCol=i;
        }
    }
    for(var k=0;k<data.length;k++){
        if(data[k][0]!==null && data[k][0]!==undefined && data[k][0]!==''){
            lastRow=k;
        }
    }
    var numCols=lastCol+1;
    var numRows=lastRow+1;
    var startX=10;
    var startY=110;
    var baseY=startY;
   
    var layer = new Kinetic.Layer();
    var totalHeight=startY;
    var totalWidth=startX+200+(50*lastCol); 
    totalWidth=Math.max(1200,totalWidth);
    var rightOffset=startX+200;
    var heights=new Array();
    var widths=new Array();
    console.log("1",totalWidth,lastCol,rightOffset,(totalWidth-rightOffset));
    for(var j=1;j<=lastRow;j++){
        var complexText = new Kinetic.Text({
            x: startX,
            y: startY,
            text: $.trim($.axmr.label(data[j][0])),
            fontSize: 12,
            fontFamily: 'sans-serif',
            lineHeight:1.5,
            fill: '#555',
            width: 200,
            padding: 5,
            align: 'left'
          });
        var offsetY=complexText.getHeight()/2-4;
        var offsetX=startX+200;
        heights[j]=startY+offsetY;
        var line = new Kinetic.Line({
          x: offsetX,
          y: startY,
          points: [0, offsetY, (totalWidth-rightOffset), offsetY],
          strokeWidth:1,
          stroke:'#555'
          
        });
        layer.add(complexText);
        layer.add(line);
        startY+=complexText.getHeight();
        totalHeight=startY;
    }
    for(var z=1;z<=lastCol;z++){
       offsetX+=30;
       
       var complexText = new Kinetic.Text({
            x: offsetX,
            y: baseY-20,
            text: firstLine($.axmr.label(data[0][z])),
            fontSize: 12,
            fontFamily: 'sans-serif',
            lineHeight:1.5,
            fill: '#555',
            width: 150,
            padding: 5,
            rotationDeg:-45,
            align: 'left'
          });
       //var offsetY=complexText.getHeight()/2-4;
       offsetX+=complexText.getHeight()/2-4;
       //heights[j]=startY+offsetY;
       widths[z]=offsetX;
       var line = new Kinetic.Line({
          x: offsetX,
          y: baseY,
          points: [0, 0, 0, totalHeight],
          strokeWidth:1,
          stroke:'#555'
          
        }) ;
        layer.add(complexText);
        layer.add(line);
    }
    for(var row=1;row<=lastRow;row++){
        for(var col=1;col<=lastCol;col++){
            if(data[row][col]){
            	var currElement=$.axmr.guid(data[row][col]);
                var currColor='lightblue';
                var currColorCode=getDato(currElement.metadata['Rimborso_Rimborsabilita']);
                currColorCode+='';
                switch(currColorCode){
                    case '0':
                        currColor='lightblue';
                    break;
                    case '1':
                        currColor='orange';
                    break;
                    case '2':
                        currColor='white';
                    break;
                }
                var circle = new Kinetic.Circle({
                  id:data[row][col],
                  x:widths[col],
                  y:heights[row],
                  radius: 10,
                  fill: currColor,
                  stroke: '#555',
                  strokeWidth: 1
                });
                if(updating)
                circle.on('click',function(){
                    var color='';
                    var inputVal=0;
                    var id=this.getId();
                   
                    switch(this.getFill()){
                        case 'lightblue':
                          color='orange';
                          inputVal=1;
                        break;
                        case 'orange':
                          color='white';
                          inputVal=2;
                        break;
                        case 'white':
                          color='lightblue';
                          inputVal=0;
                        break;
                    }
                    setRimborso(id,inputVal);
                    
                    
                    
                    this.setFill(color);
                    layer.draw();
                    
                });
                circle.on('mouseover',function(){      
                    document.body.style.cursor = 'pointer';
                });
                circle.on('mouseout',function(){             
                    document.body.style.cursor = 'default';
                });
                layer.add(circle);
            }
        }
    }
    $('#tabs-2').css({"overflow":"scroll"});
    //$('#tabs-2').width(totalWidth);
    //$('#tabs-2').parent().width(totalWidth);
    var stage = new Kinetic.Stage({
        container: 'grafico',
        width: totalWidth,
        display:'block',
        height: totalHeight
      });
    stage.clear();
    stage.add(layer);
});
	                