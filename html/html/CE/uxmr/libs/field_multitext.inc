<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_multitext extends field{

	function open_($value){
		global $in;
		$txt=$this->testo;

		if (isset($this->values)) foreach ($this->values as $key => $val) $value=$val;
		if ($this->attributes['SQL_TYPE']=='data') $value_display=substr($value,0,2)."/".substr($value,2,2)."/".substr($value,4,4);
		else $value_display=$value;
		$this->input_field="<b>".$value_display."</b>";
		$this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
		$value=str_replace("\"", "&quot;", $value);
		if ($this->attributes['TB']!='no') $this->input_txt.="<input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
	}

	function close_($value){
		global $in;

		$txt=$this->testo;


		if (isset($this->values) && $value=='') foreach ($this->values as $key => $val) $value=$val;
		else $value_display=$value;
		if ($value=='') $value="n.d.";
		if ($this->attributes['SQL_TYPE']=='data') $value_display=substr($value,0,2)."/".substr($value,2,2)."/".substr($value,4,4);
		else $value_display=$value;
		$this->input_field="<b>".$value_display."</b>";
		$this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
	}

	function fields_value_bytb($value){
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
		if (!preg_match("/ana_utenti/i",$value) && $this->attributes['BYTBNOPREFIX']=="")	$value=$this->service."_".$value;
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
		$conn=$this->conn;
		if ($where!='') $where="where $where";
		$query="select $code as code";
		if ($decode!='') $query.=", $decode as decode";
		if ($order_by!='') $query.=" from $value $where order by $order_by";
		else $query.=" from $value $where order by decode asc";
		$sql=new query($conn);
		$sql->set_sql($query);
		//echo "\n<!--$query-->";
		$sql->exec();//complessa controllare con Carlo
		$in=$this->session_vars;
		while ($sql->get_row()) {
//			print("<li>".$this->attributes['VAR']." - ".$sql->row['DECODE']."</li>");
			if ($decode!='') {
				$this->values[$sql->row['CODE']]=$sql->row['DECODE'];
				if (!isset($in[$this->attributes['VAR']]) && $this->attributes['TYPE']=='hidden') {
					global $in;
					$in[$this->attributes['VAR']]=$sql->row['DECODE']."<br />";
				}
			} else {
				global ${$this->attributes['BYVAR']};
				$this->values[$sql->row['CODE']]=${$this->attributes['BYVAR']}[$sql->row['CODE']];
			}
			$all.=$sql->row['DECODE']."<br />";
		}
//		echo $all."<hr />";
		$this->values[$this->attributes['VAR']]=$all;

	}


	function all_in($var, $i, $row, $this_closed) {
		$ret['body']="<td class=sc4bis><b>{$row[$var]}</b></td>";
		return $ret;
	}

	static function S_all_in($field, $m_p, $xml_form){
	if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
										$tr_agg .= "<td class=int>&nbsp;</td>";
									}
									return $tr_agg;
	}

}


?>