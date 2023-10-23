<script>

    $(document).ready(function(){
                $('#policy').change(function(){
                    if ($('#policy').val()==0) $('#permission-table').show();
                    else $('#permission-table').hide();
                });

            $('#editType-form-submit').click(function(){
            loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
            var formData=new FormData($('#type-form')[0]);
            var actionUrl=$('#type-form').attr("action");
            $.ajax({
                type: "POST",
                url: actionUrl,
                contentType:false,
                processData:false,
                async:false,
                cache:false,
                data: formData,
                success: function(obj){
                    if (obj.result=="OK") {
                        if ($('#container:checked').size()>0) $('#isContainer').show();
                        else $('#isContainer').hide();
                        loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                       if (obj.redirect){
                            window.location.href=obj.redirect;
                        }
                    }else {
                        loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });
        });
        child=new ajaXmrTab({
            elementName: "child",
            baseUrl: "${baseUrl}",
            listRow:childListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/addChild",
            getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/getChilds",
            deleteUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/delChild",
            dialogWidth: "500px",
            postSave: postChildSave,
            postRefresh: postChildRefresh,
            listType: "br"
        });
        child.refreshList();

        assoctemplate=new ajaXmrTab({
            elementName: "assoctemplate",
            baseUrl: "${baseUrl}",
            listRow:assocTemplateListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/assocTemplate",
            getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/getTemplates",
            deleteUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/deAssocTemplate",
            dialogWidth: "500px",
            listType: "br",
            postSave: postassocTemplateSave,
            postRefresh: postassocTemplateRefresh
        });
        assoctemplate.refreshList();

                permission=new ajaXmrTab({
                    elementName: "permission",
                    baseUrl: "${baseUrl}",
                    listRow:permissionListRow,
                    saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/acl/save",
                    getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/acl/getAll",
                    getSingleElementUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/acl/get",
                    deleteUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/acl/delete",
                    dialogWidth: "800px",
                    postSave: postPermissionSave,
                    postRefresh: postPermissionRefresh,
                    listType: "tr",
                    postPopulateFunction: postPermissionPopulate
                });
                permission.refreshList();

                assocWorkflow=new ajaXmrTab({
                    elementName: "assocWorkflow",
                    baseUrl: "${baseUrl}",
                    listRow:assocWorkFlowListRow,
                    saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/assocWorkflow",
                    getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/getWorkflows",
                    deleteUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id}/deAssocWorkflow",
                    dialogWidth: "500px",
                    listType: "br",
                    postSave: postAssocWorkflowSave,
                    postRefresh: postAssocWorkflowRefresh,
                    postClearForm: postAssocWorkflowClear
                });
                assocWorkflow.refreshList();


                if ($('#container:checked').size()>0) $('#isContainer').show();
        else $('#isContainer').hide();

        }
    );
    
    function postAssocWorkflowClear(){
    	console.log("sono qui");
    	$.ajax({
		dataType: "json",
		url: "${baseUrl}/process-engine/repository/process-definitions?suspended=false&categoryNotEquals=activiti-report&size=100",
		success: function(data){
				console.log(data.data);
				$('#wfId').html("");
				for (i=0;i<data.data.length;i++){
					$('#wfId').append("<option value='"+data.data[i].key+"'>"+data.data[i].name+"</option>");		
				}
			}
		});
    	
    }

    var allowedChilds=new Array();

    var dataPerm=null;



    function postPermissionPopulate(jsonRow){
        dataPerm=jsonRow;
        $('#cgroup')[0].checked=false;
        $('#cuser')[0].checked=false;
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

    function childListRow(jsonRow){
        console.log("aggiungo "+jsonRow.id);
        allowedChilds[jsonRow.id]=true;
        return '<b>'+jsonRow.typeId+'</b>';
    }


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
        ret+="<td>";
        if (jsonRow.containers!=null){
            for (c=0;c<jsonRow.containers.length;c++){
                if (c>0)ret+=", ";
                if (jsonRow.containers[c].authority) {
                	if (jsonRow.containers[c].dynamic) ret+="d:";
                	else ret+="g:";
                }
                else ret+="u:";
                ret+=jsonRow.containers[c].container;
            }
        }
        
        ret+="</td>";
        ret+="<td>"+jsonRow.detailTemplate+"</td>";
        return ret;
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

    function postChildRefresh(){
        $('#child-form #elementId option').each(function(){
            $(this).attr('disabled',false);
            if (allowedChilds[$(this).val()]) $(this).attr('disabled',true);
        });
    }

    function postChildSave(){
        allowedChilds=[];
    }

    var allowedTemplates=new Array();

    var allowedWorkflows=new Array();

    function postAssocWorkflowSave(){
        allowedWorkflows=[];
    }

    function postAssocWorkflowRefresh(){
        $('#assocWorkflow-form #wfId option').each(function(){
            $(this).attr('disabled',false);
            if (allowedWorkflows[$(this).val()]) $(this).attr('disabled',true);
        });
    }

    function assocWorkFlowListRow(jsonRow){
        tick="&#10007;";
        if (jsonRow.enabled) tick="&#10003;";
        return '<b>'+jsonRow.processKey+' '+tick+'</b>';
    }

    var availableFields=new Array();

    function assocTemplateListRow(jsonRow){
        allowedTemplates[jsonRow.metadataTemplate.id]=true;
        tick="&#10007;";
        if (jsonRow.enabled) tick="&#10003;";
        for (var c=0;c<jsonRow.metadataTemplate.fields.length;c++){
            availableFields[availableFields.length]=jsonRow.metadataTemplate.name+'.'+jsonRow.metadataTemplate.fields[c].name;
            var selected='';
            <#if model['elType'].titleField??>
            if ('${model['elType'].titleField.id}'==jsonRow.metadataTemplate.fields[c].id) selected='selected';
            </#if>
            $('#titleField').append("<option value='"+jsonRow.metadataTemplate.fields[c].id+"' "+selected+">"+jsonRow.metadataTemplate.name+'.'+jsonRow.metadataTemplate.fields[c].name+"</option>")
        }
        return '<b><a href="${baseUrl}/app/admin/editTemplate/'+jsonRow.metadataTemplate.id+'">'+jsonRow.metadataTemplate.name+' '+tick+'</a></b>';
    }



    function postassocTemplateRefresh(){
        $('#assoctemplate-form #templateId option').each(function(){
            $(this).attr('disabled',false);
            if (allowedTemplates[$(this).val()]) $(this).attr('disabled',true);
        });
        //$('#titleField').html("<option>Selezionare un campo</option>");
    }

    function postassocTemplateSave(){
        allowedTemplates=[];
        availableFields=[];

    }

</script>

<div class="admin-home-main">
    <a class="link-back" href="${baseUrl}/app/admin">Home Page - Console amministrazione</a>
    <br/>
    <fieldset>
    <legend>Elemento ${model['elType'].typeId}</legend>
        <div class="floatbox-right"/>
        <fieldset id="isContainer">
            <legend>Figli</legend>
            <input class="submitButton round-button blue" type="button" value="Aggiungi figlio" id="add-child" name="add-child"/>
            <div  id="child-list-availables">
            </div>
        </fieldset>
        <fieldset>
            <legend>Metadati</legend>
            <input class="submitButton round-button blue" type="button" value="Aggiungi template" id="add-assoctemplate" name="add-assoctemplate"/>
            <div  id="assoctemplate-list-availables">
            </div>
        </fieldset>
        <fieldset>
            <legend>Workflow</legend>
            <input class="submitButton round-button blue" type="button" value="Aggiungi Workflow" id="add-assocWorkflow" name="add-assocWorkflow"/>
            <div  id="assocWorkflow-list-availables">
            </div>
        </fieldset>
        <fieldset>
            <legend>Schema Permessi</legend>
            <input class="submitButton round-button blue" type="button" value="Aggiungi permessi" id="add-permission" name="add-permission"/>
            <table class="pSchema">
                <thead>
                <tr>
                    <th>Policy</th>
                <#include "helpers/permission-tb-header.ftl"/>
                    <th>Gruppi/utenti</th>
                    <th>Template</th>
                    <th>Action</th>
                </tr>
                </thead>
                <tbody id="permission-list-availables"></tbody>

            </table>
        </fieldset>
        </div>
    <form id="type-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <img src="${model['elType'].imageBase64!}"/>
        <br/>
    <#if model['elType'].selfRecursive>
        <#assign selfRecursive = ["1"]>
    </#if>
    <#if model['elType'].container>
        <#assign container = ["1"]>
    </#if>
    <#if model['elType'].rootAble>
        <#assign rootAble= ["1"]>
    </#if>
    <#if model['elType'].hasFileAttached>
        <#assign hasFileAttached= ["1"]>
    </#if>
    <#if model['elType'].checkOutEnabled>
        <#assign checkOutEnabled= ["1"]>
    </#if>
    <div style="display: inline-block">
    <@hidden "id" "id" model['elType'].id/>
    <div class="field-component">
        <@fileChooser "img" "img" "Cambia icona"/>
    </div>
    <div class="field-component">
        <@textbox "typeId" "typeId" "Nome tipologia" model['elType'].typeId 40/>
    </div>
    <div class="field-component">
        <@checkBox "selfRecursive" "selfRecursive" "Pu� contenere elementi dello stesso tipo" {"1":""} selfRecursive />
    </div>
        <div class="field-component">
        <@checkBox "container" "container" "Pu� contenere altri elementi" {"1":""} container/>
        </div>
        <div class="field-component">
        <@checkBox "hasFile" "hasFile" "Prevede file allegato" {"1":""} hasFileAttached/>
        </div>
        <div class="field-component">
        <@checkBox "rootAble" "rootAble" "Livello root" {"1":""} rootAble/>
        </div>
        <div class="field-component">
        <@checkBox "checkOutEnabled" "checkOutEnabled" "Abilita modifica con ChekOut e CheckIn" {"1":""} checkOutEnabled/>
        </div>
        <div class="field-component">
        <@selectHash "titleField" "titleField" "Campo da utilizzare come titolo"/>
        </div>
        <div class="field-component">
        <@textbox "ftlRowTemplate" "ftlRowTemplate" "Template griglia" model['elType'].ftlRowTemplate 40/>
        </div>
        <div class="field-component">
        <@textbox "ftlDetailTemplate" "ftlDetailTemplate" "Template dettaglio" model['elType'].ftlDetailTemplate 40/>
        </div>
        <div class="field-component">
        </div>
    <input class="round-button blue" type="button" value="Salva" id="editType-form-submit"/>
    </form>

    </div>


    <#assign availablesType={}/>
    <#if model['elTypes']??>
        <#list model['elTypes'] as type>
        <#if type.id != model['elType'].id>
            <#assign availablesType= availablesType + {type.id,type.typeId}/>
        </#if>
        </#list>

    </#if>

    <#assign availablesTemplates={}/>
    <#if model['templates']??>
        <#list model['templates'] as type>
            <#if !type.wfManaged>
                <#assign availablesTemplates= availablesTemplates + {type.id,type.name}/>
            </#if>
        </#list>
    </#if>

    <#assign availablesPolicies={"0","ad-hoc"}/>
    <#if model['policies']??>
        <#list model['policies'] as type>
            <#assign availablesPolicies= availablesPolicies + {type.id,type.name}/>
        </#list>

    </#if>

    <div id="child-dialog" title="Aggiungi figlio">
        <fieldset>
            <form id="child-form" method="POST" enctype="multipart/form-data">
            <@selectHash "elementId" "elementId" "Documento figlio" availablesType/>
                <br/>

                <input class="round-button blue" type="button" value="Salva" id="child-form-submit"/>
            </form>

        </fieldset>
    </div>

    <div id="assoctemplate-dialog" title="Aggiungi template">
        <fieldset>
            <form id="assoctemplate-form" method="POST" enctype="multipart/form-data">
            <@selectHash "templateId" "templateId" "Template" availablesTemplates/>
                <br/>
            <@checkBox "enabled" "enabled" "Attivo" {"1":""} /><br/>
                <input class="round-button blue" type="button" value="Salva" id="assoctemplate-form-submit"/>
            </form>

        </fieldset>
    </div>



        <div id="assocWorkflow-dialog" title="Aggiungi Workflow">
            <fieldset>
                <form id="assocWorkflow-form" method="POST" enctype="multipart/form-data">
                <@selectHash "wfId" "wfId" "Processo"/>
                    <br/>
                    
                <@checkBox "enabled" "enabled" "Attivo" {"1":""} /><br/>
                
                
                <@checkBox "startOnCreate" "startOnCreate" "Avviato alla creazione" {"1":""} /><br/>
                
                <@checkBox "startOnUpdate" "startOnCreate" "Avviato alla modifica" {"1":""} /><br/>
                
                <@checkBox "startOnDelete" "startOnCreate" "Avviato alla cencellazione" {"1":""} /><br/>
                
                    <input class="round-button blue" type="button" value="Salva" id="assocWorkflow-form-submit"/>
                </form>

            </fieldset>
        </div>


        <div id="permission-dialog" title="Aggiungi/modifica permessi">
            <fieldset>
                <form id="permission-form" method="POST" enctype="multipart/form-data">
                <div class="field-component">
                <@checkBox "allUsers" "allUsers" "Tutti gli utenti" {"1":""} />
                </div>
        	<div class="field-component">
                <@checkBox "cuser" "cuser" "Owner" {"1":""} />
                </div>
        		<div class="field-component">
                <@multiAutoCompleteFB "groups" "groups" "Gruppi" "${baseUrl}/uService/rest/user/searchAuth" "authority"/>
                </div>
        		<div class="field-component">
                <@multiAutoCompleteFB "users" "users" "Utenti" "${baseUrl}/uService/rest/user/searchUser" "username"/>
                <div class="field-component">
        		<@textbox "templateRef" "templateRef" "Dynamic Team" "" />
                </div>
        	
                <@hidden "id" "id"/>
                </div>
        		<div class="field-component">
                <@selectHash "policy" "policy" "Policy" availablesPolicies/>
                <div id="permission-table">
                <table class="pSchema" >
                    <thead>
                    <tr>
                        <th style="display: none"></th>ass
                    <#include "helpers/permission-tb-header.ftl"/>
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
                <div class="field-component">
                <@textbox "detailTemplate" "detailTemplate" "Template ad-hoc" "" />
                </div>
                </div>
                    <input class="round-button blue" type="button" value="Salva" id="permission-form-submit"/>
                </form>

            </fieldset>
        </div>


</fieldset>

    </div>

