<#assign percentuale=0>
<#assign totale=3>
<#assign statusGreen=true/>
<#assign statusGrey=false />
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey />

<#assign data1="" />
<#assign data2="" />
<#if (currBudget.getfieldData("ApprovazioneClinica","Approvato")?? && currBudget.getfieldData("ApprovazioneClinica","Approvato")?size>0 && currBudget.getfieldData("ApprovazioneClinica","Approvato")[0]=="1")>
	<#assign status1=statusGreen/>
		<#assign percentuale=percentuale+1>
		
</#if>

<#if (currBudget.getfieldData("ChiusuraBudget","Chiuso")?? && currBudget.getfieldData("ChiusuraBudget","Chiuso")?size>0 && currBudget.getfieldData("ChiusuraBudget","Chiuso")[0]=="1")>
	<#assign status2=statusGreen />

	<#assign percentuale=percentuale+1>
</#if>


<#if (center.getfieldData("statoValidazioneCentro","idBudgetApproved")?? && center.getfieldData("statoValidazioneCentro","idBudgetApproved")?size>0 && center.getfieldData("statoValidazioneCentro","idBudgetApproved")[0]==currBudget.getId()?string)>
	<#assign status3=statusGreen />
	<#assign percentuale=percentuale+1>
</#if>



<#assign percentuale=percentuale*100/totale>		
<#if status1>
	<span >
			<i class="fa fa-check-circle bigger-120 green"></i>
			Approvazione clinica
	
	</span>
<#else>	
	<span >
			<i class="fa fa-circle-o bigger-120 grey"></i>
			Approvazione clinica
	
	</span>
</#if>
<br>
<#if status2>
	<span >
			<i class="fa fa-check-circle bigger-120 green "></i>
			Budget chiuso
	
	</span>
<#else>	
	<span >
			<i class="fa fa-circle-o bigger-120 grey"></i>
			Budget chiuso
	
	</span>
</#if>
<br>
<#if status3>
	<span >
			<i class="fa fa-check-circle bigger-120 green"></i>
			Budget a contratto
	
	</span>
<#else>	
	<span >
			<i class="fa fa-circle-o bigger-120 grey"></i>
			Budget a contratto
	
	</span>
</#if>