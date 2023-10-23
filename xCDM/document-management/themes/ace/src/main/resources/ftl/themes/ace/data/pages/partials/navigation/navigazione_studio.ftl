<#assign idStudio=elStudio.getId() />

<@addmenuitem>
{
	"class":"active open",
	"link":"${baseUrl}/app/documents/detail/${idStudio}",
	"level_1":true,
	"title":"Informazioni studio",
	"icon":{"icon":"icon-folder-open","title":"Dati studio"}
		}
</@addmenuitem>

<@addmenuitem>	
{
	"class":"",
	"link":"${baseUrl}/app/documents/detail/${idStudio}#allegato-tab",
	"level_1":true,
	"title":"Documenti studio",
	"icon":{"icon":"icon-file-text","title":"Documenti studio"}
	
}
</@addmenuitem>
<#if userDetails.hasRole("CTC") >
	<@addmenuitem>
	{
		"class":"",
		"link":"#",
		"level_1":true,
		"title":"Dashboard studio",
		"icon":{"icon":"icon-dashboard","title":"Dashboard studio"},
		"submenu":[
				{
					"class":"",
					"link":"/pentahoee/content/reporting/reportviewer/report.html?solution=ce_gemelli&path=/ctcgemelli/descrittive&name=pr_tempi.prpt&locale=it_IT#id_studio=${idStudio}&centro=0",
					"target":"_blank",
					"level_2":true,
					"title":"Tempi",
					"icon":{"icon":"","title":"Tempi"}
				},
				{
					"class":"",
					"link":"/pentahoee/content/reporting/reportviewer/report.html?solution=ce_gemelli&path=/ctcgemelli/budget&name=pr_budget.prpt&locale=it_IT#id_studio=${idStudio}&centro=0",
					"target":"_blank",
					"level_2":true,
					"title":"Budget",
					"icon":{"icon":"","title":"Budget"}
				},
				
				{
					"class":"",
					"link":"/pentahoee/content/reporting/reportviewer/report.html?solution=ce_gemelli&path=/ctcgemelli/fatturazione&name=pr_fatturazione.prpt&locale=it_IT#id_studio=${idStudio}&centro=0",
					"target":"_blank",
					"level_2":true,
					"title":"Ricavi e fatturazione",
					"icon":{"icon":"","title":"Ricavi e fatturazione"}
				}
				
			]
			}
	</@addmenuitem>
<#elseif userDetails.hasRole("UR")>
	<@addmenuitem>
	{
		"class":"",
		"link":"#",
		"level_1":true,
		"title":"Dashboard studio",
		"icon":{"icon":"icon-dashboard","title":"Dashboard studio"},
		"submenu":[
				{
					"class":"",
					"link":"/pentahoee/content/reporting/reportviewer/report.html?solution=ce_gemelli&path=/ctcgemelli/descrittive&name=pr_tempi.prpt&locale=it_IT#id_studio=${idStudio}&centro=0",
					"target":"_blank",
					"level_2":true,
					"title":"Tempi",
					"icon":{"icon":"","title":"Tempi"}
				},
				
				{
					"class":"",
					"link":"/pentahoee/content/reporting/reportviewer/report.html?solution=ce_gemelli&path=/ctcgemelli/fatturazione&name=pr_fatturazione.prpt&locale=it_IT#id_studio=${idStudio}&centro=0",
					"target":"_blank",
					"level_2":true,
					"title":"Ricavi e fatturazione",
					"icon":{"icon":"","title":"Ricavi e fatturazione"}
				}
				
			]
			}
	</@addmenuitem>
<#else>
	<@addmenuitem>
	{
		"class":"",
		"link":"#",
		"level_1":true,
		"title":"Dashboard studio",
		"icon":{"icon":"icon-dashboard","title":"Dashboard studio"},
		"submenu":[
				{
					"class":"",
					"link":"/pentahoee/content/reporting/reportviewer/report.html?solution=ce_gemelli&path=/ctcgemelli/descrittive&name=pr_tempi.prpt&locale=it_IT#id_studio=${idStudio}&centro=0",
					"target":"_blank",
					"level_2":true,
					"title":"Tempi",
					"icon":{"icon":"","title":"Tempi"}
				}
				
			]
			}
	</@addmenuitem>
</#if>

<#list elStudio.getChildrenByType("Centro") as elCentro>
	
	<#assign idCentro=elCentro.getId() />
	<#--${elCentro.getFieldDataDecode("IdCentro","PI")}-->
	
	<@addmenuitem>
	{
		"class":"",
		"link":"${baseUrl}/app/documents/detail/${idCentro}",
		"level_1":true,
		"title":"Centro",
		"icon":{"icon":"icon-hospital","title":"${elCentro.getFieldDataDecode("IdCentro","PI")}"},
		"submenu":[
			{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#metadataTemplate-IdCentro2",
				"level_2":true,
				"title":"Informazioni centro",
				"icon":{"icon":"","title":"Informazioni centro"}
			},
			{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#metadataTemplate-Feasibility2",
				"level_2":true,
				"title":"Feasibility",
				"icon":{"icon":"","title":"Feasibility"}
			},
			{
			"class":"",
			"link":"${baseUrl}/app/documents/detail/${idCentro}#Budget-tab2",
			"level_2":true,
			"title":"Budget",
			"icon":{"icon":"","title":"Budget"}
			<!--, "submenu":[
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}",
					"level_3":true,
					"title":"Budget clinico",
					"icon":{"icon":"","title":"Budget clinico"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}",
					"level_3":true,
					"title":"Budget studio",
					"icon":{"icon":"","title":"Budget studio"}
				}
			]-->
			}
			
			{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#Contratto-tab2",
				"level_2":true,
				"title":"Contratto",
				"icon":{"icon":"","title":"Contratto"}
			},
			{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#MonitoraggioPaziente-tab2",
				"level_2":true,
				"title":"Monitoraggio",
				"icon":{"icon":"","title":"Monitoraggio"}
			},
			{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#Fatturazione-tab2",
				"level_2":true,
				"title":"Fatturazione",
				"icon":{"icon":"","title":"Fatturazione"}
			},
			{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#AllegatoCentro-tab2",
				"level_2":true,
				"title":"Documenti",
				"icon":{"icon":"","title":"Documenti"}
			},
			{
				"class":"filtered-tab-toggle",
				"link":"${baseUrl}/app/documents/detail/${idCentro}?toggle",
				"level_2":true,
				"title":"Mostra/Nascondi tutte le sezioni",
				"icon":{"icon":"","title":"Mostra/nascondi aree"}
			}
			
		]
	}
	
</@addmenuitem>	

</#list>
