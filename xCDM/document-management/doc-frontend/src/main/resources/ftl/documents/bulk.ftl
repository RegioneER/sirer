 <script>
 $(document).ready(function(){
	$( "#tabs" ).tabs();
	});
</script>
<div class="mainContent">

	<div class="documentMainContent">
		Bulk Upload
		<br/>
		<div id="tabs">
<ul>
<#assign sheetIdx=1/>
	<#list model['columns']?keys as sheetName>
		<li><a href="#tabs-${sheetIdx}">${sheetName}</a></li>
<#assign sheetIdx=sheetIdx+1/>
	</#list>
</ul>
<#assign sheetIdx=1/>
		<#list model['columns']?keys as sheetName>
		<#assign colIdx=0/>
		<div id="tabs-${sheetIdx}">
		<#assign sheetIdx=sheetIdx+1/>
		<h2>${sheetName}</h2>
	
			
			<form method="POST" action="${baseUrl}/app/documents/bulk/load">
			<input type="hidden" name="destId" value="${model['destType'].id}"/>
			<input type="hidden" name="bulkId" value="${model['bulkId']}"/>
			<input type="hidden" name="parentId" value="${model['parentId']}"/>
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
						<select name="col_${colIdx}">
							<option></option>
							<#list model['destType'].enabledTemplates as template>
								<#list template.fields as field>
									<option value="${field.id}">${template.name}.${field.name}</option>
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