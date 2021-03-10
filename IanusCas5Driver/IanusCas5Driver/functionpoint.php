<?php
class FPTracker{
	private static $instance;
	private static $conn;
	private static $sessionStarted=false;
	private static $session;
	private static $recording=false;
	private static $currentFP;
	private function __construct($conn){
		self::$conn=$conn;
		if($this->servizioSupportato()){
			if(!$this->isInitializedDB()){
				$this->initializeDB();
			}
			if($this->isTrackUser()){
				$this->startSession();
			}
		}
	}
	private static function newQuery(){
		return new DriverIanusSql(self::$conn);
	}
	public static function newFPTracker($conn){
		if(!isset(self::$instance)){
			self::$instance=new FPTracker($conn);
		}
		return self::$instance;
	}
	function isInitializedDB(){
		$query=self::newQuery();
		$str="select count(*) conto from user_tables where table_name='TRACK_FP_USERS'";
		$query->getRow($str);
		if($query->row['CONTO']>0)
		return true;
		else{
			return false;
		}
	}
	function isTrackUser(){
		$query=self::newQuery();
		$str="select count(userid) conto from TRACK_FP_USERS where userid='{$_SERVER['REMOTE_USER']}'";
		$query->getRow($str);
		if($query->row['CONTO']>0 || $_COOKIE['track_session']){
			return true;
		}
		else{
			if($_GET['tracker_session']=='true'){
				setcookie("track_session",1);
				return true;
			}
			return false;
		}
	}
	function startSession(){
		//session_set_cookie_params(0, $parts['path'], $parts['host']);
		session_start();
		if($_GET['force_session']!=""){
			self::$session=$_GET['force_session'];
		}
		else
		self::$session=session_id();
		if($_GET['perl'])setcookie("track_session_perl",self::$session);
		$query=self::newQuery();
		$str="select * from track_fp_sessions where php_session='".self::$session."'";
		if($query->getRow($str)){
			if($query->row['TRACKING']) {
				self::$recording=true;
				self::$currentFP=$query->row['CURRENT_FP'];
			}
			if($_GET['analyzeFP']>0) {
				$this->analyzeFP($_GET['analyzeFP']);
			}
			if($_GET['trackQuery']!="") {
				self::trackQuery($_GET['trackQuery']);
				die("ok");
			}
			if($_GET['listaFP']=='true') {
				$this->listaFP();
				die();
			}
			if($_GET['start_record']=='true'){
				$this->startRecord();
				header("Location: tracker?tracker_bar=true");
				die();
			}
			if($_GET['stop_record']=='true'){
				$this->stopRecord();
				header("Location: tracker?tracker_bar=true");
				die();
			}
			if($_GET['tracker_bar']=='true'){
				$this->toolbar();
				die();
			}
			if($_GET['tracker_session']=='true'){
				$request=str_replace("tracker_session=true","",$_SERVER['REQUEST_URI']);
				echo "<html>
						<frameset rows=\"30px,100%\" frameborder=\"0\" >
							<frame src=\"tracker?tracker_bar=true\" style='overflow:hidden' >
				   			<frame src=\"{$request}\">
						</frameset>
					</html>";
				die();
			}
		}
		else {
			$values['PHP_SESSION']=self::$session;
			$values['USERID']=$_SERVER['REMOTE_USER'];
			$query->insert($values,'track_fp_sessions');
			self::commit();
			echo "<html>
						<frameset rows=\"30px,100%\" frameborder=\"0\" >
							<frame src=\"tracker?tracker_bar=true\" style='overflow:hidden' >
				   			<frame src=\"{$_SERVER['REQUEST_URI']}\">
						</frameset>
					</html>";
			die();
		}
	}
	function initializeDB(){
		$queries[]="
		create table TRACK_FP
			(
			  ID_FP       NUMBER,
			  PHP_SESSION VARCHAR2(100),
			  NOME_FP     VARCHAR2(200),
			  ENDED       NUMBER
			)
		";	
		$queries[]="
		create table TRACK_FP_QUERIES
			(
			  ID_FP    NUMBER,
			  ID_QUERY NUMBER not null,
			  QUERY    clob
			)
		";
		$queries[]="alter table TRACK_FP_QUERIES
					  add constraint PK_FP_QUERIES primary key (ID_QUERY)";
		$queries[]="create table TRACK_FP_USERS
					(
					  USERID VARCHAR2(40)
					)";
		$queries[]="create table TRACK_FP_TABLES
					(
					  ID_QUERY      NUMBER,
					  OWNER         VARCHAR2(40),
					  TABLE_NAME    VARCHAR2(40),
					  NUM_CAMPI_IN  NUMBER,
					  NUM_CAMPI_OUT NUMBER
					)";
		$queries[]="create table TRACK_FP_SESSIONS
					(
					  PHP_SESSION VARCHAR2(100) not null,
					  TRACKING    NUMBER default 0,
					  USERID      VARCHAR2(40),
					  CURRENT_FP  NUMBER
					)";
		$queries[]="alter table TRACK_FP_SESSIONS
					  add constraint PK_SESSIONS primary key (PHP_SESSION)";
		$queries[]="create sequence FP_SESSION_SEQ
minvalue 1
maxvalue 999999999999999999999999999
start with 1
increment by 1
nocache
";
		$queries[]="create sequence FP_QUERIES_SEQ
minvalue 1
maxvalue 999999999999999999999999999
start with 1
increment by 1
nocache";
		$queries[]="alter table TRACK_FP
  add constraint PK_TRACK_FP primary key (ID_FP)";
		$queries[]="alter table TRACK_FP_USERS
  add constraint PK_FP_USERS primary key (USERID)";
		$sql=self::newQuery();
		foreach ($queries as $query){
			$sql->doCommand($query);
		}
	}
	private function servizioSupportato(){
		$servizi['pandemia.sissdev.cineca.it']=true;
		$servizi['trasparenza.sissdev.cineca.it']=true;
		$servizi['medishare.sissdev.cineca.it']=true;
		$servizi['osservazionali.sissdev.cineca.it']=true;
		$servizi['oss-sper-clin.sissdev.cineca.it']=true;
		$servizi['rapporti-ue.sissdev.cineca.it']=true;
		$servizi['aifa-reuma.sissdev.cineca.it']=true;
		$servizi['aifa-neuro.sissdev.cineca.it']=true;
		$servizi['aifa-asma.sissdev.cineca.it']=true;
		$servizi['psocare.sissdev.cineca.it']=true;
		$servizi['oftalmologici.sissdev.cineca.it']=true;
		$servizi['cardiologici.sissdev.cineca.it']=true;
		$servizi['antidiabetici.sissdev.cineca.it']=true;
		$servizi['esperti.sissdev.cineca.it']=true;
		$servizi['aifa-emato.sissdev.cineca.it']=true;
		$servizi['antineoplastici.sissdev.cineca.it']=true;
		if($servizi[$_SERVER['SERVER_NAME']])
		return true;
		else {
			return  false;
		}
	}
	function startRecord(){
		$values['TRACKING']=1;
		$values['CURRENT_FP']="fp_session_seq.nextval";
		$pk['PHP_SESSION']=self::$session;
		$query=self::newQuery();
		$query->update($values,'track_fp_sessions',$pk);
		$values_fp['ID_FP']="fp_session_seq.currval";
		$values_fp['PHP_SESSION']=self::$session;
		$values_fp['NOME_FP']=$_GET['titolo'];
		$values_fp['ENDED']="0";
		$query->insert($values_fp,'track_fp');
		self::commit();
	}
	function stopRecord(){
		$values['TRACKING']=0;
		$values['CURRENT_FP']=0;
		$pk['PHP_SESSION']=self::$session;
		$query=self::newQuery();
		$query->update($values,'track_fp_sessions',$pk);
		$values_fp['ENDED']=1;
		$pk_fp['ID_FP']=self::$currentFP;
		$query->update($values_fp,'TRACK_FP',$pk_fp);
		self::commit();
	}
	function listaFP(){
		$str="select * from TRACK_FP order by id_fp asc";
		$query=self::newQuery();
		$query->Exec($str);
		while($query->getRow()){
			echo "<div><a href='?analyzeFP={$query->row['ID_FP']}'>{$query->row['NOME_FP']}</a></div>";
		}
		die();
	}
	function analyzeFP($fp){
		$query=self::newQuery();
		$select_queries="select min(ID_QUERY) ID_QUERY, QUERY from TRACK_FP_QUERIES where ID_FP={$fp} group by QUERY";
		$query->Exec($select_queries,$bind);
		$queryPlan=self::newQuery();
		if(!$query->numRows){
			$select_queries="select ID_QUERY,query from TRACK_FP_QUERIES where id_query in (select min(ID_QUERY) ID_QUERY from TRACK_FP_QUERIES where ID_FP={$fp} group by to_char(substr(QUERY,1,3999)))";
			$query->Exec($select_queries,$bind);
			$queryPlan=self::newQuery();
		}
		if($query->numRows>0){
		$select_plan="select count(*) conto from user_tables where table_name='FP_{$fp}_PLAN'";
		$queryPlanTable=self::newQuery();
		$queryPlanTable->getRow($select_plan);

		if($queryPlanTable->row['CONTO']==0){
			while($query->getRow()){
				$explain="explain plan for ".$query->row['QUERY'];
				$queryPlan->doCommand($explain);
			}
			$tablePlan="create table FP_{$fp}_PLAN as select statement_id,
plan_id, 
timestamp, 
remarks, 
operation, 
options, 
object_node, 
object_owner, 
object_name, 
object_alias, 
object_instance, 
object_type, 
optimizer, 
search_columns, 
id, 
parent_id, 
depth, 
position, 
cost, 
cardinality, 
bytes, 
other_tag, 
partition_start, 
partition_stop, 
partition_id, 
other_xml, 
distribution, 
cpu_cost, 
io_cost, 
temp_space, 
access_predicates, 
filter_predicates, 
projection, 
time, 
qblock_name from plan_table";
			//$plan_table="plan_table";
			$queryPlan->doCommand($tablePlan);
		}
			$str_select="select plan_id,object_owner||'.'||object_name object_fullname,object_owner,object_name,projection,operation from FP_{$fp}_PLAN where operation in ('TABLE ACCESS','MAT_VIEW ACCESS','LOAD TABLE CONVENTIONAL','UPDATE','DELETE')";
			$queryPlan->Exec($str_select);
			$queryUser=self::newQuery();
			$strUser="select user from dual";
			$queryUser->getRow($strUser);
			$user=$queryUser->row['USER'];
			while ($queryPlan->getRow()){
				unset($variables);
				if($queryPlan->row['OBJECT_OWNER']==$user) $tabelleInterne[$queryPlan->row['OBJECT_FULLNAME']]=$queryPlan->row['OBJECT_FULLNAME'];
				else $tabelleEsterne[$queryPlan->row['OBJECT_FULLNAME']]=$queryPlan->row['OBJECT_FULLNAME'];
				switch($queryPlan->row['OPERATION']){
					case 'TABLE ACCESS':
					case 'MAT_VIEW ACCESS':
						$variables=explode(", ",trim($queryPlan->row['PROJECTION']));
						foreach ($variables as $var){
							$curr_var=explode(".",$var);
							
							$var_name=$curr_var[count($curr_var)-1];
							$tableIn[$queryPlan->row['OBJECT_FULLNAME']][$var_name]=$var_name;
							$oldTableIn[$queryPlan->row['OBJECT_FULLNAME']][$var]=$var;
						}
						break;
					case 'DELETE':
					case 'LOAD TABLE CONVENTIONAL':
						$queryOut=self::newQuery();
						$str="select count(*) conto from all_tab_cols where table_name='{$queryPlan->row['OBJECT_NAME']}' and owner='{$queryPlan->row['OBJECT_OWNER']}'";
						$queryOut->Exec($str);
						$queryOut->getRow();
						$tableOutInsert[$queryPlan->row['OBJECT_FULLNAME']]=$queryOut->row['CONTO'];
						break;
					case 'UPDATE':
						$select_update="select projection from FP_{$fp}_PLAN where projection like '(upd=%' and plan_id={$queryPlan->row['PLAN_ID']}";
						$updateCalc=self::newQuery();
						$updateCalc->Exec($select_update);
						while($updateCalc->getRow()){
							preg_match("/\(upd=([0-9,]*).[^\)]*\)(.*)/",$updateCalc->row['PROJECTION'],$matches);
							$campi_index=explode(",",$matches[1]);
							$campi=explode(", ",trim($matches[2]));
							foreach ($campi_index as $index){
								$curr_var=explode(".",$campi[$index-1]);
								$var_name=$curr_var[count($curr_var)-1];
								$tableOutUpdate[$queryPlan->row['OBJECT_FULLNAME']][$var_name]=$var_name;
								$oldTableOutUpdate[$queryPlan->row['OBJECT_FULLNAME']][$campi[$index-1]]=$campi[$index-1];
							}
						}
						break;
					default:
						break;
				}
			}
			Logger::send($tableIn);
			Logger::send($tableOutInsert);
			Logger::send($tableOutUpdate);
		}
		$queryFP=self::newQuery();
		$strFP="select * from track_fp where ID_FP={$fp}";
		$queryFP->Exec($strFP);
		$queryFP->getRow();
		$lista_tabelle_in="";
		$lista_tabelle_in_interne="";
		$lista_tabelle_in_esterne="";
		$lista_tabelle_in_generica="";
		$lista_tabelle_out="";
		$lista_tabelle_out_interne="";
		$lista_tabelle_out_esterne="";
		$lista_tabelle_out_generica="";
		$n_field_in=0;
		$n_field_in_interne=0;
		$n_field_in_esterne=0;
		$n_field_out=0;
		$n_field_out_interne=0;
		$n_field_out_esterne=0;
		foreach ($tableIn as $key => $val){
			$lista_tabelle_in.="$key, ";
			$conto=count($val);
			$n_field_in+=$conto;
			$old_conto=count($oldTableIn[$key]);
			$old_n_field_in+=$conto;
			$difference=$old_conto-$conto;
			Logger::send("$key ($difference)");
			$lista_tabelle_in_generica.="$key ($conto), ";
			/*$ins_in_tabelle_list['TABELLA']=$key;
			$queryIns=self::newQuery();
			$queryIns->insert($ins_in_tabelle_list,'TABELLE_LIST');*/
			if($tabelleInterne[$key]){
				$lista_tabelle_in_interne.="$key, ";
				$n_field_in_interne+=count($val);
			}
			else {
				$lista_tabelle_in_esterne.="$key, ";
				$n_field_in_esterne+=count($val);
			}
		}
		foreach ($tableOutInsert as $key => $val){
			$lista_tabelle_out.="{$key}, ";
			$n_field_out+=$val;
			$lista_tabelle_out_generica.="$key ($val), ";
			/*$ins_in_tabelle_list['TABELLA']=$key;
			$queryIns=self::newQuery();
			$queryIns->insert($ins_in_tabelle_list,'TABELLE_LIST');*/
			if($tabelleInterne[$key]){
				$lista_tabelle_out_interne.="$key, ";
				$n_field_out_interne+=$val;
			}
			else {
				$lista_tabelle_out_esterne.="$key, ";
				$n_field_out_esterne+=$val;
			}
		}
		foreach ($tableOutUpdate as $key => $val){
			$lista_tabelle_out.="{$key}, ";
			$conto=count($val);
			$n_field_out+=$conto;
			$old_conto=count($oldTableOutUpdate[$key]);
			$old_n_field_in+=$conto;
			$difference=$old_conto-$conto;
			Logger::send("Update $key ($difference)");
			$lista_tabelle_out_generica.="$key ($conto), ";
			/*$ins_in_tabelle_list['TABELLA']=$key;
			$queryIns=self::newQuery();
			$queryIns->insert($ins_in_tabelle_list,'TABELLE_LIST');*/
			if($tabelleInterne[$key]){
				$lista_tabelle_out_interne.="$key, ";
				$n_field_out_interne+=count($val);
			}
			else {
				$lista_tabelle_out_esterne.="$key, ";
				$n_field_out_esterne+=count($val);
			}
		}
		//self::commit();
		$lista_tabelle_in=rtrim($lista_tabelle_in,", ");
		$lista_tabelle_in_interne=rtrim($lista_tabelle_in_interne,", ");
		$lista_tabelle_in_esterne=rtrim($lista_tabelle_in_esterne,", ");
		$lista_tabelle_in_generica=rtrim($lista_tabelle_in_generica,", ");
		$lista_tabelle_out=rtrim($lista_tabelle_out,", ");
		$lista_tabelle_out_interne=rtrim($lista_tabelle_out_interne,", ");
		$lista_tabelle_out_esterne=rtrim($lista_tabelle_out_esterne,", ");
		$lista_tabelle_out_generica=rtrim($lista_tabelle_out_generica,", ");
		echo "<div> calcolo automatico tabelle per task: <b>{$queryFP->row['NOME_FP']}</b>
		<p>
		Tutte tabelle sono considerate interne
		<table>
		<tr><td width='40%' /><td width='10%' /><td width='40%' /><td width='10%' /></tr>
		<tr><td>tabelle in</td><td>campi in</td><td>tabelle out</td><td>campi out</td></tr>
		<tr><td>{$lista_tabelle_in}</td><td>{$n_field_in}</td><td>$lista_tabelle_out</td><td>$n_field_out</td></tr>
		</table>
		</p><p>
		Tutte le tabelle dell'utente oracle sono considerate interne. Le tabelle di un altro utente sono considerate esterne.
		<table>
		<tr><td width='20%' /><td width='5%' /><td width='20%' /><td width='5%' /><td width='20%' /><td width='5%' /><td width='20%' /><td width='5%' /></tr>
		<tr><td>tabelle in (interne)</td><td>campi in</td><td>tabelle out (interne)</td><td>campi out</td><td>tabelle in (esterne)</td><td>campi in</td><td>tabelle out (esterne)</td><td>campi out</td></tr>
		<tr><td>{$lista_tabelle_in_interne}</td><td>{$n_field_in_interne}</td><td>$lista_tabelle_out_interne</td><td>$n_field_out_interne</td><td>{$lista_tabelle_in_esterne}</td><td>{$n_field_in_esterne}</td><td>$lista_tabelle_out_esterne</td><td>$n_field_out_esterne</td></tr>
		</table>
		</div><p>
		dettaglio per tabella (numero campi tra parentesi per ogni tabella)
		<table>
		<tr><td width='50%' /><td width='50%' /></tr>
		<tr><td>tabelle in</td><td>tabelle out</td></tr>
		<tr><td>{$lista_tabelle_in_generica}</td><td>$lista_tabelle_out_generica</td></tr>
		</table>
		</p>
		";
		die();
	}
	function analyzeQuery(){}
	static function verifyFilters($query){
		if(preg_match("/^alter/i",trim($query))) return false;
		return true;
	}
	function toolbar(){
		if(self::$recording){
			echo "<html><meta http-equiv=\"refresh\" content=\"60\" /></head><body>sto registrando - <a href='?stop_record=true'>Stop registrazione</a> - <a href='?listaFP=true' target='_blank' >lista task registrati</a></body></html>";
		}
		else echo "<html><head><style>span { display:inline-block;}</style></head><body><span>non sto registrando -</span> <span><form><input type='hidden' name='start_record' value='true' >Nome task: <input type='text' name='titolo' ><input type='submit' value='Registra' ></form></span> <span>- <a href='?listaFP=true' target='_blank' >lista task registrati</a></span></body></html>";
	}
	static private function commit(){
		return self::$conn->commit();
	}
	static public function trackQuery($queryStr){
		if(self::$recording && $queryStr!="" && self::verifyFilters($queryStr) ){
			$values['ID_FP']=self::$currentFP;
			$values['ID_QUERY']="FP_QUERIES_SEQ.nextval";
			$values['QUERY']['valore']=$queryStr;
			$values['QUERY']['bind']=false;

			$query=self::newQuery();
			$query->insert($values,'TRACK_FP_QUERIES');
			self::commit();
		}
	}
}




?>