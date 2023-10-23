<?
/**
 * @package Fields
 */

include_once "field_code_decode.inc";

class field_select_visione extends field_code_decode{

	function open_($value){
        $input_html=null;
        $options=null;
        $agg_=null;
        $ret=null;
		global $in;
//		global $inputval;
		$inputval=$this->db_vars;
		$optgroup=false;
		$txt=$this->testo;
		$submit="";
		if ($this->attributes['SUBMIT']!='') $submit="submit();";
		$onchange="";
		if ($this->attributes['ONCHANGE']!='') $onchange="{$this->attributes['ONCHANGE']};";
		$action="";
		if ($this->attributes['ON_ACTION']!='' && $this->attributes['ACTION_TYPE']!='') {
			$action=$this->attributes['ACTION_TYPE']."=\"".$this->attributes['ON_ACTION']."\"";
		}
		if (isset($in[$this->attributes['VAR']])) unset ($inputval[$this->attributes['VAR']]);
		$disabled="";
		if ($this->attributes['DISABLED']!='' && $value!='') $disabled="disabled";
		$action="";
		if ($this->attributes['CALL_CF']!='') $cf_call="cf();";
		$this_progr="";

		if (count($this->values)==1){
			foreach ($this->values as $val => $decode) {
				$valore=$val;
				$decodifica=$decode;
			}
			$input_html.='<b>'.$decode.'<input type="hidden" name="'.$this->attributes['VAR'].'" value="'.$valore.'"/><input type="hidden" name="D_'.$this->attributes['VAR'].'"  value="'.$decode.'"/>'.$agg_;
		}
		else {
			$i=0;
			foreach ($this->values as $val => $decode) {
				$selected="";
				if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
				if ($in[$this->attributes['VAR']]==$val) $selected="selected";
				if (preg_match("/optgroup/",$val))
				{
					$optgroup=true;
					if ($options!='') $options.="
	        				</optgroup>";
					$options.='
	        				<optgroup label="'.$decode.'">';
				}
				else $options.='
	        				<option value="'.$val.'" '.$selected.'>'.$decode.'</option>';
				$i++;
			}
			if ($optgroup) $options.="</optgroup>";
			if (isset($in['TB_COLL']) && $in['TB_COLL']!='')  $input_html='<select '.$disabled.' name="TB_COLL_'.$in['ID_REF'].'_'.$this->attributes['VAR'].'" onchange="'.$cf_call.''.$submit.$onchange.'"'.$action.'>';
			else $input_html='<select  '.$disabled.' name="'.$this->attributes['VAR'].'" onchange="'.$cf_call.''.$submit.$onchange.'"'.$action.'>';
			if ($i>1) $input_html.="<option value=\"\">&nbsp;</option>";
			$input_html.=$options.'</select><input type="hidden" name="D_'.$this->attributes['VAR'].'"/> '.$agg_;
		}
		$this->input_field=$input_html."&nbsp;".$this->attributes['DEF'];
		$this->input_txt=$txt;
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input" colspan="'.$this->cols_form.'">'.$txt.$input_html.'</td>';
		else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td>';
	}

	function close_($value){
        $input_html=null;
		global $in;
		global $inputval;
		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
		if ($in['salva']!='' && $this->attributes['SAVE']=='obbligatorio' && $in[$this->attributes['VAR']]=='') {
			$this->validata=false;
			$txt.="<br/><font size='-1' color='red'>Error!!!Make a selection</font>";
		}
		foreach ($this->values as $val => $decode) {
			$selected="";
			#echo "<hr>".$this->attributes['VAR']." - in ".$in[$this->attributes['VAR']]." - inputval ".$inputval[$this->attributes['VAR']]." - ".$val;
			if ($inputval[$this->attributes['VAR']]==$val) $selected="selected";
			if ($in[$this->attributes['VAR']]!='' && $in[$this->attributes['VAR']]==$val) $selected="selected";
			if ($selected=='selected') {
				$input_html.='<b><i><u><font color="#333300" size="2"><span class="selectedOption">'.$decode.'</span></font></u></i></b><br>';
				
			}
			else if ($this->attributes['SHOW_SELECTED']=='') $input_html.='<font color="#005dce" size="1"><span class="unselectedOption">'.$decode.'</span></font><br>';

		}
		$this->input_txt=$txt;
		$this->input_field=$input_html;
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'"><table border=0 cellpadding=0 cellspacing=0><tr><td>'.$txt."</td><td>".$input_html.'</td></tr></table></td>';
		else $ret.='<td class="destra">'.$txt.'</td><td class="input">'.$input_html.'</td></tr>';
		return $ret;
	}

	function open_send($val){
		//Echo "<hr>sono qui<hr>";
		global $in;
		$testo=$this->testo;
		$testo_js=make_js($testo);
		#echo "<hr>invia $testo $testo_js<hr>";
		if ($this->attributes['CONDITION']!='') {

			$var_cond=$this->attributes['CONDITION'];
			$val_cond=$this->attributes['CONDITION_VALUE'];

			if (preg_match("/,/", $val_cond)){
				$vals=explode(",",$val_cond);
				//$this->condition_passed=false;
				foreach ($vals as $key => $value){
					if ($in[$var_cond]==$value) $this->condition_passed=true;
					$this->invia_js=" \n
						value=value_of('$var_cond', '0');
						if (value=='$value')
						{
				  			c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n
						}
							";
				}
			}
			else {
				//echo "<hr>$var_cond={$in[$var_cond]} - $val_cond<hr>";
				if ($in[$var_cond]==$val_cond) $this->condition_passed=true;
				else $this->condition_passed=false;
				$this->invia_js="
			  	//c1+='<<kt###".$this->attributes['VAR']."###v&&&".$var_cond."&&&=#".$val_cond."#*#*$$$".$testo_js.">>';\n
          		//c1+='<<kv###".$this->attributes['VAR']."###v&&&".$var_cond."&&&!#".$val_cond."#*#*$$$=##Vuoto#".$testo_js.">>';\n
//			  	value=value_of('$var_cond', '0');
//					if (value=='$val_cond') c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n
			  	";
			}
		}
		else $this->invia_js="c1+='<<si###".$this->attributes['VAR']."###".$testo_js.">>';\n";
		global $in;

		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']]==''){
					global $insert_errors;
					$this->validata=false;
					$insert_errors[$this->attributes['VAR']]='Selezione obbligatoria';
				}
			}
			else {
				if ($in[$this->attributes['VAR']]!=''){
					global $insert_errors;
					$this->validata=false;
					$insert_errors[$this->attributes['VAR']]='Deselezionare il seguente campo';
				}
			}
		}
	}

	function insert_stmt(){
		global $in;
		//print_r($this);
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]="{$this->attributes['VAR']}";
			$this->field_stmt[1]="D_{$this->attributes['VAR']}";
			$this->value_stmt[0]=$in[$this->attributes['VAR']];
			$this->value_stmt[1]=$this->values[$in[$this->attributes['VAR']]];
		}
		return;
	}

	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']} VARCHAR2(40)";
			$ret[1]="D_{$this->attributes['VAR']} VARCHAR2(200)";
			return $ret;
		}
		else return ;
	}

}

?>