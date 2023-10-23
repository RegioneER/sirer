(function ($, window) {
    var guid=100000000000000;
    var elements=[];
    var labels=[];
    labels[1]=[];
    labels[2]=[];
    var ids=[];

    $.axmr={};
    $.axmr.guid=function(incoming,label,label2){

        if($.isPlainObject(incoming) || $.isArray(incoming)){
        	currGuid=-1;
        	if(incoming.guid){
        		currGuid=incoming.guid;
        	}
        	else{
	        	var search=function(obj,idx){
	        		currGuid=idx;
	    			return (obj===incoming) ;
	    		}
	    		$.grep(elements,search);
    		}
            
            if(currGuid==-1){
                currGuid=++guid;
                incoming.guid=currGuid;
                elements[currGuid]=incoming;
            }
            if(incoming['id']){
                ids[incoming['id']]=currGuid;
            }
            if(label!==undefined){
                labels[1][currGuid]=label;
            }
            if(label2!==undefined){
                labels[2][currGuid]=label2;
            }
            return currGuid;
        }else{
            return elements[incoming];
        }
    };
    $.axmr.getAllElements=function(){
        return elements;
    };
    $.axmr.label=function(incoming,index){
        if(!elements[incoming]){
            return incoming;
        }
        if(!index){
           index=1;
        }
        return labels[index][incoming];
    };
    $.axmr.searchById=function(id){
         return ids[id];
    };
    $.axmr.getById=function(id){
         return elements[ids[id]];
    };
    $.axmr.deselectGrid=function(id){
        $(id).handsontable('deselectCell');
        setTimeout(function(){$(id).handsontable('deselectCell');},500);
    }
})(jQuery);
var lastCostRow, lastCostCol;
 var markup=0;
 var pazienti=0;
var costiInit=false;
var tariffarioAlpi=new Array();
var tariffarioSSN=new Array();
var dizPrestazioni=new Array();

var folderTp=null;
var folderPrestazioni=null;
var folderTpxp=null;
var folderPxp=null;
var folderPxs=null;
var folderBudgetStudio=null;
var folderPxsCTC=null;
var folderPxpCTC=null;
var folderPassthroughCTC=null;
var rowAltro=null;
var totalePaziente=0;
var totaleStudio=0;
function prepareElementForPost(element){
    element=$.extend(true,{},element);
    $.each(element, function(property,value){
        if(value===null || value===undefined) element[property]="";
        else if(!$.isPlainObject(value) &&  !$.isArray(value) ) element[property]=value.toString();
    });
    if(element.metadata)element.metadata=prepareMetadataForPost(element.metadata);
    return element;
}

function saveGrid(){
	var layout=$.extend(true,[],$('#example').data('handsontable').getData());
	var elements=$.extend(true,{},$.axmr.getAllElements());
	var folders={};
	var coordinates={"x":"tp-p_TimePoint","y":"tp-p_Prestazione","row":"Prestazioni_row","col":"TimePoint_NumeroVisita"};
	
	folders[emptyTimePoint.type.id]=folderTp;
	folders[emptyPrestazione.type.id]=folderPrestazioni;
	folders[emptytpxp.type.id]=folderTpxp;
	$.each(layout, function (row,cols){
	    $.each(cols,function(col,value){
	       if(value)layout[row][col]=value.toString();
	    });   
	});
	
	$.each(elements,function(idx,element){
	   elements[idx]=prepareElementForPost(element);
	});
	
	folders=prepareElementForPost(folders);
	var grid=$.extend(true,{},{"layout":layout,"elements":elements,"folders":folders,"coordinates":coordinates});
	var data={"grid":JSON.stringify(grid)};
	return $.ajax({
	        		method:'POST',
	        		url:'../../rest/documents/updateGrid',
	        		data:data
	        });
}
function prepareTargetForm(open){
    var result='';
    var currTarget;
    if(open) {
        if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'])) {
            currTarget=docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'][0];
        }
        else{
            currTarget=docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'];
        }
        if(!currTarget)currTarget=1;
        $('#target').val(currTarget);
    }
    else{
       currTarget=$('#target').val();
    }
    currTarget+='';
   switch(currTarget){
       case '1':
        $.each(docObj.elements.tp,function(key,val){
            var value='';
            var label='';

            if($.isArray(val.metadata['Target_Prezzo'])) {
                value=val.metadata['Target_Prezzo'][0];
            }
            else{
                value=val.metadata['Target_Prezzo'];
            }
            if($.isArray(val.metadata['TimePoint_Descrizione'])) {
                label=val.metadata['TimePoint_Descrizione'][0];
            }
            else{
                label=val.metadata['TimePoint_Descrizione'];
            }
            if(value==undefined) value='';
            if(label==undefined) label='';
            result+=label+'<input type="text" value="'+value+'" name="target_tp_'+key+'" />';
        });
        break;
       case '2':
        var value='';

        if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
            value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0];
        }
        else{
            value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'];
        }

        if(value==undefined) value='';
        result='<input type="text" value="'+value+'" name="targetPrezzo" />';
        break;
       case '3':
        if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
            value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0];
        }
        else{
            value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'];
        }

        if(value==undefined) value='';
        result='<input type="text" value="'+value+'" name="targetPrezzo" />';
        break;
   }
   $('#target-form').html(result);
}
function applyTargetForm(){
    if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'])) {
        docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'][0]=$('#target').val();
    }
    else{
        docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget']=$('#target').val();
    }
    if($('#target').val()!='1'){
       $.each(docObj.elements.tp,function(key,val){
            if($.isArray(val.metadata['Target_Prezzo'])) {
                val.metadata['Target_Prezzo'][0]='';
            }
            else{
                val.metadata['Target_Prezzo']='';
            }
       });
    }

    if($('#target').val()!='2'){
       if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
           docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0]='';
       }
       else{
           docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente']='';
       }
    }
    if($('#target').val()!='3'){
        if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
            docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0]='';
        }
        else{
            docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio']='';
        }
    }
    switch($('#target').val()){
        case '1':
            $.each(docObj.elements.tp,function(key,val){
                if($.isArray(val.metadata['Target_Prezzo'])) {
                    val.metadata['Target_Prezzo'][0]=$('input[name=target_tp_'+key+']').val();
                }
                else{
                    val.metadata['Target_Prezzo']=$('input[name=target_tp_'+key+']').val();;
                }
            });
        break;
        case '2':
             if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
                 docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0]=$('input[name=targetPrezzo]').val();
             }
             else{
                 docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente']=$('input[name=targetPrezzo]').val();
             }
        break;
        case '3':
            if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
                docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0]=$('input[name=targetPrezzo]').val();
            }
            else{
                docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio']=$('input[name=targetPrezzo]').val();
            }
        break;
    }
}


function buildTpDescription(tp){
    var metadata=prepareMetadataForPost(tp.metadata);
    var ricoveri=new Array();
    ricoveri['Ricovero_Ordinario']='Ricovero ordinario';
    ricoveri['Ricovero_Straordinario']='Ricovero straordinario';
    ricoveri['Ricovero_Ambulatoriale']='Ricovero ambulatoriale';
    ricoveri['Ricovero_Telefonico']='Contatto telefonico';
    var ricoveriStr='';
    for(var curr in ricoveri){
        if(metadata[curr])ricoveriStr+=ricoveri[curr]+'\n';
    }
    var description=metadata['TimePoint_Descrizione']+'\n';
    if(metadata['TimePoint_Tempi']) description+='Tempi: '+metadata['TimePoint_Tempi']+'\n';
    if(metadata['TimePoint_DurataCiclo']) description+='Durata: '+metadata['TimePoint_DurataCiclo']+'\n';
    if(ricoveriStr) description+='Ricovero: '+ricoveriStr    ;

    return description;
}
function clone(src) {
	function mixin(dest, source, copyFunc) {
		var name, s, i, empty = {};
		for(name in source) {
			// the (!(name in empty) || empty[name] !== s) condition avoids copying properties in "source"
			// inherited from Object.prototype.  For example, if dest has a custom toString() method,
			// don't overwrite it with the toString() method that source inherited from Object.prototype
			s = source[name];
			if(!( name in dest) || (dest[name] !== s && (!( name in empty) || empty[name] !== s))) {
				dest[name] = copyFunc ? copyFunc(s) : s;
			}
		}
		return dest;
	}

	if(!src || typeof src != "object" || Object.prototype.toString.call(src) === "[object Function]") {
		// null, undefined, any non-object, or function
		return src;
		// anything
	}
	if(src.nodeType && "cloneNode" in src) {
		// DOM Node
		return src.cloneNode(true);
		// Node
	}
	if( src instanceof Date) {
		// Date
		return new Date(src.getTime());
		// Date
	}
	if( src instanceof RegExp) {
		// RegExp
		return new RegExp(src);
		// RegExp
	}
	var r, i, l;
	if( src instanceof Array) {
		// array
		r = [];
		for( i = 0, l = src.length; i < l; ++i) {
			if( i in src) {
				r.push(clone(src[i]));
			}
		}
		// we don't clone functions for performance reasons
		//      }else if(d.isFunction(src)){
		//          // function
		//          r = function(){ return src.apply(this, arguments); };
	} else {
		// generic objects
		r = src.constructor ? new src.constructor() : {};
	}
	return mixin(r, src, clone);

}

function loadData(data,costi) {
	$('#TPS').empty();
	$('#COSTS').empty();
	//var data = dataInput.slice(0);
	//console.log('qui');
	//data=removeEmpty(data);
	var waitingLiTP = '';
	var waitingLiCost = '';
	for(var i = 0; i < data.length; i++) {
		if(i == 0) {
			for(var k = 0; k < data[0].length; k++) {
				if(k != 0) {
					var label = data[0][k];
					if(label === undefined || label === null || label === '') {
						label = 'Timepoint non specificato';
						waitingLiTP += '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_col[]" value="' + k + '"></li>';
					} else {
						var li = waitingLiTP + '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_col[]" value="' + k + '"></li>';
						waitingLiTP = '';
						$('#TPS').append(li);
					}
				}
			}
		} else {
			var label = data[i][0];
			if(label === undefined || label === null || label === '') {
				label = 'Costo non specificato';
				waitingLiCost += '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_row[]" value="' + i + '"></li>';

			} else {
				var li = waitingLiCost + '<li class="ui-state-default"><span class="ui-icon ui-icon-arrowthick-2-n-s"></span>' + label + '<input type="hidden" name="position_row[]" value="' + i + '"></li>';
				waitingLiCost = '';
				$('#COSTS').append(li);
			}
		}
	}
	var handsontable = $('#example').data('handsontable');
	handsontable.loadData(data);
	if(costi && docObj.elements.tpxp.length>0){
	    costiInit=true;
        var migrated=migrateData(handsontable.getData());
        var handsontable2 =  $('#costi').data('handsontable');

        handsontable2.loadData(migrated);
        loadCosti();//carico i costi per studio e per paziente
	}
}

function migrateData(array) {
	var newArray = clone(array);
	var totCols = new Array();
	var totRows = new Array();
	var Total = 0;
	var lastCol = 0;
	var lastRow = 0;
	//totCols[0] = 'Totale per visita';
	//totRows[0] = 'Totale per prestazione';
	for(var i = 1; i < newArray.length; i++) {
		var totRow = 0;
		if(newArray[i][0] !== undefined && newArray[i][0] !== null && $.trim(newArray[i][0]) != '')
			lastRow = i;
		for(var k = 1; k < newArray[i].length; k++) {
			var value = $.trim(newArray[i][k]);
			if(value && value != 'false') {

				if(docObj.elements.tpxp2update[i] && docObj.elements.tpxp2update[i][k]){
				    newArray[i][k] = docObj.elements.tpxp2update[i][k].metadata['Costo_TransferPrice'];
				}
				if(totRows[i] === null || totRows[i] === undefined)
					totRows[i] = 0;
				if(!isNaN(newArray[i][k]))totRows[i] += parseFloat(newArray[i][k]);
				if(k > lastCol)
					lastCol = k;
				if(totCols[k] === null || totCols[k] === undefined)
					totCols[k] = 0;
                if(!isNaN(newArray[i][k]))totCols[k] += parseFloat(newArray[i][k]);

			} else {
				newArray[i][k] = "";
			}
		}

	}
	/*lastCol = lastCol + 1;
	lastRow = lastRow + 1;
	for(var z = 0; z < lastRow; z++) {
		newArray[z][lastCol] = totRows[z];
		if(!isNaN(totRows[z]))
			Total += totRows[z];
	}
	totCols[lastCol] = Total;
	newArray[lastRow] = totCols;  */
	return newArray;
}

function mergeData(preArray,array) {
    var newArray = clone(array);
    var oldArray = clone(preArray);
    var totCols = new Array();
    var totRows = new Array();
    var Total = 0;
    var lastCol = 0;
    var lastRow = 0;
    totCols[0] = 'Totale per visita';
    totRows[0] = 'Totale per prestazione';
    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;
        if(newArray[i][0] !== undefined && newArray[i][0] !== null && $.trim(newArray[i][0]) != '')
            lastRow = i;
        for(var k = 1; k < newArray[i].length; k++) {
            var value = $.trim(newArray[i][k]);
            if(value && value != 'false') {
                newArray[i][k] = "0";
                if(totRows[i] === null || totRows[i] === undefined)
                    totRows[i] = 0;
                if(!isNaN(newArray[i][k]))totRows[i] += parseFloat(newArray[i][k]);
                if(k > lastCol)
                    lastCol = k;
                if(totCols[k] === null || totCols[k] === undefined)
                    totCols[k] = 0;
                if(!isNaN(newArray[i][k]))totCols[k] += parseFloat(newArray[i][k]);

            } else {
                newArray[i][k] = "";
            }
        }

    }
    lastCol = lastCol + 1;
    lastRow = lastRow + 1;
    for(var z = 0; z < lastRow; z++) {
        newArray[z][lastCol] = totRows[z];
        if(!isNaN(totRows[z]))
            Total += totRows[z];
    }
    totCols[lastCol] = Total;
    newArray[lastRow] = totCols;
    return newArray;
}

function totaleSSN(){
    var tot=0;
    $.each(docObj.elements.tpxp2update,function(aKey,aVal){
        if(aVal) {
          $.each(aVal,function(key,val){
                if(val && val.metadata && val.metadata['Rimborso_Rimborsabilita']){
                    if(($.isArray(val.metadata['Rimborso_Rimborsabilita']) && val.metadata['Rimborso_Rimborsabilita'][0]==2) || val.metadata['Rimborso_Rimborsabilita']==2){
                        if($.isArray(val.metadata['tp-p_Prestazione'])){
                           if($.isArray(docObj.elements.prestazioni[val.metadata['tp-p_Prestazione'][0]].metadata['Base_Nome'])){
                                var transfer=tariffarioSSN[docObj.elements.prestazioni[val.metadata['tp-p_Prestazione'][0]].metadata['Base_Nome'][0]];
                           }
                           else{
                                var transfer=tariffarioSSN[docObj.elements.prestazioni[val.metadata['tp-p_Prestazione'][0]].metadata['Base_Nome']];
                           }
                        }
                        else{
                           var transfer=tariffarioSSN[val.metadata['tp-p_Prestazione']];
                        }
                        tot+=parseFloat(transfer);
                    }
                }
           });
        }
    });
    tot=tot.toFixed(2);
}

function mostraTotCTC(totFlow,totFlowCTC,totTip1,totTip1CTC,totTip2,totTip2CTC  ,totTip3,totTip3CTC,totTip4,totTip4CTC  ,totTip5,totTip5CTC){
    console.log(arguments);
     $('#table-tot tbody').empty();
     if(isNaN(totTip1)){
         totTip1=0;
         totTip1CTC=0;
     }
    if(isNaN(totTip2)){
        totTip2=0;
        totTip2CTC=0;
    }
    if(isNaN(totTip3)){
         totTip3=0;
         totTip3CTC=0;
     }
    if(isNaN(totTip4)){
        totTip4=0;
        totTip4CTC=0;
    }
    if(isNaN(totTip5)){
         totTip5=0;
         totTip5CTC=0;
     }

     var totPat=parseFloat(totFlow) +  parseFloat(totTip1) +  parseFloat(totTip3);
     var totPatCTC=parseFloat(totFlowCTC) +  parseFloat(totTip1CTC) +  parseFloat(totTip3CTC);

    totalePaziente=totPat;

     if(pazienti>0){
         var totStudio= (totPat*pazienti)+parseFloat(totTip2)+parseFloat(totTip4);
         var totStudioCTC= (totPatCTC*pazienti)+parseFloat(totTip2CTC)+parseFloat(totTip4CTC);
         totStudioCTC=totStudioCTC.toFixed(2);
         totaleStudio= totStudio;
     }
     else{
         var totStudio= 'Definire il numero di pazienti';
         var totStudioCTC= 'Definire il numero di pazienti';
     }
     var html='';

         html+="<tr><td>Budget totale per paziente</td><td>"+totPat+"</td><td>"+totPatCTC+"</td></tr>";
         html+="<tr><td>Budget totale per studio</td><td>"+totStudio+"</td><td>"+totStudioCTC+"</td></tr>";
         //html+="<tr><td>Totale SSN</td><td>"+totaleSSN()+"</td><td>N.A.</td></tr>";

    $('#table-tot tbody').html(html);
}

function rimuoviTotali(){
    var handsontable2 =  $('#costi').data('handsontable');
    var array=handsontable2.getData();
    var newArray = clone(array);
    var totCols = new Array();
    var totRows = new Array();
    var Total = 0;
    var lastCol = 0;
    var lastRow = 0;
    var lastColFound=false;
    var lastRowFound=false;
    totCols[0] = 'Totale per visita';
    totRows[0] = 'Totale per prestazione';
    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;
        if(newArray[i][0] == 'Totale per visita')  {
            lastRowFound=true;
            lastRow = i;
        }
        for(var k = 1; k < newArray[i].length; k++) {
            var value = $.trim(newArray[i][k]);
            if((k<lastCol || lastCol==0) && (i<lastRow || lastRow==0)){
                if(value && value != 'false') {

                    if(newArray[0][k]=='Totale per prestazione')  {
                        lastColFound = true;
                        lastCol = k;
                        continue;
                    }

                }
            }
        }


    }
    //lastCol = lastCol + 1;
    //lastRow = lastRow + 1;
    if(lastColFound){
        for(var z = 0; z < newArray.length; z++) {
            if(newArray[z][lastCol])newArray[z][lastCol] = '';
             if(newArray[z][lastCol+1])newArray[z][lastCol+1] = '';

        }
    }
    if(lastRowFound){
        newArray[lastRow] = new Array();
        newArray[lastRow+1] = new Array();
    }
    handsontable2.loadData(newArray);
    return true;
}

function cleanCost(element){
   $.each(element.metadata,function(key,val){
      if(key.match(/^costo_/i)){
        if($.isArray(val)){
            val[0]='';
        }else{
          element.metadata[key]='';
        }
      }
   });
   $.axmr.guid(element,undefined,'');
}



function calcolaTotali(){
    //funzione che aggiunge totali nel tab di budget
    var handsontable2 =  $('#costi').data('handsontable');
    var handsontable1 =  $('#example').data('handsontable');
    var array=handsontable1.getData();
    var newArray = clone(array);
    var totCols = new Array();
    var totRows = new Array();
    var Total = 0;
    var lastCol = 0;
    var lastRow = 0;
    var lastRowFound=false;
    var lastColFound=false;
    markup=0;
    if(docObj.elements.budgetStudio.metadata)markup=docObj.elements.budgetStudio.metadata['BudgetCTC_Markup'];
    pazienti=docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'];
    elementToForm(docObj.elements.budgetStudio,'dialog-form-CTC');
    elementToForm(docObj.elements.budgetStudio,'dialog-form-n-pat');
    totCols[0] = 'Totale per visita';
    totRows[0] = 'Totale per prestazione';
    for(var i = 1; i < newArray.length; i++) {
        var totRow = 0;
        if(newArray[i][0] == 'Totale per visita'){
            lastRow = i;
            lastRowFound=true;
        }
        for(var k = 1; k < newArray[i].length; k++) {

            var currElement=$.axmr.guid(newArray[i][k]);
            var value = $.trim($.axmr.label(newArray[i][k],2));

            if((k<lastCol || lastCol==0) && (i<lastRow || lastRow==0)){
                if(value && value != 'false') {
                    if(currElement && getDato(currElement.metadata['Rimborso_Rimborsabilita'])=='2') {
                       cleanCost(currElement);

                    }

                    if(totRows[i] === null || totRows[i] === undefined)
                        totRows[i] = 0;
                    if(newArray[0][k]=='Totale per prestazione')  {
                        lastCol = k;
                        lastColFound=true;
                        continue;
                    }
                    if(!isNaN(value))totRows[i] += parseFloat(value);

                    if(totCols[k] === null || totCols[k] === undefined)
                        totCols[k] = 0;
                    if(!isNaN(parseFloat(value)))totCols[k] += parseFloat(value);
                }
            }
        }


    }
    if(!lastRowFound){
        for(var ii = 1; ii < newArray.length; ii++){
            var currLabel=$.trim($.axmr.label(newArray[ii][0]));
            if (newArray[ii+1] && newArray[ii+1][0])var currLabel2=$.trim($.axmr.label(newArray[ii+1][0]));
            else{
               var currLabel2='';
            }
            if( currLabel!='' && currLabel2=='') {
                lastRow=ii+1;
            }
        }
    }
    if(!lastColFound){
        for(var kk = 1; kk < newArray[0].length; kk++){
             var currLabel=$.trim($.axmr.label(newArray[0][kk]));
             if(newArray[0] && newArray[0][kk+1])var currLabel2=$.trim($.axmr.label(newArray[0][kk+1]));
             else{
                var currLabel2='';
             }
             if(currLabel!='' && currLabel2=='') {
                lastCol=kk+1;
             }
        }
    }
    //lastCol = lastCol + 1;
    //lastRow = lastRow + 1;

    for(var z = 0; z < lastRow; z++) {
        newArray[z][lastCol] = totRows[z];
        if(!isNaN(totRows[z]))
            Total += totRows[z];
    }

    totCols[lastCol] = Total;
    newArray[lastRow] = totCols;

    markup=parseFloat(markup);
    if(markup>0 && budgetCTC){

        newArray[0][lastCol+1] ='Valore CTC';
        newArray[lastRow+1][0] ='Valore CTC';

        for (var ii=1;ii<lastRow;ii++){
            if(newArray[ii][lastCol]>0)newArray[ii][lastCol+1] = (newArray[ii][lastCol]*((100+markup)/100)).toFixed(2);
        }
        for (var kk=1;kk<lastCol;kk++){
            if(newArray[lastRow][kk]>0)newArray[lastRow+1][kk] = (newArray[lastRow][kk]*((100+markup)/100)).toFixed(2);
        }
        if(newArray[lastRow][lastCol]>0){
             var totFlow=  newArray[lastRow][lastCol];
             var totFlowCTC=newArray[lastRow][lastCol+1]=newArray[lastRow+1][lastCol]= (newArray[lastRow][lastCol]*((100+markup)/100)).toFixed(2);
        }
        else{
            var totFlow=  0;
            var totFlowCTC=0;
        }
        var totTip=new Array();
        var totTipCTC=new Array();
        for(var tip=1;tip<=5;tip++){
            var tot=totTip[tip]=parseFloat($('#tot_costi_'+tip).html());

            $('#costo-ctc-mu-'+tip).remove();
            if(tot>0 && tip!=5){

                var totCTC=(totTipCTC[tip]=tot*((100+markup)/100)).toFixed(2);
                $('#costs-'+tip+' tbody').append("<tr id='costo-ctc-mu-"+tip+"'>" + "<td>Totale CTC</td>" + "<td>" + totCTC + "</td><td></td>" + "</tr>");
            } else{
                totTipCTC[tip]=tot;
            }
        }
    } else{
        newArray[0][lastCol+1] ='';
        newArray[lastRow+1][0] ='';

        for (var ii=1;ii<lastRow;ii++){
            if(newArray[ii][lastCol]>0)newArray[ii][lastCol+1] = '';
        }
        for (var kk=1;kk<lastCol;kk++){
            if(newArray[lastRow][kk]>0)newArray[lastRow+1][kk] = '';
        }
        if(newArray[lastRow][lastCol]>0){
            newArray[lastRow][lastCol+1]=newArray[lastRow+1][lastCol]= '';
        }
        var totTip=new Array();
        var totTipCTC=new Array();
        for(var tip=1;tip<=5;tip++){
            $('#costo-ctc-mu-'+tip).remove();
            totTip[tip]=totTipCTC[tip]=parseFloat($('#tot_costi_'+tip).html());
        }
        var totFlowCTC,totFlow;
        totFlowCTC=totFlow=newArray[lastRow][lastCol];
    }
    mostraTotCTC((parseFloat(totFlow)).toFixed(2),(parseFloat(totFlowCTC)).toFixed(2),(parseFloat(totTip[1])).toFixed(2),(parseFloat(totTipCTC[1])).toFixed(2),(parseFloat(totTip[2])).toFixed(2),(parseFloat(totTipCTC[2])).toFixed(2)  ,(parseFloat(totTip[3])).toFixed(2),(parseFloat(totTipCTC[3])).toFixed(2)  ,(parseFloat(totTip[4])).toFixed(2),(parseFloat(totTipCTC[4])).toFixed(2)  ,(parseFloat(totTip[5])).toFixed(2),(parseFloat(totTipCTC[5])).toFixed(2));
    var currTarget='';
    if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'])) {
        currTarget=docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'][0];
    }
    else{
        currTarget=docObj.elements.budgetStudio.metadata['BudgetCTC_TipoTarget'];
    }
    if(currTarget){
        currTarget+='';
        var targetTot=0;
        var value=0;
        var confrontValue=0;
        var advisedMarkup=0;
        var tipologia='';
        switch($('#target').val()){
            case '1':
            tipologia='Per visita';
                $.each(docObj.elements.tp,function(key,val){
                    if($.isArray(val.metadata['Target_Prezzo'])) {
                        value=val.metadata['Target_Prezzo'][0];
                    }
                    else{
                        value=val.metadata['Target_Prezzo'];
                    }
                    if(!isNaN(parseFloat(value)))targetTot+=parseFloat(value);
                });
                confrontValue=Total;
            break;
            case '2':
                tipologia='Per paziente';
                if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'])) {
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'][0];
                }
                else{
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetPaziente'];
                }
                targetTot=value;
                confrontValue=totalePaziente;
            break;
            case '3':
                tipologia='Per studio';
                if($.isArray(docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'])) {
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'][0];
                }
                else{
                    value=docObj.elements.budgetStudio.metadata['BudgetCTC_TargetStudio'];
                }
                if(!isNaN(parseFloat(value)))targetTot=parseFloat(value);
                confrontValue=totaleStudio;
            break;
        }
        advisedMarkup=(targetTot-confrontValue)*100/confrontValue;
        if(!isNaN(targetTot) && !isNaN(advisedMarkup)){
            var rowMarkup='';
            rowMarkup='<tr><td>'+tipologia+'</td><td>'+targetTot+'</td><td>'+confrontValue+'</td><td>'+advisedMarkup.toFixed(2)+'</td></tr>';
            $('#table-advised-markup tbody').html(rowMarkup);
        }
    }
    handsontable2.loadData(newArray);
    return newArray;
}

function initPreventivo(array){
	var newArray = clone(array);
	var totCols = new Array();
	var totRows = new Array();
}
function  deletePxp(idx){
   docObj.elements.pxp2delete[docObj.elements.pxp2delete.length]=$.extend(true,{},docObj.elements.pxp[idx]);
   delete docObj.elements.pxp[idx];
   updateListaCosti(1);
   calcolaTotali();
}
function  deletePxs(idx){
   docObj.elements.pxs2delete[docObj.elements.pxs2delete.length]=$.extend(true,{},docObj.elements.pxs[idx]);
   delete docObj.elements.pxs[idx];
   updateListaCosti(2);
   calcolaTotali();
}



function  deletePxpCTC(idx){
   docObj.elements.pxp2delete[docObj.elements.pxp2delete.length]=$.extend(true,{},docObj.elements.pxpCTC[idx]);
   delete docObj.elements.pxpCTC[idx];
   updateListaCosti(3);
   calcolaTotali();
}

function  deletePxsCTC(idx){
   docObj.elements.pxs2delete[docObj.elements.pxs2delete.length]=$.extend(true,{},docObj.elements.pxsCTC[idx]);
   delete docObj.elements.pxsCTC[idx];
   updateListaCosti(4);
   calcolaTotali();
}

function  deletePassthroughCTC(idx){
   docObj.elements.pxs2delete[docObj.elements.pxs2delete.length]=$.extend(true,{},docObj.elements.passthroughCTC[idx]);
   delete docObj.elements.passthroughCTC[idx];
   updateListaCosti(5);
   calcolaTotali();
}


function addCosto(descrizione,tipologia,transfer,idx){
    if(tipologia==1){
        if(idx==undefined){
            var idx=docObj.elements.pxp.length;
            docObj.elements.pxp[idx]=$.extend(true,{},emptyPrestazioneXPaziente);
            docObj.elements.pxp[idx]=formToElement('dialog-form',docObj.elements.pxp[idx]);
        }

        var remove="deletePxp("+idx+");";
    }
    else if(tipologia==2){
        if(idx==undefined){
            var idx=docObj.elements.pxs.length;
            docObj.elements.pxs[idx]=$.extend(true,{},emptyPrestazioneXStudio);
            docObj.elements.pxs[idx]=formToElement('dialog-form',docObj.elements.pxs[idx]);
        }
        var remove="deletePxs("+idx+");";
    }
    else if(tipologia==3){
        if(idx==undefined){
            var idx=docObj.elements.pxpCTC.length;
            docObj.elements.pxpCTC[idx]=$.extend(true,{},emptyPrestazioneXPaziente);
            docObj.elements.pxpCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.pxpCTC[idx]);
        }
        var remove="deletePxpCTC("+idx+");";
    }
    else if(tipologia==4){
         if(idx==undefined){
             var idx=docObj.elements.pxsCTC.length;
             docObj.elements.pxsCTC[idx]=$.extend(true,{},emptyPrestazioneXStudio);
             docObj.elements.pxsCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.pxsCTC[idx]);
         }
         var remove="deletePxsCTC("+idx+");";
    }
    else if(tipologia==5){
       if(idx==undefined){
            var idx=docObj.elements.passthroughCTC.length;
            docObj.elements.passthroughCTC[idx]=$.extend(true,{},emptyPrestazioneXStudio);
            docObj.elements.passthroughCTC[idx]=formToElement('dialog-form-cost-2',docObj.elements.passthroughCTC[idx]);
        }
        var remove="deletePassthroughCTC("+idx+");";
    }
    var id="#costs-" + tipologia ;
    $("#costo-ctc-mu-"+tipologia).remove();
    $(id+" tbody tr").last().remove();
    $(id + " tbody").append("<tr>" + "<td>" + descrizione + "</td>" + "<td>" + transfer + "</td><td><a href='#' onclick=\" $(this).closest('tr').remove();"+remove+"return false;\">X</a></td>" + "</tr>");
    var tot=0;
    $(id+" tbody tr td:nth-child(2)").each(function(){
        console.log($(this));
        tot+=parseFloat($(this).html());
    });
    tot=tot.toFixed(2);
    $(id + " tbody").append("<tr>" + "<td>Totale</td>" + "<td id='tot_costi_"+tipologia+"'>" + tot + "</td><td></td>" + "</tr>");


    calcolaTotali();

}

function updateListaCosti(tipologia){
     var id="#costs-" + tipologia ;
     $("#costo-ctc-mu-"+tipologia).remove();
     $(id+" tbody tr").last().remove();
     var tot=0;
     $(id+" tbody tr td:nth-child(2)").each(function(){
         console.log($(this));
         tot+=parseFloat($(this).html());
     });
     tot=tot.toFixed(2);
     $(id + " tbody").append("<tr>" + "<td>Totale</td>" + "<td id='tot_costi_"+tipologia+"'>" + tot + "</td><td></td>" + "</tr>");

}

function loadCosti(){
    $.each(docObj.elements.pxp,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],1,element.metadata['Costo_TransferPrice'][0],i);
        }
    });
    $.each(docObj.elements.pxs,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],2,element.metadata['Costo_TransferPrice'][0],i);
        }
    });
    $.each(docObj.elements.pxpCTC,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],3,element.metadata['Costo_TransferPrice'][0],i);
        }
    });
    $.each(docObj.elements.pxsCTC,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],4,element.metadata['Costo_TransferPrice'][0],i);
        }
    });
    $.each(docObj.elements.passthroughCTC,function(i,element){
        if(element.metadata['Base_Nome'] && element.metadata['Costo_TransferPrice']){
            addCosto(element.metadata['Base_Nome'][0],5,element.metadata['Costo_TransferPrice'][0],i);
        }
    });
    pazienti=docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'];
    $('#show-n-pat').html(pazienti);
    //updateListaCosti(1);

    //updateListaCosti(2);

}



$(function() {
	var tipologia = $("#tipologia"), descrizione = $("#descrizione"), costo = $("#costo-costo"), markupCosto =  $("#markup-costo"), transfer =  $("#transfer-costo"), allFields = $([]).add(tipologia).add(descrizione).add(costo), tips = $(".validateTips");
	function updateTips(t) {
		tips.text(t).addClass("ui-state-highlight");
		setTimeout(function() {
			tips.removeClass("ui-state-highlight", 1500);
		}, 500);
	}

	function checkLength(o, n, min, max) {
		if(o.val().length > max || o.val().length < min) {
			o.addClass("ui-state-error");
			updateTips("Length of " + n + " must be between " + min + " and " + max + ".");
			return false;
		} else {
			return true;
		}
	}

	function checkRegexp(o, regexp, n) {
		if(!(regexp.test(o.val()) )) {
			o.addClass("ui-state-error");
			updateTips(n);
			return false;
		} else {
			return true;
		}
	}
	
	function checkAll() {
		var result=true;
		for(var key in arguments){

			var o=arguments[key];
			if($.trim(o.val())=='' ) {
				o.addClass("ui-state-error");
				updateTips('Campo obbligatorio');
				result=false;
			} 
		}
		return result;
	}



	$("#dialog-form").dialog({
		autoOpen : false,
		height : 300,
		width : 350,
		modal : true,
		position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
		buttons : {
			"Aggiungi costo" : function() {
				var bValid = true;
				allFields.removeClass("ui-state-error");
				bValid = bValid && checkAll(tipologia,descrizione,costo);
				/*bValid = bValid && checkLength(name, "username", 3, 16);
				bValid = bValid && checkLength(email, "email", 6, 80);
				bValid = bValid && checkLength(password, "password", 5, 16);
				bValid = bValid && checkRegexp(name, /^[a-z]([0-9a-z_])+$/i, "Username may consist of a-z, 0-9, underscores, begin with a letter.");
				// From jquery.validate.js (by joern), contributed by Scott Gonzalez: http://projects.scottsplayground.com/email_address_validation/
				bValid = bValid && checkRegexp(email, /^((([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+(\.([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+)*)|((\x22)((((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(([\x01-\x08\x0b\x0c\x0e-\x1f\x7f]|\x21|[\x23-\x5b]|[\x5d-\x7e]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(\\([\x01-\x09\x0b\x0c\x0d-\x7f]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))))*(((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(\x22)))@((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?$/i, "eg. ui@jquery.com");
				bValid = bValid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Password field only allow : a-z 0-9");*/
				if(true) {
					addCosto(descrizione.val(),tipologia.val(),transfer.val());

					$(this).dialog("close");
				}
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
        open:function(){
            var that=this;
            var setTransfer=function(){
                if($(that).find('select[id^=unita-markup]').val()==2){
                    var costo=parseFloat($(that).find('input[id^=costo]').val()-0);
                    var aggiunta=costo * parseFloat($(that).find('input[id^=markup]').val()-0) / 100;
                    var value=costo+aggiunta;
                } else{
                    var value=parseFloat($(that).find('input[id^=costo]').val()-0)+parseFloat($(that).find('input[id^=markup]').val()-0);
                }
                $(that).find('input[id^=transfer]').val(value);
            };
            var setMarkup=function(){
                if($(that).find('input[id^=transfer]').val()>0 && $(that).find('input[id^=costo]').val()>0){
                    $(that).find('select[id^=unita-markup]').val(1);
                    var value=parseFloat($(that).find('input[id^=transfer]').val())-parseFloat($(that).find('input[id^=costo]').val());
                    $(that).find('input[id^=markup]').val(value);
                }
            };
            $(this).find('input[id^=costo]').off('change').on('change',setTransfer);
            $(this).find('input[id^=markup]').off('change').on('change',setTransfer);
            $(this).find('select[id^=unita-markup]').off('change').on('change',setTransfer);
            $(this).find('input[id^=transfer]').off('change').on('change',setMarkup);
        },
		close : function() {
			allFields.val("").removeClass("ui-state-error");
		}
	});
	$("#create-cost").button().click(function() {
		$("#dialog-form").dialog("open");
	});

    $("#dialog-form-cost-2").dialog({
    		autoOpen : false,
    		height : 300,
    		width : 350,
    		modal : true,
    		position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
    		buttons : {
    			"Aggiungi costo" : function() {
    				var bValid = true;
    				var tipologia = $("#tipologia2"), descrizione = $("#descrizione2"), costo = $("#costo2"), markupCosto = $("#markup-costo2"), transfer = $("#transfer-costo2"), allFields = $([]).add(tipologia).add(descrizione).add(costo), tips = $(".validateTips");

    				allFields.removeClass("ui-state-error");
    				bValid = bValid && checkAll(tipologia,descrizione,costo);
    				/*bValid = bValid && checkLength(name, "username", 3, 16);
    				bValid = bValid && checkLength(email, "email", 6, 80);
    				bValid = bValid && checkLength(password, "password", 5, 16);
    				bValid = bValid && checkRegexp(name, /^[a-z]([0-9a-z_])+$/i, "Username may consist of a-z, 0-9, underscores, begin with a letter.");
    				// From jquery.validate.js (by joern), contributed by Scott Gonzalez: http://projects.scottsplayground.com/email_address_validation/
    				bValid = bValid && checkRegexp(email, /^((([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+(\.([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+)*)|((\x22)((((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(([\x01-\x08\x0b\x0c\x0e-\x1f\x7f]|\x21|[\x23-\x5b]|[\x5d-\x7e]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(\\([\x01-\x09\x0b\x0c\x0d-\x7f]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))))*(((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(\x22)))@((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?$/i, "eg. ui@jquery.com");
    				bValid = bValid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Password field only allow : a-z 0-9");*/
    				if(true) {
    					addCosto(descrizione.val(),tipologia.val(),transfer.val());

    					$(this).dialog("close");
    				}
    			},
    			Cancel : function() {
    				$(this).dialog("close");
    			}
    		},
            open:function(){
                var that=this;
                var setTransfer=function(){
                    if($(that).find('select[id^=unita-markup]').val()==2){
                        var costo=parseFloat($(that).find('input[id^=costo]').val()-0);
                        var aggiunta=costo * parseFloat($(that).find('input[id^=markup]').val()-0) / 100;
                        var value=costo+aggiunta;
                    } else{
                        var value=parseFloat($(that).find('input[id^=costo]').val()-0)+parseFloat($(that).find('input[id^=markup]').val()-0);
                    }
                    $(that).find('input[id^=transfer]').val(value);
                };
                var setMarkup=function(){
                    if($(that).find('input[id^=transfer]').val()>0 && $(that).find('input[id^=costo]').val()>0){
                        $(that).find('select[id^=unita-markup]').val(1);
                        var value=parseFloat($(that).find('input[id^=transfer]').val())-parseFloat($(that).find('input[id^=costo]').val());
                        $(that).find('input[id^=markup]').val(value);
                    }
                };
                $(this).find('input[id^=costo]').off('change').on('change',setTransfer);
                $(this).find('input[id^=markup]').off('change').on('change',setTransfer);
                $(this).find('select[id^=unita-markup]').off('change').on('change',setTransfer);
                $(this).find('input[id^=transfer]').off('change').on('change',setMarkup);
            },
    		close : function() {
    			allFields.val("").removeClass("ui-state-error");
    		}
    	});
    	$("#create-cost-2").button().click(function() {
    		$("#dialog-form-cost-2").dialog("open");
    	});
	function creaPrestazione(value,row){
	   var altro=$.extend(true,{},emptyVoce);
	   altro.metadata['PrestazioniDizionario_Descrizione'][0]= value;
	   saveElement(altro,folderDizionario);
	   $('#example').handsontable('setDataAtCell',row,0,value);

	}

	$("#prestazione-dialog").dialog({
    		autoOpen : false,
    		height : 300,
    		width : 350,
    		modal : true,
    		position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
    		buttons : {
    			"Nuova prestazione" : function() {
                    var newValue=$('#Altro_Descrizione').val();
                    if(dizPrestazioni[newValue]){
                       alert('Prestazione già presente nel dizionario');
                    }else{
                       creaPrestazione(newValue,rowAltro);
                    }

    			    $(this).dialog("close");

    			},
    			Cancel : function() {
    				$(this).dialog("close");
    			}
    		},
            open:function(){

            },
    		close : function() {
    			allFields.val("").removeClass("ui-state-error");
    		}
    	});


	$("#tp-dialog-form").dialog({
		autoOpen : false,
		height : 300,
		width : 350,
		modal : true,
		position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
		buttons : {
			"Aggiungi time point" : function() {
				
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
		}
	});
	$("#tp-button").button().click(function() {
        $("#tp-dialog-form").off('dialogopen').on('dialogopen',function(ev){
            ev=ev?ev:window.event;
            var that=this;
            $(this).find('input').each(function(){
                $(this).val('');
            });


            $(this).find('input[id^=titolo]').focus();

            $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
                var newData=new Array();
                var newValue='';
                $(that).find('input').each(function(){
                    newData[this.id]=$(this).val();
                    if(this.id.match(/^titolo/))newValue=$(this).val();
                });
                //console.log(newValue);


                var table=$('#example');
                //$(td).html($(that).find('input[id^=titolo]').val());
                $('#example').handsontable('deselectCell');
                if($(that).find('input[id=numero-tp]').val()>0)var index=  parseInt($(that).find('input[id=numero-tp]').val());
                else {
                    var index = parseInt($('#example').data('handsontable').getData()[0].length-10);
                }
                table.handsontable('alter','insert_col',(index-0));
                table.handsontable('setDataAtCell',0,(index-0),newValue);
                $("#tp-dialog-form").dialog('close');
            });


        });
		$("#tp-dialog-form").dialog("open");
	});
    $("#dialog-form-transfer").dialog({
        autoOpen : false,
        height : 300,
        width : 350,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons : {
            "Aggiungi transfer price" : function() {
                $(this).dialog("close");
            },
            Cancel : function() {
                $(this).dialog("close");
            }
        },
        close : function() {
            allFields.val("").removeClass("ui-state-error");
        }
    });
	$("#prestazione-dialog-form").dialog({
		autoOpen : false,
		height : 300,
		width : 350,
		modal : true,
		
		position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
		buttons : {
			"Aggiungi prestazione" : function() {
				
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
		}
	});
	$("#prestazione-button").button().click(function() {
		$("#prestazione-dialog-form").dialog("open");
	});

    $("#dialog-form-CTC").dialog({
        autoOpen : false,
        height : 300,
        width : 350,
        modal : true,

        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons : {
            "Aggiungi markup" : function() {

                //var totali=calcolaTotali();
                //var handsontable2 =  $('#costi').data('handsontable');

                //handsontable2.loadData(totali);
                formToElement('dialog-form-CTC',docObj.elements.budgetStudio);
                calcolaTotali();
                $(this).dialog("close");
            },
            Cancel : function() {
                $(this).dialog("close");
            }
        },
        close : function() {
            allFields.val("").removeClass("ui-state-error");
        }
    });
    $("#add-CTC").button().click(function() {
        elementToForm(docObj.elements.budgetStudio,'dialog-form-CTC');
        $("#dialog-form-CTC").dialog("open");
    });

    $("#dialog-form-n-pat").dialog({
        autoOpen : false,
        height : 300,
        width : 350,
        modal : true,

        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons : {
            "Applica" : function() {

                formToElement('dialog-form-n-pat',docObj.elements.budgetStudio);

                var totali=calcolaTotali();
                pazienti=docObj.elements.budgetStudio.metadata['BudgetCTC_NumeroPazienti'];
                $('#show-n-pat').html(pazienti);
                $(this).dialog("close");
            },
            Cancel : function() {
                $(this).dialog("close");
            }
        },
        close : function() {
            allFields.val("").removeClass("ui-state-error");
        }
    });
    $("#add-n-pat").button().click(function() {
        elementToForm(docObj.elements.budgetStudio,'dialog-form-n-pat');
        $("#dialog-form-n-pat").dialog("open");
    });

    $("#dialog-form-target").dialog({
        autoOpen : false,
        height : 300,
        width : 350,
        modal : true,
        position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
        buttons : {
            "Aggiungi target" : function() {
                    applyTargetForm();
                    calcolaTotali();
                    $(this).dialog("close");

            },
            Cancel : function() {
                $(this).dialog("close");
            }
        },
        open:function(){
            prepareTargetForm(true);
        }

    });
    $("#create-target").button().click(function() {
        $("#dialog-form-target").dialog("open");
    });


});



