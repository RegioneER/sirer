<style>
	
//div[id^=informations-FeasibilityServizi_FRESP],div[id^=informations-FeasibilityFarm_FRESP],div[id^=informations-FeasibilityInfermiere_FRESP],div[id^=informations-FeasibilityInfermiere_Espletamento],div[id^=informations-FeasibilityInfermiere_Costi],div[id^=informations-FeasibilityInfermiere_ElencoAzioni],div[id^=informations-FeasibilityInfermiere_InOrario],div[id^=informations-FeasibilityInfermiere_FuoriOrario],div[id^=informations-FeasibilityInfermiere_ParzInOrario],div[id^=informations-FeasibilityInfermiere_ParzFuoriOrario],div[id^=informations-FeasibilityInfermiere_Durata],div[id^=informations-FeasibilityFarm_Farmaco],div[id^=informations-FeasibilityFarm_FornituraSponsor],div[id^=informations-FeasibilityFarm_FarmaciStruttura],div[id^=informations-FeasibilityFarm_FarmaciStruttura],div[id^=informations-FeasibilityFarm_Disponibilita],div[id^=informations-FeasibilityFarm_RicezioneFarmaco],div[id^=informations-FeasibilityFarm_TenutaCieco],div[id^=informations-FeasibilityFarm_PreparazioneFarmaco],div[id^=informations-FeasibilityFarm_Esecuzione],div[id^=informations-FeasibilityFarm_Allestimento],div[id^=informations-FeasibilityFarm_RicostruzioneDiluizione],div[id^=informations-FeasibilityFarm_ConfMasch],div[id^=informations-FeasibilityFarm_Altro],div[id^=informations-FeasibilityFarm_ClassificazioneStudio] {
//float: left;
//width: 60%;
//}
//div[id^=informations-FeasibilityServizi_noteFRESP],div[id^=informations-FeasibilityFarm_noteFRESP],div[id^=informations-FeasibilityInfermiere_noteFRESP] {
//float: left;
//width: 40%;
//border-width: 0 0 1px;
//}
//label[for^=FeasibilityServizi_FRESP],label[for^=FeasibilityFarm_FRESP],label[for^=FeasibilityInfermiere_FRESP],label[for^=FeasibilityInfermiere_ElencoAzioni] {
//width: 95%;
//}
//
//
//div[id=informations-FeasibilityFarm_Allestimento],div[id=informations-FeasibilityFarm_RicostruzioneDiluizione],div[id=informations-FeasibilityFarm_Altro]  {
//float: left;
//width: 60%;
//}
//div[id=informations-FeasibilityFarm_AllestimentoNote],div[id=informations-FeasibilityFarm_RicostruzioneDiluizioneNote],div[id=informations-FeasibilityFarm_AltroNote] {
//float: left;
//width: 40%;
//border-width: 0 0 1px;
//}
//label[for^=FeasibilityFarm_Allestimento],label[for^=FeasibilityFarm_RicostruzioneDiluizione],label[for^=FeasibilityFarm_Altro]{
//width: 95%;
//}
//
//
//td[id=td-field-FeasibilityInfermiere_Espletamento],
//td[id=td-field-FeasibilityInfermiere_Infermieri],
//td[id=td-field-FeasibilityInfermiere_TecniciLab],
//td[id=td-field-FeasibilityInfermiere_TecniciRad],
//td[id=td-field-FeasibilityInfermiere_Fisioterapisti],
//td[id=td-field-FeasibilityInfermiere_AltrePersone],
//td[id=td-field-FeasibilityInfermiere_ServiziSezioni],
//td[id=td-field-FeasibilityInfermiere_ElencoAzioni],
//td[id=td-field-FeasibilityInfermiere_InOrario],
//td[id=td-field-FeasibilityInfermiere_FuoriOrario],
//td[id=td-field-FeasibilityInfermiere_ParzInOrario],
//td[id=td-field-FeasibilityInfermiere_ParzFuoriOrario],
//td[id=td-field-FeasibilityInfermiere_Durata],
//td[id=td-field-FeasibilityFarm_Farmaco],
//td[id=td-field-FeasibilityFarm_FornituraSponsor],
//td[id=td-field-FeasibilityFarm_FarmaciStruttura],
//td[id=td-field-FeasibilityFarm_Disponibilita],
//td[id=td-field-FeasibilityFarm_RicezioneFarmaco],
//td[id=td-field-FeasibilityFarm_TenutaCieco],
//td[id=td-field-FeasibilityFarm_PreparazioneFarmaco],
//td[id=td-field-FeasibilityFarm_Esecuzione],
//td[id=td-field-FeasibilityFarm_Allestimento],
//td[id=td-field-FeasibilityFarm_RicostruzioneDiluizione],
//td[id=td-field-FeasibilityFarm_ConfMasch],
//td[id=td-field-FeasibilityFarm_Altro],
//td[id=td-field-FeasibilityFarm_AllestimentoNote],
//td[id=td-field-FeasibilityFarm_RicostruzioneDiluizioneNote],
//td[id=td-field-FeasibilityFarm_AltroNote]
//{
//background-image: url("/img/arrow_pdf.jpg");
//background-repeat: no-repeat;
//background-position: right;
//padding-right: 45px !important;
//}


#form-FeasibilityAreaME .radio {
float:left;
}
#form-FeasibilityAreaBS .radio {
float:left;
}
#form-FeasibilityAreaGA .radio {
float:left;
}
#form-FeasibilityAreaAC .radio {
float:left;
}

td[id^=td-label-DatiFeasibilityArea]{
width: 80% !important;
}

td[id^=td-field-DatiFeasibilityArea]{
width: 20% !important;
}

#DatiFeasibilityAreaAC_FAC3{
width: 100px;
}

</style>

<#include "../helpers/MetadataTemplate.ftl"/>

<div id="processes">
	<#assign activeProcess=false/>
	<#if model["activeProcesses"]??>
  	<#list model["activeProcesses"] as ist>
  		<#assign activeProcess=true/>
  	</#list>
	</#if>
	<#if !activeProcess>
		<#if model["availableProcesses"]??>
    	<#list model["availableProcesses"] as wf>
    		<#list el.type.associatedWorkflows as p>
    			<#if !p.startOnCreate && p.enabled && wf.key=p.processKey>
    				<#assign alreadyTerminated=false/>
    					<#if model['terminatedProcesses']??>
								<#list model['terminatedProcesses'] as tpInst>
									<#if tpInst.getProcessDefinitionId()?split(":")[0]=wf.key>
										<#assign alreadyTerminated=true/>
									</#if>
								</#list>
							</#if>
							<#if !alreadyTerminated>
								<input id="startProcess" action="${wf.key}" class="submitButton round-button blue startProcess btn btn-info" type="button" value="${wf.name}"><br/>	
            	</#if>
    			</#if>
    	  </#list>
    	</#list>
		</#if>
	</#if>
	
	
	<#assign ValRespIstr="" />
	<#if el.parent.getfieldData("statoValidazioneCentro","valCTC")[0]??>
		<#assign ValRespIstr=el.parent.getFieldDataCode("statoValidazioneCentro","valCTC") />
	</#if>
	
	<#--GC 01/02/2015 - Nascondo il bottone del processo di valutazione se l'istruttoria NRC è positiva o negativa--> 			
	<#if ValRespIstr=="1" || ValRespIstr=="2">
		<#assign editable=false />
	<#else>
		<div id="task-Actions" style="text-align: right"></div>
	</#if>
	
</div>


<#list el.templates as template>
	<#if template.name="DatiFeasibilityAreaME" || template.name="DatiFeasibilityAreaBS" || template.name="DatiFeasibilityAreaGA" || template.name="DatiFeasibilityAreaAC">

	<fieldset class="vs">
		<legend>Istruttoria <@elementTitle el/></legend>
	</fieldset>
					 
					  <#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	    <#list el.elementTemplates as elementTemplate>
	    	<#if elementTemplate.metadataTemplate.name=template.name && elementTemplate.enabled>	
	    		
					 <!-- DIV IMPORTANTISSIMO PER DIFFERENZIARE I CONTENUTI NEI VARI TAB-->
					 <div id="metadataTemplate-${template.name}" class="allInTemplate">
				
						<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
							<#assign formEdit=false>
	    				<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
	    					<#assign formEdit=true>
      					<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
							</#if>
							
							<table class="table table-bordered" id="checklist">
								<thead>
									<tr><th colspan="2">Attivit&agrave; di valutazione PRE CESC</th></tr>
								</thead>
							<tbody>
							
							<#list template.fields as field>
	    				
		    				<#--if field.name="FRESP1">
		    					<tr><td colspan="2" style="background-color:#DDDDDD"><b>Promotore</b></td></tr>
		    				</#if>
		    				
		    				<#if field.name="FRESP3">
			    				<tr><td colspan="2" style="background-color:#DDDDDD"><b>Clinical Research Organization (CRO)</b></td></tr>
		    				</#if>
		    				
		    				<#if field.name="FRESP5">
		    					<tr><td colspan="2" style="background-color:#DDDDDD"><b>Protocollo</b></td></tr>
		    				</#if>
		    				
		    				<#if field.name="FRESP8">
		    					<tr><td colspan="2" style="background-color:#DDDDDD"><b>Procedure</b></td></tr>
		    				</#if>
		    				
		    				<#if field.name="FRESP9">
		    					<tr><td colspan="2" style="background-color:#DDDDDD"><b>Staff</b></td></tr>
		    				</#if>
		    				
		    				<#if field.name="FRESP15">
		    					<tr><td colspan="2" style="background-color:#DDDDDD"><b>Varie</b></td></tr>
		    				</#if>
		    				
		    				<#if field.name="Infermieri">
		    					<tr><td colspan="2" style="font-size:14px;font-weight: normal;"><b>Se s&igrave;, specificare il ruolo d'appartenenza e numero di persone coinvolte:</b></td></tr>
		    				</#if-->
	
		    				<@SingleFieldTd template.name field.name el userDetails editable/>
		    				
		    				<#--if field.name?starts_with("note")>
				    			<tr><td colspan="2" style="background-color:#F5F5F5"></td></tr>
				    		</#if-->
     				
     				</#list>
	    			</tbody>
     			</table>		


	    						<#if formEdit>
	    							
		    		      	<#--button id="salvaForm-${template.name}" class="btn btn-warning templateForm" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span></button-->
										
		    		       </form>
		    		      </#if>
					
					
					    </#if>
   </#list>
 </#if>
					

							</#if>
					
				</#list>




 <#--div class="col-sm-2">
 	<button class="btn btn-xs btn-warning" onclick="window.location.href='${baseUrl}/app/documents/detail/${el.parent.id}';"><i class="icon-reply"> </i>Torna indietro </button>
 </div-->
