<#--Controlliamo che il template sia abilitato e l'utente possa visualizzarlo-->
<#function viewableTemplate templateName el userDetails>
	<#assign ret=false/>
	<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    	<#list el.elementTemplates as elementTemplate>
    		<#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled>
    			<#assign ret=true/>
    		</#if>
    	</#list>
    </#if>
    <#return ret/>
</#function>

<#--Controlliamo che il template sia abilitato e l'utente possa visualizzarlo-->
<#function getTemplate templateName el userDetails>
	<#assign ret=null/>
	<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    	<#list el.elementTemplates as elementTemplate>
    		<#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled>
    			<#assign ret=elementTemplate/>
    		</#if>
    	</#list>
    </#if>
    <#return ret/>
</#function>

<#macro TemplateForm templateName el userDetails editable classes="" >
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	<#assign groupActive=false />
    <#list el.elementTemplates as elementTemplate>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    		<#assign template=elementTemplate.metadataTemplate/>
        	<div id="metadataTemplate-${template.name}" class="row ${classes}">
        	<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
        	<form class="template-form" name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
        	</#if>
        	<#list template.fields as field>
                <#assign vals=[]/>
                <#assign fieldEditable=(editable && templatePolicy.canCreate)/>
                <#list el.data as data>
                    
                    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
                    <#if data.template.id=template.id && data.field.id=field.id >
                        <#assign vals=data.getVals()/>
                    </#if>
                </#list>
                <#assign audit=[]/> 
                <#list el.auditData as auditData>
                    <#if auditData.field.id==field.id>
                        <#assign audit=audit+[auditData]/>
                    </#if>
                </#list>
                <#assign id=template.name+"_"+field.name/>
                <#assign label>
                <@msg template.name+"."+field.name/>
                </#assign>
                <#if !groupActive >
                <div class="col-sm-12 field-component <#if fieldEditable>edit-mode<#else>view-mode</#if>" id="informations-${id}">
                <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}<#if field.mandatory><sup style="color:red">*</sup></#if>:</label>
                </#if>
                <#if fieldEditable>
	                <#assign empty=[] />
	                <@stdField template field vals true  empty false />
		        <#else>
		        	<@stdField template field vals false  empty false />
		        </#if>
	        <#if !groupActive >
                </div>
            </#if>
            </#list>
            <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
            <@script>
            $("[name=salvaForm-${template.name}]").on('click',function(){
                $('select').trigger('change'); //$('.select2-offscreen').change();
            	var $form=$($(this).data('rel'));
            	if($(this).attr('id')){
            		var formName=$(this).attr('id').replace("salvaForm-", "");
            	}else{formName="formNonEsistente"}
            	<#list template.fields as field>
                    <#if field.mandatory>
                    	<#assign label=getLabel(template.name+"."+field.name)/>
                    	var $input=$form.find('#${template.name}_${field.name}');
                    	if ($input.val()==""){
                    		bootbox.alert("Il campo ${label?html} deve essere compilato",function(){
                    			setTimeout(function(){$input.focus();},0);
                    		});
							
							return false;
                    	}
                    </#if>
                </#list>
                var goon=true;
                if (eval("typeof "+formName+"Checks == 'function'")){
									eval("goon="+formName+"Checks()");
								}
								if (!goon) return false;
                loadingScreen("Salvataggio in corso...", "loading");
                
	            try{
		            var myElement={};
		            myElement.id=loadedElement.id;
		            myElement.type=loadedElement.type;
		            myElement.metadata={};
		            myElement=formToElement($form,myElement,'${template.name}');
		            saveElement(myElement).done(function(data){
		            	bootbox.hideAll();
		            	if (data.result=="OK") {
		            	   loadingScreen("Salvataggio effettuato", "green_check");
		                    
												
												//Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
					            	window.setTimeout(function(){
											    bootbox.hideAll();
												}, 3000);
		                    
		                    if (data.redirect){
		                        window.location.href=data.redirect;
		                    }
		                }else {
		                	loadingScreen("Errore salvataggio!", "alerta");
		                	
		                }
		            }).fail(function(){
		            	bootbox.hideAll();
		            	loadingScreen("Errore salvataggio!", "alerta");
		                
		           
		            });
		         }catch(err){
		         	bootbox.hideAll();
		            loadingScreen("Errore salvataggio!", "alerta");
		            console.log(err);
		         }
            });
            </@script>
            	<div class="clearfix"></div>
            	 <button id="salvaForm-${template.name}" class="btn btn-xs btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save"></i> Salva</span>
											</button>
            	</form>
            </#if>
        </div>
        </#if>
    </#list>
</#if>
</#macro>

<#macro SingleFieldLabel templateName fieldName mandatory=false >
	<#assign id=templateName+"_"+fieldName/>
	<#assign label>
    <@msg templateName+"."+fieldName/>
    </#assign>

	<label for="${id}">${label}<#if mandatory><sup style="color:red">*</sup></#if>:</label>
</#macro>

<#macro SingleField templateName fieldName el userDetails editable>
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#list el.elementTemplates as elementTemplate>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    		<#assign template=elementTemplate.metadataTemplate/>
        	<#list template.fields as field>
        		<#if field.name=fieldName>
				<#assign vals=[]/>
				<#assign fieldEditable=(editable && templatePolicy.canCreate)/>
				<#list el.data as data>
				    
				    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
				    <#if data.template.id=template.id && data.field.id=field.id >
					<#assign vals=data.getVals()/>
				    </#if>
				</#list>
				<#assign audit=[]/> 
				<#list el.auditData as auditData>
				    <#if auditData.field.id==field.id>
					<#assign audit=audit+[auditData]/>
				    </#if>
				</#list>
				<#assign id=templateName+"_"+fieldName/>
				<div class="field-component view-mode" id="informations-${id}">
				
				<#if !(groupActive?? && groupActive)>	
					<@SingleFieldLabel template.name field.name field.mandatory />
				</#if>
				
				<#if fieldEditable>
					
					<@mdfield template field vals false true audit/>
				<#else>
					<@viewFieldNoLabel template field vals false true/>
				</#if>
				</div>
			</#if>
            </#list>
            
        </#if>
    </#list>
</#if>
</#macro>

<#macro SingleFieldNoLabel templateName fieldName el userDetails editable>
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#list el.elementTemplates as elementTemplate>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    		<#assign template=elementTemplate.metadataTemplate/>
        	<div id="metadataTemplate-${template.name}">
        	<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
        	<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
        	</#if>
        	<#list template.fields as field>
        		<#if field.name=fieldName>
				<#assign vals=[]/>
				<#assign fieldEditable=(editable && templatePolicy.canCreate)/>
				<#list el.data as data>
				    
				    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
				    <#if data.template.id=template.id && data.field.id=field.id >
					<#assign vals=data.getVals()/>
				    </#if>
				</#list>
				<#assign audit=[]/> 
				<#list el.auditData as auditData>
				    <#if auditData.field.id==field.id>
					<#assign audit=audit+[auditData]/>
				    </#if>
				</#list>
				<#assign id=template.name+"_"+field.name/>
				<#assign label>
                <@msg template.name+"."+field.name />
                </#assign>

				<div class="field-component view-mode" id="informations-${id}">
				<#if fieldEditable>
					<@mdfield template field vals false true/>
				<#else>
					<@viewFieldNoLabel template field vals false true/>
				</#if>
				</div>
			</#if>
            </#list>
            
        </div>
        </#if>
    </#list>
</#if>
</#macro>

<#macro SingleFieldByTypeNoLabel templateName fieldName type userDetails editable>
	<#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
	    <#list type.associatedTemplates as assocTemplate>
		<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
		<#if assocTemplate.enabled && templatePolicy.canCreate>
			<#assign template=assocTemplate.metadataTemplate/>
			<#assign nullArray=[]/>
			<#if template.fields??>
                            <#list template.fields as field>
								<#if field.name==fieldName>
									<@stdField template field nullArray editable nullArray false/>
								</#if>
							 </#list>
                         </#if>
	        </#if>
	    </#list>
	</#if>
</#macro>

<#macro SingleFieldByType templateName fieldName type userDetails editable>
	<#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
	    <#list type.associatedTemplates as assocTemplate>
		<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
		<#if assocTemplate.enabled && templatePolicy.canCreate>
			<#assign template=assocTemplate.metadataTemplate/>
			<#assign nullArray=[]/>
			<#if template.fields??>
                            <#list template.fields as field>
                            	<#if field.name==fieldName>
									<@stdField template field nullArray editable nullArray true/>
							 	</#if>
							 </#list>
                         </#if>
	        </#if>
	    </#list>
	</#if>
</#macro>

<#macro TemplateFormFastUpdate templateName el userDetails editable>
			
	<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	    <#list el.elementTemplates as elementTemplate>
		<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
		<#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
			<#assign template=elementTemplate.metadataTemplate/>
			<div id="metadataTemplate-${template.name}" class="form-horizontal">
			<#list template.fields as field>
			<#assign vals=[]/>
			<#assign fieldEditable=(editable && templatePolicy.canCreate)/>
			<#list el.data as data>
			    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
			    <#if data.template.id=template.id && data.field.id=field.id >
				<#assign vals=data.getVals()/>
			    </#if>
			</#list>
			<#assign audit=[]/> 
			<#list el.auditData as auditData>
			    <#if auditData.field.id==field.id>
				<#assign audit=audit+[auditData]/>
			    </#if>
			</#list>
			<#assign id=template.name+"_"+field.name/>
			<#assign label>
            <@msg template.name+"."+field.name />
            </#assign>
			<#if fieldEditable>
				<@mdFieldDetail template field vals fieldEditable audit/>
			<#else>
				<@mdFieldDetail template field vals false/>
			</#if>
			
		    </#list>
		    
		</div>
		</#if>
	    </#list>
	</#if>
</#macro>

<#macro SingleFieldFastUpdate templateName fieldName el userDetails editable>
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	    <#list el.elementTemplates as elementTemplate>
		<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
		<#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
			<#assign template=elementTemplate.metadataTemplate/>
			<#list template.fields as field>
			<#if field.name=fieldName>
				<#assign vals=[]/>
				<#assign fieldEditable=(editable && templatePolicy.canCreate)/>
				<#list el.data as data>
				    
				    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
				    <#if data.template.id=template.id && data.field.id=field.id >
					<#assign vals=data.getVals()/>
				    </#if>
				</#list>
				<#assign audit=[]/> 
				<#list el.auditData as auditData>
				    <#if auditData.field.id==field.id>
					<#assign audit=audit+[auditData]/>
				    </#if>
				</#list>
				<#assign id=template.name+"_"+field.name/>
				<#assign label>
                <@msg template.name+"."+field.name />
                </#assign>
				<#if fieldEditable>
					<@mdFieldDetail template field vals fieldEditable audit/>
				<#else>
					<@mdFieldDetail template field vals false/>
				</#if>
			</#if>
		    </#list>
		    
		</#if>
	    </#list>
	</#if>
</#macro>

<#macro SingleFieldFastUpdateNoLabel templateName fieldName el userDetails editable>
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
	    <#list el.elementTemplates as elementTemplate>
		<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
		<#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
			<#assign template=elementTemplate.metadataTemplate/>
			<#list template.fields as field>
			<#if field.name=fieldName>
				<#assign vals=[]/>
				<#assign fieldEditable=(editable && templatePolicy.canCreate)/>
				<#list el.data as data>
				    
				    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
				    <#if data.template.id=template.id && data.field.id=field.id >
					<#assign vals=data.getVals()/>
				    </#if>
				</#list>
				<#assign audit=[]/> 
				<#list el.auditData as auditData>
				    <#if auditData.field.id==field.id>
					<#assign audit=audit+[auditData]/>
				    </#if>
				</#list>
				<#assign id=template.name+"_"+field.name/>
				<#assign label>
                <@msg template.name+"."+field.name />
                </#assign>
				<#if fieldEditable>
					<@mdFieldDetail template field vals fieldEditable audit false/>
				<#else>
					<@mdFieldDetail template field vals false null false/>
				</#if>
			</#if>
		    </#list>
		    
		</#if>
	    </#list>
	</#if>
</#macro>



<#macro SingleFieldTd_old templateName fieldName el userDetails editable >
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#list el.elementTemplates as elementTemplate>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    		<#assign template=elementTemplate.metadataTemplate/>
        	<#list template.fields as field>
        		<#if field.name=fieldName>
				<#assign vals=[]/>
				<#assign fieldEditable=(editable && templatePolicy.canCreate)/>
				<#list el.data as data>
				    
				    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
				    <#if data.template.id=template.id && data.field.id=field.id >
					<#assign vals=data.getVals()/>
				    </#if>
				</#list>
				<#assign audit=[]/> 
				<#list el.auditData as auditData>
				    <#if auditData.field.id==field.id>
					<#assign audit=audit+[auditData]/>
				    </#if>
				</#list>
				<#assign id=templateName+"_"+fieldName/>
							<div class="field-component view-mode" id="informations-${id}">
								<tr id="tr-label-${id}">
									<td id="td-label-${id}">
										<#if !(groupActive?? && groupActive)>
											<@SingleFieldLabel template.name field.name field.mandatory />
										</#if>
									</td>
									<#if fieldEditable>
										<td id="td-field-${id}">
											<@mdfield template field vals false true audit/>
										</td>
									<#else>
										<td id="td-field-view-${id}">
											<@viewFieldNoLabel template field vals false true/>
										</td>
									</#if>
								</tr>
							</div>
			</#if>
            </#list>
            
        </#if>
    </#list>
</#if>
</#macro>


<#macro SingleFieldTd templateName fieldName el userDetails editable >
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#list el.elementTemplates as elementTemplate>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
        	<#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
            <#assign template=elementTemplate.metadataTemplate/>
            <#list template.fields as field>
                <#if field.name=fieldName>
                <#assign vals=[]/>
                <#assign fieldEditable=(editable && templatePolicy.canCreate)/>
                <#list el.data as data>
                   
                    <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
                    <#if data.template.id=template.id && data.field.id=field.id >
                    <#assign vals=data.getVals()/>
                    </#if>
                </#list>
                <#assign audit=[]/>
                <#list el.auditData as auditData>
                    <#if auditData.field.id==field.id>
                    <#assign audit=audit+[auditData]/>
                    </#if>
                </#list>
               
                <#assign id=templateName+"_"+fieldName/>
                           
                                <tr id="informations-${id}">
                                    <td id="td-label-${id}">
                                        <#if !(groupActive?? && groupActive)>
                                        <div class="field-component view-mode" >
                                            <@SingleFieldLabel template.name field.name field.mandatory />
                                            </div>
                                        </#if>
                                    </td>
                                    <#if fieldEditable>
                                        <td id="td-field-${id}">
                                        <div class="field-component view-mode" >
                                            <@mdfield template field vals false true audit/>
                                            </div>
                                           
                                        </td>
                                    <#else>
                                        <td id="td-field-view-${id}">
                                        <div class="field-component view-mode" >
                                            <@stdField template field vals false  empty false />
                                            
                                            </div>
                                        </td>
                                    </#if>
                                </tr>
                           
            </#if>
            </#list>
           
        </#if>
    </#list>
</#if>
</#macro>