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

   public function __construct($user, $pass, $host){
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
