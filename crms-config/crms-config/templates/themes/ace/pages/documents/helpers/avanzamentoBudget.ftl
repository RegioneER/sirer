<style>

.budget-studio td,.budget-studio th{
	padding:5px;
	text-align:center;
	font-size:12px;
}
.ui-widget-header {
	background: url("images/ui-bg_gloss-wave_55_5c9ccc_500x100.png") repeat-x scroll 50% 50% #5C9CCC!important;
}
table.ui-widget  tr:nth-child(2n+1) td {
    background-color: #F0FFFF;
}
table.ui-widget  tr:nth-child(2n) td {
    background-color: #F5FFFA;
}

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
fieldset.specchietto {
		    border: 1px solid #336EA9!important;
		    border-radius: 10px!important;
		    padding: 1em!important;
		    font-size:13px;
		    
		    font-weight:bold;
		    font-family:arial;
		    width:35%;
		    float:left;
		}

</style>

<fieldset class="specchietto" style="background-color: #DFEFFC;" ><legend>Stato di avanzamento</legend>


<#if (budget.getfieldData("ApprovazioneClinica","Approvato")?? && budget.getfieldData("ApprovazioneClinica","Approvato")?size>0 && budget.getfieldData("ApprovazioneClinica","Approvato")[0]=="1") >
	<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Approvazione clinica:</span>
	<span style="background-color: #90EE90;border-radius: 5px;padding:2px;">Si</span>
<#else>
	<span style="background-color: #FFA463;border-radius: 5px;padding:2px;">Approvazione clinica:</span>
	<span style="background-color: #FFC175;border-radius: 5px;padding:2px;">No</span>
</#if><br><br>


<#if (budget.getfieldData("ChiusuraBudget","Chiuso")?? && budget.getfieldData("ChiusuraBudget","Chiuso")?size>0 && budget.getfieldData("ChiusuraBudget","Chiuso")[0]=="1") >
	<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Budget chiuso:</span>
	<span style="background-color: #90EE90;border-radius: 5px;padding:2px;">Si</span>
<#else>
	<span style="background-color: #FFA463;border-radius: 5px;padding:2px;">Budget chiuso:</span>
	<span style="background-color: #FFC175;border-radius: 5px;padding:2px;">No</span>
</#if><br><br>


<#if (center.getfieldData("statoValidazioneCentro","idBudgetApproved")?? && center.getfieldData("statoValidazioneCentro","idBudgetApproved")?size>0 && center.getfieldData("statoValidazioneCentro","idBudgetApproved")[0]==budget.getId()?string) >
	<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Budget attualmente a contratto:</span>
	<span style="background-color: #90EE90;border-radius: 5px;padding:2px;">Si</span>
<#else>
	<span style="background-color: #FFA463;border-radius: 5px;padding:2px;">Budget attualmente a contratto:</span>
	<span style="background-color: #FFC175;border-radius: 5px;padding:2px;">No</span>
</#if><br><br>

<#if budgetStudio??>
	<#if (budgetStudio.getfieldData("BudgetCTC","Definitivo")?? && budgetStudio.getfieldData("BudgetCTC","Definitivo")?size>0 && budgetStudio.getfieldData("BudgetCTC","Definitivo")[0]=="1") >
		<span style="background-color: #9BFF9B;border-radius: 5px;padding:2px;">Budget studio definitivo:</span>
		<span style="background-color: #90EE90;border-radius: 5px;padding:2px;">Si</span>
	<#else>
		<span style="background-color: #FFA463;border-radius: 5px;padding:2px;">Budget studio definitivo:</span>
		<span style="background-color: #FFC175;border-radius: 5px;padding:2px;">No</span>
	</#if>
</#if>
</fieldset>


<fieldset class="specchietto" style="background-color: #EBC6F4;" ><legend>Informazioni</legend>


 	
 	<@elementTitle center/><br><br>
 	Versione budget:
		<#if budget??>
			<#if budget.type.titleField?? || budget.type.titleRegex??>
		    <b><@elementTitle budget/> ( v. <#if (budget.getfieldData("Budget","Versione")?size>0) >
		    	 ${budget.getfieldData("Budget","Versione")[0]}
		    	</#if> <#if (budgetStudio?? && budgetStudio.getfieldData("BudgetCTC","Tipologia")?? && budgetStudio.getfieldData("BudgetCTC","Tipologia")?size>0) >${getDecode("BudgetCTC","Tipologia",budgetStudio)}</#if>)
			</#if>
		<#else>
		</#if>
	
</fieldset>





<div class="clearfix"></div>