<?

function error_page($a, $b, $c){
print_r($a);
print_r($b);
print_r($c);
}

include_once "lib/db_wl.inc";


$conn = new dbconn ( );

$query['SOC']="select 
	distinct 
	'SOC' as LIVELLO_, 
	soc_code as CODICE, 
	soc_name as DECODIFICA 
	from md_hierarchy_91";
$query['HLGT']="select 
	distinct 
	soc_name as LIVELLO_SOC, 
	soc_code as COD_LIVELLO_SOC,
	'HLGT' as LIVELLO_, 
	HLGT_code as CODICE, 
	hlgt_name as DECODIFICA 
	from md_hierarchy_91";
$query['HLT']="select 
	distinct 
	hlgt_name as LIVELLO_HLGT, 
	hlgt_code as COD_LIVELLO_HLGT,
	'HLT' as LIVELLO_, 
	HLT_code as CODICE, 
	hlt_name as DECODIFICA 
	from md_hierarchy_91";
$query['PT']="select 
	distinct 
	hlt_name as LIVELLO_HLT,
	hlt_code as COD_LIVELLO_HLT,
	'PT' as LIVELLO_, 
	pt_code as CODICE, 
	pt_name as DECODIFICA 
	from md_hierarchy_91";
$query['LLT']="select 
	distinct 
	pt_name as LIVELLO_PT,
	pt_code as COD_LIVELLO_PT,
	'LLT' as LIVELLO_, 
	LLT_code as CODICE, 
	llt_name as DECODIFICA 
	from md_hierarchy_91";


if ($_GET['L']==1){
	$sqlQuery=$query['SOC'];
	$sqlQuery .=" where UPPER(soc_name) like '%".strtoupper($_GET['term'])."%' order by decodifica";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODICE'];
		$res[$i]['title']=$sql->row['DECODIFICA'];	
		$i++;
	}
	if ($i>0)
	die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}

if ($_GET['L']==2){
	$sqlQuery=$query['HLGT'];
	$l1=explode("###",$_GET['L1']);
	$sqlQuery .=" where soc_code='".$l1[0]."' and  UPPER(hlgt_name) like '%".strtoupper($_GET['term'])."%' order by decodifica";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODICE'];
		$res[$i]['title']=$sql->row['DECODIFICA'];
		$i++;
	}
	if ($i>0)
		die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}


if ($_GET['L']==3){
	$sqlQuery=$query['HLT'];
	$l2=explode("###",$_GET['L2']);
	
	$sqlQuery .=" where hlgt_code='".$l2[0]."' and  UPPER(hlt_name) like '%".strtoupper($_GET['term'])."%' order by decodifica";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODICE'];
		$res[$i]['title']=$sql->row['DECODIFICA'];
		$i++;
	}
	if ($i>0)
		die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}

if ($_GET['L']==4){
	$sqlQuery=$query['PT'];
	$l3=explode("###",$_GET['L3']);
	
	$sqlQuery .=" where hlt_code='".$l3[0]."' and  UPPER(pt_name) like '%".strtoupper($_GET['term'])."%' order by decodifica";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODICE'];
		$res[$i]['title']=$sql->row['DECODIFICA'];
		$i++;
	}
	if ($i>0)
		die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}

if ($_GET['L']==5){
	$sqlQuery=$query['LLT'];
	$l4=explode("###",$_GET['L4']);
	
	$sqlQuery .=" where pt_code='".$l4[0]."' and  UPPER(llt_name) like '%".strtoupper($_GET['term'])."%' order by decodifica";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['CODICE'];
		$res[$i]['title']=$sql->row['DECODIFICA'];
		$i++;
	}
	if ($i>0)
		die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}




?>
