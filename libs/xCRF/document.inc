<?
/**
 * Classe prototipo per la gestione della document
 *
 * @package FileAllegati
 */
class document_prototype {

	var $document;
	var $fields;
	var $vars;
	var $buttons;
	var $enable;
	var $query_enable;
	var $salva_js = '';
	var $invia_js = '';
	var $check_js = '';
	var $script_js = '';
	var $inrevisione_js = '';
	var $body = '';
	var $onload = '';
	var $validata = true;
	var $sql_query;
	var $sql_query_storico;
	var $PK_SERVICE;
	var $closed = false;
	var $config_service;
	var $session_vars;
	var $tb_vals;
	var $tb_vals_docs;
	var $service;
	var $uploaded_files_dir;
	var $conn;
	var $xmr;
	var $percorso_agg;
	var $errors;
	var $no_field_value_by_tb=false;
	var $insert_stmt;
	var $insert_stmt_pk;
	var $old_values;
	var $equery;
	var $stato_eq;
	var $prefix;
	var $old_values_docs_nomi;

	/**
	 * Costruttore
	 *
	 * @param dbconn $conn
	 * @param String $service
	 * @param array $config_service
	 * @param array $session_vars
	 * @param String $uploaded_files_dir
	 * @param boolean $xmr
	 * @return document_prototype
	 */
	function document_prototype($conn, $service, $config_service, $session_vars, $uploaded_files_dir, $xmr = true) {
		$this->config_service = $config_service;
		$this->session_vars = $session_vars;
		$this->uploaded_files_dir = $uploaded_files_dir;
		$this->service = $service;
		$this->conn = $conn;
		$this->prefix=$service;
		$this->xmr = $xmr;
		$this->stato_eq = "";
		if (isset ( $config_service ['PK_SERVICE'] ) && $config_service ['PK_SERVICE'] != '')
		$this->PK_SERVICE = $config_service ['PK_SERVICE'];
		else
		$this->PK_SERVICE = 'CODPAT';
	}

	/**
	 * Costruisce la document a partire dall'oggetto XML
	 *
	 * @param array $xml
	 */
	function xml_document_by_obj($xml) {
		$this->xml_document_by_vals ( $xml->vals );
	}

	/**
	 * Costruisce la document a partire dal file xml
	 *
	 * @param String $xml_file
	 */
	function xml_document_by_file($xml_file) {
		$xml = new my_xml_parser ( $xml_file );
		$this->xml_document_by_obj ( $xml );
		
//		if($this->config_service['multilang']=="1"){
//			$xml_and = simplexml_load_file($xml_file) or die("feed not loading");
//			foreach($xml_and->field as $key => $val){
//				foreach( $val->txt_value as $k => $v ){
//					echo $k ;print_R($v); echo "--<br>";
//					
//				}
//			}
//		}
	}

	/**
	 * Costruisce la document a partire dall'array vals
	 *
	 * @param array $vals 
	 */
	function xml_document_by_vals($vals) {
		$in = $this->session_vars;
		$fn = 0;
		$en = 0;
		$newtag = true;
		$this_node = new xml_node ( );
		for($i = 0; $i < count ( $vals ); $i ++) {
			$this_node->xml_node_by_array ( $vals [$i] );
			if ($this_node->type != 'cdata') {
				if ($this_node->tag == 'DOCUMENT')
				if ($this_node->type == 'open' or $this_node->type == 'complete')
				$this->document = $this_node->attributes;
				if ($this_node->tag == 'FIELD') {
					if ($this_node->type == 'open' or $this_node->type == 'complete') {
						$this->fields [$fn] = $this_node->attributes;
						$this->vars [$this_node->attributes ['VAR']] = $fn;
					}
					if ($this_node->type != 'open') {
						$fn ++;
					}
				}
				if ($this_node->tag == 'SEND')
				$this->buttons ['INVIA'] = $this_node->value;
				if ($this_node->tag == 'SUBMIT')
				$this->buttons ['SUBMIT'] = $this_node->value;
				if ($this_node->tag == 'SAVE' && $in ['USER_TIP'] != 'DM')
				$this->buttons ['SALVA'] = $this_node->value;
				//****MOd Edo 9/9/10
				if ($this_node->tag == 'REVISION' && $in ['USER_TIP'] != 'DM')
				$this->buttons ['INREVISIONE'] = $this_node->value;
				//****
				if ($this_node->tag == 'EQUERY_FORM')
				$this->buttons ['EQUERY_FORM'] = $this_node->value;
				if ($this_node->tag == 'CANCEL')
				$this->buttons ['ANNULLA'] = $this_node->value;
				if ($this_node->tag == 'DELETE_ALL')
				$this->buttons ['CANCELLA'] = $this_node->value;
				if ($this_node->tag == 'EXAM') {
					$this->enable [$en] = $this_node->attributes;
					$en ++;
				}
				if ($this_node->tag == 'TXT_VALUE'){
					if ($this_node->attributes['LANG']=='') $this->fields [$fn] ['TESTO'] = $this_node->value;
					else {
						$this->fields [$fn] ['TESTO_PLUS'][$this_node->attributes['LANG']]= $this_node->value;
					}
				}
				
				if ($this_node->tag == 'VALUE') {
					$this->fields [$fn] ['VALUE'] [$this_node->attributes ['VAL']] = $this_node->value;
					if (isset($this_node->attributes['GROUP']) && $this_node->attributes['GROUP']!='') $this->fields [$fn] ['VALUE_GROUP'] [$this_node->attributes ['VAL']] = $this_node->attributes['GROUP'];
					$this->fields [$fn] ['VALUE_TXT'] [$this_node->attributes ['VAL']] = $this_node->attributes ['TXT'];
					if($this_node->attributes['DECODE']!='')$this->fields [$fn] ['DECODE'] [$this_node->attributes ['VAL']]=$this_node->attributes['DECODE'];
					if (isset($this_node->attributes['CONDITION']) && $this_node->attributes['CONDITION']!='')
					$this->fields [$fn] ['VALUE_CONDITION'] [$this_node->attributes ['VAL']] = $this_node->attributes['CONDITION'];
					if (isset($this_node->attributes['CONDITION_VALUE']) && $this_node->attributes['CONDITION_VALUE']!='')
					$this->fields [$fn] ['VALUE_CONDITION_VALUE'] [$this_node->attributes ['VAL']] = $this_node->attributes['CONDITION_VALUE'];
					if (isset($this_node->attributes['CONDS']) && $this_node->attributes['CONDS']!='')
					$this->fields [$fn] ['VALUE_CONDS'] [$this_node->attributes ['VAL']] = $this_node->attributes['CONDS'];
					if (isset($this_node->attributes['DOCS']) && $this_node->attributes['DOCS']!='')
					$this->fields [$fn] ['VALUE_DOCS'] [$this_node->attributes ['VAL']] = $this_node->attributes['DOCS'];
				}
				
//				if($this->config_service['multilang']=="1"){
//		
//					print_R($this->fields [$fn]['VAR']);
//				}
			}
		}
		$this->document ['QUERYNAME'] = strtoupper ( $this->service ) . "_" . $this->document ['QUERYNAME'];
	}

	/**
	 * Restituisce la primary key
	 *
	 * @return array
	 */
	function pk_key() {
		$c = 0;
		for($i = 0; $i < count ( $this->fields ); $i ++) {
			if ($this->fields [$i] ['PK'] == 'yes') {
				$pk_key [$c] = $this->fields [$i] ['VAR'];
				$c ++;
			}
		}
		return $pk_key;
	}

	/**
	 * Costruisce le clausole di where sulla pk
	 *
	 * @return String
	 */
	function pk_where($binded=false) {
        $where='';
		$in = $this->session_vars;
		$pk_key = $this->pk_key ();
		for($i = 0; $i < count ( $pk_key ); $i ++) {
			if ($in [$pk_key [$i]] != 'next') {
				if ($where != '')
				$where .= ' and ';
				if(!$binded) $where .= $pk_key [$i] . "='" . $in [$pk_key [$i]] . "'";
				else $where .= $pk_key [$i] . "=:" .$pk_key [$i];
				$bind[$pk_key [$i]]= $in [$pk_key [$i]];
			}
		}
		$return['WHERE']=$where;
		$return['BIND']=$bind;
		
		Logger::send($return);
		
		if(!$binded) return $return['WHERE'];
		else return $return;
	}

	/**
	 * Costruisce la query di inserimento/update
	 *
	 * @param boolean $force_insert
	 */
	function query_builder($force_insert=false) {
		$in = $this->session_vars;
		$conn = $this->conn;
		global $_FILES;
		$dir_file = $this->uploaded_files_dir;
		foreach ( $in as $key => $value )
		$in [$key] = preg_replace ( "/'/", "''", $value );
		$sql = new query ( $conn );
		$this->progr = $in ['PROGR'];
		if ($this->xmr) {
			unset($bind);
			if ($in [$this->PK_SERVICE] == 'next')
			$this->progr = 1;
			else {
				$config_service = $this->config_service;
				$where_agg = '';
				if (isset ( $config_service ['VISITNUM_PROGR'] )) {
					$where_agg = " and visitnum_progr=:visitnum_progr";
					$bind['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
				}
				$query = "select max(visitclose) as visitclose from " . $this->service . "_coordinate where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum $where_agg";
				//$sql->set_sql (  );
				$bind['PK_SERVICE']= $in [$this->PK_SERVICE];
				$bind['VISITNUM']= $in ['VISITNUM'];
				$sql->exec ($query,$bind);//binded
				$sql->get_row ();

//				if ($sql->row ['VISITCLOSE'] == 1 && $in ['USER_TIP'] == 'DE' && !$force_insert && $in['ajax_call']=='') {
//
//					if(function_exists('testo')) error_page ( $in ['remote_userid'], testo("visitIsClosed"), "" );
//					else if(method_exists($this,'testo')) error_page ( $in ['remote_userid'], $this->testo("visitIsClosed"), "" );
//					else error_page ( $in ['remote_userid'], "Visit closed", "" );
//				}


				if ($this->progr == 'next' || $this->progr == '') {

					$query = "select max(progr) as max from " . $this->service . "_coordinate where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam $where_agg";
					
					$bind['PK_SERVICE']=$in [$this->PK_SERVICE];
					$bind['VISITNUM']=$in ['VISITNUM'];
					$bind['ESAM']=$in ['ESAM'];
					
					//$sql->set_sql ( $query );
					$sql->exec ($query,$bind);//binded
					$sql->get_row ();
					if ($sql->row ['MAX'] != '')
					$this->progr = '1';
					else
					$this->progr = $sql->row ['MAX'] + 1;
					$in ['PROGR'] = $this->progr;

				}

			}
		}
		$pk_key = $this->pk_key ();
		for($i = 0; $i < count ( $pk_key ); $i ++) {
			if ($in [$pk_key [$i]] == 'next' || $in [$pk_key [$i]] == 'progr')
			$new_insert = true;
		}

		if (! isset ( $new_insert )) {
			$binded_where = $this->pk_where (true);
			Logger::send("fdf");
			Logger::send($binded_where);
			$where = $binded_where['WHERE'];
			$bind= $binded_where['BIND'];
			if ($where != '')
			$where = "where " . $where;
			$query = "select count(*) as c from " . $this->document ['QUERYNAME'] . " $where";
			//$sql->set_sql ( $query );
			$sql->exec ($query,$bind);//binded
			$sql->get_row ();
			if ($sql->row ['C'] != '1')
			$new_insert = true;
			else
			$new_insert = false;
		}
		
		//G.Tufano 22/07/2010
		//la funzione mi restituisce il CODPAT (o altro PK_SERVICE) che può essere impostato
		//con AUTOINCREMENT (per es se CODPAT = 'next').
		//viene usato nel metodo "invia_document($xml_document, $in_s)" in estensioni di
		//study.prototype
		
		$pk_service_value = $this->query_tb ( $new_insert );
	
		if ($this->xmr)
		$this->query_abilita ();
		
		return $pk_service_value;
	}

	/**
	 * Costruisce il codice SQL dell'inserimento nella tabella
	 *
	 * @param boolean $new_insert
	 */
	function query_tb($new_insert) {
		$in = $this->session_vars;
		$conn = $this->conn;
		$dir_file = $this->uploaded_files_dir;
		$sql = new query ( $conn );
		$i = 0;

		foreach ( $this->fields as $key => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";

			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$field_obj = new $field_type ( $this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors );

			if ($field_obj->attributes ['PK'] == 'yes')
			$pk [$field_obj->attributes ['VAR']] = $in [$field_obj->attributes ['VAR']];
			if ($new_insert) {
				$field_obj->insert_stmt ( true );
				foreach ( $field_obj->value_stmt as $key_f => $val_f ) {
					if ($field_obj->value_stmt [$key_f] == "next") {
						if ($field_obj->id==$this->config_service['PK_SERVICE'] && $this->config_service['PK_SEQ']!='' && !isset($this->session_vars['ajax_call'])){
							$sql_query="select {$this->config_service['PK_SEQ']}.nextval as PK_ID from dual";
							$sql=new query($this->conn);
							$sql->set_sql($sql_query);
							$sql->exec();//non richiede binding
							$sql->get_row();
							$pk_id=$sql->row['PK_ID'];
							$this->pk_value = $pk_id;
							$in [$field_obj->attributes ['VAR']] = $pk_id;
							$this->session_vars[$field_obj->attributes ['VAR']]=$pk_id;
							$in_s=$in;
							global $in;
							$in=$in_s;
							$field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
							$field_obj->value_stmt [$key_f]=$pk_id;
						}
						else {
							if ($field_obj->attributes ['WHERE'] != '')
							$where = "where " . $field_obj->attributes ['WHERE'];
							$where = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $where );
							$query = "select max(" . $field_obj->attributes ['VAR'] . ") as max from " . $this->document ['QUERYNAME'] . " $where";
							$sql = new query ( $conn );
							$sql->set_sql ( $query );
							$sql->exec ();//complessa come list var_glob. Carlo
							$sql->get_row ();
							$in [$field_obj->attributes ['VAR']] = $sql->row ['MAX'] + 1;
							$this->pk_value = $sql->row ['MAX'] + 1;
							$field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
						}
					}
					$values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
				}
			} else {
				$field_obj->insert_stmt ();
				foreach ( $field_obj->value_stmt as $key_f => $val_f )
				$values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
			}

			if ($val ['TYPE'] == 'ckeditor') {
				unset($values[$val['VAR']]);
				foreach ( $field_obj->value_stmt as $key_f => $val_f ) {
					if($key_f==$val['VAR'])
					$clob[$val['VAR']]=$val_f;
				}
			}

		}
		/*Inserimento in coordinate*/
		if ($this->xmr) {
			$config_service = $this->config_service;
			$visitclose = '0';
			if ($new_insert) {


				if ($config_service ['VISITNUM_PROGR'] == '1') {
					$sql_query = "
						select count(*) as c from " . $this->service . "_coordinate
							where {$this->PK_SERVICE}=:pk_service
							and visitnum=:visitnum
							and esam=:esam
							and progr=:progr
							and VISITNUM_PROGR=:visitnum_progr
							  ";
					$sql = new query ( $conn );
					unset($bind);
					$bind['PK_SERVICE']=$in [$this->PK_SERVICE];
					$bind['VISITNUM']=$in ['VISITNUM'];
					$bind['ESAM']=$in ['ESAM'];
					$bind['PROGR']=$this->progr;
					$bind['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
					//$sql->set_sql ( $sql_query );
					$sql->exec ($sql_query,$bind);//binded
					$sql->get_row ();
					$count=$sql->row ['C'];
					/*if ($count > 0){
						$sql=new query($conn);
						$sql_first_insert="select insertdt from " . $this->service . "_coordinate where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "' and VISITNUM_PROGR='{$in['VISITNUM_PROGR']}'";
						$sql->set_sql ( $sql_first_insert );
						$sql->exec ();//commentata
						$sql->get_row ();
						if ($sql->row['INSERTDT']=='') $this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate,insertdt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "' and VISITNUM_PROGR='{$in['VISITNUM_PROGR']}'";
						else $this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "' and VISITNUM_PROGR='{$in['VISITNUM_PROGR']}'";
					}
					else
					$this->sql_query_coordinate = "
					insert into " . $this->service . "_coordinate
					({$this->PK_SERVICE}, visitnum, esam, progr, inizio, fine, insertdt, userid, abilitato, visitclose,VISITNUM_PROGR)
					values (" . $in [$this->PK_SERVICE] . ",'" . $in ['VISITNUM'] . "','" . $in ['ESAM'] . "','" . $this->progr . "','1','" . $in ['INVIOCO'] . "',sysdate,'" . $in ['remote_userid'] . "','1',$visitclose, {$in['VISITNUM_PROGR']})";*/
				} else {

					$sql_query = "
					select count(*) as c from " . $this->service . "_coordinate
						where {$this->PK_SERVICE}=:pk_service
						and visitnum=:visitnum
						and esam=:esam
						and progr=:progr
						  ";
					$sql = new query ( $conn );
					unset($bind);
					$bind['PK_SERVICE']=$in [$this->PK_SERVICE];
					$bind['VISITNUM']=$in ['VISITNUM'];
					$bind['ESAM']=$in ['ESAM'];
					$bind['PROGR']=$in ['PROGR'];
					//$sql->set_sql ( $sql_query );
					$sql->exec ($sql_query,$bind); //binded
					$sql->get_row ();
					$count=$sql->row ['C'];
					/*if ($count > 0)
					$this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "'";
					else
					$this->sql_query_coordinate = "insert into " . $this->service . "_coordinate ({$this->PK_SERVICE}, visitnum, esam, progr, inizio, fine, insertdt, userid, abilitato, visitclose) values (" . $in [$this->PK_SERVICE] . ",'" . $in ['VISITNUM'] . "','" . $in ['ESAM'] . "','" . $this->progr . "','1','" . $in ['INVIOCO'] . "',sysdate,'" . $in ['remote_userid'] . "','1',$visitclose)";*/
				}
			} else {
			/*	if (isset ( $config_service ['VISITNUM_PROGR'] ) && $config_service ['VISITNUM_PROGR'] == 1)
				$this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "' and VISITNUM_PROGR='{$in['VISITNUM_PROGR']}'";
				else
				$this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "'";*/
			}

		}

		/*		Inserimento in storico		*/
		$where = $this->pk_where ();
		//sql-injection CARLO
		if (! $new_insert && ! isset ( $in ['ID_QUERY'] )){
			$this->sql_query_storico = "insert into S_" . $this->document ['QUERYNAME'] . " select '" . $in ['remote_userid'] . "', sysdate, storico_id.nextval, 'V', '',  " . $this->document ['QUERYNAME'] . ".* from " . $this->document ['QUERYNAME'] . " where $where";
			$this->sql_query_storico = "insert into S_" . $this->document ['QUERYNAME'] . " select :remote_userid, sysdate, storico_id.nextval, 'V', '',  " . $this->document ['QUERYNAME'] . ".* from " . $this->document ['QUERYNAME'] . " where $where";
			$bindVars["remote_userid"]=$in['remote_userid'];
			
		}
		if (! $new_insert && isset ( $in ['ID_QUERY'] )){
			$this->sql_query_storico = "insert into S_" . $this->document ['QUERYNAME'] . " select '" . $in ['remote_userid'] . "', sysdate, storico_id.nextval, 'E', '" . $in ['ID_QUERY'] . "',  " . $this->document ['QUERYNAME'] . ".* from " . $this->document ['QUERYNAME'] . " where $where";
			$this->sql_query_storico = "insert into S_" . $this->document ['QUERYNAME'] . " select :remote_userid, sysdate, storico_id.nextval, 'E', '" . $in ['ID_QUERY'] . "',  " . $this->document ['QUERYNAME'] . ".* from " . $this->document ['QUERYNAME'] . " where $where";
			$bindVars["remote_userid"]=$in['remote_userid'];
		}
		if ($this->sql_query_storico != '') {
			$sql = new query ( $conn );
			$sql->ins_upd ( $this->sql_query_storico, $bindVars );//binded
			
		}

		$values['PROGR']=$this->progr;
		/*  	Inserimento nella tabella 	*/
		//Edo: qua metto gli array dei clob?
		//		print_r($clob);
		if ($new_insert) {
			$result = $sql->insert ( $values, $this->document ['QUERYNAME'], $pk, true, null, $clob);
		} else {
			$result = $sql->update ( $values, $this->document ['QUERYNAME'], $pk, $clob );
		}
		$this->session_vars = $in;
		$this->errors=$sql->getErrors();
		
		//G.Tufano 22/07/2010
		//restituisco l'ID del paziente appena creato, letto dalla sequence
		//per poterlo utilizzare altrove
		//(per esempio per la chiusura di una scheda "registrazione" 
		$pk_serv_val = $in [$this->PK_SERVICE];
		return $pk_serv_val;

	}

	/**
	 * Prepara lo statment della insert
	 *
	 * @param boolean $new_insert
	 */
	function insert_stmt_prepare($new_insert=false){
        $in = $this->session_vars;
	    global $conn;
		foreach ( $this->fields as $key => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";

			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$field_obj = new $field_type ( $this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors );

			if ($field_obj->attributes ['PK'] == 'yes')
			$pk [$field_obj->attributes ['VAR']] = $in [$field_obj->attributes ['VAR']];
			if ($new_insert) {
				//non deve capitare
				$field_obj->insert_stmt ( true );
				foreach ( $field_obj->value_stmt as $key_f => $val_f ) {
					if ($field_obj->value_stmt [$key_f] == "next") {
						if ($field_obj->id==$this->config_service['PK_SERVICE'] && $this->config_service['PK_SEQ']!='' && !isset($this->session_vars['ajax_call'])){
							$sql_query="select {$this->config_service['PK_SEQ']}.nextval as PK_ID from dual";
							$sql=new query($this->conn);
							$sql->set_sql($sql_query);
							$sql->exec();//non richiede binding
							$sql->get_row();
							$pk_id=$sql->row['PK_ID'];
							$this->pk_value = $pk_id;
							$in [$field_obj->attributes ['VAR']] = $pk_id;
							$this->session_vars[$field_obj->attributes ['VAR']]=$pk_id;
							$in_s=$in;
							global $in;
							$in=$in_s;
							$field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
							$field_obj->value_stmt [$key_f]=$pk_id;
						}
						else {
							if ($field_obj->attributes ['WHERE'] != '')
							$where = "where " . $field_obj->attributes ['WHERE'];
							$where = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $where );
							$query = "select max(" . $field_obj->attributes ['VAR'] . ") as max from " . $this->document ['QUERYNAME'] . " $where";
							$sql = new query ( $conn );
							$sql->set_sql ( $query );
							$sql->exec ();//complessa da gestire con carlo
							$sql->get_row ();
							$in [$field_obj->attributes ['VAR']] = $sql->row ['MAX'] + 1;
							$this->pk_value = $sql->row ['MAX'] + 1;
							$field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
						}
					}
					$values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
				}
			} else {
				$field_obj->insert_stmt ();
				foreach ( $field_obj->value_stmt as $key_f => $val_f )
				$values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
			}
		}
		$this->insert_stmt=$values;
		$this->insert_stmt_pk=$pk;

	}

	/**
	 * Individua le differenze
	 *
	 * @return arrray
	 */
	function differences(){
		$this->closed_document();
		$this->insert_stmt_prepare();
		$differences_idx=0;
		foreach ($this->insert_stmt as $key => $value) {
			if(trim($this->tb_vals[$key])!=trim($value)) {
				$differences[$differences_idx]['FIELD']=$this->fields[$this->vars[$key]]['TESTO'];
				$differences[$differences_idx]['VAR']=$key;
				$differences[$differences_idx]['NOMETAB']=$this->document ['QUERYNAME'];
				$differences[$differences_idx]['VAL_OLD']=$this->tb_vals[$key];
				$differences[$differences_idx]['VAL_NEW']=$value;
				$differences_idx++;
			}
		}
		return $differences;
	}

	/**
	 * Controlla le condizioni di obbligatorietà della document
	 *
	 * @return boolean
	 */
	function valida() {
		$this->validata = true;

		for($i = 0; $i < count ( $this->fields ); $i ++) {
			if (isset ( $this->fields [$i] ['TYPE'] ) && $this->fields [$i] ['TYPE'] != '')
			$field_type = "field_{$this->fields[$i]['TYPE']}";
			else
			$field_type = "field";

			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$field_obj = new $field_type ( $this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors );
			$field_obj->make_open_html ();
			
			if (! $field_obj->validata) {
				Logger::send("La scheda incompleta è: (id)". $field_obj->id);
				$this->errors[$field_obj->id]=$field_obj->errors[$field_obj->id];
				$this->validata = $field_obj->validata;
			}



		}
		if ($this->validata) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Allinea la struttura della tabella alla document
	 *
	 * @return boolean
	 */
	function allinea_db() {
        $sql_pk_fields=null;
        $sql_create_fields=null;
        $eq_sql_str=null;
		$in=$this->session_vars;
		$conn=$this->conn;
		$service=$this->service;
		$tb_exist = false;
		
		$str_synonym="select * from USER_SYNONYMS where synonym_name='" . $this->document ['QUERYNAME'] . "'";
		$sql = new query ( $conn );
		$sql->set_sql ( $str_synonym );
		$sql->exec ();//non richiede binding
		$sql->get_row();
		if($sql->row['TABLE_NAME']!='')$this->document ['QUERYNAME']=$sql->row['TABLE_NAME'];
		$query = "select column_name from all_col_comments where table_name='" . $this->document ['QUERYNAME'] . "'";
		$sql = new query ( $conn );
		$sql->set_sql ( $query );
		$sql->exec ();//non richiede binding
		$all_field_exist = true;
		foreach ( $this->fields as $key => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";

			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$this->no_field_value_by_tb=true;
			$field_obj = new $field_type ( $this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
			$this->no_field_value_by_tb=false;
			$allinea_stmt [$key] = $field_obj->allinea_db ();
			if ($field_obj->attributes ['PK'] == 'yes') {
				$sql_pk_fields .= "{$field_obj->attributes['VAR']},";
			}
		}

		$sql_pk_fields = rtrim ( $sql_pk_fields, "," );
		if ($sql->numrows > 0) {
			
			$tb_exist = true;
			$i = 0;
			while ( $sql->get_row () ) {
				$res [$i] = $sql->row ['COLUMN_NAME'];
				$i ++;
			}
		}
		

		if ($tb_exist) {
			$sql_pk = "";
			$c = 0;
			$all_field_exist = true;
			foreach ( $allinea_stmt as $key => $val ) {
				if ($val != '') {
					$field_exist = false;
					foreach ( $val as $vk => $vval ) {
						$nome_campo = split ( " ", $vval );
						$field_exist [$key] [$vk] = false;
						foreach ( $res as $key_res => $val_res ) {
							if ($val_res == $nome_campo [0] || $nome_campo [0] == '') {
								$field_exist [$key] [$vk] = true;
							}
						}
					}
					foreach ( $field_exist as $key => $val ) {
						foreach ( $val as $vk => $boolval )
						if (! $boolval) {
							$all_field_exist = false;
							$index = (count ( $this->fields ) * $vk) + $key;
//							$eq_sql_str [$index] = "alter table EQ_" . $this->document ['QUERYNAME'] . " add {$allinea_stmt[$key][$vk]}";
							$s_sql_str [$index] = "alter table S_" . $this->document ['QUERYNAME'] . " add {$allinea_stmt[$key][$vk]}";
							$sql_str [$index] = "alter table " . $this->document ['QUERYNAME'] . " add {$allinea_stmt[$key][$vk]}";
						}
					}
				}
			}
			$sql_pk_drop = "alter table " . $this->document ['QUERYNAME'] . " drop constraint PK_" . $this->document ['QUERYNAME'] . " cascade";
			$sql_pk = "alter table " . $this->document ['QUERYNAME'] . " add constraint PK_" . $this->document ['QUERYNAME'] . " primary key ($sql_pk_fields)";
			/*$sql_fk_coord_drop = "alter table " . $this->document ['QUERYNAME'] . " drop constraint FK_" . $this->document ['QUERYNAME'] . "_COORD cascade";*/
			global $config_service;
			/*if ($config_service ['VISITNUM_PROGR'] == 1)
			$sql_fk_coord = "alter table " . $this->document ['QUERYNAME'] . " add constraint FK_" . $this->document ['QUERYNAME'] . "_COORD foreign key (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";
			else
			$sql_fk_coord = "alter table " . $this->document ['QUERYNAME'] . " add constraint FK_" . $this->document ['QUERYNAME'] . "_COORD foreign key (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";*/
		} else {
			$this->body .= "Table <b>" . $this->document ['QUERYNAME'] . "</b> doesn't exist<br/>";
			foreach ( $allinea_stmt as $key => $val ) {
				foreach ( $val as $key_f => $val_f )
				if ($val_f != '')
				$sql_create_fields .= "{$val_f},";
			}
			$sql_create_fields = rtrim ( $sql_create_fields, "," );
			$sql_str_ini = "create table " . $this->document ['QUERYNAME'] . '(';
			$sql_str_end = ")";
			$sql_str [0] = $sql_str_ini . $sql_create_fields . $sql_str_end;
			$sql_pk = "alter table " . $this->document ['QUERYNAME'] . " add constraint PK_" . $this->document ['QUERYNAME'] . " primary key ($sql_pk_fields)";
			$config_service=$this->config_service;
			/*if ($config_service ['VISITNUM_PROGR'] == 1)
			$sql_fk_coord = "alter table " . $this->document ['QUERYNAME'] . " add constraint FK_" . $this->document ['QUERYNAME'] . "_COORD foreign key (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";
			else
			$sql_fk_coord = "alter table " . $this->document ['QUERYNAME'] . " add constraint FK_" . $this->document ['QUERYNAME'] . "_COORD foreign key (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";*/
//			$eq_sql_str [0] = "create table EQ_" . $this->document ['QUERYNAME'] . " (ID NUMBER, COMMENTO varchar2(400)," . $sql_create_fields . $sql_str_end;
//			$eq_sql_str [1] = "alter table EQ_" . $this->document ['QUERYNAME'] . " add constraint EQ_PK_" . $this->document ['QUERYNAME'] . " primary key (ID)";

			$s_sql_str [0] = "create table S_" . $this->document ['QUERYNAME'] . "(USERID VARCHAR2(200 CHAR),MODDT DATE,MODPROG NUMBER not null,FL_QUERY CHAR(1) not null,ID_QUERY NUMBER(6)," . $sql_create_fields . $sql_str_end;
			$s_sql_str [1] = "alter table S_" . $this->document ['QUERYNAME'] . " add constraint S_PK_" . $this->document ['QUERYNAME'] . " primary key (MODPROG)";

		}
		if (isset ( $in ['CREATE_DOC'] ) || isset ( $in ['CREATE_DOC_' . $this->document ['QUERYNAME']] )) {
			foreach ( $sql_str as $key => $val ) {
				$sql = new query ( $conn );
				$sql->ins_upd ($val);//non richiede binding
			}
			foreach ( $eq_sql_str as $key => $val ) {
				$sql = new query ( $conn );
				$sql->ins_upd ($val);//non richiede binding
			}
			foreach ( $s_sql_str as $key => $val ) {
				$sql = new query ( $conn );
				$sql->ins_upd ($val);//non richiede binding
			}
			if ($sql_pk_drop != '') {
				$sql = new query ( $conn );
				$sql->ins_upd ($sql_pk_drop);//non richiede binding
			}
			$sql = new query ( $conn );
			$sql->ins_upd ($sql_pk);//non richiede binding
			/*if ($sql_fk_coord_drop != '') {
				$sql = new query ( $conn );
				$sql->set_sql ( $sql_fk_coord_drop );

			}*/
			$sql = new query ( $conn );
			//$sql->set_sql ( $sql_fk_coord );
			return true;
		} else
		return ($tb_exist && $all_field_exist);
	}

	/**
	 * Controlla se la scheda e chiusa e recupera i dati salvati
	 *
	 * @param number $progr
	 * @return boolean
	 */
	function closed_document($progr=null) {
        $fields=null;
		$in = $this->session_vars;
		if (isset($progr)) $in['PROGR']=$progr;
		$conn = $this->conn;
		unset($bind);
		if ($in [$this->PK_SERVICE] == 'next')
			return false;
		else{
			$where = "VISITNUM=:visitnum and ESAM=:esam and {$this->PK_SERVICE}=:pk_service";
			$bind['VISITNUM']=$in ['VISITNUM'];
			$bind['ESAM']=$in ['ESAM'];
			$bind['PK_SERVICE']=$in [$this->PK_SERVICE];
		}
		if ($in ['PROGR'] != ''){
			$where .= "  and PROGR=:progr";
			$bind['PROGR']=$in ['PROGR'];
		}
		if (isset ( $in ['VISITNUM_PROGR'] )){
			$where .= " and VISITNUM_PROGR=:visitnum_progr";
			$bind['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
		}
		$query = "select fine, USERID from " . $this->service . "_coordinate where $where";
		$sql = new query ( $conn );
		//$sql->set_sql ( $query );
		$sql->exec ($query,$bind);//binded
		if ($sql->get_row () || $in ['equery_vis'] != '' || $in ['equery_view'] != '' || $in ['eform'] != '' || $in ['TB_COLL'] != '') {
//			echo($sql->row ['FINE']."asd");
			if ($sql->row ['FINE'] == 1)
			$ret = true;
			else
			{
				//modifica chiara del 06/07/09: al posto di $sql->row ['FINE']=='' inserito $sql->row ['FINE']!='1'
				if ($sql->row['USERID']=='' || $sql->row['USERID']==$in['remote_userid'] || $sql->row ['FINE']=='' || $sql->row ['FINE']=='0') {
					$ret=false;
				} else {
					$ret = true;
				}
			}
			
//			if($ret) echo "asd";
			
			$sql_query = "select column_name from all_col_comments where table_name='" . strtoupper ( $this->document ['QUERYNAME'] ) . "'";
			$where = '';
			foreach ( $this->fields as $key => $val ) {
				if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
				$field_type = "field_{$val['TYPE']}";
				else
				$field_type = "field";
				if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
					include_once $this->config_service['field_lib'] . $field_type . ".inc";
				} else
				include_once "{$field_type}.inc";
				$this->no_field_value_by_tb=true;
				$field_obj = new $field_type ( $this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
				$this->no_field_value_by_tb=false;
				$field_obj->insert_stmt ( false );

				if (isset ( $field_obj->field_stmt ))
				foreach ( $field_obj->field_stmt as $key => $field_name ) {
					$fields .= $field_name . ",";
					if (! isset ( $fields_array ))
					$index = 0;
					else
					$index = count ( $fields_array );
					$fields_array [$field_name] = $field_name;
				}
			}
			$fields = rtrim ( $fields, "," );

			$str_synonym="select * from USER_SYNONYMS where synonym_name='" . $this->document ['QUERYNAME'] . "'";
			//			echo $str_synonym;
			$sql = new query ( $conn );
			$sql->set_sql ( $str_synonym );
			$sql->exec ();//non richiede binding
			$sql->get_row();
			if($sql->row['TABLE_NAME']!='')$this->document ['QUERYNAME']=$sql->row['TABLE_NAME'];

			$sql_pk = "select column_name from user_cons_columns where table_name='" . $this->document ['QUERYNAME'] . "' and constraint_name=(select constraint_name from user_constraints where table_name='" . $this->document ['QUERYNAME'] . "' and constraint_type='P')";
			$query = new query ( $conn );
			$query->set_sql ( $sql_pk );
			$query->exec ();//non richiede binding
			$new_insert = false;
			$where = '';
			unset($bind_where);
			while ( $query->get_row () ) {
				if (isset ( $in [$query->row ['COLUMN_NAME']] )) {
					if ($where != '')
					$where .= " and ";
					$where .= $query->row ['COLUMN_NAME'] . "=:" .$query->row ['COLUMN_NAME'] ;
					$bind_where[$query->row ['COLUMN_NAME']]=$in [$query->row ['COLUMN_NAME']];
					if (! isset ( $wheres ))
					$index = 0;
					else
					$index = count ( $wheres );

					$wheres [$query->row ['COLUMN_NAME']] ['OP'] = "=";
					$wheres [$query->row ['COLUMN_NAME']] ['f1'] = $query->row ['COLUMN_NAME'];
					$wheres [$query->row ['COLUMN_NAME']] ['f2'] = $in [$query->row ['COLUMN_NAME']];

				}
			}
			$tables [$this->document ['QUERYNAME']] = "";
			$query_s="select * from {$this->document ['QUERYNAME']} where $where";
			
			$sql_s = new query ( $conn );
			//$sql_s->set_sql($query_s);
			$sql_s->exec($query_s,$bind_where);//binded
			if ($sql_s->numrows > 1)
			error_page ( $in ['remote_userid'], "Query:\n $query_s\n results: ({$sql_s->str})" . $sql_s->numrows . " records", "" );
			$sql_s->get_row ();
			$inputval = $sql_s->row;
			$this->tb_vals = $inputval;
			$this->closed = $ret;
			return $ret;

		} else {


			$this->closed = false;
			return false;
		}
	}

	/**
	 * Costruisce il codice html della document in compilazione
	 *
	 * @param boolean $force_open
	 * @param boolean $exclude_send_buttons
	 * @param boolean $equery
	 */
	function open_document($force_open=false,$exclude_send_buttons=false, $equery=false) {
        $testo_rev=null;
        $controlli=null;
        $equery_option=null;
        $testo_rev=null;
		$in = $this->session_vars;
		$conn = $this->conn;
		$inputval = $this->tb_vals;
		$service = $this->service;
		$config_service = $this->config_service;

//echo "Ruolo ".$this->config_service['eQuerySpec']['Integrazione']['ROLE']."<br>";
//echo "act ".$this->session_vars['WFact']."<br>";

		$template_form_html = '';
		if ($this->xmr) {
			if ($in [$config_service ['PK_SERVICE']] != 'next') {
				if (isset ( $in ['VISITNUM'] ) && isset ( $in ['ESAM'] )) {
					$sql_query = "select visitclose from {$service}_COORDINATE where VISITNUM=:visitnum and ESAM=:esam and VISITNUM_PROGR=:visitnum_progr and {$config_service['PK_SERVICE']}=:pk_service";
					$sql = new query ( $conn );
					unset($bind);
					$bind['VISITNUM']=$in['VISITNUM'];
					$bind['ESAM']=$in['ESAM'];
					$bind['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
					$bind['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
					//$sql->set_sql ( $sql_query );
					$sql->exec ($sql_query,$bind);//binded
					$sql->get_row ();
					if ($sql->row ['VISITCLOSE'] == 1 && $in ['USER_TIP'] == 'DE' && !$force_open) {
						error_page ( $in ['remote_userid'], $this->testo("visitIsClosed"), "" );
					}
				}
			}
		}
		$editing = true;
		if($this->config_service['lang']=="en")$lang=1;
		else $lang=0;
		$this->salva_js = "
		  		function salva_f(){
		  		cf();
		  		f=document.forms[0];
					el=f.elements;

					specifiche='A=ON&L=$lang&F=0';
		  		c1='';
		  		";
		$this->invia_js = "
		  		function invia_f(ajax){
		  		cf();
		  		if (ajax==undefined) ajax=true;
		  		f=document.forms[0];
					el=f.elements;
					specifiche='A=ON&L=$lang&F=0';
		  		c1='';
		  		";
		$this->check_js = '
		  		function cf(){
		  		var el;
		  		var f;
		  		f=document.forms[0];
					el=f.elements;
		  		document.forms[0].action=\'\';
		  		';
		$colonne = $this->document ['COLS'];
		$sysdate = date ( "dmY" );
		if (isset($_GET['link_to']) && $_GET['link_to']!='') $this->document ['LINK_TO']=$_GET['link_to'];
		$this->percorso_agg= "&nbsp;&gt;&nbsp;<b>" . $this->document ['TITOLO'] . "</b>";
		if ($equery){
			$sql_query="select equery_int from {$this->service}_eq where stato in (0,2) and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";
			$sql=new query($this->conn);
			if ($sql->get_row($sql_query)) $equery_int=$sql->row['EQUERY_INT'];
			else $equery_int=0;
			if ($equery_int!='') {

				if(strtolower($this->config_service['lang'])=='en'){
					$string_text="Warning! fields with the symbol <img src=\"images/eq_img.png\" width=20px> has been modified";
				}else{
					$string_text="Attenzione! i campi contrassegnati con il simbolo <img src=\"images/eq_img.png\" width=20px> hanno subito modifiche";
				}

				$note_eq="
				<div style='font-align:center;color:red;font-weight:bold'>
				$string_text
				</div>
				";
			}
		}
		$this->body = $note_eq.'
					   <form method="post" class="niceform" action="index.php" enctype="multipart/form-data"  onsubmit="return false;" onKeypress="if (event.keyCode==13) return false;">
		               <input type="hidden" name="' . $this->document ['QUERYNAME'] . '"/>
		               <input type="hidden" name="form" value="' . $in ['form'] . '"/>
		               <input type="hidden" name="link_to" value="' . $this->document ['LINK_TO'] . '"/>
		               <table align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
									  <tbody>
									  	<tr>
									  		<td>
									 ';

		$width = 100 / ($colonne * 2);
		if ($this->document ['TEMPLATE'] != '' && $in ['genera_template_html'] != "si")
		$template = file_get_contents ( "xml/{$this->document['TEMPLATE']}" );
		else {
			$this->body .= '
			       				 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
			       				 <!-- CAMPI -->' . $testo_rev;
			$template_form_html = '
				<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
			       				 <!-- CAMPI -->';
			$template = '';
			for($i = 0; $i < $colonne; $i ++) {
				$this->body .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
				$template_form_html .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
			}
			$this->body .= "</tr>";
			$template_form_html .= "</tr>";

		}

		$c = 0;
		foreach ( $this->fields as $i => $val ) {
			if ($val ['CONDITION'] != '')
			$condition_array [count ( $condition_array )] = $val ['CONDITION'];
			if($val ['TYPE']=="file_cme" || $val ['TYPE']=="file_doc") {
				$file_doc_eq['VAR']=$val['VAR'];
				$file_doc_eq['THREAD']=$val['THREAD'];
				$file_doc_eq['TOPIC']=$val['TOPIC'];
				$files_doc[]=$file_doc_eq;
				/*
			        [TYPE] => file_doc
				    [VAR] => COMUNICAZIONI_FILE
				    [THREAD] => Comunicazione
				    [TOPIC] => Communications to AIFA
				 */
			}
		}
		$condition_array = array_unique ( $condition_array );
		
		if ($equery){
			
			if($equery_int!="" || $equery_int!="0") {

			$_GET['VISITNUM_PROGR']-=0;

			if(isset($_GET['PROGR'])) $progr=$_GET['PROGR'];
			else $progr=1;

			$sql_query="select * from {$this->service}_eqfield where
				eq_int=:eq_id
				and esam=:esam
				and visitnum=:visitnum
				and visitnum_progr=:visitnum_progr
				and progr=:progr
				and {$this->PK_SERVICE}=:pk_service
				";

//			echo( $equery_int."<br>");
			unset($bind);
			$bind['EQ_ID']=$equery_int;
			$bind['ESAM']=$_GET['ESAM'];
			$bind['VISITNUM']=$_GET['VISITNUM'];
			$bind['VISITNUM_PROGR']=$_GET['VISITNUM_PROGR'];
			$bind['PROGR']=$progr;
			$bind['PK_SERVICE']=$_GET[$this->PK_SERVICE];
			$sql->exec($sql_query,$bind);//binded
			
			//------------------------------------
			$id_tipo_ref=$config_service['PRJ']*100000+$_GET[$this->PK_SERVICE];
			
//			print_r($files_doc);

			foreach($files_doc as $l=>$allegati) {
			unset($bind_array);
			$topic=preg_replace("/'/", "''", $allegati['TOPIC']);
			if ($topic!='') {
				$topic_where="topic=:topic";
				$bind_array['TOPIC']=$topic;
			}
			else $topic_where="topic is null";	
				
			$thread=$allegati['THREAD'];
			$thread=preg_replace("/'/", "''", $thread);

			$thread=str_replace("à","%",$thread);
			$thread=str_replace("è","%",$thread);
			$thread=str_replace("ì","%",$thread);
			$thread=str_replace("ò","%",$thread);
			$thread=str_replace("ù","%",$thread);
		
			$bind_array['ID_TIPO_REF']=$id_tipo_ref;
			$bind_array['TITOLO']=$thread;
			//PENULTIMO!!!
			$sql_query="
				select
				   d.id,
			       d.titolo as titolo,
			       d.autore,
			       d.data,
			       d.keywords as keywords,
			        (select
			            NOME_FILE
			           from docs d1
			        	where d1.tipo_doc='Doc_Area'
			        	and d1.id_tipo_ref=:id_tipo_ref
			        	and d1.id=
			         		(select max(d2.id) from docs d2
			         			where d2.tipo_doc='Doc_Area'
			        and d2.id_tipo_ref=:id_tipo_ref
			        and d2.id_ref=d.id and d2.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref=:id_tipo_ref
			        and d99.id_ref=d.id
			        ))
			        ) as nome_file,
			       (
			        select
			          max(d3.id)
			           from docs d3
			        where d3.tipo_doc='Doc_Area' and d3.id_tipo_ref=:id_tipo_ref and d3.id_ref=d.id and d3.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref=:id_tipo_ref
			        and d99.id_ref=d.id
			        )
			        ) as last_ver
	
			        from docs d
			        where
			        	tipo_doc='Doc_Area'
			        	and id_tipo_ref=:id_tipo_ref
			        	and id=id_ref
			        	and $topic_where
						and d.titolo like :TITOLO
					";
//			echo( "<br>".$sql_query."<br>1167 document");
			$sql2=new query($this->conn);
			$sql2->exec($sql_query, $bind_array);//binded
			$sql2->get_row();
			//piccolo trick per i documenti allegati
			foreach($files_doc as $key => $val) {
				if($sql2->row['KEYWORDS']==$val['VAR']) {
					$this->old_values[$val['VAR']]=$sql2->row['LAST_VER'];
					$this->old_values_docs_nomi[$val['VAR']]=$sql2->row['NOME_FILE'];
				}
			}
			
			} //chiudo qua foreach $c
			//------------------------------------
			}
			
			foreach ($this->tb_vals as $k=>$v) $this->old_values[$k]=$v;

			while ($sql->get_row()){
				$this->tb_vals[$sql->row['FIELD']]=$sql->row['VALORE'];
			}
		}
		foreach ( $this->fields as $i => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";
			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$field_obj = new $field_type ( $this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors );
			if (isset($condition_array) && is_array($condition_array)) foreach ( $condition_array as $key => $val ) {
				if ($val == $field_obj->id)
				$field_obj->attributes ['CALL_CF'] = "yes";
			}
			if ($inputval [$this->document ['READONLY']] == 1 && $inputval [$field_obj->id] != '') {

				if ($field_obj->id != $this->document ['READONLY_COMM']) {

					$field_obj->attributes ['DISABLED'] = 'yes';
				}
			}
			$field_obj->make_open_html ($equery);
			if ($template == '') {
				if ($field_obj->attributes ['HIDE'] == 'yes') {
					if (isset ( $field_obj->attributes ['NAME'] ) && $field_obj->attributes ['NAME'] != '') {
						$template_form_html .= "</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>";
						$this->body .= "</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>";
					} else {
						$template_form_html .= "\n<tr id='tr_{$field_obj->attributes['VAR']}'>";
						$this->body .= "\n<tr id='tr_{$field_obj->attributes['VAR']}'>";
					}
					$c = 0;
				}

				if ($colonne == $c) {
					$template_form_html .= "</tr>\n";
					$this->body .= "</tr>\n";
					$c = 0;
				}
				if ($c == 0 && $field_type != 'field_hidden' && $field_obj->attributes ['HIDE'] != 'yes') {
					$this->body .= "<tr>";
					$template_form_html .= "<tr>";
				}
				#echo $c;
				if ($field_obj->attributes ['TYPE'] != 'hidden') {
					if ($field_obj->attributes ['COLS'] == '')
					$c ++;
					else {
						$c += $field_obj->attributes ['COLS'];

					}
				}
				if ($field_obj->attributes ['COLS'] == '')
				$field_obj->attributes ['COLS'] = 1;
				if ($field_obj->attributes ['COLSPAN'] == '')
				$field_obj->attributes ['COLSPAN'] = 1;
				$colspan = $field_obj->attributes ['COLS'] * $field_obj->attributes ['COLSPAN'];
				if ($field_obj->attributes ['TYPE'] != '') {
					if ($field_obj->attributes ['COLSPAN'] == 1) {
						if ($field_obj->attributes ['TYPE'] == 'hidden') {

							$template_form_html .= "<<{$field_obj->id}>>";
						} else
						$template_form_html .= "
				<td  class='destra' colspan=\"$colspan\" id=\"cell_{$field_obj->id}\"><<TESTO {$field_obj->id}>></td>
				<td  class='input' colspan=\"$colspan\" id=\"cell_input_{$field_obj->id}\"><<{$field_obj->id}>></td>
				";
					} else {
						if ($field_obj->attributes ['TYPE'] == 'hidden')
						$template_form_html .= "<<{$field_obj->id}>>";
						else
						$template_form_html .= "
					<td  class='input' colspan=\"$colspan\" id=\"cell_input_{$field_obj->id}\"><<TESTO {$field_obj->id}>><<{$field_obj->id}>></td>
					";
					}
				} else
				$template_form_html .= "\n" . $field_obj->html;

				$this->body .= "\n" . $field_obj->html;
			} else {
				$template = str_replace ( "<<{$field_obj->id}>>", $field_obj->input_field, $template );
				$template = str_replace ( "<<TESTO {$field_obj->id}>>", $field_obj->input_txt, $template );
			}
			$this->salva_js .= $field_obj->salva_js;
			$this->check_js .= $field_obj->check_js;
			$this->invia_js .= $field_obj->invia_js;
			$this->script_js .= $field_obj->script;
			if (! $field_obj->validata)
			$this->validata = $field_obj->validata;
			$controlli .= $field_obj->controlli;
		}
		$js_function_on_send = $this->document ['JS_FUNCTION'];
		if ($this->document ['JS_ONSAVE'] == "yes")
		$js_function_on_save = $this->document ['JS_FUNCTION'];
		else
		$js_function_on_save = $this->document ['JS_ONSAVE'];
		$js_function_on_load = $this->document ['LOAD'];
		if ($template == '') {
			$this->body .= "
		  <!--FINE CAMPI-->
		  ";
			$template_form_html .= "
			<!--FINE CAMPI-->
			</table>
			";
		}
		if ($in ['genera_template_html'] == "si") {
			die ( $template_form_html );
		}
		$this->onload = $js_function_on_load;
		$this->onload .= 'cf()';
		$this->check_js .= '
		  }';
		if($this->config_service['jquery']) $this->check_js .= '$(document).ready(function(){'.$this->script_js."
		});
		  ";
		$this->salva_js .= '
		  rc=contr(c1,specifiche);
			if (rc) {return false}
			' . $controlli . '
		  if (!rc){
		  ' . $js_function_on_save . '
		   document.forms[0].INVIOCO.value=\'0\';
		   document.forms[0].action=\'index.php\';
		    el=document.getElementsByTagName(\'TR\')
		   for (i=0;i<el.length;i++) el[i].style.display=\'\';
		   f=document.forms[0];
			 el=f.elements;
		   for (i=0;i<el.length;i++) el[i].disabled=false;
		   ajax_send_form(0);

		   }
		  }';
		  if($this->config_service['jquery2'])$contr="jContr";
		  else $contr="contr";
		$this->invia_js .= '
		   rc='.$contr.'(c1,specifiche);
				if (rc) {return false}
		   ' . $controlli . '
		   if (!rc){
			   ' . $js_function_on_send . '
			   document.forms[0].INVIOCO.value=\'1\';
			   document.forms[0].action=\'index.php\';
			    el=document.getElementsByTagName(\'TR\')
		   		for (i=0;i<el.length;i++) el[i].style.display=\'\';
			   f=document.forms[0];
				 el=f.elements;
			   for (i=0;i<el.length;i++) el[i].disabled=false;
			   if (document.forms[0].EQUERY_INT) {
			   	document.forms[0].submit();
			   		return;
				}
			   if (ajax) ajax_send_form(0);
			   else document.forms[0].submit();
			  }
		  }';
		if ($template == '')
		$this->body .= '</table><p align=center>';
		else
		$this->body .= $template . "<p align=center>";
		if (isset ( $in ['eform'] ) && $in ['USER_TIP'] != 'DM')
		$this->body .= '
		  <input type="submit" value="Vai alla form" name="equery" onclick="window.location.href=\'index.php?equery&amp;VISITNUM=\'+document.forms[0].VISITNUM.value+\'&amp;ESAM=\'+document.forms[0].VISITNUM.value+\'&amp;{$this->PK_SERVICE}=\'+document.forms[0].'.$this->PK_SERVICE.'.value+\'&amp;CENTER=\'+document.forms[0].CENTER.value+\'&amp;QUESTION=\'+document.forms[0].QUESTION.value+\'&amp;PROGR=\'+document.forms[0].PROGR.value;"/>
		  ';
		if ($equery){

			if(strtolower($this->config_service['lang'])=='en'){
					$integra_button_text="Integrate eQuery";
			}else{
					$integra_button_text="Integra Scheda";
			}

			$this->body .= '
			<input type="hidden" value="'.$equery_int.'" name="EQUERY_INT">
		  	<input type="submit" value="'.$integra_button_text.'" name="salva" onclick="invia_f();"/>';
			$exclude_send_buttons=true;
		}
		if(!$exclude_send_buttons){
			if ($this->buttons ['SALVA'] && ($in ['USER_TIP'] != 'DM' || isset ( $in ['eform'] )))
			$this->body .= '
		  	<input type="submit" value="' . $this->buttons ['SALVA'] . '" name="salva" onclick="salva_f();"/>';
			if ($this->buttons ['SUBMIT'] != '')
			$this->body .= '
		  	<input type="submit" value="' . $this->buttons ['SUBMIT'] . '" onclick="submit();"/>';

			/*else {
			 $this->body.='
			 <input type="hidden" value="1" name="eQuery_Integrazione_Send_">
			 <input type="submit" value="Salva Modifiche" name="eQuery_Integrazione_Send" onclick="invia_f(false);"/>';
			 }*/

			if ($this->buttons ['INVIA'] && $in ['USER_TIP'] != 'DM' || (isset ( $in ['FORM'] ) || isset ( $in ['SEARCH'] )))
			$this->body .= '
		  <input type="submit" value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/>';
			if ($in ['USER_TIP'] == 'DM' && ! isset ( $in ['FORM'] ) && ! isset ( $in ['SEARCH'] )) {
				$sql = new query ( $conn );
				global $PROGR;

				$query = "select id , to_char(quest_dt,'DD/MM/YYYY') as data from {$this->config_service['service_root']}_equery where visitnum=:visitnum and esam=:esam and progr=:progr and {$this->PK_SERVICE}=:pk_service and validata is null --and to_be_validate=1";
				// echo $query;
				unset($bind);
				$bind['VISITNUM']=$in['VISITNUM'];
				$bind['ESAM']=$in['ESAM'];
				$bind['PROGR']=$PROGR;
				$bind['PK_SERVICE']=$in[$this->PK_SERVICE];
				//$sql->set_sql ( $query );
				$sql->exec ($query,$bind);//binded
				while ( $sql->get_row () ) {
					$equery_option .= "<option value=\"{$sql->row['ID']}\">Equery number {$sql->row['ID']} Equery data {$sql->row['DATA']}</option>";
				}
				if($this->config_service['lang']=="en") {
					$reason="Reason for change:";
					$send="Send";
					$opt1="Documentation of change";
					$opt2="Data entry error";
					$alert_msg="WARNING!!! It\\'s necessary to choose a reason for the revision";
				} else {
					$reason="Motivo della modifica:";
					$send="Procedi";
					$opt1="Documentazione di cambiamento";
					$opt2="Errore inserimento dati";
					$alert_msg="ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica";
				}

				$this->body .= "$reason
		  		<select name='ID_QUERY'>
		  			<option></option>
						<OPTION VALUE=\"-2\">$opt1</option>
						<OPTION VALUE=\"-1\">$opt2</option>
						$equery_option
		  		</select><br/>
		  		<input type=\"submit\" value=\"$send\" name=\"invia_dm\" onclick=\"
		  			if (document.forms[0].ID_QUERY.value!='') invia_f();
		  			else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;}
		  			\"/>
		  	";
		}
		if ($this->buttons ['ANNULLA'])
		$this->body .= '
		  <input type="reset" value="' . $this->buttons ['ANNULLA'] . '" name="annulla" onclick="resetForm();return false;" />';
		if ($this->buttons ['CANCELLA'])
		$this->body .= '
		  <input type="button" value="' . $this->buttons ['CANCELLA'] . '" name="cancella" onclick="resetForm();return false;" />';
		}
		//*****
		//modifica in revisione all'azienda 9/9/10
		if ($this->buttons ['INREVISIONE'] && $in ['USER_TIP'] != 'DM' && !$equery ) {
			$this->body .= '
		  	<br /><input type="submit" value="' . $this->buttons ['INREVISIONE'] . '" name="inrevisione" style="color:red;" onclick="salva_f();document.forms[0].INREV.value=1;"/>';
		}
		//*****
		$this->body .= '</p></table>';
		if(!$exclude_send_buttons) $this->body .= '</form>';
		$config_service=$this->config_service;
		if ($config_service ['PK_SERVICE'] == '')
		$this->PK_SERVICE = 'CODPAT';
		else
		$this->PK_SERVICE = $config_service ['PK_SERVICE'];
		global $vlist;
		if (!isset($in['SEARCH']) && $in [$this->PK_SERVICE] != '' && ! isset ( $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] ) && !$exclude_send_buttons) {
			if($this->document['NO_JS_BACK']=="") $history="onclick=\"history.back(); return false;\"";
			$this->body .= '
		  <p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE].'&VISITNUM='.$in ['VISITNUM'].'" '.$history.'>&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p>';
		}
		$href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";
		$this->body = preg_replace ( "/#HREF#/", $href_alternativo, $this->body );
	}

	/**
	 * Costruisce il codice html della form in visualizzazione
	 *
	 * @param boolean $no_link_back
	 * @param boolean $equery
	 */
	function close_form($no_link_back=false, $equery=false) {
        $testo_rev=null;
		$in=$this->session_vars;
		$inputval=$this->tb_vals;
		$service=$this->service;
		$conn=$this->conn;
		$config_service=$this->config_service;

//		echo "Ruolo ".$this->config_service['eQuerySpec']['Integrazione']['ROLE']."<br>";
//		echo "act ".$this->session_vars['WFact']."<br>";

		$this->percorso_agg="&nbsp;&gt;&nbsp;<b>" . $this->document ['TITOLO'] . "</b>";
		if ($in ['all_exams_view'] != '')
		$percorso = "";
		if ($in ['FORM'] != '')
		$percorso = "";
		global $vlist;
		if ($in ['ESAM'] != 0 && $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] == '')
		$patient_table = patient_table ();
		//		echo "sono qui $equery";
		
		foreach ( $this->fields as $i => $val ) {
//			if ($val ['CONDITION'] != '')
//			$condition_array [count ( $condition_array )] = $val ['CONDITION'];
			if($val ['TYPE']=="file_cme" || $val ['TYPE']=="file_doc") {
				$file_doc_eq['VAR']=$val['VAR'];
				$file_doc_eq['THREAD']=$val['THREAD'];
				$file_doc_eq['TOPIC']=$val['TOPIC'];
				$files_doc[]=$file_doc_eq;
				/*
			        [TYPE] => file_doc
				    [VAR] => COMUNICAZIONI_FILE
				    [THREAD] => Comunicazione
				    [TOPIC] => Communications to AIFA
				 */
			}
		}
		if ($equery){
			$sql_query="select equery_int from {$this->service}_eq where stato = 2 and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";

//			echo $sql_query;
			$sql=new query($this->conn);
			if ($sql->get_row($sql_query)) $equery_int=$sql->row['EQUERY_INT'];
			else $equery_int=0;
			if ($equery_int!='') {

				if(strtolower($this->config_service['lang'])=='en'){
					$string_text="Warning! fields with the symbol <img src=\"images/eq_img.png\" width=20px> has been modified";
				}else{
					$string_text="Attenzione! i campi contrassegnati con il simbolo <img src=\"images/eq_img.png\" width=20px> hanno subito modifiche";
				}
				$note_eq="
				<div style='font-align:center;color:red;font-weight:bold'>
				$string_text
				</div>
				";

			if(isset($_GET['PROGR'])) $progr=$_GET['PROGR'];
			else $progr=1;

			$sql_query="select * from {$this->service}_eqfield where
				eq_int=:eq_id
				and esam=:esam
				and visitnum=:visitnum
				and visitnum_progr=:visitnum_progr
				and progr=:progr
				and {$this->PK_SERVICE}=:pk_service
				";
			unset($bind);
			$bind['EQ_ID']=$equery_int;
			$bind['ESAM']=$_GET['ESAM'];
			$bind['VISITNUM']=$_GET['VISITNUM'];
			$bind['VISITNUM_PROGR']=$_GET['VISITNUM_PROGR'];
			$bind['PROGR']=$progr;
			$bind['PK_SERVICE']=$_GET[$this->PK_SERVICE];
			$sql->exec($sql_query,$bind);//binded
			
			$id_tipo_ref=$config_service['PRJ']*100000+$_GET[$this->PK_SERVICE];
			
			foreach ($this->tb_vals as $k=>$v) $this->old_values[$k]=$v;
			
			while ($sql->get_row()){
				$this->tb_vals[$sql->row['FIELD']]=$sql->row['VALORE'];
			}

			foreach($files_doc as $l=>$allegati) {
					unset($bind_array);
					$topic=preg_replace("/'/", "''", $allegati['TOPIC']);
					if ($topic!='') {
						$topic_where="topic=:topic";
						$bind_array['TOPIC']=$topic;
					}
					else $topic_where="topic is null";
					
					$thread=$allegati['THREAD'];
					$thread=preg_replace("/'/", "''", $thread);
		
					$thread=str_replace("à","%",$thread);
					$thread=str_replace("è","%",$thread);
					$thread=str_replace("ì","%",$thread);
					$thread=str_replace("ò","%",$thread);
					$thread=str_replace("ù","%",$thread);
					$bind_array['TITOLO']=$thread;
					$bind_array['ID_TIPO_REF']=$id_tipo_ref;
					//PENULTIMO!!!
					$sql_query="
				select
				   d.id,
			       d.titolo as titolo,
			       d.autore,
			       d.data,
			       d.keywords as keywords,
			        (select
			            NOME_FILE
			           from docs d1
			        	where d1.tipo_doc='Doc_Area'
			        	and d1.id_tipo_ref=:id_tipo_ref
			        	and d1.id=
			         		(select max(d2.id) from docs d2
			         			where d2.tipo_doc='Doc_Area'
			        and d2.id_tipo_ref=:id_tipo_ref
			        and d2.id_ref=d.id and d2.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref=:id_tipo_ref
			        and d99.id_ref=d.id
			        ))
			        ) as nome_file,
			       (
			        select
			          max(d3.id)
			           from docs d3
			        where d3.tipo_doc='Doc_Area' and d3.id_tipo_ref=:id_tipo_ref and d3.id_ref=d.id and d3.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref=:id_tipo_ref
			        and d99.id_ref=d.id
			        )
			        ) as last_ver
	
			        from docs d
			        where
			        	tipo_doc='Doc_Area'
			        	and id_tipo_ref=:id_tipo_ref
			        	and id=id_ref
			        	and $topic_where
						and d.titolo like :TITOLO
					";
//	   					echo $sql_query." 1612 document";
	   				$sql2=new query($this->conn);
					$sql2->exec($sql_query, $bind_array); //binded
					$sql2->get_row();
						
					foreach($files_doc as $key => $val) {
						if($sql2->row['KEYWORDS']==$val['VAR']) {
							$this->old_values[$val['VAR']]=$sql2->row['LAST_VER'];
							$this->old_values_docs_nomi[$val['VAR']]=$sql2->row['NOME_FILE'];
						}
					}
					
					}
			
			}
		}

		$this->body = '<table border=0 width=100%><tr><td align="center">

		     				 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
		       				 <!-- CAMPI -->' . $testo_rev;
		$colonne = $this->document ['COLS'];
		$width = 100 / ($colonne * 2);
		for($i = 0; $i < $colonne; $i ++)
		$this->body .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
		$this->body .= "</tr>";
		$this->body .= "<tr><td colspan=\"".($colonne * 2)."\" align=\"center\">$note_eq</td>";
		$this->body .= "</tr>";

		$c = 0;
		foreach ( $this->fields as $i => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";

			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$field_obj = new $field_type ( $this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors );
			$field_obj->make_open_html ($equery);
			if ($field_obj->attributes ['TYPE'] != 'hidden' && ($field_obj->attributes ['HIDE'] != 'yes' || $field_obj->condition_passed || $field_obj->attributes ['SHOW_VIS'] == 'yes')) {
				
				//EDO chiamata essenziale per equery è sempre qua il casino
				$field_obj->make_close_html ($equery);
				
				if ($colonne <= $c) {
					$this->body .= "</tr><tr>";
					$c = 0;
				}
				if ($field_obj->attributes ['COLS'] == '')
				$c ++;
				else {
					$c += $field_obj->attributes ['COLS'];
				}
				$this->body .= $field_obj->html;
			}
		}

		$this->body .= "</table>
		  <!--FINE CAMPI-->
		  ";
		$config_service=$this->config_service;
		$this->onload = '';

		if (($in ['all_exams_view'] == '' && $in ['NO_LINK'] == '') && !$no_link_back)
		$this->body .= "<br/><a href=\"javascript:history.back();\">&lt;&lt;{$this->config_service['Torna_lista_schede']}</a>";
		$this->body .= "</p>";
		$href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";
		$this->body = preg_replace ( "/#HREF#/", $href_alternativo, $this->body );
		$this->body = preg_replace ( "/<tr><\/tr>/", "", $this->body );
		$this->body .= "</td></tr></table>";
	}

	/**
	 * Discrimina sulla modalità di visualizzzazione della form e produce il relativo codice html
	 *
	 *  	$xml_form->make_html (	false, => $no_link_back
	 * 								false, => $closed
	 * 								true,  => $force_open : obbliga la visualizzazione della form in compilazione
	 * 								true   => $exclude_send_buttons : i bottoni salva,invia,annulla non vengono inseriti e la form non viene chiusa lasciando
	 * 																  modo di gestirli nella funzione chiamante
	 * 							 );
	 */
	function make_html($no_link_back=false, $closed=false,$force_open=false,$exclude_send_buttons=false) {
		$in = $this->session_vars;
		$inputval = $this->tb_vals;
		$remote_userid = $in ['remote_userid'];
		$sql_query="select fine, userid, visitclose from {$this->config_service['service']}_coordinate where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and esam='{$in['ESAM']}' and progr='{$in['PROGR']}' and visitnum='{$in['VISITNUM']}' and visitnum_progr='{$in['VISITNUM_PROGR']}'";
		$sql=new query($this->conn);
		$sql->get_row($sql_query);
		if ($sql->row['FINE']==1) $this->closed=true;
		if ($sql->row['USERID']==$remote_userid && $sql->row['FINE']!='1' && $sql->row['VISITCLOSE']!='1'  && $in['USER_TIP']!='DM') $in['USER_TIP']='DE';

		if ($closed) {
			$this->closed_document();
			$this->closed=true;
			$this->close_document(true);
			return;
		}
		if ($force_open) {
			$this->closed_document();
			$this->closed=false;
			$this->open_document($force_open,$exclude_send_buttons);
			return;
		}
		if ($in ['USER_TIP'] == 'DE') {
			if (! $this->closed_document ()){
				$this->open_document ();
			}
			else
			{
				$this->close_document ($no_link_back);
			}
		}
		if ($in ['USER_TIP'] == 'DM') {
			if (! $this->closed_document ()){

				$this->close_document ($no_link_back);
			}
			else
			$this->open_document ();
		}
		if ($in ['USER_TIP'] == 'RO') {
			$this->closed_document ();
			$this->close_document ($no_link_back);
		}

	}

	function Save($stato, $ajax=false){

	}

	function getErrors(){
		return $this->errors;
	}

	

	

	
}

/**
 * Classe prototipo della form legato all'XMR
 *
 * @package FileAllegati
 */
class xml_document_prototype extends document_prototype {

	var $sql_query_coordinate;
	var $progr;
	var $equery_table;
	var $equery_coordinate;

	/**
	 * Recupera le informazioni sui tessti configurabili
	 *
	 * @param String $testo
	 * @return String
	 */
	function testo($testo){
		//HOW TO
		/* Per utilizzare questa funzione chiamarla cosi nel codice:
		* $this->testo("PAROLACHIAVE")
		* e qui dentro definire per ogni lingua
		* $this->testi['PAROLACHIAVE']="Frase da far apparire";
		*/
		if(!isset($this->testi[$testo])){
			if(strtolower($this->config_service['lang'])=='en'){
				$this->testi['visitIsClosed']="Attention this visit is closed, it's not possible to modify/insert data";
			} else{
				$this->testi['visitIsClosed']="Attenzione la visita risulta chiusa, non &egrave; quindi possibile inserire/modificare i dati";
			}

		}
		return $this->testi[$testo];
	}


	/**
	 * Controlla se la document è chiusa e recupera i dati da DB
	 *
	 */
	function closed_document($progr=null) {
		$ret=parent::closed_document($progr);
		global $inputval;
		$inputval=$this->tb_vals;
		return $ret;
	}

	/**
	 * Costruisce il codice html della document in compilazione
	 *
	 */
	function open_document($force_open=false,$exclude_send_buttons, $equery=false) {
		parent::open_document($force_open,$exclude_send_buttons, $equery);
		global $percorso;
		$percorso.=$this->percorso_agg;
	}


	/**
	 * Costruisce il codice html della document in visualizzazione
	 *
	 */
	function close_document($no_link_back=false, $equery=false) {
		parent::close_document($no_link_back,$equery);
		global $percorso;
		$percorso.=$this->percorso_agg;
	}


	/**
	 *
	 * Costruttore
	 *
	 *
	 *
	 */
	function xml_document_prototype($conn=null, $service=null, $config_service=null, $in=null, $dir_file=null) {
		if (!isset($config_service)) global $config_service;
		if (!isset($service)) global $service;
		if (!isset($in)) global $in;
		if (!isset($dir_file)) {
			global $dir;
			$dir_file = $dir . "/uploaded_file/";
		}
		if (!isset($conn)) global $conn;
		parent::document_prototype ( $conn, $service, $config_service, $in, $dir_file );
	}

	function query_tb($new_insert) {
		//mi porto dietro il valore assegnato al nuovo paziente (codpat o simili)
		$pk_serv_val = parent::query_tb ( $new_insert );
		global $in;
		$in = $this->session_vars;

		//G.Tufano 22/07/2010
		//aggiungo questo per poter leggere il valore della sequence
		return $pk_serv_val;
		
	}

	/**
	 * Costruisce le query di abilitazione delle schede
	 *
	 *
	 */
	function query_abilita() {
	
	}

	function XML_PRINT_($values) {
        $out=null;
        $key=null;
		foreach ( $this->fields as $i => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";

			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "{$field_type}.inc";
			$field_obj = new $field_type ( $this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
			$out .= $field_obj->XML_PRINT_ ( $values );
		}
		return $out;
	}

}





?>
