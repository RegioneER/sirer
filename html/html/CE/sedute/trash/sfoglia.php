<?

include_once "config.inc";

$xml_dir="/http/servizi/AIFA_WF/trasparenza/html/procuratori/xml";
$template_dir="/http/servizi/AIFA_WF/trasparenza/html/procuratori";
$percorso="";
$original_value="";
$email_admin="cosulenza.v@cineca.it";
$root=$_SERVER['DOCUMENT_ROOT'];
$dir=$_SERVER['PATH_TRANSLATED'];
$dir=preg_replace("/\/sfoglia.php/", "", $dir);
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
$jscript="<script type=\"text/javascript\" >
	function add_value(nome,descrizione,nomeform) {
		if (!nomeform){nomeform='0'}
		chiamante=window.parent.opener.document.forms[nomeform];
		elementi_chiamante=chiamante.elements;
		 if (elementi_chiamante[descrizione]){
		  	elementi_chiamante[descrizione].value=nome;
		  	if(window.parent && window.parent.opener && window.parent.opener.cf)window.parent.opener.cf();
		  return 0;
		}
	}
</script>";

if (isset($list)){


	$body="$percorso<br/><br/>";
	$list_o= new xml_list($xml_dir.'/'.$list,$in['PAGE'],$in['RPP']);
	$body.="<p class=titolo>{$list_o->list['TITOLO']}</p>";
	$body.="<table width=\"400px\"><tr><td>";
	$body.=$list_o->list_html();
	$body.="</td></tr></table>";
	$filetxt = file_get_contents($template_dir.'/template.htm');
	
	$filetxt=preg_replace("/<!--script-->/", $jscript, $filetxt);
	$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	$filetxt=preg_replace("/index.php/", $in['script'], $filetxt);

}
elseif (isset($actnum)){

	$filetxt = file_get_contents($template_dir.'/naviga_bio.htm');
	$filetxt=preg_replace("/<!--actnum-->/", $actnum, $filetxt);
	
	$in['list']=$list='sfoglia_naz.xml';
	$in['script']='sfoglia.php';
	$in['tipo']='naviga';
	$in['PAGE']=1;
	$in['source']='CODPAT';
	$in['dest']='CODPAT';
	$body="$percorso<br/><br/>";
	$script='';
	$onload='';
	$list_o= new xml_list($xml_dir.'/'.$list,$in['PAGE'],$in['RPP']);
	$body.="<p class=titolo>{$list_o->list['TITOLO']}</p>";
	$body.=$list_o->list_html();
	$filetxt = file_get_contents($template_dir.'/template_sfoglia.htm');
	$filetxt=preg_replace("/<!--script-->/", $jscript, $filetxt);
	$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	$filetxt=preg_replace("/index.php/", $in['script'], $filetxt);
}
echo $filetxt;
?>