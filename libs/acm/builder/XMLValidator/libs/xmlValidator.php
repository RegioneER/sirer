<?php

require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xml_parser_wl.inc";
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/HTML_Parser.inc";
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/form.inc";
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/field_code_decode.inc";
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/acm/AxmrML.class.inc";
$service=$GLOBALS['service'];

if (!class_exists("xml_form")){ //bugfix xml_form potrebbe già essere stata definita nello study.module.php vmazzeo 06.03.2015
	class xml_form extends xml_form_prototype{}
}

class xmlValidator{

	var $xsd_file;
	var $xml_file;
	var $xml;
	var $validation_result;
	var $html_errors;
	var $conn;

/*
 * Costruttore, inizializza le variabili di stato relative al file xsd e xml, viene istanziato l'oggeto DOM per la 
 * rappresentazione astratta del file xml.
 * */
	function xmlValidator($xml_file, $xsd_file){
		
		/* Abilita la manipolazione degli errori */
		libxml_use_internal_errors(true);

		$this->xml_file=$xml_file;
		$this->xsd_file=$xsd_file;
		$this->xml = new DOMDocument();
		$this->xml->load($this->xml_file);

	}

/*
 * Rvede se � valido, chiama schema validate, primitiva
 * se non valido chiama errors
 * */
	function validate(){

		if (!$this->xml->schemaValidate($this->xsd_file)) {
	    	$this->validation_result = common_add_message(t("Impossible to valid the document."), ERROR);
	    	$this->libxml_display_errors($this->xml_file);
		}else{
			$this->validation_result = common_add_message(t("The file is valid!"),INFO);
		}
		
		//$this->validation_result.=$this->form_preview($this->xml_file);
		
	}

	function isValid(){
		return $this->xml->schemaValidate($this->xsd_file); 
	}	
	function form_preview($xml_file,$prefix){

		$this->conn= new dbconn();
		//$this->uploaded_file_dir 
		$myservice=$prefix;
		//var_dump($GLOBALS);
		//echo $xml_file." ".$myservice;
		$xml_form = new xml_form ( $this->conn, $myservice, "", "", "");
		$xml_form->xml_form_by_file ($xml_file);
		$xml_form->config_service['field_lib']=$_SERVER['DOCUMENT_ROOT'].'/../libs/fields/';		
		$xml_form->open_form(null, null, null, true);
		$form_preview=$xml_form->body;
		return $form_preview; 
	}
	

/*
 * codifica il singolo errore trovato dalla primitiva
 * */
	function libxml_display_error($error, $xml_base_name){
		$this->html_validation = "<div>";
//     switch ($error->level) {
//         case LIBXML_ERR_WARNING:
//             $this->html_validation .= "<div><i class=\"fa fa-exclamation-triangle orange\"></i>Warning $error->code</div>: ";
//             break;
//         case LIBXML_ERR_ERROR:
//             $this->html_validation .= "<div><i class=\"fa fa-exclamation-circle red\"></i>[Error $error->code]</div>";
//             break;
//         case LIBXML_ERR_FATAL:
//             $this->html_validation .= "<div><i class=\"fa fa-exclamation-circle red\"></i>Fatal Error $error->code</div>";
//             break;
//     }
    $error->message = preg_replace("/Element \'{http:\/\/eudract\.ClinicalTrialApplication\.xsd}/i", "", $error->message);
    $error->message = preg_replace("/\'/", "", $error->message);
    $error->message = preg_replace("/{http:\/\/eudract\.ClinicalTrialApplication\.xsd}/i", "", $error->message);
    $this->html_validation .= trim("<font style=\"font-weight:bold;\">Element</font> &raquo; ".$error->message." ");
    if ($error->file) {
    	/* Formatto l'errore */
    	$err=$error->file;
    	$err=preg_replace('/%20/', ' ', $err);
    	$err=preg_replace('/file:\/\/\//', ' ', $err);
        //$this->html_validation.="<p style=\"text-align:left;\"><font style=\"font-weight:bold;\">File</font> &raquo; ".$xml_base_name."</p>";
    }
    $this->html_validation.="<div> Line &raquo; <font style=\"color:#d94141;\">".$error->line."</font></div>";

		$this->html_validation .= "</div>";
    return $this->html_validation;
}


/*
 * Per ogni errore chiama error
 * libxml_get_errors primitiva
 * */
function libxml_display_errors($xml_base_name){
    $errors = libxml_get_errors();
    foreach ($errors as $error) {
        $this->html_errors .= $this->libxml_display_error($error, $xml_base_name);
    }
    libxml_clear_errors();
}

/*
 * restituisce il risultato della validazione
 * */
function get_validation_result(){
	return $this->validation_result;
}

/*
 * restituisce gli errori in formato html
 * */
function get_html_errors(){
	return $this->html_errors;
}

}


	function var_glob($value){
		global $in;
		global $inputval;
		if (isset($inputval[$value]) && $inputval[$value]!='') return $inputval[$value];
		if (isset($in[$value]) && $in[$value]!='') return $in[$value];
		if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') return $GLOBALS[$value];
		
		
	}


?>



