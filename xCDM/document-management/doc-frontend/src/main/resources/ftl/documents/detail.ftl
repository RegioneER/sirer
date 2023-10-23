<div class="mainContent">
<fieldset>
    <legend>${model['docDefinition'].typeId}: <@printMetadata "base.name" model['element']/></legend>
<#if model['docDefinition'].enabledTemplates?? && model['docDefinition'].enabledTemplates?size gt 0>
    <#list model['docDefinition'].enabledTemplates as template>
        <#if template.fields??>
            <#list template.fields as field>
                <#assign vals=[]/>
                <#list model['element'].data as data>
                    <#if data.template.id=template.id && data.field.id=field.id >
                        <#assign vals=data.getVals()/>
                    </#if>
                </#list>
                <@mdFieldDetail template field vals/><br/>
            </#list>
        </#if>
    </#list>
</#if>
<#if model['docDefinition'].hasFileAttached>
  <#if model['element'].file??>
    <b>File: ${model['element'].file.fileName} (${model['element'].file.size})</b>
  </#if>
</#if>
    <br/>
    <br/>
    <#assign policy=model['element'].getUserPolicy(userDetails)/>
    <table class="pSchema">
        <tr>
            <th></th>
            <#include "../admin/helpers/permission-tb-header.ftl"/>
            </th>
        </tr>
        <tr>
            <td></td>
            <td><#if policy.canView>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canCreate>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canUpdate>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canAddComment>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canModerate>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canDelete>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canChangePermission>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canAddChild>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canRemoveCheckOut>&#10004;<#else>&nbsp;</#if></td>
            <td></td>

        </tr>
    </table>
</fieldset>
</div>