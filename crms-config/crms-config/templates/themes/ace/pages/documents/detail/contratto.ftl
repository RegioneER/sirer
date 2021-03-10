<@script>
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
									
									//GC 20-12-13// Commento perche' printa il message nella task-form (chissa' qual'era la ratio...)
									//if (variables[v].name=='message' && variables[v].value!=null){
									//	form.append("<b>"+variables[v].value+"</b>");
									//}
									
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
										else if(data.formProperties[f].id.indexOf("Doc1")==0 || data.formProperties[f].id.indexOf("Doc2")==0 || data.formProperties[f].id.indexOf("Doc3")==0 || data.formProperties[f].id.indexOf("Doc4")==0){
											form.append(data.formProperties[f].name+": <br/><select class='taskForm_"+taskId+" "+addClass+"' label='"+data.formProperties[f].name+"' name='"+data.formProperties[f].id+"'><option></option></select><br/>");
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
								width=800;
								height=600;
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
														loadingScreen("Operazione terminata", "${baseUrl}/int/images/task.png",1000);
														form.dialog("close");
														window.location.reload(true);
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
										
									},
      	                           open:function(event,ui){
      	                           
      	                       		$(this).find('.datePicker').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
      	                           	//$(this).find('.datePicker').datepicker('setDate',new Date());
      	                           	$(this).find('.datePicker:focus').click(function(){
      	                           		$(this).focus();
      	                           	});
									}
									});
								form.dialog("open");
								
								console.log(variables);
								url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${el.id}/AllegatoContratto";
								
								
								$.getJSON( url, function( data ) {
								
        	console.log(data);
        	
        	
        	<#--popolo la tendina con i documenti caricati-->
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==1){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc1']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc1']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==2){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc2']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc2']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==3){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc3']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc3']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==4){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc4']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc4']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==1){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc12']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc12']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==2){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc22']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc22']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==3){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc32']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc32']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==4){
        			<#--if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";-->
        			selected="";
        			$("select[name$='Doc42']").append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					<#--if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        					else selected="";-->
        					selected="";
        					$("select[name$='Doc42']").append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');		
        				}
        			}
        		}
        	}
        	
        	
        	
        	});
								
								
								$('.datePicker').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
								
								//CRPMS-101 - Popolo automaticamente la data inizio validita con la data firma
								$('#taskForm_'+taskId+' [name="dataFirma"]').change(function(){
									var date=$('#taskForm_'+taskId+' [name="dataFirma"]').datepicker();
									date=date.data('datepicker').date;
									date= new Date(date.getTime());
									$('#taskForm_'+taskId+' [name="dataInizioVal"]').datepicker('setDate',date);  
								});
								$('#taskForm_'+taskId+' [name="dataFirma2"]').change(function(){
									var date=$('#taskForm_'+taskId+' [name="dataFirma2"]').datepicker();
									date=date.data('datepicker').date;
									date= new Date(date.getTime());
									$('#taskForm_'+taskId+' [name="dataInizioVal2"]').datepicker('setDate',date);  
								});
								
								
								return false;
							}
						});
					}
				});
				
	}
	</@script>


<#macro hiddenElementLink id name label searchScript searchValue selectedValues=[]  searchId="" selectedIds=[] aMap={} fieldDef=null enabled=true> 
<#assign usedTokenInput=usedTokenInput+1/>
<#assign theme=true/>
<#assign single=true/>
<#assign autoCompleteField=""/>
	 	<@script>
 	
 	var selected_id_${id}=null;
 	var selected_item_${id}=new Object();
 	var selected_${id}=false;
 	
 	
	<#list aMap?keys as prop>
		<#if autoCompleteField="">
			<#assign autoCompleteField=prop/>
			$('#${prop}').change(function(){if (!selected_${id}) {selected_id_${id}=null;selected_item_${id}=new Object();$('#${id}').val("");}check_${id}();});
			<#else>
			$('#${prop}').change(function(){check_${id}();});
		</#if>
		selected_item_${id}.${prop}=$('#${prop}').val();
	</#list>
	
	<#list selectedIds as sid>
		var selected_id_${id}=${sid};
	</#list>	
	
	function check_${id}(){
		console.log("Effettuo i controlli");
		if ($('#update_dictionary_${id}')){
			$('#update_dictionary_${id}').remove();			
		}
		if ($('#add_dictionary_${id}')){
			$('#add_dictionary_${id}').remove();
		}
		if (selected_id_${id}!=null && selected_id_${id}!=""){
		//Collegamento presente	
			console.log("Collegamento presente - "+selected_id_${id});
			var changed=false;
			<#list aMap?keys as prop>
				if ($('#${prop}').val()!=selected_item_${id}.${prop}) changed=true;
			</#list>
			if (changed) $('#informations-${autoCompleteField}').parent().append("<input onClick='updateDictionary_${id}();' id='update_dictionary_${id}' type='button' value='Aggiorna il dizionario'/>");
		}else {
		//Collegamento non presente
			console.log("Collegamento non presente - "+selected_id_${id});
			$('#informations-${autoCompleteField}').parent().append("<input onClick='addDictionary_${id}();' id='add_dictionary_${id}' type='button' value='Aggiungi al dizionario'/>");
			
		}
	}
	
	function addDictionary_${id}(){
		var typeId="${fieldDef.typefilters}";
		var formData=new FormData();
		formData.append('parentId', valueOfField('${fieldDef.addFilterFields}'));
		<#list aMap?keys as prop>
			formData.append("${aMap[prop]}", $('#${prop}').val()); 
		</#list>
		$.ajax({
                url: '${baseUrl}/app/rest/documents/save/'+typeId,
                type: 'POST',
                contentType:false,
                processData:false,
                async:false,
                cache:false,
                data: formData,
                success: function(obj){
                    if (obj.result=="OK") {
                        $('#${id}').val(obj.ret);
                        selected_id_${id}=obj.ret;
                        <#list aMap?keys as prop>
						selected_item_${id}.${prop}=$('#${prop}').val();
						</#list>
						$('#add_dictionary_${id}').remove();
                    }else {
                        loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
               });
	}
	
	function updateDictionary_${id}(){
		var formData=new FormData();
		<#list aMap?keys as prop>
			formData.append("${aMap[prop]}", $('#${prop}').val()); 
		</#list>
		$.ajax({
                url: '${baseUrl}/app/rest/documents/update/'+$('#${id}').val(),
                type: 'POST',
                contentType:false,
                processData:false,
                async:false,
                cache:false,
                data: formData,
                success: function(obj){
                    if (obj.result=="OK") {
                        $('#${id}').val(obj.ret);
                        selected_id_${id}=obj.ret;
                        <#list aMap?keys as prop>
						selected_item_${id}.${prop}=$('#${prop}').val();
						</#list>
						$('#update_dictionary_${id}').remove();
						
                    }else {
                        loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
               });
	}
	
	</@script>
    <input type="hidden" id="${id}" name="${name}" value="${selectedIds[0]!""}"/>
    <@script>
        
        	$( "#${autoCompleteField}" ).autocomplete({
			source: function( request, response ) {
				$.ajax({
					url: "${searchScript}?parent="+valueOfField('${fieldDef.addFilterFields}'),
					dataType: "json",
					data: {
					term: request.term
					},
					success: function( data ) {
					selected_${id}=false;
					console.log(data);
						response( $.map( data, function( item ) {
							return {
								label: item.title,
								id: item.id,
								<#list aMap?keys as prop>
								${prop}: item.metadata.${aMap[prop]}[0],
								</#list>
								value: item.title 
							}
						}));
						}
					});
					},
					minLength: 1,
					select: function( event, ui ) {
						selected_${id}=true;
						console.log(ui.item);	
						$('#${id}').val(ui.item.id);
						<#list aMap?keys as prop>
							$('#${prop}').val(ui.item.${prop});
						
						</#list>
						selected_id_${id}=ui.item.id;
						selected_item_${id}=ui.item;
					},
					open: function() {
					$( this ).removeClass( "ui-corner-all" ).addClass( "ui-corner-top" );
					},
					close: function() {
					$( this ).removeClass( "ui-corner-top" ).addClass( "ui-corner-all" );
				}
		});
        
            
       
    </@script>
</#macro>


<@script>
	function tristezza(){
		alert($('#RefContratto_NomeCognome').val());
		if($('#RefContratto_NomeCognome').val()=='') {
			alert("vuoto"); 
			event.preventDefault();
			event.stopPropagation();
		}
	}
</@script>

<style>

.vs{
float: left;
    width: 45%;
}
.vs label{
	width:33%;
}

.re{
    width: 45%;
}
.re label{
	width:33%;
}

.ri{
float: left;
    width: 45%;
}
.ri label{
	width:33%;
}

.vl{
    width: 45%;
}
.vl label{
	width:33%;
	color:#E17031;
}

.l4 {
	color:#E17031;
}

.ui-autocomplete.ui-menu{
	z-index:9999!important;
}

.span1{
	color:#125873;
}
</style>

  <div class="row">
   		<div class="col-xs-10">
   			
<#include "../helpers/MetadataTemplate.ftl"/>

	<div style="display: block">
	<!--div style="float: right"-->
	<div style="float: left">
	<!--#include "../helpers/information.ftl"/-->
	<!--#include "../helpers/actions.ftl"/-->
	<!--#include "../helpers/workflow.ftl"/-->
	<!--#include "../helpers/permission.ftl"/-->
	</div>
 
	<div style="text-align: right">
		<br/>
		<!--fieldset style="background-color:#DFEFFC"-->
			<!--legend style="color: #125873">Stato di avanzamento</legend-->
				
				<!--GC 02-12-2013 Controllo la presenza della firma SR-->
				<#assign FirmaRespSR="false">
				<#assign FirmaRespSR2="false">
					
				<#assign approv1negativa="false"/>
				<#assign approv1positiva="false"/>
				<#assign approv2positiva="false"/>
				<#assign inviatoSponsor="false"/>
				<#assign contrattoArchiviato="false"/>
					
						
					
				
				
						
					
				<#list el.getChildrenByType("LettAccFirmaContr") as child>
					<#if child.id?? && child.file??>
						<#assign FirmaRespSR="true">
						
					</#if>
				</#list>
				
				<#assign FirmaPI="false"> <#--CONTROLLO CHE NON CI SIA GIà UN FIGLIO di tipo ContrattoFirmaPI-->
				<#list el.getChildrenByType("ContrattoFirmaPI") as child>
					<#--decommentare in caso di file nel template-->
					<#--if child.id?? && child.file??-->
					<#if child.id??>
						<#assign FirmaPI="true">
					</#if>
				</#list>

				<#assign FirmaDIP="false"> <#--CONTROLLO CHE NON CI SIA GIà UN FIGLIO di tipo ContrattoFirmaDIP-->
				<#list el.getChildrenByType("ContrattoFirmaDIP") as child>
					<#--decommentare in caso di file nel template-->
					<#--if child.id?? && child.file??-->
					<#if child.id??>
					<#assign FirmaDIP="true">
					</#if>
				</#list>

				<#assign FirmaDG="false"> <#--CONTROLLO CHE NON CI SIA GIà UN FIGLIO di tipo ContrattoFirmaDG-->
				<#list el.getChildrenByType("ContrattoFirmaDG") as child>
					<#--decommentare in caso di file nel template-->
					<#--if child.id?? && child.file??-->
					<#if child.id??>
						<#assign FirmaDG="true">
					</#if>
				</#list>
				
				<#if el.getfieldData("ValiditaContratto", "armadio")[0]??>
					<#assign contrattoArchiviato="true"/>
					<!--span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Contratto archiviato:&nbsp;&nbsp;</span>
					<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Si</b> &nbsp;</span>
					Armadio:&nbsp;<span class="span1">${el.getfieldData("ValiditaContratto","armadio")[0]?split("###")[1]}</span>
					Ripiano:&nbsp;<span class="span1">${el.getfieldData("ValiditaContratto","ripiano")[0]?split("###")[1]}</span-->
				</#if>	
				
				<!-- div -->
					<#if el.getfieldData("ApprovDADSRETT", "Approvazione")[0]??>
						<#if el.getfieldData("ApprovDADSRETT", "Approvazione")[0]?split("###")[0]=="1">
							<#assign approv1positiva="true"/>
							<!--
							
							<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Approvazione DA/DS/RETTORE:&nbsp;&nbsp;</span>
							<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Positiva</b> &nbsp;</span>
							<a class="center-link" href="${baseUrl}/app/documents/custom/ApprovDADSRETT/${el.id}">
							Data firma:&nbsp;<span class="span1">${getFieldFormattedDate("ApprovDADSRETT", "dataFirma", el)}</span>
							</a>
							&nbsp;
							<#if el.getfieldData("ApprovDADSRETT", "Doc1")?? && el.getfieldData("ApprovDADSRETT", "Doc1")?size gt 0 && el.getfieldData("ApprovDADSRETT", "Doc1")[0]!="0">
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT", "Doc1")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT", "Doc1")[0]?split("###")[0]?split("_")[0]}">
								Corpus
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
							<#if el.getfieldData("ApprovDADSRETT", "Doc2")?? && el.getfieldData("ApprovDADSRETT", "Doc2")?size gt 0 && el.getfieldData("ApprovDADSRETT", "Doc2")[0]!="0">
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT", "Doc2")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT", "Doc2")[0]?split("###")[0]?split("_")[0]}">
								All. A
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
							<#if el.getfieldData("ApprovDADSRETT", "Doc3")?? && el.getfieldData("ApprovDADSRETT", "Doc3")?size gt 0 && el.getfieldData("ApprovDADSRETT", "Doc3")[0]!="0">
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT", "Doc3")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT", "Doc3")[0]?split("###")[0]?split("_")[0]}">
								All. B
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
							<#if el.getfieldData("ApprovDADSRETT", "Doc4")?? && el.getfieldData("ApprovDADSRETT", "Doc4")?size gt 0 && el.getfieldData("ApprovDADSRETT", "Doc4")[0]!="0">
								<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT", "Doc4")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT", "Doc4")[0]?split("###")[0]?split("_")[0]}">
									Altri allegati
									<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
						-->
									
						</#if>
						
						

						
						<#if el.getfieldData("ApprovDADSRETT", "Approvazione")[0]?split("###")[0]=="2">
							<#assign approv1negativa="true"/>
							<!--span style="background-color: #FFA463;border-radius: 5px;padding:2px;">Approvazione DA/DS/RETTORE:&nbsp;&nbsp;</span>
							<span style="background-color: #FFC175;border-radius: 5px;padding:2px;"><b>Negativa</b> &nbsp;</span>
							<a class="center-link" href="${baseUrl}/app/documents/custom/ApprovDADSRETT/${el.id}">
							<Data firma:&nbsp;<span class="span1">${getFieldFormattedDate("ApprovDADSRETT", "dataFirma", el)}</span>
							</a-->
						</#if>
						
						<#if el.getfieldData("ValiditaContratto", "dataSponsor")[0]??>
							<#assign inviatoSponsor="true"/>
							<!--span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Inviata al Promotore:&nbsp;&nbsp;</span>
							<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Si</b> &nbsp;</span>
							Data:&nbsp;<span class="span1">${getFieldFormattedDate("ValiditaContratto", "dataSponsor", el)}</span-->
						</#if>
						
						<#--GC 20/03/2015 blocco messo fuori dall'if-->
						<#if el.getfieldData("ValiditaContratto", "armadio")[0]??>
							<#assign contrattoArchiviato="true"/>
						</#if>
						-->	
						
						<#list el.templates as template>
							<!--
							<#if template.name=="ApprovDADSRETT">
								<a class="center-link" href="${baseUrl}/app/documents/custom/ApprovDADSRETT/${el.id}"> dettagli</a>
							</#if>
							-->
						</#list>
						
					</#if>
				<!--/div-->
				
				<#list el.getChildrenByType("LettAccFirmaContr2") as child2>
					<#if child2.id?? && child2.file??>
						<#assign FirmaRespSR2="true">
						<!--div>
							<br/>
							<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Seconda Firma Responsabile SR:&nbsp;&nbsp;</span>
							<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Si</b> &nbsp;</span>
							<a href="${baseUrl}/app/documents/detail/${child2.id}">
							Prot:&nbsp;<span class="span1">${child2.getfieldData("Step2Contr", "numProt2")[0]}</span>
							Data firma:&nbsp;<span class="span1">${child2.getfieldData("Step2Contr", "dataFirma2")[0].time?date?string.short}</span>
							Dest:&nbsp;<span class="span1">${child2.getfieldData("Step2Contr", "dest2")[0]?split("###")[1]}&nbsp;</span>
							</a>
								&nbsp;
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile2")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile2")[0]?split("###")[0]?split("_")[0]}">
								Corpus
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile22")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile22")[0]?split("###")[0]?split("_")[0]}">
								All A.
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile23")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile23")[0]?split("###")[0]?split("_")[0]}">
								All B.
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							<#if child2.getfieldData("Step2Contr", "selectFile24")?? && child2.getfieldData("Step2Contr", "selectFile24")?size gt 0>
								<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile24")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile24")[0]?split("###")[0]?split("_")[0]}">
									Altri allegati
									<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
						</div-->
					</#if>
				</#list>
				
				
				<!--div>
					<#if el.getfieldData("ApprovDADSRETT2", "Approvazione2")[0]??>
						<br/>
						<#if el.getfieldData("ApprovDADSRETT2", "Approvazione2")[0]?split("###")[0]=="1">
							<#assign approv2positiva="true"/>
							<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Seconda Approvazione DA/DS/RETTORE:&nbsp;&nbsp;</span>
							<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Positiva</b> &nbsp;</span>
							<a class="center-link" href="${baseUrl}/app/documents/custom/ApprovDADSRETT2/${el.id}">
							Data firma:&nbsp;<span class="span1">${getFieldFormattedDate("ApprovDADSRETT2", "dataFirma2", el)}</span>
							</a>
						</#if>

						  <#if el.getfieldData("ApprovDADSRETT2", "Doc12")?? && el.getfieldData("ApprovDADSRETT2", "Doc12")?size gt 0 && el.getfieldData("ApprovDADSRETT2", "Doc12")[0]!="0">
							&nbsp;
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT2", "Doc12")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT2", "Doc12")[0]?split("###")[0]?split("_")[0]}">
								Corpus
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
							<#if el.getfieldData("ApprovDADSRETT2", "Doc22")?? && el.getfieldData("ApprovDADSRETT2", "Doc22")?size gt 0 && el.getfieldData("ApprovDADSRETT2", "Doc22")[0]!="0">
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT2", "Doc22")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT2", "Doc22")[0]?split("###")[0]?split("_")[0]}">
								All. A
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
							<#if el.getfieldData("ApprovDADSRETT2", "Doc32")?? && el.getfieldData("ApprovDADSRETT2", "Doc32")?size gt 0 && el.getfieldData("ApprovDADSRETT2", "Doc32")[0]!="0">
							<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT2", "Doc32")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT2", "Doc32")[0]?split("###")[0]?split("_")[0]}">
								All. B
								<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>
							<#if el.getfieldData("ApprovDADSRETT2", "Doc42")?? && el.getfieldData("ApprovDADSRETT2", "Doc42")?size gt 0 && el.getfieldData("ApprovDADSRETT2", "Doc42")[0]!="0">
								<a href="${baseUrl}/app/documents/getAttach/uniqueId/${el.getfieldData("ApprovDADSRETT2", "Doc42")[0]?split("###")[0]?split("_")[1]}/${el.getfieldData("ApprovDADSRETT2", "Doc42")[0]?split("###")[0]?split("_")[0]}">
									Altri allegati
									<img src="/Document-icon.png" width="30" height="30">
								</a>
							</#if>

					</#if>
				</div-->


				<!--div>
					<#if FirmaRespSR=="false">
						<span style="background-color: #FFAA66;border-radius: 5px;padding:2px;">Firma Responsabile SR:&nbsp;&nbsp;</span>
						<span style="background-color: #F4A460;border-radius: 5px;padding:2px;"><b>Pending</b> &nbsp;</span>
					</#if>
				</div-->


				<#--list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="LettAccFirmaContr" && FirmaRespSR=="false" && el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?? && el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?size gt 0>
			 			<input type="button" class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Trasmissione da SR a CTC">
		     	</#if>
				</#list-->
				<#if model['getCreatableElementTypes']?? && model['getCreatableElementTypes']?size gt 0 >
				<#list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="ContrattoFirmaDIP" && FirmaDIP=="false" && ((el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?? && el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?size gt 0) || (el.getFieldDataString("preFirmaContrattoWF", "iterSemplificato")?? && el.getFieldDataString("preFirmaContrattoWF", "iterSemplificato")=="1"))>
						<input type="button" class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Firma Direttore Dipartimento/Istituto">
					</#if>
				</#list>

				<#list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="ContrattoFirmaPI" && FirmaPI=="false" && ((el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?? && el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?size gt 0) || (el.getFieldDataString("preFirmaContrattoWF", "iterSemplificato")?? && el.getFieldDataString("preFirmaContrattoWF", "iterSemplificato")=="1"))>
						<input type="button" class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Firma PI">
					</#if>
				</#list>

				<#list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="ContrattoFirmaDG"  && FirmaDG=="false" && ((el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?? && el.getfieldData("preFirmaContrattoWF", "dataRicezFirmSP")?size gt 0) || (el.getFieldDataString("preFirmaContrattoWF", "iterSemplificato")?? && el.getFieldDataString("preFirmaContrattoWF", "iterSemplificato")=="1"))>
			 			<input type="button" class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Firma DG / Delegato">
		     	</#if>
				</#list>
				</#if>
				
				<#--
				<#list el.getChildrenByType("RinnovoContratto") as subEl>
    				<#if subEl.id??>
							<div>
								<br/>
								<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Rinnovo Contratto:&nbsp;&nbsp;</span>
								<a href="${baseUrl}/app/documents/detail/${subEl.id}">
								Fine validit&agrave;:&nbsp;<span class="span1">${subEl.getfieldData("RinnovoContratto", "DataFineNuova")[0].time?date?string.short}</span>
								</a>
								
								<#if subEl.getfieldData("RinnovoContratto", "Emendamento")?? && subEl.getfieldData("RinnovoContratto", "Emendamento")?size gt 0>
									Rif. Eme:&nbsp;<span class="span1">${subEl.getFieldDataDecode("RinnovoContratto", "Emendamento")}</span> 
								</#if>
								
								<#if subEl.getfieldData("RinnovoContratto", "SelectFile")[0]??>
									&nbsp
									<a href="${baseUrl}/app/documents/getAttach/uniqueId/${subEl.getfieldData("RinnovoContratto", "SelectFile")[0]?split("###")[0]?split("_")[1]}/${subEl.getfieldData("RinnovoContratto", "SelectFile")[0]?split("###")[0]?split("_")[0]}">
										Corpus
										<img src="/Document-icon.png" width="30" height="30">
										</a>
									</#if>
									<#if subEl.getfieldData("RinnovoContratto", "SelectFile2")[0]??>
									<a href="${baseUrl}/app/documents/getAttach/uniqueId/${subEl.getfieldData("RinnovoContratto", "SelectFile2")[0]?split("###")[0]?split("_")[1]}/${subEl.getfieldData("RinnovoContratto", "SelectFile2")[0]?split("###")[0]?split("_")[0]}">
										All. A
										<img src="/Document-icon.png" width="30" height="30">
										</a>
									<a href="${baseUrl}/app/documents/getAttach/uniqueId/${subEl.getfieldData("RinnovoContratto", "SelectFile3")[0]?split("###")[0]?split("_")[1]}/${subEl.getfieldData("RinnovoContratto", "SelectFile3")[0]?split("###")[0]?split("_")[0]}">
										All. B
										<img src="/Document-icon.png" width="30" height="30">
										</a>
									<#if subEl.getfieldData("RinnovoContratto", "SelectFile4")?? && subEl.getfieldData("RinnovoContratto", "SelectFile4")?size gt 0>
										<a href="${baseUrl}/app/documents/getAttach/uniqueId/${subEl.getfieldData("RinnovoContratto", "SelectFile4")[0]?split("###")[0]?split("_")[1]}/${subEl.getfieldData("RinnovoContratto", "SelectFile4")[0]?split("###")[0]?split("_")[0]}">
											Altri allegati
											<img src="/Document-icon.png" width="30" height="30">
										</a>
									</#if>
								</#if>				
							</div>
						</#if>
    			</#list>
    			-->
				<#if model['getCreatableElementTypes']?? && model['getCreatableElementTypes']?size gt 0 >
					<#list model['getCreatableElementTypes'] as docType>

						<#if docType.typeId="LettAccFirmaContr2" && FirmaRespSR=="true" && FirmaRespSR2=="false" && approv1negativa=="true">
							<input type="button" class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Seconda trasmissione da SR a CTC">
					</#if>

					<#if docType.typeId="RinnovoContratto" && (contrattoArchiviato=="true")>
							<input type="button" class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Inserisci Rinnovo Contratto">
					</#if>

					</#list>
				</#if>
			
					
			
			
				<div>

					<#--if !(el.getfieldData("preFirmaContrattoWF","dataRicezFirmSP")?size gt 0) || (FirmaRespSR=="true" && approv1negativa=="false") || FirmaRespSR2=="true"-->
					<#if !(el.getfieldData("preFirmaContrattoWF","dataRicezFirmSP")?size gt 0) || FirmaDG=="true">
					<div id="processes">
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
													<input id="startProcess" action="${wf.key}" class="submitButton round-button blue startProcess btn btn-info" type="button" value="${wf.name}"><br/>	
					            	</#if>
					    			</#if>
					    	  </#list>
					    	</#list>
							</#if>
						</#if>
						<div id="task-Actions" style="text-align: right"></div>
					</div>
				</#if>
					
					<#--div id="task-Actions" style="text-align: right"></div-->
					
				</div>
				
			
		</fieldset>
		</div>
    		
    	<!-- inserire il template dei metadatai-->
    	<fieldset>
		  <!--legend>File allegati</legend-->
		  <br/>
			<#if model['getCreatableElementTypes']?? && model['getCreatableElementTypes']?size gt 0 >
				<#list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="AllegatoContratto">
					<!--input type="button" class="submitButton round-button blue btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Aggiungi nuovo documento allegato">
					<br/><br/-->

					<button class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';">
								<i class="icon-plus bigger-160"> </i>
								<b>Aggiungi documento</b>
							</button>

							<!--div style="float:right">
							<button class="submitButton round-button blue templateForm btn btn-info" onclick="window.location.href='${baseUrl}/app/documents/detail/${el.getParent().id}/#Fatturazione-tab2';">
								Accedi alla fatturazione
							</button>
							</div-->

					<br/><br/>
					</#if>
				</#list>
			</#if>
    			
    	<#assign parentEl=el/>

    	<!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-header"> Ultime Versioni </div>
					<div class="table-responsive">	
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<th class="hidden-480">Tipologia</th>
									<th class="hidden-480">File</th>
									<th class="hidden-480">Autore</th>
									<th class="hidden-480">Versione</th>
									<th class="hidden-480">Data</th>
									<th class="hidden-480">Note</th>
									<th class="hidden-480">Inserito da</th>
									<th class="hidden-480">Caricato il</th>
									<th style="width: 6%">Azioni</th>
								</tr>
							</thead>

							<tbody>	

    				<#list parentEl.getChildrenByType("AllegatoContratto") as subEl>
    				 <!--h3><a href="${baseUrl}/app/documents/detail/${subEl.id}"-->
    				
    				 <#-- ${subEl.titleString} analogo a @elementTitle subEl --> 
    				 	
    				 <!--@elementTitle subEl/> - versione: <#if subEl.file??>${subEl.file.version!""} - data: ${subEl.file.date.time?date?string.short}</#if> </a></h3-->
    					
    				<#assign tipologia="" />
								<#assign autore="" />
								<#assign version="" />
								<#assign fileName="" />
								<#assign uploadUser="" />
								<#assign uploadDt="" />
								<#assign data="" />
								<#assign note="" />
								<#if subEl.getfieldData("tipologiaContratto","TipoContratto")[0]??>
									<#assign tipologia=subEl.getFieldDataDecode("tipologiaContratto","TipoContratto") />
									<#if subEl.file.autore??>
										<#assign autore=subEl.file.autore />
									</#if>
									
									<#if subEl.file.version??>
										<#assign version=subEl.file.version />
									</#if>
									
									<#if subEl.file.fileName??>	
										<#assign fileName=subEl.file.fileName />
									</#if>
									
									<#if subEl.file.uploadUser??>
										<#assign uploadUser=subEl.file.uploadUser />
									</#if>
									
									<#if subEl.file.uploadDt??>
										<#assign uploadDt=subEl.file.uploadDt.time?date?string.short />
									</#if>
									
									<#if subEl.file.date??>
										<#assign data=subEl.file.date.time?date?string.short />
									</#if>
									
									<#if subEl.file.note??>
										<#assign note=subEl.file.note />
									</#if>
								</#if>
								
								<tr>
									<td class="hidden-480">${tipologia}</td>
									<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${fileName}</a></td>
									<td class="hidden-480">${autore}</td>
									<td class="hidden-480">${version}</td>
									<td class="hidden-480">${data}</td>
									<td class="hidden-480">${note}</td>
									<td class="hidden-480">${uploadUser}</td>
									<td class="hidden-480">${uploadDt}</td>
									<td>
										<div class="visible-md visible-lg hidden-sm hidden-xs action-buttons">
											<a class="blue" href="${baseUrl}/app/documents/detail/${subEl.id}">
												<i class="icon-zoom-in bigger-130"></i>
											</a>
											<a class="blue" href="${baseUrl}/app/documents/getAttach/${subEl.id}">
												<i class="icon-cloud-download bigger-130"></i>
											</a>
											<#if subEl.getFieldDataString("tipologiaContratto","numeroProtocollo")?string=="" >
											<button title="Protocolla documento" class="btn btn-xs btn-danger" onclick="if(confirm('Sei sicuro di voler protocollare il documento?')) {protocollaElement(${subEl.id},'${subEl.file.fileName}',${elStudio.id},'${elCentro.getFieldDataString("IdCentro","ProtocolloFascicolo")?string}',${elCentro.id})};return false;" href="#">
											<i class="icon-file bigger-120"></i>
											</button>
											<#else>
											<button title="Vedi documento protocollato" class="btn btn-xs btn-danger" onclick="vediProtocollo('${subEl.getFieldDataString("tipologiaContratto","numeroProtocollo")?string}'); return false;" href="#">
											<i class="icon-file bigger-120"></i>
											</button>
											</#if>
										</div>
									</td>
								</tr>
									</#list>
 							</tbody>
						</table>
					</div>
				</div>
			</div>
    	<!--fine tabella nuova-->	
    		
    	</legend>
    </fieldset>
   
   <!-- VERSIONI DI TUTTI I DOC inizio-->
   <#list parentEl.getChildrenByType("AllegatoContratto") as allContrEl>
   	
   	<!-- ultima versione -->
   	<#assign autore="" />
		<#if allContrEl.file.autore??>
			<#assign autore=allContrEl.file.autore />	
		</#if>
		<#assign note="" />	
		<#if allContrEl.file.note??>
			<#assign note=allContrEl.file.note />	
		</#if>
   	<#if ls??>
   	   <#assign ls = ls+[
				  {"id":allContrEl.id,
				   "autore":autore,
				   "fileName":allContrEl.file.fileName,
				   "version":allContrEl.file.version,
				   "uploadDt":allContrEl.file.uploadDt.time?datetime?string.full,
				   "dataDoc":allContrEl.file.date.time?date?string.short,
				   "insertBy":allContrEl.file.uploadUser,
				   "note":note,
				   "tipologia":allContrEl.getFieldDataDecode("tipologiaContratto","TipoContratto"),
				   "downloadLink":baseUrl+"/app/documents/getAttach/"+allContrEl.id}
				]>
		<#else>
			<#assign ls = [
				  {"id":allContrEl.id,
				   "autore":autore,
				   "fileName":allContrEl.file.fileName,
				   "version":allContrEl.file.version,
				   "uploadDt":allContrEl.file.uploadDt.time?datetime?string.full,
				   "dataDoc":allContrEl.file.date.time?date?string.short,
				   "insertBy":allContrEl.file.uploadUser,
				   "note":note,
				   "tipologia":allContrEl.getFieldDataDecode("tipologiaContratto","TipoContratto"),
				   "downloadLink":baseUrl+"/app/documents/getAttach/"+allContrEl.id}
				]>
   	</#if>
   	
   	<!-- versioni precedenti -->	
   	<#if allContrEl.auditFiles?size gt 0>
   		
    	<#list allContrEl.auditFiles as oldVersions>
			  <#if oldVersions.fileName?length gt 15>
					<#assign nomeFile=oldVersions.fileName?substring(0,oldVersions.fileName?length-15)+"(...)."+oldVersions.fileName?split(".")?last/>
				<#else>
				  <#assign nomeFile=oldVersions.fileName />
			  </#if>
			  <#assign dim=oldVersions.size+" Kb" />
			  
			  <#assign autore="" />	
			  <#if oldVersions.autore??>
					<#assign autore=oldVersions.autore />	
				</#if>
				<#assign note="" />	
				<#if allContrEl.file.note??>
					<#assign note=allContrEl.file.note />	
				</#if>
				<#assign oldVersionsNote="" />
				<#if oldVersions.note??>
				<#assign oldVersionsNote=oldVersions.note />
				</#if>
	  		<#assign ls = ls+[
			  {"id":oldVersions.id,
			   "autore":autore,
			   "fileName":oldVersions.fileName,
			   "version":oldVersions.version,
			   "uploadDt":oldVersions.uploadDt.time?datetime?string.full,
			   "dataDoc":oldVersions.date.time?date?string.short,
			   "tipologia":allContrEl.getFieldDataDecode("tipologiaContratto","TipoContratto"),
			   "insertBy":oldVersions.uploadUser,
			   "note":oldVersionsNote,
			   "downloadLink":baseUrl+"/app/documents/getAttach/old/"+oldVersions.id}
				]>
	  			
			</#list>
		</#if>
			 
   </#list>
   
   <div class="row">
	 	<div class="col-xs-12">
	 		<div class="table-header"> Cronologia upload file </div>
	 		<div class="table-responsive">	
   			<table id="sample-table-1" class="table table-striped table-bordered table-hover">
	 				<thead>
	 					<tr>
	 						<th class="hidden-480">Tipologia</th>
	 						<th class="hidden-480">File</th>
	 						<th class="hidden-480">Autore</th>
	 						<th class="hidden-480">Versione</th>
	 						<th class="hidden-480">Data</th>
	 						<th class="hidden-480">Note</th>
	 						<th class="hidden-480">Inserito da</th>
	 						<th class="hidden-480">Caricato il</th>
	 						<th style="width: 6%">Azioni</th>
	 					</tr>
	 				</thead>
   	
	 				<tbody>
	 				
	 				<#if ls??>		
	 				<#list ls?sort_by("uploadDt")?reverse as i>
	 					<tr>
	 						<td>${i.tipologia}</td>
	 						<td><a href="${i.downloadLink}">${i.fileName}</a></td>
	 						<td>${i.autore}</td>
	 						<td>${i.version}</td>
	 						<td>${i.dataDoc}</td>
	 						<td>${i.note}</td>
	 						<td>${i.insertBy}</td>
	 						<td>${i.uploadDt}</td>				
	 						<td>
								<div class="visible-md visible-lg hidden-sm hidden-xs action-buttons">
									<a class="blue" href="${i.downloadLink}">
										<i class="icon-cloud-download bigger-130"></i>
									</a>
								</div>
							</td>
	 					</tr>
	 				</#list>
	 			</#if>
	 				
	 				</tbody>
				</table>
			</div>
		</div>
	</div>
	 <!-- VERSIONI DI TUTTI I DOC fine-->
   

    		
    		
    		
    		<!--#include "../helpers/child-box.ftl"/-->
    			
        <#include "../helpers/attached-file.ftl"/>
        	<br/><br/>
        
        	
    </div>
    <!--#include "../helpers/comments.ftl"/-->
    <!--#include "../helpers/events.ftl"/-->	

</div>
	<#include "../helpers/contratto-status-bar.ftl"/>
    
    </div>
