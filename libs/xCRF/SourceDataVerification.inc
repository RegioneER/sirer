<?
//include_once "http_lib.inc";
include_once "study_prototype.inc";

define ("SDV_LTYPE_STATUS", 1);
define ("SDV_LTYPE_SIGNATURE", 2);
define ("SDV_LTYPE_VIOLATION", 3);


function _sdv_replace_globals($matches){
    return var_glob($matches[1]);
    //var_glob('\\1')
}

 /**
  * Classe di gestione dell'SDV
  *
  * @package CRO
  */
 class SourceDataVerification{

     public $regTable;


     /**
 	 * Costruttore dell'oggetto, vengono presi in ingresso le informazione relative alla
     * connessione oracle, al prefisso in banca dati del serviio, alle configurazioni di sistema,
 	 * e all'array multiplo $vlist contenente lo schema delle form xml, degli esami e delle visite dello studio.
 	 *
 	 * @param String $service
 	 * @param dbconn_hyper $conn
 	 * @param array $config_service
 	 * @param array $attributes
 	 * @param from $xml_form
 	 * @return SDV
 	 */
 	function SourceDataVerification( $service=null, $conn=null, $config_service,$attributes,$xml_form ){


 		$this->conn = $conn;
 		$this->service = $service;
 		$this->config_service = $config_service;
 		$this->attributes = $attributes;
 		$this->xml_form = $xml_form;

        $this -> regTable = $config_service['RegTable'];


 	}
 	
 	function SDV_validate($values , $xml_form){
        $pk=null;
 		$this->table_exist($xml_form);
 		
 		$sql=new query($this->conn);
 		
 		foreach($xml_form->fields as $key=>$val){
 			foreach($values as $key_sdv=>$val_sdv){
 				if("SDV_".$val['VAR']==$key_sdv){
 					if($val_sdv=="on"){$val_sdv=1;}
 					else{$val_sdv=0;}
 					
 					$vals['VISITNUM']=$xml_form->session_vars['VISITNUM'];
					$vals['VISITNUM_PROGR']=$xml_form->session_vars['VISITNUM_PROGR'];
					$vals['ESAM']=$xml_form->session_vars['ESAM'];
					$vals['PROGR']=$xml_form->session_vars['PROGR'];
					$vals['VALIDATED']=$val_sdv;
					$vals[$xml_form->PK_SERVICE]=$xml_form->session_vars[$xml_form->PK_SERVICE];
					$vals['CENTER']=$xml_form->session_vars['CENTER'];
					$vals['NOMETAB']=$xml_form->form['TABLE'];
					$vals['VAR']=$val['VAR'];
					$vals['MODDT']=sysdate;
					$vals['USERID']=$xml_form->session_vars['remote_userid'];
					$vals['ACTION']="Validation";
					$sql->insert($vals, $this->config_service['service']."_SDV",$pk);
 				}
			}
 		}
// 		print_r($vals);die();
 		$this->conn->commit();
// 		print_r($values);die();
 	
 	}
 	
 
		/**SDV_html($in=null)
		 *
 		 * Questo medoto genera un tabella affiancando la classica tabella riassuntiva del paziente.
 		 * In tale tabella  presente il link per abilitare/disabilitare la scheda alla modalit Audit Trail.
 		 *
 		 * @param array $in
 		 * @return $SDV_bar
 		 */
 	function SDV_html($in=null){
        $SDV_checkbox=null;
        $link_SDV=null;
        $index=null;
		global $in;

 		$progr="";
 		$progr_link="";
 		if($in['PROGR']!=''){
 			$progr=" and progr={$in['PROGR']}";
 			$progr_link="&PROGR={$in['PROGR']}";
 			}

		$sql_query="
		select  fine
		  from {$this->service}_coordinate
		  where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and esam={$in['ESAM']} and visitnum={$in['VISITNUM']} $progr and VISITNUM_PROGR={$in['VISITNUM_PROGR']}
		 ";
		 $sql=new query($this->conn);
		$sql->set_sql($sql_query);
		$sql->exec();
		while(
		$sql->get_row()){
			if (isset($sql->row['FINE']) && $sql->row['FINE']=='1') {
				$closed_form=$sql->row['FINE'];
			}
		}

		if (isset($closed_form) && $closed_form=='1') {
		 		if($this->config_service['lang']=="en") {
						$link_set_SDV="Set SDV";
						$link_unset_SDV="Unset SDV";
					} else {
						$link_set_SDV="Apri SDV";
						$link_unset_SDV="Chiudi SDV";
					}

		 		if (isset($in['SDV']) && $in['SDV']!='') {
					$SDV_checkbox.="<script>
										function checkAll(){
											var el;
						  					var f;
						  					var espressione = /SDV_/;		
						  					f=document.forms[0];
											el=f.elements;
											if(document.getElementById('SDV').checked== false){
												for (i=0;i<el.length;i++) {
													if(espressione.test(el[i].name)){el[i].checked=false;}
												}
											}
											else{
												for (i=0;i<el.length;i++) {
													if(espressione.test(el[i].name)){el[i].checked=true;}
												}
		 									}
		 								}
									</script>";
					$SDV_checkbox.='<span style=" background-color:#87ceeb; border:#000099 1px solid;padding:6px 8px 2px 4px;margin:8px;"> <input type="checkbox" id="SDV" name="SDV"  onclick="checkAll();"></span>';
		 			
		 			//&REGISTRY={$this->service} levato...
		 			$link_SDV .= "<p align=center>
								<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
								$link_unset_SDV
								</a>
								$SDV_checkbox
							</p>";
					}
				else{
					$link_SDV .= "<p align=center>
							<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&SDV=1\">
							$link_set_SDV
							</a>
						</p>
					";
					}

	 		$SDV_bar="<table class=sf width=100%   align=center>
				<tr>
					<td class=int  align=center  style=\"vertical-align:top; height:15px;\" NOWRAP> SDV </td>
				</tr>
				<tr>
					<td class=int_pt2 align=center style=\"height:50px\" NOWRAP>{$link_SDV}</td>
				</tr>
				</table>
					";
 		} else {
 			$SDV_bar="";
 		}
		return $SDV_bar;
 	}
 	
 	
 	/**
 	 * Crea la tabella per il funzionamento dell'audit trail se non esiste
 	 *
 	 * @param form $xml_form
 	 * @return boolean
 	 */
 	function table_exist($xml_form=null){

		 //creazione tabella se non esiste
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$xml_form->config_service['service']}_SDV')";
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()){
//			print_r($query->row['TABLE_NAME']);
//			print_r($query_check_existence);
			return true;
		}
		else
		{
			// da fare....
			$query_create = "
			create table {$xml_form->config_service['service']}_SDV
			(
			  $xml_form->PK_SERVICE         NUMBER,
			  ESAM           NUMBER,
			  PROGR          NUMBER,
			  VISITNUM       NUMBER,
			  VISITNUM_PROGR NUMBER,
			  VALIDATED      NUMBER,
			  CENTER         VARCHAR2(200 CHAR),
			  NOMETAB        VARCHAR2(200 CHAR),
			  VAR            VARCHAR2(200 CHAR),
			  MODDT          DATE,
			  ACTION         VARCHAR2(200 CHAR),
			  USERID         VARCHAR2(200 CHAR)
			)
			";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
		}
 	}

 	function GetLabels(){
		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
		global $service;
 		if ($this->config_service ['PK_SERVICE'] == '')
		$pk_service = "CODPAT";
		else
		$pk_service = $this->config_service ['PK_SERVICE'];
 		
		$retval = array();
		$retval[$pk_service] = "Patient Id";		
		$retval['SITEID'] = "Center";		
		$retval['SUBJID'] = "Patient Num.";		
		$retval['SIGNDATE'] = "Signature Date";		
		$retval['USERNAME'] = "Username";		
		$retval['FORM_NOTES'] = "Notes";
		return $retval;
 	}
 	
 	function GetPatients(){
		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
		global $service;
 		if (!isset($this->config_service ['PK_SERVICE']) || $this->config_service ['PK_SERVICE'] == '')
		$pk_service = "CODPAT";
		else
		$pk_service = $this->config_service ['PK_SERVICE'];
 		
		$retval = array();
		
		//$query = "select distinct($pk_service) from {$service}_COORDINATE";
		$query = "select * from {$service}_{$this->regTable}";
		$sql = new query ( $conn );
		$sql->set_sql ( $query );
		//print_r ($query);
		$sql->exec ();
		while ( $sql->get_row () ) {
			$retval[$sql->row[$pk_service]] = $sql->row;
		}
		return $retval;
 	}
 	function GetStrategy($ver = false){
		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
		global $service;
 		if ($this->config_service ['PK_SERVICE'] == '')
		$pk_service = "CODPAT";
		else
		$pk_service = $this->config_service ['PK_SERVICE'];
 		
		$retval = array();
		
		if ($ver){
			$where = "WHERE VERSION = $ver";
		}else{
			$where = "WHERE VERSION = (select MAX(VERSION) from {$service}_SDV_STRATEGY)";
		}
		$query = "select * from {$service}_SDV_STRATEGY $where";
 		$sql = new query ( $conn );
		$sql->set_sql ( $query );
		//print_r ($query);
		$sql->exec ();
		while ( $sql->get_row () ) {
			$retval[$sql->row['VISITNUM']][$sql->row['ESAM']][$sql->row['FIELD']] = true;
		}
		return $retval;
 	}
 	function GetNamesFromUsers(){
		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
		global $service;
 		if ($this->config_service ['PK_SERVICE'] == '')
		$pk_service = "CODPAT";
		else
		$pk_service = $this->config_service ['PK_SERVICE'];
 		
		$retval = array();
		
		//$query = "select distinct($pk_service) from {$service}_COORDINATE";
        /*
		$query = "select * from CMM_USERS";
		$sql = new query ( $conn );
		$sql->set_sql ( $query );
		//print_r ($query);
		$sql->exec ();
		while ( $sql->get_row () ) {
			$retval[$sql->row['CMM_USERID']] = $sql->row['NAME'].' '.$sql->row['SURNAME'];
		}
        */
		$query = "select * from ANA_UTENTI";
		$sql = new query ( $conn );
		$sql->set_sql ( $query );
		//print_r ($query);
		$sql->exec ();
		while ( $sql->get_row () ) {
			if (!isset($retval[$sql->row['USERID']])){
				$retval[$sql->row['USERID']] = $sql->row['NOME'].' '.$sql->row['COGNOME'];
			}
		}
		return $retval;
 	}
 	
 	
 	function ListStatusHtml($session_vars=null, $type = SDV_LTYPE_STATUS){
 		//$list = "";
        $html=null;
        $gruppo=null;
		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
		global $service;
		//global $config_service;
		//if($session_vars)$in=$session_vars;
		if($in['PAGE']>0)$this->page=$in['PAGE'];
		if ($this->config_service ['PK_SERVICE'] == '')
		$pk_service = "CODPAT";
		else
		$pk_service = $this->config_service ['PK_SERVICE'];

		$sql = new query ( $conn );
		$sql->set_sql ( "ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'" );
		$sql->ins_upd ();
		//print_r($session_vars);
		
		//GESTIONE QUERY DEI REPORT E CARICAMENTO DATI
		// error_reporting(E_ALL^ E_WARNING);
		// ini_set("display_errors",1);
		$this->patients = $this->GetPatients();
		//print_r($pats);
		$this->strategy = $this->GetStrategy();
		//Labels
		$this->labels = $this->GetLabels();
		//Nome-Cognome da userid
		$this->names = $this->GetNamesFromUsers();
        $i=0;
		switch ($type){
			case SDV_LTYPE_STATUS:
				if ($gruppo){
					$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
					//print_r($visit->group);

					foreach ( $visit->group as $key => $val ) {
						$in_sql = '';
						foreach ( $val ['VISIT'] as $vis => $visval ) {
							if ($in_sql != '')
							$in_sql .= ",";
							$in_sql .= "'$vis'";
						}
						if($this->cols[$i]['REF_TABLE']!='')$ref_table=$this->cols[$i]['REF_TABLE'];
						else $ref_table=$GLOBALS['patients_table'];
						if (! isset ( $fields ))
						$fields = "
							(
								select
									max(nvl(inizio,nvl2(abilitato,0,null)))||' - '||max(nvl(fine,nvl2(abilitato,0,null)))||' - '||min(visitclose)||' - '||max(abilitato)
								from " . $GLOBALS ['service'] . "_COORDINATE
								where " . $GLOBALS ['service'] . "_COORDINATE.visitnum in ($in_sql)
								and " . $ref_table . ".{$pk_service}=" . $GLOBALS ['service'] . "_COORDINATE.{$pk_service}) as v" . $key;
						else
						$fields .= ",
							(
								select
									max(nvl(inizio,nvl2(abilitato,0,null)))||' - '||max(nvl(fine,nvl2(abilitato,0,null)))||' - '||min(visitclose)||' - '||max(abilitato)
								from " . $GLOBALS ['service'] . "_COORDINATE
								where " . $GLOBALS ['service'] . "_COORDINATE.visitnum in ($in_sql)
								and " . $ref_table . ".{$pk_service}=" . $GLOBALS ['service'] . "_COORDINATE.{$pk_service}) as v" . $key;
					}			
				}
				//echo "<br/>".$fields."<br/>";
				//die("AA");
				if ($fields){
					$fields = ", ".$fields;
				}
				$query = "select {$service}_{$this->regTable}.{$pk_service}, {$service}_{$this->regTable}.SITEID, {$service}_{$this->regTable}.SUBJID, {$service}_{$this->regTable}.CENTER from {$service}_{$this->regTable}, {$service}_COORDINATE  WHERE {$service}_{$this->regTable}.{$pk_service}={$service}_COORDINATE.{$pk_service} ";
				break;
			case SDV_LTYPE_SIGNATURE:
				//$query = "select {$service}_{$this->regTable}.CODPAT, {$service}_{$this->regTable}.SITEID, {$service}_{$this->regTable}.SUBJID, {$service}_SIGNSDV.USERNAME, TO_CHAR({$service}_SIGNSDV.SIGNDATE,'DD-MM-YYYY HH24:MI:SS') AS SIGNDATE from {$service}_SIGNSDV, {$service}_{$this->regTable} WHERE {$service}_{$this->regTable}.{$pk_service}={$service}_SIGNSDV.{$pk_service}(+)";
				$query = "select {$service}_{$this->regTable}.CODPAT, {$service}_{$this->regTable}.SITEID, {$service}_{$this->regTable}.SUBJID, {$service}_SIGNSDV.USERNAME, TO_CHAR({$service}_SIGNSDV.SIGNDATE,'DD-MM-YYYY HH24:MI:SS') AS SIGNDATE from {$service}_SIGNSDV, {$service}_{$this->regTable} WHERE {$service}_{$this->regTable}.{$pk_service}={$service}_SIGNSDV.{$pk_service}";
				break;
			case SDV_LTYPE_VIOLATION:
				$query = "select {$service}_{$this->regTable}.{$pk_service}, {$service}_{$this->regTable}.SITEID, {$service}_{$this->regTable}.SUBJID from {$service}_{$this->regTable} ";
				//$query = "select {$service}_SDV_STRATEGY_STATUS.{$pk_service},{$service}_SDV_STRATEGY_STATUS.SITEID,{$service}_SDV_STRATEGY_STATUS.SUBJID,{$service}_SDV_STRATEGY_STATUS.VISITNUM, {$service}_SDV_STRATEGY_STATUS.VISITNUM_PROGR,{$service}_SDV_STRATEGY_STATUS.ESAM,{$service}_SDV_STRATEGY_STATUS.PROGR,{$service}_SDV_STRATEGY_STATUS.FIELD, {$service}_SDV_STRATEGY_STATUS.DATE_VALIDATION, {$service}_SDV_STRATEGY_STATUS.PROTOCOL_VIOLATION from {$service}_SDV_STRATEGY_STATUS, {$service}_{$this->regTable} WHERE {$service}_SDV_STRATEGY_STATUS.{$pk_service} = {$service}_{$this->regTable}.{$pk_service} AND PROTOCOL_VIOLATION IS NOT NULL"; //WHERE FIRMA=1?
				break;
		}
		if ($in['CENTER']){
			if (stripos($query, "WHERE")!==false){
				$query .= " AND ";
			}else{
				$query .= " WHERE ";
			}
			$query .= " {$service}_{$this->regTable}.CENTER='{$in['CENTER']}'";
		}
		if ($type == SDV_LTYPE_STATUS){
			$query .= " group by {$service}_{$this->regTable}.CENTER, {$service}_{$this->regTable}.{$pk_service}, {$service}_{$this->regTable}.SITEID,{$service}_{$this->regTable}.SUBJID";
			//Flusso standard, ordinamento qui
			if ($_GET['ORD'] && $_GET['ORD_TYPE']){
				$query .= " ORDER BY {$_GET['ORD']} {$_GET['ORD_TYPE']} ";
			}
		}else{
			//Flusso "custom" ordinamento dopo.
			$query .= " order by SITEID,SUBJID";
		}
		echo "<!-- ".$query."<hr> -->";
//		echo "<hr />". print_r($in,true) ."<hr /> ";
		//$query = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $query );
        $query = preg_replace_callback( "/\[(.*?)\]/", "_sdv_replace_globals", $query );
		$this->rpp = 1000*1000*1000*4;
		//if (!$this->page){
		//	$this->page=1;
		//}
		//TODO: CAMPO N_R?!?!
		//$navigation_bar="ABC";
		
		//Lancio query
		$this->sql = new query ( $conn );
		$this->sql->set_sql ( $query );
		//print_r ($query);
		$this->sql->exec ();
		
		//Conteggio righe
		$sql_count="select count(*) as conto from ($query)";
		$sql = new query ( $conn );
		$sql->get_row($sql_count);
		$nrows=$sql->row['CONTO']-0;

		$hidefields = array();
		
		switch ($type){
			case SDV_LTYPE_VIOLATION:
				$nrows = 0;
				$repkeys = array();
				$repkeys[]="SITEID";
				$repkeys[]="SUBJID";
				$repkeys[]="VISIT";
				$repkeys[]="ESAM";
				$repkeys[]="FIELD";
				$oby = $pk_service;
				if ($_GET['ORD']){
					$oby = $_GET['ORD'];
				}
				$orows = array();
				while ( $this->sql->get_row () ) {
					//print_r($this->sql->row);
					$data = $this->visite_violation(); //Codpat corrente implicito ($this->sql->row)
					foreach ($data as $visit){
						foreach ($visit as $esam){
							if (is_array($esam)){
								foreach ($esam as $fname => $field){
									if (is_array($field)){
										foreach ($field as $f){
											$r = array();
											$r['CENTER'] = $this->sql->row['SITEID'];
											$r[$pk_service] = $this->sql->row[$pk_service];
											$r['SUBJID'] = $this->sql->row['SUBJID'];
											$r['SITEID'] = $this->sql->row['SITEID'];
											$r['VISIT'] = $visit['name'];
											$r['ESAM'] = $esam['name'];
											$r['FIELD'] = $f;
											$orows[$r[$oby]][] = $r;
											$nrows++;
										}
									}
								}
							}
						}
					}			
				}
				break;
			case SDV_LTYPE_SIGNATURE:
				$nrows = 0;
				$repkeys = array();
				$repkeys[]="SITEID";
				$repkeys[]="SUBJID";
				$repkeys[]="USERNAME";
				$repkeys[]="DATA";
				$repkeys[]="VISIT";
				$repkeys[]="VISIT_PERC";
				$repkeys[]="ESAM";
				$repkeys[]="ESAM_PERC";
				$repkeys[]="NOTES";
				$oby = "SIGNDATE";
				if (isset($_GET['ORD']) && $_GET['ORD']){
				//	if ($_GET['ORD'] != "SIGNDATE"){
				//		//SIGNDATE è DATA --> Rimappato in fallback
						$oby = $_GET['ORD'];
				//	}
				}
				$orows = array();
				while ( $this->sql->get_row () ) {
					//print_r($this->sql->row);
					$data = $this->visite_signature(); //Codpat corrente implicito ($this->sql->row)
					//echo "<pre>";
					//print_r($data);
					//echo "</pre>";
					foreach ($data as $username => $datearray){
						foreach ($datearray as $kdate=>$date){
							//echo "<hr/>".$kdate."<hr/>";
							if (substr($kdate, 0, 1) != "_"){
								foreach ($date as $vkey => $visit){
									if (is_numeric($vkey)){
										foreach ($visit as $ekey => $esam){
											if (is_numeric($ekey)){
												//echo "<pre>";
												//print_r($ekey);
												//print_r($esam);
												//echo "</pre>";
												//Nome => Versione
												if ($esam['_signed']>0 && $esam['_sign_date']){
													$r = array();
													$r['CENTER'] = $this->sql->row['SITEID'];
													$r[$pk_service] = $this->sql->row[$pk_service];
													$r['SUBJID'] = $this->sql->row['SUBJID'];
													$r['SITEID'] = $this->sql->row['SITEID'];
													$r['USERNAME'] = $username;
													$r['SIGNDATE'] = $kdate;
													$r['DATA'] = $esam['_sign_date'];
													$r['VISIT'] = $visit['_name'];
													$r['VISIT_PERC'] = $visit['_perc_signed'];
													$r['ESAM'] = $esam['_name'];
													$r['ESAM_PERC'] = $esam['_perc_signed'];
													$r['NOTES'] = $date['_notes']; //Diff esami su precedente firma //"Note".$ekey;
													$orows[$r[$oby]][] = $r;
													$nrows++;
												}
											}
										}
									}
								}
							}
						}
					}
				}			
				break;
			default:
				$hidefields[] = "CENTER";
				//Non faccio nulla, ho già il conteggio standard e uso la query in modo normale
				break;
		}
		
		
		
		if ($_GET['ORD'] && $_GET['ORD_TYPE']){
			switch($_GET['ORD_TYPE']){
				case "ASC":
					ksort($orows);
					//echo "ASCORD";
					break;
				case "DESC":
					krsort($orows);
					//echo "DESCORD";
					break;
			}
		}
		
		//echo "NUMROWS->".$nrows."<br/>";
		
		//if (!$this->page){
		//	$this->page = 1;
		//}
		
		if ($this->page!=''){
			$conto = $nrows;
			//echo "CONTO->".$conto;
			$npages=ceil($conto/$this->rpp);
			$first=(($this->page-1)*$this->rpp)+1;
			if ($conto > $this->rpp) $last=$this->page*$this->rpp;
			if ($conto <= $this->rpp) $last=$conto;
			$pages=21;
			$first_page_bar=$this->page-(($pages-1)/2);
			if ($first_page_bar<=0) $first_page_bar=1;
			$last_page_bar=$first_page_bar+($pages-1);
			if ($last_page_bar>$npages){
				$last_page_bar=$npages;
				$first_page_bar=$last_page_bar-($pages-1);
				if ($first_page_bar<=0) $first_page_bar=1;
			}
			$url_base="index.php?";
			$prev_page=$this->page-1;
			$next_page=$this->page+1;
			$navigation_bar = "";
			foreach ($_GET as $key => $val){
				if ($key!='PAGE') $url_base.="$key=".urlencode($val)."&";
			}
			foreach ($_POST as $key => $val){
				if ($key!='PAGE' && $key!='form' && $key!='ESAM') $url_base.="$key=".urlencode($val)."&";
			}
			if ($this->page!=1){
				$navigation_bar.="<a href=\"{$url_base}PAGE=1\">|&lt;</a>&nbsp;<a href=\"{$url_base}PAGE=$prev_page\">&lt;</a>";
			}
			if ($first_page_bar!=1){
				$navigation_bar.="...";
			}
			for ($i=$first_page_bar;$i<=$last_page_bar;$i++){
				if ($i==$this->page) $navigation_bar.=" <b>$i</b>";
				else $navigation_bar.=" <a href=\"{$url_base}PAGE=$i\">$i</a>";
			}

			if ($last_page_bar!=$npages){
				$navigation_bar.="...";
			}
			if ($this->page!=$npages){
				$navigation_bar.=" <a href=\"{$url_base}PAGE=$next_page\">&gt;</a>&nbsp;<a href=\"{$url_base}PAGE=$npages\">&gt;|</a>";
			}
			
			/* Se siamo nell'ultima pagina il "to"($last) corrisponde al numero di risultati */
			if($_GET['PAGE'] == $last_page_bar){
				$last=$conto;
			}else{
				$last=$this->page*$this->rpp;
			}
			
			if($this->config_service ['lang'] == "en"){
				$specchietto_riassuntivo="
				Total Number of Records: <b>$conto</b><br>
				Records displayed on this page from <b>$first</b> to <b>$last</b><br>
				Go to page (1-$npages): <input type='text' id='to_page' value=\"{$_GET['PAGE']}\"><input type='button' value='Go' onclick=\"
					page=document.getElementById('to_page').value-0;
					if (page>$npages || page<=0) {
						alert('Warning! Please, select page in the range 1-$npages!');
						return false;
					}
					window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
				\">
				";
			}else{
				$specchietto_riassuntivo="
				Numero totale records: <b>$conto</b><br>
				Record mostrati in questa pagina dal <b>$first</b> al <b>$last</b><br>
				Salta a pagina (1-$npages): <input type='text' id='to_page' value=\"{$_GET['PAGE']}\"><input type='button' value='Vai' onclick=\"
					page=document.getElementById('to_page').value-0;
					if (page>$npages || page<=0) {
						alert('Attenzione! Selezionare una pagina nel range 1-$npages!');
						return false;
					}
					window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
				\">
				";	
			}
			
			//TODO: Paginazione query (da rifare)
			//$query="select * from (select t.*, rownum as n_r from ($query) t) where n_r between $first and $last";
			$html="$specchietto_riassuntivo<p align=center>$navigation_bar</p>$html";
		}
		//Conteggio
		if ($this->count_items) {
			$this->n_item_returned = $this->sql->numrows;
			$html .= "<p align=center style='font-size:14px'>$this->presenti_string <b>{$this->n_item_returned}</b> {$this->items_name}</p>" . $html;
		}

		//HEADER TABELLA!
		$html .= "<table border=\"0\" id=\"table1\" width=\"95%\" align=\"center\" class=\"table table-striped table-bordered table-hover\">
		            <thead id='lista_table_header' class='lista_table_header'><tr>";
		for($i=0;$i<count($this->sql->keys); $i++){
			$nome = $this->sql->keys [$i] ;
			if ($nome != $pk_service && !in_array($nome, $hidefields)){
				$html .= $this->col_th_testo( $i );
			}
			/*
			if (var_glob ( $nome,$session_vars ) != '' && var_glob ( $nome,$session_vars ) != 'next') {
				if ($where != '')
				$where .= " and ";
				$where .=  $this->cols [$i] ['VAR'] . "='" . var_glob ( $nome, $session_vars ) . "' ";
			}
			*/
		}
		if ($type == SDV_LTYPE_STATUS){
			$html .= $this->col_th_visite();
		}
		if ($type == SDV_LTYPE_VIOLATION){
			$html .= $this->col_th_vef();
		}
		if ($type == SDV_LTYPE_SIGNATURE){
			$html .= $this->col_th_vesig();
		}
		
		$html .= "</tr></thead>";
		
		switch ($type){
			case SDV_LTYPE_VIOLATION:
			case SDV_LTYPE_SIGNATURE:
				//TODO: Sorting
				//Visualizzazione				
				foreach ($orows as $rsorted){
					foreach ($rsorted as $r){
						$this->empty = false;
						$html .= "\n<tr>";
						for($i = 0; $i < count ( $repkeys ); $i ++) {
							$txt = "";
							$nome = $repkeys[$i] ;
							if ($nome != $pk_service && !in_array($nome, $hidefields)){
								if ($nome=="USERNAME" && $type==SDV_LTYPE_SIGNATURE){
									$realname = $this->names[$r[$nome]];
									$txt .= ($realname?$realname:$r[$nome]).' ';
								}else{
									$txt .= "\n" . $this->col_tdrow_testo($repkeys, $r, $i);
									if ($repkeys[$i] == $pk_service || $repkeys[$i] == "SUBJID") {
										$txt = "<a href=\"index.php?&exams=visite_exam.xml&{$pk_service}={$r[$pk_service]}&CENTER={$this->patients[$r[$pk_service]]['CENTER']}\">".$txt."</a>";
									}
								}
								if ($txt != '')
								$html .= "<td class=\"sc4bis\" {$this->cols [$i] ['ALIGN']}>$txt</td>";
							}
						}
						$html .= "</tr>";
					}
					
				}
				$html .= "</table>";
				break;
			default:
				$tot = 0;
				$param = "";
				while ( $this->sql->get_row () ) {
					if ($this->list ['TOTALE'] != '')
					$tot += $this->sql->row [strtoupper ( $this->list ['TOTALE'] )];
					$this->empty = false;
					$html .= "\n<tr>";
					for($i = 0; $i < count ( $this->sql->keys ); $i ++) {
						$txt = "";
						$nome = $this->sql->keys [$i] ;
						if ($nome != $pk_service && !in_array($nome, $hidefields)){
							if ($nome=="USERNAME" && $type==SDV_LTYPE_SIGNATURE){
								$realname = $this->names[$this->sql->row[$nome]];
								$txt .= ($realname?$realname:$this->sql->row[$nome]).' ';
							}else{
								$txt .= "\n" . $this->col_td_testo( $i );
								if ($this->sql->keys [$i] == $pk_service || $this->sql->keys [$i] == "SUBJID") {
									$txt = "<a href=\"index.php?&exams=visite_exam.xml&{$pk_service}={$this->sql->row[$pk_service]}&CENTER={$this->patients[$this->sql->row[$pk_service]]['CENTER']}\">".$txt."</a>";
								}
							}
							if ($txt != '')
							$html .= "<td class=\"sc4bis\" {$this->cols [$i] ['ALIGN']}>$txt</td>";
						}
					}
					if ($type == SDV_LTYPE_STATUS || $type == SDV_LTYPE_VIOLATION){
						$html .= $this->col_td_visite($type);
					}
					$html .= "</tr>";
				}
				$param .= "&amp;CENTER=" . $in ['CENTER'];
				//echo "<hr/>$param<hr/>";
				if ($in ['v_list'] == '') {
					//if ($in['list']=="patients_group_list.xml") $html.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;$param\">Lista Pazienti</a></p>";
					//else  $html.="<p align=right><a href=\"index.php?list=patients_group_list.xml&amp;$param\">Lista Pazienti</a></p>";
				}
				if ($this->list ['TOTALE'] != '') {
					$colsp = count ( $this->sql->keys ) - 3;
					if($this->config_service ['lang'] != "en"){
						$html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Totale</b></td>";
					}else{
						$html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Total</b></td>";
					}
		
					$html .= "<td class=\"sc4bis\"><b>$tot</b></td>
						 <td class=\"sc4bis\"></td>
						 </tr>
						";
				}
				$html .= "</table>";
				//echo $html."<hr>";
				//echo "<!--$query-->";
				//die("AAA");
				break;	
		}
		
		//die("ARRIVO??");
		//$html.= $navigation_bar;
		return $html; //."<hr/>PROVAQUA?!<hr/>";
		//return $list;
 	}
 	
 	function ListHtmlQuery($session_vars=null){ //Dammi una query, ti faccio la tabella
 		$navigation_bar=null;
        $where=null;
		global $remote_userid;
		global $in;
		global $conn;
		global $xml_dir;
		if($in['PAGE']>0)$this->page=$in['PAGE'];
		if ($this->config_service ['PK_SERVICE'] == '')
		$pk_service = "CODPAT";
		else
		$pk_service = $this->config_service ['PK_SERVICE'];

		$html = "<table border=\"0\" id=\"table1\" width=\"95%\" align=center><tr>";
		$sql = new query ( $conn );
		$sql->set_sql ( "ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'" );
		$sql->ins_upd ();

		$html .= "</tr>";
		error_reporting(E_ALL^ E_WARNING);
		ini_set("display_errors",1);
		global $service;
		$query = "select * from {$service}_SDV_STRATEGY_STATUS";
		echo "<!-- ".$query."<hr> -->";
        $query = preg_replace_callback( "/\[(.*?)\]/", "_sdv_replace_globals", $query );
		echo "
		<!--$query-->
		";
		$this->rpp = 25;

		if ($this->page!=''){
			$sql_count="select count(*) as conto from ($query)";
			$sql = new query ( $conn );
			$sql->get_row($sql_count);
			$conto=$sql->row['CONTO']-0;
			echo $sql_count."->".$conto;
			$npages=ceil($conto/$this->rpp);
			$first=(($this->page-1)*$this->rpp)+1;
			if ($conto > $this->rpp) $last=$this->page*$this->rpp;
			if ($conto <= $this->rpp) $last=$conto;
			$pages=21;
			$first_page_bar=$this->page-(($pages-1)/2);
			if ($first_page_bar<=0) $first_page_bar=1;
			$last_page_bar=$first_page_bar+($pages-1);
			if ($last_page_bar>$npages){
				$last_page_bar=$npages;
				$first_page_bar=$last_page_bar-($pages-1);
				if ($first_page_bar<=0) $first_page_bar=1;
			}
			$url_base="index.php?";
			$prev_page=$this->page-1;
			$next_page=$this->page+1;
			foreach ($_GET as $key => $val){
				if ($key!='PAGE') $url_base.="$key=".urlencode($val)."&";
			}
			foreach ($_POST as $key => $val){
				if ($key!='PAGE' && $key!='form' && $key!='ESAM') $url_base.="$key=".urlencode($val)."&";
			}
			if ($this->page!=1){
				$navigation_bar.="<a href=\"{$url_base}PAGE=1\">|&lt;</a>&nbsp;<a href=\"{$url_base}PAGE=$prev_page\">&lt;</a>";
			}
			if ($first_page_bar!=1){
				$navigation_bar.="...";
			}
			for ($i=$first_page_bar;$i<=$last_page_bar;$i++){
				if ($i==$this->page) $navigation_bar.=" <b>$i</b>";
				else $navigation_bar.=" <a href=\"{$url_base}PAGE=$i\">$i</a>";
			}

			if ($last_page_bar!=$npages){
				$navigation_bar.="...";
			}
			if ($this->page!=$npages){
				$navigation_bar.=" <a href=\"{$url_base}PAGE=$next_page\">&gt;</a>&nbsp;<a href=\"{$url_base}PAGE=$npages\">&gt;|</a>";
			}
			
			/* Se siamo nell'ultima pagina il "to"($last) corrisponde al numero di risultati */
			if($_GET['PAGE'] == $last_page_bar){
				$last=$conto;
			}else{
				$last=$this->page*$this->rpp;
			}
			
			if($this->config_service ['lang'] == "en"){
				$specchietto_riassuntivo="
				Total Number of Records: <b>$conto</b><br>
				Records displayed on this page from <b>$first</b> to <b>$last</b><br>
				Go to page (1-$npages): <input type='text' id='to_page' value=\"{$_GET['PAGE']}\"><input type='button' value='Go' onclick=\"
					page=document.getElementById('to_page').value-0;
					if (page>$npages || page<=0) {
						alert('Warning! Please, select page in the range 1-$npages!');
						return false;
					}
					window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
				\">
				";
			}else{
				$specchietto_riassuntivo="
				Numero totale records: <b>$conto</b><br>
				Record mostrati in questa pagina dal <b>$first</b> al <b>$last</b><br>
				Salta a pagina (1-$npages): <input type='text' id='to_page' value=\"{$_GET['PAGE']}\"><input type='button' value='Vai' onclick=\"
					page=document.getElementById('to_page').value-0;
					if (page>$npages || page<=0) {
						alert('Attenzione! Selezionare una pagina nel range 1-$npages!');
						return false;
					}
					window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
				\">
				";	
			}
			
			$query="select * from (select t.*, rownum as n_r from ($query) t) where n_r between $first and $last";
			$html="$specchietto_riassuntivo<p align=center>$navigation_bar</p>$html";
		}
		$this->sql = new query ( $conn );
		$this->sql->set_sql ( $query );
		//print_r ($query);
		$this->sql->exec ();
		if ($this->count_items) {
			$this->n_item_returned = $this->sql->numrows;
			$html = "<p align=center style='font-size:14px'>$this->presenti_string <b>{$this->n_item_returned}</b> {$this->items_name}</p>" . $html;
		}

		//print_r($this->sql->numrows);
		//die("ASD");
		//HEADER TABELLA!
		for($i=0;$i<count($this->sql->keys); $i++){
			$html .= $this->col_th_testo( $i );
			$nome = $this->sql->keys [$i] ;
			if (var_glob ( $nome,$session_vars ) != '' && var_glob ( $nome,$session_vars ) != 'next') {
				if ($where != '')
				$where .= " and ";
				$where .=  $this->cols [$i] ['VAR'] . "='" . var_glob ( $nome, $session_vars ) . "' ";
			}
		}
		
		$tot = 0;
		while ( $this->sql->get_row () ) {
			if ($this->list ['TOTALE'] != '')
			$tot += $this->sql->row [strtoupper ( $this->list ['TOTALE'] )];
			$this->empty = false;
			$html .= "\n<tr>";
			for($i = 0; $i < count ( $this->sql->keys ); $i ++) {
				$txt = "";
				//$function_to_call = "col_td_" . $this->cols [$i] ['TIPO'];
				//if (method_exists ( $this, $function_to_call ))
				$txt .= "\n" . $this->col_td_testo( $i );
				
				//if ($this->cols [$i] ['SCRIPT'] != '') {
				//	$link = $this->col_script ( $i );
				//	$txt = $link . $txt . "</a>";
				//}
				
				if ($txt != '')
				$html .= "<td class=\"sc4bis\" {$this->cols [$i] ['ALIGN']}>$txt</td>";
			}
			$html .= "</tr>";
		}
		if (isset ( $in ['CODPAT'] )) {
			$param = "CODPAT=" . $in ['CODPAT'];
			$txt;
		}
		$param .= "&amp;CENTER=" . $in ['CENTER'];
		if ($in ['v_list'] == '') {
			//if ($in['list']=="patients_group_list.xml") $html.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;$param\">Lista Pazienti</a></p>";
			//else  $html.="<p align=right><a href=\"index.php?list=patients_group_list.xml&amp;$param\">Lista Pazienti</a></p>";
		}
		if ($this->list ['TOTALE'] != '') {
			$colsp = count ( $this->sql->keys ) - 3;
			if($this->config_service ['lang'] != "en"){
				$html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Totale</b></td>";
			}else{
				$html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Total</b></td>";
			}

			$html .= "<td class=\"sc4bis\"><b>$tot</b></td>
				 <td class=\"sc4bis\"></td>
				 </tr>
				";
		}
		$html .= "</table>";
//echo $html."<hr>";
//echo "<!--$query-->";
		//die("AAA");
		return $html;
		//return $list;
 	}
 	
 	function col_td_testo($i) {
//		global $in;
		if($this->session_vars) $in=$this->session_vars;
		else{
			global $in;
		}
		//		print($in ['USER_TIP']);
		$value = $this->sql->row [strtoupper ( $this->sql->keys[$i] )];
		$value = preg_replace ( "/#(.*?)#/", "<\\1>", $value );
  		//if ($this->cols [$i] ['CRYPTO'] == 'yes' && ($in ['USER_TIP'] == 'DM' || $in ['USER_TIP'] == 'RO'))
		//$value = '****';
		return $value . "&nbsp;";
	}
 	
	function col_tdrow_testo($keys, $row, $i) {
//		global $in;
		if($this->session_vars) $in=$this->session_vars;
		else{
			global $in;
		}
		//		print($in ['USER_TIP']);
		$value = $row [strtoupper ( $keys[$i] )];
		$value = preg_replace ( "/#(.*?)#/", "<\\1>", $value );
  		//if ($this->cols [$i] ['CRYPTO'] == 'yes' && ($in ['USER_TIP'] == 'DM' || $in ['USER_TIP'] == 'RO'))
		//$value = '****';
		return $value . "&nbsp;";
	}
	
	function col_th_testo($i) {
        $param=null;
		//	  	print "<hr>col_th_testo: i=$i<hr>";
		global $in;
		if($in['SEARCH']){
			foreach ($in as $par => $valore){
				if($valore!='' && $par!='remote_userid')$param.="&$par=$valore";
			}
		}
		
		$colName = strtoupper ( $this->sql->keys[$i] ); //$this->cols [$i] ['TESTO'];
		$txt = $colName;
		$label = $this->labels[$txt];
		if ($label){
			$txt = $label;
		}
		$txt .= $this->AppendColOrd($colName);
		//$txt .= 'AA';
		/*
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
			foreach($_GET as $key=>$val){
				if ($key!='ORD' && $key!='ORD_TYPE' && $key!='page') $param.="&$key=$val";
			}
			if (isset ( $in ['page'] ))
			$param .= "page=1&";
			if (isset ( $in ['ESAM'] ) && isset ( $in ['VISITNUM'] ) && ($in ['VISITNUM'] == 0) && ($in ['ESAM'] == 0)) {
				$txt .= "
	  			<br><a href=\"index.php?&{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?&{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";

			} else { //solo le PROSSIME 4 righe erano presenti prima della modifica!!!
				if ($in ['CENTER'] != '')
				$center = "CENTER={$in['CENTER']}";
				$txt .= "
	  			<br><a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=DESC\"><img src=\"$img_up\" width=15></a>
	  			<a href=\"index.php?{$param}&ORD={$this->cols[$i]['ORD_ARROW']}&ORD_TYPE=ASC\"><img src=\"$img_down\" width=15></a>";
			}
		}
		*/
		return "<th class=\"int\">" . $txt . "</th>";
	}

	function AppendColOrd($colName){
        $param=null;
		global $in;
		//modifica di cristiano campeggiani agosto 2006
		foreach($_GET as $key=>$val){
			if ($key!='ORD' && $key!='ORD_TYPE' && $key!='page') $param.="&$key=$val";
		}
		if (isset ( $in ['page'] )){
			$param .= "page=1&";
		}
	
		$img_down = "<i class=\"fa fa-chevron-down\"></i>";
		if ($in ['ORD_TYPE'] == 'ASC' && $in ['ORD'] == $colName){
			$img_down = "<i class=\"fa fa-chevron-circle-down\"></i>";
		}
		$img_up = "<i class=\"fa fa-chevron-up\"></i>";
		if ($in ['ORD_TYPE'] == 'DESC' && $in ['ORD'] == $colName){
			$img_up = "<i class=\"fa fa-chevron-circle-up\"></i>";
		}
		$txt = "
  			<br><a href=\"index.php?{$param}&ORD={$colName}&ORD_TYPE=DESC\">$img_up</a>
  			<a href=\"index.php?{$param}&ORD={$colName}&ORD_TYPE=ASC\">$img_down</a>
  			";
		return $txt;
	}
	
	function col_td_visite($type = SDV_LTYPE_STATUS) {
        $string=null;
		global $xml_dir;
		//global $config_service;
		global $conn;
		global $in;
		$pk_service = $this->sql->row [$this->config_service ['PK_SERVICE']];
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		//echo "<pre>";
		//print_r($visit);
		//echo "</pre>";
		$sql_visite = "
			select
				fine,
				inizio,
				userid,
				visitnum,
				visitnum_progr,
				esam,
				progr,
				visitclose,
				abilitato
			from {$this->config_service['service']}_coordinate
			where {$this->config_service['PK_SERVICE']}='$pk_service'
			and abilitato=1
			order by visitnum, visitnum_progr, esam, progr";
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite );
		while ( $sql2->get_row () ) {
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['INIZIO'] = $sql2->row ['INIZIO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['FINE'] = $sql2->row ['FINE'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['USERID'] = $sql2->row ['USERID'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['ABILITATO'] = $sql2->row ['ABILITATO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['VISITCLOSE'] = $sql2->row ['VISITCLOSE'];
		}
		$sql_visite = "
			select
				s.visitnum,
				s.visitnum_progr,
				s.esam,
				s.progr,
				s.field,
				s.version,
				s.valid,
				s.date_validation,
				s.protocol_violation,
				s.signed,
				s.last_sign_date
			from {$this->config_service['service']}_sdv_strategy_status s 
			where s.{$this->config_service['PK_SERVICE']}='$pk_service'
			order by s.visitnum, s.visitnum_progr, s.esam, s.progr";
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite );
		while ( $sql2->get_row () ) {
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VERSION']= $sql2->row ['VERSION'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VALID'] = $sql2->row ['VALID'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['DATE_VALIDATION'] = $sql2->row ['DATE_VALIDATION'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['SIGNED'] = $sql2->row ['SIGNED'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['LAST_SIGN_DATE'] = $sql2->row ['LAST_SIGN_DATE'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['PROTOCOL_VIOLATION'] = $sql2->row ['PROTOCOL_VIOLATION'];			
		}
		//echo "<pre>";
		//print_r($sdv_query);
		//echo "</pre>";
		$remote_userid = $in ['remote_userid'];
		//$f_bianca = "f_bianca.gif";
		//$f_gialla = "f_gialla.gif";
		//$f_verde = "f_verde.gif";
		//$f_grigia = "f_grigia.gif";
		//$f_blue = "f_blu.gif";
        $f_bianca="<i class=\"el-icon-file-new blue\"></i>";
        $f_gialla="<i class=\"fa fa-check orange\"></i>";
        $f_verde="<i class=\"fa fa-check-circle green\"></i>";
        $f_grigia="<i class=\"fa fa-check-square gray\"></i>";
        $f_blue="<i class=\"fa fa-check-circle-o blue\"></i>";
        $f_red="<i class=\"el-icon-remove-circle red\"></i>";

		foreach ( $visit->visitnums as $visitnum => $val ) {
//			print_r($val);
//			if ($string != '')
			switch ($type){
				case SDV_LTYPE_VIOLATION:
					$string .= "\n<td class=sc4bis align=left>";
					break;
				default:
					$string .= "\n<td class=sc4bis align=center>";
					break;
			}
			$is_data_entry = false;
			$img="";
			$visita[$visitnum]['exist']=false; //Esiste la visita
			$visita[$visitnum]['enabled']=false; //Visita abilitata
			$visita[$visitnum]['skipped']=false; //Visita skippata
			$visita[$visitnum]['saved']=false; //Almeno 1 scheda salvata
			$visita[$visitnum]['sdv'] = false; //Almeno 1 campo in strategia //Almeno 1 campo SDV in visita
			$visita[$visitnum]['sdv_tobestarted'] = false; //Almeno 1 scheda freezata facente parte dell'SDV
			$visita[$visitnum]['started']=false; //Almeno 1 campo compilato (o firmato?) //Almeno 1 campo SDV con firma
			$visita[$visitnum]['finished']=true; //Tutto firmato
			$visita[$visitnum]['violation']=false; //Ho almeno 1 protocol violation (E appendo il testo...)
			
			$n_v_progr = count ( $res_query [$pk_service] [$visitnum] );
			foreach ( $res_query [$pk_service] [$visitnum] as $v_progr => $val_vprogr ) {
				foreach ( $visit->esams [$visitnum] as $esam => $val_esam ) {
					foreach ( $res_query [$pk_service] [$visitnum] [$v_progr] [$esam] as $progr => $val_progr ) {
						$visita[$visitnum]['exist']=true;
						if ($remote_userid == $val_progr ['USERID'] || $val_progr ['USERID']=='') {
							$is_data_entry = true;
							$is_data_entry [$progr] = true;
							//$visita[$visitnum]['active']=true;
						} else {
							$is_data_entry [$progr] = false;
						}

						//if ($val_progr['FINE']!=1 || $val_esam['ADD_PROGR']==''){
						//	$visita[$visitnum]['all_my_closed']=false;
						//}
						//esame visibile dall'utente in questione in ogni caso
						$visita[$visitnum]['enabled']=true;
						if ($val_progr['INIZIO']==1){
							$visita[$visitnum]['saved']=true;
						}

						if (isset($this->strategy[$visitnum][$esam])){
							$visita[$visitnum]['sdv']=true;
							if ($val_progr['FINE']==1){
								$visita[$visitnum]['sdv_tobestarted']=true;
							}
						}
						
						/*Gestione visite skippate , se il visitclose è 1 e c'è un esame skip_visit.xml*/
						if($val_esam['XML']=='skip_visit.xml' && $val_progr ['VISITCLOSE'] == 1 && $val_progr ['INIZIO']==1 && $val_progr['FINE']==1){
								$visita[$visitnum]['skipped']=true;
						}
						
						//echo "<pre>";
						//print_r($val_esam);
						//echo "</pre>";
						foreach ($sdv_query[$pk_service] [$visitnum] [$v_progr] [$esam][$progr] as $field => $val_field){
							if ($val_field['DATE_VALIDATION']){
								$visita[$visitnum]['started']=true;
							}
							if (!$val_field['SIGNED']){
								$visita[$visitnum]['finished']=false;
							}
							if ($val_field['PROTOCOL_VIOLATION']){
								if (!$visita[$visitnum]['violation']){
									$visita[$visitnum]['violation']="<ul>";
								}
								//$visita[$visitnum]['violation'].= "<li>{$esam}-{$val_esam['TESTO']} ({$v_progr}:{$progr}) {$field}: {$val_field['PROTOCOL_VIOLATION']}";
								$tprogr = "";
								if ($val_esam['PROGR'] == "yes"){
									//Se progressivo (sub)
									$tprogr = " ({$progr})";
								}
								$form= new xml_form();
								$form->xml_form_by_file($xml_dir."/".$val_esam[XML]);
								//echo "<pre>";
								//print_r($form);
								//echo "</pre>";
								$idx = $form->vars[$field];
								if ($form->fields[$idx]['TESTO']){
									$tfield = trim($form->fields[$idx]['TESTO']);
								}else{
									$tfield = $field;
								}
								$visita[$visitnum]['violation'].= "<li>{$val_esam['TESTO']}{$tprogr} - {$tfield}: {$val_field['PROTOCOL_VIOLATION']}</li>";
								//print_r($val_vprogr);
								//print_r($val_esam);
								//print_r($val_progr);
								//die("ASD");
							}
						}
					}
				}
				if ($visita[$visitnum]['violation']){
					$visita[$visitnum]['violation'].="</ul>";
				}
			}
			//Visualizzazione
			switch ($type){
				case SDV_LTYPE_STATUS:
					//if ($visita[$visitnum]['exist']) $img = $f_grigia;
					/*
					if ($visita[$visitnum]['enabled']) {
						$img = $f_bianca;
						if (!$visita[$visitnum]['active']) $img=$f_grigia;
					}
					*/
					//print_r($visita);
					if ($visita[$visitnum]['exist']){
						$img = ""; //$f_blue;
						if ($visita[$visitnum]['skipped']){
							$img = $f_blue;
						}else{
							if ($visita [$visitnum] ['sdv']) {
								$img = $f_grigia;
								if ($visita [$visitnum] ['sdv_tobestarted']){
									$img = $f_bianca;
								}
								if ($visita [$visitnum] ['started']) {
									$img = $f_gialla;
									if ($visita [$visitnum] ['finished']) {
										$img = $f_verde;
									}
								}
							}
						}
					}
					break;
				case SDV_LTYPE_VIOLATION:
					break;
			}
			//if ($visita[$visitnum]['init']==1 && $visita[$visitnum]['enabled']==1 && $visita[$visitnum]['all_my_closed']==1) $img=$f_verde;
			
			$param = "?exams=visite_exams.xml"; // . $this->cols [$i] ['EXAMS'];
			//$params = "";
			$params = "{$this->config_service ['PK_SERVICE']},CENTER"; //$this->cols [$i] ['PARAM'];
			$params = explode ( ",", $params );
			for($p = 0; $p < count ( $params ); $p ++) {
				if ($this->sql->row [strtoupper ( $params [$p] )] != '') {
					$param .= "&amp;" . strtoupper ( $params [$p] ) . "=" . $this->sql->row [strtoupper ( $params [$p] )];
				} else {
					
					$param .= "&amp;" . $params [$p];
				}
			}
			$param .= "&amp;VISITNUM=$visitnum";
			switch ($type){
				case SDV_LTYPE_STATUS:
					if ($img != '') {
						$img_tag = $img;
						//if ($img!=$f_grigia)
						$href = "
						<a href=\"index.php$param\">$img_tag</a>
						";
						//else $href=$img_tag;
					} else {
						$img_tag = '&nbsp;';
						$href = "
						$img_tag
						";
					}
					break;
				case SDV_LTYPE_VIOLATION:
					$href = $visita[$visitnum]['violation'];
					break;
			}
			$string .= "$href &nbsp;</td>";
		}
		//print_r($visita);
		return $string;
	}
	
	function col_th_visite() {
        $th=null;
		global $xml_dir;
		#$th="<th class=\"int\">";
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		foreach ( $visit->visitnums as $key => $val ) {
			if ($th != '')
			$th .= "</th><th class=\"int\">";
			else
			$th = "<th class=\"int\">";
			$th .= $val ['SHORT_TXT'];
		}
		$th .= "</th>";
		return $th;
	}
	
	function col_th_vef() {
		global $xml_dir;
		#$th="<th class=\"int\">";
		$th = "";
		$th .= "<th class=\"int\">";
		$th .= "Visit";
		$th .= $this->AppendColOrd("VISIT");
		$th .= "</th>";
		$th .= "<th class=\"int\">";
		$th .= "Form";
		$th .= $this->AppendColOrd("ESAM");
		$th .= "</th>";
		$th .= "<th class=\"int\">";
		$th .= "Field";
		$th .= $this->AppendColOrd("FIELD");
		$th .= "</th>";
		return $th;
	}
	
	function col_th_vesig() {
		global $xml_dir;
		#$th="<th class=\"int\">";
		$th = "";
		$th .= "<th class=\"int\">";
		$th .= "Visit";
		$th .= $this->AppendColOrd("VISIT");
		$th .= "</th>";
		$th .= "<th class=\"int\">";
		$th .= "% Fields for visit";
		$th .= $this->AppendColOrd("VISIT_PERC");
		$th .= "</th>";
		$th .= "<th class=\"int\">";
		$th .= "Form";
		$th .= $this->AppendColOrd("ESAM");
		$th .= "</th>";
		$th .= "<th class=\"int\">";
		$th .= "% Fields for form";
		$th .= $this->AppendColOrd("ESAM_PERC");
		$th .= "</th>";
		$th .= "<th class=\"int\">";
		$th .= "Notes";
		$th .= "</th>";
		return $th;
	}
	
	function visite_violation() {
		global $xml_dir;
		//global $config_service;
		global $conn;
		global $in;
		$pk_service = $this->sql->row [$this->config_service ['PK_SERVICE']];
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		//echo "<pre>";
		//print_r($visit);
		//echo "</pre>";
		$sql_visite = "
			select
				fine,
				inizio,
				userid,
				visitnum,
				visitnum_progr,
				esam,
				progr,
				visitclose,
				abilitato
			from {$this->config_service['service']}_coordinate
			where {$this->config_service['PK_SERVICE']}='$pk_service'
			and abilitato=1
			order by visitnum, visitnum_progr, esam, progr";
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite );
		while ( $sql2->get_row () ) {
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['INIZIO'] = $sql2->row ['INIZIO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['FINE'] = $sql2->row ['FINE'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['USERID'] = $sql2->row ['USERID'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['ABILITATO'] = $sql2->row ['ABILITATO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['VISITCLOSE'] = $sql2->row ['VISITCLOSE'];
		}
		$sql_visite = "
			select
				s.visitnum,
				s.visitnum_progr,
				s.esam,
				s.progr,
				s.field,
				s.version,
				s.valid,
				s.date_validation,
				s.protocol_violation,
				s.signed,
				s.last_sign_date
			from {$this->config_service['service']}_sdv_strategy_status s 
			where s.{$this->config_service['PK_SERVICE']}='$pk_service'
			order by s.visitnum, s.visitnum_progr, s.esam, s.progr";
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite );
		while ( $sql2->get_row () ) {
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VERSION']= $sql2->row ['VERSION'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VALID'] = $sql2->row ['VALID'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['DATE_VALIDATION'] = $sql2->row ['DATE_VALIDATION'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['SIGNED'] = $sql2->row ['SIGNED'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['LAST_SIGN_DATE'] = $sql2->row ['LAST_SIGN_DATE'];
			$sdv_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['PROTOCOL_VIOLATION'] = $sql2->row ['PROTOCOL_VIOLATION'];			
		}
		//echo "<pre>";
		//print_r($sdv_query);
		//echo "</pre>";
		foreach ( $visit->visitnums as $visitnum => $val ) {
			//echo "<pre>";
			//print_r($val);
			//echo "</pre>";
			$retval[$visitnum]=array(); 
			$retval[$visitnum]['name'] = trim($val['TEXT']);
			$n_v_progr = count ( $res_query [$pk_service] [$visitnum] );
			foreach ( $res_query [$pk_service] [$visitnum] as $v_progr => $val_vprogr ) {
				foreach ( $visit->esams [$visitnum] as $esam => $val_esam ) {
					//echo "<pre>";
					//print_r($val_esam);
					//echo "</pre>";
					$retval[$visitnum][$esam] = array();
					$retval[$visitnum][$esam]['name'] = trim($val_esam['TESTO']);;
					foreach ( $res_query [$pk_service] [$visitnum] [$v_progr] [$esam] as $progr => $val_progr ) {
						//$visita[$visitnum]['exist']=true;
						foreach ($sdv_query[$pk_service] [$visitnum] [$v_progr] [$esam][$progr] as $field => $val_field){
							if ($val_field['PROTOCOL_VIOLATION'] && $val_field['VALID']){
								$retval[$visitnum][$esam][$field] = array();
								$tprogr = "";
								if ($val_esam['PROGR'] == "yes"){
									//Se progressivo (sub)
									$tprogr = " ({$progr})";
								}
								$form= new xml_form();
								$form->xml_form_by_file($xml_dir."/".$val_esam[XML]);
								//echo "<pre>";
								//print_r($form);
								//echo "</pre>";
								$idx = $form->vars[$field];
								if ($form->fields[$idx]['TESTO']){
									$tfield = trim($form->fields[$idx]['TESTO']);
								}else{
									$tfield = $field;
								}
								//$retval[$visitnum][$esam][$field][] = "<li>{$val_esam['TESTO']}{$tprogr} - {$tfield}: {$val_field['PROTOCOL_VIOLATION']}</li>";
								$retval[$visitnum][$esam][$field][] = "{$tfield}: {$val_field['PROTOCOL_VIOLATION']}";
								//print_r($val_vprogr);
								//print_r($val_esam);
								//print_r($val_progr);
								//die("ASD");
							}
						}
					}
				}
			}
		}
		//echo "<pre>";
		//print_r($retval);
		//echo "</pre>";
		return $retval;
	}

	
	function visite_signature() {
		global $xml_dir;
		//global $config_service;
		global $conn;
		global $in;
		$pk_service = $this->sql->row [$this->config_service ['PK_SERVICE']];
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		//echo "<pre>";
		//print_r($visit);
		//echo "</pre>";
		$sql_visite = "
			select
				fine,
				inizio,
				fine,
				to_char(moddt, 'YYYY/MM/DD HH24:MI:SS') as tstamp,
				userid,
				visitnum,
				visitnum_progr,
				esam,
				progr,
				visitclose,
				abilitato
			from {$this->config_service['service']}_coordinate
			where {$this->config_service['PK_SERVICE']}='$pk_service'
			and abilitato=1
			order by visitnum, visitnum_progr, esam, progr";
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite );
		while ( $sql2->get_row () ) {
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['INIZIO'] = $sql2->row ['INIZIO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['FINE'] = $sql2->row ['FINE'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['USERID'] = $sql2->row ['USERID'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['ABILITATO'] = $sql2->row ['ABILITATO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['VISITCLOSE'] = $sql2->row ['VISITCLOSE'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['TSTAMP'] = $sql2->row ['TSTAMP'];
		}
		$sql_visite = "
			select
				to_char(s.tstamp, 'YYYY/MM/DD HH24:MI:SS') as tstamp,
				s.visitnum,
				s.visitnum_progr,
				s.esam,
				s.progr,
				s.field,
				s.version,
				s.valid,
				s.date_validation,
				s.protocol_violation,
				s.signed,
				to_char(s.last_sign_date, 'DD/MM/YYYY HH24:MI:SS') as text_sign_date,
				to_char(s.last_sign_date, 'YYYY/MM/DD HH24:MI:SS') as last_sign_date,
				s.userid
			from {$this->config_service['service']}_rpt_sdv_status s 
			where s.{$this->config_service['PK_SERVICE']}='$pk_service' 
			order by s.tstamp, s.last_sign_date NULLS FIRST , s.visitnum, s.visitnum_progr, s.esam, s.progr";
		$sql2 = new query ( $conn );
		//echo "$sql_visite<br/>";
		$sql2->exec ( $sql_visite );
		//Inserire la data tra pk_service e visitnum
		//$sdv_query [$pk_service] [$sql2->row ['LAST_SIGN_DATE']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VERSION'] = array();
		//$sdv_query [$pk_service] [$sql2->row ['LAST_SIGN_DATE']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['DATE_VALIDATION'] = array();
		while ( $sql2->get_row () ) {
			//if ($sql2->row['SIGNED'] == 1){
			//	echo "<pre>";
			//	print_r($sql2->row);
			//	echo "</pre>";
			//}
			$sdv_query [$pk_service] [$sql2->row ['TSTAMP']] [$sql2->row ['USERID']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VERSION'] = $sql2->row ['VERSION'];
			$sdv_query [$pk_service] [$sql2->row ['TSTAMP']] [$sql2->row ['USERID']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['DATE_VALIDATION'] = $sql2->row ['DATE_VALIDATION'];
			$sdv_query [$pk_service] [$sql2->row ['TSTAMP']] [$sql2->row ['USERID']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['SIGN_DATE'] = $sql2->row ['TEXT_SIGN_DATE'];
			$sdv_query [$pk_service] [$sql2->row ['TSTAMP']] [$sql2->row ['USERID']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['SIGNED'] = $sql2->row ['SIGNED'];
		}
		//echo "<pre>";
		//print_r($res_query);
		//echo "</pre>";
		//echo "##<br/><br/><br/>##";
		
		$strategy = $this->GetStrategy();
		//echo "<pre>";
		//print_r($strategy);
		//echo "</pre>";
		
		$lastdate = false;
		//giro qua per singola data e posso calcolare le percentuali utilizzando la strategia e i field che ho effettivamente firmato
		//foreach ($sdv_query as $pkid=>$datearray){
		foreach ($sdv_query [$pk_service] as $tstampdate => $useridarray){
			foreach ($useridarray as $userid => $visitarray){
				//Scorro sulla strategia
				foreach ( $strategy as $visitnum => $val ) {
					//$n_v_progr = count ( $res_query [$pk_service] [$visitnum] );
					$retval[$userid][$tstampdate][$visitnum]['_name'] = trim($visit->visitnums[$visitnum]['TEXT']);
					
					foreach ( $res_query [$pk_service] [$visitnum] as $v_progr => $val_vprogr ) { //$sdv_query??
						foreach ( $val as $esam => $val_esam ) {
							$retval[$userid][$tstampdate][$visitnum][$v_progr][$esam]['_name'] = trim($visit->esams [$visitnum][$esam]['TESTO']);

							if ($lastdate){
								foreach ($retval as $tmpuser=>$tmpdatearray){
									foreach ($retval[$tmpuser][$lastdate][$visitnum][$v_progr][$esam] as $progr => $farray){
										foreach ($farray as $fname => $value){
											if (substr($fname, 0, 1) != "_"){
												//Nome field e non mio campo custom
												//echo "{$fname} --> {$value} <br/>";
												if ($value){
													//Vado di incrementale, senza mai togliere se cambio utente
													$retval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr][$fname] = $value; //$retval[$tmpuser][$lastdate][$visitnum][$esam][$fname];
												}
											}
										}
									}
								}
							}
							
							foreach ( $res_query [$pk_service] [$visitnum] [$v_progr] [$esam] as $progr => $val_progr ) { //Anche qui progressivo su valorizzati sdv??
								//echo "{$val_progr['TSTAMP']} -- {$tstampdate}<br/>";
								if ($val_progr['FINE']==1 && $val_progr['TSTAMP'] <= $tstampdate ){
									//$visita[$visitnum]['exist']=true;
									foreach ($val_esam as $fname=>$value){
										//Field exist
										if (!isset($retval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr][$fname]) || !$retval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr][$fname]){
											$retval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr][$fname] = 0;
										}
									}
									foreach ($sdv_query[$pk_service][$tstampdate][$userid] [$visitnum] [$v_progr] [$esam][$progr] as $field => $val_field){
										//Field signed
										if ($val_field['SIGNED']){
											$retval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr]['_sign_date'] = $val_field['SIGN_DATE'];
											//$retval[$userid][$tstampdate][$visitnum][$esam]['_sign_date'] = $val_field['SIGN_DATE']; //Creo già la data ne
											$retval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr][$field] = $val_field['SIGN_DATE']; //1; //Field signed
											//echo "{$visitnum} {$esam} {$field} --> {$val_field['SIGN_DATE']} <br/>";
										}else{
											$retval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr][$field] = 0; //1; //Field signed
											//echo "{$visitnum} {$esam} {$field} --> 0 <br/>"; //Backtrace
										}
									}
								}
							}
							//
						}
					}
					//
				}
				
			}
			//echo $tstampdate."<br/>";
			$lastdate = $tstampdate;
		}
		//echo "<pre>";
		//print_r($retval);
		//echo "</pre>";
		//Array x data sulle schede inviate
		$asent = array();
		foreach ($res_query [$pk_service] as $visitnum => $visitarray){
			foreach ( $visitarray as $v_progr => $val_vprogr ) {
				foreach ($val_vprogr as $esam => $esamarray){
					foreach ($esamarray as $progr=> $val_progr){
						if ($val_progr['FINE']==1){
							$asent[$val_progr['TSTAMP']][$visitnum][$v_progr][$esam][$progr] = 1;
						}
					}
				}
			}
		}
		ksort($asent);
		$lastdate = false;
		foreach ($asent as $tstampdate => $tstamparray){
			if ($lastdate){
				foreach ($asent[$lastdate] as $visitnum => $visitarray){
					foreach ( $visitarray as $v_progr => $val_vprogr ) {
						foreach ($val_vprogr as $esam => $esamarray){
							foreach ($esamarray as $progr=> $val_progr){
								$asent[$tstampdate][$visitnum][$v_progr][$esam][$progr] = $asent[$lastdate][$visitnum][$v_progr][$esam][$progr];
							}
						}
					}
				}
			}
			$lastdate = $tstampdate;
		}
		
		//echo "<pre>";
		//print_r($asent);
		//echo "</pre>";
		
		//Calcolo array finale
		$baseval = $retval;
		$retval = array();
		//echo "START!<br/>";
		$lastdate = false;	
		foreach ($baseval as $userid => $uarray){
			foreach ($uarray as $tstampdate => $tstamparray){
				$retval[$userid][$tstampdate]['_notes']="";
				$retval[$userid][$tstampdate]['_prev']="";
				$retval[$userid][$tstampdate]['_curr']="";
				$retval[$userid][$tstampdate]['_signed']=false;
				//Calcolo prima e dopo su inserimento schede
				foreach ($asent as $sentdate => $sentarray){
					if ($sentdate < $tstampdate){
						if (!$retval[$userid][$tstampdate]['_curr']){
							$retval[$userid][$tstampdate]['_curr'] = $sentdate;
						}else{
							if ($sentdate > $retval[$userid][$tstampdate]['_curr']){
								$retval[$userid][$tstampdate]['_curr'] = $sentdate;
							}
						}
					}
				}
				if ($lastdate){
					$retval[$userid][$tstampdate]['_prev'] = $retval[$userid][$lastdate]['_curr'];
				}
				//DEBUG
				//echo "{$userid} - {$tstampdate}<br/><br/>";
				//$retval[$userid][$tstampdate]['_notes'] = $retval[$userid][$tstampdate]['_prev']."-->".$retval[$userid][$tstampdate]['_curr'];
				//$diff = array_diff($asent[$retval[$userid][$tstampdate]['_curr']], $asent[$retval[$userid][$tstampdate]['_prev']]);
				$diff = $asent[$retval[$userid][$tstampdate]['_curr']];
				if ($asent[$retval[$userid][$tstampdate]['_prev']]){
					foreach ($asent[$retval[$userid][$tstampdate]['_prev']] as $tmpvnum => $tmpvarray){
						foreach ($tmpvarray as $tmpvprogr => $tmpvparray){
							foreach ($tmpvparray as $tmpesam => $tmpearray){
								foreach ($tmpearray as $tmpprogr => $tmpvalue){
									unset($diff[$tmpvnum][$tmpvprogr][$tmpesam][$tmpprogr]);
									//echo "{$tmpvnum}-{$tmpvprogr}-{$tmpvprogr}-{$tmpprogr} --> {$diff[$tmpvnum][$tmpvprogr][$tmpesam][$tmpprogr]}<br/>";
									//if ($diff[$tmpvnum][$tmpvprogr][$tmpesam][$tmpprogr]){ //Sempre verificato
									//	$diff[$tmpvnum][$tmpvprogr][$tmpesam][$tmpprogr] = 0;
									//}
								}
							}
						}
					}
				}
				//echo "<pre>";
				//echo "CURRENT:\n";
				//print_r($asent[$retval[$userid][$tstampdate]['_curr']]);
				//echo "PREVIOUS:\n";
				//print_r($asent[$retval[$userid][$tstampdate]['_prev']]);
				//echo "DIFF:\n";
				//print_r($diff);
				//echo "</pre>";
				foreach ($diff as $tmpvnum => $tmpvarray){
					foreach ($tmpvarray as $tmpvprogr => $tmpvparray){
						foreach ($tmpvparray as $tmpesam => $tmpearray){
							foreach ($tmpearray as $tmpprogr => $tmpvalue){
								$retval[$userid][$tstampdate]['_notes'] .= trim($visit->visitnums[$tmpvnum]['TEXT'])."/".trim($visit->esams [$tmpvnum][$tmpesam]['TESTO'])." ({$tmpvnum}/{$tmpesam}) SEQ: {$tmpprogr}<br/>";
							}
						}
					}
				}
				
				
				//$retval[$userid][$tstampdate]['_notes'] .= print_r($diff);
				//Continuo con logica di calcolo percentuali
				foreach ($tstamparray as $visitnum => $vprogarray){
					$retval[$userid][$tstampdate][$visitnum]['_tot'] = 0;
					$retval[$userid][$tstampdate][$visitnum]['_signed'] = 0;
					//Genero il campo nome
					$retval[$userid][$tstampdate][$visitnum]['_name'] = $baseval[$userid][$tstampdate][$visitnum]['_name'];
					foreach ($vprogarray as $v_progr => $varray){
						//Unisco i progressivi
						foreach ($varray as $esam => $eprogarray){
							if (is_numeric($esam)){
								$retval[$userid][$tstampdate][$visitnum][$esam]['_tot'] = 0;
								$retval[$userid][$tstampdate][$visitnum][$esam]['_signed'] = 0;
								//Genero il campo nome
								$retval[$userid][$tstampdate][$visitnum][$esam]['_name'] = $baseval[$userid][$tstampdate][$visitnum][$v_progr][$esam]['_name'];
								foreach ($eprogarray as $progr => $earray){
									//Unisco i progressivi
									foreach ($earray as $fname => $fvalue){
										if (substr($fname, 0, 1) != "_"){
											$retval[$userid][$tstampdate][$visitnum]['_tot']++;
											$retval[$userid][$tstampdate][$visitnum][$esam]['_tot']++;
											if ($fvalue){
												$retval[$userid][$tstampdate][$visitnum]['_signed']++;
												$retval[$userid][$tstampdate][$visitnum][$esam]['_signed']++;
												//Genero il campo data firma
												$retval[$userid][$tstampdate][$visitnum][$esam]['_sign_date'] = $baseval[$userid][$tstampdate][$visitnum][$v_progr][$esam][$progr]['_sign_date'];
											}
										}
									}
									if ($retval[$userid][$tstampdate][$visitnum][$esam]['_signed'] > 0 && $retval[$userid][$tstampdate][$visitnum][$esam]['_sign_date']){
										$retval[$userid][$tstampdate]['_signed'] = true;
									}
									$retval[$userid][$tstampdate][$visitnum][$esam]['_perc_signed']=round($retval[$userid][$tstampdate][$visitnum][$esam]['_signed']/$retval[$userid][$tstampdate][$visitnum][$esam]['_tot']*100,2);									
								}
							}
						}
						$retval[$userid][$tstampdate][$visitnum]['_perc_signed']=round($retval[$userid][$tstampdate][$visitnum]['_signed']/$retval[$userid][$tstampdate][$visitnum]['_tot']*100,2);
					}
				}
				if ($retval[$userid][$tstampdate]['_signed']){
					$lastdate = $tstampdate;
				}
			}
		}
		//echo "<pre>";
		//print_r($retval);
		//echo "</pre>";
		return $retval;
		
		/*
		foreach ($retval[$userid] as $tstampdate => $tstamparray){
			foreach ($tstamparray as $visitnum => $varray){
				foreach ($varray as $esam => $earray){
					if (is_numeric($esam)){
						foreach ($earray as $fname => $fvalue){
							if (substr($fname, 0, 1) != "_"){
								if (!isset($signval[$userid][$fvalue][$visitnum]['_tot'])){$signval[$userid][$fvalue][$visitnum]['_tot'] = 0;}
								if (!isset($signval[$userid][$fvalue][$visitnum]['_signed'])){$signval[$userid][$fvalue][$visitnum]['_signed'] = 0;}
								if (!isset($signval[$userid][$fvalue][$visitnum][$esam]['_tot'])){$signval[$userid][$fvalue][$visitnum][$esam]['_tot'] = 0;}
								if (!isset($signval[$userid][$fvalue][$visitnum][$esam]['_signed'])){$signval[$userid][$fvalue][$visitnum][$esam]['_signed'] = 0;}
								$signval[$userid][$fvalue][$visitnum]['_tot']++;
								$signval[$userid][$fvalue][$visitnum][$esam]['_tot']++;
								if ($fvalue){
									$signval[$userid][$fvalue][$visitnum]['_signed']++;
									$signval[$userid][$fvalue][$visitnum][$esam]['_signed']++;
									$signval[$userid][$fvalue][$visitnum][$esam]['_sign_date'] = $fvalue;
								}
							}
						}
						//$signval[$userid][$tstampdate][$visitnum][$esam]['_perc_signed']=round($retval[$userid][$tstampdate][$visitnum][$esam]['_signed']/$retval[$userid][$tstampdate][$visitnum][$esam]['_tot']*100,2);
					}
				}
				//$signval[$userid][$tstampdate][$visitnum]['_perc_signed']=round($retval[$userid][$tstampdate][$visitnum]['_signed']/$retval[$userid][$tstampdate][$visitnum]['_tot']*100,2);
			}
		}
		echo "<pre>";
		print_r($signval);
		echo "</pre>";
		*/
		
	}
	
	function visite_signature_OLD() {
		global $xml_dir;
		//global $config_service;
		global $conn;
		global $in;
		$pk_service = $this->sql->row [$this->config_service ['PK_SERVICE']];
		$visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
		//echo "<pre>";
		//print_r($visit);
		//echo "</pre>";
		$sql_visite = "
			select
				fine,
				inizio,
				userid,
				visitnum,
				visitnum_progr,
				esam,
				progr,
				visitclose,
				abilitato
			from {$this->config_service['service']}_coordinate
			where {$this->config_service['PK_SERVICE']}='$pk_service'
			and abilitato=1
			order by visitnum, visitnum_progr, esam, progr";
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite );
		while ( $sql2->get_row () ) {
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['INIZIO'] = $sql2->row ['INIZIO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['FINE'] = $sql2->row ['FINE'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['USERID'] = $sql2->row ['USERID'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['ABILITATO'] = $sql2->row ['ABILITATO'];
			$res_query [$pk_service] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] ['VISITCLOSE'] = $sql2->row ['VISITCLOSE'];
		}
		$sql_visite = "
			select
				s.visitnum,
				s.visitnum_progr,
				s.esam,
				s.progr,
				s.field,
				s.version,
				s.valid,
				s.date_validation,
				s.protocol_violation,
				s.signed,
				to_char(s.last_sign_date, 'DD/MM/YYYY HH24:MI:SS') as text_sign_date,
				to_char(s.last_sign_date, 'YYYY/MM/DD HH24:MI:SS') as last_sign_date,
				s.userid
			from {$this->config_service['service']}_rpt_sdv_status s 
			where s.{$this->config_service['PK_SERVICE']}='$pk_service' 
			order by s.last_sign_date, s.visitnum, s.visitnum_progr, s.esam, s.progr";
		$sql2 = new query ( $conn );
		$sql2->exec ( $sql_visite );
		//Inserire la data tra pk_service e visitnum
		//$sdv_query [$pk_service] [$sql2->row ['LAST_SIGN_DATE']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VERSION'] = array();
		//$sdv_query [$pk_service] [$sql2->row ['LAST_SIGN_DATE']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['DATE_VALIDATION'] = array();
		while ( $sql2->get_row () ) {
			$sdv_query [$pk_service] [$sql2->row ['LAST_SIGN_DATE']] [$sql2->row ['USERID']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['VERSION'] = $sql2->row ['VERSION'];
			$sdv_query [$pk_service] [$sql2->row ['LAST_SIGN_DATE']] [$sql2->row ['USERID']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['DATE_VALIDATION'] = $sql2->row ['DATE_VALIDATION'];
			$sdv_query [$pk_service] [$sql2->row ['LAST_SIGN_DATE']] [$sql2->row ['USERID']] [$sql2->row ['VISITNUM']] [$sql2->row ['VISITNUM_PROGR']] [$sql2->row ['ESAM']] [$sql2->row ['PROGR']] [$sql2->row ['FIELD']] ['SIGN_DATE'] = $sql2->row ['TEXT_SIGN_DATE'];
		}
		//echo "<pre>";
		//print_r($sdv_query);
		//echo "</pre>";
		
		$strategy = $this->GetStrategy();
		//echo "<pre>";
		//print_r($strategy);
		//echo "</pre>";
		
		$lastdate = false;
		//giro qua per singola data e posso calcolare le percentuali utilizzando la strategia e i field che ho effettivamente firmato
		//foreach ($sdv_query as $pkid=>$datearray){
		foreach ($sdv_query [$pk_service] as $signdate => $useridarray){
			foreach ($useridarray as $userid => $visitarray){
				//Scorro sulla strategia
				foreach ( $strategy as $visitnum => $val ) {
					//$n_v_progr = count ( $res_query [$pk_service] [$visitnum] );
					$retval[$userid][$signdate][$visitnum]['_name'] = trim($visit->visitnums[$visitnum]['TEXT']);
					//$vtot = 0;
					$vsig = 0;
					if ($lastdate){
						foreach ($retval as $tmpuser=>$tmpdatearray){
							//foreach ($tmpdatearray as $tmpdate=>$tmpvisarray){
								//foreach ($tmpvisarray as $tmpvisit => $tmparr){
									//$vtot += $retval[$tmpuser][$tmpdate][$tmpvisit]['_tot'];
									$vsig += $retval[$tmpuser][$lastdate][$visitnum]['_signed'];
								//}
							//}
						}
					}
					$retval[$userid][$signdate][$visitnum]['_tot'] = 0; //$vtot; //0;
					$retval[$userid][$signdate][$visitnum]['_signed'] = $vsig; //0;
					
					foreach ( $res_query [$pk_service] [$visitnum] as $v_progr => $val_vprogr ) { //$sdv_query??
						foreach ( $val as $esam => $val_esam ) {
							$retval[$userid][$signdate][$visitnum][$esam]['_name'] = trim($visit->esams [$visitnum][$esam]['TESTO']);
							$retval[$userid][$signdate][$visitnum][$esam]['_tot'] = 0;
							$esig = 0;
							if ($lastdate){
								foreach ($retval as $tmpuser=>$tmpdatearray){
									//foreach ($tmpdatearray as $tmpdate=>$tmpvisarray){
										//foreach ($tmpvisarray as $tmpvisit => $tmpesamarr){
											//foreach ($tmpesamarr as $tmpesam => $tmparr){
												//$vtot += $retval[$tmpuser][$tmpdate][$tmpvisit]['_tot'];
												$esig += $retval[$tmpuser][$lastdate][$visitnum][$esam]['_signed'];
											//}
										//}
									//}
								}
							}
							$retval[$userid][$signdate][$visitnum][$esam]['_signed'] = $esig;
							
							foreach ( $res_query [$pk_service] [$visitnum] [$v_progr] [$esam] as $progr => $val_progr ) { //Anche qui progressivo su valorizzati sdv??
								//$visita[$visitnum]['exist']=true;
								foreach ($val_esam as $fname=>$value){
									$retval[$userid][$signdate][$visitnum]['_tot']++;
									$retval[$userid][$signdate][$visitnum][$esam]['_tot']++;
								}
								foreach ($sdv_query[$pk_service][$signdate][$userid] [$visitnum] [$v_progr] [$esam][$progr] as $field => $val_field){
									//$retval[$signdate][$visitnum][$esam][$field] = $val_field['VERSION'];
									$retval[$userid][$signdate][$visitnum]['_signed']++;
									$retval[$userid][$signdate][$visitnum][$esam]['_signed']++;
									$retval[$userid][$signdate][$visitnum][$esam]['_sign_date'] = $val_field['SIGN_DATE'];
								}
								//foreach ($retval[$signdate][$visitnum][$esam] as $rvfield=>rvversion){
								//}
							}
							$retval[$userid][$signdate][$visitnum][$esam]['_perc_signed']=round($retval[$userid][$signdate][$visitnum][$esam]['_signed']/$retval[$userid][$signdate][$visitnum][$esam]['_tot']*100,2);
						}
					}
					$retval[$userid][$signdate][$visitnum]['_perc_signed']=round($retval[$userid][$signdate][$visitnum]['_signed']/$retval[$userid][$signdate][$visitnum]['_tot']*100,2);
				}
				
			}
			$lastdate = $signdate;
		}
		return $retval;
	}
 
 }
 
 
 
 
?>