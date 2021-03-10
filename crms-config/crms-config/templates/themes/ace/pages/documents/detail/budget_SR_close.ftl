<#include "../helpers/title.ftl"/>
<#assign budget=el />
<#assign center=el.getParent() />
<#include "../helpers/avanzamentoBudget.ftl"/>
    <div style="display: block">
   <br><br>
	
     

        <div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
        <div id="tabs">
        <ul style='height:27px'>
        <li><a id='tab1' href="#tabs-1">Disegno Flowchart</a></li>
        <li><a id='tab2' href="#tabs-2">Rimborsabilit&agrave;</a></li>
        <li><a id='tab4' href="#tabs-4">Budget clinico</a></li>
        <!--li><a id='tab3' href="#tabs-3">Budget studio</a></li-->
        <li><a id='tab5' href="#tabs-5">Budget studio</a></li>
        </ul>
        <div id="tabs-1">
        <div id="example"></div>
        <!--button id="tp-button">Aggiungi visita</button-->
            <div id="tp-dialog-form" title="Aggiungi visita">
                <form>
                <fieldset>
                <label for="TimePoint_Descrizione">Descrizione</label>
                <input type="text" name="TimePoint_Descrizione" id="TimePoint_Descrizione" value="" class="text ui-widget-content ui-corner-all" />
                <label for="TimePoint_NumeroVisita">Numero visita</label>
                <input type="text" name="TimePoint_NumeroVisita" id="TimePoint_NumeroVisita" value="" class="text ui-widget-content ui-corner-all"/>
                
                <label for="TimePoint_Tempi">Tempi</label>
                <input type="text" name="TimePoint_Tempi" id="TimePoint_Tempi" value="" class="text ui-widget-content ui-corner-all"/>
                <label for="TimePoint_DurataCiclo">Durata</label>
                <input type="text" name="TimePoint_DurataCiclo" id="TimePoint_DurataCiclo" value="" class="text ui-widget-content ui-corner-all"/>
                <label>Tipo di ricovero</label><br/>
                <label for="Ricovero_Ordinario">Ricovero Ordinario</label><input type="checkbox" id="Ricovero_Ordinario" name="Ricovero_Ordinario" value="1" />
                <label for="Ricovero_Straordinario">Ricovero Extra routine</label><input type="checkbox" id="Ricovero_Straordinario" name="Ricovero_Straordinario" value="1" />
                <label for="Ricovero_Ambulatoriale">Ricovero Ambulatoriale</label><input type="checkbox" id="Ricovero_Ambulatoriale" name="Ricovero_Ambulatoriale" value="1" />
                <label for="Ricovero_Telefonico">Casa (con check telefonico )</label><input type="checkbox" id="Ricovero_Telefonico" name="Ricovero_Telefonico" value="1" />
                <label for="TimePoint_Note">Note</label>
                <input type="text" name="TimePoint_Note" id="TimePoint_Note" value="" class="text ui-widget-content ui-corner-all"/>
                
                 </fieldset>
                </form>
            </div>
             <div id="prestazione-dialog" title="Nuova Prestazione">
                <form>
                <fieldset>
                <label for="Altro_Descrizione">Descrizione</label>
                <input type="text" name="PrestazioniDizionario_Descrizione" id="Altro_Descrizione" value="" class="text ui-widget-content ui-corner-all" />
                
                
                 </fieldset>
                </form>
            </div>
            <div id="prestazione-diz-dialog" title="Nuova Prestazione">
                <form>
                <fieldset>
                 <div class="ui-widget">
                <label for="Prestazioni_prestazione">Prestazione</label>
                <input type="text" name="Prestazioni_prestazione" id="Prestazioni_prestazione" value="" class="text ui-widget-content ui-corner-all" />
                </div>
                <label for="Prestazioni_CDC">Centro di costo</label>
                <input type="text" name="Prestazioni_CDC" id="Prestazioni_CDC" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_CDCCode" id="Prestazioni_CDCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_UOC" id="Prestazioni_UOC" value="" class="text ui-widget-content ui-corner-all" />
                
                <input type="button" name="Prestazioni_Altro" id="Prestazioni_Altro" value="Salva prestazione nel dizionario" onclick="salvaPrestazione(this);" class="text ui-widget-content ui-corner-all" />
                
               <input type="hidden" name="Prestazioni_UOCCode" id="Prestazioni_UOCCode" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" name="Tariffario_Solvente" id="Tariffario_Solvente" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Tariffario_SSN" id="Tariffario_SSN" value="" class="text ui-widget-content ui-corner-all" />
                 </fieldset>
                </form>
            </div>
            <!--div ><button id="prestazione-diz-button">Aggiungi prestazione</button></div-->
         <div style='display:none'><button id="prestazione-button">Aggiungi prestazione</button></div>
            <div id="prestazione-dialog-form" title="Aggiungi prestazione">
                <p class="validateTips">Tutti i campi sono obbligatori</p>
                <form>
                <fieldset>
                <label for="titolo-prestazione">Nome prestazione</label>
                <input type="text" name="titolo-prestazione" id="titolo-prestazione" value="" class="text ui-widget-content ui-corner-all" />
                <label for="descrizione-prestazione">Descrizione</label>
                <input type="text" name="descrizione-prestazione" id="descrizione-prestazione" value="" class="text ui-widget-content ui-corner-all"/> </fieldset>
                </form>
            </div>
         <!--div id="second-element">
            <span class="sortable-list-span">
                <h3>Prestazioni</h3>
                    <ul class='sortable-list' id='COSTS' > </ul>
            </span>
            <span class="sortable-list-span">     
                <h3>Time-points</h3>
                    <ul class='sortable-list' id='TPS'> </ul>
            </span>
            <br class="clear" />
        </div-->
        </div>
        <div id="tabs-2">
         <!--canvas id='grafico' width="1200" height="500" ></canvas-->
         <div id='grafico' style="display:block"></div>
         <div id='legenda'><span style="display:inline-block;width:10px;height:10px;background-color:lightblue;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni aggiuntive rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:orange;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie ma nel caso specifico rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:white;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie a carico SSN/SSR</span></div>
         <div id='rimborsabilita'></div>
        </div>
        <div id="tabs-3" style="display:none">
        <div id='clinico'>
        <div id="costi"></div>
        <br/>
            <h2>Budget clinico</h2>
            <!--button id="create-cost">Aggiungi costo clinico</button> <button id="add-n-pat">Numero di pazienti previsto</button-->
        <div id="added-costs-1" class="ui-widget cost-table">
            <h1>Prestazioni a richiesta:</h1>
            <table id="costs-1" class="ui-widget ui-widget-content">
            <thead>
            <tr class="ui-widget-header ">
            <th>Descrizione</th>
            <th>Transfer price (&euro;)</th>
            <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
            
            </tbody>
            </table>
        </div>
        <div id="added-costs-2" class="ui-widget cost-table">
            <h1>Costi aggiuntivi per studio:</h1>
            <table id="costs-2" class="ui-widget ui-widget-content">
            <thead>
            <tr class="ui-widget-header ">
            <th>Descrizione</th>
            <th>Transfer price (&euro;)</th>
            <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
            
            </tbody>
            </table>
        </div>
        <div id='pazienti-tabs-4'><span id='global-pazienti'>Pazienti previsti:<span id='show-n-pat'></span></span></div>
       
        
            <div id="dialog-form" title="Aggiungi costo">
                
                <form>
                <fieldset>
                <label for="tipologia">Tipo di applicazione</label>
                <select  name="tipologia" id="tipologia" class="text ui-widget-content ui-corner-all" />
                    <option value="1">A richiesta</option>
                    <option value="2">Per studio</option>
                </select>
                <label for="descrizione">Descrizione</label>
                <input type="text" name="Base_Nome" id="descrizione" value="" class="text ui-widget-content ui-corner-all" />
                <label for="costo-costo">Costo (&euro;)</label>
                <input type="text" name="Costo_Costo" id="costo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup-costo">Markup</label>
                <input type="text" name="Costo_Markup" id="markup-costo" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup-costo" value="" class="text ui-widget-content ui-corner-all" >
                	<option value="1">Valore assoluto</option>
                	<option value="2">%</option>
                	
                </select>
                <label for="transfer-costo">Transfer price (&euro;)</label>
                <input type="text" name="Costo_TransferPrice" id="transfer-costo" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
            
            <div id="dialog-form-n-pat" title="Numero di pazienti">
                <form>
                <fieldset>
                <label for="n-pat">Numero di pazienti</label>
                <input type="text" name="BudgetCTC_NumeroPazienti" id="n-pat" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>
            <div id="dialog-form-transfer" title="Aggiungi transfer price">
                <p class="validateTips"></p>
                <form>
                <fieldset>
                <div id='tariffaSSN'>Tariffa SSR: <span  id='valoreSSN'></span></div>
               	<div id='tariffaAlpi'>Tariffa ALPI: <span  id='valoreAlpi'></span> &euro;</div>
               	<div id='tariffaSolvente'>Tariffa Solvente: <span  id='valoreSolvente'></span> &euro;</div>
               	<label for="oreuomo">Ore uomo</label>
                <input type="text" name="Costo_OreUomo" id="oreuomo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="oremacchina">Ore macchina</label>
                <input type="text" name="Costo_OreMacchina" id="oremacchina" value="" class="text ui-widget-content ui-corner-all" />
                <label for="costo">Costo (&euro;)</label>
                <input type="text" name="Costo_Costo" id="costo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup">Mark-up</label>
                <input type="text" name="Costo_Markup" id="markup" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup" value="" class="text ui-widget-content ui-corner-all" >
                	<option value="1">Valore assoluto</option>
                	<option value="2">%</option>
                	
                </select>
                <label for="transfer">Transfer Price (&euro;) <span style="color:red">(Obbligatorio)</span></label>
                <input type="text" name="Costo_TransferPrice" id="transfer" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
            </div>
            
            <div id="dialog-form-CTC" title="Aggiungi markup">
                <form>
                <fieldset>
                <label for="mCTC">Markup (%)</label>
                <input type="text" name="BudgetCTC_Markup" id="mCTC" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>
            
           	<div id="dialog-form-cost-2" title="Aggiungi costo non clinico">
                
                <form>
                <fieldset>
                <label for="tipologia2">Tipo di applicazione</label>
                <select  name="tipologia" id="tipologia2" class="text ui-widget-content ui-corner-all" onchange="if(this.value==5)$('#catbox').hide();else $('#catbox').show()" />
                    <option value="3">Per paziente</option>
                    <option value="4">Per studio</option>
                    <option value="5">Rimborsi a pi&egrave; di lista</option>
                </select>
                <span id='catbox'>
                <label for="interno_esterno">Categoria di costo</label>
                 <select  name="Costo_Categoria" id="interno_esterno" class="text ui-widget-content ui-corner-all" />
                    <option value="1">Interno</option>
                    <option value="2">Esterno</option>
                    
                </select>
                </span>
                <label for="descrizione2">Descrizione</label>
                <input type="text" name="Base_Nome" id="descrizione2" value="" class="text ui-widget-content ui-corner-all" />
                <label for="costo2">Costo (&euro;)</label>
                <input type="text" name="Costo_Costo" id="costo2" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup-costo2">Markup</label>
                <input type="text" name="Costo_Markup" id="markup-costo2" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup-costo2" value="" class="text ui-widget-content ui-corner-all" >
                	<option value="1">Valore assoluto</option>
                	<option value="2">%</option>
                	
                </select>
                <label for="transfer-costo2">Transfer price (&euro;)</label>
                <input type="text" name="Costo_TransferPrice" id="transfer-costo2" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
            
            <br/><br/>
            <h2>Budget non clinico</h2>
            <!--button id="add-CTC">Aggiungi markup CTC</button> <button id="create-cost-2">Aggiungi costo non clinico</button-->
            <div id="added-costs-3" class="ui-widget cost-table">
	            <h1>Costi aggiuntivi per paziente:</h1>
	            <table id="costs-3" class="ui-widget ui-widget-content">
	            <thead>
	            <tr class="ui-widget-header ">
		            <th>Descrizione</th>
		            <th>Categoria</th>
		            <th>Transfer price (&euro;)</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	        </div>
	        <div id="added-costs-4" class="ui-widget cost-table">
	            <h1>Costi aggiuntivi per studio:</h1>
	            <table id="costs-4" class="ui-widget ui-widget-content">
	            <thead>
	            <tr class="ui-widget-header ">
		            <th>Descrizione</th>
		            <th>Categoria</th>
		            <th>Transfer price (&euro;)</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	        </div>
	        <div id="added-costs-5" class="ui-widget cost-table">
	            <h1>Rimborsi a pi&egrave; di lista:</h1>
	            <table id="costs-5" class="ui-widget ui-widget-content">
	            <thead>
	            <tr class="ui-widget-header ">
		            <th>Descrizione</th>
		            <th>Transfer price (&euro;)</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	        </div>
            
             <div id="totali-CTC" class="ui-widget cost-table">
	            <h1>Totale budget:</h1>
	            <table id="table-tot" class="ui-widget ui-widget-content">
	            <thead>
	            <tr class="ui-widget-header ">
		            <th>Descrizione</th>
		            <th>Transfer price (&euro;)</th>
		            <th>Totale budget (&euro;)</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	        </div>
	        <!--button id="create-target">Aggiungi target</button-->
	        <div id="advised-markup" class="ui-widget cost-table">
	            <h1>Markup stimato:</h1>
	            <table id="table-advised-markup" class="ui-widget ui-widget-content">
	            <thead>
	            <tr class="ui-widget-header ">
	            	<th>Tipologia</th>
		            <th>Target</th>
		            <th>Transfer price di confronto (&euro;)</th>
		            <th>Markup stimato</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	        </div>
	        <div id='pazienti-tabs-3'></div>
	        
           	<div id="dialog-form-target" title="Aggiungi target">
                
                <form>
                <fieldset>
                <label for="target">Tipo di applicazione</label>
                <select  name="target" id="target" class="text ui-widget-content ui-corner-all" onchange="prepareTargetForm();" />
                    <option value="1">Per visita</option>
                    <option value="2">Per paziente</option>
                    <option value="3">Per studio</option>
                </select>
                <span id='target-form'></span>
                </fieldset>
                </form>
            </div>
            
        </div>
        <div id="tabs-4">
            
            
            
            
            
            
        </div>
         <div id="tabs-5">
            
            <#assign folderBudgetStudioList=el.getChildrenByType("FolderBudgetStudio") />
            <#list folderBudgetStudioList as budgetStudioList>
       		<#assign folderNewBudget=budgetStudioList.id />
       		<#if (budgetStudioList.getChilds()?size>0) >
           	<table class='budget-studio' cellspacing=0 border=0 cellpadding=0 >
           	<tr>
           	<th colspan=2>Versioni a confronto</th>
           	<th>Versione</th>
           	<th>Note</th>
           	<th>Versione finale</th>
           	</tr>
           
       		
	            <#list budgetStudioList.getChilds() as currBudgetStudio>  
	            	<#assign typeNewBudget=currBudgetStudio.type.id />  
	            	<tr>
		           	<td ><input type='radio' name='confronto1' value='${currBudgetStudio.id}'></td>
		           	<td ><input type='radio' name='confronto2' value='${currBudgetStudio.id}'></td>
		           	<td><a href="${baseUrl}/app/documents/custom/budget_studio/${currBudgetStudio.id}"><#attempt><!-- @elementTitle currBudgetStudio /-->
		           	Budget studio v.<#if (currBudgetStudio.getfieldData("Budget","Versione")?size>0) >
    	 ${currBudgetStudio.getfieldData("Budget","Versione")[0]}
    	</#if><#recover>Budget Studio</#attempt></a>&nbsp;</td>
		           	<td>
		           	
		           	<#if (currBudgetStudio.getfieldData("Budget","Note")?size>0) >
			    	 ${currBudgetStudio.getfieldData("Budget","Note")[0]}
			    	</#if>
		           	</td>
		           	<td><#if (currBudgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")?? && currBudgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")?size>0 && currBudgetStudio.getFieldDataStrings("BudgetCTC","Definitivo")[0]=="1") >S&igrave;<#else>No</#if></td>
		           	</tr>        	
	            	
	            </#list>
           
            </table>
            <input type="button" class="submitButton round-button blue" onclick="compareBudgetStudio();" value="Confronta budget studio" />
            </#if>
            </#list>
           
          
            
            
        </div>
        </div>
 

    </div>
   <#include "../helpers/budgetActions.ftl"/>
