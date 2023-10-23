<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/form.css"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "common/elementEdit.js","base"],
	"inline_scripts":[],
	"title" : "Creazione nuovo oggetto",
 	"description" : "Scheda di inserimento" 
} />

<#include "../partials/form-elements/select.ftl" />

<#global breadcrumbs=
	{
		"title":"Creazione nuovo oggetto",
		"links":[]
	}
	/>

<#if model['parent']?? >
	<@breadcrumbsData model['parent'] page.title true />

</#if>
<#assign json=type.getDummyJson() />
<@script>
 	
 	var dummy=${json};
 	<#if model['parent']?? >
 	dummy.parent=${model['parent'].id};
 	</#if>
 	var empties=new Array();
 	empties[dummy.type.id]=dummy;
	

	  
	$('#document-form-submit').closest('.btn').click(function(){
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
				message:'<i class="icon-spinner icon-spin"></i> <@msgJs "js.Saving"/>',
				backdrop: true,
				closeButton: false
			});
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
                        bootbox.alert('<@msgJs "js.SaveSuccess"/><i class="icon-ok green" ></i>');
                        if (obj.redirect){

		                   window.location.href=obj.redirect;
		                   
                        }
                    }else {
                        bootbox.alert('<@msgJs "js.SaveError"/><i class="icon-warning-sign red"></i>');
                    }
                },
                error: function(){
                    bootbox.alert('<@msgJs "js.SaveError"/><i class="icon-warning-sign red"></i>');
                }
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

