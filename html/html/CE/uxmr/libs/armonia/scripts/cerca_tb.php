<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html lang="IT" xmlns="http://www.w3.org/1999/xhtml">
<head>

	<title>Sfoglia ATC@ AIFA |Check-In</title>
<link media="screen" href="http://aifa-trasparenza.test.cineca.it/aifa.css" rel="stylesheet" type="text/css" />
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
					resp=response.explode("#DIV#");
					resp[0]=resp[0].replace('\n','');
					resp[0]=resp[0].replace('\s','');
					//alert (resp[0]);
					document.getElementById(resp[0]).innerHTML = resp[1];
				}
				if (response.match("#FORM#")){
					resp=response.explode("#FORM#");
					//alert (resp[0]+' - '+resp[1]);
					document.getElementById('select_'+resp[0]).innerHTML = resp[1];
				}
				if (response.match("#SELECT#")){
					resp=response.explode("#SELECT#");
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
<body onload="
		
">
<div id='debug'></div>
<!--testata-->
<table width="100%" border="0" align="center" class="bg_testata">
	<tr>
	  <td class="bg"><a href="http://www.aifa.gov.it" target="blank" title="Sito AIFA"><img src="http://aifa-trasparenza.test.cineca.it/images/nulla.gif" border="0"/></a></td>
	</tr>
</table>
<A href="index.php"> <img src="http://aifa-trasparenza.test.cineca.it/images/hp_chek-in.gif"/></a>
<!--utente-->
<table border=0 width=95% align=center><tr><td>
<!--body-->
<p align=center class=titolo>Cerca in DB</p>


<?
require_once "libs/http_lib.inc";
require_once "config.inc";
include_once "libs/db.inc";



$conn=new dbconn();
$sql=new query($conn);

$hiddens="
		<input type=\"hidden\" name=\"tbsearch\" value=\"{$tbsearch}\">
		<input type=\"hidden\" name=\"CODE\" value=\"{$CODE}\">
		<input type=\"hidden\" name=\"DECODE\" value=\"{$DECODE}\">
		<input type=\"hidden\" name=\"FIELD\" value=\"{$FIELD}\">
";

$body="
	<form method=post action=\"cerca_tb.php\">
		$hiddens
		<table border=0 cellpadding=2 cellspacing=2  align=center>
			<tr>
				<td class=destra>Cerca:</td><td class=input>
				<input type=text name=\"search\" value=\"{$search}\" size=20></td>
			</tr> 
			<tr>
				<td colspan=2 align=center><input type='submit' value='Cerca'></td>
			</tr>
		</table>
	</form>
";
//print_r($in);
if (isset($search) && $search!=''){
	$sql_query="select $CODE, $DECODE from {$service}_{$tbsearch} where upper($DECODE) like '%".strtoupper($search)."%' order by $DECODE asc";
	$sql->set_sql($sql_query);
	$sql->exec();
	$body.="<table><tr><th>Descrizione</th><th>&nbsp;</th></tr>";
	while ($sql->get_row()){
		$js_decode=str_replace("'", "\'", $sql->row[$DECODE]);
		$decode=str_replace($search, "<b>".$search."</b>", $sql->row[$DECODE]);
		$risultato.= "
		<tr>
			<td>{$decode}</td>
			<td><input type=\"button\" value=\">>\" onclick=\"
				window.opener.document.forms[0].D_{$FIELD}.value='{$js_decode}';
				window.opener.document.forms[0].{$FIELD}.value='{$sql->row[$CODE]}';
				window.close();
			\"></td>
		</tr>";
	}
	if ($risultato=='') $risultato="<tr><td colspan=2>La ricerca non ha prodotto risultati</td></tr>";
	$body.=$risultato."</table>";
	
}


echo $body;
?>
</td></tr></table>


<!-- START CANCEL FOOT -->

<!--footer-->


</body>
</html>