<?php 

class fileLoader{
	
	var $directory;
	var $ext;
	var $html_list_file;
	var $list_file;
	
	/*
	 * Genera le liste dei file xml e xsd discriminando sull'estensione.
	 * Genera la select html per selezionare i file.  
	 * */
	
	function fileLoader($directory, $ext){
		$this->directory=$directory;
		$this->ext=$ext;
		
//		print_r($this->directory);die();
		
		/* Apro la directory selezionata */
		if ($handle = opendir($this->directory)) {

   			/* Leggo il contenuto fino alla fine */
   			while ($file = readdir($handle)) {

      			/* Non considero la working directory(.) e la directory padre(..) */
      			if ($file != "." && $file != "..") {
         			if (is_dir("$this->directory$file")) {
         				/* Se trovo una directory non la aggiungo all'array di files */
         			
         			} else {
         			
         				/* Se file normale, lo aggiungo all'array di files
						 * regex
						 * b = boundary, solo parole intere
						 * $ = solo se alla fine della stringa
						 * i = case insensitive
						 * 
						 * OLD REGEX /\b{$this->ext}\b\$/i
						 */
         				if(preg_match("/^.*\.($this->ext)$/i",$file)){
            				$this->list_file[]=$file;
         				}
         			}	
      			}
   			}
   			/* Chiudo la directory */
   			closedir($handle);
		}
		
		/* Se l'array di file non � nullo lo ordino */
		if(count($this->list_file) > 0){
			sort($this->list_file);	
		}
		
		/* Creo la <SELECT> html che rappresenta la lista di file */
		$this->html_list_file="<select name=\"file_{$this->ext}\" style=\"width:85%;\">";
		$this->html_list_file.="<option checked=\"checked\" value=\"\">-- Select {$this->ext} File --</option>";
		for($i=0;$i<count($this->list_file);$i++){
			$this->html_list_file.="<option value=\"{$this->list_file[$i]}\">{$this->list_file[$i]}</option>";
		}
		$this->html_list_file.="</select>";
	}
	
	/* Restituisce un array di file CSV */
	function getFileList(){
		
		return $this->list_file;
	}
	
	/* Restituisce la rappresentazione html della lista di file CSV usando una <SELECT> */
	function getHtmlFileList(){
		
		return $this->html_list_file;
	}

}

?>




