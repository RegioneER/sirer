<@script>
    
    function claimTaskListener(){
    	$('.claim').unbind("click");
			$('.claim').click(function(){
			    loadingScreen("Reclamo il task...", "${baseUrl}/int/images/assign.gif");
			    taskId=$(this).attr("action");
			    $.ajax({
				type: "POST",
				contentType: "application/json; charset=utf-8",
				url: "${baseUrl}/process-engine/runtime/tasks/"+taskId,
				data: JSON.stringify({ "action": "claim", "assignee":"${userDetails.username}"}),
				complete: function(xhr, textStatus) {
					if (xhr.status==200){
						loadingScreen("Operazione terminata", "${baseUrl}/int/images/assign.gif",500);
						window.location.href=window.location.href;
					}else {
						loadingScreen("Errore", "${baseUrl}/int/images/alerta.gif", 3000);
					}
				
				}
			    });
			    return false;
			});
    }
    
    function doTaskListener(){
    	$('.doTask').unbind("click");
			$('.doTask').click(function(){
				taskId=$(this).attr("action");
				$.ajax({
					dataType: "json",
					url: "${baseUrl}/process-engine/form/form-data?taskId="+taskId,
					success: function(data){
						var form = $("<form/>", { action:'/myaction' });
						form.attr('id','taskForm_'+taskId);
						//form.append("<h3>"+tasks[taskId].name+"</h3>");
						for (f=0;f<data.formProperties.length;f++){
							value="";	
							required=data.formProperties[f].required;
							addClass="";
							if (required) addClass="required";
							if (data.formProperties[f].value!=null) value=data.formProperties[f].value
							form.append(data.formProperties[f].name+": <input type='text' class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"' value='"+value+"'/>");
						}
						form.dialog({
							 title: 'Completamento azione',
							 buttons: {
								"Invia": function() {
									var goon=true;
									$('.required').each(function(){
										if ($(this).val()=='') {
										alert('Compilare il campo "'+$(this).attr('label')+'"');
										goon=false;
										}
									});
									if (!goon) return false;
									console.log("passo da qui");
									var properties=new Array();
									var idx=0;
									$('.taskForm_'+taskId).each(function(){
										prop=new Object();
										prop['id']=$(this).attr('name');
										prop['value']=$(this).val();
										properties[idx]=prop;
										idx++;
										
									});
									console.log(properties);
									data=new Object();
									data['taskId']=taskId;
									data['properties']=properties;
									loadingScreen("Eseguo il task...", "${baseUrl}/int/images/process-start-icon.png");
									$.ajax({
										type: "POST",
										contentType: "application/json; charset=utf-8",
										url: "${baseUrl}/process-engine/form/form-data",
										data: JSON.stringify(data),
										success: function(data, textStatus, xhr){
											if (xhr.status==200){
												loadingScreen("Operazione terminata", "${baseUrl}/int/images/task.png",1000);
												form.dialog("close");
												window.location.href=window.location.href;
												
											}else {
												loadingScreen("Errore", "${baseUrl}/int/images/alerta.gif", 3000);
											processDef}
										},
										complete: function(xhr, textStatus) {
											if (xhr.status==200){
												loadingScreen("Operazione terminata", "${baseUrl}/int/images/task.png",1000);
												form.dialog("close");
											}else {
												loadingScreen("Errore", "${baseUrl}/int/images/alerta.gif", 3000);
											}
										
										}
									});
									
								}
							},
							close: function( event, ui ) {
								$('#taskForm_'+taskId).remove();
							}
							});
						form.dialog("open");
						return false;
					}
				});
				return false;
				});
    }


    	//getProcessActions();
    	claimTaskListener();
	doTaskListener();
    	$('#bulkFile-dialog-open').click(function(){
    		$('#bulkFile-dialog').dialog('open');
    	});
    	$('#bulkFile-dialog').dialog({
                height: 300,
                width: 600,
                modal: true,
                autoOpen: false
            });
      	$('#bulkFile-form-submit').click(function(){
            $('#bulkFile').click();
        });
        $('#bulkFile').on("change",function(){
            loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
            var formData=new FormData($('#bulkFile-form')[0]);
            var actionUrl=$('#bulkFile-form').attr("action");
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
                        bootbox.hideAll();
                        var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
                        if(obj.errorMessage.includes("RegexpCheckFailed: ")){
                            var campoLabel="";
                            campoLabel=obj.errorMessage.replace("RegexpCheckFailed: ","");
                            campoLabel=messages[campoLabel];
                            errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
                        }
                        bootbox.alert(errorMessage);
                        //loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });

        });
        
        
        $('#cloneButton').click(function(){
            loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
            var actionUrl="${baseUrl}/app/rest/documents/${el.id}/defaultClone";
            $.ajax({
                type: "GET",
                url: actionUrl,
                success: function(obj){
                    if (obj.result=="OK") {
                        if ($('#container:checked').size()>0) $('#isContainer').show();
                        else $('#isContainer').hide();
                        loadingScreen("Clonazione effettuata", "${baseUrl}/int/images/green_check.jpg",2000);
                        if (obj.redirect){
                            window.location.href=obj.redirect;
                        }
                    }else {
                        loadingScreen("Errore clonazione!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore clonazione!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });

        });
        
        $('.startProcess').click(function(){
            loadingScreen("Avvio processo in corso...", "${baseUrl}/int/images/process-start-icon.png");
            processId=$(this).attr("action");
            $.ajax({
                type: "GET",
                url: "${baseUrl}/app/rest/documents/startProcess/${el.id}/"+processId,
                async:false,
                cache:false,
                success: function(obj){
                    if (obj.result=="OK") {
                        loadingScreen("Processo Avviato", "${baseUrl}/int/images/process-start-icon.png",1000);
                        if (obj.redirect){
                            window.location.href=obj.redirect;
                        }
                    }else {
                        loadingScreen("Errore avvio processo!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore avvio processo!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });
            return;
        });
    
    
    
    
        var default_message_for_dialog = 'You are sure?';

        $("#dialog").dialog({
            modal: true,
            bgiframe: true,
            width: 300,
            height: 200,
            autoOpen: false,
            title: 'Eliminazione'
        });
        $('.delete').click(function(){
            $("#dialog").dialog('option', 'buttons', {
                "Conferma" : function() {
                    $(this).dialog("close");
                    loadingScreen("Eliminazione in corso...", "${baseUrl}/int/images/delete.png");
                    $.ajax({
                        type: "GET",
                        url: "${baseUrl}/app/rest/documents/delete/${el.id}",
                        async:false,
                        cache:false,
                        success: function(obj){
                            if (obj.result=="OK") {
                                loadingScreen("Eliminazione effettuata", "${baseUrl}/int/images/delete.png",1000);
                                if (obj.redirect){
                                    window.location.href=obj.redirect;
                                }
                            }else {
                                loadingScreen("Errore eliminazione!", "${baseUrl}/int/images/alerta.gif", 3000);
                            }
                        },
                        error: function(){
                            loadingScreen("Errore eliminazione!", "${baseUrl}/int/images/alerta.gif", 3000);
                        }
                    });
                },
                "Annulla" : function() {
                    $(this).dialog("close");
                }
            });
            $("#dialog").dialog("open");
            return;
        });

        $('.checkOut').click(function(){
        loadingScreen("CheckOut in corso...", "${baseUrl}/int/images/checkout.png");
        $.ajax({
            type: "GET",
            url: "${baseUrl}/app/rest/documents/checkOut/${el.id}",
            async:false,
            cache:false,
            success: function(obj){
                if (obj.result=="OK") {
                    loadingScreen("CheckOut effettuato", "${baseUrl}/int/images/checkout.png",1000);
                    if (obj.redirect){
                        window.location.href=obj.redirect;
                    }
                }else {
                    loadingScreen("Errore checkOut!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            },
            error: function(){
                loadingScreen("Errore checkOut!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
            });
            return;
        });

        $('.checkIn').click(function(){
            loadingScreen("CheckIn in corso...", "${baseUrl}/int/images/checkin.png");
            $.ajax({
                type: "GET",
                url: "${baseUrl}/app/rest/documents/checkIn/${el.id}",
                async:false,
                cache:false,
                success: function(obj){
                    if (obj.result=="OK") {
                        loadingScreen("CheckIn effettuato", "${baseUrl}/int/images/checkin.png",1000);
                        if (obj.redirect){
                            window.location.href=obj.redirect;
                        }
                    }else {
                        loadingScreen("Errore CheckIn!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore CheckIn!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });
            return;
        });
        $('.addMetadataTemplate').click(function(){
            loadingScreen("Aggiunta template in corso...", "${baseUrl}/int/images/AddMetadata.gif");
            templateId=$(this).attr("id");
            $.ajax({
                type: "GET",
                url: "${baseUrl}/app/rest/documents/addTemplate/${el.id}/"+templateId,
                async:false,
                cache:false,
                success: function(obj){
                    if (obj.result=="OK") {
                        loadingScreen("Template Aggiunto", "${baseUrl}/int/images/AddMetadata.gif",1000);
                        if (obj.redirect){
                            window.location.href=obj.redirect;
                        }
                    }else {
                        loadingScreen("Errore Aggiunta template!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore Aggiunta template!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });
            return;
        });


</@script>
<div id="dialog">Sei sicuro di voler eliminare l'elemento?</div>
<fieldset>
    <legend>Azioni</legend>
    <!--Blocco relativo alle azioni sui processi-->
     <#assign activeProcess=false/>
     <#if model["activeProcesses"]??>
        <#list model["activeProcesses"] as ist>
        <#assign activeProcess=true/>
        </#list>
    </#if>
    <#if !activeProcess>
    <#if model["availableProcesses"]??>
        <#list model["availableProcesses"] as wf>
            <a href="#" action="${wf.key}" class="actions-link startProcess">
                <img src="${baseUrl}/int/images/process-start-icon.png" width=18px/>&nbsp;
                Avvia il processo ${wf.name}
            </a>
            <br/>
        </#list>
    </#if>
    </#if>
    <div id="myTaskActions">
    <#if model['activeTasks']??>
    	<#list model['activeTasks'] as task>
    		<#if task.assignee?? && task.assignee!="">
    			<a href='#' class='actions-link doTask' action='${task.id}'><img src='${baseUrl}/int/images/task.png' width=18px/>${task.name} (${model['activeProcDefs'][task.processDefinitionId].name})</a><br/>
		<#else> 
			<a href="#" class="actions-link claim" action='${task.id}'><img src='${baseUrl}/int/images/assign.gif' width=18px/>Reclama l'operazione di ${task.name} (${model['activeProcDefs'][task.processDefinitionId].name})</a><br/>
		
		</#if>
    	</#list>
    </#if>
    </div>
    
                                       getChildrenByType
    <!-- fine blocco azioni sui processi -->
    
    <#if !el.locked && el.type.checkOutEnabled && userPolicy.canUpdate>
       <a href="#" class="actions-link checkOut"><img src="${baseUrl}/int/images/checkout.png" width=18px/>&nbsp;<@msg "actions.doCheckOut"/></a><br/>
    </#if>
    <#if el.locked && el.type.checkOutEnabled && userPolicy.canUpdate && el.lockedFromUser==userDetails.username>
        <a href="#" class="actions-link checkIn"><img src="${baseUrl}/int/images/checkin.png" width=18px/>&nbsp;<@msg "actions.doCheckIn"/></a><br/>
    <#else>
        <#if el.locked && el.type.checkOutEnabled && userPolicy.canRemoveCheckOut>
            <a href="#" class="actions-link checkIn"><img src="${baseUrl}/int/images/checkin.png" width=18px/>&nbsp;<@msg "actions.forceCheckIn"/></a><br/>
        </#if>
    </#if>
    <#if (userPolicy.canEnableTemplate && !el.locked) || (userPolicy.canEnableTemplate && el.locked && el.lockedFromUser==userDetails.username)>
        <#list elType.associatedTemplates as templates>
            <#assign active=false/>
            <#list el.templates as activeTemplates>
                <#if activeTemplates.id==templates.metadataTemplate.id>
                    <#assign active=true/>
                </#if>
            </#list>
            <#if !active>
                <a href="#" id="${templates.metadataTemplate.id}" class="actions-link addMetadataTemplate"><img src="${baseUrl}/int/images/AddMetadata.gif" width=18px/>&nbsp;<@msg "actions.addTemplate"/> <@msg "template.${templates.metadataTemplate.name}"/></a><br/>
            </#if>
        </#list>
    </#if>
    
    <#if userPolicy.canDelete>
        <a href="#" class="actions-link delete"><img src="${baseUrl}/int/images/delete.png" width=18px/>&nbsp;<@msg "actions.deleteElement"/></a><br/>
    </#if>
    <input class="submitButton round-button blue cloneButton" type="button" value="Clona l'elemento" id="cloneButton" name="cloneButton"/><br/>
	<#--GC 22/01/2015 Aggiunto bottone per inserimento nuova voce dizionario-->
			<#assign figli=el.getChildren() />
			<#if figli?size gt 0 >
				<#assign figlio=figli[0].getType().getId() />
					<input class="submitButton round-button blue" type="button" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${figlio}';" value="Aggiungi voce dizionario">
			</#if>
		<br>
    <input class="submitButton round-button blue" type="button" value="Caricamento da file Excel" id="bulkFile-dialog-open" name="bulkFile-dialog-open"/>
<div id="bulkFile-dialog" title="Inserimento da file Excel">
<form id="bulkFile-form" method="POST" action="${baseUrl}/app/rest/documents/bulkUpload/${el.id}" enctype="multipart/form-data">
	<select id="destType"name="destType">
            <option>Selezionare il tipo di documento bulk</option>
            <#if model['getCreatableElementTypes']??>
            <#list model['getCreatableElementTypes'] as docType>
                <option value="${docType.id}">${docType.typeId}</option>
            </#list>
            </#if>
        </select>
	<div class="field-component">
    	<input type="file" class="new-version" name="file" id="bulkFile"/>
    	<input class="submitButton round-button blue" type="button" value="Carica file Excel" id="bulkFile-form-submit" name="bulkFile-form-submit"/>
	</div>
	
</form>
</div>
</fieldset>
