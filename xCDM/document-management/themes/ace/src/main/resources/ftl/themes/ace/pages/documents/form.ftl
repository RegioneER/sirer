
<#assign templates={}/>
<#if type.ftlFormTemplate??>
	<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>
<#if templates?? && templates?size gt 0>
	<#if templates?size gt 1>
		<#if selectedTemplate!="">
			<!-- ${selectedTemplate} -->
			<#include "form/"+selectedTemplate+".ftl"/>
		</#if>
		<#else>
			<#assign keys = templates?keys>
		    <#list keys as key>
		    	<#assign selectedTemplate=key/>	
		    	<!-- ${selectedTemplate} -->
		    	<#include "form/"+key+".ftl"/>
		    </#list>
	</#if>
    
<#else>
   


<div class="mainContent">
<#if model['parent']??>

<@breadcrumbsData model['parent']/>

</#if>

<form class="form-horizontal" id="document-form" method="POST" action="${baseUrl}/app/rest/documents/save/${model['docDefinition'].id}" enctype="multipart/form-data" onsubmit="return false;" >
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
        <#assign label>
        <@msg model['docDefinition'].typeId+".fileLabel" /> <sup style='color:red'>*</sup>
        </#assign>
        <@fileChooser "file" "file" label />
        </div>
        </#if>
        <div class="clearfix"></div>
        <button class="btn btn-warning submitButton" id="document-form-submit" name="document-form-submit"><i class="icon-save bigger-160"></i><b>Salva</b></span>
		</button>
										
       

</form>
</div>

</#if>