<#setting locale="it_IT">

<#setting number_format="computer">
<#assign theme="" />
<#if model['requestCookies']?? && model['requestCookies'].theme??>
<#assign theme=model['requestCookies'].theme.getValue() />
</#if>
<#if theme="ace" || theme=="" >

<#global tmpIncludes >
<#include "lib/stdIncludes.ftl">

</#global>


	<#include "themes/ace/structure.ftl" >
<#else>
<!DOCTYPE html>
<html>
<head>
    <title>CINECA - CRMS</title>
    <script>
	   
    </script>
    <link href="${baseUrl}/int/css/redmond/jquery-ui-1.10.3.custom.css" rel="stylesheet">
    <script src="${baseUrl}/int/js/jquery-1.9.1.js"></script>
    <script src="${baseUrl}/int/js/jquery-ui-1.10.3.custom.js"></script>
    <script type="text/javascript" src="${baseUrl}/int/js/jquery.tokeninput.js"></script>
    <script type="text/javascript" src="${baseUrl}/int/js/ajaXmrTab.js"></script>
    <script type="text/javascript" src="${baseUrl}/int/js/jquery.dropdown.js"></script>
    <script src="${baseUrl}/int/js/jquery.colorpicker.js"></script>
    <script src="${baseUrl}/int/js/i18n/jquery.ui.colorpicker-en.js"></script>
    <script src="${baseUrl}/int/js/swatches/jquery.ui.colorpicker-pantone.js"> </script>
    <script src="${baseUrl}/int/js/parts/jquery.ui.colorpicker-rgbslider.js"> </script>
    <script src="${baseUrl}/int/js/parts/jquery.ui.colorpicker-memory.js">    </script>
    <script src="${baseUrl}/int/js/parsers/jquery.ui.colorpicker-cmyk-parser.js"> </script>
    <script src="${baseUrl}/int/js/parsers/jquery.ui.colorpicker-cmyk-percentage-parser.js"></script>

    <link type="text/css" rel="stylesheet" href="${baseUrl}/int/css/jquery.dropdown.css" />
    <link rel="stylesheet" href="${baseUrl}/int/css/token/token-input.css" type="text/css" />
    <link rel="stylesheet" href="${baseUrl}/int/css/token/token-input-facebook.css" type="text/css" />
    <link rel="stylesheet" type="text/css" href="${baseUrl}/int/css/defaultStyle.css" media="screen" />
    <link rel="stylesheet" type="text/css" href="${baseUrl}/int/css/adminConsoleStyle.css" media="screen" />
    <link rel="stylesheet" type="text/css" href="${baseUrl}/int/css/mainMenu.css" media="screen" />
    <link type="text/css" rel="stylesheet" href="${baseUrl}/int/css/jquery.colorpicker.css">


<script>
    $(document).ready(function(){
    	$('#pageLoaded').show();
        $(window).keydown(function(event){
        	if(event.keyCode == 13) {
                if ($(event.target).attr('id')!='searchField'){
                	event.preventDefault();
                	return false;
                }
            }
        });
        $('.datePicker').datepicker({ dateFormat: 'dd/mm/yy' });
        $(".datePicker").change(function () {
            if ($(this).val() != '') {
                console.log("dovrei controllare che la data sia corretta!");
                if ($(this).datepicker("option", "dateFormat") == 'dd/mm/yy') {
                    var d = $(this).val().substr(0, 2);
                    var m = $(this).val().substr(3, 2);
                    var y = $(this).val().substr(6, 4);
                    console.log(d + " - " + m + " - " + y);
                    var daysInMonth = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
                    if ((!(y % 4) && y % 100) || !(y % 400)) {
                        daysInMonth[1] = 29;
                    }
                    ret = d <= daysInMonth[--m];
                    if (!ret) {
                        alert("Attenzione la data " + $(this).val() + " inserita non e' valida");

                        $(this).val("");
                    }
                    console.log(ret);
                }
            }

        })
        $('.colorpicker').colorpicker({
            regional: 'en',
            ok: function (color){

                console.log(color);
                console.log($(this).val());
                $(this).css("background-color", "#"+$(this).val());
            }
        });
        $('.colorpicker').each(function(){
            $(this).css('background-color', '#'+$(this).val());

        });
       
    });



</script>
<#include "lib/stdIncludes.ftl">
<#include "lib/macros.ftl">
<#include "documents/js/jsLoader.js.ftl"/>

<style>


.info, .success, .warning, .error, .validation {
border: 1px solid;
margin: 10px 0px;
padding:15px 10px 15px 50px;
background-repeat: no-repeat;
background-position: 10px center;
min-width: 92%;
position: fixed;
top: 0px;
z-index: 10000;
}
.info {
color: #00529B;
background-color: #BDE5F8;
}
.success {
color: #4F8A10;
background-color: #DFF2BF;
}
.warning {
color: #9F6000;
background-color: #FEEFB3;
}
.error {
color: #D8000C;
background-color: #FFBABA;
}


.blue {
    background: linear-gradient(to bottom, #276780, #125873) repeat scroll 0 0 #125873;
    color: #FFFFFF;
}

.blue:hover {
    background: linear-gradient(to bottom, #276780, #5B8C9F) repeat scroll 0 0 #5B8C9F;
    color: #FFFFFF;
}

.element-title{
	font-size: 1em;
}


.audit_img{
	float: left;
    height: 20px;
    padding: 7px;
    width: 20px;
	cursor: pointer;
}

.modalLoading{
  font-family: Arial;
    font-size: 20px;
    font-weight: bold;
    left: 40%;
    position: fixed;
    top: 40%;
    }

</style>

</head>

<body>
<#include "topBanner.ftl">
<#if userDetails??>
    <#include "mainMenu.ftl">
</#if>
<div id="pageLoaded" style="display:none">
    <#include mainContent>
</div>


<div class="modal">
    <span class="modalblock"><img id="modalImg" width="48px"/><span id="modalMessage"/></span>
</div>
<div class="info" style="display:none">Info message</div>

<div class="success" style="display:none">Successful operation message</div>

<div class="warning" style="display:none">Warning message</div>

<div class="error" style="display:none">Error message</div>


</body>
</html>
</#if>