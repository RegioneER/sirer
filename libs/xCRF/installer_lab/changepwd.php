<?php

//..CHANGE PASSWORD SCRIPT 0.1
//coded by A.Colabufalo il 21/10/09

require_once 'libs/http_lib.inc';
require_once 'DB/OraDBConnection.inc.php';
require_once 'DB/OraSql.inc.php';

	$ammin_file=$_SERVER['DOCUMENT_ROOT'];
	$ammin_file=preg_replace("/html/i", "config/amministrazione.cfg", $ammin_file);
	$handle = fopen($ammin_file, "r");
	$contents = fread($handle, filesize($ammin_file));
	fclose($handle);
	$ammin_config_line=preg_split("/\n/", $contents);
	for ($i=0;$i<count($ammin_config_line);$i++) {
		if (preg_match("/OraUserid/i",$ammin_config_line[$i])) $Ora_Userid=preg_replace("/OraUserid (.*)/i", "\\1" , $ammin_config_line[$i]);
		if (preg_match("/OraPassword/i",$ammin_config_line[$i])) $Ora_Pass=preg_replace("/OraPassword (.*)/i", "\\1" , $ammin_config_line[$i]);
		if (preg_match("/OraInstance/i",$ammin_config_line[$i])) $Ora_Host=preg_replace("/OraInstance (.*)/i", "\\1" , $ammin_config_line[$i]);
	}
	$Ora_Userid=preg_replace("/\s/ ", "",$Ora_Userid);
	$Ora_Pass=preg_replace("/\s/", "",$Ora_Pass);
	$Ora_Host=preg_replace("/\s/", "",$Ora_Host);

$a = new OraDBConnection($Ora_Userid, $Ora_Pass, $Ora_Host);
$admin_md5_crypt_chars = array (
	'.',
	'/'
);

$admin_md5_crypt_chars = array_merge($admin_md5_crypt_chars, range(0, 9), range('A', 'Z'), range('a', 'z'));
//session_start();
$table_name = "FORGET_PASS";
$num_help = "0510000000";
$template_file = "forget_password/template.htm";
$js_file = "forget_pass.js";
$script = "<script type=\"text/javascript\" src=\"$js_file\"></script>";

$invia_mail = 1;

//----------prametri configurabili--------------------------------------


//Script js per il check password

$language="en";

$lost_pass['label']['userid']['it'] = "ID Utente";
$lost_pass['label']['recovery-pass']['it'] = "Recupero Password";
$lost_pass['label']['siss']['it'] = "Sistemi Informativi e Servizi per la Sanit&agrave;";
$lost_pass['label']['reserved']['it'] = "Tutti i diritti riservati";
$lost_pass['label']['proceed-button']['it'] = "Procedi";
$lost_pass['label']['lost-userid']['it'] = "Recupero Nome utente?";
$lost_pass['label']['Errore richiesta sospesa']['it']="Userid non presente in banca dati o una precedente richiesta di cambio password  ï¿½ ancora sospesa";
$lost_pass['label']['Titolo Forget Userid']['it']="Procedere con l'inserimento della sua e-mail.";
$lost_pass['label']['Invia']['it']="Invia";
$lost_pass['label']['Regole']['it']="REGOLE:";
$lost_pass['label']['Regola1']['it']="Dopo l'invio della richiesta verra' inviato all'indirizzo e-mail l'userid corrispondente in banca dati ";
$lost_pass['label']['Regola2']['it']="La password deve essere lunga almeno 8 caratteri";
$lost_pass['label']['Regola3']['it']="La password deve contenere almeno un numero, una cifra, un carattere speciale";
$lost_pass['label']['Regola4']['it']="La password non può contenere l'username";
$lost_pass['label']['Richiesta effettuata']['it']="Richiesta effettuata";
$lost_pass['label']['Oggetto mail']['it']="Assistenza Password Cineca ";
$lost_pass['label']['Userid smarrito in']['it']="Userid smarrito in";
$lost_pass['label']['your-userid']['it']="Il suo userid è";
$lost_pass['label']['Nessuna e-mail inserita']['it']="Nessuna e-mail inserita";
$lost_pass['label']['Nessun userid inserito']['it']="Nessun userid in banca dati corrisponde alla mail indicata";
$lost_pass['label']['Password cambiata']['it']="Password cambiata correttamente";
$lost_pass['label']['Testo mail change password']['it']="Per avviare la procedura di reimpostazione della password per il suo account ";
$lost_pass['label']['fare clic sul seguente link']['it']="fare clic sul seguente link ";
$lost_pass['label']['se il link non funziona']['it']="Se il link sopra indicato non funziona, copia l'URL e incollalo in una nuova finestra del browser";
$lost_pass['label']['Email inviata con successo']['it']="Email inviata con successo";
$lost_pass['label']['Seguire le istruzioni']['it']="Seguire le istruzioni per cambiare la password";
$lost_pass['label']['Stringa segreta riconosciuta']['it']="Stringa segreta riconosciuta dalla mail. Procedere con il cambio password.";
$lost_pass['label']['Password non coincidono']['it']="Le password inserite come \"nuova password\" non coincidono";
$lost_pass['label']['Inserire la nuova password']['it']="Inserire la nuova password";
$lost_pass['label']['Inserire la nuova password di controllo']['it']="Inserire la nuova password di controllo";
$lost_pass['label']['Re-inserire lo Userid']['it']="Re-inserire lo Userid";
$lost_pass['label']['Procedi']['it']="Procedi";
$lost_pass['label']['Userid']['it']="Nome utente";
$lost_pass['label']['New Password']['it']="Nuova Parola Chiave";
$lost_pass['label']['Password Check']['it']="Controllo Parola Chiave";
$lost_pass['label']['Lost Userid']['it']="Nome utente dimenticato?";

$lost_pass['label']['userid']['en'] = "Userid";
$lost_pass['label']['recovery-pass']['en'] = "Password Recovery";
$lost_pass['label']['siss']['en'] = "System and Services for Health";
$lost_pass['label']['reserved']['en'] = "All rights reserved";
$lost_pass['label']['proceed-button']['en'] = "Login";
$lost_pass['label']['lost-userid']['en'] = "Lost Userid?";
$lost_pass['label']['Errore richiesta sospesa']['en']="Userid not recognized or  previous request still pending";
$lost_pass['label']['Titolo Forget Userid']['en']="Please enter your e-mail address";
$lost_pass['label']['Invia']['en']="Send";
$lost_pass['label']['Regole']['en']="RULES:";
$lost_pass['label']['Regola1']['en']="Your userid will be sent to the entered e-mail address";
$lost_pass['label']['Regola2']['en']="The password must have at least 8 chars";
$lost_pass['label']['Regola3']['en']="The password must contain a number, a code and a special character";
$lost_pass['label']['Regola4']['en']="The password can't contain the username'";
$lost_pass['label']['Richiesta effettuata']['en']="Request done";
$lost_pass['label']['Oggetto mail']['en']="Cineca Password Assistance";
$lost_pass['label']['Userid smarrito in']['en']="Userid lost in";
$lost_pass['label']['your-userid']['en']="Your userid is";
$lost_pass['label']['Nessuna e-mail inserita']['en']="No e-mail address entered";
$lost_pass['label']['Nessun userid inserito']['en']="No userid  corrisponding to the entered e-mail address";
$lost_pass['label']['Password cambiata']['en']="Password succesfully changed";
$lost_pass['label']['Testo mail change password']['en']="To update your password: ";
$lost_pass['label']['fare clic sul seguente link']['en']="Click on this link ";
$lost_pass['label']['se il link non funziona']['en']="If the link doesn't work, please copy the URL and paste it in a new browser window";
$lost_pass['label']['Email inviata con successo']['en']="Email succesfully sent";
$lost_pass['label']['Seguire le istruzioni']['en']="Please follow the instructions to change the password";
$lost_pass['label']['Stringa segreta riconosciuta']['en']="Secret string recognized. Please proceed to change your password.";
$lost_pass['label']['Password non coincidono']['en']="Passwords do not match";
$lost_pass['label']['Inserire la nuova password']['en']="Please enter your new password";
$lost_pass['label']['Inserire la nuova password di controllo']['en']="Please re-enter your new password";
$lost_pass['label']['Re-inserire lo Userid']['en']="Please Re-enter your Userid";
$lost_pass['label']['Procedi']['en']="Proceed";
$lost_pass['label']['Userid']['en']="UserID";
$lost_pass['label']['New Password']['en']="New Password";
$lost_pass['label']['Password Check']['en']="Password Check";
$lost_pass['label']['Lost Userid']['en']="Lost Userid?";


$script = "<script type=\"text/javascript\">
function check_passwords_forget() {

	var expr_username = /gargano/i;
	var expr_num = /[0-9]/;
	var expr_letter = /[a-zA-Z]/;
	var expr_char = /[\!\"$%&()*+,-./:;<=>?\^]/;
	var new_pass_check = document.getElementById('new_password_check').value;
	var new_pass = document.getElementById('new_password').value;
//	var old_pass = document.getElementById('old_password').value;

	if(new_pass==\"\") {
		alert(\"{$lost_pass['label']['Inserire la nuova password'][$language]}\");
		
		document.getElementById('SX_PASS').className='textbox-sx-pass-wrong';
		document.getElementById('CX_PASS').className='textbox-cx-wrong';
		document.getElementById('DX_PASS').className='textbox-dx-wrong';
		
		return false;
	}
	if(new_pass_check==\"\") {
		alert(\"{$lost_pass['label']['Inserire la nuova password di controllo'][$language]}\");
		
		document.getElementById('SX_PASS_C').className='textbox-sx-pass-wrong';
		document.getElementById('CX_PASS_C').className='textbox-cx-wrong';
		document.getElementById('DX_PASS_C').className='textbox-dx-wrong';
		
		return false;
	}
	if(new_pass_check!=new_pass) {
		alert(\"{$lost_pass['label']['Password non coincidono'][$language]}\");
		
		document.getElementById('SX_PASS').className='textbox-sx-pass-wrong';
		document.getElementById('CX_PASS').className='textbox-cx-wrong';
		document.getElementById('DX_PASS').className='textbox-dx-wrong';
		
		document.getElementById('SX_PASS_C').className='textbox-sx-pass-wrong';
		document.getElementById('CX_PASS_C').className='textbox-cx-wrong';
		document.getElementById('DX_PASS_C').className='textbox-dx-wrong';
		return false;
	}
//	if(old_pass==\"\") {
//		alert(\"{$lost_pass['label']['Inserire la vecchia password'][$language]}\");
//		document.getElementById('old_password').style.border=\"1px solid red\";
//		return false;
//	}
	if(new_pass.length<8) {
		alert(\"{$lost_pass['label']['Regola2'][$language]}\");
		return false;
	}

	if(expr_username.test(new_pass)) { alert(\"{$lost_pass['label']['Regola4'][$language]}\"); return false; }
	if(!expr_num.test(new_pass)) { alert(\"{$lost_pass['label']['Regola3'][$language]}\"); return false; }
	if(!expr_letter.test(new_pass)) { alert(\"{$lost_pass['label']['Regola3'][$language]}\"); return false; }
	if(!expr_char.test(new_pass)) { alert(\"{$lost_pass['label']['Regola3'][$language]} !\\\"$%&()*+,-./:;<=>?\^\"); return false; }

	return true;

}
function testPassword_forget(passwd) {
	var intScore = 0
	var strVerdict = \"weak\"
	var strLog = \"\"

	// PASSWORD LENGTH
	if (passwd.length < 5) // length 4 or less
	{
		intScore = (intScore + 3)
		strLog = strLog + \"3 points for length (\" + passwd.length + \")\\n\"
	} else if (passwd.length > 4 && passwd.length < 8) // length between 5 and
														// 7
	{
		intScore = (intScore + 6)
		strLog = strLog + \"6 points for length (\" + passwd.length + \")\\n\"
	} else if (passwd.length > 7 && passwd.length < 16)// length between 8 and
														// 15
	{
		intScore = (intScore + 15)
		strLog = strLog + \"15 points for length (\" + passwd.length + \")\\n\"
	} else if (passwd.length > 15) // length 16 or more
	{
		intScore = (intScore + 18)
		strLog = strLog + \"18 point for length (\" + passwd.length + \")\\n\"
	}

	// LETTERS (Not exactly implemented as dictacted above because of my limited
	// understanding of Regex)
	if (passwd.match(/[a-z]/)) // [verified] at least one lower case letter
	{
		intScore = (intScore + 1)
		strLog = strLog + \"1 point for at least one lower case char\\n\"
	}

	if (passwd.match(/[A-Z]/)) // [verified] at least one upper case letter
	{
		intScore = (intScore + 5)
		strLog = strLog + \"5 points for at least one upper case char\\n\"
	}

	// NUMBERS
	if (passwd.match(/\d+/)) // [verified] at least one number
	{
		intScore = (intScore + 5)
		strLog = strLog + \"5 points for at least one number\\n\"
	}

	if (passwd.match(/(.*[0-9].*[0-9].*[0-9])/)) // [verified] at least three
													// numbers
	{
		intScore = (intScore + 5)
		strLog = strLog + \"5 points for at least three numbers\\n\"
	}

	// SPECIAL CHAR
	if (passwd.match(/.[!,@,#,$,%,^,&,*,?,_,~]/)) // [verified] at least one
													// special character
	{
		intScore = (intScore + 5)
		strLog = strLog + \"5 points for at least one special char\\n\"
	}

	// [verified] at least two special characters
	if (passwd.match(/(.*[!,@,#,$,%,^,&,*,?,_,~].*[!,@,#,$,%,^,&,*,?,_,~])/)) {
		intScore = (intScore + 5)
		strLog = strLog + \"5 points for at least two special chars\\n\"
	}

	// COMBOS
	if (passwd.match(/([a-z].*[A-Z])|([A-Z].*[a-z])/)) // [verified] both upper
														// and lower case
	{
		intScore = (intScore + 2)
		strLog = strLog + \"2 combo points for upper and lower letters\\n\"
	}

	if (passwd.match(/([a-zA-Z])/) && passwd.match(/([0-9])/)) // [verified]
																// both letters
																// and numbers
	{
		intScore = (intScore + 4)
		strLog = strLog + \"4 combo points for letters and numbers\\n\"
	}

	// [verified] letters, numbers, and special characters
	if (passwd
			.match(/([a-zA-Z0-9].*[!,@,#,$,%,^,&,*,?,_,~])|([!,@,#,$,%,^,&,*,?,_,~].*[a-zA-Z0-9])/)) {
		intScore = (intScore + 4)
		strLog = strLog
				+ \"4 combo points for letters, numbers and special chars\\n\"
	}

	if (intScore < 16) {
		strVerdict = \"invalid\";
		document.getElementById(\"colorMe\").style.background = \"red\";
	} else if (intScore > 15 && intScore < 20) {
		strVerdict = \"weak\";
		document.getElementById(\"colorMe\").style.background = \"orange\";
	} else if (intScore > 19 && intScore < 30) {
		strVerdict = \"normal\";
		document.getElementById(\"colorMe\").style.background = \"yellow\";
	} else if (intScore > 29 && intScore < 40) {
		strVerdict = \"strong\";
		document.getElementById(\"colorMe\").style.background = \"green\";
	} else {
		strVerdict = \"stronger\";
		document.getElementById(\"colorMe\").style.background = \"limeGreen\";
	}

	var perc=intScore*3;

// document.getElementById(\"score\").value=intScore;
// document.getElementById(\"verdict\").value=strVerdict;
	// document.getElementById(\"matchlog\").value=strLog;
	//document.getElementById(\"colorMe\").innerHTML = \"    \" + strVerdict + ' - ' +perc + '%';
	if(perc > 100) perc=100;
	document.getElementById(\"colorMe\").style.width = perc+\"%\";
//alert(intScore);
	return intScore + \" \" + strVerdict;

}

</script>";


$msg_errors = "<table>
					<tr>
						<td colspan=\"2\"><b>ERRORE</b></td>
					</tr>

					<tr>
						<td colspan=\"2\"><p>Userid non presente in banca dati o una precedente richiesta di cambio password  &egrave; ancora sospesa:<br />Contattare il numero <b>$num_help</b> per richiedere assistenza.</p></td>
					</tr>
				</table>";

//creazione tabella se non esiste
$query_check_existence = "select table_name from user_tables where table_name=upper('$table_name')";
$b = new OraSql($a);
$b->Exec($query_check_existence);
while ($b->getRow()) {
	$db_table_name = $b->row['TABLE_NAME'];
}

if ($db_table_name != $table_name) {
	$query_create = "
	create table $table_name
	(
	  USERID VARCHAR2(32 CHAR) not null,
	  SSID   VARCHAR2(400) not null,
	  ATTIVO NUMBER not null,
	  REQ_DT DATE not null
	)
	";
	//echo $query_create;
//	echo "Eseguo query per creare la tabella $table_name<br />";

	$b = new OraSql($a);
	$b->Exec($query_create);
	$a->commit();
	$query_alter = "alter table $table_name
	  add constraint PK_USERID_FLAG primary key (USERID, SSID)
	";
	//echo $query_alter;
//	echo "Eseguo query per aggiugnere primary key alla tabella $table_name<br />";
	$b = new OraSql($a);
	$b->Exec($query_alter);
	$a->commit();
}
//END creazione tabella se non esiste


				$messages .= "<form action=\"\" method=\"post\" onsubmit=\"return check_passwords_forget();\"><br /><br /><br /><br />
								<input type=\"hidden\" name=\"changepwdsubmit\" value=\"true\"></input>				
								<table style=\"width:50%;\" align=\"center\">
									<tr>
										<td colspan=\"2\"><b>Proceed with change password.</b></td>
									</tr>
									<tr>
										<td width=\"200px\" align=\"right\">Username:</td>
										<td align=\"left\"><b>{$in['remote_userid']}</b></td>
									</tr>
										<td align=\"right\">New password:</td>
										<td><input name=\"new_password\" id=\"new_password\" type=\"password\" tabindex=\"2\" size=\"20\" onkeyup=\"testPassword_forget(this.value);\" /></td>
									</tr>
									<tr>
										<td align=\"right\">New password check:</td>
										<td><input name=\"new_password_check\" id=\"new_password_check\" type=\"password\" tabindex=\"3\" size=\"20\" /></td>
									</tr>
									<tr>
										<td colspan=\"2\"><div id=\"colorMe\">&nbsp;</div></td>
									<tr>
									<tr><td align=\"right\">&nbsp;</td>
										<td colspan=\"2\"><input type=\"submit\" value=\"Change\" name=\"cambia\" tabindex=\"4\" /></td>
									</tr>
								</table>
								<!--alertmsg-->
								</form><br />
								<h2>RULES:</h2>
								<ul>
								<li>The new password should contain <strong>at least a letter, a number, a special character</strong> and start with a letter.</li>
								<li>The new password must contain one of the special characters enabled: !\"$%&()*+,-./:;<=>?\^</li>
								<li>Moreover 'new password' should be free of consecutive identical characters or all-numeric or all-alphabetical groups.</li>
								</ul>
								<br />
								";


					$new_passwd = admin_md5_crypt(strtoupper($_POST['new_password']), $pass_db_salt);

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
					if( isset($_POST['changepwdsubmit'])){
						if ($_POST['new_password'] == $_POST['new_password_check'] && $_POST['new_password'] != "" && $_POST['new_password_check'] != "") {
							unset ($values);
							unset ($pk);
							$values['PASSWORD'] = $new_passwd;
							$values['DTTM_SCADENZAPWD'] = "sysdate+decode(SCADENZAPWD,'3',90,'8',90,180)";
							$pk['USERID'] = strtoupper($_SERVER['REMOTE_USER']);
							$b = new OraSql($a);
							$table = "UTENTI";
	//								print_r($values);
	//								print_r($pk);
							$b->Update($values, $table, $pk);
							$a->commit();
							unset ($values);
							unset ($pk);
							//salvare record in DB
							$pk['USERID'] = $userid;
							$pk['ATTIVO'] = 1;
							$values['USERID'] = $userid;
							$values['ATTIVO'] = 0;
							$tables = $table_name;
							$b = new OraSql($a);
							$b->Update($values, $tables, $pk);
							$a->commit();
	
							$messages = "<p><h1>Password succesfully changed</h1><a href=\"../../ShibLogOut\">Go to Login</a></p>";
							
						} elseif ($_POST['new_password'] != $_POST['new_password_check']) {
								$alertmsg = "The inserted password as \"new password\" does not match";
						} elseif ($_POST['new_password'] == "" ) {
								$alertmsg = "Insert new password";
						} elseif ($_POST['new_password_check'] == "") {
								$alertmsg = "Please insert the password check";
						}
					}
					if($alertmsg!=""){$alertmsg = "<br /><div style=\"text-align:center; border:2px solid red; padding:2px;\"><p>$alertmsg</p></div>";}
			

$remote_userid=substr($in['remote_userid'],0,3);


$template = file_get_contents("template.htm");
$template = str_replace("<!--infos-->", $infos, $template);
$template = str_replace("<!--mainmenu-->", $mainmenu, $template);
$template = str_replace("<!--filters-->", $filters, $template);
$template = str_replace("<!--mailboxes-->", $mailboxes, $template);
$template = str_replace("<!--messages-->", $messages, $template);
$template = str_replace("<!--message-->", $message, $template);
$template = str_replace("<!--SCRIPT-->", $script, $template);
$template = str_replace("<!--userid-->", $remote_userid, $template);
$template = str_replace("<!--alertmsg-->", $alertmsg, $template);

die($template);



function admin_md5_crypt($pwd, $salt = null) {
	global $admin_md5_crypt_chars;
	$magic = '$apr1$';

	if ($salt != null) {
		$salt = $salt;
	} else {
		$salt = $admin_md5_crypt_chars[rand(0, count($admin_md5_crypt_chars))] . $admin_md5_crypt_chars[rand(0, count($admin_md5_crypt_chars))] . $admin_md5_crypt_chars[rand(0, count($admin_md5_crypt_chars))] . ".....";
		#join ( '', map { $admin_md5_crypt_chars[ int rand @admin_md5_crypt_chars ] } ( 0 .. 2 ) )  . ("." x 5);
	}
	$md5 = md5($pwd . $salt . $pwd);
	$md5 = hex2raw($md5);

	$ctx = $pwd . $magic . $salt;
	for ($pl = strlen($pwd); $pl > 0; $pl -= 16) {
		$ctx .= substr($md5, 0, $pl > 16 ? 16 : $pl);
	}

	for ($i = strlen($pwd); $i; $i >>= 1) {
		if ($i & 1)
			$ctx .= pack("C", 0);
		else
			$ctx .= substr($pwd, 0, 1);
	}
	$ctx = md5($ctx);
	$ctx = hex2raw($ctx);
	$final_ctx1 = $ctx;
	for ($i = 0; $i < 1000; $i++) {
		$ctx1 = '';
		if ($i & 1) {
			$ctx1 .= $pwd;
		} else {
			$ctx1 .= substr($final_ctx1, 0, 16);
		}
		if ($i % 3) {
			$ctx1 .= $salt;
		}
		if ($i % 7) {
			$ctx1 .= $pwd;
		}
		if ($i & 1) {
			$ctx1 .= substr($final_ctx1, 0, 16);
		} else {
			$ctx1 .= $pwd;
		}
		$final_ctx1 = md5($ctx1);
		$final_ctx1 = hex2raw($final_ctx1);
	}
	$final = $final_ctx1;
	#echo "<hr>".$final."<hr>";
	$passwd = '';
	$unp = unpack("C", (substr($final, 0, 1)));
	$unp1 = unpack("C", (substr($final, 6, 1)));
	$unp2 = unpack("C", (substr($final, 12, 1)));
	$passwd .= admin_md5_crypt_to64(floor($unp[1] << 16) | floor($unp1[1] << 8) | floor($unp2[1]), 4);
	#print "<br>".$passwd;
	$unp = unpack("C", (substr($final, 1, 1)));
	$unp1 = unpack("C", (substr($final, 7, 1)));
	$unp2 = unpack("C", (substr($final, 13, 1)));
	$passwd .= admin_md5_crypt_to64(floor($unp[1] << 16) | floor($unp1[1] << 8) | floor($unp2[1]), 4);
	$unp = unpack("C", (substr($final, 2, 1)));
	$unp1 = unpack("C", (substr($final, 8, 1)));
	$unp2 = unpack("C", (substr($final, 14, 1)));
	$passwd .= admin_md5_crypt_to64(floor($unp[1] << 16) | floor($unp1[1] << 8) | floor($unp2[1]), 4);
	$unp = unpack("C", (substr($final, 3, 1)));
	$unp1 = unpack("C", (substr($final, 9, 1)));
	$unp2 = unpack("C", (substr($final, 15, 1)));
	$passwd .= admin_md5_crypt_to64(floor($unp[1] << 16) | floor($unp1[1] << 8) | floor($unp2[1]), 4);
	$unp = unpack("C", (substr($final, 4, 1)));
	$unp1 = unpack("C", (substr($final, 10, 1)));
	$unp2 = unpack("C", (substr($final, 5, 1)));
	$passwd .= admin_md5_crypt_to64(floor($unp[1] << 16) | floor($unp1[1] << 8) | floor($unp2[1]), 4);
	$unp = unpack("C", substr($final, 11, 1));
	$passwd .= admin_md5_crypt_to64(floor($unp[1]), 2);
	return $magic . $salt . '$' . $passwd;
}

function hex2raw($str) {
	$chunks = str_split_1($str, 2);
	for ($i = 0; $i < sizeof($chunks); $i++) {
		$op .= chr(hexdec($chunks[$i]));
	}
	return $op;
}

function genToken($len = 32, $md5 = true) {

	# Seed random number generator
	# Only needed for PHP versions prior to 4.2
	mt_srand((double) microtime() * 1000000);
	# Array of characters, adjust as desired
	# Array of characters, adjust as desired
	$chars = array (
		'Q',
		'@',
		'8',
		'y',
		'%',
		'^',
		'5',
		'Z',
		'(',
		'G',
		'_',
		'O',
		'`',
		'S',
		'-',
		'N',
		'<',
		'D',
		'{',
		'}',
		'[',
		']',
		'h',
		';',
		'W',
		'.',
		'/',
		'|',
		':',
		'1',
		'E',
		'L',
		'4',
		'&',
		'6',
		'7',
		'#',
		'9',
		'a',
		'A',
		'b',
		'B',
		'~',
		'C',
		'd',
		'>',
		'e',
		'2',
		'f',
		'P',
		'g',
		')',
		'?',
		'H',
		'i',
		'X',
		'U',
		'J',
		'k',
		'r',
		'l',
		'3',
		't',
		'M',
		'n',
		'=',
		'o',
		'+',
		'p',
		'F',
		'q',
		'!',
		'K',
		'R',
		's',
		'c',
		'm',
		'T',
		'v',
		'j',
		'u',
		'V',
		'w',
		',',
		'x',
		'I',
		'$',
		'Y',
		'z',
		'*'
	);
	# Array indice friendly number of chars; empty token string
	$numChars = count($chars) - 1;
	$token = '';
	# Create random token at the specified length
	for ($i = 0; $i < $len; $i++)
		$token .= $chars[mt_rand(0, $numChars)];
	# Should token be run through md5?
	if ($md5) {
		# Number of 32 char chunks
		$chunks = ceil(strlen($token) / 32);
		$md5token = '';
		# Run each chunk through md5
		for ($i = 1; $i <= $chunks; $i++)
			$md5token .= md5(substr($token, $i * 32 - 32, 32));
		# Trim the token
		$token = substr($md5token, 0, $len);
	}
	return $token;
}

function str_split_1($str, $nr) {
	//Return an array with 1 less item then the one we have
	return array_slice(explode("-l-", chunk_split($str, $nr, '-l-')), 0, -1);
}
function admin_md5_crypt_to64($v, $n) {
	global $admin_md5_crypt_chars;
	$ret = '';

	while (-- $n >= 0) {
		$ret .= $admin_md5_crypt_chars[$v & 0x3f];
		$v >>= 6;
	}
	return $ret;
}

?>




