<?
/**
 * @package Fields
 */
include_once "field_code_decode.inc";

class field_cerca extends field_code_decode{

	function insert_stmt(){
		$in=$this->session_vars;
		if ($this->attributes['TB']!='no'){
	  	$this->field_stmt[0]="{$this->attributes['VAR']}";
	  	$this->field_stmt[1]="D_{$this->attributes['VAR']}";
	  	$this->value_stmt[0]=$in[$this->attributes['VAR']];
	  	$this->value_stmt[1]=$in["D_".$this->attributes['VAR']];
	  }
		return;
	}
	
	
	function open_($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		$this->input_txt=$this->testo;
		if ($inputval["D_".$this->id]!='')	{
			$code_value=$inputval[$this->id];
			$decode_value=$inputval["D_".$this->id];
		}
		if ($in["D_".$this->id]!='')	{
			$code_value=$in[$this->id];
			$decode_value=$in["D_".$this->id];
		}
		
		$this->input_field="
			<input type=\"HIDDEN\" name=\"{$this->id}\" value=\"{$code_value}\">
			<input type=\"text\" name=\"D_{$this->id}\" value=\"{$decode_value}\" size=40 onchange=\"document.forms[0].{$this->id}.value='';\"><!--e la jaddina canta-->
			<br><a href=\"#\" onclick=\"window.open('cerca_tb.php?tbsearch={$this->attributes['TBSEARCH']}&search='+document.forms[0].D_{$this->id}.value+'&CODE={$this->attributes['BYTBCODE']}&DECODE={$this->attributes['BYTBDECODE']}&FIELD={$this->id}','finestraindipendente','scrollbars=yes,resizable=yes,width=400,height=600'); return false;\">Ricerca nella Banca Dati</a>
		";
	}

	function close_($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		$this->input_txt=$this->testo;
		$this->input_field="<b>{$inputval['D_'.$this->attributes['VAR']]}</b>";
	}

}

?>