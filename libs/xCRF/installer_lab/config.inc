<?
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/http_lib.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/db.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xml_parser_wl.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/HTML_Parser.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/page.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/vlist.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/list.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/legend.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/esams_list.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/form.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/study_prototype.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xmrwf.inc.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/integrazioni_ct.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/Installer.inc";
//Decommentare in caso di studio con ePRO. (viene sovrascritta la SubjidExist)
//include_once "epro.inc"; 

$config_service['STUDY_TYPE']='LABORATORY_RANGE';

//putenv("NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1");
$editing=false;

// Configurazione ACMPath
$config_service['ACMPath'] = '/acm/';
// Configurazione ActivitiWF
$config_service['AWFConnectionId'] = 'sisa';
$config_service['AWFBaseURL'] = 'http://appserv-siss01.dev.cineca.it/GeniusWM/rest-service/';
$config_service['AWFUsername'] = 'admin';
$config_service['AWFPassword'] = 'xxx';

// Configurazione dblock
$config_service['dblock']=1;
$config_service['dblock_functions']=array();
$config_service['dblock_functions'][1]='NEWPATIENT'; //primo bit 0001
$config_service['dblock_functions'][2]='SAVESEND'; //secondo bit 0010
$config_service['dblock_functions'][3]='EQUERY'; //terzo bit 0100
$config_service['dblock_functions'][4]='OBVIOUSCORRECTION'; //quarto bit 1000

// Configurazione nuove eQuery
$config_service['eQuery']="1";
$config_service['eQuerySpec']['Integrazione']['ROLE']="DE";
$config_service['eQuerySpec']['Integrazione']['CONTROL_ROLE']="CRA";
$config_service['eQuerySpec']['Integrazione']['VALIDATOR']="DM"; 
// Fine configurazione nuove eQuery

// Configurazione alert onload
//$config_service['javascript_alert']['onunload_page']="1";
//$config_service['javascript_alert']['onsave_page']="1";
//$config_service['javascript_alert']['onsend_page']="1";

$config_service['lang']='en';
$lang=$config_service['lang'];

//criptaggio dati:
$config_service['crypto']="no";

// Log abilitato
$config_service['force_log']=false;

$email_admin="c.contino@cineca.it";
$root=$_SERVER['DOCUMENT_ROOT'];
$dir=$_SERVER['PATH_TRANSLATED'];
$dirs=explode("/", $dir);
$dir='';
for ($i=0;$i<count($dirs)-1;$i++){
	$dir.=$dirs[$i]."/";
}
$dir=rtrim($dir, "/");
$xml_dir=$dir."/xml";
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/log_trace.php";

if(isset($_GET['init_service']) ){
	$xml = simplexml_load_file("study.xml") or die("feed not loading");
	$study_name=$xml->workflow->nome;
	$study_prefix=$xml->configuration->prefix;
	
	$conn = new dbconn();
	$installer = new Installer($study_prefix, $conn, $config_service, $study_name);
	$installer->CreateSessionsTable();
	$installer->CreateCMMTable();
	$installer->FixViews();
	//echo "<a href=\"/study/{$study_name}/index.php?install\">complete installation</a>";
	header("Location: /study/{$study_name}/index.php?install");
	die();
}

$conn=new dbconn();
$sql=new query($conn);

$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
$sql->ins_upd();

class audit_trail extends audit_trail_core_prototype{
}
class integrazioni extends integrazioni_prototype_ct{
}

class xml_form extends xml_form_prototype{
	
}
class xml_form_cippa extends xml_form_prototype{
	/** PIERHD-795 (COME PIERHD-683 cfty720dde16) link_to="|ME|" link_to_send="|NEXT|"
	 * vmazzeo 20130109
	 * aggiungo campo nascosto per la gestione del LINK_TO_SEND
	 *
	 * Genera il codice html della form in compilazione
	 *
	 * @param boolean $force_open
	 * @param boolean $exclude_send_buttons
	 * @param boolean $equery
	 */
	
	function open_form($force_open=false,$exclude_send_buttons=false, $equery=false) {
		//die("QUA?");
		//		 $debug = debug_backtrace();
		//		print_r($debug[2]);
		$in = $this->session_vars;
		$conn = $this->conn;
		$inputval = $this->tb_vals;
		$service = $this->service;
		$config_service = $this->config_service;
	
		$template_form_html = '';
		if ($this->xmr) {
			if ($in [$config_service ['PK_SERVICE']] != 'next') {
				if (isset ( $in ['VISITNUM'] ) && isset ( $in ['ESAM'] )) {
					$sql_query = "select visitclose from {$service}_COORDINATE where VISITNUM={$in['VISITNUM']} and ESAM={$in['ESAM']} and VISITNUM_PROGR={$in['VISITNUM_PROGR']} and {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
					$sql = new query ( $conn );
					$sql->set_sql ( $sql_query );
					$sql->exec ();
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
		/**
		 * PIERHD-795 (COME PIERHD-683 cfty720dde16) link_to="|ME|" link_to_send="|NEXT|"
		 * vmazzeo 20121204
		 * al click su prev/next salvo la form (disabilitando gli edit checks)
		 * se chiamo salva_f con checks=false allora salto i controlli js
		 */
		$this->salva_js = "
		function salva_f(checks){
		cf();
		if (checks==undefined) checks=true;
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
		if($this->config_service['cf']=="no"){
		$this->check_js = '
		function cf(){
					//		  		return true;
					var el;
					var f;
					f=document.forms[0];
					el=f.elements;
					document.forms[0].action=\'\';
					';
		}
		else{
			$this->check_js = '
			function cf(){
					var el;
					var f;
					f=document.forms[0];
					el=f.elements;
					document.forms[0].action=\'\';
					';
		}
	
		$colonne = $this->form ['COLS'];
			$sysdate = date ( "dmY" );
			if (isset($_GET['link_to']) && $_GET['link_to']!='') $this->form ['LINK_TO']=$_GET['link_to'];
			if (isset($_GET['link_to_send']) && $_GET['link_to_send']!='') $this->form ['LINK_TO_SEND']=$_GET['link_to_send'];
			$this->percorso_agg= "&nbsp;&gt;&nbsp;<b>" . $this->form ['TITOLO'] . "</b>";
			if ($equery){
					$sql_query="select equery_int as EQUERY_INT from {$this->service}_eq where stato in (0,2) and {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}";
					$sql=new query($this->conn);
					if ($sql->get_row($sql_query)) $equery_int=$sql->row['EQUERY_INT'];
					else $equery_int=0;
					}
					$this->body = $note_eq.'
					<form method="post" class="niceform" action="index.php" enctype="multipart/form-data"  onsubmit="return false;" onKeypress="if (event.keyCode==13) return false;">
				<input type="hidden" name="' . $this->form ['TABLE'] . '"/>
							<input type="hidden" name="form" value="' . $in ['form'] . '"/>
									<input type="hidden" name="link_to" value="' . $this->form ['LINK_TO'] . '"/>
											<input type="hidden" name="link_to_send" value="' . $this->form ['LINK_TO_SEND'] . '"/>
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
			<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
					<!-- CAMPI -->' . $testo_rev;
					$template_form_html = '
					<table class="sf" align="center" border="0" cellpadding="2" cellspacing="2" width="100%"><tr>
					<!-- CAMPI -->';
			$template = '';
			//			for($i = 0; $i < $colonne; $i ++) {
			//				$this->body .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
			//				$template_form_html .= "<td width=\"" . $width . "%\">&nbsp;</td><td width=\"" . $width . "%\">&nbsp;</td>";
			//			}
			$this->body .= "</tr>";
			$template_form_html .= "</tr>";
	
			}
	
			$c = 0;
			foreach ( $this->fields as $i => $val ) {
			if ($val ['CONDITION'] != '')
				$condition_array [count ( $condition_array )] = $val ['CONDITION'];
			}
			$condition_array = array_unique ( $condition_array );
			if ($equery){
	
			$_GET['VISITNUM_PROGR']-=0;
	
			$sql_query="select * from {$this->service}_eqfield where
				--eq_int=$equery_int and
				esam={$_GET['ESAM']}
				and visitnum={$_GET['VISITNUM']}
				and visitnum_progr={$_GET['VISITNUM_PROGR']}
					and progr={$_GET['PROGR']}
					and {$this->PK_SERVICE}={$_GET[$this->PK_SERVICE]}
					and statofield=2
					";
	
					$sql->exec($sql_query);
	
					foreach ($this->tb_vals as $k=>$v) $this->old_values[$k]=$v;
					while ($sql->get_row()){
					$this->tb_vals[$sql->row['FIELD']]=$sql->row['VALORE'];
			}
	
	
		}
			foreach ( $this->fields as $i => $val ) {
			if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
				$field_type = "field_{$val['TYPE']}";
				else
				$field_type = "field";
	
					// 			if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
				// 				include_once $this->config_service['field_lib'] . $field_type . ".inc";
				// 			} else
					// 			include_once "{$field_type}.inc";
				/**
				*  Modifica 08/09/2011
				* Carico prima i campi modificati per servizio se esistono
				* M. Verrocchio
				**/
				if (!class_exists($field_type)) {
				if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'].$field_type.".inc")) {
				include_once $this->config_service['field_lib'].$field_type.".inc";
				} elseif (file_exists("{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc")) {
				include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc";
				} else {
				include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/fields/{$field_type}.inc";
				}
				}
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
				$field_obj->make_open_html ($equery);
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
			$this->salva_js .= '
			rc=contr(c1,specifiche);
			if (rc) {return false}
				if(checks){
				' . $controlli . '
	}
						if (!rc){
						if(checks){
							' . $js_function_on_save . '
	}
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
		$this->invia_js .= '
				rc=contr(c1,specifiche);
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
											$integra_button_text="Integrate Form";
													$eq_note_msg="eQuery general comment:";
													$msg_generale_obbl="General comment is necessary for eQuery";
													$msg_field_obbl="Field comment is necessary for eQuery";
													}else{
				$integra_button_text="Integra Scheda";
				$eq_note_msg="eQuery, commento generale:";
				$msg_generale_obbl="Commento generale obbligatorio per le eQuery";
				$msg_field_obbl="Commento al campo obbligatorio per le eQuery";
											}
											// Textarea per il DE, nel caso voglia fare un eQ:
												if(isset($_GET['ABILITA_EQ_DE'])){
												// Nella check_eqfield controllo prima che almeno una textarea per campo sia stata aperta, altrimenti messaggio di alert
												// Successivamente controllo che tali textarea sia compilate altrimenti messaggi odi alert.
	
				$this->body .= '<script>
						function check_eqfield_de(){
						var el;
						var f;
						var result;
						var check;
						var espressione = /EQAREADE_/;
						f=document.forms[0];
						el=f.elements;
						result = true;
						check = false;
						for (i=0;i<el.length;i++) {
						if(	espressione.test(el[i].name) && el[i].style.display!=\'none\'){
						check = true;
											}
			}
						if(check==false){
						alert(\''.$msg_field_obbl.'\');
								return false;
			}
								for (i=0;i<el.length;i++) {
								if(el[i].style.display!=\'none\' && el[i].value==\'\' && espressione.test(el[i].name) ){
								alert(\''.$msg_field_obbl.'\');
										return false;
											}
											}
										return true;
											}
											</script>';
				$this->body .= '
						<input type="hidden" value="'.$equery_int.'" name="EQUERY_INT">
								<tr><br><td align=center><input type="submit" style="width:150px; height:50px; cursor:pointer; border:1px outset #0000FF" value="'.$integra_button_text.'" name="salva" onclick="if(!check_eqfield_de()){return false; }else{invia_f();}"/></td></tr>';
	
	
	
											}
											// Fine Textarea per il DE, nel caso voglia fare un eQ:
	
											$exclude_send_buttons=true;
											}
	
											if( $this->config_service['dblock']==1 && isset($this->config_service['dblock'])){
												//Lock del DB , prevede la creazione della tabella nomestudio_dblock
												$sql_query="select * from {$this->service}_DBLOCK where CENTER={$in['CENTER']}";
												$sql=new query($this->conn);
												if ($sql->get_row($sql_query)){
												$center_to_lock=$sql->row['CENTER'];
												$center_lock_sendsave_buttons=$sql->row['SENDSAVE'];
												if($center_to_lock!='' && $center_lock_sendsave_buttons==1)	{
												$lock_send_buttons=true;
												}
												}
			}else{$lock_send_buttons=false;
			}
	
			if(!$exclude_send_buttons && !$lock_send_buttons){
			if ($this->buttons ['SALVA'] && ($in ['USER_TIP'] != 'DM' || isset ( $in ['eform'] )))
			{
	
				if(isset($this->config_service['Mobile']) ){
					$this->body .= '
			<button type="submit" class="submitBtn" value="' . $this->buttons ['SALVA'] . '" name="salva" onclick="salva_f();"/><span>' . $this->buttons ['SALVA'] . '</span></button>';
			}
			else{
			$this->body .= '
			<input type="submit" value="' . $this->buttons ['SALVA'] . ' " name="salva" onclick="salva_f();"/>';
			}
	
			}
			if ($this->buttons ['SUBMIT'] != '')
					$this->body .= '
	
					<input type="submit" value="' . $this->buttons ['SUBMIT'] . '" onclick="submit();"/>';
	
							if ($this->buttons ['INVIA'] && $in ['USER_TIP'] != 'DM' || (isset ( $in ['FORM'] ) || isset ( $in ['SEARCH'] )) )
			{
				if(isset($this->config_service['Mobile']) ){
					$this->body .= '
							<button type="submit" class="submitBtn" value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/><span>' . $this->buttons ['INVIA']  . '</span></button>';
			}
			else{
					$this->body .= '
						<input type="submit"  value="' . $this->buttons ['INVIA'] . '" name="invia" onclick="invia_f();"/>';
			}
	
			}
	
			if ($in ['USER_TIP'] == 'DM' && ! isset ( $in ['FORM'] ) && ! isset ( $in ['SEARCH'] ) ) {
				if($this->config_service['lang']=="en") {
					$reason="Reason for change:";
							$send="Send";
					$opt1="Obvious correction";
						$opt2="Data entry error";
					$opt3="Split/collapse of entry";
							$opt4="Thesaurus codification";
					$opt5="Investigator comment";
							$alert_msg="WARNING!!! It\\'s necessary to choose a reason for the revision";
				} else {
					$reason="Motivo della modifica:";
					$send="Procedi";
							$opt1="Correzione ovvia";
					$opt2="Errore inserimento dati";
					$opt3="Scissione/collasso nell'inserimento";
								$opt4="Codifica del dizionario";
								$opt5="Commento dell'investigatore";
								$alert_msg="ATTENZIONE!!! E\\' necessario scegliere un motivo della modifica";
			}
	
			$this->body .= "$reason
			<select name='ID_QUERY' disabled >
			<!--option ></option>
			<OPTION VALUE=\"-1\">$opt2</option-->
			<OPTION VALUE=\"-2\">$opt1</option>
			<!--OPTION VALUE=\"-3\">$opt3</option>
			<OPTION VALUE=\"-4\">$opt4</option>
			<OPTION VALUE=\"-5\">$opt5</option-->
			$equery_option
			</select><br/>
			<input type=\"submit\" value=\"$send\" name=\"invia_dm\" onclick=\"
			if (document.forms[0].ID_QUERY.value!='') invia_f();
			else {alert ('$alert_msg');document.forms[0].ID_QUERY.focus(); return false;}
					\"/>
				";
			}
							if ($this->buttons ['ANNULLA'])
									$this->body .= '
						<input type="reset" value="' . $this->buttons ['ANNULLA'] . '" name="annulla" />';
									}
									$this->body .= '</p></table>';
	
		if(isset($_GET['ABILITA_EQ_DE']) && $_GET['ABILITA_EQ_DE']!='')
			{
			$this->body.= $this->riassunto_eq_per_esam($in [$this->PK_SERVICE],$in ['ESAM'],$in ['PROGR'],$in ['VISITNUM'],$in ['VISITNUM_PROGR']);
			}
	
	
			if(!$exclude_send_buttons) $this->body .= '</form>';
			$config_service=$this->config_service;
									if ($config_service ['PK_SERVICE'] == '')
										$this->PK_SERVICE = 'CODPAT';
										else
										$this->PK_SERVICE = $config_service ['PK_SERVICE'];
										global $vlist;
										if (!isset($in['SEARCH']) && $in [$this->PK_SERVICE] != '' && ! isset ( $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] ) && !$exclude_send_buttons) {
			$this->body .= '
					<p align=left><a href="index.php?exams=visite_exams.xml&amp;CENTER=' . $in ['CENTER'] . '&amp;' . $this->PK_SERVICE . '=' . $in [$this->PK_SERVICE].'" onclick="history.back(); return false;">&lt;&lt;' . $config_service ['Torna_lista_schede'] . '</a></p>';
			}
	
			$href_alternativo = "index.php?CENTER=" . $in ['CENTER'] . "&{$this->PK_SERVICE}=" . $in [$this->PK_SERVICE] . "&VISITNUM=" . $in ['VISITNUM'] . "&ESAM=" . $in ['ESAM'] . "&PROGR=" . $in ['PROGR'] . "&DOWN=1";
			$this->body = preg_replace ( "/#HREF#/", $href_alternativo, $this->body );
	
		}
}

class xml_vlist extends xml_vlist_prototype{}

class xml_page extends xml_page_prototype{}

class xml_list extends xml_list_prototype{}

class legend extends legend_prototype{}

class user extends user_prototype{}

class xml_esams_list extends xml_esams_list_prototype{}

// Includo le f_to_calls abilitate (rinominate E_)
$f_to_calls_dir = substr($_SERVER['SCRIPT_FILENAME'],0,strrpos($_SERVER['SCRIPT_FILENAME'],"/"))."/f_to_calls";
//echo $f_to_calls_dir;
if (is_dir($f_to_calls_dir)) {
    if ($dh = opendir($f_to_calls_dir)) {
        while (($file = readdir($dh)) !== false) {
        	if (reset(explode('_', $file)) == "E") {
        		include_once "f_to_calls/".$file;
        	}
        }
        closedir($dh);
    }
}

function var_glob($value){
	global $in;
	global $inputval;
	if (isset($inputval[$value]) && $inputval[$value]!='') return $inputval[$value];
	if (isset($in[$value]) && $in[$value]!='') return $in[$value];
	if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') return $GLOBALS[$value];
}

function error_page($user, $error, $error_spec){
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;
	
	
	//TODO: sistemare link a ErrorPage 
	include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/ErrorPage.v2.inc";
	$ErrorPage=new error_page();
	$ErrorPage->cineca_user ="v.mazzeo@cineca.it";
	$ErrorPage->hd_pierrelgroup="";
	$ErrorPage->send_error_page($filetxt,$in,$SRV,$log_conn,$service,$remote_userid,$session_number,$user, $error, $error_spec);
	//$ErrorPage->print_error_page($filetxt, $error, $error_spec);
}

?>
