<@script>
  $('#document-form-submit').closest('.btn').off('click');
  $('#document-form-submit').off('click').on('click',function(){

  
  <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
		<#list type.associatedTemplates as assocTemplate>
			<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
			
			<#if assocTemplate.enabled && templatePolicy.canCreate>
				<#assign template=assocTemplate.metadataTemplate/>
				
				<#if template.fields??>
				
					<#list template.fields as field>
						<#if field.mandatory>
					  	<#assign label=getLabel(template.name+"."+field.name)/>
					  		if ($('#${template.name}_${field.name}').val()==""){
					  	  	alert("Il campo ${label?html} deve essere compilato");
	    						$('#${template.name}_${field.name}').focus();
	    						return false;
					  	  }
					  </#if>
				  </#list>
				  
				</#if>
						
		  </#if>
		
		</#list>
	</#if>
	
	<#if model['docDefinition'].hasFileAttached>
	  if ($('#file').val()==""){
	  	alert("Bisogna allegare un file");
	  	$('#file').focus();
			return false;
	  }
		
		<#if !model['docDefinition'].noFileinfo>
		  if ($('#version').val()==""){
		  	alert("Il campo versione deve essere compilato");
				$('#version').focus();
				return false;
		  }
		  if ($('#data').val()==""){
		  	alert("Il campo data deve essere compilato");
				$('#data').focus();
				return false;
		  }
		</#if>
		
	</#if>
	$("select[id*='-select']").remove();//TOSCANA-204 elimino elementi -select e -altro per non far triplicare i dati in banca dati
	$("input[id*='-altro']").remove();

	var formData=new FormData($('#document-form')[0]);
	var actionUrl=$('#document-form').attr("action");
var parentId=$("#parentId").val();
loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
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
                  window.location.href="${baseUrl}/app/documents/detail/"+parentId+"#finanziatori-tab";
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

</@script>



<div class="mainContent">
<form class="form-horizontal" id="document-form" method="POST" action="${baseUrl}/app/rest/documents/save/${model['docDefinition'].id}" enctype="multipart/form-data">
    <h2><@msg "type.create."+model['docDefinition'].typeId/></h2>
        <#if model['parentId']??>
        <@hidden "parentId" "parentId" model['parentId']/>
        </#if>
        <#assign type=model['docDefinition']/>
        <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
	    <#list type.associatedTemplates as assocTemplate>
		<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
		<#if assocTemplate.enabled && templatePolicy.canCreate>
			<#assign template=assocTemplate.metadataTemplate/>
			<#if template.fields??>
                            <#list template.fields as field>
                                <div class="form-group field-component field-editable" id="file_data">
                                    <@mdfield template field/>
                            	 </div>
                            </#list>
                         </#if>
			
	        </#if>
	    </#list>
	</#if>
        
        <#if model['docDefinition'].hasFileAttached>
        <#if !model['docDefinition'].noFileinfo>
        <div class="field-component" id="file_version">
            <label for="version">Versione<sup style="color:red">*</sup>:</label>
            <input type="text" name="version" id="version"/>
        </div>
        <div class="form-group field-component" id="file_data">
            <label for="data">Data<sup style="color:red">*</sup>:</label><input type="text" name="data" class="datePicker" id="data"/>
            <@script>
            	$('#data').datepicker({autoclose:true,  format: 'dd/mm/yyyy' });
            </@script>
        </div>
        <div class="form-group field-component" id="file_autore">
            <label for="autore">Autore:</label><input type="text" name="autore" id="autore"/><br/>
        </div>
        <div class="form-group field-component" id="file_node">
            <label for="note">Note:</label><textarea name="note" id="note"></textarea><br/>
        </div>
        </#if>
        <div class="form-group field-component">
        <@fileChooser "file" "file" getLabel(model['docDefinition'].typeId+".fileLabel")+"<sup style='color:red'>*</sup>"/>
        </div>
        </#if>
        <button class="submitButton round-button blue btn btn-warning" type="button" id="document-form-submit" name="document-form-submit"/>
    		<i class="icon-save bigger-160"></i><b>Salva</b>
    	</button>
    	
    </fieldset>

</form>
</div>