<?

include_once "uxmr/libs/db_wl.inc";

$conn = new dbconn ();


$query['CODE1']="select 
	distinct 
	CODE1,
	CODE2, 
	CODE,
	CODE_POINT, 
	DECODE 
	from ICD9CM_ITA
	where CODE2 is null";
$query['CODE2']="select 
	distinct 
	CODE1,
	CODE2, 
	CODE, 
	CODE_POINT, 
	DECODE 
	from ICD9CM_ITA";


if ($_GET['L']==1){
	$sqlQuery=$query['CODE1'];
	$sqlQuery .=" and UPPER(DECODE) like '%".strtoupper($_GET['term'])."%' order by DECODE";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODE1'];
		$res[$i]['title']=$sql->row['DECODE'];	
		$i++;
	}
	if ($i>0)
	die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}


if ($_GET['L']==2){
	$sqlQuery=$query['CODE2'];
	$l1=explode("###",$_GET['L1']);
	$sqlQuery .=" where UPPER(DECODE) like '%".strtoupper($_GET['term'])."%' ";
	if(isset($l1[0]) && $l1[0]!="" ){
        $sqlQuery .=" and  CODE1='".$l1[0]."'";
    }
    $sqlQuery .=" order by DECODE";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODE2'];
		$res[$i]['title']=$sql->row['DECODE'];
		$i++;
	}
	if ($i>0)
		die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}
	
	
	
?>