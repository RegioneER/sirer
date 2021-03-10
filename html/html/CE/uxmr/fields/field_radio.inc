<?


include_once "libs/field_code_decode.inc";
/**
 * Gestione del campo tipo radio
 *
 * @package Fields
 */
class field_radio extends field_code_decode {

	/**
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param String $value
	 */
	function open_($value) {
		if($this->config_service['lang']=='en')$deseleziona_txt="deselect";
		else $deseleziona_txt="deseleziona";
		$inputval = $this->db_vars;
		$in = $this->session_vars;
		$cols = $this->attributes ['SUBTBCOL'];
		$cols -= 0;
		if ($cols == 0)
			$cols = 1;
		$txt = $this->testo;
		$input_html = '
      <table border=0 cellpadding=0 cellspacing=0><tr style="display:none"><td colspan="' . $cols . '">&nbsp;</td>
      ';
		$col = 0;
		foreach ( $this->values as $val => $decode ) {
			#echo "$val - $decode";
			if ($col == $cols)
				$col = 0;
			if ($col == 0)
				$input_html .= "
      		</tr>
      		<tr>
      		";
			$col ++;
			$checked = "";
			
			/* Nicola 02/02/2011
			 * gestione evento onchange e onclick
			 */
			if($this->attributes ['ONCHANGE'] != ""){
				$onchange_radio = "onchange=\"".$this->attributes ['ONCHANGE']."\"";
			}else{
				$onchange_radio = "";
			}
			
			if($this->attributes ['ONCLICK'] != ""){
				$onclick_radio = $this->attributes ['ONCLICK'];
			}else{
				$onclick_radio = "";
			}
			
			if ($inputval [$this->attributes ['VAR']] == $val || $this->attributes ['CHECKED'] == $val)
				$checked = "checked";
			if ($in [$this->attributes ['VAR']] == $val)
				$checked = "checked";
			$input_html .= '
      		<div class="radio"><label>
      		<input class="ace" type="radio" value="' . $val . '" name="' . $this->attributes ['VAR'] . '" ' . $checked . ' '.$onchange_radio.' onclick="'.$onclick_radio.'cf();"/><span class="lbl">&nbsp;' . $decode . '&nbsp;</span>
      		</label></div>';
		}
		$input_html .= '</tr></table><div class="radio"><a href="#" onclick="radioclear(\'' . $this->attributes ['VAR'] . '\'); cf(); return false"><i class="fa fa-eraser"></i>'.$deseleziona_txt.'</a></div>';
		$this->input_field = $input_html;
		$this->input_txt = $txt;
	}
	
	function open_tablista_sql($value){
		//$value=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $value);
		$value=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $value );
		$sql=new query($this->conn);
		$tbHeaders=explode("|", $this->attributes['TABLISTA_HEADERS']);
		$sql->exec($value);//complessa Carlo var_glob
		$tb.="<br/><table border=0 cellpadding=0 cellspacing=2 align=left><tr>";
		foreach ($tbHeaders as $key=>$val){
			$tb.="<td class=int>$val</td>";
		}
		$tb.="</tr>";
		while ($sql->get_row()){
			$tb.="<tr>";
			foreach ($sql->row as $key=>$val){
				$tb.="<td class=sc4bis>$val</td>";
			}
			$tb.="</tr>";
		}
		$tb.="</table>";
		$this->input_txt.=$tb;
	}

	/**
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param String $value
	 */
	function close_($value) {
		$inputval = $this->db_vars;
		$in = $this->session_vars;
		$ret = '<tr id="' . $this->attributes ['VAR'] . '" style="display:">';
		$cols = $this->attributes ['SUBTBCOL'];
		$txt = $this->testo;
		$input_html = '
      <table border=0 cellpadding=0 cellspacing=0><tr style="display:none"><td colspan="' . $cols . '">&nbsp;</td>
      ';
		$col = 0;
		$input_html = '
      <table border=0 cellpadding=3 cellspacing=0><tr style="display:none"><td colspan="' . $cols . '">&nbsp;</td>
      ';
		foreach ( $this->values as $val => $decode ) {
			if ($col == $cols)
				$col = 0;
			if ($col == 0)
				$input_html .= "
      		</tr>
      		<tr>
      		";
			$col ++;
			$checked = "";
			if ($inputval [$this->attributes ['VAR']] == "$val") {
				$checked = "checked";
			}
			if ($in [$this->attributes ['VAR']] == "$val") {
				$checked = "checked"; #echo "<hr>".$inputval[$this->attributes['VAR']]." - ".$in[$this->attributes['VAR']]." - $val";
			}
			if ($checked == 'checked') {
				$input_html .= "<td style=\"border: 0px solid #ddd;\"><i class=\"fa fa-dot-circle-o\"></i>";
			} else
				$input_html .= "<td style=\"border: 0px solid #ddd;\"><i class=\"fa fa-circle-o\"></i>";
			$input_html .= $decode . "</td>";
		}
		$input_html .= "</table>";
		$this->input_txt = $txt;
		$this->input_field = $input_html;
		if (isset ( $this->attributes ['COLSPAN'] ) and $this->cols_form > 1)
			$ret .= '<td  class="input" colspan="' . $this->cols_form . '">' . $txt . ':' . $input_html . '</td>';
		else
			$ret .= '<td class="destra">' . $txt . ':</td><td class="input">' . $input_html . '</td></tr>';
		#return $ret;
	}
	
/*	function open_condition($val){
		if($this->config_service['jquery'] && method_exists($this,"open_jcondition")) return $this->open_jcondition($val);
		$var_cond=$val;
		$this->condition_passed=false;
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		$val_cond=$this->attributes['CONDITION_VALUE'];
		if ($this->attributes['HIDE']=='yes') {
			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
	        	valore=document.forms[0].".$var_cond.".value;
				  if (document.getElementById('tr_".$this->id."'))
					 document.getElementById('tr_".$this->id."').style.display='none';
					";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value){
					if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
					else $value_to_control=$inputval[$var_cond];

					if ($value_to_control==$value) {
						$this->condition_passed=true;
					}

					$this->check_js.=" \n
					//condizione $var_cond==$value
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  		if (document.getElementById('tr_".$this->id."'))
							document.getElementById('tr_".$this->id."').style.display='';
						}
						";
				}
				$this->check_js.="
				if (document.getElementById('tr_".$this->id."') && document.getElementById('tr_".$this->id."').style.display=='none' && document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else document.forms[0].".$this->id.".value='';
						}
				";
			}
			else {
				$op ='!=';
				if (preg_match("/\!/", $val_cond)) {
					$val_cond=str_replace("!", "",$val_cond);
					$op='==';
				}
				if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
				else $value_to_control=$inputval[$var_cond];
				if ($op=='==') $this->condition_passed=($value_to_control!=$val_cond);
				else $this->condition_passed=($value_to_control==$val_cond);

				$this->check_js.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
				$this->check_js.="
					if (document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else {
							if (document.forms[0].".$this->id."[0] && !document.forms[0].".$this->id.".selectedIndex){
								           radioclear('{$this->id}');
							}
						else document.forms[0].".$this->id.".value='';
						}
						}

				  if (document.getElementById('tr_".$this->id."'))	{

				     document.getElementById('tr_".$this->id."').style.display='none';

				  	}
					}
					else {

				  if (document.getElementById('tr_".$this->id."'))
					  document.getElementById('tr_".$this->id."').style.display='';
					}
					";
			}
		}
		else {

			if ($this->attributes['HIDE_THIS']=='yes') {

				if (preg_match("/,/", $val_cond)){
					$this->check_js.="
	        valore=document.forms[0].".$this->id.".value;
					document.forms[0].".$this->id.".value='';
				  	if (document.getElementById('cell_".$this->id."'))
					 	document.getElementById('cell_".$this->id."').style.display='none';
					if (document.getElementById('cell_input".$this->id."'))
					 	document.getElementById('cell_input".$this->id."').style.display='none';
					";
					$vals=explode(",",$val_cond);
					//$this->condition_passed=false;
					foreach ($vals as $key => $value){
						if ($in[$var_cond]==$value) $this->condition_passed=true;
						$this->check_js.=" \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			if (document.getElementById('cell_".$this->id."'))
								document.getElementById('cell_".$this->id."').style.display='';
							if (document.getElementById('cell_input".$this->id."'))
								document.getElementById('cell_input".$this->id."').style.display='';
						    document.forms[0].".$this->id.".value=valore;

						}
							";
					}
				}
				else {

					$op ='!=';
					if (preg_match("/\!/", $val_cond)) {
						$val_cond=str_replace("!", "",$val_cond);
						$op='==';
					}
					if ($op=='==') $this->condition_passed=($in[$var_cond]!=$val_cond);
					else $this->condition_passed=($in[$var_cond]==$val_cond);
					//echo "<hr>$op - $var_cond - $val_cond - {$this->attributes['VAR']}<hr>";
					$this->check_js.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
					$this->check_js.="
					if (document.forms[0].".$this->id.")
						document.forms[0].".$this->id.".value='';
				  	if (document.getElementById('cell_".$this->id."'))
					   document.getElementById('cell_".$this->id."').style.display='none';
					if (document.getElementById('cell_input".$this->id."'))
					   document.getElementById('cell_input".$this->id."').style.display='none';
					}
					else{
					  if (document.getElementById('cell_".$this->id."'))
						  document.getElementById('cell_".$this->id."').style.display='';
					  if (document.getElementById('cell_input".$this->id."'))
					  	document.getElementById('cell_input".$this->id."').style.display='';
					}
					";
				}
			}
			else {
				if (preg_match("/,/", $val_cond)){
					$this->check_js.="
	        valore=document.forms[0].".$this->id.".value;
	        document.forms[0].".$this->id.".value='';

						";
					$vals=explode(",",$val_cond);
					foreach ($vals as $key => $value){
						if (isset($in['INVIOCO'])) $value_to_control=$in[$var_cond];
						else $value_to_control=$inputval[$var_cond];
						if ($value_to_control==$value) {
							$this->condition_passed=true;
						}
						$this->check_js.=" \n
					//condizione $var_cond==$value
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			document.forms[0].".$this->id.".value=valore;
						}
						";

					}
				}else{
					$op ='!=';
					if (preg_match("/\!/", $val_cond)) {
						$val_cond=str_replace("!", "",$val_cond);
						$op='==';
					}
					foreach ($this->xml_form->fields as $key => $val){
						if ($val['TYPE']=='checkbox') {
							foreach ($val['VALUE'] as $key => $val){
								//echo "<li>$key</li>";
								if (!isset($in[$key])) $in[$key]='0';
							}
						}
					}
					if ($op=='==') $this->condition_passed=($in[$var_cond]!=$val_cond);
					else $this->condition_passed=($in[$var_cond]==$val_cond);

					$this->check_js.=" \n
					value=value_of('$var_cond', '0');

					if (value $op '$val_cond')
					{
						";
					$this->check_js.="
					if (document.forms[0].".$this->id.")
						{
							if (document.forms[0].".$this->id.".type=='checkbox' || (document.forms[0].".$this->id."[0] && document.forms[0].".$this->id."[0].type=='radio')){
								for(i=0;i<document.forms[0].".$this->id.".length;i++) document.forms[0].".$this->id."[i].checked=false;
							}
						else document.forms[0].".$this->id.".value='';
						}

				  if (document.getElementById('tr_".$this->id."'))	{

				     document.getElementById('tr_".$this->id."').style.display='none';

				  	}
					}
					else {

				  if (document.getElementById('tr_".$this->id."'))
					  document.getElementById('tr_".$this->id."').style.display='';
					}
					";
				}
			}
		}
		$this->html="<tr id='tr_".$this->id."' style=\"display:\">".$this->html."</tr>";
	}
*/
	
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
						  for (i=0;i<document.forms[0]." . $this->attributes ['VAR'] . ".length;i++){
						  	//alert (document.forms[0]." . $this->attributes ['VAR'] . "[i].value);
						  	if (document.forms[0]." . $this->attributes ['VAR'] . "[i].value==compila_value) document.forms[0]." . $this->attributes ['VAR'] . "[i].checked=true;
						  }
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
	function open_save($val) {
		if ($val == 'obbligatorio')
			$testo = $this->input_txt;
		$testo = make_js ( $this->input_txt );
		/* Andrea 26/01/2010
		 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
		 */
		if($this->attributes['LABEL_JS'] != ""){
			$testo=$this->attributes['LABEL_JS'];
		}
		if ($this->attributes ['CONDITION'] != '') {
			$var_cond = $this->attributes ['CONDITION'];
			$val_cond = $this->attributes ['CONDITION_VALUE'];
			$this->salva_js = "
			  	value=value_of('$var_cond', '0');
					if (value=='$val_cond')
			  	c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n
			  	";
		} else
			$this->salva_js = "c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n";
	}

	/**
	 * Controlli all'invio
	 *
	 * @param String $val
	 */
	function open_send($val) {
		if ($val == 'obbligatorio' && $this->session_vars ['INVIOCO'] == 1) {
			$this->condition_passed = true;
				if ($this->attributes ['CONDITION'] != '') {
					$var_cond = $this->attributes ['CONDITION'];
					if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
						/**
						 * CONTROLLO LATO SERVER.
						 * Modifica Colabufalo 02/03/2011 , gestione della condition_passed 
						 * per i campi radio condizionati da più valori (CONDITION_VALUE).
						 * In questo caso di reimposta $this->condition_passed = false;
						 * si splitta CONDITION_VALUE e si effettua un foreach , mettendo 
						 * le condizioni in OR. Alla prima condizione passata si setta
						 * $this->condition_passed = true; e si esce con un break.
						 * Il caso con CONDITION_VALUE singolo è gestito nell'else.
						 */
						$vals_cond=explode(",", $this->attributes['CONDITION_VALUE']);
						$this->condition_passed = false;
						foreach ($vals_cond as $key => $val_split_cond){
							if(trim($val_split_cond)!=""){
								if ($this->session_vars [$var_cond] == $val_split_cond){
									$this->condition_passed = true;
									break;
								}
							}
						}
					}else{
						$val_cond = $this->attributes ['CONDITION_VALUE'];
						if (preg_match("/\!/", $val_cond)) {
                            $val_cond=str_replace("!", "",$val_cond);
                            //Condizione diverso, controllo uguaglianza
                            if ($this->session_vars [$var_cond] == $val_cond) {
						$this->condition_passed = false;
					}
                        }else{
                            //Condizione uguale, controllo diversita'
                            if ($this->session_vars [$var_cond] != $val_cond) {
                                $this->condition_passed = false;
                            }
                        }
					}
					
				}
			//$this->validata=false;
			if ($this->condition_passed && $this->session_vars[$this->id]==''){
			$this->validata=false;
                $this->errors[$this->attributes['VAR']]="The field is mandatory";
            }
			if (!$this->condition_passed && $this->session_vars[$this->id]!=''){
                $this->validata=false;
                $this->errors[$this->attributes['VAR']]="The field must be empty (condition not passed)";
			}
			}

			if ($val == 'obbligatorio'){
				$testo = $this->testo;
				$testo = make_js ( $this->input_txt );
				/* Colabufalo 26/01/2010
				 * Se presente l'attributo LABEL_JS non considera l'elemento txt_value (anche se presente) negli alert JS
				 */
				if($this->attributes['LABEL_JS'] != ""){
					$testo=$this->attributes['LABEL_JS'];
				}
				if ($this->attributes ['CONDITION'] != '') {
					if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
						/**
						 * CONTROLLO LATO CLIENT.
						 * Colabufalo 02/03/2011 , gestione del controllo js 
						 * per i campi radio condizionati da più valori (CONDITION_VALUE).
						 * si splitta CONDITION_VALUE e si effettua un foreach , mettendo 
						 * le condizioni in OR. 
						 * Il caso con CONDITION_VALUE singolo è gestito nell'else.
						 */
						$vals_cond=explode(",", $this->attributes['CONDITION_VALUE']);
						foreach ($vals_cond as $key => $val_split_cond){
							if(trim($val_split_cond)!=""){
								if($or_condition==""){$or_condition="value=='".$val_split_cond."'";}
								else{$or_condition.="|| value=='".$val_split_cond."'";}
								$this->invia_js = "
									value=value_of('{$this->attributes['CONDITION']}', '0');
									if (".$or_condition."){
							  		c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n
							  	}";
							}
						}
					}
					else{
						$var_cond = $this->attributes ['CONDITION'];
						$val_cond = $this->attributes ['CONDITION_VALUE'];
						$this->invia_js .= "
					  	value=value_of('$var_cond', '0');
							if (value=='$val_cond')
					  	c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n
					  	
					  	";
					}
				} else
					$this->invia_js = "c1+='<<r###" . $this->attributes ['VAR'] . "###" . $testo . ">>';\n";
			}
		
		
	}

	/**
	 * Visualizzazione nella modalità  progressiva (header)
	 *
	 * @param String $var
	 * @param number $i
	 * @param array $row
	 * @param boolean $this_closed
	 * @return String
	 */
	function all_in($var, $i, $row, $this_closed){
		$val=$this->attributes;
		$body .= "
			<td class=sc4bis>";
		foreach ( $this->values as $k => $v ) {
			if ($row [$val ['VAR']] == $k)
				$checked = "checked";
			else
				$checked = "";
			if (! $this_closed)
				$body .= "
					<input type='radio' value=\"$k\" name=\"{$var}_PROGR_{$i}\" $checked>$v<br>
				";
			else {
				if ($checked == 'checked') {
					$body .= "
						<i class=\"fa fa-dot-circle-o\"></i>$v<br>
					";
				} else
					$body .= "
						<i class=\"fa fa-circle-o\"></i>$v<br>
					";
			}
		}
		$body = rtrim ( $body, "<br>" );
		$body .= "</td>";
		$ret['body']=$body;
		return $ret;
	}


	/**
	 * Visualizzazione nella modalità  progressiva (header)
	 *
	 * @param field_radio $field
	 * @param number $m_p
	 * @param form $xml_form
	 * @return String
	 */
	static function S_all_in($field, $m_p, $xml_form){
		foreach($xml_form->fields as $key => $value) {
			if($xml_form->fields[$key]['VAR']==$field) {
				$val=$value;
			}
		}

		$select_field .= $field . ",";
		$onclick_action = "";
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
			$i = 0;
			foreach ( $val ['VALUE'] as $k => $v ) {
				$posval [$i] = $k;
				$i ++;
			}
			for($i = 1; $i <= $m_p; $i ++) {
				$onclick_action .= "
					if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i})
						document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}.value=document.forms['ALL_IN_FORMS'].{$field}_tot.value;
					";
				foreach ( $posval as $pk => $pv ) {
					$onclick_action .= "
						if (document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i})
						document.forms['ALL_IN_FORMS'].{$field}_PROGR_{$i}[$pk].checked=document.forms['ALL_IN_FORMS'].{$field}_tot[$pk].checked;
						";
				}
			}
			foreach ( $val ['VALUE'] as $k => $v ) {
				$field_tot .= "
						<input type='radio' value=\"$k\" name=\"{$field}_tot\">$v<br>
					";
			}
			
			if($val['NOTE']!="")
			$note="<br /><span style=\"font-size:9px;color:red;\">".$val['NOTE']."</span>";
			
			$field_tot = rtrim ( $field_tot, "<br>" );
			$tr_agg .= "<td class=int valign=bottom >$field_tot
					<input type='button' value='applica a tutti'
					 onclick=\"
					 $onclick_action
					\">$note
					</td>";
		}
		return $tr_agg;
	}

}




?>
