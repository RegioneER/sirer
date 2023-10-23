<#assign icon=elType.getImageBase64()/>
<#if icon=="">
    <#assign icon=baseUrl+"/int/images/document_blank.png"/>
</#if>
<span class="info-detail">
    Creato <b>${el.creationDt.time?datetime?string.full}</b> da <b>${el.createUser}</b>
    <#if el.lastUpdateUser??>
        <br/>Ultima modifica di <b>${el.lastUpdateDt.time?datetime?string.short}</b> da <b>${el.lastUpdateUser}</b>
    </#if>
</span>
<h1 class="element-title"><@breadCrumb el/><img width="20px" src="${icon}"/>
<#if el.type.titleField??>
    <b><@elementTitle el/>
</#if>
</h1>
