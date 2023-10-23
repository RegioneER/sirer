<?

/**
 * Classe Field
 *
 * @package Fields
 */
class field extends field_prototype
{

    function field($xml_form=null, $i=null, $conn = null, $inputval = null, $in = null, $service = null, $errors = null)
    {
        if (!isset($conn)) global $conn;
        if (!isset($inputval)) global $inputval;
        if (!isset($in)) global $in;
        if (!isset($service)) global $service;
        if (!isset($errors)) global $errors;
        parent::field_prototype($conn, $xml_form, $i, $in, $inputval, $service, $errors);
    }

}


/**
 * Classe prototipo
 *
 */
class field_prototype
{

    var $attributes;
    var $values;
    var $cols_form;
    var $testo;
    var $html;
    var $field_stmt;
    var $values_stmt;
    var $id;
    var $validata = true;
    var $condition_passed = true;
    var $xml_form;
    var $input_txt;
    var $input_field;
    var $session_vars;
    var $db_vars;
    var $errors;
    var $service;
    var $conn;
    var $onload;
    var $check_js;
    var $invia_js;
    var $salva_js;
    var $inrevisione_js;
    var $config_service;
    var $edit_tag;
    var $script;
    var $class;

    /**
     * Costruttore
     *
     * @param dbcon $conn
     * @param String $xml_form
     * @param number $i
     * @param array $session_vars
     * @param array $db_vars
     * @param String $service
     * @param array $errors
     * @return field_prototype
     */
    function field_prototype($conn, $xml_form, $i, $session_vars, $db_vars, $service, $errors)
    {
        $this->session_vars = $session_vars;
        $this->db_vars = $db_vars;
        $this->errors = $errors;
        $this->xml_form = $xml_form;
        $this->service = $service;
        $this->conn = $conn;
        if ($xml_form) {
            $this->cols_form = $xml_form->form['COLS'];
        } else {
            $this->cols_form = 1;
        }
        $this->config_service = $this->xml_form->config_service;
        foreach ($xml_form->fields[$i] as $key => $val) {
            switch ($key):
                case "TESTO":
                    $this->testo = $val;
                    break;
                case "VALUE":
                    $this->values = $val;
                    break;
                default:
                    $this->attributes[$key] = $val;
            endswitch;
        }
        //$this->testo=mlOut($this->testo);
        //TODO: Tentiamo senza inizializzazione (o false invece di ""?)
        /*
        if (!isset($this->attributes['SEND'])){
            $this->attributes['SEND']="";
        }
        if (!isset($this->attributes['SAVE'])){
            $this->attributes['SAVE']="";
        }
        if (!isset($this->attributes['SEND_MATCH'])){
            $this->attributes['SEND_MATCH']="";
        }
        */

        if ($this->attributes['BYTB'] != '' && !$this->session_vars['avoidBytb']) $this->fields_value_bytb($this->attributes['BYTB']);
        if ($this->attributes['VAR']) $this->id = $this->attributes['VAR'];
        else {
            $this->id = $this->attributes['NAME'];
            $this->attributes['TB'] = 'no';
        }
        if ($this->testo != "") {
            $fileName = str_replace("\.xml", "", $this->xml_form->filename);
            $fileName = preg_replace("!\.xml!", "", $fileName);
            $this->testo = mlOut($fileName . "." . $this->id, $this->testo);
            $this->testo_ctx_help = mlOut($fileName . ".contextHelp." . $this->id, "__EMPTY_STRING__");
        }
        if ($this->attributes['SEND_MATCH'] != '' && $this->attributes['SEND'] != '') {
            if (!preg_match("{$this->attributes['SEND_MATCH_EXPR']}", $this->session_vars[$this->attributes['SEND_MATCH']])) unset($this->attributes['SEND']);
        }
        if (strtolower(trim($this->attributes['SEND'])) == 'obbligatorio' && ($this->attributes['CONDITION'] == '' || $this->attributes['ASTERISCO'] == 'yes' || ($this->config_service['SHOW_MANDATORY_ON_HIDE'] != '' && $this->attributes['HIDE'] == 'yes'))) {
            $this->testo .= "<span style=\"color:red;\">*</span>";
        }
        if (isset($this->errors[$this->id])) {
            $this->testo .= "<br><span style=\"color:red;\">" . $this->errors[$this->id] . "</span>";
        }
        if ($this->config_service['auto_facoltativi'] && $this->attributes['TB'] != 'no' && $this->attributes['SAVE'] == '' && $this->attributes['VAR_TYPE'] == 'number' && $this->attributes['VAR'] != '' && $this->attributes['TYPE'] != 'hidden') {
            $this->attributes['SAVE'] = 'facoltativo';
        }
        if ($this->config_service['auto_facoltativi'] && $this->attributes['TB'] != 'no' && $this->attributes['SEND'] == '' && $this->attributes['VAR_TYPE'] == 'number' && $this->attributes['VAR'] != '' && $this->attributes['TYPE'] != 'hidden') {
            $this->attributes['SEND'] = 'facoltativo';

        }
        if (!isset($this->attributes['DEF'])) {
            $this->attributes['DEF'] = "";
        }
        $this->attributes['DEF'] .= $this->audit_trail_txt();
    }

    /**
     * Costruisce ill codice html del campo in compilazione
     *
     * @param boolean $equery
     */
    function make_open_html($equery = false)
    {
        $eQ_area = null;
        $eQ_DM = null;
        $eQ_DM = null;
        $testo = null;
        $function_to_call = 'open_';
        $in = $this->session_vars;
        $inputval = $this->db_vars;

        if (isset($_GET['DEBUG'])) {
            $dbg = debug_backtrace();
            foreach ($dbg as $k => $v) {
                echo "FILE: {$v['file']}:{$v['line']} in function {$v['function']}<br/>";
            }
            echo "<hr/>";
        }

        if (strtolower($this->config_service['lang']) == 'it') {
            $testi['Valore Cambiato'] = "Valore Cambiato (vecchia selezione:";
            $testi['Valore Aggiunto'] = "Valore Aggiunto";
            $testi['Campo Commentato'] = "Campo Commentato";
        } else {
            $testi['Valore Cambiato'] = "Changed value (old selection: ";
            $testi['Valore Aggiunto'] = "Added value ";
            $testi['Campo Commentato'] = "Annotated Field";
        }

        if (isset($this->values) and !is_array($this->values)) $value = $this->values;
        if (isset($inputval[$this->attributes['VAR']])) $value = $inputval[$this->attributes['VAR']];
        if (isset($in[$this->attributes['VAR']])) $value = $in[$this->attributes['VAR']];
        if ($this->attributes['BYTB'] != '') $this->fields_value_bytb($this->attributes['BYTB']);
        $value = htmlentities($value, ENT_QUOTES, 'UTF-8');
        //echo "STEP1: {$this->input_field}<br/>";
        if ($this->attributes['PRIORITY_BYTB'] == 'yes') {
            if (is_array($this->values)) {
                foreach ($this->values as $curValue) {
                    $value = $curValue;
                }
            } else if ($this->values != '') {
                $value = $this->values;
            }
        }
        //echo "STEP1.1: {$this->input_field}<br/>";
        if ($in ['USER_TIP'] == 'DM' && $this->attributes['NO_DM_CHANGE'] != '') {
            $function_to_call_no_dm = "close_";
            $this->{$function_to_call_no_dm}($value);
        } else if (method_exists($this, $function_to_call)) $this->{$function_to_call}($value);
        //echo "STEP2: {$this->input_field}<br/>";
        $cols = $this->attributes['COLS'] + 0;
        if ($cols == 0) $cols = 1;

        if ($equery && $this->attributes['DISABLED'] != "yes") {

            if ($this->input_field != '' && $this->attributes['TYPE'] != 'hidden' && $this->attributes['TYPE'] != 'text' && $this->attributes['TYPE'] != '') {
                $testo_changed = '';
                $img_eq = '';
                if ($this->xml_form->old_values[$this->id] != $this->xml_form->tb_vals[$this->id]) {
                    if ($this->attributes['TYPE'] == 'file_doc' || $this->attributes['TYPE'] == 'file_cme') {
                        if ($this->attributes['TYPE'] == 'file_cme') {
                            $prev = $this->CMELayer->queryPrevious($this->inputval[$this->attributes['VAR']]);
                            $this->xml_form->old_values_docs_nomi[$this->id] = $prev['NOME_FILE'];
                        }
                        if ($this->xml_form->old_values_docs_nomi[$this->id] != "")
                            $old_spec = "<br /><a class=\"normal_link\" href=\"WCA/download.php?id={$this->xml_form->old_values[$this->id]}\"><span><img src=\"../images/word.gif\" alt=\"documento vecchio \" />{$this->xml_form->old_values_docs_nomi[$this->id]}</span></a>";
                        else
                            $old_spec = "<h3 style=\"display:inline;text-decoration:underline;\">Valore aggiunto: Non era presente un allegato</h3>";
                    } else if ($this->attributes['TYPE'] == 'checkbox') {
                        if ($this->xml_form->old_values[$this->id] == "1")
                            $old_spec = "Selezionato";
                        else $old_spec = "Non selezionato";
                    } else if (isset($this->xml_form->old_values['D_' . $this->id])) {
                        $old_spec = $this->xml_form->old_values['D_' . $this->id];
                    } else $old_spec = $this->xml_form->old_values[$this->id];

                    $img_eq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";

                    $str_testo_agg = mlOut("System.field.valore_aggiunto", $testi['Valore Aggiunto']);
                    $str_testo_change = "(" . mlOut("System.field.valore_aggiunto", $testi['Valore Cambiato']) . " {$old_spec})";

                    if ($old_spec == '') {
                        $testo_changed = "<br/><p style='color:blue;font-weight:bold;'>$str_testo_agg</p>";
                    } else {
                        $testo_changed = "<br/><p style='color:red;font-weight:bold;'>$str_testo_change</p>";
                    }
                }

                //Classe unicamente per dirimere tipo di integrazioni CRO
                $intclass = new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['USER_PROFILE'], $this->session_vars ['USER_TIP']);

                if (isset($intclass->cro) && $intclass->cro) {
                    //echo "CRO INTEGRAZIONI!";
                    //CRO-Merge Start
                    //die("ABILEQDE: ".$_GET['ABILITA_EQ_DE']);
                    if (isset($_GET['ABILITA_EQ_DE'])) {
                        //echo "MA VADO QUA??";
                        $sql_eqfield = "select * from {$this->service}_eqfield eqfield, {$this->service}_eq eq where
                            eqfield.{$this->xml_form->config_service['PK_SERVICE']}={$this->session_vars[$this->xml_form->config_service['PK_SERVICE']]}
                            and eqfield.esam={$this->session_vars['ESAM']}
                            and eqfield.visitnum={$this->session_vars['VISITNUM']}
                            and eqfield.visitnum_progr={$this->session_vars['VISITNUM_PROGR']}
                            and eqfield.progr={$this->session_vars['PROGR']}
                            and eqfield.FIELD='{$this->attributes['VAR']}'
                            and eq.equery_int=eqfield.eq_int
                            and eqfield.statofield in (0,2)
                        ";
                        //						echo $sql_eqfield;
                        $sql2 = new query ($this->conn);
                        $sql2->set_sql($sql_eqfield);
                        $sql2->exec();
                        $sql2->get_row();
                        $nota_de = $sql2->row['NOTE_DE'];
                        $nota_dm = $sql2->row['NOTE'];
                        $statofield = $sql2->row['STATOFIELD'];
                        //					echo $statofield;
                        switch ($statofield) {
                            case "0":
                                //					        echo "eQ pending da DM";
                                $eQ_DM = "<a style='color:#ff7d00;font-weight:bolder;font-size:1.5em' href=\"#\"
                                        onclick=\"show_hide('EQAREA_{$this->attributes['VAR']}');return false;\"><i class=\"fa fa-comments\"></i></a><br>
                                        <div style='display:none;border:1px solid #ff7d00; background:yellow;width:180px;height:60px;  overflow:auto;'  id='EQAREA_{$this->attributes['VAR']}' name='EQAREA_{$this->attributes['VAR']}' >$nota_dm</div>
                                        ";

                                $eQ_matita = "<a href=\"#\" onclick=\"
                                            show_hide('view_field_{$this->id}');
                                            show_hide('mod_field_{$this->id}')
                                            show_hide('EQAREADE_{$this->attributes['VAR']}');
                                            return false;
                                        \"><i class=\"fa fa-pencil-square blue\" style=\"font-size:1.2em;\"></i></a>";

                                $eQ_area = "<textarea cols='20' rows='2' style='display:none;' id='EQAREADE_{$this->attributes['VAR']}' name='EQAREADE_{$this->attributes['VAR']}' ></textarea>
                                        ";
                                $this->attributes['HIDE'] = "no";
                                break;
                            case "2":
                                //					        echo "eQ in corso di approvazione";
                                if ($this->xml_form->old_values[$this->id] != $this->xml_form->tb_vals[$this->id] && $nota_de != '') {
                                    if (isset($this->xml_form->old_values['D_' . $this->id])) {
                                        $old_spec = $this->xml_form->old_values['D_' . $this->id];
                                    } else $old_spec = $this->xml_form->old_values[$this->id];
                                    //echo $this->attributes['VAR'];
                                    if ($this->attributes['TYPE'] == "date_hyper") {
                                        if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 0, 2) != 'OK') {
                                            $dd = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 0, 2);
                                        } else {
                                            $dd = substr($this->xml_form->old_values[$this->id], 0, 2);
                                        }
                                        if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 2, 2) != 'OK') {
                                            $mm = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 2, 2);
                                        } else {
                                            $mm = substr($this->xml_form->old_values[$this->id], 2, 2);
                                        }
                                        if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 4, 2) != 'OK') {
                                            $yyyy = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 4, 2);
                                        } else {
                                            $yyyy = substr($this->xml_form->old_values[$this->id], 4, 4);
                                        }
                                        $old_spec = $dd . $mm . $yyyy;
                                    }
                                    $img_eq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";

                                    $str_testo_agg = mlOut("System.field.valore_aggiunto", $testi['Valore Aggiunto']);
                                    $str_testo_change = "(" . mlOut("System.field.valore_aggiunto", $testi['Valore Cambiato']) . " {$old_spec})";

                                    if ($old_spec == '') {
                                        $testo_changed = "<br/><p style='color:blue;font-weight:bold;'>$str_testo_agg</p>";
                                    } else
                                        $testo_changed = "<br/><p style='color:red;font-weight:bold;'>$str_testo_change</p>";
                                } elseif ($nota_de != '' && $this->xml_form->old_values[$this->id] == $this->xml_form->tb_vals[$this->id]) {
                                    $img_eq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
                                    $testo_changed = "<br/><p style='color:blue;font-weight:bold;'>" . mlOut("System.field.campo_commentato", $testi['Campo Commentato']) . "</p>";
                                }
                                $this->attributes['HIDE'] = "no";
                                break;
                            default:
                                //echo "PROVAPROVA0202!";
                                //					    	echo "default: DE vuol fare eQ su campi non pending";
                                $eQ_matita = "<a href=\"#\" onclick=\"
                                            show_hide('view_field_{$this->id}');
                                            show_hide('mod_field_{$this->id}')
                                            show_hide('EQAREADE_{$this->attributes['VAR']}');
                                            return false;
                                        \"><i class=\"fa fa-pencil-square blue\" style=\"font-size:1.2em;\"></i></a>";

                                $eQ_area = "<textarea cols='20' rows='2' style='display:none;' id='EQAREADE_{$this->attributes['VAR']}' name='EQAREADE_{$this->attributes['VAR']}' ></textarea>
                                        ";
                                break;
                        }
                        $this->close_($value);
                        $close_field = $this->input_field;
                        $this->open_($value);

                        //if ($this->attributes['TYPE'] != "" && $this->attributes['TYPE'] != "hidden" && $this->attributes['TYPE'] != "text") {

                        $this->input_field = "
								<table width=\"100%\" border=0>
									<tr>
										<td valign=top>
								<span id='view_field_{$this->id}'>$close_field</span>
								<span id='mod_field_{$this->id}' style=\"display:none\">{$this->input_field}</span>
										</td>
										<td valign=top align=right>
										$img_eq
										</td>
										<td valign=top align=right>
										$eQ_area
										</td>
									</tr>
								</table>
								";
                        $this->input_txt .= "&nbsp; $eQ_matita $testo_changed";
                        $this->input_txt = "
								<table width=\"100%\" border=0>
									<tr>
										<td valign=top align=left>
										$img_eq
										</td>
										<td valign=top align=left>
										$eQ_DM
										</td>
										<td valign=top align=right>
										{$this->input_txt}
										</td>
									</tr>
								</table>
								";
                        //}
                    }
                    //End of CRO-Merge
                } else {
                    $this->close_($value);
                    $close_field = $this->input_field;
                    $this->open_($value);
                    $this->input_field = "
                        <table width=\"100%\" border=0>
                            <tr>
                                <td valign=top>
                        <span id='view_field_{$this->id}'>$close_field</span>
                        <span id='mod_field_{$this->id}' style=\"display:none\">{$this->input_field}</span>
                                </td>
                                <td valign=top align=right>
                                $img_eq
                                </td>
                                <td valign=top align=right>
                                $eQ_area
                                </td>
                            </tr>
                        </table>
                        ";
                    $this->input_txt .= "&nbsp; $testo_changed <a href=\"#\" onclick=\"
                            show_hide('view_field_{$this->id}');
                            show_hide('mod_field_{$this->id}');
                            return false;
                        \">";
                    $this->input_txt .= "
                            (GLOB)<img src=\"images/edit.png\">(/GLOB)</a>$testo_changed";
                    $this->input_txt = "(TAB?)
                        <table width=\"100%\" border=0>
                            <tr>
                                <td valign=top align=left>
                                $img_eq
                                </td>
                                <td valign=top align=left>
                                $eQ_DM
                                </td>
                                <td valign=top align=right>
                                {$this->input_txt}
                                </td>
                            </tr>
                        </table>(/TAB?)
                        ";
                }
            }

        }
        if ($this->attributes['TYPE'] == 'hidden') {
            $colspan = $cols * 2;
            $this->html = $this->input_field;
        }
        if ($this->attributes['CONDITION'] != '') {
            $function_to_call = 'open_condition';
            if (method_exists($this, $function_to_call)) $this->{$function_to_call}($this->attributes['CONDITION']);
        }
        if ($this->attributes['COMPILA_VAL'] != '') {
            $function_to_call = 'open_compila';
            if (method_exists($this, $function_to_call)) $this->{$function_to_call}($this->attributes['COMPILA_VAL']);
        }
        $inputClass = "input";
        $txtClass = "destra";

        if (isset($this->xml_form->form['INPUTCLASS'])) {
            $inputClass = $this->xml_form->form['INPUTCLASS'];
        }
        if (isset($this->xml_form->form['TXTCLASS'])) {
            $txtClass = $this->xml_form->form['TXTCLASS'];
        }
        if (count($this->attributes) > 0) {
            $doneSave = false;
            $doneSend = false;
            foreach ($this->attributes as $key => $val) {
                if ($key != 'CONDITION') {
                    if (false && $this->config_service['jquery2'] && method_exists($this, 'open_j' . $key)) $function_to_call = 'open_j' . $key;
                    else $function_to_call = 'open_' . $key;
                    //echo ("{$function_to_call}::{$val}<br/>\n");
                    if ($function_to_call != 'open_condition' && method_exists($this, $function_to_call)) {
                        $this->{$function_to_call}($val);
                        if (strtoupper($key) == "SAVE") {
                            $doneSave = true;
                        }
                        if (strtoupper($key) == "SEND") {
                            $doneSend = true;
                        }
                    }
                }
            }
            //echo "FIELD: {$this->attributes['VAR']} -> {$doneSave},{$doneSend}<br/>";
            if (
                (strtolower($this->attributes["TYPE"]) == "textbox" && isset($this->attributes["VAR_TYPE"]) && strtolower($this->attributes["VAR_TYPE"]) != "text")
                || strtolower($this->attributes["TYPE"]) == "date_cal"
            ) {
                //echo "CAMPO TEXTBOX NUMERICO override {$this->attributes['VAR']}<br/>";
                if (!$doneSave) {
                    $function_to_call = 'open_save';
                    //echo ("{$function_to_call}::facoltativo<br/>\n");
                    $this->{$function_to_call}("facoltativo");
                }
                if (!$doneSend) {
                    $function_to_call = 'open_send';
                    //echo ("{$function_to_call}::facoltativo<br/>\n");
                    $this->{$function_to_call}("facoltativo");
                }
            }
        }
        if (isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) {
            $colspan = $cols * $this->attributes['COLSPAN'];
            if ($this->input_field == '') $this->html = $this->input_txt;
            else {
                $html_parser = new HTML_Parser();
                $html_parser->setAttribute("colspan", $colspan);
                if (isset($this->attributes['TXTWIDTH'])) {
                    $content = "
					<table border=\"0\" cellspacing=\"3\" cellpadding=\"0\" width=\"100%\" ><tr>
					<td valign=top class='$txtClass' width=\"{$this->attributes['TXTWIDTH']}\">$this->input_txt</td>
					<td valign=top class='$inputClass'>$this->input_field</td>
					</tr>
					</table>";
                    $html_parser->setContent($content);
                } else {
                    $html_parser->setAttribute("class", $inputClass);
                    //					$html_parser->setAttribute("align", "right");
                    $html_parser->setContent($this->input_txt . $this->input_field);
                }
                $html_parser->setType("TD");
                $this->html = $html_parser->print_();
            }
        } else {
            if ($this->attributes['TYPE'] != 'hidden') {


                if (!isset($this->attributes['COLS'])) {
                    $this->attributes['COLS'] = 1;
                }
                if ($this->xml_form->form['COLS'] != $this->attributes['COLS']) {
                    $width = round($this->attributes['COLS'] / $this->xml_form->form['COLS'] * 100);
                    $styleAdd = " style=\"float:left;width:{$width}%\"";
                } else $styleAdd = "";
                $span = 6;
                $labelstyle = "";
                if ($this->attributes['SPAN'] == "yes") {
                    $span = 12;
                    $labelstyle = ' style="text-align: left;" ';
                }
                //echo "{$this->attributes['VAR']}: $span<br/>";
                //print_r($this->xml_form->form);
                //die();
                $helpCtx = "";
                if ($this->testo_ctx_help != '') {
                    $helpCtx = '<span id="help-ctx-' . $this->id . '" class="help-button" data-rel="popover" data-trigger="hover" data-placement="right">?</span>';
                    $helpCtx .= '<span id="help-ctx-' . $this->id . '-content" style="display:none"><i class="blue fa fa-info-circle"></i>&nbsp;' . $this->testo_ctx_help . '</span>';
                }
                //TODO: Eventualmente rimuovere variabile $labelstyle
                $this->html = "
								<div id=\"tr_{$this->attributes['VAR']}\" {$styleAdd}>
									<label class=\"col-sm-{$span} control-label\" for=\"field_{$this->attributes['VAR']}\" $labelstyle >$this->input_txt</label>
									<div class=\"col-sm-{$span} no-padding-left\" id=\"field_{$this->attributes['VAR']}\" style=\"\">
										{$this->input_field}{$helpCtx}
									</div>
								</div>
									";
            }
        }
        if ($this->attributes['TYPE'] == 'data' && $this->salva_js == '') {
            $dcod = '00';
            if ($this->attributes['DCONT'] == 'yes') $dcod = '16';
            if ($this->attributes['DSPEC'] == 'yes') $dcod = '03';
            if ($this->attributes['DCONT'] == 'yes' && $this->attributes['DSPEC'] == 'yes') $dcod = '31';
            $this->salva_js .= "
				c1+='<<fd" . $dcod . "###" . $this->attributes['VAR'] . "###" . $testo . ">>';";
        }
        if ($this->attributes['TYPE'] == 'data' && $this->invia_js == '') {
            $dcod = '00';
            if ($this->attributes['DCONT'] == 'yes') $dcod = '16';
            if ($this->attributes['DSPEC'] == 'yes') $dcod = '03';
            if ($this->attributes['DCONT'] == 'yes' && $this->attributes['DSPEC'] == 'yes') $dcod = '31';
            $this->invia_js .= "
				c1+='<<fd" . $dcod . "###" . $this->attributes['VAR'] . "###" . $testo . ">>';";
        }
        if ($this->attributes['DISABLED'] != '') {
            $onload = $this->onload;
            $onload .= $this->check_js;
            //Compatibilita a ritroso:
            $GLOBALS['onload'] = $onload;
        }
    }


    /**
     * Restituisce il codice html del campo in compilazione
     *
     * @param String $value
     */
    function open_($value)
    {
        $txt = null;
        $this->input_txt = $txt; //TODO: Questo è da controllare!
        $in = $this->session_vars;
        $txt = $this->testo;
        $this->input_txt = $txt;
        if ($this->attributes['ONLY_AF'] != '' && $in['make_appl_form'] == '') $this->input_txt = '';
        if ($this->attributes['PARSE_TXT_VALUE'] != '') $this->input_txt = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $this->input_txt);
        return;
    }

    /**
     * Costruisce il codice html del campo in visualizzazione
     *
     * @param String $value
     */
    function close_($value)
    {
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        //$ret='<tr id="'.$this->attributes['NAME'].'" style="display:">';
        $txt = $this->testo;
        if ($inputval[$this->attributes['CONDITION']] == $this->attributes['CONDITION_VALUE'])
            $this->input_txt = $txt;
        if ($this->attributes['NO_VIS'] != '') $this->input_txt = '';
        if ($this->attributes['ONLY_AF'] != '' && $in['make_appl_form'] == '') $this->input_txt = '';
        if ($this->attributes['PARSE_TXT_VALUE'] != '') $this->input_txt = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $this->input_txt);
        return;
    }


    /**
     * Costruisce un array con i valori da inserire in DB
     *
     */
    function insert_stmt()
    {
        $val = null;
        //verifica per crypto
        if ($this->session_vars ['USER_TIP'] == 'DM' && ($this->attributes['NO_DM_CHANGE'] != '' || $this->attributes['CRYPTO'] != '')) {
            return;
        }
        $in = $this->session_vars;
        if ($this->attributes['VAR_TYPE'] == 'text')
            $controllo = "t";
        else {
            if ($this->attributes['FM_CODE']) {
                $fm = $this->attributes['FM_CODE'];
                if (strtoupper($this->config_service['lang']) == 'IT') {
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NA') $in[$this->attributes['VAR']] = -9911;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NC') $in[$this->attributes['VAR']] = -9911; // utilizzare fmweb Passport
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NN') $in[$this->attributes['VAR']] = -9922;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'ND') $in[$this->attributes['VAR']] = -9933;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NP') $in[$this->attributes['VAR']] = -9944;
                    //if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
                    //if (strtoupper($in[$this->attributes['VAR']])=='ALTRO') $in[$this->attributes['VAR']]=-9900;
                } else {
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NA') $in[$this->attributes['VAR']] = -9911;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NC') $in[$this->attributes['VAR']] = -9911; // utilizzare fmweb Passport
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NK') $in[$this->attributes['VAR']] = -9922;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'ND') $in[$this->attributes['VAR']] = -9933;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NP') $in[$this->attributes['VAR']] = -9944;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'TE') $in[$this->attributes['VAR']] = -9955;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'OT') $in[$this->attributes['VAR']] = -9900;
                }
            } else
                $fm = "00";

            if ($this->attributes['VAR_STYPE'] == 'int')
                $controllo = "np" . $fm;
            else if ($this->attributes['VAR_STYPE'] == 'neg') $controllo = "na" . $fm;
            else if ($this->attributes['VAR_STYPE'] == 'real') $controllo = "xa" . $fm;
            else $controllo = "xp" . $fm;
            if ($val != 'obbligatorio') $controllo = "f" . $controllo;
        }
        if ($this->attributes['TB'] != 'no') {
            $this->field_stmt[0] = $this->attributes['VAR'];
            $value = $in[$this->attributes['VAR']];
            $value = str_replace("\\\"", "\"", $value);
            $value = str_replace("&quot;", "\"", $value);
            //$value=$in[$this->attributes['VAR']];
            //$value=str_replace("\\\"", "\"", $value);
            $this->value_stmt[0] = $value;
        }
        return;
    }

    /**
     * Controlla se il campo in tb  allineanto con quello definito nell'XML
     *
     * @return array
     */
    function allinea_db()
    {
        if ($this->attributes['TB'] != 'no') {
            if ($this->attributes['VAR_TYPE'] == 'number') $type_field = 'NUMBER';
            else $type_field = "VARCHAR2({$this->attributes['VAR_SIZE']})";
            $ret[0] = "{$this->attributes['VAR']} {$type_field}";
            return $ret;
        } else return;
    }

    /**
     * Effettua i controlli lato server e costruisce i controlli lato client sul campo condizionato
     *
     * @param String $val
     */
    function open_condition($val)
    {
        if ($this->config_service['jquery'] && method_exists($this, "open_jcondition")) return $this->open_jcondition($val);
        if ($this->db_vars == '') {
            $this->db_vars = $_GET;
        }
        $var_cond = $val;
        $this->condition_passed = false;
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        $val_cond = $this->attributes['CONDITION_VALUE'];
        $hideJs = "
            $('#tr_" . $this->id . " select,#tr_" . $this->id . " input, #tr_" . $this->id . " textarea').prop('disabled', true);
            ";
        if ($this->attributes['HIDE'] == 'yes') {
            $hideJs = "
           if (document.getElementById('tr_" . $this->id . "')) document.getElementById('tr_" . $this->id . "').style.display='none';
           ";
        }

        if ($this->attributes['HIDE_THIS'] == 'yes') {
            $hideJs = "
            if (document.getElementById('cell_" . $this->id . "')) document.getElementById('cell_" . $this->id . "').style.display='none';
			if (document.getElementById('cell_input" . $this->id . "')) document.getElementById('cell_input" . $this->id . "').style.display='none';
          ";
        }

        //inizio nascondendo il campo
        $svuotoJs = "
            var reset{$this->id}Values={};
            var selector='[data-field-id=\"{$this->id}\"] input:not([name=\"\"]),[data-field-id=\"{$this->id}\"] textarea:not([name=\"\"]),[data-field-id=\"{$this->id}\"] select:not([name=\"\"])';
            (function(reset{$this->id}Values){
                $(selector).each(function(){
                    if ($(this).attr('type')=='radio' || $(this).attr('type')=='checkbox'){
                        if ($(this).prop('checked')) reset{$this->id}Values[$(this).attr('name')]=$(this).val();
                    }else {
                        reset{$this->id}Values[$(this).attr('name')]=$(this).val();
                    }
                });
            })(reset{$this->id}Values);
            
            $(selector).each(function(){
                if ($(this).attr('type')=='radio' || $(this).attr('type')=='checkbox'){
                    if ($(this).prop('checked'))  $(this).prop('checked', false);
                }else {
                    $(this).val('');
                }
            });
            
        ";
        $this->check_js .= "
		  valore=value_of('{$this->id}',0);
          var cond{$this->id}Passed=false;
		  {$svuotoJs}
		  {$hideJs}
					";
        $vals = explode(",", $val_cond); //separo i valori da controllare in array
        $this->condition_passed = false;
        foreach ($vals as $key => $value) { //Per ogni valore da controllare (basta che una condizione passi, per questo parto da situazione di condizione non passata)
            //Inizio controlli lato server
            if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
            else $value_to_control = $inputval[$var_cond];

            if ($value_to_control == $value) {
                $this->condition_passed = true;
            }
            //Fine controlli lato server
            $op = '==';
            if (preg_match("/\!/", $value)) {
                $value = str_replace("!", "", $value);
                $op = '!=\'\' && value !=';
            }
            if ($this->attributes['CONDITION_OP'] != '') {
                switch ($this->attributes['CONDITION_OP']) {
                    case "gt":
                        $op = ">";
                        break;
                    case "ge":
                        $op = ">=";
                        break;
                    case "lt":
                        $op = "<";
                        break;
                    case "le":
                        $op = "<=";
                        break;
                }
            }
            //Inizio controlli lato client
            $showJs = "
                if (document.getElementById('tr_" . $this->id . "')) $('#tr_" . $this->id . " select,#tr_" . $this->id . " input, #tr_" . $this->id . " textarea').prop('disabled', false);
                ";
            if ($this->attributes['HIDE'] == 'yes') {
                $showJs = "
                if (document.getElementById('tr_" . $this->id . "')) document.getElementById('tr_" . $this->id . "').style.display='';
					";
            }

            if ($this->attributes['HIDE_THIS'] == 'yes') {
                $showJs = "
                if (document.getElementById('cell_" . $this->id . "')) document.getElementById('cell_" . $this->id . "').style.display='';
				if (document.getElementById('cell_input" . $this->id . "')) document.getElementById('cell_input" . $this->id . "').style.display='';                            
							";
            }

            $resetFieldValue = "
                var selector='[data-field-id=\"{$this->id}\"] input:not([name=\"\"]),[data-field-id=\"{$this->id}\"] textarea:not([name=\"\"]),[data-field-id=\"{$this->id}\"] select:not([name=\"\"])';
                (function(reset{$this->id}Values){
                    $(selector).each(function(){
                        if ($(this).attr('type')=='checkbox'){
                            if (reset{$this->id}Values[$(this).attr('name')]){
                                $(this).prop('checked', true);
					}
                        }else if($(this).attr('type')=='radio') {
                            if (reset{$this->id}Values[$(this).attr('name')] && $(this).val()==reset{$this->id}Values[$(this).attr('name')]){
                                $(this).prop('checked', true);
					}
						} else {
                            $(this).val(reset{$this->id}Values[$(this).attr('name')]);
			}
                    });
                })(reset{$this->id}Values);

						";

            if (is_numeric($value)) {
                $rhLogical = "{$value}";
            } else {
                $rhLogical = "'{$value}'";
            }
            $this->check_js .= " \n
					value=value_of('$var_cond', '0');
		     if (value {$op} {$rhLogical}){
                cond{$this->id}Passed=true;
    			{$showJs}
                {$resetFieldValue}
             }
						";
            //Fine controlli lato client
        }
        $this->check_js .= "
        if (!cond{$this->id}Passed){
            {$svuotoJs}
					}
					";
        $this->html = "<tr id='tr_" . $this->id . "' style=\"display:\">" . $this->html . "</tr>";
    }


    /**
     * Gestisce la disabilitazione del campo
     *
     * @param String $value
     */
    function open_disabled($value)
    {
        $this->check_js .= "
				if(document.forms[0]." . $this->id . " && document.forms[0]." . $this->id . ".value!='')
					document.forms[0]." . $this->id . ".disabled=true;
			";
    }

    /**
     * Gestisce la disabilitazione del campo
     *
     * @param String $value
     */
    function open_disabled_always($value)
    {
        $this->check_js .= "
				if(document.forms[0]." . $this->id . ")
					document.forms[0]." . $this->id . ".disabled=true;
			";
    }

    function open_block_value($value)
    {
        if ($this->db_vars[$this->attributes['VAR']] != "")
            $this->check_js .= "
				if(document.forms[0]." . $this->id . ")
					document.forms[0]." . $this->id . ".disabled=true;
			";
    }


    /**
     * Controlli sul valore del campo (maggiore di )
     *
     * @param String $value
     */
    function open_max($value)
    {
        //TODO: mi sembra competamente sbagliata!!!!!
        $campi = null;
        $i = null;
        $val = null;
        if (preg_match("/\[/", $campi[$i])) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $campi[$i]);
            $this->controlli .= "
						value=value_of('" . $campo . "', '0');
						";
        } else {
            $this->controlli .= "value=$val;\n";
        }
        //traduzione del messaggio di alert in inglese
        if ($this->config_service['lang'] == "en")
            $alert_msg = "Warning the value must be greater than ";
        else
            $alert_msg = "Attenzione il valore deve essere maggiore di ";

        $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value>value) {
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";
    }


    /**
     * GENHD-42 gestione rangechecks per cro vmazzeo 20.02.2015
     */
    function open_rangecheck($rangechecks)
    {
        //print_r($rangechecks);
        foreach ($rangechecks as $key => $rangecheck) {
            $controlli_each_range = "//INIZIO CREAZIONE RANGE CHECK #" . $key . "_" . $this->id . "\n";
            $value = $rangecheck['CHECKVALUE'];
            $comparator = "";
            $level = $rangecheck['LEVEL'] == 'Soft' ? "confirm" : "alert";
            switch ($rangecheck['COMPARATOR']) {
                case 'LT':
                    $comparator = "<";
                    break;
                case 'LE':
                    $comparator = "<=";
                    break;
                case 'GT':
                    $comparator = ">";
                    break;
                case 'GE':
                    $comparator = ">=";
                    break;
                case 'EQ':
                    $comparator = "==";
                    break;
                case 'NE':
                    $comparator = "!=";
                    break;
            }
            $controlli_each_range .= "var value;\n";
            if (preg_match("/\[/", $value)) {
                $campo = trim(preg_replace("/\[(.*?)\]/e", "$1", $value));
                $controlli_each_range .= "
						value=value_of('" . $campo . "', '0');
						";

            } else {
                $value -= 0;
                $controlli_each_range .= "value=$value;\n";

            }
            if ($this->attributes ['VAR_TYPE'] == 'number') {
                $controlli_each_range .= "
					value=parseFloat(value);
					";
            }
            switch ($this->attributes['TYPE']) {
                case "date_cal":
                    $controlli_each_range .= "
					var data=new Date();
					giorno=document.forms[0]." . $this->attributes['VAR'] . "D.value;
					if(giorno=='NA' || giorno=='NK' || parseInt(giorno)<0){
						giorno=null;
					}
					mese=document.forms[0]." . $this->attributes['VAR'] . "M.value-1;
					if(parseInt(mese)<0){
						mese=null;
					}
					anno=document.forms[0]." . $this->attributes['VAR'] . "Y.value;
					if(anno=='NA' || anno=='NK' || parseInt(anno)<0){
						anno=null;
					}
					if(giorno!=null && mese!=null && anno!=null){
						data.setFullYear(anno,mese,giorno);
					}
					else{
						data=null;
					}
					if (value===undefined){
						value=new Date();
					}
						";

                    $controlli_each_range .= " if (data) // se ho degli nk non faccio partire il range check
					  {
						";
                    if ($value == '' || preg_match("/\[/", $value)) {
                        $value = str_replace(array("[", "]"), array("", ""), $value);
                        $controlli_each_range .= "
						value=new Date();
						vgiorno=document.forms[0]." . $value . ".value.substr(0,2);
						vmese=document.forms[0]." . $value . ".value.substr(2,2)-1;
						vanno=document.forms[0]." . $value . ".value.substr(4,4);
						value.setFullYear(vanno,vmese,vgiorno);
						";

                    } else {
                        $vanno = substr($value, 0, 4) + 0;
                        $vmese = substr($value, 4, 2) - 1;
                        $vgiorno = substr($value, 6, 2) + 0;

                        $controlli_each_range .= "
						value=new Date();
						value.setFullYear(" . $vanno . "," . $vmese . "," . $vgiorno . ");
						";
                    }
                    $controlli_each_range .= "} ";
                    $controlli_each_range .= "
						var currfvalue = data;
						";
                    break;
                default:
                    //Only set currfvalue
                    $controlli_each_range .= "
						var currfvalue = document.forms[0]." . $this->id . ".value;
						";
                    break;
            }

            $fileName = str_replace("\.xml", "", $this->xml_form->filename);
            $fileName = preg_replace("!\.xml!", "", $fileName);
            $alert_msg = mlOut($fileName . '.' . $this->attributes['VAR'] . '.RANGECHECK_' . $key, $rangecheck['MESSAGE']);

            //E.Gargano 15/05/09 fine
            $controlli_each_range .= "
					if (realtime_equeries['" . $this->id . "_" . $key . "'] == undefined && currfvalue!= null && currfvalue!='' && !(currfvalue" . $comparator . "value)) {";
            if ($level == 'alert') {
                $controlli_each_range .= "
						if(show_bootbox){
							bootbox.hideAll(); //nascondo lo spinner del save/sending
							bootbox.dialog({
								title: '" . mlOut('System.RangeCheck.Alert', 'Edit Check Alert') . "',
								message: '" . $alert_msg . "',
								buttons: {
									success: {
												label: '" . mlOut('System.RangeCheck.Ok', 'Ok') . "',
												className: 'btn-success',
												callback: function() {
												document.forms[0]." . $this->id . ".focus();
											 }
									}
								}
							});
							return false;
						}";
            } elseif ($level == 'confirm') {
                //".mlOut('System.RangeCheck.DoYouConfirm', 'Do you confirm?')."
                $controlli_each_range .= "
						if(show_bootbox){
							//bootbox.hideAll(); //nascondo lo spinner del save/sending
							bootbox.dialog({
								title: '" . mlOut('System.RangeCheck.Confirmation', 'Edit Check Confirmation') . "',
								message: '" . $alert_msg . "<br/>',
								buttons: {
									success: {
												label: '" . mlOut('System.RangeCheck.Confirm', 'Confirm!') . "',
												className: 'btn-success',
												callback: function() {
												
												if(my_func=='salva_f'){
													realtime_equeries." . $this->id . "_" . $key . "='passed';
													window[my_func](ajax,true,true,realtime_equeries);
													
													/*VERSIONE SINGOLA REALTIME EQUERY
													window[my_func](false);
													ShowMessage('<i class=\"icon-spinner icon-spin orange bigger-125\"></i> Saving...');
													*/
												}
												else{
													var current_realtime_equery=[{
																					EQAREA_" . $this->id . " : '" . $alert_msg . "', 
																					EQFIELD : '" . $this->id . "',
																					" . $this->id . " : document.forms[0]." . $this->id . ".value,
																					EQAREADE_" . $this->id . " : '" . mlOut('System.RangeCheck.Confirm', 'Confirm!') . "',
																					TABLE : '" . $this->xml_form->form['TABLE'] . "'
																				}];
													
													realtime_equeries['" . $this->id . "_" . $key . "']= current_realtime_equery ;
													window[my_func](ajax,true,true,realtime_equeries);
														
													/*VERSIONE SINGOLA REALTIME EQUERY
													document.forms[0].link_to_send.value=\"|ME|?&REALTIME_EQ=1&ABILITA_EQ_DM=1&EQAREA_" . $this->id . "=" . $alert_msg . "&EQFIELD=" . $this->id . "&" . $this->id . "=\"+document.forms[0]." . $this->id . ".value+\"&EQAREADE_" . $this->id . "=" . mlOut('System.RangeCheck.Confirm', 'Confirm!') . "&TABLE=" . $this->xml_form->form['TABLE'] . "\";
													window[my_func](ajax,true,false,realtime_equeries);
													ShowMessage('<i class=\"icon-spinner icon-spin orange bigger-125\"></i> Sending...');
													*/
												}
												document.forms[0]." . $this->id . ".focus();
											 }
											 
									},
									danger: {
												label: '" . mlOut('System.RangeCheck.Cancel', 'Cancel') . "',
												className: 'btn-danger',
												callback: function() {
													bootbox.hideAll();
													document.forms[0]." . $this->id . ".focus();
												}
												
									}
								}
							});
							return false;
						}";
            }
            $controlli_each_range .= "
				}
			";
            $controlli_each_range .= "//FINE CREAZIONE RANGE CHECK #" . $key . "_" . $this->id . "\n";
            $this->controlli .= $this->addConditions($controlli_each_range);
        }
    }

    /**
     * Controlli sul valore del campo (minore di )
     *
     * @param String $value
     */
    function open_min($value)
    {
        //TODO: mi sembra competamente sbagliata!!!!!
        $campi = null;
        $i = null;
        $val = null;
        if (preg_match("/\[/", $campi[$i])) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $campi[$i]);
            $this->controlli .= "
						value=value_of('" . $campo . "', '0');
						";
        } else {
            $this->controlli .= "value=$val;\n";
        }
        //traduzione del messaggio di alert in inglese
        if ($this->config_service['lang'] == "en")
            $alert_msg = "Warning the value must be less than ";
        else
            $alert_msg = "Attenzione il valore deve essere minore di ";

        $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value<=value) {
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";
    }

    /**
     * Costruisce i controlli al salvataggio
     *
     * @param String $val
     */
    function open_save($val)
    {

        $in = $this->session_vars;
        if ($this->attributes['VAR_TYPE'] == 'text') {
            $controllo = "t";
        } else {
            if ($this->attributes['FM_CODE']) {
                $fm = $this->attributes['FM_CODE'];
                if (strtoupper($this->config_service['lang']) == 'IT') {
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NA') $in[$this->attributes['VAR']] = -9911;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NC') $in[$this->attributes['VAR']] = -9911; // utilizzare fmweb Passport
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NN') $in[$this->attributes['VAR']] = -9922;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'ND') $in[$this->attributes['VAR']] = -9933;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NP') $in[$this->attributes['VAR']] = -9944;
                    //if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
                    //if (strtoupper($in[$this->attributes['VAR']])=='ALTRO') $in[$this->attributes['VAR']]=-9900;
                } else {
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NA') $in[$this->attributes['VAR']] = -9911;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NC') $in[$this->attributes['VAR']] = -9911; // utilizzare fmweb Passport
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NK') $in[$this->attributes['VAR']] = -9922;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'ND') $in[$this->attributes['VAR']] = -9933;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NP') $in[$this->attributes['VAR']] = -9944;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'TE') $in[$this->attributes['VAR']] = -9955;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'OT') $in[$this->attributes['VAR']] = -9900;
                }
            } else {
                $fm = "00";
            }

            if ($this->attributes['VAR_STYPE'] == 'int')
                $controllo = "np" . $fm;
            else if ($this->attributes['VAR_STYPE'] == 'neg') $controllo = "na" . $fm;
            else if ($this->attributes['VAR_STYPE'] == 'real') $controllo = "xa" . $fm;
            else $controllo = "xp" . $fm;
            if ($val != 'obbligatorio') $controllo = "f" . $controllo;
        }
        /*else
		 {
			if ($this->attributes['FM_CODE'])
			$fm=$this->attributes['FM_CODE'];
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else if ($this->attributes['VAR_STYPE']=='neg') $controllo="na".$fm;
			else $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
			}*/
        $testo_js = make_js($this->testo);
        if ($testo_js == '') $testo_js = $this->attributes['LABEL_JS'];
        //debug_print_backtrace();
        if (($val == 'obbligatorio' && $this->attributes['CONDITION'] == '') || $this->attributes['VAR_TYPE'] != 'text') {
            $this->salva_js .= "
				c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';\n";

            $this->inrevisione_js .= "
				c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';\n";
        }
        /*aggiorno con la possibilit di utilizzare pi valori divisi da virgola in condition_value da testare approfonditamente (Giorgio Delsignore 14/06/2010)
		 if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js.="
			var value_{$this->attributes['CONDITION']}=value_of('{$this->attributes['CONDITION']}','0');
			if(value_{$this->attributes['CONDITION']}=='{$this->attributes['CONDITION_VALUE']}')c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
			";

			}*/
        if ($val == 'obbligatorio' && $this->attributes['CONDITION'] != '') {
            $this->salva_js .= "
				" . $this->attributes['CONDITION'] . "_setted=false;
				";
            $this->inrevisione_js .= "
				" . $this->attributes['CONDITION'] . "_setted=false;
				";
            if (preg_match("/,/", $this->attributes['CONDITION_VALUE'])) {
                $vals = explode(",", $this->attributes['CONDITION_VALUE']);
                foreach ($vals as $key => $value)
                    $this->salva_js .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='" . $value . "') {
								" . $this->attributes['CONDITION'] . "_setted=true;
								c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';
								}
						";
                $this->inrevisione_js .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='" . $value . "') {
								" . $this->attributes['CONDITION'] . "_setted=true;
								c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';
								}
						";
            } else {
                $condition_value = $this->attributes['CONDITION_VALUE'];
                $oper = "==";
                if (preg_match("/!/", $condition_value)) {
                    $oper = "!=";
                    $condition_value = substr($condition_value, 1);
                }
                $this->salva_js .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'" . $condition_value . "') {
						c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';
						" . $this->attributes['CONDITION'] . "_setted=true;
					}
					";
                $this->inrevisione_js .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'" . $this->attributes['CONDITION_VALUE'] . "') {
						c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';
						" . $this->attributes['CONDITION'] . "_setted=true;
					}
					";
            }
            $this->salva_js .= "
					if (!" . $this->attributes['CONDITION'] . "_setted) {c1+='<<b###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';}
				";
            $this->inrevisione_js .= "
					if (!" . $this->attributes['CONDITION'] . "_setted) {c1+='<<b###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';}
				";
        }
        $this->session_vars = $in;
    }

    /**
     * Funzione che costruisce i controlli javascript per controllare che le condizioni specificate nell'xml
     * siano verificate
     *
     * @return unknown
     */
    function verifyConditions()
    {
        if ($this->attributes['CONDITION'] != '') {
            $verifyConditions = '
				' . $this->attributes['CONDITION'] . '_setted=false;
				';
            if (preg_match("/,/", $this->attributes['CONDITION_VALUE'])) {
                $vals = explode(",", $this->attributes['CONDITION_VALUE']);
                foreach ($vals as $key => $value) {
                    $verifyConditions .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='{$value}') {
							{$this->attributes['CONDITION']}_setted=true;
						}
						";
                }
            } else {
                $condition_value = $this->attributes['CONDITION_VALUE'];
                $oper = "==";
                if (preg_match("/!/", $condition_value)) {
                    $oper = "!=";
                    $condition_value = substr($condition_value, 1);
                }
                $verifyConditions .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'{$condition_value}') {
							{$this->attributes['CONDITION']}_setted=true;
						}
					";
            }
            $verifyConditions .= "if({$this->attributes['CONDITION']}_setted)";
        } else {
            $verifyConditions = 'if(true)';
        }
        return $verifyConditions;
    }

    /**
     * Funzione che aggiunge il controllo sul fatto che le condizioni per compilare il campo siano verificate,
     * prima di eseguire altri azioni/controlli javascript
     *
     * @param unknown_type $js
     * @return unknown
     */
    function addConditions($js)
    {
        $finalJs = null;
        if ($js != '' && $this->attributes['CONDITION'] != '') {
            $verifyConditions = $this->verifyConditions();
            $finalJs .= "
			{$verifyConditions}{
				{$js}
			}
			";
            return $finalJs;
        } else {
            return $js;
        }
    }


    /**
     * Costruisce i controlli all'invio
     *
     * @param String $val
     */
    function open_send($val)
    {
        if ($this->session_vars ['USER_TIP'] != 'DE' && $this->attributes ['CRYPTO'] == 'yes') {
            return;
        }
        $in = $this->session_vars;
        if ($this->attributes['VAR_TYPE'] == 'text') {
            $controllo = "t";
        } else {
            if ($this->attributes['FM_CODE']) {
                $fm = $this->attributes['FM_CODE'];
                if (strtoupper($this->config_service['lang']) == 'IT') {
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NA') $in[$this->attributes['VAR']] = -9911;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NC') $in[$this->attributes['VAR']] = -9911; // utilizzare fmweb Passport
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NN') $in[$this->attributes['VAR']] = -9922;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'ND') $in[$this->attributes['VAR']] = -9933;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NP') $in[$this->attributes['VAR']] = -9944;
                    //if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
                    //if (strtoupper($in[$this->attributes['VAR']])=='ALTRO') $in[$this->attributes['VAR']]=-9900;
                } else {
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NA') $in[$this->attributes['VAR']] = -9911;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NC') $in[$this->attributes['VAR']] = -9911; // utilizzare fmweb Passport
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NK') $in[$this->attributes['VAR']] = -9922;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'ND') $in[$this->attributes['VAR']] = -9933;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'NP') $in[$this->attributes['VAR']] = -9944;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'TE') $in[$this->attributes['VAR']] = -9955;
                    if (strtoupper($in[$this->attributes['VAR']]) == 'OT') $in[$this->attributes['VAR']] = -9900;
                }
            } else {
                $fm = "00";
            }
            if ($this->attributes['VAR_STYPE'] == 'int')
                $controllo = "np" . $fm;
            else if ($this->attributes['VAR_STYPE'] == 'real')
                $controllo = "xa" . $fm;
            else
                $controllo = "xp" . $fm;
        }
        /*else
		{
			if ($this->attributes['FM_CODE'])
			$fm=$this->attributes['FM_CODE'];
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')

			$controllo="np".$fm;
			else
			$controllo="xp".$fm;
		}*/
        if ($val == 'facoltativo') $controllo = "f" . $controllo;
        $testo_js = make_js($this->input_txt);
        if ($testo_js == '') $testo_js = $this->attributes['LABEL_JS'];
        //debug_print_backtrace();
        $this->invia_js = "
				c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';\n";
        if ($this->attributes['CONDITION'] != '') {
            $this->invia_js = "
				" . $this->attributes['CONDITION'] . "_setted=false;
				";
            if (preg_match("/,/", $this->attributes['CONDITION_VALUE'])) {
                $vals = explode(",", $this->attributes['CONDITION_VALUE']);
                foreach ($vals as $key => $value)
                    $this->invia_js .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='" . $value . "') {
								" . $this->attributes['CONDITION'] . "_setted=true;
								c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';
								}
						";
            } else {
                $condition_value = $this->attributes['CONDITION_VALUE'];
                $oper = "==";
                if (preg_match("/!/", $condition_value)) {
                    $oper = "!=";
                    $condition_value = substr($condition_value, 1);
                }
                $this->invia_js .= "
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'" . $condition_value . "') {
						c1+='<<" . $controllo . "###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';
						" . $this->attributes['CONDITION'] . "_setted=true;
					}
					";
            }
            $this->invia_js .= "
					if (!" . $this->attributes['CONDITION'] . "_setted) {c1+='<<b###" . $this->attributes['VAR'] . "###" . $testo_js . ">>';}
				";
        }
        $in = $this->session_vars;
        if ($in['invia'] != '' || $in['INVIOCO'] == '1') {
            if ($this->condition_passed) {
                if ($in[$this->attributes['VAR']] == '') {
                    if ($val == 'obbligatorio') {
                        $this->validata = false;
                        $testo_js = make_js($this->testo);
                        $this->errors[$this->attributes['VAR']] = "The field is mandatory";
                    }
                }
            } else {
                if ($in[$this->attributes['VAR']] != '' && $val == 'obbligatorio') {
                    $this->validata = false;
                    $testo_js = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "The field must be empty";
                }
            }
        }
        $this->session_vars = $in;
    }

    function open_jsend($val)
    {
        return $this->class .= "required,";
    }

    /**
     * Recupera i possibili valori del campo da una query di decodifica
     *
     * @param String $value
     */
    function fields_value_bytb($value)
    {
        if ($this->xml_form->no_field_value_by_tb) {
            return;
        }
        if ($this->xml_form->form['NO_LOAD_TB'] != '' && $this->xml_form->closed) return;
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        //if ($this->xml_form->closed){// && $this->xml_form->form['NO_LOAD_BYTB']=="yes"){
        //	$this->values[$inputval[$this->attributes['VAR']]]=$inputval['D_'.$this->attributes['VAR']];
        //	return ;
        //}
        $code = $this->attributes['BYTBCODE'];
        $decode = $this->attributes['BYTBDECODE'];
        $where = $this->attributes['BYTBWHERE'];
        $order_by = $this->attributes['BYTBORDERBY'];
        $where = str_replace("min_of", "<", $where);
        $where = str_replace("max_of", ">", $where);

        //nel caso in cui mi riferisca a ANA_UTENTI oppure abbia settato ANCHE il parametro bytbnoprefix="yes",
        //allora NON metto il prefisso del servizio davanti
        if (!preg_match("/ana_utenti/i", $value) && $this->attributes['BYTBNOPREFIX'] == "")
            $value = $this->service . "_" . $value;
        $decode = str_replace("#BR#", "<br>", $decode);
        $decode = str_replace("#i#", "<i>", $decode);
        $decode = str_replace("#/i#", "</i>", $decode);
        $replaceRet = query::varGlobReplace($where);
        $value = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $value);

        $where = $replaceRet['sql'];
        foreach ($replaceRet['binded'] as $key => $val) {
            $binded_vars[$key] = $val;
        }

        $decode = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $decode);
        $code = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $code);
        $order_by = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $order_by);
        $conn = $this->conn;
        if ($where != '') $where = "where $where";
        $query = "select $code as code";
        if ($decode != '') $query .= ", $decode as decode";
        if ($order_by != '') $query .= " from $value $where order by $order_by";
        else if (strtolower($this->attributes['VAR_TYPE']) == 'clob' || $this->attributes['TYPE'] == 'file_doc') $query .= " from $value $where";
        else $query .= " from $value $where order by decode asc";
        $sql = new query($conn);
        //$sql->set_sql($query);
//echo "\n<!--$query-->";
        $sql->exec($query, $binded_vars);//fatto!!!
        $in = $this->session_vars;
        while ($sql->get_row()) {
            if ($decode != '') {
                $fileName = str_replace("\.xml", "", $this->xml_form->filename);
                $fileName = preg_replace("!\.xml!", "", $fileName);
                if (($sql->row['CODE']) && (!($this->attributes['TYPE'] == 'hidden' || $this->attributes['TYPE'] == 'data' || $this->attributes['TYPE'] == 'date_cal' || $this->attributes['TYPE'] == 'text' || $this->attributes['TYPE'] == 'textbox'))) { //vmazzeo 05.04.2016 aggiunto || $this->attributes['TYPE'] == 'text'
                    $val = mlOut($fileName . '.' . $this->attributes['VAR'] . '.' . $sql->row['CODE'], $sql->row['DECODE']);
                } else {
                    $val = $sql->row['DECODE'];
                }

                $this->values[$sql->row['CODE']] = $val;
                if (!isset($in[$this->attributes['VAR']]) && $this->attributes['TYPE'] == 'hidden') {
                    global $in;
                    $in[$this->attributes['VAR']] = $sql->row['DECODE']; //$val;
                }
            } else {
                global ${$this->attributes['BYVAR']};
                $this->values[$sql->row['CODE']] = ${$this->attributes['BYVAR']}[$sql->row['CODE']];
            }
            //EDO experimental
            if ($this->attributes['TYPE'] == 'file_doc' || $this->attributes['TYPE'] == 'file_cme')
                $this->id_bytd = $this->values[$sql->row['CODE']];
//			echo($this->id_bytd);
//			if($this->attributes['TYPE']=='file_doc') $this->id=${$this->attributes['BYVAR']}[$sql->row['CODE']];
        }

    }

    /**
     * Costruisce il codice html del campo in visualizzazione
     *
     * @param boolean $equery
     */
    function make_close_html($equery = false, $eq_int = null, $deleted = false)
    { //TODO: Check deleted parameter
        $something = null;
        $str_testo_comm = null;
        $str_testo_agg = null;
        if (isset($_GET['DEBUG'])) {
            $dbg = debug_backtrace();
            foreach ($dbg as $k => $v) {
                echo "FILE: {$v['file']}:{$v['line']} in function {$v['function']}<br/>";
            }
            echo "<hr/>";
        }

        if (isset($this->attributes['VAR'])) $this->html = '<tr id=' . $this->attributes['VAR'] . ' style="display:">';
        $function_to_call = 'close_';
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        $this->deleted = $deleted;
        if ($this->config_service['lang'] == "en") {
            $value_changed_msg = "Value is changed ";
            $old_sel_msg = "old selection/value ";
        } else {
            $value_changed_msg = "Il valore  cambiato ";
            $old_sel_msg = "vecchia selezione/valore ";
        }
        if (isset($inputval[$this->attributes['VAR']])) $value = $inputval[$this->attributes['VAR']];
        $value = htmlentities($value, ENT_QUOTES, 'UTF-8');
        if ($this->attributes['BYTB'] != '') $this->fields_value_bytb($this->attributes['BYTB']);
        //echo "STEP1: {$this->input_field}<br/>";
        if ($this->attributes['ALWAYS_BYTB'] == 'yes') {
            if (is_array($this->values)) {
                foreach ($this->values as $curValue) {
                    $value = $curValue;
                }
            } else if ($this->values != '') {
                $value = $this->values;
            }
        }
        if (method_exists($this, $function_to_call)) $this->{$function_to_call}($value);
        $cols = $this->attributes['COLS'] + 0;
        if ($cols == 0) $cols = 1;

        if ($this->attributes['LINK'] != "true") {
            $this->input_txt = preg_replace("/<a(.*?)<\/a>/", "", $this->input_txt);
        }
        if (!$this->config_service['KEEP_ASTERISK']) $this->input_txt = str_replace("<font color=red>*</font>", "", $this->input_txt);
        if ($this->attributes['ONLY_AF'] != '') $this->attributes['COLSPAN'] = "2";

        if (isset($in['SDV']) && $in['SDV'] != '' && $this->config_service['SDV'] == "1" && isset($this->config_service['SDV'])) {
            $SDVchecked = "";
            if ($something == 1) {
                $SDVchecked = "checked";
            }
            $this->input_field .= '<span style=" background-color:#87ceeb; border:#000099 1px solid;padding:6px 8px 2px 4px;margin:8px;"> <input type="checkbox" id="SDV_' . $this->attributes['VAR'] . '" name="SDV_' . $this->attributes['VAR'] . '" ' . $SDVchecked . '></span>';

        }
        //Separazione CRO/Standard!

        if ($equery) {/*Prova di alleggerimento*/
            if ($this->input_field != '' && $this->attributes['TYPE'] != 'hidden' && $this->attributes['TYPE'] != 'text' && $this->attributes['TYPE'] != '' && $this->attributes['TYPE'] != 'link_hyper' && $this->attributes['DISABLED'] == '') {
                $testo_changed = '';
                $img_eq = '';
                $sql_eqfield = "select * from {$this->service}_eqfield eqfield, {$this->service}_eq eq where
                            eqfield.{$this->xml_form->config_service['PK_SERVICE']}={$_GET [$this->xml_form->config_service['PK_SERVICE']]}
                            and eqfield.esam={$_GET ['ESAM']}
                            and eqfield.visitnum={$_GET ['VISITNUM']}
                            and eqfield.visitnum_progr={$_GET ['VISITNUM_PROGR']}
                            and eqfield.progr={$_GET ['PROGR']}
                            and eqfield.FIELD='{$this->attributes['VAR']}'
                            and eq.equery_int=eqfield.eq_int
                            and eq.stato in(0,2)
                        ";
                //						echo $sql_eqfield;
                $sql6 = new query ($this->conn);
                $sql6->set_sql($sql_eqfield);
                $sql6->exec();
                $sql6->get_row();
                $nota_dm = $sql6->row['NOTE'];
                $nota_de = $sql6->row['NOTE_DE'];
                $statofield = $sql6->row['STATOFIELD'];
                //				echo $nota_de;

                if ($nota_de != '' && $this->xml_form->old_values[$this->id] == $this->xml_form->tb_vals[$this->id]) {
                    $solo_comment = 1;
                    $img_eq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
                    $testo_changed = "<br/><p style='color:blue;font-weight:bold;'>$str_testo_comm</p>";
                    if ($this->attributes['TYPE'] == "date_hyper" && $this->xml_form->old_values[$this->id . "RC"] != $this->xml_form->tb_vals[$this->id . "RC"]) {
                        $solo_comment = 0;
                    }
                } else {
                    $solo_comment = 0;
                }
                /**
                 * Fine Caso in cui il DE ha risposto o emesso eQ solo con commento
                 */

                if (count($this->xml_form->old_values[$this->id]) == 0 && count($this->xml_form->tb_vals[$this->id]) == 0 && $solo_comment != 1) {
                    $testo_changed = "";
                } else
                    if ($this->xml_form->old_values[$this->id] != $this->xml_form->tb_vals[$this->id] && $nota_de != '') {
                        if (isset($this->xml_form->old_values['D_' . $this->id])) {
                            $old_spec = $this->xml_form->old_values['D_' . $this->id];
                        } else {
                            $old_spec = $this->xml_form->old_values[$this->id];
                        }

                        if ($this->attributes['TYPE'] == "date_hyper") {
                            if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 0, 2) != 'OK') {
                                $dd = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 0, 2);
                            } else {
                                $dd = substr($this->xml_form->old_values[$this->id], 0, 2);
                            }
                            if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 2, 2) != 'OK') {
                                $mm = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 2, 2);
                            } else {
                                $mm = substr($this->xml_form->old_values[$this->id], 2, 2);
                            }
                            if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 4, 2) != 'OK') {
                                $yyyy = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 4, 2);
                            } else {
                                $yyyy = substr($this->xml_form->old_values[$this->id], 4, 4);
                            }
                            $old_spec = $dd . $mm . $yyyy;
                        }
                        $img_eq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
                        $str_testo_change = "<h3 style=\"display:inline;text-decoration:underline;\">$value_changed_msg </h3><br />$old_sel_msg:<br /> $old_spec";

                        if ($old_spec == '') {
                            $testo_changed = "<br/><span style='color:blue;font-weight:bold'><br/>$str_testo_agg</span>";
                        } else {
                            $testo_changed = "<br/><span style='color:red;font-weight:bold'><br/>$str_testo_change</span>";
                        }
                    } elseif ($this->attributes['TYPE'] == "date_hyper" && $this->xml_form->old_values[$this->id . "RC"] != $this->xml_form->tb_vals[$this->id . "RC"]
                        && $this->xml_form->old_values[$this->id] == $this->xml_form->tb_vals[$this->id]) {
                        //Caso eQ da NA a NK , cambia solo la RC
                        if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 0, 2) != 'OK') {
                            $dd = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 0, 2);
                        } else {
                            $dd = substr($this->xml_form->old_values[$this->id], 0, 2);
                        }
                        if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 2, 2) != 'OK') {
                            $mm = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 2, 2);
                        } else {
                            $mm = substr($this->xml_form->old_values[$this->id], 2, 2);
                        }
                        if (substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 4, 2) != 'OK') {
                            $yyyy = substr($this->xml_form->old_values[$this->attributes['VAR'] . 'RC'], 4, 2);
                        } else {
                            $yyyy = substr($this->xml_form->old_values[$this->id], 4, 4);
                        }
                        $old_spec = $dd . $mm . $yyyy;

                        $img_eq = "<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
                        $str_testo_change = "<h3 style=\"display:inline;text-decoration:underline;\">$value_changed_msg </h3><br />$old_sel_msg:<br /> $old_spec";

                        if ($old_spec == '') {
                            $testo_changed = "<br/><span style='color:blue;font-weight:bold'><br/>$str_testo_agg</span>";
                        } else {
                            $testo_changed = "<br/><span style='color:red;font-weight:bold'><br/>$str_testo_change</span>";
                        }
                    }


                $this->close_($value);
                $this->input_txt .= $testo_changed;
                foreach ($this->xml_form->fields as $key => $val) {
                    if ($this->xml_form->fields[$key]['HIDE'] == "yes") {
                        if ($nota_de != '') {
                            $this->xml_form->fields[$key]['HIDE'] = "no";
                        }
                    }
                }
                if (strtolower($this->config_service['lang']) == 'it') {
                    $accept_msg = 'Accettare eQuery permanentemente? (Ok per accettare)';
                    $rejept_msg = 'Rifiutare eQuery permanentemente? (Ok per rifiutare)';
                    $sure_msg = 'Sei sicuro?';
                    $approvata_eq = 'eQuery Approvata';
                    $eq_incoerente = 'Possible inconsistenza sul campo';
                } else {
                    $accept_msg = 'Accept the eQuery permanently? (Ok to accept)';
                    $rejept_msg = 'Reject the eQuery permanently? (Ok to reject)';
                    $sure_msg = 'Are you sure?';
                    $approvata_eq = 'eQuery Approved';
                    $eq_incoerente = 'Possible field inconsistency';
                }


                if ($nota_de != '' && $statofield == 2 && $in ['USER_TIP'] == 'DM') { // tolto: && !isset($_GET['ABILITA_EQ_DM'])
                    //	 			echo $nota_de;
                    $eQ_area_DE = "<a style='color:red;font-weight:bold' href=\"#\"
                                onclick=\"show_hide('EQAREADE_{$this->attributes['VAR']}');return false;\"><i class=\"fa fa-comments\"></i></a><br>
                                <div style='display:none; border:1px solid red; background:white;width:180px;height:60px; overflow:auto;'  id='EQAREADE_{$this->attributes['VAR']}' name='EQAREADE_{$this->attributes['VAR']}' >$nota_de</div>
                                ";
                    //	 			print_r($this->xml_form->PK_SERVICE);
                    $d_eqfield = $this->xml_form->old_values['D_' . $this->id];
                    $d_eqfield = str_replace("'", "\'", $d_eqfield); //non preg_replace!
                    if ($this->attributes['TYPE'] == 'ora_hyper') {
                        $field_ora_approv = "&DATEORA=ora";
                    }
                    if ($this->attributes['TYPE'] == 'date_hyper') {
                        $field_ora_approv = "&DATEORA=date";
                    }
                    //				echo $statofield;
                    //	 			print_r($this->xml_form->old_values['D_'.$this->id]);
                    //	 			echo $d_eqfield;
                    $buttons = "<td valign=top align=right><input style=\"background:green;color:white;font-weight:bold;cursor:pointer;\" type=\"button\" name=\"APPROVA_EQFIELD\" value=\"OK\" onclick=\"if(confirm('$accept_msg'))window.location.href='index.php?EQ_INT_FIELD={$sql6->row['EQ_INT']}&EQFIELD={$this->attributes['VAR']}&D_EQFIELD={$d_eqfield}&APPROVA_EQFIELD=1&{$this->xml_form->PK_SERVICE}={$_GET[$this->xml_form->PK_SERVICE]}&CENTER={$_GET['CENTER']}&ESAM={$_GET['ESAM']}&VISITNUM={$_GET['VISITNUM']}&PROGR={$_GET['PROGR']}&exams=visite_exam.xml$field_ora_approv'; else return false;\" />
                            <input  style=\"background:red;color:white;font-weight:bold;cursor:pointer;\" type=\"button\" name=\"RIFIUTA_EQFIELD\" value=\"NO\" onclick=\"if(confirm('$rejept_msg'))window.location.href='index.php?EQ_INT_FIELD={$sql6->row['EQ_INT']}&EQFIELD={$this->attributes['VAR']}&D_EQFIELD={$d_eqfield}&RIFIUTA_EQFIELD=1&{$this->xml_form->PK_SERVICE}={$_GET[$this->xml_form->PK_SERVICE]}&CENTER={$_GET['CENTER']}&ESAM={$_GET['ESAM']}&VISITNUM={$_GET['VISITNUM']}&exams=visite_exam.xml'; else return false;\" />
                            </td>
                            ";
                    $this->attributes['SHOW_VIS'] = 'yes';
                }
                //Fine Tasto di approvazione eQ per campo per DM


                // eQ richiesta dal DM, compare eQ giallo con il commento del Dm per campo
                //DM vuole fare un eQ, gli compare una textare per ogni campo che non sia pending
                if ($nota_dm != '' && $statofield == 0) {
                    $eQ_area = "<a style='color:#ff7d00;font-weight:bolder;font-size:1.3em' href=\"#\"
                            onclick=\"show_hide('EQAREA_{$this->attributes['VAR']}');return false;\"><i class=\"fa fa-comments\"></i></a><br>
                            <div style='display:none;border:1px solid #ff7d00; background:yellow;width:180px;height:60px; overflow:auto;'  id='EQAREA_{$this->attributes['VAR']}' name='EQAREA_{$this->attributes['VAR']}' >$nota_dm</div>
                            ";
                } elseif (isset($_GET['ABILITA_EQ_DM']) && $nota_de == '') {
                    //da sostituire in futuro con il seguente?
                    //if(isset($_GET['ABILITA_EQ_DM'])  && $this->xml_form->old_values[$this->id]==$this->xml_form->tb_vals[$this->id]){
                    $eQ_area = "<a style='color:blue;font-weight:bold' href=\"#\"
                            onclick=\"show_hide('EQAREA_{$this->attributes['VAR']}');return false;\"><i class=\"fa fa-pencil-square blue\" style=\"font-size:1.2em;\"></i></a><br>
                            <textarea cols='20' rows='2' style='display:none;' id='EQAREA_{$this->attributes['VAR']}' name='EQAREA_{$this->attributes['VAR']}' ></textarea>
                            ";
                }
                // Fine eQ richiesta dal DM, compare eQ giallo con il commento del Dm per campo
                //Fine DM vuole fare un eQ, gli compare una textare per ogni campo

                //Possibile incoerenza sul campo, in open_condition
                if ($this->attributes['EQ_HIDE'] == true) {
                    $this->input_txt .= "&nbsp;&nbsp;<img  title=\"$eq_incoerente\" width=\"30px\" src=\"images/punto-interrogativo.png\">";
                }

                //if ($this->attributes['TYPE'] != "" && $this->attributes['TYPE'] != "hidden" && $this->attributes['TYPE'] != "text") {
                $this->input_txt .= "&nbsp; $eQ_area";

                $this->input_txt = "
							<table width=\"100%\" border=0>
								<tr>
									<td valign=top align=left>
									$img_eq
									</td>

									<td valign=top align=left>
									$eQ_area_DE
									</td>
									<td valign=top align=right>
									{$this->input_txt}
									</td>

									$buttons
								</tr>
							</table>
							";
                //}
            }


        }

        if ($deleted == 2 && $this->attributes['MAIN'] != "yes") {
            $css_field_class = $css_txt_class = "deletedfield";
        } else {
            $css_txt_class = "destra";
            $css_field_class = "input";
        }

        if ((isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) && $this->attributes['HIDEVIS'] != 'yes') {
            $colspan = $cols * $this->attributes['COLSPAN'];
            if ($this->input_field == '') $this->html = $this->input_txt;
            else {
                if ($this->input_txt != '') $this->input_txt .= ":";
                $this->html = '<td id="' . $this->attributes['VAR'] . '" class="input" colspan="' . $colspan . '">' . $this->input_txt . $this->input_field . '</td>';
            }
        } else
            if ($this->attributes['TYPE'] != 'hidden') {
                if (
                (($this->attributes['HIDEVIS'] != 'yes' && ($this->condition_passed || $this->attributes['HIDE'] != 'yes')) || $this->attributes['SHOW_VIS'] == 'yes')
                ) {

                    $this->html = '<td colspan="' . $cols . '" class="destra">' . $this->input_txt . '</td><td colspan="' . $cols . '" class="input">' . $this->input_field . '</td>';
                    if ($this->xml_form->form['COLS'] != $this->attributes['COLS']) {
                        $width = round($this->attributes['COLS'] / $this->xml_form->form['COLS'] * 100);
                        $styleAdd = " style=\"float:left;width:{$width}%\"";
                    } else $styleAdd = "";
                    $span = 6;
                    $labelstyle = "";
                    if ($this->attributes['SPAN'] == "yes") {
                        $span = 12;
                        $labelstyle = ' style="text-align: left;" ';
                    }
                    $this->html = "
					<div id=\"tr_{$this->attributes['VAR']}\" {$styleAdd}>
						<label class=\"col-sm-{$span} control-label\" for=\"field_{$this->attributes['VAR']}\" $labelstyle >{$this->input_txt}</label>
						<div class=\"col-sm-{$span} no-padding-left\" id=\"field_{$this->attributes['VAR']}\" style=\"\">
							{$this->input_field}
						</div>
					</div>
				";
                }
                if ($this->attributes['HIDE_THIS'] != '' && $inputval[$this->attributes['VAR']] == '') $this->html = '';
            }
        if ($this->attributes['TYPE'] == 'hidden') $this->html = '';#<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';

        /**
         * Caso delle hide condizionate, nella open basta hide nel primo field .
         * Nella close bisogna gestirlo , mettendo hide_this .
         * La condition passed è gestita nel metodo open_condition.
         */
//		 echo "<hr>Passed:"; echo $this->condition_passed; echo "Var:"; echo  $this->attributes['VAR'];
        if ($this->condition_passed != 1 && $this->attributes['HIDE_THIS'] == 'yes') {
            $this->html = '';
            $this->input_txt = '';
        }

        /**
         * Esplosione delle progressive nel Patient Dossier. La parte relativa ai dati della form main non
         * deve essere ripetuta per ogni sub del Patient Dossier.
         */
        if ($this->attributes['MAIN'] == "yes" && $_GET[$this->config_service['PK_SERVICE']] != '' && isset($_GET['CRF'])) {
            $this->html = '';
        }

        /**Double data entry , rivederE:*/
        if (isset($in['DDE']) && $in['DDE'] != '') {
//			print_r($this->xml_form->difference);

            if ($this->xml_form->difference[$this->attributes['VAR']] == $this->attributes['VAR']) {
//				print_r($this->attributes['VAR']);
                if (isset($in['ONLY_EQUAL'])) {
                    $this->html = '';
                } else {
                    if ((isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) && $this->attributes['HIDEVIS'] != 'yes') {
                        $colspan = $cols * $this->attributes['COLSPAN'];
                        if ($this->input_field == '') $this->html = $this->input_txt;
                        else {
                            if ($this->input_txt != '') $this->input_txt .= "";
                            $this->html = '<td id="' . $this->attributes['VAR'] . '" class="input2" colspan="' . $colspan . '">' . $this->input_txt . $this->input_field . '</td>';
                        }
                    } else
                        if ($this->attributes['TYPE'] != 'hidden') {
                            if (
                            (($this->attributes['HIDEVIS'] != 'yes' && ($this->condition_passed || $this->attributes['HIDE'] != 'yes')) || $this->attributes['SHOW_VIS'] == 'yes')
                            ) {

                                $this->html = '<td colspan="' . $cols . '" id="' . $this->attributes['VAR'] . '" class="input2">' . $this->input_txt . '</td><td colspan="' . $cols . '" class="input2">' . $this->input_field . '</td>';
                            }
                            if ($this->attributes['HIDE_THIS'] != '' && $inputval[$this->attributes['VAR']] == '') $this->html = '';
                        }
                    if ($this->attributes['TYPE'] == 'hidden') $this->html = '';#<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';
                }
            } elseif (isset($in['ONLY_DIFF']) && $in['ONLY_DIFF'] != '') {
                $this->html = '';
                foreach ($this->xml_form->fields as $key => $val) {
                    $this->xml_form->fields[$key]['TESTO'] = '';
                }
            }
        }
    }

    /**
     * Gestisce il confirm sul campo
     *
     * @param String $value
     */
    function open_confirm($value)
    {
        $condition = null;
        $testo_js = make_js($value);
        $confirm_js = "
			if (!confirm('$testo_js')) {
				document.forms[0].{$this->attributes['VAR']}.focus();
				return false;
			}
		";
        $vars = explode("|", $this->attributes['CONFIRM_COND_VAR']);
        $values = explode("|", $this->attributes['CONFIRM_COND_VALUE']);
        if (count($vars) > 0) {
            foreach ($vars as $key => $val) {
                if ($values[$key] == 'null') $values[$key] = '';
                if ($this->attributes['CONFIRM_OP'] == 'and') $op = "&&";
                if ($this->attributes['CONFIRM_OP'] == 'or') $op = "||";
                $condition .= "(value_of('{$val}')=='{$values[$key]}') {$op} ";
            }
            $condition = rtrim($condition, " $op ");
            $condition_check = "
				if ($condition)
			";
            $confirm_js = $condition_check . $confirm_js;
        }
        $this->invia_js .= $confirm_js;
    }

    /**
     * Gestisce l'invocazione di js all'onchange del campo
     *
     * @param String $value
     */
    function open_on_change($value)
    {
        $this->salva_js .= "
	$value
			";
        $this->invia_js .= "
	$value
			";
    }

    function XML_PRINT_($values)
    {
        $search = array("'<script[^>]*?>.*?</script>'si",  // Rimozione del javascript
            "'<[\/\!]*?[^<>]*?>'si",           // Rimozione dei tag HTML
            "'([\r\n])[\s]+'",                 // Rimozione degli spazi bianchi
            "'&(quot|#34);'i",                 // Sostituzione delle entit HTML
            "'&(amp|#38);'i",
            "'&(lt|#60);'i",
            "'&(gt|#62);'i",
            "'&(nbsp|#160);'i",
            "'&(iexcl|#161);'i",
            "'&(cent|#162);'i",
            "'&(pound|#163);'i",
            "'&(copy|#169);'i",
            "'&#(\d+);'e");                    // Valuta come codice PHP

        $replace = array("",
            "",
            "\\1",
            "\"",
            "&",
            "<",
            ">",
            " ",
            chr(161),
            chr(162),
            chr(163),
            chr(169),
            "chr(\\1)");

        $this->testo = preg_replace($search, $replace, $this->testo);
        $this->testo = str_replace("Ricerca nella banca dati...", "", $this->testo);
        return $this->XML_OUTPUT($values);
    }

    function XML_OUTPUT($values)
    {
        if (isset($this->attributes['VAR'])) $tag = "VAR";
        else $tag = "LABEL" . $this->id;
        if (isset($this->attributes['VAR'])) {
            $out = "
		<$tag NAME=\"{$this->id}\">";
        } else {
            $out = "
		<$tag>";
        }
        if ($this->testo != '') $out .= "
			<TESTO><![CDATA[{$this->testo}]]></TESTO>";
        if ($this->attributes['TB'] != 'no')
            $out .= "
			<VALORE><![CDATA[{$values[$this->id]}]]></VALORE>";
        $out .= "
		</$tag>
		";
        return $out;
    }

    function open_jcondition($val)
    {
        $controllo = null;
        $var_cond = $val;
        $this->condition_passed = false;
        $in = $this->session_vars;
        $inputval = $this->db_vars;
        $val_cond = $this->attributes['CONDITION_VALUE'];
        if ($this->attributes['HIDE'] == 'yes') {
            if (preg_match("/,/", $val_cond)) {
                $controllo = "
	        	valore=document.forms[0]." . $var_cond . ".value;
					$('#tr_" . $this->id . "').hide();

					";
                $vals = explode(",", $val_cond);
                foreach ($vals as $key => $value) {
                    if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
                    else $value_to_control = $inputval[$var_cond];

                    if ($value_to_control == $value) {
                        $this->condition_passed = true;
                    }

                    $controllo .= " \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{

							$('#tr_" . $this->id . "').show();

						}
						";
                }
                $controllo .= "
				if (document.getElementById('tr_" . $this->id . "') && document.getElementById('tr_" . $this->id . "').style.display=='none' && document.forms[0]." . $this->id . ")
						{
							if (document.forms[0]." . $this->id . ".type=='checkbox' || (document.forms[0]." . $this->id . "[0] && document.forms[0]." . $this->id . "[0].type=='radio')){
								for(i=0;i<document.forms[0]." . $this->id . ".length;i++) document.forms[0]." . $this->id . "[i].checked=false;
							}
						else document.forms[0]." . $this->id . ".value='';
						}
				";
            } else {
                $op = '!=';
                if (preg_match("/\!/", $val_cond)) {
                    $val_cond = str_replace("!", "", $val_cond);
                    $op = '==';
                }
                if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
                else $value_to_control = $inputval[$var_cond];
                if ($op == '==') $this->condition_passed = ($value_to_control != $val_cond);
                else $this->condition_passed = ($value_to_control == $val_cond);

                $controllo .= " \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
                $controllo .= "
					if (document.forms[0]." . $this->id . ")
						{
							if (document.forms[0]." . $this->id . ".type=='checkbox' || (document.forms[0]." . $this->id . "[0] && document.forms[0]." . $this->id . "[0].type=='radio')){
								for(i=0;i<document.forms[0]." . $this->id . ".length;i++) document.forms[0]." . $this->id . "[i].checked=false;
							}
						else {
							if (document.forms[0]." . $this->id . "[0] && !document.forms[0]." . $this->id . ".selectedIndex){
								           radioclear('{$this->id}');
							}
						else document.forms[0]." . $this->id . ".value='';
						}
					}

					$('#tr_" . $this->id . "').hide();
					}
					else {
					$('#tr_" . $this->id . "').show();
					}
					";
            }
        } else {

            if ($this->attributes['HIDE_THIS'] == 'yes') {

                if (preg_match("/,/", $val_cond)) {
                    $controllo .= "
	        valore=document.forms[0]." . $this->id . ".value;
				document.forms[0]." . $this->id . ".value='';
					$('#cell_" . $this->id . "').hide();
					$('#cell_input" . $this->id . "').hide();
					";
                    $vals = explode(",", $val_cond);
                    //$this->condition_passed=false;
                    foreach ($vals as $key => $value) {
                        if ($in[$var_cond] == $value) $this->condition_passed = true;
                        $controllo .= " \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
							$('#cell_" . $this->id . "').show();
							$('#cell_input" . $this->id . "').show();
						    document.forms[0]." . $this->id . ".value=valore;

						}
							";
                    }
                } else {

                    $op = '!=';
                    if (preg_match("/\!/", $val_cond)) {
                        $val_cond = str_replace("!", "", $val_cond);
                        $op = '==';
                    }
                    if ($op == '==') $this->condition_passed = ($in[$var_cond] != $val_cond);
                    else $this->condition_passed = ($in[$var_cond] == $val_cond);
                    //echo "<hr>$op - $var_cond - $val_cond - {$this->attributes['VAR']}<hr>";
                    $controllo .= " \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
                    $controllo .= "
					if (document.forms[0]." . $this->id . ")
						document.forms[0]." . $this->id . ".value='';
					  	$('#cell_" . $this->id . "').hide();
					  	$('#cell_input" . $this->id . "').hide();
					}
					else{
						$('#cell_" . $this->id . "').show();
						$('#cell_input" . $this->id . "').show();
					}
					";
                }
            } else {
                if (preg_match("/,/", $val_cond)) {
                    $controllo .= "
	        valore=document.forms[0]." . $this->id . ".value;
	        document.forms[0]." . $this->id . ".value='';

						";
                    $vals = explode(",", $val_cond);
                    foreach ($vals as $key => $value) {
                        if (isset($in['INVIOCO'])) $value_to_control = $in[$var_cond];
                        else $value_to_control = $inputval[$var_cond];
                        if ($value_to_control == $value) {
                            $this->condition_passed = true;
                        }
                        $controllo .= " \n
					//condizione $var_cond==$value
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			document.forms[0]." . $this->id . ".value=valore;
						}
						";

                    }
                } else {
                    $op = '!=';
                    if (preg_match("/\!/", $val_cond)) {
                        $val_cond = str_replace("!", "", $val_cond);
                        $op = '==';
                    }
                    /*
				foreach ($this->xml_form->fields as $key => $val){
					if ($val['TYPE']=='checkbox') {
						foreach ($val['VALUE'] as $key => $val){
							//echo "<li>$key</li>";
							if (!isset($in[$key])) $in[$key]='0';
						}
					}
				}
				*/
                    if ($op == '==') $this->condition_passed = ($in[$var_cond] != $val_cond);
                    else $this->condition_passed = ($in[$var_cond] == $val_cond);

                    $controllo .= " \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
                    $controllo .= "
					if (document.forms[0]." . $this->id . ")
						{
							if (document.forms[0]." . $this->id . ".type=='checkbox' || (document.forms[0]." . $this->id . "[0] && document.forms[0]." . $this->id . "[0].type=='radio')){
								for(i=0;i<document.forms[0]." . $this->id . ".length;i++) document.forms[0]." . $this->id . "[i].checked=false;
							}
						else document.forms[0]." . $this->id . ".value='';
						}
					 $('#tr_" . $this->id . "').hide();
					}
					else {
				  		$('#tr_" . $this->id . "').show();
					}
					";
                }
            }
        }
        $this->html = "<tr id='tr_" . $this->id . "' style=\"display:\">" . $this->html . "</tr>";
        $this->script = "
				var controllo=function(){
				{$controllo}
				}
				controllo();
				$(\"[name='{$this->attributes['CONDITION']}']\").change(controllo);
				";
    }


    function audit_trail_txt()
    {
        if (class_exists("audit_trail_core")) {
            $audit_trail = new audit_trail_core($this->service, $this->conn, $this->config_service, $this->attributes, $this->xml_form);
            return $audit_trail->audit_trail_txt($this->session_vars);
        } else {
            return '';
        }
    }

    /**
     * Enter description here...
     *
     * @param object $object
     * @return boolean
     */
    function equals($object)
    {
        unset($this->attributes['BYTB']);
        $this->insert_stmt();
        $object->insert_stmt();
        foreach ($this->field_stmt as $key => $currField) {
            if ($this->field_stmt[$key] != $object->field_stmt[$key] || $this->db_vars[$this->field_stmt[$key]] != $object->db_vars[$object->field_stmt[$key]]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Crea campo input per la risoluzione delle discrepanze
     *
     * @return string
     */
    function decision_form($index)
    {
        unset($this->attributes['BYTB']);
        unset($this->session_vars);
        unset($this->db_vars);
        $this->make_open_html();
        $this->input_field = str_replace("document.forms[0]", "document.forms[{$index}]", $this->input_field);
        $this->input_field = preg_replace("/radioclear\(([^\)]*)\)/", "radioclear(\\1,{$index})", $this->input_field);
        $this->input_field = preg_replace("/_cal_anchor/", "_cal_anchor_{$index})", $this->input_field);
        return $this->input_field;
    }

    /**
     * Crea campo input per la risoluzione delle discrepanze
     *
     * @return string
     */
    function comparison_form($index)
    {
        unset($this->attributes['BYTB']);
        $this->attributes['SHOW_SELECTED'] = 'yes';
        $this->make_close_html();
        //$matches=preg_match_all('/<!--dde_start\[(.[^]]*)]\|(.[^|]*)\|-->/',$this->input_field,$match);
        $this->input_field = preg_replace("/<!--dde_start\[(.[^]]*)]\|(.[^|]*)\|-->/", "<span class='compareElement' onclick='$(\"[name=\\1]\").val(\"\\2\");'>", $this->input_field);
        $this->input_field = preg_replace("/<!--dde_end-->/", "</span>", $this->input_field);
        //$this->input_field=preg_replace("/<!--dde_complete-->/",'<a href="#" onclick="$(this).closest(\'td\').find(\'.compareElement\').click();return false; " ><img alt="Select value" src="images/icon_right2_18x18.png" width="15" /></a>',$this->input_field);
        $this->input_field .= ' <a href="#" onclick="$(this).closest(\'td\').find(\'.compareElement\').click();return false; " ><img alt="Select value" src="images/icon_right_18x18.png" width="15" /></a>';

        return $this->input_field;
    }

    /**
     * Prepara le informazioni sul valore per il log del DDE
     *
     * @return array
     */
    function getDDELogInfo()
    {
        if (count($this->value_stmt) == 0) $this->insert_stmt();
        $val['VALDE'] = $this->value_stmt[0];
        $val['D_VALDE'] = $this->value_stmt[1];
        return $val;
    }

}


?>
