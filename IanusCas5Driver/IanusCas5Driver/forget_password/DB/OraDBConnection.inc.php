<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of OraDBConnectioninc
 *
 * @author ccontino
 */
class OraDBConnection {
   protected $resource;

   public $Error_Launched=false;

   public function __construct($user=null, $pass=null, $host=null){
   	if ($user==null)	{
   	$ammin_file=$_SERVER['DOCUMENT_ROOT'];
			$ammin_file=preg_replace("/html/i", "config/amministrazione.cfg", $ammin_file);
			$handle = fopen($ammin_file, "r");
			$contents = fread($handle, filesize($ammin_file));
			fclose($handle);
			$ammin_config_line=preg_split("/\n/", $contents);
			for ($i=0;$i<count($ammin_config_line);$i++) {
				if (preg_match("/OraUserid/i",$ammin_config_line[$i])) $Ora_Userid=preg_replace("/OraUserid (.*)/i", "\\1" , $ammin_config_line[$i]);
				if (preg_match("/OraPassword/i",$ammin_config_line[$i])) $Ora_Pass=preg_replace("/OraPassword (.*)/i", "\\1" , $ammin_config_line[$i]);
				if (preg_match("/OraInstance/i",$ammin_config_line[$i])) $Ora_Host=preg_replace("/OraInstance (.*)/i", "\\1" , $ammin_config_line[$i]);
			}
			$Ora_Userid=preg_replace("/\s/ ", "",$Ora_Userid);
			$Ora_Pass=preg_replace("/\s/", "",$Ora_Pass);
			$Ora_Host=preg_replace("/\s/", "",$Ora_Host);
			$user=$Ora_Userid;
			$pass=$Ora_Pass;
			$host=$Ora_Host;
   	}
       try {
           $this->resource=oci_connect($user, $pass, $host);
       } catch (Exception $e) {
           throw new Exception("Errore connessione DB", 1);
       }      
   }

   public function commit(){
       try {
           oci_commit($this->resource);
           return true;
       } catch (Exception $e) {
           throw new Exception("Errore Commit", 2);
       }
   }

   public function close(){
       oci_close($this->resource);
   }

   public function getConnection(){
       return $this->resource;
   }

   public function rollback(){
       try {
           oci_rollback($this->resource);
       } catch (Exception $e) {
           throw new Exception("Errore Rollback", 3);
       }
   }

   function __destruct() {
        if ($this->resource){
        try {
           oci_rollback($this->resource);
       } catch (Exception $e) {
           throw new Exception("Errore Rollback in chiusura", 4);
       }
        }
   }


}
?>
