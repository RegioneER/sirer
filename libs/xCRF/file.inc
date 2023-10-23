<?php
/**
 * @package Reporting
 */
class file{
	var $handle;
	var $filename;
	function __construct($nome_file=null,$dir=null,$absolute=false){
		if(!$nome_file) return false;
		if(!$absolute){
			$path=$_SERVER['PATH_TRANSLATED'];
			$script=explode('/',$path);
			$path=str_replace($script[count($script)-1], "", $path)."/";
			$path.=trim($dir,"/")."/";
		}		
		$this->handle=fopen($path.$nome_file,"w+");
		$this->filename=$nome_file;
	}
	function write($testo){
		return fwrite($this->handle,$testo);
	}
	function __destruct(){
		fclose($this->handle);
	}
	function csv_line($array, $separator = ";"){
   	//$SEPARATOR = ";";
		$line = "";
		foreach ($array as $key => $value){
			$value=str_replace("\"","'",$value);
			$line.='"'.$value.'"'.$separator;
		}
		$line=rtrim($line,$separator);
		$line.="\r\n";
		$line=utf8_decode($line);
		$this->write($line);
	}
	function close(){
		fclose($this->handle);
	}
}
?>