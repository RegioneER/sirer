<?

include_once "../libs/xCRF/db.inc";

$conn = new dbconn ( );

$thread=strtoupper($_GET['term']);
$bind_array['TERMINE']=$thread;

$query="select * from DISPOSITIVI_MEDICI where progressivo_dm_ass=:TERMINE ";

$sql=new query($conn);
$sql->exec($query, $bind_array);
$i=0;
while ($sql->get_row()){
    $res[$i]=$sql->row;
    $i++;
}
if ($i>0)	die(json_encode($res));
else die("[{\"sstatus\":\"KO\"}]");

function error_page($a, $b, $c){
    print_r($a);
    print_r($b);
    print_r($c);
}

?>
