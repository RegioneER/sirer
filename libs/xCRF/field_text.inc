<?php
/**
 * @package Fields
 */
include_once "field.inc";

class field_text extends field{

	function open_($value){
		global $in;
		$txt=$this->testo;

		if (isset($this->values)) foreach ($this->values as $key => $val) $value=$val;
		if ($this->attributes['SQL_TYPE']=='data') $value_display=substr($value,0,2)."/".substr($value,2,2)."/".substr($value,4,4);
		else $value_display=$value;
		
		//nel caso in cui abbia un numero decimale, visualizzo correttamente lo zero prima della virgola
		//modifica G.Tufano 18/02/2011
		if($this->attributes['VAR_TYPE'] == 'number' && $value > 0 && $value < 1 ){
			$value_display = '0'.$value;
		}
		
		//modifca G.Tufano 08/11/2011
		//aggiungo la funzione CRYPTO per nascondere dati sensibili al DM
		if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes'){
			$value_display = '***';
		}
		
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
		// Inizio modifica Chiara e Davide 15/06/2011
        //if ($value=='' && isset($this->attributes['BYTB'])) $value="n.d.";
		if ($value=='' && isset($this->attributes['BYTB'])) {
			$value="";
			if (!isset($this->attributes['HIDEIFEMPTY'])) {
				$value="n.d.";
			}
		}
		// Fine modifica
		
		if ($this->attributes['SQL_TYPE']=='data') 
			$value_display=substr($value,0,2)."/".substr($value,2,2)."/".substr($value,4,4);
		else 
			$value_display=$value;
		
		//nel caso in cui abbia un numero decimale, visualizzo correttamente lo zero prima della virgola
		//modifica G.Tufano 18/02/2011
		if($this->attributes['VAR_TYPE'] == 'number' && $value > 0 && $value < 1 ){
			$value = '0'.$value;
		}
		
		//modifca G.Tufano 08/11/2011
		//aggiungo la funzione CRYPTO per nascondere dati sensibili al DM
		if ($in ['USER_TIP'] != 'DE' and $this->attributes ['CRYPTO'] == 'yes'){
			$value_display = '***';
		}
		
		$this->input_field="<b>".$value_display."</b>";
		$this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
	}
	
	function all_in($var, $i, $row, $this_closed) {
	//nel caso in cui abbia un numero decimale, visualizzo correttamente lo zero prima della virgola
		//modifica G.Tufano 18/02/2011
		if($this->attributes['VAR_TYPE'] == 'number' && $row[$var] > 0 && $row[$var] < 1 ){
			$row[$var] = '0'.$row[$var];
		}
		$ret['body']="<td class=sc4bis><b>{$row[$var]}</b></td>";
		return $ret;
	}

	static function S_all_in($field, $m_p, $xml_form){
        $tr_agg=null;
	if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
										$tr_agg .= "<td class=int>&nbsp;</td>";
									}
									return $tr_agg;
	}
	
	function builder_js(){
		$field_description['field']="text";
		$field_description['order']=2;

		//$this->open_('',true);
		$field_description['view']="\"<div class=\'form-group\' style='height:10px'><div align=\'<%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.TXT_ALIGN)) %>\' ><%=  Formbuilder.helpers.simple_format(rf.get(Formbuilder.options.mappings.LABEL)) %></div></div>\"";
		
		$field_description['edit'][]='edit/db_info_label'; 	 //uso lo stesso del date_cal perchè non mi interessa settare var_type e var_size
		//$field_description['edit'][]='edit/allowed_values';
		//$field_description['edit'][]='edit/bytb';
		//$field_description['edit'][]='edit/main_sub';
		$field_description['edit'][]='edit/condition';
		//$field_description['edit'][]='edit/javascript';
		$field_description['edit'][]='edit/formatting';
		//$field_description['edit'][]='edit/save_send';
		$field_description['addButton']['class']='fa fa-quote-left';
		$field_description['addButton']['label']='Label';
		
		
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