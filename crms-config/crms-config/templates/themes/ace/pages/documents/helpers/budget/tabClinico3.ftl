
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
         </fieldset>
        <div class="clearfix"></div>
       
       
        <!--button id="create-cost">Aggiungi costo clinico</button-->
            <div id="dialog-form" title="Aggiungi costo">
                
                <form>
                <fieldset>
                <div class="alert alert-block alert-info" id="budgetChange3">   <i class="icon-info-sign blue bigger-140"></i> I campi contrassegnati da "<span class="red">*</span>" sono obbligatori</div>
               
                <input type="hidden"  name="tipologia"  id="tipologia" value="1" class="dont-clear text ui-widget-content ui-corner-all" />
                    
                
                <label for="descrizione">Descrizione<span class="red">*</span></label>
                <input type="text" name="Base_Nome" id="descrizione" value="" class="text ui-widget-content ui-corner-all" />
                <span >
                <label for="Prestazioni_CDC2">Competenza<span class="red">*</span></label>
                <input type="text" name="Prestazioni_CDC" id="Prestazioni_CDC2" value="" class="text ui-widget-content ui-corner-all" />
                </span>
                <label for="oreuomo2">Tempo uomo</label>
                <input type="text" name="Costo_OreUomo" id="oreuomo2" style="width:35px;" value="" class="text ui-widget-content ui-corner-all" /> Ore <input sise="2" style="width:30px;" type="text" name="Costo_MinutiUomo" id="minuomo2" value="" class="text ui-widget-content ui-corner-all" /> Minuti
                <label for="personale2">Personale coinvolto</label>
                <input type="text" name="Costo_PersonaleLabel" id="Costo_PersonaleLabel2" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_Personale" id="Costo_Personale2" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_PersonaleMatricola" id="Costo_PersonaleMatricola2" value="" class="text ui-widget-content ui-corner-all" />
                <!--label for="Costo_QuantitaNA">Quantit&agrave; non applicabile</label>
                <input type="checkbox" name="Costo_QuantitaNA" value="1" id="Costo_QuantitaNA"  class="text ui-widget-content ui-corner-all" /-->
                <label for="Costo_Quantita">Quantit&agrave;</label>
                <input type="text" name="Costo_Quantita" id="Costo_Quantita" value="" class="text ui-widget-content ui-corner-all" /> 
                <label for="costo-costo">Costo (&euro;)<span class="ssn_diz" ></span></label>
                <input type="text" name="Costo_Costo" id="costo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup-costo">Markup</label>
                <input type="text" name="Costo_Markup" id="markup-costo" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup-costo" value="" class="text ui-widget-content ui-corner-all" >
                    <option value="2" selected >%</option>
                    <option value="1">Valore assoluto</option>
                    
                </select>
                <label for="transfer-costo">Transfer price (&euro;)<span class="red">*</span></label>
                <input type="text" name="Costo_TransferPrice" id="transfer-costo" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" id="idx" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" id="Prestazioni_CDCCode2" name="Prestazioni_CDCCode" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" id="Prestazioni_UOC2" name="Prestazioni_UOC" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" id="Prestazioni_UOCCode2" name="Prestazioni_UOCCode" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" id="Tariffario_Solvente2" name="Tariffario_Solvente" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" id="Tariffario_SSN2" name="Tariffario_SSN" value="" class="text ui-widget-content ui-corner-all" />
                 <@SingleFieldByType "Prestazioni" "Attivita" availableTypes.PrestazioneXPaziente userDetails true />
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
            
            <#include "transferForm.ftl"/>

            
            </div>
   </div>