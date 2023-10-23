<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of OraSqlinc
 *
 * @author ccontino
 */
class OraSql {

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

	public function __construct(OraDBConnection $db) {
		$this->Conn = $db;
	}

	public function SetSql($sql_str) {
		$this->Sql_Str = $sql_str;
	}

	public function getSql() {
		return $this->Sql_Str;
	}

	public function Exec($sql_str = null) {
		if (isset ( $sql_str )) {
			$this->Sql_Str = $sql_str;
		}
		if (! isset ( $this->Sql_Str )) {
			throw new SqlException ( "Query non definita", 1 );
		}

		$this->Parse();
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
		$sql_query="select COLUMN_NAME, DATA_TYPE, CHAR_LENGTH from USER_TAB_COLUMNS where table_name='{$tb_name}'";
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
			$binded=OraSql::prepeare_bind($field_name, $valore);
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
		$values_array=OraSql::Upper($array_assoc);
		$data_tb=$this->getTbStruct($table_name, $values_array);
		foreach ($data_tb as $field=>$val) {
			if ($data_tb[$field]['PK']) {
				$pk[$field]=$data_tb[$field]['VALUE'];
			}
		}
		$retpk=OraSql::BuildWhereBinded($pk, $data_tb);
		$pk_where=$retpk['WhereString'];
		$pk_=$retpk['PK_'];
		$this->SetSql("select count(*) as conto from {$table_name} $pk_where");
		$this->Stmt=oci_parse($this->Conn->getConnection(), $this->Sql_Str);
		if (!$this->Stmt) {
			throw new SqlException("Errore parse oracle", "7");
		}
		foreach ($pk_ as $key=>$val) {
			if ($pk_[$key]['BINDED']) {
				if (!oci_bind_by_name($this->Stmt, ":PK_B_{$key}_", $pk_[$key]['VALUE'], $retpk['PK_'][$key]['LEN'], $retpk['PK_'][$key]['TYPE'])) {
					throw new SqlException("Errore Binding Variabili", "10");
				}
			}
		}
		if (!oci_execute($this->Stmt,OCI_DEFAULT)) {
			throw new SqlException("Errore Execute", "14");
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
		$values_array=OraSql::Upper($array_assoc);
		$data_tb=$this->getTbStruct($table_name, $values_array);
		//$blob = oci_new_descriptor($this->Conn->getConnection(), OCI_D_LOB);
		//echo "a";

		foreach ( $values_array as $field_name => $valore ) {
			$binded=OraSql::prepeare_bind($field_name, $valore);
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
		//echo " b ";
		if (count($this->insert_errors)>0) {
			error_page();
			throw new SqlException("Errore Campi", $this->insert_errors);
		}
		$fields=rtrim($fields, ",");
		$retpk=OraSql::BuildWhereBinded($pk, $data_tb);
		$pk_where=$retpk['WhereString'];
		$pk_=$retpk['PK_'];

		$this->SetSql("update {$table_name} set {$fields} $pk_where RETURNING ROWID$return_field INTO :rid$return_var_bind");
		$this->Parse();
		$rowid = oci_new_descriptor($this->Conn->getConnection(), OCI_D_ROWID);
		if (!$rowid) {
			error_page();
			throw new SqlException("Errore descrittore rowid", "8");
		}
		//      echo "<hr>".$this->Stmt->Sql_Str."<hr>"; die(); //.oci_bind_by_name($this->Stmt, ":rid",   $rowid, -1, OCI_B_ROWID)."<hr>"; die();
		if (!oci_bind_by_name($this->Stmt, ":rid",   $rowid, -1, OCI_B_ROWID)) {
			error_page();
			throw new SqlException("Errore Binding Variabili", "9");
		}
		foreach ($pk_ as $key=>$val) {
			if ($pk_[$key]['BINDED']) {
				if (!oci_bind_by_name($this->Stmt, ":PK_B_{$key}_", $pk_[$key]['VALUE'], $retpk['PK_'][$key]['LEN'], $retpk['PK_'][$key]['TYPE'])) {
					error_page();
					throw new SqlException("Errore Binding Variabili", "10");
				}
			}
		}
		//echo " c ";
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
							error_page();
							throw new SqlException("Errore Binding Variabili", "10");
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
			error_page();
			throw new SqlException("Errore Binding", "13");
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
		$values_array=OraSql::Upper($array_assoc);
		$data_tb=$this->getTbStruct($table_name, $values_array);
		foreach ( $values_array as $field_name => $valore ) {
			$binded=OraSql::prepeare_bind($field_name, $valore);
			$this->CheckValueField($data_tb, $field_name);
			switch ($data_tb[$field_name]['TYPE']) {
				case SQLT_BLOB:
					$lob_obj[$field_name]=oci_new_descriptor($this->Conn->getConnection(),OCI_D_LOB);
					$return_field.=",{$field_name}";
					$return_var_bind.=",:{$field_name}";
					$fields.=$binded['field_name'].",";
					$vals.="EMPTY_BLOB(),";
					break;
				case SQLT_CLOB:
					$lob_obj[$field_name]=oci_new_descriptor($this->Conn->getConnection(),OCI_D_LOB);
					$return_field.=",{$field_name}";
					$return_var_bind.=",:{$field_name}";
					$fields.=$binded['field_name'].",";
					$vals.="EMPTY_CLOB(),";
					break;
				default:
					$fields.=$binded['field_name'].",";
					$vals.=$binded['value'].",";
					break;
			}
			$data_tb[$field_name]['BINDED']=$binded['binded'];
		}
		if (count($this->insert_errors)>0) {
			var_dump($this->insert_errors);
			throw new SqlException("Errore Campi", 100);
		}
		$fields=rtrim($fields, ",");
		$vals=rtrim($vals, ",");
		$this->Sql_Str="insert into {$table_name} ($fields) values ($vals)  RETURNING ROWID$return_field INTO :rid$return_var_bind";
		$this->Parse();
		$rowid = oci_new_descriptor($this->Conn->getConnection(), OCI_D_ROWID);
		if (!$rowid) {
			throw new SqlException("Errore descrittore rowid", "8");
		}
		if (!oci_bind_by_name($this->Stmt, ":rid",   $rowid, -1, OCI_B_ROWID)) {
			throw new SqlException("Errore Binding Variabili", "9");
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
							throw new SqlException("Errore Binding Variabili", "10");
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
			throw new SqlException("Errore Binding", "13");
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
		if (count($wheres)>0) foreach ($wheres as $key=>$val) {
			$where.="$key =:w_c_{$key},";
		}
		if ($wheres!=null) foreach($wheres as $key => $val) {
			ocibindbyname($this->stmt, ":w_c_{$key}", $wheres[$key]);
		}
		$this->ExecuteSelectStmt();
	}

	protected function Parse(){
		try {
			$this->Stmt = oci_parse ( $this->Conn->getConnection (), $this->Sql_Str );
//			            echo "<hr>".$this->Sql_Str."<hr>";
		} catch ( Exception $e ) {
			error_page();
			throw new SqlException ( "Errore esecuzione Query", 2 );
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
			$var= oci_execute ( $this->Stmt , OCI_DEFAULT);
			if(!$var) throw new SqlException ( "Errore esecuzione Query", 4,oci_error($this->Stmt) );

		} catch ( Exception $e ) {
			throw new SqlException ( "Errore esecuzione Query", 3 ,oci_error($this->Stmt));
		}
	}


}

class SqlException extends Exception {
	function SqlException($error, $error_code, $error_spec) {
		error_page($_SERVER['REMOTE_USER'], $error, $error_spec );
//		$log_date = date ( 'd_m_Y' );
//		$log_file="../logs/check__{$mailbox}__log_$log_date.log";
//
//		$file_check = fopen ( $log_file, "a" );
//		$file_str=date ( 'd/m/Y H:i:s' ).": CONTROLLO MAIL INIZIATO, UTENTE: {$_SERVER['REMOTE_USER']} \n";
//		fwrite ( $file_check, $file_str );
	}

}

?>
