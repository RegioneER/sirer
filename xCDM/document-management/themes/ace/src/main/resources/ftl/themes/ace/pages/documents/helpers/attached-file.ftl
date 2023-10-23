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
                        window.location.href=obj.redirect;
                    }
                }else {
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            },
            error: function(){
                loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        });

    });
    
    $('.attachFile-form-showDialog').click(function(){
    	$( "#attachFile-dialog").modal();
    });
</@script>
<#if elType.hasFileAttached>
	<#assign elementModal>
	   <form id="attachFile-form" class="form-horizontal" method="POST" action="${baseUrl}/app/rest/documents/${el.id}/attach" enctype="multipart/form-data">
        <#if ! elType.noFileinfo>
        <div class="field-component form-group" id="version-div">
            <label for="version">Versione:</label>
            <input type="text" name="version" id="version"/>
        </div>
        <div class="field-component form-group" id="data-div">
            <label for="data">Data:</label><input type="text" name="data" class="datePicker" id="data"/>
            <@script>
            	$('#data').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
            </@script>
        </div>
        <div class="field-component form-group" id="comment-div">
            <label for="autore">Autore:</label><input type="text" name="autore" id="autore"/><br/>
        </div>
        <div class="field-component form-group" id="note-div">
            <label for="note">Note:</label><textarea name="note" id="note"></textarea><br/>
        </div>
        </#if>
        <div class="field-component form-group">
        <#assign label>
        <@msg model['docDefinition'].typeId+".fileLabel" /> <sup style='color:red'>*</sup>
        </#assign>
        <@fileChooser "file" "file" label />
        </div>
        <div class="form-group">
            <button class="submitButton btn btn-primary" type="button" id="attachFile-form-submit" name="document-form-submit">
            <i class="icon-cloud-upload"></i> Carica file
            </button>
            <button class="btn" type="reset" id="attachFile-form-cancel" name="document-form-submit" onclick="$('#attachFile-dialog').modal('hide');">
            <i class="fa fa-reply"></i> Annulla
            </button>
        </div>
    </form>
	</#assign>

	<@modalbox "attachFile-dialog" "Carica nuova versione del file" elementModal/>

    </#if>
<div class="widget-box">
	<div class="widget-header">
		<h4>File</h4>
		<div class="widget-toolbar info">
			<a href="#" class="attachFile-form-showDialog">
				<i class="icon-cloud-upload"></i> Upload
			</a>
		</div>
	</div>
	<div class="widget-body">
		<div class="widget-main">
				
		<#if el.file?? &&  el.file.fileName??>
    		<a class="download-img" href="${baseUrl}/app/documents/getAttach/${el.id}" title="Download" style="float:left;padding-right:5px;">
            <i class="icon-cloud-download icon-4x"></i> 
        </a>
        File:<strong>
        <#if el.file.fileName?length gt 30>
        ${el.file.fileName?substring(0,23)}(...).${el.file.fileName?split(".")?last}
        <#else>
        ${el.file.fileName}
        </#if></strong>
        <br/>
            Dimensioni:<strong>${el.file.size} Kb</strong><br/>
            Caricato il:<strong>${el.file.uploadDt.time?date?string.short}</strong><br/>
            inserito da:<strong>${el.file.uploadUser}</strong>
            <#if el.file?? && ! elType.noFileinfo>
            	<br/>
		        Autore: <b>${el.file.autore!""}</b><br/>
		        Versione: <b>${el.file.version!""}</b><br/>
		        <#if el.file.date??>
		        Data documento: <b>${el.file.date.time?date?string.long}</b><br/>
		        </#if>
		        Note: <b>${el.file.note!""}</b><br>
        	</#if>
    	</#if>
    	
    	<#if (userPolicy.canUpdate && !el.locked) || (userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username)>
	     	<button class="submitButton btn btn-xs btn-primary attachFile-form-showDialog" type="button" name="document-form-submit">
	            <i class="icon-cloud-upload"></i> 
				<#if el.file?? &&  el.file.fileName??>
	     				Carica nuova versione
	     		<#else>
	     				Carica un file
	     		</#if>
		     </button>
		     
		</#if>
		
		<#if el.auditFiles?size gt 0>
        	<a href="#" onclick="$('#oldVersion-files').modal();return false;">
        	<i class="icon-time"></i> Mostra versioni precedenti</a><br/>
			<#assign fileHistory>        	
			 <div>
				
			
	        	<#list el.auditFiles as oldVersions>
	        	<div class="well">
		        	<a href="${baseUrl}/app/documents/getAttach/old/${oldVersions.id}" style="
		        	float:left;
		        	padding:5px;
		        	">
			           <i class="icon-cloud-download icon-4x"></i> 
			        </a>
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
				        Versione: <b>
				        ${el.file.version!""}
					    </b><br/>
					    <#if el.file.date??>
				        Data documento: <b>${oldVersions.date.time?date?string.long}</b><br/>
				        </#if>
				        Note: <b>${oldVersions.note!""}</b><br>
		        	</#if>
		         </div>
	        </#list>
			</div>
			</#assign>
			
			<@modalbox "oldVersion-files" "<h4 class=\"blue\"><i class=\"icon-time icon-large\"></i> Versioni precedenti</h4>" fileHistory/>
			
        </#if>
    		
		</div>
	</div>
</div>
