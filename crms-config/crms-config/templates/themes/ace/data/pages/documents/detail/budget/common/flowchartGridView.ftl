        <#include "../functions/fixHeaders.ftl"/>

$('#example').handsontable({
	  width: 1200,
	  height:400,
	  minSpareRows:1,
	  minSpareCols:1,
	  manualColumnResize:true,
	  rowHeaders:fixRowHeaders,
	  colHeaders: fixColHeaders,
	  minCols: 5,
	  minRows: 15,

	  contextMenu: false,
	
	  cells: function (row, col, prop) {
	    var cellProperties = {}
	    if(row !== 0 && col !== 0) {
	      cellProperties.renderer=myCheckboxRenderer;
	    }
	    else{
	      
	      cellProperties.readOnly=true;
	      cellProperties.renderer=myTranslateRender;
	    }      
	    return cellProperties;
	  },
	  afterChange: function(changes, source) {
	      if(source!='loadData'){
	        var data= $('#example').data('handsontable').getData();
	        //loadData(data);
	      }
	      
	      if( costiInit && changes!==null){
	      //console.log('qui');
	      	  var allChanges=clone(changes);
	      	  while($.isArray(changes[0])){
	      	  		allChanges=changes;
	      	  		changes=changes[0];
	      	  }
			
	          for(var i=0;i<allChanges.length;i++){
				
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
	  },
	  afterCreateCol:function(index,amount){
	      if($('#example').data('handsontable').isPopulated()){
	          var data= $('#example').data('handsontable').getData();
	          loadData(data);
	      }
	      $('#costi').handsontable('alter','insert_col',index,amount);
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
          
          
  
  