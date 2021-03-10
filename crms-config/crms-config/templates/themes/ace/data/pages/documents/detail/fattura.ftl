<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
	"inline_scripts":[],
	"title" : "Dettaglio fattura",
 	"description" : "Dettaglio fattura" 
} />
<#assign elStudio=el.getParent().getParent().getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />

<@script>

var sidebarDefault="${el.getParent().getParent().getParent().getId()}#Fatturazione-tab2";

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
                                 
                                 //GC 20-12-13// Commento perch??? printa il message nella task-form (chiss??? qual'era la ratio...)
                                 //if (variables[v].name=='message' && variables[v].value!=null){
                                 //    form.append("<b>"+variables[v].value+"</b>");
                                 //}
                                 
                             }
                             for (f=0;f<data.formProperties.length;f++){
                                 value="";    
                                 required=data.formProperties[f].required;
                                 addClass="";
                                 if (required) addClass="required";
                                 if (data.formProperties[f].value!=null) value=data.formProperties[f].value
                                 if (data.formProperties[f].type=="string"){
                                 
                                     if(data.formProperties[f].id.indexOf("note")==0 || data.formProperties[f].id.indexOf("Note")==0){
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
                                                     loadingScreen("Operazione effettuata con successo", "${baseUrl}/int/images/task.png",1000);
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
                                 	$(this).find('.datePicker').datepicker('setDate',new Date());
                                 	$(this).find('.datePicker').blur();
                                 }
                                 });
                             form.dialog("open");
                             
                             return false;
                         }
                     });
                 }
             });
 }   

 	console.log("Sono in fattura.js.ftl: - ready");
 	
	mioArray = new Array();
	mioArray2 = new Array();
	mioArray3 = new Array();
	$("td[id^='idGruppo']").each(function(){
		var gruppo=$(this).attr("id");
		var tdidVal=$("#"+gruppo).html();
		var identificativo=gruppo.split("_")[1];
		
		//raggruppo anche le prestazioni con lo stesso nome
		if(tdidVal==''){tdidVal=$("#idDescr_"+identificativo).html();}
		
		
		var economico=$("#totale3_"+identificativo).html();
		var rimborsabile=$("#idRimbo_"+identificativo).html()=="si" ? true : false;
		var attivita=$("#idAtt_"+identificativo).html();
		//console.log(tdidVal+gruppo);
		
		if(!mioArray[tdidVal]){
			mioArray[tdidVal]=0;
			mioArray2[tdidVal]=0;
			mioArray3[tdidVal]="";
		}
		
		if(rimborsabile){mioArray2[tdidVal]+=parseFloat(economico);}
		
		mioArray[tdidVal]+=parseFloat(economico);
		mioArray3[tdidVal]=attivita;
		$("#riga_"+identificativo).remove();
		
	});
	
	$("#table_prest").find("tr th:nth-child(3)").remove();
	$("#table_prest").find("tr td:nth-child(3)").remove();
	
	console.log(mioArray);

	for (var key in mioArray) {
		console.log(key);
		$("#table_prest").append("<tr><td>"+key+"</td><td >"+mioArray3[key]+"</td><td style='text-align:right;'>"+mioArray2[key].formatMoney()+"</td><td style='text-align:right;'>"+mioArray[key].formatMoney()+"</td></tr>");
		}
	
	
$("td[id^='totale']").each(function(){
			var tdid=$(this).attr("id");
			var prezzoPrestazioni=$("#"+tdid).html();
			if(prezzoPrestazioni) {prezzoPrestazioni=prezzoPrestazioni.formatMoney();}
			$("#"+tdid).html(prezzoPrestazioni);
		});
	
		$("span[id^='importoTotale']").each(function(){
		var tdid=$(this).attr("id");
		var prezzoPrestazioni=$("#"+tdid).html();
		if(prezzoPrestazioni) {prezzoPrestazioni=prezzoPrestazioni.formatMoney();}
		$("#"+tdid).html(prezzoPrestazioni);
	});
	
	function executeConfirmTask(taskId,domElement){	
		
		if (confirm("Sei sicuro di voler procedere?")){
			$(domElement).addClass('disabled');
			loadingScreen("Invio in corso", "loading");
			data=new Object();
			data['taskId']=taskId;
			$.ajax({
				type: "POST",
				contentType: "application/json; charset=utf-8",
				url: "${baseUrl}/app/rest/documents/submitTask/"+taskId,
				success: function(data, textStatus, xhr){
					if (xhr.status==200){
						jQuery.ajaxSetup({ cache: true });
						$.ajax({
                             type: "GET",
                             url: "${baseUrl}/app/rest/documents/advancedSearchDictionary/Ribaltamento?parent_obj_id_eq=${el.id}",
                             
                             contentType:false,
                             processData:false,
                             async:false,
                             cache:false,
                              success: function(obj){
                                  console.log(obj);
                                 if(obj && obj[0] && obj[0].id)location.href='${baseUrl}/app/documents/detail/'+obj[0].id;
                                 else{
                                 	location.reload(true);
                                 }
                             }
                         });
					}else alert("Errore!!!");
				}
			});	
		}
	}	

	
function update(id,metadata){
		return $.ajax({
  	method : 'POST',
  	async : false,
  	url : '../../rest/documents/update/' + id,
  	data : metadata
 		});
	}
	
function SetCheckPrestFatt(){
$(':checkbox[name=DatiSchedulingFattura_Fatturato]').each(function(){
				var metadata={};
				metadata[this.name]='';
				
				metadata[this.name]=this.checked ? 1 : '';
				
				var identificativo=this.id.split('_')[1];
				
				console.log('DatiSchedulingFattura_Fatturato');
				update(identificativo, metadata);
			});		
}

	
</@script>
