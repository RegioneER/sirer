<#assign type=model['docDefinition']/>
<#global page={
        "content": path.pages+"/"+mainContent,
        "styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
        "scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
        "inline_scripts":[],
        "title" : "Dettaglio",
        "description" : "Dettaglio"
        } />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>
    $("[name=salvaForm-RiduzioneFattura]").prop("name","salvaForm-RiduzioneFatturaCustom").unbind('click');
    $("#salvaForm-RiduzioneFattura").prop("id","salvaForm-RiduzioneFatturaCustom");

    $("[name=salvaForm-RiduzioneFatturaCustom]").unbind('click').on('click',function(){
        var $form=$($(this).data('rel'));
        if($(this).attr('id')){
            var formName=$(this).attr('id').replace("salvaForm-", "");
        }
        else{
            formName="formNonEsistente";
        }
        if ($('#RiduzioneFattura_QuantitaRiduzione').val()==""){
            console.log("controllo campo obbligatorio RiduzioneFattura_QuantitaRiduzione di tipo TEXTBOX");
            bootbox.alert("Il campo Importo da detrarre deve essere compilato",function(){
                setTimeout(function(){$input.focus();},0);
            });
            $('#RiduzioneFattura_QuantitaRiduzione').focus();
            return false;
        }
        else{
            if(isNaN($('#RiduzioneFattura_QuantitaRiduzione').val())){
                console.log("controllo campo obbligatorio Farmaco_tipo di tipo TEXTBOX sia numerico");
                bootbox.alert("Il campo Importo da detrarre deve essere numerico",function(){
                    setTimeout(function(){$input.focus();},0);
                });
                $('#RiduzioneFattura_QuantitaRiduzione').focus();
                return false;
            }
        }

        if ($('#RiduzioneFattura_TipoRiduzione').val()==""){
            console.log("controllo campo obbligatorio RiduzioneFattura_TipoRiduzione di tipo SELECT");
            bootbox.alert("Il campo Riduzione deve essere compilato",function(){
                setTimeout(function(){$input.focus();},0);
            });
            $('#RiduzioneFattura_TipoRiduzione').focus();
            return false;
        }
        if ($('#RiduzioneFattura_QuandoRecuperare').val()==""){
            console.log("controllo campo obbligatorio RiduzioneFattura_QuandoRecuperare di tipo SELECT");
            bootbox.alert("Il campo Da recuperare deve essere compilato",function(){
                setTimeout(function(){$input.focus();},0);
            });
            $('#RiduzioneFattura_QuandoRecuperare').focus();
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


        window.location.href='${baseUrl}/app/documents/detail/${el['parent'].getId()}';

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
$.fn.editable.defaults.mode = 'inline';
$('.field-inline-anchor').editable({
params: function(params) {
var metadata={};
metadata[params.name]=params.value

return metadata;
},
emptytext :"Valore mancante"
});
var loadedElement=${loadedJson};
var dummy=${json};
var empties=new Array();

empties[dummy.type.id]=dummy;


$('select').select2({containerCssClass:'select2-ace',allowClear: true});
</@script>
