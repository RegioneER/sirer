function onload()
{
    var el=document.forms[0].elements;
    //el.OTHVAR4.disabled=true;
}

function validate(bug)
{
    var el=document.forms[0].elements;
    if(bug==1 && cfg.debug==0)return true;
    var x,y;
    
    /* 28.01.2014 : 16 dpv*/
    if (el.HGT1N.value==''){
        alert('The "Body height" has to be given.');
        return false;
    }
    /* 28.01.2014 : 17 dpv*/
    x=toInt(el.HGT1N.value);
    if(!isNaN(x))if(x<140||210<x){
        if(!confirm('The Body height is not within the range 140-210 cm. Please press "Cancel" to check the data again or "OK" to confirm your entries.'))return false;
    }
    /* 28.01.2014 : 18 dpv*/
    if (el.SBP1N.value==''){
        alert('The answer for "Systolic blood pressure" has to be given. Please check the data. ');
        return false;
    }
    /* 28.01.2014 : 19 dpv*/
    x=toInt(el.SBP1N.value);
    if(!isNaN(x))if(x<90||150<x){
        if(!confirm('The Systolic blood pressure is out of the reference region (90-150 mmHg). Please press "Cancel" to check the data again or "OK" to confirm your entries.'))return false;
    }
    /* 28.01.2014 : 20 dpv*/
    if (el.DBP1N.value==''){
        alert('The answer for "Diastolic blood pressure" has to be given. Please check the data. ');
        return false;
    }
    /* 28.01.2014 : 21 dpv*/
    x=toInt(el.DBP1N.value);
    if(!isNaN(x))if(x<60||90<x){
        if(!confirm('The Diastolic blood pressure is out of the reference region (60-90 mmHg). Please press "Cancel" to check the data again or "OK" to confirm your entries.'))return false;
    }
    /* 28.01.2014 : 22 dpv*/
    x=toInt(el.SBP1N.value);
    y=toInt(el.DBP1N.value);
    if(!isNaN(x))if(!isNaN(y))if(x <= y){
        alert('The systolic blood pressure is not higher than the diastolic blood pressure. Please check the data.');
        return false;
    }
    /* 28.01.2014 : 23 dpv*/
    if (el.PLS1N.value==''){
        alert('The answer for "Pulse rate" has to be given. Please check the data. ');
        return false;
    }
    /* 28.01.2014 : 24 dpv*/
    x=toInt(el.PLS1N.value);
    if(!isNaN(x))if(x<60||100<x){
        if(!confirm('The Pulse rate is out of the reference region (60-100 beats/min). Please press "Cancel" to check the data again or "OK" to confirm your entries.'))return false;
    }
    
    // POPUP
    //06.02.2014 || ATN - iFrame
    
    if(!el.OTHVAR4.checked)
    {
        //iFrame_ueaex();
        iFrame_ueaex()
        $("#dialog").dialog("open");
        el.OTHVAR4.checked = true;
        return false;
    }

    return true;
}