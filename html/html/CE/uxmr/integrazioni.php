<?php

define("AREA_OFFSET", 10000000);

class integrazioni extends integrazioni_prototype {

	
	var $non_appr_condition;
	var $inrev_esam;
	var $inrev_visitnum;
	var $stato;
	var $stato_obj;

//	function __construct($config_param, $conn, $userid, $profilo, $xmr_tip){
//		$this->pk_field=$config_param['PK_SERVICE'];
//
//		//ROLE
//		if(is_array($config_param['eQuerySpec']['Integrazione']['ROLE']))
//			$this->role=$config_param['eQuerySpec']['Integrazione']['ROLE'][$config_param['service']];
//		else
//			$this->role=$config_param['eQuerySpec']['Integrazione']['ROLE'];
//		//VALIDATOR
//		if(is_array($config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']]))
//			$this->approv_role=$config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']];
//		else
//			$this->approv_role=$config_param['eQuerySpec']['Integrazione']['VALIDATOR'];
//
//		//NON_APPROV
//		if(is_array($config_param['eQuerySpec']['Integrazione']['NON_APPROV'][$config_param['service']]))
//			$this->non_appr_states=$config_param['eQuerySpec']['Integrazione']['NON_APPROV'][$config_param['service']];
//		else
//			$this->non_appr_states=$config_param['eQuerySpec']['Integrazione']['NON_APPROV'];
//
//		//NON_APPROV_QUERY
//		if(is_array($config_param['eQuerySpec']['Integrazione']['NON_APPROV_CONDITION'][$config_param['service']]))
//			$this->non_appr_condition=$config_param['eQuerySpec']['Integrazione']['NON_APPROV_CONDITION'][$config_param['service']];
//
//		//APPROV
//		if(is_array($config_param['eQuerySpec']['Integrazione']['APPROV'][$config_param['service']]))
//			$this->appr_states=$config_param['eQuerySpec']['Integrazione']['APPROV'][$config_param['service']];
//		else
//			$this->appr_states=$config_param['eQuerySpec']['Integrazione']['APPROV'];
//			
//		//INREV esam
//		if(is_array($config_param['eQuerySpec']['Integrazione']['INREV_ESAM'][$config_param['service']]))
//			$this->inrev_esam=$config_param['eQuerySpec']['Integrazione']['INREV_ESAM'][$config_param['service']];
//		else
//			$this->inrev_esam=$config_param['eQuerySpec']['Integrazione']['INREV_ESAM'];
//		//INREV visitnum
//		if(is_array($config_param['eQuerySpec']['Integrazione']['INREV_VISITNUM'][$config_param['service']]))
//			$this->inrev_visitnum=$config_param['eQuerySpec']['Integrazione']['INREV_VISITNUM'][$config_param['service']];
//		else
//			$this->inrev_visitnum=$config_param['eQuerySpec']['Integrazione']['INREV_VISITNUM'];
//
//		$this->conn=$conn;
//		if (isset($_POST[$this->pk_field])) $this->pk_value=$_POST[$this->pk_field];
//		else $this->pk_value=$_GET[$this->pk_field];
//		$this->service=$config_param['service'];
//		$this->userid=$userid;
//		$this->profilo=$profilo;
//		$this->stato=$this->getStato();
//		$this->stato_obj=$this->getStatoObj();
//		$this->xmr_tip=$xmr_tip;
//		$this->eq_enabled=$this->isEnabled($profilo, $config_param);
//
//		//DEBUG
////		if($this->eq_enabled)
////		echo "eq enabled yes<br>";
////		else
////		echo "eq enabled NO<br>";
//		//DEBUG
//
//		if ($this->eq_enabled){
//			$this->getEqs();
//			$this->getActiveEq();
//		}
////print_r($this);
//	}
	
//	function getStatoObj(){
////		if($this->pk_value!='next' || $this->pk_value!='' || $this->pk_value!=null) {
//		if(is_numeric($this->pk_value)) {
//			$sql_query="select id_stato from {$this->service}WF_STATO where	PK_SERVICE={$this->pk_value}";
//	//		echo $sql_query;
//			$sql=new query($this->conn);
//			$sql->get_row($sql_query);
//			if($sql->numrows==0) return 1;
//			else return $sql->row['ID_STATO'];
//		}
//		
//	}
	
	function isEnabled($profilo, $config_param){
		//echo "CHECK {$this->service}:";
		$query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_EQ')";
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		$query->get_row ();
		if($query->numrows==0){
			//echo "QUA";
			return false;
		}
		/*
		 * Leghiamo questa funzione agli stati in cui ? possibile
		 * richiedere integrazioni (parametro definito nel config)
		 * ed al fatto che non ci siano integrazioni in fase di approvazione
		 * sulla stessa pratica (parametrizzabile)
		 */
		//if(count($config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']])>100)
		//		print_r($config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']]);
		//		if(count($config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']])>1 && !in_array($profilo, $config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']])) {
		//			return true;
		//		}
//		echo "<br><br><br>Role: {$this->role} Profilo: $profilo <br><br><br><br> xmr_tip {$this->xmr_tip} (deve essere de <br>) e not Approv role {$this->approv_role[$this->stato_prat]} <br > ";

		if ($config_param['eQuery']!=1) return false;
		
		//condizione riguardante l'azienda e al rpatica in compilazione
		if($this->inEmeApprovazione() && $this->role==$profilo){
			//echo "QUI";
			return false;
		}
		

		if (($this->role!=$profilo && $this->xmr_tip=='DE') && !($this->approv_role==$profilo || $this->approv_role[$this->stato_prat]==$profilo )) {
			return false;
			//echo "FALSO";
		}
		//global $study_;
		//print_r($study_);
		//print_r($this,true);
		//die("calippo");
		return $this->inEmendamento();
	}
	
	function inEmendamento(){
		//print_r($this);
		$array['ID_STUD'] =  $this->pk_value;
		if (!is_numeric($array['ID_STUD'])){
			return false;
		}
		$sql = "select IN_EMENDAMENTO from {$this->service}_REGISTRAZIONE where {$this->pk_field}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		if ($query->get_row()){
			return ($query->row['IN_EMENDAMENTO'] == 1);
		}else{
			return false;
		}
	}
	function inEmeApprovazione(){
		//print_r($this);
		$array['ID_VAL'] =  $this->pk_value;
		if (!is_numeric($array['ID_VAL'])){
			return false;
		}
		$sql = "select IN_EMENDAMENTO_APPROVAZIONE from {$this->service}_REGISTRAZIONE where {$this->pk_field}=:id_val and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		if ($query->get_row()){
			return ($query->row['IN_EMENDAMENTO_APPROVAZIONE'] == 1);
		}else{
			return false;
		}
	}
	
	function getEqs(){
		//if ($this->eq_int=='') return null;
		$sql_query="select equery_int from {$this->service}_EQ where
		userid_ins='{$this->userid}'
		and {$this->pk_field}={$this->pk_value}
		";
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			$this->eqs[]=$sql->row['EQUERY_INT'];
		}
	}
	function getActiveEq(){
		//if ($this->eq_int=='') return null;
		if($this->role==$this->profilo)
		$sql_query="select equery_int, stato from {$this->service}_EQ where
		userid_ins='{$this->userid}'
		and {$this->pk_field}={$this->pk_value}
		and stato in (0,2)
		";
		else
		$sql_query="select equery_int, stato from {$this->service}_EQ where
		 {$this->pk_field}={$this->pk_value}
		and stato = 2
		";
		$sql=new query($this->conn);
		//echo $sql_query;
		$sql->get_row($sql_query);
		//print_r($sql->row);
		$this->eq_int=$sql->row['EQUERY_INT'];
		//echo "<br/>EQ_INT: {$this->eq_int}<br/>";
		$this->stato=$sql->row['STATO'];
		//aggiungere controlli di sicurezza
		/*
		if($_POST['EQ_INT']==''){
			$this->eq_int=$_POST['EQ_INT'];

		}
		*/
	}
	
	function inviaPerApprovazione(){
		//setta lo stato a 2 e rendi approvabile
		$values['STATO']=2;
		$pk['EQUERY_INT']=$this->eq_int;
		$pk[$this->pk_field]=$this->pk_value;
		$sql=new query($this->conn);
		$sql->update($values, $this->service."_EQ", $pk);
		//$this->conn->commit();
	}
	
	function stornaPerIntegrazione(){
		//setto STATO a 0 e rendi modificabile
		$values['STATO']=0;
		$pk['EQUERY_INT']=$this->eq_int;
		$pk[$this->pk_field]=$this->pk_value;
		$sql=new query($this->conn);
		$sql->update($values, $this->service."_EQ", $pk);
		
		//setto IN_EMENDAMENTO_APPROVAZIONE a 0 e rendi modificabile (sia per istruttoria negativa che per parere sospensivo)
		$values_1['IN_EMENDAMENTO_APPROVAZIONE']=0;
		//$pk['EQUERY_INT']=$this->eq_int;
		$pk_1[$this->pk_field]=$this->pk_value;
		$sql_1=new query($this->conn);
		$sql_1->update($values_1, $this->service."_REGISTRAZIONE", $pk_1);

	}

	
	
//	function ApprovaEq($vlist,$xml_dir, $config_service, $session_vars, $uploaded_file_dir){
//		if ($this->eq_int == ''){
//			return;
//		}
//		$eq_int=$this->eq_int;
//		$id_area = 1;
//		//$id_area = $this->pk_value + (AREA_OFFSET*$id_area);
//		$id_tipo_ref = $this->pk_value + (AREA_OFFSET*$id_area);
//		//echo "ID_TIPO_REF: $id_tipo_ref<br/>";
//		
//		//////--ELIMINAZIONE--//////
//		//Controllo schede da eliminare
//		$sql_to_be_deleted="
//			select
//				esam, progr, visitnum, visitnum_progr
//			from {$this->service}_coordinate
//			where {$this->pk_field}={$this->pk_value}
//			and eq_action=2
//		";
//		$sql=new query($this->conn);
//		$sql->exec($sql_to_be_deleted);
//		while ($sql->get_row()){
//			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
//			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
//			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
//			$wca_docs='';
//			foreach ($xml_form->fields as $key=>$val){
//				if ($val['TYPE']=="file_doc"){
//					$wca_docs[$val['VAR']]=true;
//				}
//			}
//			foreach ($wca_docs as $key => $val){
//				$key = "{$key}_{$sql->row['VISITNUM_PROGR']}";
//				if ($sql->row['PROGR']!=1) $key="{$key}_{$sql->row['PROGR']}";
//				//$id_tipo_ref=700000+$this->pk_value;
//				$sql_update="update docs set tipo_doc='Trash' where id_tipo_ref=$id_tipo_ref and keywords='$key'";
//				$sql3=new query($this->conn);
//				$sql3->set_sql($sql_update);
//				$sql3->ins_upd();
//			}
//			$scheda=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
//			$table=$xml_form->form['TABLE'];
//			$sql_storico="insert into S_{$table}
//				select '{$this->userid}', sysdate, storico_id.nextval, 'D', $eq_int, o.* from {$table} o
//				where
//					o.ESAM={$sql->row['ESAM']}
//					and o.VISITNUM={$sql->row['VISITNUM']}
//					and o.VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
//					and o.PROGR={$sql->row['PROGR']}
//					and o.{$this->pk_field}={$this->pk_value}
//				";
//			$sql2=new query($this->conn);
//			$sql2->set_sql($sql_storico);
//			$sql2->ins_upd();
//		}
//		//elimino le schede
//		$sql_delete="delete from {$this->service}_coordinate where
//		{$this->pk_field}={$this->pk_value} and eq_action=2";
//		$sql=new query($this->conn);
//		$sql->set_sql($sql_delete);
//		$sql->ins_upd();
//		
//		//////--INSERIMENTO--//////
//		//aggiorno le schede nuove
//		$sql=new query($this->conn);
//		$sqlq = "select * from {$this->service}_coordinate where {$this->pk_field}={$this->pk_value} AND EQ_ACTION=1"; //and INV_QUERY = $eq_int 
//		$sql->exec($sqlq);
//		$toadd = array();
//		//$i = 0;
//		global $study_;
//		while ($sql->get_row()){
//			//$toadd[$i]['VISITNUM'] = $sql->row['VISITNUM'];
//			//$toadd[$i]['VISITNUM_PROGR'] = $sql->row['VISITNUM_PROGR'];
//			//$toadd[$i]['ESAM'] = $sql->row['ESAM'];
//			//$toadd[$i]['PROGR'] = $sql->row['PROGR'];
//			//$i++;
//			$toadd[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']][$sql->row['PROGR']] = true;
//			////////NO!//$study_->openEsamProgr($pkid,$vid,$vprogr,$esam,$progr,true, false);
//		}
//		//foreach ($toadd)
//		
//		$sql=new query($this->conn);
//		$sql_update="update {$this->service}_coordinate set INV_QUERY=null, EQ_ACTION=null
//		where {$this->pk_field}={$this->pk_value} and eq_action=1";
//		$sql->set_sql($sql_update);
//		$sql->ins_upd();
//		//Devo aggiungere la riga nella tabella per poi essere compatibile con il caso sotto.
//		
//		//////--MODIFICA/INSERIMENTO--//////
//		//applico le modifiche campo campo
//		$sql_query="select distinct visitnum,visitnum_progr,esam,progr from {$this->service}_eqfield
//			where eq_int=$eq_int
//			order by visitnum,visitnum_progr,esam,progr
//			";
//		$sql=new query($this->conn);
//		$sql->exec($sql_query);
//		while ($sql->get_row()){
//			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
//			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
//			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
//			//--Inserimento riga in tabella se necessario
//			if ($toadd[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']][$sql->row['PROGR']]){
//				$insert = true;
//				$ftab = $xml_form->form['TABLE'];
//				//Check esistenza tabella, se esiste inserisco altrimenti non faccio nulla (aspetto la updatedb)
//				$query_check_existence = "select table_name from user_tables where table_name=upper('{$ftab}')";
//				$query = new query ( $this->conn );
//				$query->set_sql ( $query_check_existence );
//				$query->exec ();
//				$query->get_row ();
//				//die($insert);
//				if ($userid && strtoupper($userid) != "NULL"){
//					$userid = "'".$userid."'";
//				}else{
//					$userid = "NULL";
//				}
//				if($query->numrows!=0 && $insert){
//					//die("QUA");
//					$sql_tb="insert into $ftab(USERID_INS,{$this->pk_field}, VISITNUM,VISITNUM_PROGR,ESAM,PROGR) "; //GUID?
//					$sql_tb.=" VALUES ($userid,{$this->pk_value},{$sql->row['VISITNUM']},{$sql->row['VISITNUM_PROGR']},{$sql->row['ESAM']},{$sql->row['PROGR']}) ";
//					$query->set_sql($sql_tb);
//					$query->ins_upd();
//					//die($sql_tb);
//				}
//			}
//			//--Proseguo
//			$wca_docs='';
//			foreach ($xml_form->fields as $key=>$val){
//				if ($val['TYPE']=="file_doc"){
//					$wca_docs[$val['VAR']]=true;
//				}
//			}
//			foreach ($xml_form->fields as $key=>$val){
//				if ($val['TYPE']=="data"){
//					$date_fields[$val['VAR']]=true;
//				}
//			}
//			foreach ($xml_form->fields as $key=>$val){
//				if ($val['TYPE']=="checkbox"){
//					$checkbox_fields[$val['VAR']]=true;
//				}
//			}
//			$scheda=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
//			$table=$xml_form->form['TABLE'];
//			$sql_storico="insert into S_{$table}
//				select '{$this->userid}', sysdate, storico_id.nextval, 'U', $eq_int, o.* from {$table} o
//				where
//					o.ESAM={$sql->row['ESAM']}
//					and o.VISITNUM={$sql->row['VISITNUM']}
//					and o.VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
//					and o.PROGR={$sql->row['PROGR']}
//					and o.{$this->pk_field}={$this->pk_value}
//				";
//			$pk[$this->pk_field]=$this->pk_value;
//			$pk['ESAM']=$sql->row['ESAM'];
//			$pk['VISITNUM']=$sql->row['VISITNUM'];
//			$pk['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
//			$pk['PROGR']=$sql->row['PROGR'];
//			$sql_query_fields="select field, valore from {$this->service}_eqfield
//				where
//					ESAM={$sql->row['ESAM']}
//					and VISITNUM={$sql->row['VISITNUM']}
//					and VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
//					and PROGR={$sql->row['PROGR']}
//					and {$this->pk_field}={$this->pk_value}
//					and EQ_INT=$eq_int
//				";
//			$sql2=new query($this->conn);
//			$sql2->exec($sql_query_fields);
//			$values='';
//			while ($sql2->get_row()){
//				if (!$wca_docs[$sql2->row['FIELD']]) {
//					if ($date_fields[$sql2->row['FIELD']]) $values[$sql2->row['FIELD']]="to_date('{$sql2->row['VALORE']}','DDMMYYYY')";
////					else if($checkbox_fields[$sql2->row['FIELD']]) {
////						$values[$sql2->row['FIELD']]="null";
////					}
//					else $values[$sql2->row['FIELD']]=$sql2->row['VALORE'];
//				} else {
//					$sql3=new query($this->conn);
//					$sql_update_1="
//						update docs set tipo_doc='Trash'
//						where id_ref = (select id_ref from docs where id={$sql2->row['VALORE']})
//						and id <>{$sql2->row['VALORE']}
//						";
//					$sql_update_2="
//						update docs set id_ref={$sql2->row['VALORE']}, approved=1, approved_by='{$this->userid}', approv_dt=sysdate, approv_comm='Integrazione n.ro $eq_int'
//						where id={$sql2->row['VALORE']}
//						";
//					$sql3->set_sql($sql_update_1);
//					$sql3->ins_upd();
//					$sql3->set_sql($sql_update_2);
//					$sql3->ins_upd();
//				}
//			}
//			$sql2->set_sql($sql_storico);
//			$sql2->ins_upd();
//			$sql2->update($values, $table, $pk);
//		}
//
//		$this->conn->commit();
//		$sql_query="select distinct visitnum,visitnum_progr,esam from {$this->service}_coordinate
//			where {$this->pk_field}={$this->pk_value}
//			order by visitnum,visitnum_progr,esam
//			";
//		$sql=new query($this->conn);
//		$sql->exec($sql_query);
//		while ($sql->get_row()){
//			if (!isset($vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])) continue;
//			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
//			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
//			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
//			$wca_docs='';
//			foreach ($xml_form->fields as $key=>$val){
//				if ($val['TYPE']=="file_doc"){
//					$wca_docs[$val['VAR']]=true;
//				}
//			}
//			$vprogr = $sql->row['VISITNUM_PROGR'];
//			$sql_check="
//				select count(*) as n_schede, max(progr) as max_progr
//				from {$this->service}_coordinate
//				where {$this->pk_field}={$this->pk_value}
//				and esam={$sql->row['ESAM']}
//				and visitnum={$sql->row['VISITNUM']}
//				and visitnum_progr={$sql->row['VISITNUM_PROGR']}
//				";
//			$sql2=new query($this->conn);
//			$sql2->get_row($sql_check);
//			$sql2->row['MAX_PROGR']-=0;
//			if ($sql2->row['MAX_PROGR']!=$sql2->row['N_SCHEDE']){
//				$last_progr=$sql2->row['MAX_PROGR'];
//				$trovato=false;
//				while (!$trovato){
//					$sql_check2="
//		  				select count(*) as conto
//		  				from {$this->service}_coordinate
//		  				where
//		  				esam={$sql->row['ESAM']}
//						and visitnum={$sql->row['VISITNUM']}
//						and visitnum_progr={$sql->row['VISITNUM_PROGR']}
//		  				and progr=$last_progr-1
//		  				and {$this->pk_field}={$this->pk_value}";
//					$sql2->get_row($sql_check2);
//					if ($sql2->row['CONTO']==0){
//						$trovato=true;
//						$sql3=new query($this->conn);
//						$progr=$last_progr-1;
//						$sql_insert="
//						  	select *
//						  	from {$this->service}_COORDINATE
//						  	where
//		  					esam={$sql->row['ESAM']}
//							and visitnum={$sql->row['VISITNUM']}
//							and visitnum_progr={$sql->row['VISITNUM_PROGR']}
//						  	and progr=$progr+1
//						  	and {$this->pk_field}={$this->pk_value}";
//						$tb="{$this->service}_COORDINATE";
//						$pk='';
//						$sql3->get_row($sql_insert);
//						$sql3->row['PROGR']-=1;
//						$sql3->insert($sql3->row, $tb, $pk);
//						foreach ($wca_docs as $key => $val){
//							$orig_progr=$progr+1;
//							$key = "{$key}_{$vprogr}";
//							$_orig_key="{$key}_{$orig_progr}";
//							if ($progr>1) $_dest_key="{$key}_$progr";
//							else $_dest_key=$key;
//							//$id_tipo_ref=700000+$this->pk_value;
//							$sql_update="
//								update docs set keywords='$_dest_key' where id_tipo_ref=$id_tipo_ref and keywords='$_orig_key'";
//							$sql3=new query($this->conn);
//							$sql3->set_sql($sql_update);
//							$sql3->ins_upd();
//						}
//						$sql_update="
//						  	update {$xml_form->form['TABLE']}
//						  	set progr=progr-1
//						  	where
//						  	esam={$sql->row['ESAM']}
//							and visitnum={$sql->row['VISITNUM']}
//							and visitnum_progr={$sql->row['VISITNUM_PROGR']}
//						  	and progr=$progr+1
//						  	and {$this->pk_field}={$this->pk_value}";
//
//						$sql3->set_sql($sql_update);
//						$sql3->ins_upd();
//						$sql_delete="
//						  	delete from {$this->service}_COORDINATE
//						  	where
//						  	esam={$sql->row['ESAM']}
//							and visitnum={$sql->row['VISITNUM']}
//							and visitnum_progr={$sql->row['VISITNUM_PROGR']}
//						  	and progr=$progr+1
//						  	and {$this->pk_field}={$this->pk_value}";
//						$sql3->set_sql($sql_delete);
//						$sql3->ins_upd();
//						//$this->conn->commit();
//					}else $last_progr-=1;
//				}
//			}
//		}
//		$this->conn->commit();
//		$sql_update="update {$this->service}_EQ set stato=1, close_dt=sysdate where equery_int=$eq_int";
//		$sql->set_sql($sql_update);
//		$sql->ins_upd();
//		$this->conn->commit();
//
//	}

//	function respingiEq($vlist,$xml_dir,$config_service, $session_vars, $uploaded_file_dir, $commento){
//		if ($this->eq_int == ''){
//			return;
//		}
//		$eq_int=$this->eq_int;
//		//$id_tipo_ref = 700000 + $this->pk_value;
//		$id_area = 1;
//		//$id_area = $this->pk_value + (AREA_OFFSET*$id_area);
//		$id_tipo_ref = $this->pk_value + (AREA_OFFSET*$id_area);
//		/*****/
//		/*pulisco documenti*/
//
//		$sql_update="update docs set tipo_doc='Trash' where id_tipo_ref=$id_tipo_ref and approved is null";
//		$sql3=new query($this->conn);
//		$sql3->set_sql($sql_update);
//		$sql3->ins_upd();
//
//		/*fine pulisco documenti*/
//		$sql_to_be_deleted="
//			select
//				esam, progr, visitnum, visitnum_progr
//			from {$this->service}_coordinate
//			where {$this->pk_field}={$this->pk_value}
//			and eq_action=1 and INV_QUERY=$eq_int
//		";
//		$sql=new query($this->conn);
//		$sql->exec($sql_to_be_deleted);
//		while ($sql->get_row()){
//			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
//			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
//			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
//			$scheda=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
//			$table=$xml_form->form['TABLE'];
//			$sql_storico="insert into S_{$table}
//				select '{$this->userid}', sysdate, storico_id.nextval, 'D', $eq_int, o.* from {$table} o
//				where
//					o.ESAM={$sql->row['ESAM']}
//					and o.VISITNUM={$sql->row['VISITNUM']}
//					and o.VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
//					and o.PROGR={$sql->row['PROGR']}
//					and o.{$this->pk_field}={$this->pk_value}
//				";
//			$sql2=new query($this->conn);
//			$sql2->set_sql($sql_storico);
//			$sql2->ins_upd();
//		}
//		$this->conn->commit();
//
//		/*****/
//
//
//		$sql_to_be_deleted="
//			delete
//			from {$this->service}_coordinate
//			where {$this->pk_field}={$this->pk_value}
//			and inv_query={$this->eq_int}
//			and eq_action=1
//		";
//		$sql=new query($this->conn);
//		$sql->set_sql($sql_update);
//		$sql->ins_upd();
//		$this->conn->commit();
//
//		$values='';
//		$pk='';
//		$values['INV_QUERY']="null";
//		$values['EQ_ACTION']="null";
//		$pk['INV_QUERY']="null";
//		$pk['EQ_ACTION']="2";
//		$pk[$this->pk_field]=$this->pk_value;
//		$table=$this->service."_coordinate";
//		$sql=new query($this->conn);
//		$sql->update($values, $table, $pk);
//		$this->conn->commit();
//
//		$sql=new query($this->conn);
//		$values='';
//		$pk='';
//		$values['STATO']=3;
//		$values['RISP_DM']=$commento;
//		$values['CLOSE_DT']="sysdate";
//		$pk['EQUERY_INT']=$this->eq_int;
//		$pk[$this->pk_field]=$this->pk_value;
//		$table=$this->service."_EQ";
//		$sql->update($values, $table, $pk);
//		$this->conn->commit();
//	}
	
	
	/**
	 * Salvataggio equery campo
	 *
	 */
//	function SaveEqInt($xml_form){
//		
//		echo "SaveEqInt di integrazioni.php <br>";
//		
//		$id_area = 1;
//		//$id_area = $this->pk_value + (AREA_OFFSET*$id_area);
//		$id_tipo_ref = $this->pk_value + (AREA_OFFSET*$id_area);
//		
//		$ret=$this->getEqSpec($this->vlist);
//		$sql_check="select distinct eqfield.esam,
//                eqfield.{$this->pk_field},
//                eq.equery_int,
//                substr(eq.userid_ins,0,3) as center,
//                eq.rich_dm,
//                eq.rich_de,
//                eq.risp_dm,
//                eq.stato,
//                eq.ins_dt,
//                eqfield.progr,
//                eqfield.visitnum,
//                eqfield.visitnum_progr
//           from {$this->service}_eq eq, {$this->service}_eqfield eqfield
//           where
//                eq.equery_int=eqfield.eq_int
//					";
//		$sql = new query ( $this->conn );
//		$sql->exec ( $sql_check );
//		/*
//		while ( $sql->get_row () ) {
//			if ($sql->row['ESAM']==$ret[0]['PK']['ESAM'] && ($sql->row['STATO']=="0" || $sql->row['STATO']=="2")  ){
//				$body.="<form method='post'>
//						<TABLE align=center class=\"bordi\" width=\"70%\">
//	          				 <tr>
//								<td align=center colspan=4 cols=2><b><font size=\"3\" color=\"red\">Sorry, an eQuery is pending on this form</font></td>
//							</tr>
//						</table>
//						<br><br><br><br><br><br><br><br>
//						<TABLE align=center class=\"bordi\" width=\"70%\">
//							<tr>
//								<td cols=\"2\" align=center><a href=\"index.php?\"><font >Go to Home Page</font></a></td>
//							</tr>
//						</table>
//						<br><br><br><br><br><br><br><br><br><br>
//						";
//				die($body);// cercare di far tornare il body nel template
//			}
//		}
//		*/
//		foreach ($xml_form->fields as $key=>$val){
//			if ($val['TYPE']=="file_doc"){
//				$keywords=$val['VAR'];
//				if ($_POST['PROGR']!=1) $keywords.="_".$_POST['PROGR'];
//				//$id_tipo_ref=700000+$this->pk_value;
//				$sql_query="
//					select max(id) as C
//					from docs
//					where id_tipo_ref=$id_tipo_ref
//					and keywords='{$keywords}'
//					and tipo_doc='Doc_Area'
//					and approved is null
//					";
//				$sql=new query($this->conn);
//				if ($sql->get_row($sql_query)) {
//					if ($sql->row['C']!=''){
//						$fields[]=$val['VAR'];
//						$values[]=$sql->row['C'];
//					}
//				}
//			}
//		}
//
//		$session=new query($this->conn);
//		$session->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DDMMYYYY'");
//		$session->ins_upd();
//
//		$sql_query="select * from {$xml_form->form['TABLE']}
//			where $this->pk_field={$_POST[$this->pk_field]}
//			and esam={$_POST['ESAM']}
//			and progr={$_POST['PROGR']}
//			and visitnum={$_POST['VISITNUM']}
//			and visitnum_progr={$_POST['VISITNUM_PROGR']}";
//
//		$sql=new query($this->conn);
//		$sql->get_row($sql_query);
//		foreach ($sql->row as $key=>$val){
//			$original_res[$key]=$val;
//		}
//		if (!$original_res){
//			//die("GETSCHEMA!");
//			$sql_query="SELECT COLUMN_NAME, DATA_TYPE, DATA_LENGTH FROM all_tab_columns where table_name = '{$xml_form->form['TABLE']}' ";
//			$sql=new query($this->conn);
//			$sql->exec($sql_query);
//			while($sql->get_row()){
//				$original_res[$sql->row['COLUMN_NAME']] = '';
//			}
//		}
//		foreach ($xml_form->fields as $key=>$val){
//			if ($val['VAR']!='' && $val['TB']!='no'){
//				if (!isset($_POST[$val['VAR']]) || $_POST[$val['VAR']]=='') $_POST[$val['VAR']]=0;
//				$field_type = "field_{$val['TYPE']}";
//				include_once "libs/field.inc";
//				if (file_exists("fields/{$field_type}.inc")){
//					//echo "-MYFIELD";
//					include_once "fields/{$field_type}.inc";
//				}elseif (file_exists("libs/{$field_type}.inc")){
//					//echo "-LIBFIELD";
//					include_once "libs/{$field_type}.inc";
//				}else{
//					//echo "-LIBFIELDFIELD";
//					include_once "libs/fields/{$field_type}.inc";
//				}
//				$field_obj = new $field_type ( $xml_form, $xml_form->vars[$val['VAR']], $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $xml_form->errors );
//				$field_obj->insert_stmt();
//				foreach ($field_obj->field_stmt as $f=>$fv){
//					$fields[]=$fv;
//				}
//				foreach ($field_obj->value_stmt as $f=>$fv){
//					$values[]=$fv;
//				}
//			}
//		}
//		//echo "<br/>";
//		//print_r($fields);
//		//echo "<br/><br/>";
//		//print_r($values);
//		//echo "<br/><br/>";
//		//print_r($original_res);
//		//echo "<br/>";
//		//die("MORI");
//		/*
//		foreach ($original_res as $key=>$val){
//			echo "<li>$key - $val</li>";
//
//			if (isset($_POST[$key]) && $_POST[$key]!=$sql->row[$key] && isset($xml_form->fields[$xml_form->vars[$key]])
//			){
//				echo "<li>$key - $val - {$_POST[$key]}</li>";
//				$field_type = "field_{$xml_form->fields[$xml_form->vars[$key]]['TYPE']}";
//				include_once "libs/field.inc";
//				if (file_exists("libs/{$field_type}.inc")) include_once "libs/{$field_type}.inc";
//				else include_once "libs/fields/{$field_type}.inc";
//				$field_obj = new $field_type ( $xml_form, $xml_form->vars[$key], $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $xml_form->errors );
//				$field_obj->insert_stmt();
//				foreach ($field_obj->field_stmt as $key=> $val) $fields[]=$val;
//				foreach ($field_obj->value_stmt as $key=> $val) $values[]=$val;
//			}
//		}
//		*/
//		if ($this->eq_int=='') $this->createEq();
////			echo "<pre>";
////			print_r($values);
////			echo "</pre>";
////			echo "<pre>";
////			print_r($original_res);
////			echo "</pre>";
//		foreach ($fields as $key=>$val){
//
//			if ($values[$key]!=$original_res[$val]){ // && !($original_res[$val]==0 && $values[$key] =='') && !($original_res[$val]=='' && $values[$key] ==0)) {
//	//			echo $values[$key];
//	//			echo $original_res[$val]; //die();
//				$sql_query="select count(*) as c from {$this->service}_eqfield
//					where $this->pk_field={$_POST[$this->pk_field]}
//					and esam={$_POST['ESAM']}
//					and progr={$_POST['PROGR']}
//					and visitnum={$_POST['VISITNUM']}
//					and visitnum_progr={$_POST['VISITNUM_PROGR']}
//					and EQ_INT='{$this->eq_int}'
//					and field='$val'";
//				$sql->get_row($sql_query);
//				$vals='';
//				$pk='';
//				$vals['VALORE']=$values[$key];
//				if ($sql->row['C']=='0'){
//					$vals['EQ_INT']=$this->eq_int;
//					$vals[$this->pk_field]=$_POST[$this->pk_field];
//					$vals['ESAM']=$_POST['ESAM'];
//					$vals['VISITNUM']=$_POST['VISITNUM'];
//					$vals['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
//					$vals['PROGR']=$_POST['PROGR'];
//					$vals['FIELD']=$val;
//					$sql->insert($vals, $this->service."_EQFIELD",$pk);
//				}else {
//	
//					$pk['EQ_INT']=$this->eq_int;
//					$pk[$this->pk_field]=$_POST[$this->pk_field];
//					$pk['ESAM']=$_POST['ESAM'];
//					$pk['VISITNUM']=$_POST['VISITNUM'];
//					$pk['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
//					$pk['PROGR']=$_POST['PROGR'];
//					$pk['FIELD']=$val;
//					$table=$this->service."_EQFIELD";
//					$sql->update($vals, $table,$pk);
//				}
//			}
//		}
//		
//		//Aggiornamento tabella coordinate per gestione aggiunta schede
//		$sql_query="select * from {$this->service}_coordinate
//			where $this->pk_field={$_POST[$this->pk_field]}
//			and esam={$_POST['ESAM']}
//			and progr={$_POST['PROGR']}
//			and visitnum={$_POST['VISITNUM']}
//			and visitnum_progr={$_POST['VISITNUM_PROGR']}
//			";
//		if (!$sql->get_row($sql_query)){
//			//Non ho la riga in tabella coordinate
//			//die ("INSERT!");
//			$sql_query="insert into {$this->service}_coordinate(abilitato,{$this->pk_field},esam,progr,visitnum,visitnum_progr,inizio,fine,eq_action)
//				values (1,{$_POST[$this->pk_field]},{$_POST['ESAM']},{$_POST['PROGR']},{$_POST['VISITNUM']},{$_POST['VISITNUM_PROGR']},1,1,1)";
//			$sql->exec($sql_query);	
//		}
//		
//		
//		$this->conn->commit();
//	}
	
	
	
}




?>
