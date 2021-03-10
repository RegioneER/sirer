<?

include_once "uxmr/libs/db_wl.inc";

$conn = new dbconn ();


$query['CODE1']="select 
	distinct 
	CODE1,
	CODE2, 
	DECODE1,
	DECODE2
	from UKCRC
	where CODE2=1";
$query['CODE2']="select 
	distinct 
	CODE1,
	CODE2, 
	DECODE1,
	DECODE2
	from UKCRC";


if ($_GET['L']==1){
	$sqlQuery=$query['CODE1'];
	$sqlQuery .=" and UPPER(DECODE1) like '%".strtoupper($_GET['term'])."%' order by DECODE1";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODE1'];
		$res[$i]['title']=$sql->row['DECODE1'];	
		$i++;
	}
	if ($i>0)
	die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}


if ($_GET['L']==2){
	$sqlQuery=$query['CODE2'];
	$l1=explode("###",$_GET['L1']);
	$sqlQuery .=" where UPPER(DECODE2) like '%".strtoupper($_GET['term'])."%' ";
    if(isset($l1[0]) && $l1[0]!="" ) {
        $sqlQuery .= "and CODE1='" . $l1[0] . "' ";
    }
    $sqlQuery .=" order by DECODE2";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODE2'];
		$res[$i]['title']=$sql->row['DECODE2'];
		$i++;
	}
	if ($i>0)
		die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}
	
	
	
?>