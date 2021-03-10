<#include "../helpers/MetadataTemplate.ftl"/>
<#assign editable=false/>
<@script>
    $('#attachFile-form-submit').click(function(){
    	<#if elType.hasFileAttached>
			        if ($('#file').val()==""){
			        	alert("Bisogna allegare un file");
			        	$('#file').focus();
    					return false;
			        }
			        <#if !elType.noFileinfo>
			        if ($('#version').val()==""){
			        	alert("Il campo versione deve essere compilato");
    					$('#version').focus();
    					return false;
			        }
			        if ($('#data').val()==""){
			        	alert("Il campo data deve essere compilato");
    					$('#data').focus();
    					return false;
			        }
			        </#if>
		</#if>
        loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
        var formData=new FormData($('#attachFile-form')[0]);
        var actionUrl=$('#attachFile-form').attr("action");
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
                    if ($('#container:checked').size()>0) $('#isContainer').show();
                    else $('#isContainer').hide();
                    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                    if (obj.redirect){
                        //window.location.href=obj.redirect;
                        window.location.href='${baseUrl}/app/documents/detail/${el.getParent().getId()}<#if model['docDefinition'].hashBack?? >#${model['docDefinition'].hashBack}</#if>';
                    }
                }else {
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

    });
    $( "#attachFile-dialog" ).dialog({
        autoOpen: false,
        height: 400,
        width: 800,
        modal: true,
        buttons: {
            Cancel: function() {
                $( this ).dialog( "close" );
            }
        },
        close: function() {
        }
    });
    $('#attachFile-form-showDialog').click(function(){
    	$( "#attachFile-dialog").dialog( "open" );
    });
    <#if elType.typeId=="AllegatoCentro">
$('#checklist tr:last').after('<tr><td><span style="color:white">Dati Protocollo: </span><b>Fascicolo:</b></td> <td><b>${el.getParent().getFieldDataString("IdCentro","ProtocolloFascicolo")?string}</b></td></tr>');
    </#if>
</@script>
<#if elType.hasFileAttached>
<fieldset>
    <legend>File allegato</legend>
    <div id="task-Actions" style="text-align: right;margin:10px"></div>
    <#if elType.enabledTemplates?? && elType.enabledTemplates?size gt 0>
	    <#list el.templates as template>
	    	<#assign titolo> <@msg "template.${template.name}"/> </#assign>
	      <@TemplateFormTable template.name el userDetails editable titolo />
	    </#list>
		</#if>
    
    
    <#if el.file??>
        <div id="attachedFile-list-availables">

        </div>

        <div class="well">
         <a class="download-img" href="${baseUrl}/app/documents/getAttach/${el.id}" title="Download" style="
         float:left;
         padding:5px;
         ">
            <i class="icon-cloud-download icon-4x"></i> 
        </a>
        
        <#if el.locked && el.lockedFromUser!=userDetails.username><img src="${baseUrl}/int/images/lock.png" width="21px"/></#if>
        <#if !el.locked && el.type.checkOutEnabled && userPolicy.canUpdate>
       		<a href="#" class="actions-link checkOut"><img src="${baseUrl}/int/images/checkout.png" width=18px/>&nbsp;<@msg "actions.doCheckOut"/></a><br/>
   		  </#if>
		    <#if el.locked && el.type.checkOutEnabled && userPolicy.canUpdate && el.lockedFromUser==userDetails.username>
		    	<a href="#" class="actions-link checkIn"><img src="${baseUrl}/int/images/checkin.png" width=18px/>&nbsp;<@msg "actions.doCheckIn"/></a><br/>
		    <#else>
		    	<#if el.locked && el.type.checkOutEnabled && userPolicy.canRemoveCheckOut>
		      	<a href="#" class="actions-link checkIn"><img src="${baseUrl}/int/images/checkin.png" width=18px/>&nbsp;<@msg "actions.forceCheckIn"/></a><br/>
		      </#if>
		    </#if>
        
        <br/>
        
        
        
        
        File:<b>
        <#if el.file.fileName?length gt 30>
        ${el.file.fileName?substring(0,23)}(...).${el.file.fileName?split(".")?last}
        <#else>
        ${el.file.fileName}
        </#if></b>
       
        <br/>
            Dimensioni:<b>${el.file.size} Kb</b><br/>
            Caricato il: <b>${el.file.uploadDt.time?date?string.short}</b><br/>
            inserito da: <b>${el.file.uploadUser}</b><br/>
            <#if el.file?? && ! elType.noFileinfo>
		        Autore: <b>${el.file.autore!""}</b><br/>
		        Versione: <b>
		        <#--
		        Modifica versioning per CTC gemelli CRPMS-156:
		        ${el.file.version!""}
		        -->
		        <#--
		        <#assign currVersion=el.auditFiles?size+1/>
		        ${currVersion!""}
		        -->
		        ${el.file.version!""}
		        </b><br/>
		        <#if el.file.date??>
		        Data documento: <b>${el.file.date.time?date?string.long}</b><br/>
		        </#if>
		        Note: <b>${el.file.note!""}</b><br>
        	</#if>
        </div>
        <#if el.auditFiles?size gt 0>
        	<#--assign prevVersion=currVersion-1/-->
        	<a href="#" onclick="if (document.getElementById('oldVersion-files').style.display=='none') $('#oldVersion-files').show();else $('#oldVersion-files').hide(); return false">
        	<i class="icon-time"></i> Mostra/nascondi versioni precedenti</a><br/>
        	<fieldset id="oldVersion-files" style="display:none">
			 <div>
				<h4 class="blue"><i class="icon-time icon-large"></i> Versioni precedenti</h4>
			
	        	<#list el.auditFiles as oldVersions>
	        	<div class="well">
		        	<a href="${baseUrl}/app/documents/getAttach/old/${oldVersions.id}" style="
		        	float:left;
		        	padding:5px;
		        	">
			           <i class="icon-cloud-download icon-4x"></i> 
			        </a>
			        <div id="attachedFile-list-availables">
			
			        </div>
			        <span>
			            File:<b>
			        <#if oldVersions.fileName?length gt 30>
			        ${oldVersions.fileName?substring(0,23)}(...).${el.file.fileName?split(".")?last}
			        <#else>
			        ${oldVersions.fileName}
			        </#if></b><br/>
		        	Dimensioni: <b>${oldVersions.size} Kb</b><br/>
		            Caricato il: <b>${oldVersions.uploadDt.time?date?string.short}</b><br/>
		            inserito da: <b>${oldVersions.uploadUser}</b><br/>
		            <#if el.file?? && ! elType.noFileinfo>
				        Autore: <b>${oldVersions.autore!""}</b><br/>
				        Versione: <b>${oldVersions.version!""}</b><br/>
				        <#if el.file.date??>
				        Data documento: <b>${oldVersions.date.time?date?string.long}</b><br/>
				        </#if>
				        Note: <b>${oldVersions.note!""}</b><br>
		        	</#if>
		         </div>
	        </#list>
	</fieldset>
        </#if>
       
    <#else>
    </#if>
    <#if elType.typeId!="AllegatoCentro" || (elType.typeId=="AllegatoCentro" && el.getFieldDataString("DocCentroSpec","ProtocolloNumero")?string=="") >
    <#if (userPolicy.canUpdate && !el.locked) || (userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username)>
     <button class="submitButton btn btn-primary" type="button" id="attachFile-form-showDialog" name="document-form-submit">
            <i class="icon-cloud-upload"></i> Carica nuova versione
            </button><br/>
   
    <div id="attachFile-dialog" title="Carica nuova versione">
    <form id="attachFile-form" method="POST" action="${baseUrl}/app/rest/documents/${el.id}/attach" enctype="multipart/form-data">
        <#if ! elType.noFileinfo>
        
        
        <div class="field-component" id="version-div">
            <label for="version">Versione:</label>
            <input type="text" name="version" id="version"/>
        </div>
        <#--
        <input type="hidden" name="version" value="auto"/>
        -->
        
        <div class="field-component" id="data-div">
            <label for="data">Data:</label><input type="text" name="data" class="datePicker" id="data"/>
            <@script>
            	$('#data').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
            </@script>
        </div>
        <div class="field-component" id="comment-div">
            <label for="autore">Autore:</label><input type="text" name="autore" id="autore"/><br/>
        </div>
        <div class="field-component" id="note-div">
            <label for="note">Note:</label><textarea name="note" id="note"></textarea><br/>
        </div>
        </#if>
        <div class="field-component">
        <@fileChooser "file" "file" getLabel(elType.typeId+".fileLabel")/>
        </div>
            <button class="submitButton btn btn-primary" type="button" id="attachFile-form-submit" name="document-form-submit">
            <i class="icon-cloud-upload"></i> Carica file
            </button><br/>
        </div>
    </form>
    </div>
    </#if>
    </#if>
</fieldset>

</#if>

<#--include "../helpers/comments.ftl"/-->