<?php 
include_once "field_hidden.inc";

class field_hidden_gen extends field_hidden {

	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			$type_field="VARCHAR2({$this->attributes['VAR_SIZE']})";
			switch ($this->attributes['VAR_TYPE']){
				case 'number':
					$type_field='NUMBER';
					break;
				case 'date':
					$type_field='DATE';
					break;
			}
			$ret[0]="{$this->attributes['VAR']} {$type_field}";
			return $ret;
		}
		else return ;
	}

}

?>