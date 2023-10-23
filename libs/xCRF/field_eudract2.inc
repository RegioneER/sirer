<?
/**
 * @package Fields
 */
include_once "field_textbox.inc";

class field_eudract2 extends field_textbox{


	function open_($value){
		
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		$conn=$this->conn;
		$txt=$this->testo;
		$this->input_txt=$txt;


		if ($value!=''){
			$splits=explode("-", $value);
			$first=$splits[0];
			$second=$splits[1];
			$third=$splits[2];		
		}
		
		if ($this->attributes['DISABLED_ALWAYS']=='yes') $disabled="disabled";
		else $disabled="";
		
		$onblur="onblur=\"document.forms[0].{$this->id}.value=document.forms[0].{$this->id}_FIRST.value+'-'+document.forms[0].{$this->id}_SECOND.value+'-'+document.forms[0].{$this->id}_THIRD.value;cf();\"";
      	$this->input_field="
      		<input type=\"text\" name=\"{$this->id}_FIRST\" $disabled value=\"$first\" size=4 maxlength=\"4\" $onblur>-
      		<input type=\"text\" name=\"{$this->id}_SECOND\" $disabled value=\"$second\" size=6 maxlength=\"6\" $onblur>-
      		<input type=\"text\" name=\"{$this->id}_THIRD\" $disabled value=\"$third\"  size=2 maxlength=\"2\" $onblur>
      		
      		<input type=\"hidden\" name=\"{$this->id}\" value=\"$value\">
      	";
      	

		$this->salva_js.="
			document.forms[0].{$this->id}_FIRST.disabled=false;
			document.forms[0].{$this->id}_SECOND.disabled=false;
			document.forms[0].{$this->id}_THIRD.disabled=false;
			";
			
		}
		

	


	function open_send($val){
		$in=$this->session_vars;
		$send_eudract="if (document.forms[0].{$this->id}_FIRST.value.length!=4) {
				alert('Attenzione! Inserire quattro cifre nel primo box');
				document.forms[0].{$this->id}_FIRST.value='';
				document.forms[0].{$this->id}_FIRST.focus();
				return false;
				}
			if (document.forms[0].{$this->id}_SECOND.value.length!=6) {
				alert('Attenzione! Inserire sei cifre nel secondo box');
				document.forms[0].{$this->id}_SECOND.value='';
				document.forms[0].{$this->id}_SECOND.focus();
				return false;
				}
			if (document.forms[0].{$this->id}_THIRD.value.length!=2) {
				alert('Attenzione! Inserire due cifre nel terzo box');
				document.forms[0].{$this->id}_THIRD.value='';
				document.forms[0].{$this->id}_THIRD.focus();
				return false;
				}
			if (document.forms[0].{$this->id}_FIRST.value == null || !document.forms[0].{$this->id}_FIRST.value.toString().match(/^[-]?\d*\.?\d*$/)) {
				alert ('per piacere, niente caratteri!');
				return false;
				}
			if (document.forms[0].{$this->id}_SECOND.value == null || !document.forms[0].{$this->id}_SECOND.value.toString().match(/^[-]?\d*\.?\d*$/)) {
				alert ('per piacere, niente caratteri!');
				return false;
				}
			if (document.forms[0].{$this->id}_THIRD.value == null || !document.forms[0].{$this->id}_THIRD.value.toString().match(/^[-]?\d*\.?\d*$/)) {
				alert ('per piacere, niente caratteri!');
				return false;
				}
		";
		$this->invia_js.=$send_eudract;

	}





	function close_($value){
		$in=$this->session_vars;
		
		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
		if ($in['USER_TIP']!='DE' and $this->attributes['CRYPTO']=='yes') $input_html='***';
		else $input_html=$value;
		if ($input_html=='') $input_html='&nbsp;';
		$this->input_txt=$txt;
		$this->input_field='<b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>'.$this->attributes['DEF'];
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'';
		else $ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>';
		
	}
}

?>