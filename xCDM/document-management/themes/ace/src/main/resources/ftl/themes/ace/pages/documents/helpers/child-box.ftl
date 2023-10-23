
<div class="widget-box">
	<div class="widget-header">
		<h4>Allegati</h4>
		<div class="widget-toolbar">
			<#if model['getCreatableElementTypes']?? && model['getCreatableElementTypes']?size gt 0 >
			    <#list model['getCreatableElementTypes'] as docType>
			    	<a class="" href="${baseUrl}/app/documents/addChild/${el.id}/${docType.id}"><i class="fa fa-plus"></i> ${docType.typeId}</a>
			    </#list>
			</#if>	
		</div>
	</div>
	<div class="widget-body">
		<div class="widget-main">
		<#if model['getCreatableElementTypes']?? && model['getCreatableElementTypes']?size gt 0 >
			    <#list model['getCreatableElementTypes'] as docType>
			    	<a class="btn btn-sm btn-info" href="${baseUrl}/app/documents/addChild/${el.id}/${docType.id}"> Crea nuovo ${docType.typeId}</a>
			    </#list>
		</#if>
		
		<#if el.children??>
			<div class="table-responsive">
				<table class="table table-striped table-bordered table-hover">
					<thead>
						<tr>
							<th>&nbsp;</th>
							<th>Titolo</th>
							<th>Data Creazione</th>
							<th>Data Ultima modifica</th>
						</tr>
					</thead>
					<tbody>
						
				<#list el.children as child>
					<tr onclick="window.location.href='${baseUrl}/app/documents/detail/${child.id}';">
						<#assign typeIconSrc=child.type.imageBase64!/>
						<#if typeIconSrc=="">
						    <#assign typeIconSrc=baseUrl+"/int/images/document_blank.png"/>
						</#if>
						<td><img src="${typeIconSrc}" style="max-height:20px"/></td>
						<td>${child.titleString}</td>
						<td>${child.creationDt.time?datetime?string.short}</td>
						<td><#if child.lastUpdateDt??>
							${child.lastUpdateDt.time?datetime?string.short}
							<#else>&nbsp;
							</#if>
						</td>
					</tr>	
				</#list>
					</tbody>
				</table>
				<#if el.children?size == 1>
				${el.children?size} elemento contenuto
				<#else>
				${el.children?size} elementi contenuti
				</#if>
			</div>
		</#if> 
		</div>
	</div>
</div>
		
