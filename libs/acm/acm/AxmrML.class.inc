<?php 


class axmr_ml{

	var	$prefix;
	var $lang;
	var $conn;

	function loadLanguage(){
		//Logger::send("Carico le stringhe...");
		$sql=new query($this->conn);
		$bind = array();
		$bind['LANG'] = $this->lang;
		$sql->exec("SELECT * FROM {$this->prefix}_I18N WHERE LANG=:LANG",$bind);
		while ($sql->get_row()){
			$_SESSION['labels'][$sql->row['LABEL']]=$sql->row['TEXT'];
		}

	}

	function __construct($prefix, $lang, $conn){
		if (session_id()=="") session_start();
		$this->prefix=$prefix;
		$this->lang=$lang;
		$this->conn=$conn;
		unset($_SESSION['labels']);
		if (!isset($_SESSION['labels']) || count($_SESSION['labels'])==0)
		$this->loadLanguage();
		//global $ml;
		//$ml=$this;
	}

	function changeLanguage($code){
		$this->lang=$code;
		$this->loadLanguage();
	}

	function updateLabel($string, $text){
		$bind['LANG'] = $this->lang;
		$bind['LABEL']= $string;
		$bind['TEXT']= $text;
		$sql=new query($this->conn);
		$sql->ins_upd("UPDATE {$this->prefix}_I18N SET TEXT=:TEXT WHERE LANG=:LANG AND LABEL=:LABEL ",$bind);
		$this->conn->commit();
		unset($_SESSION['labels']);
	}

	function out($string, $defaultValue=null){
		$retval = $string;
		if (isset($defaultValue) && $defaultValue!="") $retval=$defaultValue;
		if (!isset($_SESSION['labels'][$string]) || $_SESSION['labels'][$string]==""){
			$bind = array();
			$bind['LANG'] = $this->lang;
			$bind['LABEL']= $string;
			$label=$string;
			$sql=new query($this->conn);
			$sql_query="select * from {$this->prefix}_I18N where LANG=:LANG and LABEL=:LABEL";
			$text=$string;
			$sql->exec($sql_query, $bind);
			if ($sql->get_row()){
				$_SESSION['labels'][$string]=$sql->row['TEXT'];
			}else {
				if (isset($defaultValue) && $defaultValue!="") {
					$bind['TEXT']= $defaultValue;
					$text=$defaultValue;
				}
				else $bind['TEXT']= $string;

				Logger::send("inserisco in db {$bind['LABEL']}, $string");
				$sql->ins_upd("INSERT INTO {$this->prefix}_I18N (LANG, LABEL, TEXT) VALUES(:LANG, :LABEL, :TEXT) ",$bind);
				$this->conn->commit();
			}
			$_SESSION['labels'][$label]=$text;
			
		}else $retval=$_SESSION['labels'][$string];
		return $retval;
	}

}


function mlOut($string, $defaultValue=null){
	global $ml;
	$string=trim($string);
	$defaultValue=trim($defaultValue);
	return $ml->out($string, $defaultValue);
}


function mlChangeLanguage($code){
	global $ml;
	$ml->changeLanguage($code);
}

function mlGetLanguage(){
	global $ml;
	return $ml->lang;
}

function mlLoadLanguage(){
	global $ml;
	$ml->loadLanguage();
}

function mlOutJs($string, $defaultValue=null){
	return make_js(mlOut($string, $defaultValue));
}

function mlUpdateLabel($string, $text){
	global $ml;
	$ml->updateLabel($string, $text);
}
?>