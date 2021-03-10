
<div id="tabs-4" class="tab-pane">
		 
        <div id='clinico'>
        <div style="float:right">
        <#if !(nobutton??) >
         <button id="applicaSSN" class="submitButton round-button blue templateForm btn btn-info" >
			<i class="icon-euro bigger-160"></i>
			<b> Applica valori SSR</b>
			</button>
        <button id="create-cost" class="submitButton round-button blue templateForm btn btn-info" >
			<i class="icon-plus bigger-160"></i>
			<b> Attivit&agrave;/Prestazione extra</b>
			</button>
			<button id="create-ca" class="submitButton round-button blue templateForm btn btn-info" >
			<i class="icon-plus bigger-160"></i>
			<b> Costi studio-specifici</b>
			</button>
			</#if>
			</div>
			 <div class="clearfix"></div>
        <div id="costi"></div>
        <br/>
        <fieldset>
            <legend>Budget clinico</legend>
        <div id="added-costs-1" style="min-width:500px;" class="ui-widget cost-table col-xs-6">
            <legend>Attivit&agrave;/Prestazioni a richiesta:</legend>
            <table id="costs-1" class="table table-striped table-bordered table-hover">
            <thead>
            <tr >
            <th>Descrizione</th>
            <th>Transfer price (&euro;)</th>
            <th>Modifica</th>
            <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
        		<tr>
            <td colspan=4><span class="help-button">?</span> Tabella riassuntiva delle prestazioni cliniche richiedibili per paziente </td>
            
            </tr>
        		
            </tbody>
            </table>
        </div>
        <#--div id="added-costs-2" style="min-width:500px;" class="ui-widget cost-table col-xs-6">
            <legend>Attivit&agrave;/prestazioni extra per studio:</legend>
            <table id="costs-2" class="table table-striped table-bordered table-hover">
            <thead>
            <tr>
            <th>Descrizione</th>
            <th>Transfer price (&euro;)</th>
            <th>Modifica</th>
            <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
     		  <tr>
            	<td colspan=4><span class="help-button">?</span> Tabella riassuntiva delle prestazioni cliniche richiedibili per studio </td>
            
           	  </tr>
            </tbody>
            </table>
        </div-->
        
        <div class="clearfix"></div>
       <br/>
        
        <div id="added-ca" style="min-width:500px;" class="ui-widget cost-table col-xs-12">
            <legend>Costi studio-specifici:</legend>
            <table id="costs-3" class="table table-striped table-bordered table-hover">
            <thead>
            <tr >
            <th>Tipologia</th>
            <th>Descrizione</th>
            <th>Descrizione braccio di controllo</th>
            <th>Quantit&agrave;</th>
            <th>Totale valore (&euro;)</th>
            <th>Modifica</th>
            <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
        		<tr>
            <td colspan=7><span class="help-button">?</span> Tabella riassuntiva dei costi aggiuntivi </td>
            
            </tr>
        		
            </tbody>
            </table>
        </div>
       </fieldset>
      
            <#include "extraForm.ftl"/>
            
            <div id="dialog-form-n-pat" title="Numero di pazienti">
                <form>
                <fieldset>
                <label for="n-pat">Numero di pazienti</label>
                <input type="text" name="BudgetCTC_NumeroPazienti" id="n-pat" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>
            
            <#include "transferForm.ftl"/>
            <#include "costiForm.ftl"/>
            
            </div>
   </div>