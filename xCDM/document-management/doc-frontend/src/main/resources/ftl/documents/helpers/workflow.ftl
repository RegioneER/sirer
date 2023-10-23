<script>
    $(document).ready(function(){
    	$( ".flow-dialog" ).dialog({
            autoOpen: false,
            height: 500,
            width: 500,
            modal: true,
            buttons: {
                Cancel: function() {
                    $( this ).dialog( "close" );
                }
            },
            close: function() {
            }
        });

        $('.followFlow').button().click(function( event ) {
            event.preventDefault();
            flowId=$(this).attr("action");
            $( "#flow-"+flowId+"-dialog" ).dialog( "open" );
        });

        $('.flowSendClass').click(function(){
            loadingScreen("Invio richiesta...", "${baseUrl}/int/images/process-start-icon.png");
            flowId=$(this).attr("action");
            processInstanceId=$(this).attr("instanceId");
            var formData=new FormData($('#flow-'+flowId+'-form')[0]);
            $.ajax({
                type: "POST",
                url: "${baseUrl}/app/rest/documents/followFlow/${el.id}/"+processInstanceId+"/"+flowId,
                contentType:false,
                processData:false,
                async:false,
                cache:false,
                data: formData,
                success: function(obj){
                    if (obj.result=="OK") {
                        loadingScreen("Richiesta effettuata", "${baseUrl}/int/images/green_check.jpg",2000);
                        $( "#flow-"+flowId+"-dialog" ).dialog( "close" );
                        if (obj.redirect){
                            window.location.href=obj.redirect;
                        }
                    }else {
                        loadingScreen("Errore!", "${baseUrl}/int/images/alerta.gif", 3000);
                        $("#flow-"+flowId+"-dialog" ).dialog( "close" );
                    }
                },
                error: function(){
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                    $("#flow-"+flowId+"-dialog" ).dialog( "close" );
                }
            });
        });

    });
</script>

<fieldset>
    <legend>Processi</legend>
    
    <h2>Processi in corso</h2>
    <#assign activeProcess=false/>
    <#if model["activeProcesses"]??>
        <#list model["activeProcesses"] as ist>
        <#assign activeProcess=true/>
          	Processo <b>${ist.id}</b>
          	<img src="${baseUrl}/process-engine/runtime/process-instances/${ist.processInstanceId}/diagram" width="300px"/>
        </#list>
    </#if>
    <#if model["terminatedProcesses"]??>
	<h2>Storico processi</h2>
    <ul>    
    <#list model["terminatedProcesses"] as ist>
                       <li> Processo <b>${ist.id}</b></li>
        </#list>
        </ul>
    </#if>
    
   
    


</fieldset>