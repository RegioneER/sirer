<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_link extends field{

	function open_($value){
		if ($this->attributes['HIDE_OPEN']!=''){
			$this->input_txt='';
			$this->input_field='';
			return;
		}
		global $in;
		$txt=$this->testo;
		$this->input_field="";
		//print_r($this->values);
		if (isset($this->values)) foreach ($this->values as $key => $val){
			if($val!=''){
				foreach ($in as $k=>$v){
					$val = str_replace("[$k]",$v,$val);
				}
				$this->input_field.=strtoupper($key)."=".$val."&";
			}
		}
		//echo($this->input_field);
		$target = "";
		if ($this->attributes['TARGET']){
			$target = "target='{$this->attributes['TARGET']}'";
		}
		if($this->input_field!='')
			$this->input_field="<a href='{$this->attributes['SCRIPT']}?{$this->input_field}' {$target} >$txt</a>";
		else
			$this->input_field="<a href='{$this->attributes['SCRIPT']}' {$target} >$txt</a>";
		
		//      $this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
		if ($this->attributes['TB']!='no') $this->input_txt="<input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
		//echo "LINKOP1: {$this->input_field}<br/>";
	}

	function close_($value){
		global $in;
		$txt=$this->testo;
		$this->input_field="";
		//print_r($this->values);
		if (isset($this->values)) foreach ($this->values as $key => $val){
			if($val!=''){
				foreach ($in as $k=>$v){
					$val = str_replace("[$k]",$v,$val);
				}
				$this->input_field.=strtoupper($key)."=".$val."&";
			}
		}
		//echo($this->input_field);
		//echo "LINKCL0.1: {$this->input_field}<br/>";
		$target = "";
		if ($this->attributes['TARGET']){
			$target = "target='{$this->attributes['TARGET']}'";
		}
		if($this->input_field!='')
			$this->input_field="<a href='{$this->attributes['SCRIPT']}?{$this->input_field}' {$target} >$txt</a>";
		else
			$this->input_field="<a href='{$this->attributes['SCRIPT']}' {$target} >$txt</a>";

		//        $this->input_txt=$txt;
		//echo "LINKCL0.2: {$this->input_field}<br/>";
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
		//echo "LINKCL1: {$this->input_field}<br/>";
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
		$where=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $where);
		$decode=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $decode);
		$code=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $code);
		$order_by=preg_replace("/\[(.*?)\]/e","var_glob('\\1')" , $order_by);
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
	
	function builder_js(){
		$field_description['field']="link";
		$field_description['order']=99;

		//$this->open_('',true);
		$field_description['view']="\"<div class=\'form-group\' style='height:10px'><div align=\'<%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.TXT_ALIGN)) %>\' ><%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.LABEL)) %></div></div>\"";
		$field_description['edit'][]='edit/link_attributes';//vmazzeo aggiunta modifica attributi script e target 17.02.2016
		$field_description['edit'][]='edit/db_info_label'; 	 //uso lo stesso del date_cal perchè non mi interessa settare var_type e var_size
		//$field_description['edit'][]='edit/allowed_values';
		//$field_description['edit'][]='edit/bytb';
		//$field_description['edit'][]='edit/main_sub';
		$field_description['edit'][]='edit/condition';
		//$field_description['edit'][]='edit/javascript';
		$field_description['edit'][]='edit/formatting';
		//$field_description['edit'][]='edit/save_send';
		$field_description['addButton']['class']='fa fa-external-link';
		$field_description['addButton']['label']='Link';
		
		
		return $field_description;
		
		
		
		/*$result = <<< EOT
		(function() {
			Formbuilder.registerField('text', {
				order : 1,
				view : "",
				edit : 	"<div class=\"panel-group\" id=\"accordion\"> " +
						"<%= Formbuilder.templates['edit/db_info']() %>\\n"+
						"<%= Formbuilder.templates['edit/allowed_values']() %>\\n"+
						"<%= Formbuilder.templates['edit/bytb']() %>" +
						"<%= Formbuilder.templates['edit/main_sub']() %>" +
						"<%= Formbuilder.templates['edit/condition']() %>" +
						"<%= Formbuilder.templates['edit/javascript']() %>" +
						"<%= Formbuilder.templates['edit/formatting']() %>" +
						"<%= Formbuilder.templates['edit/save_send']() %>"+
						"</div>",
				addButton : "<span class='symbol'><span class='fa fa-quote-left'></span></span> Text Label",
				defaultAttributes : function(attrs) {
					attrs.field_options.size = 'small';
					return attrs;
				}
			});
		
		}).call(this);
EOT;
		return $result;*/
	}
}


?>