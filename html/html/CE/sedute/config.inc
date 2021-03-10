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
include_once "/http/lib/wkpdf/WKPDF.php";
include_once "send_email_common.inc";

include_once "study.inc.mproto.php";

//$reflector = new ReflectionClass('legend_prototype');
//echo $reflector->getFileName();
//echo get_include_path ();
//
//echo "<br><br>".realpath ( 'libs/legend.inc' );
//echo "<br><br>".realpath ( '/http/servizi/siss-bundle-01/comitatietici-online.cineca.it/html/sedute/libs/legend.inc' );

define("AREA_OFFSET", 10000000);

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

$conn=new dbconn();
$sql=new query($conn);

//$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'");
$sql->ins_upd();

$config_service=null;
$config_service['PRJ']=200;

$config_service['Menu_paziente']='Menu Riunione';
$config_service['Lista_schede']='Dettaglio Riunione';
$config_service['Patients_list']='Lista Riunioni';
$config_service['Torna_lista_schede']='Torna al dettaglio Riunione';

//CONFIGURAZIONI GIULIO AD-HOC
$config_service['SHOW_MANDATORY_ON_HIDE']=true;
//lascia i buchi nelle progressive
$config_service['ALLOW_BLANK_PROGR']=true;
//lascia i buchi nelle visite progressive
$config_service['ALLOW_BLANK_VPROGR']=true;

#Forzatura per il salavataggio dei doc generali, doc centro specifici e centri a studio inviato in BD
//echo "<pre>";
//print_r($config_service['ALWAYS_SAVEABLE']);
//echo "</pre>";
//TODO: CHECK QUI!
$config_service['ALWAYS_SAVEABLE']['2']['20']=true; #documenti verbale

class xml_form extends xml_form_prototype{}

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
			$params=split(",",$param);
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
		if ($this->cols [$i] ['IMG'] != '')
		$img = "images/{$this->cols[$i]['IMG']}"; else
		$img = "images/lente.gif";
		$value = "<img src=\"$img\" width=32 border=0>";

		return $value . "&nbsp;";
	}
	
}


class legend extends legend_prototype{}

class user extends user_prototype{}

//class xml_esams_list extends xml_esams_list_prototype{}
include_once "esams_list.inc";


function var_glob($value){
	global $in;
	global $inputval;
	if (isset($inputval[$value]) && $inputval[$value]!='') return $inputval[$value];
	if (isset($in[$value]) && $in[$value]!='') return $in[$value];
	if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') return $GLOBALS[$value];
}
function error_page_old($user, $error, $error_spec){
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;
	#echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
	$today = date("j/m/Y, H:m:s");
	if (is_array($error_spec)) foreach ($error_spec as $key => $val) $spec.="\n $key : $val";
	mail($email_admin, "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n");
	$body="<p align=center><font size=4><b>Si ?erificato un errore</b></p><br><br>$error_spec<br>$error";
	$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
	die($filetxt);
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
			$debug = debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS);
			//debug_print_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS);
			//  foreach($debug as $key => $val) {
			//   foreach($val  as $k => $v) {
			//    $debug_info.=$k." ".$v."<br />";
			//   }
			//  }
			$body="<h2>ERRORE DEVEL (CONFIG)</h2><h3>$error</h3><br />$debug_info";
			if ($_GET['DEBUG']){
				$body.= "<pre>";
				$body.= print_r($debug,true);
				$body.="</pre>";
			}
			//  print_r($debug[0]);
			//  $debug_info=var_export($debug,true);
		}
		mail($email_admin, "Errore[".$in['remote_userid']."]$prod",$alltxt, $headers);
		$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
		die($filetxt);

	}
 
	///////////////F_TO_CALLS/////////////
	function componenti_merge(){
		global $in;
		global $conn;
		global $service;
		global $study_;
		if ($in['USER_TIP']=='DE' && !isset($in['ajax_call'])){
			//print_r($in);
			//die("QUA");
			//echo "<br/>";
			$dst = "CONVOCAZIONI";
			$src = array("CONVOCAZIONI_ESTERNI","CONVOCAZIONI_SPERIMENTATORI");
			/*
			foreach ($in as $key => $val){
				foreach ($src as $s){
					if (preg_match("!^{$s}_MCHECK_!", $key)){
						$valore=str_replace("{$s}_MCHECK_", "", $key);
						$valore = $dst."_MCHECK_".$valore;
						echo $valore;
						if (!isset($valore)){
							$in[$valore] = $in[$key];
						}
						//$value.=$valore."|";
					}
				}
			}
			*/
			//print_r($study_->pk_service);
			//die($study_->xmr->pk_service);
			$pksv = $study_->xmr->pk_service;
			$pkid = $in[$study_->xmr->pk_service];
			$sql=new query($conn); 
			
			$sql_query="select * from {$service}_sel_componenti where {$pksv} = {$pkid} "; // and esam=1";
			$sql->exec($sql_query);
			$dval = "";
			if ($sql->get_row()){
				//echo  "PAOSLI";
				$dval = $sql->row[$dst];
				//echo  "<br/>$dval<br/>";
				$dval = explode("|",$dval);
				foreach ($src as $s){
					$tmp = $sql->row[$s];
					//echo  "<br/>$tmp<br/>";
					$tmp = explode("|",$tmp);
					$tmp = array_diff($tmp,$dval);
					$dval = array_merge($dval,$tmp);
				}
			}
			$dval = implode("|",$dval);
			
			$sql_close="update {$service}_sel_componenti set $dst ='$dval' where {$pksv} = {$pkid} ";
			//die($sql_close);
			$sql->set_sql($sql_close);
			//echo("$sql_close<br/>");
			$sql->ins_upd();
			
			//print_r($in);
			//die();
		}
	}
	
	function creaPDF_odg(){
		global $in;
		global $service;
		$center = $in['CENTER'];
		//die("CENTER: {$in['CENTER']}");
		$file = "/odg.html";
		// if(!file_exists($_SERVER['DOCUMENT_ROOT'].$file)) {
			// $file = "/odg.html";
		// } 
		creaPDF("odg", $file);
	}
	
	function creaPDF_verbale(){
		global $in;
		global $service;
		$center = $in['CENTER'];
		//die("CENTER: {$in['CENTER']}");
		$file = "/verbale.html";
		// if(!file_exists($_SERVER['DOCUMENT_ROOT'].$file)) {
			// $file = "/verbale_{$in['CENTER']}.html";
		// } 
		creaPDF("verbale", $file);
	}
	
	function creaPDF($type, $template){
		//creazione pdf
		global $in;
		global $conn;
		global $service;
		global $study_;
		if ($in['USER_TIP']=='DE' && !isset($in['ajax_call'])){
			$pksv = $study_->xmr->pk_service;
			$pkid = $in[$study_->xmr->pk_service];
			//Progressivo esam (sempre 1 direi)
			$prq = 1;
			//Base dir per i file generati e template
			$dir="{$_SERVER['DOCUMENT_ROOT']}/gendocs";
			//Template
			$ptfile=$template;  
			//print_r($in);
			
			
			//Tabella
			$tabella="{$service}_REGISTRAZIONE";
			//Query recupero dati registrazione
			$sql_q="select * FROM $tabella WHERE {$pksv}='{$pkid}' and progr=$prq";
			//echo "$sql_q.<hr>";
			$sql=new query($conn);
			$sql->set_sql($sql_q);
			$sql->exec();
			$sql->get_row();
			$reg = $sql->row;
			//print_r($reg);
			//echo "<br/>";
			//die();
			//echo $ptfile;
			//echo "Cols=$sql->numcols<hr>";
			//echo $dir.$ptfile;
			$file_txt= file_get_contents($dir.$ptfile);
			//echo $file_txt."<hr>";
			//die();
			
			//$file_txt=preg_replace("/\[(.*?)\]/em","var_glob('\\1')" , $file_txt);	
			
			$ora_inizio = sprintf("%02d:%02d", $reg['ORA_INIZIO_H'], $reg['ORA_INIZIO_M']);
			$file_txt = str_replace("#ODG_INTESTAZIONE#",$in['ODG_INTESTAZIONE'],$file_txt);
			$file_txt = str_replace("#ODG#",$in['ODG'],$file_txt);
			$file_txt = str_replace("#VERBALE#",$in['VERBALE'],$file_txt);
			$file_txt = str_replace("#NOW#",date("d/m/Y"),$file_txt);
			$file_txt = str_replace("#ORA_INIZIO#",$ora_inizio,$file_txt);
			$file_txt = str_replace("#DATA_SEDUTA#",$reg['DATA_SED_DT'],$file_txt);
			
			$tabella_1="GSE_LISTA_COMPONENTI";
			//Query recupero dati componenenti
			$sqlq_1="select * FROM $tabella_1 t WHERE CENTER={$in['CENTER']} order by cognome";
			//echo "$sqlq_1.<hr>";
			$sql_1=new query($conn);
			$sql_1->set_sql($sqlq_1);
			$sql_1->exec();
			$count_comp=1;
			$componenti='';
			$componenti_1='';
			$componenti_2='';
			$presidente='';
			
			while($sql_1->get_row()){
				
				//echo "{$sql_1->row['COGNOME']} $count_comp<br>";
				
				if($sql_1->row['MEMO']!='Presidente' && $count_comp<=9) {
					$count_comp++;
					$componenti_1.="<i>{$sql_1->row['QUALIFICA']} {$sql_1->row['NOME']} {$sql_1->row['COGNOME']} <br/> {$sql_1->row['RUOLO']}<br/><br/></i>";
				}
				else if($sql_1->row['MEMO']!='Presidente' && $count_comp>9) {
					$componenti_2.="<i>{$sql_1->row['QUALIFICA']} {$sql_1->row['NOME']} {$sql_1->row['COGNOME']} <br/> {$sql_1->row['RUOLO']}<br/><br/></i>";
				}
				if($sql_1->row['MEMO']=='Presidente') $presidente="{$sql_1->row['QUALIFICA']} {$sql_1->row['NOME']} {$sql_1->row['COGNOME']} <br/> </i>{$sql_1->row['RUOLO']}<br/><br/></i>";
			}
			
			$componenti_2.="<i>e.p.c.</i><br/><br/>";
			
			//Query recupero dati membro esterno fisso LEONE
			$sqlq_2="select * FROM ana_utenti_2 WHERE id_ce=9 and profilo='CMP' and subprofilo='EXT' and userid='LEONE'";
			//echo "$sqlq_2 <hr>";
			$sql_2=new query($conn);
			$sql_2->set_sql($sqlq_2);
			$sql_2->exec();
			$sql_2->get_row();
			$componenti_2.="<i>{$sql_2->row['QUALIFICA']} {$sql_2->row['NOME']} {$sql_2->row['COGNOME']} <br/> {$sql_2->row['RUOLO']}<br/><br/></i>";
			
			$componenti_2.="<i><u>LORO SEDI</u></i><br/><br/>";
			
			$file_txt = str_replace("#PRESIDENTE#",$presidente,$file_txt);
			$file_txt = str_replace("#COMPONENTI1#",$componenti_1,$file_txt);
			$file_txt = str_replace("#COMPONENTI2#",$componenti_2,$file_txt);
			
			if($_GET['DEBUG']==1) echo $file_txt."<hr>";
			//die(1);
			$f_dir=$dir."/documents/";
			//$fd=$in['RICHIESTA']."_".$in['VISITNUM']."_".$in['ESAM']."_".$in['PROGR'];
			$fd=$in['ID_SED'];
			$nomefile=$f_dir.$type."_htm_".$fd.".htm";
			$pdffile=$f_dir.$type."_".$fd.".pdf";
			$linkfile="/gendocs/documents/".$type."_".$fd.".pdf";
			if($_GET['DEBUG']==1) echo "$fd<hr> $f_dir<hr> $nomefile<hr> $pdffile<hr> $linkfile<hr>";
			//die();
			
			$htmlf = fopen( $nomefile, "w");
			
			if ($htmlf) {
				fputs ($htmlf, $file_txt);
			}else{
				echo "CAPPERILLO!!<hr>";
			}
			fclose ($htmlf);
			
			//echo $file_txt;
			//die();
			
			//
			//
			//
			//$rc=system('/http/local/bin/htmldoc_rw -t pdf14  --no-title --size A4  --browserwidth 800 --footer .t. --header ... --headfootsize 8 --headfootfont Times-Italic--bottom 5mm --top 5mm --left 5mm --right 5mm --path /amministrazione/schede_utente --webpage '.$nomefile.' > '.$pdffile,$ret);
			//die($ret);
			
			$path = $_SERVER ['PATH_TRANSLATED'];
			//echo $_SERVER ['PATH_TRANSLATED'];
			//die();
			$images_path = str_replace ( "index.php", "../gendocs/", $path );
			
			$wk=new WKPDF();
			$wk->set_page_size("A4"); //formato pagina 
			//$wk->set_toc(true); //aggiunge sommario
			$wk->set_title("Test1"); //aggiugne titolo
			//$wk->pageNumber(true); //aggiunge numerazione alle pagine
			if ($in['CENTER']==1) $html_header="$images_path/header_avr.html";
			if ($in['CENTER']==2) $html_header="$images_path/header_avn.html";
			if ($in['CENTER']==3) $html_header="$images_path/header_avc.html";
			$wk->pageHeader($html_header);
			if ($in['CENTER']==1) $html_footer="$images_path/footer_avr.html";
			if ($in['CENTER']==2) $html_footer="$images_path/footer_avn.html";
			if ($in['CENTER']==3) $html_footer="$images_path/footer_avc.html";
			$wk->pageFooter($html_footer);
			$wk->render("{$nomefile}");
			$wk->output(WKPDF::$PDF_SAVEFILE, $pdffile);
			
			//die($linkfile);
		}			
	}

	function action_osservazioni(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			//if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DELLE OSSERVAZIONI
				$id_area = 2;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="OSSERV_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Osservazioni', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			//}
		
	}		
	
	function action_relazione(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			//if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DELLE OSSERVAZIONI
				$id_area = 2;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="RELAZ_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Relazioni', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			//}
		
	}

	function action_osservazioni_eme(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			//if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DELLE OSSERVAZIONI
				$id_area = 2;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="OSSERV_EME_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Osservazioni Emendamento', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			//}
		
	}		
	
	function action_relazioni_eme(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];
			
			//if ($in['INVIOCO'] == 1){
				
				//APPROVO I DOCUMENTI ALLEGATI ALLA SCHEDA DELLE OSSERVAZIONI
				$id_area = 2;
				$id_tipo_ref = $pkid + (AREA_OFFSET*$id_area);
				
				$kw="RELAZ_EME_FILE";
				
				if ($in['VISITNUM_PROGR']>0 || $in['PROGR']>1) {
					if($in['VISITNUM_PROGR']>0) $kw.="_{$in['PROGR']}_{$in['VISITNUM_PROGR']}";
						else $kw.="_{$in['PROGR']}";
				}
				
				$sql_update="update docs set approv_comm='Invio Scheda Relazioni Emendamento', approved=1, approv_dt=sysdate, approved_by='$user' where id in (
   			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   			) and tipo_doc='Doc_Area' and keywords ='$kw'";
   			Logger::send($sql_update);
				$sql=new query($conn);
				$sql->set_sql($sql_update);
				$sql->ins_upd();
				
			//}
		
	}

	function link_parere_odg_verbale($xml_form){
		//collego il parere all'odg o verbale (dipende quale scheda sto salvando)
		global $in;
		global $conn;
		global $service;
		global $study_;
		
		Logger::send($xml_form->session_vars);

		if($xml_form->session_vars['VISITNUM']==0 && $xml_form->session_vars['ESAM']==1){
			$table="gse_sel_studi";
			$field="link_odg";
			
			//$sql_update_clear="update ce_valutazione set {$field}={$in['ID_SED']} where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1 and progr=(select max(progr) from ce_valutazione where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1)";
			$sql_update_clear="update ce_valutazione set {$field}='', link_verbale='' where {$field}={$in['ID_SED']}";
   		Logger::send($sql_update_clear);
			$sql_clear=new query($conn);
			$sql_clear->set_sql($sql_update_clear);
			$sql_clear->ins_upd();
			
			$sql_update_clear_eme="update ce_eme_valutazione set {$field}='', link_verbale='' where {$field}={$in['ID_SED']}";
   		Logger::send($sql_update_clear_eme);
			$sql_clear_eme=new query($conn);
			$sql_clear_eme->set_sql($sql_update_clear_eme);
			$sql_clear_eme->ins_upd();
			
			}
			
		if($xml_form->session_vars['VISITNUM']==2 && $xml_form->session_vars['ESAM']==1){
			$table="gse_pres_studi";
			$field="link_verbale";
			
			//$sql_update_clear="update ce_valutazione set {$field}={$in['ID_SED']} where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1 and progr=(select max(progr) from ce_valutazione where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1)";
			$sql_update_clear="update ce_valutazione set {$field}='-9900'";
   		Logger::send($sql_update_clear);
			$sql_clear=new query($conn);
			$sql_clear->set_sql($sql_update_clear);
			$sql_clear->ins_upd();
			
			$sql_update_clear_eme="update ce_eme_valutazione set {$field}='-9900'";
   		Logger::send($sql_update_clear_eme);
			$sql_clear_eme=new query($conn);
			$sql_clear_eme->set_sql($sql_update_clear_eme);
			$sql_clear_eme->ins_upd();
					
			}
		
		if (!isset($in['ajax_call'])){
		
			//STUDI
			$sql_query_1="select * from {$table} where id_sed={$in['ID_SED']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']}";
			Logger::send($sql_query_1);
			$sql_1=new query($conn);
			$sql_1->set_sql($sql_query_1);
			$sql_1->exec();
			$sql_1->get_row();
			
			Logger::send($sql_1->row['STUDI']);
			$studi = explode("|",$sql_1->row['STUDI']);
			Logger::send($studi);
			for ($k = 0; $k<count($studi);$k++){
				$s = $studi[$k];
				$s = trim($s);
				$stud_center = explode("_",$s);
				$id_stud=$stud_center[0];
				$param_center=$stud_center[1];
				Logger::send($id_stud." ".$param_center);
				
				if(is_numeric($id_stud)){
					$sql_update_s="update ce_valutazione set {$field}={$in['ID_SED']} where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1 and progr=(select max(progr) from ce_valutazione where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1)";
   				Logger::send($sql_update_s);
					$sql_s=new query($conn);
					$sql_s->set_sql($sql_update_s);
					$sql_s->ins_upd();
				}
	  	
			}
			
			//STUDI SOSPESI
			Logger::send($sql_1->row['STUDI_SOSPESI']);
			$studi_sospesi = explode("|",$sql_1->row['STUDI_SOSPESI']);
			Logger::send($studi_sospesi);
			for ($k = 0; $k<count($studi_sospesi);$k++){
				$s = $studi_sospesi[$k];
				$s = trim($s);
				$stud_center = explode("_",$s);
				$id_stud=$stud_center[0];
				$param_center=$stud_center[1];
				Logger::send($id_stud." ".$param_center);
				
				if(is_numeric($id_stud)){
					$sql_update_ss="update ce_valutazione set {$field}={$in['ID_SED']} where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1 and progr=(select max(progr) from ce_valutazione where id_stud={$id_stud} and visitnum=4 and visitnum_progr=$param_center-1 and esam=1)";
   				Logger::send($sql_update_ss);
					$sql_ss=new query($conn);
					$sql_ss->set_sql($sql_update_ss);
					$sql_ss->ins_upd();
				}
	  	
			}
			
			//EMENDAMENTI
			Logger::send($sql_1->row['STUDI_EMENDAMENTI']);
			$studi_eme = explode("|",$sql_1->row['STUDI_EMENDAMENTI']);
			Logger::send($studi_eme);
			for ($k = 0; $k<count($studi_eme);$k++){
				$s = $studi_eme[$k];
				$s = trim($s);
				$stud_center = explode("_",$s);
				$id_stud=$stud_center[0];
				$param_1=$stud_center[1];
				$param_2=$stud_center[2];

				if(is_numeric($id_stud)){
		    	$sql_update_e="update CE_EME_VALUTAZIONE set {$field}={$in['ID_SED']} where id_stud={$id_stud} and visitnum=20 and visitnum_progr={$param_1} and esam=3 and progr={$param_2}";
   				Logger::send($sql_update_e);
					$sql_e=new query($conn);
					$sql_e->set_sql($sql_update_e);
					$sql_e->ins_upd();
				}

			}
			
			//EMENDAMENTI SOSPESI
			Logger::send($sql_1->row['STUDI_EME_SOSP']);
			$studi_eme_sosp = explode("|",$sql_1->row['STUDI_EME_SOSP']);
			Logger::send($studi_eme_sosp);
			for ($k = 0; $k<count($studi_eme_sosp);$k++){
				$s = $studi_eme_sosp[$k];
				$s = trim($s);
				$stud_center = explode("_",$s);
				$id_stud=$stud_center[0];
				$param_1=$stud_center[1];
				$param_2=$stud_center[2];
				
				if(is_numeric($id_stud)){
					$sql_update_e="update CE_EME_VALUTAZIONE set {$field}={$in['ID_SED']} where id_stud={$id_stud} and visitnum=20 and visitnum_progr={$param_1} and esam=3 and progr={$param_2}";
   				Logger::send($sql_update_e);
					$sql_e=new query($conn);
					$sql_e->set_sql($sql_update_e);
					$sql_e->ins_upd();
				}
	  	
			}
			
		}
		
	}
	
	function force_doc_verb(){
		global $in;
		global $conn;
		global $study_;
		
		$pkid = $in[$study_->xmr->pk_service];
		$user=$in['remote_userid'];

		if ($in['FORCE_DOC_VERB']=="yes"){
			
				$sql = new query ($conn);
				$sql_update="update gse_coordinate set visitclose=1,fine=1 where id_sed={$in['ID_SED']} and visitnum={$in['VISITNUM']} and esam={$in['ESAM']} and progr={$in['PROGR']} ";
				$sql->set_sql($sql_update); 
				$sql->ins_upd();
				
				Logger::send($sql_update);
				
				$conn->commit();
				}
	}	
	
	function registra_riunione(){
		global $study_;
		global $in;
		global $conn;
		global $study_;
		
		$study_->openEsamProgr($in['ID_SED'],0,0,11,1);
	
		$sql = new query ($conn);
		$sql_insert="insert into gse_cronologia_odg (id_sed,visitnum,visitnum_progr,esam,progr,userid_ins,tipo,d_tipo) values ({$in['ID_SED']},'{$in['VISITNUM']}','0','11','1','{$in['remote_userid']}','1','Convocazione') ";
		$sql->set_sql($sql_insert); 
		$sql->ins_upd();
		//Logger::send($sql_insert);
		$conn->commit();

	}

	//////////////FINE F_TO_CALLS/////////

?>
