<style>
.form-horizontal .form-group{
	margin:0px;
}
label,#StatoPaziente-StatoPaziente_Stato div{
	padding-left:0px!important;
	margin-left:0px!important;
}
#StatoPaziente-StatoPaziente_Stato div{
	padding-bottom:20px;
}
.clearfix:after {
		    content: ".";
		    display: block;
		    height: 0;
		    clear: both;
		    visibility: hidden;
	    }
		
		.clearfix {
		    clear: both;
	    }
fieldset.specchietto {
		    border: 1px solid #336EA9!important;
		    border-radius: 10px!important;
		    padding: 1em!important;
		    font-size:12px;
		    
		    font-weight:bold;
		    font-family:arial;
		    width:90%;
		    float:left;
		    margin:10px;
		}
fieldset.specchietto * {
font-size:12px;

}		


.clearfix:after {
    content: ".";
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
    }

.clearfix {
    clear: both;
    }
    
.vs{
float: left;
    width: 50%;
    height:150px;
}
.vs label{
	width:30%;
}

.re{
float: left;
    width: 40%;
    height:150px;
}
.re label{
	width:55%;
}

.ri{
float: left;
    width: 80%;
}
.ri label{
	width:55%;
}

.vl{
float: left;
    width: 45%;
}
.vl label{
	width:55%;
}

.ui-autocomplete.ui-menu{
	z-index:9999!important;
}

.view-mode label {
    background-color: #FFFFFF;
    font-weight: normal !important;
    margin: 0;
    padding: 0.25em 0.5em;
    width: 15em;
}

.list-table a:hover {
    color: #000000;
    text-decoration: none;
}
.list-table a:visited {
    color: #000000;
    text-decoration: none;
}
.list-table a {
    color: #000000;
    text-decoration: none;
}
.home-fieldset {
    background-color: #DFEFFC;
    border: 1px solid #8AB8DA;
    border-radius: 10px;
    margin-bottom: 20px;
    padding: 5px;
    width: 90%;
}
.home-legend {
    background-color: #4084CA;
    border: 1px solid #8AB8DA;
    border-radius: 10px;
    color: #FFFFFF;
    padding: 5px;
}
.highlightRow {
    color: #438DD7 !important;
    font-weight: bold;
}
.list-table {
}
.list-table th {
    background-color: #FFFFFF;
    border-bottom: 1px solid #4D80B4;
    border-left: 1px ridge #4D80B4;
    color: #5D8DBE;
    font-size: 12px;
    font-weight: bold;
}
.list-table td {
    font-size: 12px;
    padding-left: 2px;
    padding-right: 2px;
    text-align: left;
}
.list-table tr:nth-child(2n+1) td {
    background-color: #F0FFFF;
}
.list-table tr:nth-child(2n) td {
    background-color: #F5FFFA;
}
.select2-container {
	min-width:130px!important;
}
</style>
<@script>
var loadedBraccio=false;
	$('label').removeAttr('class');
</@script>

<#include "../helpers/MetadataTemplate.ftl"/>
 <div class="row">
	<div class="col-xs-10">
		<#assign parentEl=el/>


		<div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
		<div id="tabs" class="tabbable">
			<ul style='height:27px'  class="nav nav-tabs">
				<!-- li><a id='tab0' href="#tabs-0" data-toggle="tab" >Gruppi di prestazioni</a></li -->
				<!--li><a id='tab1' href="#tabs-1" data-toggle="tab" >Flowchart</a></li-->
				<li><a id='DatiMonitoraggioAmministrativo' href="#tabs-DatiMonitoraggioAmministrativo" data-toggle="tab" >Scheda monitoraggio amministrativo</a></li>
				<li><a id='DatiMonPxP' href="#tabs-DatiMonPxP" data-toggle="tab" >Prestazioni</a></li>
				<li><a id='DatiMonPazientiFatturabili' href="#tabs-DatiMonPazientiFatturabili" data-toggle="tab" >Pazienti Fatturabili</a></li>
			</ul>
			<div  class="tab-content" >
				<div id="tabs-DatiMonitoraggioAmministrativo" class="tab-pane">
					<#assign editMonitoraggio=false />
					<#assign tablePrestazioni>
					<table class="table table-striped table-bordered table-hover " >
						<thead>
						<tr>
							<th>Descrizione</th>
							<th>Fatturate</th>
							<th>Nr. Pazienti</th>
							<th>Totali da fatturare</th>
						</tr>
						</thead>
						<tbody>
						<tr><td colspan="4"><span class="help-button">?</span>&nbsp;Prestazioni a richiesta / altre prestazioni non cliniche per paziente</td></tr>

			<#list parentEl.getChildrenByType("FolderMonPxP") as subFolder>
				<#list subFolder.getChilds() as subEl>
					<#assign editDatiMonPxP=true />
					<#if (subEl.getfieldData("DatiMonPxP","Fatturato")?? && subEl.getfieldData("DatiMonPxP","Fatturato")?size>0 && subEl.getfieldData("DatiMonPxP","Fatturato")[0]?number>0 ) && (subEl.getfieldData("DatiMonPxP","Fatturabile")?? && subEl.getfieldData("DatiMonPxP","Fatturabile")?size>0 && subEl.getfieldData("DatiMonPxP","Fatturabile")[0]?number==0) >
						<#assign editDatiMonPxP=false />
					</#if>
					<#assign editMonitoraggio=editMonitoraggio || editDatiMonPxP />
					<#assign prestazione=subEl.getFieldDataElement("DatiMonPxP","BudgetLink")[0] />
						<tr>
							<td>${prestazione.getfieldData("Base","Nome")[0]}</td>
							<td><#if (subEl.getfieldData("DatiMonPxP","Fatturato")?? && subEl.getfieldData("DatiMonPxP","Fatturato")?size>0) >${subEl.getfieldData("DatiMonPxP","Fatturato")[0]}<#else>0</#if></td>
							<td><input <#if !editDatiMonPxP>disabled="disabled"</#if> type="text" size="5" id="${subEl.getId()}" name="DatiMonPxP_numeroPazienti" value="<#if (subEl.getfieldData("DatiMonPxP","numeroPazienti")?? && subEl.getfieldData("DatiMonPxP","numeroPazienti")?size>0) >${subEl.getfieldData("DatiMonPxP","numeroPazienti")[0]}<#else>0</#if>" /></td>
							<td><input <#if !editDatiMonPxP>disabled="disabled"</#if> type="text" size="5" id="${subEl.getId()}" name="DatiMonPxP_Fatturabile" value="<#if (subEl.getfieldData("DatiMonPxP","Fatturabile")?? && subEl.getfieldData("DatiMonPxP","Fatturabile")?size>0) >${subEl.getfieldData("DatiMonPxP","Fatturabile")[0]}<#else>0</#if>" /></td>
						</tr>
				</#list>
			</#list>

						</tbody>
					</table>
					</#assign>
					<#assign tablePazienti>
					<table class="table table-striped table-bordered table-hover " >
						<thead>
						<tr>
							<th>Descrizione</th>
							<th>Nr. Pazienti</th>
							<th>Prezzo Totale</th>
						</tr>
						</thead>
						<tbody>
						<#list parentEl.getChildrenByType("FolderMonPazientiFatturabili") as subFolder>
						<#list subFolder.getChilds() as subEl>
						<#assign editDatiMonPazientiFatturabili=true />
						<#if (subEl.getfieldData("DatiMonPazientiFatturabili","Fatturato")?? && subEl.getfieldData("DatiMonPazientiFatturabili","Fatturato")?size>0 && subEl.getfieldData("DatiMonPazientiFatturabili","Fatturato")[0]?number>0 ) && (subEl.getfieldData("DatiMonPazientiFatturabili","Fatturabile")?? && subEl.getfieldData("DatiMonPazientiFatturabili","Fatturabile")?size>0 && subEl.getfieldData("DatiMonPazientiFatturabili","Fatturabile")[0]?number==0) >
						<#assign editDatiMonPazientiFatturabili=false />
						</#if>
						<#assign editMonitoraggio=editMonitoraggio || editDatiMonPazientiFatturabili />
						<#assign prestazione=subEl.getFieldDataString("DatiMonPazientiFatturabili","Note")/>
						<tr>
							<td>${prestazione}</td>
							<td><input <#if !editDatiMonPazientiFatturabili>disabled="disabled"</#if> type="text" size="5" id="${subEl.getId()}" name="DatiMonPazientiFatturabili_numeroPazienti" value="<#if (subEl.getfieldData("DatiMonPazientiFatturabili","numeroPazienti")?? && subEl.getfieldData("DatiMonPazientiFatturabili","numeroPazienti")?size>0) >${subEl.getfieldData("DatiMonPazientiFatturabili","numeroPazienti")[0]}<#else>0</#if>" /></td>
							<td><input <#if !editDatiMonPazientiFatturabili>disabled="disabled"</#if> type="text" size="5" id="${subEl.getId()}" name="DatiMonPazientiFatturabili_Prezzo" value="<#if (subEl.getfieldData("DatiMonPazientiFatturabili","Prezzo")?? && subEl.getfieldData("DatiMonPazientiFatturabili","Prezzo")?size>0) >${subEl.getfieldData("DatiMonPazientiFatturabili","Prezzo")[0]}<#else>0</#if>" /></td>

						</tr>
						</#list>
						 </#list>

						</tbody>
					</table>
					</#assign>
					<#assign titolo> <@msg "template.DatiMonitoraggioAmministrativo"/> </#assign>
					<@TemplateFormTable "DatiMonitoraggioAmministrativo" el userDetails editMonitoraggio titolo/>
				</div>
				<div id="tabs-DatiMonPxP" class="tab-pane">
					${tablePrestazioni}
					<div class="clearfix"></div>
					<#if editMonitoraggio>
						<button class="btn btn-warning" id="Salva"  onclick="saveAll();"><i class="icon-save"></i> <b>Salva</b></button>
					</#if>
				</div>
				<div id="tabs-DatiMonPazientiFatturabili" class="tab-pane">
					${tablePazienti}
					<div class="clearfix"></div>
					<#if editMonitoraggio>
					<button class="btn btn-warning" id="Salva"  onclick="saveAll();"><i class="icon-save"></i> <b>Salva</b></button>
				</#if>
				</div>
			</div>
		</div>
	</div>
	<#-- div class="col-xs-2 sidebar-right">
		<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
			<i class="icon-chevron-right bigger-150"></i>
		</div>
		<div class=" status-bar-content">
			<div class="col-xs-12 status-bar">
				<h2>Informazioni paziente</h2>
				<@TemplateForm "DatiMonitoraggioAmministrativo" el userDetails false />
				<div class="clearfix"></div>
				<div class="field-component" style="padding-left:12px">
				<@TemplateFormFastUpdate "StatoPaziente" el userDetails true />
			</div>


			<#assign bracciOptions=""/>
			<#assign currBraccio=[""] />
			<#if (el.getFieldDataElement("DatiCustomMonitoraggioAmministrativo","Braccio")?size gt 0) >
				<#assign braccioFilter=el.getFieldDataElement("DatiCustomMonitoraggioAmministrativo","Braccio")[0].getFieldDataString("Base","Nome") />
				<#assign currBraccio=[el.getFieldDataElement("DatiCustomMonitoraggioAmministrativo","Braccio")[0].getId()?string+"###"+braccioFilter] />
				<@script>
					var loadedBraccio='${el.getFieldDataElement("DatiCustomMonitoraggioAmministrativo","Braccio")[0].getId()?string}';
					var braccioFilter="${braccioFilter}";
					$('#DatiCustomMonitoraggioAmministrativo_Braccio-select').val(loadedBraccio);
				</@script>
			<#else>
				<@script>
					var braccioFilter=false;

				</@script>
			</#if>
			<#list parentEl.getChildrenByType("FolderMonBracci") as subFolder>
				<#assign bracciLinkList=subFolder.getChildren() />
				<#assign bracciList=[] />
				<#list bracciLinkList as braccio>

					<#assign braccioEl=braccio.getFieldDataElement("DatiMonBraccio","Braccio")[0] />
					<#assign bracciList=bracciList+[braccioEl] />
					<#assign bracciOptions=bracciOptions+"<option value='"+braccioEl.getId()+"'>"+braccioEl.getFieldDataString("Base","Nome")+"</option>"/>
				</#list>
			</#list>
			<#if bracciOptions!="" >
				<div class="clearfix field-inline-edit" style="padding-left:12px">
					<label>Braccio:</label><br>
					<#attempt>
						<@braccioField "DatiCustomMonitoraggioAmministrativo" "Braccio" parentEl userDetails true bracciList currBraccio />
					<#recover>
					</#attempt>
				</div>
			</#if>
		</div>
	</div -->
	</div>
</div>