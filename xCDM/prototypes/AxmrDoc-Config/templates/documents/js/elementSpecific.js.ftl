  <script>
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
    
    function valueOfField(idField){
    	field=$('#'+idField);
    	 if (field.attr('istokeninput')=='true'){
			value=field.tokenInput("get");
			if (value.length>0)
			return value[0].id;
			else return "";
			}
    	if (field.attr('type')=='radio'){
		return $('#'+idField+':checked').attr('title');
		}else if (field.prop('tagName')=='SELECT'){
		    return field.find('option:selected').val();
		}else {
			return field.val();
		}	
}

    function saveUpdateField(idField){
        loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        form=document.forms[idField];
        var formData=new FormData(form);
        var actionUrl=$(form).attr("action")+"${el.id}";
        field=$(form).find('#'+idField);
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
                    $(".warning").show();
                    if (field.attr('istokeninput')=='true'){
			value=field.tokenInput("get");
			if (fieldTypes[idField]=="ELEMENT_LINK") 
			$('#'+idField+'_value').html("<a href='${baseUrl}/app/documents/detail/"+value[0].id+"'>"+value[0].name+"</a>");
			else $('#'+idField+'_value').html(value[0].name);
			}else if (field.attr('type')=='radio'){
			    $('#'+idField+'_value').html($('#'+idField+':checked').attr('title'));
			}else if (field.prop('tagName')=='SELECT'){
			    $('#'+idField+'_value').html(field.find('option:selected').text());
			}else {
			$('#'+idField+'_value').html(field.val());
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

    $(document).ready(function(){
     $('#t').change(function(){
	    	$('#t-form').submit();
	    });
    $('#metadataTemplate-tabs').tabs();
    	$('.allInTemplate').find("select").each(function(){
        	registerEventsForField(this);
        });
         $('.allInTemplate').find("input").each(function(){
        	registerEventsForField(this);
        });
         $('.allInTemplate').find("radio").each(function(){
        	registerEventsForField(this);
        });
        $(".templateForm").click(function (){
        	formName=$(this).attr('id').replace("salvaForm-", "");
        	$(".warning").hide();
        	loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        	form=document.forms[formName];
		var formData=new FormData(form);
		var actionUrl=$(form).attr("action")+"${el.id}";
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
			}else {
			    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
			}
		    },
		    error: function(){
			loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
		    }
		});
        });
    	$('#metadataTemplate-tabs').tabs();
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
        $('.cloneButton').click(function(){
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
        loadTasks();
        
        
    });
    
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
						$('#task-Actions').append('<input class="submitButton round-button blue" type="button" onclick="executeConfirmTask('+task.id+')" value="'+task.name+'"><br/>');						
					}
					if (task.type=="Form"){
						gtasks[task.id]=task;
						console.log("Task di tipo Confirm");
						$('#task-Actions').append('<input class="submitButton round-button blue" type="button" onclick="executeFormTask('+task.id+')" value="'+task.name+'"><br/>');						
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
				url: "${baseUrl}/process-engine/form/form-data",
				data: JSON.stringify(data),
				success: function(data, textStatus, xhr){
					if (xhr.status==200){
						window.location.href=window.location.href;
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
								title=gtasks[taskId].name; 
								width=400;
								height=400;
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
														window.location.href=window.location.href;
														
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
					}
				});
	}
	
	</script>
