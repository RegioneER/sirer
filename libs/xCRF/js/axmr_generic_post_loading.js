var f_salva_f = window.salva_f;
var f_invia_f = window.invia_f;
var confirm_orig = window.confirm;
var alert_orig = window.alert;

var origcf = cf;
cf = function() {
    var retval=origcf();
    $('form#esamForm div.hideBlock').show();
    $('form#esamForm div.hideBlock > div:hidden').parent().hide();
    return retval;
}


window.salva_f = function (ajax, showLoading, show_bootbox, realtime_equeries) { //GENHD-44 vmazzeo 23.02.2015
    if (showLoading == undefined) ShowMessage('<i class="icon-spinner icon-spin orange bigger-125"></i> Saving...');
    if ($('.bootbox-body').css('display') == undefined) {
        setTimeout("salva_f(" + ajax + ", true," + show_bootbox + "," + realtime_equeries + ");", 300);
        return;
    }
    f_salva_f(ajax, showLoading, show_bootbox, realtime_equeries);
}

window.invia_f = function (ajax, showLoading, show_bootbox, realtime_equeries) { //GENHD-44 vmazzeo 23.02.2015
    if (showLoading == undefined) ShowMessage('<i class="icon-spinner icon-spin orange bigger-125"></i> Sending...');
    if ($('.bootbox-body').css('display') == undefined) {
        setTimeout("invia_f(" + ajax + ", true," + show_bootbox + "," + realtime_equeries + ");", 300);
        return;
    }
    f_invia_f(ajax, showLoading, show_bootbox, realtime_equeries);
}



        	if(navigator.userAgent.toLowerCase().indexOf('firefox') > -1)
        	{
    window.alert = function () {
        console.log(arguments);
        //bootbox.alert(arguments[0], function(){bootbox.hideAll();});
        alert_orig(arguments[0]);
        bootbox.hideAll();
        cf();
    };

    window.confirm = function () {
        if (!confirm_orig(arguments[0])) {
            bootbox.hideAll();
            cf();
            return false;
        }
        else return true;
    };
} else {
    window.alert = function () {
        console.log(arguments);
        alert_orig(arguments[0]);
        bootbox.hideAll();
        cf();
    };

    window.confirm = function () {
        if (!confirm_orig(arguments[0])) {
            bootbox.hideAll();
            cf();
            return false;
        }
        else return true;
    };
}
        	
        	
        	