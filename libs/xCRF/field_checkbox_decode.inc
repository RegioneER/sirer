<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_checkbox_decode extends field{

	/**
	 * open_
	 * Costruisce il codice html del campo in compilazione
	 *
	 * @param string $value
	 */
	function open_($value){
//		global $inputval;
		global $in;
		$inputval=$this->db_vars;
		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$cols=$this->attributes['SUBTBCOL'];
		//			print_r ($this->attributes);

		$txt=$this->testo;
		$html_parser=new HTML_Parser();
		$html_parser->attributes['colspan']=$cols;
		$html_parser->content="";
		$input_html='
	      <table border=0 cellpadding=0 cellspacing=0 width=100%>
	      	<tr style="display:none">
	      		'.$html_parser->td().'
	      ';
		$col=0;
		if ($this->xml_form->form['CONT_FORM']=="yes")
		foreach ($this->values as $val => $decode) if (!preg_match("/_PROGR_/", $val)) unset ($this->values[$val]);
		foreach ($this->values as $val => $decode) {
			if ($col==$cols) $col=0;
			if ($col==0) $input_html.="
      		</tr>
      		<tr>
      		";
			$col++;
			/*
			$this->check_js.="
      		if (document.forms[0].$val.checked)
      				document.forms[0].$val.value=1;
      		else document.forms[0].$val.value=0;
      				";
*/
			$checked="";
			if ($inputval[$val]==1) $checked="checked";
			if ($in[$val]==1) $checked="checked";
			if ($this->attributes['VALUE_TXT'][$val]!='')
			$this->attributes['VALUE_TXT'][$val]="<br><font size=1><b>".$this->attributes['VALUE_TXT'][$val]."</b></font>";
			
			
			$input_html.='
      		<td><input type="checkbox" value="1" name="'.$val.'" '.$checked.' onclick="'.$this->attributes['ON_ACTION'].'
      		
      		cf();"/>
      		<!--span id="'.$val.'_span" onclick="document.forms[0].'.$val.'.checked=true;'.$this->attributes['ON_ACTION'].'cf();"-->
      		'.$decode.' '.$this->attributes['VALUE_TXT'][$val].' 
      		<!--/span--></td>';
			if (isset($in['INVIOCO']) && !isset($in[$val])) $in[$val]=0;
		}
		$input_html.='</tr></table>';
		$this->input_field=$input_html;
		$this->input_txt=$txt;
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
		else $ret.='<td class="destra">'.$txt.':</td><td class="input">'.$input_html.'</td></tr>';

		#return $ret;
	}

	/**
	 * close_
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param string $value
	 * @return string
	 */

	/**
	 * close_
	 * Costruisce il codice html del campo in visualizzazione
	 *
	 * @param string $value
	 * @return string
	 */
	function close_($value){
		//modifica chiara del 06/08/2009 - i global non funzionano su venice

		//global $inputval;
		//global $in;
		$in=$this->session_vars;
		$inputval=$this->db_vars;

		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$cols=$this->attributes['SUBTBCOL'];
		$txt=$this->testo;
		//      echo "{$this->attributes['VAR']}<hr>";
		$input_html='
      <table border=0 cellpadding=0 cellspacing=0 width=100%><tr><td colspan="'.$cols.'">&nbsp;</td>
      ';
		$col=0;
		if ($this->xml_form->form['CONT_FORM']=="yes")
		foreach ($this->values as $val => $decode) if (!preg_match("/_PROGR_/", $val)) unset ($this->values[$val]);

		foreach ($this->values as $val => $decode) {
			if ($col==$cols) $col=0;
			if ($col==0) $input_html.="
      		</tr>
      		<tr>
      		";
			$col++;
			$checked="";
			//      		echo "$val=$inputval[$val]<hr>";
			if ($inputval[$val]==1) $checked="checked";
			//       		echo "$val=$inputval[$val]- $checked<hr>";
			if ($checked=='checked') $input_html.='<td><img src="/images/checkedcheck.gif">';
			else $input_html.='<td><img src="/images/uncheckedcheck.gif">';
			if (isset($this->xml_form->old_values[$val]) && $this->xml_form->old_values[$val]!=$inputval[$val]) $input_html.="<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>";
			if ($this->attributes['VALUE_TXT'][$val]!='')
			$this->attributes['VALUE_TXT'][$val]="<br><font size=1><b>".$this->attributes['VALUE_TXT'][$val]."</b></font>";
			//        		echo "$input_html<hr>";
			$input_html.=$decode.' '.$this->attributes['VALUE_TXT'][$val].'</td>';
		}
		$input_html.='</tr></table>';
		//        		echo "$input_html<hr>";
		$this->input_txt=$txt;
		$this->input_field=$input_html;
		//        		echo "---------{$this->input_field}<hr>";
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.':'.$input_html.'</td>';
		else $ret.='<td class="destra" align=right>'.$txt.':</td><td class="input">'.$input_html.'</td></tr>';
		return $ret;
	}

	/**
	 * Popola le propriet "field_stmt" e "value_stmt" necessarie alla costruzione degli stmt di inserimento/update
	 *
	 */
	function insert_stmt(){
		global $in;
		if ($this->attributes['BYTB']!='' )$this->fields_value_bytb($this->attributes['BYTB']);
		
		
		if ($this->attributes['TB']!='no'){
			$i=0;
			foreach ($this->values as $key => $val){				
				$this->field_stmt[$i]="{$key}";
				$this->value_stmt[$i]="{$in[$key]}";
				
				if($in[$key]==1){
					$i++;
					$this->field_stmt[$i]="D_{$key}";
					$this->value_stmt[$i]="{$this->attributes['DECODE'][$key]}";
				}
				$i++;
			}
		}
		
		return;
	}

	/**
	 * open_save
	 * Costruisce i controlli javascript e lato server per il salvataggio della scheda
	 *
	 * @param string $val
	 */
	function open_save($val){
		
	global $in;
		if ($this->xml_form->form['CONT_FORM']=="yes" && !preg_match("/_PROGR_/",$this->attributes['VAR'])) return true;
		if ($this->attributes['CONDITION']!='') {
			$var_cond=$this->attributes['CONDITION'];
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if (preg_match("/,/", $val_cond)){
				$vals=explode(",",$val_cond);
				foreach ($vals as $key => $value)	if ($in[$var_cond]==$value) $this->condition_passed=true;
			}
			else {
				if ($in[$var_cond]==$val_cond) $this->condition_passed=true;
				else $this->condition_passed=false;
			}
		}
		else {
			$this->condition_passed=true;
		
			$this->salva_js="
				var checked_{$this->id}=false;
				";
			foreach($this->values as $key => $val){
				$this->salva_js.="
					if (document.forms[0].{$key}.checked) checked_{$this->id}=true;
				";
			}
			if ($this->attributes['ALERT']!='') {
				$msg=$this->attributes['ALERT'];
			}
			else $msg="Selezionare almeno un checkbox";
			$this->salva_js.="
			if (!checked_{$this->id}){				
				alert('$msg');
				document.forms[0].{$this->id}.focus();
				return false;
			}
			";
		}
		if (($in['salva']!='' || $in['INVIOCO']=='0')){
			$checked=false;
			foreach($this->values as $key => $val){
				if ($in[$key]!='0') $checked=true;
			}
			
			global $insert_errors;
			if ($this->condition_passed && !$checked) {
				$this->validata=false;
				$insert_errors[$this->attributes['VAR']]='Selezionare almeno un checkbox';
			}
			if (!$this->condition_passed && $checked) {
				$this->validata=false;
				$insert_errors[$this->attributes['VAR']]='Lasciare libero il seguente campo';
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
	function open_send($val){
		global $in;
		//if ($this->xml_form->form['CONT_FORM']=="yes" && !preg_match("/_PROGR_/",$this->attributes['VAR'])) return true;
		if ($this->attributes['CONDITION']!='') {
			$var_cond=$this->attributes['CONDITION'];
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if (preg_match("/,/", $val_cond)){
				$vals=explode(",",$val_cond);
				//$this->condition_passed=false;
				foreach ($vals as $key => $value)	if ($in[$var_cond]==$value) $this->condition_passed=true;
			}
			else {
				//echo "<hr>$var_cond={$in[$var_cond]} - $val_cond<hr>";
				if ($in[$var_cond]==$val_cond) $this->condition_passed=true;
				else $this->condition_passed=false;
			}
		}
		else $this->condition_passed=true;
		if (($in['invia']!='' || $in['INVIOCO']=='1')){
			$checked=false;
			foreach($this->values as $key => $val){
//				echo "<li>$key - $val - {$in[$key]}</li>";
				if ($in[$key]!='0') $checked=true;
			}
			global $insert_errors;
			//print_r($this->attributes);
			if ($this->condition_passed && !$checked) {
				$this->validata=false;
				$insert_errors[$this->attributes['VAR']]='Selezionare almeno un checkbox';
			}
			if (!$this->condition_passed && $checked) {
				$this->validata=false;
				$insert_errors[$this->attributes['VAR']]='Lasciare libero il seguente campo';
			}

			//if (!$this->validata) $insert_errors[$this->attributes['VAR']]='Selezionare almeno un checkbox';
		}


	}

	/**
	 * open_group_send
	 * Gestione dei controlli sull'invio di un gruppo di check
	 *
	 * @param string $val
	 */
	function open_group_send($val){
        $controllo_js=null;
		global $in;
		//print_r($this->xml_form);
		
		//		/if ($this->condition_passed) echo "<hr>ciao<hr>";
		$go_on=false;
		$group_campi='';
		$group_start='';
		foreach ($this->xml_form->fields as $key => $val){
			if ($val['GROUP']==$this->attributes['GROUP']){
				if ($group_start=='')$group_start=$val['VAR'];
				if (isset($val['VALUE'])) foreach($val['VALUE'] as $key => $val){
					$group[count($group)]=$key;
					$group_campi.=$val.", ";
					if ($in[$key]!='' && $in[$key]!=0) $go_on=true;
				}
				//print_r($val);
			}
		}
		
		
		$group_campi=rtrim($group_campi,", ");
		$group_campi=str_replace('"','\\"',$group_campi);
		if($group_start==$this->attributes['VAR']){
			if($this->attributes['CONDITION']){
				$var_cond=$this->attributes['CONDITION'];
				$inputval=$this->db_vars;
				
				$val_cond=$this->attributes['CONDITION_VALUE'];
				if (preg_match("/,/", $val_cond)){
					$vals=explode(",",$val_cond);
					$controllo_js.="
						value=value_of('$var_cond', '0');
						if (";
					foreach ($vals as $key => $value){

						$controllo_js.=" value=='$value' ||";
					}
					$controllo_js=rtrim($controllo_js,"||");
					$controllo_js.=")";
				}
				else {

					$op ='==';
					if (preg_match("/\!/", $val_cond)) {
						$val_cond=str_replace("!", "",$val_cond);
						$op='!=';
					}

					$controllo_js=" \n
					value=value_of('$var_cond', '0');
					if (value $op '$val_cond')

						";

				}
			}
			$controllo_js.="
					if(";
			foreach ($group as $checkbox)
			$controllo_js.=" !document.forms[0].$checkbox.checked	&&";
			$controllo_js=rtrim($controllo_js,"&&");
			$group_campi=make_js($group_campi);
			
			if($this->config_service['lang'] == "en"){
				$testo="Attention choose one of the following fields:\\n$group_campi";
			}else{
				$testo="Attenzione scegliere uno tra i seguenti campi:\\n$group_campi";
			}
		
			if($this->attributes['TESTO_ALERT'])$testo=$this->attributes['TESTO_ALERT'];
			$controllo_js.="){
			alert(\"$testo\");
			return false;
			}
			";
		}
		
		if ($in['invia']!='' || $in['INVIOCO']=='1' || $this->attributes['GROUP_SAVE']=='obbligatorio'){
			if (!$go_on && ($this->condition_passed || $this->attributes['CONDITION']=='')){
				global $insert_errors;
				$this->validata=false;
				{
					
					foreach ($group as $key=>$val){
						if ((isset($_POST[$val]) && $_POST[$val]=='1') || (!isset($_POST[$val]) && $this->db_vars[$val]==1)){
							$this->validata=true;
						}else {
							
						}
					}
				}
				if(!$this->validata)
				$insert_errors[$this->attributes['VAR']]="Please make at least one selection";
			}
		}
		$this->invia_js.=$controllo_js;
		if($this->attributes['GROUP_SAVE']=='obbligatorio')$this->salva_js.=$controllo_js;
		//echo "</ul>";
	}

	function open_group_save($value){
		if(!isset($this->attributes['GROUP_SEND'])) {
			return $this->open_group_send($value);
		}
	}


	function open_send_group($val){
        $js_check_fine=null;
        $js_check_=null;
        $in=null; //TODO: mi sembra sbagliato!!!!
		if ($this->attributes['CONDITION']!='') {
			$this->invia_js.="";
			$var_cond=$this->attributes['CONDITION'];
			$val_cond=$this->attributes['CONDITION_VALUE'];
			if (preg_match("/,/", $val_cond)){
				$vals=explode(",",$val_cond);
				//$this->condition_passed=false;
				foreach ($vals as $key => $value)				
					if ($in[$var_cond]==$value) $this->condition_passed=true;
			}
			else {
				if ($in[$var_cond]==$val_cond) $this->condition_passed=true;
				else $this->condition_passed=false;
			}
		}
		else $this->condition_passed=true;
		
		foreach ($this->attributes['VALUE_GROUP'] as $key=>$val){
			$group[$val][]=$key;
		}
		foreach ($group as $key=>$val){
			
			$js_check_fine.="group_{$key} && ";
			foreach ($val as $k=>$v){
				if (!isset($js_check[$key])) $js_check[$key]="\ngroup_$key=false;";
				$js_check[$key].="\nif (document.forms[0].$v.checked) group_$key=true;";
			}
		}
		$js_check_fine=rtrim($js_check_fine," && ");
		foreach ($js_check as $key=>$val){
			$js_check_.=$val;	
		}
		$this->testo_js=make_js($this->testo);
		$js_check_.="\nif (!($js_check_fine)) {
			alert('Attenzione! Campo {$this->testo_js} incompleto');
			return false;
		}";
		$this->invia_js.=$js_check_;
		if ($this->attributes['CONDITION']!='') {
			$this->invia_js.="";
		}				
	}

	/**
	 * allinea_db
	 * Costruisce l'array dei campi necessari da creare in DB	 *
	 *
	 * @return array
	 */
	function allinea_db(){
		if ($this->attributes['BYTB']!='' ) $this->fields_value_bytb($this->attributes['BYTB']);
		if ($this->attributes['TB']!='no'){
			$i=0;
			foreach ($this->values as $key => $val){
				$ret[$i]="{$key} NUMBER";
				$i++;
				$ret[$i]="D_{$key} VARCHAR2(200 CHAR)";
				$i++;
			}
			return $ret;
		}
		else return ;
	}



	/**
	 * open_none
	 * Sbianca la checkbox in determinate ipotesi
	 *
	 * @param string $value
	 */
	function open_none($value){
        $sbianca=null;
		foreach ($this->values as $key => $val){
			if ($key!=$value) $sbianca.="\n document.forms[0].{$key}.checked=false;";
		}
		$this->check_js.="
				if (document.forms[0].{$value}.checked) {
					$sbianca
				}
			";
	}

	function open_set_na($value){
        $js_string_na=null;
        $js_string_bl=null;
		$split=explode(",",$value);
		foreach ($split as $key=>$val) {
			$js_string_na.="\n document.forms[0].$val.value='NA';";
			$js_string_bl.="\n if(document.forms[0].$val.value=='NA') document.forms[0].$val.value='';";
		}

		$this->check_js.="
		if (document.forms[0].{$this->id}.checked){
		{$js_string_na}
	}
	else{ $js_string_bl }
		";

	}
}


?>