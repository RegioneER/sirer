<?

include_once "field.inc";

/**
 * Classe Field Code/Decode per la gestione di campi che prevedono codice e decodifica
 *
 * @package Fields
 */
class field_code_decode extends field{

	/**
	 * Costruisce un array con i campi da salvare in DB ed i relativi valori
	 *
	 */
	function insert_stmt(){ 
		if ($this->session_vars ['USER_TIP'] == 'DM' && ($this->attributes['NO_DM_CHANGE']!='' || $this->attributes['CRYPTO']!='')){
			return;
		}
		$in=$this->session_vars;
		if ($this->attributes['TB']!='no'){
	  	$this->field_stmt[0]="{$this->attributes['VAR']}";
	  	$this->field_stmt[1]="D_{$this->attributes['VAR']}";
	  	$this->value_stmt[0]=$in[$this->attributes['VAR']];
	  	if($this->attributes['DECODE'][$in[$this->attributes['VAR']]]!='')
	  	$this->value_stmt[1]=$this->attributes['DECODE'][$in[$this->attributes['VAR']]];
	  	else
	  	$this->value_stmt[1]=$this->values[$in[$this->attributes['VAR']]];
	  }
		return;
	}
   
	/**
	 * allinea_db
	 * Costruisce l'array con i campi necessari da creare in DB
	 *
	 * @return array
	 */
	function allinea_db(){
  	if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']} NUMBER";
			$ret[1]="D_{$this->attributes['VAR']} VARCHAR2(200)";
			return $ret;
		}
		else return ;
	}
	
	function XML_OUTPUT($values){
		$tag="VAR";
		$out="
		<$tag NAME=\"{$this->attributes['VAR']}\">";
		
		if ($this->testo!='') $out.="
			<TESTO><![CDATA[{$this->testo}]]></TESTO>";
		$out.= "
			<VALORE><![CDATA[{$values[$this->id]}]]></VALORE>
			<DECODIFICA><![CDATA[{$values["D_".$this->id]}]]></DECODIFICA>
		</$tag>
		";
		return $out;
	}


}

?>