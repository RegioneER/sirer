
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2","jstree/themes/default/style.min.css"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base","jstree/jstree.min.js"],
	"inline_scripts":[],
	"title" : "Dettaglio",
 	"description" : "Dettaglio" 
} />



<#assign link={
	    		"title":"xCDM Console",
	    		"link":"${baseUrl}/app/admin"
	    	} 
	    	/>  
<#global breadcrumbs={"title":"Elemento ${model['elType'].typeId}","links":[]} />
<#global breadcrumbs=breadcrumbs+{"links":breadcrumbs.links+[link]} />

<@addmenuitem>
{ 
	"class":"",
	"link":"${baseUrl}/app/admin",
	"level_1":true,
	"title":"Console amministrativa",
	"icon":{"icon":"icon-cogs","title":"xCDM Console"},
	"submenu":[
		{
			"class":"",
			"link":"${baseUrl}/app/admin/editType/${model['elType'].id?c}",
			"level_2":true,
			"title":"Tempi",
			"icon":{"icon":"fa fa-file","title":"Elemento ${model['elType'].typeId}"}
		}
	]
	}
</@addmenuitem>

<@addmenuitem>
{
	"class":"",
	"link":"/ACM",
	"level_1":true,
	"title":"Gestione utenti",
	"icon":{"icon":"fa fa-users","title":"Gestione utenti"}
		}
</@addmenuitem>


<@addmenuitem>
{
	"class":"",
	"link":"${baseUrl}/pconsole",
	"level_1":true,
	"title":"Gestione processi",
	"icon":{"icon":"fa fa-code-fork","title":"Gestione processi"}
		}
</@addmenuitem>

<@addmenuitem>
{
	"class":"",
	"link":"${baseUrl}/app/admin/messages/it_IT",
	"level_1":true,
	"title":"Gestione Localizzazione",
	"icon":{"icon":"fa fa-flag","title":"Gestione Localizzazione"}
		}
</@addmenuitem>
<@script>
    		var selects=$('select');
    		$.each(selects, function(i, currSelect){
    			var options = $(currSelect).find('option');
				var arr = options.map(function(_, o) { return { t: $(o).text(), v: o.value }; }).get();
				arr.sort(function(o1, o2) { return o1.t.toUpperCase() > o2.t.toUpperCase() ? 1 : o1.t.toUpperCase() < o2.t.toUpperCase() ? -1 : 0; });
				options.each(function(i, o) {
				  o.value = arr[i].v;
				  $(o).text(arr[i].t);
				});
    		});
    		
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
                        if ($('#container:checked').size()>0) {
                        	$('#isContainer').show();
                        	$('#isContainerLi').show();
                        }
                        else {
                        	$('#isContainer').hide();
                        	$('#isContainerLi').hide();
                        }
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
            listRow: childListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/addChild",
            getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/getChilds",
            deleteUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/delChild",
            dialogWidth: "500px",
            postSave: postChildSave,
            postRefresh: postChildRefresh,
            listType: "tr"
        });
        child.refreshList();

        assoctemplate=new ajaXmrTab({
            elementName: "assoctemplate",
            baseUrl: "${baseUrl}",
            listRow: assocTemplateListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/assocTemplate",
            getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/getTemplates",
            dialogWidth: "500px",
            listType: "tr",
            postSave: postassocTemplateSave,
            postRefresh: postassocTemplateRefresh
        });
        assoctemplate.refreshList();

                permission=new ajaXmrTab({
                    elementName: "permission",
                    baseUrl: "${baseUrl}",
                    listRow:permissionListRow,
                    saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/acl/save",
                    getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/acl/getAll",
                    getSingleElementUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/acl/get",
                    deleteUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/acl/delete",
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
                    listRow: assocWorkFlowListRow,
                    saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/assocWorkflow",
                    getAllUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/getWorkflows",
                    deleteUrl: "${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/deAssocWorkflow",
                    dialogWidth: "500px",
                    listType: "tr",
                    postSave: postAssocWorkflowSave,
                    postRefresh: postAssocWorkflowRefresh,
                    postClearForm: postAssocWorkflowClear
                });
                assocWorkflow.refreshList();


                if ($('#container:checked').size()>0) {
                	$('#isContainer').show();
                	$('#isContainerLi').show();
        		}
        else {
        	$('#isContainer').hide();
        	$('#isContainerLi').hide();
        }
        $( "#templateAcl-dialog" ).dialog({
            autoOpen: false,
            height: 400,
            width: 600,
            modal: true,
            buttons: {
                Cancel: function() {
                    $( this ).dialog( "close" );
                }
            },
            close: function() {
            }
        });
        $('#templateAcl-form-submit').click(function(){
        	loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        	var formData=new FormData($('#templateAcl-form')[0]);
        	$.ajax({
			type: "POST",
			url: $('#templateAcl-form').attr('action'),
			contentType:false,
			processData:false,
			async:false,
			cache:false,
			data: formData,
			success: function(obj){
			    if (obj.result=="OK") {
				loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
				$( "#templateAcl-dialog" ).dialog( "close" );
	
			    }else {
				loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
				$( "#templateAcl-dialog" ).dialog( "close" );
			    }
			    assoctemplate.refreshList();
			},
			error: function(){
			    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
			    $( "#templateAcl-dialog" ).dialog( "close" );
			}
		   });
        	
        });

    
    function postAssocWorkflowClear(){
    	$.ajax({
		dataType: "json",
		url: "${baseUrl}/process-engine/repository/process-definitions?suspended=false&latest=true&categoryNotEquals=activiti-report&size=100",
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
        return '<td><a href="${baseUrl}/app/admin/editType/'+jsonRow.id+'">'+jsonRow.typeId+'</a></td>';
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
        if (jsonRow.detailTemplate!=null) 
        ret+="<td>"+jsonRow.detailTemplate+"</td>";
        else ret+="<td>&nbsp;</td>";
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
        enabledTick="<i class='fa fa-close'></i> ";
        if (jsonRow.enabled) enabledTick="<i class='fa fa-check'></i> ";
        startTick="<i class='fa fa-close'></i> ";
        if (jsonRow.startOnCreate) startTick="<i class='fa fa-check'></i> ";
        updateTick="<i class='fa fa-close'></i> ";
        if (jsonRow.startOnUpdate) updateTick="<i class='fa fa-check'></i> ";
        deleteTick="<i class='fa fa-close'></i> ";
        if (jsonRow.startOnDelete) deleteTick="<i class='fa fa-check'></i> ";
        row="";
        row+="<td>"+jsonRow.processKey+"</td>";
        row+="<td>"+enabledTick+"</td>";
        row+="<td>"+startTick+"</td>";
        row+="<td>"+updateTick+"</td>";
        row+="<td>"+deleteTick+"</td>";
        return row;
    }

    var availableFields=new Array();

    function assocTemplateListRow(jsonRow){
        allowedTemplates[jsonRow.metadataId]=true;
        tick="<i class='fa fa-close'></i> ";
        if (jsonRow.enabled) tick="<i class='fa fa-check'></i> ";
        row='<td><a href="${baseUrl}/app/admin/editTemplate/'+jsonRow.metadataId+'">'+jsonRow.metadataTemplateName+'</a></td>';
        row+='<td>'+tick+'</a></td>';
        row+='<td><a href="#" class="template-delete" style="display: inline-block" title="Elimina" data-id="'+jsonRow.id+'"><i class="icon icon-trash"></i> </a></td>'
        row+='<td><a href="#" class="templateAcl-add-link" action="'+jsonRow.id+'" title="Aggiungi permessi"><i class="icon icon-plus"> </i><i class="icon icon-lock"></i></a>';
        if (jsonRow.templateAcls.length>0){
        	for (var a=0;a<jsonRow.templateAcls.length;a++){
        		row+="<br/><a href='#' class='templateAcl-delete-link' action='"+jsonRow.templateAcls[a].id+"' assoc='"+jsonRow.id+"'><i class=\"icon icon-trash\"></i> </a>";
        		row+="&nbsp;&nbsp; Permessi: ";
        		if (jsonRow.templateAcls[a].policy.canView) row+="V&nbsp;";
        		if (jsonRow.templateAcls[a].policy.canCreate) row+="C&nbsp;";
        		if (jsonRow.templateAcls[a].policy.canUpdate) row+="M&nbsp;";
        		if (jsonRow.templateAcls[a].policy.canDelete) row+="E&nbsp;";
        		row+=" - Container: ";
        		for (var c=0;c<jsonRow.templateAcls[a].containers.length;c++){
        			if (c>0) row+=",";
        			if (jsonRow.templateAcls[a].containers[c].authority) row+="g:";
        			else row+="u:"; 
        			row+=jsonRow.templateAcls[a].containers[c].container;
        		}
        	}
        	
        }
        row+="</td>";
        return row;
}



    function postassocTemplateRefresh(){
    	$('.template-delete').unbind("click");
    	$('.template-delete').click(function(){
    	     var url="${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/deAssocTemplate/"+$(this).attr('data-id');
             if (confirm("Sei sicuro")){
                loadingScreen("Eliminazione in corso...", "${baseUrl}/int/images/loading.gif");
                $.ajax({
                    type: "GET",
                    url: url,
                    success: function(obj){
                        if (obj.result=="OK") {
                            loadingScreen("Eliminazione effettuata!","${baseUrl}/int/images/green_check.jpg",2000);
                            assoctemplate.refreshList();
                        } else {
                            loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                        }
                    }
                });
            }
            return false;
    	});
        $('#assoctemplate-form #templateId option').each(function(){
            $(this).attr('disabled',false);
            if (allowedTemplates[$(this).val()]) $(this).attr('disabled',true);
        });
        $('.templateAcl-add-link').unbind("click");
        $('.templateAcl-add-link').click(function(){
        	console.log("sono qui!!!");
        	$('#templateAcl-form').attr('action',"${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/template/"+$(this).attr('action')+"/acl");
        	$( "#templateAcl-dialog" ).dialog("open");
        	return false;
        });
        $('.templateAcl-delete-link').unbind("click");
        $('.templateAcl-delete-link').click(function(){
        	url="${baseUrl}/app/rest/admin/type/${model['elType'].id?c}/template/"+$(this).attr('assoc')+"/acl/"+$(this).attr('action')+"/delete";
        	$.ajax({
                    type: "GET",
                    url: url,
                    success: function(obj){
                        if (obj.result=="OK") {
                            loadingScreen("Eliminazione effettuata!", "${baseUrl}/int/images/green_check.jpg",2000);
                            assoctemplate.refreshList();
                        } else {
                            loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                        }
                    }
                });
                return false;
        });
        
        //$('#titleField').html("<option>Selezionare un campo</option>");
    }

    function postassocTemplateSave(){
        allowedTemplates=[];
        availableFields=[];

    }

</@script>

