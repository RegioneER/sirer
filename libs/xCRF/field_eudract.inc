<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_eudract extends field{

	function open_($value){
		global $in;
//		global $inputval;
		$inputval=$this->db_vars;
		$this->input_txt=$this->testo;
		if ($inputval[$this->attributes['VAR']]!='')	{
			$decode_value=$inputval[$this->attributes['VAR']];
		}
		if ($in[$this->attributes['VAR']]!='')	{
			$decode_value=$in[$this->attributes['VAR']];
		}
		$decode_values=explode("-", $decode_value);
		$this->input_field="
			<input type=\"HIDDEN\" name=\"{$this->attributes['VAR']}\" value=\"{$decode_value}\">
			<input type=\"text\" name=\"A_{$this->attributes['VAR']}\" value=\"{$decode_values[0]}\" size=4 onblur=\"
			document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].A_{$this->attributes['VAR']}.value+'-'+document.forms[0].B_{$this->attributes['VAR']}.value+'-'+document.forms[0].C_{$this->attributes['VAR']}.value;
			\">-
			<input type=\"text\" name=\"B_{$this->attributes['VAR']}\" value=\"{$decode_values[1]}\" size=6 onblur=\"
			document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].A_{$this->attributes['VAR']}.value+'-'+document.forms[0].B_{$this->attributes['VAR']}.value+'-'+document.forms[0].C_{$this->attributes['VAR']}.value;
			\">-
			<input type=\"text\" name=\"C_{$this->attributes['VAR']}\" value=\"{$decode_values[2]}\" size=2 onblur=\"
			document.forms[0].{$this->attributes['VAR']}.value=document.forms[0].A_{$this->attributes['VAR']}.value+'-'+document.forms[0].B_{$this->attributes['VAR']}.value+'-'+document.forms[0].C_{$this->attributes['VAR']}.value;
			\">
		";
	}

	function close_($value){
		global $in;
		global $inputval;
		$this->input_txt=$this->testo;
		$this->input_field="<b>{$inputval[$this->attributes['VAR']]}</b>";
	}

}

?>