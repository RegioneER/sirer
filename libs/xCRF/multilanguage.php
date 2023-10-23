<?php 

include_once "AxmrML.class.inc";
include_once "db.inc";

global $mltab;
$mltab = "ML_SERVICE";

//
//CREATE TABLE PT_I18N
//(
//  LANG   VARCHAR2(4 BYTE),
//  LABEL  VARCHAR2(4000 BYTE),
//  TEXT   VARCHAR2(4000 BYTE)
//)
//LOGGING 
//NOCOMPRESS 
//NOCACHE
//NOPARALLEL
//MONITORING;
//
//
//CREATE UNIQUE INDEX PK_PT_I18N ON PT_I18N
//(LANG, LABEL)
//LOGGING
//NOPARALLEL;
//
//
//ALTER TABLE PT_I18N ADD (
//  CONSTRAINT PK_PT_I18N
// PRIMARY KEY
// (LANG, LABEL));
//

function ml_init_global($study_prefix) {
	global $ml;
	$conn=new dbconn();
	$prefix = $study_prefix;
	$lang = getLanguage();
    //die("ENTRO QUA?");
	$ml = new axmr_ml($prefix,$lang,$conn, array());
}

function getLanguage(){
	if (!isset($_SESSION['language'])){
		$_SESSION['language'] = "IT";
	}
	//$_SESSION['language'] = "EN";
	$lang = $_SESSION['language'];
	return $lang;
}

function t($string){
	global $mltab;
	$retval = $string;
	$lang = getLanguage();
	$prefix = "ACM";
	$conn=new dbconn();
	//print_r($_SERVER);
	$GLOBALS['dir'] = $_SERVER['DOCUMENT_ROOT']."".$_SERVER['SCRIPT_URL'] ;//SCRIPT_URI
	$ml = new axmr_ml($prefix,$lang,$conn, array());
	//print_r($ml);
	if ($string){
		
		/*
		$bind = array();
		$bind['STRING'] = $string;
		$row = db_nextrow(db_query_bind("SELECT * FROM {$mltab} WHERE EN=:STRING ",$bind));
		if (!$row){
			$nextid = db_getmaxdbvalue($mltab, "ID");
			$nextid = common_nextId($nextid,1);
			$bind['NEXTID'] = $nextid;
			if (db_query_update_bind("INSERT INTO {$mltab}(ID,EN,LAST_USED) VALUES(:NEXTID, :STRING, SYSDATE) ",$bind)){
				//Tutto ok
			}else{
				//Qualcosa non va
				//die("MORTO?");
			}
		}
		if ($row && isset($row[$lang]) && $row[$lang]){
			$retval = $row[$lang];
		}
		db_query_update_bind("UPDATE {$mltab} SET LAST_USED = SYSDATE WHERE EN=:STRING ",$bind);
		*/
		
		//AXMRML Method
		$string=trim($string);
		//$defaultValue=trim($defaultValue);
		return $ml->out($string); //, $defaultValue);
		
	}
	unset($ml); //Free object
	$conn->closeConnection(); //Close DB Connection
	return $retval;
}

function error_page($user, $error, $error_spec){
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;
	
	echo $error;
	echo $error_spec;
	//TODO: sistemare link a ErrorPage 
	include_once "ErrorPage.v2.inc";
	$ErrorPage=new error_page();
	$ErrorPage->cineca_user ="v.mazzeo@cineca.it";
	$ErrorPage->hd_pierrelgroup="";
	$ErrorPage->send_error_page($filetxt,$in,$SRV,$log_conn,$service,$remote_userid,$session_number,$user, $error, $error_spec);
	$ErrorPage->print_error_page($filetxt, $error, $error_spec);
}


?>