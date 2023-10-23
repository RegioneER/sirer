<?
/**
 * Classe error_page
 * Classe per la gestione degli errori e relativi desitnatari
 * @package XMR Hyperlibs
 *
 */
class error_page{


	function __construct(){
		$this->cineca_user ="v.mazzeo@cineca.it,dario.mengoli@gmail.com";
		$this->hd_pierrelgroup="l.verri@cineca.it";
	}
	
	function send_error_page($filetxt,$in,$SRV,$log_conn,$service,$remote_userid,$session_number,$user, $error, $error_spec){
        $spec=null;
		if ($error == "Attention this visit is closed, it's not possible to modify/insert data" ||
			$error == "Attenzione la visita risulta chiusa, non &egrave; quindi possibile inserire/modificare i dati") {
			return;
		}		
// 		if(preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])){
// 			//"Sviluppo";
// 			$mailto=$this->cineca_user;
// 		}elseif(preg_match("/\.test\./i",$_SERVER['HTTP_HOST'])){
// 			//"Preproduzione";
// 			$mailto=$this->cineca_user." , ".$this->hd_pierrelgroup;
// 		}else{
// 			//"Produzione";
// 			// Eventuale altro recapito:
// 			$xml = simplexml_load_file("xml/error_page.xml");
// 			$other_mailto = $xml->mailto;
// 			$mailto.=$other_mailto;
			
// 			$mailto=$this->cineca_user." , ".$this->hd_pierrelgroup." , l.verri@cineca.it,s.scalise@cineca.it";
// 		}
		
		$mailto=$this->cineca_user." , ".$this->hd_pierrelgroup." , l.verri@cineca.it";
		
		$today = date("j/m/Y, H:m:s");
		$url_from=$_SERVER['HTTP_REFERER'];
		if($_GET['list']!=''){
			$url_from="https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
		}
		
		$headers  = "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\n";
		$headers .= "Content-type: text/html; charset=utf-8 \n";
		if (is_array($error_spec)) foreach ($error_spec as $key => $val){ $spec.="\n $key : $val";}
		//print($mailto);print($headers);echo "<hr>";
        //TODO: Uncomment mailing!!
		//mail("$mailto", "Errore[".$in['remote_userid']."]","$today <br><br> $error <br><br> <b>Specifiche errore:<b> <br>".$spec."<br><b> URL:<b> <br><a href='$url_from' target='_new'>".$url_from."</a>", "$headers");
        echo("Errore[".$in['remote_userid']."]"."<br/>"."$today <br><br> $error <br><br> <b>Specifiche errore:<b> <br>".$spec."<br><b> URL:<b> <br><a href='$url_from' target='_new'>".$url_from."</a><br/>");
        $dbg = debug_backtrace();
        foreach ($dbg as $k=>$v){
            echo "FILE: {$v['file']}:{$v['line']} in function {$v['function']}<br/>";
        }

    }

	function print_error_page($filetxt, $error, $error_spec) {
		if ($error == "Attention this visit is closed, it's not possible to modify/insert data" ||
			$error == "Attenzione la visita risulta chiusa, non &egrave; quindi possibile inserire/modificare i dati") {
			$body="<p align=center><font size=4><b>$error</b></p><br><br>$error_spec";
		} else {
			$body="<p align=center><font size=4><b>Attention , there was an error</b></p><br><br>$error_spec<br>$error";
		}
		$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
		$filetxt=preg_replace("/<!--utente-->/", "", $filetxt);
		$onload.=";\nif (document.forms[0]) document.forms[0].action='';";
		$filetxt=preg_replace("/\/\/<!--onload-->/", $onload, $filetxt);
		$filetxt=preg_replace("/<!--user_name-->/", "", $filetxt);
		die($filetxt);
	}
}


?>
