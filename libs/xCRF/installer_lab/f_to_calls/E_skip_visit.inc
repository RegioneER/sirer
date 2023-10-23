<?php

$ftc_name="skip_visit";
$ftc_description="If called, close all the exams of the visit.<br/>IMPORTANT: the form file <u>must</u> be named <b>skip_visit.xml</b>";


/**
 * Gestione dello skip di una visita, vengono chiusi tutti esami della visita corrente.
 *
 * 
 * @return Boolean
 */
function skip_visit(){
	global $in;
	global $conn;
	global $service;
	global $lang;
	
	if($lang=='en'){
		$alert_skip="The skip is not activable, make sure that the visit is empty";
		$confirm_skip=" This visit will be locked with no data entered. Please confirm.";
	}
	else{
		$alert_skip="Lo skip non è attivabile, assicurarsi che la visita sia vuota";
		$confirm_skip=" Questa visita sarà bloccata all'inserimento dei dati. Prego confermare";
	}
	
	if ($in['INVIOCO']==1){
		$sql2=new query($conn);
		$sql_check="select count(*) as CONTO from {$service}_coordinate where inizio=1 and codpat={$in['CODPAT']} and visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']}";
		$sql2->set_sql($sql_check);
		$sql2->exec();
		$sql2->get_row();
//		echo $sql2->row['CONTO']; 
//		echo $sql_check; 
		
		$count=$sql2->row['CONTO'];
//		echo "----------";echo $count;echo "----------";
		// Sono dopo il salvataggio, se � 1 vuol dire che ho salvato solo l'esame di skip_visit
		if($count!=1){
			if( $in['ajax_call']!=''){
				echo "Error:#error#";
				die($alert_skip);
			}
			else{
				error_page($in['remote_userid'],"Error : skip visit");
			}
		}
		else {
			if( $in['ajax_call']!=''){
				echo "Confirm:#confirm#";
				die($confirm_skip);
			}
			else{ 
				$sql_visitclose="update {$service}_coordinate set  visitclose=1 where visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and progr={$in['PROGR']} and codpat={$in['CODPAT']}  ";
				$sql=new query($conn);
				$sql->set_sql($sql_visitclose);
				$sql->ins_upd();
				
				$sql_fine="update {$service}_coordinate set fine=1  where visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and progr={$in['PROGR']} and codpat={$in['CODPAT']} and esam={$in['ESAM']}  ";
				$sql=new query($conn);
				$sql->set_sql($sql_fine);
				$sql->ins_upd();

				// Leggo l'eventuale visita successiva da abilitare
				$xml = simplexml_load_file("xml/visite_exams.xml") or die("visite_exams.xml not loading");
				
				foreach($xml->xpath("/visit_exam/group/visit[@number=".$in['VISITNUM']."]/enable_visit") as $visit_to_enable) {
					// Ho almeno una visita da abilitare
					$enable_next_visit = true;
					// Per ogni visita da abilitare trovo gli esami corrispondenti
					foreach($xml->xpath("/visit_exam/group/visit[@number=".intval($visit_to_enable['number'])."]/exam") as $exam_to_enable) {
						$sql=new query($conn);
						$vals['CODPAT'] = $in['CODPAT'];
						$vals['VISITNUM'] = intval($visit_to_enable['number']);
						$vals['ESAM'] = intval($exam_to_enable['number']);
						$vals['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
						$sql_exam_enabled =
							"SELECT COUNT(*) AS CONTO FROM {$service}_COORDINATE
							WHERE CODPAT=:CODPAT AND VISITNUM=:VISITNUM AND ESAM=:ESAM AND VISITNUM_PROGR=:VISITNUM_PROGR";
						$sql->exec($sql_exam_enabled, $vals);
						$sql->get_row();
						if ($sql->row['CONTO']==0) {
							$vals['PROGR'] = $in['PROGR'];
							$sql_visitenable="INSERT INTO {$service}_COORDINATE(VISITNUM, VISITNUM_PROGR, PROGR, ESAM, CODPAT, ABILITATO) VALUES(:VISITNUM, :VISITNUM_PROGR, :PROGR, :ESAM, :CODPAT, 1)";
							$sql=new query($conn);
							$sql->exec($sql_visitenable, $vals);
						}
					}
				}
			}
		}
	}
}

?>