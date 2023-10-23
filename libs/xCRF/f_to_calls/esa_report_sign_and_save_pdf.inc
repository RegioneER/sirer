<?php

$ftc_name="DDEPatientExists";
$ftc_description="Checks if exists a row with CENTER, SITEID SUBJID in <SERVICE>_REGISTRATION.";

/**
 * Funzione ausiliaria per la creazione dei report
 *
 */
function esig_and_create_pdf_report($xml_form) {
	global $in;
	global $conn;
	global $service;
	global $lang;

	if($lang=='en') {
		$visit_sign=" All forms must be sent.";
		$alert_enable=" Your Username is not able to sign eCRF. ";
		$alert_eqpending=" The electronic signature can be affixed only if there are no query pending in the related visit. At the moment there is at least one query pending in this visit. ";
		$alert_access=" The username inserted does not match with the one used to access.";
		$alert_user=" The username is not valid.";
		$alert_passwd=" The password is not correct.";
		$alert_doc=" An error occurrend generating the PDF document.";
	} else {
		$visit_sign=" Tutti gli esami devono essere inviati.";
		$alert_enable=" L'username non corrisponde a quello con cui si è effettuato l'accesso.";
		$alert_eqpending=" La firma elettronica può essere apposto solo se non ci sono query in attesa della visita correlati. Al momento non vi è almeno una query in attesa di questa visita. ";
		$alert_access=" L'username non corrisponde a quello con cui si è effettuato l'accesso.";
		$alert_user=" L'username non è valido.";
		$alert_passwd=" La password inserita non è corretta.";
		$alert_doc=" Errore nel generare il documento PDF.";
	}

	// Controllo solo la combinazione user/password
	if ($in['INVIOCO']!=1) {
		$condition_passed=false;
		include_once '/http/lib/DriverIanus/libs.inc';
		$driver_conn=new DriverIanusDBConnection();
		$in['SAEPWD']=ereg_replace( ' ', "+", $in['SAEPWD']);
	   	//Controllo correttezza passwd immessa rispetto a quella dell'usserid in DB
//		if (CheckUserLogged()) {
			if (CheckPWD($driver_conn, strtoupper($in['remote_userid']), strtoupper($in['SAEPWD']))) {
				if(CheckUserSignEnable($in['SINVSIGN'], "PI,CO_PI") != 0) {
		   			$condition_passed = true;
				} else {
					$condition_passed=false;
					if( $in['ajax_call']!='') {
						echo "Error:#error#";
						die($alert_enable);
					}
				}
			} else {
				$condition_passed = false;
				if( $in['ajax_call']!=''){
			    	echo "Error:#error#";
					die($alert_passwd);
				}
			}
//		} else {
//			$condition_passed = false;
//			if( $in['ajax_call']!=''){
//	   	 		echo "Error:#error#";
//				die($alert_user);
//			}
//		}
	
		if($condition_passed == true && $in['ajax_call'] == ''){
			// Invio mail
			SendMailSMSSaveESAE($xml_form);
			
			// Forzo il commit
			$xml_form->conn->commit();
			// Genero il documento
			$mydocgen = new DocumentGenerator();
			$response = $mydocgen->doDocGen_f_to_call();
			
			if (!$response) {
				error_page(strtoupper($in['remote_userid']), $alert_doc, array($response));
			}
			
			return true;
		}else{
			return false;
		}
	}
}

/**
 * Manda una mail dopo la registrazione
 *
 * @param unknown_type $xml_form
 */

function SendMailSMSSaveESAE($xml_form) {
	global $in;
	global $conn;
	global $service;
	global $lang;
	$xml_form->conn->commit();

	/*Alert via mail della registrazione del paziente*/
	$vals = array();
	$val['VISITNUM'] = $in['VISITNUM'];	
	$val['CODPAT'] = $in['CODPAT'];
	$val['ESAM'] = $in['ESAM'];
	$val['PROGR'] = $in['PROGR'];
	$val['CENTER'] = $in['CENTER'];	
	$sql_mailsent =
		"select to_char(s.SINVDAT,'DD-MON-YYYY') as SINVDAT_2, s.SINVDATRC, SUBSTR(SINVTIM, 0, 2)||':'||SUBSTR(SINVTIM, 3, 2) as SINVTIM_2,
		s.SITEID, s.SUBJID, s.AETERM1, s.AETERM2, s.AETERM3, to_char(s.SAESTDAT,'DD-MON-YYYY') as SAESTDAT_2, SAESTDATRC,
		s.D_SAETYPE, s.D_SAEREL
		from {$service}_SAE s where s.codpat=:CODPAT and s.visitnum=:VISITNUM and s.esam=:ESAM and s.progr=:PROGR and s.center=:CENTER";
	$sql = new query ( $conn );
	$sql->exec($sql_mailsent, $val);
	$sql->get_row();
	$SINVDAT=NA_date_format($sql->row['SINVDAT_2'], $sql->row['SINVDATRC']);
	$SINVTIM=$sql->row['SINVTIM_2'];
	$SITEID=$sql->row['SITEID'];
	$SUBJID=$sql->row['SUBJID'];
	$AETERM1=$sql->row['AETERM1'];
	$AETERM2=$sql->row['AETERM2'];
	$AETERM3=$sql->row['AETERM3'];
	$SAESTDAT=NA_date_format($sql->row['SAESTDAT_2'], $sql->row['SAESTDATRC']);
	$D_SAETYPE=$sql->row['D_SAETYPE'];
	$D_SAEREL=$sql->row['D_SAEREL'];
	
	$vals = array();
	$vals['CODPAT'] = $in['CODPAT'];
	$sql_mailsent=
				"SELECT CMM.COUNTRY, CMM.D_COUNTRY, R.SITEID, R.SUBJID, TO_CHAR(C.INSERTDT,'DD/MM/YYYY HH24:MI:SS') AS INSERTDATE
				FROM {$service}_COORDINATE C, {$service}_REGISTRATION R, CMM_CENTER CMM
				WHERE C.CODPAT=R.CODPAT AND CMM.CODE=R.SITEID AND C.CODPAT=:CODPAT AND C.VISITNUM=0 AND C.ESAM=0 ORDER BY R.SITEID, R.SUBJID";
	$sql = new query ( $conn );
	$sql->exec($sql_mailsent, $vals);
	$sql->get_row();
	$country=$sql->row['COUNTRY'];
	

	$mailto="hypersuite@cineca.it";

	$headers  = "From: SIRE@{$_SERVER['SERVER_NAME']}\n";
	$headers .= "Content-type: text/html; charset=utf-8 \n";
	mail($mailto, "SiRE - eSAE Report",
"This report has been generated on: <b>{$SINVDAT} {$SINVTIM} GMT +0100</b> and applies to any variations in the eSAEs database.<br/><br/>
<i>Subject ID:</i> <b>{$SITEID}-{$SUBJID}</b><br/><br/>
<i>SAE description:</i>  <b>{$AETERM1} – {$AETERM2} – {$AETERM3}</b><br/><br/>
<i>Date of onset:</i> <b>{$SAESTDAT}</b><br/><br/>
<i>SAE type:</i> <b>{$D_SAETYPE}</b><br/><br/>
<i>Drug/Event Relationship:</i> <b>{$D_SAEREL}</b>", $headers);
			
	//Includo la libreria per l'sms
// 	include_once "libs/sms_api.php";
	//Invio l'sms
// 	$sms_text = "The report has been generated on:{$SINVDAT} {$SINVTIM} GMT +0100 Sub.ID:{$SITEID}-{$SUBJID} SAE desc.:".(substr($AETERM1, 0, 40))." Onset: {$SAESTDAT} SAE type:{$D_SAETYPE}";
// 	sms_send("hyperphar@hosting", "ags3xxx", $sms_notification_mailto, "SiRESAE", $sms_text, $smsto, '', '', '', ''); 
}

/**
 * Funzione ausiliaria per la formattazione della data
 *
 * @param string $date
 * @param string $date_rc
 */
function NA_date_format($date, $date_rc)
{
	$date_formatted = "";
	if (strtoupper($date_rc) == "OKOKOK") {
		$date_formatted = $date;
	} elseif (substr(strtoupper($date_rc), 0, 4) == "NANA") {
		$date_formatted = "NA-NA-".substr($date, 7);
	} elseif (substr(strtoupper($date_rc), 0, 4) == "NKNK") {
		$date_formatted = "NK-NK-".substr($date, 7);
	} elseif (substr(strtoupper($date_rc), 0, 2) == "NA") {
		$date_formatted = "NA-".substr($date, 3);
	} elseif (substr(strtoupper($date_rc), 0, 2) == "NK") {
		$date_formatted = "NK-".substr($date, 3);
	} else {
		$date_formatted = "NA-NA-NA";
	}
	
	return $date_formatted;
}

?>
