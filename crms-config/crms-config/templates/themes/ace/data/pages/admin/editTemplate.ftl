
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
<#global breadcrumbs={"title":"Template ${model['template'].name}","links":[]} />
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
			"link":"${baseUrl}/app/admin/editTemplate/${model['template'].id?c}",
			"level_2":true,
			"title":"Tempi",
			"icon":{"icon":"fa fa-list","title":"Template ${model['template'].name}"}
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

         $('#field-form #type').change(function(){
             if ($(this).val()=='ELEMENT_LINK') {
             	$('#multiTypeSelector').show();
             	$('[for="multiTypeSelector"]').show();
             }
             else {
             	$('#multiTypeSelector').hide();
             	$('[for="multiTypeSelector"]').hide();
             }
             if ($(this).val()=='SELECT' || $(this).val()=='CHECKBOX' || $(this).val()=='RADIO' || $(this).val()=='ELEMENT_LINK'){
             	$('#availableValues').show();
             	$('[for="availableValues"]').show();
             }else {
             console.log("nascondo availableValues");
             	$('#availableValues').hide();
             	$('[for="availableValues"]').hide();
             }
             if ($(this).val()=='EXT_DICTIONARY' || $(this).val()=='ELEMENT_LINK'){
             	$('#externalDictionary').show();
             	$('[for="externalDictionary"]').show();
             	$('#addFilterFields').show();
             	$('[for="addFilterFields"]').show();
             }else {
             	$('#externalDictionary').hide();
             	$('[for="externalDictionary"]').hide();
             	$('#addFilterFields').hide();
             	$('[for="addFilterFields"]').hide();
             }
         });
         $('#template-form-submit').click(function(){
             loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
             var formData=new FormData($('#template-form')[0]);
             var actionUrl=$('#template-form').attr("action");
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
         field=new ajaXmrTab({
             elementName: "field",
             baseUrl: "${baseUrl}",
             listRow: fieldListRow,
             saveOrUpdateUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/saveField",
             getAllUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/getFields",
             getSingleElementUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/getField",
             deleteUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/deleteField",
             dialogWidth: "500px",
             listType: "tr",
             postSave: fieldPostSave,
             postClearForm: fieldPostClear
         });
         field.refreshList();

     function fieldPostClear(){
      if ($('#field-form #type').val()=='ELEMENT_LINK') {
             	$('#multiTypeSelector').show();
             	$('[for="multiTypeSelector"]').show();
             }
             else {
             	$('#multiTypeSelector').hide();
             	$('[for="multiTypeSelector"]').hide();
             }
             if ($('#field-form #type').val()=='SELECT' || $('#field-form #type').val()=='CHECKBOX' || $('#field-form #type').val()=='RADIO' || $('#field-form #type').val()=='ELEMENT_LINK'){
             	$('#availableValues').show();
             	$('[for="availableValues"]').show();
             	$('#addFilterFields').show();
             	$('[for="addFilterFields"]').show();
             }else {
             console.log("nascondo availableValues");
             	$('#availableValues').hide();
             	$('[for="availableValues"]').hide();
             }
             if ($('#field-form #type').val()=='EXT_DICTIONARY' || $('#field-form #type').val()=='ELEMENT_LINK'){
             	$('#externalDictionary').show();
             	$('[for="externalDictionary"]').show();
             	$('#addFilterFields').show();
             	$('[for="addFilterFields"]').show();
             }else {
             	$('#externalDictionary').hide();
             	$('[for="externalDictionary"]').hide();
             	$('#addFilterFields').hide();
             	$('[for="addFilterFields"]').hide();
             }
             
             
             
     }

     function fieldPostSave(){
        $('#startDateId').html("<option></option>");
        $('#endDateId').html("<option></option>");
     }

     function fieldListRow(jsonRow){
         if (jsonRow.type=="DATE" || jsonRow.type=="DATETIME"){
            <#if model['template'].startDateField??>
            if ('${model['template'].startDateField.id}'==jsonRow.id) {
                $('#startDateId').append("<option value=\""+jsonRow.id+"\" selected>"+jsonRow.name+"</option>");
            }
            else </#if>$('#startDateId').append("<option value=\""+jsonRow.id+"\">"+jsonRow.name+"</option>");
            <#if model['template'].endDateField??>
             if ('${model['template'].endDateField.id}'==jsonRow.id) {
                $('#endDateId').append("<option value=\""+jsonRow.id+"\" selected>"+jsonRow.name+"</option>");
            }
            else </#if>$('#endDateId').append("<option value=\""+jsonRow.id+"\">"+jsonRow.name+"</option>");
         }
         orderLink="";
         if (jsonRow.position>0) 
         	orderLink+=''+
         	'<a title="Sposta in testa" style="display: inline-block" href="#" onclick="moveTop('+jsonRow.id+');return false"><i class="fa fa-angle-double-up"></i> </a>&nbsp;'+
         	'<a title="Sposta su" style="display: inline-block" href="#" onclick="moveUp('+jsonRow.id+');return false"><i class="fa fa-angle-up"></i> </a>';
         orderLink+=''+
         	'<a title="Sposta giù" style="display: inline-block" href="#" onclick="moveDown('+jsonRow.id+');return false"><i class="fa fa-angle-down"></i> </a>&nbsp;'+
         	'<a title="Sposta alla fine" style="display: inline-block" href="#" onclick="moveBottom('+jsonRow.id+');return false"><i class="fa fa-angle-double-down"></i> </a>';
         return '<td>'+jsonRow.name+' ('+jsonRow.type+')</td><td>'+orderLink+'</td>';
     }
     
     function moveUp(idField){
     	$.ajax({
                 type: "GET",
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/field/"+idField+"/moveUp",
                 success: function(obj){
                     if (obj.result=="OK") {
                     	field.refreshList();    
                     }else {
                         alert("Errore");
                     }
                 },
                 error: function(){
                 	alert("Errore");
                 }
             });
     }
     
     function moveDown(idField){
     	$.ajax({
                 type: "GET",
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/field/"+idField+"/moveDown",
                 success: function(obj){
                     if (obj.result=="OK") {
                     	field.refreshList();    
                     }else {
                         alert("Errore");
                     }
                 },
                 error: function(){
                 	alert("Errore");
                 }
             });
     }
     
     function moveTop(idField){
     $.ajax({
                 type: "GET",
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/field/"+idField+"/moveTop",
                 success: function(obj){
                     if (obj.result=="OK") {
                     	field.refreshList();    
                     }else {
                         alert("Errore");
                     }
                 },
                 error: function(){
                 	alert("Errore");
                 }
             });
     }
     
     function moveBottom(idField){
     $.ajax({
                 type: "GET",
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id?c}/field/"+idField+"/moveBottom",
                 success: function(obj){
                     if (obj.result=="OK") {
                     	field.refreshList();    
                     }else {
                         alert("Errore");
                     }
                 },
                 error: function(){
                 	alert("Errore");
                 }
             });
     }

 </@script>