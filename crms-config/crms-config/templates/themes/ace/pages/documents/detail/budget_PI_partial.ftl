
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
                <input type="hidden" name="dizionario" id="dizionario" value="" class="text ui-widget-content ui-corner-all" />
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
        
        <#include "../helpers/budget/tabClinico.ftl"/>
        </div>
  <button style='display:inline-block;font-size=14px;' id="Salva" onclick="saveAll();">Salva</button>    <button style='display:inline-block;font-size=14px;' id="clona" onclick="cloneObj(${el.id},true);">Copia questa versione del budget</button>            
  

    </div>
   <#include "../helpers/budgetActions.ftl"/>
