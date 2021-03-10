
<#assign totale=4>
<#assign percentuale=0>
<#assign statusGreen="fa fa-check-circle-o green"/>
<#assign statusGrey="fa fa-circle-o grey" />
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey data1="" data2="" data3="" data4="" />

<#assign proFormaLink=false />
<#if getFieldFormattedDate("DatiFatturaWF", "DataApprovCTC", el)!="">
	<#assign status1=statusGreen/>
		<#assign percentuale=percentuale+1>
		<#assign data1=getFieldFormattedDate("DatiFatturaWF", "DataApprovCTC", el) />
		<#assign proFormaLink=true />
</#if>
	<#assign proFormaLink=true /> <#-- lo metto a true per far visualizzare anche se non è stata inviata alla ragioneria -->
<#assign proFormaLink=false /> <#-- SIRER-68 per ora lo commentiamo -->
<#if getFieldFormattedDate("DatiFatturaWF", "DataEmissione", el)!="">
	<#assign status2=statusGreen />
	<#assign data2=getFieldFormattedDate("DatiFatturaWF", "DataEmissione", el) />
	<#assign codiceFattura=el.getfieldData("DatiFatturaWF","CodiceFattura")[0]!"" />
	<#assign noteFattura=el.getfieldData("DatiFatturaWF","Note")[0]!"" />
	<#assign percentuale=percentuale+1>
</#if>


<#list el.getChildrenByType("FatturaFeedback") as subEl>
	
	
	<#assign status3=statusGreen />
	<#assign data3=getFieldFormattedDate("DatiFatturaFeedback", "Data", subEl) />
	<#if subEl.id?? && subEl.getfieldData("DatiFatturaFeedback","Feedback")[0]?? >
		
		<#assign statoFatt=subEl.getfieldData("DatiFatturaFeedback","Feedback")[0]?split("###")[0]/>
		
		<#if statoFatt=="1">
		
			<#assign status4=statusGreen />
			<#assign data4=getFieldFormattedDate("DatiFatturaFeedback", "Data", subEl) />
			<#break/>
	  </#if>
	</#if>
</#list>				

<#if status3!=statusGrey>
	<#assign percentuale=percentuale+1>
</#if>
<#if status4!=statusGrey>
	<#assign percentuale=percentuale+1>
</#if>



<#assign percentuale=percentuale*100/totale>
<div class="col-xs-3 sidebar-right">	
<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
<i class="icon-chevron-right bigger-150"></i>
</div>	
<div class=" status-bar-content">
<div class="col-xs-12 status-bar" >
	<h2>Informazioni</h2>
		<div>
			Fattura di ${el.getfieldData("DatiFattura","Tipologia")[0]?split("###")[1]}: <b>${el.id}</b><br/>
			<#assign totaleFattura="0"/>
			<#assign realeFattura="0"/>
			<#assign riduzione="0"/>
			<#assign riassorbimentoAcconto="0"/>
			<#assign assorb=parentEl.getChildrenByType("riassorbimentoAcconto")    />
			<#if (assorb?size >0)>
					<#list assorb as subEl>
						<#assign riassorbimentoAcconto=subEl.getFieldDataString("riassorbimentoAcconto","Valore") />
					</#list>
			</#if>
			<#if el.getfieldData("DatiFatturaWF","realeFattura")[0]?? >
				<#assign totaleFattura=el.getfieldData("DatiFatturaWF","totaleFattura")[0]?number />
				<#assign realeFattura=el.getfieldData("DatiFatturaWF","realeFattura")[0]?number />
			</#if>
			<#if el.getfieldData("DatiFatturaWF","totaleFattura")[0]?? >
				<#assign totaleFattura=el.getfieldData("DatiFatturaWF","totaleFattura")[0]?number />
			</#if>
			<#if el.getfieldData("DatiFatturaWF","riduzioneFattura")[0]?? && el.getfieldData("DatiFatturaWF","riduzioneFattura")[0]!="" >
				<#assign riduzione=el.getfieldData("DatiFatturaWF","riduzioneFattura")[0]?number />
			<#else>
				<#list el.getChildrenByType("RiduzioneFattura") as currChild >
					<#if currChild.getFieldDataCode("RiduzioneFattura","TipoRiduzione")?? && currChild.getFieldDataCode("RiduzioneFattura","TipoRiduzione")[0]=="1" >
						<#-- percentuale -->
						<#assign perc=currChild.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")?number />
						<#if realeFattura?number gt 0 >
						<#assign riduzione=realeFattura*perc/100 />
						</#if>
					<#else>
						<#assign riduzione=currChild.getFieldDataString("RiduzioneFattura","QuantitaRiduzione")?number />
					</#if>
					<#assign realeFattura=realeFattura?number-riduzione?number />
				</#list>
			</#if>
			<div style="float:left">Importo Totale:</div><div style="float: right" id="totaleFattura_${el.id}"><b>${totaleFattura?number?string(",##0.00")} &euro;</b></div>
			<div style="clear: both;"></div>
			<#if riassorbimentoAcconto?number?string!="0">
				<div style="float:left">Quota Acconto Riassorbita:</div> <div style="float: right" id="totaleFattura_${el.id}"> <b>- ${riassorbimentoAcconto?number?string(",##0.00")} &euro;</b></div>
				<div style="clear: both;"></div>
			</#if>
			<#if riduzione?number?string!="0">
				<div style="float:left">Importo Riduzione:</div> <div style="float: right"  id="riduzione_${el.id}"><b>- ${riduzione?number?string(",##0.00")} &euro;</b></div>
				<div style="clear: both;"></div>
			</#if>
			<div style="float:left">Importo Fattura:</div> <div style="float: right;border-top: 2px solid black;"  id="realeFattura_${el.id}"><b>${realeFattura?number?string(",##0.00")} &euro;</b></div>
			<div style="clear: both;"><#if codiceFattura?? && codiceFattura!="" >Codice fattura: <b>${codiceFattura}</b><br/></#if>
			<#if noteFattura?? && noteFattura!="" >Note: <b>${noteFattura}</b><br/></#if></div>
		</div>
		<#if proFormaLink >
			<br/>
			<div>
				<a style="text-decoration:none;" href="${baseUrl}/app/documents/pdf/fatturaPDF/${el.getId()}"><img style="float:left;" src="/pdf.jpg" width="40" height="40"></a>
				<span style="float:left;height:40px;padding:10px 0px"><a href="${baseUrl}/app/documents/pdf/fatturaPDF/${el.getId()}" style="text-decoration:none;">&nbsp;Scarica pro-forma fattura</a></span>
			</div>
		</#if>
</div>

<div class="col-xs-12 status-bar">
		<h2>Avanzamento</h2>
		<div class="progress pos-rel" data-percent="${percentuale}%">
			<div class="progress-bar" style="width:${percentuale}%;"></div>
		</div>
		<div class="timeline-container timeline-style2">
			<div class="timeline-items">

				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Invio Ufficio amministrativo</span>
							<i class="my-timeline ${status1}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${data1}</span>
							</div>
						</div>
					</div>
				</div>
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Emissione</span>
							<i class="my-timeline ${status2}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${data2}</span>
							</div>
						</div>
					</div>
				</div>
				
				<#list el.getChildrenByType("FatturaFeedback") as currChild >
					<#assign importo=currChild.getFieldDataString("DatiFatturaFeedback","Importo") />
				<div class="timeline-item clearfix">
					<div class="timeline-info">
									<span class="timeline-date">${currChild.getFieldDataDecode("DatiFatturaFeedback","Feedback")} <#if importo!="">(Importo: <span class="to-money">${importo}</span>)</#if></span>
								<i class="my-timeline ${statusGreen}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
									<span class="timeline-date">${getFieldFormattedDate("DatiFatturaFeedback", "Data", currChild)}</span>
							</div>
						</div>
					</div>
				</div>
				</#list>
				
				

				<#if status4=statusGrey>
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Incassata</span>
							<i class="my-timeline ${status4}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${data4}</span>
							</div>
						</div>
					</div>
				</div>
				</#if>
				
				
				
			</div>
		</div>
				
			</div>
		
		</div>
		</div>