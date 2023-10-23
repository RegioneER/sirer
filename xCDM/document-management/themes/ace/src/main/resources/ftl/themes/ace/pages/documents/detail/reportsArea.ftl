<h1>Area ${el.titleString}</h1>
	<#if el.childs??>
		<#list el.childs as report>
			<#if report.getUserPolicy(userDetails).canBrowse>
				<li><a href='${baseUrl}/app/documents/detail/${report.id}'>${report.titleString}</a></li>
			</#if>
		</#list>		
	</#if>
