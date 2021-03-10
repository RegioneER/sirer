<?
/*
 * @package Fields
 */
include_once "field.inc";

class field_function extends field{
	var $max_js;
	var $min_js;
   
    function open_($value){
    	$this->attributes['COLSPAN']=$this->attributes['COLSPAN']?$this->attributes['COLSPAN']:1;
    	$this->attributes['COLS']=$this->attributes['COLS']?$this->attributes['COLS']:1;
		if(function_exists($this->attributes['FUNCTION']))
		$result=$this->attributes['FUNCTION']($value,true);
    	$this->input_txt="<tr><td colspan='".($this->attributes['COLS']*$this->attributes['COLSPAN'])."'>".$result."</td></tr>";
		return $result;
	}

	function close_($value){
		if(function_exists($this->attributes['FUNCTION']))
		$result=$this->attributes['FUNCTION']($value,false);
		return $result;
	}

	function open_compila($value){
		
	}

	function open_max($value){
	
	}

	function open_min($value){
		
				
	}

	function open_dividendo($val){
	
	}

	function open_equals($val){
		
	}

	function open_execute($value){
	
	}

	function open_on_change($value){
		
	}

	function open_sfoglia($value){
	
	}

	function open_sum($val){
		
	}

	function open_upper($value){
		
	}
	function allinea_db(){
		return ;
	}
}

?>