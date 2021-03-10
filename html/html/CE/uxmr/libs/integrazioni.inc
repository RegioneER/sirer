<?php
/**
 * @package Integrazioni
 */

class integrazioni_prototype{

	var $conn;
	var $eq_int;
	var $eqs;
	var $eq_enabled;
	var $userid;
	var $profilo;
	var $config_param;
	var $role;
	var $xmr_tip;
	var $service;
	var $pk_field;
	var $pk_value;
	var $approv_role;
	var $non_appr_states;
	var $appr_states;
	var $observer_role;
	var $non_appr_condition;
	var $inrev_esam;
	var $inrev_visitnum;
	var $stato_obj;
	var $stato_no_eq;
	var $session_vars;
	var $excluded_visits;
	var $config_service;
	
	/**
	 * 
	 * Funzione che restituisce il codice html delle integrazioni effettuate sull'oggetto in questione
	 * Se specificato il parametro $eq_int mostra il dettaglio dell'integrazione in questione
	 * @param array $vlist
	 * @param array $config_service
	 * @param String $xml_dir
	 * @param boolean $table
	 * @param number $eq_int
	 * @param boolean $full_mode
	 */
	function showEq($vlist, $config_service, $xml_dir, $table=true, $eq_int=null, $full_mode=false){
		$this->eqs='';
		$sql_query="select equery_int from {$this->service}_EQ where
		{$this->pk_field}=:pk_value order by ins_dt desc
				";
		$bind['pk_value']=$this->pk_value;
		$sql=new query($this->conn);
		$sql->exec($sql_query, $bind);
		while ($sql->get_row()){
			$this->eqs[]=$sql->row['EQUERY_INT'];
		}
		
		if (!isset($eq_int)) $ret.="<h1>Lista integrazioni</h1>";
		

		if ($table) $ret.="
		<table border=1 cellpadding=0 width=80% cellspacing=0>
			<tr>
				<th>N.ro</th>
				<th>Stato</th>
				<th>Data inserimento</th>
				<th>Data chiusura</th>
				<th>Note Integrazione</th>
				<th>Richiesta Integrazione</th>
				<th>Note esito</th>
				<th>Dettaglio modifiche</th>
			</tr>
		";
		foreach ($this->eqs as $key=>$val){
			if (!isset($eq_int)) $ret.=$this->getEqShortDetails($vlist, $config_service,$val, $table);
			else {
				if ($val==$eq_int){
					if (!$full_mode) $ret.=$this->getEqShortDetails($vlist, $config_service,$val, $table);
					else $ret.=$this->getEqDetails($vlist, $config_service,$val, $xml_dir);
				}
			}
		}
		if ($table) $ret.="</table>";
		return $ret;
	}

	/**
	 * 
	 * Restituisce il codice html del dettaglio dell'integrazione $eq_int
	 * @param array $vlist
	 * @param array $config_service
	 * @param number $eq_int
	 * @param String $xml_dir
	 */
	function getEqDetails($vlist, $config_service,$eq_int,$xml_dir){		
		//Recupero da DB i campi dalla tabella [PREFIX]_EQ relativi all'integrazione in questione
		$sql_query_eq="select * from {$this->service}_EQ where equery_int=:eq_int";
		$sql=new query($this->conn);
		$bind['eq_int']=$eq_int;
		$sql->get_row($sql_query_eq,$bind);
		$ret.="<a href=\"index.php?{$this->pk_field}={$this->pk_value}&SHOW_EQ\">Torna alla lista delle integrazioni</a>";
		$ret.="<h2>Integrazione n.ro {$eq_int}</h2>";
		if ($sql->row['STATO']==1) $d_stato="Approvata";
		if ($sql->row['STATO']==2) $d_stato="In corso di approvazione";
		if ($sql->row['STATO']==0 && $sql->row['RICH_DM']=='') $d_stato="In corso di compilazione";
		if ($sql->row['STATO']==0 && $sql->row['RICH_DM']!='') $d_stato="Richiesta Integrazione da {$this->approv_role[$sql->row['WF_STATO']]}";
		if ($sql->row['STATO']==3) $d_stato="Rifiutata";
		$stato=$sql->row['STATO'];
		$ret.="<li>Stato: <b>$d_stato</b></li>";
		$ret.="<li>Richiesta il : <b>{$sql->row['INS_DT']}</b></li>";
		if ($sql->row['STATO']==1 || $sql->row['STATO']==3) $ret.="<li>Chiusa il : <b>{$sql->row['CLOSE_DT']}</b></li>";
		if ($sql->row['RICH_DE']!='') $ret.="<li>Note inserite da {$this->role} : <b>{$sql->row['RICH_DE']}</b></li>";
		if ($sql->row['RICH_DM']!='') $ret.="<li>Note inserite da {$this->approv_role[$sql->row['WF_STATO']]} : <b>{$sql->row['RICH_DM']}</b></li>";
		if ($sql->row['RISP_DM']!='') $ret.="<li>Note esito: <b>{$sql->row['RISP_DM']}</b></li>";
		
		$ret.="<li><b>Dettaglio:</b><ul>";
		//Recupero da DB i campi dalla tabella [PREFIX]_EQFIELD relativi alle coordinate di tutte le schede modificate dall'integrazione in questione
		$sql_query_field="select distinct visitnum, visitnum_progr, progr, esam, action from {$this->service}_eqfield where eq_int=:eq_int order by VISITNUM_PROGR,PROGR";
		$bind['eq_int']=$eq_int;
		$sql->exec($sql_query_field,$bind);
		$detailSpec='';
		while ($sql->get_row()){
			//in $action setto il tipo di modifica (1=inserimento, 2=eliminazione, 0=modifica)
			$action=$sql->row['ACTION'];
			//Aggiungo identificativo del blocco se il blocco è progressivo
			$blocco="";
			if ($sql->row['VISITNUM_PROGR']>0) {
				$blocco_nr=$sql->row['VISITNUM_PROGR']+1;
				$blocco="Blocco: <b>$blocco_nr</b>";
			}
			//Aggiungo identificativo della scheda modificata se la scheda è progressiva
			$scheda_nr='';
			if ($vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['PROGR']=='yes'){
				$scheda_nr="Scheda n.ro <b>{$sql->row['PROGR']}</b>";
			}
			
			$nomeScheda=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			if ($sql->row['ACTION']==1) $detail="Scheda aggiunta";
			if ($sql->row['ACTION']==0) $detail="Scheda modificata";
			if ($sql->row['ACTION']==2) $detail="Scheda eliminata";
			if ($blocco!='' && $scheda_nr!='') {
				$specScheda="$blocco, $scheda_nr";
			}else $specScheda=$blocco.$scheda_nr;
			if ($specScheda!='') $specScheda="(".$specScheda.")";
			$detailSpec.="<h3>($detail) <b>$nomeScheda</b> $specScheda</h3><ul>";
			//Construisco l'oggetto xml_form relativo alla scheda modificata
			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $db_vals, $xml_dir );
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );			
			$db_vals='';
			//Se l'integrazione è in corso di compilazione/approvazione e la scheda è stata modificata (non cancellata o inserita) 
			//recupero i valori pre-integrazione dalla tabella corrente
			//Altrimenti li recupero dalla tabella di storico fintrando sul campo ID_QUERY=$eq_int
			// e li memorizzo nell'array associativo $db_vals
			if ($action==0 && ($stato==0 || $stato==2)){
				//Logger::send("prendo da tb");
				$sql_tb_vals="select * from {$xml_form->form['TABLE']}
							where 
								visitnum=:visitnum
								and esam=:esam
								and progr=:progr
								and visitnum_progr=:visitnum_progr
								and {$this->pk_field}=:pk_field
							";	
				$bind2['visitnum']=$sql->row['VISITNUM'];
				$bind2['visitnum_progr']=$sql->row['VISITNUM_PROGR'];
				$bind2['esam']=$sql->row['ESAM'];
				$bind2['progr']=$sql->row['PROGR'];
				$bind2['pk_field']=$this->pk_value;
				$sql2=new query($this->conn);
				$sql2->exec($sql_tb_vals, $bind2);
				$sql2->get_row();
				foreach($sql2->row as $field=>$valore) $db_vals[$field]=$valore;
			}else if ($action==0){
				//Logger::send("prendo da tb");
				$sql_tb_vals="select * from S_{$xml_form->form['TABLE']}
							where 
								visitnum=:visitnum
								and esam=:esam
								and progr=:progr
								and visitnum_progr=:visitnum_progr
								and {$this->pk_field}=:pk_field
								and id_query=:eq_int
							";	
				$bind2['visitnum']=$sql->row['VISITNUM'];
				$bind2['visitnum_progr']=$sql->row['VISITNUM_PROGR'];
				$bind2['esam']=$sql->row['ESAM'];
				$bind2['progr']=$sql->row['PROGR'];
				$bind2['pk_field']=$this->pk_value;
				$bind2['eq_int']=$eq_int;
				$sql2=new query($this->conn);
				$sql2->exec($sql_tb_vals, $bind2);
				$sql2->get_row();
				foreach($sql2->row as $field=>$valore) $db_vals[$field]=$valore;
			}
			//Prendo dalla tabella [PREFIX]_EQFIELD i valori dei campi aggiunti/modificati/eliminati durante l'integrazione
			// e li memorizzi nell'array associativo $eq_vals
			$sql_query_vals="select FIELD, VALORE from {$this->service}_EQFIELD 
			where 
				visitnum=:visitnum
				and esam=:esam
				and progr=:progr
				and visitnum_progr=:visitnum_progr
				and eq_int=:eq_int
				and {$this->pk_field}=:pk_field
			";
			$bind2['visitnum']=$sql->row['VISITNUM'];
			$bind2['visitnum_progr']=$sql->row['VISITNUM_PROGR'];
			$bind2['esam']=$sql->row['ESAM'];
			$bind2['progr']=$sql->row['PROGR'];
			$bind2['eq_int']=$eq_int;
			$bind2['pk_field']=$this->pk_value;
			
			$sql2=new query($this->conn);
			$sql2->exec($sql_query_vals, $bind2);
			$eq_vals='';
			while ($sql2->get_row()){
				$eq_vals[$sql2->row['FIELD']]=$sql2->row['VALORE'];
			}
			//Aggiungo ad $eq_vals le coordinate della scheda in questione
			$eq_vals[$this->pk_field]=$this->pk_value;
			$eq_vals['VISITNUM']=$sql->row['VISITNUM'];
			$eq_vals['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
			$eq_vals['ESAM']=$sql->row['ESAM'];;
			$eq_vals['PROGR']=$sql->row['PROGR'];
			//Costruisco $db_vals2 come merge dei valori pre-modifica sovrascritti dai valori post-modifica
			//Attenzione! in caso di eliminazione della scheda in $db_vals avrò i valori della scheda eliminata
			foreach($db_vals as $key=>$val) $db_vals2[$key]=$val;
			foreach($eq_vals as $key=>$val) $db_vals2[$key]=$val;
			
			//In caso di modifica della scheda costruisco una tabella con tre colonne (nome campo|valora nuovo|valore vecchio)
			//Altrimenti costruisco una tabella con 2 colonne (nome campo|valore)
			if ($action==0) $detailSpec.="<table border=1 width=70% cellpadding=0 cellspacing=0><tr><th>Campo</th><th>Valore nuovo</th><th>Valore vecchio</th></tr>";
			else $detailSpec.="<table border=1 width=70% cellpadding=0 cellspacing=0><tr><th>Campo</th><th>Valore</th></tr>";
			//Ciclo tutti i campi della form xml
			//Logger::send("andiamo a pranzo");
		//Logger::send($this->session_vars);
			foreach ($xml_form->fields as $key=>$val){
				//Identifico il tipo di campo ed includo la libreria relativa
				if (isset ( $val ['TYPE'] ) && $val ['TYPE'] != '')
				$field_type = "field_{$val['TYPE']}";
				else
				$field_type = "field";
				if ($config_service['field_lib'] != '' && file_exists ( $config_service['field_lib'] . $field_type . ".inc" )) {
					include_once $config_service['field_lib'] . $field_type . ".inc";
				} else
				include_once "libs/{$field_type}.inc";
				$this->session_vars['ID_PRAT']=$this->session_vars[$config_service['PK_SERVICE']]=$this->pk_value;
				//Se ci sono modifiche su quel campo costruisco l'oggetto relativo al campo
				if (isset($eq_vals[$val['VAR']]))
				{
					//Costruisco il campo e chiamo i metodi di costruzione del campo in visualizzazione con i valori $db_vals (pre-modifica)
					$field_obj = new $field_type ( $xml_form, $key, $this->conn, $db_vals, $this->session_vars, $this->service, $errors );
					$field_obj->close_($db_vals[$field_obj->id]);
					$input_txt=$field_obj->input_txt;
					$old_value=$field_obj->input_field;
					//Costruisco il campo e chiamo i metodi di costruzione del campo in visualizzazione con i valori $db_vals2 (post-modifica)
					$field_obj = new $field_type ( $xml_form, $key, $this->conn, $db_vals2, $this->session_vars, $this->service, $errors );
					$field_obj->close_($db_vals2[$field_obj->id], true);
					$new_value=$field_obj->input_field;
					if ($field_obj->input_field!=''){
						//Se l'azione è di modifica construisco il tracciato record con le tre colonne, altrimeni solo con 2
						if ($action==0) $detailSpec.="<tr><td valign=top>".$input_txt."</td><td valign=top>$new_value</td><td valign=top>$old_value</td></tr>";
						if ($action==1) $detailSpec.="<tr><td valign=top>".$input_txt."</td><td valign=top>$new_value</td></tr>";
						if ($action==2) $detailSpec.="<tr><td valign=top>".$input_txt."</td><td valign=top>$new_value</td></tr>";
					}
					
				}
			
				}
				$detailSpec.="</tr></table></ul>";
								
		}
		return $ret.$detailSpec;
	}
	
	/**
	 * 
	 * Costruisce un riassunto dei dettagli dell'integrazione $eq_int
	 * Se $row=true il risultato è un recordo di una tabella html
	 * Altrimenti un elenco puntato
	 * @param array $vlist
	 * @param array $config_service
	 * @param number $eq_int
	 * @param boolean $row
	 * @return string
	 */
	function getEqShortDetails($vlist, $config_service,$eq_int, $row=true){
		//Recupero i dati dell'integrazione
		$sql_query_eq="select * from {$this->service}_EQ where equery_int=:eq_int";
		$sql=new query($this->conn);
		$bind['eq_int']=$eq_int;
		$sql->get_row($sql_query_eq,$bind);
		$ret.="<h2><a href=\"index.php?{$this->pk_field}={$this->pk_value}&SHOW_EQ=$eq_int\">Integrazione n.ro {$eq_int}</a></h2>";
		if ($sql->row['STATO']==1) $d_stato="Approvata";
		if ($sql->row['STATO']==2) $d_stato="In corso di approvazione";
		if ($sql->row['STATO']==0 && $sql->row['RICH_DM']=='') $d_stato="In corso di compilazione";
		if ($sql->row['STATO']==0 && $sql->row['RICH_DM']!='') $d_stato="Richiesta Integrazione da {$this->approv_role[$sql->row['WF_STATO']]}";
		if ($sql->row['STATO']==3) $d_stato="Rifiutata";
		
		$ret.="<li>Stato: <b>$d_stato</b></li>";
		$ret.="<li>Richiesta il : <b>{$sql->row['INS_DT']}</b></li>";
		if ($sql->row['STATO']==1 || $sql->row['STATO']==3) $ret.="<li>Chiusa il : <b>{$sql->row['CLOSE_DT']}</b></li>";
		if ($sql->row['RICH_DE']!='') $ret.="<li>Note inserite da {$this->role} : <b>{$sql->row['RICH_DE']}</b></li>";
		if ($sql->row['RICH_DM']!='') $ret.="<li>Note inserite da {$this->approv_role[$sql->row['WF_STATO']]} : <b>{$sql->row['RICH_DM']}</b></li>";
		if ($sql->row['RISP_DM']!='') $ret.="<li>Note esito: <b>{$sql->row['RISP_DM']}</b></li>";
		if ($row) $record="
			<td valign=top><a href=\"index.php?{$this->pk_field}={$this->pk_value}&SHOW_EQ=$eq_int\">$eq_int</a></td>
			<td valign=top>$d_stato</td>
			<td valign=top>{$sql->row['INS_DT']}</td>
			<td valign=top>{$sql->row['CLOSE_DT']}</td>
			<td valign=top>{$sql->row['RICH_DE']}</td>
			<td valign=top>{$sql->row['RICH_DM']}</td>
			<td valign=top>{$sql->row['RISP_DM']}</td>
		";
		$ret.="<li><b>Dettaglio:</b><ul>";
		//Recupero la lista delle schede modificate/eliminate/aggiunte dall'integrazione
		$sql_query_field="select distinct visitnum, visitnum_progr, progr, esam, action from {$this->service}_eqfield where eq_int=:eq_int order by VISITNUM_PROGR,PROGR";
		$bind['eq_int']=$eq_int;
		$sql->exec($sql_query_field,$bind);
		$detailSpec='';
		while ($sql->get_row()){
			//Se il blocco è progressivo aggiungo l'identificativo del blocco
			$blocco="";
			if ($sql->row['VISITNUM_PROGR']>0) {
				$blocco_nr=$sql->row['VISITNUM_PROGR']+1;
				$blocco="Blocco: <b>$blocco_nr</b>";
			}
			//Se la scheda è progressiva aggiungo l'identificativo della scheda
			$scheda_nr='';
			if ($vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['PROGR']=='yes'){
				$scheda_nr="Scheda n.ro <b>{$sql->row['PROGR']}</b>";
			}
			$nomeScheda=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			if ($sql->row['ACTION']==1) $detail="Scheda aggiunta";
			if ($sql->row['ACTION']==0) $detail="Scheda modificata";
			if ($sql->row['ACTION']==2) $detail="Scheda eliminata";
			if ($blocco!='' && $scheda_nr!='') {
				$specScheda="$blocco, $scheda_nr";
			}else $specScheda=$blocco.$scheda_nr;
			if ($specScheda!='') $specScheda="(".$specScheda.")";
			$detailSpec.="<li>($detail) <b>$nomeScheda</b> $specScheda</li>";
			//$ret.="<pre>".print_r($vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']],true)."</pre>";
		}
		$ret.="$detailSpec</ul></li>";
		if ($row){
			$detailSpec=str_replace("<li>", "<br/>", $detailSpec);
			$detailSpec=str_replace("</li>", "", $detailSpec);
			$detailSpec=ltrim($detailSpec,"<br/>");
			$record.="<td  valign=top>$detailSpec</td>";
			return "<tr>$record</tr>";
		}
		return $ret;
	}

	/**
	 * 
	 * Costruttore ...
	 * @param array $config_param
	 * @param dbconn $conn
	 * @param String $userid
	 * @param String $profilo
	 * @param String $xmr_tip
	 */
	function __construct($config_param, $conn, $userid, $profilo, $xmr_tip,$session_vars){
		$this->pk_field=$config_param['PK_SERVICE'];
		//$this->session_vars=array();
		//$this->session_vars=array_merge($this->session_vars,$session_vars);
			$this->session_vars=$session_vars;
		//Logger::send("costruttore");
		//Logger::trace("trace");
		//Logger::send($session_vars);
		//ROLE
		$this->config_service=$config_param;
		if(is_array($config_param['eQuerySpec']['Integrazione']['ROLE']))
			$this->role=$config_param['eQuerySpec']['Integrazione']['ROLE'][$config_param['service']];
		else
			$this->role=$config_param['eQuerySpec']['Integrazione']['ROLE'];

		//VALIDATOR
		if(is_array($config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']]))
			$this->approv_role=$config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']];
		else
			$this->approv_role=$config_param['eQuerySpec']['Integrazione']['VALIDATOR'];

		if(is_array($config_param['eQuerySpec']['Integrazione']['OBSERVER'][$config_param['service']]))
		$this->observer_role=$config_param['eQuerySpec']['Integrazione']['OBSERVER'][$config_param['service']];
		else
		$this->observer_role=$config_param['eQuerySpec']['Integrazione']['OBSERVER'];

		//NON_APPROV
		if(is_array($config_param['eQuerySpec']['Integrazione']['NON_APPROV'][$config_param['service']]))
			$this->non_appr_states=$config_param['eQuerySpec']['Integrazione']['NON_APPROV'][$config_param['service']];
		else
			$this->non_appr_states=$config_param['eQuerySpec']['Integrazione']['NON_APPROV'];

		//NON_APPROV_QUERY
		if(is_array($config_param['eQuerySpec']['Integrazione']['NON_APPROV_CONDITION'][$config_param['service']]))
			$this->non_appr_condition=$config_param['eQuerySpec']['Integrazione']['NON_APPROV_CONDITION'][$config_param['service']];

		//APPROV
		if(is_array($config_param['eQuerySpec']['Integrazione']['APPROV'][$config_param['service']]))
			$this->appr_states=$config_param['eQuerySpec']['Integrazione']['APPROV'][$config_param['service']];
		else
			$this->appr_states=$config_param['eQuerySpec']['Integrazione']['APPROV'];

		//INREV esam
		if(is_array($config_param['eQuerySpec']['Integrazione']['INREV_ESAM'][$config_param['service']]))
			$this->inrev_esam=$config_param['eQuerySpec']['Integrazione']['INREV_ESAM'][$config_param['service']];
		else
			$this->inrev_esam=$config_param['eQuerySpec']['Integrazione']['INREV_ESAM'];
		//INREV visitnum
		if(is_array($config_param['eQuerySpec']['Integrazione']['INREV_VISITNUM'][$config_param['service']]))
			$this->inrev_visitnum=$config_param['eQuerySpec']['Integrazione']['INREV_VISITNUM'][$config_param['service']];
		else
			$this->inrev_visitnum=$config_param['eQuerySpec']['Integrazione']['INREV_VISITNUM'];
		//blocco delle integrazioni nello stato chiuso
		if(is_array($config_param['eQuerySpec']['Integrazione']['STATO_NO_EQ'][$config_param['service']]))
			$this->stato_no_eq=$config_param['eQuerySpec']['Integrazione']['STATO_NO_EQ'][$config_param['service']];
		else
			$this->stato_no_eq=$config_param['eQuerySpec']['Integrazione']['STATO_NO_EQ'];

		$this->conn=$conn;
		if (isset($_POST[$this->pk_field])) $this->pk_value=$_POST[$this->pk_field];
		else $this->pk_value=$_GET[$this->pk_field];
		$this->service=$config_param['service'];
		$this->userid=$userid;
		$this->profilo=$profilo;
		$this->stato=$this->getStato();
		$this->stato_obj=$this->getStatoObj();
		$this->xmr_tip=$xmr_tip;
		$this->eq_enabled=$this->isEnabled($profilo, $config_param);
		if(is_array($config_param['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$config_param['service']]))$this->excluded_visits=$config_param['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$config_param['service']];
		else
		$this->excluded_visits=$config_param['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'];
		
		$this->checkCreateEqTb();
		//DEBUG
//		if($this->eq_enabled)
//		echo "eq enabled yes<br>";
//		else
//		echo "eq enabled NO<br>";
		//DEBUG
		//Se le integrazioni sono abilitate nel servizio recupero tutte le integrazioni e setto quella attiva
		if ($this->eq_enabled){
			$this->getEqs();
			$this->getActiveEq();
		}

	}
	
	function isApprovRole($role){
		if(is_array($this->approv_role)){
			return ($this->approv_role[$this->stato_obj]==$role);
		}	
		else{
			return ($this->approv_role==$role);
		}
	}
	
	function isObserverRole($role){
		if(is_array($this->observer_role)){
			return ($this->observer_role[$this->stato_obj]==$role);
		}	
		else{
			return ($this->observer_role==$role);
		}
	}

	function isEqueryRole($role){
		if(is_array($this->role)){
			return ($this->role[$this->stato_obj]==$role);
		}	
		else{
			return ($this->role==$role);
		}
	}
	function isExcludedFromEquery($visitnum){
		return $this->excluded_visits["{$visitnum}"];
	}

	/**
	 *
	 * Creazione delle due tabelle se non esitono
	 */
	function checkCreateEqTb($xml_form=null){
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_EQ')";
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		$query->get_row ();
		if($query->numrows==0){
			$query_create = "
			create table {$this->service}_EQ
			(
			  EQUERY_INT NUMBER not null,
			  {$this->pk_field}  NUMBER not null,
			  USERID_INS VARCHAR2(80 CHAR),
			  INS_DT     DATE,
			  STATO      NUMBER,
			  RICH_DM CLOB,
			  RICH_DE CLOB,
			  RISP_DM CLOB,
			  WF_STATO NUMBER,
			  FILE_DM
			)
			";
			  /* *
			   * RICH_DM->domanda dell ufficio per richiedere itnegrazione
			   * RICH_DE->motivo modifica dell'azienda
			   * RISP_DM->motivo del'ufficio per negare
			   * */
			  $sql = new query ( $this->conn );
			  $sql->set_sql ( $query_create );
			  $sql->ins_upd ();
		}
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_EQFIELD')";
		$query = new query ( $this->conn );
		//$query->set_sql ( $query_check_existence );
		$query->exec ($query_check_existence);//non richiede binding
		$query->get_row ();
		if($query->numrows==0){
			$query_create = "
			create table {$this->service}_EQFIELD
			(
			  {$this->pk_field} NUMBER not null,
			  ESAM           NUMBER not null,
			  VISITNUM       NUMBER not null,
			  VISITNUM_PROGR NUMBER not null,
			  PROGR          NUMBER not null,
			  EQ_INT         NUMBER not null,
			  FIELD          VARCHAR2(200 CHAR) not null,
			  VALORE         VARCHAR2(4000 CHAR),
			  ACTION 		NUMBER DEFAULT 0
			)
			";
			$sql = new query ( $this->conn );
			$sql->ins_upd ( $query_create ); //bind non necessario
		}
		return true;
	}

	//Recupero le integrazioni attive
	function getActiveEq(){
		//if ($this->eq_int=='') return null;
		//Stato 0,2,5 se richiedente, 2,5 se approvatore/osservatore
		if($this->role==$this->profilo)
		$sql_query="select equery_int, stato from {$this->service}_EQ where
		--userid_ins='{$this->userid}' and
		{$this->pk_field}=:pk_value
		and stato in (0,2,5)
		";
		else
		$sql_query="select equery_int, stato from {$this->service}_EQ where
		 {$this->pk_field}=:pk_value
		and stato in (2,5)
		";
		$sql=new query($this->conn);
                $bind['pk_value']=$this->pk_value;
		$sql->get_row($sql_query, $bind);
		$this->eq_int=$sql->row['EQUERY_INT'];
		$this->stato=$sql->row['STATO'];
		/*//aggiungere controlli di sicurezza
		if($_POST['EQ_INT']==''){
			$this->eq_int=$_POST['EQ_INT'];

		}*/
	}

	/**
	 * 
	 * Recupero tutte le integrazioni presenti
	 * @return NULL
	 */
	function getEqs(){
		if ($this->eq_int=='') return null;
		$sql_query="select equery_int from {$this->service}_EQ where
		{$this->pk_field}=:pk_service order by ins_dt desc
		";
		unset($bind);
		$bind['PK_SERVICE']=$this->pk_value;
		$sql=new query($this->conn);
		$sql->exec($sql_query,$bind);//binded
		while ($sql->get_row()){
			$this->eqs[]=$sql->row['EQUERY_INT'];
		}
	}

	/**
	 * 
	 * Recupero lo stato dell'integrazione attiva
	 */
	function getStato(){
		
		if ($this->eq_int=='') return null;
		$sql_query="select stato from {$this->service}_EQ where
		userid_ins='{$this->userid}'
		and equery_int={$this->eq_int}
		and {$this->pk_field}={$this->pk_value}
		";
		$sql=new query($this->conn);
		$sql->get_row($sql_query);
		return $sql->row['STATO'];
	}

	/**
	 * 
	 * Recupero dal Wrokflow lo stato dell'oggetto in questione
	 */
	function getStatoObj(){
		if(is_numeric($this->pk_value)) {
                        $bind['pk_value']=$this->pk_value;
			$sql_query="select id_stato from {$this->service}WF_STATO where	PK_SERVICE=:pk_value";
			$sql=new query($this->conn);
			$sql->get_row($sql_query, $bind);
			if($sql->numrows==0) return 1;
			else return $sql->row['ID_STATO'];
		}
		
	}

	/**
	 * 
	 * Controllo che il modulo sia attivato ed utilizzabile sull'oggetto in questione
	 * @param String $profilo
	 * @param array $config_param
	 */
	function isEnabled($profilo, $config_param){
		//Se non esiste la tabella [PREFIX]_EQ restituisco false
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_EQ')";
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		$query->get_row ();
		if($query->numrows==0) 
		return false;
		//Se l'oggetto è in corso di compilazione resituisco false
		if($this->stato_obj==1 && $this->role==$profilo) return false;
		//Se l'oggetto si trova in uno stato che non è integrabile restituisco false
		if($this->stato_no_eq[$this->stato_obj] && $this->role==$profilo) return false;
		//Se il parametro di configurazione eQuery!=1 restituisco false
		if ($config_param['eQuery']!=1) return false;
		//Se il profilo è != dall'integratore o è il Data Entry per lo stato in questione e il profilo non è l'approvatore per lo stato in questione restituisco false;
		if (($this->role!=$profilo && $this->xmr_tip=='DE') && !($this->approv_role==$profilo || $this->approv_role[$this->stato_obj]==$profilo ))	return false;
		else return true;
		//Altrimenti resituisco true;

	}

	/**
	 * 
	 * Creo l'integrazione
	 * @param String $rich_mess
	 */
	function createEq($rich_mess=null){
		$sql=new query($this->conn);
		$sql_seq="select {$this->service}_eqseq.nextval as eq_int from dual";
		$sql->get_row($sql_seq);
		$this->eq_int=$sql->row['EQ_INT'];
		$val_th['EQUERY_INT']=$this->eq_int;
		$val_th[$this->pk_field]=$this->pk_value;
		$val_th['USERID_INS']=$this->userid;
		$val_th['INS_DT']='sysdate';
		if (isset($rich_mess)) $val_th['RICH_DM']=$rich_mess;
		$val_th['STATO']=0;
		if($_POST[$this->pk_field]!="") $id_prat=$_POST[$this->pk_field];
		else $id_prat=$_GET[$this->pk_field];
		//Recupero lo stato dell'oggetto all'atto della creazione dell'integrazione		
		$sql_wfstato="select ID_STATO from {$this->service}WF_STATO where PK_SERVICE=:id_prat";
		$sql_wf=new query($this->conn);
		$bind['ID_PRAT']=$id_prat;
		$sql_wf->get_row($sql_wfstato,$bind);
		//Controllo che il modulo preveda il campo WF_STATO
		$sql_exists="select * from user_tab_columns where column_name=:col_name and TABLE_NAME=:tab_name";
                $bind['col_name']="WF_STATO";
                $bind['tab_name']="{$this->service}_EQ";
		$sql_ex=new query($this->conn);
		$sql_ex->exec($sql_exists,$bind);
		if($sql_ex->numrows>0)
		$val_th['WF_STATO']=$sql_wf->row['ID_STATO'];
		$sql->insert($val_th,$this->service."_EQ","");
		$this->conn->commit();
		return $this->eq_int;
	}


	/**
	 * Salvataggio equery campo per form $xml_form
	 *
	 */
	function SaveEqInt($xml_form){
		$ret=$this->getEqSpec($this->vlist);
		//Non so cosa fa!!!
		$sql_check="select distinct eqfield.esam,
                eqfield.{$this->pk_field},
                eq.equery_int,
                substr(eq.userid_ins,0,3) as center,
                eq.rich_dm,
                eq.rich_de,
                eq.risp_dm,
                eq.stato,
                eq.ins_dt,
                eqfield.progr,
                eqfield.visitnum,
                eqfield.visitnum_progr
           from {$this->service}_eq eq, {$this->service}_eqfield eqfield
           where eq.equery_int=eqfield.eq_int";
		$sql = new query ( $this->conn ); 
		$sql->exec ( $sql_check );//non richiede binding
		foreach ($xml_form->fields as $key=>$val){
			if ($val['TYPE']=="file_doc" || $val['TYPE']=="file_cme"){
				$keywords=$val['VAR'];
				if ($_POST['PROGR']!=1) $keywords.="_".$_POST['PROGR'];
				//$id_tipo_ref=700000+$this->pk_value;
				$id_tipo_ref=$config_service['PRJ']*100000+$this->pk_value;
				$sql_query="
					select max(id) as C
					from docs
					where id_tipo_ref=:id_tipo_ref
					and keywords=:keywords
					and tipo_doc=:tipo_doc
					and approved is null
					";
                                        $bind['keywords']=$keywords;
                                        $bind['id_tipo_ref']=$id_tipo_ref;
                                        $bind['tipo_doc']="Doc_Area";
                                        
				$sql=new query($this->conn);
				if ($sql->get_row($sql_query,$bind)) {
					if ($sql->row['C']!=''){
						$fields[]=$val['VAR'];
						$values[]=$sql->row['C'];
					}
				}
			}
		}
		//FINO A QUI
		$session=new query($this->conn);
		$session->ins_upd("ALTER SESSION SET NLS_DATE_FORMAT = 'DDMMYYYY'");//bind non necessario

		//Prendo i dati dalla scheda in questione e li salvo in $origina_res
		$sql_query="select * from {$xml_form->form['TABLE']}
			where $this->pk_field={$_POST[$this->pk_field]}
			and esam=:esam
			and progr=:progr
			and visitnum=:visitnum
			and visitnum_progr=:visitnum_progr";
                        $bind['esam']=$_POST['ESAM'];
                        $bind['progr']=$_POST['PROGR'];
                        $bind['visitnum']=$_POST['VISITNUM'];
                        $bind['visitnum_progr']=$_POST['VISITNUM_PROGR'];
                        
		$sql=new query($this->conn);
		$sql->get_row($sql_query, $bind);
		foreach ($sql->row as $key=>$val){
			$original_res[$key]=$val;
		}
		//Ciclo tutti i campi di xml_form
		
		//Logger::send($this->session_vars);
		foreach ($xml_form->fields as $key=>$val){
			if ($val['VAR']!='' && $val['TB']!='no'){
				if (!isset($_POST[$val['VAR']]) || $_POST[$val['VAR']]=='') $_POST[$val['VAR']]=0;
				$field_type = "field_{$val['TYPE']}";
				if (!class_exists($field_type)) {
					if ($this->config_service['field_lib'] != '' && file_exists($this->config_service['field_lib'].$field_type.".inc")) {
						include_once $this->config_service['field_lib'].$field_type.".inc";
					} elseif (file_exists("libs/{$field_type}.inc")) {
						include_once "libs/{$field_type}.inc";
					} else {
						include_once "libs/fields/{$field_type}.inc";
					}
				}
				//Costruisco l'oggetto field relativo
				
				$field_obj = new $field_type ( $xml_form, $xml_form->vars[$val['VAR']], $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $xml_form->errors );
				//Costruisco l'insert_stmt relativo al campo
				$field_obj->insert_stmt();
				foreach ($field_obj->field_stmt as $f=>$fv){
					$fields[]=$fv;
				}
				foreach ($field_obj->value_stmt as $f=>$fv){
					$values[]=$fv;
				}
				
			}
			}
		//Se non presenti integrazioni ne creo una
		if ($this->eq_int=='') {
			$this->createEq();
		}
		//Logger::send($fields);
		//Logger::send($values);
		//Trasformo i 2 array $fields e $values in un array associativo $assocArray
		foreach ($fields as $key=>$val){
			$assocArray[$val]=$values[$key];
		}
		//Prendo i dati da coordinate
		$sql_query="select * from {$this->service}_COORDINATE 
		where {$this->pk_field}=:pk_value
		and esam=:esam
		and visitnum=:visitnum
		and visitnum_progr=:visitnum_progr
		and progr=:progr			
		";
               $bind['esam']=$assocArray['ESAM'];
               $bind['progr']=$assocArray['PROGR'];
               $bind['visitnum']=$assocArray['VISITNUM'];
               $bind['visitnum_progr']=$assocArray['VISITNUM_PROGR'];
               $bind['pk_value']=$assocArray[$this->pk_field];
		//Se non presente in coordinate aggiungo record in coordinate con eq_action=1
		if (!$sql->get_row($sql_query, $bind)){
			//Logger::send("Nuovo inserimento scheda progressiva");
			$insertValuesCoord['INIZIO']=1;
			$insertValuesCoord['FINE']=1;
			$insertValuesCoord['VISITCLOSE']=1;
			$insertValuesCoord['USERID']=$this->userid;
			$insertValuesCoord['INV_QUERY']=$this->eq_int;
			$insertValuesCoord['EQ_ACTION']=1;
			$insertValuesCoord['ABILITATO']=1;
			$insertValuesCoord['INSERTDT']="sysdate";
			$insertValuesCoord['ESAM']=$assocArray['ESAM'];
			$insertValuesCoord['VISITNUM']=$assocArray['VISITNUM'];
			$insertValuesCoord['VISITNUM_PROGR']=$assocArray['VISITNUM_PROGR'];
			$insertValuesCoord['PROGR']=$assocArray['PROGR'];
			$insertValuesCoord[$this->pk_field]=$assocArray[$this->pk_field];
			//Logger::send("Coordinate");
			//Logger::send($insertValuesCoord);
			//Logger::send("{$xml_form->form['TABLE']}");
			//Logger::send($assocArray);
			$pk='';
			$sql->insert($insertValuesCoord, $this->service."_COORDINATE", $pk);
			$sql->insert($assocArray, $xml_form->form['TABLE'], $pk);
			//Per ogni campo inserisco i valori nuovi in EQFIELD
			foreach ($assocArray as $k=>$v){
				if (!isset($pk[$k])){
					$eqFieldAssocArray['ESAM']=$assocArray['ESAM'];
					$eqFieldAssocArray['VISITNUM']=$assocArray['VISITNUM'];
					$eqFieldAssocArray['VISITNUM_PROGR']=$assocArray['VISITNUM_PROGR'];
					$eqFieldAssocArray['PROGR']=$assocArray['PROGR'];
					$eqFieldAssocArray[$this->pk_field]=$assocArray[$this->pk_field];
					$eqFieldAssocArray['FIELD']=$k;
					$eqFieldAssocArray['EQ_INT']=$this->eq_int;
					$eqFieldAssocArray['VALORE']=$v;
					$eqFieldAssocArray['ACTION']=1;
					$sql->insert($eqFieldAssocArray, $this->service."_EQFIELD", $pk);
				}
			}
		} else if ($sql->row['EQ_ACTION']==1 || ($sql->row['INIZIO']!=1 && $sql->row['EQ_ACTION']=='')){
			//Se in coordinate trovo il record con EQ_ACTION=1
			//Logger::send("Modifica scheda inserita durante integrazione");
			$pk['ESAM']=$assocArray['ESAM'];
			$pk['VISITNUM']=$assocArray['VISITNUM'];
			$pk['VISITNUM_PROGR']=$assocArray['VISITNUM_PROGR'];
			$pk['PROGR']=$assocArray['PROGR'];
			$pk[$this->pk_field]=$assocArray[$this->pk_field];
			//inserisco data di modifica
			$insertValuesCoord['MODDT']="sysdate";
			$insertValuesCoord['INIZIO']=1;
			$insertValuesCoord['EQ_ACTION']=1;
			//Logger::send("Coordinate");
			//Logger::send($insertValuesCoord);
			//Logger::send("{$xml_form->form['TABLE']}");
			//Logger::send($assocArray);
			$sql->update($insertValuesCoord, $this->service."_COORDINATE", $pk);
			if ($sql->row['INIZIO']!=1){
				foreach ($pk as $f=>$v){
					$assocArray2[$f]=$v;
				}
				foreach ($assocArray as $f=>$v){
					$assocArray2[$f]=$v;
				}
				$pk2='';
				$sql->insert($assocArray2, $xml_form->form['TABLE'], $pk);
				//Inserisco tutti i campi in eqfield
				foreach ($assocArray as $k=>$v){
					if (!isset($pk[$k])){
						$eqFieldAssocArray['ESAM']=$assocArray['ESAM'];
						$eqFieldAssocArray['VISITNUM']=$assocArray['VISITNUM'];
						$eqFieldAssocArray['VISITNUM_PROGR']=$assocArray['VISITNUM_PROGR'];
						$eqFieldAssocArray['PROGR']=$assocArray['PROGR'];
						$eqFieldAssocArray[$this->pk_field]=$assocArray[$this->pk_field];
						$eqFieldAssocArray['FIELD']=$k;
						$eqFieldAssocArray['EQ_INT']=$this->eq_int;
						$eqFieldAssocArray['VALORE']=$v;
						$eqFieldAssocArray['ACTION']=1;
						$sql->insert($eqFieldAssocArray, $this->service."_EQFIELD", $pk2);
					}
				}
			}else {
				//Se trovo già i campi in eqfield li aggiorno
			$sql->update($assocArray, $xml_form->form['TABLE'], $pk);
			foreach ($assocArray as $k=>$v){
				if (!isset($pk[$k])){
					$eqFieldAssocArray['FIELD']=$k;
					$eqFieldAssocArray['EQ_INT']=$this->eq_int;
					$eqFieldAssocArray['VALORE']=$v;
					$sql->update($eqFieldAssocArray, $this->service."_EQFIELD", $pk);
		}
			}
		}
		} else {
			//Se trovo la scheda in coordinate
			//Logger::send("Modifica scheda già presente");
			//Aggiungo/aggiorno i campi modificati in EQFIELD
		foreach ($fields as $key=>$val){

			
			if ($values[$key]!=$original_res[$val] && !($original_res[$val]=='0' && $values[$key] =='') && !($original_res[$val]=='' && $values[$key] =='0')) {
			$sql_query="select count(*) as c from {$this->service}_eqfield
				where $this->pk_field={$_POST[$this->pk_field]}
				and esam=:esam
				and progr=:progr
				and visitnum=:visitnum
				and visitnum_progr=:visitnum_progr
				and EQ_INT=:eq_int
				and field=:field";
                                $bind['esam']=$_POST['ESAM'];
                                $bind['visitnum']=$_POST['VISITNUM'];
                                $bind['visitnum_progr']=$_POST['VISITNUM_PROGR'];
                                $bind['progr']=$_POST['PROGR'];
                                $bind['eq_int']=$this->eq_int;
                                $bind['field']=$val;
                                $bind['pk_value']=$_POST[$this->pk_field];
			$sql->get_row($sql_query, $bind);
			$vals='';
			$pk='';
			$vals['VALORE']=$values[$key];
			//Discrimino su insert/update
			if ($sql->row['C']=='0'){
				$vals['EQ_INT']=$this->eq_int;
				$vals[$this->pk_field]=$_POST[$this->pk_field];
				$vals['ESAM']=$_POST['ESAM'];
				$vals['VISITNUM']=$_POST['VISITNUM'];
				$vals['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
				$vals['PROGR']=$_POST['PROGR'];
				$vals['FIELD']=$val;
				$sql->insert($vals, $this->service."_EQFIELD",$pk);
			}else {

				$pk['EQ_INT']=$this->eq_int;
				$pk[$this->pk_field]=$_POST[$this->pk_field];
				$pk['ESAM']=$_POST['ESAM'];
				$pk['VISITNUM']=$_POST['VISITNUM'];
				$pk['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
				$pk['PROGR']=$_POST['PROGR'];
				$pk['FIELD']=$val;
				$table=$this->service."_EQFIELD";
				$sql->update($vals, $table,$pk);
			}
			}
		}
		}
		
		$this->conn->commit();
	}

	function ApprovaEq($vlist,$xml_dir, $config_service, $session_vars, $uploaded_file_dir){

		if($config_service['IN_REV'][$this->service]) {
			$sql_query="select ESAM,VISITNUM,VISITNUM_PROGR,PROGR,{$this->pk_field},USERID_INS,INS_DT,STATO_RICH,DURATA_HH,SCADUTA,EQ_INT from {$this->service}_INREV 
                        where {$this->pk_field}=:pk_value";
                        $bind['pk_value']=$this->pk_value;
		$sql=new query($this->conn);
			$sql->exec($sql_query,$bind);
			$i=0;
			if($sql->numrows>0) {
		while ($sql->get_row()){
					if($sql->row['STATO_RICH']==1 && $sql->row['EQ_INT']==$this->eq_int) {
						$values['STATO_RICH']=2;
						$pk['VISITNUM']=$sql->row['VISITNUM'];
						$pk['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
						$pk['ESAM']=$sql->row['ESAM'];
						$pk['PROGR']=$sql->row['PROGR'];
						$pk['ID_PRAT']=$this->pk_value;
						$tb="{$this->service}_INREV";
						$sql_update=new query($this->conn);
						$sql_update->update($values,$tb,$pk);
						$this->conn->commit();
				}
			}
			}
		}
			
		$eq_int=$this->eq_int;
		if($eq_int=="") return;
		
		$sql=new query($this->conn);
		
		//aggiorno le schede nuove
		$sql_update="update {$this->service}_coordinate set INV_QUERY=null, EQ_ACTION=null
		where {$this->pk_field}=:pk_value and eq_action=:eq_action";
                $bind['pk_value']=$this->pk_value;
                $bind['eq_action']=1;
		
		$sql->ins_upd($sql_update,$bind);
		
		//applico le modifiche campo campo
		$sql_query="select distinct visitnum,visitnum_progr,esam,progr from {$this->service}_eqfield
					where eq_int=:eq_int and action=:action
			order by visitnum,visitnum_progr,esam,progr
			";
                $bind['eq_int']=$eq_int;
                $bind['action']=0;
                
		$sql->exec($sql_query,$bind);
		
		while ($sql->get_row()){
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			if($xml=="" && is_array($vlist->esams[$sql->row['VISITNUM']][0])) $xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['XML'];
			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
			
			$wca_docs='';
			foreach ($xml_form->fields as $key=>$val){
				if ($val['TYPE']=="file_doc"  || $val['TYPE']=="file_cme"){
					$wca_docs[$val['VAR']]=true;
				}
			}
			foreach ($xml_form->fields as $key=>$val){
				if ($val['TYPE']=="data"){
					$date_fields[$val['VAR']]=true;
				}
			}
			foreach ($xml_form->fields as $key=>$val){
				if ($val['TYPE']=="checkbox"){
					$checkbox_fields[$val['VAR']]=true;
				}
			}
			$scheda=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			$table=$xml_form->form['TABLE'];
			$sql_storico="insert into S_{$table}
						select '{$this->userid}', sysdate, storico_id.nextval, 'U', :eq_int, o.* from {$table} o
				where
							o.ESAM=:esam
							and o.VISITNUM=:visitnum
							and o.VISITNUM_PROGR=:visitnum_progr
							and o.PROGR=:progr
							and o.{$this->pk_field}=:pk_value
						";
                        $bind['esam']=$sql->row['ESAM'];
                        $bind['visitnum']=$sql->row['VISITNUM'];
                        $bind['visitnum_progr']=$sql->row['VISITNUM_PROGR'];
                        $bind['progr']=$sql->row['PROGR'];
                        $bind['pk_value']=$this->pk_value;
                        $bind['eq_int']=$eq_int;
                        
			$pk[$this->pk_field]=$this->pk_value;
			$pk['ESAM']=$sql->row['ESAM'];
			$pk['VISITNUM']=$sql->row['VISITNUM'];
			$pk['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
			$pk['PROGR']=$sql->row['PROGR'];
			$sql_query_fields="select field, valore from {$this->service}_eqfield
				where
							ESAM=:esam
							and VISITNUM=:visitnum
							and VISITNUM_PROGR=:visitnum_progr
							and PROGR=:progr
							and {$this->pk_field}=:pk_value
							and EQ_INT=:eq_int
				";
			$sql2=new query($this->conn);
			$sql2->exec($sql_query_fields, $bind);
			$values='';
			while ($sql2->get_row()){
				if (!$wca_docs[$sql2->row['FIELD']]) {
					if ($date_fields[$sql2->row['FIELD']]) $values[$sql2->row['FIELD']]="to_date('{$sql2->row['VALORE']}','DDMMYYYY')";
					else $values[$sql2->row['FIELD']]=$sql2->row['VALORE'];
				}
			}
			
			$sql2->ins_upd($sql_storico, $bind);
		
			if (is_array($values)>0){
				$query_check=new query($this->conn);
				$sql_check="select {$this->pk_field} from $table where 
                                {$this->pk_field}=:pk_value 
                                and ESAM=:esam
                                and VISITNUM=:visitnum 
                                and VISITNUM_PROGR=:visitnum_progr 
                                and PROGR=:progr";
                                $bind['esam']=$pk['ESAM'];
                                $bind['visitnum']=$pk['VISITNUM'];
                                $bind['visitnum_progr']=$pk['VISITNUM_PROGR'];
                                $bind['progr']=$pk['PROGR'];
                                $bind['pk_value']=$this->pk_value;
				$query_check->exec($sql_check,$bind);
				$query_check->get_row();
				if($query_check->numrows>0) {
					$sql2->update($values, $table, $pk);
				} else {
					$values[$this->pk_field]=$pk[$this->pk_field];
					$values['ESAM']=$pk['ESAM'];
					$values['VISITNUM']=$pk['VISITNUM'];
					$values['VISITNUM_PROGR']=$pk['VISITNUM_PROGR'];
					$values['PROGR']=$pk['PROGR'];
					$sql2->insert($values, $table, $pk);
				}
			}
		
		}
		
		//Sistemo Docs
		//$id_tipo_ref=700000+$this->pk_value;
		$id_tipo_ref=$config_service['PRJ']*100000+$this->pk_value;
		$sql_update_wca="
				update docs set approved=:approved, approv_dt=sysdate, approv_comm=:approv_comm 
				WHERE 
					id_tipo_ref=:id_tipo_ref
					and approved is null
					and tipo_doc=:tipo_doc
					and 
					id IN
					  (SELECT MAX(id)
					  FROM docs
					  WHERE id_tipo_ref=:id_tipo_ref
					  AND keywords    IN
					    (SELECT
					      CASE
					        WHEN visitnum_progr=:visitnum_progr
					        AND progr          =:progr
					        THEN field
					        WHEN visitnum_progr=:visitnum_progr
					        AND progr          >:progr
					        THEN field
					          ||'_'
					          ||progr
					        ELSE field
					          ||'_'
					          ||progr
					          ||'_'
					          ||visitnum_progr
					      END AS field
					    FROM {$this->service}_eqfield
					    WHERE {$this->pk_field}=:pk_value
					    AND eq_int   =:eq_int
					    AND action  <>:action
					    )
					    group by keywords
					  )
				";
                                            $bind['approved']=1;
                                            $bind['approv_dt']="sysdate";
                                            $bind['approv_comm']="Integrazione n.ro $eq_int";
                                            $bind['tipo_doc']="Doc_Area";
                                            $bind['id_tipo_ref']=$id_tipo_ref;
                                            $bind['visitnum_progr']=0;
                                            $bind['progr']=1;
                                            $bind['pk_value']=$this->pk_value;
                                            $bind['eq_int']=$this->eq_int;
                                            $bind['action']=2;
		$sql_update_wca_2="
						
						update docs set tipo_doc=:tipo_doc_
						WHERE 
							id_tipo_ref=:id_tipo_ref
							and approved is null
							and tipo_doc=:tipo_doc
							  AND keywords    IN
							    (SELECT
							      CASE
							        WHEN visitnum_progr=:visitnum_progr
							        AND progr          =:progr
							        THEN field
							        WHEN visitnum_progr=:visitnum_progr
							        AND progr          >:progr
							        THEN field
							          ||'_'
							          ||progr
							        ELSE field
							          ||'_'
							          ||progr
							          ||'_'
							          ||visitnum_progr
							      END AS field
							    FROM {$this->service}_eqfield
							    WHERE {$this->pk_field}=:pk_value
							    AND eq_int   =:eq_int
							    AND action  <>:action
							    )
						";
                                            
                                            $bind['tipo_doc_']="Trash";
                                            
		$sql->ins_upd($sql_update_wca,$bind);
		$sql->ins_upd($sql_update_wca_2,$bind);
		//Logger::send($sql_update_wca);
		//Logger::send($sql_update_wca_2);
		//Controllo schede da eliminare
		$bind['eq_action']=2;
		$sql_to_be_deleted="
			select
				esam, progr, visitnum, visitnum_progr
			from {$this->service}_coordinate
			where {$this->pk_field}=:pk_value
			and eq_action=:eq_action
		";
		$sql=new query($this->conn);
		$sql->exec($sql_to_be_deleted, $bind);
		//Logger::send($session_vars);
		while ($sql->get_row()){
			//Logger::send("Esame da eliminare:");
			//Logger::send($sql->row);
			
			if (class_exists("Study_{$config_service['service']}")){
				$class_name="Study_{$config_service['service']}";
					}
			else $class_name="Study";
			//Logger::send($class_name);
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			call_user_func("{$class_name}::SDeleteProgrEsam",$this->conn, $config_service,$session_vars,$xml_dir,$xml, $session_vars['remote_userid'], $this->pk_value, $sql->row['ESAM'], $sql->row['PROGR'], $sql->row['VISITNUM'], $sql->row['VISITNUM_PROGR']);
		}

		
		/*
		
		$sql_query="select distinct visitnum,visitnum_progr,esam from {$this->service}_coordinate
			where {$this->pk_field}={$this->pk_value} and visitnum in (0,1,2)
			order by visitnum,visitnum_progr,esam
			";
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			if (!isset($vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])) continue;
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
			$wca_docs='';
			foreach ($xml_form->fields as $key=>$val){
				if ($val['TYPE']=="file_doc"  || $val['TYPE']=="file_cme"){
					$wca_docs[$val['VAR']]=true;
				}
			}
			$sql_check="
				select count(*) as n_schede, max(progr) as max_progr
				from {$this->service}_coordinate
				where {$this->pk_field}={$this->pk_value}
				and esam={$sql->row['ESAM']}
				and visitnum={$sql->row['VISITNUM']}
				and visitnum_progr={$sql->row['VISITNUM_PROGR']}
				";
			$sql2=new query($this->conn);
			$sql2->get_row($sql_check);
			$sql2->row['MAX_PROGR']-=0;
			if ($sql2->row['MAX_PROGR']!=$sql2->row['N_SCHEDE']){
				$last_progr=$sql2->row['MAX_PROGR'];
				$trovato=false;
				while (!$trovato){
					$sql_check2="
		  				select count(*) as conto
		  				from {$this->service}_coordinate
		  				where
		  				esam={$sql->row['ESAM']}
						and visitnum={$sql->row['VISITNUM']}
						and visitnum_progr={$sql->row['VISITNUM_PROGR']}
		  				and progr=$last_progr-1
		  				and {$this->pk_field}={$this->pk_value}";
					$sql2->get_row($sql_check2);
					if ($sql2->row['CONTO']==0){
						$trovato=true;
						$sql3=new query($this->conn);
						$progr=$last_progr-1;
						$sql_insert="
						  	select *
						  	from {$this->service}_COORDINATE
						  	where
		  					esam={$sql->row['ESAM']}
							and visitnum={$sql->row['VISITNUM']}
							and visitnum_progr={$sql->row['VISITNUM_PROGR']}
						  	and progr=$progr+1
						  	and {$this->pk_field}={$this->pk_value}";
						$tb="{$this->service}_COORDINATE";
						$pk='';
						$sql3->get_row($sql_insert);
						$sql3->row['PROGR']-=1;
						$sql3->insert($sql3->row, $tb, $pk);
						foreach ($wca_docs as $key => $val){
							$orig_progr=$progr+1;
							$_orig_key="{$key}_{$orig_progr}";
							if ($progr>1) $_dest_key="{$key}_$progr";
							else $_dest_key=$key;
							$id_tipo_ref=700000+$this->pk_value;
							$sql_update="
								update docs set keywords='$_dest_key' where id_tipo_ref=$id_tipo_ref and keywords='$_orig_key'";
							$sql3=new query($this->conn);
							$sql3->set_sql($sql_update);
							$sql3->ins_upd();
						}
						$sql_update="
						  	update {$xml_form->form['TABLE']}
						  	set progr=progr-1
						  	where
						  	esam={$sql->row['ESAM']}
							and visitnum={$sql->row['VISITNUM']}
							and visitnum_progr={$sql->row['VISITNUM_PROGR']}
						  	and progr=$progr+1
						  	and {$this->pk_field}={$this->pk_value}";

						$sql3->set_sql($sql_update);
						$sql3->ins_upd();
						$sql_delete="
						  	delete from {$this->service}_COORDINATE
						  	where
						  	esam={$sql->row['ESAM']}
							and visitnum={$sql->row['VISITNUM']}
							and visitnum_progr={$sql->row['VISITNUM_PROGR']}
						  	and progr=$progr+1
						  	and {$this->pk_field}={$this->pk_value}";
						$sql3->set_sql($sql_delete);
						$sql3->ins_upd();
						//$this->conn->commit();
					}else $last_progr-=1;
				}
			}
		}
		$this->conn->commit();
		*/
		$values='';
		$pk='';
		$values['STATO']=1;
		$values['CLOSE_DT']="sysdate";
		$pk['EQUERY_INT']=$this->eq_int;
		$pk[$this->pk_field]=$this->pk_value;
		$table=$this->service."_EQ";
		$sql->update($values, $table, $pk);
		$this->conn->commit();

	}


	function getEqSpec($vlist,$userid=null){
		if($this->eq_int=="") return false;
		
		if(isset($_POST['ESAM'])){
				$where="and esam={$_POST['ESAM']}";
			}
		$sql_query="select distinct visitnum,visitnum_progr,esam,progr, action from {$this->service}_eqfield
			where eq_int=:eq_int $where
			order by visitnum,visitnum_progr,esam,progr
			";
                        $bind['eq_int']=$this->eq_int;
		$sql=new query($this->conn);
		$sql->exec($sql_query,$bind);
		while ($sql->get_row()){
			$scheda[]=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			$spec[]=0;
			$spec_pk[]['VISITNUM']=$sql->row['VISITNUM'];
			$spec_pk[count($spec_pk)-1]['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
			$spec_pk[count($spec_pk)-1]['PROGR']=$sql->row['PROGR'];
			$spec_pk[count($spec_pk)-1]['ESAM']=$sql->row['ESAM'];
			$spec_pk[count($spec_pk)-1]['ACTION']=$sql->row['ACTION'];
			$d_spec[]=$this->d_stati($sql->row['ACTION']);
		}
		foreach ($scheda as $key=>$val){
			$ret[$key]['SCHEDA']=$scheda[$key];
			$ret[$key]['PK']=$spec_pk[$key];
			$ret[$key]['MODIFICA']=$d_spec[$key];
			$ret[$key]['CODE']=$spec[$key];
		}

		return $ret;
	}

	function d_stati($key){
		$d_spec[0]="modificata";
		$d_spec[1]="aggiunta";
		$d_spec[2]="eliminata";
		return $d_spec[$key];
	}

	function respingiEq($vlist,$xml_dir,$config_service, $session_vars, $uploaded_file_dir, $commento){
		
		if($config_service['IN_REV'][$this->service]) {
			$sql_query="select ESAM,VISITNUM,VISITNUM_PROGR,PROGR,{$this->pk_field},USERID_INS,INS_DT,STATO_RICH,DURATA_HH from {$this->service}_INREV 
                        where {$this->pk_field}=:pk_value";
                        $bind['pk_value']=$this->pk_value;
			$sql=new query($this->conn);
			$sql->exec($sql_query,$bind);
			$i=0;
			if($sql->numrows>0) {
				while($sql->get_row()) {
					if($sql->row['STATO_RICH']==1) {
						$values['STATO_RICH']=3;
						$pk['VISITNUM']=$sql->row['VISITNUM'];
						$pk['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
						$pk['ESAM']=$sql->row['ESAM'];
						$pk['PROGR']=$sql->row['PROGR'];
						$pk['ID_PRAT']=$this->pk_value;
						$tb="{$this->service}_INREV";
						$sql_update=new query($this->conn);
						$sql_update->update($values,$tb,$pk);
						$this->conn->commit();
					}
				}
			}
		}
		
		$eq_int=$this->eq_int;
		//$id_tipo_ref = 700000 + $this->pk_value;
		$id_tipo_ref=$config_service['PRJ']*100000+$this->pk_value;

		$sql=new query($this->conn);
		//Inserisco nello storico la scheda di cui si erea chiesta la modifica
		$sql_query="select distinct visitnum,visitnum_progr,esam,progr from {$this->service}_eqfield
							where eq_int=:eq_int and action=:action
							order by visitnum,visitnum_progr,esam,progr
		";
                $bind['eq_int']=$eq_int;
                $bind['action']=0;
		$sql->exec($sql_query,$bind);
		
		while ($sql->get_row()){
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			if($xml=="" && is_array($vlist->esams[$sql->row['VISITNUM']][0])) $xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['XML'];
			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
			$table=$xml_form->form['TABLE'];
			$sql_storico="insert into S_{$table}
								select '{$this->userid}', sysdate, storico_id.nextval, 'U', $eq_int, o.* from {$table} o
				where
					o.ESAM=:esam
					and o.VISITNUM=:visitnum
					and o.VISITNUM_PROGR=:visitnum_progr
					and o.PROGR=:progr
					and o.{$this->pk_field}=:pk_value
				";
                                        $bind['esam']=$sql->row['ESAM'];
                                        $bind['visitnum']=$sql->row['VISITNUM'];
                                        $bind['visitnum_progr']=$sql->row['VISITNUM_PROGR'];
                                        $bind['progr']=$sql->row['PROGR'];
                                        $bind['pk_value']=$this->pk_value;
                                        
			$sql2=new query($this->conn);
			$sql2->ins_upd($sql_storico,$bind);
		}
		
		 		
		/*pulisco documenti*/

		$sql_update_wca="update docs set approved=0, approv_dt=sysdate, approv_comm='Integrazione {$this->eq_int} rifiutata' 
		where approved is null and id in (select max(id) from docs where id_tipo_ref=$id_tipo_ref  and keywords in (
		select 
		case 
			when visitnum_progr=0 and progr=1 then field
			when visitnum_progr=0 and progr>1 then field||'_'||progr
			else field||'_'||progr||'_'||visitnum_progr
		end as field from {$this->service}_eqfield 
		where {$this->pk_field}=:pk_value and eq_int=:eq_int
		)
		)";
                $bind['eq_int']=$this->eq_int;
                $bind['pk_value']=$this->pk_value;
		$sql=new query($this->conn);
		
		$sql->ins_upd($sql_update_wca,$bind);
		
		
		$sql_update="update docs set tipo_doc='Trash' where id_tipo_ref=$id_tipo_ref and approved is null and keywords in (
		select 
		case 
			when visitnum_progr=0 and progr=1 then field
			when visitnum_progr=0 and progr>1 then field||'_'||progr
			else field||'_'||progr||'_'||visitnum_progr
		end as field from {$this->service}_eqfield
                where {$this->pk_field}=:pk_value and eq_int=:eq_int)
		";
		$sql3=new query($this->conn);
		
		$sql3->ins_upd($sql_update,$bind);
		
		//Controllo schede da eliminare
		$sql_to_be_deleted="
							select
								esam, progr, visitnum, visitnum_progr
							from {$this->service}_coordinate
							where {$this->pk_field}=:pk_value
							and eq_action=1
						";
		$sql=new query($this->conn);
		$sql->exec($sql_to_be_deleted,$bind);
		//Logger::send($session_vars);
		while ($sql->get_row()){
			//Logger::send("Esame da eliminare:");
			//Logger::send($sql->row);
		
			if (class_exists("Study_{$config_service['service']}")){
				$class_name="Study_{$config_service['service']}";
			}
			else $class_name="Study";
			//Logger::send($class_name);
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			call_user_func("{$class_name}::SDeleteProgrEsam",$this->conn, $config_service,$session_vars,$xml_dir,$xml, $session_vars['remote_userid'], $this->pk_value, $sql->row['ESAM'], $sql->row['PROGR'], $sql->row['VISITNUM'], $sql->row['VISITNUM_PROGR']);
		}
		$sql_update_coordinate="update {$this->service}_coordinate set EQ_ACTION=null, inv_query=null where EQ_ACTION=2 and {$this->pk_field}={$this->pk_value}";
		$sql->ins_upd($sql_update_coordinate);
		
		$this->conn->commit();

		/*****/


		$sql_to_be_deleted="
			delete
			from {$this->service}_coordinate
			where {$this->pk_field}=:pk_value
			and inv_query=:eq_int
			and eq_action=1
		";
		$sql=new query($this->conn);
		
		$sql->ins_upd($sql_update, $bind);
		$this->conn->commit();

		$values='';
		$pk='';
		$values['INV_QUERY']="null";
		$values['EQ_ACTION']="null";
		$pk['INV_QUERY']="null";
		$pk['EQ_ACTION']="2";
		$pk[$this->pk_field]=$this->pk_value;
		$table=$this->service."_coordinate";
		$sql=new query($this->conn);
		$sql->update($values, $table, $pk);
		$this->conn->commit();

		$sql=new query($this->conn);
		$values='';
		$pk='';
		$values['STATO']=3;
		$values['RISP_DM']=$commento;
		$values['CLOSE_DT']="sysdate";
		$pk['EQUERY_INT']=$this->eq_int;
		$pk[$this->pk_field]=$this->pk_value;
		$table=$this->service."_EQ";
		$sql->update($values, $table, $pk);
		$this->conn->commit();
	}

	function inviaPerApprovazione(){
		//setta lo stato a 2 e sposta la decisione di approvazione all'AIFA (parametro in config.inc))
		$values['STATO']=2;
		$pk['EQUERY_INT']=$this->eq_int;
		$pk[$this->pk_field]=$this->pk_value;
		$sql=new query($this->conn);
		$sql->update($values, $this->service."_EQ", $pk);
		$this->conn->commit();

	}
	
	function getActiveEqVisitnum() {
		$this->getActiveEq();
		if($this->eq_int!="") {
			$query="select distinct visitnum from {$this->service}_EQFIELD 
                        where eq_int = :eq_int and {$this->pk_field}=:pk_value
			union
			select distinct VISITNUM from {$this->service}_coordinate 
                        where {$this->pk_field}=:pk_value and EQ_ACTION is not null
			";
                        $bind['eq_int']=$this->eq_int;
                        $bind['pk_value']=$_GET[$this->pk_field];
//			echo $query;
			$sql=new query($this->conn);
			$sql->exec($query,$bind);
			$vnum=array();
			while($sql->get_row()) {
				$vnum[]=$sql->row['VISITNUM'];
	}

		}
//		print_r($vnum);
		return $vnum;
	}

}

class form_int_prototype extends xml_form_prototype {

	
	function make_html($no_link_back=false, $closed=false,$force_open=false,$exclude_send_buttons=false) {
		
		$in = $this->session_vars;
		$inputval = $this->tb_vals;
		$remote_userid = $in ['remote_userid'];
		
		$sblocca = false;
		if ($this->config_service['eQuerySpec']['Integrazione']['KEEP_OPEN'][$in['VISITNUM']][$in['ESAM']]){
			$sblocca = true;
		}

//		$in ['USER_TIP']='RO';
		
		$sql_query="select inizio,fine, userid, visitclose from {$this->config_service['service']}_coordinate 
                where {$this->PK_SERVICE}=:pk_service
                and esam=:esam 
                and progr=:progr
                and visitnum=:visitnum 
                and visitnum_progr=:visitnum_progr";
                $bind['esam']=$in['ESAM'];
                $bind['visitnum']=$in['VISITNUM'];
                $bind['visitnum_progr']=$in['VISITNUM_PROGR'];
                $bind['progr']=$in['PROGR'];
                $bind['pk_service']=$in[$this->PK_SERVICE];
//		echo $sql_query;
		$sql=new query($this->conn);
		$sql->get_row($sql_query,$bind);
		
		
		if(is_numeric($in[$this->PK_SERVICE]) && $in[$this->PK_SERVICE]!="") {
			$sql_query="SELECT ID_STATO FROM {$this->config_service['service']}WF_STATO 
                        WHERE PK_SERVICE=:pk_service";
                        $bind['pk_service']=$in[$this->PK_SERVICE];
//			echo $sql_query;
			$sql_stato=new query($this->conn);
			$sql_stato->get_row($sql_query,$bind);
			$stato_prat=$sql_stato->row['ID_STATO'];
		}
//echo $this->session_vars['WFact'];
//echo "<br />";
//echo $this->config_service['eQuerySpec']['Integrazione']['ROLE'][$this->service];
//echo "<br />";

		if ($sql->row['FINE']==1) $this->closed=true;
		if ($sql->row['USERID']==$remote_userid && $sql->row['FINE']!='1' && $sql->row['VISITCLOSE']!='1') $in['USER_TIP']='DE';
		else if(!$sblocca && $sql->row['USERID']!="" && $this->config_service['eQuerySpec']['Integrazione']['ROLE']!=$this->session_vars['WFact']) {
			$in['USER_TIP']='RO';
			$force_open=false;
//			$closed=true;
		}

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

		if ($this->config_service['eQuery']==1){
			$integrazione=new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['WFact'], $this->session_vars ['USER_TIP']);
		}
		if ($_GET['VISITNUM_PROGR']=='') {
			$_GET['VISITNUM_PROGR']=0;
			$this->session_vars['VISITNUM_PROGR']=0;
		}

		$this->closed_form();

		if($this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$this->config_service['service']][$_GET['VISITNUM']]!="")
			$exclude_visit=$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$this->config_service['service']][$_GET['VISITNUM']];
		else
			$exclude_visit=$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$_GET['VISITNUM']];


		if ($integrazione->eq_enabled && !isset($exclude_visit)	&& !isset($this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_ESAM'][$_GET['ESAM']])
		){
			//$integrazione=new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['WFact'], $this->session_vars ['USER_TIP']);
			if ($integrazione->role==$integrazione->profilo) {
				
				if ($integrazione->eq_enabled && !($integrazione->eq_int!='' && $integrazione->stato==2)){
					//echo $integrazione->stato;
					if ($integrazione->eq_int!=''){
						//echo $integrazione->role." ".$integrazione->profilo;
						
						if($_GET['PROGR']=="") $progr=1;
						else $progr=$_GET['PROGR'];
						
						$sql_query="select EQ_ACTION from {$this->service}_COORDINATE
						where INV_QUERY=:eq_int
						and esam=:esam
						and progr=:progr
						and VISITNUM=:visitnum
						and VISITNUM_PROGR=:visitnum_progr
						and {$this->config_service['PK_SERVICE']}=:pk_service
						";
                                                $bind['eq_int']=$integrazione->eq_int;
                                                $bind['esam']=$_GET['ESAM'];
                                                $bind['progr']=$progr;
                                                $bind['visitnum']=$_GET['VISITNUM'];
                                                $bind['visitnum_progr']=$_GET['VISITNUM_PROGR'];
                                                $bind['pk_service']=$_GET[$this->config_service['PK_SERVICE']];
						$sql=new query($this->conn);
						$sql->get_row($sql_query,$bind);
						$eq_action=$sql->row['EQ_ACTION'];
					
						if ($eq_action==1){
							$this->open_form ();
							return;
						} else {
							$this->open_form(true, null, true);
							return;
						}
					} else {
						$this->open_form(true, null, true);
						return;
					}
				} else {
					$this->close_form(false,true);
					return;
				}
			}

			if ($integrazione->approv_role==$integrazione->profilo || $integrazione->approv_role[$stato_prat]==$integrazione->profilo){
				if($confs=='eq' || $confs!='' /*non è ancora premuto su protocolla e invia per le tipo I*/ )
				//EDO aggiungo questo con equery false quando non acora l'azienda ha terinato di inviare la pratica
				$this->close_form(false,false);
				else
				//approvazione integrazioni
				$this->close_form(false,true);
			} else {
				//questo else serve per vedere le schede azienda da parte di aifa anche da un profilo sbagliato, naturally le vede chiuse
				$this->close_form();
			}
			//ATTENZIONE ATENZIONE
			//levato questo 24/11/10 perché non ,i visualizzava da aifa le schede azienda			
			//return;
//			if(($in['USER_TIP']!='DE' && $this->session_vars['USER_TIP']!='DE') /*|| $in['USER_TIP']=='RO'*/)
//			return;
		} else {
			
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
				$this->open_form ();
			}
		if ($in ['USER_TIP'] == 'RO') {
				$this->closed_form ();
				$this->close_form ($no_link_back);
			}
		}

//		return parent::make_html($no_link_back, $closed, $force_open, $exclude_send_buttons);
	}
	
	
}



?>