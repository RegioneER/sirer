<#if allBudgets??>
	<#assign allBudgets=allBudgets?reverse />
	<table class="table table-striped table-bordered table-hover">
		<thead>
			<tr>
				
				<th>Data creazione</th>
				<th>Data modifica</th>
				<th>Autore</th>
				<th>Versione</th>
				<th>Note</th>
				<th>Stato</th>
				<th>Azioni</th>
			</tr>
		</thead>
		<tbody>
		  <#if (allBudgets?size == 0)>
       			<tr>
            <td colspan=7><span class="help-button">?</span> Nessun budget inserito </td>
            
            </tr>
            </#if>
	<#list allBudgets as currBudget>
			<tr>
				
				<td>${currBudget.creationDt.time?datetime?string.medium}</td>
				<td><#if currBudget.lastUpdateDt?? >${currBudget.lastUpdateDt.time?datetime?string.medium}</#if></td>
				<td user-budgetCreatorBB="<#if currBudget.lastUpdateUser?? >${currBudget.lastUpdateUser}</#if>"><#if currBudget.lastUpdateUser?? >${currBudget.lastUpdateUser}</#if></td>
				<td user-budgetVersioneBB="${currBudget.getFieldDataString("Base","Nome")?string}" ><@elementTitle currBudget/><#if (currBudget.getfieldData("Budget","Versione")?size>0) >( v. ${currBudget.getfieldData("Budget","Versione")[0]} )</#if></td>
				<td><#if  (currBudget?? && currBudget.getfieldData("Budget","Note")?? && currBudget.getfieldData("Budget","Note")?size>0) >${currBudget.getfieldData("Budget","Note")[0]}</#if></td>
				<td><#include "budgetStatusCol.ftl"></td>
				<td><#if currBudget.getUserPolicy(userDetails).isCanView() ><button style="margin-top:0px;" class="btn btn-info btn-sm"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-1';" title="Flowchart budget"  > <i class="icon icon-edit"></i></button></#if>
				
				</td>
			</tr>
	</#list>
		</tbody>
	</table>
</#if>
