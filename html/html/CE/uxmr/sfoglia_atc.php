<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html lang="IT" xmlns="http://www.w3.org/1999/xhtml">
<head>

	<title>Sfoglia ATC</title>
<link media="screen" href="/aifa.css" rel="stylesheet" type="text/css" />
<link href="assets/css/bootstrap.min.css" rel="stylesheet" />
<link rel="stylesheet" href="assets/css/font-awesome.min.css" />
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css">


<!--[if IE 7]>
  <link rel="stylesheet" href="assets/css/font-awesome-ie7.min.css" />
<![endif]-->

<!-- page specific plugin styles -->

<!-- fonts -->

<link rel="stylesheet" href="assets/css/ace-fonts.css" />

<!-- ace styles -->

<link rel="stylesheet" href="assets/css/ace.min.css" />
<link rel="stylesheet" href="assets/css/ace-rtl.min.css" />
<link rel="stylesheet" href="assets/css/ace-skins.min.css" />

<!--[if lte IE 8]>
		  <link rel="stylesheet" href="assets/css/ace-ie.min.css" />
		<![endif]-->

<!-- inline styles related to this page -->

		<!-- ace settings handler -->


			<!--[if !IE]> -->

		<script type="text/javascript">
			window.jQuery || document.write("<script src='assets/js/jquery-2.0.3.min.js'>"+"<"+"/script>");
		</script>

		<!-- <![endif]-->

		<!--[if IE]>
		<script type="text/javascript">
		 window.jQuery || document.write("<script src='assets/js/jquery-1.10.2.min.js'>"+"<"+"/script>");
		</script>
		<![endif]-->


	<script src="assets/js/ace.min.js"></script>	
	<script src="assets/js/ace-extra.min.js"></script>

		<!-- HTML5 shim and Respond.js IE8 support of HTML5 elements and media queries -->

		<!--[if lt IE 9]>
		<script src="assets/js/html5shiv.js"></script>
		<script src="assets/js/respond.min.js"></script>
		<![endif]-->
		
	
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
	<!--a href="https://ricerca-clinica.sissdev.cineca.it"><img src="img/testata-page.jpg"  usemap="#Map3"></a-->
</div>

<!--utente-->
<table border=0 width=95% align=center><tr><td>
<!--body-->


<?
require_once "libs/http_lib.inc";
include_once "config.inc";
include_once "libs/db.inc";



	$conn2=new dbconn("FARMACI_BDUF","sibdfc1$","generici_prod");
	$table="farmaci.fatc";



$sql=new query($conn2);


if (!isset($ATC)){
	$sql_query="select  ATC,datc from $table where atc in ('A', 'B','C','D','G','H','J','L','M','N','P','R','S','V') ORDER BY ATC asc";
	$sql->set_sql($sql_query);
	$sql->exec();
	$header_tb="<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
								<thead>
									<tr>
										<th>ATC</th>
										<th>Descrizione</th>
									</tr>
								</thead>";
	while ($sql->get_row()){
		$result.="<tr>
								<td class=sc4bis>{$sql->row['ATC']}</td>
								<td class=sc4bis><a href='sfoglia_atc.php?CODE=$CODE&DECODE=$DECODE&LIVELLO=$LIVELLO&GROUP=$GROUP&ATC={$sql->row['ATC']}'>{$sql->row['DATC']}</a></td>
							</tr>";
	}
	$footer_tb="</table>";
	echo $header_tb.$result.$footer_tb;
}
else {
	$len=strlen($ATC);
	if ($len==1) $next_len=3;
	if ($len==3) $next_len=4;
	if ($len==4) $next_len=5;
	if ($len==5) $next_len=7;
	//echo "<hr>$len";
	if ($next_len>3) $checkbox=true;
	if ($next_len==7) $sql_query="select  ATC,datc, (select datc from $table where atc='$ATC') as gruppo from $table where atc like '$ATC%' and length(ATC)=$next_len ORDER BY ATC asc";
	else	$sql_query="select  ATC,datc,datc as gruppo from $table where atc like '$ATC%' and length(ATC)=$next_len ORDER BY ATC asc";
	$sql->set_sql($sql_query);
	$sql->exec();
	$header_tb="<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\"><thead><tr><th>ATC</th><th>Descrizione</th></tr></thead>";
	while ($sql->get_row()){
		if ($checkbox) {
			$decode=str_replace("'", "\'", $sql->row['DATC']);
			$group=str_replace("'", "\'", $sql->row['GRUPPO']);
			$length=strlen ($sql->row['ATC']);
				if ($length==4) $livello="III";
				if ($length==5 || $length==6) $livello="IV";
				if ($length==7) $livello="V";
				if ($GROUP=='') $this_check="<input type=\"radio\" onclick=\"
				window.opener.document.forms[0].$CODE.value='{$sql->row['ATC']}';
				window.opener.document.forms[0].$DECODE.value='$decode';
				window.opener.document.forms[0].$LIVELLO.value='$livello';
				window.opener.cf();
				window.close();\">";
			else $this_check="<input type=\"radio\" onclick=\"
				window.opener.document.forms[0].$CODE.value='{$sql->row['ATC']}';
				window.opener.document.forms[0].$DECODE.value='$decode';
				window.opener.document.forms[0].$GROUP.value='$group';
				window.opener.document.forms[0].$LIVELLO.value='$livello';
				window.opener.cf();
				window.close();\">";

		}
		if ($next_len<7) $link="<a href='sfoglia_atc.php?CODE=$CODE&DECODE=$DECODE&LIVELLO=$LIVELLO&GROUP=$GROUP&ATC={$sql->row['ATC']}'>";
		else $link="<!a>";
		$result.="<tr><td>$this_check{$sql->row['ATC']}</td><td>$link{$sql->row['DATC']}</a></td></tr>";
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