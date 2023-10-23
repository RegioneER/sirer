<@script>
  	var formSubmitButtonStd=function(){
  		formName=$(this).attr('id').replace("salvaForm-", "");
  		formSubmitStd(formName);
  	};
  	var formSubmitStd=function(formName){
  
        	var goon=true;
			if (eval("typeof "+formName+"Checks == 'function'")){
				eval("goon="+formName+"Checks()");
			}
			if (!goon) return false;
        	$(".warning").hide();
        	loadingScreen("Salvataggio in corso...", "loading");
        	
        	form=document.forms[formName];
		var formData=new FormData(form);
		var actionUrl=$(form).attr("action")+"${el.id?c}";
		
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
				loadingScreen("Salvataggio effettuato", "green_check");
			}else {
				loadingScreen("Errore salvataggio!", "alerta");
			}
		    },
		    error: function(){
				loadingScreen("Errore salvataggio!", "alerta");
		    }
		});
        };
  	

    	$('#t').change(function(){
	    	$('#t-form').submit();
	    });
    	//$('#metadataTemplate-tabs').tabs();
    	$('#metadataTemplate-tabs a[id^=ui-id-]').on('click',function(){
			var hash=this.href;
			hash=hash.replace(/^[^#]*/,'');
			window.location.hash=hash;
		});
    	$('.allInTemplate').find("select").each(function(){
        	registerEventsForField(this);
        });
         $('.allInTemplate').find("input").each(function(){
        	registerEventsForField(this);
        });
         $('.allInTemplate').find("radio").each(function(){
        	registerEventsForField(this);
        });
        $(".templateForm").click(formSubmitButtonStd);
    	//$('#metadataTemplate-tabs').tabs();
        <#if editable>
            $('.right-corner').hide();
            $('.save-buttons').button({
            icons: {
                primary: "ui-icon-check"
            },
            text: false});
            $('.cancel-buttons').button({
                icons: {
                primary: "ui-icon-cancel"
                },
            text: false});
            $('.cancel-buttons').click(function(){
                $('.view-mode').show();
                $('.edit-mode').hide();
            });

        $('.view-editable-field').mouseover(function(){
            onMouseOverEditable(this);
        });
        $('.view-editable-field').mouseout(function(){
            onMouseOutEditable(this);
        });
        $('.save-buttons').click(function(){
            idField=$(this).val();
           <#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	    		<#list el.elementTemplates as elementTemplate>
	    			<#if elementTemplate.enabled>
	    				<#list elementTemplate.metadataTemplate.fields as field>
	    					<#if field.mandatory> 
	    					<#assign label=getLabel(elementTemplate.metadataTemplate.name+"."+field.name)/>
	    					if (idField=='${elementTemplate.metadataTemplate.name}_${field.name}' && valueOfField(idField)==''){
	    						alert("Il campo ${label} deve essere compilato");
	    						return false;
	    					}
	    					</#if>
	    				</#list> 
	    			</#if>
	    		</#list>
	  		</#if>
            saveUpdateField(idField);
            $('#'+idField+"_value_view").show();
            $('#form-'+idField).hide();
        });
            $('.cancel-buttons').click(function(){
                $('.single-field-form').hide();
                $('.data-view-mode').show();
            });

            $('.view-editable-field').click(function(){
                idField=$(this).attr("id");
                idField=idField.replace("_value_view","");
                $('.single-field-form').hide();
                $('.data-view-mode').show();
                $('#'+idField+"_value_view").hide();
                $('#form-'+idField).show();
                form=document.forms[idField];
                field=$(form).find('#'+idField);
                origValue=field.val();
        });
        </#if>
        
        $('.delete').click(function(){
        	bootbox.confirm("Are you sure?", function(result) {
				if (result){
					loadingScreen("Eliminazione in corso...", "${baseUrl}/int/images/delete.png");
                    $.ajax({
                        type: "GET",
                        url: "${baseUrl}/app/rest/documents/delete/${el.id?c}",
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
				}	
			}); 
		});
            

        $('.checkOut').click(function(){
        loadingScreen("CheckOut in corso...", "${baseUrl}/int/images/checkout.png");
        $.ajax({
            type: "GET",
            url: "${baseUrl}/app/rest/documents/checkOut/${el.id?c}",
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
                url: "${baseUrl}/app/rest/documents/checkIn/${el.id?c}",
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
                url: "${baseUrl}/app/rest/documents/addTemplate/${el.id?c}/"+templateId,
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
        $('.cloneButton').click(function(){
            loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
            var actionUrl="${baseUrl}/app/rest/documents/${el.id?c}/defaultClone";
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
        var bbox=null;
        $('.startProcess').click(function(){
            bootbox.dialog({
				message: "<i class='fa fa-spinner fa-spin'></i> Avvio processo in corso ..."
			});
            processId=$(this).attr("action");
            $.ajax({
                type: "GET",
                url: "${baseUrl}/app/rest/documents/startProcess/${el.id?c}/"+processId,
                async:false,
                cache:false,
                success: function(obj){
                    if (obj.result=="OK") {
                    	bootbox.hideAll();
                        bootbox.dialog({
							message: "Processo avviato"
						});
                        $.ajax({
                        	type: "GET",
                        	url: "${baseUrl}/process-engine/runtime/tasks?processInstanceId="+obj.ret+"&involvedUser=${userDetails.username}",
                        	success: function(){
                        		window.location.href='${baseUrl}/app/documents/detail/${el.id}';              		
                        	}
                        });
                    }else {
                    	bootbox.hideAll();
                    	bootbox.alert("Errore avvio processo!", function() {
                    	});
                    }
                },
                error: function(){
                    bootbox.hideAll();
                    	bootbox.alert("Errore avvio processo!", function() {
                    	});
                }
            });
            return;
        });
        

  
  
  function DateFmt(fstr) {
        this.formatString = fstr

        var mthNames = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
        var dayNames = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
        var zeroPad = function(number) {
            return ("0"+number).substr(-2,2);
        }

        var twoDigit= function(string){
            return (string+'').substr(2,2);
        }

        var dateMarkers = {
            d:['getDate',function(v) { return zeroPad(v)}],
            m:['getMonth',function(v) { return zeroPad(v+1)}],
            n:['getMonth',function(v) { return mthNames[v]; }],
            w:['getDay',function(v) { return dayNames[v]; }],
            y:['getFullYear',function(v) { return twoDigit(v)}],
            H:['getHours',function(v) { return zeroPad(v)}],
            M:['getMinutes',function(v) { return zeroPad(v)}],
            S:['getSeconds',function(v) { return zeroPad(v)}],
            i:['toISOString']
        };

        this.format = function(date) {
            var dateTxt = this.formatString.replace(/%(.)/g, function(m, p) {
                var rv = date[(dateMarkers[p])[0]]()

                if ( dateMarkers[p][1] != null ) rv = dateMarkers[p][1](rv)

                return rv

            });

            return dateTxt
        }

    }
    
    function addAuditTable(idField){
    	$('#informations-'+idField).prepend("<img class='audit_img audit' id='audit_"+idField+"' src='${baseUrl}/int/images/history.png'/>");
    	$('#audit_'+idField).click(function(){
    		$( "#auditTable_"+idField ).dialog("open");
    	});
    	
    }
    


    function saveUpdateField(idField){
        loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        form=document.forms[idField];
        var formData=new FormData(form);
        var actionUrl=$(form).attr("action")+"${el.id?c}";
        field=$(form).find('#'+idField);
        if($(form).find('#'+idField+'-select').size()>0){
        	field=$(form).find('#'+idField+'-select');
        }
        var newValue=field.val();
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
                	
                    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",1000);
                    $(".warning").hide();
                    console.log(field);
                    if (field.attr('istokeninput')=='true'){
						value=field.tokenInput("get");
						if (fieldTypes[idField]=="ELEMENT_LINK")  $('#'+idField+'_value').html("<a href='${baseUrl}/app/documents/detail/"+value[0].id+"'>"+value[0].name+"</a>");
						else $('#'+idField+'_value').html(value[0].name);
					}else if (field.attr('type')=='radio'){
			    		$('#'+idField+'_value').html($('#'+idField+':checked').attr('title'));
					}else if (field.prop('tagName')=='SELECT'){
			    		$('#'+idField+'_value').html(field.find('option:selected').text().split('###')[0]);
					}else {
						console.log(field.attr('id'));
						if (idField=='tipologiaContratto_TipoContratto') 	$('#'+idField+'_value').html(field.val().split("###")[1]);
						else	$('#'+idField+'_value').html(field.val());
	            }
                    if ($('#'+idField+'_audit')){
                    	auditTBody=$('#'+idField+'-audit-table');
	                    fmt = new DateFmt("%d/%m/%y %H.%M");
	                    auditTBody.append(' <tr><td>${userDetails.username}</td><td>'+fmt.format(new Date())+'</td><td>update</td><td>'+origValue+'</td><td>'+newValue+'</td></tr>');
					}
                }else {
                	if (obj.errorMessage!=null) loadingScreen(obj.errorMessage, "${baseUrl}/int/images/alerta.gif", 3000);
                	else loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                	$(".warning").show();
                }
            },
            error: function(){
                loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                $(".warning").show();
            }
        });
        $('#'+idField).show();
        $('#form-'+idField).hide();
    }

    function onMouseOverEditable(obj){
        $(obj).addClass("editable-field");
        $(obj).find('.right-corner').show();

    }

    function onMouseOutEditable(obj){
        $(obj).removeClass("editable-field");
        $(obj).find('.right-corner').hide();
    }

	var origValue=null;
	
    function registerEventsForField(field){
    	    $(this).change(function(){
	    	$(".warning").html("Attenzione, le modifiche effettuate saranno valide solo dopo aver salvato i dati");
		$(".warning").show();
	    }); 
	    
    }

    
    var globalTasks=new Object();
	var gtasks=new Object();

	function loadTasks(){
		globalTasks=new Object();
		$.ajax({
			type: "GET",
			url: "${baseUrl}/app/rest/documents/tasks/${el.id?c}",
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
	
	}
	
	function processTask(){
		if (!document.getElementById('task-Actions')) return;
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
						$('#task-Actions').append(' <a class="btn btn-success btn-xs" href="#" onclick="executeConfirmTask('+task.id+');"> <i class="fa fa-play"></i> '+task.name+'</button> ');						
					}
					if (task.type=="Form"){
						gtasks[task.id]=task;
						console.log("Task di tipo Form");
						$('#task-Actions').append(' <a class="btn btn-success btn-xs" href="#" onclick="executeFormTask('+task.id+');return false;"><i class="fa fa-pencil"></i> '+task.name+'</a> ');						
					}
				}
			}
		}
	}
	
	function executeConfirmTask(taskId){	
		if (confirm("Sei sicuro di voler procedere?")){
			data=new Object();
			data['taskId']=taskId;
			$.ajax({
				type: "POST",
				contentType: "application/json; charset=utf-8",
				url: "${baseUrl}/app/rest/documents/submitTask/"+taskId,
				success: function(data, textStatus, xhr){
					if (xhr.status==200){
						window.location.reload(true);
					}else alert("Errore!!!");
				}
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
								var form = $("<form id='taskForm_"+taskId+"' name='taskForm_"+taskId+"'/>", { action:'/myaction' });
								form.attr('id','taskForm_'+taskId);
								for (v=0;v<variables.length;v++){
									console.log(v+" - "+variables[v]);									
								}
								for (f=0;f<data.formProperties.length;f++){
									value="";	
									required=data.formProperties[f].required;
									addClass="";
									if (required) addClass="required ";
									if (data.formProperties[f].value!=null) value=data.formProperties[f].value
									if (data.formProperties[f].type=="string"){
									
										if(data.formProperties[f].id.indexOf("note")==0){
											form.append(data.formProperties[f].name+": <br/><textarea class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"'>"+value+"</textarea><br/>");
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
									if (data.formProperties[f].type=="date"){
									
										  addClass+= "datePicker";
											form.append(data.formProperties[f].name+": <input type='text' class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"' value='"+value+"'/><br/>");
									}
									form.append('<br/>');
								}
								title=gtasks[taskId].name; 
								width=400;
								height=400;
								$('#task-form .modal-body').html(form);
								var cancelButton = $("<button>");
								cancelButton.addClass("btn");
								cancelButton.addClass("btn-sm");
								var cancelButtonText='<i class="fa fa-undo"></i> Annulla';
								cancelButton.html(cancelButtonText);
								cancelButton.click(function(){
									$('#task-form').modal("hide");	
								});
								var submitButton = $("<button>");
								submitButton.addClass("btn");
								submitButton.addClass("btn-sm");
								submitButton.addClass("btn-info");
								var submitText='<i class="fa fa-play"></i> Invia';
								submitButton.html(submitText);
								submitButton.click(function(){
												bootbox.dialog({
													message: "<i class='fa fa-spinner fa-spin'></i> Invio task in corso ..."
												});
													var goon=true;
													$('.required').each(function(){
														if ($(this).val()=='') {
														bootbox.hideAll();
														bootbox.alert('Compilare il campo '+$(this).attr('label'));
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
													taskForm=document.forms["taskForm_"+taskId];
													var formData=new FormData(taskForm);
													$.ajax({
														type: "POST",
														url: "${baseUrl}/app/rest/documents/submitTask/"+taskId,
														data: formData,
														contentType:false,
											            processData:false,
											            async:false,
											            cache:false,
														 success: function(obj){
														 	console.log(obj);
		                    								if (obj.result=="OK") {
		                    								    bootbox.hideAll();
		                    									bootbox.dialog({
																	message: "Task completato con successo"
																});
		                    									$('#task-form').modal("hide");
																window.location.reload(true);
															}else {
																bootbox.hideAll();
		                    									bootbox.alert({
																	message: "Errore nel completamento del Task"
																});
																$('#task-form').modal("hide");
														
		                    								}
		                    							}
													});
								});
								$('#task-form .modal-footer').html(cancelButton);
								$('#task-form .modal-footer').append(submitButton);
								$('#task-form').modal();
								$('.datePicker').datepicker({autoclose:true,  format: 'dd/mm/yyyy' });
								return false;
							}
						});
					}
				});
	}
	$('#bulkFile-dialog-open').click(function(){
		$('#bulkFile-form-dialog').modal();
	});
	
	
	$('#bulkFile-form-submit').click(function(){
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
                        loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });

        });
	
	</@script>

<div class="widget-box ">
	<div class="widget-header">
		<h4 class="lighter smaller">
		<i class="icon-cogs blue"></i> Azioni
		</h4>
	</div>
	<div class="widget-body">
		<div class="widget-main">
			<#assign activeProcess=false/>
		     <#if model["activeProcesses"]??>
		        <#list model["activeProcesses"] as ist>
		        <#assign activeProcess=true/>
		        </#list>
		    </#if>
		    <#if !activeProcess>
		    <#if model["availableProcesses"]??>
		        <#list model["availableProcesses"] as wf>
		            <a href="#" class="btn btn-xs btn-success startProcess" action="${wf.key}">
		                <i class="fa fa-play"></i> 
		                Avvia il processo ${wf.name}
		            </a>
		            <br/>
		        </#list>
		    </#if>
		    </#if>	
		    <div id="task-Actions"> </div>
		    <#if !el.locked && el.type.checkOutEnabled && userPolicy.canUpdate>
		       <a href="#" class="btn btn-xs btn-warning checkOut"><i class="fa fa-sign-out"></i> <@msg "actions.doCheckOut"/></a><br/>
		    </#if>
		        
		    <#if el.locked && el.type.checkOutEnabled && userPolicy.canUpdate && el.lockedFromUser==userDetails.username>
		    	<a href="#" class="btn btn-xs btn-warning checkIn"><i class="fa fa-sign-in"></i> <@msg "actions.doCheckIn"/></a><br/>
		    <#else>
		        <#if el.locked && el.type.checkOutEnabled && userPolicy.canRemoveCheckOut>
		   			<a href="#" class="btn btn-xs btn-warning checkIn"><i class="fa fa-unlock"></i> <@msg "actions.forceCheckIn"/></a><br/>
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
		                <a href="#" id="${templates.metadataTemplate.id}" class="btn btn-xs btn-success addMetadataTemplate"><i class="fa fa-tags"></i> <@msg "actions.addTemplate"/> <@msg "template.${templates.metadataTemplate.name}"/></a><br/>
		            </#if>
		        </#list>
		    </#if>
		    <#if userPolicy.canDelete>
		        <a href="#" class="btn btn-xs btn-alert delete"><i class="fa fa-trash"></i> <@msg "actions.deleteElement"/></a><br/>
		    </#if>
		    <a href="#" class="btn btn-xs submitButton cloneButton" type="button" id="cloneButton" name="cloneButton">
			<i class="fa fa-copy"></i> Clona l'elemento
			</a><br/>
			<a href="#" class="btn btn-xs btn-info submitButton round-button blue" id="bulkFile-dialog-open" name="bulkFile-dialog-open">
			<i class="fa fa-file-excel-o"></i> 
			Caricamento da file Excel
			</a>

	</div>
</div>
<@modalbox "task-form" "Task Form" ""/>
<#assign modalBody>
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
</#assign>

<@modalbox "bulkFile-form-dialog" "Carica da File Excel" modalBody/>

