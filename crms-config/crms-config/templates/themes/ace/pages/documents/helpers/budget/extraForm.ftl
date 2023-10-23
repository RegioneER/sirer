<style>
.icon-time::before{
	display:none;
}
#Costo-Costo_Copertura label{

     display: block !important;
     float: none !important;
     margin: 0 !important;
     padding: 0 !important;
 }

#Prestazioni-Prestazioni_Opzionale {
    display: block !important;
    float: none !important;
    margin: 0 !important;
    padding: 0 !important;
}
</style>
<div id="dialog-form" title="Aggiungi Prestazione/Attivit&agrave;">
                
                <form>
                <fieldset>
                <div class="alert alert-block alert-info" id="budgetChange3">	<i class="icon-info-sign blue bigger-140"></i> I campi contrassegnati da "<span class="red">*</span>" sono obbligatori</div>

                <input type="hidden" value="1"  name="tipologia" onchange="changeTipologia();" id="tipologia" class="dont-clear text ui-widget-content ui-corner-all" />
                <span >
                <label for="Prestazioni_CDC2">Servizi/Sezioni coinvolti<span class="red">*</span></label>
                <input type="text" name="Prestazioni_CDC" id="Prestazioni_CDC2" value="" class="text ui-widget-content ui-corner-all" />
                </span>
                <label for="descrizione">Descrizione<span class="red">*</span></label>
                <input type="text" name="Base_Nome" id="descrizione" value="" class="text ui-widget-content ui-corner-all" />
                <#if availableTypes.PrestazioneXPaziente?? >
                    <@SingleFieldByType "Prestazioni" "Attivita" availableTypes.PrestazioneXPaziente userDetails true />
                </#if>
                <span >
                <label for="Costo_Copertura">Copertura del costo<span class="red">*</span></label>
			     <select name="Costo_Copertura" id="Costo_Copertura">
			    <option></option>
			        <option value="1###A">A</option>
			        <option value="2###B">B</option>
			        <option value="3###C">C</option>
			        <option value="4###D">D</option>
				<option value="5###E">E</option>
			</select>
                </span>
                <input type="hidden" name="Costo_Personale" id="Costo_Personale2" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Costo_PersonaleMatricola" id="Costo_PersonaleMatricola2" value="" class="text ui-widget-content ui-corner-all" />
                <#if availableTypes.PrestazioneXPaziente?? >
                    <@SingleFieldByType "Prestazioni" "Opzionale" availableTypes.PrestazioneXPaziente userDetails true />
                </#if>
    <script>
        $("input[name=Prestazioni_Opzionale]").change(function(){gestCosto_Quantita()});
        function gestCosto_Quantita(){
            var value=false;
            value=$('input[name=Prestazioni_Opzionale]:checked').val();
            if(value=="1###Si"){
                $("#CostoDIV").hide();
                $("#Costo_Quantita").val('');
            }
            else{
                $("#CostoDIV").show();
                $("#Costo_Quantita").val('1');
            }
        }
    </script>
                <div id="CostoDIV">
                <label for="Costo_Quantita">Quantit&agrave; a paziente <span class="red">*</label>
                <input type="text" name="Costo_Quantita" id="Costo_Quantita" value="" class="text ui-widget-content ui-corner-all" />
                </div>
                <label for="costo-costo">Costo (&euro;)<span class="ssn_diz" ></span></label>
                <input type="text" name="Costo_Costo" id="costo" value="" class="text ui-widget-content ui-corner-all" />
                <label for="markup-costo">Markup</label>
                <input type="text" name="Costo_Markup" id="markup-costo" value="" class="text ui-widget-content ui-corner-all" />
                <select name="Costo_MarkupUnita" id="unita-markup-costo" value="" class="text ui-widget-content ui-corner-all" >
                	<option value="2" selected >%</option>
                	<option value="1">Valore assoluto</option>
                </select>
                <label for="transfer-costo">Importo (Tariffa) (&euro;)<span class="red">*</span></label>
                <input type="text" name="Costo_TransferPrice" id="transfer-costo" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" id="idx" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" id="Prestazioni_Codice2" name="Prestazioni_Codice" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" id="Prestazioni_CDCCode2" name="Prestazioni_CDCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" id="Prestazioni_UOC2" name="Prestazioni_UOC" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" id="Prestazioni_UOCCode2" name="Prestazioni_UOCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" id="Tariffario_Solvente2" name="Tariffario_Solvente" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" id="Tariffario_SSN2" name="Tariffario_SSN" value="" class="text ui-widget-content ui-corner-all" />
               </fieldset>
                </form>
            </div>
