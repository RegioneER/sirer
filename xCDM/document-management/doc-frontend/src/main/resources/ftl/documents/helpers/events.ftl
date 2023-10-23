<#if model['events']??>
<#assign evs=model['events']/>
<fieldset>
    <legend>Ultime azioni</legend>
    <#list evs as ev>
        <li>${ev.evDt.time?datetime?string.short} - ${ev.evType} - ${ev.username}<#if allElements?? && allElements>
         - <a href="${baseUrl}/app/documents/detail/${ev.element.id}">elemento</a>
        </#if></li>
    </#list>
</fieldset>
</#if>