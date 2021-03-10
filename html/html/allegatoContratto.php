<?

include_once "acm/db.inc";
$conn = new dbconn ( );


$codiceArray=str_split("###",$_POST['codice']);
$codice=$_GET['codice'];//$codiceArray[0];

if($codice!=5){

$sqlQuery ="select *
  from doc_obj_md_val
 where 
 code=".$codice." and 
 md_id in
       (select id
          from doc_obj_md
         where element_id in (select d.id
                                from doc_obj d, doc_type t
                               where d.type_id = t.id
                                 and t.type_name = 'AllegatoContratto'
                                 and d.parent_id = '".strtoupper($_POST['parentId'])."'))";
         
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$i++;
	}
	if ($i>0) die("ATTENZIONE!\n\n Il documento che si sta tentando di inserire e' gia' presente in questo contratto.");
	//die(json_encode($res));
	//else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");
}
function error_page($a, $b, $c){
    print_r($a);
    print_r($b);
    print_r($c);
}

?>