<?

include_once "lib/db_wl.inc";

$conn = new dbconn ( );

$query="select id_sed,to_char(data_sed_dt,'DD/MM/YYYY') data_sed_dt from gse_registrazione where data_sed_dt>sysdate order by data_sed_dt";

	$sql=new query($conn);
	$sql->exec($query);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['ID_SED'];
		$res[$i]['title']=$sql->row['DATA_SED_DT'];	
		$i++;
	}
	if ($i>0)	die(json_encode($res));
	else die("[{\"id\":\"-9999\",\"title\":\"Non disponibile\"}]");

function error_page($a, $b, $c){
print_r($a);
print_r($b);
print_r($c);
}

?>
