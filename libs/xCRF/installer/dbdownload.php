<?php
ini_set('display_errors',1);
error_reporting(E_ERROR);
//error_reporting(E_ALL);
require_once("libs/http_lib.inc");
require_once("libs/file.inc");
require_once "libs/db.inc";
$cartella_servizio = str_replace("/dbdownload.php","",$_SERVER['SCRIPT_FILENAME']);
chdir($cartella_servizio);
$cartella = "estraz_file";
$conn = new dbconn();
$formatoData = "DD/MM/YYYY";
date_default_timezone_set('Europe/Rome');

ob_start();
//Creo le cartelle di esportazione
mkdir("$cartella",0775);
mkdir("$cartella/csv",0775);
mkdir("$cartella/txt",0775);
mkdir("$cartella/xls",0775);
//Recupero Prefisso servizio da tabella STUDIES
global $service;
$service = getCurrentServicePrefix($cartella_servizio);
//die($service);

if ($argv[1] == 'notturno') {
    estrazione_notturna();
} else {
    if ($_GET['realtime'] == 'yes') {
        estrazione_realtime($_GET['center']);
    } else {
        link_file();
    }
}

function getCurrentServicePrefix($cartella){
	global $conn;
	$query = new query($conn);
	unset($bind);
	$studystr = stristr($cartella,"/study/");
	$path = substr($studystr,strrpos($studystr,"/")+1);
	$bind['PATH'] = $path;
	$sql_auth = "select PREFIX from STUDIES where DESCR = :PATH";
	$query -> exec($sql_auth, $bind);
	$servizio = "";
	if($query -> get_row()) {
		$servizio = $query->row['PREFIX'];
	}
	return $servizio;
}
function getRemoteUser(){
	return ($_SERVER['REMOTE_USER']?$_SERVER['REMOTE_USER']:'00100001');
}

function getTipologiaUtente(){
	global $conn;
	global $service;
	$query = new query($conn);
	unset($bind);
	$bind['REMOTE_USERID'] = getRemoteUser();
	$sql_auth = "select distinct tipologia from {$service}_utenti_centri where userid = :remote_userid";
	$query -> exec($sql_auth, $bind);
	$tipologia = "";
	while($query -> get_row()){
		switch ($query -> row['TIPOLOGIA']){
			case "DM":
				if ($tipologia != "DE" )
				$tipologia = $query -> row['TIPOLOGIA'];
				break;
			case "RO":
				if ($tipologia != "DE"  && $tipologia != "DM"){
					$tipologia = $query -> row['TIPOLOGIA'];
				}
				break;
			case "DE":
				if (true){
					$tipologia = $query -> row['TIPOLOGIA'];
				}
				break;
		}
	}
	//die($tipologia);
	return $tipologia;
}

function estrazione_realtime($centerspec) {
	global $conn;
	global $service;
	$tipologia = getTipologiaUtente();
	//Controllo TIPOLOGIA
	if ($tipologia == 'DM') {
		$vis_nomecognome = false;
		genera_db($vis_nomecognome);
		link_file();
	} else if ($tipologia == 'RO') {
		$vis_nomecognome = false;
		genera_db($vis_nomecognome);
		link_file();
	} else if ($tipologia == 'DE') {
		$vis_nomecognome = true;
		unset($bind);
		$bind['REMOTE_USERID'] = getRemoteUser();
		$query_centro = new query($conn);
		$sql_auth_centro = "select center from {$service}_utenti_centri where userid = :remote_userid order by center asc";
		//echo $sql_auth_centro;
		//var_dump($bind);
		$query_centro -> exec($sql_auth_centro, $bind);
		$found = false;
		while ($query_centro -> get_row()) {
			if ($query_centro->row['CENTER']==$centerspec){
				$found=true;
				break;
			}
		}
		if ($found){
			genera_db($vis_nomecognome, $centerspec);
			link_file($centerspec);
		}else{
			die("CENTRO NON ACCESSIBILE");
		}
	} else {
		die("TIPOLOGIA UTENTE NON RICONOSCIUTA! ({$tipologia})");
	}
}

function link_file($centerspec=false) {
	global $conn, $service, $cartella, $cartella_servizio;
	$query = new query($conn);
	unset($bind);
	$bind['REMOTE_USERID'] = getRemoteUser();
	$sql_num = "select center from {$service}_utenti_centri where userid = :remote_userid";
	$query -> exec($sql_num, $bind);
	if ($centerspec){
		$found = false;
		while ($query -> get_row()) {
			if ($query->row['CENTER']==$centerspec){
				$found=true;
				break;
			}
		}
		if ($found){
			$centro = $centerspec;
		}
	}else{
		if ($query -> numrows == 1 && $query -> get_row()) {
			$centro = $query -> row['CENTER'];
		}
	}
	$tipologia = getTipologiaUtente();
	if ($tipologia == 'DM') {
		$vis_nomecognome = false;
	} else if ($tipologia == 'RO') {
		$vis_nomecognome = false;
	} else if ($tipologia == 'DE') {
		$vis_nomecognome = true;
	}
	echo $vis_nomecognome."<br/>";
	if ($vis_nomecognome){
		$n_nomecognome = "1";
	}else{
		$n_nomecognome = "2";
	}	
	$nomeFile = "estrazione-{$centro}-" . $n_nomecognome . ".zip";
	$fullPath = $cartella_servizio.'/'.$cartella.'/'.$nomeFile;
	echo $fullPath."<br/>";
	echo file_exists($fullPath);
	//die($nomeFile); 
	ob_clean();
	header("Pragma: public");
	header("Expires: 0");
	header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
	header('Content-Type: application/octet-stream');
	header("Content-Description: File Transfer");
	header("Content-Disposition: attachment; filename=\"estrazione-{$service}.zip\"");
	header("Accept-Ranges: bytes");
	header("Content-Length: ".filesize($fullPath));
	header("Content-Transfer-Encoding: binary");
	
	//$file=file_get_contents($cartella_servizio.'/'.$cartella.'/'.$nomeFile);
	//die($file);
	readfile($fullPath);
	die();
}

function estrazione_notturna() {
	global $conn;
	global $service;
	$query = new query($conn);
	$sql_centri = "select center from {$service}_centri";
	$query -> exec($sql_centri, $bind);
	while ($query -> get_row()) {
		genera_db(true, $query -> row['CENTER']);
	}
	genera_db(true); // si nome
	genera_db(false); // no nome
}

function genera_db($vis_nomecognome, $centro=false) {
	global $cartella, $cartella_servizio;
	chdir($cartella_servizio);
	if ($vis_nomecognome)
		$n_nomecognome = "1";
	else
		$n_nomecognome = "2";
	$nomeFile = "estrazione-{$centro}-" . $n_nomecognome . ".zip";
	echo $nomeFile."<br/>";
	$filetxt = new file('info.txt',$cartella);
	$filetxt->write("Generated on " . date(DATE_RFC822));	
	unset($q);
	echo $cartella_servizio."<br/>";
	echo $nomeFile."<br/>";
	echo $centro."<br/>";
	
	$qi = 0;
	//Recupero tutte le tabelle con [PREFIX]_[NOMETAB]
	global $service;
	global $conn;
	$tabquery = new query($conn);
	//$tabsql = "SELECT table_name FROM user_tables where table_name like '{$service}\_%' escape '\' ";
	//$tabsql = "SELECT distinct table_name FROM cols where table_name like '{$service}\_%' escape '\' and column_name in ('CODPAT','CENTER')";
	$tabsql = "SELECT distinct table_name FROM cols where table_name like '{$service}\_%' escape '\' and column_name = 'CODPAT' and table_name in 
(select distinct table_name FROM cols where table_name like '{$service}\_%' escape '\' and column_name = 'CENTER')";
	$tabquery->exec($tabsql);
	while ($tabquery->get_row()){
		$tabname = $tabquery->row['TABLE_NAME'];
		$q[$qi]['file'] = "{$qi}_{$tabname}";
		$q[$qi]['query'] = "select * from {$tabname}";
		$qi++;
	}
	
	unset($qq);
    $cont = 0;
    foreach ($q as $key => $value) {
        $qq[$cont]['file'] = $value['file'];
        $qq[$cont]['query'] = $value['query'] . ' order by center, codpat';
        $cont++;
    }
    var_dump($qq);
    
	foreach ($qq as $key => $value) {
		salva_csv($centro, filtraCentri($qq[$key]['query'],$centro), $qq[$key]['file'], $cartella);
		salva_txt($centro, filtraCentri($qq[$key]['query'],$centro), $qq[$key]['file'], $cartella);
		salva_xls($centro, filtraCentri($qq[$key]['query'],$centro), $qq[$key]['file'], $cartella);	
	}
	//die("ASD");
	comprimi($nomeFile, $cartella);
}

function filtraCentri($sql, $centro) {
	global $service;
	//return "select t.* from (".$sql.") t where t.center in (select center from {$service}_utenti_centri where userid = :userid)";
	$sqlcentro = "select t.* from (".$sql.") t";
	if ($centro){
		$sqlcentro .= " where t.center = {$centro}";
	}else{
		$sqlcentro .= " where t.center in (select center from {$service}_utenti_centri where userid = '".getRemoteUser()."')";
	}
	return $sqlcentro;
}

function salva_csv($centro, $query,$estrazione_file,$estrazione_dir, $estrazione_sep=';', $estrazione_ext = 'csv') {
	global $conn, $formatoData;
	unset($bind);
	//$bind['USERID'] = ($centro?$centro.'00001':($_SERVER['REMOTE_USER']?$_SERVER['REMOTE_USER']:'DMENGOLI'));
	$sql=new query($conn);
	$sql -> exec("alter session set nls_date_format = '{$formatoData}'");
	$sql->exec($query); //, $bind); //Estraggo i dati, niente bind x utente...
	//echo getcwd();
	//echo "<br/>".$estrazione_dir.'/csv'.$estrazione_file.'.'.$estrazione_ext."<br/>";
	$filecvs = new file($estrazione_file.'.'.$estrazione_ext,$estrazione_dir.'/csv');
	$filecvs->csv_line($sql->keys,$estrazione_sep);
	for ($i=0;$i<$sql->numrows;$i++){
		//echo "ROW $i";
		for ($k=0;$k<$sql->numcols;$k++){
			$filecvs->write(utf8_decode(('"' . $sql->res[$sql->keys[$k]][$i] . '"' . ((($k + 1) == $sql->numcols) ? '' : $estrazione_sep))));
		}
		$filecvs->write("\n");
	}
	$filecvs->close();
}

function salva_txt($centro, $query,$estrazione_file,$estrazione_dir, $estrazione_ext = 'txt') {
	global $conn, $formatoData;
	unset($bind);
	//$bind['USERID'] = ($centro?$centro.'00001':($_SERVER['REMOTE_USER']?$_SERVER['REMOTE_USER']:'DMENGOLI'));
	$sql=new query($conn);
	$sql -> exec("alter session set nls_date_format = '{$formatoData}'");
	$sql->exec($query); //, $bind);
	$filetxt = new file($estrazione_file.'.'.$estrazione_ext,$estrazione_dir.'/txt');
	for ($i = 0; $i < count($sql->keys);$i++) {
		$filetxt->write(str_pad($sql->keys[$i], $sql->size[$sql->keys[$i]]+3)."|");
	}
	$filetxt->write("\n");
	while($sql->get_row()) {
		for ($i = 0; $i < count($sql->row);$i++) {
			$testo = $sql->row[$sql->keys[$i]];
			$testo = str_replace ( chr(10), " ", $testo );
			$testo = str_replace ( chr(13), " ", $testo );
			$filetxt->write(str_pad($testo, $sql->size[$sql->keys[$i]]+3)."|");
		}
	$filetxt->write("\n");
	$filetxt->close();
	}
}

function salva_xls($centro, $query,$estrazione_file,$estrazione_dir, $estrazione_sep=',', $estrazione_ext = 'xlsx') {
    global $conn, $formatoData;
    require_once 'libs/PHPExcelLib/PHPExcel.php';
    $objPHPExcel = new PHPExcel();
    $objPHPExcel -> getProperties() -> setCreator("CINECA") -> setLastModifiedBy("CINECA") -> setTitle('Estrazione') -> setSubject('Estrazione') -> setDescription('Estrazione') -> setKeywords('Estrazione') -> setCategory("Estrazione");
    $objPHPExcel -> getSheet(0) -> setTitle(date("Y-m-d"));
    unset($bind);
    //$bind['USERID'] = ($centro?$centro.'00001':($_SERVER['REMOTE_USER']?$_SERVER['REMOTE_USER']:'DMENGOLI'));
    $sql=new query($conn);
    $sql -> exec("alter session set nls_date_format = '{$formatoData}'");
    $sql->exec($query); //, $bind);
    $contatoreColonna = 0;
    foreach ($sql->res as $colonna => $righe) {
        $codRiga = 1;
        $codColonna = convertiColonna(++$contatoreColonna);
        //echo "-->".$codColonna.$codRiga."<--<br/>";
        $objPHPExcel -> setActiveSheetIndex(0) -> setCellValue($codColonna . $codRiga, $colonna);
        foreach ($righe as $numriga => $valoreriga) {
            $codRiga++;
            $objPHPExcel -> setActiveSheetIndex(0) -> setCellValue($codColonna . $codRiga, $valoreriga);
        }
    }
    
    //$objWriterXLS = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
    // set default font
    $objPHPExcel->getDefaultStyle()->getFont()->setName('Calibri');
    $objPHPExcel->getDefaultStyle()->getFont()->setSize(8);
    $objWriterXLS = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
    $objWriterXLS -> save($estrazione_dir.'/xls/' . $estrazione_file.'.'.$estrazione_ext);
    /* $filexls = new file($estrazione_file.'.'.$estrazione_ext,$estrazione_dir.'/xls');
    $filexls->write(utf8_decode("<TABLE>"));
    $filexls->write(utf8_decode("<TR>"));
    for ($i=0;$i<$sql->numcols;$i++){
        $filexls->write(utf8_decode("<TD>"));
        $filexls->write(utf8_decode($sql->keys[$i]));
        $filexls->write(utf8_decode("</TD>"));          
    }
    $filexls->write(utf8_decode("</TR>"));
    for ($i=0;$i<$sql->numrows;$i++){
        $filexls->write(utf8_decode( "<TR>"));
        for ($k=0;$k<$sql->numcols;$k++) {
            $filexls->write(utf8_decode( "<TD>"));
            $filexls->write(utf8_decode( $sql->res[$sql->keys[$k]][$i]));
            $filexls->write(utf8_decode( "</TD>"));         
        }
        $filexls->write(utf8_decode( "</TR>"));
    }
    $filexls->write(utf8_decode( "</TABLE>"));
    *
    */
}

function convertiColonna($numero) {
	global $y;
	if (!isset($y) || !$y){
	    $y[0] = '';
	    for ($i = 1; $i <= 26; $i++) {
	        $y[] = creaLettera($i);
	    }
	    for ($ii = 1; $ii <= 26; $ii++) {
	        for ($ij = 1; $ij <= 26; $ij++) {
	            $y[] = creaLettera($ii) . creaLettera($ij);
	        }
	    }
	    for ($iii = 1; $iii <= 26; $iii++) {
	    	for ($iij = 1; $iij <= 26; $iij++) {
	    		for ($ijj = 1; $ijj <= 26; $ijj++) {
	    			$y[] = creaLettera($iii) . creaLettera($iij) . creaLettera($ijj);
	    		}
	    	}
	    }
	}
    return $y[$numero];
}

function creaLettera($i) {
    if ($i <= 26) {
        return chr($i + 64);
    }
}


function invia_email($from,$to,$bcc,$testo,$subject){
	$eol=PHP_EOL;
	$headers .= 'From: '.$from.''.$eol;
	$headers .= 'BCC: '.$bcc.''.$eol;
	$testo=preg_replace("/<(.*?)>/", "", $testo);
	mail($to, $subject, $testo, $headers);
}

function comprimi($nome_file, $compressione_dir) {
    exec("rm $compressione_dir/$nome_file");
	exec("cd $compressione_dir; zip -9 -r $nome_file txt xls csv info.txt listavariabili.xls listavariabili.pdf");
	exec("rm -f $compressione_dir/txt/*.txt");
	exec("rm -f $compressione_dir/xls/*.xlsx");
	exec("rm -f $compressione_dir/csv/*.csv");
	exec("rm -f $compressione_dir/info.txt");
    exec("chgrp devj $compressione_dir/$nome_file");
    exec("chmod ug+w $compressione_dir/$nome_file");
}

function error_page($user, $error, $error_spec) {
	$email = "geniussuite@cineca.it";
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;
	global $bind;
	global $config_service;
	$bind['global_remote_userid'] = getRemoteUser();
	$eol = PHP_EOL;
	$today = date("j/m/Y, H:m:s");
	$prefisso = "http" . ($_SERVER['SERVER_PORT'] == '443' ? 's' : '') . "://";
	// Dati generali
	$alltxt = "DATI GENERALI:\n* Data: {$today}\n* IP richiesta: {$_SERVER['REMOTE_ADDR']}\n* URL richiesta: {$prefisso}{$_SERVER['HTTP_HOST']}{$_SERVER['REQUEST_URI']}";
	$alltxt .= "\n* FORM: " . $_REQUEST['form'];
	$alltxt .= " - " . $config_service['PK_SERVICE'] . ": " . $_REQUEST[$config_service['PK_SERVICE']];
	// Specifiche errore
	if (is_array($error_spec))
		foreach ($error_spec as $key => $val)
			$spec .= "\n* $key : $val";
	else
		$spec = $error_spec;

	$alltxt .= "\n\nSPECIFICHE ERRORE:{$spec}";
	// Backtrace
	$alltxt .= "\n\nBACKTRACE:";
	$headers = "From: ERROR_" . $service . "@{$_SERVER['SERVER_NAME']}$eol";
	$headers .= "Content-type: text/plain; charset=utf-8$eol";
	$codice = debug_backtrace();
	foreach ($codice as $key => $val) {
		$alltxt .= "\n* $val[file]:$val[line] ($val[function])";
	}
	// Binding query
	$decode_bind = strtoupper(str_replace(":", "", $error));
	$decode_bind = str_replace("ERRORE QUERY", "In chiaro:", strtoupper($decode_bind));
	foreach ($bind as $key => $val) {
		$spec_bind .= " $key:$val";
		$decode_bind = str_replace(':' . strtoupper($key), "'{$val}'", $decode_bind);
	}
	$alltxt .= "\n\nBINDING QUERY:\n* {$error}\n* {$decode_bind}";
	mail($email, "Errore [" . getRemoteUser() . "]", $alltxt, $headers);
	$body = "<p align=center><img src=\"images/eq_img.png\"><br /><font size=4><b>Database Error: Sorry for the inconvenience.</b></p>
	<div style=\"text-align:center; color: red; padding: 15px;\">Technicians have been alerted.</div>
	<div style=\"background-color: #F9F9F9;
    color: #787878;
    font-size: 10px;
    padding: 40px;\">Error details<br /> " . str_replace('* ', '<br />', $spec) . "<br /><br />{$error}</div><br />";
	//$error
	$filetxt = preg_replace("/<!--body-->/", $body, $filetxt);
	$filetxt = str_replace("<title><!--user_name-->", "<title>" . getRemoteUser(), $filetxt);
	die($filetxt);
}

?>