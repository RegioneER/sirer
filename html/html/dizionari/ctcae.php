<?
function error_page($a, $b, $c){
    print_r($a);
    print_r($b);
    print_r($c);
}

include("../uxmr/libs/db_wl.inc");


$conn = new dbconn ( );

$query['1']="select 
	distinct 
	
	soc_code as CODICE, 
	soc as DECODIFICA 
	from ctcae";
$query['2']="select 
	distinct 
	code as codice, 
	term as DECODIFICA
	from ctcae where ";

if($_GET['term']!=""){//STSANPRJS-586 se cerco da DM con term non uso il filtro, lo uso se cerco da interfaccia utente
    $query['1'].=" where upper(soc) like upper(:term)";

    $query['2'].="  upper(term) like upper(:term)";

    $addFilterQuery1=" upper(grade1) like upper(:term) ";
    $addFilterQuery2=" upper(grade2) like upper(:term) ";
    $addFilterQuery3=" upper(grade3) like upper(:term) ";
    $addFilterQuery4=" upper(grade4) like upper(:term) ";
    $addFilterQuery5=" upper(grade5) like upper(:term) ";
}
else{
    $query['2'].=" soc_code=:filter";

    $addFilterQuery1=" code=:filter ";
    $addFilterQuery2=" code=:filter ";
    $addFilterQuery3=" code=:filter ";
    $addFilterQuery4=" code=:filter ";
    $addFilterQuery5=" code=:filter ";
}
$query['3']="select distinct * from (
	select 
		 
		1 codice,
		'(1) '||grade1 decodifica
		from ctcae where grade1 != '-'
		and  {$addFilterQuery1}
	union	
	select 
		 
		2 codice,
		'(2) '||grade2 decodifica
		from ctcae where grade2 != '-'
		and {$addFilterQuery2}
	union	
	select 
		 
		3 codice,
		'(3) '||grade3 decodifica
		from ctcae where grade3 != '-'
		and {$addFilterQuery3}
	union	
	select 
		 
		4 codice,
		'(4) '||grade4 decodifica
		from ctcae where grade4 != '-'
		and {$addFilterQuery4}
	union	
	select 
		 
		5 codice,
		'(5) '||grade5 decodifica
		from ctcae where grade5 != '-'
		and  {$addFilterQuery5}
		)
		";

$sqlQuery=$query[$_GET['L']];
$filter=explode("###",$_GET['filter']);
unset($bind);
if($_GET['L']>1){
    $bind['filter']=$filter[0];
}
if($_GET['term']!="") {
    $bind["term"] = '%'.$_GET['term'].'%';
}

$sql=new query($conn);
$sql->exec($sqlQuery,$bind);
//var_dump($sqlQuery);
$i=0;
while ($sql->get_row()){
    $res[$i]['id']=$sql->row['CODICE'];
    $res[$i]['title']=$sql->row['DECODIFICA'];
    $i++;
}
if ($i>0)
    die(json_encode($res));
else die("[{\"id\":\"-1\",\"title\":\"Non applicabile\"}]");





?>
