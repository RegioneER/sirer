<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_db extends field{


function allinea_db(){
	if ($this->attributes['VAR_TYPE']=='number') $type_field='NUMBER';
	else $type_field="VARCHAR2({$this->attributes['VAR_SIZE']})";
	return "{$this->attributes['VAR']} {$type_field}";
}


}

?>