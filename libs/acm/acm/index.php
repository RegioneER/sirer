<?php
//Force https
if (!$_SERVER['HTTPS'] && $_SERVER['PORT']!="443"){
	$url = "https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
	header('Location: '.$url);
}

ini_set('display_errors','1');
error_reporting(E_ERROR|E_PARSE);
include_once "../layout/layoutLibs/NavBar.class.php";
include_once "../layout/layoutLibs/NavBarItem.class.php";
include_once "../layout/layoutLibs/Link.class.php";
include_once "../layout/layoutLibs/LinkedEvent.class.php";
include_once "../layout/layoutLibs/BreadCrumb.class.php";
include_once "../layout/layoutLibs/SideBar.class.php";
include_once "../layout/layoutLibs/SideBarItem.class.php";


//Inizializzo framework di gestione chiamate e pagine
include_once "menu.php";
limonade_init();
//Controlla utenze
$bind['USERID']=$_SERVER['REMOTE_USER'];
$rs = db_query_bind("SELECT count(*) as C FROM UTENTI_VISTEAMMIN u WHERE u.USERID= :USERID ",$bind);
$present=false;
while ($row1 = db_nextrow($rs)){
	if ($row1['C']>0){
        $present=true;
	}
}
if ($present){
    //Fai partire limonade
    run();
    //Chiudi connessione Multilanguage
    mlConnClose();
}else {
    //Utente non abilitato
    header('HTTP/1.0 403 Forbidden');
    echo 'User cannot access this area';
}

die();

//die($output);

?>
