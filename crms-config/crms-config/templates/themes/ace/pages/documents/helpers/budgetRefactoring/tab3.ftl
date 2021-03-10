<div id="tabs-3" class="tab-pane" style="display:none">
	<h3>Refactoring...</h3>
            <button id="add-CTC">Aggiungi markup CTC</button>
            <div id="dialog-form-CTC" title="Aggiungi markup">
                <form>
                <fieldset>
                <label for="mCTC">Markup (%)</label>
                <input type="text" name="BudgetCTC_Markup" id="mCTC" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>
            <button id="create-cost-2">Aggiungi costo non clinico</button>
           	<div id="dialog-form-cost-2" title="Aggiungi costo non clinico">
                
                <form>
	                <fieldset>
		                <label for="tipologia2">Tipo di applicazione</label>
		                <select  name="tipologia" id="tipologia2" class="text ui-widget-content ui-corner-all" onchange="if(this.value==5)$('#catbox').hide();else $('#catbox').show()" />
		                    <option value="3">Per paziente</option>
		                    <option value="4">Per studio</option>
		                    <option value="5">Pass-through</option>
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
		                	<option value="2" selected >%</option>
		                	<option value="1">Valore assoluto</option>
		                	
		                </select>
		                <label for="transfer-costo2">Transfer price (&euro;)</label>
		                <input type="text" name="Costo_TransferPrice" id="transfer-costo2" value="" class="text ui-widget-content ui-corner-all" />
	                </fieldset>
                </form>
            </div>
            <br/><br/>
            <h2>Budget non clinico</h2>
            <div id="added-costs-3" class="ui-widget cost-table">
	            <h1>Costi aggiuntivi per paziente:</h1>
	            <table id="costs-3" class="ui-widget ui-widget-content">
	            <thead>
	            <tr class="ui-widget-header ">
		            <th>Descrizione</th>
		            <th>Categoria</th>
		            <th>Transfer price (&euro;)</th>
		            <th>Modifica</th>
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
		            <th>Modifica</th>
		            <th>Rimuovi</th>
	            </tr>
	            </thead>
	            <tbody>
	            
	            </tbody>
	            </table>
	        </div>
	        <div id="added-costs-5" class="ui-widget cost-table">
	            <h1>Pass-through:</h1>
	            <table id="costs-5" class="ui-widget ui-widget-content">
	            <thead>
	            <tr class="ui-widget-header ">
		            <th>Descrizione</th>
		            <th>Transfer price (&euro;)</th>
		            <th>Modifica</th>
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
	        <button id="create-target">Aggiungi target</button>
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