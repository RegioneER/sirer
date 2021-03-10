<?php

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


	function __construct($config_param, $conn, $userid, $profilo, $xmr_tip){

		$this->pk_field=$config_param['PK_SERVICE'];

		//ROLE
		if($config_param['eQuerySpec']['Integrazione']['ROLE'][$config_param['service']]!="")
			$this->role=$config_param['eQuerySpec']['Integrazione']['ROLE'][$config_param['service']];
		else
			$this->role=$config_param['eQuerySpec']['Integrazione']['ROLE'];

		//VALIDATOR
		if($config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']]!="")
			$this->approv_role=$config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']];
		else
			$this->approv_role=$config_param['eQuerySpec']['Integrazione']['VALIDATOR'];


		//NON_APPROV
		if($config_param['eQuerySpec']['Integrazione']['NON_APPROV'][$config_param['service']]!="")
			$this->non_appr_states=$config_param['eQuerySpec']['Integrazione']['NON_APPROV'][$config_param['service']];
		else
			$this->non_appr_states=$config_param['eQuerySpec']['Integrazione']['NON_APPROV'];

		//APPROV
		if($config_param['eQuerySpec']['Integrazione']['APPROV'][$config_param['service']]!="")
			$this->appr_states=$config_param['eQuerySpec']['Integrazione']['APPROV'][$config_param['service']];
		else
			$this->appr_states=$config_param['eQuerySpec']['Integrazione']['APPROV'];

		$this->conn=$conn;
		if (isset($_POST[$this->pk_field])) $this->pk_value=$_POST[$this->pk_field];
		else $this->pk_value=$_GET[$this->pk_field];
		$this->service=$config_param['service'];
		$this->userid=$userid;
		$this->profilo=$profilo;
		$this->stato=$this->getStato();
		$this->xmr_tip=$xmr_tip;
		$this->eq_enabled=$this->isEnabled($profilo, $config_param);
		if ($this->eq_enabled){
			$this->getEqs();
			$this->getActiveEq();
		}
		
		//print_r($this);
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
			  RICH_DM VARCHAR2(4000 CHAR),
			  RICH_DE VARCHAR2(4000 CHAR),
			  RISP_DM VARCHAR2(4000 CHAR)
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
		$query->set_sql ( $query_check_existence );
		$query->exec ();
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
			  VALORE         VARCHAR2(4000 CHAR)
			)
			";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
		}
		return true;
	}

	function getActiveEq(){
		if ($this->eq_int=='') return null;
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
		$sql->get_row($sql_query);
		$this->eq_int=$sql->row['EQUERY_INT'];
		$this->stato=$sql->row['STATO'];
		//aggiungere controlli di sicurezza
		if($_POST['EQ_INT']==''){
			$this->eq_int=$_POST['EQ_INT'];

		}
	}

	function getEqs(){
		if ($this->eq_int=='') return null;
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

	function isEnabled($profilo, $config_param){
		/*
		 * Leghiamo questa funzione agli stati in cui ? possibile
		 * richiedere integrazioni (parametro definito nel config)
		 * ed al fatto che non ci siano integrazioni in fase di approvazione
		 * sulla stessa pratica (parametrizzabile)
		 */
		if ($config_param['eQuery']!=1) return false;
		if (($this->role!=$profilo || $this->xmr_tip=='DE') && !($this->approv_role==$profilo)) return false;
		else if(count($config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']])>1 && in_array($profilo, $config_param['eQuerySpec']['Integrazione']['VALIDATOR'][$config_param['service']])) {
			return false;
		}
		else return true;


	}

	function createEq(){
		$sql=new query($this->conn);
		$sql_seq="select {$this->service}_eqseq.nextval as eq_int from dual";
		$sql->get_row($sql_seq);
		$this->eq_int=$sql->row['EQ_INT'];
		$val_th['EQUERY_INT']=$this->eq_int;
		$val_th[$this->pk_field]=$this->pk_value;
		$val_th['USERID_INS']=$this->userid;
		$val_th['INS_DT']='sysdate';
		$val_th['STATO']=0;
		$sql->insert($val_th,$this->service."_EQ","");
		$this->conn->commit();
		return $this->eq_int;
	}


	/**
	 * Salvataggio equery campo
	 *
	 */
	function SaveEqInt($xml_form){


		$ret=$this->getEqSpec($this->vlist);
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
           where
                eq.equery_int=eqfield.eq_int
					";
		$sql = new query ( $this->conn );
		$sql->exec ( $sql_check );
		/*
		while ( $sql->get_row () ) {
			if ($sql->row['ESAM']==$ret[0]['PK']['ESAM'] && ($sql->row['STATO']=="0" || $sql->row['STATO']=="2")  ){
				$body.="<form method='post'>
						<TABLE align=center class=\"bordi\" width=\"70%\">
	          				 <tr>
								<td align=center colspan=4 cols=2><b><font size=\"3\" color=\"red\">Sorry, an eQuery is pending on this form</font></td>
							</tr>
						</table>
						<br><br><br><br><br><br><br><br>
						<TABLE align=center class=\"bordi\" width=\"70%\">
							<tr>
								<td cols=\"2\" align=center><a href=\"index.php?\"><font >Go to Home Page</font></a></td>
							</tr>
						</table>
						<br><br><br><br><br><br><br><br><br><br>
						";
				die($body);// cercare di far tornare il body nel template
			}
		}
		*/
		foreach ($xml_form->fields as $key=>$val){
			if ($val['TYPE']=="file_doc"){
				$keywords=$val['VAR'];
				if ($_POST['PROGR']!=1) $keywords.="_".$_POST['PROGR'];
				$id_tipo_ref=700000+$this->pk_value;
				$sql_query="
					select max(id) as C
					from docs
					where id_tipo_ref=$id_tipo_ref
					and keywords='{$keywords}'
					and tipo_doc='Doc_Area'
					and approved is null
					";
				$sql=new query($this->conn);
				if ($sql->get_row($sql_query)) {
					if ($sql->row['C']!=''){
						$fields[]=$val['VAR'];
						$values[]=$sql->row['C'];
					}
				}
			}
		}

		$session=new query($this->conn);
		$session->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DDMMYYYY'");
		$session->ins_upd();

		$sql_query="select * from {$xml_form->form['TABLE']}
			where $this->pk_field={$_POST[$this->pk_field]}
			and esam={$_POST['ESAM']}
			and progr={$_POST['PROGR']}
			and visitnum={$_POST['VISITNUM']}
			and visitnum_progr={$_POST['VISITNUM_PROGR']}";

		$sql=new query($this->conn);
		$sql->get_row($sql_query);
		foreach ($sql->row as $key=>$val){
			$original_res[$key]=$val;
		}
		foreach ($xml_form->fields as $key=>$val){
			if ($val['VAR']!='' && $val['TB']!='no'){
				if (!isset($_POST[$val['VAR']]) || $_POST[$val['VAR']]=='') $_POST[$val['VAR']]=0;
				$field_type = "field_{$val['TYPE']}";
				include_once "libs/field.inc";
				if (file_exists("libs/{$field_type}.inc")) include_once "libs/{$field_type}.inc";
				else include_once "libs/fields/{$field_type}.inc";
				$field_obj = new $field_type ( $xml_form, $xml_form->vars[$val['VAR']], $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $xml_form->errors );
				$field_obj->insert_stmt();
				foreach ($field_obj->field_stmt as $f=>$fv){
					$fields[]=$fv;
				}
				foreach ($field_obj->value_stmt as $f=>$fv){
					$values[]=$fv;
				}
			}
		}
		/*
		foreach ($original_res as $key=>$val){
			echo "<li>$key - $val</li>";

			if (isset($_POST[$key]) && $_POST[$key]!=$sql->row[$key] && isset($xml_form->fields[$xml_form->vars[$key]])
			){
				echo "<li>$key - $val - {$_POST[$key]}</li>";
				$field_type = "field_{$xml_form->fields[$xml_form->vars[$key]]['TYPE']}";
				include_once "libs/field.inc";
				if (file_exists("libs/{$field_type}.inc")) include_once "libs/{$field_type}.inc";
				else include_once "libs/fields/{$field_type}.inc";
				$field_obj = new $field_type ( $xml_form, $xml_form->vars[$key], $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $xml_form->errors );
				$field_obj->insert_stmt();
				foreach ($field_obj->field_stmt as $key=> $val) $fields[]=$val;
				foreach ($field_obj->value_stmt as $key=> $val) $values[]=$val;
			}
		}
		*/
		if ($this->eq_int=='') $this->createEq();
//			echo "<pre>";
//			print_r($values);
//			echo "</pre>";
//			echo "<pre>";
//			print_r($original_res);
//			echo "</pre>";
		foreach ($fields as $key=>$val){

			if ($values[$key]!=$original_res[$val] && !($original_res[$val]==0 && $values[$key] =='') && !($original_res[$val]=='' && $values[$key] ==0)) {
//			echo $values[$key];
//			echo $original_res[$val]; //die();
			$sql_query="select count(*) as c from {$this->service}_eqfield
				where $this->pk_field={$_POST[$this->pk_field]}
				and esam={$_POST['ESAM']}
				and progr={$_POST['PROGR']}
				and visitnum={$_POST['VISITNUM']}
				and visitnum_progr={$_POST['VISITNUM_PROGR']}
				and EQ_INT='{$this->eq_int}'
				and field='$val'";
			$sql->get_row($sql_query);
			$vals='';
			$pk='';
			$vals['VALORE']=$values[$key];
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
		$this->conn->commit();
	}

	function ApprovaEq($vlist,$xml_dir, $config_service, $session_vars, $uploaded_file_dir){
		$eq_int=$this->eq_int;
		//Controllo schede da eliminare
		$sql_to_be_deleted="
			select
				esam, progr, visitnum, visitnum_progr
			from {$this->service}_coordinate
			where {$this->pk_field}={$this->pk_value}
			and eq_action=2
		";
		$sql=new query($this->conn);
		$sql->exec($sql_to_be_deleted);
		while ($sql->get_row()){
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
			$wca_docs='';
			foreach ($xml_form->fields as $key=>$val){
				if ($val['TYPE']=="file_doc"){
					$wca_docs[$val['VAR']]=true;
				}
			}
			foreach ($wca_docs as $key => $val){
				if ($sql->row['PROGR']!=1) $key="{$key}_{$sql->row['PROGR']}";
				$id_tipo_ref=700000+$this->pk_value;
				$sql_update="update docs set tipo_doc='Trash' where id_tipo_ref=$id_tipo_ref and keywords='$key'";
				$sql3=new query($this->conn);
				$sql3->set_sql($sql_update);
				$sql3->ins_upd();
			}
			$scheda=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			$table=$xml_form->form['TABLE'];
			$sql_storico="insert into S_{$table}
				select '{$this->userid}', sysdate, storico_id.nextval, 'D', $eq_int, o.* from {$table} o
				where
					o.ESAM={$sql->row['ESAM']}
					and o.VISITNUM={$sql->row['VISITNUM']}
					and o.VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
					and o.PROGR={$sql->row['PROGR']}
					and o.{$this->pk_field}={$this->pk_value}
				";
			$sql2=new query($this->conn);
			$sql2->set_sql($sql_storico);
			$sql2->ins_upd();
		}
		//elimino le schede
		$sql_delete="delete from {$this->service}_coordinate where
		{$this->pk_field}={$this->pk_value} and eq_action=2";
		$sql=new query($this->conn);
		$sql->set_sql($sql_delete);
		$sql->ins_upd();
		$sql=new query($this->conn);
		//aggiorno le schede nuove
		$sql_update="update {$this->service}_coordinate set INV_QUERY=null, EQ_ACTION=null
		where {$this->pk_field}={$this->pk_value} and eq_action=1";
		$sql->set_sql($sql_update);
		$sql->ins_upd();
		//applico le modifiche campo campo
		$sql_query="select distinct visitnum,visitnum_progr,esam,progr from {$this->service}_eqfield
			where eq_int=$eq_int
			order by visitnum,visitnum_progr,esam,progr
			";
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
			$wca_docs='';
			foreach ($xml_form->fields as $key=>$val){
				if ($val['TYPE']=="file_doc"){
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
				select '{$this->userid}', sysdate, storico_id.nextval, 'U', $eq_int, o.* from {$table} o
				where
					o.ESAM={$sql->row['ESAM']}
					and o.VISITNUM={$sql->row['VISITNUM']}
					and o.VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
					and o.PROGR={$sql->row['PROGR']}
					and o.{$this->pk_field}={$this->pk_value}
				";
			$pk[$this->pk_field]=$this->pk_value;
			$pk['ESAM']=$sql->row['ESAM'];
			$pk['VISITNUM']=$sql->row['VISITNUM'];
			$pk['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
			$pk['PROGR']=$sql->row['PROGR'];
			$sql_query_fields="select field, valore from {$this->service}_eqfield
				where
					ESAM={$sql->row['ESAM']}
					and VISITNUM={$sql->row['VISITNUM']}
					and VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
					and PROGR={$sql->row['PROGR']}
					and {$this->pk_field}={$this->pk_value}
					and EQ_INT=$eq_int
				";
			$sql2=new query($this->conn);
			$sql2->exec($sql_query_fields);
			$values='';
			while ($sql2->get_row()){
				if (!$wca_docs[$sql2->row['FIELD']]) {
					if ($date_fields[$sql2->row['FIELD']]) $values[$sql2->row['FIELD']]="to_date('{$sql2->row['VALORE']}','DDMMYYYY')";
//					else if($checkbox_fields[$sql2->row['FIELD']]) {
//						$values[$sql2->row['FIELD']]="null";
//					}
					else $values[$sql2->row['FIELD']]=$sql2->row['VALORE'];
				} else {
					$sql3=new query($this->conn);
					$sql_update_1="
						update docs set tipo_doc='Trash'
						where id_ref = (select id_ref from docs where id={$sql2->row['VALORE']})
						and id <>{$sql2->row['VALORE']}
						";
					$sql_update_2="
						update docs set id_ref={$sql2->row['VALORE']}, approved=1, approved_by='{$this->userid}', approv_dt=sysdate, approv_comm='Integrazione n.ro $eq_int'
						where id={$sql2->row['VALORE']}
						";
					$sql3->set_sql($sql_update_1);
					$sql3->ins_upd();
					$sql3->set_sql($sql_update_2);
					$sql3->ins_upd();
				}
			}
			$sql2->set_sql($sql_storico);
			$sql2->ins_upd();
			$sql2->update($values, $table, $pk);
		}

		$this->conn->commit();
		$sql_query="select distinct visitnum,visitnum_progr,esam from {$this->service}_coordinate
			where {$this->pk_field}={$this->pk_value}
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
				if ($val['TYPE']=="file_doc"){
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
		$sql_update="update {$this->service}_EQ set stato=1, close_dt=sysdate where equery_int=$eq_int";
		$sql->set_sql($sql_update);
		$sql->ins_upd();
		$this->conn->commit();

	}


	function getEqSpec($vlist,$userid=null){
		if($this->eq_int=="") return false;

		if(isset($_POST['ESAM'])){
				$where="and esam={$_POST['ESAM']}";
			}
		$sql_query="select distinct visitnum,visitnum_progr,esam,progr from {$this->service}_eqfield
			where eq_int={$this->eq_int} $where
			order by visitnum,visitnum_progr,esam,progr
			";
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			$scheda[]=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			$spec[]=0;
			$spec_pk[]['VISITNUM']=$sql->row['VISITNUM'];
			$spec_pk[count($spec_pk)-1]['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
			$spec_pk[count($spec_pk)-1]['PROGR']=$sql->row['PROGR'];
			$spec_pk[count($spec_pk)-1]['ESAM']=$sql->row['ESAM'];
			$d_spec[]=$this->d_stati(0);
		}
		$sql_query="select distinct visitnum,visitnum_progr,esam,progr from {$this->service}_coordinate
		where {$this->pk_field}={$this->pk_value} and eq_action=1
		";
		$sql->exec($sql_query);
		while ($sql->get_row()){
			$scheda[]=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			$spec[]=1;
			$spec_pk[]['VISITNUM']=$sql->row['VISITNUM'];
			$spec_pk[count($spec_pk)-1]['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
			$spec_pk[count($spec_pk)-1]['PROGR']=$sql->row['PROGR'];
			$spec_pk[count($spec_pk)-1]['ESAM']=$sql->row['ESAM'];
			$d_spec[]=$this->d_stati(1);
		}
		$sql_query="select distinct visitnum,visitnum_progr,esam,progr from {$this->service}_coordinate
		where {$this->pk_field}={$this->pk_value} and eq_action=2
		";
		$sql->exec($sql_query);
		while ($sql->get_row()){
			$scheda[]=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			$spec[]=2;
			$spec_pk[]['VISITNUM']=$sql->row['VISITNUM'];
			$spec_pk[count($spec_pk)-1]['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
			$spec_pk[count($spec_pk)-1]['PROGR']=$sql->row['PROGR'];
			$spec_pk[count($spec_pk)-1]['ESAM']=$sql->row['ESAM'];
			$d_spec[]=$this->d_stati(2);
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
		$eq_int=$this->eq_int;
		$id_tipo_ref = 700000 + $this->pk_value;
		/*****/
		/*pulisco documenti*/

		$sql_update="update docs set tipo_doc='Trash' where id_tipo_ref=$id_tipo_ref and approved is null";
		$sql3=new query($this->conn);
		$sql3->set_sql($sql_update);
		$sql3->ins_upd();

		/*fine pulisco documenti*/
		$sql_to_be_deleted="
			select
				esam, progr, visitnum, visitnum_progr
			from {$this->service}_coordinate
			where {$this->pk_field}={$this->pk_value}
			and eq_action=1 and INV_QUERY=$eq_int
		";
		$sql=new query($this->conn);
		$sql->exec($sql_to_be_deleted);
		while ($sql->get_row()){
			$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
			$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
			$scheda=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			$table=$xml_form->form['TABLE'];
			$sql_storico="insert into S_{$table}
				select '{$this->userid}', sysdate, storico_id.nextval, 'D', $eq_int, o.* from {$table} o
				where
					o.ESAM={$sql->row['ESAM']}
					and o.VISITNUM={$sql->row['VISITNUM']}
					and o.VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}
					and o.PROGR={$sql->row['PROGR']}
					and o.{$this->pk_field}={$this->pk_value}
				";
			$sql2=new query($this->conn);
			$sql2->set_sql($sql_storico);
			$sql2->ins_upd();
		}
		$this->conn->commit();

		/*****/


		$sql_to_be_deleted="
			delete
			from {$this->service}_coordinate
			where {$this->pk_field}={$this->pk_value}
			and inv_query={$this->eq_int}
			and eq_action=1
		";
		$sql=new query($this->conn);
		$sql->set_sql($sql_update);
		$sql->ins_upd();
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


}

class form_int_prototype extends xml_form_prototype {

	
	function make_html($no_link_back=false, $closed=false,$force_open=false,$exclude_send_buttons=false) {
		
		$in = $this->session_vars;
		$inputval = $this->tb_vals;
		$remote_userid = $in ['remote_userid'];
		
//		$in ['USER_TIP']='RO';
		
		$sql_query="select fine, userid, visitclose from {$this->config_service['service']}_coordinate where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and esam='{$in['ESAM']}' and progr='{$in['PROGR']}' and visitnum='{$in['VISITNUM']}' and visitnum_progr='{$in['VISITNUM_PROGR']}'";
//		echo $sql_query;
		$sql=new query($this->conn);
		$sql->get_row($sql_query);
		
		
		if(is_numeric($in[$this->PK_SERVICE]) && $in[$this->PK_SERVICE]!="") {
			$sql_query="SELECT ID_STATO FROM {$this->config_service['service']}WF_STATO WHERE PK_SERVICE='{$in[$this->PK_SERVICE]}' ";
//			echo $sql_query;
			$sql_stato=new query($this->conn);
			$sql_stato->get_row($sql_query);
			$stato_prat=$sql_stato->row['ID_STATO'];
		}
//echo $this->session_vars['WFact'];
//echo "<br />";
//echo $this->config_service['eQuerySpec']['Integrazione']['ROLE'][$this->service];
//echo "<br />";

		if ($sql->row['FINE']==1) $this->closed=true;
		if ($sql->row['USERID']==$remote_userid && $sql->row['FINE']!='1' && $sql->row['VISITCLOSE']!='1') $in['USER_TIP']='DE';
		else if($sql->row['USERID']!="" && $this->config_service['eQuerySpec']['Integrazione']['ROLE'][$this->service]!=$this->session_vars['WFact']) {
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
						where INV_QUERY={$integrazione->eq_int}
						and esam={$_GET['ESAM']}
						and progr=$progr
						and VISITNUM={$_GET['VISITNUM']}
						and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}
						and {$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}
						";
						$sql=new query($this->conn);
						$sql->get_row($sql_query);
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