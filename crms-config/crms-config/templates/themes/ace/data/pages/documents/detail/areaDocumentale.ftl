<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
	"inline_scripts":[],
	"title" : "Dettaglio",
 	"description" : "Dettaglio" 
} />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>
	$.fn.editable.defaults.mode = 'inline';
	$('.field-inline-anchor').editable({
	    params: function(params) {
		    var metadata={};
		    metadata[params.name]=params.value
		   
		    return metadata;
	    },
	    emptytext :"Valore mancante"	
	});
 	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var empties=new Array();
 	
 	empties[dummy.type.id]=dummy;
 	$('#sidebar').find('.nav-list li:nth(1)').find('ul').show();
</@script>


<#if model['getCreatableElementTypes']??>
<#list model['getCreatableElementTypes'] as docType>
<#assign tmpText>
<@msg "type.create."+docType.typeId/>
</#assign>
<#assign tmpText=tmpText?replace("Carica documento","") />
    <#assign temp>
    	<#if temp??>${temp},</#if>
    	{
			"class":"",
			"link":"${baseUrl}/app/documents/addChild/${el.id}/${docType.id}",
			"level_2":true,
			"title":"Nuovo studio",
			"icon":{"icon":"icon-plus","title":"${tmpText}"}
		}
    </#assign>		
    
        	
    
				
   
</#list>


<@addmenuitem>
	{
		"class":"",
		"link":"${baseUrl}/app/documents",
		"level_1":true,
		"title":"Nuovo documento",
		"icon":{"icon":"icon-plus","title":"Carica documento"},
		"submenu":[
		${temp}
		]
	}
</@addmenuitem>
</#if>