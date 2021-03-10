<?

include_once "../libs/xCRF/db.inc";

$conn = new dbconn ( );

$thread=strtoupper($_GET['term']);
if ($_GET ['SPECIALITA'] != '' || $_GET ['AIC'] != '' || $_GET ['TIT_AIC'] != '' || $_GET ['PRINC_ATT'] != '') {
    if ($_GET ['SPECIALITA'] != '') {
        $pattern = $_GET ['SPECIALITA'];
        $pattern = str_replace("'", "''", $pattern);
        $pattern = strtoupper($pattern);
        $sql_where [count($sql_where)] = "upper(specialita) like '%$pattern%'";
    }
    if ($_GET ['AIC'] != '') {
        $pattern = $_GET ['AIC'];
        $pattern = str_replace("'", "''", $pattern);
        $pattern = strtoupper($pattern);
        $sql_where [count($sql_where)] = "upper(aic_spec) like '%$pattern%'";
    }
    if ($_GET ['TIT_AIC'] != '') {
        $pattern = $_GET ['TIT_AIC'];
        $pattern = str_replace("'", "''", $pattern);
        $pattern = strtoupper($pattern);
        $sql_where [count($sql_where)] = "upper(ditta) like '%$pattern%'";
    }
    if ($_GET ['PRINC_ATT'] != '') {
        $pattern = $_GET ['PRINC_ATT'];
        $pattern = str_replace("'", "''", $pattern);
        $pattern = strtoupper($pattern);
        $sql_where [count($sql_where)] = "upper(dsost) like '%$pattern%'";
    }
    $sql_where_clause = "";
    foreach ($sql_where as $key => $val) {
        if ($sql_where_clause != '') $sql_where_clause .= " and ";
        $sql_where_clause .= $val;
    }
    $sql_where_clause = "where " . $sql_where_clause;

    $query = "select   minsan10 as aic_minsan,
                       specialita as spec_specialita,
                    atc,
                    ditta,
                    dsost,
                    aic_conf,
                    sostanza
      from farmaci_sfoglia
     $sql_where_clause ";

    //$query="select * from DISPOSITIVI_MEDICI where progressivo_dm_ass=:TERMINE ";

    $sql = new query($conn);
    $sql->exec($query, $bind_array);
    $i = 0;
    while ($sql->get_row()) {
        $res[$i] = $sql->row;
        $i++;
    }
    if ($i > 0) die(json_encode($res));
    else die("[{\"sstatus\":\"KO\"}]");
}

function error_page($a, $b, $c){
    print_r($a);
    print_r($b);
    print_r($c);
}

?>
