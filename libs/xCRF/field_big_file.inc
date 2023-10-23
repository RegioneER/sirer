<?php
/**
 * @package FileAllegati
 */
include_once "libs/field_code_decode.inc";

include_once "libs/field_jQueryAppletFile.inc";
class field_big_file extends field_jQueryAppletFile{

	function __construct($xml_form=null, $i=null, $conn=null, $inputval=null, $in=null, $service=null, $errors=null){
		parent::__construct($xml_form, $i, $conn, $inputval, $in, $service, $errors);
		$this->attributes['APPLET']="yes";
	}
	
}



?>
