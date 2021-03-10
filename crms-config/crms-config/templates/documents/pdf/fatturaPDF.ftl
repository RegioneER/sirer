<#assign el=element/>
<#setting number_format="0.##" />
<#setting locale="it_IT">
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
.list-table {
}
.list-table th {
    background-color: #FFFFFF;
    border-bottom: 1px solid #4D80B4;
    border-left: 1px ridge #4D80B4;
    color: #5D8DBE;
    font-size: 12px;
    font-weight: bold;
    text-align: left;
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

.done{
	background-color: lightgreen;border-radius: 5px;padding:2px;
	vertical-align:middle;
}
.pending{
	background-color: #F98F1D;border-radius: 5px;padding:2px;
}

</style>

  <div class="row">
   		<div class="col-xs-9">

			<!--#include "../helpers/MetadataTemplate.ftl"/-->
	<div style="display: block">
	<!--div style="float: right"-->
	<div style="float: left">
	<!--#include "../helpers/information.ftl"/-->
	<!--#include "../helpers/actions.ftl"/-->
	<!--#include "../helpers/workflow.ftl"/-->
	<!--#include "../helpers/permission.ftl"/-->
	</div>  

	<#assign centro=el.getParent().getParent().getParent() />
	<#assign studio=centro.getParent() />
	
	<#assign sponsor="" />
    <#assign croString="" />
    <#assign codice="" />
    <#assign titolo="" />
    <#assign DenCentro="" />
    <#assign DenIstituto="" />
    <#assign DenDipartimento="" />
    <#assign DenUnitaOperativa="" />
    <#assign DenPrincInv="" />
				<#assign eudraCT=""/>
				<#assign tipoStudio=""/>

    <#assign idStudio = studio.getFieldDataString("UniqueIdStudio", "id") />
    <#if (studio.getFieldDataElement("datiPromotore", "promotore")?? && studio.getFieldDataElement("datiPromotore", "promotore")?size>0) >
            <#assign sp = studio.getFieldDataElement("datiPromotore", "promotore")[0] />
            <#assign sponsor = sp.getFieldDataString("DatiPromotoreCRO","denominazione") />
    </#if>
    <#if (studio.getFieldDataElement("datiCRO", "denominazione")?? && studio.getFieldDataElement("datiCRO", "denominazione")?size>0) >
            <#assign cro = studio.getFieldDataElement("datiCRO", "denominazione")[0] />
            <#assign croString = cro.getFieldDataString("DatiPromotoreCRO","denominazione") />
    </#if>
    <#if (studio.getfieldData("IDstudio","CodiceProt")?? && studio.getfieldData("IDstudio","CodiceProt")?size>0) >
           <#assign codice=studio.getFieldDataString("IDstudio","CodiceProt") />
    </#if>
    <#if (studio.getfieldData("IDstudio","TitoloProt")?? && studio.getfieldData("IDstudio","TitoloProt")?size>0) >
           <#assign titolo=studio.getFieldDataString("IDstudio","TitoloProt") />
    </#if>
				<#if (studio.getFieldDataString("datiStudio","eudractNumber")?? && studio.getFieldDataString("datiStudio","eudractNumber")!="" ) >
					<#assign eudraCT=studio.getFieldDataString("datiStudio","eudractNumber")/>
				</#if>
				<#if (studio.getFieldDataDecode("datiStudio","tipoStudio")?? && studio.getFieldDataDecode("datiStudio","tipoStudio")!="" ) >
					<#assign tipoStudio=studio.getFieldDataDecode("datiStudio","tipoStudio")/>
				</#if>

    
    <#assign DenCentro = centro.getFieldDataDecode("IdCentro","Struttura") />
				<!--#assign DenIstituto = centro.getFieldDataDecode("IdCentro","Istituto") /-->
				<!--#assign DenDipartimento = centro.getFieldDataDecode("IdCentro","Dipartimento") /-->
    <#assign DenUnitaOperativa = centro.getFieldDataDecode("IdCentro","UO") />
    <#assign DenPrincInv = centro.getFieldDataDecode("IdCentro","PI") />
    
	<#assign info>
	<table>

      <tr> <th>ID studio</th><td> ${idStudio}</td></tr>
      <tr> <th>Codice</th><td> ${codice}</td></tr>
      <tr> <th>Titolo</th><td> ${titolo}</td></tr>
						<tr> <th>Tipologia dello studio</th><td> ${tipoStudio}</td></tr>
						<tr> <th>Numero Eudract<em>(se applicabile)</em></th><td> ${eudraCT}</td></tr>
      <tr> <th>Promotore</th><td> ${sponsor}</td></tr>
      <tr> <th>CRO</th><td> ${croString}</td></tr>
      <tr> <th>Struttura</th> <td> ${DenCentro}</td></tr>
						<!--tr> <th>Istituto</th><td> ${DenIstituto}</td></tr-->
						<!--tr> <th>Dipartimento</th><td> ${DenDipartimento}</td></tr-->
      <tr> <th>Unita' operativa</th><td> ${DenUnitaOperativa}</td></tr>
      <tr> <th>Principal Investigator</th><td> ${DenPrincInv}</td></tr>
      </table>
	</#assign>
				<#assign intestatario="">
				<#assign piva="">
				<#assign indirizzo="">
				<#if el.getfieldData("DatiFatturaScheduling","DestinatarioRagSoc")[0]??>
					<#assign intestatario=el.getfieldData("DatiFatturaScheduling","DestinatarioRagSoc")[0] />
	
				</#if>
				<#if el.getfieldData("DatiFatturaScheduling","DestinatarioPIVA")[0]??>
					<#assign piva=el.getfieldData("DatiFatturaScheduling","DestinatarioPIVA")[0] />
				</#if>
				<#if el.getfieldData("DatiFatturaScheduling","DestinatarioIndirizzo")[0]??>
					<#assign indirizzo=el.getfieldData("DatiFatturaScheduling","DestinatarioIndirizzo")[0]/>
				</#if>
				<#assign intestazione>
					<table>
						<tr>
							<th >Spett.le</th>	<td >${intestatario}</td>
						</tr>
						<tr>
							<th >P.IVA / Codice Fiscale</th> <td >${piva}</td>
						</tr>
						<tr>
							<th >Indirizzo completo</th> <td >${indirizzo}</td>
						</tr>
					</table>
				</#assign>
	
				<#assign intestatario="">
				<#assign piva="">
				<#assign indirizzo="">
				<#if el.getfieldData("DatiFatturaScheduling","FatturazioneRagSoc")[0]??>
					<#assign intestatario=el.getfieldData("DatiFatturaScheduling","FatturazioneRagSoc")[0] />

				</#if>
				<#if el.getfieldData("DatiFatturaScheduling","FatturazionePIVA")[0]??>
					<#assign piva=el.getfieldData("DatiFatturaScheduling","FatturazionePIVA")[0] />
				</#if>
				<#if el.getfieldData("DatiFatturaScheduling","FatturazioneIndirizzo")[0]??>
					<#assign indirizzo=el.getfieldData("DatiFatturaScheduling","FatturazioneIndirizzo")[0]/>
				</#if>
				<#assign fatturazione>
					<table>
						<tr>
							<th >Spett.le</th>	<td >${intestatario}</td>
						</tr>
						<tr>
							<th >P.IVA / Codice Fiscale</th> <td >${piva}</td>
						</tr>
						<tr>
							<th >Indirizzo completo</th> <td >${indirizzo}</td>
						</tr>
					</table>
				</#assign>
		
				<div style="text-align:center" >
		
					<h2>Proforma fattura</h2>
				</div>
	
				<div style="text-align:left" >
					<table>
						<tr> <th>Numero Fattura di ${el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[1]}  </th><td> ${el.id}</td></tr>
						<!--tr> <th>Importo totale</th><td>${el.getFieldDataString("DatiFatturaWF","realeFattura")?number} &euro;</td></tr-->
					</table>
				</div>
				<div style="float:left; border:1px solid black;width:100%">
					<h4>Intestatario Fattura</h4>
					${intestazione}
				</div>
				<div style="float:left; border:1px solid black;width:1000%">
					<h4>Indirizzo Fatturazione</h4>
					${fatturazione}
				</div>
				<div style="clear: both"/>
				<div>
					<h4>Dati Studio</h4>
					${info}
				</div>
				<div style="float:left; border:1px solid black;width:1000%">
	<table>
						<tr> <th>Note CTO/TFA per emissione:</th><td> ${el.getFieldDataString("DatiFatturaWF","NoteApprovCTC")} </td></tr>
		</table>
				</div>

	     		
    						 		<#assign feedback=true/>	
    					 		
        		
        	<br/>	
        
			 	<#assign Feed=false/>
			
    							
				<#list el.getChildrenByType("FatturaFeedback") as subEl>
					<#assign feedback=true />
    				<#if subEl.id??>
    					
    					<#assign statoFatt=subEl.getfieldData("DatiFatturaFeedback","Feedback")[0]?split("###")[0]/>
    					
    					<#if statoFatt=="3">
    						<#assign Feed=true/>
    				  </#if>
    					
    				
						</#if>
    			</#list>	
	
      <#assign parentEl=el/>
       <#assign tipo1=[]/>
       <#assign tipo2=[]/>
      <#list parentEl.getChildrenByType("LinkVoceMonitoraggioFattura") as subEl1>
	    	
	    	<#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
	    	
	    	<#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='2'>
	    		<#assign tipo2=tipo2+[subEl]/>
	    	<#elseif (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='1' >
	    		<#assign tipo1=tipo1+[subEl]/>
	    	</#if>
	    	</#list>
	    <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='1'> 
	    	<!--tabella Milestone di fatturazione tempo zero inizio-->
    		<div class="row">
					<div class="col-xs-12">
						<div class="table-header"> Milestone di fatturazione tempo zero (inizio contratto) </div>
						<div class="table-responsive">
    					<table id="sample-table-1" class="table table-striped table-bordered table-hover" border="1" cellpadding="4" cellspacing="3" style="width:100%; border-collapse:collapsed;">
								<thead>
									<tr>
	    							<th style="text-align:left;width:70%">Descrizione</th>
	    							<th style="text-align:center;width:15%">Rimborsabile</th>
	    							<th style="text-align:right;width:15%">Totale</th>
	    						</tr>
    						</thead>
								<tbody>
									<#assign prezzoAcc="">
									<#assign startUp="">
									<#if el.getfieldData("DatiFatturaScheduling","AccontoAssoluto")[0]??>
										<#assign prezzoAcc=el.getfieldData("DatiFatturaScheduling","AccontoAssoluto")[0] />
										<#assign startUp="Anticipo sui pazienti" />	
									</#if>
									<#assign rimbo="">
									<#if el.getfieldData("DatiFatturaScheduling","StartUpRimborsabile")[0]??>
										<#assign rimbo=el.getFieldDataDecode("DatiFatturaScheduling","StartUpRimborsabile")/>
									</#if>
	    						<tr>
	    							<td style="text-align:left;">${startUp}</td>
	    							<td id="totale6_${el.id}" style="text-align:center;">${rimbo}</td>
													<td id="totale5_${el.id}" style="text-align:right;"><#attempt>${prezzoAcc?number}<#recover>${prezzoAcc} </#attempt> &euro;</td>
	    						</tr>
	    					</tbody>
							</table>
						</div>
					</div>
				</div>
				<!--tabella Milestone di fatturazione tempo zero fine-->
	    </#if>
	    
	    
	    <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='2' || el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='3' && (tipo1?size > 0) >
	    <fieldset>
	   	<!--legend>Prestazioni cliniche da protocollo</legend-->
	   		<div class="table-header"> Prestazioni cliniche da protocollo </div>
	     <table border="1" cellpadding="4" cellspacing="3" style="width:100%; border-collapse:collapsed;"  class=" table table-striped table-bordered table-hover" >
	    <thead>
	    	<tr>
	    		<th style="text-align:left;width:50%">Descrizione</th>
	    		<th style="text-align:center;width:15%">Numero Pazienti</th>
	    		<th style="text-align:center;width:20%">Prestazioni Erogate</th>
	    		<th style="text-align:right;width:15%">Totale</th>
	    	
	    	</tr>
	    	</thead>
	    	<tbody>
	    	
	    <#assign parentEl=el/>
	    <#list tipo1 as subEl>
	    	
	    	
	    	
	    	<#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='1'>
	    		
	    	<tr>
	    		<td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","Descrizione")[0]!""}</td>
	    		<td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPaz")[0]!""}</td>
	    		<td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPrestazioni")[0]!""}</td>
										<td id="totale1_${subEl.id}" style="text-align:right;">${subEl.getFieldDataString("DatiMonitoraggioFattura","Totale")?number} &euro;</td>
	    		
	    	</tr>
	    	
	    	</#if>
	    	
	    </#list>
	    </tbody>
	  </table>
	  </fieldset>
	     
	    <br/>
	    <#if (tipo2?size > 0)   >
	    
	    <fieldset>
	    <div class="table-header">Prestazioni cliniche a richiesta / altre prestazioni per paziente </div>
	    <table class="table table-striped table-bordered table-hover" border="1" cellpadding="4" cellspacing="3" style="width:100%; border-collapse:collapsed;">
	    <thead>
	    	<tr>
	    		<th style="text-align:left;width:50%">Descrizione</th>
	    		<th style="text-align:center;width:15%">Numero Pazienti</th>
	    		<th style="text-align:center;width:20%">Prestazioni Erogate</th>
	    		<th style="text-align:right;width:15%">Totale</th>
	    		
	    	</tr>
	    </thead>
	    <tbody>
	    	
	    
								<#list parentEl.getChildrenByType("LinkVoceMonitoraggioFattura") as subEl1>
	    	
									<#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
	    	
	    	<#if (subEl.id)?? && (subEl.getfieldData("DatiVoceFattura","Tipologia")[0])=='2'>
	    		
	    	<tr>
	    		<td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","Descrizione")[0]!""}</td>
											<!--td style="text-align:left;">${subEl.getfieldData("DatiMonitoraggioFattura","AttivitaDecode")[0]!""}</td>
											<td style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","Codice")!""}</td>
											<td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","SSN")!""}</td>
											<td class="to-money" style="text-align:left;">${subEl.getFieldDataString("DatiMonitoraggioFattura","TransferPrice")!""}</td-->

	    		<td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPaz")[0]!""}</td>
	    		<td style="text-align:center;">${subEl.getfieldData("DatiMonitoraggioFattura","NumPrestazioni")[0]!""}</td>
											<td id="totale2_${subEl.id}" style="text-align:right;">${subEl.getfieldData("DatiMonitoraggioFattura","Totale")[0]?number!""} &euro;</td>
											<!--td style="text-align:center;"><#if (subEl.getChildren()?? && subEl.getChildren()?size gt 0)><a href='${subEl.getId()}'><img width="20" height="20" src="/img/details.png"></img></a><#else>n.a.</#if></td-->
	    	</tr>
	    	
	    	</#if>
	    	
	    </#list>
	    </tbody>
	  </table>
	  </fieldset>
	    
	    <br/>
	  </#if>  
	 		</#if>
				<#assign riduzione=false />
				<#list el.getChildrenByType("RiduzioneFattura") as subEl>
					<#if subEl.id??>
						<#assign riduzione=true />
					</#if>
				</#list>

				<#if riduzione>
	    
					<#list el.getChildrenByType("RiduzioneFattura") as subEl>
						<div class="table-header">Riduzione fattura</div>
						<table class="table table-striped table-bordered table-hover" border="1" cellpadding="4" cellspacing="3" style="width:100%; border-collapse:collapsed;">
							<thead>
							<tr>
								<th style="text-align:left;width:80%">Riduzione </th>
								<th style="text-align:left;width:20%">Importo riduzione</th>
							</tr>
							</thead>
							<tbody>
							<#if subEl.id??>
								<tr>
									<#if subEl.getFieldDataCode("RiduzioneFattura","TipoRiduzione")?? && subEl.getFieldDataCode("RiduzioneFattura","TipoRiduzione")=="1" >
										<td style="text-align:left;">riduzione del ${subEl.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} ${subEl.getFieldDataDecode("RiduzioneFattura","TipoRiduzione")!""} da recuperare ${subEl.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}</td>
										<#else>
											<td style="text-align:left;">riduzione di ${subEl.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} ${subEl.getFieldDataDecode("RiduzioneFattura","TipoRiduzione")!""} da recuperare ${subEl.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}</td>
									</#if>

									<td style="text-align:center;" class="to-money">
										${el.getFieldDataString("DatiFatturaWF","riduzioneFattura")!""}
									</td>
	    
								</tr>

								</tbody>
								</table>
								</#if>
					</#list>
				</#if>
	    <#assign vociScheduling=parentEl.getChildrenByType("LinkVoceSchedulingFattura")>
	    
	    <#if (vociScheduling?? && vociScheduling?size gt 0 && el.getfieldData("DatiFattura","Tipologia")[0]!='4')>
	    <fieldset>
	    
	   	<!--legend>Prestazioni/servizi sullo studio</legend-->
	   	<div class="table-header"> Prestazioni/servizi sullo studio </div>
	     <table id="table_prest" class=" table table-striped table-bordered table-hover" border="1" cellpadding="4" cellspacing="3" style="width:100%; border-collapse:collapsed;">
	    	<thead>
	    	<tr>
	    		<th style="text-align:left;width:50%">Descrizione</th>
	    		<th style="text-align:center;width:20%">Voce in fattura</th>
	    		<th style="text-align:right;width:15%">Totale rimborsabile</th>
	    		<th style="text-align:right;width:15%">Totale</th>
	    	</tr>
	    </thead>
	    <tbody>
	    <#list vociScheduling as subEl1>
	    	
	    	<#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
	    	
	    	<#if (subEl.id)??>
	    	<tr id="riga_${subEl.id}">
	    		<td id="idDescr_${subEl.id}" style="text-align:left;">${subEl.getfieldData("DatiSchedulingFattura","Descrizione")[0]!""}</td>
	    		<td id="idGruppo_${subEl.id}" style="text-align:center;">${subEl.getfieldData("DatiSchedulingFattura","Gruppo")[0]!""}</td>
	    		<td id="idRimbo_${subEl.id}" style="text-align:right;"><#if (subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")?? && subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")?size>0 && subEl.getfieldData("DatiSchedulingFattura","Rimborsabile")[0]=='1')>si<#else>no</#if></td>
											<td id="totale3_${subEl.id}" style="text-align:right;">${subEl.getFieldDataString("DatiSchedulingFattura","Prezzo")?number} &euro;</td>
	    	</tr>
	    	
	    	</#if>
	    	
	    </#list>
	    </tbody>
	      </table>
	    </fieldset>  
	    </#if>
	    
					<#assign vociRiduzione=parentEl.getChildrenByType("LinkVoceRiduzioneFattura")>

						<#if (vociRiduzione?? && vociRiduzione?size gt 0 )>
							<fieldset>

								<!--legend>Prestazioni/servizi sullo studio</legend-->
								<div class="table-header">Recupero riduzioni fattura</div>
								<table class="table table-striped table-bordered table-hover" border="1" cellpadding="4" cellspacing="3" style="width:100%; border-collapse:collapsed;">
									<thead>
									<tr>
										<th style="text-align:left;width:80%">Riduzione </th>
										<th style="text-align:left;width:20%">Importo riduzione</th>
									</tr>
									</thead>
									<tbody>
									<#list vociRiduzione as subEl1>

										<#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
										<#assign mia_riduzione=subEl.getFieldDataElement('DatiRiduzioneFattura','LinkRiduzione')[0]/>
										<#if subEl.id??>
											<tr>
												<td style="text-align:left;">
													<#if mia_riduzione.getFieldDataCode("RiduzioneFattura","TipoRiduzione")?? && mia_riduzione.getFieldDataCode("RiduzioneFattura","TipoRiduzione")=="1" >
														riduzione del ${mia_riduzione.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} ${mia_riduzione.getFieldDataDecode("RiduzioneFattura","TipoRiduzione")!""} da recuperare ${mia_riduzione.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}
														<#else>
															riduzione di ${mia_riduzione.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")!""} ${mia_riduzione.getFieldDataDecode("RiduzioneFattura","TipoRiduzione")!""} da recuperare ${mia_riduzione.getFieldDataDecode("RiduzioneFattura","QuandoRecuperare")!""}
													</#if>
													relativa alla fattura n.ro ${mia_riduzione.getParent().getId()}
												</td>
												<td style="text-align:right;" class="to-money">
													${subEl.getFieldDataString("DatiRiduzioneFattura","ImportoRecuperato")?number} &euro;
												</td>

											</tr>

										</#if>

									</#list>
									</tbody>
								</table>
							</fieldset>
						</#if>

	    <br/>
	    <#if el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[0]=='4'> 
	  <fieldset>
	   	
	   	<div class="table-header">Rimborsi a pi&egrave; di lista </div>
	    
	     <table class="table table-striped table-bordered table-hover" border="1" cellpadding="4" cellspacing="3" style="width:100%; border-collapse:collapsed;">
	     <thead>
	    	<tr>
	    		<th style="text-align:left;width:60%">Descrizione</th>
	    		<th style="text-align:right;width:15%">Totale</th>
	    	</tr>
	    </thead>
	    <tbody>
	    <#list parentEl.getChildrenByType("LinkVocePassThroughFattura") as subEl1>
	    	
	    	<#assign subEl=subEl1.getFieldDataElement('LinkRichiesta','Richiesta')[0]/>
	    	
	    	<#if (subEl.id)??>
	    	<tr>
	    		<td style="text-align:left;">${subEl.getfieldData("DatiPassThroughFattura","Descrizione")[0]!""}</td>
											<td id="totale4_${subEl.id}" style="text-align:right;">${subEl.getFieldDataString("DatiPassThroughPrezzo","Prezzo")?number} &euro;</td>
	    	</tr>
	    	</#if>
	    	
	    </#list>
	    </tbody>
	      </table>
	     </fieldset>     
	    </#if>
	    
   		<!--/fieldset-->  	
   		<#assign assorb=parentEl.getChildrenByType("riassorbimentoAcconto")	/>
   		<#if (assorb?size >0)>
        		<div class="table-header">Voci a credito </div>
	    <table border="1" cellspacing="3" cellpadding="3" class="table table-striped table-bordered table-hover" style="width:100%; border-collapse:collapsed;">
	    <thead>
	    	<tr>
	    		<th style="text-align:left;width:80%">Descrizione</th>
	    		<th style="text-align:center;width:20%">Valore a credito detratto dal totale</th>
	    		
	    	</tr>
	    </thead>
	    <tbody>
	    	
	    
	    <#list assorb as subEl>
	    	
	    	
	    	
	    	
	    		
	    	<tr>
	    		<td style="text-align:left;">Quota acconto riassorbita</td>
									<td style="text-align:center;" class="to-money">${subEl.getFieldDataString("riassorbimentoAcconto","Valore")?number} &euro;</td>
	    		
	    	</tr>
	    	
	    	
	    	
	    </#list>
	    </tbody>
	  </table>
     </#if>  		
        <br/>	 		
					<div style="text-align:right" >
						<table border="1" cellspacing="3" cellpadding="3" class="table table-striped table-bordered table-hover" style="width:100%; border-collapse:collapsed;">
							<!--tr> <th>Numero Fattura di ${el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[1]}  </th><td> ${el.id}</td></tr-->
							<tr> <td style="text-align:left;">Importo totale</td><td style="text-align:right;" class="to-money">${el.getFieldDataString("DatiFatturaWF","realeFattura")?number} &euro;</td></tr>
						</table>
					</div>
              		
  		
        		 <br/><br/> <br/><br/>
    		<#--include "../helpers/child-box.ftl"/-->

				<#--include "../helpers/comments.ftl"/-->		
					
    </div>
 
    <!--#include "../helpers/events.ftl"/-->
 
			<div style="page-break-after: always"></div>
			<div style="text-align:center" >

				<h2>Riversamento</h2>
			</div>
			<#list parentEl.getChildrenByType("Ribaltamento") as elRibaltamento  >
				<#assign prezzoTotale=0 />
				<#assign ctcTotale=0 />
				<#assign transferTotale=0 />
				<#assign SSNTotale=0 />
				<#assign ribaltamentoTotale=0 />
				<#assign totalePercentualeFeas=0 />

				<table border="1" cellspacing="3" cellpadding="3" class="table table-striped table-bordered table-hover" style="width:100%; border-collapse:collapsed;">
					<#list elRibaltamento.getChildrenByType("CDCRibaltamento") as subEl>

						<#assign ctc=subEl.getfieldData("CDCSummary", "Prezzo")[0]?number-subEl.getfieldData("CDCSummary", "TransferPrice")[0]?replace(",", ".")?number />
						<#assign prezzo=subEl.getfieldData("CDCSummary", "Prezzo")[0]?replace(",", ".")?number />
						<#assign transfer=subEl.getfieldData("CDCSummary", "TransferPrice")[0]?replace(",", ".")?number />
						<#assign SSN=(subEl.getfieldData("CDCSummary", "SSN")[0]!0)?replace(",", ".")?number />
						<#if subEl.getFieldDataString("CDCSummary", "Ribaltamento")!="" >
							<#assign ribaltamento=(subEl.getFieldDataString("CDCSummary", "Ribaltamento"))?replace(",", ".")?number />
							<#elseif subEl.getFieldDataString("CDCSummary", "CDCCode")=="0" || subEl.getFieldDataString("CDCSummary", "CDCCode")=="99">
								<#assign ribaltamento=prezzo />
								<#else>
									<#assign ribaltamento=prezzo-transfer />
						</#if>


						<#assign prezzoTotale=prezzoTotale+prezzo />
						<#assign ctcTotale=ctcTotale+ctc />
						<#assign transferTotale=transferTotale+transfer />
						<#assign SSNTotale=SSNTotale+SSN />
						<#assign ribaltamentoTotale=ribaltamentoTotale+ribaltamento />




					</#list>
					<tr>
						<td><b>Totale Fattura: </b></td>
						<td class="prezzo">${prezzoTotale?string(",##0.00")} &euro;</td>
						<td class="prezzo"><b>Totale Riversamento: </b></td>
						<td class="prezzo" name="ribaltamentoTotale" style="font-weight: bold">
							${ribaltamentoTotale?string(",##0.00")} &euro;
						</td>
					</tr>
				</table>
				<table border="1" cellspacing="3" cellpadding="3" class="table table-striped table-bordered table-hover" style="width:100%; border-collapse:collapsed;">

					<thead>
					<tr>
						<th colspan="6">Riversamento attivit&agrave;/prestazioni</th>
					</tr>
					</thead>
					<thead>
					<tr>
						<th>Fondo</th>
						<th>Percentuale inserita in Fattibilit&agrave;</th>
						<th>Percentuale da riversare</th>
						<th>Valore da riversare &euro;</th>
						<th>Percentuale riversata</th>
						<th>Valore riversato &euro;</th>
					</tr>
					</thead>
					<tr>
						<td>Importi trattenuti dall'Azienda sanitaria come overhead</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc6Feas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc6")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc6Riversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc6UR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc6RiversatoUR")}</td>
					</tr>
					<tr>
						<td>Compensi al personale medico coinvolto nello studio clinico<br/>
							<!--label><b>note da Fattibilit&agrave;:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_noteCompensiDirigenteFeas")}</label><br/-->
							<label><b>note CTO/TFA:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_noteCompensiDirigente")}</label>
						</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiDirigenteFeas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiDirigente")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiDirigenteUR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiDirigenteRiversatoUR")}</td>
					</tr>
					<tr>
						<td>Compensi al personale non medico coinvolto nello studio clinico<br/>
							<!--label><b>note da Fattibilit&agrave;:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_noteCompensiRepartoFeas")}</label><br/-->
							<label><b>note CTO/TFA:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_noteCompensiReparto")}</label>
						</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiRepartoFeas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiReparto")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiRepartoUR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_compensiRepartoRiversatoUR")}</td>
					</tr>
					<tr>
						<td>Compensi destinati a fondo di U.O.<br/>
							<!--label><b>note da Fattibilit&agrave;:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc1NoteFeas")}</label><br/-->
							<label><b>note CTO/TFA:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc1Note")}</label></td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc1Feas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc1")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc1Riversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc1UR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc1RiversatoUR")}</td>
					</tr>
					<tr>
						<td>Compensi destinati all'Universit&agrave;</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc2Feas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc2")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc2Riversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc2UR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc2RiversatoUR")}</td>
					</tr>
					<tr>
						<td>Importo accantonato nel fondo Clinical Trial Office (CTO)/Task Force Aziendale (TFA)</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc3Feas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc3")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc3Riversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc3UR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc3RiversatoUR")}</td>
					</tr>
					<tr>
						<td>Importo accantonato nel fondo per gli studi no profit</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc4Feas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc4")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc4Riversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc4UR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc4RiversatoUR")}</td>
					</tr>
					<tr>
						<td>Importo accantonato nel fondo per la Sezione del CER (se applicabile)</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc7Feas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc7")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc7Riversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc7UR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc7RiversatoUR")}</td>
					</tr>
					<tr>
						<td>Fondo Centro Farmacologia clinica</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaFeas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercFarmacologia")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaUR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercFarmacologiaRiversatoUR")}</td>
					</tr>
					<tr>
						<td>Compenso per progetto universitario</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioFeas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercUniversitario")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioUR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePercUniversitarioRiversatoUR")}</td>
					</tr>
					<tr>
						<td>Altro<br/>
							<!--label><b>note da Fattibilit&agrave;:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_notePerc5Feas")}</label><br/-->
							<label><b>note CTO/TFA:</b> ${elRibaltamento.getFieldDataString("RibaltamentoFondi_notePerc5")}</label></td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc5Feas")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc5")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc5Riversato")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc5UR")}</td>
						<td>${elRibaltamento.getFieldDataString("RibaltamentoFondi_valorePerc5RiversatoUR")}</td>
					</tr>
					<tr>
						<td colspan="6"><span><b>Note CTO/TFA:</b>&nbsp;${elRibaltamento.getFieldDataString("RibaltamentoFondi_noteCTO")}</span></td>
					</tr>
				</table>
			</#list>
 	    </div>   
 	  
		<#--include "../helpers/fattura-status-bar.ftl"/-->
	
	    </div>