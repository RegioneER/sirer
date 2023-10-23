<script>
    $(document).ready(function(){
        $('#document-form-submit').click(function(){
            loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
            var formData=new FormData($('#document-form')[0]);
            var actionUrl=$('#document-form').attr("action");
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
    });
    
      function valueOfField(idField){
      	console.log("valueOfField - "+idField);
    	console.log(idField);
    	field=$('#'+idField);
    	 if (field.attr('istokeninput')=='true'){
			value=field.tokenInput("get");
			console.log(value);
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
    

</script>
<div class="mainContent">
<form id="document-form" method="POST" action="${baseUrl}/app/rest/documents/save/${model['docDefinition'].id}" enctype="multipart/form-data">
    <fieldset>
        <legend>Crea ${model['docDefinition'].typeId}</legend>
        <#if model['parentId']??>
        <@hidden "parentId" "parentId" model['parentId']/>
        </#if>
        <#if model['docDefinition'].enabledTemplates?? && model['docDefinition'].enabledTemplates?size gt 0>
            <#list model['docDefinition'].enabledTemplates as template>
                    <#if template.fields??>
                            <#list template.fields as field>
                                    <@mdfield template field/>
                            </#list>
                    </#if>
            </#list>
        </#if>
        <#if model['docDefinition'].hasFileAttached>
        <div class="field-component" id="version">
            <label for="version">Versione:</label><input type="text" name="version" id="version"/>
        </div>
        <div class="field-component" id="version">
            <label for="data">Data:</label><input type="text" name="data" class="datePicker hasDatepicker" id="data"/><br/>
        </div>
        <div class="field-component" id="version">
            <label for="autore">Autore:</label><input type="text" name="autore" id="autore"/><br/>
        </div>
        <div class="field-component" id="version">
            <label for="note">Note:</label><textarea name="note" id="note"></textarea><br/>
        </div>
        <div class="field-component">
        <@fileChooser "file" "file" "File allegato"/>
        </div>
        </#if>
        <input class="submitButton round-button blue" type="button" value="Salva" id="document-form-submit" name="document-form-submit"/>
    </fieldset>

</form>
</div>