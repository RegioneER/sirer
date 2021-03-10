<?php 
/**
 * @package Fields
 */
include_once "field.inc";


class field_multicheck extends field{
	
	function open_($val){
		$this->input_txt=$this->testo;
		$this->input_field="<div style=\"height:auto;overflow:auto;\">";
		foreach($this->values as $key=>$val){
			$checked="";
			$get_parameter="{$this->id}_MCHECK_{$key}";
			if (preg_match("!{$key}!", $this->db_vars[$this->id])) $checked="checked";
			if ($this->db_vars==NULL && $_GET[$get_parameter]) $checked="checked";
			$this->input_field.="
			<input type=\"checkbox\" $checked name=\"{$this->id}_MCHECK_{$key}\">$val<br/>";
			}
		
		$this->input_field.="</div>";
	}
	
	function close_($val){
		$checkedcheck = "<img src=\"images/checkedcheck.gif\">";
		$this->input_field="";
		$this->input_txt=$this->testo;
		foreach($this->values as $key=>$val){
			if (preg_match("!{$key}!", $this->db_vars[$this->id])) 
			$this->input_field.="<table><tr><td>$checkedcheck</td><td> $val</td></table>";
		}		
	}
	
	function insert_stmt(){
		$in=$this->session_vars;
		$value="|";
		foreach ($in as $key => $val){
			if (preg_match("!^{$this->id}_MCHECK_!", $key)){
				$valore=str_replace("{$this->id}_MCHECK_", "", $key);
				$value.=$valore."|";
			}
		}
		$this->field_stmt[0]=$this->attributes['VAR'];
		$this->value_stmt[0]=$value;
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