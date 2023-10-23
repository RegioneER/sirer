/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
    @version $Revision: 2768 $
    @author  $Author: atn $
    @date    $Date: 2014-01-27 16:19:27 +0100 (Mo, 27 Jan 2014) $
 */

var el = document.forms[0].elements;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
var BrowserDetect = {
    init: function () {
        this.browser = this.searchString(this.dataBrowser) || "An unknown browser";
        this.version = this.searchVersion(navigator.userAgent)
        || this.searchVersion(navigator.appVersion)
        || "an unknown version";
        this.OS = this.searchString(this.dataOS) || "an unknown OS";
    },
    searchString: function (data) {
        for (var i=0;i<data.length;i++)	{
            var dataString = data[i].string;
            var dataProp = data[i].prop;
            this.versionSearchString = data[i].versionSearch || data[i].identity;
            if (dataString) {
                if (dataString.indexOf(data[i].subString) != -1)
                    return data[i].identity;
            }
            else if (dataProp)
                return data[i].identity;
        }
    },
    searchVersion: function (dataString) {
        var index = dataString.indexOf(this.versionSearchString);
        if (index == -1) return;
        return parseFloat(dataString.substring(index+this.versionSearchString.length+1));
    },
    dataBrowser: [
    {
        string: navigator.userAgent,
        subString: "Chrome",
        identity: "Chrome"
    },
    {
        string: navigator.userAgent,
        subString: "OmniWeb",
        versionSearch: "OmniWeb/",
        identity: "OmniWeb"
    },
    {
        string: navigator.vendor,
        subString: "Apple",
        identity: "Safari",
        versionSearch: "Version"
    },
    {
        prop: window.opera,
        identity: "Opera",
        versionSearch: "Version"
    },
    {
        string: navigator.vendor,
        subString: "iCab",
        identity: "iCab"
    },
    {
        string: navigator.vendor,
        subString: "KDE",
        identity: "Konqueror"
    },
    {
        string: navigator.userAgent,
        subString: "Firefox",
        identity: "Firefox"
    },
    {
        string: navigator.vendor,
        subString: "Camino",
        identity: "Camino"
    },
    {		// for newer Netscapes (6+)
        string: navigator.userAgent,
        subString: "Netscape",
        identity: "Netscape"
    },
    {
        string: navigator.userAgent,
        subString: "MSIE",
        identity: "Explorer",
        versionSearch: "MSIE"
    },
    {
        string: navigator.userAgent,
        subString: "Gecko",
        identity: "Mozilla",
        versionSearch: "rv"
    },
    { 		// for older Netscapes (4-)
        string: navigator.userAgent,
        subString: "Mozilla",
        identity: "Netscape",
        versionSearch: "Mozilla"
    }
    ],
    dataOS : [
    {
        string: navigator.platform,
        subString: "Win",
        identity: "Windows"
    },
    {
        string: navigator.platform,
        subString: "Mac",
        identity: "Mac"
    },
    {
        string: navigator.userAgent,
        subString: "iPhone",
        identity: "iPhone/iPod"
    },
    {
        string: navigator.platform,
        subString: "Linux",
        identity: "Linux"
    }
    ]

};
BrowserDetect.init();
//--------------------------------------------------------------------------------------------------------------
function clean_allChildren(a)
{
    var arr = a;
    jQuery.each(arr, function(){
        var b = $("input[name='"+this+"']").attr('type');
        if(b == "radio")
        {
            $("input[name='"+this+"']").attr('checked', false);
        }
        if(b == "text")
        {
            $("input[name='"+this+"']").val(null);
        }
        if(b == "checkbox")
        {
            $("input[name='"+this+"']").attr('checked', false);
        }
    });
}
function table_hide(a)
{
    //table_hide(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).parent('tr').hide();
        clean_allChildren(arr);
    });
}
// Just for Othvar without attr NAME! 
function table_hideV2(a)
{
    //table_hideV2(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#"+this).parent('td').hide();
        clean_allChildren(arr);
    });
}

function table_hide_special(a)
{
    //for Text/input
    //table_hide(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).css('color','#D6D6EB');
        $("#"+this).css("visibility","hidden");
        $('#cell_input_'+this).css('color','#D6D6EB');
        clean_allChildren(arr);
    });
}
function table_hide_RadioSpecial(a)
{
    // for Radio
    //table_hide(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).css('color','#D6D6EB');
        $("#"+this).css("visibility","hidden");
        clean_allChildren(arr);
        $("input[name='"+this+"']").css('visibility','hidden');
        $('#cell_input_'+this).css('color','#D6D6EB');
        $('#cell_input_'+this+ ' td').css("visibility","hidden");
    });
}
function table_hideToshow_special(a)
{
    //table_hide(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).css('color','#282853');
        $("#"+this).css("visibility","visible");
        $('#cell_input_'+this).css('color','#282853');
        $("#cell_"+this).parent('tr').show();
    });
} 
function table_hideToshow_RadioSpecial(a)
{
    //table_hide(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).css('color','#282853');
        $("#"+this).css("visibility","visible");
        $("input[name='"+this+"']").css('visibility','visible');
        $('#cell_input_'+this).css('color','#282853');
        $('#cell_input_'+this+ ' td').css("visibility","visible");
    });
}


function table_hideToshow(a)
{
    //table_hide(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).parent('tr').show();
    });
}
// Just for Othvar without attr NAME! 
function table_hideToshowV2(a)
{
    //table_hideV2(["XXX","XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#"+this).parent('td').show();
        clean_allChildren(arr);
    });
}

function all_table_hide(a)
{
    //all_table_hide(["XXX,XXX"]);
    
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).parent('tr').parent('tbody').hide();
        $('input[name="salva"]').css('visibility','hidden');
        $('input[name="invia"]').css('visibility','hidden');
        $('input[name="annulla"]').css('visibility','hidden');
    });
   
}
function all_table_hide2(a)
{
    //all_table_hide(["XXX,XXX"]);
    
    var arr = a;
    jQuery.each(arr, function(){
        $("#cell_"+this).parent('tr').parent('tbody').hide();      
    });
   
}

function manuell_textbox(a)
{
    // enable_textbox(["XXX,XXX"]);
    var arr = a;
    jQuery.each(arr, function(){
        $("#"+this).attr("value","");
        $("#"+this).attr("disabled",false);
    });
   
}
// HIDE text_hyper without NAME !

function radio_hide_rowV2(a,b,c)
{
    //radio_hide_rowV2(['PRF1C'],[0],['OTHVAR2','OTHVAR3']);
    var el=document.forms[0].elements;
    var rads=document.forms[0].elements[a]
    var arr = c;
    var updateRadio = function ()
    {
        jQuery.each(arr, function(){
            var z = $("#cell_"+this).is("td");
            var i;
            for(i=0;i<b.length;i++)
            {
                if(radioCheckMulti(a,b) ==  true)
                //if( el[(a)][b[i]].checked == true)
                {
                    if(z == true)
                    {
                        table_hideToshow([this]);
                    }
                    if(z == false)
                    {
                        table_hideToshowV2([this]);
                    }
                }
                //if(!anyChecked(rads))
                else
                {
                    if(z == true)
                    {
                        table_hide([this]);
                    }
                    if(z == false)
                    {
                        table_hideV2([this]);
                    }
                }
            }
               
            
        });
    };
    
    
    window.setInterval(updateRadio, 50);
}





// hide table in table with Radio button
function radio_hide_multiCol(a,b,c)
{
    //radio_hide_special(['VAELC'],0,['LETSCN']);
    var updateRadio = function ()
    {
        if( el[(a)][b].checked )
        {
            table_hideToshow_special(c);
        }
        else
        {
            table_hide_special(c);
        }
    };
    
    window.setInterval(updateRadio, 50);
}
// function Control if something change or not
function select_hide_Col(a,b,c)
{
    var updateSelect = function ()
    {
        if( el[(a)].selectedIndex == b)
        {
            table_hideToshow(c);
        }
        else
        {
            table_hide(c);
        }
    };
    
    window.setInterval(updateSelect, 50);
}
// function Control if something change or not
/*
function controlChange(f)
{
    var i = function(){
        f();
    };
    window.setInterval(i, 50);
}
 */
/*
function controlChange(f)
{
    $(document).on("change",'.sf',function()
    {
        controlChange2(f);
    });

}
 */

function controlChangeV2(f)
{
    
    if(BrowserDetect.browser == "Explorer")
    {
        // for Internet Explorer
        var i = function(){
            f();
        };
        window.setInterval(i, 50);
    }
    var i = function(){
        f();
    };
    window.setInterval(i, 100);
/*
    else
    {
        $('body').change(function()
        {
            f();
        });
    }
     */
    
}

// Version 2 || 16.12.2013 ATN
// es muss immer am ende der "funtion onload" sein!!!
function controlChange(f)
{
    $("html").change(function(){
        f();
    }).change();
    $("html").keyup(function(){
        f();
    }).keyup();
    $("html").keydown(function(){
        f();
    }).keydown();
    $("html").mouseup(function(){
        f();
    }).mouseup();
    $("html").mousedown(function(){
        f();
    }).mousedown();
}
// Radio number checked, aufzählung von 0 !
function  selectRadioNum(num)
{
    // selectRadioNum("XXX",7);
    var a = $('input[name="'+num+'"]').length;
    for(var i=0; i<=a;i++)
    {
        if(el[(num)][i].checked == true)
        {
            num = i;
            return num;
        }
    }
}
// Text Value from to || Diff
function  selectValueNumFromTo(num,b,c)
{
    //selectValueNumFromTo("TRAR1A",[0,1,10,30,50,70,90],[0,9,29,49,69,89,100]);
    var arr1 = b;
    var arr2 = c;
    var arr3 = new Array();
    var arr4 = new Array();
    jQuery.each(arr1, function(){
        arr3.push(this);
    });
    jQuery.each(arr2, function(){
        arr4.push(this);
    });
    for(var i=0; i<arr4.length;i++)
    {
        if( toInt(el[(num)].value) >= arr3[i] &&  toInt(el[(num)].value) <= arr4[i])
        {
            num = i;
            return num;
        }
    }
}
// one of Radio/Box is checked
function oneOfAllChecked(a)
{
    // sample || if( !oneOfAllChecked(['HGB','HCT','WBC','NTR','LYM','MON','EOS','BAS','RBC','PLAT']) ) {Alert/Confirm};
    var arr = jQuery.makeArray(a);
    
    for( var i = 0; i < arr.length; i++ )
    {
        var b = $('input[name="'+arr[i]+'"]').attr('type');
        if(b == 'radio')
        {
            if( anyChecked(el[(arr[i])]) )
            {
                return true;
                break;
            }
        }
        else
        {
            if( el[(arr[i])].checked )
            {
                return true;
                break;
            }
        }
    }
    return false;
}
// is All Checked Radio/Box
function allChecked(a)
{
    // sample || if( !oneOfAllChecked(['HGB','HCT','WBC','NTR','LYM','MON','EOS','BAS','RBC','PLAT']) ) {Alert/Confirm};
    var arr = jQuery.makeArray(a);
    var ai = 0;

    for( var i = 0; i < arr.length; i++ )
    {
        if( anyChecked(el[(arr[i])]) )
        {
            ai = ai+1;
        }
    }
    if(ai == arr.length)
    {
        return true;
    }
    else{
        return false;
    }
}

// if Radio Checked 1 or 2 or 3
function radioCheckMulti(a,b)
{
    // radioCheckMulti('OCT4BC',[0,2]);
    var i;
    for(i=0;i < b.length; i++)
    {
        if(el[(a)][b[i]].checked)
        {
            return true;
            break;
        }
    }
}
// if Select option select true
function anySelect(a)
{
    // anySelect(['XY']);
    var sel=document.forms[0].elements[a];
    if(!!sel.value)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Date show Hide
function elDate_hide_row(a,b)
{
    //elDate_hide_row(['XXX'],['XXX','XXX']);

    var updateDate = function ()
    {
        if( !elDate(a).equals(MissingDate()) )
        {
            table_hideToshow(b);
        }
        else
        {
            table_hide(b);
        }
    }
    window.setInterval(updateDate, 500);
}

//--------------------------------------------------------------------------------------------------------------
//Date
//--------------------------------------------------------------------------------------------------------------
//
//Calender erlaubt NK und NA
function MissingDateNkNa(a)
{
    // sample || if(elDate('MHDAT').equals(MissingDate()),MissingDateNkNa('MHDAT'))
    var str = a.replace(' ','');
    str = str.toUpperCase();
    if( el[str+'D',str+'M',str+'Y'].value != 'NA' && el[str+'D',str+'M',str+'Y'].value != 'NK' ){
        return true;
    }
    if(!el[str+'D',str+'M',str+'Y'].value){
        return true;
    }
    else {
        return false;
    }
}
// is Date there?
function isDateThere(a)
{
    if( !!el[(a+'D')].value || !!el[(a+'M')].value || !!el[(a+'Y')].value )
    {
        return true;
    }else{
        return false;
    }
}
var date = new Date();
// Datum Difference
function GetHDdateBetween(startDate, endDate)
{
    var xy = startDate.search('/');
    var yx = endDate.search('/');
    var x,y,a,a1,b,b1,dateStart,dateEnd,date,tag1,mon1,jahr1,tag2,mon2,jahr2;
    if( xy != -1 )
    {
        x = startDate.split("/");
        a = x[2];
        a1 = a[0]+a[1]+a[2]+a[3];
        dateStart = new Date(a1,(x[1]-1),x[0]);
    }
    if(yx != -1)
    {
        y = endDate.split("/");
        b = y[2];
        b1 = b[0]+b[1]+b[2]+b[3];
        dateEnd = new Date(b1,(y[1]-1),y[0]);
    }
    if( xy == -1)
    {
        x = startDate;
        tag1 = x[0]+x[1];
        mon1 = x[2]+x[3];
        jahr1 = x[4]+x[5]+x[6]+x[7];
        dateStart = new Date(jahr1,mon1,tag1);
    }
    if( yx == -1)
    {
        y = endDate;
        tag2 = y[0]+y[1];
        mon2 = y[2]+y[3];
        jahr2 = y[4]+y[5]+y[6]+y[7];
        dateEnd = new Date(jahr2,mon2,tag2);
    }
    date = dateEnd.getDate() - dateStart.getDate();
    if( date < 0)
    {
        date = date - 2 * date;
        return date;
    }
    else
    {
        return date;
    }           
}
function parseHDdate(str) 
{
    return new Date(str.substring(4,8), str.substring(2,4), str.substring(0,2));
}
function parseHDdate2(str) 
{
    if(str.search("/") != -1)
    {
        return new Date(str.substring(6,9), str.substring(3,5), str.substring(0,2));
    }
    else
    {
        return new Date(str.substring(4,8), str.substring(2,4), str.substring(0,2));
    }
}
function addDate(a,b,c)
{
    return new Date(c, b-1, a);
}

function GetHDdateBetweenV2(a, b) {
    var a2 = a;
    var b2 = b;
    var a1,b1;
    if(a2.search('/') == -1)
    {
        a1 = new Date(a.substring(4,8), a.substring(2,4)-1, a.substring(0,2));
    }
    if(a2.search('/') != -1)
    {
        a1 = new Date(a.substring(6,10), a.substring(3,5)-1, a.substring(0,2));
    }
    if(b2.search('/') == -1)
    {
        b1 = new Date(b.substring(4,8), b.substring(2,4)-1, b.substring(0,2));
    }
    if(b2.search('/') != -1)
    {
        b1 = new Date(b.substring(6,10), b.substring(3,5)-1, b.substring(0,2));
    }
    return ( b1-a1)/(1000*60*60*24);
}
// Check Time
function isTimeThere(a)
{
    // isTimeThere('XY')
    var str = a.replace(' ','');
    str = str.toUpperCase();
    if( !el[str+'_H'].value || !el[str+'_M'].value){
        return false;
    }
    else{
        return true;
    }
}
//--------------------------------------------------------------------------------------------------------------
// All about Numbers
//--------------------------------------------------------------------------------------------------------------
//Sort numbers
function sortMaxInt(a)
{
    var str2 = new Array();
    for(var i=0; i <= a.length; i++)
    {
        if(!isNaN(a[i]))
        {
            str2.push(a[i]);
        }
    }
    str2 = str2.sort(function(a,b){
        return a-b
    });
    
    return str2[str2.length-1];
}
function sortMinInt(a)
{
    var str2 = new Array();
    for(var i=0; i <= a.length; i++)
    {
        if( !isNaN(a[i]) )
        {
            str2.push(a[i]);
        }
    }
    str2 = str2.sort(function(a,b){
        return b-a
    });
    
    return str2[str2.length-1];
}
function sortMinMaxInt(a)
{
    var str2 = new Array();
    for(var i=0; i <= a.length; i++)
    {
        if(!isNaN(a[i]))
        {
            str2.push(a[i]);
        }
    }
    str2 = str2.sort(function(a,b){
        return a-b
    });
    return str2;
}
function sortMaxMinInt(a)
{
    var str2 = new Array();
    for(var i=0; i <= a.length; i++)
    {
        if(!isNaN(a[i]))
        {
            str2.push(a[i]);
        }
    }
    str2 = str2.sort(function(a,b){
        return b-a
    });
    return str2;
}
function lastInt(a)
{
    var str2 = new Array();
    for(var i=0; i <= a.length; i++)
    {
        if(!!a[i])
        {
            if(!isNaN(a[i]))
            {
                str2.push(a[i]);
            }
        }
    }
    return str2[str2.length-1];
}
//--------------------------------------------------------------------------------------------------------------
// Erkennt Value Change
//--------------------------------------------------------------------------------------------------------------
$.event.special.inputchange = {
    setup: function() {
        var self = this, val;
        $.data(this, 'timer', window.setInterval(function() {
            val = self.value;
            if ( $.data( self, 'cache') != val ) {
                $.data( self, 'cache', val );
                $( self ).trigger( 'inputchange' );
            }
        }, 20));
    },
    teardown: function() {
        window.clearInterval( $.data(this, 'timer') );
    },
    add: function() {
        $.data(this, 'cache', this.value);
    }
};

//$('#XY').on('inputchange', function() { alert('test'); });

// Radio is changed to Value
function radioChangeValue(a,f)
{
    var arr = a;
    jQuery.each(arr, function(){
        $('#cell_input_'+this).change(function()
        {
            f(); 
        });
    });
};

// fehlender variable testen
function testThis(a)
{
    var arr = a;
    var i = 0;
    var txt_val, select_val;
    jQuery.each(arr, function(){
        clean_allChildren(arr);
        var b = $("#cell_"+this).is("td");
        //-----------------------------------------------------------------------
        // variable true/false
        if(b == false)
        {
            alert("false entry: " + this)
            i = i + 1;
        }
        // end variable
        //-----------------------------------------------------------------------
        // value true/false for radio
        if(b == true)
        {
            var lang = $("#cell_input_"+this+" tr").children().length;
            for(var z=0;z<=lang;z++)
            {
                var z2 = $("#cell_input_"+this+" tr td:nth-child("+z+") input").val();
                if( parseInt(z2) >= 0 )
                {
                    txt_val += "\n" + $("#cell_input_"+this+" tr td:nth-child("+z+") input").attr("type") + " || " + this + " : " + z2;
                }
            }
            txt_val += "\n"
        }
        // end radio
        //-----------------------------------------------------------------------
        // select true/false
        if(b == true)
        {
            //POSFO1C
            var lang = $("#cell_input_"+this+" select").children().length;
            for(var z=0;z<=lang;z++)
            {
                var z2 = $("#cell_input_"+this+" select option:nth-child("+z+") ").val();
                if( parseInt(z2) >= 0 )
                {
                    select_val += "\n select option || " + this + " : " + z2;
                }

            }
            select_val += "\n";
        }

    });
     
    if(i == 0)
    {
        alert("everything OK");
    }
    return txt_val +"\n"+ select_val;
}

function showAllName()
{
    var a  = $('.sf tr input').length;
    var a2  = $('.sf tr').length;
    var b;

    for(var z = 1; z<a2;z++)
    {
        for(var i = 1; i<a; i++)
        {
            var h = $('.sf tr:nth-child('+z+') input:nth-child('+i+')').attr('name');
            if(h != null)
            {
                b += '\n' + $('.sf tr:nth-child('+z+') input:nth-child('+i+')').attr('type') + ' || ' + $('.sf tr:nth-child('+z+') input:nth-child('+i+')').attr('name') + '\n';
            }
        }
    }
    alert(b);
    return b;
}
   
//--------------------------------------------------------------------------------------------------------------
