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
	}
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





  <div class="row">
   		<div class="col-xs-9">
<#include "../helpers/MetadataTemplate.ftl"/>
<#assign tabs=[] />
<#assign tabsContent=[] />

<#assign tabsGroups={"metadataTemplate-Progetto2":"metadataTemplate-Progetto2", "UOPartecipante2":"metadataTemplate-Progetto2"} />
			
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
	<#assign tabOrder=['template.Progetto', 'type.UOPartecipante']/>
</#if>
<div id="metadataTemplate-tabs">
	<#list tabOrder as itm>
		<!-- CERCO OGGETTO: ${itm} -->
		<#assign found=false />
		<#list el.templates as template>
			<!-- CICLO TEMPLATE: ${template.name} -->
			<#if itm="template."+template.name>
				<!-- TROVO TEMPLATE: ${template.name} -->
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
				<#--@msg "type."+itm?split(".")[1]/-->
				<#assign splitted = itm?split(".")[1] />
				<!-- SPLITTED: ${splitted} -->
				<@msg itm />
				</#assign>
				<#assign tabs=tabs+[{"target": splitted+"-tab"+"2","label":tabLabel,"class":"filtered-tab "+tabsGroups[splitted+"2"]}] />
				<!--li><a href="#${splitted}-tab"><@msg itm/></a></li-->
		</#if>
		
		<!-- stampo i type disabled -->
		<#if itm?starts_with("disabledType.")>
				<#assign found=true />		
				<#assign tabLabel>
				<@msg "type."+itm?split(".")[1]/>
				</#assign>
				
				<#assign tabs=tabs+[{"target": itm?split(".")[1]+"-tab"+"2","label":tabLabel,"disabled":true,"class":"filtered-tab "+tabsGroups[itm?split(".")[1]+"-tab"+"2"]}] />
					<#assign tabsContent=tabsContent+[{"content":"Area non attiva in attesa di completamento della valutazione da parte del CTO / TFA","id":itm?split(".")[1]+"-tab"+"2" }] />
				<!--li><a href="#${itm?split(".")[1]}-tab"><@msg "type."+itm?split(".")[1]/></a></li-->
		</#if>
		
		<!-- stampo i template disabled -->
		<#if ((itm?starts_with("disabledTemplate.") || !found ) && (tabsGroups[itm?split(".")[1]+"-tab"+"2"]??))>
		
				<#assign tabLabel>
				<@msg "template."+itm?split(".")[1]/>
				</#assign>
				<#assign tabs=tabs+[{"target": itm?split(".")[1]+"-tab"+"2","label":tabLabel,"disabled":true,"class":"filtered-tab "+tabsGroups[itm?split(".")[1]+"-tab"+"2"]}] />
					<#if itm?starts_with("disabledTemplate.")>
						<#assign tabsContent=tabsContent+[{"content":"Area non attiva in attesa di completamento della valutazione da parte del CTO / TFA","id": itm?split(".")[1]+"-tab"+"2"}] />
					<#else>
						<#assign tabsContent=tabsContent+[{"content":"Area non attiva ","id": itm?split(".")[1]+"-tab"+"2"}] />
					</#if>
				<!--li><a href="#${itm?split(".")[1]}-tab"><@msg "type."+itm?split(".")[1]/></a></li-->
		</#if>
		
	</#list>

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


<#list el.templates as template>	<!-- ${template.name} IdCentro DatiCentro Feasibility QUA-->


				<#assign currTabContent>

			<div class="emendamento-template">
				<#-- @TemplateForm template.name el userDetails editable/ -->
					<#assign titolo> <@msg "template.${template.name}"/> </#assign>
				<@TemplateFormTable template.name el userDetails editable titolo classes />
			</div>
				</#assign>

<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"metadataTemplate-"+template.name+"2" }] />

</#list>










 








<#assign currTabContent >

<div id="UOPartecipante-tab">
		<fieldset>
			<!--legend>File allegati</legend-->
    	<#assign parentEl=el/>
		

		<#if model['getCreatableElementTypes']??>
			<#list model['getCreatableElementTypes'] as docType>
				<#if docType.typeId="UOPartecipante">
				<input type="button" class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Aggiungi UO">
			</#if>
			</#list>
		</#if>

		
    	<br/><br/>
    	
        <div id="dialog" style="display:none;" title="UO Partecipante"></div>
        <br/><br/>

        <!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-responsive">
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<th class="hidden-480" >Struttura</th>
									<th class="hidden-480" >Dipartimento</th>
									<th class="hidden-480" >UO</th>
									<th class="hidden-480" >Responsabile scientifico UO</th>
									<th class="hidden-480" >Azioni</th>
 								</tr>
							</thead>

							<tbody>

							<#assign noDoc>
								<tr>
	            		<td colspan=8><span class="help-button">?</span> Nessun documento inserito </td>
	           		</tr>
           		</#assign>

    					<#list parentEl.getChildrenByType("UOPartecipante") as subEl>
	    						<#assign noDoc="" />
								<#assign tipologia="" />
								<#assign autore="" />
								<#assign version="" />
								<#assign fileName="" />
								<#assign uploadUser="" />
								<#assign uploadDt="" />
								<#assign data="" />
								<#if subEl.getfieldData("UOPartecipante","TipoDocumento")[0]??>
									<#assign tipologia=subEl.getFieldDataDecode("UOPartecipante","TipoDocumento") />
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

								<tr>
									<td>${subEl.getFieldDataDecode("UOPartecipante","Struttura")}</td>
									<td>${subEl.getFieldDataDecode("UOPartecipante","Dipartimento")}</td>
									<td>${subEl.getFieldDataDecode("UOPartecipante","UO")}</td>
									<td>${subEl.getFieldDataDecode("UOPartecipante","PINomeCognome")}</td>
									<td>
										<button title="Visualizza dettaglio" class="btn btn-info btn-xs" style="margin-top:0px" onclick="window.location.href='${baseUrl}/app/documents/detail/${subEl.id}'" > <i class="icon icon-edit"></i></button>
										<#if subEl.getFieldDataCode("UOPartecipante","DocCompleta")!="">
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
<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"UOPartecipante-tab2" }] />
	



	
	
	
	    

  </div>
  </div>

	</fieldset>

<@tabbedView tabs tabsContent "metadataTemplate-IdCentro2" />

</div>
	<#--include "../helpers/centro-status-bar.ftl"/-->
    
</div>