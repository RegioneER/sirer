<style>
.status-bar {
    margin-top: 0px;
}
</style>

<#setting number_format="0.##">
<#setting locale="en_US">
<#assign percentuale=0 />
<#assign totale=7 />
<#assign statusGreen="fa fa-check-circle-o green"/>
<#assign statusRed="icon-remove-circle red"/>
<#assign statusGrey="fa fa-circle-o grey" />
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey status9=statusGrey status10=statusGrey status11=statusGrey status12=statusGrey status13=statusGrey status14=statusGrey/>

<#assign prot="" />
<#assign destinatario="" />
<#assign linkFirma="" />
<#assign dataFirma="" />


<#assign dataApprSR="" />		
<#if el.getfieldData("preFirmaContrattoWF","dataApprSR")?? && el.getfieldData("preFirmaContrattoWF","dataApprSR")?size gt 0>
	<#assign dataApprSR=getFieldFormattedDate("preFirmaContrattoWF", "dataApprSR", el) />		
	<#assign status7=statusGreen />
	<#assign percentuale=percentuale+1>
</#if>

<#assign fineValidita="" />		
<#if el.getfieldData("preFirmaContrattoWF","fineValidita")?? && el.getfieldData("preFirmaContrattoWF","fineValidita")?size gt 0>
	<#assign fineValidita=getFieldFormattedDate("preFirmaContrattoWF", "fineValidita", el) />
</#if>

<#assign dataInvioSP="" />	
<#if el.getfieldData("preFirmaContrattoWF","dataInvioSP")?? && el.getfieldData("preFirmaContrattoWF","dataInvioSP")?size gt 0>
	<#assign dataInvioSP=getFieldFormattedDate("preFirmaContrattoWF", "dataInvioSP", el) />
	<#assign status8=statusGreen />
	<#assign percentuale=percentuale+1>		
</#if>

<#assign dataRicezFirmSP="" />	
<#if el.getfieldData("preFirmaContrattoWF","dataRicezFirmSP")?? && el.getfieldData("preFirmaContrattoWF","dataRicezFirmSP")?size gt 0>
	<#assign dataRicezFirmSP=getFieldFormattedDate("preFirmaContrattoWF", "dataRicezFirmSP", el) />		
	<#assign status9=statusGreen />
	<#assign percentuale=percentuale+1>
</#if>

<#assign dataTrasmContrSR="" />	
<#if el.getfieldData("ValiditaContratto","dataTrasmContrSR")?? && el.getfieldData("ValiditaContratto","dataTrasmContrSR")?size gt 0>
	<#assign dataTrasmContrSR=getFieldFormattedDate("ValiditaContratto", "dataTrasmContrSR", el) />
	<#assign status10=statusGreen />
	<#assign percentuale=percentuale+1>
</#if>
	
<#list el.getChildrenByType("LettAccFirmaContr") as child>
	<#if child.id?? && child.file??>
		<#assign FirmaRespSR="true">
			<!--span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Firma Responsabile SR:&nbsp;&nbsp;</span>
			<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Si</b> &nbsp;</span-->
			<#--a href="${baseUrl}/app/documents/detail/${child.id}"-->
			<#assign linkFirma="${baseUrl}/app/documents/detail/${child.id}" />
			<!--Prot:&nbsp; ${child.getfieldData("Step1Contr", "numProt")[0]}-->
			<#assign prot=child.getfieldData("Step1Contr", "numProt")[0] />
			<!--Data firma:&nbsp; ${child.getfieldData("Step1Contr", "dataFirma")[0].time?date?string.short}-->
			<!--Dest:&nbsp; ${child.getfieldData("Step1Contr", "dest")[0]?split("###")[1]}&nbsp; -->
			<#assign destinatario=child.getfieldData("Step1Contr", "dest")[0]?split("###")[1] />
			<#--/a-->
				&nbsp;							 
			<!--
			<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child.getfieldData("Step1Contr", "selectFile")[0]?split("###")[0]?split("_")[1]}/${child.getfieldData("Step1Contr", "selectFile")[0]?split("###")[0]?split("_")[0]}">
				Corpus
				<img src="/Document-icon.png" width="30" height="30">
				</a>
			<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child.getfieldData("Step1Contr", "selectFile12")[0]?split("###")[0]?split("_")[1]}/${child.getfieldData("Step1Contr", "selectFile12")[0]?split("###")[0]?split("_")[0]}">
				All. A
				<img src="/Document-icon.png" width="30" height="30">
				</a>
			<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child.getfieldData("Step1Contr", "selectFile13")[0]?split("###")[0]?split("_")[1]}/${child.getfieldData("Step1Contr", "selectFile13")[0]?split("###")[0]?split("_")[0]}">
				All. B
				<img src="/Document-icon.png" width="30" height="30">
				</a>
			<#if child.getfieldData("Step1Contr", "selectFile14")?? && child.getfieldData("Step1Contr", "selectFile14")?size gt 0>
				<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child.getfieldData("Step1Contr", "selectFile14")[0]?split("###")[0]?split("_")[1]}/${child.getfieldData("Step1Contr", "selectFile14")[0]?split("###")[0]?split("_")[0]}">
					Altri allegati
					<img src="/Document-icon.png" width="30" height="30">
				</a>
		  </#if>
		  -->
		<#assign status1=statusGreen/>
		<#assign percentuale=percentuale+1 />
		<#assign dataFirma=getFieldFormattedDate("Step1Contr", "dataFirma", child) />
	</#if>
</#list>

<#assign prot2="" />
<#assign destinatario2="" />
<#assign linkFirma2="" />
<#list el.getChildrenByType("LettAccFirmaContr2") as child2>
	<#if child2.id?? && child2.file??>
		<#assign FirmaRespSR2="true">
			<!--span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Seconda Firma Responsabile SR:&nbsp;&nbsp;</span>
			<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Si</b> &nbsp;</span-->
			<!--a href="${baseUrl}/app/documents/detail/${child2.id}"-->
			<#assign linkFirma2="${baseUrl}/app/documents/detail/${child2.id}" />
			<!--Prot:&nbsp; ${child2.getfieldData("Step2Contr", "numProt2")[0]}-->
			<#assign prot2=child2.getfieldData("Step2Contr", "numProt2")[0] /> 
			<!--Data firma:&nbsp; ${child2.getfieldData("Step2Contr", "dataFirma2")[0].time?date?string.short} -->
			<!--Dest:&nbsp; ${child2.getfieldData("Step2Contr", "dest2")[0]?split("###")[1]}&nbsp; -->
			<#assign destinatario2=child2.getfieldData("Step2Contr", "dest2")[0]?split("###")[1] />
			<!--/a-->
				&nbsp;
			<!--
			<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile2")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile2")[0]?split("###")[0]?split("_")[0]}">
				Corpus
				<img src="/Document-icon.png" width="30" height="30">
				</a>
			<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile22")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile22")[0]?split("###")[0]?split("_")[0]}">
				All A.
				<img src="/Document-icon.png" width="30" height="30">
				</a>
			<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile23")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile23")[0]?split("###")[0]?split("_")[0]}">
				All B.
				<img src="/Document-icon.png" width="30" height="30">
				</a>
			<#if child2.getfieldData("Step2Contr", "selectFile24")?? && child2.getfieldData("Step2Contr", "selectFile24")?size gt 0>
				<a href="${baseUrl}/app/documents/getAttach/uniqueId/${child2.getfieldData("Step2Contr", "selectFile24")[0]?split("###")[0]?split("_")[1]}/${child2.getfieldData("Step2Contr", "selectFile24")[0]?split("###")[0]?split("_")[0]}">
					Altri allegati
					<img src="/Document-icon.png" width="30" height="30">
				</a>
			</#if>
			-->
			<#assign status5=statusGreen/>
			<#assign percentuale=percentuale+1>
			<#assign totale=totale+1 />
			<#assign dataFirma2=getFieldFormattedDate("Step2Contr", "dataFirma2", child2) />		
	</#if>
</#list>



<#assign FirmaPI="" />
<#assign dataFirmaPI="" />
<#list el.getChildrenByType("ContrattoFirmaPI") as childPI>
	<#if childPI.id??>
		<#assign FirmaPI="true">
		<#assign status14=statusGreen/>
		<#assign percentuale=percentuale+1>
		<#assign dataFirmaPI=getFieldFormattedDate("DatiContrattoFirmaPI", "dataFirma", childPI) />		
	</#if>
</#list>

<#assign FirmaDIP="" />
<#assign dataFirmaDIP="" />
	<#list el.getChildrenByType("ContrattoFirmaDIP") as childDIP>
	<#if childDIP.id??>
	<#assign FirmaDIP="true">
	<#assign status11=statusGreen/>
	<#assign percentuale=percentuale+1>
	<#assign dataFirmaDIP=getFieldFormattedDate("DatiContrattoFirmaDIP", "dataFirma", childDIP) />
</#if>
</#list>

<#assign FirmaDG="" />
<#assign dataFirmaDG="" />
<#list el.getChildrenByType("ContrattoFirmaDG") as childDG>
	<#if childDG.id??>
		<#assign FirmaDG="true">
		<#assign status12=statusGreen/>
		<#assign percentuale=percentuale+1>
		<#assign dataFirmaDG=getFieldFormattedDate("DatiContrattoFirmaDG", "dataFirma", childDG) />		
	</#if>
</#list>


<#assign dataContrattoMail="" />
<#if el.getfieldData("ValiditaContratto", "dataContrattoMail")[0]??>
	<#assign dataContrattoMail="true"/>
	<#assign dataContrattoMail=getFieldFormattedDate("ValiditaContratto", "dataContrattoMail", el) />
	<#assign status13=statusGreen />
	<#assign percentuale=percentuale+1>
</#if>


<#assign dataSponsor="" />
<#if el.getfieldData("ValiditaContratto", "dataSponsor")[0]??>
	<#assign inviatoSponsor="true"/>
	<!--span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Inviata al Promotore:&nbsp;&nbsp;</span>
	<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Si</b> &nbsp;</span-->
	<!--Data:&nbsp;<span class="span1">${getFieldFormattedDate("ValiditaContratto", "dataSponsor", el)}</span-->
	<#assign dataSponsor=getFieldFormattedDate("ValiditaContratto", "dataSponsor", el) />
	<#assign status3=statusGreen />
	<#assign percentuale=percentuale+1>
</#if>

<#assign armadio="" />
<#assign ripiano="" />
<#assign stanza="" />
<#assign classificatore="" />		
<#assign dataArchiviazione="" />
<#assign numeroRepertorio="" />
<#if el.getfieldData("ValiditaContratto", "armadio")[0]??>
	<#assign contrattoArchiviato="true"/>
	<!--span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Contratto archiviato:&nbsp;&nbsp;</span>
	<span style="background-color: lightgreen;border-radius: 5px;padding:2px;"><b>Si</b> &nbsp;</span>
	Armadio:&nbsp;<span class="span1">${el.getfieldData("ValiditaContratto","armadio")[0]?split("###")[1]}</span>
	Ripiano:&nbsp;<span class="span1">${el.getfieldData("ValiditaContratto","ripiano")[0]?split("###")[1]}</span-->
	<#assign armadio=el.getfieldData("ValiditaContratto","armadio")[0]?split("###")[1] />
	<#assign ripiano=el.getfieldData("ValiditaContratto","ripiano")[0]?split("###")[1] />
	<#assign stanza=el.getfieldData("ValiditaContratto","stanza")[0]?split("###")[1] />
	<#assign classificatore=el.getFieldDataString("ValiditaContratto","classificatore") />
	<#assign numeroRepertorio=el.getFieldDataString("ValiditaContratto","numeroRepertorio") />
			
	<#if el.getfieldData("ValiditaContratto","dataArchiviazione")?? && el.getfieldData("ValiditaContratto","dataArchiviazione")?size gt 0>
		<#assign dataArchiviazione=getFieldFormattedDate("ValiditaContratto", "dataArchiviazione", el) />		
	</#if>
	
	<#assign status4=statusGreen />
	<#assign percentuale=percentuale+1>	
	
</#if>

<div class="col-xs-2 status-bar">
	<h2>Informazioni</h2>

	<#-- if el.parent.getfieldData("statoValidazioneCentro", "idBudgetApproved")?? && el.parent.getfieldData("statoValidazioneCentro", "idBudgetApproved")?size gt 0>
		<#assign budId=el.parent.getfieldData("statoValidazioneCentro", "idBudgetApproved")[0] />
		<a style="text-decoration:none;" href="${baseUrl}/app/documents/download/excel2/${budId}" ><img style="float:left;" width="40" height="40" src="/Oficina-XLS-icon.png"> <span style="float:left;" >Scarica budget<br/> prezzi (Contratto)</span></a>
	</#if -->
			
	<#if FirmaRespSR=="true">
		<br/><br/>
		Firma:<br/>
		<a href="${linkFirma}">
			Numero Protocollo: ${prot}<br>
			Destinatario: ${destinatario}
		</a>
	</#if>	
	
	<#if FirmaRespSR2=="true">
		<br><br>
		Seconda firma:<br/>
		<a href="${linkFirma2}">
			Numero Protocollo: ${prot2}<br>
			Destinatario: ${destinatario2}
		</a>
	</#if>
	
	<br><br>
	
<#assign val1="false"/>
<#assign val2="false"/>
<#assign dataAppr="" />				
<#if el.getfieldData("ApprovDADSRETT", "Approvazione")[0]??>
	<#if el.getFieldDataCode("ApprovDADSRETT", "Approvazione")=="1">
		<#assign val1="true"/>
		Inizio validit&agrave;:&nbsp;<span class="span1"><b>${getFieldFormattedDate("ApprovDADSRETT", "dataInizioVal", el)}</b></span><br/>
		Fine validit&agrave;:&nbsp;<span class="span1"><b>${getFieldFormattedDate("ApprovDADSRETT", "dataFineVal", el)}</b></span>
		<#assign status2=statusGreen />
	</#if>
	<#if el.getFieldDataCode("ApprovDADSRETT", "Approvazione")=="2">
		<#assign status2=statusRed />
	</#if>
	<#assign percentuale=percentuale+1>
	<#assign dataAppr=getFieldFormattedDate("ApprovDADSRETT", "dataFirma", el) />
</#if>

<#if el.getfieldData("ApprovDADSRETT2", "Approvazione2")[0]?? && el.getFieldDataCode("ApprovDADSRETT2", "Approvazione2")=="1">
	<#assign val2="true"/>
	Inizio validit&agrave;:&nbsp;<span class="span1"><b>${getFieldFormattedDate("ApprovDADSRETT2", "dataInizioVal2", el)}</b></span>
		<br/>
	Fine validit&agrave;:&nbsp;<span class="span1"><b>${getFieldFormattedDate("ApprovDADSRETT2", "dataFineVal2", el)}</b></span>
	<#assign status6=statusGreen />
	<#assign percentuale=percentuale+1>
	<#assign totale=totale+1 />
	<#assign dataAppr2=getFieldFormattedDate("ApprovDADSRETT2", "dataFirma2", el) />
</#if>

	
	<br/>
	Armadio: <b>${armadio}</b> - Ripiano: <b>${ripiano}</b><br/>
	Stanza: <b>${stanza}</b> <br/>
	Classificatore: <b>${classificatore}</b><br/>
	Nr. Repertorio: <b>${numeroRepertorio}</b></br/>
<br/>


<#--if val1=="false" && val2=="false"-->
	Inizio validit&agrave;:&nbsp;<span class="span1"><b>${dataFirmaDG}</b></span>
		<br/>
	Fine validit&agrave;:&nbsp;<span class="span1"><b>${fineValidita}</b></span>
<#-- /#if -->


<br/>
<#if el.getChildrenByType("RinnovoContratto")?size gt 0 >
	<span class="span1"><br>Rinnovi:<br></span>
	<#list el.getChildrenByType("RinnovoContratto") as subEl>
		<#if subEl.id??>
			<a href="${baseUrl}/app/documents/detail/${subEl.id}">
				Fine validit&agrave;:&nbsp;<span class="span1">${getFieldFormattedDate("RinnovoContratto", "DataFineNuova", subEl)}</span>
			</a>
			<br/>
		</#if>
	</#list>
</#if>


</div>

<#assign percentuale=percentuale*100/totale>			
<div class="col-xs-2 status-bar">
		<h4>Avanzamento contratto</h4>
		<div class="progress pos-rel" data-percent="${percentuale}%">
			<div class="progress-bar" style="width:${percentuale}%;"></div>
		</div>
		<div class="timeline-container timeline-style2">
			<div class="timeline-items">
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Fine redazione contratto</span>
							<i class="my-timeline ${status7}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataApprSR}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Trasmissione a Promotore per firma</span>
							<i class="my-timeline ${status8}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataInvioSP}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Ricezione contratto firmato da Promotore</span>
							<i class="my-timeline ${status9}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataRicezFirmSP}</span>
							</div>
						</div>
					</div>
				</div>
				
				<#--
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Trasmissione contratto da SR a CTC</span>
							<i class="my-timeline ${status1}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataFirma}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Trasmissione contratto da Direzione Policlinico a CTC</span>
							<i class="my-timeline ${status2}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataAppr}</span>
							</div>
						</div>
					</div>
				</div>
				
				<#if FirmaRespSR2=="true">
					<div class="timeline-item clearfix">
						<div class="timeline-info">
									<span class="timeline-date">Seconda trasmissione contratto da SR a CTC</span>
								<i class="my-timeline ${status5}"></i>
						</div>
						<div class="timeline-body widget-box transparent">
							<div class="widget-body">
								<div class="widget-main no-padding">
									<span class="timeline-date">${dataFirma2}</span>
								</div>
							</div>
						</div>
					</div>
				</#if>
				
				<#if val2=="true">
					<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Seconda trasmissione contratto da Direzione Policlinico a CTC</span>
							<i class="my-timeline ${status6}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataAppr2}</span>
							</div>
						</div>
					</div>
				</div>
				</#if>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Trasmissione da CTC a SR</span>
							<i class="my-timeline ${status10}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataTrasmContrSR}</span>
							</div>
						</div>
					</div>
				</div>
				-->
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Firma Direttore Dipartimento / Istituto</span>
							<i class="my-timeline ${status11}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataFirmaDIP}</span>
							</div>
						</div>
					</div>
				</div>

				<div class="timeline-item clearfix">
					<div class="timeline-info">
						<span class="timeline-date">Firma PI</span>
						<i class="my-timeline ${status14}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataFirmaPI}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Firma DG / Delegato (inizio validit&agrave;)</span>
							<i class="my-timeline ${status12}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataFirmaDG}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Trasmissione contratto via mail a SP, PI e servizi coinvolti</span>
							<i class="my-timeline ${status13}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataContrattoMail}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Trasmissione contratto firmato a Promotore e PI</span>
							<i class="my-timeline ${status3}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataSponsor}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Archiviato</span>
							<i class="my-timeline ${status4}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataArchiviazione}</span>
							</div>
						</div>
					</div>
				</div>
				
				
			</div>
		</div>
	</div>

<#setting locale="it_IT">