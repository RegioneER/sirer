<#include "../helpers/MetadataTemplate.ftl"/>
<#assign editable=false/>
<#if userPolicy.canUpdate && !el.locked>
    <#assign editable=true/>
</#if>
<#if userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username>
    <#assign editable=true/>
</#if>


<#assign label="type."+elType.getTypeId() />
    <legend><@msg label /></legend>
<div class="form-horizontal" >	
<#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
    <#list el.templates as template>
        <@TemplateForm template.name el userDetails false />
    </#list>
</#if>
</div>
<br>
