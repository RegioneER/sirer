<?
require_once "libs/http_lib.inc";
include_once "libs/db.inc";
include_once "libs/xml_parser_wl.inc";
include_once "libs/HTML_Parser.inc";
include_once "libs/page.inc";
include_once "libs/vlist.inc";
include_once "libs/list.inc";
include_once "libs/legend.inc";
include_once "libs/esams_list.inc";
include_once "libs/form.inc";
include_once "libs/study_prototype.inc";
include_once "libs/xmrwf.inc.php";
include_once "libs/equery.inc";
include_once "/http/lib/wkpdf/WKPDF.php";
include_once "send_email_common.inc";



//Include integrazioni
//LUIGI: disattivo vecchia tipologia emendamento
//include_once "libs/integrazioni.inc";
//include_once "integrazioni.php";


include_once "study.inc.mproto.php";
$xdebugQueryCount=0;
define ('AREA_OFFSET',10000000);

$editing=false;
$email_admin="g.contino@cineca.it";
$root=$_SERVER['DOCUMENT_ROOT'];
$dir=$_SERVER['PATH_TRANSLATED'];
$dirs=explode("/", $dir);
$dir='';
for ($i=0;$i<count($dirs)-1;$i++){
	$dir.=$dirs[$i]."/";
}
$dir=rtrim($dir, "/");
if (!is_dir($GLOBALS['dir']."/log_trace")) {
	mkdir($GLOBALS['dir']."/log_trace", 0777);
	chmod($file_log, 0777);
	chmod($GLOBALS['dir']."/log_trace", 0777);
}
$xml_dir=$dir."/xml";
$file_log=$dir."/log_trace/".strtoupper($in['remote_userid']).".log";
$log_conn=new dbconn();
$q_log=new query($log_conn);
$sql="select max(id) as ID from sessions";
$q_log->set_sql($sql);
$q_log->exec();
$q_log->get_row();
$session_number=$q_log->row['ID']+1;
$log_str="<session $session_number><hr><b>Script : index.php</b><br><b>Parametri di input</b><ul>";
foreach($in as $key=> $val) $log_str.="<li>$key: $val</li>";
$log_str.="</ul></session>";
$handle = fopen($file_log, 'a+');
fwrite($handle, $log_str);
fclose($handle);
$sql="insert into sessions(id, userid, data) values($session_number, '".$remote_userid."', sysdate)";
$q_log->set_sql($sql);
$q_log->ins_upd();
$log_conn->commit();
$template_dir=$dir;

$config_service['SHOW_MANDATORY_ON_HIDE']=true;

//$config_service['FILE_DOC_NA'] = 1;

//INTEGRAZIONI - Equery
//LUIGI: disattivo vecchia tipologia emendamento
//$config_service['eQuery']=1;
//$config_service['eQuerySpec']['Integrazione']['ON']=true;

//PERSONALIZZIONE PER SERVIZIO
//stati nei quali non e' prevista l'approvazione delle integrazioni
//$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][4]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_ESAM'][0]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][2]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][4]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][5]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][9]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][10]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][20]=true;

//Visita dell'EMENDAMENTO
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT']['EME_VISIT'][20]=true;

//profilo di chi fa le integrazioni (GIULIO se provo a settare la SGR come richiedente, poi non si vedono le modifiche richieste con il punto esclamativo)
$config_service['eQuerySpec']['Integrazione']['ROLE']="Segreteria CE";
//profilo di chi approva le integrazioni EDO
$config_service['eQuerySpec']['Integrazione']['VALIDATOR']="Segreteria CE";
//stati nei quali si puo' integrare la domanda EDO
$config_service['eQuerySpec']['Integrazione']['APPROV'][1]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][2]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][3]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][4]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][5]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][6]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][7]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][8]=true;
//visite ed exam da tenere aperti in ogni caso
$config_service['eQuerySpec']['Integrazione']['KEEP_OPEN'][20][3]=true;

/*

//stati nei quali non e' prevista l'approvazione delle integrazioni
$config_service['eQuerySpec']['Integrazione']['NON_APPROV'][2]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][3]=true;
$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][4]=true;
//profilo di chi fa le integrazioni
$config_service['eQuerySpec']['Integrazione']['ROLE']="Azienda Farmaceutica";
//profilo di chi approva le integrazioni EDO

$config_service['eQuerySpec']['Integrazione']['VALIDATOR']="AIFA Unita Operativa";
//stati nei quali si pu? integrare la domanda EDO
$config_service['eQuerySpec']['Integrazione']['APPROV'][3]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][4]=true;
$config_service['eQuerySpec']['Integrazione']['APPROV'][5]=true;


$config_service['eQuerySpec']['Integrazione']['NON_APPROV_CONDITION']="select * from cp_ii_in_carico where stato_prat=2";

$config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][3]=true;

$config_service['eQuerySpec']['Integrazione']['ROLE']="Azienda Farmaceutica";

$config_service['eQuerySpec']['Integrazione']['VALIDATOR'][2]='Profilo Amministrativo';

$config_service['eQuerySpec']['Integrazione']['APPROV'][2]=true;
*/
//FINE INTEGRAZIONI

#CONFIGURAZIONI GIULIO AD-HOC
$config_service['SHOW_MANDATORY_ON_HIDE']=true;
#lascia i buchi nelle progressive
$config_service['ALLOW_BLANK_PROGR']=true;
#lascia i buchi nelle visite progressive
$config_service['ALLOW_BLANK_VPROGR']=true;

#Forzatura per il salavataggio dei doc generali, doc centro specifici e centri a studio inviato in BD
$config_service['ALWAYS_SAVEABLE']['0']['2']=true; #documenti generali
$config_service['ALWAYS_SAVEABLE']['0']['10']=true; #centri
$config_service['ALWAYS_SAVEABLE']['1']['23']=true; #documenti centro-specifici
$config_service['ALWAYS_SAVEABLE']['0']['6']=true; #farmaci studio interventistico
$config_service['ALWAYS_SAVEABLE']['0']['7']=true; #dispositivi studio interventistico
$config_service['ALWAYS_SAVEABLE']['0']['15']=true; #farmaco studio osservazionale
$config_service['ALWAYS_SAVEABLE']['0']['5']=true; #tessuti umani
$config_service['ALWAYS_SAVEABLE']['0']['18']=true; #dispositivi studio osservazionale

$conn=new dbconn();
$sql=new query($conn);

//$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'");
$sql->ins_upd();


$config_service['PRJ']=100;

$config_service['Menu_paziente']='Menu Studio';
$config_service['Lista_schede']='Dettaglio Studio';
$config_service['Patients_list']='Lista Studi';
$config_service['Torna_lista_schede']='Torna al dettaglio Studio';


if ($config_service['eQuerySpec']['Integrazione']['ON']){
	eval("class xml_form_proto extends form_int_prototype{}"); // libs/integrazioni.inc
}
else eval("class xml_form_proto extends xml_form_prototype{}"); // libs/form.inc



class xml_form extends xml_form_proto{

	#GC 05/11/2014# Nuova gestione EME e riapertura schede. Funzione importata da study_prototype
	function open_form($force_open=false,$exclude_send_buttons=false, $equery=false) {
		
		$in = $this->session_vars;
		$conn = $this->conn;
		$inputval = $this->tb_vals;
		$service = $this->service;
		$config_service = $this->config_service;

//echo "Ruolo ".$this->config_service['eQuerySpec']['Integrazione']['ROLE']."<br>";
//echo "act ".$this->session_vars['WFact']."<br>";

		$template_form_html = '';
		if ($this->xmr) {
			if ($in [$config_service ['PK_SERVICE']] != 'next') {
				if (isset ( $in ['VISITNUM'] ) && isset ( $in ['ESAM'] )) {
					$sql_query = "select visitclose from {$service}_COORDINATE where VISITNUM=:visitnum and ESAM=:esam and VISITNUM_PROGR=:visitnum_progr and {$config_service['PK_SERVICE']}=:pk_service";
					$sql = new query ( $conn );
					unset($bind);
					$bind['VISITNUM']=$in['VISITNUM'];
					$bind['ESAM']=$in['ESAM'];
					$bind['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
					$bind['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
					//$sql->set_sql ( $sql_query );
					$sql->exec ($sql_query,$bind);//binded
					$sql->get_row ();
					if ($sql->row ['VISITCLOSE'] == 1 && $in ['USER_TIP'] == 'DE' && !$force_open) {
						error_page ( $in ['remote_userid'], $this->testo("visitIsClosed"), "" );
					}
				}
			}
		}
		$editing = true;
		if($this->config_service['lang']=="en")$lang=1;
		else $lang=0;
		$this->salva_js = "
		  		function salva_f(){
		  		cf();
		  		f=document.forms[0];
					el=f.elements;

					specifiche='A=ON&L=$lang&F=0';
		  		c1='';
		  		";
		$this->invia_js = "
		  		function invia_f(ajax){
		  		cf();
		  		if (ajax==undefined) ajax=true;
		  		f=document.forms[0];
					el=f.elements;
					specifiche='A=ON&L=$lang&F=0';
		  		c1='';
		  		";
		$this->check_js = '
		  		function cf(){
		  		var el;
		  		var f;
		  		f=document.forms[0];
					el=f.elements;
		  		document.forms[0].action=\'\';
		  		';
		$colonne = $this->form ['COLS'];
		$sysdate = date ( "dmY" );
		if (isset($_GET['link_to']) && $_GET['link_to']!='') $this->form ['LINK_TO']=$_GET['link_to'];
		$this->percorso_agg= "&nbsp;&gt;&nbsp;<b>" . $this->form ['TITOLO'] . "</b>";
		if ($equery){
			$showAsOpen=false;
			$sql_query="select equery_int from {$this->service}_eq where stato in (0,2) and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";
			$sql=new query($this->conn);
			if ($sql->get_row($sql_query)) $equery_int=$sql->row['EQUERY_INT'];
			else $equery_int=0;
			
			$sql_query_2="select EQ_ACTION,INIZIO,FINE from {$this->service}_COORDINATE where PROGR=:progr and VISITNUM=:visitnum and ESAM=:esam and VISITNUM_PROGR=:visitnum_progr and {$config_service['PK_SERVICE']}=:pk_service";
			$bind['VISITNUM']=$in['VISITNUM'];
			$bind['ESAM']=$in['ESAM'];
			$bind['PROGR']=$in['PROGR'];
			$bind['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
			$bind['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
			
			
			if ($sql->get_row($sql_query_2, $bind) && $sql->row['INIZIO']==1 ){
				
				$eq_action=$sql->row['EQ_ACTION'];
				if ($sql->row['EQ_ACTION']==1) $showAsOpen=true;
				else $showAsOpen=false; 
			}else $showAsOpen=true;
			
			
			if ($equery_int!='') {

				if(strtolower($this->config_service['lang'])=='en'){
					$string_text="Warning! fields with the symbol <img src=\"images/eq_img.png\" width=20px> has been modified";
				}else{
					$string_text="Attenzione! i campi contrassegnati con il simbolo <img src=\"images/eq_img.png\" width=20px> hanno subito modifiche";
				}

				$note_eq="
				<div style='font-align:center;color:red;font-weight:bold'>
				$string_text
				</div>
				";
			}
		}
		$in ['form']=htmlentities($in ['form']);
		$this->body = $note_eq.'
					   <form method="post" class="niceform" action="index.php" enctype="multipart/form-data"  onsubmit="return false;" onKeypress="if (event.keyCode==13) return false;">
		               <input type="hidden" name="' . $this->form ['TABLE'] . '"/>
		               <input type="hidden" name="form" value="' . $in ['form'] . '"/>
		               <input type="hidden" name="link_to" value="' . $this->form ['LINK_TO'] . '"/>
		               <table align="center" border="0" cellpadding="2" cellspacing="2" width="98%">
									  <tbody>
									  	<tr>
									  		<td>
									 ';

		$width = 100 / ($colonne * 2);
		if ($this->form ['TEMPLATE'] != '' && $in ['genera_template_html'] != "si")
		$template = file_get_contents ( "xml/{$this->form['TEMPLATE']}" );
		else {
			$this->body .= '
			       				 <table class="sf table table-bordered" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
			       				 <!-- CAMPI -->' . $testo_rev;
			$template_form_html = '
				<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
			       				 <!-- CAMPI -->';
			$template = '';
			for($i = 0; $i < $colonne; $i ++) {
				$this->body .= "<td style=\"border: 0px solid #ddd;\" width=\"" . $width . "%\">&nbsp;</td><td style=\"border: 0px solid #ddd;\" width=\"" . $width . "%\">&nbsp;</td>";
				$template_form_html .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
			}
			$this->body .= "</tr>";
			$template_form_html .= "</tr>";

		}

		$c = 0;
		foreach ( $this->fields as $i => $val ) {
			
			if ($val ['CONDITION'] != '')
			$condition_array [count ( $condition_array )] = $val ['CONDITION'];
			if($val ['TYPE']=="file_cme" || $val ['TYPE']=="file_doc") {
				$file_doc_eq['VAR']=$val['VAR'];
				$file_doc_eq['THREAD']=$val['THREAD'];
				$file_doc_eq['TOPIC']=$val['TOPIC'];
				$files_doc[]=$file_doc_eq;
				/*
			        [TYPE] => file_doc
				    [VAR] => COMUNICAZIONI_FILE
				    [THREAD] => Comunicazione
				    [TOPIC] => Communications to AIFA
				 */
			}
		}
		$condition_array = array_unique ( $condition_array );
		
		if ($equery){

			if($equery_int!="" || $equery_int!="0") {

			$_GET['VISITNUM_PROGR']-=0;

			if(isset($_GET['PROGR'])) $progr=$_GET['PROGR'];
			else $progr=1;

			$sql_query="select * from {$this->service}_eqfield where
				eq_int=:eq_id
				and esam=:esam
				and visitnum=:visitnum
				and visitnum_progr=:visitnum_progr
				and progr=:progr
				and {$this->PK_SERVICE}=:pk_service
				";

//			echo( $sql_query."<br>");
			unset($bind);
			$bind['EQ_ID']=$equery_int;
			$bind['ESAM']=$_GET['ESAM'];
			$bind['VISITNUM']=$_GET['VISITNUM'];
			$bind['VISITNUM_PROGR']=$_GET['VISITNUM_PROGR'];
			$bind['PROGR']=$progr;
			$bind['PK_SERVICE']=$_GET[$this->PK_SERVICE];
			$sql->exec($sql_query,$bind);//binded
			
			//------------------------------------
			$id_tipo_ref=$config_service['PRJ']*100000+$_GET[$this->PK_SERVICE];
			
//			print_r($files_doc);

			foreach($files_doc as $l=>$allegati) {
			unset($bind_array);
			$topic=preg_replace("/'/", "''", $allegati['TOPIC']);
			if ($topic!='') {
				$topic_where="topic=:topic";
				$bind_array['TOPIC']=$topic;
			}
			else $topic_where="topic is null";	
				
			$thread=$allegati['THREAD'];
			$thread=preg_replace("/'/", "''", $thread);

			$thread=str_replace("à","%",$thread);
			$thread=str_replace("è","%",$thread);
			$thread=str_replace("ì","%",$thread);
			$thread=str_replace("ò","%",$thread);
			$thread=str_replace("ù","%",$thread);
		
			$bind_array['ID_TIPO_REF']=$id_tipo_ref;
			$bind_array['TITOLO']=$thread;
			//PENULTIMO!!!
			$sql_query="
				select
				   d.id,
			       d.titolo as titolo,
			       d.autore,
			       d.data,
			       d.keywords as keywords,
			        (select
			            NOME_FILE
			           from docs d1
			        	where d1.tipo_doc='Doc_Area'
			        	and d1.id_tipo_ref=:id_tipo_ref
			        	and d1.id=
			         		(select max(d2.id) from docs d2
			         			where d2.tipo_doc='Doc_Area'
			        and d2.id_tipo_ref=:id_tipo_ref
			        and d2.id_ref=d.id and d2.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref=:id_tipo_ref
			        and d99.id_ref=d.id
			        ))
			        ) as nome_file,
			       (
			        select
			          max(d3.id)
			           from docs d3
			        where d3.tipo_doc='Doc_Area' and d3.id_tipo_ref=:id_tipo_ref and d3.id_ref=d.id and d3.id<(select
			          max(d99.id)
			           from docs d99
			        where d99.tipo_doc='Doc_Area'
			        and d99.id_tipo_ref=:id_tipo_ref
			        and d99.id_ref=d.id
			        )
			        ) as last_ver
	
			        from docs d
			        where
			        	tipo_doc='Doc_Area'
			        	and id_tipo_ref=:id_tipo_ref
			        	and id=id_ref
			        	and $topic_where
						and d.titolo like :TITOLO
					";
//			echo( "<br>".$sql_query."<br>1172");
			$sql2=new query($this->conn);
			$sql2->exec($sql_query, $bind_array);//binded
			$sql2->get_row();
			//piccolo trick per i documenti allegati
			foreach($files_doc as $key => $val) {
				if($sql2->row['KEYWORDS']==$val['VAR']) {
					$this->old_values[$val['VAR']]=$sql2->row['LAST_VER'];
					$this->old_values_docs_nomi[$val['VAR']]=$sql2->row['NOME_FILE'];
				}
			}
			
			} //chiudo qua foreach $c
			//------------------------------------
			}
			
			foreach ($this->tb_vals as $k=>$v)  {
				$this->old_values[$k]=$v;
			}

			while ($sql->get_row()){
				$this->tb_vals[$sql->row['FIELD']]=$sql->row['VALORE'];
			}
		}
		foreach ( $this->fields as $i => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
			$field_type = "field_{$val['TYPE']}";
			else
			$field_type = "field";
			
			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				include_once $this->config_service['field_lib'] . $field_type . ".inc";
			} else
			include_once "libs/{$field_type}.inc";
			$field_obj = new $field_type ( $this, $i, $this->conn, $this->tb_vals, $this->session_vars, $this->service, $this->errors );
			if (isset($condition_array) && is_array($condition_array)) foreach ( $condition_array as $key => $val ) {
				if ($val == $field_obj->id)
				$field_obj->attributes ['CALL_CF'] = "yes";
			}
			if ($inputval [$this->form ['READONLY']] == 1 && $inputval [$field_obj->id] != '') {

				if ($field_obj->id != $this->form ['READONLY_COMM']) {

					$field_obj->attributes ['DISABLED'] = 'yes';
				}
			}
			if ($showAsOpen) $field_obj->make_open_html ();
			else $field_obj->make_open_html ($equery);
			if ($template == '') {
				if ($field_obj->attributes ['HIDE'] == 'yes') {
					if (isset ( $field_obj->attributes ['NAME'] ) && $field_obj->attributes ['NAME'] != '') {
						$template_form_html .= "</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>";
						$this->body .= "</tr>\n<tr id='tr_{$field_obj->attributes['NAME']}'>";
					} else {
						$template_form_html .= "\n<tr id='tr_{$field_obj->attributes['VAR']}'>";
						$this->body .= "\n<tr id='tr_{$field_obj->attributes['VAR']}'>";
					}
					$c = 0;
				}

				if ($colonne == $c) {
					$template_form_html .= "</tr>\n";
					$this->body .= "</tr>\n";
					$c = 0;
				}
				if ($c == 0 && $field_type != 'field_hidden' && $field_obj->attributes ['HIDE'] != 'yes') {
					$this->body .= "<tr>";
					$template_form_html .= "<tr>";
				}
				#echo $c;
				if ($field_obj->attributes ['TYPE'] != 'hidden') {
					if ($field_obj->attributes ['COLS'] == '')
					$c ++;
					else {
						$c += $field_obj->attributes ['COLS'];

					}
				}
				if ($field_obj->attributes ['COLS'] == '')
				$field_obj->attributes ['COLS'] = 1;
				if ($field_obj->attributes ['COLSPAN'] == '')
				$field_obj->attributes ['COLSPAN'] = 1;
				$colspan = $field_obj->attributes ['COLS'] * $field_obj->attributes ['COLSPAN'];
				if ($field_obj->attributes ['TYPE'] != '') {
					if ($field_obj->attributes ['COLSPAN'] == 1) {
						if ($field_obj->attributes ['TYPE'] == 'hidden') {

							$template_form_html .= "<<{$field_obj->id}>>";
						} else
						$template_form_html .= "
				<td  class='destra' colspan=\"$colspan\" id=\"cell_{$field_obj->id}\"><<TESTO {$field_obj->id}>></td>
				<td  class='input' colspan=\"$colspan\" id=\"cell_input_{$field_obj->id}\"><<{$field_obj->id}>></td>
				";
					} else {
						if ($field_obj->attributes ['TYPE'] == 'hidden')
						$template_form_html .= "<<{$field_obj->id}>>";
						else
						$template_form_html .= "
					<td  class='input' colspan=\"$colspan\" id=\"cell_input_{$field_obj->id}\"><<TESTO {$field_obj->id}>><<{$field_obj->id}>></td>
					";
					}
				} else
				$template_form_html .= "\n" . $field_obj->html;

				$this->body .= "\n" . $field_obj->html;
			} else {
				$template = str_replace ( "<<{$field_obj->id}>>", $field_obj->input_field, $template );
				$template = str_replace ( "<<TESTO {$field_obj->id}>>", $field_obj->input_txt, $template );
			}
			$this->salva_js .= $field_obj->salva_js;
			$this->check_js .= $field_obj->check_js;
			$this->invia_js .= $field_obj->invia_js;
			$this->script_js .= $field_obj->script;
			if (! $field_obj->validata)
			$this->validata = $field_obj->validata;
			$controlli .= $field_obj->controlli;
		}
		$js_function_on_send = $this->form ['JS_FUNCTION'];
		if ($this->form ['JS_ONSAVE'] == "yes")
		$js_function_on_save = $this->form ['JS_FUNCTION'];
		else
		$js_function_on_save = $this->form ['JS_ONSAVE'];
		$js_function_on_load = $this->form ['LOAD'];
		if ($template == '') {
			$this->body .= "
		  <!--FINE CAMPI-->
		  ";
			$template_form_html .= "
			<!--FINE CAMPI-->
			</table>
			";
		}
		if ($in ['genera_template_html'] == "si") {
			die ( $template_form_html );
		}
		$this->onload = $js_function_on_load;
		$this->onload .= 'cf()';
		$this->check_js .= '
		  }';
		if($this->config_service['jquery']) $this->check_js .= '$(document).ready(function(){'.$this->script_js."
		});
		  ";
		$this->salva_js .= '
		  rc=contr(c1,specifiche);
			if (rc) {return false}
			' . $controlli . '
		  if (!rc){
		  ' . $js_function_on_save . '
		   document.forms[0].INVIOCO.value=\'0\';
		   document.forms[0].action=\'index.php\';
		    el=document.getElementsByTagName(\'TR\')
		   for (i=0;i<el.length;i++) el[i].style.display=\'\';
		   f=document.forms[0];
			 el=f.elements;
		   for (i=0;i<el.length;i++) el[i].disabled=false;
		   ajax_send_form(0);

		   }
		  }';
		  if($this->config_service['jquery2'])$contr="jContr";
		  else $contr="contr";
		$this->invia_js .= '
		   rc='.$contr.'(c1,specifiche);
				if (rc) {return false}
		   ' . $controlli . '
		   if (!rc){
			   ' . $js_function_on_send . '
			   document.forms[0].INVIOCO.value=\'1\';
			   document.forms[0].action=\'index.php\';
			    el=document.getElementsByTagName(\'TR\')
		   		for (i=0;i<el.length;i++) el[i].style.display=\'\';
			   f=document.forms[0];
				 el=f.elements;
			   for (i=0;i<el.length;i++) el[i].disabled=false;
			   if (document.forms[0].EQUERY_INT) {
			   	document.forms[0].submit();
			   		return;
				}
			   if (ajax) ajax_send_form(0);
			   else document.forms[0].submit();
			  }
		  }';
		if ($template == '')
		$this->body .= '</table><p align=center>';
		else
		$this->body .= $template . "<p align=center>";
		if (isset ( $in ['eform'] ) && $in ['USER_TIP'] != 'DM')
		$this->body .= '
		  <input type="submit" value="Vai alla form" name="equery" onclick="window.location.href=\'index.php?equery&amp;VISITNUM=\'+document.forms[0].VISITNUM.value+\'&amp;ESAM=\'+document.forms[0].VISITNUM.value+\'&amp;{$this->PK_SERVICE}=\'+document.forms[0].{$this->PK_SERVICE}.value+\'&amp;CENTER=\'+document.forms[0].CENTER.value+\'&amp;QUESTION=\'+document.forms[0].QUESTION.value+\'&amp;PROGR=\'+document.forms[0].PROGR.value;"/>
		  ';
		if ($equery){

			if(strtolower($this->config_service['lang'])=='en'){
					$integra_button_text="Integrate eQuery";
			}else{
					$integra_button_text="Integra Scheda";
			}

			$this->body .= '
			<input type="hidden" value="'.$equery_int.'" name="EQUERY_INT">
		  	<input type="submit" value="'.$integra_button_text.'" name="salva" onclick="invia_f();"/>';
			$exclude_send_buttons=true;
		}
		if(!$exclude_send_buttons){
			if ($this->buttons ['SALVA'] && ($in ['USER_TIP'] != 'DM' || isset ( $in ['eform'] ))){
			#GC 18/11/2015 NUOVA_GRAFICA
			//$this->body .= '
		  //	<input type="submit" value="' . $this->buttons ['SALVA'] . '" name="salva" onclick="salva_f();"/>';
		  $this->body .= '
							<button class="btn btn-warning" type="button" onclick="salva_f();">
								<i class="fa fa-floppy-o bigger-110"></i>
								'.$this->buttons ['SALVA'].'
								</button>';	
		  	}
			if ($this->buttons ['SUBMIT'] != '')
			$this->body .= '
		  	<input type="submit" value="' . $this->buttons ['SUBMIT'] . '" onclick="submit();"/>';

			/*else {
			 $this->body.='
			 <input type="hidden" value="1" name="eQuery_Integrazione_Send_">
			 <input type="submit" value="Salva Modifiche" name="eQuery_Integrazione_Send" onclick="invia_f(false);"/>';
			 }*/

			if ($this->buttons ['INVIA'] && $in ['USER_TIP'] != 'DM' || (isset ( $in ['FORM'] ) || isset ( $in ['SEARCH'] ))){
			#GC 18/11/2015 NUOVA_GRAFICA
			//$this->body .= '
		  //<input type="submit" value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/>';
		  $this->body .= '
							<button class="btn btn-info" type="button" onclick="invia_f();">
								<i class="icon icon-lock bigger-110"></i>
								'. $this->buttons ['INVIA'] . '
								</button>
							';
		  }
			if ($in ['USER_TIP'] == 'DM' && ! isset ( $in ['FORM'] ) && ! isset ( $in ['SEARCH'] )) {
				$sql = new query ( $conn );
				global $PROGR;
				
				#GC 07/11/2014# Nuova gestione EME e riapertura schede. Ignoro la tabella ce_equery perche' non la utilizzo
				//$query = "select id , to_char(quest_dt,'DD/MM/YYYY') as data from {$this->config_service['service_root']}_equery where visitnum=:visitnum and esam=:esam and progr=:progr and {$this->PK_SERVICE}=:pk_service and validata is null --and to_be_validate=1";
				//// echo $query;
				//unset($bind);
				//$bind['VISITNUM']=$in['VISITNUM'];
				//$bind['ESAM']=$in['ESAM'];
				//$bind['PROGR']=$PROGR;
				//$bind['PK_SERVICE']=$in[$this->PK_SERVICE];
				////$sql->set_sql ( $query );
				//$sql->exec ($query,$bind);//binded
				//while ( $sql->get_row () ) {
				//	$equery_option .= "<option value=\"{$sql->row['ID']}\">Equery number {$sql->row['ID']} Equery data {$sql->row['DATA']}</option>";
				//}
				#FINE
				
				#GC 07/11/2014# Nuova gestione EME e riapertura schede. 
				$query = "select visitnum_progr as id_eme, emend_code ,to_char(emend_dt,'DD/MM/YYYY') as emend_dt from {$this->config_service['service_root']}_emendamenti where {$this->PK_SERVICE}=:pk_service";
				// echo $query;
				unset($bind);
				$bind['VISITNUM']=$in['VISITNUM'];
				$bind['ESAM']=$in['ESAM'];
				$bind['PROGR']=$PROGR;
				$bind['PK_SERVICE']=$in[$this->PK_SERVICE];
				//$sql->set_sql ( $query );
				$sql->exec ($query,$bind);//binded
				while ( $sql->get_row () ) {
					$eme_option .= "<option value=\"{$sql->row['ID_EME']}\">Emendamento: {$sql->row['EMEND_CODE']} ({$sql->row['EMEND_DT']})</option>";
				}
				#FINE
				
				if($this->config_service['lang']=="en") {
					$reason="Reason for change:";
					$send="Send";
					$opt1="Documentation of change";
					$opt2="Data entry error";
					$alert_msg="WARNING!!! It\\'s necessary to choose a reason for the revision";
				} else {
					$reason="Motivo della modifica:";
					$send="Procedi";
					$opt1="Documentazione di cambiamento";
					$opt2="Errore inserimento dati";
					$alert_msg="ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica";
				}

				$this->body .= "$reason
		  		<select name='ID_QUERY'>
		  			<option></option>
						<OPTION VALUE=\"-2\">$opt1</option>
						<OPTION VALUE=\"-1\">$opt2</option>
						$eme_option
		  		</select><br/>
		  		
		  		<!--GC 19/11/2015 NUOVA_GRAFICA
		  		<input type=\"submit\" value=\"$send\" name=\"invia_dm\" onclick=\"
		  			if (document.forms[0].ID_QUERY.value!='') invia_f();
		  			else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;}
		  			\"/>
		  		-->
		  			
		  		<button class=\"btn btn-info\" type=\"button\" onclick=\"
		  			if (document.forms[0].ID_QUERY.value!='') invia_f();
		  			else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;} \">
								<i class=\"icon icon-lock bigger-110\"></i>
								". $send . "
								</button>	
		  			
		  	";
		}
		if ($this->buttons ['ANNULLA']){
		#GC 18/11/2015 NUOVA_GRAFICA
		//$this->body .= '
		//  <input type="reset" value="' . $this->buttons ['ANNULLA'] . '" name="annulla" onclick="resetForm();return false;" />';
		$this->body .= '
						<button class="btn" type="reset" >
								<i class="icon-undo bigger-110"></i>
								'.$this->buttons ['ANNULLA'].'
								</button>';
		}						
		if ($this->buttons ['CANCELLA']){
		#GC 18/11/2015 NUOVA_GRAFICA
		//$this->body .= '
		//<input type="button" value="' . $this->buttons ['CANCELLA'] . '" name="cancella" onclick="resetForm();return false;" />';
		  
		 $this->body .= '
						<button class="btn" type="reset" >
								<i class="icon-undo bigger-110"></i>
								'.$this->buttons ['CANCELLA'].'
								</button>';
							}
		}
		//*****
		//modifica in revisione all'azienda 9/9/10
		if ($this->buttons ['INREVISIONE'] && $in ['USER_TIP'] != 'DM' && !$equery ) {
			$this->body .= '
		  	<br /><input type="submit" value="' . $this->buttons ['INREVISIONE'] . '" name="inrevisione" style="color:red;" onclick="salva_f();document.forms[0].INREV.value=1;"/>';
		}
		//*****
		$this->body .= '</p></table>';
		if(!$exclude_send_buttons) $this->body .= '</form>';
		$config_service=$this->config_service;
		if ($config_service ['PK_SERVICE'] == '')
		$this->PK_SERVICE = 'CODPAT';
		else
		$this->PK_SERVICE = $config_service ['PK_SERVICE'];
		global $vlist;
		if (!isset($in['SEARCH']) && $in [$this->PK_SERVICE] != '' && ! isset ( $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] ) && !$exclude_send_buttons) {
			if($this->form['NO_JS_BACK']=="") $history="onclick=\"history.back(); return false;\"";
			$this->body .= '
		  <p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE].'&VISITNUM='.$in ['VISITNUM'].'" '.$history.'>&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p>';
		}
		$href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";
		$this->body = preg_replace ( "/#HREF#/", $href_alternativo, $this->body );
	}

	function close_form($no_link_back=false, $equery=false){
		
		$temp_close=parent::close_form($no_link_back,$equery);
		
		$js_function_on_load = $this->form ['LOAD_CLOSE'];
		$this->onload = $js_function_on_load;
		
		return $temp_close;	
	}

}

class xml_vlist extends xml_vlist_prototype{}

class xml_page extends xml_page_prototype{
	
		/**
	 * page_html
	 * Costruisce il codice html della pagina
	 *
	 * @return string
	 */
	function page_html(){
		for ($i=0;$i<count($this->blocco);$i++) $this->body.=$this->blocco_html($i);
		return "<div class=\"xmr_contenuto\">".$this->body."</div>";
	}

	function blocco_html($i){
		$html="
		  				<TABLE cellSpacing=2 cellPadding=2 width=\"95%\" align=center border=0>
              <TBODY>
              	<TR>
                	<TD class=int>".$this->blocco[$i]['TITOLO']."</td>
								</tr>
							";
		for ($l=0;$l<count($this->links[$i]);$l++) {
			$param=$this->links[$i][$l]['PARAM'];
			$params=explode(",",$param);
			$param="";

			for ($p=0;$p<count($params);$p++) {
				$params[$p]=preg_replace("/\|/i", "," , $params[$p]);
				#echo "{$params[$p]} <br>";
				$param.=$params[$p]."&";
			}
			if($this->links[$i][$l]['TR_CSS_CLASS']!="") $tr_css_class="class=\"{$this->links[$i][$l]['CLASS']}\" ";
			else $tr_css_class="";
			
			if($this->links[$i][$l]['ONCLICK']!="") $tr_onclick=" onclick=\"{$this->links[$i][$l]['ONCLICK']}\" ";
			else $tr_onclick="";
			
//			echo "<a href=\"".$this->links[$i][$l]['SCRIPT']."?".$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param."\">".$this->links[$i][$l]['TESTO']."</a>";
			if ($this->links[$i][$l]['TIPO']!='') $param=$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param;
			if ($this->links[$i][$l]['PARAM']=="ADMIN_PROFILI=yes" && !in_array($_SERVER['REMOTE_USER'],$this->admin_profili)) {
				$html.="<tr $tr_css_class $tr_onclick>
						<td class=\"destra-bis\">Profilo non abilitato alla gestione dei profili</td>
					</tr>";
			} else {
				
				global $in;
				global $conn;
				
				$numero_parentesi='';
				if ($this->links[$i][$l]['SQL_COUNT']!=''){
				$query_count = "{$this->links[$i][$l]['SQL_COUNT']}";	
				$sql_count = new query ( $conn );
				//GIULIO 14-02-2013 Commentata in quanto il conteggio e' sul totale degli studi inseriti da chiunque
				$bind['remote_userid']=$in['remote_userid'];
				$bind['center']=$in['CENTER'];
				//echo $bind['center'];
  	 			$sql_count-> exec ( $query_count,$bind );
  	 			//echo $query_count."<br/>";
     			$sql_count-> get_row();
				if ($sql_count->row['NUM_ROW']!=0){
					$numero_parentesi=" <font color='red'><i>(".$sql_count->row['NUM_ROW'].")</i></font>";
					}
				}
						
				$html.="<tr $tr_css_class $tr_onclick>
						<td class=\"destra-bis\"><a href=\"".$this->links[$i][$l]['SCRIPT']."?".$param."\">".$this->links[$i][$l]['TESTO'].$numero_parentesi."</a></td>
					</tr>
						   ";
			}
		}
		$html.=" </table>";
		return $html;

	}
	
	//////// MUTUATO DA OSSC ////////
	
	/*
	//Gestione Javascript sui blocchi
	function blocco_html($i){
		$html="
		  				<TABLE cellSpacing=2 cellPadding=2 width=\"95%\" align=center border=0>
              <TBODY>
              	<TR>
                	<TD class=int_hp>".$this->blocco[$i]['TITOLO']."</td>
								</tr>
							";
		for ($l=0;$l<count($this->links[$i]);$l++) {
			$param=$this->links[$i][$l]['PARAM'];
			$params=explode(",",$param);
			$param="";

			for ($p=0;$p<count($params);$p++) $param.=$params[$p]."&";
			#echo "<A href=\"".$this->links[$i][$l]['SCRIPT']."?".$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param."\">".$this->links[$i][$l]['TESTO']."</a>";
			if ($this->links[$i][$l]['TIPO']!='') $param=$this->links[$i][$l]['TIPO']."=".$this->links[$i][$l]['XML']."&amp;".$param;
			$html.="
								<tr>
								 <td class=\"destra-bis_hp\"><A href=\"".$this->links[$i][$l]['SCRIPT']."?".$param."\">".$this->links[$i][$l]['TESTO']."</a>
							   </td>
						   </tr>
						   ";
		}
		$html.=" </table>";
		return $html;

	}	
	*/
	//////// FINE MUTUATO DA OSSC ////////
	
}

class xml_list extends xml_list_prototype{
	
	function xml_list($xml_file, $page, $rpp,$conn, $config_service, $session_vars) {
	$page=$_GET['PAGE'];
	if ($page=='' || $page==0) $page=1;
		parent::xml_list_prototype($xml_file, $page, 10);
	}
	
	function col_th_lente($i) {
		//	  	print "<hr>col_th_testo: i=$i<hr>";
		global $in;
		$txt = $this->cols [$i] ['TESTO'];
		if ($this->cols [$i] ['ORD_ARROW'] != '') {
			if ($this->cols [$i] ['ORD_ARROW'] == 'yes')
			$this->cols [$i] ['ORD_ARROW'] = $this->cols [$i] ['NOME'];
			$img_down = "/images/down_arrow.gif";
			if ($in ['ORD_TYPE'] == 'ASC' && $in ['ORD'] == $this->cols [$i] ['ORD_ARROW'])
			$img_down = "/images/down_arrow_red.gif";
			$img_up = "/images/up_arrow.gif";
			if ($in ['ORD_TYPE'] == 'DESC' && $in ['ORD'] == $this->cols [$i] ['ORD_ARROW'])
			$img_up = "/images/up_arrow_red.gif";

			//modifica di cristiano campeggiani agosto 2006
			foreach ( $_GET as $key => $val ) {
				if ($key != 'ORD' && $key != 'ORD_TYPE' && $key != 'page')
				$param .= "$key=$val&";
			}
			if (isset ( $in ['page'] ))
			$param .= "page=1&";
			if (isset ( $in ['ESAM'] ) && isset ( $in ['VISITNUM'] ) && ($in ['VISITNUM'] == 0) && ($in ['ESAM'] == 0)) {

				$txt .= "
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";

			} else { //solo le PROSSIME 4 righe erano presenti prima della modifica!!!
				if ($in ['CENTER'] != '')
				$center = "CENTER={$in['CENTER']}";
				$txt .= "
	  			<br><a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
			}
		}

		return "<th class=\"int\">" . $txt . "</th>";
	}
	
	function col_td_lente($i) {
		//print_r($this->cols[$i]);//if ($this->cols[$i])
		if ($this->cols [$i] ['IMG'] != ''){
			$img = "images/{$this->cols[$i]['IMG']}";
			#GC NUOVA_GRAFICA
			$value = "<span class=\"btn btn-xs btn-info\" ><i class=\"fa fa-edit bigger-120\"></i></span>";
		}
		else{
			$img = "images/lente.gif";
			$value = "<img src=\"$img\" width=32 border=0>";
			}

		return $value . "&nbsp;";
	}
	
	
	function col_th_matita($i) {
		return "<th class=\"int\">" . $this->cols [$i] ['TESTO'] . "</th>";
	}
	
	function col_td_matita($i) {
		return "<img src=\"/images/pen.png\" border=0>";
	}
	
	/*
	function col_td_elimina($i) {
		//print_r($this);
		print_r($in);
		return "<a href=\"?delete=elimina&ID_STUD={$i}\"><img src=\"/images/trash.png\" border=0></a>";
	}
	*/

	
}


class legend extends legend_prototype{}

class user extends user_prototype{}

//class xml_esams_list extends xml_esams_list_prototype{}
include_once "esams_list.inc";


function var_glob($value){
	global $in;
	global $inputval;
	if (isset($inputval[$value]) && $inputval[$value]!='') {return $inputval[$value];};
	if (isset($in[$value]) && $in[$value]!='') {return $in[$value];};
	if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') {return $GLOBALS[$value];};
	return '';
}
	function error_page($user, $error, $error_spec){
		
		Logger::trace();
		
		global $filetxt;
		global $in;
		global $SRV;
		global $log_conn;
		global $service;
		global $remote_userid;
		global $session_number;
		$eol=PHP_EOL;
		//die("POLLO!");
		$email_admin="g.contino@cineca.it, l.verri@cineca.it, l.pazzi@cineca.it, a.ramenghi@cineca.it";
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
	
	function centri_open_subwf01(){
		global $study_;
		global $in;
		global $conn;
		
		//Fix PC_KEY
		$pkid = $in[$study_->xmr->pk_service];
		$curvnum = $in['VISITNUM'];
		$vprogr = $in['VISITNUM_PROGR'];
		$curesam = $in['ESAM'];
		$progr = $in['PROGR'];
		$in['PC_KEY']=$in['PROGR'];
		$fields = array();
		$fields['PC_KEY'] = $in['PC_KEY'];
		if($in['PRINC_INV']=='-9944')$fields['D_PRINC_INV']=$in['SPEC_PI'];
		$study_->updateEsamProgr($pkid,$curvnum,$vprogr,$curesam,$progr,$fields);
		
		$sgrStato = 3;
		centri_subWF(1); //Id visita
		/*
		$profilo = $study_->getProfilo($study_->user->userid);
		$st = $study_->dettaglio['STATO_INT'];
		error_log("ST: $st");
		if ($profilo == "SGR" || $st >= $sgrStato){
			centri_subWF(2); //Id visita
		}
		*/
		if ($in['FORCE_CENTRO']=="yes"){
			
				$sql = new query ($conn);
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and visitnum_progr={$in['VISITNUM_PROGR']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
		}
	}
	
	function centri_open_subwf02(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		Logger::send("centri_open_subwf02");
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
		
		if ($in['INVIOCO'] == 1 && !isset($in['ajax_call'])){
		//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DEL PARERE
			$id_area = 1;
			$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
			
			$kw="DOC_PARERE";
			
			if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
				if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
					else $kw.="_{$in['PROGR']}";
			}
			
			$sql_update="update docs set approv_comm='Invio Scheda Parere', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
		}
		
		if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send("centri_open_subwf02 - dentro");
			
			if ($in['INVIOCO'] == 1 && !isset($in['ajax_call'])){
				
				//Se il parere e' definitivo positivo
				if ($in['RIS_DELIB'] == 1 || $in['RIS_DELIB'] == 4 || $in['RIS_DELIB'] == 5 || $in['RIS_DELIB'] == 8){
					
					$vprogr = $in['VISITNUM_PROGR'];
					$new_vprogr=$vprogr+1;
					$sql_update_2="update {$study_->xmr->prefix}_CENTRILOCALI set stato=5 where {$study_->xmr->pk_service}={$study_->pk_service} and visitnum=0 and visitnum_progr=0 and progr=$new_vprogr";
 				 	//Logger::send($sql_update_2);
					$sql_2=new query($conn);
 					$sql_2->set_sql($sql_update_2);
					$sql_2->ins_upd();	
  				
					//DATI AMMINISTRATIVI
					centri_subWF(10, "CENTRO", "PC_KEY", true); //Id visita
						
					//APRO LE SCHEDE DI FUP
					centri_subWF(5, "CENTRO", "PC_KEY", true); //Id visita
				
					#APRO LE SCHEDE DI SAE
					centri_subWF(9, "CENTRO", "PC_KEY", true); //Id visita
				
						
					//Luigi bug allibente emendamenti vengono riaperti
					$query_check_eme="select count(*) as EMEPRESENTE from ce_coordinate where visitnum=20 and id_stud={$in['ID_STUD']}";
					$sql_check_eme=new query($conn);
					$sql_check_eme->set_sql($query_check_eme);
					$sql_check_eme->exec();
					$sql_check_eme->get_row();
					$numeme=$sql_check_eme->row['EMEPRESENTE'];
					if ($numeme==0){
						Logger::send('apro emendamenti');
							$vid = 20;
							$open = array();
							$open[] = 1;
							$study_->openVisit($vid,$open);
						}
						
					$study_->SendMailNcr(3);
				}
				
				if ($in['RIS_DELIB'] == 1 || $in['RIS_DELIB'] == 2 || $in['RIS_DELIB'] == 4 || $in['RIS_DELIB'] == 5 || $in['RIS_DELIB'] == 8){
				//CHIUDO LA VISITCLOSE PER QUESTA SPECIFICA VISITA PROGRESSIVA PER SUCCESSIVO CONTROLLO APERTURA EMENDAMENTI in open_conduzione_studio
					$sql_close="update ce_coordinate set visitclose=1 where id_stud={$in['ID_STUD']} and visitnum='4' and visitnum_progr={$in['VISITNUM_PROGR']}";
					$sql=new query($conn);
					$sql->set_sql($sql_close);
					$sql->ins_upd();
				}
				
				//Se il parere e' sospensivo:
				if ($in['RIS_DELIB'] == 3 || $in['RIS_DELIB'] == 6){
				
					#GC 16/03/2016
					if ($in['RIS_DELIB'] == 3 && $in['PARERE_CEP'] == 1){
						$study_->SendMailCEP();
					}
					
					$vprogr = $in['VISITNUM_PROGR'];
					$new_vprogr=$vprogr+1;
					$sql_update_2="update {$study_->xmr->prefix}_CENTRILOCALI set stato=4 where {$study_->xmr->pk_service}={$study_->pk_service} and visitnum=0 and visitnum_progr=0 and progr=$new_vprogr";
	 				//Logger::send($sql_update_2);
					$sql_2=new query($conn);
	 				$sql_2->set_sql($sql_update_2);
	  			$sql_2->ins_upd();	
					
					//Riapro i dati generali, e i dati centro specifici per quel centro
					$study_->reOpenVisit(0);
					$study_->reOpenVisitProgr(1,$vprogr);
					
					$study_->SendMailNcr(2);
				
				}
				
				//Se il parere e' non approvato:
				if ($in['RIS_DELIB'] == 2){
					$vprogr = $in['VISITNUM_PROGR'];
					$new_vprogr=$vprogr+1;
					$sql_update_2="update {$study_->xmr->prefix}_CENTRILOCALI set stato=6 where {$study_->xmr->pk_service}={$study_->pk_service} and visitnum=0 and visitnum_progr=0 and progr=$new_vprogr";
 					//Logger::send($sql_update_2);
					$sql_2=new query($conn);
 					$sql_2->set_sql($sql_update_2);
  				$sql_2->ins_upd();	
  				
				}
				
			}
		
	}
	
	function centri_subWF($step, $centerField = false, $pcKey = false, $checkOpened = false){ //Step ? id visita da aprire (oltre che lo step), poi vediamo
		global $in;
		global $conn;
		global $service;
		global $study_;
		if ($in['USER_TIP']=='DE' && !isset($in['ajax_call'])){
			//die("QUI: $step");
			$pkid = $in[$study_->xmr->pk_service];
			$curvnum = $in['VISITNUM'];
			$vprogr = $in['VISITNUM_PROGR'];
			$curesam = $in['ESAM'];

			$progr = $in['PROGR'];
			//die("STEP: $step");
			//die("QUAA");
			switch ($step){
				case 1:
					$ovnum = $step;
					$ovprogr = $in['PROGR']-1;
					$oprogr = 1;
					//die("QUAI");
					//$study_->openEsamProgr($pkid,$ovnum,$ovprogr,21,$oprogr);
					//die("QUAOO");
					$study_->openEsamProgr($pkid,$ovnum,$ovprogr,22,$oprogr, true, false);
					$study_->openEsamProgr($pkid,$ovnum,$ovprogr,23,$oprogr, false, false); //Non apro niente degli esam progressivi
					//update campi pre-compilati
					//die("PKID: ".$pkid); // "$pkid";
					$row = $study_->loadEsamProgr($pkid,$curvnum,$vprogr,$curesam,$progr);
					$fields = array();
					$fields['PC_KEY'] = $in['PC_KEY'];
					$fields['CENTRO'] = $in['CENTRO'];
					$fields['PRINC_INV'] = $in['PRINC_INV'];
					$fields['D_CENTRO'] = str_replace("'","''",$row['D_CENTRO']);
					//$fields['D_PRINC_INV'] = $in['D_PRINC_INV'];
					$fields['D_PRINC_INV'] = str_replace("'","''",$row['D_PRINC_INV']);
					//print_r($fields);
					//print_r($in);
					//die();
					$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,22,$oprogr,$fields);
					//Unsetto principal investigator x documentazione (non ha il campo)
					unset($fields['PRINC_INV']);
					unset($fields['D_PRINC_INV']);
					//$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,23,$oprogr,$fields); //Commento perch? ? meglio non avere nulla.
					//die("STEPEND: $step");
					break;
				case 2:
					//die("CASE 2");
					$ovnum = $step;
					$ovprogr = $in['PROGR']-1;
					$oprogr = 1;
					$study_->openEsamProgr($pkid,$ovnum,$ovprogr,1,$oprogr,true,false);
					//update campi pre-compilati
					$row = $study_->loadEsamProgr($pkid,$curvnum,$vprogr,$curesam,$progr);
					$fields = array();
					$fields['PC_KEY'] = $in['PC_KEY'];
					$fields['CENTRO'] = $in['CENTRO'];
					$fields['D_CENTRO'] = str_replace("'","''",$row['D_CENTRO']);
					$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,1,$oprogr,$fields);
					break;
				case 5:
				case 10:
						//die("OK!");
						$eopen = array();
						$checkesam = 1;
						if ($step == 5){
							$eopen[] = 1;
							$eopen[] = 2;
							$eopen[] = 3;
							#GC 10/06/2013 - Scheda risultati centro-specifica sostituita con quella studio-specifica Issue CE-8
							//$eopen[] = 4;
						}else if ($step == 10){
							$eopen[] = 1;
						}
						//die($in['INVIOCO']);
						//print_r($in);
						//die("QUA");
								
								$ovnum = $step;
								$ovprogr=$in['VISITNUM_PROGR'];
								
								$oprogr = 1;
								//die("OPEN: $ovprogr");
								foreach ($eopen as $eo){
									$study_->openEsamProgr($pkid,$ovnum,$ovprogr,$eo,$oprogr,true,false);
								}
								//$study_->openEsamProgr($pkid,$ovnum,$ovprogr,2,$oprogr);
								//$study_->openEsamProgr($pkid,$ovnum,$ovprogr,3,$oprogr);
								//$study_->openEsamProgr($pkid,$ovnum,$ovprogr,4,$oprogr);
								//update campi pre-compilati
								$row = $study_->loadEsamProgr($pkid,$curvnum,$vprogr,$curesam,$progr);
								$fields = array();
								$fields['PC_KEY'] = $in['PC_KEY'];
								$fields['CENTRO'] = $in['CENTRO'];
								//$fields['PRINC_INV'] = $in['PRINC_INV'];
								$fields['D_CENTRO'] = $row['D_CENTRO'];
								//$fields['D_PRINC_INV'] = $in['D_PRINC_INV'];
								//$fields['D_PRINC_INV'] = $row['D_PRINC_INV'];
								//print_r($fields);
								//print_r($in);
								//die();
								foreach ($eopen as $eo){
									$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,$eo,$oprogr,$fields);
								}
								//$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,2,$oprogr,$fields);
								//$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,3,$oprogr,$fields);
								//$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,4,$oprogr,$fields);
							//}
							//die("STEPEND: $step");
					//}
					break;
					case 9:
						//die("OK!");
						$eopen = array();
						$sql_select9="select TIPO_SPER from ce_registrazione where id_stud=$pkid";
						$sql9=new query($conn);
						$sql9->set_sql($sql_select9);
						$sql9->exec();
						$sql9->get_row();
						$tipo_sper=$sql9->row['TIPO_SPER'];
						
						if ($tipo_sper==1 or $tipo_sper==3 or $tipo_sper==5 or $tipo_sper==7) $eopen[] = 2;
						if ($tipo_sper==2 or $tipo_sper==6 or $tipo_sper==8 or $tipo_sper==9 or $tipo_sper==12 or $tipo_sper==10) $eopen[] = 9;
						
						$eopen[] = 4; #GC 13/11/2015 Rapporti di sicurezza
								
						$ovnum = $step;
						$ovprogr=$in['VISITNUM_PROGR'];
						
						$oprogr = 1;
						//die("OPEN: $ovprogr");
						foreach ($eopen as $eo){
							$study_->openEsamProgr($pkid,$ovnum,$ovprogr,$eo,$oprogr,true,false);
						}
						$row = $study_->loadEsamProgr($pkid,$curvnum,$vprogr,$curesam,$progr);
						$fields = array();
						$fields['CENTRO'] = $in['CENTRO'];
						$fields['D_CENTRO'] = $row['D_CENTRO'];
						foreach ($eopen as $eo){
							$study_->updateEsamProgr($pkid,$ovnum,$ovprogr,$eo,$oprogr,$fields);
						}
					break;
			}
			
		}
	}
	
	function allinea_centrilocali(){
		global $study_;
		global $in;
		global $conn;
		
		$sql_select1="select * from ce_locale01 where visitnum=1 and esam=22 and visitnum_progr={$in['VISITNUM_PROGR']} and id_stud={$in['ID_STUD']} and progr=1";
		$sql1=new query($conn);
		$sql1->set_sql($sql_select1);
		$sql1->exec();
		$sql1->get_row();
		
		$progrcentro=$in['VISITNUM_PROGR']+1;
		$sql = new query ($conn);
		$bind=$sql1->row;
		if($bind['PRINC_INV']=='-9944')$bind['D_PRINC_INV']=$bind['SPEC_PI'];
		
		$sql_update="update ce_centrilocali 
		set STRUTTURA=:STRUTTURA, 
		D_STRUTTURA=:D_STRUTTURA, 
		DIPARTIMENTO=:DIPARTIMENTO, 
		D_DIPARTIMENTO=:D_DIPARTIMENTO, 
		DIR_DIPARTIMENTO=:DIR_DIPARTIMENTO, 
		UNITA_OP=:UNITA_OP, 
		D_UNITA_OP=:D_UNITA_OP, 
		UNITA_OPERATIVA_TEMP=:D_UNITA_OP, 
		DIR_UO=:DIR_UO, 
		PRINC_INV=:PRINC_INV, 
		D_PRINC_INV=:D_PRINC_INV,  
		SPEC_PI=:SPEC_PI, 
		MMG_PLS=:MMG_PLS  
		where id_stud={$in['ID_STUD']} 
		and visitnum=0 
		and visitnum_progr=0 
		and esam=10 
		and progr=$progrcentro";
		$sql->exec($sql_update,$bind); 		
		
		if ($in['RIAPRISCHEDADM']=="yes") {
		
		$sql_update2="update ce_reginvio
		set PRINC_INV=:PRINC_INV, 
		D_PRINC_INV=:D_PRINC_INV 
		where id_stud={$in['ID_STUD']} 
		and visitnum=2
		and visitnum_progr={$in['VISITNUM_PROGR']} 
		and esam=1";
		
		$sql->exec($sql_update2,$bind); 
		
		$sql_update3="update ce_valutazione
		set PRINC_INV=:PRINC_INV, 
		D_PRINC_INV=:D_PRINC_INV 
		where id_stud={$in['ID_STUD']} 
		and visitnum=4
		and visitnum_progr={$in['VISITNUM_PROGR']} 
		and esam=1";
		
		$sql->exec($sql_update3,$bind); 
		
		}
	}

	function open_istr_ts(){
		global $in;
		global $conn;
		global $service;
		global $study_;
		Logger::send('open_parere');
		
		if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send('open_parere - dentro');
		//Attivo al send
		$keyField = 'PC_KEY';
		$centerField = 'CENTRO';
		$docField = 'DOC_COMPLETA';
		if ($in['USER_TIP']=='DE' && $in['INVIOCO'] ==1 && !isset($in['ajax_call'])){
			Logger::send('nel primo if');
			//die("QUI: $step");
			$pkid = $in[$study_->xmr->pk_service];
			$curvnum = $in['VISITNUM'];
			$vprogr = $in['VISITNUM_PROGR'];
			$curesam = $in['ESAM'];

			$progr = $in['PROGR'];
			//die("STEP: $step");
			//die("QUAA");
			
			//recupero le visite progressive x poi verificare la presenza dei centri
			$parvisit = 4; //Id visita del parere (che devo aprire o modificare)
			$paresam = 1; //Esam parere
			$vprogs = $study_->getMaxVprogr($pkid,$parvisit);
			$vprogs++;
			$c = $in[$centerField];
			$k = $in[$keyField];
			//echo "CENTRO:".$c."<br/>";
			$docVal = $in[$docField];

			Logger::send($docVal);
			if ($docVal == 1){
				//Luigi: scheda istruttoria tecnico-scientifica
					#GC 19/05/2016# Assegno all'istr ts lo stesso progr della verifica documentale positiva che l'ha generata per valorizzare l'editor dell'istr ts
					/*$p = $study_->getMaxProgr($pkid,2,$vprogr,21); //Controllo se c'e' gia' una scheda its
					$oprogr=$p;
					if($p) $oprogr++;
					if($p=='') $oprogr=1;
					$study_->openEsamProgr($pkid,2,$vprogr,21,$oprogr,true,false);*/
					$study_->openEsamProgr($pkid,2,$vprogr,21,$progr,true,false);
				
				//Luigi: scheda parere
					$ovnum = $parvisit;
					$p = $study_->getMaxProgr($pkid,$parvisit,$vprogr,$paresam); //Controllo se c'e' gia' una scheda parere
					$oprogr=$p;
					if($p) $oprogr++;
					if($p=='') $oprogr=1;
					$study_->openEsamProgr($pkid,$parvisit,$vprogr,$paresam,$oprogr,true,false);
				
				//update campi pre-compilati
					$fields = array();
					$fields[$keyField] = $k;
					$fields['CENTRO'] = $c;
					$fields['PRINC_INV'] = $in['PRINC_INV'];
					$fields['D_CENTRO'] = str_replace("'","''",$in['D_CENTRO']);
					$fields['D_PRINC_INV'] = str_replace("'","''",$in['D_PRINC_INV']);
					$study_->updateEsamProgr($pkid,$parvisit,$vprogr,$paresam,$oprogr,$fields);
					
					$new_vprogr=$vprogr+1;
				  $sql_update_2="update {$study_->xmr->prefix}_CENTRILOCALI set stato=3 where {$study_->xmr->pk_service}={$study_->pk_service} and visitnum=0 and visitnum_progr=0 and progr=$new_vprogr";
 				 	//Logger::send($sql_update_2);
				  $sql_2=new query($conn);
 					$sql_2->set_sql($sql_update_2);
  				$sql_2->ins_upd();	
				
			}elseif ($docVal == 2){ #GIULIO 20-12-12 Se la documentazione non e' completa, apro solo gli esam 23,24 del centro in questione
				Logger::send('sto per entrare in reOpenVisitProgr');
				
				$new_vprogr=$vprogr+1;
				$sql_update_2="update {$study_->xmr->prefix}_CENTRILOCALI set stato=2 where {$study_->xmr->pk_service}={$study_->pk_service} and visitnum=0 and visitnum_progr=0 and progr=$new_vprogr";
 				//Logger::send($sql_update_2);
				$sql_2=new query($conn);
 				$sql_2->set_sql($sql_update_2);
  			$sql_2->ins_upd();	
				
				$study_->reOpenVisit(0);
				$study_->reOpenVisitProgr(1,$vprogr);
				$study_->SendMailNcr(1);
			 }
			}
	}

	/* function open_parere(){
		global $in;
		global $conn;
		global $service;
		global $study_;
		Logger::send('open_parere2');
		
		if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send('open_parere2 - dentro');
		//Attivo al send
		if ($in['USER_TIP']=='DE' && $in['INVIOCO'] ==1 && !isset($in['ajax_call'])){
			Logger::send('nel primo if');
			$pkid = $in[$study_->xmr->pk_service];
			$curvnum = $in['VISITNUM'];
			$vprogr = $in['VISITNUM_PROGR'];
			$curesam = $in['ESAM'];
			$progr = $in['PROGR'];
			
			#Apro scheda di parere
			$parvisit = 4; //Id visita del parere (che devo aprire o modificare)
			$paresam = 1; //Esam parere
			$p = $study_->getMaxProgr($pkid,$parvisit,$vprogr,$paresam); //Controllo se c'e' gia' una scheda parere
			$oprogr=$p;
			if($p) $oprogr++;
			if($p=='') $oprogr=1;
			$study_->openEsamProgr($pkid,$parvisit,$vprogr,$paresam,$oprogr,true,false);
			
			#Carico i dati del centro
			$row = $study_->loadEsamProgr($pkid,1,$vprogr,22,1);
			
			//CONTROLLARE QUESTA QUERY, SEMBRA NON VALORIZZARE I CAMPI NELLA VALUTAZIONE
			$fields = array();
			$fields['CENTRO'] = $row['CENTRO'];
			$fields['PRINC_INV'] = $row['PRINC_INV'];
			$fields['D_CENTRO'] = $row['D_CENTRO'];
			$fields['D_PRINC_INV'] = $row['D_PRINC_INV'];
			$study_->updateEsamProgr($pkid,$parvisit,$vprogr,$paresam,$oprogr,$fields);
			
			//print_r($row);
			//die($row);

			}
	} */
		
	function open_conduzione_studio($xml_form){
		global $in;
		global $conn;
		global $service;
		global $study_;
		
		global $filetxt;
		
		Logger::send('open_conduzione_studio');
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
		
		if ($in['USER_TIP']=='DE' && $in['INVIOCO'] ==1 && !isset($in['ajax_call'])){
		//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DEI DATI AMMINISTRATIVI DELLO STUDIO
			$id_area = 1;
			$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
			
			$kw=array();
			
			$kw[0]="DELIB_FILE";
			$kw[1]="STIPULA_FILE";
			$kw[2]="ASS_FILE";
			$kw[3]="DOC_POLIZZA";
			
			for ($i=0;$i<=3;$i++){
			
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw[$i].="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw[$i].="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Dati Amministrativi', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
				select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
				) and tipo_doc='Doc_Area' and keywords in ('$kw[$i]')";
				
				Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
			}
		}
		
		if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send('open_conduzione_studio - dentro');
		
		
		#Controllo se tutti i pareri sono stati inviati INVIATI in BD per evitare di aprire EME con schede aperte (magari da sospensioni)
		$sql_select1="select count (distinct progr) as NUM_CENTRI from ce_coordinate where visitnum=0 and esam=10 and id_stud=$pkid";
		$sql1=new query($conn);
		$sql1->set_sql($sql_select1);
		$sql1->exec();
		$sql1->get_row();
		$num_centri=$sql1->row['NUM_CENTRI'];
		
		$sql_select2="select count (distinct visitnum_progr) as NUM_PARERI from ce_coordinate where visitnum=4 and id_stud=$pkid";
		$sql2=new query($conn);
		$sql2->set_sql($sql_select2);
		$sql2->exec();
		$sql2->get_row();
		$num_pareri=$sql2->row['NUM_PARERI'];
		
		$sql_select4="select max(nvl(visitclose,0)) as VC from ce_coordinate where visitnum=4 and id_stud=$pkid";
		$sql4=new query($conn);
		$sql4->set_sql($sql_select4);
		$sql4->exec();
		$sql4->get_row();
		$vc_pareri=$sql4->row['VC'];
			
		if ($in['USER_TIP']=='DE' && $in['INVIOCO'] ==1 && !isset($in['ajax_call'])){

			if($in['DELIB']==1 || $in['DELIB']==3){
				/* 	sposto al parere positivo
				//APRO LE SCHEDE DI FUP
				centri_subWF(5, "CENTRO", "PC_KEY", true); //Id visita
				
				#APRO LE SCHEDE DI SAE
				centri_subWF(9, "CENTRO", "PC_KEY", true); //Id visita
				 */
				#APRO LE SCHEDE DI CONCLUSIONE E RISULTATI IN TOTO
				$vid = 22;
				$open_concl_toto = array();
				$open_concl_toto[] = 221;
				$open_concl_toto[] = 222;
				$open_concl_toto[] = 223;
				$study_->openVisit($vid,$open_concl_toto);
				
//				#se ci sono tutti i pareri -> posso aprire gli EMENDAMENTI
//				#LUIGI: con i nuovi eme elimino il controllo che tutti i pareri di tutti i centri siano inviati
//				if($vc_pareri==1){
//					
//				//Luigi bug allibente emendamenti vengono riaperti
//				$query_check_eme="select count(*) as EMEPRESENTE from ce_coordinate where visitnum=20 and id_stud={$in['ID_STUD']}";
//				$sql_check_eme=new query($conn);
//				$sql_check_eme->set_sql($query_check_eme);
//				$sql_check_eme->exec();
//				$sql_check_eme->get_row();
//				$numeme=$sql_check_eme->row['EMEPRESENTE'];
//				if ($numeme==0){
//					Logger::send('apro emendamenti');
//						$vid = 20;
//						$open = array();
//						$open[] = 1;
//						$study_->openVisit($vid,$open);
//					}
//				
//				}
				
			}
				
			
			if ($in['DELIB']==2) {
				//se ci sono tutti i pareri definitivi ed almeno 1 scheda dati ammin positiva -> posso aprire gli EMENDAMENTI
				//LUIGI: con i nuovi eme elimino il controllo che tutti i pareri di tutti i centri siano inviati
				$sql_select3="select min(nvl(delib,0)) as NR from ce_coordinate c,ce_richiesta_delibera r where c.id_stud=r.id_stud and c.visitnum=r.visitnum and c.visitnum_progr=r.visitnum_progr and c.id_stud={$in['ID_STUD']} and c.visitnum=10 and c.visitnum_progr not in ({$in['VISITNUM_PROGR']}) and c.visitclose=1";
				$sql3=new query($conn);
				$sql3->set_sql($sql_select3);
				$sql3->exec();
				$sql3->get_row();
				$num=$sql3->row['NR'];
				
				if(/* $study_->CheckVisitClosed("4") && $num_centri==$num_pareri && */ $num){
					//APRO EMENDAMENTI
					//Luigi bug allibente emendamenti vengono riaperti
					$query_check_eme="select count(*) as EMEPRESENTE from ce_coordinate where visitnum=20 and id_stud={$in['ID_STUD']}";
					$sql_check_eme=new query($conn);
					$sql_check_eme->set_sql($query_check_eme);
					$sql_check_eme->exec();
					$sql_check_eme->get_row();
					$numeme=$sql_check_eme->row['EMEPRESENTE'];
					if ($numeme==0){
						$vid = 20;
						$open = array();
						$open[] = 1;
						$study_->openVisit($vid,$open);
					}
				}		
			}
				
			//CHIUDO LA VISITCLOSE PER QUESTA SPECIFICA VISITA PROGRESSIVA
			$sql_close="update ce_coordinate set visitclose=1 where id_stud={$in['ID_STUD']} and visitnum='10' and visitnum_progr={$in['VISITNUM_PROGR']}";
			$sql=new query($conn);
			$sql->set_sql($sql_close);
			$sql->ins_upd();
			
			// non applicabile per il veneto: #Controllo se tutti i pareri sono stati inviati INVIATI in BD per evitare di aprire EME con schede aperte (magari da sospensioni)
			// if($vc_pareri==0){
				// $body="<h2>ATTENZIONE</h2><h3>E' necessario inviare i pareri di tutti i centri in banca dati prima di procedere con i dati amministrativi dello studio</h3><br /><br />";
				// $body.="<a href=\"javascript:history.back();\">&lt;&lt;Torna indietro</a>";
				// $filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
				// die($filetxt);
			// }
			
		}
		
	}
	
	function emendamento_crea_nuovo(){
		
		Logger::send('emendamento_crea_nuovo');
		
		if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send('emendamento_crea_nuovo - dentro');
		
		//Se ho INVIATO la form, lancio aggiornamento nuovo emendamento
		//Apro integrazioni per quello studio?!
		global $in;
		global $conn;
		global $service;
		global $study_;
		if ($in['USER_TIP']=='DE' && !isset($in['ajax_call'])){
			$pkid = $in[$study_->xmr->pk_service];
			$curvnum = $in['VISITNUM'];
			$vprogr = $in['VISITNUM_PROGR'];
			
			//print_r($in);
			//die($in['INVIOCO']);
			//if ($in['INVIOCO']==1){
			
				//$study_->openEmendamento($pkid);
				
				/*
				//Clono tutte le righe dei primi esam e gli apro rossi (con emendamento += 1)
				//Apro e clono solo esam che esistono gi?
				$curvnum = 0;
				$study_->cloneVisit($pkid,$curvnum,$vprogr,'EMENDAMENTO');
				$curvnum = 2;
				$study_->cloneVisit($pkid,$curvnum,$vprogr,'EMENDAMENTO');
				//die("aperto?");
				*/
				//apro schede di valutazione successive
				//$study_->openEsamProgr($pkid,$curvnum,$vprogr,2,1);
				//$study_->openEsamProgr($pkid,$curvnum,$vprogr,3,1);
				$study_->openEsamProgr($pkid,$curvnum,$vprogr,10,1, false);
				
			//}
		}

	}
	
	function emendamento_invia_per_approvazione(){
		//Se ho INVIATO la form, lancio aggiornamento nuovo emendamento
		//Apro integrazioni per quello studio?!
		global $in;
		global $conn;
		global $service;
		global $study_;
		if ($in['USER_TIP']=='DE' && !isset($in['ajax_call'])){
			$pkid = $in[$study_->xmr->pk_service];
			$curvnum = $in['VISITNUM'];
			$vprogr = $in['VISITNUM_PROGR'];
			
			//print_r($in);
			//die($in['INVIOCO']);
			if ($in['INVIOCO']==1){
				//Ho premuto send e non save
				print_r($study_->integrazione);
				$study_->inviaEmendamento($pkid);
				//$study_->integrazione->inviaPerApprovazione();
				//die("INVIO X APPROVAZIONE");
				
				//Apro schede verifica doc e parere
				$study_->openEsamProgr($pkid,$curvnum,$vprogr,2,1);
				$study_->openEsamProgr($pkid,$curvnum,$vprogr,3,1);
				
			}
		}
	}
	
	function emendamento_verifica_doc(){
	
		Logger::send('emendamento_verifica_doc');
		
		if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send('emendamento_verifica_doc - dentro');
		
		global $in;
		global $conn;
		global $service;
		global $study_;
		if ($in['USER_TIP']=='DE' && !isset($in['ajax_call'])){
			$pkid = $in[$study_->xmr->pk_service];
			$curvnum = $in['VISITNUM'];
			$vprogr = $in['VISITNUM_PROGR'];
			$progr = $in['PROGR'];
			
			//print_r($in);
			//die($in['INVIOCO']);
			if ($in['INVIOCO']==1){
				//Ho premuto send e non save
				//print_r($study_->integrazione);
				if ($in['DOC_COMPLETA']==1){
					
					//Luigi:creo la scheda di valutazione
					$study_->openEsamProgr($pkid,$curvnum,$vprogr,3,$progr);
					
					//Luigi:abilito la valutazione
					//LUIGI: disattivo vecchia tipologia emendamento
					// $fields = array();
					// $fields['IN_SEDUTA'] = 0;
					// $study_->updateEsamProgr($pkid,0,0,0,1,$fields);
					
					//Luigi:salvo il centro relativo alla progressiva
					$fields2['CENTRO'] = $in['CENTRO'];
					$fields2['D_CENTRO'] = $in['D_CENTRO'];
					$study_->updateEsamProgr($pkid,$curvnum,$vprogr,3,$progr,$fields2);
					
					//Luigi:creo la scheda di sospensione
					$study_->openEsamProgr($pkid,$curvnum,$vprogr,4,$progr);
					$fields = array();
					
					//Luigi:salvo il centro relativo alla progressiva
					$fields3['CENTRO'] = $in['CENTRO'];
					$fields3['D_CENTRO'] = $in['D_CENTRO'];
					$study_->updateEsamProgr($pkid,$curvnum,$vprogr,4,$progr,$fields3);
					
					//Luigi:creo le scheda di istruttoria ts
					$study_->openEsamProgr($pkid,$curvnum,$vprogr,5,$progr, true, false);
					//Luigi:salvo il centro relativo alla progressiva
					$fields4 = array();
					$fields4['CENTRO'] = $in['CENTRO'];
					$fields4['D_CENTRO'] =  $in['D_CENTRO'];
					$study_->updateEsamProgr($pkid,$curvnum,$vprogr,5,$progr,$fields4);
					
				}else{
					$study_->integraEmendamento($pkid);
				}
			}
		}
		
	}

	function emendamento_chiudi(){
		
		Logger::send('emendamento_chiudi');
		
		if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send('emendamento_chiudi - dentro');
		
		//Se ho INVIATO la form, lancio aggiornamento nuovo emendamento
		//Apro integrazioni per quello studio?!
		global $in;
		global $conn;
		global $service;
		global $study_;
		if ($in['USER_TIP']=='DE' && !isset($in['ajax_call'])){
			$pkid = $in[$study_->xmr->pk_service];
			$curvnum = $in['VISITNUM'];
			$vprogr = $in['VISITNUM_PROGR'];
			$progr = $in['PROGR'];
			
			//Luigi:ha effetto solo la valutazione del primo centro 
			//LUIGI: disattivo vecchia tipologia emendamento
			//$sql_query_eq = "select IN_EMENDAMENTO from CE_REGISTRAZIONE where id_stud=$pkid";
			//$sql_eq = new query ( $conn );
			//$sql_eq->get_row ( $sql_query_eq );
			if ($in['INVIOCO']==1 /*&& $sql_eq->row['IN_EMENDAMENTO']==1*/){
				$accetta = false;
				if ($in['RIS_DELIB']==1 || $in['RIS_DELIB']==12 || $in['RIS_DELIB']==4 || $in['RIS_DELIB']==5 || $in['RIS_DELIB']==9){
					$accetta = true;
					if($in['RIS_DELIB']==2) $accetta = false;
					
					//LUIGI: disattivo vecchia tipologia emendamento
					#GC 06/11/2014# Nuova gestione EME e riapertura schede
					//$study_->closeEmendamento($pkid, $accetta);
					
					$query_check_invio="select fine as EMEINVIATO from ce_coordinate where visitnum=20 and id_stud={$in['ID_STUD']} and visitnum_progr={$in['VISITNUM_PROGR']} and ESAM=1";
					$sql_check_invio=new query($conn);
					$sql_check_invio->set_sql($query_check_invio);
					$sql_check_invio->exec();
					$sql_check_invio->get_row();
					if ($sql_check_invio->row['EMEINVIATO']!=1) error_page($in ['remote_userid'],"Non e' possibile inviare la valutazione. E' necessario prima inviare i dati dell'emendamento","");
					
					#Apro nuovo eme
					//$study_->openEsamProgr($pkid,$curvnum,$vprogr+1,1,1, false, false);
					#FINE
					
				}
				
				if ($in['RIS_DELIB']==10 || $in['RIS_DELIB']==11){
					$study_->integraEmendamento($pkid);
				}
			}
			
			//Luigi: chiudo la scheda per la sospensione
			if ($in['INVIOCO']==1){
				$sql_update="update ce_coordinate set fine=1 where id_stud=$pkid and esam=4 and visitnum=20 and visitnum_progr=$vprogr and progr=$progr ";
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				}
			
			//Luigi: creo la scheda dati amministrativi
			if ($in['INVIOCO']==1 && ($in['RIS_DELIB']==1 || $in['RIS_DELIB']==2 || $in['RIS_DELIB']==4 || $in['RIS_DELIB']==5 || $in['RIS_DELIB']==9)){
				$study_->openEsamProgr($pkid,$curvnum,$vprogr,6,$progr, true, false);
				//Luigi:salvo il centro relativo alla progressiva
				$fields = array();
				$fields['CENTRO'] = $in['CENTRO'];
				$fields['D_CENTRO'] = $in['D_CENTRO'];
				$study_->updateEsamProgr($pkid,$curvnum,$vprogr,6,$progr,$fields);
			}
		}
	}
	
	function action_rapporti(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DEL PARERE
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="RELAZIONE_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Rapporti', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			}
		
	}	

	function action_susar(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DEL PARERE
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="SAE_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda SAE', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			}
		
	}	

	function action_susar_ext(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DEL PARERE
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="SAE_EXT_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda SAE esterno', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			}
		
	}	

	function action_risultati(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DEL PARERE
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="RISULTATO_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Parere', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			}
		
	}	

	function action_doc_eme(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			//LUIGI: nuova gestione eme
			//if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DEL PARERE
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="DOC_EMENDAMENTO";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Doc Eme', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id from docs where id_tipo_ref=$id_tipo_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			//}
		
	}	

	function force_doc_gen(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
		
		$sql = new query ($conn);
		if ($in['FORCE_DOC_GEN']=="yes"){
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				}
			$id_area = 1;
			$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
			
			$kw="DOC_CORE";
			if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
				if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
				else $kw.="_{$in['PROGR']}";
				}
			$sql_update_1="update docs set approv_comm='Invio Schede generali', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
			) and tipo_doc='Doc_Area' and keywords ='$kw'";
			Logger::send($sql_update_1);
			$sql->set_sql($sql_update_1);
			$sql->ins_upd();
			
			$conn->commit();
			//mandare una mail al ce interessato se CTA_INVIATA=1
	}
	
	function force_doc_cs(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
		
		$sql = new query ($conn);
		if ($in['FORCE_DOC_CS']=="yes"){
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and visitnum_progr={$in['VISITNUM_PROGR']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				}
			$id_area = 1;
			$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
			
			$kw="DOC_CENTROSPEC";
			if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
				if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
				else $kw.="_{$in['PROGR']}";
				}
			$sql_update_1="update docs set approv_comm='Invio Schede centro specifiche', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
			) and tipo_doc='Doc_Area' and keywords ='$kw'";
			Logger::send($sql_update_1);
			$sql->set_sql($sql_update_1);
			$sql->ins_upd();
			
			$conn->commit();
			//mandare una mail al ce interessato se CTA_INVIATA=1
	}
	
	function force_farmaci(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];

		if ($in['FORCE_FARMACI']=="yes"){
			
				$sql = new query ($conn);
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				
				$conn->commit();
				//mandare una mail al ce interessato se CTA_INVIATA=1
				}
	}

	function force_dispositivi(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];

		if ($in['FORCE_DISPOSITIVI']=="yes"){
			
				$sql = new query ($conn);
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				
				$conn->commit();
				//mandare una mail al ce interessato se CTA_INVIATA=1
				}
	}

	function force_farmaco_osserv(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];

		if ($in['FORCE_FARMACO_OSSERV']=="yes"){
			
				$sql = new query ($conn);
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				
				$conn->commit();
				//mandare una mail al ce interessato se CTA_INVIATA=1
				}
	}

	function force_tessuti(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];

		if ($in['FORCE_TESSUTI']=="yes"){
			
				$sql = new query ($conn);
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				
				$conn->commit();
				//mandare una mail al ce interessato se CTA_INVIATA=1
				}
	}

	function force_dispositivi_osserv(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];

		if ($in['FORCE_DISPOSITIVI_OSSERV']=="yes"){
			
				$sql = new query ($conn);
				$sql_update="update ce_coordinate set visitclose=1,fine=1 where id_stud={$in['ID_STUD']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				
				$conn->commit();
				//mandare una mail al ce interessato se CTA_INVIATA=1
				}
	}
			
	function action_avvio(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		Logger::send('action_avvio');
		
		//LUIGI:non blocco questa esecuzione per permettere l'approvazione del documento
		//if ($in['RIAPRISCHEDADM']=="yes") return;
		
		Logger::send('action_avvio - dentro');
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
				
				if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DI AVVIO
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="AVVIO_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Avvio', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
		}
	}	
	
	function action_conclusione(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
				
				if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DI AVVIO
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="CONCLUSIONE_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Conslusione', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
			
   			Logger::send($sql_update);
			
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
		}
	}	

	function action_conclusione_toto(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
				
				if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DI AVVIO
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="CONCLUSIONE_TOTO_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Conslusione toto', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
		}
	}	

	function action_risultati_toto(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
				
				if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DI AVVIO
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="RISULTATO_TOTO_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Risultati toto', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
		}
	}	
	
	function action_pubblicazioni_toto(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
				
				if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DI AVVIO
				$id_area = 1;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="PUBBLICAZIONE_TOTO_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Pubblicazioni toto', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
		}
	}	
	
	function registrazione(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		
		$user=$in['remote_userid'];
		
		$sql_update_1="update CE_REGISTRAZIONE set CENTER='{$in['ID_STUD']}' where id_stud='{$in['ID_STUD']}' and esam=0";
		$sql = new query ( $conn );
		$sql->set_sql($sql_update_1);
		$sql->ins_upd();	
		
	}
	
?>
