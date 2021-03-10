
<div id="tabs-4" class="tab-pane">
		 
        <div id='clinico'>
        <div style="float:right">
         <div id="dialog-form-prezzo" title="Aggiungi prezzo finale">
                <p class="validateTips"></p>
                <form>
                <fieldset>
                <div id='tariffaSSN'>Tariffa SSR: <span  id='valoreSSN'></span> &euro;</div>
               	<div id='tariffaAlpi'>Tariffa ALPI: <span  id='valoreAlpi'></span> &euro;</div>
               	<div id='tariffaSolvente'>Tariffa Solvente: <span  id='valoreSolvente'></span> &euro;</div>
               	<div id='transferPrice'>Transfer Price: <span  id='valoreTransferPrice'></span> &euro;</div>
               	<br><br>
                <label for="PrezzoFinale_Prezzo">Prezzo (&euro;) <span style="color:red">(Obbligatorio)</span></label>
                <input type="text" name="PrezzoFinale_Prezzo" id="PrezzoFinale_Prezzo" value="" class="text ui-widget-content ui-corner-all" />
                </fieldset>
                </form>
            </div>
       
			
			</div>
			 <div class="clearfix"></div>
       
        <br/>
        <fieldset>
           <#assign tabs=[] />
		<#assign tabsContent=[] />
		<#assign tabs=tabs+[{"target":"tabNonClinico","label":"Budget non clinico"}] />
		<#assign tabs=tabs+[{"target":"tabClinico","label":"Budget clinico"}] />
		<#--assign tabs=tabs+[{"target":"tabStudio","label":"Budget studio"}] /-->
        <#assign currTabContent>
        <#--div id="added-costs-2" class="ui-widget cost-table">
            <legend>Attivit&agrave;/prestazioni extra per studio::</legend>
            <table id="costs-2" class="table table-striped table-bordered table-hover">
            <thead>
            <tr>
            <th>Descrizione</th>
            <th>Prezzo (&euro;)</th>
            <th>Modifica il prezzo</th>
            
            </tr>
            </thead>
            <tbody>
            
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
            <th>Costo (&euro;)</th>
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
        <div class="clearfix"></div>
       </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"tabClinico" }] />
        <#assign currTabContent>
        		<table id="tablesList" style="width:100%" ><tr><td>
	        <div id="added-costs-4" class="ui-widget cost-table">
	            <fieldset> <legend>Attivit&agrave;/prestazioni extra per studio:</legend>
	            <table id="costs-4" class="table table-striped table-bordered table-hover">
	            <thead>
	            <tr">
		            <th>Descrizione</th>
		            <th>Categoria</th>
		            <th>Prezzo (&euro;)</th>
		            <th>Modifica</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	            </fieldset>
	        </div>
	        </td></tr><tr><td>
	        <div id="added-costs-5" class="ui-widget cost-table">
	            <fieldset> <legend>Rimborsi a pi&egrave; di lista</legend>
	            <table id="costs-5"class="table table-striped table-bordered table-hover">
	            <thead>
	            <tr>
		            <th>Descrizione</th>
		            <th>Prezzo (&euro;)</th>
		            <th>Modifica</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	            </fieldset>
	        </div>
            </td></tr></table>
        </#assign>
	    			<#assign tabsContent=tabsContent+[{"content":currTabContent,"id":"tabNonClinico" }] />
       		 <@tabbedView tabs tabsContent "tabNonClinico" />
            <div id="dialog-form-cost-2" title="Aggiungi costo non clinico">
                
                <form>
                <fieldset>
                <label for="tipologia2">Tipo di applicazione</label>
                <select  name="tipologia" id="tipologia2" class="text ui-widget-content ui-corner-all" onchange="changeTipologia();if(this.value==5)$('#catbox').hide();else $('#catbox').show()" />
                    
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
                <label for="Prestazioni_prestazione">Descrizione</label>
                
                <input type="text" name="Base_Nome" id="Prestazioni_prestazione" value="" class="text ui-widget-content ui-corner-all" />
                <span class="tip_exclusive">
                <label for="Prestazioni_CDC">Competenza</label>
                
                <input type="text" name="Prestazioni_CDC" id="Prestazioni_CDC" value="" class="text ui-widget-content ui-corner-all" />
                </span>
                <label for="costo2">Costo (&euro;)</label>
                <input type="text" name="Costo_Costo" id="costo2" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup-costo2">Markup</label>
                <input type="text" name="Costo_Markup" id="markup-costo2" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup-costo2" value="" class="text ui-widget-content ui-corner-all" >       	
                	<option value="2" selected >%</option>
                	<option value="1">Valore assoluto</option>
                </select>
                
                <label for="prezzo-add">Prezzo (&euro;)</label>
                <input type="text" name="Costo_Prezzo" id="prezzo-add" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="idx" id="idx" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_UOCCode" id="Prestazioni_UOCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_UOC" id="Prestazioni_UOC" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_CDCCode" id="Prestazioni_CDCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="dizionario" id="dizionario" value="" class="text ui-widget-content ui-corner-all" />
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
            </fieldset>
            </div>
   </div>