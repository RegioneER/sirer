<?php

$ftc_name="ElectronicSignature";
$ftc_description="To be called in an exam that has the function to add a signature to that visit by authorized in <SERVICE>_FIRMA_UTENTI_CENTRI.<br/>IMPORTANT: the form file <u>must</u> be named <b>esign.xml</b>";
include_once "{$_SERVER['DOCUMENT_ROOT']}/service/DriverIanus/libs.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/db.inc";
global $conn;
$xml = simplexml_load_file("study.xml") or die("study.xml not loading");
$service=$xml->configuration->prefix;

$create_table=new query($conn);
// Creo la tabella se non esiste
$sql_create_table="SELECT COUNT(*) as CONTO FROM ALL_VIEWS WHERE VIEW_NAME='{$service}_FIRMA_UTENTI_CENTRI'";
$create_table->set_sql($sql_create_table);
$create_table->exec();
$create_table->get_row();
if ($create_table->row['CONTO'] == 0) {
	$sql_create_table="CREATE OR REPLACE FORCE VIEW {$service}_FIRMA_UTENTI_CENTRI
(
   USERNAME,
   CENTER,
   USER_ROLE
)
AS
   SELECT uss.userid AS username, uss.site_id AS center, sp.code AS user_role
     FROM users_sites_studies uss, studies_profiles sp
    WHERE USS.STUDY_PREFIX = SP.STUDY_PREFIX AND sp.STUDY_PREFIX = '{$service}'
";
	$create_table->set_sql($sql_create_table);
	$create_table->exec();
	//$sql_create_table="alter table {$service}_FIRMA_UTENTI_CENTRI add constraint PK_{$service}_FIRMA primary key (USERNAME, CENTER)";
	//$create_table->set_sql($sql_create_table);
	//$create_table->exec();
}

// Creo la tabella se non esiste
$sql_create_table="SELECT COUNT(*) as CONTO FROM ALL_TABLES WHERE TABLE_NAME='{$service}_SIGNATURES'";
$create_table->set_sql($sql_create_table);
$create_table->exec();
$create_table->get_row();
if ($create_table->row['CONTO'] == 0) {
	$sql_create_table= "create table {$service}_SIGNATURES (codpat NUMBER(38), esam NUMBER(38), visitnum NUMBER(38),
	visitnum_progr NUMBER(38), progr NUMBER(38), account VARCHAR2(2000 CHAR), sign_date DATE)";
	$create_table->set_sql($sql_create_table);
	$create_table->exec();
}



/**
 * Genstione della firma digitale con pre-controllo su condizioni studio-specifiche
 *
 *
 * @return Boolean
 */
function ElectronicSignature($xml_form){
	global $in;
	global $conn;
	global $service;
	global $lang;

	/**
	 * PIERHD-790
	 * vmazzeo 14.01.2013
	 * mancava $conn->commit() bloccando l'inserimento in _ESIG per visite contenenti l'esame skip_visit.
	 */
	$conn->commit();


	// Esame 47 -> skip visit in Gilenya, da non considerare nella firma digitale
	$visite_exams_path=str_replace("index.php", "", $_SERVER['SCRIPT_FILENAME'])."xml/visite_exams.xml";
	$vlist = new xml_esams_list ( $visite_exams_path ,$config,$session_vars, $conn);
	/*Numero dell'esame skip_visit della visita*/
	$skip_visit_esams = array();
	foreach($vlist->esams as $key=>$val){
		if($key==$in['VISITNUM']){
			foreach($val as $k=>$v){
	 			if($v['XML']=='skip_visit.xml'){
					$skip_visit_esams[] = $v['NUMBER'];
	 			}
			}
		}
	}

	if($lang=='en'){
		$visit_sign=" All forms must be sent.";
		$alert_enable=" Your Username is not able to sign eCRF. ";
		$alert_eqpending=" The electronic signature can be affixed only if there are no query pending in the related visit. At the moment there is at least one query pending in this visit. ";
		$alert_access=" The username inserted does not match with the one used to access.";
		$alert_user=" The username is not valid.";
		$alert_passwd=" The password is not correct.";
	}
	else{
		$visit_sign=" Tutti gli esami devono essere inviati.";
		$alert_enable=" L'username non corrisponde a quello con cui si è effettuato l'accesso.";
		$alert_eqpending=" La firma elettronica può essere apposto solo se non ci sono query in attesa della visita correlati. Al momento non vi è almeno una query in attesa di questa visita. ";
		$alert_access=" L'username non corrisponde a quello con cui si è effettuato l'accesso.";
		$alert_user=" L' username non è valido.";
		$alert_passwd=" La password inserita non è corretta.";
	}
// 	$sql2=new query($conn);
// 	$sql_check="select c.code CODE from CMM_CENTER c, {$service}_REGISTRAZIONE s WHERE LTRIM (TO_CHAR (c.id_center, '000'))= s.center and s.codpat={$in['CODPAT']}";
// 	$sql2->set_sql($sql_check);
// 	$sql2->exec();
// 	$sql2->get_row();

	$sql2=new query($conn);
	$sql_check="select count(*) as CONTO from {$service}_coordinate where  codpat={$in['CODPAT']} and visitnum ={$in['VISITNUM']} and ( fine is null or fine=0 ) and esam not in ({$in['ESAM']}";
	if (count($skip_visit_esams) > 0) {
		$sql_check .= ", ".implode(", ", $skip_visit_esams);
	}
	$sql_check .= ")";
	$sql2->set_sql($sql_check);
	$sql2->exec();
	$sql2->get_row();
	include_once "{$_SERVER['DOCUMENT_ROOT']}/service/DriverIanus/libs.inc";
	//include_once '/http/lib/DriverIanus/libs.inc';
	$driver_conn=new DriverIanusDBConnection();
	$in['PASSWORD']=ereg_replace( ' ', "+", $in['PASSWORD']);

	//Controllo chiusura di tutti gli esami, tranne quello della signature
	if($sql2->row['CONTO']==0){
		//Controllo corrispondenza con userid loggato
		if(CheckUserValid()){
			//Controllo che l'utente sia abilitato a firmare
			if(CheckUserSignEnable()==0){
				$condition_passed=false;
				if( $in['ajax_call']!=''){
					echo "Error:#error#";
					die($alert_enable);
				}
			}
			else{
				//Controllo correttezza pawwd immessa rispetto a quella dell'usserid in DB
				//(CheckUserPassword()){
				//include_once "{$_SERVER['DOCUMENT_ROOT']}/service/DriverIanus/libs.inc";
				$driver_conn=new DriverIanusDBConnection();
				$in['PASSWORD']=ereg_replace( ' ', "+", $in['PASSWORD']);
		    	//Controllo correttezza pawwd immessa rispetto a quella dell'usserid in DB
		    	if (CheckPWD($driver_conn, strtoupper($in['remote_userid']), strtoupper($in['PASSWORD']))){
					//Controllo di eventuali eQ pending nella visita corrente
					if(CheckEqVisitPending()!=0){
						$condition_passed=false;
						if( $in['ajax_call']!=''){
							echo "Error:#error#";
							die($alert_eqpending);
						}
					}
					else{
						$condition_passed=true;
					}
				}else{
					$condition_passed=false;
					if( $in['ajax_call']!=''){
				    	echo "Error:#error#";
						die($alert_passwd);
					}
				}
			}
		}else{
			$condition_passed=false;
			if( $in['ajax_call']!=''){
		    	echo "Error:#error#";
				die($alert_user);
			}
		}
	}
	else{
		$condition_passed=false;
		//Controllo chiusura di tutti gli esami, tranne quello della signature
		if( $in['ajax_call']!=''){
			echo "Error:#error#";
			die($visit_sign);
		}
	}

	if($condition_passed==true){
		//FINE , tracciamento nella tabella delle firme.
		UpdateDbSignature($xml_form);
	}else{
		return false;
	}

}

/**
 * Check dello userid inserito con quello con quelli registrati in db
 *
 *
 * @return Boolean
 */
function CheckUserValid(){
	global $in;
	global $conn;
	global $service;
	global $lang;
	//Controllo che l'utente sia abilitato a firmare
	$sql3=new query($conn);
	$val['USERNAME'] = $in['USERNAME'];
	$sql_check3="select count(*) as CONTO from utenti where userid=:USERNAME";
	$sql3->exec($sql_check3, $val);
	$sql3->get_row();
	// Se è 0 , l'utente non è abilitato a firmare per questo centro.
	return ($sql3->row['CONTO'] > 0) ;
}
/**
 * Check dello userid inserito con quello con cui si è effettuato l'accesso
 *
 *
 * @return Boolean
 */
function CheckUserLogged(){
	global $in;
	global $conn;
	global $service;
	global $lang;
	//Controllo corrispondenza con userid loggato
	if($in['SINVSIGN']==$in['remote_userid']){
		return true;
	}
	else{
		//Controllo corrispondenza con userid loggato
    	return false;
    }
}
/**
 * Gestione dell'abilitazione all'utente alla firma digitale.
 *
 *
 * @return Boolean
 */
function CheckUserSignEnable($username = ""){
	global $in;
	global $conn;
	global $service;
	global $lang;
	if ($username == "") {
		$username = $in['USERNAME'];
	}
	//Controllo che l'utente sia abilitato a firmare
	$sql3=new query($conn);
	$val['USERNAME'] = $username;
	$val['CENTER'] = $in['CENTER'];
	/**
     * vmazzeo
     * 21.10.2013 il filtro su PI esisteva già da prima in test e non in prod. oggi allineo in prod
	 */
    $val['USER_ROLE']='DE'; //Formerly PI
	$sql_check3="select count(*) as CONTO from {$service}_firma_utenti_centri where  username=:USERNAME and CENTER=:CENTER  AND USER_ROLE=:USER_ROLE";
	$sql3->exec($sql_check3, $val);
	$sql3->get_row();
	$enabled=$sql3->row['CONTO'];
	// Se $enabled è 0 , l'utente non è abilitato a firmare per questo centro.
	return $enabled;
}


/**
 * Gestione del match di username e password nella firma digitale.
 *
 *
 * @return Boolean
 */
function CheckUserPassword(){
	global $in;
	global $conn;
	global $service;
	global $lang;
	include_once '/http/lib/DriverIanus/libs.inc';
		$driver_conn=new DriverIanusDBConnection();
		$in['PASSWORD']=ereg_replace( ' ', "+", $in['PASSWORD']);
    	//Controllo correttezza pawwd immessa rispetto a quella dell'usserid in DB
    	if (CheckPWD($driver_conn, strtoupper($in['remote_userid']), strtoupper($in['PASSWORD']))){
 //    		print_r($in['PASSWORD']);echo "OK";
    		return true;
    	}
    	else{
    		return false;
    	}
}

function CheckEqVisitPending(){
	global $in;
	global $conn;
	global $service;
	global $lang;
	//Controllo che l'utente sia abilitato a firmare
	$sql3=new query($conn);

	$val['CODPAT'] = $in['CODPAT'];
	$val['VISITNUM'] = $in['VISITNUM'];
	$val['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
	$sql_check3="select count(*) as CONTO from {$service}_eqfield where codpat=:CODPAT and visitnum=:VISITNUM and visitnum_progr=:VISITNUM_PROGR and statofield in (0,2)";
	$sql3->exec($sql_check3, $val);
	$sql3->get_row();
	$eq_pending=$sql3->row['CONTO'];
	// Se $eq_pending è 0 , non ci sono eQuery pending nella visita.
	return $eq_pending ;
}

/**
 * Tracciamento per paziente ed esame delle form firmate digitalmente.
 * @return Boolean
 */
function UpdateDbSignature($xml_form){
	global $in;
	global $conn;
	global $service;
	global $lang;
	$sql3=new query($conn);
	//Gestione Audit Trail
	$pk='';
	$vals_at['VISITNUM']=$in['VISITNUM'];
	$vals_at['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
	$vals_at['ESAM']=$in['ESAM'];
	$vals_at['PROGR']=$in['PROGR'];
	$vals_at['CODPAT']=$in['CODPAT'];
	$vals_at['CENTER']=$in['CENTER'];
	$vals_at['VALUE_NEW']="to_char(sysdate , 'DD/MM/YYYY HH24:MI:SS')";
	$vals_at['NOMETAB']=$xml_form->form['TABLE'];
	$vals_at['USERID']=$in['remote_userid'];
	$vals_at['MODDT']="sysdate";
	$vals_at['VAR']='TIME_SIG';
	$vals_at['ACTION']="Change/update by Investigator";
	$sql3->insert($vals_at, "S_X_".$service,$pk);
//	$conn->commit();

	$visite_exams_path=str_replace("index.php", "", $_SERVER['SCRIPT_FILENAME'])."xml/visite_exams.xml";
	$vlist = new xml_esams_list ( $visite_exams_path ,$config,$session_vars, $conn);

	/*Numero dell'esame skip_visit della visita*/
	foreach($vlist->esams as $key=>$val){
		if($key==$in['VISITNUM']){
			foreach($val as $k=>$v){
	 			if($v['XML']=='skip_visit.xml'){$and_not_skip_esam="and esam <> {$v['NUMBER']}";}
			}
		}
	}

	$sql_check3="select count(*) as CONTO from {$service}_SIGNATURES where  codpat={$in['CODPAT']} and visitnum={$in['VISITNUM']}  AND VISITNUM_PROGR={$in['VISITNUM_PROGR']} ";
	$sql3->set_sql($sql_check3);
	$sql3->exec();
	$sql3->get_row();
	 if($sql3->row['CONTO']==0){
	 	$pk='';
		$vals['SIGN_DATE']="sysdate";
		$vals['ACCOUNT']=$in['remote_userid'];

		$vals['VISITNUM']=$in['VISITNUM'];
		$vals['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
		$vals['PROGR']=$in['PROGR'];
		$vals['CODPAT']=$in['CODPAT'];
 		foreach($vlist->esams as $key=>$val){
 			if($key==$in['VISITNUM']){
	 			foreach($val as $k=>$v){
	 				$vals['ESAM']=$v['NUMBER'];
	 				$sql3->insert($vals, $service."_SIGNATURES ",$pk);
	 			}
 			}
 		}
	 }
	 else{
	 	if($in['VISITNUM_PROGR']!=""){$and_visitnumprogr="and  visitnum_progr={$in['VISITNUM_PROGR']}";}
	 	else{$and_visitnumprogr="and  visitnum_progr=0";}
		//Al successivo re-send- eSignature della form signature deve essere aggiornato il record precedentemente cancellato
		$sql_update="update {$service}_signatures set sign_date=sysdate, account='{$in['remote_userid']}' 
		where visitnum={$in['VISITNUM']}  and codpat={$in['CODPAT']}  $and_visitnumprogr";
		// Commento perché la sysdate va updatata comunque
		//		and account is null and sign_date is null";
		$sql3->set_sql($sql_update);
		$sql3->ins_upd();
	 }


	 $sql_visitclose="update {$service}_coordinate set  visitclose=1 where visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and codpat={$in['CODPAT']}  ";
	 $sql3->set_sql($sql_visitclose);
	 $sql3->ins_upd();

	 $sql_fine="update {$service}_coordinate set fine=1  where  visitnum={$in['VISITNUM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and codpat={$in['CODPAT']}  $and_not_skip_esam";
	 $sql3->set_sql($sql_fine);
	 $sql3->ins_upd();

	 $conn->commit();
}

?>
