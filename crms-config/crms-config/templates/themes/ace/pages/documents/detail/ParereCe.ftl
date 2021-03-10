<#include "../helpers/MetadataTemplate.ftl"/>
<#include "../../../macros.ftl"/>

<#assign type=model['docDefinition']/>
<#assign templates={}/>
<#if type.ftlFormTemplate??>
	<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>
<div class="mainContent">

    <#if el.getFieldDataCode("ParereCe","esitoParere")!="">
        <div id="task-Actions"></div>
    </#if>
<div class="row">
	<div class="col-sm-8">
	<h2>Parere CE</h2>
    <@TemplateForm "ParereCe" el userDetails true />
	</div>
	<div class="col-sm-4">
<#include "../helpers/attached-file.ftl"/>
	
	</div>
	
</div>
    
	
	
</div>


