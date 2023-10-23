<?php 
require_once "libs/http_lib.inc";
include_once "libs/db.inc";
include_once "libs/xml_parser_wl.inc";
include_once "libs/HTML_Parser.inc";
include_once "libs/page.inc";
include_once "libs/vlist.inc";
include_once "libs/list.inc";
include_once "libs/legend.inc";
include_once "libs/esams_list.inc";
include_once "libs/form.inc";
include_once "libs/study_prototype.inc";
include_once "libs/xmrwf.inc.php";
include_once "libs/integrazioni.inc";

function SubjidExist($xml_form){
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
		$sql_subjid_tmp="select count(*) as CONTO from {$service}_REGISTRATION t where CENTER={$in['CENTER']} and SUBJID={$in['SUBJID']} ";
		$sql2_tmp->set_sql($sql_subjid_tmp);
		$sql2_tmp->exec();
		while($sql2_tmp->get_row()){
//			print($sql2_tmp->row['CONTO']."<hr />");
			if($sql2_tmp->row['CONTO']==2){
				echo "Error:#error#";
				die($alert_exist);
			}
		}
		
		/**
		 * ePRO:
		 */
		
		$pass=GeneratePassword(8,1);
		
		while(CheckPasswordExist($pass)==true){
			$pass=GeneratePassword(8,1);
		}
		UpdatePatPassword($xml_form,$pass);
	}
	
}


/**
 * ePRO:
 */
function UpdatePatPassword($xml_form,$password){
		global $conn;
		global $in;
		global $service;

		if($in['PROGR']==''){$in['PROGR']=1;}
		if($in['ESAM']==''){$in['ESAM']=0;}
		if($in['VISITNUM']==''){$in['VISITNUM']=0;}
		
		$sql_insert="update {$service}_REGISTRATION set PASSWORD='{$password}' where visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and  visitnum_progr={$in['VISITNUM_PROGR']} and progr={$in['PROGR']} and codpat={$in['CODPAT']}  ";
		$sql=new query($conn);
		$sql->set_sql($sql_insert);
		$sql->ins_upd();
		$conn->commit();		
}

function CheckPasswordExist($password){
		global $conn;
		global $in;
		global $service;
		
		$sql=new query($conn);
		$sql_passwd_exist="select count(*) as PASSWDEXIST from {$service}_REGISTRATION t where PASSWORD='{$password}' ";
		$sql->set_sql($sql_passwd_exist);
		$sql->exec();
		if($sql->get_row()){
//			print($sql->row['PASSWDEXIST']."<hr />");
			if($sql->row['PASSWDEXIST']>0){
				return true;
			}
		}
		return false;
}

function GeneratePassword($length,$level){

   list($usec, $sec) = explode(' ', microtime());
   srand((float) $sec + ((float) $usec * 100000));

   $validchars[1] = "0123456789";
   $validchars[2] = "0123456789abcdfghjkmnpqrstvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   $validchars[3] = "0123456789_!@#$%&*()-=+/abcdfghjkmnpqrstvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_!@#$%&*()-=+/";

   $password  = "";
   $counter   = 0;

   while ($counter < $length) {
     $actChar = substr($validchars[$level], rand(0, strlen($validchars[$level])-1), 1);

     // All character must be different
     if (!strstr($password, $actChar)) {
        $password .= $actChar;
        $counter++;
     }
   }

   return $password;

}
/**
 * fine ePRO
 */



?>