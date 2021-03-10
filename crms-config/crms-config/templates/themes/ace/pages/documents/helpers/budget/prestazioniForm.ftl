<div id="prestazione-diz-dialog" title="Nuova Prestazione" style="display: none;">
                <form>
                <fieldset>
                 <div class="ui-widget">
                <label for="Prestazioni_prestazione">Prestazione<span style="color:red">*</span></label>
                <input type="text" name="Prestazioni_prestazione" id="Prestazioni_prestazione" value="" class="text ui-widget-content ui-corner-all" />
                </div>
                <label for="Prestazioni_CDC">Competenza<span style="color:red">*</span></label>
                <input type="text" name="Prestazioni_CDC" id="Prestazioni_CDC" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_CDCCode" id="Prestazioni_CDCCode" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Prestazioni_UOC" id="Prestazioni_UOC" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="dizionario" id="dizionario" value="" class="text ui-widget-content ui-corner-all" />
                <@SingleFieldByType "Prestazione" "Attivita" availableTypes.Prestazione userDetails true />
                <input type="button" name="Prestazioni_Altro" id="Prestazioni_Altro" value="Salva prestazione nel dizionario" onclick="salvaPrestazione(this);"  class="btn btn-warning" />
                 <input type="hidden" name="Prestazioni_Codice" id="Prestazioni_Codice" value="" class="text ui-widget-content ui-corner-all" />
               <input type="hidden" name="Prestazioni_UOCCode" id="Prestazioni_UOCCode" value="" class="text ui-widget-content ui-corner-all" />
                 <input type="hidden" name="Tariffario_Solvente" id="Tariffario_Solvente" value="" class="text ui-widget-content ui-corner-all" />
                <input type="hidden" name="Tariffario_SSN" id="Tariffario_SSN" value="" class="text ui-widget-content ui-corner-all" />
                 </fieldset>
                </form>
            </div>