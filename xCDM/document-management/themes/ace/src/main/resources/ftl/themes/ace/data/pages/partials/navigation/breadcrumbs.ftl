<#assign icon=elType.getImageBase64()/>
<#if icon=="">
    <#assign icon=baseUrl+"/int/images/document_blank.png"/>
</#if>
<!--span class="info-detail">
    Creato <b>${el.creationDt.time?datetime?string.full}</b> da <b>${el.createUser}</b>
    <#if el.lastUpdateUser??>
        <br/>Ultima modifica di <b>${el.lastUpdateDt.time?datetime?string.short}</b> da <b>${el.lastUpdateUser}</b>
    </#if>
</span-->
<@breadcrumbsData el/><img width="20px" src="${icon}"/>
<#if el.type.titleField?? || el.type.titleRegex??>
    <b><@elementTitle el/><#if (el.getfieldData("Budget","Versione")?size>0) >
    	 ( v. ${el.getfieldData("Budget","Versione")[0]} )
    	</#if>
</#if>
</h1>
