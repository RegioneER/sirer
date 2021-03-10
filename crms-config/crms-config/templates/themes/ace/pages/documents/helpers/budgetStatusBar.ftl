<#setting number_format="0.##">
<#setting locale="en_US">
<#assign percentuale=0>
<#assign totale=3>
<#assign statusGreen="fa fa-check-circle-o green"/>
<#assign statusGrey="fa fa-circle-o grey" />
<#assign statusRed="icon-remove-circle red" />
<#if budgetBase?? >
	<#assign budget=budgetBase />
</#if>
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey />

<#assign data1="" />
<#assign data2="" />
<#assign data3="" />
<#if (budget.getfieldData("ApprovazioneClinica","Approvato")?? && budget.getfieldData("ApprovazioneClinica","Approvato")?size>0 && budget.getfieldData("ApprovazioneClinica","Approvato")[0]=="1")>
	<#if budget.getFieldDataString("ApprovazioneClinica","Approvato")=="1">
		<#assign status1=statusGreen/>
	<#else>
		<#assign status1=statusRed/>
	</#if>
		<#assign percentuale=percentuale+1>
		<#assign data1=getFieldFormattedDate("ApprovazioneClinica","Data",budget) />
</#if>

<#if (budget.getfieldData("ChiusuraBudget","Chiuso")?? && budget.getfieldData("ChiusuraBudget","Chiuso")?size>0 && budget.getfieldData("ChiusuraBudget","Chiuso")[0]=="1")>
	<#assign status2=statusGreen />
	<#assign data2=getFieldFormattedDate("ChiusuraBudget","Data",budget) />
	<#assign percentuale=percentuale+1>
</#if>


<#if (center.getfieldData("statoValidazioneCentro","idBudgetApproved")?? && center.getfieldData("statoValidazioneCentro","idBudgetApproved")?size>0 && center.getfieldData("statoValidazioneCentro","idBudgetApproved")[0]==budget.getId()?string)>
	<#assign status3=statusGreen />
	<#assign data3=data2 />
	<#assign percentuale=percentuale+1>
</#if>



<#assign percentuale=percentuale*100/totale>	
<div class="col-xs-3 sidebar-right">	
<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
<i class="icon-chevron-right bigger-150"></i>
</div>	
<div class=" status-bar-content">
		<div class="col-xs-12 status-bar">
				<h2>Informazioni</h2>
				<b><@elementTitle center/></b><br>
				<#setting locale="it_IT">
				Creato il: <b>${budget.creationDt.time?datetime?string.medium}</b><br>
				Modificato il: <b><#if budget.lastUpdateDt?? >${budget.lastUpdateDt.time?datetime?string.medium}</#if></b><br>
				Autore: <b><#if budget.lastUpdateUser?? >${budget.lastUpdateUser}<#else>${budget.createUser}</#if></b><br><br>
				<#setting locale="en_US">
		 	Versione budget:
				<#if budget??>
					<#if budget.type.titleField?? || budget.type.titleRegex??>
				    <b><@elementTitle budget/> ( v. <#if (budget.getfieldData("Budget","Versione")?size>0) >
				    	 ${budget.getfieldData("Budget","Versione")[0]}
				    	</#if> <#if (budgetStudio?? && budgetStudio.getfieldData("BudgetCTC","Tipologia")?? && budgetStudio.getfieldData("BudgetCTC","Tipologia")?size>0) >${getDecode("BudgetCTC","Tipologia",budgetStudio)}</#if>)
					</#if>
				<#else>
				</#if>
		</div>
		<#-- div class="col-xs-12 status-bar">
				<h2>Emendamenti</h2>
				<#if budget.getFieldDataDecode("Emendamento","Emendamento")?? && budget.getFieldDataDecode("Emendamento","Emendamento")!="">
					<#assign labelEme="Emendamento: "+budget.getFieldDataDecode("Emendamento","Emendamento") >
				<#else>
					<#assign labelEme="Associa emendamento al budget" >
				</#if>
				<@templateModalForm "Emendamento" budget userDetails true labelEme checks />
		</div -->
		<#-- if spechiettoBracci?? >
			${spechiettoBracci}
		</#if -->
		<#if !(approvazione??) >
			<#assign approvazione=budget.getChildrenByType("FolderApprovazione") />
		</#if>
		<#if approvazione?? && (approvazione?size > 0) >
		<#if !(approvazioneDetails??)>
		<#assign approvazioneDetails=approvazione[0].getChildren() />
		</#if>
		<!--div class="col-xs-12 status-bar">
				<h2>Approvazione clinica</h2>
				<#if (approvazioneDetails?size > 0) >
				<table class="table table-striped table-bordered table-hover">
				<thead><tr><td>Servizio</td><td>Stato</td></tr></thead>
				<tbody>
					<#list approvazioneDetails as currUO>
						<#assign currStato=currUO.getFieldDataDecode("ReviewBudgetPI","Stato") />
						<#assign currStatoCode=currUO.getFieldDataCode("ReviewBudgetPI","Stato") />
						<#assign statoClass="label-warning" />
						<#switch currStatoCode>
							<#case "1">
								<#assign statoClass="label-warning" />
    						<#break>
    						<#case "2">
								<#assign statoClass="label-success" />
    						<#break>
    						<#case "3">
								<#assign statoClass="label-danger" />
    						<#break>
						</#switch>
						<tr><td>${currUO.getFieldDataString("ReviewBudgetPI","UODescrizione")}</td><td><span class="label ${statoClass}">${currStato}</span></td></tr>	
					</#list>
				</tbody>
				</table>
				<#else>
					Non richiesta.
				</#if>
		</div-->
		</#if>
		<!--div class="col-xs-12 status-bar">
		<h2>Avanzamento</h2>
		<div class="progress pos-rel" data-percent="${percentuale}%">
			<div class="progress-bar" style="width:${percentuale}%;"></div>
		</div>
		<div class="timeline-container timeline-style2">
			<div class="timeline-items">

				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Approvazione clinica</span>
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
								<span class="timeline-date">Budget chiuso</span>
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
				
				<div class="timeline-item clearfix">
					<div class="timeline-info">
								<span class="timeline-date">Budget attualmente a contratto</span>
							<i class="my-timeline ${status3}"></i>
					</div>
					<div class="timeline-body widget-box transparent">
						<div class="widget-body">
							<div class="widget-main no-padding">
								<span class="timeline-date">${data3}</span>
							</div>
						</div>

					</div>
				</div>
				
				
				
			</div>
		</div-->
		</div>
		</div>
		</div>
		<#setting locale="it_IT">