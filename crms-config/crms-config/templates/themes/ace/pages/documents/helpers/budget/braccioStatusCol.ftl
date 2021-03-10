<#assign percentuale=0>
<#assign totale=3>
<#assign statusGreen=true/>
<#assign statusGrey=false />
<#assign status1=statusGrey status2=statusGrey status3=statusGrey status4=statusGrey status5=statusGrey status6=statusGrey status7=statusGrey status8=statusGrey />
<#assign budgetNonno=currBudget.getParent().getParent() />
<#assign data1="" />
<#assign data2="" />
<#if (budgetNonno.getfieldData("ApprovazioneClinica","Approvato")?? && budgetNonno.getfieldData("ApprovazioneClinica","Approvato")?size>0 && budgetNonno.getfieldData("ApprovazioneClinica","Approvato")[0]=="1")>
	<#assign status1=statusGreen/>
		<#assign percentuale=percentuale+1>
		
</#if>


<#if (currBudget.getfieldData("BraccioWF","BudgetDefinitivo")?? && currBudget.getfieldData("BraccioWF","BudgetDefinitivo")?size>0 && currBudget.getfieldData("BraccioWF","BudgetDefinitivo")[0]!="")>
	<#assign status2=statusGreen />

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
			Budget studio definitivo
	
	</span>
<#else>	
	<span >
			<i class="fa fa-circle-o bigger-120 grey"></i>
			Budget studio definitivo
	
	</span>
</#if>
