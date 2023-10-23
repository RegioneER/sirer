<#include "../helpers/MetadataTemplate.ftl"/>
<#include "../../../macros.ftl"/>
<#assign type=model['docDefinition']/>
<#assign templates={}/>
<#if type.ftlFormTemplate??>
	<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>
<div class="mainContent">

    <#if el.getFieldDataCode("IstruttoriaCE","DocCompleta")!="">
        <div id="task-Actions"></div>
    </#if>

    <h2>Istruttoria CE</h2>
    <@TemplateForm "IstruttoriaCE" el userDetails true />
</div>


