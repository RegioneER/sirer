<?php
/**
 * Classe di connessione al DB
 *
 * @package CORE
 */
class dbconn extends Configurable {
	
	/**
	 * Username del DB
	 *
	 * @var String
	 */
	var $username;
	/**
	 * Password del DB
	 *
	 * @var String
	 */
	var $pass;
	/**
	 * Host del DB
	 *
	 * @var String
	 */
	var $host;
	/**
	 * Handler della connessione
	 *
	 * @var Resource
	 */
	var $conn;

	var $flagClosed = false;
	
	/**
	 * Costrutture, stabilisce la connessione al DB
	 *
	 * @param String $username
	 * @param String $pass
	 * @param String $host
	 * @return dbconn
	 */
	function dbconn($username = null, $pass = null, $host = null) {
		parent::__construct ();
		#putenv("NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1");
		if (! isset ( $username )) {
			$ammin_file = $_SERVER ['DOCUMENT_ROOT'];
			$ammin_file = preg_replace ( "/html/i", "config/amministrazione.cfg", $ammin_file );
			$handle = fopen ( $ammin_file, "r" );
			$contents = fread ( $handle, filesize ( $ammin_file ) );
			fclose ( $handle );
			$ammin_config_line = preg_split ( "/\n/", $contents );
			for($i = 0; $i < count ( $ammin_config_line ); $i ++) {
				if (preg_match ( "/OraUserid/i", $ammin_config_line [$i] ))
					$Ora_Userid = preg_replace ( "/OraUserid (.*)/i", "\\1", $ammin_config_line [$i] );
				if (preg_match ( "/OraPassword/i", $ammin_config_line [$i] ))
					$Ora_Pass = preg_replace ( "/OraPassword (.*)/i", "\\1", $ammin_config_line [$i] );
				if (preg_match ( "/OraInstance/i", $ammin_config_line [$i] ))
					$Ora_Host = preg_replace ( "/OraInstance (.*)/i", "\\1", $ammin_config_line [$i] );
			}
			$Ora_Userid = preg_replace ( "/\s/ ", "", $Ora_Userid );
			$Ora_Pass = preg_replace ( "/\s/", "", $Ora_Pass );
			$Ora_Host = preg_replace ( "/\s/", "", $Ora_Host );
			$this->username = $Ora_Userid;
			$this->pass = $Ora_Pass;
			$this->host = $Ora_Host;
		} else {
			$this->username = $username;
			$this->pass = $pass;
			$this->host = $host;
		}
		
		$this->conn = ocilogon ( $this->username, $this->pass, $this->host ) or die ( "<hr>Errore connessione al DB $username<hr>" );
		unset ( $this->username );
		unset ( $this->pass );
		unset ( $this->host );
	}
	
	/**
	 * Chiude la connessione al DB
	 *
	 * @return boolean
	 */
	function close() {
		//$this->flagClosed=true;
		return ocicommit ( $this->conn );
	}
	
	function closeConnection(){
		$this->flagClosed=true;
		return oci_close($this->conn);
	}
	
	/**
	 * Effettua il commit delle transazioni pendenti
	 *
	 * @return boolean
	 */
	function commit() {
		global $insert_errors;
		global $in;
		if (count ( $insert_errors ) > 0) {
			error_page ( $in ['remote_userid'], "Errore Oracle", $insert_errors );
		}
		if (! isset ( $in ['ajax_call'] ) || $in ['ajax_call'] == '')
			return ocicommit ( $this->conn );
		else
			return;
	}

	function isClosed(){
		return $this->flagClosed;
	}

}

/**
 * Classe di gestione delle query
 *
 * @package CORE
 */
class query extends Configurable {
	
	/**
	 * Codice sql dell'istruzione
	 *
	 * @var String
	 */
	var $str;
	/**
	 * Oggetto dbconn
	 *
	 * @var dbconn
	 */
	var $conn;
	/**
	 * Statement dell'istruzione
	 *
	 * @var stmt
	 */
	var $stmt;
	/**
	 * Array risultato della query
	 *
	 * @var array
	 */
	var $res;
	/**
	 * Numero di colonne selezionate
	 *
	 * @var number
	 */
	var $numcols;
	/**
	 * Numero di record selezionati
	 *
	 * @var number
	 */
	var $numrows;
	/**
	 * Indice del record attuale
	 *
	 * @var number
	 */
	var $n_r;
	/**
	 * Record attuale
	 *
	 * @var array
	 */
	var $row;
	/**
	 * Chiavi della query
	 *
	 * @var array
	 */
	var $keys;
	/**
	 * Tipologie dei campi selezionati
	 *
	 * @var array
	 */
	var $type;
	/**
	 * Dimensione dei campi
	 *
	 * @var array
	 */
	var $size;
	/**
	 * Specifiche degli errori
	 *
	 * @var array
	 */
	var $errors;
	
	/**
	 * Costruttore
	 *
	 * @param dbconn $conn
	 * @return query
	 */
	function query($conn) {
		parent::__construct ();
		$this->conn = $conn->conn;
	}
	static function var_config($value) {
		global $config_service;
		global $patients_table;
		if($value=='patients_table') return $patients_table;
		if (isset ( $config_service [$value] ) && $config_service [$value] != '' && $value!='VISITNUM_PROGR')
		return $config_service [$value];
		return "[".$value."]";
	}
	static function varGlobReplace($sql_str) {
		$sql_str=preg_replace ( "/\[(.*?)\]/e", "query::var_config('\\1')", $sql_str );
		if (preg_match_all ( "!'(.*?)'!", $sql_str, $matches )) {
			foreach ( $matches [1] as $k => $v ) {
				if (preg_match_all ( "!\[(.*?)\]!", $v, $matches_1 )) {
					foreach ( $matches_1 [1] as $m1 => $v1 ) {
						$v2 = str_replace ( "[$v1]", "'||:global_{$v1}||'", $v );
						$sql_str = str_replace ( $v, $v2, $sql_str );
						
						$binded_vars ["global_{$v1}"] = var_glob ( $v1 );
					}
				}
			}
		}
		
		if (preg_match_all ( "/\[(.*?)\]/", $sql_str, $matches )) {
			foreach ( $matches [1] as $k => $v ) {
				$sql_str = preg_replace ( "!\[$v\]!", ":global_{$v}", $sql_str );
				$binded_vars ["global_{$v}"] = var_glob ( $v );
			}
		}
		$ret ['sql'] = $sql_str;
		$ret ['binded'] = $binded_vars;
		return $ret;
	}
	
	/**
	 * Imposta il codice sql dell'istruzione
	 *
	 * @param String $sql_str
	 */
	function set_sql($sql_str) {
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( 'query->set_sql($sql_str)', $args );
		}
		$this->str = $sql_str;
	}
	
	/**
	 * Restituisce il codice sql dell'istruzione impostata
	 *
	 * @return String
	 */
	function get_sql() {
		return $this->str;
	}
	
	/**
	 * Effettua operazioni senza risultato su DB
	 *
	 */
	function ins_upd($sql_query = null, $bindVars = null) {
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		global $session_number;
		$POST_GET_PARAM = '';
		$SERVER_PARAM = '';
		$time_ini = time ();
		if (isset ( $sql_query ))
			$this->set_sql ( $sql_query );
		$this->stmt = ociparse ( $this->conn, $this->str );
		if (isset ( $bindVars ) && is_array ( $bindVars ))
			foreach ( $bindVars as $field_name => $valore ) {
				@ocibindbyname ( $this->stmt, ":{$field_name}", $bindVars [$field_name] );
			}
		if (! ociexecute ( $this->stmt, OCI_DEFAULT )) {
			$file_log = $GLOBALS ['dir'] . "/log_trace/" . $in ['remote_userid'] . ".log";
			if ($this->getConfiguration ( 'trace' ) == 'on')
				Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
			error_page ( $in ['remote_userid'], "Errore query: " . $this->str, ocierror ( $this->stmt ) );
		}
		
	
	}
	
	function insertOrUpdate($values, $table, $pk=null, $clob=null){
		if ($pk!=null) foreach ($pk as $key=> $val){
			$pk_key.="{$key}=:PK_{$key} and ";
			$wheres[$key]['f1']=$key;
			$wheres[$key]['f2']=$val;
		}
		
		
		$query=new query($this);
		$query->select(array('CONTO' => 'count(*)'),array( $table => "a"),null,$wheres);
		$query->get_row();
		if ($query->row['CONTO']>0){
			$this->update($values, $table, $pk, $clob);
		}
		else{
			$this->insert($values, $table);
		}
	}
	
	function insertOrAvoid($values, $table, $pk=null, $clob=null){
		if ($pk!=null) foreach ($pk as $key=> $val){
			$pk_key.="{$key}=:PK_{$key} and ";
			$wheres[$key]['f1']=$key;
			$wheres[$key]['f2']=$val;
		}
		
		
		$query=new query($this);
		$query->select(array('CONTO' => 'count(*)'),array( $table => "a"),null,$wheres);
		$query->get_row();
		if ($query->row['CONTO']==0){
			$this->insert($values, $table);
		}
	}
	/**
	 * Gestisce l'inserimento di LOB in tabella
	 *
	 * @param String $var_bindata
	 * @param String $var_bindata_2
	 * @param String $file_to_lob
	 * @param String $testo_descr
	 * @return boolean
	 */
	function insert_lob($var_bindata, $var_bindata_2, $file_to_lob, $testo_descr) {
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( 'query->insert_lob($var_bindata,$var_bindata_2,$file_to_lob,$testo_descr)', $args );
		}
		$this->stmt = ociparse ( $this->conn, $this->str );
		$handle_r = fopen ( $file_to_lob, "r" );
		$contents_r = fread ( $handle_r, filesize ( $file_to_lob ) );
		fclose ( $handle_r );
		
		// Creates an "empty" OCI-Lob object to bind to the locator
		$myLOB = ocinewdescriptor ( $this->conn, OCI_D_LOB );
		$myLOB_2 = ocinewdescriptor ( $this->conn, OCI_D_LOB );
		// Bind the returned Oracle LOB locator to the PHP LOB object
		ocibindbyname ( $this->stmt, ":$var_bindata", $myLOB, - 1, OCI_B_BLOB );
		ocibindbyname ( $this->stmt, ":$var_bindata_2", $myLOB_2, - 1, OCI_B_BLOB );
		// Execute the statement using , OCI_DEFAULT - as a transaction
		if (! ociexecute ( $this->stmt, OCI_DEFAULT )) {
			$error = ocierror ( $this->stmt );
			die ( "Errore ininserimento <pre>" . $this->str . "</pre>" . "<br><br>" . $error ["message"] );
		}
		//or die ("Unable to execute query\n");
		

		$myLOB->save ( $contents_r );
		$myLOB->free ();
		OCIFreeStatement ( $this->stmt );
		$myLOB_2->save ( $testo_descr );
		$myLOB_2->free ();
		OCIFreeStatement ( $this->stmt );
		
		if (OCICommit ( $this->conn )) {
			
			return true;
		} else {
			ocirollback ( $this->conn );
			
			return false;
		}
	}
	
	/**
	 * Esegue una insert su tabella
	 *
	 * @param array $values
	 * @param String $table
	 * @param array $pk
	 * @param boolean $return
	 * @param array $files
	 * @param array $clob
	 * @return boolean
	 */
	function insert($values, $table, $pk = null, $return = true, $files = null, $clob = null) {
		$time_ini = time ();
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( 'query->insert($values, $table, $pk, $return=true, $files=null, $clob=null)', $args );
		}
		//se  presente array files, inseriscilo in BLOB
		if (is_array ( $files ) && count ( $files ) > 0)
			$files_flag = true;
			//se  presente array clob, inseriscilo in CLOB
		if (is_array ( $clob ) && count ( $clob ) > 0)
			$clob_flag = true;
		$fields = "";
		$valori = "";
		foreach ( $values as $field_name => $valore ) {
			if (preg_match ( "/^to_date/i", $valore ) || preg_match ( "/sysdate/i", $valore ) || preg_match ( "/nextval$/i", $valore ) || preg_match ( "/currval$/i", $valore )) {
				$fields .= "{$field_name},";
				$valori .= "$valore,";
				unset ( $values [$field_name] );
			} else {
				if (preg_match ( "/sysdate/i", $valore )) {
					$fields .= "{$field_name},";
					$valori .= "$valore,";
					unset ( $values [$field_name] );
				} else {
					$fields .= "{$field_name},";
					$valori .= ":{$field_name},";
				}
			}
		}
		//preparo l'empty blob per i files
		if (isset ( $files_flag ) && $files_flag) {
			foreach ( $files as $field_name => $file ) {
				$fields .= "{$field_name},";
				$valori .= "EMPTY_BLOB(),";
				$returning .= "{$field_name},";
				$into .= ":{$field_name},";
			
			}
			$returning = rtrim ( $returning, "," );
			$into = rtrim ( $into, "," );
			$returning_into = " RETURNING $returning INTO $into";
		
		}
		
		//preparo l'empty clob per i testi lunghi
		if (isset ( $clob_flag ) && $clob_flag) {
			//			$returning=$into=$valori=$fields="";
			foreach ( $clob as $field_name => $long_txt ) {
				$fields .= "{$field_name},";
				$valori .= "EMPTY_CLOB(),";
				$returning .= "{$field_name},";
				$into .= ":{$field_name},";
			
			}
			$returning = rtrim ( $returning, "," );
			$into = rtrim ( $into, "," );
			$returning_into_clob = " RETURNING $returning INTO $into";
		
		}
		$pk_key = "";
		$pk_key_bind = "";
		if (isset ( $pk ) && is_array ( $pk ))
			foreach ( $pk as $key => $val ) {
				$pk_key .= "{$key},";
				$pk_key_bind .= ":{$key}_,";
			}
		
		$fields = rtrim ( $fields, "," );
		$valori = rtrim ( $valori, "," );
		$pk_key = rtrim ( $pk_key, "," );
		$pk_key_bind = rtrim ( $pk_key_bind, "," );
		$this->str = "INSERT INTO $table ($fields) values ($valori)"; // RETURN $pk_key INTO $pk_key_bind";
		
		if (isset ( $files_flag ) && $files_flag)
			$this->str .= $returning_into;
		
		if (isset ( $clob_flag ) && $clob_flag)
			$this->str .= $returning_into_clob;
				
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		$this->stmt = ociparse ( $this->conn, $this->str );
		
		if (isset ( $files_flag ) && $files_flag) {
			foreach ( $files as $field_name => $file ) {
				$blob_descr [$field_name] = oci_new_descriptor ( $this->conn, OCI_D_LOB );
			}
		}
		if (isset ( $files_flag ) && $files_flag) {
			foreach ( $files as $field_name => $file ) {
				oci_bind_by_name ( $this->stmt, ":{$field_name}", $blob_descr [$field_name], - 1, OCI_B_BLOB );
			}
		}
		
		if (isset ( $clob_flag ) && $clob_flag) {
			foreach ( $clob as $field_name => $long_txt ) {
				$clob_descr [$field_name] = oci_new_descriptor ( $this->conn, OCI_D_LOB );
			}
		
		}
		if (isset ( $clob_flag ) && $clob_flag) {
			foreach ( $clob as $field_name => $long_txt ) {
				oci_bind_by_name ( $this->stmt, ":{$field_name}", $clob_descr [$field_name], - 1, OCI_B_CLOB );
			}
		}
		
		foreach ( $values as $field_name => $valore ) {
			ocibindbyname ( $this->stmt, ":{$field_name}", $values [$field_name] );
		}
		if (! ociexecute ( $this->stmt, OCI_DEFAULT )) {
			global $in;
			$sql = $this->str;
			if ($this->getConfiguration ( 'trace' ) == 'on')
				Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
			if (! $return)
				$this->gest_db_error ( $values, $table );
			else {
				$debug_values = "";
				$length = "";
				foreach ( $values as $key => $val ) {
					
					$query_debug = "select * from ALL_TAB_COLUMNS where table_name=upper('$table') and column_name=upper('$key')";
					$stmt = oci_parse ( $this->conn, $query_debug );
					oci_execute ( $stmt, OCI_DEFAULT );
					oci_fetch ( $stmt );
					if (oci_result ( $stmt, "CHAR_LENGTH" ) == 0)
						$length = oci_result ( $stmt, "DATA_LENGTH" );
					else
						$length = oci_result ( $stmt, "CHAR_LENGTH" );
					$column_name = oci_result ( $stmt, "COLUMN_NAME" );
					
					$debug_values .= "\n* Nome campo: " . $column_name . " -> Valore campo: " . $values [$column_name] . " (Tipo: " . oci_result ( $stmt, "DATA_TYPE" ) . " Oracle Length: " . $length . ") Length Value: " . strlen ( $values [$column_name] ) . " * | mb_strlen: " . mb_strlen ( $values [$column_name], 'utf-8' );
				}
				error_page ( $in ['remote_userid'], "Errore query: " . $sql . " \n " . $debug_values, ocierror ( $this->stmt ) );
			}
		}
		if (isset ( $files_flag ) && $files_flag) {
			foreach ( $files as $field_name => $file ) {
				$fp = fopen ( $file, "r" );
				if (! $fp) {
					if ($this->getConfiguration ( 'trace' ) == 'on')
						Logger::trace ( "Errore file blob:file non esistente" );
					error_page ( $in ['remote_userid'], "Error file", array ('SPEC' => "Errore file blob:file non esistente" ) );
				}
				$content = fread ( $fp, filesize ( $file ) );
				fclose ( $fp );
				if (! $blob_descr [$field_name]->save ( $content )) {
					if ($this->getConfiguration ( 'trace' ) == 'on')
						Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
					error_page ( $in ['remote_userid'], "Errore query: " . $this->str, ocierror ( $this->stmt ) );
				}
			}
		}
		if (isset ( $clob_flag ) && $clob_flag) {
			foreach ( $clob as $field_name => $long_txt ) {
				if (! $clob_descr [$field_name]->save ( $long_txt )) {
					if ($this->getConfiguration ( 'trace' ) == 'on')
						Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
					error_page ( $in ['remote_userid'], "Errore query: " . $this->str, ocierror ( $this->stmt ) );
				}
			}
		}
		return null;
	}
	
	/**
	 * Identifica l'errore dell'istruzione sql eseguita
	 *
	 * @param array $values
	 * @param String $table
	 */
	function gest_db_error($values, $table) {
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( 'query->gest_db_error($values, $table)', $args );
		}
		$sql_query = "select column_name, data_type, data_length,char_length from user_tab_cols where table_name=:table_name ";
		$bind_table ['TABLE_NAME'] = strtoupper ( $table );
		$this->exec ( $sql_query, $bind_table ); //binded
		while ( $this->get_row () ) {
			if ($this->row ['DATA_TYPE'] == 'VARCHAR2') {
				if (strlen ( $values [$this->row ['COLUMN_NAME']] ) > $this->row ['CHAR_LENGTH'])
					$this->errors [$this->row ['COLUMN_NAME']] = "Testo troppo lungo";
			}
			if ($this->row ['DATA_TYPE'] == 'NUMBER') {
				if ($values [$this->row ['COLUMN_NAME']] != '' && ! is_numeric ( $values [$this->row ['COLUMN_NAME']] ))
					$this->errors [$this->row ['COLUMN_NAME']] = "Valore non numerico";
			}
		}
	}
	
	/**
	 * Restituisce le specifiche degli errori
	 *
	 * @return array
	 */
	function getErrors() {
		return $this->errors;
	}
	
	/**
	 * Effettua una query di update
	 *
	 * @param array $values
	 * @param String $table
	 * @param array $pk
	 * @param array $clob
	 */
	function update($values, $table, $pk = null, $clob = null) {
		
		$time_ini = time ();
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( 'query->update($values, $table, $pk=null, $clob=null)', $args );
		}
		if (is_array ( $clob ))
			$clob_flag = true;
		$fields = "";
		
		foreach ( $values as $field_name => $valore ) {
			if (preg_match ( "/^to_date/i", $valore ))
				$fields .= "{$field_name}=$valore,";
			else {
				if (preg_match ( "/sysdate/i", $valore )) {
					$fields .= "{$field_name}=$valore,";
					unset ( $values [$field_name] );
				} else {
					$fields .= "{$field_name}=:{$field_name},";
				}
			}
		
		}
		if (isset ( $clob_flag ) && $clob_flag) {
			foreach ( $clob as $field_name => $long_txt ) {
				$fields .= "{$field_name}=EMPTY_CLOB(),";
				$returning .= "{$field_name},";
				$into .= ":{$field_name},";
			
			}
			$returning = rtrim ( $returning, "," );
			$into = rtrim ( $into, "," );
			$returning_into_clob = " RETURNING $returning INTO $into";
		}
		$pk_key = "";
		if ($pk != null)
			foreach ( $pk as $key => $val ) {
				$pk_key .= "{$key}=:PK_{$key} and ";
			}
		
		$fields = rtrim ( $fields, "," );
		$pk_key = preg_replace ( "/ and $/", "", $pk_key );
		if ($pk_key != '')
			$pk_key = "where $pk_key";
		
		$this->str = "update $table set $fields $pk_key";
		
		if (isset ( $clob_flag ) && $clob_flag)
			$this->str .= $returning_into_clob;
		
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		$this->stmt = ociparse ( $this->conn, $this->str );
		
		if (isset ( $clob_flag ) && $clob_flag) {
			foreach ( $clob as $field_name => $long_txt ) {
				$clob_descr [$field_name] = oci_new_descriptor ( $this->conn, OCI_D_LOB );
			}
		
		}
		if (isset ( $clob_flag ) && $clob_flag) {
			foreach ( $clob as $field_name => $long_txt ) {
				oci_bind_by_name ( $this->stmt, ":{$field_name}", $clob_descr [$field_name], - 1, OCI_B_CLOB );
			}
		}
		
		foreach ( $values as $field_name => $valore ) {
			
			if (! preg_match ( "/^to_date/i", $valore )) {
				$values [$field_name] = preg_replace ( "/\n/", "", $values [$field_name] );
				ocibindbyname ( $this->stmt, ":{$field_name}", $values [$field_name] );
			}
		}
		if ($pk != null)
			foreach ( $pk as $key => $val ) {
				ocibindbyname ( $this->stmt, ":PK_{$key}", $pk [$key] );
			}
		
		if (! ociexecute ( $this->stmt, OCI_DEFAULT )) {
			global $in;
			if ($this->getConfiguration ( 'trace' ) == 'on')
				Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
			if (isset ( $in ['ajax'] ))
				$this->gest_db_error ( $values, $table );
			else {
				$debug_values = "";
				$length = "";
				foreach ( $values as $key => $val ) {
					$query_debug = "select * from ALL_TAB_COLUMNS where table_name=upper('$table') and column_name=upper('$key')";
					$stmt = oci_parse ( $this->conn, $query_debug );
					oci_execute ( $stmt, OCI_DEFAULT );
					oci_fetch ( $stmt );
					if (oci_result ( $stmt, "CHAR_LENGTH" ) == 0)
						$length = oci_result ( $stmt, "DATA_LENGTH" );
					else
						$length = oci_result ( $stmt, "CHAR_LENGTH" );
					$column_name = oci_result ( $stmt, "COLUMN_NAME" );
					$debug_values .= "\n* Nome campo: " . $column_name . " -> Valore campo: " . $values [$column_name] . " (Tipo: " . oci_result ( $stmt, "DATA_TYPE" ) . " Oracle Length: " . $length . ") Length Value: " . strlen ( $values [$column_name] ) . " * | mb_strlen: " . mb_strlen ( $values [$column_name], 'utf-8' );
				}
				$debug_values .= "\n\n PK: \n";
				foreach ( $pk as $key => $val ) {
					$query_debug = "select * from ALL_TAB_COLUMNS where table_name=upper('$table') and column_name=upper('$key')";
					$stmt = oci_parse ( $this->conn, $query_debug );
					oci_execute ( $stmt, OCI_DEFAULT );
					oci_fetch ( $stmt );
					if (oci_result ( $stmt, "CHAR_LENGTH" ) == 0)
						$length = oci_result ( $stmt, "DATA_LENGTH" );
					else
						$length = oci_result ( $stmt, "CHAR_LENGTH" );
					$column_name = oci_result ( $stmt, "COLUMN_NAME" );
					$debug_values .= "\n* Nome campo: " . $column_name . " -> Valore campo: " . $pk [$column_name] . " (Tipo: " . oci_result ( $stmt, "DATA_TYPE" ) . " Oracle Length: " . $length . ") Length Value: " . strlen ( $values [$column_name] ) . " *";
				
				}
				error_page ( $in ['remote_userid'], "Errore query: " . $this->str . " \n " . $debug_values, ocierror ( $this->stmt ) );
			}
		}
		if (isset ( $clob_flag ) && $clob_flag) {
			foreach ( $clob as $field_name => $long_txt ) {
				if (! $clob_descr [$field_name]->save ( $long_txt )) {
					if ($this->getConfiguration ( 'trace' ) == 'on')
						Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
					error_page ( $in ['remote_userid'], "Errore query: " . $this->str, ocierror ( $this->stmt ) );
				}
			}
		}
	}
	
	/**
	 * Costruisce l'istruzione di select
	 *
	 * @param array $values
	 * @param array $tables
	 * @param array $wheres_join
	 * @param array $wheres
	 * @param array $orders
	 * @param array $groups
	 */
	function select($values, $tables, $wheres_join = null, $wheres = null, $orders = null, $groups = null) {
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( 'query->select($values, $tables, $wheres_join=null,$wheres=null, $orders=null, $groups=null)', $args );
		}
		foreach ( $values as $field_alias => $field_name ) {
			$fields .= "{$field_name} as \"{$field_alias}\",";
		}
		$fields = rtrim ( $fields, "," );
		foreach ( $tables as $table_name => $table_alias ) {
			if ($table_alias != '')
				$table_alias = "\"{$table_alias}\"";
			$froms .= "{$table_name}  {$table_alias},";
		}
		$froms = rtrim ( $froms, "," );
		if ($wheres_join != null)
			foreach ( $wheres_join as $key => $val ) {
				if ($val ['OP'] == '')
					$val ['OP'] = "=";
				$where_join .= "{$val['f1']} {$val['OP']} {$val['f2']} and ";
			}
		$where_join = rtrim ( $where_join, " and " );
		if ($wheres != null)
			foreach ( $wheres as $key => $val ) {
				if ($val ['OP'] == '')
					$val ['OP'] = "=";
				$where .= "{$val['f1']} {$val['OP']} :{$key} and ";
			}
		$where = rtrim ( $where, " and " );
		if ($orders != null)
			foreach ( $orders as $field => $ord_type ) {
				if ($ord_type == '')
					$ord_type = 'asc';
				$oder_by .= "{$field} {$ord_type},";
			}
		$oder_by = rtrim ( $oder_by, "," );
		if ($groups != null)
			foreach ( $groups as $field => $ord_type ) {
				if ($ord_type == '')
					$ord_type = 'asc';
				$group_by .= "{$field},";
			}
		$group_by = rtrim ( $group_by, "," );
		if ($where_join != '')
			$where_tot .= $where_join;
		if ($where != '') {
			if ($where_tot != '')
				$where_tot .= " and ";
			$where_tot .= $where;
		}
		if ($where_tot != '')
			$where_tot = "where $where_tot";
		if ($order_by != '')
			$order_by = "order by $order_by";
		if ($group_by != '')
			$group_by = "group by $group_by";
		$this->str = "Select $fields from $froms $where_tot $group_by $order_by";
		$this->stmt = ociparse ( $this->conn, $this->str );
		if ($wheres != null)
			foreach ( $wheres as $key => $val ) {
				$valore_bind = $val ['f2'];
				ocibindbyname ( $this->stmt, ":{$key}", $val ['f2'] );
			}
		if (! ociexecute ( $this->stmt, OCI_DEFAULT )) {
			if ($this->getConfiguration ( 'trace' ) == 'on')
				Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
			error_page ( $in ['remote_userid'], "Errore query: " . $this->str, ocierror ( $this->stmt ) );
		}
		$this->numcols = ocinumcols ( $this->stmt );
		if (! ociexecute ( $this->stmt, OCI_DEFAULT )) {
			if ($this->getConfiguration ( 'trace' ) == 'on')
				Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
			error_page ( $in ['remote_userid'], "Errore query: " . $this->query, ocierror ( $this->stmt ) );
		}
		$this->numrows = ocifetchstatement ( $this->stmt, $this->res );
		$this->n_r = 0;
		$i = 0;
		foreach ( $this->res as $key => $val ) {
			$this->keys [$i] = $key;
			$this->type [$key] = ocicolumntype ( $this->stmt, $i + 1 );
			$this->size [$key] = ocicolumnsize ( $this->stmt, $i + 1 );
			$i ++;
		}
	}
	
	/**
	 * Esegue l'istruzione sql
	 *
	 * @param String $sql_str
	 * @param array $bind_array
	 */
	function exec($sql_str = null, $bind_array = null) {
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( 'query->exec($sql_str=null, $bind_array=null)', $args ); //debug
		}
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		global $config_general;
		if (isset ( $sql_str ))
			$this->set_sql ( $sql_str );
		//FPTracker::trackQuery ( $this->str );
		$POST_GET_PARAM = '';
		$SERVER_PARAM = '';
		$this->row = "";
		$this->res = "";
		$time_ini = time ();
		global $session_number;
		$values_str = "";
		$time_ini = time ();
		$log = "Init_time:" . time ();
		if ($this->str != '') {
			$this->stmt = ociparse ( $this->conn, $this->str );
			//die($this->str);
			if (isset ( $bind_array ))
				foreach ( $bind_array as $key => $val ) {
					
					@ocibindbyname ( $this->stmt, ":{$key}", $bind_array [$key], - 1 );
					$values_str = "$key = $val | ";
					
				}
			
			if (! ociexecute ( $this->stmt, OCI_DEFAULT )) {
				if ($this->getConfiguration ( 'trace' ) == 'on')
					Logger::trace ( "Errore query: " . $this->str, ocierror ( $this->stmt ) );
				error_page ( $in ['remote_userid'], "Errore query: " . $this->str, ocierror ( $this->stmt ) );
			}
			$this->numcols = ocinumcols ( $this->stmt );
			$this->numrows = @ocifetchstatement ( $this->stmt, $this->res );
			$this->n_r = 0;
			$i = 0;
			foreach ( $this->res as $key => $val ) {
				$this->keys [$i] = $key;
				$this->type [$key] = ocicolumntype ( $this->stmt, $i + 1 );
				$this->size [$key] = ocicolumnsize ( $this->stmt, $i + 1 );
				$i ++;
			}
		}
	
	}
	
	/**
	 * Restituisce il record successivo
	 *
	 * @param String $sql_str
	 * @return boolean
	 */
	function get_row($sql_str = null, $bind = null) {
		if ($this->getConfiguration ( 'debug' ) == 'on') {
			$args = func_get_args ();
			Logger::call ( __METHOD__, $args );
		}
		if (isset ( $sql_str )) {
			$this->exec ( $sql_str, $bind ); //binded
		}
		if ($this->n_r + 1 > $this->numrows) {
			return false;
		} else {
			foreach ( $this->res as $key => $val ) {
				$this->row [$key] = $this->res [$key] [$this->n_r];
			}
			$this->n_r ++;
			return true;
		}
	}
	###endsub###
	

	###sub get_row_by_index($index as int) as boolean###
	function get_row_by_index($index) {
		if ($index > $this->numrows)
			return false;
		else {
			foreach ( $this->res as $key => $val ) {
				$this->row [$key] = $this->res [$key] [$index];
			}
			return true;
		}
	}
	###endsub###
	

	###sub tb_res() as string###
	/**
	 * Restituisce una tabella html con il risultato della query
	 *
	 * @return String
	 */
	function tb_res() {
		$tb = "<table border=1 cellpadding=0 cellspacing=0><tr>";
		for($i = 0; $i < $this->numcols; $i ++)
			$tb .= "<th>" . $this->keys [$i] . "</th>";
		$tb .= "</tr>";
		for($r = 0; $r < $this->numrows; $r ++) {
			$tb .= "<tr>";
			for($i = 0; $i < $this->numcols; $i ++)
				$tb .= "<td>" . $this->res [$this->keys [$i]] [$r] . "</td>";
			$tb .= "</tr>";
		}
		$tb .= "</table>";
		return $tb;
	}
	
	/**
	 * Effettua una ricerca su tutti i campi
	 *
	 * @param String $table
	 * @param String $pattern
	 */
	function search_allfield($table, $pattern) {
		$this->str = "select column_name, data_type from user_tab_columns where table_name=upper(:table_name)";
		$bind ['TABLE_NAME'] = $table;
		$this->exec ( $this->str, $bind ); //binded
		$where = "";
		while ( $this->get_row () ) {
			if (is_numeric ( $pattern )) {
				if ($this->row ['DATA_TYPE'] == 'NUMBER') {
					if ($where == '')
						$where = ' where ';
					else
						$where .= ' or ';
					$where .= $this->row ['COLUMN_NAME'] . "=$pattern";
				}
			}
			if ($this->row ['DATA_TYPE'] == 'DATE') {
				$patterndate = preg_replace ( '/\//', "", $pattern );
				if (is_numeric ( $patterndate )) {
					if ($where == '')
						$where = ' where ';
					else
						$where .= ' or ';
					$where .= "to_char(" . $this->row ['COLUMN_NAME'] . ",'DDMMYYYY')=$patterndate";
				}
			}
			if ($this->row ['DATA_TYPE'] == 'VARCHAR2') {
				if ($where == '')
					$where = ' where ';
				else
					$where .= ' or ';
				$where .= "upper(" . $this->row ['COLUMN_NAME'] . ") like upper('%" . $pattern . "%')";
			}
		}
		$this->str = "select * from $table $where";
		$this->exec (); //obsoleta trovare dove testare ....carlo????
	}
	
	/**
	 * Effettua una ricerca nei campi selezionati
	 *
	 * @param String $table
	 * @param array $fields
	 * @param String $pattern
	 * @param array $order_by
	 */
	function search_infield($table, $fields, $pattern, $order_by) {
		$afield = split ( ",", $fields );
		$this->str = "select column_name, data_type from user_tab_columns where table_name=upper(:table_name)";
		$bind ['TABLE_NAME'] = $table;
		$this->exec ( $this->str, $bind ); //binded
		$where = "";
		while ( $this->get_row () ) {
			foreach ( $afield as $data ) {
				#echo "CAMPO: {$this->row['COLUMN_NAME']} - $data<br>";
				if ($this->row ['COLUMN_NAME'] == $data) {
					#echo "TROVATO: {$this->row['COLUMN_NAME']} - $data<br>";
					if (is_numeric ( $pattern )) {
						if ($this->row ['DATA_TYPE'] == 'NUMBER') {
							if ($where == '')
								$where = ' where ';
							else
								$where .= ' or ';
							$where .= $this->row ['COLUMN_NAME'] . "=$pattern";
						}
					}
					if ($this->row ['DATA_TYPE'] == 'DATE') {
						$patterndate = preg_replace ( '/\//', "", $pattern );
						if (is_numeric ( $patterndate )) {
							if ($where == '')
								$where = ' where ';
							else
								$where .= ' or ';
							$where .= "to_char(" . $this->row ['COLUMN_NAME'] . ",'DDMMYYYY')=$patterndate";
						}
					}
					if ($this->row ['DATA_TYPE'] == 'VARCHAR2') {
						if ($where == '')
							$where = ' where ';
						else
							$where .= ' or ';
						$where .= "upper(" . $this->row ['COLUMN_NAME'] . ") like upper('%" . $pattern . "%')";
					}
				}
			}
			if ($fields_select != '')
				$fields_select .= ",";
			if ($this->row ['DATA_TYPE'] == 'DATE')
				$fields_select .= "to_char({$this->row['COLUMN_NAME']}, 'DD/MM/YYYY HH24:mi:ss') as {$this->row['COLUMN_NAME']}_STR";
			else
				$fields_select .= $this->row ['COLUMN_NAME'];
		
		}
		$this->str = "select $fields_select from $table $where $order_by";
		#echo "<hr>{$this->str}<hr>";
		$this->exec (); //obsoleta trovare dove testare ....carlo????
	}
	
	/**
	 * Costruisce una select
	 *
	 * @param String $name
	 * @return String
	 */
	function make_select_option($name) {
		$option = "<select name=\"$name\">\n<option value=''>&nbsp;</option>";
		global $in;
		while ( $this->get_row () ) {
			$selected = "";
			if ($in ['$name'] == $this->row ['VALUE'])
				$selected = "selected";
			$option .= "<option value=\"" . $this->row ['VALUE'] . "\" $selected>" . $this->row ['DECODE'] . "</option>\n";
		}
		$option .= "</select>";
		return $option;
	}
	
	/**
	 * Costruisce una lista di option dal risultato della query
	 *
	 * @param String $name
	 * @return String
	 */
	function make_option($name) {
		#echo "CIAO";
		global $in;
		while ( $this->get_row () ) {
			$selected = "";
			
			if ($in [$name] == $this->row ['VALUE'])
				$selected = "selected";
			$option .= "<option value=\"" . $this->row ['VALUE'] . "\" $selected>" . $this->row ['DECODE'] . "</option>\n";
		}
		return $option;
	}
	
	/**
	 * Costruisce una lista di checkbox dal risultato della query
	 *
	 * @param array $cols
	 * @return String
	 */
	function make_check($cols) {
		$check = "";
		global $in;
		$i = 0;
		$check = "<table border=0 cellpadding=0 cellpsacing=0><tr>";
		while ( $this->get_row () ) {
			if ($i == $cols) {
				$i = 0;
				$check .= "</tr><tr>";
			}
			$i ++;
			$checked = "";
			if (isset ( $in [$this->row ['VALUE']] ))
				$checked = "checked";
			$check .= "<td><input type=\"checkbox\" name=\"" . $this->row ['VALUE'] . "\" value=\"1\" $checked><input type=\"hidden\ name=\"D_" . $this->row ['VALUE'] . "\" value=\"" . $this->row ['DECODE'] . "\">" . $this->row ['DECODE'] . "</td>";
		}
		$check .= "</tr></table>";
		return $check;
	}
}
###endsub###
?>
