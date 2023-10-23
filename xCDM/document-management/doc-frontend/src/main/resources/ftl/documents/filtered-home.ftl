<script>

    var file=null;
    $(document).ready(function(){
        jQuery.event.props.push('dataTransfer');

        var filedrag = $("#child-box");

        var xhr = new XMLHttpRequest();
        if (xhr.upload) {

            filedrag.bind("dragover", function(e){
                e.stopPropagation();
                e.preventDefault();
                $('#child-box').css("background-color", "#ECF6FD");
            });
            filedrag.bind("dragleave", function(e){
                e.stopPropagation();
                e.preventDefault();
                $('#child-box').css("background-color", "white");
            });
            filedrag.bind("drop", function(e){
                e.stopPropagation();
                e.preventDefault();
                var files = e.target.files || e.dataTransfer.files;
                if (files.length>1) {
                	alert("Caricare un file per volta");
                	return;
                	}
                for (var i = 0, f; f = files[i]; i++) {
                    file=f;
                    console.log(f);
                    $('#droppedFile-Form').dialog('open');
                }
            });

        }

        $('#droppedFile-Form').dialog({
            height: 300,
            width: 300,
            modal: true,
            autoOpen: false
        });

        $('#droppedFile-Form #droppedFile-type').change(function(){
            $('#droppedFile-Form').dialog('close');
            $('#'+$(this).val()+'-dialog').dialog('open');
        });

    <#list model['getCreatableRootElementTypes'] as docType>
        <#if docType.hasFileAttached>
            $('#${docType.typeId}-dialog').dialog({
                height: 300,
                width: 600,
                modal: true,
                autoOpen: false
            });
        $('#${docType.typeId}-form-submit').click(function(){
            var formData=new FormData($('#${docType.typeId}-form')[0]);
            var actionUrl=$('#${docType.typeId}-form').attr("action");
            formData.append("file", file);
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
                        loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                        if (obj.redirect){
                            window.location.href=obj.redirect;
                        }
                    }else {
                        console.log("sono qui myXhr");
                        loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    }
                },
                error: function(){
                    console.log("sono qui myXhr");
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            });
            $('#child-box').css("background-color", "white");
        });
        </#if>
    </#list>

    });

</script>


<#list model['getCreatableRootElementTypes'] as docType>
    <#if docType.hasFileAttached>
    <div id="${docType.typeId}-dialog" title="Nuovo ${docType.typeId}">
        <form id="${docType.typeId}-form" method="POST" action="${baseUrl}/app/rest/documents/save/${docType.id}" enctype="multipart/form-data">
            <#if docType.enabledTemplates?? && docType.enabledTemplates?size gt 0>
                <#list docType.enabledTemplates as template>
                    <#if template.fields??>
                        <#list template.fields as field>
                            <@mdfield template field/>
                        </#list>
                    </#if>
                </#list>
            </#if>

            <input class="submitButton round-button blue" type="button" value="Salva" id="${docType.typeId}-form-submit" name="${docType.typeId}-form-submit"/>

        </form>
    </div>
    </#if>
</#list>


<div id="droppedFile-Form" title="Selezionare il tipo di documento">
    <div class="field-component">
        <select id="droppedFile-type">
            <option>Selezionare il tipo di documento</option>
            <#list model['getCreatableRootElementTypes'] as docType>
                <#if docType.hasFileAttached>
                <option value="${docType.typeId}"><@msg "type.${docType.typeId}"/></option>
                </#if>
            </#list>
        </select>
    </div>
</div>

<div class="mainContent">
 <div>
        <span class="dropdown-anchor" data-dropdown="#dropdown-1"><@msg "actions.addNewElement"/></span>
            <div id="dropdown-1" class="dropdown dropdown-tip">
                <ul class="dropdown-menu">
                <#list model['getCreatableRootElementTypes'] as docType>
                    <li><a href="${baseUrl}/app/documents/new/${docType.id}">
                        <#assign icon=docType.getImageBase64()/>
                        <#if icon=="">
                            <#assign icon=baseUrl+"/int/images/document_blank.png"/>
                        </#if>
                        <img src="${icon}" width="14px">&nbsp;<@msg "type.${docType.typeId}"/></a></li>
                </#list>
                </ul>
            </div>
        </div>
<div class="documentMainContent">
    <fieldset id="child-box" class="child-box">
        <legend>Elementi presenti</legend>
        <#if model['getCreatableRootElementTypes']?? && model['getCreatableRootElementTypes']?size gt 0>
       
        </#if>
        <br/>
        <#if model['rootElements']??>
        <table class="pSchema-2">
	<tr>
		<th>&nbsp;</th>
		<th>Titolo</th>
		<th>Data creazione</th>
		<th>Data ultima modifica</th>
	</tr>
<#list model['rootElements'] as element>
    <#include "helpers/element.ftl"/>
</#list>
</table>
</#if>
<#assign totalPages=(model['numChilds']/model['rpp'])?ceiling/>
	<@pages totalPages model['page']/>
    </fieldset>
</div>
    <#assign allElements=true/>
    <#include "helpers/events.ftl"/>
</div>