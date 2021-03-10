<?php

ini_set('display_errors','1');
error_reporting(E_ERROR|E_PARSE);
//l'invio mail con la pass nuova
//hidden per assicurarsi l'identit� della POST

require_once 'DB/OraDBConnection.inc.php';
require_once 'DB/OraSql.inc.php';

$bcc="c.contino@cineca.it,a.ramenghi@cineca.it";
//require_once 'http_lib.inc.php';
if (isset($_POST['CWD'])) $_SERVER['DOCUMENT_ROOT']=$_POST['CWD'];
$a = new OraDBConnection();
//print_r($_SERVER['HTTP_REFERER']);
global $admin_md5_crypt_chars;
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
	if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/lost-password.conf.inc")){
		/** File personalizzato per il singolo servizio
		 * SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
		 */
		include_once("{$_SERVER['DOCUMENT_ROOT']}/lost-password.conf.inc");
	}

	else if(strtoupper($language) != strtoupper("en") && strtoupper($language) != strtoupper("it")){
		
		
			/** setto inglese, prendo i termini dal file di configurazione standard di libreria */
			$language = "en";
			include_once("/http/lib/IanusCas5Driver/LOGIN/lost-password.conf.inc");
		
	}
	else{
	/** Se il browsere è in italiano o in inglese , prendo i termini  dal file di configurazione standard di libreria 
	 * La language viene presa dalla $_SERVER['HTTP_ACCEPT_LANGUAGE']
	 */
		include_once("/http/lib/IanusCas5Driver/LOGIN/lost-password.conf.inc");
	}

$script = "<script type=\"text/javascript\">
function check_passwords_forget() {

	var expr_num = /[0-9]/;
	var expr_letter = /[a-zA-Z]/;
	var expr_char = /[\!\"$%&()*+,-./:;<=>?\^]/;
	var new_pass_check = document.getElementById('new_password_check').value;
	var new_pass = document.getElementById('new_password').value;

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
	if(new_pass.length<8) {
		alert(\"{$lost_pass['label']['Regola2'][$language]}\");
		return false;
	}
	if(!expr_num.test(new_pass)) { alert(\"{$lost_pass['label']['Regola5'][$language]}\"); return false; }
	if(!expr_letter.test(new_pass)) { alert(\"{$lost_pass['label']['Regola6'][$language]}\"); return false; }
	if(!expr_char.test(new_pass)) { alert(\"{$lost_pass['label']['Regola7'][$language]} !\\\"$%&()*+,-./:;<=>?\^\"); return false; }

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

	if(perc > 100) perc=100;
	document.getElementById(\"colorMe\").style.width = perc+\"%\";
	return intScore + \" \" + strVerdict;

}

</script>";

$invia_mail = 1;

$msg_errors = "
				<table class=\"input-tb\">
					<tr>
						<td style=\"height:70px;\"><!-- <img src=\"images/cineca-logo-box.gif\" /> --></td>
						<td></td>
					</tr>
					<tr>
						<td colspan=\"2\" style=\"text-align:left;font-weight:bold;font-size:16px;color:#e60000;\">{$lost_pass['label']['Errore richiesta sospesa'][$language]}.</td>
					</tr>
					<tr>
						<td colspan=\"2\" style=\"text-align:left;color:#e60000;\"><a href=\"/\" style=\"color:#0079bc;\">Go to Login</a></td>
					</tr>
				</table>
				<!-- Vecchia table
				<table>
					<tr>
						<td colspan=\"2\"><b>ERRORE</b></td>
					</tr>

					<tr>
						<td colspan=\"2\"><p>{$lost_pass['label']['Errore richiesta sospesa'][$language]}.</p></td>
					</tr>
				</table>
				-->";

//creazione tabella se non esiste
$query_check_existence = "select table_name from user_tables where table_name=upper('$table_name')";
$b = new OraSql($a);
//print_r($a);
$b->Exec($query_check_existence);

while ($b->getRow()) {
	$db_table_name = $b->row['TABLE_NAME'];
}

if ($db_table_name != $table_name) {
	$query_create = "
	create table $table_name
	(
	  USERID VARCHAR2(100) not null,
	  SSID   VARCHAR2(400) not null,
	  ATTIVO NUMBER not null,
	  REQ_DT DATE not null
	)
	";
	//echo $query_create;
	echo "Eseguo query per creare la tabella $table_name<br />";

	$b = new OraSql($a);
	$b->Exec($query_create);
	$a->commit();
	$query_alter = "alter table $table_name
	  add constraint PK_USERID_FLAG primary key (USERID, SSID)
	";
	//echo $query_alter;
	echo "Eseguo query per aggiugnere primary key alla tabella $table_name<br />";
	$b = new OraSql($a);
	$b->Exec($query_alter);
	$a->commit();
}
//END creazione tabella se non esiste

$message .= "<script>document.getElementById(\"left\").style.display= \"none\";</script>";
if (isset($_GET['passchanged'])){

	$messages .= "
	<table class=\"input-tb\">
		<tr>
			<td style=\"height:70px;\"><!-- <img src=\"images/cineca-logo-box.gif\" /> --></td>
			<td></td>
		</tr>
		<tr>
			<td colspan=\"2\" style=\"text-align:left;font-weight:bold;font-size:16px;color:#e60000;\">{$lost_pass['label']['Password cambiata'][$language]}.</td>
		</tr>
		<tr>
			<td colspan=\"2\" style=\"text-align:left;font-size:14px;color:#e60000;\"><a href=\"/\" style=\"color:#0079bc;\">Go to Home Page</a></td>
		</tr>
	</table>
	";
}
else{
//2 SECONDO LIVELLO DELL APPLICAZIONE, INVIA MAIL SE ESISTE USER
if ($_POST['procedi']) {
	$userid = strtoupper($_POST['userid']);
	$query = "select * from ana_utenti where USERID=:remote_user";
	//	echo $query;
	$bind['REMOTE_USER']=$userid;
	$b = new OraSql($a);
	$b->Exec($query,$bind);
	//	echo $b->row['EMAIL'];
	//	print_r($b->row['EMAIL']);
	while ($b->getRow()) {
		$email = $b->row['EMAIL'];
	}
	//	echo $email;
//	mail("e.gargano@cineca.it", "Forget pass: $email", "Forget pass: $email");

	$query = "select * from forget_pass where USERID=:remote_user";
	//echo $query;
	$bind['REMOTE_USER']=$userid;
	$b = new OraSql($a);
	$b->Exec($query,$bind);
	while ($b->getRow()) {
		$ssid = $b->row['SSID'];
		$flag = $b->row['ATTIVO'];
		//		$req_dt = $b->row['REQ_DT'];
	}

	if ($email == "") {
		$messages .= $msg_errors;
	} else {
		//generato identificativo univoco
		//phpsessid+date+random
		$date = date("Ymdhms");
		$rand = rand();
		///ERROR
		if ($_COOKIE['PHPSESSID'] == "logoutdone") {
			$begin_string = genToken();
		} else {
			$begin_string = $_COOKIE['PHPSESSID'];
		}
		$magic_string = $begin_string . "_" . $date . "_" . substr($rand, 0, 5);
		$magic_url = "<a href=\"http://{$_SERVER['SERVER_NAME']}/authzssl/forget_password/?CheckSID=" . $magic_string . "\">http://{$_SERVER['SERVER_NAME']}/authzssl/forget_password/?CheckSID=$magic_string</a>";
		require_once('/http/lib/php_utils/mail/send_email_common.inc');
		//send_mail("noreply@cineca.it", $email, $bcc, "{$lost_pass['label']['Testo mail change password'][$language]} $userid </b><br /> {$lost_pass['label']['fare clic sul seguente link'][$language]}:</b><br /> $magic_url</b><br /><br />{$lost_pass['label']['se il link non funziona'][$language]}", "{$lost_pass['label']['Oggetto mail'][$language]}");
		// modifica d.saraceno 22/03/2016

		send_email($email, "noreply@cineca.it", "noreply@cineca.it", "{$lost_pass['label']['Oggetto mail'][$language]}", "{$lost_pass['label']['Testo mail change password'][$language]} $userid </b><br /> {$lost_pass['label']['fare clic sul seguente link'][$language]}:</b><br /> $magic_url</b><br /><br />{$lost_pass['label']['se il link non funziona'][$language]}", null);

		

		$sql_delete="delete from $table_name where userid=:remote_user";
		$bind['REMOTE_USER']=$userid;
		$b = new OraSql($a);
		$b->Exec($sql_delete,$bind);
		$a->commit();
		//salvare record in DB
		$values['USERID'] = $userid;
		$values['ATTIVO'] = 1;
		$values['SSID'] = $magic_string;
		$values['REQ_DT'] = "sysdate";
		$tables = $table_name;
		$b = new OraSql($a);
		$b->Insert($values, $tables);
		$a->commit();

		$messages .= "
					<table class=\"input-tb\">
						<tr>
							<td style=\"height:70px;\"><!-- <img src=\"images/cineca-logo-box.gif\" /> --></td>
							<td></td>
						</tr>
						<tr>
							<td colspan=\"2\" style=\"text-align:left;font-weight:bold;font-size:16px;color:#e60000;\">{$lost_pass['label']['Email inviata con successo'][$language]}<br /> {$lost_pass['label']['Seguire le istruzioni'][$language]}.</td>
						</tr>
						<tr>
							<td colspan=\"2\" style=\"text-align:left;color:#e60000;\"><a href=\"/\" style=\"color:#0079bc;\">Go to Home Page</a></td>
						</tr>
					</table>
					";
	}

	//3 TERZO LIVELLO DELL APPLICAZIONE, L UTENTE ARRIVA DAL LINK NELLA MAIL
} else
	if ($_GET['CheckSID']) {
		//3.3 TERZO SOTTOLIVELLO DELL APPLICAZIONE, L UTENTE REINSERISCE USERID
		if ($_POST['ri-procedi']) {
			//CONTROLLARE UNIVOCO DENTRO DB, CON userid QUESTA
			$userid = strtoupper($_POST['userid']);
			$query = "select * from forget_pass where USERID=:remote_user";
			//echo $query;
			$bind['REMOTE_USER']=$userid;
			$b = new OraSql($a);
			$b->Exec($query,$bind);
			while ($b->getRow()) {
				$ssid = $b->row['SSID'];
				$flag = $b->row['ATTIVO'];
			}




			if ($ssid == $_GET['CheckSID']) {
				//arriva da questa form (id segreto)
				$messages .= "<form action=\"https://{$_SERVER['HTTP_HOST']}/authzssl/forget_password/?{$_SERVER['QUERY_STRING']}\" method=\"post\" onsubmit=\"return check_passwords_forget();\">
				<input type='hidden' name='CWD' value='{$_SERVER['DOCUMENT_ROOT']}'>
				<input type='hidden' name='HOST' value='{$_SERVER['HTTP_HOST']}'>
							<table class=\"input-tb\">
										<tr>
											<td style=\"height:70px;\"><!-- <img src=\"images/cineca-logo-box.gif\" /> --></td>
											<td></td>
										</tr>
										<!--tr>
											<td style=\"text-align:right;\"><label for=\"userid\" class=\"bold\">{$lost_pass['label']['Userid'][$language]}&nbsp;&raquo;</label></td>
											<td class=\"center\">
												<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
													<tr>
														<td class=\"textbox-sx-user\"></td>
														<td class=\"textbox-cx\"><input type=\"text\" class=\"textbox\" id=\"userid\" name=\"userid\"/></td>
														<td class=\"textbox-dx\"></td>
													</tr>
												</table>
											</td>
										</tr-->
										<tr>
											<td style=\"text-align:right;\"><label for=\"userid\" class=\"bold\">{$lost_pass['label']['New Password'][$language]}&nbsp;&raquo;</label></td>
											<td class=\"center\">
												<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
													<tr>
														<td id=\"SX_PASS\" class=\"textbox-sx-pass\"></td>
														<td id=\"CX_PASS\" class=\"textbox-cx\"><input type=\"password\" class=\"textbox\" id=\"new_password\" name=\"new_password\" onkeyup=\"testPassword_forget(this.value);\" /></td>
														<td id=\"DX_PASS\" class=\"textbox-dx\"></td>
													</tr>
												</table>
											</td>
										</tr>
										<tr>
											<td style=\"text-align:right;\"><label for=\"userid\" class=\"bold\">{$lost_pass['label']['Password Check'][$language]}&nbsp;&raquo;</label></td>
											<td class=\"center\">
												<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
													<tr>
														<td id=\"SX_PASS_C\" class=\"textbox-sx-pass\"></td>
														<td id=\"CX_PASS_C\" class=\"textbox-cx\"><input type=\"password\" class=\"textbox\" id=\"new_password_check\" name=\"new_password_check\"/></td>
														<td id=\"DX_PASS_C\" class=\"textbox-dx\"></td>
													</tr>
													<tr><td colspan=\"2\"><div style=\"margin-top:2px;height:2px;\" id=\"colorMe\">&nbsp;</div></td></tr>
												</table>
											</td>
										</tr>
										<tr>
											<td></td>
											<td colspan=\"2\" class=\"center\">
												<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
													<tr>
														<td id=\"TD-PASS-SX\" class=\"button-sx\"></td>
														<td id=\"TD-PASS-CX\" class=\"button-cx\">
															<input onmousedown=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark-down.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark-down.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark-down.gif');\" onmouseover=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark-hover.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark-hover.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark-hover.gif');\" onmouseout=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark.gif');\" type=\"submit\" id=\"Change\" name=\"Change\" class=\"button\" value=\"Change\"/>
														</td>
														<td id=\"TD-PASS-DX\" class=\"button-dx\"></td>
													</tr>
												</table>
											</td>
										</tr>
										<tr><td><br /><br /><br /></td><td></td></tr>
									</table>
								</form>
								<table style=\"margin-top:180px;\">
									<tr><td colspan=\"2\"><h2>{$lost_pass['label']['Regole'][$language]}</h2>
										<ul>
											<li>{$lost_pass['label']['Regola2'][$language]}</li>
											<li>{$lost_pass['label']['Regola3'][$language]}</li>
											<li>{$lost_pass['label']['Regola4'][$language]}</li>
										</ul></td></tr></table>
								";
			} else {
				$messages .= $msg_errors;
			}

		} else
			if ($_POST['Change']) {
				//3.2 SECONDO SOTTOLIVELLO DELL APPLICAZIONE, L UTENTE CAMBIA PASS
				//controlli ID segreto, cambiare pass solo se la data e minore di 7 giorni

				$query = "select * from forget_pass where SSID=:SID_CHECK";
				//echo $query;
				$bind['SID_CHECK']=$_GET['CheckSID'];
				$b = new OraSql($a);
				$b->Exec($query,$bind);
				while ($b->getRow()) {
					$userid = $b->row['USERID'];
					$flag = $b->row['ATTIVO'];
				}
				if ($userid != "") {
					$query = "select * from UTENTI where USERID=:remote_user";
					//		print_r( $db );
					$bind['REMOTE_USER']=$userid;
					$b = new OraSql($a);
					$b->Exec($query,$bind);
					while ($b->getRow()) {
						$old_pass_db = $b->row['PASSWORD'];

					}
					$bind_arno['NEW_PASSWORD']=admin_md5_crypt($_POST['new_password']);
					//Nuovo cas con password case sensitive - niente uppercase
					//$_POST['new_password']=strtoupper($_POST['new_password']);
					//$_POST['new_password_check']=strtoupper($_POST['new_password_check']);

					//$passwd=admin_md5_crypt(strtoupper($_POST['old_password']), $pass_db_salt);
					$bCryptedPass = password_hash($_POST['old_password'], PASSWORD_BCRYPT, array("cost" => 12));
					$bCryptedPass = str_replace('$2y$', '$2a$', $bCryptedPass);
					$passwd = $bCryptedPass;
					//$new_passwd = admin_md5_crypt($_POST['new_password']);
					$bCryptedPass = password_hash($_POST['new_password'], PASSWORD_BCRYPT, array("cost" => 12));
					$bCryptedPass = str_replace('$2y$', '$2a$', $bCryptedPass);
					$new_passwd=$bCryptedPass;


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
					if ($_POST['new_password'] == $_POST['new_password_check'] && $_POST['new_password'] != "" && $_POST['new_password_check'] != "") {
						//aggiungere sso
						$sql=new OraSql($a);
						$sql_sso="select username from CAS_USERS where upper(userid)=:remote_userid";
						unset($bind);
						$bind['REMOTE_USERID']=$userid;
						$sql->Exec($sql_sso,$bind);
						if ($sql->getRow()){
							$sso_user=true;
						}

						if(!$sso_user){
							unset ($values);
							unset ($pk);
							$values['PASSWORD'] = $new_passwd;
							//$values['DTTM_SCADENZAPWD'] = "sysdate+90";
							$pk['USERID']=$userid;
							$b = new OraSql($a);
							$table = "UTENTI";
							
							$b->Update($values, $table, $pk);
							$a->commit();
								
						}
						else{
							unset ($values);
							unset ($pk);
							$values['PASSWORD'] = $new_passwd;
							//$values['DTTM_SCADENZAPWD'] = "sysdate+90";
							$pk['USERID']=$userid;
							$b = new OraSql($a);
							$table = "CAS_USERS";
								
							$b->Update($values, $table, $pk);
							$a->commit();
												
						}
						if(preg_match("/arno-bundle-01/i",$_SERVER['DOCUMENT_ROOT'])){
							$str_arno="UPDATE autenticazione_utente
							SET
							password = :new_password,
							abilitato = 1,
							old_password1 = '',
							old_password2 = '',
							old_password3 = '',
							old_password4 = '',
							scadenza_password = sysdate+90,
							password_recover_random = NULL,
							password_recover_date = NULL
							WHERE nome_utente = :utente AND abilitato!=0";
							
							$bind_arno['UTENTE']=$userid;
							
							$sql_arno=new DriverIanusSql($DriverIanusConnection);
							$sql_arno->Exec($str_arno,$bind_arno);
						}
							$location="http://";
							$location.=$_POST['HOST'];
							$location.="/authzssl/forget_password/?passchanged";
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

						header("location:$location");
						die();

					} else
						if ($_POST['new_password'] != $_POST['new_password_check']) {
							$messages .= "<p>{$lost_pass['label']['Password non coincidono'][$language]}</p>";
						} else
							if ($_POST['new_password'] == "") {
								$messages .= "<p>{$lost_pass['label']['Inserire la nuova password'][$language]}</p>";
							} else
								if ($_POST['new_password_check'] == "") {
									$messages .= "<p>{$lost_pass['label']['Inserire la nuova password di controllo'][$language]}</p>";
								}
				
				}

			} else {
				//3.1 PRIMO SOTTOLIVELLO DELL APPLICAZIONE, L UTENTE REINSERISCE USERID
				$messages .= "<form action=\"\" method=\"post\"><br /><br /><br /><br />
						<div style=\"font-weight:bold;color:#fff;\"><span style=\"color:#0079bc;\">&#9632;</span> {$lost_pass['label']['Re-inserire lo Userid'][$language]}</div>
						<table class=\"input-tb\">
							<tr>
								<td style=\"text-align:right;\"><label for=\"userid\" class=\"bold\">Userid&nbsp;&raquo;</label></td>
								<td class=\"center\">
									<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
										<tr>
											<td class=\"textbox-sx-user\"></td>
											<td class=\"textbox-cx\"><input type=\"text\" class=\"textbox\" id=\"userid\" name=\"userid\"/></td>
											<td class=\"textbox-dx\"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td></td>
								<td colspan=\"2\" class=\"center\">
									<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
										<tr>
											<td id=\"TD-PASS-SX\" class=\"button-sx\"></td>
											<td id=\"TD-PASS-CX\" class=\"button-cx\">
												<input onmousedown=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark-down.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark-down.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark-down.gif');\" onmouseover=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark-hover.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark-hover.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark-hover.gif');\" onmouseout=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark.gif');\" type=\"submit\" id=\"ri-procedi\" name=\"ri-procedi\" class=\"button\" value=\"{$lost_pass['label']['Procedi'][$language]}\"/>
											</td>
											<td id=\"TD-PASS-DX\" class=\"button-dx\"></td>
										</tr>
									</table>
								</td>
							</tr>
						</table>

						<!-- Vecchia table

						<table style=\"width:50%;\" align=\"center\">" .
							"<div>{$lost_pass['label']['Re-inserire lo Userid'][$language]}:</div>
							<tr>
								<td align=\"right\">Userid:</td>
								<td><input name=\"userid\" id=\"userid\" type=\"text\" tabindex=\"1\" size=\"20\" /></td>
							</tr>
							<tr><td align=\"right\">&nbsp;</td>
								<td colspan=\"2\"><input type=\"submit\" value=\"{$lost_pass['label']['Procedi'][$language]}\" name=\"ri-procedi\" tabindex=\"4\" /></td>
							</tr>
						</table>

						-->
						</form>";
			}

	} else {
		//1 PRIMO LIVELLO DELL APPLICAZIONE, inserisci user e invia richiesta
		$messages .= "<form action=\"\" method=\"post\">
			<table class=\"input-tb\">
				<tr>
					<td style=\"height:70px;\"><!-- <img src=\"images/cineca-logo-box.gif\" /> --></td>
					<td></td>
				</tr>
				<tr>
					<td style=\"text-align:right;\"><label for=\"userid\" class=\"bold\">{$lost_pass['label']['Userid'][$language]}&nbsp;&raquo;</label></td>
					<td class=\"center\">
						<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
							<tr>
								<td class=\"textbox-sx-user\"></td>
								<td class=\"textbox-cx\"><input type=\"text\" class=\"textbox\" id=\"userid\" name=\"userid\"/></td>
								<td class=\"textbox-dx\"></td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td></td>
					<td colspan=\"2\" class=\"center\">
						<table style=\"margin:0 auto;\" cellpadding=\"0\" cellspacing=\"0\">
							<tr>
								<td id=\"TD-PASS-SX\" class=\"button-sx\"></td>
								<td id=\"TD-PASS-CX\" class=\"button-cx\">
									<input onmousedown=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark-down.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark-down.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark-down.gif');\" onmouseover=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark-hover.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark-hover.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark-hover.gif');\" onmouseout=\"change_img('TD-PASS-SX', '../LOGIN/images/button-sx-dark.gif');change_img('TD-PASS-CX', '../LOGIN/images/button-cx-dark.gif');change_img('TD-PASS-DX', '../LOGIN/images/button-dx-dark.gif');\" type=\"submit\" id=\"procedi\" name=\"procedi\" class=\"button\" value=\"{$lost_pass['label']['Procedi'][$language]}\"/>
								</td>
								<td id=\"TD-PASS-DX\" class=\"button-dx\"></td>
							</tr>
						</table>
					</td>
				</tr>
				<tr><td colspan=\"2\" style=\"text-align:left;\">&nbsp;&nbsp;&nbsp;<a href=\"../forget_userid/forget_userid.php\" style=\"color:#0079bc;\">{$lost_pass['label']['Lost Userid'][$language]}</a></td></tr>
			</table>
		<!-- Vecchia table
		<table style=\"width:50%;\" align=\"center\">
			<tr>
				<td align=\"right\">{$lost_pass['label']['Userid'][$language]}:</td>
				<td><input name=\"userid\" id=\"userid\" type=\"text\" tabindex=\"1\" size=\"20\" /></td>
			</tr>
			<tr><td align=\"right\">&nbsp;</td>
				<td colspan=\"2\"><input type=\"submit\" value=\"{$lost_pass['label']['Procedi'][$language]}\" name=\"procedi\" tabindex=\"4\" /></td>
			</tr>
		</table>" .
				"<table><tr><a href=\"../forget_userid/forget_userid.php\">{$lost_pass['label']['Lost Userid'][$language]}</a></tr></table>
		-->
		</form>
		";
	}
}

/* GESTIRE PERSONALIZZAZIONE */
if (file_exists("{$_SERVER['DOCUMENT_ROOT']}/authzssl/forget_password.html")){
	$template = file_get_contents("{$_SERVER['DOCUMENT_ROOT']}/authzssl/forget_password.html");
}else{
	$template = file_get_contents("/http/lib/IanusCas5Driver/LOGIN/template/forget_password.html");
}
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
$idp=explode("\.", $idp);
$idp=strtoupper($idp[0]);
if (isset($forceTemplate[$idp][$id_servizio])) 
$template = file_get_contents("/http/lib/IanusCas5Driver/LOGIN/template/".$forceTemplate[$idp][$id_servizio]);
*/


//$template = str_replace("<!--infos-->", $infos, $template);
$template = str_replace("<!-- mainmenu -->", $mainmenu, $template);
$template = str_replace("<!-- filters -->", $filters, $template);
$template = str_replace("<!-- mailboxes -->", $mailboxes, $template);
$template = str_replace("<!-- messages -->", $messages, $template);
$template = str_replace("<!-- message -->", $message, $template);
$template = str_replace("<!-- SCRIPT -->", $script, $template);
$template = preg_replace("/<!-- titolo -->/i", $lost_pass['label']['titolo'], $template);
$template = preg_replace("/<!-- action -->/i", "", $template);
$template = preg_replace("/<!-- userid -->/i", $lost_pass['label']['userid'][$language], $template);
$template = preg_replace("/<!-- siss -->/i", $lost_pass['label']['siss'][$language], $template);
$template = preg_replace("/<!-- reserved -->/i", $lost_pass['label']['reserved'][$language], $template);
$template = preg_replace("/<!-- proceed-button -->/i", $lost_pass['label']['proceed-button'][$language], $template);
$template = preg_replace("/<!-- lost-userid -->/i", $lost_pass['label']['lost-userid'][$language], $template);
$template = preg_replace("/<!-- script -->/i", $script, $template);
$template = preg_replace("/<!-- messages -->/i", $messages, $template);
die($template);

function send_mail($from, $to, $bcc, $testo, $subject) {
	$eol = PHP_EOL;
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

function error_page($user, $error, $error_spec) {

	$service = strtoupper(substr($_SERVER['HTTP_HOST'], 0, strpos($_SERVER['HTTP_HOST'], ".")));
	$email_admin = "e.gargano@cineca.it";
	$filetxt = file_get_contents("template.htm");
	$debug_info = debug_backtrace();
	$debug_info_str = "PHP DEBUG INFO:" . var_export($debug_info, true) . "END PHP DEBUG INFO";
	#echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
	$today = date("j/m/Y, H:m:s");
	$ajax = isset ($in['ajax_call']) ? "S�" : "No";

	if (is_array($error_spec))
		foreach ($error_spec as $key => $val)
			$spec .= "\n $key : $val";
	else
		$spec = $error_spec;

	$debug_info_str = "<br>" . $debug_info_str;
	$debug_info_str = preg_replace("[\n]", "<br>", $debug_info_str);
	$debug_info_str = preg_replace("/array/i", "<b>Array:</b>", $debug_info_str);
	$debug_info_str = preg_replace("/([0-9]) =>/", "<b> \\1 => </b>", $debug_info_str);

	$alltxt = "<table width=80% border=1>
					<tr><td style=\"margin:10px; padding:10px;\">Data: <b>$today</b></td></tr>
					<tr><td style=\"margin:10px; padding:10px;\">Errore: <b>$error</b></td></tr>
					<tr><td style=\"margin:10px; padding:10px;\">IP richiesta: <b>{$_SERVER['REMOTE_ADDR']}</b></td></tr>
					<tr><td style=\"margin:10px; padding:10px;\">URL richiesta: <b>{$_SERVER['REQUEST_URI']}</b></td></tr>
					<tr><td style=\"margin:10px; padding:10px;\">Servizio: <b>$service</b></td></tr>
					<tr><td style=\"margin:10px; padding:10px;\">Specifiche errore: <b>$spec</b></td></tr>
					<tr><td style=\"margin:10px; padding:10px;\">Chiamata ajax: <b style=\"color: red;\">$ajax</b></td></tr>
					<tr><td style=\"margin:10px; padding:10px;\">DEBUG INFO: <code>" . $debug_info_str . ".</code></td></tr>
				</table>";

	$headers = "From: ERROR_" . $service . "@{$_SERVER['SERVER_NAME']}\r\n";
	$headers .= "Content-type: text/html\r\n";

	mail($email_admin, "Errore[" . $user . "]", $alltxt, $headers);

	$body = "<p align=center><b style=\"font-size:16px; color:red;\">Si &egrave; verificato un errore: </b></p><br><br>
		<b style=\"font-size:18px;\">$error</b>";
	$filetxt = preg_replace("/<!--messages-->/", $body, $filetxt);
	die($filetxt);
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

function hex2raw($str) {
	$chunks = str_split_1($str, 2);
	for ($i = 0; $i < sizeof($chunks); $i++) {
		$op .= chr(hexdec($chunks[$i]));
	}
	return $op;
}

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
