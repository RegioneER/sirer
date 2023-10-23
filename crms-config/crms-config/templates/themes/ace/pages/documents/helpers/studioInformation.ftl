<style>
	
.select2-container .select2-choice{
min-width: 300px !important;
}

label, .lbl {
    vertical-align: bottom;
}	
	
.ui-autocomplete.ui-menu{
	z-index:9999!important;
}

.cp .field-component{
//clear: both;
float:left;
width: 200px;
overflow: visible;
margin-right: 5px;
margin-top: -11px;
}
.cpf .field-component{
//clear: both;
float:left;
overflow: visible;
width: 200px;
margin-right: 5px;
margin-top: -11px;
}
.cpr .field-component{
//clear: both;
float:left;
overflow: visible;
width: 200px;
margin-right: 5px;
margin-top: -11px;
}

.cpoc .field-component{
//clear: both;
float:left;
overflow: visible;
width: 200px;
margin-right: 5px;
margin-top: -11px;
}

.cpl .field-component{
//clear: both;
float:left;
overflow: visible;
width: 200px;
margin-right: 5px;
margin-top: -11px;
}

.field-component.to-edit {
overflow: visible;
}

.clearfix {
clear: both;
}

//.x-radio-input {
//display:block;
//}

#metadataTemplate-IDstudio .col-sm-3{
width:auto !important;
}

#metadataTemplate-UniqueIdStudio .col-sm-3{
width:auto !important;
}

.x-checkbox-input {
display:block;
}

//label[for="datiStudio_etaUtero"]{
//height: 8.5em;
//}

//label[for="datiStudio_etaPop1944A"]{
//height: 3.5em;
//}

.single-field-form {
margin-left: 21em;
}

.data-view-mode{
//margin-left: 21em;
//height: 23px;
}

//#datiStudio-datiStudio_etaUtero ul{
//	margin-left: 0px;
//}
//
//#datiStudio-datiStudio_etaPop1944A ul{
//	margin-left: 0px;
//}

.col-sm-1, .col-sm-2, .col-sm-3, .col-sm-4, .col-sm-5, .col-sm-6, .col-sm-7, .col-sm-8, .col-sm-9, .col-sm-10, .col-sm-11 {
    float: none;
}

</style>

<#include "../helpers/macroGemelli.ftl"/>

<@script>


//$(document).ready(function(){
	
	setTimeout(function(){
	
	//alert($('#datiStudio_durata').val());
	
//	if($('#datiPromotore_promotore')) alert('si');
//	else alert('no');
	
	if(valueOfField('datiPromotore_promotore')==''){
		$('[id^=datiPromotore_Ref]').attr('disabled',true);
		$('[id^=datiPromotore_Ref]').val('');
		$('[id^=datiPromotore_ref]').attr('disabled',true);
		$('[id^=datiPromotore_ref]').val('');
		$('[id^=update_dictionary_datiPromotore]').hide();
		$('[id^=add_dictionary_datiPromotore]').hide();
	}else{
		$('[id^=datiPromotore_Ref]').attr('disabled',false);
		$('[id^=datiPromotore_ref]').attr('disabled',false);
	}
	
	$('#datiPromotore_promotore').change(function(){
		if(valueOfField('datiPromotore_promotore')!='') {
			$('[id^=datiPromotore_Ref]').attr('disabled',false);
			$('[id^=datiPromotore_ref]').attr('disabled',false);
		}
		else{
		$('[id^=datiPromotore_Ref]').attr('disabled',true);
		$('[id^=datiPromotore_Ref]').val('');
		$('[id^=datiPromotore_ref]').attr('disabled',true);
		$('[id^=datiPromotore_ref]').val('');
		$('[id^=update_dictionary_datiPromotore]').hide();
		$('[id^=add_dictionary_datiPromotore]').hide();
		}
	});
	
	if(valueOfField('datiCRO_denominazione')==''){
		$('[id^=datiCRO]').attr('disabled',true);
			$('[id^=datiCRO]').val('');
			$('[id^=update_dictionary_datiCRO]').hide();
			$('[id^=add_dictionary_datiCRO]').hide();
	}else{
		$('[id^=datiCRO]').attr('disabled',false);
		}
	
	$('#datiCRO_denominazione').change(function(){
		if(valueOfField('datiCRO_denominazione')!='') {
			$('[id^=datiCRO]').attr('disabled',false);
		}
		else {
			$('[id^=datiCRO]').attr('disabled',true);
			$('[id^=datiCRO]').val('');
			$('[id^=update_dictionary_datiCRO]').hide();
			$('[id^=add_dictionary_datiCRO]').hide();
		}
	});
$('#informations-datiStudio_meddra').before('<tr><td colspan="2" style="background-color:#DDDDDD"><b>CLASSIFICAZIONE PATOLOGIA IN STUDIO</b></td></tr>');
$('#informations-datiStudio_profit').before('<tr><td colspan="2" style="background-color:#DDDDDD"><b>&nbsp;</b></td></tr>');
},1000);

function datiStudioChecks(){

	//calcoloDataFine();
	
	//if(checkEudractNumber() && checkTipoPop() && checkEtaPop()) return true;
	if(checkEudractNumber()) return true;
	else return false;
	
	return true;
}

function datiPromotoreChecks(){

return checkEmail('datiPromotore_RefEmail');
	
}

function datiCROChecks(){

return checkEmail('datiCRO_email');

}

function checkEmail(nomeCampo){
var res=true;
$("input[name^="+nomeCampo+"]").each(function() {
  if(this.value){
    if(!isValidEmailAddress(this.value)){
		alert('Formato email non valida');
		$(this).focus();
		res=false;
		return false;
		}
  }
});
	
return res;	
}


function isValidEmailAddress(emailAddress) {
    var pattern = /^([a-z\d!#$%&'*+\-\/=?^_`{|}~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+(\.[a-z\d!#$%&'*+\-\/=?^_`{|}~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]+)*|"((([ \t]*\r\n)?[ \t]+)?([\x01-\x08\x0b\x0c\x0e-\x1f\x7f\x21\x23-\x5b\x5d-\x7e\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]|\\[\x01-\x09\x0b\x0c\x0d-\x7f\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]))*(([ \t]*\r\n)?[ \t]+)?")@(([a-z\d\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]|[a-z\d\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF][a-z\d\-._~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]*[a-z\d\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])\.)+([a-z\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]|[a-z\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF][a-z\d\-._~\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF]*[a-z\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])\.?$/i;
    return pattern.test(emailAddress);
};

//AUTOCOMPILAZIONE DELLA DATA DI FINE DURATA STUDIO
//function calcoloDataFine(){
//	if($('#datiStudio_durata').val()!="" && $('#datiStudio_Durata-select').val()!="" && $('#datiStudio_dataInizio').val()!=""){
//
//	var unita=parseFloat($('#datiStudio_Durata-select').val().split("###")[0]);
//	var addVar=parseFloat($('#datiStudio_durata').val());
//	var date=$('#datiStudio_dataInizio').datepicker();
//	date=date.data('datepicker').date;
//	date= new Date(date.getTime());
//	
//	switch(unita){
//		
//		case 1:
//		date.setDate(date.getDate()+addVar);
//		break;
//		
//		case 2:
//		date.setDate(date.getDate()+addVar*7);
//		break;
//		
//		case 3:
//		date.setMonth(date.getMonth()+addVar);
//		break;
//		
//		case 4:
//		date.setFullYear(date.getFullYear()+addVar);
//		break;
//		
//		}
//	
//	$('#datiStudio_dataFine').datepicker('setDate',date);
//	
//	}
//
//}

//Controllo EudraCT Number
function checkEudractNumber(){
	var risultato=true;
	if($('#datiStudio_eudractNumber').is(':visible') && $('#datiStudio_eudractNumber').val()!=""){
		var eudractNumber=$('#datiStudio_eudractNumber').val();
		var emailRegex = '^20[0-9]{2}-[0-9]{6}-[0-9]{2}$';
		if(!eudractNumber.match(emailRegex)){
	  	alert("ATTENZIONE!\nIl formato corretto del campo EudraCT Number e' il seguente: 20xx-xxxxxx-xx\n dove 'x' e' un numero intero da 0 a 9.\nIn alternativa e' possibile lasciarlo vuoto.");
			$('#datiStudio_eudractNumber').focus();
			risultato=false;
		}
	}else	$('#datiStudio_eudractNumber').val('');
	return risultato;
}

//Controllo checkTipoPop
//function checkTipoPop(){
//	var risultato=true;
//	if($('#datiStudio_tipoPop1').prop('checked') || $('#datiStudio_tipoPop2').prop('checked') || $('#datiStudio_tipoPop5').prop('checked')){
//	}else{
//		alert("ATTENZIONE!\nSelezionare almeno un'opzione per 'Popolazione in studio'");
//		$('#datiStudio_tipoPop1').focus();
//		risultato=false;
//	}
//return risultato;
//}

//Controllo checkEtaPop
//function checkEtaPop(){
//	var risultato=true;
//	if($('#datiStudio_etaUtero').prop('checked') || $('#datiStudio_etaNeonati').prop('checked') || $('#datiStudio_etaPop01M').prop('checked') || $('#datiStudio_etaPop123M').prop('checked') || $('#datiStudio_etaPop211A').prop('checked') || $('#datiStudio_etaPop12318A').prop('checked') || $('#datiStudio_etaPop1944A').prop('checked') || $('#datiStudio_etaPop4564A').prop('checked') || $('#datiStudio_etaPop65A').prop('checked')){
//	}else{
//			alert("ATTENZIONE!\nSelezionare almeno un'opzione per 'Popolazione pediatrica, adulta o geriatrica'");
//			$('#datiStudio_etaUtero').focus();
//			risultato=false;
//		}
//return risultato;
//}




$(document).ready(function(){
	//$('#datiStudio_durata').add('#datiStudio_Durata-select').add('#datiStudio_dataInizio').change(calcoloDataFine);	
}
);

</@script>

<style>
/*ciao*/
.cp{
//float: left;
clear:both;
width: 100%;
//width: 400px;
}
.cp label{
//	width:136px;
}

.cpf{
//float: left;
clear:both;
width: 100%;
//width: 400px;
}
.cpf label{
//	width:136px;
}

.cpr{
//float: left;
clear:both;
width: 100%;
//width: 400px;
}
.cpr label{
//	width:136px;
}

.cpoc{
//float: left;
clear:both;
width: 100%;
//width: 400px;
}
.cpoc label{
//	width:136px;
}

.cpl{
//float: left;
clear:both;
width: 100%;
//width: 400px;
}
.cpl label{
//	width:136px;
}

.cppm{
//float: left;
clear:both;
width: 100%;
//width: 400px;
}
.cppm label{
//	width:136px;
}

.cpfv{
//float: left;
clear:both;
width: 100%;
//width: 400px;
}
.cpfv label{
//	width:136px;
}

.col-sm-5 {
    width: 82.667%;
}
</style>

<#include "MetadataTemplate.ftl"/>
<#--if infoPanel=="main">
<fieldset id="child-box" class="child-box">
<#else>
<fieldset style="width:100%">
</#if-->
    <#--legend>Informazioni<#if el.locked><img src="${baseUrl}/int/images/lock.png" width="36px"/></#if></legend-->
	<#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
		
		<#--
		<@TemplateFormFastUpdate "IDstudio" el userDetails editable/>
    <@TemplateFormFastUpdate "UniqueIdStudio" el userDetails editable/>
    -->
    
	<#assign tabOrder=['datiStudio','datiCoordinatore']/>

	<#assign counter=0 />
        <div id="metadataTemplate-tabs" class="tabbable" >
			<ul  class="nav nav-tabs" >
				<#list tabOrder as templateName>
					<#if viewableTemplate(templateName, el, userDetails)>
					<#assign counter=counter+1 />
					 <li <#if counter=1 >class="active"</#if>><a href="#metadataTemplate-${templateName}"  data-toggle="tab" ><@msg "template.${templateName}"/></a></li>
					</#if>
				</#list>
				<li><a href="#promotori-tab" data-toggle="tab" >Promotori</a></li>
				<li><a href="#finanziatori-tab" data-toggle="tab" >Finanziatori</a></li>
				<li><a href="#cro-tab" data-toggle="tab" >CRO</a></li>
				<li><a href="#centri-tab" data-toggle="tab" >Centri</a></li>
				<li><a href="#farmaci-tab" data-toggle="tab" >Farmaci/Dispositivi/Altro</a></li>


				<#--li><a href="#dsur-tab" data-toggle="tab" >Safety</a></li-->
				<li><a href="#emendamenti-tab" data-toggle="tab">Emendamenti</a></li>
				<li><a href="#allegato-tab" data-toggle="tab" >Documenti core studio</a></li>
				<li><a href="#prodottistudio-tab" data-toggle="tab">Prodotti</a></li>
			</ul>
		<#assign counter=0 />
	<div  class="tab-content" >
	<#list el.getElementTemplates() as template>
		<#if template.getMetadataTemplate().getName()="datiStudio">
	  	<#if template.getUserPolicy(userDetails, el).isCanUpdate()>
	    	<#assign chiuso=true>
	    <#else><#assign chiuso=false>
	    </#if>
	  </#if>
	</#list>
	<#-- Controllo esistenza emendamento attivo (in sessione utente) -->
	<#assign forceEdit = false />
	<#if userDetails.getEmeSessionId()?? && userDetails.getEmeSessionId() gt 0 && el.getInEmendamento()==true>
		<#assign chiuso=false />
		<#assign editable = true />
		<#assign forceEdit = true />
	</#if>
	<#if forceRO?? && forceRO>
	    <#assign chiuso=true />
	</#if>
	

	<#-- Inizializzo qui la variabile che mi dice se posso aggiungere figli o meno "true" per tutti-->
	<#assign addChildrens=true />
	<#if userDetails.hasRole("SP") && canAccess > <#-- se sono sponsor e posso vedere è perchè ho inserito io questo studio -->
		<#-- sovrascrivo addChildrens se ho inviato almeno un centro inserito da me (per tutti i tipi di oggetti tranne "Centro" e "allegato"-->
		<#assign parentEl=el/>
		<#list parentEl.getChildrenByType("Centro") as elCentro>
			<#if elCentro.getFieldDataString("RichiestaSponsor","statoRichiesta")?? && elCentro.getFieldDataString("RichiestaSponsor","statoRichiesta")!="" && elCentro.getFieldDataString("RichiestaSponsor","statoRichiesta")=="1">
					<#assign addChildrens=false>
			</#if>
		</#list>
	</#if>



	<#list el.templates as template>
		<!-- TEMPLATE: ${template.name}<br/> -->
	    <#if template.name!="IDstudio" &&  template.name!="UniqueIdStudio">
		    <#if template.name="datiPromotore" || template.name="datiCRO" >
		    	<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
		    	<#list el.elementTemplates as elementTemplate>
		    		<#if elementTemplate.metadataTemplate.name=template.name && elementTemplate.enabled>
		    			
		    			<div id="metadataTemplate-${template.name}" class="allInTemplate tab-pane">
		    			<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
		    			<#assign formEdit=false>
		    			<#assign idSp=el.getfieldData("datiPromotore","promotore") />
							<#if idSp[0]?? && idSp[0]?size gt 0>
		    				<input type="hidden" id="datiPromotore_promotore" disabled="disabled" name="parent_promo" value="${idSp[0].id}">
							</#if>
		    			<#assign idCro=el.getfieldData("datiCRO","denominazione") />	
		    			<#if idCro[0]?? && idCro[0]?size gt 0>
								<input type="hidden" id="datiCRO_denominazione" disabled="disabled" name="parent_cro" value="${idCro[0].id}">
		    			</#if>
		    			
		    			<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit) >
		    				<#assign formEdit=true>
        					<form name="${template.name}" class="form-horizontal" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
        				</#if>
						<#list template.fields as field>
		    				<#assign isEditable=editable>
		    					
		    				<#if field.name="promotore" || field.name="denominazione">
		    					<#assign isEditable=chiuso>
		    				</#if>
		    				
		    				<#if field.name="cpLink" || field.name="cpfLink" || field.name="cprLink" || field.name="cpocLink" || field.name="cplLink" || field.name="cppmLink" || field.name="cpfvLink">
		    				<span style="display:none">
		    				</#if>
		    				
		    				<#if field.name="RefNomeCognomeF" || field.name="NomeReferenteF">
		    					<br/><br/>
		    					<fieldset class="cpf">
		    						
		    						<legend style="width: 100%; border-width:0 0 5px;">Contact Point</legend>
		    						
		    						<legend style="width: 200px; font-size: 17px;">Direzione Medica</legend>
		    								    						
		    				</#if>
		    				<#if field.name="refNomeCognomeP" || field.name="nomeReferente">
		    					</fieldset>
		    					<br/>
		    					<fieldset class="cp">
		    						
		    						<legend style="width: 200px; font-size: 17px;">Amministrazione</legend>
		    				</#if>
		    				<#if field.name="RefNomeCognomepR" || field.name="NomeReferenteR">
		    					</fieldset>
		    					<br/>
		    					<fieldset class="cpr">
		    						<legend style="width: 350px; font-size: 17px;">Regolatorio (referente per il Comitato Etico)</legend>
		    								    						
		    				</#if>
		    					<#if field.name="RefNomeCognomeOC" || field.name="NomeReferenteOC">
		    					</fieldset>
		    					<br/>
		    					<fieldset class="cpoc">
		    						<legend style="width: 200px; font-size: 17px;">Monitor</legend>
		    								    						
		    				</#if>
		    				<#if field.name="RefNomeCognomeL" || field.name="NomeReferenteL">
		    					</fieldset>
		    					<br/>
		    					<fieldset class="cpl">
		    						<legend style="width: 200px; font-size: 17px;">Legale<br>(chi firma il contratto)</legend>
		    								    						
		    				</#if>
		    				<#if field.name="RefNomeCognomePM" || field.name="NomeReferentePM">
		    					</fieldset>
		    					<br/>
		    					<fieldset class="cpl">
		    						<legend style="width: 200px; font-size: 17px;">Project Manager</legend>
		    								    						
		    				</#if>
		    				<#if field.name="RefNomeCognomeFV" || field.name="NomeReferenteFV">
		    					</fieldset>
		    					<br/>
		    					<fieldset class="cpl">
		    						<legend style="width: 200px; font-size: 17px;">Farmacovigilanza</legend>
		    								    						
		    				</#if>
							<#if field.name="GruppoAttivitaPrincipale">
								<tr><td colspan="2" style="background-color:#DDDDDD"><b>CLASSIFICAZIONE PATOLOGIA IN STUDIO</b></td></tr>
							</#if>

		    				<@SingleField template.name field.name el userDetails isEditable/>
		    				<#if field.name="cpLink" || field.name="cpfLink" || field.name="cprLink" || field.name="cpocLink" || field.name="cplLink" || field.name="cppmLink" || field.name="cpfvLink">

		    				</#if>
		    			</#list>
		    			</fieldset>
		    			
		    			<div class="clearfix"> </div>
		    			
		    			<#if formEdit>
		    			 <button class="submitButton round-button blue templateForm btn btn-warning" id="salvaForm-${template.name}" ><i class="icon-save bigger-160" id="document-form-submit" name="document-form-submit" ></i><b>Salva</b></span>
											</button>
		    			  	<!--input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche"-->
			            	</form>
			            </#if>
		    			</div>
		    		</#if>
		    	</#list>
		    </#if>
		    
		    	
		    <#else>
		    	<#assign counter=counter+1 />
		    		<#if counter=1>
		    			<#assign classes="tab-pane in active" />
		    		<#else>
		    			<#assign classes="tab-pane" />
		    		</#if>
		    	<#assign titolo="Dati generali studio"/>
				<#if template.name="datiCoordinatore">
					<#assign titolo="Centro Coordinatore">
				</#if>
				<!-- QUA INIZIO IL TEMPLATE DATI STUDIO -->
			    <@TemplateFormTable template.name el userDetails editable titolo classes "false" forceEdit />
				<!-- QUA FINISCO IL TEMPLATE DATI STUDIO -->
	        </#if>	
        </#if>
    </#list>
    
    <div id="dsur-tab" class="tab-pane">
  			
  			<#if userDetails.hasRole("CTC") > <#-- TOSCANA-165 aggiungo controllo classico su ruolo e possibilit� di creazione ma non lo limito come per i farmaci (vedi codice sotto)-->			
				<#if model['getCreatableElementTypes']??>
					<#list model['getCreatableElementTypes'] as docType>
						<#if docType.typeId="DSUR" >
					 		<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Carica nuovo DSUR">
					 	</#if>
					</#list>
				</#if>
			</#if>
			<br><br>
			<div class="home-container">
				<span class="home-table" >
					<table id="grid-dsur" class="grid-table" ></table>
						<div id="grid-dsur-pager"></div>
				</span>
			</div>
	  				
	</div>
 			
 			
	<div id="farmaci-tab" class="tab-pane">
		<#if canAccessTab>
			<#assign sameGroup=false />
			<#-- assign sameGroup=model['docService'].checkUsersSameGroupByPrefix(model['userService'].loadUserByUsername(el.createUser),userDetails,"CTO_") / -->
			<#assign sameGroup=true />
			<#if sameGroup >
				<#if addChildrens && canAccessTab>
					<#if model['getCreatableElementTypes']??>
						<#list model['getCreatableElementTypes'] as docType>
							<#if docType.typeId="Farmaco" >
								<button class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo prodotto</b></button>
							</#if>
						</#list>
					</#if>
				</#if>
			</#if>
			<br/><br/>
			<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">
					<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<th class="hidden-480">Tipo</th>
									<th class="hidden-480">Prodotto</th>
									<!--th class="hidden-480">Descrizione</th-->
									<!--th class="hidden-480">Modalità fornitura/copertura oneri finanziari</th-->
									<!--th class="hidden-480">Numero unit&agrave; a paziente</th>
									<th class="hidden-480">Totale valore</th-->
									<!--th class="hidden-480">Movimentazione magazzino</th-->
									<th class="hidden-480" style="width: 10%">Azioni</th>
								</tr>
							</thead>

							<tbody>
								<#assign noFarmaci>
									<tr><td colspan=7><span class="help-button">?</span> Nessun prodotto inserito </td></tr>
								</#assign>

							<#assign parentEl=el/>
							<#list parentEl.getChildrenByType("Farmaco") as subEl>
								<#if subEl.deleted>
								<#else>
									<#assign noFarmaci="">

									<#assign tipo=subEl.getFieldDataDecode("Farmaco","tipo") />
									<#assign prodotto="">
									<#assign descrizione="">
									<#assign unita="">
									<#assign numero="">
									<#assign valore="">
									<#assign copertura="">
									<#if subEl.getFieldDataCode("Farmaco","tipo")=="1">
										<#assign prodotto=subEl.getFieldDataDecode("Farmaco","princAtt") />
										<#if subEl.getFieldDataCode("Farmaco","princAtt")=="-9999">
											<#assign prodotto=subEl.getFieldDataString("Farmaco","princAttAltro") />
										</#if>
										<#if subEl.getFieldDataString("Farmaco","SpecialitaAIC")??>
											<#assign prodotto="Princ. Att.: "+prodotto+" - Specialità medicinale: "+subEl.getFieldDataString("Farmaco","SpecialitaAIC") />
										</#if>
									<#elseif subEl.getFieldDataCode("Farmaco","tipo")=="2">
										<#if subEl.getfieldData("Farmaco","dispMed")?? &&  subEl.getfieldData("Farmaco","dispMed")?size gt 0 >
											<#assign prodotto=subEl.getFieldDataDecode("Farmaco","dispMed") />
											<#if subEl.getFieldDataCode("Farmaco","dispMed")=="-9999">
												<#assign prodotto=subEl.getFieldDataString("Farmaco","dispMedAltro") />
											</#if>
										</#if>
									<#else>
										<#assign prodotto=subEl.getFieldDataString("Farmaco","descrizioneAttr")+subEl.getFieldDataString("Farmaco","descrizioneMat")+subEl.getFieldDataString("Farmaco","descrizioneMatAltro")  />
									</#if>

									<#assign descrizione=""/>
									<#assign unita=subEl.getFieldDataString("Farmaco","unitaMisura") />
									<#assign numero=subEl.getFieldDataString("Farmaco","numUnitaPaz") />
									<#assign valore=subEl.getFieldDataString("Farmaco","totaleValore") />
									<#-- assign copertura=subEl.getFieldDataDecode("Farmaco","modalitaFornitura") /-->
								<!-- inizio tabella nuova -->
										<tr>
											<td class="hidden-480">${tipo}</td>
											<td class="hidden-480">${prodotto}</td>
											<!--td class="hidden-480">${descrizione}</td-->
											<!--td class="hidden-480">${copertura}</td-->
											<!--td class="hidden-480">${numero}</td>
											<td class="hidden-480">${valore}</td-->
											<!--td class='hidden-480' style="text-align: center">
												<a href="#" class="tooltip-info" data-rel="tooltip" title="Movimentazione magazzino">
													<span class="blue">
														<i class="icon-zoom-in bigger-120"></i>
													</span>
												</a>
											</td-->
											<td>
													<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
														<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
															<i class="icon-edit bigger-120"></i>
														</button>
														<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
														<#if elPolicy.canDelete && canAccessTab>
															<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il farmaco?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
																<i class="icon-trash bigger-120"></i>
															</button>
														</#if>

													</div>
											</td>
										</tr>
										<!-- fine tabella nuova -->
								</#if>
							</#list>

							${noFarmaci}

							</tbody>
						</table>

					</div>
				</div>
			</div>
		<#else>
		<div class="row">
			<div class="col-xs-12">
				<h1>Informazioni non compilabili/visualizzabili se non è stato inserito un centro di competenza dell’utente collegato</h1>
			</div>
		</div>
		</#if> <#-- canAccessTab -->
	</div>

	<div id="promotori-tab" class="tab-pane">		
		<#-- Se profilo segreteria pu� modificare l'elemento... -->
		<#if addChildrens && canAccessTab>
		<#if model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	    		<#if docType.typeId="PromotoreStudio">
					<button class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo Promotore</b></button></br></br>
					<#--
					<@script>
						var messages=null;
						$.getJSON(baseUrl+'/app/rest/documents/messages', function(data){messages=data.resultMap;});
						var modalform=new xCDM_Modal('${baseUrl}', 'PromotoreStudio', function(){}, function(){}, function(){});
					</@script>
					-->
				</#if>
			</#list>
		</#if>
		</#if>

	
	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">	
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
												<thead>
													<tr>
														<th class="hidden-480">Nome del promotore</th>
														<th class="hidden-480">Nome del referente</th>
														<th class="hidden-480" style="width: 10%">Azioni</th>
													</tr>
												</thead>

												<tbody>	
												
												<#assign noPromotori>	
													<tr>
	            							<td colspan=7><span class="help-button">?</span> Nessun promotore inserito </td>
	           							</tr>
           							</#assign>	
    	
    	<#assign parentEl=el/>
    	<#list parentEl.getChildrenByType("PromotoreStudio") as subEl>
    	<#if subEl.deleted>
    	<#else>
    	<#assign noPromotori="">
    	

    	    	<!-- inizio tabella nuova -->
						
						
															
					<tr>
						<#if canAccessTab>
							<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}"><#if subEl.getFieldDataElement("datiPromotore","promotore")[0]??>${subEl.getFieldDataElement("datiPromotore","promotore")[0].getTitleString()!""}</#if></a></td>
						<#else>
							<td><#if subEl.getFieldDataElement("datiPromotore","promotore")[0]??>${subEl.getFieldDataElement("datiPromotore","promotore")[0].getTitleString()!""}</#if></td>
						</#if>
						<td>${subEl.getFieldDataString("datiPromotore","RefNomeCognomeF")!""}</td>
			
						<!--td class="hidden-480">
							<span class="label label-sm label-warning">Expiring</span>
						</td-->
						

			
						<td>
							<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
								<!--button class="btn btn-xs btn-success">
									<i class="icon-ok bigger-120"></i>
								</button-->
								<#if canAccessTab >
									<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
										<i class="icon-edit bigger-120"></i>
									</button>
									<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
									<#if elPolicy.canDelete>
										<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il promotore?')) {deleteElement('${subEl.id}')};return false;">
											<i class="icon-trash bigger-120"></i>
										</button>
									</#if>
								</#if>
								<!--button class="btn btn-xs btn-warning">
									<i class="icon-flag bigger-120"></i>
								</button-->
							</div>
			
							<div class="visible-xs visible-sm hidden-md hidden-lg">
								<div class="inline position-relative">
									<button class="btn btn-minier btn-primary dropdown-toggle" data-toggle="dropdown">
										<i class="icon-cog icon-only bigger-110"></i>
									</button>
			
									<ul class="dropdown-menu dropdown-only-icon dropdown-yellow pull-right dropdown-caret dropdown-close">
										<li>
											<a href="#" class="tooltip-info" data-rel="tooltip" title="View">
												<span class="blue">
													<i class="icon-zoom-in bigger-120"></i>
												</span>
											</a>
										</li>
			
										<li>
											<a href="#" class="tooltip-success" data-rel="tooltip" title="Edit">
												<span class="green">
													<i class="icon-edit bigger-120"></i>
												</span>
											</a>
										</li>
			
										<li>
											<a href="#" class="tooltip-error" data-rel="tooltip" title="Delete">
												<span class="red">
													<i class="icon-trash bigger-120"></i>
												</span>
											</a>
										</li>
									</ul>
								</div>
							</div>
						</td>
					</tr>
			
    	
    	<!-- fine tabella nuova -->	
    	
    	</#if>
    	</#list>
    	
    	${noPromotori}
    	
 		</tbody>
		</table>
		</div>
		</div>
		</div>
	</div>
	
	
	<div id="finanziatori-tab" class="tab-pane">
		<#if addChildrens && canAccessTab >
		<#if model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	    		<#if docType.typeId="FinanziatoreStudio">
					<button class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo Finanziatore</b></button></br></br>
					<#--
					<@script>
						var messages=null;
						$.getJSON(baseUrl+'/app/rest/documents/messages', function(data){messages=data.resultMap;});
						var modalform=new xCDM_Modal('${baseUrl}', 'FinanziatoreStudio', function(){}, function(){}, function(){});
					</@script>
					-->
				</#if>
			</#list>
		</#if>
		</#if>

	
	
	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">	
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
												<thead>
													<tr>
														<th class="hidden-480">Nome del finanziatore</th>
														<th class="hidden-480">Nome del referente</th>
														<th class="hidden-480" style="width: 10%">Azioni</th>
													</tr>
												</thead>

												<tbody>	
												
												<#assign noFinanziatori>	
													<tr>
	            							<td colspan=7><span class="help-button">?</span> Nessun finanziatore inserito </td>
	           							</tr>
           							</#assign>	
    	
    	<#assign parentEl=el/>
    	<#list parentEl.getChildrenByType("FinanziatoreStudio") as subEl>
    	<#if subEl.deleted>
    	<#else>
    	<#assign noFinanziatori="">
    	

    	    	<!-- inizio tabella nuova -->
						
						
															
					<tr>
						<#if canAccessTab>
							<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}"><#if subEl.getFieldDataString("datiFinanziatore","NomeFinanziatore")??>${subEl.getFieldDataString("datiFinanziatore","NomeFinanziatore")}</#if></a></td>
						<#else>
							<td><#if subEl.getFieldDataString("datiFinanziatore","NomeFinanziatore")??>${subEl.getFieldDataString("datiFinanziatore","NomeFinanziatore")}</#if></td>
						</#if>
						<td>${subEl.getFieldDataString("datiFinanziatore","FinReferente")!""}</td>
						<td>
							<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
								<#if  canAccessTab>
									<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
										<i class="icon-edit bigger-120"></i>
									</button>
									<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
									<#if elPolicy.canDelete >
										<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il finanziatore?')) {deleteElement('${subEl.id}')};return false;">
											<i class="icon-trash bigger-120"></i>
										</button>
									</#if>
								</#if>
							</div>
			
							<div class="visible-xs visible-sm hidden-md hidden-lg">
								<div class="inline position-relative">
									<button class="btn btn-minier btn-primary dropdown-toggle" data-toggle="dropdown">
										<i class="icon-cog icon-only bigger-110"></i>
									</button>
			
									<ul class="dropdown-menu dropdown-only-icon dropdown-yellow pull-right dropdown-caret dropdown-close">
										<li>
											<a href="#" class="tooltip-info" data-rel="tooltip" title="View">
												<span class="blue">
													<i class="icon-zoom-in bigger-120"></i>
												</span>
											</a>
										</li>
			
										<li>
											<a href="#" class="tooltip-success" data-rel="tooltip" title="Edit">
												<span class="green">
													<i class="icon-edit bigger-120"></i>
												</span>
											</a>
										</li>
			
										<li>
											<a href="#" class="tooltip-error" data-rel="tooltip" title="Delete">
												<span class="red">
													<i class="icon-trash bigger-120"></i>
												</span>
											</a>
										</li>
									</ul>
								</div>
							</div>
						</td>
					</tr>
			
    	
    	<!-- fine tabella nuova -->	
    	
    	</#if>
    	</#list>
    	
    	${noFinanziatori}
    	
 		</tbody>
		</table>
		</div>
		</div>
		</div>
	</div>



	
	
	<div id="cro-tab" class="tab-pane">
	<#if canAccessTab >
		<#if addChildrens >
		<#if model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	    		<#if docType.typeId="CROStudio">
					<button class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuova CRO</b></button></br></br>
					<#--
					<@script>
						var messages=null;
						$.getJSON(baseUrl+'/app/rest/documents/messages', function(data){messages=data.resultMap;});
						var modalform=new xCDM_Modal('${baseUrl}', 'CROStudio', function(){}, function(){}, function(){});
					</@script>
					-->
				</#if>
			</#list>
		</#if>
		</#if>

	
	
		<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">	
    					<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<th class="hidden-480">Nome della CRO</th>
									<th class="hidden-480">Nome del referente</th>
									<th class="hidden-480" style="width: 10%">Azioni</th>
								</tr>
							</thead>

							<tbody>

								<#assign noCRO>
								<tr>
									<td colspan=7><span class="help-button">?</span> Nessuna CRO inserita </td>
								</tr>
								</#assign>
    							<#assign parentEl=el/>
								<#list parentEl.getChildrenByType("CROStudio") as subEl>
									<#if subEl.deleted>
									<#else>
									<#assign noCRO="">
									<!-- inizio tabella nuova -->
									<tr>
										<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}"><#if subEl.getFieldDataElement("datiCRO","denominazione")[0]??>${subEl.getFieldDataElement("datiCRO","denominazione")[0].getTitleString()!""}</#if></a></td>

										<td>${subEl.getFieldDataString("datiCRO","RefNomeCognomeF")!""}</td>
										<td>
											<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
												<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
													<i class="icon-edit bigger-120"></i>
												</button>

												<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
												<#if elPolicy.canDelete >
												<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare la CRO?')) {deleteElement('${subEl.id}')};return false;">
													<i class="icon-trash bigger-120"></i>
												</button>
												</#if>
											</div>
											<div class="visible-xs visible-sm hidden-md hidden-lg">
												<div class="inline position-relative">
													<button class="btn btn-minier btn-primary dropdown-toggle" data-toggle="dropdown">
														<i class="icon-cog icon-only bigger-110"></i>
													</button>
													<ul class="dropdown-menu dropdown-only-icon dropdown-yellow pull-right dropdown-caret dropdown-close">
														<li>
															<a href="#" class="tooltip-info" data-rel="tooltip" title="View">
																<span class="blue">
																	<i class="icon-zoom-in bigger-120"></i>
																</span>
															</a>
														</li>

														<li>
															<a href="#" class="tooltip-success" data-rel="tooltip" title="Edit">
																<span class="green">
																	<i class="icon-edit bigger-120"></i>
																</span>
															</a>
														</li>

														<li>
															<a href="#" class="tooltip-error" data-rel="tooltip" title="Delete">
																<span class="red">
																	<i class="icon-trash bigger-120"></i>
																</span>
															</a>
														</li>
													</ul>
												</div>
											</div>
										</td>
									</tr>
									<!-- fine tabella nuova -->
    							</#if>
    						</#list>
							${noCRO}
				 			</tbody>
						</table>
					</div>
				</div>
		</div>
	<#else>
		<div class="row">
			<div class="col-xs-12">
				<h1>Informazioni non compilabili/visualizzabili se non è stato inserito un centro di competenza dell’utente collegato</h1>
			</div>
		</div>
	</#if> <#-- canAccessTab -->
	</div>
	
 			
    <div id="centri-tab" class="tab-pane" >
    	<#if model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	    		<#if docType.typeId="Centro"> 
	    			<#--<@createFormModal docType el true  />-->
	    			<button class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo centro</b></button>
	      	</#if>
    		</#list>
    	</#if>
    	<br/>	<br/>

    	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">	
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
												<thead>
													<tr>
														<th class="hidden-480">Sede dello studio</th>

														<th class="hidden-480">Unit&agrave; Operativa</th>
														<th class="hidden-480">Principal Investigator</th>
														<!--th class="hidden-480">Stato</th-->
														<th class="hidden-480" style="width: 10%">Azioni</th>
													</tr>
												</thead>

												<tbody>	
												
												<#assign noCentri>	
													<tr>
	            							<td colspan=7><span class="help-button">?</span> Nessun centro inserito </td>
	           							</tr>
           							</#assign>	
    	
    	<#assign parentEl=el/>
    	<#list parentEl.getChildrenByType("Centro") as subEl>
    	<#if subEl.deleted>
    	<#else>
    	<#assign noCentri="">
    		    	<!-- inizio tabella nuova -->
						
						
						<#assign status ="" />
						<#assign status1="" />
						<#assign status2="" />
						<#assign status3="" />
						<#assign cantDeleteCenter="" />
						<#--STSANSVIL-666 il PI non può eliminare centri non suoi, quindi mi collego alla gestione dell'eliminazione
						di cantDeleteCenter (lo imposto a uno se non faccio parte della stessa struttura o non sono io il pi del centro)
						successivamente forzo e blocco l'eliminazione se il centro è in feasibility come già previsto prima
						-->
						<#-- QUI VERIFICO L'APPARTENENZA ALLA STRUTTURA! -->
						<#assign piCF=(subEl.getFieldDataCode("IdCentro","PINomeCognome"))!"" />
						<#assign strutturaCODE=(subEl.getFieldDataCode("IdCentro","Struttura"))!"" />
						<#assign uoCODE=(subEl.getFieldDataCode("IdCentro","UO"))!"" />
						<#assign userCF = userDetails.username />
						<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
							<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
						</#if>
						<#assign userHasSite = false />
						<#list userSitesCodesList as site>
							<#if site==strutturaCODE>
								<#assign userHasSite = true />
							</#if>
						</#list>
						<#assign userHasUO = false />
						<#list userUOCodesList as uo>
							<#if uo==uoCODE>
								<#assign userHasUO = true />
							</#if>
						</#list>
						<#if ( userDetails.hasRole("tech-admin") || userDetails.hasRole("REGIONE") || (subEl.getCreateUser()==userDetails.username) || (userHasSite && !userDetails.hasRole("PI") && !userDetails.hasRole("COORD")) || (userDetails.hasRole("PI") && (userCF == piCF|| userDetails.username == piCF)) || (userHasUO && userDetails.hasRole("COORD")) )>
							<#--questo è lo stesso if che c'è in centro.ftl per la visualizzazione del centro stesso-->
							<#assign cantDeleteCenter="" />
						<#else>
							<#assign cantDeleteCenter="1" />
						</#if>
						<#--STSANSVIL-666 fine -->

						<#if subEl.getfieldData("statoValidazioneCentro", "idBudgetApproved")?? && subEl.getfieldData("statoValidazioneCentro", "idBudgetApproved")?size gt 0>
							<#assign status1="<span class='label label-danger'>Budget</span>" />
						</#if>
						
						<#if subEl.getfieldData("statoValidazioneCentro","fattLocale")?? && subEl.getfieldData("statoValidazioneCentro","fattLocale")?size gt 0>
							<#if subEl.getFieldDataCode("statoValidazioneCentro","fattLocale")="1">
								<#assign status2="<span class='label label-info'>Fatt. PI positiva</span>"/>
							</#if>
							<#if subEl.getFieldDataCode("statoValidazioneCentro","fattLocale")="2">
								<#assign status2="<span class='label label-danger'>Fatt. PI negativa</span>"/>
							</#if>
							<#assign cantDeleteCenter="1" />
						</#if>
						
						<#if subEl.getfieldData("statoValidazioneCentro","valCTC")?? && subEl.getfieldData("statoValidazioneCentro","valCTC")?size gt 0 && subEl.getFieldDataCode("statoValidazioneCentro","valCTC")="1">
							<#assign status3="<span class='label label-success'>Valutazione CTO/TFA</span>" />
						</#if>
						
						<#if status1=="" && status2=="" && status3=="">
							<#assign status="<span class='label label-warning'>Pending</span>"/>
						</#if>
						<#if status3!="">
							<#assign status1="" />
							<#assign status2="" />	
						</#if>
															
													<tr>
														<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}"><#if subEl.getfieldData("IdCentro","Struttura")[0]??>${subEl.getfieldData("IdCentro","Struttura")[0]?split("###")[1]!""}</#if></a></td>

														<td><#if subEl.getfieldData("IdCentro","UO")[0]??>${subEl.getfieldData("IdCentro","UO")[0]?split("###")[1]!""}</#if></td>
														<td>${subEl.getFieldDataDecode("IdCentro","PINomeCognome")}</td>

														<!--td class="hidden-480">
															<span class="label label-sm label-warning">Expiring</span>
														</td-->
														
														<!--td class='hidden-480'>
																${status}
																${status1}
																${status2}
																${status3}
														</td-->

														<td>
															<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
																<!--button class="btn btn-xs btn-success">
																	<i class="icon-ok bigger-120"></i>
																</button-->

																<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
																	<i class="icon-edit bigger-120"></i>
																</button>
																

																<#if cantDeleteCenter!="1">
																	<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
																	<#assign strutturaCODE=(subEl.getFieldDataCode("IdCentro","Struttura"))!"" />
																	<#assign userHasSite = false />
																	<#list userSitesCodesList as site>
																		<#if site==strutturaCODE>
																		<#assign userHasSite = true />
																	</#if>
																	</#list>

																	<#if elPolicy.canDelete && userHasSite>
																		<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il centro?')) {deleteElement('${subEl.id}')};return false;">
																			<i class="icon-trash bigger-120"></i>
																		</button>
																	</#if>
																</#if>


																<!--button class="btn btn-xs btn-warning">
																	<i class="icon-flag bigger-120"></i>
																</button-->
															</div>

															<div class="visible-xs visible-sm hidden-md hidden-lg">
																<div class="inline position-relative">
																	<button class="btn btn-minier btn-primary dropdown-toggle" data-toggle="dropdown">
																		<i class="icon-cog icon-only bigger-110"></i>
																	</button>

																	<ul class="dropdown-menu dropdown-only-icon dropdown-yellow pull-right dropdown-caret dropdown-close">
																		<li>
																			<a href="#" class="tooltip-info" data-rel="tooltip" title="View">
																				<span class="blue">
																					<i class="icon-zoom-in bigger-120"></i>
																				</span>
																			</a>
																		</li>

																		<li>
																			<a href="#" class="tooltip-success" data-rel="tooltip" title="Edit">
																				<span class="green">
																					<i class="icon-edit bigger-120"></i>
																				</span>
																			</a>
																		</li>

																		<li>
																			<a href="#" class="tooltip-error" data-rel="tooltip" title="Delete">
																				<span class="red">
																					<i class="icon-trash bigger-120"></i>
																				</span>
																			</a>
																		</li>
																	</ul>
																</div>
															</div>
														</td>
													</tr>

    	
    	<!-- fine tabella nuova -->	
    	
    	</#if>
    	</#list>
    	
    	${noCentri}
    	
 												</tbody>
											</table>
											</div>
											</div>
											</div>	
    
	</div>


		<#--Controllo che ci sia almeno un parere positivo in un centro-->
		<#assign parPos=false>
		<#list parentEl.getChildrenByType("Centro") as elCentro>
			<#list elCentro.getChildrenByType("ParereCe") as elParere>
				<#if elParere.getFieldDataCode("ParereCe","esitoParere")?? >
					<#if elParere.getFieldDataCode("ParereCe","esitoParere")=="1" || elParere.getFieldDataCode("ParereCe","esitoParere")=="4" || elParere.getFieldDataCode("ParereCe","esitoParere")=="6">
						<#assign parPos=true>
					</#if>
				</#if>
			</#list>
		</#list>
    
   
	    <div id="emendamenti-tab" class="tab-pane">
			<#if canAccessTab>
				<#if parPos>

					<#assign parentEl=el/>
						<#if model['getCreatableElementTypes']??>
						<!-- <h1> VINCENZO ${model['getCreatableElementTypes']?size}</h1> -->
							<#list model['getCreatableElementTypes'] as docType>
								<#if docType.typeId="Emendamento">
									<button class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo emendamento</b></button>
								</#if>
							</#list>
						</#if>
					<br/>	<br/>

					<div class="row">
						<div class="col-xs-12">
							<div class="table-responsive">
								<table id="sample-table-1" class="table table-striped table-bordered table-hover">
									<thead>
										<tr>
											<th class="hidden-480">Codice</th>
											<!--th class="hidden-480">Titolo</th-->
											<th class="hidden-480">Tipologia</th>
											<th class="hidden-480">Data</th>
											<th class="hidden-480">Sintesi</th>
											<!--th class="hidden-480">EME CE</th-->
											<th class="hidden-480" style="width: 10%">Azioni</th>
										</tr>
									</thead>

									<tbody>
											<#assign noEmendamenti>
												<tr><td colspan=7><span class="help-button">?</span> Nessun emendamento inserito </td></tr>
											</#assign>

										<#assign parentEl=el/>
										<#list parentEl.getChildrenByType("Emendamento") as subEl>
											<#if subEl.deleted>
											<#else>
												<#assign noEmendamenti="">
												<#assign emece="">
													<#if subEl.getfieldData("DatiEmendamento","CeEme")?? && subEl.getfieldData("DatiEmendamento","CeEme")[0]??>
														<#assign emece=subEl.getFieldDataDecode("DatiEmendamento","CeEme")>
													</#if>

											<!-- inizio tabella nuova -->
													<tr>
														<td class="hidden-480">
															<a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}">
																${subEl.getFieldDataString("DatiEmendamento","CodiceEme")}
															</a>
														</td>
														<!--td class="hidden-480">${subEl.getFieldDataString("DatiEmendamento","TitoloEme")}</td-->
														<td class="hidden-480">${subEl.getFieldDataDecode("DatiEmendamento","TipologiaEme")}</td>
														<td class="hidden-480">${getFieldFormattedDate("DatiEmendamento","DataEme",subEl)}</td>
														<td class="hidden-480">${subEl.getFieldDataString("DatiEmendamento","SintesiEme")}</td>
														<!--td class="hidden-480">${emece}</td-->
														<td>
																<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
																	<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
																		<i class="icon-edit bigger-120"></i>
																	</button>
																	<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
																	<#if elPolicy.canDelete >
																		<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il farmaco?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
																			<i class="icon-trash bigger-120"></i>
																		</button>
																	</#if>
																</div>
														</td>
													</tr>
													<!-- fine tabella nuova -->
											</#if>
										</#list>

										${noEmendamenti}

									</tbody>
								</table>
							</div>
						</div>
					</div>
				<#else>
					<div>Area attiva solo per studi con almeno un centro con approvazione del CE</div>
				</#if>
			<#else>
			<div class="row">
				<div class="col-xs-12">
					<h1>Informazioni non compilabili/visualizzabili se non è stato inserito un centro di competenza dell’utente collegato</h1>
				</div>
			</div>
			</#if> <#-- canAccessTab -->
	    </div>
		<div id="prodottistudio-tab" class="tab-pane">
			<#if canAccessTab>
				<#assign prodottiAbilitato=false />
				<#list el.getChildrenByType("Centro") as subElCentro>
					<#if subElCentro.getChildrenByType("AvvioCentro")?size gt 0>
						<#assign prodottiAbilitato=true />
					</#if>
				</#list>
				<#if prodottiAbilitato==true >
					<#assign parentEl=el/>
					<#if addChildrens >
						<#if model['getCreatableElementTypes']??>
							<#list model['getCreatableElementTypes'] as docType>
								<#if docType.typeId="ProdottoStudio">
									<button class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo prodotto dello studio</b></button>
								</#if>
							</#list>
						</#if>
					</#if>
					<br/><br/>

					<div class="row">
						<div class="col-xs-12">
							<div class="table-responsive">
								<table id="sample-table-1" class="table table-striped table-bordered table-hover">
									<thead>
									<tr>
										<th class="hidden-480">Tipo prodotto</th>
										<th class="hidden-480">Codice</th>
										<th class="hidden-480">Descrizione</th>
										<th class="hidden-480">Link</th>
										<th class="hidden-480">Data</th>
										<th class="hidden-480" style="width: 10%">Azioni</th>
									</tr>
									</thead>

									<tbody>
										<#assign noProdotti>
										<tr><td colspan=7><span class="help-button">?</span> Nessun prodotto dello studio inserito </td></tr>
										</#assign>

										<#assign parentEl=el/>
										<#list parentEl.getChildrenByType("ProdottoStudio") as subEl>
											<#if subEl.deleted>
											<#else>
												<#assign noProdotti="">
											<!-- inizio tabella nuova -->
											<tr>
												<td class="hidden-480">${subEl.getFieldDataDecode("prodottoStudio","tipoProdotto")}</td>
												<td class="hidden-480">
													<#if subEl.getFieldDataString("prodottoStudio","DoiPmid")!="" >
														DOI o PMID: ${subEl.getFieldDataString("prodottoStudio","DoiPmid")}
													<#elseif subEl.getFieldDataString("prodottoStudio","ISBN")!="" >
													ISBN: ${subEl.getFieldDataString("prodottoStudio","ISBN")}
													<#elseif subEl.getFieldDataString("prodottoStudio","codiceBrevetto")!="" >
														Brevetto: ${subEl.getFieldDataString("prodottoStudio","codiceBrevetto")}
													</#if>
												</td>
												<td class="hidden-480">${subEl.getFieldDataString("prodottoStudio","descrizioneProdotto")}</td>
												<td class="hidden-480">
													<#if subEl.getFieldDataString("prodottoStudio","link")!="" >
														<a href="${subEl.getFieldDataString("prodottoStudio","link")}">${subEl.getFieldDataString("prodottoStudio","link")}</a>
													</#if>
												</td>
												<td class="hidden-480">${getFieldFormattedDate("prodottoStudio","dataProdotto",subEl)}</td>
												<td>
													<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
														<button title="Scarica allegato" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/getAttach/${subEl.id}';">
															<i class="icon-download bigger-120"></i>
														</button>

														<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
														<#if elPolicy.canDelete >
															<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il prodotto?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
																<i class="icon-trash bigger-120"></i>
															</button>
														</#if>
													</div>

												</td>
											</tr>
											<!-- fine tabella nuova -->
											</#if>
										</#list>
										${noProdotti}
									</tbody>
								</table>
							</div>
						</div>
					</div>
				<#else>
					<div>Area attiva solo per studi con almeno un centro in monitoraggio</div>
				</#if>
			<#else>
			<div class="row">
				<div class="col-xs-12">
					<h1>Informazioni non compilabili/visualizzabili se non è stato inserito un centro di competenza dell’utente collegato</h1>
				</div>
			</div>
			</#if> <#-- canAccessTab -->
		</div>

 		<div id="allegato-tab" class="tab-pane" >
    		<#if canAccessTab>
				<fieldset>
					<!--legend>File allegati</legend-->
				<#assign parentEl=el/>
				<#assign sameGroup=false />
				  <#-- assign sameGroup=model['docService'].checkUsersSameGroupByPrefix(model['userService'].loadUserByUsername(el.createUser),userDetails,"CTO_") / -->
				 <#assign sameGroup=true />
				<#if sameGroup>
					<#if model['getCreatableElementTypes']??>
						<#list model['getCreatableElementTypes'] as docType>
							<#if docType.typeId="allegato">
						<button class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  >
							</i><b>Aggiungi nuovo documento allegato</b>
									</button>
					  </#if>
						</#list>
					</#if>
				</#if>

					<br/><br/>
					<!--a href="#" onclick="getDocCe(${el.id});">Consulta Area documentale CE</a>
					<a href="#" alt="Scarica Area documentale CE in formato ZIP" title="Scarica Area documentale CE in formato ZIP" onclick="getDocCeZip(${el.id});" ><i class="fa fa-file-archive-o" aria-hidden="true"></i></a-->
					<div id="dialog" style="display:none;" title="Documentazione Generale"></div>
				<!--inizio tabella nuova-->
				<div class="row">
						<div class="col-xs-12">
							<div class="table-responsive">
							<table id="sample-table-1" class="table table-striped table-bordered table-hover">
									<thead>
										<tr>
											<th class="hidden-480" style="width:1%">Tipologia</th>
											<th class="hidden-480" >File</th>
											<th class="hidden-480" >Autore</th>
											<th class="hidden-480" >Versione</th>
											<th class="hidden-480" >Data</th>
											<th class="hidden-480" >Inserito da</th>
											<th class="hidden-480" >Caricato il</th>
											<th class="hidden-480" >Azioni</th>
										</tr>
									</thead>

									<tbody>

									<#assign noDoc>
										<tr>
								<td colspan=8><span class="help-button">?</span> Nessun documento inserito </td>
							</tr>
						</#assign>

								<#list parentEl.getChildrenByType("allegato") as subEl>

									<#--h3><a href="${baseUrl}/app/documents/detail/${subEl.id}"><#if subEl.getfieldData("DocGenerali","DocGen")[0]??>${subEl.getfieldData("DocGenerali","DocGen")[0]?split("###")[1]} - versione: ${subEl.file.version!""} - data: <#if subEl.file.date??>${subEl.file.date.time?date?string.short}</#if><#else>Non definito</#if></a></h3-->

											<#if subEl.file??>
											<#assign noDoc="" />
											<#assign tipologia="" />
											<#assign autore="" />
											<#assign version="" />
											<#assign fileName="" />
											<#assign uploadUser="" />
											<#assign uploadDt="" />
											<#assign data="" />
											<#if subEl.getfieldData("DocGenerali","DocGen")[0]??>
												<#assign tipologia=subEl.getFieldDataDecode("DocGenerali","DocGen")/>
												<#if subEl.file??>
													<#if subEl.file.autore??>
														<#assign autore=subEl.file.autore />
													</#if>

													<#if subEl.file.version??>
														<#assign version=subEl.file.version />
													</#if>

													<#if subEl.file.fileName??>
														<#assign fileName=subEl.file.fileName />
													</#if>

													<#if subEl.file.uploadUser??>
														<#assign uploadUser=subEl.file.uploadUser />
													</#if>

													<#if subEl.file.uploadDt??>
														<#assign uploadDt=subEl.file.uploadDt.time?date?string.short />
													</#if>

													<#if subEl.file.date??>
														<#assign data=subEl.file.date.time?date?string.short />
													</#if>
												</#if>
											</#if>

											<tr>
												<#if subEl.file??>
													<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}">${tipologia}</a></td>
													<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${fileName}</a></td>
													<td>${autore}</td>
													<td>${version}</td>
													<td>${data}</td>
													<td user-data="${uploadUser}">${uploadUser}</td>
													<td>${uploadDt}</td>
													<!--td class="hidden-480"><span class="label label-sm label-warning">Expiring</span></td-->
												<#else>
													<td colspan="7"><div id="success" class="alert alert-block alert-danger">	<i class="icon-ko red red">Caricamento del documento non andato a buon fine. Riprovare avendo cura di fare click una sola volta</div></td>
												</#if>
												<td>
													<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
														<!--button class="btn btn-xs btn-success">
															<i class="icon-ok bigger-120"></i>
														</button-->

														<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
															<i class="icon-edit bigger-120"></i>
														</button>
														<#-- PROTOCOLLAZIONE NON IN STUDIO, COMMENTO SOLTANTO PER TENERE TRACCIA DEL CODICE
														<#if subEl.getFieldDataString("DocGenerali","ProtocolloNumero")?string=="" >
															<button title="Protocolla documento" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler protocollare il documento?')) {protocollaElement(${subEl.id},'${subEl.file.fileName}',${elStudio.id},'${elStudio.getFieldDataString("IDstudio","ProtocolloFascicolo")?string}')};return false;" href="#">
																<i class="icon-file bigger-120"></i>
															</button>
														<#else>
															<button title="Vedi documento protocollato" class="btn btn-xs btn-danger" onclick="vediProtocollo('${subEl.getFieldDataString("DocGenerali","ProtocolloNumero")?string}'); return false;" href="#">
																<i class="icon-file bigger-120"></i>
															</button>
														</#if>
														-->
														<#assign elPolicy=subEl.getUserPolicy(userDetails)/>
														<#if elPolicy.canDelete >
															<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il documento?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
																<i class="icon-trash bigger-120"></i>
															</button>
														</#if>

														<!--button class="btn btn-xs btn-warning">
															<i class="icon-flag bigger-120"></i>
														</button-->
													</div>
												</td>
											</tr>

										</#if>

								</#list>

								${noDoc}

									</tbody>
								</table>
							</div>
						</div>
					</div>
				<!--fine tabella nuova-->

				</fieldset>
			<#else>
			<div class="row">
				<div class="col-xs-12">
					<h1>Informazioni non compilabili/visualizzabili se non è stato inserito un centro di competenza dell’utente collegato</h1>
				</div>
			</div>
			</#if> <#-- canAccessTab -->
    </div>
    </div>
    
    
    </div>
</#if>
</fieldset>
