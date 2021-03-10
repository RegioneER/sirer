<#include "../helpers/title.ftl"/>
<#assign budget=el />
<#assign center=el.getParent() />
<#include "../helpers/avanzamentoBudget.ftl"/>
    <div style="display: block">
   <br><br>
            <link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery.ui.base.css" />
        <!--link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery.ui.css" /-->
        <link rel="stylesheet" href="${baseUrl}/int/css/budget/jquery.handsontable.full.css" />
        <link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery-ui.css" />
        <link rel="stylesheet" href="${baseUrl}/int/css/budget/base.css" />
	<style>
		.ui-autocomplete.ui-menu{
			z-index:9999!important;
		}
			.handsontable td{
				font-size: 13px;
				font-weight:200;
				color:black!important;
			}
			#tabs ul{
				height: 41px!important;
			}
			#tabs li a{
				font-size: 125%;
			    
			    padding: 0.8em 5em;
			}
		input[type=text], select,option {
		    font-size: 1.2vw!important;
		    line-height: 1.3vw;
		   
		}
		#tp-dialog-form input[type=text], select,option {
		    font-size: 1vw!important;
		    line-height: 1.1vw;
		   
		}
		
		input[type=checkbox]{
			display:inline-block;
		}
		label{
			font-size:1.3vw;
			line-height:1.6vw;
		}
		#tp-dialog-form label{
			font-size:1.1vw;
			line-height:1.4vw;
		}
		.ui-dialog button, button.ui-button {
			font-size:1.3vw!important;
			}
		#tp-dialog-form .ui-dialog button, button.ui-button {
			font-size:1.1vw!important;
			}
	</style>
        <!--script  src="js/jquery.js"></script-->
        <script  src="/js/budget/jquery.handsontable.full.js"></script>
        <!--script src="/js/budget/ui/jquery-ui.js"></script>
        <script src="/js/budget/ui/jquery.ui.widget.js"></script>
        <script src="/js/budget/ui/jquery.ui.tabs.js"></script-->
        <script src="/js/budget/ui/jquery.ui.sortable.js"></script>
        <!--script  src="js/jcanvas.min.js"></script-->
        <script  src="/js/budget/kinetic.min.js"></script>
        <script  src="/js/budget/custom.js"></script>
        
		
		<script>
    
        loadingScreen("Caricamento in corso...", "${baseUrl}/int/images/loading.gif");
        
        var cache = {};
        function setRimborso(id,valore){
        	var myElement=$.axmr.guid(id);
        	myElement.metadata['Rimborso_Rimborsabilita'][0]=valore;
        	
        }
        function firstLine(testo){
        	testo=testo.replace(/(\n.*)*$/g,'');
        	return $.trim(testo);
        }
        function getDato(dato){
        	if($.isArray(dato)){
        		return dato[0];
        	}
        	else{
        		return dato;
        	}
        }
        
        function updateTips(t) {
        	var tips=$('.validateTips');
			tips.text(t).addClass("ui-state-highlight").show();
			tips.parent().animate({
                scrollTop : 10
            }, 500);
			setTimeout(function() {
				tips.removeClass("ui-state-highlight", 1500);
			}, 500);
		}
        var budgetCTC=false;
        function moveBudget(target){
        	if(target=='tabs-3'){
        		budgetCTC=true;
        	}
        	else{
        		budgetCTC=false;
        	}
	    	var handsontable1 =  $('#example').data('handsontable'); 
            var handsontable2 =  $('#costi').data('handsontable');   
            var preMigration= handsontable2.getData()
            if(costiInit || preMigration[1][0]!==null || preMigration[0][1]!==null){
            	//var migrated=mergeData(preMigration,handsontable1.getData());
            	//handsontable2.loadData(preMigration);
            	//$('#costi').handsontable('render');
            	calcolaTotali();
            }
            else{
            costiInit=true;
            	var migrated=migrateData(handsontable1.getData());
            	var handsontable2 =  $('#costi').data('handsontable');   
            
            	handsontable2.loadData(migrated);
            }
        	$('#clinico').prependTo('#'+target);
        	$('#global-pazienti').appendTo('#pazienti-'+target);
        	//rimuoviTotali();
        	//calcolaTotali();
        }
        var folderDizionario=84902;//dizionario delle prestazioni necessario per inserire nuove prestazioni in prod: 84902 in locale 3586
        var linkable=185015;//lista di elementi prestazioni da dizionario in prod:185015 in locale: 34
       /* var emptyFolderTimePoint={"id":"","type":{"id":"57","typeId":"FolderTimePoint"},"metadata":{"Base_Nome":["Timepoint"]},"title":"Timepoint"};
		var emptyFolderPrestazioni={"id":"","type":{"id":"58","typeId":"FolderPrestazioni"},"metadata":{"Base_Nome":["Prestazioni"]},"title":"Prestazioni"};
		var emptyFolderTpxp={"id":"","type":{"id":"59","typeId":"FolderTp-p"},"metadata":{"Base_Nome":["tpxp"]},"title":"tpxp"};
		var emptyTimePoint={"id":"","type":{"id":"62","typeId":"TimePoint"},"children":[],"metadata":{"TimePoint_Tempi":[""],"TimePoint_NumeroVisita":[""],"TimePoint_Note":[""],"TimePoint_Descrizione":[""],"TimePoint_DurataCiclo":[""],"TimePoint_NumeroPrestazioni":[""]},"title":""};
		var emptyPrestazione={"id":"","type":{"id":"63","typeId":"Prestazione"},"children":[],"metadata":{"Prestazioni_row":[""],"Base_Nome":[""],"Prestazioni_prestazione":[""]},"title":""};
		var emptytpxp={"id":"","type":{"id":"64","typeId":"tp-p"},"children":[],"metadata":{"Costo_MarkupCTC":[""],"Costo_Costo":[""],"tp-p_Prestazione":[""],"Costo_OffertaFinale":[""],"tp-p_TimePoint":[""]},"title":null};
*-/		
		var emptyPrestazione={"id":null,"type":{"id":"4","typeId":"Prestazione"},"children":null,"metadata":{"Tariffario_SSN":[""],"Prestazioni_row":[""],"Tariffario_Gemelli":[""],"Base_Nome":[""],"Prestazioni_prestazione":[],"Tariffario_ALPI":[""]},"title":""}
		var emptyTimePoint={"id":null,"type":{"id":"3","typeId":"TimePoint"},"children":null,"metadata":{"Ricovero_Straordinario":[""],"TimePoint_Tempi":[""],"TimePoint_NumeroVisita":[""],"TimePoint_Note":[""],"TimePoint_Descrizione":[""],"Ricovero_Telefonico":[""],"TimePoint_DurataCiclo":[""],"Ricovero_Ambulatoriale":[""],"Ricovero_Ordinario":[""],"TimePoint_NumeroPrestazioni":[""]},"title":""};
		var emptytpxp={"id":null,"type":{"id":"6","typeId":"tp-p"},"children":null,"metadata":{"Costo_MarkupCTC":[""],"Costo_OreUomo":[""],"Rimborso_ApprovatoDa":[""],"Costo_OreMacchina":[""],"tp-p_Prestazione":[],"Costo_Costo":[""],"Base_Nome":[""],"Costo_TransferPrice":[""],"Costo_OffertaSponsor":[""],"Rimborso_ApprovatoInData":[],"Costo_OffertaMinima":[""],"tp-p_TimePoint":[],"Costo_MarkupUnita":[""],"Rimborso_MandatoInApprovazioneDa":[""],"Costo_OffertaFinale":[""],"Rimborso_Rimborsabilita":[""],"Rimborso_MandatoInApprovazioneInData":[],"Costo_Markup":[""]},"title":""}
		var emptyFolderPXP={"id":null,"type":{"id":"16","typeId":"FolderPXP"},"children":null,"metadata":{"Base_Nome":[""]},"title":null};
		var emptyFolderPXS={"id":null,"type":{"id":"17","typeId":"FolderPXS"},"children":null,"metadata":{},"title":null};
		var emptyPrestazioneXPaziente={"id":null,"type":{"id":"14","typeId":"PrestazioneXPaziente"},"children":null,"metadata":{"Costo_MarkupCTC":[""],"Prestazione_Prestazione":[],"Prestazione_NomePrestazione":[""],"Costo_OffertaFinale":[""],"Costo_Costo":[""],"Base_Nome":[""],"Costo_OffertaSponsor":[""],"Costo_TransferPrice":[""],"Costo_OffertaMinima":[""],"Costo_Markup":[""],"Costo_MarkupUnita":[""],"Costo_OreMacchina":[""],"Prestazione_NumeroRipetizioni":[""]},"title":""};
		var emptyPrestazioneXStudio={"id":null,"type":{"id":"15","typeId":"PrestazioneXStudio"},"children":null,"metadata":{"Costo_MarkupCTC":[""],"Prestazione_Prestazione":[],"Prestazione_NomePrestazione":[""],"Costo_OffertaFinale":[""],"Costo_Costo":[""],"Base_Nome":[""],"Costo_OffertaSponsor":[""],"Costo_TransferPrice":[""],"Costo_OffertaMinima":[""],"Costo_Markup":[""],"Costo_MarkupUnita":[""],"Costo_OreMacchina":[""],"Prestazione_NumeroRipetizioni":[""]},"title":""};
        
        var emptyFolderBudgetStudio={"id":null,"type":{"id":"22","typeId":"BudgetStudio"},"children":null,"metadata":{"Base_Nome":[""]},"title":""};
		var emptyBudgetCTC={"id":null,"type":{"id":"23","typeId":"BudgetCTC"},"children":null,"metadata":{"BudgetCTC_NumeroPazienti":[""],"BudgetCTC_Markup":[""],"Base_Nome":[""]},"title":""};
		var emptyVoce={"id":null,"type":{"id":"8","typeId":"VocePrestazione"},"children":null,"metadata":{"PrestazioniDizionario_CodiceBranca3":[""],"PrestazioniDizionario_Descrizione":[""],"PrestazioniDizionario_CodiceBranca4":[""],"PrestazioniDizionario_CodiceBranca1":[""],"PrestazioniDizionario_CodiceBranca2":[""],"PrestazioniDizionario_Codice":[""],"PrestazioniDizionario_Tipo":[""],"PrestazioniDizionario_Nota":[""],"PrestazioniDizionario_TariffaALPI":[""],"PrestazioniDizionario_TariffaSSN":[""]},"title":""};
        var emptyFolderPXPCTC={"id":null,"type":{"id":"26","typeId":"FolderPXPCTC"},"children":null,"metadata":{"Base_Nome":[""]},"title":""};
        var emptyFolderPXSCTC={"id":null,"type":{"id":"27","typeId":"FolderPXSCTC"},"children":null,"metadata":{"Base_Nome":[""]},"title":""};
        var emptyFolderPassthroughCTC={"id":null,"type":{"id":"28","typeId":"FolderPassthroughCTC"},"children":null,"metadata":{"Base_Nome":[""]},"title":""};
  */      
        //confronta
        var empties=new Array();
        var emptiesTmp=new Array();
        //voce typeId in prod: 67 in locale : 8
        var emptyVoce={"id":null,"type":{"id":"67","typeId":"VocePrestazione"},"children":null,"metadata":{"PrestazioniDizionario_CodiceBranca3":[""],"PrestazioniDizionario_Descrizione":[""],"PrestazioniDizionario_CodiceBranca4":[""],"PrestazioniDizionario_CodiceBranca1":[""],"PrestazioniDizionario_CodiceBranca2":[""],"PrestazioniDizionario_Codice":[""],"PrestazioniDizionario_Tipo":[""],"PrestazioniDizionario_Nota":[""],"PrestazioniDizionario_TariffaALPI":[""],"PrestazioniDizionario_TariffaSSN":[""]},"title":""};
        <#list elType.getAllowedChilds() as myType>
		<#assign json=myType.getDummyJson() />
		empty${myType.typeId}=${json};
			<#list myType.getAllowedChilds() as childType>
				<#assign json=childType.getDummyJson() />
				empty${childType.typeId}=${json};
			</#list>
		</#list>
        
        emptiesTmp[emptiesTmp.length]=emptyFolderTimePoint;
        emptiesTmp[emptiesTmp.length]=emptyFolderPrestazioni;
        emptiesTmp[emptiesTmp.length]=emptyFolderTpxp;
        emptiesTmp[emptiesTmp.length]=emptyTimePoint;
        emptiesTmp[emptiesTmp.length]=emptyPrestazione;
        emptiesTmp[emptiesTmp.length]=emptytpxp;
        emptiesTmp[emptiesTmp.length]=emptyFolderPXP;
        emptiesTmp[emptiesTmp.length]=emptyFolderPXS;
        emptiesTmp[emptiesTmp.length]=emptyPrestazioneXPaziente;
        emptiesTmp[emptiesTmp.length]=emptyPrestazioneXStudio;
        emptiesTmp[emptiesTmp.length]=emptyFolderBudgetStudio;
        emptiesTmp[emptiesTmp.length]=emptyBudgetCTC;
        emptiesTmp[emptiesTmp.length]=emptyVoce;
        emptiesTmp[emptiesTmp.length]=emptyFolderPXPCTC;
        emptiesTmp[emptiesTmp.length]=emptyFolderPXSCTC;
        emptiesTmp[emptiesTmp.length]=emptyFolderPassthroughCTC;
        
        $.each(emptiesTmp,function(ie,currEmpty){
        	empties[currEmpty.type.id]=currEmpty;
        });
        
        <#assign elementJson=model['element'].getElementJsonToString(userDetails) />
        var loadedElement=${elementJson};
        var docObj;
        var prepareForDelete=new Array();
        var pxp=new Array();
        var pxs=new Array();
        function alertError(){
        	alert('Errore nel caricamento');
        }
        function sortTp(a,b){
        	if(parseInt(getDato(a.metadata['TimePoint_col']))>parseInt(getDato(b.metadata['TimePoint_col']))){return 1;}
        	else if(parseInt(getDato(a.metadata['TimePoint_col']))<parseInt(getDato(b.metadata['TimePoint_col']))){return -1;}
        	else{
        		return 0;
        	}
        }
        function sortPrestazioni(a,b){
        	if(parseInt(getDato(a.metadata['Prestazioni_row']))>parseInt(getDato(b.metadata['Prestazioni_row']))){return 1;}
        	else if(parseInt(getDato(a.metadata['Prestazioni_row']))<parseInt(getDato(b.metadata['Prestazioni_row']))){return -1;}
        	else{
        		return 0;
        	}
        }
        
        function formToElement(form,element){
        	$('#'+form).find(':input').each(function (){
        		var label=$(this).attr('name');
        		//label=label.replace(/^[^_]*_/,'');
        		if(empties[element.type.id].metadata[label]!=undefined){
        			if($(this).attr('type')=='checkbox'){
        				if(this.checked) element.metadata[label]=1;//$(this).val(); risulta vuoto indagare come mai viene svuotato
        				else  element.metadata[label]='';
        			}
        			else{
        				element.metadata[label]=$(this).val();
        			}
        		}
        		else{
        		console.log(label);
        		console.log(empties[element.type.id].metadata[label]);
        		}
        	});
        	return element;
        }
        
        function elementToForm(element,form){
        	$('#'+form).find(':input').each(function (){
        		var label=$(this).attr('name');
        		//label=label.replace(/^[^_]*_/,'');
        		if($(this).attr('type')=='checkbox'){
        			if(getDato(element.metadata[label]))this.checked=true;
        			else this.checked=false;
        		}
        		else{
        			var dato=getDato(element.metadata[label]);
        			if(dato!==undefined && dato!==null)$(this).val(dato);
        			else if(element.metadata.hasOwnProperty(label)) $(this).val('');
        		}
        	});
        }
        
        function prepareMetadataForPost(inMetadata){

        	var metadata=$.extend(true,{},inMetadata);

        	$.each(metadata,function(key,value){
        		if($.isPlainObject(value[0])){
        			metadata[key]=value[0].id.toString();
        		}
        		else{
        			if($.isArray(value)){
        				if(value[0]===null || value[0]===undefined) metadata[key]="";
        				else metadata[key]=value[0].toString();
        			}else{
        				metadata[key]=value.toString();
        			}
        		}
        	});

        	return metadata;
        }
        function updateElement(element){
        	var metadata=prepareMetadataForPost(element.metadata);
        	
        	return $.ajax({
        		method:'POST',
        		url:'../../rest/documents/update/'+element.id,
        		data:metadata
        	});
        	
        }
        function preparePrestazione(prestazione,row){
        }
        function prepareTpxp(value,p,tp){
        	if(!value){
        		//non dovrei più entrare qui
        		console.log('non dovrei più entrare qui');
        			return;
        		}
        			
        	var myElement=$.extend(true,{},emptytpxp);
        	if(value){
        		myElement.metadata['tp-p_Checked']=1;
        		}
        	myElement.coordinates={x:tp,y:p};
        	return myElement;
        	
        }
        function saveElement(element,parent){
        	if(element.id){
        		return updateElement(element);
        	}
        	else{
        		var metadata=prepareMetadataForPost(element.metadata);
        		metadata.parentId=parent;
	        	return $.ajax({
	        		method:'POST',
	        		url:'../../rest/documents/save/'+element.type.id,
	        		data:metadata
	        	}).done(function (data){
	        		element.id=data.ret;
	        	});
	        	 
	        }
        }
        function findElement(element,parent){
    	
    		var metadata=prepareMetadataForPost(element.metadata);
    		metadata.parentId=parent;
        	return $.ajax({
        		method:'POST',
        		url:'../../rest/documents/searchByExample/'+element.type.id,
        		data:metadata
        	}).done(function(){console.log('Found!!!');}).fail(function(){console.log('error',element);});
        	 
       
        }
        function deleteElement(element){
        	if(element && element.id)
        	return $.ajax({
        		url:'../../rest/documents/delete/'+element.id,
        		data:element.metadata
        	}).done(function(){console.log('DELETED');}).fail(alertError);
        }
        /*function saveTpxp(updatedDocObj){
			var actions=new Array();
        	$.each(docObj.elements.tpxp2delete,function(iRow,row){
        		if($.isArray(row)){
	        		$.each(row,function(kCol,col){
	        			if($.isPlainObject(col)){
	        				deleteElement(col);
	        			}
	        		});
        		}
        	});
        	
        	$.each(docObj.elements.tpxp2update,function(iRow,row){
        		if($.isArray(row)){
	        		$.each(row,function(kCol,col){
	        			if($.isPlainObject(col)){
	        				if(!$.isPlainObject(col.metadata['tp-p_TimePoint'])){
	        				console.log(col.metadata['tp-p_TimePoint']);
	        					col.metadata['tp-p_TimePoint']=updatedDocObj.elements.tp[col.metadata['tp-p_TimePoint']-1]['id'];
	        				}
	        				if(!$.isPlainObject(col.metadata['tp-p_Prestazione'])){
	        				
	        					col.metadata['tp-p_Prestazione']=updatedDocObj.elements.prestazioni[col.metadata['tp-p_Prestazione']-1]['id'];
	        				}
	        				console.log("rimborso_"+iRow+"_"+kCol+"");
	        				
	        				if($("input[id^=rimborso_"+iRow+"_"+kCol+"]").size()>0){
	        					col.metadata['Rimborso_Rimborsabilita']=$("input[id^=rimborso_"+iRow+"_"+kCol+"]").val();
	        				}
	        				actions[actions.length]=saveElement(col,folderTpxp);
	        			}
	        		});
        		}
        	});
        	setTimeout(function(){location.reload();},2000);
        }*/
        function saveAll(){
        	//salvo tutto
        	loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        	var queue=$.when({start:true});
        	//salvo la griglia
        	/*
			queue=$.when(queue).then(function(data){
				
				return saveGrid()
			});   
			*/
        	//salvo prestazioni per paziente di tipo clinico
        	$.each(docObj.elements.pxp,function(i,pxp){
        		if(pxp){
        			queue=$.when(queue).then(function(data){
        				return saveElement(pxp,folderPxp);
        			});
        		}
        	});
        	//salvo prestazioni per studio di tipo clinico
        	$.each(docObj.elements.pxs,function(i,pxs){
        		if(pxs){
        			queue=$.when(queue).then(function(data){
        				return saveElement(pxs,folderPxs);
        			});
        		}
        	});
        	//salvo budget studio
        	/*if(docObj.elements.budgetStudio && $.isPlainObject(docObj.elements.budgetStudio)){
        		queue=$.when(queue).then(function(data){
        			return saveElement(docObj.elements.budgetStudio,folderBudgetStudio);
        		});
        	}*/
        	//cancello pxp
        	$.each(docObj.elements.pxp2delete,function(iRow,row){
       			if($.isPlainObject(row)){
       				queue=$.when(queue).then(function(data){
    					return deleteElement(row);
    				});
    			}		
        	});
        	//cancello pxs
        	$.each(docObj.elements.pxs2delete,function(iRow,row){
    			if($.isPlainObject(row)){
    				queue=$.when(queue).then(function(data){
    					return deleteElement(row);
    				});
    			}
        	});
		        				
        	$.when(queue).then(function(){location.reload(true);});
        	return;
        	//setTimeout(function(){var newDoc=new myElementJSON(${model['element'].id},saveTpxp)},2000);
        }
       function sortTpxp(tpxp){
        console.log(tpxp);
        	var result=new Array();
        	for(var i=0;i<tpxp.length;i++){
        		var currChild=tpxp[i];
        		if(currChild.metadata['tp-p_Prestazione'][0]){ 
        		if(!$.isArray(result[currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row']])){
        			result[currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row']]=new Array();
        		}
        		if(currChild.metadata['tp-p_TimePoint'][0]){
        			result[currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row']][currChild.metadata['tp-p_TimePoint'][0].metadata['TimePoint_NumeroVisita']]=currChild;
        			currChild.metadata['tp-p_Prestazione']=currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row'];
        			currChild.metadata['tp-p_TimePoint']=currChild.metadata['tp-p_TimePoint'][0].metadata['TimePoint_NumeroVisita'];
        		}
        		else{
        		
        			if(docObj && docObj.elements && docObj.elements.tpxp2delete)docObj.elements.tpxp2delete[docObj.elements.tpxp2delete.length]=currChild;
        			continue;
        		}
        		}
        		else{
        			continue;
        		}
        		
        	}
        	console.log(result);
        	return result;
        }
        /*function sortTpxp2update(tpxp){
        	var result=new Array();
        	for(var i=0;i<tpxp.length;i++){
        		var currChild=tpxp[i];
        		if(!$.isArray(result[currChild.metadata['tp-p_Prestazione'][0].id])){
        			result[currChild.metadata['tp-p_Prestazione'][0].id]=new Array();
        		}
        		result[currChild.metadata['tp-p_Prestazione'][0].id][currChild.metadata['tp-p_TimePoint'][0].id]=currChild;
        	}
        	return result;
        }*/
        function getDataFromObj(myObject){
        	var result=new Array();
        	var currRow=new Array();
    		currRow[0]='';
    		$.each(myObject.tp,function(k,currTp){
    			//currRow[k+1]=currTp.metadata['TimePoint_Descrizione'];
    			currRow[k+1]=$.axmr.guid(currTp,buildTpDescription(currTp));
    			currTp.coordinates={x:k+1,y:1};
    		});
    		result[0]=currRow;
        	$.each(myObject.prestazioni, function(i,currPrestazione){
        		var row=i+1;
        		currRow=new Array();
        		currRow[0]=$.axmr.guid(currPrestazione,getDato(currPrestazione.metadata['Prestazioni_prestazione']));
        		currPrestazione.coordinates={x:1,y:i+1};
        		for(var col=1;col<result[0].length;col++){
        			currRow[col]='';
        		}
        		result[row]=currRow;
        	});
        	$.each(myObject.tpxp, function(i,currTpxp){
        		
        		var prestaAssoc;
        		var tpAssoc;
        		if($.isPlainObject(getDato(currTpxp.metadata['tp-p_Prestazione']))) prestaAssoc=$.axmr.getById(getDato(currTpxp.metadata['tp-p_Prestazione'])['id']);
        		if($.isPlainObject(getDato(currTpxp.metadata['tp-p_TimePoint']))) tpAssoc=$.axmr.getById(getDato(currTpxp.metadata['tp-p_TimePoint'])['id']);
        		if(prestaAssoc && tpAssoc)result[prestaAssoc.coordinates.y][tpAssoc.coordinates.x]=$.axmr.guid(currTpxp,getDato(currTpxp.metadata['tp-p_Checked']),getDato(currTpxp.metadata['Costo_TransferPrice']));
        	});
        	return result;
        }
        
			var myElementJSON=function(id,callback){
			//tp:timepoint,tpxp:prestazione al timepoint x, pxp: prestazione per paziente, pxs; prestazione per lo studio
				this.elements={tp:[],prestazioni:[],tpxp:[],pxp:[],pxs:[],markup:0,tpxp2update:[],tpxp2delete:[],pxs2delete:[],pxp2delete:[],budgetStudio:[],pxpCTC:[],pxsCTC:[],passthroughCTC:[]};
				var instance=this;
				function parseElement(data){
						instance.elements.globalData=data;
					if(data.children && data.children.length>0){
							$.each(data.children,function(index,child){
								var type=child.type.typeId;
								
								switch(type){
									case 'FolderTimePoint':
										folderTp=child.id;
										instance.elements.tp=child.children;
										instance.elements.tp.sort(sortTp);
									break;
									case 'FolderPrestazioni':
										folderPrestazioni=child.id;
										instance.elements.prestazioni=child.children;
										instance.elements.prestazioni.sort(sortPrestazioni);
									break;
									case 'FolderTpxp':
										folderTpxp=child.id;
										instance.elements.tpxp=child.children;
										//instance.elements.tpxp2update=sortTpxp2update(child.children);
									break;
									case 'FolderPXP':
										folderPxp=child.id;
										instance.elements.pxp=child.children;
									break;
									case 'FolderPXS':
										folderPxs=child.id;
										instance.elements.pxs=child.children;
									break;
									case 'FolderBudgetStudio':
										folderBudgetStudio=child.id;
										
										if($.isArray(child.children) && child.children.length>0){
											instance.elements.budgetStudio=child.children[0];
										}
										else{
											instance.elements.budgetStudio=$.extend(true,{},emptyBudgetCTC);
										}
									break;
								}
							
							});
						}
						instance.elements.tpxp2update=$.extend(true,[],instance.elements.tpxp);
						var data=getDataFromObj(instance.elements);
						//var costi=getCostiFromObj(instance.elements);
						console.log(instance.elements);
						console.log(data);
	 				if(!callback)loadData(data,true,instance);
         				var checkFolders=false;
						if(folderTp==null){
			        		//saveElement(emptyFolderTimePoint,id);
			        		checkFolders=true;
			        	}
			        	if(folderPrestazioni==null){
			        		//saveElement(emptyFolderPrestazioni,id);
			        		checkFolders=true;
			        	}
			        	if(folderTpxp==null){
			        		//saveElement(emptyFolderTpxp,id);
			        		checkFolders=true;
			        	}
			        	if(folderPxp==null){
			        		//saveElement(emptyFolderPXP,id);
			        		checkFolders=true;
			        	}
			        	if(folderPxs==null){
			        		//saveElement(emptyFolderPXS,id);
			        		checkFolders=true;
			        	}
			        	if(folderBudgetStudio==null){
			        		//saveElement(emptyFolderBudgetStudio,id);
			        		instance.elements.budgetStudio=$.extend(true,{},emptyBudgetCTC);
			        		checkFolders=true;
			        	}
			        	if(checkFolders){
			        		setTimeout(function(){getFolders(id)},100);
			        	}
			        	if(callback) callback(instance);
			        	toggleLoadingScreen();
			        	setTimeout(function(){
							var hash = $.trim( window.location.hash );
							console.log(hash);
							if(hash)$('a[href$="'+hash+'"]').click();
							},100);
				}
				
				
				
				
				if(loadedElement){
					parseElement(loadedElement);
				}
				else{
					(function(){
						$.ajax({
							dataType: "json",
							url:'../../rest/documents/getElementJSON/'+id
						}).done(parseElement).fail(alertError);
				})();
				}
			}
			
			function getFolders(id,reload){
				if(!(folderTp!=null && folderPrestazioni!=null && folderTpxp!=null && folderPxp!=null && folderPxs!=null && folderBudgetStudio!=null)){
					$.ajax({
						dataType: "json",
						url:'../../rest/documents/getElementJSON/'+id
					}).done(function(data){
						if(data.children.length>0){
							$.each(data.children,function(index,child){
								var type=child.type.typeId;
								
								switch(type){
									case 'FolderTimePoint':
										folderTp=child.id;
										
									break;
									case 'FolderPrestazioni':
										folderPrestazioni=child.id;
										
									break;
									case 'FolderTpxp':
										folderTpxp=child.id;
										
									break;
									case 'FolderPXP':
										folderPxp=child.id;
									break;
									case 'FolderBudgetStudio':
										folderBudgetStudio=child.id;
									break;
									case 'FolderPXS':
										folderPxs=child.id;
									break;
									
								}
							
							});
						}
						setTimeout(function(){getFolders(id,true)},1000);
						if(reload) console.log('Please reload');
					});
					
				}
			}
			$(document).ready(
				function(){
					/*$.ajax({
					//prod: '${baseUrl}/app/rest/documents/getLinkableElements/185015'
				        url: '${baseUrl}/app/rest/documents/getLinkableElements/'+linkable,
				        data: {
				            term: ''
				        },
				        success: function (response) {
				            $.each(response,function(index,item){
				                if(item.metadata && item.metadata['PrestazioniDizionario.TariffaSSN'] && !tariffarioSSN[item.title])tariffarioSSN[item.title]=item.metadata["PrestazioniDizionario.TariffaSSN"].vals[0];
				                if(item.metadata && item.metadata['PrestazioniDizionario.TariffaALPI'] && !tariffarioAlpi[item.title])tariffarioAlpi[item.title]=item.metadata["PrestazioniDizionario.TariffaALPI"].vals[0];
				                if(item.metadata && item.id && !dizPrestazioni[item.id] )dizPrestazioni[item.title]=item.id;
				            });
				        }
				    });*/
					docObj=new myElementJSON(${model['element'].id});

				}
			);
				
           
            $(document).ready(function() {
                $( "#tabs" ).tabs();
                $("#tab1").click(function(){
                	rimuoviTotali();
                    //$('#example').handsontable('render');
                    
                });
                
                $("#tab3").click(function(){
                    /*
                    var handsontable1 =  $('#example').data('handsontable'); 
                    var handsontable2 =  $('#costi').data('handsontable');   
                    var preMigration= handsontable2.getData()
                    if(costiInit || preMigration[1][0]!==null || preMigration[0][1]!==null){
                    	//var migrated=mergeData(preMigration,handsontable1.getData());
                    	//handsontable2.loadData(preMigration);
                    	//$('#costi').handsontable('render');
                    	calcolaTotali();
                    }
                    else{
                    costiInit=true;
                    	var migrated=migrateData(handsontable1.getData());
                    	var handsontable2 =  $('#costi').data('handsontable');   
                    
                    	handsontable2.loadData(migrated);
                    }
                    */
                    moveBudget('tabs-3');
                    
                    
                });
                 $("#tab4").click(function(){
                 	moveBudget('tabs-4');
                 });
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
                    var heights=new Array();
                    var widths=new Array();
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
                          points: [0, offsetY, 1000, offsetY],
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
                                
                                layer.add(circle);
                            }
                        }
                    }
                    var stage = new Kinetic.Stage({
                        container: 'grafico',
                        width: 1200,
                        display:'block',
                        height: totalHeight
                      });
                    stage.clear();
                    stage.add(layer);
                });
            });
            
        </script>

        <div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
        <div id="tabs">
        <ul style='height:27px'>
        <li><a id='tab1' href="#tabs-1">Disegno Flowchart</a></li>
        <li><a id='tab2' href="#tabs-2">Rimborsabilit&agrave;</a></li>
        <li><a id='tab4' href="#tabs-4">Budget clinico</a></li>
        <!--li><a id='tab3' href="#tabs-3">Budget studio</a></li-->
        </ul>
        <div id="tabs-1">
        <div id="example"></div>
        <!--button id="tp-button">Aggiungi visita</button-->
            <div id="tp-dialog-form" title="Aggiungi visita">
                <form>
                <fieldset>
                <label for="TimePoint_Descrizione">Descrizione</label>
                <input type="text" name="TimePoint_Descrizione" id="TimePoint_Descrizione" value="" class="text ui-widget-content ui-corner-all" />
                <label for="TimePoint_NumeroVisita">Numero visita</label>
                <input type="text" name="TimePoint_NumeroVisita" id="TimePoint_NumeroVisita" value="" class="text ui-widget-content ui-corner-all"/>
                
                <label for="TimePoint_Tempi">Tempi</label>
                <input type="text" name="TimePoint_Tempi" id="TimePoint_Tempi" value="" class="text ui-widget-content ui-corner-all"/>
                <label for="TimePoint_DurataCiclo">Durata</label>
                <input type="text" name="TimePoint_DurataCiclo" id="TimePoint_DurataCiclo" value="" class="text ui-widget-content ui-corner-all"/>
                <label>Tipo di ricovero</label><br/>
                <label for="Ricovero_Ordinario">Ricovero Ordinario</label><input type="checkbox" id="Ricovero_Ordinario" name="Ricovero_Ordinario" value="1" />
                <label for="Ricovero_Straordinario">Ricovero Extra routine</label><input type="checkbox" id="Ricovero_Straordinario" name="Ricovero_Straordinario" value="1" />
                <label for="Ricovero_Ambulatoriale">Ricovero Ambulatoriale</label><input type="checkbox" id="Ricovero_Ambulatoriale" name="Ricovero_Ambulatoriale" value="1" />
                <label for="Ricovero_Telefonico">Casa (con check telefonico )</label><input type="checkbox" id="Ricovero_Telefonico" name="Ricovero_Telefonico" value="1" />
                <label for="TimePoint_Note">Note</label>
                <input type="text" name="TimePoint_Note" id="TimePoint_Note" value="" class="text ui-widget-content ui-corner-all"/>
                
                 </fieldset>
                </form>
            </div>
             <div id="prestazione-dialog" title="Nuova Prestazione">
                <form>
                <fieldset>
                <label for="Altro_Descrizione">Descrizione</label>
                <input type="text" name="PrestazioniDizionario_Descrizione" id="Altro_Descrizione" value="" class="text ui-widget-content ui-corner-all" />
                
                
                 </fieldset>
                </form>
            </div>
            <div id="prestazione-diz-dialog" title="Nuova Prestazione">
                <form>
                <fieldset>
                 <div class="ui-widget">
                <label for="Prestazioni_prestazione">Prestazione</label>
                <input type="text" name="Prestazioni_prestazione" id="Prestazioni_prestazione" value="" class="text ui-widget-content ui-corner-all" />
                </div>
                <label for="Prestazioni_CDC">Centro di costo</label>
                <input type="text" name="Prestazioni_CDC" id="Prestazioni_CDC" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_CDCCode" id="Prestazioni_CDCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_UOC" id="Prestazioni_UOC" value="" class="text ui-widget-content ui-corner-all" />
                
               <input type="hidden" name="Prestazioni_UOCCode" id="Prestazioni_UOCCode" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" name="Tariffario_Solvente" id="Tariffario_Solvente" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Tariffario_SSN" id="Tariffario_SSN" value="" class="text ui-widget-content ui-corner-all" />
                 </fieldset>
                </form>
            </div>
            <!--div ><button id="prestazione-diz-button">Aggiungi prestazione</button></div-->
         
         <div style='display:none'><button id="prestazione-button">Aggiungi prestazione</button></div>
            <div id="prestazione-dialog-form" title="Aggiungi prestazione">
                <p class="validateTips">Tutti i campi sono obbligatori</p>
                <form>
                <fieldset>
                <label for="titolo-prestazione">Nome prestazione</label>
                <input type="text" name="titolo-prestazione" id="titolo-prestazione" value="" class="text ui-widget-content ui-corner-all" />
                <label for="descrizione-prestazione">Descrizione</label>
                <input type="text" name="descrizione-prestazione" id="descrizione-prestazione" value="" class="text ui-widget-content ui-corner-all"/> </fieldset>
                </form>
            </div>
         <!--div id="second-element">
            <span class="sortable-list-span">
                <h3>Prestazioni</h3>
                    <ul class='sortable-list' id='COSTS' > </ul>
            </span>
            <span class="sortable-list-span">     
                <h3>Time-points</h3>
                    <ul class='sortable-list' id='TPS'> </ul>
            </span>
            <br class="clear" />
        </div-->
        </div>
        <div id="tabs-2">
         <!--canvas id='grafico' width="1200" height="500" ></canvas-->
         <div id='grafico' style="display:block"></div>
         <div id='legenda'><span style="display:inline-block;width:10px;height:10px;background-color:lightblue;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni aggiuntive rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:orange;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie ma nel caso specifico rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:white;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie a carico SSN/SSR</span></div>
         <div id='rimborsabilita'></div>
        </div>
       
        <div id="tabs-4">
           <div id='clinico'>
        <div id="costi"></div>
        <br/>
            <h2>Budget clinico</h2>
        <div id="added-costs-1" class="ui-widget cost-table">
            <h1>Costi aggiuntivi per paziente:</h1>
            <table id="costs-1" class="ui-widget ui-widget-content">
            <thead>
            <tr class="ui-widget-header ">
            <th>Descrizione</th>
            <th>Transfer price</th>
            <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
            
            </tbody>
            </table>
        </div>
        <div id="added-costs-2" class="ui-widget cost-table">
            <h1>Costi aggiuntivi per studio:</h1>
            <table id="costs-2" class="ui-widget ui-widget-content">
            <thead>
            <tr class="ui-widget-header ">
            <th>Descrizione</th>
            <th>Transfer price</th>
            <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
            
            </tbody>
            </table>
        </div>
		    <div id='pazienti-tabs-4'><span id='global-pazienti'>Pazienti previsti:<span id='show-n-pat'></span></span></div>
       
        <button id="create-cost">Aggiungi costo clinico</button>
            <div id="dialog-form" title="Aggiungi costo">
                
                <form>
                <fieldset>
                <label for="tipologia">Tipo di applicazione</label>
                <select  name="tipologia" id="tipologia" class="text ui-widget-content ui-corner-all" />
                    <option value="1">Per paziente</option>
                    <option value="2">Per studio</option>
                </select>
                <label for="descrizione">Descrizione</label>
                <input type="text" name="Base_Nome" id="descrizione" value="" class="text ui-widget-content ui-corner-all" />
                <label for="costo-costo">Costo</label>
                <input type="text" name="Costo_Costo" id="costo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup-costo">Markup</label>
                <input type="text" name="Costo_Markup" id="markup-costo" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup-costo" value="" class="text ui-widget-content ui-corner-all" >
                	<option value="1">Valore assoluto</option>
                	<option value="2">%</option>
                	
                </select>
                <label for="transfer-costo">Transfer price</label>
                <input type="text" name="Costo_TransferPrice" id="transfer-costo" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
            <button id="add-n-pat">Numero di pazienti previsto</button>
            <div id="dialog-form-n-pat" title="Numero di pazienti">
                <form>
                <fieldset>
                <label for="n-pat">Numero di pazienti</label>
                <input type="text" name="BudgetCTC_NumeroPazienti" id="n-pat" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>
            <div id="dialog-form-transfer" title="Aggiungi transfer price">
                <p class="validateTips"></p>
                <form>
                <fieldset>
                <div id='tariffaSSN'>Tariffa SSR: <span  id='valoreSSN'></span></div>
               	<div id='tariffaAlpi'>Tariffa ALPI: <span  id='valoreAlpi'></span></div>
               	<div id='tariffaSolvente'>Tariffa Solvente: <span  id='valoreSolvente'></span></div>
               	<label for="oreuomo">Ore uomo</label>
                <input type="text" name="Costo_OreUomo" id="oreuomo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="oremacchina">Ore macchina</label>
                <input type="text" name="Costo_OreMacchina" id="oremacchina" value="" class="text ui-widget-content ui-corner-all" />
                <label for="costo">Costo</label>
                <input type="text" name="Costo_Costo" id="costo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup">Mark-up</label>
                <input type="text" name="Costo_Markup" id="markup" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup" value="" class="text ui-widget-content ui-corner-all" >
                	<option value="1">Valore assoluto</option>
                	<option value="2">%</option>
                	
                </select>
                <label for="transfer">Transfer Price <span style="color:red">(Obbligatorio)</span></label>
                <input type="text" name="Costo_TransferPrice" id="transfer" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
            </div> 
            
            
            
            
            
        </div>
        </div>
  <button id="Salva" onclick="saveAll();">Salva</button>     
  <script type="text/javascript">
        //var data=[[]];
        //var data = [["Procedure","Screening","P2 TP1 D1","P2 TP1 D8","P2 TP1 D15"," P2 TP2 D1","P2 TP2 D8","P2 TP2 D15","P2 TP3 D1","P2 TP3 D8","P2 TP3 D15","P2 TP4 D1","P2 TP4 D15","End of Study /    30-day Follow-up"],[" Informed Consent Process "," x ","","","","","","","","","","","",""],["Complete Physical Exam (incl. vitals and med history as well as Signs, Symptoms and Toxicities)"," x ","","","","","","","","","","","",""],["Inclusion/Exclusion"," x ","","","","","","","","","","","",""],["Focused Physical Exam (incl. vitals and med history as well as Signs, Symptoms and Toxicities)",""," x "," x "," x "," x ","",""," x ","",""," x ",""," x "],["ECOG"," x "," x "," x "," x "," x ","",""," x ","",""," x ",""," x "],["BSA (included in physical exam)"," x "," x "," x "," x "," x ","",""," x ","",""," x ",""," x "],["Hematology"," x "," x "," x "," x "," x "," x "," x "," x ","",""," x ",""," x "],["Biochemistry"," x "," x "," x "," x "," x "," x "," x "," x ","",""," x ",""," x "],["Hgb A1C"," x ","","",""," x ","","","","",""," x ",""," x "],["Urine Cotinine"," x ","","","","","","","","","","","",""],["Urinalysis"," x ","","",""," x ","","","","",""," x ","",""],["CA-125"," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x ",""," x "],["CT Scan or MRI "," x ","","","","",""," x ","","","",""," x ",""],["Obtaining of Archival tumor sample"," x ","","","","","","","","","","","",""],["Pharmacokinetics",""," x ","",""," x ","","","","","","","",""],["Pharmacodynamics-plasma",""," x "," x "," x "," x ","",""," x ","","","","",""],["Pharmacodynamics - fresh tumor biopsy (optional)"," x ","",""," x ","","","","","","","","",""],["Pharmacodynamics - Ascitic fluid (optional)"," x ",""," x ","","","","","","","","","",""],["Serum or Urine Pregnancy Test"," x ","","","","","","","","","","","",""],["12-Lead ECG"," x "," x ","","","","",""," x ","",""," x ",""," x "],[" Total Patient Care Related Per Visit "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "," € -   "],["","","","","","","","","","","","","",""],["Investigator Fee"," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "],["Study/Nurse Coordinator Fee                                                                               (includes drug dispensing and compliance as well as concomitant medications)"," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "],["Administration/Data Entry Fee"," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "," x "]];
        var prestazioni=['prestazione1','prestazione2'];
        var tps=[];
        
        var myForm1Renderer = function (instance, td, row, col, prop, value, cellProperties) {
            
            Handsontable.TextCell.renderer.apply(this, arguments);
            
            $(td).html($.axmr.label(value));
            $(td).off('click').on('click',function(ev){
            	$.axmr.deselectGrid('#example');
            	return true;
            });
            $(td).off('click').on('click',function(ev){
            	ev=ev?ev:window.event;
                ev.stopPropagation();
                ev.preventDefault();
                
                $(this).dblclick();
                
            });
            $(td).off('dblclick').on('dblclick',function(ev){
                ev=ev?ev:window.event;
                ev.stopPropagation();
                ev.preventDefault();
               
                $("#prestazione-diz-dialog").off('dialogopen').on('dialogopen',function(ev){
                    var width=$(window).width()/100*80;
                    var height=$(window).height()/100*80;
                    $(this).dialog('option',{width:width,height:height});
                    ev=ev?ev:window.event;
                    var that=this;
                    $.axmr.deselectGrid('#example');
                    var myElement=$.axmr.guid(value);
                    if(myElement){
                    	elementToForm(myElement,'prestazione-diz-dialog');
                   	}
                    else{
                    	elementToForm(emptyPrestazione,'prestazione-diz-dialog');
                    }
                   
                    $(this).find('input[id^=Prestazioni_prestazione]').focus();
                    console.log($(this).find('input[id^=titolo]'));
                    var that=this;
                    $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
                        var checkAll=true;
                        $(that).find('input[type=text]').each(function(){
                        	if(!$(this).val()){
                        		checkAll=false;
                        	}
                        });
                        if(!checkAll){
                        	alert('Compilare tutti i campi per la prestazione.');
                        	return;
                        }
                        if(!myElement){
                        	myElement=$.extend(true,{},emptyPrestazione);
                        }
                        myElement.coordinates={x:col,y:row};
                        formToElement('prestazione-diz-dialog',myElement);
                        
                        newValue=$.axmr.guid(myElement,getDato(myElement.metadata['Prestazioni_prestazione']));
                        $('#example').handsontable('setDataAtCell',row,col,newValue);
                        $("#prestazione-diz-dialog").dialog('close');
                    });
                    
                    
                });
                $("#prestazione-diz-dialog").dialog("open");
                return false;
            }).css({
                color: 'black'
            });
        };
        var myForm2Renderer = function (instance, td, row, col, prop, value, cellProperties) {
            
            Handsontable.TextCell.renderer.apply(this, arguments);
            
            $(td).html($.axmr.label(value));
            $(td).off('click').on('click',function(ev){
            	$.axmr.deselectGrid('#example');
            	return true;
            });
            $(td).off('click').on('click',function(ev){
            	ev=ev?ev:window.event;
                ev.stopPropagation();
                ev.preventDefault();
                
                $(this).dblclick();
                
            });
            $(td).off('dblclick').on('dblclick',function(ev){
                ev=ev?ev:window.event;
                ev.stopPropagation();
                ev.preventDefault();
                
                
                $("#tp-dialog-form").off('dialogopen').on('dialogopen',function(ev){
                	var width=$(window).width()/100*80;
                    var height=$(window).height()/100*80;
                    $(this).dialog('option',{width:width,height:height});
                    ev=ev?ev:window.event;
                    var that=this;
                    
                    $.axmr.deselectGrid('#example');
                    var myElement=$.axmr.guid(value);
                   
                    if(myElement){
                    	elementToForm(myElement,'tp-dialog-form');
                    }
                    else{
                    	elementToForm(emptyTimePoint,'tp-dialog-form');
                    }
                    $(this).find('input[id$=Descrizione]').focus();
                    $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
                        var newValue='';
                        
                        if(!myElement){
                        	myElement=$.extend(true,{},emptyTimePoint)
                        }
                        //if(newData['TimePoint_NumeroVisita']=='')newData['TimePoint_NumeroVisita']=col;
                        myElement.coordinates={x:col,y:row};
                        formToElement('tp-dialog-form',myElement);
                        newValue=$.axmr.guid(myElement,buildTpDescription(myElement));
                        $('#example').handsontable('setDataAtCell',row,col,newValue);
                       
                        $("#tp-dialog-form").dialog('close');
                    });
                    
                    
                });
                $("#tp-dialog-form").dialog("open");
                return false;
            }).css({
                color: 'black'
            });
        };
        //form dei costi
         var myForm3Renderer = function (instance, td, row, col, prop, value, cellProperties) {
           
            
            Handsontable.TextCell.renderer.apply(this, arguments);
            var firstData=$.axmr.label($('#example').handsontable('getDataAtCell',row,col));
            
            $(td).html($.axmr.label(value,2));
            if(firstData){
          
            	if(!value)value=$('#example').handsontable('getDataAtCell',row,col);
          		var myElement=$.axmr.guid(value);
            	var rimborso=getDato(myElement.metadata['Rimborso_Rimborsabilita'])
            	rimborso+='';
            	var color='lightblue';
            	switch(rimborso){
            		case '0':
	            		color='lightblue';
	            		break;
	            	case '1':
	            		color='orange';
	            		break;
	            	case '2':
	            		color='white';
	            		break;
            	}
            	console.log(color);
            	$(td).css({"background-color":color});
            }
            else{
            	
	                       		
            	if(value){
		        	var rowText=$('#costi').handsontable('getDataAtCell',row,0);
		        		if(value<0){
		        			$(td).css({"background-color":'#F4505E'});
		        		}
		        		else if(rowText=='Valore target' || rowText =='Target markup'){
		        			$(td).css({"background-color":'#F4EC7F'});
		        		}
		        		else{
            		$(td).css({"background-color":'#7EF780'});
            	}
            	}
            	else{	
            	$(td).css({"background-color":'#CCC'});
            	}
            }
             $(td).off('dblclick').on('dblclick',function(ev){
	            	ev=ev?ev:window.event;
	                ev.stopPropagation();
	                ev.preventDefault();
					$.axmr.deselectGrid('#costi');	            	
					return;
	            });
            
        };
        var myCheckboxRenderer = function (instance, td, row, col, prop, value, cellProperties) {
            var test=$.axmr.label(value);
          if(arguments[5]!== undefined &&  arguments[5]!== null &&  ($.trim(test.toString()).match(/^x$/i) || test===true || test==1))arguments[5]=true;
          else if(arguments[5]!==null && arguments[5]!='true' && arguments[5]!==true ){
              arguments[5]=false;
          }
          Handsontable.CheckboxCell.renderer.apply(this, arguments);
          
          /*$(td).css({
            background: 'yellow'
          });*/
        };
         var myFixedRenderer = function (instance, td, row, col, prop, value, cellProperties) {         
          Handsontable.TextCell.renderer.apply(this, arguments);         
          $(td).html('<div style="height: 30px; overflow:hidden;">'+$(td).html()+'</div');
        };
        var myTranslateRender= function (instance, td, row, col, prop, value, cellProperties) {         
          Handsontable.TextCell.renderer.apply(this, arguments);         
          if(value=='Totale per visita' || value=='Valore con markup' || value=='Totale per prestazione' ){
          		$(td).css({"background-color":'#00BF00'});
          }   
          if(value=='Valore target' || value=='Target markup'){
          		$(td).css({"background-color":'#F7F754'});
          }         
          var label=$.axmr.label(value);
          $(td).html(label);
          
        };
        var myCostRenderer = function (instance, td, row, col, prop, value, cellProperties) {         
          Handsontable.TextCell.renderer.apply(this, arguments);         
          var label=$.axmr.label(value,2);
          $(td).html(label);
          $(td).css({
            color: 'black'
          });
        };
        $('#costi').handsontable({
          width: 1200,
          height:800,
          minSpareRows:10,
          minSpareCols:10,
          columnHeaders:true,
          rowHeaders:true,
          minCols: 25,
          minRows: 25,
          colHeaders: true,
          contextMenu: false,
          manualColumnResize:true,
          cells: function (row, col, prop) {
            var cellProperties = {}
            cellProperties.readOnly=true;
            if(row==0 || col==0){
            	
            	cellProperties.renderer=myTranslateRender;
            } 
            if(row!=0 && col!=0)cellProperties.renderer=myForm3Renderer;  
            return cellProperties;
          }
          
          });
          $('#example').handsontable({
          width: 1200,
          height:800,
          minSpareRows:10,
          minSpareCols:10,
          manualColumnResize:true,
          columnHeaders:true,
          rowHeaders:true,
          minCols: 25,
          minRows: 25,
          colHeaders: true,
          contextMenu: true,

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
                loadData(data);
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
           $( "#Prestazioni_prestazione" ).autocomplete({
				
				minLength: 2,
				select: function( event, ui ) {
							$(this).closest('form').find('input#Prestazioni_CDC').val('');
						},
				source:function( request, response ) {
							var term = request.term;
							if ( term in cache ) {
								response( cache[ term ] );
								return;
							}
							$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
								cache[ term ] = data;
								response( data );
							});
						}
				
			});
			$( "#Prestazioni_CDC" ).autocomplete({
				
				minLength: 0,
				source:function( request, response ) {
							request.prestazione=$( "#Prestazioni_prestazione" ).val();
							$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
								//cache[ term ] = data;
								response( data );
							});
						},
				 select: function( event, ui ) {
							valorizzaCDC(this,ui.item);
						}
				
			});
			$("#prestazione-diz-dialog").dialog({
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
		        open:function(){
		            
		        }
		
		    });
		    $("#prestazione-diz-button").button().click(function() {
		        $("#prestazione-diz-dialog").dialog("open");
		    });
          //$( ".sortable-list" ).sortable();
       
    </script>

    </div>
   <#include "../helpers/budgetActions.ftl"/>
