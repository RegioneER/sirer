<?
if(!function_exists("error_page")){
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
	    mail("v.mazzeo@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n");
	    $body="<p align=center><font size=4><b>An error occurred</b></p><br><br>";
	    $filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	    global $study_;
        $btrace = debug_backtrace();
        $stackstr = print_r($btrace,true);
	    //do_render($study_, "<div class=\"alert alert-danger\"><i class=\"icon-remove\"></i><strong>Error: </strong>".$error."</div><pre>{$stackstr}</pre>");
		echo "<pre>";
	    die(print_r(array("v.mazzeo@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n","stacktrace:".$stackstr),1));
    } 
}
	
}
ini_set('display_errors','1');
error_reporting(E_ERROR|E_PARSE);
include_once "acm/db.inc";
$conn = new dbconn ( );

//HDCRPMS-630 CONTROLLO ESISTENZA CENTRO AGGANCIATO CON :idStud
$sqlQuery ="SELECT count(*) as CONTO
FROM ce_info_studio info,ce_centrilocali cl
WHERE info.id_stud=cl.id_stud and (info.id_stud =:idStud  AND cl.centro=:id_str AND  cl.unita_op=:id_uo AND cl.princ_inv=:id_pi)";

$sql=new query($conn);
$bindVars['idStud']=$_POST['id'];
$bindVars['id_str']=$_POST['id_str'];
$bindVars['id_uo']=$_POST['id_uo'];
$bindVars['id_pi']=$_POST['id_pi'];
//var_dump($sqlQuery);
//var_dump($bindVars);
$sql->exec($sqlQuery, $bindVars);
$idArray= array();
$sql->get_row();
if($sql->row['CONTO']>0) {
    if ($_POST['ajax_call'] == 'yes') {
        $error= json_encode(array(
            "sstatus" => "ko",
            "error" => "ATTENZIONE!",
            "detail" => "IL CENTRO E' GIA' PRESENTE IN CE, CONTATTARE LA SEGRETERIA E FARE ESEGUIRE LA PROCEDURA DI INVIO DAL CE AL CRMS"
        ));
        die ($error);
    }

}

$sqlQuery ="select * from ce_info_studio where id_stud =:idStud";
$sql=new query($conn);
$bindVars=array();
$bindVars['idStud']=$_POST['id'];
$sql->exec($sqlQuery, $bindVars);
$idArray= array();
$sql->get_row();
$i=0;
$idArray[$i]['code']=$sql->row['ID_STUD'];
$idArray[$i]['decode']="ID:".$sql->row['ID_STUD']." (Codice: ".$sql->row['CODICE_PROT'].")";
if($sql->row['ID_STUD']) die(json_encode($idArray));


//HDCRPMS-630 CONTROLLO ESISTENZA CENTRO AGGANCIATO CON :eudract
$sqlQuery ="SELECT count(*) as CONTO
FROM ce_info_studio info,ce_centrilocali cl
WHERE info.id_stud=cl.id_stud and (info.eudract_num =:eudract  AND cl.centro=:id_str AND  cl.unita_op=:id_uo AND cl.princ_inv=:id_pi)";

$sql=new query($conn);
$bindVars['eudract']=$_POST['eudract'];
$bindVars['id_str']=$_POST['id_str'];
$bindVars['id_uo']=$_POST['id_uo'];
$bindVars['id_pi']=$_POST['id_pi'];
//var_dump($sqlQuery);
//var_dump($bindVars);
$sql->exec($sqlQuery, $bindVars);
$idArray= array();
$sql->get_row();
if($sql->row['CONTO']>0) {
    if ($_POST['ajax_call'] == 'yes') {
        $error= json_encode(array(
            "sstatus" => "ko",
            "error" => "ATTENZIONE!",
            "detail" => "IL CENTRO E' GIA' PRESENTE IN CE, CONTATTARE LA SEGRETERIA E FARE ESEGUIRE LA PROCEDURA DI INVIO DAL CE AL CRMS"
        ));
        die ($error);
    }

}
//if($_POST['eudract']!=""){
	$sqlQuery ="select * from ce_info_studio where eudract_num =:eudract"; //and crpms_studio_progr is null
	$bindVars=array();
    $bindVars['eudract']=$_POST['eudract'];
	$sql->exec($sqlQuery, $bindVars);
	$i=0;
	$eudractArray= array();
	while ($sql->get_row()){
		//array_push($eudractArray,$sql->row['EUDRACT_NUM']);
		$eudractArray[$i]['code']=$sql->row['ID_STUD'];
		$eudractArray[$i]['decode']="EudarCT number:".$sql->row['EUDRACT_NUM']." (Codice: ".$sql->row['CODICE_PROT'].")";
		$i++;
	}
	if ($i>0) die(json_encode($eudractArray));
	//else if($_POST['codice']!=""){
	else{
        $i=0;
		$codiceArray= array();
		$codiceArray[$i]['code']="0";
		$codiceArray[$i]['decode']="Crea nuovo studio in CE-Toscana";
		if($_POST['codice']!=""){
            //HDCRPMS-630 CONTROLLO ESISTENZA CENTRO AGGANCIATO CON :codice
            /*$sqlQuery ="SELECT count(*) as CONTO
FROM ce_info_studio info,ce_centrilocali cl
WHERE info.id_stud=cl.id_stud and (upper(info.codice_prot) like upper('%'||:codice||'%') AND cl.centro=:id_str AND  cl.unita_op=:id_uo AND cl.princ_inv=:id_pi)";

            $sql=new query($conn);
            $bindVars['codice']=$_POST['codice'];
            $bindVars['id_str']=$_POST['id_str'];
            $bindVars['id_uo']=$_POST['id_uo'];
            $bindVars['id_pi']=$_POST['id_pi'];
//var_dump($sqlQuery);
//var_dump($bindVars);
            $sql->exec($sqlQuery, $bindVars);
            $idArray= array();
            $sql->get_row();
            if($sql->row['CONTO']>0) {
                if ($_POST['ajax_call'] == 'yes') {
                    $error= json_encode(array(
                        "sstatus" => "ko",
                        "error" => "ATTENZIONE!",
                        "detail" => "IL CENTRO E' GIA' PRESENTE IN CE, CONTATTARE LA SEGRETERIA E FARE ESEGUIRE LA PROCEDURA DI INVIO DAL CE AL CRMS"
                    ));
                    die ($error);
                }

            }*/
			$sqlQuery ="select * from ce_info_studio where upper(codice_prot) like upper('%'||:codice||'%')";
            $bindVars=array();
			$bindVars['codice']=strtoupper($_POST['codice']);
			$sql->exec($sqlQuery, $bindVars);
			while ($sql->get_row()){
				$i++;
				$codiceArray[$i]['code']=$sql->row['ID_STUD'];
				$codiceArray[$i]['decode']="Codice: ".$sql->row['CODICE_PROT']." (ID: ".$sql->row['ID_STUD'].")";
			}
		}
		die(json_encode($codiceArray));
		//else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
	}

?>