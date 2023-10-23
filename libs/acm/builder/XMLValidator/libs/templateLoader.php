<?php 

class templateLoader{

	var $html_file;
	var $html_result;
	
	/*
	 *Carica il template, effettua le sostituzioni e restituisce il template 
	 * */
	
	/*
	 * Viene passato il file html con il template e i richiami al css e alle immagini
	 * Viene fatta una file_get_contents sul file passato
	 * */
	function templateLoader($html_file){
		$this->html_file=$html_file;
		$this->html_result=file_get_contents($this->html_file);
	}
	
	/*
	 * Inizializzo la variabile di stato , se ho necessità di cambiare template
	 * */
	function setTemplate($html_file){
		$this->html_file=$html_file;
	}
	
	/*
	 * Restituisce il template con i contenuti
	 * */
	function getTemplate(){
		return $this->html_result;
	}
	
	/*
	 * Effettua la sostiuzione dei contenuti 
	 * es.:
	 * <!-- xml_info--> con $xml_info
	 * */
	function replaceContent($regex, $replacement){
		$this->html_result=preg_replace($regex, $replacement, $this->html_result);
	}
}

?>




