<?php 

include_once "libs/field.inc";


class field_multicheck extends field{
	
	var $initial_values; //Valori di default alla prima apertura della scheda
	
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
	function field_multicheck($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors){
		parent::field($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors);
		$this->initial_values = array(); //array(1=>"PIPPO",3=>"PLUTO",8=>"PAPERINO");
		//Logica di riciclo funzioni per load bytb e caricamento di selvalues
		if ($this->attributes['DEFAULT_BYTB']){
			$tmpvals = $this->values;
			$bytb=$this->attributes['BYTB'];
			$code=$this->attributes['BYTBCODE'];
			$decode=$this->attributes['BYTBDECODE'];
			$where=$this->attributes['BYTBWHERE'];
			$order_by=$this->attributes['BYTBORDERBY'];
			//sostituzione campi
			$this->attributes['BYTB'] = $this->attributes['DEFAULT_BYTB'];
			$this->attributes['BYTBCODE'] = $this->attributes['DEFAULT_BYTBCODE'];
			$this->attributes['BYTBDECODE'] = $this->attributes['DEFAULT_BYTBDECODE'];
			$this->attributes['BYTBWHERE'] = $this->attributes['DEFAULT_BYTBWHERE'];
			$this->attributes['BYTBORDERBY'] = $this->attributes['DEFAULT_BYTBORDERBY'];
			//Generazione init values
			$this->values = array();
			$this->fields_value_bytb($this->attributes['BYTB']);
			$this->initial_values = $this->values;
			//Rimetto normale
			$this->values = $tmpvals;
			$this->attributes['BYTB'] = $bytb;
			$this->attributes['BYTBCODE'] = $code;
			$this->attributes['BYTBDECODE'] = $decode;
			$this->attributes['BYTBWHERE'] = $where;
			$this->attributes['BYTBORDERBY'] = $order_by;
			if ($this->attributes['DEFAULT_SPLITVALUES']){
				$str = "";
				foreach ($this->initial_values as $s){
					if ($s){
						$str = $s;
						break;
					}
				}
				//$str = $this->initial_values[0];
				//echo $str;
				$this->initial_values = explode($this->attributes['DEFAULT_SPLITVALUES'],$str);
				$this->initial_values = $this->suppressEmpty($this->initial_values);
			}
		}
	}

	function suppressEmpty($array){
		$retval = array();
		foreach ($array as $a){
			if ($a != ""){
				$retval[] = $a;
			}
		}
		return $retval;
	}
	
	function open_($val){
		
		//print_r($this->initial_values);
		//print_r($this->values);
		
		$height_box="150";
		if($this->attributes['HEIGHT_BOX']) $height_box=$this->attributes['HEIGHT_BOX'];
		
		$this->input_txt="<div style=\"border-bottom: 4px solid white;padding:5px;width:100%;background-color:#E0E0E0\">";
		$this->input_txt=$this->testo;
		$this->input_txt.="</div>";
		
		$this->input_field="<div style=\"height:".$height_box."width:100%;overflow:auto;background-color:#F5F5F5\">";
		$def = false;
		if ($this->db_vars[$this->id]=="" && count($this->initial_values)>0){
			//echo "VUOTO!";
			$def = true;
		}
		foreach($this->values as $key=>$val){
			$checked="";
			#GC HDCE-1836#
			//if (preg_match("!{$key}!", $this->db_vars[$this->id])) $checked="checked";
			if (preg_match("/\|{$key}\|/", $this->db_vars[$this->id])) $checked="checked";
			if ($def && in_array($key,$this->initial_values)){$checked="checked";}
			
			//$this->input_field.="<input type=\"checkbox\" $checked name=\"{$this->id}_MCHECK_{$key}\">$val<br/>";
			$this->input_field.="<div class=\"checkbox\">
														<label>
															<input class=\"ace\" type=\"checkbox\" onclick=\"if(typeof {$this->id}_MCHECK_function != 'undefined' && $.isFunction({$this->id}_MCHECK_function)) {$this->id}_MCHECK_function($(this));\" $checked name=\"{$this->id}_MCHECK_{$key}\">
															<span class=\"lbl\"> ".$val." </span>
														</label>
      										 </div>
													 ";
			
			
			}
		
		$this->input_field.="</div>";
	}
	
	function close_($val){
		$checkedcheck = "<img src=\"images/checkedcheck.gif\">";
		$this->input_field="";
		$this->input_txt=$this->testo;
		foreach($this->values as $key=>$val){
			#GC HDCE-1836#
			//if (preg_match("!{$key}!", $this->db_vars[$this->id]))
			if (preg_match("/\|{$key}\|/", $this->db_vars[$this->id]))
			$this->input_field.="<table><tr><td>$checkedcheck</td><td> $val</td></table>";
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
				$valore=str_replace("{$this->id}_MCHECK_", "", $key);
				$value.=$valore."|";
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
			
			$javas=$this->verifyConditions();
			$javas.="{
		
				$check_
		
			}";
			
		$this->salva_js=$javas;
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
			
		$javas=$this->verifyConditions();
		$javas.="{
		
			$check_
		
		}";
			
		$this->invia_js=$javas;
	}
	
}

?>