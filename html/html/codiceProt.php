<?

//error_reporting(E_ALL);
include_once "../libs/xCRF/db.inc";

$conn = new dbconn ( );


$sqlQuery ="select * from DOC_OBJ_MD_VIEW where field_name='CodiceProt'
  			 and UPPER(txt_value) = '".strtoupper($_POST['codice'])."'";
	$sql=new query($conn);
	$sql->exec($sqlQuery);
	$i=0;
	while ($sql->get_row()){
		$i++;
	}
	if ($i>0) die("ATTENZIONE!\n\n Il codice protocollo che si sta tentando di inserire e' gia' associato ad un altro studio in banca dati.\nConfermi la creazione dello studio?");
	//die(json_encode($res));
	//else die("[{\"id\":\"-9999\",\"title\":\"Non applicabile\"}]");


?>
