<#assign type=model['docDefinition']/>
<@breadcrumbsData el />
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","pace","handsontable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","handsontable","pace","kinetic","budget","base"],
	"inline_scripts":[],
	"title" : "Budget",
 	"description" : "Budget" 
} />
<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#--include "../../partials/form-elements/select.ftl" /-->

<#include "budget/common/style.ftl"/>   
<#include "budget/common/jsLibs.ftl"/>    
<#include "budget/common/loadedJsons2.ftl"/>  
     
<@script>
	var baseData=new Array();
	baseData[0]=new Array();
	<#include "budget/functions/formPrezzo.ftl"/> 
	<#include "budget/functions/setRimborso.ftl"/>  
    <#include "budget/functions/firstLine.ftl"/>    
    <#include "budget/functions/getDato.ftl"/>      
    <#include "budget/functions/updateTips.ftl"/>     
        
       
        
    <#--include "budget/functions/moveBudget.ftl"/-->     
       function moveBudget(){}
        
        //confronta
        <#--include "budget/common/empties.ftl"/-->    
        
        
        var docObj;
        var prepareForDelete=new Array();
        var pxp=new Array();
        var pxs=new Array();
        budgetCTC=true;
        <#include "budget/functions/alertError.ftl"/>    
       	<#include "budget/functions/sortTp.ftl"/>
        <#include "budget/functions/sortPrestazioni.ftl"/>
        <#include "budget/functions/formToElement.ftl"/>
        <#include "budget/functions/elementToForm.ftl"/>
        <#include "budget/functions/prepareMetadataForPost.ftl"/>
        <#include "budget/functions/updateElement.ftl"/>
        <#include "budget/functions/prepareTpxp.ftl"/>
        <#include "budget/functions/saveElement.ftl"/>
        <#include "budget/functions/findElement.ftl"/>
        <#include "budget/functions/deleteElement.ftl"/>
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
                    updatePrezzoTD($(that).find('input[id^=PrezzoFinale_Prezzo]').val(),idx,tipologia)
                    

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
            return false;
       
        }
        
        function updatePrezzoTD(prezzo,idx,tipologia){
        	var id="#tr-tip"+tipologia+"-" + idx ;
        	
			$(id+"  td:nth-child(2)").html(prezzo.formatMoney());
			
        }
		
    $("#dialog-form-cost-2").dialog({
    		autoOpen : false,
    		height : 400,
    		width : 450,
    		modal : true,
    		position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
    		buttons:[
	 		    {
	 				text:"Aggiungi costo", 
	 				click: function() {
	    				var bValid = true;
	    				var tipologia = $("#tipologia2"), descrizione = $("#Prestazioni_prestazione"), costo = $("#costo2"), markupCosto = $("#markup-costo2"), transfer = $("#transfer-costo2"), categoria = $("#interno_esterno"), allFields = $([]).add(tipologia).add(descrizione).add(costo), tips = $(".validateTips");
						var idx=$("#idx").val();
						var update=false;
						if(isNaN(idx) || (!idx && idx!==0))idx=undefined;
						else update=true;
	    				allFields.removeClass("ui-state-error");
	    				bValid = bValid && checkAll(tipologia,descrizione,costo);
	    				/*bValid = bValid && checkLength(name, "username", 3, 16);
	    				bValid = bValid && checkLength(email, "email", 6, 80);
	    				bValid = bValid && checkLength(password, "password", 5, 16);
	    				bValid = bValid && checkRegexp(name, /^[a-z]([0-9a-z_])+$/i, "Username may consist of a-z, 0-9, underscores, begin with a letter.");
	    				// From jquery.validate.js (by joern), contributed by Scott Gonzalez: http://projects.scottsplayground.com/email_address_validation/
	    				bValid = bValid && checkRegexp(email, /^((([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+(\.([a-z]|\d|[!#\$%&'\*\+\-\/=\?\^_`{\|}~]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])+)*)|((\x22)((((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(([\x01-\x08\x0b\x0c\x0e-\x1f\x7f]|\x21|[\x23-\x5b]|[\x5d-\x7e]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(\\([\x01-\x09\x0b\x0c\x0d-\x7f]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))))*(((\x20|\x09)*(\x0d\x0a))?(\x20|\x09)+)?(\x22)))@((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?$/i, "eg. ui@jquery.com");
	    				bValid = bValid && checkRegexp(password, /^([0-9a-zA-Z])+$/, "Password field only allow : a-z 0-9");*/
	    				if(descrizione.val()!='') {
	    					prezzo=$('#prezzo-add').val();
	    					var categoriaVal=(tipologia.val()==3 || tipologia.val()==4)?categoria.val():undefined;
	    					addPrezzo(descrizione.val(),tipologia.val(),transfer.val(),categoriaVal,prezzo,idx,update);
	    					calcolaTotali();
	    					$(this).dialog("close");
	    				}else{
	    					bootbox.alert('Attenzione inserire la descrizione');
	    				}
	    			},
	 				"class" : "btn btn-primary btn-xs"
	 			},
	 			{
	 				text: "Annulla", 
	 				click:function() {
	    				$(this).dialog("close");
	    			},
	 				"class" : "btn btn-xs"
	 			}
	 		],
    		
            open:function(){
            	var width=$(window).width()/100*80;
                var height=$(window).height()/100*80;
                //$(this).dialog('option',{width:width,height:height});
                $(this).dialog('option',{height:height});
                var that=this;
                var setTransfer=function(){
                    if($(that).find('select[id^=unita-markup]').val()==2){
                        var costo=parseFloat($(that).find('input[id^=costo]').val()-0);
                        var aggiunta=costo * parseFloat($(that).find('input[id^=markup]').val()-0) / 100;
                        var value=costo+aggiunta;
                    } else{
                        var value=parseFloat($(that).find('input[id^=costo]').val()-0)+parseFloat($(that).find('input[id^=markup]').val()-0);
                    }
                    $(that).find('input[id^=prezzo]').val(value);
                };
                var setMarkup=function(){
                    if($(that).find('input[id^=prezzo]').val()>0 && $(that).find('input[id^=costo]').val()>0){
                        $(that).find('select[id^=unita-markup]').val(1);
                        var value=parseFloat($(that).find('input[id^=prezzo]').val())-parseFloat($(that).find('input[id^=costo]').val());
                        $(that).find('input[id^=markup]').val(value);
                    }
                };
                $(this).find('input[id^=costo]').off('change').on('change',setTransfer);
                $(this).find('input[id^=markup]').off('change').on('change',setTransfer);
                $(this).find('select[id^=unita-markup]').off('change').on('change',setTransfer);
                $(this).find('input[id^=prezzo]').off('change').on('change',setMarkup);
            },
    		close : function() {
    			allFields.not('.dont-clear').val("").removeClass("ui-state-error");
    		}
    	});
    	
    	$("#create-cost-2").button().click(function() {
    		$("#dialog-form-cost-2").find(':input').not('.dont-clear').val('');
    		//$("#idx").val('');
    		//$('#tipologia2').val(''); 
    		$('#tipologia2').removeAttr('disabled'); 
        	$('#unita-markup-costo2').find('option').removeAttr('selected').prop('selected',false).first().prop('selected',true);
    		$("#dialog-form-cost-2").dialog("open");
    	});
		
        function saveAll(){
        	loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        	var queue=$.when({start:true});
	    	queue=$.when(queue).then(function(data){return saveBulkElements();});
	    	$.when(queue).then(function(data){
	    		if(data.result=='OK'){
	    			updateIds(data.resultMap);
	    			loadingScreen("Salvataggio effettuato!", "${baseUrl}/int/images/green_check.jpg", 1500);
	    			clearSingleNotification('budgetChange');
	    		}else{
					bootbox.hideAll();
					var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
					if(data.errorMessage.includes("RegexpCheckFailed: ")){
						var campoLabel="";
						campoLabel=data.errorMessage.replace("RegexpCheckFailed: ","");
						campoLabel=messages[campoLabel];
						errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
					}
					bootbox.alert(errorMessage);
					//loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
        		}
	    	},function(){loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);});
	    	//$.when(queue).then(function(){location.reload(true);});
	    	return;
        }
		        				
        <#include "budget/functions/sortTpxp.ftl"/>
        <#include "budget/functions/getDataFromObj.ftl"/>
        
        
			var myElementJSON=function(id,callback){
				
			//tp:timepoint,tpxp:prestazione al timepoint x, pxp: prestazione per paziente, pxs; prestazione per lo studio
				<#include "budget/common/docObjDefinition.ftl">
				var instance=this;
				<#include "budget/functions/parseElement2.ftl"/>
				
				
				
				<#include "budget/common/ajaxLoad.ftl"/>
				
			}
			function getFolders(){}
			<#--include "budget/functions/getFolders.ftl"/-->
			

			
					loadingScreen("Caricamento in corso...", "${baseUrl}/int/images/loading.gif");
        
			        if(!updating){
			        	//$(document).ready(function(){
			        		$('form').parent().parent().find('button:contains(Aggiungi)').remove();
			        		$('form').parent().not('[id^=clone]').find(':input').not('button').attr('disabled','disabled');
			        		$('#Salva').remove();
			        	//});
			        }
					
					

				
	               
	                <#include "budget/common/tab1Click.ftl"/>
	                <#include "budget/common/tab3Click.ftl"/>
	                <#include "budget/common/tab4Click.ftl"/>
	                <#include "budget/common/tab2Click.ftl"/>
	                <#include "budget/common/tabNavigation.ftl"/> 
	                
	               		
		    		
		    		
		    		<#--include "budget/common/costiGridEdit.ftl"/> 
		    		<#include "budget/common/flowchartGridEdit.ftl"/--> 
				    <#include "budget/common/prestazioniAutocomplete.ftl"/>      
				  	<#include "budget/common/prepareBracciForm2.ftl"/>
				          
				           
		    		
		    		docObj=new myElementJSON("${model['element'].id}");
	          
            
       	<#include "budget/functions/valorizzaCDC.ftl"/>
        
   
        var prestazioni=['prestazione1','prestazione2'];
        var tps=[];
        
        <#--include "budget/functions/myForm1Renderer.ftl"/>
        <#include "budget/functions/myForm2Renderer.ftl"/>
        <#include "budget/functions/myForm3Renderer.ftl"/>
        <#include "budget/functions/myCheckboxRenderer.ftl"/>
        <#include "budget/functions/myTranslateRender.ftl"/>
        <#include "budget/functions/myCostRenderer.ftl"/-->
        
</@script>