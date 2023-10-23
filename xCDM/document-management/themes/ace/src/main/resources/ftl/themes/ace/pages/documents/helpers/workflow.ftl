<@script>
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
        
        var processStory=new Object();
        
        function getActiveProcessStory(pid){
        	processStory[pid]=new Object();
        	$.getJSON("${baseUrl}/process-engine/history/historic-process-instances/"+pid, function(data){
        		console.log(data);
        		processStory[pid]['pdata']=data;
        	});
        	$.getJSON("${baseUrl}/process-engine/history/historic-task-instances?processInstanceId="+pid, function(data){
        		console.log(data);
        		processStory[pid]['tdata']=data;
        	});
        	renderProcess(pid);
        }
        
    function dateFormat(d){
        return ("0" + d.getDate()).slice(-2) + "-" + ("0"+(d.getMonth()+1)).slice(-2) + "-" +
    d.getFullYear() + " " + ("0" + d.getHours()).slice(-2) + ":" + ("0" + d.getMinutes()).slice(-2);
    }
        
        
        function renderProcess(pid){
        	if (processStory[pid]['pdata'] && processStory[pid]['tdata']){
        		plist=$('#pdetail-'+pid);
        		plist.html("");
        		startTime=processStory[pid]['pdata'].startTime;
        		startDate=new Date(startTime);
        		proto=$('#timeline-item-proto');
        		item=proto.clone();
        		item.attr('id','pstart-'+pid);
        		item.find('.btn').addClass('btn-success');
        		item.find('.btn').addClass('completed');
        		item.find('.timeline-date').html(dateFormat(startDate));
        		item.find('.widget-main span').html("Avvio processo");
        		plist.append(item);
        		for (i=0;i<processStory[pid]['tdata'].data.length;i++){
        			console.log(processStory[pid]['tdata'].data[i]);
        			itemData=processStory[pid]['tdata'].data[i];
        			proto=$('#timeline-item-proto');
        			item=proto.clone();
        			if(itemData.endTime!=null){
        				item.find('.btn').addClass('btn-success');
        				item.find('.btn').addClass('completed');
        				endTime=itemData.endTime;
        				endDate=new Date(endTime);
        				item.attr('id','ptask-'+itemData.id);
        				item.find('.timeline-date').html(dateFormat(endDate));
	        			item.find('.widget-main span').html(itemData.name);
        			}else {
        				startTime=itemData.startTime;
        				startDate=new Date(startTime);
        				item.attr('id','ptask-'+itemData.id);
        				item.find('.timeline-date').html(dateFormat(startDate));
	        			item.find('.widget-main span').html(itemData.name);
        			}
        			plist.append(item);
        		}
        		if (processStory[pid]['pdata'].endTime!=null){
	        		endTime=processStory[pid]['pdata'].endTime;
	        		endDate=new Date(endTime);
	        		proto=$('#timeline-item-proto');
	        		item=proto.clone();
	        		item.attr('id','pstart-'+pid);
	        		item.find('.btn').addClass('btn-success');
	        		item.find('.btn').addClass('completed');
	        		item.find('.timeline-date').html(dateFormat(endDate));
	        		item.find('.widget-main span').html("Processo completato");
	        		plist.append(item);	
        		}
        	}else { 
        		console.log("Non trovo i dati, asspetto 1s");
        		setTimeout(function(){ renderProcess(pid); }, 1000);
        	}
        }
        
        <#if model["activeProcesses"]?? && model["activeProcesses"]?size gt 0>
		    
		        <#list model["activeProcesses"] as ist>
		        	getActiveProcessStory(${ist.id});
				</#list>
		</#if>

</@script>

<style>

div.timeline-container.timeline-style2 div.timeline-info i.timeline-indicator.btn-success.completed{
	background-color: rgb(135, 184, 127) !important;
}

</style>

<div style="display:none">
	<div id='timeline-item-proto' class="timeline-item clearfix">
		<div class="timeline-info">
			<span class="timeline-date">11:15 pm</span>
			<i class="timeline-indicator btn btn-info no-hover"></i>
		</div>
		<div class="widget-box transparent">
			<div class="widget-body">
				<div class="widget-main no-padding">
					<span class="bigger-110">
						Process start
					</span>
				</div>
			</div>
		</div>
	</div>

</div>
 <#if model["terminatedProcesses"]?? && (model["terminatedProcesses"]?size gt 0)>
<div class="widget-box ">
	<div class="widget-header">
		<h4 class="lighter smaller">
		<i class="icon-cogs blue"></i> Processi
		</h4>
	</div>
	<div class="widget-body">
		<div class="widget-main">
		    <#assign activeProcess=false/>
		    <#if model["activeProcesses"]?? && model["activeProcesses"]?size gt 0>
		    	<h5>Processi in corso</h5>
		        <#list model["activeProcesses"] as ist>
		          	<#assign activeProcess=true/>
		          	<div class="row">
						<div class="col-xs-12 col-sm-10 col-sm-offset-1">
							<div class="timeline-container timeline-style2">
								<span class="timeline-label">
									<b>Processo ${ist.id}</b>
								</span>
								<div class="timeline-items" id="pdetail-${ist.id}">
									<i class="fa fa-spinner fa-spin"></i>
								</div><!-- /.timeline-items -->
							</div><!-- /.timeline-container -->
						</div>
					</div>
					<a target="about:blank" href="${baseUrl}/process-engine/runtime/process-instances/${ist.processInstanceId}/diagram"><img src="${baseUrl}/process-engine/runtime/process-instances/${ist.processInstanceId}/diagram" width="100%"/></a>
					
		        </#list>
		    </#if>
		    <#if model["terminatedProcesses"]?? && model["terminatedProcesses"]?size gt model["activeProcesses"]?size>
				<div class="accordion-style1 panel-group" id="accordion">
				 <div class="panel panel-default">
				  <div class="panel-heading">
				   <h4 class="panel-title">
				     <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#accordion" href="#collapseOne">
				       <i data-icon-show="ace-icon fa fa-angle-right" data-icon-hide="ace-icon fa fa-angle-down" class="bigger-110 ace-icon fa fa-angle-right"></i>
				       	Storico processi
				     </a>
				   </h4>
				  </div>
				  <div id="collapseOne" class="panel-collapse collapse">
				    <div class="panel-body">
			    <#list model["terminatedProcesses"] as ist1>
			    	<#if ist??>
			    		<#if ist1.id!=ist.id>
			    		<@script>
							getActiveProcessStory(${ist1.id})
						</@script>
				           <div class="row">
								<div class="col-xs-12 col-sm-10 col-sm-offset-1">
									<div class="timeline-container timeline-style2">
										<span class="timeline-label">
											<a href="#" onclick="">Processo ${ist1.id}</a>
										</span>
										<div class="timeline-items" id="pdetail-${ist1.id}">
											<i class="fa fa-spinner fa-spin"></i>
										</div><!-- /.timeline-items -->
									</div><!-- /.timeline-container -->
								</div>
							</div>
				    	</#if>
					<#else>
						<@script>
							getActiveProcessStory(${ist1.id})
						</@script>
					<div class="row">
						<div class="col-xs-12 col-sm-10 col-sm-offset-1">
							<div class="timeline-container timeline-style2">
								<span class="timeline-label">
									<a href="#" onclick="getActiveProcessStory(${ist1.id});return false;">Processo ${ist1.id}</a>
								</span>
								<div class="timeline-items" id="pdetail-${ist1.id}">
									<i class="fa fa-spinner fa-spin"></i>
								</div><!-- /.timeline-items -->
							</div><!-- /.timeline-container -->
						</div>
					</div>
					</#if>
				</#list>
		        </div>
				  </div>
				 </div>
				</div>
		    </#if>
		</div>
	</div>
</div>
</#if>
	