<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html lang="IT" xmlns="http://www.w3.org/1999/xhtml">
<head>

	<title>Sfoglia ATC</title>
<link media="screen" href="/aifa.css" rel="stylesheet" type="text/css" />
<!--meta refresh-->
<script type="text/javascript" src="libs/js/fmweb.js"></script>

<script type="text/javascript" src="libs/js/show_values.js"></script>
<script type="text/javascript">

	function IsNumeric(sText)
		{
		   var ValidChars = "0123456789.";
		   var IsNumber=true;
		   var Char;


		   for (i = 0; i < sText.length && IsNumber == true; i++)
		      {
		      Char = sText.charAt(i);
		      if (ValidChars.indexOf(Char) == -1)
		         {
		         IsNumber = false;
		         }
		      }
		   return IsNumber;

		   }

function createRequestObject() {
			var ro;
			var browser = navigator.appName;
			if(browser == "Microsoft Internet Explorer"){
				ro = new ActiveXObject("Microsoft.XMLHTTP");
			}else{
				ro = new XMLHttpRequest();
			}
			return ro;
		}
		var ritorno=true;
		var http = createRequestObject();

		function show_hide(id_tag){
			if (document.getElementById(id_tag).style.display!='') document.getElementById(id_tag).style.display='';
			else document.getElementById(id_tag).style.display='none';
		}

		function ajax_call(html_id, param) {
			if (ritorno){
			ritorno=false;
			//document.getElementById(html_id).innerHTML='<img src="/images/loading.gif">';
			call='ajax.php?HTML_ID='+html_id+'&'+param;
			alert(call);
			document.getElementById('debug').innerHTML='<a href="'+call+'" target="_new">debug</a>';
			http.open('get', call);
			http.onreadystatechange = handleResponse;
			http.send(null);
			 } else {
	      setTimeout('ajax_call("'+html_id+'", "'+param+'")', 10);
	   }
		}

		function ajax_call_form(FORM, param1, param2, param3, param4) {
			if (ritorno){
			ritorno=false;
			//document.getElementById(html_id).innerHTML='<img src="/images/loading.gif">';
			call='ajax.php?FORM='+FORM+'&'+param1+'&'+param2+'&'+param3+'&'+param4;
			//document.getElementById('debug').innerHTML='<a href="'+call+'" target="_new">debug</a>';
			//alert (call);
			http.open('get', call);
			http.onreadystatechange = handleResponse;
			http.send(null);
			 } else {
	      setTimeout('ajax_call_form('+FORM+', '+param1+', '+param2+', '+param3+', '+param4+')', 10);
	   }
		}

		function ajax_call_select(FORM, param1, param2, param3, param4) {
			if (ritorno){
			ritorno=false;
			document.getElementById(FORM).innerHTML='<img src="/images/loading.gif">';
			call='ajax.php?SELECT='+FORM+'&'+param1+'&'+param2+'&'+param3+'&'+param4;
			//document.getElementById('debug').innerHTML='<a href="'+call+'" target="_new">debug</a>';
			//alert (call);
			//document.getElementById(FORM).innerHTML = '<option>asdfas</option>';
			http.open('get', call);
			http.onreadystatechange = handleResponse;
			http.send(null);
			 } else {
	      setTimeout('ajax_call_select('+FORM+', '+param1+', '+param2+', '+param3+', '+param4+')', 10);
	   }
		}



		function handleResponse() {
			if(http.readyState == 4){
				var response = http.responseText;
				if (response.match("#DIV#")){
					resp=response.split("#DIV#");
					resp[0]=resp[0].replace('\n','');
					resp[0]=resp[0].replace('\s','');
					//alert (resp[0]);
					document.getElementById(resp[0]).innerHTML = resp[1];
				}
				if (response.match("#FORM#")){
					resp=response.split("#FORM#");
					//alert (resp[0]+' - '+resp[1]);
					document.getElementById('select_'+resp[0]).innerHTML = resp[1];
				}
				if (response.match("#SELECT#")){
					resp=response.split("#SELECT#");
					//alert (resp[0]+' - '+resp[1]);
					document.getElementById(resp[0]).innerHTML = resp[1];
				}
				ritorno=true;
				}
		}

		function show_div(){
			var divs=document.getElementsByTagName("div");
			//alert ('ciao');
			for (i=0;i<divs.length;i++){
				if (divs[i].id.match(/^emendation_/)) divs[i].style.display='';
			}
			//for (i=0;i<document.getElementsByTag('DIV').length;i++)
			//	alert(document.getElementsByTag('DIV')[i].id);
		}
		function hide_div(){
			var divs=document.getElementsByTagName("div");
			for (i=0;i<divs.length;i++){
				if (divs[i].id.match(/^emendation_/)) divs[i].style.display='none';
			}
			//for (i=0;i<document.getElementsByTag('DIV').length;i++)
			//	alert(document.getElementsByTag('DIV')[i].id);
		}

		</script>
<!--script-->
</head>
<body>
<div id='debug'></div>
<!--testata-->
<div id="div8476" class="head-page">
	<a href="https://ricerca-clinica.sissdev.cineca.it"><img src="img/testata-page.jpg"  usemap="#Map3"></a>
</div>

<!--utente-->
<table border=0 width=95% align=center><tr><td>
<!--body-->


<?
require_once "libs/http_lib.inc";
include_once "config.inc";
include_once "libs/db.inc";


$conn2=new dbconn();



$sql=new query($conn2);


if (!isset($FF)){
	$sql_query="select distinct dosage_from_category,d_dosage_from_category
from dosage_form_categorie
order by 1";
	$sql->set_sql($sql_query);
	$sql->exec();
	$header_tb="<table border=1 cellpadding=0 cellspacing=0><tr><th>Codice</th><th>Descrizione</th></tr>";
	while ($sql->get_row()){
		$result.="<tr><td>{$sql->row['DOSAGE_FROM_CATEGORY']}</td><td><a href='sfoglia_forma_farm.php?CODE=$CODE&DECODE=$DECODE&FF={$sql->row['DOSAGE_FROM_CATEGORY']}'>{$sql->row['D_DOSAGE_FROM_CATEGORY']}</a></td></tr>";
	}
	$footer_tb="</table>";
	echo $header_tb.$result.$footer_tb;
}
else {
	if ($FF=='') $cond=" is null ";
	else $cond="=$FF";
	$sql_query="select *
  from DOSAGE_FORM_IT
 	where dosage_from_category $cond order by term_name";
 	
	$sql->set_sql($sql_query);
	$sql->exec();
	$header_tb="<table border=1 cellpadding=0 cellspacing=0><tr><th>Codice</th><th>Descrizione</th></tr>";
	while ($sql->get_row()){
		
			$decode=str_replace("'", "\'", $sql->row['TERM_NAME']);
			$this_check="<input type=\"radio\" onclick=\"
				window.opener.document.forms[0].$CODE.value='{$sql->row['TERM_IDENTIFIER']}';
				window.opener.document.forms[0].$DECODE.value='$decode';
				window.opener.cf();
				window.close();\">";

		$result.="<tr><td>$this_check{$sql->row['TERM_IDENTIFIER']}</td><td>$decode</td></tr>";
	}
	$footer_tb="</table>";
	echo "<a href=\"javascript:history.back();\">indietro</a>".$header_tb.$result.$footer_tb;
}




?>
</td></tr></table>


<!-- START CANCEL FOOT -->

<!--footer-->
<table width="100%" >
	<tr>
		<!--td align="center">In collaborazione con: <br/><a href="http://www.cineca.org/"><img src="https://trasparenza.agenziafarmaco.it/images/logoblu.gif" alt="" /></a>
		<br/><a title="Valid XHTML 1.0" href="http://validator.w3.org/check/referer"></a></td-->
		<!--logo-->
	</tr>
</table>

</body>
</html>