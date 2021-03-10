<?php

if(!class_exists("FPTracker"))
	include_once '/http/lib/DriverIanus/functionpoint.php';

/**
 * Classe di connessione al db
 *
 * @package XMR 2.1
 *
 */
class dbconn{

	var $username;
	var $pass;
	var $host;
	var $conn;


	/**
	 * Costruttore
	 *
	 * @param string $username
	 * @param string $pass
	 * @param string $host
	 * @return dbconn
	 */
	function dbconn($username = null, $pass = null, $host = null){
		#putenv("NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1");
		if (!isset($username)){
			$ammin_file=$_SERVER['DOCUMENT_ROOT'];
			$ammin_file=preg_replace("/html/i", "config/amministrazione.cfg", $ammin_file);
			$handle = fopen($ammin_file, "r");
			$contents = fread($handle, filesize($ammin_file));
			fclose($handle);
			$ammin_config_line=preg_split("/\n/", $contents);
			for ($i=0;$i<=count($ammin_config_line);$i++) {
				if (preg_match("/OraUserid/i",$ammin_config_line[$i])) $Ora_Userid=preg_replace("/OraUserid (.*)/i", "\\1" , $ammin_config_line[$i]);
				if (preg_match("/OraPassword/i",$ammin_config_line[$i])) $Ora_Pass=preg_replace("/OraPassword (.*)/i", "\\1" , $ammin_config_line[$i]);
				if (preg_match("/OraInstance/i",$ammin_config_line[$i])) $Ora_Host=preg_replace("/OraInstance (.*)/i", "\\1" , $ammin_config_line[$i]);
			}
			$Ora_Userid=preg_replace("/\s/ ", "",$Ora_Userid);
			$Ora_Pass=preg_replace("/\s/", "",$Ora_Pass);
			$Ora_Host=preg_replace("/\s/", "",$Ora_Host);
			$this->username=$Ora_Userid;
			$this->pass=$Ora_Pass;
			$this->host=$Ora_Host;
		}
		else {
			$this->username=$username;
			$this->pass=$pass;
			$this->host=$host;
		}
		$this->conn=ocilogon($this->username,$this->pass,$this->host) or die ("<hr>Errore connessione al DB $username<hr>");
	}



	/**
	 * Close
	 *
	 * Chiude la connessione al db
	 *
	 * @return bool
	 */
	function close(){
		return ocicommit($this->conn);
	}



	/**
	 * Commit
	 *
	 * Esegue il commit se non � definito o � vuoto il parametro di POST/GET 'no_commit'
	 *
	 * @return bool
	 */
	function commit(){
		global $in;
		if ($in['no_commit']=='')   return ocicommit($this->conn);
		else return ocirollback($this->conn);
	}


}


/**
 * Classe query
 *
 */
class query{

	var $str;
	var $conn;
	var $stmt;
	var $res;
	var $numcols;
	var $numrows;
	var $n_r;
	var $row;
	var $keys;
	var $type;
	var $size;


	/**
	 * Costruttore
	 *
	 * @param dbconn $conn
	 * @return query
	 */
	function query($conn){
		$this->conn=$conn->conn;
	}



	/**
	 * set_sql
	 *
	 * Imposta lo statement sql
	 *
	 * @param string $sql_str
	 */
	function set_sql($sql_str){
		$this->str=$sql_str;
	}

	/**
	 * get_sql
	 *
	 * Restituisce lo statement sql
	 *
	 * @return string
	 */
	function get_sql(){
		return $this->str;
	}

	/**
	 * ins_upd
	 *
	 * Esegue lo statement di Insert/update
	 *
	 */
	function ins_upd($sql_query=null, $bindVars=null){
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		if (isset($sql_query)) $this->set_sql($sql_query);
		$this->stmt=ociparse($this->conn, $this->str);
		foreach($bindVars as $field_name => $valore){
			ocibindbyname($this->stmt, ":{$field_name}", $bindVars[$field_name]);
		}
		if (!ociexecute($this->stmt, OCI_DEFAULT))
		error_page($in['remote_userid'],"Errore query: ".$this->str, ocierror($this->stmt));

	}

	/**
	 * insert
	 *
	 * Effettua l'insert dei valori dell'array $values nella tabella $table, con chiave primare $pk
	 * $values=array associativo: nome_campo=>valore
	 * $table=stringa con nome della tabella
	 * $pk=array associativo: nome_colonna_chiave=>nome_colonna_chiave
	 *
	 * @param array $values
	 * @param string $table
	 * @param array $pk
	 * @return unknown
	 */
	function insert($values, $table, $pk){
		foreach($values as $field_name => $valore){
			$fields.="{$field_name},";
			$valori.=":{$field_name},";
		}
		foreach ($pk as $key=> $val){
			$pk_key.="{$key},";
			$pk_key_bind.=":{$key}_,";
		}
		$fields=rtrim($fields,",");
		$valori=rtrim($valori,",");
		$pk_key=rtrim($pk_key,",");
		$pk_key_bind=rtrim($pk_key_bind,",");
		$this->str="INSERT INTO $table ($fields) values ($valori)";// RETURN $pk_key INTO $pk_key_bind";
		$this->stmt = ociparse($this->conn, $this->str);
		foreach($values as $field_name => $valore){
			ocibindbyname($this->stmt, ":{$field_name}", $values[$field_name]);
		}
		if (!ociexecute($this->stmt, OCI_DEFAULT)) error_page($in['remote_userid'],"Errore query: ".$this->str, ocierror($this->stmt));
		return $ret;
	}

	/**
	 * update
	 *
	 * Effettua l'update di un record
	 * $values:array associativo nome_campo=>valore
	 * $table: stringa nome_tabella
	 * $pk: array associativo nome_campo_pk=>valore
	 *
	 * @param array $values
	 * @param string $table
	 * @param array $pk
	 */
	function update($values, $table, $pk=null){
		foreach($values as $field_name => $valore){
			$fields.="{$field_name}=:{$field_name},";
		}
		if ($pk!=null) foreach ($pk as $key=> $val){
			$pk_key.="{$key}=:{$key} and ";
		}
		$fields=rtrim($fields,",");
		$pk_key=rtrim($pk_key," and ");
		if ($pk_key!='') $pk_key="where $pk_key";
		$this->str="update $table set $fields $pk_key";
		$this->stmt = ociparse($this->conn, $this->str);
		foreach($values as $field_name => $valore){
			ocibindbyname($this->stmt, ":{$field_name}", $values[$field_name]);
		}
		if ($pk!=null) foreach($pk as $key => $val){
			ocibindbyname($this->stmt, ":{$key}", $pk[$key]);
		}
		if (!ociexecute($this->stmt, OCI_DEFAULT)) error_page($in['remote_userid'],"Errore query: ".$this->str, ocierror($this->stmt));
	}

	/**
	 * exec
	 *
	 * Esegue lo statement sql
	 *
	 */
	function exec($sql_str=null){
	if (isset($sql_str)){
			$this->set_sql($sql_str);
		}
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		$this->stmt=ociparse($this->conn, $this->str);
		if (!ociexecute($this->stmt, OCI_DEFAULT)) error_page($in['remote_userid'],"Errore query: ".$this->str, ocierror($this->stmt));
		$this->numcols=ocinumcols($this->stmt) ;
		//if (!ociexecute($this->stmt, OCI_DEFAULT)) error_page($in['remote_userid'],"Errore query: ".$this->query, ocierror($this->stmt));
		$this->numrows = ocifetchstatement($this->stmt, $this->res);
		$this->n_r=0;
		$i=0;
		foreach ($this->res as $key => $val) {
			$this->keys[$i]=$key;
			$this->type[$key]=ocicolumntype($this->stmt, $i+1);
			$this->size[$key]=ocicolumnsize($this->stmt, $i+1);
			$i++;
		}
	}

	/**
	 * get_row
	 *
	 * Inserisce nella propriet� row il record successivo o false in caso non ci sia
	 *
	 * @return bool
	 */
	function get_row($sql_str=null){
	if (isset($sql_str)){
			$this->set_sql($sql_str);
			$this->exec();
		}
		if ($this->n_r+1>$this->numrows)  return false;
		else{
			foreach ($this->res as $key => $val) {
				$this->row[$key]=$this->res[$key][$this->n_r];
			}
			$this->n_r++;
			return true;
		}
	}

	/**
	 * get_row_by_index
	 *
	 *  Inserisce nella propriet� row il record con indice $index o false in caso non ci sia
	 *
	 * @param int $index
	 * @return bool
	 */
	function get_row_by_index($index){
		if ($index>$this->numrows)  return false;
		else{
			foreach ($this->res as $key => $val) {
				$this->row[$key]=$this->res[$key][$index];
			}
			return true;
		}
	}

	/**
	 * tb_res
	 *
	 * Restituisce il codice html della tabella con il risultato della query
	 *
	 * @param bool $no_header
	 * @return string
	 */
	function tb_res($no_header=false){
		$tb="<table border=1 cellpadding=0 cellspacing=0>";
		if (!$no_header){
			$tb.="<tr>";
			for ($i=0;$i<$this->numcols;$i++) $tb.="<th>".$this->keys[$i]."</th>";
			$tb.="</tr>";
		}
		for ($r=0;$r<$this->numrows;$r++){
			$tb.="<tr>";
			for ($i=0;$i<$this->numcols;$i++) $tb.="<td>".$this->res[$this->keys[$i]][$r]."</td>";
			$tb.="</tr>";
		}
		$tb.="</table>";
		return $tb;
	}

	/**
	 * select
	 *
	 * Crea la query di selezione dei campi $values nelle tabelle $tables con join $where_join, condizioni $wheres, criteri di ordinamento $orders e raggruppamento $groups
	 *
	 * $values: array associativo nome_campo=>alias
	 * $tables: array associativo nome_tabella=>alias
	 * $wheres_join:array con criteri di join
	 * $wheres: array con condizioni
	 * $orders: array associativo nome_campo=>asc/desc
	 * $groups: array con nome_campo
	 *
	 * @param array $values
	 * @param array $tables
	 * @param array $wheres_join
	 * @param array $wheres
	 * @param array $orders
	 * @param array $groups
	 */
	function select($values, $tables, $wheres_join=null,$wheres=null, $orders=null, $groups=null){
		foreach($values as $field_alias => $field_name){
			$fields.="{$field_name} as \"{$field_alias}\",";
		}
		$fields=rtrim($fields,",");
		foreach($tables as $table_name => $table_alias){
			if ($table_alias!='') $table_alias="\"{$table_alias}\"";
			$froms.="{$table_name}  {$table_alias},";
		}
		$froms=rtrim($froms,",");
		if ($wheres_join!=null) foreach($wheres_join as $key => $val){
			if ($val['OP']=='') $val['OP']="=";
			$where_join.="{$val['f1']} {$val['OP']} {$val['f2']} and ";
		}
		$where_join=rtrim($where_join," and ");
		if ($wheres!=null) foreach($wheres as $key => $val){
			if ($val['OP']=='') $val['OP']="=";
			$where.="{$val['f1']} {$val['OP']} :{$key} and ";
		}
		$where=rtrim($where," and ");
		if ($orders!=null) foreach($orders as $field => $ord_type){
			if ($ord_type=='') $ord_type='asc';
			$oder_by.="{$field} {$ord_type},";
		}
		$oder_by=rtrim($oder_by,",");
		if ($groups!=null) foreach($groups as $field => $ord_type){
			if ($ord_type=='') $ord_type='asc';
			$group_by.="{$field},";
		}
		$group_by=rtrim($group_by,",");
		if ($where_join!='') $where_tot.=$where_join;
		if ($where!='') {
			if ($where_tot!='') $where_tot.=" and ";
			$where_tot.=$where;
		}
		if ($where_tot!='') $where_tot="where $where_tot";
		if ($order_by!='') $order_by="order by $order_by";
		if ($group_by!='') $group_by="group by $order_by";
		$this->str="Select $fields from $froms $where_tot $group_by $order_by";
		$this->stmt = ociparse($this->conn, $this->str);
		if ($wheres!=null) foreach($wheres as $key => $val){
			$valore_bind=$val['f2'];
			ocibindbyname($this->stmt, ":{$key}", $val['f2']);
		}
		if (!ociexecute($this->stmt, OCI_DEFAULT)) error_page($in['remote_userid'],"Errore query: ".$this->str, ocierror($this->stmt));
		$this->numcols=ocinumcols($this->stmt) ;
		if (!ociexecute($this->stmt, OCI_DEFAULT)) error_page($in['remote_userid'],"Errore query: ".$this->query, ocierror($this->stmt));
		$this->numrows = ocifetchstatement($this->stmt, $this->res);
		$this->n_r=0;
		$i=0;
		foreach ($this->res as $key => $val) {
			$this->keys[$i]=$key;
			$this->type[$key]=ocicolumntype($this->stmt, $i+1);
			$this->size[$key]=ocicolumnsize($this->stmt, $i+1);
			$i++;
		}
	}

	/**
	 * search_allfield
	 *
	 * Crea una query per ricercare $pattern in tutti i campi della tabella $table e la esegue
	 *
	 * @param string $table
	 * @param string $pattern
	 */
	function search_allfield($table, $pattern){
		$this->str="select column_name, data_type from user_tab_columns where table_name=upper('$table')";
		$this->exec();
		$where="";
		while ($this->get_row()){
			if (is_numeric($pattern)){
				if ($this->row['DATA_TYPE']=='NUMBER') {
					if ($where=='') $where=' where ';
					else $where.=' or ';
					$where.=$this->row['COLUMN_NAME']."=$pattern";
				}
			}
			if ($this->row['DATA_TYPE']=='DATE'){
				$patterndate=preg_replace('/\//', "", $pattern);
				if (is_numeric($patterndate)) {
					if ($where=='') $where=' where ';
					else $where.=' or ';
					$where.="to_char(".$this->row['COLUMN_NAME'].",'DDMMYYYY')=$patterndate";
				}
			}
			if ($this->row['DATA_TYPE']=='VARCHAR2')  {
				if ($where=='') $where=' where ';
				else $where.=' or ';
				$where.="upper(".$this->row['COLUMN_NAME'].") like upper('%".$pattern."%')";
			}
		}
		$this->str="select * from $table $where";
		$this->exec();
	}

	/**
	 * search_infield
	 *
	 * Crea la query per ricercare $pattern nie campi $fields della tabella $table e la esegue
	 * $fiels: nome dei campi separati da ","
	 *
	 * @param string $table
	 * @param string $fields
	 * @param string $pattern
	 */
	function search_infield($table, $fields, $pattern){
		$afield=split(",",$fields);
		$this->str="select column_name, data_type from user_tab_columns where table_name=upper('$table')";
		$this->exec();
		$where="";
		while ($this->get_row()){
			foreach($afield as $data){
				if (preg_match("/^".$this->row['COLUMN_NAME']."$/i", $data)){
					if (is_numeric($pattern)){
						if ($this->row['DATA_TYPE']=='NUMBER') {
							if ($where=='') $where=' where ';
							else $where.=' or ';
							$where.=$this->row['COLUMN_NAME']."=$pattern";
						}
					}
					if ($this->row['DATA_TYPE']=='DATE'){
						$patterndate=preg_replace('/\//', "", $pattern);
						if (is_numeric($patterndate)) {
							if ($where=='') $where=' where ';
							else $where.=' or ';
							$where.="to_char(".$this->row['COLUMN_NAME'].",'DDMMYYYY')=$patterndate";
						}
					}
					if ($this->row['DATA_TYPE']=='VARCHAR2')  {
						if ($where=='') $where=' where ';
						else $where.=' or ';
						$where.="upper(".$this->row['COLUMN_NAME'].") like upper('%".$pattern."%')";
					}
				}
			}
		}
		$this->str="select * from $table $where";
		$this->exec();
	}

	/**
	 * make_select_option
	 *
	 * Restituisce il codice html della lista di option di una select-box a partire dal risultato della query
	 * Inoltre imposta come selezionato il valore se uguale al POST/GET [nome_campo].
	 * $name � il nome della select
	 *
	 * @param string $name
	 * @return string
	 */
	function make_select_option($name){
		$option="<select name=\"$name\">\n<option value=''>&nbsp;</option>";
		global $in;
		while ($this->get_row()){
			$selected="";
			if ($in['$name']==$this->row['VALUE']) $selected="selected";
			$option.="<option value=\"".$this->row['VALUE']."\" $selected>".$this->row['DECODE']."</option>\n";
		}
		$option.="</select>";
		return $option;
	}

	/**
	 * make_check
	 *
	 * Crea una lista di check a partire dal risultato della query suddivisa in $cols colonne
	 *
	 * @param int $cols
	 * @return string
	 */
	function make_check($cols){
		$check="";
		global $in;
		$i=0;
		$check="<table border=0 cellpadding=0 cellpsacing=0><tr>";
		while ($this->get_row()){
			if ($i==$cols) {$i=0;$check.="</tr><tr>";}
			$i++;
			$checked="";
			if (isset($in[$this->row['VALUE']])) $checked="checked";
			$check.="<td><input type=\"checkbox\" name=\"".$this->row['VALUE']."\" value=\"1\" $checked><input type=\"hidden\ name=\"D_".$this->row['VALUE']."\" value=\"".$this->row['DECODE']."\">".$this->row['DECODE']."</td>";
		}
		$check.="</tr></table>";
		return $check;
	}
}
?>
