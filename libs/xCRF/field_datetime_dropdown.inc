<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_datetime_dropdown extends field
{

    var $datetime_format = "dd/MM/yyyy HH24:mi";
    var $datepicker_format = "dd/MM/yyyy HH:mm";

    /**
     * open_
     * Costruisce il codice html del campo in compilazione
     *
     * @param string $value
     */
    function open_($value)
    {
        $input_html = null;
        $ret = null;
        $date_def = null;


        if ($this->attributes['SAVE'] == "") {
            $this->attributes['SAVE'] = "facoltativo";
        }

        if ($this->attributes['ON_CHANGE'] != '') {
            $var = $this->id;
            $js_on_change = "onchange=\"" . $this->attributes['ON_CHANGE'] . "\"";
        }
//		print_r($this->xml_form->salva_js);
//		$this->xml_form->salva_js='';
//		$this->xml_form->check_js='';
//		print_r($this);
        $in = $this->session_vars;
        $inputval = $this->db_vars;
//		print_r ($inputval);
//		echo $this->attributes['VAR']."<hr>";
        $add_cal = '
		<script language="javascript">
        	new Control.DatePicker(\'' . $this->attributes['VAR'] . '\', { icon: \'images/calendar.png\' , timePicker: true, timePickerAdjacent: true, dateTimeFormat: \'' . $this->datepicker_format . '\'});
        </script>
		 ';

        $txt = $this->testo;
        $keys = array_keys($this->values);
        $value_init = $keys[0];

        $bind_value[$this->xml_form->PK_SERVICE] = $this->session_vars['CODPAT'];
        $bind_value['ESAM'] = $this->session_vars['ESAM'];
        $bind_value['PROGR'] = $this->session_vars['PROGR'];
        $bind_value['VISITNUM'] = $this->session_vars['VISITNUM'];
        $bind_value['VISITNUM_PROGR'] = $this->session_vars['VISITNUM_PROGR'];

        /* Estraggo i valori da DB perchè $inputval taglia l'orario */
        $sql_time = "select to_char(" . $this->attributes['VAR'] . ", '" . $this->datetime_format . "') as " . $this->attributes['VAR'] . "
		from " . $this->xml_form->form['TABLE'] . "
		where " . $this->xml_form->PK_SERVICE . "=:" . $this->xml_form->PK_SERVICE . "
		and ESAM=:ESAM
		and PROGR=:PROGR
		and VISITNUM=:VISITNUM
		and VISITNUM_PROGR=:VISITNUM_PROGR";
        $query_time = new query($this->conn);
        $query_time->exec($sql_time, $bind_value);//binded
        $query_time->get_row();

        $input_element = "<input " . $js_on_change . " readonly=\"readonly\" style=\"color:#666666;padding: 3px;\" type=\"text\" id=\"" . $this->attributes['VAR'] . "\" name=\"" . $this->attributes['VAR'] . "\" class=\"datetimepicker\" value=\"" . $query_time->row[$this->attributes['VAR']] . "\" />";

        if ($value_init == 'sysdate') $value = date("dmY");
        if ($value == '') $value = $value_init;
        if (preg_match("/\//", $value)) {
            $dd = substr($value, 0, 2);
            $mm = substr($value, 3, 2);
            $yyyy = substr($value, 6, 4);
        } else {
            $dd = substr($value, 0, 2);
            $mm = substr($value, 2, 2);
            $yyyy = substr($value, 4, 4);
        }

        $this->validata = true;
        if (isset($in['salva']) and $this->attributes['SAVE'] == 'obbligatorio') {
            if (!checkdate($mm, $dd, $yyyy)) {
                $txt .= "<br/><font color=red size=\"-1\">Error! Date not valid</font>";
                $this->validata = false;
            }
        }
        if (isset($in['invia']) and $this->attributes['SEND'] == 'obbligatorio' && $this->condition_passed) {
            if (!checkdate($mm, $dd, $yyyy)) {
                //echo "<hr>Campo non validato {$this->id}<hr>";
                $txt .= "<br/><font color=red size=\"-1\">Error! Date not valid</font>";
                $this->validata = false;
            }
        }

        $rc = '<input type="hidden" name="' . $this->attributes['VAR'] . 'RC" value="OKOKOK" />';

        $input_html .= $input_element . $add_cal . $rc;
        // echo $input_html."<hr>".$input_element."<hr />";
        if ($this->attributes['DEF'] != '') $input_html .= $this->attributes['DEF'];
        $this->input_field = $input_html;
        $this->input_txt = $txt;
        if (isset($this->attributes['COLSPAN']) and $this->cols_form > 1) $ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
        else $ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . $date_def . '</td>';

        $this->session_vars = $in;
    }

    /**
     * Gestisce l'invocazione di js all'onchange del campo
     *
     * @param String $value
     */
    function open_on_change($value)
    {

        if ($value != "Calcola_Transp_Delay();") {
            $this->salva_js .= "
			$value
			";
            $this->invia_js .= "
			$value
			";
        } else {
            return;
        }
    }

    function close_($value)
    {
        $sstr = null;

        $inputval = $this->session_vars;
        $ret = '<tr id="' . $this->attributes['VAR'] . '" style="display:">';
        $txt = $this->testo;
//		echo $value;
//		print_r($this->db_vars[$this->attributes['VAR'].'RC']);

        $rc = $this->attributes['VAR'] . 'RC';

        $this->input_txt = $txt;

        $bind_value[$this->xml_form->PK_SERVICE] = $this->session_vars['CODPAT'];
        $bind_value['ESAM'] = $this->session_vars['ESAM'];
        $bind_value['PROGR'] = $this->session_vars['PROGR'];
        $bind_value['VISITNUM'] = $this->session_vars['VISITNUM'];
        $bind_value['VISITNUM_PROGR'] = $this->session_vars['VISITNUM_PROGR'];

        /* Estraggo i valori da DB perchè $inputval taglia l'orario */
        $sql_time = "select to_char(" . $this->attributes['VAR'] . ", '" . $this->datetime_format . "') as " . $this->attributes['VAR'] . "
		from " . $this->xml_form->form['TABLE'] . "
		where " . $this->xml_form->PK_SERVICE . "=:" . $this->xml_form->PK_SERVICE . "
		and ESAM=:ESAM
		and PROGR=:PROGR
		and VISITNUM=:VISITNUM
		and VISITNUM_PROGR=:VISITNUM_PROGR";
        $query_time = new query($this->conn);
        $query_time->exec($sql_time, $bind_value);//binded
        $query_time->get_row();

        if ($query_time->row[$this->attributes['VAR']] != "") {
            $input_html = $query_time->row[$this->attributes['VAR']];
            $def = "(" . $this->attributes['DEF'] . ")";
        } else {
            $input_html = "";
            $def = "";
        }

        $this->input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '&nbsp</span></font></i></b>' . $def;

        if (isset($this->attributes['COLSPAN']) and $this->cols_form > 1) $ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
        else
            $ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $sstr . '</td></tr>';
        #return $ret;
    }

    /**
     * Popola le proprieta' "field_stmt" e "value_stmt" necessarie alla costruzione degli stmt di inserimento/update
     *
     */
    function insert_stmt($insert = true)
    {
        //echo "<hr>entra en la funcion";
        $in = $this->session_vars;
        $conn = $this->conn;

        if (isset($this->attributes['FORMAT'])) $format = $this->attributes['FORMAT'];
        else $format = 'DDMMYYYY';
        if (!$insert) {
            $this->field_stmt[0] = "{$this->attributes['VAR']}";
            $this->field_stmt[1] = "{$this->attributes['VAR']}RC";
            return;
        }
        if ($this->attributes['TB'] != 'no') {

            $this->field_stmt[0] = "{$this->attributes['VAR']}";
            $this->field_stmt[1] = "{$this->attributes['VAR']}RC";
//			if($in[$this->attributes['VAR']] != ""){
//				$in[$this->attributes['VAR']] = $in[$this->attributes['VAR']].":00";
//			}
            $this->value_stmt[0] = "to_date('" . $in[$this->attributes['VAR']] . "', 'DD/MM/YYYY HH24:MI')";
            $this->value_stmt[1] = $in[$this->attributes['VAR'] . 'RC'];

//			print($this->value_stmt[0]."<hr />");
//			print($this->value_stmt[1]."<hr />");
        }

//		echo "<hr>ESTO ES LO QUE SE INSERTA!";
//		print_r($this->value_stmt);
//		echo "<hr>";
//
        return;
    }

    /**
     * allinea_db
     * Costruisce l'array dei campi necessari da creare in DB     *
     *
     * @return array
     */
    function allinea_db()
    {
        if ($this->attributes['TB'] != 'no') {
            $ret[0] = "{$this->attributes['VAR']} DATE";
            $ret[1] = "{$this->attributes['VAR']}RC VARCHAR2(8)";
            return $ret;
        } else return;
    }

    /**
     * open_save
     * Costruisce i controlli javascript e lato server per il salvataggio della scheda
     *
     * @param string $val
     */
    function open_save($val)
    {
        #echo "<hr>{$this->testo}";
        $testo = make_js($this->testo);
//		echo $val;

        $this->condition_passed = true;

        $in = $this->session_vars;
        $insert_errors = $this->errors;
        if ($in['invia'] != '' || $in['INVIOCO'] == '0') {
            if ($this->condition_passed) {
                if ($in[$this->attributes['VAR']] == '' && $this->attributes['SAVE'] != 'facoltativo') {
                    $this->validata = false;
                    $testo_js = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "Il campo &egrave; obbligatorio";
                }
            } else {
                if ($in[$this->attributes['VAR']] != '') {
                    $this->validata = false;
                    $testo_js = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "Il campo deve essere vuoto";
                }
            }
        }
    }

    /**
     * open_send
     * Costruisce i controlli javascript e lato server per l'invio della scheda
     *
     * @param string $val
     * @return bool
     */
    function open_send($val)
    {
        #echo "<hr>{$this->testo}";
        $testo = make_js($this->testo);
//		echo $val;

        $in = $this->session_vars;
        $insert_errors = $this->errors;

        if ($this->attributes['LABEL_JS'] != "") {
            $testo = make_js($this->attributes['LABEL_JS']);
        }

        if ($this->config_service['lang'] == "en") {
            $alert_msg = 'Warning. Incorrect format in the field\n' . $testo . '::\ncannot be blank.';
        } else {
            $alert_msg = 'Attenzione. Valore non corretto nel campo\n' . $testo . '::\non pu&ograve; essere vuoto.';
        }

        if ($val == 'obbligatorio') {
            $this->invia_js = "
				var f = document.forms[0];
				var el = f.elements;
				if(f.{$this->attributes['VAR']}.value=='')
						{
							alert('" . $alert_msg . "');
							this.focus();
							return false;
						}
						";
        }

        $this->condition_passed = true;
        if ($in['invia'] != '' || $in['INVIOCO'] == '1') {
            if ($this->condition_passed) {
                if ($in[$this->attributes['VAR']] == '' && $this->attributes['SEND'] != 'facoltativo') {
                    $this->validata = false;
                    $this->errors[$this->attributes['VAR']] = "Il campo &egrave; obbligatorio";
                }
            } else {
                if ($in[$this->attributes['VAR']] != '') {
                    $this->validata = false;
                    $testo_js = make_js($this->testo);
                    $this->errors[$this->attributes['VAR']] = "Il campo deve essere vuoto";
                }
            }
        }


    }
}


?>