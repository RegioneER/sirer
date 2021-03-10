<#global availableTypes={} /> 
<@script>
    var updating=<#if el.getUserPolicy(userDetails).isCanUpdate() && el.getFieldDataString("ApprovazioneClinica","InviaServizi")!="1" >true<#else>false</#if>;
   	<#list elType.getAllowedChilds() as myType>
   	<#global availableTypes=availableTypes+{myType.typeId:myType} /> 
	<#assign json=myType.getDummyJson() />
	empty${myType.typeId}=${json};
		<#list myType.getAllowedChilds() as childType>
			<#global availableTypes=availableTypes+{childType.typeId:childType} /> 
			<#assign json=childType.getDummyJson() />
			empty${childType.typeId}=${json};
		</#list>
	</#list>
    <#assign elementJson=model['element'].getElementCoreJsonToString(userDetails) />
    var loadedElement=${elementJson};
    var groupItems=new Array();
    <#--list model['groupItems'] as item >
	groupItems[groupItems.length]=${item.getElementCoreJsonToString(userDetails)};
	</#list-->
</@script>