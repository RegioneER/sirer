<script>
    $(document).ready(function(){
        type=new ajaXmrTab({
            elementName: "type",
            baseUrl: "${baseUrl}",
            listRow:typeListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/save",
            getAllUrl: "${baseUrl}/app/rest/admin/getTypes",
            deleteUrl: "${baseUrl}/",
            dialogWidth: "500px",
            editPage: "${baseUrl}/app/admin/editType"
        });
        type.refreshList();

        template=new ajaXmrTab({
            elementName: "template",
            baseUrl: "${baseUrl}",
            listRow:templateListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/template/save",
            getAllUrl: "${baseUrl}/app/rest/admin/getTemplates",
            deleteUrl: "${baseUrl}/",
            dialogWidth: "500px",
            editPage: "${baseUrl}/app/admin/editTemplate"
        });
        template.refreshList();

        policy=new ajaXmrTab({
            elementName: "policy",
            baseUrl: "${baseUrl}",
            listRow:policyListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/policy/save",
            getAllUrl: "${baseUrl}/app/rest/admin/getPolicies",
            deleteUrl: "${baseUrl}/app/rest/admin/policy/delete",
            getSingleElementUrl: "${baseUrl}/app/rest/admin/getPolicy",
            dialogWidth: "500px",
            postPopulateFunction: policyPostPopulate
        });
        policy.refreshList();

        $('#tabs').tabs();
    });


    function typeListRow(jsonRow){
        return '<a href="${baseUrl}/app/admin/editType/'+jsonRow.id+'"><img src="'+jsonRow.imageBase64+'" width="48px"><br>'+jsonRow.typeId+'</a>';
    }

    function templateListRow(jsonRow){
        return '<a href="${baseUrl}/app/admin/editTemplate/'+jsonRow.id+'"><img src="${baseUrl}/int/images/metadata.png">'+jsonRow.name+'</a>';
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
    }

    function policyListRow(jsonRow){
        ret="<tr>";
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
        ret+='<td>';
        ret+='<a href="#" class="ui-icon ui-icon-pencil policy-edit" style="display: inline-block" title="modifica">'+jsonRow.id+'</a>';
        ret+='&nbsp;&nbsp;';
        ret+='<a href="#" class="ui-icon ui-icon-trash policy-delete" style="display: inline-block" title="elimina">'+jsonRow.id+'</a>';
        ret+='</td>';
        ret+="</tr>";
        return ret;
        //return '<a href="${baseUrl}/app/admin/editPolicy/'+jsonRow.id+'"><img src="${baseUrl}/int/images/policy_icon.png">'+jsonRow.name+'</a>';
    }
</script>
<div class="left-menu-2">
    <input class="fixedButton submitButton round-button blue" type="button" value="Nuova tipologia" id="add-type" name="add-type"/>
    <br/>
    <input class="fixedButton submitButton round-button blue" type="button" value="Nuovo template metadati" id="add-template" name="add-template"/>
    <br/>
    <input class="fixedButton submitButton round-button blue" type="button" value="Nuova policy" id="add-policy" name="add-policy"/>
</div>
<div id="template-dialog" title="Aggiungi template">
    <fieldset>
        <form id="template-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <@textbox "name" "name" "Nome" "" 40/>
            <br/>
        <@textarea "description" "description" "Descrizione" 40 3 />
            <br/>
            <input class="round-button blue" type="button" value="Salva" id="template-form-submit"/>
        </form>

    </fieldset>
</div>

<div id="type-dialog" title="Aggiungi tipologia">
    <fieldset>
        <form id="type-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <@textbox "typeId" "typeId" "Nome tipologia" "" 40/>
            <br/>
        <@checkBox "selfRecursive" "selfRecursive" "Può contenere elementi dello stesso tipo" {"1":""} />
            <br/>
            <br/>
            <br/>
        <@checkBox "container" "container" "Può contenere altri elementi" {"1":""} />
            <br/>
            <br/>
        <@checkBox "hasFile" "hasFile" "Prevede file allegato" {"1":""} />
            <br/>
            <br/>
        <@fileChooser "img" "img" "Icona"/>
            <br/><br/>
            <br/>
            <input class="round-button blue" type="button" value="Salva" id="type-form-submit"/>
        </form>
    </fieldset>
</div>

<div id="policy-dialog" title="Aggiungi policy">
    <fieldset>
        <form id="policy-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <@hidden "id" "id" ""/>
        <@textbox "name" "name" "Nome" "" 40/>
            <br/>
        <@textbox "description" "description" "Descrizione" "" 40/>
            <br/>
        <@checkBox "view" "view" "Visualizzazione" {"1":""} />
            <br/>
            <br/>
        <@checkBox "create" "create" "Creazione" {"1":""} />
            <br/>
            <br/>
        <@checkBox "update" "update" "Modifica metadati e file allegati" {"1":""} />
            <br/>
            <br/><br/>
        <@checkBox "addComment" "addComment" "Aggiunta Commento" {"1":""} />
            <br/>
            <br/>
        <@checkBox "moderate" "moderate" "Moderazione Commenti" {"1":""} />
            <br/>
            <br/>
        <@checkBox "delete" "delete" "Eliminazione" {"1":""} />
            <br/>
            <br/>
        <@checkBox "changePermission" "changePermission" "Modifica Permessi" {"1":""} />
            <br/>
            <br/>
        <@checkBox "addChild" "addChild" "Aggiunta elementi innestati" {"1":""} />
            <br/>
            <br/>  <br/>
        <@checkBox "removeCheckOut" "removeCheckOut" "Rimozione Check-Out" {"1":""} />
            <br/>
            <br/>
        <input class="round-button blue" type="button" value="Salva" id="policy-form-submit"/>
        </form>
    </fieldset>
</div>