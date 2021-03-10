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
<#assign elStudio=el.getParent().getParent().getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#--include "../../partials/form-elements/select.ftl" /-->

<#include "budget/common/style.ftl"/>   
<#include "budget/common/jsLibs.ftl"/>    
<#include "budget/common/loadedJsons2.ftl"/>  
     
<@script>

	<#include "budget/functions/formPrezzo.ftl"/> 
	<#include "budget/functions/setRimborso.ftl"/>  
    <#include "budget/functions/firstLine.ftl"/>    
    <#include "budget/functions/getDato.ftl"/>      
    <#include "budget/functions/updateTips.ftl"/>     
        
       
        var budgetCTC=false;
        var updating=false
		 var isClosed=false;
		 isUO=true;
		 isPI=false;
		 isCurrPI=false;
		 var authorities={};
		 <#if userDetails.hasRole('PI')> 
		 	isPI=true;
		 	<#if templates?? && templates?size gt 1>
		 		 var isCurrPI=true;
		 	</#if>
		</#if>
			
		 	<#list userDetails.getAuthorities() as auth>
		 		authorities['${auth.getAuthority()}']='${auth.getAuthority()}';
		 	</#list>
		
		 
		 var cantDelete=true;
    <#include "budget/functions/moveBudget.ftl"/>     
       
        
        //confronta
        <#--include "budget/common/empties.ftl"/-->    
        
        
        var docObj;
        var prepareForDelete=new Array();
        var pxp=new Array();
        var pxs=new Array();
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

        function saveAll(){
        	loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        	var queue=$.when({start:true});
	    	queue=$.when(queue).then(function(data){return saveGrid();});
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
        <#include "budget/functions/getDataFromObj_2.ftl"/>
        
        
			var myElementJSON=function(id,callback){
				
			//tp:timepoint,tpxp:prestazione al timepoint x, pxp: prestazione per paziente, pxs; prestazione per lo studio
				<#include "budget/common/docObjDefinition.ftl">
				var instance=this;
				<#include "budget/functions/parseElement.ftl"/>
				
				
				
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
	                
	               		
		    		
		    		
		    		<#include "budget/common/costiGridEdit.ftl"/> 
		    		<#include "budget/common/flowchartGridEdit.ftl"/> 
				    <#include "budget/common/prestazioniAutocomplete.ftl"/>      
				  	<#include "budget/common/prepareBracciForm.ftl"/>
				          
				     <#if (el.getfieldData("ApprovazioneClinica","Approvato")?? && el.getfieldData("ApprovazioneClinica","Approvato")?size>0 && el.getfieldData("ApprovazioneClinica","Approvato")[0]=="1")>
		 			 
		 			 $('#dialog-form').parent().find('button:contains(Aggiungi)').remove();
		 			 $('#dialog-form').find(':input').attr('disabled','disabled');
		 			 $('#dialog-form-transfer').parent().find('button:contains(Aggiungi)').remove();
		 			 $('#dialog-form-transfer').find(':input').attr('disabled','disabled');
		 			 </#if>      
		    		
		    		docObj=new myElementJSON("${model['element'].id}");
	          
            
       	<#include "budget/functions/valorizzaCDC.ftl"/>
        
   
        var prestazioni=['prestazione1','prestazione2'];
        var tps=[];
        
        <#include "budget/functions/myForm1Renderer.ftl"/>
        <#include "budget/functions/myForm2Renderer.ftl"/>
        <#include "budget/functions/myForm3Renderer.ftl"/>
        <#include "budget/functions/myCheckboxRenderer_2.ftl"/>
        <#include "budget/functions/myTranslateRender.ftl"/>
        <#include "budget/functions/myCostRenderer.ftl"/>
        
</@script>