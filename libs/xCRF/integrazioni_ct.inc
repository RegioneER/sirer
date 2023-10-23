<?

include_once "integrazioni.inc";
/**
 * Classe di gestione delle integrazioni alle schede (eQuery)
 *
 * @package Hyper
 *  
 */
class integrazioni_prototype_ct extends integrazioni_prototype{


    var $cro = true;
	/**
 	 * Costruttore dell'oggetto, vengono presi in ingresso le informazione relative alla
     * connessione oracle, al prefisso in banca dati del serviio, alle configurazioni di sistema,
 	 * e all'array multiplo $vlist contenente lo schema delle form xml, degli esami e delle visite dello studio.
 	 *
 	 * @param String $userid
 	 * @param String $profilo
 	 * @param String $xmr_tip
 	 * @param dbconn_hyper $conn
 	 * @param array $config_param
 	 * 
 	 * @return integrazioni
 	 */
	function __construct($config_param, $conn, $userid, $profilo, $xmr_tip,$session_vars = array(), $xml_dir=false){
        //parent::__construct($config_param, $conn, $userid, $profilo, $xmr_tip,$session_vars);
        
		$this->config_service = $config_param;
		if ($this->config_service['eQueryNoCroMode']) $this->cro=false;
		$this->role=$config_param['eQuerySpec']['Integrazione']['ROLE'];
		$this->pk_field=$config_param['PK_SERVICE'];
		$this->approv_role=$config_param['eQuerySpec']['Integrazione']['VALIDATOR'];
		$this->non_appr_states=$config_param['eQuerySpec']['Integrazione']['NON_APPROV'];
		$this->appr_states=$config_param['eQuerySpec']['Integrazione']['APPROV'];
		$this->control_role=$config_param['eQuerySpec']['Integrazione']['CONTROL_ROLE'];
		$this->conn=$conn;
		if (isset($_POST[$this->pk_field])) $this->pk_value=$_POST[$this->pk_field];
		else $this->pk_value=$_GET[$this->pk_field];
		$this->service=$config_param['service'];
		$this->userid=$userid;
		$this->profilo=$profilo;
		$this->stato=$this->getStato();
		$this->xmr_tip=$xmr_tip;
		$xml_autodir = str_replace ( "index.php", "", $_SERVER ['SCRIPT_FILENAME'] ) . "xml";
		//if (!$xml_dir){
		//	debug_print_backtrace();
		//	die();
		//}
		$this->xml_dir = ($xml_dir?$xml_autodir:"xml");

		$this->eq_enabled=$this->isEnabled($profilo, $config_param);
		if ($this->eq_enabled){
//			In Installer.inc:
            if ($config_param['production'] != 1) {
                $this->checkCreateEqView();
            }
			$this->getEqs();
			if (!isset($_POST['SEARCH'])) $this->getActiveEq();
		}
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
			  USERID_INS VARCHAR2(32 CHAR),
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
			  VALORE_OLD     VARCHAR2(4000 CHAR),
			  ACTION 		 NUMBER DEFAULT 0
			)
			";
            $sql = new query ( $this->conn );
            $sql->ins_upd ( $query_create ); //bind non necessario
        }
        return true;
    }

    /**
	  * Gestisce il salvataggio delle eQuery per campo nelle tabelle dedicate: NOMESTUDIO_EQ per la gestione delle eQ sulla form.
	  * NOMESTUDIO_EQFIELD per la gestione a livello di campo della eQuery.
	  * Viene gestito il comportamento della piattaforma a livello di profilo implementando 4 stati dell'eQuery:
	  * Stato 0: eQ emessa dal DM verso il DE;
	  * Stato 1: eQ approvata dal DM con aggiornamento del dato;
	  * Stato 2: eQ pendente emessa dal DE verso il DM;
	  * Stato 3: eQ rifiutata dal DM , dato non aggiornato;
	  * 
	  * @param array $xml_form
 	  * 
 	  * @return void
	  */
	function SaveEqDE($xml_form){
		//Controllo se l'utenza è quella di ruolo semplice e non di approvazione
		if($this->isRole($this->profilo) ){
			// Prendo tutto da eq e eqfield, lo metto in $pending.
			 $pending=$xml_form->FieldPendig();
		
			 // Valori vecchi , valori nuovi:, vedere se serve davvero.
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
			
			
			$fields=array();
			foreach ($xml_form->fields as $key=>$val){
				if ($val['VAR']!='' && $val['TB']!='no'){
					if (!isset($_POST[$val['VAR']]) || $_POST[$val['VAR']]==='') $_POST[$val['VAR']]=0;
					$field_type = "field_{$val['TYPE']}";
					include_once "libs/field.inc";
					//echo $val['TYPE']."<br>";
// 					if (file_exists("libs/{$field_type}.inc")) include_once "libs/{$field_type}.inc";
// 					else include_once "libs/fields/{$field_type}.inc";
					/**
					 *  Modifica 08/09/2011
					 * Carico prima i campi modificati per servizio se esistono
					 * M. Verrocchio
					**/
					if (!class_exists($field_type)) {
						if ($xml_form->config_service['field_lib'] != '' && file_exists($xml_form->config_service['field_lib'].$field_type.".inc")) {
							
							include_once $xml_form->config_service['field_lib'].$field_type.".inc";
						} elseif (file_exists("{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc")) {
							
							include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc";
						} else {
							
							include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/fields/{$field_type}.inc";
						}
					}
					
					$field_obj = new $field_type ( $xml_form, $xml_form->vars[$val['VAR']], $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $xml_form->errors );
					$field_obj->insert_stmt();
					if ($field_type=="field_checkbox_hyper" || $field_type=="field_checkbox"){
						$keys=array_keys($field_obj->values);
						/*
							if (!$_POST['EQAREADE_'.$keys[0]]){
								$_POST['EQAREADE_'.$keys[0]] = $_POST["EQAREADE_".$field_obj->id];
								//echo "EQAIDK: 'EQAREADE_{$field_obj->id}'<br/>\n";
								//echo "EQA0K: 'EQAREADE_{$keys[0]}'<br/>\n";
								//echo "EQAID: {$_POST["EQAREADE_".$field_obj->id]}<br/>\n";
								//echo "EQA0: {$_POST['EQAREADE_'.$keys[0]]}<br/>\n";
							}else{
						$_POST["EQAREADE_".$field_obj->id]=$_POST['EQAREADE_'.$keys[0]];
								//echo "EQAIDK: 'EQAREADE_{$field_obj->id}'<br/>\n";
								//echo "EQA0K: 'EQAREADE_{$keys[0]}'<br/>\n";
								//echo "EQAID: {$_POST["EQAREADE_".$field_obj->id]}<br/>\n";
								//echo "EQA0: {$_POST['EQAREADE_'.$keys[0]]}<br/>\n";
						unset($_POST['EQAREADE_'.$keys[0]]);
						}
						*/
						$fields[]=$field_obj->id;
						$values[]=$field_obj;
					}
					foreach ($field_obj->field_stmt as $f=>$fv){
						$fields[]=$fv;
					}
					foreach ($field_obj->value_stmt as $f=>$fv){
						$values[]=$fv;
					}
				}
			}
			//echo "<hr/>";
			////var_dump($fields);
			////var_dump($values);
			////echo "<hr/>";
			//var_dump($_POST);
			//Inserimento della eQ in DB
			foreach($fields as $key=>$val){
				// Manino pazzesco per far funzionare i field progressivi:				
				if($val!='CODPAT' && $val!='PROGR'  && $val!='VISITNUM_PROGR'  && $val!='ESAM'  && $val!='VISITNUM'){
					if($_POST[$val.'_PROGR_'.$_POST['PROGR']]!=''){
						$_POST[$val]=$_POST[$val.'_PROGR_'.$_POST['PROGR']];
						$_POST['EQAREADE_'.$val]=$_POST['EQAREADE_'.$val.'_PROGR_'.$_POST['PROGR']];
					}
				}
				
				$vals='';
				$pk='';
				$vals['VALORE']=$values[$key];
				$vals['VALORE_OLD']=$original_res[$fields[$key]];
				//var_dump($pending);
				//echo "VAL: {$val} --> {$_POST['EQAREADE_'.$val]}<br/>\n";
				if($_POST['EQAREADE_'.$val]!=''){
					if ($val==$pending[$val]['FIELD']){
						//echo "Campo pendente: {$val}<br/>\n";
					$this->eq_int=$pending[$val]["EQ_INT"];
					$checkboxEq=false;
						if ( is_object($values[$key]) && ( (get_class($values[$key])=="field_checkbox_hyper") || (get_class($values[$key])=="field_checkbox")) ){
						$checkboxEq=true;
					}
						//echo "CHECKBOXEQ: {$checkboxEq}<br/>\n";
					if (!$checkboxEq){
							//echo "NON CHECKBOX<br/>\n";
						$this->eq_int=$pending[$val]['EQ_INT'];
						$pk['EQ_INT']=$this->eq_int;
						$pk[$this->pk_field]=$_POST[$this->pk_field];
						$pk['ESAM']=$_POST['ESAM'];
						$pk['VISITNUM']=$_POST['VISITNUM'];
						$pk['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
						$pk['PROGR']=$_POST['PROGR'];
						$pk['FIELD']=$val;
						$vals['STATOFIELD']=2;
						$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
						$table=$this->service."_EQFIELD";
						
						$sql->update($vals, $table,$pk);
						
						foreach ($fields as $inner_key=>$inner_val){
							if("D_{$val}"==$inner_val || "{$val}_H"==$inner_val || "{$val}_M"==$inner_val || "{$val}RC"==$inner_val){
								$vals='';
								$pk='';
								$vals['VALORE']=$values[$inner_key];
								$vals['VALORE_OLD']= $original_res[$fields[$inner_key]];
								if ($inner_val==$pending[$inner_val]['FIELD']){
				//					echo "Campo pendente con dec: $val ";echo "<br>";
									
									$this->eq_int=$pending[$inner_val]['EQ_INT'];
									$pk['EQ_INT']=$this->eq_int;
									$pk[$this->pk_field]=$_POST[$this->pk_field];
									$pk['ESAM']=$_POST['ESAM'];
									$pk['VISITNUM']=$_POST['VISITNUM'];
									$pk['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
									$pk['PROGR']=$_POST['PROGR'];
									$pk['FIELD']=$inner_val;
									$vals['STATOFIELD']=2;
									$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
									$table=$this->service."_EQFIELD";
									
									$sql->update($vals, $table,$pk);
								}
							}
						}
						}else{
						$vals['VALORE']="checkbox Modificato";
						$pk['EQ_INT']=$this->eq_int;
						$pk[$this->pk_field]=$_POST[$this->pk_field];
						$pk['ESAM']=$_POST['ESAM'];
						$pk['VISITNUM']=$_POST['VISITNUM'];
						$pk['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
						$pk['PROGR']=$_POST['PROGR'];
						$pk['FIELD']=$val;
						$vals['STATOFIELD']=2;
						$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
						$sql->update($vals, $this->service."_EQFIELD",$pk);
							foreach ($values[$key]->values as $fkey=>$fval){
								$vals='';
								$vals['VALORE']=$_POST[$fkey];
								$pk['EQ_INT']=$this->eq_int;
								$pk[$this->pk_field]=$_POST[$this->pk_field];
								$pk['ESAM']=$_POST['ESAM'];
								$pk['VISITNUM']=$_POST['VISITNUM'];
								$pk['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
								$pk['PROGR']=$_POST['PROGR'];
								$pk['FIELD']=$fkey;
								$vals['STATOFIELD']=2;
								$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
								$sql->update($vals, $this->service."_EQFIELD",$pk);
								//echo "sono qui";
								//var_dump($vals);
								//var_dump($pk);
								}
							}
					}
					else{
			//			echo "Campo non pendente: $val ";echo "<br>";
						$this->createEq();
						/*
						$vals['EQ_INT']=$this->eq_int;
						$vals[$this->pk_field]=$_POST[$this->pk_field];
						$vals['ESAM']=$_POST['ESAM'];
						$vals['VISITNUM']=$_POST['VISITNUM'];
						$vals['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
						$vals['PROGR']=$_POST['PROGR'];
						$vals['FIELD']=$val;
						$vals['STATOFIELD']=2;
						$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
						$sql->insert($vals, $this->service."_EQFIELD",$pk);
						*/	
						$checkboxEq=false;
						if (is_object($values[$key]) && ( (get_class($values[$key])=="field_checkbox_hyper") || (get_class($values[$key])=="field_checkbox")) ){
							$checkboxEq=true;
						}
						if (!$checkboxEq){
						$vals['EQ_INT']=$this->eq_int;
						$vals[$this->pk_field]=$_POST[$this->pk_field];
						$vals['ESAM']=$_POST['ESAM'];
						$vals['VISITNUM']=$_POST['VISITNUM'];
						$vals['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
						$vals['PROGR']=$_POST['PROGR'];
						$vals['FIELD']=$val;
						$vals['STATOFIELD']=2;
						$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
						$sql->insert($vals, $this->service."_EQFIELD",$pk);
						foreach ($fields as $inner_key=>$inner_val){
							if("D_{$val}"==$inner_val || "{$val}_H"==$inner_val || "{$val}_M"==$inner_val || "{$val}RC"==$inner_val){
								$vals='';
								$pk='';
								$vals['VALORE']=$values[$inner_key];
								$vals['VALORE_OLD']= $original_res[$fields[$inner_key]];
								$vals['EQ_INT']=$this->eq_int;
								$vals[$this->pk_field]=$_POST[$this->pk_field];
								$vals['ESAM']=$_POST['ESAM'];
								$vals['VISITNUM']=$_POST['VISITNUM'];
								$vals['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
								$vals['PROGR']=$_POST['PROGR'];
								$vals['FIELD']=$inner_val;
								$vals['STATOFIELD']=2;
								$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
				
								$sql->insert($vals, $this->service."_EQFIELD",$pk);
							}
						}
					}else {
						
						$vals['VALORE']="checkbox Modificato";
						$vals['EQ_INT']=$this->eq_int;
						$vals[$this->pk_field]=$_POST[$this->pk_field];
						$vals['ESAM']=$_POST['ESAM'];
						$vals['VISITNUM']=$_POST['VISITNUM'];
						$vals['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
						$vals['PROGR']=$_POST['PROGR'];
						$vals['FIELD']=$val;
						$vals['STATOFIELD']=2;
						$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
						$sql->insert($vals, $this->service."_EQFIELD",$pk);
							foreach ($values[$key]->values as $fkey=>$fval){
								$vals='';
								$pk='';
								$vals['VALORE']=$_POST[$fkey];
								$vals['EQ_INT']=$this->eq_int;
								$vals[$this->pk_field]=$_POST[$this->pk_field];
								$vals['ESAM']=$_POST['ESAM'];
								$vals['VISITNUM']=$_POST['VISITNUM'];
								$vals['VISITNUM_PROGR']=$_POST['VISITNUM_PROGR'];
								$vals['PROGR']=$_POST['PROGR'];
								$vals['FIELD']=$fkey;
								$vals['STATOFIELD']=2;
								$vals['NOTE_DE']=$_POST['EQAREADE_'.$val];
								$sql->insert($vals, $this->service."_EQFIELD",$pk);
								}
							}
					}
					$this->inviaPerApprovazione();
				}
			}
			$this->conn->commit();
		}

		//die();
	}

	/**
	 * 
	 * Gestisce l'emissione della eQ da parte del DM. Lo stato passa a 2.
	 * 
 	 * 
     * @return void
	 */
	function inviaPerApprovazione(){
        global $service;
        global $study_;
		//setta lo stato a 2 e sposta la decisione di approvazione all'AIFA (parametro in config.inc))
		$values['STATO']=2;
		$pk['EQUERY_INT']=$this->eq_int;
		$values['RICH_DE']=$_POST['RICH_DE'];
		$values['MOD_DT']="sysdate";
		$pk[$this->pk_field]=$this->pk_value;
		$sql=new query($this->conn);
		$sql->update($values, $this->service."_EQ", $pk);
		$this->conn->commit();
		
        $link = "\nElenco query: \nhttps://{$_SERVER['SERVER_NAME']}/study/main/index.php?list=equery_list_answered_DM.xml";
        $addVars = $values;
        $addVars['SERVER_NAME'] = $_SERVER['SERVER_NAME'];
        $addVars['EQUERY_INT'] = $pk['EQUERY_INT'];
        $addVars['LINK'] = $link;
        //$this->sendGenericMail($in['VISITNUM'], $in['ESAM'], "SEND", false, false, $in, false);
        $study_->sendGenericMail(-1, -1, "EQUERY", false, false, $addVars, false);

        //$eol="\n";
        //$headers = "From: INFO_" . $service . "@{$_SERVER['SERVER_NAME']}$eol";
        //$headers .= "Content-type: text/plain; charset=utf-8$eol";
        //mail("mt.marano@cineca.it, elisa.rossi@cineca.it, dario.mengoli@gmail.com", "Nuova eQuery OSSERVAFLU da approvare (DEVEL)", "Inserita nuova equery da approvare ({$pk['EQUERY_INT']}) {$link}", $headers);


	}



	/**
	 * 
	 * Controlla lo stato della eQ restituendo un valore volto a discriminare l'abilitazione o meno della funzionalit
	 * 
     * @return $this->eq_int
	 */	
	function getActiveEq(){
		// Discrimino anche sull'esame, non solo sul codpat, altrimenti approverebbe l'eQ in blocco sul paziente
		if(isset($_POST['ESAM']) && $this->pk_value!='' && $_POST[$this->pk_field]!='next' ){
			if($this->isRole($this->profilo)){
				$sql_query="select eq.equery_int, eq.stato,eqfield.esam from {$this->service}_EQ eq,{$this->service}_EQFIELD eqfield where
				eq.{$this->pk_field}={$this->pk_value}
				and eq.equery_int=eqfield.eq_int
				and eqfield.esam={$_POST['ESAM']}
				and eq.stato in (0)
				";
				//and eq.stato in (0,2) --cambio ultima riga della query precedente a causa della abilitazione di equery multiple con differenti id
			}else{
				return null;
				/*query tolta a causa della abilitazione di equery multiple con differenti id
				
				$sql_query="select eq.equery_int, eq.stato,eqfield.esam  from {$this->service}_EQ eq ,{$this->service}_EQFIELD eqfield where
				eq.equery_int=eqfield.eq_int
				and eq.{$this->pk_field}={$this->pk_value}
				and eqfield.esam={$_POST['ESAM']}
				and eq.stato = 2
				";*/
			}
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$this->eq_int=$sql->row['EQUERY_INT'];
			$this->stato=$sql->row['STATO'];
//				echo $sql_query;print_r($this->eq_int);die("passo qui");
			if($this->eq_int!=''){
				return $this->eq_int;
			}
			else {
				return null;
			}
		}elseif($this->isRole($this->profilo)) {
            //$sql_query = "select equery_int, stato from {$this->service}_EQ where
			//userid_ins='{$this->userid}'
			//and {$this->pk_field}={$this->pk_value}
			//and stato in (0,2)
			//";
            return null;
        }elseif(!$this->isRole($this->profilo)){
			$sql_query="select equery_int, stato from {$this->service}_EQ where
			    {$this->pk_field}={$this->pk_value}
			    and stato = 2
			";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$this->eq_int=$sql->row['EQUERY_INT'];
			$this->stato=$sql->row['STATO'];
//			echo $sql_query;print_r($this->eq_int);die("passo qui");
			return $this->eq_int;
		}else{
    		return null;
		}


	}




/**
 * 
 * Controlla l'esistenza della vista necessaria alle eQ per campo, che in caso negativo viene creata in automatico.
 * 
 * 
 * @return $exist
 */
	function checkCreateEqView($xml_form=null){
		$exist=false;
		
		$query_check_existence_reg = "select view_name from user_views where view_name=upper('{$this->service}_REGISTRAZIONE')
										union
										select table_name from user_tables where table_name=upper('{$this->service}_REGISTRAZIONE')";
//		echo $query_check_existence;
		$query_reg = new query ( $this->conn );
		$query_reg->set_sql ( $query_check_existence_reg );
		$query_reg->exec ();
		if($query_reg->get_row ()){
//			print_r($query->row['VIEW_NAME']);
//			print_r($query_check_existence);
			$exist=true;
		}
		else
		{
			$query_create_reg = "
			CREATE OR REPLACE VIEW {$this->service}_REGISTRAZIONE AS
				SELECT *
			  FROM {$this->service}_REGISTRATION
           ";
			
//			echo $query_create;
			$sql_reg = new query ( $this->conn );
			$sql_reg->set_sql ( $query_create_reg );
			$sql_reg->ins_upd ();
		}
		
		$exist=false;
		
		//creazione vista se non esiste
		$query_check_existence = "select view_name from user_views where view_name=upper('{$this->service}_INTEGRAZIONI_SCHEDE')";
//		echo $query_check_existence;
		$query = new query ( $this->conn );
		$query->set_sql ( $query_check_existence );
		$query->exec ();
		if($query->get_row ()){
//			print_r($query->row['VIEW_NAME']);
//			print_r($query_check_existence);
			$exist=true;
		}
		else
		{
			$query_create = "
			CREATE OR REPLACE VIEW {$this->service}_INTEGRAZIONI_SCHEDE AS
				SELECT DISTINCT REG.SITEID AS SITEID,
				REG.CENTER AS CENTER,
			    REG.SUBJID,
			    EQ.STATO,
				EQ.EQUERY_INT,
			    EQ.INS_DT,
				EQ.CLOSE_DT,
			    EQFIELD.PROGR,
				EQFIELD.ESAM,
				EQFIELD.CODPAT,
			    EQFIELD.VISITNUM,
			    EQFIELD.VISITNUM_PROGR,
				EQFIELD.NOTE,
				EQFIELD.NOTE_DE
			  FROM {$this->service}_EQ EQ, {$this->service}_EQFIELD EQFIELD, {$this->service}_REGISTRAZIONE REG
           WHERE
                EQ.EQUERY_INT=EQFIELD.EQ_INT
           AND
                REG.{$this->pk_field}=EQ.{$this->pk_field}
				AND EQFIELD.FIELD NOT LIKE 'D\_%' escape '\';
			";
			
			$query_create = "
			CREATE OR REPLACE VIEW {$this->service}_INTEGRAZIONI_SCHEDE AS
				SELECT DISTINCT REG.SITEID AS SITEID,
				REG.CENTER AS CENTER,
			    REG.SUBJID,
			    EQ.STATO,
				EQ.EQUERY_INT,
			    EQ.INS_DT,
				EQ.CLOSE_DT,
			    EQFIELD.PROGR,
				EQFIELD.ESAM,
				EQFIELD.CODPAT,
			    EQFIELD.VISITNUM,
			    EQFIELD.VISITNUM_PROGR,
				EQFIELD.NOTE,
				EQFIELD.NOTE_DE
			  FROM {$this->service}_EQ EQ, {$this->service}_EQFIELD EQFIELD, {$this->service}_REGISTRAZIONE REG
           WHERE
                EQ.EQUERY_INT=EQFIELD.EQ_INT
           AND
                REG.{$this->pk_field}=EQ.{$this->pk_field}
				AND EQFIELD.FIELD NOT LIKE 'D\_%' escape '\'
			";
			
//			echo $query_create;
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->ins_upd ();
			$exist=true;
		}
		return $exist;
 	}
 	
 	/**
 	 * Controlla l'abilitazione al modulo eQ, definibile nel file di configurazione del servizio
 	 * 
 	 * @return boolean
 	 * 
 	 */
	function isEnabled($profilo, $config_param){
		/*
		 * Leghiamo questa funzione agli stati in cui  possibile
		 * richiedere integrazioni (parametro definito nel config)
		 * ed al fatto che non ci siano integrazioni in fase di approvazione
		 * sulla stessa pratica (parametrizzabile)
		*/
		if ($config_param['eQuery']!=1){
			return false;
		}
//		print_r($this->role);
//		print_r($this->xmr_tip);
//		print_r($this->approv_role);
        $enabprofs = array();
        if (!is_array($this->role)){
            $enabprofs[] = $this->role;
        }else{
            $enabprofs = array_merge($enabprofs,$this->role);
        }
        if (!is_array($this->approv_role)){
            $enabprofs[] = $this->approv_role;
        }else{
            $enabprofs = array_merge($enabprofs,$this->approv_role);
        }
        if (!is_array($this->control_role)){
            $enabprofs[] = $this->control_role;
        }else{
            $enabprofs = array_merge($enabprofs,$this->control_role);
        }
        //echo "<pre>";
        //print_r($enabprofs);
        //echo "\n".$profilo;
        //echo "</pre>";
		if (!in_array($profilo,$enabprofs)){
			return false;
		}else{
			return true;
		}
	}
    function isRole($profilo){
        $retval = false;
        if (is_array($this->role)){
            $retval = in_array($profilo,$this->role);
        }else{
            $retval = ($this->role == $profilo);
        }
        return $retval;
    }
    function isApprovRole($profilo){
        $retval = false;
        if (is_array($this->approv_role)){
            $retval = in_array($profilo,$this->approv_role);
        }else{
            $retval = ($this->approv_role == $profilo);
        }
        return $retval;
    }
    function isControlRole($profilo){
        $retval = false;
        if (is_array($this->control_role)){
            $retval = in_array($profilo,$this->control_role);
        }else{
            $retval = ($this->control_role == $profilo);
        }
        return $retval;
    }

    function getNewValueEq($eq_int,$eqfield){
    	$sql_valfield = "select VALORE from {$this->service}_EQFIELD where eq_int={$eq_int} and field='{$eqfield}'";
    	//var_dump ( $sql_decfield );
    	$sql1 = new query ( $this->conn );
    	$sql1->set_sql ( $sql_valfield );
    	$sql1->exec ();
    	$sql1->get_row ();
    	//var_dump($sql1->row);
    	// echo $sql_decfield;
    	return $sql1->row ['VALORE'];
    }

	/**
	 * Tale metodo implementa l'approvazione dell'eQ da parte del DM, lo stato passa a 1.
	 * 
	 * @return void
	 */
	function ApprovaEq($vlist,$xml_dir, $config_service, $session_vars, $uploaded_file_dir , $field_ora_approv=null){
		$eq_int=$this->eq_int;
		if($session_vars['EQ_INT_FIELD']!='')
		$eq_int=$session_vars['EQ_INT_FIELD'];

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
			$scheda=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
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
			where eq_int=$eq_int and statofield in (1,3)
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
			$scheda=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
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
					and EQ_INT=$eq_int and statofield in (1,3)
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

			} //fine while

				//limite non si dovrebbe mai presentare un caso con 3 indici di values valorizzati
				foreach($values as $key=>$val) {
					if($key!=$_GET['EQFIELD'] && $key!='D_'.$_GET['EQFIELD'] && $key!=$_GET['EQFIELD'].'RC') unset($values[$key]);
					else $keys[]=$key;
				}
				//print_r($values);
				
				if(count($values)==2) {
					/***Aggiunta da Edo il 18/03/2010 per far entrare in audit trail le equery*/
					if("D_".$keys[0]==$keys[1]) {
						$code=$keys[0];
						$decode=$keys[1];
					} else if("D_".$keys[1]==$keys[0]){
						$code=$keys[1];
						$decode=$keys[0];
					} 
					else if($keys[1]."RC"==$keys[0]){
						$code=$keys[1];
						$decode=$keys[0];
					} 
					else if($keys[0]."RC"==$keys[1]){
						$code=$keys[0];
						$decode=$keys[1];
					}
					
					else {
						error_page($session_vars['REMOTE_USERID'],"Audit trails error for equery","Audit trails error for equery");
					}
					
				}else{
					$code= $keys[0];
				}
				
				/**
				 * Gestione action dell'AT
				 */
				if($config_service['lang']=="en" || $this->config_service['lang']=="en"){
					$txt_DE_eQ="Correction by Investigator";
					$txt_DM_eQ="Correction due to eQuery by Data Manager";
					$txt_CRA_eQ="Correction due to eQuery by CRA";
					$txt_DE_eQ_reopen_mainsub="Obvious correction by Investigator";
		
				}
				else{
					$txt_DE_eQ="Correzione dello sperimentatore";
					$txt_DM_eQ="Correzione dovuta a eQuery del Data Manager";
					$txt_CRA_eQ="Correzione dovuta a eQuery del CRA";
					$txt_DE_eQ_reopen_mainsub="Correzione ovvia Investigatore";
				}
				$session=new query($this->conn);
				$session->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DDMMYYYY'");
				$session->ins_upd();
				
				$query_action="select * from {$this->service}_eqfield eqfield,{$this->service}_eq eq, {$this->service}_utenti_centri uc  where
									ESAM={$session_vars['ESAM']}
									and VISITNUM={$session_vars['VISITNUM']}
									and VISITNUM_PROGR={$session_vars['VISITNUM_PROGR']}
									and PROGR={$session_vars['PROGR']}
									and eq.{$this->pk_field}={$session_vars[$this->pk_field]}
									and eqfield.eq_int=eq.equery_int
									and eqfield.eq_int={$session_vars['EQ_INT_FIELD']}
									and field='{$code}'
									and uc.userid=eq.userid_ins 
									and uc.center='{$session_vars['CENTER']}'
									";
				$sql4=new query($this->conn);
				$sql4->exec($query_action);
				$sql4->get_row();
				if($sql4->row['TIPOLOGIA']=='Data manager'){$action=$txt_DM_eQ;}
				elseif($sql4->row['TIPOLOGIA']=='Data Entry'){
					if($sql4->row['FIELD']==$xml_form->form['MAIN_FIELD'] && $sql4->row['VALORE']==$xml_form->form['MAIN_FIELD_VALUE'] && $vlist->esams[$session_vars['VISITNUM']][$session_vars['ESAM']]['MAIN']=="yes"){
						/*Caso della riapertura di una main-sub , effettuo un eQ automatica e auto-approvata , con questa ragione*/
						$action=$txt_DE_eQ_reopen_mainsub;
					}
					else{
						$action=$txt_DE_eQ;
					}
				}
				elseif($sql4->row['TIPOLOGIA']=='CRA'){$action=$txt_CRA_eQ;}
				
				/***/

				$query_old_value="select * from $table where
									ESAM={$session_vars['ESAM']}
									and VISITNUM={$session_vars['VISITNUM']}
									and VISITNUM_PROGR={$session_vars['VISITNUM_PROGR']}
									and PROGR={$session_vars['PROGR']}
									and {$this->pk_field}={$session_vars[$this->pk_field]}
									";
				$sql3=new query($this->conn);
				$sql3->exec($query_old_value);
				$sql3->get_row();
				$old_value=$sql3->row[$code];
				$d_old_value=$sql3->row[$decode];
				$userid_ins=$sql3->row['USERID_INS'];
				
				
//				echo $userid_ins;echo "<- user <br>";
//				echo $values[$code]; echo "<- new <br>";
//				echo $old_value; echo "<- old <br>";
//				echo $values[$decode]; echo "<- new <br>";
//				echo $d_old_value; echo "<- old <br>";
				
				if($values[$code]!=$old_value){
					$values_at['CODPAT']=$session_vars['CODPAT'];
					$values_at['ESAM']=$session_vars['ESAM'];
					$values_at['PROGR']=$session_vars['PROGR'];
					$values_at['VISITNUM']=$session_vars['VISITNUM'];
					$values_at['VISITNUM_PROGR']=$session_vars['VISITNUM_PROGR'];
					$values_at['CENTER']=$session_vars['CENTER'];
					$values_at['VALUE_NEW']=$values[$code];
					$values_at['D_VALUE_NEW']=$values[$decode];
					$values_at['VALUE_OLD']=$old_value;
					$values_at['D_VALUE_OLD']=$d_old_value;
					$values_at['NOMETAB']=$table;
					$values_at['VAR']=$code;
					$values_at['FIELD']="null";
					$values_at['MODDT']="sysdate";
					$values_at['ACTION']=$action;
					$values_at['USERID']=$userid_ins;
					//print_r($values_at);
					if($keys[0]."RC"==$keys[1]){
						// Gestione NA NK per campi date modificati nell'eQ per l'AT
					   	$offset = 0;
                        if (substr($values[$code] , 0,2)== 'to') {
					   	    $offset = 9;
					   	}
						if(substr($values[$decode], 0,2)!='OK'){
								$dd=substr($values[$decode],(0+$offset),2);

						}	else {
						    $dd=substr($values[$code], (0+$offset),2);
                        }
						if(substr($values[$decode], 2,2)!='OK'){
								$mm=substr($values[$decode],(2+$offset),2);
						}	else $mm=substr($values[$code], (2+$offset),2);
						if(substr($values[$decode], 4,2)!='OK'){
								$yyyy=substr($values[$decode],(4+$offset),2);
						}	else $yyyy=substr($values[$code], (4+$offset),4);

						
						$values_at['VALUE_NEW']=$dd.$mm.$yyyy;
						$values_at['D_VALUE_NEW']="";
						
						if(substr($d_old_value, 0,2)!='OK'){
								$dd=substr($d_old_value,0,2);
						}	else $dd=substr($old_value, 0,2);
						if(substr($d_old_value, 2,2)!='OK'){
								$mm=substr($d_old_value,2,2);
						}	else $mm=substr($old_value, 2,2);
						if(substr($d_old_value, 4,2)!='OK'){
								$yyyy=substr($d_old_value,4,2);
						}	else $yyyy=substr($old_value, 4,4);
						
						$values_at['VALUE_OLD']=$dd.$mm.$yyyy;
						$values_at['D_VALUE_OLD']="";
					}
					$sql5=new query($this->conn);
					$sql5->insert($values_at, "S_X_".$this->service);
					$this->conn->commit();
				}
				elseif($values[$decode]!=$d_old_value){
					$values_at['CODPAT']=$session_vars['CODPAT'];
					$values_at['ESAM']=$session_vars['ESAM'];
					$values_at['PROGR']=$session_vars['PROGR'];
					$values_at['VISITNUM']=$session_vars['VISITNUM'];
					$values_at['VISITNUM_PROGR']=$session_vars['VISITNUM_PROGR'];
					$values_at['CENTER']=$session_vars['CENTER'];
					$values_at['VALUE_NEW']=$values[$code];
					$values_at['D_VALUE_NEW']=$values[$decode];
					$values_at['VALUE_OLD']=$old_value;
					$values_at['D_VALUE_OLD']=$d_old_value;
					$values_at['NOMETAB']=$table;
					$values_at['VAR']=$code;
					$values_at['FIELD']="null";
					$values_at['MODDT']="sysdate";
					$values_at['ACTION']=$action;
					$values_at['USERID']=$userid_ins;
					//print_r($values_at);
					
					if($keys[0]."RC"==$keys[1]){
						// Gestione NA NK per campi date modificati nell'eQ per l'AT
						if(substr($values[$decode], 0,2)!='OK'){
								$dd=substr($values[$decode],0,2);
						}	else $dd=substr($values[$code], 0,2);
						if(substr($values[$decode], 2,2)!='OK'){
								$mm=substr($values[$decode],2,2);
						}	else $mm=substr($values[$code], 2,2);
						if(substr($values[$decode], 4,2)!='OK'){
								$yyyy=substr($values[$decode],4,2);
						}	else $yyyy=substr($values[$code], 4,4);
						
						$values_at['VALUE_NEW']=$dd.$mm.$yyyy;
						$values_at['D_VALUE_NEW']="";
						
						if(substr($d_old_value, 0,2)!='OK'){
								$dd=substr($d_old_value,0,2);
						}	else $dd=substr($old_value, 0,2);
						if(substr($d_old_value, 2,2)!='OK'){
								$mm=substr($d_old_value,2,2);
						}	else $mm=substr($old_value, 2,2);
						if(substr($d_old_value, 4,2)!='OK'){
								$yyyy=substr($d_old_value,4,2);
						}	else $yyyy=substr($old_value, 4,4);
						
						$values_at['VALUE_OLD']=$dd.$mm.$yyyy;
						$values_at['D_VALUE_OLD']="";
					}
					$sql5=new query($this->conn);
					$sql5->insert($values_at, "S_X_".$this->service);
					$this->conn->commit();
				}
			/******/
			/**
			 * Nel caso dei campi ora, viene valorizzato un flag in più nel button OK dentro field.inc
			 * Nel controller , dove viene chiamato questo metodo , viene settato $field_ora_approv=yes se la GET[ORA]==yes
			 */
			if($field_ora_approv=="ora"){
				$values[$_GET['EQFIELD']."_H"]=substr($values[$code],0,2);
				$values[$_GET['EQFIELD']."_M"]=substr($values[$code],2,2);
			}
			elseif($field_ora_approv=="date"){
				$values[$_GET['EQFIELD']."RC"]=$values[$code."RC"];
			}
			$sql2->set_sql($sql_storico);
			$sql2->ins_upd();
			if(!empty($values)){ //vmazzeo 26.02.2015 bugfix generato dalla creazione delle realtime equery
				//dmengoli 06.07.2015 -> fix per creazione equery su form mai salvate
				$sql_check="
				select count(*) as conto
				from $table
				where {$this->pk_field}={$pk[$this->pk_field]}
				and esam={$pk['ESAM']}
				and visitnum={$pk['VISITNUM']}
				and visitnum_progr={$pk['VISITNUM_PROGR']}
				and progr = {$pk['PROGR']}
				";
				$sql2=new query($this->conn);
				$sql2->get_row($sql_check);
				//die("CONTOROW: ".$sql2->row['CONTO']);
				if ($sql2->row['CONTO']==0) {
					$insvalues = array_merge($values,$pk);
					$insvalues['USERID_INS'] = $this->userid;
					$sql2->get_row("SELECT CENTER FROM {$this->service}_{$this->config_service['RegTable']} WHERE $this->pk_field = {$pk[$this->pk_field]}");
					$insvalues['CENTER'] = $sql2->row['CENTER'];
					//var_dump($insvalues);
					$sql2->insert($insvalues, $table, $pk);
				}else{
					//echo("CIAO4.1?<br/>\n");
					//var_dump($values); //checkbox Modificato
					$val_tmp = $values;
					foreach ($val_tmp as $k=>$v){
						if (strtoupper($v)=="CHECKBOX MODIFICATO"){
							//Devo confermare anche tutti gli altri checkboxes...
							//var_dump($xml_form);
							foreach ($xml_form->fields as $f){
								if ($f['VAR']==$k && ($f['TYPE']=='checkbox' || $f['TYPE']=='checkbox_hyper') ){
									//var_dump($f);
									//die("STA QUAQUA");
									unset($values[$k]);
									foreach($f['VALUE'] as $innerval => $innertxt){
										$this->ApprovaEqField($eq_int, $innerval, "");
										$values[$innerval]=$this->getNewValueEq($eq_int,$innerval);
									}
									//die("MOLTO BENE");
									break;
								}
							}
							//die("STO QUA CKBOX!");
						}
					}
					//var_dump($values);
					//die("FINE??");
					if ($values){
					$sql2->update($values, $table, $pk);
				}
					//echo("CIAO4.2?<br/>\n");
				}
			}
			if(class_exists('SDV_module')){
				$xml=$vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML'];
				$xml_form = new xml_form ( $this->conn, $this->service, $config_service, $session_vars, $uploaded_file_dir );
				$xml_form->xml_form_by_file ( $xml_dir . '/' . $xml );
				$sdv=new SDV_module($this->conn,$session_vars,$config_service,$this->service,$vlist,$xml_dir);
				$result=$sdv->after_ApprovaEq($xml_form);
			}
		}
//die();
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
//		$sql_update="update {$this->service}_EQ set close_dt=sysdate where equery_int=$eq_int";
//		$sql->set_sql($sql_update);
//		$sql->ins_upd();
		
		$this->conn->commit();
//		$sql_update="update {$this->service}_EQ set stato=1, close_dt=sysdate where equery_int=$eq_int";
//		$sql->set_sql($sql_update);
//		$sql->ins_upd();
//		$this->conn->commit();

			if($vlist->esams[$_GET['VISITNUM']][$_GET['ESAM']]['SUB']=="yes"){
				//Se la form è una Sub ed ha tutti i campi vuoti passa allo stato deleted.
				 $this->CheckSubIsDeleted($xml_form , $table ,$session_vars);	
			}

	}


	function CheckSubIsDeleted($xml_form , $table, $session_vars){
			$sql_sub_deleted="select * from {$table} where CODPAT={$session_vars['CODPAT']} and esam={$session_vars ['ESAM']}
			and progr={$session_vars ['PROGR']} and visitnum_progr={$session_vars ['VISITNUM_PROGR']}
							";
							
//			echo $sql_sub_deleted;die();
			$sql = new query ( $this->conn );
			$sql->set_sql($sql_sub_deleted);
			$sql->exec();
			$sql->get_row();
			$fields=$sql->row;
			
			$primarykeys['CODPAT']="CODPAT";
			$primarykeys['CENTER']="CENTER";
			$primarykeys['USERID_INS']="USERID_INS";
			$primarykeys['ESAM']="ESAM";
			$primarykeys['VISITNUM']="VISITNUM";
			$primarykeys['VISITNUM_PROGR']="VISITNUM_PROGR";
			$primarykeys['PROGR']="PROGR";
			
			$sub_is_deleted_by_eq=true;
			foreach($fields as $key => $val){
					if( !in_array($key , $primarykeys)){
							if($val!=''){$sub_is_deleted_by_eq=false;}
//								echo 	$key."<BR>";
					}
			}
			
			if($sub_is_deleted_by_eq==true){
					$pk_delete['CODPAT']=$session_vars['CODPAT'];
					$pk_delete['ESAM']=$session_vars['ESAM'];
					$pk_delete['PROGR']=$session_vars['PROGR'];
					$pk_delete['VISITNUM']=$session_vars['VISITNUM'];
					$pk_delete['VISITNUM_PROGR']=$session_vars['VISITNUM_PROGR'];
					$values['DELETED']=1;
					
					$sql2 = new query ( $this->conn );
					$sql2->update($values, $table, $pk_delete);
					
					$table_coord=$this->service."_COORDINATE";
					$values_coord['ABILITATO']=2;
					$sql3 = new query ( $this->conn );
					$sql3->update($values_coord, $table_coord, $pk_delete);
						
			}
			
//			print_R($sql2->str);print_R($sql3->str);
			$this->conn->commit();
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
        /*
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
        */
        $sql->insert($val_th,$this->service."_EQ","");
        $this->conn->commit();
        return $this->eq_int;
    }

	/**
	 * Gestione Nuove eQuery , aggiungere sulle hyperlibs.
	 *
	 * ////////////////////////
	 *
	 * /**
	 * METODI:
	 *
	 *
	 * make_patient_table(): come quello di libreria ma viene aggiunto l'HTML dello specchietto di approvazione eQ per il DM.
	 *
	 * SaveEqInt(): crea l'oggetto realitvo alla form e chiama il SaveEqInt() di integrazioni.inc.
	 *
	 * GenerateEqDM($eq_DM): effettua il salvataggio in DB dell'eQ fatta dal DM, prende i valori dei commenti ai campi fatti dal DM
	 *
	 * ApprovaEqField($eq_int,$eqfield,$d_eqfield): Viene gestita l'approvazione della eQ a livello di campo per il profilo APPROV_ROLE
	 *
	 * function RifiutaEqField($eq_int,$eqfield,$d_eqfield): Viene gestito il rifiuto della eQ a livello di campo da parte del profilo APPROV_ROLE
	 */

	/**
	 * SaveEqInt()
	 * Gestisce la generazione di un eQ a livello di campo associando l'identificativo alla singola eQ e popolando il DB.
	 */
	function SaveEqInt() {
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
		$visite_exams_path = str_replace ( "index.php", "", $_SERVER ['SCRIPT_FILENAME'] ) . "xml/visite_exams.xml";
		$vlist = new xml_esams_list ( $visite_exams_path, $this->config_service, $this->session_vars, $this->conn );
		$xml = $vlist->esams [$_POST ['VISITNUM']] [$_POST ['ESAM']] ['XML'];

		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
		// $this->integrazione->SaveEqInt($xml_form);

		$this->SaveEqDE ( $xml_form );
		global $in;
		header ( "location: index.php?exams=visite_exams.xml&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}" );
		die ();
	}

	/**
	 * GenerateEqDM($eq_DM)
	 * Gestisce la generazione di un eQ a livello di campo associando l'identificativo alla singola eQ e popolando il DB.
	 * La gestione  unicamente dedicata al caso del profile APPROV_ROLE.
	 */
	function GenerateEqDM($eq_DM) {
		$vals = '';
		$pk = '';
		$vals2 = '';
		$pk2 = '';

		global $in;
		/**
		 * Creazione del field statement e dell'array dei field relativi alla form.
		 */
		$visite_exams_path = str_replace ( "index.php", "", $_SERVER ['SCRIPT_FILENAME'] ) . "xml/visite_exams.xml";
		$vlist = new xml_esams_list ( $visite_exams_path, $this->config_service, $this->session_vars, $this->conn );
		$form = $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['XML'];
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $in, $this->uploaded_file_dir );
		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
		foreach ( $xml_form->fields as $key => $val ) {
			if ($val ['VAR'] != '' && $val ['TB'] != 'no') {
				if (! isset ( $_POST [$val ['VAR']] ) || $_POST [$val ['VAR']] == '')
					$_POST [$val ['VAR']] = 0;
				$field_type = "field_{$val['TYPE']}";
				include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/field.inc";
				// echo $val['VAR'];
				//echo "class_exists ? {$_SERVER['DOCUMENT_ROOT']}/../libs/{$field_type}.inc ? ".file_exists ( $_SERVER['DOCUMENT_ROOT']."/../libs/"$field_type}.inc");
				// if (file_exists("libs/{$field_type}.inc")) include_once "libs/{$field_type}.inc";
				// else include_once "libs/fields/{$field_type}.inc";
				/**
				 * Modifica 08/09/2011
				 * Carico prima i campi modificati per servizio se esistono
				 * M.
				 * Verrocchio
				 */
				if (! class_exists ( $field_type )) {
					if ($this->config_service ['field_lib'] != '' && file_exists ( $this->config_service ['field_lib'] . $field_type . ".inc" )) {
						include_once $this->config_service ['field_lib'] . $field_type . ".inc";
					} elseif (file_exists ( "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc" )) {
						include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc";
					} else {
						include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/fields/{$field_type}.inc";
					}
				}
				$field_obj = new $field_type ( $xml_form, $xml_form->vars [$val ['VAR']], $this->conn, $xml_form->tb_vals, $in, $this->service, $xml_form->errors );
				$field_obj->insert_stmt ();

				foreach ( $field_obj->field_stmt as $f => $fv ) {
					$fields [] = $fv;
					$fieldsById [$fv] = $field_obj->id;
					$fieldsByField [$field_obj->id] [$fv] = true;
				}
				foreach ( $field_obj->value_stmt as $f => $fv ) {
					$values [] = $fv;
				}
			}
		}
		/**
		 * Fine creazione del field statement e dell'array dei field relativi alla form.
		 */

		foreach ( $eq_DM as $k => $v ) {
			$pattern = '/^EQAREA_/';
			// Prendo solo i commenti che si riferiscono ai campi della form, non le variabli hidden come codpat etc..
			// echo preg_match($pattern,$k);
			if ($v != '' && preg_match ( $pattern, $k )) {

				// $vals , per la tabella SERVIZIO_EQ, $vals2 , per la tabella SERVIZIO_EQFIELD:
				$sqlseq = new query ( $this->conn );
				$sequence = "select {$this->service}_eqseq.nextval as eq_int from dual";
				$sqlseq->get_row ( $sequence );
				$vals2 ['EQ_INT'] = $vals ['EQUERY_INT'] = $sqlseq->row ['EQ_INT'];

				// print_r($this->config_service['PK_SERVICE']);
				$sql = new query ( $this->conn );
				$vals2 [$this->config_service ['PK_SERVICE']] = $vals [$this->config_service ['PK_SERVICE']] = $eq_DM [$this->config_service ['PK_SERVICE']];
				$vals ['USERID_INS'] = $eq_DM ['USERID_INS'];
				$vals ['INS_DT'] = 'sysdate';
				$vals ['STATO'] = '0';
				$vals ['RICH_DM'] = $eq_DM ['EQCOMMENT'];

				// print_r($vals);
				$sql->insert ( $vals, $this->service . "_EQ", $pk );
				$this->conn->commit ();
				// echo $eq_DM['TABLE'];

				// EQFIELD
				$sql2 = new query ( $this->conn );

				// Prendo i valori dalla banca dati della scheda chiusa
				$sql_table = "select * from {$eq_DM['TABLE']} where {$this->config_service['PK_SERVICE']}={$eq_DM[$this->config_service['PK_SERVICE']]} and esam={$eq_DM['ESAM']}
							and visitnum={$eq_DM['VISITNUM']} and progr={$eq_DM['PROGR']} and visitnum_progr={$eq_DM['VISITNUM_PROGR']}
							";
				$sql2 = new query ( $this->conn );
				$sql2->set_sql ( $sql_table );
				$sql2->exec ();
				$sql2->get_row ();
				$table_vals = $sql2->row;
				// print_r($table_vals);

				// Prendo tutto $k tranne le prime sette lettere, sarebbe EQAREA_
				// echo substr($k,7);
				$fieldInEqArea = substr ( $k, 7 );
				$fieldId = $fieldsById [$fieldInEqArea];
				//var_dump ( $fieldsByField [$fieldId] );
				$insertedFields = "";
				foreach ( $fieldsByField [$fieldId] as $eqFk => $eqFv ) {
					$vals2 ['ESAM'] = $eq_DM ['ESAM'];
					$vals2 ['VISITNUM'] = $eq_DM ['VISITNUM'];
					$vals2 ['VISITNUM_PROGR'] = $eq_DM ['VISITNUM_PROGR'];
					$vals2 ['PROGR'] = $eq_DM ['PROGR'];
					$vals2 ['FIELD'] = $eqFk;
					$vals2 ['NOTE'] = $v;
					$vals2 ['VALORE'] = $table_vals [substr ( $k, 7 )];
					$vals2 ['STATOFIELD'] = 0;
					$sql2->insert ( $vals2, $this->service . "_EQFIELD", $pk2 );
					$insertedFields [$eqFk] = true;
				}
				if (! isset ( $insertedFields [$fieldId] )) {
					$vals2 ['ESAM'] = $eq_DM ['ESAM'];
					$vals2 ['VISITNUM'] = $eq_DM ['VISITNUM'];
					$vals2 ['VISITNUM_PROGR'] = $eq_DM ['VISITNUM_PROGR'];
					$vals2 ['PROGR'] = $eq_DM ['PROGR'];
					$vals2 ['FIELD'] = $fieldId;
					$vals2 ['NOTE'] = $v;
					$vals2 ['VALORE'] = $table_vals [substr ( $k, 7 )];
					$vals2 ['STATOFIELD'] = 0;
					$sql2->insert ( $vals2, $this->service . "_EQFIELD", $pk2 );
					$insertedFields [$eqFv] = true;
				}

				/*
				 * //Gestione delle decodifiche: foreach($fields as $ke=>$va){ $field_pending=substr($k,7); if("D_{$field_pending}"==$va){ //						echo $va; $vals2['FIELD']="D_{$field_pending}"; $vals2['NOTE']=$v; //				echo $table_vals[substr($k,7)]; $vals2['VALORE']=$table_vals[substr($k,7)]; $vals2['STATOFIELD']=0; //				print_r($vals2); $sql2->insert($vals2, $this->service."_EQFIELD",$pk2); } if($field_pending."RC"==$va){ //						echo $va; $vals2['FIELD']=$field_pending."RC"; $vals2['NOTE']=$v; //				echo $table_vals[substr($k,7)]; $vals2['VALORE']=$table_vals[substr($k,7)."RC"]; $vals2['STATOFIELD']=0; //				print_r($vals2); $sql2->insert($vals2, $this->service."_EQFIELD",$pk2); } }
				 */
			}
		}
		$this->conn->commit ();
		if (!isset($eq_DM['REALTIME_EQUERIES'])){
			header ( "location: index.php?exams=visite_exams.xml&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&CENTER={$in['CENTER']}" );
		}
		else{
			return true;
		}
	}

	/**
	 * ApprovaEqField($eq_int,$eqfield,$d_eqfield)
	 * Viene gestita l'approvazione della eQ a livello di campo per il profilo APPROV_ROLE
	 *
	 * @param number $eq_int
	 * @param number $eqfield
	 * @param string $d_eqfield
	 *
	 */
	function ApprovaEqField($eq_int, $eqfield, $d_eqfield) {
		//debug_print_backtrace();
		//die();
		// echo $eq_int;
		// echo $eqfield;
		$sql2 = new query ( $this->conn );
		$pk ['EQ_INT'] = $eq_int;
		$pk ['FIELD'] = $eqfield;
		$values ['STATOFIELD'] = 1;
		$sql2->update ( $values, "{$this->service}_EQFIELD", $pk );
		$this->conn->commit ();

		$sql_decfield = "select count(*) as d_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='D_{$eqfield}'";
		//var_dump ( $sql_decfield );
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['D_EQFIELD'] != '') {

			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = "D_$eqfield";
			$values ['STATOFIELD'] = 1;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}

		$sql_orafield = "select count(*) as ora_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field in ('{$eqfield}_H','{$eqfield}_M')";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_orafield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['ORA_EQFIELD'] != '') {
			$sqlora = new query ( $this->conn );
			$pk2 = array ();
			$values = array ();
			$pk2 ['EQ_INT'] = $eq_int;
			$pk2 ['FIELD'] = $eqfield . "_H";
			$values ['STATOFIELD'] = 1;
			// print_r($values);print_r($this->conn);print_r($this->service);print_r($pk2);
			$sqlora->update ( $values, "{$this->service}_EQFIELD", $pk2 );
			$this->conn->commit ();

			$sqlmin = new query ( $this->conn );
			$pk3 ['EQ_INT'] = $eq_int;
			$pk3 ['FIELD'] = $eqfield . "_M";
			$values ['STATOFIELD'] = 1;
			$sqlmin->update ( $values, "{$this->service}_EQFIELD", $pk3 );
			$this->conn->commit ();
		}

		$sql_decfield = "select count(*) as date_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='{$eqfield}RC'";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;die();
		if ($sql1->row ['DATE_EQFIELD'] != '') {

			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = $eqfield . "RC";
			$values ['STATOFIELD'] = 1;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}

		$sql_table = "select count(*) as conto from {$this->service}_EQFIELD where eq_int={$eq_int} and statofield in (0,2)";
		$sql4 = new query ( $this->conn );
		$sql4->set_sql ( $sql_table );
		$sql4->exec ();
		$sql4->get_row ();
		$eq_pending = $sql4->row ['CONTO'];
		// echo $sql_table;
		// echo $eq_pending;
		if ($eq_pending == 0) {
			$sql5 = new query ( $this->conn );
			$pk5 ['EQUERY_INT'] = $eq_int;
			$values5 ['CLOSE_DT'] = 'sysdate';
			$values5 ['STATO'] = 1;
			$sql5->update ( $values5, "{$this->service}_EQ", $pk5 );
			$this->conn->commit ();

			// $this->integrazione->ApprovaEq($this->vlist,$this->xml_dir,$this->config_service, $this->session_vars, $this->uploaded_file_dir);
		}

		/*
		 * Riapertura della firma elettronica quando si approva una eQuery Verrocchio 05/07/2011 Verri 05/07/2013
		 */
		global $in;
		if ($in ['USER_TIP'] == 'DM') {
			$electronic_signature_esam = array ();
			$visite_exams_path = str_replace ( "index.php", "", $_SERVER ['SCRIPT_FILENAME'] ) . "xml/visite_exams.xml";
			$vlist = new xml_esams_list ( $visite_exams_path, $this->config_service, $this->session_vars, $this->conn );
			/* Numero dell'esame skip_visit della visita */
			$visit_num = array ();
			foreach ( $vlist->esams as $key => $val ) {
				foreach ( $val as $k => $v ) {
					if ($v ['XML'] == 'esign.xml') {
						$electronic_signature_esam [$key] = $v ['NUMBER'];
					}
				}
			}
			// Per tutte le signature
			foreach ( $electronic_signature_esam as $visit_num => $esam_num ) {
				$query = new query ( $this->conn );
				unset ( $vals );
				$vals ['PK_SERVICE'] = $in [$this->config_service ['PK_SERVICE']];
				$vals ['VISITNUM'] = $visit_num;
				$vals ['ESAM'] = $esam_num;
				$vals ['PROGR'] = "1"; //-> Esame di firma mai progressivo (Se progressivo utilizzare il MAX(PROGR) //$this->session_vars ['PROGR'];
				$vals ['VISITNUM_PROGR'] = ($in ['VISITNUM_PROGR']?$in ['VISITNUM_PROGR']:0);
				$sql_query = "SELECT * FROM {$this->config_service['service']}_COORDINATE WHERE {$this->config_service['PK_SERVICE']}=:PK_SERVICE AND ESAM=:ESAM and VISITNUM=:VISITNUM AND PROGR=:PROGR AND VISITNUM_PROGR=:VISITNUM_PROGR";
				$query->exec ( $sql_query, $vals );
				$query->get_row ();
				if ($query->row ['FINE'] == 1) {
					// Riapro la Electronic Signature
					$query = new query ( $this->conn );
					unset ( $vals );
					$vals ['CODPAT'] = $in [$this->config_service['PK_SERVICE']];
					$vals ['VISITNUM'] = $visit_num;
					$vals ['ESAM'] = $esam_num;
					$sql_query = "UPDATE {$this->service}_COORDINATE SET FINE='0' WHERE {$this->config_service['PK_SERVICE']}=:CODPAT AND VISITNUM=:VISITNUM AND ESAM=:ESAM";
					$query->exec ( $sql_query, $vals );

					$query = new query ( $this->conn );
					unset ( $vals );
					$vals ['CODPAT'] = $in [$this->config_service['PK_SERVICE']];
					$vals ['VISITNUM'] = $visit_num;
					$sql_query = "UPDATE {$this->service}_COORDINATE SET VISITCLOSE='0' WHERE {$this->config_service['PK_SERVICE']}=:CODPAT AND VISITNUM=:VISITNUM";
					$query->exec ( $sql_query, $vals );
				}
			}

			//Ripaertura visita (e quindi possibilità di reinserire record main/sub se ho modificato il valore del filed propedeutico di una MAIN
			$visite_exams_path = str_replace ( "index.php", "", $_SERVER ['SCRIPT_FILENAME'] ) . "xml/visite_exams.xml";
			$vlist = new xml_esams_list ( $visite_exams_path, $this->config_service, $this->session_vars, $this->conn );
			$form = $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['XML'];
			$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $in, $this->uploaded_file_dir );
			$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
			//var_dump($xml_form);
			//xml_form->form['MAIN_FIELD']
			var_dump($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']]);
			if ($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['MAIN']){
				//Placeholder per esame MAIN
				//die("MAIN");
			}

			//Riapro tutta la visita che coinvolge l'esame in eQuery
			$query = new query ( $this->conn );
			unset ( $vals );
			$vals ['CODPAT'] = $in [$this->config_service['PK_SERVICE']];
			$vals ['VISITNUM'] = $in ['VISITNUM'];
			$sql_query = "UPDATE {$this->service}_COORDINATE SET VISITCLOSE='0' WHERE {$this->config_service['PK_SERVICE']}=:CODPAT AND VISITNUM=:VISITNUM";
			$query->exec ( $sql_query, $vals );

		}
		return true;

	}

	/**
	 * RifiutaEqField($eq_int,$eqfield,$d_eqfield)
	 * Viene gestito il rifiuto della eQ a livello di campo da parte del profilo APPROV_ROLE
	 *
	 * @param number $eq_int
	 * @param number $eqfield
	 * @param string $d_eqfield
	 *
	 */
	function RifiutaEqField($eq_int, $eqfield, $d_eqfield) {
		global $in;
		// echo $eq_int;
		// echo $eqfield;
		$sql2 = new query ( $this->conn );
		$pk ['EQ_INT'] = $eq_int;
		$pk ['FIELD'] = $eqfield;
		$values ['STATOFIELD'] = 3;
		$sql2->update ( $values, "{$this->service}_EQFIELD", $pk );
		$this->conn->commit ();
		// echo $d_eqfield;

		$sql_decfield = "select count(*) as d_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='D_{$eqfield}'";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['D_EQFIELD'] != '') {
			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = "D_$eqfield";
			$values ['STATOFIELD'] = 3;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}

		$sql_orafield = "select count(*) as ora_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field in ('{$eqfield}_H','{$eqfield}_M')";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_orafield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['ORA_EQFIELD'] != '') {
			$sqlora = new query ( $this->conn );
			$pk2 = array ();
			$values = array ();
			$pk2 ['EQ_INT'] = $eq_int;
			$pk2 ['FIELD'] = $eqfield . "_H";
			$values ['STATOFIELD'] = 3;
			// print_r($values);print_r($this->conn);print_r($this->service);print_r($pk2);
			$sqlora->update ( $values, "{$this->service}_EQFIELD", $pk2 );
			$this->conn->commit ();

			$sqlmin = new query ( $this->conn );
			$pk3 ['EQ_INT'] = $eq_int;
			$pk3 ['FIELD'] = $eqfield . "_M";
			$values ['STATOFIELD'] = 3;
			$sqlmin->update ( $values, "{$this->service}_EQFIELD", $pk3 );
			$this->conn->commit ();
		}

		$sql_decfield = "select count(*) as date_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='{$eqfield}RC'";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['DATE_EQFIELD'] != '') {
			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = $eqfield . "RC";
			$values ['STATOFIELD'] = 3;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}

		$sql_table = "select count(*) as conto from {$this->service}_EQFIELD where eq_int={$eq_int} and statofield in (0,2)";
		$sql4 = new query ( $this->conn );
		$sql4->set_sql ( $sql_table );
		$sql4->exec ();
		$sql4->get_row ();
		$eq_pending = $sql4->row ['CONTO'];
		// echo $sql_table;
		// echo $eq_pending;
		if ($eq_pending == 0) {
			$sql5 = new query ( $this->conn );
			$pk5 ['EQUERY_INT'] = $eq_int;
			$values5 ['CLOSE_DT'] = 'sysdate';
			$values5 ['STATO'] = 1;
			$sql5->update ( $values5, "{$this->service}_EQ", $pk5 );
			$this->conn->commit ();
		}
	}
	/**
	 * Fine Gestione Nuove eQuery
	 */

}
