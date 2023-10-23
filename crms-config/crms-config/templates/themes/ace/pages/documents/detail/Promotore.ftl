    <#--include "../helpers/title.ftl"/-->
        <div style="display: block">
            <div style="float: right">
            <#include "../helpers/attached-file.ftl"/>
        </div>

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

    <#macro TemplateForm templateName el userDetails editable classes="" forceEdit=false >
    <#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#assign groupActive=false />
    <#list el.elementTemplates as elementTemplate>
    <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
    <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    <#assign template=elementTemplate.metadataTemplate/>
    <div id="metadataTemplate-${template.name}" class="${classes}">
        <#if editable && (templatePolicy.canCreate || templatePolicy.canUpdate || forceEdit)>
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
    <div class="col-sm-12 field-component <#if fieldEditable>edit-mode<#else>view-mode</#if>" id="informations-${id}">
        <label class="col-sm-3 control-label no-padding-right" for="${id}">${label}<#if field.mandatory><sup style="color:red">*</sup></#if>:</label>
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
    <@script>
    $("[name=salvaForm-${template.name}]").on('click',function(){
    var $form=$($(this).data('rel'));
    //QUESTO E' IL CODICE DI METADATATEMPLATE.FTL
    var nomeTemp = "METADATATEMPLATE.FTL";
    if($(this).attr('id')){
    var formName=$(this).attr('id').replace("salvaForm-", "");
    }else{formName="formNonEsistente"}
    <#list template.fields as field>
    <#if field.mandatory>
    <#assign label=getLabel(template.name+"."+field.name)/>
    var $input=$form.find('#${template.name}_${field.name}');
    if ($input.is(':visible') && $input.val()==""){
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
    <#assign myElJson=el.getElementCoreJsonToString(userDetails) /> <#-- SIRER-60 trovato bug su loadedElement -->
    var myEl=${myElJson};
    if (!jQuery.isEmptyObject(myEl)){
    myElement=myEl;
    }
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


    window.location.href="/acm/?/dizionari/list/${model['docDefinition'].typeId}";

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
    </div>
    </#if>
    </#list>
    </#if>
    </#macro>

    <#macro SingleFieldLabel templateName fieldName mandatory=false >
    <#assign id=templateName+"_"+fieldName/>
    <#assign label=messages[templateName+"."+fieldName]!templateName+"."+fieldName/>
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

    <#macro TemplateFormFastUpdate templateName el userDetails editable forceEdit=false useDataName=false >

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
        <#assign fieldEditable=(forceEdit || (editable && templatePolicy.canUpdate))/>
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
    <!-- PASSO DI QUA EDITABLE FAST UPDATE -->
    <@mdFieldDetail template field vals fieldEditable audit true el.id useDataName />
    <div id="${id}-afterdiv-${el.id}"></div>
    <#else>
    <!-- PASSO DI QUA NON EDITABLE FAST UPDATE-->
    <@mdFieldDetail template field vals false audit true el.id useDataName />
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


    <#macro SingleFieldTd templateName fieldName el userDetails editable forceEdit=false>
    <#if el.elementTemplates?? && el.elementTemplates?size gt 0>
    <#list el.elementTemplates as elementTemplate>
    <#if elementTemplate.metadataTemplate.name=templateName && elementTemplate.enabled && templatePolicy.canView>
    <#assign templatePolicy=elementTemplate.getUserPolicy(userDetails, el)/>
    <#assign template=elementTemplate.metadataTemplate/>
    <#list template.fields as field>
    <#if field.name=fieldName>
    <#assign vals=[]/>
    <#assign fieldEditable=(editable && (templatePolicy.canCreate || forceEdit) )/>
    <#list el.data as data>

    <#assign fieldEditable=(editable && (templatePolicy.canUpdate || forceEdit) )/>
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
            <div class="field-component view-mode editable" >
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
            <#assign editable=false/>
            <#if userPolicy.canUpdate && !el.locked>
            <#assign editable=true/>
        </#if>
    <#if userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username>
    <#assign editable=true/>
    </#if>
    <@script>

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
    return field.find('option:selected').text();
    }else {
    return field.val();
    }
    }

    function DateFmt(fstr) {
    this.formatString = fstr

    var mthNames = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
    var dayNames = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
    var zeroPad = function(number) {
    return ("0"+number).substr(-2,2);
    }

    var twoDigit= function(string){
    return (string+'').substr(2,2);
    }

    var dateMarkers = {
    d:['getDate',function(v) { return zeroPad(v)}],
    m:['getMonth',function(v) { return zeroPad(v+1)}],
    n:['getMonth',function(v) { return mthNames[v]; }],
    w:['getDay',function(v) { return dayNames[v]; }],
    y:['getFullYear',function(v) { return twoDigit(v)}],
    H:['getHours',function(v) { return zeroPad(v)}],
    M:['getMinutes',function(v) { return zeroPad(v)}],
    S:['getSeconds',function(v) { return zeroPad(v)}],
    i:['toISOString']
    };

    this.format = function(date) {
    var dateTxt = this.formatString.replace(/%(.)/g, function(m, p) {
    var rv = date[(dateMarkers[p])[0]]()

    if ( dateMarkers[p][1] != null ) rv = dateMarkers[p][1](rv)

    return rv

    });

    return dateTxt
    }

    }



    function saveUpdateField(idField){
    loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
    form=document.forms[idField];
    var formData=new FormData(form);
    var actionUrl=$(form).attr("action")+"${el.id}";
    field=$(form).find('#'+idField);
    var newValue=field.val();
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
    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",1000);
    if (field.attr('istokeninput')=='true'){
    value=field.tokenInput("get");
    console.log(value[0].name);
    if (fieldTypes[idField]=="ELEMENT_LINK")
    $('#'+idField+'_value').html("<a href='${baseUrl}/app/documents/detail/"+value[0].id+"'>"+value[0].name+"</a>");
    else $('#'+idField+'_value').html(value[0].name);
    }else if (field.attr('type')=='radio'){
    $('#'+idField+'_value').html($('#'+idField+':checked').attr('title'));
    }else if (field.prop('tagName')=='SELECT'){
    $('#'+idField+'_value').html(field.find('option:selected').text());
    }else {
    $('#'+idField+'_value').html(field.val());
    }
    if ($('#'+idField+'_audit')){
    auditTBody=$('#'+idField+'-audit-table');
    fmt = new DateFmt("%d/%m/%y %H.%M");
    auditTBody.append(' <tr><td>${userDetails.username}</td><td>'+fmt.format(new Date())+'</td><td>update</td><td>'+origValue+'</td><td>'+newValue+'</td></tr>');
    }
    }else{
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
    $('#'+idField).show();
    $('#form-'+idField).hide();
    }

    function onMouseOverEditable(obj){
    $(obj).addClass("editable-field");
    $(obj).find('.right-corner').show();

    }

    function onMouseOutEditable(obj){
    $(obj).removeClass("editable-field");
    $(obj).find('.right-corner').hide();
    }

    var origValue=null;


    <#if editable>
    $('.right-corner').hide();
    $('.save-buttons').button({
    icons: {
    primary: "ui-icon-check"
    },
    text: false});
    $('.cancel-buttons').button({
    icons: {
    primary: "ui-icon-cancel"
    },
    text: false});
    $('.cancel-buttons').click(function(){
    $('.view-mode').show();
    $('.edit-mode').hide();
    });


    </#if>


    </@script>

    <#if infoPanel=="main">
    <fieldset id="child-box" class="child-box">
        <#else>
        <fieldset style="width:60%">
        </#if>

        <#assign label="type."+elType.getTypeId() />
        <legend><@msg label /></legend>
        <div class="form-horizontal" >
            <#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
            <#list el.templates as template>
            <@TemplateForm template.name el userDetails editable />
        </#list>
    </#if>
    </div>
    <br>
    <#-- Vecchio fastupdate
    <h2 class="blue"><i class="icon-info-sign icon-large"></i>
        Informazioni<#if el.locked && el.lockedFromUser!=userDetails.username><img src="${baseUrl}/int/images/lock.png" width="36px"/></#if>
    </h2>
    <#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
    <#list el.templates as template>
    <#if template.fields??>
    <@TemplateFormFastUpdate template.name el userDetails true />
    </#if>
    </#list>
    </#if>
    -->
    </fieldset>

    </div>
    <#--include "../helpers/comments.ftl"/-->
    <#--include "../helpers/events.ftl"/-->
