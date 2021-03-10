<div id="clone-dialog-form" title="Copia budget">
    <form>
    <fieldset>
    <!--label for="Budget_Versione">Versione</label-->
    
    <!--input type="hidden" name="Budget_Versione" id="Budget_Versione" value="" class="text ui-widget-content ui-corner-all" /.-->
    <label for="BudgetCTC_Tipologia2">Tipologia</label>
                <select  name="BudgetCTC_Tipologia" id="BudgetCTC_Tipologia2" class="text ui-widget-content ui-corner-all" >
                	<option></option>
                	<option value="1###Versione Sponsor">Versione Sponsor</option>
                	<option value="2###Versione PI">Versione PI</option>
                	<option value="3###Versione NRC">Versione NRC</option>
                </select>
    <label for="Budget_Note">Note</label>
    <textarea name="Budget_Note" id="Versione_Note" cols="100" rows="6"  class="text ui-widget-content ui-corner-all"></textarea>
    <input type="hidden" name="BudgetCTC_Definitivo" id="BudgetCTC_Definitivo" value="" class="text ui-widget-content ui-corner-all"/>
    <input type="hidden" name="clone_id" id="clone_id" value="" class="text ui-widget-content ui-corner-all"/>
        </fieldset>
    </form>
</div>
<div id="clone2-dialog-form" title="Copia budget">
    <form>
    <fieldset>
    <!--label for="Base_Nome2">Nome</label-->
    <!--input type="hidden" name="Base_Nome" id="Base_Nome2" value="" class="text ui-widget-content ui-corner-all" /-->
    <!--label for="Budget_Versione2">Versione</label-->
    <!--input type="hidden" name="Budget_Versione" id="Budget_Versione2" value="" class="text ui-widget-content ui-corner-all" /-->
    <label for="Budget_Note2">Note</label>
    <textarea name="Budget_Note" id="Budget_Note2" cols="100" rows="6"  class="text ui-widget-content ui-corner-all"></textarea>
   
     <input type="hidden" name="ApprovazioneClinica_Approvato" id="ApprovazioneClinica_Approvato2" value="" class="text ui-widget-content ui-corner-all"/>
     <input type="hidden" name="ApprovazioneClinica_InviaServizi" id="ApprovazioneClinica_InviaServizi" value="" class="text ui-widget-content ui-corner-all"/>
     <input type="hidden" name="noSkipBudgetCTC" id="noSkipBudgetCTC" value="1" class="text ui-widget-content ui-corner-all"/>
     <input type="hidden" name="ChiusuraBudget_Chiuso" id="ChiusuraBudget_Chiuso2" value="" class="text ui-widget-content ui-corner-all"/>
         <input type="hidden" name="clone_id" id="clone_id2" value="" class="text ui-widget-content ui-corner-all"/>
        </fieldset>
    </form>
</div>
<div id="clone3-dialog-form" title="Copia budget in altro centro">
    <form>
    <fieldset>
    <select  name="inCentro" id="inCentro" class="text ui-widget-content ui-corner-all" >
        <option></option>
    </select>
    <label for="Budget_Note2">Note</label>
    <textarea name="Budget_Note" id="Budget_Note2" cols="100" rows="6"  class="text ui-widget-content ui-corner-all"></textarea>
   
     <input type="hidden" name="ApprovazioneClinica_Approvato" id="ApprovazioneClinica_Approvato2" value="" class="text ui-widget-content ui-corner-all"/>
     <input type="hidden" name="ApprovazioneClinica_InviaServizi" id="ApprovazioneClinica_InviaServizi" value="" class="text ui-widget-content ui-corner-all"/>
     <input type="hidden" name="noSkipBudgetCTC" id="noSkipBudgetCTC" value="1" class="text ui-widget-content ui-corner-all"/>
     <input type="hidden" name="ChiusuraBudget_Chiuso" id="ChiusuraBudget_Chiuso2" value="" class="text ui-widget-content ui-corner-all"/>
         <input type="hidden" name="clone_id" id="clone_id3" value="" class="text ui-widget-content ui-corner-all"/>
        </fieldset>
    </form>
</div>