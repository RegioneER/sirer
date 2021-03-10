<@script>
	var profiloCTC='';
	var globalTasks=new Object();
	var gtasks=new Object();

	function loadTasks(){
		globalTasks=new Object();
		$.ajax({
			type: "GET",
			url: "${baseUrl}/app/rest/documents/tasks/${el.id}",
			dataType: "json",
			success: function(tasks){
				
				for (t=0;t<tasks.length;t++){
						if (!globalTasks[tasks[t].processKey]){
							globalTasks[tasks[t].processKey]=new Object();
						}
						if (!globalTasks[tasks[t].processKey].instances){
							globalTasks[tasks[t].processKey].instances=new Object();
						}
						if (!globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId]){
							globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId]=new Array();
						}
						globalTasks[tasks[t].processKey].processName=tasks[t].processName;
						
						globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId][globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId].length]=tasks[t];	
					
				}
				
				processTask();
			}
		});

		<#if !(budgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")?? && budgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")?size>0 && budgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")[0]=="1") >
		$.ajax({
				type: "GET",
				url: "${baseUrl}/app/rest/documents/tasks/${budgetStudio.id}",
				dataType: "json",
				success: function(tasks){

					for (t=0;t<tasks.length;t++){
						if (!globalTasks[tasks[t].processKey]){
							globalTasks[tasks[t].processKey]=new Object();
						}
						if (!globalTasks[tasks[t].processKey].instances){
							globalTasks[tasks[t].processKey].instances=new Object();
						}
						if (!globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId]){
							globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId]=new Array();
						}
						globalTasks[tasks[t].processKey].processName=tasks[t].processName;
						globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId][globalTasks[tasks[t].processKey].instances[tasks[t].processInstanceId].length]=tasks[t];
					}
					processTask();
				}
		});
		</#if>
	}
	
	function processTask(){
		$('#task-Actions').html("");
		gtasks=new Object();
		for(var pKey in globalTasks) {
			console.log(pKey+" - "+globalTasks[pKey].processName);
			for (var pInst in globalTasks[pKey].instances){
				console.log(pInst);
				tasks=globalTasks[pKey].instances[pInst];
				for (tt=0;tt<tasks.length;tt++){
					task=tasks[tt];
					if (task.type=="Alert"){
						alert(task.processVariables.message);
						data=new Object();
						data['taskId']=task.id;
						$.ajax({
								type: "POST",
								contentType: "application/json; charset=utf-8",
								url: "${baseUrl}/process-engine/form/form-data",
								data: JSON.stringify(data),
								success: function(data, textStatus, xhr){
									if (xhr.status==200){
										loadTasks();
									}else alert("Errore!!!");
							}
						});
					}
					if (task.type=="Confirm"){
						gtasks[task.id]=task;
						console.log("Task di tipo Confirm");
						//SIRER-18 AL MOMENTO NASCONDO I TASK SU APPROVAZIONE PREZZI E BUDGET CLINICO
						//if(task.name!="Considera budget dei prezzi come finale" && task.name!="Approva budget clinico"){
						//SIRER-42 ripristino Considera budget dei prezzi come finale
						if(task.name!="Approva budget clinico"){
							$('#task-Actions').append('<button class="btn btn-primary"  onclick="executeConfirmTask('+task.id+');">'+task.name+'</button>');
						}
					}
					if (task.type=="Form"){
						gtasks[task.id]=task;
						console.log("Task di tipo Confirm");
						//SIRER-18 AL MOMENTO NASCONDO I TASK SU APPROVAZIONE PREZZI E BUDGET CLINICO
						//if(task.name!="Considera budget dei prezzi come finale" && task.name!="Approva budget clinico"){
						//SIRER-42 ripristino Considera budget dei prezzi come finale
						if(task.name!="Approva budget clinico"){
							$('#task-Actions').append('<button class="btn btn-primary"  onclick="executeFormTask('+task.id+')">'+task.name+'</button>');
						}
					}
				}
			}
		}
	}
	
	function executeConfirmTask(taskId){	
		if (confirm("Sei sicuro di voler procedere?\nAssicurarsi di aver salvato le ultime modifiche prima di procedere.")){
			var data=new Object();
			data['taskId']=taskId;
			$.ajax({
				type: "POST",
				contentType: "application/json; charset=utf-8",
				url: "${baseUrl}/process-engine/form/form-data",
				data: JSON.stringify(data),
				success: function(data, textStatus, xhr){
					if (xhr.status==200){
						window.location.reload(true);
					}else if(gtasks[taskId].taskVariables && gtasks[taskId].taskVariables.message){
						alert(gtasks[taskId].taskVariables.message);
					}
					else alert("Errore!!!");
				}
			}).fail(function( xhr){
			
				if (xhr.status==500){
					if(gtasks[taskId].taskVariables && gtasks[taskId].taskVariables.message){
						alert(gtasks[taskId].taskVariables.message);
					}
					else alert("Errore!!!");
				}else alert("Errore sul canale di comunicazione. Provare piu' tardi.");
			});	
		}
	}
	
	function executeFormTask(taskId){	
    		$.ajax({
					dataType: "json",
					url: "${baseUrl}/process-engine/runtime/tasks/"+taskId+"/variables",
					success: function(variables){
					
		    			$.ajax({
							dataType: "json",
							url: "${baseUrl}/process-engine/form/form-data?taskId="+taskId,
							success: function(data){
								console.log(variables);
								var form = $("<form/>", { action:'/myaction' });
								form.attr('id','taskForm_'+taskId);
								for (v=0;v<variables.length;v++){
									console.log(v+" - "+variables[v]);
									if (variables[v].name=='message' && variables[v].value!=null){
										form.append("<p><b>"+variables[v].value+"</b></p>");
									}
								}
								for (f=0;f<data.formProperties.length;f++){
									value="";	
									required=data.formProperties[f].required;
									addClass="";
									if (required) addClass="required";
									if (data.formProperties[f].value!=null) value=data.formProperties[f].value
									if (data.formProperties[f].type=="string"){
									
										if(data.formProperties[f].id.indexOf("note")==0){
											form.append(data.formProperties[f].name+": <br/><textarea class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"'> "+value+"</textarea><br/>");
										}
										else{
											form.append(data.formProperties[f].name+": <input type='text' class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"' value='"+value+"'/><br/>");
										}
								
									}
									if (data.formProperties[f].type=="enum"){
									    options="";
									    for (ev=0;ev<data.formProperties[f].enumValues.length;ev++){
									    	console.log(data.formProperties[f].enumValues[ev].id);
									    	console.log(data.formProperties[f].enumValues[ev].name);
									    	options+='<option value="'+data.formProperties[f].enumValues[ev].id+'">'+data.formProperties[f].enumValues[ev].name+'</option>';
									    }
									    form.append(data.formProperties[f].name+": <select class='taskForm_"+taskId+" "+addClass+"' name='"+data.formProperties[f].id+"'>"+options+"</select><br/>");
									}
									
									form.append('<br/>');
									
								}
								title=gtasks[taskId].name; 
								width=400;
								height=400;
								form.dialog({
									 title: title,
									 width: width,
									 height: height,
									 buttons: [{
										text:"Invia",
										click: function() {
											var goon=true;
											$('.required').each(function(){
												if ($(this).val()=='') {
												alert('Compilare il campo "'+$(this).attr('label')+'"');
												goon=false;
												}
											});
											if (!goon) return false;
											var properties=new Array();
											var idx=0;
											$('.taskForm_'+taskId).each(function(){
												prop=new Object();
												prop['id']=$(this).attr('name');
												prop['value']=$(this).val();
												properties[idx]=prop;
												idx++;
												
											});
											data=new Object();
											data['taskId']=taskId;
											data['properties']=properties;
											$.ajax({
												type: "POST",
												contentType: "application/json; charset=utf-8",
												url: "${baseUrl}/process-engine/form/form-data",
												data: JSON.stringify(data),
												success: function(data, textStatus, xhr){
													if (xhr.status==200){
														form.dialog("close");
														window.location.reload(true);
														
													}else {
														alert("Errore");
														form.dialog("close");
													}
												},
												complete: function(xhr, textStatus) {
													if (xhr.status==200){
														loadingScreen("Operazione effettuata con successo", "${baseUrl}/int/images/task.png",1000);
														form.dialog("close");
													}else {
														alert("Errore");
														form.dialog("close");
													}
												
												}
											});
											
										},
										"class" : "btn btn-primary btn-xs"
									},
									
									
									{
										text:"Annulla",
										click: function( event, ui ) {
											$('#taskForm_'+taskId).remove();
											
										},
										"class" : "btn  btn-xs"
									}]
									});
									
								form.dialog("open");
								return false;
							}
						});
					}
				});
	}
    
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
						loadingScreen("Operazione effettuata con successo", "${baseUrl}/int/images/assign.gif",500);
						window.location.reload(true);
					}else {
						loadingScreen("Errore", "${baseUrl}/int/images/alerta.gif", 3000);
					}
				
				}
			    });
			    return false;
			});
    }
    
    function doTask(taskId, forceSubmit){
    	console.log("doTask - "+forceSubmit);
    		$.ajax({
					dataType: "json",
					url: "${baseUrl}/process-engine/runtime/tasks/"+taskId+"/variables",
					success: function(variables){
					
		    			$.ajax({
							dataType: "json",
							url: "${baseUrl}/process-engine/form/form-data?taskId="+taskId,
							success: function(data){
								console.log(variables);
								var form = $("<form/>", { action:'/myaction' });
								form.attr('id','taskForm_'+taskId);
								for (v=0;v<variables.length;v++){
									console.log(v+" - "+variables[v]);
									if (variables[v].name=='message' && variables[v].value!=null){
										form.append("<b>"+variables[v].value+"</b>");
									}
								}
								for (f=0;f<data.formProperties.length;f++){
									value="";	
									required=data.formProperties[f].required;
									addClass="";
									if (required) addClass="required";
									if (data.formProperties[f].value!=null) value=data.formProperties[f].value
									if (data.formProperties[f].type=="string"){
									
										if(data.formProperties[f].id.indexOf("note")==0){
											form.append(data.formProperties[f].name+": <br/><textarea class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"'> "+value+"</textarea><br/>");
										}
										else{
											form.append(data.formProperties[f].name+": <input type='text' class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"' value='"+value+"'/><br/>");
										}
								
									}
									if (data.formProperties[f].type=="enum"){
									    options="";
									    for (ev=0;ev<data.formProperties[f].enumValues.length;ev++){
									    	console.log(data.formProperties[f].enumValues[ev].id);
									    	console.log(data.formProperties[f].enumValues[ev].name);
									    	options+='<option value="'+data.formProperties[f].enumValues[ev].id+'">'+data.formProperties[f].enumValues[ev].name+'</option>';
									    }
									    form.append(data.formProperties[f].name+": <select class='taskForm_"+taskId+" "+addClass+"' name='"+data.formProperties[f].id+"'>"+options+"</select><br/>");
									}
									
									form.append('<br/>');
									
								}
								var title="Conferma operazione";
								
								width=300;
								height=250;
								
								if (data.formProperties.length>0) {
								
									title="Compila la form"; 
									width=400;
									height=400;
								
								}
								
								form.dialog({
									 title: title,
									 width: width,
									 height: height,
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
											data=new Object();
											data['taskId']=taskId;
											data['properties']=properties;
											$.ajax({
												type: "POST",
												contentType: "application/json; charset=utf-8",
												url: "${baseUrl}/process-engine/form/form-data",
												data: JSON.stringify(data),
												success: function(data, textStatus, xhr){
													if (xhr.status==200){
														form.dialog("close");
														window.location.reload(true);
														
													}else {
														loadingScreen("Errore", "${baseUrl}/int/images/alerta.gif", 3000);
													processDef}
												},
												complete: function(xhr, textStatus) {
													if (xhr.status==200){
														loadingScreen("Operazione effettuata con successo", "${baseUrl}/int/images/task.png",1000);
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
										if (forceSubmit){
											var properties=new Array();
											var idx=0;
											$('.taskForm_'+taskId).each(function(){
												prop=new Object();
												prop['id']=$(this).attr('name');
												prop['value']=$(this).val();
												properties[idx]=prop;
												idx++;
												
											});
											data=new Object();
											data['taskId']=taskId;
											data['properties']=properties;
											$.ajax({
												type: "POST",
												contentType: "application/json; charset=utf-8",
												url: "${baseUrl}/process-engine/form/form-data",
												data: JSON.stringify(data),
												success: function(data, textStatus, xhr){
													if (xhr.status==200){
														loadingScreen("Operazione effettuata con successo", "${baseUrl}/int/images/task.png",1000);
														window.location.reload(true);
													}else {
														loadingScreen("Errore", "${baseUrl}/int/images/alerta.gif", 3000);
													processDef}
												},
												complete: function(xhr, textStatus) {
													if (xhr.status==200){
														loadingScreen("Operazione effettuata con successo", "${baseUrl}/int/images/task.png",1000);
													}else {
														loadingScreen("Errore", "${baseUrl}/int/images/alerta.gif", 3000);
													}
												
												}
											});
										}
									}
									});
								form.dialog("open");
								return false;
							}
						});
					}
				});
    }
    
    function doTaskListener(){
    	$('.doTask').unbind("click");
			$('.doTask').click(function(){
				taskId=$(this).attr("action");
				doTask(taskId, false);
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
                        $.ajax({
                        	type: "GET",
                        	url: "${baseUrl}/process-engine/runtime/tasks?processInstanceId="+obj.ret+"&involvedUser=${userDetails.username}",
                        	success: function(taskInfo){
                        		console.log(taskInfo);
                        		doTask(taskInfo.data[0].id);                        		
                        	}
                        });
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

   	 <#assign activeProcess=false/>
     <#if model["activeProcesses"]??>
        <#list model["activeProcesses"] as ist>
        <#assign activeProcess=true/>
        </#list>
    </#if>
    <#if !activeProcess>
    <#if model["availableProcesses"]??>
        <#list model["availableProcesses"] as wf>
        	<#list el.type.associatedWorkflows as p>
        		<#if !p.startOnCreate && p.enabled && wf.key=p.processKey>
        			<#assign alreadyTerminated=false/>
        			<#if model['terminatedProcesses']??>
						<#list model['terminatedProcesses'] as tpInst>
							<#if tpInst.getProcessDefinitionId()?split(":")[0]=wf.key>
							<#assign alreadyTerminated=true/>
							</#if>
						</#list>
					</#if>
					<#if !alreadyTerminated>
					<input id="startProcess" action="${wf.key}" class="submitButton round-button blue startProcess" type="button" value="${wf.name}">
    		        
		            </#if>
        		</#if>
        	</#list>
            
        </#list>
    </#if>
    </#if>
    
    <div id="task-Actions"> </div>
