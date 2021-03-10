<?

include_once "../libs/xCRF/db.inc";

$conn = new dbconn ( );

$thread="%".strtoupper($_GET['term'])."%";
$bind_array['TERMINE']=$thread;
$query="select PROGRESSIVO_DM_ASS,DENOMINAZIONE_COMMERCIALE,FABBRICANTE_ASSEMBLATORE from DM where UPPER(DENOMINAZIONE_COMMERCIALE) like :TERMINE ";
if($_GET['id']){
    $bind_array['PROGRESSIVO_DM_ASS']=$_GET['id'];
    $query.=" and PROGRESSIVO_DM_ASS=:PROGRESSIVO_DM_ASS";
}

	$sql=new query($conn);
	$sql->exec($query, $bind_array);
	$i=0;
	while ($sql->get_row()){
		$res[$i]['id']=$sql->row['PROGRESSIVO_DM_ASS']."###".str_replace(array("*","\\",",","(",")"),array(" "," "," "," "," "),$sql->row['DENOMINAZIONE_COMMERCIALE']);
		$res[$i]['title']=$sql->row['DENOMINAZIONE_COMMERCIALE'];
		$res[$i]['fabbricante']=str_replace(array("*","\\",",","(",")"),array(" "," "," "," "," "),$sql->row['FABBRICANTE_ASSEMBLATORE']);
		$i++;
	}
	if ($i>0)	die(json_encode($res));
	else die("[{\"id\":\"-9999###Non disponibile\",\"title\":\"Non disponibile\",\"fabbricante\":\"Non disponibile\"}]");

function error_page($a, $b, $c){
print_r($a);
print_r($b);
print_r($c);
}

?>
