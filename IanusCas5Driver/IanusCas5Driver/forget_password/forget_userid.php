<?php


//..FORGET USERID SCRIPT 0.1
//coded by A.Colabufalo il 21/10/09

//MANCA LA POSSIBILIT� DI RENDERE PUBBLICA LA PAGINA DI FORGET PASSWORD

//l'invio mail con la pass nuova
//hidden per assicurarsi l'identit� della POST

require_once 'DB/OraDBConnection.inc.php';
require_once 'DB/OraSql.inc.php';
//require_once 'http_lib.inc.php';

$a = new OraDBConnection('giotto', 'gio0109!', 'generici_dev');

$admin_md5_crypt_chars = array (
	'.',
	'/'
);

$admin_md5_crypt_chars = array_merge($admin_md5_crypt_chars, range(0, 9), range('A', 'Z'), range('a', 'z'));
//session_start();
$table_name = "FORGET_PASS";
$num_help = "0510000000";
$tempalte_file = "template.htm";
$js_file = "forget_pass.js";
$script = "<script type=\"text/javascript\" src=\"$js_file\"></script>";

$invia_mail = 1;
$lang="en";
$lang = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);

if(strtolower($lang)=='it'){
	
	$testi['Errore richiesta sospesa']="Userid non presente in banca dati o una precedente richiesta di cambio password  � ancora sospesa";
				$testi['Titolo Forget Userid']="Procedere con l'inserimento della sua e-mail.";
				$testi['Invia']="Invia";
				$testi['Regole']="REGOLE:";
				$testi['Regola1']="Dopo l'invio della richiesta verra' inviato all'indirizzo e-mail l'userid corrispondente in banca dati ";
				$testi['Richiesta effettuata']="Richiesta effettuata";
				$testi['Oggetto mail']="Assistenza Userid Cineca ";
				$testi['Userid smarrito in']="Userid smarrito in";
				$testi['Il suo userid �']="Il suo userid �";
				$testi['Nessuna e-mail inserita']="Nessuna e-mail inserita";
				$testi['Nessun userid inserito']="Nessun userid in banca dati corrisponde alla mail indicata";
				
				
				
							
				}
			else{
				
				$testi['Errore richiesta sospesa']="Userid not present in data base or a previous request of change password is suspend";
				$testi['Titolo Forget Userid']="Insert your e-mail address";
				$testi['Invia']="Send";
				$testi['Regole']="RULES:";
				$testi['Regola1']="After the submit the system will send the correspondig data base userid on your e-mail address ";
				$testi['Richiesta effettuata']="Request done";
				$testi['Oggetto mail']="Cineca Userid Assistance";
				$testi['Userid smarrito in']="Userid lost in";
				$testi['Il suo userid �']="Your userid is";
				$testi['Nessuna e-mail inserita']="Nobody e-mail inserted";
				$testi['Nessun userid inserito']="Nobody userid in data base corrisponding on the inserted mail";
				
			}			

//----------prametri configurabili--------------------------------------

$msg_errors = "<table>
					<tr>
						<td colspan=\"2\"><b>ERRORE</b></td>
					</tr>

					<tr>
						<td colspan=\"2\"><p>{$testi['Errore richiesta sospesa']}:<br /> </p></td>
					</tr>
				</table>";
				
				
$messages .= "<form action=\"\" method=\"post\" onsubmit=\"return check_passwords_forget();\"><br /><br /><br /><br />
								<table style=\"width:50%;\" align=\"center\">
									<tr>
										<td colspan=\"2\"><b>{$testi['Titolo Forget Userid']}</b></td>
									</tr>
									<tr>
										<td width=\"200px\" align=\"right\">E-mail:</td>
										<td align=\"left\"><input name=\"email_in\" id=\"email_in\" type=\"text\" tabindex=\"3\" size=\"20\" /></td>
									</tr>
									<tr><td align=\"right\">&nbsp;</td>
										<td colspan=\"2\"><input type=\"submit\" value=\"{$testi['Invia']}\" name=\"{$testi['Invia']}\" tabindex=\"4\" /></td>
									</tr>
								</table>
								</form><br />
								<h2>{$testi['Regole']}</h2>
								<ul>
								<li>{$testi['Regola1']}</li>
								</ul>
								<br />
								";


					if (isset ($_GET['debug'])) {
						$messages .= "da db: " . $old_pass_db . "<br />";
						$pass_db_tmp = str_replace('$apr1$', '', $old_pass_db);
						$pass_db_salt = substr($pass_db_tmp, 0, strpos($pass_db_tmp, '$'));

						$messages .= "troncata: " . $pass_db_tmp . "<br />";
						$messages .= "salt: " . $pass_db_salt . "<br />";
						$messages .= "from ianus function old: " . $passwd . "<br />";
						$messages .= "from ianus function NEW: " . $new_passwd . "<br />";

					}


					//print_r($_POST);
					if ( $_POST['email_in'] != "" ) {
						
					//Controllo sull'esistenza in banca dati dell'userid:
					$email_in=$_POST['email_in'];
					$userid_existence = "select userid from ANA_UTENTI_1 where email='$email_in'";
					$b = new OraSql($a);
					$b->Exec($userid_existence);

					while ($b->getRow()) {
						$lost_userid = $b->row['USERID'];
						
						if($lost_userid!=''){
							send_mail("noreply@cineca.it", $email_in, "", "{$testi['Userid smarrito in']}: <b>{$_SERVER['SERVER_NAME']}</b><br/>{$testi['Il suo userid �']}: $lost_userid ", "{$testi['Oggetto mail']}");						
						}
					}					
						
						$messages = "<p><h1>{$testi['Richiesta effettuata']}</h1><a href=\"../../../../authzssl/login.php\">Go to Login</a></p>";
					} else
						if ($_POST['email_in'] == "") {
							$messages .= "<p>{$testi['Nessuna e-mail inserita']}</p>";
						} else
							if ($lost_userid=='') {

								$messages .= "<p>{$testi['Nessun userid inserito']}</p>";
							} 



//$template = file_get_contents("template.htm");
if (file_exists("{$_SERVER['DOCUMENT_ROOT']}/forget_password.htm")) $template = file_get_contents("{$_SERVER['DOCUMENT_ROOT']}/forget_password.htm"); 
else $template = file_get_contents("/http/lib/DriverIanus/forget_password/template.htm");
$template = str_replace("<!--infos-->", $infos, $template);
$template = str_replace("<!--mainmenu-->", $mainmenu, $template);
$template = str_replace("<!--filters-->", $filters, $template);
$template = str_replace("<!--mailboxes-->", $mailboxes, $template);
$template = str_replace("<!--messages-->", $messages, $template);
$template = str_replace("<!--message-->", $message, $template);
$template = str_replace("<!--SCRIPT-->", $script, $template);

die($template);

function send_mail($from, $to, $bcc, $testo, $subject) {
	$eol = "\r\n";
	$headers .= 'From: ' . $from . '' . $eol;
	$headers .= 'BCC: ' . $bcc . '' . $eol;
	$headers .= "Content-type: text/html $eol";
	//	$testo=preg_replace("/<(.*?)>/", "", $testo);
	$testo .= nl2br($testo, true);
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