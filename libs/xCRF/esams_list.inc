<?

/**
 * Classe xml_esams_list_prototype
 *
 * Gestisce la rappresentazione grafica delle schede dello studio
 * @package ViewsAndControllers
 */
class xml_esams_list_prototype
{

    var $titolo;
    var $visitnums;
    var $esams;
    var $enable_visit;
    var $group;
    var $links;
    var $html;
    var $page;
    var $xml;
    var $PK_SERVICE;
    var $tabs;
    var $visit_menu;
    var $config;
    var $testi;
    var $true_false;
    var $config_service;
    var $conn;
    var $session_vars;
    var $xml_dir;
    var $lang = 'it';
    var $integrazione;

    /**
     * Recupera i testi configurabili
     *
     * @param String $testo
     * @return String
     */
    function testo($testo)
    {
        if (!isset($this->testi[$testo])) {
            if ($this->lang == 'it') {
                $this->testi['Aggiungi'] = "Aggiungi";
                $this->testi['Elimina'] = "Elimina";
                $this->testi['Sei sicuro di voler eliminare'] = "Sei sicuro di voler eliminare";
                $this->testi['numero'] = "numero";
                $this->testi['inviato_corretto_da'] = "Inviato/Corretto da";
                $this->testi['data_invio'] = "Data&nbsp;d'invio";
                $this->testi['Aggiungi_nuova_visita'] = "Aggiungi nuova visita";
            } else {
                $this->testi['Aggiungi'] = "Add";
                $this->testi['Elimina'] = "Delete";
                $this->testi['Sei sicuro di voler eliminare'] = "Are you sure you want to delete";
                $this->testi['numero'] = "number";
                $this->testi['inviato_corretto_da'] = "Sent/Modified by";
                $this->testi['data_invio'] = "Sent&nbsp;date";
                $this->testi['Aggiungi_nuova_visita'] = "Add new visit";
            }
        }
        return $this->testi[$testo];
    }

    /**
     * Costruisce le configurazioni
     *
     */
    function configura()
    {
        if (isset($this->config_service['lang'])) $this->config['language'] = $this->config_service['lang'];
        if (!isset($this->config['language'])) $this->config['language'] = 'it';
        $this->testi['nuovo_inserimento'] = mlOut("System.New", "New");
        $this->true_false['configurato'] = true;
    }

    /**
     * Costruttore
     *
     * @param string $xml_file
     * @return xml_esams_list
     */
    function xml_esams_list_prototype($xml_file, $config_service = null, $session_vars = null, $conn = null, $xml_dir = null)
    {
        $en_idx = null;
        if (!isset($config_service)) global $config_service;
        $this->config_service = $config_service;
        if (!isset($session_vars)) {
            global $in;
            $session_vars = $in;
        }
        if (!isset($xml_dir)) global $xml_dir;
        $this->xml_dir = $xml_dir;
        $this->session_vars = $session_vars;
        if (!isset($conn)) global $conn;
        $this->conn = $conn;
        $this->configura();
        $this->PK_SERVICE = $this->config_service['PK_SERVICE'];
        $xml_parser = new my_xml_parser($xml_file);
        $this_node = new xml_node();
        $g = 0;
        for ($i = 0; $i < count($xml_parser->vals); $i++) {
            $this_node->xml_node_by_array($xml_parser->vals[$i]);
            if ($this_node->type != 'cdata') {
                if ($this_node->tag == 'VISIT_EXAM') if ($this_node->type == 'open' or $this_node->type == 'complete') {
                    $this->page = $this_node->attributes;
                }
                if ($this_node->tag == 'GROUP') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->group[$g] = $this_node->attributes;
                    }
                    if ($this_node->type == 'close') {
                        $g++;
                    }
                }

                if ($this_node->tag == 'VISIT') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $vis_num = $this_node->attributes['NUMBER'] + 0;
                        $this->group[$g]['VISIT'][$vis_num] = $vis_num;
                        $this->visitnums[$vis_num] = $this_node->attributes;
                    }
                }
                if ($this_node->tag == 'EXAM') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $es_num = $this_node->attributes['NUMBER'] + 0;
                        $this->group[$g]['ESAM'][$es_num] = $es_num;
                        $this->esams[$vis_num][$es_num] = $this_node->attributes;
                        $this->xml[$es_num] = $this_node->attributes['XML'];
                    }
                }
                if ($this_node->tag == 'CLOSE_VISIT') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->visitnums[$vis_num]['CLOSE_VISIT'] = $this_node->value;

                    }
                }
                if ($this_node->tag == 'CLOSE_VISIT_NOTE') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->visitnums[$vis_num]['CLOSE_VISIT_NOTE'] = $this_node->value;
                        $this->visitnums[$vis_num]['CLOSE_VISIT_NOTE_ATTR'] = $this_node->attributes;

                    }
                }
                if ($this_node->tag == 'ENABLE_VISIT') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $en_idx += 0;
                        $this->enable_visit[$vis_num][$en_idx] = $this_node->attributes;
                        $en_idx++;
                    }
                }
                if ($this_node->tag == 'TEXT') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->esams[$vis_num][$es_num]['TESTO'] = $this_node->value;
                    }
                }
                if ($this_node->tag == 'EXAM_HEADER') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->esams[$vis_num][$es_num]['HEADER'] = $this_node->value;
                    }
                }
                if ($this_node->tag == 'CLOSE_ALL') {
                    if ($this_node->type == 'open' or $this_node->type == 'complete') {
                        $this->esams['CLOSE_ALL'] = $this_node->value;
                    }
                }
            }
        }

        if (isset($this->config_service['eQuery']) && $this->config_service['eQuery'] == 1) {
            if (
                (isset($_GET[$this->config_service['PK_SERVICE']]) && $_GET[$this->config_service['PK_SERVICE']] != '' && $_GET[$this->config_service['PK_SERVICE']] != 'next') ||
                (isset($_POST[$this->config_service['PK_SERVICE']]) && $_POST[$this->config_service['PK_SERVICE']] != '' && $_POST[$this->config_service['PK_SERVICE']] != 'next')
            )
                //echo ("USER_PROFILE: ".$this->session_vars['USER_PROFILE']."<br/>");
                //print_r($this->session_vars);
                //echo "<hr/>";
                //debug_print_backtrace();
                //echo "<hr/>";
                $this->integrazione = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP'], $this->session_vars, $this->xml_dir);
        }
    }

    /**
     * Controlla se la visita  chiusa
     *
     * @param number $visitnum
     * @return boolean
     */
    function isVisitClose($visitnum)
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        $sql_visitclose = "
			select
				max(visitclose) as visitclose
			from " . $GLOBALS['service'] . "_COORDINATE
			where visitnum=:visitnum and {$this->PK_SERVICE}=:pk_service
			";
        $sql = new query($conn);
        unset($bind);
        $bind['VISITNUM'] = $visitnum;
        $bind['PK_SERVICE'] = $in[$this->PK_SERVICE];
        //$sql->set_sql($sql_visitclose);
        $sql->exec($sql_visitclose, $bind);//binded
        if ($sql->get_row()) {
            if ($sql->row['VISITCLOSE'] == 1) return true;
            else return false;
        } else return false;
    }

    function AddVisitProgr($visitnum)
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        if ($this->isVisitClose($visitnum)) return false;
        $sql_visit_progr = "
			select
				max(visitnum_progr) as visitnum_progr
			from " . $GLOBALS['service'] . "_COORDINATE
			where visitnum=:visitnum and {$this->PK_SERVICE}=:pk_service
			";
        unset($bind);
        $bind['VISITNUM'] = $visitnum;
        $bind['PK_SERVICE'] = $in[$this->PK_SERVICE];

        $sql = new query($conn);
        //$sql->set_sql($sql_visit_progr);
        $sql->exec($sql_visit_progr, $bind);//binded
        if ($sql->get_row()) {
            $next_visit_progr = $sql->row['VISITNUM_PROGR'] + 1;
        } else $next_visit_progr = 0;
        foreach ($this->esams[$visitnum] as $key => $val) {
            if ($val['DEFAULT'] == 'yes') {
                //sql-injection CARLO
                $sql_query_enable = "insert into " . $GLOBALS['service'] . "_COORDINATE
					({$this->PK_SERVICE}, visitnum, visitnum_progr, esam, progr, abilitato)
					values ({$in[$this->PK_SERVICE]}, $visitnum, $next_visit_progr, $key, 1, 1)
				";
                $sql_query_enable = "insert into " . $GLOBALS['service'] . "_COORDINATE
					({$this->PK_SERVICE}, visitnum, visitnum_progr, esam, progr, abilitato)
					values ({$in[$this->PK_SERVICE]}, $visitnum, $next_visit_progr, $key, 1, 1)
				";
                $bindVars['pk_service'] = $in[$this->PK_SERVICE];
                $bindVars['visitnum'] = $visitnum;
                $bindVars['next_visit_progr'] = $next_visit_progr;
                $bindVars['key'] = $key;
                //$sql->set_sql($sql_query_enable);
                $sql->ins_upd($sql_query_enable, $bindVars); //binded
                $conn->commit();
            }
        }
        return $next_visit_progr;
    }

    function DelVisitProgr($visitnum, $visitnum_progr)
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $sql = new query($conn);
        foreach ($this->esams[$visitnum] as $key => $val) {
            $xml_form = new xml_form();
            $xml_form->xml_form_by_file($xml_dir . '/' . $val['XML']);
            $table = $xml_form->form['TABLE'];
            $esam = $val['NUMBER'];
            //sql-injection CARLO
            $bindVars = '';
            $sql_save_storico = "
				insert into S_{$xml_form->form['TABLE']}
  					select '{$in['remote_userid']}', sysdate, storico_id.nextval, 'E', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
   					and t.esam=$esam
     				and t.visitnum = {$visitnum}
     				and t.visitnum_progr = {$visitnum_progr}
			";
            $sql_save_storico = "
				insert into S_{$xml_form->form['TABLE']}
  					select :remote_user, sysdate, storico_id.nextval, 'E', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = :pk_service
   					and t.esam=:esam
     				and t.visitnum = :visitnum
     				and t.visitnum_progr = :visitnum_progr
			"; //binded
            $bindVars['remote_userid'] = $in['remote_userid'];
            $bindVars['pk_service'] = $in[$this->PK_SERVICE];
            $bindVars['esam'] = $esam;
            $bindVars['visitnum'] = $visitnum;
            $bindVars['visitnum_progr'] = $visitnum_progr;
            $bindVars2 = '';
            $sql_delete = "
     			delete from {$xml_form->form['TABLE']}
     			where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     				and esam=$esam
     				and visitnum = {$visitnum}
     				and visitnum_progr = {$visitnum_progr}
     		";
            $sql_delete = "
     			delete from {$xml_form->form['TABLE']}
     			where {$this->PK_SERVICE} = :pk_service
     				and esam=:esam
     				and visitnum = :visitnum
     				and visitnum_progr = :visitnum_progr
     		"; //binded
            $bindVars2['pk_service'] = $in[$this->PK_SERVICE];
            $bindVars2['esam'] = $esam;
            $bindVars2['visitnum'] = $visitnum;
            $bindVars2['visitnum_progr'] = $visitnum_progr;
            $sql->ins_upd($sql_save_storico, $bindVars); //binded
            $sql->ins_upd($sql_delete, $bindVars2); //binded
            //echo "<li>$sql_save_storico</li><li>$sql_delete</li>";

        }
        $bindVars3 = "";
        $sql_delete_coordinate = "
     			delete from " . $GLOBALS['service'] . "_COORDINATE where
     				{$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     				and visitnum = {$visitnum}
     				and visitnum_progr = {$visitnum_progr}
     		";
        $sql_delete_coordinate = "
     			delete from " . $GLOBALS['service'] . "_COORDINATE where
     				{$this->PK_SERVICE} = :pk_service
     				and visitnum = :visitnum
     				and visitnum_progr = :visitnum_progr
     		"; //binded

        $bindVars3['pk_service'] = $in[$this->PK_SERVICE];
        $bindVars3['visitnum'] = $visitnum;
        $bindVars3['visitnum_progr'] = $visitnum_progr;
        $sql->ins_upd($sql_delete_coordinate, $bindVars3); //binded
        $conn->commit();
        //echo "<li> - $sql_delete_coordinate</li>";
        $this->ScalaVisiteProgr($visitnum, $visitnum_progr);
    }

    function ScalaVisiteProgr($visitnum, $visitnum_progr)
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $sql = new query($conn);
        $sql_vprogrs = "select visitnum_progr from " . $GLOBALS['service'] . "_COORDINATE where
			{$this->PK_SERVICE} = :pk_service
     				and visitnum = :visitnum
     				and visitnum_progr > :visitnum_progr
     			order by visitnum_progr asc
			";
        unset($bind);
        $bind['PK_SERVICE'] = $in[$this->PK_SERVICE];
        $bind['VISITNUM'] = $visitnum;
        $bind['VISITNUM_PROGR'] = $visitnum_progr;
        //$sql->set_sql($sql_vprogrs);
        $sql->exec($sql_vprogrs, $bind);//binded
        while ($sql->get_row()) {
            $sql2 = new query($conn);
            //echo "<li><b>{$sql->row['VISITNUM_PROGR']}</b></li>";
            $vprogr = $sql->row['VISITNUM_PROGR'];
            $sql_duplica_coordinate = "
     		insert into " . $GLOBALS['service'] . "_COORDINATE
     			select
     				VISITNUM,
     				PROGR,
     				ESAM,
     				INIZIO,
     				FINE,
     				INSERTDT,
     				MODDT,
     				USERID,
     				VISITCLOSE,
     				INV_QUERY,
     				{$this->PK_SERVICE},
     				ABILITATO,
     				VISITNUM_PROGR-1
     			from " . $GLOBALS['service'] . "_COORDINATE
     			where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     			and visitnum = {$visitnum}
     			and visitnum_progr = {$vprogr}
     				";
            $sql_duplica_coordinate = "
     		insert into " . $GLOBALS['service'] . "_COORDINATE
     			select
     				VISITNUM,
     				PROGR,
     				ESAM,
     				INIZIO,
     				FINE,
     				INSERTDT,
     				MODDT,
     				USERID,
     				VISITCLOSE,
     				INV_QUERY,
     				{$this->PK_SERVICE},
     				ABILITATO,
     				VISITNUM_PROGR-1
     			from " . $GLOBALS['service'] . "_COORDINATE
     			where {$this->PK_SERVICE} = :pk_service
     			and visitnum = :visitnum
     			and visitnum_progr = :visitnum_progr
     				"; //binded
            $bindVars = '';
            $bindVars['pk_service'] = $in[$this->PK_SERVICE];
            $bindVars['visitnum'] = $visitnum;
            $bindVars['visitnum_progr'] = $vprogr;
            //echo "<li>$sql_duplica_coordinate</li>";
            $sql2->ins_upd($sql_duplica_coordinate, $bindVars); //binded
            foreach ($this->esams[$visitnum] as $key => $val) {
                $xml_form = new xml_form();
                $xml_form->xml_form_by_file($xml_dir . '/' . $val['XML']);
                $table = $xml_form->form['TABLE'];
                $esam = $val['NUMBER'];
                $sql_save_storico = "
				insert into S_{$xml_form->form['TABLE']}
  					select '{$in['remote_userid']}', sysdate, storico_id.nextval, 'S', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
   					and t.esam=$esam
     				and t.visitnum = {$visitnum}
     				and t.visitnum_progr = {$vprogr}
				";
                $sql_save_storico = "
				insert into S_{$xml_form->form['TABLE']}
  					select :remote_userid, sysdate, storico_id.nextval, 'S', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = :pk_service
   					and t.esam=:esam
     				and t.visitnum = :visitnum
     				and t.visitnum_progr = :visitnum_progr
				"; //binded
                $bindVars1 = "";
                $bindVars1["remote_userid"] = $in['remote_userid'];
                $bindVars1["pk_service"] = $in[$this->PK_SERVICE];
                $bindVars1["esam"] = $esam;
                $bindVars1["visitnum"] = $visitnum;
                $bindVars1["visitnum_progr"] = $vprogr;
                $sql_update_table = "
					update {$table} set visitnum_progr=visitnum_progr-1
					where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
						and esam=$esam
     					and visitnum = {$visitnum}
     					and visitnum_progr = {$vprogr}
				";
                $sql_update_table = "
					update {$table} set visitnum_progr=visitnum_progr-1
					where {$this->PK_SERVICE} = :pk_service
						and esam=:esam
     					and visitnum = :visitnum
     					and visitnum_progr = :visitnum_progr
				"; // binded
                $bindVars2 = "";
                $bindVars2["pk_service"] = $in[$this->PK_SERVICE];
                $bindVars2["esam"] = $esam;
                $bindVars2["visitnum"] = $visitnum;
                $bindVars2["visitnum_progr"] = $vprogr;
                $sql2->ins_upd($sql_save_storico, $bindVars1); //binded
                $sql2->ins_upd($sql_update_table, $bindVars2); //binded
                //echo "<li>$sql_save_storico</li><li>$sql_update_table</li>";
            }
            $sql_coordinate_delete = "
				delete from " . $GLOBALS['service'] . "_COORDINATE
				where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     			and visitnum = {$visitnum}
     			and visitnum_progr = {$vprogr}
			";
            $sql_coordinate_delete = "
				delete from " . $GLOBALS['service'] . "_COORDINATE
				where {$this->PK_SERVICE} = :pk_service
     			and visitnum = :visitnum
     			and visitnum_progr = :visitnum_progr
			"; //binded
            $bindVars3 = "";
            $bindVars3["pk_service"] = $in[$this->PK_SERVICE];
            $bindVars3["visitnum"] = $visitnum;
            $bindVars3["visitnum_progr"] = $vprogr;
            $sql2->ins_upd($sql_coordinate_delete, $bindVars3); //binded
            //echo "<li>$sql_coordinate_delete</li>";
        }
        $conn->commit();
    }

    /**
     * Restituisce il codice xml dell'oggetto
     *
     * @return string
     */
    function obj_to_xml()
    {
        $xml_str = "<visit_exam>\n";
        foreach ($this->group as $key => $val) {
            $xml_str .= "	<group text=\"{$val['TEXT']}\">\n";
            foreach ($val['VISIT'] as $key_v => $val_v) {
                $xml_str .= "		<visit number=\"$val_v\" text=\"{$this->visitnums[$val_v]['TEXT']}\" short_txt=\"{$this->visitnums[$val_v]['SHORT_TXT']}\">\n";
                foreach ($this->esams[$val_v] as $es_num => $es_val) {
                    if (isset($es_val['PROGR'])) $progr = "PROGR=\"{$es_val['PROGR']}\"";
                    else $progr = "";
                    $xml_str .= "			<exam number=\"{$es_num}\" xml=\"{$es_val['XML']}\" $progr >\n";
                    $xml_str .= "				<text>{$es_val['TESTO']}</text>\n";
                    $xml_str .= "			</exam>\n";
                }
                $xml_str .= "		</visit>\n";
            }
            $xml_str .= "	</group>\n";
        }
        $xml_str .= "</visit_exam>";
        return $xml_str;
    }


    /**
     * Costruisce i tab relativo alla form visualizzata
     *
     * @return string
     */
    function esams_list_tab()
    {
        $es_val = null;
        $esam = null;
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $config_service = $this->config_service;
        $this->tab = "
		<noscript>
		<font color='red'>Attenzione salvare i dati prima di cambiare form</font>
		</noscript>
		<ul id=\"globalnav\">";
        if ($config_service['PK_SERVICE'] != '') $this->PK_SERVICE = $config_service['PK_SERVICE'];
        if ($config_service['VISITNUM_PROGR'] == '1') {
            $add_vprogr = "VISITNUM_PROGR,";
            $sql = new query($conn);
            $sql_select = "select max(visitnum_progr) as maxvp from " . $GLOBALS['service'] . "_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service";
            //$sql->set_sql($sql_select);
            unset($bind_pk);
            $bind_pk['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
            $sql->exec($sql_select, $bind_pk);//binded
            $sql->get_row();
            $max_vp = $sql->row['MAXVP'];
            foreach ($this->visitnums as $visit => $vval) {
                if ($vval['PROGR'] == 'yes') {
                    $v_progr_esam_spec = $this->esams[$visit];
                    unset($this->esams[$visit]);
                    for ($i = 0; $i <= $max_vp; $i++) {
                        $this->esams[$visit][$i] = $v_progr_esam_spec;
                    }
                }
            }
        }
        if ($in[$this->PK_SERVICE] == 'next') return;
        $query = "select visitnum,$add_vprogr esam, progr, inizio, fine,visitclose, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato, eq_action from " . $GLOBALS['service'] . "_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service order by visitnum,$add_vprogr esam ,progr";
        //echo "<hr>$query<hr>";
        $sql = new query($conn);
        unset($bind_pk);
        $bind_pk['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
        //$sql->set_sql($query);
        $sql->exec($query, $bind_pk);//binded
        $this->visit_menu = "<table  border=0><tr><th class=titolo><a href=\"index.php?CENTER=" . $in['CENTER'] . "&" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;exams=visite_exams.xml\">Lista Schede</a></th></tr>";
        #print_r($this->visitnums);
        while ($sql->get_row()) {
            if ($this->visitnums[$sql->row['VISITNUM']]['PROGR'] == 'yes') {
                if ($sql->row['ABILITATO'] == '1') $this->visitnums[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']]['ENABLED'] = true;
                if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']])) {
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE'] = $sql->row['FINE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO'] = $sql->row['INIZIO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT'] = $sql->row['INSERTDT'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO'] = $sql->row['ABILITATO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE'] = $sql->row['VISITCLOSE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION'] = $sql->row['EQ_ACTION'];
                }
            } else {
                if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])) {
                    if ($sql->row['ABILITATO'] == '1') $this->visitnums[$sql->row['VISITNUM']]['ENABLED'] = true;
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE'] = $sql->row['FINE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO'] = $sql->row['INIZIO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT'] = $sql->row['INSERTDT'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO'] = $sql->row['ABILITATO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE'] = $sql->row['VISITCLOSE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION'] = $sql->row['EQ_ACTION'];
                }
            }
        }
        foreach ($this->visitnums as $key => $val) {
            if ($val['PROGR'] == 'yes') {
                foreach ($this->esams[$key] as $vprogr => $vesam) {

                    $nro = $vprogr + 1;
                    if ($in['VISITNUM'] == $key && $in['VISITNUM_PROGR'] == $vprogr) {
                        if ($this->visitnums[$key][$vprogr]['ENABLED']) $this->visit_menu .= "<tr><td class=int><a href=\"index.php?CENTER=" . $in['CENTER'] . "&" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=" . $val['NUMBER'] . "&amp;exams=visite_exams.xml\"><font color=red>" . $val['TEXT'] . " $nro</font></a></td></tr>";
                        $visit_enabled = false;
                        foreach ($vesam as $esam => $es_val) {
                            if ($es_val)
                                if ($in['VISITNUM'] == $key) $this->print_esams_tab($es_val, $key, $esam);
                                else $this->print_esams_tab($es_val, $key, $esam, false);
                        }
                    } else if ($this->visitnums[$key][$vprogr]['ENABLED']) {
                        $this->print_esams_tab($es_val, $key, $esam, false);
                    }
                }
            } else {
                if ($in['VISITNUM'] == $key) {

                    if ($this->visitnums[$key]['ENABLED']) $this->visit_menu .= "<tr><td class=sc4bis><li><a href=\"index.php?CENTER=" . $in['CENTER'] . "&" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=" . $val['NUMBER'] . "&amp;exams=visite_exams.xml\" class=\"here\"><font color=red>" . $val['TEXT'] . "</font></a></li></td></tr>";
                    foreach ($this->esams[$key] as $esam => $es_val) {
                        if ($in['VISITNUM'] == $key) $this->print_esams_tab($es_val, $key, $esam);
                    }
                } else {
                    if ($this->visitnums[$key]['ENABLED']) $this->visit_menu .= "<tr><td class=sc4bis><li><a href=\"index.php?CENTER=" . $in['CENTER'] . "&" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=" . $val['NUMBER'] . "&amp;exams=visite_exams.xml\" class=\"here\">" . $val['TEXT'] . "</a></li></td></tr>";
                    foreach ($this->esams[$key] as $esam => $es_val) {
                        $this->print_esams_tab($es_val, $key, $esam, false);
                    }
                }
            }
        }
        $this->tab .= "</ul><br><br><br>";
        global $config_service;
        global $tab_menu_list;
        $this->visit_menu .= "
			<tr>
				<td class=titolo align=center><a href=\"index.php?list=patients_list.xml\">{$config_service['Patients_list']}</a></td>
			</tr>
			$tab_menu_list
		";
        if (class_exists('SDV_module')) {
            $link = "index.php?SDV_LIST=status";
            if ($in['CENTER'] != '') $link .= "&CENTER={$in['CENTER']}";
            $this->visit_menu .= "
                <tr>
                    <td class=titolo align=center><a href=\"$link\">SDV Status list</a></td>
                </tr>";
        }
        $this->visit_menu .= "
        </table>
        ";
        return $this->tab;
    }

    /**
     * Restituisce il tab dell'esame $esam della visita $key
     *
     * @param array $es_val
     * @param number $key
     * @param number $esam
     */
    function print_esams_tab($es_val, $key, $esam, $this_visit = true)
    {
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $config_service = $this->config_service;

        //echo "<hr>$key<hr>";
        $link = "index.php?CENTER=" . $in['CENTER'] . "&" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=" . $key . "&amp;ESAM={$esam}";
        //echo "<hr>$esam - <hr>";
        $enabled = false;


        if (isset($es_val['PROGR']) && $es_val['PROGR'] == 'yes' && $es_val['CONT_FORM'] == '') {
            if (isset($es_val['RES']) && is_array($es_val['RES'])) foreach ($es_val['RES'] as $res_key => $vals) {
                $es_progr = $res_key;
                $link .= "&PROGR={$es_progr}";
                if ($vals['ABILITATO'] == '1') $enabled = true;
                $sql2 = new query($conn);
                if ($es_val['VAL_AGG'] != '') {
                    //echo "<hr>{$es_val['TESTO']}<hr>";
                    $query_data = "select {$es_val['VAL_AGG']} as VAL_AGG from {$GLOBALS['service']}_{$es_val['TABLE']} where " . $config_service['PK_SERVICE'] . "=:pk_service and  progr=:progr and esam=:esam";
                    //echo "<hr>$query_data";
                    unset($bind);
                    $bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                    $bind['PROGR'] = $es_progr;
                    $bind['ESAM'] = $esam;
                    //$sql2->set_sql($query_data);
                    $sql2->exec($query_data, $bind);//binded
                    $sql2->get_row();
                    $date = $sql2->row['VAL_AGG'];
                    //echo $date;
                }
                $nome_esame = $es_val['TESTO'] . " $date";
                //echo "<hr>$nome_esame";
                if ($enabled) {
                    if (isset($in['ESAM']) && $in['ESAM'] == $esam && $in['PROGR'] == $es_progr) {
                        if ($this_visit) $this->tab .= "<li>{$es_val['HEADER']}<a href=\"#\" class=\"here\" onclick=\"return false;\">{$nome_esame}</a></li>\n";
                        //$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li><a href=\"#\" class=\"here\" onclick=\"return false;\"><font color=red>{$nome_esame}</font></a></li></td></tr>";
                    } else {
                        global $editing;
                        if ($editing) {
                            //$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\" onclick=\"window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$es_progr}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;\">{$nome_esame}</a></li></td></tr>";

                            if ($this_visit) $this->tab .= "<li>{$es_val['HEADER']}<a href=\"$link\"
								onclick=\"
					window.open('confirm_tab_change.php?" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$es_progr}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;
				\">{$nome_esame}</a></li>\n";
                        } else {
                            if ($this_visit) $this->tab .= "<li>{$es_val['HEADER']}<a href=\"$link\">{$es_val['TESTO']}</a></li>\n";
                            //$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\">{$nome_esame}</a></li></td></tr>";
                        }
                    }
                }
            }
        } else {
            //print_r($es_val);
            if (isset($es_val['RES']) && is_array($es_val['RES'])) foreach ($es_val['RES'] as $res_key => $vals) {
                if ($vals['ABILITATO'] == '1') $enabled = true;
            }
            if ($enabled) {
                if (class_exists('SDV_module')) {
                    $param['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                    $param['VISITNUM'] = $key;
                    $param['ESAM'] = $esam;
                    $param['FINE'] = $es_val['RES'][1]['FINE'];
                    $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], $this);
                    $vprogr = 0; //TODO: Le visite progressive non sono gestite!
                    $add_module = $sdv->before_print_esams($param, 1, $vprogr); //TODO: Le visite progressive non sono gestite!
                }
                if (isset($in['ESAM']) && $in['ESAM'] == $esam) {
                    if ($this_visit) $this->tab .= "<li>{$es_val['HEADER']}<a href=\"#\" class=\"here\" onclick=\"return false;\">{$es_val['TESTO']}</a></li>\n";
                    //$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li><a href=\"#\" class=\"here\" onclick=\"return false;\"><font color=red>{$es_val['TESTO']}</font></a></li></td></tr>";
                } else {
                    global $editing;
                    if ($editing) {
                        //$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\" onclick=\"window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$vals['PROGR']}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;\">{$es_val['TESTO']}</a></li></td></tr>";
                        if ($this_visit) $this->tab .= "<li>{$es_val['HEADER']}<a href=\"$link\"
								onclick=\"
                                    window.open('confirm_tab_change.php?" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$vals['PROGR']}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;
                                \">{$es_val['TESTO']}</a>{$add_module}</li>\n";
                    } else {
                        if ($this_visit) $this->tab .= "<li>{$es_val['HEADER']}<a href=\"$link\">{$es_val['TESTO']}</a>{$add_module}</li>\n";
                        //$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\">{$es_val['TESTO']}</a></li></td></tr>";
                    }
                }
            }
        }
    }

    /**
     * Sostituisce l'ultima occorenza di $search
     *
     * @param unknown_type $search
     * @param unknown_type $replace
     * @param unknown_type $subject
     * @return unknown
     */
    function str_lreplace($search, $replace, $subject)
    {
        $pos = strrpos($subject, $search);

        if ($pos === false) {
            return $subject;
        } else {
            return substr_replace($subject, $replace, $pos, strlen($search));
        }
    }

    function buildEsamsList($service = null)
    {
        $show_all = null;
        $max_vprogr = null;
        if (isset($service))
            $parametro_passato = true;
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $config_service = $this->config_service;
        global $patient_table;
        $sql = new query($conn);
        if (!$service)global $service;
        $sql_close = "select min(visitclose) as chiusa from {$service}_coordinate where {$config_service['PK_SERVICE']}=:pk_service";

        //echo "<li>$sql_close</li>";
        unset($bind_pk);
        $bind_pk['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
        //$sql->set_sql($sql_close);
        $sql->exec($sql_close, $bind_pk);//binded
        $sql->get_row();
        $chiusa = $sql->row['CHIUSA'];

        if ($config_service['PK_SERVICE'] == '') $config_service['PK_SERVICE'] = $this->PK_SERVICE;
        if ($config_service['VISITNUM_PROGR'] == '1') {
            $add_vprogr = "VISITNUM_PROGR,";
            $sql = new query($conn);
            $sql_select = "select max(visitnum_progr) as maxvp from " . $service . "_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service";
            unset($bind_pk);
            $bind_pk['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
            $sql->exec($sql_select, $bind_pk);//binded
            $sql->get_row();
            $max_vp = $sql->row['MAXVP'];
            foreach ($this->visitnums as $visit => $vval) {
                if ($vval['PROGR'] == 'yes') {
                    $v_progr_esam_spec = $this->esams[$visit];
                    unset($this->esams[$visit]);
                    for ($i = 0; $i <= $max_vp; $i++) {
                        $this->esams[$visit][$i] = $v_progr_esam_spec;
                    }
                }
            }
        }
        $query = "select userid,visitclose,visitnum,$add_vprogr esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato, eq_action from " . $service . "_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service order by visitnum,$add_vprogr esam ,progr";
        unset($bind_pk);
        $bind_pk['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
        $sql = new query($conn);
        $sql->exec($query, $bind_pk);//binded
        while ($sql->get_row()) {
            if ($this->visitnums[$sql->row['VISITNUM']]['PROGR'] == 'yes') {
                if ($sql->row['ABILITATO'] == '1') $this->visitnums[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']]['ENABLED'] = true;
                if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']])) {
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE'] = $sql->row['FINE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO'] = $sql->row['INIZIO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT'] = $sql->row['INSERTDT'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO'] = $sql->row['ABILITATO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA'] = $sql->row['VALIDATA'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE'] = $sql->row['VISITCLOSE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['USERID'] = $sql->row['USERID'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION'] = $sql->row['EQ_ACTION'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['_DBG_HERE_ATTR'] = "buildEsamsList";
                    $this->visitnums[$sql->row['VISITNUM']]['CLOSED'] = $sql->row['VISITCLOSE'];
                }
            } else {
                if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])) {
                    if ($sql->row['ABILITATO'] == '1') $this->visitnums[$sql->row['VISITNUM']]['ENABLED'] = true;
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE'] = $sql->row['FINE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO'] = $sql->row['INIZIO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT'] = $sql->row['INSERTDT'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO'] = $sql->row['ABILITATO'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA'] = $sql->row['VALIDATA'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE'] = $sql->row['VISITCLOSE'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['USERID'] = $sql->row['USERID'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION'] = $sql->row['EQ_ACTION'];
                    $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['_DBG_HERE_ATTR'] = "buildEsamsList";
                    $this->visitnums[$sql->row['VISITNUM']]['CLOSED'] = $sql->row['VISITCLOSE'];
                }
            }
        }
        $this->tab = "<ul id=\"globalnav\">";
        if ($this->config_service['eQuery'] == 1) {
            $sql_eqint = "select * from {$service}_eqfield eqfield,{$service}_EQ eq where
						 eqfield.{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
						and eq.equery_int=eqfield.eq_int and eq.stato in (0,2)
					";
            $sql3 = new query ($this->conn);
            $sql3->set_sql($sql_eqint);
            $sql3->exec();
            $this->pending_esams = array();
            while ($sql3->get_row()) {
                foreach ($this->visitnums as $visitnum => $visit_val) {
                    foreach ($this->esams[$visitnum] as $esam => $es_val) {
                        if ($sql3->row['ESAM'] == $esam && $sql3->row['VISITNUM'] == $visitnum) {
                            $this->pending_esams[$visitnum][$esam]['EQ_PENDING'] = 1;
                            $this->pending_esams[$visitnum][$esam]['EQ_INT'] = $sql3->row['EQ_INT'];
                        } else {
                            $this->pending_esams[$visitnum][$esam]['EQ_PENDING'] = 0;
                        }
                    }
                }
            }
        }

        foreach ($this->visitnums as $key => $val) {
            if ($val['VIEWABLE_ON_CLOSE'] == 'yes' && $in['USER_TIP'] != 'DE' && $val['CLOSED'] != '1') {
                continue;
            }
            $af_progr = "";
            if (isset($in['GROUP'])) {
                $in['VISITNUM'] = 'non so';
                if (isset($this->group[$in['GROUP']]['VISIT'][$key])) {
                    $in['VISITNUM'] = $key;
                }
            }
            if ($val['PROGR'] == 'yes') {
                $visitProgressive[$key] = true;
                if (!$this->isVisitClose($key) && $val['BUTTONS_DISABLED'] != 'yes' && $in['USER_TIP'] == 'DE') {
                    //$aggiungi_visita='<div><button value="" id="add_visit_button">Aggiungi visita</button></div>';
                } else {
                    $aggiungi_visita = '';
                }
                global $config_service;
                if (isset($config_service['class_visit_progr'])) {
                    $style_table = "class=\"{$config_service['class_visit_progr']}\" ";
                } else {
                    $style_table = "";
                }
                if ($this->visitnums[$key][0]['ENABLED']) {
                    $tabs[$key] = mlOut("VISIT." . $this->visitnums[$key]['NUMBER'] . ".NAME", $this->visitnums[$key]['TEXT']);
                    //$tabs[$key]=$this->visitnums[$key]['TEXT'];
                }
                foreach ($this->esams[$key] as $vprogr => $vesam) {
                    if ($max_vprogr < $vprogr) $max_vprogr = $vprogr;
                }
                global $onload;
                foreach ($this->esams[$key] as $vprogr => $vesam) {
                    $nro = $vprogr + 1;
                    if ($val['SET_PROGR_START'] == '') $nro_label = $nro;
                    else $nro_label = $vprogr + $val['SET_PROGR_START'];

                    if ($this->visitnums[$key][$vprogr]['ENABLED']) {
                        $param = "";
                        foreach ($_GET as $gkey => $gval) {
                            if ($gkey != 'VISITNUM_PROGR') {
                                $param .= "$gkey=$gval&";
                            }
                        }
                        if ($in['VISITNUM_PROGR'] != $nro - 1 && $this->visitnums[$key]['SHOW_ALWAYS'] != "yes") {
                            $onload .= "
								document.getElementById('af_{$key}_{$nro}').style.display='none';
								";
                        }
                        if ($this->config_service['mostraDataInvio']) {
                            $show_all .= "
									document.getElementById('table_af_{$key}_{$nro}').className='';
									";
                        } else {
                            $show_all .= "
									document.getElementById('af_{$key}_{$nro}').style.display='';
								";
                        }
                        $not_delete = false;
                        foreach ($vesam as $esam => $es_val) {
                            if ($es_val['RES'][1]['FINE'] == '1') {
                                $not_delete = true;
                            }
                        }
                        if ($in['USER_TIP'] != 'DE') {
                            $not_delete = true;
                        }
                        $onclick = "";

                        foreach ($vesam as $esam => $es_val) {
                            if ($vprogr == null) {
                                $vprogr = "0";
                            }
                            $esams = array();
                            if ($es_val['RES'][1]['ABILITATO'] == '1') {
                                $esams = $this->print_esams($es_val, $key, $esam, $vprogr);
                                if ($this->config_service['mostraDataInvio']) {
                                }
                            }
                            foreach ($esams as $k => $v) {
                                $content[$key][$vprogr][$k] = $v;
                            }
                        }

                    }
                }
            } else {
                $visitProgressive[$key] = false;
                if ($this->visitnums[$key]['ENABLED']) {
                    $tbody_close = '';
                    $tbody_open = '';
                    $show_hide_link = '';
                    $count_schede = 0;
                    $schede_vuote = 0;
                    foreach ($this->esams[$key] as $esam => $es_val) {
                        if ($es_val['RES'][1]['ABILITATO'] == '1') {
                            $count_schede++;
                        }
                        if ($es_val['RES'][1]['ABILITATO'] == '1') {
                            foreach ($es_val['RES'] as $k_v => $v_v) {
                                if ($v_v['INIZIO'] != '1') {
                                    $schede_vuote++;
                                }
                            }
                        }
                    }

                    $tabs[$key] = mlOut("VISIT." . $val['NUMBER'] . ".NAME", $val['TEXT']);
                    foreach ($this->esams[$key] as $esam => $es_val) {
                        $this_enabled = false;
                        if (!$es_val['RES']) {
                            $es_val['RES'] = array();
                        }
                        foreach ($es_val['RES'] as $p => $x) {
                            if ($es_val['RES'][$p]['ABILITATO'] == 1) {
                                $this_enabled = true;
                            }
                        }
                        $esams = array();
                        if ($this_enabled) {
                            $esams = $this->print_esams($es_val, $key, $esam);
                        }
                        foreach ($esams as $k => $v) {
                            $content[$key][0][$k] = $v;
                        }
                    }
                }
            }

            global $service;
            $sql_close_visit = "select nvl(min(visitclose),0) as close from {$service}_coordinate where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and VISITNUM=$key";
            $sql = new query($this->conn);
            $sql->get_row($sql_close_visit);

        }
        global $service;
        $sql_close = "select min(visitclose) as closed from {$service}_coordinate where {$config_service['PK_SERVICE']}=:pk_service";
        $sql2 = new query($conn);
        unset($bind_pk);
        $bind_pk['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
        $sql2->exec($sql_close, $bind_pk);//binded
        $sql2->get_row();
        if (isset($this->esams['CLOSE_ALL']) && $in['USER_TIP'] == 'DE' && $sql2->row['CLOSED'] != '1') {
            $sql_query = "select max(stato) as stato from {$service}_coordinate where {$this->PK_SERVICE}=:pk_service and abilitato=1";
            $sql = new query($conn);
            unset($bind_stato);
            $bind_stato['PK_SERVICE'] = $in[$this->PK_SERVICE];
            $sql->exec($sql_query, $bind_stato);//binded
            $sql->get_row();
            if ($sql->row['STATO'] == '2') {
                $sql_query = "select min(fine) as fine from {$service}_coordinate where {$this->PK_SERVICE}=:pk_service and abilitato=1";
                $sql = new query($conn);
                unset($bind_chiusa);
                $bind_chiusa['PK_SERVICE'] = $in[$this->PK_SERVICE];
                $sql->exec($sql_query, $bind_chiusa);//binded
                $sql->get_row();

            } else {
                $js_close_all = make_js($this->esams['CLOSE_ALL']);
            }
        }
        if ($this->config_service['lang'] == "en") {
            $go = "Go to ";
        } else {
            $go = "Vai alla ";
        }
        if ($config_service['Patients_list'] != "") {
            $link = "index.php?list=patients_list.xml";
            if ($in['CENTER'] != '') {
                $link .= "&CENTER={$in['CENTER']}";
            }
            if (!$parametro_passato) {

            }
        }
        foreach ($tabs as $key => $val) {
            if ($this->visitnums[$key]['CLOSED'] == 1) {
                $status = "completed";
            } else {
                $status = "incomplete";
                $empty = true;
                foreach ($content[$key] as $esam => $val1) {
                    foreach ($val1 as $k => $v) {
                        if ($v['status'] != 'to_be_comp.gif') $empty = false;
                    }
                }
                if ($empty) $status = "new";
            }
            $tabStatuses[$key]['STATO'] = $status;
        }

        foreach ($content as $k1 => $l1) {
            foreach ($l1 as $k2 => $l2) {
                foreach ($l2 as $k3 => $l3) {
                }
            }
        }
        $this->tabs = $tabs;
        $this->tabsContent = $content;
        $this->tabStatuses = $tabStatuses;
        $this->visitProgressive = $visitProgressive;
        $ret['tabs'] = $tabs;
        $ret['contents'] = $content;
        $ret['tabStatuses'] = $tabStatuses;
        $ret['visitProgressive'] = $visitProgressive;
        return $ret;
    }

    /**
     * Restituisce la lista delle form compilate e compilabili
     *
     * @return string
     */
    function esams_list_html($service = null)
    {
        $color = null;
        $options = null;
        $config_service = null;
        $es_progr = null;
        //$ret=$this->buildEsamsList($service);
        $tabs = $this->tabs;
        $content = $this->tabsContent;
        $tabStatuses = $this->tabStatuses;
        $visitProgressive = $this->visitProgressive;
        global $in;
        if (!$service) {
            $service = $this->config_service['service'];
        }

        $listStyle = $this->config_service['VisiteListStyle'];
        //var_dump($listStyle);

        //DA QUI NUOVA MODALITA'
        $this->body = '
				<!--div class="widget-box"-->
					<!--div class="widget-header header-color-blue">
						<h5><i class="fa fa-folder"></i> Patient\'s folder</h5>
				</div-->
				<!--div class="widget-body"-->
				<div class="br_separator"/>
					<div class="tabbable" >';
        if (!$listStyle) {
            $this->body .= '	<ul class="nav nav-tabs" id="myTab">';
        }
        $first = true;
        if ($_GET['A_VISITNUM'] != "") $activeTab = $_GET['A_VISITNUM'];
        if ($_GET['VISITNUM'] != "") $activeTab = $_GET['VISITNUM'];

        $visitTitle = array();
        foreach ($tabs as $key => $val) {
            //if ($tabStatuses[$key]['STATO']=="completed") $color="green";
            //if ($tabStatuses[$key]['STATO']=="incomplete") $color="orange";
            //if ($tabStatuses[$key]['STATO']=="new") $color="blue";
            if ((!isset($activeTab) && $first) || $activeTab == $key) $class = "active";
            else $class = "";
            if (!$listStyle) {
                $this->body .= '
			<li class="' . $class . '">
				<a data-toggle="tab" href="#visit_' . $key . '" class="green">
					<i class="' . $color . ' fa fa-clipboard bigger-110"></i> ' . mlOut("VISIT." . $key . ".NAME", $val) . '
				</a>
			</li>';
            } else {
                $visitTitle[$key] = '
			<div class="tab-content active" style="border-bottom: 0px; " >
				<a data-toggle="tab" href="#visit_' . $key . '" class="green">
					<i class="' . $color . ' fa fa-clipboard bigger-110"></i> ' . mlOut("VISIT." . $key . ".NAME", $val) . '
				</a>
			</div>';

            }
            $first = false;
        }
        if (!$listStyle) {
            $this->body .= '	</ul>';
            $this->body .= '	<div class="tab-content">';
        }
        $first = true;
        foreach ($content as $visit => $val1) {
            if ((!isset($activeTab) && $first) || $activeTab == $visit || $listStyle) {
                $class = "active";
            } else {
                $class = "";
            }
            if ($listStyle) {
                $this->body .= $visitTitle[$visit];
                $this->body .= '<div class="tab-content esam_content" style="padding:0px; border-top: 0px;">';
            }
            $this->body .= "<div id=\"visit_{$visit}\" data-visitnum='{$visit}' class=\"tab-pane in $class\">";
            $lastVProgr = end(array_keys($val1));
            foreach ($val1 as $vprogr => $_val1) {

                if ($visitProgressive[$visit]) {
                    $nVisit = $vprogr + 1;

                    $aggiungi_visita = '';
                    if ($vprogr == $lastVProgr && !$this->isVisitClose($visit) && $_val1['BUTTONS_DISABLED'] != 'yes' && $in['USER_TIP'] == 'DE') {
                        //Recupero i parametri di get
                        $qstr = "";
                        $hasVNUM = false;
                        foreach ($_GET as $k => $v) {
                            if ($qstr) {
                                $qstr .= "&";
                            }
                            if (strtoupper($k) == "VISITNUM") {
                                $hasVNUM = true;
                            }
                            if (strtoupper($k) == "VISITNUM_PROGR") {
                                //Ignoro il parametro
                            }
                            $qstr .= $k . "=" . htmlspecialchars($v);
                        }
                        if (!$hasVNUM) {
                            $qstr .= "&VISITNUM={$visit}";
                        }
                        $qstr .= "&CREATE_VPROGR=yes";
                        $aggiungi_visita = '<button class="btn btn-xs btn-info" id="add_visit_button" onclick="window.location.href=\'index.php?' . $qstr . '\';return false;">' . mlOut("System.esams_list.add_new_visit", $this->testo("Aggiungi_nuova_visita")) . '</button>';
                    }

                    $this->body .= "
						<div class='vprogr-exam-list' data-visitnum='{$visit}' data-visitnum-progr='{$vprogr}' id='visit-$visit-progr-$vprogr'>
						<div style='float: left; width: 70%;'><h4>" . mlOut("VISIT.PROGRESSIVE.NR", "Visit n.ro") . " {$nVisit}</h4></div>
						<div style='float: right; width: 25%; text-align: right;'>{$aggiungi_visita}</div>
					";
                }

                foreach ($_val1 as $esam => $val2) {
                    if ($val2['correlated']) continue;
                    if (isset($val2['corr'])) {
                        $hasCorrelated = true;
                        $corrEsam = $val2['corr'];
                    } else {
                        $hasCorrelated = false;
                    }
                    if (!$visitProgressive[$visit])
                        $es_val = $this->esams[$visit][$esam];
                    else
                        $es_val = $this->esams[$visit][$vprogr][$esam];
                    $file_form = $es_val['XML'];
                    $form1 = new xml_form($this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                    $form1->xml_form_by_file($this->xml_dir . "/" . $file_form);
                    if (array_key_exists('DATA-FILTER', $es_val)) {
                        $sql_query = "select distinct {$es_val['DATA-FILTER']} as FILTER
										from {$form1->form['TABLE']} 
										where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} 
											and visitnum={$visit}
											and visitnum_progr={$vprogr}
											and esam={$esam}
											order by FILTER";
                        $sql = new query ($this->conn);
                        $sql->set_sql($sql_query);
                        $sql->exec();
                        while ($sql->get_row()) {
                            $options .= "<option value=\"{$sql->row['FILTER']}\">{$sql->row['FILTER']}</option>";
                        }
                        $js_filter = "
							var valore=$(\"#DATA-FILTER\")[0].value;
							$(\"[data-filter]\").hide();
							$(\"[data-filter=\"+valore+\"]\").show();
							if (valore=='') $(\"[data-filter]\").show();
							";
                        //echo $js_filter;
                        $this->body .= "
							<script> function filtra(){ $js_filter }</script>
							Filtra per: <select id=\"DATA-FILTER\" onchange=\"filtra();\">
							<option value=\"\">Tutte</option>
							$options
							</select><br><br>";
                    }
                    $nomeEsame = $this->esams[$visit][$esam]['TESTO'];

                    $this->body .= "<div style='clear:both;' data-esam-nome='" . strip_tags($nomeEsame) . "' data-esam='$esam' data-visitnum='$visit' data-visitnum-progr='$vprogr'>";
                    $grupped = false;
                    if ($this->esams[$visit][$esam]['GROUP_PROGR'] != null) {
                        $groupCount = $this->esams[$visit][$esam]['GROUP_PROGR'] - 0;
                        if (count($val2) >= $groupCount) {
                            $grupped = true;
                            $tot = count($val2);
                            foreach ($val2 as $progr => $v) {
                                if ($v['status'] != "submitted.gif") {
                                    $tot--;
                                }
                            }
                            $this->body .= "<p data-esam-nro='$tot' data-esam-name='" . strip_tags($nomeEsame) . "' data-esam='$esam' data-visitnum='$visit' data-visitnum-progr='$vprogr' data-esam-corr='$corrEsam' class=\"alert-success esam-row-groupped progr-groupped\" style='margin: 0 0 0;padding-left: 5px;'>
							<i class=\" fa fa-clipboard bigger-110\"></i> <strong>$nomeEsame (" . $tot . ")</strong> &nbsp;
							<a href='#' data-esam='$esam' data-visitnum='$visit' data-visitnum-progr='$vprogr' class='show_groupped' style='display:;'><i class='fa fa-eye'></i> <span>" . mlOut('System.esams.mostra', 'mostra') . "</span></a>
							<a href='#' data-esam='$esam' data-visitnum='$visit' data-visitnum-progr='$vprogr' class='hide_groupped' style='display: none;'><i class='fa fa-eye-slash'></i> <span>" . mlOut('System.esams.nascondi', 'nascondi') . "</span></a> 
						</p>
						";
                        }
                    }
                    foreach ($val2 as $progr => $v) {
                        if ($progr . "" != "corr") {
                            if ($v['status'] == 'submitted.gif') {
                                $statusClass = "success";
                                $statusText = mlOut("System.Exam.Completed", "Completed");;
                                $linkIcon = "check-square-o";
                                $colorClass = "green";
                            }
                            if ($v['status'] == NULL || $v['status'] == "to_be_comp.gif") {
                                $statusClass = "info";
                                $statusText = mlOut("System.Exam.NewForm", "New form");
                                $linkIcon = "plus";
                                $colorClass = "blue";
                            }
                            if ($v['status'] == "divieto") {
                                $statusClass = "info";
                                $statusText = mlOut("System.Exam.NewForm", "New form");
                                $linkIcon = "minus-circle"; //GENHD-44 non veniva colorato di rosso se il "red" era in $linkIcon, spostato in $colorClass
                                $colorClass = "red";
                            }
                            if ($v['status'] == 'saved.gif') {
                                $statusClass = "warning";
                                $statusText = mlOut("System.Exam.NotCompleted", "Not completed");
                                $linkIcon = "pencil-square-o";
                                $colorClass = "orange";
                            }
                            if ($statusClass != "info" && isset($v['dateInv']) && count($v['dateInv']) > 0) {
                                $statusText .= " - " . mlOut("System.Exam.ModifiedBy", "Modified by") . " " . $v['dateInv'][0] . " " . mlOut("System.Exam.ModifiedOn", "on") . " " . $v['dateInv'][1];
                            }
                            //Icone EQ e moduli aggiuntivi (SDV)
                            $addmodule = "";
                            $addeq = "";
                            if (class_exists('SDV_module')) {
                                $vprogr = 0; //TODO: Indice visite progressive?
                                $eprogr = 1; //Esami non progressivi
                                $xmldir = false;
                                $param['PK_SERVICE'] = $in[$this->config_service['PK_SERVICE']];
                                $param['VISITNUM'] = $visit;
                                $param['ESAM'] = $esam;
                                $param['FINE'] = ($v['status'] == 'submitted.gif'); //$es_val['RES'][1]['FINE'];
                                $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], $this, $xmldir);
                                $addmodule = $sdv->before_print_esams($param, $eprogr, $vprogr);
                                //echo "<pre>ADDM: {$addmodule}<br/>\n</pre>";
                            }
                            if ($this->config_service['eQuery'] == 1) {
                                $this->integrazione->eq_int = $this->pending_esams[$visit][$esam]['EQ_INT'];
                            }

                            $es_val = $this->esams[$visit][$esam];
                            if ($this->integrazione->eq_enabled) {
                                $eqpresent = false;
                                if ($this->pending_esams[$visit][$esam]['EQ_INT'] != "" || ($es_val['MAIN'] == "yes" && $this->pending_esams[$visit][$esam + 1]['EQ_INT'] != "")) {
                                    $eqpresent = true;
                                }
                                if ($es_val['PROGR'] != "") {
                                    $agg_where = '';
                                    if ($vprogr != null) $agg_where = "and VISITNUM_PROGR={$vprogr}";
                                    $sql_query = "select count(*) as c from {$service}_eqfield where
	                                    esam={$esam}
	                                    and visitnum={$visit}
	                                    $agg_where
	                                    and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
	                                    --and eq_int={$this->integrazione->eq_int}
	                                    and action=0
	                                    ";
                                    $sql2 = new query($this->conn);
                                    //echo "$sql_query<hr/>";
                                    $sql2->get_row($sql_query);
                                    if ($sql2->row['C'] > 0) {
                                        $eqpresent = true;
                                    }
                                    //SDV Per esami progressivi
                                    if (class_exists('SDV_module')) {
                                        $vprogr = 0; //TODO: Indice visite progressive?
                                        $xmldir = false;

                                        $param['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                                        $param['VISITNUM'] = $key;
                                        $param['ESAM'] = $esam;
                                        $param['ALL_IN'] = 'yes';
                                        $param['FINE'] = $es_val['RES'][$es_progr]['FINE'];
                                        $sdv = new SDV_module($this->conn, $this->session_vars, $this->config_service, $this->config_service['service'], $this, $xmldir);
                                        $addmodule = $sdv->before_print_esams($param, null, $vprogr);
                                        //echo "<pre>PROGR_ADDM: {$addmodule}<br/>\n</pre>";
                                    }
                                }
                                if ($eqpresent) {
                                    $addeq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em; color:red; \" title=\"There are eQueries pending\"></i>";
                                }
                            }
                            //Integrazioni old style
                            if ($es_val['RES']['1']['EQ_ACTION'] == 1) {
                                $addeq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\" title=\"La scheda e' in fase di integrazione\"></i>";
                                //$nome_esame.="</a><b>(scheda aggiunta in fase di integrazione)</b>";
                            }
                            if ($es_val['RES']['1']['EQ_ACTION'] == 2) {
                                $addeq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\" title=\"La scheda rimossa in fase di integrazione\"></i>";
                                //$nome_esame.="</a><b>(scheda rimossa in fase di integrazione)</b>";
                            }
                            if ($linkIcon == 'plus') $newForm = "true";
                            else $newForm = "false";
                            $nomeEsame = str_replace("</a>", "", $v['nome']);
                            $addStyle = "display:";
                            $addClass = "notSubmitted";
                            if ($grupped && $v['status'] == "submitted.gif") {
                                $addStyle = " display:none;";
                                $addClass = " submitted";
                            }
                            $status = "<span data-esam-new='$newForm' data-esam='$esam' data-esam-progr='$progr' data-visitnum='$visit' data-visitnum-progr='$vprogr' data-esam-corr='$corrEsam' class=\"esam-label label label-sm label-{$statusClass} {$addClass}\" style=\"float:right;border-radius: 0 0 0 8px! important;{$addStyle}\">$statusText</span>";
                            $this->body .= "{$status}<p style='{$addStyle}' data-esam-new='$newForm' data-esam-name='" . strip_tags($nomeEsame) . "' data-esam='$esam' data-esam-progr='$progr' data-visitnum='$visit' data-visitnum-progr='$vprogr' data-esam-corr='$corrEsam' class=\"esam-row alert-{$statusClass} {$addClass}\">{$v['link']}<i class=\"fa fa-{$linkIcon} {$colorClass}\"></i> {$addeq} {$addmodule} <span class=\"text-$statusClass\">{$v['nome']}</span></a>
							";
                            $this->body .= "</p>";
                            if ($hasCorrelated) {
                                if (isset($val1[$vprogr][$corrEsam][$progr])) {

                                    $corrVal = $val1[$vprogr][$corrEsam][$progr];

                                    if ($corrVal['status'] == 'submitted.gif') {
                                        $statusClass = "success";
                                        $statusText = mlOut("System.Exam.Completed", "Completed");
                                        $linkIcon = "check-square-o";
                                    }
                                    if ($corrVal['status'] == NULL || $corrVal['status'] == "to_be_comp.gif") {
                                        $statusClass = "info";
                                        $statusText = mlOut("System.Exam.NewForm", "New form");
                                        $linkIcon = "plus-square";
                                    }
                                    if ($corrVal['status'] == 'saved.gif') {
                                        $statusClass = "warning";
                                        $statusText = mlOut("System.Exam.NotCompleted", "Not completed");
                                        $linkIcon = "pencil-square-o";
                                    }
                                    if ($v['status'] == "divieto") {
                                        $statusClass = "info";
                                        //$statusText="New form";
                                        $statusText = mlOut("System.Exam.NewForm", "New form");
                                        $linkIcon = "minus-circle red";
                                    }
                                    if ($statusClass != "info" && isset($corrVal['dateInv']) && count($corrVal['dateInv']) > 0) {
                                        $statusText .= " - " . mlOut("System.Exam.ModifiedBy", "Modified by") . " " . $corrVal['dateInv'][0] . " " . mlOut("System.Exam.ModifiedOn", "on") . " " . $corrVal['dateInv'][1];
                                    }
                                    $nomeEsame = str_replace("</a>", "", $v['nome']);
                                    if ($linkIcon == 'plus') $newForm = "true";
                                    else $newForm = "false";
                                    $addStyle = "display:";
                                    $addStyle = "display:";
                                    $addClass = "notSubmitted";
                                    if ($grupped && $v['status'] == "submitted.gif") {
                                        $addStyle = " display:none;";
                                        $addClass = " submitted";
                                    }
                                    $status = "<span data-esam-new='$newForm' data-esam='$esam' data-esam-progr='$progr' data-visitnum='$visit' data-visitnum-progr='$vprogr' data-esam-corr='$corrEsam' class=\"esam-label label label-sm label-{$statusClass} {$addClass}\" style=\"float:right;border-radius: 0 0 0 8px! important;{$addStyle}\">$statusText</span>";
                                    $this->body .= "$status<p style='{$addStyle}' data-esam-new='$newForm' data-esam='$esam' data-esam-name='" . strip_tags($nomeEsame) . "' data-esam-corr='$corrEsam' data-esam-progr='$progr' data-visitnum='$visit' data-visitnum-progr='$vprogr' class=\"esam-row alert-{$statusClass} {$addClass}\" style=\"padding-left:20px!important;\">{$corrVal['link']}<i class=\"fa fa-{$linkIcon}\"></i> <span class=\"text-$statusClass\">{$corrVal['nome']}</span></a>
									";
                                    $this->body .= "</p>";
                                }

                            }
                        }

                    }
                    $this->body .= "</div>";
                }
                if ($visitProgressive[$visit]) {
                    $this->body .= "
						</div>
					";
                }
            }

            $this->body .= "
			</div>		
			";

            if ($listStyle) {
                //Chiudo il div di bordatura contenuto.
                $this->body .= '</div>';
                //Aggiungo piccolo spazio bianco tra 1 riga e l'altra
                $this->body .= '<p>&nbsp;</p>';
            }

            $first = false;
        }
        if (!$listStyle) {
            $this->body .= '</div>';
        }
        $this->body .= '
						</div>
				<!--/div--><!--/div-->';

        return $this->body;
    }

    /**
     * Restituisce il codice html dell esame $esam della visita $key
     * ($key=VISITNUM)
     * @param array $es_val
     * @param number $key
     * @param number $esam
     */
    function print_esams($es_val, $key, $esam, $vprogr = 0)
    {
        $progr = null;
        $archiviata = null;
        if ($es_val['HEADER'] != "") $header = "<tr><td class=\"sc4bis\"></td><td class=\"int exam_header\" style=\"text-align:left;\">{$es_val['HEADER']}</td></tr>";
        if ($vprogr != null) $agg_param = "&VISITNUM_PROGR={$vprogr}";
        else $agg_param = "";
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $config_service = $this->config_service;
        global $service;
        $nome_form = $es_val['TESTO'];
        /*ESAM STANDARD*/
        if ((!isset($es_val['PROGR']) || $es_val['PROGR'] != 'yes') && !isset($es_val['CORR']) && $es_val['SUB'] != "yes") {
            $img = "to_be_comp.gif";
            $progr = 1;
            if ($es_val['PROGR'] != '') $progr = $es_val['PROGR'];
            if ($es_val['RES'][$progr]['INIZIO'] == '0' || $es_val['RES'][$progr]['INIZIO'] == '') $img = "to_be_comp.gif";
            if ($es_val['RES'][$progr]['INIZIO'] == '1') $img = "saved.gif";
            if ($es_val['RES'][$progr]['FINE'] == '1') $img = "submitted.gif";
            if ($this->config_service['mostraDataInvio']) {
                $file_form = $es_val['XML'];
                $form1 = new xml_form($this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                $form1->xml_form_by_file($xml_dir . "/" . $file_form);
                $f_table = $form1->form['TABLE'];
                $dateinv = $this->getInsData($f_table, $in[$config_service['PK_SERVICE']], $key, $vprogr, $esam, $progr);
                $agg_dateinv = "<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
											</td>";
            }
            $date = $es_val['RES'][$progr]['INSERTDT'];
            if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE'] == 'yes' && $es_val['RES'][$progr]['FINE'] != '1') {
                if ($in['USER_TIP'] != 'DE' && $es_val['RES'][$progr]['USERID'] != $in['remote_userid']) return;
            }
            //agg da mod  di alejandra nelle lib vecchie
            if ($es_val['FOTH'] && ($es_val['RES'][$progr]['FINE'] == '1' || $es_val['FOTH_ALWAYS'] == 'yes')) {
                if (isset($es_val['EOTH']) && $es_val['EOTH'] !== '') $esam_oth = $es_val['EOTH'];
                else $esam_oth = $es_val['NUMBER'];
                //per ottenere un foth preciso
                if ($es_val['FOTH_SAME_FORM'] != "") {
                    $add_foth_where = " and visitnum_progr=:visitnum_progr and progr=:progr";
                    unset($bind_data);
                    $bind_data['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                    $bind_data['ESAM'] = $esam_oth;
                    $bind_data['VISITNUM_PROGR'] = $vprogr;
                    $bind_data['PROGR'] = $progr;
                } else {
                    $add_foth_where = "";
                    unset($bind_data);
                    $bind_data['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                    $bind_data['ESAM'] = $esam_oth;

                }
                $query_data = "select {$es_val['FOTH']} as FOTH from {$config_service['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}=:pk_service and esam=:esam {$add_foth_where}";
                $sql2 = new query($conn);
                $sql2->exec($query_data, $bind_data);//binded
                $sql2->get_row();
                $foth = $sql2->row['FOTH'];
                $nome_esame = mlOut("VISIT." . $key . ".EXAM." . $esam . ".NAME", $es_val['TESTO']) . $foth;
            } else {
                $nome_esame = mlOut("VISIT." . $key . ".EXAM." . $esam . ".NAME", $es_val['TESTO']);
            }
            if ($es_val['INS_DATE'] == 'yes') {
                $nome_esame .= $date;
            }
            if ($es_val['RES'][$progr]['FINE'] == '1') $nome_esame .= "</a>";
            if ($es_val['RES'][$progr]['ABILITATO'] == '1' || $es_val['RES']['']['ABILITATO'] == '1') {
                $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;VISITNUM_PROGR={$vprogr}&amp;PROGR=1&amp;form=" . $es_val['XML'] . "{$agg_param}\">";
                $close_href = "</a>";
                if ($es_val['INDENT'] == 'yes') $indent = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
                else $indent = "";
                $img_tag = "<img src=\"/images/$img\" border=\"0\">";
                if ($this->config_service['eQuery'] == 1) {
                    $this->integrazione->eq_int = $this->pending_esams[$key][$esam]['EQ_INT'];
                }

                $ret[$esam][$progr]["link"] = $href;
                $ret[$esam][$progr]["nome"] = $nome_esame;
                $ret[$esam][$progr]["status"] = $img;
                $ret[$esam][$progr]["date"] = $date;
                $ret[$esam][$progr]["dateInv"] = $dateinv;
            }
        } //ESAMI PROGRESSIVI
        elseif ($es_val['SUB'] != "yes") {
            $last_progr = 0;
            $form_alt = '';
            if (isset($es_val['RES']) && !isset($es_val['CORR'])) {
                if ((isset($es_val['CONT_FORM']) && $es_val['CONT_FORM'] == 'yes') || isset($es_val['ALL_IN'])) {
                    $sql2 = new query($conn);
                    if ($es_val['VAL_AGG'] != '') {
                        $where_agg = $es_val['WHERE_AGG'];
                        $query_data = "select {$es_val['VAL_AGG']} as VAL_AGG from {$GLOBALS['service']}_{$es_val['TABLE']} where " . $config_service['PK_SERVICE'] . "=:pk_service and esam=:esam $where_agg";
                        unset($bind_agg);
                        $bind_agg['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                        $bind_agg['ESAM'] = $esam;
                        $sql2->exec($query_data, $bind_agg);
                        $sql2->get_row();
                        $date = $sql2->row['VAL_AGG'];
                    }

                    foreach ($es_val['RES'] as $es_progr => $progr_vals) {
                        if ($es_val['RES'][$es_progr]['INIZIO'] == '1') {
                            $sql2 = new query($conn);
                            if ($es_val['DATA'] != '') {
                                $query_data = "select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where " . $config_service['PK_SERVICE'] . "='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
                                $sql2->set_sql($query_data);
                                $sql2->exec();
                                $sql2->get_row();
                                $date = $sql2->row['DATA'];
                            }
                            if ($es_val['VAL_AGG'] != '') {
                                $query_data = "select {$es_val['VAL_AGG']} as VAL_AGG from {$service}_{$es_val['TABLE']} where " . $config_service['PK_SERVICE'] . "='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}' and esam='$esam'";
                                $sql2->set_sql($query_data);
                                $sql2->exec();
                                $sql2->get_row();
                                $date = $sql2->row['VAL_AGG'];
                            }
                            if ($es_val['FOTH']) {
                                $query_data = "select {$es_val['FOTH']} as FOTH from {$GLOBALS['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}' and visitnum_progr={$vprogr}";
                                #echo "<hr>$query_data";
                                $sql2->set_sql($query_data);
                                $sql2->exec();
                                $sql2->get_row();
                                $date = $sql2->row['FOTH'];
                            }
                            if ($es_val['RES'][$es_progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                            if ($es_val['RES'][$es_progr]['INIZIO'] == '1') $img = "saved.gif";
                            if ($es_val['RES'][$es_progr]['FINE'] == '1') $img = "submitted.gif";
                        }
                        $last_progr = $es_progr;
                    }
                    $n_progr = 0;
                    $init = false;
                    $all_completed = true;
                    $eq_present = false;
                    $add_text = '';
                    $count_added = 0;
                    $count_deleted = 0;
                    $all_deleted = true;
                    $all_added = true;
                    $deleted = false;
                    $added = false;
                    $modified = false;
                    //TODO: Verificare equery per esami progressivi QUI!
                    if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '') {
                        $agg_where = '';
                        if ($vprogr != null) $agg_where = "and VISITNUM_PROGR={$vprogr}";
                        $sql_query = "select count(*) as c from {$service}_eqfield where
                        esam={$esam}
                        and visitnum=$key
                        $agg_where
                        and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
                        and eq_int={$this->integrazione->eq_int}
                        and action=0
                        ";
                        $sql2 = new query($this->conn);
                        $sql2->get_row($sql_query);
                        if ($sql2->row['C'] > 0) {
                            $modified = true;
                        }
                    }
                    $unset_viewable_on_close = false;
                    foreach ($es_val['RES'] as $keys => $val) {
                        if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE'] == 'yes' && $in['USER_TIP'] != 'DE') {
                            if ($val['FINE'] == '1' || $val['USERID'] == $this->session_vars['remote_userid']) $n_progr++;
                            if ($val['USERID'] == $this->session_vars['remote_userid']) $unset_viewable_on_close = true;
                        } else {
                            if ($val['INIZIO'] == '1') $n_progr++;
                        }
                        if ($val['INIZIO'] == '' || $val['INIZIO'] == '0') $img = "to_be_comp.gif";
                        if ($val['INIZIO'] == '1') $init = true;
                        if ($val['FINE'] != '1') $all_completed = false;
                        if ($val['INV_QUERY'] != '') $eq_present = true;
                        if ($val['EQ_ACTION'] == 2) {
                            $all_added = false;
                            $count_deleted++;
                            $deleted = true;
                        }
                        if ($val['EQ_ACTION'] == 1) {
                            $all_deleted = false;
                            $count_added++;
                            $added = true;
                        }

                    }
                    if ($unset_viewable_on_close) unset($es_val['VIEWABLE_ON_CLOSE']);
                    if ($add_text != '' && $all_added) $add_text = "</a><b>(Schede aggiunte in fase di integrazione)</b>";
                    if ($add_text != '' && $all_deleted) $add_text = "</a><b>(Schede rimosse in fase di integrazione)</b>";
                    if ($modified || $added || $deleted) {
                        $kind = "";
                        if ($deleted) {
                            if ($kind != '') $kind .= "/";
                            $kind .= "eliminate";
                        }
                        if ($added) {
                            if ($kind != '') $kind .= "/";
                            $kind .= "aggiunte";
                        }
                        if ($modified) {
                            if ($kind != '') $kind .= "/";
                            $kind .= "modificate";
                        }
                        $add_text = "</a><b>(Schede $kind in fase di integrazione)</b>";
                    }


                    if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE'] == 'yes' && $in['USER_TIP'] != 'DE') {
                        if ($n_progr == 0) {
                            return;
                        } else {
                            $all_completed = true;
                        }
                    }
                    if ($init) $img = "saved.gif";
                    if ($all_completed) $img = "submitted.gif";
                    if ($n_progr == 0) {
                        $img = "to_be_comp.gif";
                        if ($this->true_false['configurato']) {
                            $n_progr = $this->testi['nuovo_inserimento'];
                        } else {
                            $n_progr = "Nuovo inserimento";
                        }
                    }

                    if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE'] == 'yes') {
                        $count_fine = 0;
                        foreach ($es_val['RES'] as $k_idx => $val_idx) {
                            if ($val_idx['FINE'] == 1 || $val_idx['USERID'] == $in['remote_userid']) {

                                $count_fine++;
                            }
                        }
                        $n_progr = $count_fine;
                        if ($count_fine == 0) {
                            $img = "to_be_comp.gif";
                        }
                    }
                    $date = " (" . $n_progr . ") " . $date;
                    $nome_esame = mlOut("VISIT." . $key . ".EXAM." . $esam . ".NAME", $es_val['TESTO']) . " $date";
                    $nome_esame .= $add_text;
                    if ($progr != '') {
                        $sql_query = "select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}
                        and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1 and visitnum_progr=$vprogr";

                        unset($bind_chiusa);
                        $bind_chiusa['PK_SERVICE'] = $in[$this->PK_SERVICE];
                        $bind_chiusa['VISITNUM'] = $key;
                        $bind_chiusa['ESAM'] = $esam;
                        $bind_chiusa['VISITNUM_PROGR'] = $vprogr;
                        $bind_chiusa['PROGR'] = $progr;
                    } else {
                        /*$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery
                                    where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and visitnum=$key and esam=$esam and nvl(chiusa,0)<>1 and visitnum_progr=$vprogr";*/
                        $sql_query = "
                        select nvl(e.chiusa,0) as chiusa, min(c.fine) as fine from {$service}_equery e, {$service}_coordinate c
                        where c.{$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and c.visitnum=$key and c.esam=$esam and nvl(e.chiusa,0)<>1 and c.visitnum_progr=$vprogr
                        and e.{$this->PK_SERVICE}=c.{$this->PK_SERVICE} and e.esam=c.esam and c.visitnum=e.visitnum and c.visitnum_progr=e.visitnum_progr
                        group by e.chiusa
                        ";
                        unset($bind_chiusa);
                        $bind_chiusa['PK_SERVICE'] = $in[$this->PK_SERVICE];
                        $bind_chiusa['VISITNUM'] = $key;
                        $bind_chiusa['ESAM'] = $esam;
                        $bind_chiusa['VISITNUM_PROGR'] = $vprogr;

                    }

                    $sql2 = new query($conn);
                    $sql2->exec($sql_query, $bind_chiusa);//binded
                    if ($sql2->numrows > 0) {
                        $sql2->get_row();
                        if ($in['USER_TIP'] == 'DE' && !$archiviata && $sql2->row['CHIUSA'] == '0' && ($es_val['RES'][$es_progr]['FINE'] != '1' || $sql2->row['FINE'] == '0')) {
                            $nome_esame .= "<font color=red>(" . mlOut("System.Exam.InReview", "da revisionare") . ")</font>";
                        }
                    }
                    if ($es_val['RES'][$es_progr]['ABILITATO'] == '1') {
                        $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=" . $es_val['XML'] . "{$agg_param}\">";
                        if ($es_progr != '') {
                        }

                        $close_href = "</a>";
                        $img_tag = "<img src=\"/images/$img\" border=\"0\">";
                        if ($deleted || $modified || $added) {
                            $img_tag = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\" title=\"La scheda e' in fase di integrazione\"></i>" . $img_tag;
                        }
                        $ret[$esam][$es_progr]["link"] = $href;
                        $ret[$esam][$es_progr]["nome"] = $nome_esame;
                        $ret[$esam][$es_progr]["status"] = $img;
                        $ret[$esam][$es_progr]["date"] = $date;
                    }
                } else {
                    foreach ($es_val['RES'] as $es_progr => $progr_vals) {
                        if ($es_val['RES'][$es_progr]['INIZIO'] == '1') {
                            $sql2 = new query($conn);
                            $date = "";
                            if ($this->config_service['mostraDataInvio']) {
                                $file_form = $es_val['XML'];
                                $form1 = new xml_form($this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                                $form1->xml_form_by_file($xml_dir . "/" . $file_form);
                                $f_table = $form1->form['TABLE'];
                                $dateinv = $this->getInsData($f_table, $in[$config_service['PK_SERVICE']], $key, $vprogr, $esam, $es_progr);
                                $agg_dateinv = "<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
											</td>";
                            }
                            if ($es_val['DATA'] != '') {
                                $query_data = "select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where " . $config_service['PK_SERVICE'] . "=:pk_service and  progr=:progr";
                                unset($bind_data);
                                $bind_data['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                                $bind_data['PROGR'] = $es_progr;
                                $sql2->exec($query_data, $bind_data);//binded
                                $sql2->get_row();
                                $date = $sql2->row['DATA'];
                            }
                            if ($es_val['VAL_AGG'] != '') {
                                $query_data = "select {$es_val['VAL_AGG']} as VAL_AGG from {$service}_{$es_val['TABLE']} where " . $config_service['PK_SERVICE'] . "=:pk_service and  progr=:progr and esam=:esam ";
                                unset($bind_agg);
                                $bind_agg['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                                $bind_agg['PROGR'] = $es_progr;
                                $bind_agg['ESAM'] = $esam;
                                $sql2->exec($query_data, $bind_agg);//binded
                                $sql2->get_row();
                                $date = $sql2->row['VAL_AGG'];
                            }
                            if ($es_val['FOTH']) {
                                if ($es_val['WOTH'] != '') {
                                    $add_foth_where = "and ({$es_val['WOTH']})";
                                } else {
                                    $add_foth_where = "";
                                }
                                $query_data = "select {$es_val['FOTH']} as FOTH from {$GLOBALS['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}=:pk_service and  progr=:progr and visitnum_progr=:visitnum_progr " . $add_foth_where;
                                unset($bind_data);
                                $bind_data['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                                $bind_data['PROGR'] = $es_progr;
                                $bind_data['VISITNUM_PROGR'] = $vprogr;
                                $sql2->exec($query_data, $bind_data);//binded
                                $sql2->get_row();
                                $date .= $sql2->row['FOTH'];
                            }
                            if ($last_progr + 1 != $es_progr)
                                while ($last_progr < $es_progr - 1) {
                                    $last_progr++;
                                    $n_progr = $last_progr;
                                    $img = "to_be_comp.gif";
                                    $form_alt = str_replace(".xml", ".xml", $es_val['XML']);
                                    if (!file_exists($xml_dir . "/" . $form_alt)) {
                                        $form_alt = $es_val['XML'];
                                    }
                                    $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=" . $form_alt . "{$agg_param}\">";
                                    $nome_esame = mlOut("VISIT." . $key . ".EXAM." . $esam . ".NAME", $es_val['TESTO']) . " n. $n_progr";
                                    if ($progr != '') {
                                        $sql_query = "select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam and progr=:progr";
                                        $sql2 = new query($conn);
                                        unset($bind_chiusa);
                                        $bind_chiusa['PK_SERVICE'] = $in[$this->PK_SERVICE];
                                        $bind_chiusa['VISITNUM'] = $key;
                                        $bind_chiusa['ESAM'] = $esam;
                                        $bind_chiusa['PROGR'] = $progr;
                                        $sql2->exec($sql_query, $bind_chiusa);//binded
                                        if ($sql2->numrows > 0) {
                                            $sql2->get_row();
                                            if ($in['USER_TIP'] == 'DE' && !$archiviata && $sql2->row['CHIUSA'] == '0' && $es_val['RES'][$es_progr]['FINE'] != '1') $nome_esame .= "<font color=red>(da revisionare)</font>";
                                        }
                                    }
                                    $close_href = "</a>";
                                    $img_tag = "<img src=\"/images/$img\" border=\"0\">";
                                    $ret[$esam][$progr]["link"] = $href;
                                    $ret[$esam][$progr]["nome"] = $nome_esame;
                                    $ret[$esam][$progr]["status"] = $img;
                                    $ret[$esam][$progr]["date"] = $date;
                                    $ret[$esam][$progr]["dateInv"] = $dateinv;

                                }
                            if ($es_val['RES'][$es_progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                            if ($es_val['RES'][$es_progr]['INIZIO'] == '1') $img = "saved.gif";
                            if ($es_val['RES'][$es_progr]['FINE'] == '1') $img = "submitted.gif";
                            $n_progr = $es_progr;
                            if (isset($es_val['VAL_AGG'])) $nome_esame = "{$es_val['TESTO']} {$date}";
                            else {
                                if ($date != '') $date = " n.{$n_progr} ($date)";
                                $nome_esame = mlOut("VISIT." . $key . ".EXAM." . $esam . ".NAME", $es_val['TESTO']) . " $date";
                            }
                            if ($es_val['RES'][$es_progr]['ABILITATO'] == '1') {
                                $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=" . $es_val['XML'] . "{$agg_param}\">";
                                if ($es_progr != '') {
                                }
                                $close_href = "</a>";
                                $img_tag = "<img src=\"/images/$img\" border=\"0\">";
                                $ret[$esam][$es_progr]["link"] = $href;
                                $ret[$esam][$es_progr]["nome"] = $nome_esame;
                                $ret[$esam][$es_progr]["status"] = $img;
                                $ret[$esam][$es_progr]["date"] = $date;
                                $ret[$esam][$es_progr]["dateInv"] = $dateinv;

                            }
                            //LUIGI aggiunto meccanismo correlate e visione correlata al salvataggio/invio
                            //Logger::send($this->esams[$key]);
                            if ($this->visitnums[$vprogr]['PROGR'] == "yes") $forEachRoot = $this->esams[$key][$vprogr];
                            else $forEachRoot = $this->esams[$key];
                            foreach ($forEachRoot as $esam_corr => $es_val_corr) {
                                if (!is_numeric($esam_corr)) continue;
                                if ($es_val_corr['CORR'] != '' && $es_val_corr['CORR'] == $esam && ($es_val_corr['CORR_ON_SEND'] != 'yes' || $es_val['RES'][$es_progr]['FINE'] == 1)) {
                                    $date = "";
                                    $img = "to_be_comp.gif";
                                    if ($es_val_corr['RES'][$es_progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                                    if ($es_val_corr['RES'][$es_progr]['INIZIO'] == '1') $img = "saved.gif";
                                    if ($es_val_corr['RES'][$es_progr]['FINE'] == '1') $img = "submitted.gif";
                                    $dtp = '';
                                    if ($es_val_corr['DATA']) {
                                        $query_data = "select to_char({$es_val_corr['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val_corr['TABLE']} where " . $config_service['PK_SERVICE'] . "=:pk_service and  progr=:progr";
                                        unset($bind_data);
                                        $bind_data['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];
                                        $bind_data['PROGR'] = $es_progr;
                                        $sql2->exec($query_data, $bind_data);//binded
                                        $sql2->get_row();
                                        $date = $sql2->row['DATA'];
                                    }
                                    $n_progr = $es_progr;
                                    if ($date != '') {
                                        $dtp = " n.{$n_progr} ($date)";
                                    }
                                    $nome_esame = $es_val_corr['TESTO'] . " $dtp";
                                    if ($progr != '') {
                                        $sql_query = "select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam and progr=:progr";
                                        $sql2 = new query($conn);
                                        unset($bind_chiusa);
                                        $bind_chiusa['PK_SERVICE'] = $in[$this->PK_SERVICE];
                                        $bind_chiusa['VISITNUM'] = $key;
                                        $bind_chiusa['ESAM'] = $esam;
                                        $bind_chiusa['PROGR'] = $progr;
                                        $sql2->exec($sql_query, $bind_chiusa);//binded
                                        if ($sql2->numrows > 0) {
                                            $sql2->get_row();
                                            if ($in['USER_TIP'] == 'DE' && !$archiviata && $sql2->row['CHIUSA'] == '0' && $es_val['RES'][$es_progr]['FINE'] != '1') $nome_esame .= "<font color=red>(da revisionare)</font>";
                                        }
                                    }
                                    if ($this->config_service['mostraDataInvio']) {
                                        $file_form = $es_val_corr['XML'];
                                        $form1 = new xml_form($this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir);
                                        $form1->xml_form_by_file($xml_dir . "/" . $file_form);
                                        $f_table = $form1->form['TABLE'];
                                        $dateinv = $this->getInsData($f_table, $in[$config_service['PK_SERVICE']], $key, $vprogr, $es_val_corr['NUMBER'], $es_progr);
                                        $agg_dateinv = "<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
											</td>";
                                    }
                                    $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=$key&amp;ESAM=" . $es_val_corr['NUMBER'] . "&amp;PROGR=$es_progr&amp;form=" . $es_val_corr['XML'] . "\">";
                                    $close_href = "</a>";
                                    if (!$es_val_corr['VIEWABLE_ON_CLOSE'] || $es_val_corr['RES'][$es_progr]['FINE'] == '1') {
                                        $ret[$es_val_corr['NUMBER']][$es_progr]["link"] = $href;
                                        $ret[$es_val_corr['NUMBER']][$es_progr]["nome"] = $nome_esame;
                                        $ret[$es_val_corr['NUMBER']][$es_progr]["status"] = $img;
                                        $ret[$es_val_corr['NUMBER']][$es_progr]["date"] = $date;
                                        $ret[$es_val_corr['NUMBER']][$es_progr]["dateInv"] = $dateinv;
                                        $ret[$es_val_corr['NUMBER']]['correlated'] = true;
                                        $ret[$esam]["corr"] = $es_val_corr['NUMBER'];
                                    }
                                }
                            }
                            $last_progr = $es_progr;
                        }

                    }
                }
                if (($es_val['RES'][$es_progr]['FINE'] == 1 || $es_val['RES'][$es_progr]['INIZIO'] == '' || $es_val['NEXT_ENABLED'] != '') && !isset($es_val['ALL_IN']) && !$es_val['RES'][$es_progr]['VISITCLOSE']) {
                    if ($es_val['RES'][$es_progr]['INIZIO'] != '') {
                        $next_progr = $es_progr + 1;
                    } else {
                        $next_progr = $es_progr;
                    }
                    $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;" . $config_service['PK_SERVICE'] . "=" . $in[$config_service['PK_SERVICE']] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=" . $es_val['XML'] . "{$agg_param}\">";
                    $close_href = "</a>";
                    if (!isset($form_alt) || $form_alt == '') $form_alt = $es_val['XML'];
                    if ($this->config_service['mostraDataInvio']) {
                    }
                    if ($es_val['CONT_FORM'] != 'yes' && $es_val['DISABLE_NEW'] == '' && $in['USER_TIP'] != 'RO') {
                        $ret[$esam][$next_progr]["link"] = $href;
                        $ret[$esam][$next_progr]["nome"] = $this->testi['nuovo_inserimento'] . ": " . mlOut("VISIT." . $key . ".EXAM." . $esam . ".NAME", $es_val['TESTO']);
                        $ret[$esam][$next_progr]["status"] = "to_be_comp.gif";
                        $ret[$esam][$next_progr]["date"] = $date;
                        $ret[$esam][$next_progr]["dateInv"] = $dateinv;
                    }
                }
            }
        }
        if (!$ret) {
            $ret = array();
        }
        foreach ($ret as $esam => $val1) {
            foreach ($val1 as $progr => $val2) {
                if ($ret[$esam][$progr]["status"] == 'to_be_comp.gif' && $this->session_vars['USER_TIP'] == 'DM') {
                    $ret[$esam][$progr]["link"] = "";
                    $ret[$esam][$progr]["status"] = "divieto";
                    if (!isset($this->config_service['SHOW_ALL_EXAMS'])) { //vmazzeo 20.02.2015 GENHD-44 inserisco un flag SHOW_ALL_EXAMS da istanziare studio specifico (richiesta da exom)
                        unset($ret[$esam][$progr]);
                        if (preg_match("/^{$this->testi['nuovo_inserimento']}/", $ret[$esam][$next_progr]["nome"])) {
                            unset($ret[$esam][$progr]);
                        }
                    }
                }
            }
        }
        return $ret;
    }


    function getInsData($f_table, $pk_service, $visitnum, $visitnum_progr, $esam, $progr)
    {
        global $conn;
        $dateinv = array('', '');
        $query_exists = "SELECT * FROM user_tables where table_name = UPPER('$f_table')";
        $sql_exists = new query($conn);
        if ($sql_exists->get_row($query_exists)) {
            //TODO sistemare il binding!!!
            $query_invio = "select a.NOME||' '||a.COGNOME||' '||a.AZIENDA_ENTE NOME,
			to_char(nvl( MODDT ,INSERTDT), 'DD/MM/YYYY') as DATAINS
			from $f_table t,{$this->config_service['service']}_COORDINATE c, ANA_UTENTI_1 a where t.{$this->config_service['PK_SERVICE']}=:pk_service 
			and a.userid=t.USERID_INS 
			and t.{$this->config_service['PK_SERVICE']}=c.{$this->config_service['PK_SERVICE']} 
			and t.esam=c.esam 
			and t.visitnum=c.visitnum 
			and t.VISITNUM_PROGR=c.VISITNUM_PROGR
			and t.PROGR=c.PROGR 
			and t.PROGR=:progr 
			and t.VISITNUM=:visitnum 
			and t.VISITNUM_PROGR=:visitnum_progr 
			and t.esam=:esam";

            $bind['pk_service'] = $pk_service;
            $bind['VISITNUM'] = $visitnum;
            $bind['VISITNUM_PROGR'] = $visitnum_progr;
            $bind['ESAM'] = $esam;
            $bind['PROGR'] = $progr;
            $sql_invio = new query($conn);
            $sql_invio->exec($query_invio, $bind);
            $sql_invio->get_row();

            if ($sql_invio->row['NOME'] != '') $dateinv[0] .= $sql_invio->row['NOME'];
            if ($sql_invio->row['DATAINS'] != '') $dateinv[1] .= $sql_invio->row['DATAINS'];
            return $dateinv;
        }
    }

    /**
     * Vista alternativa di visualizzazione delle form
     *
     * @return string
     */
    function esams_list_html_view()
    {
        $esam_html = null;
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $config_service = $this->config_service;
        global $es_form;
        $query = "select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato, eq_action from " . $GLOBALS['service'] . "_COORDINATE where {$this->PK_SERVICE}=:pk_service order by visitnum,progr";
        //	  	echo "<hr>$query<hr>";
        //		echo $in[$this->PK_SERVICE]."<hr>";
        $sql = new query($conn);
        $bind_pk['PK_SERVICE'] = $in[$this->PK_SERVICE];
        $sql = new query($conn);
        //$sql->set_sql($query);
        $sql->exec($query, $bind_pk);//binded
        $esams_html = "";
        while ($sql->get_row()) {
            if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])) {
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE'] = $sql->row['FINE'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO'] = $sql->row['INIZIO'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT'] = $sql->row['INSERTDT'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO'] = $sql->row['ABILITATO'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION'] = $sql->row['EQ_ACTION'];
            }
        }
        //	  	print_r($this->esams);
        foreach ($this->visitnums as $key => $val) {
            if (!isset($in['VISITNUM']) || $in['VISITNUM'] == $key) {
                $this->body .= "
		  		<table class=\"bordi\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"95%\">
// 	        	<!--<tr>
// 							<td class=\"int\" align=\"left\"><b>" . $val['TEXT'] . "</b></td>
// 						</tr>
// 						</table>
// 						<table class=\"tabgrigia\" align=\"center\" border=\"0\" cellspacing=\"0\" width=\"95%\">-->
// 					      <!--tr>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"15%\"><b>Status</b></td>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"35%\"><b>Form name</b></td>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Due date</b></td>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Received date</b></td>
// 					     </tr-->
						";
                foreach ($this->esams[$key] as $esam => $es_val) {
                    $nome_form = $es_val['TESTO'];
                    //ESAMI NON PROGRESSIVO
                    if ((!isset($es_val['PROGR']) || $es_val['PROGR'] != 'yes') && !isset($es_val['CORR'])) {
                        $img = "to_be_comp.gif";
                        $progr = 1;
                        if ($es_val['PROGR'] != '') $progr = $es_val['PROGR'];
                        #echo "<hr>$key - $esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
                        if ($es_val['RES'][$progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                        if ($es_val['RES'][$progr]['INIZIO'] == '1') $img = "saved.gif";
                        if ($es_val['RES'][$progr]['FINE'] == '1') $img = "submitted.gif";
                        $date = $es_val['RES'][$progr]['INSERTDT'];
                        $nome_esame = $es_val['TESTO'];
                        if ($es_val['RES'][$progr]['FINE'] == '1') $nome_esame .= "</a>";
                        #if ($es_val['RES'][$progr]['FINE']=='1' && $in['USER_TIP']=='DE') $nome_esame.="&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;equery=".$es_val['XML']."\">invia e-query";
                        if ($es_val['RES'][$progr]['ABILITATO'] == '1' || $es_val['RES']['']['ABILITATO'] == '1') {
                            #$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;form=".$es_val['XML']."\">";
                            #$close_href="</a>";
                            //										$this->body.="
                            //									<tr>
                            //										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
                            //										</td>
                            //										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame."$close_href<br/>
                            //										</td>
                            //										<!--td class=\"sc4bis\" align=\"center\">
                            //										</td>
                            //										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
                            //										</td-->
                            //										</tr>
                            //										";
                            $in['VISITNUM'] = $key;
                            $in['ESAM'] = $esam;
                            $in['PROGR'] = $progr;
                            //										$in['CENTER']=$progr;
                            $xml_form = new xml_form();
                            //echo "$key -- $esam --{$es_form[$key][$esam]}<hr>";
                            $xml_form->xml_form_by_file($xml_dir . '/' . $es_form[$key][$esam]);
                            if ($xml_form->closed_form()) {
                                $xml_form->close_form();
                                $esam_html .= "" . $xml_form->body;
                                $tab = "<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
                                $esam_html = preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
                            }
                            unset($in['VISITNUM']);

                        }
                    } //ESAMI PROGRESSIVI
                    else {
                        if (isset($es_val['RES']) && !isset($es_val['CORR'])) {
                            foreach ($es_val['RES'] as $es_progr => $progr_vals) {
                                //										echo "<hr>$es_progr - ";
                                #print_r($es_val);
                                if ($es_val['RES'][$es_progr]['INIZIO'] == '1') {
                                    #echo "<hr>2 $es_progr - ";
                                    if ($es_val['RES'][$es_progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                                    if ($es_val['RES'][$es_progr]['INIZIO'] == '1') $img = "saved.gif";
                                    if ($es_val['RES'][$es_progr]['FINE'] == '1') $img = "submitted.gif";
                                    $date = "";
                                    $date = $es_val['RES'][$es_progr]['INSERTDT'];
                                    if ($date != '') $date = "($date)";
                                    $nome_esame = $es_val['TESTO'] . " $date";
                                    #echo "<hr>{$es_val['TESTO']} - $date";
                                    #if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val['XML']."\">invia e-query";
                                    if ($es_val['RES'][$es_progr]['ABILITATO'] == '1') {
                                        #$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
                                        #$close_href="</a>";
                                        //														$this->body.="
                                        //															<tr>
                                        //																 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
                                        //																</td>
                                        //																<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
                                        //																</td>
                                        //																<!--td class=\"sc4bis\" align=\"center\">
                                        //																</td>
                                        //																<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
                                        //																</td-->
                                        //															</tr>
                                        //														";
                                        $in['VISITNUM'] = $key;
                                        $in['ESAM'] = $esam;
                                        $in['PROGR'] = $es_progr;
                                        $xml_form = new xml_form();
                                        $xml_form->xml_form_by_file($xml_dir . '/' . $es_form[$key][$esam]);
                                        if ($xml_form->closed_form()) {
                                            $xml_form->close_form();
                                            $esam_html .= "" . $xml_form->body;
                                            $tab = "<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
                                            $esam_html = preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
                                        }
                                        unset($in['VISITNUM']);
                                        unset($in['ESAM']);
                                        unset($in['PROGR']);
                                    }
                                    foreach ($this->esams[$key] as $esam_corr => $es_val_corr) {
                                        #echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
                                        if ($es_val_corr['CORR'] == $esam && ($es_val_corr['CORR_ON_SEND'] != 'yes' || $es_val['RES'][$es_progr]['FINE'] == 1)) {
                                            #echo "<hr> Esame correlato per $esam : ".$esam_corr;
                                            $img = "to_be_comp.gif";
                                            //											print_r($es_val_corr);
                                            #echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
                                            if ($es_val_corr['RES'][$es_progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                                            if ($es_val_corr['RES'][$es_progr]['INIZIO'] == '1') $img = "saved.gif";
                                            if ($es_val_corr['RES'][$es_progr]['FINE'] == '1') $img = "submitted.gif";
                                            #$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
                                            $dtp = '';
                                            $date = "";
                                            $date = $es_val_corr['RES'][$es_progr]['INSERTDT'];
                                            #echo "<hr>$date<hr>";
                                            if ($date != '') $dtp = "($date)";
                                            $nome_esame = $es_val_corr['TESTO'] . " $dtp";
                                            #if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val_corr['XML']."\">invia e-query";
                                            #$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
                                            #$close_href="</a>";
                                            //										$this->body.="
                                            //									<tr>
                                            //										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
                                            //										</td>
                                            //										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
                                            //										</td>
                                            //										<!--td class=\"sc4bis\" align=\"center\">
                                            //										</td>
                                            //										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
                                            //										</td-->
                                            //										</tr>
                                            //										";
                                            $in['VISITNUM'] = $key;
                                            $in['ESAM'] = $esam_corr;
                                            $in['PROGR'] = $es_progr;
                                            $xml_form = new xml_form();
                                            $xml_form->xml_form_by_file($xml_dir . '/' . $es_form[$key][$esam_corr]);
                                            if ($xml_form->closed_form()) {
                                                $xml_form->close_form();
                                                $esam_html .= "" . $xml_form->body;
                                                $tab = "<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
                                                $esam_html = preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
                                            }
                                            unset($in['VISITNUM']);
                                            unset($in['ESAM']);
                                            unset($in['PROGR']);
                                        }
                                    }
                                }

                            }

                        }
                    }
                }
            }
            $this->body .= "</table>";
        }
        /*PARTE RELATIVA ALLA CHIUSURA DELLA VISITA
		if ($in['VISITNUM']!=''){
		$query="select min(fine) as fine, min(visitclose) as vclose from ".$GLOBALS['service']."_COORDINATE where {$this->PK_SERVICE}='".$in[$this->PK_SERVICE]."' and VISITNUM='".$in['VISITNUM']."'";
		$sql->set_sql($query);
		$sql->exec();//commentata
		$sql->get_row();
		if($sql->row['FINE']=='1' && $sql->row['VCLOSE']!='1') $this->body.="
		<table border=0 cellspacing=0 cellpadding=0 align=center><tr><td>
		<form method=post action='index.php' align=center>
		<input type='hidden' name=$this->PK_SERVICE value='".$in[$this->PK_SERVICE]."'>
		<input type='hidden' name='VISITNUM' value='".$in['VISITNUM']."'>
		<input type='hidden' name='CENTER' value='".$in['CENTER']."'>
		<input type='hidden' name='exams' value='visite_exams.xml'>
		<input type='submit' name='close_visit' value='Close Visit' align=center>
		</form>
		</td></tr></table>
		";
		}*/
        /*$this->body.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Vista individuale</a>
		<br/><a href=\"index.php?exams=visite_exams.xml&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Individual Patient Exam List</a>
		<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Procuratori registrati </a></p>";
		*/

        $this->body .= $esam_html;

        return $this->body;
    }

    /**
     * Restituisce il codice html delle form raggrupate
     *
     * @return string
     */
    function esams_group_html()
    {
        $agg_param=null;
        $in = $this->session_vars;
        $conn = $this->conn;


        $query = "select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato, eq_action from " . $GLOBALS['service'] . "_COORDINATE where {$this->PK_SERVICE}=:pk_service order by progr";
        #echo $query;
        $bind_pk['PK_SERVICE'] = $in[$this->PK_SERVICE];
        $sql = new query($conn);
        //$sql->set_sql($query);
        $sql->exec($query, $bind_pk);//binded
        while ($sql->get_row()) {
            if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])) {
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE'] = $sql->row['FINE'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO'] = $sql->row['INIZIO'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT'] = $sql->row['INSERTDT'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO'] = $sql->row['ABILITATO'];
                $this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION'] = $sql->row['EQ_ACTION'];
            }
        }
        #print_r
        foreach ($this->group[$in['GROUP']]['VISIT'] as $grp => $val_grp) {
            #echo "<hr>$grp<hr>";
            $in['VISITNUM'] = $grp;
            foreach ($this->visitnums as $key => $val) {
                if (!isset($in['VISITNUM']) || $in['VISITNUM'] == $key) {
                    $this->body .= "
			  		<table class=\"bordi\" border=\"0\" bordercolor=\"#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"100%\">
		        	<tr>
								<td class=\"int\" align=\"left\"><a href=\"index.php?{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&amp;VISITNUM=" . $val['NUMBER'] . "&exams=" . $GLOBALS['visit_structure_xml'] . "\" class=\"sc2b\">" . $val['TEXT'] . "</a></td>
							</tr>
							</table>
							<table class=\"tabgrigia\" align=\"center\" border=\"0\" cellspacing=\"0\" width=\"95%\">
						      <!--tr>
						      <td class=\"sc4bis\" align=\"center\" width=\"15%\"><b>Status</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"35%\"><b>Form name</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Due date</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Received date</b></td>
						     </tr-->
							";
                    foreach ($this->esams[$key] as $esam => $es_val) {
                        $nome_form = $es_val['TESTO'];
                        //ESAMI NON PROGRESSIVO
                        if ((!isset($es_val['PROGR']) || $es_val['PROGR'] != 'yes') && !isset($es_val['CORR'])) {
                            $img = "to_be_comp.gif";
                            $progr = 1;
                            if ($es_val['PROGR'] != '') $progr = $es_val['PROGR'];
                            #echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
                            if ($es_val['RES'][$progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                            if ($es_val['RES'][$progr]['INIZIO'] == '1') $img = "saved.gif";
                            if ($es_val['RES'][$progr]['FINE'] == '1') $img = "submitted.gif";
                            $date = $es_val['RES'][$progr]['INSERTDT'];
                            $nome_esame = $es_val['TESTO'];
                            if ($es_val['RES'][$progr]['ABILITATO'] == '1' || $es_val['RES']['']['ABILITATO'] == '1') {
                                $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$progr&amp;form=" . $es_val['XML'] . "\">";
                                $close_href = "</a>";
                                $this->body .= "
										<tr>
											 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href" . $es_val['TESTO'] . "$close_href<br/>
											</td>
											<td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
											</td>
											</tr>
											";
                            }
                        } //ESAMI PROGRESSIVI
                        else {
                            if (isset($es_val['RES']) && !isset($es_val['CORR'])) {
                                foreach ($es_val['RES'] as $es_progr => $progr_vals) {
                                    #echo "<hr>$es_progr - ";
                                    #print_r($progr_vals);
                                    if ($es_val['RES'][$es_progr]['INIZIO'] == '1') {
                                        #echo "<hr>2 $es_progr - ";
                                        if ($es_val['RES'][$es_progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                                        if ($es_val['RES'][$es_progr]['INIZIO'] == '1') $img = "saved.gif";
                                        if ($es_val['RES'][$es_progr]['FINE'] == '1') $img = "submitted.gif";
                                        $date = $es_val['RES'][$es_progr]['INSERTDT'];
                                        $nome_form = $es_val['TESTO'] . " ($date)";
                                        if ($es_val['RES'][$es_progr]['ABILITATO'] == '1') {
                                            $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=" . $es_val['XML'] . "{$agg_param}\">";
                                            $close_href = "</a>";
                                            $this->body .= "
																<tr>
																	 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href" . $es_val['TESTO'] . "($date) $close_href<br/>
																	</td>
																	<td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
																	</td>
																</tr>
															";

                                        }

                                        foreach ($this->esams[$key] as $esam_corr => $es_val_corr) {
                                            #echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
                                            if ($es_val_corr['CORR'] == $esam && ($es_val_corr['CORR_ON_SEND'] != 'yes' || $es_val['RES'][$es_progr]['FINE'] == 1)) {
                                                # echo "<hr> Esame correlato per $esam : ".$esam_corr;
                                                $img = "to_be_comp.gif";
                                                #echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
                                                if ($es_val_corr['RES'][$es_progr]['INIZIO'] == '0') $img = "to_be_comp.gif";
                                                if ($es_val_corr['RES'][$es_progr]['INIZIO'] == '1') $img = "saved.gif";
                                                if ($es_val_corr['RES'][$es_progr]['FINE'] == '1') $img = "submitted.gif";
                                                #$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
                                                $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=" . $es_val_corr['XML'] . "\">";
                                                $close_href = "</a>";
                                                $this->body .= "
										<tr>
											 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href" . $es_val_corr['TESTO'] . "($date) $close_href<br/>
											</td>
											<td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
											</td>
											</tr>
											";
                                            }
                                        }
                                    }

                                }
                                $next_progr = $es_progr + 1;
                                $href = "<a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;&amp;form=" . $es_val['XML'] . "{$agg_param}\">";
                                $close_href = "</a>";
                                $this->body .= "
													<tr>
														<td class=\"sc4bis\" align=\"center\"><a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=" . $es_val['XML'] . "{$agg_param}\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
														</td>
														<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=" . $in['CENTER'] . "&amp;{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=" . $es_val['XML'] . "{$agg_param}\">New " . $es_val['TESTO'] . "</a><br/>
														</td>
														<td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\">&nbsp;<br/>
														</td>
													</tr>
											";
                            }
                        }
                    }
                }
            }
        }
        $this->body .= "</table><p align=right><a href=\"index.php?list=patients_list.xml&{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&CENTER=" . $in['CENTER'] . "\">Menu Procuratore</a>
	  	<br/><a href=\"index.php?exams=" . $GLOBALS['visit_structure_xml'] . "&{$this->PK_SERVICE}=" . $in[$this->PK_SERVICE] . "&CENTER=" . $in['CENTER'] . "\">Vista individuale</a>
	  	<br/><a href=\"index.php?list=patients_list.xml&CENTER=" . $in['CENTER'] . "\">Lista Procure</a></p>";
        return $this->body;
    }

    function eQProgrPending($key, $esam, $vprogr = null, $progr = null)
    {
        global $service;
        $in = $this->session_vars;
        $conn = $this->conn;
        $xml_dir = $this->xml_dir;
        $config_service = $this->config_service;
        if ($this->config_service['eQuery'] == 1 && $this->integrazione->eq_enabled) {
            $agg_where = '';
            if ($vprogr != null) $agg_where = " and VISITNUM_PROGR={$vprogr}";
            if ($progr != null) $agg_where .= " and PROGR={$progr}";
            $sql_query = "select count(*) as c from {$service}_eqfield where
				esam={$esam}
				and visitnum=$key
				$agg_where
				and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
				and statofield in (0,2)
			";
            $sql2 = new query($this->conn);
            $sql2->get_row($sql_query);

            if ($sql2->row['C'] > 0) {
                return true;
            } else return false;
        } else return false;


    }


}

?>
