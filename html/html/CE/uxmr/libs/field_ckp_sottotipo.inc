<?php 
/**
 * @package Fields
 */
include_once 'field_checkbox.inc';

class field_ckp_sottotipo extends field_checkbox{
	

	function close_($value){
		$this->input_field="
		<table width=\"100%\" border=\"1\">
			<tr>
				<td><b>{$this->testo}</b></td>
				<td><b>Condition to be fullfilled</b></td>
				<td><b>Documentation to be supplied</b></td>
				<td><b>Procedure Type</b></td>
			</tr>
		";
		foreach ($this->values as $key=>$val){
			if (isset($this->values[$key."1"]) || isset($this->values[$key."_1"]) || $key==''){
				$this->input_field.="
			<tr>
				<td><b>{$val}</b></td>
				<td>{$this->attributes['VALUE_CONDS'][$key]}&nbsp;</td>
				<td>{$this->attributes['VALUE_DOCS'][$key]}&nbsp;</td>
				<td>{$proc_types}&nbsp;</td>
			</tr>
			";
			}
			else {
			$checked="<img src=\"images/uncheckedcheck.gif\">";
			if ($this->db_vars[$key]==1) $checked="<img src=\"images/checkedcheck.gif\">";
			if (isset($this->xml_form->old_values) && $this->xml_form->old_values[$key]!=$this->db_vars[$key]) $img_="<img src=\"images/eq_img.png\" width=\"20px\">";
			else $img_='';
			
			$this->input_field.="
			<tr>
				<td>{$img_}$checked{$val}</td>
				<td>{$this->attributes['VALUE_CONDS'][$key]}&nbsp;</td>
				<td>{$this->attributes['VALUE_DOCS'][$key]}&nbsp;</td>
				<td>{$this->attributes['VALUE_CONDITION'][$key]}&nbsp;</td>
			</tr>
			";
		}
		}
		$this->input_field.="</table>";
	}
	
	function open_($value){
		$this->input_field="
		<table width=\"100%\" border=\"1\">
			<tr>
				<td><b>{$this->testo}</b></td>
				<td><b>Condition to be fullfied</b></td>
				<td><b>Documentation to be supplied</b></td>
				<td><b>Procedure Type</b></td>
			</tr>
		
		";
		foreach ($this->values as $key=>$val){
			if (isset($this->values[$key."1"]) || isset($this->values[$key."_1"]) || $key==''){
				$this->input_field.="
			<tr>
				<td><b>{$val}</b></td>
				<td>{$this->attributes['VALUE_CONDS'][$key]}&nbsp;</td>
				<td>{$this->attributes['VALUE_DOCS'][$key]}&nbsp;</td>
				<td>{$proc_types}&nbsp;</td>
			</tr>
			";
			}
			else {
			$conds_type=$this->attributes['VALUE_CONDITION'][$key];
			$conds_types=explode(",", $conds_type);
			$disabled="DISABLED";
			foreach ($conds_types as $k=>$v_){
				$v_s=explode("|",$v_);
				
				foreach ($v_s as $k_=>$v){ 
				if ($v!=''){
					$this->check_js.="
				
				//if (document.forms[0].{$v}.value=='1')
				//document.forms[0].{$key}.disabled=false;
				";
				if ($this->db_vars[$v]==1) $disabled='';
				}else $disabled='';
				}
			} 
			$checked="";
			if ($this->db_vars[$key]==1) $checked="checked";
			
			$condition_values=explode(",",$this->attributes['VALUE_CONDS'][$key]);
			foreach ($condition_values as $ck=>$cv){
				if ($cv!=''){
					$cv=$cv-0;
					if ($conds[$this->session_vars['ESAM']-100][$cv]!='') {
						$conds[$this->session_vars['ESAM']-100][$cv].="|";
						$conds_[$this->session_vars['ESAM']-100][$cv].="|";
					}
					$conds[$this->session_vars['ESAM']-100][$cv].=$key;
					$conds_[$this->session_vars['ESAM']-100][$cv].='1';
				}
			}
		$docs_values=explode(",",$this->attributes['VALUE_DOCS'][$key]);
			foreach ($docs_values as $ck=>$cv){
				if ($cv!=''){
					$cv=$cv-0;
					if ($docs[$this->session_vars['ESAM']-100][$cv]!='') {
						$docs[$this->session_vars['ESAM']-100][$cv].="|";
						$docs_[$this->session_vars['ESAM']-100][$cv].="|";
					}
					$docs[$this->session_vars['ESAM']-100][$cv].=$key;
					$docs_[$this->session_vars['ESAM']-100][$cv].='1';
				}
			}
			$proc_types=str_replace("|", ",",$this->attributes['VALUE_CONDITION'][$key]);
			$disabled='';			
			if (isset($this->xml_form->old_values) && $this->xml_form->old_values[$key]!=$this->db_vars[$key]) $img_="<img src=\"images/eq_img.png\" width=\"20px\">";
			else $img_='';
			$this->input_field.="
			<tr>
				<td>$img_<input type='checkbox' name=\"{$key}\" value=\"1\" $checked $disabled onclick=\"cf();\">{$val}</td>
				<td>{$this->attributes['VALUE_CONDS'][$key]}&nbsp;</td>
				<td>{$this->attributes['VALUE_DOCS'][$key]}&nbsp;</td>
				<td>{$proc_types}&nbsp;</td>
			</tr>
			";
		}
		}
		foreach ($this->xml_form->fields as $f_idx => $f_value){
			if ($this->xml_form->fields[$f_idx]->attributes['VAR']==$this->id) $this->xml_form->fields[$f_idx]['SEND'] = 'abbligatorio';
			foreach ($conds[$this->session_vars['ESAM']-100] as $key=>$val){
				$idx_esam=$this->session_vars['ESAM']-100;
				if ($f_value['VAR']=="CON_{$idx_esam}_{$key}"){
					$this->xml_form->fields[$f_idx]['CONDITION']=$val;
					$this->xml_form->fields[$f_idx]['SHOW_VIS']='yes';
					$this->xml_form->fields[$f_idx]['HIDE']='yes';
					$this->xml_form->fields[$f_idx]['CONDITION_VALUE']=$conds_[$this->session_vars['ESAM']-100][$key];
				}					
			}
		foreach ($docs[$this->session_vars['ESAM']-100] as $key=>$val){
				$idx_esam=$this->session_vars['ESAM']-100;
				if ($f_value['VAR']=="DOC_{$idx_esam}_{$key}"){
					$this->xml_form->fields[$f_idx]['CONDITION']=$val;
					$this->xml_form->fields[$f_idx]['HIDE']='yes';
					$this->xml_form->fields[$f_idx]['SHOW_VIS']='yes';
					$this->xml_form->fields[$f_idx]['CONDITION_VALUE']=$docs_[$this->session_vars['ESAM']-100][$key];
				}					
			}	
		}
		$this->input_field.="</table>";
	}
	
}

?>