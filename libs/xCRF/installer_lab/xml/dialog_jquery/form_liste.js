function form_liste( )
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
    var el = document.forms[0].elements;
    var str = document.URL;
    var n;
    var a;
    //var url_ad = "https://xolair.test.hypernetproject.com/uxmr/index.php?CENTER="+el.CENTER.value+"&CODPAT="+el.CODPAT.value;
    var prot = window.location.protocol; // http:
    var hostn = window.location.hostname; // hostname
    var url_ad = prot+"//"+hostn+"/uxmr/index.php?CENTER="+el.CENTER.value+"&CODPAT="+el.CODPAT.value;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //1
    var arrA = new Array(2,3,4,5,6,7,8,16,17,18,19,20,21);
    var i;
    for(i = 0; i <= arrA.length; i++ )
    {
        if(el.ESAM.value == '31' && toInt(el.VISITNUM.value) == arrA[i])
        {
            //CENTER=001&CODPAT=641&VISITNUM=8&ESAM=31&PROGR=1&VISITNUM_PROGR=0&form=obs.xml
            //CENTER=001&CODPAT=641&VISITNUM=15&ESAM=58&PROGR=1&form=ae.xml
            a =  url_ad+"&VISITNUM="+arrA[i]+"&ESAM=31&PROGR=1&VISITNUM_PROGR=0&form=obs.xml";
            $(document).ready(function() 
            {
                if(str == a)
                {
                    n = str.replace("VISITNUM="+arrA[i]+"&ESAM=31&PROGR=1&VISITNUM_PROGR=0&form=obs.xml", "VISITNUM=15&ESAM=58&PROGR=1&VISITNUM_PROGR=0&form=ae.xml");
                }
                else
                {
                    n = str.replace("VISITNUM="+arrA[i]+"&ESAM=31&PROGR=1&form=obs.xml", "VISITNUM=15&ESAM=58&PROGR=1&form=ae.xml");
                }
                console.log(a);
                console.log(n);
                $("#dialog").html("<a>"+a+"</a><br/><a>"+n+"</a><a id='Loaden'></a><br/><iframe id='dialog_iframe' onload='IframeHelper.onLoaded(this.src);' onerror='IframeHelper.onErrored(this.src);' src='"+n+"' frameborder='0'></iframe>");
            });
        }
    }
   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
}
// original
/*
    
    */
   /*
    jQuery.each(d1, function()
     {
        if(el.ESAM.value == c1 && toInt(el.VISITNUM.value) == this)
        {
            //CENTER=001&CODPAT=641&VISITNUM=8&ESAM=31&PROGR=1&VISITNUM_PROGR=0&form=obs.xml
            //CENTER=001&CODPAT=641&VISITNUM=15&ESAM=58&PROGR=1&form=ae.xml
            a =  url_ad+"&VISITNUM="+this+"&ESAM="+c1+"&PROGR=1&VISITNUM_PROGR=0&form="+a1+".xml";
            $(document).ready(function() 
            {
                if(str == a)
                {
                    n = str.replace("VISITNUM="+this+"&ESAM="+c1+"&PROGR=1&VISITNUM_PROGR=0&form="+a1+".xml", "VISITNUM=15&ESAM=58&PROGR=1&VISITNUM_PROGR=0&form="+b1+".xml");
                }
                else
                {
                    n = str.replace("VISITNUM="+this+"&ESAM="+c1+"&PROGR=1&form="+a1+".xml", "VISITNUM=15&ESAM=58&PROGR=1&form="+b1+".xml");
                }
                console.log(a);
                console.log(n);
                $("#dialog").html("<a>"+a+"</a><br/><a>"+n+"</a><a id='Loaden'></a><br/><iframe id='dialog_iframe' onload='IframeHelper.onLoaded(this.src);' onerror='IframeHelper.onErrored(this.src);' src='"+n+"' frameborder='0'></iframe>");
            });
        }
    });
   
    */