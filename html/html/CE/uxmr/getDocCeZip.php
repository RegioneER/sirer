<?php 

include_once "config.inc";
include_once "study.inc.php";


//LUIGI FACCIO PARTIRE DB,WF E CONTROLLER (controllo chi può fare cosa)
$xmr = new xmrwf ( "study.xml", $conn );


$sub_service=str_replace($xmr->dir, "", $dir);
$sub_service=rtrim($sub_service, "/");
$sub_service=ltrim($sub_service, "/");
$xml_dir="$dir/xml";

if ($sub_service!=''){	
	foreach ($xmr->substudies as $key => $val){
		if ($val->prefix==$sub_service) $xmr=$val;				
		$xml_dir=str_replace("$sub_service/xml", "xml/$sub_service", $xml_dir);			
	}	
}


$xmr->setConfigParam();
$user=new user($conn, $in['remote_userid'], $xmr);

$config_service['filetxt']=$filetxt;

if (class_exists("Study_{$xmr->prefix}")){
	$class_name="Study_".$xmr->prefix;
}
else $class_name="Study";
$study_=new $class_name($xml_dir, $service, "visite_exams.xml", $conn, $in, $config_service, $user,false, $config_service['WF_NAME'], $xmr);
$study_->Controller();


//PREPARO IL DOWNLOAD SICURO
function enforceSaferDownload($wantedDir,$finalFile){
	$wantedDir=realpath($wantedDir);
	$finalFile=realpath($finalFile);
	$pos=strpos($finalFile,$wantedDir);
	if($pos===FALSE){
		echo "Bad Request!";
		die();
		return false;
	}
	else {
		return true;
	}
}

if (isset($_GET['ID_STUD']) ){

//LUIGI CALCOLO I DOCUMENTI PER IL CORRETTO ID_STUD	
	$sql_studi="select c.doc_core, d.ext, d.nome_file, c.userid_ins, c.d_doc_gen, c.doc_vers, to_char(c.doc_dt,'DD/MM/YYYY') as doc_dt, c.descr_agg from ce_documentazione c, docs d where c.id_stud=:ID_STUD and d.id=c.doc_core";
	$query_studi = new query ( $conn );
	$bindsup['ID_STUD']=$_GET['ID_STUD'];
	$query_studi->exec($sql_studi, $bindsup);
	//var_dump($query_studi);
	//die();

if ($query_studi->numrows!=0) {
	//LUIGI CREO IL FILE ZIP RINOMINANDO IL CONTENUTO	
	$zip = new ZipArchive();
	$filename = "./WCA/docs/zipGen_{$bindsup['ID_STUD']}.zip";

	if ($zip->open($filename, ZipArchive::CREATE)!==TRUE) {
    exit("cannot open <$filename>\n");
	}
	
	while ($query_studi->get_row()){
		$zip->addFile("./WCA/docs/Doc_Area".$query_studi->row['DOC_CORE'].".".$query_studi->row['EXT'] , $query_studi->row['NOME_FILE']);
		print("./WCA/docs/Doc_Area".$query_studi->row['DOC_CORE'].".".$query_studi->row['EXT']);
		print ("<br>");
		print($query_studi->row['NOME_FILE']);
		print ("<br>");
		print ("<br>");
	}
	
	$zip->close();
	
	echo $filename;
	
		$wantedDir="./WCA/docs/";
		$dir=$filename;
		$nome_file="zipGen_{$bindsup['ID_STUD']}.zip";

		enforceSaferDownload($wantedDir,$dir);

	//LUIGI SCARICO IL FILE
	header("Content-type:application/zip;\n");
	header("Content-Transfer-Encoding: Binary");
	header("Content-Disposition: attachment; filename=".$nome_file);

	ob_clean();
	ob_end_flush();
	readfile($dir);

	exit;
		
	} else {
		echo "<font size=\"5px\">File zip non generato! <br> Non è stato inserito nessun file nella documentazione generale";
		echo "<br><br> <a href=\"#\" onclick=\"history.back()\">&lt;&lt;Torna alle schede dello studio</a></font>";
	}

}

else error_page('BAD request','BAD request');
	
	
?>