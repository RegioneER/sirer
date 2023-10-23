<?
include_once "study_prototype.inc";
 /**
  * Classe di gestione dell'SDV
  *
  * @package Hyper
  */
 class SysTables{

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
 	 * @return db actions
 	 */
 	function SysTables( $service=null, $conn=null, $config_service,$vlist , $xml_dir){
// 		phpinfo();die();
 		$this->conn = $conn;
 		$this->service = $service;
 		$this->config_service = $config_service;
 		$this->vlist = $vlist;
 		$this->xml_dir = $xml_dir;
 		
 	 	$servicename=$this->service;
		 $table_sys_tables=$servicename."_SYS_TABLES";
		 $this->sys_tables=$table_sys_tables;
		$query=new query ( $this->conn );
		$query_check_existence6 = "select table_name from user_tables where table_name=upper('$table_sys_tables')";
		$query->set_sql ( $query_check_existence6 );
		$query->exec ();
		if($query->get_row ()){
			$return = true;
		}
		else
		{
			$query_create = "
			create table $table_sys_tables
				(
				  TOKEN NUMBER,
				  DATATOKEN DATE,
				  SYS_TABLE VARCHAR2(200)
				)
			";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
//			echo "<hr>$query_create";
			$this->conn->commit();
		}
 		
 	}
 	
 	
 	
 function SysEsta(){
		
		
		/**
		 * come anticipato da Margherita, avremmo bisogno di avere una tabella (SYS_ESTA) che contenga:
·         ESAM                   Numero ESAM
·         N_FORM            Nome form corrispondente
·         N_TAB                 Tabella corrispondente
		 */
		 $servicename=$this->service;
		 $table_sys_esta=$servicename."_SYS_ESTA";
		$query=new query ( $this->conn );
		$query_check_existence6 = "select table_name from user_tables where table_name=upper('$table_sys_esta')";
		$query->set_sql ( $query_check_existence6 );
		$query->exec ();
		if($query->get_row ()){
			$return = true;
		}
		else
		{
			$query_create = "
			create table $table_sys_esta
				(
				  VISITNUM NUMBER,
				  ESAM NUMBER,
				  N_FORM VARCHAR2(2000 CHAR),
				  N_TAB     VARCHAR2(200 CHAR),
				  FORM_TYPE VARCHAR2(200 CHAR)
				)
			";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
//			echo "<hr>$query_create";
			$this->conn->commit();
		}
		
		$query_token=new query ( $this->conn );
		$query_token_existence6 = "select to_char(max(DATATOKEN),'YYYY-MM-DD HH24:MI:SS') as DATATOKEN from ".$this->sys_tables;
		$query_token->set_sql ( $query_token_existence6 );
		$query_token->exec ();
		if($query_token->get_row ()){
			$token=$query_token->row['DATATOKEN'];
			$today=date("Y-m-d H:i:s");
//			print_R($today);echo "<hr>";
//			echo $token;echo "<hr>";
			$to_time=strtotime("$today");
			$from_time=strtotime("$token");
//			echo $to_time; echo "<br>";
//			echo $from_time; echo "<br>";
			$diff_time=round(abs($to_time - $from_time) /60 ,2);
			if($diff_time<2){
				die("Sessione aperta , attendere 3 minuti");
			}
		}
		
		$query2=new query ( $this->conn );
		$sql_truncate="truncate table {$table_sys_esta}";
		$query2->set_sql ( $sql_truncate );
		$query2->ins_upd ();
		$this->conn->commit();
			
		$query3=new query ( $this->conn );
		$values3['TOKEN'] = 1;
		$values3['DATATOKEN']= "sysdate";
     	$values3['SYS_TABLE']= "ESTA";
		$tb3 = $this->sys_tables;
		$pk = '';
		$query3->insert ( $values3, $tb3, $pk );
		$this->conn->commit();
		
		$xml_dir=$this->xml_dir;
		foreach ($this->vlist->esams as $key => $val){
			if (isset($val) && is_array($val)) foreach ($val as $kv => $vv)
			{
				$es_name[$kv]=$vv['TESTO'];
				$es_form[$key][$kv]=$vv['XML'];
			}
		}
		
		$sql = new query ( $this->conn );
		foreach ($this->vlist->visitnums as $key => $val){
			foreach ($this->vlist->esams[$key] as $k => $v){
				$esame=trim($this->vlist->esams[$key][$k]['TESTO']);
				$num_esame=$this->vlist->esams[$key][$k]['NUMBER'];
				$form_reg= new xml_form();
				$form_reg->xml_form_by_file($xml_dir."/".$es_form[$key][$k]);
				$patients_table=$form_reg->form['TABLE'];
				$type = "NORMAL";
				if ($this->vlist->esams[$key][$k]['MAIN']){
                    $type = "MAIN";
				}
                if ($this->vlist->esams[$key][$k]['MAINSUB']){
                    $type = "SUB";
                }
				//var_dump($form_reg);
				//var_dump($this->vlist->esams[$key][$k]);
                //var_dump($v);
                //echo "<hr/>";
				$values ['VISITNUM'] = $key;
				$values ['ESAM'] = $num_esame;
				$values ['N_FORM'] =$esame;
				$values ['N_TAB'] = $patients_table;
                $values ['FORM_TYPE'] = $type;
				$tb = "$table_sys_esta";
				$pk = '';
				$sql->insert ( $values, $tb, $pk );
				
//				print_r("<hr />Row inserted:  Visita:".$key."   -   Num.Esame:".$num_esame."  - Nome Esame:".$esame ."  - Tabella:".$patients_table);
			}
		}
		$this->conn->commit();
		
		
		
	}
	
	function SysLkup(){
		/**
		Crea una tabella di sistema SYS_LKUP la quale contenta tutte le lookup di tutti i campi con decodifica, ecco i campi della tabella:
		Idlkup number() è numero progressivo
		Tablenm varchar2(100) è nome tabella
		Fieldnm varchar2(100) è nome del campo
		Code varchar2(20) è codice
		Decode varchar2(200) è decodifica
		Ecco un esempio: tabella Demog campo Sex
		1, ‘DEMOG’,’SEX’,1,’Male’
		2,’DEMOG’,’SEX’,2,’Female’
		E così per tutti i campi che hanno unadecodifica.
		*/
			$servicename=$this->service;
			$table_sys_lkup=$servicename."_SYS_LKUP";
			$query=new query ( $this->conn );
			$query_check_existence6 = "select table_name from user_tables where table_name=upper('$table_sys_lkup')";
			$query->set_sql ( $query_check_existence6 );
			$query->exec ();
			if($query->get_row ()){
				$return = true;
			}
			else
			{
				$query_create = "
				create table $table_sys_lkup
					(
					  IDLKUP 	NUMBER,
					  TABLENM 	VARCHAR2(200 CHAR),
					  FIELDNM 	VARCHAR2(200 CHAR),
					  CODE    	VARCHAR2(200 CHAR),
					  D_CODE    VARCHAR2(4000 CHAR),
					  FIELDTYPE    VARCHAR2(200 CHAR)					  
					)
				";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $query_create );
				$sql->ins_upd ();
	//			echo "<hr>$query_create";
				$this->conn->commit();
			}
			
			$query_token=new query ( $this->conn );
			$query_token_existence6 = "select to_char(max(DATATOKEN),'YYYY-MM-DD HH24:MI:SS') as DATATOKEN from ".$this->sys_tables;
			$query_token->set_sql ( $query_token_existence6 );
			$query_token->exec ();
			if($query_token->get_row ()){
				$token=$query_token->row['DATATOKEN'];
				$today=date("Y-m-d H:i:s");
	//			print_R($today);echo "<hr>";
	//			echo $token;echo "<hr>";
				$to_time=strtotime("$today");
				$from_time=strtotime("$token");
	//			echo $to_time; echo "<br>";
	//			echo $from_time; echo "<br>";
				$diff_time=round(abs($to_time - $from_time) /60 ,2);
				if($diff_time<3){
					die("Sessione aperta , attendere 3 minuti");
				}
			}
			
			$query2=new query ( $this->conn );
			$sql_truncate="truncate table {$table_sys_lkup}";
			$query2->set_sql ( $sql_truncate );
			$query2->ins_upd ();
			$this->conn->commit();
			
			$query3=new query ( $this->conn );
			$values3['TOKEN'] = 1;
			$values3['DATATOKEN']= "sysdate";
	        $values3['SYS_TABLE']= "LKUP";

        	$tb3 = $this->sys_tables;
			$pk = '';
			$query3->insert ( $values3, $tb3, $pk );
			$this->conn->commit();			
		
			$query_insert = new query ( $this->conn );
			$idlkup=0;
			$idinserted=0;
        	$lkup_inserted=array();
			foreach ( $this->vlist->esams as $k => $v ){
//				print_r($k);print_r($v);
				foreach ( $v as $ke => $va ){					
					$form=$this->vlist->esams[$k][$ke]['XML'];
//					echo '<br>'.$form.'<br>';
					$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
					$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
					foreach($xml_form->fields as $key_field=>$val_field){
						if($val_field['TYPE']=="radio" || $val_field['TYPE']=="select" || $val_field['TYPE']=="checkbox" || $val_field['TYPE']=="checkbox_decode"){
							$idlkup++;
							$lookupexist=false;

							foreach($val_field['VALUE'] as $key=>$val){
								foreach($lkup_inserted as $chiave=>$valore){
									// Controllo l'univocità della look up. 
									if($xml_form->form['TABLE']==$valore['TABLENM'] && $val_field['VAR']==$valore['FIELDNM']
									 && $key==$valore['CODE'] && $val==$valore['D_CODE'] && $val_field['TYPE']==$valore['FIELDTYPE']
									){	
										$lookupexist=true;								
									}
								}
//								echo "<hr>";
//								echo $idlkup; echo $valore['TABLENM']; echo $valore['CODE'];echo $valore['FIELDNM'];
//								echo "<hr>";
								if($lookupexist==false){
									$values_lkup['IDLKUP']=$idlkup;
									$values_lkup['TABLENM']=$xml_form->form['TABLE'];
									$values_lkup['FIELDNM']=$val_field['VAR'];
									$values_lkup['CODE']=$key;
									$values_lkup['D_CODE']=$val;
									$values_lkup['FIELDTYPE']=$val_field['TYPE'];
									$tb = "$table_sys_lkup";
									$pk = '';
									$query_insert->insert ( $values_lkup, $tb, $pk );
									$idinserted++;
									$lkup_inserted[$idinserted]=$values_lkup;
								}
							}
						}
					}
				}
				$this->conn->commit();
			}
			$this->conn->commit();
	}
	
	function SysVrlb(){
			$servicename=$this->service;
			$table_sys_vrlb=$servicename."_SYS_VRLB";
			$query=new query ( $this->conn );
			$query_check_existence6 = "select table_name from user_tables where table_name=upper('$table_sys_vrlb')";
			$query->set_sql ( $query_check_existence6 );
			$query->exec ();
			if($query->get_row ()){
				$return = true;
			}
			else
			{
				$query_create = "
				create table $table_sys_vrlb
					(
					  IDVRLB 			NUMBER,
					  TABLE_NAME 		VARCHAR2(100 CHAR),
					  VARIABLE_NAME 	VARCHAR2(100 CHAR),
					  LABEL_NAME  		VARCHAR2(4000 CHAR),
					  TYPE_SIZE 	    VARCHAR2(100 CHAR),
					  VAR_FORMAT 	    VARCHAR2(100 CHAR),
					  VAR_LENGTH 	    VARCHAR2(100 CHAR),
					  SPEC_MISSING 	    VARCHAR2(10 CHAR),
					  MANDATORY 	    VARCHAR2(10 CHAR),
					  COND_MANDATORY 	VARCHAR2(4000 CHAR),
					  VAR_DEF 	    	VARCHAR2(4000 CHAR)
					)
				";
				//,
                //VAR_MIN 	    	VARCHAR2(1000 CHAR),
				//VAR_MAX 	    	VARCHAR2(1000 CHAR)
				$sql = new query ( $this->conn );
				$sql->set_sql ( $query_create );
				$sql->ins_upd ();
	//			echo "<hr>$query_create";
				$this->conn->commit();
			}
			
			$query_token=new query ( $this->conn );
			$query_token_existence6 = "select to_char(max(DATATOKEN),'YYYY-MM-DD HH24:MI:SS') as DATATOKEN from ".$this->sys_tables;
			$query_token->set_sql ( $query_token_existence6 );
			$query_token->exec ();
			if($query_token->get_row ()){
				$token=$query_token->row['DATATOKEN'];
				$today=date("Y-m-d H:i:s");
	//			print_R($today);echo "<hr>";
	//			echo $token;echo "<hr>";
				$to_time=strtotime("$today");
				$from_time=strtotime("$token");
	//			echo $to_time; echo "<br>";
	//			echo $from_time; echo "<br>";
				$diff_time=round(abs($to_time - $from_time) /60 ,2);
				if($diff_time<3){
					die("Sessione aperta , attendere 3 minuti");
				}
			}
			
			$query2=new query ( $this->conn );
			$sql_truncate="truncate table {$table_sys_vrlb}";
			$query2->set_sql ( $sql_truncate );
			$query2->ins_upd ();
			$this->conn->commit();
			
			$query3=new query ( $this->conn );
			$values3['TOKEN'] = 1;
			$values3['DATATOKEN']= "sysdate";
        	$values3['SYS_TABLE']= "VRLB";

        	$tb3 = $this->sys_tables;
			$pk = '';
			$query3->insert ( $values3, $tb3, $pk );
			$this->conn->commit();
			
			$query_insert = new query ( $this->conn );
			$idvrlb=0;
        	$variable_vrlb = array();
			foreach ( $this->vlist->esams as $k => $v ){
//				print_r($k);print_r($v);
				foreach ( $v as $ke => $va ){					
					$form=$this->vlist->esams[$k][$ke]['XML'];
//					echo '<br>'.$form.'<br>';
					$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
					$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
					foreach($xml_form->fields as $key_field=>$val_field){
						//if($val_field['TYPE']!="" && $val_field['TYPE']!="hidden")
						if($val_field['TYPE']!="" && $variable_vrlb[$xml_form->form['TABLE']][$val_field['VAR']]!=1){
								$variable_vrlb[$xml_form->form['TABLE']][$val_field['VAR']]=1;
								$values_vrlb['IDVRLB']=$idvrlb++;
								$values_vrlb['TABLE_NAME']=$xml_form->form['TABLE'];
								$values_vrlb['VARIABLE_NAME']=$val_field['VAR'];
								$values_vrlb['LABEL_NAME']=$this->FilterTags($val_field['TESTO']);
								$values_vrlb['TYPE_SIZE']=$val_field['TYPE'];
	                            $values_vrlb['VAR_FORMAT']=$val_field['VAR_TYPE'];
								$values_vrlb['VAR_LENGTH']=$val_field['VAR_SIZE'];
								$values_vrlb['SPEC_MISSING']=($val_field['FM_CODE']?"Y":"N");
								$values_vrlb['MANDATORY']=(strtoupper($val_field['SEND'])=="OBBLIGATORIO"?"Y":"N");
								$condition = "";
								if ($val_field['CONDITION']){
									$condition = "{$val_field['CONDITION']} ({$val_field['CONDITION_VALUE']})";
								}
                            	$values_vrlb['COND_MANDATORY']=$condition;
                            	$values_vrlb['VAR_DEF']=$val_field['DEF'];
								//Gestire eventualmente max/min date (invertire) e fare in modo di non applicare la sostituzione nel DB con la data corrente (ma scrivere l'indicazione "SYSDATE"
                            	//$values_vrlb['VAR_MIN']=$val_field['MIN'];
								//$values_vrlb['VAR_MAX']=$val_field['MAX'];
								$tb = "$table_sys_vrlb";
								$pk = '';
								$query_insert->insert ( $values_vrlb, $tb, $pk );
						}
					}
				}
				$this->conn->commit();
			}
			$this->conn->commit();
	}
	
	
	
 function SysOthvr(){
			$servicename=$this->service;
			$table_sys_othvr=$servicename."_SYS_OTHVR";
			$query=new query ( $this->conn );
			$query_check_existence6 = "select table_name from user_tables where table_name=upper('$table_sys_othvr')";
			$query->set_sql ( $query_check_existence6 );
			$query->exec ();
			if($query->get_row ()){
				$return = true;
			}
			else
			{
				$query_create = "
				create table $table_sys_othvr
					(
					  ID_OTHVR 			NUMBER,
					  ESAM              NUMBER,
					  VISITNUM          NUMBER,
					  TABLE_NAME 		VARCHAR2(200 CHAR),
					  VARIABLE_NAME 	VARCHAR2(200 CHAR),
					  TYPE_SIZE 	    VARCHAR2(40 CHAR)					  
					)
				";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $query_create );
				$sql->ins_upd ();
	//			echo "<hr>$query_create";
				$this->conn->commit();
			}
			
			$query_token=new query ( $this->conn );
			$query_token_existence6 = "select to_char(max(DATATOKEN),'YYYY-MM-DD HH24:MI:SS') as DATATOKEN from ".$this->sys_tables;
			$query_token->set_sql ( $query_token_existence6 );
			$query_token->exec ();
			if($query_token->get_row ()){
				$token=$query_token->row['DATATOKEN'];
				$today=date("Y-m-d H:i:s");
	//			print_R($today);echo "<hr>";
	//			echo $token;echo "<hr>";
				$to_time=strtotime("$today");
				$from_time=strtotime("$token");
	//			echo $to_time; echo "<br>";
	//			echo $from_time; echo "<br>";
				$diff_time=round(abs($to_time - $from_time) /60 ,2);
				if($diff_time<3){
//					die("Sessione aperta , attendere 3 minuti");
				}
			}
			
			$query2=new query ( $this->conn );
			$sql_truncate="truncate table {$table_sys_othvr}";
			$query2->set_sql ( $sql_truncate );
			$query2->ins_upd ();
			$this->conn->commit();
			
			$query3=new query ( $this->conn );
			$values3['TOKEN'] = 1;
			$values3['DATATOKEN']= "sysdate";
     		$values3['SYS_TABLE']= "OTHVR";

     		$tb3 = $this->sys_tables;
			$pk = '';
			$query3->insert ( $values3, $tb3, $pk );
			$this->conn->commit();
			
			$query_insert = new query ( $this->conn );
			
			$idothvr=0;
     		$variable_othvr=array();
			foreach ( $this->vlist->esams as $k => $v ){
//				print_r($k);print_r($v);
				foreach ( $v as $ke => $va ){					
					$form=$this->vlist->esams[$k][$ke]['XML'];
//					echo '<br>'.$form.'<br>';
					$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
					$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
					foreach($xml_form->fields as $key_field=>$val_field){
						//if($val_field['TYPE']!="" && $val_field['TYPE']!="hidden")
						if($val_field['TYPE']!="" && $variable_othvr[$xml_form->form['TABLE']][$val_field['VAR']]!=1){
							$variable_othvr[$xml_form->form['TABLE']][$val_field['VAR']]=1;
							$values_othvr['TABLE_NAME']=$xml_form->form['TABLE'];
							$values_othvr['TYPE_SIZE']=$val_field['TYPE'];
							$values_othvr['ESAM']=$ke;
							$values_othvr['VISITNUM']=$k;
							$tb = "$table_sys_othvr";
							$pk = '';
								
							if($val_field['TYPE']=="date" || $val_field['TYPE']=="date_cal" ){
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."RC";
								$query_insert->insert ( $values_othvr, $tb, $pk );
								
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_D";
								$query_insert->insert ( $values_othvr, $tb, $pk );

								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_M";
								$query_insert->insert ( $values_othvr, $tb, $pk );

								$values_othvr['ID_OTHVR']=$idothvr++;								
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_Y";
								$query_insert->insert ( $values_othvr, $tb, $pk );
							}
							elseif($val_field['TYPE']=="radio" || $val_field['TYPE']=="select" || $val_field['TYPE']=="checkbox_decode" ){
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']="D_".$val_field['VAR'];
								$query_insert->insert ( $values_othvr, $tb, $pk );
							}
							elseif($val_field['TYPE']=="ora"){
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_H";
								$query_insert->insert ( $values_othvr, $tb, $pk );
								
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_M";
								$query_insert->insert ( $values_othvr, $tb, $pk );
							}
						}
					}
				}
				$this->conn->commit();
			}
			$this->conn->commit();
	}

 function SysVisit(){
			$servicename=$this->service;
			$table_sys=$servicename."_SYS_VISIT";
			$query=new query ( $this->conn );
			$query_check_existence6 = "select table_name from user_tables where table_name=upper('$table_sys')";
			$query->set_sql ( $query_check_existence6 );
			$query->exec ();
			if($query->get_row ()){
				$return = true;
			}
			else
			{
				$query_create = "
				create table $table_sys
					(
					  STUDY_PREFIX 		VARCHAR2(255 CHAR),
					  VISITNUM          NUMBER,
					  VISIT_NAME 		VARCHAR2(255 CHAR)
					)
				";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $query_create );
				$sql->ins_upd ();
	//			echo "<hr>$query_create";
				$this->conn->commit();
			}
			
			
			$query_token=new query ( $this->conn );
			$query_token_existence6 = "select to_char(max(DATATOKEN),'YYYY-MM-DD HH24:MI:SS') as DATATOKEN from ".$this->sys_tables;
			$query_token->set_sql ( $query_token_existence6 );
			$query_token->exec ();
			if($query_token->get_row ()){
				$token=$query_token->row['DATATOKEN'];
				$today=date("Y-m-d H:i:s");
	//			print_R($today);echo "<hr>";
	//			echo $token;echo "<hr>";
				$to_time=strtotime("$today");
				$from_time=strtotime("$token");
	//			echo $to_time; echo "<br>";
	//			echo $from_time; echo "<br>";
				$diff_time=round(abs($to_time - $from_time) /60 ,2);
				if($diff_time<3){
//					die("Sessione aperta , attendere 3 minuti");
				}
			}
			
			$query2=new query ( $this->conn );
			$sql_truncate="truncate table {$table_sys}";
			$query2->set_sql ( $sql_truncate );
			$query2->ins_upd ();
			$this->conn->commit();
			
			$query3=new query ( $this->conn );
			$values3['TOKEN'] = 1;
			$values3['DATATOKEN']= "sysdate";
     		$values3['SYS_TABLE']= "VISIT";

     		$tb3 = $this->sys_tables;
			$pk = '';
			$query3->insert ( $values3, $tb3, $pk );
			$this->conn->commit();
			
			$query_insert = new query ( $this->conn );
						
			foreach ($this->vlist->visitnums as $k=>$v){
				//print_r($v);
				$values['STUDY_PREFIX']=$servicename;
				$values['VISITNUM']=$v['NUMBER'];
				$values['VISIT_NAME']=$v['SHORT_TXT'];
				$tb = "$table_sys";
				$pk = '';
				$query_insert->insert ( $values, $tb, $pk );
				$this->conn->commit();
			}
			$this->conn->commit();
			//die();
			/*
			$idothvr=0;
			foreach ( $this->vlist->esams as $k => $v ){
//				print_r($k);print_r($v);
				foreach ( $v as $ke => $va ){					
					$form=$this->vlist->esams[$k][$ke]['XML'];
//					echo '<br>'.$form.'<br>';
					$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
					$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
					foreach($xml_form->fields as $key_field=>$val_field){
						if($val_field['TYPE']!="" && $val_field['TYPE']!="hidden" ){

							$values_othvr['TABLE_NAME']=$xml_form->form['TABLE'];
							$values_othvr['TYPE_SIZE']=$val_field['TYPE'];
							$values_othvr['ESAM']=$ke;
							$values_othvr['VISITNUM']=$k;
							$tb = "$table_sys_othvr";
							$pk = '';
								
							if($val_field['TYPE']=="date_hyper"  ){
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."RC";
								$query_insert->insert ( $values_othvr, $tb, $pk );
								
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_D";
								$query_insert->insert ( $values_othvr, $tb, $pk );

								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_M";
								$query_insert->insert ( $values_othvr, $tb, $pk );

								$values_othvr['ID_OTHVR']=$idothvr++;								
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_Y";
								$query_insert->insert ( $values_othvr, $tb, $pk );
							}
							elseif($val_field['TYPE']=="radio_hyper" || $val_field['TYPE']=="select_hyper" ){
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']="D_".$val_field['VAR'];
								$query_insert->insert ( $values_othvr, $tb, $pk );
							}
							elseif($val_field['TYPE']=="ora_hyper"){
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_H";
								$query_insert->insert ( $values_othvr, $tb, $pk );
								
								$values_othvr['ID_OTHVR']=$idothvr++;
								$values_othvr['VARIABLE_NAME']=$val_field['VAR']."_M";
								$query_insert->insert ( $values_othvr, $tb, $pk );
							}
						}
					}
				}
				$this->conn->commit();
			}
			$this->conn->commit();
			*/
	}
	
 function CorniceHtml(){
	$cornice='
		<style>
		/* Table Layout */
		.main-box{
			margin: 0 auto;
			margin-top:20px; 
			width:500px;
			vertical-align:top;
			height:250px;
			
		}
		
		.main-top-sx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-top-sx.gif) no-repeat bottom right;
		}
		
		.main-top{
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-top.gif) repeat-x bottom;
		}
		
		.main-top-dx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-top-dx.gif) repeat-x bottom left;
		}
		
		.main-sx{
			width:2px;
			background:#ffffff url(../../../LOGIN/images/main-sx.gif) repeat-y;
		}
		
		.main-dx{
			width:2px;
			background:#ffffff url(../../../LOGIN/images/main-dx.gif) repeat-y;
		}
		
		.main-bottom-sx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-bottom-sx.gif) no-repeat;
		}
		
		.main-bottom{
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-bottom.gif) repeat-x;
		}
		
		.main-bottom-dx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-bottom-dx.gif) repeat-x;
		}
		</style>
		<table class="main-box" cellpadding="7px" cellspacing="0" >
			<!-- START - ROW TOP SX -->
			<tr>
				<td class="main-top-sx"></td>
				<td class="main-top"></td>
				<td class="main-top-dx"></td>
			</tr>
			<!-- FINE - ROW TOP SX -->
			
			<!-- START - ROW CORPO -->
			<tr>
				<td class="main-sx"></td>
				<td class="main-cx" ><!--form--></td>
				<td class="main-dx"></td>
			</tr>
			<!-- FINE - ROW CORPO -->
			
			<!-- START - ROW BOTTOM -->
			<tr>
				<td class="main-bottom-sx"></td>
				<td class="main-bottom"></td>
				<td class="main-bottom-dx"></td>
			</tr>
			<!-- FINE - ROW BOTTOM -->
		</table>';
	return $cornice;
	}
	
	function FilterTags($text){
		//mixed preg_replace ( mixed $pattern , mixed $replacement , mixed $subject [, int $limit = -1 [, int &$count ]] )
		return trim(preg_replace("/<(.*)>/U","",$text));
		//return preg_replace("/(<([\w]+)[^>]*>)(.*?)(<\/\\2>)/","",$text);
		//return truncate($text);
		
		/*
		$html = "<b>bold text</b><a href=howdy.html>click me</a>";
	
		preg_match_all("/(<([\w]+)[^>]*>)(.*?)(<\/\\2>)/", $html, $matches, PREG_SET_ORDER);
		
		foreach ($matches as $val) {
		    echo "matched: " . $val[0] . "\n";
		    echo "part 1: " . $val[1] . "\n";
		    echo "part 2: " . $val[2] . "\n";
		    echo "part 3: " . $val[3] . "\n";
		    echo "part 4: " . $val[4] . "\n\n";
		}
		die();
		*/
	}
	
 	function truncate($text, $length, $suffix = '&hellip;', $isHTML = true){
		$i = 0;
		$simpleTags=array('br'=>true,'hr'=>true,'input'=>true,'image'=>true,'link'=>true,'meta'=>true);
		$tags = array();
		if($isHTML){
			preg_match_all('/<[^>]+>([^<]*)/', $text, $m, PREG_OFFSET_CAPTURE | PREG_SET_ORDER);
			foreach($m as $o){
				if($o[0][1] - $i >= $length)
					break;
				$t = substr(strtok($o[0][0], " \t\n\r\0\x0B>"), 1);
				// test if the tag is unpaired, then we mustn't save them
				if($t[0] != '/' && (!isset($simpleTags[$t])))
					$tags[] = $t;
				elseif(end($tags) == substr($t, 1))
					array_pop($tags);
				$i += $o[1][1] - $o[0][1];
			}
		}
		
		// output without closing tags
		$output = substr($text, 0, $length = min(strlen($text),  $length + $i));
		// closing tags
		$output2 = (count($tags = array_reverse($tags)) ? '</' . implode('></', $tags) . '>' : '');
		
		// Find last space or HTML tag (solving problem with last space in HTML tag eg. <span class="new">)
		$pos = (int)end(end(preg_split('/<.*>| /', $output, -1, PREG_SPLIT_OFFSET_CAPTURE)));
		// Append closing tags to output
		$output.=$output2;

		// Get everything until last space
		$one = substr($output, 0, $pos);
		// Get the rest
		$two = substr($output, $pos, (strlen($output) - $pos));
		// Extract all tags from the last bit
		preg_match_all('/<(.*?)>/s', $two, $tags);
		// Add suffix if needed
		if (strlen($text) > $length) { $one .= $suffix; }
		// Re-attach tags
		$output = $one . implode($tags[0]);

		//added to remove  unnecessary closure
		$output = str_replace('</!-->','',$output); 

		return $output;
	}
 	
 }
 
 
?>
