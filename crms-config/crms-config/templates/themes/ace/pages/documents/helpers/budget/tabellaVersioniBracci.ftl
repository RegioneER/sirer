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
	<#assign bracciLinks>
	${bracciLinks}
	<a href="${baseUrl}/app/documents/detail/${currBudget.id}"><button class="btn btn-info" style="margin:3px;" ><@elementTitle currBudget/></button></a>
	</#assign>
			<tr>
				
				<td>${currBudget.creationDt.time?datetime?string.medium}</td>
				<td><#if currBudget.lastUpdateDt?? >${currBudget.lastUpdateDt.time?datetime?string.medium}</#if></td>
				<td><#if currBudget.lastUpdateUser?? >${currBudget.lastUpdateUser}</#if></td>
				<td><@elementTitle currBudget/><#if (currBudget.getfieldData("Budget","Versione")?size>0) >( v. ${currBudget.getfieldData("Budget","Versione")[0]} )</#if></td>
				<td><#if  (currBudget?? && currBudget.getfieldData("Budget","Note")?? && currBudget.getfieldData("Budget","Note")?size>0) >${currBudget.getfieldData("Budget","Note")[0]}</#if></td>
				<td><#include "braccioStatusCol.ftl"></td>
				<td><#if currBudget.getUserPolicy(userDetails).isCanView() ><button style="margin-top:0px;" class="btn btn-info btn-sm"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-1';" title="Flowchart budget"  > <i class="icon icon-table"></i></button><button style="margin-top:0px;margin-right:0px!important;" class="btn btn-warning btn-sm"  title="Rimborsabilit&agrave; SSN/SSR"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-2';"" > <i class="icon icon-compass"></i></button><button style="margin-top:0px;" class="btn btn-success btn-sm"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-4';" title="Dettaglio economico del budget PI" > <i class="icon icon-eur"></i></button><#if userDetails.hasRole("CTC") ><button style="margin-top:0px;margin-right:0px!important" title="Versioni budget di studio" class="btn btn-primary btn-sm"   onclick="location.href='${baseUrl}/app/documents/detail/${currBudget.id}#tabs-5';"" > <i class="icon icon-legal"></i></button></#if><#if true ><button style="margin-top:0px;;" title="Elimina braccio" class="btn btn-danger btn-sm"   onclick="if(confirm('Sei sicuro di voler eliminare il braccio?'))deleteElementRow('${currBudget.id}',this);" > <i class="icon icon-trash"></i></button></#if></#if>
				
				</td>
			</tr>
	</#list>
		</tbody>
	</table>
</#if>
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