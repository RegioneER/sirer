<#include "../helpers/MetadataTemplate.ftl"/>
<#include "../../../macros.ftl"/>
<#assign type=model['docDefinition']/>
<#assign templates={}/>
<#if type.ftlFormTemplate??>
	<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>
<div class="mainContent">
    <h2>Team di studio</h2>
    <@TemplateForm "DatiTeamDiStudio" el userDetails true />
</div>


