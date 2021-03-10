<?

include_once "uxmr/libs/db_wl.inc";

$conn = new dbconn ();


$query['ID']="select 
	distinct 
	ID, 
	DESCRIZIONE
	from CE_ELENCO_CENTRILOC";
$query['ID2']="select 
	distinct 
	ID,
	ID2, 
	DESCRIZIONE,
	DESCRIZIONE2
	from CE_ELENCO_CENTRILOC";

$query['ID']="select 
	distinct 
	ID_AZIENDA AS ID, 
	DESCRIZIONE_AZIENDA AS DESCRIZIONE
	from ANA_STRUTTURE";
$query['ID2']="select 
	distinct 
	ID AS ID2,
	ID_AZIENDA AS ID, 
	DESCRIZIONE AS DESCRIZIONE2,
	DESCRIZIONE_AZIENDA AS DESCRIZIONE
	from ANA_STRUTTURE";
$query['ID3']="select 
	distinct 
	ID AS ID3,
	ID_STRUTTURA as ID2,
	ID_AZIENDA AS ID, 
	DESCRIZIONE AS DESCRIZIONE3
	from ANA_DIPARTIMENTI";
$query['ID4']="select 
	distinct 
	ID AS ID4,
	ID_DIPARTIMENTO as ID3,
	ID_AZIENDA AS ID, 
	DESCRIZIONE AS DESCRIZIONE4
	from ANA_UO";


if ($_GET['L']==1){
    $sqlQuery=$query['ID'];
    //$sqlQuery .=" where UPPER(DESCRIZIONE) like '%".strtoupper($_GET['term'])."%' order by DESCRIZIONE";
    $sqlQuery .=" where UPPER(DESCRIZIONE_AZIENDA) like '%".strtoupper($_GET['term'])."%' order by DESCRIZIONE_AZIENDA";
    $sql=new query($conn);
    $sql->exec($sqlQuery);
    $i=0;
    while ($sql->get_row()){
        $res[$i]['id']=$sql->row['ID'];
        $res[$i]['title']=$sql->row['DESCRIZIONE'];
        $i++;
    }
    if ($i>0)
        die(json_encode($res));
    else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}


if ($_GET['L']==2){
    $sqlQuery=$query['ID2'];
    $l1=explode("###",$_GET['L1']);
    //$sqlQuery .=" where ID='".$l1[0]."' and  UPPER(DESCRIZIONE2) like '%".strtoupper($_GET['term'])."%' order by DESCRIZIONE2";
    $sqlQuery .=" where UPPER(DESCRIZIONE) like '%".strtoupper($_GET['term'])."%' ";
    if(isset($l1[0]) && $l1[0]!=""){
        $sqlQuery.=" and ID_AZIENDA='".$l1[0]."' ";
    }
    $sqlQuery .=" order by DESCRIZIONE";
    $sql=new query($conn);
    $sql->exec($sqlQuery);
    $i=0;
    while ($sql->get_row()){
        $res[$i]['id']=$sql->row['ID2'];
        $res[$i]['title']=$sql->row['DESCRIZIONE2'];
        $i++;
    }
    if ($i>0)
        die(json_encode($res));
    else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}

if ($_GET['L']==3){
    $sqlQuery=$query['ID3'];
    $l1=explode("###",$_GET['L1']);
    $l2=explode("###",$_GET['L2']);
    //$sqlQuery .=" where ID='".$l1[0]."' and  UPPER(DESCRIZIONE2) like '%".strtoupper($_GET['term'])."%' order by DESCRIZIONE2";
    $sqlQuery .=" where UPPER(DESCRIZIONE) like '%".strtoupper($_GET['term'])."%'";
    if(isset($l1[0]) && $l1[0]!="" && $l2[0] && $l2[0]!="" ){
        $sqlQuery.="and ID_AZIENDA='".$l1[0]."' and ID_STRUTTURA='".$l2[0]."' ";
    }
    $sqlQuery .=" order by DESCRIZIONE";
    //die($sqlQuery);
    $sql=new query($conn);
    $sql->exec($sqlQuery);
    $i=0;
    while ($sql->get_row()){
        $res[$i]['id']=$sql->row['ID3'];
        $res[$i]['title']=$sql->row['DESCRIZIONE3'];
        $i++;
    }
    if ($i>0)
        die(json_encode($res));
    else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}

if ($_GET['L']==4){
    $sqlQuery=$query['ID4'];
    $l1=explode("###",$_GET['L1']);
    $l2=explode("###",$_GET['L2']);
    $l3=explode("###",$_GET['L3']);
    //$sqlQuery .=" where ID='".$l1[0]."' and  UPPER(DESCRIZIONE2) like '%".strtoupper($_GET['term'])."%' order by DESCRIZIONE2";
    $sqlQuery .=" where UPPER(DESCRIZIONE) like '%".strtoupper($_GET['term'])."%' ";
    if(isset($l1[0]) && $l1[0]!=""  ){
        $sqlQuery.="and ID_AZIENDA='".$l1[0]."'  ";
    }
    $sqlQuery .=" order by DESCRIZIONE";






    //die($sqlQuery);
    $sql=new query($conn);
    $sql->exec($sqlQuery);
    $i=0;
    while ($sql->get_row()){
        $res[$i]['id']=$sql->row['ID4'];
        $res[$i]['title']=$sql->row['DESCRIZIONE4'];
        $i++;
    }
    if ($i>0)
        die(json_encode($res));
    else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}

?>