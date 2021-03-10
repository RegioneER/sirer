<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : [],
	"scripts" : [],
	"inline_scripts":[],
	"title" : "Dettaglio",
 	"description" : "Dettaglio" 
} />

<@breadcrumbsData el />
<#assign idCentro=el.parent.getId() />
<@script>

	window.location.href="${baseUrl}/app/documents/detail/${idCentro}#MonitoraggioAmministrativo-tab2";

</@script>