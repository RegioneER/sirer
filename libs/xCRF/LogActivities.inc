<?
include_once "db.inc";

/**
 * Classe LogActivities
 * Classe per la gestione del log delle attività lato client
 * @package XMR Hyperlibs
 *
 */

class LogActivities {
	
	var $log_dir = "/log_trace";
	var $sessions_vars;
	var $lang;
	var $service;
	var $pk_service;
	
	/**
	 * Costruttore: allineamento e verifica della tabella di sessione in banca dati.
	 *
	 */
	function __construct($sessions_vars,$lang='en' , $service , $pk_service, $config_param) {
		$this->session_vars = $sessions_vars;
		$this->lang = $lang;
		$this->service = $service;
		$this->pk_service = $pk_service;

        if ($config_param['production'] != 1) {
            $sessions_cols = array('ID' => 'NUMBER not null',
                'SESSION_ID' => 'CHAR(32)',
                'USERID' => 'VARCHAR2(32 CHAR)',
                'DATA' => 'DATE',
                'URL' => 'VARCHAR2(2000)',
                'REFERER' => 'VARCHAR2(2000)',
                'TIPO' => 'VARCHAR2(20)');
            $conn = new dbconn();
            $query = new query($conn);
            $query_check_existence = "SELECT COLUMN_NAME FROM USER_TAB_COLUMNS WHERE TABLE_NAME='SESSIONS'";
            $query->set_sql($query_check_existence);
            $query->exec();
            while ($query->get_row()) {
                $tb_vals [$query->row ['COLUMN_NAME']] = $query->row ['COLUMN_NAME'];
            }
            foreach ($sessions_cols as $key => $val) {
                if (!in_array($key, $tb_vals)) {
                    $alter_sessions_table = "ALTER TABLE SESSIONS ADD $key $val";
                    $query->set_sql($alter_sessions_table);
                    $query->exec();
                }
            }

            $this->CheckLogDir(); //Attenzione che in questo modo in produzione non verrebbe rigenerata la cartella dei log alla sua cancellazione
        }
	}
	
	/**
	 * CheckLogDir();
	 * 
	 * Controllo esistenza direttorio per il log.
	 */
	private function CheckLogDir() {
		if (! is_dir ( $GLOBALS ['dir'] . $this->log_dir )) {
			mkdir ( $GLOBALS ['dir'] . $this->log_dir, 0777 );
			//			chmod($file_log, 0777);
			chmod ( $GLOBALS ['dir'] . $this->log_dir, 0777 );
		}
	}
	
	/**
	 * DoLog();
	 * 
	 * Gestione log dell'utente, via filesystem e banca dati
	 */
	public function DoLog($force_log=false) {
        $in=null;
		//File e Tabella di Log solo in produzione
		$remote_userid=$this->session_vars['remote_userid'];
		$url = "https://" . $_SERVER ['HTTP_HOST'] . $_SERVER ['REQUEST_URI'];
		$url_from = $_SERVER ['HTTP_REFERER'];
		$url_tipo = "";
		if(strpos ( $url, '&form=' ) && !$this->CheckFormClosed()) {
			// Form aperta
			$url_tipo = "F";
		} elseif(strpos ( $url, '&form=' )) {
			// Form chiusa
			$url_tipo = "C";
		}
		$session_id = substr($_SERVER['HTTP_SHIB_SESSION_ID'], 1, 32);
		
		// Controllo che l'ultima riga di sessione sia diversa
		$log_conn = new dbconn ( );
		$q_log = new query ( $log_conn );
		$sql = "select * from (select * from sessions t order by data desc) where rownum=1";
		$q_log->set_sql ( $sql );
		$q_log->exec ();
		$q_log->get_row ();
		if ((($q_log->numrows == 0) || trim ( $q_log->row ['USERID'] ) != trim ( $remote_userid ) || trim ( $q_log->row ['URL'] ) != trim ( $url ) || trim ( $q_log->row ['TIPO'] ) != trim ( $url_tipo )) && trim ( $remote_userid ) != '' && trim ( $url ) != '') {
			$dir=$_SERVER['PATH_TRANSLATED'];
			$dirs=explode("/", $dir);
			$dir='';
			for ($i=0;$i<count($dirs)-1;$i++){
				$dir.=$dirs[$i]."/";
			}
			$dir=rtrim($dir, "/");
			$file_log = $dir . $this->log_dir ."/". strtoupper ( $remote_userid ) . ".log";
			$sql = "select max(id) as ID from sessions";
			$q_log->set_sql ( $sql );
			$q_log->exec ();
			$q_log->get_row ();
			$session_number = $q_log->row ['ID'] + 1;
			
			// Uso il binding
			$vals = array();
			$vals['ID'] = $session_number;
			$vals['SESSION_ID'] = $session_id;
			$vals['USERID'] = $remote_userid;
			$vals['URL'] = $url;
			$vals['REFERER'] = $url_from;
			$vals['TIPO'] = $url_tipo;
			$sql = "insert into sessions(id, session_id, userid, data, url, referer, tipo) values(:ID, :SESSION_ID, :USERID, sysdate , :URL, :REFERER, :TIPO)";
			$q_log->exec($sql, $vals);
			$log_conn->commit();
			
			if($force_log==true &&  !preg_match("/\.dev\./i",$_SERVER['HTTP_HOST']) && !preg_match("/\.test\./i",$_SERVER['HTTP_HOST']) ){
				$log_str = "<session $session_number><hr><b>Script : index.php</b><br><b>Parametri di input</b><ul>";
				foreach ( $in as $key => $val )
					$log_str .= "<li>$key: $val</li>";
				$log_str .= "</ul></session>";
				$handle = fopen ( $file_log, 'a+' );
				fwrite ( $handle, $log_str );
				fclose ( $handle );
			}
		}
	}
	
	public function HTMLActivity(){
		$remote_userid=$this->session_vars['remote_userid'];
		$last_access_conn=new dbconn();
		$q_last_activity=new query($last_access_conn);
		$sql = "SELECT * FROM (SELECT * FROM SESSIONS WHERE DATA < (SELECT DATA
			FROM (SELECT DATA FROM SESSIONS WHERE TIPO = 'L' AND USERID='".$remote_userid."'
			ORDER BY DATA DESC) WHERE ROWNUM = 1) AND (TIPO != 'L' OR TIPO IS NULL)
			AND USERID='".$remote_userid."' ORDER BY DATA DESC) WHERE ROWNUM = 1";

		$q_last_activity->set_sql($sql);
		$q_last_activity->exec();
		$q_last_activity->get_row();
		
		$sql = "SELECT DATA FROM (SELECT DATA, RANK() OVER (ORDER BY DATA DESC) SESSION_RANK
			FROM SESSIONS t WHERE TIPO='L' AND USERID='".$remote_userid."') WHERE SESSION_RANK = 2";

		$q_last_access=new query($last_access_conn);
		$q_last_access->set_sql($sql);
		$q_last_access->exec();
		$q_last_access->get_row();
		
		$blocco_ultimo_accesso ="<span>";
		
		if ($q_last_access->numrows > 0) {
			$blocco_ultimo_accesso .= "<i>".$this->testo("Bentornato").":</i> <b>".$remote_userid."</b>&nbsp;&nbsp;<i>".
				$this->testo("Ultimo accesso").":</i> <b>".$q_last_access->row['DATA']."</b>&nbsp;&nbsp;<br/>";
			if ($q_last_activity->row['TIPO'] == 'F') {
				$blocco_ultimo_accesso .=				
					"<span title=\"".$this->testo("Avviso form aperta")."\">".
					"<img width=\"15px\" src=\"images/warning_img_small.png\" style=\"vertical-align: -20%;\"/>&nbsp;".
					"<i>".$this->testo("Ultima attivita").
					":</i> <b>".$q_last_activity->row['DATA']."</b>&nbsp;".
					"<img width=\"15px\" src=\"images/warning_img_small.png\" style=\"vertical-align: -20%;\"/>"."</span>&nbsp;&nbsp;";
			} else {
				$blocco_ultimo_accesso .=				
					"<i>".$this->testo("Ultima attivita").":</i> <b>".$q_last_activity->row['DATA']."</b>&nbsp;&nbsp;";
			}
			$blocco_ultimo_accesso .=
				"<a href=\"".$q_last_activity->row['URL']."\"><u>".$this->testo("Vai")." &gt;&gt;</u></a>";
		} else {
			$blocco_ultimo_accesso .= "<i>".$this->testo("Benvenuto").":</i> <b>".$remote_userid."</b>";
		}
		
		$blocco_ultimo_accesso .="</span>";

		return $blocco_ultimo_accesso;
	}
	
	public function HTMLLastActivityOnly(){
		$remote_userid=$this->session_vars['remote_userid'];
		$last_access_conn=new dbconn();
		$q_last_activity=new query($last_access_conn);
		$sql = "SELECT * FROM (SELECT * FROM SESSIONS WHERE DATA < (SELECT DATA
			FROM (SELECT DATA FROM SESSIONS WHERE TIPO = 'L' AND USERID='".$remote_userid."'
			ORDER BY DATA DESC) WHERE ROWNUM = 1) AND (TIPO != 'L' OR TIPO IS NULL)
			AND USERID='".$remote_userid."' ORDER BY DATA DESC) WHERE ROWNUM = 1";

		$q_last_activity->set_sql($sql);
		$q_last_activity->exec();
		$q_last_activity->get_row();
		
		$sql = "SELECT DATA FROM (SELECT DATA, RANK() OVER (ORDER BY DATA DESC) SESSION_RANK
			FROM SESSIONS t WHERE TIPO='L' AND USERID='".$remote_userid."') WHERE SESSION_RANK = 2";

		$q_last_access=new query($last_access_conn);
		$q_last_access->set_sql($sql);
		$q_last_access->exec();
		$q_last_access->get_row();
		
		$blocco_ultimo_accesso ="<span>";
		
		if ($q_last_access->numrows > 0) {
			if ($q_last_activity->row['TIPO'] == 'F') {
				$blocco_ultimo_accesso .=				
					"<span title=\"".$this->testo("Avviso form aperta")."\">".
					"<img width=\"15px\" src=\"images/warning_img_small.png\" style=\"vertical-align: -20%;\"/>&nbsp;".
					"<i>".$this->testo("Ultima attivita").
					":</i> <b>".$q_last_activity->row['DATA']."</b>&nbsp;".
					"<img width=\"15px\" src=\"images/warning_img_small.png\" style=\"vertical-align: -20%;\"/>"."</span>&nbsp;&nbsp;";
			} else {
				$blocco_ultimo_accesso .=				
					"<i>".$this->testo("Ultima attivita").":</i> <b>".$q_last_activity->row['DATA']."</b>&nbsp;&nbsp;";
			}
			$blocco_ultimo_accesso .=
				"<a href=\"".$q_last_activity->row['URL']."\"><u>".$this->testo("Vai")." &gt;&gt;</u></a>";
		}
		
		$blocco_ultimo_accesso .="</span>";
	
		return $blocco_ultimo_accesso;
	}

	function testo($testo){
		//TODO: mettere $this->config_service ['Lista_schede'] nelle frasi in modo da configurarle dallo study.xml

		//HOW TO
		/** Per utilizzare questa funzione chiamarla cosi nel codice:
		 * $this->testo("PAROLACHIAVE")
		 * e qui dentro definire per ogni lingua
		 * $this->testi['PAROLACHIAVE']="Frase da far apparire";
		 */
		if(!isset($this->testi[$testo])){
			if($this->lang=='en'){
				$this->testi['Benvenuto']="Welcome";
				$this->testi['Bentornato']="Welcome";
				$this->testi['Ultimo accesso']="Last access";
				$this->testi['Ultima attivita']="Last activity (prev. session)";
				$this->testi['Vai']="GO";
				$this->testi['Avviso form aperta']="Last activity points to an open form. Check if all the data has been saved.";
			}
			else{ 
				$this->testi['Benvenuto']="Benvenuto";
				$this->testi['Bentornato']="Bentornato";
				$this->testi['Ultimo accesso']="Ultimo accesso";
				$this->testi['Ultima attivita']="Ultima attivit&#224; (sessione prec.)";
				$this->testi['Vai']="VAI";
				$this->testi['Avviso form aperta']="L'ultima attivit&#224; punta ad una form aperta. Controllare che i dati siano stati salvati.";
			}

		}
		return $this->testi[$testo];
	} 
	
	private function CheckFormClosed(){
		$form_closed=new dbconn();
		$q_form_closed=new query($form_closed);
		if($this->session_vars['PROGR']!=""){
			$and_progr=" AND PROGR={$this->session_vars['PROGR']}";
		}
		if($this->session_vars['VISITNUM_PROGR']!=""){
			$and_visitnum_progr=" AND VISITNUM_PROGR={$this->session_vars['VISITNUM_PROGR']}";
		}
		$pk = "CODPAT";
		if ($this->pk_service){
			$pk = $this->pk_service;
		}
		$sql = "SELECT FINE  FROM {$this->service}_COORDINATE WHERE {$pk}={$this->session_vars[$pk]} 
		AND VISITNUM = {$this->session_vars['VISITNUM']} AND ESAM = {$this->session_vars['ESAM']} 
		{$and_progr} {$and_visitnum_progr}";
		//var_dump($this->session_vars);
		//echo "$sql";
		$q_form_closed->set_sql($sql);
		$q_form_closed->exec();
		$q_form_closed->get_row();
		
		return $q_form_closed->row['FINE'] == 1;
	}
	
	public function getLastActivityType(){
		$remote_userid=$this->session_vars['remote_userid'];
		$last_access_conn=new dbconn();
		$q_last_activity=new query($last_access_conn);
		$sql = "SELECT * FROM (SELECT * FROM SESSIONS WHERE DATA < (SELECT DATA
			FROM (SELECT DATA FROM SESSIONS WHERE TIPO = 'L' AND USERID='".$remote_userid."'
			ORDER BY DATA DESC) WHERE ROWNUM = 1) AND (TIPO != 'L' OR TIPO IS NULL)
			AND USERID='".$remote_userid."' ORDER BY DATA DESC) WHERE ROWNUM = 1";

		$q_last_activity->set_sql($sql);
		$q_last_activity->exec();
		$q_last_activity->get_row();
		
		return $q_last_activity->row['TIPO'];
	}
}

?>