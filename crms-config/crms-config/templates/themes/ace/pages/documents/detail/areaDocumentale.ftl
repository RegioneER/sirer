

<style>

.vs{
float: left;
    width: 45%;
}
.vs label{
	width:33%;
}

.re{
    width: 45%;
}
.re label{
	width:33%;
}

.ri{
float: left;
    width: 45%;
}
.ri label{
	width:33%;
}

.vl{
    width: 45%;
}
.vl label{
	width:33%;
	color:#E17031;
}

.l4 {
	color:#E17031;
}

.ui-autocomplete.ui-menu{
	z-index:9999!important;
}

.span1{
	color:#125873;
}
</style>

  <div class="row">
   		<div class="col-xs-12">
   			
<#include "../helpers/MetadataTemplate.ftl"/>
	<#assign folders={"Template":[],"SOP":[],"Altro":[]} />
	<#list el.getChildren() as subEl1>
		<#if subEl1.getUserPolicy(userDetails).isCanView()>
		<#assign folders=folders+{subEl1.getFieldDataDecode("DatiDocMeta","Tipologia"):folders[subEl1.getFieldDataDecode("DatiDocMeta","Tipologia")]+[subEl1]} />
		</#if>
	</#list>

	<div style="display: block">
	
			
    <#list folders?keys as currFolder >
		<#assign content=folders[currFolder] />
    	<!--inizio tabella nuova-->
    	<div class="row">
				<div class="col-xs-12">
					<div class="table-header"> <i class="icon-file-text"></i> ${currFolder} </div>
					<div class="table-responsive">	
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
									<#--th class="hidden-480">Tipologia</th-->
									<th class="hidden-480">File</th>
									<th class="hidden-480">Titolo</th>
									<th class="hidden-480">Autore</th>
									<th class="hidden-480">Versione</th>
									<th class="hidden-480">Data</th>
									<th class="hidden-480">Note</th>
									<th class="hidden-480">Inserito da</th>
									<th class="hidden-480">Caricato il</th>
									<th style="width: 6%">Azioni</th>
								</tr>
							</thead>

							<tbody>	

    				<#list content as subEl>
    		
    				
    				<#assign tipologia >
    					<@msg "type."+subEl.getType().getTypeId() />	
    					
    				</#assign>
								<#assign autore="" />
								<#assign titolo="" />
								<#assign version="" />
								<#assign fileName="" />
								<#assign uploadUser="" />
								<#assign uploadDt="" />
								<#assign data="" />
								<#assign note="" />
								
									<#if subEl.file??>
									<#if subEl.file.autore??>
										<#assign autore=subEl.file.autore />
									</#if>
									
									<#assign titolo=subEl.getFieldDataString("DatiDocMeta","Titolo") />
									
									
									<#if subEl.file.version??>
										<#assign version=subEl.file.version />
									</#if>
									
									<#if subEl.file.fileName??>	
										<#assign fileName=subEl.file.fileName />
									</#if>
									
									<#if subEl.file.uploadUser??>
										<#assign uploadUser=subEl.file.uploadUser />
									</#if>
									
									<#if subEl.file.uploadDt??>
										<#assign uploadDt=subEl.file.uploadDt.time?date?string.short />
									</#if>
									
									<#if subEl.file.date??>
										<#assign data=subEl.file.date.time?date?string.short />
									</#if>
									
									<#if subEl.file.note??>
										<#assign note=subEl.file.note />
									</#if>
								</#if>
								
								<tr>
									<#--td class="hidden-480">${tipologia}</td-->
									<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${fileName}</a></td>
									<td class="hidden-480"><a class="center-link" href="${baseUrl}/app/documents/getAttach/${subEl.id}">${titolo}</a></td>
									<td class="hidden-480">${autore}</td>
									<td class="hidden-480">${version}</td>
									<td class="hidden-480">${data}</td>
									<td class="hidden-480">${note}</td>
									<td class="hidden-480">${uploadUser}</td>
									<td class="hidden-480">${uploadDt}</td>
									<td>
										<div class="visible-md visible-lg hidden-sm hidden-xs action-buttons">
											<a class="blue" href="${baseUrl}/app/documents/detail/${subEl.id}">
												<i class="icon-zoom-in bigger-130"></i>
											</a>
											<a class="blue" href="${baseUrl}/app/documents/getAttach/${subEl.id}">
												<i class="icon-cloud-download bigger-130"></i>
											</a>
										</div>
									</td>
								</tr>
									</#list>
 							</tbody>
						</table>
					</div>
				</div>
			</div>
    	<!--fine tabella nuova-->	
    		
    	</legend>
    </fieldset>
   </#list>
        	
    </div>
   

</div>
	
    
    </div>