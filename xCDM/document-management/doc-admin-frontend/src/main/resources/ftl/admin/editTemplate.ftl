<script>

     $(document).ready(function(){
         $('#field-form #type').change(function(){
             if ($(this).val()=='ELEMENT_LINK') {
             	$('#multiTypeSelector').show();
             	$('[for="multiTypeSelector"]').show();
             }
             else {
             	$('#multiTypeSelector').hide();
             	$('[for="multiTypeSelector"]').hide();
             }
             if ($(this).val()=='SELECT' || $(this).val()=='CHECKBOX' || $(this).val()=='RADIO'){
             	$('#availableValues').show();
             	$('[for="availableValues"]').show();
             }else {
             console.log("nascondo availableValues");
             	$('#availableValues').hide();
             	$('[for="availableValues"]').hide();
             }
             if ($(this).val()=='EXT_DICTIONARY'){
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
             listRow:fieldListRow,
             saveOrUpdateUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id}/saveField",
             getAllUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id}/getFields",
             getSingleElementUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id}/getField",
             deleteUrl: "${baseUrl}/app/rest/admin/template/${model['template'].id}/deleteField",
             dialogWidth: "500px",
             listType: "br",
             postSave: fieldPostSave,
             postClearForm: fieldPostClear
         });
         field.refreshList();
     });
     
     function fieldPostClear(){
      if ($('#field-form #type').val()=='ELEMENT_LINK') {
             	$('#multiTypeSelector').show();
             	$('[for="multiTypeSelector"]').show();
             }
             else {
             	$('#multiTypeSelector').hide();
             	$('[for="multiTypeSelector"]').hide();
             }
             if ($('#field-form #type').val()=='SELECT' || $('#field-form #type').val()=='CHECKBOX' || $('#field-form #type').val()=='RADIO'){
             	$('#availableValues').show();
             	$('[for="availableValues"]').show();
             }else {
             console.log("nascondo availableValues");
             	$('#availableValues').hide();
             	$('[for="availableValues"]').hide();
             }
             if ($('#field-form #type').val()=='EXT_DICTIONARY'){
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
         if (jsonRow.position>0) orderLink+='<a class="ui-icon ui-icon-arrowthickstop-1-n" title="Sposta in testa" style="display: inline-block" href="#" onclick="moveTop('+jsonRow.id+');return false">&nbsp;</a>&nbsp;<a class="ui-icon ui-icon-arrowthick-1-n" title="Sposta su" style="display: inline-block" href="#" onclick="moveUp('+jsonRow.id+');return false">%nbsp;</a>';
         orderLink+='<a class="ui-icon ui-icon-arrowthick-1-s" title="Sposta gi" style="display: inline-block" href="#" onclick="moveDown('+jsonRow.id+');return false">&nbsp;</a>&nbsp;<a class="ui-icon ui-icon-arrowthickstop-1-s" title="Sposta alla fine" style="display: inline-block" href="#" onclick="moveBottom('+jsonRow.id+');return false">%nbsp;</a>';
         return '<b>'+jsonRow.name+' ('+jsonRow.type+')'+orderLink;
     }
     
     function moveUp(idField){
     	$.ajax({
                 type: "GET",
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id}/field/"+idField+"/moveUp",
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
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id}/field/"+idField+"/moveDown",
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
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id}/field/"+idField+"/moveTop",
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
                 url: "${baseUrl}/app/rest/admin/template/${model['template'].id}/field/"+idField+"/moveBottom",
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

 </script>

 <div class="mainContent">
<div class="documentMainContent">
    <a class="link-back" href="${baseUrl}/app/admin">Home Page - Console amministrazione</a>
    <br/>

    <fieldset>
          <div class="floatbox-right"/>
        <fieldset>
            <legend>Campi</legend>
            <input class="submitButton round-button blue" type="button" value="Aggiungi campo" id="add-field" name="add-field"/>
            <div id="field-list-availables">
            </div>
        </fieldset>
        </div>
        <legend>Template ${model['template'].name}</legend>
     <div style="display: inline-block">

        <form id="template-form" method="POST" action="${baseUrl}/app/rest/admin/template/save" enctype="multipart/form-data">
        <@hidden "id" "id" model['template'].id/>
            <div class="field-component">
            <@textbox "name" "name" "Nome" model['template'].name 40/>
            </div>
            <div class="field-component">
            <@textarea "description" "description" "Descrizione" 40 3 model['template'].description/>
            </div>
            <div class="field-component">
            <#if model['template'].auditable?? && model['template'].auditable>
                <#assign auditable= ["1"]>
            </#if>
            <@checkBox "auditable" "auditable" "Auditable" {"1":""} auditable />
            </div>
            <div class="field-component">
            <#if model['template'].calendarized?? && model['template'].calendarized>
                <#assign calendarized= ["1"]>
            </#if>
            <@checkBox "calendarized" "calendarized" "Calendarizzato" {"1":""} calendarized />
            </div>
            <div class="field-component">
            <@textbox "calendarName" "calendarName" "Nome calendario" model['template'].calendarName 40/>
            </div>
            <div class="field-component">
            <@colorpicker "calendarColor" "calendarColor" "Colore calendario" model['template'].calendarColor/>
            </div>
            <div class="field-component">
            <@selectHash "startDateId" "startDateId" "Start Date Field"/>
            </div>
            <div class="field-component">
            <@selectHash "endDateId" "endDateId" "End date Field" />
            </div>
            <div class="field-component">
            <#if model['template'].wfManaged?? && model['template'].wfManaged>
                <#assign wfManaged= ["1"]>
            </#if>
            <@checkBox "wfManaged" "wfManaged" "Controllato da Workflow" {"1":""} wfManaged />
            </div>
            
            
            <input class="round-button blue" type="button" value="Salva" id="template-form-submit"/>
        </form>
</div>


        <div id="field-dialog" title="Aggiungi template">
            <fieldset>
                <form id="field-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
                <@hidden "id" "id" />
                    <div class="field-component">
                <@textbox "name" "name" "Nome" "" 40/>
                    </div>
                    <div class="field-component">
                <@selectHash "type" "type" "Tipo" {"TEXTBOX":"textbox","TEXTAREA":"textarea","DATE":"data","SELECT":"Select","RADIO":"radio","CHECKBOX":"Check", "ELEMENT_LINK":"collegamento elemento", "EXT_DICTIONARY": "Dizionario Esterno"}/>
                    </div>
                    <div id="multiTypeSelector" class="field-component" style="display: none">
                <@multiAutoCompleteFB "typefilters" "typefilters" "Tipi di elementi collegati" "${baseUrl}/app/rest/admin/type/searchElType" "typeId" null "id"/><br/>
                    </div>
                    <div class="field-component">
                <@checkBox "mandatory" "mandatory" "Obbligatorio" {"true":""}/>
                    </div>
                    <div class="field-component">
                <@textarea "availableValues" "availableValues" "Valori possibili"  />
                <@textbox "externalDictionary" "externalDictionary" "Script esterno"  />
                <@textbox "addFilterFields" "addFilterFields" "Filtri aggiuntivi"  />
            </div>

                    <input class="round-button blue" type="button" value="Salva" id="field-form-submit"/>
                </form>

            </fieldset>
        </div>
    </fieldset>
</div>
 </div>