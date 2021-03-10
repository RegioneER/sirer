
<?php

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




/**
 * Funzione ricorsiva che aggiorna i task
 *
 * @param integer $id
 */
/*function aggiorna_figli($id){
	global $conn;
	$sql=new query($conn);
	$query_upd_corr="update task t set (t.data_inizio, t.data_fine)=(select t1.data_fine+1, t1.data_fine+1+t.durata from task t1 where t1.id=t.parent) where t.id=$id";
	$sql->set_sql($query_upd_corr);
	$sql->ins_upd();
	$query="select id from task where parent=$id";
	$sql->set_sql($query);
	$sql->exec();
	while ($sql->get_row()) aggiorna_figli($sql->row['ID']);
}
*/

#foreach ($in as $key => $val) echo "<hr>$key $val";

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

session_start();
$sid=session_id();

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
		select nome||' '||cognome as nome from ".txt('ana_utenti')." where userid='{$in['remote_userid']}'
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
 * Utilit� gestione slavataggio in db
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
		if ($sql->row['CONTO']>0 || !isset($config_calendar['Organizer'])) $link_stampa="<p align=right  style=\"background: url(images/button.gif) bottom repeat-x ;\"><input title='".txt('link_crea_riunione')."' type='button' value='".txt('Calendario_Crea_Riunione')."' onclick=\"window.location.href='{$scriptname}?tab=1&action=new_riunione';\">&nbsp;&nbsp;<a href='{$scriptname}?{$param}&print_version=yes' target='_new'>".txt('Link_stampa')."<img src='images/ico_stampa.gif' border=0></a></p>";
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
				<br><a href='{$scriptname}?tab=12' title='".txt('tab_title_12')."'>Send new message</a>
				<br><a href='{$scriptname}?tab=12' title='".txt('tab_title_12')."'>".txt('MORE')."</a>
			  </fieldset>";
		if ($in['id_group']!=''){
			$content_body="$link_stampa
						".$docs->docs_area()."
						<br>".$forums->forum_list()."
						";
			if(txt('cineca_note'))$content_body="<fieldset>".txt('cineca_note')."</fieldset> <br>".$content_body;

		}
		else {
			$sql_query="select count(*) as conto from organizer where userid='{$in['remote_userid']}'";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();
			$sql->get_row();
			if ($sql->row['CONTO']!=0){

				$link_new_event="<a href='{$_GLOBALS['scriptname']}?tab=1&action=new_riunione' title='".txt('link_crea_riunione')."'>".txt('Calendario_Crea_Riunione')."</a>";
			}
			else $link_new_event='';
			if($tabs[13])$forum_last=$forums->forum_list_last()."
						<br>";

		$content_body="<fieldset><legend class=mttl>My WCA Home</legend>
		$link_stampa
						<fieldset><legend class=mttl>".txt('Menu_principale_riunione')."</legend>
							".$meetings->riunioni_prossime()."
							<br>
							$link_new_event
							<br>
							<a href='{$scriptname}?tab=1' title='".txt('tab_title_1')."'>".txt('MORE')."</a>
							</fieldset>
						<br>
						".$docs->docs_area_last()."
						<br>".$forum_last.$mess_int."
							</fieldset>
						";
		}
	}
	if ($in['tab'] =='1'){
		$content_body.=$riunioni->riunioni_html();
	}
	if ($in['tab'] =='3'){
		$docs=new doc_gest();
		$usr_o=new user_gest();
		$Super_User=$usr_o->IsSuperUser();
		if (isset($id_area) && $id_area!='') {
			if (preg_match("/\^/", $id_area)){
				$sql_areas="select distinct(id_ref) from ".txt('wom_user_ref')." where tipo_ref='Doc_Area'";
				if (!$Super_User) $sql_areas.=" and userid='{$in['remote_userid']}' ";
				$sql=new query($conn);
				$sql->set_sql($sql_areas);
				$sql->exec();
				while ($sql->get_row()){
					if ($id_areas!='') $id_areas.="^";
					$id_areas.=$sql->row['ID_REF'];
				}
				if (isset($in['search']) && $in['search']!='') $searched="Keyword searched: <font color='red'>{$in['search']}</font><br><a href='{$_GLOBALS['scriptname']}?tab={$in['tab']}'>Clear search result</a>";
				$content_body.="<fieldset><legend class=mttl id=m_5_h>".txt('Area_documentale_Titolo')."</legend>
		<table border=0 width=100% style=\"background: url(images/button.gif) bottom repeat-x ;\">
					<tr>
					<td align=center>$searched</td>
					<td align=right>
						<form method=post name='search_docs_area' action='index.php' style=\"text-align:right\">
							<span class=\"sbox_l\" onclick=\"document.forms['search_docs_area'].search.value='Search...';\"></span>
						<span class=\"sbox\"><input type=text name='search'  value='{$in['search']}'
							onclick=\"if (this.value=='Search...')this.value='';\" size=5
							onblur=\"if (this.value=='') {this.value='Search...';}\"></span>
						<span class=\"sbox_r\" id=\"srch_clear\"
							onclick=\"
								if (document.forms['search_docs_area'].search.value=='Search...' ||
									document.forms['search_docs_area'].search.value=='') return false;
									else document.forms['search_docs_area'].submit();\"></span>

							<input type='hidden' name='id_area' value='$id_areas'>
			<input type='hidden' name='tab' value='{$in['tab']}'>

						</form>
					</td><td width=10%>$link_stampa</td>
				</tr>

			</table>";
				$id_areas=preg_split("/\^/",$id_area);
				foreach ($id_areas as $key => $val){
					if ($content_body!='')
					$this_area=$docs->show_area($val);
					if ($this_area!='') $content_body.="<br>";
					$content_body.=$this_area;
				}
				$content_body.="</fieldset>";
			}
			else $content_body=$docs->show_area($id_area);
		}
		if (isset($id_doc) && $id_doc!='') $content_body=$docs->show_doc($id_doc, 1);
		if (isset($approv) && $approv!='' && !isset($doc_approv)) $content_body=$docs->intra_area_approv($approv);
		if (!isset($id_doc) && !isset($id_area)) $content_body=$docs->docs_area();
	}

	if ($in['tab']=='4'){
		$user=new user_gest();
		$content_body=$user->user_tree();
	}
	if ($in['tab']=='5'){
		$docs=new doc_gest();
		$content_body=$docs->publish_area();
	}
	if ($in['tab']=='15'){
		$users=new user_gest();
		if ($user_id=='') $content_body=$users->contacts_list();
		else $content_body=$users->user_details($user_id);
	}
	if ($in['tab']=='12'){
		$msg_int=new mess_gest();
		$content_body.=$msg_int->messaggi();
	}
	if ($in['tab']=='13'){
		$forums=new forum_gest();
		if (!isset($id_forum)) $content_body.=$forums->forum_list();
		if (isset($id_forum)  && !isset($id)) {
			if (preg_match("/\^/", $id_forum)){
				$id_forums=preg_split("/\^/",$id_forum);
				$sql_areas="select distinct id_ref from ".txt('wom_user_ref')." where tipo_ref='Forum'";
				if (!$Super_User) $sql_areas.=" and userid='{$in['remote_userid']}'";
				$sql=new query($conn);
				$sql->set_sql($sql_areas);
				$sql->exec();
				while ($sql->get_row()){
					if ($id_areas!='') $id_areas.="^";
					$id_areas.=$sql->row['ID_REF'];
				}
				$content_body="<fieldset><legend class=mttl>".txt('Forum_Lista')."</legend>
				<form method=post name='search_{$id_area}' action='index.php' style=\"text-align:right\">
				<table border=0 width=100% style=\"background: url(images/button.gif) bottom repeat-x ;\">
					<tr>
						<td align=right>

					<span class=\"sbox_l\" onclick=\"document.forms['search_{$id_area}'].search.value='Search...';\"></span>
					<span class=\"sbox\"><input type=text name='search'  value='{$in['search']}'
							onclick=\"if (this.value=='Search...')this.value='';\" size=5
							onblur=\"if (this.value=='') {this.value='Search...';}\"></span>
						<span class=\"sbox_r\" id=\"srch_clear\"
							onclick=\"
								if (document.forms['search_{$id_area}'].search.value=='Search...' ||
									document.forms['search_{$id_area}'].search.value=='') return false;
									else document.forms['search_{$id_area}'].submit();\"></span>
							<input type='hidden' name='id_forum' value='{$id_areas}'>
							<input type='hidden' name='tab' value='{$in['tab']}'>
				</form></td><td width=10%>$link_stampa</td></tr></table>
				";
				foreach ($id_forums as $key => $val){
					if ($content_body!='') $content_body.="<br>";
					$content_body.=$forums->forum($val);
				}
			}
			else $content_body.=$forums->forum($id_forum);
		}
		if (isset($id_forum)  && isset($id)) $content_body.=$forums->show_topic($id_forum,$id);
	}
	if ($in['tab']=='22'){
		$doc_o=new doc_gest();
		if ($tipo=='') $tipo=1;
		if (!isset($id_doc)) $content_body=$doc_o->approval_area($tipo);
		else $content_body=$doc_o->approval_form();
	}

	if ($in['tab']==23){
		$content_body.=searchpage();
	}
	if ($in['tab']==26){

		foreach($report_enabled_users as $key=> $val){
			//echo "<li>$key - $val</li>";
			if ($in['remote_userid']==$val || true){
				$meet_class=$docs_class=$users_class=$forum_class=$aw_stat_class='mttl2';
				if ($in['rep']=='') {
					$meet_class="mttl2_new";
					$iframe='<iframe src="/cgi-bin/reports?fase=1&nome_progetto=R1&vis_head=no" height="1000" width="100%" scrolling="auto" frameborder="0"></IFRAME>';
				}
				if ($in['rep']=='docs') {
					$docs_class="mttl2_new";
					$iframe='<iframe src="/cgi-bin/reports?fase=1&nome_progetto=R2&vis_head=no" height="1000" width="100%" scrolling="auto" frameborder="0"></IFRAME>';
				}
				if ($in['rep']=='users') {
					$users_class="mttl2_new";
					$iframe='<iframe src="/cgi-bin/reports?fase=1&nome_progetto=R3&vis_head=no" height="1000" width="100%" scrolling="auto" frameborder="0"></IFRAME>';
				}
				if ($in['rep']=='forum') {
					$forum_class="mttl2_new";
					$iframe='<iframe src="/cgi-bin/reports?fase=1&nome_progetto=R4&vis_head=no" height="1000" width="100%" scrolling="auto" frameborder="0"></IFRAME>';
				}
				//Per abilitare le statistiche di accesso decommentare il seguente blocco
				/*if ($in['rep']=='aw_stat') {
					$aw_stat_class="mttl2_new";
					$iframe='<iframe src="/cgi-bin/awstats/bin/awstats.pl?config='.$_SERVER['SERVER_NAME'].'&output=main&framename=index&lang=en" height="1000" width="100%" scrolling="auto" frameborder="0"></IFRAME>';
				}*/
				$content_body="
				<fieldset><legend class='mttl'>Reports</legend>
					<table border=0 align=center span=0 padding=>
						<tr>
							<td class='$meet_class'><a href='{$_SERVER['SCRIPT_NAME']}?tab=26&rep='>".txt('Menu_principale_riunione')."</a></td>
							<td class='$docs_class'><a href='{$_SERVER['SCRIPT_NAME']}?tab=26&rep=docs'>".txt('Menu_principale_Area_Documentale')."</a></td>
							<td class='$users_class'><a href='{$_SERVER['SCRIPT_NAME']}?tab=26&rep=users'>".txt('statistiche_utenti')."</a></td>
							<td class='$forum_class'><a href='{$_SERVER['SCRIPT_NAME']}?tab=26&rep=forum'>".txt('Menu_principale_Forum')."</a></td>
							<!--AW_STAT-->
						</tr>
					</table>
					$iframe
				</fieldset>
				";
				//Per abilitare le statistiche di accesso decommentare la seguente riga
				//$content_body=str_replace("<!--AW_STAT-->","<td class='$aw_stat_class'><a href='/cgi-bin/awstats/bin/awstats.pl?config=".$_SERVER['SERVER_NAME']."&output=main&framename=index&lang=en' target='_new'>".txt('statistiche_accesso')."</a></td>",$content_body);
			}
		}
	}
	if ($in['tab']=='100'){
		$usr_o=new user_gest();
		$content_body=$usr_o->list_da_abilitare();
	}
	$query="select nome from prj where id=$prj";
	$sql->set_sql($query);
	$sql->exec();
	$sql->get_row();
	$prj_name=$sql->row['NOME'];
	$body="";
	$tabs_obj=new tab_gest();
	$Navigation_icon.=$tabs_obj->tab_gest_html($in['tab']);
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


if (isset($tab)){
	$str_help="Help_tab_{$tab}";
	if (isset($action)) $str_help.="_{$action}";
	if (isset($display)) $str_help.="_{$display}";
	if (isset($visione)) $str_help.="_{$visione}";
	if (isset($id_forum)) $str_help.="_id_forum";
	if (isset($id_area)) $str_help.="_id_area";
	if (isset($user_id)) $str_help.="_user_id";
	$help_txt=txt($str_help);
}
else {
	$str_help="Help_tab_0";
	$help_txt=txt($str_help);
}

$sql=new query($conn);
$usr_o=new user_gest();
$user_groups=$usr_o->user_groups($in['remote_userid']);
$grp_o=new group_gest();
$grp_parent=$grp_o->where_group_with_parent($user_groups);
if($user_groups!='' || $Super_User)$grp_son=$grp_o->where_group_with_subgroups($user_groups);
//echo "<li>$user_groups</li><li>$grp_parent</li><li>$grp_son</li>";
if ($grp_parent!='') $grp_list=$user_groups.",".$grp_parent;
else $grp_list=$user_groups;
if ($grp_son!='') $grp_list.=",".$grp_son;
$grp_list=preg_replace("/^,/","", $grp_list);
//echo "<hr>$user_groups - $grp_parent - $grp_son<hr>";
if ($grp_list!='') {
	$sql_query="select distinct id, nome from workspaces_1 where prj={$in['prj']} and id in ($grp_list)";
	$sql->set_sql($sql_query);
	$sql->exec();
	//print_r($sql->res);
	$m_3="
	 <fieldset width=100%><legend class=mttl>".txt('Workspaces')."</legend>
	 <a href='{$_GLOBALS['scriptname']}?sid_' title='".txt('tab_title_0')."'>".txt('all_site')."</a>
	";
	while ($sql->get_row()){
		if ($in['id_group']==$sql->row['ID']) $sql->row['NOME']="<font color=red>".$sql->row['NOME']."</font>";
		$m_3.="<p class=mttl2><a href='{$_GLOBALS['scriptname']}?sid_id_group={$sql->row['ID']}' title='".txt('link_workspace')."'>{$sql->row['NOME']}</a></p><ul>";
		$sql2=new query($conn);
		$sql_query="select distinct id, nome from workspaces_2 where id_ref={$sql->row['ID']} and id in ({$grp_list})";
		$sql2->set_sql($sql_query);
		$sql2->exec();
		while ($sql2->get_row()) {
			if ($in['id_group']==$sql2->row['ID']) $sql2->row['NOME']="<font color=red>".$sql2->row['NOME']."</font>";
			$m_3.="<li><a href='{$_GLOBALS['scriptname']}?sid_id_group={$sql2->row['ID']}' title='".txt('link_workspace')."'>{$sql2->row['NOME']}</a></li>";
		}
		$m_3.="</ul>";
	}
	$m_3.="
	 </fieldset>
	";
}


$m_4="
	       <fieldset width=100%>
				$help_txt
			  </fieldset>
	";

/* Se configurazione standard visualizza la colonna sinistra ($left_column) */
if($WCA['type'] == "MONITORAGGIO"){
	$left_column = "";
}else{
	$left_column = "
		<td width=20% rowspan=2 bgcolor='#E1ECFC' valign=top style='padding:4px'>
			$m_1<br>
			$m_3<br>
			$m_2
		</td>";
}

$tb_body="<tr>
	{$left_column}
	<td bgcolor='#E1ECFC' valign=top style='padding:4px'>
		$m_4<br>$m_5</td>
	</tr>
	";

if (isset ($banner_config['href'])) $banner = "
  <tr>
    <td align=\"center\"><a href=\"{$banner_config['href']}\"><img src=\"{$banner_config['image']}\" border=\"0\" alt=\"{$banner_alt['alt']}\"></a></td>
    <td align=\"center\" valign=\"bottom\"><a href=\"{$banner_config['href']}\"><img src=\"images/logo-regione-veneto.jpg\" border=\"0\" alt=\"{$banner_alt['alt']}\"></a></td>
  </tr>
  <tr>
  	<td align=\"center\" colspan=\"2\"><h1>Web Community Area</h1></td>
  </tr>
";
else $banner = "
  <tr>
    <td align=\"center\"><img src=\"{$banner_config['image']}\" border=\"0\" alt=\"{$banner_config['alt']}\"></td>
  </tr>
";

/* Se configurazione standard visualizza la colonna sinistra ($left_column) */
if($WCA['type'] == "MONITORAGGIO"){
	$Navigation_icon="";
}

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
		//$body=$docs->show_area($id_area);
		$html_str=preg_replace("/<!--body-->/", $body, $html_str);
		$html_str=preg_replace("/<!--refresh-->/", $refresh, $html_str);
		if ($tab==1 && ($action=='new_riunione' || $ID!='')) $google_map="<script src=\"http://maps.google.com/maps?file=api&amp;v=2.x&amp;key={$google_key}\" type=\"text/javascript\"></script>";
		$html_str=preg_replace("/<!--google_map-->/", $google_map, $html_str);
		$html_str=preg_replace("/<!--script-->/", $script, $html_str);
		$html_str=preg_replace("/\/\/<!--onload-->/", $onload, $html_str);
		//$html_str=preg_replace("/href=\"(.*?)\"/ie", "to_post_link('\\1')",$html_str);
		//$html_str=preg_replace("/href='(.*?)'/ie", "to_post_link('\\1')",$html_str);
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
		if($banner_config['pdf_image'])$banner_pdf="<img src=\"{$banner_config['pdf_image']}\">";
		$body="<table border=0 cellpadding=0 cellspacing=0 width=1024><tr><td>$banner_pdf</td><td>{$m_1}</td></tr><tr><td colspan=2>$content_body</td></tr></table>";
		$html_str=preg_replace("/<!--body-->/", $body, $html_str);
		//$body=str_replace("</fieldset>","</fieldset><!--NewPage-->", $body);
		//		$body=str_replace("display:none","", $body);
		//		$body=str_replace("doc.jpg","doc_1.gif", $body);
		//		$body=str_replace("folder_icon","folder_icon_open", $body);
		//		$body=str_replace("pdf.jpg","pdf.gif", $body);
		//		$html_str=preg_replace("/<!--body-->/", $body, $html_str);
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