<?php 
 
//**************INCLUDES ***************************
require_once "libs/http_lib.inc";
include_once "libs/db.inc";
include_once "libs/xml_parser_wl.inc";
include_once "libs/HTML_Parser.inc";
include_once "fax_api.inc";
include_once "libs/page.inc";
include_once "libs/vlist.inc";
include_once "libs/list.inc";
include_once "libs/legend.inc";
include_once "libs/esams_list.inc";
include_once "libs/form.inc";
include_once "libs/study_prototype.inc";
include_once "libs/xmrwf.inc.php";
//****************FINE INCLUDES *********************


//********* CONFIGURAZIONI SERVIZIO DEFAULT *********************
$editing = false;
$email_admin = "g.tufano@cineca.it";
$config_service['email_admin']="g.tufano@cineca.it";
$config_service['equery']="yes";
$config_service['dir_lib']="libs/armonia";
$config_service ['from_service_email']="no_reply@cineca.it";
$config_service ['from_service_name']="Registro AIFA Farmaci - Notifiche automatiche";
$config_service ['helpdesk_mail']="";
$config_service ['nome_servizio']="";
$config_service ['nome_registro']="";


$root = $_SERVER ['DOCUMENT_ROOT'];
$dir = $_SERVER ['PATH_TRANSLATED'];
$dirs = explode ( "/", $dir );
$dir = '';


for($i = 0; $i < count ( $dirs ) - 1; $i ++) {
	$dir .= $dirs [$i] . "/";
}
$dir = rtrim ( $dir, "/" );
if (! is_dir ( $GLOBALS ['dir'] . "/log_trace" )) {
	mkdir ( $GLOBALS ['dir'] . "/log_trace", 0777 );
	chmod ( $file_log, 0777 );
	chmod ( $GLOBALS ['dir'] . "/log_trace", 0777 );
}


$xml_dir = $dir . "/xml";
$file_log = $dir . "/log_trace/" . strtoupper ( $in ['remote_userid'] ) . ".log";
$log_conn = new dbconn ( );
$q_log = new query ( $log_conn );
$sql = "select max(id) as ID from sessions";
$q_log->set_sql ( $sql );
$q_log->exec ();
$q_log->get_row ();
$session_number = $q_log->row ['ID'] + 1;
$log_str = "<session $session_number><hr><b>Script : index.php</b><br><b>Parametri di input</b><ul>";
foreach ( $in as $key => $val )
$log_str .= "<li>$key: $val</li>";
$log_str .= "</ul></session>";
$handle = fopen ( $file_log, 'a+' );
fwrite ( $handle, $log_str );
fclose ( $handle );
$sql = "insert into sessions(id, userid, data) values($session_number, '" . $remote_userid . "', sysdate)";
$q_log->set_sql ( $sql );
$q_log->ins_upd ();
$log_conn->commit ();
$template_dir = $dir;

$conn = new dbconn ( );
$sql = new query ( $conn );

// $sql->set_sql ( "ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'" );
// $sql->ins_upd ();


//********* FINE CONFIGURAZIONI *********************



/**
 * INCLUDE DI TUTTI I SERVIZI PER REPLICARE IL SISTEMA INGEGNOSO CHE GIA' GIORGINO E CARLO SPERIMENTARONO
 * ANNI ADDIETRO E CHE CONDUCONO TUTTI I NOSTRI SERVIZI.
 */
class xml_form_armonia extends xml_form_prototype {


	function make_html($no_link_back=false, $closed=false,$force_open=false,$exclude_send_buttons=false) {
		$in = $this->session_vars;
		$inputval = $this->tb_vals;
		$remote_userid = $in ['remote_userid'];
		$sql_query="select fine, userid, visitclose from {$this->config_service['service']}_coordinate where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and esam='{$in['ESAM']}' and progr='{$in['PROGR']}' and visitnum='{$in['VISITNUM']}' and visitnum_progr='{$in['VISITNUM_PROGR']}'";
		$sql=new query($this->conn);
		$sql->get_row($sql_query);
		if ($sql->row['FINE']==1) $this->closed=true;
		if ($sql->row['USERID']==$remote_userid && $sql->row['FINE']!='1' && $sql->row['VISITCLOSE']!='1' && $in['USER_TIP']!='DM') $in['USER_TIP']='DE';

		if ($closed) {
			$this->closed_form();
			$this->closed=true;
			$this->close_form(true);
			return;
		}
		if ($force_open) {
			$this->closed_form();
			$this->closed=false;
			$this->open_form($force_open,$exclude_send_buttons);
			return;
		}
		if ($in ['USER_TIP'] == 'DE') {
			if (! $this->closed_form ()){
				$this->open_form ();
			}
			else
			{
				$this->close_form ($no_link_back);
			}
		}
		if ($in ['USER_TIP'] == 'DM') {
			if (! $this->closed_form ()){
				$this->close_form ($no_link_back);
			}
			else
			{
				if ($in['RO']=='1') $this->close_form ($no_link_back);
			 else $this->open_form ();
			}
		}
		if ($in ['USER_TIP'] == 'RO') {
			$this->closed_form ();
			$this->close_form ($no_link_back);
		}

	}
}


class xml_vlist_armonia extends xml_vlist_prototype {}
class xml_page_armonia extends xml_page_prototype {}
class xml_list_armonia extends xml_list_prototype {}
class user_armonia extends user_prototype {}

class xml_esams_list_armonia extends xml_esams_list_prototype {



	/**
	 * Restituisce la lista delle form compilate e compilabili
	 *
	 * @return string
	 */
	function esams_list_html($service=null){
		if(isset($service))
		$parametro_passato=true;
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		global $patient_table;
		//$this->body.=$patient_table;
		$sql=new query($conn);
		if(!$service)global $service;
		$sql_close="select min(visitclose) as chiusa from {$service}_coordinate where {$config_service['PK_SERVICE']}=:pk_service";

		//echo "<li>$sql_close</li>";
		unset($bind_pk);
		$bind_pk['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
		//$sql->set_sql($sql_close);
		$sql->exec($sql_close,$bind_pk);//binded
		$sql->get_row();
		$chiusa=$sql->row['CHIUSA'];

		if ($config_service['PK_SERVICE']=='') $config_service['PK_SERVICE']=$this->PK_SERVICE;
		if ($config_service['VISITNUM_PROGR']=='1') {
			$add_vprogr="VISITNUM_PROGR,";
			$sql=new query($conn);
			$sql_select="select max(visitnum_progr) as maxvp from ".$service."_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service";
			unset($bind_pk);
			$bind_pk['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
			//$sql->set_sql($sql_select);
			$sql->exec($sql_select,$bind_pk);//binded
			$sql->get_row();
			$max_vp=$sql->row['MAXVP'];
			foreach($this->visitnums as $visit => $vval){
				if ($vval['PROGR']=='yes') {
					$v_progr_esam_spec=$this->esams[$visit];
					unset($this->esams[$visit]);
					for ($i=0; $i<=$max_vp; $i++){
						$this->esams[$visit][$i]=$v_progr_esam_spec;
					}
				}
			}
		}
		//if ($in['USER_TIP']=='DE')
		$query="select userid,visitclose,visitnum,$add_vprogr esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$service."_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service order by visitnum,$add_vprogr esam ,progr";
		//else $query="select visitnum,$add_vprogr esam, progr, decode(validata,0,1,1,1,null,null) as inizio, validata as fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."' order by visitnum,$add_vprogr esam ,progr";
		//echo "<hr>$query<hr>";
		unset($bind_pk);
		$bind_pk['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
		$sql=new query($conn);
		//$sql->set_sql($query);
		$sql->exec($query,$bind_pk);//binded
		#print_r($this->visitnums);
		while ($sql->get_row()){
			if ($this->visitnums[$sql->row['VISITNUM']]['PROGR']=='yes') {
				if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']]['ENABLED']=true;
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']])){
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA']=$sql->row['VALIDATA'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE']=$sql->row['VISITCLOSE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['USERID']=$sql->row['USERID'];
					$this->visitnums[$sql->row['VISITNUM']]['CLOSED']=$sql->row['VISITCLOSE'];
				}
			}
			else {
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
					if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']]['ENABLED']=true;
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA']=$sql->row['VALIDATA'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE']=$sql->row['VISITCLOSE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['USERID']=$sql->row['USERID'];
					$this->visitnums[$sql->row['VISITNUM']]['CLOSED']=$sql->row['VISITCLOSE'];
				}
			}
		}
		#print_r($this->esams);
		$this->tab="<ul id=\"globalnav\">";

		foreach ($this->visitnums as $key => $val) {
			//	print_r($val);
			if ($val['VIEWABLE_ON_CLOSE']=='yes' && $in['USER_TIP']!='DE' && $val['CLOSED']!='1'){
				continue;
			}
			$af_progr="";
			if (isset($in['GROUP'])){
				$in['VISITNUM']='non so';
				if (isset($this->group[$in['GROUP']]['VISIT'][$key])){

					$in['VISITNUM']=$key;
				}
			}
			//echo "<li>{$in['VISITNUM']}</li>";

			if (!isset($in['VISITNUM']) || $in['VISITNUM']=="$key"){


				if ($val['PROGR']=='yes') {

					if (!$this->isVisitClose($key) && $val['BUTTONS_DISABLED']!='yes' && $in['USER_TIP']=='DE') $aggiungi_visita="<input type='button' value='".$this->testo('Aggiungi')." {$this->visitnums[$key]['TEXT']}' onclick=\"
						window.location.href='index.php?CENTER={$in['CENTER']}&VISITNUM={$key}&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&CREATE_VPROGR=yes';
					\">";
					else $aggiungi_visita='';
					global $config_service;
					if (isset($config_service['class_visit_progr']))
					$style_table="class=\"{$config_service['class_visit_progr']}\" ";
					else $style_table="";

					if ($this->visitnums[$key][0]['ENABLED'])
					{
						$this->body.="
		  				<table $style_table width=\"100%\">
							<tr class='int'>
							<td>&nbsp;&nbsp;</td>
								<td width=80%>
								<a href=\"index.php?CENTER={$in['CENTER']}&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&exams=visite_exams.xml\">
						{$this->visitnums[$key]['TEXT']}
								</a>
								</td>

								<td align=center>
								$aggiungi_visita<br/>
									<a href=\"#\" onclick=\"
									//--show_all--
									return false;
									\">Mostra tutte le schede</a>
								</td>
							</tr>
						";
					}
					foreach($this->esams[$key] as $vprogr => $vesam) {
						if ($max_vprogr<$vprogr) $max_vprogr=$vprogr;
					}
					global $onload;
					foreach($this->esams[$key] as $vprogr => $vesam){

						$nro=$vprogr+1;
						if($val['SET_PROGR_START']=='')$nro_label=$nro;
						else $nro_label=$vprogr+$val['SET_PROGR_START'];

						if ($this->visitnums[$key][$vprogr]['ENABLED']){
							$param="";
							foreach($_GET as $gkey => $gval) if ($gkey!='VISITNUM_PROGR') $param.="$gkey=$gval&";
							if ($in['VISITNUM_PROGR']!=$nro-1 && $this->visitnums[$key]['SHOW_ALWAYS']!="yes") {
								$onload.="
								document.getElementById('af_{$key}_{$nro}').style.display='none';
								";
							}
							$show_all.="
								document.getElementById('af_{$key}_{$nro}').style.display='';
							";
							$not_delete=false;
							foreach ($vesam as $esam => $es_val){
								if ($es_val['RES'][1]['FINE']=='1') $not_delete=true;
							}
							if ($in['USER_TIP']!='DE') $not_delete=true;
							if ($not_delete || $val['BUTTONS_DISABLED']=='yes') $delete_button="";
							else $delete_button="
									<input type='button' value='".$this->testo('Elimina')."' onclick=\"
										if (confirm('".$this->testo("Sei sicuro di voler eliminare")." {$this->visitnums[$key]['TEXT']} ".$this->testo("numero")." $nro?'))
											window.location.href='index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&VISITNUM_PROGR={$vprogr}&DelVisitProgr=yes';
										else return false;
									\">
								";

							if ($this->visitnums[$key]['DATA_TABLE']!=''){
								$sql2=new query($conn);
								$tbs=explode("|", $this->visitnums[$key]['DATA_TABLE']);
								$fields=explode(";", $this->visitnums[$key]['DATA_FIELD']);
								$lbls=explode("|", $this->visitnums[$key]['DATA_HEADER']);
									
								$table='';
								$data='';
								$tb_content='';
								$tb_header='';
								$data_cols='';
								$f_count=0;
								$idx_start=0;
								$idx_end=0;
								$tot_field=0;
								for ($i=0;$i<count($tbs);$i++){
									$sql_query="select {$fields[$i]} from {$service}_{$tbs[$i]} where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
									unset($bind_field);
									$bind_field['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
									$bind_field['VISITNUM']=$key;
									$bind_field['VISITNUM:PROGR']=$vprogr;
									$sql2->exec($sql_query,$bind_field);//binded
									$fields_count[$i]=count(explode(",", $fields[$i]));
									$idx_start+=$fields_count[$i-1];
									$tot_field+=$fields_count[$i];
									$f_count=0;
									while ($sql2->get_row()){
										if ($sql2->n_r>1)
										$f_count=0;
										foreach ($sql2->row as $k_=>$v_){
											$data[$idx_start+$f_count].=$v_."<br/>";
											$f_count++;
										}
									}
								}

								for($i=0;$i<$tot_field;$i++){
									$data[$i]=rtrim($data[$i], "<br/>");
									$tb_content.="<td valign=top align=right class=sc4bis>{$data[$i]}</td>";
								}
								foreach ($lbls as $l_idx=>$l_content){
									$tb_header.="<th valign=top class='int'>$l_content</th>";
								}

								$table="<table width=100%><tr>$tb_header</tr><tr>$tb_content</tr></table>";
								$display="none";
							}
							else {
								$table='';
								$display='';
							}

							$onclick="";
							$this->body.="
							<tr>
								<td valign=top class=sc4bis>
									&nbsp;<b>$nro_label.</b>
								</td>
								<td colspan=2>
								<table style=\"border:2px solid\" width=100%>
									<tr class='int'>
										<td width=80%>
							$table
										</td>
										<td valign=top align=center>
							$delete_button<br/>
											<a href=\"#\" onclick=\"show_hide('af_{$key}_{$nro}'); return false;\">Mostra/nascondi schede</a>
										</td>
									</tr>
									<tr>
										<td colspan=2>
											<table id='af_{$key}_{$nro}' align=\"center\" style=\"display:$display;border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        					";
							foreach ($vesam as $esam => $es_val){
								if ($vprogr==null) $vprogr="0";

								if ($es_val['RES'][1]['ABILITATO']=='1') {

									$this->print_esams($es_val,$key,$esam, $vprogr);
								}
							}
							$this->body.="
											</table>
										</td>
									</tr>
								</table>
							</td>
						</tr>";
						}
					}
					$this->body=str_replace("//--show_all--", $show_all, $this->body);
					if ($this->visitnums[$key][0]['ENABLED']) $this->body.="</table>";
				}
				else{

					if ($this->visitnums[$key]['ENABLED']){
						$tbody_close='';
						$tbody_open='';
						$show_hide_link='';
						$count_schede=0;
						$schede_vuote=0;
						foreach ($this->esams[$key] as $esam => $es_val){

							if ($es_val['RES'][1]['ABILITATO']=='1') {
								$count_schede++;
							}
							if ($es_val['RES'][1]['ABILITATO']=='1') {
								foreach ($es_val['RES'] as $k_v=>$v_v){
									if ($v_v['INIZIO']!='1')
									$schede_vuote++;
								}
							}
						}
						if (isset($val['SHOW_HIDE'])){
							$tbody_open="<tbody id=\"VISITNUM_{$key}_TBODY\" style=\"display:none\">";
							$tbody_close="</tbody>
							<tbody id=\"VISITNUM_{$key}_TBODY_\" style=\"display:\">
								<tr>
									<td class=sc4bis>
									<ul>
										<li><b>Totale Schede: $count_schede</b></li>
										<li><b><font color=red>Schede vuote: $schede_vuote</font></b></li>
									</ul>
									</td>
							</tbody>
							";
							$show_hide_link="
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<a href=\"#\" onclick=\"
							show_hide('VISITNUM_{$key}_TBODY');
							show_hide('VISITNUM_{$key}_TBODY_');
							return false;
							\">Mostra/Nascondi tutte le schede</a>";
						}

						$this->body.="
		  		<table border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        	<tr>
							<!--td class=\"int\" colspan=2 align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"sc2b\">".$val['TEXT']."</a>
						$show_hide_link
							</td-->
							<td class=\"int\" colspan=2 align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"sc2b\">".$val['TEXT']."</a></td>
							<td class=\"int\"  align=\"left\">Inviato/corretto da</td>
							<td class=\"int\"  align=\"left\">Data d'invio</td>
				</tr>
						$tbody_open
						";
						foreach ($this->esams[$key] as $esam => $es_val){
							$this_enabled=false;
							foreach ($es_val['RES'] as $p => $x){
								if ($es_val['RES'][$p]['ABILITATO']==1) $this_enabled=true;
							}
							if ($this_enabled) {
								$this->print_esams($es_val,$key,$esam);
							}

						}
						$this->body.=$tbody_close;
					}
				}
			}
			global $service;
			$sql_close_visit="select nvl(min(visitclose),0) as close from {$service}_coordinate where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and VISITNUM=$key";
			$sql=new query($this->conn);
			$sql->get_row($sql_close_visit);
			if ($this->visitnums[$key]['CLOSE_VISIT']!='' && $sql->row['CLOSE']=='0' && $in['USER_TIP']=='DE' && ($in['VISITNUM']=='' || $in['VISITNUM']==$key)){
				if ($this->visitnums[$key]['CLOSE_VISIT_NOTE']){
					$this->body.="
				<tr>
					<td class=\"int\" colspan=2 align=center>
						<div id='BUTTON_CLOSE_VISIT' style=\"display:\">
						<input type=\"button\" value=\"{$this->visitnums[$key]['CLOSE_VISIT']}\"
						onclick=\"
						document.getElementById('CLOSE_VISIT_NOTE').style.display='';
						document.getElementById('BUTTON_CLOSE_VISIT').style.display='none';
						\"
						>
						</div>
						<div id='CLOSE_VISIT_NOTE' class=\"input\" style=\"display:none\">
						<form method='GET' action=\"index.php\" onsubmit=\"
						if (document.getElementById('NOTE_CHIUSURA_SPEC_ID').value==''){
							alert('Inserire note');
							return false;
						}
						\">
						<input type='hidden' name='{$this->PK_SERVICE}' value=\"{$in[$this->PK_SERVICE]}\">
						<input type='hidden' name='CLOSE_VISIT' value=\"$key\">
					{$this->visitnums[$key]['CLOSE_VISIT_NOTE']}:<br/>
						<textarea id='NOTE_CHIUSURA_SPEC_ID' name='NOTE_CHIUSURA_SPEC' cols=80 rows=5></textarea><br/>
						<input type='submit' value=\"Procedi\" onclick=\"
						if (document.getElementById('NOTE_CHIUSURA_SPEC_ID').value==''){
							alert('Inserire note');
							return false;
						}
						\">
						&nbsp; <input type='button' value=\"Annulla\"
						onclick=\"
						document.getElementById('CLOSE_VISIT_NOTE').style.display='none';
						document.getElementById('BUTTON_CLOSE_VISIT').style.display='';
						\"
						>
						</form>
						</div>
					</td>
				</tr>
					";
				}
				else
				$this->body.="
				<tr>
					<td class=\"int\" colspan=2 align=center>
						<input type=\"button\" value=\"{$this->visitnums[$key]['CLOSE_VISIT']}\"
						onclick=\"window.location.href=window.location.href+'&CLOSE_VISIT=$key';\"
						>
					</td>
				</tr>
			";
			}
			//echo "<hr>".$this->body."<hr>";
		}
		/*PARTE RELATIVA ALLA CHIUSURA DELLA VISITA*/
		/*if ($in['VISITNUM']!=''){
		 $query="select min(fine) as fine, min(visitclose) as vclose from ".$GLOBALS['service']."_COORDINATE where ".$config_service['PK_SERVICE']."='".$in[$config_service['PK_SERVICE']]."' and VISITNUM='".$in['VISITNUM']."'";
		$sql->set_sql($query);
		$sql->exec();//commentata
		$sql->get_row();
		if($sql->row['FINE']=='1' && $sql->row['VCLOSE']!='1') $this->body.="
		<table border=0 cellspacing=0 cellpadding=0 align=center><tr><td>
		<form method=post action='index.php' align=center>
		<input type='hidden' name='".$config_service['PK_SERVICE']."' value='".$in[$config_service['PK_SERVICE']]."'>
		<input type='hidden' name='VISITNUM' value='".$in['VISITNUM']."'>
		<input type='hidden' name='CENTER' value='".$in['CENTER']."'>
		<input type='hidden' name='exams' value='visite_exams.xml'>
		<!--input type='submit' name='close_visit' value='Close Visit' align=center-->
		</form>
		</td></tr></table>
		";
		}*/
		if ($this->body!='')	$this->body.="</table>";
		//print_r($this->esams);
		global $service;
		$sql_close="select min(visitclose) as closed from {$service}_coordinate where {$config_service['PK_SERVICE']}=:pk_service";
		$sql2=new query($conn);
		//$sql2->set_sql($sql_close);
		unset($bind_pk);
		$bind_pk['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
		$sql2->exec($sql_close,$bind_pk);//binded
		$sql2->get_row();
		if (isset($this->esams['CLOSE_ALL']) && $in['USER_TIP']=='DE' && $sql2->row['CLOSED']!='1')
		{
			$sql_query="select max(stato) as stato from {$service}_coordinate where {$this->PK_SERVICE}=:pk_service and abilitato=1";
			//echo $sql_query;
			$sql=new query($conn);
			//$sql->set_sql($sql_query);
			unset($bind_stato);
			$bind_stato['PK_SERVICE']=$in[$this->PK_SERVICE];
			$sql->exec($sql_query,$bind_stato);//binded
			$sql->get_row();
			if ($sql->row['STATO']=='2') {
				$sql_query="select min(fine) as fine from {$service}_coordinate where {$this->PK_SERVICE}=:pk_service and abilitato=1";
				$sql=new query($conn);
				unset($bind_chiusa);
				$bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
				//$sql->set_sql($sql_query);
				//echo "<hr>$sql_query<hr>";
				$sql->exec($sql_query,$bind_chiusa);//binded
				$sql->get_row();

				if ($sql->row['FINE']=='1')
				$this->body.="
			<p align=center id='close_all_p'>
			<a href=\"index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\">
			Invia revisione
			</a>
			</p>
		<script>
			document.getElementById('close_all_p').innerHTML='<input type=\\'button\\' value=\\'Invia revisione\\' onclick=\"window.location.href=\\'index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\\'\">';
		</script>
		";
			}
			else {
				$js_close_all=make_js($this->esams['CLOSE_ALL']);
				$this->body.="
			<p align=center id='close_all_p'>
			<a href=\"index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\">
				{$this->esams['CLOSE_ALL']}
			</a>
			</p>
		<script>
			document.getElementById('close_all_p').innerHTML='<input type=\"button\" value=\"{$js_close_all}\" onclick=\"if (confirm(\\'Attenzione!Preseguendo non sara\\' possibile effettuare modifiche alla pratica.\\'))window.location.href=\\'index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\\';else return false;\">';
		</script>
		";
			}
		}
		$this->body.="<p align=left>";
		if($this->config_service['lang']=="en") {
			$go="Go to ";
		} else {
			$go="Vai alla ";
		}
		/*
		 if ($in['USER_TIP']=='DE') $this->body.="
		<a href=\"index.php?list=patients_list.xml&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&CENTER=".$in['CENTER']."\">{$config_service['Menu_paziente']}</a><br>";
		*/
		//print_r($config_service);
		if($config_service['Patients_list']!="") {
			$link="index.php?list=patients_list.xml";
			if($in['CENTER']!='') $link.="&CENTER={$in['CENTER']}";
			if(!$parametro_passato)	$this->body.="$go
	  	<a href=\"$link\">{$config_service['Patients_list']} &gt;&gt; </a>";
		}
		/*
		 if ($in['USER_TIP']=='DE') $this->body.="
		<a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">{$config_service['Patients_list']}</a>";
		*/
		$this->body.="</p><br />";
		if(!isset($in['VISITNUM']))
			$this->body.=$this->printEquery($in[$this->PK_SERVICE]);
		//print_r($this);
		return $this->body;
	}
	
	
	function print_esams($es_val, $key, $esam, $vprogr=0){
		if($es_val['HEADER']!="")$header="<tr><td class=\"sc4bis\"></td><td class=\"int exam_header\" style=\"text-align:left;\">{$es_val['HEADER']}</td></tr>";
		if ($vprogr!=null) $agg_param="&VISITNUM_PROGR={$vprogr}";
		else $agg_param="";
		$in=$this->session_vars;
		$conn=$this->conn;
		//TODO sistemare la xml_dir
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		global $service;
		$nome_form=$es_val['TESTO'];
		$file_form=$es_val['XML'];
		$form1= new xml_form();
		$form1->xml_form_by_file($xml_dir."/".$file_form);
		$f_table=$form1->form['TABLE'];
		//		echo $f_table."<hr>";
		//ESAMI NON PROGRESSIVO
		if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
			$img="to_be_comp.gif";
			$progr=1;
			if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
			if ($es_val['RES'][$progr]['INIZIO']=='0' || $es_val['RES'][$progr]['INIZIO']=='') $img="to_be_comp.gif";
			if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
			if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
			$file_form=$es_val['XML'];
			$form1= new xml_form();
			$form1->xml_form_by_file($xml_dir."/".$file_form);
			$f_table=$form1->form['TABLE'];
			$dateinv=Set_Ins_data($f_table,$esam, $progr, $in[$config_service['PK_SERVICE']]);
			$nome_esame=$es_val['TESTO'];
			if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
			if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
				$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";
				$close_href="</a>";
				if ($es_val['INDENT']=='yes') $indent="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
				else $indent="";
				$img_tag="<img src=\"/images/$img\" border=\"0\">";
				//if ($in['USER_TIP']=='DM') $img_tag='';
				$this->body.="
										<tr>
											 <td class=\"sc4bis\" width=\"10%\" align=\"center\">{$indent}{$href}{$img_tag}{$close_href}
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"50%\">{$indent}$href".$nome_esame."$close_href<br/>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
											</td>
											</tr>
											";
			}
		}
		//ESAMI PROGRESSIVI
		else {
			$last_progr=0;
			$form_alt='';
			//			print_r($es_val);
			if (isset($es_val['RES']) && !isset($es_val['CORR'])){
				//				print_r($es_val);
				if((isset($es_val['CONT_FORM']) && $es_val['CONT_FORM']=='yes') || isset($es_val['ALL_IN'])){
						
					$sql2=new query($conn);
	
					//MODIFICO VAL_AGG AFFINCHE' ESEGUA SOLO LA QUERY, SENZA ANDARE SUL PROGR
					//modifica G.Tufano 20/02/2012
					if ($es_val['VAL_AGG']!='') {
						$where_agg = $es_val['WHERE_AGG'];
						$query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and esam=:esam $where_agg";
	
						unset($bind_agg);
						$bind_agg['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
						$bind_agg['ESAM']=$esam;
						// 						echo "$query_data<hr />";print_r($bind_agg);
	
						$sql2->exec($query_data,$bind_agg);
						$sql2->get_row();
						$date=$sql2->row['VAL_AGG'];
					}
	
					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						//							echo "<hr>$last_progr -  $es_progr";
						#print_r($es_val);
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							//print_r($es_val);
							if ($es_val['DATA']!='') {
								$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								#echo "<hr>$query_data";
								$sql2->set_sql($query_data);
								$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['DATA'];
							}
							#print_r($this);
							if ($last_progr+1!=$es_progr)
							while ($last_progr<$es_progr-1){
							$last_progr++;
							$n_progr=$last_progr;
							$img="to_be_comp.gif";
							//												$form_alt=str_replace(".xml", "_alt.xml", $es_val['XML']);
							$form_alt=str_replace(".xml", ".xml", $es_val['XML']);
									#echo "<hr>".$xml_dir.$form_alt;
							if (!file_exists($xml_dir."/".$form_alt)) $form_alt=$es_val['XML'];
									$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$form_alt."{$agg_param}\">";
							$nome_esame=$es_val['TESTO']." n. $n_progr";
							$file_form=$es_val['XML'];
							$form1= new xml_form();
							$form1->xml_form_by_file($xml_dir."/".$file_form);
									$f_table=$form1->form['TABLE'];
							$dateinv=Set_Ins_data($f_table,$esam, $n_progr, $in[$config_service['PK_SERVICE']]);
	
									$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1";
									$sql2=new query($conn);
							$sql2->set_sql($sql_query);
							$sql2->exec();
							if ($sql2->numrows>0){
							$sql2->get_row();
							if ($in['USER_TIP']=='DE' && !$archiviata  && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare)</font>";
									}
									//echo "<li>$nome_esame $esam - {$es_val['RES'][$progr]['VALIDATA']}</li>";
							$close_href="</a>";
							$img_tag="<img src=\"/images/$img\" border=\"0\">";
									//if ($in['USER_TIP']=='DM') $img_tag='';
							//if ($in['USER_TIP']=='DM'  && !$archiviata ) $img_tag='';
							//echo "<hr>$key - $nome_esame";
							//echo "<hr> da aggiungere progressivo $n_progr";
							$this->body.="
							<tr>
							<td class=\"sc4bis\" width=\"10%\" align=\"center\"> - $href{$img_tag}$close_href
																		</td>
																		<td class=\"sc4bis\" align=\"left\" width=\"50%\">$href".$nome_esame." $close_href<br/>
																		</td>
							<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b><br/>
																		</td>
																		<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
																		</td>
																	</tr>
							";
	
							}
	
	
								#echo "<hr>2 $es_progr - ";
								if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
								if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
								#$date="";
							#$date=$es_val['RES'][$es_progr]['INSERTDT'];
	
	
							}
	
							foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
							#echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
							if ($es_val_corr['CORR']==$esam){
								//								 echo "<hr> Esame correlato per $esam : ".$esam_corr;
									$img="to_be_comp.gif";
							#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
								if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
								if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
									if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
									#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
									$dtp='';
									$query_data="select to_char({$es_val_corr['DATA']}, 'DD/MM/YYYY') as data from {$GLOBALS['service']}_{$es_val_corr['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								#echo "<hr>$query_data";
								$sql2->set_sql($query_data);
									$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['DATA'];
								#echo "<hr>$date<hr>";
								$n_progr=$es_progr;
								if ($date!='') 	$dtp=" n.{$n_progr} ($date)";
								$nome_esame=$es_val_corr['TESTO']." $dtp";
								$file_form=$es_val_corr['XML'];
								$form1= new xml_form();
								$form1->xml_form_by_file($xml_dir."/".$file_form);
								$f_table=$form1->form['TABLE'];
								$dateinv=Set_Ins_data($f_table,$esam, $n_progr, $in[$config_service['PK_SERVICE']]);
								$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1";
								$sql2=new query($conn);
									$sql2->set_sql($sql_query);
									$sql2->exec();
									if ($sql2->numrows>0){
								$sql2->get_row();
								if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare)</font>";
										//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare)</font>";
									}
								//echo "<li>$nome_esame $esam - {$es_val['RES'][$progr]['VALIDATA']}</li>";
								//if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;
								//						  $href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val_corr['XML']."\">";
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;CODPAT=".$in['CODPAT']."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
								$close_href="</a>";
									$img_tag="<img src=\"/images/$img\" border=\"0\">";
								//if ($in['USER_TIP']=='DM') $img_tag='';
									$this->body.="
											<tr>
								<td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
								</td>
												<td class=\"sc4bis\" align=\"left\" width=\"50%\">$href".$nome_esame." $close_href<br/>
								</td>
												<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
								</td>
								<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
												</td>
								</tr>
												";
								}
							}
							#echo "<hr>ultimo progr $es_progr";
							$last_progr=$es_progr;
						}
						$n_progr=0;
						foreach ($es_val['RES'] as $keys => $val) {
								if ($val['INIZIO']=='1') $n_progr++;
						}
								if ($n_progr==0) {
								$img="to_be_comp.gif";
								if($this->true_false['configurato'])
									$n_progr=$this->testi['nuovo_inserimento'];
									else
									$n_progr="Nuovo inserimento";
									}
									$date=" (".$n_progr.") ".$date;
									$nome_esame=$es_val['TESTO']." $date";
									$file_form=$es_val['XML'];
									$form1= new xml_form();
						$form1->xml_form_by_file($xml_dir."/".$file_form);
									$f_table=$form1->form['TABLE'];
									$dateinv=Set_Ins_data($f_table,$esam, $n_progr, $in[$config_service['PK_SERVICE']]);
									//					echo "<li>$key - $esam - $progr</li>";
									if ($progr!='') {
									$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}
							and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1 and visitnum_progr=$vprogr";
						}
						else {
							/*$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery
						where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and visitnum=$key and esam=$esam and nvl(chiusa,0)<>1 and visitnum_progr=$vprogr";*/
										$sql_query="
									select nvl(e.chiusa,0) as chiusa, min(c.fine) as fine from {$service}_equery e, {$service}_coordinate c
							where c.{$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and c.visitnum=$key and c.esam=$esam and nvl(e.chiusa,0)<>1 and c.visitnum_progr=$vprogr 
										and e.{$this->PK_SERVICE}=c.{$this->PK_SERVICE} and e.esam=c.esam and c.visitnum=e.visitnum and c.visitnum_progr=e.visitnum_progr
									group by e.chiusa
							";
						}
						
						$sql2=new query($conn);
						$sql2->set_sql($sql_query);
						$sql2->exec();
	
						if ($sql2->numrows>0){
									$sql2->get_row();
									if ($in['USER_TIP']=='DE' && !$archiviata  && $sql2->row['CHIUSA']=='0' && ($es_val['RES'][$es_progr]['FINE']!='1' || $sql2->row['FINE']=='0')) {
									$nome_esame.="<font color=red>(da revisionare)</font>";
							}
									}
						if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
							$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";
	
							$close_href="</a>";
							$img_tag="<img src=\"/images/$img\" border=\"0\">";
									if ($deleted||$modified||$added){
									$img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;
									}
	
									$this->body.="{$header}
														<tr>
															 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
															</td>
															<td class=\"sc4bis\" align=\"left\" width=\"50%\">$href".$nome_esame." $close_href<br/>
															</td>
															<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
															</td>
															<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
															</td>
														</tr>
													";
						}
					}
					else{
									foreach ($es_val['RES'] as $es_progr => $progr_vals){
							if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
									$sql2=new query($conn);
									$date="";
								if ($es_val['DATA']!='') {
									$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and  progr=:progr";
									unset($bind_data);
									$bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
									$bind_data['PROGR']=$es_progr;
									//$sql2->set_sql($query_data);
									$sql2->exec($query_data,$bind_data);//binded
									$sql2->get_row();
									$date=$sql2->row['DATA'];
									}
									if ($es_val['VAL_AGG']!='') {
									$query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and  progr=:progr and esam=:esam ";
									unset($bind_agg);
									$bind_agg['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
									$bind_agg['PROGR']=$es_progr;
									$bind_agg['ESAM']=$esam;
									//$sql2->set_sql($query_data);
									$sql2->exec($query_data,$bind_agg);//binded
									$sql2->get_row();
									$date=$sql2->row['VAL_AGG'];
									}
									if ($es_val['FOTH'])
									{
									$query_data="select {$es_val['FOTH']} as FOTH from {$GLOBALS['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}=:pk_service and  progr=:progr and visitnum_progr=:visitnum_progr";
									#echo "<hr>$query_data";
									unset($bind_data);
									$bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
									$bind_data['PROGR']=$es_progr;
									$bind_data['VISITNUM_PROGR']=$vprogr;
									//$sql2->set_sql($query_data);
									$sql2->exec($query_data,$bind_data);//binded
									$sql2->get_row();
									$date.=$sql2->row['FOTH'];
									}
									if ($last_progr+1!=$es_progr)
									while ($last_progr<$es_progr-1){
									$last_progr++;
									$n_progr=$last_progr;
									$img="to_be_comp.gif";
										$form_alt=str_replace(".xml", ".xml", $es_val['XML']);
									if (!file_exists($xml_dir."/".$form_alt)) $form_alt=$es_val['XML'];
										$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$form_alt."{$agg_param}\">";
									$nome_esame=$es_val['TESTO']." n. $n_progr";
									$file_form=$es_val['XML'];
										$form1= new xml_form();
										$form1->xml_form_by_file($xml_dir."/".$file_form);
										$f_table=$form1->form['TABLE'];
										$dateinv=Set_Ins_data($f_table,$esam, $n_progr, $in[$config_service['PK_SERVICE']]);
										if ($progr!=''){
										$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam and progr=:progr";
										$sql2=new query($conn);
										unset($bind_chiusa);
										$bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
										$bind_chiusa['VISITNUM']=$key;
										$bind_chiusa['ESAM']=$esam;
										$bind_chiusa['PROGR']=$progr;
										//$sql2->set_sql($sql_query);
										$sql2->exec($sql_query,$bind_chiusa);//binded
										if ($sql2->numrows>0){
										$sql2->get_row();
										if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare)</font>";
											//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare)</font>";
										}
										}
										$close_href="</a>";
										$img_tag="<img src=\"/images/$img\" border=\"0\">";
									$this->body.="{$header}
																	<tr>
																		 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																		</td>
																		<td class=\"sc4bis\" align=\"left\" width=\"50%\">$href".$nome_esame." $close_href<br/>
																		</td>
										<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
																		</td>
																		<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[0]</b><br/>
																		</td>
																	</tr>
																";
	
									}
								if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
										if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
										if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
										$n_progr=$es_progr;
										$file_form=$es_val['XML'];
								$form1= new xml_form();
										$form1->xml_form_by_file($xml_dir."/".$file_form);
										$f_table=$form1->form['TABLE'];
										$dateinv=Set_Ins_data($f_table,$esam, $n_progr, $in[$config_service['PK_SERVICE']]);
										if (isset($es_val['VAL_AGG'])) $nome_esame="{$es_val['TESTO']} {$date}";
										else {
										if ($date!='') $date=" n.{$n_progr} ($date)";
										$nome_esame=$es_val['TESTO']." $date";
										}
										if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
										$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."{$agg_param}\">";
										if ($es_progr!=''){
									}
										$close_href="</a>";
										$img_tag="<img src=\"/images/$img\" border=\"0\">";
										$this->body.="{$header}
																	<tr>
										<td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																		</td>
										<td class=\"sc4bis\" align=\"left\" width=\"50%\">$href".$nome_esame." $close_href<br/>
																		</td>
										<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
																		</td>
																		<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
																		</td>
																	</tr>
										";
	
										}
	
								foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
										if ($es_val_corr['CORR']!='' && $es_val_corr['CORR']==$esam){
										# echo "<hr> Esame correlato per $esam : ".$esam_corr;
										$img="to_be_comp.gif";
											#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
										if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
										if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
										if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
										#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
										$dtp='';
										$query_data="select to_char({$es_val_corr['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val_corr['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and  progr=:progr";
										#echo "<hr>$query_data";
										unset($bind_data);
										$bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
										$bind_data['PROGR']=$es_progr;
										//$sql2->set_sql($query_data);
										$sql2->exec($query_data,$bind_data);//binded
										$sql2->get_row();
										$date=$sql2->row['DATA'];
										if ($es_val['FOTH'])
										{
										$query_data="select {$es_val['FOTH']} as FOTH from {$GLOBALS['service']}_{$es_val['TOTH']} where codpat='{$in['CODPAT']}' and  progr='{$es_progr}'";
										#echo "<hr>$query_data";
											$sql2->set_sql($query_data);
										$sql2->exec();
										$sql2->get_row();
										$date.=$sql2->row['FOTH'];
										}
										//echo "<hr>$date<hr>";
										$n_progr=$es_progr;
										if ($date!='') 	$dtp=" n.{$n_progr} ($date)";
										$nome_esame=$es_val_corr['TESTO']." $dtp";
										$file_form=$es_val_corr['XML'];
										$form1= new xml_form();
										$form1->xml_form_by_file($xml_dir."/".$file_form);
										$f_table=$form1->form['TABLE'];
										$dateinv=Set_Ins_data($f_table,$esam_corr, $es_progr, $in[$config_service['PK_SERVICE']]);
										if ($progr!=''){
										$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam and progr=:progr";
										$sql2=new query($conn);
											//$sql2->set_sql($sql_query);
										unset($bind_chiusa);
										$bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
										$bind_chiusa['VISITNUM']=$key;
											$bind_chiusa['ESAM']=$esam;
										$bind_chiusa['PROGR']=$progr;
										$sql2->exec($sql_query,$bind_chiusa);//binded
										if ($sql2->numrows>0){
										$sql2->get_row();
										if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare)</font>";
												//if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare)</font>";
										}
										}
										//if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val_corr['XML']."\">";
										$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=".$es_val_corr['NUMBER']."&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
	
										$close_href="</a>";
										$this->body.="
											<tr>
										<td class=\"sc4bis\" width=\"10%\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
												</td>
												<td class=\"sc4bis\" align=\"left\" width=\"50%\">$href".$nome_esame." $close_href<br/>
												</td>
												<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
												</td>
												<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
												</td>
												</tr>
												";
									}
								}
								#echo "<hr>ultimo progr $es_progr";
								$last_progr=$es_progr;
							}
	
						}
										}
										//echo "<li>$key - $esam - ";
										//print_r($es_val);
										//echo "</li>";
										//print_r($this->esams[$key][$esam]['NEXT_ENABLED']);
										if (($es_val['RES'][$es_progr]['FINE']==1 || $es_val['RES'][$es_progr]['INIZIO']=='' || $es_val['NEXT_ENABLED']!='') && !isset($es_val['ALL_IN']) && !$es_val['RES'][$es_progr]['VISITCLOSE']){
										//print_r($es_val);
						if(!$this->true_false['configurato'])$this->testi['nuovo_inserimento']='Nuovo inserimento';
										if ($es_val['RES'][$es_progr]['INIZIO']!='') $next_progr=$es_progr+1;
										else $next_progr=$es_progr;
						$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."{$agg_param}\">";
						$close_href="</a>";
						if (!isset($form_alt) || $form_alt=='') $form_alt=$es_val['XML'];
										if ($es_val['CONT_FORM']!='yes' && $es_val['DISABLE_NEW']=='' && $in['USER_TIP']!='RO')$this->body.="
														<tr>
										<td class=\"sc4bis\" width=\"10%\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
										</td>
															<td class=\"sc4bis\" align=\"left\" width=\"50%\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$form_alt."\">{$this->testi['nuovo_inserimento']}: ".$es_val['TESTO']."</a><br/>
										</td>
															<td class=\"sc4bis\" align=\"left\" width=\"30%\">&nbsp;
															</td>
															<td class=\"sc4bis\" align=\"left\" width=\"10%\">&nbsp;
															</td>
														</tr>
												";
					}
				}
			}
		}
	
	
	/**
	 * Metodo per visualizzare le equery pending su un particolare paziente
	 * 
	 * Enter description here ...
	 * @param unknown_type $codpat
	 * @param unknown_type $open
	 * @return string
	 */
	function printEquery($codpat,$open=false){
		global $in;
		global $remote_userid;
		global $conn;
		global $service;
		//print_r($this);
		//TODO sistemare il binding
		$sql_query="
			select e.ID,
						e.REGISTRY,
				       e.ESAM,
				       e.VISITNUM,
				       e.VISITNUM_PROGR,
				       e.PROGR,
				       e.CODPAT,
				       e.CENTER,
				       e.TIPO_EQUERY,
				       C.DENOM,
				       E.CHIUSA,
				       to_char(E.CHIUSA_DT,'DD/MM/YYYY') CHIUSA_DT,
				       E.TO_BE_VALIDATE,
				       E.VALIDATA,
				       to_char(E.VAL_DT,'DD/MM/YYYY') VAL_DT,
				       E.VAL_USERID,
				       to_char(E.QUEST_DT,'DD/MM/YYYY') QUEST_DT,
				      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
				       to_char(E.CHIUSA_DT,'DD/MM/YYYY') CHIUSA_DT
				  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
				 where c.center = e.center
				   and uc.center = c.center
				   and uc.userid = '{$remote_userid}'
	         and e.codpat={$codpat}
				   order by  e.CENTER,e.TIPO_EQUERY,e.ID";
	
		$sql = new query ( $conn );
		$sql->set_sql ( $sql_query );
		$sql->exec ();
			
		if ($sql->numrows == 0)
		{
			$html="<table border=0 cellpadding=0 cellspacing=2 width=95% align=center><td class='int' colspan=9 align=center><b>&nbsp;Non ci sono eQuery per questo paziente.</b>
											</td> </table";
		}
		else
		{
			if ($open)
			$html="<h4 style='text-align:center;'>Equery aperte in corso</h4>
				<table border='0px' cellpadding='0px' cellspacing='2px' width='95%' align='center'>
					<tr>
						<th class='int'>ID</th>
						<th class='int'>Codice Paziente</th>
						<th class='int'>Tipo eQuery</th>
						<th class='int'>Visita</th>
						<th class='int'>Esame</th>
						<th class='int'>Data domanda</th>
						<th class='int'>Risposta</th>
						<th class='int'>Data risposta</th>
						<th class='int'>Modifica</th>
					</tr>
			";
			if (!$open){
				$html="<h4 style='text-align:center;'>Equery aperte in corso</h4>
				<table border='0px' cellpadding='0px' cellspacing='2px' width='95%' align='center'>
					<tr>
						<th class='int'>ID</th>
						<th class='int'>Codice Paziente</th>
						<th class='int'>Tipo eQuery</th>
						<th class='int'>Visita</th>
						<th class='int'>Esame</th>
						<th class='int'>Data domanda</th>
						<th class='int'>Risposta</th>
						<th class='int'>Data risposta</th>
						<th class='int'>Data chiusura</th>
						<th class='int'>Modifica</th>
					</tr>
			";			
			}
			$old_center='';
			while ($sql->get_row()){
				$visita=$this->visitnums[$sql->row['VISITNUM']]['TEXT'];
				$esame=$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
				$link_="<a href=\"index.php?eQuery&eform&ID={$sql->row['ID']}\">{$sql->row['ID']}</a>";
				$link_stat="<a href=\"index.php?eQuery&eform&ID={$sql->row['ID']}&VIS=1\">Visualizza</a>";
				if($sql->row['TIPO_EQUERY']==1)
				{
					$tipo_equery="Modifica dati";
				}
				else
				{
					if($sql->row['TIPO_EQUERY']==2)
					$tipo_equery="Quesito clinico";
					else
					$tipo_equery="Classificazione non effettuata";
				}
					
				global $config_service;
				if ($sql->row['TO_BE_VALIDATE']=='1' && $in['USER_TIP']=='DM' && $sql->row['VAL_DT']=='') {
					$form="&amp;form={$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML']}";
					$link_validazione="
						<a href=\"index.php?CENTER={$sql->row['CENTER']}&amp;{$config_service['PK_SERVICE']}={$sql->row[$config_service['PK_SERVICE']]}&amp;ESAM={$sql->row['ESAM']}&amp;PROGR={$sql->row['PROGR']}&amp;VISITNUM={$sql->row['VISITNUM']}&amp;VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}{$form}\">Modifica i dati della form</a>
						";
				}
				if ($sql->row['TO_BE_VALIDATE']=='1' && $sql->row['VAL_DT']=='' && $in['USER_TIP']!='DM'){
					$link_validazione='Modifica da effettuare';
				}
				if ($sql->row['TO_BE_VALIDATE']=='0'){
					$link_validazione='Modifica non necessaria';
				}
				if ($sql->row['TO_BE_VALIDATE']==''){
					$link_validazione='---';
				}
				if ($sql->row['TO_BE_VALIDATE']=='1' && $sql->row['VAL_DT']!=''){
					$sql_umod=new query($conn);
					$sql_umod_text="select AZIENDA_ENTE||'-'||NOME||' '||COGNOME||' ('||USERID||')' as UMOD  from ANA_UTENTI_1  where  USERID='{$sql->row['VAL_USERID']}'";
					$sql_umod->set_sql($sql_umod_text);
					$sql_umod->exec();
					$sql_umod->get_row();
	
					$link_validazione=$this->testo("ChangeMadeAt")." ".$sql->row['VAL_DT']."<BR> da ".$sql_umod->row['UMOD'];
				}
					
				if ($old_center!=$sql->row['DENOM'])
				{
					$old_center=$sql->row['DENOM'];
					if ($open){
						$html.="<tr><td class=input colspan=9 align=center>
					<b>{$sql->row['DENOM']} ({$sql->row['CENTER']})</b></tD></tr>
	      ";
			  }
			  else {
			  	$html.="<tr><td class=input colspan=10 align=center>
					<b>{$sql->row['DENOM']} ({$sql->row['CENTER']})</b></tD></tr>
	      ";
			  }
				}
				$quest_status="<b><font color=\"#FF0000\">No</font></b>";
				if($sql->row['ANS_DT']!='')$quest_status="<b>Si</b>";
				$quest_status.="<br>".$link_stat;
	
				if ($open){
					$html.="
					<tr>
						<td class=sc4bis align=center>$link_</td>
						<td class=sc4bis>{$sql->row['CODPAT']}</td>
						<td class=sc4bis>$tipo_equery</td>
						<td class=sc4bis>$visita</td>
						<td class=sc4bis>$esame</td>
						<td class=sc4bis>{$sql->row['QUEST_DT']}</td>
						<td class=sc4bis align=center>$quest_status</td>
						<td class=sc4bis>{$sql->row['ANS_DT']}</td>
						<td class=sc4bis align=center>$link_validazione</td>
					</tr>
						";
				}
				else
				$html.="
					<tr>
						<td class=sc4bis align=center>$link_</td>
						<td class=sc4bis>{$sql->row['CODPAT']}</td>
						<td class=sc4bis>$tipo_equery</td>
						<td class=sc4bis>$visita</td>
						<td class=sc4bis>$esame</td>
						<td class=sc4bis>{$sql->row['QUEST_DT']}</td>
						<td class=sc4bis align=center>$quest_status</td>
						<td class=sc4bis>{$sql->row['ANS_DT']}</td>
						<td class=sc4bis>{$sql->row['CHIUSA_DT']}</td>
						<td class=sc4bis align=center>$link_validazione</td>
					</tr>
						";
			}
			$html.="</table>";
		}
	
		return $html;
			
	}
	
}


class legend_armonia extends legend_prototype {

	/**
	* Costruttore
	*
	* @return legend_prototype
	*/
	function legend_armonia() {
		global $in;
		$this->html_legend_visita = "<br><br>
 	<table class=\"bordi\" width=\"40%\" align=\"center\">
 <tr>
  <td width=\"8%\" colspan=\"2\">&nbsp;&nbsp;<b>Legenda</b></td>
 </tr>
       <tr> 
          <TD class=\"sc4bis\" width=\"5%\"><IMG src=\"/images/to_be_comp.gif\" border=0> </TD>
          <TD class=\"sc4bis\" width=\"95%\">Scheda da compilare. Cliccare sul quadratino vuoto per compilare la scheda</TD></TR>
        <TR>
          <TD class=\"sc4bis\"><IMG src=\"/images/saved.gif\" border=0> </TD>
          <TD class=\"sc4bis\">Scheda parzialmente compilata. Cliccare sul check rosso per completare o modificare i dati</TD></TR>
        <TR>
          <TD class=\"sc4bis\"><IMG src=\"/images/submitted.gif\" border=0> </TD>
          <TD class=\"sc4bis\">Scheda completata e inviata. Non &egrave; possibile modificarla. Cliccare sul check verde per visualizzare i dati inseriti</TD></TR>
        </TBODY>
</TABLE>
 	";

		$this->html_legend_lista = "<br><br>
 	<table class=\"bordi\" width=\"40%\" align=\"center\">
 <tr>
  <td width=\"8%\" colspan=\"2\">&nbsp;&nbsp;<b>Legenda</td>
 </tr>
 <tr>
  <td class=\"sc4bis\" width=\"5%\"><img src=\"/images/f_bianca.gif\" border=\"0\" ></td>
     <td class=\"sc4bis\" width=\"95%\">Schede da compilare. Cliccare sulla freccia bianca per iniziare l'inserimento</td>
 </tr>
 <tr>
  <td class=\"sc4bis\"><img src=\"/images/f_gialla.gif\" border=\"0\" ></td>
     <td class=\"sc4bis\">Alcune schede devono ancora essere inserite. Cliccare sulla freccia gialla per proseguire l'inserimento</td>
 </tr>
 <tr>
  <td class=\"sc4bis\"><img src=\"/images/f_verde.gif\" border=\"0\"></td>
     <td class=\"sc4bis\">Tutte le schede sono state compilate. Cliccare sulla freccia verde per visualizzare i dati inseriti</td>
 </tr>
 
 </table>";
		if ($in ['USER_TIP'] == 'DM') {
			$this->html_legend_visita = "
			<br>	<table class=\"bordi\" width=\"40%\" align=\"center\">
 <tr>
  <td width=\"8%\" colspan=\"2\">&nbsp;&nbsp;<b>Legenda</b></td>
 </tr>
        
       
        <tr> 
          <TD class=\"sc4bis\" width=\"5%\"><IMG src=\"/images/to_be_comp.gif\" border=0> </TD>
          <TD class=\"sc4bis\" width=\"95%\">Scheda da compilare. Cliccare sul quadratino vuoto per compilare la scheda</TD></TR>
        <TR>
          <TD class=\"sc4bis\"><IMG src=\"/images/saved.gif\" border=0> </TD>
          <TD class=\"sc4bis\">Scheda parzialmente compilata. Cliccare sul check rosso per completare o modificare i dati</TD></TR>
        <TR>
          <TD class=\"sc4bis\"><IMG src=\"/images/submitted.gif\" border=0> </TD>
          <TD class=\"sc4bis\">Scheda completata e inviata. Non &egrave; possibile modificarla. Cliccare sul check verde per visualizzare i dati inseriti</TD></TR>
        </TBODY>
</TABLE>
		 	";
			$this->html_legend_lista = "
			<br> 	<table class=\"bordi\" width=\"40%\" align=\"center\">
 <tr>
  <td class=\"sc4bis\" width=\"5%\"><img src=\"/images/f_bianca.gif\" border=\"0\" ></td>
     <td class=\"sc4bis\" width=\"95%\">Schede da compilare. Cliccare sulla freccia bianca per iniziare l'inserimento</td>
 </tr>
 <tr>
  <td class=\"sc4bis\"><img src=\"/images/f_gialla.gif\" border=\"0\" ></td>
     <td class=\"sc4bis\">Alcune schede devono ancora essere inserite. Cliccare sulla freccia gialla per proseguire l'inserimento</td>
 </tr>
 <tr>
  <td class=\"sc4bis\"><img src=\"/images/f_verde.gif\" border=\"0\"></td>
     <td class=\"sc4bis\">Tutte le schede sono state compilate. Cliccare sulla freccia verde per visualizzare i dati inseriti</td>
 </tr>
 </table>";
		}

	}
}







/**
 * Funzioni di servizio uguali a tutti i servizi
 */

function Make_pdf(){
	global $in;
	global $conn;
	global $service;
	global $xml_dir;
	if ($in['ajax_call']=='')
	{
		$xml_form=new xml_form();
		$form=$in['form'];
		$xml_form->xml_form_by_file($xml_dir.'/'.$form);
		$xml_form->closed_form();
		$xml_form->close_form();
		$body=$xml_form->body;
		//   echo $body."<hr>";
		Set_formAE($body);
		if (!preg_match("/^997/", $remote_userid)) Invia_fax_sae();
		//   die();
		//

	}
}



function armonia_invia_fax()
{
	global $conn;
	global $xml_dir;
	global $in;
	global $resp;
	global $telreps;
	global $remote_userid;
	//  echo "Invia Fax <hr>";
	$f_dir=$xml_dir."/documents/";
	$fd=$in['CENTER']."_".$in['CODPAT']."_".$in['VISITNUM']."_".$in['ESAM']."_".$in['PROGR'];
	$user='aifa-reuma@aifa.it';
	$password='antireumatici';
	$fname=$f_dir."pdf".$fd.".pdf";
	//echo $fname."<hr>";
	$id_servizio='';
	$oggetto='SEGNALAZIONE DI SOSPETTA ADR';

	$destinazione[0]['receiver']=$resp;
	//se sono in PROD
	if ((preg_match("/agenziafarmaco/i",$_SERVER['SERVER_NAME']))){
		$oggetto='SEGNALAZIONE DI SOSPETTA ADR';
		$destinazione[0]['faxnumber']=$telreps;
		$destinazione[0]['company_receiver']="Responsabile di farmacovigilanza ";
	}
	else{
		$oggetto='TEST - SEGNALAZIONE DI SOSPETTA ADR';
		$destinazione[0]['faxnumber']="0516171365";
		$destinazione[0]['company_receiver']="CINECA";
	}

	$test=0;
	$priorita=1;
	$data_sched='';
	$commento='4 pagine';
	$esito_email='a.bosio@cineca.it';
	// echo $user." ".$password." ".$fname." ".$id_servizio." ".$oggetto."<hr> ";
	// print_r($destinazione);
	// echo $test." ".$priorita." ".$data_sched." ".$commento." ".$esito_email."<hr> ";
	$result=send_fax($user, $password,$fname,$id_servizio,$oggetto,$destinazione, $test, $priorita, $data_sched, $commento,$esito_email);
	//  echo $result."<hr>";
	////

	$sql=new query($conn);

	$query="insert into FAX_LOG (CODPAT, CENTER, FNAME, FDATE, USERID, RESP, TELRESP, UIN) values ( '".$in[CODPAT]."','".$in[CENTER]."','".$fname."',sysdate,'".$remote_userid."','".$resp."','".$telreps."','".$result."')";
	//echo $query."<hr>";
	$sql->set_sql($query);
	$sql->ins_upd();
	$conn->commit();

	//	if ($result <= 0) {
	//		echo "messaggio di errore<hr>";
	//		echo fax_geterror($result);
	//		echo "<hr>";
	//	}else{
	//		echo "nordine con UIN $result inserito<hr>";
	//	}
}

function Set_Ins_data($f_table,$esam, $progr, $codpat){
	global $conn;
	$dateinv=array('','');

//TODO sistemare il binding!!!
	$query_invio="select a.NOME||' '||a.COGNOME||' '||a.AZIENDA_ENTE NOME,
			(case when MODDT is not null then to_char(MODDT, 'DD/MM/YYYY')  else to_char(INSERTDT, 'DD/MM/YYYY') end) as DATAINS
			from $f_table t,{$GLOBALS['service']}_COORDINATE c, ANA_UTENTI_1 a where t.codpat=
			'$codpat' 
			and a.userid=t.USERID_INS 
			and t.codpat=c.codpat 
			and t.esam=c.esam 
			and t.visitnum=c.visitnum 
			and t.VISITNUM_PROGR=c.VISITNUM_PROGR
			and t.PROGR=c.PROGR 
			and t.PROGR=$progr 
			and t.esam=$esam";
	//				echo "<hr>".$query_invio."<hr>";
	$sql_invio=new query($conn);
	$sql_invio->set_sql($query_invio);
	$sql_invio->exec();
	$sql_invio->get_row();
	if ($sql_invio->row['NOME']!='') $dateinv[0].=$sql_invio->row['NOME'];
	if ($sql_invio->row['DATAINS']!='') $dateinv[1].=$sql_invio->row['DATAINS'];
	return $dateinv;
}



function var_glob($value) {
	global $in;
	global $inputval;
	if (isset ( $inputval [$value] ) && $inputval [$value] != '')
	return $inputval [$value];
	if (isset ( $in [$value] ) && $in [$value] != '')
	return $in [$value];
	if (isset ( $GLOBALS [$value] ) && $GLOBALS [$value] != '')
	return $GLOBALS [$value];
}



/**
 * 
 * Funzione per segnalare gli errori
 * 
 * @param unknown_type $user
 * @param unknown_type $error
 * @param unknown_type $error_spec
 */
function error_page($user, $error, $error_spec){
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;

	$eol=PHP_EOL;
	$email_admin="g.tufano@cineca.it,s.scalise@cineca.it";
	if($error_spec==''){
		$error_spec=ocierror($conn);
	}


	#echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
	$today = date("j/m/Y, H:m:s");
	$ajax=isset($in['ajax_call'])?"Si":"No";
	$php_debug=debug_backtrace();
	//$php_debug2=var_export($php_debug,true);
	//$php_debug2="<table><tr><th>PHP DEBUG</th></tr><tr><td>$php_debug2</td></tr></table>";
	$i_e_debug=var_export($insert_errors,true);
	$i_e_debug="<table><tr><th>I.E. DEBUG</th></tr><tr><td>$i_e_debug</td></tr></table>";

	if (is_array($error_spec))
	foreach ($error_spec as $key => $val)
	$spec.="\n $key : $val";
	else
	$spec = $error_spec;

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
*DEBUG INFO: ".$debug_info_str.
"	

".$php_debug."

".$i_e_debug;


	$headers  = " ERROR_".$service."@{$_SERVER['SERVER_NAME']}$eol";
	//	$headers .= "Content-type: text/html\r\n";
	$headers .= "Content-type: text/plain; charset=utf-8$eol";
	//	$debug_info=nl2br(var_export( debug_backtrace(), TRUE ) );

	$prod="";
	if(preg_match("/\.agenziafarmaco\./", $_SERVER['HTTP_HOST'])){
		if(preg_match("/too large/i",$spec)) {
			$edo=substr($spec,strpos($spec,"value too large for column")+28,strlen($spec));
			$edo=substr($edo,0,strpos($edo,"(actual:"));
			$edo=substr($edo,strrpos($edo,".")+1);

			$body="<h2 style=\"color:red;\">Valore troppo grande per il campo: ".$edo."</h2>";

		}
		$body.="<h3>$error_spec.<br /> 
Contattare il supporto tecnico se l'errore &egrave; imprevisto e si dovesse riverificare. Specificare il messaggio di errore mostrato.</h3>";
		$prod="_!PRODUZIONE!";
	} else {
		print_r($error_spec);
		$debug = debug_backtrace();
		//		foreach($debug as $key => $val) {
		//			foreach($val  as $k => $v) {
		//				$debug_info.=$k." ".$v."<br />";
		//			}
		//		}
		$body="<h2>ERRORE DEVEL</h2><h3>$error</h3><br />$debug_info";
		//		print_r($debug[0]);
		//		$debug_info=var_export($debug,true);
	}
	mail($email_admin, "Errore[".$in['remote_userid']."]$prod",$alltxt, $headers);
	$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	die($filetxt);
}



