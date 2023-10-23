<?

include_once "field_textbox.inc";

/**
 * Classe per la gestione dei campi di tipo textbox
 *
 * @package Fields
 */
class field_textbox_extended extends field_textbox
{
    var $max_js;
    var $min_js;

    /**
     * Costruisce il codice html del campo in compilazione
     *
     * @param String $value
     */
    function open_($value)
    {
        $agg_ = null;
        global $in;
        $in = $this->session_vars;
        //		echo $in['USER_TIP'];
        //		global $inputval;
        $inputval = $this->db_vars;
        $txt = $this->testo;
        if ($this->attributes ['CHECK'] == '')
            $this->attributes ['CHECK'] = "text";

        if ($this->attributes ['SIZE'] == '')
            $this->attributes ['SIZE'] = '20';

        if ($this->attributes ['ONCHANGE'] != '')
            $onchange = "{$this->attributes['ONCHANGE']};";

        if (isset ($this->values) && is_array($this->values))
            foreach ($this->values as $key => $val)
                $value = $val;
        if ($inputval [$this->attributes ['VAR']] != '')
            $value = $inputval [$this->attributes ['VAR']];
        if ($in [$this->attributes ['VAR']] != '')
            $value = $in [$this->attributes ['VAR']];

        if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
            if ($value == -9911)
                $value = "NA";
            if ($value == -9922)
                $value = "NK";
            if ($value == -9933)
                $value = "ND";
            if ($value == -9944)
                $value = "NP";
            if ($value == -9955)
                $value = "TE";
            if ($value == -9900)
                $value = "OT";

        }

        $disabled = "";
        if ($this->attributes ['DISABLED'] != '') {
            if ($value != '')
                $disabled = "disabled=\"disabled\"";
            $this->check_js .= "
				if (document.forms[0].{$this->id}.value!='') document.forms[0].{$this->id}.disabled=true;
			";
        }
        if ($this->attributes['BLOCK_VALUE'] == 'yes' && $this->db_vars[$this->attributes['VAR']] != "") {
            $disabled = "disabled=\"disabled\"";
        }
        $action = "";

        if ($this->attributes ['ON_ACTION'] != '' && $this->attributes ['ACTION_TYPE'] != '') {
            $action = $this->attributes ['ACTION_TYPE'] . "=\"" . $this->attributes ['ON_ACTION'] . "\"";
            //         echo "$action<hr>";
        }

        if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes') {
            $html_parser = new HTML_Parser ();
            $html_parser->setAttribute("type", "hidden");
            $html_parser->setAttribute("name", $this->attributes ['VAR']);
            $html_parser->setContent($value);
            $html_parser->setType("INPUT");
            $this->input_field = '***' . $html_parser->print_();
            //$this->input_field='***<input type="hidden" name="'.$this->attributes['VAR'].'"  value="'.$value.'"/>';
        } else {
            if ($this->attributes ['EMAIL'] != '') {
                $val_email = explode("@", $value);
                $this->input_field = "<input type=\"text\" name=\"{$this->attributes['VAR']}_0\" value=\"{$val_email[0]}\">@<input type=\"text\" size='20' name=\"{$this->attributes['VAR']}_1\" value=\"{$val_email[1]}\" onblur=\"document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].{$this->attributes['VAR']}_0.value+'@'+document.forms[0].{$this->attributes['VAR']}_1.value\"><input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
            } else {
                //          echo "$action<hr>";
                if ($this->attributes ['CALL_CF'] != '')
                    $cf_call = "cf();";
                if ($this->attributes ['ON_BLUR'] != '') {
                    //echo "<hr>{$this->id}<hr>";
                    $var = $this->id;
                    $vars = explode("_PROGR_", $var);
                    $js_on_blur = preg_replace("/document\.forms\[0\]\.(.*?)\.value/i", "document.forms[0].\\1_PROGR_{$vars[1]}.value", $this->attributes ['ON_BLUR']);
                    //print_r($this->attributes);
                    $cf_call .= "{$js_on_blur};";
                    //echo "<li>$js_on_blur</li>";
                }

                $value = str_replace("\"", "&quot;", $value);
                $html_parser = new HTML_Parser ();
                $html_parser->setAttribute("type", "text");
                $html_parser->setAttribute("maxlength", $this->attributes ['VAR_SIZE']);
                $html_parser->setAttribute("size", $this->attributes ['SIZE']);
                $html_parser->setAttribute("name", $this->attributes ['VAR']);
                $html_parser->setAttribute("onblur", $cf_call);
                if ($this->attributes['ONCHANGE'] != '') $html_parser->setAttribute("onchange", $onchange);
                $html_parser->setAttribute($disabled, "");
                $html_parser->setAttribute($action, "");
                $html_parser->setContent($value);
                $html_parser->setType("INPUT");
                $this->input_field = $html_parser->print_() . $this->attributes ['DEF'] . $agg_;
                /*
                $this->input_field='<input  type="text" maxlength="'.$this->attributes['VAR_SIZE'].'" size="'.$this->attributes['SIZE'].'"
                name="'.$this->attributes['VAR'].'" value="'.$value.'"
                onblur="'.$cf_call.'" '.
                $disabled.
                $action.'>'.$this->attributes['DEF'].''.$agg_;
                */

            }
        }
        $this->input_txt = $txt;
        if ($this->attributes ['TEXTONLY'] == "yes") {
            $this->input_txt = $value;
            $this->input_field = '';
        }
        //if ($this->attributes['DISABLED']!='') $this->input_field='<input type=\'hidden\' name="'.$this->attributes['VAR'].'" value="'.$value.'"><b>'.$value.'</b>';
    }

    /**
     * Controlli sul campo di tipo codice fiscale
     *
     * @param String $value
     */
    function open_codfisc($value)
    {

        //traduzione del messaggio di alert in inglese
        if ($this->config_service ['lang'] == "en")
            $alert_msg = "Warning the fiscal code must be 16 characters ";
        else
            $alert_msg = "Attenzione il codice fiscale deve essere di 16 caratteri ";

        $this->invia_js .= "
			if (document.forms[0].{$this->id}.value.length!=16){
				alert('" . $alert_msg . "');
				document.forms[0].{$this->id}.focus();
				return false;
			}
		";
        $this->salva_js .= "
			if (document.forms[0].{$this->id}.value.length!=16){
				alert('" . $alert_msg . "');
				document.forms[0].{$this->id}.focus();
				return false;
			}
		";
    }

    /**
     * Costruisce il codice html del campo in visualizzazione
     *
     * @param String $value
     */
    function close_($value)
    {
        //global $in;

        if ($this->attributes['VAR_EXT'] != "" && $value != "")
            $value = $this->fields_value_ext($value);

        if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
            if ($value == -9911)
                $value = "NA";
            if ($value == -9922)
                $value = "NK";
            if ($value == -9933)
                $value = "ND";
            if ($value == -9944)
                $value = "NP";
            if ($value == -9955)
                $value = "TE";
            if ($value == -9900)
                $value = "OT";

        }
        $in = $this->session_vars;
        $ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
        $txt = $this->testo;
        if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes')
            $input_html = '***';
        else
            $input_html = $value;
        if ($input_html == '')
            $input_html = '&nbsp;';
        $this->input_txt = $txt;

        $this->input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>' . $this->attributes ['DEF'];
        if (isset ($this->attributes ['COLSPAN']) and $this->cols_form > 1)
            $ret .= '<td  class="input_txt" colspan="' . $this->cols_form . '">' . $txt . $input_html . '';
        else
            $ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>';

        #return $ret;
    }

    /**
     * Recupera i possibili valori del campo da una quesry di decodifica
     *
     * @param String $value
     */
    function fields_value_ext($value)
    {

        /*
         *
         * La magia risiede qui
         * var_ext="CODICE_FARMACO" tb_ext="farmaci_checkin" where_ext="CODICE_FARMACO=[AIC6]" label_ext="Aic6"
         *
         */

        $in = $this->session_vars;
        $inputval = $this->db_vars;
        //if ($this->xml_form->closed){// && $this->xml_form->form['NO_LOAD_BYTB']=="yes"){
        //	$this->values[$inputval[$this->attributes['VAR']]]=$inputval['D_'.$this->attributes['VAR']];
        //	return ;
        //}

        //if($inputval!=null) {

        $var_ext = $this->attributes['VAR_EXT'];
        $tb_ext = $this->attributes['TB_EXT'];
        $where_ext = $this->attributes['WHERE_EXT'];
        $label_ext = $this->attributes['LABEL_EXT'];
        $css_ext = $this->attributes['CSS_EXT'];


        $label_ext = str_replace("#BR#", "<br />", $label_ext);
        $label_ext = str_replace("#BR /#", "<br />", $label_ext);
        $label_ext = str_replace("#br#", "<br />", $label_ext);
        $label_ext = str_replace("#br /#", "<br />", $label_ext);
        $label_ext = str_replace("#i#", "<i>", $label_ext);
        $label_ext = str_replace("#/i#", "</i>", $label_ext);

        //echo "<br>prima ".$where_ext." ";
        $where_ext = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $where_ext);
        //$where_ext=preg_replace("/\[(.*?)\]/e",$inputval['\\1'] , $where_ext);
        //echo "<br>dopo ".$where_ext."<br>-----------------------------------------<br>";
        $label_ext = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $label_ext);
        $var_ext = preg_replace("/\[(.*?)\]/e", "var_glob('\\1')", $var_ext);

        $conn = $this->conn;

        $query = "select $var_ext as code";
        if ($where_ext != '') $where = "where $where_ext";

        $query .= " from $tb_ext $where and rownum=1";

        $sql = new query($conn);
        $sql->exec($query);//complessa var_glob Carlo

        if ($sql->numrows > 0) {
            $sql->get_row();

            $in = $this->session_vars;

            $sql->row['CODE'] = str_replace("\"", "", $sql->row['CODE']);
            $value = str_replace("\"", "", $value);

            $trimmed_sql_result = str_replace("'", "", $sql->row['CODE']);
            $trimmed_value = str_replace("'", "", $value);

            if (strtoupper($trimmed_sql_result) != strtoupper($trimmed_value)) {
                $value = "$label_ext: " . $sql->row['CODE'] . "<br /> [" . $value . "]";
            }
        }
        return $value;
    }

    /**
     * Gestisce la compilazione automatica del campo
     *
     * @param String $value
     */
    function open_compila($value)
    {
        #echo "<hr>$value";
        $this->check_js .= "
					if (document.forms[0]." . $this->attributes ['COMPILA_CONDITION_VAR'] . ".value==" . $this->attributes ['COMPILA_CONDITION_VALUE'] . "){
						compila_value=document.forms[0]." . $this->attributes ['COMPILA'] . ".value;
						if (compila_value>0){
							document.forms[0]." . $this->id . ".value=compila_value;
							document.forms[0]." . $this->id . ".disabled=true;
						}
					}
			";
    }

    /**
     * Controlli sul valore (maggiore)
     *
     * @param String $value
     */
    function open_max($value)
    {
        if (preg_match("/\[/", $value)) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $value);
            $this->controlli .= "
						value=value_of('" . $campo . "', '0');
						";
            if ($this->attributes ['SAVE'] != '')
                $this->salva_js .= "
						value=value_of('" . $campo . "', '0');
						";
        } else {
            $value -= 0;
            $this->controlli .= "value=$value;\n";
            if ($this->attributes ['SAVE'] == 'obbligatorio')
                $this->salva_js .= "value=$value;\n";
        }
        if ($this->attributes ['VAR_TYPE'] == 'number') {
            $this->controlli .= "
			value=parseFloat(value);
			";
            if ($this->attributes ['SAVE'] != '')
                $this->salva_js .= "
					value=parseFloat(value);
						";

        }
        //traduzione del messaggio di alert in inglese
        if ($this->config_service ['lang'] == "en")
            $alert_msg = "Warning the value must be less than ";
        else
            $alert_msg = "Attenzione il valore deve essere minore di ";
        if ($this->attributes['SEND'] == 'obbligatorio') {
            //E.Gargano 15/05/09
            //controllo se la condizione si è verificata in js
            $cond = $this->attributes['CONDITION'];
            $val_cond = $this->attributes['CONDITION_VALUE'];
            if ($this->attributes['CONDITION'] != '') {
                $this->controlli .= "
				if (document.forms[0]." . $cond . ".value==$val_cond)";
            }
            //E.Gargano 15/05/09 fine
            $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value>value) {";

        } else {
            $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value>value) {";
        }
        /*Coomentato da Giorgio Delsignore il 31/05/2010 per inserire la parte soprastante che verifica le condizioni per i campi obbligatori
        if ($this->attributes ['SEND'] == 'obbligatorio')
            $this->controlli .= "
                if (document.forms[0]." . $this->id . ".value>value) {";
        else
            $this->controlli .= "
                if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value>value) {";*/
        $this->controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";

        if ($this->attributes ['SAVE'] == 'obbligatorio')
            $this->salva_js .= "
				if (document.forms[0]." . $this->id . ".value>value) {
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";

        //		echo $this->controlli;
    }

    /**
     * Controlli sul valore (minore)
     *
     * @param String $value
     */
    function open_min($value)
    {
        if (preg_match("/\[/", $value)) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $value);
            $this->controlli .= "
						value=value_of('" . $campo . "', '0');
						";
            if ($this->attributes ['SAVE'] != '')
                $this->salva_js .= "
						value=value_of('" . $campo . "', '0');
						";
        } else {
            $value -= 0;
            $this->controlli .= "value=$value;\n";
            if ($this->attributes ['SAVE'] == 'obbligatorio')
                $this->salva_js .= "value=$value;\n";
        }
        if ($this->attributes ['VAR_TYPE'] == 'number') {
            $this->controlli .= "
			value=parseFloat(value);
			";
            if ($this->attributes ['SAVE'] != '')
                $this->salva_js .= "
					value=parseFloat(value);
						";

        }

        $testo = make_js($this->testo);

        /* Nicola 20/01/2010
         * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
         */
        if ($this->attributes['LABEL_JS'] != "") {
            $testo = $this->attributes['LABEL_JS'];
        }

        //traduzione del messaggio di alert in inglese
        if ($this->config_service ['lang'] == "en")
            $alert_msg = "Warning the value {$testo} must be greater than ";
        else
            $alert_msg = "Attenzione il valore di {$testo} deve essere maggiore di ";
        if ($this->attributes['SEND'] == 'obbligatorio') {
            //E.Gargano 15/05/09
            //controllo se la condizione si è verificata in js
            $cond = $this->attributes['CONDITION'];
            $val_cond = $this->attributes['CONDITION_VALUE'];
            if ($this->attributes['CONDITION'] != '') {
                $this->controlli .= "
				if (document.forms[0]." . $cond . ".value==$val_cond)";
            }
            //E.Gargano 15/05/09 fine
            $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value<=value) {";

        } else {
            $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value<=value) {";
        }
        /*if ($this->attributes ['SEND'] == 'obbligatorio')
            $this->controlli .= "
                if (document.forms[0]." . $this->id . ".value<=value) {";
        else
            $this->controlli .= "
                if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value<=value) {";*/
        $this->controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";
        if ($this->attributes ['SAVE'] == 'obbligatorio')
            $this->salva_js .= "
				if (document.forms[0]." . $this->id . ".value<=value) {
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";

    }

    /**
     * Controlli sul valore (minore o uguale)
     *
     * @param String $value
     */
    function open_min_eq($value)
    {
        if (preg_match("/\[/", $value)) {
            $campo = preg_replace("/\[(.*?)\]/e", "$1", $value);
            $this->controlli .= "
						value=value_of('" . $campo . "', '0');
						";
            if ($this->attributes ['SAVE'] != '')
                $this->salva_js .= "
						value=value_of('" . $campo . "', '0');
						";
        } else {
            $value -= 0;
            $this->controlli .= "value=$value;\n";
            if ($this->attributes ['SAVE'] == 'obbligatorio')
                $this->salva_js .= "value=$value;\n";
        }
        if ($this->attributes ['VAR_TYPE'] == 'number') {
            $this->controlli .= "
			value=parseFloat(value);
			";
            if ($this->attributes ['SAVE'] != '')
                $this->salva_js .= "
					value=parseFloat(value);
						";

        }
        //traduzione del messaggio di alert in inglese
        if ($this->config_service ['lang'] == "en")
            $alert_msg = "Warning the value must be equal to or greater than ";
        else
            $alert_msg = "Attenzione il valore di \"" . make_js($this->testo) . "\" deve essere maggiore o uguale a ";

        if ($this->attributes ['SEND'] == 'obbligatorio')
            $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value<value) {";
        else
            $this->controlli .= "
				if (document.forms[0]." . $this->id . ".value!='' && document.forms[0]." . $this->id . ".value<value) {";
        $this->controlli .= "
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";
        if ($this->attributes ['SAVE'] == 'obbligatorio')
            $this->salva_js .= "
				if (document.forms[0]." . $this->id . ".value<value) {
					alert('" . $alert_msg . "'+value);
					document.forms[0]." . $this->id . ".focus();
					return false;
				}
		";

    }

    /**
     * Controlli sull'operazione di divisione
     *
     * @param String $val
     */
    function open_dividendo($val)
    {
        global $in;
        $dividendo = $this->attributes ['DIVIDENDO'];
        if (preg_match("/\[/", $dividendo)) {
            $dividendo = preg_replace("/\[(.*?)\]/e", "$1", $dividendo);
            $this->check_js .= "
				value=value_of('$dividendo', '0');
				value=value-0;
					";
            $dividendo = $in [$dividendo] + 0;
        } else
            $this->check_js .= "
				value=$dividendo;
				";
        $divisore = $this->attributes ['DIVISORE'];
        #echo "<hr>$divisore<hr>";
        if (preg_match("/\[/", $divisore)) {
            $divisore = preg_replace("/\[(.*?)\]/e", "$1", $divisore);
            $this->check_js .= "
				divisore=value_of('$divisore', '0');
				divisore=divisore-0;
					";
            $divisore = $in [$divisore] + 0;
        } else
            $this->check_js .= "
				divisore=$divisore;
				";
        $this->check_js .= " \n
				//value=value_of('$dividendo', '0');
				//value=value-0;
				valore=value/divisore;
				document.forms[0]." . $this->attributes ['VAR'] . ".value=valore;
				";
        $valore = $dividendo / $divisore;
        $in [$this->attributes ['VAR']] = $valore;
    }

    /**
     * Controlli di uguaglianza
     *
     * @param String $val
     */
    function open_equals($val)
    {
        $t = str_replace("*", "", $this->testo);
        $this->invia_js .= "value=$val;\n";

        //traduzione del messaggio di alert in inglese
        if ($this->config_service ['lang'] == "en")
            $alert_msg = "must be";
        else
            $alert_msg = "deve essere";

        $this->invia_js .= "
				if (document.forms[0]." . $this->attributes ['VAR'] . ".value!=value) {
					alert('{$t} " . $alert_msg . " '+value);
					document.forms[0]." . $this->attributes ['VAR'] . ".focus();
					return false;
				}
		";

    }

    /**
     * Esegue del codice javascript
     *
     * @param String $value
     */
    function open_execute($value)
    {
        $this->check_js .= "
      $value" . ";";
    }

    /**
     * Esegue del codice js all'onchange
     *
     * @param String $value
     */
    function open_on_change($value)
    {
        $this->check_js .= "$value
		";
    }

    /**
     * Gestione dello sfoglia su dizionari
     *
     * @param String $value
     */
    function open_sfoglia($value)
    {
        $tip_sfo = explode(";", $value);
        for ($f = 0; $f < count($tip_sfo); $f++) {
            //         echo "$f--$tip_sfo[$f]<hr>";
            $but = explode(",", $tip_sfo [$f]);
            $but_text = $but [0];
            $but_file = $but [1];
            $but_file = preg_replace("!\[(.*?)\]!i", '$1', $but_file);
            $but_file = str_replace("|and|", '&', $but_file);

            if ($this->attributes ['SFOGLIA_ADD_PARAM'] != '') {
                $params = explode(",", $this->attributes ['SFOGLIA_ADD_PARAM']);
                foreach ($params as $key => $val) {
                    $but_file .= "&{$val}={$_GET[$val]}";
                }
            }
            if (preg_match('/^js:/', $but_text)) {
                $but_text = str_replace("js:", "", $but_text);
                $agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
            } else {
                if (strtolower($but_text) == 'reset' || strtolower($but_text) == 'cancella' || $this->attributes['SFOGLIA_CLEAR_LABEL'] == $but_text)
                    $agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
                else
                    $agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"apri_window('/$but_file');return false;\">";
                //         echo "$but_text -- $but_file<hr>";
                $this->input_field .= $agg;
            }
        }
    }

    /**
     * Effettua in js operazione di somma
     *
     * @param String $val
     */
    function open_sum($val)
    {
        global $in;
        $campi = explode(",", $val);
        $minval = $this->attributes ['SUM_MAGGIORE'] + 0;
        $maxval = $this->attributes ['SUM_MINORE'] + 0;
        $check = "if (value >= $minval)";
        if ($maxval > 0)
            $check = "if (value >= $minval && value <= $maxval)";
        $somma = 0;
        for ($i = 0; $i < count($campi); $i++) {
            if ($i == 0)
                $this->check_js .= " \n
					document.forms[0]." . $this->attributes ['VAR'] . ".value='';
				";
            if (preg_match("/\[/", $campi [$i])) {
                $campo = preg_replace("/\[(.*?)\]/e", "$1", $campi [$i]);
                $somma += $in [$campo];
                $this->check_js .= "
						value=value_of('" . $campo . "', '0');
						value=value-0;
						//alert (value);
						";
            } else {
                $somma += $campi [$i];
                $this->check_js .= "
						value=" . $campi [$i] . ";
						";
            }
            $this->check_js .= "
					//$check {
					somma=document.forms[0]." . $this->attributes ['VAR'] . ".value - 0;
					somma+=value;
					document.forms[0]." . $this->attributes ['VAR'] . ".value=somma;
					//}
				";
        }
        $in [$this->attributes ['VAR']] = $somma;
    }

    /**
     * Trasforma il campo in uppercase
     *
     * @param String $value
     */
    function open_upper($value)
    {
        $this->check_js .= "
			document.forms[0].{$this->id}.value=document.forms[0].{$this->id}.value.toUpperCase();
		";
    }

    /**
     * Visualizzazione nella modalità  progressiva
     *
     * @param String $var
     * @param number $i
     * @param array $row
     * @param boolean $this_closed
     * @return String
     */
    function all_in($var, $i, $row, $this_closed)
    {
        /*if($this_closed=='' || $this_closed==null) {
            $this_closed=true;
        }*/

        $val = $this->attributes;
        $row[$val['VAR']] = str_replace("\"", "'", $row[$var]);
        //if ($this_closed){

        if ($this->attributes['VAR_EXT'] != "" && $row[$var] != '') {
            $row[$var] = $this->fields_value_ext($row[$var]);
        }
        $body = "
			<td class=sc4bis>
				<b>{$row[$var]}</b>
				</td>
				";
        $ret['body'] = $body;
        return $ret;
    }

    /**
     * Visualizzazione nella modalità  progressiva (header)
     *
     * @param field_textbox $field
     * @param number $m_p
     * @param form $xml_form
     * @return String
     */
    static function S_all_in($field, $m_p, $xml_form)
    {
        $field_tot = null;
        $tr_agg = null;
        $select_field = $field . ",";
        if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
            $onclick_action = "";
            for ($i = 1; $i <= $m_p; $i++) {
                $onclick_action .= "document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}.value=document.forms['ALL_IN_FORMS'].{$field}_TOT.value;
			";
            }
            $field_tot .= "
			<input type='textbox' name='{$field}_TOT'><br />
			<input type='button' value='applica a tutti' onclick=\"
			$onclick_action
			\">
		";
            $tr_agg .= "<td class=int>$field_tot &nbsp;</td>";
        }
        return $tr_agg;
    }
}

?>
