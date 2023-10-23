<?php

$ftc_name="SubjidExist";
$ftc_description="Checks if exists a row with CENTER e SUBJID in <SERVICE>_REGISTRAZIONE.";

function SubjidExist() {
	global $in;
	global $conn;
	global $service;
	global $lang;
	if($lang=='en'){
		$alert_exist="The patient number already exist ";
	}
	else{
		$alert_exist="Il codice del paziente esistente";
	}
	
	if ($in['INVIOCO']==1){
		$sql2_tmp=new query($conn);
		$vals = array();
		$vals['CENTER'] = $in['CENTER'];
		$vals['SUBJID'] = $in['SUBJID'];
		$sql_subjid_tmp="select count(*) as CONTO from {$service}_REGISTRAZIONE t where CENTER=:CENTER and SUBJID=:SUBJID";
		$sql2_tmp->exec($sql_subjid_tmp, $vals);
		$sql2_tmp->get_row();
		Logger::info(intval($sql2_tmp->row['CONTO']));
		Logger::info($sql_subjid_tmp);
		Logger::info($vals);
		if($sql2_tmp->row['CONTO'] > 1){
			echo "Error:#error#";
			die($alert_exist);
		}
	}
	
}

?>
