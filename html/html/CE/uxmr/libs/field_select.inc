<?

include_once "field_code_decode.inc";

/**
 * Classe per la gestione del campo tipo di select
 *
 * @package Fields
 */
class field_select extends field_code_decode {
	
	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value) {
		global $in;
		//		global $inputval;
		//print_r($this->xml_form->form);
		$inputval = $this->db_vars;
		//		if($this->id=='HOSPITALS')print_r($inputval);
		$optgroup = false;
		$txt = $this->testo;
		$submit = "";
		if ($this->attributes ['SUBMIT'] != '')
			$submit = "submit();";
		$onchange = "";
		if ($this->attributes ['ONCHANGE'] != '')
			$onchange = "{$this->attributes['ONCHANGE']};";
		$action = "";
		if ($this->attributes ['ON_ACTION'] != '' && $this->attributes ['ACTION_TYPE'] != '') {
			$action = $this->attributes ['ACTION_TYPE'] . "=\"" . $this->attributes ['ON_ACTION'] . "\"";
		}
		if (isset ( $in [$this->attributes ['VAR']] ))
			unset ( $inputval [$this->attributes ['VAR']] );
		$disabled = "";
		if ($this->attributes ['ALWAYS_DISABLED'] != '' || ($this->attributes ['DISABLED'] != '' && $value != ''))
			$disabled = "disabled";
		$action = "";
		if ($this->attributes ['CALL_CF'] != '')
			$cf_call = "cf();";
		$this_progr = "";
		
		if (isset ( $in ['TB_COLL'] ) && $in ['TB_COLL'] != '')
			$input_html = '<select ' . $disabled . ' name="TB_COLL_' . $in ['ID_REF'] . '_' . $this->attributes ['VAR'] . '" onchange="' . $cf_call . '' . $submit . $onchange . '"' . $action . '><option value="">&nbsp;</option>';
		else
			$input_html = '<select  ' . $disabled . ' name="' . $this->attributes ['VAR'] . '" onchange="' . $onchange . $cf_call . '' . $submit . '" ' . $action . '><option value="">&nbsp;</option>';
		foreach ( $this->values as $val => $decode ) {
			$selected = "";
			
			#echo "<hr>".$this->attributes['VAR']." - ".$in[$this->attributes['VAR']]." - ".$inputval[$this->attributes['VAR']]." - ".$val;
			//        		echo $txt.' -- '.$val.' - '.$this->attributes['VAR'].' - '.$in[$this->attributes['VAR']]."<hr>";
			if ($inputval [$this->attributes ['VAR']] == $val)
				$selected = "selected";
			if ($in [$this->attributes ['VAR']] == $val)
				$selected = "selected";
				//echo "<li>{$inputval[$this->attributes['VAR']]}==$val - $selected</li>";
			if (preg_match ( "/optgroup/", $val )) {
				$optgroup = true;
				if ($options != '')
					$options .= "
	        				</optgroup>";
				$options .= '
	        				<optgroup label="' . $decode . '">';
			} else{
				$options .= '
	        				<option value="' . $val . '" ' . $selected . '>' . $decode . '</option>';
			}
		}
		if ($optgroup)
			$options .= "</optgroup>";
		
		$input_html .= $options . '</select><input type="hidden" name="D_' . $this->attributes ['VAR'] . '"/> ' . $agg_;
		$this->input_field = $input_html . "&nbsp;" . $this->attributes ['DEF'];
		//echo $this->input_field."<hr>";
		$this->input_txt = $txt;
		//print_r($inputval);
		/*
		if ($this->xml_form->form['CONT_FORM']!='') {
			$vars=explode("_PROGR_", $this->id);
			$progr=$vars[1];
			$READ_ONLY_VAR="READ_ONLY_PROGR_".$progr;
			}
			else $READ_ONLY_VAR="READ_ONLY";
		//echo "<hr>{$this->id} - {$this->xml_form->form['READONLY']} - {$inputval['READ_ONLY']}<hr>";
			if ($this->xml_form->form['READONLY']!='') {
			if ($inputval[$READ_ONLY_VAR]=='1' && $inputval[$this->id]=='') $this->input_field.="<br><font color=red>Il campo non � presente in BDF</font>";
		}
		*/
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1)
			$ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . $input_html . '</td>';
		else
			$ret .= '<td class="destra">' . $txt . '</td><td class="input">' . $input_html . '</td>';
		#return $ret;
	}
	
	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 * @return String
	 */
	function close_($value) {
		//modifica chiara del 06/08/2009 - i global non funzionano su venice
		//global $in;
		//global $inputval;
		$in = $this->session_vars;
		$inputval = $this->db_vars;
		
		$ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
		$txt = $this->testo;
		if ($in ['salva'] != '' && $this->attributes ['SAVE'] == 'obbligatorio' && $in [$this->attributes ['VAR']] == '') {
			$this->validata = false;
			$txt .= "<br/><font size='-1' color='red'>Error!!!Make a selection</font>";
		}
		foreach ( $this->values as $val => $decode ) {
			$selected = "";
			//echo "<hr>".$this->attributes['VAR']." - in ".$in[$this->attributes['VAR']]." - inputval ".$inputval[$this->attributes['VAR']]." - ".$val;
			if ($inputval [$this->attributes ['VAR']] == $val)
				$selected = "selected";
			if ($in [$this->attributes ['VAR']] != '' && $in [$this->attributes ['VAR']] == $val)
				$selected = "selected";
			if ($selected == 'selected')
				$input_html .= '<b><i><u><font color="#333300" size="2"><span class="selectedOption">' . $decode . '</span></font></u></i></b><br>';
			else if ($this->attributes ['SHOW_SELECTED'] == '')
				$input_html .= '<font color="#005dce" size="1"><span class="unselectedOption">' . $decode . '</span></font><br>';
		
		}
		$this->input_txt = $txt;
		$this->input_field = $input_html;
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1)
			$ret .= '<td  class="input_txt" colspan="' . $this->cols_form . '"><table border=0 cellpadding=0 cellspacing=0><tr><td>' . $txt . "</td><td>" . $input_html . '</td></tr></table></td>';
		else
			$ret .= '<td class="destra">' . $txt . '</td><td class="input">' . $input_html . '</td></tr>';
		return $ret;
	}
	
	/**
	 * Gestisce la compilazione automatica del campo
	 *
	 * @param String $value
	 */
	function open_compila($value) {
		#echo "<hr>$value";
		$this->check_js .= "
					if (document.forms[0]." . $this->attributes ['COMPILA_CONDITION_VAR'] . ".value==" . $this->attributes ['COMPILA_CONDITION_VALUE'] . "){
						compila_value=document.forms[0]." . $this->attributes ['COMPILA'] . ".value;
						if (compila_value>0){
							document.forms[0]." . $this->attributes ['VAR'] . ".value=compila_value;
							document.forms[0]." . $this->attributes ['VAR'] . ".disabled=true;
						}
					}
			";
	}

	/**
	 * Controlli al salvataggio
	 *
	 * @param String $val
	 */
	function open_save($val){
		$testo=$this->testo;
		$testo=make_js($testo);
	
		/* Andrea 26/01/2010
		 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		 */
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}
		$condition_value=$this->attributes['CONDITION_VALUE'];
		$oper="==";
		if (preg_match("/!/",$condition_value)) {
			$oper="!=";
			$condition_value=substr($condition_value, 1);
		}
		
		if ($this->attributes ['CONDITION'] != '') {
			$var_cond = $this->attributes ['CONDITION'];
			$val_cond = $condition_value;
				   $this->salva_js = "
			  	value=value_of('$var_cond', '0');
					if (value{$oper}'$val_cond')
			  	c1+='<<si###".$this->attributes['VAR']."###".$testo.">>';\n
			  	";
		} 
		else
			$this->salva_js = "c1+='<<si###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n";
		if ($in ['salva'] != '' || $in ['INVIOCO'] == '0') {
			if ($in [$this->attributes ['VAR']] == '') {
				global $insert_errors;
				$this->validata = false;
				$insert_errors [$this->attributes ['VAR']] = 'Selezione obbligatoria';
			}
		}
	}
	
	/**
	 * Controlli all'invio
	 * 
	 *
	 * @param String $val
	 */
	function open_send($val) {
		global $in;
		$testo=$this->testo;
		$testo=make_js($testo);
		/* Andrea 26/01/2010
		 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		 */
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}
		$oper="==";
		$condition_value=$this->attributes['CONDITION_VALUE'];
		if (preg_match("/!/",$condition_value)) {
			$oper="!=";
			$condition_value=substr($condition_value, 1);
		}

		if ($this->attributes ['CONDITION'] != '') {
			$var_cond = $this->attributes ['CONDITION'];
			$val_cond = $condition_value;
			
			if (preg_match ( "/,/", $val_cond )) {
				$vals = explode ( ",", $val_cond );
				foreach ( $vals as $key => $value ) {
					//if ($in[$var_cond]==$value) $this->condition_passed=true;
					$this->invia_js .= " \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			c1+='<<si###".$this->attributes['VAR']."###".$testo.">>';\n
						}
							";
				}
			} else {
				//echo "<li>{$this->attributes['CONDITION_VALUE']} - {$this->attributes['CONDITION']} - {$this->id}</li>";
				if (preg_match ( "/!/", $this->attributes ['CONDITION_VALUE'] )) {
					$val_cond = str_replace ( "!",'', $this->attributes ['CONDITION_VALUE'] );
					$op = "!=";
				} else
					$op = "==";
				$this->invia_js = "
			  	value=value_of('$var_cond', '0');
				if (value $op '$val_cond') c1+='<<si###".$this->attributes['VAR']."###".$testo.">>';\n
			  	";
			}
		}
		else $this->invia_js="c1+='<<si###".$this->attributes['VAR']."###".$testo.">>';\n";
		global $in;
		
		if ($in ['invia'] != '' || $in ['INVIOCO'] == '1') {
			if ($this->condition_passed) {
				if ($this->session_vars [$this->attributes ['VAR']] == '') {
					global $insert_errors;
					$this->validata = false;
					$insert_errors [$this->attributes ['VAR']] = 'Selezione obbligatoria';
				}
			} else {
				if ($this->session_vars [$this->attributes ['VAR']] != '') {
					global $insert_errors;
					$this->validata = false;
					$insert_errors [$this->attributes ['VAR']] = 'Deselezionare il seguente campo';
				}
			}
		}
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
	function all_in($var, $i, $row, $this_closed) {
		
		$options = "";
		$js_script = "";
		foreach ( $this->values as $kf => $vf ) {
			if ($row [$var] == $kf) {
				$selected = "selected";
				$hidden_value = $vf;
			} else
				$selected = "";
			$js_script .= "
													if (this.value==$kf) document.forms['ALL_IN_FORMS'].D_{$var}_PROGR_{$i}.value='$vf';
												";
			$options .= "<option value='$kf' $selected>$vf</option>";
		}
		if ($this_closed)
			$content = "<b>$hidden_value</b>";
		else {
			$content = "<input type='hidden' name='D_{$var}_PROGR_{$i}' value=\"$hidden_value\">
												<select onchange=\"
												if (this.value=='') document.forms['ALL_IN_FORMS'].D_{$var}_PROGR_{$i}.value='';
												$js_script
												\" name=\"{$var}_PROGR_{$i}\"><option></option>$options</select>
												 ";
		}
		$ret['body'] = "
												<td class=sc4bis>
												$content
												</td>";
		return $ret;
	}
	
	/**
	 * Visualizzazione nella modalitÃ  progressiva (header)
	 *
	 * @param field_select $field
	 * @param number $m_p
	 * @param form $xml_form
	 * @return String
	 */
	static function S_all_in($field, $m_p, $xml_form){
		$select_field .= "$field,";
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
			$tr_agg .= "<td class=int>&nbsp;</td>";
		}
		return $tr_agg;
	}

}

?>