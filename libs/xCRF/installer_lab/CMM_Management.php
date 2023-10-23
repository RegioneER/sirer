<?php

require_once "/http/lib/php_utils/smarty/Smarty.class.php";
require_once "/http/lib/XMR/hyperlibs/libs/ErrorPage.v2.inc";

// Costruisco per bene la tabella CMM_CENTER e CMM_USERS
$cmm_s_cols = array (
		'userid' => 'VARCHAR2(20)',
		'moddt' => 'DATE',
		'modprog' => 'NUMBER(6) not null',
		'fl_query' => 'CHAR(1) not null',
		'id_query' => 'NUMBER(6)',
);

$cmm_center_cols = array (
		'ID_CENTER' => 'NUMBER not null',
		'CODE' => 'VARCHAR2(20)',
		'NAME' => 'VARCHAR2(255)',
		'PI' => 'VARCHAR2(255)',
		'ADDRESS' => 'VARCHAR2(255)',
		'COUNTRY' => 'NUMBER',
		'D_COUNTRY' => 'VARCHAR2(255)',
		'PHONE' => 'VARCHAR2(255)',
		'FAX' => 'VARCHAR2(255)',
		'GENURS' => 'VARCHAR2(255)',
		'STATUS' => 'NUMBER',
		'D_STATUS' => 'VARCHAR2(20)',
		'ALL_USER_DISABLED_MAIL_SENT'=> 'NUMBER',
);

$cmm_center_s_cols = array_merge($cmm_s_cols, $cmm_center_cols);

$cmm_users_cols = array (
		'CMM_USERID' => 'VARCHAR2(32 CHAR)',
		'ROLE' => 'NUMBER',
		'D_ROLE' => 'VARCHAR2(50)',
		'CODE' => 'VARCHAR2(20)',
		'NAME' => 'VARCHAR2(255)',
		'SURNAME' => 'VARCHAR2(255)',
		'EMAIL' => 'VARCHAR2(255)',
		'PHONE' => 'VARCHAR2(255)',
		'FAX' => 'VARCHAR2(255)',
		'ADDRESS' => 'VARCHAR2(255)',
		'CREATEDT' => 'DATE',
		'FSTACCDT' => 'DATE',
		'LSTACCDT' => 'DATE',
		'EXPDT' => 'DATE',
		'ENDDT' => 'DATE',
		'STATUS' => 'NUMBER',
		'D_STATUS' => 'VARCHAR2(20)',
		'SIGN' => 'NUMBER',
		'D_SIGN' => 'VARCHAR2(20)',
		'SIGNSAE' => 'NUMBER',
		'D_SIGNSAE' => 'VARCHAR2(20)',
		'GENURS' => 'VARCHAR2(255)',
		'FIRST_PASSWORD' => 'VARCHAR2(32)',
		'MAIL_SENT' => 'CHAR(1)',
);

$cmm_users_s_cols = array_merge($cmm_s_cols, $cmm_users_cols);

$cmm_language_cols = array (
		'CENTER' => 'VARCHAR2(20) NOT NULL',
		'LANGUAGE' => 'VARCHAR2(12) NOT NULL',
		'D_LANGUAGE' => 'VARCHAR2(200)',
);

$firma_utenti_centri_cols = array (
		'USERNAME' => 'VARCHAR2(20) NOT NULL',
		'CENTER' => 'VARCHAR2(20) NOT NULL',
		'USER_ROLE' => 'VARCHAR2(200)',
);

$study_language_cols = array (
		'LANGUAGE' => 'VARCHAR2(3) NOT NULL',
		'D_LANGUAGE' => 'VARCHAR2(200) NOT NULL',
);

$cmm_center_sequence_name = "CMM_CENTER_SEQUENCE";
$mandatory_field_message = "This field is mandatory.</br>(Max 100 characters allowed)";
$only_number_field_message = "Only number are allowed for this field.</br>(Max 50 characters allowed)";
$max_lenght_fields_message = "Max 100 characters allowed";
$email_field_message = "Insert a valid email address.</br>(Max 100 characters allowed)";
$confirm_center_change_status_message = "You about to change the status of the center \"##CENTER_CODE##\"";
$confirm_center_disable_message = "<br/>(Disabling this center will disable all its users)";
$confirm_center_change_status_question = "<br/>Are you sure?";
$confirm_center_change_status_yes_label = "Yes";
$confirm_center_change_status_no_label = "No";
$connectivity_fail_label = "Session expired. Please log in again.";
$user_creation_info_label = "The user has been created.<br />Please disable (if enabled) pop-up blocking to print the user information form.";
$popup_block_info_label = "Please disable pop-up blocking to print the user information form.";
$user_confirm_disable_label = "Are you sure to disable the selected user?";
$icon_file = array (
		"edit" => "libs/images/icon_edit_18x18.png",
		"new" => "libs/images/icon_cd_new_18x18.png",
		"save" => "libs/images/icon_save_18x18.png",
		"delete" => "libs/images/icon_remove_18x18.png",
		"undo" => "libs/images/icon_left_18x18.png",
		"explore" => "libs/images/icon_explore_18x18.png",
		"loading" => "libs/images/waiting_animatedCircle.gif",
		"save_forbidden" => "libs/images/icon_save_forbidden_18x18.png",
		"up" => "libs/images/icon_up_18x18.png",
		"edit_forbidden" => "libs/images/icon_edit_forbidden_18x18.png",
		"edit_languages" => "libs/images/icon_languages_18x18.png",
		"edit_languages_forbidden" => "libs/images/icon_languages_forbidden_18x18.png",
		"info" => "libs/images/icon_info_18x18.png",
		"sent_mail" => "libs/images/icon_sent_mail_18x18.jpg",
		"ok" => "libs/images/icon_ok_18x18.png",
);


$user_roles = array(
		'11' => 'Site Staff',
		'12' => 'Principal Investigator',
		'13' => 'Sub-Investigator',
		'6' => 'CRA',
		'7' => 'Data Manager',
		'5' => 'Sponsor',
		'1' => 'Project Manager',
);


function hasRangeSubStudy()
{
	return is_dir("../rangexmr");
}

function getCRACenters($userid = null) {
	global $conn;

	if ($userid == null) {
		$userid = $_SERVER['REMOTE_USER'];
	}
	$getcracenter_query_sql = "SELECT CENTER FROM CRA_CENTER WHERE USERID_CRA=:USERID_CRA";
	$vals = array();
	$vals['USERID_CRA'] = $userid;
	$getcracenter_query = new query($conn);
	$getcracenter_query->exec($getcracenter_query_sql, $vals);
	$cracenters = array();
	while ($getcracenter_query->get_row()) {
		$cracenters[] = $getcracenter_query->row['CENTER'];
	}

	return $cracenters;
}

function generatePassword($length=8, $strength=8) {
	$vowels = "AEUY";
	$consonants = 'BDGHJLMNPQRSTVWXZ';
	$numbers = '1234567890';
	$special_chars= '@$%!'; //09/04/2013 - Rimosso ( e ) per problemi con Shibboleth //11/04/2013 rimosso anche # vmazzeo

	$password = '';
	for ($i = 0; $i < $length; $i++) {
		$alt = mt_rand(0, 3);
		switch($alt) {
			case 0:
				$password .= $consonants[(rand() % strlen($consonants))];
				break;
			case 1:
				$password .= $vowels[(rand() % strlen($vowels))];
				break;
			case 2:
				$password .= $numbers[(rand() % strlen($numbers))];
				break;
			case 3:
				$password .= $special_chars[(rand() % strlen($special_chars))];
				break;
		}
	}
	return $password;
}

function allineaSEQ($conn, $study_name) {
	global $cmm_center_sequence_name;
	// A seconda dell'ambiente faccio partire la sequence da valori differenzi
	$seq_start_value = "1";
	if (preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])) {
		// Dev
		$seq_start_value = "1";
	} elseif (preg_match("/\.test\./i",$_SERVER['HTTP_HOST']) || $in['CENTER'] == '599') {
		// 			Test
		$seq_start_value = "1";
	} elseif (preg_match("/-preprod\./i",$_SERVER['HTTP_HOST'])) {
		// 			PreProd
		$seq_start_value = "501";
	} else {
		// Prod
		$seq_start_value = "1";
	}
	$query = new query ( $conn );
	// Controllo se la tabella esiste
	$query_check_existence = "SELECT COUNT(*) AS CONTO FROM ALL_SEQUENCES
			WHERE SEQUENCE_OWNER LIKE '".strtoupper($study_name)."%' AND SEQUENCE_NAME='{$cmm_center_sequence_name}'";
	$query->set_sql ( $query_check_existence );
	$query->exec();
	$query->get_row();
	if ($query->row['CONTO'] == 0) {
		$query_create =
				"CREATE SEQUENCE {$cmm_center_sequence_name}
				 MINVALUE 1
				 START WITH {$seq_start_value}
                 INCREMENT BY 1
                 NOCACHE";
		$sql = new query ( $conn );
		$sql->set_sql ( $query_create );
		$sql->ins_upd ();
	}
}

function allineaDB($conn, $mytable, $mytable_cols, $mytable_costraint = '') {
	$query = new query ( $conn );
	// Controllo se la tabella esiste
	$query_check_existence = "SELECT COUNT(*) C FROM USER_TAB_COLUMNS WHERE TABLE_NAME='".$mytable."'";
	$query->set_sql ( $query_check_existence );
	$query->exec();
	$query->get_row();
	if ($query->row['C'] > 0) {
		// La tabella esiste ALTER
		$query_check_existence = "SELECT COLUMN_NAME FROM USER_TAB_COLUMNS WHERE TABLE_NAME='".$mytable."'";
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		while ( $query->get_row () ) {
			$tb_vals [$query->row ['COLUMN_NAME']] = $query->row ['COLUMN_NAME'];
		}
		foreach ( $mytable_cols as $key => $val ) {
			if (! in_array ( $key, $tb_vals )) {
				$alter_sessions_table = "ALTER TABLE ".$mytable." ADD $key $val";
				$query->set_sql ( $alter_sessions_table );
				$query->exec ();
			}
		}
		if ($mytable_costraint != '') {
			$sql = new query ( $conn );
			$sql->set_sql ( $mytable_costraint );
			$sql->exec ();
		}
	} else {
		// La tabella non esiste CREATE
		$query_create .= "
			create table ".$mytable."
				(
			";
		foreach ( $mytable_cols as $key => $val ) {
			$query_create .= $key." ".$val;
			if ($key != array_pop(array_keys($mytable_cols))) {
				$query_create .= ",";
			}
			$query_create .= "
				";
		}
		$query_create .= ")";
		$sql = new query ( $conn );
		$sql->set_sql ( $query_create );
		$sql->ins_upd ();

		if ($mytable_costraint != '') {
			$sql = new query ( $conn );
			$sql->set_sql ( $mytable_costraint );
			$sql->exec ();
		}
	}
}

function copiaInStoricoDB($conn, $mytable, $table_cols, $pk_field, $pk, $doCommit = false) {
	$sql_storico = "insert into S_{$mytable}
		select '{$_SERVER['REMOTE_USER']}', sysdate, storico_id.nextval, 'V','', ";
	foreach ($table_cols as $key => $value)
	{
		$sql_storico .= "o.".$key;
		if ($key != array_pop(array_keys($table_cols))) {
			$sql_storico .= ", ";
		}
	}
	$sql_storico .= " from {$mytable} o where o.{$pk_field} LIKE '{$pk}'";

	$sql = new query ( $conn );
	$sql->set_sql ( $sql_storico );
	$sql->ins_upd ();
	if ($doCommit) {
		$conn->commit();
	}
	return $sql->get_sql();
}

function getLanguages() {
	global $conn;
	global $study_prefix;

	$sql_languages = "SELECT * FROM {$study_prefix}_LANGUAGES";
	$sql = new query ($conn);
	$sql->exec($sql_languages);
	$return_value = array();
	while($sql->get_row()) {
		$return_value[$sql->row['LANGUAGE']] = $sql->row['D_LANGUAGE'];
	}
	return $return_value;
}

function sanitizeInput($array_var) {
	global $lang_array;
	global $cmm_center_cols;
	global $cmm_users_cols;

	$return_value = array();
	foreach ($array_var as $array_var_key => $array_var_value) {
		$array_of_possible_keys = array_merge($cmm_center_cols, $cmm_users_cols,
		array("ACTION" => "ACTION"), $lang_array);
		foreach ($array_of_possible_keys as $cmm_keys => $cmm_values) {
			if  ($array_var_key == "ACTION") {
				// Nel caso ho ACTION ritorno tutto senza cambiare niente
				return $array_var;
			} elseif ((preg_match("/[0-9]+_".$cmm_keys."$/", $array_var_key)
			|| preg_match("/[NEWUSER|NEWCENTER]_".$cmm_keys."$/", $array_var_key))
			&& (stristr($array_var_key, "input") || stristr($array_var_key, "select") || stristr($array_var_key, "check"))
			&& !stristr($array_var_key, "prev_")/* && $array_var_value != '' elimina le variabili nulle*/) {
					
				$return_value[$cmm_keys] = $array_var_value;
			} elseif (preg_match("/checkboxlang_".$cmm_keys."/i", $array_var_key)) {
				$return_value[$cmm_keys] = $cmm_keys;
			}
		}
	}

	return $return_value;
}
function checkArrayValues($array_var) {
	global $lang_array;

	$generic_error = false;
	$error_message = "";

	if (!isset($array_var["ACTION"])) {
		// Se non c'e' action esco
		$generic_error = true;
		$error_message = 'No $POST variables';
	} else if (preg_match("/connectivity_check/i", $array_var["ACTION"])) {
		// Check di connessione, non faccio niente
			
	} else if (preg_match("/send_user_info/i", $array_var["ACTION"])) {
		// Check di connessione, non faccio niente
		if (!isset($array_var["CMM_USERID"])) {
			$generic_error = true;
			$error_message = 'No \'CMM_USERID\' variables';
		}
	} else if (preg_match("/get_user_info/i", $array_var["ACTION"])) {
		// Check di connessione, non faccio niente
		if (!isset($array_var["CMM_USERID"])) {
			$generic_error = true;
			$error_message = 'No \'CMM_USERID\' variables';
		}
	} else if (preg_match("/pagination/i", $array_var["ACTION"])) {
		// Paginazione
		if (!isset($array_var["from"]) || !isset($array_var["to"])) {
			$generic_error = true;
			$error_message = 'No \'from\' or \'to\' variables';
		}
	} else if (preg_match("/center/i", $array_var["ACTION"])) {
		// Se e' un centro
		if (!isset($array_var["ID_CENTER"])) {
			// Se non c'e' un centro
			$generic_error = true;
			$error_message = 'No $POST[\'ID_CENTER\'] variables';
		} else if (!(isAdmin() || isPM() ||
		(intval(substr($_SERVER["REMOTE_USER"], 0, 3)) == $array_var["ID_CENTER"]) ||
		(isCRA() && in_array($array_var["ID_CENTER"], getCRACenters())))) {
			// Se non si e' admin o PM o CRA e il centro è associato al CRA o non si tenta di modificare un centro non autorizzato
			$generic_error = true;
			$error_message = 'Only Admin can modifiy this center';
		} elseif(preg_match("/get_language_center/i", $array_var["ACTION"])) {
			// Se prendo i languages associati, controllo che sia specificato l'ID_CENTER
			if (!isset($array_var["ID_CENTER"])) {
				// Se non c'e' un centro
				$generic_error = true;
				$error_message = 'No $POST[\'ID_CENTER\'] variables';
			}
		} elseif(preg_match("/update_language_center/i", $array_var["ACTION"])) {
			// Se modifico i languages associati, controllo che ce ne sia almeno uno da abilitare
			$lang_found = false;
			//Logger::info($array_var);
			foreach ($array_var as $single_lang_key => $single_lang_value) {
				if (array_key_exists($single_lang_key, $lang_array)) {
					$lang_found = true;
					break;
				}
			}
			if (!$lang_found) {
				$generic_error = true;
				$error_message = 'The center should have at least one language selected';
			}
			if (!isset($array_var["ID_CENTER"])) {
				// Se non c'e' un centro
				$generic_error = true;
				$error_message = 'No $POST[\'ID_CENTER\'] variables';
			}
		}
	} else if (preg_match("/user/i", $array_var["ACTION"])) {
		// Se e' un utente
		if (!isset($array_var["CMM_USERID"])) {
			// Se non c'e' un utente
			$generic_error = true;
			$error_message = 'No $POST[\'CMM_USERID\'] variables';
		} elseif (!(isAdmin() || isPM() || (isCRA() && in_array($array_var["ID_CENTER"], getCRACenters())) ||
		(intval(substr($array_var["CMM_USERID"], 0, 3)) == $array_var["ID_CENTER"]) ||
		(($array_var["CMM_USERID"] == "NEWUSER") && (intval(substr($_SERVER["REMOTE_USER"], 0, 3)) == $array_var["ID_CENTER"])))) {
			// Se non si e' admin o PM o CRA e il centro è associato al CRA o l'utente che si tenta di modificare non appartiene al centro passato
			// o al centro non autorizzato
			$generic_error = true;
			$error_message = 'Cannot update this users';
		} elseif (!(((isAdmin() || isPM()) && intval($array_var["ROLE"]) < 10) || intval($array_var["ROLE"]) >= 10 )) {
			// Se non si e' admin o PM non si posso inserire utenti non investigator del centro
			$generic_error = true;
			$error_message = 'Cannot insert user different from investigator';
		} elseif(!isEnabledUser($array_var["CMM_USERID"]) && !preg_match("/insert/i", $array_var['ACTION'])) {
			// Se l'utente era precedentemente disabilitato, non è possibile più modificarlo
			$generic_error = true;
			$error_message = 'Cannot update a disabled user';
		} elseif (intval($array_var["ROLE"]) < 10 && ($array_var["SIGN"] == "1" || $array_var["SIGNSAE"] == "1")) {
			// Se l'utente è un'utenza globale non ha permesso di firma
			$generic_error = true;
			$error_message = 'Global user cannot sign eCRF or eSAE';
		} elseif (intval($array_var["ROLE"]) == 11 && ($array_var["SIGN"] == "1" || $array_var["SIGNSAE"] == "1")) {
			// Se l'utente è Site Staff non ha permesso di firma
			$generic_error = true;
			$error_message = 'Site Staff user cannot sign eCRF or eSAE';
		} elseif (intval($array_var["ROLE"]) == 13 && $array_var["SIGN"] == "1") {
			// Se l'utente è Sub-Investigator non ha permesso di firma dell'eCRF
			$generic_error = true;
			$error_message = 'Sub-Investigator user cannot sign eCRF';
		}
	}

	if ($generic_error) {
		// Errore
		echo json_encode(array("sstatus" => "ko", "user" => $_SERVER['REMOTE_USER'], "error" => $error_message, "detail" => ""));
		die();
	}
}

function isEnabledCenter($center_id) {
	global $conn;

	if ($center_id == "NEWCENTER") {
		// Se è un nuovo centro
		if (isAdmin() || isPM()) {
			// Se sono admin o pm posso inserire
			return true;
		} else {
			// Altrimenti non posso inserire
			return false;
		}
	}
	$vals = array();
	$query_center_list_query = "SELECT * FROM CMM_CENTER WHERE ID_CENTER=:ID_CENTER";
	$vals["ID_CENTER"] = $center_id;
	// 		Logger::info($query_center_list_query);
	// 		Logger::info($vals);
	$query_center_list=new query($conn);
	$query_center_list->exec($query_center_list_query, $vals);
	$query_center_list->get_row();
	if ($query_center_list->numrows > 0) {
		return ($query_center_list->row["STATUS"] == 1);
	} else {
		return false;
	}
}

function isEnabledUser($user_id) {
	global $conn;

	$vals = array();
	$query_user_list_query = "SELECT * FROM CMM_USERS WHERE CMM_USERID=:CMM_USERID";
	$vals["CMM_USERID"] = $user_id;
	//		Logger::info($query_center_list_query);
	//		Logger::info($vals);
	$query_user_list=new query($conn);
	$query_user_list->exec($query_user_list_query, $vals);
	$query_user_list->get_row();
	if ($query_user_list->numrows > 0) {
		return ($query_user_list->row["STATUS"] == 1);
	} else {
		return false;
	}
}

function isAdmin() {
	return preg_match("/^admin/i", $_SERVER["REMOTE_USER"]) || preg_match("/^cttd/i", $_SERVER["REMOTE_USER"]);
}

function isCRA() {
	return substr($_SERVER["REMOTE_USER"], 0, 3) == "996";
}

function isPM() {
	return substr($_SERVER["REMOTE_USER"], 0, 3) == "991";
}

function getCentersData($from = null, $to = null) {
	global $conn;
	global $study_prefix;

	/** Lista dei centri **/

	$query_center_list_query =
			"SELECT * FROM (SELECT t.*, RANK() OVER (ORDER BY ID_CENTER) AS ROWNUMBER FROM CMM_CENTER t WHERE";
	if (isAdmin()) {
		$query_center_list_query .= "ID_CENTER NOT IN (99, 599) ";
	} elseif (isCRA()) {
		$query_center_list_query .= "ID_CENTER IN (";
		foreach (getCRACenters() as $center) {
			$query_center_list_query .= $center.", ";
		}
		$query_center_list_query .= "0)";

	} elseif (isPM()) {
		$query_center_list_query .= "ID_CENTER NOT IN (99, 599) ";
	} else {
		$query_center_list_query .= "ID_CENTER=".intval(substr($_SERVER["REMOTE_USER"], 0, 3));
	}

	$query_center_list_query .= " ORDER BY ID_CENTER) WHERE 1=1".
	(isset($from) ? " AND ROWNUMBER >= ".intval($from) : "").
	(isset($to) ? " AND ROWNUMBER <= ".intval($to) : "");

	// Esecuzione della query
	$query_center_list=new query($conn);
	$query_center_list->exec ( $query_center_list_query );
	$db_centers = array();
	while($query_center_list->get_row()){
		$db_center = $query_center_list->row;
		/** Lista degli utenti **/
		$vals = array();
		$vals['CENTER_CODE'] = substr("000".$query_center_list->row['ID_CENTER'], -3);
		$query_user_list_query = "SELECT * FROM CMM_USERS WHERE SUBSTR(CMM_USERID, 0, 3)=:CENTER_CODE AND SUBSTR(CMM_USERID, 0, 3)!='599' AND CMM_USERID NOT LIKE '%00099' ORDER BY CMM_USERID";
		$query_user_list=new query($conn);
		$query_user_list->exec($query_user_list_query, $vals);
		$db_users = array();
		while($query_user_list->get_row()){
			$db_users[]=$query_user_list->row;
		}
		/** Lista delle lingue **/
		$vals = array();
		$vals['CENTER_CODE'] = substr("000".$query_center_list->row['ID_CENTER'], -3);
		$query_lang_list_query =
				"SELECT P.*, L.SELECTED from {$study_prefix}_LANGUAGES P, (SELECT 'YES' AS SELECTED, LANGUAGE FROM CMM_LANGUAGE
					WHERE CENTER = :CENTER_CODE) L WHERE P.LANGUAGE = L.LANGUAGE(+) ORDER BY P.LANGUAGE";
		$query_lang_list=new query($conn);
		$query_lang_list->exec($query_lang_list_query, $vals);
		$db_langs = array();
		while($query_lang_list->get_row()){
			$db_langs[]=$query_lang_list->row;
		}
		// Aggiungo un utente dummy per l'inserimento
		$db_users['CMM_USERID'] = array('CMM_USERID' => 'CMM_USERID', 'ROLE' => '11');
		// Aggiungo gli utenti al centro
		$db_center['USERS'] = $db_users;
		// Aggiungo le lingue al centro
		$db_center['LANGS'] = $db_langs;
		// Aggiungo il centro alla lista dei centri
		$db_centers[$query_center_list->row['ID_CENTER']]= $db_center;
	}

	return $db_centers;
}

function getUserInfo($cmm_userid) {
	global $conn;

	$vals = array();
	$vals['CMM_USERID'] = $cmm_userid;
	$query_user_info_query = "SELECT * FROM CMM_USERS WHERE CMM_USERID=:CMM_USERID";
	$query_user_info = new query($conn);
	$query_user_info->exec($query_user_info_query, $vals);
	$query_user_info->get_row();

	$user_info = $query_user_info->row;

	return $user_info;
}

function sendUserInfo($cmm_userid) {
	global $conn;

	$vals = array();
	$vals['CMM_USERID'] = $cmm_userid;
	$query_user_info_query = "SELECT * FROM CMM_USERS WHERE CMM_USERID=:CMM_USERID";
	$query_user_info = new query($conn);
	$query_user_info->exec($query_user_info_query, $vals);
	$query_user_info->get_row();

	$user_info = $query_user_info->row;

	return $user_info;
}

//Funzioni helper IANUS
function SetIanusGroup($conn,$userId,$groupId){
	$sql_ianus3=new query($conn);
	$vals_user=array();
	$vals_user['USERID']=$userId;
	$vals_user['ID_GRUPPOU']=$groupId;
	$vals_user['ABILITATO']=1;
	$vals_user['UPDATE_ID']=0;
	$sql_ianus3->insert($vals_user,"UTENTI_GRUPPIU",'');
}
function SetIanusFunction($conn,$userId,$funzName){
	$sql_ianus3=new query($conn);
	$vals_user=array();
	$vals_user['USERID']=$userId;
	$vals_user['NOME_FUNZ']=$funzName;
	$vals_user['TIPO_ECCEZIONE']=1;
	$vals_user['UPDATE_ID']=0;
	$sql_ianus3->insert($vals_user,"UTENTI_FUNZ",'');

}
function insert_center($values){
	global $conn;
	global $study_prefix;

	//CONTROLLO CHE IL CODE INSERITO NON ESISTA GIA' IN TABELLA
	$check_center_exists_query="SELECT CODE from CMM_CENTER where CODE='".$values['CODE']."'";
	$check_center_exists=new query($conn);
	$check_center_exists->exec($check_center_exists_query);
	$check_center_exists->get_row();
	$check_center_id=$check_center_exists->row;
	if($check_center_id!=''){
		echo json_encode(array("sstatus" => "ko", "error" => "A Center with the same SITEID exists, please choose another.", "detail" => ""));
		die();
	}
	$id_center=$values['ID_CENTER'];
	if($id_center>=990){
		echo json_encode(array("sstatus" => "ko", "error" => "You can't insert a center with CENTER_ID>=990", "detail" => ""));
		die();
	}	
	// Insert del centro
	$sql2=new query($conn);
	$sql2->insert($values,"CMM_CENTER");
	// Insert into DBLOCK
	
	$values2=array();
	$values2['CENTER'] = $id_center;
	$values2['sendsave'] = 0;
	$values2['equery'] = 0;
	$sql3=new query($conn);
	$sql3->insert($values2, $study_prefix."_DBLOCK");

	// Substudy RANGE
	if (hasRangeSubStudy()) {
		// RANGE_COORDINATE
		$values = array();
		$values['VISITNUM'] = "0";
		$values['VISITNUM_PROGR'] = "0";
		$values['PROGR'] = "0";
		$values['ESAM'] = "0";
		$values['INIZIO'] = "0";
		$values['FINE'] = "0";
		$values['USERID'] = substr("000".$id_center, -3)."00001";
		$values['VISITCLOSE'] = "0";
		$values['CODPAT'] = $id_center;
		$values['ABILITATO'] = "1";
		$sql_range=new query($conn);
		$sql_range->insert($values,"RANGE_COORDINATE");

		// RANGE_REGISTRATION
		$values = array();
		$values['CODPAT'] = $id_center;
		$values['ESAM'] = "0";
		$values['PROGR'] = "1";
		$values['VISITNUM'] = "0";
		$values['VISITNUM_PROGR'] = "0";
		$values['CENTER'] =  substr("000".$id_center, -3);
		$values['SITEID'] =  substr("000".$id_center, -3);

		$sql_range=new query($conn);
		$sql_range->insert($values,"RANGE_REGISTRATION");


	}

	$conn->commit();
}
//require_once "libs/hyperlibs/http_lib.inc";

//if (($_SERVER['REMOTE_USER']!='ADMIN' || ($_SERVER['REMOTE_USER']!='CRA') ){die("Utente non abilitato");}

$user_textbox_editable_field = array("NAME", "SURNAME", "EMAIL", "PHONE", "FAX", "ADDRESS");
$user_textbox_not_editable_field = array("CREATEDT",  "EXPDT", "FSTACCDT", "LSTACCDT", "ENDDT");

/** Require della libreria per l'interfacciamento al DB del servizio. */
include_once "libs/db.inc";
// Connessione generale
$conn= new dbconn();
$sql=new query($conn);
$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
$sql->ins_upd();

$xml = simplexml_load_file("study.xml") or die("feed not loading");
$study_name=$xml->workflow->nome;
$study_prefix=$xml->configuration->prefix;


function isAjax()
{
	if (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && $_SERVER['HTTP_X_REQUESTED_WITH'] == "XMLHttpRequest")
	return true;
	return false;
}

function send_error_page($service,$remote_userid, $error, $error_spec){
	$cineca_user ="hypersuite@cineca.it";
	$hd_pierrelgroup="hypernet@pierrel-research.com";
	if(preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])){
		//"Sviluppo";
		$mailto=$cineca_user;
	}elseif(preg_match("/\.test\./i",$_SERVER['HTTP_HOST'])){
		//"Preproduzione";
		$mailto=$cineca_user." , ".$hd_pierrelgroup;
	}else{
		//"Produzione";
		// Eventuale altro recapito:
		$xml = simplexml_load_file("xml/error_page.xml");
		$other_mailto = $xml->mailto;
		//$mailto.=$other_mailto;
			
		$mailto=$cineca_user." , ".$hd_pierrelgroup."";
	}

	$today = date("j/m/Y, H:m:s");
	$url_from=$url_from="https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
	if($_GET['list']!=''){
		$url_from="https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
	}

	$headers  = "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\n";
	$headers .= "Content-type: text/html; charset=utf-8 \n";
	if (is_array($error_spec)) foreach ($error_spec as $key => $val){
		$spec.="\n $key : $val";
	}
	//print($mailto);print($headers);echo "<hr>";
	mail("$mailto", "Errore[".$_SERVER['REMOTE_USER']."]","$today <br><br> $error <br><br> <b>Specifiche errore:<b> <br>".$spec."<br><b> URL:<b> <br><a href='$url_from' target='_new'>".$url_from."</a>", "$headers");
}

function error_page($user, $error, $detail)
{
	global $study_prefix;
	if (isAjax()) {
		send_error_page($study_prefix,$_SERVER['REMOTE_USER'], $error, $detail);
		echo json_encode(array("sstatus" => "ko", "user" => $user, "error" => $error, "detail" => implode("-", $detail)));
		die();
	}
}


if (isAjax()) {
	//Logger::info($_POST);
	// Array delle lingue
	$lang_array = getLanguages($conn, $study_prefix);

	// Sanitize input
	$_POST = sanitizeInput($_POST);

	// Check request
	checkArrayValues($_POST);
	// Richieste Ajax
	$values = array();
	if (preg_match("/connectivity_check/i", $_POST["ACTION"])) {
		// Check di connessione
		echo json_encode(array("sstatus" => "ok"));

	}  elseif (preg_match("/get_user_info/i", $_POST["ACTION"])) {
		if (isset($_POST["CMM_USERID"]) && $_POST["CMM_USERID"] != '') {
			echo json_encode(array_merge(array("sstatus" => "ok"), getUserInfo($_POST["CMM_USERID"])));
		} else {

		}

	} elseif (preg_match("/send_user_info/i", $_POST["ACTION"])) {
		if (isset($_POST["CMM_USERID"]) && $_POST["CMM_USERID"] != '') {
			/*
			 * COMMENTATO PER NON FAR MANDARE MAIL AUTOMATICA
			$userinfo = getUserInfo($_POST["CMM_USERID"]);

			//site_headers
			if (preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])) {
			// Dev
			$site_headers = $study_name.".dev";
			} elseif (preg_match("/\.test\./i",$_SERVER['HTTP_HOST'])) {
			// Test
			$site_headers = $study_name.".test";
			} elseif (preg_match("/-preprod\./i",$_SERVER['HTTP_HOST'])) {
			// PreProd
			$site_headers = $study_name."-preprod";
			} else {
			// Prod
			$site_headers = $study_name;
			}

			// Header dell'email
			$headers  = "From: {$site_headers}@hypernetproject.com\nContent-type: text/html; charset=utf-8 \n";
			// Costruisco il template per la mail in base al servizio
			// User information
			$email_template = new Smarty();
			$email_template->assign("userinfo", $userinfo);
			$email_template->assign("send_password", FALSE);
			$userinfo['URL'] = "https://".$_SERVER['HTTP_HOST']."/";
			$email_text = $email_template->fetch(preg_replace("/\.php/", ".email.tpl", $_SERVER['SCRIPT_FILENAME']));
			mail($userinfo['EMAIL'], ucfirst($study_name)." registration", $email_text, $headers);
			// User password
			$email_template = new Smarty();
			$email_template->assign("userinfo", $userinfo);
			$email_template->assign("send_password", TRUE);
			$email_text = $email_template->fetch(preg_replace("/\.php/", ".email.tpl", $_SERVER['SCRIPT_FILENAME']));
			mail($userinfo['EMAIL'], ucfirst($study_name)." registration", $email_text, $headers);
			*/
			// Aggiorno il mailsent
			$where['CMM_USERID'] = $_POST["CMM_USERID"];
		$values['MAIL_SENT'] = "Y";
		$sql2 = new query($conn);
		$sql2->update($values, "CMM_USERS", $where);
		$conn->commit();

		echo json_encode(array_merge(array("sstatus" => "ok")));
		} else {

		}

	}elseif (preg_match("/pagination/i", $_POST["ACTION"])) {
		if (isset($_POST["from"]) && $_POST["from"] != '' && isset($_POST["to"]) && $_POST["to"] != '') {
			echo json_encode(array_merge(array("sstatus" => "ok"), getCentersData($_POST["from"], $_POST["to"])));
		} else {

		}
			
	} elseif (preg_match("/get_language_center/i", $_POST["ACTION"])) {
		// Get delle lingue del centro
		$vals = array();
		$vals['CENTER_CODE'] = substr("000".$_POST["ID_CENTER"], -3);
		$query_lang_list_query =
					"SELECT P.*, L.SELECTED from {$study_prefix}_LANGUAGES P, (SELECT 'YES' AS SELECTED, LANGUAGE FROM CMM_LANGUAGE
						WHERE CENTER = :CENTER_CODE) L WHERE P.LANGUAGE = L.LANGUAGE(+) ORDER BY P.LANGUAGE";
		$query_lang_list=new query($conn);
		$query_lang_list->exec($query_lang_list_query, $vals);
		$db_langs = array();
		while($query_lang_list->get_row()){
			$db_langs[]=$query_lang_list->row;
		}

		echo json_encode(array_merge(array("sstatus" => "ok"), $db_langs));
			
	} elseif (preg_match("/update_language_center/i", $_POST["ACTION"])) {
		// Aggiornamento Language
		$center_id = substr("000".$_POST["ID_CENTER"], -3);
		$values['ID_CENTER'] = $center_id;
		$sql_stmt = "DELETE FROM CMM_LANGUAGE WHERE CENTER=:ID_CENTER";
		$sql=new query($conn);
		$sql->exec($sql_stmt, $values);
		$conn->commit();
		foreach ($_POST as $single_lang_key => $single_lang_value) {
			if (array_key_exists($single_lang_key, $lang_array)) {
				$values = array();
				$values['LANG_CODE'] = $single_lang_key;
				$sql_stmt =
						"INSERT INTO CMM_LANGUAGE SELECT '{$center_id}', L.LANGUAGE, L.D_LANGUAGE
						FROM {$study_prefix}_LANGUAGES L WHERE L.LANGUAGE=:LANG_CODE";
				$sql=new query($conn);
				$sql->exec($sql_stmt, $values);
				$conn->commit();
			}
		}
		// Riselezioni i campi
		$sql_fill_form = new query($conn);
		$sql_fill_form->select(
		array("LANG_CHECKBOX" => "'checkboxlang_'||LANGUAGE||'_center_{$_POST["ID_CENTER"]}'"),
		array("CMM_LANGUAGE" => "CMM_LANGUAGE"), null,
		array("CENTER" => array("f1"=>"CENTER", "f2"=>$center_id)));
		$selected_langs = array();
		while($sql_fill_form->get_row()) {
			$selected_langs[$sql_fill_form->row[LANG_CHECKBOX]] = "on";
		}
			
		echo json_encode(array_merge(array("sstatus" => "ok"), $selected_langs));
			
	} elseif (preg_match("/center/i", $_POST["ACTION"])) {
		if (! (isAdmin() || isPM() || (isEnabledCenter($_POST["ID_CENTER"]) && isCRA() && in_array($_POST["ID_CENTER"], getCRACenters())))) {
			//print_r();
			// Se il centro è disabilitato oppure non si è admin o pm oppure cra e non si amministra il centro
			// oppure non è un utente (nuovo o vecchio) del centro che amministro
			echo json_encode(array("sstatus" => "ko", "error" => "Center is disabled", "detail" => ""));
			die();
		}

		// CENTER
		$field_names = array(
				'ID_CENTER' => 'ID_CENTER',
				'CODE' => 'CODE',
				'NAME' => 'NAME',
				'PI' => 'PI',
				'ADDRESS' => 'ADDRESS',
				'PHONE' => 'PHONE',
				'FAX' => 'FAX',
				'COUNTRY' => 'COUNTRY',
				'D_COUNTRY' => 'D_COUNTRY',
				'STATUS' => 'STATUS',
				'D_STATUS' => 'D_STATUS',
				'GENURS' => 'GENURS',
		);

		foreach ($field_names as $field_name)
		{
			if (isset($_POST[$field_name])) {
				$values[$field_name] = $_POST[$field_name];
					
			}
		}
			
		// Aggiungo l'utente
		$values['GENURS'] = $_SERVER['REMOTE_USER'];

		if ($_POST["ID_CENTER"] == "NEWCENTER") {
			/** NUOVO SVILUPPO
			 *
			 * 1) L'ID_CENTER deve prendere il centro con code maggiore dalla CMM_Center, e creare quindi il successivo.
			 * 2) Controllare che in preprod il centro 599 non venga creato.
			 *    Quindi creando come amministratore in Ianus il centro 598,
			 *    il successivo centro creato dal tool Account management deve essere con code 600 e non 599.
			 *
			 * V. Mazzeo
			 * 24/01/2012
			 *
			 */
			//INSERIMENTO NUOVO CENTRO
			// Seleziono il next val
			$sql_stmt = "SELECT	max(ID_CENTER)+1 as ID_CENTER from CMM_CENTER WHERE ID_CENTER!=599";
			$sql=new query($conn);
			$sql->exec($sql_stmt);
			$sql->get_row();
			if($sql->row['ID_CENTER']==''){
				$id_center_nextval=1;
				if (preg_match("/-preprod\./i",$_SERVER['HTTP_HOST'])) {
					// 			PreProd
					$id_center_nextval = "501";
				}
			}
			else{
				$id_center_nextval=$sql->row['ID_CENTER'];
				if ($id_center_nextval=='599') {
					$id_center_nextval++; //non posso creare il centro 599
				}
			}
			$values['ID_CENTER'] = $id_center_nextval;
				
				
				
				
			// 			$sql_stmt = "SELECT	{$cmm_center_sequence_name}.NEXTVAL AS IDCENTER_NEXTVAL FROM DUAL";
			// 			$sql=new query($conn);
			// 			$sql->exec($sql_stmt);
			// 			$sql->get_row();
			// 			$id_center_nextval=$sql->row['IDCENTER_NEXTVAL'];

			insert_center($values);
			// Riselezioni i campi
			$sql_fill_form = new query($conn);
			$sql_fill_form->select($field_names,
			array("CMM_CENTER" => "CMM_CENTER"), null,
			array("ID_CENTER" => array("f1"=>"ID_CENTER", "f2"=>$id_center_nextval)));
			$sql_fill_form->get_row();

			echo json_encode(array_merge(array("sstatus" => "ok", "new_center_inserted" => true), $sql_fill_form->row));

		} else { //AGGIORNAMENTO STATUS DEL CENTRO
			$where['ID_CENTER'] = intval($values["ID_CENTER"]);
			if ($values) {
				//print_r($values);	
				// Copio nello storico
				$sql_storico=copiaInStoricoDB($conn, "CMM_CENTER", $cmm_center_cols, "ID_CENTER", $values["ID_CENTER"]);
				$sql2 = new query($conn);
				$sql2->update($values, "CMM_CENTER", $where);

				// Disabilito anche gli utenti
				if ($values['D_STATUS'] == "Disabled") {
					$sql_ianus_users=new query($conn);
					$temp_vals['CENTER_CODE'] = substr("000".$values["ID_CENTER"], -3);
					$query_user_list_query = "SELECT CMM_USERID FROM CMM_USERS WHERE SUBSTR(CMM_USERID, 0, 3)=:CENTER_CODE AND CMM_USERID NOT LIKE '%00099' ORDER BY CMM_USERID";
					$sql_ianus_users->exec($query_user_list_query, $temp_vals);

					while($sql_ianus_users->get_row()) {
						// Scorro gli utenti
						$sql_ianus=new query($conn);
						$vals_user=array();
						$vals_user['ABILITATO']="0";
						$sql_ianus->update($vals_user, "UTENTI", array("USERID" => $sql_ianus_users->row['CMM_USERID']));
						// Scorro gli utenti
						$sql_cmm_user=new query($conn);
						$vals_user=array();
						$vals_user['STATUS']="0";
						$vals_user['D_STATUS']="Disabled";
						$vals_user['ENDDT']="sysdate";
						copiaInStoricoDB($conn, "CMM_USERS", $cmm_users_cols, "CMM_USERID", $sql_ianus_users->row['CMM_USERID']);
						$sql_cmm_user->update($vals_user, "CMM_USERS", array("CMM_USERID" => $sql_ianus_users->row['CMM_USERID']));
					}
					if($sql_ianus_users->numrows>0)
					{
						$sql_get_center_code="SELECT CODE FROM CMM_CENTER WHERE ID_CENTER={$where['ID_CENTER']}";
						$sql_get_center_code_query=new query($conn);
						$sql_get_center_code_query->exec($sql_get_center_code);
						$sql_get_center_code_query->get_row();
						$center_code=$sql_get_center_code_query->row["CODE"];
						
						
						$all_user_disabled_query = new query($conn);
						$all_user_disabled_values=array("ALL_USER_DISABLED_MAIL_SENT"=>"1");
						$all_user_disabled_query->update($all_user_disabled_values, "CMM_CENTER", $where);
						send_error_page($study_prefix,$_SERVER['REMOTE_USER'], "ALL USERS DISABLED", array("ERROR"=>"ALL THE USERS OF THE CENTER {$center_code} ARE DISABLED!"));
					}
					
				}
				$conn->commit();

				// Riselezioni i campi
				$sql_fill_form = new query($conn);
				$sql_fill_form->select($field_names,
				array("CMM_CENTER" => "CMM_CENTER"), null,
				array("ID_CENTER" => array("f1"=>"ID_CENTER", "f2"=>$values["ID_CENTER"])));
				$sql_fill_form->get_row();
					
				echo json_encode(array_merge(array("sstatus" => "ok", "center_status_updated" => true), $sql_fill_form->row));
			} else {
				echo json_encode(array("sstatus" => "ko"));
			}
		}

	} elseif (preg_match("/user/i", $_POST["ACTION"])) {
		if (intval($_POST["ID_CENTER"])<900&&!isEnabledCenter($_POST["ID_CENTER"]) ||
		!(
		isAdmin() ||
		isPM() ||
		(
		isEnabledCenter($_POST["ID_CENTER"]) &&
		(
		(isCRA() && in_array($_POST["ID_CENTER"], getCRACenters())) ||
		(intval(substr($_POST["CMM_USERID"], 0, 3)) == $_POST["ID_CENTER"]) ||
		(($_POST["CMM_USERID"] == "NEWUSER") && (intval(substr($_SERVER["REMOTE_USER"], 0, 3)) == $_POST["ID_CENTER"]))
		)
		)
		)
			
		) {
			// Se il centro è disabilitato oppure non si è admin o pm oppure cra e non si amministra il centro
			// oppure non è un utente (nuovo o vecchio) del centro che amministro
			/** NUOVO SVILUPPO V.Mazzeo 20/01/2012: ho aggiunto condizione affinchè un global user possa essere inserito anche se non si verificano le condizioni riportate sopra**/
			echo json_encode(array("sstatus" => "ko", "error" => "Center is disabled"+$_POST["ID_CENTER"], "detail" => ""));
			die();
		}
		// USER
		$field_names = array(
				'CMM_USERID' => 'CMM_USERID',
				'ROLE' => 'ROLE',
				'D_ROLE' => 'D_ROLE',
				'CODE' => 'CODE',
				'NAME' => 'NAME',
				'SURNAME' => 'SURNAME',
				'EMAIL' => 'EMAIL',
				'PHONE' => 'PHONE',
				'FAX' => 'FAX',
				'ADDRESS' => 'ADDRESS',
				'STATUS' => 'STATUS',
				'D_STATUS' => 'D_STATUS',
				'SIGN' => 'SIGN',
				'D_SIGN' => 'D_SIGN',
				'SIGNSAE' => 'SIGNSAE',
				'D_SIGNSAE' => 'D_SIGNSAE',
				'GENURS' => 'GENURS',
				'MAIL_SENT' => 'MAIL_SENT',
		);

		$field_names_complete = array_merge($field_names,
		array(
					'CREATEDT' => 'CREATEDT',
					'FSTACCDT' => 'FSTACCDT',
					'LSTACCDT' => 'LSTACCDT',
					'EXPDT' => 'EXPDT',
					'ENDDT' => 'ENDDT',
			)
		);
			
		foreach ($field_names as $field_name)
		{
			if (isset($_POST[$field_name])) {
				$values[$field_name] = $_POST[$field_name];
					
			}
		}
		// Aggiungo l'utente
		$values['GENURS'] = $_SERVER['REMOTE_USER'];
		// Aggiungo l'exp date
		if (isset($values['STATUS']) && $values['STATUS'] == 0) {
			$values['ENDDT'] = "sysdate";
		}
			
		if ($_POST["CMM_USERID"] == "NEWUSER") {
			// Seleziono il next val
			$center_id = $_POST["ID_CENTER"];

			if (intval($center_id) > 900) {
				// Utente globale
				$sql_stmt =
					"SELECT CASE
					         WHEN USERID IS NULL THEN
					          '{$center_id}'||'00001'
					         ELSE
					          '{$center_id}'||USERID
					       END AS USERID_NEXTVAL
					  FROM (SELECT LTRIM(TO_CHAR(MAX(TO_NUMBER(SUBSTR(USERID, 4))) + 1, '00000')) AS USERID
					          FROM (SELECT USERID
					                  FROM UTENTI
					                 WHERE USERID != '{$center_id}00099'
					                   AND USERID LIKE '{$center_id}%'))";
			} else {
				// Utente di un centro
				$center_id = substr("000".$_POST["ID_CENTER"], -3);
				// Site Staff o PI
				$sql_stmt =
					"SELECT '".$center_id."'||
						(CASE
						WHEN NOT MAX(TO_NUMBER(SUBSTR(USERID, 4))) IS NULL THEN LTRIM(TO_CHAR(MAX(TO_NUMBER(SUBSTR(USERID, 4))) + 1, '00000'))
						ELSE '00001' END)
					AS USERID_NEXTVAL
					FROM (SELECT USERID FROM UTENTI WHERE USERID!='".$center_id."00099')
					WHERE USERID LIKE '".$center_id."%'";
			}
			$sql=new query($conn);
			$sql->exec($sql_stmt);
			$sql->get_row();
			$userid_nextval=$sql->row['USERID_NEXTVAL'];
			/** NUOVO SVILUPPO
			 *
			 * 1) Controllare che non vengano creati utenti con id XXXXXXX99 (user test)
			 *    il successivo utente creato dal tool Account management deve essere con code XXXXX100 .
			 *
			 * V. Mazzeo
			 * 24/01/2012
			 *
			 */
			if(substr($userid_nextval,-2)=='99'){
				$userid_nextval=str_replace("099","100",$userid_nextval);
			}
			// Generate password
			$new_user_password = generatePassword();
			$values['FIRST_PASSWORD']=strtolower($new_user_password);
			$expirepwd = "sysdate-1";
			// Insert dell'utente in CMM_USERS
			$values['CMM_USERID']=$userid_nextval;
			$values['CREATEDT']="sysdate";
			$values['EXPDT']=$expirepwd;
			$sql2=new query($conn);
			$sql2->insert($values,"CMM_USERS");
			// 				$conn->commit();

			// Insert dell'utente in UTENTI

			$sql_ianus=new query($conn);
			$vals_user=array();
			$vals_user['USERID']=$userid_nextval;
			$vals_user['PASSWORD']=strtoupper($new_user_password);
			$vals_user['ABILITATO']=1;
			$vals_user['ID_TIPOLOGIA']=1;
			$vals_user['BUDGET']=0;
			$vals_user['CONSUMO']=0;
			$vals_user['SCADENZAPWD']=8;
			$vals_user['DTTM_SCADENZAPWD']=$expirepwd;
			$vals_user['DTTM_ULTIMOACCESSO']="";
			$vals_user['SBLOCCOPWD']="";
			$vals_user['ID_VISTA']=0;
			$vals_user['UPDATE_ID']=0;
			$sql_ianus->insert($vals_user,"UTENTI",'');
			// Insert dell'utente in ANA_UTENTI_1
			$sql_ianus2=new query($conn);
			$vals_user=array();
			$vals_user['USERID']=$userid_nextval;
			$vals_user['ID_TIPOLOGIA']=1;
			$vals_user['COGNOME']=$values['SURNAME'];
			$vals_user['NOME']=$values['NAME'];
			$vals_user['EMAIL']=$values['EMAIL'];
			$vals_user['TELEFONO']=$values['PHONE'];
			$vals_user['FAX']=$values['FAX'];
			$vals_user['VIA']=$values['ADDRESS'];
			$vals_user['UPDATE_ID']=0;
			$sql_ianus2->insert($vals_user,"ANA_UTENTI_1",'');
			// Insert dell'utente in UTENTI_GRUPPI_U
			SetIanusGroup($conn,$userid_nextval,2);
			//$sql_ianus3=new query($conn);
			//$vals_user=array();
			//$vals_user['USERID']=$userid_nextval;
			//$vals_user['ID_GRUPPOU']=2;
			//$vals_user['ABILITATO']=1;
			//$vals_user['UPDATE_ID']=0;
			//$sql_ianus3->insert($vals_user,"UTENTI_GRUPPIU",'');

			switch (intval($_POST["ROLE"])){
				//Insert Gruppi e funzioni
				case 1: //PM
					SetIanusGroup($conn,$userid_nextval,5);
					SetIanusFunction($conn,$userid_nextval,'/cgi-bin/gestione_CRA');
					break;
				case 5: //SPONSOR
					SetIanusGroup($conn,$userid_nextval,4);
					break;
				case 6: //CRA
					//SetIanusFunction($conn,$userid_nextval,'/cgi-bin/gestione_CRA');
					SetIanusGroup($conn,$userid_nextval,6);
					break;
				case 7: //DM
					SetIanusGroup($conn,$userid_nextval,3);
					SetIanusFunction($conn,$userid_nextval,'/cgi-bin/browse_table');
					SetIanusFunction($conn,$userid_nextval,'/cgi-bin/multiple_dnl');
					break;
			}

			// per il delete
			/*
			delete from UTENTI_GRUPPIU where userid='00600002';
			delete from ANA_UTENTI_1 where userid='00600002';
			delete from UTENTI where userid='00600002';
			*/

			// 				$conn->commit();

			if (intval($_POST["ROLE"]) > 11) {
				// Abilitazione o meno alla firma
				$sql_disable_signature = new query($conn);
				// Cancello prima l'abilitazione alla firma nel caso la tabella sia stata in qualche modo alterata e quindi risilta disallineata
				$sql_disable_signature->exec(
						"DELETE FROM {$study_prefix}_FIRMA_UTENTI_CENTRI WHERE USERNAME=:USERNAME AND CENTER=:CENTER", 
				array("USERNAME" => $_POST["CMM_USERID"], "CENTER" => substr($_POST["CMM_USERID"], 0, 3)));
				if ($values['SIGN'] || $values['SIGNSAE']) {
					// Abilito la firma
					$sql_enable_signature = new query($conn);
					$sql_enable_signature->insert(
					array(
								"USERNAME" => $userid_nextval,
								"CENTER" => $center_id,
								"USER_ROLE" => ($_POST["ROLE"] == '12' ? "PI" : "CO_PI"),
					), $study_prefix."_FIRMA_UTENTI_CENTRI");
				}
			}
			$all_user_disabled_query = new query($conn);
			$all_user_disabled_values=array("ALL_USER_DISABLED_MAIL_SENT"=>"");
			$where=array("ID_CENTER"=>$center_id); 
			$all_user_disabled_query->update($all_user_disabled_values, "CMM_CENTER", $where);
			
			$conn->commit();

			// Riselezioni i campi
			$sql_fill_form = new query($conn);
			$sql_fill_form->select($field_names_complete,
			array("CMM_USERS" => "CMM_USERS"), null,
			array("CMM_USERID" => array("f1"=>"CMM_USERID", "f2"=>$userid_nextval)));
			$sql_fill_form->get_row();

			$new_user_data = $sql_fill_form->row;
			$new_user_data['PASSWORD'] = strtolower($new_user_password);

			echo json_encode(array_merge(array("sstatus" => "ok", "new_user_inserted" => true), $new_user_data));

		}
		else { //AGGIORNAMENTO UTENTE ESISTENTE
			$where['CMM_USERID'] = $values["CMM_USERID"];
			if ($values) {
				// Copio nello storico
				copiaInStoricoDB($conn, "CMM_USERS", $cmm_users_cols, "CMM_USERID", $values["CMM_USERID"]);
					
				//Update utente
				$sql2 = new query($conn);
				$sql2->update($values, "CMM_USERS", $where);
					
				// Abilitazione o meno dell'utente
				$sql_ianus=new query($conn);
				$vals_user=array();
				if(isset($values['STATUS'])){
					//HO INVIATO SOLO LA DISABILITAZIONE DELL'UTENTE
				 
					$vals_user['ABILITATO']=$values['STATUS'];
					$sql_ianus->update($vals_user, "UTENTI", array("USERID" => $values['CMM_USERID']));
					$sql_ianus=new query($conn);
				}
				if (isset($values['SURNAME'])){
					//HO MODIFICATO I DATI ANAGRAFICI DELL'UTENTE
				
					$vals_user=array();
					$vals_user['COGNOME']=$values['SURNAME'];
					$vals_user['NOME']=$values['NAME'];
					$vals_user['EMAIL']=$values['EMAIL'];
					$vals_user['TELEFONO']=$values['PHONE'];
					$vals_user['FAX']=$values['FAX'];
					$vals_user['VIA']=$values['ADDRESS'];
					$sql_ianus->update($vals_user, "ANA_UTENTI_1", array("USERID" => $values['CMM_USERID']));
				}
				// Abilitazione o meno alla firma
				if (intval($_POST["ROLE"]) > 11) {
					$sql_disable_signature = new query($conn);
					// Cancello prima l'abilitazione alla firma nel caso la tabella sia stata in qualche modo alterata e quindi risilta disallineata
					$sql_disable_signature->exec(
							"DELETE FROM {$study_prefix}_FIRMA_UTENTI_CENTRI WHERE USERNAME=:USERNAME AND CENTER=:CENTER", 
					array("USERNAME" => $values["CMM_USERID"], "CENTER" => substr($values["CMM_USERID"], 0, 3)));

					if ($values['SIGN'] || $values['SIGNSAE']) {
						// Abilito la firma
						$sql_enable_signature = new query($conn);
						$sql_enable_signature->insert(
						array(
									"USERNAME" => $values["CMM_USERID"],
									"CENTER" => substr($values["CMM_USERID"], 0, 3),
									"USER_ROLE" => ($_POST["ROLE"] == '12' ? "PI" : "CO_PI"),
						), $study_prefix."_FIRMA_UTENTI_CENTRI");
							

					}
				}
					
				$conn->commit();
					
				// Riselezioni i campi
				$sql_fill_form = new query($conn);
				$sql_fill_form->select($field_names_complete,
				array("CMM_USERS" => "CMM_USERS"), null,
				array("CMM_USERID" => array("f1"=>"CMM_USERID", "f2"=>$values["CMM_USERID"])));
				$sql_fill_form->get_row();
					
				echo json_encode(array_merge(array("sstatus" => "ok","user_updated" => true,$sql2->get_sql(), "VALS"=>$vals_user), $sql_fill_form->row));
					
			}
			else {
				echo json_encode(array("sstatus" => "ko"));
			}
			//break;
		}
	}

	die();
}

// CMM_CEMTER
allineaDB($conn, "CMM_CENTER", $cmm_center_cols, "alter table CMM_CENTER add constraint PK_CMM_CENTER primary key (ID_CENTER)");
allineaDB($conn, "S_CMM_CENTER", $cmm_center_s_cols, "alter table S_CMM_CENTER add constraint S_PK_CMM_CENTER primary key (MODPROG)");
// CMM_USERS
allineaDB($conn, "CMM_USERS", $cmm_users_cols, "alter table CMM_USERS add constraint PK_CMM_USERS primary key (CMM_USERID)");
allineaDB($conn, "S_CMM_USERS", $cmm_users_s_cols, "alter table S_CMM_USERS add constraint S_PK_CMM_USERS primary key (MODPROG)");
// CMM_LANGUAGE
allineaDB($conn, "CMM_LANGUAGE", $cmm_language_cols, "ALTER TABLE CMM_LANGUAGE ADD CONSTRAINT PK_CMM_LANGUAGE PRIMARY KEY (CENTER, LANGUAGE)");
// SERVICE_LANGUAGE
allineaDB($conn, $study_prefix."_LANGUAGES", $study_language_cols, "ALTER TABLE {$study_prefix}_LANGUAGES ADD CONSTRAINT PK_{$study_prefix}_LANGUAGES PRIMARY KEY (LANGUAGE)");
// SEQUENCE
allineaSEQ($conn, $study_name);
// FIRMA UTENTI CENTRI
allineaDB($conn, $study_prefix."_FIRMA_UTENTI_CENTRI", $firma_utenti_centri_cols, "ALTER TABLE {$study_prefix}_FIRMA_UTENTI_CENTRI ADD CONSTRAINT PK_{$service}_FIRMA PRIMARY KEY (USERNAME, CENTER)");
//LISTE COUNTRY
$iso_country_list = array();
$iso_country_list_query = "SELECT * FROM {$study_prefix}_ISO_COUNTRY_LIST ORDER BY COUNTRY";
$query_country_list=new query($conn);
$query_country_list->exec($iso_country_list_query);
while($query_country_list->get_row()){
	$iso_country_list[$query_country_list->row["ISO"]]=$query_country_list->row["COUNTRY"];
}
/**
 * NUOVO SVILUPPO 20/01/2012
 * 1) inserisco gli utenti creati tramite ianus e non tramite cmm
 * 2) disabilito o elimino gli utenti disabilitati o eliminati tramite ianus e non tramite cmm
 * V. Mazzeo
 */
/** 1)  */
$query_inserisci_ianus_to_cmm_query="select * from ANA_UTENTI_1 ana JOIN UTENTI ute on ana.userid=ute.userid where ana.userid not in (select cmm_userid from cmm_users) and ana.userid not like '%99' and ana.userid not like '990%' AND ana.userid not like '992%' AND ana.userid not like '993%' AND ana.userid not like '994%' AND ana.userid not like '998%' AND ana.userid not like '999%' and ana.userid not like '599%' and REGEXP_LIKE(ana.userid,'^[0-9]')";
//echo $query_inserisci_ianus_to_cmm_query;
$query_allinea_ianus=new query($conn);
$query_allinea_ianus->exec($query_inserisci_ianus_to_cmm_query);
while($query_allinea_ianus->get_row()){
	$from_ianus_to_cmm= array();
	$from_ianus_to_cmm['CMM_USERID']=$query_allinea_ianus->row['USERID'];
	//PRENDO IL RUOLO DALL'USERID
	if(substr($query_allinea_ianus->row['USERID'],0,3)=='991')//PER I GLOBAL USER
	{
		$from_ianus_to_cmm['ROLE']='1';
		$from_ianus_to_cmm['D_ROLE']='Project Manager';
	}
	else if(substr($query_allinea_ianus->row['USERID'],0,3)=='995')
	{
		$from_ianus_to_cmm['ROLE']='5';
		$from_ianus_to_cmm['D_ROLE']='Sponsor';
	}
	else if(substr($query_allinea_ianus->row['USERID'],0,3)=='996')
	{
		$from_ianus_to_cmm['ROLE']='6';
		$from_ianus_to_cmm['D_ROLE']='CRA';
	}
	else if(substr($query_allinea_ianus->row['USERID'],0,3)=='997')
	{
		$from_ianus_to_cmm['ROLE']='7';
		$from_ianus_to_cmm['D_ROLE']='Data Manager';
	}
	else{
		//PER GLI UTENTI DEI CENTRI VEDO SE C'E' UN'OCCORRENZA IN {$study_prefix}_FIRMA_UTENTI_CENTRI
		$query_get_role_query="SELECT USER_ROLE FROM {$study_prefix}_FIRMA_UTENTI_CENTRI WHERE USERNAME=".$query_allinea_ianus->row['USERID'];
		$query_get_role=new query($conn);
		$query_get_role->exec($query_get_role_query);
		$query_get_role->get_row();
		$user_role=$query_get_role->row;
		if(isset($user_role)&&$user_role["USER_ROLE"]=='PI')
		{
			$from_ianus_to_cmm['ROLE']='12';
			$from_ianus_to_cmm['D_ROLE']='Principal Investigator';
			$from_ianus_to_cmm['SIGN']='1';
			$from_ianus_to_cmm['D_SIGN']='Enabled';
			$from_ianus_to_cmm['SIGNSAE']='1';
			$from_ianus_to_cmm['D_SIGNSAE']='Enabled';
				
		}
		else if(isset($user_role)&&$user_role["USER_ROLE"]=='CO_PI')
		{
			$from_ianus_to_cmm['ROLE']='13';
			$from_ianus_to_cmm['D_ROLE']='Sub-Investigator';
			$from_ianus_to_cmm['SIGN']='1';
			$from_ianus_to_cmm['D_SIGN']='Enabled';
			$from_ianus_to_cmm['SIGNSAE']='1';
			$from_ianus_to_cmm['D_SIGNSAE']='Enabled';
		}
		else{
			$from_ianus_to_cmm['ROLE']='11';
			$from_ianus_to_cmm['D_ROLE']='Site Staff';
			$from_ianus_to_cmm['SIGN']='0';
			$from_ianus_to_cmm['D_SIGN']='Disabled';
			$from_ianus_to_cmm['SIGNSAE']='0';
			$from_ianus_to_cmm['D_SIGNSAE']='Disabled';
		}
		//controllo che già esista un centro in CMM_CENTER
		$check_center_exists_query="SELECT ID_CENTER from CMM_CENTER where ID_CENTER='".substr($query_allinea_ianus->row['USERID'],0,3)."'";
		$check_center_exists=new query($conn);
		$check_center_exists->exec($check_center_exists_query);
		$check_center_exists->get_row();
		$check_center_id=$check_center_exists->row;
		if($check_center_id==''){
			//IL CENTRO NON ESISTE! QUINDI LO CREO
			$id_center=substr($query_allinea_ianus->row['USERID'],0,3);
			insert_center(array('ID_CENTER'=>$id_center,'NAME'=>$id_center." NAME ",'CODE'=>$id_center." CODE",'STATUS'=>'1','D_STATUS'=>'Enabled'));
		}
	}
	$from_ianus_to_cmm['SURNAME']=$query_allinea_ianus->row['COGNOME'];
	$from_ianus_to_cmm['NAME']=$query_allinea_ianus->row['NOME'];
	$from_ianus_to_cmm['EMAIL']=$query_allinea_ianus->row['EMAIL'];
	$from_ianus_to_cmm['PHONE']=$query_allinea_ianus->row['TELEFONO'];
	$from_ianus_to_cmm['FAX']=$query_allinea_ianus->row['FAX'];
	$from_ianus_to_cmm['ADDRESS']=$query_allinea_ianus->row['VIA']." ".$query_allinea_ianus->row['CAP']." ".$query_allinea_ianus->row['CITTA']." ".$query_allinea_ianus->row['NAZIONE'];
	$from_ianus_to_cmm['STATUS']=$query_allinea_ianus->row['ABILITATO'];
	if($query_allinea_ianus->row['abilitato'])
	{
		$from_ianus_to_cmm['D_STATUS']='Enabled';
	}
	else{
		$from_ianus_to_cmm['D_STATUS']='Disabled';
	}
	$from_ianus_to_cmm['FIRST_PASSWORD']=$query_allinea_ianus->row['SBLOCCOPWD'];
	$expirepwd = "sysdate-1";
	//IMPOSTO DATA DI CREAZIONE
	$createdt="";
	if(isset($query_allinea_ianus->row["DTTM_CREAZIONE"])) //NON TUTTI GLI STUDI HANNO QUESTO CAMPO IN TABELLA IANUS!
	{
		$createdt=$query_allinea_ianus->row["DTTM_CREAZIONE"];
	}
	else{
		//SE NON C'E' IN TABELLA IANUS PRENDO LA DATA DI CREAZIONE DALLA TABELLA STORICO
		$query_get_createdt_query="SELECT MODDT FROM S_X_{$study_prefix} WHERE NOMETAB='UTENTI' AND VAR='USERID' AND VALUE_NEW='".$query_allinea_ianus->row['USERID']."'";
		$query_get_createdt=new query($conn);
		$query_get_createdt->exec($query_get_createdt_query);
		$query_get_createdt->get_row();
		$createdt=$query_get_createdt->row["MODDT"];
		//echo "</br>".$query_get_createdt_query." ".$createdt;
	}
	$from_ianus_to_cmm['CREATEDT']=$createdt;
	$from_ianus_to_cmm['EXPDT']=$expirepwd;
	$from_ianus_to_cmm['GENURS'] = $_SERVER['REMOTE_USER'];

	$from_ianus_to_cmm_query=new query($conn);
	$from_ianus_to_cmm_query->insert($from_ianus_to_cmm,"CMM_USERS");
	//echo $from_ianus_to_cmm_query->get_sql();

	//echo "<pre>";
	//print_r($from_ianus_to_cmm);
	//echo "</pre>";
}
/** FINE 1)  */
/** 2)  */
$query_disabilita_ianus_to_cmm_query="update CMM_USERS set status=0, d_status='Disabled' where CMM_USERID in ( select userid from UTENTI where ABILITATO='0')";
//echo $query_disabilita_ianus_to_cmm_query;
$query_disabilita_ianus_to_cmm=new query($conn);
$query_disabilita_ianus_to_cmm->exec($query_disabilita_ianus_to_cmm_query);

$query_elimina_ianus_to_cmm_query="delete from CMM_USERS where CMM_USERID not in ( select userid from ANA_UTENTI_1)";
//echo $query_elimina_ianus_to_cmm_query;
$query_elimina_ianus_to_cmm=new query($conn);
$query_elimina_ianus_to_cmm->exec($query_elimina_ianus_to_cmm_query);

/** FINE 2)  */
$conn->commit();
/** fine nuovo sviluppo */

/** Lista dei centri **/
$query_center_list_query = "SELECT * FROM CMM_CENTER WHERE ";
if (isAdmin()) {
	$query_center_list_query .= "ID_CENTER NOT IN ( 599) ";
} elseif (isCRA()) {
	$query_center_list_query .= "ID_CENTER IN (";
	foreach (getCRACenters() as $center) {
		$query_center_list_query .= $center.", ";
	}
	$query_center_list_query .= "0)";

} elseif (isPM()) {
	$query_center_list_query .= "ID_CENTER NOT IN ( 599) ";
} else {
	$query_center_list_query .= "ID_CENTER=".intval(substr($_SERVER["REMOTE_USER"], 0, 3));
}
$query_center_list_query .= " ORDER BY ID_CENTER";
$query_center_list=new query($conn);
$query_center_list->exec ( $query_center_list_query );
$db_centers = array();
while($query_center_list->get_row()){
	$db_center = $query_center_list->row;
	/** Lista degli utenti **/
	$vals = array();
	$vals['CENTER_CODE'] = substr("000".$query_center_list->row['ID_CENTER'], -3);
	$query_user_list_query = "SELECT * FROM CMM_USERS WHERE SUBSTR(CMM_USERID, 0, 3)=:CENTER_CODE AND CMM_USERID NOT LIKE '%00099' ORDER BY CMM_USERID";
	$query_user_list=new query($conn);
	$query_user_list->exec($query_user_list_query, $vals);
	$db_users = array();
	$all_user_disabled=true;
	if($db_center["STATUS"]==0||($db_center["STATUS"]==1&&$query_user_list->numrows==0)){
		//se il centro è disabilitato oppure è abilitato ma non ha utenti
		$all_user_disabled=false;
	};
	while($query_user_list->get_row()){
		$row = $query_user_list->row;
		if($all_user_disabled&&isset($row["STATUS"])&&$row["STATUS"]==1){
			//se il centro è abilitato ed almeno un utente è abilitato
			$all_user_disabled=false;
		}
		//if (!$row['EXPDT']){
		$vals['USERID'] = $row['CMM_USERID'];
		$tmpquery = "SELECT DTTM_SCADENZAPWD,DTTM_ULTIMOACCESSO FROM UTENTI WHERE USERID=:USERID";
		$tmpquery_list=new query($conn);
		$tmpquery_list->exec($tmpquery, $vals);
		if ($tmpquery_list->get_row()){
			//echo "ENTRO";
			//ALLINEO ULTIMO ACCESSO E SCADENZA PWD DA VALORI IN TABELLA IANUS
			$sql2 = new query($conn);
			$values = array();
			$values['LSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
			$values['EXPDT'] = $tmpquery_list->row['DTTM_SCADENZAPWD'];
			if($row['FSTACCDT']==""){
				//se il first access non è stato ancora valorizzato allora coincide con l'ultimo accesso di ianus
				$values['FSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
				$row['FSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
			}
			$where['CMM_USERID']=$row['CMM_USERID'];
			$sql2->update($values, "CMM_USERS", $where);
			$conn->commit();
			//VISUALIZZO NUOVI VALORI
			$row['LSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
			$row['EXPDT'] = $tmpquery_list->row['DTTM_SCADENZAPWD'];
				
		}
		//echo("EXP:".$row['EXPDT']."<br/>");
		//}
		$db_users[]= $row;
	}
	//echo "<br/>".$query_user_list->numrows." ".$query_center_list->row['CODE']." all disabled? ".$all_user_disabled;
	if($all_user_disabled&&$db_center["ALL_USER_DISABLED_MAIL_SENT"]!="1"){
		$all_user_disabled_query = new query($conn);
		$all_user_disabled_values=array("ALL_USER_DISABLED_MAIL_SENT"=>"1");
		$where=array("ID_CENTER"=>$query_center_list->row['ID_CENTER']);
		$all_user_disabled_query->update($all_user_disabled_values, "CMM_CENTER", $where);
		$conn->commit();
		send_error_page($study_prefix,$_SERVER['REMOTE_USER'], "ALL USERS DISABLED", array("ERROR"=>"ALL THE USERS OF THE CENTER {$query_center_list->row['CODE']} ARE DISABLED!"));
	}
	//die();
	/** Lista delle lingue **/
	$vals = array();
	$vals['CENTER_CODE'] = substr("000".$query_center_list->row['ID_CENTER'], -3);
	$query_lang_list_query =
		"SELECT P.*, L.SELECTED from {$study_prefix}_LANGUAGES P, (SELECT 'YES' AS SELECTED, LANGUAGE FROM CMM_LANGUAGE
			WHERE CENTER = :CENTER_CODE) L WHERE P.LANGUAGE = L.LANGUAGE(+) ORDER BY P.LANGUAGE";
	$query_lang_list=new query($conn);
	$query_lang_list->exec($query_lang_list_query, $vals);
	$db_langs = array();
	while($query_lang_list->get_row()){
		$db_langs[]=$query_lang_list->row;
	}
	// Aggiungo un utente dummy per l'inserimento
	$db_users['CMM_USERID'] = array('CMM_USERID' => 'CMM_USERID');
	// Aggiungo gli utenti al centro
	$db_center['USERS'] = $db_users;
	// Aggiungo le lingue al centro
	$db_center['LANGS'] = $db_langs;
	// Aggiungo il centro alla lista dei centri
	$db_centers[$query_center_list->row['ID_CENTER']]= $db_center;
}

// 	$db_centers = array();
// Aggiungo un centro ed un utente dummy per l'inserimento
/** Lista delle lingue **/
$vals = array();
$vals['CENTER_CODE'] = substr("000".$query_center_list->row['ID_CENTER'], -3);
$query_lang_list_query = "SELECT P.*, '' from {$study_prefix}_LANGUAGES P ORDER BY P.LANGUAGE";
$query_lang_list=new query($conn);
$query_lang_list->exec($query_lang_list_query, $vals);
$db_langs = array();
while($query_lang_list->get_row()){
	$db_langs[]=$query_lang_list->row;
}

$db_centers['ID_CENTER'] = array('ID_CENTER' => 'IDCENTER', 'LANGS' => $db_langs, 'USERS' => array('CMM_USERID' => array ('CMM_USERID' => 'CMM_USERID')));

// Aggiungo gli utenti globali
$global_users = array();
$query_user_list_query = "SELECT * FROM CMM_USERS WHERE CMM_USERID LIKE '9%' ORDER BY CMM_USERID";
$query_user_list=new query($conn);
$query_user_list->exec($query_user_list_query);
while($query_user_list->get_row()){
	$row = $query_user_list->row;
	$vals['USERID'] = $row['CMM_USERID'];
	$tmpquery = "SELECT * FROM UTENTI WHERE USERID=:USERID";
	$tmpquery_list=new query($conn);
	$tmpquery_list->exec($tmpquery, $vals);
	if ($tmpquery_list->get_row()){
		//ALLINEO ULTIMO ACCESSO E SCADENZA PWD DA VALORI IN TABELLA IANUS
		$sql2 = new query($conn);
		$values = array();
		$values['LSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
		$values['EXPDT'] = $tmpquery_list->row['DTTM_SCADENZAPWD'];
		if($row['FSTACCDT']==""){
			//se il first access non è stato ancora valorizzato allora coincide con l'ultimo accesso di ianus
			$values['FSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
			$row['FSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
		}
		$where['CMM_USERID']=$row['CMM_USERID'];
		$sql2->update($values, "CMM_USERS", $where);
		$conn->commit();
		//VISUALIZZO NUOVI VALORI
		$row['LSTACCDT']=$tmpquery_list->row['DTTM_ULTIMOACCESSO'];
		$row['EXPDT'] = $tmpquery_list->row['DTTM_SCADENZAPWD'];
	}
	$global_users[$query_user_list->row['CMM_USERID']]=$row;
}
//Utente dummy x insert
$global_users['CMM_USERID'] = array('CMM_USERID' => 'CMM_USERID', 'ROLE' => '1');

define('SMARTY_DIR', '/http/lib/php_utils/smarty/');

$template = new Smarty();
 	//$template->debugging = true;
$template->error_reporting=E_ALL;
$remote_user_ = array(
 			"id" => strtoupper($_SERVER['REMOTE_USER']),
 			"center" => (isAdmin() ? $_SERVER['REMOTE_USER'] : substr($_SERVER['REMOTE_USER'], 0, 3)),
			"id_center" => (isAdmin() ? $_SERVER['REMOTE_USER'] : intval(substr($_SERVER['REMOTE_USER'], 0, 3))));
$template->assign("remote_user", $remote_user_);

$cracenters = getCRACenters();
$template->assign("cracenters", $cracenters);
// echo "<pre>";
// var_dump($template);
// echo "</pre>";
/**
 * PIERHD-8 update 12.12.2012
 * quando viene creato un nuovo centro tramite Account Management appaia un errore se il PM cerca di inserire nella colonna SITEID un id con dimensione superiore alla minima.
 * vmazzeo 21.12.2012
 */
$siteid_lenght_query = "SELECT MIN( DATA_LENGTH )/4 AS MIN_LENGHT from user_tab_columns where (table_name='{$study_prefix}_REGISTRATION' AND column_name='SITEID') OR (table_name='CMM_CENTER' and column_name='CODE')";
$siteid_lenght_conn=new query($conn);
$siteid_lenght_conn->exec($siteid_lenght_query);
$siteid_lenght_conn->get_row();
$siteid_lenght=$siteid_lenght_conn->row['MIN_LENGHT'];
$template->assign("siteid_lenght",$siteid_lenght);
$siteid_length_message = "This field is mandatory.</br>(Max {$siteid_lenght} characters allowed)";

$template->assign("icon_file", $icon_file);
$template->assign("mandatory_field_message", $mandatory_field_message);
$template->assign("siteid_length_message", $siteid_length_message);
$template->assign("only_number_field_message", $only_number_field_message);
$template->assign("max_lenght_fields_message", $max_lenght_fields_message);
$template->assign("email_field_message", $email_field_message);
$template->assign("confirm_center_change_status_message", $confirm_center_change_status_message);
$template->assign("confirm_center_disable_message", $confirm_center_disable_message);
$template->assign("confirm_center_change_status_question", $confirm_center_change_status_question);
$template->assign("confirm_center_change_status_yes_label", $confirm_center_change_status_yes_label);
$template->assign("confirm_center_change_status_no_label", $confirm_center_change_status_no_label);
$template->assign("connectivity_fail_label", $connectivity_fail_label);
$template->assign("user_creation_info_label", $user_creation_info_label);
$template->assign("popup_block_info_label", $popup_block_info_label);
$template->assign("user_confirm_disable_label", $user_confirm_disable_label);

$template->assign("user_textbox_editable_field", $user_textbox_editable_field);
$template->assign("user_textbox_not_editable_field", $user_textbox_not_editable_field);

$template->assign("request_uri", $_SERVER["REQUEST_URI"]);
$template->assign("is_submit", (isset($_POST['Submit']) && $_POST['Submit']!="") ? "true" : "false");

$template->assign("db_centers", $db_centers);
$template->assign("db_users", $db_users);

$template->assign("global_users", $global_users);

$template->assign("iso_country_list", $iso_country_list);
$template->assign("user_roles", $user_roles);
$template->assign("study_name",$study_name);
// Registro le funzioni per la gestione dei livelli di utenza
$template->assign('isAdmin', isAdmin());
$template->assign('isCRA', isCRA());
$template->assign('isPM', isPM());
//echo basename(__FILE__, ".php").".tpl");

$template->display("CMM_Management.tpl");
//var_dump($template);

?>
