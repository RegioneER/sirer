<script>


    $(document).ready(function(){
        $('#attachFile-form-submit').click(function(){
            $('#file').click();
        });
        $('#file').on("change",function(){
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
        $( "#attachFile-dialog" ).dialog({
            autoOpen: false,
            height: height,
            width: width,
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
    });



</script>
<#if elType.hasFileAttached>
<fieldset>
    <legend>File allegato</legend>
    <#if el.file??>
        <a class="download-img" href="${baseUrl}/app/documents/getAttach/${el.id}">
            <img src="${baseUrl}/int/images/download.jpg" width="48px"/>
        </a>
        <div id="attachedFile-list-availables">

        </div>
        <span class="attached-file" title="${el.file.fileName}">
            File:<b>
        <#if el.file.fileName?length gt 30>
        ${el.file.fileName?substring(0,23)}(...).${el.file.fileName?split(".")?last}
        <#else>
        ${el.file.fileName}
        </#if></b><br/>
            Dimensioni:<b>${el.file.size} Kb</b><br/>
            <b>${el.file.uploadDt.time?datetime?string.full}</b><br/>
            inserito da: <b>${el.file.uploadUser}</b>
        </span>
        <br/>Autore:<b>${el.file.autore}
        <br/>Versione:<b>${el.file.version}
        <br/>Data:<b>${el.file.date.time?datetime?string.full}
        <br/>Note:<b>${el.file.note}
    <#else>
    </#if>
    <#if (userPolicy.canUpdate && !el.locked) || (userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username)>
    <input class="submitButton round-button blue" type="button" value="Carica nuova versione ..." id="attachFile-form-showDialog" name="document-form-submit"/><br/>

    <div id="attachFile-dialog" title="Carica nuova versione">
    <form id="attachFile-form" method="POST" action="${baseUrl}/app/rest/documents/${el.id}/attach" enctype="multipart/form-data">
        <div class="field-component">
            Versione:<input type="text" name="version" id="version"/><br/>
            Data:<input type="text" name="data" class="datePicker hasDatepicker" id="data"/><br/>
            <script>
            $(document).ready(function(){
            	$('#data').datepicker({ dateFormat: 'dd/mm/yy' });
            });
            </script>
            Autore:<input type="text" name="autore" id="autore"/><br/>
            Note:<textarea name="note" id="note"></textarea><br/>
            File:<input type="file" name="file" id="file"/>
            <@fileChooser "file" "file" "File allegato"/>"/>
            <input class="submitButton round-button blue" type="button" value="Carica file" id="attachFile-form-submit" name="document-form-submit"/><br/>
        </div>
    </form>
    </div>
    </#if>
</fieldset>
</#if>
