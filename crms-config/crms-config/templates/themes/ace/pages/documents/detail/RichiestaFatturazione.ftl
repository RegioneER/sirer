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
//.list-table {
//}
//.list-table th {
//    background-color: #FFFFFF;
//    border-bottom: 1px solid #4D80B4;
//    border-left: 1px ridge #4D80B4;
//    color: #5D8DBE;
//    font-size: 12px;
//    font-weight: bold;
//    text-align: left;
//}
//.list-table td {
//    font-size: 12px;
//    padding-left: 2px;
//    padding-right: 2px;
//    text-align: left;
//}
//.list-table tr:nth-child(2n+1) td {
//    background-color: #F0FFFF;
//}
//.list-table tr:nth-child(2n) td {
//    background-color: #F5FFFA;
//}

.data-view-mode {
    margin-left: 2em;
}

.select2-container {
    min-width: 100px;
}

</style>

<#include "../helpers/MetadataTemplate.ftl"/>
<#include "../helpers/title.ftl"/>
	<div style="display: block">
		<!--div style="float: right"-->
		<div style="float: left">
		<!--#include "../helpers/information.ftl"/-->
		<!--#include "../helpers/actions.ftl"/-->
		<!--#include "../helpers/workflow.ftl"/-->
		<!--#include "../helpers/permission.ftl"/-->
		</div>       		
  
  	<#assign activeProcess=false/>
  	<#assign feedback=true/>
  	<#assign edit=false/>	
  	<#if model["activeProcesses"]??>
    	<#list model["activeProcesses"] as ist>
     		<#assign feedback=false/>
     		<#assign activeProcess=true/>
     		<#assign edit=true/>
     	</#list>
  	</#if>
    <div id="task-Actions" style="float: right;"> 
    
    </div>    
    <!--		
    <fieldset style="background-color:#DFEFFC">
		<legend style="color: #125873">Stato di avanzamento</legend>
		
		<#if getFieldFormattedDate("DatiFatturaWF", "DataApprovCTC", el)=="">
			<span style="background-color: #FFAA66;border-radius: 5px;padding:2px;">Richiesta di fatturazione:&nbsp;&nbsp;</span>
			<span style="background-color: #F4A460;border-radius: 5px;padding:2px;"><b>Pending</b> &nbsp;</span>
		</#if>
		<#if getFieldFormattedDate("DatiFatturaWF", "DataApprovCTC", el)!="">
			<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Richiesta di fatturazione:&nbsp;&nbsp;</span>
			<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>${getFieldFormattedDate("DatiFatturaWF", "DataApprovCTC", el)}</b> &nbsp;</span>
		</#if>
		</fieldset>
		-->
		
		<#assign Feed=false/>
		<#assign stile1=" \"background-color: #FFAA66;border-radius: 5px;padding:2px;\" "/>
    <#assign stile2=" \"background-color: #F4A460;border-radius: 5px;padding:2px;\" "/>	
    					
		<#list el.getChildrenByType("FatturaFeedback") as subEl>
    		<#if subEl.id??>
    			
    			<#assign statoFatt=subEl.getfieldData("DatiFatturaFeedback","Feedback")[0]?split("###")[0]/>
    			<#if statoFatt=="1" || statoFatt=="3">
    				<#assign Feed=true/>
    				<#assign stile1=" \"background-color: #9BFF9B;border-radius: 5px;padding:2px;\" "/>
    				<#assign stile2=" \"background-color: lightgreen;border-radius: 5px;padding:2px;\" "/>	
    			</#if>	
    			
					<div>
						<span style=${stile1}>Feedback fattura:&nbsp;&nbsp;</span>
						<span style=${stile2}>${subEl.getfieldData("DatiFatturaFeedback","Feedback")[0]?split("###")[1]} (${subEl.getfieldData("DatiFatturaFeedback", "Data")[0].time?date?string.short})</span>
						<br/><br/>
					</div>
				</#if>
    	</#list>
    		
    <br><br>			
    
     
       
    <#assign parentEl=el/>
    <legend>Riepilogo</legend>  		
	  <!--legend>Fattura di ${el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[1]} ${el.id}</legend-->
		<#assign prezzoAcc="0.00" />
		<#if el.getfieldData("DatiFatturaScheduling","AccontoAssoluto")[0]??>
			<#assign prezzoAcc=el.getfieldData("DatiFatturaScheduling","AccontoAssoluto")[0] />
		</#if>
		<#assign rimbo="">
			<#if el.getfieldData("DatiFatturaScheduling","StartUpRimborsabile")[0]??>
				<#assign rimbo='${getDecode("DatiFatturaScheduling","StartUpRimborsabile",el)}' />
			</#if>

		<#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='1' && prezzoAcc?number gt 0 >
			<!--tabella milestone start-up inizio-->
    		<div id="acconto" class="row">
				<div class="col-xs-12">
					<div class="table-header"> Milestone di fatturazione tempo zero (inizio contratto) </div>
					<div class="table-responsive">	
    				<table id="sample-table-1" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
	  							<th class="hidden-480" style="text-align:left;width:60%">Descrizione</th>
	  							<th class="hidden-480" style="text-align:center;width:10%">Rimborsabile</th>
	  							<th class="hidden-480" style="text-align:right;width:10%">Totale</th>
	  							<th class="hidden-480" style="text-align:center;width:10%">Fattura</th>
	  							<th class="hidden-480" style="text-align:center;width:10%">Visualizza fattura </th>
	  						</tr>
    					</thead>
							<tbody>
							<tr>
	  							<td class="hidden-480" style="text-align:left;">Anticipo sui pazienti</td>
	  							<td class="hidden-480" style="text-align:center;">${rimbo}</td>
	  							<td class="hidden-480" id="totale5_${el.id}" style="text-align:right;">${prezzoAcc}</td>
	  							<td class="hidden-480" style="text-align:center;"><form id="${el.id}" name="fattura2" ><@SingleFieldNoLabel "DatiFatturaScheduling" "SelectFattura" el userDetails edit/></form></td>
	  							<td class="hidden-480" style="text-align:center;"><#if (el.getFieldDataCode("DatiFatturaScheduling","SelectFattura")!="0" && el.getFieldDataElement("DatiFatturaScheduling","LinkFattura")?? && el.getFieldDataElement("DatiFatturaScheduling","LinkFattura")?size gt 0)><a href='${el.getFieldDataElement("DatiFatturaScheduling","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
	  						</tr>
							</tbody>
						</table>
					</div>
				</div>
			</div>
			<!--tabella milestone start-up fine-->
	  	</#if>
	  
	  <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='2' || el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='3'>
	  	<!-- tabella Prestazioni cliniche da protocollo inizio-->
    	<!--div id="monitoraggio" class="row">
				<div class="col-xs-12">
					<div class="table-header"> Prestazioni cliniche da protocollo </div>
					<div class="table-responsive">	
    				<table id="sample-table-2" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
	  							<th style="text-align:left;width:40%">Descrizione</th>
	  							<th style="text-align:left;width:5%">Tipologia attivit&agrave;</th>
	  							<th style="text-align:left;width:5%">Codice tariffario</th>
	  							<th style="text-align:left;width:5%">Tariffa SSR</th>
	  							<th style="text-align:left;width:5%">Transfer price</th>
	  							<th style="text-align:center;width:5%">Numero Pazienti</th>
	  							<th style="text-align:center;width:5%">Prestazioni Erogate</th>
	  							<th style="text-align:right;width:5%">Totale</th>
	  							<th style="text-align:center;width:5%">Visualizza dettaglio</th>
	  							<th style="text-align:center;width:5%">Fattura</th>
	  							<th style="text-align:center;width:5%">Visualizza fattura</th>
	  						</tr>
    					</thead>
							<tbody>
	  						<#assign parentEl=el/>
	  						<#list parentEl.getChildrenByType("VoceMonitoraggioFattura") as subEl>
	  							<#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='1'>
	  								<#assign linkedEl=subEl.getChildrenByType("LinkMonitoraggio")[0] >
	  								<tr data-order="${linkedEl.getfieldData("DatiLinkMonitoraggio","OrdinePrestazione")[0]!""}"  >
	  							
	  									<td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","Descrizione")[0]!""}</td>
	  									<td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","AttivitaDecode")[0]!""}</td>
	  									<td style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","Codice")!""}</td>
	  									<td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","SSN")!""}</td>
	  									<td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","TransferPrice")!""}</td>
	  									
	  									<td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPaz")[0]!""}</td>
	  									<td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPrestazioni")[0]!""}</td>
	  									<td id="totale1_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiMonitoraggioFattura","Totale")[0]!""}</td>
	  									<td style="text-align:center;"><#if (subEl.getChildren()?? && subEl.getChildren()?size gt 0)><a href='${subEl.getId()}'><img width="20" height="20" src="/img/details.png"></img></a><#else>n.a.</#if></td>
	  									<td id="giulio" style="text-align:center;"><form id="${subEl.id}" name="fattura" ><@SingleFieldNoLabel "DatiVoceFattura" "SelectFattura" subEl userDetails edit/></form> </td>
	  									<td style="text-align:center;"><#if (subEl.getFieldDataCode("DatiVoceFattura","SelectFattura")!="0" && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?? && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?size gt 0)><a href='${subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
	  								</tr>
	  							</#if>
	  						</#list>
	  					</tbody>
						</table>
					</div>
				</div>
			</div-->
			<!-- tabella Prestazioni cliniche da protocollo fine-->

	  	<!-- tabella Prestazioni cliniche a richiesta / altre prestazioni per paziente inizio-->
			<#assign vociMonitoraggio=parentEl.getChildrenByType("VoceMonitoraggioFattura") />
			<#if (vociMonitoraggio?? && vociMonitoraggio?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
			<div id="richiesta" class="row">
				<div class="col-xs-12">
					<div class="table-header"> Prestazioni/Attività aggiuntive</div>
					<div class="table-responsive">	
    				<table id="sample-table-3" class="table table-striped table-bordered table-hover">
							<thead>
								<tr>
	  							<th style="text-align:left;width:40%">Descrizione</th>
	  							<th style="text-align:left;width:5%">Tipologia attivit&agrave;</th>
	  							<th style="text-align:left;width:5%">Codice tariffario</th>
	  							<th style="text-align:left;width:5%">Tariffa SSR</th>
	  							<th style="text-align:left;width:5%">Transfer price</th>
	  							<!--th style="text-align:center;width:5%">Numero Pazienti</th-->
	  							<th style="text-align:center;width:5%">Prestazioni Erogate</th>
	  							<th style="text-align:right;width:5%">Totale</th>
	  							<!--th style="text-align:center;width:5%">Visualizza dettaglio</th-->
	  							<th style="text-align:center;width:5%">Fattura</th>
	  							<th style="text-align:center;width:5%">Visualizza fattura</th>
	  						</tr>
    					</thead>
							<tbody>
	  						<#list vociMonitoraggio as subEl>
	  							<#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='2'>
	  								<tr>
	  									<td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","Descrizione")[0]!""}</td>
	  									<td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","AttivitaDecode")[0]!""}</td>
	  									<td style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","Codice")!""}</td>
	  									<td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","SSN")!""}</td>
	  									<td class="to-money" style="text-align:left;"><#if subEl.getFieldDataString("DatiMonitoraggioFattura","TransferPrice")!=""  >${subEl.getFieldDataString("DatiMonitoraggioFattura","TransferPrice")!""}<#else>N.A,</#if></td>
	  									
	  									<!--td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPaz")[0]!""}</td-->
	  									<td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPrestazioni")[0]!""}</td>
	  									<td id="totale2_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiMonitoraggioFattura","Totale")[0]!""}</td>
	  									<!--td style="text-align:center;"><#if (subEl.getChildren()?? && subEl.getChildren()?size gt 0)><a href='${subEl.getId()}'><img width="20" height="20" src="/img/details.png"></img></a><#else>n.a.</#if></td-->
	  									<td id="giulio"style="text-align:center;"><form id="${subEl.id}" name="fattura" ><@SingleFieldNoLabel "DatiVoceFattura" "SelectFattura" subEl userDetails edit/></form></td>
	  									<td style="text-align:center;"><#if (subEl.getFieldDataCode("DatiVoceFattura","SelectFattura")!="0" && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?? && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?size gt 0)><a href='${subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
	  								</tr>
	  							</#if>
	  						</#list>
	  					</tbody>
						</table>
					</div>
				</div>
			</div>
			</#if>
			<!-- tabella Prestazioni cliniche a richiesta / altre prestazioni per paziente fine-->
			<!-- tabella Voci Pazienti Fatturabili inizio-->
			<#assign vociPazienti=parentEl.getChildrenByType("VocePazientiFattura") />
			<#if (vociPazienti?? && vociPazienti?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
				<div class="table-header"> Pazienti Fatturabili</div>
				<div class="table-responsive">
				<table id="sample-table-3" class="table table-striped table-bordered table-hover">
					<thead>
					<tr>
						<th style="text-align:left;width:40%">Descrizione</th>
						<th style="text-align:left;width:40%">Nr. pazienti</th>
						<th style="text-align:left;width:5%">Importo totale</th>
						<th style="text-align:center;width:5%">Fattura</th>
						<th style="text-align:center;width:5%">Visualizza fattura</th>
					</tr>
					</thead>
					<tbody>
					<#list vociPazienti as subEl>
					<#if (subEl.id)?? && subEl.getfieldData("DatiVoceFattura","Tipologia")?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='8'>
					<tr>
						<td style="text-align:left;">${subEl.getFieldDataString("DatiPazientiFattura","Descrizione")}</td>
						<td style="text-align:left;">${subEl.getFieldDataString("DatiPazientiFattura","NumPaz")}</td>
						<td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiPazientiFattura","Totale")!""}</td>
						<td id="vincenzo"style="text-align:center;"><form id="${subEl.id}" name="fattura" ><@SingleFieldNoLabel "DatiVoceFattura" "SelectFattura" subEl userDetails edit/></form></td>
						<td style="text-align:center;"><#if (subEl.getFieldDataCode("DatiVoceFattura","SelectFattura")!="0" && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?? && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?size gt 0)><a href='${subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
					</tr>
					</#if>
				</#list>
				</tbody>
				</table>
			</div>
			</div>
			</div>
			</#if>
			<!-- tabella Voci Pazienti fatturabili fine-->
			<!-- tabella Voci Aggiuntive Fattura  inizio-->
			<#assign vociAggiuntive=parentEl.getChildrenByType("VoceAggiuntivaFattura") />
			<div id="richiesta" class="row">
				<div class="col-xs-12">
					<div class="table-header">Voci aggiuntive in fattura
					<#list model['getCreatableElementTypes'] as docType>
						<#if docType.typeId="VoceAggiuntivaFattura" && edit>
						<div style="float:right;margin-bottom: 5px"><input type="button" class="btn btn-secondary btn-sm btn-spaced" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Aggiungi voce aggiuntiva"></div>
						</#if>
					</#list>
					</div>
					<div class="table-responsive">
						<table id="sample-table-3" class="table table-striped table-bordered table-hover">
							<thead>
							<tr>
								<th style="text-align:left;width:40%">Descrizione</th>
								<th style="text-align:left;width:5%">Importo totale</th>
								<th style="text-align:center;width:5%">Fattura</th>
								<th style="text-align:center;width:5%">Visualizza fattura</th>
							</tr>
							</thead>
							<tbody>
							<#list vociAggiuntive as subEl>
							<#if (subEl.id)?? && subEl.getfieldData("DatiVoceFattura","Tipologia")?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='6'>
							<tr>
								<td style="text-align:left;">${subEl.getFieldDataString("DatiAggiuntivaFattura","Descrizione")}</td>
								<td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiAggiuntivaFattura","Totale")!""}</td>
								<td id="vincenzo"style="text-align:center;"><form id="${subEl.id}" name="fattura" ><@SingleFieldNoLabel "DatiVoceFattura" "SelectFattura" subEl userDetails edit/></form></td>
								<td style="text-align:center;"><#if (subEl.getFieldDataCode("DatiVoceFattura","SelectFattura")!="0" && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?? && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?size gt 0)><a href='${subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
							</tr>
							</#if>
							</#list>
						</tbody>
						</table>
					</div>
				</div>
			</div>
			<!-- tabella Voci Aggiuntive Fattura fine-->
		  	<!-- tabella Recupero Riduzioni Fattura  inizio-->
			<#assign vociRiduzioni=parentEl.getChildrenByType("VoceRiduzioneFattura") />
			<#if (vociRiduzioni?? && vociRiduzioni?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
			<div id="richiesta" class="row">
				  <div class="col-xs-12">
					  <div class="table-header"> Riduzioni in precedenti fatture da recuperare </div>
					  <div class="table-responsive">
						  <table id="sample-table-3" class="table table-striped table-bordered table-hover">
							  <thead>
							  <tr>
								  <th style="text-align:left;width:40%">N.ro Riferimento Fattura</th>
								  <th style="text-align:left;width:5%">Importo da recuperare</th>
								  <th style="text-align:center;width:5%">Fattura</th>
								  <th style="text-align:center;width:5%">Visualizza fattura</th>
							  </tr>
							  </thead>
							  <tbody>
							  <#list vociRiduzioni as subEl>
								  <#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='5'>
									  <tr>
										  <td style="text-align:left;">
											  <#if subEl.getFieldDataElement("DatiRiduzioneFattura","LinkRiduzione")?? && subEl.getFieldDataElement("DatiRiduzioneFattura","LinkRiduzione")?size gt 0>
												  <a href='${subEl.getFieldDataElement("DatiRiduzioneFattura","LinkRiduzione")[0].getParent().getId()}'>${subEl.getFieldDataElement("DatiRiduzioneFattura","LinkRiduzione")[0].getParent().getId()}</img></a>
												  <#else>n.a.
											  </#if>
										  </td>
										  <td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiRiduzioneFattura","ImportoRecuperato")!""}</td>
										  <td id="vincenzo"style="text-align:center;"><form id="${subEl.id}" name="fattura" ><@SingleFieldNoLabel "DatiVoceFattura" "SelectFattura" subEl userDetails edit/></form></td>
										  <td style="text-align:center;"><#if (subEl.getFieldDataCode("DatiVoceFattura","SelectFattura")!="0" && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?? && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?size gt 0)><a href='${subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
									  </tr>
								  </#if>
							  </#list>
							  </tbody>
						  </table>
					  </div>
				  </div>
		  	</div>
			</#if>
		  <!-- tabella Recupero Riduzioni Fattura fine-->
	 	</#if>

	  <#assign vociScheduling=parentEl.getChildrenByType("VoceSchedulingFattura") />
	  <#if (vociScheduling?? && vociScheduling?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')> 
	  	<!-- tabella Prestazioni/servizi sullo studio inizio-->
    	<div class="row" id="studio" >
				<div class="col-xs-12">
					<div class="table-header"> Prestazioni/servizi sullo studio </div>
					<div class="table-responsive">	
    				<table id="sample-table-4" class="table table-striped table-bordered table-hover">
							<thead>
								<tr data-order="0">
	  							<th style="text-align:left;width:30%">Descrizione</th>
	  							<th style="text-align:left;width:30%">Tipologia attivit&agrave;</th>
	  							<th style="text-align:center;width:30%">Voce in fattura</th>
	  							<th style="text-align:center;width:10%">Rimborsabile</th>
	  							<th style="text-align:right;width:10%">Totale</th>
	  							<th style="text-align:center;width:10%">Fattura</th>
	  							<th style="text-align:center;width:10%">Visualizza fattura</th>
	  						</tr>
	  					</thead>
							<tbody>
    	  				<#list vociScheduling as subEl>
	  							<#if (subEl.id)??>
	  							<tr>
	  								<td style="text-align:left;">${subEl.getfieldData("DatiSchedulingFattura","Descrizione")[0]!""}</td>
	  								<td style="text-align:left;">${subEl.getfieldData("DatiSchedulingFattura","AttivitaDecode")[0]!""}</td>
	  								<td style="text-align:center;">${subEl.getfieldData("DatiSchedulingFattura","Gruppo")[0]!""}</td>
	  								<td style="text-align:center"><#if (subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")?size>0 && subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")[0]=='1')>si<#else>no</#if></td>
	  								<td style="text-align:right;" id="totale3_${subEl.id}">${subEl.getfieldData("DatiSchedulingFattura","Prezzo")[0]!""}</td>
    								<td style="text-align:center;"><form id="${subEl.id}" name="fattura" ><@SingleFieldNoLabel "DatiVoceFattura" "SelectFattura" subEl userDetails edit/></form></td>
    								<td style="text-align:center;"><#if (subEl.getFieldDataCode("DatiVoceFattura","SelectFattura")!="0" && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?? &&  subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?size gt 0)><a href='${subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
	  							</tr>
	  							</#if>
	  						</#list>
	  	  			</tbody>
						</table>
					</div>
				</div>
			</div>
			<!-- tabella Prestazioni/servizi sullo studio fine-->
	  </#if>
	  
	  <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='4'> 
	  	<!-- tabella Rimborsi a pi&egrave; di lista inizio-->
    	<div id="passthrough" class="row">
				<div class="col-xs-12">
					<div class="table-header"> Rimborsi a pi&egrave; di lista </div>
					<div class="table-responsive">	
    				<table id="sample-table-5" class="table table-striped table-bordered table-hover">
							<thead>
								<tr data-order="0">
	    						<th class="hidden-480">Descrizione</th>
	    						<th class="hidden-480">Totale</th>
	    						<th class="hidden-480">Fattura</th>
	    						<th class="hidden-480">Visualizza fattura d</th>
	    					</tr>
    					</thead>
							<tbody>
	    					<#list parentEl.getChildrenByType("VocePassThroughFattura") as subEl>
	    						<#if (subEl.id)??>
	    						<tr>
	    							<td class="hidden-480">${subEl.getfieldData("DatiPassThroughFattura","Descrizione")[0]}</td>
	    							<#--td>${subEl.getfieldData("DatiPassThroughPrezzo","Prezzo")[0]}</td-->
	    							<td class="hidden-480"><form id="${subEl.id}" name="prezzoPT" ><@SingleFieldNoLabel "DatiPassThroughPrezzo" "Prezzo" subEl userDetails edit/></form></td>
	    							<td class="hidden-480"><form id="${subEl.id}" name="fattura" ><@SingleFieldNoLabel "DatiVoceFattura" "SelectFattura" subEl userDetails edit/></form></td>
	    							<td class="hidden-480"><#if (subEl.getFieldDataCode("DatiVoceFattura","SelectFattura")!="0" && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?? && subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")?size gt 0)><a href='${subEl.getFieldDataElement("DatiVoceFattura","LinkFattura")[0].getId()}'><img width="40" height="50" src="/invoice.png"></img></a><#else>n.a.</#if></td>
	    						</tr>
	    						</#if>
	    					</#list>
							</tbody>
						</table>
					</div>
				</div>
			</div>
			<!-- tabella Rimborsi a pi&egrave; di lista fine-->
	  </#if>
        		
       				
		<div id="processes" style="float:left">
		 <#assign activeProcess=false/>
     <#if model["activeProcesses"]??>
        <#list model["activeProcesses"] as ist>
        	<#assign activeProcess=true/>
        </#list>
    	</#if>
    	<#if !activeProcess>
    		<#if model["availableProcesses"]??>
    	    <#list model["availableProcesses"] as wf>
    	    	<#list el.type.associatedWorkflows as p>
    	    		<#if !p.startOnCreate && p.enabled && wf.key=p.processKey>
    	    			<#assign alreadyTerminated=false/>
    	    			<#if model['terminatedProcesses']??>
									<#list model['terminatedProcesses'] as tpInst>
										<#if tpInst.getProcessDefinitionId()?split(":")[0]=wf.key>
											<#assign alreadyTerminated=true/>
										</#if>
									</#list>
								</#if>
								<#if !alreadyTerminated>
									<input id="startProcess" action="${wf.key}" class="submitButton round-button blue startProcess" type="button" value="${wf.name}"><br/>	
			        	</#if>
    	    		</#if>
    	    	</#list>
    	    </#list>
    		</#if>
    	</#if>
   
   
		
		<!--div id="saveButton" style="float:left">
    	<input style="float:left" class="round-button blue" type="button" value="Salva modifiche" onclick="javascript:saveAll();">
		</div-->
		
		<!--		
		<#list model['getCreatableElementTypes'] as docType>
		 	<#if docType.typeId="FatturaFeedback" && feedback==true && Feed==false>
				<br/>
				<input type="button" class="submitButton round-button blue" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.id}/${docType.id}';" value="Invia Richiesta di fatturazione">
		 	</#if>
		</#list>	 		
		-->
    	<br/><br/><br/><br/><br/>
    	<#--include "../helpers/child-box.ftl"/-->
    	<#include "../helpers/attached-file.ftl"/>
			<#--include "../helpers/comments.ftl"/-->
    </div>
    
    <!--#include "../helpers/events.ftl"/-->
