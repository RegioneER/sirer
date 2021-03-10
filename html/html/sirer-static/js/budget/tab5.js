$("#add-CTC").button().click(function() {
    bootbox.prompt({
        title: "Inserisci Overhead Aziendale (&euro;)",
        value: markup_tmp,
        callback: function (overhead) {
            //alert("overhead: "+overhead);
            if (overhead != null) {
                if (overhead != "" && !isNaN(overhead)) {
                    var postUrl = baseUrl + "/app/rest/documents/update/" + loadedBudgetStudio.id;
                    var postData = new Object();
                    postData['BudgetCTC_Markup'] = overhead;
                    $.post(postUrl, postData).done(function (data) {
                        if (data.result != 'OK') {
                            bootbox.alert('Attenzione!!! Errore nel salvataggio');
                        }
                        else {
                            if (overhead != null) {
                                $("#markup-ins").html("€ " + parseFloat(overhead).toFixed(2));
                            }
                            bootbox.hideAll();
                        }
                    });
                    markup_tmp=overhead;
                }
                else {
                    bootbox.alert("Inserire un valore numerico per Overhead Aziendale (€)");
                }
            }
        }
    });
});
$("input[name=BudgetCTC_FINEntita]").prop("readonly","readonly");
$("input[name^=BudgetCTC_FIN]").bind("change",function(){
    if($(this).prop("id")!="BudgetCTC_FINEntita" &&
        $(this).prop("id")!="BudgetCTC_FINnoProfitFinanzInterno" &&
        $(this).prop("id")!="BudgetCTC_FINNoteFinanziamento"
    ) {
        sommaFinanziamenti();
    }
});
var sommaEntita=0;
function sommaFinanziamenti(){
    sommaEntita=0
    $("input[name^=BudgetCTC_FIN]").each(function(){
        if($(this).prop("id")!="BudgetCTC_FINEntita" &&
            $(this).prop("id")!="BudgetCTC_FINnoProfitFinanzInterno" &&
            $(this).prop("id")!="BudgetCTC_FINNoteFinanziamento"
        ) {
            if($(this).val()!="") {
                if (!isNaN($(this).val()) ) {
                    sommaEntita += parseFloat($(this).val());
                }
                else {
                    sommaEntita = 0;
                    bootbox.alert("Inserire un valore numerico positivo");
                    $(this).focus();
                    return;
                }
            }
        }
    });
    $("input[name=BudgetCTC_FINEntita]").val(sommaEntita);
}

$("#add-n-pat").button().click(function() {
    bootbox.prompt({
        title: "Inserisci numero di pazienti previsto",
        value: numero_pazienti_tmp,
        callback: function (numero_pazienti) {
            //alert("numero_pazienti: "+numero_pazienti);
            if (numero_pazienti != null) {
                if (numero_pazienti != "" && !isNaN(numero_pazienti)) {
                    var postUrl = baseUrl + "/app/rest/documents/update/" + loadedBudgetStudio.id;
                    var postData = new Object();
                    postData['BudgetCTC_NumeroPazienti'] = numero_pazienti;
                    $.post(postUrl, postData).done(function (data) {
                        if (data.result != 'OK') {
                            bootbox.alert('Attenzione!!! Errore nel salvataggio');
                        }
                        else {
                            if (numero_pazienti != null) {
                                $("#show-n-pat").html(numero_pazienti);
                            }
                            bootbox.hideAll();
                        }
                    });
                    numero_pazienti_tmp=numero_pazienti;
                }
                else {
                    bootbox.alert("Inserire un valore numerico per Numero di pazienti previsto");
                }
            }
        }
    });
});

$("#create-target").button().click(function() {
    var myForm=$("#dialog-form-proto").clone();
    myForm.find("form").attr("id","dialog-form-target");
    bootbox.confirm({
        title: 'Inserisci corrispettivo contrattuale',
        message: myForm.html(),
        callback: function(result){
            if(result){
                var myTipoTarget=$("#dialog-form-target select[name=BudgetCTC_TipoTarget]").val();
                var myTarget=$("#dialog-form-target input[name=targetPrezzo]").val();
                if(myTarget!=null ) {
                    if (myTarget != "" && !isNaN(myTarget)) {
                        var postUrl = baseUrl + "/app/rest/documents/update/" + loadedBudgetStudio.id;
                        var postData = new Object();
                        postData['BudgetCTC_TipoTarget'] = myTipoTarget;
                        if (myTipoTarget == "2") {
                            postData['BudgetCTC_TargetPaziente'] = myTarget;
                            postData['BudgetCTC_TargetStudio'] = "";
                        }
                        else {
                            postData['BudgetCTC_TargetPaziente'] = "";
                            postData['BudgetCTC_TargetStudio'] = myTarget;
                        }
                        $.post(postUrl, postData).done(function (data) {
                            if (data.result != 'OK') {
                                bootbox.alert('Attenzione!!! Errore nel salvataggio');
                            }
                            else {
                                if (myTipoTarget != null && myTarget != null) {
                                    myProposta = "";
                                    if (myTipoTarget == 2) {
                                        myProposta ="&euro; " + parseFloat(myTarget).toFixed(2) ;
                                    }
                                    else {
                                        myProposta ="&euro; " + parseFloat(myTarget).toFixed(2) + "  per intero studio";
                                    }
                                    proposta_promotore=parseFloat(myTarget).toFixed(2);
                                    $("#proposta_promotore").html(myProposta);
                                    totPerPaz=(parseFloat(proposta_promotore)+parseFloat(totPricePaz)).toFixed(2);
                                    $("#show-TotPerPaz").html("&euro; " +totPerPaz);
                                    totPerStudio=parseFloat(totPerPaz*numero_pazienti_tmp).toFixed(2);
                                    $("#show-TotPerStudio").html("&euro; "+totPerStudio);
                                }

                                bootbox.hideAll();
                            }
                        });
                        $("#dialog-form-proto input[name=targetPrezzo]").attr("value",myTarget);
                    }
                    else {
                        bootbox.alert("Inserire un valore numerico per Importo");
                    }
                }
            }
        }
    });
});

$('[name=salvaForm-BudgetCTC]').unbind('click').on('click', function () {
    var $form = $($(this).data('rel'));
    if ($(this).attr('id')) {
        var formName = $(this).attr('id').replace('salvaForm-', '');
    }
    else {
        formName = 'formNonEsistente'
    }
    var goon = true;
    if (eval('typeof ' + formName + 'Checks == \'function\'')) {
        eval('goon=' + formName + 'Checks()');
    }
    if (!goon) return false;
    loadingScreen('Salvataggio in corso...', 'loading');
    try {
        var myElement = {
        };
        myElement.id = loadedBudgetStudio.id;
        myElement.type = loadedBudgetStudio.type;
        myElement.metadata = {
        };
        myElement = formToElement($form, myElement, 'BudgetCTC');
        saveElement(myElement).done(function (data) {
            bootbox.hideAll();
            if (data.result == 'OK') {
                loadingScreen('Salvataggio effettuato', 'green_check');
                //Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
                window.setTimeout(function () {
                    bootbox.hideAll();
                }, 3000);
                if (data.redirect) {
                    window.location.href = data.redirect;
                }
            } else {
                loadingScreen('Errore salvataggio!', 'alerta');
            }
        }).fail(function () {
            bootbox.hideAll();
            loadingScreen('Errore salvataggio!', 'alerta');
        });
    } catch (err) {
        bootbox.hideAll();
        loadingScreen('Errore salvataggio!', 'alerta');
        console.log(err);
    }
});
