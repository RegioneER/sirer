<?php 
/**
 * @package Fields
 */
include_once "field.inc";


class field_multicheck extends field
{

    function open_($val)
    {
        $this->input_txt = $this->testo;
        $this->input_field = "<div style=\"height:auto;overflow:auto;\">";
        foreach ($this->values as $key => $val) {
            $checked = "";
            $get_parameter = "{$this->id}_MCHECK_{$key}";
            if (preg_match("/\\|{$key}\\|/", $this->db_vars[$this->id])) $checked = "checked";
            if ($this->db_vars == NULL && $_GET[$get_parameter]) $checked = "checked";
            $this->input_field .= "
			    <input type=\"checkbox\" $checked name=\"{$this->id}_MCHECK_{$key}\" onchange=\"cf();\" >$val<br/>"; //il CF su onchange ora e' d'ufficio, potrebbe essere condizionato alle effettive condition presenti nella form.
        }

        $this->input_field .= "</div>";
    }

    function close_($val)
    {
        $checkedcheck = "<img src=\"images/checkedcheck.gif\">";
        $this->input_field = "";
        $this->input_txt = $this->testo;
        foreach ($this->values as $key => $val) {
            if (preg_match("/\\|{$key}\\|/", $this->db_vars[$this->id]))
                $this->input_field .= "<table><tr><td>$checkedcheck</td><td> $val</td></table>";
        }
    }

    function insert_stmt()
    {
        $in = $this->session_vars;
        $value = "|";
        foreach ($in as $key => $val) {
            if (preg_match("!^{$this->id}_MCHECK_!", $key)) {
                $valore = str_replace("{$this->id}_MCHECK_", "", $key);
                $value .= $valore . "|";
            }
        }
        $this->field_stmt[0] = $this->attributes['VAR'];
        $this->value_stmt[0] = $value;
    }

    function allinea_db()
    {
        if ($this->attributes['TB'] != 'no') {
            $ret[0] = "{$this->attributes['VAR']} varchar2(4000 char)";
            return $ret;
        } else return;
    }

    function open_save($val)
    {
        $controllo_js = "";
        if ($this->attributes['CONDITION']) {
            $var_cond = $this->attributes['CONDITION'];
            $inputval = $this->db_vars;
            $val_cond = $this->attributes['CONDITION_VALUE'];
            if (preg_match("/,/", $val_cond)) {
                $vals = explode(",", $val_cond);
                $controllo_js .= "
						value=value_of('$var_cond', '0');
						if (";
                foreach ($vals as $key => $value) {

                    $controllo_js .= " value=='$value' ||";
                }
                $controllo_js = rtrim($controllo_js, "||");
                $controllo_js .= ")";
            } else {
                $op = '==';
                if (preg_match("/\!/", $val_cond)) {
                    $val_cond = str_replace("!", "", $val_cond);
                    $op = '!=';
                }
                $controllo_js = " \n
					value=value_of('$var_cond', '0');
					if (value $op '$val_cond')

						";
            }
        }
        $check_ = "{$this->id}_passed=false";
        foreach ($this->values as $key => $val) {
            $check_ .= "
			if (document.forms[0].{$this->id}_MCHECK_{$key}.checked) {$this->id}_passed=true;
			";
        }
        $testo_js = make_js($this->testo);
        $check_ .= $controllo_js . "
			if (!{$this->id}_passed){
				alert('Please make at least one selection in field : $testo_js ({$this->id})');
				document.forms[0].{$this->id}_MCHECK_{$key}.focus();
				return false;
			}
			";
        $this->salva_js = $check_;
    }

    function open_send($val)
    {
        $controllo_js = "";
        if ($this->attributes['CONDITION']) {
            $var_cond = $this->attributes['CONDITION'];
            $inputval = $this->db_vars;
            $val_cond = $this->attributes['CONDITION_VALUE'];
            if (preg_match("/,/", $val_cond)) {
                $vals = explode(",", $val_cond);
                $controllo_js .= "
						value=value_of('$var_cond', '0');
						if (";
                foreach ($vals as $key => $value) {

                    $controllo_js .= " value=='$value' ||";
                }
                $controllo_js = rtrim($controllo_js, "||");
                $controllo_js .= ")";
            } else {
                $op = '==';
                if (preg_match("/\!/", $val_cond)) {
                    $val_cond = str_replace("!", "", $val_cond);
                    $op = '!=';
                }
                $controllo_js = " \n
					value=value_of('$var_cond', '0');
					if (value $op '$val_cond')

						";
            }
        }
        $check_ = "{$this->id}_passed=false";
        foreach ($this->values as $key => $val) {
            $check_ .= "
			if (document.forms[0].{$this->id}_MCHECK_{$key}.checked) {$this->id}_passed=true;
			";
        }
        $testo_js = make_js($this->testo);
        $check_ .= $controllo_js . "
			if (!{$this->id}_passed){
				alert('Please make at least one selection in field : $testo_js ({$this->id})');
				document.forms[0].{$this->id}_MCHECK_{$key}.focus();
				return false;
			}
			";
        $this->invia_js = $check_;
    }

    function open_condition($val)
    {
        //lancio l'esecuzione standard normale
        parent::open_condition($val);
        //Recupero l'operando e le variabili che mi occorrono
        $var_cond=$val;
        //$this->condition_passed=false;
        //$in=$this->session_vars;
        $inputval=$this->db_vars;
        $val_cond=$this->attributes['CONDITION_VALUE'];
        //Gestione elenco
        if (preg_match("/,/", $val_cond)) {
            $vals = explode(",", $val_cond);
            $valcondjs = "";
            foreach ($vals as $key => $value) {
                if ($valcondjs){
                    $valcondjs.= " && ";
                }
                $valcondjs.= "valuemspec!='$value'";
            }
            //Qui inserisco il codice che mi serve per gestire correttamente i field multicheck (tutti i checkbox)
            $this->check_js .= " \n
                //condizione $var_cond==$value MCHECK spec.
                valuemspec=value_of('$var_cond', '0');
                if ($valcondjs)
                {
                ";
            foreach ($this->attributes['VALUE_TXT'] as $idtxt => $valtxt) {
                $this->check_js .= "
                    if (document.forms[0]." . $this->id . "_MCHECK_" . $idtxt . "){
                        document.forms[0]." . $this->id . "_MCHECK_" . $idtxt . ".checked=false;
                    }
                    ";
            }
            $this->check_js.="
                }
                ";
        }else {
            $op = '!=';
            if (preg_match("/\!/", $val_cond)) {
                $val_cond = str_replace("!", "", $val_cond);
                $op = '==';
            }
            //Qui inserisco il codice che mi serve per gestire correttamente i field multicheck (tutti i checkbox)
            $this->check_js .= " \n
					if (value $op '$val_cond')
					{
						";
            foreach ($this->attributes['VALUE_TXT'] as $idtxt => $valtxt) {
                $this->check_js .= "
                        if (document.forms[0]." . $this->id . "_MCHECK_" . $idtxt . "){
                            document.forms[0]." . $this->id . "_MCHECK_" . $idtxt . ".checked=false;
                        }
                        ";
            }
            $this->check_js .= "
					}
						";
        }
        //Fine dei giochi.
    }


}

?>