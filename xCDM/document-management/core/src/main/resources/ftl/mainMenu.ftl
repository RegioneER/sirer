<!--
<div class="mainMenu">

    <form class="form-wrapper cf" action="${baseUrl}/app/documents/search" method="GET">
        <input type="text" name="pattern" placeholder="Search here..." required>
        <button type="submit">Search</button>
    </form>

    <ul>
        <li class="<#if !model['typeId']?? && model['area']?? && model['area']=="documents">selected </#if>mainMenu_1_item"><a href="${baseUrl}/app/documents"><@msg "system.home"/></a></li>
    <#if model['rootBrowse']??>
    <#list model['rootBrowse'] as elType>
    	<li class="mainMenu_1_item<#if model['typeId']?? && model['typeId']==elType.id> selected</#if>"><a href="${baseUrl}/app/documents/${elType.id}"><@msg "type."+elType.typeId/></a></li>
    </#list>
    </#if>
        <li class="<#if model['area']?? && model['area']=="calendar">selected </#if>mainMenu_1_item"><a href="${baseUrl}/app/calendar"><@msg "system.calendar"/></a></li>
    
    </ul>
</div>
-->