<?php 

include_once "field_big_file.inc";

class field_fileUpload extends field_big_file{
	
	function __construct($xml_form, $i, $conn=null, $inputval=null, $in=null, $service=null, $errors=null){
		parent::__construct($xml_form, $i, $conn, $inputval, $in, $service, $errors);
		$this->cmeLayer="no";
		$this->wca="no";
		$this->applet="no";
		//if (isset($this->attributes['APPLET']) && $this->attributes['APPLET']=='yes') $this->applet="yes";
		
	}
	
}

?>