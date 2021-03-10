<div id="versioniBudgetStudio" class="">

	<#assign folderBudgetStudioList=el.getChildrenByType("FolderBudgetStudio") />
	<#assign folderBudgetStudioList=folderBudgetStudioList?reverse />
	<#list folderBudgetStudioList as budgetStudioList>
		<#assign folderNewBudget=budgetStudioList.id />
		<div class="buttons-studio">
			<#if (budgetStudioList.getChildren()?size>1) >
				<button class="btn btn-primary"  onclick="compareBudgetStudio();">Confronta budget studio</button>
			</#if>
			<#if canCopyStudio>
				<button class="btn btn-primary"  onclick=" newBudgetStudio();//$('#newbudget-dialog-form').dialog('open');">Aggiungi nuovo</button>
			</#if>
		</div>
		<#if (budgetStudioList.getChildren()?size>0) >
		<table class='table table-striped table-bordered table-hover' cellspacing=0 border=0 cellpadding=0 >
			<thead>
			<tr>
				<th colspan=2>Versioni a confronto</th>
				<th>Autore</th>
				<th>Versione</th>

				<th>Tipologia</th>
				<th>Note</th>
				<th>Versione finale</th>
				<th>Azioni</th>
			</tr>
			</thead>
			<tbody>
			<#assign allBudgets=budgetStudioList.getChildren() />
			<#assign allBudgets=allBudgets?reverse />
			<#list allBudgets as currBudgetStudio>
			<#assign typeNewBudget=currBudgetStudio.type.id />
			<tr>
				<td ><input type='radio' name='confronto1' value='${currBudgetStudio.id}'></td>
				<td ><input type='radio' name='confronto2' value='${currBudgetStudio.id}'></td>
				<td>${currBudgetStudio.lastUpdateUser}</td>
				<td><a href="${baseUrl}/app/documents/custom/budget_studio/${currBudgetStudio.id}"><#attempt><!-- @elementTitle currBudgetStudio /-->
					<#if (currBudgetStudio.getfieldData("Base","Nome")?size>0) >
					${currBudgetStudio.getfieldData("Base","Nome")[0]}
				</#if> v.<#if (currBudgetStudio.getfieldData("Budget","Versione")?size>0) >
					${currBudgetStudio.getfieldData("Budget","Versione")[0]}
				</#if><#recover>Budget Studio</#attempt></a>&nbsp;


			<td>
				<#if (currBudgetStudio.getfieldData("BudgetCTC","Tipologia")?size>0) >
				${getDecode("BudgetCTC","Tipologia",currBudgetStudio)}
			</#if>
			</td>
			<td>
				<#if (currBudgetStudio.getfieldData("Budget","Note")?size>0) >
				${currBudgetStudio.getfieldData("Budget","Note")[0]}
			</#if>
			</td>
			<td style="vertical-align:middle"><#if (currBudgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")?? && currBudgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")?size>0 && currBudgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")[0]=="1") ><i class="fa fa-check-circle green bigger-160" ></i><#else><i class="fa fa-circle-o grey bigger-160"></i></#if></td>
			<td>
				<button style="margin-top:0px;" class="btn btn-warning btn-sm"   onclick="location.href='${baseUrl}/app/documents/custom/budget_studio/${currBudgetStudio.id}';"" ><i class="icon-eye-open"></i> Visualizza</button>
				<#if canCopyStudio><button style="margin-top:0px;" class="btn btn-primary btn-sm"   onclick="openClone('${currBudgetStudio.id}')" ><i class="icon-copy"></i> Copia</button></#if>

			<button style="margin-top:0px;display:none;" class="btn btn-success btn-sm"   onclick="location.href='${baseUrl}/app/documents/download/excelStudio/${currBudgetStudio.id}';"><i class="icon icon-download"> Scarica excel</button></td>

			</tr>

			</#list>
			</tbody>
		</table>
		</#if>
	</#list>



<#--include "../budget/cloneForms.ftl"/-->
        </div>