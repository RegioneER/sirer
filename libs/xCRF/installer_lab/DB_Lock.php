<?php
//ini_set('display_errors',1);
//require_once "libs/hyperlibs/http_lib.inc";
require_once "/http/lib/php_utils/smarty/Smarty.class.php";
/** Require della libreria per l'interfacciamento al DB del servizio. */
include_once "libs/db.inc";
include_once "config.inc";
$conn= new dbconn();


if ($_SERVER['REMOTE_USER'] != 'ADMIN' && substr($_SERVER["REMOTE_USER"], 0, 3) != '997') {
	die("Utente non abilitato");
}

$xml = simplexml_load_file("study.xml") or die("feed not loading");
$study_prefix=$xml->configuration->prefix;

/** Check esistenza tabella nella BD dello studio **/
$query_check_existence4 = "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='{$study_prefix}_DBLOCK'";
$query=new query($conn);
$query->set_sql ( $query_check_existence4 );
$query->exec ();
if($query->get_row ()){
	$return = true;
}
else
{
	$query_create = "
	create table {$study_prefix}_DBLOCK
	(
	CENTER NUMBER DEFAULT -1 NOT NULL ENABLE, 
	CODPAT NUMBER DEFAULT -1 NOT NULL ENABLE, 
	VISITNUM NUMBER DEFAULT -1 NOT NULL ENABLE, 
	ESAM NUMBER DEFAULT -1 NOT NULL ENABLE, 
	DBLOCK NUMBER, 
	D_DBLOCK VARCHAR2(25 CHAR),
	CONSTRAINT PK_{$study_prefix}_DBLOCK PRIMARY KEY (CENTER,CODPAT,VISITNUM,ESAM)
	)";
	//echo $query_create;
	$sql = new query ( $conn );
	$sql->set_sql ( $query_create );
	$sql->ins_upd ();
}

define('SMARTY_DIR', '/http/lib/php_utils/smarty/');

$template = new Smarty();


$icon_file = array (
		"edit" => "libs/images/icon_edit_18x18.png",
		"new" => "libs/images/icon_cd_new_18x18.png",
		"save" => "libs/images/icon_save_18x18.png",
		"delete" => "libs/images/icon_remove_18x18.png",
		"undo" => "libs/images/icon_left_18x18.png",
		"explore" => "libs/images/icon_explore_18x18.png",
		"loading" => "libs/images/waiting_animatedCircle.gif",
		"save_forbidden" => "libs/images/icon_save_forbidden_18x18.png",
		"up" => "libs/images/icon_up_18x18.png",
		"edit_forbidden" => "libs/images/icon_edit_forbidden_18x18.png",
		"edit_languages" => "libs/images/icon_languages_18x18.png",
		"edit_languages_forbidden" => "libs/images/icon_languages_forbidden_18x18.png",
		"info" => "libs/images/icon_info_18x18.png",
		"sent_mail" => "libs/images/icon_sent_mail_18x18.jpg",
		"ok" => "libs/images/icon_ok_18x18.png",
		"right"=>"libs/images/icon_right_18x18.png",
		"yellow"=>"libs/images/yellowball.gif",
		"red"=>"libs/images/redball.gif",
		"green"=>"libs/images/greenball.gif",
);
$template->assign("icon_file", $icon_file);

/**
 ARRAY DELLE POSSIBILI FUNZIONALITA' DA DISABILITARE
 RICORDATI CHE E' UNA BITMAP
 EQUERY DBLOCK = 1
 SAVESEND DBLOCK = 2
 NEWPATIENT DBLOCK = 4
 OBVIOUS CORRECTION DBLOCK = 8
*/
$function=$config_service['dblock_functions'];


$template->assign("funzioni",$function);

if(isset($_POST['Submit']) && $_POST['Submit']!=""){
	if(isset($_POST['lock_type'])&&$_POST['lock_type']=='PER_ID_CENTER'){

		/** Lista dei centri */
		$str1="select distinct id_center,code, PI
				from cmm_center  where id_center not like '599' order by ID_CENTER";
		$sql=new query($conn);
		$sql->exec($str1);

		while($sql->get_row()){
			$centers[$sql->row['ID_CENTER']]=$sql->row;
			$centers[$sql->row['ID_CENTER']]['DBLOCK']=0; //inizializzo i dblock a 0 per tutti i centri, li valorizzo correttamente con la select sucecssiva
			foreach($function as $func=>$value){
				$centers[$sql->row['ID_CENTER']][$value]=0; //inizializzo i bit a 0 per ogni funzione da disabilitare
			}
		}




		$val=array();
		foreach($_POST as $name=>$value){
			/** valorizzo i bit per il dblock in base alle post che mi sono arrivate */
			if(preg_match("/[0-9]_/i", $name)){
				$centro_funzione=explode("_", $name);
				$centro=$centro_funzione[0];
				$funzione=$centro_funzione[1];
				$centers[$centro][$funzione]=$value;
			}


		}

		foreach($centers as $centro){
			$dblockbin="";

			foreach($function as $funzione){

				if($centro[$funzione]=="0"){
					$dblockbin="0".$dblockbin;
				}
				else{
					$dblockbin="1".$dblockbin;
				}
			}//funzione

			$dblock=bindec($dblockbin);
			$val['CENTER'] = $centro['ID_CENTER'];
			$val['DBLOCK'] = $dblock;

			//STO BLOCCANDO TUTTI I PAZIENTI DI UN CENTRO QUINDI POSSO ANCHE ELIMINARE LE EVENTUALI ENTRIES PER CODPAT E INSERIRE UN NUOVO RECORD PER QUESTO CENTRO
			$delete_center = "DELETE FROM {$study_prefix}_DBLOCK WHERE CENTER=:CENTER AND CODPAT=-1";
			$sql2 = new query ( $conn );
			$sql2->exec($delete_center, $val);
			//INSERISCO IL RECORD PER IL CENTRO solo se sto bloccando $value!=0 (vuol dire che sto sbloccando)


				$sql2=new query($conn);
				$sql2->insert($val,"{$study_prefix}_DBLOCK");

		}//centro

		$location=substr($_SERVER["REQUEST_URI"],0,strrpos($_SERVER["REQUEST_URI"],'?'));

	}
	elseif(isset($_POST['lock_type'])&&$_POST['lock_type']=='PER_CODPAT'){
		/** Lista dei pazienti di un centro */
		$str1="select CODPAT,SITEID, SUBJID
		from {$study_prefix}_REGISTRATION
		where CENTER={$_POST['CENTRO']} AND VISITNUM=0 AND ESAM=0 ORDER BY SUBJID";
		//echo $str1;
		$sql=new query($conn);
		$sql->exec($str1);

		while($sql->get_row()){
			$patients[$sql->row['CODPAT']]=$sql->row;
			$centro_name=$sql->row['SITEID'];
		}

		$val=array();
		$val['CENTER']=$_POST['CENTRO'];
		foreach($_POST as $name=>$value){
			/** valorizzo i bit per il dblock in base alle post che mi sono arrivate */
			if(preg_match("/[0-9]_/i", $name)){
				$paziente_funzione=explode("_", $name);
				$paziente=$paziente_funzione[0];
				$funzione=$paziente_funzione[1];
				$patients[$paziente][$funzione]=$value;
				$patients[$paziente]['CODPAT']=$paziente;
			}
		
		
		}
		
		
		
		foreach($patients as $paziente){
			$dblockbin="";
			
			foreach($function as $funzione){
			
				if($paziente[$funzione]==""){
					$dblockbin="0".$dblockbin;
				}
				else{
					$dblockbin="1".$dblockbin;
				}
			}//funzione
			
			$dblock=bindec($dblockbin);
			$val['CODPAT'] = $paziente['CODPAT'];
			$val['DBLOCK'] = $dblock;
			
			
			//STO AGGIORNANDO IL PAZIENTE: QUINDI ELIMINO IL RECORD ATTUALE (SE ESISTE
			$delete_center = "DELETE FROM {$study_prefix}_DBLOCK WHERE CENTER=:CENTER AND CODPAT=:CODPAT";
			$sql2 = new query ( $conn );
			$sql2->exec($delete_center, $val);
			
			//INSERISCO IL RECORD PER IL PAZIENTE SOLO SE STO SOVRASCRIVENDO (INERIHT=='');
		
			if(!isset($paziente['INHERIT'])||$paziente['INHERIT']==""){
				$sql2=new query($conn);
				$sql2->insert($val,"{$study_prefix}_DBLOCK");
				var_dump($sql2->get_sql());
			}
		}//centro
		$location=$_SERVER["REQUEST_URI"];
	}
	$conn->commit();
	//die();
	//echo $location;
	header( "Location: {$location}") ;
}




if(isset($_GET['centro']) && $_GET['centro']!=''){
	/** Lista dei pazienti di un centro */
	$str1="select CODPAT,SITEID, SUBJID
	from {$study_prefix}_REGISTRATION
	where CENTER={$_GET['centro']} AND VISITNUM=0 AND ESAM=0 ORDER BY SUBJID";
	$sql=new query($conn);
	$sql->exec($str1);

	while($sql->get_row()){
		$patients[$sql->row['CODPAT']]=$sql->row;
		$centro_name=$sql->row['SITEID'];
	}



	/** CONTROLLO SE I PAZIENTI NON SONO BLOCCATI A LIVELLO DI CENTRO */
	$str="select DBLOCK from {$study_prefix}_dblock where CENTER={$_GET['centro']} and codpat =-1";
	$sql=new query($conn);
	$sql->set_sql($str);
	$sql->exec();
	$sql->get_row();
	$center_dblock=$sql->row['DBLOCK'];
	//ASSEGNO IL VALORE CHE HO IN DB AL CENTRO
	//$patients[$codpat]['DBLOCK']=$center_dblock;
	/**OTTENGO IL VALORE DI DBLOCK DEL CENTRO COME BITMAP*/
	$center_dblock_bin=decbin($center_dblock);
	$center_dblock_bin=substr("00000000".$center_dblock_bin, -1*sizeof($function));

	foreach($function as $func=>$value){
		//ASSEGNO IL VALORE PER OGNI FUNZIONE COME BIT (1 blocco abilitato, 0 blocco non abilitato) AL CENTRO
		$center_lock[$_GET['centro']][$value]=substr($center_dblock_bin,-1*$func,1);
	}


	foreach($patients as $patient){
		$patients[$patient['CODPAT']]['DBLOCK']=$center_dblock;
		$patients[$patient['CODPAT']]['INHERIT']="1"; //IL PAZIENTE STA EREDITANDO DAL CENTRO (nel ciclo successivo setto inherit a 0 perchè sta sovrascrivendo)
		foreach($function as $func=>$value){
			//ASSEGNO IL VALORE PER OGNI FUNZIONE COME BIT (1 blocco abilitato, 0 blocco non abilitato) AD OGNI PAZIENTE ****EREDITANDO DAL CENTRO******
			$patients[$patient['CODPAT']][$value]=substr($center_dblock_bin,-1*$func,1);
		}
	}
	

	/** Valori presenti attualmente nella tabella relativa al DBLOCK per i pazienti di questo centro */
	$str="select * from {$study_prefix}_dblock where CENTER={$_GET['centro']} and codpat !=-1";
	$sql=new query($conn);
	$sql->set_sql($str);
	$sql->exec();

	while($sql->get_row()){
		$patient_dblock=$sql->row['DBLOCK'];
		$patient_dblock_bin=decbin($patient_dblock);
		$patient_dblock_bin=substr("00000000".$patient_dblock_bin, -1*sizeof($function));
		$patients[$sql->row['CODPAT']]['DBLOCK']=$patient_dblock;
		$patients[$sql->row['CODPAT']]['INHERIT']="0";

		foreach($function as $func=>$value){
			//ASSEGNO IL VALORE PER OGNI FUNZIONE COME BIT (1 blocco abilitato, 0 blocco non abilitato) AL PAZIENTE SOVRASCRIVENDO QUELLA EREDITATA DAL CENTRO
			$patients[$sql->row['CODPAT']][$value]=substr($patient_dblock_bin,-1*$func,1);
		}
	}


	$template->assign("pazienti",$patients);
	$template->assign("centro",$_GET['centro']);
	$template->assign("centro_name",$centro_name);
	$template->assign("centro_lock",$center_lock);

}
else{
	/** Lista dei centri */
	$str1="select distinct id_center,code, PI
	  from cmm_center  where id_center not like '599' order by ID_CENTER";
	$sql=new query($conn);
	$sql->exec($str1);

	while($sql->get_row()){
		$centers[$sql->row['ID_CENTER']]=$sql->row;
		$centers[$sql->row['ID_CENTER']]['DBLOCK']=0; //inizializzo i dblock a 0 per tutti i centri, li valorizzo correttamente con la select sucecssiva
		foreach($function as $func=>$value){
			$centers[$sql->row['ID_CENTER']][$value]=0; //inizializzo i bit a 0 per ogni funzione da disabilitare
		}
	}


	/** Valori presenti attualmente nella tabella DBLOCK relativa ad un blocco a livello di centro*/
	$str="select * from {$study_prefix}_dblock  where codpat =-1 and visitnum =-1 and esam =-1";
	$sql=new query($conn);
	$sql->set_sql($str);
	$sql->exec();

	while($sql->get_row()){
		$center_dblock=$sql->row['DBLOCK'];
		//ASSEGNO IL VALORE CHE HO IN DB AL CENTRO
		$centers[$sql->row['CENTER']]['DBLOCK']=$center_dblock;
		/**OTTENGO IL VALORE DI DBLOCK COME BITMAP*/
		$center_dblock_bin=decbin($center_dblock);
		$center_dblock_bin=substr("00000000".$center_dblock_bin, -1*sizeof($function));
		foreach($function as $func=>$value){
			//ASSEGNO IL VALORE PER OGNI FUNZIONE COME BIT (1 blocco abilitato, 0 blocco non abilitato)
			$centers[$sql->row['CENTER']][$value]=substr($center_dblock_bin,-1*$func,1);
		}
		/** controllo se ci sono lock a livello di paziente o di visita o di esame OVERRIDE DELLE FUNZIONI DA PARTE DEI PAZIENTI*/
		/** prendo i valori presenti attualmente nella tabella relativa al DBLOCK per i pazienti di questo centro */
		$str="select * from {$study_prefix}_dblock where CENTER={$sql->row['CENTER']} and codpat !=-1";
		$sql2=new query($conn);
		$sql2->set_sql($str);
		$sql2->exec();
		$overrided_functions=array();
		while($sql2->get_row()){
			$patient_dblock=$sql2->row['DBLOCK'];
			$patient_dblock_bin=decbin($patient_dblock);
			$patient_dblock_bin=substr("00000000".$patient_dblock_bin, -1*sizeof($function));
			foreach($function as $func=>$value){
				//ASSEGNO IL VALORE PER OGNI FUNZIONE COME BIT (1 blocco abilitato, 0 blocco non abilitato) AL PAZIENTE SOVRASCRIVENDO QUELLA EREDITATA DAL CENTRO
				if($centers[$sql->row['CENTER']][$value]!=substr($patient_dblock_bin,-1*$func,1)){
					//echo "<b>{$value} DIVERSI!!!!</b><br/> ";
					$centers[$sql->row['CENTER']]['OVERRIDED_'.$value]++;
				}
			}
			//SETTO A 0 IL BIT PER IL BLOCCO DELL'ARRUOLAMENTO IN MODO DA CONTROLLARE L'UGLIAGLIANZA DEI BIT RESTANTI
			$center_dblock_bin=substr_replace($center_dblock_bin,'0',-1*array_search('NEWPATIENT', $config_service['dblock_functions']),1);
			if($patient_dblock_bin==$center_dblock_bin){
				$centers[$sql->row['CENTER']]['OVERRIDED_EQUAL']++;
			}
		}
	}
	$template->assign("centri",$centers);
}





//HOW TO
/** Per utilizzare questa funzione chiamarla cosi nel codice:
 * $this->testo("PAROLACHIAVE")
 * e qui dentro definire per ogni lingua
 * $this->testi['PAROLACHIAVE']="Frase da far apparire";
 */
$testi = array();
if(!isset($testi[$testo])){
	if(strtolower($xml->configuration->lang)=='en') {
		$testi['center'] = "Center ID";
		$testi['principal_password'] = "Password of the Principal activated";
		$testi['center_name'] = "Center Name";
		$testi['principal_investigator'] = "Principal Investigator";
		$testi['how_to_use'] = "Select the option to enable/disable the functionality for a center";
		$testi['lock'] = "Freeze entire site";
		$testi['lock_patients'] = "Freeze entire patient";
		$testi['go_to_patients']="Freeze per patient";
		$testi['go_to_visits']="Freeze per visit";
	} elseif(strtolower($xml->configuration->lang)=='it') {
		$testi['center'] = "Numero";
		$testi['principal_password'] = "Password del Principal Attivata";
		$testi['center_name'] = "Nome del centro";
		$testi['principal_investigator'] = "Principal Investigator";
		$testi['how_to_use'] = "Selezione l'opzione per disabilitare una funzione ad un centro";
		$testi['hint'] = "disabilita tutti i pazienti del centro";
		$testi['lock_patients'] = "Disabilita tutte le visite del paziente";
		$testi['go_to_patients']="Disabilita i pazienti singolarmente";
		$testi['go_to_visits']="Disabilita le visite del paziente singolarmente";
	}
}
$template->assign("testi",$testi);

/*function error_page($user, $error, $error_spec){
 global $filetxt;
global $in;
global $SRV;
global $log_conn;
global $service;
global $remote_userid;
global $session_number;

include_once "libs/ErrorPage.v2.inc";
$ErrorPage=new error_page();
$ErrorPage->print_error_page($filetxt, $error, $error_spec);
}*/





$template->allow_php_tag = true;
// 	$template->debugging = true;
$template->display(basename(__FILE__, ".php").".tpl");
?>


