<?
/**
 * @package Fields
 */
class field{

	var $attributes;
	var $values;
	var $cols_form;
	var $testo;
	var $html;
	var $field_stmt;
	var $values_stmt;
	var $id;

	function field($xml_form,$i){
		global $in;
		$this->xml_form=$xml_form;
		$this->cols_form=$xml_form->form['COLS'];
		foreach ($xml_form->fields[$i] as $key => $val){
			switch($key):
			case "TESTO":
				$this->testo=$val;
				break;
			case "VALUE":
				$this->values=$val;
				break;
			default:
				$this->attributes[$key]=$val;
				endswitch;
		}
		if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
		if ($this->attributes['VAR']) $this->id=$this->attributes['VAR'];
		else {
			$this->id=$this->attributes['NAME'];
			$this->attributes['TB']='no';
		}
		//print_r($this);
	}

	function make_open_html(){
		//campo in compilazione
		$function_to_call='open_';
		global $in;
		global $inputval;
		if (isset($this->values) and !is_array($this->values)) $value=$this->values;
		if (isset($inputval[$this->attributes['VAR']])) $value=$inputval[$this->attributes['VAR']];
		if (isset($in[$this->attributes['VAR']])) $value=$in[$this->attributes['VAR']];
		if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
		//CHIAMATA DELLA OPEN
		if (method_exists($this,$function_to_call)) $this->{$function_to_call}($value);
		$cols=$this->attributes['COLS']+0;
		if ($cols==0) $cols=1;
		if ($this->attributes['TYPE']=='hidden') $this->html='<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';


		# Per ogni attributo chiamo la funzione apposita (open_{tipologia campo}_{nome attributo})#
		if (count($this->attributes)>0) foreach($this->attributes as $key => $val){
			$function_to_call='open_'.$key;
			if (method_exists($this,$function_to_call)) $this->{$function_to_call}($val);
		}

		if (isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) {
			$colspan=$cols*$this->attributes['COLSPAN'];
			if ($this->input_field=='') $this->html=$this->input_txt;
			else $this->html='<td  class="input" colspan="'.$colspan.'">'.$this->input_txt.$this->input_field.'</td>';
		}
		else
		#Se è presente una tipologia diversa da hidden creo la cella#
		{
			//if ($this->input_txt!='') $this->input_txt.=":";
			if ($this->attributes['TYPE']!='hidden') $this->html='<td colspan="'.$cols.'" class="destra">'.$this->input_txt.'</td><td colspan="'.$cols.'" class="input">'.$this->input_field.'</td>';
		}


		#Aggiungo le stringe di controlli javascript relativa al campo in DATA#
		if ($this->attributes['TYPE']=='data' && $this->salva_js=='')
		{
			$dcod='00';
			if ($this->attributes['DCONT']=='yes') $dcod='16';
			$this->salva_js.="
				c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
		}
		if ($this->attributes['TYPE']=='data' && $this->invia_js=='')
		{
			$dcod='00';
			if ($this->attributes['DCONT']=='yes') $dcod='16';
			$this->invia_js.="
				c1+='<<fd".$dcod."###".$this->attributes['VAR']."###".$testo.">>';";
		}
		
		//if (isset($this->attributes['CONDITION']) && $this->attributes['CONDITION']!='') $this->html="<tr id=''>".$this->html."</tr>";
	}

	function open_($value){
		global $in;
		$ret='<tr id="'.$this->attributes['NAME'].'" style="display:">';
		$txt=$this->testo;
		$this->input_txt=$txt."<tr>";
		return;
	}

	function close_($value){
		global $in;
		global $inputval;
		$ret='<tr id="'.$this->attributes['NAME'].'" style="display:">';
		$txt=$this->testo;
		if ($inputval[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE'])
		$this->input_txt=$txt."<tr>";
		return;
	}

	function insert_stmt(){
		global $in;
		//echo "<hr>";
		//print_r($in);
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]=$this->attributes['VAR'];
			$this->value_stmt[0]=$in[$this->attributes['VAR']];
		}
		//print_r($this->value_stmt);
		return;
	}

	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			if ($this->attributes['VAR_TYPE']=='number') $type_field='NUMBER';
			else $type_field="VARCHAR2({$this->attributes['VAR_SIZE']})";
			$ret[0]="{$this->attributes['VAR']} {$type_field}";
			return $ret;
		}
		else return ;
	}

	function open_condition($val){
		$var_cond=$val;
		$val_cond=$this->attributes['CONDITION_VALUE'];
		if ($this->attributes['HIDE']=='yes') {
			if (preg_match("/,/", $val_cond)){
				$this->check_js.="
	        valore=document.forms[0].".$this->id.".value;
					document.forms[0].".$this->id.".value='';
				  if (document.getElementById('".$this->id."'))
					 document.getElementById('".$this->id."').style.display='none';
					";
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value)
				$this->check_js.=" \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  	if (document.getElementById('".$this->id."'))
								document.getElementById('".$this->id."').style.display='';
						    document.forms[0].".$this->id.".value=valore;
	
						}
							";
			}
			else {
				$op ='!=';
				if (preg_match("/\!/", $val_cond)) {
					$val_cond=str_replace("!", "",$val_cond);
					$op='==';
				}
				$this->check_js=" \n
					value=value_of('$var_cond', '0');
					if (value $op '$val_cond')
					{
						";
				$this->check_js.="
					if (document.forms[0].".$this->id.")
						document.forms[0].".$this->id.".value='';
				  if (document.getElementById('".$this->id."'))
					   document.getElementById('".$this->id."').style.display='none';
					}
					else 
				  if (document.getElementById('".$this->id."'))
					  document.getElementById('".$this->id."').style.display='';
					";
			}
		}
		else $this->check_js="
			value=value_of('$var_cond', '0');
						if (value=='$val_cond')
						{ 
						document.getElementById('".$this->id."').style.display='';
						}
						else {
						document.forms[0].".$this->id.".value='';
						document.getElementById('".$this->id."').style.display='none';
						}
						";
				 
		$this->html="<tr id='".$this->id."' style=\"display:\">".$this->html."</tr>";
	}

	function open_disabled($value){
		$this->check_js.="
				if(document.forms[0].".$this->id.".disabled)
					document.forms[0].".$this->id.".disabled=true;
			";
	}

	function open_max($value){
		if (preg_match("/\[/",$campi[$i])){
			$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
			$this->invia_js.="
						value=value_of('".$campo."', '0');
						";
		}
		else {
			$this->invia_js.="value=$val;\n";
			
		}
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning, the value must be less than  ";
		else
			$alert_msg="Attenzione il valore deve essere minore di ";
			
		$this->invia_js.="
				if (document.forms[0].".$this->id.".value>value) {
					alert('".$alert_msg."'+value);
					document.forms[0].".$this->id.".focus();
					return false;
				} 
		";				
	}

	function open_min($value){
		if (preg_match("/\[/",$campi[$i])){
			$campo=preg_replace("/\[(.*?)\]/e", "$1" , $campi[$i]);
			$this->invia_js.="
						value=value_of('".$campo."', '0');
						";
		}
		else {
			$this->invia_js.="value=$val;\n";
		}
		
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning, the value must be greater than  ";
		else
			$alert_msg="Attenzione il valore deve essere maggiore di ";
			
		$this->invia_js.="
				if (document.forms[0].".$this->id.".value<=value) {
					alert('".$alert_msg."'+value);
					document.forms[0].".$this->id.".focus();
					return false;
				} 
		";				
	}

	function open_save($val){
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
		else
		{
			if ($this->attributes['FM_CODE'])
			$fm=$this->attributes['FM_CODE'];
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')
			$controllo="np".$fm;
			else
			$controllo="xp".$fm;
			if ($val!='obbligatorio') $controllo="f".$controllo;
		}
		$testo_js=make_js($this->testo);
		if (($val=='obbligatorio' && $this->attributes['CONDITION']=='')||$this->attributes['VAR_TYPE']!='text'){
			$this->salva_js="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
		if ($val=='obbligatorio' && $this->attributes['CONDITION']!=''){
			$this->salva_js="
				if (document.forms[0].".$this->attributes['CONDITION'].".value=='".$this->attributes['CONDITION_VALUE']."') c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		}
	}

	function open_send($val){
		if ($this->attributes['VAR_TYPE']=='text')
		$controllo="t";
		else
		{
			if ($this->attributes['FM_CODE'])
			$fm=$this->attributes['FM_CODE'];
			else
			$fm="00";
			if ($this->attributes['VAR_STYPE']=='int')

			$controllo="np".$fm;
			else
			$controllo="xp".$fm;
		}
		$testo_js=make_js($this->input_txt);
		$this->invia_js="
				c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		if ($this->attributes['CONDITION']!=''){
			$this->invia_js="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->invia_js.="
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
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<".$controllo."###".$this->attributes['VAR']."###".$testo_js.">>';
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->invia_js.="
					if (!".$this->attributes['CONDITION']."_setted) {c1+='<<b###".$this->attributes['VAR']."###".$testo_js.">>';}
				";
		}
	}

	function fields_value_bytb($value){
		$code=$this->attributes['BYTBCODE'];
		$decode=$this->attributes['BYTBDECODE'];
		$where=$this->attributes['BYTBWHERE'];
		$where=str_replace("min_of","<",$where);
		$where=str_replace("max_of",">",$where);
		if (!preg_match("/ana_utenti/i",$value))	$value=$GLOBALS['service']."_".$value;
		$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
		$decode=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $decode);
		$code=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $code);
		global $conn;
		if ($where!='') $where="where $where";
		$query="select $code as code";
		if ($decode!='') $query.=", $decode as decode";
		$query.=" from $value $where order by decode asc";
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();//complessa var_glob Carlo
		#echo "<hr>$query";
		while ($sql->get_row()) {
			if ($decode!='') $this->values[$sql->row['CODE']]=$sql->row['DECODE'];
			else {
				global ${$this->attributes['BYVAR']};
				$this->values[$sql->row['CODE']]=${$this->attributes['BYVAR']}[$sql->row['CODE']];
			}
		}
	}

	function make_close_html(){
		if (isset($this->attributes['VAR'])) $this->html='<tr id='.$this->attributes['VAR'].' style="display:">';
		//        else $this->html='<tr>';
		$function_to_call='close_';
		global $in;
		global $inputval;
		if (isset($inputval[$this->attributes['VAR']])) $value=$inputval[$this->attributes['VAR']];
		if ($this->attributes['BYTB']!='') $this->fields_value_bytb($this->attributes['BYTB']);
		if (method_exists($this,$function_to_call)) $this->{$function_to_call}($value);
		$cols=$this->attributes['COLS']+0;
		if ($cols==0) $cols=1;
		#Tag field con definizione mancante di tipologa=>deve essere stampato solo il valore testuale#
		if (isset($this->attributes['COLSPAN']) || !isset($this->attributes['VAR'])) {
			$colspan=$cols*$this->attributes['COLSPAN'];
			if ($this->input_field=='') $this->html=$this->input_txt;
			else $this->html='<td  class="input" colspan="'.$colspan.'">'.$this->input_txt.":".$this->input_field.'</td>';
		}
		else
		#Se è presente una tipologia diversa da hidden creo la cella#
		//        	if($this->attributes['HIDEVIS']=='yes') $this->attributes['HIDE']='yes' ;
		if ($this->attributes['TYPE']!='hidden') {
			//if ($this->input_txt!='') $this->input_txt.=':';
			if (($this->attributes['HIDE']!='yes'&&$this->attributes['HIDEVIS']!='yes') || ($inputval[$this->attributes['VAR']]!='' || $inputval[$this->attributes['CONDITION']]==$this->attributes['CONDITION_VALUE']))
			$this->html='<td colspan="'.$cols.'" class="destra">'.$this->input_txt.'</td><td colspan="'.$cols.'" class="input">'.$this->input_field.'</td>';
		}
		#se la tipologia è hidden creo un TR non visualizzabile#
		if ($this->attributes['TYPE']=='hidden') $this->html='';#<tr id="'.$this->attributes['VAR'].'" style="display:none">'.$this->input_field.'</tr>';
		#$this->html=$input_html;
	}

}


?>