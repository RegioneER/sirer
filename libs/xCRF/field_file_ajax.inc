<?php 
/**
 * @package FileAllegati
 */
include_once 'field.inc';
include_once 'field_textbox.inc';

class field_file_ajax extends field_textbox{
	
	function open_($value){
		$this->input_field="
		<span id='{$this->id}_file_id'></span>
		<a href=\"#\" onclick=\"
		ajax_file_call('ajaxUpload','VAR={$this->id}');
		return false;\">Carica nuovo file</a>
		";
		$this->input_txt="prova";
	}
	
}

?>