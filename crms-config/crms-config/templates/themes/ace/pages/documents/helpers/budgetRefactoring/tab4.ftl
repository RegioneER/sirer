
<div id="tabs-4" class="tab-pane">
    <div id='clinico'>
        <div style="float:right">
            <#if !(nobutton??) && !readonly >
            <button id="create-cost" class="submitButton round-button blue templateForm btn btn-info" >
                <i class="icon-plus bigger-160"></i>
                <b>Prestazione/Attivit&agrave; aggiuntiva</b>
            </button>
            <button id="create-ca" class="submitButton round-button blue templateForm btn btn-info" >
                <i class="icon-plus bigger-160"></i>
                <b>Servizio aggiuntivo studio specifico</b>
            </button>
        </#if>
    </div>
    <div class="clearfix"></div>
    <div id="costi"></div>
    <br/>
    <fieldset>
        <div id="added-costs-1" style="min-width:500px;" class="ui-widget cost-table col-xs-12">
            <legend>Prestazioni/Attivit&agrave; aggiuntive:</legend>
            <table id="costs-1" class="table table-striped table-bordered table-hover">
                <thead>
                <tr >
                    <th>Servizi/Sezioni coinvolte</th>
                    <th>Codice prestazione SSR:</th>
                    <th>Descrizione</th>
                    <th>Tariffa da nomenclatore (&euro;)</th>
                    <th>Tariffa Prestazione (&euro;)</th>
                    <th>N. Prest./ Paziente</th>
                    <th>Codice modalit&agrave; copertura oneri finanziari<br/>(A, B, C, D, E)</th>
                    <th>Modifica</th>
                    <th>Rimuovi</th>
                </tr>
                </thead>
                <tbody>
                <tr>
                    <td colspan="9"><span class="help-button">?</span> Tabella riassuntiva delle prestazioni/attivit&agrave; aggiuntive</td>

                </tr>

                </tbody>
            </table>
        </div>
        <#--div id="added-costs-2" style="min-width:500px;" class="ui-widget cost-table col-xs-6">
        <legend>Attivit&agrave;/prestazioni extra per studio:</legend>
        <table id="costs-2" class="table table-striped table-bordered table-hover">
            <thead>
            <tr>
                <th>Descrizione</th>
                <th>Transfer price (&euro;)</th>
                <th>Modifica</th>
                <th>Rimuovi</th>
            </tr>
            </thead>
            <tbody>
            <tr>
                <td colspan=4><span class="help-button">?</span> Tabella riassuntiva delle prestazioni cliniche richiedibili per studio </td>

            </tr>
            </tbody>
        </table>
        </div-->

        <div class="clearfix"></div>
        <br/>

        <div id="added-ca" style="min-width:500px;" class="ui-widget cost-table col-xs-12">
            <legend>Altri servizi aggiuntivi studio specifici</legend>
            <table id="costs-3" class="table table-striped table-bordered table-hover">
                <thead>
                <tr >
                    <th>Descrizione</th>
                    <!--th>Previsto</th-->
                    <!--th>Descrizione braccio di controllo</th-->
                    <th>Codice Modalità Copertura Oneri Finanziari (A,B,C,D,E)</th>
                    <th>Totale valore (&euro;)</th>
                    <th>Modifica</th>
                    <th>Rimuovi</th>
                </tr>
                </thead>
                <tbody>
                <tr>
                    <td colspan=7><span class="help-button">?</span> Tabella riassuntiva dei servizi aggiuntivi per studio</td>

                </tr>

                </tbody>
            </table>
        </div>
    </fieldset>

    <#include "../budget/extraForm.ftl"/>

    <!--div id="dialog-form-n-pat" title="Numero di pazienti">
        <form>
            <fieldset>
                <label for="n-pat">Numero di pazienti</label>
                <input type="text" name="BudgetCTC_NumeroPazienti" id="n-pat" value="" class="text ui-widget-content ui-corner-all" />

            </fieldset>
        </form>
    </div-->

    <#-- include "../budget/transferForm.ftl"/ -->
    <#include "../budget/costiForm.ftl"/>
    <#assign legendaCosti=true />
    <#include "../legenda.ftl"/>

</div>
</div>
<@script>

var folderPXPId=${el.getChildrenByType('FolderPXP')[0].id};
var folderCostiAggiuntiviId=${el.getChildrenByType('FolderCostiAggiuntivi')[0].id};
$(document).ready(function(){
    loadBC();
});


</@script>
<script src="/sirer-static/js/budget/tab4.js"></script>
