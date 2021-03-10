<?

include_once "../libs/xCRF/db.inc";

$conn = new dbconn ( );

$thread="%".strtoupper($_GET['term'])."%";
$bind_array['TERMINE']=$thread;

$query="select distinct sostanza,dsost from farmaci_sfoglia where UPPER(dsost) like :TERMINE ";

$sql=new query($conn);
$sql->exec($query, $bind_array);
$i=0;
while ($sql->get_row()){
    $res[$i]['id']=$sql->row['SOSTANZA']."###".$sql->row['DSOST'];
    $res[$i]['title']=$sql->row['DSOST'];
    $i++;
}
if ($i>0)	die(json_encode($res));
else die("[{\"id\":\"-9999###Non disponibile\",\"title\":\"Non disponibile\"}]");

function error_page($a, $b, $c){
    print_r($a);
    print_r($b);
    print_r($c);
}

?>
