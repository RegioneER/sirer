
<style>
    .modal-form-aic .row{
        margin:0px !important;
    }
</style>
<@script>
function visualizzaModalRicerca(){
var myForm=$("#prototypes #dialog-form-aic").clone();

myForm.attr("id","dialog-form-aic-visible");
myForm.find('#button-search').click(function(){visualizzaTabellaRisultatiRicerca()});
var myDialog= bootbox.dialog({
"title":"Cerca Farmaco",
"message":myForm
});

};

function visualizzaTabellaRisultatiRicerca(){
var specialita=$("#dialog-form-aic-visible #SPECIALITA").val();
var aic=$("#dialog-form-aic-visible #AIC").val();
var titolare=$("#dialog-form-aic-visible #TIT_AIC").val();
var principio_attivo=$("#dialog-form-aic-visible #PRINC_ATT").val();
$.ajax({
type : "GET",
url : "/cercaSpecialitaFarmaci.php?SPECIALITA=" + specialita+"&AIC="+aic+"&TIT_AIC="+titolare+"&PRINC_ATT="+principio_attivo,
dataType : "json",
success : function(data) {
if (data.sstatus == 'ko') {
bootbox.alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
//bootbox.hideAll();
}
else {
var myTBODY=$("#dialog-form-aic-visible #cercaFarmaci-table tbody");
myTBODY.html('');
$.each(data, function(skey, sval) {
var myTR=$("<tr>");
    var myTD=$("<td>");
        myTD.html(sval.AIC_MINSAN);
        myTR.append(myTD);
        myTD=$("<td>");
        myTD.html(sval.SPEC_SPECIALITA);
        myTR.append(myTD);
        myTD=$("<td>");
        myTD.html(sval.ATC);
        myTR.append(myTD);
        myTD=$("<td>");
        myTD.html(sval.DITTA);
        myTR.append(myTD);
        myTD=$("<td>");
        var myA=$("<a>");
            myA.attr("href","#");
            $(myA).html('<i class="fa fa-plus fa-2x blue"></i>&nbsp');
            myA.click(function(){
            $("#Farmaco_SpecialitaAIC").val(sval.SPEC_SPECIALITA);
            $("#Farmaco_CodiceAIC").val(sval.AIC_MINSAN);
            $("#Farmaco_ConfezioneAIC").val(sval.AIC_CONF);
            $("#Farmaco_CodiceATC").val(sval.ATC);
            $("#Farmaco_princAtt").tokenInput("clear");
            $("#Farmaco_princAtt").tokenInput("add", {id: sval.SOSTANZA+"###"+sval.DSOST, name: sval.DSOST});
            bootbox.hideAll();
            });
            myTD.append(myA);
            myTR.append(myTD);
            myTBODY.append(myTR);
            });
            }
            }
            });
            }
        </@script>
        <div id="prototypes" style="display:none">
            <div id="dialog-form-aic" title="Cerca Farmaco">
                <div class="modal-form-aic row">
                <span class="row">
                    <label class="col-sm-3 control-label no-padding-right" for="SPECIALITA">Specialità medicinale:</label>
                    <div class="col-sm-9">
                        <input id='SPECIALITA' type='text' size=40 name='SPECIALITA'>
                    </div>
                </span>
                    <span class="row">
                    <label class="col-sm-3 control-label no-padding-right" for="AIC">AIC:</label>
                    <div class="col-sm-9">
                        <input id='AIC' type='text' size=40 name='AIC'>
                    </div>
                </span>

                    <span class="row">
                    <label class="col-sm-3 control-label no-padding-right" for="TIT_AIC">Titolare AIC:</label>
                    <div class="col-sm-9">
                        <input id='TIT_AIC' type='text' size=40 name='TIT_AIC'>
                    </div>
                </span>
                    <span class="row">
                    <label class="col-sm-3 control-label no-padding-right" for="PRINC_ATT">Principio attivo:</label>
                    <div class="col-sm-9">
                        <input id='PRINC_ATT' type='text' size=40 name='PRINC_ATT'>
                    </div>
                </span>

                    <div class="col-sm-3">&nbsp;</div>
                    <div class="col-sm-9">
                        <button id="button-search" class="btn btn-purple btn-sm" >
                            <span id="std-label"><i class="icon-search"></i> Avvia la ricerca</span>
                            <span id="searching-label" style="display:none"><i class="icon-spinner icon-spin"></i> ricerca in corso...</span>
                        </button>
                    </div>
                </div>
                <div class="row" style="clear: both;padding:10px 0px;">
                    <div class="col-xs-12">
                        <div class="col-xs-12">
                            <div class="table-responsive" style="font-size: 14px !important;">
                                <table id="cercaFarmaci-table" class="table table-striped table-bordered table-hover">
                                    <thead>
                                    <tr>
                                        <th class="">AIC</th>
                                        <th class="">Specialità medicinale</th>
                                        <th class="">ATC</th>
                                        <th class="">Ditta</th>
                                        <th class="" style="width: 10%">Azioni</th>
                                    </tr>
                                    </thead>
                                    <tbody>
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </div>
                </div>

            </div>
        </div>