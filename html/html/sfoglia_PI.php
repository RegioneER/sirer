<?


function error_page($a, $b, $c){
    print_r($a);
    print_r($b);
    print_r($c);
}


include_once "../libs/xCRF/db.inc";

$conn = new dbconn ();

//TOSCANA-185
$query['CODE']="select CF as CODE, NOME || ' ' || COGNOME as DECODE from ANA_PI";

if ($_GET['L1']){
    $L1 = urldecode($_GET['L1']);
    if (stristr($L1,"###")!==false){
        $strCode = explode("###",$L1)[0];
        if (is_numeric($strCode)){
            $query['CODE'].=" where ID_AZIENDA = '{$strCode}' ";
        }
    }
}
//var_dump($query['CODE']);

if (isset($_GET['term']) && $_GET['term']!=""){
    $sqlQuery=$query['CODE'];
    if (stristr($sqlQuery,"where")!==false){
        $sqlQuery.=" and ";
    }else{
        $sqlQuery.=" where ";
    }
    $sqlQuery .=" UPPER(NOME || ' ' || COGNOME) like '%".strtoupper($_GET['term'])."%' and ABILITATO=1";
    $sql=new query($conn);
    $sql->exec($sqlQuery);
    $i=0;

    while ($sql->get_row()){
        $res[$i]['id']=$sql->row['CODE']."###".$sql->row['DECODE'];;
        $res[$i]['title']=$sql->row['DECODE'];
        $i++;
    }
    if ($i>0)
        die(json_encode($res));
    else die("[{\"id\":\"-9999\",\"title\":\"Nessun risultato trovato\"}]");
}

?>