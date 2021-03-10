<#setting number_format="0.##">
<#setting locale="en_US">
<#assign percentuale=0>
<#assign totale=4>
<#assign statusGreen="fa fa-check-circle-o green"/>
<#assign statusGrey="fa fa-circle-o grey" />
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey />


<#assign data1="" />
<#assign data2="" />
<#assign data3="" />
<#assign data4="" />
<#if (budget.getfieldData("ApprovazioneClinica","Approvato")?? && budget.getfieldData("ApprovazioneClinica","Approvato")?size>0 && budget.getfieldData("ApprovazioneClinica","Approvato")[0]=="1")>
	<#assign status1=statusGreen/>
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
<#if (budgetStudio.getfieldData("BudgetCTC","Definitivo")?? && budgetStudio.getfieldData("BudgetCTC","Definitivo")?size>0 && budgetStudio.getfieldData("BudgetCTC","Definitivo")[0]=="1") >
	<#assign status4=statusGreen/>
	<#assign data4=getFieldFormattedDate("BudgetCTC","DefinitivoData",budgetStudio) />
		<#assign percentuale=percentuale+1>
		

</#if>



<#assign percentuale=percentuale*100/totale>	
<div  class="col-xs-3 sidebar-right">
<div id="rightbar-toggle" class="btn btn-app btn-xs btn-info  ace-settings-btn open">
<i class="icon-chevron-right bigger-150"></i>
</div>	
<div class=" status-bar-content">
		<div class="col-xs-12 status-bar">
				<h2>Informazioni</h2>
				<b><@elementTitle center/></b><br>
				<#setting locale="it_IT">
				Creato il: <b>${budgetStudio.creationDt.time?datetime?string.medium}</b><br>
				Modificato il: <b><#if budgetStudio.lastUpdateDt?? >${budgetStudio.lastUpdateDt.time?datetime?string.medium}</#if></b><br>
				Autore: <b><#if budgetStudio.lastUpdateUser?? >${budgetStudio.lastUpdateUser}<#else>${budgetStudio.creationUser}</#if></b><br><br>
				<#setting locale="en_US">
		 	Versione budget:
				<#if budgetStudio??>
					<#if budgetStudio.type.titleField?? || budgetStudio.type.titleRegex??>
				    <b><@elementTitle budgetStudio/> ( v. <#if (budgetStudio.getfieldData("Budget","Versione")?size>0) >
				    	 ${budgetStudio.getfieldData("Budget","Versione")[0]}
				    	</#if> <#if (budgetStudio?? && budgetStudio.getfieldData("BudgetCTC","Tipologia")?? && budgetStudio.getfieldData("BudgetCTC","Tipologia")?size>0) >${getDecode("BudgetCTC","Tipologia",budgetStudio)}</#if>)
				    	<#if  (budget.getfieldData("Budget","Note")?? && budget.getfieldData("Budget","Note")?size>0) >
				    	<div><br><span style="font-weight:bold">Note budget:</span> <b>${budget.getfieldData("Budget","Note")[0]}</b></div>
				    	</#if>
				    	<#if  (budgetStudio?? && budgetStudio.getfieldData("Budget","Note")?? && budgetStudio.getfieldData("Budget","Note")?size>0) >
				    	<div><br><span style="font-weight:bold">Note budget studio:</span> <b>${budgetStudio.getfieldData("Budget","Note")[0]}</b></div>
				    	</#if>
				    	</b>
					</#if>
				<#else>
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
								<span class="timeline-date">Budget dei prezzi definitivo</span>
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
		</div>
		</div>
		</div>
		</div>