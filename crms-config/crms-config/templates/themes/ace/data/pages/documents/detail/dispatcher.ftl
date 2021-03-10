<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "common/elementEdit.js","token-input"],
	"inline_scripts":[newInlineScript],
	"title" : "Dettaglio studio",
 	"description" : "Dettaglio studio" 
} />

<@breadcrumbsData model['element'] page.description />



<#assign json=type.getDummyJson() />
<@script>
 
 	var dummy=${json};
 	var empties=new Array();
 	empties[dummy.type.id]=dummy;
	
	
	  
	$('#document-form-submit').closest('.btn').click(function(){
	     
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
			                                    		bootbox.alert("Il campo ${label?html} deve essere compilato",function(){
			                                    			setTimeout(function(){$('#${template.name}_${field.name}').focus();},0);
			                                    		});
														
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
			        	bootbox.alert("Bisogna allegare un file",function(){
			        		setTimeout(function(){$('#file').focus();},0);
			        	});
			        	
						return false;
			        }
			        <#if !model['docDefinition'].noFileinfo>
			        if ($('#version').val()==""){
			        	bootbox.alert("Il campo versione deve essere compilato",function(){
			        		$('#version').focus();
			        	});
						
						return false;
			        }
			        if ($('#data').val()==""){
			        	bootbox.alert("Il campo data deve essere compilato",function(){
			        		$('#data').focus();
			        	});
						
						return false;
			        }
			        </#if>
		        </#if>
            bootbox.alert('Salvataggio in corso <i class="icon-spinner icon-spin"></i>');
            dummy=formToElement('document-form',dummy);
            saveElement(dummy).done(function(data){
            	bootbox.hideAll();
            	if (data.result=="OK") {
                    bootbox.alert('Salvataggio effettuato <i class="icon-ok green" ></i>');
                    if (data.redirect){
                        window.location.href=data.redirect;
                    }
                }else {
					var errorMessage="Errore salvataggio! <i class='icon-warning-sign red'></i>";
					if(data.errorMessage.includes("RegexpCheckFailed: ")){
						var campoLabel="";
						campoLabel=data.errorMessage.replace("RegexpCheckFailed: ","");
						campoLabel=messages[campoLabel];
						errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
					}
					bootbox.alert(errorMessage);
                }
            }).fail(function(){
            	bootbox.hideAll();
                bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
           
            });
            
       
    });
    
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
	
</@script>
