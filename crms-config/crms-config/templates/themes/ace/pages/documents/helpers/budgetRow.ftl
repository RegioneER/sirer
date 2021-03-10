<a href="${detailLink}">
	<#if element.type.titleField??>
        <b><@elementTitle element/></b></a> - <a href="${baseUrl}/app/documents/hardDelete/${element.id}">Elimina</a><br/>
    <#else>
    </a>
    </#if>
	