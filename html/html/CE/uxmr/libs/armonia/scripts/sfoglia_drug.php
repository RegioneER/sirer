<?
/*function error_page($user, $error, $error_spec){
global $filetxt;
global $in;
global $SRV;
global $log_conn;
global $service;
global $remote_userid;
global $session_number;
#echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
$val=debug_backtrace();
$text="PHP Debug:".var_export($val,true)."fine PHP Debug";
$today = date("j/m/Y, H:m:s");
if (is_array($error_spec)) foreach ($error_spec as $key => $val) $spec.="\n $key : $val";
mail("g.delsignore@cineca.it,g.stabile@cineca.it,a.colabufalo@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n.$text");
$body="<p align=center><font size=4><b>Si è verificato un errore</b></p><br><br>$error_spec<br>$error<hr>";
$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
die($filetxt);
}*/
putenv("NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1");
//require_once "libs/http_lib.inc";
include_once "config.inc";
/*include_once "libs/db.inc";
include_once "libs/xml_form.inc";
include_once "libs/xml_field.inc";
include_once "libs/xml_parser.inc";
include_once "libs/xml_page.inc";*/
$xml_dir="/http/www/aieop/html/xmr_studies/GCCB/xml";
$template_dir="/http/www/aieop/html/xmr_studies/GCCB";
$percorso="";
$original_value="";
$email_admin="g.delsignore@cineca.it";
$root=$_SERVER['DOCUMENT_ROOT'];
$dir=$_SERVER['PATH_TRANSLATED'];
$dir=preg_replace("/\/sfoglia_drug.php/", "", $dir);
$xml_dir=$dir."/xml";
$log_conn=new dbconn();
$q_log=new query($log_conn);
$log_conn=new dbconn();
$q_log=new query($log_conn);
$sql="select max(id) as ID from sessions";
$q_log->set_sql($sql);
$q_log->exec();
$q_log->get_row();
$session_number=$q_log->row['ID']+1;
#echo "<hr>".$session_number."<hr>";
$sql="insert into sessions(id, userid, data) values($session_number, '".$remote_userid."', sysdate)";
$q_log->set_sql($sql);
$q_log->ins_upd();
$log_conn->commit();
$conn=new dbconn();
$template_dir=$dir;

if(!isset($list)){
	$in['list']=$list='sfoglia_drug.xml';
}

if (isset($list)){
	$in['scrip']='sfoglia_drug.php';
	$in['tipo']='naviga';
	$in['page']=1;
	//$in['source']='CODPAT';
	//$in['dest']='CODPAT';
	$body="$percorso<br/><br/>";
	$script='';
	$onload='';
	$list_o= new xml_list($xml_dir.'/'.$list);
	$body.="<p class=titolo>{$list_o->list['TITOLO']}</p>";
	$body.=$list_o->list_html();
	$filetxt = file_get_contents($template_dir.'/template_sfoglia.htm');
	$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);


}
//elseif (isset($actnum)){
//
//	$filetxt = file_get_contents($template_dir.'/naviga_bio.htm');
//	$filetxt=preg_replace("/<!--actnum-->/", $actnum, $filetxt);
//	
//	$in['list']=$list='sfoglia_bio.xml';
//	$in['scrip']='sfoglia.php';
//	$in['tipo']='naviga';
//	$in['page']=1;
//	$in['source']='CODPAT';
//	$in['dest']='CODPAT';
//	$body="$percorso<br/><br/>";
//	$script='';
//	$onload='';
//	$list_o= new xml_list($xml_dir.'/'.$list);
//	$body.="<p class=titolo>{$list_o->list['TITOLO']}</p>";
//	$body.=$list_o->list_html();
//	$filetxt = file_get_contents($template_dir.'/template_sfoglia.htm');
//	$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
//
//}
echo $filetxt;
?>