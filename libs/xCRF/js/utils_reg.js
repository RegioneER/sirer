/*******************************************
 * Questo script ha lo scopo di ottimizzare*
 * le procedure di che mostrano/nascondono *
 * le righe delle scelte regionali         *
 * ****************************************/

function display_reg_rows(){
    var nmax_reg = 30;
    if (!document.forms[0].elements['UPTDATA_REG_N'])
        return false;
    val=value_of('UPTDATA_REG_N', '0');
    for (var i=0; i<nmax_reg; i++){
        var j=i+1;
//        alert('val is '+val+' j is '+j);
        if (val < j){
            if (document.getElementById('tr_REG_NAME_'+j))
                document.getElementById('tr_REG_NAME_'+j).style.display='none';
            if (document.getElementById('tr_REG_USER_'+j))
                document.getElementById('tr_REG_USER_'+j).style.display='none';
            if (document.forms[0].elements['REG_NAME_'+j])
                document.forms[0].elements['REG_NAME_'+j].value='';
            if (document.forms[0].elements['REG_USER_'+j])
                document.forms[0].elements['REG_USER_'+j].selectedIndex=0;
        }
        else {        
            if (document.getElementById('tr_REG_NAME_'+j))
                document.getElementById('tr_REG_NAME_'+j).style.display='';
            if (document.getElementById('tr_REG_USER_'+j))
                document.getElementById('tr_REG_USER_'+j).style.display='';
        }
    }

}