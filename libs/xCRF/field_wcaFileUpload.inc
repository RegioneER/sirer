<?php 

include_once "field_big_file.inc";

class field_wcaFileUpload extends field_big_file{
	
	function __construct($xml_form=null, $i=null, $conn=null, $inputval=null, $in=null, $service=null, $errors=null){
		parent::__construct($xml_form, $i, $conn, $inputval, $in, $service, $errors);
		$this->cmeLayer="no";
		$this->wca="yes";
		$this->applet="no";
		if (isset($this->attributes['APPLET']) && $this->attributes['APPLET']=='yes') $this->applet="yes";
	}
}

?>