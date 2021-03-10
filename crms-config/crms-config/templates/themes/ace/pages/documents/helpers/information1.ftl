
<#assign editable=false/>
<#if userPolicy.canUpdate && !el.locked>
    <#assign editable=true/>
</#if>
<#if userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username>
    <#assign editable=true/>
</#if>

<#include "MetadataTemplate.ftl"/>

<#if infoPanel=="main">
<fieldset id="child-box" class="child-box">
<#else>
<fieldset>
</#if>
    <legend>Informazioni<#if el.locked><img src="${baseUrl}/int/images/lock.png" width="36px"/></#if></legend>
    <@TemplateForm "test1" el userDetails editable/>
    <@TemplateForm "info" el userDetails editable/>
</fieldset>
<div class="info" style="display:none">Info message</div>

<div class="success" style="display:none">Successful operation message</div>

<div class="warning" style="display:none">Warning message</div>

<div class="error" style="display:none">Error message</div>