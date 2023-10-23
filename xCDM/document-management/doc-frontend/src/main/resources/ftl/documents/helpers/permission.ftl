<script>

$(document).ready(function(){
	 permission=new ajaXmrTab({
                    elementName: "permission",
                    baseUrl: "${baseUrl}",
                    listRow:permissionListRow,
                    saveOrUpdateUrl: "${baseUrl}/app/rest/documents/${el.id}/acl/save",
                    getAllUrl: "${baseUrl}/app/rest/documents/${el.id}/acl/getAll",
                    getSingleElementUrl: "${baseUrl}/app/rest/documents/${el.id}/acl/get",
                    deleteUrl: "${baseUrl}/app/rest/documents/${el.id}/acl/delete",
                    dialogWidth: "800px",
                    postSave: postPermissionSave,
                    postRefresh: postPermissionRefresh,
                    listType: "tr",
                    postPopulateFunction: postPermissionPopulate
                });
                permission.refreshList();
});

 var selectedPolicies=new Array();


function permissionListRow(jsonRow){
        ret="";
        if (jsonRow.predPolicy!=null) {
            selectedPolicies[jsonRow.id]=true;
            ret+="<td>"+jsonRow.predPolicy.name+"</td>";
        }
        else ret+="<td>&nbsp;</td>";
        if (jsonRow.policy.canView) ret+="<td>&#10004;</td>";
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
        ret+="<td>";
        if (jsonRow.containers!=null){
            for (c=0;c<jsonRow.containers.length;c++){
                if (c>0)ret+=", ";
                if (jsonRow.containers[c].authority) ret+="g:";
                else ret+="u:";
                ret+=jsonRow.containers[c].container;
            }
        }
        ret+="</td>";
        return ret;
    }

 function postPermissionPopulate(jsonRow){
 console.log("sono qui");
        dataPerm=jsonRow;
        if (jsonRow.predPolicy!=null) {
            $('#permission-form #policy').val(jsonRow.predPolicy.id);
            $('#permission-table').hide();
        }
        else {
            $('#permission-form #policy').val(0);
            $('#permission-table').show();
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

        for (c=0;c<jsonRow.containers.length;c++){
            console.log(jsonRow.containers[c]);
            if (jsonRow.containers[c].authority){
                if (jsonRow.containers[c].container=='cgroup')  $('#permission-form #cgroup')[0].checked=true;
                else $('#permission-form #groups').tokenInput("add", {id: jsonRow.containers[c].container, name: jsonRow.containers[c].container});
            }else {
                if (jsonRow.containers[c].container=='cuser')  $('#cuser')[0].checked=true;
                else $('#permission-form #users').tokenInput("add", {id: jsonRow.containers[c].container, name: jsonRow.containers[c].container});
            }
        }
    }


function postPermissionRefresh(){
        //$('#permission-form #policy option').each(function(){
        //    $(this).attr('disabled',false);
        //    if (selectedPolicies[$(this).val()]) $(this).attr('disabled',true);
        //});
    }

    function postPermissionSave(){
        selectedPolicies=[];

    }


</script>
<fieldset>
    <legend>Permessi</legend>
<#assign policy=el.getUserPolicy(userDetails)/>
    <table class="pSchema">
        <tr>
            <th></th>
        <#include "../../admin/helpers/permission-tb-header.ftl"/>
            
        </tr>
        <tr>
            <td></td>
            <td><#if policy.canView>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canUpdate>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canAddComment>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canModerate>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canDelete>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canChangePermission>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canAddChild>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canRemoveCheckOut>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canLaunchProcess>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canEnableTemplate>&#10004;<#else>&nbsp;</#if></td>
            <td><#if policy.canBrowse>&#10004;<#else>&nbsp;</#if></td>
            
        </tr>
    </table>
    <#if policy.canChangePermission>
    <a href="#" onclick="if (document.getElementById('modPermission').style.display=='none') {$('#modPermission').show();} else {$('#modPermission').hide();};return false;">Modifica permessi</a>
    <div id="modPermission" style="display:none">
    <input class="submitButton round-button blue" type="button" value="Aggiungi permessi" id="add-permission" name="add-permission"/>
            
    <table class="pSchema">
        <tr>
            <th>Nome</th>
        <#include "../../admin/helpers/permission-tb-header.ftl"/>
            <th>utenti/gruppi</th>
            <th>azione</th>
        </tr>
        <tbody id="permission-list-availables"></tbody>

 
    </table>
     <div id="permission-dialog" title="Aggiungi/modifica permessi">
            <fieldset>
                <form id="permission-form" method="POST" enctype="multipart/form-data">
                <div class="field-component">
                <@checkBox "allUsers" "allUsers" "Tutti gli utenti" {"1":""} />
                </div>
        		<div class="field-component">
                <@multiAutoCompleteFB "groups" "groups" "Gruppi" "${baseUrl}/uService/rest/user/searchAuth" "authority"/>
                </div>
        		<div class="field-component">
                <@multiAutoCompleteFB "users" "users" "Utenti" "${baseUrl}/uService/rest/user/searchUser" "username"/>
                <@hidden "id" "id"/>
                </div>
        		<div class="field-component">
        		  <#assign availablesPolicies={"0","ad-hoc"}/>
				    <#if model['policies']??>
				        <#list model['policies'] as type>
				            <#assign availablesPolicies= availablesPolicies + {type.id,type.name}/>
				        </#list>
				
				    </#if>
                <@selectHash "policy" "policy" "Policy" availablesPolicies/>
                <div id="permission-table">
                <table class="pSchema" >
                    <thead>
                    <tr>
                        <th style="display: none"></th>
                    <#include "../../admin/helpers/permission-tb-header.ftl"/>
                        <th style="display: none"></th>
                    </tr>
                    </thead>
                    <tbody>
                    <tr>
                        <td style="display: none"></td>
                        <td><@checkBox "view" "view" "" {"1":""} /></td>
                        <td><@checkBox "create" "create" "" {"1":""} /></td>
                        <td><@checkBox "update" "update" "" {"1":""} /></td>
                        <td><@checkBox "addComment" "addComment" "" {"1":""} /></td>
                        <td><@checkBox "moderate" "moderate" "" {"1":""} /></td>
                        <td><@checkBox "delete" "delete" "" {"1":""} /></td>
                        <td><@checkBox "changePermission" "changePermission" "" {"1":""} /></td>
                        <td><@checkBox "addChild" "addChild" "" {"1":""} /></td>
                        <td><@checkBox "removeCheckOut" "removeCheckOut" "" {"1":""} /></td>
                        <td><@checkBox "launchProcess" "launchProcess" "" {"1":""} /></td>
                        <td><@checkBox "enableTemplate" "enableTemplate" "" {"1":""} /></td>
                        <td><@checkBox "canBrowse" "canBrowse" "" {"1":""} /></td>
                        <td style="display: none"></td>
                    </tr>
                    </tbody>
                </table>
                </div>
                    <input class="round-button blue" type="button" value="Salva" id="permission-form-submit"/>
                </form>

            </fieldset>
        </div>
        </div>
        </#if>
</fieldset>