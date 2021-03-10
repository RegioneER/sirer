<#assign type=model['docDefinition']/>
<#assign templates={}/>
<#if type.ftlFormTemplate??>
	<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>

   


<@script>
        $('#document-form-submit').off('click').on('click',function(){
            var formData=new FormData($('#document-form')[0]);
            var actionUrl=$('#document-form').attr("action");
               
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
                           //alert('redirect?');
                           window.location.href='${baseUrl}/app/documents/detail/${model['parent'].getId()}<#if model['docDefinition'].hashBack?? >#${model['docDefinition'].hashBack}</#if>';
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

<form class="form-horizontal" id="document-form" method="POST" action="${baseUrl}/app/rest/documents/save/${model['docDefinition'].id}" onsubmit="return false;" enctype="multipart/form-data">
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
        <#--
        Modifica versioning per CTC gemelli CRPMS-156
        
        <div class="form-group field-component field-editable" id="file_version">
            <label class="col-sm-3 control-label no-padding-right" for="version">Versione<sup style="color:red">*</sup>:</label>
            <div class="col-sm-9">
            	<input type="text" name="version" id="version"/>
            </div>
        </div>
        -->
        <input type="hidden" name="version" value="auto"/>
        <div class="form-group field-component field-editable" id="file_data">
            <label class="col-sm-3 control-label no-padding-right" for="data">Data relazione (gg/mm/yyyy)<sup style="color:red">*</sup>:</label>
            <div class="col-sm-9">
            	<input type="text" name="data" class="datePicker" id="data"/>
	            <@script>
	            	$('#data').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
	            </@script>
	        </div>
        </div>
        <div class="form-group field-component field-editable" id="file_autore">
            <label class="col-sm-3 control-label no-padding-right" for="autore">Autore:</label>
            <div class="col-sm-9">
            	<input type="text" name="autore" id="autore"/>
            </div>
        </div>
        <div class="form-group field-component field-editable" id="file_node">
            <label class="col-sm-3 control-label no-padding-right" for="note">Note:</label>
            <div class="col-sm-9">
            	<textarea name="note" id="note"></textarea>
            </div>
        </div>
        </#if>
        <div class="form-group field-component field-editable">
        <@fileChooser "file" "file" getLabel(model['docDefinition'].typeId+".fileLabel")+"<sup style='color:red'>*</sup>"/>
        </div>
        </#if>
        <div class="clearfix"></div>
        <button class="btn btn-warning submitButton" id="document-form-submit" name="document-form-submit"><i class="icon-save bigger-160"></i><b>Salva</b></span>
		</button>

</form>
</div>

