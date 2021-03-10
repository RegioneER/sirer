<?
/**
 * @package FileAllegati
 */
include_once "field.inc";

class field_allegati extends field{

	/**
	 * Enter description here...
	 *
	 */
	function insert_stmt(){
		global $in;
		return;
	}

	/**
	 * Alliena_db
	 * Costruisce la stringa di inserimento del campo nella tabella quando non presente
	 *
	 * @return string
	 */
	function allinea_db(){
		return ;
	}


	function open_($value){
		global $in;
//		global $inputval;
		$inputval=$this->db_vars;
		global $conn;
		$txt=$this->testo;
		$allegati=new allegato();
		$this->input_field=$allegati->form($this->id, 1, "prova", $conn);
		$this->input_txt=$txt;
		
	}

	/**
	 * close_
	 * Crea il codice html del campo in visualizzazioen
	 *
	 * @param string $value
	 */
	function close_($value){
		global $in;
		global $inputval;
		$ret='<tr id="'.$this->attributes['VAR'].'" style="display:">';
		$txt=$this->testo;
		$input_html="{$inputval[$this->id."_H"]}:{$inputval[$this->id."_M"]}";
		if ($input_html=='') $input_html='&nbsp;';
		$this->input_txt=$txt;
		$this->input_field='<b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>';
		if (isset($this->attributes['COLSPAN']) and $this->cols_form>1) $ret.='<td  class="input_txt" colspan="'.$this->cols_form.'">'.$txt.$input_html.'';
		else $ret.='<td class="destra">'.$txt.'</td><td class="input"><b><i><font color="#333300"><span class="textfield">'.$input_html.'</span></font></i></b>';
		#return $ret;
	}
	
	function open_send($val){
		//echo "<li>{$this->id}</li>";
		
		$testo_js=make_js($this->input_txt);
		$this->invia_js="
				c1+='<<xp00###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
				c1+='<<xp00###".$this->attributes['VAR']."_M###".$testo_js.">>';\n";
		if ($this->attributes['CONDITION']!=''){
			$this->invia_js="
				".$this->attributes['CONDITION']."_setted=false;
				";
			if (preg_match("/,/",$this->attributes['CONDITION_VALUE'])){
				$vals=explode(",", $this->attributes['CONDITION_VALUE']);
				foreach ($vals as $key => $value)
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value=='".$value."') {
								".$this->attributes['CONDITION']."_setted=true;
								c1+='<<xp00###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
								c1+='<<xp00###".$this->attributes['VAR']."_M###".$testo_js.">>';\n
								}
						";
			}
			else
			{
				$oper="==";
				if (preg_match("/!/",$this->attributes['CONDITION_VALUE'])) {$oper="!=";$this->attributes['CONDITION_VALUE']=substr($this->attributes['CONDITION_VALUE'], 1);}
				$this->invia_js.="
						value=value_of('{$this->attributes['CONDITION']}', '0');
						if (value $oper'".$this->attributes['CONDITION_VALUE']."') {
						c1+='<<xp00###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
						c1+='<<xp00###".$this->attributes['VAR']."_M###".$testo_js.">>';\n						
						".$this->attributes['CONDITION']."_setted=true;
					}
					";
			}
			$this->invia_js.="
					if (!".$this->attributes['CONDITION']."_setted) {
						c1+='<<b###".$this->attributes['VAR']."_H###".$testo_js.">>';\n
						c1+='<<b###".$this->attributes['VAR']."_M###".$testo_js.">>';\n
						}
				";
		}
		global $in;
		//print_r($in);
		//echo "<hr>{$in['invia']}!='' || {$in['INVIOCO']}=='1'<hr>";
		if ($in['invia']!='' || $in['INVIOCO']=='1'){
			if ($this->condition_passed){
				if ($in[$this->attributes['VAR']."_H"]=='' || $in[$this->attributes['VAR']."_M"]=='') {
					$this->validata=false;
					global $insert_errors;
					$testo_js=make_js($this->testo);
					$insert_errors[$this->attributes['VAR']]="Il campo è obbligatorio";
				}
			}
			else {
				if ($in[$this->attributes['VAR']."_H"]!='' || $in[$this->attributes['VAR']."_M"]!='') {
					$this->validata=false;
					global $insert_errors;
					$testo_js=make_js($this->testo);
					$insert_errors[$this->attributes['VAR']]="Il campo deve essere vuoto";
				}
			}
		}
	}

}

?>
