<?php

$ftc_name="DDEPatientExists";
$ftc_description="Checks if exists a row with CENTER, SITEID SUBJID in <SERVICE>_REGISTRATION.";

function DDEPatientExists() {
	
	global $in;
	global $conn;
	global $service;
	global $lang;
	if($lang=='en'){
		$alert_exist="The patient has been already submitted into the system";
	}
	else{
		$alert_exist="Il paziente è stato già inserito nel sistema";
	}
	if ($in['INVIOCO']==1){
		if (method_exists("DDE_module", "DDEPatientExists")) {
			if(DDE_module::DDEPatientExists($in['CENTER'], $in['SITEID'], $in['SUBJID'])) {
				echo "Error:#error#";
				die($alert_exist);
			}
		}
	}
	
}

?>
