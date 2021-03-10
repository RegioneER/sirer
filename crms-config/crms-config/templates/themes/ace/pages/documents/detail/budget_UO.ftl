<#assign budget=el />
<#assign center=el.getParent() />
<#assign tabs=[] />
<#assign tabsContent=[] />
<#include "../helpers/MetadataTemplate.ftl"/>
<#assign nobutton=true />
 <div class="row">
   		<div class="col-xs-9">
   		<div style="text-align:right">
   		<button class="btn btn-warning" id="Salva"  onclick="saveAll();"><i class="icon-save"></i> <b>Salva</b></button>
		
		
   		 <#include "../helpers/budget/bracciFormView.ftl"/>
			<#include "../helpers/budgetActions.ftl"/>
		</div>
    <div style="display: block">
	
     

        <div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
        <div id="tabs" class="tabbable">
        <ul style='height:27px'  class="nav nav-tabs">
        <li><a id='tab1' href="#tabs-1" data-toggle="tab" >Flowchart</a></li>
        <li><a id='tab2' href="#tabs-2" data-toggle="tab" >SSN/SSR</a></li>
        <li><a id='tab4' href="#tabs-4" data-toggle="tab" >Budget PI/Servizi</a></li>
        <li><a id='tab6' href="#tabs-6" data-toggle="tab" >Controllo versioni</a></li>
        <!--li><a id='tab3' href="#tabs-3">Budget studio</a></li-->
        </ul>
        <div  class="tab-content" >
        <div id="tabs-6" class="tab-pane">
         	<#assign allBudgets=center.getChildrenByType('Budget') />
        	<#include "../helpers/budget/tabellaVersioni.ftl"/>
        </div>
        <div id="tabs-1" class="tab-pane">
        <div id="example"></div>
        <!--button id="tp-button">Aggiungi visita</button-->
            <#include "../helpers/budget/formTimePoint.ftl" />
             <div id="prestazione-dialog" title="Nuova Prestazione">
                <form>
                <fieldset>
                <label for="Altro_Descrizione">Descrizione</label>
                <input type="text" name="PrestazioniDizionario_Descrizione" id="Altro_Descrizione" value="" class="text ui-widget-content ui-corner-all" />
                
                
                 </fieldset>
                </form>
            </div>
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
        <div id="tabs-2" class="tab-pane">
         <!--canvas id='grafico' width="1200" height="500" ></canvas-->
         <div id='grafico' style="display:block"></div>
         <div id='legenda'><span style="display:inline-block;width:10px;height:10px;background-color:lightblue;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni aggiuntive rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:orange;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie ma nel caso specifico rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:white;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie a carico SSN/SSR</span></div>
         <div id='rimborsabilita'></div>
        </div>
        
        <#include "../helpers/budget/tabClinico.ftl"/>
            </div>
            </div>  
            
            
            
            
        </div>
        </div>

<#include "../helpers/budgetStatusBar.ftl"/>
 </div>