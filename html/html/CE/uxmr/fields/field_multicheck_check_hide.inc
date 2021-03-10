<?php 

include_once "libs/field.inc";


class field_multicheck_check_hide extends field{
	
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
	function field_multicheck_check_hide($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors){
		parent::field($conn, $xml_form,$i,$session_vars, $db_vars, $service, $errors);
		$this->cb_value = false; //array(1=>"PIPPO",3=>"PLUTO",8=>"PAPERINO");
		//Logica di riciclo funzioni per load bytb e caricamento di selvalues
		$this->cb_value = $this->attributes['CB_VALUE'];
		$this->cb_text = $this->attributes['CB_TAG'];
	}
	
	function open_($val){
		
		$this->input_txt="<div style=\"border-bottom: 4px solid white;padding:5px;width:100%;background-color:#E0E0E0\">";
		$this->input_txt=$this->testo;
		$this->input_txt.="</div>";
		
		$this->input_field="<div style=\"height:400px;overflow:auto;background-color:#F5F5F5\">";
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
			//$this->input_field.="<input type=\"checkbox\" $checked name=\"{$this->id}_MCHECK_{$key}\">$val<br/>";
			$this->input_field.="<div class=\"checkbox\">
														<label>
															<input class=\"ace\" type=\"checkbox\" $checked name=\"{$this->id}_MCHECK_{$key}\">
															<span class=\"lbl\"> ".$val." </span>
														</label>
      										 </div>
													 ";
													 
			$this->input_field.="<!--{$this->cb_text}--> <input style=\"display:none;\" type=\"checkbox\" $ichecked name=\"{$this->id}_MCKSEL_{$key}\" value=\"{$this->cb_value}\">";
		}
		
		$this->input_field.="</div>";
	}
	
	function close_($val){

		//GIULIO - In visualizzazione interrogo anche la vista definita nell'attributo BYTB_VIS perche' lo studio potrebbe non essere nella vista primaria
		if($this->attributes['BYTB_VIS']) $this->fields_value_bytb_vis($this->attributes['BYTB_VIS']);
		
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

	function fields_value_bytb_vis($value){
		if ($this->xml_form->no_field_value_by_tb){
			return;
		}
		if ($this->xml_form->form['NO_LOAD_TB']!='' && $this->xml_form->closed) return;
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		//if ($this->xml_form->closed){// && $this->xml_form->form['NO_LOAD_BYTB']=="yes"){
		//	$this->values[$inputval[$this->attributes['VAR']]]=$inputval['D_'.$this->attributes['VAR']];
		//	return ;
		//}
		$code=$this->attributes['BYTBCODE'];
		$decode=$this->attributes['BYTBDECODE'];
		$where=$this->attributes['BYTBWHERE'];
		$order_by=$this->attributes['BYTBORDERBY'];
		$where=str_replace("min_of","<",$where);
		$where=str_replace("max_of",">",$where);
		
		//nel caso in cui mi riferisca a ANA_UTENTI oppure abbia settato ANCHE il parametro bytbnoprefix="yes", 
		//allora NON metto il prefisso del servizio davanti
		if (!preg_match("/ana_utenti/i",$value) && $this->attributes['BYTBNOPREFIX']=="")	
			$value=$this->service."_".$value;
		$decode=str_replace("#BR#", "<br>", $decode);
		$decode=str_replace("#i#", "<i>", $decode);
		$decode=str_replace("#/i#", "</i>", $decode);
		//$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
		$where=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $where );
		//$decode=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $decode);
		$decode=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $decode );
		//$code=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $code);
		$code=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $code );
		//$order_by=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $order_by);
		$order_by=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $order_by );
		$conn=$this->conn;
		if ($where!='') $where="where $where";
		$query="select $code as code";
		if ($decode!='') $query.=", $decode as decode";
		if ($order_by!='') $query.=" from $value $where order by $order_by";
		else if(strtolower($this->attributes['VAR_TYPE'])=='clob' || $this->attributes['TYPE']=='file_doc') $query.=" from $value $where";
		else $query.=" from $value $where order by decode asc";
		$sql=new query($conn);
		$sql->set_sql($query);
		//echo "\n<!--$query-->";
		$sql->exec();
		$in=$this->session_vars;
		while ($sql->get_row()) {
			if ($decode!='') {
				$this->values[$sql->row['CODE']]=$sql->row['DECODE'];
				if (!isset($in[$this->attributes['VAR']]) && $this->attributes['TYPE']=='hidden') {
					global $in;
					$in[$this->attributes['VAR']]=$sql->row['DECODE'];
				}
			}
			else {
				global ${$this->attributes['BYVAR']};
				$this->values[$sql->row['CODE']]=${$this->attributes['BYVAR']}[$sql->row['CODE']];
			}
		}

	}
		
}

?>