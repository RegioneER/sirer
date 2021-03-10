<#assign type=model['docDefinition']/>
<#global availableTypes={} /> 
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","handsontable"],
	"scripts" : ["budget/axmrTools.js","budget/budgetTools.js","jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","handsontable","base"],
	"inline_scripts":[],
	"title" : "Dettaglio paziente",
 	"description" : "Dettaglio paziente"
} />
<#assign elCentro=el.getParent() />
<#assign elStudio=elCentro.getParent() />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>
	loadingScreen("Caricamento in corso...", "${baseUrl}/int/images/loading.gif");
	var sidebarDefault='${elCentro.getId()}#MonitoraggioPaziente-tab2';
	$.fn.editable.defaults.mode = 'inline';
	$('.field-inline-anchor').editable({
	    params: function(params) {
		    var metadata={};
		    metadata[params.name]=params.value
		   
		    return metadata;
	    },
	    emptytext :"Valore mancante"	
	});
 	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var groupItems=new Array();
 	var empties=new Array();
 	
 	empties[dummy.type.id]=dummy;
    <#if (model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="" || model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="1") >
		<#assign editMonitoraggio=true />
	<#else>
		<#assign editMonitoraggio=false />
	</#if>
    var edit=<#if editMonitoraggio>true<#else>false</#if>;
    <#list elType.getAllowedChilds() as myType>
		<#assign json=myType.getDummyJson() />
		empties['${myType.id}']=empties['${myType.typeId}']=${json};
		<#list myType.getAllowedChilds() as childType>
			<#assign json=childType.getDummyJson() />
			empties['${childType.id}']=empties['${childType.typeId}']=${json};
		</#list>
	</#list>
</@script>

<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#--include "../../partials/form-elements/select.ftl" /-->
<#global page=page + {"scripts": page.scripts + ["select2"], "styles": page.styles + ["select2"]} />
<@script>
$('select').not('#DatiCustomPaziente_Braccio-select').select2({containerCssClass:'select2-ace',allowClear: true});
</@script>
<@breadcrumbsData el />
<#-- link rel="stylesheet" href="${baseUrl}/int/css/budget/jquery.handsontable.full.css" />
<link rel="stylesheet" href="${baseUrl}/int/css/budget/themes/base/jquery-ui.css" />
<link rel="stylesheet" href="${baseUrl}/int/css/budget/base.css" / -->
<@style>
		.ui-autocomplete.ui-menu{
			z-index:9999!important;
		}
		input[type=checkbox]{
			width:auto;
		}
		#Prestazioni_Altro{
			font-size: 14px;
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
		/*input[type=text], select,option {
		    font-size: 1.2vw!important;
		    line-height: 1.3vw;
		   
		}
		#tp-dialog-form input[type=text], select,option {
		    font-size: 1vw!important;
		    line-height: 1.1vw;
		   
		}*/
		.largeTd{
			width:110px;
		}
		.top{
			vertical-align:top;
		}
		.gridLabel{
			background-color:#77EF56;
			color:#FFF;
			width:66px;
			font-weight:bold;
			border-radius:25px;
			padding:0px 10px;
			vertical-align:bottom;
		}
		.gridLabel2{
			background-color:#94CCE8;
			color:#FFF;
			width:66px;
			font-weight:bold;
			border-radius:25px;
			padding:0px 10px;
			vertical-align:bottom;
			
		}
		.gridLabel3{
			background-color:#CCC;
			color:#FFF;
			width:66px;
			font-weight:bold;
			border-radius:25px;
			padding:0px 10px;
			vertical-align:bottom;
		}
		input[type=checkbox]{
			display:inline-block;
		}
		/*label{
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
			}*/
		#monitoraggio th {
			text-align:left;
		}
	    .handsontable tr td{
			vertical-align:bottom;
			padding-bottom:10px;
		}
		/*fix modal form nuova grafica*/
		.ui-dialog-content label{
			display:block;
		}
		.ui-dialog-content #ricoveriList label{
			display:inline-block;
			margin-right:10px;
		}
		.ui-dialog-content input[type=checkbox]{
			vertical-align: middle;
		}
		.dragdealer.horizontal,.dragdealer.horizontal .handle{
			height:17px;
		}
		.dragdealer.vertical,.dragdealer.vertical .handle{
			width:17px;
		}
		.handle{
			cursor:grab;
		}
	</@style>
<#-- script  src="/js/budget/axmrTools.js"></script>
<script  src="/js/budget/budgetTools.js"></script>
<script  src="/js/budget/jquery.handsontable.full.js"></script>

<script src="/js/budget/ui/jquery.ui.widget.js"></script-->


<@script>
	function updateIds(map){
		var currElement;
		if(map &&  ($.isArray(map) || $.isPlainObject(map))){
			$.each(map, function(guid,id){
				currElement=$.axmr.guid(guid);
				if(currElement &&  ($.isPlainObject(currElement) || $.isArray(currElement))){
					currElement.id=id;
				}
			});
		}
		window.onbeforeunload = function() {
			
			return;
		}
	}
	
	var oldSaveUpdateField=saveUpdateField;
	saveUpdateField=function(idField){
		oldSaveUpdateField(idField);
		braccioFilter=$('#DatiCustomPaziente_Braccio_value').text();
		$('#monitoraggio').handsontable('render');
	}
	var braccioFilter;
	
    <#if (model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="" || model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="1") >
		<#assign editMonitoraggio=true />
	<#else>
		<#assign editMonitoraggio=false />
	</#if>
    var edit=<#if editMonitoraggio>true<#else>false</#if>;
   
    var docObj;
    
    var fatturabili={};
    var lastCompleta=0;
    var firstCompleta=0 ;
    function saveAll(){
		loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
		var totFatturabili=0;

		$.each(fatturabili,function(i,myElement){
			if(myElement && myElement.metadata && getDato(myElement.metadata['DatiMonTimePoint_Fatturabile'])){
				totFatturabili+=1;
				var currData=getDato(myElement.metadata['DatiMonTimePoint_DataVisita']);
				if(currData.toString().match(/\//)){
					var st = currData;
					var pattern = /(\d{2})\/(\d{2})\/(\d{4})/;
					var dt = new Date(st.replace(pattern,'$3-$2-$1'));
					currData=dt.getTime();
				}
				lastCompleta=Math.max(lastCompleta,currData);
				if(firstCompleta==0 && !isNaN(currData) && currData>0){
					firstCompleta=currData;
				}
				firstCompleta=Math.min(firstCompleta,currData);
			}
		})
	
		loadedElement.metadata['DatiCustomPaziente_VisiteFatturabili']=totFatturabili;
		loadedElement.metadata['DatiCustomPaziente_UltimaVisitaCompletata']=lastCompleta;
		loadedElement.metadata['DatiCustomPaziente_PrimaVisitaCompletata']=firstCompleta;
		loadedElement.metadata['DatiCustomPaziente_Braccio']=$('#DatiCustomPaziente_Braccio-select').val();
		delete loadedElement.metadata['StatoPaziente_Stato'];
		var queue=$.when({start:true});
		var folders={};
		folders[empties['MonTimePoint'].type.id]=folderTp;
		folders[empties['MonPrestazioni'].type.id]=folderPrestazioni;
		folders[empties['MonPxT'].type.id]=folderTpxp;
		queue=$.when(queue).then(function(data){
			return saveGrid('#monitoraggio','DatiMonPxT_MonTimePoint','DatiMonPxT_MonPrestazione','GridY_row','GridX_col',folders,null,true);
		});
		queue=$.when(queue).then(function(data){
			updateIds(data.resultMap);
			return saveElement(loadedElement);
		});
		$('[name=DatiMonPxP_Fatturabile]').each(function(){
			var that=this;
			queue=$.when(queue).then(function(){return savePrestazione(that);});
		});
		$.when(queue).then(function(){loadingScreen("Salvataggio effettuato!", "${baseUrl}/int/images/green_check.jpg", 1500);clearSingleNotification('budgetChange');if((!loadedBraccio && $('#DatiCustomPaziente_Braccio-select').val()) || loadedBraccio!=$('#DatiCustomPaziente_Braccio-select').val()){loadingScreen("Caricamento in corso...", "loading");location.reload(true);}});
	    return;
		
	}
	
	function savePrestazione(object){
		var element={id:'',metadata:{}};
		element.id=object.id;
		element.metadata['DatiMonPxP_Fatturabile']=object.value;
		return updateElement(element);
	}
	
    function prepareTpxp(value,p,tp,old){
    	
    	var myElement=$.axmr.guid(old);
    	if(!myElement){	
    		console.log('noooooo');
    		myElement=$.extend(true,{},empties['MonPxT']);
    		return false;
    	}
    	$.axmr.deselectGrid('#monitoraggio');
    	
    	if(value){
    		myElement.metadata['DatiMonPxT_Eseguito']=1;
    	}else{
    		myElement.metadata['DatiMonPxT_Eseguito']='';
    	}
    	myElement.coordinates={x:tp,y:p};
    	$.axmr.setUpdated(myElement);
    	return myElement;
    	
    }
    
    function sortTp(a,b){
    	if(parseInt(getDato(a.metadata['DatiMonTimePoint_TimePoint'][0].metadata['TimePoint_col']))>parseInt(getDato(b.metadata['DatiMonTimePoint_TimePoint'][0].metadata['TimePoint_col']))){return 1;}
    	else if(parseInt(getDato(a.metadata['DatiMonTimePoint_TimePoint'][0].metadata['TimePoint_col']))<parseInt(getDato(b.metadata['DatiMonTimePoint_TimePoint'][0].metadata['TimePoint_col']))){return -1;}
    	else{
    		return 0;
    	}
    }
    
    function sortPrestazioni(a,b){
    	if(parseInt(getDato(a.metadata['DatiMonPrestazioni_Prestazione'][0].metadata['Prestazioni_row']))>parseInt(getDato(b.metadata['DatiMonPrestazioni_Prestazione'][0].metadata['Prestazioni_row']))){return 1;}
    	else if(parseInt(getDato(a.metadata['DatiMonPrestazioni_Prestazione'][0].metadata['Prestazioni_row']))<parseInt(getDato(b.metadata['DatiMonPrestazioni_Prestazione'][0].metadata['Prestazioni_row']))){return -1;}
    	else{
    		return 0;
    	}
    }
    
    function getDataFromObj(myObject){
    	var result=new Array();
    	var currRow=new Array();
		currRow[0]='';
		$.each(myObject.tp,function(k,currTp){
			
			currRow[k+1]=$.axmr.guid(currTp,buildTpDescription(currTp.metadata['DatiMonTimePoint_TimePoint'][0]));
			currTp.coordinates={x:k+1,y:1};
		});
		result[0]=currRow;
    	$.each(myObject.prestazioni, function(i,currPrestazione){
    		var row=i+1;
    		var rifPrestazione=currPrestazione.metadata['DatiMonPrestazioni_Prestazione'][0];
    		var labelPrestazione=getDato(rifPrestazione.metadata['Prestazioni_Codice']);
			if(!labelPrestazione)labelPrestazione='';
			else labelPrestazione+=' '
	        labelPrestazione+=getDato(rifPrestazione.metadata['Prestazioni_prestazione']);
	    	/*if(labelPrestazione.length>18){
	    		labelPrestazione=labelPrestazione.substr(0,15)+'...';
	    	}*/
    		currRow=new Array();
    		currRow[0]=$.axmr.guid(currPrestazione,labelPrestazione);
    		currPrestazione.coordinates={x:1,y:i+1};
    		for(var col=1;col<result[0].length;col++){
    			currRow[col]='';
    		}
    		result[row]=currRow;
    	});
    	$.each(myObject.tpxp, function(i,currTpxp){
    		var prestaAssoc;
    		var tpAssoc;
    		if(getDato(currTpxp.metadata['DatiMonPxT_MonPrestazione'])>0) prestaAssoc=$.axmr.getById(getDato(currTpxp.metadata['DatiMonPxT_MonPrestazione']));
    		if(getDato(currTpxp.metadata['DatiMonPxT_MonTimePoint'])>0) tpAssoc=$.axmr.getById(getDato(currTpxp.metadata['DatiMonPxT_MonTimePoint']));
    		if(prestaAssoc && tpAssoc)result[prestaAssoc.coordinates.y][tpAssoc.coordinates.x]=$.axmr.guid(currTpxp,getDato(currTpxp.metadata['DatiMonPxT_Eseguito']));
    	});
    	return result;
    }
    
    var myCheckboxRenderer = function (instance, td, row, col, prop, value, cellProperties) {
     $(td).removeAttr('title');
	  $(td).off('click').off('dblclick').on('click',function(){
	  	$.axmr.deselectGrid('#monitoraggio');
	  }).on('dblclick',function(){
	  	$.axmr.deselectGrid('#monitoraggio');
	  })
	  ;
      var enabled=false;
      if(value || value===false ){
      	enabled=true;
      }
     
      
      var test=$.axmr.label(value);
      var grey=false;
      var myElement=$.axmr.guid(value);;
      if(enabled && braccioFilter && value && myElement && $.isPlainObject(myElement)){
      	var bracciAbilitati=getDato(getDato(myElement.metadata['DatiMonPxT_TPxP']).metadata['Costo_Braccio']);
      	var regex="\\|"+braccioFilter+"\\|";
      	if(bracciAbilitati && !bracciAbilitati.match(regex)){
      		enabled=false;
      	}
      }
      if(arguments[5]!== undefined &&  arguments[5]!== null &&  ($.trim(test.toString()).match(/^x$/i) || test===true || test==1))arguments[5]=true;
      else if(arguments[5]!==null && arguments[5]!='true' && arguments[5]!==true ){
          arguments[5]=false;
      }
      if($.isPlainObject(myElement)){
      	var columnTp=$.axmr.guid(instance.getDataAtCell(0,col));
      	if(!edit || getDato(columnTp.metadata['DatiFatturazioneTP_ReportFatturazione'])){
      		cellProperties.readOnly=true;
      		grey=true;
      	}
      }
      Handsontable.CheckboxCell.renderer.apply(this, arguments);
      
      if(enabled){
      	$(td).find('input').show();
      }
      else{
      	$(td).find('input').hide();
      	$(td).find('input').each(function(){
      		this.checked=false;
      	});
      }
      if(grey){
      	$(td).find('input').fadeTo(0, 0.5);;
      }
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
      $(td).attr('title',label);
      if(label && label.length>15){
      	label=label.substr(0,15)+'...';
      }
      $(td).html(label);
    };
        
    var myElementJSON=function(id,callback){
		
		//tp:timepoint,tpxp:prestazione al timepoint x, pxp: prestazione per paziente, pxs; prestazione per lo studio
		this.elements={tp:[],prestazioni:[],tpxp:[],pxp:[],pxs:[],tpxp2update:[],tpxp2delete:[],pxs2delete:[],pxp2delete:[],budgetStudio:[],pxpCTC:[],pxsCTC:[],passthroughCTC:[],bracci:[]};
		var instance=this;
		function parseElement(data){
			instance.elements.globalData=data;
			if(data.children && data.children.length>0){
					$.each(data.children,function(index,child){
						var type=child.type.typeId;
						
						switch(type){
							case 'FolderMonTimePoint':
								folderTp=child.id;
								instance.elements.tp=child.children;
								instance.elements.tp.sort(sortTp);
							break;
							case 'FolderMonPrestazioni':
								folderPrestazioni=child.id;
								instance.elements.prestazioni=child.children;
								instance.elements.prestazioni.sort(sortPrestazioni);
							break;
							case 'FolderMonPxT':
								folderTpxp=child.id;
								instance.elements.tpxp=child.children;
								//instance.elements.tpxp2update=sortTpxp2update(child.children);
							break;
							case 'FolderPXP//':
								folderPxp=child.id;
								instance.elements.pxp=child.children;
							break;
							case 'FolderPXS//':
								folderPxs=child.id;
								instance.elements.pxs=child.children;
							break;
							case 'FolderPXPCTC//':
								folderPxpCTC=child.id;
								instance.elements.pxpCTC=child.children;
							break;
							case 'FolderPXSCTC//':
								folderPxsCTC=child.id;
								instance.elements.pxsCTC=child.children;
							break;
							case 'FolderPassthroughCTC//':
								folderPassthroughCTC=child.id;
								instance.elements.passthroughCTC=child.children;
							break;
							case 'FolderBudgetStudio//':
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
				}else{
					$.each(groupItems,function(index,child){
						var type=child.type.typeId;
						switch(type){
							case 'FolderMonTimePoint':
								folderTp=child.id;
								
							break;
							case 'FolderMonPrestazioni':
								folderPrestazioni=child.id;
								
							break;
							case 'MonTimePoint':
								instance.elements.tp[instance.elements.tp.length]=child;
							break;
							case 'MonPrestazioni':
								instance.elements.prestazioni[instance.elements.prestazioni.length]=child;
							break;
							case 'MonPxT':
								instance.elements.tpxp[instance.elements.tpxp.length]=child;
							break;
							case 'MonPxP':
							case 'MonPxPCTC':
								instance.elements.pxp[instance.elements.pxp.length]=child;
							break;
							case 'MonBraccio':
								instance.elements.bracci[instance.elements.bracci.length]=child;
							break;
							case 'FolderMonPxT':
								folderTpxp=child.id;
							break;
							
						}
						instance.elements.tp.sort(sortTp);
						instance.elements.prestazioni.sort(sortPrestazioni);
					});
				}
				instance.elements.tpxp2update=$.extend(true,[],instance.elements.tpxp);
				var data=getDataFromObj(instance.elements);
				var handsontable = $('#monitoraggio').data('handsontable');
				if(handsontable)handsontable.loadData(data);
			   
 				
	        	if(callback) callback(instance);
	        	toggleLoadingScreen();

		}
		
		
		if(loadedElement && groupItems && groupItems.length>0){
			parseElement(loadedElement);
		}
		else{
			//Pace.restart();
			(function(){
				$.ajax({
					dataType: "json",
					url:'${baseUrl}/app/rest/documents/'+loadedElement.id+'/getGrouppedElements'
				}).done(function(data){
						groupItems=data;
						parseElement(loadedElement);
					}
					).fail(alertError);
			})();
		}
		/*
		if(loadedElement && false){
			parseElement(loadedElement);
		}
		else{
			(function(){
				$.ajax({
					dataType: "json",
					url:'../../rest/documents/getElementJSON/'+loadedElement.id+'?level=3&rule=complete'
				}).done(function(data){parseElement(data);toggleLoadingScreen();}).fail(alertError);
			})();
		}	
		*/
}
	
	var timepointForm=function(ev,col,myElement,value,cleanLabel,td){
			var label='';
			
			if(!edit || getDato(myElement.metadata['DatiFatturazioneTP_ReportFatturazione'])){
				return false;
			}
	        console.log('hoclickato3');
	        ev=ev?ev:window.event;
	        ev.stopPropagation();
	        ev.preventDefault();
	       console.log('hoclickato4');
	        $("#tp-dialog-form").off('dialogopen').on('dialogopen',function(ev){
	        console.log('hoclickato5');
	            var width=$(window).width()/100*80;
	            var height=$(window).height()/100*80;
	            //$(this).dialog('option',{width:width,height:height});
	            ev=ev?ev:window.event;
	            var that=this;
	            $.axmr.deselectGrid('#monitoraggio');
	            var myElement=$.axmr.guid(value);
	            if(myElement){
	            	elementToForm(myElement,'tp-dialog-form');
	            	$('#tp-dialog-form').find('[name=col]').val(col);
	            	var elementDate=$('#DatiMonTimePoint_DataVisita').val()+'';
	            	if(!elementDate.match('/') && elementDate){
	                	var d = new Date(parseInt(elementDate));					
						var date=pad(d.getDate(),2)+'/'+pad((d.getMonth()+1),2)+'/'+d.getFullYear();
						$('#DatiMonTimePoint_DataVisita').val(date);
					}
	            	$('#TimePoint_Descrizione').html($.axmr.label(value));
	           	}
	            else{
	            console.log('no',myElement);
	            	$(this).dialog('close');
	            	return;
	            	//elementToForm(empties['MonTimePoint'],'tp-dialog-form');
	            }
	    
	            var that=this;
	            $(this).parent().find('button:contains(Applica)').off('click').on('click',function(){
	                var checkAll=true;
	                $(that).find('input[type=text]').each(function(){
	                	if(!$(this).val()){
	                		checkAll=false;
	                	}
	                });
	                $(that).find('#DatiMonTimePoint_Fatturabile').each(function(){
	                	if(!this.checked){
	                		checkAll=true;
	                	}
	                });
	                if(!checkAll){
	                	alert('Compilare tutti i campi per la visita.');
	                	return;
	                }
	                
	                myElement.coordinates={x:col,y:0};
	                formToElement('tp-dialog-form',myElement); 
	                $('#monitoraggio').handsontable('render');
	                label="<div class='top'>"+label+"</div>";
	                if(getDato(myElement.metadata['DatiFatturazioneTP_ReportFatturazione'])){
	                	label+='<div class="gridLabel3">Chiuso</div>';
			        	var col2=parseInt(col)+2;
			        	$(td).closest('table').find('colgroup col:nth-child('+col2+')').css({"min-width":'95px'});
			        	$(td).html(label);
			        	$(td).find('.gridLabel').remove();
	                }
	                else if(getDato(myElement.metadata['DatiMonTimePoint_Fatturabile'])){
	                	label=cleanLabel+'<div class="gridLabel">Completa</div>';
			        	var col2=parseInt(col)+2;
			        	$(td).closest('table').find('colgroup col:nth-child('+col2+')').css({"min-width":'95px'});
			        	$(td).html(label);
			        	$(td).find('.gridLabel2').remove();
			        }else{
			        	label+='<div class="gridLabel2">Chiudi</div>';
			        	var col2=parseInt(col)+2;
			        	$(td).closest('table').find('colgroup col:nth-child('+col2+')').css({"min-width":'95px'});
			        	$(td).html(label);
			        	$(td).find('.gridLabel').remove();
			        }    
	                $("#tp-dialog-form").dialog('close');
	                 console.log('2ui');
	            });
	            console.log('1ui');
	            
	            
	        });
	        $("#tp-dialog-form").dialog("open");
	        return false;
	};
	
	var myForm1Renderer = function (instance, td, row, col, prop, value, cellProperties) {
            
        Handsontable.TextCell.renderer.apply(this, arguments);
        var label=$.axmr.label(value);
        var cleanLabel=label;
        var myElement=$.axmr.guid(value);
        if(myElement && myElement.metadata && getDato(myElement.metadata['DatiMonTimePoint_Fatturabile'])){
				fatturabili[myElement.id]=myElement;
		}
        if(td){
        	if(label)label="<div class='top'>"+label+"</div>";
        	if(myElement && getDato(myElement.metadata['DatiFatturazioneTP_ReportFatturazione'])){
            	label+='<div class="gridLabel3">Chiuso</div>';
	        	var col2=parseInt(col)+2;
	        	$(td).closest('table').find('colgroup col:nth-child('+col2+')').css({"min-width":'95px'});
	        	$(td).html(label);
	        	$(td).find('.gridLabel').remove();
            }
            else if(myElement && getDato(myElement.metadata['DatiMonTimePoint_Fatturabile'])){
	        	label+='<div class="gridLabel">Completa</div>';
	        	var col2=parseInt(col)+2;
	        	$(td).closest('table').find('colgroup col:nth-child('+col2+')').css({"min-width":'95px'});
	        }
	        else{
	        	if(label)
	        	label+='<div class="gridLabel2">Chiudi</div>';
	        	var col2=parseInt(col)+2;
	        	$(td).closest('table').find('colgroup col:nth-child('+col2+')').css({"min-width":'95px'});
	        }
        
	        $(td).html(label);
	        $(td).off('click').on('click',function(ev){
	        	$.axmr.deselectGrid('#monitoraggio');
	        	return true;
	        });
	        $(td).off('click').on('click',function(ev){
	        	ev=ev?ev:window.event;
	            ev.stopPropagation();
	            ev.preventDefault();
	            
	            $(this).dblclick();
	            
	        });
	        $(td).off('dblclick').on('dblclick',function(ev){
	        	timepointForm(ev,col,myElement,value,cleanLabel,td);
	        }).css({
	            color: 'black'
	        });
        }
    };
	var myTimer=null;
	var myTime2r=null;
	var rowHeaderWidth=22;
		$("#tp-dialog-form").dialog({
			autoOpen : false,
			height : 400,
			width : 450,
			modal : true,
			position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
			buttons : [
			{
				text: "Applica modifiche", 
				click: function() {
					
				},
				"class" : "btn btn-xs btn-primary"
			},
			{
				text: "Annulla", 
				click: function() {
					$(this).dialog("close");
				},
				"class" : "btn btn-xs "
			}],
			close : function() {
				var allFields=$(this).find('input[type=text]');
				allFields.val("").removeClass("ui-state-error");
			}
		});
		$('#monitoraggio').handsontable({
          width: 1200,
          height:800,
          minSpareRows:20,
          minSpareCols:10,
          startRows: 20, 
          colHeaders:function(col){
          	var header=$.axmr.label(this.data[0][col]);
          	if(header){
          		header=header.replace(/\n/g,"<br>");
          	}else{
          		header='';
          	}
          	myTimer=setTimeout(function(){
          		clearTimeout(myTimer);
          		if($('[data-row=0]').size()>0){
          			$('.my-col-headers').hide();
          		}else{
          			$('.my-col-headers').show();
          			$('.my-col-headers').each(function(){
          				$(this).closest('th').off('click').on('click',function(ev){
          				console.log('hoclickato1');
          					var that=$(this).find('.my-col-headers');
          					var value=that.data('guid');
          					console.log(value);
          					var myElement=$.axmr.guid(value);
          					timepointForm(ev,that.data('colHeader'),myElement,value,header,null);
          					//$("#tp-dialog-form").dialog("open");
          					console.log('hoclickato2');
          				});
          			});
          		}
          	},200);
          	if($('[data-row=0]').size()>0) var display=' style="display:none" ';
          	else  display=' style="display:inline" ';
            return "<span class='my-col-headers' "+display+" data-colHeader='"+col+"' data-guid='"+this.data[0][col]+"' >"+header+"</span>";
          },
          rowHeaders:function(row){
          	var header=$.axmr.label(this.data[row][0]);
          	if(header){
          		header=header.replace(/\n/g,"<br>");
          	}else{
          		header='';
          	}
          	myTimer2=setTimeout(function(){
          	console.log('log');
          		clearTimeout(myTimer2);
          		if($('[data-column=0]').size()>0){
          			$('.my-row-headers').hide();
          			
          			$(".rowHeader").each(function(){
          				rowHeaderWidth=Math.max($(this).next().width(),rowHeaderWidth);
		          		$(this).css({"width": '22px'});
		          	});
          		}else{
          			$('.my-row-headers').show();
          			$(".rowHeader").each(function(){
		          		$(this).css({"width": rowHeaderWidth});
		          	});
          		}
          	},200);
          	
          	if($('[data-column=0]').size()>0) var display=' style="display:none" ';
          	else  display=' style="display:inline" ';
            return "<span class='my-row-headers' "+display+" data-rowHeader='"+row+"' data-guid='"+this.data[row][0]+"' >"+header+"</span>";
          },
          minCols: 0,
          minRows: 0,
          manualColumnResize:true,
          
          contextMenu: false,
          
          cells: function (row, col, prop) {
            var cellProperties = {}
            
            if(row==0 || col==0){
            	cellProperties.readOnly=true;
            	if(col==0) cellProperties.renderer=myTranslateRender;
            	else cellProperties.renderer=myForm1Renderer;
            	
            } 
			else{
				cellProperties.renderer=myCheckboxRenderer;
			}
            return cellProperties;
          },
          afterChange: function(changes, source) {
             
              
              if( changes!==null){
              //console.log('qui');
              	  var allChanges=clone(changes);
              	  while($.isArray(changes[0])){
              	  		allChanges=changes;
              	  		changes=changes[0];
              	  }
				
	              for(var i=0;i<allChanges.length;i++){
					
	              	if(allChanges[i]!==undefined && $.isArray(allChanges[i]) && allChanges[i][0]>0 && allChanges[i][1]>0 ){
	              		var myElement=$.axmr.guid(allChanges[i][3]);
	              		if(!myElement){
	              			myElement=prepareTpxp(allChanges[i][3],allChanges[i][0],allChanges[i][1],allChanges[i][2]);
	              			if(myElement){
		              			var myValue=$.axmr.guid(myElement,getDato(myElement.metadata['DatiMonPxT_Eseguito']));
		              			$('#monitoraggio').handsontable('setDataAtCell',allChanges[i][0],allChanges[i][1],myValue);
	              			}
	              		}
	              		
	              		
	              	}
	              	
	              	//$('#costi').handsontable('setDataAtCell',changes);
	              }
              }
              
          }
          
        });
        function selezionaTutti(button){
        	var col=$(button).closest('form').find('[name=col]').val(); 
        	var data=$.extend(true,[],$('#monitoraggio').data('handsontable').getData());
        	for(var j=1;j<data.length;j++){
        		if($.isArray(data[j])){
	        	
        			var currElement=$.axmr.guid(data[j][col]);
        			if($.isPlainObject(currElement)){
        				var enabled=true;
        				if(braccioFilter ){
					      	var bracciAbilitati=getDato(getDato(currElement.metadata['DatiMonPxT_TPxP']).metadata['Costo_Braccio']);
					      	var regex="\\|"+braccioFilter+"\\|";
					      	if(bracciAbilitati && !bracciAbilitati.match(regex)){
					      		enabled=false;
					      	}
					      }
					      
					     
					      
				      	var columnTp=$.axmr.guid(data[0][col]);
				      	if(!edit || getDato(columnTp.metadata['DatiFatturazioneTP_ReportFatturazione'])){
				      		enabled=false;
				      	}
				      	if(enabled){
				      		currElement.metadata['DatiMonPxT_Eseguito']="1";
				      		$.axmr.guid(currElement,"1");
				      		$.axmr.setUpdated(currElement);
				      	}
					      
        			}
	        		
        		}
        	}
        	$('#monitoraggio').handsontable('render');
        }
        docObj=new myElementJSON();  
</@script>