<?php

include_once "sedute/libs/db.inc";

error_reporting(E_ERROR);

ini_set('display_errors', 1);


$conn = new dbconn ( );

$sql=new query($conn); 
$sql2=new query($conn); 


//var_dump( $_POST );
 
$sql_query="select f.id as CODE, f.file_name||' ('||m.tipodocumento||')' as DECODE 
from doc_obj_file f, doc_obj d, DOC_EME_MASTER_V m 
where d.id = m.ALLEGATOEME_ID 
and d.file_id=f.id
and m.emendamento_id=:EME_ID"; 
$bind = array();
$bind['ID']=$_POST['id'];
$bind['EME_ID']=$_POST['eme_id'];
$sql->exec($sql_query, $bind);

$sql_query2="select *
from doc_viewobj_parereeme
where id = :ID";

$sql2->get_row($sql_query2, $bind);

//echo "<pre>";
//var_dump($sql2->row['ID']);
//echo "</pre>";



//echo $sql2->row['PCE_DOCUMENTAZIONE_C'];
$save=array();
$save=explode("|",$sql2->row['PCE_DOCUMENTAZIONE_C']);
//echo "<pre>";
//var_dump($save);
//echo "</pre>";


while ($sql->get_row()){
	$checked="";
	if (in_array($sql->row['CODE'], $save)){
		$checked="checked";
	}
	//echo "fwnfklnwfkw";
	echo "<span class=\"col-sm-9 x-checkbox-input x-field-ParereEme_documentazione\">
			<div class=\"checkbox\">
                <label>
                    <input autocomplete=\"off\" class=\"ace\" id=\"ParereEme_documentazione_{$sql->row['CODE']}\" name=\"ParereEme_documentazione\" value=\"{$sql->row['CODE']}###{$sql->row['DECODE']}\" title=\"{$sql->row['DECODE']}\" type=\"checkbox\" {$checked}><span class=\"lbl\">{$sql->row['DECODE']}</span>
					</input>
                </label>
            </div>
		</span>
	<br>";

}





function error_page($user, $error, $error_spec){
		global $filetxt;
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		global $session_number;
		$eol=PHP_EOL;
		//die("POLLO!");
		$email_admin="g.contino@cineca.it, l.pazzi@cineca.it, l.verri@cineca.it, a.ramenghi@cineca.it";
		if($error_spec==''){
			$error_spec=ocierror($conn);
		}
		
		#echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
		$today = date("j/m/Y, H:m:S");
		$ajax=isset($in['ajax_call'])?"Si":"No";
		if (is_array($error_spec)){
			foreach ($error_spec as $key => $val){
				$spec.="\n $key : $val";
			}
		}else{
			$spec = $error_spec;
		}
		//$debug_info_str = "<br>".$debug_info_str;
		//$debug_info_str = preg_replace("[\n]","<br>",$debug_info_str);
		//$debug_info_str = preg_replace("/array/i","<b>Array:</b>",$debug_info_str);
		//$debug_info_str = preg_replace("/([0-9]) =>/","<b> \\1 => </b>",$debug_info_str);
		
		$alltxt =
			"* Data: $today
			* Errore: $error
			
			* Session Number:$session_number IP richiesta: {$_SERVER['REMOTE_ADDR']}
			* URL richiesta: {$_SERVER['REQUEST_URI']}
			* Servizio: $service
			* Specifiche errore: $spec
			* Chiamata ajax: $ajax
			* var export (_SERVER): $debug
			*DEBUG INFO: ".$debug_info_str;
		
		$headers  = "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}$eol";
		// $headers .= "Content-type: text/html\r\n";
		$headers .= "Content-type: text/plain; charset=utf-8$eol";
		// $debug_info=nl2br(var_export( debug_backtrace(), TRUE ) );
		$prod="";
		if(preg_match("/\.agenziafarmaco\./", $_SERVER['HTTP_HOST'])){
			if(preg_match("/too large/i",$spec)) {
				$edo=substr($spec,strpos($spec,"value too large for column")+28,strlen($spec));
				$edo=substr($edo,0,strpos($edo,"(actual:"));
				$edo=substr($edo,strrpos($edo,".")+1);
				$body="<h2 style=\"color:red;\">Valore troppo grande per il campo: ".$edo."</h2>";
			}
			$body.="<h3>Errore del sistema. Contattare il supporto tecnico.</h3>$debug_info";
			$prod="_!PRODUZIONE!";
		} else {
			//print_r($error_spec);
			$debug = debug_backtrace();
			//  foreach($debug as $key => $val) {
			//   foreach($val  as $k => $v) {
			//    $debug_info.=$k." ".$v."<br />";
			//   }
			//  }
			$body="<h2>ERRORE DEVEL</h2><h3>$error</h3><br />$debug_info";
			//  print_r($debug[0]);
			//  $debug_info=var_export($debug,true);
		}
		mail($email_admin, "Errore[".$in['remote_userid']."]$prod",$alltxt, $headers);
		$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
		die($filetxt);

	}
?>