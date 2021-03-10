<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
	"inline_scripts":[],
	"title" : "Dettaglio",
 	"description" : "Dettaglio" 
} />

<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />

<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />

<#list el.templates as template>
	<#if template.name="DatiFeasibilityAreaME" || template.name="DatiFeasibilityAreaBS" || template.name="DatiFeasibilityAreaGA" || template.name="DatiFeasibilityAreaAC">
	<#assign nomeTemplate=template.name />
	</#if>
</#list>


<@script>




var sidebarDefault="${el.getParent().getId()}#metadataTemplate-Feasibility2";

	$.fn.editable.defaults.mode = 'inline';
	
 	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var empties=new Array();
 	
 	var nomeTemplate=${nomeTemplate};
 	var formName=nomeTemplate.id.replace("form-", "");
 	
 	empties[dummy.type.id]=dummy;
	
	function checkPreCesc(){
			
			/*Istruttoria Area Metodologica ed economica*/
			var a="";
			for(a=1;a<=15;a++){
				var b=$('#DatiFeasibilityAreaME_FME'+a).length;
			  var c=$('#DatiFeasibilityAreaME_FME'+a+':checked').val();
			  var d=$('#DatiFeasibilityAreaME_FME'+a).attr('type');
			  if(b && !c && d=='radio'){
				  alert("ATTENZIONE! Compilare tutti campi obbligatori della scheda Area Metodologica ed Economica");
					return false;
				}
			}
			
				
			/*Istruttoria Area Beni sanitari*/
			var a="";
			for(a=1;a<=5;a++){
				var b=$('#DatiFeasibilityAreaBS_FBS'+a).length;
			  var c=$('#DatiFeasibilityAreaBS_FBS'+a+':checked').val();
			  if(b && !c){
				  alert("ATTENZIONE! Compilare tutti campi obbligatori della scheda Area Beni Sanitari");
					return false;
				}
			}
			
			/*Istruttoria Area Assicurativa*/
			var a="";
			for(a=1;a<=2;a++){
				var b=$('#DatiFeasibilityAreaAC_FAC'+a).length;
			  var c=$('#DatiFeasibilityAreaAC_FAC'+a+':checked').val();
			  if(b && !c){
				  alert("ATTENZIONE! Compilare tutti campi obbligatori della scheda Area Assicurativa");
					return false;
				}
			}
			
			if($('#DatiFeasibilityAreaAC_FAC3').length && $('#DatiFeasibilityAreaAC_FAC3').val()==""){
			 alert("ATTENZIONE! Compilare tutti campi obbligatori");
			 return false;
			}
			
			/*Istruttoria Area Giuridico-Amministrativa*/
			var a="";
			for(a=1;a<=8;a++){
				var b=$('#DatiFeasibilityAreaGA_FGA'+a).length;
			  var c=$('#DatiFeasibilityAreaGA_FGA'+a+':checked').val();
			  var d=$('#DatiFeasibilityAreaGA_FGA'+a).attr('type');
			  if(b && !c && d=='radio'){
				  alert("ATTENZIONE! Compilare tutti campi obbligatori della scheda Istruttoria Area Giuridico-Amministrativa");
					return false;
				}
			}
			
			var a=$('#DatiFeasibilityAreaGA_FGA6');
			if(a.length){
				if(a.val()==""){
				 alert("ATTENZIONE! Compilare tutti campi obbligatori della scheda Istruttoria Area Giuridico-Amministrativa1");
				 return false;
				}else{
					var b=isNaN(a.val());
					var c=a.val().match(',');
					if(!b && c==null) {}
					else {
						alert('ATTENZIONE! Utilizzare un numero reale e il punto come separatore nel campo \'Registrazione del valore in DBNRC\' ');
						a.focus();
						return false;
					}
				 }
			}
			
				
				return true;
			}
			
	
	function executeFormTask(taskId){
			
			/*
			$('input[name^=DatiFeasibilityAreaME_FME]:not(:checked)').each(function(){
				if($('input[name='+this.name+']:checked').size()==0){
					alert("ATTENZIONE! Compilare tutti campi obbligatori");
					return false;
				}
			});
			*/
			
			
			
			
			
			
	
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
									if (required) addClass="required";
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
											/*GC CRPMS-237 punto 109 - se l'esito istruttoria è pos o neg -> tutti i campi obbligatori*/
											var tendinaIstruttoria=$('select[name=Feasibility]').val().split('###')[0];
											if(goon && tendinaIstruttoria!="3" && tendinaIstruttoria!="4") goon=checkPreCesc();
											
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
											//console.log(form);
											//return;
        									var formData=new FormData(taskForm);
											//data=new Object();
											//data['taskId']=taskId;
											//data['properties']=properties;
											
											
											
												
											//GIULIO 30/01/2015 - Forzo il salvataggio della form all'invio del processo
											formSubmitStd(formName);
											
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
                    									loadingScreen("Operazione terminata", "${baseUrl}/int/images/task.png",1000);
														form.dialog("close");
														//window.location.reload(true);
														
														window.location.assign("${baseUrl}/app/documents/detail/"+loadedElement.parentId+"#FeasibilityAreaME-tab2");
														
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
								$('.datePicker').datepicker({autoclose:true,  format: 'dd/mm/yyyy' });
								return false;
							}
						});
					}
				});
	}	
	
</@script>


