 <div id="tabs-7" class="tab-pane" >
 
 <#if allBudgets??>
 
 
 <div id="B-totali-CTC" class="ui-widget cost-table full-w">
    <fieldset> <legend>Totale budget</legend>
    <table id="b-table-tot" class="table table-striped table-bordered table-hover">
    <thead>
    <tr>  	
        <th>Descrizione</th>
        <th>Transfer price (&euro;)</th>
        <th>Totale budget (&euro;)</th>
    </tr>
    </thead>
    <tbody>
    <#assign tot=0>
    <#assign totCTC=0>
 	<#list allBudgets as currBudgetBraccio>
 		    <tr>
 		    	<td colspan="3"  style="background-color:#E7E4EC"><b>Braccio <@elementTitle currBudgetBraccio/></b></td>
		        
		    </tr>
		    <#list currBudgetBraccio.getChildrenByType("FolderBudgetStudio")[0].getChildren() as currBudget>
		    <#if currBudget.getFieldDataString("BudgetCTC","Definitivo")=="1">
		    <#attempt>
		    <#assign currVal=currBudget.getFieldDataString('BudgetCTC_TotaleStudio')?number />
		    <#assign tot=tot+currVal />
		    <#recover></#attempt>
		    <#attempt>
		    <#assign currValCTC=currBudget.getFieldDataString('BudgetCTC_TotaleStudioCTC')?number />
		    <#assign totCTC=totCTC+currValCTC />
		    <#recover></#attempt>
		    <tr>
 		    	
		        <td>Budget totale per paziente</td>
		       
		        <td class="to-money" >${currBudget.getFieldDataString('BudgetCTC_TotalePaziente')}</td>
		        <td class="to-money" >${currBudget.getFieldDataString('BudgetCTC_TotalePazienteCTC')}</td>
		        
		    </tr>
		    <tr>
 		    	
		        <td>Budget totale per studio</td>
		        
		        <td class="to-money" >${currBudget.getFieldDataString('BudgetCTC_TotaleStudio')}</td>
		        <td class="to-money" >${currBudget.getFieldDataString('BudgetCTC_TotaleStudioCTC')}</td>
		        
		    </tr>
		     </#if>
		    </#list>
 	</#list>
 		
 		   <tr>
 		    	<td colspan="3"  style="background-color:#E7E4EC"><b >Budget complessivo</b></td>
		        
		    </tr>
		    <tr id="b-tot-row" >
		        <td>Totale budget studio<input type="hidden" value="${tot}" id="totBracci" /><input type="hidden" value="${tot}" id="totBracciCTC" /></td>
		        
		        <td class="to-money" id="totaleBracci" >${tot}</td>
		        <td class="to-money" id="totaleBracciCTC" >${totCTC}</td>
		       
		    </tr>
    </tbody>
    </table>
    </fieldset>
</div>

</#if>
</div>