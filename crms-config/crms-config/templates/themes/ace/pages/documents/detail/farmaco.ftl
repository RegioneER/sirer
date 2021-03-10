<#include "../helpers/macroGemelli.ftl"/>
<#include "../helpers/MetadataTemplate.ftl"/>


<#assign tabOrder=['datiStudio','datiPromotore', 'datiCRO','DSUR']/>

<#assign counter=0 />
<div id="metadataTemplate-tabs" class="tabbable" >
	<ul  class="nav nav-tabs" >
		<#list tabOrder as templateName>
		<#if viewableTemplate(templateName, el, userDetails)>
		<#assign counter=counter+1 />
		<li <#if counter=1 >class="active"</#if>><a href="#metadataTemplate-${templateName}"  data-toggle="tab" ><@msg "template.${templateName}"/></a></li>
</#if>
</#list>
<li><a href="#centri-tab" data-toggle="tab" >Dati farmaco</a></li>
<!--li><a href="#farmaci-tab" data-toggle="tab" >Magazzino</a></li-->
<!--li><a href="#dsur-tab" data-toggle="tab" >Safety</a></li>
<li><a href="#emendamenti-tab" data-toggle="tab">Emendamenti</a></li>
<li><a href="#allegato-tab" data-toggle="tab" ><@msg "type.allegato"/></a></li-->
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


<div id="centri-tab" class="tab-pane">
	<#list el.templates as template>
	<#if template.name!="IDstudio" &&  template.name!="UniqueIdStudio">
	<#if template.name="datiPromotore" || template.name="datiCRO">
	<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	<#list el.elementTemplates as elementTemplate>
	<#if elementTemplate.metadataTemplate.name=template.name && elementTemplate.enabled>

	<div id="metadataTemplate-${template.name}" class="allInTemplate tab-pane">
		<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
		<#assign formEdit=false>
		<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
		<#assign formEdit=true>
		<form name="${template.name}" class="form-horizontal" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
		</#if>

		<#assign idSp=el.getfieldData("datiPromotore","promotore") />
		<#if idSp[0]?? && idSp[0]?size gt 0>
		<input type="hidden" id="datiPromotore_promotore" disabled="disabled" name="parent_promo" value="${idSp[0].id}">
	</#if>

	<#assign idCro=el.getfieldData("datiCRO","denominazione") />
	<#if idCro[0]?? && idCro[0]?size gt 0>
	<input type="hidden" id="datiCRO_denominazione" disabled="disabled" name="parent_cro" value="${idCro[0].id}">
</#if>

<#list template.fields as field>
<#assign isEditable=editable>

<#if field.name="promotore" || field.name="denominazione">
<#assign isEditable=chiuso>
</#if>

<#if field.name="cpLink" || field.name="cpfLink" || field.name="cprLink" || field.name="cpocLink" || field.name="cplLink">
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
	<legend style="width: 200px; font-size: 17px;">Regolatorio</legend>

</#if>
<#if field.name="RefNomeCognomeOC" || field.name="NomeReferenteOC">
</fieldset>
<br/>
<fieldset class="cpoc">
	<legend style="width: 200px; font-size: 17px;">Operazioni Cliniche</legend>

</#if>
<#if field.name="RefNomeCognomeL" || field.name="NomeReferenteL">
</fieldset>
<br/>
<fieldset class="cpl">
	<legend style="width: 200px; font-size: 17px;">Legale</legend>

</#if>
<@SingleField template.name field.name el userDetails isEditable/>
<#if field.name="cpLink" || field.name="cpfLink" || field.name="cprLink" || field.name="cpocLink" || field.name="cplLink">

</#if>
</#list>
</fieldset>

<div class="clearfix"> </div>

<#if formEdit>
<button class="submitButton round-button blue templateForm btn btn-warning" id="salvaForm-${template.name}" ><i class="icon-save bigger-160" id="salvaForm-${template.name}" name="salvaForm-${template.name}" ></i><b>Salva</b></span>
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
<#-- TOSCANA-189 riscrivo io la form di edit del farmaco per gestire la validazione al salvataggio -->
<#assign groupActive=false />
<#list el.elementTemplates as elementTemplate>
<#if elementTemplate.metadataTemplate.name==template.name && elementTemplate.enabled>
<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
<#if templatePolicy.canView>

<#assign template=elementTemplate.metadataTemplate/>
<#assign toClose=true />
<div id="metadataTemplate-${template.name}" class="${classes}">
	<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
	<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
	</#if>
	<table class="table table-bordered" id="checklist">
		<thead>
		<tr><th colspan="2">Dati generali farmaco</th></tr>
		</thead>
		<#list template.fields as field>
		<@SingleFieldTd template.name field.name el userDetails editable />
	</#list>
	</table>

</#if>

</#if>
</#list>


<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
<div class="clearfix"></div>
<button id="salvaForm-${template.name}" class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span>
</button>
</form>
</#if>
</#if>
</#if>
</#list>
<#-- assign legendaFarmaco=true>
<#include "../helpers/legenda.ftl" /-->
<#include "../helpers/sfogliaFarmaciDialog.ftl"/>
</div>


<div id="farmaci-tab" class="tab-pane">
	<#if model['getCreatableElementTypes']??>
	<#list model['getCreatableElementTypes'] as docType>
	<#if docType.typeId="MovimentazioneFarmaco" >
	<button class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi movimentazione per un centro</b></button>
</#if>
</#list>
</#if>
<br/>	<br/>



