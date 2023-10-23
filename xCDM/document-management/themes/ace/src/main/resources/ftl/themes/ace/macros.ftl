
<#macro reportBuilder reportRootEl>
		<#assign reportList=[]/>
		<#if reportRootEl.childs??>
			<#list reportRootEl.childs as area>
				<#if area.childs??>
					<#assign tmpReports=[]/>
					<#list area.childs as report>
						<#if !report.deleted && report.getUserPolicy(userDetails).canBrowse>
							<#assign tmpReports=tmpReports+[{"id": report.id, "title": report.titleString, "position": report.position?c}]/>
						</#if>
					</#list>
					<#if tmpReports?size gt 0>
						<#assign reportList=reportList+[{"id": area.id, "title": area.titleString, "children": tmpReports}]/>
					</#if>
				</#if>
			</#list>
		</#if>
		<@addmenuitem>
		{
			"level_1":true,
			"title":"Dashboards",
			"icon":{"icon":"icon-dashboard","title":"Dashboard"}
			<#if reportList?size gt 0>
			,"submenu":[
			<#list reportList as area>
			<#assign classes=""/>
			{
				"level_2":true,
				"title":"${area.title}",
				"icon":{"icon":"","title":"${area.title}"}
				<#if area.children?size gt 0>
				,"submenu":[
					<#list area.children?sort_by("position") as report>
						{
						"link":"${baseUrl}/app/documents/detail/${report.id}",
						"level_3":true,
						"title":"${report.title}",
						"icon":{"icon":"","title":"${report.title}"}
						}
					<#if report_has_next>,</#if>
					</#list>
				]
				</#if>
			}
			<#if area_has_next>,</#if>
			</#list>
			]
			</#if>
		}
		</@addmenuitem>
</#macro>

<#macro selectAuthorities id name label url title selectedValues id selectedIds templatename noLabel fieldDef editable>
<li>Sono qui</li>

<input type="text" id="e6"/>
<@script>
    $("#e6").select2({
    placeholder: "Cerca un gruppo di utenti",
    minimumInputLength: 2,
    ajax: { // instead of writing the function to execute the request we use Select2's convenient helper
    	url: "${url}",
    	dataType: 'json',
    	data: function (term, page) {
		    return {
		    	term: term
		    };
    	},
    	results: function (data, page) { // parse the results into the format expected by Select2.
    	var ret=new Array();
    	for (i=0;i<data.length;i++){
	    	var itm=new Object();
	    	itm.id=data[i].id;
	    	itm.text=data[i].authority;
	    	ret[i]=itm;
    	}
    	return {results: ret};
    }
    },
    initSelection: function(element, callback) {
    	var id=$(element).val();
    	if (id!=="") {
    		$.ajax("${url}?term=", {
    		dataType: "json"
    	}).done(function(data) { callback(data); });
    }
    }
    });

    function movieFormatResult(movie) {
    console.log("sono qui");
    console.log(movie);
        var markup = "<table class='movie-result'><tr>";
        if (movie.posters !== undefined && movie.posters.thumbnail !== undefined) {
            markup += "<td class='movie-image'><img src='" + movie.posters.thumbnail + "'/></td>";
        }
        markup += "<td class='movie-info'><div class='movie-title'>" + movie.title + "</div>";
        if (movie.critics_consensus !== undefined) {
            markup += "<div class='movie-synopsis'>" + movie.critics_consensus + "</div>";
        }
        else if (movie.synopsis !== undefined) {
            markup += "<div class='movie-synopsis'>" + movie.synopsis + "</div>";
        }
        markup += "</td></tr></table>";
        return markup;
    }

    function movieFormatSelection(movie) {
        return movie.title;
    }
    </@script>


</#macro>

<#macro initDataJson el noScript=false>
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<#assign json=el.type.getDummyJson() />
<#if noScript>
	var loadedElement=${loadedJson};
	<@dummyDataJson el.type noScript />
<#else>
<@script>
	var loadedElement=${loadedJson};
	<@dummyDataJson el.type noScript />
</@script>
</#if>
</#macro>

<#macro dummyDataJson type noScript=true>
	<#assign json=type.getDummyJson() />
	<#if !noScript>
	var empties=new Array();
	</#if>
	var dummy=${json};
	empties=new Array();
 	empties[dummy.type.id]=dummy;
</#macro>


<#--
<#macro firmaFileSelect id name label value="" size=30 noLabel=true fieldDef=null editable=false xEditable=false>
<#if !noLabel>
	<label for="${id}">${label}</label>
</#if>
<select name="${id}" id="${id}"><option></option></select>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
<#else>
	<#assign parentId=el.parent.id/>
</#if>
	<@script>
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==1){
        			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";
        			$('#${id}').append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        			else selected="";
        					$('#${id}').append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');
        				}
        			}
        		}
        	}
        	});

	</@script>
</#macro>
-->
<#--
<#macro firmaFileSelect2 id name label value="" size=30 noLabel=true fieldDef=null>
<#if !noLabel>
	<label for="${id}">${label}</label>
</#if>
<select name="${id}" id="${id}"><option></option></select>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
<#else>
	<#assign parentId=el.parent.id/>
</#if>
	<@script>
        	console.log('${value}');
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==2){
        			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";
        			$('#${id}').append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        			else selected="";
        					$('#${id}').append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');
        				}
        			}
        		}
        	}
        	});

	</@script>
</#macro>
-->
<#function getField templateName fieldName element>
   <#assign ret=""/>
   	<#if element.getfieldData(templateName, fieldName)?? && element.getfieldData(templateName, fieldName)?size gt 0 && element.getfieldData(templateName, fieldName)[0]??>
   		<#assign ret=element.getfieldData(templateName, fieldName)[0]!""/>
   	</#if>
   <#return ret/>
</#function>

<#function getCode templateName fieldName element>
	<#return getField(templateName,fieldName,element)?split('###')[0] />
</#function>

<#function getDecode templateName fieldName element>
	<#return getField(templateName,fieldName,element)?split('###')[1] />
</#function>

<#function getFieldFormattedDate templateName fieldName element format="dd/MM/yyyy">
   <#assign ret=""/>
   	<#if element.getfieldData(templateName, fieldName)?? && element.getfieldData(templateName, fieldName)?size gt 0 && element.getfieldData(templateName, fieldName)[0]??>

   		<#assign ret=element.getfieldData(templateName, fieldName)[0].time?date?string(format)/>
   	</#if>
   <#return ret/>
</#function>

<#macro elementTitle element>
	<#attempt>
    ${element.titleString!""}
    <#recover>
    </#attempt>
</#macro>

<#function getTitle element>
    <#assign ret=""/>
    <#list element.data as metadata>
        <#if element.type.titleField?? && metadata.field.id=element.type.titleField.id>
	        <#if metadata.field.type="ELEMENT_LINK">
	        	<#assign ret="->"+getTitle(metadata.getVals()[0])/>
	        <#elseif metadata.field.type="EXT_DICTIONARY" || metadata.field.type="SELECT" || metadata.field.type="RADIO" || metadata.field.type="CHECKBOX"/>
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
        	<#if element.type.typeId!="reportsArea">
            <a href="${baseUrl}/app/documents/detail/${element.parent.id}<#if element.type.hashBack?? >#${element.type.hashBack}</#if>">
     		</#if>
                <img width="20px" src="${element.parent.type.imageBase64!}"/>
                <#if element.parent.type.titleField?? || element.parent.type.titleRegex??>
                    <@elementTitle element.parent/>
                </#if>
            <#if element.type.typeId!="reportsArea">
	            </a>
	        </#if>
        &gt;
    <#else>
        <a href="${baseUrl}/app/documents/">Home</a>
        &gt;
    </#if>
</#macro>

<#macro breadcrumbsData element areaTitle="" iteration=false hashBack="" >
	<#if !iteration>

		<#global breadcrumbs={"title":areaTitle,"links":[]} />
	</#if>
    <#if element.parent??>
    	<@breadcrumbsData element.parent "" true element.type.hashBack />
    </#if>
    <#if iteration>
	    	<#assign title><#if element.type.typeId=="BudgetBracci">Budget complessivo</#if><@elementTitle element/></#assign>
	    	<#if element.type.typeId!="reportsArea">
	            <#assign url>${baseUrl}/app/documents/detail/${element.id}<#if hashBack?? >#${hashBack}</#if></#assign>
	    	<#else>
	    		<#assign url="#"/>
	    	</#if>
	    	<#assign link={
	    		"title":title,
	    		"link":url
	    	} />
	<#else>
		<#assign title><#if element.type.typeId=="BudgetBracci">Budget complessivo</#if><@elementTitle element /></#assign>

		<#assign link={"title":title} />
	</#if>
	<#if title?? && !title?matches('^\\s*$') >
    <#global breadcrumbs=breadcrumbs+{"links":breadcrumbs.links+[link]} />
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
<#macro showData template fieldDef  mddata=[] editable=false audit=[]>
	<#if mddata?? && mddata?size gt 0 >
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
                    <#case "CHECKBOX">
                    <#case "SELECT">
                        <#if mddata[0]?? && mddata[0]!="">
                        ${mddata[0]?split("###")[1]}
                        <#else>&nbsp;
                        </#if>
                        <#break>
                    <#case "ELEMENT_LINK">
                        <#if mddata[0]??>
                                <#--a href="${baseUrl}/app/documents/detail/${mddata[0].id}"--><@elementTitle mddata[0]/><#--/a-->
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
        </#if>
</#macro>

<#macro viewFieldNoLabel template fieldDef  mddata=[] editable=false audit=[]>
	<#assign id=template.name+"_"+fieldDef.name/>
	<#assign label>
        <@msg template.name+"."+fieldDef.name/>
    </#assign>
     <#if fieldDef.macroView??>
		<#assign x=fieldDef.macroView/>
 		<@.vars[x] id id template fieldDef  mddata editable audit/>
	 <#else>
    	<@showData template fieldDef  mddata editable audit />
     </#if>

</#macro>

<#macro viewField template fieldDef  mddata=[] editable=false audit=[]>
	 <#assign id=template.name+"_"+fieldDef.name/>
	 <#assign label>
        <@msg template.name+"."+fieldDef.name/>
     </#assign>
     <div class="form-group field-component view-mode" id="${template.name}-${id}">
     <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
     <div class="col-sm-9" id="${id}">
     <@viewFieldNoLabel template fieldDef  mddata editable audit/>
     </div>
     </div>

</#macro>

<#macro mdFieldDetail template fieldDef  mddata=[] editable=false audit=[] showLabel=true elId="" >
    <#if editable>
    	<@stdField template fieldDef mddata editable audit showLabel true elId="" />
    <#else>
    	<@viewField template fieldDef  mddata editable audit />
    </#if>
    <#return />
    <#--mdfield template="" fieldDef=""  mddata=[] divContainer=true noLabel=false-->
    <#assign id=template.name+"_"+fieldDef.name/>
	 <#assign label>
        <@msg template.name+"."+fieldDef.name/>
     </#assign>

    <#assign addClass=""/>
    <#if editable>
        <#assign addClass="view-editable-field"/>
    </#if>
    <div class="form-group" id="${template.name}-${id}">
    <#if showLabel>
	    	 <#assign label>
                <@msg template.name+"."+fieldDef.name/>
             </#assign>
	    <label for="${id}">

		<#if template.auditable && audit??>
		<a hidefocus="hidefocus" href="#${template.name}_${fieldDef.name}_audit" class="btn-link" role="button" data-toggle="modal" title="Mostra audit trail" id="${template.name}_${fieldDef.name}_audit_btn" >
		<i class="icon-time"></i></a>

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

                    <#case "CHECKBOX">
                    <#case "RADIO">
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
<div id="${id}_audit" class="modal fade" tabindex="-1">
 <div class="modal-dialog">
  <div class="modal-content">
	<div class="modal-header no-padding">
		<div class="table-header">
			<button type="button" class="close" data-dismiss="modal" aria-hidden="true"><span class="white">&times;</span></button>
			Storico delle modifiche
		</div>
	</div>

	<div class="modal-body no-padding">
		<table class="table table-striped table-bordered table-hover no-margin-bottom no-border-top">
			<thead>
				<tr>
		            <th>Utente</th>
		            <th>Data</th>
		            <th>Tipo modifica</th>
		            <th>Valore vecchio</th>
		            <th>Valore nuovo</th>
		        </tr>
			</thead>

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

	<div class="modal-footer no-margin-top">
		<button class="btn btn-sm btn-danger pull-right" data-dismiss="modal"><i class="icon-remove"></i> Close</button>

	</div>
  </div><!-- /.modal-content -->
 </div><!-- /.modal-dialog -->
</div>


</#if>
</#macro>

<#macro startGroup>
	<#assign groupActive=true />
</#macro>

<#macro endGroup>
	<#assign groupActive=false />
</#macro>

<#macro auditTable template field element>
<#assign audit=[]/>
<#list element.auditData as auditData>
    <#if auditData.field.id==field.id>
    	<#assign audit=audit+[auditData]/>
	</#if>
</#list>
<div id="auditTable_${template.name}_${field.name}" title="Storico valori" style="display:none">
    <table class="pSchema">
        <tr>
            <th>Utente</th>
            <th>Data</th>
            <th>Tipo modifica</th>
            <th>Valore vecchio</th>
            <th>Valore nuovo</th>
        </tr>
        <tbody id='${template.name}_${field.name}-audit-table'>
            <#list audit as a>
            <#assign old=""/>
            <#assign new=""/>
                <#switch field.type>
                    <#case "DATE">
                            <#assign old=dateValue(a.getOldVals()[0])/>
                            <#assign new=dateValue(a.getNewVals()[0])/>
                        <#break>
                    <#case "ELEMENT_LINK">
                    	<#if a.getOldVals()[0]??>
                    	<#assign old=a.getOldVals()[0].titleString/>
                    	<#else>
                    	<#assign old=""/>
                    	</#if>
                    	<#if a.getNewVals()?? && a.getNewVals()[0]??>
                    	<#assign new=a.getNewVals()[0].titleString!"&nbsp;"/>
                    	<#else>
                    	<#assign new="&nbsp;"/>
                    	</#if>
                    <#break>
                    <#case "SELECT">
                    	<#if a.getOldVals()[0]??>
                    	<#assign old=a.getOldVals()[0]?split("###")[1]!"&nbsp;"/>
                    	<#else>
                    	<#assign old=""/>
                    	</#if>
                    	<#assign new=a.getNewVals()[0]?split("###")[1]!"&nbsp;"/>
                    <#break>
                    <#case "EXT_DICTIONARY">
                    	<#if a.getOldVals()[0]??>
                    	<#assign old=a.getOldVals()[0]?split("###")[1]!"&nbsp;"/>
                    	<#else>
                    	<#assign old=""/>
                    	</#if>
                    	<#assign new=a.getNewVals()[0]?split("###")[1]!"&nbsp;"/>
                    <#break>
                    <#default>
                    	<#assign old=a.getOldVals()[0]!"&nbsp;"/>
                    	<#assign new=a.getNewVals()[0]!"&nbsp;"/>
                </#switch>
            <tr>
                <td>${a.username}</td>
                <td>${a.modDt.time?datetime?string.short}</td>
                <td><@msg "system."+a.action/></td>
                <td>${old}</td>
                <td>${new}</td>
            </tr>
    </#list>
    </tbody>
    </table>
</div>
</#macro>

<#macro mdfield template="" fieldDef=""  mddata=[] divContainer=true noLabel=false, audit=[]>
	<#assign empty=[] />
	<#assign withLabel=!noLabel />
	<@stdField template fieldDef mddata true audit withLabel />
</#macro>

<#macro stdField template="" fieldDef=""  mddata=[] editable=true audit=[]  withLabel=true fastUpdate=false elId="">
	<#assign noLabel=!withLabel />
	<#assign id=fieldDef.name/>
	<#assign label=fieldDef.name/>
	<#if template!="">
	    <#assign id=template.name+"_"+fieldDef.name/>
	    <#assign label>
	        <@msg template.name+"."+fieldDef.name/>
	    </#assign>
	    <#assign labelJS="${messages[label]!label}" />
		<#if fieldDef.mandatory><#assign label="${label}<sup style=\"color:red\">*</sup>"/></#if>
		<#if template.auditable && audit??>
			<#assign label>
			<a hidefocus="hidefocus" href="#${template.name}_${fieldDef.name}_audit" class="btn-link" role="button" data-toggle="modal" title="Mostra audit trail" id="${template.name}_${fieldDef.name}_audit_btn" >
			<i class="icon-time"></i> </a> ${label}
			</#assign>
		</#if>
	</#if>
	<#if !withLabel && template.auditable && audit??>
			<a hidefocus="hidefocus" href="#${template.name}_${fieldDef.name}_audit" class="btn-link" role="button" data-toggle="modal" title="Mostra audit trail" id="${template.name}_${fieldDef.name}_audit_btn"
			style="float:left;padding-right:5px;">
			<i class="icon-time"></i></a>
	</#if>
	<#assign addClass=""/>
    <#if editable>
        <#assign addClass=" field-editable"/>
        <#else>
        <#assign addClass=" field-view"/>
    </#if>
    <#if fastUpdate>
        <#assign addClass=" field-inline-edit"/>
    </#if>
		<div class="${addClass}" id="${template.name}-${id}">
					<@script>
			if (!fieldTypes) var fieldTypes=new Object();
				fieldTypes["${id}"]="${fieldDef.type}";
			</@script>
	<#if template.auditable && audit??>
		<@footer>
		<div id="${id}_audit" class="modal fade" tabindex="-1">
		 <div class="modal-dialog">
		  <div class="modal-content">
			<div class="modal-header no-padding">
				<div class="table-header">
					<button type="button" class="close" data-dismiss="modal" aria-hidden="true"><span class="white">&times;</span></button>
					Storico delle modifiche
				</div>
			</div>

			<div class="modal-body no-padding">
				<table class="table table-striped table-bordered table-hover no-margin-bottom no-border-top">
					<thead>
						<tr>
				            <th>Utente</th>
				            <th>Data</th>
				            <th>Tipo modifica</th>
				            <th>Valore vecchio</th>
				            <th>Valore nuovo</th>
				        </tr>
					</thead>

					<tbody id='${id}-audit-table'>
		            <#list audit as a>
		            <#assign old=""/>
		            <#assign new=""/>
		                    <#if fieldDef.type=="DATE">
		                            <#assign old=dateValue(a.getOldVals()[0])/>
		                            <#assign new=dateValue(a.getNewVals()[0])/>
		                    </#if>
		                    <#if fieldDef.type=="SELECT" || fieldDef.type=="CHECKBOX" || fieldDef.type=="RADIO" || fieldDef.type=="EXT_DICTIONARY">
		                    	<#assign old=a.getOldVals()[0]!"&nbsp;"/>
		                    	<#assign new=a.getNewVals()[0]!"&nbsp;"/>
		                    	<#if old!="&nbsp;">
		                    		<#assign old=old?split("###")[1]/>
		                    	</#if>
		                    	<#if new!="&nbsp;">
		                    		<#assign new=new?split("###")[1]/>
		                    	</#if>
		                    <#else>
		                    	<#assign old=a.getOldVals()[0]!"&nbsp;"/>
		                    	<#assign new=a.getNewVals()[0]!"&nbsp;"/>
		                    </#if>
		                    <#if fieldDef.type=="ELEMENT_LINK">
			                    <#if a.getOldVals()[0]??>
			                    	<#assign old=getTitle(a.getOldVals()[0])/>
			                    <#else>
			                    	<#assign old="&nbsp;"/>
			                    </#if>
			                    <#if a.getNewVals()[0]??>
			                    	<#assign new=getTitle(a.getNewVals()[0])/>
			                   	<#else>
			                    	<#assign new="&nbsp;"/>
			                    </#if>
		                    </#if>
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

			<div class="modal-footer no-margin-top">
				<button class="btn btn-sm btn-danger pull-right" data-dismiss="modal"><i class="icon-remove"></i> Close</button>

			</div>
		  </div><!-- /.modal-content -->
		 </div><!-- /.modal-dialog -->
		</div>
		</@footer>
	</#if>

	<#assign size=10/>
		<#if fieldDef.size??><#assign size=fieldDef.size/></#if>

	<#switch fieldDef.type>
		<#case "TEXTBOX">
		    <#if fieldDef.macro??>
	        		<#assign x=fieldDef.macro/>
	         		<@.vars[x] id id label mddata?first!"" size noLabel fieldDef editable />
	        <#elseif fastUpdate>
				<#assign updateId=model['element'].id?string />
				<#if !noLabel >
				<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
				</#if>
				<div class="col-sm-9">
					<a class="field-component ${addClass} inline-field field-inline-anchor" href="#" id="${id}" data-type="text" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
				</div>
				<@script>
					$('#${id}').editable({
					   emptytext :"Valore mancante"
					});
				</@script>
			<#elseif noLabel>
				<@textboxNoLabel id id label mddata?first!"" size editable/>
	        <#else>
	            <@textbox id id label mddata?first!"" size editable/>
	        </#if>
	    <#break>
	    <#case "TEXTAREA">
	    	<#if fastUpdate>
				<#assign updateId=model['element'].id?string />
				<#--if !elId??> <#assign elId=model['element'].id?string /></#if-->
				<#if !noLabel >
				<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
				</#if>
				<div class="col-sm-9">
				<a class="inline-field field-inline-anchor" href="#" id="${id}" class="field-component ${addClass}" data-type="textarea" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
				</div>
				<@script>
					$('#${id}').editable({
					    emptytext :"Valore mancante"
					});
				</@script>
				<#elseif noLabel>
					<@textareaNoLabel id id label 40 3 mddata?first!"" editable/>
		    	<#else>

		        	<@textarea id id label 40 3 mddata?first!"" editable/>
		        </#if>
	        <#break>
	    <#case "DATE">
	    	<#if fastUpdate>
				<#assign updateId=model['element'].id?string />
				<#if !noLabel >
				<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
				</#if>
				<div class="col-sm-9">
					 <a class="inline-field field-inline-anchor field-component ${addClass}" href="#" id="${id}" data-type="date" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${mddata?first.time?string("dd/MM/yyyy")!""}</a>
				    <@script>
				    $('#${id}').editable({
					    format: 'dd/mm/yyyy',
					    viewformat: 'dd/mm/yyyy',
					    datepicker: {
					    	weekStart: 1
					    }
				    });
				    </@script>
				</div>
			<#elseif noLabel>
	    		<@datePickerNoLabel id id label mddata?first!"" editable/>
	    	<#else>
	        	<@datePicker id id label mddata?first!"" editable/>
	        </#if>
	        <#break>
	    <#case "SELECT">
	        <#if fieldDef.macro??>

				   <#if model['element']??>
				   		<#assign updateId=model['element'].id?string />
		           <#else>
		           		<#assign updateId=""/>
		           </#if>
		           <#assign x=fieldDef.macro/>
		           <#assign label>
                                                   <@msg template.name+"."+fieldDef.name/>
                                                </#assign>

			       	<#if fastUpdate>
                        <#attempt>
					   		<@.vars[x] id id label mddata?first!"" size noLabel fieldDef editable true updateId/>
				       	<#recover>
			       		<#attempt>
			           		<@.vars[x] id id label mddata?first!"" size noLabel fieldDef editable/>
			           	<#recover>
			           		<@.vars[x] id id label null mddata?first!"" editable/>
			           	</#attempt>
			       	</#attempt>
				   <#else>

				   		<#attempt>
			           		<@.vars[x] id id label mddata?first!"" size noLabel fieldDef editable/>
			           	<#recover>
			           		<@.vars[x] id id label null mddata?first!"" editable/>
			           	</#attempt>
				   </#if>
	        <#elseif fastUpdate>
				<#assign updateId=model['element'].id?string />
				<#if !noLabel >
				<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
				</#if>
				<#assign value=mddata?first!""/>
				<#assign valueText=value?split("###")[1]/>
				<div class="col-sm-9">
					<a href="#" class="inline-field" id="${id}" data-type="select2" data-pk="1" data-value="${value}" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${valueText}</a>
				</div>
				<@script>
				<#assign keys = fieldDef.availableValuesMap?keys>

				$('#${id}').editable({
					source: [
						<#list keys as key>
							{id: "${key?html}###${fieldDef.availableValuesMap[key]?html}", text: "${fieldDef.availableValuesMap[key]?html}"}<#if key_has_next>,</#if>
					    </#list>
					],
					select2: {
					multiple: false,
					emptytext :"Valore mancante"
				}
				});
			</@script>
			<#elseif noLabel>
                <@selectHashNoLabelPlus id id label null mddata?first!"" editable/>
            <#else>
                <@selectHashPlus id id label null mddata?first!"" editable/>
            </#if>

	        <#break>
	    <#case "RADIO">
		     <#if fieldDef.macro??>
    			<#assign x=fieldDef.macro/>
	            <@.vars[x] id id label fieldDef.availableValuesMap mddata?first!""/>
	         <#elseif fastUpdate>
				<#assign updateId=model['element'].id?string />
				<#--if !elId??> <#assign elId=model['element'].id?string /></#if-->
				<#if !noLabel >
				<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
				</#if>
			<a class="field-inline-anchor" href="#" id="${id}" class="field-component ${addClass}" data-type="radio" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/update/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>

			<#elseif noLabel>
	    		<@radioNoLabel id id label fieldDef.availableValuesMap mddata?first!"" editable/>
	    	<#else>
	        	<@radioHash id id label fieldDef.availableValuesMap mddata?first!"" editable/>
	        </#if>

	        <#break>
	    <#case "CHECKBOX">
	    	<#if fieldDef.macro??>
	    	     		<#assign x=fieldDef.macro/>
	            <@.vars[x] id id label fieldDef.availableValuesMap mddata  editable/>
	        <#elseif fastUpdate>
				<#assign updateId=model['element'].id?string />
				<#if !noLabel >
				<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
				</#if>
			<a class="field-inline-anchor" href="#" id="${id}" class="field-component ${addClass}" data-type="checkbox" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/update/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>

			<#elseif noLabel>
	    		<@checkboxNoLabel id id label fieldDef.availableValuesMap mddata  editable/>
	    	<#else>
	        	<@checkboxHash id id label fieldDef.availableValuesMap mddata editable/>
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
	         		<@.vars[x] id id label "${baseUrl}/app/rest/documents/getLinkableElements/${fieldDef.id}" "title" selectedValues "id", selectedIds fieldDef.availableValuesMap fieldDef  editable/>
	         	<#else>
	         		<@singleAutoCompleteFBNoLabel id id label "${baseUrl}/app/rest/documents/getLinkableElements/${fieldDef.id}" "title" selectedValues "id", selectedIds  editable/>
	        	</#if>
	        <#else>
	        	<@singleAutoCompleteFB id id label "${baseUrl}/app/rest/documents/getLinkableElements/${fieldDef.id}" "title" selectedValues "id", selectedIds  editable/>
			</#if>
	        <#break>
	         <#case "EXT_DICTIONARY">
	         <#if mddata[0]??>
		            <#assign selectedIds=[mddata[0]]/>
	                    <#assign selectedValues=[mddata[0]?split("###")[1]]/>

		        <#else>
		            <#assign selectedValues=[]/>
		            <#assign selectedIds=[]/>
		        </#if>
	          <#if fieldDef.macro??>
	        		<#assign x=fieldDef.macro/>
            <@.vars[x] id id label "${fieldDef.externalDictionary}" "title" selectedValues "id", selectedIds template.name noLabel fieldDef editable/>
        	<#else>
		        <script>
		        var ${id}_addFilters="";
		        </script>

		        <#if fieldDef.addFilterFields??>
		        <script>
		        var ${id}_addFilters="${fieldDef.addFilterFields}";
		        </script>

		        <!--GC 02/10/2015 -->
		        <!-- Passaggio dello userid nello script IdCentroStudioSfoglia.php per filtrare UO e PI sul PI che inserisce il centro-->
		        <#assign remoteUser="" />
			        <#if userDetails.hasRole("PI")>
								<#assign remoteUser=userDetails.username />
								<script>
					        ${id}_addFilters+=",ui=${remoteUser}";
					      </script>
							</#if>

		        </#if>
		        <#if noLabel>
		        	<@singleAutoCompleteFunctionFBNoLabel id id label "${fieldDef.externalDictionary}" "title" selectedValues "id", selectedIds template.name editable/>
		        <#else>
		        	<@singleAutoCompleteFunctionFB id id label "${fieldDef.externalDictionary}" "title" selectedValues "id", selectedIds template.name editable/>
				</#if>
			</#if>
	        <#break>
	</#switch>

	</div>

</#macro>



<#function getLabel id>
	<#return messages[id]!id/>
</#function>

<#macro msg id>
    <@security.authorize ifAnyGranted="tech-admin">
        <span data-msg="${id}">
      </@security.authorize>
  	${messages[id]!id}
  <@security.authorize ifAnyGranted="tech-admin">
        </span>
        <button data-label-change="${id}" class="btn btn-info btn-xs pen-selected"><i class="fa fa-pencil label-anchor"></i></button>
        <@script>
            $('[data-label-change="${id}"]').unbind('click');
            $('[data-label-change="${id}"]').click(function(e){
                e.preventDefault();
                labelId=$(this).attr('data-label-change');
                bootbox.prompt("Etichetta per "+labelId, function(result) {
                  if (result === null) {
                    console.log('close');
                  } else {
                    console.log(result);

                    $.post("${baseUrl}/app/rest/admin/messages/it_IT", { propName: labelId, value: result } ).done(function( data ) {
                        if (data.result!='OK') {bootbox.alert("Errore impostazione etichetta");}
                        else {$('[data-msg="'+labelId+'"]').html(result);}
                    });
                  }
                });
                e.stopPropagation();
                return false;
            });

        </@script>

  </@security.authorize>
</#macro>

<#macro msgJs id>${messages[id]!id}</#macro>

<#macro datePickerNoLabel id name label value="" editable=true>
	<#assign txtValue=""/>
	<#if value != "" >
	    <#assign txtValue=value.time?date?string("dd/MM/yyyy")/>
	</#if>
	<#if editable>
	<div class="col-sm-3">

	<div class="input-group input-group-sm input-append date"   >
			<input  type="text" name="${name}" id="${id}"  value="${txtValue}" data-date-format="dd/mm/yyyy" value="${txtValue}" class="form-control" />
			<span class="input-group-addon add-on"><i class="icon-calendar"></i></span>
		</div>
	</div>

	<@script>

		$( ".date" ).datepicker({autoclose:true, format:"dd/mm/yyyy"});
	</@script>
	<#else>
	<div class="col-sm-9">
		<span class="field-view-mode field-date" id="${id}">${txtValue}</span>
	</div>
	</#if>
</#macro>

<#macro datePicker id name label value="" editable=true >
	<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
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


<#macro radioNoLabel id name label values={} value="" editable=true>
<div class="col-sm-9">
<#if editable>
    <#assign keys = values?keys>
    <#list keys as key>
        <span class="x-radio-input x-field-${name}">
        	<div class="radio">
				<label>
					<input type="radio" class="ace" id="${id}" name="${name}" value="${key?html}###${values[key]?html}" <#if (value?split("###")[0])==key>checked</#if> title="${values[key]}"><span class="lbl"> ${values[key]}</span>
				</label>
			</div>

        </span>
    </#list>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
<#else>
 <#assign keys = values?keys>
    <span class="field-view-mode field-radio" id="${id}">
        <#list keys as key>
        	<#if (value?split("###")[0])==key>
        		${values[key]}
        	</#if>
		</#list>
    </span>
</#if>
</div>
</#macro>




<#macro radioHash id name label values={} value="" editable=true>
<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<@radioNoLabel id name label values value/>
</#macro>


<#macro checktextNoLabel id name label values={} selectedValues=[] editable=true>
	<div class="checkbox-container col-sm-9">
		<#if editable>
		    <#assign keys = values?keys>
		    <#list keys as key>
		    	<#assign isSelected=false/>
		    	<#assign value="NKNV###NKNV"/>
		    	<#list selectedValues as selectedValue>
		    		<#if (selectedValue?split("###")[0])==key>
		    			<#assign value=selectedValue/>
		    			<#assign isSelected=true/>
					</#if>
		    	</#list>
		   		<span class="col-sm-9 x-checkbox-input x-field-${name}">
		    		<div class="checkbox">
						<label>
							<input autocomplete='off' type="checkbox" class="ace" id="${id}-code${key}" name="${name}" data-id="${id}-code${key?html}" data-code="${key?html}" <#if (value?split("###")[0])==key>checked="checked" value="${value?split("###")[0]}###${value?split("###")[1]}"<#else> value="${key?html}###${values[key]?html}"</#if> title="${values[key]}"><span class="lbl"> ${values[key]}</span>
							<input type='text' disabled="true" id="${id}-decode${key}" value="<#if (value?split("###")[0])==key>${value?split("###")[1]}</#if>">
						</label>
					</div>
		        </span>
		        <@script>
				$("#${id}-code${key}").change(function(){
					console.log("Check ${key} "+$(this).is(":checked"));
					if ($(this).is(":checked")){
						$('#${id}-decode${key}').attr('disabled',false);
					}else {
						$('#${id}-decode${key}').attr('disabled',true);
						$('#${id}-decode${key}').val("");
					}
				});

				$('#${id}-decode${key}').change(function(){
					$("#${id}-code${key}").val("${key?html}###"+$('#${id}-decode${key}').val());
				});

				if ($("#${id}-code${key}").is(":checked")){
					$('#${id}-decode${key}').attr('disabled',false);
				}else {
					$('#${id}-decode${key}').attr('disabled',true);
					$('#${id}-decode${key}').val("");
				}

			</@script>
		    </#list>

			<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
			    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
			    <span id="alert-msg-${id}"></span>
			</span>
		<#else>
		 <#assign keys = values?keys>
		    <span class="field-view-mode field-check">
		    	<#list keys as key>
                    <#assign isSelected=false/>
                    <#assign value="NKNV###NKNV"/>
                    <#list selectedValues as selectedValue>
                        <#if (selectedValue?split("###")[0])==key>
                            <#assign value=selectedValue/>
                            <#assign isSelected=true/>
                        </#if>
                    </#list>
		    		<#if (value?split("###")[0])==key>
		        		<i class="icon-check"></i>
		        	<#else>
		        		<i class="icon-check-empty"></i>
		        	</#if>
		        	${values[key]}
		        	<#--else>
		        		<#assign thisSelected=false>
		        		<#assign thisSelectedDecode="">
		        		<#list selectedValues as sItem>
		        			<#if sItem?split("###")[0]==key>
		        				<#assign thisSelected=true>
		        				<#assign thisSelectedDecode=sItem?split("###")[1]>
		        			</#if>
		        		</#list>
		      			<#if thisSelected>
		      				<i class="icon-check"></i> ${values[key]}: <strong>${thisSelectedDecode}</strong>
		      			<#else>
		      				<i class="icon-check-empty"></i> ${values[key]}: __________________
		      			</#if>

		        	</#if-->
		        	<#if key_has_next><br/></#if>
		    	</#list>
		    </span>
		</#if>
	</div>
</#macro>

<#macro checkboxNoLabel id name label values={} selectedValues=[] editable=true>
<div class="checkbox-container col-sm-9">
<#if editable>
    <#assign keys = values?keys>
    <#list keys as key>
    	 <#assign isSelected=false/>
		    	<#assign value="NKNV###NKNV"/>
		    	<#list selectedValues as selectedValue>
		    		<#if (selectedValue?split("###")[0])==key>
		    			<#assign value=selectedValue/>
		    			<#assign isSelected=true/>
					</#if>
		    	</#list>
   		<span class="col-sm-9 x-checkbox-input x-field-${name}">
    		<div class="checkbox">
				<label>

					<input autocomplete='off' type="checkbox" class="ace" id="${id}" name="${name}" value="${key?html}###${values[key]?html}" <#if (value?split("###")[0])==key>checked="checked"</#if> title="${values[key]}"><span class="lbl"> ${values[key]}</span>

				</label>
			</div>
        </span>
    </#list>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
<#else>
 <#assign keys = values?keys>
    <span class="field-view-mode field-check">
    	<#list keys as key>
    	<#if value??>
    		<#if (value?split("###")[0])==key>
        		<i class="icon-check"></i>
        	<#else>
        		<i class="icon-check-empty"></i>
        	</#if>
        	${values[key]}
        	<#if key_has_next><br/></#if>
    	<#else>

    	</#if>
    	</#list>
    </span>
</#if>
</div>
</#macro>
<#macro viewFieldNoLabelStartGroup id name template fieldDef  mddata=[] editable=false audit=[] >
	<@startGroup />
    <@showData template fieldDef  mddata editable audit />
</#macro>

<#macro viewFieldNoLabelEndGroup  id name template fieldDef  mddata=[] editable=false audit=[] >
	<#if editable>
	<@endGroup />
    <#else>
	<@endGroup />
	<#--/ul-->
	</#if><@showData template fieldDef  mddata editable audit />
</#macro>

<#macro checkboxNoLabelStartGroup id name label values={} value=[] editable=true>
	<#if editable>
	<@startGroup />
	<#else>
	<@startGroup />
	<#--ul-->
	</#if>
    <@checkboxNoLabel id name label values value editable/>
</#macro>

<#macro checkboxNoLabelEndGroup id name label values={} value=[] editable=true>
	<@endGroup />
    <@checkboxNoLabel id name label values value editable/>
</#macro>


<#macro checkboxHash id name label values={} value=[] editable=true>
<label class="col-sm-3 control-label no-padding-right"  for="${id}">${label}:</label>
<@checkboxNoLabel id name label values value editable/>
</#macro>


<#macro selectHashNoLabel id name label values={} value="">


<select id="${id}" name="${name}" style="min-width:40%">
    <option></option>
    <#assign keys = values?keys>
    <#list keys as key>
        <option value="${key}" <#if value=key>selected</#if>>${values[key]}</option>
    </#list>
</select>
<@script>
$('#${id}').select2();
</@script>
</#macro>

<#macro selectHashNoLabelPlus id name label values={} value="" editable=true>
<#assign selectedCode=""/>
<#assign selectedDecode=""/>
<#if value?? && value?contains("###")>

<#assign selectedCode=value?split("###")[0]/>
<#assign selectedDecode=value?split("###")[1]/>
</#if>
<#if editable>
<@script>

(function($,window){

		console.log("${id} :${value?html}");
		$.getJSON("${baseUrl}/app/rest/documents/values/fieldname/${id}", function(data){
			var val="${value?html}";
			valuesArray=new Array();
			for (var i in data.resultMap){

				itm=new Object();
				itm.id=i+"###"+data.resultMap[i];
				itm.text=data.resultMap[i];
				valuesArray[valuesArray.length]=itm;
			}
			console.log(valuesArray);
			 $("#${id}-select").select2({ data: valuesArray });
			  $('#${id}-select').select2("val",val);
		var addAltroField=function(value){
			$('#${id}-select').after('<input type="text" id="${id}-altro" name="${name}-altro" />');
	       	$('#${id}-altro').val(value);
	       	$('#${id}-altro').change(function(){
				if ($('#${id}-select').val().indexOf('-9999###')==0){
	                $('#${id}').val('-9999###' + $('#${id}-altro').val());
	            }
			});
		}
        if (val.indexOf('-9999###')==0) {
	       console.log(val);
	       addAltroField("${selectedDecode?html}");

        }

		var removeAltroField=function(){
			$('#${id}-altro').remove();

		}

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

		$('#${id}-select').change(function(){
			console.log($(this).val());
			if ($(this).val().indexOf('-9999###')==0){
				console.log("devo mostrare il campo altro");
				addAltroField("");
				$('#${id}-altro').focus();
			}else {
				removeAltroField();
				// $('#${id}').val($('#${id}-select').select2('data').id);
			}
		});
		});

})(jQuery,window);




</@script>
<div class="col-sm-9">
<input id="${id}-select" name="${name}-select" <#if !editable>disabled="disabled"</#if>/>
    <#--
    <option></option>
    <#assign keys = values?keys>
    <#list keys as key>
        <option value="${key?html}###${values[key]?html}"
                <#if key?split("###")[0]=selectedCode>selected</#if>>${values[key]}</option>
    </#list>

</select>
-->
<input type="hidden" id="${id}" name="${name}"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</div>
<#else>
<span class="field-view-mode field-select" id="${id}">${selectedDecode}</span>
</#if>
</#macro>

<#macro selectHashPlus id name label values={} value="" editable=true>
<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
<@selectHashNoLabelPlus id name label values value/>
</#macro>


<#macro selectHash id name label values={} value="">
<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
<div class="col-sm-9">
<@selectHashNoLabel id name label values value/>
</div>
</#macro>


<#macro multiAutoCompleteFunctionFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] templateName=""  editable=true>
</#macro>

<#macro singleAutoCompleteFunctionFBNoLabel id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] templateName="" editable=true>
    <@multiAutoCompleteFunctionNoLabel id name label searchScript searchValue selectedValues true true searchId selectedIds templateName editable/>
</#macro>

<#macro singleAutoCompleteFunctionFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] templateName="" editable=true>
    <@multiAutoCompleteFunction id name label searchScript searchValue selectedValues true true searchId selectedIds templateName editable/>
</#macro>


<#macro multiAutoCompleteFunction id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] templateName="" editable=true>
    <label for="${id}" class="col-sm-3 control-label no-padding-right" >${label}:</label>
    <@multiAutoCompleteFunctionNoLabel id name label searchScript searchValue selectedValues theme single searchId selectedIds templateName editable/>
</#macro>

<#assign usedTokenInput=0/>



<#macro multiAutoCompleteFunctionNoLabel id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] templateName="" editable=true>
<#if editable>
<#assign usedTokenInput=usedTokenInput+1/>
<div class="col-sm-9">
    <select id="${id}-select" name="${name}">
    </select><input type="text" id="${id}-altro" name="${name}" style="display:none">
    </div>
    <input type="hidden" id="${id}" name="${name}"/>
    <@script>
    if (!dependency) var dependency=new Object();

    	if (${id}_addFilters && ${id}_addFilters!=""){
    		console.log(${id}_addFilters);
    		filters=${id}_addFilters.split(",");
    		console.log(filters);
    		var addedParam="";
    		for (l=0;l<filters.length;l++){
				secondSplit=filters[l].split("=");
				console.log(secondSplit);
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


    	function buildScriptUrl_${id}(){
    		var addedParam="";
    		if (${id}_addFilters && ${id}_addFilters!=""){
    		filters=${id}_addFilters.split(",");

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
				addedParam+="&";
			}
			}
			console.log("QUI"+addedParam);
			return '${searchScript}?'+addedParam;
    	}

    	function populateSelect_${id}(){
    		$('#${id}-select').select2("val", "");
    	    $('#${id}-select').html("");
    	    $('#${id}-select').append("<option></option>");

    		var url=buildScriptUrl_${id}();
    		var valorizza=function(){
    			console.log('niente da valorizzare');
    			return false;
    		};
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
                            	console.log('trovato valore');
                            	valorizza=function(){
                            		console.log('tento la valorizzazione del campo');
	                            	$('#${id}-select').select2("val", "${selectedIds[idx]?html}");
                            	var myVal="${selectedIds[idx]?html}";
                            	if(myVal.indexOf("-9999###")==0){
	                            	var altroValue=$('#${id}-select option[value^=-9999###]').val();
                					$('#${id}-select').select2("val",altroValue);
            					}
	                            }	;
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
						$('#${id}-select').select2("val",altroValue);
	                	$('#${id}-altro').show();
	                	$('#${id}-altro').val(decode);
                	}
    	    	}
    	    	if(val.indexOf('-9999###')){
    	    		var altroValue=$('#${id}-select option[value^=-9999###]').val();
                	$('#${id}-select').select2("val",altroValue);
    	    	}

    	    	$('#${id}-select').append("<option value=\""+val+"\" "+selected+">"+field.title+"</option>");

			   });
			   valorizza();
			   if (dependency['${id}'])
			    for(var index in dependency['${id}']) {
				  setTimeout('populateSelect_'+dependency['${id}'][index]+'()',50);
				}

			  });
			}
    	}

    </@script>
    <#else>
    	<span class="field-view-mode field-ext-dic">
    		<#if searchId!="">
    						<#assign idx=0/>

                            <#list selectedValues as sv>
                            	${selectedIds[idx]?split("###")[1]?html}
                            	<#if sv_has_next>, </#if>
                            	<#assign idx=idx+1/>
                            </#list>
                        <#else>
                            <#list selectedValues as sv>
                            ${sv?html}
                            <#if sv_has_next>, </#if>
                            </#list>
        	</#if>
    	</span>
    </#if>
</#macro>

<#macro multiAutoCompleteFunctionNoLabel_ id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] templateName="" editable=true>
<#return>
sadasdasdsadasdsa
<#assign usedTokenInput=usedTokenInput+1/>
    <input type="text" id="${id}" class="randomClass-${usedTokenInput}" name="${name}"/>
    <@script>
    	function rebuildToken_${id}(){
    		$('#form-${id}').find(".token-input-list-facebook").remove();
        	$('#${id}.randomClass-${usedTokenInput}').html("");
        	buildToken_${id}();
        	$('#${id}').tokenInput('clear');

    	}


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


        buildToken_${id}();

    </@script>
</#macro>

<#macro extDictionaryAutocomplete id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel>
    	<@singleAutoCompleteFBNoLabel id name label fieldDef.externalDictionary searchValue selectedValues searchId selectedIds  editable/>
    <#else>
    	<@singleAutoCompleteFB id name label fieldDef.externalDictionary searchValue selectedValues searchId selectedIds  editable/>
    </#if>
</#macro>

<#macro multiAutoCompleteFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] editable=true>
      <@multiAutoComplete id name label searchScript searchValue selectedValues true false searchId selectedIds/>
</#macro>

<#macro singleAutoCompleteFBNoLabel id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] editable=true>
    <@multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues true true searchId selectedIds editable/>
</#macro>

<#macro singleAutoCompleteFB id name label searchScript searchValue selectedValues=[] searchId="" selectedIds=[] editable=true>
    <@multiAutoComplete id name label searchScript searchValue selectedValues true true searchId selectedIds/>
</#macro>


<#macro multiAutoComplete id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] editable=true>
    <label for="${id}">${label}:</label>
    <@multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues theme single searchId selectedIds/>
</#macro>

<#assign usedTokenInput=0/>
<#--
<#macro multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] editable=true>
<input id="${id}" name="${name}"/>
<@script>
	<#assign data_values="{}"/>
			<#assign idx=0>
			<#list selectedIds as item>
			<#assign stringValue=""/>
			<#assign codeValue=""/>
			<#if item?string?matches("(.*)###(.*)")>
				<#assign splitted=item?string?split("###")/>
				<#assign codeValue=splitted[0]/>
				<#assign stringValue=splitted[1]/>
			<#else>
				<#assign codeValue=item/>
				<#assign stringValue=selectedValues[idx]/>
			</#if>
				<#if idx gt 0><#assign data_values=data_values+","/><#else><#assign data_values=""/></#if>
					<#assign data_values=data_values+"{id: \"${codeValue}\", text: \"${stringValue}\"}"/>
				<#assign idx=idx+1/>
			</#list>

	$('#${id}').select2({
	<#if !single>
	multiple: true,
	</#if>
	minimumInputLength: 1,
	<#if single>
	maximumSelectionSize: 1,
	</#if>
	containerCssClass:'select2-ace',
	allowClear: true,
	ajax: {
			url:'${searchScript}',
			dataType: 'json',
			data: function (term, page) {
						return {
							term: term
						};
					},
			results: function (data, page) {
				var length=data.length;
				var results=new Array();
				for(var i=0;i<length;i++){
					results[i]={id:data[i].${searchId},text:data[i].${searchValue}};
				}
				return {results: results, more: false};
			}
		},
		initSelection: function(element, callback) {
		<#if !single>
			data=[${data_values}];
		<#else>
			data=${data_values};
		</#if>
			callback(data);
		}
	});

</@script>
</#macro>
-->


<#macro multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] editable=true>
<#if editable>
<#global page=page+{"scripts" : page.scripts+["tokenInput"]}/>
<#assign usedTokenInput=usedTokenInput+1/>
    <input type="text" id="${id}" class="randomClass-${usedTokenInput}" name="${name}"/>
    <@script>
        $("#${id}.randomClass-${usedTokenInput}").attr('isTokenInput',true);

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
                },
                onAdd: function (item){
                	console.log(item);
                		if(typeof item.id==="string" && item.id.match("^-9999###")){
                			$("#informations-${id}Altro").show();
                		}
                		else{
                			$("#informations-${id}Altro input").val("");
                			$("#informations-${id}Altro").hide();
                		}
                },
                onDelete: function (item){
                	console.log(item);
                			$("#informations-${id}Altro input").val("");
                			$("#informations-${id}Altro").hide();
                },
                onReady: function(){
                	<#assign toShow=false>
                	<#if selectedValues??>
                		<#if searchId!="">
                		    <#assign idx=0/>
                		    <#list selectedValues as sv>
                		    	<#if selectedIds[idx]?string?starts_with("-9999###")>
                		        <#assign toShow=true>
                		      </#if>
                		      <#assign idx=idx+1/>
                		    </#list>
                		<#else>
                		    <#list selectedValues as sv>
                		    	<#if sv="-9999">
                		        <#assign toShow=true>
                		      </#if>
                		    </#list>
                		</#if>

                	</#if>

                	<#if toShow>
                			$("#informations-${id}Altro").show();
                	<#else>
                			$("#informations-${id}Altro").hide();
                	</#if>

                }

            });

    </@script>
    <#else>
    	<span class="field-view-mode field-elementLink">
    		<#if selectedValues??>
                        <#if searchId!="">
                            <#assign idx=0/>
                            <#list selectedValues as sv>
                					${sv}
                					<#if sv_has_next>, </#if>
                                <#assign idx=idx+1/>
                            </#list>

                        <#else>
                            <#list selectedValues as sv>
                                ${sv}
                                <#if sv_has_next>, </#if>
                            </#list>
                        </#if>
        	</#if>
    	</span>
    </#if>
</#macro>

<#macro multiAutoCompleteNoLabel__ id name label searchScript searchValue selectedValues=[] theme=false single=false searchId="" selectedIds=[] editable=true>
<#assign usedTokenInput=usedTokenInput+1/>
    <input type="text" id="${id}" class="randomClass-${usedTokenInput}" name="${name}"/>
    <@script>
        $("#${id}.randomClass-${usedTokenInput}").attr('isTokenInput',true);

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

    </@script>
</#macro>


<#macro hidden id name value="">
<input type="hidden" name="${name}" id="${id}" value="${value!""}"/>
</#macro>

<#macro textboxNoLabel id name label value="" size=10 editable=true>
<div class="col-sm-9">
<#if editable>
<input type="text" <#if !editable>disabled="disabled"</#if> name="${name}" id="${id}" value="${value!""}" size="${size}"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
<#else>
	<span id="${id}" class="field-view-mode field-textbox">${value!""}</span>
</#if>
</div>
</#macro>

<#macro textbox id name label value="" size=10 editable=true>
<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
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


<#macro colorPicker id name label value="">
	<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<div class="col-sm-9">
	<div class="bootstrap-colorpicker">
																<input id="${id}" name="${id}" type="text" class="input-small" value="${value}" />
															</div>
	</div>
<@script>
	$('#${id}').colorpicker();
	$('#${id}').colorpicker().on('changeColor',function(ev){ $('#${id}').css("background-color",ev.color.toHex());
});
</@script>
</#macro>

<#macro fileChooser id name label value="">
<#if label!="">
<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
<div class="col-sm-4">
</#if>
	<input type="file" name="${name}" id="${id}" value=""/>
	<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    	<span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    	<span id="alert-msg-${id}"></span>
	</span>
<@script>
$('#${id}').ace_file_input({
					no_file:'Nessun file allegato',
					btn_choose:'Sfoglia',
					btn_change:'Cambia file',
					droppable:false,
					onchange:null,
					thumbnail:false //| true | large
					//whitelist:'gif|png|jpg|jpeg'
					//blacklist:'exe|php'
					//onchange:''
					//
				});
</@script>
<#if label!="">
</div>
</#if>
</#macro>

<#macro password id name label value="">
<label for="${id}" class="col-sm-3 control-label no-padding-right" >${label}:</label>
<input type="password" name="${name}" id="${id}" value="${value!""}"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>        </#macro>

<#macro textareaNoLabel id name label cols=40 rows=3 value="" editable=true >
<#if editable>
<div class="col-sm-9">
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
<textarea cols="${cols}" rows="${rows}" type="text" name="${name}" id="${id}">${value!""}</textarea>
</div>
<#else>
<span class="field-view-mode field-textarea" id="${id}">${value!""}</span>
</#if>

</#macro>

<#macro textarea id name label cols=20 rows=1 value="" editable=true>
<label for="${id}" class="col-sm-3 control-label no-padding-right" >${label}:</label>
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
    <#--assign url="${baseUrl}/app/documents"/-->
    <#assign url=""/>
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

<#macro tabbedView tabs=[] tabsContent=[] activeTab="" >

	<div class="tabbable" >
		<ul class="nav nav-tabs" >
			<#list tabs as currTab >
				<#if !(currTab.class??) >

					<#assign tab=currTab+{"class":""} />
					<#else>
					<#assign tab=currTab />
				</#if>

				<#if tab.active!false || activeTab=tab.target ><#assign tab=tab+{"class":tab.class+" active"} /><#elseif tab.disabled?? && tab.disabled><#assign tab=tab+{"class":tab.class+" disabled-tab"} /></#if>
				<#if tab.active!false || activeTab=tab.target ><#assign activeTab=tab.target /></#if>
				<li class="${tab.class}"><a href="#${tab.target}" data-toggle="tab" >${tab.label}</a></li>
			</#list>
		</ul>
		<div  class="tab-content" >
			<#list tabsContent as tab >
				<div id="${tab.id}" class="tab-pane <#if tab.id==activeTab>in active</#if> ${tab.cssClass!""}">
				${tab.content}
				</div>
			</#list>
		</div>
	</div>
</#macro>

<#macro infobox id icon color content title="" number="" stat="" statType=""  >

	<div id="${id}" class="infobox infobox-${color}" <#if title?? && title!="">title="${title}"</#if> >
		<div class="infobox-icon">
			<i class="ace-icon ${icon}"></i>
		</div>

		<div class="infobox-data">
			<span class="infobox-data-number">${number}</span>
			<div class="infobox-content">${content}</div>
		</div>
		<#if stat!="">
		<div class="stat stat-${statType}">${stat}%</div>
		</#if>
	</div>
</#macro>

<#macro onclick id complete=false>
	<#assign function>
	<#nested>
	</#assign>
	<#if complete>
	<@script>
		$('#${id}').on('click',${function});
	</@script>
	<#else>
	<@script>
		$('#${id}').on('click',function(event){
				${function}
			}
		);
	</@script>
	</#if>
</#macro>

<#macro modalbox id title body footer="" sticky=true>
<div id="${id}" class="modal fade">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
        <h4 class="modal-title">${title}</h4>
      </div>
      <div class="modal-body">
      	${body}
	  </div>
      <div class="modal-footer">
      	${footer}
	  </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->
</#macro>


<#macro widgetBox title iconClasses body>
	<div class="widget-box ">
		<div class="widget-header">
			<h4 class="lighter smaller">
				<i class="${iconClasses}"></i>
				${title}
			</h4>
		</div>
		<div class="widget-body">
			<div class="widget-main no-padding">
				${body}
			</div>
		</div>
	</div><!-- /widget-box -->
</#macro>

<#macro centroSelect id name label value="" size=30 noLabel=true fieldDef=null editable=false xEditable=false>
<#if !noLabel>
	<#if xEditable>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<#else>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	</#if>
</#if>

<div class="col-sm-9">
	<select name="${id}" id="${id}"><option></option></select>
</div>

<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parent'].parent.id />
<#else>
	<#assign parentId=el.parent.parent.id/>
</#if>
	<@script>
	console.log("qui");
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/Centro";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){
        		console.log(data[i].metadata.IdCentro_Struttura);
        			if ('${value}'==data[i].id+'###'+data[i].id) selected=" selected";
        			else selected="";
        			$('#${id}').append('<option '+selected+' value="'+data[i].id+'###'+data[i].id+'">'+data[i].metadata.IdCentro_PI[0].split('###')[1]+' ('+data[i].metadata.IdCentro_Struttura[0].split('###')[1]+')'+'</option>');

        	}
        	});

	</@script>
</#macro>

<#macro confezioneSelect id name label value="" size=30 noLabel=true fieldDef=null editable=false xEditable=false>
<#if !noLabel>
	<#if xEditable>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<#else>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	</#if>
</#if>

<div class="col-sm-9">
	<select name="${id}" id="${id}"><option></option></select>
</div>

<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parent'].parent.id />
<#else>
	<#assign parentId=el.parent.parent.id/>
</#if>
	<@script>
		console.log("qui");
  	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/FarmacoCarico";
  	$.getJSON( url, function( data ) {
	  	console.log(data);
	  	for (i=0;i<data.length;i++){
	  		ciclofor(data[i]);
	  	}
  	});
   var residui={};
  	function ciclofor (current){
  		console.log(current.metadata.DatiFarmacoCarico_RifBolla);
  		console.log(current.id);
			url="${baseUrl}/app/rest/documents/getElementsByParentAndType/"+current.id+"/FarmacoCaricoKit";
			$.getJSON( url, function( data1 ) {
				console.log(data1);
				for (j=0;j<data1.length;j++){
					console.log(current);
					residui[data1[j].id+'###'+data1[j].id]=parseInt(data1[j].metadata.DatiFarmacoCaricoKitResiduo_QuantitaResidua);
	  			if ('${value}'==data1[j].id+'###'+data1[j].id) selected=" selected";
	  			else selected="";

	  			var ts=parseInt(data1[j].metadata.DatiFarmacoCaricoKitResiduo_DataUltimaScadenza);
	  			var theDate = new Date(ts);
	  			var LocaleDateString = theDate.toLocaleDateString();

	  			$('#${id}').append('<option '+selected+' value="'+data1[j].id+'###'+data1[j].id+'">'+'Bolla:'+current.metadata.DatiFarmacoCarico_RifBolla+' - Lotto: '+data1[j].metadata.DatiFarmacoCaricoKit_NumeroLotto+' - Kit: '+data1[j].metadata.DatiFarmacoCaricoKit_NumeroKit+' - Residuo: '+data1[j].metadata.DatiFarmacoCaricoKitResiduo_QuantitaResidua+' - Scadenza: '+LocaleDateString+'</option>');
				}
			});
  	}

	</@script>
</#macro>

<#macro firmaFileSelectAll tipodoc id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=false updateId="">

<#if !noLabel>
	<#if xEditable>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<#else>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	</#if>
</#if>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
<#else>
	<#assign parentId=el.parent.id/>
</#if>
<#if xEditable && editable>
	<#if value?split("###")?size gt 1>
	<#assign displayValue=value?split("###")[1]/>
	<#else>
		<#assign displayValue=""/>
	</#if>
		<div class="col-sm-12">
			<a href="#" id="${id}" data-type="select2" data-pk="1" data-value="ru" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="Effettua la selezione">${displayValue}</a>
		</div>
<@script>
	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
    var source_${id}=new Array();
    $.getJSON( url, function( data ) {
    	console.log("-----");
      	for (i=0;i<data.length;i++){
      		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==${tipodoc}){
      			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
    			else selected="";
       			option=new Object();
      			option.id=data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
       			option.text=data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
       			option.selected=selected;
       			source_${id}[source_${id}.length]=option;
       			if (data[i].auditFiles!=null){
      				for (a=0;a<data[i].auditFiles.length;a++){
      					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
      					else selected="";
      					option=new Object();
      					option.id=data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
      					option.text=data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
      					option.selected=selected;
      					source_${id}[source_${id}.length]=option;
      				}
      			}
      		}
      	}
      	$('#${id}').editable({
      		source: source_${id},
      		select2:{
      			initSelection: function (element, callback) {
			        var data = new Object;
			        data.id="${value}";
			        data.text="${displayValue}";
			        callback(data);
			    }
      		}
		});
    });

</@script>
<#else>
	<div class="col-sm-9">
<select name="${id}" id="${id}"><option></option></select>
</div>
	<@script>
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==${tipodoc}){
        			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";
        			$('#${id}').append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        			else selected="";
        					$('#${id}').append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');
        				}
        			}
        		}
        	}
        	});
	</@script>
</#if>
</#macro>

<#macro firmaFileSelect id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=false updateId="">
	<@firmaFileSelectAll "1" id name label value size noLabel fieldDef editable xEditable updateId/>
</#macro>

<#macro firmaFileSelect2 id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=false updateId="">
	<@firmaFileSelectAll "2" id name label value size noLabel fieldDef editable xEditable updateId/>
</#macro>

<#macro firmaFileSelect3 id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=false updateId="">
	<@firmaFileSelectAll "3" id name label value size noLabel fieldDef editable xEditable updateId/>
</#macro>

<#macro firmaFileSelect4 id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=false updateId="">
	<@firmaFileSelectAll "4" id name label value size noLabel fieldDef editable xEditable updateId/>
</#macro>

<#--
<#macro firmaFileSelect2 id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=true  updateId="">
<#if !noLabel>
	<#if xEditable>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<#else>
		<label for="${id}">${label}</label>
	</#if>
</#if>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
<#else>
	<#assign parentId=el.parent.id/>
</#if>
<#if xEditable && editable>
	<#if value?split("###")?size gt 1>
	<#assign displayValue=value?split("###")[1]/>
	<#else>
		<#assign displayValue=""/>
	</#if>
		<div class="col-sm-12">
			<a href="#" id="${id}" data-type="select2" data-pk="1" data-value="ru" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="Effettua la selezione">${displayValue}</a>
		</div>
	<@script>
		url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
	    var source_${id}=new Array();
	    $.getJSON( url, function( data ) {
	    	console.log("-----");
	      	for (i=0;i<data.length;i++){
	      		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==2){
	      			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
	    			else selected="";
	       			option=new Object();
	      			option.id=data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
	       			option.text=data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
	       			option.selected=selected;
	       			source_${id}[source_${id}.length]=option;
	       			if (data[i].auditFiles!=null){
	      				for (a=0;a<data[i].auditFiles.length;a++){
	      					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
	      					else selected="";
	      					option=new Object();
	      					option.id=data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
	      					option.text=data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
	      					option.selected=selected;
	      					source_${id}[source_${id}.length]=option;
	      				}
	      			}
	      		}
	      	}
	      	$('#${id}').editable({
	      		source: source_${id},
	      		select2:{
	      			initSelection: function (element, callback) {
				        var data = new Object;
				        data.id="${value}";
				        data.text="${displayValue}";
				        callback(data);
				    }
	      		}
			});
	    });
	</@script>
<#else>
	<select name="${id}" id="${id}"><option></option></select>
	<@script>
        	console.log('${value}');
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){
        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==2){
        			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";
        			$('#${id}').append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        			else selected="";
        					$('#${id}').append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');
        				}
        			}

        		}

        	}
        	});

	</@script>
</#if>
</#macro>

<#macro firmaFileSelect3 id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=false  updateId="">
<#if !noLabel>
	<#if xEditable>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<#else>
		<label for="${id}">${label}</label>
	</#if>
</#if>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
<#else>
	<#assign parentId=el.parent.id/>
</#if>
<#if xEditable && editable>
	<#if value?split("###")?size gt 1>
	<#assign displayValue=value?split("###")[1]/>
	<#else>
		<#assign displayValue=""/>
	</#if>
		<div class="col-sm-12">
			<a href="#" id="${id}" data-type="select2" data-pk="1" data-value="ru" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="Effettua la selezione">${displayValue}</a>
		</div>
	<@script>
		url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
	    var source_${id}=new Array();
	    $.getJSON( url, function( data ) {
	    	console.log("-----");
	      	for (i=0;i<data.length;i++){
	      		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==3){
	      			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
	    			else selected="";
	       			option=new Object();
	      			option.id=data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
	       			option.text=data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
	       			option.selected=selected;
	       			source_${id}[source_${id}.length]=option;
	       			if (data[i].auditFiles!=null){
	      				for (a=0;a<data[i].auditFiles.length;a++){
	      					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
	      					else selected="";
	      					option=new Object();
	      					option.id=data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
	      					option.text=data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
	      					option.selected=selected;
	      					source_${id}[source_${id}.length]=option;
	      				}
	      			}
	      		}
	      	}
	      	$('#${id}').editable({
	      		source: source_${id},
	      		select2:{
	      			initSelection: function (element, callback) {
				        var data = new Object;
				        data.id="${value}";
				        data.text="${displayValue}";
				        callback(data);
				    }
	      		}
			});
	    });
	</@script>
<#else>
	<select name="${id}" id="${id}"><option></option></select>
	<@script>
        	console.log('${value}');
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){

        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==3){

        			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";
        			$('#${id}').append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        			else selected="";
        					$('#${id}').append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');
        				}
        			}

        		}

        	}
        	});

	</@script>
</#if>
</#macro>

<#macro firmaFileSelect4 id name label value="" size=30 noLabel=true fieldDef=null editable=true xEditable=false  updateId="">
<#if !noLabel>
	<#if xEditable>
		<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
	<#else>
		<label for="${id}">${label}</label>
	</#if>
</#if>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
<#else>
	<#assign parentId=el.parent.id/>
</#if>
<#if xEditable && editable>
	<#if value?split("###")?size gt 1>
	<#assign displayValue=value?split("###")[1]/>
	<#else>
		<#assign displayValue=""/>
	</#if>
		<div class="col-sm-12">
			<a href="#" id="${id}" data-type="select2" data-pk="1" data-value="ru" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="Effettua la selezione">${displayValue}</a>
		</div>
	<@script>
		url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
	    var source_${id}=new Array();
	    $.getJSON( url, function( data ) {
	    	console.log("-----");
	      	for (i=0;i<data.length;i++){
	      		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==4){
	      			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
	    			else selected="";
	       			option=new Object();
	      			option.id=data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
	       			option.text=data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName;
	       			option.selected=selected;
	       			source_${id}[source_${id}.length]=option;
	       			if (data[i].auditFiles!=null){
	      				for (a=0;a<data[i].auditFiles.length;a++){
	      					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
	      					else selected="";
	      					option=new Object();
	      					option.id=data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
	      					option.text=data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName;
	      					option.selected=selected;
	      					source_${id}[source_${id}.length]=option;
	      				}
	      			}
	      		}
	      	}
	      	$('#${id}').editable({
	      		source: source_${id},
	      		select2:{
	      			initSelection: function (element, callback) {
				        var data = new Object;
				        data.id="${value}";
				        data.text="${displayValue}";
				        callback(data);
				    }
	      		}
			});
	    });
	</@script>
<#else>
	<select name="${id}" id="${id}"><option></option></select>
	<@script>

        	console.log('${value}');
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){

        		if(data[i].metadata.tipologiaContratto_TipoContratto[0].split('###')[0]==4){

        			if ('${value}'==data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName) selected=" selected";
        			else selected="";
        			$('#${id}').append('<option '+selected+' value="'+data[i].file.fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'">'+data[i].titleString+' (ver: '+data[i].file.version+') - '+data[i].file.fileName+'</option>');
        			if (data[i].auditFiles!=null){
        				for (a=0;a<data[i].auditFiles.length;a++){
        					if ('${value}'==data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName)  selected=" selected";
        			else selected="";
        					$('#${id}').append('<option '+selected+'  value="'+data[i].auditFiles[a].fileContentId+'_'+data[i].id+'###'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'">'+data[i].titleString+' (ver: '+data[i].auditFiles[a].version+') - '+data[i].auditFiles[a].fileName+'</option>');
        				}
        			}

        		}

        	}
        	});

	</@script>
</#if>
</#macro>
-->

<#macro emendamentoSelect id name label value="" size=30 noLabel=true fieldDef=null editable=true>
<#if !noLabel>
	<label class="col-sm-3 control-label" for="${id}">${label}:</label>
</#if>
<div class="col-sm-3">
<select name="${id}" id="${id}"><option></option></select>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
	<#assign parentEl=model['parent']/>
<#else>
	<#assign parentId=el.parent.id/>
	<#assign parentEl=el.parent/>
</#if>

<#if fieldDef.availableValuesMap.padre?? && fieldDef.availableValuesMap.padre=="1">
	<#assign studioId=parentEl.parent.id />
</#if>
<#if fieldDef.availableValuesMap.padre?? && fieldDef.availableValuesMap.padre=="2">
	<#assign studioId=parentEl.parent.parent.id />
</#if>



	<@script>

        	console.log('${value}','verifica');
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${studioId}/Emendamento";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){

        		console.log(data[i].metadata.DatiEmendamento_CodiceEme[0]);

        			if ('${value}'==data[i].id+'###'+data[i].metadata.DatiEmendamento_CodiceEme[0]) selected=" selected";
        			else selected="";

        			$('#${id}').append('<option '+selected+' value="'+data[i].id+'###'+data[i].metadata.DatiEmendamento_CodiceEme[0]+'">'+data[i].metadata.DatiEmendamento_CodiceEme[0]+'</option>');


        	}
        	});

	</@script>
</div>
</#macro>

<#macro emendamentoSelect1 id name label value="" size=30 noLabel=true fieldDef=null editable=true>
<#if !noLabel>
	<label for="${id}">${label}</label>
</#if>
<div class="col-sm-3">
<select name="${id}" id="${id}"><option></option></select>
<#assign parentId=""/>
<#if model['parentId']??>
	<#assign parentId=model['parentId']/>
<#else>
	<#assign parentId=el.parent.id/>
</#if>
<#assign studioId=el.parent.parent.parent.id />


	<@script>

        	console.log('${value}');
        	url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${studioId}/Emendamento";
        	$.getJSON( url, function( data ) {
        	console.log(data);
        	for (i=0;i<data.length;i++){

        		console.log(data[i].metadata.DatiEmendamento_CodiceEme[0]);

        			if ('${value}'==data[i].id+'###'+data[i].metadata.DatiEmendamento_CodiceEme[0]) selected=" selected";
        			else selected="";

        			$('#${id}').append('<option '+selected+' value="'+data[i].id+'###'+data[i].metadata.DatiEmendamento_CodiceEme[0]+'">'+data[i].metadata.DatiEmendamento_CodiceEme[0]+'</option>');


        	}
        	});

	</@script>
</div>
</#macro>

<#macro modal id modalTitle buttonTitle content style={"buttonType":"input"} options="" >

<div id="${id}" >
    ${content}
</div>
<#if style?? && style.buttonType?? && style.buttonType=="button">
	<button id="${id}-button" class="${style.buttonClass!""} btn btn-info" >${buttonTitle}</button>
<#else>
	<input id="${id}-button" type="button" class="submitButton round-button blue btn btn-info" value="${buttonTitle}">
</#if>
<@script>
$("#${id}").dialog({
		title: "${modalTitle}",
	    autoOpen:false,
	    height : ${style.height!"'auto'"},
	    width : ${style.width!"'auto'"},
	    modal : true,
	    position: { my: "center", at: "center top", of: document.getElementById('centeredElement') }
	    <#if options?? && options!="" >
	    ,
	    ${options}
	    </#if>

	});
	$("#${id}-button").button().click(function() {
		$('#${id}').dialog("open");
	});
</@script>
</#macro>

<#macro templateModalForm templateName el userDetails editable title="" checks="" buttonTitle="Salva" buttonType="input" >
	 <#list el.elementTemplates as elementTemplate>
	    	<#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled>
				<#assign idModal=templateName+"_"+el.getId() />
				<#assign content>
					<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
							<#assign groupActive=false />
						    <#list el.elementTemplates as elementTemplate>
						        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
						        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
						    		<#assign template=elementTemplate.metadataTemplate/>
						        	<div id="metadataTemplate-${template.name}" >
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
						                <#assign label>
						                    <@msg template.name+"."+field.name/>
						                </#assign>
						                <#if !groupActive >
						                <div class="field-component <#if fieldEditable>edit-mode<#else>view-mode</#if>" id="informations-${id}">
						                <label for="${id}">${label}<#if field.mandatory><sup style="color:red">*</sup></#if>:</label>
						                </#if>
						                <#if fieldEditable>
						                <#assign empty=[] />
						                <@stdField template field vals true  empty false />

							        <#else>
							        	<@stdField template field vals false  empty false />
							                <#--@viewFieldNoLabel template field vals false true/-->
							        </#if>
							        <#if !groupActive >
						                </div>
						            </#if>
						            </#list>
						            <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
						            <#assign buttons>
						            buttons:[{
						            text:'Save',
						            click:function(){
                                        $('select').trigger('change'); //$('.select2-offscreen').change();
						            	<#list template.fields as field>
						                    <#if field.mandatory>
						                    	<#assign label=getLabel(template.name+"."+field.name)/>
						                    	var $input=$('#${template.name}_${field.name}');
						                    	if ($input.val()==""){
						                    		bootbox.alert("Il campo ${label?html} deve essere compilato",function(){
						                    			setTimeout(function(){$input.focus();},0);
						                    		});

													return false;
						                    	}
						                    </#if>
						                </#list>
						                ${checks}
						                bootbox.alert('Salvataggio in corso <i class="icon-spinner icon-spin"></i>');
							            try{
							            	<@initDataJson el true/>
								            var myElement={};
								            myElement.id=loadedElement.id;
								            myElement.type=loadedElement.type;
								            myElement.metadata={};
								            myElement=formToElement('metadataTemplate-${template.name}',myElement,'${template.name}');

								            saveElement(myElement).done(function(data){
								            	bootbox.hideAll();
								            	if (data.result=="OK") {
								                    bootbox.alert('Salvataggio effettuato <i class="icon-ok green" ></i>');

																		//Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
											            	window.setTimeout(function(){
																	    bootbox.hideAll();
																		}, 3000);

								                    if (data.redirect){
								                        window.location.href=data.redirect;
								                    }
								                }else {
								                	bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
								                }
								            }).fail(function(){
								            	bootbox.hideAll();
								                bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');

								            });
								         }catch(err){
								         	bootbox.hideAll();
								            bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
								            console.log(err);
								         }
								         $(this).dialog("close");
						            },
						            "class" : "btn btn-xs btn-warning"
						            },
									{
										text: "Annulla",
										click: function() {
											$(this).dialog("close");
										},
										"class" : "btn btn-xs"
									}

						            ]
						            </#assign>
						            	<!--div class="clearfix"></div>
						            	 <button class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span>
																	</button-->
						            	<!--input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche"-->
						            	</form>
						            </#if>
						        </div>
						        </#if>
						    </#list>
						</#if>
				</#assign>
				<@modal idModal title title content {"buttonType":"input"} buttons />
			</#if>
	</#list>
</#macro>


<#macro createFormModal type parent=null redirect=true checks="" buttonTitle="" title="" >
<#assign idModal="modal-create-"+type.id />

<#if buttonTitle=="">
	<#assign buttonTitle2>
		<i class="icon-plus bigger-160"  ></i> <b><@msg "type.create."+type.typeId/></b>
	</#assign>
<#else>
	<#assign buttonTitle2>
		<i class="icon-plus bigger-160"  ></i> <b>${buttonTitle}</b>
	</#assign>
</#if>
<#if title?? || title=="">

	<#assign title2><@msg "type.create."+type.typeId/></#assign>
	<#else>
	<#assign title2=title />
</#if>
<#assign title2=title2?trim />

	 <#assign buttons>
        buttons:[{
        text:'Salva',
        click:function(){
	     	var $form=$('#create-document-form-${type.id}');
			$('#${idModal}').dialog('close');
			        <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
				    <#list type.associatedTemplates as assocTemplate>
					<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
					<#if assocTemplate.enabled && templatePolicy.canCreate>
						<#assign template=assocTemplate.metadataTemplate/>
						<#if template.fields??>
			                            <#list template.fields as field>
			                                    <#if field.mandatory>
			                                    	<#assign label=getLabel(template.name+"."+field.name)/>

			                                    	if ($form.find('[name=${template.name}_${field.name}]').val()==""){
			                                    		bootbox.alert("Il campo ${label?html} deve essere compilato",function(){
			                                    			$('#${idModal}').dialog('open');
															setTimeout(function(){$form.find('[name=${template.name}_${field.name}]').focus();},0);
			                                    		});

														return false;
			                                    	}
			                                    </#if>
			                            </#list>
			                         </#if>

				        </#if>
				    </#list>
				</#if>
				<#if type.hasFileAttached>
			        if ($form.find('[name=file]').val()==""){
			        	bootbox.alert("Bisogna allegare un file",function(){
			        		setTimeout(function(){$('#file').focus();},0);
			        	});

						return false;
			        }
			        <#if !type.noFileinfo>
			        if ($form.find('[name=version]').val()==""){
			        	bootbox.alert("Il campo versione deve essere compilato",function(){
			        		$('#version').focus();
			        	});

						return false;
			        }
			        if ($form.find('[name=data]').val()==""){
			        	bootbox.alert("Il campo data deve essere compilato",function(){
			        		$('#data').focus();
			        	});

						return false;
			        }
			        </#if>
		        </#if>
			${checks}
            bootbox.alert('Salvataggio in corso <i class="icon-spinner icon-spin"></i>');
            <@dummyDataJson type />
            dummy.parent=${parent.id};
            var myElement={};
            myElement.parent=dummy.parent;
            myElement.type=dummy.type;
            myElement.metadata={};
            myElement=formToElement('create-document-form-${type.id}',myElement);
            saveElement(myElement).done(function(data){
            	bootbox.hideAll();
            	if (data.result=="OK") {
                    bootbox.alert('Salvataggio effettuato <i class="icon-ok green" ></i>');
                    <#if redirect>
					if (data.redirect){
                        window.location.href=data.redirect;
                    }
					<#else>
					if (data.redirect){
                        window.location.reload(true);
                    }
					</#if>

                }else {
                	bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
                }
            }).fail(function(){
            	bootbox.hideAll();
                bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');

            });


    },
        "class" : "btn btn-xs btn-warning"
        },
		{
			text: "Annulla",
			click: function() {
				$(this).dialog("close");
			},
			"class" : "btn btn-xs"
		}

        ]
	</#assign>
	<#assign modalForm>
	<form id="create-document-form-${type.id}" name="create-document-form-${type.id}" method="POST" action="${baseUrl}/app/rest/documents/save/${model['docDefinition'].id}" enctype="multipart/form-data" onsubmit="return false;" >

	        <#if parent??>
	        <@hidden "parentId" "parentId" parent.id />
	        </#if>

	        <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
		    <#list type.associatedTemplates as assocTemplate>
			<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
			<#if assocTemplate.enabled && templatePolicy.canCreate>
				<#assign template=assocTemplate.metadataTemplate/>
				<#if template.fields??>
	                            <#list template.fields as field>
	                                    <@mdfield template field/>
	                            </#list>
	                         </#if>

		        </#if>
		    </#list>
		</#if>

	        <#if type.hasFileAttached>
	        <#if !type.noFileinfo>
	        <div class="field-component" id="file_version">
	            <label for="version">Versione<sup style="color:red">*</sup>:</label>
	            <input type="text" name="version" id="version"/>
	        </div>
	        <div class="field-component" id="file_data">
	            <label for="data">Data<sup style="color:red">*</sup>:</label><input type="text" name="data" class="datePicker" id="data"/>
	            <@script>
	            	$('#data').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
	            </@script>
	        </div>
	        <div class="field-component" id="file_autore">
	            <label for="autore">Autore:</label><input type="text" name="autore" id="autore"/><br/>
	        </div>
	        <div class="field-component" id="file_node">
	            <label for="note">Note:</label><textarea name="note" id="note"></textarea><br/>
	        </div>
	        </#if>
	        <div class="field-component">
	        <#assign label>
	        <@msg model['docDefinition'].typeId+".fileLabel" /> <sup style='color:red'>*</sup>
	        </#assign>
	        <@fileChooser "file" "file" label />
	        </div>
	        </#if>
	        <div class="clearfix"></div>
	        <!--button class="btn btn-warning submitButton" id="document-form-submit" name="document-form-submit"><i class="icon-save bigger-160"></i><b>Salva</b></span>
			</button-->



	</form>
</#assign>
<@modal idModal title2 buttonTitle2 modalForm {"buttonType":"button"} buttons />
</#macro>

<#macro braccioSelect id="" name="" label="" values={} value="" editable=true>
<#assign selectedCode=""/>
<#assign selectedDecode=""/>
<#if value!="" >
<#assign value=value?split("###")[0] />
</#if>
<@script>



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
                $('#${id}').val('-9999###' + $('#${id}-altro').val());
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






</@script>

<select id="${id}-select" name="${name}-select">
    <option></option>
    <#assign keys = values?keys>
    <#list keys as key>
        <option value="${key?html}"
                <#if key=value>selected<#elseif (value?? && key?starts_with("-9999###") && value?starts_with("-9999###")) >selected<#assign toSet=key /></#if>>${values[key]}</option>
    </#list>
    <#if toSet??>
    <@script>
    	$('#${id}-select').select2("val","${toSet}");
    </@script>
    </#if>
</select>
<input type="hidden" id="${id}" name="${name}"/>
<input type="text" id="${id}-altro" name="${name}-altro" style="display:none"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
</#macro>

<#function limit stringValue limit>
	<#assign miniString=(stringValue!"")>
	<#if (miniString?length &lt; limit)>
		<#assign result=miniString />
	<#else>
		<#assign cut=limit-3 />
		<#assign result=miniString?substring(0,cut) />
		<#assign result=result+"..." />
	</#if>
	<#return result>
</#function>

<#macro tableTemplateForm templateName el userDetails editable classes="" >
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
<#assign thead="<div class=\"table-responsive\"><table class=\"table table-striped table-bordered table-hover\" ><thead><tr>" />
<#assign tbody="<tbody><tr>" />
	<#assign groupActive=false />
    <#list el.elementTemplates as elementTemplate>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    		<#assign template=elementTemplate.metadataTemplate/>
        	 <#assign thead>
        	<div id="metadataTemplate-${template.name}" class="${classes}">
        	<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
        	<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
        	</#if>
        	${thead}
        	</#assign>
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
               <#assign thead>
                ${thead}
                <th><label for="${id}">${label}<#if field.mandatory><sup style="color:red">*</sup></#if>:</label></th>
                </#assign>
                </#if>
                <#if fieldEditable>
                <#assign empty=[] />
                <#assign tbody>
                ${tbody}
                <td>
                <@stdField template field vals true  empty false />
                </td>
                </#assign>
	        <#else>
	        	<#assign tbody>
                ${tbody}
                <td>
	        	<@stdField template field vals false  empty false />
	        	</td>
	        	</#assign>
	                <#--@viewFieldNoLabel template field vals false true/-->
	        </#if>

            </#list>
            <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
            <@script>
            $("[name=salvaForm-${template.name}]").on('click',function(){
            	var $form=$($(this).data('rel'));
                $('select').trigger('change'); //$('.select2-offscreen').change();
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
                bootbox.alert('Salvataggio in corso <i class="icon-spinner icon-spin"></i>');
	            try{
		            var myElement={};
		            myElement.id=loadedElement.id;
		            myElement.type=loadedElement.type;
		            myElement.metadata={};
		            myElement=formToElement($form,myElement,'${template.name}');
		            saveElement(myElement).done(function(data){
		            	bootbox.hideAll();
		            	if (data.result=="OK") {
		                    bootbox.alert('Salvataggio effettuato <i class="icon-ok green" ></i>');

												//Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
					            	window.setTimeout(function(){
											    bootbox.hideAll();
												}, 3000);

		                    if (data.redirect){
		                        window.location.href=data.redirect;
		                    }
		                }else {
		                	bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
		                }
		            }).fail(function(){
		            	bootbox.hideAll();
		                bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');

		            });
		         }catch(err){
		         	bootbox.hideAll();
		            bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
		            console.log(err);
		         }
            });
            </@script>
            	<div class="clearfix"></div>
            	 <button class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b><@msg "actions.save"/></b></span>
											</button>
            	<!--input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche"-->
            	</form>
            </#if>

        </#if>
    </#list>
    <#assign thead=thead+"</tr></thead>" />
    <#assign tbody=tbody+"</tr></tbody></table></form></div></div>" />
    ${thead}
    ${tbody}
</#if>
</#macro>


<#macro TemplateFormTable templateName el userDetails editable titleTable="" classes="" >
<#assign toClose=false />
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>

	<#assign groupActive=false />
    <#list el.elementTemplates as elementTemplate>
        <#if elementTemplate.metadataTemplate.name==templateName && elementTemplate.enabled>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        	<#if templatePolicy.canView>

    		<#assign template=elementTemplate.metadataTemplate/>
    			<#assign toClose=true />
        	<div id="metadataTemplate-${template.name}" class="${classes}">
        	<#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate)>
        	<form name="${template.name}" style="display:" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;">
        	</#if>
        	<table class="table table-bordered" id="checklist">
							<thead>
								<tr><th colspan="2">${titleTable}</th></tr>
							</thead>
        	<#list template.fields as field>
                <@SingleFieldTd template.name field.name el userDetails editable />
            </#list>
        </table>

      </#if>

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
                loadingScreen("Waiting <i class="icon-spinner icon-spin"></i>", "loading");

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
            	 <button id="salvaForm-${template.name}" class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span>
											</button>
            	<!--input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche"-->
            	</form>
            </#if>
</#if>
<#if toClose >
</div>
</#if>
</#macro>

<#macro GetProcess id el userDetails>
<div id="task-Actions-${childId}"></div>
<@script>
var taskId=${id};
loadTasksById(taskId);
</@script>
</#macro>






<#macro SingleFieldNoLabelNoDiv templateName fieldName el userDetails>
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#list el.elementTemplates as elementTemplate>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
        <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
        <#assign template=elementTemplate.metadataTemplate/>
           <#list template.fields as field>
            <#if field.name=fieldName>
        <#assign vals=[]/>
        <#list el.data as data>

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
          <@viewFieldNoLabel template field vals false true/>
        </#if>
            </#list>
         </#if>
    </#list>
</#if>
</#macro>





<#macro defaultSidebar>


<#if model['getCreatableRootElementTypes']??>
  <#--#list model['getCreatableRootElementTypes'] as docType>
    <@addmenuitem>
      {
        "class":"",
        "link":"#",
        "level_1":true,
        "title":"${docType.typeId}",
        "icon":{"icon":"","title":"${docType.typeId}"},
        "submenu":[
          {
            "class":"",
            "link":"${baseUrl}/app/documents/new/${docType.typeId}",
            "level_2":true,
            "title":"Aggiungi",
            "icon":{"icon":"icon-plus","title":"Create new ${docType.typeId}"}
          },
          {
            "class":"",
            "link":"${baseUrl}/app/documents/${docType.typeId}",
            "level_2":true,
            "title":"Lista",
            "icon":{"icon":"icon-list","title":"List ${docType.typeId}"}
          }
          ]
      }
      </@addmenuitem>

  </#list-->

  <#--> //el.id</#-->


</#if>
</#macro>


<#function max x y>
    <#if (x<y)><#return y>
    <#else><#return x>
    </#if>
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
    <#--assign url="${baseUrl}/app/documents"/-->
    <#assign url=""/>
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



<#macro createFormModal type parent=null redirect=true checks="" buttonTitle="" title="" >
<#assign idModal="modal-create-"+type.id />

<#if buttonTitle=="">
	<#assign buttonTitle2>
		<i class="icon-plus bigger-160"  ></i> <b><@msg "type.create."+type.typeId/></b>
	</#assign>
<#else>
	<#assign buttonTitle2>
		<i class="icon-plus bigger-160"  ></i> <b>${buttonTitle}</b>
	</#assign>
</#if>
<#if title?? || title=="">

	<#assign title2><@msg "type.create."+type.typeId/></#assign>
	<#else>
	<#assign title2=title />
</#if>
<#assign title2=title2?trim />

	 <#assign buttons>
        buttons:[{
        text:'Save',
        click:function(){
            $('select').trigger('change'); //$('.select2-offscreen').change();
	     	var $form=$('#create-document-form-${type.id}');
			$('#${idModal}').dialog('close');
			        <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
				    <#list type.associatedTemplates as assocTemplate>
					<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
					<#if assocTemplate.enabled && templatePolicy.canCreate>
						<#assign template=assocTemplate.metadataTemplate/>
						<#if template.fields??>
			                            <#list template.fields as field>
			                                    <#if field.mandatory>
			                                    	<#assign label=getLabel(template.name+"."+field.name)/>

			                                    	if ($form.find('[name=${template.name}_${field.name}]').val()==""){
			                                    		bootbox.alert("Il campo ${label?html} deve essere compilato",function(){
			                                    			$('#${idModal}').dialog('open');
															setTimeout(function(){$form.find('[name=${template.name}_${field.name}]').focus();},0);
			                                    		});

														return false;
			                                    	}
			                                    </#if>
			                            </#list>
			                         </#if>

				        </#if>
				    </#list>
				</#if>
				<#if type.hasFileAttached>
			        if ($form.find('[name=file]').val()==""){
			        	bootbox.alert("Bisogna allegare un file",function(){
			        		setTimeout(function(){$('#file').focus();},0);
			        	});

						return false;
			        }
			        <#if !type.noFileinfo>
			        if ($form.find('[name=version]').val()==""){
			        	bootbox.alert("Il campo versione deve essere compilato",function(){
			        		$('#version').focus();
			        	});

						return false;
			        }
			        if ($form.find('[name=data]').val()==""){
			        	bootbox.alert("Il campo data deve essere compilato",function(){
			        		$('#data').focus();
			        	});

						return false;
			        }
			        </#if>
		        </#if>
			${checks}
            bootbox.alert('Waiting <i class="icon-spinner icon-spin"></i>');
            <@dummyDataJson type />
            dummy.parent=${parent.id};
            var myElement={};
            myElement.parent=dummy.parent;
            myElement.type=dummy.type;
            myElement.metadata={};
            myElement=formToElement('create-document-form-${type.id}',myElement);
            saveElement(myElement).done(function(data){
            	bootbox.hideAll();
            	if (data.result=="OK") {
                    bootbox.alert('Salvataggio effettuato <i class="icon-ok green" ></i>');
                    <#if redirect>
					if (data.redirect){
                        window.location.href=data.redirect;
                    }
					<#else>
					if (data.redirect){
                        window.location.reload(true);
                    }
					</#if>

                }else {
                	bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');
                }
            }).fail(function(){
            	bootbox.hideAll();
                bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');

            });


    },
        "class" : "btn btn-xs btn-warning"
        },
		{
			text: "Annulla",
			click: function() {
				$(this).dialog("close");
			},
			"class" : "btn btn-xs"
		}

        ]
	</#assign>
	<#assign modalForm>
	<form id="create-document-form-${type.id}" name="create-document-form-${type.id}" method="POST" action="${baseUrl}/app/rest/documents/save/${model['docDefinition'].id}" enctype="multipart/form-data" onsubmit="return false;" >

	        <#if parent??>
	        <@hidden "parentId" "parentId" parent.id />
	        </#if>

	        <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
		    <#list type.associatedTemplates as assocTemplate>
			<#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
			<#if assocTemplate.enabled && templatePolicy.canCreate>
				<#assign template=assocTemplate.metadataTemplate/>
				<#if template.fields??>
	                            <#list template.fields as field>
	                                    <@mdfield template field/>
	                            </#list>
	                         </#if>

		        </#if>
		    </#list>
		</#if>

	        <#if type.hasFileAttached>
	        <#if !type.noFileinfo>
	        <div class="field-component" id="file_version">
	            <label for="version">Versione<sup style="color:red">*</sup>:</label>
	            <input type="text" name="version" id="version"/>
	        </div>
	        <div class="field-component" id="file_data">
	            <label for="data">Data<sup style="color:red">*</sup>:</label><input type="text" name="data" class="datePicker" id="data"/>
	            <@script>
	            	$('#data').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
	            </@script>
	        </div>
	        <div class="field-component" id="file_autore">
	            <label for="autore">Autore:</label><input type="text" name="autore" id="autore"/><br/>
	        </div>
	        <div class="field-component" id="file_node">
	            <label for="note">Note:</label><textarea name="note" id="note"></textarea><br/>
	        </div>
	        </#if>
	        <div class="field-component">
	        <#assign label>
            <@msg model['docDefinition'].typeId+".fileLabel" /> <sup style='color:red'>*</sup>
            </#assign>
            <@fileChooser "file" "file" label />
	        </div>
	        </#if>
	        <div class="clearfix"></div>
	        <!--button class="btn btn-warning submitButton" id="document-form-submit" name="document-form-submit"><i class="icon-save bigger-160"></i><b>Salva</b></span>
			</button-->
	</form>
</#assign>
<@modal idModal title2 buttonTitle2 modalForm {"buttonType":"button"} buttons />
</#macro>


<#macro controlledFormField template templatePolicy field element="" editable=true withLabel=true showAudit=true>
    <#assign fieldEditable=editable>
    <#assign vals=[]/>
    <#assign audit=[]/>
    <#if element != "">
        <#list element.data as data>
            <#assign fieldEditable=(editable && templatePolicy.canUpdate)/>
            <#if data.template.id=template.id && data.field.id=field.id >
                <#assign vals=data.getVals()/>
            </#if>
        </#list>
        <#if showAudit>
            <#list element.auditData as auditData>
                <#if auditData.field.id==field.id>
                    <#assign audit=audit+[auditData]/>
                </#if>
            </#list>
        </#if>
    </#if>
    <div data-field-id="${template.name}_${field.name}" data-field-type="${field.type}" class="" id="informations-${template.name}_${field.name}">
        <label class="col-sm-3 control-label no-padding-right" for="${template.name}_${field.name}"><@msg template.name+"."+field.name/></label>
        <#assign empty=[] />
        <@stdField template field vals fieldEditable audit false/>
    </div>
</#macro>

<#macro controlledFormTemplate template templatePolicy element="" fieldEditable=true withLabel=true showAudit=true>
    <#list template.fields as field>
        <div class="row">
            <@controlledFormField template templatePolicy field element editable withLabel showAudit/>
        </div>
    </#list>
</#macro>

<#macro allInControlledForm elType userDetails baseUrl element="" parentId="" templateOrders=[] tabbed=true>
    <#assign postUrl="">
    <#if element != "">
        <#assign postUrl="${baseUrl}/app/rest/documents/checkAndUpdate/${element.id}">
    <#else>
        <#assign postUrl="${baseUrl}/app/rest/documents/checkAndSave/${elType.typeId}">
    </#if>
    <form class="form-horizontal" id="document-form" method="POST" action="${postUrl}" enctype="multipart/form-data" onsubmit="return false;" >
        <#if parentId != "">
            <@hidden "parentId" "parentId" parentId/>
        </#if>
        <#assign availableTemplates=[]>
        <#if element != "">
            <#if el.elementTemplates?? && el.elementTemplates?size gt 0>
                <#list element.elementTemplates as elementTemplate>
                    <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, element)/>
                    <#if elementTemplate.enabled && templatePolicy.canView>
                        <#assign availableTemplates=availableTemplates+[elementTemplate.metadataTemplate]>
                    </#if>
                </#list>
            </#if>
        <#else>
            <#if elType.associatedTemplates?? && elType.associatedTemplates?size gt 0>
                <#list elType.associatedTemplates as assocTemplate>
                    <#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, elType)/>
                    <#if assocTemplate.enabled && templatePolicy.canCreate>
                        <#assign availableTemplates=availableTemplates+[assocTemplate.metadataTemplate]>
                    </#if>
                </#list>
            </#if>
        </#if>
        <#if availableTemplates?size gt 1>
        <div class="widget-box">
            <div class="widget-header widget-header-small">
                <#if tabbed>
                    <div class="widget-toolbar no-border">
                        <ul id="myTab" class="nav nav-tabs">
                            <#if templateOrders?size gt 0>
                                <#list templateOrders as templateName>
                                    <#list availableTemplates as template>
                                        <#if template.name == templateName>
                                            <li>
                                                <a style="font-size: 14px; font-weight: bold;" href="#${template.name}_template_tab" data-toggle="tab"><@msg "template."+template.name/></a>
                                            </li>
                                        </#if>
                                    </#list>
                                </#list>
                            <#else>
                                <#list availableTemplates as template>
                                    <li>
                                        <a style="font-size: 14px; font-weight: bold;" href="#${template.name}_template_tab" data-toggle="tab"><@msg "template."+template.name/></a>
                                    </li>
                                </#list>
                            </#if>
                        </ul>
                    </div>
                <#else>
                    <h2><#if element == ""><@msg "type.create."+elType.typeId/><#else><@msg "type."+elType.typeId/></#if></h2>
                </#if>
            </div>
        <#else>
        <div class="widget-box">
            <div class="widget-header widget-header-small">
                <h4><#if element == ""><@msg "type.create."+elType.typeId/><#else><@msg "type."+elType.typeId/></#if></h4>
            </div>
        </#if>
        <div class="widget-body">
        <div class="widget-main padding-6">
            <#if availableTemplates?size gt 1>
                <#if templateOrders?size gt 0 && tabbed>
                <div class="tab-content">
                </#if>
                <#list templateOrders as templateName>
                    <#list availableTemplates as template>
                        <#if template.name == templateName>
                            <#assign templatePolicy="">
                            <#if element != "">
                                <#list el.elementTemplates as elementTemplate>
                                    <#if elementTemplate.metadataTemplate.name==templateName>
                                        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, element)/>
                                    </#if>
                                </#list>
                            <#else>
                                <#list elType.associatedTemplates as assocTemplate>
                                    <#if assocTemplate.metadataTemplate.name==templateName>
                                        <#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, elType)/>
                                    </#if>
                                </#list>
                            </#if>
                            <#if templateOrders?size gt 0 && tabbed>
                            <div id="${template.name}_template_tab" class="tab-pane">
                            </#if>
                            <@controlledFormTemplate template templatePolicy element/>
                            <#if templateOrders?size gt 0 && tabbed>
                            </div>
                            </#if>
                        </#if>
                    </#list>
                </#list>
            <#else>
                <#list availableTemplates as template>
                    <#assign templatePolicy="">
                    <#if element != "">
                        <#list el.elementTemplates as elementTemplate>
                            <#if elementTemplate.metadataTemplate.name==template.name>
                                <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, element)/>
                            </#if>
                        </#list>
                    <#else>
                        <#list elType.associatedTemplates as assocTemplate>
                            <#if assocTemplate.metadataTemplate.name==template.name>
                                <#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, elType)/>
                            </#if>
                        </#list>
                    </#if>
                    <#if availableTemplates?size gt 0 && tabbed>
                    <div id="${template.name}_template_tab" class="tab-pane">
                    </#if>
                    <@controlledFormTemplate template templatePolicy element/>
                    <#if availableTemplates?size gt 0 && tabbed>
                    </div>
                    </#if>
                </#list>
            </#if>
        </div>
            <#if templateOrders?size gt 0 && tabbed>
            </div>
            </#if>
            <div class="widget-toolbox button-footer-area padding-8 clearfix"></div>
        </div>
    </div>
    </form>
    <#assign formName="detail">
    <#if element=="">
        <#assign formName="create">
    </#if>
    <@script>
        <#include "pages/documents/helpers/xcdm-control.js.ftl"/>
        loadMessages('${baseUrl}');
        loadControls('${baseUrl}','${type.typeId}', 'document-form', "${formName}");
    </@script>
</#macro>