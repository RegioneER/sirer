			<div id="dialog-form-transfer" title="Aggiungi transfer price">
                <p class="validateTips"></p>
                <form>
                <fieldset>
                <div id='tariffaSSN'>Tariffa SSR: <span  id='valoreSSN'></span> &euro;</div>
               	<!--div id='tariffaAlpi'>Tariffa aziendale: <span  id='valoreAlpi'></span> &euro;</div-->
               	<!--div id='tariffaSolvente'>Tariffa aziendale: <span  id='valoreSolvente'></span> &euro;</div-->
               	<span>
                <#--@SingleFieldByType "Costo" "Copertura" availableTypes.PrestazioneXPaziente userDetails true /-->
                <label for="Costo_Copertura">Copertura del costo<span class="red">*</span></label>
			     <select name="Costo_Copertura" id="Costo_Copertura">
			    <option></option>
			        <option value="1###A: fondi della struttura sanitaria">fondi della struttura sanitaria</option>
			        <option value="2###B: finanziamento proveniente da terzi">finanziamento proveniente da terzi</option>
			        <option value="3###C: fondo aziendale come previsto dal D.M. 17/12/2004">fondo aziendale come previsto dal D.M. 17/12/2004</option>
			        <option value="4###D: a carico del promotore profit">a carico del promotore profit</option>
			</select>
                </span>
               	<#--label for="oreuomo">Tempo uomo</label>
                <input type="text" name="Costo_OreUomo" id="oreuomo" style="width:35px;" value="" class="text ui-widget-content ui-corner-all" /> Ore <input sise="2" style="width:30px;" type="text" name="Costo_MinutiUomo" id="minuomo" value="" class="text ui-widget-content ui-corner-all" /> Minuti
                <label for="personale">Personale coinvolto</label>
                <input type="text" name="Costo_PersonaleLabel" id="Costo_PersonaleLabel" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_Personale" id="Costo_Personale" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_PersonaleMatricola" id="Costo_PersonaleMatricola" value="" class="text ui-widget-content ui-corner-all" />
                <label for="oremacchina">Ore macchina</label>
                <input type="text" name="Costo_OreMacchina" id="oremacchina" value="" class="text ui-widget-content ui-corner-all" /-->
                <label for="costo">Costo (&euro;)</label>
                <input type="text" name="Costo_Costo" id="costo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup">Mark-up</label>
                <input type="text" name="Costo_Markup" id="markup" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup" value="" class="text ui-widget-content ui-corner-all" >
                	<option value="2" selected >%</option>
                	<option value="1">Valore assoluto</option>	
                	
                </select>
                <label for="transfer">Transfer Price (&euro;) <span style="color:red">(Obbligatorio)</span></label>
                <input type="text" name="Costo_TransferPrice" id="transfer" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_Braccio" id="transfer" value="" class="text ui-widget-content ui-corner-all" />
                
                </fieldset>
                </form>
            </div>