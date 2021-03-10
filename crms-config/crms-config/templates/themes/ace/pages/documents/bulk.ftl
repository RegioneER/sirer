  <div class="page-header">
		<h1>Caricamento File Excel</h1>
  </div>
  <div class="alert alert-info">
  	Selezionare il foglio excel contenuto nel file caricato e mappare i campi sui metadati definiti per l'oggetto di ${model['destType'].typeId}
  </div>
  <@style>
  	.select2-choice{
  		min-width:200px;
  		}
  </@style>
<#assign sheetIdx=1/>
<div class="tabbable">
		<ul id="myTab4" class="nav nav-tabs padding-12 tab-color-blue background-blue">
			<#list model['columns']?keys as sheetName>
			<li <#if sheetIdx==1>class="active"</#if>>
				<a href="#tabs-${sheetIdx?c}" data-toggle="tab"><i class="fa fa-file-excel-o"></i> ${sheetName}</a>
			</li>
			<#assign sheetIdx=sheetIdx+1/>
			</#list>
		</ul>
		<div class="tab-content">
		<#assign sheetIdx=1/>
		<#list model['columns']?keys as sheetName>
		<#assign colIdx=0/>
		<div id="tabs-${sheetIdx?c}" class="tab-pane<#if sheetIdx==1> in active</#if>">
			<h2>${sheetName}</h2>
	
			
			<form method="POST" action="${baseUrl}/app/documents/bulk/load">
			<input type="hidden" name="destId" value="${model['destType'].id?c}"/>
			<input type="hidden" name="bulkId" value="${model['bulkId']?c}"/>
			<input type="hidden" name="parentId" value="${model['parentId']?c}"/>
			<input type="hidden" name="sheetName" value="${sheetName}"/>
			<table class="pSchema">
			<tr>
				<th>Campo Excel</th>
				<th>&nbsp</th>
				<th>Campo destinazione</th>
			<tr>
			<#list model['columns'][sheetName] as column>
				<tr>
					<td style="text-align:right">${column}</td>
					<td> -> </td>
					<td>
						<select id="map_${sheetIdx}_${colIdx?c}" name="col_${colIdx?c}">
							<option></option>
							<#list model['destType'].enabledTemplates as template>
								<#list template.fields as field>
									<option value="${field.id?c}">${template.name}.${field.name}</option>
								</#list>
							</#list>
						</select>
						<@script>
							$('#map_${sheetIdx}_${colIdx?c}').select2();
						</@script>
					</td>
				</tr>
			<#assign colIdx=colIdx+1/>
			</#list>
			</table>
			<button type="submit" class="btn btn-warning">
				<i class="fa fa-upload"></i> Carica
			</button>
			
			</form>
		
		
		</div>
		<#assign sheetIdx=sheetIdx+1/>
		</#list>
			
		</div>
</div>

<#--

	<div class="documentMainContent">
		Bulk Upload
		<br/>
		<div id="tabs">
<ul>
<#assign sheetIdx=1/>
	<#list model['columns']?keys as sheetName>
		<li><a href="#tabs-${sheetIdx?c}">${sheetName}</a></li>
<#assign sheetIdx=sheetIdx+1/>
	</#list>
</ul>
<#assign sheetIdx=1/>
		<#list model['columns']?keys as sheetName>
		<#assign colIdx=0/>
		<div id="tabs-${sheetIdx?c}">
		<#assign sheetIdx=sheetIdx+1/>
		<h2>${sheetName}</h2>
	
			
			<form method="POST" action="${baseUrl}/app/documents/bulk/load">
			<input type="hidden" name="destId" value="${model['destType'].id?c}"/>
			<input type="hidden" name="bulkId" value="${model['bulkId']?c}"/>
			<input type="hidden" name="parentId" value="${model['parentId']?c}"/>
			<input type="hidden" name="sheetName" value="${sheetName}"/>
			<table class="pSchema">
			<tr>
				<th>Campo Excel</th>
				<th>&nbsp</th>
				<th>Campo destinazione</th>
			<tr>
			<#list model['columns'][sheetName] as column>
				<tr>
					<td>${column}</td>
					<td> -> </td>
					<td>
						<select name="col_${colIdx?c}" style="min-width:200px">
							<option></option>
							<#list model['destType'].enabledTemplates as template>
								<#list template.fields as field>
									<option value="${field.id?c}">${template.name}.${field.name}</option>
								</#list>
							</#list>
						</select>
					</td>
				</tr>
			<#assign colIdx=colIdx+1/>
			</#list>
			</table>
			<input type="submit" value="Carica"/>
			
			</form>
	
			
		</div>
		</#list>
	</div>
	</div>
</div>
-->