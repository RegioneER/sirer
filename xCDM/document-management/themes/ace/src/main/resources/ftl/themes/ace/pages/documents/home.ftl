<div class="home-container" >
		<style>
		
		.ui-jqgrid tr.jqgrow td {
			white-space:normal;
		}
		.ui-jqgrid .ui-jqgrid-htable th div {
			white-space:normal;
			height:auto;
			margin-bottom:3px;
		}
	
		
		.home-table .ui-jqgrid{
			margin:10px;
			
		}
		
		tr.jqgrow{
			cursor:pointer;
		}
		
		.home-table {
			float:left;
		}
		.infobox {
			cursor: pointer;
			height: 130px;
		}
		
		</style>
		<@script>
			var $path_base = "${path.base}";//this will be used in gritter alerts containing images
		</@script>
		<#--
	<div class="col-sm-12 infobox-container">
		<@infobox "studi_ins" "icon icon-folder-open" "blue" "Totale Proposte"  "Lista proposte presenti nel sistema" />
		<@infobox "studi_1" "icon icon-folder-open" "green" "In compilazione"  "Lista proposte in compilazione" />
		<@infobox "studi_2" "icon icon-folder-open" "orange" "Offerta Core"  "Lista proposte in compilazione" />
		<@infobox "studi_3" "icon icon-folder-open" "red" "Offerta Cliente"  "Lista proposte in compilazione" />
		<@infobox "studi_4" "icon icon-folder-open" "orange2" "Firma Cliente"  "Lista proposte in compilazione" />
		<@infobox "studi_5" "icon icon-folder-open" "brown" "Firma Core"  "Lista proposte in compilazione" />
		<@infobox "studi_6" "icon icon-folder-open" "blue2" "Svolgimento"  "Lista proposte in compilazione" />
		<@infobox "studi_7" "icon icon-folder-open" "purple" "Consegna dliverables Core"  "Lista proposte in compilazione" />
		<@infobox "studi_8" "icon icon-folder-open" "green" "Consegna dliverables Cliente"  "Lista proposte in compilazione" />
		<@infobox "studi_9" "icon icon-folder-open" "orange" "Concluso"  "Lista proposte in compilazione" />

	</div>

		
		
		<span class="home-table" >
		<table id="home-grid-table" class="grid-table" ></table>
			<div id="home-grid-pager"></div>
		</span>	
	-->
<#assign title>
<span><@msg "base.title"/></span>
Benvenuto ${user.name}
</#assign>
<#assign body>
<#attempt>
	<#include "splash/${getUserGroups(userDetails)}.ftl"/>
	<#recover>
	<#include "splash/default.ftl"/>
</#attempt>	
</#assign>


<#assign footer>
<button id='splash-close' class="btn btn-xs pull-left">Chiudi</button>
disattiva finestra di benvenuto
<input id="splash-disable" class="ace ace-switch ace-switch-6" type="checkbox" name="switch-field-1">
<span class="lbl"></span>
</#assign>

<@script>


$('#splash-close').click(function(){
	$('#splash-home').modal("hide");
});

if (document.cookie.indexOf("splashDisabled") >= 0) {
	  
}else {
	$('#splash-home').modal();
}

$('#splash-disable').click(function(){
	//$('#splash-home').modal("hide");
	document.cookie = "splashDisabled=true; max-age=" + 60 * 60 * 24 * 365 * 2; // 60 seconds to a minute, 60 minutes to an hour, 24 hours to a day, and 10 days.
});
</@script>

<@modalbox "splash-home" title body footer/>
		
		
 </div>