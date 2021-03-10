<#assign budget=el />
<#assign budgetBase=el.getParent().getParent() />
<#assign center=budgetBase.getParent() />
<#assign tabs=[] />
<#assign tabsContent=[] />
<#include "../helpers/MetadataTemplate.ftl"/>
 <div class="row">
   		<div class="col-xs-9">
   		<div style="text-align:right">
   		<#--button class="btn btn-warning" id="Salva"  onclick="saveAll();"><i class="icon-save"></i> <b>Salva</b></button>
		<button class="btn btn-primary" id="clona"  onclick="openClone(${el.id},true);"><i class="icon-copy"></i> Copia</button>
		<#--button class="btn btn-primary" id="nuovo" onclick="window.location.href='${baseUrl}/app/documents/addChild/${el.getParent().id}/${elType.id}';" >Crea nuovo budget</button-->
   		 <#--include "../helpers/budget/bracciForm.ftl"/-->
<button class="btn btn-primary" onclick="window.location.href='${baseUrl}/app/documents/detail/${el.parent.parent.id}';"> Torna al budget complessivo</button>
			<#include "../helpers/budgetActions.ftl"/>
		<#assign approvazione=budget.getChildrenByType("FolderApprovazione") />
		<#if approvazione?? && (approvazione?size > 0) >
			<#assign approvazioneDetails=approvazione[0].getChildren() />
			<#if !(approvazioneDetails?? && (approvazioneDetails?size > 0)) >
				<button class="btn btn-primary" id="clona"  onclick="inviaServizi(${el.id},true);">Invia ai servizi</button>		
			</#if>
		</#if>
		</div>
		
    <div style="display: block">	
         
   

        <div id='centerElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
        <div id="tabs" class="tabbable">
        <ul style='height:27px'  class="nav nav-tabs">
        <li><a id='tab1' href="#tabs-1" data-toggle="tab" >Flowchart</a></li>
        <li><a id='tab2' href="#tabs-2" data-toggle="tab" >SSN/SSR</a></li>
        <li><a id='tab4' href="#tabs-4" data-toggle="tab" >Budget PI/Servizi</a></li>
        <li><a id='tab5' href="#tabs-5" data-toggle="tab" >Budget studio</a></li>
        <li><a id='tab6' href="#tabs-6" data-toggle="tab" >Bracci</a></li>
        <!--li><a id='tab3' href="#tabs-3">Budget studio</a></li-->
        </ul>
        <div  class="tab-content" >
        <div id="tabs-6" class="tab-pane">
         	<#assign allBudgets=el.getParent().getChildren() />
        	<#include "../helpers/budget/tabellaVersioniBracci.ftl"/>
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
            <#include "../helpers/budget/prestazioniForm.ftl" />
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
        <div id="tabs-2" class="tab-pane">
         <!--canvas id='grafico' width="1200" height="500" ></canvas-->
         <div id='grafico' style="display:block"></div>
         <div id='legenda'><span style="display:inline-block;width:10px;height:10px;background-color:lightblue;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni aggiuntive rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:orange;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie ma nel caso specifico rimborsate dal promotore&nbsp;&nbsp;</span><br/><span style="display:inline-block;width:10px;height:10px;background-color:white;border:1px solid #a4a4a4;"></span><span style="display:inline-block;font-size:17px;font-weight:200;">&nbsp;&nbsp;prestazioni routinarie a carico SSN/SSR</span></div>
         <div id='rimborsabilita'></div>
        </div>
        <div id="tabs-3" class="tab-pane" style="display:none">
        
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
                    <option value="5">Rimborsi a pi&egrave; di lista</option>
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
	            <h1>Rimborsi a pi&egrave; di lista:</h1>
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
        <#assign canCopyStudio=true />
		<#include "../helpers/budget/tabellaVersioniStudio2.ftl"/>
        <#include "../helpers/budget/tabClinicoView3.ftl"/>
        </div>
        </div>
        

     
  
    </div>
   
    </div>
<#include "../helpers/budgetStatusBar.ftl"/>
 </div>