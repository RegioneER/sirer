<?php

function error_page($a, $b, $c){
    print_r($a);
    print_r($b);
    print_r($c);
}

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

include_once "../libs/xCRF/db.inc";

$conn = new dbconn ();

$sql_studi="select DEPOTFARMACOBARCODE_ID from BARCODE_MASTER_V where DEPOTFARMACO_ID=:DEPOTFARMACO_ID and SCARICATO='0'";
$bindsup['DEPOTFARMACO_ID']=$_GET['DEPOTFARMACO_ID'];
$query_studi = new query ( $conn );
$query_studi->exec($sql_studi, $bindsup);
$i=0;
while ($query_studi->get_row()){
    $res[$i]['ID']=$query_studi->row['DEPOTFARMACOBARCODE_ID'];
    $i++;
}
if ($i>0)
    die(json_encode($res));
else
    $res['KO']['ID']="Nessun Barcode Disponibile";
die(json_encode($res));

?>