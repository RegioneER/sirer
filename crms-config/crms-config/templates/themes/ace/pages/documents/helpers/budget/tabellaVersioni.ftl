<#assign bracciLinks="" />
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
				<!--th>Stato</th-->
				<th>Versione Finale</th>
				<th>Azioni</th>
			</tr>
		</thead>
		<tbody>
		  <#if (allBudgets?size == 0)>
       			<tr>
            <td colspan=7><span class="help-button">?</span> Nessun budget inserito </td>
            
            </tr>
            </#if>
    <#assign bracciFlag=false >
	<#list allBudgets as currBudget>
		<#if currBudget.type.typeId="BudgetSingoloBraccio"> <#assign bracciFlag=true ></#if>
		<#assign bracciLinks>
		${bracciLinks}
		<a href="${baseUrl}/app/documents/detail/${currBudget.id}"><button class="btn btn-info" style="margin:3px;" ><@elementTitle currBudget/></button></a>
		</#assign>
			<tr>
				
				<td>${currBudget.creationDt.time?datetime?string.medium}</td>
				<td><#if currBudget.lastUpdateDt?? >${currBudget.lastUpdateDt.time?datetime?string.medium}</#if></td>
				<td user-budgetCreator="<#if currBudget.lastUpdateUser?? >${currBudget.lastUpdateUser}</#if>"><#if currBudget.lastUpdateUser?? >${currBudget.lastUpdateUser}</#if></td>
				<td user-budgetVersione="${currBudget.getFieldDataString("Base","Nome")?string}" ><@elementTitle currBudget/><#if (currBudget.getfieldData("Budget","Versione")?size>0) >( v. ${currBudget.getfieldData("Budget","Versione")[0]} )</#if></td>
				<td><#if  (currBudget?? && currBudget.getfieldData("Budget","Note")?? && currBudget.getfieldData("Budget","Note")?size>0) >${currBudget.getfieldData("Budget","Note")[0]}</#if></td>
				<!--td><#include "budgetStatusCol.ftl"></td-->
				<td style="vertical-align:middle"><#if (currBudget.getChildrenByType('FolderBudgetStudio')[0].getChildrenByType('BudgetCTC')[0].getFieldDataStrings("BudgetCTC","Definitivo")?? && currBudget.getChildrenByType('FolderBudgetStudio')[0].getChildrenByType('BudgetCTC')[0].getFieldDataStrings("BudgetCTC","Definitivo")?size>0 && currBudget.getChildrenByType('FolderBudgetStudio')[0].getChildrenByType('BudgetCTC')[0].getFieldDataStrings("BudgetCTC","Definitivo")[0]=="1") ><i class="fa fa-check-circle green bigger-160" ></i><#else><i class="fa fa-circle-o grey bigger-160"></i></#if></td>
				<td>
				<#if currBudget.getUserPolicy(userDetails).isCanView() >
					<button style="margin-top:0px;" class="btn btn-info btn-sm"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-4';" title="Visualizza Budget"  > <i class="icon icon-table"></i></button>
					<!--button style="margin-top:0px;margin-right:0px!important;" class="btn btn-warning btn-sm"  title="Rimborsabilit&agrave; SSN/SSR"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-2';"" > <i class="icon icon-compass"></i></button>
					<button style="margin-top:0px;" class="btn btn-success btn-sm"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-4';" title="Dettaglio economico del budget PI" > <i class="icon icon-eur"></i></button>
					<#if userDetails.hasRole("CTC") >
						<button style="margin-top:0px;" title="Versioni budget di studio" class="btn btn-primary btn-sm"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-5';"" > <i class="icon icon-legal"></i></button>
					</#if>
					<button style="margin-top:0px;display:none!important;" title="Scarica excel budget PI" class="btn btn-warning btn-sm"   onclick="location.href='${baseUrl}/app/documents/download/excel/${currBudget.id}';"" > <i class="icon icon-download"></i></button-->
				</#if>
				</td>
			</tr>
	</#list>
		</tbody>
	</table>
</#if>
<#if bracciFlag>
<#global spechiettoBracci >

<div class="col-xs-12 status-bar">
<h2>
Bracci
</h2>
<span id="bracciList">
	${bracciLinks}
</span>
</div>
</#global>
</#if>