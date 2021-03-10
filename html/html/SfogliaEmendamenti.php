<?

include_once "lib/db_wl.inc";

$conn = new dbconn ( );

$query="select id_stud||'_'||visitnum_progr as id_eme, emend_code from ce_emendamenti where id_stud={$_GET['id_stud']}";

	$sql=new query($conn);
	$sql->exec($query);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['ID_EME'];
		$res[$i]['title']=$sql->row['EMEND_CODE'];	
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
