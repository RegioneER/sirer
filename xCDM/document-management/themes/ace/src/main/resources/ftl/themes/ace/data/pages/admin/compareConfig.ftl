
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


<@addmenuitem>
{
	"class":"",
	"link":"${baseUrl}/app/admin",
	"level_1":true,
	"title":"Console amministrativa",
	"icon":{"icon":"icon-cogs","title":"xCDM Console"}
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
var impConfig;
var thisConfig;

var impTemplates;
var impTemplatesById;
var thisTemplates;

var impFields;
var impFieldsById;
var thisFields;

var impTypes;
var impTypesById;
var thisTypes;

var impWorkflows;
var impWorkflowsById;
var thisWorkflows;


var impPolicies;
var impPoliciesById;
var thisPolicies;

var impCalendars;
var thisCalendars;

function remoteCalls(){
    $.ajax({
                 url:$('#configUrl').val(),
                 dataType: 'jsonp',
                 success:function(json){
                    impConfig=json;
                    $.getJSON("${baseUrl}/app/rest/admin/configuration", function(data){
                        thisConfig=data;
                        doCompare();
                    });
                 },
                 error:function(){
                     alert("Error");
                 }
            });
}

function loadConfigurations(){
    setTimeout(function(){ remoteCalls(); }, 500);
}

$('#loadConfigJson').click(function(){
    loadConfigurations();
});

function doCompare(){
    console.log("inizio Compare");
    impTemplates=new Object();
    impTemplatesById=new Object();
    thisTemplates=new Object();
    impFields=new Object();
    impFieldsById=new Object();
    thisFields=new Object();
    impTypes=new Object();
    impTypesById=new Object();
    thisTypes=new Object();
    impPolicies=new Object();
    impPoliciesById=new Object();
    thisPolicies=new Object();
    impCalendars=new Object();
    thisCalendars=new Object();
    for (i=0;i<impConfig.templates.length;i++){
        impTemplates[impConfig.templates[i].name]=impConfig.templates[i];
        impTemplatesById[impConfig.templates[i].id]=impConfig.templates[i];
        for(f=0;f<impConfig.templates[i].fields.length;f++){
            impFields[impConfig.templates[i].fields[f].templateName+"_"+impConfig.templates[i].fields[f].name]=impConfig.templates[i].fields[f];
            impFieldsById[impConfig.templates[i].fields[f].id]=impConfig.templates[i].fields[f];
        }
    }
    for (i=0;i<thisConfig.templates.length;i++){
        thisTemplates[thisConfig.templates[i].name]=thisConfig.templates[i];
        for(f=0;f<impConfig.templates[i].fields.length;f++){
            thisFields[thisConfig.templates[i].fields[f].templateName+"_"+thisConfig.templates[i].fields[f].name]=thisConfig.templates[i].fields[f];
        }
    }
    for (i=0;i<impConfig.types.length;i++){
        impTypes[impConfig.types[i].typeId]=impConfig.types[i];
        impTypesById[impConfig.types[i].id]=impConfig.types[i];
    }
    for (i=0;i<thisConfig.types.length;i++){
        thisTypes[thisConfig.types[i].typeId]=thisConfig.types[i];
    }
    impWorkflows=impConfig.processes;
    thisWorkflows=thisConfig.processes;
    for (i=0;i<impConfig.policies.length;i++){
        impPolicies[impConfig.policies[i].name]=impConfig.policies[i];
        impPoliciesById[impConfig.policies[i].id]=impConfig.policies[i];
    }
    for (i=0;i<thisConfig.policies.length;i++){
        thisPolicies[thisConfig.policies[i].name]=thisConfig.policies[i];
    }
    for (i=0;i<impConfig.calendars.length;i++){
        impCalendars[impConfig.calendars[i].name]=impConfig.calendars[i];
    }
    for (i=0;i<thisConfig.calendars.length;i++){
        thisCalendars[thisConfig.calendars[i].name]=thisConfig.calendars[i];
    }
    typesCompare();
    templatesCompare();
    processesCompare();
}

function assocTemplateCompare(typeId){
    template=$("<div class='col-sm-3'></div>");
            template.append($('<h4>Templates</h4>'));
            templateDifferent=false;
            for (ti=0;ti<impTypes[typeId].associatedTemplates.length;ti++){
                t=impTypes[typeId].associatedTemplates[ti];
                found=false;
                templateSpecLi=$('<li>');
                thisTemplateDifferent=false;
                templateSpecLi.append('<span>'+impTypes[typeId].associatedTemplates[ti].metadataTemplateName+'</span>');
                for (tti=0;tti<thisTypes[typeId].associatedTemplates.length;tti++){
                    if (thisTypes[typeId].associatedTemplates[tti].metadataTemplateName==impTypes[typeId].associatedTemplates[ti].metadataTemplateName){
                        found=true;
                        if (thisTypes[typeId].associatedTemplates[tti].enabled!=impTypes[typeId].associatedTemplates[ti].enabled){
                            thisTemplateDifferent=templateDifferent=true;
                            updateTemplateAssocLink=$('<a>');
                            updateTemplateAssocLink.attr('href', '#');
                            updateTemplateAssocLink.attr('data-assoc-id',thisTypes[typeId].associatedTemplates[tti].id);
                            updateTemplateAssocLink.attr('data-type-id', thisTypes[typeId].id);
                            updateTemplateAssocLink.attr('data-enabled', impTypes[typeId].associatedTemplates[ti].enabled);
                            updateTemplateAssocLink.attr('data-template-id', thisTemplates[impTypes[typeId].associatedTemplates[ti].metadataTemplateName].id);
                            updateTemplateAssocLink.html("update");
                            updateTemplateAssocLink.click(function(){
                                tId=$(this).attr('data-template-id');
                                typeIdCode=$(this).attr('data-type-id');
                                aId=$(this).attr('data-assoc-id');
                                enabled=$(this).attr('data-enabled');
                                objToSend=new Object();
                                objToSend.templateId=tId;
                                if (enabled=='true') objToSend.enabled=1;
                                else objToSend.enabled=0;
                                $.ajax({
                                    type: "GET",
                                    url: "${baseUrl}/app/rest/admin/type/"+typeIdCode+"/deAssocTemplate/"+aId,
                                    success: function(data){
                                        if (data.result=='OK'){
                                            goon=true;
                                        }
                                    },
                                    async: false
                                });

                                $.ajax({
                                    type: "POST",
                                    url: "${baseUrl}/app/rest/admin/type/"+typeIdCode+"/assocTemplate",
                                    data: objToSend,
                                    success: function(data){
                                        if (data.result=='OK'){
                                            goon=true;
                                        }
                                    },
                                    async: false
                                });
                                loadConfigurations();
                            });
                            templateSpecLi.append(" - ");
                            templateSpecLi.append(updateTemplateAssocLink);
                        }
                    }
                }
                if (thisTemplateDifferent){
                    templateSpecLi.find('span:first-child').prepend('<i class="fa fa-remove red"></i> ');

                }else {
                    templateSpecLi.find('span:first-child').prepend('<i class="fa fa-check green"></i> ');
                }
                if (!found) {
                    templateDifferent=true;
                    assocTemplateLink=$('<a>');
                    assocTemplateLink.attr('href', '#');
                    assocTemplateLink.attr('data-template-id', thisTemplates[impTypes[typeId].associatedTemplates[ti].metadataTemplateName].id);
                    assocTemplateLink.attr('data-enabled', impTypes[typeId].associatedTemplates[ti].enabled);
                    assocTemplateLink.attr('data-type-Id',thisTypes[typeId].id);
                    assocTemplateLink.click(function(){
                        tId=$(this).attr('data-template-id');
                        typeIdCode=$(this).attr('data-type-Id');
                        enabled=$(this).attr('data-enabled');
                        objToSend=new Object();
                        objToSend.templateId=tId;
                        if (enabled=='true') objToSend.enabled=1;
                        else objToSend.enabled=0;
                        $.ajax({
                            type: "POST",
                            url: "${baseUrl}/app/rest/admin/type/"+typeIdCode+"/assocTemplate",
                            data: objToSend,
                            success: function(data){
                                if (data.result=='OK'){
                                    goon=true;
                                }
                            },
                            async: false
                        });
                        loadConfigurations();
                    });
                    assocTemplateLink.html("create association");
                    templateSpecLi.append(" - ");
                    templateSpecLi.append(assocTemplateLink);
                }
                template.append(templateSpecLi);
            }

            if (templateDifferent){
               template.find('h4').prepend("<i class='fa fa-remove red'></i> ");
            }else {
               template.find('h4').prepend("<i class='fa fa-check green'></i> ");
            }
    ret=new Object();
    ret.content=template;
    ret.diff=templateDifferent;
    return ret;
}

function assocWorkflowCompare(typeId){
    workflow=$("<div class='col-sm-3'></div>");
            workflow.append($('<h4>Workflows</h4>'));
            workflowDifferent=false;
            for (ti=0;ti<impTypes[typeId].associatedWorkflows.length;ti++){
                t=impTypes[typeId].associatedWorkflows[ti];
                found=false;
                workflowSpecLi=$('<li>');
                thisWorkflowDifferent=false;
                workflowSpecLi.append('<span>'+impTypes[typeId].associatedWorkflows[ti].metadataWorkflowName+'</span>');
                for (tti=0;tti<thisTypes[typeId].associatedWorkflows.length;tti++){
                    if (thisTypes[typeId].associatedWorkflows[tti].metadataWorkflowName==impTypes[typeId].associatedWorkflows[ti].metadataWorkflowName){
                        found=true;
                        if (thisTypes[typeId].associatedWorkflows[tti].enabled!=impTypes[typeId].associatedWorkflows[ti].enabled){
                            thisWorkflowDifferent=workflowDifferent=true;
                            updateWorkflowAssocLink=$('<a>');
                            updateWorkflowAssocLink.attr('href', '#');
                            updateWorkflowAssocLink.attr('data-assoc-id',thisTypes[typeId].associatedWorkflows[tti].id);
                            updateWorkflowAssocLink.attr('data-type-id', thisTypes[typeId].id);
                            updateWorkflowAssocLink.attr('data-enabled', impTypes[typeId].associatedWorkflows[ti].enabled);
                            updateWorkflowAssocLink.attr('data-workflow-id', thisWorkflows[impTypes[typeId].associatedWorkflows[ti].metadataWorkflowName].id);
                            updateWorkflowAssocLink.html("update");
                            updateWorkflowAssocLink.click(function(){
                                tId=$(this).attr('data-workflow-id');
                                typeIdCode=$(this).attr('data-type-id');
                                aId=$(this).attr('data-assoc-id');
                                enabled=$(this).attr('data-enabled');
                                objToSend=new Object();
                                objToSend.workflowId=tId;
                                if (enabled=='true') objToSend.enabled=1;
                                else objToSend.enabled=0;
                                $.ajax({
                                    type: "GET",
                                    url: "${baseUrl}/app/rest/admin/type/"+typeIdCode+"/deAssocWorkflow/"+aId,
                                    success: function(data){
                                        if (data.result=='OK'){
                                            goon=true;
                                        }
                                    },
                                    async: false
                                });

                                $.ajax({
                                    type: "POST",
                                    url: "${baseUrl}/app/rest/admin/type/"+typeIdCode+"/assocWorkflow",
                                    data: objToSend,
                                    success: function(data){
                                        if (data.result=='OK'){
                                            goon=true;
                                        }
                                    },
                                    async: false
                                });
                                loadConfigurations();
                            });
                            workflowSpecLi.append(" - ");
                            workflowSpecLi.append(updateWorkflowAssocLink);
                        }
                    }
                }
                if (thisWorkflowDifferent){
                    workflowSpecLi.find('span:first-child').prepend('<i class="fa fa-remove red"></i> ');

                }else {
                    workflowSpecLi.find('span:first-child').prepend('<i class="fa fa-check green"></i> ');
                }
                if (!found) {
                    workflowDifferent=true;
                    assocWorkflowLink=$('<a>');
                    assocWorkflowLink.attr('href', '#');
                    assocWorkflowLink.attr('data-workflow-id', thisWorkflows[impTypes[typeId].associatedWorkflows[ti].metadataWorkflowName].id);
                    assocWorkflowLink.attr('data-enabled', impTypes[typeId].associatedWorkflows[ti].enabled);
                    assocWorkflowLink.attr('data-type-Id',thisTypes[typeId].id);
                    assocWorkflowLink.click(function(){
                        tId=$(this).attr('data-workflow-id');
                        typeIdCode=$(this).attr('data-type-Id');
                        enabled=$(this).attr('data-enabled');
                        objToSend=new Object();
                        objToSend.workflowId=tId;
                        if (enabled=='true') objToSend.enabled=1;
                        else objToSend.enabled=0;
                        $.ajax({
                            type: "POST",
                            url: "${baseUrl}/app/rest/admin/type/"+typeIdCode+"/assocWorkflow",
                            data: objToSend,
                            success: function(data){
                                if (data.result=='OK'){
                                    goon=true;
                                }
                            },
                            async: false
                        });
                        loadConfigurations();
                    });
                    assocWorkflowLink.html("create association");
                    workflowSpecLi.append(" - ");
                    workflowSpecLi.append(assocWorkflowLink);
                }
                workflow.append(workflowSpecLi);
            }

            if (workflowDifferent){
               workflow.find('h4').prepend("<i class='fa fa-remove red'></i> ");
            }else {
               workflow.find('h4').prepend("<i class='fa fa-check green'></i> ");
            }
    ret=new Object();
    ret.content=workflow;
    ret.diff=workflowDifferent;
    return ret;
}

function typesCompare(){
    contentDiv=$('#typesCmpArea');
    contentDiv.html("");
    for (var typeId in impTypes){
        typeLi=$('<li>');
        if (thisTypes[typeId]==undefined){
            typeLi.append('<span>Type '+typeId+' not defined</span>');
            typeLi.append(' - ');
            typeCreateLink=$('<a>');
            typeCreateLink.attr('href', '#');
            typeCreateLink.attr('data-typeId', typeId);
            typeCreateLink.html("create");
            typeCreateLink.click(function(){
                createType($(this).attr('data-typeId'));
                loadConfigurations();
            });
            typeLi.append(typeCreateLink);
        }else {
            typeLi.append('<span>Type '+typeId+' defined</span>');
            typeUl=$('<div class="row"></div>');
            typeUl.attr('id',typeId+"_detail");
            //typeUl.hide();
            diffCheck=new Object();
            different=false;
            metadataDifferent=false;
            metadata=$("<div class='col-sm-3'></div>");
            metadata.append("<h4>Type info</h4>");
            for (var k in impTypes[typeId]){
                if (k!='id' && k!='imageBase64' && k!='titleFieldName' && k!='titleTemplateName'){
                    if (impTypes[typeId][k]!=null && (impTypes[typeId][k].constructor==String || impTypes[typeId][k].constructor==Number || impTypes[typeId][k].constructor==Boolean)) {
                        diffCheck[k]=(impTypes[typeId][k]!=thisTypes[typeId][k]);
                        if (impTypes[typeId][k]!=thisTypes[typeId][k]) metadataDifferent=true;
                        if (diffCheck[k]) {
                            check="<i class='fa fa-remove red'></i> ";
                            value=" (this: "+thisTypes[typeId][k]+", imp: "+inpTypes[typeId][k]+")";
                        }
                        else {
                            check="<i class='fa fa-check green'></i> ";
                            value=" ("+impTypes[typeId][k]+")";
                        }
                        metadata.append("<li>"+check+k+value+"</li>");
                    }
                }
            }
            if (metadataDifferent){
                metadata.find('h4').prepend("<i class='fa fa-remove red'></i> ");
                updateLink=$('<a>');
                updateLink.attr('href','#');
                updateLink.attr('data-typeId', typeId);
                updateLink.click(function(){
                    typeId1=$(this).attr('data-typeId');
                    objToSave=buildTypeDataObject(typeId1);
                    objToSave.id=thisTypes[typeId1].id;
                    typeDataPostRequest(typeId1, objToSave);
                    loadConfigurations();
                });
                updateLink.html('update');
                metadata.find("h4").append(' - ');
                metadata.find("h4").append(updateLink);
            }else {
                metadata.find('h4').prepend("<i class='fa fa-check green'></i> ");
            }
            typeUl.append(metadata);

            tCompare=assocTemplateCompare(typeId);
            templateDifferent=tCompare.diff;
            typeUl.append(tCompare.content);
            wCompare=assocWorkflowCompare(typeId);
            workflowDifferent=wCompare.diff;
            typeUl.append(wCompare.content);





            different=(metadataDifferent || templateDifferent || workflowDifferent);
            if (different){
                typeLi.find('span:first-child').prepend("<i class='fa fa-remove red'></i> ");
            }else{
                typeLi.find('span:first-child').prepend("<i class='fa fa-check green'></i> ");
            }

            detailLink=$('<a>');
            detailLink.attr('href','#');
            detailLink.attr('data-typeId', typeId);
            detailLink.click(function(){
                typeId1=$(this).attr('data-typeId');
                if ($('#'+typeId1+"_detail").is(":visible")){
                    $('#'+typeId1+"_detail").hide();
                }else $('#'+typeId1+"_detail").show();
            });
            detailLink.html('show/hide detail');

            typeLi.append(' - ');
            typeLi.append(detailLink);
            typeLi.append(typeUl);
        }
        contentDiv.append(typeLi);
    }
}

function buildTypeDataObject(typeId){
    objToSave=new Object();
        for (var k in impTypes[typeId]){
          if (k!='id' && k!='imageBase64' && k!='titleFieldName' && k!='titleTemplateName'){
            if (impTypes[typeId][k]!=null){
              if (impTypes[typeId][k].constructor==String
                  ||
                  impTypes[typeId][k].constructor==Number
                 ) {
                objToSave[k]=impTypes[typeId][k];
              }
              if (impTypes[typeId][k].constructor==Boolean && impTypes[typeId][k]){
                if (k=='hasFileAttached') objToSave['hasFile']=true;
                else objToSave[k]=true;
              }
            }
          }
        }
        if (impTypes[typeId]["titleFieldName"]!=undefined && impTypes[typeId]["titleFieldName"]!=null && thisFields[impTypes[typeId]["titleTemplateName"]+"_"+impTypes[typeId]["titleFieldName"]]!=undefined){
           objToSave.titleField=thisFields[impTypes[typeId]["titleTemplateName"]+"_"+impTypes[typeId]["titleFieldName"]].id;
        }
    return objToSave;
}

function typeDataPostRequest(typeId, objToSave){
    goon=false;
    $.ajax({
        type: "POST",
        url: "${baseUrl}/app/rest/admin/type/save",
        data: objToSave,
        success: function(data){
            if (data.result=='OK'){
                goon=true;
            }
        },
        async: false
    });
    return goon;
}

function createType(typeId){
    objToSave=buildTypeDataObject(typeId);
    typeDataPostRequest(typeId, objToSave);
}

function processesCompare(){
    contentDiv=$('#processesCmpArea');
    contentDiv.html("");
    for (var k in impConfig.processes){
        pLi=$('<li>');
        if (thisConfig.processes[k]!=undefined){
            pLi.append("<span>Process: "+k+" found</span>");
            if (impConfig.processes[k].checksum==thisConfig.processes[k].checksum){
                pLi.find('span').prepend("<i class='fa fa-check green'></i>");
            }else {
                deployLink.attr('href', '#');
                deployLink.attr('data-pkey', k);
                deployLink.html("update process");
                deployLink.click(function(){
                    pKey=$(this).attr('data-pkey');
                    deployProcess(pKey);
                });
                pLi.append(" - ");
                pLi.append(deployLink);
            }
        }else {
            pLi.append("<span>Process: "+k+" not found</span>");
            deployLink=$('<a>');
            deployLink.attr('href', '#');
            deployLink.attr('data-pkey', k);
            deployLink.html("deploy process");
            deployLink.click(function(){
                pKey=$(this).attr('data-pkey');
                deployProcess(pKey);
            });
            pLi.append(" - ");
            pLi.append(deployLink);
        }
        contentDiv.append(pLi);
    }
}

function deployProcess(pKey){
     objToSave=new Object();
     objToSave.content=impConfig.processes[pKey].content;
     $.ajax({
            type: "POST",
            url: "${baseUrl}/app/rest/admin/workflow/upload/"+pKey,
            data: objToSave,
            success: function(data){
                    if (data.result=='OK'){
                       goon=true;
                    }
                },
            async: false
        });
     return false;
}



function templatesCompare(){
    tplDiv=$('#templatesCmpArea');
    tplDiv.html("");
    for (var k in impTemplates){
        if (thisTemplates[k]==undefined){
            //Nuovo template
            tplLi=$('<li>');
            tplCreateLink=$('<a>');
            tplCreateLink.attr('data-name',k);
            tplCreateLink.attr('href','#');
            tplCreateLink.html('create');
            tplCreateLink.click(function(){
                tplName=$(this).attr('data-name');
                createTemplate(impTemplates[tplName]);
                return false;
            });
            tplLi.append('<span>'+k+' not found - </span>');
            tplLi.append(tplCreateLink);
            tplDiv.append(tplLi);
        }else {
             tplLi=$('<li>');
             tplLi.append('<span>'+k+' found</span>');
             compareResult=compareTpl(k);
             if (compareResult.updateMetadata){
                updateLink=$('<a>');
                updateLink.attr('href', "#");
                updateLink.html("update");
                tplLi.append(" - ");
                tplLi.append(updateLink);
             }
             if (compareResult.reorder){
                reorderLink=$('<a>');
                reorderLink.attr('href', "#");
                reorderLink.attr('data-tpl-name', k);
                reorderLink.html("reorder fields");
                reorderLink.click(function(){
                    tplName=$(this).attr('data-tpl-name');
                    reorderFields(tplName);
                });
                tplLi.append(" - ");
                tplLi.append(reorderLink);
             }
             if (compareResult.showAction){
                 showActionLink=$('<a>');
                 showActionLink.attr('href', "#");
                 showActionLink.attr('data-tpl', k);
                 showActionLink.html("show/hide");
                 showActionLink.click(function(){
                    tplName=$(this).attr('data-tpl');
                    if ($('#'+tplName+'-detail').is(':visible')){
                        $('#'+tplName+'-detail').hide();
                    }else {
                        $('#'+tplName+'-detail').show();
                    }
                 })
                 tplLi.append(" - ");
                 tplLi.append(showActionLink);
             }
             tplLi.append(compareResult.content);
             tplDiv.append(tplLi);
        }
    }
}

function compareTpl(tplName){
     tplOrig=impTemplates[tplName];
     tplDest=thisTemplates[tplName];
     ret=new Object();
     ret.content=$('<ul>');
     ret.content.attr('id', tplName+"-detail");
     ret.content.hide();
     ret.showAction=true;
     ret.updateMetadata=false;
     if (tplOrig.auditable==tplDest.auditable){
        ret.content.append("<li><i class='fa fa-check green'></i> Auditable: "+tplOrig.auditable+"</li>");
     }else {
        ret.content.append("<li><i class='fa fa-remove red'></i> Auditable: orig:"+tplOrig.auditable+" - dest:"+tplDest.auditable+"</li>");
        ret.updateMetadata=true;
     }
     if (tplOrig.deleted==tplDest.deleted){
             ret.content.append("<li><i class='fa fa-check green'></i> deleted: "+tplOrig.deleted+"</li>");
     }else {
        ret.content.append("<li><i class='fa fa-remove red'></i> deleted: orig:"+tplOrig.deleted+" - dest:"+tplDest.deleted+"</li>");
        ret.updateMetadata=true;
     }
     if (tplOrig.description==tplDest.description){
        ret.content.append("<li><i class='fa fa-check green'></i> description: "+tplOrig.description+"</li>");
     }else {
        ret.content.append("<li><i class='fa fa-remove red'></i> description: orig:"+tplOrig.description+" - dest:"+tplDest.description+"</li>");
        ret.updateMetadata=true;
     }
     ret.reorder=true;
     for (i=0;i<tplOrig.fields.length;i++){
        fieldFound=false;
        for (j=0;j<tplDest.fields.length;j++){
            if (tplOrig.fields[i].name==tplDest.fields[j].name) fieldFound=true;
        }
        if (!fieldFound) {
            ret.reorder=false;
            fieldLi=$("<li>");
            fieldCreateLink=$("<a>");
            fieldCreateLink.attr('data-orig-idx', i);
            fieldCreateLink.attr('data-tpl-name', tplName);
            fieldCreateLink.attr('href', "#");
            fieldCreateLink.html("create");
            fieldCreateLink.click(function(){
                goon=createField($(this).attr('data-tpl-name'), $(this).attr('data-orig-idx'), thisTemplates[$(this).attr('data-tpl-name')].id);
            });
            fieldLi.append($('<span>Field '+tplOrig.fields[i].name+' not found - </span>'));
            fieldLi.append(fieldCreateLink);
        }else {
            fieldLi=$("<li>");
            fieldLi.append($('<span>Field '+tplOrig.fields[i].name+' found</span>'));
        }
        ret.content.append(fieldLi);
     }
     return ret;
}

function getSortedKeys(obj) {
    var keys = []; for(var key in obj) keys.push(key);
    return keys.sort(function(a,b){return obj[a]-obj[b]});
}

function reorderFields(tplName){
    tplOrig=impTemplates[tplName];
    tplDest=thisTemplates[tplName];
    fieldsOrdered=new Object();
    for (i=0;i<tplOrig.fields.length;i++){
        fieldsOrdered[tplOrig.fields[i].position]=tplOrig.fields[i];
    }
    sortedKey=getSortedKeys(fieldsOrdered);
    for (i=sortedKey.length-1;i>=0;i--){
        for (j=0;j<tplDest.fields.length;j++){
            if (tplDest.fields[j].name==fieldsOrdered[sortedKey[i]].name){
                $.ajax({
                    type: "GET",
                    url: "${baseUrl}/app/rest/admin/template/"+tplDest.id+"/field/"+tplDest.fields[j].id+"/moveTop",
                    success: function(data){
                        if (data.result=='OK'){
                            goon=true;
                        }
                    },
                    async: false
                });
            }
        }

    }
}

function createTemplate(tpl){
    var ctpl=tpl;
    objToSave=new Object();
    objToSave.name=ctpl.name;
    objToSave.description=ctpl.description;
    if (ctpl.auditable) objToSave.auditable=ctpl.auditable;
    if (ctpl.deleted) objToSave.deleted=ctpl.deleted;
    var goon=false;
    $.ajax({
        type: "POST",
        url: "${baseUrl}/app/rest/admin/template/save",
        data: objToSave,
        success: function(data){
                if (data.result=='OK'){
                   goon=true;
                   ctpl.id=data.ret;
                }
            },
        async: false
    });
    if (goon){
        for (i=0;i<ctpl.fields.length && goon;i++){
            goon=createField(ctpl.name, i, ctpl.id);
        }
        loadConfigurations();
    }else {
        alert("Errore creazione!!!");

    }
}

function createField(tplName, idx, tplDestId){
    f=impTemplates[tplName].fields[i];
    fieldToSave=new Object();
    fieldToSave.name=f.name;
    fieldToSave.type=f.type;
    fieldToSave.externalDictionary=f.externalDictionary;
    fieldToSave.addFilterFields=f.addFilterFields;
    fieldToSave.typefilters=f.typefilters;
    fieldToSave.availableValues=f.availableValues;
    fieldToSave.macro=f.macro;
    fieldToSave.macroView=f.macroView;
    fieldToSave.size=f.size;
    if (f.mandatory) fieldToSave.mandatory=f.mandatory;
    fieldToSave.baseNameOra=f.baseNameOra;
    $.ajax({
        type: "POST",
        url: "${baseUrl}/app/rest/admin/template/"+tplDestId+"/saveField",
        data: fieldToSave,
        success: function(data){
            if (data.result=='OK'){
                goon=true;
            }else {
                goon=false;
            }
        },
        async: false
    });
    return goon;
}

loadConfigurations();
</@script>




