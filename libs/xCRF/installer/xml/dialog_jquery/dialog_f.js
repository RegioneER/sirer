// @version $Id: dialog_f.js 212 2013-08-21 12:39:44Z atn $
function dialog_Iframe()
{ 
    
    $( "#dialog" ).dialog({
        modal: true, 
        title: 'ADVERSE EVENTS', 
        autoOpen: true,
        width: '80%',
        height: '800',
        close: true,
        closeOnEscape: false,
        resizable: true,
        buttons: {
            //            Ja: function () {
            //                $(obj).removeAttr('onclick');                                
            //                $(obj).parents('.Parent').remove();
            //              
            //              								
            //                $(this).dialog("close");
            //            },
            "Close": function () {
                var r = confirm("Do you want to close the page 'ADVERSE EVENTS'?");
                if (r==true)
                {
                    $(this).dialog("close");
                } 
            }
        },
        open: function(event, ui)
        {
            $(".ui-dialog-titlebar-close", $(this).parent()).hide();
        }
         
    });
     
}


function iFrame_ueaex()
{
    // FORM Liste
    //form_liste();  
    form_liste()
    //iFrame Function
    dialog_Iframe();
}
var IframeHelper = (function () {
    return {
        onLoaded: function (source) {
        //alert(source + ' loaded OK');
        },
        onErrored: function (source) {
            alert('For technical reasons, the page cannot be loaded. Please go directly to "ADVERSE EVENTS"');
            $("#dialog").dialog("close");
        }
    }
}());

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $(function() {
//      https: xolair.test.hypernetproject.com/uxmr/index.php?CENTER=004&CODPAT=1301&VISITNUM=1&ESAM=10&PROGR=1&form=prick.xml
//     var str = document.URL;
//     var n2 = str.replace("VISITNUM=1&ESAM=10&PROGR=1&form=prick.xml", "VISITNUM=80&ESAM=41&PROGR=1&form=ueaex.xml");
//      
//     $( "#dialog" ).dialog({
//         modal: true, 
//         title: 'Unerwünschte Ereignisse einschließlich Schwere Asthma-Exazerbationen', 
//         autoOpen: true,
//         width: '80%',
//         height: '950',
//          close: true,
//         closeOnEscape: false,
//         resizable: true,
//         buttons: {
//                          Ja: function () {
//                                $(obj).removeAttr('onclick');                                
//                                $(obj).parents('.Parent').remove();
//              
//              								
//                              $(this).dialog("close");
//                          },
//             "Schließen": function () {
//                 var r = confirm("wollen Sie 'Unerwünschte Ereignisse einschließlich Schwere Asthma-Exazerbationen' verlassen?");
//                 if (r==true)
//                 {
//                     $(this).dialog("close");
//                 } 
//             }
//         },
//         open: function(event, ui)
//         {
//             $(".ui-dialog-titlebar-close", $(this).parent()).hide();
//         }
//     });
//     $("#dialog").html("<a>"+n2+"</a><iframe id='dialog_iframe' src='"+n2+"' frameborder='0'></iframe>");   
// });
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
