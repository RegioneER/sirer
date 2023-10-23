<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["jquery-ui-full", "datetimepicker","pages/studio.css","x-editable","select2","jqgrid"],
"scripts" : ["xCDM-modal","jquery-ui-full","datetimepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base","jqgrid","pages/home.js"],
"inline_scripts":[],
"title" : "Gestione Dizionario Promotori",
"description" : "Gestione Dizionario Promotori"
} />
<@style>
.select2-container {
	min-width:330px;
}

.infobox{
    width: 150px;
    height: 103px;
    text-align: center;
		//background-image: -moz-linear-gradient(bottom, #F2F2F2 0%, #FFFFFF 100%);
}

.infobox > .infobox-data {
    text-align: center;
    padding-left: 0px;
}

div#budget div{

}

</@style>
<#global breadcrumbs=
{
	"title":"Ultime modifiche",
	"links":[]
}
/>

<#if model['getCreatableRootElementTypes']??>
	<#list model['getCreatableRootElementTypes'] as docType>
		<#if docType.typeId="Studio">
			<@addmenuitem>
			{
				"class":"",
				"link":"${baseUrl}/app/documents/new/Studio",
				"level_1":true,
				"title":"Nuovo studio",
				"icon":{"icon":"icon-folder-open","title":"Nuovo studio"}
					}
			</@addmenuitem>

			<@addmenuitem>
			{
				"class":"",
				"link":"#",
				"level_1":true,
				"title":"Nuovo Centro",
				"icon":{"icon":"icon-hospital","title":"Nuovo centro"},
				"id": "addCenter"
					}
			</@addmenuitem>

			<@addmenuitem>
			{
				"class":"",
				"link":"${baseUrl}/app/documents/new/Progetto",
				"level_1":true,
				"title":" Nuovo progetto",
				"icon":{"icon":"icon-bar-chart","title":"Nuovo progetto"}
					}
			</@addmenuitem>
		</#if>
	</#list>
</#if>


<@onclick "studi_ins">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_ins').addClass('infobox-dark');
			studyList();
</@onclick>

<@onclick "studi_ins_reg">
            $('.infobox').removeClass('infobox-dark');
            $('#studi_ins_reg').addClass('infobox-dark');
            studyListReg();
</@onclick>
<@onclick "centri_ins_istruttoria">
            $('.infobox').removeClass('infobox-dark');
            $('#centri_ins_istruttoria').addClass('infobox-dark');
            centriListIstruttoria();
</@onclick>
<@onclick "tutti_centri">
			$('.infobox').removeClass('infobox-dark');
			$('#tutti_centri').addClass('infobox-dark');
			centriList();
</@onclick>
<@onclick "feasibility">
			$('.infobox').removeClass('infobox-dark');
			$('#feasibility').addClass('infobox-dark');
			feasabilityList();
</@onclick>
<@onclick "budget">
			$('.infobox').removeClass('infobox-dark');
			$('#budget').addClass('infobox-dark');
			budgetList();
</@onclick>
<@onclick "contratto">
			$('.infobox').removeClass('infobox-dark');
			$('#contratto').addClass('infobox-dark');
			contrattoList();
</@onclick>
<@onclick "valutazione_ce">
			$('.infobox').removeClass('infobox-dark');
			$('#valutazione_ce').addClass('infobox-dark');
			valutazioneCeList();
</@onclick>
<@onclick "approvati_ce">
			$('.infobox').removeClass('infobox-dark');
			$('#approvati_ce').addClass('infobox-dark');
			approvatoCeList();
</@onclick>
<@onclick "sospesi_ce">
			$('.infobox').removeClass('infobox-dark');
			$('#sospesi_ce').addClass('infobox-dark');
			sospesoCeList();
</@onclick>
<@onclick "nonapprovati_ce">
			$('.infobox').removeClass('infobox-dark');
			$('#nonapprovati_ce').addClass('infobox-dark');
			nonapprovatoCeList();
</@onclick>
<@onclick "studi_fatt">
			$('.infobox').removeClass('infobox-dark');
			$('#studi_fatt').addClass('infobox-dark');
			studiFattList();
</@onclick>

<@onclick "centri_monitor">
	$('.infobox').removeClass('infobox-dark');
	$('#centri_monitor').addClass('infobox-dark');
	monitorList();
</@onclick>

<@onclick "centri_chiusi">
	$('.infobox').removeClass('infobox-dark');
	$('#centri_chiusi').addClass('infobox-dark');
	chiusiList();
</@onclick>

<@onclick "centri_emendamento">
	$('.infobox').removeClass('infobox-dark');
	$('#centri_emendamento').addClass('infobox-dark');
	emendamentoList();
</@onclick>

<@onclick "centri_ritirati">
	$('.infobox').removeClass('infobox-dark');
	$('#centri_ritirati').addClass('infobox-dark');
	ritiratiList();
</@onclick>

<@onclick "tutti_centri">
	$('.infobox').removeClass('infobox-dark');
	$('#tutti_centri').addClass('infobox-dark');
	centriList();
</@onclick>

<@onclick "progetti_totali">
	$('.infobox').removeClass('infobox-dark');
	$('#progetti_totali').addClass('infobox-dark');
	progettiList();
</@onclick>