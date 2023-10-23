<?
include_once "db.inc";

/**
 * Classe ConcurrentAccess
 * Classe per la gestione degli accessi concorrenti
 * @package XMR Hyperlibs
 *
 */

class ConcurrentAccess {
	
	private $activity_time_mins = 60;
	
	/**
	 * Costruttore: allineamento e verifica della tabella di sessione in banca dati.
	 *
	 */
	function __construct($sessions_vars, $lang='en', $service, $pk_service) {
		$this->session_vars = $sessions_vars;
		$this->lang = $lang;
		$this->service = $service;
		$this->pk_service = $pk_service;
		
		$conn = new dbconn();
		$query = new query($conn);
		
		$sessions_cols = array ('ID' => 'NUMBER not null',
								'SESSION_ID' => 'CHAR(128 CHAR)',
								'USERID' => 'VARCHAR2(200 CHAR)',
								'DATA' => 'DATE',
								'URL' => 'VARCHAR2(4000 CHAR)',
								'REFERER' => 'VARCHAR2(4000 CHAR)',
								'TIPO' => 'VARCHAR2(20)' );
		$query_check_existence = "SELECT COUNT(TABLE_NAME) AS CONTO FROM USER_TABLES WHERE TABLE_NAME=UPPER('SESSIONS')";
		$query->set_sql ($query_check_existence);
		$query->exec();
		$query->get_row();
		if ($query->row['CONTO'] == 0) {
			$query_create = 'CREATE TABLE SESSIONS (ID NUMBER not null)';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
		}

		$query_check_existence = "SELECT COLUMN_NAME FROM USER_TAB_COLUMNS WHERE TABLE_NAME='SESSIONS'";
		$query->set_sql ($query_check_existence);
		$query->exec();
		while ($query->get_row ()) {
			$tb_vals[$query->row['COLUMN_NAME']] = $query->row['COLUMN_NAME'];
		}
		foreach ($sessions_cols as $key => $val) {
			if (!in_array($key, $tb_vals)) {
				$alter_sessions_table = "ALTER TABLE SESSIONS ADD $key $val";
				$query->set_sql ($alter_sessions_table);
				$query->exec();
			}
		}
		
	}
	
	/**
	 * Funzione per la generazione del messaggio di accesso concorrente
	 * 
	 */
	public function HTMLConcurrentAccess(){
		$remote_userid=$this->session_vars['remote_userid'];
		$session_id = substr($_SERVER['HTTP_SHIB_SESSION_ID'], 1, 32);
		$current_access_conn = new dbconn();
		$current_access_query = new query($current_access_conn);
// 		$sql = "SELECT COUNT(*) AS CURRENT_ACCESSES FROM SESSIONS WHERE SESSION_ID IN 
// 			(SELECT SESSION_ID FROM (SELECT SESSION_ID FROM SESSIONS WHERE TIPO='L' AND SESSION_ID IS NOT NULL) MINUS
// 			SELECT SESSION_ID FROM (SELECT SESSION_ID FROM SESSIONS WHERE TIPO='O' AND SESSION_ID IS NOT NULL))
// 			AND SUBSTR(USERID,0,3) LIKE '".substr($remote_userid, 0, 3)."%'
// 			AND USERID <> '".$remote_userid."'
// 			AND SESSION_ID <> '".$session_id."'
// 			AND DATA < sysdate+8/24";
		$sql = "SELECT COUNT(*) AS TOTAL_ACTIVITIES FROM (SELECT USERID, COUNT(*) AS ACTIVITIES FROM SESSIONS WHERE SESSION_ID IN
			(SELECT SESSION_ID FROM (SELECT SESSION_ID FROM SESSIONS WHERE TIPO='L' AND SESSION_ID IS NOT NULL) MINUS
			SELECT SESSION_ID FROM (SELECT SESSION_ID FROM SESSIONS WHERE TIPO='O' AND SESSION_ID IS NOT NULL))
			AND SUBSTR(USERID,0,3) LIKE '".substr($remote_userid, 0, 3)."%'
 			AND USERID <> '".$remote_userid."'
			AND SESSION_ID <> '".$session_id."'
			AND DATA > sysdate-".$this->activity_time_mins."/(24*60)
			GROUP BY USERID)";
		
		$current_access_query->exec($sql);
		$current_access_query->get_row();
		
		if ($current_access_query->row['TOTAL_ACTIVITIES'] > 0) {
			$blocco_attivita_recenti ="<span>".
				"<img width=\"15px\" src=\"images/warning_img_small.png\" style=\"vertical-align: -20%;\"/>&nbsp;".
				"<b>".$this->testo("Avviso")."</b>&nbsp;".
				"<img width=\"15px\" src=\"images/warning_img_small.png\" style=\"vertical-align: -20%;\"/>&nbsp;".
				"</span>";
		} else {
			$blocco_attivita_recenti = "";
		}

		return $blocco_attivita_recenti;
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
				$this->testi['Avviso']="Please pay attention that at least one user is logged into the eCRF";
			} else { 
				$this->testi['Avviso']="Attenzione c'&egrave; almeno un utente loggato nella eCRF";
			}
		}
		return $this->testi[$testo];
	} 
	
}

?>
