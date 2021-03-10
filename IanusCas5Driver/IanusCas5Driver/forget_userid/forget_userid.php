<?php

//MANCA LA POSSIBILITà DI RENDERE PUBBLICA LA PAGINA DI FORGET PASSWORD

//l'invio mail con la pass nuova
//hidden per assicurarsi l'identità della POST

require_once 'DB/OraDBConnection.inc.php';
require_once 'DB/OraSql.inc.php';
//require_once 'http_lib.inc.php';

$a = new OraDBConnection();
$admin_md5_crypt_chars = array (
	'.',
	'/'
);

$admin_md5_crypt_chars = array_merge($admin_md5_crypt_chars, range(0, 9), range('A', 'Z'), range('a', 'z'));
//session_start();
$table_name = "FORGET_PASS";
$num_help = "0510000000";
//$js_file = "forget_pass.js";
//$script = "<script type=\"text/javascript\" src=\"$js_file\"></script>";


	/** Controllo la lingua del browser per la personalizzazione del template di lost-password e lost-userid
	 * @autori: N.Cuccurazzu, A.Colabufalo ;
	 * */
	$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
	/** Se la lingua del browser non è nè inglese nè italiano imposto la cerco nel servizio un file di configurazione. */
	if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/lost-userid.conf.inc")){
		include_once("{$_SERVER['DOCUMENT_ROOT']}/lost-userid.conf.inc");
	}
	else if(strtoupper($language) != strtoupper("en") && strtoupper($language) != strtoupper("it")){
		
		
			/** setto inglese, prendo i termini dal file di configurazione standard di libreria */
			$language = "en";
			include_once("/http/lib/IanusCas5Driver/LOGIN/lost-userid.conf.inc");
		
	}
	else{
	/** Se il browsere è in italiano o in inglese , prendo i termini  dal file di configurazione standard di libreria 
	 * La language viene presa dalla $_SERVER['HTTP_ACCEPT_LANGUAGE']
	 */
	 	
		include_once("/http/lib/IanusCas5Driver/LOGIN/lost-userid.conf.inc");
	}
	


/* Carico la configurazione del FORGET_PASSWORD  OLD: */
//if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/lost-userid.conf.inc")){
//	/* File personalizzato per il singolo servizio
//	 * SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
//	 */
//	include_once("{$_SERVER['DOCUMENT_ROOT']}/lost-userid.conf.inc");
//}else{
//	include_once("/http/lib/IanusCas5Driver/LOGIN/lost-userid.conf.inc");
//}

$script = "<script type=\"text/javascript\">
function check_userid_forget() {
	var email = document.getElementById('email_in').value;
	
	if(email==\"\") {
		alert(\"{$lost_user['label']['Nessuna e-mail inserita'][$language]}\");
		
		document.getElementById('SX_MAIL').className='textbox-sx-mail-wrong';
		document.getElementById('CX_MAIL').className='textbox-cx-wrong';
		document.getElementById('DX_MAIL').className='textbox-dx-wrong';
		
		return false;
	}else {
		var re = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    	if (!re.test(email)) {
    		alert(\"Malformed email\");
    		return false;
    	}
    }
}
</script>";


$invia_mail = 1;
//$lang="en";

				$msg_errors = "<table>
					<tr>
						<td colspan=\"2\"><b>ERRORE</b></td>
					</tr>

					<tr>
						<td colspan=\"2\"><p>{$lost_user['label']['Errore richiesta sospesa'][$language]}:<br /> </p></td>
					</tr>
					</table>";
				
				

					$messages .= "
					<div class=\"widget-main\">
						<h4 class=\"header blue lighter bigger\"><i class=\"ace-icon fa fa-user green\"></i> {$lost_user['label']['recovery-pass'][$language]} </h4>
						<form class=\"fm-v clearfix\" action=\"\" method=\"post\" onsubmit=\"return check_userid_forget();\">
							<input type='hidden' name='CWD' value='{$_SERVER['DOCUMENT_ROOT']}'>
							<input type='hidden' name='HOST' value='{$_SERVER['HTTP_HOST']}'>
							<h6>{$lost_user['label']['Titolo Forget Userid'][$language]}</h6>
							<fieldset>
								<label class=\"block clearfix\">
									<span class=\"block input-icon input-icon-right\">
										<input type=\"text\" name=\"email_in\" id=\"email_in\" class=\"form-control\" placeholder=\"E-mail\" />
										<i class=\"ace-icon fa fa-envelope\"></i>
									</span>
			                    </label>	
								
								<span style='float:right;padding-top: 10px;'><a href=\"/\" style=\"color:#0079bc;\"><i class='fa fa-home'></i> {$lost_user['label']['backtohome'][$language]}</a></span>
		
			                    <input type=\"submit\" id=\"Invia\" name=\"Invia\" value=\"{$lost_user['label']['Invia'][$language]}\" class=\"btn btn-sm btn-info\" />				
			                
							</fieldset>
							<h4 class=\"header blue lighter bigger\"><i class=\"ace-icon fa fa-list green\"></i> {$lost_user['label']['Regole'][$language]} </h4>
								<ul>
									<li>{$lost_user['label']['Regola1'][$language]}</li>
								</ul>
						</form>
					</div>
								";
					if ( $_POST['email_in'] != "" ) {
						
					//Controllo sull'esistenza in banca dati dell'userid:
					$email_in=$_POST['email_in'];
					$userid_existence = "select userid from ANA_UTENTI_1 where email=:email";
					$b = new OraSql($a);
					$bind['EMAIL']=$email_in;
					$b->Exec($userid_existence,$bind);
					
					while ($b->getRow()) {
						$lost_userid = $b->row['USERID'];
						
						if($lost_userid!=''){
							send_mail("noreply@cineca.it", $email_in, "", "{$lost_user['label']['Userid smarrito in'][$language]}: <b>{$_SERVER['SERVER_NAME']}</b><br/> USERID: <b>$lost_userid</b> ", "{$lost_user['label']['Oggetto mail'][$language]}");						
						}
					}					
						
						$messages = "
								<div class=\"widget-main\">
									<h4 class=\"header blue lighter bigger\"><i class=\"ace-icon fa fa-key green\"></i> {$lost_user['label']['recovery-pass'][$language]}</h4>
									<div class=\"alert alert-block alert-success\">
										<strong>
											<i class=\"ace-icon fa fa-check\"></i> 
										</strong>
										{$lost_user['label']['Richiesta effettuata'][$language]}.
									</div>
									<div style=\"text-align:right\">
								    	<a href=\"/\"><i class='fa fa-home'></i> Go to Home Page</a>
								    </div>
								</div>
						";
					} else
						if ($_POST['email_in'] == "") {
//							$messages .= "<p>{$lost_user['label']['Nessuna e-mail inserita'][$language]}</p>";
						} else
							if ($lost_userid=='') {

//								$messages .= "<p>{$lost_user['label']['Nessun userid inserito'][$language]}</p>";
							}

/* GESTIRE PERSONALIZZAZIONE */
//if (file_exists("{$_SERVER['DOCUMENT_ROOT']}/forget_userid.htm")){
//	$template = file_get_contents("{$_SERVER['DOCUMENT_ROOT']}/forget_userid.htm");
//}else {
//	$template = file_get_contents("/http/lib/IanusCas5Driver/LOGIN/template/forget_userid.html");
//}

$template = file_get_contents("/http/lib/IanusCas5Driver/LOGIN/template/forget_userid.html");

/*
$query_check_existence = "select * from idp_spec";
$b = new OraSql($a);
$b->Exec($query_check_existence);
while ($b->getRow()) {
	$idp = $b->row['PORTAL'];
}
$query_check_existence = "select * from idp_servizi where upper(url)='".strtoupper($_SERVER['HTTP_HOST'])."'";
$b = new OraSql($a);
$b->Exec($query_check_existence);
while ($b->getRow()) {
	$id_servizio = $b->row['ID'];
}
$idp=split("\.", $idp);
$idp=strtoupper($idp[0]);
if (isset($forceTemplate[$idp][$id_servizio])) 
$template = file_get_contents("/http/lib/IanusCas5Driver/LOGIN/template/".$forceTemplate[$idp][$id_servizio]);
*/
Logger::send($language);
$template = preg_replace("/<!-- titolo -->/i", $lost_user['label']['titolo'], $template);
$template = preg_replace("/<!-- action -->/i", "", $template);
$template = preg_replace("/<!-- userid -->/i", $lost_user['label']['userid'][$language], $template);
$template = preg_replace("/<!-- siss -->/i", $lost_user['label']['siss'][$language], $template);
$template = preg_replace("/<!-- reserved -->/i", $lost_user['label']['reserved'][$language], $template);
$template = preg_replace("/<!-- proceed-button -->/i", $lost_user['label']['proceed-button'][$language], $template);
$template = preg_replace("/<!-- lost-userid -->/i", $lost_user['label']['lost-userid'][$language], $template);
$template = preg_replace("/<!-- messages -->/i", $messages, $template);
$template = preg_replace("/<!-- script -->/i", $script, $template);

if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login.css")) {
	$template=str_replace("<!--custom_css-->", "<link rel=\"stylesheet\" href=\"/authzssl/login.css\" />", $template);
}
die($template);

function send_mail($from, $to, $bcc, $testo, $subject) {
	$eol = "\r\n";
	$headers .= 'From: ' . $from . '' . $eol;
	$headers .= 'BCC: ' . $bcc . '' . $eol;
	$headers .= "Content-type: text/html $eol";
	//	$testo=preg_replace("/<(.*?)>/", "", $testo);
	$testo = nl2br($testo, true);
	$today = date("Y_m_d");
	$now = date("d/m/Y h:i:s");
	$log = "
				<p align=center>Email sended at $now</p>
				<li>to:$to</li>
				<li>headers:$headers</li>
				<li>oggetto:$subject</li>
				<li>testo:$testo</li>
				<hr>
				";
	if (!file_exists("email_log/email_log_{$today}.html")) {
		mkdir("email_log/email_log_{$today}.html", 0777);
	}

	$log .= file_get_contents("email_log/email_log_{$today}.html");
	$fp = fopen("email_log/email_log_{$today}.html", 'w');
	fwrite($fp, $log);
	fclose($fp);
	mail($to, $subject, $testo, $headers);
}

			
	

?>
