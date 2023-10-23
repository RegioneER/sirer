<?
include_once "db.inc";

/**
 * Classe DocumentGenerator
 * Classe per la gestione del log delle attività lato client
 * @package XMR Hyperlibs
 *
 */

class DocumentGenerator {
	protected $default_document_dir = "";
	protected $lang;
	protected $pk_service;
	protected $ws_base_url = "http://localhost:8084/PentahoActionCallerWS/WS?wsdl";
	//protected $ws_base_url = "http://siss01.private.cineca.it:8084/PentahoActionCallerWS/WS?wsdl";
	protected $siteid;
	protected $subjid;
	protected $center;
	protected $codpat;
	protected $visitnum;
	protected $esam;
	protected $progr;
	protected $file_name;
	
	public function __construct($center = null, $codpat = null, $visitnum = null, $esam = null, $progr = null)
	{
		global $in;
		$this->center = ($center == null ? $in['CENTER'] : $center);
		$this->codpat = ($codpat == null ? $in['CODPAT'] : $codpat);
		$this->visitnum = ($visitnum == null ? $in['VISITNUM'] : $visitnum);
		$this->esam = ($esam == null ? $in['ESAM'] : $esam);
		$this->progr = ($progr == null ? $in['PROGR'] : $progr);
		$this->set_vars();
	}
	
	private function set_vars()
	{
		global $service;
		global $in;
		$conn = new dbconn ( );
		if ($this->center != "") {
			// SiteID
			$sql_query = "select CODE from CMM_CENTER WHERE LTRIM (TO_CHAR (ID_CENTER, '000')) = '{$this->center}'";
			$sql = new query ( $conn );
			$sql->set_sql ( $sql_query );
			$sql->exec ();
			$sql->get_row ();
			$this->siteid = $sql->row ['CODE'];
		}
		if ($this->codpat != "") {
			//Subjid
			$sql_query = "select SUBJID from {$service}_REGISTRATION WHERE CODPAT='{$this->codpat}'";
			$sql = new query ( $conn );
			$sql->set_sql ( $sql_query );
			$sql->exec ();
			$sql->get_row ();
			$this->subjid = $sql->row['SUBJID'];
		}
		if ($this->default_document_dir == "") {
			$this->default_document_dir = "{$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents/{$this->siteid}/{$this->subjid}";
		}
		if ($this->file_name == "") {
			//Filename
			$sql_query = "select SITEID||'-'||SUBJID||'_SAEid'||PROGR||'_'||D_SAETYPE as FILE_NAME from {$service}_SAE t where center='{$this->center}' and codpat='{$this->codpat}' and visitnum='{$this->visitnum}' and esam='{$this->esam}'".($this->progr != "" ? " and progr='{$this->progr}'" : "");
			$sql = new query ( $conn );
			$sql->set_sql ( $sql_query );
			$sql->exec ();
			$sql->get_row ();
			$this->file_name = $sql->row['FILE_NAME'];
		}
	}
	
	/**
	 * Crea la directory per i documenti
	 *
	 */
	function make_document_dir()
	{
		if (! is_dir("{$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents")) {
			mkdir("{$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents");
		}
		if (! is_dir("{$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents/{$this->siteid}")) {
			mkdir("{$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents/{$this->siteid}");
		}
		if (! is_dir("{$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents/{$this->siteid}/{$this->subjid}")) {
			mkdir("{$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents/{$this->siteid}/{$this->subjid}");
		}
		system("chgrp -R devj {$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents/", $retval);
		system("chmod -R ug+w {$_SERVER['DOCUMENT_ROOT']}/uxmr/xml/documents/", $retval);
	}
	
	/**
	 * doDocGen_f_to_call
	 * Genera il documento PDF (per la f_to_call)
	 *
	 * @param string $document_dir
	 */
	
	function doDocGen_f_to_call($document_dir = "", $solution_name = "", $action_name = "", $path = "") {
		if ($document_dir == "") {
			$this->make_document_dir();
			$document_dir = $this->default_document_dir;
			Logger::send($this->default_document_dir);
		}
		try {
			// Solution name
			if ($solution_name == "" ) {
				$solution_name = "xmr_to_pdf";
			}
			// Action name
			if ($action_name == "" ) {
				$temp_action_name = $_SERVER['HTTP_HOST'];
				$temp_action_name = preg_replace("/https:\/\//", "", $temp_action_name);
				$temp_action_name = preg_replace("/http:\/\//", "", $temp_action_name);
				if (preg_match("/\.dev\./i",$temp_action_name)) {
					// Dev
					$temp_action_name = substr($temp_action_name, 0, strpos($temp_action_name, ".dev"));
				} elseif (preg_match("/\.test\./i",$temp_action_name)) {
					$temp_action_name = substr($temp_action_name, 0, strpos($temp_action_name, ".test"));
					// Test 
				} elseif (preg_match("/-preprod\./i",$temp_action_name)) {
					// PreProd
					$temp_action_name = substr($temp_action_name, 0, strpos($temp_action_name, "-preprod"));
					$temp_action_name = $temp_action_name."_qa";
				} else {
					// Prod
					$temp_action_name = substr($temp_action_name, 0, strpos($temp_action_name, "."));
				}
					
				$action_name = "xmr_to_pdf_".$temp_action_name.".xaction";
			}
			// Path
			if ($path == "" ) {
			}

			// Cancello il file per sicurezza
			unlink($document_dir."/".$this->file_name);
			$response = "";
			$i = 0;
			while (!file_exists($document_dir."/".$this->file_name) && $i < 5) {
				$options = array(
					'soap_version' => SOAP_1_2,
					'exceptions' => true,
					'trace' => 1,
					'cache_wsdl' => WSDL_CACHE_NONE
				); 
				$ws_client = new SoapClient($this->ws_base_url);
				
				$parameters = array(
					'solution' => $solution_name,
					'path' => $path,
					'actionName' => $action_name,
					'params' => "&progr_={$this->progr}&codpat_={$this->codpat}&reportname={$this->file_name}&directory={$document_dir}",
				);
//				echo print_r($parameters);
//				die();
				$response = $ws_client->ActionCall($parameters);
				$i++;
			}
			if (file_exists($document_dir."/".$this->file_name)) {
				system("chgrp -R devj {$document_dir}/{$this->file_name}", $retval);
				system("chmod -R ug+w {$document_dir}/{$this->file_name}", $retval);
			}
			
        } catch (Exception $e) {
			return false;
		}
		return $response;
	}
	
	/**
	 * doCreateLink
	 *
	 */
	function doCreateLink() {
		// setto le vars
		return "/uxmr/xml/documents/{$this->siteid}/{$this->subjid}/{$this->file_name}.pdf";
	}

}

?>