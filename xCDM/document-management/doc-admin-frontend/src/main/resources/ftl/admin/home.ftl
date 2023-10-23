<script>
    $(document).ready(function(){
        type=new ajaXmrTab({
            elementName: "type",
            baseUrl: "${baseUrl}",
            listRow:typeListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/save",
            getAllUrl: "${baseUrl}/app/rest/admin/type/getAll",
            deleteUrl: "${baseUrl}/app/rest/admin/type/delete",
            dialogWidth: "500px",
            editPage: "${baseUrl}/app/admin/editType",
            listType:"li"
        });
        type.refreshList();

        template=new ajaXmrTab({
            elementName: "template",
            baseUrl: "${baseUrl}",
            listRow:templateListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/template/save",
            getAllUrl: "${baseUrl}/app/rest/admin/template/getAll",
            deleteUrl: "${baseUrl}/app/rest/admin/template/delete/{id}",
            dialogWidth: "500px",
            editPage: "${baseUrl}/app/admin/editTemplate",
            listType:"li"
        });
        template.refreshList();

        policy=new ajaXmrTab({
            elementName: "policy",
            baseUrl: "${baseUrl}",
            listRow:policyListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/policy/save",
            getAllUrl: "${baseUrl}/app/rest/admin/policy/getAll",
            deleteUrl: "${baseUrl}/app/rest/admin/policy/delete",
            getSingleElementUrl: "${baseUrl}/app/rest/admin/policy/get",
            dialogWidth: "500px",
            postPopulateFunction: policyPostPopulate,
            listType:"tr"
        });
        policy.refreshList();

        $('#tabs').tabs();
    });

    function typeListRow(jsonRow){
        var img;
        console.log(jsonRow);
        if (jsonRow.imageBase64=='') img='<img height="60px" src="${baseUrl}/int/images/document_blank.png">';
        else img='<img height="60px" src="'+jsonRow.imageBase64+'">'
        return '<a href="${baseUrl}/app/admin/editType/'+jsonRow.id+'">'+img+'<br/>'+jsonRow.typeId+'</a>';
    }

    function templateListRow(jsonRow){
        return '<a href="${baseUrl}/app/admin/editTemplate/'+jsonRow.id+'"><img height="60px" src="${baseUrl}/int/images/metadata.png"><br/>'+jsonRow.name+'</a>';
    }

    function policyPostPopulate(jsonRow){
        $('#view')[0].checked=jsonRow.policy.canView;
        $('#create')[0].checked=jsonRow.policy.canCreate;
        $('#update')[0].checked=jsonRow.policy.canUpdate;
        $('#addComment')[0].checked=jsonRow.policy.canAddComment;
        $('#moderate')[0].checked=jsonRow.policy.canModerate;
        $('#delete')[0].checked=jsonRow.policy.canDelete;
        $('#changePermission')[0].checked=jsonRow.policy.canChangePermission;
        $('#addChild')[0].checked=jsonRow.policy.canAddChild;
        $('#removeCheckOut')[0].checked=jsonRow.policy.canRemoveCheckOut;
        $('#launchProcess')[0].checked=jsonRow.policy.canLaunchProcess;
        $('#enableTemplate')[0].checked=jsonRow.policy.canEnableTemplate;
        $('#canBrowse')[0].checked=jsonRow.policy.canBrowse;
    }

    function policyListRow(jsonRow){
        ret="";
        ret+="<td>"+jsonRow.name+"</td>";
        if (jsonRow.policy.canView) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canCreate) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canUpdate) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canAddComment) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canModerate) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canDelete) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canChangePermission) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canAddChild) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canRemoveCheckOut) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canLaunchProcess) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canEnableTemplate) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canBrowse) ret+="<td>&#10004;</td>";
        else ret+="<td>&nbsp;</td>";
        return ret;
    }
</script>
<div class="admin-home-main">
    <input class="submitButton round-button blue" type="button" value="Aggiungi una tipologia" id="add-type" name="add-type"/>
    <input class="submitButton round-button blue" type="button" value="Aggiungi un template metadati" id="add-template" name="add-template"/>
    <input class="submitButton round-button blue" type="button" value="Aggiungi una policy" id="add-policy" name="add-policy"/>
    <input class="round-button blue" type="button" value="Gestisci processi" onclick="window.location.href='${baseUrl}/pconsole/#processmodel';"/>
    <input class="round-button blue" type="button" value="Gestisci utenti" onclick="window.location.href='${baseUrl}/pconsole/#user';"/>
    <input class="round-button blue" type="button" value="Gestisci gruppi" onclick="window.location.href='${baseUrl}/pconsole/#group';"/>
    <input class="round-button blue" type="button" value="Gestisci localizzazione" onclick="window.location.href='${baseUrl}/app/admin/messages/it_IT';"/>
    <br/>
    <br/>
    <fieldset id="tabs-1">
            <legend>Tipologie di elementi</legend>
        <div class="grid">
                <ul id="type-list-availables"></ul>
            </div>

    </fieldset>
    <br/>
    <fieldset id="tabs-2">
            <legend>Template metadati</legend>
        <div class="grid">
                    <ul id="template-list-availables"></ul>
                </div>
        <br/>
        </fieldset>
    <br/>
    <div>

    <fieldset id="tabs-3">
        <fieldset style="display:inline-block;float:right">
        <#include "helpers/permission-legend.ftl"/>
        </fieldset>
            <legend>Policy predefinite</legend>
            <table class="pSchema">
                <thead>
                <tr>
                    <th>Policy</th>
                    <#include "helpers/permission-tb-header.ftl"/>
                    <th>Action</th>
                </tr>
                </thead>
                <tbody id="policy-list-availables"></tbody>
                </table>
    </fieldset>

        

    </div>
    </div>
<#include "typeForms/element.ftl"/>
<#include "typeForms/metadata.ftl"/>
<#include "typeForms/policy.ftl"/>