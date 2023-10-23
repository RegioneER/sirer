<?
/**
 * @package Fields
 */
include_once "field_textbox.inc";

class field_cod_eu extends field_textbox{


	function open_($value){
		$in=$this->session_vars;
		$inputval=$this->db_vars;
		$conn=$this->conn;
		$txt=$this->testo;
		$this->input_txt=$txt;
		if ($value!=''){
			$splits=explode("/", $value);
			$rms_code=$splits[0];
			$eu_code_farma=$splits[2];
			$progr_dos=$splits[3];
			$tipo_var=$splits[4];
			$progr_dom=$splits[5];			
		}
		if ($this->attributes['DISABLED_ALWAYS']=='yes') $disabled="disabled";
		else $disabled="";
		$onblur="onblur=\"document.forms[0].{$this->id}.value=document.forms[0].{$this->id}_RMS.value+'/H/'+document.forms[0].{$this->id}_CODE_FARMA.value+'/'+document.forms[0].{$this->id}_PROGR_DOS.value+'/'+document.forms[0].{$this->id}_TIPO_VARIAZIONE.value+'/'+document.forms[0].{$this->id}_PROGR_DOM.value;cf();\"";
      	$this->input_field="
      		<input type=\"text\" name=\"{$this->id}_RMS\" $disabled value=\"$rms_code\" size=2 $onblur>/H/
      		<input type=\"text\" name=\"{$this->id}_CODE_FARMA\" $disabled value=\"$eu_code_farma\" size=4 $onblur>/
      		<input type=\"text\" name=\"{$this->id}_PROGR_DOS\" $disabled value=\"$progr_dos\"  size=3 $onblur>/
      		<input type=\"text\" name=\"{$this->id}_TIPO_VARIAZIONE\" $disabled value=\"$tipo_var\" size=2 $onblur>/
      		<input type=\"text\" name=\"{$this->id}_PROGR_DOM\" $disabled value=\"$progr_dom\" size=3 $onblur>
      		<input type=\"hidden\" name=\"{$this->id}\" value=\"$value\">
      	";
      	//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning! Enter at most three ciphers in the third box ";
		else
			$alert_msg="Attenzione! Inserire al massimo tre cifre nel terzo box ";
      	
      	$this->check_js.="
      	
      		if (document.forms[0].{$this->id}_PROGR_DOS.value.length>3) {
				alert('".$alert_msg."');
				document.forms[0].{$this->id}_PROGR_DOS.value='';
				document.forms[0].{$this->id}_PROGR_DOS.focus();
				return false;
			}
      	";
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