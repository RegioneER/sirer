<?php

$ftc_name="SendMain";
$ftc_description="To be called by a sub form to close the corresponding main esam.";
/**
 * Gestione dell'abilitazione  della form sub relativa al salvataggio della safety laboratory.
 *
 * 
 * @return sql op
 */
function SendMain(){
	global $in;
	global $conn;
	global $service;
	global $lang;
	
	 if($in['INVIOCO']==1){
	 		$sql3=new query($conn);
	 		$pk='';
			$vals['FINE']=1;
			$pk['ESAM']=$in['ESAM']-1;
			$pk['VISITNUM']=$in['VISITNUM'];
			$pk['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
			$pk['PROGR']=$in['PROGR'];
			$pk['CODPAT']=$in['CODPAT'];
			$sql3->update($vals, $service."_COORDINATE",$pk);	
			
			$conn->commit();
	 }
	 else{
	 	return;
	 }
}
?>
