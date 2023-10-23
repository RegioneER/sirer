<style>

    .clearfix:after {
        content: ".";
        display: block;
        height: 0;
        clear: both;
        visibility: hidden;
    }

    .clearfix {
        clear: both;
    }

    .vs {
        float: left;
        width: 50%;
        height: 150px;
    }

    .vs label {
        width: 30%;
    }

    .re {
        float: left;
        width: 40%;
        height: 150px;
    }

    .re label {
        width: 55%;
    }

    .ri {
        float: left;
        width: 80%;
    }

    .ri label {
        width: 55%;
    }

    .vl {
        float: left;
        width: 45%;
    }

    .vl label {
        width: 55%;
    }

    .ui-autocomplete.ui-menu {
        z-index: 9999 !important;
    }

    .view-mode label {
        background-color: #FFFFFF;
        font-weight: normal !important;
        margin: 0;
        padding: 0.25em 0.5em;
        width: 15em;
    }

    .list-table a:hover {
        color: #000000;
        text-decoration: none;
    }

    .list-table a:visited {
        color: #000000;
        text-decoration: none;
    }

    .list-table a {
        color: #000000;
        text-decoration: none;
    }

    .home-fieldset {
        background-color: #DFEFFC;
        border: 1px solid #8AB8DA;
        border-radius: 10px;
        margin-bottom: 20px;
        padding: 5px;
        width: 90%;
    }

    .home-legend {
        background-color: #4084CA;
        border: 1px solid #8AB8DA;
        border-radius: 10px;
        color: #FFFFFF;
        padding: 5px;
    }

    .highlightRow {
        color: #438DD7 !important;
        font-weight: bold;
    }

    .list-table {
    }

    .list-table th {
        background-color: #FFFFFF;
        border-bottom: 1px solid #4D80B4;
        border-left: 1px ridge #4D80B4;
        color: #5D8DBE;
        font-size: 12px;
        font-weight: bold;
        text-align: left;
    }

    .list-table td {
        font-size: 12px;
        padding-left: 2px;
        padding-right: 2px;
        text-align: left;
    }

    .list-table tr:nth-child(2n+1) td {
        background-color: #F0FFFF;
    }

    .list-table tr:nth-child(2n) td {
        background-color: #F5FFFA;
    }

    .done {
        background-color: lightgreen;
        border-radius: 5px;
        padding: 2px;
        vertical-align: middle;
    }

    .pending {
        background-color: #F98F1D;
        border-radius: 5px;
        padding: 2px;
    }

</style>
<#assign parentEl=el/>

<#include "../helpers/MetadataTemplate.ftl"/>
<div class="row">
    <div class="col-xs-9">



        <div style="display: block">
            <div id="task-Actions" style="margin-bottom:10px;text-align:right;"></div>
        </div>
        <#assign titolo> <@msg "template.DatiMonitoraggioClinico"/> </#assign>
        <@TemplateFormTable "DatiMonitoraggioClinico" el userDetails userPolicy.canUpdate titolo/>
    </div>
    <#include "../helpers/attached-file.ftl"/>

</div>

<@script>
$( document ).ready(function() {
	$('#salvaForm-DatiMonitoraggioClinico').off('click').on('click',function(){
		var $form=$($(this).data('rel'));
    if($(this).attr('id')){
    var formName=$(this).attr('id').replace("salvaForm-", "");
    }
    else{
    formName="formNonEsistente"
    }
	
	//LUIGI controllo ad-hoc sulla sequenzialità date
	date_split1=$('#DatiMonitoraggioClinico_dataRiferimentoDa').val().split("/");
	date1= new Date(date_split1[2], date_split1[1]-1, date_split1[0], 0, 0, 0, 0);
	date_split2=$('#DatiMonitoraggioClinico_dataRiferimentoA').val().split("/");
	date2= new Date(date_split2[2], date_split2[1]-1, date_split2[0], 0, 0, 0, 0);
	if (date2<date1){
		alert ('la data di riferimento del rapporto Dal non può essere precedente alla data di riferimento del rapporto Al');
		return false;
	}
	
    var goon=true;
    if (eval("typeof "+formName+"Checks == 'function'")){
    eval("goon="+formName+"Checks()");
    }
    if (!goon) return false;
    loadingScreen("Salvataggio in corso...", "loading");

    try{
    var myElement={};
    myElement.id=loadedElement.id;
    myElement.type=loadedElement.type;
    myElement.metadata={};
    myElement=formToElement($form,myElement,'Farmaco');
    saveElement(myElement).done(function(data){
    bootbox.hideAll();
    if (data.result=="OK") {
    loadingScreen("Salvataggio effettuato", "green_check");


    //Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
    window.setTimeout(function(){
    bootbox.hideAll();
    }, 3000);

    if (data.redirect){
    window.location.href=data.redirect;
    }
    }else {
        var errorMessage="Errore salvataggio! <i class='icon-warning-sign red'></i>";
        if(data.errorMessage.includes("RegexpCheckFailed: ")){
            var campoLabel="";
            campoLabel=data.errorMessage.replace("RegexpCheckFailed: ","");
            campoLabel=messages[campoLabel];
            errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
        }
        bootbox.alert(errorMessage);

    }
    }).fail(function(){
    bootbox.hideAll();
    loadingScreen("Errore salvataggio!", "alerta");


    });
    }catch(err){
    bootbox.hideAll();
    loadingScreen("Errore salvataggio!", "alerta");
    console.log(err);
    }
	});
});
</@script>




