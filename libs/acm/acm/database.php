<?php 

define ("ACT_INSERT", 1);
define ("ACT_MODIFY", 2);
define ("OLDPREFIX",'OLD_');
define ("FORM_SUBMIT","SUBMIT");
define ("FORM_BACK","BACK");
define ("NUMROWS","NROWS");
define ("FORM_NEWROW", "NEWROW");
define ("STORICO", 1); //STORICO=1 -> Storicizzazione abilitata, STORICO=0 -> Storicizzazione disabilitata

/*
 * TABELLE STORICO CON IN TESTA QUESTE COLONNE:
 * "ID_STORICO"        NUMBER(12),
 * MODDATE             DATE,
 * MODUSER             VARCHAR(200 CHAR),
 *
 * SEQUENCE:
 * CREATE SEQUENCE ACM_STORICO_ID
 * START WITH 1
 * MAXVALUE 9999999999999999999999999999
 * MINVALUE 1
 * NOCYCLE
 * NOCACHE
 * NOORDER;
 *
 *
 */
function _db_connect(){
	global $db_user;
	global $db_pwd;
	global $db_host;
	global $db_name;
	global $dbconn;
    if (!isset($dbconn) || $dbconn==null){
		putenv("NLS_LANG=AMERICAN_AMERICA.AL32UTF8");
		$db_user=rtrim($db_user, "\n");
		$db_user=rtrim($db_user, "\r");
		$db_host=rtrim($db_host, "\n");
		$db_host=rtrim($db_host, "\r");
		$db_pwd=rtrim($db_pwd, "\n");
		$db_pwd=rtrim($db_pwd, "\r");
		$dbconn=oci_connect($db_user,$db_pwd,$db_host) or die ("<hr>Errore connessione al DB $db_user<hr>");
	
		$Alter="ALTER SESSION SET NLS_DATE_FORMAT='DD-MM-YYYY'";
		$Stmt = oci_parse($dbconn,$Alter);
		oci_execute($Stmt,OCI_DEFAULT);
    }
	return $dbconn;	
}

##Da rirpistinare per debug DS&T
/*
function db_commit(){
	global $dbconn;
	oci_commit($dbconn);
}
*/
function db_close(){
	global $dbconn;
	oci_rollback($dbconn);
	oci_close($dbconn);
}

function _db_commit($conn){
	oci_commit($conn);
}

function _db_rollback($conn){
	oci_rollback($conn);
}

function _db_error_page($error = ''){
	global $db_type;
	
	$message = '<p>The site is currently not available due to technical problems. Please try again later. Thank you for your understanding.</p>';
	$message .= '<hr /><p><small>If you are the maintainer of this site, please check your database settings in the <code>settings.php</code> file and ensure that your hosting provider\'s database server is running. For more help, see the <a href="http://drupal.org/node/258">handbook</a>, or contact your hosting provider.</small></p>';

	if ($error && ini_get('display_errors')) {
		$message .= '<p><small>The '.$db_type.' error was: '.$error.'.</small></p>';
	}
	print($message);
	exit;
}

function db_commit(){
	_db_commit(_db_connect());
}

function db_rollback(){
	_db_rollback(_db_connect());
}

function db_query($SQL, $commit = false){
	$c = _db_connect();
	$q = db_prefix_tables($SQL);
	
	$q = preg_replace("/'/", "''", $q);

	//$q = mysql_real_escape_string($q,$c);
	$q = str_replace("''[","'",$q);
	$q = str_replace("]''","'",$q);
	//echo("<br/>$q<br/>");
	
	$stmt=oci_parse($c, $q);
	$rbool = oci_execute($stmt, OCI_DEFAULT);

	if ($rbool == false && err_can_show()){
		$err = oci_error($stmt);
		$etx = $err['message'];
		common_add_message("Errore QUERY: $q<br/>Errore Oracle: ".$etx, ERROR);
		_db_rollback($c);
		return FALSE;
	}
	if ($commit && ($stmt !== FALSE)){
		_db_commit($c);
	}	
	return $stmt;
}
function db_query_bind($SQL, $bind=null, $commit = false){
	$c = _db_connect();
	$q = db_prefix_tables($SQL);
	
	//$q = preg_replace("/'/", "''", $q);

	//$q = mysql_real_escape_string($q,$c);
	//$q = str_replace("''[","'",$q);
	//$q = str_replace("]''","'",$q);
	//echo($q);
	//common_add_message("Executing query: {$q}", INFO);
	$stmt=oci_parse($c, $q);
	foreach ($bind as $k=>$v){
		//oci_bind_by_name($stmt, ":$k", $v, -1);
		oci_bind_by_name($stmt, ":$k", $bind[$k], -1);
		//common_add_message("Binding :$k in $v", INFO);
	}
	$rbool = oci_execute($stmt, OCI_DEFAULT);

	if ($rbool == false && err_can_show()){
		$err = oci_error($stmt);
		$etx = $err['message'];
		common_add_message("Errore QUERY: $q<br/>Errore Oracle: ".$etx, ERROR);
		$bindtxt = "";
		$count = 0;
		foreach ($bind as $k=>$v){
			if ($count >=10){
				$count = 0;
				$bindtxt .= "<br/>";
			}
			$bindtxt .= "{$k}: {$v}, ";
			$count++;
		}
		common_add_message("Binding variables: $bindtxt", ERROR);
		_db_rollback($c);
		return FALSE;
	}
	//common_add_message("SQL: $q - Commit value: $commit", INFO);
	if ($commit && ($stmt !== FALSE)){
		_db_commit($c);
	}	
	return $stmt;
}
function db_query_bind_blob($SQL, $blobs, $commit = false){
	$c = _db_connect();
	$q = db_prefix_tables($SQL);
	
	$q = preg_replace("/'/", "''", $q);

	//$q = mysql_real_escape_string($q,$c);
	$q = str_replace("''[","'",$q);
	$q = str_replace("]''","'",$q);
	//echo($q);
	$stmt=oci_parse($c, $q);
	foreach ($blobs as $k=>$v){
		$lob[$k] = oci_new_descriptor($c, OCI_D_LOB);
		//echo "BINDING: $k->$v";
		oci_bind_by_name($stmt, ":$k", $lob[$k], -1, OCI_B_BLOB);
		$lob[$k]->WriteTemporary($v['DATA'],OCI_TEMP_BLOB);
		//$lob[$k]->write($v['DATA']);
	}
	/*
	foreach ($blobs as $k=>$v){
		echo "<br/>BLOB($k):<br/>$v<br/>";
	}
	*/
	$rbool = oci_execute($stmt, OCI_DEFAULT);
	/*
	foreach ($blobs as $k=>$v){
		if ($lob[$k]->save($v)){
	        //oci_commit($conn);
	        echo "Blob successfully uploaded\n";
	    }
	}
	*/
	if ($rbool == false && err_can_show()){
		$err = oci_error($stmt);
		$etx = $err['message'];
		common_add_message("Errore QUERY: $q<br/>Errore Oracle: ".$etx, ERROR);
		_db_rollback($c);
		return FALSE;
	}
	if ($commit && ($stmt !== FALSE)){
		_db_commit($c);
	}	
	foreach ($blobs as $k=>$v){
		//$lob[$k]->Close();
		oci_free_descriptor($lob[$k]);
	}
	return $stmt;
}

function db_nextrow($rs){
	$row = oci_fetch_assoc($rs);
	return $row;
}


function db_query_update($sql) {
	$result = db_query($sql,true);
	return ($result !== FALSE);
}
function db_query_update_bind($sql,$bind,$commit=true) {
	$result = db_query_bind($sql, $bind, $commit);
	return ($result !== FALSE);
}
function db_query_update_bind_blob($sql,$blobs) {
	$result = db_query_bind_blob($sql, $blobs, true);
	return ($result !== FALSE);
}

function db_prefix_tables($sql) {
  global $db_prefix;
  return strtr($sql, array('{' => $db_prefix, '}' => ''));
}

/**
 * Lock a table.
 */
function db_lock_table($table) {
  db_query('LOCK TABLES {'. db_escape_table($table) .'} WRITE');
}

/**
 * Unlock all locked tables.
 */
function db_unlock_tables() {
  db_query('UNLOCK TABLES');
}

/**
 * Check if a table exists.
 */
function db_table_exists($table) {
	$bind = array();
	$bind['TABNAME'] = $table;
	return (bool) db_nextrow(db_query_bind("SELECT table_name FROM user_tables where table_name = :TABNAME",$bind));
}

/**
 * Check if a column exists in the given table.
 */
function db_column_exists($table, $column) {
  return (bool) db_nextrow(db_query("SHOW COLUMNS FROM {". db_escape_table($table) ."} LIKE '". db_escape_table($column) ."'"));
}

function db_key_exists($table, $keycolumn, $keyvalue) {
	
}

function db_form_updatedb($table, $row, $action, $keycolumn, $commit=true, $notify = true, $history=true){
	$retval = false;
	if ($notify){
		db_mail_update($table, $row, $action);
	}
	switch ($action){
		case ACT_INSERT:
			$retval = db_insert_row($table,$row,$keycolumn,$commit);
			break;
		case ACT_MODIFY:
			unset($row['UTENTE']);
			unset($row['AZIENDA']);
			$retval = db_update_row($table,$row,$keycolumn,$commit,$history);
			break;
		default:
			if (err_can_show()){
				common_add_message("Azione non riconosciuta: $action", ERROR);
			}
			break;
	}
	return $retval;
}
function db_form_updatedb_blob($table, $row, $blobs, $action, $keycolumn, $notify = true){
	$retval = false;
	if ($notify){
		db_mail_update($table, $row, $action);
	}
	switch ($action){
		case ACT_INSERT:
			$retval = db_insert_row_blob($table,$row,$blobs,$keycolumn);
			break;
		case ACT_MODIFY:
			unset($row['UTENTE']);
			unset($row['AZIENDA']);
			$retval = db_update_row_blob($table,$row,$blobs,$keycolumn);
			break;
		default:
			if (err_can_show()){
				common_add_message("Azione non riconosciuta: $action", ERROR);
			}
			break;
	}
	return $retval;
}

function db_insert_row($table,$row,$keycolumn,$commit=true){
	$retval = true;

	$koldarray = array();
	if (is_array($keycolumn)){
		foreach ($keycolumn as $k){
			$koldarray[] = OLDPREFIX.$k;
		}
	}else{
		$koldarray[] = OLDPREFIX.$keycolumn;
	}
	
	$SQL = "INSERT INTO $table (";
	$i = 0;
	foreach(array_keys($row) as $key){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && !in_array($key,$koldarray)){
			if ($i>0){
				$SQL .= ",";
			}
			$SQL .= $key;
			$i++;
		}
	}
	$SQL .= ") VALUES ( ";
	$i = 0;
	$bind = array();
	foreach(array_keys($row) as $key){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && !in_array($key,$koldarray)){
			if ($i>0){
				$SQL .= ", ";
			}
			//$SQL .= "'[{$row[$key]}]'";
			if ($row[$key] === "" || $row[$key] === false){
				$SQL .= "NULL";
			}else{
				if (strstr($row[$key],"[SYSDATE]")){
					$SQL .= str_replace("[SYSDATE]","SYSDATE",$row[$key]);
					//unset($row[$key]);
				}else if (strstr($row[$key],".NEXTVAL") && common_beginsWith($row[$key],"[") && common_endsWith($row[$key],"]")) {
					$SQL .= str_replace("[","",str_replace("]","",$row[$key]));
				}else {
					$SQL .= ":{$key}";
					$bind[$key] = $row[$key];
				}
			}
			$i++;
		}
	}
	$SQL .= " )";
	//echo "<br/>".$SQL."<br/>";
	$retval = db_query_update_bind($SQL,$bind,$commit);
	return $retval;
}

function db_insert_row_blob($table,$row, $blobs,$keycolumn){
	$retval = true;
	$SQL = "INSERT INTO $table (";
	$i = 0;
	$debug = false;
	foreach(array_keys($row) as $key){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && $key != OLDPREFIX.$keycolumn){
			if (!is_object($row[$key])){
				if ($i>0){
					$SQL .= ",";
				}
				$SQL .= $key;
			}else{
				//Gestisco comunque i BLOBS!
				$blobs[$key]['DATA'] = $row[$key]->load();
				$blobs[$key]['NAME'] = $row[$key."_FNAME"];
				//$debug = true;
			}
			$i++;
		}
	}
	//$row = array_diff_key($row,$blobs);
	//foreach ($blobs as $key=>)
	foreach($blobs as $key=>$val){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && $key != OLDPREFIX.$keycolumn){
			if ($i>0){
				$SQL .= ",";
			}
			$SQL .= $key;
			unset($row[$key]);
			//unset($row[$key."_FNAME"]);
			$i++;
		}
	}
	$SQL .= ") VALUES (";
	$i = 0;
	foreach(array_keys($row) as $key){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && $key != OLDPREFIX.$keycolumn){
			if ($i>0){
				$SQL .= ",";
			}
			//$SQL .= "'[{$row[$key]}]'";
			//if (!is_object($row[$key])){
				if ($row[$key] === "" || $row[$key] === false){
					$SQL .= "NULL";
				}else{
					$SQL .= "'[{$row[$key]}]'";
				}
			//}else{
			//	$blobs[$key] = 
			//}
			$i++;
		}
	}
	foreach($blobs as $key=>$val){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && $key != OLDPREFIX.$keycolumn){
			if ($i>0){
				$SQL .= ",";
			}
			if ($val['DATA'] === "" || $val['DATA'] === false){
				$SQL .= "NULL";
			}else{
				$SQL .= ":$key";
			}
			$i++;
		}
	}
	$SQL .= ")";
	if ($debug){
		echo "<pre>";
		//print_r($row);
		//print_r($blobs);
		echo "</pre>";
		echo "<hr/>$SQL<hr/>";
		die("DEBUG!");
	}
	$retval = db_query_update_bind_blob($SQL,$blobs);
	return $retval;
}

function db_update_row($table,$row,$keycolumn,$commit=true, $history=true){
	$retval = true;

    $bind = array();
	
	$karray = array();
	$koldarray = array();
	if (is_array($keycolumn)){
		foreach ($keycolumn as $k){
			$karray[] = $k;
			if ($row[OLDPREFIX.$k]){
				$bind[OLDPREFIX.$k] = $row[OLDPREFIX.$k];
			}else{
				$bind[OLDPREFIX.$k] = $row[$k];
			}
			$koldarray[] = OLDPREFIX.$k;
		}
	}else{
		$karray[] = $keycolumn;
		$koldarray[] = OLDPREFIX.$keycolumn;
		if ($row[OLDPREFIX.$keycolumn]){
			$bind[OLDPREFIX.$keycolumn] = $row[OLDPREFIX.$keycolumn];
		}else{
			$bind[OLDPREFIX.$keycolumn] = $row[$keycolumn];
		}
	}
	
	$SQL = "UPDATE $table SET ";
	$i = 0;
	foreach(array_keys($row) as $key){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && !in_array($key,$koldarray)){
			if ($i>0){
				$SQL .= ",";
			}
			$SQL .= $key;
			$SQL .= " = ";
			if ($row[$key] === "" || $row[$key] === false){
				$SQL .= "NULL";
			}else{
				if (strstr($row[$key],"[SYSDATE]")){
					$SQL .= str_replace("[SYSDATE]","SYSDATE",$row[$key]);
					//unset($row[$key]);
				}else{
					$SQL .= ":{$key}";
					$bind[$key] = $row[$key];
				}
			}
			$i++;
		}
	}
	$SQL .= " WHERE ";
	$tmpand = "";
    $whereclause = "";
	foreach ($karray as $k){
        $whereclause .= $tmpand.$k." = :".OLDPREFIX.$k." ";
		$tmpand = " AND ";
	}
    $SQL .= $whereclause;
	//common_add_message($SQL,INFO);
    if (STORICO && $history){
        //Storico
        $hsql = 'INSERT INTO {S_'.$table.'} (SELECT acm_storico_id.nextval,SYSDATE,\''.$_SERVER['REMOTE_USER'].'\',t.* FROM '.$table.' t WHERE '.$whereclause.')'; //Inserimento in tabella storico S_$table
        if (!db_query_update_bind($hsql,$bind,$commit)){
            common_add_message("Inserimento in tabella storico fallito!",ERROR);
        }
    }
    $retval = db_query_update_bind($SQL,$bind,$commit);
    return $retval;
}
function db_update_row_blob($table,$row, $blobs, $keycolumn){
	$retval = true;
	$SQL = "UPDATE $table SET ";
	$i = 0;
	//$bind = array();
	foreach(array_keys($row) as $key){
		if (is_object($row[$key])){
			$blobs[$key]['DATA'] = $row[$key]->load();
			$blobs[$key]['NAME'] = $row[$key."_FNAME"];
		}
	}
	foreach ($blobs as $key=>$val){
		unset($row[$key]);
		unset($row[$key."_FNAME"]);
	}
	foreach(array_keys($row) as $key){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && $key != OLDPREFIX.$keycolumn){
			//if (!is_object($row[$key])){
				if ($i>0){
					$SQL .= ",";
				}
				$SQL .= $key;
				$SQL .= " = ";
				if ($row[$key] === "" || $row[$key] === false){
					$SQL .= "NULL";
				}else{
					$SQL .= "'[{$row[$key]}]'";
				}
			//}else{
			//	//Gestisco comunque i BLOBS!
			//	$blobs[$key]['DATA'] = $row[$key]->load();
			//	$blobs[$key]['NAME'] = $row[$key."_FNAME"];
			//}
			$i++;
		}
	}
	foreach($blobs as $key=>$val){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && $key != OLDPREFIX.$keycolumn){
			if ($i>0){
				$SQL .= ",";
			}
			$SQL .= $key;
			$SQL .= " = ";
			if ($val['DATA'] === "" || $val['DATA'] === false){
				$SQL .= "NULL";
			}else{
				//$SQL .= "EMPTY_BLOB()";
				$SQL .= ":$key";
			}
			$i++;
			$SQL .= ", {$key}_FNAME = '[{$val['NAME']}]'";
		}
	}
	$SQL .= " WHERE ".$keycolumn." = '[".$row[OLDPREFIX.$keycolumn]."]'";
	/*
	$i = 0;
	if (count($blobs)){
		$SQL .= " returning ";
		foreach($blobs as $key=>$val){
			if ($key != FORM_SUBMIT && $key != OLDPREFIX.$keycolumn){
				if ($i>0){
					$SQL .= " and ";
				}
				$SQL .= $key;
				$SQL .= " into ";
				$SQL .= ":$key";
				
			}
			$i++;
		}
	}
	*/
	$retval = db_query_update_bind_blob($SQL,$blobs);
	return $retval;
}
function db_update_row_NEW($table,$row,$keycolumn){
	$retval = true;
	$SQL = "UPDATE $table SET ";
	$i = 0;
	$bind = $row;
	foreach(array_keys($row) as $key){
		if ($key != FORM_SUBMIT && $key != FORM_BACK && $key != OLDPREFIX.$keycolumn){
			if ($i>0){
				$SQL .= ",";
			}
			$SQL .= $key;
			$SQL .= " = ";
			if ($row[$key] === "" || $row[$key] === false){
				$SQL .= "NULL";
				unset($bind[$key]);
			}else{
				$SQL .= " :$key ";
			}
			$i++;
		}
	}
	$SQL .= " WHERE ".$keycolumn." = :".OLDPREFIX.$keycolumn."";
	$retval = db_query_update_bind($SQL, $bind);
	return $retval;
}

function db_form_updatedb_multi($table, $arows, $keycolumn, $notify = true){
	$retval = false;
	$nrows = $arows[NUMROWS];
	unset ($arows[NUMROWS]);
	$splrows = db_form_explode_rows($arows, $nrows);
	for ($i = 1; $i<=$nrows; $i++){ //1-based!!!
		$row = $splrows[$i];
		$action = ACT_INSERT;
		if ($row[$keycolumn] && strlen($row[$keycolumn]) >0 ){
			$action = ACT_MODIFY;
		}
		//die(strlen($row[$keycolumn])."---".$row[$keycolumn]."---".$keycolumn);
		if ($notify){
			db_mail_update($table, $row, $action);
		}
		switch ($action){
			case ACT_INSERT:
				$retval = db_insert_row($table,$row,$keycolumn);
				break;
			case ACT_MODIFY:
				unset($row['UTENTE']);
				unset($row['AZIENDA']);
				$retval = db_update_row($table,$row,$keycolumn);
				break;
			default:
				if (err_can_show()){
					common_add_message("Azione non riconosciuta: $action", ERROR);
				}
				break;
		}
	}
	return $retval;
}

function db_form_explode_rows($post, $nr){
	$rows = array();
	$keys = array_keys($post);
	/*
	for ($i=1;$i<=$nrows;$i++){
		foreach ($keys as $k){
			if (common_endsWith($keys,$i)){
				//Appendi campo...
			}
		}
	}
	*/
	foreach ($keys as $k){
		$spl = explode("_",$k);
		//$idx = $spl[count($spl)-1]+0;
		$idx = array_pop($spl);
		if ($idx > 0){
			$rows[$idx][implode("_",$spl)] = $post[$k];
		}else{
			//common_add_message("Nessuna riga per campo: $k", WARNING);
		}
	}
	return $rows;
}

function db_getmaxvalue($rows, $count, $field){
	$retval = false;
	for ($i = 1; $i<=$count; $i++){
		$val = $rows[$i][$field];
		if ($val && is_numeric($val)){
			if (!$retval){
					$retval = $val;
			}else{
				if ($val > $retval){
					$retval = $val;
				}
			}
		} 
	}
	return $retval;
}

function db_getmaxcharvalue($rows, $count, $field){
	$retval = false;
	for ($i = 1; $i<=$count; $i++){
		$val = $rows[$i][$field];
		if ($val){
			if (!$retval){
					$retval = $val;
			}else{
				if ($val > $retval){
					$retval = $val;
				}
			}
		} 
	}
	return $retval;
}

function db_delete_rows($table, $whereclause, $final = false){
	if (!$whereclause || $whereclause == ""){
		if (err_can_show()){
			common_add_message("Nessuna clausola WHERE in cancellazione.", ERROR);
		}
		return true;
	}
    $SQL = "";
	if (!$final){
		$SQL .= "UPDATE {".$table."} SET DELETED=1 WHERE ".$whereclause." ";
	}else{
		$SQL .= "UPDATE {".$table."} SET DELETED_DEF=1 WHERE ".$whereclause." ";
	}
	$retval = db_query_update($SQL);
	return true;
}

function db_update_rows($table, $whereclause, $updateclause){
	if (!$whereclause || $whereclause == ""){
		if (err_can_show()){
			common_add_message("Nessuna clausola WHERE in update.", ERROR);
		}
		return true;
	}
    if (STORICO){
        //Storico
        $SQL = "";
        $SQL .= "SELECT * FROM {".$table."} WHERE ".$whereclause." ";
        $res = db_query($SQL);
        print_r($res);
        die();
    }
    $SQL = "";
	$SQL .= "UPDATE {".$table."} SET {$updateclause} WHERE ".$whereclause." ";
	$retval = db_query_update($SQL);
	return true;
}

function db_getmaxdbvalue($table, $field, $where = null){
	$SQL = "SELECT $field FROM {$table} ";
	if ($where != null){
		$SQL .= " where $where";
	}
	$SQL .= " order by $field desc";
	//echo $SQL;
	$row = db_nextrow(db_query($SQL));
	//print_r($row);
	return $row[$field];
}

function db_mail_update($table,$row,$action){
	global $u;
	/*
	$headers = 'From: noreply@cineca.it' . "\n" .
    'Reply-To: noreply@cineca.it';
	$az = "INSERT";
	if ($action == ACT_MODIFY){
		$az = "MODIFY";
	}
	$msg = "Modifica al sistema:\n";
	//$msg.= "Tabella: $table - Azione: $az\n";
	$msg.= "Tabella: $table - Azione: $az\n";
	$mdata = "";
	$oldrow = false;
	if ($action == ACT_MODIFY){
		//Vecchi valori
		$oldrow = db_nextrow(db_query("SELECT * FROM {$table} WHERE ID = '[".$row['ID']."]'"));
	}
	//Nuovi valori
	$msg.= "\n";
	$msg.= "ID Modificato: {$row['OLD_ID']} --> {$row['ID']}\n";
	$loggeduser = "";
	if (is_object($u)){
		$loggeduser = $u->username;
	}
	$msg.= "Utente: {$loggeduser}";
	if ($oldrow){
		$msg .= "/ {$oldrow['UTENTE']}\n";
	}
	$msg.= "\n";
	foreach ($row as $k=>$v){
		if (!is_object($v)){
			if ($k != "OLD_ID" && $k != "SUBMIT"){
				if ($oldrow){
					if ($oldrow[$k] != $v){
						$mdata.= "$k:\t\t{$oldrow[$k]} --> $v\n";
					}
				}else{
					$mdata.= "$k:\t\t$v\n";
				}
			}
		}
	}
	$msg .= $mdata;
	$msg.= "\nFINE.";
	if ($mdata){
		mail("dario.mengoli@gmail.com", "[MODIFICA]" , $msg, $headers );
	}
	*/
}

function db_mail_update_old($table,$row,$action){
	/*
	$headers = 'From: noreply@cineca.it' . "\n" .
    'Reply-To: noreply@cineca.it';
	$az = "INSERT";
	if ($action == ACT_MODIFY){
		$az = "MODIFY";
	}
	$msg = "Modifica al sistema :\n";
	//$msg.= "Tabella: $table - Azione: $az\n";
	$msg.= "Tabella: $table - Azione: $az\n";
	if ($action == ACT_MODIFY){
		//Vecchi valori
		$msg.= "Vecchi valori:\n";
		$oldrow = db_nextrow(db_query("SELECT * FROM {$table} WHERE ID = '[".$row['ID']."]'"));
		foreach ($oldrow as $k=>$v){
			if (!is_object($v)){
				$msg.= "$k:\t\t$v\n";
			}
		}
		$msg.= "\n";
	}
	//Nuovi valori
	$msg.= "Nuovi valori:\n";
	foreach ($row as $k=>$v){
		if (!is_object($v)){
			$msg.= "$k:\t\t$v\n";
		}
	}
	$msg.= "\nFINE.";
	mail("dario.mengoli@gmail.com", "[MODIFICA]" , $msg, $headers );
	*/
}

function db_getnextsequencevalue($table,$seqname=false){
	$seq = $table."_SEQ";
	if ($seqname){
		$seq=$seqname;
	}
	$SQL = "SELECT {$seq}.nextval as NEXT FROM DUAL";
	$row = db_nextrow(db_query($SQL));
	print_r($row);
	return $row['NEXT'];
}

?>
