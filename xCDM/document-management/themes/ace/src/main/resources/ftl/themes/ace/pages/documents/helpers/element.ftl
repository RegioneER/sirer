<#assign detailLink=baseUrl+"/app/documents/detail/"+element.id/>
<#assign typeIconSrc=element.type.imageBase64!/>
<#if typeIconSrc=="">
    <#assign typeIconSrc=baseUrl+"/int/images/document_blank.png"/>
</#if>
<tr>
		<td>
			<a href="${detailLink}">
	    		<img width="30px" src="${typeIconSrc}"/>
			</a>
		</td>
	
<#if element.type.ftlRowTemplate?? && element.type.ftlRowTemplate!="">
	<#include element.type.ftlRowTemplate+".ftl"/>
     <#else>
   	<td>
   	<#include "stdElementRow.ftl"/>
   	</td>
</#if>
<td>
	${element.creationDt.time?datetime?string.short}
</td>
<td>
<#if element.lastUpdateDt??>
	${element.lastUpdateDt.time?datetime?string.short}
	<#else>&nbsp;
	</#if>
</td>
</tr>