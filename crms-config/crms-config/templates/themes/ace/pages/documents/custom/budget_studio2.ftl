<#assign budget=model['element'] />
<#assign el= budget.getParent() />
<#assign elType= el.type />
<#assign budgetStudio=budget />
<#assign budget=budgetStudio.getParent().getParent().getParent().getParent() />

<#assign budgetBase=budget />
<#assign center=budgetBase.getParent() />
<#assign budget=model['element'] />
<#assign el= el.getParent() />
<#assign elType= el.type />
 <#include "../helpers/MetadataTemplate.ftl"/>
 <div class="row">
   		<div class="col-xs-9">
        <div style="text-align:right">
        <button class="btn btn-warning" id="Salva"  onclick="saveAll();"><i class="icon-save"></i> <b>Salva</b></button>
        <button class="btn btn-primary" id="create-cost-2"><i class="icon-plus"></i> Costo non clinico</button>
        <button class="btn btn-primary" id="add-CTC"><i class="icon-plus"></i> Overhead aziendale</button> 
	        <button class="btn btn-primary"  id="add-n-pat">Numero di pazienti previsto</button> <#--button class="btn btn-primary" id="create-target"><i class="icon-plus"></i> Proposta promotore</button-->
    	<button class="btn btn-primary"   onclick="location.href='../../detail/${el.getId()}#tabs-5';">Lista di budget studio</button>
    	<#include "../helpers/budgetStudioActions.ftl"/>
    </div>
    <div style="display: block">
   <br><br>
	
            <!--link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery.ui.base.css" /-->
        <!--link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery.ui.css" /-->
        
	<style>
		#task-Actions{
			display:inline;
		}
		/*fieldset {
		    border: 1px solid #336EA9;
		    border-radius: 10px;
		    padding: 1em;
		    
		}*/
		
		div.cost-table{
			margin:0px;
		}
		.half-w2{
			width:45%;
			float:right;
		}
		.half-w{
			width:45%;
			float:left;
		}
		.full-w{
			width:91.5%;
			
		}
		#budget-clinico{
			width:30%;
		}
		#budget-studio{
			width:60%;
		}
		.ui-dialog fieldset {
		    border: 0px solid #336EA9;
		    border-radius: 0px;
		    padding: 1em;
		    
		}
		
		#tablesList td{
			vertical-align:top;
			padding:5px;
			
		}
		
		.ui-autocomplete.ui-menu{
			z-index:9999!important;
		}
			.handsontable td{
				font-size: 13px;
				font-weight:200;
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
		/*label{
			font-size:1.3vw;
			line-height:1.6vw;
		}*/
		#tp-dialog-form label{
			font-size:1.1vw;
			line-height:1.4vw;
		}
		
	</style>


  <@script>
  Pace.start();
 </@script>

      
        <@script>
        
        loadingScreen("Caricamento in corso...", "${baseUrl}/int/images/loading.gif");
         <#include "../../../data/pages/documents/detail/budget/functions/fixHeaders.ftl"/>
        var updating=(<#if el.getUserPolicy(userDetails).isCanUpdate() >true<#else>false</#if> && <#if budgetStudio.getUserPolicy(userDetails).isCanUpdate() >true<#else>false</#if>);
        if(!updating){
        		$('button:has(i.icon-plus)').remove();
        		$('form').parent().parent().find('button:contains(Aggiungi)').remove();
        		$('form').find(':input').not('button').attr('disabled','disabled');
        		$('#Salva').remove();
        		$('#add-n-pat').hide();
        	
        }else{
        	$('#add-n-pat').show();
        }
        var cache = {};
        var baseData;
        var budgetCTC=true;
        var folderPrezzi;
        var folderTarget;
        function updatePrezzoTD(prezzo,idx,tipologia,myElement){
        	if(myElement){
        	
	        	if(tipologia==1 || tipologia==2){
	        		myElement=getDato(myElement.metadata['PrezzoFinale_Prestazione']);
	        		
	        	}
        	var quantita=parseFloat(getDato(myElement.metadata['Costo_Quantita']));
	        	if(tipologia!=5){
			    	if(quantita && !isNaN(quantita) && quantita>0)prezzo=prezzo*quantita;
			    	else prezzo='N.A.';
			    }
			}
        	
        	var id="#tr-tip"+tipologia+"-" + idx ;
        	
			$(id+"  td:nth-child(2)").html(prezzo.formatMoney());
			
        }
        function formPrezzo(tipologia,idx){
        	var myElement;
        	switch(tipologia){
       			case '1':
       			case '2':
       				var myElement=docObj.elements.prezzi[idx];
       			break;
       			case '3':
       				var myElement=docObj.elements.pxpCTC[idx];
       			break;
       			case '4':
       				var myElement=docObj.elements.pxsCTC[idx];
       			break;
       			case '5':
       				var myElement=docObj.elements.passthroughCTC[idx];
       			break;
       		}
        	if(tipologia==1 || tipologia==2){
        		form='dialog-form-prezzo';
        		changeButton=true;
        	}
        	else {
        		form='dialog-form-cost-2';
        		changeButton=false;
        	}
        	if(!changeButton){            		           		
               		elementToForm(myElement,form);
               		$('#'+form).find('#idx').val(idx);  
               		$('#tipologia2').val(tipologia);  
               		$('#tipologia2').attr('disabled','disabled'); 
            } 
        	if(changeButton)$("#"+form).off('dialogopen').on('dialogopen',function(ev){
           		var width=$(window).width()/100*80;
                var height=$(window).height()/100*80;
                //$(this).dialog('option',{width:width,height:height});
                ev=ev?ev:window.event;
                var that=this;
                if(!myElement) {
                	console.log('controllare');
                	myElement=$.extend(true,{},emptyPrezzoPrestazione);
                }
                elementToForm(myElement, form);
                                                         
	           $(this).find('[id^=tariffa]').hide(); 
	           $(this).find('#valoreTransferPrice').html(getDato(getDato(myElement.metadata['PrezzoFinale_Prestazione']).metadata['Costo_TransferPrice'])); 
               
              $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
                	if($(that).find('input[id^=PrezzoFinale_Prezzo]').val()=='' || isNaN($(that).find('input[id^=PrezzoFinale_Prezzo]').val())){
                		updateTips( 'Prezzo obbligatorio.' );
                		return;
                	}
                	else{
                		$('.validateTips').removeClass("ui-state-highlight").hide();
                	}
                    var newValue='';
                    myElement=formToElement(form,myElement,folderPrezzi);
                                        updatePrezzoTD($(that).find('input[id^=PrezzoFinale_Prezzo]').val(),idx,tipologia,myElement)
                    

                   calcolaTotali();
                   $("#dialog-form-prezzo").dialog('close');
                });
                if(!updating){
               		$(this).parent().find('button:contains(Aggiungi)').remove();
			        $(this).parent().find(':input').not('button').attr('disabled','disabled');
			    } 
                
            });
             console.log('ora 2');
            $("#"+form).dialog("open");
             changeTipologia();   
            return false;
       
        }
        
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
        var budgetCTC=true;
        function moveBudget(target){
        	if(target=='tabs-3'){
        		budgetCTC=true;
        		$('#add-n-pat').show();
        		$('#global-pazienti').show();
        	}
        	else{
        		budgetCTC=false;
        		$('#add-n-pat').hide();
        		$('#global-pazienti').hide();
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
   
        //confronta
        var empties=new Array();
        var emptiesTmp=new Array();
        //voce typeId in prod: 67 in locale : 8
        var emptyVoce={"id":null,"type":{"id":"67","typeId":"VocePrestazione"},"children":null,"metadata":{"PrestazioniDizionario_CodiceBranca3":[""],"PrestazioniDizionario_Descrizione":[""],"PrestazioniDizionario_CodiceBranca4":[""],"PrestazioniDizionario_CodiceBranca1":[""],"PrestazioniDizionario_CodiceBranca2":[""],"PrestazioniDizionario_Codice":[""],"PrestazioniDizionario_Tipo":[""],"PrestazioniDizionario_Nota":[""],"PrestazioniDizionario_TariffaALPI":[""],"PrestazioniDizionario_TariffaSSN":[""]},"title":""};
        <#list elType.getAllowedChilds() as myType>
		<#assign json=myType.getDummyJson() />
		empty${myType.typeId}=${json};
		empties[empty${myType.typeId}.type.id]=empty${myType.typeId};
			<#list myType.getAllowedChilds() as childType>
				<#assign json=childType.getDummyJson() />
				empty${childType.typeId}=${json};
				empties[empty${childType.typeId}.type.id]=empty${childType.typeId};
			</#list>
		</#list>

		<#list budget.type.getAllowedChilds() as myType>
		
		<#assign json=myType.getDummyJson() />
		empty${myType.typeId}=${json};
			<#list myType.getAllowedChilds() as childType>
				<#assign json=childType.getDummyJson() />
				empty${childType.typeId}=${json};
			</#list>
		</#list>
/*
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
        emptiesTmp[emptiesTmp.length]=emptyPrezzoPrestazione;
        emptiesTmp[emptiesTmp.length]=emptyFolderBracci;
        emptiesTmp[emptiesTmp.length]=emptyBraccio;
        $.each(emptiesTmp,function(ie,currEmpty){
        	empties[currEmpty.type.id]=currEmpty;
        });
        */
        <#global availableTypes={} /> 
		
	   
	   	<#list elType.getAllowedChilds() as myType>
	   	<#global availableTypes=availableTypes+{myType.typeId:myType} /> 
		
			<#list myType.getAllowedChilds() as childType>
				<#global availableTypes=availableTypes+{childType.typeId:childType} /> 
				
			</#list>
		</#list>
        <#assign elementJson=el.getElementCoreJsonToString(userDetails) />
        <#assign budgetJson=budget.getElementCoreJsonToString(userDetails) />
        var loadedElement=${elementJson};
        var loadedBudget=${budgetJson};
        var groupItems=new Array();
	    <#--list model['groupItems'] as item >
	    	
		groupItems[groupItems.length]=${item.getElementCoreJsonToString(userDetails)};
		</#list-->
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
        
        function formToElement(form,element,parent){
        	$('#'+form).find(':input').each(function (){
        		var label=$(this).attr('name');
        		//label=label.replace(/^[^_]*_/,'');
        		if(empties[element.type.id].metadata[label]!=undefined){
        			if($(this).attr('type')=='checkbox'){
        				if(this.checked) element.metadata[label]=1;//$(this).val(); risulta vuoto indagare come mai viene svuotato
        				else  element.metadata[label]='';
        			}
        			else if($(this).attr('type')=='radio'){
						if(this.checked) element.metadata[label]=$(this).val();
					}
        			else{
        			//PrezzoFinale_Prezzo
        				var value=$(this).val();
        				if(label=='PrezzoFinale_Prezzo' || label=='Costo_Prezzo' || label=='Costo_Costo' || label=='Costo_TransferPrice'){
        					value=value.formatMoney().unformatMoney();
        				}
        				element.metadata[label]=value;
        			}
        		}
        		else{
        		console.log(label);
        		console.log(empties[element.type.id].metadata[label]);
        		}
        	});
        	$.axmr.setUpdated(element,parent);
        	return element;
        }
        
        function elementToForm(element,form){
        	$('#'+form).find(':input').each(function (){
        		var label=$(this).attr('name');
        		//label=label.replace(/^[^_]*_/,'');
        		if($(this).attr('type')=='checkbox'){
        			if(getDato(element.metadata[label]))this.checked=true;
        			else this.checked=false;
        		}else if($(this).attr('type')=='radio'){
					var metaValue=getDato(element.metadata[label]);
					var decoded = $('<div/>').html(metaValue).text();
					if(decoded==this.value)this.checked=true;
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
			var quickMetadata={};
			$.each(metadata,function(key,value){
				if(!$.isArray(value)){
					var tmp=value;
					value=new Array();
					value[0]=tmp;
				}
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
				if( approvedMetadata && $.isArray(approvedMetadata) && $.inArray(key,approvedMetadata)>-1){
					quickMetadata[key]=metadata[key];
				}
			});
			if(quickSave){
				return quickMetadata;
			}
			else{
				return metadata;
			}
		}
        function updateElement(element){
        	var metadata=prepareMetadataForPost(element.metadata);
        	
        	return $.ajax({
        		method:'POST',
        		url:'../../../rest/documents/update/'+element.id,
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
	        		url:'../../../rest/documents/save/'+element.type.id,
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
        		url:'../../../rest/documents/searchByExample/'+element.type.id,
        		data:metadata
        	}).done(function(){console.log('Found!!!');}).fail(function(){console.log('error',element);});
        	 
       
        }
        function deleteElement(element){
        	if(element && element.id)
        	return $.ajax({
        		url:'../../../rest/documents/delete/'+element.id,
        		data:element.metadata
        	}).done(function(){console.log('DELETED');}).fail(alertError);
        }
        
        function saveAll(){
        	loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        	var queue=$.when({start:true});
        	queue=$.when(queue).then(function(data){return saveBulk();});
        	$.when(queue).then(function(data){
	    		if(data.result=='OK'){
	    			updateIds(data.resultMap);
	    			clearSingleNotification('budgetChange');
	    			loadingScreen("Salvataggio effettuato!", "${baseUrl}/int/images/green_check.jpg", 1500);
	    			$(".warning").hide();
	    		}else{
	    			loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
        		}
	    	},function(){loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);});
	    	//$.when(queue).then(function(){location.reload(true);});
        	return;
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
        	//ciclo i timepoint prima colonna vuota e le altri con la descrizinoe del tp
    		currRow[0]='';
    		$.each(myObject.tp,function(k,currTp){
    			//currRow[k+1]=currTp.metadata['TimePoint_Descrizione'];
    			currRow[k+1]=$.axmr.guid(currTp,buildTpDescription(currTp));
    			currTp.coordinates={x:k+1,y:1};
    		});
    		result[0]=currRow;
    		//ciclo le prestazioni e setto la prima colonna di ogni riga
        	$.each(myObject.prestazioni, function(i,currPrestazione){
        		var row=i+1;
        		currRow=new Array();
        		var labelPrestazione=getDato(currPrestazione.metadata['Prestazioni_Codice']);
				if(!labelPrestazione)labelPrestazione='';
				else labelPrestazione+=' '
		        labelPrestazione+=getDato(currPrestazione.metadata['Prestazioni_prestazione']);
		    	if(labelPrestazione.length>18){
		    		labelPrestazione=labelPrestazione.substr(0,15)+'...';
		    	}
        		
        		currRow[0]=$.axmr.guid(currPrestazione,labelPrestazione);
        		currPrestazione.coordinates={x:1,y:i+1};
        		for(var col=1;col<result[0].length;col++){
        			currRow[col]='';
        		}
        		result[row]=currRow;
        	});
        	//ciclo i prezzi
        	var prezzi=new Array();
        	$.each(myObject.prezzi, function(i,currPrezzo){
        		var currTpxp=getDato(currPrezzo.metadata['PrezzoFinale_Prestazione']);
        		var label=getDato(currPrezzo.metadata['PrezzoFinale_Prezzo']);
        		//if(!label) label=getDato(currTpxp.metadata['Costo_TransferPrice']);
        		prezzi[currTpxp.id]=$.axmr.guid(currPrezzo,getDato(currTpxp.metadata['tp-p_Checked']),label);
        	});
        	//ciclo le prestazioni al timepoint x 
        	$.each(myObject.tpxp, function(i,currTpxp){
        		
        		var prestaAssoc;
        		var tpAssoc;
        		if($.isPlainObject(getDato(currTpxp.metadata['tp-p_Prestazione']))) prestaAssoc=$.axmr.getById(getDato(currTpxp.metadata['tp-p_Prestazione'])['id']);
        		if($.isPlainObject(getDato(currTpxp.metadata['tp-p_TimePoint']))) tpAssoc=$.axmr.getById(getDato(currTpxp.metadata['tp-p_TimePoint'])['id']);
        		if(prestaAssoc && tpAssoc){
        			if(prezzi[currTpxp.id]){
        				result[prestaAssoc.coordinates.y][tpAssoc.coordinates.x]=prezzi[currTpxp.id];
        			}
        			else{
        				var currPrezzo= $.extend(true,{},emptyPrezzoPrestazione);
        				currPrezzo.parent=folderPrezzi;
        				currPrezzo.metadata['PrezzoFinale_Prestazione'][0]=currTpxp;
        				myObject.prezzi[myObject.prezzi.length]=currPrezzo;
        				result[prestaAssoc.coordinates.y][tpAssoc.coordinates.x]=$.axmr.guid(currPrezzo,getDato(currTpxp.metadata['tp-p_Checked']),getDato(currTpxp.metadata['PrezzoFinale_Prestazione']));
        				
        			}
        			//result[prestaAssoc.coordinates.y][tpAssoc.coordinates.x]=$.axmr.guid(currTpxp,getDato(currTpxp.metadata['tp-p_Checked']),getDato(currTpxp.metadata['PrezzoFinale_Prestazione']));
        		}
        	});
        	return result;
        }
        
			var myElementJSON=function(id,callback){
				profiloCTC=true;
			//tp:timepoint,tpxp:prestazione al timepoint x, pxp: prestazione per paziente, pxs; prestazione per lo studio
				<#include "../../../data/pages/documents/detail/budget/common/docObjDefinition.ftl">
				//this.elements={tp:[],prestazioni:[],tpxp:[],pxp:[],pxs:[],markup:0,tpxp2update:[],tpxp2delete:[],pxs2delete:[],pxp2delete:[],budgetStudio:[],pxpCTC:[],pxsCTC:[],passthroughCTC:[],prezzi:[],target:{},bracci:[]};
				var instance=this;
				
				function parseElement(data,budget){
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
									case 'FolderPXPCTC':
										folderPxpCTC=child.id;
										instance.elements.pxpCTC=child.children;
									break;
									case 'FolderPXSCTC':
										folderPxsCTC=child.id;
										instance.elements.pxsCTC=child.children;
									break;
									case 'FolderPassthroughCTC':
										folderPassthroughCTC=child.id;
										instance.elements.passthroughCTC=child.children;
									break;
									case 'FolderBracci':
										folderBracci=child.id;
										instance.elements.bracci=child.children;
									break;
									case 'FolderCostiAggiuntivi':
										folderCostiAggiuntivi=child.id;
										instance.elements.costiAggiuntivi=child.children;
									break;
											
									/*case 'FolderBudgetStudio':
										folderBudgetStudio=child.id;
										
										if($.isArray(child.children) && child.children.length>0){
											instance.elements.budgetStudio=child.children[0];
										}
										else{
											instance.elements.budgetStudio=$.extend(true,{},emptyBudgetCTC);
										}
									break;*/
								}
							
							});
						}else{
							instance.elements.target=[];
							$.each(groupItems,function(index,child){
								var type=child.type.typeId;
								
								switch(type){
									case 'FolderTimePoint':
										folderTp=child.id;
										break;
									case 'TimePoint':
										instance.elements.tp[instance.elements.tp.length]=child;
									break;
									case 'FolderPrestazioni':
										folderPrestazioni=child.id;
										break;
									case 'Prestazione':
										instance.elements.prestazioni[instance.elements.prestazioni.length]=child;
									break;
									case 'FolderTpxp':
										folderTpxp=child.id;
										break;
									case 'tpxp':
										instance.elements.tpxp[instance.elements.tpxp.length]=child;
									break;
									
									
									case 'FolderBracci':
										folderBracci=child.id;
										break;
									case 'Braccio':
										instance.elements.bracci[instance.elements.bracci.length]=child;
									break;
									case 'FolderBudgetStudio':
										folderBudgetStudio=child.id;
										instance.elements.budgetStudio=loadedBudget;
										
									break;
									case 'FolderPXPCTC':
										folderPxpCTC=child.id;
									break;
									case 'PrestazioneXPaziente':
										if(child.parentTypeId=='FolderPXP'){
											instance.elements.pxp[instance.elements.pxp.length]=child;
										}else if(child.parentTypeId=='FolderPXPCTC'){
											instance.elements.pxpCTC[instance.elements.pxpCTC.length]=child;
						}
									break;
									case 'FolderPXSCTC':
										folderPxsCTC=child.id;
									break;
									case 'PrestazioneXStudio':
										if(child.parentTypeId=='FolderPXS'){
											instance.elements.pxs[instance.elements.pxs.length]=child;
										}else if(child.parentTypeId=='FolderPXSCTC'){
											instance.elements.pxsCTC[instance.elements.pxsCTC.length]=child;
										} if(child.parentTypeId=='FolderPassthroughCTC'){
											instance.elements.passthroughCTC[instance.elements.passthroughCTC.length]=child;
										}
										
									break;
									case 'FolderPassthroughCTC':
										folderPassthroughCTC=child.id;
									break;
									
									
									case 'FolderPrezzi':
										folderPrezzi=child.id;
									break;
									case 'PrezzoPrestazione':
										var currTp=getDato(child.metadata['PrezzoFinale_Prestazione']);
										if(currTp.type.typeId=='TimePoint'){
											instance.elements.target[currTp.id]=child;
										}
										else{
											instance.elements.prezzi[instance.elements.prezzi.length]=child;
										}
										
									break;
									case 'FolderTarget':
										folderTarget=child.id;
										//instance.elements.target=child;
										//TODO:gestire foldertarget
										/*
										$.each(child.children,function(key,val){
											tp=getDato(val.metadata['PrezzoFinale_Prestazione']);
											if(tp)instance.elements.target[tp.id]=val;
										});*/
										
									break;
									case 'FolderCostiAggiuntivi':
										folderCostiAggiuntivi=child.id;
										break;
									case 'CostoAggiuntivo':
										instance.elements.costiAggiuntivi[instance.elements.costiAggiuntivi.length]=child;
										break;
									
								}
							
							});
							instance.elements.tp.sort(sortTp);
							instance.elements.prestazioni.sort(sortPrestazioni);
						}
						instance.elements.budgetStudio=loadedBudget;
						if(loadedBudget && false){
							folderBudgetStudio=loadedBudget.parent.id;
							instance.elements.budgetStudio=loadedBudget;			
							//instance.elements.prezzi=loadedBudget.children;
							if(loadedBudget.children && loadedBudget.children.length>0){
								$.each(loadedBudget.children,function(index,child){
									var type=child.type.typeId;
								
									switch(type){
										case 'FolderPXPCTC':
											folderPxpCTC=child.id;
											instance.elements.pxpCTC=child.children;
										break;
										case 'FolderPXSCTC':
											folderPxsCTC=child.id;
											instance.elements.pxsCTC=child.children;
										break;
										case 'FolderPassthroughCTC':
											folderPassthroughCTC=child.id;
											instance.elements.passthroughCTC=child.children;
										break;
										case 'FolderPrezzi':
											folderPrezzi=child.id;
											instance.elements.prezzi=child.children;
										break;
										case 'FolderTarget':
											folderTarget=child.id;
											$.each(child.children,function(key,val){
												tp=getDato(val.metadata['PrezzoFinale_Prestazione']);
												if(tp)instance.elements.target[tp.id]=val;
											});
											
										break;
									}
								});
							}
						}
						instance.elements.tpxp2update=$.extend(true,[],instance.elements.tpxp);
						var data=getDataFromObj(instance.elements);
						//var costi=getCostiFromObj(instance.elements);
						console.log(instance.elements);
						console.log(data);
						baseData=data;
	 				    loadData(data,true,instance);
	 				    calcolaTotali();
         				var checkFolders=false;
         				if(instance.elements.bracci && instance.elements.bracci.length>0){
         					$("#add-n-pat").show();
         				}
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
			        	if(folderPxpCTC==null){
			        		//saveElement(emptyFolderPXPCTC,id);
			        		checkFolders=true;
			        	}
			        	if(folderPxsCTC==null){
			        		//saveElement(emptyFolderPXSCTC,id);
			        		checkFolders=true;
			        	}if(folderPassthroughCTC==null){
			        		//saveElement(emptyFolderPassthroughCTC,id);
			        		checkFolders=true;
			        	}
						if(folderCostiAggiuntivi==null){
				    		//saveElement(emptyFolderPXP,id);
				    		checkFolders=true;
				    	}
			        	if(checkFolders){
			        		setTimeout(function(){getFolders(id)},100);
			        	}
			        	if(callback) callback(instance);
			        	toggleLoadingScreen();
				}
				
				
				
				
				if(loadedElement && groupItems && groupItems.length>0){
					parseElement(loadedElement);
				}
				else{
					Pace.restart();
					groupItems=[];
					(function(){
						$.ajax({
							dataType: "json",
							url:'${baseUrl}/app/rest/documents/'+loadedElement.id+'/getGrouppedElements'
						}).done(function(data){
								groupItems=$.merge(groupItems,data);
								Pace.restart();
								$.ajax({
									dataType: "json",
									url:'${baseUrl}/app/rest/documents/'+loadedBudget.id+'/getGrouppedElements'
								}).done(function(data){
									groupItems=$.merge(groupItems,data);
									parseElement(loadedElement,loadedBudget);
								}).fail(alertError);
						}
						).fail(alertError);
					})();
				}
				if(loadedElement){
					parseElement(loadedElement,loadedBudget);
				}
				else{
					(function(){
						$.ajax({
							dataType: "json",
							url:'../../../rest/documents/getElementJSON/'+id
						}).done(parseElement).fail(alertError);
					})();
				}
			}
			
			function getFolders(id,reload){
				if(!(folderTp!=null && folderPrestazioni!=null && folderTpxp!=null && folderPxp!=null &&  folderBudgetStudio!=null)){
					$.ajax({
						dataType: "json",
						url:'../../../rest/documents/getElementJSON/'+id
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
									
									case 'FolderPXPCTC':
										folderPxpCTC=child.id;
									break;
									case 'FolderPXSCTC':
										folderPxsCTC=child.id;
									break;
									case 'FolderPassthroughCTC':
										folderPassthroughCTC=child.id;
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
					
					docObj=new myElementJSON(${el.id});
					$that3=$( "#Costo_PersonaleLabel") ;
					$( "#Costo_PersonaleLabel" ).autocomplete({
													
						minLength: 2,
						select: function( event, ui ) {
									$('#Costo_Personale').val(ui.item.id+'###'+ui.item.value);
									$('#Costo_PersonaleMatricola').val(ui.item.matricola);
									
								},
						source:function( request, response ) {
									$that3.next('i.icon-spinner').remove();
									$that3.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;top:0px;left:-20px' ></i>");
									var term = request.term;
									if ( term in cache ) {
										response( cache[ term ] );
										return;
									}
									$.getJSON(  "/dizionari/personale.php", request, function( data, status, xhr ) {
										cache[ term ] = data;
										response( data );
										$that3.next('i.icon-spinner').remove();
									});
								}
						
					});

				}
			);
				
           
            
        </@script>
		
        <div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
        <div id="tabs">
       
        <div id="tabs-3">
        <div id='clinico'>
        <div id="costi"></div>
        <#assign tabs=[] />
		<#assign tabsContent=[] />
		<#assign tabs=tabs+[{"target":"tabNonClinico","label":"Budget non clinico"}] />
		<#assign tabs=tabs+[{"target":"tabClinico","label":"Budget clinico"}] />
		<#assign tabs=tabs+[{"target":"tabStudio","label":"Budget studio"}] />
       <#assign currTabContent>
           
            <table id="tablesList" style="width:100%" ><tr><td>
            <div id="added-costs-3" class="ui-widget cost-table">
	            <fieldset> <legend>Costi aggiuntivi per paziente</legend>
	            <table id="costs-3" class="table table-striped table-bordered table-hover">
	            <thead>
	            <tr >
		            <th>Descrizione</th>
		            <th>Categoria</th>
		            <th>Prezzo (&euro;)</th>
		            <th>Modifica</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	        </div>
	        </fieldset>
	        </td></tr><tr><td>
	        <div id="added-costs-5" class="ui-widget cost-table">
	            <fieldset> <legend>Rimborsi a pi&egrave; di lista</legend>
	            <table id="costs-5"class="table table-striped table-bordered table-hover">
	            <thead>
	            <tr>
		            <th>Descrizione</th>
		            <th>Prezzo (&euro;)</th>
		            <th>Modifica</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	            </fieldset>
	        </div>
            </td></tr></table>
	         
            
       
      
        </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"tabNonClinico" }] />
        <#assign currTabContent>
           
            <!--button id="create-cost">Aggiungi costo clinico</button--> 
        <div id="added-costs-1" class="ui-widget cost-table">
            <legend>Prestazioni a richiesta</legend>
            <table id="costs-1" class="table table-striped table-bordered table-hover">
            <thead>
            <tr>
            <th>Descrizione</th>
            <th>Prezzo (&euro;)</th>
            <th>Modifica il prezzo</th>
            <th></th>
            </tr>
            </thead>
            <tbody>
            
            </tbody>
            </table>
        </div>
       
        </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"tabClinico" }] />
        
          
            <div id="dialog-form-n-pat" title="Numero di pazienti">
                <form>
                <fieldset>
                <label for="n-pat">Numero di pazienti</label>
                <input type="text" name="BudgetCTC_NumeroPazienti" id="n-pat" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>
            <div id="dialog-form-prezzo" title="Aggiungi prezzo finale">
                <p class="validateTips"></p>
                <form>
                <fieldset>
                <div id='tariffaSSN'>Tariffa SSR: <span  id='valoreSSN'></span> &euro;</div>
               	<div id='tariffaAlpi'>Tariffa ALPI: <span  id='valoreAlpi'></span> &euro;</div>
               	<div id='tariffaSolvente'>Tariffa Solvente: <span  id='valoreSolvente'></span> &euro;</div>
               	<div id='transferPrice'>Transfer Price: <span  id='valoreTransferPrice'></span> &euro;</div>
               	<br><br>
                <label for="PrezzoFinale_Prezzo">Prezzo per singola attivit&agrave;/prestazione (&euro;) <span style="color:red">(Obbligatorio)</span></label>
                <input type="text" name="PrezzoFinale_Prezzo" id="PrezzoFinale_Prezzo" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
            </div>
            
            <div id="dialog-form-CTC" title="Aggiungi overhead aziendale">
                <form>
                <fieldset>
                <label for="BudgetCTC_Markup">Overhead aziendale (%)</label>
                <input type="text" name="BudgetCTC_Markup" id="BudgetCTC_Markup" value="" class="text ui-widget-content ui-corner-all" />
               </fieldset>
                </form>
            </div>
            
           	<div id="dialog-form-cost-2" title="Aggiungi costo non clinico">
                
                <form>
                <fieldset>
                
                <#--select  name="tipologia" id="tipologia2" class="text ui-widget-content ui-corner-all" onchange="changeTipologia();if(this.value==5)$('#catbox').hide();else $('#catbox').show()" />
                    <option value="3">Per paziente</option>
                    
                    
                </select-->
                <input type="hidden" name="tipologia" id="tipologia2" value="3" class="dont-clear" />
                <#--span id='catbox'>
                <label for="interno_esterno">Categoria di costo</label>
                 <select  name="Costo_Categoria" id="interno_esterno" class="text ui-widget-content ui-corner-all" />
                    <option value="1">Interno</option>
                    <option value="2">Esterno</option>
                    
                </select>
                </span-->
                <label for="Prestazioni_prestazione">Descrizione</label>
                
                <input type="text" name="Base_Nome" id="Prestazioni_prestazione" value="" class="text ui-widget-content ui-corner-all" />
                <span class="tip_exclusive">
                <label for="Prestazioni_CDC">Competenza</label>
                
                <input type="text" name="Prestazioni_CDC" id="Prestazioni_CDC" value="" class="text ui-widget-content ui-corner-all" />
                </span>
                <@SingleFieldByType "Prestazione" "Attivita" availableTypes.Prestazione userDetails true />
				              <#--label for="oreuomo">Tempo uomo</label>
                <input type="text" name="Costo_OreUomo" id="oreuomo" style="width:35px;" value="" class="text ui-widget-content ui-corner-all" /> Ore <input sise="2" style="width:30px;" type="text" name="Costo_MinutiUomo" id="minuomo" value="" class="text ui-widget-content ui-corner-all" /> Minuti
                <label for="personale">Personale coinvolto</label>
                <input type="text" name="Costo_PersonaleLabel" id="Costo_PersonaleLabel" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_Personale" id="Costo_Personale" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_PersonaleMatricola" id="Costo_Personale" value="" class="text ui-widget-content ui-corner-all" /-->
                <label for="Costo_QuantitaNA">Quantit&agrave; non applicabile</label>
				<input type="checkbox" onchange="if(this.checked){$('#Costo_Quantita').val('').prop('disabled',true);} else {$('#Costo_Quantita').prop('disabled',false);}" name="Costo_QuantitaNA" value="1" id="Costo_QuantitaNA"  class="text ui-widget-content ui-corner-all" />
                <label for="Costo_Quantita">Quantit&agrave;</label>
                <input type="text" name="Costo_Quantita" id="Costo_Quantita" value="" class="text ui-widget-content ui-corner-all" /> 
  
                <label for="costo2">Costo (&euro;)</label>
                <input type="text" name="Costo_Costo" id="costo2" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup-costo2">Markup</label>
                <input type="text" name="Costo_Markup" id="markup-costo2" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup-costo2" value="" class="text ui-widget-content ui-corner-all" >       	
                	<option value="2" selected >%</option>
                	<option value="1">Valore assoluto</option>
                </select>
                
                <label for="prezzo-add">Prezzo (&euro;)</label>
                <input type="text" name="Costo_Prezzo" id="prezzo-add" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="idx" id="idx" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_UOCCode" id="Prestazioni_UOCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_UOC" id="Prestazioni_UOC" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_CDCCode" id="Prestazioni_CDCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="dizionario" id="dizionario" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
            
            <#assign currTabContent>
           
             
	        <div id="totali-CTC" class="ui-widget cost-table full-w">
	            <fieldset> <legend>Totale budget</legend>
	            <table id="table-tot" class="table table-striped table-bordered table-hover">
	            <thead>
	            <tr>
		            <th>Descrizione</th>
		            <th>Proposta promotore (&euro;)</th>
		            <th>Transfer price (&euro;)</th>
		            <th>Totale budget (&euro;)</th>
		            <th>TP/Promotore (%)<span class="help-button" title="Differenziale percentuale tra transfer price e proposta promotore">?</span></th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	            </fieldset>
	        </div>
	       
            <div id="advised-markup" class="ui-widget cost-table full-w">
	            <!--fieldset><legend>Markup stimato</legend>
	            <table id="table-advised-markup" class="table table-striped table-bordered table-hover">
	            <thead>
	            <tr>
	            	<th>Tipologia</th>
		            <th>Proposta promotore</th>
		            <th>Transfer price di confronto (&euro;)</th>
		            <th>Markup stimato</th>
	            </tr>
	            </thead>
	            <tbody>
     		  <tr>
            	<td colspan=4><span class="help-button">?</span> Tabella riassuntiva del markup stimato sulla base della proposta promotore </td>
            
           	  </tr>
            </tbody>
	            </table>
	            </fieldset-->
	            <div  style="font-size:21px!important;">
		        <label >Overhead aziendale: <span id='markup-ins'>N.A.</span></label><br>
		        <label  ><div id='pazienti-tabs-4'><span id='global-pazienti'>Pazienti previsti:<span id='show-n-pat'></span></span></div></label>
		        </div>
	        </div>
	        
            
	        <div class="clearfix"></div>
            
       
	        
	        <div id='pazienti-tabs-3'></div>
	        
           	<div id="dialog-form-target" title="Aggiungi proposta promotore">
                
                <form>
                <fieldset>
                <label for="target">Tipo di applicazione</label>
                <select  name="target" id="target" class="text ui-widget-content ui-corner-all" onchange="prepareTargetForm();" />
                    <option value="1">Per visita</option>
                    <option value="2">Per paziente</option>
                    <option value="3">Per studio</option>
                </select>
                <span id='target-form'></span>
                </fieldset>
                </form>
            </div>
            </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"tabStudio" }] />
	    			<@tabbedView tabs tabsContent "summaryTabs" />
        </div>
  
  <@script>
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
                    //$(this).dialog('option',{width:width,height:height});
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
                        
                        var labelPrestazione=getDato(myElement.metadata['Prestazioni_Codice']);
				        if(!labelPrestazione)labelPrestazione='';
						else labelPrestazione+=' '
				        labelPrestazione+=getDato(myElement.metadata['Prestazioni_prestazione']);
				    	if(labelPrestazione.length>18){
				    		labelPrestazione=labelPrestazione.substr(0,15)+'...';
				    	}
                        newValue=$.axmr.guid(myElement,labelPrestazione);
                        $('#example').handsontable('setDataAtCell',row,col,newValue);
                        $("#prestazione-diz-dialog").dialog('close');
                    });
                    if(!updating){
	               		$(this).parent().find('button:contains(Aggiungi)').remove();
				        $(this).parent().find(':input').not('button').attr('disabled','disabled');
				    } 
                    
                    
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
                    //$(this).dialog('option',{width:width,height:height});
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
                    if(!updating){
	               		$(this).parent().find('button:contains(Aggiungi)').remove();
				        $(this).parent().find(':input').not('button').attr('disabled','disabled');
				    } 
                    
                    
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
            var firstData=$.axmr.guid(value);
            var myContent=$.axmr.label(value,2);
           	if(isNaN(myContent)){
           		myContent='';
           	}
           	var rowText=$('#costi').handsontable('getDataAtCell',row,0);
   			var colOcc=($('#costi').handsontable('getDataAtCell',0,col)=='Totale occorrenze' || rowText =='Target markup');
           	if(myContent && !colOcc){
           		var money=myContent.formatMoney();
           	}
           	else if(colOcc){
           		money=myContent;
           	}
           	else{
           		money='';
           	}
		    $(td).html(money);
            
            if(firstData){
          
            	if(!value)value=$('#costi').handsontable('getDataAtCell',row,col);
          		var myElement=$.axmr.guid(value);
          		var mySelectedPrestazione;
          	    if(myElement)mySelectedPrestazione=getDato(myElement.metadata['PrezzoFinale_Prestazione']);
          	    var rimborso='';
            	if(mySelectedPrestazione) rimborso=getDato(mySelectedPrestazione.metadata['Rimborso_Rimborsabilita']);
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
            	$(td).off('click').on('click',function(ev){
	                ev=ev?ev:window.event;
	                ev.stopPropagation();
	                ev.preventDefault();
	             	$.axmr.deselectGrid('#costi');
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
	             	$.axmr.deselectGrid('#costi');
	                 if(mySelectedPrestazione && getDato(mySelectedPrestazione.metadata['Rimborso_Rimborsabilita'])==2){
	             
	                	return;	
	                }
	                
                
	                $("#dialog-form-prezzo").off('dialogopen').on('dialogopen',function(ev){
	               		var width=$(window).width()/100*80;
	                    var height=$(window).height()/100*80;
	                    //$(this).dialog('option',{width:width,height:height});
	                    ev=ev?ev:window.event;
	                    var that=this;
	                    if(!myElement) {
	                    	console.log('controllare');
	                    	myElement=$.extend(true,{},emptyPrezzoPrestazione);
	                    }
	                    elementToForm(myElement,'dialog-form-prezzo');
	                    
	                    
	                    $('#costi').handsontable('deselectCell');
	                    $(this).find('input[id^=costo]').focus();
	                   
			            
			            var myPrestazioneGuid=$('#costi').handsontable('getDataAtCell',row,0);
			            var myPrestazioneLabel=$.axmr.label(myPrestazioneGuid);
			            $("#dialog-form-transfer").prev('.ui-dialog-titlebar').find('.ui-dialog-title').html(myPrestazioneLabel);
			            var myPrestazione=$.axmr.guid(myPrestazioneGuid);
			            var valoreSSN,valoreSolvente,valoreAlpi;
			            if($.isPlainObject(myPrestazione)){
	                    	valoreSSN=getDato(myPrestazione.metadata['Tariffario_SSN']);
							valoreSolvente=getDato(myPrestazione.metadata['Tariffario_Solvente']);
							valoreAlpi=getDato(myPrestazione.metadata['Tariffario_ALPI']);
							valoreTransferPrice=getDato(mySelectedPrestazione.metadata['Costo_TransferPrice']);
						}
						if(valoreSSN){
							$(that).find('#valoreSSN').html(valoreSSN);
							$(that).find('#tariffaSSN').show();
						}
						else{
							$(that).find('#valoreSSN').html('');
							$(that).find('#tariffaSSN').hide();
						}
						if(valoreSolvente){
							$(that).find('#valoreSolvente').html(valoreSolvente);
							$(that).find('#tariffaSolvente').show();
						}
						else{
							$(that).find('#valoreSolvente').html('');
							$(that).find('#tariffaSolvente').hide();
						}
						if(valoreAlpi){
							$(that).find('#valoreAlpi').html(valoreAlpi);
							$(that).find('#tariffaAlpi').show();
						}
						else{
							$(that).find('#valoreAlpi').html('');
							$(that).find('#tariffaAlpi').hide();
						}
						if(valoreTransferPrice){
							$(that).find('#valoreTransferPrice').html(valoreTransferPrice);
							$(that).find('#transferPrice').show();
						}
						else{
							$(that).find('#valoreTransferPrice').html('');
							$(that).find('#transferPrice').hide();
						}
	                    
	                    $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
	                    	if($(that).find('input[id^=PrezzoFinale_Prezzo]').val()=='' || isNaN($(that).find('input[id^=PrezzoFinale_Prezzo]').val())){
	                    		updateTips( 'Prezzo obbligatorio.' );
	                    		return;
	                    	}
	                    	else{
	                    		$('.validateTips').removeClass("ui-state-highlight").hide();
	                    	}
	                        var newValue='';
	                        myElement=formToElement('dialog-form-prezzo',myElement,folderPrezzi);
	                        mySelectedPrestazione=getDato(myElement.metadata['PrezzoFinale_Prestazione']);
	                        var label=getDato(myElement.metadata['PrezzoFinale_Prezzo']);
        					//if(!label) label=getDato(mySelectedPrestazione.metadata['Costo_TransferPrice']);
        					if(isNaN(label))label='';
	                        newValue=$.axmr.guid(myElement,getDato(myElement.metadata['tp-p_Checked']),label);         
	                        $('#costi').handsontable('setDataAtCell',row,col,newValue);

	                       calcolaTotali();
	                        $("#dialog-form-prezzo").dialog('close');
	                    });
	                    if(!updating){
		               		$(this).parent().find('button:contains(Aggiungi)').remove();
					        $(this).parent().find(':input').not('button').attr('disabled','disabled');
					    } 
	                    
	                });
	                 console.log('ora 2');
	                $("#dialog-form-prezzo").dialog("open");
	                return false;
	            });
            }
            else{
            	
	            $(td).off('dblclick').on('dblclick',function(ev){
	            	ev=ev?ev:window.event;
	                ev.stopPropagation();
	                ev.preventDefault();
	            	$.axmr.deselectGrid('#costi');
	            	return;
	            });
            	if(value){
            	var rowText=$('#costi').handsontable('getDataAtCell',row,0);
            	console.log(value);
            		if(value<0){
            			$(td).css({"background-color":'#F4505E'});
            		}
            		else if(rowText=='Proposta promotore' || rowText =='TP/Proposta promotore'){
            			$(td).css({"background-color":'#F4EC7F'});
            		}
            		else{
            			//$(td).css({"background-color":'#7EF780'});
            			$(td).css({"font-weight":'bold'});
            		}
            	}
            	else{	
            		$(td).css({"background-color":'#CCC'});
            	}
            }
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
          if(value=='Totale per visita' || value=='Valore con markup' || value=='Totale per prestazione' || value=='Totale occorrenze' ){
          		//$(td).css({"background-color":'#00BF00'});
          		$(td).css({"font-weight":'bold'});
          }   
          if(value=='Proposta promotore' || value =='TP/Proposta promotore'){
          		$(td).css({"background-color":'#F7F754'});
          		//$(td).css({"font-weight":'bold'});
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
          minSpareRows:1,
          minSpareCols:1,
          
          rowHeaders:fixRowHeaders,
          minCols: 5,
          minRows: 15,
          colHeaders: fixColHeaders,
          contextMenu: false,
          manualColumnResize:true,
          cells: function (row, col, prop) {
            var cellProperties = {}
            cellProperties.readOnly=!updating;
            if(row==0 || col==0){
            	
            	//cellProperties.type='text';
            	cellProperties.renderer=myTranslateRender;
            } 
            if(row!=0 && col!=0)cellProperties.renderer=myForm3Renderer;  
            return cellProperties;
          }
          
          });
          if(false)
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
              //cellProperties.readOnly=true;
              if(row>0) {
              	cellProperties.renderer=myForm1Renderer;
              	//cellProperties.type='text';
              	/*da sistemare
              	cellProperties.type='autocomplete';
              	//cellProperties.source=prestazioni;
              	cellProperties.options={items: 10};
			      cellProperties.source= function (query, process) {
			      //prod :'${baseUrl}/app/rest/documents/getLinkableElements/185015'
			        $.ajax({
			          url: '${baseUrl}/app/rest/documents/getLinkableElements/'+linkable,
			          data: {
			            term: query
			          },
			          success: function (response) {
			            //console.log("response", response);
			            process(response);
			          }
			        });
			      };*/
              }
              	
              if(col>0) cellProperties.renderer=myForm2Renderer;
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
	              			var myValue=$.axmr.guid(myElement,getDato(myElement.metadata['tp-p_Checked']),getDato(myElement.metadata['PrezzoFinale_Prestazione']));
	              			$('#example').handsontable('setDataAtCell',allChanges[i][0],allChanges[i][1],myValue);
	              		}
	              		else if(myElement){
	              			var myValue=$.axmr.guid(myElement,getDato(myElement.metadata['tp-p_Checked']),getDato(myElement.metadata['PrezzoFinale_Prestazione']));
	              		
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
	              			var myValue=$.axmr.guid(myElement,getDato(myElement.metadata['tp-p_Checked']),getDato(myElement.metadata['PrezzoFinale_Prestazione']));
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
  
          function valorizzaCDC(cdc,item){
          		$(cdc).val(item.value);
          		$(cdc).closest('form').find('input#Prestazioni_UOC').val(item.uo);
				$(cdc).closest('form').find('input#Prestazioni_UOCCode').val(item.uo_code);
				$(cdc).closest('form').find('input#Tariffario_Solvente').val(item.solvente);
				$(cdc).closest('form').find('input#Tariffario_SSN').val(item.ssn);
				$(cdc).closest('form').find('input#Prestazioni_CDCCode').val(item.id);
				if(item.ssn)$(cdc).closest('form').find('.ssn_diz').html(' (Valore SSR: '+item.ssn.formatMoney()+')');
				$(cdc).off('keypress').on('keypress',function (){
					if($(cdc).val()!=item.value){
						var that=cdc;
						/*$('#prestazione-diz-dialog').on('dialogclose',function(){
							$(that).off('keypress');
						});*/
						$(cdc).closest('form').find('.ssn_diz').html('');
						$(cdc).closest('form').find('input#Prestazioni_CDCCode').val('');
						$(cdc).closest('form').find('input#Prestazioni_UOC').val('');
						$(cdc).closest('form').find('input#Prestazioni_UOCCode').val('');
						$(cdc).closest('form').find('input#Tariffario_Solvente').val('');
						$(cdc).closest('form').find('input#Tariffario_SSN').val('');
						$(this).off('keypress');
					}
				});
          }
           $( "#Prestazioni_prestazione" ).autocomplete({
				
				minLength: 2,
				select: function( event, ui ) {
							var request={prestazione:$( "#Prestazioni_prestazione" ).val(),term:''};
							$('#Tariffario_SSN').val(ui.item.ssn);
							$( "#Prestazioni_Codice" ).val(ui.item.id);
							$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
								if(data.length==1){
									valorizzaCDC($( "#Prestazioni_CDC" ),data[0]);
								}
							});
							
							$(this).off('keypress').on('keypress',function(){
								if($(this).val()!=ui.item.value){
									$( "#Prestazioni_CDC" ).val('');
									$( "#Prestazioni_CDC" ).keypress();
									$(this).off('keypress');
								}
							});
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
			$( "#Prestazioni_prestazione" ).change(function(){
				var request={prestazione:$( "#Prestazioni_prestazione" ).val(),term:''};
				$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
					if(data.length==1){
						valorizzaCDC($( "#Prestazioni_CDC" ),data[0]);
					}
				});
			});
			$( "#Prestazioni_CDC" ).off('click').click(function(){
			    $( this ).autocomplete('search','');
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
		        height : 400,
		        width : 450,
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
       
    </@script>

    </div>
    <div>
    <br>
    

    </div>
    </div>
        </div>
        <#assign budget=budgetBase />
<#include "../helpers/budgetStudioStatusBar.ftl"/>
 </div>