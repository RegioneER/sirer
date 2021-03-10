<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_link extends field{

	function open_($value){
		global $in;
		$txt=$this->testo;
		$this->input_field="";
		if (isset($this->values)) foreach ($this->values as $key => $val){
			if($val!='')$this->input_field.=strtolower($key)."=".$val."&";
		}

		if($this->input_field!='')
		$this->input_field="<a href='{$this->attributes['SCRIPT']}?{$this->input_field}'>$txt</a>";

		//      $this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
		if ($this->attributes['TB']!='no') $this->input_txt="<input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
	}

	function close_($value){
		global $in;
		$txt=$this->testo;
		$this->input_field="";
		if (isset($this->values)) foreach ($this->values as $key => $val){
			if($val!='')$this->input_field.=strtolower($key)."=".$val."&";
		}
		if($this->input_field!='')
		$this->input_field="<a href='{$this->attributes['SCRIPT']}?{$this->input_field}'>$txt</a>";

		//        $this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
	}

	/*function open_condition($val){
	$this->attributes['CONDITION_VALUE'].="!";
	$ret=parent::open_condition($val);
	$this->attributes['CONDITION_VALUE']=rtrim($this->attributes['CONDITION_VALUE'],"!");
	return $ret;
	}	*/

	function fields_value_bytb($value){
		global $in;
		global $inputval;
		//print_r($inputval);
		if ($this->xml_form->closed && $this->xml_form->form['NO_LOAD_BYTB']=="yes"){
			$this->values[$inputval[$this->attributes['VAR']]]=$inputval['D_'.$this->attributes['VAR']];
			return ;
		}
		$code=$this->attributes['BYTBCODE'];
		$decode=$this->attributes['BYTBDECODE'];
		$where=$this->attributes['BYTBWHERE'];
		$order_by=$this->attributes['BYTBORDERBY'];
		$where=str_replace("min_of","<",$where);
		$where=str_replace("max_of",">",$where);
		if (!preg_match("/ana_utenti/i",$value))	$value=$GLOBALS['service']."_".$value;
		$decode=str_replace("#BR#", "<br>", $decode);
		$decode=str_replace("#i#", "<i>", $decode);
		$decode=str_replace("#/i#", "</i>", $decode);
		/* $where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
		$decode=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $decode);
		$code=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $code);
		$order_by=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $order_by); */
		
		$where=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $where );
		$decode=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $decode );
		$code=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $code );
		$order_by=preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $order_by );
		
		//echo "<hr>{$inputval['PROV_CP']} - {$in['PROV_CP']} - {$_GLOBALS['PROV_CP']}<hr>$where";
		global $conn;
		if ($where!='') $where="where $where";
		$query="select $code as code";
		if ($decode!='') $query.=", $decode as decode";
		if ($order_by!='') $query.=" from $value $where order by $order_by";
		else $query.=" from $value $where order by decode asc";
		$sql=new query($conn);
		$sql->set_sql($query);
		//echo "<li>$query</li>";
		//$querys_[count($query_)]=
		$sql->exec();//complessa var_glob Carlo
		global $in;
		while ($sql->get_row()) {
			foreach ($sql->row as $var => $val){
				if($var!='CODE' && $var!='DECODE'){
					$this->values[$var]=$val;
				}
			}
			//			if ($decode!='') {
			//				$this->values[$sql->row['CODE']]=$sql->row['DECODE'];
			//				if (!isset($in[$this->attributes['VAR']]) && $this->attributes['TYPE']=='hidden') $in[$this->attributes['VAR']]=$sql->row['DECODE'];
			//			}
			//			else {
			//				global ${$this->attributes['BYVAR']};
			//				$this->values[$sql->row['CODE']]=${$this->attributes['BYVAR']}[$sql->row['CODE']];
			//			}
		}
	}
}


?>