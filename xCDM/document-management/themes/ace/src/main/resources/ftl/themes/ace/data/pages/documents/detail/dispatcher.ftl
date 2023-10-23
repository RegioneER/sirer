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
			                                    		bootbox.alert("<@msgJs "js.Field"/> ${label?html} <@msgJs "js.isMandatory"/>",function(){
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
			        	bootbox.alert("<@msgJs "js.fileNeeded"/>",function(){
			        		setTimeout(function(){$('#file').focus();},0);
			        	});
			        	
						return false;
			        }
			        <#if !model['docDefinition'].noFileinfo>
			        if ($('#version').val()==""){
			        	bootbox.alert("<@msgJs "js.versionFieldNeeded"/>",function(){
			        		$('#version').focus();
			        	});
						
						return false;
			        }
			        if ($('#data').val()==""){
			        	bootbox.alert("<@msgJs "js.dataFieldNeeded"/>",function(){
			        		$('#data').focus();
			        	});
						
						return false;
			        }
			        </#if>
		        </#if>
			bootbox.dialog({
				message:'<i class="icon-spinner icon-spin"></i> <@msgJs "js.Saving"/> ',
				backdrop: true,
				closeButton: false
			});
			dummy=formToElement('document-form',dummy);
            saveElement(dummy).done(function(data){
            	bootbox.hideAll();
            	if (data.result=="OK") {
                    bootbox.alert('<@msgJs "js.SaveSuccess"/><i class="icon-ok green" ></i>');
                    if (data.redirect){
                        window.location.href=data.redirect;
                    }
                }else {
                	bootbox.alert('<@msgJs "js.SaveError"/><i class="icon-warning-sign red"></i>');
                }
            }).fail(function(){
            	bootbox.hideAll();
                bootbox.alert('<@msgJs "js.SaveError"/><i class="icon-warning-sign red"></i>');
           
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

<@defaultSidebar/>
