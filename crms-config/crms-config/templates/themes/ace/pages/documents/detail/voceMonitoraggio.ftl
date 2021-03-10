<style>
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
</style>
<#include "../helpers/title.ftl"/>
	
<!--tabella dettaglio fattura inizio-->
<div class="row">
	<div class="col-xs-12">
		<div class="table-header"> Dettaglio fattura </div>
		<div class="table-responsive">	
			<table id="sample-table-1" class="table table-striped table-bordered table-hover">
				<thead>
					<tr>
						<th style="text-align:left;width:20%">Visita</th>
						<th style="text-align:left;width:40%">Prestazione</th>
						<th style="text-align:left;width:30%">Paziente</th>
						<th style="text-align:left;width:10%">N. prestazioni</th>
					</tr>
				</thead>
				<tbody>
					<#list el.getChildrenByType("LinkMonitoraggio") as currLink >
						<tr>
							<td style="text-align:left;width:20%">${currLink.getFieldDataString("DatiLinkMonitoraggio","TimePoint")}</td>
						 	<td style="text-align:left;width:40%">${currLink.getFieldDataString("DatiLinkMonitoraggio","Prestazione")}</td>
							<td style="text-align:left;width:30%"><#if currLink.getFieldDataElement("DatiLinkMonitoraggio","Paziente")?size gt 0>${currLink.getFieldDataElement("DatiLinkMonitoraggio","Paziente")[0].getFieldFormattedDate("DatiMonitoraggioAmministrativo","dataMonitoraggio")} <#if currLink.getFieldDataElement("DatiLinkMonitoraggio","Paziente")[0].getFieldDataDecode("DatiMonitoraggioAmministrativo","BraccioBudget")?? && currLink.getFieldDataElement("DatiLinkMonitoraggio","Paziente")[0].getFieldDataDecode("DatiMonitoraggioAmministrativo","BraccioBudget")!=""> - ${currLink.getFieldDataElement("DatiLinkMonitoraggio","Paziente")[0].getFieldDataDecode("DatiMonitoraggioAmministrativo","BraccioBudget")}</#if></#if></td>
						 	<td style="text-align:left;width:10%">${currLink.getFieldDataString("DatiLinkMonitoraggio","Quantita")}</td>
						 </tr>
					</#list>
				</tbody>
			</table>
		</div>
	</div>
</div>
<!--tabella dettaglio fattura fine-->