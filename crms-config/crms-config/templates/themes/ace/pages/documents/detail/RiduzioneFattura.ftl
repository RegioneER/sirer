<#include "../helpers/MetadataTemplate.ftl"/>
<#include "../../../macros.ftl"/>
<#assign type=model['docDefinition']/>
<#assign templates={}/>
<#if type.ftlFormTemplate??>
	<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>
<div class="mainContent">
    <h2>Riduzione Fattura</h2>
    <@TemplateForm "RiduzioneFattura" el userDetails true />
</div>


