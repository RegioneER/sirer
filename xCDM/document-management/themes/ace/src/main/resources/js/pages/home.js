function TSToDate(date){
	if(!date)return "Valore mancante";
	var fmt = new DateFmt("%d/%m/%y %H.%M");
	return fmt.format(new Date(date));
}

function DateFmt(fstr) {
    this.formatString = fstr

    var mthNames = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
    var dayNames = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
    var zeroPad = function(number) {
        return ("0"+number).substr(-2,2);
    }

    var twoDigit= function(string){
        return (string+'').substr(2,2);
    }

    var dateMarkers = {
        d:['getDate',function(v) { return zeroPad(v)}],
        m:['getMonth',function(v) { return zeroPad(v+1)}],
        n:['getMonth',function(v) { return mthNames[v]; }],
        w:['getDay',function(v) { return dayNames[v]; }],
        y:['getFullYear',function(v) { return twoDigit(v)}],
        H:['getHours',function(v) { return zeroPad(v)}],
        M:['getMinutes',function(v) { return zeroPad(v)}],
        S:['getSeconds',function(v) { return zeroPad(v)}],
        i:['toISOString']
    };

    this.format = function(date) {
        var dateTxt = this.formatString.replace(/%(.)/g, function(m, p) {
            var rv = date[(dateMarkers[p])[0]]()

            if ( dateMarkers[p][1] != null ) rv = dateMarkers[p][1](rv)

            return rv

        });

        return dateTxt
    }

}

function descrStudio(studio){
	return studio.IDstudio_CodiceProt+' ('+studio.UniqueIdStudio_id+')';
}

function descrCentro(centro){
	return centro.IdCentro_PI[0].split("###")[1]+' ('+centro.IdCentro_Struttura[0].split("###")[1]+')';
}

function descrBudget(budget){
	return budget.Base_Nome[0]+' v. '+budget.Budget_Versione[0];
}

function toLength(string){
	var length= 100;
	if(!string) return string;
	if(string.length<=length) return string;
	else return string.substring(0, length-3) + "...";
}

function updateRowHeights(){
	var tr_height=0;
	$('tr.jqgrow td').css({height:'auto'});
	$('tr.jqgrow').each(function(){
		tr_height=Math.max(tr_height,$(this).height());
	});
	$('tr.jqgrow td').css({height:tr_height+'px'});
	
	tr_height=0;
	$('.ui-jqgrid .ui-jqgrid-htable th div').css({height:'auto'});
	$('.ui-jqgrid .ui-jqgrid-htable th div').each(function(){
		tr_height=Math.max(tr_height,$(this).height());
	});
	tr_height+=20;
	$('.ui-jqgrid .ui-jqgrid-htable th div').css({height:tr_height+'px'});
}



function enableTooltips(table) {
	$('.navtable .ui-pg-button').tooltip({container:'body'});
	$(table).find('.ui-pg-div').tooltip({container:'body'});
}




