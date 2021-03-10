<?

include_once "lib/db_wl.inc";

$conn = new dbconn ( );

$query="select id,descrizione from ce_veneto.ce_doc_gen";

	$sql=new query($conn);
	$sql->exec($query);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['ID'];
		$res[$i]['title']=$sql->row['DESCRIZIONE'];	
		$i++;
	}
	if ($i>0)	die(json_encode($res));
	//else die("[{\"id\":\"-9999\",\"title\":\"Non disponibile\"}]");

function error_page($a, $b, $c){
print_r($a);
print_r($b);
print_r($c);
}

?>
