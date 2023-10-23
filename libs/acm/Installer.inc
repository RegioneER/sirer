<?
 /**
  * Classe per l'installazione ACM
  *
  * @package Hyper
  */
 class Installer{

     /*
      * ESEGUIRE PRIMA IL FILE acm_installer.ddl.sql!!!
      * Modificare sui nuovi servizi il file di configurazione acm: dbconfig.php
      * Creare repository per il progetto su csv.private.cineca.it corente con la configurazione di dbconfig.php
      * Eseguire su IDP proprio del servizio: grant all on AUTHORITIES to [USER_DB];
      * Eseguire su IDP proprio del servizio: grant all on GRANTED_AUTHORITIES to [USER_DB];
      * Eseguire su db PENTAHO5: grant all on AUTHORITIES to [USER_DB];
      * Eseguire su db PENTAHO5: grant all on GRANTED_AUTHORITIES to [USER_DB];
      *
      *
      */

	 function Installer($service=null, $conn=null){
	 	$this->conn = $conn;
 		$this->service = $service;
	 }

     function checkTabExists($tabname){
         $retval = true;
         $tabname = strtoupper($tabname);
         $query = new query ( $this->conn );
         $query_check_existence = "select table_name from user_tables where table_name=upper('{$tabname}')";
         $query->set_sql ( $query_check_existence );
         $query->exec ();
         if(!$query->get_row()){
             $retval = false;
         }
         return $retval;
     }

     /**
      *
      * Controlla l'esistenza delle tabelle e viste necessarie all'ACM
      *
      */
     function checkCreateACMTables(){

         /**
          * CREAZIONE TABELLE
          * CRO Team 20141016
          * START
          */

         //{$this->service}_REGISTRATION
         $query = new query ( $this->conn );
         $query_check_existence = "select table_name from user_tables where table_name=upper('{$this->service}_REGISTRATION')";
         $query->set_sql ( $query_check_existence );
         $query->exec ();
         if($query->get_row ()==''){
             $query_create = "CREATE TABLE {$this->service}_REGISTRATION
										(
										  CODPAT          NUMBER,
										  USERID_INS      VARCHAR2(32 CHAR),
										  ESAM            NUMBER,
										  PROGR           NUMBER,
										  VISITNUM        NUMBER,
										  VISITNUM_PROGR  NUMBER,
										  CENTER          VARCHAR2(40 CHAR),
										  HD_SUBJID       NUMBER,
										  INITIALS        VARCHAR2(2 CHAR),
										  PATIENT_LANG    VARCHAR2(3 CHAR),
										  PASSWORD        VARCHAR2(8 CHAR),
										  SITEID          VARCHAR2(10 CHAR),
										  SUBJID          VARCHAR2(4 CHAR),
										  CONSTRAINT PK_{$this->service}_REGISTRATION
										 PRIMARY KEY
										 (CODPAT, ESAM, PROGR, VISITNUM, VISITNUM_PROGR),
										  CONSTRAINT FK_{$this->service}_REGISTRATION_COORD
										 FOREIGN KEY (VISITNUM, VISITNUM_PROGR, PROGR, ESAM, CODPAT)
										 REFERENCES {$this->service}_COORDINATE (VISITNUM,VISITNUM_PROGR,PROGR,ESAM,CODPAT)
										    ON DELETE CASCADE
										)
										LOGGING
										NOCOMPRESS
										NOCACHE
										NOPARALLEL
										MONITORING
					 	";
             $sql=new query($this->conn);
             $sql->set_sql ( $query_create );
             $sql->ins_upd ();
             $this->report .= "<hr>$query_create";
         }


     }



     //TODO: !!!
     //////////////////////////////////ELIMINARE SOTTO!!////////////////////////////////////////
     //TODO: !!!


 	
	/**
	 * Crea le tabelle per la gestione CMM
	 * 
	 * CMM_MANAGEMENT v2.0
	 * vmazzeo 20122203
	 * 
	 */
	function CreateCMMTable() {
		$query = new query ( $this->conn );
		// CMM_CENTER
		$sessions_table_exist = "select table_name from user_tables where table_name=upper('CMM_CENTER')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = '
				CREATE TABLE CMM_CENTER
				(
					"ID_CENTER"	NUMBER not null,
					"CODE"		VARCHAR2(20),
					"NAME"		VARCHAR2(255),
					"PI"		VARCHAR2(255),
					"ADDRESS"	VARCHAR2(255),
					"COUNTRY"	NUMBER,
					"D_COUNTRY"	VARCHAR2(255),
					"PHONE"		VARCHAR2(255),
					"FAX"		VARCHAR2(255),
					"GENURS"	VARCHAR2(255),
					"STATUS"	NUMBER,
					"D_STATUS"	VARCHAR2(20),
					
					CONSTRAINT "PK_CMM_CENTER" PRIMARY KEY ("ID_CENTER")
				
				)
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// S_CMM_CENTER
		$sessions_table_exist = "select table_name from user_tables where table_name=upper('S_CMM_CENTER')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = '
				CREATE TABLE S_CMM_CENTER
				(
					"USERID"	VARCHAR2(32 CHAR),
					"MODDT"		DATE,
					"MODPROG"	NUMBER(6) not null,
					"FL_QUERY"	CHAR(1) not null,
					"ID_QUERY"	NUMBER(6),
					"ID_CENTER"	NUMBER not null,
					"CODE"		VARCHAR2(20),
					"NAME"		VARCHAR2(255),
					"PI"		VARCHAR2(255),
					"ADDRESS"	VARCHAR2(255),
					"COUNTRY"	NUMBER,
					"D_COUNTRY"	VARCHAR2(255),
					"PHONE"		VARCHAR2(255),
					"FAX"		VARCHAR2(255),
					"GENURS"	VARCHAR2(255),
					"STATUS"	NUMBER,
					"D_STATUS"	VARCHAR2(20),
					
					CONSTRAINT "PK_S_CMM_CENTER" PRIMARY KEY ("MODPROG")
				)
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// CMM_USERS
		$sessions_table_exist = "select table_name from user_tables where table_name=upper('CMM_USERS')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = '
				CREATE TABLE CMM_USERS
				(
					"CMM_USERID"	VARCHAR2(32 CHAR),
					"ROLE"			NUMBER,
					"D_ROLE"		VARCHAR2(50),
					"CODE"			VARCHAR2(20),
					"NAME"			VARCHAR2(255),
					"SURNAME"		VARCHAR2(255),
					"EMAIL"			VARCHAR2(255),
					"PHONE"			VARCHAR2(255),
					"FAX"			VARCHAR2(255),
					"ADDRESS"		VARCHAR2(255),
					"CREATEDT"		DATE,
					"FSTACCDT"		DATE,
					"LSTACCDT"		DATE,
					"EXPDT"			DATE,
					"ENDDT"			DATE,
					"STATUS"		NUMBER,
					"D_STATUS"		VARCHAR2(20),
					"SIGN"			NUMBER,
					"D_SIGN"		VARCHAR2(20),
					"SIGNSAE"		NUMBER,
					"D_SIGNSAE"		VARCHAR2(20),
					"GENURS"		VARCHAR2(255),
					"FIRST_PASSWORD" VARCHAR2(32),
					"MAIL_SENT"      CHAR(1),
					
					CONSTRAINT "PK_CMM_USERS" PRIMARY KEY ("CMM_USERID")
				)
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// S_CMM_USERS
		$sessions_table_exist = "select table_name from user_tables where table_name=upper('S_CMM_USERS')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = '
				CREATE TABLE S_CMM_USERS
				(
					"USERID"		VARCHAR2(32 CHAR),
					"MODDT"			DATE,
					"MODPROG"		NUMBER(6) not null,
					"FL_QUERY"		CHAR(1) not null,
					"ID_QUERY"		NUMBER(6),
					"CMM_USERID"	VARCHAR2(32 CHAR),
					"ROLE"			NUMBER,
					"D_ROLE"		VARCHAR2(50),
					"CODE"			VARCHAR2(20),
					"NAME"			VARCHAR2(255),
					"SURNAME"		VARCHAR2(255),
					"EMAIL"			VARCHAR2(255),
					"PHONE"			VARCHAR2(255),
					"FAX"			VARCHAR2(255),
					"ADDRESS"		VARCHAR2(255),
					"CREATEDT"		DATE,
					"FSTACCDT"		DATE,
					"LSTACCDT"		DATE,
					"EXPDT"			DATE,
					"ENDDT"			DATE,
					"STATUS"		NUMBER,
					"D_STATUS"		VARCHAR2(20),
					"SIGN"			NUMBER,
					"D_SIGN"		VARCHAR2(20),
					"SIGNSAE"		NUMBER,
					"D_SIGNSAE"		VARCHAR2(20),
					"GENURS"		VARCHAR2(255),
					"FIRST_PASSWORD" VARCHAR2(32),
					"MAIL_SENT"      CHAR(1),
									
					CONSTRAINT "PK_S_CMM_USERS" PRIMARY KEY ("MODPROG")
				)
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}

		// CMM_LANGUAGE
		$sessions_table_exist = "select table_name from user_tables where table_name=upper('CMM_LANGUAGE')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = '
				CREATE TABLE CMM_LANGUAGE
				(
					"CENTER" VARCHAR2(20) NOT NULL,
					"LANGUAGE" VARCHAR2(12) NOT NULL,
					"D_LANGUAGE" VARCHAR2(200),
									
					CONSTRAINT "PK_CMM_LANGUAGE" PRIMARY KEY ("CENTER", "LANGUAGE")
				)
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// SERVICE_LANGUAGE
		$sessions_table_exist = "select table_name from user_tables where table_name=upper('".$this->service."_LANGUAGES')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = '
				CREATE TABLE '.$this->service.'_LANGUAGES
				(
					"LANGUAGE"		VARCHAR2(3) NOT NULL,
					"D_LANGUAGE"	VARCHAR2(200) NOT NULL,
													
					CONSTRAINT PK_'.$this->service.'_LANGUAGES PRIMARY KEY ("LANGUAGE")
				)
			';
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
			
			$pk='';
			$vals_languages="";
			$vals_languages['LANGUAGE']="ITA";
			$vals_languages['D_LANGUAGE']="Italian";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="ENG";
			$vals_languages['D_LANGUAGE']="English";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="DEU";
			$vals_languages['D_LANGUAGE']="German";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="ESP";
			$vals_languages['D_LANGUAGE']="Spanish";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="ROM";
			$vals_languages['D_LANGUAGE']="Romanian";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="HUR";
			$vals_languages['D_LANGUAGE']="Hungarian";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="POR";
			$vals_languages['D_LANGUAGE']="Portuguese";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="RUS";
			$vals_languages['D_LANGUAGE']="Russian";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
				
			$vals_languages['LANGUAGE']="FRA";
			$vals_languages['D_LANGUAGE']="French";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
			
			$vals_languages['LANGUAGE']="TUR";
			$vals_languages['D_LANGUAGE']="Turkish";
			$query->insert($vals_languages,$this->service."_LANGUAGES",$pk);
		}
			

		// 	ISO_COUNTRY_LIST
			$sessions_table_exist = "select table_name from user_tables where table_name=upper('".$this->service."_ISO_COUNTRY_LIST')";
			$query->set_sql ( $sessions_table_exist );
			$query->exec ();
			if($query->get_row ()){
				$return =  true;
			}
			else
			{
				$query_create = '
							CREATE TABLE '.$this->service.'_ISO_COUNTRY_LIST
							(
								"ISO"     NUMBER not null,
  								"COUNTRY" VARCHAR2(250) not null,
								"TIMEZONE" VARCHAR2(250),												
								CONSTRAINT PK_'.$this->service.'_ISO_COUNTRY_LIST PRIMARY KEY ("ISO")
							)
						';
				$sql = new query ( $this->conn );
				$sql->set_sql ( $query_create );
				$sql->exec ();
				$this->report .= "<hr>$query_create";
				
				$pk="";
				$vals_countries="";
				$vals_countries["ISO"]="4";$vals_countries["COUNTRY"]="Afghanistan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="248";$vals_countries["COUNTRY"]="Aland Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="8";$vals_countries["COUNTRY"]="Albania";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="12";$vals_countries["COUNTRY"]="Algeria";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="16";$vals_countries["COUNTRY"]="American Samoa";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="20";$vals_countries["COUNTRY"]="Andorra";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="24";$vals_countries["COUNTRY"]="Angola";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="660";$vals_countries["COUNTRY"]="Anguilla";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="10";$vals_countries["COUNTRY"]="Antarctica";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="28";$vals_countries["COUNTRY"]="Antigua and Barbuda";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="32";$vals_countries["COUNTRY"]="Argentina";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="51";$vals_countries["COUNTRY"]="Armenia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="533";$vals_countries["COUNTRY"]="Aruba";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="36";$vals_countries["COUNTRY"]="Australia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="40";$vals_countries["COUNTRY"]="Austria";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="31";$vals_countries["COUNTRY"]="Azerbaijan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="44";$vals_countries["COUNTRY"]="Bahamas";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="48";$vals_countries["COUNTRY"]="Bahrain";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="50";$vals_countries["COUNTRY"]="Bangladesh";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="52";$vals_countries["COUNTRY"]="Barbados";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="112";$vals_countries["COUNTRY"]="Belarus";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="56";$vals_countries["COUNTRY"]="Belgium";$vals_countries["TIMEZONE"]="Europe/Brussels";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="84";$vals_countries["COUNTRY"]="Belize";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="204";$vals_countries["COUNTRY"]="Benin";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="60";$vals_countries["COUNTRY"]="Bermuda";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="64";$vals_countries["COUNTRY"]="Bhutan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="68";$vals_countries["COUNTRY"]="Bolivia, Plurinational State of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="70";$vals_countries["COUNTRY"]="Bosnia and Herzegovina";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="72";$vals_countries["COUNTRY"]="Botswana";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="74";$vals_countries["COUNTRY"]="Bouvet Island";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="76";$vals_countries["COUNTRY"]="Brazil";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="86";$vals_countries["COUNTRY"]="British Indian Ocean Territory";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="96";$vals_countries["COUNTRY"]="Brunei Darussalam";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="100";$vals_countries["COUNTRY"]="Bulgaria";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="854";$vals_countries["COUNTRY"]="Burkina Faso";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="108";$vals_countries["COUNTRY"]="Burundi";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="116";$vals_countries["COUNTRY"]="Cambodia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="120";$vals_countries["COUNTRY"]="Cameroon";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="124";$vals_countries["COUNTRY"]="Canada";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="132";$vals_countries["COUNTRY"]="Cape Verde";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="136";$vals_countries["COUNTRY"]="Cayman Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="140";$vals_countries["COUNTRY"]="Central African Republic";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="148";$vals_countries["COUNTRY"]="Chad";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="152";$vals_countries["COUNTRY"]="Chile";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="156";$vals_countries["COUNTRY"]="China";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="162";$vals_countries["COUNTRY"]="Christmas Island";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="166";$vals_countries["COUNTRY"]="Cocos (Keeling) Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="170";$vals_countries["COUNTRY"]="Colombia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="174";$vals_countries["COUNTRY"]="Comoros";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="178";$vals_countries["COUNTRY"]="Congo";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="180";$vals_countries["COUNTRY"]="Congo, the Democratic Republic of the";$vals_countries["TIMEZONE"]="";;
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="184";$vals_countries["COUNTRY"]="Cook Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="188";$vals_countries["COUNTRY"]="Costa Rica";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="191";$vals_countries["COUNTRY"]="Croatia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="192";$vals_countries["COUNTRY"]="Cuba";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="196";$vals_countries["COUNTRY"]="Cyprus";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="203";$vals_countries["COUNTRY"]="Czech Republic";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="208";$vals_countries["COUNTRY"]="Denmark";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="262";$vals_countries["COUNTRY"]="Djibouti";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="212";$vals_countries["COUNTRY"]="Dominica";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="214";$vals_countries["COUNTRY"]="Dominican Republic";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="218";$vals_countries["COUNTRY"]="Ecuador";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="818";$vals_countries["COUNTRY"]="Egypt";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="222";$vals_countries["COUNTRY"]="El Salvador";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="226";$vals_countries["COUNTRY"]="Equatorial Guinea";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="232";$vals_countries["COUNTRY"]="Eritrea";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="233";$vals_countries["COUNTRY"]="Estonia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="231";$vals_countries["COUNTRY"]="Ethiopia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="238";$vals_countries["COUNTRY"]="Falkland Islands (Malvinas)";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="234";$vals_countries["COUNTRY"]="Faroe Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="242";$vals_countries["COUNTRY"]="Fiji";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="246";$vals_countries["COUNTRY"]="Finland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="250";$vals_countries["COUNTRY"]="France";$vals_countries["TIMEZONE"]="Europe/Paris";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="254";$vals_countries["COUNTRY"]="French Guiana";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="258";$vals_countries["COUNTRY"]="French Polynesia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="260";$vals_countries["COUNTRY"]="French Southern Territories";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="266";$vals_countries["COUNTRY"]="Gabon";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="270";$vals_countries["COUNTRY"]="Gambia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="268";$vals_countries["COUNTRY"]="Georgia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="276";$vals_countries["COUNTRY"]="Germany";$vals_countries["TIMEZONE"]="Europe/Berlin";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="288";$vals_countries["COUNTRY"]="Ghana";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="292";$vals_countries["COUNTRY"]="Gibraltar";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="300";$vals_countries["COUNTRY"]="Greece";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="304";$vals_countries["COUNTRY"]="Greenland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="308";$vals_countries["COUNTRY"]="Grenada";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="312";$vals_countries["COUNTRY"]="Guadeloupe";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="316";$vals_countries["COUNTRY"]="Guam";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="320";$vals_countries["COUNTRY"]="Guatemala";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="831";$vals_countries["COUNTRY"]="Guernsey";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="324";$vals_countries["COUNTRY"]="Guinea";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="624";$vals_countries["COUNTRY"]="Guinea-Bissau";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="328";$vals_countries["COUNTRY"]="Guyana";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="332";$vals_countries["COUNTRY"]="Haiti";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="334";$vals_countries["COUNTRY"]="Heard Island and McDonald Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="340";$vals_countries["COUNTRY"]="Honduras";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="344";$vals_countries["COUNTRY"]="Hong Kong";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="348";$vals_countries["COUNTRY"]="Hungary";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="352";$vals_countries["COUNTRY"]="Iceland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="356";$vals_countries["COUNTRY"]="India";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="360";$vals_countries["COUNTRY"]="Indonesia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="364";$vals_countries["COUNTRY"]="Iran, Islamic Republic of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="368";$vals_countries["COUNTRY"]="Iraq";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="372";$vals_countries["COUNTRY"]="Ireland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="833";$vals_countries["COUNTRY"]="Isle of Man";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="376";$vals_countries["COUNTRY"]="Israel";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="380";$vals_countries["COUNTRY"]="Italy";$vals_countries["TIMEZONE"]="Europe/Rome";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="388";$vals_countries["COUNTRY"]="Jamaica";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="392";$vals_countries["COUNTRY"]="Japan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="832";$vals_countries["COUNTRY"]="Jersey";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="400";$vals_countries["COUNTRY"]="Jordan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="398";$vals_countries["COUNTRY"]="Kazakhstan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="404";$vals_countries["COUNTRY"]="Kenya";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="296";$vals_countries["COUNTRY"]="Kiribati";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="410";$vals_countries["COUNTRY"]="Korea, Republic of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="414";$vals_countries["COUNTRY"]="Kuwait";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="417";$vals_countries["COUNTRY"]="Kyrgyzstan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="428";$vals_countries["COUNTRY"]="Latvia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="422";$vals_countries["COUNTRY"]="Lebanon";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="426";$vals_countries["COUNTRY"]="Lesotho";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="430";$vals_countries["COUNTRY"]="Liberia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="434";$vals_countries["COUNTRY"]="Libyan Arab Jamahiriya";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="438";$vals_countries["COUNTRY"]="Liechtenstein";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="440";$vals_countries["COUNTRY"]="Lithuania";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="442";$vals_countries["COUNTRY"]="Luxembourg";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="446";$vals_countries["COUNTRY"]="Macao";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="807";$vals_countries["COUNTRY"]="Macedonia, the former Yugoslav Republic of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="450";$vals_countries["COUNTRY"]="Madagascar";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="454";$vals_countries["COUNTRY"]="Malawi";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="458";$vals_countries["COUNTRY"]="Malaysia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="462";$vals_countries["COUNTRY"]="Maldives";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="466";$vals_countries["COUNTRY"]="Mali";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="470";$vals_countries["COUNTRY"]="Malta";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="584";$vals_countries["COUNTRY"]="Marshall Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="474";$vals_countries["COUNTRY"]="Martinique";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="478";$vals_countries["COUNTRY"]="Mauritania";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="480";$vals_countries["COUNTRY"]="Mauritius";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="175";$vals_countries["COUNTRY"]="Mayotte";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="484";$vals_countries["COUNTRY"]="Mexico";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="583";$vals_countries["COUNTRY"]="Micronesia, Federated States of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="498";$vals_countries["COUNTRY"]="Moldova, Republic of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="492";$vals_countries["COUNTRY"]="Monaco";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="496";$vals_countries["COUNTRY"]="Mongolia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="499";$vals_countries["COUNTRY"]="Montenegro";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="500";$vals_countries["COUNTRY"]="Montserrat";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="504";$vals_countries["COUNTRY"]="Morocco";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="508";$vals_countries["COUNTRY"]="Mozambique";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="104";$vals_countries["COUNTRY"]="Myanmar";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="516";$vals_countries["COUNTRY"]="Namibia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="520";$vals_countries["COUNTRY"]="Nauru";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="524";$vals_countries["COUNTRY"]="Nepal";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="528";$vals_countries["COUNTRY"]="Netherlands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="530";$vals_countries["COUNTRY"]="Netherlands Antilles";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="540";$vals_countries["COUNTRY"]="New Caledonia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="554";$vals_countries["COUNTRY"]="New Zealand";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="558";$vals_countries["COUNTRY"]="Nicaragua";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="562";$vals_countries["COUNTRY"]="Niger";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="566";$vals_countries["COUNTRY"]="Nigeria";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="570";$vals_countries["COUNTRY"]="Niue";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="574";$vals_countries["COUNTRY"]="Norfolk Island";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="580";$vals_countries["COUNTRY"]="Northern Mariana Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="578";$vals_countries["COUNTRY"]="Norway";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="512";$vals_countries["COUNTRY"]="Oman";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="586";$vals_countries["COUNTRY"]="Pakistan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="585";$vals_countries["COUNTRY"]="Palau";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="275";$vals_countries["COUNTRY"]="Palestinian Territory";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="591";$vals_countries["COUNTRY"]="Panama";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="598";$vals_countries["COUNTRY"]="Papua New Guinea";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="600";$vals_countries["COUNTRY"]="Paraguay";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="604";$vals_countries["COUNTRY"]="Peru";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="608";$vals_countries["COUNTRY"]="Philippines";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="612";$vals_countries["COUNTRY"]="Pitcairn";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="616";$vals_countries["COUNTRY"]="Poland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="620";$vals_countries["COUNTRY"]="Portugal";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="630";$vals_countries["COUNTRY"]="Puerto Rico";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="634";$vals_countries["COUNTRY"]="Qatar";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="638";$vals_countries["COUNTRY"]="Reunion";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="642";$vals_countries["COUNTRY"]="Romania";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="643";$vals_countries["COUNTRY"]="Russian Federation";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="646";$vals_countries["COUNTRY"]="Rwanda";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="652";$vals_countries["COUNTRY"]="Saint Barth";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="654";$vals_countries["COUNTRY"]="Saint Helena, Ascension and Tristan da Cunha";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="659";$vals_countries["COUNTRY"]="Saint Kitts and Nevis";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="662";$vals_countries["COUNTRY"]="Saint Lucia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="663";$vals_countries["COUNTRY"]="Saint Martin (French part)";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="666";$vals_countries["COUNTRY"]="Saint Pierre and Miquelon";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="670";$vals_countries["COUNTRY"]="Saint Vincent and the Grenadines";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="882";$vals_countries["COUNTRY"]="Samoa";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="674";$vals_countries["COUNTRY"]="San Marino";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="678";$vals_countries["COUNTRY"]="Sao Tome and Principe";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="682";$vals_countries["COUNTRY"]="Saudi Arabia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="686";$vals_countries["COUNTRY"]="Senegal";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="688";$vals_countries["COUNTRY"]="Serbia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="690";$vals_countries["COUNTRY"]="Seychelles";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="694";$vals_countries["COUNTRY"]="Sierra Leone";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="702";$vals_countries["COUNTRY"]="Singapore";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="703";$vals_countries["COUNTRY"]="Slovakia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="705";$vals_countries["COUNTRY"]="Slovenia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="90";$vals_countries["COUNTRY"]="Solomon Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="706";$vals_countries["COUNTRY"]="Somalia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="710";$vals_countries["COUNTRY"]="South Africa";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="239";$vals_countries["COUNTRY"]="South Georgia and the South Sandwich Islands";$vals_countries["TIMEZONE"]="";;
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="724";$vals_countries["COUNTRY"]="Spain";$vals_countries["TIMEZONE"]="Europe/Madrid";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="144";$vals_countries["COUNTRY"]="Sri Lanka";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="736";$vals_countries["COUNTRY"]="Sudan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="740";$vals_countries["COUNTRY"]="Suriname";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="744";$vals_countries["COUNTRY"]="Svalbard and Jan Mayen";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="748";$vals_countries["COUNTRY"]="Swaziland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="752";$vals_countries["COUNTRY"]="Sweden";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="756";$vals_countries["COUNTRY"]="Switzerland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="760";$vals_countries["COUNTRY"]="Syrian Arab Republic";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="158";$vals_countries["COUNTRY"]="Taiwan, Province of China";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="762";$vals_countries["COUNTRY"]="Tajikistan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="834";$vals_countries["COUNTRY"]="Tanzania, United Republic of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="764";$vals_countries["COUNTRY"]="Thailand";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="626";$vals_countries["COUNTRY"]="Timor-Leste";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="768";$vals_countries["COUNTRY"]="Togo";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="772";$vals_countries["COUNTRY"]="Tokelau";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="776";$vals_countries["COUNTRY"]="Tonga";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="780";$vals_countries["COUNTRY"]="Trinidad and Tobago";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="788";$vals_countries["COUNTRY"]="Tunisia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="792";$vals_countries["COUNTRY"]="Turkey";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="795";$vals_countries["COUNTRY"]="Turkmenistan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="796";$vals_countries["COUNTRY"]="Turks and Caicos Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="798";$vals_countries["COUNTRY"]="Tuvalu";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="800";$vals_countries["COUNTRY"]="Uganda";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="804";$vals_countries["COUNTRY"]="Ukraine";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="784";$vals_countries["COUNTRY"]="United Arab Emirates";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="826";$vals_countries["COUNTRY"]="United Kingdom";$vals_countries["TIMEZONE"]="Europe/London";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="840";$vals_countries["COUNTRY"]="United States";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="581";$vals_countries["COUNTRY"]="United States Minor Outlying Islands";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="858";$vals_countries["COUNTRY"]="Uruguay";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="860";$vals_countries["COUNTRY"]="Uzbekistan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="548";$vals_countries["COUNTRY"]="Vanuatu";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="336";$vals_countries["COUNTRY"]="Vatican City State";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="862";$vals_countries["COUNTRY"]="Venezuela, Bolivarian Republic of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="704";$vals_countries["COUNTRY"]="Viet Nam";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="92";$vals_countries["COUNTRY"]="Virgin Islands, British";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="384";$vals_countries["COUNTRY"]="Cote d'Ivoire";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="408";$vals_countries["COUNTRY"]="Korea, Democratic People's Republic of";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
					
				$vals_countries["ISO"]="418";$vals_countries["COUNTRY"]="Lao People's Democratic Republic";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1001";$vals_countries["COUNTRY"]="United States - Alabama";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1002";$vals_countries["COUNTRY"]="United States - Alaska";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1003";$vals_countries["COUNTRY"]="United States - Arizona";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1004";$vals_countries["COUNTRY"]="United States - Arkansas";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1005";$vals_countries["COUNTRY"]="United States - California";$vals_countries["TIMEZONE"]="America/Los_Angeles";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1006";$vals_countries["COUNTRY"]="United States - Colorado";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1007";$vals_countries["COUNTRY"]="United States - Connecticut";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1008";$vals_countries["COUNTRY"]="United States - Delaware";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1009";$vals_countries["COUNTRY"]="United States - District of Columbia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1010";$vals_countries["COUNTRY"]="United States - Florida";$vals_countries["TIMEZONE"]="America/New_York";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1011";$vals_countries["COUNTRY"]="United States - Georgia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1012";$vals_countries["COUNTRY"]="United States - Hawaii";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1013";$vals_countries["COUNTRY"]="United States - Idaho";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1014";$vals_countries["COUNTRY"]="United States - Illinois";$vals_countries["TIMEZONE"]="America/Chicago";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1015";$vals_countries["COUNTRY"]="United States - Indiana";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1016";$vals_countries["COUNTRY"]="United States - Iowa";$vals_countries["TIMEZONE"]="America/Chicago";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1017";$vals_countries["COUNTRY"]="United States - Kansas";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1018";$vals_countries["COUNTRY"]="United States - Kentucky";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1019";$vals_countries["COUNTRY"]="United States - Louisiana";$vals_countries["TIMEZONE"]="America/Chicago";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1020";$vals_countries["COUNTRY"]="United States - Maine";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1021";$vals_countries["COUNTRY"]="United States - Maryland";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1022";$vals_countries["COUNTRY"]="United States - Massachusetts";$vals_countries["TIMEZONE"]="America/New_York";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1023";$vals_countries["COUNTRY"]="United States - Michigan";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1024";$vals_countries["COUNTRY"]="United States - Minnesota";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1025";$vals_countries["COUNTRY"]="United States - Mississippi";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1026";$vals_countries["COUNTRY"]="United States - Missouri";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1027";$vals_countries["COUNTRY"]="United States - Montana";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1028";$vals_countries["COUNTRY"]="United States - Nebraska";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1029";$vals_countries["COUNTRY"]="United States - Nevada";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1030";$vals_countries["COUNTRY"]="United States - New Hampshire";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1031";$vals_countries["COUNTRY"]="United States - New Jersey";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1032";$vals_countries["COUNTRY"]="United States - New Mexico";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1033";$vals_countries["COUNTRY"]="United States - New York";$vals_countries["TIMEZONE"]="America/New_York";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1034";$vals_countries["COUNTRY"]="United States - North Carolina";$vals_countries["TIMEZONE"]="America/New_York";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1035";$vals_countries["COUNTRY"]="United States - North Dakota";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1036";$vals_countries["COUNTRY"]="United States - Ohio";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1037";$vals_countries["COUNTRY"]="United States - Oklahoma";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1038";$vals_countries["COUNTRY"]="United States - Oregon";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1039";$vals_countries["COUNTRY"]="United States - Pennsylvania";$vals_countries["TIMEZONE"]="America/New_York";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1040";$vals_countries["COUNTRY"]="United States - Rhode Island";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1041";$vals_countries["COUNTRY"]="United States - South Carolina";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1042";$vals_countries["COUNTRY"]="United States - South Dakota";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1043";$vals_countries["COUNTRY"]="United States - Tennessee";$vals_countries["TIMEZONE"]="America/Chicago";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1044";$vals_countries["COUNTRY"]="United States - Texas";$vals_countries["TIMEZONE"]="America/Chicago";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1045";$vals_countries["COUNTRY"]="United States - Utah";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1046";$vals_countries["COUNTRY"]="United States - Vermont";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1047";$vals_countries["COUNTRY"]="United States - Virginia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1048";$vals_countries["COUNTRY"]="United States - Washington";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1049";$vals_countries["COUNTRY"]="United States - West Virginia";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1050";$vals_countries["COUNTRY"]="United States - Wisconsin";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
				$vals_countries["ISO"]="1051";$vals_countries["COUNTRY"]="United States - Wyoming";$vals_countries["TIMEZONE"]="";
				$query->insert($vals_countries,$this->service."_ISO_COUNTRY_LIST",$pk);
				
			}	
			
			
			
			
		// FIRMA_UTENTI_CENTRI
		/*$sessions_table_exist = "select VIEW_NAME from ALL_VIEWS where VIEW_NAME=upper('{$this->service}_FIRMA_UTENTI_CENTRI')";
		$query->set_sql ( $sessions_table_exist );
		$query->exec ();
		if($query->get_row ()){
			$return =  true;
		}
		else
		{
			$query_create = "
				CREATE OR REPLACE FORCE VIEW {$this->service}_FIRMA_UTENTI_CENTRI
				(
				   USERNAME,
				   CENTER,
				   USER_ROLE
				)
				AS
				   SELECT uss.userid AS username, uss.site_id AS center, sp.code AS user_role
				     FROM users_sites_studies uss, studies_profiles sp
				    WHERE USS.STUDY_PREFIX = SP.STUDY_PREFIX AND sp.STUDY_PREFIX = '{$this->service}'";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}*/
		
		// DB_LOCK
		$query_check_existenceDBLOCK = "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='{$this->service}_DBLOCK'";
		$query->set_sql ( $query_check_existenceDBLOCK );
		$query->exec ();
		if($query->get_row ()){
			$return = true;
		}
		else
		{
			$query_create = "
			create table {$this->service}_DBLOCK
			(
			CENTER NUMBER DEFAULT -1 NOT NULL ENABLE, 
			CODPAT NUMBER DEFAULT -1 NOT NULL ENABLE, 
			VISITNUM NUMBER DEFAULT -1 NOT NULL ENABLE, 
			ESAM NUMBER DEFAULT -1 NOT NULL ENABLE, 
			DBLOCK NUMBER, 
			D_DBLOCK VARCHAR2(25 CHAR),
			CONSTRAINT PK_{$study_prefix}_DBLOCK PRIMARY KEY (CENTER,CODPAT,VISITNUM,ESAM)
			)";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}
		
		// S_DB_LOCK
		$query_check_existenceS_DBLOCK = "SELECT TABLE_NAME FROM USER_TABLES WHERE TABLE_NAME='S_{$this->service}_DBLOCK'";
		$query->set_sql ( $query_check_existenceS_DBLOCK );
		$query->exec ();
		if($query->get_row ()){
			$return = true;
		}
		else
		{
			$query_create = "
			create table S_{$this->service}_DBLOCK
			(
			ID_STORICO NUMBER(12,0),
    		MODDATE DATE,
    		MODUSER VARCHAR2(200 CHAR),
			CENTER NUMBER DEFAULT -1 NOT NULL ENABLE, 
			CODPAT NUMBER DEFAULT -1 NOT NULL ENABLE, 
			VISITNUM NUMBER DEFAULT -1 NOT NULL ENABLE, 
			ESAM NUMBER DEFAULT -1 NOT NULL ENABLE, 
			DBLOCK NUMBER, 
			D_DBLOCK VARCHAR2(25 CHAR),
			CONSTRAINT PK_S_{$study_prefix}_DBLOCK PRIMARY KEY (ID_STORICO)
			)";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $query_create );
			$sql->exec ();
			$this->report .= "<hr>$query_create";
		}

        echo $this->report;

		return $return;
	}

	function PrintReport() {
		die($this->report);
	}
 }


/*
 * DA INSERIRE!
 *
 *  Formatted on 07/09/2015 14:00:29 (QP5 v5.215.12089.38647)
CREATE OR REPLACE FORCE VIEW ACM_USERS_GP
(
	ID_PROFILO,
	DESCRIZIONE,
	STUDY_PREFIX,
	STUDIO_DESCR,
	STATUS,
	USERID
)
AS
   SELECT sp.id id_profilo,
          au.descrizione DESCRIZIONE,
          sp.STUDY_PREFIX,
          s.descr AS studio_descr,
          sp.ACTIVE STATUS,
          UP.userid
     FROM users_profiles UP,
          studies_profiles sp,
          ana_gruppiu au,
          studies s
    WHERE     UP.profile_id = sp.id
AND sp.id = au.id_gruppou
AND sp.scope = 0
AND s.prefix = sp.study_prefix;


 * Formatted on 07/09/2015 14:01:57 (QP5 v5.215.12089.38647)
CREATE OR REPLACE FORCE VIEW ACM_USERS_LP
(
	USERID,
	USER_SITE_STUDY_STATUS,
	SITE_CODE,
	SITE_DESCR,
	SITE_STATUS,
	SITE_STUDY_STATUS,
	STUDY_PREFIX,
	STUDIO_DESCR,
	ID_PROFILO,
	DESCRIZIONE,
	UTENTE_PROFILO_STATUS
)
AS
   SELECT uss.userid,
          uss.active USER_SITE_STUDY_STATUS,
          s.code SITE_CODE,
          s.descr SITE_DESCR,
          s.active SITE_STATUS,
          ss.active SITE_STUDY_STATUS,
          ss.study_prefix,
          st.descr AS studio_descr,
          sp.id ID_PROFILO,
          au.descrizione DESCRIZIONE,
          UP.active UTENTE_PROFILO_STATUS
     FROM users_sites_studies uss,
          users_sites us,
          sites s,
          sites_studies ss,
          users_profiles UP,
          studies_profiles sp,
          ana_gruppiu au,
          studies st
    WHERE     ss.site_id = s.id
AND uss.site_id = s.id
AND us.userid = uss.userid
AND us.site_id = s.id
AND UP.userid = uss.userid
AND UP.profile_id = uss.user_profile_id
AND st.prefix = ss.study_prefix
AND sp.id = UP.profile_id
AND sp.id = au.id_gruppou;

 */