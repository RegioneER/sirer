<?

include_once "field.inc";

/**
 * Classe per la gestione dei campi di tipo textbox
 *
 * @package Fields
 */
class field_units extends field {
	var $max_js;
	var $min_js;

	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value) {
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

		if (isset ( $this->values ) && is_array ( $this->values ))
			foreach ( $this->values as $key => $val )
				$value = $val;
		if ($inputval [$this->attributes ['VAR']] != '')
			$value = $inputval [$this->attributes ['VAR']];
		if ($in [$this->attributes ['VAR']] != '')
			$value = $in [$this->attributes ['VAR']];

		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
			if ($value == - 9911)
				$value = "NA";
			if ($value == - 9922)
				$value = "NK";
			if ($value == - 9933)
				$value = "ND";
			if ($value == - 9944)
				$value = "NP";
			if ($value == - 9955)
				$value = "TE";
			if ($value == - 9900)
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
		if( $this->attributes['BLOCK_VALUE']=='yes' && $this->db_vars[$this->attributes['VAR']]!="") {
	  		$disabled = "disabled=\"disabled\"";
	  	}
		$action = "";

		if ($this->attributes ['ON_ACTION'] != '' && $this->attributes ['ACTION_TYPE'] != '') {
			$action = $this->attributes ['ACTION_TYPE'] . "=\"" . $this->attributes ['ON_ACTION'] . "\"";
			//         echo "$action<hr>";
		}

		if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes') {
			$html_parser = new HTML_Parser ( );
			$html_parser->setAttribute ( "type", "hidden" );
			$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
			$html_parser->setContent ( $value );
			$html_parser->setType ( "INPUT" );
			$this->input_field = '***' . $html_parser->print_ ();
			//$this->input_field='***<input type="hidden" name="'.$this->attributes['VAR'].'"  value="'.$value.'"/>';
		} else {
			if ($this->attributes ['EMAIL'] != '') {
				$val_email = explode ( "@", $value );
				$this->input_field = "<input type=\"text\" name=\"{$this->attributes['VAR']}_0\" value=\"{$val_email[0]}\">@<input type=\"text\" size='20' name=\"{$this->attributes['VAR']}_1\" value=\"{$val_email[1]}\" onblur=\"document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].{$this->attributes['VAR']}_0.value+'@'+document.forms[0].{$this->attributes['VAR']}_1.value\"><input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
			} else {
				//          echo "$action<hr>";
				if ($this->attributes ['CALL_CF'] != '')
					$cf_call = "cf();";
				if ($this->attributes ['ON_BLUR'] != '') {
					//echo "<hr>{$this->id}<hr>";
					$var = $this->id;
					$vars = explode ( "_PROGR_", $var );
					$js_on_blur = preg_replace ( "/document\.forms\[0\]\.(.*?)\.value/i", "document.forms[0].\\1_PROGR_{$vars[1]}.value", $this->attributes ['ON_BLUR'] );
					//print_r($this->attributes);
					$cf_call .= "{$js_on_blur};";
					//echo "<li>$js_on_blur</li>";
				}

				$value = str_replace ( "\"", "&quot;", $value );
				$html_parser = new HTML_Parser ( );
				$html_parser->setAttribute ( "type", "text" );
				$html_parser->setAttribute ( "maxlength", $this->attributes ['VAR_SIZE'] );
				$html_parser->setAttribute ( "size", $this->attributes ['SIZE'] );
				$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
				$html_parser->setAttribute ( "onblur", $cf_call );
				if($this->attributes['ONCHANGE']!='')$html_parser->setAttribute ( "onchange", $onchange );
				$html_parser->setAttribute ( $disabled, "" );
				$html_parser->setAttribute ( $action, "" );
				$html_parser->setContent ( $value );
				$html_parser->setType ( "INPUT" );
				$this->input_field = $html_parser->print_ () . $this->attributes ['DEF'] . $agg_;
				
				/* Select con le unita' di misura disponibili da DB */
				if($this->attributes['UNITS'] != "" && preg_match("/,/i", $this->attributes['UNITS'])){
					$units = explode(",", $this->attributes['UNITS']);
				
					$select_units = "<select name=\"".$this->attributes['VAR']."_UNIT\">";
					$select_units .= "<option val=\"\"></option>";
					foreach($units as $k_unit => $v_unit){
						
						/* Sostituzione caratteri speciali */
						$v_unit = preg_replace("/u/i", "µ", $v_unit);
						
						/* Selezione unita' di misura in banca dati */
						if($this->db_vars[$this->attributes['VAR']."_UNIT"] == $v_unit){
							$unit_selected = "selected=\"selected\"";
						}else{
							$unit_selected = "";
						}
						
						$select_units .= "<option {$unit_selected} val=\"{$k_unit}\">{$v_unit}</option>";
					}
					$select_units .= "</select>";
					
					$this->input_field .= " ".$select_units;	
				}
				
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

	function open_send($val) {
		global $in;
		
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
		else
		{
			if ($this->attributes['FM_CODE']){
			$fm=$this->attributes['FM_CODE'];
			    if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
        		if (strtoupper($in[$this->attributes['VAR']])=='NK') $in[$this->attributes['VAR']]=-9922;
        		if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
        		if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
        		if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
        		if (strtoupper($in[$this->attributes['VAR']])=='OT') $in[$this->attributes['VAR']]=-9900;
			}

			else
			$fm="00";

			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else if ($this->attributes['VAR_STYPE']=='neg') $controllo="na".$fm;
			else if($this->attributes['VAR_STYPE']=='real') $controllo="xa".$fm;
			else $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
		}
		
		$testo_js=make_js($this->testo);
		if ($testo_js=='') $testo_js=$this->attributes['LABEL_JS'];
		
		/* Andrea 26/01/2010
		 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		 */
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}
		if ($this->attributes ['CONDITION'] != '') {
			$var_cond = $this->attributes ['CONDITION'];
			$val_cond = $this->attributes ['CONDITION_VALUE'];
			
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
					$val_cond = str_replace ( "!", $this->attributes ['CONDITION_VALUE'] );
					$op = "!=";
				} else
					$op = "==";
				$this->invia_js = "
			  	value=value_of('$var_cond', '0');
				if (value $op '$val_cond') c1+='<<si###".$this->attributes['VAR']."###".$testo.">>';\n
			  	";
			}
		}
		else{
			
			/* Gestione controlli al salvataggio */
			if($this->config_service['lang'] == "en"){
				$alert_send_msg_value = "Warning. Incorrect format in the field\\n{$testo_js}:\\ncannot be blank.";
				$alert_send_msg_unit = "Warning. Incorrect format in the field\\n{$testo_js}:\\ncannot be blank.\\nPlease specify also units measurement.";
			}else{
				$alert_send_msg_value = "Warning. Incorrect format in the field\\n{$testo_js}:\\ncannot be blank.";
				$alert_send_msg_unit = "Attenzione. Valore scorretto nel campo\\n{$testo_js}:\\nnon può essere vuoto.\\nSpecificare anche l\\'unità di misura.";
			}
			
			if (($val=='obbligatorio' && $this->attributes['CONDITION']=='')||($this->attributes['VAR_TYPE']!='text' && $val=='facoltativo')){
				$this->invia_js="c1+='<<{$controllo}###".$this->attributes['VAR']."###".$testo_js.">>';";
			}
			
			$this->invia_js.="
			if(document.forms[0].".$this->attributes['VAR'].".value != ''){
				if(!document.forms[0].".$this->attributes['VAR']."_UNIT.selectedIndex){
					alert('".$alert_send_msg_unit."');
					document.forms[0].".$this->attributes['VAR']."_UNIT.focus();
					return false;
				}
			}else{
				if(document.forms[0].".$this->attributes['VAR']."_UNIT.selectedIndex){
					alert('".$alert_send_msg_value."');
					document.forms[0].".$this->attributes['VAR'].".focus();
					return false;
				}
			}
			";
		}
		
		global $in;
		
		if ($in ['invia'] != '' || $in ['INVIOCO'] == '1') {
			if ($this->condition_passed) {
				if ($this->session_vars [$this->attributes ['VAR']] == '' && $val=='obbligatorio') {
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
	 * Costruisce i controlli al salvataggio
	 *
	 * @param String $val
	 */
	function open_save($val){

		$in=$this->session_vars;
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
		else
		{
			if ($this->attributes['FM_CODE']){
			$fm=$this->attributes['FM_CODE'];
			    if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
        		if (strtoupper($in[$this->attributes['VAR']])=='NK') $in[$this->attributes['VAR']]=-9922;
        		if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
        		if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
        		if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
        		if (strtoupper($in[$this->attributes['VAR']])=='OT') $in[$this->attributes['VAR']]=-9900;
			}

			else
			$fm="00";

			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else if ($this->attributes['VAR_STYPE']=='neg') $controllo="na".$fm;
			else if($this->attributes['VAR_STYPE']=='real') $controllo="xa".$fm;
			else $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
		}
		
		$testo_js=make_js($this->testo);
		if ($testo_js=='') $testo_js=$this->attributes['LABEL_JS'];
		
		/* Gestione controlli al salvataggio */
		if($this->config_service['lang'] == "en"){
			$alert_save_msg_value = "Warning. Incorrect format in the field\\n{$testo_js}:\\ncannot be blank.";
			$alert_save_msg_unit = "Warning. Incorrect format in the field\\n{$testo_js}:\\ncannot be blank.\\nPlease specify also units measurement.";
		}else{
			$alert_save_msg_value = "Warning. Incorrect format in the field\\n{$testo_js}:\\ncannot be blank.";
			$alert_save_msg_unit = "Attenzione. Valore scorretto nel campo\\n{$testo_js}:\\nnon può essere vuoto.\\nSpecificare anche l\\'unità di misura.";
		}
		$this->salva_js.="
		if(document.forms[0].".$this->attributes['VAR'].".value != ''){
			if(!document.forms[0].".$this->attributes['VAR']."_UNIT.selectedIndex){
				alert('".$alert_save_msg_unit."');
				document.forms[0].".$this->attributes['VAR']."_UNIT.focus();
				return false;
			}
		}else{
			if(document.forms[0].".$this->attributes['VAR']."_UNIT.selectedIndex){
				alert('".$alert_save_msg_value."');
				document.forms[0].".$this->attributes['VAR'].".focus();
				return false;
			}
		}
		";
		
		if (($val=='obbligatorio' && $this->attributes['CONDITION']=='')||($this->attributes['VAR_TYPE']!='text' && $val=='facoltativo')){

			$this->salva_js.="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";

			$this->inrevisione_js.="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
		/*aggiorno con la possibilità di utilizzare più valori divisi da virgola in condition_value da testare approfonditamente (Giorgio Delsignore 14/06/2010)
		if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js.="
			var value_{$this->attributes['CONDITION']}=value_of('{$this->attributes['CONDITION']}','0');
			if(value_{$this->attributes['CONDITION']}=='{$this->attributes['CONDITION_VALUE']}')c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
			";

		}*/
		if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js.="
				".$this->attributes['CONDITION']."_setted=false;
				";
			$this->inrevisione_js.="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
				$this->inrevisione_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
								}
						";
			}
			else
			{
				$oper="==";
				if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
				$this->salva_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
				$this->inrevisione_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->salva_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
			$this->inrevisione_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
		}
		$this->session_vars=$in;
	}
	
	/**
	 * Controlli sul campo di tipo codice fiscale
	 *
	 * @param String $value
	 */
	function open_codfisc($value) {

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
	function close_($value) {
		//		global $in;
		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE']) {
			if ($value == - 9911)
				$value = "NA";
			if ($value == - 9922)
				$value = "NK";
			if ($value == - 9933)
				$value = "ND";
			if ($value == - 9944)
				$value = "NP";
			if ($value == - 9955)
				$value = "TE";
			if ($value == - 9900)
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

		$this->input_field = '<b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b> '.$this->db_vars[$this->attributes ['VAR']."_UNIT"].' '.$this->attributes ['DEF'];
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1)
			$ret .= '<td  class="input_txt" colspan="' . $this->cols_form . '">' . $txt . $input_html . '';
		else
			$ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b> '.$this->db_vars[$this->attributes ['VAR']."_UNIT"];

	#return $ret;
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
	function open_max($value) {
		if (preg_match ( "/\[/", $value )) {
			//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $value );
			$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $value );
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
		if ($this->attributes['SEND']=='obbligatorio') {
			//E.Gargano 15/05/09
			//controllo se la condizione si è verificata in js
			$cond=$this->attributes['CONDITION'];
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if($this->attributes['CONDITION']!='') {
				$this->controlli.="
				if (document.forms[0].".$cond.".value==$val_cond)";
			}
			//E.Gargano 15/05/09 fine
			$this->controlli.="
				if (document.forms[0].".$this->id.".value>value) {";

		} else { $this->controlli.="
				if (document.forms[0].".$this->id.".value!='' && document.forms[0].".$this->id.".value>value) {";
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
	function open_min($value) {
		if (preg_match ( "/\[/", $value )) {
			//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $value );
			$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $value );
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

		$testo=make_js($this->testo);

		/* Nicola 20/01/2010
		 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		 */
			if($this->attributes['LABEL_JS'] != ""){
				$testo=$this->attributes['LABEL_JS'];
			}

		//traduzione del messaggio di alert in inglese
		if ($this->config_service ['lang'] == "en")
			$alert_msg = "Warning the value {$testo} must be greater than ";
		else
			$alert_msg = "Attenzione il valore di {$testo} deve essere maggiore di ";
		if ($this->attributes['SEND']=='obbligatorio') {
			//E.Gargano 15/05/09
			//controllo se la condizione si è verificata in js
			$cond=$this->attributes['CONDITION'];
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if($this->attributes['CONDITION']!='') {
				$this->controlli.="
				if (document.forms[0].".$cond.".value==$val_cond)";
			}
			//E.Gargano 15/05/09 fine
			$this->controlli.="
				if (document.forms[0].".$this->id.".value<=value) {";

		} else { $this->controlli.="
				if (document.forms[0].".$this->id.".value!='' && document.forms[0].".$this->id.".value<=value) {";
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
	function open_min_eq($value) {
		if (preg_match ( "/\[/", $value )) {
			//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $value );
			$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $value );
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
			$alert_msg = "Attenzione il valore di \"" . make_js ( $this->testo ) . "\" deve essere maggiore o uguale a ";

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
	function open_dividendo($val) {
		global $in;
		$dividendo = $this->attributes ['DIVIDENDO'];
		if (preg_match ( "/\[/", $dividendo )) {
			//$dividendo = preg_replace ( "/\[(.*?)\]/e", "$1", $dividendo );
			$dividendo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $dividendo );
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
		if (preg_match ( "/\[/", $divisore )) {
			$divisore = preg_replace ( "/\[(.*?)\]/e", "$1", $divisore );
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
	function open_equals($val) {
		$t = str_replace ( "*", "", $this->testo );
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
	function open_execute($value) {
		$this->check_js .= "
      $value" . ";";
	}

	/**
	 * Esegue del codice js all'onchange
	 *
	 * @param String $value
	 */
	function open_on_change($value) {
		$this->check_js .= "$value
		";
	}

	/**
	 * Gestione dello sfoglia su dizionari
	 *
	 * @param String $value
	 */
	function open_sfoglia($value) {
		$tip_sfo = explode ( ";", $value );
		for($f = 0; $f < count ( $tip_sfo ); $f ++) {
			//         echo "$f--$tip_sfo[$f]<hr>";
			$but = explode ( ",", $tip_sfo [$f] );
			$but_text = $but [0];
			$but_file = $but [1];
			$but_file = preg_replace ( "!\[(.*?)\]!i", '$1', $but_file );
			$but_file = str_replace ( "|and|", '&', $but_file );

			if ($this->attributes ['SFOGLIA_ADD_PARAM'] != '') {
				$params = explode ( ",", $this->attributes ['SFOGLIA_ADD_PARAM'] );
				foreach ( $params as $key => $val ) {
					$but_file .= "&{$val}={$_GET[$val]}";
				}
			}
			if(preg_match('/^js:/',$but_text)){
				$but_text=str_replace("js:","",$but_text);
				$agg = "&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
			}
			else{
				if (strtolower($but_text) == 'reset' || strtolower($but_text) == 'cancella' || $this->attributes['SFOGLIA_CLEAR_LABEL']==$but_text)
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
	function open_sum($val) {
		global $in;
		$campi = explode ( ",", $val );
		$minval = $this->attributes ['SUM_MAGGIORE'] + 0;
		$maxval = $this->attributes ['SUM_MINORE'] + 0;
		$check = "if (value >= $minval)";
		if ($maxval > 0)
			$check = "if (value >= $minval && value <= $maxvalue)";
		$somma = 0;
		for($i = 0; $i < count ( $campi ); $i ++) {
			if ($i == 0)
				$this->check_js .= " \n
					document.forms[0]." . $this->attributes ['VAR'] . ".value='';
				";
			if (preg_match ( "/\[/", $campi [$i] )) {
				//$campo = preg_replace ( "/\[(.*?)\]/e", "$1", $campi [$i] );
				$campo = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return $matches[1];}, $value );
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
	function open_upper($value) {
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
	function all_in($var, $i, $row, $this_closed) {
		$val=$this->attributes;
		$row[$val['VAR']]=str_replace("\"", "'", $row[$var]);
		if ($this_closed){
			$body="
			<td class=sc4bis>
				<b>{$row[$var]}</b>
				</td>
				";
				$ret['body']=$body;
				return $ret;
		}
		if (isset ( $val ['SFOGLIA'] )
		//&& $this->xml_form->session_vars ['USER_TIP'] == 'DE'
		&& ! $this_closed) {
			$value = $val ['SFOGLIA'];
			$tip_sfo = explode ( ";", $value );
			$but = explode ( ",", $tip_sfo [0] );
			$but_text = $but [0];
			$but_file = $but [1];
			$but_file = preg_replace ( "!\[(.*?)\]!i", '$1' . "_PROGR_{$i}", $but_file );
			$but_file = str_replace ( "|and|", '&', $but_file );

			if ($val ['SFOGLIA_ADD_PARAM'] != '') {
				$params = explode ( ",", $val ['SFOGLIA_ADD_PARAM'] );
				foreach ( $params as $kp => $vp ) {
					$but_file .= "&{$vp}={$_GET[$vp]}";
				}
			}
			if ($row [$val ['VAR']] == '')
				$last_call_sfoglia = $but_file;
			else
				$last_call_sfoglia = '';

			if ($but_text == 'cancella')
				$agg = "<br/>&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"$but_file;return false;\">";
			else if($val ['SFOGLIA_SINGOLO']!='no'){
				if ($row [$val ['VAR']] == '')	$agg = "<br/>&nbsp;<input type=\"button\" value=\"$but_text\" name=\"$but_text\" onClick=\"apri_window('/$but_file');return false;\">";
			}
		} else
			$agg = '';
			
		$align="";
		if($this->attributes['ALIGN']!="")
		$align=" align=\"{$this->attributes['ALIGN']}\"";
		
		if (isset ( $val ['DISABLED_ALWAYS'] )) {
			$body .= "
				<td class=sc4bis $align>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
		} else {
			if (isset ( $val ['DISABLED'] ) && $row[$val['VAR']]!='') {
				$body .= "
				<td class=sc4bis $align>
				<input type='hidden' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\">
				<span id='SPAN_{$var}_PROGR_{$i}'>{$row[$val['VAR']]}</span>
				$agg
				</td>
				";
			} else {
				$maxlength="";

				if(isset($val['VAR_SIZE'])) $maxlength="MAXLENGTH=\"{$val['VAR_SIZE']}\"";
				$size="";
				if(isset($val['SIZE'])) $maxlength.=" SIZE=\"{$val['SIZE']}\"";
				$body .= "
				<td class=sc4bis $align >
				<input type='textbox' name='{$var}_PROGR_{$i}' value=\"{$row[$val['VAR']]}\" $maxlength>$agg
				</td>
				";
			}
		}
		$ret['last_call_sfoglia']=$last_call_sfoglia;
		$ret['body']=$body;
		return $ret;
	}

	/**
	 * Visualizzazione nella modalità  progressiva (header)
	 *
	 * @param field_units $field
	 * @param number $m_p
	 * @param form $xml_form
	 * @return String
	 */
	static function S_all_in($field, $m_p, $xml_form){
		$select_field .= $field . ",";
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
			$onclick_action = "";
		for($i = 1; $i <= $m_p; $i ++) {
			$onclick_action .= "document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}.value=document.forms['ALL_IN_FORMS'].{$field}_TOT.value;
			";
		}
		$field_tot .= "
			<input type='textbox' name='{$field}_TOT'><br>
			<!--input type='button' value='applica a tutti' onclick=\"
			$onclick_action
			\"-->
			<button class=\"btn btn-xs btn-warning\" type=\"button\" onclick=\"$onclick_action\">
				<i class=\"fa fa-floppy-o bigger-110\"></i>
				applica a tutti
			</button>
		";
		$tr_agg .= "<td class=int>$field_tot &nbsp;</td>";
		}
		return $tr_agg;
	}
	
/**
	 * Costruisce un array con i valori da inserire in DB
	 *
	 */
	function insert_stmt(){
		$in=$this->session_vars;
	if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
	else
		{
			if ($this->attributes['FM_CODE']){
			$fm=$this->attributes['FM_CODE'];
			    if (strtoupper($in[$this->attributes['VAR']])=='NA') $in[$this->attributes['VAR']]=-9911;
        		if (strtoupper($in[$this->attributes['VAR']])=='NK') $in[$this->attributes['VAR']]=-9922;
        		if (strtoupper($in[$this->attributes['VAR']])=='ND') $in[$this->attributes['VAR']]=-9933;
        		if (strtoupper($in[$this->attributes['VAR']])=='NP') $in[$this->attributes['VAR']]=-9944;
        		if (strtoupper($in[$this->attributes['VAR']])=='TE') $in[$this->attributes['VAR']]=-9955;
        		if (strtoupper($in[$this->attributes['VAR']])=='OT') $in[$this->attributes['VAR']]=-9900;
			}

			else
			$fm="00";

			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else if ($this->attributes['VAR_STYPE']=='neg') $controllo="na".$fm;
			else if($this->attributes['VAR_STYPE']=='real') $controllo="xa".$fm;
			else $controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
		}
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]=$this->attributes['VAR'];
			
			$this->field_stmt[1]=$this->attributes['VAR']."_UNIT";
			
			$value=$in[$this->attributes['VAR']];
			$value_unit=$in[$this->attributes['VAR']."_UNIT"];
			
			$value=str_replace("\\\"", "\"", $value);
			$value=str_replace("&quot;", "\"", $value);
			//$value=$in[$this->attributes['VAR']];
			//$value=str_replace("\\\"", "\"", $value);
			$this->value_stmt[0]=$value;
			$this->value_stmt[1]=$value_unit;
		}
		return;
	}
	
	/**
	 * Controlla se il campo in tb Ã¨ allineanto con quello definito nell'XML
	 *
	 * @return array
	 */
	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			if ($this->attributes['VAR_TYPE']=='number') $type_field='NUMBER';
			else $type_field="VARCHAR2({$this->attributes['VAR_SIZE']})";
			$ret[0]="{$this->attributes['VAR']} {$type_field}";
			$ret[1]="{$this->attributes['VAR']}_UNIT VARCHAR2(100)";
			return $ret;
		}
		else return ;
	}
}

?>
