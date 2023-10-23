<?

include_once ("field.inc"); 

/**
 * Classe per la gestione dei campi di tipo password
 *
 * @package Hyper
 */
class field_password extends field{
	function __construct($conn=null, $xml_form=null,$i=null,$session_vars=null, $db_vars=null, $service=null, $errors=null){
		parent::field($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors);
		if($this->attributes['SHOW_CRF']=='yes' && isset($_GET['CRF_BLANK'])){
			unset($this->attributes['HIDE']);
		}
		$this->testo=str_replace("*","",$this->testo);
	}
	var $max_js;
	var $min_js;
	
	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 */
	function close_($value) {
		//		global $in;
		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE'])
		{
				if ($value  == -9911) $value = "NA";
				if ($value  == -9922) $value = "NK";
				if ($value  == -9933) $value = "ND";
				if ($value  == -9944) $value = "NP";
				if ($value  == -9955) $value = "TE";
				if ($value  == -9900) $value = "OT";
				
		} 
		$in = $this->session_vars;
		$ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
		$txt = $this->testo;
        $input_html = "";
		if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes')
			$input_html .= '***';
		else
			$input_html .= $value;
		if ($input_html == '')
			$input_html .= '&nbsp;';
			
		if (isset($in['AUDIT_TRAIL']) && $in['AUDIT_TRAIL']!='') {
			$audit_trail =  new audit_trail($this->service,$this->conn,$this->config_service,$this->attributes,$this->xml_form);
			$input_html.= $audit_trail->audit_trail_popup($in);
	
		}
			
		$db=$this->attributes['VAR'];
		if(isset ( $_GET ['CRF_ANNOTE'] )){
			$input_html .= $this->xml_form->form['TABLE'].'.'.$db;
		}
		$this->input_txt = $txt;
		$this->input_field = '<span class="textfield"><b><i><font color="#333300"><u>' . $input_html . '</u></font></i></b></span>' . $this->attributes ['DEF'];
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1){
			$ret .= '<td  class="input_txt" colspan="' . $this->cols_form . '">' . $txt . $input_html . '';
			}
		else{
			$ret .= '<td class="destra">' . $txt . '</td><td class="input"><b><i><font color="#333300"><span class="textfield">' . $input_html . '</span></font></i></b>';
		}
		#return $ret;
		$input_html='********';
		
	}
	
	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value){
		global $in;
		$in = $this->session_vars;
		//		echo $in['USER_TIP'];
//		global $inputval;
		$inputval=$this->db_vars;
		$txt = $this->testo;
		if ($this->attributes ['CHECK'] == '')
			$this->attributes ['CHECK'] = "text";
		
		if ($this->attributes ['SIZE'] == '')
			$this->attributes ['SIZE'] = '20';
		if (isset ( $this->values ) && is_array ( $this->values ))
			foreach ( $this->values as $key => $val )
				$value = $val;
		if ($inputval [$this->attributes ['VAR']] != '')
			$value = $inputval [$this->attributes ['VAR']];
		if ($in [$this->attributes ['VAR']] != '')
			$value = $in [$this->attributes ['VAR']];
		
		if ($this->attributes ['VAR_TYPE'] != 'text' && $this->attributes ['FM_CODE'])
		{
				if ($value  == -9911) $value = "NA";
				if ($value  == -9922) $value = "NK";
				if ($value  == -9933) $value = "ND";
				if ($value  == -9944) $value = "NP";
				if ($value  == -9955) $value = "TE";
				if ($value  == -9900) $value = "OT";
				
		} 
		$disabled = "";
		if ($this->attributes ['DISABLED'] != '') {
			if ($value != '')
				$disabled = "disabled";
			$this->check_js .= "
				if (document.forms[0].{$this->id}.value!='') document.forms[0].{$this->id}.disabled=true;
			";
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
			$this->input_field = '********' . $html_parser->print_ ();
			//$this->input_field='***<input type="hidden" name="'.$this->attributes['VAR'].'"  value="'.$value.'"/>';
		} else {
			if ($this->attributes ['EMAIL'] != '') {
				$val_email = explode ( "@", $value );
				$this->input_field = "<input type=\"password\" name=\"{$this->attributes['VAR']}_0\" value=\"{$val_email[0]}\">@<input type=\"password\" size='20' name=\"{$this->attributes['VAR']}_1\" value=\"{$val_email[1]}\" onblur=\"document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].{$this->attributes['VAR']}_0.value+'@'+document.forms[0].{$this->attributes['VAR']}_1.value\"><input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
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
				$html_parser->setAttribute ( "type", "password" );
				$html_parser->setAttribute ( "maxlength", $this->attributes ['VAR_SIZE'] );
				$html_parser->setAttribute ( "size", $this->attributes ['SIZE'] );
				$html_parser->setAttribute ( "name", $this->attributes ['VAR'] );
				$html_parser->setAttribute ( "onblur", $cf_call );
				$html_parser->setAttribute ( $disabled, "" );
				$html_parser->setAttribute ( $action, "" );
				$html_parser->setContent ( $value );
				$html_parser->setType ( "INPUT" );
				$this->input_field = $html_parser->print_ () . $this->attributes ['DEF'] . $agg_;
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
		
		if(isset ( $in['FIELD'] ) and $in['FIELD']==$this->attributes['DESCRIPTION']){
				$this->input_field = '
		      <table class="eqfield"><tr ><td >'.$html_parser->print_ ().'</td></tr></table>
		      ';
		}
		
		//if ($this->attributes['DISABLED']!='') $this->input_field='<input type=\'hidden\' name="'.$this->attributes['VAR'].'" value="'.$value.'"><b>'.$value.'</b>';
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
		$testo_js=make_js($this->testo);
		if ($testo_js=='' || $this->attributes['LABEL_JS']!='') $testo_js=$this->attributes['LABEL_JS'];
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
	
	
	
}

?>