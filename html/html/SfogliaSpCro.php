<?
include_once "../libs/xCRF/db.inc";

$conn = new dbconn ( );

$thread="%".strtoupper($_GET['term'])."%";
$bind_array['TERMINE']=$thread;

header('Content-Type: application/json');

if ($thread!='' && isset($_SESSION['SfogliaSpCro'][$thread])) die(json_encode($_SESSION['SfogliaSpCro'][$thread]));
elseif (isset($_SESSION['SfogliaSpCro']['all'])) die(json_encode($_SESSION['SfogliaSpCro']['all']));

$query="select * from CE_ELENCO_PROMOTORI_CRO where UPPER(denominazione) like :TERMINE ";

	$sql=new query($conn);
	$sql->exec($query, $bind_array);
	$i=0;
	while ($sql->get_row()){
		//$res[$i]['id']=$sql->row['ID']."###".$sql->row['ID'];
		$res[$i]['id']=$sql->row['ID']."###".$sql->row['DENOMINAZIONE'];
		$res[$i]['title']=str_replace(array("(",")"),array("",""),$sql->row['DENOMINAZIONE']);
		$i++;
	}
	if ($i>0)	die(json_encode($res));
	else die("[{\"id\":\"-9999###Non disponibile\",\"title\":\"Non disponibile\"}]");

	if ($thread!='') $_SESSION['SfogliaSpCro'][$thread]=$res;
	else $_SESSION['SfogliaSpCro']['all']=$res;

	
function error_page($a, $b, $c){
	print_r($a);
	print_r($b);
	print_r($c);
}

?> 
