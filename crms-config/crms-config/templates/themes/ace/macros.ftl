<#macro reportBuilder reportRootEl>
        <#assign reportList=[]/>
        <#if reportRootEl.childs??>
            <#list reportRootEl.getChildren() as area>
                <#if area.childs??>
                    <#assign tmpReports=[]/>
                    <#list area.childs as report>
                        <#if !report.deleted && report.getUserPolicy(userDetails).canBrowse>
                            <#assign tmpReports=tmpReports+[{"id": report.id, "title": report.titleString, "position": report.position?c, "positionSort": report.position?number}]/>
                        </#if>
                    </#list>
                    <#if tmpReports?size gt 0>
                        <#assign reportList=reportList+[{"id": area.id, "title": area.titleString, "children": tmpReports,  "positionSort": area.position?number}]/>
                    </#if>
                </#if>
            </#list>
        </#if>
        <#assign reportList=reportList?sort_by("positionSort") >
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
                    <#list area.children?sort_by("positionSort") as report>
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

            url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
            $.getJSON( url, function( data ) {

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


<#function getFieldMulti templateName fieldName element>
    <#assign ret=[]/>
    <#if element.getfieldData(templateName, fieldName)?? && element.getfieldData(templateName, fieldName)?size gt 0 && element.getfieldData(templateName, fieldName)[0]??>
        <#assign ret=element.getfieldData(templateName, fieldName)/>
    </#if>
    <#return ret/>
</#function>

<#function getCodeMulti templateName fieldName element>
    <#assign ret=[]/>
    <#assign values=getFieldMulti(templateName fieldName element) />
    <#if values??>
        <#list values as v>
            <#assign tmpval = v?string?split('###')[0] />
            <#assign ret=ret+[tmpval] />
        </#list>
    </#if>
    <#return ret/>
</#function>

<#function getDecodeMulti templateName fieldName element>
    <#assign ret=[]/>
    <#assign values=getFieldMulti(templateName fieldName element)/>
    <#list values as v>
        <#assign tmpval = v?string?split('###')[1] />
        <#assign ret=ret+[tmpval] />
        <#--assign ret=ret+[v?string?split('###')[1]] /-->
    </#list>
    <#return ret/>
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
                    <#--case "RADIO">
                        <#if mddata[0]?? && mddata[0]!="">
                        ${mddata[0]?split("###")[1]}
                        <#else>&nbsp;
                        </#if>
                        <#break-->
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
    <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>
     <#if fieldDef.macroView??>
        <#assign x=fieldDef.macroView/>
        <@.vars[x] id id template fieldDef  mddata editable audit/>
     <#else>
        <@showData template fieldDef  mddata editable audit />
     </#if>

</#macro>

<#macro viewField template fieldDef  mddata=[] editable=false audit=[]>
     <#assign id=template.name+"_"+fieldDef.name/>
     <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>

     <div class="form-group field-component view-mode" id="${template.name}-${id}">
     <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
     <div class="col-sm-9" id="${id}">
     <@viewFieldNoLabel template fieldDef  mddata editable audit/>
     </div>
     </div>

</#macro>

<#macro mdFieldDetail template fieldDef  mddata=[] editable=false audit=[] showLabel=true elId="" useDataName=false >
    <#if editable>
        <@stdField template fieldDef mddata editable audit showLabel true elId useDataName/>
    <#else>
        <@viewField template fieldDef  mddata editable audit />
    </#if>
    <#return />
    <#--mdfield template="" fieldDef=""  mddata=[] divContainer=true noLabel=false-->
    <#assign id=template.name+"_"+fieldDef.name/>
    <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>

    <#assign addClass=""/>
    <#if editable>
        <#assign addClass="view-editable-field"/>
    </#if>
    <div class="form-group" id="${template.name}-${id}">
    <#if showLabel>
        <#assign label=messages[template.name+"."+fieldDef.name]!template.name+"."+fieldDef.name/>
        <label for="${id}">

        <#if template.auditable && audit??>
            <@auditLink template.name fieldDef.name elementId/>
            <!--<a hidefocus="hidefocus" href="#${template.name}_${fieldDef.name}_audit" class="btn-link" role="button" data-toggle="modal" title="Mostra audit trail" id="${template.name}_${fieldDef.name}_audit_btn" >
            <i class="icon-time"></i></a>-->

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
                    <#--case "RADIO">
                        <#if mddata[0]?? && mddata[0]!="">

                        ${mddata[0]?split("###")[1]}
                        <#else>&nbsp;
                        </#if>
                        <#break-->
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

<#macro auditLink templateName="" fieldName="" elementId="" cssAdded="">
    <#if elementId?? && elementId?has_content>
        <a hidefocus="hidefocus" class="btn-link" role="button" title="Mostra audit trail"
        <#if cssAdded!="">style="${cssAdded}"</#if>
            href="#"
            data-audit-id="${templateName}_${fieldName}_${elementId}"
            data-el-id="${elementId}" data-template-name="${templateName}" data-field-name="${fieldName}">

                <i class="icon-time"></i> </a>
            <@script>
            $('a[data-audit-id="${templateName}_${fieldName}_${elementId}"]').unbind('click');
            $('a[data-audit-id="${templateName}_${fieldName}_${elementId}"]').click(function(){
                showAuditData(${elementId}, '${templateName}', '${fieldName}');
            });
            </@script>
        </#if>
</#macro>

<#macro stdField template="" fieldDef=""  mddata=[] editable=true audit=[]  withLabel=true fastUpdate=false elId="" useDataName=false >
    <#assign noLabel=!withLabel />
    <#assign id=fieldDef.name/>
    <#assign label=fieldDef.name/>
    <#assign elId=elId?string!"" />
    <!-- ELID: ${elId?string}-->
    <#if elId?string=="">
        <#if model['element']?? >
            <#assign elId=model['element'].id?string />
        </#if>
    </#if>

    <#if template!="">
        <#assign id=template.name+"_"+fieldDef.name/>
        <#assign label=template.name+"."+fieldDef.name/>
        <#assign label="${messages[label]!label}" />
        <#assign labelJS="${messages[label]!label}" />
        <#if fieldDef.mandatory><#assign label="${label}<sup style=\"color:red\">*</sup>"/></#if>
        <#if template.auditable && audit??>
            <#assign label>
                <@auditLink template.name fieldDef.name elementId/> ${label}
                <!--<a hidefocus="hidefocus" href="#${template.name}_${fieldDef.name}_audit" class="btn-link" role="button" data-toggle="modal" title="Mostra audit trail" id="${template.name}_${fieldDef.name}_audit_btn" >
                <i class="icon-time"></i> </a> ${label}-->
            </#assign>
        </#if>
    </#if>
    <#if !withLabel && template.auditable && audit??>
        <@auditLink template.name fieldDef.name elementId "float:left;padding-right:5px;"/>
        <!--<div class="audit-icon-div">
            <a hidefocus="hidefocus" href="#${template.name}_${fieldDef.name}_audit" class="btn-link" role="button" data-toggle="modal" title="Mostra audit trail" id="${template.name}_${fieldDef.name}_audit_btn"
            style="float:left;padding-right:5px;">
            <i class="icon-time"></i></a>
        </div>-->
    </#if>
    <#assign addClass=""/>
    <#if editable>
        <#assign addClass=" field-editable"/>
        <#else>
        <#assign addClass=" field-view"/>
    </#if>
    <#if fastUpdate>
        <#assign addClass="col-sm-12 field-inline-edit"/>
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
                <#assign updateId=elId?string />
                <#if !noLabel >
                <label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
                </#if>
                <div class="col-sm-9">
                    <#if useDataName >
                    <a class="field-component ${addClass} inline-field field-inline-anchor" href="#" data-name="${id}" id="${id}-${updateId}" data-type="text" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                    <#else>
                    <a class="field-component ${addClass} inline-field field-inline-anchor" href="#" id="${id}" data-type="text" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                </#if>
                </div>
                <@script>
                    $(document).ready(function(){
                        <#if useDataName >
                            $("[id='${id}-${updateId}']").editable({
                        <#else>
                            $("[id='${id}']").editable({
                        </#if>
                        emptytext :"Valore mancante",
                        success: function(response, newValue) {
                                    if (jQuery.isFunction(window.fastUpdatePageCallback)){
                                        fastUpdatePageCallback(response, newValue, '${id}', ${updateId});
                                    }
                                }
                        });
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
                <#assign updateId=elId?string />
                <#--if !elId??> <#assign elId=model['element'].id?string /></#if-->
                <#if !noLabel >
                <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
                </#if>
                <div class="col-sm-9">
                <#if useDataName >
                    <a class="inline-field field-inline-anchor" href="#" data-name="${id}" id="${id}-${updateId}" class="field-component ${addClass}" data-type="textarea" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                <#else>
                    <a class="inline-field field-inline-anchor" href="#" id="${id}" class="field-component ${addClass}" data-type="textarea" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                </#if>
                </div>
                <@script>
                    $(document).ready(function(){
                        <#if useDataName >
                            $("[id='${id}-${updateId}']").editable({
                        <#else>
                            $("[id='${id}']").editable({
                        </#if>
                            emptytext :"Valore mancante",
                            success: function(response, newValue) {
                                if (jQuery.isFunction(window.fastUpdatePageCallback)){
                                    fastUpdatePageCallback(response, newValue, '${id}', ${updateId});
                                }
                            }
                        });
                    });
                </@script>
                <#elseif noLabel>
                    <@textareaNoLabel id id label 40 1 mddata?first!"" editable/>
                <#else>

                    <@textarea id id label 40 1 mddata?first!"" editable/>
                </#if>
            <#break>
        <#case "DATE">
            <#if fastUpdate>
                <#assign updateId=elId?string />
                <#if !noLabel >
                <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
                </#if>
                <div class="col-sm-9">
                    <#if useDataName >
                    <a class="inline-field field-inline-anchor field-component ${addClass}" href="#" data-name="${id}" id="${id}-${updateId}" data-format="dd/mm/yyyy" data-type="date" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}"><#if mddata?size gt 0>${mddata?first.time?string("dd/MM/yyyy")!""}</#if></a>
                    <#else>
                    <a class="inline-field field-inline-anchor field-component ${addClass}" href="#" id="${id}" data-format="dd/mm/yyyy" data-type="date" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}"><#if mddata?size gt 0>${mddata?first.time?string("dd/MM/yyyy")!""}</#if></a>
                </#if>
                    <@script>
                    $(document).ready(function(){
                        <#if useDataName >
                            $("[id='${id}-${updateId}']").editable({
                        <#else>
                            $("[id='${id}']").editable({
                        </#if>
                            format: 'dd/mm/yyyy',
                            viewformat: 'dd/mm/yyyy',
                            emptytext :"Valore mancante",
                            success: function(response, newValue) {
                                if (jQuery.isFunction(window.fastUpdatePageCallback)){
                                    fastUpdatePageCallback(response, newValue, '${id}', ${updateId});
                                }
                            },
                            datepicker: {
                                weekStart: 1
                            }
                        });
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
				<#assign updateId=elId?string />
                <#assign x=fieldDef.macro/>
				<#if fieldDef.macro?contains("Multiple") >
                    <#if fastUpdate>
                        <#attempt>
                            <@.vars[x] id id messages[label]!label mddata size noLabel fieldDef editable true updateId/>
                        <#recover>
                        <#attempt>
                            <@.vars[x] id id messages[label]!label mddata size noLabel fieldDef editable/>
                        <#recover>
                            <@.vars[x] id id messages[label]!label fieldDef.availableValuesMap mddata editable/>
                        </#attempt>
                    </#attempt>
                   <#else>
				        <#attempt>
					         <@.vars[x] id id messages[label]!label mddata size noLabel fieldDef editable/>
                        <#recover>
                            <@.vars[x] id id messages[label]!label fieldDef.availableValuesMap mddata editable/>
                        </#attempt>
                   </#if>
				<#else>
                    <#if fastUpdate>
                        <#attempt>
                            <@.vars[x] id id messages[label]!label mddata?first!"" size noLabel fieldDef editable true updateId/>
                        <#recover>
                        <#attempt>
                            <@.vars[x] id id messages[label]!label mddata?first!"" size noLabel fieldDef editable/>
                        <#recover>
                            <@.vars[x] id id messages[label]!label fieldDef.availableValuesMap mddata?first!"" editable/>
                        </#attempt>
                    </#attempt>
                   <#else>
				        <#attempt>
					         <@.vars[x] id id messages[label]!label mddata?first!"" size noLabel fieldDef editable/>
                        <#recover>
                            <@.vars[x] id id messages[label]!label fieldDef.availableValuesMap mddata?first!"" editable/>
                        </#attempt>
                   </#if>
				</#if>
            <#elseif fastUpdate>
                <#assign updateId=elId?string />
                <#if !noLabel >
                <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
                </#if>
                <#assign value=mddata?first!""/>
                <#assign valueText=""/>
                <#if value?? && value!="">
                    <#assign valueText=value?split("###")[1]/>
                </#if>
                <div class="col-sm-9">
                    <#if useDataName >
                    <a href="#" class="inline-field" data-name="${id}" id="${id}-${updateId}" data-type="select2" data-value="${value}" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${valueText}</a>
                    <#else>
                    <a href="#" class="inline-field" id="${id}" data-type="select2" data-value="${value}" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/updateField/${updateId}" data-title="${labelJS}">${valueText}</a>
                </#if>
                </div>
                <@script>
                <#assign keys = fieldDef.availableValuesMap?keys>

                $(document).ready(function(){
                    <#if useDataName >
                        $("[id='${id}-${updateId}']").editable({
                    <#else>
                        $("[id='${id}']").editable({
                    </#if>
                        source: [
                            <#list keys as key>
                                {id: "${key?html}###${fieldDef.availableValuesMap[key]?html}", text: "${fieldDef.availableValuesMap[key]?html}"}<#if key_has_next>,</#if>
                            </#list>
                        ],
                        select2: {
                            multiple: false,
                            emptytext :"Valore mancante"
                        },
                        success: function(response, newValue) {
                            if (jQuery.isFunction(window.fastUpdatePageCallback)){
                                fastUpdatePageCallback(response, newValue, '${id}', ${updateId});
                            }
                        }
                    });
                });
            </@script>
            <#elseif noLabel>
                <@selectHashNoLabelPlus id id label fieldDef.availableValuesMap mddata?first!"" editable/>
            <#else>
                <@selectHashPlus id id label fieldDef.availableValuesMap mddata?first!"" editable/>
            </#if>

            <#break>
        <#case "RADIO">
             <#if fieldDef.macro??>
                <#assign x=fieldDef.macro/>
                <@.vars[x] id id label fieldDef.availableValuesMap mddata?first!""/>
             <#elseif fastUpdate>
                <#assign updateId=elId?string />
                <#if !noLabel >
                    <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
                </#if>
                <#if useDataName >
                    <a class="field-inline-anchor" href="#" data-name="${id}" id="${id}-${updateId}" class="field-component ${addClass}" data-type="radio" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/update/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                <#else>
                    <a class="field-inline-anchor" href="#" id="${id}" class="field-component ${addClass}" data-type="radio" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/update/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                </#if>
            <#elseif noLabel>
                <@radioNoLabel id id label fieldDef.availableValuesMap mddata?first!"" editable/>
            <#else>
                <@radioHash id id label fieldDef.availableValuesMap mddata?first!"" editable/>
            </#if>

            <#break>
        <#case "CHECKBOX">
            <#if fieldDef.macro?? || fieldDef.macroView??>
                <#if !noLabel >
                <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
                </#if>

                <#if !editable && fieldDef.macroView??>
                    <#assign x=fieldDef.macroView/>
                <#else>
                    <#assign x=fieldDef.macro/>
                </#if>
                <@.vars[x] id id label fieldDef.availableValuesMap mddata![]  editable/>
            <#elseif fastUpdate>
                <#assign updateId=elId?string />
                <#--if !elId??> <#assign elId=model['element'].id?string /></#if-->
				<#if !noLabel >
                <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
                </#if>
                <#if useDataName >
                    <a class="field-inline-anchor" href="#" data-name="${id}" id="${id}-${updateId}" class="field-component ${addClass}" data-type="checkbox" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/update/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                <#else>
                    <a class="field-inline-anchor" href="#" id="${id}" class="field-component ${addClass}" data-type="checkbox" data-pk="${updateId}" data-url="${baseUrl}/app/rest/documents/update/${updateId}" data-title="${labelJS}">${mddata?first!""}</a>
                </#if>
            <#elseif noLabel>
            	<div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
                <@checkboxNoLabel id id label fieldDef.availableValuesMap mddata![]  editable/>
            <#else>
                <@checkboxHash id id label fieldDef.availableValuesMap mddata![]  editable/>
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
           <#--
            <#case "EXT_DICTIONARY">
            <@script>
            var ${id}_addFilters="";
            </@script>
             <#if mddata[0]??>
                <#assign selectedIds=[mddata[0]]/>
                    <#assign selectedValues=[mddata[0]?split("###")[1]]/>

            <#else>
                <#assign selectedValues=[]/>
                <#assign selectedIds=[]/>
            </#if>
            <#if fieldDef.addFilterFields??>
            <@script>
            var ${id}_addFilters="${fieldDef.addFilterFields}";
            </@script>
            </#if>
            <#if noLabel>
                <@singleAutoCompleteFunctionFBNoLabel id id label "${fieldDef.externalDictionary}" "title" selectedValues "id", selectedIds template.name  editable/>
            <#else>
                <@singleAutoCompleteFunctionFB id id label "${fieldDef.externalDictionary}" "title" selectedValues "id", selectedIds template.name  editable/>
            </#if>
            <#break>
            -->
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
    ${messages[id]!id}
</#macro>

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
        <span class="field-view-mode field-date" id="${id}">${txtValue}</span>
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
<#if editable>
    <#assign keys = values?keys>
    <#list keys as key>
        <span class="x-radio-input x-field-${name}">
            <div class="radio">
                <label>
                    <input type="radio" class="ace" onchange="valorizzaRadio('${id}')" id="${id}" name="${name}" value="${key?html}###${values[key]?html}" <#if (value?split("###")[0])==key>checked</#if> title="${values[key]}"><span class="lbl"> ${values[key]}</span>
                </label>
            </div>
        
        </span>
    </#list>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>

<span id="radioClear-${id}" name="radioClear-${id}">
    <div class="radio">
        <a href="#" onclick="$('[name=${name}]').prop('checked', false).trigger('change'); return false;"><i class="fa fa-eraser"></i> deseleziona</a>
    </div>
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
</#macro>




<#macro radioHash id name label values={} value="" editable=true>
<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
<div class="col-sm-9">
<@radioNoLabel id name label values value/>
</div>
</#macro>


<#macro checkboxNoLabel id name label values={} value=[] editable=true>
<#if editable>
    <#assign keys = values?keys>
    <#list keys as key>

        <span class="col-sm-9 x-checkbox-input x-field-${name}">
            <div class="checkbox">
                <label>
               		<#assign checkSelected=false>
                	<#if value?is_enumerable>
                		<#list value as selectedkey>
	                    	<#if selectedkey?split('###')[0]==key>
	                    		<#assign checkSelected=true>
	                		</#if>
	                    </#list>
                	</#if>
                    <input autocomplete='off' type="checkbox" class="ace" id="${id}" <#if checkSelected>checked="true"</#if> name="${name}" value="${key?html}###${values[key]?html}" title="${values[key]}"><span class="lbl"> ${values[key]}</span>

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
        	<#assign checkSelected=false>
            <#if value?is_enumerable>
            	<#list value as selectedkey>
	            	<#if selectedkey?split('###')[0]==key>
	                	<#assign checkSelected=true>
	                </#if>
	            </#list>
            </#if>
                	
            <#if checkSelected>
                <i class="icon-check"></i> 
            <#else>
                <i class="icon-check-empty"></i> 
            </#if>
            ${values[key]}
            <#if key_has_next><br/></#if>

        </#list>
    </span>
</#if>
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
<div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
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
<#assign htmlId=id+"-select"/>
<#--
<#if el?? && el.typeName?? && el.typeName != 'Budget' && el.typeName != 'BudgetSingoloBraccio'>
<#assign htmlId=id+"-select"/>
</#if>
-->
<#if value?? && value?contains("###")>
<#assign selectedCode=value?split("###")[0]/>
<#assign selectedDecode=value?split("###")[1]/>
</#if>
<#if editable>
<@script>


if (jsInitFieldFunctions==undefined){
var jsInitFieldFunctions=new Object();
}

jsInitFieldFunctions['${id}']=function(baseSelector, initValue){
var selector="";
if(baseSelector!=undefined) {
selector=baseSelector+" ";
}
var val="${value?html}";
if (initValue!=undefined) val=initValue;
var altroDecode='altrooo';
if (val.indexOf('-9999###')==0) {
<#assign keys = values?keys>
<#list keys as key>
<#if key == "-9999">altroDecode='${values[key]}'</#if>
</#list>
$(selector+'select[name=${htmlId}]').val("-9999###"+altroDecode);
$(selector+'input[name="${id}"]').val(val);
}else {
$(selector+'select[name=${htmlId}]').val(val);
$(selector+'input[name="${id}"]').val(val);//HDCRPMS-1146 vmazzeo 15.03.2018
}
var addAltroField=function(value){
$(selector+'input[name="${id}-altro"]').remove();
$(selector+'select[name=${htmlId}]').after('<input type="text" id="${id}-altro" placeholder="specificare altro ..." name="${name}-altro" />');
$(selector+'input[name="${id}-altro"]').val(value);
$(selector+'input[name="${id}-altro"]').change(function(){
if ($(selector+'select[name=${htmlId}]').val().indexOf('-9999###')==0){
$(selector+'[name=${id}]').val('-9999###' + $(selector+'input[name="${id}-altro"]').val());
}
});
}
if (val.indexOf('-9999###')==0) {
addAltroField("${selectedDecode?html}");
if (initValue!=undefined) {
var altroSpec=val.replace('-9999###','');
$(selector+'input[name="${id}-altro"]').val(altroSpec);
}
}

var removeAltroField=function(){
$(selector+'input[name="${id}-altro"]').remove();
}

//$(selector+'select[name=${htmlId}]').unbind('change');//VMAZZEO TOLGO UNBIND ALTRIMENTI PERDIAMO I BIND SPECIFICI HDCRPMS-1083
$(selector+'select[name=${htmlId}]').change(function(){

if ($(this).val().indexOf('-9999###')==0){
addAltroField("");
$(selector+'input[name="${id}-altro"]').focus();
}else {
removeAltroField();
if ('${htmlId}'!='${id}'){
$(selector+'[name=${id}]').val($(selector+'[name=${htmlId}]').val());
}
<#if htmlId!=id>
if($(selector+'select[name=${htmlId}]').data('select2')){ //HDCRPMS-465 gestito come in PD crpms-352 migliorato check su abilitazione select2
$(selector+'[name=${id}]').val($(selector+'[name="${htmlId}"]').select2('data').id);
}else{
$(selector+'[name=${id}]').val($(selector+'[name="${htmlId}"]').val());
}
</#if>
}
});
}

jsInitFieldFunctions['${id}']();

</@script>
<div class="col-sm-9">
    <select id="${htmlId}" name="${htmlId}" <#if !editable>disabled="disabled"</#if>>
<option></option>
<#assign keys = values?keys>
<#list keys as key>
<option value="${key?html}###${values[key]?html}"
<#if key?split("###")[0]=selectedCode>selected</#if>>${values[key]}</option>
</#list>
</select>
<input type="text" id="${id}-altro" name="${name}-altro" style="display:none">
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
            
            return '${searchScript}?'+addedParam;
        }

        function populateSelect_${id}(){
            $('#${id}-select').select2("val", "");
            $('#${id}-select').html("");
            $('#${id}-select').append("<option></option>");

            var url=buildScriptUrl_${id}();
            var valorizza=function(){
                
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
                                
                                valorizza=function(){
                                    
                                    $('#${id}-select').select2("val", "${selectedIds[idx]?html}");
                                var myVal="${selectedIds[idx]?html}";
                                if(myVal.indexOf("-9999###")==0){
                                    var altroValue=$('#${id}-select option[value^="-9999###"]').val();
                                    $('#${id}-select').select2("val",altroValue);
                                }
                                }   ;
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
                    var altroValue=$('#${id}-select option[value^="-9999###"]').val();
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
                    
                    
                    val=valueOfField(idField);
                    
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
                                {id: "${selectedIds[idx]}", name: "${sv?html}"},
                                <#assign idx=idx+1/>
                            </#list>

                        <#else>
                            <#list selectedValues as sv>
                                {id: '${sv}', name: "${sv?html}"},
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


<#macro documentazioneParereEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
	<#if noLabel==false>
		${label}
	</#if>
   	<div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>
	<@script>
	
	$(document).ready(function(){
		//alert("ready");
		var centro='';
		
		if (typeof loadedElement.parentId == 'undefined' ){
			centro= $(location).attr('href').split("/")[7];
		}else{
			centro= loadedElement.parentId;
		}
		//alert (centro);
		
		var request = $.ajax({
		url: "/get_documentazione.php",
		method: "POST",
		data: { id : loadedElement.id , centro_id: centro},
		dataType: "html"
		});
	 
		request.done(function( msg ) {
		$( "#${id}-ajax-container" ).html( msg );
		});
	 
		request.fail(function( jqXHR, textStatus ) {
		alert( "Request failed: " + textStatus );
		});
	});
	
	</@script>
</#macro>


<#macro documentazioneParereView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>
        //alert("ready");
        var parere='';

        parere= $(location).attr('href').split("/")[7];
        console.log(parere);

                var request2 = $.ajax({
                url: "/get_documentazione_view.php",
                method: "POST",
                data: { id : parere},
                dataType: "html"
                });

                request2.done(function( msg ) {
                $( "#${id}-ajax-container" ).html( msg );
                });

                request2.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
                });

    </@script>
</#macro>


<#macro documentazioneParereStudioEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
        <div id="${id}-ajax-container"></div>
        <@script>

            $(document).ready(function(){
                //alert("ready");
                var centro='';
                var studio='';

                if (typeof loadedElement.parentId == 'undefined' ){
                    centro= $(location).attr('href').split("/")[7];
                    var request = $.ajax({
                        url: "/sirer/app/rest/documents/getelementidstudio/"+centro,
                        method: "GET",
                        dataType: "json"
                    });

                    request.done(function( msg ) {
                        studio= msg.ret;

                        var request2 = $.ajax({
                            url: "/get_documentazione_studio.php",
                            method: "POST",
                            data: { id : loadedElement.id , studio_id: studio},
                            dataType: "html"
                        });

                        request2.done(function( msg ) {
                            $( "#${id}-ajax-container" ).html( msg );
                        });

                        request2.fail(function( jqXHR, textStatus ) {
                            alert( "Request failed: " + textStatus );
                        });
                    });

                    request.fail(function( jqXHR, textStatus ) {
                        alert( "Request failed: " + textStatus );
                    });

                }else{
                    centro= loadedElement.parentId;
                    var request = $.ajax({
                        url: "/sirer/app/rest/documents/getelementidstudio/"+centro,
                        method: "GET",
                        dataType: "json"
                    });

                    request.done(function( msg ) {
                        studio= msg.ret;

                        var request2 = $.ajax({
                            url: "/get_documentazione_studio.php",
                            method: "POST",
                            data: { id : loadedElement.id , studio_id: studio},
                            dataType: "html"
                        });

                        request2.done(function( msg ) {
                            $( "#${id}-ajax-container" ).html( msg );
                        });

                        request2.fail(function( jqXHR, textStatus ) {
                            alert( "Request failed: " + textStatus );
                        });
                    });

                    request.fail(function( jqXHR, textStatus ) {
                        alert( "Request failed: " + textStatus );
                    });

                }


            });

        </@script>
</#macro>


<#macro documentazioneParereStudioView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>
        //alert("ready");
        var parere='';

        parere= $(location).attr('href').split("/")[7];
        console.log(parere);

        var request2 = $.ajax({
            url: "/get_documentazione_studio_view.php",
            method: "POST",
            data: { id : parere},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
</#macro>

<#macro documentazioneParereEmeEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
	<#if noLabel==false>
		${label}
	</#if>
   	<div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>
	<@script>
	
	$(document).ready(function(){
		//alert("ready");
		var eme='';
		
		if (typeof loadedElement.parentId == 'undefined' ){
			eme= $(location).attr('href').split("/")[7];
		}else{
			eme= loadedElement.parentId;
		}
		//alert (eme);
		
		var request = $.ajax({
		url: "/get_documentazione_eme.php",
		method: "POST",
		data: { id : loadedElement.id , eme_id: eme},
		dataType: "html"
		});
	 
		request.done(function( msg ) {
		$( "#${id}-ajax-container" ).html( msg );
		});
	 
		request.fail(function( jqXHR, textStatus ) {
		alert( "Request failed: " + textStatus );
		});
	});
	
	</@script>
</#macro>


<#macro documentazioneParereEmeView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>
        //alert("ready");
        var parere='';

        parere= $(location).attr('href').split("/")[7];
        console.log(parere);

        var request2 = $.ajax({
            url: "/get_documentazione_eme_view.php",
            method: "POST",
            data: { id : parere},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
</#macro>

<#macro documentazioneParerePazEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>
    <@script>

        $(document).ready(function(){
            //alert("ready");
            var paz='';

            if (typeof loadedElement.parentId == 'undefined' ){
                paz= $(location).attr('href').split("/")[8];
            }else{
                paz= loadedElement.parentId;
            }
            //alert (eme);

            var request = $.ajax({
                url: "/get_documentazione_paz.php",
                method: "POST",
                data: { id : loadedElement.id },
                    dataType: "html"
            });

            request.done(function( msg ) {
                $( "#${id}-ajax-container" ).html( msg );
            });

            request.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
            });
        });

    </@script>
</#macro>


<#macro documentazioneParerePazView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>
        //alert("ready");
        var parere='';
        var paz='';

        parere= $(location).attr('href').split("/")[7];
        paz=parere.split("#")[0];
        console.log(parere);

        var request2 = $.ajax({
            url: "/get_documentazione_paz_view.php",
            method: "POST",
            data: { id : paz},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
</#macro>



<#macro componentiParereEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>

    <@script>

        $(document).ready(function(){

            var username='${userDetails.username}';

            var request = $.ajax({
                url: "/get_componenti.php",
                method: "POST",
                data: { id : loadedElement.id , username: username},
                    dataType: "html"
                });

            request.done(function( msg ) {
                $( "#${id}-ajax-container" ).html( msg );
            });

            request.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
            });
        });

    </@script>
</#macro>


<#macro componentiParereView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>

        var parere='';
        parere= $(location).attr('href').split("/")[7];
        console.log(parere);

        var request2 = $.ajax({
            url: "/get_componenti_view.php",
            method: "POST",
            data: { id : parere},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
</#macro>



<#macro componentiParereEmeEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>

    <@script>

        $(document).ready(function(){

            var username='${userDetails.username}';

            var request = $.ajax({
                url: "/get_componenti.php",
                method: "POST",
                data: { id : loadedElement.id , username: username, emendamento: "yes"},
                dataType: "html"
            });

            request.done(function( msg ) {
                $( "#${id}-ajax-container" ).html( msg );
            });

            request.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
            });
        });

    </@script>
</#macro>


<#macro componentiParereEmeView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
        </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>

        var parere='';
        parere= $(location).attr('href').split("/")[7];
        console.log(parere);

        var request2 = $.ajax({
            url: "/get_componenti_view.php",
            method: "POST",
            data: { id : parere, emendamento: "yes"},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
</#macro>



<#macro componentiParerePazEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>

    <@script>

        $(document).ready(function(){

            var username='${userDetails.username}';

            var request = $.ajax({
                url: "/get_componenti.php",
                method: "POST",
                data: { id : loadedElement.id , username: username, pazienti: "yes"},
                dataType: "html"
            });

            request.done(function( msg ) {
                $( "#${id}-ajax-container" ).html( msg );
            });

            request.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
            });
        });

    </@script>
</#macro>


<#macro componentiParerePazView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>

        var parere='';
        var paz="";

        parere= $(location).attr('href').split("/")[7];
        paz=parere.split("#")[0];
        console.log(paz);

        var request2 = $.ajax({
            url: "/get_componenti_view.php",
            method: "POST",
            data: { id : paz, pazienti: "yes"},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
</#macro>



<#macro documentazioneParereEmeStudioEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>
    <@script>

    $(document).ready(function(){
        //alert("ready");
        var centro='';
        var studio='';

        if (typeof loadedElement.parentId == 'undefined' ){
            centro= $(location).attr('href').split("/")[7];
            var request = $.ajax({
                url: "/sirer/app/rest/documents/getelementidstudio/"+centro,
                method: "GET",
                dataType: "json"
            });

            request.done(function( msg ) {
                studio= msg.ret;

                var request2 = $.ajax({
                    url: "/get_documentazione_studio.php",
                    method: "POST",
                    data: { id : loadedElement.id , studio_id: studio, emendamento: "yes"},
                    dataType: "html"
                });

                request2.done(function( msg ) {
                    $( "#${id}-ajax-container" ).html( msg );
                });

                request2.fail(function( jqXHR, textStatus ) {
                    alert( "Request failed: " + textStatus );
                });
            });

            request.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
            });

        }else{
            centro= loadedElement.parentId;
            var request = $.ajax({
                url: "/sirer/app/rest/documents/getelementidstudio/"+centro,
                method: "GET",
                dataType: "json"
            });

            request.done(function( msg ) {
                studio= msg.ret;

                var request2 = $.ajax({
                    url: "/get_documentazione_studio.php",
                    method: "POST",
                    data: { id : loadedElement.id , studio_id: studio, emendamento: "yes"},
                    dataType: "html"
                });

                request2.done(function( msg ) {
                    $( "#${id}-ajax-container" ).html( msg );
                });

                request2.fail(function( jqXHR, textStatus ) {
                    alert( "Request failed: " + textStatus );
                });
            });

            request.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
            });

        }


    });

    </@script>
</#macro>

<#macro documentazioneParereEmeStudioView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>
        //alert("ready");
        var parere='';

        parere= $(location).attr('href').split("/")[7];
        console.log(parere);

        var request2 = $.ajax({
            url: "/get_documentazione_studio_view.php",
            method: "POST",
            data: { id : parere, emendamento: "yes"},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
</#macro>

<#macro documentazioneParereEmeCentroEdit id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <div id="${id}-ajax-container"></div>
    <@script>

        $(document).ready(function(){
            //alert("ready");
            var centro=$('#ParereEme_CentroEmeId').val();

            //alert (centro);

            var request = $.ajax({
                url: "/get_documentazione.php",
                method: "POST",
                data: { id : loadedElement.id , centro_id: centro, emendamento: "yes"},
                dataType: "html"
            });

            request.done(function( msg ) {
                $( "#${id}-ajax-container" ).html( msg );
            });

            request.fail(function( jqXHR, textStatus ) {
                alert( "Request failed: " + textStatus );
            });
        });

    </@script>
</#macro>

<#macro documentazioneParereEmeCentroView id=null name="" label="" searchScript="" searchValue="" selectedValues=[] searchId="" selectedIds=[] templateName="" noLabel=true fieldDef={} editable=true>
    <#if noLabel==false>
        ${label}
    </#if>
    <div class="checkbox" id="cb_${id}_all" ><a href="#" onclick="$('input[name=${id}]').prop('checked', true); return false;" >Seleziona tutto</a> - <a href="#" onclick="$('input[name=${id}]').prop('checked', false); return false;" >Deseleziona tutto</a></div>
    <b><div id="${id}-ajax-container"></div></b>
    <@script>
        //alert("ready");
        var parere='';

        parere= $(location).attr('href').split("/")[7];
        console.log(parere);

        var request2 = $.ajax({
            url: "/get_documentazione_view.php",
            method: "POST",
            data: { id : parere, emendamento: "yes"},
            dataType: "html"
        });

        request2.done(function( msg ) {
            $( "#${id}-ajax-container" ).html( msg );
        });

        request2.fail(function( jqXHR, textStatus ) {
            alert( "Request failed: " + textStatus );
        });

    </@script>
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
    <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
    <div class="col-sm-9">
        <@multiAutoCompleteNoLabel id name label searchScript searchValue selectedValues theme single searchId selectedIds/>
    </div>
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

        function buildURI_${usedTokenInput}() {
			var url = "${searchScript}";
			var regexp = /\[(.*)\]/;
			var matches = url.match(regexp);
			if (Array.isArray(matches) && matches.length>0){
				url=url.replace(matches[0],valueOfField(matches[1]));
			}
			return url;
		}
		

            $("#${id}.randomClass-${usedTokenInput}").tokenInput(buildURI_${usedTokenInput}, {
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
                                {id: "${selectedIds[idx]}", name: "${sv?html}"},
                                <#assign idx=idx+1/>
                            </#list>

                        <#else>
                            <#list selectedValues as sv>
                                {id: '${sv}', name: "${sv?html}"},
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
                    
                        if(typeof item.id==="string" && item.id.match("^-9999###")){
                            <#-- vmazzeo CRPMS-354 PORTATO CON TOSCANA-135 14.03.2017
                             * è possibile che l'elemento ${id}Altro non abbia il prefisso informations (vedi costiForm.ftl)
                             * quindi aggiungo controllo sull'esistenza del div #informations-${id}Altro altrimenti provo con #${id}Altro
                            -->
                            if($("#informations-${id}Altro").length){
                                $("#informations-${id}Altro").show();
                            }
                            else if($("div[id$='-${id}Altro']").length){
                                $("div[id$='-${id}Altro']").show();
                            }
                        }
                        else{
                            if($("#informations-${id}Altro").length){
                                $("#informations-${id}Altro input").val("");
                                $("#informations-${id}Altro").hide();
                            }
                            else if($("div[id$='-${id}Altro']").length){
                                $("div[id$='-${id}Altro']")
                                $("div[id$='-${id}Altro'] input").val("");
                                $("div[id$='-${id}Altro']").hide();
                            }
                        }
                },
                onDelete: function (item){
                    
                            if($("#informations-${id}Altro").length){
                                $("#informations-${id}Altro input").val("");
                                $("#informations-${id}Altro").hide();
                            }
                            else if($("div[id$='-${id}Altro']").length){
                                $("div[id$='-${id}Altro'] input").val("");
                                $("div[id$='-${id}Altro']").hide();

                            }
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
                            if($("#informations-${id}Altro").length){
                                $("#informations-${id}Altro").show();
                            }
                            else if($("div[id$='-${id}Altro']").length){
                                $("div[id$='-${id}Altro']").show();
                            }
                    <#else>
                            if($("#informations-${id}Altro").length){
                             $("#informations-${id}Altro").hide();
                            }
                            else if($("div[id$='-${id}Altro']").length){
                                $("div[id$='-${id}Altro']").hide();
                            }
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
        
        function buildURI_${usedTokenInput}() {
			var url = "${searchScript}";
			var regexp = /\[(.*)\]/;
			var matches = url.match(regexp);
			if (Array.isArray(matches) && matches.length>0){
				url=url.replace(matches[0],valueOfField(matches[1]));
			}
			return url;
		}
		
		
            $("#${id}.randomClass-${usedTokenInput}").tokenInput(buildURI_${usedTokenInput}, {
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
                                {id: "${selectedIds[idx]}", name: "${sv?html}"},
                                <#assign idx=idx+1/>
                            </#list>

                        <#else>
                            <#list selectedValues as sv>
                                {id: '${sv}', name: "${sv?html}"},
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

<#macro hiddenField id name label=null value="" size=30 noLabel=true fieldDef=null editable=true>
<input type="hidden" name="${name}" id="${id}" value="${value!""}"/>
</#macro>

<#macro hidden id name value="">
<input type="hidden" name="${name}" id="${id}" value="${value!""}"/>
</#macro>

<#macro textboxNoLabel id name label value="" size=10 editable=true>
<#if editable>
<input type="text" <#if !editable>disabled="disabled"</#if> name="${name}" id="${id}" value="${value!""}" size="${size}"/>
<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
    <span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
    <span id="alert-msg-${id}"></span>
</span>
<#else>
    <span id="${id}" class="field-view-mode field-textbox">${value!""}</span>
</#if>
</#macro>

<#macro textbox id name label value="" size=10 editable=true>
<label  class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
<div class="col-sm-9">
<@textboxNoLabel id name label value size/>
</div>
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

<#macro textareaNoLabel id name label cols=40 rows=1 value="" editable=true >
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

<#macro textarea id name label cols=40 rows=1 value="" editable=true>
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
        $(document).ready(function(){
            $('#${id}').editable({
                source: source_${id},
                select2:{
                    initSelection: function (element, callback) {
                        var data = new Object;
                        data.id="${value}";
                        data.text="${displayValue}";
                        callback(data);
                    }
                },
                success: function(response, newValue) {
                    if (jQuery.isFunction(window.fastUpdatePageCallback)){
                        fastUpdatePageCallback(response, newValue, '${id}', ${parentId});
                    }
                }
            });
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
            
            url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
            $.getJSON( url, function( data ) {
            
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
            
            url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
            $.getJSON( url, function( data ) {
            
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

            
            url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${parentId}/AllegatoContratto";
            $.getJSON( url, function( data ) {
            
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

<#macro emendamentoSelect id name label value="" size=30 noLabel=true fieldDef={} editable=true>
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


<#if fieldDef.padre?? && fieldDef.padre=="1">
    <#assign studioId=parentEl.parent.id />
</#if>
<#if fieldDef.padre?? && fieldDef.padre=="2">
    <#assign studioId=parentEl.parent.parent.id />
</#if>




    <@script>

            
            url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${studioId}/Emendamento";
            $.getJSON( url, function( data ) {
            
            for (i=0;i<data.length;i++){

                

                    if ('${value}'==data[i].id+'###'+data[i].metadata.DatiEmendamento_CodiceEme[0]) selected=" selected";
                    else selected="";

                    $('#${id}').append('<option '+selected+' value="'+data[i].id+'###'+data[i].metadata.DatiEmendamento_CodiceEme[0]+'">'+data[i].metadata.DatiEmendamento_CodiceEme[0]+'</option>');


            }
            });
            $('#${id}').unbind('change').bind("change",function(){
            $('#Emendamento-Emendamento_Emendamento').css('transition', 'border-color 3s');
            var loadingSpan=$('<span>');
                            if ($('#Emendamento_Emendamento-loadingSpan')){
                                $('#Emendamento_Emendamento-loadingSpan').remove();
                            }
                            loadingSpan.attr('id','Emendamento_Emendamento-loadingSpan');
                            loadingSpan.addClass('saving-span');
                            loadingSpan.html('<i class="fa fa-spinner fa-spin fa-fw"></i>');
                            $('#Emendamento-Emendamento_Emendamento').css('display','inline');
                            $('#Emendamento-Emendamento_Emendamento').append(loadingSpan);
                            $.post( "${baseUrl}/app/rest/documents/updateField/${el.id}",{name:'Emendamento_Emendamento', value:$(this).val()}, function( data ) {
                                if (data.result!='OK'){
                                    alert('Attenzione! errore nel salvataggio');
                                    $('#Emendamento_Emendamento-loadingSpan').html('<i class="fa fa-exclamation-triangel red"></i>');
                                    $('#Emendamento_Emendamento').css('cssText', 'border: 1px solid red !important');
                                }
                                else {
                                    $('#Emendamento_Emendamento-loadingSpan').html('<i class="fa fa-check green"></i>');
                                    $('#Emendamento_Emendamento').css('cssText', 'border: 1px solid green !important');
                                    setTimeout(function(){
                                        $('#Emendamento_Emendamento-loadingSpan').remove();
                                        $('#Emendamento_Emendamento').css('cssText', 'border: 1px solid #aaa !important');
                                    },2500);
                                }
                            });
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

            
            url="${baseUrl}/app/rest/documents/getElementsByParentAndType/${studioId}/Emendamento";
            $.getJSON( url, function( data ) {
            
            for (i=0;i<data.length;i++){

                

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
                                        <#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
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
                                    text:'Salva',
                                    click:function(){

                                        <#list template.fields as field>
                                            <#if field.mandatory>
												
                                                <#assign label=getLabel(template.name+"."+field.name)/>
                                                var $input=$('#${template.name}_${field.name}');
                                                if ($input.is(':visible') && $input.val()==""){ //LUIGI:controllo di visibilità del padre del campo obbligatorio
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
                                            <#assign myElJson=el.getElementCoreJsonToString(userDetails) /> <#-- SIRER-60 trovato bug su loadedElement -->
                                            var myEl=${myElJson};
                                            myElement.id=myEl.id;
                                            myElement.type=myEl.type;
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
                                                    else if(window.location.hash!=""){
                                                            myHash=window.location.hash;
                                                            window.location.hash="";
                                                            window.location.hash=myHash;
                                                    }
                                                }else {
                                                    var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
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
                                         }catch(err){
                                            bootbox.hideAll();
                                            bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');

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
                    var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
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
            <@fileChooser "file" "file" getLabel(model['docDefinition'].typeId+".fileLabel")+"<sup style='color:red'>*</sup>"/>
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

        $('#${id}').val(val);
        if (val.indexOf('-9999###')==0) {

            $('#${id}-altro').show();
            $('#${id}-altro').val("${selectedDecode?html}");
        }

        $('#${id}-altro').change(function(){
            if ($('#${id}-select').val().indexOf('-9999###')==0){
                $('#${id}').val('-9999###' + $('#${id}-altro').val());
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
                <#assign label=messages[template.name+"."+field.name]!template.name+"."+field.name/>
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
                <#list template.fields as field>
                    <#if field.mandatory>

                        <#assign label=getLabel(template.name+"."+field.name)/>
                        var $input=$form.find('#${template.name}_${field.name}');
                        if ($input.is(':visible') && $input.val()==""){ //LUIGI:controllo di visibilità del padre del campo obbligatorio
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
                    <#assign myElJson=el.getElementCoreJsonToString(userDetails) /> <#-- SIRER-60 trovato bug su loadedElement -->
                    var myEl=${myElJson};
                    myElement.id=myEl.id;
                    myElement.type=myEl.type;
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
                            else if(window.location.hash!=""){
                                myHash=window.location.hash;
                                window.location.hash="";
                                window.location.hash=myHash;
                            }
                        }else {
                            var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
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
                 }catch(err){
                    bootbox.hideAll();
                    bootbox.alert('Errore salvataggio! <i class="icon-warning-sign red"></i>');

                 }
            });
            </@script>
                <div class="clearfix"></div>
                 <button class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span>
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


<#macro TemplateFormTable templateName el userDetails editable titleTable="" classes="" forceReload="false" forceEdit=false>
<!-- QUA INIZIO LA MACRO -->
<#assign toClose=false />
<#if forceEdit>
<#assign editable = forceEdit />
</#if>
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>

    <#assign groupActive=false />
    <#list el.elementTemplates as elementTemplate>
        <#if elementTemplate.metadataTemplate.name==templateName && elementTemplate.enabled>
        <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
            <#if templatePolicy.canView>

            <#assign template=elementTemplate.metadataTemplate/>
                <#assign toClose=true />
            <div id="metadataTemplate-${template.name}" class="${classes}">
            <!-- TemplateFormTable: ${templateName} -->
            <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
                <#if forceEdit>
                    <div name="${template.name}" style="" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;" >
                <#else>
                    <form name="${template.name}" style="" id="form-${template.name}" method="POST" action="${baseUrl}/app/rest/documents/update/" onsubmit="return false;" >
                </#if>
            </#if>
            <table class="table table-bordered" id="checklist">
                            <thead>
                                <tr><th colspan="2">${titleTable}</th></tr>
                            </thead>
            <#list template.fields as field>
                <@SingleFieldTd template.name field.name el userDetails editable forceEdit />
            </#list>
        </table>
        <!-- FINISCO LA TABELLA DEI CAMPI -->

      </#if>

        </#if>
    </#list>


    <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
    	<!-- ENTRO QUI PER DIRIMERE LO SCRIPT PER IL SALVA FORM -->
        <#assign myElJson=el.getElementCoreJsonToString(userDetails) /> <#-- SIRER-60 trovato bug su loadedElement -->
    	<!-- EL ${myElJson} -->
    	<@script>
    	//SCRIPT PER TEMPLATE: ${template.name}
    	$("[name=salvaForm-${template.name}]").on('click',function(){
                var $form=$($(this).data('rel'));
                //QUESTO E' IL CODICE DI MACROS.FTL
                var nomeTemp = "MACROS.FTL";
                if($(this).attr('id')){
                    var formName=$(this).attr('id').replace("salvaForm-", "");
                }else{
                	formName="formNonEsistente";
                }
                <#list template.fields as field>
                    <#if field.mandatory>

						var $input;
						var notcompiled=false;
						<#if field.type=="RADIO" >
							$input=$form.find("input[name='${template.name}_${field.name}']:checked");
							notcompiled=$input.val()===undefined || $input.val()=="";
						<#elseif field.type=="CHECKBOX">
							$input=$form.find("input[name='${template.name}_${field.name}']:checked").length;
							notcompiled=$input==0;
						<#else>
							$input=$form.find('#${template.name}_${field.name}');
							notcompiled=$input.val()===undefined || $input.val()=="";
						</#if>
						<#assign label=getLabel(template.name+"."+field.name)/>
						if ( ($("#informations-${template.name}_${field.name}").is(':visible') || $("#${template.name}-${template.name}_${field.name}").is(':visible')) && (notcompiled) ){ //LUIGI:controllo di visibilità del padre del campo obbligatorio
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
                    var forceReload=${forceReload?string};
                    var myEl=${myElJson};
                    myElement.id=myEl.id;
                    myElement.type=myEl.type;
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

                            if (data.redirect && !forceReload){
                                window.location.href=data.redirect;
                            }
                            else if(forceReload){
                                window.location.reload(true);
                            }
                            else if(window.location.hash!=""){
                                myHash=window.location.hash;
                                window.location.hash="";
                                window.location.hash=myHash;
                            }
                        }else {
                            var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
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
                        loadingScreen("Errore salvataggio!", "alerta");


                    });
                 }catch(err){
                    bootbox.hideAll();
                    loadingScreen("Errore salvataggio!", "alerta");
                    
                 }
                
       	});
    	//FINE SCRIPT PER TEMPLATE: ${template.name}
    	</@script>
            <#--  --@script>
            $("[name=salvaForm-${template.name}]").on('click',function(){
                var $form=$($(this).data('rel'));
                //QUESTO E' IL CODICE DI MACROS.FTL
                var nomeTemp = "MACROS.FTL";
                if($(this).attr('id')){
                    var formName=$(this).attr('id').replace("salvaForm-", "");
                }else{formName="formNonEsistente"}
                <#list template.fields as field>
                    <#if field.mandatory>

						var $input;
						var notcompiled=false;
						<#if field.type=="RADIO" >
							$input=$form.find("input[name='${template.name}_${field.name}']:checked");
							notcompiled=$input.val()===undefined || $input.val()=="";
						<#elseif field.type=="CHECKBOX">
							$input=$form.find("input[name='${template.name}_${field.name}']:checked").length;
							notcompiled=$input==0;
						<#else>
							$input=$form.find('#${template.name}_${field.name}');
							notcompiled=$input.val()===undefined || $input.val()=="";
						</#if>
						<#assign label=getLabel(template.name+"."+field.name)/>
						if ( ($("#informations-${template.name}_${field.name}").is(':visible') || $("#${template.name}-${template.name}_${field.name}").is(':visible')) && (notcompiled) ){ //LUIGI:controllo di visibilità del padre del campo obbligatorio
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
                    var forceReload=${forceReload};
                    <#assign myElJson=el.getElementCoreJsonToString(userDetails) /> <#-- SIRER-60 trovato bug su loadedElement -- >
                    var myEl=${myElJson};
                    myElement.id=myEl.id;
                    myElement.type=myEl.type;
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

                            if (data.redirect && !forceReload){
                                window.location.href=data.redirect;
                            }
                            else if(forceReload){
                                window.location.reload(true);
                            }
                            else if(window.location.hash!=""){
                                myHash=window.location.hash;
                                window.location.hash="";
                                window.location.hash=myHash;
                            }
                        }else {
                            var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
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
                        loadingScreen("Errore salvataggio!", "alerta");


                    });
                 }catch(err){
                    bootbox.hideAll();
                    loadingScreen("Errore salvataggio!", "alerta");
                    
                 }
            });
            </@script-->
            <!-- FINE DELL'ASSEGNAZIONE SCRIPT SALVA FORM -->
                <div class="clearfix"></div>
                 <button id="salvaForm-${template.name}" class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" ><i class="icon-save bigger-160" ></i><b>Salva</b></span>
                                            </button>
                <!--input id="salvaForm-${template.name}" class="submitButton round-button blue templateForm" type="button" value="Salva modifiche"-->
                <#if forceEdit>
                    </div>
                <#else>
                    </form>
                </#if>
            </#if>
</#if>
<#if toClose >
</div>
</#if>
<!-- QUA TERMINA LA MACRO -->
</#macro>
<#macro TemplateFormTableAlpaca templateName el userDetails editable titleTable="" classes="" forceReload="false" forceEdit=false horizontalView=true >
<#assign toClose=false />
<#if el.elementTemplates?? && el.elementTemplates?size gt 0>

    <#assign groupActive=false />
    <#list el.elementTemplates as elementTemplate>
        <#if elementTemplate.metadataTemplate.name==templateName && elementTemplate.enabled>
            <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
            <#if templatePolicy.canView>

                <#assign template=elementTemplate.metadataTemplate/>
                    <#--  --assign toClose=true /-->
                <div id="metadataTemplate-${template.name}" class="${classes}">
                    <div id="metadataTemplate-${template.name}-FORM">&nbsp;</div>
                </div>
                <#assign alpacaMode="" />
                <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit) >
                    <#assign alpacaMode="editMode" />
                <#else>
                    <#assign alpacaMode="viewMode" />
                </#if>
                <#--
                <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit) >
                    <#assign alpacaMode="editMode" />
                <#else>
                    <#assign alpacaMode="viewMode" />
                </#if>
                -->
                <@script>
                    if (alpacaJsons==undefined){
                        var alpacaJsons={};
                    }
                    var alpacaJSON_${templateName} = {};

                    $.ajax({
                        url: baseUrl+"/app/rest/documents/xml/${templateName}/${el.id}/alpaca/${alpacaMode}",
                        type: "GET",
                        dataType: "json"

                    }).done(function(jsonData) {
                        //alert(jsonData);
                        $("#metadataTemplate-${template.name}-FORM").html("<div class='loading'><i class='fa fa-spin fa-spinner'></i> caricamento ...</div>");
                        alpacaJSON_${templateName} = jsonData;
                        alpacaJsons['${templateName}']=jsonData;
                        <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
                            jsonData.options["form"] = {
                                "buttons": {
                                    "submit": {
                                        "title": "<i class=\"icon-save bigger-160\"></i> Salva",
                                        "click": function() {
                                            fzSalvaForm_${template.name}(alpacaJSON_${templateName});
                                        },
                                        "id": "salvaForm-${template.name}",
                                        "attributes": {
                                            "class": "btn btn-warning",
                                            "name": "salvaForm-${template.name}",
                                            "data-rel": "#form-${template.name}"
                                        }
                                    }
                                },
                                "toggleSubmitValidState": false
                            };

                            if (typeof(jsonData.postRenderFunction)!='undefined' && jsonData.postRenderFunction!=null){
                                jsonData.postRender = function(control){
                                    $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                    ( function(dsString){
                                        eval(dsString);
                                    })(jsonData.postRenderFunction);
                                    $('#metadataTemplate-${template.name}-FORM select option[value=""]').empty().append("[Seleziona...]");
                                    $("select").select2();
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').attr('data-date-format',"dd/mm/yyyy");
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').datepicker({autoclose:true,  format: 'dd/mm/yyyy', locale: 'it' });
                                    $("#metadataTemplate-${template.name}-FORM .alpaca-required-indicator").empty();
                                    //onReadyFunction
                                    if (typeof(onReadyFunction) === "function") {
                                        onReadyFunction();
                                    }
                                };
                            }else{
                                jsonData.postRender = function(control){
                                    $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                    $('#metadataTemplate-${template.name}-FORM select option[value=""]').empty().append("[Seleziona...]");
                                    $("select").select2();
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').attr('data-date-format',"dd/mm/yyyy");
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').datepicker({autoclose:true,  format: 'dd/mm/yyyy', locale: 'it' });
                                    $("#metadataTemplate-${template.name}-FORM .alpaca-required-indicator").empty();
                                    //onReadyFunction
                                    if (typeof(onReadyFunction) === "function") {
                                        onReadyFunction();
                                    }
                                };
                            }
                        <#else>
                            if (typeof(jsonData.postRenderFunction)!='undefined' && jsonData.postRenderFunction!=null){
                                jsonData.postRender = function(control){
                                    $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                    ( function(dsString){
                                        eval(dsString);
                                    })(jsonData.postRenderFunction);
                                    $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                    //$("select").select2();
                                    $("#metadataTemplate-${template.name}-FORM .alpaca-required-indicator").empty();
                                };
                            }else{

                                jsonData.postRender = function(control){
                                    $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                    //$("select").select2();
                                    $("#metadataTemplate-${template.name}-FORM .alpaca-required-indicator").empty();
                                };
                            }
                        </#if>

                        <#if horizontalView>
                            //Visualizzazione orizzontale
                            jsonData.view.parent = jsonData.view.parent+"-horizontal";
                        </#if>

                            $.each(jsonData.options.fields, function(key, val){
                                if (typeof(val.dataSourceFunction)!='undefined' && val.dataSourceFunction!=null){
                                    val.dataSource = function(callback){
                                        ( function(dsString){
                                            eval(dsString);
                                        })(val.dataSourceFunction);
                                    };
                                }
                                if (val.type=="date"){

                                    val["picker"]={
                                        "format": "DD/MM/YYYY",
                                        "locale": "it"
                                    }
                                    val["dateFormat"]="DD/MM/YYYY";
                                    //val["maskString"]="DD/MM/YYYY";
                                    //val["fieldClass"]+= " datePickerAlpaca ";
                                }
                                if (val.type=="select"){
                                    val["removeDefaultNone"]=false;
                                }
                                if (val.type=="select" || val.type=="radio" || val.type=="checkbox"){
                                    val["emptySelectFirst"]=false;
                                }
                            });
                            $("#metadataTemplate-${template.name}-FORM").alpaca(jsonData);
                            <#--if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
                                enableSalvaForm_${template.name}();
                            </#if-->

                        });
                </@script>
            </#if>

        </#if>
    </#list>

    <#--  JS SALVATAGGIO -->
    <!--
    EDITABLE: ${editable?string}<br/>
    CAN CREATE: ${templatePolicy.canCreate?string}<br/>
    CAN UPDATE: ${templatePolicy.canUpdate?string}<br/>
    -->
    <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
        <@script>
        <#--
        function enableSalvaForm_${template.name}(){
        $("[name=salvaForm-${template.name}]").on('click',function(){
        fzSalvaForm_${template.name}();
        });
        }
        -->

        function fzSalvaForm_${template.name}(alpacaJSON){
            var $form=$($("[name=salvaForm-${template.name}]").data('rel'));
            if($("[name=salvaForm-${template.name}]").attr('id')){
                var formName=$("[name=salvaForm-${template.name}]").attr('id').replace("salvaForm-", "");
            }else{
                formName="formNonEsistente"
            }

        $.each(alpacaJSON.options.fields, function(key, val){
            //alert(key);
            var $input=$form.find('#'+key);
            if ($input.is(':visible') && $input.val()==""){ //LUIGI:controllo di visibilità del padre del campo obbligatorio
                bootbox.alert("Il campo '"+val.label+"' deve essere compilato",function(){
                    setTimeout(function(){$input.focus();},0);
                });
                return false;
            }
        });

        if($('#metadataTemplate-'+formName+'-FORM div.has-error :visible').size()>0){ //if ($('div.alpaca-invalid :input').size()>0){ //VMAZZEO CRMSVENETO-51 23.01.2019
            alert("Compilare i campi obbligatori (in rosso)");
            return false;
        }
        var goon=true;
        if (eval("typeof "+formName+"Checks == 'function'")){
            eval("goon="+formName+"Checks()");
        }
        if (!goon) return false;
        loadingScreen("Salvataggio in corso...", "loading");

        try{
            if (typeof(empties[${el.type.id}])=="undefined"){
                empties[${el.type.id}] = {};
                empties[${el.type.id}].metadata = {};
                $.each(alpacaJSON.options.fields, function(key, val){
                    empties[${el.type.id}].metadata[key] = [];
                });
            }
            var myElement={};
            myElement.id=${el.id};
            myElement.type={};
            myElement.type.id=${el.type.id};
            myElement.type.typeId='${el.type.typeId}';
            //${el.type.id} //${el.type.typeId}
            myElement.metadata={};
            myElement=formToElementAlpaca($form,myElement,alpacaJSON);
            saveElementAlpaca(formName, myElement).done(function(data){
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
    }
    </@script>
<#--
        <div class="clearfix"></div>
        <button id="salvaForm-${template.name}" class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" >
            <i class="icon-save bigger-160" ></i><b>Salva</b>
        </button>
        </form>
-->
    </#if>
</#if>
<#if toClose >
</div>
</#if>
</#macro>

<#macro TemplateFormTableTypeAlpaca templateName type userDetails editable titleTable="" classes="" forceReload="false" forceEdit=false horizontalView=true >
    <#assign toClose=false />
    <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>

        <#assign groupActive=false />
        <#list type.associatedTemplates as assocTemplate>
            <#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
            <#if assocTemplate.enabled && templatePolicy.canCreate>

                <#assign template=assocTemplate.metadataTemplate/>
                <#--  --assign toClose=true /-->
                <div id="metadataTemplate-${template.name}" class="${classes}">
                    <div id="metadataTemplate-${template.name}-FORM">&nbsp;</div>
                </div>
                <#assign alpacaMode="" />
                <#--
                <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit) >
                    <#assign alpacaMode="editMode" />
                <#else>
                    <#assign alpacaMode="viewMode" />
                </#if>
                -->
                <@script>
                    if (alpacaJsons==undefined){
                        var alpacaJsons={};
                    }
                    var alpacaJSON_${templateName} = {};

                    $.ajax({
                        url: baseUrl+"/app/rest/documents/xml/${templateName}/alpaca", ///${alpacaMode}
                        type: "GET",
                        dataType: "json"

                    }).done(function(jsonData) {
                        //alert(jsonData);
                        $("#metadataTemplate-${template.name}-FORM").html("<div class='loading'><i class='fa fa-spin fa-spinner'></i> caricamento ...</div>");
                        alpacaJSON_${templateName} = jsonData;
                        alpacaJsons['${templateName}']=jsonData;
                        <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
                            jsonData.options["form"] = {
                                "buttons": {
                                    "submit": {
                                       "title": "<i class=\"icon-save bigger-160\"></i> Salva",
                                        "click": function() {
                                        fzSalvaForm_${template.name}(alpacaJSON_${templateName});
                                    },
                                    "id": "salvaForm-${template.name}",
                                    "attributes": {
                                        "class": "btn btn-warning",
                                        "name": "salvaForm-${template.name}",
                                        "data-rel": "#form-${template.name}"
                                    }
                                }
                            },
                            "toggleSubmitValidState": false
                            };

                            if (typeof(jsonData.postRenderFunction)!='undefined' && jsonData.postRenderFunction!=null){
                                jsonData.postRender = function(control){
                                    $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                    ( function(dsString){
                                        eval(dsString);
                                    })(jsonData.postRenderFunction);
                                    $('#metadataTemplate-${template.name}-FORM select option[value=""]').empty().append("[Seleziona...]");
                                    $("select").select2();
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').attr('data-date-format',"dd/mm/yyyy");
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').datepicker({autoclose:true,  format: 'dd/mm/yyyy', locale: 'it' });
                                    $("#metadataTemplate-${template.name}-FORM .alpaca-required-indicator").empty();
                                };
                            }else{
                                jsonData.postRender = function(control){
                                    $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                    $('#metadataTemplate-${template.name}-FORM select option[value=""]').empty().append("[Seleziona...]");
                                    $("select").select2();
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').attr('data-date-format',"dd/mm/yyyy");
                                    //$('#metadataTemplate-${template.name}-FORM .datePickerAlpaca input.form-control').datepicker({autoclose:true,  format: 'dd/mm/yyyy', locale: 'it' });
                                    $("#metadataTemplate-${template.name}-FORM .alpaca-required-indicator").empty();
                                };
                            }
                        <#else>
                            jsonData.postRender = function(control){
                                $("#metadataTemplate-${template.name}-FORM div.loading").remove();
                                //$("select").select2();
                                $("#metadataTemplate-${template.name}-FORM .alpaca-required-indicator").empty();
                            };
                        </#if>

                        <#if horizontalView>
                            //Visualizzazione orizzontale
                            jsonData.view.parent = jsonData.view.parent+"-horizontal";
                        </#if>

                        $.each(jsonData.options.fields, function(key, val){
                            if (typeof(val.dataSourceFunction)!='undefined' && val.dataSourceFunction!=null){
                                val.dataSource = function(callback){
                                    ( function(dsString){
                                        eval(dsString);
                                    })(val.dataSourceFunction);
                                };
                            }
                            if (val.type=="date"){

                                val["picker"]={
                                    "format": "DD/MM/YYYY",
                                    "locale": "it"
                                }
                                val["dateFormat"]="DD/MM/YYYY";
                                //val["maskString"]="DD/MM/YYYY";
                                //val["fieldClass"]+= " datePickerAlpaca ";
                            }
                            if (val.type=="select"){
                                val["removeDefaultNone"]=false;
                            }
                            if (val.type=="select" || val.type=="radio" || val.type=="checkbox"){
                                val["emptySelectFirst"]=false;
                            }
                        });
                        $("#metadataTemplate-${template.name}-FORM").alpaca(jsonData);
                        <#--if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
                            enableSalvaForm_${template.name}();
                        </#if-->

                    });
                </@script>
            </#if>



            <#--  JS SALVATAGGIO -->
            <!--
            EDITABLE: ${editable?string}<br/>
            CAN CREATE: ${templatePolicy.canCreate?string}<br/>
            CAN UPDATE: ${templatePolicy.canUpdate?string}<br/>
            -->
            <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
                <@script>
                    <#--
                    function enableSalvaForm_${template.name}(){
                    $("[name=salvaForm-${template.name}]").on('click',function(){
                    fzSalvaForm_${template.name}();
                    });
                    }
                    -->

                    function fzSalvaForm_${template.name}(alpacaJSON){
                        var $form=$($("[name=salvaForm-${template.name}]").data('rel'));
                        if($("[name=salvaForm-${template.name}]").attr('id')){
                            var formName=$("[name=salvaForm-${template.name}]").attr('id').replace("salvaForm-", "");
                        }else{
                            formName="formNonEsistente"
                        }

                        $.each(alpacaJSON.options.fields, function(key, val){
                            //alert(key);
                            var $input=$form.find('#'+key);
                            if ($input.is(':visible') && $input.val()==""){ //LUIGI:controllo di visibilità del padre del campo obbligatorio
                                bootbox.alert("Il campo '"+val.label+"' deve essere compilato",function(){
                                    setTimeout(function(){$input.focus();},0);
                                });
                                return false;
                            }
                        });

                        if($('div.has-error :visible').size()>0){ //if ($('div.alpaca-invalid :input').size()>0){ //VMAZZEO CRMSVENETO-51 23.01.2019
                            alert("Compilare i campi obbligatori (in rosso)");
                            return false;
                        }

                        var goon=true;
                        if (eval("typeof "+formName+"Checks == 'function'")){
                            eval("goon="+formName+"Checks()");
                        }
                        if (!goon) return false;
                        loadingScreen("Salvataggio in corso...", "loading");

                        // TODO: VERIFICARE QUA!

                        try{
                            var myElement={};
                            //myElement.id=loadedElement.id;
                            myElement.type=type;
                            myElement.metadata={};
                            myElement=formToElementAlpaca($form,myElement,alpacaJSON);
                            saveElementAlpaca(formName, myElement).done(function(data){
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
                    }
                </@script>
                <#--
                <div class="clearfix"></div>
                <button id="salvaForm-${template.name}" class="btn btn-warning" name="salvaForm-${template.name}" data-rel="#form-${template.name}" >
                    <i class="icon-save bigger-160" ></i><b>Salva</b>
                </button>
                </form>
                -->
            </#if>
        </#list>
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





<#macro selectHashNoLabelPlusMultiple id name label values={} value=[] editable=true>
<#assign selectedCodes=[]/>
<#assign selectedDecodes=[]/>
<#assign htmlId=id/>

<#if value?? && value?is_enumerable >
	<#list value as val>
		<#if val?? && val?contains("###")>
			<#assign selectedCodes=selectedCodes + [val?split("###")[0]]/>
			<#assign selectedDecodes=selectedDecodes + [val?split("###")[1]]/>
		</#if>
	</#list>
</#if>
<#if editable>

	<@script>		
	$('#s2id_${htmlId} ul li input').css('min-width','200px');		
	</@script>
	
	<div class="col-sm-9">
		<select id="${htmlId}" name="${htmlId}" <#if !editable>disabled="disabled"</#if> multiple="multiple">
			<!--option></option-->
			<#assign keys = values?keys>
			<#list keys as key>
				<option value="${key?html}###${values[key]?html}"
					<#list selectedCodes as selectedCode>
					<#if key?split("###")[0]==selectedCode>selected</#if>
					</#list> 
				>
				${values[key]}
				</option>
			</#list>
		</select>
		<span class="ui-state-error ui-corner-all" id='alert-${id}' style="display:none">
			<span class="ui-icon ui-icon-alert" style="float: left; margin-right: .3em;"></span>
			<span id="alert-msg-${id}"></span>
		</span>
	</div>
<#else>
	<#list selectedDecodes as selectedDecode>
		<span class="field-view-mode field-select" id="${id}">${selectedDecode}</span>
	</#list>
</#if>
</#macro>




<#macro selectHashPlusMultiple id name label values={} value=[] noLabel=false fieldDef={} editable=true>
<label class="col-sm-3 control-label no-padding-right" for="${id}">${label}:</label>
<@selectHashNoLabelPlusMultiple id name label values value editable/>
</#macro>

