<?php


class modalWindow{
	
	//connessione al DB
	private $sql;
	//il contenuto della pagina
	private $body;
	//var d'ambiente
	private $session_vars;
	
	//core di quello che verrà generato
	private $scripts;
	private $body;
	private $list;
	
	//pagina da richiamare per la form
	private $ajax_dir = 'ajax'. DIRECTORY_SEPARATOR;
	private $ajax_page;
	private $ajax_obj;
	
	
	//constructor
	public function __construct($conn, $session_vars=null, $ajax_page, $list ) {
		//controllo se è attivo il debug
		if ((isset($_GET['debug']) && $_GET['debug'] === true) || (isset($_POST['debug']) && $_POST['debug']===true) )
		$this->debug= true;
	
		//creo la connessione al DB
		$this->sql = new query($conn);
	
		//salvo le variabili d'ambiente
		$this->session_vars = $session_vars;
		
		$this->ajax_page = $ajax_page; 
		if (file_exists($ajax_dir.$this->ajax_page))
			include_once ($ajax_dir.$this->ajax_page);
		$this->ajax_obj = new $this->ajax_page ;
		
		
		$this->list = $list;
	}
	
	/**
	 * funzione che restituisce gli script necessari per la finestra modale
	 * 
	 */
	function get_scripts(){
		return $this->scripts;
	}
	
	/**
	* funzione che restituisce il body necessario per la finestra modale
	*
	*/
	function get_body(){
		return $this->body;
	}
	
	
	
}

