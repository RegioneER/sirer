<?php 

include_once "libs/field.inc";


class field_multicheck_check extends field{
	
	var $cb_value;
	var $cb_text;
	
	/**
	 * Costruttore
	 *
	 * @param dbcon $conn
	 * @param String $xml_form
	 * @param number $i
	 * @param array $session_vars
	 * @param array $db_vars
	 * @param String $service
	 * @param array $errors
	 * @return field_prototype
	 */
	function field_multicheck_check($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors){
		parent::field($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors);
		$this->cb_value = false; //array(1=>"PIPPO",3=>"PLUTO",8=>"PAPERINO");
		//Logica di riciclo funzioni per load bytb e caricamento di selvalues
		$this->cb_value = $this->attributes['CB_VALUE'];
		$this->cb_text = $this->attributes['CB_TAG'];
	}
	
	function open_($val){
		$this->input_txt=$this->testo;
		$this->input_field="<div style=\"height:150px;overflow:auto;\">";
		$spl = explode("|",$this->db_vars[$this->id]);
		//print_r($spl);
		//die();
		foreach($this->values as $key=>$val){
			$checked="";
			$selected = "";
			#GC HDCE-1836# Es: selezionando questo studio |101165_1| viene checkato anche |1165_1|, quindi controllo che il match sia anche sui pipe |
			//if (preg_match("!{$key}!", $this->db_vars[$this->id])){
			if (preg_match("/\|{$key}\|/", $this->db_vars[$this->id])){
				$checked="checked";
				$skey = array_search($key,$spl);
				$selected = $spl[($skey+1)];
			}
			//echo $selected;
			$ichecked = "";
			if ($selected == $this->cb_value){
				$ichecked = "checked";
			}
			$this->input_field.="<input type=\"checkbox\" $checked name=\"{$this->id}_MCHECK_{$key}\">$val<br/>";
			$this->input_field.="{$this->cb_text} <input type=\"checkbox\" $ichecked name=\"{$this->id}_MCKSEL_{$key}\" value=\"{$this->cb_value}\">";
		}
		
		$this->input_field.="</div>";
	}
	
	function close_($val){
		$checkedcheck = "<img src=\"images/checkedcheck.gif\">";
		$this->input_field="";
		$this->input_txt=$this->testo;
		foreach($this->values as $key=>$val){ 
			#GC HDCE-1836# Es: selezionando questo studio |101165_1| viene checkato anche |1165_1|, quindi controllo che il match sia anche sui pipe |
			//if (preg_match("!{$key}!", $this->db_vars[$this->id])){
			if (preg_match("/\|{$key}\|/", $this->db_vars[$this->id])){
			$this->input_field.="<table><tr><td>$checkedcheck</td><td> $val</td></table>";
			}
		}		
	}
	
	function insert_stmt(){
		if ($this->session_vars ['USER_TIP'] == 'DM' && ($this->attributes['NO_DM_CHANGE']!='' || $this->attributes['CRYPTO']!='')){
   		return;
  	}
		$in=$this->session_vars;
		$value="|";
		foreach ($in as $key => $val){
			if (preg_match("!^{$this->id}_MCHECK_!", $key)){
				$mvalore=str_replace("{$this->id}_MCHECK_", "", $key);
				$value.=$mvalore."|";
				$sval = $in["{$this->id}_MCKSEL_$mvalore"];
				$value.=$sval."|";
			}
		}
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]=$this->attributes['VAR'];
			$this->value_stmt[0]=$value;
		}
	}
	
	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']} varchar2(4000 char)";
			return $ret;
		}
		else return ;
	}
	
	function open_save($val){
		$check_="{$this->id}_passed=false";
		foreach($this->values as $key=>$val){
			$check_.="
			if (document.forms[0].{$this->id}_MCHECK_{$key}.checked) {$this->id}_passed=true;
			";
		}
		$testo_js=make_js($this->testo);
		$check_.="
			if (!{$this->id}_passed){
				alert('Effettuare almeno una selezione nel campo: $testo_js');
				document.forms[0].{$this->id}_MCHECK_{$key}.focus();
				return false;
			}
			";
		$this->salva_js=$check_;
	}
	
	function open_send($val){
		$check_="{$this->id}_passed=false";
		foreach($this->values as $key=>$val){
			$check_.="
			if (document.forms[0].{$this->id}_MCHECK_{$key}.checked) {$this->id}_passed=true;
			";
		}
		$testo_js=make_js($this->testo);
		$check_.="
			if (!{$this->id}_passed){
				alert('Effettuare almeno una selezione nel campo: $testo_js');
				document.forms[0].{$this->id}_MCHECK_{$key}.focus();
				return false;
			}
			";
		$this->invia_js=$check_;
	}
	
}

?>