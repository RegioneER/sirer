<#macro elementTitle element>
    ${element.titleString!""}
</#macro>

<#function getTitle element>
    <#assign ret=""/>
    <#list element.data as metadata>
        <#if metadata.field.id=element.type.titleField.id>
	        <#if metadata.field.type="ELEMENT_LINK">
	        	<#assign ret="->"+getTitle(metadata.getVals()[0])/>
	        <#elseif metadata.field.type="EXT_DICTIONARY" || metadata.field.type="SELECT" || metadata.field.type="RADIO"/>
	            <#assign ret=metadata.getVals()[0]?split("###")[1]/> 
	        <#else> 
	        <#if metadata.getVals()[0]??>
	        	<#assign ret=metadata.getVals()[0]/>
	        	<#else>
	        	<#assign ret="undefined"/>
	        	</#if>
	        </#if>
        </#if>
    </#list>
    <#if element.type.typeId="Studio">
    	 <#list element.data as metadata>
    	 	<#if metadata.field.name="id" && metadata.template.name="UniqueIdStudio">
				<#assign ret=ret+" ("+metadata.getVals()[0]+")"/>
    	   </#if>
	        
    </#list>
    </#if>
    <#return ret/>
</#function>

<#macro infoBox text>
<a title="${text}" href="#" onclick="return false;" class="ui-icon ui-icon-info" style="display: inline-block"></a>
</#macro>

<#macro breadCrumb element>
    <#if element.parent??>
        <@breadCrumb element.parent/>
            <a href="${baseUrl}/app/documents/detail/${element.parent.id}">
                <img width="20px" src="${element.parent.type.imageBase64!}"/>
                <#if element.parent.type.titleField??>
                    <@elementTitle element.parent/>
                </#if>
            </a>
        &gt;
    <#else>
        <a href="${baseUrl}/app/documents/">Home</a>
        &gt;
    </#if>
</#macro>

<#macro printMetadata metadataField element label="">
    <#if element.data??>
    <#list element.data as data>
        <#if metadataField ==  data.templateName+"."+data.field.name>
            <#list data.vals as val>${val!""}</#list>
        </#if>
    </#list>
    </#if>
</#macro>

<#macro saveButtons saveButtons formId>
    <#list saveButtons?keys as prop>
        <input class="submitButton ${prop} round-button blue" type="button" value="${saveButtons[prop]}" id="${formId}-submit" name="${formId}-submit"/>
    </#list>
</#macro>

<#macro html value><#if value!="">${value?html}</#if></#macro>

<#function dateValue value="">
    <#if value!="">
        <#return value.time?date?string("dd/MM/yyyy")/>
        <#else>
        <#return ""/>
    </#if>
</#function>

<#function viewData type values=[]>
            <#switch type>
                <#case "TEXTBOX">
                    <#return values[0]!"&nbsp;"/>
                    <#break>
                <#case "TEXTAREA">
                    <#return values[0]!"&nbsp;"/>
                    <#break>
                <#case "DATE">
                <#return dateValue(values[0])/>
                    <#break>
            </#switch>
</#function>

<#macro viewFieldNoLabel template fieldDef  mddata=[] editable=false audit=[]>
	<#assign id=template.name+"_"+fieldDef.name/>
    <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>
    <div id="${id}_value_view" class="data-view-mode" style="display: ">
                <#if editable>
                    <span class="ui-icon ui-icon-pencil right-corner" title="modifica">edit</span>
                </#if>
                <span id="${id}_value">
                <#switch fieldDef.type>
                    <#case "TEXTBOX">
                        ${mddata[0]!""}&nbsp;
                        <#break>
                    <#case "TEXTAREA">
                        ${mddata[0]!""}&nbsp;
                        <#break>
                    <#case "DATE">
                        ${dateValue(mddata[0])}&nbsp;
                        <#break>
                    <#case "RADIO">
                    	<#if mddata[0]?? && mddata[0]!="">
	                    ${mddata[0]?split("###")[1]}    
						<#else>&nbsp;
                        </#if>
                        <#break>
                    <#case "SELECT">
                        <#if mddata[0]?? && mddata[0]!="">
                        ${mddata[0]?split("###")[1]}
                        <#else>&nbsp;
                        </#if>
                        <#break>
                    <#case "ELEMENT_LINK">
                        <#if mddata[0]??>
                                <a href="${baseUrl}/app/documents/detail/${mddata[0].id}"><@elementTitle mddata[0]/></a>
                        <#else>&nbsp;
                        </#if>
                    <#break>
                    <#case "EXT_DICTIONARY">
                        <#if mddata[0]??>
                        	<#assign code=mddata[0]?split("###")[0]/>
                        	<#assign decode=mddata[0]?split("###")[1]/>
                               ${decode!""}
                        <#else>&nbsp;
                        </#if>
                    <#break>
                </#switch>
                </span>
                </div>

</#macro>

<#macro viewField template fieldDef  mddata=[] editable=false audit=[]>
	 <#assign id=template.name+"_"+fieldDef.name/>
     <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>
     <div class="field-component view-mode" id="${template.name}-${id}">
     <label for="${id}">${label}:</label>
     <@viewFieldNoLabel template fieldDef  mddata editable audit/>
     </div>  

</#macro>

<#macro mdFieldDetail template fieldDef  mddata=[] editable=false audit=[] showLabel=true>
    <#assign id=template.name+"_"+fieldDef.name/>
    <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>
    
    <#assign addClass=""/>
    <#if editable>
        <#assign addClass="view-editable-field"/>
    </#if>
    <div class="field-component view-mode" id="${template.name}-${id}">
    <#if showLabel> 
	    <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>
		<label for="${id}">
		<#if template.auditable && audit??>
	    <img alt="Mostra Audit" class="history-img" src="${baseUrl}/int/images/history.png" onclick="
		    if (document.getElementById('${template.name}_${fieldDef.name}_audit').style.display=='none')
		    document.getElementById('${template.name}_${fieldDef.name}_audit').style.display='';
		    else document.getElementById('${template.name}_${fieldDef.name}_audit').style.display='none';
		    "/>
	    </#if>${label}<#if fieldDef.mandatory><sup style="color:red">*</sup></#if>:</label>
    </#if>
        <div id="${id}_value_view" class="data-view-mode ${addClass}" style="display: ">
                <#if editable>
                    <span class="ui-icon ui-icon-pencil right-corner" title="modifica">edit</span>
                </#if>
                <span id="${id}_value">
                <#switch fieldDef.type>
                    <#case "TEXTBOX">
                        ${mddata[0]!""}&nbsp;
                        <#break>
                    <#case "TEXTAREA">
                        ${mddata[0]!""}&nbsp;
                        <#break>
                    <#case "DATE">
                        ${dateValue(mddata[0])}&nbsp;
                        <#break>
                    <#case "RADIO">
                    	<#if mddata[0]?? && mddata[0]!="">

                        ${mddata[0]?split("###")[1]}
                        <#else>&nbsp;
                        </#if>
                        <#break>
                    <#case "SELECT">
                        <#if mddata[0]?? && mddata[0]!="">
                        ${mddata[0]?split("###")[1]}
                        <#else>&nbsp;
                        </#if>
                        <#break>
                    <#case "ELEMENT_LINK">
                        <#if mddata[0]??>
                                <a href="${baseUrl}/app/documents/detail/${mddata[0].id}"><@elementTitle mddata[0]/></a>
                        <#else>&nbsp;
                        </#if>
                    <#break>
                    <#case "EXT_DICTIONARY">
                        <#if mddata[0]??>
                        	<#assign code=mddata[0]?split("###")[0]/>
                        	<#assign decode=mddata[0]?split("###")[1]/>
                               ${decode!""}
                        <#else>&nbsp;
                        </#if>
                    <#break>
                </#switch>
                </span>
            </div>
        <#if editable>
            <form name="${id}" style="display: none" class="single-field-form" id="form-${id}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
                <@mdfield template fieldDef mddata false true/>
                <div class="save-options" tabindex="1">
                    <button class="save-buttons" style="height: 24px" value="${id}">
                        <button class="cancel-buttons"  style="height: 24px" value="${id}">
                </div>
            </form>
        </#if>

</div>
<#if template.auditable && audit??>
<div id="${id}_audit"  style="display:none">
    <table class="pSchema">
        <tr>
            <th>Utente</th>
            <th>Data</th>
            <th>Tipo modifica</th>
            <th>Valore vecchio</th>
            <th>Valore nuovo</th>
        </tr>
        <tbody id='${id}-audit-table'>
            <#list audit as a>
            <#assign old=""/>
            <#assign new=""/>
                <#switch fieldDef.type>
                    <#case "DATE">
                            <#assign old=dateValue(a.getOldVals()[0])/>
                            <#assign new=dateValue(a.getNewVals()[0])/>
                        <#break>
                    <#default>
                    <#assign old=a.getOldVals()[0]!"&nbsp;"/>
                    <#assign new=a.getNewVals()[0]!"&nbsp;"/>
                </#switch>
            <tr>
                <td>${a.username}</td>
                <td>${a.modDt.time?datetime?string.short}</td>
                <td>${a.action}</td>
                <td>${old}</td>
                <td>${new}</td>
            </tr>
    </#list>
    </tbody>
    </table>
</div>
</#if>
</#macro>

<#macro mdfield template="" fieldDef=""  mddata=[] divContainer=true noLabel=false>
	<#assign id=fieldDef.name/>
	<#assign label=fieldDef.name/>
	<#if template!="">
	    <#assign id=template.name+"_"+fieldDef.name/>
	    <#assign label=template.name+"."+fieldDef.name/>
		<#if fieldDef.mandatory><#assign label="${messages[label]!label}<sup style=\"color:red\">*</sup>"/></#if>
	</#if>
	<#if divContainer>
		<div class="field-component" id="${template.name}-${id}">
	</#if>
	<script>
	if (!fieldTypes) var fieldTypes=new Object();
		fieldTypes["${id}"]="${fieldDef.type}";	
	</script>
	<#assign size=10/>
		<#if fieldDef.size??><#assign size=fieldDef.size/></#if>
	<#switch fieldDef.type>
		<#case "TEXTBOX">
	        <#if noLabel>
	        <#if fieldDef.macro??>
	         		<#assign x=fieldDef.macro/> 
	         		<@.vars[x] id id messages[label]!label mddata?first!"" size/>
	         	<#else>
	        	<@textboxNoLabel id id messages[label]!label mddata?first!"" size/>
	        </#if>
	        <#else>
	            <@textbox id id messages[label]!label mddata?first!"" size/>
	        </#if>
	    <#break>
	    <#case "TEXTAREA">
	    	<#if noLabel>
	    		<@textareaNoLabel id id messages[label]!label 40 5 mddata?first!""/>
	    	<#else>
	        	<@textarea id id messages[label]!label 40 5 mddata?first!""/>
	        </#if>
	        <#break>
	    <#case "DATE">
	    	<#if noLabel>
	    		<@datePickerNoLabel id id messages[label]!label mddata?first!""/>
	    	<#else>
	        	<@datePicker id id messages[label]!label mddata?first!""/>
	        </#if>
	        <#break>
	    <#case "SELECT">
	    	<#assign availableValues = {}>
	    	<#list fieldDef.availableValuesMap?keys as prop>
			    <#assign availableValues = availableValues+ {prop+"###"+fieldDef.availableValuesMap[prop]?html: fieldDef.availableValuesMap[prop]}/>
			</#list>
	    	<#if noLabel>
	    		<@selectHashNoLabelPlus id id messages[label]!label availableValues mddata?first!""/>
	    	<#else>
	        	<@selectHashPlus id id messages[label]!label availableValues mddata?first!""/>
	        </#if>
	        <#break>
	    <#case "RADIO">
	    	<#assign availableValues = {}>
	    	<#list fieldDef.availableValuesMap?keys as prop>
			    <#assign availableValues = availableValues+ {prop+"###"+fieldDef.availableValuesMap[prop]?html: fieldDef.availableValuesMap[prop]}/>
			</#list>
	    	<#if noLabel>
	    		<@radioNoLabel id id messages[label]!label availableValues mddata?first!""/>
	    	<#else>
	        	<@radioHash id id messages[label]!label availableValues mddata?first!""/>
	        </#if>
	        <#break>
	    <#case "ELEMENT_LINK">
	        <#if mddata[0]??>
	            <#assign selectedValues=[getTitle(mddata[0])]/>
	            <#assign selectedIds=[mddata[0].id]/>
	        <#else>
	            <#assign selectedValues=[]/>
	            <#assign selectedIds=[]/>
	        </#if>
	        <#if noLabel>
	         	<#if fieldDef.macro??>
	         		<#assign x=fieldDef.macro> 
	         		<@.vars[x] id id messages[label]!label "${baseUrl}/app/rest/documents/getLinkableElements/${fieldDef.id}" "title" selectedValues "id", selectedIds fieldDef.availableValuesMap fieldDef/>
	         	<#else>
	         		<@singleAutoCompleteFBNoLabel id id messages[label]!label "${baseUrl}/app/rest/documents/getLinkableElements/${fieldDef.id}" "title" selectedValues "id", selectedIds/>
	        	</#if>
	        <#else>
	        	<@singleAutoCompleteFB id id messages[label]!label "${baseUrl}/app/rest/documents/getLinkableElements/${fieldDef.id}" "title" selectedValues "id", selectedIds/>
			</#if>
	        <#break>
	         <#case "EXT_DICTIONARY">
	        <script>
	        var ${id}_addFilters="";
	        </script>
	         <#if mddata[0]??>
	            <#assign selectedIds=[mddata[0]]/>
                    <#assign selectedValues=[mddata[0]?split("###")[1]]/>
                              
	        <#else>
	            <#assign selectedValues=[]/>
	            <#assign selectedIds=[]/>
	        </#if>
	        <#if fieldDef.addFilterFields??>
	        <script>
	        var ${id}_addFilters="${fieldDef.addFilterFields}";
	        </script>
	        </#if>
	        <#if noLabel>
	        	<@singleAutoCompleteFunctionFBNoLabel id id messages[label]!label "${fieldDef.externalDictionary}" "title" selectedValues "id", selectedIds template.name/>
	        <#else>
	        	<@singleAutoCompleteFunctionFB id id messages[label]!label "${fieldDef.externalDictionary}" "title" selectedValues "id", selectedIds template.name/>
			</#if>
	        <#break>
	</#switch>
	<#if divContainer>
	</div>
	</#if>
</#macro>



<#function getLabel id>
	<#return messages[id]!id/>
</#function>
<#macro msg id>
        ${messages[id]!id}
</#macro>

<#macro datePickerNoLabel id name label value="">
	<#assign txtValue=""/>
	<#if value != "" >
	    <#assign txtValue=value.time?date?string("dd/MM/yyyy")/>
	</#if>
	<input type="text" name="${name}" id="${id}" value="${txtValue}" class="datePicker"/>
	<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
	    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
	    <span id="alert-msg-${id}"></span>
	</span>
</#macro>

<#macro datePicker id name label value="">
	<label for="${id}">${label}:</label>
	<@datePickerNoLabel id name label value/>
</#macro>

<#macro select id name label values value="">
<label for="${id}">${label}:</label>
<select id="${id}" name="${name}">
<option></option>
<#list values as itm>
<option value="${itm}" <#if value==itm>selected</#if>>${itm}</option>
        </#list>
        </select>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>


<#macro checkBox id name label values={} value=[]>
<#if label!="">
<label for="${id}">${label}:</label>
</#if>
     <#assign keys = values?keys>
    <#list keys as key>
        <input id="${id}" name="${name}" type="checkbox" value="${key}" <#if value?seq_contains(key)>checked</#if> title="${values[key]}">${values[key]}
    </#list>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>

<#macro mSelectHash id name label values={} value=[]>
<label for="${id}">${label}:</label>
<select id="${id}" name="${name}" multiple size="${values?size+1}">
    <option></option>
    <#assign keys = values?keys>
    <#list keys as key>
        <option value="${key}" <#if value?seq_contains(itm)>selected</#if>>${values[key]}
    </#list>
</select>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>


<#macro radioNoLabel id name label values={} value="">
    <#assign keys = values?keys>
    <#list keys as key>
        <input type="radio" id="${id}" name="${name}" value="${key}" <#if value==key>checked</#if> title="${values[key]}">${values[key]}
    </#list>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>

<#macro radioHash id name label values={} value="">
<label for="${id}">${label}:</label>
<@radioNoLabel id name label values value/>
</#macro>

<#macro selectHashNoLabel id name label values={} value="">


<select id="${id}" name="${name}">
    <option></option>
    <#assign keys = values?keys>
    <#list keys as key>
        <option value="${key}" <#if value=key>selected</#if>>${values[key]}</option>
    </#list>
</select>

</#macro>

<#macro selectHashNoLabelPlus id name label values={} value="">
<#assign selectedCode=""/>
<#assign selectedDecode=""/>
<#if value?? && value?contains("###")>

<#assign selectedCode=value?split("###")[0]/>
<#assign selectedDecode=value?split("###")[1]/>
</#if>
<script>

$(document).ready(function(){

		val="${value?html}";
		console.log("${id} :${value?html}");
		$('#${id}').val(val);
        if (val.indexOf('-9999###')==0) {
	       	console.log(val);
	       	$('#${id}-altro').show();
	       	$('#${id}-altro').val("${selectedDecode?html}");
        }

		$('#${id}-altro').change(function(){
			if ($('#${id}-select').val().indexOf('-9999###')==0){
				$('#${id}').val('-9999###'+$('#${id}-altro').val());	
			}
		});
		
		
		$('#${id}-select').change(function(){
			console.log($(this).val());
			if ($(this).val().indexOf('-9999###')==0){
				console.log("devo mostrare il campo altro");
				$('#${id}-altro').show();
				$('#${id}-altro').focus();
			}else {
				$('#${id}-altro').hide();	
				$('#${id}').val($('#${id}-select').val());
			}
		});
		
		

});


</script>

<select id="${id}-select" name="${name}-select">
    <option></option>
    <#assign keys = values?keys>
    <#list keys as key>
        <option value="${key}" <#if key?split("###")[0]=selectedCode>selected</#if>>${values[key]}</option>
    </#list>
</select>
<input type="hidden" id="${id}" name="${name}"/>
<input type="text" id="${id}-altro" name="${name}-altro" style="display:none"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>

<#macro selectHashPlus id name label values={} value="">
<label for="${id}">${label}:</label>
<@selectHashNoLabelPlus id name label values value/>
</#macro>


<#macro selectHash id name label values={} value="">
<label for="${id}">${label}:</label>
<@selectHashNoLabel id name label values value/>
</#macro>


<#macro multiAutoCompleteFunctionFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] templateName="">
      <@multiAutoCompleteFunction id name label searchScript searchValue selectedValues true false searchId selectedIds templateName/>
</#macro>

<#macro singleAutoCompleteFunctionFBNoLabel id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] templateName="">
    <@multiAutoCompleteFunctionNoLabel id name label searchScript searchValue selectedValues true true searchId selectedIds templateName/>
</#macro>

<#macro singleAutoCompleteFunctionFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] templateName="">
    <@multiAutoCompleteFunction id name label searchScript searchValue selectedValues true true searchId selectedIds templateName/>
</#macro>


<#macro multiAutoCompleteFunction id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] templateName="">
    <label for="${id}">${label}:</label>
    <@multiAutoCompleteFunctionNoLabel id name label searchScript searchValue selectedValues theme single searchId selectedIds templateName/>
</#macro>

<#assign usedTokenInput=0/>



<#macro multiAutoCompleteFunctionNoLabel id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] templateName="">
<#assign usedTokenInput=usedTokenInput+1/>
    <select id="${id}-select" name="${name}-select">
    </select><input type="text" id="${id}-altro" name="${name}-altro" style="display:none">
    <input type="hidden" id="${id}" name="${name}"/>
    <script>
    if (!dependency) var dependency=new Object();
    
    $(document).ready(function(){
    	if (${id}_addFilters && ${id}_addFilters!=""){
    		filters=${id}_addFilters.split(",");
    		var addedParam="";
    		for (l=0;l<filters.length;l++){
				secondSplit=filters[l].split("=");
				var re = new RegExp("^\\[(.*)\\]$");
				if (secondSplit[1].match(re)) {
					idField=secondSplit[1].replace("\[","");
					idField=idField.replace("\]","");
					if (!dependency[idField]) dependency[idField]=new Array();
					dependency[idField][dependency[idField].length]='${id}';
				}
			}
		}
		
		$('#${id}-altro').change(function(){
			if ($('#${id}-select').val().indexOf('-9999###')==0){
				$('#${id}').val('-9999###'+$('#${id}-altro').val());	
			}
		});
		
		
		$('#${id}-select').change(function(){
			if ($(this).val().indexOf('-9999###')==0){
				$('#${id}-altro').show();
				$('#${id}-altro').focus();
			}else {
				$('#${id}-altro').hide();	
				$('#${id}').val($('#${id}-select').val());
			}
			if (dependency['${id}'])
			    for(var index in dependency['${id}']) {
				  setTimeout('populateSelect_'+dependency['${id}'][index]+'()',50);
				}	
		});
		populateSelect_${id}();
		});
    	
    	function buildScriptUrl_${id}(){
    		if (${id}_addFilters && ${id}_addFilters!=""){
    		filters=${id}_addFilters.split(",");
    		var addedParam="";
    		for (l=0;l<filters.length;l++){
				secondSplit=filters[l].split("=");
				var re = new RegExp("^\\[(.*)\\]$");
				if (secondSplit[1].match(re)) {
					idField=secondSplit[1].replace("\[","");
					idField=idField.replace("\]","");
					if (addedParam!="") addedParam+="&";
					if (!valueOfField(idField)) return "";
					addedParam+=secondSplit[0]+"="+encodeURIComponent(valueOfField(idField));
				}else {
					addedParam+=secondSplit[0]+"="+encodeURIComponent(secondSplit[1]);
				}
			}
			}
			return '${searchScript}?'+addedParam;
    	}
    	
    	function populateSelect_${id}(){
    	    $('#${id}-select').html("");
    	    $('#${id}-select').append("<option></option>");
    		var url=buildScriptUrl_${id}();
    		if (url!=""){
    		$.getJSON(url,function(result){
    		   $.each(result, function(i, field){
			     var val=field.id+"###"+field.title;  
			     var code=field.id+"###";
			     var selected="";
			     var decode="";
			     <#if searchId!="">
                            <#assign idx=0/>
                            <#list selectedValues as sv>
                            if ("${selectedIds[idx]?html}".indexOf(code)==0) {
                            	selected="selected";
                            	decode="${selectedIds[idx]?split("###")[1]?html}";
                            	}
                                <#assign idx=idx+1/>
                            </#list>

                        <#else>
                            <#list selectedValues as sv>
                            if (val=="${sv?html}") selected="selected";
                            </#list>
                        </#if>
                if (selected!="") {
                	$('#${id}').val(val);
                	if (val.indexOf('-9999###')==0) {
	                	$('#${id}-altro').show();
	                	$('#${id}-altro').val(decode);
                	}
    	    	}
    	    	$('#${id}-select').append("<option value=\""+val+"\" "+selected+">"+field.title+"</option>");    	
			   });
			   if (dependency['${id}'])
			    for(var index in dependency['${id}']) {
				  setTimeout('populateSelect_'+dependency['${id}'][index]+'()',50);
				}
				
			  });		
			}
    	}
    	
    </script>
    
</#macro>

<#macro multiAutoCompleteFunctionNoLabel_ id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] templateName="">
<#assign usedTokenInput=usedTokenInput+1/>
    <input type="text" id="${id}" class="randomClass-${usedTokenInput}" name="${name}"/>
    <script type="text/javascript">
    	function rebuildToken_${id}(){
    		$('#form-${id}').find(".token-input-list-facebook").remove();
        	$('#${id}.randomClass-${usedTokenInput}').html("");
        	buildToken_${id}();
        	$('#${id}').tokenInput('clear');
        	
    	}
    	
    	$(document).ready(function(){
    	if (${id}_addFilters && ${id}_addFilters!=""){
			filters=${id}_addFilters.split(",");
    		for (l=0;l<filters.length;l++){
				secondSplit=filters[l].split("=");
				var re = new RegExp("^\\[(.*)\\]$");
				if (secondSplit[1].match(re)) {
					idField=secondSplit[1].replace("\[","");
					idField=idField.replace("\]","");
					$('#'+idField).change(function(){
					console.log("effettuo modifiche - "+idField);
					console.log("svuoto ${templateName}-${id}");
					val=valueOfField(idField);
					console.log("val: "+val);
					$('#${templateName}-${id}').find(".token-input-list-facebook").remove();
					buildToken_${id}();
					});
				}
			}
			}
    	});
    
    	function buildToken_${id}(){
    		if (${id}_addFilters && ${id}_addFilters!=""){
			filters=${id}_addFilters.split(",");
			var addedParam="";
			var re = new RegExp("^\\[(.*)\\]$");
			for (l=0;l<filters.length;l++){
				secondSplit=filters[l].split("=");
				if (secondSplit[1].match(re)) {
					idField=secondSplit[1].replace("\[","");
					idField=idField.replace("\]","");
					idField=idField.replace("\.","_");
					if (addedParam!="") addedParam+="&";
					addedParam+=secondSplit[0]+"="+valueOfField(idField);
					
				}else {
						addedParam+=secondSplit[0]+"="+secondSplit[1];
				}
				
			}
    		}
    		var link="${searchScript}";
    		if (addedParam!="") link+="?"+addedParam;
    		$("#${id}.randomClass-${usedTokenInput}").attr('isTokenInput',true);
        	$("#${id}.randomClass-${usedTokenInput}").tokenInput(link, {
                queryParam: "term",
                hintText: "Digitare almeno 2 caratteri",
                minChars: 0,
                searchingText: "ricerca in corso...",
                noResultsText: "Nessun risultato",
                <#if single>
                tokenLimit: 1,
                </#if>
                <#if theme>theme: 'facebook',
                </#if>
                preventDuplicates: true,
                <#if selectedValues??>
                prePopulate: [
                        <#if searchId!="">
                            <#assign idx=0/>
                            <#list selectedValues as sv>
                                {id: '${selectedIds[idx]}', name: "${sv}"},
                                <#assign idx=idx+1/>
                            </#list>

                        <#else>
                            <#list selectedValues as sv>
                                {id: '${sv}', name: "${sv}"},
                            </#list>
                        </#if>

                ],
                </#if>
                onResult: function (results) {
                    $.each(results, function (index, value) {
                        value.name = value.${searchValue};
                        <#if searchId!="">
                            value.id=value.${searchId}+"###"+value.name;
                        <#else>
                            value.id=value.${searchValue};
                        </#if>

                    });

                    return results;
                }
            });
    	}
    
        $(document).ready(function() {
        	buildToken_${id}();    
        });
    </script>
</#macro>


<#macro multiAutoCompleteFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[]>
      <@multiAutoComplete id name label searchScript searchValue selectedValues true false searchId selectedIds/>
</#macro>

<#macro singleAutoCompleteFBNoLabel id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[]>
    <@multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues true true searchId selectedIds/>
</#macro>

<#macro singleAutoCompleteFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[]>
    <@multiAutoComplete id name label searchScript searchValue selectedValues true true searchId selectedIds/>
</#macro>


<#macro multiAutoComplete id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[]>
    <label for="${id}">${label}:</label>
    <@multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues theme single searchId selectedIds/>
</#macro>

<#assign usedTokenInput=0/>

<#macro multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[]>
<#assign usedTokenInput=usedTokenInput+1/>
    <input type="text" id="${id}" class="randomClass-${usedTokenInput}" name="${name}"/>
    <script type="text/javascript">
        $("#${id}.randomClass-${usedTokenInput}").attr('isTokenInput',true);
        $(document).ready(function() {
            $("#${id}.randomClass-${usedTokenInput}").tokenInput("${searchScript}", {
                queryParam: "term",
                hintText: "Digitare almeno 2 caratteri",
                minChars: 2,
                searchingText: "ricerca in corso...",
                noResultsText: "Nessun risultato",
                <#if single>
                tokenLimit: 1,
                </#if>
                <#if theme>theme: 'facebook',
                </#if>
                preventDuplicates: true,
                <#if selectedValues??>
                prePopulate: [
                        <#if searchId!="">
                            <#assign idx=0/>
                            <#list selectedValues as sv>
                                {id: '${selectedIds[idx]}', name: "${sv}"},
                                <#assign idx=idx+1/>
                            </#list>

                        <#else>
                            <#list selectedValues as sv>
                                {id: '${sv}', name: "${sv}"},
                            </#list>
                        </#if>

                ],
                </#if>
                onResult: function (results) {
                    $.each(results, function (index, value) {
                        value.name = value.${searchValue};
                        <#if searchId!="">
                            value.id=value.${searchId};
                        <#else>
                            value.id=value.${searchValue};
                        </#if>

                    });

                    return results;
                }
            });
        });
    </script>
</#macro>


<#macro hidden id name value="">
<input type="hidden" name="${name}" id="${id}" value="${value!""}"/>
</#macro>

<#macro textboxNoLabel id name label value="" size=10>
<input type="text" name="${name}" id="${id}" value="${value!""}" size="${size}"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>

</#macro>

<#macro textbox id name label value="" size=10>
<label for="${id}">${label}:</label>
<@textboxNoLabel id name label value size/>
</#macro>

<#macro colorpicker id name label value="">
<label for="${id}">${label}:</label>
<input type="text" class="colorpicker" name="${name}" id="${id}" value="${value!""}" size="10"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>

<#macro fileChooser id name label value="">
<#if label!="">
<label for="${id}">${label}:</label>
</#if>
<input type="file" name="${name}" id="${id}" value=""/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>

<#macro password id name label value="">
<label for="${id}">${label}:</label>
<input type="password" name="${name}" id="${id}" value="${value!""}"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>        </#macro>

<#macro textareaNoLabel id name label cols=40 rows=4 value="">
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
<textarea cols="${cols}" rows="${rows}" type="text" name="${name}" id="${id}">${value!""}</textarea>
</#macro>

<#macro textarea id name label cols=40 rows=4 value="">
<label for="${id}">${label}:</label>
<@textareaNoLabel id name label cols rows value/>
</#macro>


<#function max x y>
    <#if (x<y)><#return y><#else><#return x></#if>
</#function>
<#function min x y>
    <#if (x<y)><#return x><#else><#return y></#if>
</#function>

<#macro pages totalPages p elId="" showNumPages=10>
	<#assign size = totalPages>
    <#if size gt 1>
    <#if elId?? && elId?string!="">
    <#assign url="${baseUrl}/app/documents/detail/${elId}"/>
    <#else>
    <#assign url="${baseUrl}/app/documents"/>
    </#if>
    <div class="paging-bar">
    <#if (p<=showNumPages/2)>
        <#assign interval = 1..10>
    <#elseif ((size-p)<showNumPages/2)> 
        <#assign interval = (size-showNumPages)..size >
    <#else>
        <#assign interval = (p-(showNumPages/2))..(p+(showNumPages/2))>
    </#if>
    <#if !(interval?seq_contains(1))>
     <a href="${url}?p=1">1</a>&nbsp;... <#rt>
    </#if>
    <#list interval as page>
    	<#if page gt 0 && page <= size>
        <#if page=p>
         <strong>${page}</strong>&nbsp;<#t>
        <#else>
        <a href="${url}?p=${page}">${page}</a>&nbsp;<#t>
        </#if>
        </#if>
    </#list>
    <#if !(interval?seq_contains(size))>
     ... <a href="${url}?p=${size}">${size}</a><#lt>
     </#if>
      <form method="GET" action="${url}">
     	<input type="textbox" name="p" size="2"/><input class="round-button blue" type="submit" value="go to page"/>
     </form>
     </div>
     </#if>
    
</#macro>
