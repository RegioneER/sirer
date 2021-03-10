     <#include "../functions/fixHeaders.ftl"/>
var reloadFCTimer=null;     
$('#example').handsontable({
  width: 1200,
  height:450,
  minSpareRows:2,
  minSpareCols:2,
  manualColumnResize:true,
  rowHeaders:fixRowHeaders,
  colHeaders: fixColHeaders,
  minCols: 5,
  minRows: 15,
  
  contextMenu: true,

  cells: function (row, col, prop) {
    var cellProperties = {}
    cellProperties.readOnly=!updating;
    if(row !== 0 && col !== 0) {
      cellProperties.renderer=myCheckboxRenderer;
    }
    else{
      
      if(row>0) {
      	cellProperties.renderer=myForm1Renderer;
      	
      	
      }
      	
      if(col>0) cellProperties.renderer=myForm2Renderer;
    }        
    return cellProperties;
  },
  afterChange: function(changes, source) {
      var reload=false;
      
      if( costiInit && changes!==null){
      //console.log('qui');
      	  var allChanges=clone(changes);
      	  while($.isArray(changes[0])){
      	  		allChanges=changes;
      	  		changes=changes[0];
      	  }
		
          for(var i=0;i<allChanges.length;i++){
			if(allChanges[i][0]==0 || allChanges[i][1]==0){
				reload=true;
			}
          	if(allChanges[i]!==undefined && $.isArray(allChanges[i]) && (allChanges[i][0]==0 || allChanges[i][1]==0)  ){
          
          	
          		$('#costi').handsontable('setDataAtCell',allChanges[i][0],allChanges[i][1],allChanges[i][3]);
          	}
          	else if(allChanges[i]!==undefined && $.isArray(allChanges[i]) && allChanges[i][0]>0 && allChanges[i][1]>0 ){
          		var myElement=$.axmr.guid(allChanges[i][3]);
          		if(!myElement && allChanges[i][3]){
          			myElement=prepareTpxp(allChanges[i][3],allChanges[i][0],allChanges[i][1]);
          			var myValue=$.axmr.guid(myElement,getDato(myElement.metadata['tp-p_Checked']),getDato(myElement.metadata['Costo_TransferPrice']));
          			$('#example').handsontable('setDataAtCell',allChanges[i][0],allChanges[i][1],myValue);
          		}
          		else if(myElement){
          			var myValue=$.axmr.guid(myElement,getDato(myElement.metadata['tp-p_Checked']),getDato(myElement.metadata['Costo_TransferPrice']));
          		
          			$('#costi').handsontable('setDataAtCell',allChanges[i][0],allChanges[i][1],myValue);
          		}
          		else{
          			$('#costi').handsontable('setDataAtCell',allChanges[i][0],allChanges[i][1],'');
          		}
          	}
          	
          	//$('#costi').handsontable('setDataAtCell',changes);
          }
      }
      else if(changes){
       	console.log(costiInit);
       	console.log(changes);
       	var allChanges=clone(changes);
      	while($.isArray(changes[0])){
      			allChanges=changes;
      			changes=changes[0];
      	}
      	for(var i=0;i<allChanges.length;i++){
      		if(allChanges[i][0]==0 || allChanges[i][1]==0){
				reload=true;
			}
           if(allChanges[i][0]!=0 && allChanges[i][1]!=0){
      			var myElement=$.axmr.guid(allChanges[i][3]);
          		if(!myElement && allChanges[i][3]){
          			myElement=prepareTpxp(allChanges[i][3],allChanges[i][0],allChanges[i][1]);
          			var myValue=$.axmr.guid(myElement,getDato(myElement.metadata['tp-p_Checked']),getDato(myElement.metadata['Costo_TransferPrice']));
          			$('#example').handsontable('setDataAtCell',allChanges[i][0],allChanges[i][1],myValue);
          		}
      		}
      	}
      }
      if(source!='loadData' && reload){
      	if(reloadFCTimer){
          	clearTimeout(reloadFCTimer);
          }
        setTimeout(function(){
        	var data= $('#example').data('handsontable').getData();
        	loadData(data);
        },100);
        
      }
  },
  afterCreateCol:function(index,amount){
      if($('#example').data('handsontable').isPopulated()){
          var data= $('#example').data('handsontable').getData();
          loadData(data);
      }
      $('#costi').handsontable('alter','insert_col',index,amount);
      if($('#example').data('handsontable').isPopulated()){
      	  var baseVisita= $('#example').handsontable('getDataAtCell',0,1);
	        if(!baseVisita){
	        	baseVisita=0;
	        }else{
	        	var objV0=$.axmr.guid(baseVisita);
	        	if(objV0){
	        		baseVisita=getDato(objV0.metadata['TimePoint_NumeroVisita']);
	        		baseVisita=parseInt(baseVisita);
	        	}else{
	        		baseVisita=0;
	        	}
	        }
	      var rowData=$('#example').handsontable('getDataAtRow',0);
	      for(var idx=1;idx<rowData.length;idx++){
	      	var currCol=idx+1;
	      	myElement=$.axmr.guid(rowData[idx]);
	      	if($.isPlainObject(myElement) && myElement.metadata ){
	      		myElement.metadata['TimePoint_col']=currCol;
	      		myElement.metadata['TimePoint_NumeroVisita']=idx-1+baseVisita;
	      		$.axmr.setUpdated(myElement);
	      		$.axmr.guid(myElement,buildTpDescription(myElement));
	      	}
	      }
	      
      }
  },
  afterCreateRow:function(index,amount){
      if($('#example').data('handsontable').isPopulated()){
          var data= $('#example').data('handsontable').getData();
          loadData(data);
      }
      $('#costi').handsontable('alter','insert_row',index,amount);
  },
  afterRemoveCol:function(index,amount){
      if($('#example').data('handsontable').isPopulated()){
          var data= $('#example').data('handsontable').getData();
          loadData(data);
      }
      if($('#example').data('handsontable').isPopulated()){
	      var rowData=$('#example').handsontable('getDataAtRow',0);
	      for(var idx=1;idx<rowData.length;idx++){
	      	var baseVisita= $('#example').handsontable('getDataAtCell',0,1);
	        if(!baseVisita){
	        	baseVisita=0;
	        }else{
	        	var objV0=$.axmr.guid(baseVisita);
	        	if(objV0){
	        		baseVisita=getDato(objV0.metadata['TimePoint_NumeroVisita']);
	        		baseVisita=parseInt(baseVisita);
	        	}else{
	        		baseVisita=0;
	        	}
	        }
	      	var currCol=idx+1;
	      	myElement=$.axmr.guid(rowData[idx]);
	      	if($.isPlainObject(myElement) && myElement.metadata ){
	      		myElement.metadata['TimePoint_col']=currCol;
	      		myElement.metadata['TimePoint_NumeroVisita']=idx-1+baseVisita;
	      		$.axmr.setUpdated(myElement);
	      		$.axmr.guid(myElement,buildTpDescription(myElement));
	      	}
	      }
      }
      $('#costi').handsontable('alter','remove_col',index,amount);
  },
  afterRemoveRow:function(index,amount){
      if($('#example').data('handsontable').isPopulated()){
          var data= $('#example').data('handsontable').getData();
          loadData(data);
      }
      $('#costi').handsontable('alter','remove_row',index,amount);
  }
  });
  
  