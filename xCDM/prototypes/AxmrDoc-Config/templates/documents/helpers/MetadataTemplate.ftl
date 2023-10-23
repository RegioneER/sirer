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

<#macro TemplateForm templateName el userDetails editable>
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#list el.elementTemplates as elementTemplate>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    		<#assign template=elementTemplate.metadataTemplate/>
        	<div id="metadataTemplate-${template.name}" class="allInTemplate">
        	<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
        	<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
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
                <#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
                <div class="field-component view-mode" id="informations-${id}">
                <label for="${id}">${label}<#if field.mandatory><sup style="color:red">*</sup></#if>:</label>
                <#if fieldEditable>
                	<@mdfield template field vals false true/>
	        <#else>
	                <@viewFieldNoLabel template field vals false true/>
	        </#if>
                </div>
            </#list>
            <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
            	<input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche">
            	</form>
            </#if>
        </div>
        </#if>
    </#list>
</#if>
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
				<#assign id=template.name+"_"+field.name/>
				<#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
				<div class="field-component view-mode" id="informations-${id}">
				<label for="${id}">${label}<#if field.mandatory><sup style="color:red">*</sup></#if>:</label>
				<#if fieldEditable>
					<@mdfield template field vals false true/>
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
        	<div id="metadataTemplate-${template.name}" class="allInTemplate">
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
				<#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
				<div class="field-component view-mode" id="informations-${id}">
				<#if fieldEditable>
					<@mdfield template field vals false true/>
				<#else>
					<@viewFieldNoLabel template field vals false true/>
				</#if>
				</div>
			</#if>
            </#list>
            <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
            	<input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche">
            	</form>
            </#if>
        </div>
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
			<div id="metadataTemplate-${template.name}">
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
			<#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
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
				<#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
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
				<#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
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

