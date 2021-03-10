<#setting number_format="0.##">
<#setting locale="en_US">	
<#assign percentuale=0>
<#assign statusGreen="fa fa-check-circle-o green"/>
<#assign statusGrey="fa fa-circle-o grey" />
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey status9=statusGrey />

<#assign dataFeasibility="" />
<#--if el.getfieldData("statoValidazioneCentro","fattLocale")?? && el.getfieldData("statoValidazioneCentro","fattLocale")?size gt 0 && el.getFieldDataCode("statoValidazioneCentro","fattLocale")="1"-->
<#if el.getfieldData("statoValidazioneCentro","fattLocale")?? && el.getfieldData("statoValidazioneCentro","fattLocale")?size gt 0 >
	<#assign status1=statusGreen/>
		<#assign percentuale=percentuale+1>
		<#assign dataFeasibility=getFieldFormattedDate("statoValidazioneCentro","dataFattLocale",el) />
</#if>

<#assign idBudgetApproved=0 />
<#if el.getfieldData("statoValidazioneCentro", "idBudgetApproved")?? && el.getfieldData("statoValidazioneCentro", "idBudgetApproved")?size gt 0>
	<#assign status2=statusGreen />
	<#assign idBudgetApproved=el.getfieldData("statoValidazioneCentro", "idBudgetApproved")[0]?number />
	<#assign percentuale=percentuale+1>
</#if>

<#assign dataBudget="" />
<#list el.getChildrenByType("Budget") as budEl>
	<#assign idBud=budEl.getId()?number />
	<#if idBudgetApproved=idBud>
		<#assign dataBudget=getFieldFormattedDate("ChiusuraBudget", "Data",budEl) />
	</#if>
	<#break>
</#list>

<#if el.getfieldData("statoValidazioneCentro","valCTC")?? && el.getfieldData("statoValidazioneCentro","valCTC")?size gt 0 && el.getFieldDataCode("statoValidazioneCentro","valCTC")="1">
	<#assign status3=statusGreen />
	<#assign percentuale=percentuale+1>
</#if>

<#assign dataFirmaDG="" />
<#list el.getChildrenByType("Contratto") as conEl>
	<#list conEl.getChildrenByType("ContrattoFirmaDG") as firmaDGel>	
		<#if firmaDGel.getfieldData("DatiContrattoFirmaDG","dataFirma")?? && firmaDGel.getfieldData("DatiContrattoFirmaDG","dataFirma")?size gt 0>
			<#assign dataFirmaDG=getFieldFormattedDate("DatiContrattoFirmaDG", "dataFirma",firmaDGel) />
			<#assign status4=statusGreen />
			<#assign percentuale=percentuale+1>
			<#break>
		</#if>
	</#list>	
</#list>

<#assign dataParere="" />
<#assign statoParere="">
	<#list el.getChildrenByType("ParereCe") as elParere>
	<#assign statoParere=elParere.getfieldData("ParereCe","esitoParere")[0]>
	<#if statoParere="Parere favorevole">
		<#assign status5=statusGreen />
		<#assign dataParere=getFieldFormattedDate("ParereCe","dataParere",elParere) />
		<#assign percentuale=percentuale+1>
		<#break>
	</#if>
</#list>

<#assign dataMonit="" />
<#if el.getfieldData("DatiChiusuraWF", "dataCloseOut")?? && el.getfieldData("DatiChiusuraWF", "dataCloseOut")?size gt 0>
	<#assign status6=statusGreen />
	<#assign dataMonit=getFieldFormattedDate("DatiChiusuraWF","dataCloseOut",el) />
	<#assign percentuale=percentuale+1>
</#if>

<#assign dataEmissioneFatturaSaldo="" />
<#list el.getChildrenByType("Fatturazione") as fatturazioneEl>
	<#--Fatturazione:${fatturazioneEl.getId()}-->
	<#list fatturazioneEl.getChildrenByType("RichiestaFatturazione") as richFatEl>
		<#--RichiestaFatturazione: ${richFatEl.getId()}
		Tipo:${richFatEl.getFieldDataCode("DatiFattura","Tipologia")}-->
		<#if richFatEl.getFieldDataCode("DatiFattura","Tipologia")=="3"><#--saldo-->
			<#list richFatEl.getChildrenByType("Fattura") as fatturaEl>
				<#--Fatture:${fatturaEl.getId()}-->
				<#if fatturaEl.getfieldData("DatiFatturaWF","DataEmissione")?? && fatturaEl.getfieldData("DatiFatturaWF","DataEmissione")?size gt 0>
						<#--${getFieldFormattedDate("DatiFatturaWF","DataEmissione",fatturaEl)!""}-->
						<#assign dataEmissioneFatturaSaldo=getFieldFormattedDate("DatiFatturaWF", "DataEmissione",fatturaEl) />
						<#assign status7=statusGreen />
						<#assign percentuale=percentuale+1>
						<#break>
				</#if>
			</#list>
		</#if>
	</#list>
</#list>

<#assign dataChiusura="" />
<#if el.getfieldData("DatiChiusuraWF", "dataChiusuraAmm")?? && el.getfieldData("DatiChiusuraWF", "dataChiusuraAmm")?size gt 0>
	<#assign status8=statusGreen />
	<#assign dataChiusura=getFieldFormattedDate("DatiChiusuraWF","dataChiusuraAmm",el) />
	<#assign percentuale=percentuale+1>
</#if>

<#assign dataAperturaCentro="" />
<#list el.getChildrenByType("ArruolamentoPrimoPaz") as app>
	<#if !(app_has_next)>
		<#assign status9=statusGreen />
		<#if app.getfieldData("DatiArrPrimoPaz", "dataAperturaCentro")?? && app.getfieldData("DatiArrPrimoPaz", "dataAperturaCentro")?size gt 0>
			<#assign dataAperturaCentro=getFieldFormattedDate("DatiArrPrimoPaz", "dataAperturaCentro", app) />
			<#assign percentuale=percentuale+1>
		</#if>
	</#if>
</#list>

<#if byPassFirmaContratto=="1">
	<#assign percentuale=percentuale*100/8>
<#else>
	<#assign percentuale=percentuale*100/9>
</#if>

<#assign dataRitiro="" />
<#if el.getfieldData("DatiChiusuraWF", "dataRitiro")?? && el.getfieldData("DatiChiusuraWF", "dataRitiro")?size gt 0>
	<#assign dataRitiro>
		<p>
			<span style="color:red; font-weight: bold;">Data ritiro:</span>&nbsp;
			<span style="font-weight: bold;">${getFieldFormattedDate("DatiChiusuraWF","dataRitiro",el)}</span>
		</p>
	</#assign>
</#if>

<#assign noteRitiro="" />
<#if el.getfieldData("DatiChiusuraWF", "noteRitiro")?? && el.getfieldData("DatiChiusuraWF", "noteRitiro")?size gt 0>
	<#assign noteRitiro>
		<p>
			<span style="color:red; font-weight: bold;">Note ritiro:</span>&nbsp;
			<span style="font-weight: bold;">${el.getfieldData("DatiChiusuraWF","noteRitiro")[0]}</span><br/>
		</p>
	</#assign>
</#if>
				
<div  class="col-xs-3 sidebar-right">
<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
<i class="icon-chevron-right bigger-150"></i>
</div>	
<div class=" status-bar-content">
	
		<div class="col-xs-12 status-bar">
			<h2>Informazioni</h2>
			<#assign linkFattLoc="#" />
			<#assign onclickFattLoc="" />
			<#if userDetails.hasRole("CTC") || userDetails.hasRole("PI")>
				<#if getCode("datiStudio", "Profit", el.parent)=="">
					<#assign onclickFattLoc="alert('ATTENZIONE! Selezionare la tipologia di studio profit/no profit prima di generare il modulo di fattibilita\\' locale.');return false;" />
				</#if>
				<#if getCode("datiStudio", "Profit", el.parent)!="">
					<#assign linkFattLoc="${baseUrl}/app/documents/pdf/Fattibilita_Locale/${el.getId()}" />
				</#if>
				<a style="text-decoration:none;" onclick="${onclickFattLoc}" href="${linkFattLoc}"><img style="float:left;" width="40" height="40" src="/pdf.jpg"><span style="float:left;" >&nbsp;Genera modulo di impatto aziendale</span></a>
			</#if>
			<#if userDetails.hasRole("CTC")>
    			<@script>
                function showSelectQuarantena(){
                        var my_dialog=bootbox.dialog({
                            message : '<h3>Sei sicuro di voler togliere il centro dalla quarantena?</h3>',
                            title : '<label>Centro in quarantena</label>',
                            buttons : {
                                success : {
                                    label : "Confirm",
                                    className : "btn-success",
                                    callback : function() {
                                        $.ajax({
                                                type : "POST",
                                                url : "${baseUrl}/app/rest/documents/updateField/${el.getId()}",
                                                data : "name=Quarantena_quarantena&value=2###No&pk=${el.getId()}",
                                                dataType : "json",
                                                async: false, //aspetto che torni dalla chiamata ajax
                                                success : function(data) {
                                                    if (data.result != 'OK') {
                                                        bootbox.alert("ERRORE");
                                                    }
                                                    else{
                                                        location.reload(); 
                                                    }
                                                }
                                        });
                                    }
                                },
                                danger : {
                                    label : "Cancel",
                                    className : "btn-primary",
                                    callback : function (){
                                    
                                    }
                                }
                            }
                        });
                }
                </@script>
                <#if el.getFieldDataCode("Quarantena","quarantena")=="1">
                    <#assign onclickQuarantena="showSelectQuarantena();return false;" />
                    <div class="col-sm-12" style="clear:both;">
                        <div id="quarantena" class="alert alert-block alert-danger" style="">
                            <i class="fa fa-exclamation-circle red"></i> <a style="text-decoration:none;" onclick="${onclickQuarantena}" href="#"><span style="float:left;" >&nbsp;Centro in Quarantena</span></a>
                        </div>  
                    </div>
                   
                </#if>   
			</#if>
		</div>
	
		<div class="col-xs-12 status-bar">
		<h2>Avanzamento</h2>
		
		${dataRitiro}
		${noteRitiro}
		
		<div class="progress pos-rel" data-percent="${percentuale}%">
			<div class="progress-bar" style="width:${percentuale}%;"></div>
		</div>
		<div class="timeline-container timeline-style2">
			<div class="timeline-items">

				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Fattibilit&agrave; PI</span>
							<i class="my-timeline ${status1}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataFeasibility}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Chiusura budget (ultima versione)</span>
							<i class="my-timeline ${status2}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataBudget}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Valutazione CTO / TFA</span>
							<i class="my-timeline ${status3}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${getFieldFormattedDate("statoValidazioneCentro","dataValCTC",el)}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Valutazione Comitato Etico</span>
							<i class="my-timeline ${status5}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataParere}</span>
							</div>
						</div>
					</div>
				</div>

				<#if byPassFirmaContratto=="0">
					<div class="timeline-item clearfix">
						<div class="timeline-info">
									<span class="timeline-date">Firma contratto DG</span>
								<i class="my-timeline ${status4}"></i>
						</div>
						<div class="timeline-body widget-box transparent">
							<div class="widget-body">
								<div class="widget-main no-padding">
									<span class="timeline-date">${dataFirmaDG}</span>
								</div>
							</div>
						</div>
					</div>
				</#if>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Apertura centro</span>
							<i class="my-timeline ${status9}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataAperturaCentro}</span>
							</div>
						</div>

					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Close-Out visit (fine monitoraggio)</span>
							<i class="my-timeline ${status6}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataMonit}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Emissione fattura di saldo (fine fatturazione)</span>
							<i class="my-timeline ${status7}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataEmissioneFatturaSaldo}</span>
							</div>
						</div>
					</div>
				</div>			
			
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Chiusura amministrativa</span>
							<i class="my-timeline ${status8}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${dataChiusura}</span>
							</div>
						</div>

					</div>
				</div>
				
			</div>
		</div>
		</div>
		</div>
		</div>