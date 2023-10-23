<style>

.select2-container .select2-choice{
min-width: 350px !important;
}

.token-input-list-facebook{
width: 463px;
border-left-width: 1px;
border-right-width: 1px;
margin-right: 22px;
}

.clearfix:after {
content: ".";
display: block;
height: 0;
clear: both;
visibility: hidden;
}

.clearfix {
clear: both;
border-bottom-width: 11px;
}

.dc{
float: left;
width: 100%;
}
.dc label{
width:47%;
}

.vs{
//float: left;
//width: 45%;
width: 100%;
}
.vs label{
width:60%;
}

.vs .select2-choice{
//width: 90px;
}

.ef div[id^=AnalisiCentro-AnalisiCentro_valorePerc]{
float: left;
}
.ef label[for^=AnalisiCentro_valorePerc]{
float: left;
width:52%;
}

div[id^=informations-Feasibility_FC], div[id^=informations-FeasibilityRadio_F2RESP1], div[id^=informations-FeasibilityLabo_F3RESP1], div[id^=informations-FeasibilityAS_F4RESP1], div[id^=informations-FeasibilityAP_F5RESP1] {
float: left;
width: 60%;
}
div[id^=informations-Feasibility_noteFC], div[id^=informations-FeasibilityRadio_noteF2RESP1], div[id^=informations-FeasibilityLabo_noteF3RESP1], div[id^=informations-FeasibilityAS_noteF4RESP1], div[id^=informations-FeasibilityAP_noteF5RESP1] {
float: left;
width: 40%;
border-width: 0 0 1px;
}
label[for^=Feasibility_FC], label[for^=FeasibilityRadio_F2RESP1], label[for^=FeasibilityLabo_F3RESP1], label[for^=FeasibilityAS_F4RESP1], label[for^=FeasibilityAP_F5RESP1]{
width: 95%;
}

div[id=informations-Feasibility_FC6] {
float: left;
width: 40%;
}

td[id=td-field-AnalisiCentro_saleOperatorie],
td[id=td-field-AnalisiCentro_materiali],
td[id=td-field-AnalisiCentro_attrezzature],
td[id=td-field-AnalisiCentro_tipologiaIntervento],
td[id=td-field-AnalisiCentro_tempoIntervento],
td[id=td-field-AnalisiCentro_tempoSala],
td[id=td-field-AnalisiCentro_tempoMinuti1],
td[id=td-field-AnalisiCentro_tempoMinuti2],
td[id=td-field-AnalisiCentro_tempoMinuti3],
td[id=td-field-AnalisiCentro_tempoMinuti5],
td[id=td-field-AnalisiCentro_tempoOre1],
td[id=td-field-AnalisiCentro_tempoOre2],
td[id=td-field-AnalisiCentro_tempoOre3],
td[id=td-field-AnalisiCentro_tempoOre4],
td[id=td-field-AnalisiCentro_enteErogatore],
td[id=td-field-AnalisiCentro_valorePerc1],
td[id=td-field-AnalisiCentro_valorePerc2],
td[id=td-field-AnalisiCentro_valorePerc3],
td[id=td-field-AnalisiCentro_valorePerc4],
td[id=td-field-AnalisiCentro_valorePerc5],
td[id=td-field-Feasibility_NrPaz]
{
background-image: url("/img/arrow_pdf.jpg");
background-repeat: no-repeat;
background-position: right;
padding-right: 45px !important;
}

.vl{
width: 100%;
}
.vl label{
width:55%;
color:#E17031;
}

.l4 {
color:#E17031;
}

.pi{
float: left;
width: 50%;
}
.pi label{
width:50%
}

.spec{
width: 50%;
}
.spec label{
width:30%
}

.centro-template #informations-DatiCentro_NrPaz {
display:none !important;
}

.nav-tabs > li {
height: 34px;
}

//#ServiziCoinvolti-ServiziCoinvolti_SERV1 ul{
//	margin-left: 0px;
//	margin-bottom: 0px;
//}

#form-DatiCentro .field-component{
clear:both;
}

#s2id_DatiCentro_CeDt-select{
padding-left: 12px;
padding-right: 12px;
}

#s2id_DatiCentro_CeDt-select span{
color: #858585;
font-size: 12px;
}

#form-AnalisiCentro .radio {
float:left;
}
#form-Feasibility .radio {
float:left;
}

#Feasibility_dataApprIst,
#Feasibility_dataApprDip{
width: 90px;
}

td[id^=td-label-Feasibility_],
td[id^=td-label-AnalisiCentro_]{
width: 70% !important;
}

td[id^=td-field-Feasibility_],
td[id^=td-field-AnalisiCentro_]{
width: 30% !important;
}

#form-DatiCentro .form-control{
min-width: 312px !important;
}


div[id^=task-Actions-] .btn{
		font-size: 13px !important;
		margin-top: 0px !important;
}

</style>

<#-- QUI VERIFICO L'APPARTENENZA ALLA STRUTTURA! -->
<#assign piCF=(el.getFieldDataCode("IdCentro","PINomeCognome"))!"" />
<#assign strutturaCODE=(el.getFieldDataCode("IdCentro","Struttura"))!"" />
<#assign uoCODE=(el.getFieldDataCode("IdCentro","UO"))!"" />
<#assign userCF = userDetails.username />
<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
	<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
</#if>
<#assign userHasSite = false />
<!-- userSitesCodesList size: ${userSitesCodesList?size} -->
<#if userSitesCodesList?size gt 0 >
	<#list userSitesCodesList as site>
	<!-- current site: ${site} -->
		<#if site==strutturaCODE>
			<#assign userHasSite = true />
		</#if>
	</#list>
<#else>
	<#assign userHasSite = true />
</#if>
<#assign userHasUO = false />
<#list userUOCodesList as uo>
<!--LIST uo: _${uo}_ == _${uoCODE}_ ?-->
	<#if uo==uoCODE>
<!--SI!-->
		<#assign userHasUO = true />
	</#if>
</#list>

<!--
PI CF: ${piCF}<br/>
Struttura CODE: ${strutturaCODE}<br/>
UO CODE: ${uoCODE}<br/>
-->

<#-- userDetails.hasRole("CTC") && true -->
<!--userDetail.username ${userDetails.username}
userDetails.hasRole("tech-admin") ${userDetails.hasRole("tech-admin")?c}
userDetails.hasRole("REGIONE") ${userDetails.hasRole("REGIONE")?c}
el.getCreateUser() ${el.getCreateUser()}
userHasSite ${userHasSite?c}
userDetails.hasRole("PI") ${userDetails.hasRole("PI")?c}
userHasUO ${userHasUO?c}
userDetails.hasRole("COORD") ${userDetails.hasRole("COORD")?c}
userCF ${userCF}
piCF ${piCF}-->

<#if ( userDetails.hasRole("tech-admin") || userDetails.hasRole("REGIONE") || (userHasSite && !userDetails.hasRole("PI") && !userDetails.hasRole("COORD") && !userDetails.hasRole("SP")) || (userDetails.hasRole("PI") && (userCF == piCF|| userDetails.username == piCF))  || (userDetails.hasRole("SP") && (el.getCreateUser()==userDetails.username)) || (userHasUO && userDetails.hasRole("COORD")) )>

<script>

	function ceUrl(a,d){

		var b;
		var c;


		b=a.replace("ctcgemelli","comitatoeticogemelli");
		c="https://"+b+d;

		//window.location.href=c;

		window.open(
		c,
		'_blank'
		)
	};

	// Per ora non spostare in html/sirer-static/js/common/elementDelete.js o default.js
	// STSANSVIL-2857
	function deleteServizio(servizio) {
		var flagServizioBudget=false;
		var clickedId=servizio.id;
		//console.log("id elemento: "+clickedId);

		if (confirm('Sei sicuro di voler eliminare il servizio coinvolto?')) {
			// Prendo l'elemento cliccato in formato JSON e prendo l'ID del centro
			$.ajax({
    			url: baseUrl + '/app/rest/documents/getElementJSON/' + clickedId,
    			async: false, 
    			dataType: 'json',
    			success: function (element) {
					var idCentro = element.parentId;
					
					// Prendo il centro in formato JSON
					$.ajax({
    					url: baseUrl + '/app/rest/documents/getElementJSON/' + idCentro,
    					async: false, 
    					dataType: 'json',
    					success: function (centro) {
							var cercoBudget = centro.children;
							
							// Ciclo tra i figli di Centro
							for (var i = 0; i < cercoBudget.length; i++) {
								var tipoBudget = cercoBudget[i].type.typeId;

								// Cerco quello di tipo Budget
								if (tipoBudget=="Budget") {
									//console.log(cercoBudget[i])
									var idBudget=cercoBudget[i].id;

									// Prendo il budget in formato JSON
									$.ajax({
										url: baseUrl + '/app/rest/documents/getElementJSON/' + idBudget,
										async: false, 
										dataType: 'json',
										success: function (budget) {
											var cercoFolder = budget.children;

											// Ciclo tra i figli di Budget
											for (var i = 0; i < cercoFolder.length; i++) {
												var tipoFolder = cercoFolder[i].type.typeId;
												
												// Cerco quello di tipo FolderPXP
												if (tipoFolder=="FolderPXP") {
													//console.log(cercoFolder[i]);
													var idFolder=cercoFolder[i].id;

													// Prendo FolderPXP in formato JSON
													$.ajax({
														url: baseUrl + '/app/rest/documents/getElementJSON/' + idFolder,
														async: false, 
														dataType: 'json',
														success: function (folder) {
															var cercoPXP = folder.children;

															// Ciclo tra i figli di FolderPXP
															for (var i = 0; i < cercoPXP.length; i++) {
																var tipoPXP = cercoPXP[i].type.typeId;

																// Cerco quello di tipo PrestazioneXPaziente
																if (tipoPXP=="PrestazioneXPaziente") {
																	//console.log(cercoPXP[i]);
																	var idPXP = cercoPXP[i].id;
																	//console.log(idPXP);

																	// Prendo PrestazioneXPaziente in formato JSON
																	$.ajax({
																		url: baseUrl + '/app/rest/documents/getElementJSON/' + idPXP,
																		async: false, 
																		dataType: 'json',
																		success: function (pxp) {
																			if (pxp.metadata['Prestazioni_CDC']!="") {
																				var cercoPrestazioni = pxp.metadata['Prestazioni_CDC'];
																				//console.log(pxp)
																				//console.log(cercoPrestazioni);

																				// Ciclo l'array di Prestazioni_CDC
																				for (var i = 0; i < cercoPrestazioni.length && flagServizioBudget==false; i++) {
																					var idPrestazione = cercoPrestazioni[i].id;
																					//console.log("prestazione: "+idPrestazione);
																					//console.log("clicked: "+clickedId);

																					if (clickedId==idPrestazione) {
																						flagServizioBudget = true;
																						//console.log("id uguali");
																					};
																				};
																			};
	}
																	}) // fine PrestazioneXPaziente
																	
																};
															};
														}
													}); // fine FolderPXP
												};
											};
										}
									}); // fine Budget
								};
							}
						}
					}); // fine Centro
				} // fine primo JSON
  			});
		
			if (flagServizioBudget==true) {
				alert("Impossibile eliminare, poiché il servizio è presente in Budget");
			} else {
				//console.log("si può eliminare");
				//console.log(flagServizioBudget);
				// Non funziona deleteElement(clickedId);
				$.ajax({
					url : '../../rest/dm/deleteElement/' + clickedId,
				}).done(function() {
					console.log('DELETED');
					location.reload(true);
				});
			};
															
		}; return false;
	};

	// STSANSVIL-8453 TEMPLATE FINE CENTRO
	$( document ).ready(function() {
		$("[name=DatiChiusuraCentro_conclusioneAnticipataRadio]").on('change',function(){
			if($('#DatiChiusuraCentro_conclusioneAnticipataRadio:checked').val()!==undefined && $('#DatiChiusuraCentro_conclusioneAnticipataRadio:checked').val().split("###")[0]==1){
				$('#informations-DatiChiusuraCentro_conclusioneAnticipata').show();
			}
			else if($('#DatiChiusuraCentro_conclusioneAnticipataRadio:checked').val()!==undefined && $('#DatiChiusuraCentro_conclusioneAnticipataRadio:checked').val().split("###")[0]==2){
				$('#informations-DatiChiusuraCentro_conclusioneAnticipata').hide();
				$("#DatiChiusuraCentro_conclusioneAnticipata:checked").each(function(){
					$(this).prop("checked",false)
				});
			}
		});
		$("[name=DatiChiusuraCentro_conclusioneAnticipataRadio]").trigger("change");
	});

</script>
<script>
bootbox.dialog({
    message: '<div class="text-center"><i class="fa fa-spin fa-spinner"></i> Caricamento in corso...</div>',
    closeButton: false,
    onEscape: false
      });
</script>
<@script>
    bootbox.hideAll();
</@script>


<#assign forceEdit = false />
<#if userDetails.getEmeSessionId()?? && userDetails.getEmeSessionId() gt 0 && el.getInEmendamento()==true>
	<#assign forceEdit = true />
	${el.id?string}
</#if>


  <div class="row">
   		<div class="col-xs-9">
<#include "../helpers/MetadataTemplate.ftl"/>
<#assign tabs=[] />
<#assign tabsContent=[] />

<#assign tabsGroups={"metadataTemplate-IdCentro2":"metadataTemplate-IdCentro2",
					 "AllegatoCentro-tab2":"metadataTemplate-IdCentro2",
					 "IstruttoriaCE-tab2":"IstruttoriaCE-tab2",
			         "ParereCe-tab2":"IstruttoriaCE-tab2",
			         "metadataTemplate-Feasibility2":"metadataTemplate-Feasibility2",
			"metadataTemplate-DatiCentro2":"metadataTemplate-Feasibility2",
			"TeamDiStudio-tab2":"metadataTemplate-Feasibility2",
			"DepotFarmaco-tab2":"metadataTemplate-Feasibility2",
			"GestioneFarmacia-tab2":"GestioneFarmacia-Feasibility2",
			"metadataTemplate-FeasibilityRESP2":"metadataTemplate-Feasibility2",
			"FeasibilityAreaME-tab2":"metadataTemplate-Feasibility2",
			"Budget-tab2":"Budget-tab2",
			"Contratto-tab2":"Contratto-tab2",
			"MonitoraggioAmministrativo-tab2":"MonitoraggioAmministrativo-tab2",
			"AvvioCentro-tab2":"MonitoraggioAmministrativo-tab2",
			"ChiusuraCentro-tab2":"MonitoraggioAmministrativo-tab2",
			"MonitoraggioClinico-tab2":"MonitoraggioAmministrativo-tab2",
			"Fatturazione-tab2":"Fatturazione-tab2",
			"metadataTemplate-DatiChiusuraWF2":"MonitoraggioAmministrativo-tab2" } />
			<#-- NASCONDO SAFETY AL MOMENTO NON LA VOGLIONO
			,"Safety-tab2":"MonitoraggioAmministrativo-tab2" } / -->
<div style="display: block">
<div style="float: right">
	<#--include "../helpers/centerActions.ftl"/-->
</div>

<#if infoPanel=="main">
	<fieldset id="child-box" class="child-box">
<#else>
<fieldset style="width:100%">
	<fieldset>

		<div id="processes" style="float:right">
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
								<input id="startProcess" action="${wf.key}" class="submitButton round-button blue templateForm btn btn-info startProcess" type="button" value="${wf.name}">
								<br/>
							</#if>
						</#if>
					</#list>
				</#list>
			</#if>
		</#if>
       	<div id="task-Actions">
        </div>

	</div>
</#if>

</fieldset>


<#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
	<#assign tabOrder=['template.IdCentro','template.DatiCentro','type.TeamDiStudio','type.DepotFarmaco','type.GestioneFarmacia','type.AllegatoCentro','type.IstruttoriaCE','template.Feasibility','template.FeasibilityRESP','type.FeasibilityAreaME','type.Budget','template.ValiditaCTC','type.Contratto']/>
	<#if getUserGroups(userDetails)=='SR'>
		<#assign tabOrder=['template.IdCentro','template.DatiCentro','type.TeamDiStudio','type.AllegatoCentro','template.Feasibility','template.FeasibilityRESP','template.ValiditaCTC','type.Contratto']/>
	</#if>

	<#if el.getfieldData("statoValidazioneCentro", "valCTC")?? && el.getfieldData("statoValidazioneCentro", "valCTC")?size gt 0 && el.getfieldData("statoValidazioneCentro", "valCTC")[0]?split("###")[0] ="1">
		<#if getUserGroups(userDetails)!='SR'>
			<#-- NASCONDO SAFETY AL MOMENTO NON LA VOGLIONO assign tabOrder=tabOrder+['type.AvvioCentro','type.MonitoraggioClinico','type.MonitoraggioAmministrativo','type.ChiusuraCentro','type.Safety','type.ParereCe','type.Fatturazione','template.DatiChiusuraWF']/ -->
			<#assign tabOrder=tabOrder+['type.AvvioCentro','type.MonitoraggioClinico','type.MonitoraggioAmministrativo','type.ChiusuraCentro','type.ParereCe','type.Fatturazione','template.DatiChiusuraWF']/>
		</#if>
		<#if getUserGroups(userDetails)=='SR'>
			<#assign tabOrder=tabOrder+['type.ParereCe','type.Fatturazione','template.DatiChiusuraWF']/>
		</#if>
	<#else>
		<#--GC 14/12/2015 CRPMS-264-->
		<#if getUserGroups(userDetails)!='SR'>
			<#-- NASCONDO SAFETY AL MOMENTO NON LA VOGLIONO assign tabOrder=tabOrder+['disabledType.MonitoraggioAmministrativo','disabledType.Safety','type.ParereCe','disabledType.Fatturazione','disabledTemplate.DatiChiusuraWF']/ -->
			<#assign tabOrder=tabOrder+['disabledType.MonitoraggioAmministrativo','type.ParereCe','disabledType.Fatturazione','disabledTemplate.DatiChiusuraWF']/>
		</#if>
		<#if getUserGroups(userDetails)=='SR'>
			<#assign tabOrder=tabOrder+['type.ParereCe','disabledType.Fatturazione','disabledType.MonitoraggioAmministrativo','disabledTemplate.DatiChiusuraWF']/>
		</#if>
	</#if>
	<#if getUserGroups(userDetails)=='SP'>
		<#assign tabOrder=['template.IdCentro','type.AllegatoCentro']/>
		<#if el.getfieldData("statoValidazioneCentro", "fattLocale")?? && el.getfieldData("statoValidazioneCentro", "fattLocale")?size gt 0 && el.getfieldData("statoValidazioneCentro", "fattLocale")[0]?split("###")[0] ="1">
			<#assign tabOrder=tabOrder+['template.DatiCentro','type.TeamDiStudio','type.DepotFarmaco','type.GestioneFarmacia','template.Feasibility','template.FeasibilityRESP','type.FeasibilityAreaME','type.Budget','template.ValiditaCTC','type.Contratto']/>
		</#if>
		<#if el.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")!="" || el.getFieldDataString("statoValidazioneCentro","idParereCE")!="" >
			<#assign tabOrder=tabOrder+['type.IstruttoriaCE','type.ParereCe'] />
		</#if>
	</#if>
<div id="metadataTemplate-tabs">
	<#list tabOrder as itm>
	<!--${itm} template.IdCentro template.DatiCentro type.AllegatoCentro template.Feasibility type.Budget template.ValiditaCTC-->
		<#assign found=false />
		<#list el.templates as template>
			<!-- ${template.name} IdCentro DatiCentro Feasibility-->
			<#if itm="template."+template.name>
				<!-- ${itm} template.IdCentro template.DatiCentro template.Feasibility -->
				<#assign found=true />
				<!-- STAMPO i TEMPLATE -->
			<#assign tabLabel >
			<@msg "template.${template.name}"/>
			</#assign>

			<#assign tabs=tabs+[{"target":"metadataTemplate-"+template.name+"2","label":tabLabel,"class":"filtered-tab "+tabsGroups["metadataTemplate-"+template.name+"2"]!""}] />
			<!--li><a href="#metadataTemplate-${template.name}"><@msg "template.${template.name}"/></a></li-->
			</#if>
		</#list>

		<!-- STAMPO i TYPE -->
		<#if itm?starts_with("type.")>
				<#assign found=true />
				<#assign tabLabel>
				<@msg "type."+itm?split(".")[1]/>
				</#assign>
				<#assign tabs=tabs+[{"target": itm?split(".")[1]+"-tab"+"2","label":tabLabel,"class":"filtered-tab "+tabsGroups[itm?split(".")[1]+"-tab"+"2"]}] />
				<!--li><a href="#${itm?split(".")[1]}-tab"><@msg "type."+itm?split(".")[1]/></a></li-->
		</#if>

		<!-- stampo i type disabled -->
		<#if itm?starts_with("disabledType.")>
				<#assign found=true />
				<#assign tabLabel>
				<@msg "type."+itm?split(".")[1]/>
				</#assign>

				<#assign tabs=tabs+[{"target": itm?split(".")[1]+"-tab"+"2","label":tabLabel,"disabled":true,"class":"filtered-tab "+tabsGroups[itm?split(".")[1]+"-tab"+"2"]}] />
					<#assign tabsContent=tabsContent+[{"content":"Area non attiva in attesa di completamento della valutazione da parte dell'ufficio ricerca","id":itm?split(".")[1]+"-tab"+"2" }] />
				<!--li><a href="#${itm?split(".")[1]}-tab"><@msg "type."+itm?split(".")[1]/></a></li-->
		</#if>

		<!-- stampo i template disabled -->
		<#if ((itm?starts_with("disabledTemplate.") || !found ) && (tabsGroups[itm?split(".")[1]+"-tab"+"2"]??))>

				<#assign tabLabel>
				<@msg "template."+itm?split(".")[1]/>
				</#assign>
				<#assign tabs=tabs+[{"target": itm?split(".")[1]+"-tab"+"2","label":tabLabel,"disabled":true,"class":"filtered-tab "+tabsGroups[itm?split(".")[1]+"-tab"+"2"]}] />
					<#if itm?starts_with("disabledTemplate.")>
						<#assign tabsContent=tabsContent+[{"content":"Area non attiva in attesa di completamento della valutazione da parte dell'ufficio ricerca","id": itm?split(".")[1]+"-tab"+"2"}] />
					<#else>
						<#assign tabsContent=tabsContent+[{"content":"Area non attiva ","id": itm?split(".")[1]+"-tab"+"2"}] />
					</#if>
				<!--li><a href="#${itm?split(".")[1]}-tab"><@msg "type."+itm?split(".")[1]/></a></li-->
		</#if>

	</#list>


<#assign feasibilityPIChiusa=false />
<#if el.getfieldData("statoValidazioneCentro","fattLocale")?? && el.getfieldData("statoValidazioneCentro","fattLocale")?size gt 0>
    <#assign feasibilityPIChiusa=true />
</#if>

<#-- CICLO I TEMPLATES -->
<#list el.templates as template>	<!-- ${template.name} IdCentro DatiCentro Feasibility QUA-->
	<#if template.fields?? && template.name!="statoValidazioneCentro">


		<#if template.name="Feasibility">
			<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	    	<#list el.elementTemplates as elementTemplate>
	    		<#if elementTemplate.metadataTemplate.name=template.name && elementTemplate.enabled>
						<#assign currTabContent>
						<div class="tabbable">

						<#--Tabella riassuntiva della feasibility PI-->
						<div class="row">
							<div class="col-xs-12">
								<div class="table-responsive">
									<table id="sample-table-1" class="table table-striped table-bordered table-hover">
										<thead>
											<tr>
												<th class="hidden-480" >Principal Investigator</th>
												<th class="hidden-480 center">Stato</th>
												<th class="hidden-480 center">Inviato il</th>
												<th class="hidden-480 center">Inviato da</th>
												<th class="hidden-480 center">Azioni</th>
											</tr>
										</thead>
										<tbody>
											<#assign statoFeasibilityPI="<span class='label label-warning'>Pending</span>"/>
											<#if el.getfieldData("statoValidazioneCentro","fattLocale")?? && el.getfieldData("statoValidazioneCentro","fattLocale")?size gt 0>
												<#if el.getFieldDataCode("statoValidazioneCentro","fattLocale")="1">
													<#assign statoFeasibilityPI="<span class='label label-success'>Positivo</span>" />
												<#elseif el.getFieldDataCode("statoValidazioneCentro","fattLocale")="2">
													<#assign statoFeasibilityPI="<span class='label label-danger'>Negativo</span>" />
												</#if>
											</#if>

											<#assign dataFeasibility="" />
											<#if el.getfieldData("statoValidazioneCentro","fattLocale")?? && el.getfieldData("statoValidazioneCentro","fattLocale")?size gt 0 && el.getFieldDataCode("statoValidazioneCentro","fattLocale")="1">
												<#assign dataFeasibility=getFieldFormattedDate("statoValidazioneCentro","dataFattLocale",el) />
											</#if>

											<#assign userFeasibility="" />
											<#if el.getfieldData("statoValidazioneCentro","UserFattLocale")?? && el.getfieldData("statoValidazioneCentro","UserFattLocale")?size gt 0>
												<#assign userFeasibility=el.getfieldData("statoValidazioneCentro","UserFattLocale")[0] />
											</#if>

											<tr>
												<!--td>${el.getFieldDataDecode("IdCentro","PI")}</td-->
												<td>${el.getFieldDataDecode("IdCentro","PINomeCognome")}</td>
												<td class="center">${statoFeasibilityPI}</td>
												<td class="center">${dataFeasibility}</td>
												<td user-fattpi="${userFeasibility}"  class="center">${userFeasibility}</td>
												<td class="center">

													<#if userDetails.hasRole("CTC") || userDetails.hasRole("REGIONE") || userDetails.hasRole("DIR") || userDetails.hasRole("SEGRETERIA") || userDetails.hasRole("PI") || userDetails.hasRole("COORD") || userDetails.hasRole("SP")>
														<#assign linkAnalisiCentro="target2" />
														<#assign linkChecklist="target1" />
														<#assign onclickFeasPI="" />
													<#else>
														<#assign linkAnalisiCentro="" />
														<#assign linkChecklist="" />
														<#assign onclickFeasPI>
															onclick="alert('Operazione non consentita al profilo attuale')"
														</#assign>
													</#if>

													<div class="visible-md visible-lg hidden-sm hidden-xs action-buttons">
														<#--a class="blue" href="#${linkAnalisiCentro}" ${onclickFeasPI}>
															Analisi centro&nbsp;<i class="icon-zoom-in bigger-130"></i>
														</a>
														<br/-->
														<a class="blue" href="#${linkChecklist}" ${onclickFeasPI}>
															Dati per Fattibilit&agrave;&nbsp;<i class="icon-zoom-in bigger-130"></i>
														</a>
													</div>
												</td>
											</tr>

									</tbody>
									</table>
								</div>
							</div>
						</div>
						<!--fine tabella nuova-->
						<#--FINE-->

						<ul class="nav nav-tabs" >
							<li style="display:none; ">
								<a href="#target2" data-toggle="tab"> Analisi centro </a>
							</li>
							<li style="display:none; ">
								<a href="#target1" data-toggle="tab"> Checklist </a>
							</li>
						</ul>

				<div class="tab-content">

					<div id="target1" class="tab-pane">






				<#list el.templates as template>
					<#if template.name="Feasibility">

						<!-- DIV IMPORTANTISSIMO PER DIFFERENZIARE I CONTENUTI NEI VARI TAB-->
						<div id="metadataTemplate-${template.name}" class="allInTemplate">
						<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
							<#assign editFea=editable && (templatePolicy.canCreate || templatePolicy.canUpdate) />
							<#assign titoloFea="Informazioni per la valutazione locale dello studio" />
							<@TemplateFormTable template.name el userDetails editFea titoloFea classes />
						</div>

					</#if>
				</#list>
			</div>

			<div id="target2" class="tab-pane">

				<#list el.templates as template>
					<#if template.name="AnalisiCentro">

						<!-- DIV IMPORTANTISSIMO PER DIFFERENZIARE I CONTENUTI NEI VARI TAB-->
						<div id="metadataTemplate-${template.name}" class="allInTemplate">
							<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
							<#assign formEdit=false>
	    				<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
	    					<#assign formEdit=true>
      					<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
							</#if>

								<table>
			  					<tr>
			  						<td>
			    						Legenda:
			    					</td>
			    				</tr>
			    				<tr>
			    					<td style="text-align:center; padding-right: 13px;">
			    						<font color=red>*</font>
			    						</td>
			    						<td>
			    						Dato obbligatorio.
			    						</td>
			    					</tr>
			    					<tr>
			    						<td>
			    						<img src="/img/arrow_pdf.jpg" alt="Dato">
			  						</td>
			  						<td>
			    						Dato che verr&agrave; inserito nella documentazione centro specifica.
			  						</td>
			  					</tr>
			  				</table>

	    					<table class="table table-bordered" id="analisi-centro">

									<thead>
										<tr><th colspan="2">Analisi Centro</th></tr>
									</thead>

									<tbody>

	    					<#list template.fields as field>

	    						<#if field.name="tempoMinuti1">
		    							<#--tr><td colspan="2" style="background-color:#DDDDDD"><b>Tempo</b></td></tr-->
		    							<tr><td colspan="2" style="background-color:#DDDDDD"><b>Tempo per il singolo paziente (in minuti)</b></td></tr>
		    					</#if>

		    					<#if field.name="tempoOre1">
		    						<tr><td colspan="2" style="background-color:#DDDDDD"><b>Tempo complessivo attivit&agrave; (in ore)</b></td></tr>
		    					</#if>

	    						<#if field.name="saleOperatorie">
	    							<tr>
	    								<td><b>Totale</b></td>
		    							<td><b>100%</b></td>
		    						</tr>
		    					</#if>

	    						<@SingleFieldTd template.name field.name el userDetails editable/>

     						</#list>

							</tbody>
     					</table>

	    				<table>
		  					<tr>
		  						<td>
		    						Legenda:
		    					</td>
		    				</tr>
		    				<tr>
		    					<td style="text-align:center; padding-right: 13px;">
		    						<font color=red>*</font>
		    						</td>
		    						<td>
		    						Dato obbligatorio.
		    						</td>
		    					</tr>
		    					<tr>
		    						<td>
		    						<img src="/img/arrow_pdf.jpg" alt="Dato">
		  						</td>
		  						<td>
		    						Dato che verr&agrave; inserito nella documentazione centro specifica.
		  						</td>
		  					</tr>
		  				</table>

	    						<#if formEdit>
		    		        		<button id="salvaForm-${template.name}" class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span>
											</button>
		    		        	</form>
		    		      </#if>




	    			</div>
					</#if>
				</#list>

				</div>

		</div>


				</div>


		    		</#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"metadataTemplate-"+template.name+"2" }] />
    </#if>
   </#list>
 </#if>
<#-- Fine template Feasibility -->
<#elseif template.name="FeasibilityRESP">

	<#assign currTabContent>

	<!--inizio tabella nuova-->
	<div class="row">
		<div class="col-xs-12">
		<#if !feasibilityPIChiusa && model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	    		<#if docType.typeId="FeasibilityServiziRichiesta">
					<button class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo Servizio</b></button></br></br>
					<#--
					<@script>
						var messages=null;
						$.getJSON(baseUrl+'/app/rest/documents/messages', function(data){messages=data.resultMap;});
						var modalform=new xCDM_Modal('${baseUrl}', 'FeasibilityServizi', function(){}, function(){}, function(){});
					</@script>
					-->
				</#if>
			</#list>
		</#if>
			<div class="table-responsive">
				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
					<thead>
						<tr>
							<th class="hidden-480" >Servizio Coinvolto</th>
							<th class="hidden-480 center" >Stato</th>
							<th class="hidden-480 center" >Note</th>
							<th class="hidden-480 center" >Inviato il</th>
							<th class="hidden-480 center" >Inviato da</th>
							<th class="hidden-480 center" >Azioni</th>
						</tr>
					</thead>
					<tbody>

					<#assign noServ>
						<tr>
	        		<td colspan=8><span class="help-button">?</span> Nessun servizio coinvolto. Selezionare e salvare i servizi coinvolti e premere il pulsante "Invia ai servizi". </td>
	        	</tr>
          </#assign>

					<#list el.getChildren() as centerChildFeaRich>
						<#assign centerChild=centerChildFeaRich/>
						<#if centerChildFeaRich.getChildren()?size gt 0 && centerChildFeaRich.getChildren()[0]?? >
							<#assign centerChild=centerChildFeaRich.getChildren()[0] />
						</#if>
						<#assign childName=centerChild.getTypeName() />
						<#if childName?starts_with("Feasibility") && !childName?starts_with("FeasibilityArea") && !childName?starts_with("FeasibilityDS")>
							<#assign noServ="" />
							<#assign utenteFeasibility="" />
							<#if centerChild.getfieldData("FeasibilityServWF","Userid")[0]?? && centerChild.getfieldData("FeasibilityServWF","Userid")[0]!="">
								<#assign utenteFeasibility=centerChild.getfieldData("FeasibilityServWF","Userid")[0] />
							</#if>

							<#assign status="<span class='label label-warning'>Pending</span>"/>
							<#if centerChild.getfieldData("FeasibilityServWF","Feasibility")[0]?? && centerChild.getfieldData("FeasibilityServWF","Feasibility")[0]!="">
								<#if centerChild.getfieldData("FeasibilityServWF","Feasibility")[0]?split("###")[0]=="1" >
									<#assign status="<span class='label label-success'>Positivo</span>" />
								</#if>
								<#if centerChild.getfieldData("FeasibilityServWF","Feasibility")[0]?split("###")[0]=="2" >
									<#assign status="<span class='label label-danger'>Negativo</span>" />
								</#if>
							</#if>

							<#assign dataFeasibility="" />
							<#if centerChild.getfieldData("FeasibilityServWF","DataInvio")[0]?? && centerChild.getfieldData("FeasibilityServWF","DataInvio")[0]!="">
								<#assign dataFeasibility=centerChild.getfieldData("FeasibilityServWF","DataInvio")[0].time?date?string.short />
							</#if>


							<#assign noteFeasibility=centerChild.getFieldDataString("FeasibilityServWF","Note") />
							<#assign feaServLink=centerChild.getId() />
							<#if centerChild.getChildren()?size gt 0 && centerChild.getChildren()[0]?? >
								<#assign feaServLink=centerChild.getChildren()[0].getId() />
							</#if>
							<tr>
								<td><a class="center-link" href="${baseUrl}/app/documents/detail/${feaServLink}">${centerChildFeaRich.getFieldDataString("FeasibilitySUO","Servizio")} <br> ${centerChildFeaRich.getFieldDataDecode("FeasibilitySUO","Struttura")} - ${centerChildFeaRich.getFieldDataDecode("FeasibilitySUO","Dipartimento")} - ${centerChildFeaRich.getFieldDataDecode("FeasibilitySUO","UO")} <br> Figure Coinvolte:  ${centerChildFeaRich.getFieldDataString("FeasibilitySUO","FigureCoinvolte")}</a></td>
								<td class="center">${status}</td>
								<td class="center">${noteFeasibility}</td>
								<td class="center">${dataFeasibility}</td>
								<td class="center">${utenteFeasibility}</td>
								<td class="center">
									<div class="visible-md visible-lg hidden-sm hidden-xs">
									<#if getUserGroups(userDetails)!='SP'>
											<button title="Visualizza dettaglio" style="margin-top:0" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${centerChild.getId()}';">
											<i class="icon-edit bigger-120"></i>
										</button>
										</#if>
										<#-- [STSANSVIL-2857] Aggiunta eliminazione Servizi Coinvolti -->
										<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD")>
											<#assign budgetChiuso=false />
											<#if el.getfieldData("statoValidazioneCentro","typeBudgetApproved")?? && el.getfieldData("statoValidazioneCentro","typeBudgetApproved")?size gt 0>
												<#assign budgetChiuso=true />
											</#if>
											<#if feasibilityPIChiusa && budgetChiuso >
												<button title="Elimina" style="margin-top:0" class="btn btn-xs btn-info" onclick="alert('Impossibile eliminare: Budget e/o Fattibilità chiusi')" href="#">
													<i class="icon-trash bigger-120"></i>
												</button>
											<#else>
												<button title="Elimina" style="margin-top:0" class="btn btn-xs btn-info" onclick="deleteServizio({ id:${centerChildFeaRich.getId()} })" href="#">
													<i class="icon-trash bigger-120"></i>
												</button>
											</#if>
										</#if>
									</div>
									
									<#-- assign childId=centerChild.getId() />

									<@GetProcess childId centerChild userDetails / -->

								</td>
							</tr>
						</#if>
					</#list>

					${noServ}

				</tbody>
				</table>
			</div>
		</div>
	</div>
	<!--fine tabella nuova-->


		    		</#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"metadataTemplate-"+template.name+"2" }] />

<#assign currTabContent >

	<#include "../helpers/farmaci-centro-tab.ftl">

</#assign>
<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"DepotFarmaco-tab2" }] />
<#assign currTabContent >

<#include "../helpers/farmaci-gestione-tab.ftl">

</#assign>
<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"GestioneFarmacia-tab2" }] />




<#assign currTabContent >

  <div id="TeamDiStudio-tab">
		<fieldset>
			<!--legend>File allegati</legend-->
    	<#assign parentEl=el/>

    	<#if !feasibilityPIChiusa && model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	    		<#if docType.typeId="TeamDiStudio">
	            <input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Aggiungi personale">
	         </#if>
    		</#list>
    	</#if>

    	<br/><br/>
    	<!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr><td colspan="5" style="background-color:#DDDDDD"><b>PERSONALE DIPENDENTE/CONVENZIONATO SSR PRESSO LA STRUTTURA/UO PROPONENTE</b></td></tr>
								<tr>
									<!--th class="hidden-480" >Dipendente</th-->
									<th class="hidden-480" >Nome e cognome</th>
									<th class="hidden-480" >Ruolo</th>
									<th class="hidden-480" >Azioni</th>
								</tr>
							</thead>

							<tbody>

							<#assign noMembri>
								<tr>
	            		<td colspan=8><span class="help-button">?</span> Nessun componente inserito </td>
	           		</tr>
           		</#assign>

    					<#list parentEl.getChildrenByType("TeamDiStudio") as subEl>
								<#assign nome="" />
								<#assign noMembri="" />
								<#assign attInOrario="" />
								<#assign attOutOrario="" />

								<#if subEl.getFieldDataCode("DatiTeamDiStudio","TipoPersonale")=="1" >

									<#if subEl.getfieldData("DatiTeamDiStudio","NomeCognome")[0]??>
										<#--assign nome=subEl.getfieldData("DatiTeamDiStudio","NomeCognome")[0].getfieldData("PI","PrincInv")[0] /-->
										<#assign nome=subEl.getFieldDataDecode("DatiTeamDiStudio","NomeCognome") />
									<#else>
										<#assign nome=subEl.getFieldDataString("DatiTeamDiStudio","AltroPersonale") />
									</#if>

									<#assign ruolo=subEl.getFieldDataDecode("DatiTeamDiStudio","Ruolo")/>

									<#assign strutturato=subEl.getFieldDataDecode("DatiTeamDiStudio","TipoPersonale")/>


									<tr>
										<#--td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}">${nome}</a></td-->
										<!--td class="hidden-480">${strutturato}</td-->
										<td class="hidden-480">${nome}</td>
										<td class="hidden-480">${ruolo}</td>
										<td>
											<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
												<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
													<i class="icon-edit bigger-120"></i>
												</button>
												<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD") || userDetails.hasRole("REGIONE") || userDetails.hasRole("DIR") || userDetails.hasRole("SEGRETERIA")>
													<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il membro?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
														<i class="icon-trash bigger-120"></i>
													</button>
												</#if>
											</div>
										</td>
									</tr>

								</#if>
							</#list>

							${noMembri}

 							</tbody>
						</table>
					</div>
				</div>
			</div>
    	<!--fine tabella nuova-->


    	<!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr><td colspan="6" style="background-color:#DDDDDD"><b>PERSONALE NON DIPENDENTE/NON CONVENZIONATO SSR PRESSO LA STRUTTURA/UO PROPONENTE</b></td></tr>
								<tr>
									<!--th class="hidden-480" >Dipendente</th-->
									<th class="hidden-480" >Nome e cognome</th>
									<th class="hidden-480" >Ruolo</th>
									<th class="hidden-480" >Ente<br/> appartenenza</th>
									<th class="hidden-480" >Azioni</th>
								</tr>
							</thead>

							<tbody>

							<#assign noMembri>
								<tr>
	            		<td colspan=8><span class="help-button">?</span> Nessun componente inserito </td>
	           		</tr>
           		</#assign>

    					<#list parentEl.getChildrenByType("TeamDiStudio") as subEl>
								<#assign nome="" />
								<#assign noMembri="" />

								<#assign tipoRapporto="" />
								<#assign ente="" />
								<#assign attivitaStudio="" />

								<#if subEl.getFieldDataCode("DatiTeamDiStudio","TipoPersonale")=="2" >

									<#if subEl.getfieldData("DatiTeamDiStudio","NomeCognome")[0]??>
										<#--assign nome=subEl.getfieldData("DatiTeamDiStudio","NomeCognome")[0].getfieldData("PI","PrincInv")[0] /-->
										<#assign nome=subEl.getFieldDataDecode("DatiTeamDiStudio","NomeCognome") />
									<#else>
										<#assign nome=subEl.getFieldDataString("DatiTeamDiStudio","AltroPersonale") />
									</#if>

									<#assign ruolo=subEl.getFieldDataDecode("DatiTeamDiStudio","Ruolo")/>

									<#assign strutturato=subEl.getFieldDataDecode("DatiTeamDiStudio","TipoPersonale")/>

									<#assign ente=subEl.getFieldDataString("DatiTeamDiStudio","EnteNonDip")/>

									<tr>
										<#--td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}">${nome}</a></td-->
										<!--td class="hidden-480">${strutturato}</td-->
										<td class="hidden-480">${nome}</td>
										<td class="hidden-480">${ruolo}</td>
										<td class="hidden-480">${ente}</td>
										<td>
											<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
												<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
													<i class="icon-edit bigger-120"></i>
												</button>
												<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD")>
													<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il membro?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
														<i class="icon-trash bigger-120"></i>
													</button>
												</#if>
											</div>
										</td>
									</tr>

								</#if>
							</#list>

							${noMembri}

 							</tbody>
						</table>
					</div>
				</div>
			</div>
    	<!--fine tabella nuova-->



    	</fieldset>

  </div>
    </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"TeamDiStudio-tab2" }] />




<#-- Fine template FeasibilityREsP -->
<#elseif template.name="TeamRicerca">
			<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	    <#list el.elementTemplates as elementTemplate>
	    	<#if elementTemplate.metadataTemplate.name=template.name && elementTemplate.enabled>
				<!--@TemplateForm template.name el userDetails editable/-->
					<#assign currTabContent>
				<!-- DIV IMPORTANTISSIMO PER DIFFERENZIARE I CONTENUTI NEI VARI TAB-->
				<div id="metadataTemplate-${template.name}" class="allInTemplate">

				<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
	    		<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
      			<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
					</#if>

				<#list template.fields as field>

	    				<div>

	    				<#if field.name="PI1">
	    					<fieldset class="pi">
	    				<legend>Personale strutturato presente in anagrafica</legend>

	    				<div class="clearfix"> </div>

	    				</#if>
	    				<#if field.name="SPEC1">
	    				</fieldset>
	    					<fieldset class="spec">
	    				<legend>Altro personale (dottorandi/specializzandi/altri)</legend>

	    				</#if>

	    				<@SingleField template.name field.name el userDetails editable/>

     				</#list>
	    			</fieldset>

	    			<div class="clearfix">

	    			</div>

	    		</div>

	    			<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
		            	<#--input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm btn btn-warning templateForm" type="button" value="Salva"-->

		            	<button id="salvaForm-${template.name}" class="btn btn-warning templateForm" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span>
									</button>

		            	</form>
		            </#if>
	    			</div>
	    </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"metadataTemplate-"+template.name+"2" }] />
    </#if>
   </#list>
 </#if>

<#-- Fine template TeamRicerca -->
		<#else>
				<#assign currTabContent>

			<div class="centro-template">
				<#-- @TemplateForm template.name el userDetails editable/ -->
					<#assign titolo> <@msg "template.${template.name}"/> </#assign>
				<@TemplateFormTable template.name el userDetails editable titolo classes "false" forceEdit />
			</div>
				</#assign>

				<#if template.name!="AnalisiCentro">

	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"metadataTemplate-"+template.name+"2" }] />

	    	</#if>

<#-- Fine altri template -->
		</#if>

	</#if>


<#-- QUA TERMINO IL CICLO DEI TEMPLATE -->
</#list>

<#-- HO TERMINATO I CICLI, TORNO A ESECUZIONE PRINCIPALE -->




<#-- PARTO CON I CONTENUTI DEI TAB EXTRA -->

 <#assign currTabContent >

  <div id="AllegatoCentro-tab">
		<fieldset>
			<!--legend>File allegati</legend-->
    	<#assign parentEl=el/>
		<#assign elStudio=parentEl.parent />
    	<#if model['getCreatableElementTypes']??>
    		<#list model['getCreatableElementTypes'] as docType>
	    		<#if docType.typeId="AllegatoCentro">
	            <input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Aggiungi documento">
	         </#if>
    		</#list>
    	</#if>

    	<br/><br/>
    	<!--
		<a href="#" onclick="getDocCeCentro(${el.id});">Consulta Area documentale CE</a>
		<a href="#" alt="Scarica Area documentale CE in formato ZIP" title="Scarica Area documentale CE in formato ZIP" onclick="getDocCeCentroZip(${el.id});" ><i class="fa fa-file-archive-o" aria-hidden="true"></i></a>
		-->
        <div id="dialog" style="display:none;" title="Documentazione Centrospecifica"></div>
        <br/><br/>
		<h3>Documentazione centrospecifica</h3>
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
									<th class="hidden-480">Num. Protocollo</th>
									<th class="hidden-480" >Azioni</th>
								</tr>
							</thead>

							<tbody>

							<#assign noDoc>
								<tr>
	            		<td colspan=8><span class="help-button">?</span> Nessun documento inserito </td>
	           		</tr>
           		</#assign>

    					<#list parentEl.getChildrenByType("AllegatoCentro") as subEl>
							<#if subEl.getFieldDataCode("DocCentroSpec","TipoDocumento")?string != "18">
	    						<#assign noDoc="" />
								<#assign tipologia="" />
								<#assign autore="" />
								<#assign version="" />
								<#assign fileName="" />
								<#assign uploadUser="" />
								<#assign uploadDt="" />
								<#assign data="" />
								<!-- QUI ELENCO TUTTI I DOCUMENTI TRANNE QUELLI CON CODICE 18, CIOE QUELLI PERVENUTI POST ISTRUTTORIA-->
								<!-- I DOCUMENTI CON CODICE 18 SONO ELENCATI NELLA TABELLA DI SEGUITO-->
								<#if subEl.getfieldData("DocCentroSpec","TipoDocumento")[0]??>
									<#assign tipologia=subEl.getFieldDataDecode("DocCentroSpec","TipoDocumento") />
									<#if subEl.file?? && subEl.file.autore??>
										<#assign autore=subEl.file.autore />
									</#if>

									<#if subEl.file?? && subEl.file.version??>
										<#assign version=subEl.file.version />
									</#if>

									<#if subEl.file?? && subEl.file.fileName??>
										<#assign fileName=subEl.file.fileName />
									</#if>

									<#if subEl.file?? && subEl.file.uploadUser??>
										<#assign uploadUser=subEl.file.uploadUser />
									</#if>

									<#if subEl.file?? && subEl.file.uploadDt??>
										<#assign uploadDt=subEl.file.uploadDt.time?date?string.short />
									</#if>

									<#if subEl.file?? && subEl.file.date??>
										<#assign data=subEl.file.date.time?date?string.short />
									</#if>
								</#if>

								<tr>
									<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}">${tipologia}</a></td>
									<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${fileName}</a></td>
								<#if subEl.getFieldDataCode("DocCentroSpec","TipoDocumento")!="777">
									<td>${autore}</td>
									<td>${version}</td>
									<td>${data}</td>
									<td user-allegato="${uploadUser}">${uploadUser}</td>
									<td>${uploadDt}</td>
									<td>${subEl.getFieldDataString("DocCentroSpec","ProtocolloNumero")?string}</td>
									<td>
										<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
											<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
												<i class="icon-edit bigger-120"></i>
											</button>
										<#if subEl.getFieldDataString("DocCentroSpec","ProtocolloNumero")?string=="" >
											<button title="Protocolla documento" class="btn btn-xs btn-info" onclick="if(confirm('Sei sicuro di voler protocollare il documento?')) {protocollaElement('${subEl.id}','${subEl.file.fileName}','${elStudio.getFieldDataString("UniqueIdStudio","id")}','${parentEl.getFieldDataString("IdCentro","ProtocolloFascicolo")?string}','DocCentroSpec',${parentEl.id},'${uploadUser}','${elStudio.getFieldDataString("IDstudio","CodiceProt")}','${parentEl.getFieldDataDecode("IdCentro","PINomeCognome")?string}','${tipologia}')};return false;" href="#">
											<i class="fa fa-file-o bigger-120"></i>
											</button>
											<#else>
											<button title="Vedi documento protocollato" class="btn btn-xs btn-info" onclick="vediProtocollo('${subEl.getFieldDataString("DocCentroSpec","ProtocolloNumero")?string}'); return false;" href="#">
											<i class="fa fa-file bigger-120"></i>
											</button>
										</#if>
										<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD")>
										<button title="Elimina" class="btn btn-xs btn-info" onclick="if(confirm('Sei sicuro di voler eliminare il documento?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
											<i class="icon-trash bigger-120"></i>
											</button>
										</#if>
										</div>
									</td>
								<#else>
									<td colspan="7" style="text-align: center"> <b>Documentazione Zip generata il ${uploadDt}, per rigerenarla cliccare sul pulsante in alto "Genera Zip Documentazione"</b></td>
								</#if>
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
		<!--inizio tabella per documenti pervenuti post istruttoria/parere condizionato-->
		<h3>Documentazione post istruttoria/parere condizionato</h3>
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
							<th class="hidden-480">Num. Protocollo</th>
							<th class="hidden-480" >Azioni</th>
						</tr>
						</thead>

						<tbody>

						<#assign noDoc>
						<tr>
							<td colspan=8><span class="help-button">?</span> Nessun documento inserito </td>
						</tr>
						</#assign>

						<#list parentEl.getChildrenByType("AllegatoCentro") as subEl>
						<#if subEl.getFieldDataCode("DocCentroSpec","TipoDocumento")?string == "18">
						<#assign noDoc="" />
						<#assign tipologia="" />
						<#assign autore="" />
						<#assign version="" />
						<#assign fileName="" />
						<#assign uploadUser="" />
						<#assign uploadDt="" />
						<#assign data="" />
						<#if subEl.getfieldData("DocCentroSpec","TipoDocumento")[0]??>
						<#assign tipologia=subEl.getFieldDataDecode("DocCentroSpec","TipoDocumento") />
						<#if subEl.file?? && subEl.file.autore??>
						<#assign autore=subEl.file.autore />
					</#if>

					<#if subEl.file?? && subEl.file.version??>
					<#assign version=subEl.file.version />
				</#if>

				<#if subEl.file?? && subEl.file.fileName??>
				<#assign fileName=subEl.file.fileName />
			</#if>

			<#if subEl.file?? && subEl.file.uploadUser??>
			<#assign uploadUser=subEl.file.uploadUser />
		</#if>

		<#if subEl.file?? && subEl.file.uploadDt??>
		<#assign uploadDt=subEl.file.uploadDt.time?date?string.short />
		</#if>

		<#if subEl.file?? && subEl.file.date??>
		<#assign data=subEl.file.date.time?date?string.short />
		</#if>
		</#if>

		<tr>
			<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}">${tipologia}</a></td>
			<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${fileName}</a></td>
			<#if subEl.getFieldDataCode("DocCentroSpec","TipoDocumento")!="777">
			<td>${autore}</td>
			<td>${version}</td>
			<td>${data}</td>
			<td user-allegato="${uploadUser}">${uploadUser}</td>
			<td>${uploadDt}</td>
			<td>${subEl.getFieldDataString("DocCentroSpec","ProtocolloNumero")?string}</td>
			<td>
				<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
					<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
						<i class="icon-edit bigger-120"></i>
					</button>
					<#if subEl.getFieldDataString("DocCentroSpec","ProtocolloNumero")?string=="" >
					<button title="Protocolla documento" class="btn btn-xs btn-info" onclick="if(confirm('Sei sicuro di voler protocollare il documento?')) {protocollaElement('${subEl.id}','${subEl.file.fileName}','${elStudio.getFieldDataString("UniqueIdStudio","id")}','${parentEl.getFieldDataString("IdCentro","ProtocolloFascicolo")?string}','DocCentroSpec',${parentEl.id},'${uploadUser}','${elStudio.getFieldDataString("IDstudio","CodiceProt")}','${parentEl.getFieldDataDecode("IdCentro","PINomeCognome")?string}','${tipologia}')};return false;" href="#">
					<i class="fa fa-file-o bigger-120"></i>
					</button>
					<#else>
					<button title="Vedi documento protocollato" class="btn btn-xs btn-info" onclick="vediProtocollo('${subEl.getFieldDataString("DocCentroSpec","ProtocolloNumero")?string}'); return false;" href="#">
					<i class="fa fa-file bigger-120"></i>
					</button>
				</#if>
				<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD")>
				<button title="Elimina" class="btn btn-xs btn-info" onclick="if(confirm('Sei sicuro di voler eliminare il documento?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
					<i class="icon-trash bigger-120"></i>
				</button>
			</#if>
			</div>
			</td>
			<#else>
			<td colspan="7" style="text-align: center"> <b>Documentazione Zip generata il ${uploadDt}, per rigerenarla cliccare sul pulsante in alto "Genera Zip Documentazione"</b></td>
		</#if>
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

	  </div>

    </#assign>
	 <#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"AllegatoCentro-tab2" }] />







 <#assign currTabContent >
 <div id="IstruttoriaCE-tab">
		<fieldset>
    	<#assign parentEl=el/>
		<#assign istruttoriaInCompilazione=false />
		<#list parentEl.getChildrenByType("IstruttoriaCE") as istruttoria>
			<#if !istruttoriaInCompilazione && istruttoria.getFieldDataString("IstruttoriaCE","istruttoriaWFinviata")=="" >
				<#assign istruttoriaInCompilazione=true />
			</#if>
		</#list>
		<!--istruttoria in compilazione? ${istruttoriaInCompilazione?c}
		valCTC? ${el.getFieldDataCode("statoValidazioneCentro","valCTC")}
		inviatoCE? ${el.getFieldDataCode("statoValidazioneCentro","inviatoCE")}
		idIstruttoriaCEPositiva? ${el.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")}-->

		<#if (el.getFieldDataCode("statoValidazioneCentro","fattLocale")=="1" || el.getFieldDataString("statoValidazioneCentro","inviatoCE")=="1") && !istruttoriaInCompilazione && el.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")=="">
<!-- istruttoria in compilazione? ${istruttoriaInCompilazione?c}
valCTC? ${el.getFieldDataCode("statoValidazioneCentro","valCTC")}
inviatoCE? ${el.getFieldDataCode("statoValidazioneCentro","inviatoCE")}
idIstruttoriaCEPositiva? ${el.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")} -->
			<#if model['getCreatableElementTypes']??>
				<#list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="IstruttoriaCE">
					<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Nuova Istruttoria">
				</#if>
				</#list>
			</#if>

		</#if>


    	<br/><br/>

        <!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<th class="hidden-480" style="width:1%">Data</th>
									<th class="hidden-480" >Codice interno</th>
									<th class="hidden-480" >Documentazione completa</th>
									<th class="hidden-480" >Osservazioni</th>
									<th class="hidden-480" >Azioni</th>
 								</tr>
							</thead>

							<tbody>

							<#assign noDoc>
								<tr>
	            		<td colspan=8><span class="help-button">?</span> Nessun documento inserito </td>
	           		</tr>
           		</#assign>

    					<#list parentEl.getChildrenByType("IstruttoriaCE") as subEl>
	    						<#assign noDoc="" />


								<tr>
									<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}"> ${subEl.getFieldDataDate("IstruttoriaCE","DataRicDoc").time?date?string.short}</a></td>
									<td>${subEl.getFieldDataString("IstruttoriaCE","DelibNum")}</td>
									<td>${subEl.getFieldDataDecode("IstruttoriaCE","DocCompleta")}</td>
									<td>${subEl.getFieldDataString("IstruttoriaCE","Osservazioni")}</td>
									<td>
										<button title="Visualizza dettaglio" class="btn btn-info btn-xs" style="margin-top:0px" onclick="window.location.href='${baseUrl}/app/documents/detail/${subEl.id}'" > <i class="icon icon-edit"></i></button>
										<#if subEl.getFieldDataCode("IstruttoriaCE","DocCompleta")!="">
											<div id="task-Actions-${subEl.id}" style="float:right"></div>
											<@script>
											loadTasksById(${subEl.id});
											</@script>
										</#if>
									</td>
								</tr>
						</#list>

							${noDoc}

 							</tbody>
						</table>
					</div>
				</div>
			</div>
    	<!--fine tabella nuova-->



    	</fieldset>

  </div>
    </#assign>
	 <#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"IstruttoriaCE-tab2" }] />









	<#assign currTabContent >
		<div id="FeasibilityAreaME-tab">
  	<!--inizio tabella nuova-->
	<div class="row">
		<div class="col-xs-12">
			<div class="table-responsive">
				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
					<thead>
						<tr>
							<th class="hidden-480"        style="width:20%">Valutazione finale aziendale</th>
							<th class="hidden-480 center" style="width:10%">Stato</th>
							<th class="hidden-480 center" style="width:25%">Note</th>
							<th class="hidden-480 center" style="width:20%">Rilasciata da</th>
							<th class="hidden-480 center" style="width:10%">Inviata il</th>
							<th class="hidden-480 center" style="width:10%">Inviata da</th>
							<th class="hidden-480 center" style="width:5%">Azioni</th>
						</tr>
					</thead>
					<tbody>

					<#assign noValRespIStr>
						<tr>
          		<td colspan=9><span class="help-button">?</span> Esito non presente </td>
         		</tr>
       		</#assign>

					<#list el.getChildren() as centerChild>
						<#assign childName=centerChild.getTypeName() />
						<#if childName?starts_with("ValutazioneRI")>
							<#assign noValRespIStr="" />
							<#assign utenteFeasibility="" />

							<#if centerChild.getfieldData("ValutazioneRIWF","Userid")[0]?? && centerChild.getfieldData("ValutazioneRIWF","Userid")[0]!="">
								<#assign utenteFeasibility=centerChild.getfieldData("ValutazioneRIWF","Userid")[0] />
							</#if>

							<#assign status="<span class='label'>Pending</span>"/>
							<#if centerChild.getfieldData("ValutazioneRIWF","val")[0]?? && centerChild.getfieldData("ValutazioneRIWF","val")[0]!="">
								<#if centerChild.getfieldData("ValutazioneRIWF","val")[0]?split("###")[0]=="1" >
									<#assign status="<span class='label label-success'>Positivo</span>" />
								</#if>
								<#if centerChild.getfieldData("ValutazioneRIWF","val")[0]?split("###")[0]=="2" >
									<#assign status="<span class='label label-danger'>Negativo</span>" />
								</#if>
								<#if centerChild.getfieldData("ValutazioneRIWF","val")[0]?split("###")[0]=="3" >
									<#assign status="<span class='label label-warning'>Sospeso</span>" />
								</#if>
							</#if>

							<#assign dataFeasibility="" />
							<#if centerChild.getfieldData("ValutazioneRIWF","DataInvio")[0]?? && centerChild.getfieldData("ValutazioneRIWF","DataInvio")[0]!="">
								<#assign dataFeasibility=centerChild.getfieldData("ValutazioneRIWF","DataInvio")[0].time?date?string.short />
							</#if>

							<#assign note="" />
							<#if centerChild.getfieldData("ValutazioneRIWF","note")[0]?? && centerChild.getfieldData("ValutazioneRIWF","note")[0]!="">
								<#assign note=centerChild.getfieldData("ValutazioneRIWF","note")[0] />
							</#if>

							<#assign rilasciataDa="" />
							<#if centerChild.getfieldData("ValutazioneRIWF","rilasciataDa")[0]?? && centerChild.getfieldData("ValutazioneRIWF","rilasciataDa")[0]!="">
								<#assign rilasciataDa=centerChild.getfieldData("ValutazioneRIWF","rilasciataDa")[0] />
							</#if>
							<tr>
								<td>${centerChild.titleString}</td>
								<td class="center">${status}</td>
								<td class="center">${note}</td>
								<td class="center">${rilasciataDa}</td>
								<td class="center">${dataFeasibility}</td>
								<td user-fattctc="${utenteFeasibility}"  class="center">${utenteFeasibility}</td>
								<td class="center"> - </td>
							</tr>
						</#if>
					</#list>

					${noValRespIStr}

				</tbody>
				</table>
			</div>
		</div>
	</div>
	<!--fine tabella nuova-->




	<!--inizio tabella nuova-->

	<#--GC 07/09/2016 commentato in attesa di requisiti TOSCANA-31
	<#assign Profit=getCode("datiStudio","Profit",el.parent) />
	<#if Profit=="2">
		<div class="row">
			<div class="col-xs-12">
				<div class="table-responsive">
					<table id="sample-table-1" class="table table-striped table-bordered table-hover">
						<thead>
							<tr>
								<th class="hidden-480"        style="width:25%">Autorizzazione Direttore Sanitario</th>
								<th class="hidden-480 center" style="width:10%">Autizzazione</th>
								<th class="hidden-480 center" style="width:35%">Note</th>
								<th class="hidden-480 center" style="width:10%">Inviato il</th>
								<th class="hidden-480 center" style="width:15%">Inviato da</th>
								<th class="hidden-480 center" style="width:5%">Azioni</th>
							</tr>
						</thead>
						<tbody>

						<#list el.getChildren() as centerChild>
							<#assign childName=centerChild.getTypeName() />
							<#if childName==("FeasibilityDS")>
								<#assign utenteAdempimenti="" />

								<#if centerChild.getfieldData("FeasibilityDSWF","Userid")[0]?? && centerChild.getfieldData("FeasibilityDSWF","Userid")[0]!="">
									<#assign utenteAdempimenti=centerChild.getfieldData("FeasibilityDSWF","Userid")[0] />
								</#if>

								<#assign status="<span class='label'>Pending</span>"/>
								<#if centerChild.getfieldData("FeasibilityDSWF","Autorizzazione")[0]?? && centerChild.getfieldData("FeasibilityDSWF","Autorizzazione")[0]!="">
									<#if centerChild.getfieldData("FeasibilityDSWF","Autorizzazione")[0]?split("###")[0]=="1" >
										<#assign status="<span class='label label-success'>Positiva</span>" />
									</#if>
									<#if centerChild.getfieldData("FeasibilityDSWF","Autorizzazione")[0]?split("###")[0]=="2" >
										<#assign status="<span class='label label-danger'>Negativa</span>" />
									</#if>
								</#if>

								<#assign dataAdempimenti="" />
								<#if centerChild.getfieldData("FeasibilityDSWF","DataInvio")[0]?? && centerChild.getfieldData("FeasibilityDSWF","DataInvio")[0]!="">
									<#assign dataAdempimenti=centerChild.getfieldData("FeasibilityDSWF","DataInvio")[0].time?date?string.short />
								</#if>

								<#assign noteAdempimenti="" />
								<#if centerChild.getfieldData("FeasibilityDSWF","note")[0]?? && centerChild.getfieldData("FeasibilityDSWF","note")[0]!="">
									<#assign noteAdempimenti=centerChild.getfieldData("FeasibilityDSWF","note")[0] />
								</#if>

								<tr>

									<#assign ValRespIstr="" />

									<#if el.getfieldData("statoValidazioneCentro","valCTC")[0]??>
										<#assign ValRespIstr=el.getFieldDataCode("statoValidazioneCentro","valCTC") />
									</#if>

									<#assign checkLink="" /-->
									<#--if ValRespIstr=="1">
										<#assign checkLink="" />
									<#else>
										<#assign checkLink>
											onclick="alert('Attenzione! E\' possibile compilare la scheda dopo la verifica positiva del Responsabile Istruttoria');return false;"
										</#assign>
									</#if-->

									<#--td><a class="center-link" ${checkLink} href="${baseUrl}/app/documents/detail/${centerChild.getId()}">${centerChild.titleString}</a></td>
									<td class="center">${status}</td>
									<td class="center">${noteAdempimenti}</td>
									<td class="center">${dataAdempimenti}</td>
									<td class="center">${utenteAdempimenti}</td>
									<td class="center">
										<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
											<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${centerChild.getId()}'">
												<i class="icon-edit bigger-120"></i>
											</button>
										</div>
									</td>
								</tr>
							</#if>
						</#list>

					</tbody>
					</table>
				</div>
			</div>
		</div>
	</#if-->
	<!--fine tabella nuova-->


	<#assign byPassFirmaContratto="0">
	<!--inizio tabella nuova-->
	<#--GC 07/09/2016 commentato in attesa di requisiti TOSCANA-31
	<div class="row">
		<div class="col-xs-12">
			<div class="table-responsive">
				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
					<thead>
						<tr>
							<th class="hidden-480"        style="width:25%">Attivit&agrave; di valutazione POST CESC</th>
							<th class="hidden-480 center" style="width:10%">Stato</th>
							<th class="hidden-480 center" style="width:35%">Note</th>
							<th class="hidden-480 center" style="width:10%">Inviato il</th>
							<th class="hidden-480 center" style="width:15%">Inviato da</th>
							<th class="hidden-480 center" style="width:5%">Azioni</th>
						</tr>
					</thead>
					<tbody>


					<#assign ValRespIstr="" />
					<#if el.getfieldData("statoValidazioneCentro","valCTC")[0]??>
						<#assign ValRespIstr=el.getFieldDataCode("statoValidazioneCentro","valCTC") />
					</#if>
					<#if ValRespIstr=="1">
						<#assign checkLink="" />
					<#else>
						<#assign checkLink>
							onclick="alert('Attenzione! E\' possibile compilare la scheda dopo la verifica positiva del Responsabile Istruttoria');return false;"
						</#assign>
					</#if>


					<#list el.getChildren() as centerChild>
						<#assign childName=centerChild.getTypeName() />
						<#if childName?starts_with("AdempimentiAmm")>

							<#assign utenteAdempimenti="" />

							<#if centerChild.getfieldData("AdempimentiAmmWF","Userid")[0]?? && centerChild.getfieldData("AdempimentiAmmWF","Userid")[0]!="">
								<#assign utenteAdempimenti=centerChild.getfieldData("AdempimentiAmmWF","Userid")[0] />
							</#if>

							<#assign status="<span class='label'>Pending</span>"/>
							<#if centerChild.getfieldData("AdempimentiAmmWF","Esito")[0]?? && centerChild.getfieldData("AdempimentiAmmWF","Esito")[0]!="">
								<#if centerChild.getfieldData("AdempimentiAmmWF","Esito")[0]?split("###")[0]=="1" >
									<#assign status="<span class='label label-success'>Positivo</span>" />
								</#if>
								<#if centerChild.getfieldData("AdempimentiAmmWF","Esito")[0]?split("###")[0]=="2" >
									<#assign status="<span class='label label-danger'>Negativo</span>" />
								</#if>
								<#if centerChild.getfieldData("AdempimentiAmmWF","Esito")[0]?split("###")[0]=="3" >
									<#assign status="<span class='label label-warning'>Sospeso</span>" />
								</#if>
								<#if centerChild.getfieldData("AdempimentiAmmWF","Esito")[0]?split("###")[0]=="4" >
									<#assign status="<span class='label label-info'>In carico</span>" />
								</#if>
							</#if>

							<#assign dataAdempimenti="" />
							<#if centerChild.getfieldData("AdempimentiAmmWF","DataInvio")[0]?? && centerChild.getfieldData("AdempimentiAmmWF","DataInvio")[0]!="">
								<#assign dataAdempimenti=centerChild.getfieldData("AdempimentiAmmWF","DataInvio")[0].time?date?string.short />
							</#if>

							<#assign noteAdempimenti="" />
							<#if centerChild.getfieldData("AdempimentiAmmWF","note")[0]?? && centerChild.getfieldData("AdempimentiAmmWF","note")[0]!="">
								<#assign noteAdempimenti=centerChild.getfieldData("AdempimentiAmmWF","note")[0] />
							</#if>

							<tr>

								<#assign attivita>
									<a class="center-link" ${checkLink} href="${baseUrl}/app/documents/detail/${centerChild.getId()}">${centerChild.titleString}</a>
								</#assign>

								<#assign azioni>
									<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
										<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${centerChild.getId()}'">
											<i class="icon-edit bigger-120"></i>
										</button>
									</div>
								</#assign>

								<#if childName=="AdempimentiAmmGA" && ValRespIstr=="1" && contrattoNecessario=="2">
									<#assign attivita>
										${centerChild.titleString}
									</#assign>
									<#assign status="N.A." />
									<#assign noteAdempimenti="Contratto non necessario" />
									<#assign azioni="" />
									<#assign byPassFirmaContratto="1" />
								</#if>

								<td>${attivita}</td>
								<td class="center">${status}</td>
								<td class="center">${noteAdempimenti}</td>
								<td class="center">${dataAdempimenti}</td>
								<td class="center">${utenteAdempimenti}</td>
								<td class="center">${azioni}</td>
							</tr>
						</#if>
					</#list>

				</tbody>
				</table>
			</div>
		</div>
	</div-->
	<!--fine tabella nuova-->


		</div>

        </#assign>
        <#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"FeasibilityAreaME-tab2" }] />




	<#if getUserGroups(userDetails)!='SR'>
<#assign currTabContent >
		<div id="Budget-tab">
    <#assign parentEl=el/>
    <#assign butt1="" />
    <#assign butt2="" />
    <#assign butt3="" />
    <#if model['getCreatableElementTypes']??>
  		<#list model['getCreatableElementTypes'] as docType>

    		<#if docType.typeId="Budget">
    	<#assign butt1>
        	<!--input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Crea nuovo budget"-->
			<input type="button" class="submitButton round-button blue templateForm btn btn-info" id="nuovoBudget" name="nuovoBudget" onclick="return false;" value="Crea nuovo budget" />
        </#assign>
        </#if>
        <#if docType.typeId="BudgetBracci">
        	<#assign butt2>
        	<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Crea nuovo budget a bracci">
        	</#assign>
        </#if>
        <#if docType.typeId="PropostaSponsor">
        	<#assign butt3>
       		<#assign proposta=el.getChildrenByType('PropostaSponsor') />
       		<#if (proposta?size == 0) >
        		<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Inserisci prima proposta promotore">
        	<#else>
        		<#list proposta as currPoposta>
        		<#--input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/detail/${currPoposta.id}';" value="${currPoposta.getTitleString()}"-->
        		<#--@modal "myTest" "test modal" "click" "Hello world!" /-->
        		<#assign checks>
        			if(isNaN($('#PropostaSponsor_TotalePazienteSponsor').val())){
		                alert("Il valore della proposta promotore deve essere numerico");
		                $('#PropostaSponsor_TotalePazienteSponsor').focus();
		                return false;
		            }

        		</#assign>
        		<@templateModalForm "PropostaSponsor" currPoposta userDetails true currPoposta.getTitleString() checks />
        		</#list>
        	</#if>
        	</#assign>
        </#if>
  		</#list>
		</#if>
		${butt1} <#--${butt2} SIRER-18 nascondo creazione budget a bracci-->
		<br><br>
		<#assign center=el />
    <#assign allBudgets=center.getChildrenByType('Budget') />
    <#if ( allBudgets?size > 0 ) >
     <#include "../helpers/budget/tabellaVersioni.ftl"/>
  	 </#if>
  	<#assign allBudgets=center.getChildrenByType('BudgetBracci') />
     <#if ( allBudgets?size > 0 ) >
     <#include "../helpers/budget/tabellaVersioniBB.ftl"/>
     </#if>
		</div>




        </#assign>
        <#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"Budget-tab2" }] />
</#if>

		<#assign currTabContent >
		<div id="Contratto-tab">
    	<#assign parentEl=el/>

        <#if (el.getfieldData("statoValidazioneCentro", "valCTC")?? && el.getfieldData("statoValidazioneCentro", "valCTC")?size gt 0 && el.getfieldData("statoValidazioneCentro", "valCTC")[0]?split("###")[0] ="1") && userDetails.hasRole("CTC") || userDetails.hasRole("SR")>
	      <!--nuovo bottone di creazione contratto che crea subito l'oggetto contratto-->
	    	<input type="button" style="margin-bottom:10px" class="submitButton round-button blue btn btn-info" id="creacontratto" value="Nuovo iter di avvio">
		</#if>

    	<!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<th class="hidden-480">Versione</th>
									<th class="hidden-480">Creato da</th>
									<th class="hidden-480">Ultima modifica</th>
									<th class="hidden-480">Stato</th>
									<th class="hidden-480">Scadenza</th>
									<#--th class="hidden-480">Corpus (ultima versione)</th>
									<th class="hidden-480">All.A (ultima versione)</th>
									<th class="hidden-480">All.B (ultima versione)</th-->
									<th>Azioni</th>
								</tr>
							</thead>

							<tbody>

							<#assign noContr>
								<tr>
	            		<td colspan=9><span class="help-button">?</span> Nessun documento inserito </td>
	           		</tr>
           		</#assign>

							<#assign versioneContratto=0 />
				      <!--#assign contrattoPresente=false/-->
				  		<#list parentEl.getChildrenByType("Contratto") as subEl>

				  		<#assign noContr="" />

				  		<!--h3><a href="${baseUrl}/app/documents/detail/${subEl.id}">Accedi al Contratto <#if subEl.file??>${subEl.file.version} (${subEl.file.date.time?datetime?string.full})</#if></a></h3-->
				  		<!--#assign contrattoPresente=true/-->
  						<#assign versioneContratto=versioneContratto+1 />

  							<#assign createUser="" />
  							<#if subEl.createUser??>
  								<#assign createUser=subEl.createUser />
  							</#if>

  							<#assign lastUpdateDt="" />
  							<#if subEl.lastUpdateDt??>
  								<#assign lastUpdateDt=subEl.lastUpdateDt.time?date?string.short />
  							<#else>
  								<#assign lastUpdateDt=subEl.creationDt.time?date?string.short />
  							</#if>

  							<!--CTC GEMELLI-->
  							<#assign scadenza="" />
  							<#if subEl.getfieldData("ValiditaContratto","UltimaScadenza")[0]??>
  								<#assign scadenza=getFieldFormattedDate("ValiditaContratto", "UltimaScadenza", subEl) />
  							<#elseif subEl.getfieldData("ValiditaContratto","DataFineVal")[0]??>
  								<#assign scadenza=getFieldFormattedDate("ValiditaContratto", "DataFineVal", subEl) />
  							</#if>

  							<!--NRC PADOVA-->
  							<#assign scadenza="" />
  							<!--if da gestire quando sistemo il rinnovo contratto-->
  							<#if subEl.getfieldData("ValiditaContratto","UltimaScadenza")[0]??>
  								<#assign scadenza=getFieldFormattedDate("ValiditaContratto", "UltimaScadenza", subEl) />
  							<#elseif subEl.getfieldData("preFirmaContrattoWF","fineValidita")[0]??>
  								<#assign scadenza=getFieldFormattedDate("preFirmaContrattoWF", "fineValidita", subEl) />
  							</#if>


  							<!--
  							<#assign tipologia="" />
								<#assign autore="" />
								<#assign version="" />
								<#assign fileName="" />
								<#assign uploadUser="" />
								<#assign uploadDt="" />
								<#assign data="" />
								<#if subEl.getfieldData("DocCentroSpec","TipoDocumento")[0]??>
									<#assign tipologia=subEl.getFieldDataDecode("DocCentroSpec","TipoDocumento") />
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
								-->

								<!--file allegati-->
								<#assign fileCorpus="" />
								<#assign fileCorpusVers="" />
								<#assign fileCorpusId="" />
								<#assign fileAllA="" />
								<#assign fileAllAVers="" />
								<#assign fileAllAId="" />
								<#assign fileAllB="" />
								<#assign fileAllBVers="" />
								<#assign fileAllBId="" />
								<#list subEl.getChildrenByType("AllegatoContratto") as allContrEl>
									<#if allContrEl.getfieldData("tipologiaContratto","TipoContratto")[0]??>
										<#if allContrEl.getFieldDataCode("tipologiaContratto","TipoContratto")=="1">
											<#if allContrEl.file.fileName??>
												<#assign fileCorpus=allContrEl.file.fileName />
												<#assign fileCorpusVers=allContrEl.file.version />
												<#assign fileCorpusId=allContrEl.getId() />
											</#if>
										</#if>
										<#if allContrEl.getFieldDataCode("tipologiaContratto","TipoContratto")=="2">
											<#if allContrEl.file.fileName??>
												<#assign fileAllA=allContrEl.file.fileName />
												<#assign fileAllAVers=allContrEl.file.version />
												<#assign fileAllAId=allContrEl.getId() />
											</#if>
										</#if>
										<#if allContrEl.getFieldDataCode("tipologiaContratto","TipoContratto")=="3">
											<#if allContrEl.file.fileName??>
												<#assign fileAllB=allContrEl.file.fileName />
												<#assign fileAllBVers=allContrEl.file.version />
												<#assign fileAllBId=allContrEl.getId() />
											</#if>
										</#if>
									</#if>
								</#list>

								<!--stato-->
								<#assign statoContratto="" />
								<#list subEl.getChildrenByType("LettAccFirmaContr") as child>
									<#if child.id?? && child.file??>
										<#assign statoContratto="Firmato" />
									</#if>
								</#list>

								<#if subEl.getfieldData("ApprovDADSRETT", "Approvazione")[0]?? && subEl.getfieldData("ApprovDADSRETT", "Approvazione")[0]?split("###")[0]=="1">
									<#assign statoContratto="Approvato"/>
								</#if>

								<#if subEl.getfieldData("ValiditaContratto", "dataSponsor")[0]??>
									<#assign statoContratto="Inviato SP"/>
								</#if>

								<#if subEl.getfieldData("ValiditaContratto", "armadio")[0]??>
									<#assign statoContratto="Archiviato"/>
								</#if>


								<tr>
									<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}">${versioneContratto}</a></td>
									<td>${createUser}</td>
									<td>${lastUpdateDt}</td>
									<td class="hidden-480">${statoContratto}</td>
									<td>${scadenza}</td>
									<#--td title="${fileCorpus} (v. ${fileCorpusVers})"><#if fileCorpusId?string!=""><a class="center-link" href="${baseUrl}/app/documents/getAttach/${fileCorpusId}"> ${limit(fileCorpus,15)} (v.&nbsp;${fileCorpusVers})</a></#if></td>
									<td><#if fileAllAId?string!=""><a class="center-link" href="${baseUrl}/app/documents/getAttach/${fileAllAId}"> ${limit(fileAllA,15)} (v.&nbsp;${fileAllAVers})</a></#if></td>
									<td><#if fileAllBId?string!=""><a class="center-link" href="${baseUrl}/app/documents/getAttach/${fileAllBId}"> ${limit(fileAllB,15)} (v.&nbsp;${fileAllBVers})</a></#if></td-->
									<td>
										<div class="visible-md visible-lg hidden-sm hidden-xs action-buttons">
											<a class="blue" href="${baseUrl}/app/documents/detail/${subEl.id}">
												<i class="icon-zoom-in bigger-130"></i>
											</a>
										</div>
									</td>
								</tr>
  						</#list>

  						${noContr}

  					</tbody>
						</table>
					</div>
				</div>
			</div>
    	<!--fine tabella nuova-->




  		<!--#if !contrattoPresente&&  model['getCreatableElementTypes']??-->
  		<#if model['getCreatableElementTypes']??>
  			<#list model['getCreatableElementTypes'] as docType>
    			<#if docType.typeId="Contratto">

    	    	<!--vecchio bottone di aggiunta contratto che passava per la il template dei dati del referente e poi creava l'oggetto contratto-->
    	  		<!--input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Aggiungi contratto"-->

    	    	<@script>

							    $('#creacontratto').click(function(){

										var formData=new FormData();
										formData.append("parentId", "${el.id}");
										var actionUrl="${baseUrl}/app/rest/documents/save/${docType.id}";

										 $.ajax({
										            type: "POST",
										            url: actionUrl,
										            contentType:false,
										            processData:false,
										            async:false,
										            cache:false,
										            data: formData,
										            success: function(obj){
										                 if (obj.result=="OK") {
										                    window.location.href="${baseUrl}/app/documents/detail/"+obj.ret;
										                 }
										            }
										        });
										    });

						</@script>


    	    </#if>
  			</#list>
  		</#if>


    </div>
        </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"Contratto-tab2" }] />
	    <#assign currTabContent >


		<!-- INIZIO SPECCHIETTO PARERI -->


    <div id="ParereCe-tab">
    	<fieldset>
	    	<legend>Pareri Comitato Etico</legend>
			<#assign parentEl=el/>
			<#assign istruttoriaInCompilazione=false />
		<#list parentEl.getChildrenByType("IstruttoriaCE") as istruttoria>
			<#if !istruttoriaInCompilazione && istruttoria.getFieldDataString("IstruttoriaCE","istruttoriaWFinviata")=="" >
				<#assign istruttoriaInCompilazione=true />
			</#if>
		</#list>
		<#if (el.getFieldDataCode("statoValidazioneCentro","fattLocale")=="1" || el.getFieldDataString("statoValidazioneCentro","inviatoCE")=="1") && !istruttoriaInCompilazione && el.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")!="" && el.getFieldDataString("statoValidazioneCentro","idParereCE")=="">

			<#if model['getCreatableElementTypes']??>
				<#list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="ParereCe">
					<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Nuovo Parere">
				</#if>
				</#list>
			</#if>

		</#if>
			<br><br>

  			 <!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<th class="hidden-480" style="width:1%">Data prima seduta</th>
									<th class="hidden-480" >Data riesame</th>
									<th class="hidden-480" >Parere</th>
									<th class="hidden-480" >Note</th>
									<th class="hidden-480" >Azioni</th>
 								</tr>
							</thead>

							<tbody>

							<#assign noDoc>
								<tr>
				            		<td colspan=8><span class="help-button">?</span> Nessun documento inserito </td>
				           		</tr>
			           		</#assign>
							<#assign parerePositivo="false" />
			           		<#list parentEl.getChildrenByType("ParereCe") as subEl>
			           			<#assign noDoc="" />

								<tr>
									<td><a class="center-link" href="${baseUrl}/app/documents/detail/${subEl.id}"> ${subEl.getFieldDataDate("ParereCe","dataSeduta").time?date?string.short}</a></td>
									<td>${subEl.getFieldDataDate("ParereCe","dataSeduta").time?date?string.short}</td>
									<td>${subEl.getFieldDataDecode("ParereCe","esitoParere")}</td>
									<#if subEl.getFieldDataCode("ParereCe","esitoParere")=="1" || subEl.getFieldDataCode("ParereCe","esitoParere")=="4" >
										<#assign parerePositivo="true" />
									</#if>
									<td>${subEl.getFieldDataString("ParereCe","Note")}</td>
									<td>
										<button title="Visualizza dettaglio" class="btn btn-info btn-xs" style="margin-top:0px" onclick="window.location.href='${baseUrl}/app/documents/detail/${subEl.id}'" > <i class="icon icon-edit"></i></button>
										<#if subEl.file?? && subEl.file.fileName?? >
											<#--  if subEl.getFieldDataString("ParereCe","ProtocolloNumero")?string=="" >
												<!-- button title="Protocolla documento" class="btn btn-xs btn-danger" style="margin-top:0px" onclick="if(confirm('Sei sicuro di voler protocollare il documento?')) {protocollaElement('${subEl.id}','${subEl.file.fileName}','${el.id}','${parentEl.getFieldDataString("IdCentro","ProtocolloFascicolo")?string}','ParereCe',${parentEl.id})};return false;" href="#">
													<i class="icon-file bigger-120"></i>
												</button>
											<#else>
												<button title="Vedi documento protocollato" class="btn btn-xs btn-danger" style="margin-top:0px" onclick="vediProtocollo('${subEl.getFieldDataString("ParereCe","ProtocolloNumero")?string}'); return false;" href="#">
													<i class="icon-file bigger-120"></i>
												</button -->
											</ #if -->
										<#else>
											<button title="Nessun documento allegato" class="btn btn-xs btn-danger" style="background-color:#888 !important;color:#ddd !important; margin-top:0px" onclick="alert('nessun documento allegato'); return false;" href="#">
												<i class="icon-file bigger-120"></i>
											</button>
										</#if>
										<button title="Compila Lettera di parere" class="btn btn-info btn-xs" style="margin-top:0px" onclick="window.open('/documentazione/?/lettere/parere/${parentEl.parent.id}/${parentEl.id}/${subEl.id}');" > <i class="icon-file-text"></i></button>
										<#if subEl.getFieldDataCode("ParereCe","esitoParere")!="">
											<div id="task-Actions-${subEl.id}" style="float:right"></div>
											<@script>
											loadTasksById(${subEl.id});
											</@script>
										</#if>
									</td>
								</tr>
			           		</#list>

			           		${noDoc}

 							</tbody>
						</table>
					</div>
				</div>
			</div>
    	<!--fine tabella nuova-->


  		</fieldset>

		</div>


		<!-- FINE SPECCHIETTO PARERI -->

        </#assign>
		<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"ParereCe-tab2" }] />

	<#if getUserGroups(userDetails)!='SR'>
		<#assign currTabContent >


			<div id="AvvioCentro-tab"  class="home-container">

    		<#assign parentEl=el />
    		<#assign FirmaContratto="false" />
    		<#assign dataArrPrimoPaz="false" />
			<#assign almenoUnPaziente="false" />
			<#assign almenoUnaSchedaMonClinico="false" />
			<#assign DatiAvvioCentroEDITABLE=true />

			<#assign dataPrimoArr="" />
    		<#-- CONTENUTO TAB MONITORAGGIO DISPONIBILE ALLA FIRMA DEL CONTRATTO-->
				<#-- 2019.06.20 vmazzeo: MODIFICATA visibilita' tab monitoraggio: è visibile se c'è almeno un parere favorevole -->
    		<#list parentEl.getChildrenByType("Contratto") as contr>
				<#list contr.getChildrenByType("ContrattoFirmaDG") as elFirmaDG>
    				<#if elFirmaDG.getfieldData("DatiContrattoFirmaDG", "dataFirma")[0]??>
	    				<#assign FirmaContratto="true"/>
    				</#if>
    			</#list>
  			</#list>
			<#if parentEl.getChildrenByType("MonitoraggioAmministrativo")?size gt 0>
				<#assign almenoUnPaziente="true" />

			</#if>
			<#if parentEl.getChildrenByType("MonitoraggioClinico")?size gt 0>
				<#assign almenoUnaSchedaMonClinico="true" />
			</#if>
			<#if parerePositivo=="true">
				<#list parentEl.getChildrenByType("AvvioCentro") as app>
					<#if !(app_has_next)>
						<div id="task-Actions-${app.id}" style="padding:10px 0px;float:right"></div>
						<@script>
						loadTasksById(${app.id});
						</@script>
						<#assign dataArrPrimoPaz="true" />
						<#assign dataPrimoArr=getFieldFormattedDate("DatiAvvioCentro","dataPrimoArr",app) />
						<#assign titolo> <@msg "template.DatiAvvioCentro"/> </#assign>
						<#assign forceReload="true" />
						<#assign DatiAvvioCentroEDITABLE=app.getUserPolicy(userDetails).canCreate />
						<@TemplateFormTable "DatiAvvioCentro" app userDetails DatiAvvioCentroEDITABLE titolo classes forceReload />
						<fieldset>
						<br/><br/>
						<!--inizio tabella nuova-->
						<div class="row">
							<div class="col-xs-12">
								<div class="table-responsive">
									<table id="sample-table-1" class="table table-striped table-bordered table-hover">
										<thead>
										<tr>
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

										<#list app.getChildrenByType("AllegatoAvvioCentro") as subEl>
											<#assign noDoc="" />
											<#assign tipologia="" />
											<#assign autore="" />
											<#assign version="" />
											<#assign fileName="" />
											<#assign uploadUser="" />
											<#assign uploadDt="" />
											<#assign data="" />
											<#if subEl.file?? && subEl.file.autore??>
												<#assign autore=subEl.file.autore />
											</#if>
											<#if subEl.file?? && subEl.file.version??>
												<#assign version=subEl.file.version />
											</#if>
											<#if subEl.file?? && subEl.file.fileName??>
												<#assign fileName=subEl.file.fileName />
											</#if>
											<#if subEl.file?? && subEl.file.uploadUser??>
												<#assign uploadUser=subEl.file.uploadUser />
											</#if>
											<#if subEl.file?? && subEl.file.uploadDt??>
												<#assign uploadDt=subEl.file.uploadDt.time?date?string.short />
											</#if>
											<#if subEl.file?? && subEl.file.date??>
												<#assign data=subEl.file.date.time?date?string.short />
											</#if>
											<tr>
												<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${fileName}</a></td>
												<td>${autore}</td>
												<td>${version}</td>
												<td>${data}</td>
												<td>${uploadUser}</td>
												<td>${uploadDt}</td>
												<td>
													<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
														<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
															<i class="icon-edit bigger-120"></i>
														</button>

													<#-- if subEl.getFieldDataString("AllegatoAvvioCentro","ProtocolloNumero")?string=="" >
														<!-- button title="Protocolla documento" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler protocollare il documento?')) {protocollaElement(${subEl.id},'${subEl.file.fileName}',${el.id},'${parentEl.getFieldDataString("IdCentro","ProtocolloFascicolo")?string}','AllegatoAvvioCentro',${parentEl.id})};return false;" href="#">
														<i class="icon-file bigger-120"></i>
														</button>
														<#else>
														<button title="Vedi documento protocollato" class="btn btn-xs btn-danger" onclick="vediProtocollo('${subEl.getFieldDataString("AllegatoAvvioCentro","ProtocolloNumero")?string}'); return false;" href="#">
														<i class="icon-file bigger-120"></i>
														</button -->
													</ #if -->

													<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD")>
														<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il documento?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
															<i class="icon-trash bigger-120"></i>
														</button>
													</#if>
													<#--TOSCANA-168 INIZIO -->
													<div style="clear:both"></div>
													<#if el.getFieldDataString("IdCentro","inviatoCE")?? && el.getFieldDataString("IdCentro","inviatoCE")=="1">
													<div id="task-Actions-${subEl.id}" style=""></div>
													<@script>
													loadTasksById(${subEl.id});
												</@script>
												<#else>
												<!--div id="nonInviatoCE" style=""> <button class="btn btn-primary btn-sm btn-spaced" onclick="alert('Centro non ancora inviato al CE');"> invia al CE</button> </div-->
											</#if>
											<#--TOSCANA-168 FINE -->
											</div>
											</td>
											</tr>
										</#list>
										${noDoc}
										</tbody>
									</table>
								</div>
							</div>
						</div>
						<!--fine tabella nuova-->
						<#list app.getType().getAllowedChilds() as subEl>
							<#if subEl.typeId=="AllegatoAvvioCentro" >
								<#assign allegatoAvvioPolicy=subEl.getUserPolicy(userDetails) />
								<#if allegatoAvvioPolicy.canCreate && DatiAvvioCentroEDITABLE >
									<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${app.id}/${subEl.typeId}';" value="Aggiungi documento">
								</#if>
							</#if>
						</#list>
						</fieldset>
					</#if>
				</#list>
			</#if>
			<#-- TOSCANA-190 Occorre fare in modo quindi che il monitoraggio si possa attivare per gli studi no profit anche in assenza di contratto firmato -->
			<#assign StudioNoProfit="false"/>
			<#assign Profit=getCode("datiStudio","Profit",el.parent) />
			<#if Profit=="2">
				<#assign StudioNoProfit="true"/>
			</#if>
  			<#if parerePositivo=="true" || StudioNoProfit =="true" >
				<#if model['getCreatableElementTypes']??>
					<#list model['getCreatableElementTypes'] as docType>
						<#if docType.typeId="AvvioCentro" && dataArrPrimoPaz=="false">
							<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Avvio studio nel centro">
						</#if>

					</#list>
				</#if>
	  		<#else>
	  			La funzione di avvio centro sar&agrave; disponibile dopo l'inserimento di un parere favorevole
 			</#if>
 				<!--
  			<#if FirmaContratto=="false">

  			</#if>
  			-->

			</div>
		</#assign>
		<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"AvvioCentro-tab2" }] />
		<#assign currTabContent >


			<div id="MonitoraggioClinico-tab"  class="home-container">
				<#if ( parerePositivo=="true" || StudioNoProfit =="true" ) && dataArrPrimoPaz=="true" >
					<#if model['getCreatableElementTypes']??>
						<#list model['getCreatableElementTypes'] as docType>
							<#if docType.typeId="MonitoraggioClinico" && dataArrPrimoPaz=="true">
								<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Inserisci nuova scheda di monitoraggio clinico">
							</#if>
						</#list>
					</#if>
				<#if dataArrPrimoPaz=="true">
					<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD") || userDetails.hasRole("REGIONE") || userDetails.hasRole("DIR") || userDetails.hasRole("SEGRETERIA")>
						<br><br>
						<div>
							<span class="home-table" >
								<table id="grid-monitoraggioclinico-table" class="grid-table" ></table>
									<div id="grid-monitoraggioclinico-pager"></div>
								</span>
						</div>
					<#else>
						Sezione non abilitata per il profilo attuale
					</#if>
				</#if>
				<#else>
				La funzione di monitoraggio sar&agrave; disponibile all'inserimento della data di arruolamento primo soggetto
				</#if>
			</div>
		</#assign>
		<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"MonitoraggioClinico-tab2" }] />
		<#assign currTabContent >


		<div id="MonitoraggioAmministrativo-tab"  class="home-container">
			<#if ( parerePositivo=="true" || StudioNoProfit =="true" ) && dataPrimoArr!="" >
				<#if model['getCreatableElementTypes']??>
					<#list model['getCreatableElementTypes'] as docType>
						<#if docType.typeId="MonitoraggioAmministrativo" && dataArrPrimoPaz=="true">
							<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="inserisci nuova scheda di monitoraggio amministrativo">
						</#if>
					</#list>
				</#if>
				<#if dataArrPrimoPaz=="true">
					<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD") || userDetails.hasRole("REGIONE") || userDetails.hasRole("DIR")>
						<br><br>
						<div>
								<span class="home-table" >
									<table id="home-grid-table" class="grid-table" ></table>
										<div id="home-grid-pager"></div>
									</span>
						</div>
					<#else>
						Sezione non abilitata per il profilo attuale
					</#if>
				</#if>
			<#else>
				La funzione di monitoraggio sar&agrave; disponibile all'inserimento della data di arruolamento primo soggetto
			</#if>
		</div>
		</#assign>
		<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"MonitoraggioAmministrativo-tab2" }] />

		<#assign currTabContent >


			<div id="ChiusuraCentro-tab"  class="home-container">
			<#assign DatiChiusuraCentroEDITABLE=true />
			<#if parerePositivo=="true"  >
				<#if parentEl.getChildrenByType("ChiusuraCentro")?size gt 0 >
					<#list parentEl.getChildrenByType("ChiusuraCentro") as app>
						<#if !(app_has_next)>
							<div id="task-Actions-${app.id}" style="padding:10px 0px;float:right"></div>
							<@script>
								loadTasksById(${app.id});
							</@script>
							<#assign titolo> <@msg "template.DatiChiusuraCentro"/> </#assign>
							<#assign forceReload="true" />
							<#assign DatiChiusuraCentroEDITABLE=app.getUserPolicy(userDetails).canCreate />
							<@TemplateFormTable "DatiChiusuraCentro" app userDetails DatiChiusuraCentroEDITABLE titolo classes forceReload />
							<fieldset>
								<br/><br/>
								<!--inizio tabella nuova-->
								<div class="row">
									<div class="col-xs-12">
										<div class="table-responsive">
											<table id="sample-table-1" class="table table-striped table-bordered table-hover">
												<thead>
												<tr>
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

												<#list app.getChildrenByType("allegatoChiusuraCentro") as subEl>
												<#assign noDoc="" />
												<#assign tipologia="" />
												<#assign autore="" />
												<#assign version="" />
												<#assign fileName="" />
												<#assign uploadUser="" />
												<#assign uploadDt="" />
												<#assign data="" />
												<#if subEl.file?? && subEl.file.autore??>
													<#assign autore=subEl.file.autore />
												</#if>
												<#if subEl.file?? && subEl.file.version??>
													<#assign version=subEl.file.version />
												</#if>
												<#if subEl.file?? && subEl.file.fileName??>
													<#assign fileName=subEl.file.fileName />
												</#if>
												<#if subEl.file?? && subEl.file.uploadUser??>
													<#assign uploadUser=subEl.file.uploadUser />
												</#if>
												<#if subEl.file?? && subEl.file.uploadDt??>
													<#assign uploadDt=subEl.file.uploadDt.time?date?string.short />
												</#if>
												<#if subEl.file?? && subEl.file.date??>
													<#assign data=subEl.file.date.time?date?string.short />
												</#if>
							<tr>
								<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${fileName}</a></td>
								<td>${autore}</td>
								<td>${version}</td>
								<td>${data}</td>
								<td>${uploadUser}</td>
								<td>${uploadDt}</td>
								<td>
									<div class="visible-md visible-lg hidden-sm hidden-xs btn-group">
										<button title="Visualizza dettaglio" class="btn btn-xs btn-info" onclick="location.href='${baseUrl}/app/documents/detail/${subEl.id}';">
											<i class="icon-edit bigger-120"></i>
										</button>
									<#-- if subEl.getFieldDataString("AllegatoChiusuraCentro","ProtocolloNumero")?string=="" >
										<!--button title="Protocolla documento" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler protocollare il documento?')) {protocollaElement(${subEl.id},'${subEl.file.fileName}',${el.id},'${parentEl.getFieldDataString("IdCentro","ProtocolloFascicolo")?string}','AllegatoChiusuraCentro',${parentEl.id})};return false;" href="#">
										<i class="icon-file bigger-120"></i>
										</button>
										<#else>
										<button title="Vedi documento protocollato" class="btn btn-xs btn-danger" onclick="vediProtocollo('${subEl.getFieldDataString("AllegatoChiusuraCentro","ProtocolloNumero")?string}'); return false;" href="#">
										<i class="icon-file bigger-120"></i>
										</button -->
									</ #if -->

									<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD")>
										<button title="Elimina" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler eliminare il documento?')) {deleteElement({id:${subEl.id}})};return false;" href="#">
											<i class="icon-trash bigger-120"></i>
										</button>
									</#if>
							</div>
							</td>
							</tr>
							</#list>
							${noDoc}
							</tbody>
							</table>
							</div>
							</div>
							</div>
							<!--fine tabella nuova-->
							<#list app.getType().getAllowedChilds() as subEl>

							<#if subEl.typeId=="allegatoChiusuraCentro" >
							<#assign allegatoAvvioPolicy=subEl.getUserPolicy(userDetails) />
							<#if allegatoAvvioPolicy.canCreate && DatiChiusuraCentroEDITABLE >
							<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${app.id}/${subEl.typeId}';" value="Aggiungi documento">
							</#if>
							</#if>
							</#list>
							</fieldset>
						</#if>
					</#list>
				<#else>
					La funzione di chiusura Centro sar&agrave; disponibile all'invio della scheda di avvio studio nel centro
				</#if>
			<#else>
				La funzione di chiusura Centro sar&agrave;  disponibile dopo l'inserimento di un parere favorevole
			</#if>
			</div>
		</#assign>
		<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"ChiusuraCentro-tab2" }] />
	    <#assign currTabContent >


			<div id="Safety-tab"  class="home-container">

    		<#--div class="tabbable" >
    		<ul class="nav nav-tabs" >
    		<li class="active"><a href="#sub-safety" data-toggle="tab">

														Eventi avversi
													</a></li>
    		<li>
    		<a href="#sub-dsur" data-toggle="tab">

														DSUR
													</a>
    		</li>
    		</ul>
    		<div class="tab-content"-->
    		<div id="sub-safety" class="tab-pane in active">
  			<#if parerePositivo=="true">


  					<#if model['getCreatableElementTypes']??>
  						<#list model['getCreatableElementTypes'] as docType>

    						<#if docType.typeId="Safety" && dataArrPrimoPaz=="true">
    					 		<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Registra nuovo evento avverso">
    					 	</#if>

    					 	<#if docType.typeId="AvvioCentro" && dataArrPrimoPaz=="false">
    					 		E' necessario avviare il monitoraggio prima di poter registrare eventi avversi.
    					 	</#if>

  						</#list>
  					</#if>
	  			<#if dataArrPrimoPaz=="true">

				<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI") || userDetails.hasRole("COORD")>
		  			<br><br>
		  			<div>
		  				<span class="home-table" >
							<table id="grid-safety" class="grid-table" ></table>
								<div id="grid-safety-pager"></div>
							</span>
						</div>
					<#else>
						Sezione non abilitata per il profilo attuale
					</#if>

	  			</#if>
	  		<#else>
	  			La funzione di safety sar&agrave; disponibile dopo l'inserimento di un parere favorevole
 			</#if>
 			</div>
 			<#--div id="sub-dsur" class="tab-pane">
 			<#if parerePositivo=="true">


  					<#if model['getCreatableElementTypes']??>
  						<#list model['getCreatableElementTypes'] as docType>

    						<#if docType.typeId="DSUR" && dataArrPrimoPaz=="true">
    					 		<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Carica nuovo DSUR">
    					 	</#if>

    					 	<#if docType.typeId="AvvioCentro" && dataArrPrimoPaz=="false">
    					 		E' necessario avviare il monitoraggio prima di poter registrare eventi avversi.
    					 	</#if>

  						</#list>
  					</#if>
	  			<#if dataArrPrimoPaz=="true">
	  			<br><br>
	  			<div>
	  				<span class="home-table" >
						<table id="grid-dsur" class="grid-table" ></table>
							<div id="grid-dsur-pager"></div>
						</span>
						</div>
	  			</#if>
	  		<#else>
	  			La funzione di safety sar&agrave; disponibile dopo l'inserimento di un parere favorevole
 			</#if>
 			</div>
 			</div>
 			</div-->
 				<!--
  			<#if FirmaContratto=="false">

  			</#if>
  			-->

			</div>
		</#assign>
		<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"Safety-tab2" }] />
	</#if>
	    <#assign currTabContent >

    <div id="Fatturazione-tab">
      <#assign parentEl=el/>
      <#assign existfatt=false/>
      	<table class="table table-striped table-bordered table-hover"><thead><tr><th>Tipologia</th> <th>Azioni</th></tr></thead>
  		<#list parentEl.getChildrenByType("Fatturazione") as subEl>
  			<#if (subEl.id)??><#assign existfatt=true/>	</#if>
  			<tr><td>
  				 <#if subEl.getFieldDataDecode("scheduling","ModalitaFatturazione")?? && subEl.getFieldDataDecode("scheduling","ModalitaFatturazione")!="">${subEl.getFieldDataDecode("scheduling","ModalitaFatturazione")!"Informazioni mancanti"} ( ${subEl.getFieldDataDecode("scheduling","Periodicita")!""} ${subEl.getFieldDataDecode("scheduling","TipologiaCalcolo")!""} )<#else>Informazioni mancanti</#if>
  				</td>
  				<td><button title="Visualizza dettaglio" class="btn btn-info btn-xs" style="margin-top:0px" onclick="window.location.href='${baseUrl}/app/documents/detail/${subEl.id}'" > <i class="icon icon-edit"></i></button></td>
  				</tr>
  		</#list>
  		</table>
  		<#if model['getCreatableElementTypes']??>
  			<#list model['getCreatableElementTypes'] as docType>
    			<#if docType.typeId="Fatturazione">

	    			<@script>

								    $('#creafatturazione').click(function(){

											var formData=new FormData();
											formData.append("parentId", "${el.id}");
											var actionUrl="${baseUrl}/app/rest/documents/save/${docType.id}";

											 $.ajax({
											            type: "POST",
											            url: actionUrl,
											            contentType:false,
											            processData:false,
											            async:false,
											            cache:false,
											            data: formData,
											            success: function(obj){
											                 if (obj.result=="OK") {
											                    window.location.href="${baseUrl}/app/documents/detail/"+obj.ret;
											                 }
											            }
											        });
											    });

						</@script>

	    	  	<!--input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Crea fatturazione"-->
	    	  	<#if !existfatt>
	    	  		<input type="button" class="submitButton round-button blue btn btn-info" id="creafatturazione" value="Attiva fatturazione">
	    	  	</#if>
    	  	</#if>
  			</#list>
  		</#if>
     </div>
        </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"Fatturazione-tab2" }] />

	<#-- /#if -->


</#if>
  </div>
  </div>

	</fieldset>

<@tabbedView tabs tabsContent "metadataTemplate-IdCentro2" />

</div>
	<#include "../helpers/centro-status-bar.ftl"/>

    </div>

<#else>

	<#--assign editable=false /-->
	<h1>Centro non visibile per l'utente/profilo corrente</h1>
<!--
userDetail.username ${userDetails.username}
userDetails.hasRole("tech-admin") ${userDetails.hasRole("tech-admin")?c}
userDetails.hasRole("REGIONE") ${userDetails.hasRole("REGIONE")?c}
el.getCreateUser() ${el.getCreateUser()}
userHasSite ${userHasSite?c}
userDetails.hasRole("PI") ${userDetails.hasRole("PI")?c}
userHasUO ${userHasUO?c}
userDetails.hasRole("COORD") ${userDetails.hasRole("COORD")?c}
userCF ${userCF}
piCF ${piCF}



-->

</#if>
