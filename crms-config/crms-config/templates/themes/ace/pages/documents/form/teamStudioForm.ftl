<#include "../helpers/MetadataTemplate.ftl"/>
<#include "../../../macros.ftl"/>
<#assign type=model['docDefinition']/>
<#assign templates={}/>
<#if type.ftlFormTemplate??>
	<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>

   


<@script>

				$('#document-form-submit').ready(function() {
					$('#DatiTeamDiStudio-DatiTeamDiStudio_NomeCognome').hide();
					$('#DatiTeamDiStudio-DatiTeamDiStudio_AltroPersonale').hide();
    			$('#DatiTeamDiStudio-DatiTeamDiStudio_attivitaDip1').hide();
    			$('#DatiTeamDiStudio-DatiTeamDiStudio_attivitaDip2').hide();
    			$('#DatiTeamDiStudio-DatiTeamDiStudio_attivitaNonDip1').hide();
    			$('#DatiTeamDiStudio-DatiTeamDiStudio_rapLavNonDip').hide();
    			$('#DatiTeamDiStudio-DatiTeamDiStudio_EnteNonDip').hide();
    			
    			a=$('[for=DatiTeamDiStudio_NomeCognome]').html().replace(":","")
					$('[for=DatiTeamDiStudio_NomeCognome]').html(a+"<sup style='color:red'>*</sup>:")
			    b=$('[for=DatiTeamDiStudio_AltroPersonale]').html().replace(":","")
					$('[for=DatiTeamDiStudio_AltroPersonale]').html(b+"<sup style='color:red'>*</sup>:")
    			
				});
				
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
				                                    		<#if field.type="RADIO">
						                                    	if ($('#${template.name}_${field.name}').is(':visible') && !$('[name=${template.name}_${field.name}]').is(':checked')){
						                                    	console.log("controllo campo obbligatorio ${template.name}_${field.name} di tipo ${field.type}");
				                                    		<#else>
				                                    			if ($('#${template.name}_${field.name}').is(':visible') && $('#${template.name}_${field.name}').val()==""){
				                                    			console.log("controllo campo obbligatorio ${template.name}_${field.name} di tipo ${field.type}");
				                                    		</#if>
				                                    				alert("Il campo ${label?html} deve essere compilato");
											    													$('#${template.name}_${field.name}').focus();
											    													return false;
											    												}
				                                    </#if>
				                                    
				                                    /*Controlli obbligatorieta' di campi condizionati ad hoc per questa scheda*/
				                                    if($('input[name=DatiTeamDiStudio_TipoPersonale]:checked').val().split("###")[0]=="1" && $('#DatiTeamDiStudio_NomeCognome').val()==""){
				                                    	alert("Il campo Nome e cognome deve essere compilato");
								    													$('#${template.name}_${field.name}').focus();
								    													return false;
				                                    }
				                                    if($('input[name=DatiTeamDiStudio_TipoPersonale]:checked').val().split("###")[0]=="2" && $('#DatiTeamDiStudio_AltroPersonale').val()==""){
				                                    	alert("Il campo Nome e cognome deve essere compilato");
								    													$('#${template.name}_${field.name}').focus();
								    													return false;
				                                    }
				                                    
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

<@script>

$('#DatiTeamDiStudio-DatiTeamDiStudio_NomeCognome').hide();
	$('#DatiTeamDiStudio-DatiTeamDiStudio_AltroPersonale').hide();
	$('#DatiTeamDiStudio-DatiTeamDiStudio_EnteNonDip').hide();
	$('#DatiTeamDiStudio-DatiTeamDiStudio_Struttura').hide();
	$('#DatiTeamDiStudio-DatiTeamDiStudio_Dipartimento').hide();
	$('#DatiTeamDiStudio-DatiTeamDiStudio_OspedalePresidio').hide();
	$('#DatiTeamDiStudio-DatiTeamDiStudio_UO').hide();

$('[name=DatiTeamDiStudio_TipoPersonale]').change(function(){
  if($('#DatiTeamDiStudio_TipoPersonale:checked', '#document-form').val()===undefined){
	  
  	$('#DatiTeamDiStudio-DatiTeamDiStudio_NomeCognome').hide();
	$('[id=DatiTeamDiStudio_NomeCognome]').val('');//se nascondo sbianco il valore!
	
	$('#DatiTeamDiStudio-DatiTeamDiStudio_AltroPersonale').hide();
	$('[id=DatiTeamDiStudio_AltroPersonale]').val('');//se nascondo sbianco il valore!
	
	$('#DatiTeamDiStudio-DatiTeamDiStudio_EnteNonDip').hide();
	$('[id=DatiTeamDiStudio_EnteNonDip]').val('');//se nascondo sbianco il valore!
	
	$('#DatiTeamDiStudio-DatiTeamDiStudio_Struttura').hide();
	$('[name=DatiTeamDiStudio_Struttura]').val('');//se nascondo sbianco il valore!
	$('[name=DatiTeamDiStudio_Struttura]').trigger('change');//se nascondo sbianco il valore!
	
	$('#DatiTeamDiStudio-DatiTeamDiStudio_Dipartimento').hide();
	$('[name=DatiTeamDiStudio_Dipartimento]').val('');//se nascondo sbianco il valore!
	$('[name=DatiTeamDiStudio_Dipartimento]').trigger('change');//se nascondo sbianco il valore!

	$('#DatiTeamDiStudio-DatiTeamDiStudio_OspedalePresidio').hide();
	$('[name=DatiTeamDiStudio_OspedalePresidio]').val('');//se nascondo sbianco il valore!
	$('[name=DatiTeamDiStudio_OspedalePresidio]').trigger('change');//se nascondo sbianco il valore!

	$('#DatiTeamDiStudio-DatiTeamDiStudio_UO').hide();
	$('[id=DatiTeamDiStudio_UO]').val('');//se nascondo sbianco il valore!
	
  }
  else{
	  if($('#DatiTeamDiStudio_TipoPersonale:checked', '#document-form').val().split('###')[0]=='1'){
	    
		$('#DatiTeamDiStudio-DatiTeamDiStudio_AltroPersonale').hide();
		$('[id=DatiTeamDiStudio_AltroPersonale]').val('');//se nascondo sbianco il valore!
		
	    $('#DatiTeamDiStudio-DatiTeamDiStudio_NomeCognome').show();
		
		$('#DatiTeamDiStudio-DatiTeamDiStudio_EnteNonDip').hide();
		$('[id=DatiTeamDiStudio_EnteNonDip]').val('');//se nascondo sbianco il valore!
		
		$('#DatiTeamDiStudio-DatiTeamDiStudio_Struttura').show();
		$('#DatiTeamDiStudio-DatiTeamDiStudio_Dipartimento').show();
		$('#DatiTeamDiStudio-DatiTeamDiStudio_OspedalePresidio').show();
		$('#DatiTeamDiStudio-DatiTeamDiStudio_UO').show();
	  }
	  if($('#DatiTeamDiStudio_TipoPersonale:checked', '#document-form').val().split('###')[0]=='2'){
		  
	    $('#DatiTeamDiStudio-DatiTeamDiStudio_AltroPersonale').show();
		
	    $('#DatiTeamDiStudio-DatiTeamDiStudio_NomeCognome').hide();
		$('[id=DatiTeamDiStudio_NomeCognome]').val('');//se nascondo sbianco il valore!
		
		$('#DatiTeamDiStudio-DatiTeamDiStudio_EnteNonDip').show();
		
		$('#DatiTeamDiStudio-DatiTeamDiStudio_Struttura').hide();
		$('[name=DatiTeamDiStudio_Struttura]').val('');//se nascondo sbianco il valore!
		$('[name=DatiTeamDiStudio_Struttura]').trigger('change');//se nascondo sbianco il valore!
		
		$('#DatiTeamDiStudio-DatiTeamDiStudio_Dipartimento').hide();
		$('[name=DatiTeamDiStudio_Dipartimento]').val('');//se nascondo sbianco il valore!
		$('[name=DatiTeamDiStudio_Dipartimento]').trigger('change');//se nascondo sbianco il valore!

		$('#DatiTeamDiStudio-DatiTeamDiStudio_OspedalePresidio').hide();
		$('[name=DatiTeamDiStudio_OspedalePresidio]').val('');//se nascondo sbianco il valore!
		$('[name=DatiTeamDiStudio_OspedalePresidio]').trigger('change');//se nascondo sbianco il valore!

		$('#DatiTeamDiStudio-DatiTeamDiStudio_UO').hide();
		$('[id=DatiTeamDiStudio_UO]').val('');//se nascondo sbianco il valore!
	  }
  }
});
$("#DatiTeamDiStudio-DatiTeamDiStudio_NomeCognome div.col-sm-9").removeClass("col-sm-9").addClass("col-sm-3")
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
            <label class="col-sm-3 control-label no-padding-right" for="data">Data<sup style="color:red">*</sup>:</label>
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

