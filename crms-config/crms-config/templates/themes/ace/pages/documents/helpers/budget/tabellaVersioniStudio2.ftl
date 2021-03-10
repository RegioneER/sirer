<div id="tabs-5" class="tab-pane">
            
            <#assign folderBudgetStudioList=el.getChildrenByType("FolderBudgetStudio") />
            <#assign folderBudgetStudioList=folderBudgetStudioList?reverse />
            <#list folderBudgetStudioList as budgetStudioList>
       		<#assign folderNewBudget=budgetStudioList.id />
       		<div class="buttons-studio">
       		
			<#if canCopyStudio>
			<@script>
			function newBudgetStudio(form){
				var element=$.extend(true,{},emptyBudgetCTC);
				//element=formToElement(form,element);
				loadingScreen("Salvataggio in corso...", "/CPRMS/app/int/images/loading.gif");
				$.when(saveElement(element,folderBudgetStudio)).then(function(data){
					window.location.href='../custom/budget_studio2/'+data.ret;
				});
			}
			</@script>
			<button class="btn btn-primary"  onclick=" newBudgetStudio();//$('#newbudget-dialog-form').dialog('open');">Aggiungi nuovo</button>
			<!--div id="newbudget-dialog-form"  class='safeUpdating' title="Aggiungi nuovo">
                <form>
                <fieldset>
                <label for="Budget_Versione3">Versione</label>
                <input type="text" name="Budget_Versione" id="Budget_Versione3" value="" class="text ui-widget-content ui-corner-all" />
                <label for="BudgetCTC_Tipologia">Tipologia</label>
                <select  name="BudgetCTC_Tipologia" id="BudgetCTC_Tipologia" class="text ui-widget-content ui-corner-all" >
                	<option></option>
                	<option value="1###Versione Sponsor">Versione Sponsor</option>
                	<option value="2###Versione PI">Versione PI</option>
                	<option value="3###Versione CTC">Versione CTC</option>
                </select>
                <label for="Budget_Note3">Note</label>
                <textarea name="Budget_Note" id="Budget_Note3" cols="100" rows="6"  class="text ui-widget-content ui-corner-all"></textarea>
                
                
                
                    </fieldset>
                </form>
            </div-->
			</#if>
			</div>
       		<#if (budgetStudioList.getChildren()?size>0) >
            <table class='table table-striped table-bordered table-hover' cellspacing=0 border=0 cellpadding=0 >
            <thead>
           	<tr>
           
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
		           	
		           <td>${currBudgetStudio.lastUpdateUser}</td>
		           	<td><a href="${baseUrl}/app/documents/custom/budget_studio2/${currBudgetStudio.id}"><#attempt><!-- @elementTitle currBudgetStudio /-->
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
		            <button style="margin-top:0px;" class="btn btn-warning btn-sm"   onclick="location.href='${baseUrl}/app/documents/custom/budget_studio2/${currBudgetStudio.id}';"" ><i class="icon-eye-open"></i> Visualizza</button>
		            <#if canCopyStudio><button style="margin-top:0px;" class="btn btn-primary btn-sm"   onclick="openClone('${currBudgetStudio.id}')" ><i class="icon-copy"></i> Copia</button></#if>
				
		            <button style="margin-top:0px;display:none;" class="btn btn-success btn-sm"   onclick="location.href='${baseUrl}/app/documents/download/excelStudio/${currBudgetStudio.id}';"><i class="icon icon-download"> Scarica excel</button></td>
   
		           	</tr>        	
	            	
	            </#list>
           </tbody>
            </table>
            
            </#if>
            </#list>
           
          
            
            <#include "cloneForms.ftl"/>
        </div>