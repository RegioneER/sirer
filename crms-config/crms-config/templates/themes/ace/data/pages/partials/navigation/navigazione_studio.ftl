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
	"icon":{"icon":"icon-file-text","title":"Documenti core studio"}
	
}
</@addmenuitem>

<#list elStudio.getChildrenByType("Centro") as elCentro>
	
	<#assign idCentro=elCentro.getId() />
	<#if getUserGroups(userDetails)!='SP'>
		<@addmenuitem>
		{
			"class":"",
			"link":"${baseUrl}/app/documents/detail/${idCentro}",
			"level_1":true,
			"title":"Centro",
			"icon":{"icon":"icon-hospital","title":"${elCentro.titleString}"},
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
					"link":"${baseUrl}/app/documents/detail/${idCentro}#metadataTemplate-DatiCentro2",
					"level_2":true,
					"title":"Fattibilità",
					"icon":{"icon":"","title":"Fattibilità"}
				},
				{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#Budget-tab2",
				"level_2":true,
				"title":"Budget",
				"icon":{"icon":"","title":"Budget"}
				},
				{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}#IstruttoriaCE-tab2",
				"level_2":true,
				"title":"Valutazioni CE",
				"icon":{"icon":"","title":"Valutazioni CE"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}#Contratto-tab2",
					"level_2":true,
					"title":"Autorizzazioni avvio",
					"icon":{"icon":"","title":"Autorizzazioni avvio"}
				}
				,
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}#MonitoraggioAmministrativo-tab2",
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
					"link":"${baseUrl}/app/documents/detail/${idCentro}#GestioneFarmacia-tab2",
					"level_2":true,
					"title":"Gestione Farmacia",
					"icon":{"icon":"","title":"Gestione Farmacia"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}#AllegatoCentro-tab2",
					"level_2":true,
					"title":"Documenti",
					"icon":{"icon":"","title":"Documenti centro specifici"}
					}
				,
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
	<#else>
		<#if (elCentro.getfieldData("statoValidazioneCentro", "fattLocale")?? && elCentro.getfieldData("statoValidazioneCentro", "fattLocale")?size gt 0 && elCentro.getfieldData("statoValidazioneCentro", "fattLocale")[0]?split("###")[0] ="1") && ((elCentro.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")=="" || elCentro.getFieldDataString("statoValidazioneCentro","idParereCE")==""))>
			<@addmenuitem>
			{
				"class":"",
				"link":"${baseUrl}/app/documents/detail/${idCentro}",
				"level_1":true,
				"title":"Centro",
				"icon":{"icon":"icon-hospital","title":"${elCentro.titleString}"},
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
						"link":"${baseUrl}/app/documents/detail/${idCentro}#metadataTemplate-DatiCentro2",
						"level_2":true,
						"title":"Fattibilità",
						"icon":{"icon":"","title":"Fattibilità"}
					},
					{
						"class":"",
						"link":"${baseUrl}/app/documents/detail/${idCentro}#Budget-tab2",
						"level_2":true,
						"title":"Budget",
						"icon":{"icon":"","title":"Budget"}
					}
				]
			}
			</@addmenuitem>
		<#elseif (elCentro.getFieldDataString("statoValidazioneCentro","idIstruttoriaCEPositiva")!="" || elCentro.getFieldDataString("statoValidazioneCentro","idParereCE")!="") >
		<@addmenuitem>
		{
			"class":"",
			"link":"${baseUrl}/app/documents/detail/${idCentro}",
			"level_1":true,
			"title":"Centro",
			"icon":{"icon":"icon-hospital","title":"${elCentro.titleString}"},
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
					"link":"${baseUrl}/app/documents/detail/${idCentro}#metadataTemplate-DatiCentro2",
					"level_2":true,
					"title":"Fattibilità",
					"icon":{"icon":"","title":"Fattibilità"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}#Budget-tab2",
					"level_2":true,
					"title":"Budget",
					"icon":{"icon":"","title":"Budget"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}#IstruttoriaCE-tab2",
					"level_2":true,
					"title":"Valutazioni CE",
					"icon":{"icon":"","title":"Valutazioni CE"}
				}
			]
		}
		</@addmenuitem>
		<#else>
			<@addmenuitem>
			{
				"class":"",
					"link":"${baseUrl}/app/documents/detail/${idCentro}",
					"level_1":true,
					"title":"Centro",
					"icon":{"icon":"icon-hospital","title":"${elCentro.titleString}"},
					"submenu":[
						{
						"class":"",
						"link":"${baseUrl}/app/documents/detail/${idCentro}#metadataTemplate-IdCentro2",
						"level_2":true,
						"title":"Informazioni centro",
						"icon":{"icon":"","title":"Informazioni centro"}
						}
					]
			}
			</@addmenuitem>
		</#if>
	</#if>
</#list>

<#list elStudio.getChildrenByType("Emendamento") as elEmendamento>
<#assign idEmendamento=elEmendamento.getId() />

<@addmenuitem>
		{
			"class":"",
			"link":"${baseUrl}/app/documents/detail/${idEmendamento}",
			"level_1":true,
			"title":"Emendamento",
			"icon":{"icon":"icon-eraser","title":"${elEmendamento.titleString}"},
			"submenu":[
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idEmendamento}#metadataTemplate-DatiEmendamento2",
					"level_2":true,
					"title":"Dati Emendamento",
					"icon":{"icon":"","title":"Dati Emendamento"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idEmendamento}#AllegatoEme-tab2",
					"level_2":true,
					"title":"Documentazione Emendamento",
					"icon":{"icon":"","title":"Allegati Emendamento"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idEmendamento}#IstruttoriaEme-tab2",
					"level_2":true,
					"title":"Istruttoria Emendamento",
					"icon":{"icon":"","title":"Istruttoria Emendamento"}
				},
				{
					"class":"",
					"link":"${baseUrl}/app/documents/detail/${idEmendamento}#ParereEme-tab2",
					"level_2":true,
					"title":"Parere Emendamento",
					"icon":{"icon":"","title":"Parere Emendamento"}
				}

			]
		}

		</@addmenuitem>

</#list>
