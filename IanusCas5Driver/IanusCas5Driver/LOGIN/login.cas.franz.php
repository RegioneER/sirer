<?php


$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
if ($language=='') $language='en';
$language=strtolower($language);

//Franz 26012017 Inizio modifica

if ( preg_match("/\/portal\//",$_GET['service'])){
	$urlportal=str_replace("https://".$_SERVER['HTTP_HOST']."/portal/",'',$_GET['service']); //Franz 26012017 modifica
	$urlportal=preg_replace("/\/index.php.*$/",'',$urlportal); //Franz 26012017 modifica
	$urlportal=preg_replace("/\/$/",'',$urlportal); //Franz 26012017 modifica
	die ($_SERVER['HTTP_HOST'].' = '.$urlportal.' = '.$_GET['service']);
}

$urlserv=str_replace("https://".$_SERVER['HTTP_HOST']."/study/",$_GET['service']);
$urlserv=preg_replace("/\/index.php.*$/",'',$urlserv);
$urlserv=preg_replace("/\/$/",'',$urlserv);

if ($urlserv !=''){
	if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login_template_cas_".$urlserv.".html")) $template=file_get_contents($_SERVER['DOCUMENT_ROOT']."/authzssl/login_template_cas_".$urlserv.".html");
	else $template=file_get_contents("/http/lib/IanusCasDriver/LOGIN/template/login_template.html");
}else {//Franz 26012017 Fine modifica, inizio else modifica, codice precedente alla modifica
	if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login_template_cas.html")) $template=file_get_contents($_SERVER['DOCUMENT_ROOT']."/authzssl/login_template_cas.html");
	else $template=file_get_contents("/http/lib/IanusCasDriver/LOGIN/template/login_template.html");
}////Franz 26012017 Fine else modifica

if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login.css")) {
	$template=str_replace("<!--custom_css-->", "<link rel=\"stylesheet\" href=\"/authzssl/login.css\" />", $template);
}
if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login-logo.png")) {
	$template=str_replace("<!--login_logo-->", "<div class=\"center\"><img src=\"/authzssl/login-logo.png\"/></div>", $template);
}

$commonMessageFile="/http/lib/IanusCasDriver/LOGIN/messages_{$language}.inc";
$defaultMessageFile="/http/lib/IanusCasDriver/LOGIN/messages_en.inc"; //Questa è la lingua di default!
$customMessageFile=$_SERVER['DOCUMENT_ROOT']."/authzssl/messages_{$language}.inc";
if (file_exists($customMessageFile)) {
	include_once $customMessageFile;
}
else {
	if (file_exists($commonMessageFile)) {
		include_once $commonMessageFile;
	}
	else {
		include_once $defaultMessageFile; 
	}
}
if ($_SERVER['DOCUMENT_ROOT']."/authzssl/login-copyright.html") {
	$copyright_file_content=file_get_contents($_SERVER['DOCUMENT_ROOT']."/authzssl/login-copyright.html");
}
else {
	$copyright_file_content=file_get_contents("/http/lib/IanusCasDriver/LOGIN/login-copyright.html");
}
if (!isset($_POST) || count($_POST)==0){
	
	if (strtoupper($language) == strtoupper("it")){$language_show='IT';}else {$language_show='EN';}
	$sql_get_msg_ts="select MESSAGGIO_LOGIN_{$language_show} as message from CAS_SERVICES where 
			upper(URL)='".strtoupper($_SERVER['HTTP_HOST'])."'
			and sysdate between messaggio_from_dt and messaggio_to_dt";
	$sql2=new DriverIanusSql($DriverIanusConnection);
	if ($sql2->getRow($sql_get_msg_ts)){
	$loginMsgOut=$sql2->row['MESSAGE'];
		ini_set( 'date.timezone', 'Europe/Rome' );
		$template = preg_replace("/<!-- out_code -->/i", "<center><div style='min-width:340px;width:50% !important' class='alert alert-warning'>".$loginMsgOut."</div></center>", $template);
	}
	
	$cookieSpecFile="cookiespec_".strtolower($language_show).".html";
	$tagCookie=file_get_contents("/http/lib/DriverIanus/cookieConsent/".$cookieSpecFile);
	
	$cssCookie='<link rel="stylesheet" type="text/css" href="/authzssl/cookieConsentCss"/>';
	

	$template=preg_replace("!</head>!i", $cssCookie."</head>", $template);
	$template=preg_replace("!</body>!i", $tagCookie."</body>", $template);
	
	$loginUrl=$_GET['loginCallBack'];
	$form=file_get_contents("/http/lib/IanusCasDriver/LOGIN/template/login_form.html");
	$form=str_replace("__service__", $_GET['service'], $form);
	$form=str_replace("__lt__", $_GET['lt'], $form);
	$form=str_replace("__loginCallBack__", $_GET['loginCallBack'], $form);
	$form=str_replace("__execution__", $_GET['execution'], $form);
	$template=str_replace("__widget_content__", $form, $template);
	$template=str_replace("__title_page__", $messages['__title_page__'], $template);
	$template=str_replace("<!--copyright-->", $copyright_file_content, $template);
	$template=str_replace("__welcome_login_message__", $messages['__welcome_login_message__'], $template);
	$template=str_replace("__username__", $messages['__username__'], $template);
	$template=str_replace("__password__", $messages['__password__'], $template);
	$template=str_replace("__login_button_label__", $messages['__login_button_label__'], $template);
	$template=str_replace("__forgot_password__", $messages['__forgot_password__'], $template);
	$template=str_replace("__forgot_username__", $messages['__forgot_username__'], $template);
	
	if (isset($_GET['loginError']) && $_GET['loginError']=='true'){
		$template=str_replace("__error_message__", "<div class=\"alert alert-danger\">".$messages['__error_message__']."</div>", $template);
	}else {
		$template=str_replace("__error_message__", '', $template);
	}
	
}else {
	require_once '/http/lib/IanusCasDriver/ApacheCrypt.inc.php';
	if (CheckPassword($_POST['username'], $_POST['password'], false)){
		$sso=false;
	}else {
		$sso=true;
		$sso=CheckPassword($_POST['username'], $_POST['password'], true);
		
	}
	$loginUrl=$_POST['loginCallBack']."?service=".urlencode($_POST['service']);
	unset ($_POST['loginCallBack']);
	unset ($_POST['service']);
	if (!$sso) $_POST['username'].="@".$_SERVER['HTTP_HOST'];
	$form="<form id='login_form' method='post' name='login' action='$loginUrl' enctype='application/x-www-form-urlencoded'>";
	foreach ($_POST as $key=>$val){
		if ($key=='submit') $form.="<noscript><input type='submit' name='_{$key}' value='$val'/></noscript>";
		else $form.="<input type='hidden' name='$key' value='$val'/>";
	}
	$form.="</form>";
	$loading="<div style=\"padding:4px\"><h2 style=\"padding-right:60px;float:right;\">".$messages['__processing__']."...</h2><i class=\"fa fa-spinner fa-spin fa-4x\"></i> </div>";
	$content=$form.$loading;
	
	$template=str_replace("__widget_content__", $content, $template);
	
	$template.="<script>
		$(document).ready(function(){
			$('#login_form').submit();
		});
	</script>";
}




function CheckPassword($userid, $password, $sso=false){
	$tb_utenti="UTENTI";
	$userid=strtoupper($userid);
	$caseSensitivePassword=$password;
	$password=strtoupper($password);
	$conn=new LoginDBConnection();
	$sql=new LoginSql($conn);
	if (!$sso){
		$sql_query="select count(*) as C from CAS_USERS where upper(username)=upper('{$userid}@{$_SERVER['SERVER_NAME']}')";
		if ($sql->getRow($sql_query)){
			if ($sql->row['C']==0) return false;
		}
		/*$sql_query="select count(*) as C from CAS_USERS where upper(username)=upper('$userid')";
		if ($sql->getRow($sql_query)){
			if ($sql->row['C']>0) return false;
		}*/
		
	}
	
	if (preg_match("!^SHIBPROBE!i",$userid)){
		$db_password='$apr1$rHf.....$mSWdreIYc6blwACyL2bXD/';
		$seeds=split('\$', $db_password);
		$seed=$seeds[2];
		if (MD5AdminMd5Crypt($password, $seed)==$db_password){
			return true;
		}
		else {
			return false;
		}
	}
	if ($sso){
		$sql_query="select password from CAS_USERS where upper(username)=upper('$userid')";
	}
	else $sql_query="select password from $tb_utenti where upper(userid)=upper('$userid')";
	if ($sql->getRow($sql_query)){
		
		$db_password=$sql->row['PASSWORD'];
		$seeds=split('\$', $db_password);
		
		$seed=$seeds[2];
		if($password!=trim($password)){
			return false;
		}
		elseif ($password==$db_password || crypt($password,substr($password, 0,2))==$db_password || MD5AdminMd5Crypt($caseSensitivePassword, $seed)==$db_password) {
			$new_pass=MD5AdminMd5Crypt($password);
			$values['PASSWORD']=$new_pass;
			$pk['USERID']=$userid;
			$sql_length_pass="select char_length from user_tab_cols where column_name='PASSWORD' and table_name='UTENTI'";
			$sql = new LoginSql ($conn);
			$sql->getRow ($sql_length_pass);
			if ($sql->row['CHAR_LENGTH']<40){
				$sql_alter_tb="alter table utenti modify PASSWORD varchar2(40 char)";
				$sql->doCommand($sql_alter_tb);
			}
			if($sso){
				$sql->Update($values, "CAS_USERS", $pk);
			}
			else $sql->Update($values, "UTENTI", $pk);
			$conn->commit();
			return true;
		}
		elseif (MD5AdminMd5Crypt($password, $seed)==$db_password){
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}



class LoginDBConnection {
	protected $resource;

	public $Error_Launched=false;

	public function __construct($user=null, $pass=null, $host=null){
		if (!isset($user)){
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
			$user=$Ora_Userid;
			$pass=$Ora_Pass;
			$host=$Ora_Host;
		}
		try {
			$this->resource=oci_connect($user, $pass, $host) or die("<h1>Problema connessione DB</h1> <a href=\"javascript: history.go(-1);\" >effettuare nuovamente il login</a>");
		} catch (Exception $e) {
			throw new Exception("Errore connessione DB", 1);
		}
	}

	public function commit(){
		try {
			oci_commit($this->resource);
			return true;
		} catch (Exception $e) {
			throw new Exception("Errore Commit", 2);
		}
	}

	public function close(){
		oci_close($this->resource);
	}

	public function getConnection(){
		return $this->resource;
	}

	public function rollback(){
		try {
			oci_rollback($this->resource);
		} catch (Exception $e) {
			throw new Exception("Errore Rollback", 3);
		}
	}

	function __destruct() {
		if ($this->resource){
			try {
				oci_rollback($this->resource);
			} catch (Exception $e) {
				throw new Exception("Errore Rollback in chiusura", 4);
			}
		}
	}


}


class LoginSql {

	protected $Conn;
	protected $Stmt;
	protected $Row;
	protected $Sql_Str;
	protected $numRows;
	protected $numCols;
	protected $colsType;
	protected $colsLength;
	protected $colsName;
	protected $result;
	protected $idx;
	public $insert_errors;

	public function __construct(LoginDBConnection $db) {
		$this->Conn = $db;
	}

	public function SetSql($sql_str) {
		$this->Sql_Str = $sql_str;
	}

	public function getSql() {
		return $this->Sql_Str;
	}

	public function Exec($sql_str = null, $bind_array=null) {
		if (isset ( $sql_str )) {
			$this->Sql_Str = $sql_str;
		}
		if (! isset ( $this->Sql_Str )) {
			throw new DriverIanusSqlException ( "Query non definita", 1 );
		}

		$this->Parse();
		// Aggiunto il binding all'Exec
		// 26/08/2011 Verrocchio
		if (isset($bind_array) && is_array($bind_array)) foreach ($bind_array as $key=>$val) {
			ocibindbyname($this->Stmt, ":{$key}", $bind_array[$key],-1);
		}

		$this->ExecuteSelectStmt();
	}

	public function getRow($sql_str = null) {
		if (isset ( $sql_str ))
			$this->Exec ( $sql_str );
		if ($this->idx >= $this->numRows)
			return false;
		foreach ( $this->result as $key => $val ) {
			$this->Row [$key] = $val [$this->idx];
		}
		$this->idx+=1;
		return $this->Row;
	}

	function getRowByIndex($index) {
		if ($index>$this->numRows)  return false;
		else {
			foreach ($this->result as $key => $val) {
				$this->Row[$key]=$this->result[$key][$index];
			}
			return true;
		}
	}

	public function __get($name_var) {
		switch ($name_var) {
			case "Row" :
				return $this->{$name_var};
				break;
			case "row" :
				return $this->Row;
				break;
			case "numCols" :
				return $this->{$name_var};
				break;
			case "numRows" :
				return $this->{$name_var};
				break;
			case "colsName" :
				return $this->{$name_var};
				break;
			case "colsType" :
				return $this->{$name_var};
				break;
			case "colsLength" :
				return $this->{$name_var};
				break;
			case "Stmt" :
				return $this->{$name_var};
				break;
			default :
				throw new Exception ( "Errore proprietà inesistente", "10" );
				break;
		}
	}

	public function getPk($tb_name) {
		$tb_name=strtoupper($tb_name);
		$sql_query="select COLUMN_NAME from user_cons_columns where constraint_name=(select constraint_name from user_constraints where TABLE_NAME='{$tb_name}' and CONSTRAINT_TYPE='P')";
		$this->Exec($sql_query);
		while ($this->getRow()) {
			$pk[$this->row['COLUMN_NAME']]=true;
		}
		return $pk;
	}

	public function getTbStruct($tb_name, $array_assoc=null) {
		$tb_name=strtoupper($tb_name);
		$pk=$this->getPk($tb_name);
		$sql_query="select upper(COLUMN_NAME) as column_name, DATA_TYPE, CHAR_LENGTH from USER_TAB_COLUMNS where table_name='{$tb_name}'";
		$this->Exec($sql_query);
		while ($this->getRow()) {
			if (isset($array_assoc)) {
				if (isset($array_assoc[$this->row['COLUMN_NAME']])) $data_tb[$this->row['COLUMN_NAME']]['VALUE']=$array_assoc[$this->row['COLUMN_NAME']];
			}
			if ($pk[$this->row['COLUMN_NAME']]) $data_tb[$this->row['COLUMN_NAME']]['PK']=true;
			else $data_tb[$this->row['COLUMN_NAME']]['PK']=false;
			switch($this->row['DATA_TYPE']) {
				case 'VARCHAR2':
					$data_tb[$this->row['COLUMN_NAME']]['TYPE']=SQLT_CHR;
					break;
				case 'NUMBER':
					$data_tb[$this->row['COLUMN_NAME']]['LEN']=-1;
					$data_tb[$this->row['COLUMN_NAME']]['TYPE']=SQLT_LNG;
					break;
				case 'CLOB':
					$data_tb[$this->row['COLUMN_NAME']]['LEN']=-1;
					$data_tb[$this->row['COLUMN_NAME']]['TYPE']=SQLT_CLOB;
					break;
				case 'BLOB':
					$data_tb[$this->row['COLUMN_NAME']]['LEN']=-1;
					$data_tb[$this->row['COLUMN_NAME']]['TYPE']=SQLT_BLOB;
					break;
			}
			$data_tb[$this->row['COLUMN_NAME']]['ORA_TYPE']=$this->row['DATA_TYPE'];
			if ($this->row['DATA_TYPE']=='VARCHAR2') $data_tb[$this->row['COLUMN_NAME']]['LEN']=$this->row['CHAR_LENGTH'];
		}
		return $data_tb;
	}

	protected static function prepeare_bind($field_name, $value) {
		if (
				preg_match ( "/^to_date/i", $value )
				|| preg_match ( "/sysdate/i", $value )
				|| preg_match ( "/nextval$/i", $value )
				|| preg_match ( "/currval$/i", $value )
		) {
			$ret['field_name']=$field_name;
			$ret['value']=$value;
			$ret['binded']=false;
		}
		else {
			$ret['field_name']=$field_name;
			$ret['value']=":{$field_name}";
			$ret['binded']=true;
		}
		return $ret;
	}

	public static function Upper($array) {
		foreach ($array as $key=>$val) {
			if (strtoupper($key)!=$key) {
				$key=strtoupper($key);
			}
			$ret_array[$key]=$val;
		}
		return $ret_array;
	}
	public static function BuildWhereBinded($pk, $data_tb) {
		foreach ($pk as $key=>$val) {
			$binded=LoginSql::prepeare_bind($field_name, $valore);
			$pk_[$key]['BINDED']=$binded['binded'];
			$pk_[$key]['VALUE']=$val;
			$pk_[$key]['TYPE']=$data_tb[$key]['TYPE'];
			$pk_[$key]['LEN']=$data_tb[$key]['LEN'];
			$pk_where.="{$key}=:PK_B_{$key}_ and ";
		}
		$pk_where=rtrim($pk_where, " and ");
		if ($pk_where!='') $pk_where="where $pk_where";
		$ret['PK_']=$pk_;
		$ret['WhereString']=$pk_where;
		return $ret;
	}

	public function Save($array_assoc, $table_name) {
		$table_name=strtoupper($table_name);
		$values_array=LoginSql::Upper($array_assoc);
		$data_tb=$this->getTbStruct($table_name, $values_array);
		foreach ($data_tb as $field=>$val) {
			if ($data_tb[$field]['PK']) {
				$pk[$field]=$data_tb[$field]['VALUE'];
			}
		}
		$retpk=LoginSql::BuildWhereBinded($pk, $data_tb);
		$pk_where=$retpk['WhereString'];
		$pk_=$retpk['PK_'];
		$this->SetSql("select count(*) as conto from {$table_name} $pk_where");
		$this->Stmt=oci_parse($this->Conn->getConnection(), $this->Sql_Str);
		if (!$this->Stmt) {
			throw new DriverIanusSqlException("Errore parse oracle", "7");
		}
		foreach ($pk_ as $key=>$val) {
			if ($pk_[$key]['BINDED']) {
				if (!oci_bind_by_name($this->Stmt, ":PK_B_{$key}_", $pk_[$key]['VALUE'], $retpk['PK_'][$key]['LEN'], $retpk['PK_'][$key]['TYPE'])) {
					throw new DriverIanusSqlException("Errore Binding Variabili", "10");
				}
			}
		}
		if (!oci_execute($this->Stmt,OCI_DEFAULT)) {
			throw new DriverIanusSqlException("Errore Execute", "14");
		}
		$row = oci_fetch_assoc($this->Stmt);
		if ($row['CONTO']>0) {
			return $this->Update($array_assoc, $table_name, $pk);
		}else {
			return $this->Insert($array_assoc, $table_name);
		}
	}

	public function Update($array_assoc, $table_name, $pk) {
		$table_name=strtoupper($table_name);
		$values_array=LoginSql::Upper($array_assoc);
		$data_tb=$this->getTbStruct($table_name, $values_array);
		//$blob = oci_new_descriptor($this->Conn->getConnection(), OCI_D_LOB);
		foreach ( $values_array as $field_name => $valore ) {
			$binded=LoginSql::prepeare_bind($field_name, $valore);
			$this->CheckValueField($data_tb, $field_name);
			switch ($data_tb[$field_name]['TYPE']) {
				case SQLT_BLOB:
					$lob_obj[$field_name]=oci_new_descriptor($this->Conn->getConnection(),OCI_D_LOB);
					$return_field.=",{$field_name}";
					$return_var_bind.=",:{$field_name}";
					$fields.=$binded['field_name']."=EMPTY_BLOB(),";
					break;
				case SQLT_CLOB:
					$lob_obj[$field_name]=oci_new_descriptor($this->Conn->getConnection(),OCI_D_LOB);
					$return_field.=",{$field_name}";
					$return_var_bind.=",:{$field_name}";
					$fields.=$binded['field_name']."=EMPTY_CLOB(),";
					break;
				default:
					$fields.=$binded['field_name']."=".$binded['value'].",";
					break;
			}
			$data_tb[$field_name]['BINDED']=$binded['binded'];
		}
		if (count($this->insert_errors)>0) {
			throw new DriverIanusSqlException("Errore Campi", 100);
		}
		$fields=rtrim($fields, ",");
		$retpk=LoginSql::BuildWhereBinded($pk, $data_tb);
		$pk_where=$retpk['WhereString'];
		$pk_=$retpk['PK_'];
		$this->SetSql("update {$table_name} set {$fields} $pk_where RETURNING ROWID$return_field INTO :rid$return_var_bind");
		$this->Parse();
		$rowid = oci_new_descriptor($this->Conn->getConnection(), OCI_D_ROWID);
		if (!$rowid) {
			throw new DriverIanusSqlException("Errore descrittore rowid", "8");
		}
		if (!oci_bind_by_name($this->Stmt, ":rid",   $rowid, -1, OCI_B_ROWID)) {
			throw new DriverIanusSqlException("Errore Binding Variabili", "9");
		}
		foreach ($pk_ as $key=>$val) {
			if ($pk_[$key]['BINDED']) {
				if (!oci_bind_by_name($this->Stmt, ":PK_B_{$key}_", $pk_[$key]['VALUE'], $retpk['PK_'][$key]['LEN'], $retpk['PK_'][$key]['TYPE'])) {
					throw new DriverIanusSqlException("Errore Binding Variabili", "10");
				}
			}
		}
		foreach ($data_tb as $field_name =>$val) {
			if ($data_tb[$field_name]['BINDED']) {
				switch($data_tb[$field_name]['TYPE']) {
					case SQLT_BLOB:
						oci_bind_by_name($this->Stmt, ":{$field_name}",   $lob_obj[$field_name], -1, OCI_B_BLOB);
						break;
					case SQLT_CLOB:
						oci_bind_by_name($this->Stmt, ":{$field_name}",   $lob_obj[$field_name], -1, OCI_B_CLOB);
						break;
					default:
						if (!oci_bind_by_name($this->Stmt, ":{$field_name}", $data_tb[$field_name]['VALUE'], $data_tb[$field_name]['LEN'], $data_tb[$field_name]['TYPE'])) {
							throw new DriverIanusSqlException("Errore Binding Variabili", "10");
						}
						break;
				}
			}
		}
		$this->ExecuteStmt();
		if (count($lob_obj)>0) foreach ($lob_obj as $field_name=>$obj) {
			$lob_obj[$field_name]->save($data_tb[$field_name]['VALUE']);
			$lob_obj[$field_name]->free;
		}
		foreach ($data_tb as $field_name=>$value) {
			if ($value['PK']) {
				$pks.=$field_name.",";
			}
		}
		$pks=rtrim($pks, ",");
		if ($pks=='') $pks="ROWIDTOCHAR(t.ROWID) as RID";
		$this->SetSql("select {$pks} from {$table_name} t WHERE ROWID = :rid");
		$this->Parse();
		if (!oci_bind_by_name($this->Stmt, ":rid", $rowid, -1, OCI_B_ROWID)) {
			throw new DriverIanusSqlException("Errore Binding", "13");
		}
		$this->ExecuteStmt();
		$row = oci_fetch_assoc($this->Stmt);
		oci_free_statement($this->Stmt);
		return $row;
	}

	public function CheckValueField($data_tb, $field) {
		switch($data_tb[$field]['ORA_TYPE']) {
			case 'VARCHAR2':
				if (strlen($data_tb[$field]['VALUE'])>$data_tb[$field]['LEN']) {
					$this->insert_errors[$field]['ERROR_SPEC']="Valore troppo lungo";
					$this->insert_errors[$field]['ERROR']="TOO_LARGE";
					$this->insert_errors[$field]['VALUE']=$data_tb[$field]['VALUE'];
				}
				break;
			case 'NUMBER':
				if (!is_numeric($data_tb[$field]['VALUE']) && !preg_match("!nextval$!", $data_tb[$field]['VALUE']) && !preg_match("!currval$!", $data_tb[$field]['VALUE'])) {
					$this->insert_errors[$field]['ERROR_SPEC']="Valore non numerico";
					$this->insert_errors[$field]['ERROR']="NOT_NUM";
					$this->insert_errors[$field]['VALUE']=$data_tb[$field]['VALUE'];
				}
				break;
			case 'CLOB':
				break;
			case 'BLOB':
				break;
		}
	}

	public function doCommand($sql_command=null) {
		if (isset($sql_command)) $this->SetSql($sql_command);
		$this->Parse();
		$this->ExecuteStmt();
	}

	public function Insert($array_assoc, $table_name) {
		$table_name=strtoupper($table_name);
		$values_array=LoginSql::Upper($array_assoc);
		$data_tb=$this->getTbStruct($table_name, $values_array);
		foreach ( $values_array as $field_name => $valore ) {
			$binded=LoginSql::prepeare_bind($field_name, $valore);
			$this->CheckValueField($data_tb, $field_name);
			switch ($data_tb[$field_name]['TYPE']) {
				case SQLT_BLOB:
					$lob_obj[$field_name]=oci_new_descriptor($this->Conn->getConnection(),OCI_D_LOB);
					$return_field.=",{$field_name}";
					$return_var_bind.=",:{$field_name}";
					$fields.="\"".$binded['field_name']."\"".",";
					$vals.="EMPTY_BLOB(),";
					break;
				case SQLT_CLOB:
					$lob_obj[$field_name]=oci_new_descriptor($this->Conn->getConnection(),OCI_D_LOB);
					$return_field.=",{$field_name}";
					$return_var_bind.=",:{$field_name}";
					$fields.="\"".$binded['field_name']."\"".",";
					$vals.="EMPTY_CLOB(),";
					break;
				default:
					$fields.="\"".$binded['field_name']."\"".",";
					$vals.=$binded['value'].",";
					break;
			}
			$data_tb[$field_name]['BINDED']=$binded['binded'];
		}
		if (count($this->insert_errors)>0) {
			var_dump($this->insert_errors);
			throw new DriverIanusSqlException("Errore Campi", 100);
		}
		$fields=rtrim($fields, ",");
		$vals=rtrim($vals, ",");
		$this->Sql_Str="insert into {$table_name} ($fields) values ($vals)  RETURNING ROWID$return_field INTO :rid$return_var_bind";
		$this->Parse();
		$rowid = oci_new_descriptor($this->Conn->getConnection(), OCI_D_ROWID);
		if (!$rowid) {
			throw new DriverIanusSqlException("Errore descrittore rowid", "8");
		}
		if (!oci_bind_by_name($this->Stmt, ":rid",   $rowid, -1, OCI_B_ROWID)) {

			throw new DriverIanusSqlException("Errore Binding Variabili", "9");
		}
		foreach ($data_tb as $field_name =>$val) {
			if ($data_tb[$field_name]['BINDED']) {
				switch($data_tb[$field_name]['TYPE']) {
					case SQLT_BLOB:
						oci_bind_by_name($this->Stmt, ":{$field_name}",   $lob_obj[$field_name], -1, OCI_B_BLOB);
						break;
					case SQLT_CLOB:
						oci_bind_by_name($this->Stmt, ":{$field_name}",   $lob_obj[$field_name], -1, OCI_B_CLOB);
						break;
					default:
						if (!oci_bind_by_name($this->Stmt, ":{$field_name}", $data_tb[$field_name]['VALUE'], $data_tb[$field_name]['LEN'], $data_tb[$field_name]['TYPE'])) {
							throw new DriverIanusSqlException("Errore Binding Variabili", "10");
						}
						break;
				}

			}
		}
		$this->ExecuteStmt();
		if (count($lob_obj)>0) foreach ($lob_obj as $field_name=>$obj) {
			$lob_obj[$field_name]->save($data_tb[$field_name]['VALUE']);
			$lob_obj[$field_name]->free;
		}
		foreach ($data_tb as $field_name=>$value) {
			if ($value['PK']) {
				$pks.=$field_name.",";
			}
		}
		$pks=rtrim($pks, ",");
		if ($pks=='') $pks="ROWIDTOCHAR(t.ROWID) as RID";
		$this->SetSql("select {$pks} from {$table_name} t WHERE ROWID = :rid");
		$this->Parse();
		if (!oci_bind_by_name($this->Stmt, ":rid", $rowid, -1, OCI_B_ROWID)) {
			throw new DriverIanusSqlException("Errore Binding", "13");
		}
		$this->ExecuteStmt();
		$row = oci_fetch_assoc($this->Stmt);
		return $row;
	}

	function tb_res() {
		$tb="<table border=1 cellpadding=0 cellspacing=0><tr>";
		for ($i=0;$i<$this->numCols;$i++) $tb.="<th>".$this->colsName[$i]."</th>";
		$tb.="</tr>";
		for ($r=0;$r<$this->numRows;$r++) {
			$tb.="<tr>";
			for ($i=0;$i<$this->numCols;$i++) $tb.="<td>".$this->result[$this->colsName[$i]][$r]."</td>";
			$tb.="</tr>";
		}
		$tb.="</table>";
		return $tb;
	}

	function make_select_option($name, $selected) {
		$option="<select name=\"$name\">\n<option value=''>&nbsp;</option>";
		$option.=$this->make_option($name, $values);
		$option.="</select>";
		return $option;
	}


	function make_option($name, $values) {
		while ($this->get_row()) {
			$selected="";
			if ($values[$name]==$this->Row['VALUE']) $selected="selected";
			$option.="<option value=\"".$this->Row['VALUE']."\" $selected>".$this->Row['DECODE']."</option>\n";
		}
		return $option;
	}

	function make_check($cols, $values) {
		$i=0;
		$check="<table border=0 cellpadding=0 cellpsacing=0><tr>";
		while ($this->get_row()) {
			if ($i==$cols) {$i=0;$check.="</tr><tr>";}
			$i++;
			$checked="";

			if (isset($values[$this->Row['VALUE']])) $checked="checked";
			$check.="<td><input type=\"checkbox\" name=\"".$this->Row['VALUE']."\" value=\"1\" $checked><input type=\"hidden\" name=\"D_".$this->Row['VALUE']."\" value=\"".$this->Row['DECODE']."\">".$this->row['DECODE']."</td>";
		}
		$check.="</tr></table>";
		return $check;
	}

	function Select($fields, $table_name, $wheres=null, $ords=null) {
		if ($fields=='*') {
			$campi="*";
		}
		else {
			foreach ($fields as $key=>$val) {
				$campi.="$key as \"$val\",";
			}
		}
		if (count($wheres)>0) foreach ($wheres as $key=>$val) {
			$where.="$key =:w_c_{$key},";
		}
		if (count($ords)>0) foreach ($ords as $key=>$val) {
			$order.=" {$val['FIELD']} {$val['ORD_TYPE']},";
		}
		$campi=rtrim($campi, ",");
		$where=rtrim($where, ",");
		$order=rtrim($order, ",");
		if ($where!='') $where="where $where";
		if ($order!='') $order="order by $order";
		$sql_query="select $campi from $table_name $where $order";
		$this->SetSql($sql_query);
		$this->Parse();
		if ($wheres!=null) foreach($wheres as $key => $val) {
			ocibindbyname($this->Stmt, ":w_c_{$key}", $val);
		}
		$this->ExecuteSelectStmt();
	}

	protected function Parse(){
		try {
			$this->Stmt = oci_parse ( $this->Conn->getConnection (), $this->Sql_Str );
		} catch ( Exception $e ) {
			throw new DriverIanusSqlException ( "Errore esecuzione Query", 2 );
		}
	}


	protected function ExecuteSelectStmt(){
		$this->ExecuteStmt();
		$this->idx = 0;
		oci_fetch_all ( $this->Stmt, $this->result );
		$this->numRows = oci_num_rows ( $this->Stmt );
		$this->numCols = oci_num_fields ( $this->Stmt );
		for($i = 1; $i <= $this->numCols; $i ++) {
			$this->colsName [$i] = oci_field_name ( $this->Stmt, $i );
			$this->colsType [$i] = oci_field_type ( $this->Stmt, $i );
			$this->colsLength [$i] = oci_field_size ( $this->Stmt, $i );
		}
	}


	protected function ExecuteStmt(){
		try {
			oci_execute ( $this->Stmt , OCI_DEFAULT);
		} catch ( Exception $e ) {
			throw new DriverIanusSqlException ( "Errore esecuzione Query", 3 );
		}
	}


}

class LoginSqlException extends Exception {

}
die($template);
	