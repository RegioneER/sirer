<?

include_once "field.inc";

/**
 * Classe per la gestione di campi nascosti
 *
 * @package Fields
 */
class field_hidden extends field
{

    /**
     * Costruisce il codice html del campo in compilazione
     *
     * @param String $value
     */
    function open_($value)
    {
        $inputval = $this->db_vars;
        $in = $this->session_vars;

        //    echo $this->attributes['VAR'].":".$value."<hr>";
        //echo "<hr>{$this->attributes['VAR']} - $value a \"sysdate\"<hr>";
        if ("{$value}" == "sysdate") {
            //echo "<hr>{$this->attributes['VAR']} - $value a \"sysdate\"<hr>";
            $value = date("dmY");
            //echo "{$this->attributes['VAR']} sono qui - $value a ";
        }
        if ($value == '') {
            if (count($this->values) > 0)
                if (isset($this->values) && is_array($this->values))
                    foreach ($this->values as $key => $val) {
                        $value = $key;
                        $inputval[$this->attributes['VAR']] = $value;
                        #echo "<hr> ".$this->attributes['VAR']." ==$value";
                    }
        }
        if ($in[$this->attributes['VAR']] != '') $value = $in[$this->attributes['VAR']];
        $value = str_replace("\"", "&quot;", $value);
        #	echo $this->attributes['VAR']." - $value<hr>";
        if (isset($in['TB_COLL']) && $in['TB_COLL'] != '') $this->input_field = '<input type="hidden" name="TB_COLL_' . $in['ID_REF'] . '_' . $this->attributes['VAR'] . '" value="' . $value . '"/>';
        else $this->input_field = '<input type="hidden" name="' . $this->attributes['VAR'] . '" value="' . $value . '"/>';
    }

    /**
     * Gestisce la compilazione automatica del campo
     *
     * @param String $value
     */
    function open_compila($value)
    {
        $condition_var = $this->attributes['COMPILA_CONDITION_VAR'];
        $condition_val = $this->attributes['COMPILA_CONDITION_VALUE'];
        if ($this->attributes['COND_OP']) $operatore_confronto = $this->attributes['COND_OP'];
        else $operatore_confronto = "==";
        $operatore = $this->attributes['COMPILA_OP'];
        $operatore = str_replace("AND", "&&", $operatore);

        if ($operatore == '') $operatore = "&&";
        //echo "$operatore<hr>";
        $vars = explode("|", $condition_var);
        $valuess = explode("|", $condition_val);
        //		print_r($vars);
        //		print_r($valuess);
        $valore_var = "";
        $valori = "";
        $condizioni_tot = "";
        foreach ($vars as $key => $var) {
            $valore_var .= "value_{$var}=value_of('{$var}','0');\n
			//alert (value_{$var});\n";
            $valori .= " - '+value_{$var}+'";
            $values = explode(",", $valuess[$key]);
            $condizioni = "";
            //			print_r($values);
            foreach ($values as $kv => $val) {
                if ($condizioni != '') $condizioni .= " || ";
                $condizioni .= "value_{$var}{$operatore_confronto}'{$val}'";
                //				echo "$condizioni<hr>";
            }
            if ($condizioni_tot != '') {
                $condizioni_tot .= " $operatore ";
            };
            $condizioni_tot .= "($condizioni)";
        }
// 		Logger::info($condizioni_tot) ;
        $js_cond = "
		$valore_var
		//alert(value_UFF_COMP+' - '+value_TIPO_PRATICA);
		\r\n
		//alert('valore da impostare: $value - condizioni $valori');
		if ($condizioni_tot) document.forms[0].{$this->attributes['VAR']}.value='$value';
		else document.forms[0].{$this->attributes['VAR']}.value='';
		//alert('valore impostato:'+document.forms[0].{$this->attributes['VAR']}.value);
		";
        $this->check_js .= $js_cond;
    }

    /**
     * Gestisce controlli aggiuntivi
     *
     * @param String $value
     */
    function open_controll($value)
    {
        $check = '';
        $param = explode("=", $value);
        $vars = $param[0];
        $vals = $param[1];
        $vars = explode(",", $vars);
        $vals = explode(",", $vals);
        for ($i = 0; $i < count($vars); $i++) {
            if ($check != '') $check .= " && ";
            $check .= "document.forms[0].{$vars[$i]}.value=='{$vals[$i]}'";
        }
        $this->invia_js .= "
			document.forms[0].{$this->attributes['VAR']}.value='0';
			if ($check) document.forms[0].{$this->attributes['VAR']}.value='1';
			//alert (document.forms[0].{$this->attributes['VAR']}.value);
			//return false;
			";
    }

    /**
     * Gestisce la funzione di operazione di divisione
     *
     * @param String $val
     */
    function open_dividendo($val)
    {
        $in = $this->session_vars;
        $dividendo = $this->attributes['DIVIDENDO'];
        if (preg_match("/\[/", $dividendo)) {
            $dividendo = preg_replace("/\[(.*?)\]/e", "$1", $dividendo);
            $this->check_js .= "
			value=value_of('$dividendo', '0');
			value=value-0;
				";
            $dividendo = $in[$dividendo] + 0;
        } else $this->check_js .= "
			value=$dividendo;
			";
        $divisore = $this->attributes['DIVISORE'];
        #echo "<hr>$divisore<hr>";
        if (preg_match("/\[/", $divisore)) {
            $divisore = preg_replace("/\[(.*?)\]/e", "$1", $divisore);
            $this->check_js .= "
			divisore=value_of('$divisore', '0');
			divisore=divisore-0;
				";
            $divisore = $in[$divisore] + 0;
        } else $this->check_js .= "
			divisore=$divisore;
			";
        $this->check_js .= " \n
			//value=value_of('$dividendo', '0');
			//value=value-0;
			valore=value/divisore;
			
			if (isNaN(parseInt(valore)) || isNaN(valore)) valore=0;
			//alert (valore);
			document.forms[0]." . $this->attributes['VAR'] . ".value=valore;
			";
        $valore = $dividendo / $divisore;
        $in[$this->attributes['VAR']] = $valore;
    }

    /**
     * Gestisce la funzione di numero random
     *
     * @param String $value
     */
    function open_rand($value)
    {
        #echo "<hr>$value - {$this->attributes['RAND_VAR']}<hr>";
        $value -= 1;
        $this->invia_js .= "
			if (value_of('{$this->attributes['RAND_VAR']}')=='1') document.forms[0].{$this->attributes['VAR']}.value=Math.round({$value}*Math.random())+1;
			//alert ( document.forms[0].{$this->attributes['VAR']}.value);
			//return false;
		";
    }

    /**
     * Gestisce l'operazione di somma
     *
     * @param String $val
     */
    function open_sum($val)
    {
        $in = $this->session_vars;
        $campi = explode(",", $val);
        $minval = $this->attributes['SUM_MAGGIORE'] + 0;
        $maxval = $this->attributes['SUM_MINORE'] + 0;
        $check = "if (value >= $minval)";
        if ($maxval > 0) $check = "if (value >= $minval && value <= $maxval)";
        $somma = 0;
        for ($i = 0; $i < count($campi); $i++) {
            if ($i == 0) $this->check_js .= " \n
				document.forms[0]." . $this->attributes['VAR'] . ".value='';
			";
            if (preg_match("/\[/", $campi[$i])) {
                $campo = preg_replace("/\[(.*?)\]/e", "$1", $campi[$i]);
                $somma += $in[$campo];
                $this->check_js .= "
					value=value_of('" . $campo . "', '0');
					value=value-0;
					//alert (value);
					";
            } else {
                $somma += $campi[$i];
                $this->check_js .= "
					value=" . $campi[$i] . ";
					";
            }
            $this->check_js .= "
					$check {
					somma=document.forms[0]." . $this->attributes['VAR'] . ".value - 0;
					somma+=value;
					document.forms[0]." . $this->attributes['VAR'] . ".value=somma;
					}
				";
        }
        $in[$this->attributes['VAR']] = $somma;
    }

    /**
     * Gestisce la modalit in tabella delle schede progressive
     *
     * @param String $var
     * @param number $i
     * @param array $row
     * @param boolean $this_closed
     * @return String
     */
    function all_in($var, $i, $row, $this_closed)
    {
        //se il campo nascosto  CENTER, nn gli viene passato nulla da banca dati, e $this->values ha un UNICO elemento
        if ($row[$var] == '' && $var == 'CENTER' && count($this->values) == 1) {
            //copio l'array in uno temporaneo
            $array = $this->values;
            // estraggo il primo valore (l'array  tipo array('001'=>'001')
            //imposto il valore del campo uguale al centro.
            $valore = array_shift($array);
        } else
            $valore = $row[$var];

        if (!$this_closed) {
            $body = "<input type='hidden' name='{$var}_PROGR_{$i}' value=\"$valore\">";
        } else $body = "";
        $ret['body'] = $body;
        return $ret;
    }

    /**
     * Metodo statico per la gestione della modalit di visualizzazione in tabella per schede progressive
     *
     * @param unknown_type $field
     * @param unknown_type $m_p
     * @param unknown_type $xml_form
     * @return unknown
     */
    static function S_all_in($field, $m_p, $xml_form)
    {
        $tr_agg = null;
        return $tr_agg;
    }

    function builder_js()
    {
        $field_description['field'] = "hidden";
        $field_description['order'] = 1;

        $this->open_('', true);

        $field_description['view'] = "\"<div style=\'background-color:#FFFFDD;padding:3px;\' class=\'hidden-<%= rf.get(Formbuilder.options.mappings.VAR) %>\'><input type=\'text\'/> <em><label>\\n  <span><%= rf.get(Formbuilder.options.mappings.VAR) %> (hidden value)</em></div>\"";

        /*$field_description['view']= <<< EOT
            "<div style='background-color:#FFFFDD;padding:3px'><input type='text' class='rf-size-<%= rf.get(Formbuilder.options.mappings.VAR_SIZE) %>' /> <em><label>\n  <span><%= rf.get(Formbuilder.options.mappings.VAR) %> (hidden value)</em></div>"
EOT;*/
        $field_description['edit'][] = 'edit/db_info';
        $field_description['edit'][] = 'edit/value';
        $field_description['edit'][] = 'edit/bytb';
        $field_description['addButton']['class'] = 'fa fa-header';
        $field_description['addButton']['icon'] = '<b>H</b>';
        $field_description['addButton']['label'] = 'Hidden';

        return $field_description;

    }


}

?>