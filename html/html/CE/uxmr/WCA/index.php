<?php

session_start();
$sid=session_id();
/**
 * Lettura variabili Post, Get e Server
 *
 */
include ("libs/http_lib.inc");
/**
 * File di configurazione dei parametri
 *
 */
include ("wom_config.inc");
/**
 * Core del sistema
 *
 */
require ("libs/new_core.inc");

/**
 * File di help
 *
 */
include ("wom_help_online.inc");
/**
 * Gestione calendario
 *
 */
require ("libs/calendar.inc");
/**
 * Connessione al DB
 *
 */
require ("libs/db_wl.inc");
//require ("libs/xml_form.inc");
//require ("libs/xml_field.inc");
//require ("libs/xml_parser_wl.inc");
//print_r($_SERVER);
//print_r($_POST);
//print_r($in);
//print_r($_FILES);
//die();
foreach ($in as $key => $val){
	${strtolower($key)}=$in[strtolower($key)]=$val;
}
$scriptname=$SRV['PHP_SELF'];
//


if ($in['KEYWORDS']=='ANNEX_CIRC9_FLOP') {
	global $testo_config;
	global $config_document;
	$testo_config['doc_ext_list']='.zip,';
	$config_document['doc_zip_ext_filter']=false;
}
/**
 * restituisce il valore del parametro passato
 *
 * @param string $value
 * @return string
 */

//foreach ($in as $key=> $val){
//	if ($val=='') {
//		unset($in[$key]);
//		unset ($$key);
//
//	}
//}

if ($in['ajax_call']=='') {
	//print_r($in);
	//print_r($_FILES);
	$_FILES['f_file']['name']=str_replace("à", "a'", $_FILES['f_file']['name']);
	$_FILES['f_file']['name']=str_replace("è", "e'", $_FILES['f_file']['name']);
	$_FILES['f_file']['name']=str_replace("ì", "i'", $_FILES['f_file']['name']);
	$_FILES['f_file']['name']=str_replace("ò", "o'", $_FILES['f_file']['name']);
	$_FILES['f_file']['name']=str_replace("ù", "u'", $_FILES['f_file']['name']);
	//die();
}
$html_str="
		<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">
		<html>
		<head>
		<!--refresh-->
		</head><body><!--body--></body></html>
";

#$conn=pg_connect("host=localhost dbname=pj_manager user=postgres password=postgres") or die("Errore connessione al db");

$conn=new dbconn();
$sql=new query($conn);
$user=new user_gest();
$Super_User=$user->IsSuperUser();
if (!$Super_User){
	unset($tabs[4]);
	unset($img_tabs[4]);
}


#echo "<hr>$sid<hr>";

foreach ($in as $key => $val){
	if (preg_match("/^sid_/", $key)){
		$sql_del_sid="delete from session_sid where userid='{$in['remote_userid']}' and sid='$sid'";
		$sql=new query($conn);
		$sql->set_sql($sql_del_sid);
		$sql->ins_upd();
		$conn->commit();
	}
}

foreach ($in as $key => $val){
	if (preg_match("/^sid_/", $key)){
		$nome_var=preg_replace("/^sid_/", "", $key);
		if ($nome_var!=''){
			$sql_ins_sid="insert into session_sid (userid, sid, nome_var, value) values('{$in['remote_userid']}', '$sid', '$nome_var', '$val')";
			$sql=new query($conn);
			$sql->set_sql($sql_ins_sid);
			$sql->ins_upd();
			$conn->commit();
		}
	}
}
$sql_query="select nome_var, value from session_sid where userid='{$in['remote_userid']}' and sid='$sid'";
$sql=new query($conn);
$sql->set_sql($sql_query);
$sql->exec();
while ($sql->get_row()) $in[strtoupper($sql->row['NOME_VAR'])]=$in[$sql->row['NOME_VAR']]=${$sql->row['NOME_VAR']}=${strtoupper($sql->row['NOME_VAR'])}=$sql->row['VALUE'];

//print_r($in);

$sql_query="
		select nome||' '||cognome as nome from ana_utenti where userid='{$in['remote_userid']}'
	";
$sql->set_sql($sql_query);
$sql->exec();
$sql->get_row();
$nome_user=$sql->row['NOME'];

$data=null;
$data=build_date('giorno', 'mese', 'anno');
$refresh=null;

if (isset($ical_make)){
	$riuns=new riunioni_gest();
	die ($riuns->make_ical_file());
}
/**
 * Utilità gestione slavataggio in db
 *
 */
include ("libs/db_utils.inc");

$html_str=file_get_contents("template.html");

$sql_query="select ug.userid,a.abilitato from users_group ug, ana_utenti_1 a, ana_utenti_1 a1 where ug.id_group = 28 and a.azienda_ente=a1.azienda_ente and a1.userid='{$in['remote_userid']}' and ug.userid=a.userid";
$sql->set_sql($sql_query);
$sql->exec();
$sql->get_row();
$userid_coord=$sql->row['USERID'];
//echo "<hr>$userid_coord<hr>";
if ($userid_coord==$in['remote_userid']){
$img_tabs[100]="btn_partner.gif";
$tabs[100]="Partner<br>Working Team";
}

if (isset($prj)){
	$riunioni=new riunioni_gest();
	$riunioni->make_array_color();
	if ($in['tab']=='') $tab=$in['tab']=0;
	$mese_str[1]=$testo_config['Calendario_Mese_Gennaio'];
	$mese_str[2]=$testo_config['Calendario_Mese_Febbraio'];
	$mese_str[3]=$testo_config['Calendario_Mese_Marzo'];
	$mese_str[4]=$testo_config['Calendario_Mese_Aprile'];
	$mese_str[5]=$testo_config['Calendario_Mese_Maggio'];
	$mese_str[6]=$testo_config['Calendario_Mese_Giugno'];
	$mese_str[7]=$testo_config['Calendario_Mese_Luglio'];
	$mese_str[8]=$testo_config['Calendario_Mese_Agosto'];
	$mese_str[9]=$testo_config['Calendario_Mese_Settembre'];
	$mese_str[10]=$testo_config['Calendario_Mese_Ottobre'];
	$mese_str[11]=$testo_config['Calendario_Mese_Novembre'];
	$mese_str[12]=$testo_config['Calendario_Mese_Dicembre'];
	$giorno_str[1]=txt('Calendario_Giorno_Corto_lun');
	$giorno_str[2]=txt('Calendario_Giorno_Corto_mar');
	$giorno_str[3]=txt('Calendario_Giorno_Corto_mer');
	$giorno_str[4]=txt('Calendario_Giorno_Corto_gio');
	$giorno_str[5]=txt('Calendario_Giorno_Corto_ven');
	$giorno_str[6]=txt('Calendario_Giorno_Corto_sab');
	$giorno_str[7]=txt('Calendario_Giorno_Corto_dom');
	$giorno_str_long[1]=txt('Calendario_Giorno_lun');
	$giorno_str_long[2]=txt('Calendario_Giorno_mar');
	$giorno_str_long[3]=txt('Calendario_Giorno_mer');
	$giorno_str_long[4]=txt('Calendario_Giorno_gio');
	$giorno_str_long[5]=txt('Calendario_Giorno_ven');
	$giorno_str_long[6]=txt('Calendario_Giorno_sab');
	$giorno_str_long[7]=txt('Calendario_Giorno_dom');
	$calendar=calendar($data, null, $array_color);
	//$content_body="";
	$data=build_date('giorno', 'mese', 'anno');
	$giorno="0".$data['mday'];
	$giorno=substr($giorno, strlen($giorno) -2,2);
	$mese="0".$data['mon'];
	$mese=substr($mese, strlen($mese) -2,2);
	$data_rif="<b>Data di riferimento: {$giorno}/{$mese}/{$data['year']}";
	$param='';
	foreach ($HTTP_GET_VARS as $key=>$val) {
		if ($param!='') $param.="&";
		$param.=$key."=".$val;
	}
	foreach ($HTTP_POST_VARS as $key=>$val) {
		if ($param!='') $param.="&";
		$param.=$key."=".$val;
	}
	$link_stampa='';
	if ($print_version=='') $link_stampa="<p align=right  style=\"background: url(images/button.gif) bottom repeat-x ;\"><a href='{$scriptname}?{$param}&print_version=yes' target='_new'>".txt('Link_stampa')."<img src='images/ico_stampa.gif' border=0></a></p>";
	if ($tab=='1' && !isset($id) && $action!='new_riunione') {
		$sql=new query($conn);
		$sql_query="select count(*) as conto from organizer where userid='{$in['remote_userid']}' and prj={$in['prj']}";
		$sql->set_sql($sql_query);
		$sql->exec();
		$sql->get_row();
		if ($sql->row['CONTO']>0 || !isset($config_calendar['Organizer'])) $link_stampa="<p align=right  style=\"background: url(images/button.gif) bottom repeat-x ;\"><input type='button' value='".txt('Calendario_Crea_Riunione')."' onclick=\"window.location.href='{$scriptname}?tab=1&action=new_riunione';\">&nbsp;&nbsp;<a href='{$scriptname}?{$param}&print_version=yes' target='_new'>".txt('Link_stampa')."<img src='images/ico_stampa.gif' border=0></a></p>";
		else $link_stampa="<p align=right  style=\"background: url(images/button.gif) bottom repeat-x ;\"><a href='{$scriptname}?{$param}&print_version=yes' target='_new'>".txt('Link_stampa')."<img src='images/ico_stampa.gif' border=0></a></p>";
	}
	if ($in['tab']==0){
		$docs=new doc_gest();
		$forums=new forum_gest();
		$meetings=new riunioni_gest();
		$mess_int_o=new mess_gest();
		if(isset($tabs[12]))
			$mess_int="
				<fieldset><legend class=mttl id=m_6_h>".txt('Messaggi_Last')."</legend>
				".$mess_int_o->list_mess()."
				<br><a href='{$scriptname}?tab=12'>Send new message</a>	
				<br><a href='{$scriptname}?tab=12'>".txt('MORE')."</a>
			  </fieldset>";
		if ($in['id_group']!=''){
			$content_body="$link_stampa
						".$docs->docs_area()."
						<br>".$forums->forum_list()."
						";

		}
		else 
		$content_body="<fieldset><legend class=mttl>My WCA Home</legend>
		$link_stampa
						<fieldset><legend class=mttl>".txt('Menu_principale_riunione')."</legend>	
							".$meetings->riunioni_prossime()."
							<a href='{$_GLOBALS['scriptname']}?tab=1&action=new_riunione'>Add new event</a>
							<br>
							<a href='{$scriptname}?tab=1'>".txt('MORE')."</a>
							</fieldset>
						<br>
						".$docs->docs_area_last()."
						<br>".$forums->forum_list_last()."
						<br>	".$mess_int."
							</fieldset>						
						";
	}

	if ($in['tab'] =='3'){
		$docs=new doc_gest();
		$usr_o=new user_gest();
		if(isset($_GET['download_all'])) {
			$docs->download_all($_GET['id_area']);
		}
		$Super_User=$usr_o->IsSuperUser();
		if (isset($_GET['DeleteIdDoc'])){
			$docs->delete_doc($_GET['DeleteIdDoc'], false);
			unset($_GET['DeleteIdDoc']);
		}
		if (isset($id_area) && $id_area!='') {
				
				if (isset($in['topic'])) 	$content_body=$docs->show_area_mini($id_area);
				else $content_body=$docs->show_area_mini($id_area).$down_all_link;
				if (isset($in['AF'])){
					$html_str=preg_replace("/<!--language-->/",$testo_config['language'], $html_str);
					$html_str=preg_replace("/<!--body-->/", $content_body, $html_str);
					$html_str=preg_replace("/<!--script-->/", $script, $html_str);
					$html_str=preg_replace("/<!--google_map-->/", $google_map, $html_str);
					$html_str=preg_replace("/\/\/<!--onload-->/", $onload, $html_str);
					die ($html_str);
			
			}
		}
		if (isset($id_doc) && $id_doc!='') $content_body=$docs->show_doc_mini($id_doc, 1);
		//if (isset($approv) && $approv!='' && !isset($doc_approv)) $content_body=$docs->intra_area_approv($approv);
		if (!isset($id_doc) && !isset($id_area)) $content_body=$docs->docs_area();
	}
	$query="select nome from prj where id=$prj";
	$sql->set_sql($query);
	$sql->exec();
	$sql->get_row();
	$prj_name=$sql->row['NOME'];
	$body="";
	$tabs_obj=new tab_gest();
	if($Super_User || $in['remote_userid']=='CONTINO')$Navigation_icon.=$tabs_obj->tab_gest_html($in['tab']);
	
}


$struttura_tabella[1][1]='1';
$struttura_tabella[1][2]='2';
$struttura_tabella[1][3]='3';
$struttura_tabella[2][4]='4';
$struttura_tabella[2][5]='5';
$struttura_tabella[2][6]='6';
//DATI UTENTE
$usr_o=new user_gest();
$m_1="<div id=\"m_1\">
				".$usr_o->user_detail_short()."
			  </div>";


$m_2="<div id=\"user_online\"></div>";


if ($in['id_group']!=''){
			$sql_query="select nome from wom_groups where id={$in['id_group']}";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();
			$sql->get_row();
			$content_body="<fieldset><legend class=mttl>".txt('group').": {$sql->row['NOME']}</legend>$content_body</fieldset>";
}


$m_5="<div id=\"m_5\" style=\"width:100%\">
	        $content_body<br>
	     </div>
	     ";
$mess_int_o=new mess_gest();

if ($tab!='12') $mess_int="
				<fieldset width='100%'><legend class=mttl id=m_6_h>".txt('Messaggi_Last')."</legend>
				".$mess_int_o->list_mess()."
			  </fieldset>";

//HELP


$tb_body="<tr>
			
			<td bgcolor='#E1ECFC' valign=top style='padding:4px'>
				$m_4<br>$m_5</td>
			</tr>
			";
$body.="
<table border=0 cellpadding=0 cellspacing=0 width=100% align=center style=\"background-color:$bgcolor;\">
$banner
<tr>
        <td valign=bottom><br>$Navigation_icon</td>
    </tr>
   </table> 
	<table border=0 id=t_1 cellpadding=0 cellspacing=2  width=100% align=center style=\"background-color:$bgcolor;\">
	$tb_body
	";
$body.="</table>";
$html_str=preg_replace("/<!--language-->/",$testo_config['language'], $html_str);
#if (isset($prj)) $body.="</fieldset></td></table>";
if (isset($view_user_details)){
	$usr_o=new user_gest();
	$body=$usr_o->user_details($view_user_details);
	$html_str=preg_replace("/<!--body-->/", $body, $html_str);
	$html_str=preg_replace("/<!--script-->/", $script, $html_str);
	$html_str=preg_replace("/<!--google_map-->/", $google_map, $html_str);
	$html_str=preg_replace("/\/\/<!--onload-->/", $onload, $html_str);
	$html_str=str_replace("ajax_call('user_online', 'useronline=yes');setInterval('ajax_call(\\'user_online\\', \\'useronline=yes\\')', 28000);","",$html_str);
	die ($html_str);
}
if (isset($view_users_list_tipo)){
	$usr_o=new user_gest();
	$body=$usr_o->user_list_tipo($view_users_list_tipo, $id_tipo_ref,false,false,true);
	$html_str=preg_replace("/<!--body-->/", $body, $html_str);
	$html_str=str_replace("ajax_call('user_online', 'useronline=yes');setInterval('ajax_call(\\'user_online\\', \\'useronline=yes\\')', 28000);","",$html_str);
	die ($html_str);
}
if (!isset($editor_doc) || $editor_doc==''){
	if (!isset($print_version)) {
		$html_str=preg_replace("/<!--body-->/", $body, $html_str);
		$html_str=preg_replace("/<!--refresh-->/", $refresh, $html_str);
		if ($tab==1 && ($action=='new_riunione' || $ID!='')) $google_map="<script src=\"http://maps.google.com/maps?file=api&amp;v=2.x&amp;key={$google_key}\" type=\"text/javascript\"></script>";
		$html_str=preg_replace("/<!--google_map-->/", $google_map, $html_str);
		$html_str=preg_replace("/<!--script-->/", $script, $html_str);
		$html_str=preg_replace("/\/\/<!--onload-->/", $onload, $html_str);
		echo $html_str;
	}
	else {
		$content_body=str_replace("ajax_call('user_online', 'useronline=yes');setInterval('ajax_call(\\'user_online\\', \\'useronline=yes\\')', 28000);","",$content_body);
		$content_body=str_replace("</fieldset>","</fieldset><!--NewPage-->", $content_body);
		$content_body=str_replace("display:none","", $content_body);
		$content_body=str_replace("doc.jpg","doc_1.gif", $content_body);
		$content_body=str_replace("folder_icon.gif","folder_icon_open.gif", $content_body);
		$content_body=str_replace("pdf.jpg","pdf.gif", $content_body);
		$content_body=str_replace("tree-node.gif","tree-node-open.gif", $content_body);
		$body="<table border=0 cellpadding=0 cellspacing=0 width=1024><tr><td><img src=\"images/intestazione_agenzia.png\"></td><td>{$m_1}</td></tr><tr><td colspan=2>$content_body</td></tr></table>";
		$html_str=preg_replace("/<!--body-->/", $body, $html_str);
		$html_str=preg_replace("/<!--refresh-->/", $refresh, $html_str);
		$google_map="<script src=\"http://maps.google.com/maps?file=api&amp;v=2.x&amp;key={$google_key}\" type=\"text/javascript\"></script>";
		$html_str=preg_replace("/<!--google_map-->/", $google_map, $html_str);
		$html_str=str_replace("style='display:'", "", $html_str);
		$html_str=preg_replace("/<!--script-->/", $script, $html_str);
		$html_str=preg_replace("/\/\/<!--onload-->/", $onload, $html_str);
		$search = array ("'<script[^>]*?>.*?</script>'si","'<input[^>]*?>'si");
		$replace = array ("","");
		$html_str = preg_replace($search, $replace, $html_str);
		$dir_html_pdf=$SRV['SCRIPT_FILENAME'];
		$dir_html_pdf=str_replace("{$SRV['PHP_SELF']}","",$dir_html_pdf);
		//die("<hr>$dir_html_pdf");
		$file_to_write="$dir_html_pdf/html_pdf/".strtolower($remote_userid).".html";
		$file=fopen($file_to_write, "w");
		$file=fwrite($file, $html_str);
		system("chmod g+w $dir_html_pdf/html_pdf/*");
		fclose($file);
		$html_str=file_get_contents("template.html");
		$http_html_pdf=str_replace("{$SRV['PHP_SELF']}","", $http);
		$http_html_pdf.="/html_pdf/";
		$refresh="<meta http-equiv=\"refresh\" content=\"0; url=html_pdf/html2pdf/demo/html2ps.php?process_mode=single&URL=$http_html_pdf/".strtolower($remote_userid).".html&batch%5B%5D=www.google.com&batch%5B%5D=www.altavista.com&batch%5B%5D=www.msn.com&proxy=&pixels=1024&scalepoints=1&renderimages=1&renderlinks=1&renderfields=1&media=Letter&cssmedia=screen&leftmargin=10&rightmargin=10&topmargin=15&bottommargin=15&encoding=&headerhtml=&footerhtml=&watermarkhtml=&pslevel=3&method=fpdf&pdfversion=1.3&output=0&convert=Convert+File\">";
		$body="<table border=0><tr><td><img src=\"images/loading.gif\"></td><td class=titolo>Creating the print version of this webpage. This may take a few moments. Please wait.</td></tr></table>";
		$html_str=preg_replace("/<!--body-->/", $body, $html_str);
		$html_str=preg_replace("/<!--refresh-->/", $refresh, $html_str);
		echo $html_str;
	}
}
else {
	$docs=new doc_gest();
	$body=$docs->new_editor();
	$html_str=file_get_contents("template.html");
	$html_str=preg_replace("/<!--body-->/", $body, $html_str);
}


?>