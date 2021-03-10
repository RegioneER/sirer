<?

/**
 * Classe xml_esams_list_prototype
 *
 * Gestisce la rappresentazione grafica delle schede dello studio
 * @package ViewsAndControllers
 */
class xml_esams_list_prototype{

	var $titolo;
	var $visitnums;
	var $esams;
	var $enable_visit;
	var $group;
	var $links;
	var $html;
	var $page;
	var $xml;
	var $PK_SERVICE;
	var $tabs;
	var $visit_menu;
	var $config;
	var $testi;
	var $true_false;
	var $config_service;
	var $conn;
	var $session_vars;
	var $xml_dir;
	var $lang='it';
	var $integrazione;

	/**
	 * Recupera i testi configurabili
	 *
	 * @param String $testo
	 * @return String
	 */
	function testo($testo){
		if(!isset($this->testi[$testo])){
			if($this->lang=='en'){
				$this->testi['Aggiungi']="Add";
				$this->testi['Elimina']="Delete";
				$this->testi['Sei sicuro di voler eliminare']="Are you sure you want to delete";
				$this->testi['numero']="number";
				$this->testi['inviato_corretto_da']="Sent/Modified by";
				$this->testi['data_invio']="Sent&nbsp;date";
			}
			else{
				$this->testi['Aggiungi']="Aggiungi";
				$this->testi['Elimina']="Elimina";
				$this->testi['Sei sicuro di voler eliminare']="Sei sicuro di voler eliminare";
				$this->testi['numero']="numero";
				$this->testi['inviato_corretto_da']="Inviato/Corretto da";
				$this->testi['data_invio']="Data&nbsp;d'invio";
			}
		}
		return $this->testi[$testo];
	}

	/**
	 * Costruisce le configurazioni
	 *
	 */
	function configura(){
		if(isset($this->config_service['lang']))$this->config['language']=$this->config_service['lang'];
		if(!isset($this->config['language']))$this->config['language']='it';
		if(strtolower($this->config['language'])=='it'){
			$this->testi['nuovo_inserimento']='Nuovo inserimento';
		}
		else{
			$this->testi['nuovo_inserimento']='New';
		}
		$this->true_false['configurato']=true;
	}
	/**
	 * Costruttore
	 *
	 * @param string $xml_file
	 * @return xml_esams_list
	 */
	function xml_esams_list_prototype($xml_file, $config_service=null, $session_vars=null, $conn=null, $xml_dir=null){
		if (!isset($config_service)) global $config_service;
		$this->config_service=$config_service;
		if (!isset($session_vars)) {
			global $in;
			$session_vars=$in;
		}
		if (!isset($xml_dir)) global $xml_dir;
		$this->xml_dir=$xml_dir;
		$this->session_vars=$session_vars;
		if (!isset($conn)) global $conn;
		$this->conn=$conn;
		$this->configura();
		$this->PK_SERVICE=$this->config_service['PK_SERVICE'];
		$xml_parser=new my_xml_parser($xml_file);
		$this_node=new xml_node();
		$g=0;
		for ($i=0;$i<count($xml_parser->vals);$i++){
			$this_node->xml_node_by_array($xml_parser->vals[$i]);
			if ($this_node->type!='cdata'){
				if ($this_node->tag=='VISIT_EXAM') if ($this_node->type=='open' or $this_node->type=='complete') {
					$this->page=$this_node->attributes;
				}
				if ($this_node->tag=='GROUP') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->group[$g]=$this_node->attributes;
					}
					if ($this_node->type=='close') {
						$g++;
					}
				}

				if ($this_node->tag=='VISIT') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$vis_num=$this_node->attributes['NUMBER']+0;
						$this->group[$g]['VISIT'][$vis_num]=$vis_num;
						$this->visitnums[$vis_num]=$this_node->attributes;
					}
				}
				if ($this_node->tag=='EXAM') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$es_num=$this_node->attributes['NUMBER']+0;
						$this->group[$g]['ESAM'][$es_num]=$es_num;
						$this->esams[$vis_num][$es_num]=$this_node->attributes;
						$this->xml[$es_num]=$this_node->attributes['XML'];
					}
				}
				if ($this_node->tag=='CLOSE_VISIT') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->visitnums[$vis_num]['CLOSE_VISIT']=$this_node->value;

					}
				}
				if ($this_node->tag=='CLOSE_VISIT_NOTE') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->visitnums[$vis_num]['CLOSE_VISIT_NOTE']=$this_node->value;
						$this->visitnums[$vis_num]['CLOSE_VISIT_NOTE_ATTR']=$this_node->attributes;

					}
				}
				if ($this_node->tag=='ENABLE_VISIT') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$en_idx+=0;
						$this->enable_visit[$vis_num][$en_idx]=$this_node->attributes;
						$en_idx++;
					}
				}
				if ($this_node->tag=='TEXT') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->esams[$vis_num][$es_num]['TESTO']=$this_node->value;
					}
				}
				if ($this_node->tag=='EXAM_HEADER') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->esams[$vis_num][$es_num]['HEADER']=$this_node->value;
					}
				}
				if ($this_node->tag=='CLOSE_ALL') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$this->esams['CLOSE_ALL']=$this_node->value;
					}
				}
			}
		}

		if (isset($this->config_service['eQuery']) && $this->config_service['eQuery']==1){
			if (
			(isset($_GET[$this->config_service['PK_SERVICE']]) && $_GET[$this->config_service['PK_SERVICE']]!='' && $_GET[$this->config_service['PK_SERVICE']]!='next') ||
			(isset($_POST[$this->config_service['PK_SERVICE']]) && $_POST[$this->config_service['PK_SERVICE']]!='' && $_POST[$this->config_service['PK_SERVICE']]!='next')
			)
			$this->integrazione=new integrazioni($this->config_service, $this->conn, $this->session_vars['remote_userid'], $this->session_vars['WFact'], $this->session_vars ['USER_TIP'],$this->session_vars);
		}
	}

	/**
	 * Controlla se la visita è chiusa
	 *
	 * @param number $visitnum
	 * @return boolean
	 */
	function isVisitClose($visitnum){
		$in=$this->session_vars;
		$conn=$this->conn;
		$sql_visitclose="
			select
				max(visitclose) as visitclose
			from ".$GLOBALS['service']."_COORDINATE
			where visitnum=:visitnum and {$this->PK_SERVICE}=:pk_service
			";
		$sql=new query($conn);
		unset($bind);
		$bind['VISITNUM']=$visitnum;
		$bind['PK_SERVICE']=$in[$this->PK_SERVICE];
		//$sql->set_sql($sql_visitclose);
		$sql->exec($sql_visitclose,$bind);//binded
		if ($sql->get_row()){
			if ($sql->row['VISITCLOSE']==1) return true;
			else return false;
		}
		else return false;
	}

	function AddVisitProgr($visitnum){
		$in=$this->session_vars;
		$conn=$this->conn;
		if ($this->isVisitClose($visitnum)) return false;
		$sql_visit_progr="
			select
				max(visitnum_progr) as visitnum_progr
			from ".$GLOBALS['service']."_COORDINATE
			where visitnum=:visitnum and {$this->PK_SERVICE}=:pk_service
			";
		unset($bind);
		$bind['VISITNUM']=$visitnum;
		$bind['PK_SERVICE']=$in[$this->PK_SERVICE];
		
		$sql=new query($conn);
		//$sql->set_sql($sql_visit_progr);
		$sql->exec($sql_visit_progr,$bind);//binded
		if ($sql->get_row()){
			$next_visit_progr=$sql->row['VISITNUM_PROGR']+1;
		}
		else $next_visit_progr=0;
		foreach ($this->esams[$visitnum] as $key => $val){
			if($val['DEFAULT']=='yes') {
				//sql-injection CARLO
				$sql_query_enable="insert into ".$GLOBALS['service']."_COORDINATE
					({$this->PK_SERVICE}, visitnum, visitnum_progr, esam, progr, abilitato)
					values ({$in[$this->PK_SERVICE]}, $visitnum, $next_visit_progr, $key, 1, 1)
				";
				$sql_query_enable="insert into ".$GLOBALS['service']."_COORDINATE
					({$this->PK_SERVICE}, visitnum, visitnum_progr, esam, progr, abilitato)
					values ({$in[$this->PK_SERVICE]}, $visitnum, $next_visit_progr, $key, 1, 1)
				";
				$bindVars['pk_service']=$in[$this->PK_SERVICE];
				$bindVars['visitnum']=$visitnum;
				$bindVars['next_visit_progr']=$next_visit_progr;
				$bindVars['key']=$key;
				//$sql->set_sql($sql_query_enable);
				$sql->ins_upd($sql_query_enable, $bindVars); //binded
				$conn->commit();
			}
		}
		return $next_visit_progr;
	}

	function DelVisitProgr($visitnum, $visitnum_progr){
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$sql=new query($conn);
		foreach ($this->esams[$visitnum] as $key => $val){
			$xml_form=new xml_form();
			$xml_form->xml_form_by_file($xml_dir.'/'.$val['XML']);
			$table=$xml_form->form['TABLE'];
			$esam=$val['NUMBER'];
			//sql-injection CARLO
			$bindVars='';
			$sql_save_storico="
				insert into S_{$xml_form->form['TABLE']}
  					select '{$in['remote_userid']}', sysdate, storico_id.nextval, 'E', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
   					and t.esam=$esam
     				and t.visitnum = {$visitnum}
     				and t.visitnum_progr = {$visitnum_progr}
			";
     		$sql_save_storico="
				insert into S_{$xml_form->form['TABLE']}
  					select :remote_user, sysdate, storico_id.nextval, 'E', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = :pk_service
   					and t.esam=:esam
     				and t.visitnum = :visitnum
     				and t.visitnum_progr = :visitnum_progr
			"; //binded
     		$bindVars['remote_userid']=$in['remote_userid'];
     		$bindVars['pk_service']=$in[$this->PK_SERVICE];
     		$bindVars['esam']=$esam;
     		$bindVars['visitnum']=$visitnum;
     		$bindVars['visitnum_progr']=$visitnum_progr;
     		$bindVars2='';
			$sql_delete="
     			delete from {$xml_form->form['TABLE']}
     			where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     				and esam=$esam
     				and visitnum = {$visitnum}
     				and visitnum_progr = {$visitnum_progr}
     		";
     		$sql_delete="
     			delete from {$xml_form->form['TABLE']}
     			where {$this->PK_SERVICE} = :pk_service
     				and esam=:esam
     				and visitnum = :visitnum
     				and visitnum_progr = :visitnum_progr
     		"; //binded
     		$bindVars2['pk_service']=$in[$this->PK_SERVICE];
     		$bindVars2['esam']=$esam;
     		$bindVars2['visitnum']=$visitnum;
     		$bindVars2['visitnum_progr']=$visitnum_progr;	
			$sql->ins_upd($sql_save_storico, $bindVars); //binded
			$sql->ins_upd($sql_delete, $bindVars2); //binded
			//echo "<li>$sql_save_storico</li><li>$sql_delete</li>";

		}
		$bindVars3="";
		$sql_delete_coordinate="
     			delete from ".$GLOBALS['service']."_COORDINATE where
     				{$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     				and visitnum = {$visitnum}
     				and visitnum_progr = {$visitnum_progr}
     		";
     	$sql_delete_coordinate="
     			delete from ".$GLOBALS['service']."_COORDINATE where
     				{$this->PK_SERVICE} = :pk_service
     				and visitnum = :visitnum
     				and visitnum_progr = :visitnum_progr
     		"; //binded
     	
     	$bindVars3['pk_service']=$in[$this->PK_SERVICE];
     	$bindVars3['visitnum']=$visitnum;
     	$bindVars3['visitnum_progr']=$visitnum_progr;
		$sql->ins_upd($sql_delete_coordinate, $bindVars3); //binded
		$conn->commit();
		//echo "<li> - $sql_delete_coordinate</li>";
		$this->ScalaVisiteProgr($visitnum, $visitnum_progr);
	}

	function ScalaVisiteProgr($visitnum, $visitnum_progr){
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$sql=new query($conn);
		$sql_vprogrs="select visitnum_progr from ".$GLOBALS['service']."_COORDINATE where
			{$this->PK_SERVICE} = :pk_service
     				and visitnum = :visitnum
     				and visitnum_progr > :visitnum_progr
     			order by visitnum_progr asc
			";
		unset($bind);
		$bind['PK_SERVICE']=$in[$this->PK_SERVICE];
		$bind['VISITNUM']=$visitnum;
		$bind['VISITNUM_PROGR']=$visitnum_progr;
		//$sql->set_sql($sql_vprogrs);
		$sql->exec($sql_vprogrs,$bind);//binded
		while ($sql->get_row()){
			$sql2=new query($conn);
			//echo "<li><b>{$sql->row['VISITNUM_PROGR']}</b></li>";
			$vprogr=$sql->row['VISITNUM_PROGR'];
			$sql_duplica_coordinate="
     		insert into ".$GLOBALS['service']."_COORDINATE
     			select
     				VISITNUM,
     				PROGR,
     				ESAM,
     				INIZIO,
     				FINE,
     				INSERTDT,
     				MODDT,
     				USERID,
     				VISITCLOSE,
     				INV_QUERY,
     				{$this->PK_SERVICE},
     				ABILITATO,
     				VISITNUM_PROGR-1
     			from ".$GLOBALS['service']."_COORDINATE
     			where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     			and visitnum = {$visitnum}
     			and visitnum_progr = {$vprogr}
     				";
     		$sql_duplica_coordinate="
     		insert into ".$GLOBALS['service']."_COORDINATE
     			select
     				VISITNUM,
     				PROGR,
     				ESAM,
     				INIZIO,
     				FINE,
     				INSERTDT,
     				MODDT,
     				USERID,
     				VISITCLOSE,
     				INV_QUERY,
     				{$this->PK_SERVICE},
     				ABILITATO,
     				VISITNUM_PROGR-1
     			from ".$GLOBALS['service']."_COORDINATE
     			where {$this->PK_SERVICE} = :pk_service
     			and visitnum = :visitnum
     			and visitnum_progr = :visitnum_progr
     				"; //binded
     			$bindVars='';
     			$bindVars['pk_service']=$in[$this->PK_SERVICE];
     			$bindVars['visitnum']=$visitnum;
     			$bindVars['visitnum_progr']=$vprogr;	
			//echo "<li>$sql_duplica_coordinate</li>";
			$sql2->ins_upd($sql_duplica_coordinate, $bindVars); //binded
			foreach ($this->esams[$visitnum] as $key => $val){
				$xml_form=new xml_form();
				$xml_form->xml_form_by_file($xml_dir.'/'.$val['XML']);
				$table=$xml_form->form['TABLE'];
				$esam=$val['NUMBER'];
				$sql_save_storico="
				insert into S_{$xml_form->form['TABLE']}
  					select '{$in['remote_userid']}', sysdate, storico_id.nextval, 'S', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
   					and t.esam=$esam
     				and t.visitnum = {$visitnum}
     				and t.visitnum_progr = {$vprogr}
				";
     			$sql_save_storico="
				insert into S_{$xml_form->form['TABLE']}
  					select :remote_userid, sysdate, storico_id.nextval, 'S', null, t.*
    				from {$xml_form->form['TABLE']} t
   					where t.{$this->PK_SERVICE} = :pk_service
   					and t.esam=:esam
     				and t.visitnum = :visitnum
     				and t.visitnum_progr = :visitnum_progr
				"; //binded
     			$bindVars1="";
     			$bindVars1["remote_userid"]=$in['remote_userid'];
     			$bindVars1["pk_service"]=$in[$this->PK_SERVICE];
     			$bindVars1["esam"]=$esam;
     			$bindVars1["visitnum"]=$visitnum;
     			$bindVars1["visitnum_progr"]=$vprogr;
				$sql_update_table="
					update {$table} set visitnum_progr=visitnum_progr-1
					where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
						and esam=$esam
     					and visitnum = {$visitnum}
     					and visitnum_progr = {$vprogr}
				";
     			$sql_update_table="
					update {$table} set visitnum_progr=visitnum_progr-1
					where {$this->PK_SERVICE} = :pk_service
						and esam=:esam
     					and visitnum = :visitnum
     					and visitnum_progr = :visitnum_progr
				"; // binded
     			$bindVars2="";
     			$bindVars2["pk_service"]=$in[$this->PK_SERVICE];
     			$bindVars2["esam"]=$esam;
     			$bindVars2["visitnum"]=$visitnum;
     			$bindVars2["visitnum_progr"]=$vprogr;
				$sql2->ins_upd($sql_save_storico, $bindVars1); //binded
				$sql2->ins_upd($sql_update_table, $bindVars2); //binded
				//echo "<li>$sql_save_storico</li><li>$sql_update_table</li>";
			}
			$sql_coordinate_delete="
				delete from ".$GLOBALS['service']."_COORDINATE
				where {$this->PK_SERVICE} = {$in[$this->PK_SERVICE]}
     			and visitnum = {$visitnum}
     			and visitnum_progr = {$vprogr}
			";
     		$sql_coordinate_delete="
				delete from ".$GLOBALS['service']."_COORDINATE
				where {$this->PK_SERVICE} = :pk_service
     			and visitnum = :visitnum
     			and visitnum_progr = :visitnum_progr
			"; //binded
     		$bindVars3="";
     		$bindVars3["pk_service"]=$in[$this->PK_SERVICE];
     		$bindVars3["visitnum"]=$visitnum;
     		$bindVars3["visitnum_progr"]=$vprogr;
			$sql2->ins_upd($sql_coordinate_delete, $bindVars3); //binded
			//echo "<li>$sql_coordinate_delete</li>";
		}
		$conn->commit();
	}

	/**
	 * Restituisce il codice xml dell'oggetto
	 *
	 * @return string
	 */
	function obj_to_xml(){
		$xml_str="<visit_exam>\n";
		foreach ($this->group as $key => $val){
			$xml_str.="	<group text=\"{$val['TEXT']}\">\n";
			foreach ($val['VISIT'] as $key_v => $val_v) {
				$xml_str.="		<visit number=\"$val_v\" text=\"{$this->visitnums[$val_v]['TEXT']}\" short_txt=\"{$this->visitnums[$val_v]['SHORT_TXT']}\">\n";
				foreach ($this->esams[$val_v] as $es_num => $es_val){
					if (isset($es_val['PROGR'])) $progr="PROGR=\"{$es_val['PROGR']}\"";
					else $progr="";
					$xml_str.="			<exam number=\"{$es_num}\" xml=\"{$es_val['XML']}\" $progr >\n";
					$xml_str.="				<text>{$es_val['TESTO']}</text>\n";
					$xml_str.="			</exam>\n";
				}
				$xml_str.="		</visit>\n";
			}
			$xml_str.="	</group>\n";
		}
		$xml_str.="</visit_exam>";
		return $xml_str;
	}


	/**
	 * Costruisce i tab relativo alla form visualizzata
	 *
	 * @return string
	 */
	function esams_list_tab(){
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		$this->tab="
		<noscript>
		<font color='red'>Attenzione salvare i dati prima di cambiare form</font>
		</noscript>
		<ul id=\"globalnav\">";
		if ($config_service['PK_SERVICE']!='') $this->PK_SERVICE=$config_service['PK_SERVICE'];
		if ($config_service['VISITNUM_PROGR']=='1') {
			$add_vprogr="VISITNUM_PROGR,";
			$sql=new query($conn);
			$sql_select="select max(visitnum_progr) as maxvp from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service";
			//$sql->set_sql($sql_select);
			unset($bind_pk);
			$bind_pk['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
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
		if ($in[$this->PK_SERVICE]=='next') return;
		$query="select visitnum,$add_vprogr esam, progr, inizio, fine,visitclose, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service order by visitnum,$add_vprogr esam ,progr";
		//echo "<hr>$query<hr>";
		$sql=new query($conn);
		unset($bind_pk);
		$bind_pk['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
		//$sql->set_sql($query);
		$sql->exec($query,$bind_pk);//binded
		$this->visit_menu="<table  border=0><tr><th class=titolo><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;exams=visite_exams.xml\">Lista Schede</a></th></tr>";
		#print_r($this->visitnums);
		while ($sql->get_row()){
			if ($this->visitnums[$sql->row['VISITNUM']]['PROGR']=='yes') {
				if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']]['ENABLED']=true;
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']])){
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE']=$sql->row['VISITCLOSE'];
				}
			}
			else {
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
					if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']]['ENABLED']=true;
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE']=$sql->row['VISITCLOSE'];
				}
			}
		}
		foreach ($this->visitnums as $key => $val) {
			if ($val['PROGR']=='yes'){
				foreach($this->esams[$key] as $vprogr => $vesam){

					$nro=$vprogr+1;
					if ($in['VISITNUM']==$key && $in['VISITNUM_PROGR']==$vprogr){
						if ($this->visitnums[$key][$vprogr]['ENABLED']) $this->visit_menu.="<tr><td class=int><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\"><font color=red>".$val['TEXT']." $nro</font></a></td></tr>";
						//$this->tab.="\n<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\">".$val['TEXT']." $nro</a>\n<ul>\n";
						$visit_enabled=false;
						foreach ($vesam as $esam => $es_val){
							if ($es_val)
							if ($in['VISITNUM']==$key)	$this->print_esams_tab($es_val,$key,$esam);
							else $this->print_esams_tab($es_val,$key,$esam,false);
						}
						//$this->tab.="</ul>";
					}
					else if ($this->visitnums[$key][$vprogr]['ENABLED']) {
						//$this->visit_menu.="<tr><td class=sc4bis><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\">".$val['TEXT']." $nro</a></td></tr>";
						$this->print_esams_tab($es_val,$key,$esam,false);
					}
					//else $this->tab.="<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\">".$val['TEXT']." $nro</a></li>\n";
					//echo "<hr>{$_GET['VISITNUM_PROGR']}<hr>";
				}
			}
			else {
				if ($in['VISITNUM']==$key){

					if ($this->visitnums[$key]['ENABLED']) $this->visit_menu.="<tr><td class=sc4bis><li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\"><font color=red>".$val['TEXT']."</font></a></li></td></tr>";
					//$this->tab.="<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\">".$val['TEXT']."</a></li>\n<ul>\n";
					foreach ($this->esams[$key] as $esam => $es_val){
						if ($in['VISITNUM']==$key)	$this->print_esams_tab($es_val,$key,$esam);
					}
					//$this->tab.="</ul>";
				}
				else {
					if ($this->visitnums[$key]['ENABLED']) $this->visit_menu.="<tr><td class=sc4bis><li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"here\">".$val['TEXT']."</a></li></td></tr>";
					foreach ($this->esams[$key] as $esam => $es_val){
						$this->print_esams_tab($es_val,$key,$esam,false);
					}
				}
				//else $this->tab.="<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\">".$val['TEXT']."</a></li>\n";
			}
		}
		$this->tab.="</ul><br><br><br>";
		global $config_service;
		global $tab_menu_list;
		$this->visit_menu.="
			<tr>
				<td class=titolo align=center><a href=\"index.php?list=patients_list.xml\">{$config_service['Patients_list']}</a></td>
			</tr>
			$tab_menu_list
		</table>";
		return $this->tab;
	}

	/**
	 * Restituisce il tab dell'esame $esam della visita $key
	 *
	 * @param array $es_val
	 * @param number $key
	 * @param number $esam
	 */
	function print_esams_tab($es_val, $key, $esam, $this_visit=true){
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;

		//echo "<hr>$key<hr>";
		$link="index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$key."&amp;ESAM={$esam}";
		//echo "<hr>$esam - <hr>";
		$enabled=false;


		if (isset($es_val['PROGR']) && $es_val['PROGR']=='yes' && $es_val['CONT_FORM']==''){
			if (isset($es_val['RES']) && is_array($es_val['RES'])) foreach($es_val['RES'] as $res_key => $vals) {
				$es_progr=$res_key;
				$link.="&PROGR={$es_progr}";
				if ($vals['ABILITATO']=='1') $enabled=true;
				$sql2=new query($conn);
				if ($es_val['VAL_AGG']!='') {
					//echo "<hr>{$es_val['TESTO']}<hr>";
					$query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and  progr=:progr and esam=:esam";
					//echo "<hr>$query_data";
					unset($bind);
					$bind['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
					$bind['PROGR']=$es_progr;
					$bind['ESAM']=$esam;
					//$sql2->set_sql($query_data);
					$sql2->exec($query_data,$bind);//binded
					$sql2->get_row();
					$date=$sql2->row['VAL_AGG'];
					//echo $date;
				}
				$nome_esame=$es_val['TESTO']." $date";
				//echo "<hr>$nome_esame";
				if ($enabled){
					if (isset($in['ESAM']) && $in['ESAM']==$esam && $in['PROGR']==$es_progr) {
						if ($this_visit) $this->tab.="<li>{$es_val['HEADER']}<a href=\"#\" class=\"here\" onclick=\"return false;\">{$nome_esame}</a></li>\n";
						//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li><a href=\"#\" class=\"here\" onclick=\"return false;\"><font color=red>{$nome_esame}</font></a></li></td></tr>";
					}
					else {
						global $editing;
						if ($editing) {
							//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\" onclick=\"window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$es_progr}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;\">{$nome_esame}</a></li></td></tr>";

							if ($this_visit) $this->tab.="<li>{$es_val['HEADER']}<a href=\"$link\"
								onclick=\"
					window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$es_progr}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;
				\">{$nome_esame}</a></li>\n";
						}
						else {
							if ($this_visit) $this->tab.="<li>{$es_val['HEADER']}<a href=\"$link\">{$es_val['TESTO']}</a></li>\n";
							//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\">{$nome_esame}</a></li></td></tr>";
						}
					}
				}
			}
		}
		else{
			//print_r($es_val);
			if (isset($es_val['RES']) && is_array($es_val['RES'])) foreach($es_val['RES'] as $res_key => $vals) {
				if ($vals['ABILITATO']=='1') $enabled=true;
			}
			if ($enabled){
				if (isset($in['ESAM']) && $in['ESAM']==$esam) {
					if ($this_visit) $this->tab.="<li>{$es_val['HEADER']}<a href=\"#\" class=\"here\" onclick=\"return false;\">{$es_val['TESTO']}</a></li>\n";
					//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li><a href=\"#\" class=\"here\" onclick=\"return false;\"><font color=red>{$es_val['TESTO']}</font></a></li></td></tr>";
				}
				else {
					global $editing;
					if ($editing) {
						//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\" onclick=\"window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$vals['PROGR']}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;\">{$es_val['TESTO']}</a></li></td></tr>";
						if ($this_visit) $this->tab.="<li>{$es_val['HEADER']}<a href=\"$link\"
								onclick=\"
					window.open('confirm_tab_change.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&VISITNUM={$key}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$esam}&PROGR={$vals['PROGR']}','finestraindipendente','scrollbars=yes,resizable=yes,width=600,height=400'); return false;
				\">{$es_val['TESTO']}</a></li>\n";
					}
					else {
						if ($this_visit) $this->tab.="<li>{$es_val['HEADER']}<a href=\"$link\">{$es_val['TESTO']}</a></li>\n";
						//$this->visit_menu.="<tr><td class=sc4bis style=\"font-size:xx-small\"><li>&nbsp;&nbsp;<a href=\"$link\">{$es_val['TESTO']}</a></li></td></tr>";
					}
				}
			}
		}
	}

	/**
	 * Sostituisce l'ultima occorenza di $search
	 *
	 * @param unknown_type $search
	 * @param unknown_type $replace
	 * @param unknown_type $subject
	 * @return unknown
	 */
	function str_lreplace($search, $replace, $subject)
	{
		$pos = strrpos($subject, $search);

		if($pos === false)
		{
			return $subject;
		}
		else
		{
			return substr_replace($subject, $replace, $pos, strlen($search));
		}
	}


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
							<tr class=int>
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
							if($this->config_service['mostraDataInvio']){
								$show_all.="
									document.getElementById('table_af_{$key}_{$nro}').className='';
								";
							}
							else{
								$show_all.="
									document.getElementById('af_{$key}_{$nro}').style.display='';
								";
							}
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
								$tb_header.="<th valign=top class=int>$l_content</th>";
							}

							$table="<table width=100%><tr>$tb_header</tr><tr>$tb_content</tr></table>";
							$display="none";
							}
							else {
								$table='';
								$display='';
							}
							
							$onclick="";
							if($this->config_service['mostraDataInvio']){
								
								$header_dateinv="<td class=\"int\"  align=\"left\">".$this->testo('inviato_corretto_da')."</td>
							<td class=\"int\"  align=\"left\">".$this->testo('data_invio')."</td>
							";
								$css='<style>
							   .hide tr {
								display:none;
								}
								.hide tr.int {
								display:table-row !important;
								}
								</style>
								';
								$this->body.="
							<tr>
								<td valign=top class=sc4bis>
								$css
									&nbsp;<b>$nro_label.</b>
								</td>
								<td colspan=2>
								<table style=\"border:2px solid\" width=100% id=\"table_af_{$key}_{$nro}\" >
									<tr class=int>
										<td colspan=2 width=70%>
											$table
										</td>
										{$header_dateinv}
										<td valign=top align=center>
										$delete_button<br/>
											<a href=\"#\" onclick=\"var table=document.getElementById('table_af_{$key}_{$nro}');if(table.className=='') {table.className+='hide';} else table.className='';return false;\">Mostra/nascondi schede</a>
										</td>
									</tr>
									";
							}
							else{
							$this->body.="
							<tr>
								<td valign=top class=sc4bis>
									&nbsp;<b>$nro_label.</b>
								</td>
								<td colspan=2>
								<table style=\"border:2px solid\" width=100%>
									<tr class=int>
										<td width=80%>
											$table
										</td>
										{$header_dateinv}
										<td valign=top align=center>
										$delete_button<br/>
											<a href=\"#\" onclick=\"show_hide('af_{$key}_{$nro}'); return false;\">Mostra/nascondi schede</a>
										</td>
									</tr>
									<tr>
										<td colspan=2>
											<table id='af_{$key}_{$nro}' align=\"center\" style=\"display:$display;border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        					";
							}
							foreach ($vesam as $esam => $es_val){
								if ($vprogr==null) $vprogr="0";

								if ($es_val['RES'][1]['ABILITATO']=='1') {
									
									$this->print_esams($es_val,$key,$esam, $vprogr);
									if($this->config_service['mostraDataInvio']){
										$this->body=$this->str_lreplace('</tr>',"<td class=sc4bis  align=\"left\">&nbsp;</td></tr>",$this->body);
									}
								}
							}
							if($this->config_service['mostraDataInvio']){
									$this->body.="
												
									</table>
								</td>
							</tr>";
							}
						
							else
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
						if($this->config_service['mostraDataInvio']){

							$header_dateinv="<td class=\"int\"  align=\"left\">".$this->testo('inviato_corretto_da')."</td>
							<td class=\"int\"  align=\"left\">".$this->testo('data_invio')."</td>";
						}
						$this->body.="
		  		<table border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        	<tr>
							<td class=\"int\" colspan=2 align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"sc2b\">".$val['TEXT']."</a>
						$show_hide_link
							</td>
							{$header_dateinv}
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
			document.getElementById('close_all_p').innerHTML='<input type=\"button\" value=\"{$js_close_all}\" onclick=\"if (confirm(\\'Attenzione!Preseguendo non sar� possibile effettuare modifiche alla pratica.\\'))window.location.href=\\'index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\\';else return false;\">';
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
		$this->body.="</p>";
		return $this->body;
	}

	/**
	 * Restituisce il codice html dell esame $esam della visita $key
	 * ($key=VISITNUM)
	 * @param array $es_val
	 * @param number $key
	 * @param number $esam
	 */
	function print_esams($es_val, $key, $esam, $vprogr=0){
		if($es_val['HEADER']!="")$header="<tr><td class=\"sc4bis\"></td><td class=\"int exam_header\" style=\"text-align:left;\">{$es_val['HEADER']}</td></tr>";
		if ($vprogr!=null) $agg_param="&VISITNUM_PROGR={$vprogr}";
		else $agg_param="";
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		global $service;
		$nome_form=$es_val['TESTO'];
		//ESAMI NON PROGRESSIVO
		if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
			$img="to_be_comp.gif";
			$progr=1;
			if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
			if ($es_val['RES'][$progr]['INIZIO']=='0' || $es_val['RES'][$progr]['INIZIO']=='') $img="to_be_comp.gif";
			if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
			if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
			if($this->config_service['mostraDataInvio']){
				$file_form=$es_val['XML'];
				$form1= new xml_form( $this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir );
				$form1->xml_form_by_file($xml_dir."/".$file_form);
				$f_table=$form1->form['TABLE'];
				$dateinv=$this->getInsData($f_table,$in[$config_service['PK_SERVICE']],$key,$vprogr,$esam, $progr );
				$agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
											</td>";
			}
			$date=$es_val['RES'][$progr]['INSERTDT'];
			if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes' && $es_val['RES'][$progr]['FINE']!='1' ){
				if($in['USER_TIP']!='DE' && $es_val['RES'][$progr]['USERID']!=$in['remote_userid']) return;
			}
			//agg da mod  di alejandra nelle lib vecchie
			if ($es_val['FOTH'] && ($es_val['RES'][$progr]['FINE']=='1' || $es_val['FOTH_ALWAYS']=='yes'))
			{
				if(isset($es_val['EOTH']) && $es_val['EOTH']!=='')$esam_oth=$es_val['EOTH'];
				else $esam_oth=$es_val['NUMBER'];
				//per ottenere un foth preciso
				if($es_val['FOTH_SAME_FORM']!=""){
					$add_foth_where=" and visitnum_progr=:visitnum_progr and progr=:progr";
					unset($bind_data);
					$bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
					$bind_data['ESAM']=$esam_oth;
					$bind_data['VISITNUM_PROGR']=$vprogr;
					$bind_data['PROGR']=$progr;
				}
				else {
					$add_foth_where="";
					unset($bind_data);
					$bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
					$bind_data['ESAM']=$esam_oth;
					
				}
				$query_data="select {$es_val['FOTH']} as FOTH from {$config_service['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}=:pk_service and esam=:esam {$add_foth_where}";
//				echo "$query_data";
				$sql2=new query($conn);
				//$sql2->set_sql($query_data);
				
				$sql2->exec($query_data,$bind_data);//binded
				$sql2->get_row();
				$foth=$sql2->row['FOTH'];
				$nome_esame=$es_val['TESTO'].$foth;
//				echo $date;
			}
			else{
			$nome_esame=$es_val['TESTO'];
			}
			if($es_val['INS_DATE']=='yes'){
				$nome_esame.=$date;
			}
			//end alej mod


			if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
			if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1')
			{
				$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=1&amp;form=".$es_val['XML']."{$agg_param}\">";
				$close_href="</a>";
				if ($es_val['INDENT']=='yes') $indent="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
				else $indent="";
				$img_tag="<img src=\"/images/$img\" border=\"0\">";
				//if ($in['USER_TIP']=='DM') $img_tag='';
				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
					$agg_where='';
					if ($vprogr!=null) $agg_where="and VISITNUM_PROGR={$vprogr}";
					$sql_query="select count(*) as c from {$service}_eqfield where
					esam={$esam}
					and visitnum=$key
					and progr=$progr
					$agg_where
					and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
					and eq_int={$this->integrazione->eq_int}
					";
					$sql2=new query($this->conn);
					$sql2->get_row($sql_query);
					if ($sql2->row['C']>0){
						$img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
						//$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
						$nome_esame.="</a><b>(scheda modificata in fase di integrazione)</b>";
					}
				}
				if ($es_val['RES']['1']['EQ_ACTION']==1){
					$img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
					$nome_esame.="</a><b>(scheda aggiunta in fase di integrazione)</b>";
				}
			if ($es_val['RES']['1']['EQ_ACTION']==2){
					$img_tag="<img src=\"images/iphone_delete_icon.png\" width=\"15px\" title=\"La scheda rimossa in fase di integrazione\">".$img_tag;
					$nome_esame.="</a><b>(scheda rimossa in fase di integrazione)</b>";
				}
				$this->body.="{$header}
									<tr>
										 <td class=\"sc4bis\" width=\"10%\" align=\"center\">{$indent}{$href}{$img_tag}{$close_href}
										 </td>
										<td class=\"sc4bis\" align=\"left\">{$indent}$href".$nome_esame."$close_href<br/>
										</td>
{$agg_dateinv}
									</tr>
										";
			}
		}
		//ESAMI PROGRESSIVI
		else {
// 			print_r($es_val);
			//echo "<li>$key, $esam, $vprogr</li>";
			$last_progr=0;
			$form_alt='';
			//print_r($es_val);
			if (isset($es_val['RES']) && !isset($es_val['CORR'])){
				//print_r($es_val);
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
// 						echo "<hr>$last_progr -  $es_progr";
						//print_r($es_val);
						
						if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
						if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
						if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";

						$last_progr=$es_progr;
					}
					$n_progr=0;
					$init=false;
					$all_completed=true;
					$eq_present=false;
					$add_text='';
					$count_added=0;
					$count_deleted=0;
					$all_deleted=true;
					$all_added=true;
					
					$deleted=false;
				$added=false;
				$modified=false;
				
				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
					$agg_where='';
					if ($vprogr!=null) $agg_where="and VISITNUM_PROGR={$vprogr}";
					$sql_query="select count(*) as c from {$service}_eqfield where
					esam={$esam}
					and visitnum=$key
					$agg_where
					and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
					and eq_int={$this->integrazione->eq_int}
					and action=0
					";
					$sql2=new query($this->conn);
					$sql2->get_row($sql_query);
					if ($sql2->row['C']>0){
						$modified=true;
					}
				}
				
					$unset_viewable_on_close=false;
					foreach ($es_val['RES'] as $keys => $val) {
						if(isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes' && $in['USER_TIP']!='DE'){
							if ($val['FINE']=='1' || $val['USERID']==$this->session_vars['remote_userid']) $n_progr++;
							if( $val['USERID']==$this->session_vars['remote_userid'])$unset_viewable_on_close=true;
						}
						else{
							if ($val['INIZIO']=='1') $n_progr++;
						}
						if ($val['INIZIO']=='' || $val['INIZIO']=='0') $img="to_be_comp.gif";
						if ($val['INIZIO']=='1') $init=true;
						if ($val['FINE']!='1') $all_completed=false;
						if ($val['INV_QUERY']!='') $eq_present=true;
						if ($val['EQ_ACTION']==2) {
							$all_added=false;
							$count_deleted++;
							$deleted=true;
						}
						if ($val['EQ_ACTION']==1) {
							$all_deleted=false;
							$count_added++;
							$added=true;
						}
						
					}
					if($unset_viewable_on_close)unset($es_val['VIEWABLE_ON_CLOSE']);
					if ($add_text!='' && $all_added) $add_text="</a><b>(Schede aggiunte in fase di integrazione)</b>";
					if ($add_text!='' && $all_deleted) $add_text="</a><b>(Schede rimosse in fase di integrazione)</b>";
					if ($modified||$added||$deleted){
						$kind="";
						if ($deleted){
							if ($kind!='') $kind.="/";
							$kind.="eliminate";
						}
						if ($added){
							if ($kind!='') $kind.="/";
							$kind.="aggiunte";
						}
						if ($modified){
							if ($kind!='') $kind.="/";
							$kind.="modificate";
						}
						$add_text="</a><b>(Schede $kind in fase di integrazione)</b>";
					}

			
					if(isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes' && $in['USER_TIP']!='DE'){
						if($n_progr==0){
							return ;
						}
						else{
							$all_completed=true;
						}
					}
					if ($init) $img="saved.gif";
					if ($all_completed)  $img="submitted.gif";
					if ($n_progr==0) {
						$img="to_be_comp.gif";
						if($this->true_false['configurato'])
						$n_progr=$this->testi['nuovo_inserimento'];
						else
						$n_progr="Nuovo inserimento";
					}

					if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes'){
						$count_fine=0;
						foreach ($es_val['RES'] as $k_idx=>$val_idx){
							if ($val_idx['FINE']==1 || $val_idx['USERID']==$in['remote_userid']) {

								$count_fine++;
							}
						}
						$n_progr=$count_fine;
						if ($count_fine==0){
							$img="to_be_comp.gif";
						}
					}
					$date=" (".$n_progr.") ".$date;
					$nome_esame=$es_val['TESTO']." $date";
					$nome_esame.=$add_text;
					if ($progr!='') {
						$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}
						and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1 and visitnum_progr=$vprogr";
						
						unset($bind_chiusa);
						$bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
						$bind_chiusa['VISITNUM']=$key;
						$bind_chiusa['ESAM']=$esam;
						$bind_chiusa['VISITNUM_PROGR']=$vprogr;
						$bind_chiusa['PROGR']=$progr;
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
						unset($bind_chiusa);
						$bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
						$bind_chiusa['VISITNUM']=$key;
						$bind_chiusa['ESAM']=$esam;
						$bind_chiusa['VISITNUM_PROGR']=$vprogr;
						
					}
					
					$sql2=new query($conn);
					//$sql2->set_sql($sql_query);
					$sql2->exec($sql_query,$bind_chiusa);//binded
					if ($sql2->numrows>0){
						$sql2->get_row();
						if ($in['USER_TIP']=='DE' && !$archiviata  && $sql2->row['CHIUSA']=='0' && ($es_val['RES'][$es_progr]['FINE']!='1' || $sql2->row['FINE']=='0')) {
							$nome_esame.="<font color=red>(da revisionare)</font>";
						}
					}
					if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
						$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";
						if ($es_progr!=''){
								}

						$close_href="</a>";
						$img_tag="<img src=\"/images/$img\" border=\"0\">";
						if ($deleted||$modified||$added){
							$img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;
						}

						$this->body.="{$header}
													<tr>
														 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
														</td>
														<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
														</td>
														<!--td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
														</td-->
													</tr>
												";
					}
				}
				else{
					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							$date="";
							if($this->config_service['mostraDataInvio']){
								$file_form=$es_val['XML'];
								$form1= new xml_form( $this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir );
								$form1->xml_form_by_file($xml_dir."/".$file_form);
								$f_table=$form1->form['TABLE'];
								$dateinv=$this->getInsData($f_table,$in[$config_service['PK_SERVICE']],$key,$vprogr,$esam, $es_progr );
								$agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
											</td>";
							}
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
								if($es_val['WOTH']!=''){
                                    $add_foth_where="and ({$es_val['WOTH']})";
                                }
                                else{
                                    $add_foth_where="";
                                }
                                $query_data="select {$es_val['FOTH']} as FOTH from {$GLOBALS['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}=:pk_service and  progr=:progr and visitnum_progr=:visitnum_progr ".$add_foth_where;
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
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}
							if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
							$n_progr=$es_progr;
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
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	{$agg_dateinv}
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}

							foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
								if ($es_val_corr['CORR']!='' && $es_val_corr['CORR']==$esam && ($es_val_corr['CORR_ON_SEND']!='yes' || $es_val['RES'][$es_progr]['FINE']==1)){
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
									//echo "<hr>$date<hr>";
									$n_progr=$es_progr;
									if ($date!='') 	$dtp=" n.{$n_progr} ($date)";
									$nome_esame=$es_val_corr['TESTO']." $dtp";
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
									if($this->config_service['mostraDataInvio']){
										$file_form=$es_val_corr['XML'];
										$form1= new xml_form( $this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir );
										$form1->xml_form_by_file($xml_dir."/".$file_form);
										$f_table=$form1->form['TABLE'];
										$dateinv=$this->getInsData($f_table,$in[$config_service['PK_SERVICE']],$key,$vprogr,$es_val_corr['NUMBER'], $es_progr );
										$agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
											</td>";
									}
									$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=".$es_val_corr['NUMBER']."&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
									$close_href="</a>";
									$this->body.="{$header}
										<tr>
											 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
											</td>
											{$agg_dateinv}
											<!--td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
											</td-->
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
					if($this->config_service['mostraDataInvio']){
						
						$agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;</b>
											</td>
											<td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;</b><br/>
											</td>";
					}
					if ($es_val['CONT_FORM']!='yes' && $es_val['DISABLE_NEW']=='' && $in['USER_TIP']!='RO')$this->body.="
													<tr>
														<td class=\"sc4bis\" width=\"10%\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."{$agg_param}\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
														</td>
														<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$form_alt."{$agg_param}\">{$this->testi['nuovo_inserimento']}: ".$es_val['TESTO']."</a><br/>
														</td>
														{$agg_dateinv}
														<!--td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\">&nbsp;<br/>
														</td-->
													</tr>
											";
				}
			}
		}
	}
	

	
	
	function getInsData($f_table,$pk_service,$visitnum,$visitnum_progr,$esam, $progr){
		global $conn;
		$dateinv=array('','');

		//TODO sistemare il binding!!!
		$query_invio="select a.NOME||' '||a.COGNOME||' '||a.AZIENDA_ENTE NOME,
			to_char(nvl( MODDT ,INSERTDT), 'DD/MM/YYYY') as DATAINS
			from $f_table t,{$this->config_service['service']}_COORDINATE c, ANA_UTENTI_1 a where t.{$this->config_service['PK_SERVICE']}=:pk_service 
			and a.userid=t.USERID_INS 
			and t.{$this->config_service['PK_SERVICE']}=c.{$this->config_service['PK_SERVICE']} 
			and t.esam=c.esam 
			and t.visitnum=c.visitnum 
			and t.VISITNUM_PROGR=c.VISITNUM_PROGR
			and t.PROGR=c.PROGR 
			and t.PROGR=:progr 
			and t.VISITNUM=:visitnum 
			and t.VISITNUM_PROGR=:visitnum_progr 
			and t.esam=:esam";
		
		$bind['pk_service']=$pk_service;
		$bind['VISITNUM']=$visitnum;
		$bind['VISITNUM_PROGR']=$visitnum_progr;
		$bind['ESAM']=$esam;
		$bind['PROGR']=$progr;
		$sql_invio=new query($conn);
		$sql_invio->exec($query_invio,$bind);
		$sql_invio->get_row();

		if ($sql_invio->row['NOME']!='') $dateinv[0].=$sql_invio->row['NOME'];
		if ($sql_invio->row['DATAINS']!='') $dateinv[1].=$sql_invio->row['DATAINS'];
		return $dateinv;
	}

	/**
	 * Vista alternativa di visualizzazione delle form
	 *
	 * @return string
	 */
	function esams_list_html_view(){
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		global $es_form;
		$query="select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$this->PK_SERVICE}=:pk_service order by visitnum,progr";
		//	  	echo "<hr>$query<hr>";
		//		echo $in[$this->PK_SERVICE]."<hr>";
		$sql=new query($conn);
		$bind_pk['PK_SERVICE']=$in[$this->PK_SERVICE];
		$sql=new query($conn);
		//$sql->set_sql($query);
		$sql->exec($query,$bind_pk);//binded
		$esams_html="";
		while ($sql->get_row()){
			if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
			}
		}
		//	  	print_r($this->esams);
		foreach ($this->visitnums as $key => $val) {
			if (!isset($in['VISITNUM']) || $in['VISITNUM']==$key){
				$this->body.="
		  		<table class=\"bordi\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"95%\">
// 	        	<!--<tr>
// 							<td class=\"int\" align=\"left\"><b>".$val['TEXT']."</b></td>
// 						</tr>
// 						</table>
// 						<table class=\"tabgrigia\" align=\"center\" border=\"0\" cellspacing=\"0\" width=\"95%\">-->
// 					      <!--tr>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"15%\"><b>Status</b></td>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"35%\"><b>Form name</b></td>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Due date</b></td>
// 					      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Received date</b></td>
// 					     </tr-->
						";
				foreach ($this->esams[$key] as $esam => $es_val){
					$nome_form=$es_val['TESTO'];
					//ESAMI NON PROGRESSIVO
					if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
						$img="to_be_comp.gif";
						$progr=1;
						if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
						#echo "<hr>$key - $esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
						if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
						if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
						if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
						$date=$es_val['RES'][$progr]['INSERTDT'];
						$nome_esame=$es_val['TESTO'];
						if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
						#if ($es_val['RES'][$progr]['FINE']=='1' && $in['USER_TIP']=='DE') $nome_esame.="&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;equery=".$es_val['XML']."\">invia e-query";
						if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
							#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=".$progr."&amp;form=".$es_val['XML']."\">";
							#$close_href="</a>";
							//										$this->body.="
							//									<tr>
							//										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
							//										</td>
							//										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame."$close_href<br/>
							//										</td>
							//										<!--td class=\"sc4bis\" align=\"center\">
							//										</td>
							//										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
							//										</td-->
							//										</tr>
							//										";
							$in['VISITNUM']=$key;
							$in['ESAM']=$esam;
							$in['PROGR']=$progr;
							//										$in['CENTER']=$progr;
							$xml_form=new xml_form();
							//echo "$key -- $esam --{$es_form[$key][$esam]}<hr>";
							$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam]);
							if ($xml_form->closed_form()) {
								$xml_form->close_form();
								$esam_html.="".$xml_form->body;
								$tab="<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
								$esam_html=preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
							}
							unset($in['VISITNUM']);

						}
					}
					//ESAMI PROGRESSIVI
					else {
						if (isset($es_val['RES']) && !isset($es_val['CORR'])){
							foreach ($es_val['RES'] as $es_progr => $progr_vals){
								//										echo "<hr>$es_progr - ";
								#print_r($es_val);
								if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
									#echo "<hr>2 $es_progr - ";
									if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
									if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
									if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
									$date="";
									$date=$es_val['RES'][$es_progr]['INSERTDT'];
									if ($date!='') $date="($date)";
									$nome_esame=$es_val['TESTO']." $date";
									#echo "<hr>{$es_val['TESTO']} - $date";
									#if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val['XML']."\">invia e-query";
									if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
										#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
										#$close_href="</a>";
										//														$this->body.="
										//															<tr>
										//																 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
										//																</td>
										//																<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
										//																</td>
										//																<!--td class=\"sc4bis\" align=\"center\">
										//																</td>
										//																<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
										//																</td-->
										//															</tr>
										//														";
										$in['VISITNUM']=$key;
										$in['ESAM']=$esam;
										$in['PROGR']=$es_progr;
										$xml_form=new xml_form();
										$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam]);
										if ($xml_form->closed_form()) {
											$xml_form->close_form();
											$esam_html.="".$xml_form->body;
											$tab="<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
											$esam_html=preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
										}
										unset($in['VISITNUM']);
										unset($in['ESAM']);
										unset($in['PROGR']);
									}
									foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
										#echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
										if ($es_val_corr['CORR']==$esam  && ($es_val_corr['CORR_ON_SEND']!='yes' || $es_val['RES'][$es_progr]['FINE']==1)){
											#echo "<hr> Esame correlato per $esam : ".$esam_corr;
											$img="to_be_comp.gif";
											//											print_r($es_val_corr);
											#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
											if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
											if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
											if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
											#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
											$dtp='';
											$date="";
											$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
											#echo "<hr>$date<hr>";
											if ($date!='') 	$dtp="($date)";
											$nome_esame=$es_val_corr['TESTO']." $dtp";
											#if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;equery=".$es_val_corr['XML']."\">invia e-query";
											#$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
											#$close_href="</a>";
											//										$this->body.="
											//									<tr>
											//										 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											//										</td>
											//										<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
											//										</td>
											//										<!--td class=\"sc4bis\" align=\"center\">
											//										</td>
											//										<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
											//										</td-->
											//										</tr>
											//										";
											$in['VISITNUM']=$key;
											$in['ESAM']=$esam_corr;
											$in['PROGR']=$es_progr;
											$xml_form=new xml_form();
											$xml_form->xml_form_by_file($xml_dir.'/'.$es_form[$key][$esam_corr]);
											if ($xml_form->closed_form()) {
												$xml_form->close_form();
												$esam_html.="".$xml_form->body;
												$tab="<HR BREAK><table class=\"sf\" align=\"center\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\" width=\"80%\"><tr>";
												$esam_html=preg_replace("/<!--FINE CAMPI-->(.*?)<!-- CAMPI -->/sm", "$tab", $esam_html);
											}
											unset($in['VISITNUM']);
											unset($in['ESAM']);
											unset($in['PROGR']);
										}
									}
								}

							}

						}
					}
				}
			}
			$this->body.="</table>";
		}
		/*PARTE RELATIVA ALLA CHIUSURA DELLA VISITA
		if ($in['VISITNUM']!=''){
		$query="select min(fine) as fine, min(visitclose) as vclose from ".$GLOBALS['service']."_COORDINATE where {$this->PK_SERVICE}='".$in[$this->PK_SERVICE]."' and VISITNUM='".$in['VISITNUM']."'";
		$sql->set_sql($query);
		$sql->exec();//commentata
		$sql->get_row();
		if($sql->row['FINE']=='1' && $sql->row['VCLOSE']!='1') $this->body.="
		<table border=0 cellspacing=0 cellpadding=0 align=center><tr><td>
		<form method=post action='index.php' align=center>
		<input type='hidden' name=$this->PK_SERVICE value='".$in[$this->PK_SERVICE]."'>
		<input type='hidden' name='VISITNUM' value='".$in['VISITNUM']."'>
		<input type='hidden' name='CENTER' value='".$in['CENTER']."'>
		<input type='hidden' name='exams' value='visite_exams.xml'>
		<input type='submit' name='close_visit' value='Close Visit' align=center>
		</form>
		</td></tr></table>
		";
		}*/
		/*$this->body.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Vista individuale</a>
		<br/><a href=\"index.php?exams=visite_exams.xml&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Individual Patient Exam List</a>
		<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Procuratori registrati </a></p>";
		*/

		$this->body.=$esam_html;

		return $this->body;
	}

	/**
	 * Restituisce il codice html delle form raggrupate
	 *
	 * @return string
	 */
	function esams_group_html(){
		$in=$this->session_vars;
		$conn=$this->conn;


		$query="select visitnum, esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato from ".$GLOBALS['service']."_COORDINATE where {$this->PK_SERVICE}=:pk_service order by progr";
		#echo $query;
		$bind_pk['PK_SERVICE']=$in[$this->PK_SERVICE];
		$sql=new query($conn);
		//$sql->set_sql($query);
		$sql->exec($query,$bind_pk);//binded
		while ($sql->get_row()){
			if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
				$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
			}
		}
		#print_r
		foreach ($this->group[$in['GROUP']]['VISIT'] as $grp => $val_grp){
			#echo "<hr>$grp<hr>";
			$in['VISITNUM']=$grp;
			foreach ($this->visitnums as $key => $val) {
				if (!isset($in['VISITNUM']) || $in['VISITNUM']==$key){
					$this->body.="
			  		<table class=\"bordi\" border=\"0\" bordercolor=\"#c0c0c0\" cellpadding=\"2\" cellspacing=\"2\" width=\"100%\">
		        	<tr>
								<td class=\"int\" align=\"left\"><a href=\"index.php?{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=".$val['NUMBER']."&exams=".$GLOBALS['visit_structure_xml']."\" class=\"sc2b\">".$val['TEXT']."</a></td>
							</tr>
							</table>
							<table class=\"tabgrigia\" align=\"center\" border=\"0\" cellspacing=\"0\" width=\"95%\">
						      <!--tr>
						      <td class=\"sc4bis\" align=\"center\" width=\"15%\"><b>Status</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"35%\"><b>Form name</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Due date</b></td>
						      <td class=\"sc4bis\" align=\"center\" width=\"25%\"><b>Received date</b></td>
						     </tr-->
							";
					foreach ($this->esams[$key] as $esam => $es_val){
						$nome_form=$es_val['TESTO'];
						//ESAMI NON PROGRESSIVO
						if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
							$img="to_be_comp.gif";
							$progr=1;
							if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
							#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
							if ($es_val['RES'][$progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
							$date=$es_val['RES'][$progr]['INSERTDT'];
			$nome_esame=$es_val['TESTO'];
						if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1'){
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$progr&amp;form=".$es_val['XML']."\">";
								$close_href="</a>";
								$this->body.="
										<tr>
											 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href".$es_val['TESTO']."$close_href<br/>
											</td>
											<td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
											</td>
											</tr>
											";
							}
						}
						//ESAMI PROGRESSIVI
						else {
							if (isset($es_val['RES']) && !isset($es_val['CORR'])){
								foreach ($es_val['RES'] as $es_progr => $progr_vals){
									#echo "<hr>$es_progr - ";
									#print_r($progr_vals);
									if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
										#echo "<hr>2 $es_progr - ";
										if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
										if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
										if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
										$date=$es_val['RES'][$es_progr]['INSERTDT'];
										$nome_form=$es_val['TESTO']." ($date)";
										if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
											$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."{$agg_param}\">";
											$close_href="</a>";
											$this->body.="
																<tr>
																	 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$es_val['TESTO']."($date) $close_href<br/>
																	</td>
																	<td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
																	</td>
																</tr>
															";

										}

										foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
											#echo "<br/>$esam_corr - $esam -".$es_val_corr['CORR'];
											if ($es_val_corr['CORR']==$esam  && ($es_val_corr['CORR_ON_SEND']!='yes' || $es_val['RES'][$es_progr]['FINE']==1)){
												# echo "<hr> Esame correlato per $esam : ".$esam_corr;
												$img="to_be_comp.gif";
												#echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
												if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
												if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
												if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
												#$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
												$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam_corr&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
												$close_href="</a>";
												$this->body.="
										<tr>
											 <td class=\"sc4bis\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
											</td>
											<td class=\"sc4bis\" align=\"left\">$href".$es_val_corr['TESTO']."($date) $close_href<br/>
											</td>
											<td class=\"sc4bis\" align=\"center\">
											</td>
											<td class=\"sc4bis\" align=\"center\"><b>$date</b>&nbsp;<br/>
											</td>
											</tr>
											";
											}
										}
									}

								}
								$next_progr=$es_progr+1;
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;&amp;form=".$es_val['XML']."{$agg_param}\">";
								$close_href="</a>";
								$this->body.="
													<tr>
														<td class=\"sc4bis\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."{$agg_param}\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
														</td>
														<td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$next_progr&amp;form=".$es_val['XML']."{$agg_param}\">New ".$es_val['TESTO']."</a><br/>
														</td>
														<td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\">&nbsp;<br/>
														</td>
													</tr>
											";
							}
						}
					}
				}
			}
		}
		$this->body.="</table><p align=right><a href=\"index.php?list=patients_list.xml&{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Menu Procuratore</a>
	  	<br/><a href=\"index.php?exams=".$GLOBALS['visit_structure_xml']."&{$this->PK_SERVICE}=".$in[$this->PK_SERVICE]."&CENTER=".$in['CENTER']."\">Vista individuale</a>
	  	<br/><a href=\"index.php?list=patients_list.xml&CENTER=".$in['CENTER']."\">Lista Procure</a></p>";
		return $this->body;
	}
	
	

}

?>
