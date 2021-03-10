<?

include_once "libs/field.inc";

/**
 * Classe Field Code/Decode per la gestinoe di campi che prevedono codice e decodifica
 *
 * @package XMR_CORE
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
		$invals=$this->session_vars;
	  	global $in;
		if ($this->attributes['TB']!='no'){
		  	$this->field_stmt[0]="{$this->attributes['VAR']}";
		  	$this->field_stmt[1]="D_{$this->attributes['VAR']}";
		  	$this->value_stmt[0]=$invals[$this->attributes['VAR']];
		  	if($this->attributes['DECODE'][$invals[$this->attributes['VAR']]]!=''){
		  		$this->value_stmt[1]=$this->attributes['DECODE'][$invals[$this->attributes['VAR']]];
		  	}else{
		  		$this->value_stmt[1]=$this->values[$invals[$this->attributes['VAR']]];
		  		$this->session_vars["D_{$this->attributes['VAR']}"] = $this->values[$invals[$this->attributes['VAR']]];
		  		$in["D_{$this->attributes['VAR']}"] = $this->values[$invals[$this->attributes['VAR']]];
		  		//$_SESSION
		  	}
	  	}
	  	//print_r($this->session_vars);
	  	//global $in;
	  	//print_r($in);
	  	//die("POLLO");
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