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

global $mlcache;
$mlcache = array();

global $mlconn;
$mlconn = false;

function t($string){
	global $mltab;
    global $mlcache;
    global $mlconn;
	if (!isset($_SESSION['language'])){
		$_SESSION['language'] = "IT";
	}
	//$_SESSION['language'] = "IT";
	$lang = $_SESSION['language'];
	$retval = $string;
    if ($mlcache[$lang][$string]){
        $retval = $mlcache[$lang][$string];
    }else{
        $prefix = "ACM";
        if (!$mlconn){
            $mlconn=new dbconn();
        }
        //print_r($_SERVER);
        $GLOBALS['dir'] = $_SERVER['DOCUMENT_ROOT']."".$_SERVER['SCRIPT_URL'] ;//SCRIPT_URI
        $ml = new axmr_ml($prefix,$lang,$mlconn);
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
            $retval = $ml->out($string); //, $defaultValue);
            $mlcache[$lang][$string] = $retval;
        }
        unset($ml); //Free object
        //$mlconn->closeConnection(); //Close DB Connection
    }
    //ritorno cmq la stringa
    return $retval;
}

function mlConnClose(){
    global $mlconn;
    if ($mlconn){
        $mlconn->closeConnection(); //Close DB Connection
    }

}
function error_page($user, $error, $error_spec){
    global $filetxt;
    global $in;
    global $SRV;
    global $log_conn;
    global $service;
    global $remote_userid;
    global $session_number;
	
	/*VMAZZEO FIX ERROR_PAGE SU RICHIESTA AJAX SAVE/SEND 06.10.2014*/
	if($_POST['ajax_call']=='yes'){
		echo json_encode ( array (
				"sstatus" => "ko",
				"user" => $user,
				"error" => $error,
				"detail" => "Database ERROR: <br/>Code: ".$error_spec['code']."<br/>Message: ".$error_spec['message']
		) );
		die ();
	}
	else{
	    #echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
	    $today = date("j/m/Y, H:m:s");
	    Logger::trace('error');
	    if (is_array($error_spec)) foreach ($error_spec as $key => $val) $spec.="\n $key : $val";
	    mail("v.mazzeo@cineca.it, dario.mengoli@gmail.com", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n");
	    $body="<p align=center><font size=4><b>An error occurred</b></p><br><br>";
	    $filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	    global $study_;
        $btrace = debug_backtrace();
        $stackstr = print_r($btrace,true);
	    //do_render($study_, "<div class=\"alert alert-danger\"><i class=\"icon-remove\"></i><strong>Error: </strong>".$error."</div><pre>{$stackstr}</pre>");
		echo "<pre>";
	    die(print_r(array("d.saraceno@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n","stacktrace:".$stackstr),1));
    } 
}


?>
