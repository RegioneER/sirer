<#global availableTypes={} /> 
<@script>
	var empties=new Array();
    var updating=<#if el.getUserPolicy(userDetails).isCanUpdate() && el.getParent().getParent().getFieldDataString("ApprovazioneClinica","InviaServizi")!="1" >true<#else>false</#if>;
   	<#list elType.getAllowedChilds() as myType>
   	<#global availableTypes=availableTypes+{myType.typeId:myType} /> 
	<#assign json=myType.getDummyJson() />
	empty${myType.typeId}=${json};
	empties[empty${myType.typeId}.type.id]=empty${myType.typeId};
		<#list myType.getAllowedChilds() as childType>
			<#global availableTypes=availableTypes+{childType.typeId:childType} /> 
			<#assign json=childType.getDummyJson() />
			empty${childType.typeId}=${json};
			empties[empty${childType.typeId}.type.id]=empty${childType.typeId};
		</#list>
	</#list>
    <#assign elementJson=model['element'].getElementCoreJsonToString(userDetails) />
    var loadedElement=${elementJson};
    var groupItems=new Array();
    <#--list model['groupItems'] as item >
	groupItems[groupItems.length]=${item.getElementCoreJsonToString(userDetails)};
	</#list-->
</@script>