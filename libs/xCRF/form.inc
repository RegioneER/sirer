<?
//Prova di commit 
///MERGED

/**
 * Classe prototipo per la gestione della form
 *
 * @package ViewsAndControllers
 */
class form_prototype
{

    var $form;
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
    var $no_field_value_by_tb = false;
    var $insert_stmt;
    var $insert_stmt_pk;
    var $old_values;
    var $equery;
    var $stato_eq;
    var $prefix;
    var $old_values_docs_nomi;
    var $header;
    var $footer;

    /**
     * Costruttore
     *
     * @param dbconn $conn
     * @param String $service
     * @param array $config_service
     * @param array $session_vars
     * @param String $uploaded_files_dir
     * @param boolean $xmr
     * @return form_prototype
     */
    function form_prototype($conn, $service, $config_service, $session_vars, $uploaded_files_dir, $xmr = true)
    {
        $this->config_service = $config_service;
        $this->session_vars = $session_vars;
        $this->uploaded_files_dir = $uploaded_files_dir;
        $this->service = $service;
        $this->conn = $conn;
        $this->prefix = $service;
        $this->xmr = $xmr;
        $this->stato_eq = "";
        if (isset ($config_service ['PK_SERVICE']) && $config_service ['PK_SERVICE'] != '')
            $this->PK_SERVICE = $config_service ['PK_SERVICE'];
        else
            $this->PK_SERVICE = $this->config_service['PK_SERVICE'];
    }

    /**
     * Costruisce la form a partire dall'oggetto XML
     *
     * @param array $xml
     */
    function xml_form_by_obj($xml)
    {
        $this->xml_form_by_vals($xml->vals);
    }

    /**
     * Costruisce la form a partire dal file xml
     *
     * @param String $xml_file
     */
    function xml_form_by_file($xml_file)
    {
        $this->filename = str_replace("\.xml", "", basename($xml_file));
        $xml = new my_xml_parser ($xml_file);
        $this->xml_form_by_obj($xml);

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
     * Costruisce la form a partire dall'array vals
     *
     * @param array $vals
     */
    function xml_form_by_vals($vals)
    {
        $in = $this->session_vars;
        $fn = 0;
        $en = 0;
        $newtag = true;
        $this_node = new xml_node ();
        /*INIZIO - GENHD-42 gestione rangechecks per cro vmazzeo 20.02.2015*/
        $rangeCheck = array();
        $rangeCheckCount = 0;
        /*FINE - GENHD-42 gestione rangechecks per cro vmazzeo 20.02.2015*/
        $fileName = str_replace("\.xml", "", $this->filename);
        $fileName = preg_replace("!\.xml!", "", $fileName);
        for ($i = 0; $i < count($vals); $i++) {
            $this_node->xml_node_by_array($vals [$i]);
            if ($this_node->type != 'cdata') {
                if ($this_node->tag == 'FORM')
                    if ($this_node->type == 'open' or $this_node->type == 'complete')
                        $this->form = $this_node->attributes;
                if ($this_node->tag == 'FIELD') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->fields [$fn] = $this_node->attributes;
                        $this->vars [$this_node->attributes ['VAR']] = $fn;
                    }
                    if ($this_node->type != 'open') {
                        $fn++;
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
                if ($this_node->tag == 'HEADER')
                    $this->header = $this_node->value;
                if ($this_node->tag == 'FOOTER')
                    $this->footer = $this_node->value;
                if ($this_node->tag == 'CANCEL')
                    $this->buttons ['ANNULLA'] = $this_node->value;
                if ($this_node->tag == 'DELETE_ALL')
                    $this->buttons ['CANCELLA'] = $this_node->value;
                if ($this_node->tag == 'EXAM') {
                    $this->enable [$en] = $this_node->attributes;
                    $en++;
                }
                if ($this_node->tag == 'TXT_VALUE') {
                    if ($this_node->attributes['LANG'] == '') $this->fields [$fn] ['TESTO'] = $this_node->value;
                    else {
                        $this->fields [$fn] ['TESTO_PLUS'][$this_node->attributes['LANG']] = $this_node->value;
                    }
                }
                /*INIZIO - GENHD-42 gestione rangechecks per cro vmazzeo 20.02.2015*/
                if ($this_node->tag == 'RANGECHECK') {
                    if ($this_node->type == 'open') {
                        $rangeCheck = array();
                        $rangeCheckCount = 0;
                        $rangeCheck['COMPARATOR'] = $this_node->attributes['COMPARATOR'];
                        $rangeCheck['LEVEL'] = $this_node->attributes['LEVEL'];
                    }
                    if ($this_node->type == 'close' && !empty($rangeCheck)) {
                        $this->fields[$fn]['RANGECHECK'][] = $rangeCheck;
                        $rangeCheckCount++;
                        mlOut($fileName . '.' . $this->fields [$fn]['VAR'] . '.RANGECHECK_' . $rangeCheckCount, $rangeCheck['MESSAGE']);
                    }
                }
                if ($this_node->tag == 'CHECKVALUE') {
                    if ($this_node->type == 'complete') {
                        $rangeCheck['CHECKVALUE'] = $this_node->value;

                    }
                }
                if ($this_node->tag == 'MESSAGE') {
                    if ($this_node->type == 'complete') {
                        $rangeCheck['MESSAGE'] = $this_node->value;

                    }
                }
                /*FINE - GENHD-42 gestione rangechecks per cro vmazzeo 20.02.2015*/

                if ($this_node->tag == 'VALUE') {
                    $fileName = str_replace("\.xml", "", $this->filename);
                    $fileName = preg_replace("!\.xml!", "", $fileName);
                    //Logger::send($vals);
                    //Logger::send($fileName . '.' . $this->fields [$fn]['VAR'] . '.' . $this_node->attributes ['VAL']);
                    $this->fields [$fn] ['VALUE'] [$this_node->attributes ['VAL']] = mlOut($fileName . '.' . $this->fields [$fn]['VAR'] . '.' . $this_node->attributes ['VAL'], $this_node->value);
                    if (isset($this_node->attributes['GROUP']) && $this_node->attributes['GROUP'] != '') $this->fields [$fn] ['VALUE_GROUP'] [$this_node->attributes ['VAL']] = $this_node->attributes['GROUP'];
                    $this->fields [$fn] ['VALUE_TXT'] [$this_node->attributes ['VAL']] = $this_node->attributes ['TXT'];
                    if ($this_node->attributes['DECODE'] != '') $this->fields [$fn] ['DECODE'] [$this_node->attributes ['VAL']] = $this_node->attributes['DECODE'];
                    if (isset($this_node->attributes['CONDITION']) && $this_node->attributes['CONDITION'] != '')
                        $this->fields [$fn] ['VALUE_CONDITION'] [$this_node->attributes ['VAL']] = $this_node->attributes['CONDITION'];
                    if (isset($this_node->attributes['CONDITION_VALUE']) && $this_node->attributes['CONDITION_VALUE'] != '')
                        $this->fields [$fn] ['VALUE_CONDITION_VALUE'] [$this_node->attributes ['VAL']] = $this_node->attributes['CONDITION_VALUE'];
                    if (isset($this_node->attributes['CONDS']) && $this_node->attributes['CONDS'] != '')
                        $this->fields [$fn] ['VALUE_CONDS'] [$this_node->attributes ['VAL']] = $this_node->attributes['CONDS'];
                    if (isset($this_node->attributes['DOCS']) && $this_node->attributes['DOCS'] != '')
                        $this->fields [$fn] ['VALUE_DOCS'] [$this_node->attributes ['VAL']] = $this_node->attributes['DOCS'];
                }

//				if($this->config_service['multilang']=="1"){
//
//					print_R($this->fields [$fn]['VAR']);
//				}
            }
        }
        if (!isset($this->form['COLS'])) {
            $this->form['COLS'] = 1;
        }
        $this->form ['TABLE'] = strtoupper($this->service) . "_" . $this->form ['TABLE'];
    }

    /**
     * Restituisce la primary key
     *
     * @return array
     */
    function pk_key()
    {
        $c = 0;
        for ($i = 0; $i < count($this->fields); $i++) {
            if ($this->fields [$i] ['PK'] == 'yes') {
                $pk_key [$c] = $this->fields [$i] ['VAR'];
                $c++;
            }
        }
        return $pk_key;
    }

    /**
     * Costruisce le clausole di where sulla pk
     *
     * @return String
     */
    function pk_where($binded = false)
    {
        $where = null;
        $in = $this->session_vars;
        $pk_key = $this->pk_key();
        for ($i = 0; $i < count($pk_key); $i++) {
            if ($in [$pk_key [$i]] != 'next') {
                if ($where != '')
                    $where .= ' and ';
                if (!$binded) $where .= $pk_key [$i] . "='" . $in [$pk_key [$i]] . "'";
                else $where .= $pk_key [$i] . "=:" . $pk_key [$i];
                $bind[$pk_key [$i]] = $in [$pk_key [$i]];
            }
        }
        $return['WHERE'] = $where;
        $return['BIND'] = $bind;


        if (!$binded) return $return['WHERE'];
        else return $return;
    }

    /**
     * Costruisce la query di inserimento/update
     *
     * @param boolean $force_insert
     */
    function query_builder($force_insert = false)
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        global $_FILES;
        $dir_file = $this->uploaded_files_dir;
        foreach ($in as $key => $value)
            $in [$key] = preg_replace("/'/", "''", $value);
        $sql = new query ($conn);
        $this->progr = $in ['PROGR'];
        if ($this->xmr) {
            unset($bind);
            if ($in [$this->PK_SERVICE] == 'next')
                $this->progr = 1;
            else {
                $config_service = $this->config_service;
                $where_agg = '';
                if (isset ($config_service ['VISITNUM_PROGR'])) {
                    $where_agg = " and visitnum_progr=:visitnum_progr";
                    $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                }
                $query = "select max(visitclose) as visitclose from " . $this->service . "_coordinate where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum $where_agg";
                //$sql->set_sql (  );
                $bind['PK_SERVICE'] = $in [$this->PK_SERVICE];
                $bind['VISITNUM'] = $in ['VISITNUM'];
                $sql->exec($query, $bind);//binded
                $sql->get_row();

                if ($sql->row ['VISITCLOSE'] == 1 && $in ['USER_TIP'] == 'DE' && !$force_insert && $in['ajax_call'] == '') {

                    if (function_exists('testo')) error_page($in ['remote_userid'], mlOut("System.form.visit_closed", testo("visitIsClosed")), "");
                    else if (method_exists($this, 'testo')) error_page($in ['remote_userid'], mlOut("System.form.visit_closed", $this->testo("visitIsClosed")), "");
                    else error_page($in ['remote_userid'], "Visit closed", "");
                }


                if ($this->progr == 'next' || $this->progr == '') {

                    $query = "select max(progr) as max from " . $this->service . "_coordinate where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam $where_agg";

                    $bind['PK_SERVICE'] = $in [$this->PK_SERVICE];
                    $bind['VISITNUM'] = $in ['VISITNUM'];
                    $bind['ESAM'] = $in ['ESAM'];

                    //$sql->set_sql ( $query );
                    $sql->exec($query, $bind);//binded
                    $sql->get_row();
                    if ($sql->row ['MAX'] != '')
                        $this->progr = '1';
                    else
                        $this->progr = $sql->row ['MAX'] + 1;
                    $in ['PROGR'] = $this->progr;

                }

            }
        }
        $pk_key = $this->pk_key();
        for ($i = 0; $i < count($pk_key); $i++) {
            if ($in [$pk_key [$i]] == 'next' || $in [$pk_key [$i]] == 'progr')
                $new_insert = true;
        }

        if (!isset ($new_insert)) {
            $binded_where = $this->pk_where(true);
            $where = $binded_where['WHERE'];
            $bind = $binded_where['BIND'];
            if ($where != '')
                $where = "where " . $where;
            $query = "select count(*) as c from " . $this->form ['TABLE'] . " $where";
            //$sql->set_sql ( $query );
            $sql->exec($query, $bind);//binded
            $sql->get_row();
            if ($sql->row ['C'] != '1')
                $new_insert = true;
            else
                $new_insert = false;
        }

        //G.Tufano 22/07/2010
        //la funzione mi restituisce il CODPAT (o altro PK_SERVICE) che pu essere impostato
        //con AUTOINCREMENT (per es se CODPAT = 'next').
        //viene usato nel metodo "invia_form($xml_form, $in_s)" in estensioni di
        //study.prototype
        $pk_service_value = $this->query_tb($new_insert);

        if ($this->xmr)
            $this->query_abilita();

        return $pk_service_value;
    }

    /**
     * Costruisce il codice SQL dell'inserimento nella tabella
     *
     * @param boolean $new_insert
     */
    function query_tb($new_insert)
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        $dir_file = $this->uploaded_files_dir;
        $sql = new query ($conn);
        $i = 0;

        foreach ($this->fields as $key => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";
            if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                include_once $this->config_service['field_lib'] . $field_type . ".inc";
            } else {
                include_once realpath(dirname(__FILE__) . "{$field_type}.inc");
            }
            $field_obj = new $field_type ($this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            if ($field_obj->attributes ['PK'] == 'yes')
                $pk [$field_obj->attributes ['VAR']] = $in [$field_obj->attributes ['VAR']];
            if ($new_insert) {
                $field_obj->insert_stmt(true);
                if (!$field_obj->value_stmt) {
                    $field_obj->value_stmt = array();
                }
                foreach ($field_obj->value_stmt as $key_f => $val_f) {
                    if ($field_obj->value_stmt [$key_f] == "next") {
                        if ($field_obj->id == $this->config_service['PK_SERVICE'] && $this->config_service['PK_SEQ'] != '' && !isset($this->session_vars['ajax_call'])) {
                            $sql_query = "select {$this->config_service['PK_SEQ']}.nextval as PK_ID from dual";
                            $sql = new query($this->conn);
                            $sql->set_sql($sql_query);
                            $sql->exec();//non richiede binding
                            $sql->get_row();
                            $pk_id = $sql->row['PK_ID'];
                            $this->pk_value = $pk_id;
                            $in [$field_obj->attributes ['VAR']] = $pk_id;
                            $this->session_vars[$field_obj->attributes ['VAR']] = $pk_id;
                            $in_s = $in;
                            global $in;
                            $in = $in_s;
                            $field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
                            $field_obj->value_stmt [$key_f] = $pk_id;
                        } else {
                            if ($field_obj->attributes ['WHERE'] != '')
                                $where = "where " . $field_obj->attributes ['WHERE'];
                            $where = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $where);
                            $query = "select max(" . $field_obj->attributes ['VAR'] . ") as max from " . $this->form ['TABLE'] . " $where";
                            $sql = new query ($conn);
                            $sql->set_sql($query);
                            $sql->exec();//complessa come list var_glob. Carlo
                            $sql->get_row();
                            $in [$field_obj->attributes ['VAR']] = $sql->row ['MAX'] + 1;
                            $this->pk_value = $sql->row ['MAX'] + 1;
                            $field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
                        }
                    }
                    $values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
                }
            } else {
                $field_obj->insert_stmt();
                if ($field_obj->value_stmt) {
                    foreach ($field_obj->value_stmt as $key_f => $val_f) {
                        $values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
                    }
                }
            }

            if ($val ['TYPE'] == 'ckeditor') {
                unset($values[$val['VAR']]);
                foreach ($field_obj->value_stmt as $key_f => $val_f) {
                    if ($key_f == $val['VAR'])
                        $clob[$val['VAR']] = $val_f;
                }
            }
            if (!isset($this->session_vars['ajax_call']) && class_exists('SDV_module')) {
                //Lancio l'inserimento SDV solamente a seguito di dati correttamente inviati (non chiamata ajax, poichè potrei non avere codpat etc...)
                $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], null, null);
                $sdv->after_query_tb_foreach($this, $field_obj);
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
                    $sql = new query ($conn);
                    unset($bind);
                    $bind['PK_SERVICE'] = $in [$this->PK_SERVICE];
                    $bind['VISITNUM'] = $in ['VISITNUM'];
                    $bind['ESAM'] = $in ['ESAM'];
                    $bind['PROGR'] = $this->progr;
                    $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                    //$sql->set_sql ( $sql_query );
                    $sql->exec($sql_query, $bind);//binded
                    $sql->get_row();
                    $count = $sql->row ['C'];
                    if ($count > 0) {
                        $sql = new query($conn);
                        $sql_first_insert = "select insertdt from " . $this->service . "_coordinate where {$this->PK_SERVICE}=:pk_service and esam=:esam and visitnum=:visitnum and progr=:progr and VISITNUM_PROGR=:visitnum_progr";
                        unset($bind);
                        $bind['PK_SERVICE'] = $in [$this->PK_SERVICE];
                        $bind['ESAM'] = $in ['ESAM'];
                        $bind['VISITNUM'] = $in ['VISITNUM'];
                        $bind['VISITNUM_PROGR'] = $in ['VISITNUM_PROGR'];
                        $bind['PROGR'] = $this->progr;
                        //$sql->set_sql ( $sql_first_insert );
                        $sql->exec($sql_first_insert, $bind);//binded
                        $sql->get_row();
                        if ($sql->row['INSERTDT'] == '') $this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate,insertdt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "' and VISITNUM_PROGR='{$in['VISITNUM_PROGR']}'";
                        else $this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "' and VISITNUM_PROGR='{$in['VISITNUM_PROGR']}'";
                    } else
                        $this->sql_query_coordinate = "
					insert into " . $this->service . "_coordinate
					({$this->PK_SERVICE}, visitnum, esam, progr, inizio, fine, insertdt,moddt, userid, abilitato, visitclose,VISITNUM_PROGR)
					values (" . $in [$this->PK_SERVICE] . ",'" . $in ['VISITNUM'] . "','" . $in ['ESAM'] . "','" . $this->progr . "','1','" . $in ['INVIOCO'] . "',sysdate,sysdate,'" . $in ['remote_userid'] . "','1',$visitclose, {$in['VISITNUM_PROGR']})";
                } else {

                    $sql_query = "
					select count(*) as c from " . $this->service . "_coordinate
						where {$this->PK_SERVICE}=:pk_service
						and visitnum=:visitnum
						and esam=:esam
						and progr=:progr
						  ";
                    $sql = new query ($conn);
                    unset($bind);
                    $bind['PK_SERVICE'] = $in [$this->PK_SERVICE];
                    $bind['VISITNUM'] = $in ['VISITNUM'];
                    $bind['ESAM'] = $in ['ESAM'];
                    $bind['PROGR'] = $in ['PROGR'];
                    //$sql->set_sql ( $sql_query );
                    $sql->exec($sql_query, $bind); //binded
                    $sql->get_row();
                    $count = $sql->row ['C'];
                    if ($count > 0)
                        $this->sql_query_coordinate = "update " . $this->service . "_coordinate set visitclose=$visitclose, moddt=sysdate, fine='" . $in ['INVIOCO'] . "', inizio='1' where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' and esam='" . $in ['ESAM'] . "' and visitnum='" . $in ['VISITNUM'] . "' and progr='" . $this->progr . "'";
                    else
                        $this->sql_query_coordinate = "insert into " . $this->service . "_coordinate ({$this->PK_SERVICE}, visitnum, esam, progr, inizio, fine, insertdt,moddt, userid, abilitato, visitclose) values (" . $in [$this->PK_SERVICE] . ",'" . $in ['VISITNUM'] . "','" . $in ['ESAM'] . "','" . $this->progr . "','1','" . $in ['INVIOCO'] . "',sysdate,sysdate,'" . $in ['remote_userid'] . "','1',$visitclose)";
                }
            } else {
                $bindVars = "";
                if (isset ($config_service ['VISITNUM_PROGR']) && $config_service ['VISITNUM_PROGR'] == 1) {
                    $this->sql_query_coordinate = "
					update " . $this->service . "_coordinate set 
						visitclose=$visitclose, 
						moddt=sysdate, 
						fine='" . $in ['INVIOCO'] . "', 
						inizio='1' 
					where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' 
					and esam='" . $in ['ESAM'] . "' 
					and visitnum='" . $in ['VISITNUM'] . "' 
					and progr='" . $this->progr . "' 
					and VISITNUM_PROGR='{$in['VISITNUM_PROGR']}'";
                    $this->sql_query_coordinate = "
					update " . $this->service . "_coordinate set 
						visitclose=:visitclose, 
						moddt=sysdate, 
						fine=:fine, 
						inizio='1' 
					where {$this->PK_SERVICE}=:pk_service 
					and esam=:esam 
					and visitnum=:visitnum 
					and progr=:progr 
					and VISITNUM_PROGR=:visitnum_progr"; //binded
                    $bindVars['visitclose'] = $visitclose;
                    $bindVars['pk_service'] = $in [$this->PK_SERVICE];
                    $bindVars['fine'] = $in ['INVIOCO'];
                    $bindVars['esam'] = $in ['ESAM'];
                    $bindVars['visitnum'] = $in ['VISITNUM'];
                    $bindVars['progr'] = $this->progr;
                    $bindVars['visitnum_progr'] = $in['VISITNUM_PROGR'];
                } else {
                    $this->sql_query_coordinate = "
					update " . $this->service . "_coordinate set 
						visitclose=$visitclose, 
						moddt=sysdate, 
						fine='" . $in ['INVIOCO'] . "', 
						inizio='1' 
					where {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "' 
					and esam='" . $in ['ESAM'] . "' 
					and visitnum='" . $in ['VISITNUM'] . "' 
					and progr='" . $this->progr . "'";
                    $this->sql_query_coordinate = "
					update " . $this->service . "_coordinate set 
						visitclose=:visitclose, 
						moddt=sysdate, 
						fine=:fine, 
						inizio='1' 
					where {$this->PK_SERVICE}=:pk_service 
					and esam=:esam 
					and visitnum=:visitnum 
					and progr=:progr"; //binded
                    $bindVars['visitclose'] = $visitclose;
                    $bindVars['pk_service'] = $in [$this->PK_SERVICE];
                    $bindVars['fine'] = $in ['INVIOCO'];
                    $bindVars['esam'] = $in ['ESAM'];
                    $bindVars['visitnum'] = $in ['VISITNUM'];
                    $bindVars['progr'] = $this->progr;
                }
            }

            $sql = new query ($conn);
            $sql->ins_upd($this->sql_query_coordinate, $bindVars); //binded
        }

        /*		Inserimento in storico		*/
        $where = $this->pk_where();
        if (!$new_insert && !isset ($in ['ID_QUERY'])) {
            $this->sql_query_storico = "
			insert into S_" . $this->form ['TABLE'] . " 
				select 
					'" . $in ['remote_userid'] . "', 
					sysdate, 
					storico_id.nextval, 
					'V', 
					'',  
					" . $this->form ['TABLE'] . ".* 
				from " . $this->form ['TABLE'] . " where $where";
            $this->sql_query_storico = "
			insert into S_" . $this->form ['TABLE'] . " 
				select 
					:remote_userid, 
					sysdate, 
					storico_id.nextval, 
					'V', 
					'',  
					" . $this->form ['TABLE'] . ".* 
				from " . $this->form ['TABLE'] . " where $where"; //binded
            $bindVars1 = "";
            $bindVars1["remote_userid"] = $in ['remote_userid'];

        }
        if (!$new_insert && isset ($in ['ID_QUERY'])) {
            $this->sql_query_storico = "
			insert into S_" . $this->form ['TABLE'] . " 
				select '" . $in ['remote_userid'] . "', 
				sysdate, storico_id.nextval, 'E', 
				'" . $in ['ID_QUERY'] . "',  " . $this->form ['TABLE'] . ".* 
				from " . $this->form ['TABLE'] . " where $where";
            $this->sql_query_storico = "
			insert into S_" . $this->form ['TABLE'] . " 
				select :remote_userid, 
				sysdate, storico_id.nextval, 'E', 
				:id_query,  " . $this->form ['TABLE'] . ".* 
				from " . $this->form ['TABLE'] . " where $where"; //binded
            $bindVars1 = "";
            $bindVars1["remote_userid"] = $in ['remote_userid'];
            $bindVars1["id_query"] = $in ['ID_QUERY'];
        }
        if ($this->sql_query_storico != '') {
            $sql = new query ($conn);
            $sql->ins_upd($this->sql_query_storico, $bindVars1); //binded
        }

        $values['PROGR'] = $this->progr;
        /*  	Inserimento nella tabella 	*/
        //Edo: qua metto gli array dei clob?
        //		print_r($clob);
        if ($new_insert) {
            $result = $sql->insert($values, $this->form ['TABLE'], $pk, true, null, $clob);
        } else {
            $result = $sql->update($values, $this->form ['TABLE'], $pk, $clob);
        }
        $this->session_vars = $in;
        $this->errors = $sql->getErrors();

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
    function insert_stmt_prepare($new_insert = false)
    {
        $in = null; //TODO: probabile errore!!!
        $conn = $this->conn;
        foreach ($this->fields as $key => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";

            if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                include_once $this->config_service['field_lib'] . $field_type . ".inc";
            } else
                include_once "{$field_type}.inc";
            $field_obj = new $field_type ($this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);

            if ($field_obj->attributes ['PK'] == 'yes')
                $pk [$field_obj->attributes ['VAR']] = $in [$field_obj->attributes ['VAR']];
            if ($new_insert) {
                //non deve capitare
                $field_obj->insert_stmt(true);
                foreach ($field_obj->value_stmt as $key_f => $val_f) {
                    if ($field_obj->value_stmt [$key_f] == "next") {
                        if ($field_obj->id == $this->config_service['PK_SERVICE'] && $this->config_service['PK_SEQ'] != '' && !isset($this->session_vars['ajax_call'])) {
                            $sql_query = "select {$this->config_service['PK_SEQ']}.nextval as PK_ID from dual";
                            $sql = new query($this->conn);
                            $sql->set_sql($sql_query);
                            $sql->exec();//non richiede binding
                            $sql->get_row();
                            $pk_id = $sql->row['PK_ID'];
                            $this->pk_value = $pk_id;
                            $in [$field_obj->attributes ['VAR']] = $pk_id;
                            $this->session_vars[$field_obj->attributes ['VAR']] = $pk_id;
                            $in_s = $in;
                            global $in;
                            $in = $in_s;
                            $field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
                            $field_obj->value_stmt [$key_f] = $pk_id;
                        } else {
                            if ($field_obj->attributes ['WHERE'] != '')
                                $where = "where " . $field_obj->attributes ['WHERE'];
                            $where = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $where);
                            $query = "select max(" . $field_obj->attributes ['VAR'] . ") as max from " . $this->form ['TABLE'] . " $where";
                            $sql = new query ($conn);
                            $sql->set_sql($query);
                            $sql->exec();//complessa da gestire con carlo
                            $sql->get_row();
                            $in [$field_obj->attributes ['VAR']] = $sql->row ['MAX'] + 1;
                            $this->pk_value = $sql->row ['MAX'] + 1;
                            $field_obj->value_stmt [$key_f] = $in [$field_obj->attributes ['VAR']];
                        }
                    }
                    $values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
                }
            } else {
                $field_obj->insert_stmt();
                foreach ($field_obj->value_stmt as $key_f => $val_f)
                    $values [$field_obj->field_stmt [$key_f]] = $field_obj->value_stmt [$key_f];
            }
        }
        $this->insert_stmt = $values;
        $this->insert_stmt_pk = $pk;

    }

    /**
     * Individua le differenze
     *
     * @return arrray
     */
    function differences()
    {
        $this->closed_form();
        $this->insert_stmt_prepare();
        $differences_idx = 0;
        foreach ($this->insert_stmt as $key => $value) {
            if (trim($this->tb_vals[$key]) != trim($value)) {
                $differences[$differences_idx]['FIELD'] = $this->fields[$this->vars[$key]]['TESTO'];
                $differences[$differences_idx]['VAR'] = $key;
                $differences[$differences_idx]['NOMETAB'] = $this->form ['TABLE'];
                $differences[$differences_idx]['VAL_OLD'] = $this->tb_vals[$key];
                $differences[$differences_idx]['VAL_NEW'] = $value;
                $differences_idx++;
            }
        }
        return $differences;
    }

    /**
     * Controlla le condizioni di obbligatoriet della form
     *
     * @return boolean
     */
    function valida()
    {
        $this->validata = true;
        if (isset($this->config_service['eQuery']) && $this->config_service['eQuery'] == 1) {
            $this->integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);
            if ($this->integrazione->eq_int != '' && $this->integrazione->role == $this->integrazione->profilo) {
                $sql_query_int = "select FIELD,VALORE from {$this->service}_EQFIELD where 
					ESAM=:esam
					and VISITNUM=:visitnum
					and VISITNUM_PROGR=:visitnum_progr
					and PROGR=:progr
					and {$this->config_service['PK_SERVICE']}=:pk_service
					and eq_int=:eq_int
				";
                $bind['esam'] = $this->session_vars['ESAM'];
                $bind['visitnum'] = $this->session_vars['VISITNUM'];
                $bind['visitnum_progr'] = $this->session_vars['VISITNUM_PROGR'];
                $bind['progr'] = $this->session_vars['PROGR'];
                $bind['pk_service'] = $this->session_vars[$this->config_service['PK_SERVICE']];
                $bind['eq_int'] = $this->integrazione->eq_int;
                $sql = new query($this->conn);
                $sql->exec($sql_query_int, $bind);
                while ($sql->get_row()) {
                    $this->session_vars[$sql->row['FIELD']] = $sql->row['VALORE'];
                }
            }
        }
        for ($i = 0; $i < count($this->fields); $i++) {
            if (isset ($this->fields [$i] ['TYPE']) && $this->fields [$i] ['TYPE'] != '')
                $field_type = "field_{$this->fields[$i]['TYPE']}";
            else
                $field_type = "field";

            if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                include_once $this->config_service['field_lib'] . $field_type . ".inc";
            } else
                include_once "{$field_type}.inc";

            $field_obj = new $field_type ($this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            $field_obj->make_open_html();

            if (!$field_obj->validata) {
                //Logger::send("La scheda incompleta : (id)". $field_obj->id);
                $this->errors[$field_obj->id] = $field_obj->errors[$field_obj->id];
                $this->validata = $field_obj->validata;
            }


        }

        if ($this->validata) {
            //Controllo sintassi edit check grammatica nostra (server-side)
            $paths = array(
                realpath($_SERVER['DOCUMENT_ROOT'] . "/../libs"),
                '.',
            );
            set_include_path(implode(PATH_SEPARATOR, $paths));
            include_once 'pest/Pest.php';
            include_once 'pest/PestJSON.php';
            //require_once '../pest/PestXML.php';
            //Istanzia oggetto con umarshalling JSON e lancia la chiamata.
            //TODO: Modificare indirizzo WS per deploy sulle macchine
            $address = "http://localhost:8080"; //"http://appserv-siss.dev.cineca.it";
            $pest = new PestJSON($address);

            $tocheck = '$result="true";'; //TODO: Sintassi all'interno della form
            //Sostituisci valori variabili all'interno della sintassi della form

            //{ "studyPrefix":"VNC", "pkServiceKey":"CODPAT", "pkValue": "141", "check": "[SYNTAX_TO_CHECK]" }
            $data = array(
                "studyPrefix" => $this->service, //Prefisso servizio
                "pkServiceKey" => $this->config_service['PK_SERVICE'],
                "pkValue" => $this->session_vars[$this->config_service['PK_SERVICE']],
                "check" => $tocheck
            );
            $connectId = "sisa"; //TODO: Parametrizzare
            $magic = "abcd"; //TODO: Parametrizzare
            $hash = "9ba33147cb5b1de49c6f3b2abb21d25abd28ce1d208df0458d08b574a14c6a04"; //"abcdefg"; //DigestUtils.sha256Hex(msg + magic)
            //TODO: SCOMMENTARE IF X ATTIVARE CONTROLLO!
            //$result = $pest->post("/GeniusAPI/api/{$connectId}/{$hash}/checkform", $data);
            //print_r($result);
            //TODO: SCOMMENTARE IF X ATTIVARE CONTROLLO!
            //if ($result['checkReturnValue']!="true"){
            //    $this->validata = false;
            //    return false;
            //}


            //die("\n<br/>DONE CHECK.");
            //$address = "http://127.0.0.1:8080";
            //$pest = new Pest($address);
            //$data = array(
            //    "i" => 123,
            //    "str" => "Bob",
            //    "arr" => array("a", "b", "c"),
            //    "map" => array(
            //        "a" => 1,
            //        "b" => 2,
            //        "c" => 3
            //    )
            //);
            //
            //$headers = array(
            //    "abc" => "123"
            //);
            //
            //$result = $pest->post("/my/rest/uri", $data, $headers);
            //Parso il risultato (array con result e value)
            //su value mi aspetto il mio valore di ritorno e imposto $this->validata
            //FINE Edit-check grammatica

            return true;
        } else {
            return false;
        }
    }

    /**
     * Allinea la struttura della tabella alla form
     *
     * @return boolean
     */
    function allinea_db()
    {
        $sql_pk_fields = null;
        $sql_create_fields = null;
        $sql_create_fields_storico = null;
        $in = $this->session_vars;
        $conn = $this->conn;
        $service = $this->service;
        $tb_exist = false;
        $str_synonym = "select * from USER_SYNONYMS where synonym_name='" . $this->form ['TABLE'] . "'";
        $sql = new query ($conn);
        $sql->set_sql($str_synonym);
        $sql->exec();//non richiede binding
        $sql->get_row();
        if ($sql->row['TABLE_NAME'] != '') $this->form ['TABLE'] = $sql->row['TABLE_NAME'];
        $query = "select column_name from all_col_comments where table_name='" . $this->form ['TABLE'] . "'";
        $sql = new query ($conn);
        $sql->set_sql($query);
        $sql->exec();//non richiede binding
        $all_field_exist = true;
        foreach ($this->fields as $key => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";


            /**
             *  Modifica 08/09/2011
             * Carico prima i campi modificati per servizio se esistono
             * M. Verrocchio
             **/
            $dir = str_replace('index.php', '', $_SERVER['SCRIPT_FILENAME']);
            $stdFileInc = $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
            if (!class_exists($field_type)) {
                if ($dir != '' && file_exists($dir . "fields/" . $field_type . ".inc")) {
                    include_once $dir . "fields/" . $field_type . ".inc";
                } elseif (file_exists($stdFileInc)) {
                    include_once $stdFileInc;
                } else {
                    include_once "fields/{$field_type}.inc";
                }

            }
            $this->no_field_value_by_tb = true;
            $field_obj = new $field_type ($this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            $this->no_field_value_by_tb = false;
            $allinea_stmt [$key] = $field_obj->allinea_db();
            if ($field_obj->attributes ['PK'] == 'yes') {
                $sql_pk_fields .= "{$field_obj->attributes['VAR']},";
            }
            //Luigi: corretto l'override della allinea_db
            if (method_exists($field_obj, 'allinea_db_storico')) {
                $allinea_storico [$key] = $field_obj->allinea_db_storico();
            }
        }

        $sql_pk_fields = rtrim($sql_pk_fields, ",");
        if ($sql->numrows > 0) {
            $tb_exist = true;
            $i = 0;
            while ($sql->get_row()) {
                $res [$i] = $sql->row ['COLUMN_NAME'];
                $i++;
            }
        }

        if ($tb_exist) {
            $sql_pk = "";
            $c = 0;
            $all_field_exist = true;
            foreach ($allinea_stmt as $key => $val) {
                if ($val != '') {
                    $field_exist = false;
                    foreach ($val as $vk => $vval) {
                        $nome_campo = explode(" ", $vval);
                        $field_exist [$key] [$vk] = false;
                        foreach ($res as $key_res => $val_res) {
                            if ($val_res == $nome_campo [0] || trim($nome_campo [0]) == '') {
                                $field_exist [$key] [$vk] = true;
                            }
                        }
                    }
                    foreach ($field_exist as $key1 => $val1) {
                        foreach ($val1 as $vk => $boolval) {
                            if (!$boolval) {
                                $all_field_exist = false;
                                $index = (count($this->fields) * $vk) + $key;
                                //                          $eq_sql_str [$index] = "alter table EQ_" . $this->form ['TABLE'] . " add {$allinea_stmt[$key][$vk]}";
                                /**
                                 * Per i field che vogliono tipi di colonne nello storico diversi ripsetto alla tabella di raccolta.
                                 * Ad es. il field date_hyper , ha tre colonne virutali in tabella ma reali nello storico . Questo perch ad ogni update
                                 * l'XMR fa un insert into S_[TABLE] select * from [TABLE] quindi devono essere reali.
                                 */
                                if (isset($allinea_storico[$key][$vk])) {
                                    $s_sql_str [$index] = "alter table S_" . $this->form ['TABLE'] . " add {$allinea_storico[$key][$vk]}";
                                } else {
                                    $s_sql_str [$index] = "alter table S_" . $this->form ['TABLE'] . " add {$allinea_stmt[$key][$vk]}";
                                }
                                $sql_str [$index] = "alter table " . $this->form ['TABLE'] . " add {$allinea_stmt[$key][$vk]}";
                            }
                        }
                    }
                }
            }
            $sql_pk_drop = "alter table " . $this->form ['TABLE'] . " drop constraint PK_" . $this->form ['TABLE'] . " cascade";
            $sql_pk = "alter table " . $this->form ['TABLE'] . " add constraint PK_" . $this->form ['TABLE'] . " primary key ($sql_pk_fields)";
            $sql_fk_coord_drop = "alter table " . $this->form ['TABLE'] . " drop constraint FK_" . $this->form ['TABLE'] . "_COORD cascade";
            global $config_service;
            if ($config_service ['VISITNUM_PROGR'] == 1)
                $sql_fk_coord = "alter table " . $this->form ['TABLE'] . " add constraint FK_" . $this->form ['TABLE'] . "_COORD foreign key (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";
            else
                $sql_fk_coord = "alter table " . $this->form ['TABLE'] . " add constraint FK_" . $this->form ['TABLE'] . "_COORD foreign key (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";
        } else {
            $this->body .= "Table <b>" . $this->form ['TABLE'] . "</b> doesn't exist<br/>";
            foreach ($allinea_stmt as $key => $val) {
                if (isset($val)) {
                    foreach ($val as $key_f => $val_f)
                        if ($val_f != '') {
                            $sql_create_fields .= "{$val_f},";
                            if (isset($allinea_storico[$key][$key_f])) $sql_create_fields_storico .= "{$allinea_storico[$key][$key_f]},";
                            else $sql_create_fields_storico .= "{$val_f},";
                        }
                }
            }

            $sql_create_fields = rtrim($sql_create_fields, ",");
            $sql_create_fields_storico = rtrim($sql_create_fields_storico, ",");
            $sql_str_ini = "create table " . $this->form ['TABLE'] . '(';
            $sql_str_end = ")";
            $sql_str [0] = $sql_str_ini . $sql_create_fields . $sql_str_end;
            $sql_pk = "alter table " . $this->form ['TABLE'] . " add constraint PK_" . $this->form ['TABLE'] . " primary key ($sql_pk_fields)";
            $config_service = $this->config_service;
            if ($config_service ['VISITNUM_PROGR'] == 1)
                $sql_fk_coord = "alter table " . $this->form ['TABLE'] . " add constraint FK_" . $this->form ['TABLE'] . "_COORD foreign key (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, VISITNUM_PROGR, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";
            else
                $sql_fk_coord = "alter table " . $this->form ['TABLE'] . " add constraint FK_" . $this->form ['TABLE'] . "_COORD foreign key (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR)  references {$service}_COORDINATE (VISITNUM, ESAM, {$this->PK_SERVICE}, PROGR) on delete cascade";
//          $eq_sql_str [0] = "create table EQ_" . $this->form ['TABLE'] . " (ID NUMBER, COMMENTO varchar2(400)," . $sql_create_fields . $sql_str_end;
//          $eq_sql_str [1] = "alter table EQ_" . $this->form ['TABLE'] . " add constraint EQ_PK_" . $this->form ['TABLE'] . " primary key (ID)";

            $s_sql_str [0] = "create table S_" . $this->form ['TABLE'] . "(USERID VARCHAR2(32 CHAR),MODDT DATE,MODPROG NUMBER not null,FL_QUERY CHAR(1) not null,ID_QUERY NUMBER," . $sql_create_fields_storico . $sql_str_end;
            $s_sql_str [1] = "alter table S_" . $this->form ['TABLE'] . " add constraint S_PK_" . $this->form ['TABLE'] . " primary key (MODPROG)";

        }
        if (isset ($in ['CREATE']) || isset ($in ['CREATE_' . $this->form ['TABLE']])) {
            if (isset($sql_str)) {
                foreach ($sql_str as $key => $val) {
                    $sql = new query ($conn);
                    $sql->ins_upd($val); // bind non necessario
                }
            }
            if (isset($s_sql_str)) {
                foreach ($s_sql_str as $key => $val) {
                    $sql = new query ($conn);
                    $sql->ins_upd($val); // bind non necessario
                }
            }
            if (isset($eq_sql_str)) {
                foreach ($eq_sql_str as $key => $val) {
                    $sql = new query ($conn);
                    $sql->ins_upd($val); // bind non necessario
                }
            }
            if ($sql_pk_drop != '') {
                $sql = new query ($conn);
                $sql->ins_upd($sql_pk_drop); // bind non necessario
            }
            $sql = new query ($conn);
            $sql->ins_upd($sql_pk); // bind non necessario
            if ($sql_fk_coord_drop != '') {
                $sql = new query ($conn);
                $sql->ins_upd($sql_fk_coord_drop); // bind non necessario
            }
            $sql = new query ($conn);
            $sql->ins_upd($sql_fk_coord); // bind non necessario
            return true;
        } else
            return ($tb_exist && $all_field_exist);
    }


    /**
     * Drop della della tabella della form
     * vmazzeo 29.04.2014 per builder
     *
     * @return boolean
     */
    function drop_db_table()
    {
        $sql_pk_fields = null;
        $in = $this->session_vars;
        $conn = $this->conn;
        $service = $this->service;
        $tb_exist = false;
        $str_synonym = "select * from USER_SYNONYMS where synonym_name='" . $this->form ['TABLE'] . "'";
        $sql = new query ($conn);
        $sql->set_sql($str_synonym);
        $sql->exec();//non richiede binding
        $sql->get_row();
        if ($sql->row['TABLE_NAME'] != '') $this->form ['TABLE'] = $sql->row['TABLE_NAME'];
        $query = "select column_name from all_col_comments where table_name='" . $this->form ['TABLE'] . "'";
        $sql = new query ($conn);
        $sql->set_sql($query);
        $sql->exec();//non richiede binding
        $all_field_exist = true;
        foreach ($this->fields as $key => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";


            /**
             *  Modifica 08/09/2011
             * Carico prima i campi modificati per servizio se esistono
             * M. Verrocchio
             **/
            $dir = str_replace('index.php', '', $_SERVER['SCRIPT_FILENAME']);
            $stdFileInc = $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
            if (!class_exists($field_type)) {
                if ($dir != '' && file_exists($dir . "fields/" . $field_type . ".inc")) {
                    include_once $dir . "fields/" . $field_type . ".inc";
                } elseif (file_exists($stdFileInc)) {
                    include_once $stdFileInc;
                } else {
                    include_once "fields/{$field_type}.inc";
                }

            }
            $this->no_field_value_by_tb = true;
            $field_obj = new $field_type ($this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            $this->no_field_value_by_tb = false;
            $allinea_stmt [$key] = $field_obj->allinea_db();
            if ($field_obj->attributes ['PK'] == 'yes') {
                $sql_pk_fields .= "{$field_obj->attributes['VAR']},";
            }
            //Luigi: corretto l'override della allinea_db
            if (method_exists($field_obj, 'allinea_db_storico')) {
                $allinea_storico [$key] = $field_obj->allinea_db_storico();
            }
        }

        $sql_pk_fields = rtrim($sql_pk_fields, ",");
        if ($sql->numrows > 0) {
            $tb_exist = true;
            $i = 0;
            while ($sql->get_row()) {
                $res [$i] = $sql->row ['COLUMN_NAME'];
                $i++;
            }
        }
        $dropped = false;
        if ($tb_exist) {
            $drop_table = "drop table " . $this->form ['TABLE'] . "";
            $sql = new query ($conn);
            $sql->ins_upd($drop_table); // bind non necessario
            $drop_s_table = "drop table S_" . $this->form ['TABLE'] . "";
            $sql = new query ($conn);
            $sql->ins_upd($drop_s_table); // bind non necessario
            $dropped = true;
        }
        return $dropped;
    }

    /**
     * Controlla se la scheda e chiusa e recupera i dati salvati
     *
     * @param number $progr
     * @return boolean
     */
    function closed_form($progr = null)
    {
        $fields = null;
        $in = $this->session_vars;
        if (isset($progr)) $in['PROGR'] = $progr;
        $conn = $this->conn;

        unset($bind);
        if ($in [$this->PK_SERVICE] == 'next')
            return false;
        else {
            $where = "VISITNUM=:visitnum and ESAM=:esam and {$this->PK_SERVICE}=:pk_service";
            $bind['VISITNUM'] = $in ['VISITNUM'];
            $bind['ESAM'] = $in ['ESAM'];
            $bind['PK_SERVICE'] = $in [$this->PK_SERVICE];
        }
        if ($in ['PROGR'] != '') {
            $where .= "  and PROGR=:progr";
            $bind['PROGR'] = $in ['PROGR'];
        }
        if (isset ($in ['VISITNUM_PROGR'])) {
            $where .= " and VISITNUM_PROGR=:visitnum_progr";
            $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
        }
        $query = "select fine, USERID , ABILITATO from " . $this->service . "_coordinate where $where";
        $sql = new query ($conn);
        //$sql->set_sql ( $query );
        $sql->exec($query, $bind);//binded

        if ($sql->get_row() || $in ['equery_vis'] != '' || $in ['equery_view'] != '' || $in ['eform'] != '' || $in ['TB_COLL'] != '') {
            $abilitato = $sql->row ['ABILITATO'];
            if ($sql->row ['FINE'] == 1)
                $ret = true;
            else {
                //modifica chiara del 06/07/09: al posto di $sql->row ['FINE']=='' inserito $sql->row ['FINE']!='1'
                if ($sql->row['USERID'] == '' || $sql->row['USERID'] == $in['remote_userid'] || $sql->row ['FINE'] == '' || $sql->row ['FINE'] == '0') {
                    $ret = false;
                } else {
                    $ret = true;
                }
            }
            $sql_query = "select column_name from all_col_comments where table_name='" . strtoupper($this->form ['TABLE']) . "'";
            $where = '';
            foreach ($this->fields as $key => $val) {
                if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                    $field_type = "field_{$val['TYPE']}";
                else
                    $field_type = "field";
                /**
                 *  Modifica 08/09/2011
                 * Carico prima i campi modificati per servizio se esistono
                 * M. Verrocchio
                 **/
                if (!class_exists($field_type)) {
                    if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                        include_once $this->config_service['field_lib'] . $field_type . ".inc";
                    } elseif (file_exists($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc")) {
                        include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
                    } else {
                        include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/fields/{$field_type}.inc";
                    }
                }
                $this->no_field_value_by_tb = true;
                $field_obj = new $field_type ($this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
                $this->no_field_value_by_tb = false;
                $field_obj->insert_stmt(false);

                if (isset ($field_obj->field_stmt))
                    foreach ($field_obj->field_stmt as $key => $field_name) {
                        $fields .= $field_name . ",";
                        if (!isset ($fields_array))
                            $index = 0;
                        else
                            $index = count($fields_array);
                        $fields_array [$field_name] = $field_name;
                    }
            }
            $fields = rtrim($fields, ",");

            $str_synonym = "select * from USER_SYNONYMS where synonym_name='" . $this->form ['TABLE'] . "'";
            //          echo $str_synonym;
            $sql = new query ($conn);
            $sql->set_sql($str_synonym);
            $sql->exec();//non richiede binding
            $sql->get_row();
            if ($sql->row['TABLE_NAME'] != '') $this->form ['TABLE'] = $sql->row['TABLE_NAME'];

            $sql_pk = "select column_name from user_cons_columns where table_name='" . $this->form ['TABLE'] . "' and constraint_name=(select constraint_name from user_constraints where table_name='" . $this->form ['TABLE'] . "' and constraint_type='P')";
            $query = new query ($conn);
            $query->set_sql($sql_pk);
            $query->exec();//non richiede binding
            $new_insert = false;
            $where = '';

            unset($bind_where);
            while ($query->get_row()) {
                if (isset ($in [$query->row ['COLUMN_NAME']])) {
                    if ($where != '')
                        $where .= " and ";
                    $where .= $query->row ['COLUMN_NAME'] . "=:" . $query->row ['COLUMN_NAME'];
                    $bind_where[$query->row ['COLUMN_NAME']] = $in [$query->row ['COLUMN_NAME']];
                    if (!isset ($wheres))
                        $index = 0;
                    else
                        $index = count($wheres);

                    $wheres [$query->row ['COLUMN_NAME']] ['OP'] = "=";
                    $wheres [$query->row ['COLUMN_NAME']] ['f1'] = $query->row ['COLUMN_NAME'];
                    $wheres [$query->row ['COLUMN_NAME']] ['f2'] = $in [$query->row ['COLUMN_NAME']];

                }
            }
            $tables [$this->form ['TABLE']] = "";
            if (!$bind_where) {
                error_page($in ['remote_userid'], "PK Vuota, la tabella {$this->form ['TABLE']} non esiste. Entrare nel sistema per eseguire 'UpdateDB'.", "");
            }
            if ($abilitato == 2 && isset($_GET['PROGR']) && $_GET['PROGR'] != '') {
                // Abilitato = 2 , sta per record sub cancellato. Si prendono i dati dallo storico barrati al centro.
                $and_modprog = "and modprog=(select max(MODPROG) from S_{$this->form ['TABLE']} where $where)";
                $query_s = "select * from S_{$this->form ['TABLE']} where $where $and_modprog";
                //              echo $query_s;
                $sql_s = new query ($conn);
                //$sql_s->set_sql($query_s);
                $sql_s->exec($query_s, $bind_where);//binded
                $sql_s->get_row();
                //              echo $sql_s->row['FL_QUERY'];
                if ($sql_s->row['FL_QUERY'] == "U") {// La cancellazione  avvenuta tramite eQ. Prendo i valori dalla tabella vera.
                    $query_s = "select * from {$this->form ['TABLE']} where $where";
                }
            } else {
                $query_s = "select * from {$this->form ['TABLE']} where $where";
            }
            $sql_s = new query ($conn);
            //$sql_s->set_sql($query_s);
            $sql_s->exec($query_s, $bind_where);//binded
            if ($sql_s->numrows > 1) {
                error_page($in ['remote_userid'], "Query:\n $query_s\n results: ({$sql_s->str})" . $sql_s->numrows . " records", "");
            }
            $sql_s->get_row();
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
     * Costruisce il codice html della form in compilazione
     *
     * @param boolean $force_open
     * @param boolean $exclude_send_buttons
     * @param boolean $equery
     */
    function open_form($force_open = false, $exclude_send_buttons = false, $equery = false, $preview = false)
    {
        $testo_rev = null;
        $controlli = null;
        $equery_option = null;

        $in = $this->session_vars;
        $conn = $this->conn;
        $inputval = $this->tb_vals;
        $service = $this->service;
        $config_service = $this->config_service;

        $template_form_html = '';
        if (!$preview && $this->xmr) {
            if ($in [$config_service ['PK_SERVICE']] != 'next') {
                if (isset ($in ['VISITNUM']) && isset ($in ['ESAM'])) {
                    $sql_query = "select visitclose from {$service}_COORDINATE where VISITNUM=:visitnum and ESAM=:esam and VISITNUM_PROGR=:visitnum_progr and {$config_service['PK_SERVICE']}=:pk_service";
                    $sql = new query ($conn);
                    unset($bind);
                    $bind['VISITNUM'] = $in['VISITNUM'];
                    $bind['ESAM'] = $in['ESAM'];
                    $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                    $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                    //$sql->set_sql ( $sql_query );
                    $sql->exec($sql_query, $bind);//binded
                    $sql->get_row();
                    if ($sql->row ['VISITCLOSE'] == 1 && $in ['USER_TIP'] == 'DE' && !$force_open) {
                        error_page($in ['remote_userid'], $this->testo("visitIsClosed"), "");
                    }
                }
            }
        }
        $editing = true;
        if ($this->config_service['lang'] == "en") $lang = 1;
        else $lang = 0;
        if (!$preview) {
            //GENHD-42 rangecheck gestione alert e confirm con bootbox - vmazzeo 23.02.2015
            $this->salva_js = "
			function salva_f(ajax,showLoading,show_bootbox,realtime_equeries){
			cf();
			if (show_bootbox==undefined) show_bootbox=true;
			if (realtime_equeries==undefined) realtime_equeries=[];
			f=document.forms[0];
			el=f.elements;
	
			specifiche='A=ON&L=$lang&F=0';
			c1='';
			var my_func=arguments.callee.toString().match(/function ([^\(]+)/)[1];
			";
            //GENHD-42 rangecheck gestione alert e confirm con bootbox - vmazzeo 23.02.2015
            $this->invia_js = "
			function invia_f(ajax,showLoading,show_bootbox,realtime_equeries){
			cf();
			if (ajax==undefined) ajax=true;
			if (show_bootbox==undefined) show_bootbox=true;
			if (realtime_equeries==undefined) realtime_equeries=[];
			f=document.forms[0];
			el=f.elements;
			specifiche='A=ON&L=$lang&F=0';
			c1='';
			var my_func=arguments.callee.toString().match(/function ([^\(]+)/)[1];
			";
        }
        $this->check_js = '
					function cf(){
					var el;
					var f;
					f=document.forms[0];
					el=f.elements;
					document.forms[0].action=\'\';
					';

        $colonne = $this->form ['COLS'];
        $sysdate = date("dmY");
        if (isset($_GET['link_to']) && $_GET['link_to'] != '') $this->form ['LINK_TO'] = $_GET['link_to'];
        if (isset($_GET['link_to_send']) && $_GET['link_to_send'] != '') $this->form ['LINK_TO_SEND'] = $_GET['link_to_send'];//<!--vmazzeo 24.20.2015 bugfix non veniva considerato il link_to_send all\'invio della scheda-->
        $this->percorso_agg = "&nbsp;&gt;&nbsp;<b>" . $this->form ['TITOLO'] . "</b>";
        if (!$preview && $equery) {
            $showAsOpen = false;
            $sql_query = "select equery_int from {$this->service}_eq where stato in (0,2) and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";
            $sql = new query($this->conn);
            if ($sql->get_row($sql_query)) $equery_int = $sql->row['EQUERY_INT'];
            else $equery_int = 0;
            $sql_query_2 = "select EQ_ACTION,INIZIO,FINE from {$this->service}_COORDINATE where PROGR=:progr and VISITNUM=:visitnum and ESAM=:esam and VISITNUM_PROGR=:visitnum_progr and {$config_service['PK_SERVICE']}=:pk_service";
            $bind['VISITNUM'] = $in['VISITNUM'];
            $bind['ESAM'] = $in['ESAM'];
            $bind['PROGR'] = $in['PROGR'];
            $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
            $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];


            if ($sql->get_row($sql_query_2, $bind) && $sql->row['INIZIO'] == 1) {

                $eq_action = $sql->row['EQ_ACTION'];
                if ($sql->row['EQ_ACTION'] == 1) $showAsOpen = true;
                else $showAsOpen = false;
            } else $showAsOpen = false; //true //Sono dentro una equery, comunque ho matitine e mai scheda aperta in compilazione normale

            if ($equery_int != '') {

                if (strtolower($this->config_service['lang']) == 'it') {
                    $string_text = "Attenzione! i campi contrassegnati con il simbolo <i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i> hanno subito modifiche";
                } else {
                    $string_text = "Warning! fields with the symbol <i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i> has been modified";
                }
                $note_eq = "
				<div style='font-align:center;color:red;font-weight:bold'>
				$string_text
				</div>
				";
            }
        }

        $in ['form'] = htmlentities($in ['form']);
        $addPopulateAsPreviousButton = '';
        if ($in['PROGR'] > 1) {
            $addPopulateAsPreviousButton = "<button class='btn btn-info populateAsPrevious' disabled=true>Compila la scheda come la precedente</button>
			<script>
			$(document).ready(function(){
			    $('.populateAsPrevious').attr('disabled', false);
			    $('.populateAsPrevious').click(function(){
			    	populateAsPrevious();    
			    });
			});
			</script>";
        }
        $this->body = $note_eq . ' 
				<script>
					var pkService=\'' . $this->PK_SERVICE . '\';
				</script>
				' . $addPopulateAsPreviousButton . '
				<form method="post" id="esamForm" class="form-horizontal opened" role="form" action="index.php" enctype="multipart/form-data"  onsubmit="return false;" onKeypress="if (event.keyCode==13) return false;">
				<input type="hidden" name="' . $this->form ['TABLE'] . '"/>
						<input type="hidden" name="form" value="' . $in ['form'] . '"/>
								<input type="hidden" name="link_to" value="' . $this->form ['LINK_TO'] . '"/>
								<input type="hidden" name="link_to_send" value="' . $this->form ['LINK_TO_SEND'] . '"/> <!--vmazzeo 24.02.2015 bugfix non veniva considerato il link_to_send all\'invio della scheda-->
								<input type="hidden" name="REALTIME_EQUERIES"/>
<!--
										<table align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
										<tbody>
										<tr>
										<td>
										-->
									 ';

        $width = 100 / ($colonne * 2);
        if ($this->form ['TEMPLATE'] != '' && $in ['genera_template_html'] != "si")
            $template = file_get_contents("xml/{$this->form['TEMPLATE']}");
        else {
            $this->body .= '
			<!--		<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
			-->
					<!-- CAMPI -->' . $testo_rev;
            $template_form_html = '
<!--
					<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
-->
					<!-- CAMPI -->';
            $template = '';
            if ($this->config_service['COLS_HAS_SAME_WIDTH']) {
                for ($i = 0; $i < $colonne; $i++) {
                    $this->body .= "<!--
							<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>
									-->";
                    $template_form_html .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
                }
            }
            $this->body .= "<!--</tr>-->";
            $template_form_html .= "</tr>";

        }

        $c = 0;
        $condition_array = array();
        foreach ($this->fields as $i => $val) {
            if ($val ['CONDITION'] != '')
                $condition_array [count($condition_array)] = $val ['CONDITION'];
            if ($val ['TYPE'] == "file_cme" || $val ['TYPE'] == "file_doc") {
                $file_doc_eq['VAR'] = $val['VAR'];
                $file_doc_eq['THREAD'] = $val['THREAD'];
                $file_doc_eq['TOPIC'] = $val['TOPIC'];
                $files_doc[] = $file_doc_eq;
                /*
			        [TYPE] => file_doc
				    [VAR] => COMUNICAZIONI_FILE
				    [THREAD] => Comunicazione
				    [TOPIC] => Communications to AIFA
				 */
            }
        }
        $condition_array = array_unique($condition_array);
        if (!$preview && $equery) {


            $_GET['VISITNUM_PROGR'] -= 0;
            if (isset($_GET['PROGR'])) $progr = $_GET['PROGR'];
            else $progr = 1;

            //--eq_int=:eq_id and
            $sql_query = "select * from {$this->service}_eqfield where
				esam=:esam
				and visitnum=:visitnum
				and visitnum_progr=:visitnum_progr
				and progr=:progr
				and {$this->PK_SERVICE}=:pk_service
			and statofield=2
			";

//			echo( $sql_query."<br>");
            unset($bind);
            //$bind['EQ_ID']=$equery_int;
            $bind['ESAM'] = $_GET['ESAM'];
            $bind['VISITNUM'] = $_GET['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $_GET['VISITNUM_PROGR'];
            $bind['PROGR'] = $progr;
            $bind['PK_SERVICE'] = $_GET[$this->PK_SERVICE];
            $sql->exec($sql_query, $bind);//binded

            //------------------------------------
            $id_tipo_ref = $config_service['PRJ'] * 100000 + $_GET[$this->PK_SERVICE];

//			print_r($files_doc);

            if (!$files_doc) {
                $files_doc = array();
            }
            foreach ($files_doc as $l => $allegati) {
                unset($bind_array);
                $topic = preg_replace("/'/", "''", $allegati['TOPIC']);
                if ($topic != '') {
                    $topic_where = "topic=:topic";
                    $bind_array['TOPIC'] = $topic;
                } else $topic_where = "topic is null";

                $thread = $allegati['THREAD'];
                $thread = preg_replace("/'/", "''", $thread);

                $thread = str_replace("", "%", $thread);
                $thread = str_replace("", "%", $thread);
                $thread = str_replace("", "%", $thread);
                $thread = str_replace("", "%", $thread);
                $thread = str_replace("", "%", $thread);

                $bind_array['ID_TIPO_REF'] = $id_tipo_ref;
                $bind_array['TITOLO'] = $thread;
                //PENULTIMO!!!
                $sql_query = "
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
//			echo( "<br>".$sql_query."<br>1172");
                $sql2 = new query($this->conn);
                $sql2->exec($sql_query, $bind_array);//binded
                $sql2->get_row();
                //piccolo trick per i documenti allegati
                foreach ($files_doc as $key => $val) {
                    if ($sql2->row['KEYWORDS'] == $val['VAR']) {
                        $this->old_values[$val['VAR']] = $sql2->row['LAST_VER'];
                        $this->old_values_docs_nomi[$val['VAR']] = $sql2->row['NOME_FILE'];
                    }
                }

            } //chiudo qua foreach $c
            //------------------------------------

            if ($this->tb_vals) {
                foreach ($this->tb_vals as $k => $v) {
                    $this->old_values[$k] = $v;
                }
            }

            while ($sql->get_row()) {
                $this->tb_vals[$sql->row['FIELD']] = $sql->row['VALORE'];
            }
        }

        //var_dump($this->fields);
        foreach ($this->fields as $i => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";

            // 			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
            // 				include_once $this->config_service['field_lib'] . $field_type . ".inc";
            // 			} else
            // 			include_once "{$field_type}.inc";
            /**
             *  Modifica 08/09/2011
             * Carico prima i campi modificati per servizio se esistono
             * M. Verrocchio
             **/
            if (!class_exists($field_type)) {
                if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                    include_once $this->config_service['field_lib'] . $field_type . ".inc";
                } elseif (file_exists($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc")) {
                    include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
                } else {
                    include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/fields/{$field_type}.inc";
                }
            }
            $field_obj = new $field_type ($this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            //echo "{$field_obj->attributes['TYPE']}"; //.print_r($field_obj,true);

            if (isset($condition_array) && is_array($condition_array)) foreach ($condition_array as $key => $val) {
                if ($val == $field_obj->id)
                    $field_obj->attributes ['CALL_CF'] = "yes";
            }
            if ($inputval [$this->form ['READONLY']] == 1 && $inputval [$field_obj->id] != '') {

                if ($field_obj->id != $this->form ['READONLY_COMM']) {

                    $field_obj->attributes ['DISABLED'] = 'yes';
                }
            }
            if ($showAsOpen) $field_obj->make_open_html();
            else $field_obj->make_open_html($equery);
            if ($template == '') {
                /*
				if ($field_obj->attributes ['HIDE'] == 'yes') {
					//TODO: apriamo un div e non lo chiudiamo non mi piace
					if (isset ( $field_obj->attributes ['NAME'] ) && $field_obj->attributes ['NAME'] != '') {
						$template_form_html .= "</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>";
						$this->body .= "<!--</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>--></div><div id='tr_{$field_obj->attributes['NAME']}' class=\"form-group hideBlock -1\" >";
					} else {
						$template_form_html .= "\n<tr id='tr_{$field_obj->attributes['VAR']}'>";

						$this->body .= "\n<!--<tr id='tr_{$field_obj->attributes['VAR']}'>--></div><div id='tr_{$field_obj->attributes['VAR']}' class=\"form-group hideBlock -2\" >";
					}
					$c = 0;
				}
				*/

                if ($colonne == $c && $field_obj->attributes["TYPE"] != "hidden") {
                    $template_form_html .= "</tr>\n";
                    $this->body .= "<!--</tr>--></div>\n";
                    $c = 0;
                }
                if ($c == 0 && $field_type != 'field_hidden') { //&& $field_obj->attributes ['HIDE'] != 'yes'
                    $this->body .= "<!--<tr>--><div class=\"form-group " . ($field_obj->attributes ['HIDE'] == 'yes' ? 'hideBlock -2' : '') . "\" >";
                    $template_form_html .= "<!--<tr>--><div class=\"form-group " . ($field_obj->attributes ['HIDE'] == 'yes' ? 'hideBlock -2' : '') . "\">";
                }
                #echo $c;
                if ($field_obj->attributes ['TYPE'] != 'hidden') {
                    if ($field_obj->attributes ['COLS'] == '')
                        $c++;
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

                $this->body .= "\n<span data-field-id=\"{$field_obj->id}\">" . $field_obj->html . "</span>";
            } else {
                $template = str_replace("<<{$field_obj->id}>>", $field_obj->input_field, $template);
                $template = str_replace("<<TESTO {$field_obj->id}>>", $field_obj->input_txt, $template);
            }
            if (!$preview) {
                $this->salva_js .= $field_obj->salva_js;
            }
            $this->check_js .= $field_obj->check_js;
            if (!$preview) {
                $this->invia_js .= $field_obj->invia_js;
            }
            $this->script_js .= $field_obj->script;
            if (!$field_obj->validata)
                $this->validata = $field_obj->validata;
            $controlli .= $field_obj->controlli;
        }
        $js_function_on_send = $this->form ['JS_FUNCTION'];
        if ($this->form ['JS_ONSAVE'] == "yes")
            $js_function_on_save = $this->form ['JS_FUNCTION'];
        else
            $js_function_on_save = $this->form ['JS_ONSAVE'];
        $js_function_on_load = $this->form ['LOAD'];
        if ($template == '') {
            $this->body .= "
					<!--FINE CAMPI-->
					</div>
					";
            $template_form_html .= "
					<!--FINE CAMPI-->
					</table>
					";
        }
        if ($in ['genera_template_html'] == "si") {
            die ($template_form_html);
        }
        $this->onload = $js_function_on_load;
        $this->onload .= 'cf();';
        $this->check_js .= '
	}';
        if (!$preview) {
            $this->salva_js .= '
				  rc=contr(c1,specifiche);
						if (rc) {return false;}
						' . $controlli . '
								if (!rc){
					                    var jscustomfuncres = function(){return true;};
					    ';
            if ($js_function_on_save) {
                if (strpos(strtolower($js_function_on_save), "return") === false) {
                    //Non ho alcun return, meglio che lo imposti io d'ufficio.
                    $js_function_on_save = trim($js_function_on_save);
                    $js_function_on_save = trim($js_function_on_save, ";");
                    $js_function_on_save = "return (" . $js_function_on_save . ");";
                }
                $this->salva_js .= 'jscustomfuncres = function(){' . $js_function_on_save . '};';

            }
            $this->salva_js .= '
					                    if (!jscustomfuncres()) {return false;}
										/* VMAZZEO BUGFIX AL SAVE NON BISOGNA INVIARE LE REALTIME EQUERIES
										var json_string="[ { ";
										var and=false
										  for(var key in realtime_equeries){
										    if(and) json_string+=" , ";
										    json_string+=" \""+key+"\": "+JSON.stringify(realtime_equeries[key])+" ";
										    and=true;
										  }
										json_string+="} ]";
										document.forms[0].REALTIME_EQUERIES.value=json_string;*/
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
            $this->invia_js .= '
						rc=contr(c1,specifiche);
						if (rc) {return false;}
						' . $controlli . '
								if (!rc){
					        var jscustomfuncres = function(){return true;};
					    ';
            if ($js_function_on_send) {
                if (strpos(strtolower($js_function_on_send), "return") === false) {
                    //Non ho alcun return, meglio che lo imposti io d'ufficio.
                    $js_function_on_send = trim($js_function_on_send);
                    $js_function_on_send = trim($js_function_on_send, ";");
                    $js_function_on_send = "return (" . $js_function_on_send . ");";
                }
                $this->invia_js .= 'jscustomfuncres = function(){' . $js_function_on_send . ';}';

            }
            $this->invia_js .= '
					        if (!jscustomfuncres()) {return false;}
					   		var json_string="{  ";
							var and=false
							  for(var key in realtime_equeries){
							    if(and) json_string+=" , ";
							    json_string+=" \""+key+"\": "+JSON.stringify(realtime_equeries[key])+" ";
							    and=true;
							  }
							json_string+=" }";
							document.forms[0].REALTIME_EQUERIES.value=json_string;
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
        }
        if ($template == '')
            $this->body .= '</table><p align=center>';
        else
            $this->body .= $template . "<p align=center>";
        if (isset ($in ['eform']) && $in ['USER_TIP'] != 'DM')
            $this->body .= '
					<input type="submit" value="Vai alla form" name="equery" onclick="window.location.href=\'index.php?equery&amp;VISITNUM=\'+document.forms[0].VISITNUM.value+\'&amp;ESAM=\'+document.forms[0].VISITNUM.value+\'&amp;{$this->PK_SERVICE}=\'+document.forms[0].' . $this->PK_SERVICE . '.value+\'&amp;CENTER=\'+document.forms[0].CENTER.value+\'&amp;QUESTION=\'+document.forms[0].QUESTION.value+\'&amp;PROGR=\'+document.forms[0].PROGR.value;"/>
					';
        if (!$preview && $equery) {

            if (strtolower($this->config_service['lang']) == 'it') {
                $integra_button_text = "Integra Scheda";
                $eq_note_msg = "eQuery, commento generale:";
                $msg_generale_obbl = "Commento generale obbligatorio per le eQuery";
                $msg_field_obbl = "Commento al campo obbligatorio per le eQuery";
            } else {
                $integra_button_text = "Integrate Form";
                $eq_note_msg = "eQuery general comment:";
                $msg_generale_obbl = "General comment is necessary for eQuery";
                $msg_field_obbl = "Field comment is necessary for eQuery";
            }
            // Textarea per il DE, nel caso voglia fare un eQ:
            if (isset($_GET['ABILITA_EQ_DE'])) {
                // Nella check_eqfield controllo prima che almeno una textarea per campo sia stata aperta, altrimenti messaggio di alert
                // Successivamente controllo che tali textarea sia compilate altrimenti messaggi odi alert.

                $this->body .= '<script>
						
						
						function check_eqfield_de(){
						var el;
						var f;
						var result;
						var check;
						var espressione = /EQAREADE_/;
						f=document.forms[0];
						el=f.elements;
						result = true;
						';
                if (!$showAsOpen) {
                    $this->body .= '
						check = false;
						for (i=0;i<el.length;i++) {
							if(	espressione.test(el[i].name) && el[i].style.display!=\'none\'){
								check = true;
							}
						}
						';
                } else {
                    $this->body .= '
						check = true;
						';
                }
                $this->body .= '
						if(check==false){
						alert(\'' . $msg_field_obbl . '\');
								return false;
			}
									
								for (i=0;i<el.length;i++) {
								if(el[i].style.display!=\'none\' && el[i].value==\'\' && espressione.test(el[i].name) ){
								alert(\'' . $msg_field_obbl . '\');
										return false;
			}
										var nomecampo=el[i].name;
										nomecampo=nomecampo.replace(\'EQAREADE_\',\'\');
										if(el[i].value==\'\' && espressione.test(el[i].name) && document.getElementById(\'EQAREA_\'+nomecampo)!=null ){
										alert(\'E\\\' necessario rispondere a tutte le equery\');
										return false;
			}
			}
					   		return true;
			}
										</script>';
                $this->body .= '
						<input type="hidden" value="' . $equery_int . '" name="EQUERY_INT">
								<tr><br><td align=center><input type="submit" style="width:150px; height:50px; cursor:pointer; border:1px outset #0000FF" value="' . $integra_button_text . '" name="salva" onclick="if(!check_eqfield_de()){return false; }else{invia_f();}"/></td></tr>';


            }
            // Fine Textarea per il DE, nel caso voglia fare un eQ:

            $exclude_send_buttons = true;
        }
        $lock_send_buttons = false;
        if (!$preview && $this->config_service['dblock'] == 1 && isset($this->config_service['dblock'])) {
            /**
             * gestione DBLOCK
             * vmazzeo luglio 2013
             */
            //Lock del DB , prevede la creazione della tabella nomestudio_dblock
            //var_dump($in);


            //CONTROLLO SE QUESTO PAZIENTE E' DISABILITATO
            if (isset($in[$this->config_service['PK_SERVICE']]) && $in[$this->config_service['PK_SERVICE']] != 'next' && isset($in['CENTER']) && $in['CENTER'] != '') {
                $sql_query = "select CENTER,{$this->config_service['PK_SERVICE']},DBLOCK from {$this->service}_DBLOCK where CENTER={$in['CENTER']} and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} UNION select CENTER,{$this->config_service['PK_SERVICE']},DBLOCK from {$this->service}_DBLOCK where CENTER={$in['CENTER']} and {$this->config_service['PK_SERVICE']}=-1 ORDER BY {$this->config_service['PK_SERVICE']} DESC";
                $sql_patient = new query($this->conn);
                //PRENDO SOLTANTO IL PRIMO RECORD (se paziente  overridato spunter per primo, altrimenti ho il dblock generico per il centro)
                if ($sql_patient->get_row($sql_query)) {
                    $center_to_lock = $sql_patient->row['CENTER'];
                    $lock_sendsave_buttons = $sql_patient->row['DBLOCK'];
                }
            }
            $center_dblock_bin = decbin($lock_sendsave_buttons);
            //echo "DB VALUE ".$lock_sendsave_buttons;
            $center_dblock_bin = substr("00000000" . $center_dblock_bin, -1 * sizeof($config_service['dblock_functions']));
            $lock_save_send = substr($center_dblock_bin, -1 * array_search('SAVESEND', $config_service['dblock_functions']), 1);
            $lock_obvious = substr($center_dblock_bin, -1 * array_search('OBVIOUSCORRECTION', $config_service['dblock_functions']), 1);
            //echo $center_dblock_bin." OPEN FORM QUESTO PAZIENTE E' DISABILITATO SAVESEND? ".$lock_save_send." centro: ".$center_to_lock;

            //CONTROLLO SE IL CENTRO HA L'ARRUOLAMENTO DISABILITATO
            if (!isset($in[$this->config_service['PK_SERVICE']]) && isset($in['CENTER']) && $in['CENTER'] != '') {
                $sql_query = "select CENTER,{$this->config_service['PK_SERVICE']},DBLOCK from {$this->service}_DBLOCK where CENTER={$in['CENTER']} AND {$this->config_service['PK_SERVICE']}=-1 ORDER BY {$this->config_service['PK_SERVICE']} DESC";
                $sql_patient = new query($this->conn);
                //PRENDO SOLTANTO IL PRIMO RECORD (se paziente  overridato spunter per primo, altrimenti ho il dblock generico per il centro)
                if ($sql_patient->get_row($sql_query)) {
                    $center_to_lock = $sql_patient->row['CENTER'];
                    $lock_sendsave_buttons = $sql_patient->row['DBLOCK'];
                }
            }
            $center_dblock_bin = decbin($lock_sendsave_buttons);
            //echo "DB VALUE ".$lock_sendsave_buttons;
            $lock_new_patient = substr("00000000" . $center_dblock_bin, -1 * sizeof($config_service['dblock_functions']));
            $lock_new_patient = substr($center_dblock_bin, -1 * array_search('NEWPATIENT', $config_service['dblock_functions']), 1);
            //echo " NEW PATIENT? ".$lock_new_patient;
            if ($center_to_lock != '' && (($lock_save_send && $in ['USER_TIP'] != 'DM') || ($in['VISITNUM'] == 0 && $in['ESAM'] == 0 && $lock_new_patient)) || ($lock_obvious && $in ['USER_TIP'] == 'DM')) {
                $lock_send_buttons = true;
            }
        } else {
            $lock_send_buttons = false;
        }
        //Logger::send('qui');
        //Logger::send($lock_send_buttons);
        $xmlBaseName = preg_replace("!\.xml$!", "", $this->filename);
        if (!$preview && !$exclude_send_buttons && !$lock_send_buttons) {
            if ($this->buttons ['SALVA'] && ($in ['USER_TIP'] != 'DM' || isset ($in ['eform'])) && !isset ($_GET ['ABILITA_MOD_DM'])) {

                $this->body .= '
							<button class="btn btn-warning" type="button" onclick="salva_f();">
								<i class="fa fa-floppy-o bigger-110"></i>
								' . mlOut("{$xmlBaseName}.ButtonSave", $this->buttons ['SALVA']) . '
								</button>
										<!--
		  			<input type="submit" value="' . $this->buttons ['SALVA'] . ' " name="salva" onclick="salva_f();"/>-->';


            }
            if ($this->buttons ['SUBMIT'] != '' && !isset ($_GET ['ABILITA_MOD_DM']))
                $this->body .= '
						<button class="btn btn-info" type="button" onclick="submit();">
								<i class="fa fa-lock bigger-110"></i>
								' . mlOut("{$xmlBaseName}.ButtonSend", $this->buttons ['SUBMIT']) . '
								</button>
						<!--<input type="submit" value="' . $this->buttons ['SUBMIT'] . '" onclick="submit();"/>-->';

            if ($this->buttons ['INVIA'] && $in ['USER_TIP'] != 'DM' && !isset ($_GET ['ABILITA_MOD_DM']) || (isset ($in ['FORM']) || isset ($in ['SEARCH']))) {
                $this->body .= '
							<button class="btn btn-info" type="button" onclick="invia_f();">
								<i class="fa fa-lock bigger-110"></i>
								' . mlOut("{$xmlBaseName}.ButtonSend", $this->buttons ['INVIA']) . '
								</button>
							<!--<input type="submit"  value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/>-->';


            }
            if (!isset($_GET['SEARCH']) && !isset($_POST['SEARCH'])) {
                $query = "select id , to_char(quest_dt,'DD/MM/YYYY') as data from {$this->config_service['service_root']}_equery 
			where 
			visitnum=:visitnum 
			and esam=:esam 
			and progr=:progr 
			and visitnum_progr=:visitnum_progr
			and {$this->PK_SERVICE}=:pk_service 
			and validata is null";
                unset($bind);
                $bind['VISITNUM'] = $in['VISITNUM'];
                $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                $bind['ESAM'] = $in['ESAM'];
                $bind['PROGR'] = $in['PROGR'];
                $bind['PK_SERVICE'] = $in[$this->PK_SERVICE];
                $sql3 = new query($this->conn);
                $sql3->exec($query, $bind);//binded
                while ($sql3->get_row()) {
                    if (isset($_GET['ID_QUERY']) && $_GET['ID_QUERY'] == $sql3->row['ID']) $selected = " selected";
                    else $selected = " ";
                    $equery_option .= "<option value=\"{$sql3->row['ID']}\" {$selected}>Equery number {$sql3->row['ID']} ({$sql3->row['DATA']})</option>";
                }
            }

            //Logger::send($equery_option);
            //print_r($in);
            if ((($in ['USER_TIP'] == 'DM') && !isset ($in ['FORM']) && !isset ($in ['SEARCH'])) || (isset ($_GET ['ABILITA_MOD_DM']) && $this->session_vars ['USER_TIP'] == 'DE' && $this->config_service['de_modify_form_allowed'] == true)) { //&& (!isset($in['module']) || $in['module']!="SDV")
                if ($this->config_service['lang'] == "en") {
                    $reason = "Reason for change:";
                    $send = "Send";
                    $opt1 = "Obvious correction";
                    $opt2 = "Data entry error";
                    $opt3 = "Split/collapse of entry";
                    $opt4 = "Thesaurus codification";
                    $opt5 = "Investigator comment";
                    $alert_msg = "WARNING!!! It\\'s necessary to choose a reason for the revision";
                } else {
                    $reason = "Motivo della modifica:";
                    $send = "Procedi";
                    $opt1 = "Correzione ovvia";
                    $opt2 = "Errore inserimento dati";
                    $opt3 = "Scissione/collasso nell'inserimento";
                    $opt4 = "Codifica del dizionario";
                    $opt5 = "Commento dell'investigatore";
                    $alert_msg = "ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica";
                }

                if ($_GET['module'] != "SDV" && $_GET['sdv_action'] != 'eSignature') {
                    $this->body .= "
						<div class=\"form-group\">
						<label class=\"col-sm-6 control-label\" for=\"ID_QUERY\">$reason</label>
						<div id=\"ID_QUERY\" class=\"col-sm-6 no-padding-left\">
                        <select name='ID_QUERY'>
                        <!--option ></option-->
                        <OPTION VALUE=\"-1\">$opt2</option>
                        <OPTION VALUE=\"-2\">$opt1</option>
                        <!--OPTION VALUE=\"-3\">$opt3</option>
                        <OPTION VALUE=\"-4\">$opt4</option>
                        <OPTION VALUE=\"-5\">$opt5</option-->
                        $equery_option
                        </select>
                        </div>
                        </div>
                        ";
                }
                $this->body .= "
                    <p style=\"text-align:center;\">
                    <button class=\"btn btn-success\" type=\"button\" name=\"invia_dm\"
				";
                if ($_GET['module'] != "SDV" && $_GET['sdv_action'] != 'eSignature') {
                    $this->body .= "
                        onclick=\"
                        if (document.forms[0].ID_QUERY.value!='') invia_f();
                        else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;}
                        \"
                    ";
                } else {
                    $this->body .= "
                        onclick=\"invia_f();\"
                    ";
                }
                $this->body .= "
                    >
                    <i class=\"icon-ok bigger-110\"></i>
                    $send
                    </button>
                    <!--
                    <input type=\"submit\" value=\"$send\" name=\"invia_dm\" onclick=\"
                    if (document.forms[0].ID_QUERY.value!='') invia_f();
                    else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;}
                    \"/>
                    -->
                ";
            }
            if ($this->buttons ['ANNULLA'])
                $this->body .= '
						<button class="btn" type="reset" >
								<i class="icon-undo bigger-110"></i>
								' . mlOut("{$xmlBaseName}.ButtonReset", $this->buttons ['ANNULLA']) . '
								</button>
										<!--
		  <input type="reset" value="' . $this->buttons ['ANNULLA'] . '" name="annulla"  />-->';
            if ($this->buttons ['CANCELLA'])
                $this->body .= '
				<button class="btn" type="reset" >
								<i class="icon-undo bigger-110"></i>
								' . mlOut("{$xmlBaseName}.ButtonReset", $this->buttons ['CANCELLA']) . '
								</button>
										<!--
		  <input type="button" value="' . $this->buttons ['CANCELLA'] . '" name="cancella"  />-->';
        }
        $this->body .= '</p>';
        //vmazzeo nascondo legenda per bottoni aggiungendo classe hide 06.06.2014
        $this->body .= "<div class=\"alert alert-block alert-success hide\"><i class=\"icon-bullhorn\"></i> " . mlOut("System.FormButtonLegend", "Legenda per bottoni") . "</div>";
        if (isset($_GET['ABILITA_EQ_DE']) && $_GET['ABILITA_EQ_DE'] != '') {
            $this->body .= $this->riassunto_eq_per_esam($in [$this->PK_SERVICE], $in ['ESAM'], $in ['PROGR'], $in ['VISITNUM'], $in ['VISITNUM_PROGR']);
        }


        if (!$exclude_send_buttons) $this->body .= '</form>';
        $config_service = $this->config_service;
        if ($config_service ['PK_SERVICE'] == '')
            $this->PK_SERVICE = $this->config_service['PK_SERVICE'];
        else
            $this->PK_SERVICE = $config_service ['PK_SERVICE'];
        global $vlist;
        if (!isset($in['SEARCH']) && $in [$this->PK_SERVICE] != '' && !isset ($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN']) && !$exclude_send_buttons) {
            if ($this->form['NO_JS_BACK'] == "") $history = "onclick=\"history.back(); return false;\"";
            //commento back vmazzeo 06.06.2014
            $this->body .= '
			<div class="hide"><p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE] . '&VISITNUM=' . $in ['VISITNUM'] . '" ' . $history . '>&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p></div>';
        }

        $href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";

        $this->body = preg_replace("/#HREF#/", $href_alternativo, $this->body);

    }

    /**
     * Costruisce il codice html della form in visualizzazione
     *
     * @param boolean $no_link_back
     * @param boolean $equery
     */
    function close_form($no_link_back = false, $equery = false)
    {
        $testo_rev = null;
        $in = $this->session_vars;
        $inputval = $this->tb_vals;
        $service = $this->service;
        $conn = $this->conn;
        $config_service = $this->config_service;
        //echo "EQ: {$equery}<br/>";
        //debug_print_backtrace();
        if ($equery) {
            $integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);
            if (isset($integrazione->cro) && $integrazione->cro) {
                //Salto il validate_form!
            } else {
                if ($this->config_service['eQuery'] == 1) {
                    $sql_query = "select equery_int from {$this->service}_eq where stato in (2) and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";
                    $sql = new query($this->conn);
                    if ($sql->get_row($sql_query)) {
                        $equery_int = $sql->row['EQUERY_INT'];
                        if (($this->session_vars['USER_TIP'] == "DM" || $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR'] == $this->session_vars['USER_PROFILE']) && !isset($_GET['CRF'])) {
                            return $this->validate_form();

                        }
                    }
                }
            }
        }
        $this->percorso_agg = "&nbsp;&gt;&nbsp;<b>" . $this->form ['TITOLO'] . "</b>";
        if ($this->config_service['lang'] == "en") {
            $eq_note_msg = "eQuery general comment:";
            $integra_button_text = "Generate eQuery";
        } else {
            $eq_note_msg = "eQuery, commento generale: ";
            $integra_button_text = "Genera eQuery";
        }
        if ($in ['all_exams_view'] != '')
            $percorso = "";
        if ($in ['FORM'] != '')
            $percorso = "";
        global $vlist;
        if ($in ['ESAM'] != 0 && $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] == '')
            //$patient_table = patient_table ();
            //echo "FORM CLOSE_FORM EQUERY: $equery<br/>";

            $serialized_fields = array();
        $autocompile_fields = array();

        foreach ($this->fields as $i => $val) {
//			if ($val ['CONDITION'] != '')
//			$condition_array [count ( $condition_array )] = $val ['CONDITION'];
            if ($val ['TYPE'] == "file_cme" || $val ['TYPE'] == "file_doc") {
                $file_doc_eq['VAR'] = $val['VAR'];
                $file_doc_eq['THREAD'] = $val['THREAD'];
                $file_doc_eq['TOPIC'] = $val['TOPIC'];
                $files_doc[] = $file_doc_eq;
                /*
			        [TYPE] => file_doc
				    [VAR] => COMUNICAZIONI_FILE
				    [THREAD] => Comunicazione
				    [TOPIC] => Communications to AIFA
				 */
            }
            if ($val['TYPE'] == "multicheck") {
                $sfield['VAR'] = $val['VAR'];
                $sfield['TYPE'] = $val['TYPE'];
                $sfield['APPEND'] = '_MCHECK_[KEY]';
                $sfield['SEP'] = "|"; //Separatore
                $sfield['GROUP'] = 1; //Gruppo atomico formato da X valori (in questo caso è elenco dei singoli valori, quindi 1)
                $sfield['VALUE'] = "1"; //Valore da impostare nei nuovi campi creati in funzione della serializzazione (in questo caso i checkbox erano valorizzati a 1)
                $serialized_fields[$sfield['VAR']] = $sfield;
            }
            //carico dati campi autocompilati e TB=no
            if ($val['TB'] == "no" && $val['COMPILA_CONDITION_VAR']) {
                $acfield['VAR'] = $val['VAR'];
                $acfield['COMPILA_CONDITION_VAR'] = $val['COMPILA_CONDITION_VAR'];
                $acfield['COMPILA_CONDITION_VALUE'] = $val['COMPILA_CONDITION_VALUE'];
                $acfield['COMPILA_VAL'] = $val['COMPILA_VAL'];
                $acfield['COMPILA_OP'] = $val['COMPILA_OP'];
                $acfield['COND_OP'] = $val['COND_OP'];
                $autocompile_fields[$acfield['VAR']] = $acfield;
            }
        }
        if ($equery) {
            $_GET['VISITNUM_PROGR'] -= 0;
            if (isset($_GET['PROGR'])) $progr = $_GET['PROGR'];
            else $progr = 1;

            if ($integrazione->cro) {
                $sql_query = "select eq_int as equery_int from {$this->service}_eqfield where statofield in (0,2)
			            and {$this->PK_SERVICE}=:pk_service
			            and esam=:esam
                        and visitnum=:visitnum
                        and visitnum_progr=:visitnum_progr
                        and progr=:progr
                        ";
            } else {
                $sql_query = "select equery_int from {$this->service}_eq where stato in (0,2)
			            and {$this->PK_SERVICE}=:pk_service
                        ";
            }
            $bind['ESAM'] = $_GET['ESAM'];
            $bind['VISITNUM'] = $_GET['VISITNUM'];
            $bind['VISITNUM_PROGR'] = $_GET['VISITNUM_PROGR'];
            $bind['PROGR'] = $progr;
            $bind['PK_SERVICE'] = $_GET[$this->PK_SERVICE];
            $sql = new query($this->conn);
            $sql->exec($sql_query, $bind);
            if ($sql->get_row()) $equery_int = $sql->row['EQUERY_INT'];
            else $equery_int = 0;
            if ($equery_int != '') {
                $string_text = mlOut("WARNING_EQ_FORM", "Warning! fields with the symbol <i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i> has been modified");
                $note_eq = "
				<div style='text-align:center;color:red;font-weight:bold'>
				$string_text
				</div>
				";

                $sql_query = "select * from {$this->service}_eqfield where
				nvl(statofield,0)=2 
				and esam=:esam
				and visitnum=:visitnum
				and visitnum_progr=:visitnum_progr
				and progr=:progr
				and {$this->PK_SERVICE}=:pk_service
				";
                unset($bind);
                //$bind['EQ_ID']=$equery_int;
                $bind['ESAM'] = $_GET['ESAM'];
                $bind['VISITNUM'] = $_GET['VISITNUM'];
                $bind['VISITNUM_PROGR'] = $_GET['VISITNUM_PROGR'];
                $bind['PROGR'] = $progr;
                $bind['PK_SERVICE'] = $_GET[$this->PK_SERVICE];
                $sql->exec($sql_query, $bind);//binded


                $id_tipo_ref = $config_service['PRJ'] * 100000 + $_GET[$this->PK_SERVICE];

                foreach ($this->tb_vals as $k => $v) $this->old_values[$k] = $v;

                while ($sql->get_row()) {
                    $this->tb_vals[$sql->row['FIELD']] = $sql->row['VALORE'];
                }

                if (!$files_doc) {
                    $files_doc = array();
                }
                foreach ($files_doc as $l => $allegati) {

                    unset($bind_array);
                    $topic = preg_replace("/'/", "''", $allegati['TOPIC']);
                    if ($topic != '') {
                        $topic_where = "topic=:topic";
                        $bind_array['TOPIC'] = $topic;
                    } else $topic_where = "topic is null";

                    $thread = $allegati['THREAD'];
                    $thread = preg_replace("/'/", "''", $thread);


                    $bind_array['TITOLO'] = $thread;
                    $bind_array['ID_TIPO_REF'] = $id_tipo_ref;
                    //PENULTIMO!!!
                    $sql_query = "
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
//	   					echo $sql_query." 1620";

                    $sql2 = new query($this->conn);
                    $sql2->exec($sql_query, $bind_array); //binded
                    $sql2->get_row();

                    foreach ($files_doc as $key => $val) {
                        if ($sql2->row['KEYWORDS'] == $val['VAR']) {
                            $this->old_values[$val['VAR']] = $sql2->row['LAST_VER'];
                            $this->old_values_docs_nomi[$val['VAR']] = $sql2->row['NOME_FILE'];
                        }
                    }
                }
            }
        }
        $this->body = '<form method="post" class="form-horizontal closed"><div class="form-group">';
        if (class_exists('SDV_module')) {
            $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], null);
            $this->body .= $sdv->before_close_form($this);
        }

        //DMENGOLI - 2015-07-28 - Sistemo i dati in DB se ho campi serializzati
        foreach ($serialized_fields as $sfield) {
            if ($sfield['VAR'] && $this->tb_vals[$sfield['VAR']]) {
                $svalue = $this->tb_vals[$sfield['VAR']];
                $splval = explode($sfield['SEP'], $svalue);
                foreach ($splval as $sval) {
                    if ($sval || $sval === "0") { //Potrebbe esserci 0 come chiave in linea teorica....
                        $append = str_replace("[KEY]", $sval, $sfield['APPEND']);
                        $this->tb_vals[$sfield['VAR'] . $append] = $sfield['VALUE'];
                    }
                }
            }
        }
        //DMENGOLI - 2015-10-13 - Sistemo i dati in DB se ho campi autocompilati e non in tabella (TB=no)
        foreach ($autocompile_fields as $acfield) {
            if ($acfield['VAR']) {
                $condition_var = $acfield['COMPILA_CONDITION_VAR'];
                $condition_val = $acfield['COMPILA_CONDITION_VALUE'];
                $compila_val = $acfield['COMPILA_VAL'];
                if ($acfield['COND_OP']) $operatore_confronto = $acfield['COND_OP'];
                else $operatore_confronto = "==";
                $operatore = $acfield['COMPILA_OP'];
                $operatore = str_replace("AND", "&&", $operatore);
                if ($operatore == '') $operatore = "&&";
                $vars = explode("|", $condition_var);
                $valuess = explode("|", $condition_val);
                $valore_var = array();
                $valori = "";
                $condizioni_tot = "";
                foreach ($vars as $key => $var) {
                    $valore_var[$var] = $this->tb_vals[$var];
                    $valori .= " - $valore_var[$var] ";
                    $values = explode(",", $valuess[$key]);
                    $condizioni = "";
                    foreach ($values as $kv => $val) {
                        $this->tb_vals[$acfield['VAR']] = $compila_val;
                    }
                }
                //echo "<pre>";
                //print_r($this->tb_vals);
                //echo "</pre>";
            }
        }

        $this->body .= '		       				 <!-- CAMPI -->' . $testo_rev;
        $colonne = $this->form ['COLS'];
        $width = 100 / ($colonne * 2);
        for ($i = 0; $i < $colonne; $i++)
            $this->body .= "<!--<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>-->";
        $this->body .= "<!--</tr>-->";
        if ($note_eq != "") {
            //print_r($note_eq);
            $this->body .= "<!--<tr><td colspan=\"" . ($colonne * 2) . "\" align=\"center\">$note_eq</td>--><div class=\"alert alert-warning center\">$note_eq</div>";
        }
        $this->body .= "<!--</tr>-->";

        $c = 0;
        // Gestione deleted
        if (isset($_GET['PROGR']) && $_GET['PROGR'] != '' && $in[$this->PK_SERVICE] != '') {
            $sql_delete = "select *  from {$this->service}_coordinate where  {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}
			and esam={$in ['ESAM']} and visitnum={$in ['VISITNUM']} and visitnum_progr={$in ['VISITNUM_PROGR']} and progr={$in ['PROGR']}
			";
            $query_delete = new query($this->conn);
            if ($query_delete->get_row($sql_delete)) {
                $deleted = $query_delete->row['ABILITATO'];
            }

        }
        foreach ($this->fields as $i => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";

            /**
             *  Modifica 08/09/2011
             * Carico prima i campi modificati per servizio se esistono
             * M. Verrocchio
             **/
            if (!class_exists($field_type)) {
                if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                    include_once $this->config_service['field_lib'] . $field_type . ".inc";
                } elseif (file_exists($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc")) {
                    include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
                } else {
                    include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/fields/{$field_type}.inc";
                }
            }
            $field_obj = new $field_type ($this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            $field_obj->make_open_html($equery);

            if ((isset($_GET['CRF_BLANK']) || isset($_GET['CRF_ANNOTE'])) && $field_type == "field") {// Caso dei titoli condizionati nella 1Click CRF
                if (preg_match("/,/", $field_obj->attributes ['CONDITION_VALUE'])) {
                    $vals = explode(",", $field_obj->attributes ['CONDITION_VALUE']);
                    foreach ($vals as $key => $value) {
                        if ($in[$field_obj->attributes ['CONDITION']] == $value) {
                            $field_obj->condition_passed = 1;
                        }
                    }
                } else {
                    if ($in[$field_obj->attributes ['CONDITION']] == $field_obj->attributes ['CONDITION_VALUE']) {
                        $field_obj->condition_passed = 1;
                    }
                }

            }
            //			echo $field_obj->condition_passed; echo $field_obj->attributes ['VAR'];echo " SHOW CRF: ".$field_obj->attributes ['SHOW_CRF']; echo "<hr>";
            if ($field_obj->attributes ['TYPE'] != 'hidden' && ($field_obj->attributes ['HIDE'] != 'yes' || $field_obj->condition_passed || $field_obj->attributes ['SHOW_VIS'] == 'yes' || ($field_obj->attributes ['SHOW_CRF'] == 'yes' && (isset($_GET['CRF_BLANK']) || isset($_GET['CRF_ANNOTE']))))) {
                $field_html = "";
                $field_obj->make_close_html($equery, null, $deleted); //TODO: Chiamata modificata qua. ($equery_int?)
                $field_html = $field_obj->html;

                if ($colonne <= $c) {
                    $this->body .= "<!--</tr><tr>--></div><div class=\"form-group\">";
                    $c = 0;
                }
                if ($field_obj->attributes ['COLS'] == '')
                    $c++;
                else {
                    $c += $field_obj->attributes ['COLS'];
                }
                if (class_exists('SDV_module')) {
                    $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], null);
                    $field_html = $sdv->after_make_close_html($this, $i, $field_obj);
                }

                $this->body .= "<span data-field-id=\"{$field_obj->id}\">$field_html</span>";
            }
        }

        $this->body .= "</div>
		  <!--FINE CAMPI-->
		  ";
        $config_service = $this->config_service;
        $this->onload = '';
        if (strtolower($this->config_service['lang']) == 'it') {
            $integra_button_text = "Integra Scheda";
            $SDV_button_text = "Valida Scheda";
            $eq_note_msg = "eQuery, commento generale:";
            $msg_generale_obbl = "Commento generale obbligatorio per le eQuery";
            $msg_field_obbl = "Commento al campo obbligatorio per le eQuery";
            $link_eq = "eQuery risposte";
        } else {
            $integra_button_text = "Integrate Form";
            $SDV_button_text = "Validate Form";
            $eq_note_msg = "eQuery general comment:";
            $msg_generale_obbl = "General comment is necessary for eQuery";
            $msg_field_obbl = "Field comment is necessary for eQuery";
            $link_eq = "Answered eQueries";
        }
        // Textarea per il DM, nel caso voglia fare un eQ:
        if (isset($_GET['ABILITA_EQ_DM'])) {


            // Nella check_eqfield controllo prima che almeno una textarea per campo sia stata aperta, altrimenti messaggio di alert
            // Successivamente controllo che tali textarea sia compilate altrimenti messaggi odi alert.
            $this->body .= '<script>
					function check_eqfield(){
					var el;
					var f;
					var result;
					var check;
					var espressione = /EQAREA_/;
					f=document.forms[0];
					el=f.elements;
					result = true;
					check = false;
					for (i=0;i<el.length;i++) {
					if(el[i].style.display!=\'none\'  && espressione.test(el[i].name) ){
					check = true;
		}
		}
					if(check==false){
					alert(\'' . $msg_field_obbl . '\');
							return false;
		}
							for (i=0;i<el.length;i++) {
							if(el[i].style.display!=\'none\' && el[i].value==\'\' && espressione.test(el[i].name) ){
							alert(\'' . $msg_field_obbl . '\');
									result = false;
		}
		}
				   		return result;
		}
									</script>';

            $this->body .= '<input type="hidden" name="' . $this->PK_SERVICE . '" value="' . $_GET[$this->PK_SERVICE] . '"   />
					<input type="hidden" name="ESAM" value="' . $_GET['ESAM'] . '"   />
							<input type="hidden" name="VISITNUM" value="' . $_GET['VISITNUM'] . '"   />
									<input type="hidden" name="VISITNUM_PROGR" value="' . $_GET['VISITNUM_PROGR'] . '"   />
											<input type="hidden" name="PROGR" value="' . $_GET['PROGR'] . '"   />
													<input type="hidden" name="USERID_INS" value="' . $in['remote_userid'] . '"   />
															<input type="hidden" name="TABLE" value="' . $this->form['TABLE'] . '"   />
																	';

            $this->body .= '<br><table><tr><td align=center><input type="submit" style="width:150px; height:50px; cursor:pointer; border:1px outset #0000FF"  value="' . $integra_button_text . '" name="salva_eq_dm" onclick="if(!check_eqfield()){return false;}" /></td></tr>
					</table>';
            $this->body .= '<br>';
        }
        if (class_exists('SDV_module')) {
            $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], null);
            $this->body .= $sdv->after_close_form($this);
        }
        if (isset($_GET['SDV']) && $this->config_service['SDV'] == "1" && isset($this->config_service['SDV'])) {
            $this->body .= '<br><table><tr><td align=center><input type="submit" style="width:150px; height:50px; cursor:pointer; border:1px outset #0000FF"  value="' . $SDV_button_text . '" name="source_data_verification" /></td></tr>
					</table>';
            $this->body .= '<br>';
        }

        if (!isset($_GET['CRF'])) {
            $this->body .= $this->riassunto_eq_per_esam($in [$this->PK_SERVICE], $in ['ESAM'], $in ['PROGR'], $in ['VISITNUM'], $in ['VISITNUM_PROGR']);
        }

        // Fine Textarea per il DM, nel caso voglia fare un eQ:
        /*
		if (($in ['all_exams_view'] == '' && $in ['NO_LINK'] == '') && !$no_link_back){
		//$this->body .= "<br/><a href=\"javascript:history.back();\">&lt;&lt;{$this->config_service['Torna_lista_schede']}</a>";
			$history = "";
			if($this->form['NO_JS_BACK']=="") $history="onclick=\"history.back(); return false;\"";
			//commento back vmazzeo 06.06.2014
			//$this->body .= '<div><p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE].'&VISITNUM='.$in ['VISITNUM'].'&ESAM='.$in ['ESAM'].'" '.$history.'>&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p></div>';
			$this->body .= '<div><p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE].'&VISITNUM='.$in ['VISITNUM'].'" '.$history.'>&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p></div>';
		}
		*/
        if ($in['USER_TIP'] == 'DM') {
            $this->body .= "<div align=right><a href=\"index.php?&list=equery_list_answered_DM.xml\">&gt;&gt; {$link_eq}</a></div>";
        }

        //TODO: MERGE QUI SOTTO?

        if ($in['USER_TIP'] == 'DM' && $this->config_service['STUDY_TYPE'] != 'LABORATORY_RANGE' && $this->config_service['STUDY_TYPE'] != 'CLINICAL_TRIAL') {
            $linkMod = "index.php?{$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}&VISITNUM={$_GET['VISITNUM']}&ESAM={$_GET['ESAM']}&PROGR={$_GET['PROGR']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&ABILITA_MOD_DM=1";
            $this->body = "<button class=\"btn btn-sm btn-warning\" onclick=\"window.location.href='{$linkMod}';\">
							<i class=\"icon-pencil bigger-110\"></i>
							<span class=\"bigger-110 no-text-shadow\">" . mlOut("System.ModifyForm", "Modify form") . "</span>
						</button>" . $this->body;
        }
        //TODO: NUOVO AUDIT TRAIL QUI??
        if ($this->config_service['AT_FANCY']) {
            $auditTrailJs = "showAudit('" . mlOut("Audit.AuditTitle", "Audit Trail") . "');";
            $this->body = "<a class=\"btn btn-sm btn-info \" style=\"float:right\" href=\"#form_a_t\" data-toggle=\"modal\">
		<i class=\"fa fa-eye bigger-110\"></i>
		<span class=\"bigger-110 no-text-shadow\">" . mlOut("Audit.ShowAudit", "Show Audit Trail") . "</span>
				</a>" . $this->body;
        }
        $this->body .= "</p>";
        $href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";
        $this->body = preg_replace("/#HREF#/", $href_alternativo, $this->body);
        $this->body = preg_replace("/<tr><\/tr>/", "", $this->body);
        //$this->body .= "</td></tr></table>";
        $this->body .= '</form>';
        if (!isset($_GET['CRF'])) {
            $this->body .= $this->auditTrail($_GET['VISITNUM'], $_GET['VISITNUM_PROGR'], $_GET['ESAM'], $_GET['PROGR'], $_GET[$this->config_service['PK_SERVICE']]);
        }
        if ((!isset($_GET['CRF_BLANK']) && !isset($_GET['CRF_ANNOTE']))) {
            $this->body = $this->recordBaseLog($_GET['VISITNUM'], $_GET['VISITNUM_PROGR'], $_GET['ESAM'], $_GET['PROGR'], $_GET[$this->config_service['PK_SERVICE']]) . $this->body;
        }
    }

    function recordBaseLog($v, $vp, $e, $p, $pk)
    {
        $bind['VISITNUM'] = $v;
        $bind['VISITNUM_PROGR'] = $vp;
        $bind['ESAM'] = $e;
        $bind['PROGR'] = $p;
        $dateFormat = "DD/MM/YYYY HH24:MI:SS";
        $bind[$this->config_service['PK_SERVICE']] = $pk;
        $whereClause = "m.VISITNUM=:VISITNUM and m.VISITNUM_PROGR=:VISITNUM_PROGR and m.ESAM=:ESAM and m.PROGR=:PROGR and m.{$this->config_service['PK_SERVICE']}=:{$this->config_service['PK_SERVICE']}";
        $sql_coord = "select to_char(m.insertdt,'{$dateFormat}') as insertdt, to_char(m.moddt,'{$dateFormat}') as moddt, a1.nome||' '||a1.cognome as createuser, a2.nome||' '||a2.cognome as lastmoduser from {$this->service}_coordinate m, ana_utenti a1, ana_utenti a2
		            where m.create_user=a1.userid(+) and m.last_mod_user=a2.userid(+) and {$whereClause}";
        $sql = new query($this->conn);
        $sql->get_row($sql_coord, $bind);
        $coorData = $sql->row;
        $ret = "
		<div id='baseAuditRecordLog' class='alert alert-info' style='text-align:right; padding:2px; font-size:0.8em;'>
				Record " . mlOut('Audit.CreatedOn', "created on") . " {$coorData['INSERTDT']} " . mlOut('Audit.CreatedBy', 'by') . " {$coorData['CREATEUSER']}";
        if (trim($coorData['LASTMODUSER']) != '' && ($coorData['INSERTDT'] != $coorData['MODDT'])) { //Devo fare TRIM perchè ho lo spazio [NOME] [COGNOME]
            $ret .= " <br/>
				" . mlOut("Audit.LastModDate", "last modification on") . " {$coorData['MODDT']} " . mlOut('Audit.ModBy', 'by') . " {$coorData['LASTMODUSER']}
		";
        }
        return $ret . "</div>";
    }

    function auditTrail($v, $vp, $e, $p, $pk)
    {
        $equery = null;
        $deleted = null;
        $auditLog = null;
        $ret = '
			<button class="btn btn-info" id="showAudit">' . mlOut("form.showAudit", "Mostra audit trail") . '</button>
					<script>
					$(\'#showAudit\').click(function(){
						$(\'#form_a_t\').modal();
					});
					</script>
			<div id="form_a_t" class="modal fade" tabindex="-1">
			    <div class="modal-dialog">
			        <div class="modal-content">
			            <div class="modal-header no-padding">
			                <div class="table-header">
			                    <button type="button" class="close" data-dismiss="modal" aria-hidden="true"><span class="white">&times;</span></button>
			                    <i class="fa fa-eye"></i>&nbsp; Audit Trail
			                </div>
			            </div>
			            <div class="modal-body no-padding">';
        $bind['VISITNUM'] = $v;
        $bind['VISITNUM_PROGR'] = $vp;
        $bind['ESAM'] = $e;
        $bind['PROGR'] = $p;
        $dateFormat = "DD/MM/YYYY HH24:MI:SS";
        $bind[$this->config_service['PK_SERVICE']] = $pk;
        $whereClause = "m.VISITNUM=:VISITNUM and m.VISITNUM_PROGR=:VISITNUM_PROGR and m.ESAM=:ESAM and m.PROGR=:PROGR and m.{$this->config_service['PK_SERVICE']}=:{$this->config_service['PK_SERVICE']}";
        $sql_coord = "select to_char(m.insertdt,'{$dateFormat}') as insertdt, to_char(m.moddt,'{$dateFormat}') as moddt, a1.nome||' '||a1.cognome as createuser, a2.nome||' '||a2.cognome as lastmoduser from {$this->service}_coordinate m, ana_utenti a1, ana_utenti a2
		            where m.create_user=a1.userid(+) and m.last_mod_user=a2.userid(+) and {$whereClause}";
        $sql = new query($this->conn);
        $sql->get_row($sql_coord, $bind);
        $coorData = $sql->row;
        $sql_stor = "select to_char(eq.quest_dt,'{$dateFormat}') as eq_quest_dt, a.nome as uname, a.cognome as usurname, 
					a1.nome as iname, a1.cognome as isurname,
					to_char(m.moddt, '{$dateFormat}') as s_moddt,
					m.* 
					from S_{$this->form['TABLE']} m, ana_utenti a, {$this->service}_equery eq, ana_utenti a1
					where a.userid=m.userid
					and a1.userid=m.userid
					and eq.id(+)=m.id_query
					and {$whereClause} order by MODPROG desc
				";
        $sql->exec($sql_stor, $bind);
        $prev_values = $this->tb_vals;
        $noStor = true;
        $modId = 0;
        while ($sql->get_row()) {
            $noStor = false;
            $storData[] = $sql->row;
            foreach ($sql->row as $key => $val) {
                if ($key == 'UNAME'
                    || $key == 'USURNAME'
                    || $key == 'INAME'
                    || $key == 'ISURNAME'
                    || $key == 'USERID'
                    || $key == 'MODDT'
                    || $key == 'MODPROG'
                    || $key == 'FL_QUERY'
                    || $key == 'ID_QUERY'
                    || $key == 'EQ_QUEST_DT'
                    || $key == 'USERID_INS'
                    || $key == 'S_MODDT'
                ) continue;
                if ($prev_values[$key] != $val) {
                    $mods[$modId]['FIELDS'][$key]['old'] = $val;
                    $mods[$modId]['FIELDS'][$key]['new'] = $prev_values[$key];
                }
            }
            if ($sql->row['ID_QUERY'] > 0) {
                $mods[$modId]['REASON'] = "eQuery n.ro " . $sql->row['ID_QUERY'];
            } else {
                if ($sql->row['ID_QUERY'] == "-1") {
                    $mods[$modId]['REASON'] = "Data entry error";
                } else {
                    $mods[$modId]['REASON'] = mlOut(audit . equery_neg, 'Modifica dati');
                }
            }
            $mods[$modId]['ModBy'] = $sql->row['UNAME'] . " " . $sql->row['USURNAME'];
            $mods[$modId]['ModOn'] = $sql->row['S_MODDT'];
            $prev_values = $sql->row;
            $modId++;
        }
        $ret .= "
		<div id='auditRecordLog' class='alert alert-info' style='text-align:right'>
				Record " . mlOut('Audit.CreatedOn', "created on") . " {$coorData['INSERTDT']} " . mlOut('Audit.CreatedBy', 'by') . " {$coorData['CREATEUSER']}";
        if ($coorData['INSERTDT'] != $coorData['MODDT'])
            $ret .= " <br/>
				" . mlOut("Audit.LastModDate", "last modification on") . " {$coorData['MODDT']} " . mlOut('Audit.ModBy', 'by') . " {$coorData['LASTMODUSER']}
		</div>
		<hr>";
        $ret .= '
		<div class="timeline-container">';
        foreach ($mods as $mkey => $mval) {
            $rowAudit = '
					<div class="timeline-item clearfix">
						<div class="timeline-info">
							<i class="timeline-indicator icon-edit btn btn-success no-hover"></i>
						</div>
						<div class="widget-box transparent">
							<div class="widget-header widget-header-small">
								<h5 class="smaller">
									<a href="#" class="blue">' . $mval['ModBy'] . '</a>
									<span class="grey">' . $mval['REASON'] . '</span>
								</h5>
								<span class="widget-toolbar no-border">
									<i class="icon-time bigger-110"></i> ' . $mval['ModOn'] . '
								</span>

								<span class="widget-toolbar">
									<a href="#" data-action="collapse"><i class="icon-chevron-up"></i></a>
								</span>
							</div>
							<div class="widget-body">
								<div class="widget-main">
											<table class="auditTable">
												<thead>
													<tr>
														<th class="col-sm-4">' . mlOut('Audit.Field', "Field") . '</th>
														<th class="col-sm-4">' . mlOut('Audit.ChangeType', "Change Type") . '</th>
														<th class="col-sm-4">' . mlOut('Audit.OldValue', "Old value") . '</th>
														<th class="col-sm-4">' . mlOut('Audit.NewValue', "New Value") . '</th>
													</tr>
												</thead>
												<tbody>
									';

            foreach ($this->fields as $i => $val) {
                $fieldModified = false;
                if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                    $field_type = "field_{$val['TYPE']}";
                else
                    $field_type = "field";

                if (!class_exists($field_type)) {
                    if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                        include_once $this->config_service['field_lib'] . $field_type . ".inc";
                    } elseif (file_exists($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc")) {
                        include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
                    } else {
                        include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/fields/{$field_type}.inc";
                    }
                }

                $field_obj = new $field_type ($this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
                $fieldModified = false;
                foreach ($mval['FIELDS'] as $fk => $fv) {
                    //TODO: effettuare controlli accurati
                    if ($field_obj->id == $fk) $fieldModified = true;
                    foreach ($field_obj->values as $chkIdx => $chkValue) {
                        if ($chkIdx == $fk) $fieldModified = true;
                    }
                }
                if ($fieldModified) {
                    $this->tb_vals[$field_obj->id] = $mval['FIELDS'][$field_obj->id]['old'];
                    if ($this->tb_vals["D_" . $field_obj->id]) {
                        $this->tb_vals["D_" . $field_obj->id] = $mval['FIELDS']["D_" . $field_obj->id]['old'];
                    }

                    foreach ($field_obj->values as $chkIdx => $chkValue) {
                        if (isset($mval['FIELDS'][$chkIdx])) {
                            $this->tb_vals[$chkIdx] = $mval['FIELDS'][$chkIdx]['old'];
                        }
                    }
                    $field_obj = new $field_type ($this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
                    $field_obj->attributes['SHOW_SELECTED'] = "yes";
                    $field_obj->make_close_html($equery, $deleted);
                    $old_val = $this->tb_vals[$field_obj->id];
                    $old_html = $field_obj->input_field;
                    $this->tb_vals[$field_obj->id] = $mval['FIELDS'][$field_obj->id]['new'];
                    if ($this->tb_vals["D_" . $field_obj->id]) {
                        $this->tb_vals["D_" . $field_obj->id] = $mval['FIELDS']["D_" . $field_obj->id]['new'];
                    }

                    foreach ($field_obj->values as $chkIdx => $chkValue) {
                        if (isset($mval['FIELDS'][$chkIdx])) {
                            $this->tb_vals[$chkIdx] = $mval['FIELDS'][$chkIdx]['new'];
                        }
                    }
                    $field_obj = new $field_type ($this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
                    $field_obj->attributes['SHOW_SELECTED'] = "yes";
                    $field_obj->make_close_html($equery, $deleted);
                    $new_val = $this->tb_vals[$field_obj->id];
                    $new_html = $field_obj->input_field;
                    $checkboxField = false;
                    foreach ($field_obj->values as $chkIdx => $chkValue) {
                        if (isset($mval['FIELDS'][$chkIdx])) {
                            $checkboxField = true;
                            $old_val += $mval['FIELDS'][$chkIdx]['old'];
                            $new_val += $mval['FIELDS'][$chkIdx]['new'];
                        }
                    }
                    $diff = $new_val - $old_val;
                    if ($old_val != $new_val) $changeType = mlOut("Audit.Update", "update");
                    if ($new_val == '') $changeType = mlOut("Audit.Delete", "delete");
                    if ($old_val == '') $changeType = mlOut("Audit.Create", "create");
                    if ($checkboxField) $changeType = mlOut("Audit.Changed", "changed");
                    $rowAudit .= "
							<tr>
								<td class=\"col-sm-4\">" . $field_obj->input_txt . "</td>
								<td class=\"col-sm-4\">" . $changeType . "</td>
								<td class=\"col-sm-4\">" . $old_html . "</td>
								<td class=\"col-sm-4\">" . $new_html . "</td>
							</tr>";
                }
            }

            $rowAudit .= '
										</tbody>
									</table>
								</div>
							</div>
						</div>					
					</div>	
					';
            $auditLog = $rowAudit . $auditLog;
        }
        $ret .= $auditLog . "</div>";

        return $ret . " </div>
				        </div>
				    </div>
				</div>
			</div>";
    }

    /**
     * Discrimina sulla modalit di visualizzzazione della form e produce il relativo codice html
     *
     *    $xml_form->make_html (    false, => $no_link_back
     *                                false, => $closed
     *                                true,  => $force_open : obbliga la visualizzazione della form in compilazione
     *                                true   => $exclude_send_buttons : i bottoni salva,invia,annulla non vengono inseriti e la form non viene chiusa lasciando
     *                                                                  modo di gestirli nella funzione chiamante
     *                             );
     */
    function make_html($no_link_back = false, $closed = false, $force_open = false, $exclude_send_buttons = false)
    {
        $stato_prat = null;
        $confs = null;
        $in = $this->session_vars;
        $inputval = $this->tb_vals;
        $remote_userid = $in ['remote_userid'];
        if (isset($_GET['CRF']) && $in [$this->PK_SERVICE] != '') {
            /**Esplosione delle progressive nel Patient Dossier:*/
            $in ['PROGR'] = $this->session_vars['PROGR'] = $_GET['PROGR'];
        }

        if ($in [$this->PK_SERVICE] == 'next')
            return false;
        else
            $where = "VISITNUM='" . $in ['VISITNUM'] . "' and ESAM='" . $in ['ESAM'] . "' and {$this->PK_SERVICE}='" . $in [$this->PK_SERVICE] . "'";
        if ($in ['PROGR'] != '')
            $where .= "  and PROGR='" . $in ['PROGR'] . "'";
        if (isset ($in ['VISITNUM_PROGR']))
            $where .= " and VISITNUM_PROGR={$in['VISITNUM_PROGR']}";

        $sql_query = "select fine, userid, visitclose from {$this->config_service['service']}_coordinate where $where";
        //		$sql_query="select fine, userid, visitclose from {$this->config_service['service']}_coordinate where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and esam='{$in['ESAM']}' and progr='{$in['PROGR']}' and visitnum='{$in['VISITNUM']}' and visitnum_progr='{$in['VISITNUM_PROGR']}'";
        $sql = new query($this->conn);
        $sql->get_row($sql_query);
        /*
		if(isset($this->workflow) && is_numeric($in[$this->PK_SERVICE]) && $in[$this->PK_SERVICE]!="") {
			$sql_query="SELECT ID_STATO FROM {$this->config_service['service']}WF_STATO WHERE PK_SERVICE='{$in[$this->PK_SERVICE]}' ";
			$sql_stato=new query($this->conn);
			$sql_stato->get_row($sql_query);
			$stato_prat=$sql_stato->row['ID_STATO'];
		}
		*/
        if ($sql->row['FINE'] == 1) $this->closed = true;


        if ((isset($_GET['CRF_BLANK']) || isset($_GET['CRF_ANNOTE']))) {
            if ($closed) {
                $this->closed_form();
                $this->closed = true;
                $this->close_form(true);
                return;
            }
        } else {

            //Separo CRO/Standard Integrazioni da qua
            $integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);
            if (isset($integrazione->cro) && $integrazione->cro) {

                if ($sql->row['USERID'] == $remote_userid && $sql->row['FINE'] != '1' && $sql->row['VISITCLOSE'] != '1') $in['USER_TIP'] = 'DE';
                if ($closed) {
                    $this->closed_form();
                    $this->closed = true;
                    $this->close_form(true);
                    return;
                }
                if ($force_open) {
                    $this->closed_form();
                    $this->closed = false;
                    $this->open_form($force_open, $exclude_send_buttons);
                    return;
                }
                if ($in ['USER_TIP'] == 'DE') {
                    if ($this->config_service['eQuery'] == 1)
                        $integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);
                    if (!$this->closed_form($this->session_vars['PROGR'])) {

                        $this->open_form();
                    } else {
                        //Penso che mi basti sapere che le integrazioni sono abilitate...
                        if ($integrazione->eq_enabled) { //&& $integrazione->isRole($this->session_vars['USER_PROFILE'])
                            if (isset($_GET['ABILITA_EQ_DE'])) { //&& $this->config_service['eQuerySpec']['Integrazione']['ROLE']==$this->session_vars['USER_PROFILE']
                                $this->open_form(true, null, true);
                            } else {
                                $this->close_form($no_link_back, true);
                            }
                        } else {
                            $this->close_form($no_link_back);
                        }
                        //gestione abilita modifica form chiusa da parte del DE
                        if (isset ($_GET ['ABILITA_MOD_DM']) && $in ['USER_TIP'] == 'DE' && $this->config_service['de_modify_form_allowed'] == true) {
                            $this->open_form(true, false, false);
                        } /*else {
							$this->close_form ( $no_link_back );
						}*/
                    }
                }
                if ($in ['USER_TIP'] == 'DM') {
                    if ($this->config_service['eQuery'] == 1)
                        $integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);
                    if (!$this->closed_form()) {
                        $this->close_form($no_link_back);
                    } else {
                        if ($integrazione->eq_enabled) { //&& $integrazione->isApprovRole($this->session_vars['USER_PROFILE'])
                            if (isset($_GET['ABILITA_MOD_DM'])) { //&& $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR']==$this->session_vars['USER_PROFILE']
                                $this->open_form();
                            } else {
                                $this->close_form($no_link_back, true);
                            }
                        } else {
                            $this->close_form($no_link_back);
                        }
                    }
                }
                if ($in ['USER_TIP'] == 'RO') {
                    if ($this->config_service['eQuery'] == 1)
                        $integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);
                    if (!$this->closed_form()) {

                        $this->close_form($no_link_back);
                    } else {
                        if ($integrazione->eq_enabled && $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR'] == $this->session_vars['USER_PROFILE'] && !isset($_GET['ABILITA_MOD_DM'])) {
                            $this->close_form($no_link_back, true);

                        } elseif ($integrazione->eq_enabled && $this->config_service['eQuerySpec']['Integrazione']['CONTROL_ROLE'] == $this->session_vars['USER_PROFILE'] && !isset($_GET['ABILITA_MOD_DM'])) {

                            $this->close_form($no_link_back, true);

                        } elseif (isset($_GET['ABILITA_MOD_DM'])) {
                            $this->open_form();
                        } else {

                            $this->close_form($no_link_back);
                        }
                    }
                }
            } else {
                //echo "Form: make_html, USER_TIP:{$in['USER_TIP']}<br/>";
                if ($sql->row['USERID'] == $remote_userid && $sql->row['FINE'] != '1' && $sql->row['VISITCLOSE'] != '1' && $in['USER_TIP'] != 'DM') $in['USER_TIP'] = 'DE';
                else if ($sql->row['USERID'] != "" && $this->config_service['eQuery'] == 1 && $this->config_service['eQuerySpec']['Integrazione']['ROLE'][$this->service] != $this->session_vars['USER_PROFILE']) {
                    $in['USER_TIP'] = 'RO';
                    $force_open = false;
                    //			$closed=true;
                }

                if ($closed) {
                    $this->closed_form();
                    $this->closed = true;
                    $this->close_form(true);
                    return;
                }
                if ($force_open) {
                    $this->closed_form();
                    $this->closed = false;
                    $this->open_form($force_open, $exclude_send_buttons);
                    return;
                }

                if ($this->config_service['eQuery'] == 1) {
                    $integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);
                }

                if ($_GET['VISITNUM_PROGR'] == '') {
                    $_GET['VISITNUM_PROGR'] = 0;
                    $this->session_vars['VISITNUM_PROGR'] = 0;
                }

                //TODO: verificare necessit di tale chiamata
                $this->closed_form();

                if ($this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$this->config_service['service']][$_GET['VISITNUM']] != "")
                    $exclude_visit = $this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$this->config_service['service']][$_GET['VISITNUM']];
                else
                    $exclude_visit = $this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$_GET['VISITNUM']];


                if ($this->config_service['eQuery'] == 1 && $integrazione->eq_enabled && !isset($exclude_visit) && !isset($this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_ESAM'][$_GET['ESAM']])
                ) {
                    $integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);

                    if (isset($integrazione->cro) && $integrazione->cro) {
                        if ($integrazione->eq_enabled && $this->config_service['eQuerySpec']['Integrazione']['ROLE'] == $this->session_vars['USER_PROFILE'] && isset($_GET['ABILITA_EQ_DE'])) {
                            $this->open_form(true, null, true);
                        } else {
                            $this->close_form($no_link_back);
                        }
                    } else {
                        if ($integrazione->role == $integrazione->profilo) {
                            if ($integrazione->eq_enabled && !($integrazione->eq_int != '' && $integrazione->stato == 2)) {
                                //echo $integrazione->stato;
                                if ($integrazione->eq_int != '') {

                                    //echo $integrazione->role." ".$integrazione->profilo;

                                    if ($_GET['PROGR'] == "") $progr = 1;
                                    else $progr = $_GET['PROGR'];

                                    $sql_query = "select EQ_ACTION from {$this->service}_COORDINATE
	                                where INV_QUERY={$integrazione->eq_int}
	                                and esam={$_GET['ESAM']}
	                                and progr=$progr
	                                and VISITNUM={$_GET['VISITNUM']}
	                                and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}
	                                and {$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}
	                                ";
                                    $sql = new query($this->conn);
                                    $sql->get_row($sql_query);
                                    $eq_action = $sql->row['EQ_ACTION'];

                                    //if ($eq_action==1){
                                    //	$this->open_form ();
                                    //	return;
                                    //} else {
                                    $this->open_form(true, null, true);
                                    return;
                                    //}
                                } else {
                                    $this->open_form(true, null, true);
                                    return;
                                }
                            } else {
                                $this->close_form(false, true);
                                return;
                            }
                        }

                        if ($integrazione->isObserverRole($integrazione->profilo) || $integrazione->approv_role == $integrazione->profilo || $integrazione->approv_role[$stato_prat] == $integrazione->profilo) {
                            if ($confs == 'eq' || $confs != '' /*non  ancora premuto su protocolla e invia per le tipo I*/) {
                                echo "FORM QUA1<br/>";
                                //EDO aggiungo questo con equery false quando non acora l'azienda ha terinato di inviare la pratica
                                $this->close_form(false, false);
                            } else {
                                echo "FORM QUA2<br/>";
                                //approvazione integrazioni
                                $this->close_form(false, true);
                            }
                        } else {
                            //questo else serve per vedere le schede azienda da parte di aifa anche da un profilo sbagliato, naturally le vede chiuse
                            $this->close_form();
                        }
                        //ATTENZIONE ATENZIONE
                        //levato questo 24/11/10 perch non ,i visualizzava da aifa le schede azienda
                        //return;
                        //			if(($in['USER_TIP']!='DE' && $this->session_vars['USER_TIP']!='DE') /*|| $in['USER_TIP']=='RO'*/)
                        //			return;
                    }
                } else {
                    if ($in ['USER_TIP'] == 'DE') {
                        if (!$this->closed_form()) {
                            $this->open_form();
                        } else {
                            $this->close_form($no_link_back);
                        }
                    }
                    if ($in ['USER_TIP'] == 'DM') {
                        if (!$this->closed_form()) {
                            $this->close_form($no_link_back);
                        } else {
                            if ($integrazione->eq_enabled && $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR'] == $this->session_vars['USER_PROFILE'] && !isset($_GET['ABILITA_MOD_DM'])) {
                                $this->close_form($no_link_back, true);

                            } elseif (isset($_GET['ABILITA_MOD_DM'])) {
                                $this->open_form();
                            } else {

                                $this->close_form($no_link_back);
                            }

                        }

                    }


                    if ($in ['USER_TIP'] == 'RO') {

                        $this->closed_form();
                        $this->close_form($no_link_back);
                    }
                }
            }
        }

    }

    function Save($stato, $ajax = false)
    {

    }

    function getErrors()
    {
        return $this->errors;
    }

    function csv_form($estrazione_dir, $ext = ".csv", $separator = ";", $param_where = null, $evenif_open = false, $bind_where = null)
    {
        $controlli = null;
        $colonne = null;
        $c = null;
        $cols_headers = null;
        $file = null;
        $return_string = null;
        $excel = null;
        $patient_table = null;
        global $in;
        global $inputval;
        global $percorso;
        global $conn;

        if ($this->form['CONT_FORM'] == 'yes') {
            $num_form_progr = $inputval['PROGR_NUM'];
            //echo "<hr>$num_form_progr<hr>";
            for ($form_progr = 1; $form_progr <= $num_form_progr; $form_progr++) {
                foreach ($this->fields as $i => $val) {
                    if (isset($val['TYPE']) && $val['TYPE'] != '') $field_type = "field_{$val['TYPE']}";
                    else $field_type = "field";
                    include_once "{$field_type}.inc";
                    $field_obj = new $field_type($this, $i);
                    $field_obj->attributes['VAR'] .= "_PROGR_" . $form_progr;
                    $field_obj->make_close_html();
                    #echo "<br/>{$field_obj->attributes['VAR']} {$field_obj->attributes['TYPE']} - $colonne - $c -post ";
                    if ($colonne == $c) {
                        $this->body .= "</tr><tr>";
                        $c = 0;
                    }
                    #echo $c;
                    if ($field_obj->attributes['TYPE'] != 'hidden' && $field_obj->attributes['TYPE'] != '') {
                        if ($field_obj->attributes['COLS'] == '') $c++;
                        else {
                            $c += $field_obj->attributes['COLS'];

                        }

                    }
                    if ($field_obj->attributes['TYPE'] != 'hidden') $this->body .= $field_obj->html;
                    /*$this->salva_js.=$field_obj->salva_js;
					 $this->check_js.=$field_obj->check_js;
					 $this->invia_js.=$field_obj->invia_js;*/
                    if (!$field_obj->validata) $this->validata = $field_obj->validata;
                    $controlli .= $field_obj->controlli;
                }
            }
        } else {
            //$SEPARATOR = ";";
            $campi_sql = "";
            foreach ($this->fields as $i => $val) {
                if (isset($val['TYPE']) && $val['TYPE'] != '') $field_type = "field_{$val['TYPE']}";
                else $field_type = "field";
                include_once "{$field_type}.inc";
                $field_obj = new $field_type($this, $i);
                if ($field_obj->attributes['VAR'] != '' && $field_obj->attributes['TB'] != 'no') {
                    $field_obj->insert_stmt();

//modifica by G.Tufano 10/06/2011
//gestisco curr_campo e curr_cols_header come array
//altrimenti i checkbox non si visualizzavano (si
//visualizzava solo l'ultimo)
                    if ($this->form['SHOW_CODE'] == '') {
                        $iter = 1;
                        $curr_campo = "";
                        $curr_cols_header = "";
                        foreach ($field_obj->field_stmt as $value) {
                            if ($iter > 1 && $value == $field_obj->attributes['VAR'] . 'RC') continue;
                            $curr_campo .= "curr_table.{$value}, ";
                            if ($field_obj->attributes['ALIAS_DL'] == '')
                                $curr_cols_header .= '"' . $value . '"' . $separator;
                            else
                                $curr_cols_header .= '"' . $field_obj->attributes['ALIAS_DL'] . '"' . $separator;
                            $iter++;
                        }

                        if ($field_obj->attributes['EXCEL_QUERY'] == '') {
                            $cols_headers .= $curr_cols_header;
                            $campi_sql .= $curr_campo;
                        } else {

                            $campi_sql .= "{$field_obj->attributes['EXCEL_QUERY']} AS \"{$field_obj->attributes['VAR']}\", ";

                        }

                    } else {
                        $iter = 1;
                        $curr_campo = "";
                        $curr_cols_header = "";
                        foreach ($field_obj->field_stmt as $value) {
                            if ($iter > 1 && substr($value, strlen($value) - 5) == '_DTRC') continue;
                            $curr_campo .= "curr_table.{$value}, ";
                            $cols_headers .= '"' . $value . '"' . $separator;
                            if ($field_obj->attributes['EXCEL_QUERY'] == '') {
                                $cols_headers .= $curr_cols_header;
                                $campi_sql .= $curr_campo;

                            } else {
                                $campi_sql .= "{$field_obj->attributes['EXCEL_QUERY']} AS \"{$field_obj->attributes['VAR']}\", ";

                            }
                            $iter++;
                        }

                    }
                    //$campi_sql.="curr_table.{$field_obj->field_stmt[0]}, ";
                }
            }

            $campi_sql = rtrim($campi_sql, ", ");
//			echo $campi_sql."<hr>";
            $cols_headers = rtrim($cols_headers, $separator) . "\r\n";
            if ($this->form['DB_FILE'] == '') {
                //prendo solo le schede chiuse
                if ($evenif_open == false) {
                    $fine_condition = "AND coor.fine=1";
                } //prendo anche le schede aperte (fine = null)
                else {
                    $fine_condition = "";
                }
                $excel_str = "select $campi_sql from {$this->form['TABLE']} curr_table, " . $this->service . "_coordinate coor 
				where coor.{$this->PK_SERVICE}=curr_table.{$this->PK_SERVICE} and coor.progr=curr_table.progr 
				and coor.visitnum=curr_table.visitnum and coor.visitnum_progr=curr_table.visitnum_progr and coor.esam=curr_table.esam " . $fine_condition;

                //possibilita' di aggiungere clausole WHERE
                if (!is_null($param_where) || $param_where != "") {
                    $excel_str .= " AND " . $param_where;
                }
                $excel_sql = new query($conn);
            } else {
                $conn2 = new dbconn(null, null, null, $this->form['DB_FILE']);
                $excel_str = "select $campi_sql from {$this->form['PREFIX']}{$this->form['TABLE']} curr_table";

                //possibilita' di aggiungere clausole WHERE
                if (!is_null($param_where) || $param_where != "") {
                    $excel_str .= " WHERE " . $param_where;
                }
                $excel_sql = new query($conn2);
            }

            $str = "ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY'";
            //$excel_sql->set_sql($str);
            $excel_sql->exec($str, $bind_where);//non richiede binding
            if ($return_string) {
                return $excel_str;
            }
            //$excel_sql->set_sql($excel_str);
            $excel_sql->exec($excel_str, $bind_where);//non richiede binding per forza: di norma i paramentri sono calcolati funzionalmente
            //			echo $excel_str;
            //					die();
            /*if ($excel_sql->numcols>248) {
			//				$excel=$excel_sql->tb_res_r();

			//echo "<hr>".$excel_sql->numcols;
			//echo " -- ".$this->form['FNAME']."<hr>";
			}
			else
			$excel=$excel_sql->tb_res();*/
            include_once("file.inc");
            $file_csv = new file($this->form['FNAME'] . $ext, $estrazione_dir);
            $file_csv->write($cols_headers);
            while ($excel_sql->get_row()) {
                $file_csv->csv_line($excel_sql->row, $separator);
                #$handle=fopen("/http/www/overvap/html/") ;

            }
            //						echo $excel;
            //						die();
            foreach ($this->fields as $i => $val) {
                if (isset($val['TYPE']) && $val['TYPE'] != '') $field_type = "field_{$val['TYPE']}";
                else $field_type = "field";
                include_once "{$field_type}.inc";
                $field_obj = new $field_type($this, $i);
                $field_obj->make_close_html();
                #echo "<br/>{$field_obj->attributes['VAR']} {$field_obj->attributes['TYPE']} - $colonne - $c -post ";
                if ($colonne == $c) {
                    $this->body .= "</tr><tr>";
                    //echo "qui";
                    $c = 0;
                }
                #echo $c;
                if ($field_obj->attributes['TYPE'] != 'hidden' && $field_obj->attributes['TYPE'] != '') {
                    if ($field_obj->attributes['COLS'] == '') $c++;
                    else {
                        $c += $field_obj->attributes['COLS'];

                    }

                }
                //				if ($field_obj->attributes['TYPE']!='hidden') $this->body.=$field_obj->html;
                $testo = preg_replace("'<[\/\!]*?[^<>]*?>'si", "", $field_obj->testo);

                if ($field_obj->attributes['VAR'] != '' && $val['TYPE'] != 'text' && $val['TYPE'] != 'hidden' && $testo != '' && $this->form['ADD_QUESTIONS'] != '') {
                    if ($field_obj->attributes['EXCEL_NAME'] == '') $excel = str_replace("<th>{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['VAR']}</font> <br> {$testo}</th>", $excel);
                    else $excel = str_replace("<th>{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['EXCEL_NAME']}</font> <br> {$testo}</th>", $excel);
                    if ($field_obj->attributes['EXCEL_NAME'] == '') $excel = str_replace("<th>D_{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['VAR']}</font> <br> {$testo}</th>", $excel);
                    else $excel = str_replace("<th>D_{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['EXCEL_NAME']}</font> <br> {$testo}</th>", $excel);
                }
                /*$this->salva_js.=$field_obj->salva_js;
				 $this->check_js.=$field_obj->check_js;
				 $this->invia_js.=$field_obj->invia_js;*/
                if (!$field_obj->validata) $this->validata = $field_obj->validata;
                $controlli .= $field_obj->controlli;
            }
        }

        return $file;


    }


    /**
     * excel_form
     *
     * Crea una versione excel dei dati raccolti con una form a partirte
     * da un xml
     *
     * @return unknown
     */

    function excel_form($param_where = null, $evenif_open = false, $bind_where = null)
    {
        $patient_table = null;
        $controlli = null;
        global $in;
        global $inputval;
        global $percorso;
        global $conn;
        if ($in['allarga']) $valore = 10;
        else $valore = 2;
        /*$percorso=split(",", $this->form['PERCORSO']);
		 for ($p=0;$p<count($percorso);$p++){
		 if ($inputval['D_PROTOCOL']=='' && $percorso[$p]=='D_PROTOCOL') $per.="EpSSG Registry";
		 $per.=$inputval[$percorso[$p]]." &gt; ";
		 }
		 $per.=$this->form['TITOLO'];*/
        //$percorso.="&nbsp;&gt;&nbsp;<b>".$this->form['TITOLO']."</b>";
        if ($in['all_exams_view'] != '') $percorso = "";
        if ($in['FORM'] != '') $percorso = "";
        //if ($in['ESAM']!=0) $patient_table=patient_table();
        $this->body = '<!--tabs-->
		 <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
		  <tbody>
		  <tr>
		    <td class="testo" colspan="2">' . $percorso . '</td></tr>
		  <tr>
		    <td colspan="2">
		      <!--table align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
		        <tbody>
		        <tr>
		          <td class="int" colspan="2">' . $this->form['TITOLO'] . '</td>
						</tr>
						</tbody>
					</table>
					<table border="0" cellpadding="2" cellspacing="2" width="98%" align="center">
					  <tbody>
					  <tr>
					  	<td class="centro" colspan="2" valign="bottom" width="55%" align="center"><a href="/help.htm" target="_blank">Help</a></td>
					  </tr>
						</tbody>
					</table--></table>
		' . $patient_table . '
		     				 <table class="sf" align="center" border="0" cellpadding="' . $valore . '" cellspacing="' . $valore . '" width="80%"><tr>
		       				 <!-- CAMPI -->';
        $colonne = $this->form['COLS'];
        $width = 100 / ($colonne * 2);
        for ($i = 0; $i < $colonne; $i++) $this->body .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
        $this->body .= "</tr>";
        $c = 0;
        #echo "<hr>colonne= $colonne<hr>";

        if ($this->form['CONT_FORM'] == 'yes') {
            $num_form_progr = $inputval['PROGR_NUM'];
            //echo "<hr>$num_form_progr<hr>";
            for ($form_progr = 1; $form_progr <= $num_form_progr; $form_progr++) {
                foreach ($this->fields as $i => $val) {
                    if (isset($val['TYPE']) && $val['TYPE'] != '') $field_type = "field_{$val['TYPE']}";
                    else $field_type = "field";
                    include_once "{$field_type}.inc";
                    $field_obj = new $field_type($this, $i);
                    $field_obj->attributes['VAR'] .= "_PROGR_" . $form_progr;
                    $field_obj->make_close_html();
                    #echo "<br/>{$field_obj->attributes['VAR']} {$field_obj->attributes['TYPE']} - $colonne - $c -post ";
                    if ($colonne == $c) {
                        $this->body .= "</tr><tr>";
                        $c = 0;
                    }
                    #echo $c;
                    if ($field_obj->attributes['TYPE'] != 'hidden' && $field_obj->attributes['TYPE'] != '') {
                        if ($field_obj->attributes['COLS'] == '') $c++;
                        else {
                            $c += $field_obj->attributes['COLS'];

                        }

                    }
                    if ($field_obj->attributes['TYPE'] != 'hidden') $this->body .= $field_obj->html;
                    /*$this->salva_js.=$field_obj->salva_js;
					 $this->check_js.=$field_obj->check_js;
					 $this->invia_js.=$field_obj->invia_js;*/
                    if (!$field_obj->validata) $this->validata = $field_obj->validata;
                    $controlli .= $field_obj->controlli;
                }
            }
        } else {
            $campi_sql = "";
            foreach ($this->fields as $i => $val) {
                if (isset($val['TYPE']) && $val['TYPE'] != '') $field_type = "field_{$val['TYPE']}";
                else $field_type = "field";
                include_once "{$field_type}.inc";
                $field_obj = new $field_type($this, $i);
                if ($field_obj->attributes['VAR'] != '' && $field_obj->attributes['TB'] != 'no') {
                    $field_obj->insert_stmt();
                    if ($this->form['SHOW_CODE'] == '') {
                        $iter = 1;
                        foreach ($field_obj->field_stmt as $value) {
                            if ($iter > 1 && $value == $field_obj->attributes['VAR'] . 'RC') continue;
                            $curr_campo = "curr_table.{$value}, ";
                            $iter++;
                        }

                        if ($field_obj->attributes['EXCEL_QUERY'] == '') $campi_sql .= $curr_campo;
                        else $campi_sql .= "{$field_obj->attributes['EXCEL_QUERY']} as \"{$field_obj->attributes['VAR']}\", ";

                    } else {
                        $iter = 1;
                        foreach ($field_obj->field_stmt as $value) {
                            if ($iter > 1 && substr($value, strlen($value) - 5) == '_DTRC') continue;
                            $curr_campo = "curr_table.{$value}, ";
                            if ($field_obj->attributes['EXCEL_QUERY'] == '') $campi_sql .= $curr_campo;
                            else $campi_sql .= "{$field_obj->attributes['EXCEL_QUERY']} as \"{$field_obj->attributes['VAR']}\", ";
                            $iter++;
                        }

                    }
                    //					$campi_sql.="curr_table.{$field_obj->field_stmt[0]}, ";
                }

            }
            $campi_sql = rtrim($campi_sql, ", ");
            if ($this->form['DB_FILE'] == '') {

                //prendo solo le schede chiuse
                if ($evenif_open == false) {
                    $fine_condition = "AND coor.fine=1";
                } //prendo anche le schede aperte (fine = null)
                else {
                    $fine_condition = "";
                }

                $excel_str = "select $campi_sql from {$this->form['TABLE']} curr_table, " . $GLOBALS['service'] . "_coordinate coor 
				where coor.{$this->PK_SERVICE}=curr_table.{$this->PK_SERVICE} and coor.progr=curr_table.progr 
				and coor.visitnum=curr_table.visitnum and coor.visitnum_progr=curr_table.visitnum_progr and coor.esam=curr_table.esam " . $fine_condition;

                //possibilita' di aggiungere clausole WHERE
                if (!is_null($param_where) || $param_where != "") {
                    $excel_str .= " AND " . $param_where;
                }

                $excel_sql = new query($conn);
            } else {
                $conn2 = new dbconn(null, null, null, $this->form['DB_FILE']);
                $excel_str = "select $campi_sql from {$this->form['PREFIX']}{$this->form['TABLE']} curr_table";

                //possibilita' di aggiungere clausole WHERE
                if (!is_null($param_where) || $param_where != "") {
                    $excel_str .= " WHERE " . $param_where;
                }

                $excel_sql = new query($conn2);
            }
            //$excel_sql->set_sql($excel_str);
            $excel_sql->exec($excel_str, $bind_where);//non richiede binding per forza: di norma i paramentri sono calcolati funzionalmente
            //			echo $excel_str;
            //						die();
            if ($excel_sql->numcols > 248) {
                //				$excel=$excel_sql->tb_res_r();

                //echo "<hr>".$excel_sql->numcols;
                //echo " -- ".$this->form['FNAME']."<hr>";
            } else $excel = $excel_sql->tb_res();
            //						echo $excel;
            //						die();
            foreach ($this->fields as $i => $val) {
                if (isset($val['TYPE']) && $val['TYPE'] != '') $field_type = "field_{$val['TYPE']}";
                else $field_type = "field";
                include_once "{$field_type}.inc";
                $field_obj = new $field_type($this, $i);
                $field_obj->make_close_html();
                #echo "<br/>{$field_obj->attributes['VAR']} {$field_obj->attributes['TYPE']} - $colonne - $c -post ";
                if ($colonne == $c) {
                    $this->body .= "</tr><tr>";
                    //echo "qui";
                    $c = 0;
                }
                #echo $c;
                if ($field_obj->attributes['TYPE'] != 'hidden' && $field_obj->attributes['TYPE'] != '') {
                    if ($field_obj->attributes['COLS'] == '') $c++;
                    else {
                        $c += $field_obj->attributes['COLS'];

                    }

                }
                //				if ($field_obj->attributes['TYPE']!='hidden') $this->body.=$field_obj->html;
                $testo = preg_replace("'<[\/\!]*?[^<>]*?>'si", "", $field_obj->testo);

                if ($field_obj->attributes['VAR'] != '' && $val['TYPE'] != 'text' && $val['TYPE'] != 'hidden' && $testo != '' && $this->form['ADD_QUESTIONS'] != '') {
                    if ($field_obj->attributes['EXCEL_NAME'] == '') $excel = str_replace("<th>{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['VAR']}</font> <br> {$testo}</th>", $excel);
                    else $excel = str_replace("<th>{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['EXCEL_NAME']}</font> <br> {$testo}</th>", $excel);
                    if ($field_obj->attributes['EXCEL_NAME'] == '') $excel = str_replace("<th>D_{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['VAR']}</font> <br> {$testo}</th>", $excel);
                    else $excel = str_replace("<th>D_{$field_obj->attributes['VAR']}</th>", "<th><font color=red>{$field_obj->attributes['EXCEL_NAME']}</font> <br> {$testo}</th>", $excel);
                }
                /*$this->salva_js.=$field_obj->salva_js;
				 $this->check_js.=$field_obj->check_js;
				 $this->invia_js.=$field_obj->invia_js;*/
                if (!$field_obj->validata) $this->validata = $field_obj->validata;
                $controlli .= $field_obj->controlli;
            }
        }
        //		echo $excel_sql->numcols;
        //		die();

        //$this->body.="</table>
        //  <!--FINE CAMPI-->
        //  ";
        include_once("excel.inc");
        $conversion = new excel_converter($excel);
        $file = $conversion->convert($excel);
        return $file;
    }

    function validate_form()
    {
        $force_open = null;
        $field_obj = null;
        $equery = null;
        $note_eq = null;
        $testo_rev = null;
        $cf_end = null;
        $jsAccept = null;
        $jsReject = null;
        $function_accept = null;
        $function_reject = null;
        $controlli = null;
        $eqFunction = null;

        $in = $this->session_vars;
        $conn = $this->conn;
        $inputval = $this->tb_vals;
        $service = $this->service;
        $config_service = $this->config_service;
        $template_form_html = '';
        if ($this->xmr) {
            if ($in [$config_service ['PK_SERVICE']] != 'next') {
                if (isset ($in ['VISITNUM']) && isset ($in ['ESAM'])) {
                    $sql_query = "select visitclose from {$service}_COORDINATE where VISITNUM={$in['VISITNUM']} and ESAM={$in['ESAM']} and VISITNUM_PROGR={$in['VISITNUM_PROGR']} and {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
                    $sql = new query ($conn);
                    $sql->set_sql($sql_query);
                    $sql->exec();
                    $sql->get_row();
                    if ($sql->row ['VISITCLOSE'] == 1 && $in ['USER_TIP'] == 'DE' && !$force_open) {
                        error_page($in ['remote_userid'], mlOut("System.form.visit_closed", $this->testo("visitIsClosed")), "");
                    }
                }
            }
        }
        $_GET['VISITNUM_PROGR'] -= 0;
        $sql_query = "select * from {$this->service}_eqfield where
        nvl(statofield,0)=2 and
        esam={$_GET['ESAM']}
        and visitnum={$_GET['VISITNUM']}
        and visitnum_progr={$_GET['VISITNUM_PROGR']}
        and progr={$_GET['PROGR']}
        and {$this->PK_SERVICE}={$_GET[$this->PK_SERVICE]}
        ";
        $sql = new query($this->conn);
        $sql->exec($sql_query);
        while ($sql->get_row()) {
            $equery_spec[$sql->row['FIELD']]["VALUE"] = $sql->row['VALORE'];
            $equery_spec[$sql->row['FIELD']]["NOTE"] = $sql->row['NOTE_DE'];
            $equery_spec[$sql->row['FIELD']]["EQ_INT"] = $sql->row['EQ_INT'];
            $jsFor[$equery_spec[$field_obj->id]['EQ_INT']] = false;
        }
        $editing = true;
        if ($this->config_service['lang'] == "en") $lang = 1;
        else $lang = 0;
        //GENHD-42 rangecheck gestione alert e confirm con bootbox - vmazzeo 23.02.2015
        $this->salva_js = "
        function salva_f(show_bootbox){
        cf();
        if (show_bootbox==undefined) show_bootbox=true;
        f=document.forms[0];
        el=f.elements;
        specifiche='A=ON&L=$lang&F=0';
        c1='';
        ";
        //GENHD-42 rangecheck gestione alert e confirm con bootbox - vmazzeo 23.02.2015
        $this->invia_js = "
        function invia_f(ajax,show_bootbox){
        cf();
        if (ajax==undefined) ajax=true;
		if (show_bootbox==undefined) show_bootbox=true;
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
        $colonne = $this->form ['COLS'];
        $sysdate = date("dmY");
        if (isset($_GET['link_to']) && $_GET['link_to'] != '') $this->form ['LINK_TO'] = $_GET['link_to'];
        if (isset($_GET['link_to_send']) && $_GET['link_to_send'] != '') $this->form ['LINK_TO_SEND'] = $_GET['link_to_send'];//<!--vmazzeo 24.20.2015 bugfix non veniva considerato il link_to_send all\'invio della scheda-->
        $this->percorso_agg = "&nbsp;&gt;&nbsp;<b>" . $this->form ['TITOLO'] . "</b>";
        if ($equery) {
            $sql_query = "select equery_int as EQUERY_INT from {$this->service}_eq where stato in (0,2) and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";
            $sql = new query($this->conn);
            if ($sql->get_row($sql_query)) $equery_int = $sql->row['EQUERY_INT'];
            else $equery_int = 0;
        }
        $this->body = $note_eq . '
                <form method="post" class="niceform" action="index.php" enctype="multipart/form-data"  onsubmit="return false;" onKeypress="if (event.keyCode==13) return false;">
                <input type="hidden" name="' . $this->form ['TABLE'] . '"/>
                        <input type="hidden" name="form" value="' . $in ['form'] . '"/>
                                <input type="hidden" name="link_to" value="' . $this->form ['LINK_TO'] . '"/>
                                <input type="hidden" name="link_to_send" value="' . $this->form ['LINK_TO_SEND'] . '"/><!--vmazzeo 24.02.2015 bugfix non veniva considerato il link_to_send all\'invio della scheda-->
                                <input type="hidden" name="REALTIME_EQUERIES"/>
                                        <table align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
                                        <tbody>
                                        <tr>
                                        <td>
                                     ';

        $width = 100 / ($colonne * 2);
        if ($this->form ['TEMPLATE'] != '' && $in ['genera_template_html'] != "si")
            $template = file_get_contents("xml/{$this->form['TEMPLATE']}");
        else {
            $this->body .= '
                    <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
                    <!-- CAMPI -->' . $testo_rev;
            $template_form_html = '
                    <table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
                    <!-- CAMPI -->';
            $template = '';
            $this->body .= "</tr>";
            $template_form_html .= "</tr>";

        }

        $c = 0;
        $condition_array = array();
        foreach ($this->fields as $i => $val) {
            if ($val ['CONDITION'] != '')
                $condition_array [count($condition_array)] = $val ['CONDITION'];
        }
        $condition_array = array_unique($condition_array);
        if ($equery) {

            $_GET['VISITNUM_PROGR'] -= 0;

            $sql_query = "select * from {$this->service}_eqfield where
            --eq_int=$equery_int and
            esam={$_GET['ESAM']}
            and visitnum={$_GET['VISITNUM']}
            and visitnum_progr={$_GET['VISITNUM_PROGR']}
            and progr={$_GET['PROGR']}
            and {$this->PK_SERVICE}={$_GET[$this->PK_SERVICE]}
            and statofield=2
            ";

            $sql->exec($sql_query);

            foreach ($this->tb_vals as $k => $v) $this->old_values[$k] = $v;
            while ($sql->get_row()) {
                $this->tb_vals[$sql->row['FIELD']] = $sql->row['VALORE'];
            }


        }
        foreach ($this->fields as $i => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";

            //          if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
            //              include_once $this->config_service['field_lib'] . $field_type . ".inc";
            //          } else
            //          include_once "{$field_type}.inc";
            /**
             *  Modifica 08/09/2011
             * Carico prima i campi modificati per servizio se esistono
             * M. Verrocchio
             **/
            if (!class_exists($field_type)) {
                if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                    include_once $this->config_service['field_lib'] . $field_type . ".inc";
                } elseif (file_exists($_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc")) {
                    include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/{$field_type}.inc";
                } else {
                    include_once $_SERVER['DOCUMENT_ROOT'] . "/../libs/xCRF/fields/{$field_type}.inc";
                }
            }
            $field_obj = new $field_type ($this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            if (isset($condition_array) && is_array($condition_array)) foreach ($condition_array as $key => $val) {
                if ($val == $field_obj->id)
                    $field_obj->attributes ['CALL_CF'] = "yes";
            }
            if ($inputval [$this->form ['READONLY']] == 1 && $inputval [$field_obj->id] != '') {

                if ($field_obj->id != $this->form ['READONLY_COMM']) {

                    $field_obj->attributes ['DISABLED'] = 'yes';
                }
            }
            //$field_obj->attributes['DISABLED']=yes;
            if ($field_obj->id != '') {
                if ($field_obj->attributes['TYPE'] == "checkbox" || $field_obj->attributes['TYPE'] == "checkbox_hyper") {
                    $cf_end .= "
                    //Disabilitazione campo {$field_obj->id} di tipo {$field_obj->attributes['TYPE']} - 
                    ";
                    foreach ($field_obj->values as $k => $v) {
                        $cf_end .= "
                        document.forms[0].{$k}.disabled=true";
                    }
                } else {
                    $cf_end .= "
                    //Disabilitazione campo {$field_obj->id} di tipo {$field_obj->attributes['TYPE']} -
                    if (document.forms[0].{$field_obj->id}){
                    if (document.forms[0].{$field_obj->id}.type!='hidden') document.forms[0].{$field_obj->id}.disabled=true;
                    if (document.forms[0].{$field_obj->id} && document.forms[0].{$field_obj->id}[0] && document.forms[0].{$field_obj->id}[0].type=='radio'){
                    for (i=0;i<document.forms[0].{$field_obj->id}.length;i++) document.forms[0].{$field_obj->id}[i].disabled=true;
                }
                    ";
                    if (preg_match("/ora/", $field_obj->attributes['TYPE'])) {
                        $cf_end .= "
                            
                if (document.forms[0].{$field_obj->id}_H){
                    document.forms[0].{$field_obj->id}_H.disabled=true;
                    document.forms[0].{$field_obj->id}_M.disabled=true;
                }
                                ";
                    }
                    if (preg_match("/dat/", $field_obj->attributes['TYPE'])) {
                        $cf_end .= "
                if (document.forms[0].{$field_obj->id}D && document.forms[0].{$field_obj->id}M && document.forms[0].{$field_obj->id}Y){
                document.forms[0].{$field_obj->id}D.disabled=true;
                document.forms[0].{$field_obj->id}M.disabled=true;
                document.forms[0].{$field_obj->id}Y.disabled=true;
                }
                                
                        ";
                    }

                    $cf_end .= "
                }
                ";
                }
            }
            $fieldQuery = false;
            if (isset($equery_spec[$field_obj->id])) {
                $fieldQuery = true;
                $old_value = $this->tb_vals[$field_obj->id];
                $old_valueRC = $this->tb_vals[$field_obj->id . "RC"];
                $new_value = $equery_spec[$field_obj->id]['VALUE'];
                $equery_spec[$field_obj->id]['OLD_VALUE'] = $this->tb_vals[$field_obj->id];
                $eq_int = $equery_spec[$field_obj->id]['EQ_INT'];

                if ($field_type == 'field_date_hyper' || $field_type == 'field_data_hyper' || $field_type == 'field_date_hyper_day') {
                    $rcvalue = $equery_spec[$field_obj->id . "RC"]['VALUE'];
                    $day = substr($new_value, 0, 2);
                    if (substr($rcvalue, 0, 2) != 'OK') $day = substr($rcvalue, 0, 2);
                    $month = substr($new_value, 2, 2);
                    if (substr($rcvalue, 2, 2) != 'OK') $month = substr($rcvalue, 2, 2);
                    $year = substr($new_value, 4, 4);
                    if (substr($rcvalue, 4, 2) != 'OK') $year = substr($rcvalue, 4, 2);
                    $valueStr = $day . "/" . $month . "/" . $year;

                    $old_day = substr($old_value, 0, 2);
                    if (substr($old_valueRC, 0, 2) != 'OK') $old_day = substr($old_valueRC, 0, 2);
                    $old_month = substr($old_value, 2, 2);
                    if (substr($old_valueRC, 2, 2) != 'OK') $old_month = substr($old_valueRC, 2, 2);
                    $old_year = substr($old_value, 4, 4);
                    if (substr($old_valueRC, 4, 2) != 'OK') $old_year = substr($old_valueRC, 4, 2);


                    $oldValueStr = $old_day . "/" . $old_month . "/" . $old_year;
                    if ($old_value == '')
                        $eqSpec = "Aggiunto valore: <b>$valueStr</b>";
                    elseif ($new_value == '')
                        $eqSpec = "Eliminato il valore: <b>$oldValueStr</b>";
                    else $eqSpec = " Valore originale <b>$oldValueStr</b> sostituito con <b>$valueStr</b>";
                } else {
                    if (isset($equery_spec["D_" . $field_obj->id]['VALUE'])) {
                        $oldValueStr = $this->tb_vals["D_" . $field_obj->id];
                        $valueStr = $equery_spec["D_" . $field_obj->id]['VALUE'];
                    } else {
                        $oldValueStr = $this->tb_vals[$field_obj->id];
                        $valueStr = $equery_spec[$field_obj->id]['VALUE'];
                    }
                    if ($field_type == "field_ora_hyper") {
                        $oldValueStr = substr($oldValueStr, 0, 2) . ":" . substr($oldValueStr, 2, 2);
                        $valueStr = substr($valueStr, 0, 2) . ":" . substr($valueStr, 2, 2);
                    }
                    if ($old_value == '')
                        $eqSpec = "Aggiunto valore: <b>$valueStr</b>";
                    elseif ($new_value == '')
                        $eqSpec = "Eliminato il valore: <b>$oldValueStr</b>";
                    else $eqSpec = "Valore originale <b>$oldValueStr</b> sostituito con <b>$valueStr</b>";

                }
                $equery_spec[$field_obj->id]['VALUE'] = preg_replace("/\\n/", "\\\\n", $equery_spec[$field_obj->id]['VALUE']);
                $equery_spec[$field_obj->id]['VALUE'] = preg_replace("/\\t/", "\\\\t", $equery_spec[$field_obj->id]['VALUE']);
                $equery_spec[$field_obj->id]['VALUE'] = preg_replace("/\\r/", "\\\\r", $equery_spec[$field_obj->id]['VALUE']);
                $equery_spec[$field_obj->id]['OLD_VALUE'] = preg_replace("/\\n/", "\\\\n", $equery_spec[$field_obj->id]['OLD_VALUE']);
                $equery_spec[$field_obj->id]['OLD_VALUE'] = preg_replace("/\\t/", "\\\\t", $equery_spec[$field_obj->id]['OLD_VALUE']);
                $equery_spec[$field_obj->id]['OLD_VALUE'] = preg_replace("/\\r/", "\\\\r", $equery_spec[$field_obj->id]['OLD_VALUE']);

                $equery_spec[$field_obj->id]['VALUE'] = preg_replace("/\'/", "\\'", $equery_spec[$field_obj->id]['VALUE']);
                $equery_spec[$field_obj->id]['OLD_VALUE'] = preg_replace("/\'/", "\\'", $equery_spec[$field_obj->id]['OLD_VALUE']);

                $jsAccept[$equery_spec[$field_obj->id]['EQ_INT']] .= "
                if (document.forms[0].{$field_obj->id}[0] && document.forms[0].{$field_obj->id}[0].type=='radio'){
                for (i=0;i<document.forms[0].{$field_obj->id}.length;i++){
                if (document.forms[0].{$field_obj->id}[i].value=='{$equery_spec[$field_obj->id]['VALUE']}')
                document.forms[0].{$field_obj->id}[i].checked=true;
                else document.forms[0].{$field_obj->id}[i].checked=false;
            }
            }else {
            document.forms[0].{$field_obj->id}.value='{$equery_spec[$field_obj->id]['VALUE']}';
            if (document.forms[0].{$field_obj->id}D){
            if ('{$equery_spec[$field_obj->id]['VALUE']}'.length==8){
            if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(0,2)=='OK') {document.forms[0].{$field_obj->id}D.value='{$equery_spec[$field_obj->id]['VALUE']}'.substr(0,2);}
            else if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(0,2)=='NA') {document.forms[0].{$field_obj->id}D.value='NA';}
            else if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(0,2)=='NK') {document.forms[0].{$field_obj->id}D.value='NK';}

            if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(2,2)=='OK') {document.forms[0].{$field_obj->id}M.options[parseInt('{$equery_spec[$field_obj->id]['VALUE']}'.substr(2,2),10)].selected=true;}
            else if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(2,2)=='NA') {document.forms[0].{$field_obj->id}M.value='-9911';}
            else if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(2,2)=='NK') {document.forms[0].{$field_obj->id}M.value='-9922';}

            if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(4,2)=='OK') {document.forms[0].{$field_obj->id}Y.value='{$equery_spec[$field_obj->id]['VALUE']}'.substr(4,4);}
            else if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(4,2)=='NA') {document.forms[0].{$field_obj->id}Y.value='NA';}
            else if ('{$equery_spec[$field_obj->id.'RC']['VALUE']}'.substr(4,2)=='NK') {document.forms[0].{$field_obj->id}Y.value='NK';}

            }
            else {
            document.forms[0].{$field_obj->id}D.value='';
            document.forms[0].{$field_obj->id}M.value='';
            document.forms[0].{$field_obj->id}Y.value='';
            }
            }
            if (document.forms[0].{$field_obj->id}_H){
                document.forms[0].{$field_obj->id}_H.value='{$equery_spec[$field_obj->id]['VALUE']}'.substr(0,2);   
                document.forms[0].{$field_obj->id}_M.value='{$equery_spec[$field_obj->id]['VALUE']}'.substr(2,2);
            }
            }
            ";
                $jsReject[$equery_spec[$field_obj->id]['EQ_INT']] .= "
                if (document.forms[0].{$field_obj->id}[0] && document.forms[0].{$field_obj->id}[0].type=='radio'){
                for (i=0;i<document.forms[0].{$field_obj->id}.length;i++){
                if (document.forms[0].{$field_obj->id}[i].value=='{$equery_spec[$field_obj->id]['OLD_VALUE']}')
                document.forms[0].{$field_obj->id}[i].checked=true;
                else document.forms[0].{$field_obj->id}[i].checked=false;
            }
            }else {
            document.forms[0].{$field_obj->id}.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}';
            if (document.forms[0].{$field_obj->id}D){
            if ('{$equery_spec[$field_obj->id]['OLD_VALUE']}'.length==8){
            //document.forms[0].{$field_obj->id}D.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(0,2);
            //document.forms[0].{$field_obj->id}M.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(2,2);
            //document.forms[0].{$field_obj->id}Y.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(4,4);
            if ('{$old_valueRC}'.substr(0,2)=='OK') {document.forms[0].{$field_obj->id}D.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(0,2)}
            else if ('{$old_valueRC}'.substr(0,2)=='NA') {document.forms[0].{$field_obj->id}D.value='NA';}
            else if ('{$old_valueRC}'.substr(0,2)=='NK') {document.forms[0].{$field_obj->id}D.value='NK';}

            if ('{$old_valueRC}'.substr(2,2)=='OK') {document.forms[0].{$field_obj->id}M.options[parseInt('{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(2,2),10)].selected=true;}
            else if ('{$old_valueRC}'.substr(2,2)=='NA') {document.forms[0].{$field_obj->id}M.value='-9911';}
            else if ('{$old_valueRC}'.substr(2,2)=='NK') {document.forms[0].{$field_obj->id}M.value='-9922';}

            if ('{$old_valueRC}'.substr(4,2)=='OK') {document.forms[0].{$field_obj->id}Y.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(4,4);}
            else if ('{$old_valueRC}'.substr(4,2)=='NA') {document.forms[0].{$field_obj->id}Y.value='NA';}
            else if ('{$old_valueRC}'.substr(4,2)=='NK') {document.forms[0].{$field_obj->id}Y.value='NK';}

                
                
            }
            else {
            document.forms[0].{$field_obj->id}D.value='';
            document.forms[0].{$field_obj->id}M.value='';
            document.forms[0].{$field_obj->id}Y.value='';
            }
            }
            if (document.forms[0].{$field_obj->id}_H){
                document.forms[0].{$field_obj->id}_H.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(0,2);   
                document.forms[0].{$field_obj->id}_M.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(2,2);
            }
            }
            ";
                /*
                 $js_add.="
                function accept_eq_{$equery_spec[$field_obj->id]['EQ_INT']}(){
                if (document.forms[0].{$field_obj->id}[0] && document.forms[0].{$field_obj->id}[0].type=='radio'){
                for (i=0;i<document.forms[0].{$field_obj->id}.length;i++){
                if (document.forms[0].{$field_obj->id}[i].value=='{$equery_spec[$field_obj->id]['VALUE']}')
                    document.forms[0].{$field_obj->id}[i].checked=true;
                else document.forms[0].{$field_obj->id}[i].checked=false;
                }
                }else {
                document.forms[0].{$field_obj->id}.value='{$equery_spec[$field_obj->id]['VALUE']}';
                if (document.forms[0].{$field_obj->id}D){
                if ('{$equery_spec[$field_obj->id]['VALUE']}'.length==8){
                document.forms[0].{$field_obj->id}D.value='{$equery_spec[$field_obj->id]['VALUE']}'.substr(0,2);
                document.forms[0].{$field_obj->id}M.value='{$equery_spec[$field_obj->id]['VALUE']}'.substr(2,2)-0;
                document.forms[0].{$field_obj->id}Y.value='{$equery_spec[$field_obj->id]['VALUE']}'.substr(4,4);
                }else {
                document.forms[0].{$field_obj->id}D.value='';
                document.forms[0].{$field_obj->id}M.value='';
                document.forms[0].{$field_obj->id}Y.value='';
                }
                }
                }
                cf();
                }

                function reject_eq_{$equery_spec[$field_obj->id]['EQ_INT']}(){
                if (document.forms[0].{$field_obj->id}[0] && document.forms[0].{$field_obj->id}[0].type=='radio'){
                for (i=0;i<document.forms[0].{$field_obj->id}.length;i++){
                if (document.forms[0].{$field_obj->id}[i].value=='{$equery_spec[$field_obj->id]['OLD_VALUE']}')
                    document.forms[0].{$field_obj->id}[i].checked=true;
                else document.forms[0].{$field_obj->id}[i].checked=false;
                }
                }else {
                document.forms[0].{$field_obj->id}.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}';
                if (document.forms[0].{$field_obj->id}D){
                if ('{$equery_spec[$field_obj->id]['OLD_VALUE']}'.length==8){
                document.forms[0].{$field_obj->id}D.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(0,2);
                document.forms[0].{$field_obj->id}M.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(2,2)-0;
                document.forms[0].{$field_obj->id}Y.value='{$equery_spec[$field_obj->id]['OLD_VALUE']}'.substr(4,4);
                }
                else {
                document.forms[0].{$field_obj->id}D.value='';
                document.forms[0].{$field_obj->id}M.value='';
                document.forms[0].{$field_obj->id}Y.value='';
                }
                }
                }
                cf();
                }
                ";
                */
                //echo "<li>aggiunte funzioni accept e reject per {$equery_spec[$field_obj->id]['EQ_INT']}</li>";
                //echo "<li>{$field_obj->id} {$this->tb_vals[$field_obj->id]} -> {$equery_spec[$field_obj->id]['VALUE']}</li>";
            }

            if ($field_type == 'field_checkbox_hyper') {
                $fieldQuery = false;
                foreach ($field_obj->values as $key => $val) {
                    if (isset($equery_spec[$key])) {
                        $eq_int = $equery_spec[$key]['EQ_INT'];
                        $fieldQuery = true;
                    }

                }
                if ($fieldQuery) {
                    //                          $function_accept="
                    //                          function accept_eq_{$equery_spec[$field_obj->id]['EQ_INT']}(){";
                    //                          $function_reject="
                    //                          function reject_eq_{$equery_spec[$field_obj->id]['EQ_INT']}(){";
                    foreach ($field_obj->values as $key => $val) {
                        $query_spec[$field_obj->id]['EQ_INT'] = $eq_int;
                        $query_spec[$field_obj->id]['OLD_VALUES'][$key] = $this->tb_vals[$key] - 0;
                        $query_spec[$field_obj->id]['VALUES'][$key] = $equery_spec[$key]['VALUE'] - 0;
                        $old_value = $this->tb_vals[$key] - 0;
                        $new_value = $equery_spec[$key]['VALUE'] - 0;
                        if ($old_value == 1) $oldValues[] = $val;
                        if ($new_value == 1) $newValues[] = $val;
                        if ($new_value == 1) $function_accept .= "\ndocument.forms[0].{$key}.checked=true;";
                        else $function_accept .= "\ndocument.forms[0].{$key}.checked=false;";
                        if ($old_value == 1) $function_reject .= "\ndocument.forms[0].{$key}.checked=true;";
                        else $function_reject .= "\ndocument.forms[0].{$key}.checked=false;";
                    }
                    $valueStr = '';
                    foreach ($newValues as $key => $val) $valueStr .= "<br/>$val";
                    $oldValueStr .= '';
                    foreach ($oldValues as $key => $val) $oldValueStr .= "<br/>$val";
                    $valueStr = preg_replace("/^<br\/>/", "", $valueStr);
                    $oldValueStr = preg_replace("/^<br\/>/", "", $oldValueStr);
                    /*
                     $function_accept.="
                    cf();
                    }
                    ";
                    $function_reject.="
                    cf();
                    }
                    ";
                    $js_add.=$function_accept."\n\n".$function_reject;
                    */
                    $jsAccept[$equery_spec[$field_obj->id]['EQ_INT']] = $function_accept;
                    $jsReject[$equery_spec[$field_obj->id]['EQ_INT']] = $function_reject;
                    //echo "<li>aggiunte funzioni accept e reject per {$equery_spec[$field_obj->id]['EQ_INT']}</li>";

                }
            }
            if ($fieldQuery) {
                if ($oldValueStr == '' || $oldValueStr == '//') $oldValueStr = "n.d.";
                if ($valueStr == '' || $valueStr == '//') $valueStr = "n.d.";
                if (!isset($alreadyWritten[$equery_spec[$field_obj->id]['EQ_INT']]))
                    if (strtolower($this->config_service['lang']) == 'it') {
                        $eqSpec = "<table border=1 cellpadding=0 cellspacing=0 align=right>
                    <tr>
							<td colspan=3 style='color:red'>Modifica pendente</td>
                    </tr>
                    <tr>
							<td colspan=2>Valore Orignale</td>
							<td>Valore Modificato</td>
                    </tr>
                    <tr>
                    <td valign=top><b>$oldValueStr</b></td>
                    <td align=center><b>-&gt;</b></td>
                    <td valign=top><b>$valueStr<b></td>
                    </tr>
                    <tr>
							<td colspan=1 style='color:red'>Nota</td>
                    <td colspan=2>{$equery_spec[$field_obj->id]['NOTE']}</td>
                    </tr>
                    <tr>
                    <td>
							<input type='radio' value='1' name='EQ_{$equery_spec[$field_obj->id]['EQ_INT']}' onclick=\"accept_eq_{$equery_spec[$field_obj->id]['EQ_INT']}();\">Approva
                    </td>
                    <td colspan=2>
                    <input type='radio' value='2' checked name='EQ_{$equery_spec[$field_obj->id]['EQ_INT']}'
							onclick=\"reject_eq_{$equery_spec[$field_obj->id]['EQ_INT']}();\">Rifiuta
                    </td>
                    <!--
                    <td>
                    <input type='radio' value='0' checked name='EQ_{$equery_spec[$field_obj->id]['EQ_INT']}'
                    onclick=\"reject_eq_{$equery_spec[$field_obj->id]['EQ_INT']}()\"
                    \";>Rimanda
                    </td>
                    -->
                    </tr>
                    </table>
                    ";
                    } else {
                        $eqSpec = "<table border=1 cellpadding=0 cellspacing=0 align=right>
                    <tr>
							<td colspan=3 style='color:red'>Pending change</td>
                    </tr>
                    <tr>
							<td colspan=2>Original value</td>
							<td>Modified Value</td>
                    </tr>
                    <tr>
                    <td valign=top><b>$oldValueStr</b></td>
                    <td align=center><b>-&gt;</b></td>
                    <td valign=top><b>$valueStr<b></td>
                    </tr>
                    <tr>
							<td colspan=1 style='color:red'>Note</td>
                    <td colspan=2>{$equery_spec[$field_obj->id]['NOTE']}</td>
                    </tr>
                    <tr>
                    <td>
							<input type='radio' value='1' name='EQ_{$equery_spec[$field_obj->id]['EQ_INT']}' onclick=\"accept_eq_{$equery_spec[$field_obj->id]['EQ_INT']}();\">Approve
                    </td>
                    <td colspan=2>
                    <input type='radio' value='2' checked name='EQ_{$equery_spec[$field_obj->id]['EQ_INT']}'
							onclick=\"reject_eq_{$equery_spec[$field_obj->id]['EQ_INT']}();\">Refuse
                    </td>
                    <!--
                    <td>
                    <input type='radio' value='0' checked name='EQ_{$equery_spec[$field_obj->id]['EQ_INT']}'
                    onclick=\"reject_eq_{$equery_spec[$field_obj->id]['EQ_INT']}()\"
                    \";>Rimanda
                    </td>
                    -->
                    </tr>
                    </table>
                    ";
                    }
                $alreadyWritten[$equery_spec[$field_obj->id]['EQ_INT']] = true;
                //$field_obj->testo="<table border=0 cellpadding=0 cellspacing=0><tr><td valign=top>".$field_obj->testo;
                $field_obj->attributes['DEF'] .= "<br/>" . $eqSpec;
            }
            $field_obj->make_open_html();
            if ($template == '') {
                if ($field_obj->attributes ['HIDE'] == 'yes') {
                    if (isset ($field_obj->attributes ['NAME']) && $field_obj->attributes ['NAME'] != '') {
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
                        $c++;
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
                $template = str_replace("<<{$field_obj->id}>>", $field_obj->input_field, $template);
                $template = str_replace("<<TESTO {$field_obj->id}>>", $field_obj->input_txt, $template);
            }

            $this->salva_js .= $field_obj->salva_js;
            $this->check_js .= $field_obj->check_js;
            $this->invia_js .= $field_obj->invia_js;
            if (!$field_obj->validata)
                $this->validata = $field_obj->validata;
            $controlli .= $field_obj->controlli;
        }
        $js_function_on_send = $this->form ['JS_FUNCTION'];
        if ($this->form ['JS_ONSAVE'] == "yes")
            $js_function_on_save = $this->form ['JS_FUNCTION'];
        else
            $js_function_on_save = $this->form ['JS_ONSAVE'];
        $js_function_on_load = $this->form ['LOAD'];
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
            die ($template_form_html);
        }
        $this->onload .= $js_function_on_load;
        $this->onload .= 'cf()';
        $this->check_js .= '
                ' . $cf_end . '
    }';
        $this->salva_js .= '
                rc=contr(c1,specifiche);
                    if (rc) {return false;}
                ' . $controlli . '
                        if (!rc){
                                var jscustomfuncres = function(){return true;};
					    ';
        if ($js_function_on_save) {
            if (strpos(strtolower($js_function_on_save), "return") === false) {
                //Non ho alcun return, meglio che lo imposti io d'ufficio.
                $js_function_on_save = trim($js_function_on_save);
                $js_function_on_save = trim($js_function_on_save, ";");
                $js_function_on_save = "return (" . $js_function_on_save . ");";
            }
            $this->salva_js .= 'jscustomfuncres = function(){' . $js_function_on_save . '};';

        }
        $this->salva_js .= '
        						if (!jscustomfuncres()) {return false;}
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
        foreach ($jsAccept as $key => $val) {
            $eqFunction .= "
            function accept_eq_{$key}(){
            $val
            cf();
        }
        ";
            $eqFunction .= "
            function reject_eq_{$key}(){
            {$jsReject[$key]}
            cf();
        }
        ";

        }
        $this->invia_js .= '
                rc=contr(c1,specifiche);
                if (rc) {return false;}
                ' . $controlli . '
                        if (!rc){
                    var jscustomfuncres = function(){return true;};
                ';
        if ($js_function_on_send) {
            if (strpos(strtolower($js_function_on_send), "return") === false) {
                //Non ho alcun return, meglio che lo imposti io d'ufficio.
                $js_function_on_send = trim($js_function_on_send);
                $js_function_on_send = trim($js_function_on_send, ";");
                $js_function_on_send = "return (" . $js_function_on_send . ");";
            }
            $this->invia_js .= 'jscustomfuncres = function(){' . $js_function_on_send . '};';

        }
        $this->invia_js .= '
                    if (!jscustomfuncres()) {return false;}
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
    }
                    ' . $eqFunction;
        if ($template == '')
            $this->body .= '</table><p align=center>';
        else
            $this->body .= $template . "<p align=center>";
        if (isset ($in ['eform']) && $in ['USER_TIP'] != 'DM')
            $this->body .= '
                    <input type="submit" value="Vai alla form" name="equery" onclick="window.location.href=\'index.php?equery&amp;VISITNUM=\'+document.forms[0].VISITNUM.value+\'&amp;ESAM=\'+document.forms[0].VISITNUM.value+\'&amp;{$this->PK_SERVICE}=\'+document.forms[0].' . $this->PK_SERVICE . '.value+\'&amp;CENTER=\'+document.forms[0].CENTER.value+\'&amp;QUESTION=\'+document.forms[0].QUESTION.value+\'&amp;PROGR=\'+document.forms[0].PROGR.value;"/>
              ';
        if ($equery) {

            if (strtolower($this->config_service['lang']) == 'it') {
                $integra_button_text = "Integra Scheda";
                $eq_note_msg = "eQuery, commento generale:";
                $msg_generale_obbl = "Commento generale obbligatorio per le eQuery";
                $msg_field_obbl = "Commento al campo obbligatorio per le eQuery";
            } else {
                $integra_button_text = "Integrate Form";
                $eq_note_msg = "eQuery general comment:";
                $msg_generale_obbl = "General comment is necessary for eQuery";
                $msg_field_obbl = "Field comment is necessary for eQuery";
            }
            // Textarea per il DE, nel caso voglia fare un eQ:
            if (isset($_GET['ABILITA_EQ_DE'])) {
                // Nella check_eqfield controllo prima che almeno una textarea per campo sia stata aperta, altrimenti messaggio di alert
                // Successivamente controllo che tali textarea sia compilate altrimenti messaggi odi alert.

                $this->body .= '<script>
                        function check_eqfield_de(){
                        var el;
                        var f;
                        var result;
                        var check;
                        var espressione = /EQAREADE_/;
                        f=document.forms[0];
                        el=f.elements;
                        result = true;
                        check = false;
                        for (i=0;i<el.length;i++) {
                        if( espressione.test(el[i].name) && el[i].style.display!=\'none\'){
                        check = true;
            }
            }
                        if(check==false){
                        alert(\'' . $msg_field_obbl . '\');
                                return false;
            }
                                for (i=0;i<el.length;i++) {
                                if(el[i].style.display!=\'none\' && el[i].value==\'\' && espressione.test(el[i].name) ){
                                alert(\'' . $msg_field_obbl . '\');
                                        return false;
            }
            }
                            return true;
            }
                                        </script>';
                $this->body .= '
                        <input type="hidden" value="' . $equery_int . '" name="EQUERY_INT">
                                <tr><br><td align=center><input type="submit" style="width:150px; height:50px; cursor:pointer; border:1px outset #0000FF" value="' . $integra_button_text . '" name="salva" onclick="if(!check_eqfield_de()){return false; }else{invia_f();}"/></td></tr>';


            }
            // Fine Textarea per il DE, nel caso voglia fare un eQ:

            $exclude_send_buttons = true;
        }

        /**
         * gestione DBLOCK
         * vmazzeo luglio 2013
         *
         * DOVREMMO INSERIRE A QUESTO LIVELLO IL CONTROLLO SUL DB LOCK PER IL SAVE/SEND
         * ma in base alla gestione delle equery per questo studio (in cui il dm le approva tramite send della form)
         * il dm deve poter sempre accettare o rifiutare query anche se c' il DBLOCK (sia per il send che per le equery)
         * (perch si assume che siano state generate prima del blocco)
         */
        $lock_send_buttons = false;
        $this->body .= "</div>";
        if (!$exclude_send_buttons && !$lock_send_buttons) {
            if ($this->buttons ['SALVA'] && (($in ['USER_TIP'] != 'DM' && $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR'] != $this->session_vars['USER_PROFILE']) || isset ($in ['eform']))) {

                if (isset($this->config_service['Mobile'])) {
                    $this->body .= '
                            <button type="submit" class="submitBtn" value="' . $this->buttons ['SALVA'] . '" name="salva" onclick="salva_f();"/><span>' . $this->buttons ['SALVA'] . '</span></button>';
                } else {
                    $this->body .= '
                            <input type="submit" value="' . $this->buttons ['SALVA'] . ' " name="salva" onclick="salva_f();"/>';
                }

            }
            if ($this->buttons ['SUBMIT'] != '')
                $this->body .= '

                        <input type="submit" value="' . $this->buttons ['SUBMIT'] . '" onclick="submit();"/>';

            if ($this->buttons ['INVIA'] && ($in ['USER_TIP'] != 'DM' && $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR'] != $this->session_vars['USER_PROFILE']) || (isset ($in ['FORM']) || isset ($in ['SEARCH']))) {
                if (isset($this->config_service['Mobile'])) {
                    $this->body .= '
                      <button type="submit" class="submitBtn" value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/><span>' . $this->buttons ['INVIA'] . '</span></button>';
                } else {
                    $this->body .= '
                            <input type="submit"  value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/>';
                }

            }

            if (($this->session_vars['USER_TIP'] == "DM" || $this->config_service['eQuerySpec']['Integrazione']['VALIDATOR'] == $this->session_vars['USER_PROFILE']) && !isset ($in ['FORM']) && !isset ($in ['SEARCH'])) {
                if ($this->config_service['lang'] == "en") {
                    $reason = "Reason for change:";
                    $send = "Send";
                    $opt1 = "Obvious correction";
                    $opt2 = "Data entry error";
                    $opt3 = "Split/collapse of entry";
                    $opt4 = "Thesaurus codification";
                    $opt5 = "Investigator comment";
                    $alert_msg = "WARNING!!! It\\'s necessary to choose a reason for the revision";
                } else {
                    $reason = "Motivo della modifica:";
                    $send = "Procedi";
                    $opt1 = "Correzione ovvia";
                    $opt2 = "Errore inserimento dati";
                    $opt3 = "Scissione/collasso nell'inserimento";
                    $opt4 = "Codifica del dizionario";
                    $opt5 = "Commento dell'investigatore";
                    $alert_msg = "ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica";
                }
                $this->body .= "<input type='hidden' value='1' name='eQueryApproval'>";
                $this->body .= "
                <input type=\"submit\" value=\"$send\" name=\"invia_dm\" onclick=\"
                if (document.forms[0].eQueryApproval.value!='') invia_f();
                else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;}
                \"/>
                ";
            }
            if ($this->buttons ['ANNULLA'])
                $this->body .= '
                        <input type="reset" value="' . $this->buttons ['ANNULLA'] . '" name="annulla" />';
        }
        $this->body .= '</p></table>';

        if (isset($_GET['ABILITA_EQ_DE']) && $_GET['ABILITA_EQ_DE'] != '') {
            $this->body .= $this->riassunto_eq_per_esam($in [$this->PK_SERVICE], $in ['ESAM'], $in ['PROGR'], $in ['VISITNUM'], $in ['VISITNUM_PROGR']);
        }


        if (!$exclude_send_buttons) $this->body .= '</form>';
        $config_service = $this->config_service;
        if ($config_service ['PK_SERVICE'] == '')
            $this->PK_SERVICE = $this->config_service['PK_SERVICE'];
        else
            $this->PK_SERVICE = $config_service ['PK_SERVICE'];
        global $vlist;
        if (!isset($in['SEARCH']) && $in [$this->PK_SERVICE] != '' && !isset ($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN']) && !$exclude_send_buttons) {
            //commento back vmazzeo 06.06.2014
            $this->body .= '
            <div class="hide"><p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE] . '" onclick="history.back(); return false;">&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p></div>';
        }

        $href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";
        $this->body = preg_replace("/#HREF#/", $href_alternativo, $this->body);

    }

    /**
     * Genera la lista delle eQuery presenti sulla form
     *
     * @param array $codpat
     * @param array $esam
     * @param array $progr
     * @param array $visitnum
     * @param array $visitnum_progr
     *
     * @return $report
     *
     */
    function riassunto_eq_per_esam($codpat, $esam, $progr, $visitnum, $visitnum_progr)
    {
        $conn = $this->conn;
        $service = $this->service;
        $sql = new query($conn);
        $report = "</div>"; //TODO: Bruttissimo! Chiudo div delle form che non viene chiuso prima??
        if ($this->config_service['eQuery'] == 1 && $codpat != '') {
            $str_id = "select distinct eq_int from {$service}_eqfield where {$this->PK_SERVICE}={$codpat} and esam={$esam} and progr={$progr} and visitnum={$visitnum} and visitnum_progr={$visitnum_progr} order by eq_int";
            //	 echo $str_id;
            $sql->exec($str_id);
            //$report.="<p>&nbsp;</p>";
            $report .= "<div id=\"eqpanel_open_link\" style=\"margin: auto; width: 60%; padding:30px 5px 5px 5px; text-align:center;\"  ><a href=\"#\" onclick=\"$('#eqpanel_open_link').hide();$('#eqpanel_close_link').show();$('#riassuntoeq_container').show();return false;\" >" . mlOut("MESSAGE_EQUERY_HISTORY_OPEN", "Open EQuery Panel history") . "</a></div>";
            $report .= "<div id=\"eqpanel_close_link\" style=\"margin: auto; width: 60%; padding:30px 5px 5px 5px; text-align:center; display: none;\"  ><a href=\"#\" onclick=\"$('#eqpanel_close_link').hide();$('#eqpanel_open_link').show();$('#riassuntoeq_container').hide();return false;\" >" . mlOut("MESSAGE_EQUERY_HISTORY_CLOSE", "Close EQuery Panel history") . "</a></div>";
            while ($sql->get_row()) {
                //		echo "<br>";echo $sql->row['EQ_INT'];echo "<br>";
                $report .= '<div id="riassuntoeq_container" style="display:none;">';
                $report .= $this->riassunto_eq_per_id($sql->row['EQ_INT']);
                $report .= '</div>';
            }
        }
        return $report;
    }

    /**
     * Genera la lista delle eQuery presenti sul singolo campo della form considerata nel metodo riassunto_eq_per_esam.
     *
     * @param numeric $id
     *
     * @return HTML
     *
     */
    function riassunto_eq_per_id($id)
    {
        $conn = $this->conn;
        $service = $this->service;
        $sql = new query($conn);
        $str_main = "select * from {$service}_eq where equery_int={$id} ";
        $sql->get_row($str_main);
        $main_data = $sql->row;

        if ($this->config_service['lang'] == "en") {
            $txt_aperta = 'Opened';
            $txt_approvata = 'Resolved';
            $txt_chiusa = 'Closed';
            $txt_risposta = 'Answered';
            $txt_rifiutata = 'Not resolved';
            $txt_richiesta = 'User: ';
            $txt_sper = 'User: Investigator';
            $txt_indata = 'Date';
            $txt_general = 'General comment';
            $txt_nomecampo = 'Field name';
            $txt_nuovovalore = 'New value';
            $txt_vecchiovalore = 'Old value';
            $txt_stato = 'Status';
            $txt_dm_campo = 'eQuery';
            $txt_de_campo = 'Answer';
            $txt_nocommento = '';
        } else {
            $txt_aperta = 'Aperta';
            $txt_approvata = 'Risolta';
            $txt_chiusa = 'Chiusa';
            $txt_risposta = 'Risposta';
            $txt_rifiutata = 'Non risolta';
            $txt_richiesta = 'Utente: ';
            $txt_sper = 'Utente: Sperimentatore';
            $txt_indata = 'Data';
            $txt_general = 'Testo generale';
            $txt_nomecampo = 'Nome campo';
            $txt_nuovovalore = 'Nuovo valore';
            $txt_vecchiovalore = 'Vecchio valore';
            $txt_stato = 'Stato';
            $txt_dm_campo = 'eQuery';
            $txt_de_campo = 'Testo risposta';
            $txt_nocommento = '';
        }

        switch ($main_data['STATO']) {
            case '0':
                $stato = $txt_aperta;
                break;
            case '1':
                $stato = $txt_chiusa;
                break;
            case '2':
                $stato = $txt_risposta;
                break;
            case '3':
                $stato = $txt_rifiutata;
                break;
        }
        switch (substr($main_data['USERID_INS'], 0, 3)) {
            case '997':
                $richiedente = 'DM';

                break;
            case '996':
                $richiedente = 'CRA';

                break;
            default:
                $richiedente = 'DE';
                break;

        }
        //echo "<pre>";
        //print_r($main_data);
        //echo "</pre>";
        if ($main_data['RICH_DM'] == '') {
            $data_de = $main_data['INS_DT'];
        } else {
            $data_de = $main_data['CLOSE_DT'];
        }

        $data_de = $this->FormatDate($data_de);

        $str_all = "select * from {$service}_eqfield where eq_int={$id} ";
        $sql->exec($str_all);
        $all_field_data = array();
        while ($sql->get_row()) {
            //echo "precedente : "; print_R($all_field_data[$id]);
            //echo "corrente: ";print_r($sql->row);
            if ($all_field_data[$id]['FIELD'] == "D_" . $sql->row['FIELD']) {
                // Se già ho preso la decodifica è ok.
                continue;
            }
            $all_field_data[$id] = $sql->row;

        }
        //echo "Result: " ; print_r($all_field_data[$id]);
        $str_fields = "select * from {$service}_eqfield where eq_int={$id} ";
        $sql->exec($str_fields);
        $counter = 1;
        $richiesta_dm_cra = "";
        $note_dm_html = "";
        $note_de_html = "";
        $note_cl_html = "";
        $array_date = array();
        while ($sql->get_row()) {
            if ($counter % 2 == 1) {
                $odd_even = "odd";
            } else {
                $odd_even = "even";
            }
            $curr_field_data = $sql->row;

            switch ($curr_field_data['STATOFIELD']) {
                case '0':
                    $statofield = $txt_aperta;
                    break;
                case '1':
                    $statofield = $txt_approvata;
                    break;
                case '2':
                    $statofield = $txt_risposta;
                    break;
                case '3':
                    $statofield = $txt_rifiutata;
                    break;
            }
            if ($curr_field_data['NOTE'] != '') {
                $main_data['INS_DT'] = $this->FormatDate($main_data['INS_DT']);
                $note_dm_html = "<tr class='destra'><td colspan=3 >$txt_richiesta $richiedente ({$main_data['USERID_INS']})</td><td colspan=2>$txt_indata: {$this->FormatDate($main_data['INS_DT'])}</td></tr>";
                $note_dm_field = $curr_field_data['NOTE'];
                $note_dm_html .= "<tr class='eq_sum_field_{$odd_even}' ><td colspan=5 align=left>$txt_dm_campo: {$note_dm_field}</td></tr>";
            }
            if ($curr_field_data['NOTE_DE'] != '') {
                $note_de_html = "<tr class='destra'><td  colspan=3>$txt_sper</td><td colspan=2>$txt_indata: {$this->FormatDate($main_data['MOD_DT'])}<!--{$data_de}--></td></tr>";
                $note_de_field = $curr_field_data['NOTE_DE'];
                $note_de_html .= "<tr class='eq_sum_field_{$odd_even}' ><td colspan=5 align=left>$txt_de_campo: {$note_de_field}</td></tr>";
            }
            if ($main_data['CLOSE_DT'] != '') {
                $note_cl_html = "<tr class='destra'><td  colspan=3>$txt_richiesta Data Manager</td><td colspan=2>$txt_indata: {$this->FormatDate($main_data['CLOSE_DT'])}</td></tr>";
                $note_cl_field = "eQuery Closed";
                $note_cl_html .= "<tr class='eq_sum_field_{$odd_even}' ><td colspan=5 align=left>$txt_de_campo: {$note_cl_field}</td></tr>";
            }
            /**
             * Nel caso di campi di tipo ora  si vuole visualizzare solo il formato HHMM.
             */
//		 print_r($curr_field_data);
            foreach ($this->fields as $k => $v) {
//	 		print_r($v['TYPE']);
                if ($v['TYPE'] == "ora") {
                    if ($v['VAR'] . "_M" == $curr_field_data['FIELD'] || $v['VAR'] . "_H" == $curr_field_data['FIELD']) {
                        $curr_field_data['FIELD'] = "";
                    }
                }
                if ($v['TYPE'] == "date" || $v['TYPE'] == "date_cal" || $v['TYPE'] == "data" || $v['TYPE'] == "data_dropdown") {
                    //echo "Entro in data?";
                    if ($v['VAR'] == $curr_field_data['FIELD'] && $curr_field_data['FIELD'] != '') {
                        // In $v['VAR'] on è presente [NOMECAMPO]RC , quindi se sono qui è il [NOMECAMPO]
                        $sql2 = new query($conn);
                        $sql_date_rc = "select VALORE from {$service}_eqfield where eq_int={$id} and field='{$curr_field_data['FIELD']}RC'";
                        $sql2->get_row($sql_date_rc);
                        $date_rc = $sql2->row;
                        // Gestione NA e NK del date
                        if (substr($date_rc['VALORE'], 0, 2) != 'OK' && substr($date_rc['VALORE'], 0, 2) != '') {
                            $dd = substr($date_rc['VALORE'] . 'RC', 0, 2);
                        } else $dd = substr($curr_field_data['VALORE'], 0, 2);
                        if (substr($date_rc['VALORE'], 2, 2) != 'OK') {
                            $mm = substr($date_rc['VALORE'] . 'RC', 2, 2);

                        } else $mm = substr($curr_field_data['VALORE'], 2, 2);
                        if (substr($date_rc['VALORE'], 4, 2) != 'OK') {
                            $yyyy = substr($date_rc['VALORE'] . 'RC', 4, 2);

                        } else $yyyy = substr($curr_field_data['VALORE'], 4, 4);

                        $curr_field_data['VALORE'] = $dd . "/" . $mm . "/" . $yyyy;
//					print_r($dd.$mm.$yyyy);
                    }
                    /**
                     * Nel caso di campi date , non si deve vedere il record RC
                     */
                    if ($v['VAR'] . "RC" == $curr_field_data['FIELD']) {
                        $array_date[$curr_field_data['EQ_INT']][$curr_field_data['FIELD']] = $curr_field_data['VALORE'];
                        $curr_field_data['FIELD'] = "";
                    }
                }
            }

            /**
             * Nel caso di campi con decodifica si vuole visualizzare solo la decodifica (Si / No).
             */
            if ($all_field_data[$id]['FIELD'] == "D_" . $curr_field_data['FIELD'] || $curr_field_data['FIELD'] == "") {
                //echo "VADO A FINIRE QUA?";
                $richiesta_dm_cra .= "";
            } else {
                /**
                 * Inoltre il nome della colonna in banca dati deve essere quella del campo di codifica (es ASA e non D_ASA)
                 */
                //echo "OPPURE VADO A FINIRE QUI?";
                if (preg_match("/^D_/", $curr_field_data['FIELD'])) {
                    $curr_field_data['FIELD'] = preg_replace("/^D_/", "", $curr_field_data['FIELD']);
                }

                $richiesta_dm_cra .= "

                    $note_dm_html

                    $note_de_html

                    $note_cl_html

                    <tr class='eq_sum_field_{$odd_even}' ><td align=left>$txt_nomecampo: {$curr_field_data['FIELD']}</td><td align=left>$txt_vecchiovalore: {$curr_field_data['VALORE_OLD']}</td><td align=left>$txt_nuovovalore: {$curr_field_data['VALORE']}</td><td colspan=2 align=left>$txt_stato: {$statofield}</td></tr>
                    ";
                $counter++;
            }


        }


        $result = "<table align=\"center\" class=\"table table-striped table-bordered table-hover\" style=\"width: 60%;\"><tr class='titolo2' ><td colspan=5>eQuery ID: {$main_data['EQUERY_INT']} - $stato </td></tr>
	$richiesta_dm_cra

	</table>
	";


        return $result;
    }

    /**
     * Formattazione automatica della data
     *
     * @param string $date
     */
    function FormatDate($date)
    {
        if (strlen($date) == 8) {
            $data_gg = substr($date, 0, 2);
            $data_mm = substr($date, 2, 2);
            $data_yy = substr($date, 4, 4);
            $date = $data_gg . "/" . $data_mm . "/" . $data_yy;
        }
        return $date;
    }

    /**
     * Controlla tutti i campi sotto eQ per singolo campo presenti nella form e al paziente in visualizzazione.
     *
     * @param array $xml_form
     *
     * @return array
     */
    function FieldPendig($in = null)
    {

        $sql_check = "select * from {$this->service}_eqfield eqfield, {$this->service}_eq eq
				where eq.equery_int=eqfield.eq_int
				and statofield in (0,2)
				and eqfield.{$this->PK_SERVICE}={$_POST[$this->PK_SERVICE]}
				and esam={$_POST['ESAM']}
				and progr={$_POST['PROGR']}
				and VISITNUM={$_POST['VISITNUM']}
				and VISITNUM_PROGR={$_POST['VISITNUM_PROGR']}";

        $sql = new query ($this->conn);
        $sql->exec($sql_check);

        /**
         * Se eQ pending su un campo , valorizzo l'array:
         */
        while ($sql->get_row()) {
            $pending[$sql->row['FIELD']] = $sql->row;
        }

        /**[AC]Bisognerebbe gestire gli esami progressivi con questa : */
        /**$sql_check="select * from {$this->service}_eqfield eqfield, {$this->service}_eq eq
         * where eq.equery_int=eqfield.eq_int
         * and statofield in (0,2)
         * and eqfield.{$this->PK_SERVICE}={$_POST[$this->PK_SERVICE]}
         * and esam={$_POST['ESAM']}
         * and VISITNUM={$_POST['VISITNUM']}
         * and VISITNUM_PROGR={$_POST['VISITNUM_PROGR']}
         * and PROGR={$_POST['PROGR']}";
         */

        //Debug:
//		echo "FIELD PENDING:";echo "<br>";
//		print_r($pending);echo "<br>";
//		echo "Query in DB:";echo "<br>"; echo $sql_check;echo "<br>";
//		die();

        return $pending;
    }

    function Set_DDE_Difference($difference)
    {
        //      print_r($difference);
        $this->difference = $difference;

    }


}

/**
 * Classe prototipo della form legato all'XMR
 *
 * @package ViewsAndControllers
 */
class xml_form_prototype extends form_prototype
{

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
    function testo($testo)
    {
        //HOW TO
        /* Per utilizzare questa funzione chiamarla cosi nel codice:
		* $this->testo("PAROLACHIAVE")
		* e qui dentro definire per ogni lingua
		* $this->testi['PAROLACHIAVE']="Frase da far apparire";
		*/
        if (!isset($this->testi[$testo])) {
            if (strtolower($this->config_service['lang']) == 'it') {
                $this->testi['visitIsClosed'] = "Attenzione la visita risulta chiusa, non &egrave; quindi possibile inserire/modificare i dati";
            } else {
                $this->testi['visitIsClosed'] = "Attention this visit is closed, it's not possible to modify/insert data";
            }

        }
        return $this->testi[$testo];
    }


    /**
     * Controlla se la form  chiusa e recupera i dati da DB
     *
     */
    function closed_form($progr = null)
    {
        $ret = parent::closed_form($progr);
        global $inputval;
        $inputval = $this->tb_vals;
        return $ret;
    }

    /**
     * Costruisce il codice html della form in compilazione
     *
     */
    function open_form($force_open = false, $exclude_send_buttons = false, $equery = false, $preview = false)
    {
        parent::open_form($force_open, $exclude_send_buttons, $equery, $preview);
        global $percorso;
        $percorso .= $this->percorso_agg;
    }


    /**
     * Costruisce il codice html della form in visualizzazione
     *
     */
    function close_form($no_link_back = false, $equery = false)
    {
        parent::close_form($no_link_back, $equery);
        global $percorso;
        $percorso .= $this->percorso_agg;
    }


    /**
     *
     * Costruttore
     *
     *
     *
     */
    function xml_form_prototype($conn = null, $service = null, $config_service = null, $in = null, $dir_file = null)
    {
        if (!isset($config_service)) global $config_service;
        if (!isset($service)) global $service;
        if (!isset($in)) global $in;
        if (!isset($dir_file)) {
            global $dir;
            $dir_file = $dir . "/uploaded_file/";
        }
        if (!isset($conn)) global $conn;
        parent::form_prototype($conn, $service, $config_service, $in, $dir_file);
    }

    function query_tb($new_insert)
    {
        //mi porto dietro il valore assegnato al nuovo paziente (codpat o simili)
        $pk_serv_val = parent::query_tb($new_insert);
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
    function query_abilita()
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        $query = new query ($conn);
        $nq = 0;
        for ($en = 0; $en < count($this->enable); $en++) {
            if (isset ($in ['invia']) || $in ['INVIOCO'] == '1' || $this->enable [$en] ['ONSAVE'] != '') {
                #echo "<hr>Controllo abilitazioni";
                if ($in ['PROGR'] == '')
                    $in ['PROGR'] = 1;
                $vis_num = $this->enable [$en] ['VISITNUM'];
                $es_num = $this->enable [$en] ['NUMBER'];

                if ($this->enable [$en] ['PROGR'] != '')
                    $in ['PROGR'] = $this->enable [$en] ['PROGR'];
                $cond_var = $this->enable [$en] ['CONDITION_VAR'];
                $cond_val = $this->enable [$en] ['CONDITION_VALUE'];
                if ($cond_var == '' || ($cond_var != '' && $in [$cond_var] == $cond_val)) {
                    #echo "<hr>Controllo abilitazioni 1";
                    $config_service = $this->config_service;
                    unset($bind);
                    if ($config_service ['VISITNUM_PROGR'] == '1') {
                        if ($this->enable [$en] ['VISITNUM_PROGR'] != '')
                            $vis_progr = $this->enable [$en] ['VISITNUM_PROGR'];
                        else {
                            if (isset ($in ['VISITNUM_PROGR'])) {
                                $vis_progr = $in ['VISITNUM_PROGR'];
                            } else
                                $vis_progr = 0;
                        }
                        $agg_sql_insert_field = ",visitnum_progr";
                        $agg_sql_insert_value = ",$vis_progr";
                        $where_agg = " and visitnum_progr=:visitnum_progr";
                        $bind['VISITNUM_PROGR'] = $vis_progr;
                    }
                    $bind['VISITNUM'] = $vis_num;
                    $bind['ESAM'] = $es_num;
                    $bind['PROGR'] = $in ['PROGR'];
                    $bind['PK_SERVICE'] = $in [$this->PK_SERVICE];
                    if (strtolower($this->enable [$en] ['PROGR']) == 'next') {
                        $query_progr = "select max(progr) PROGR from " . $this->service . "_coordinate where visitnum=:visitnum and esam=:esam and {$this->PK_SERVICE}=:pk_service $where_agg";
                        $sql = new query ($conn);
                        //$sql->set_sql ( $query_progr );
                        $sql->exec($query_progr, $bind);//binded
                        $sql->get_row();
                        $in ['PROGR'] = $sql->row ['PROGR'] + 1;
                    }
                    $query_abil = "select * from " . $this->service . "_coordinate where visitnum=:visitnum and esam=:esam and progr=:progr and {$this->PK_SERVICE}=:pk_service $where_agg";
//					echo $query_abil."<br>";
                    //$query->set_sql ( $query_abil );

                    $query->exec($query_abil, $bind);//binded
                    if (!($query->numrows >= 1)) {
                        $query_ins_abil = "insert into " . $this->service . "_coordinate (visitnum $agg_sql_insert_field,esam,progr,{$this->PK_SERVICE}, abilitato, userid) values ('$vis_num' $agg_sql_insert_value ,'$es_num','" . $in ['PROGR'] . "','" . $in [$this->PK_SERVICE] . "','1', null)";
                        $this->query_enable [$nq] = $query_ins_abil;
                        $nq++;
                    }
                }
            }
        }
    }

    function XML_PRINT_($values)
    {
        $key = null;
        $out = null;
        foreach ($this->fields as $i => $val) {
            if (isset ($val ['TYPE']) && $val ['TYPE'] != '')
                $field_type = "field_{$val['TYPE']}";
            else
                $field_type = "field";

            if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'] . $field_type . ".inc")) {
                include_once $this->config_service['field_lib'] . $field_type . ".inc";
            } else
                include_once "{$field_type}.inc";
            $field_obj = new $field_type ($this, $key, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors);
            $out .= $field_obj->XML_PRINT_($values);
        }
        return $out;
    }

}

/**
 * Funzione make_js
 * @param String $testo Testo in input
 *
 */
function make_js($testo)
{
    global $config_service;
    $testo_js = preg_replace("/'/", "\'", $testo);
    $testo_js = preg_replace("!\n!m", "", $testo_js);
    $testo_js = str_replace("\r", "", $testo_js);
    //$testo_js = preg_replace ( "/<a(.*?)\/a>/m", "", $testo_js );
    $testo_js = preg_replace("/<(.*?)>/m", "", $testo_js);

    $testo_js = preg_replace("/&(.*?);/", "", $testo_js);
    if ($config_service['ammetti_parentesi_js'] == '') $testo_js = preg_replace("/\((.*?)\)/", "", $testo_js);
    $testo_js = preg_replace("/\?(.*)/", "", $testo_js);
    $testo_js = preg_replace("/\*/", "", $testo_js);
    $testo_js = ltrim($testo_js);
    $testo_js = rtrim($testo_js);
    return $testo_js;
}


?>
