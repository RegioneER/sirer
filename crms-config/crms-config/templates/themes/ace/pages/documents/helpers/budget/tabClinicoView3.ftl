
<div id="tabs-4" class="tab-pane">
		 
        <div id='clinico'>
        <div style="float:right">
       
			</div>
			 <div class="clearfix"></div>
        <div id="costi"></div>
        <#--br/>
        <fieldset>
            <legend>Budget clinico</legend>
        <div id="added-costs-1" style="min-width:500px;" class="ui-widget cost-table col-xs-6">
            <legend>Prestazioni a richiesta:</legend>
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
        
        <div class="clearfix"></div-->
       
       
        <!--button id="create-cost">Aggiungi costo clinico</button-->
             <#include "extraForm.ftl"/>
            
            <!--button id="add-n-pat">Numero di pazienti previsto</button-->
            <div id="dialog-form-n-pat" title="Numero di pazienti">
                <form>
                <fieldset>
                <label for="n-pat">Numero di pazienti</label>
                <input type="text" name="BudgetCTC_NumeroPazienti" id="n-pat" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>
            
            <#include "transferForm.ftl"/>
            </fieldset>
            </div>
   </div>