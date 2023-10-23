<?php 
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'ajax_utilities.inc.php';


class ajax_cancella_paziente{
	
	//numero di passi necessari all'operazione
	private $steps = 3;
	private $scripts = '	<link rel="stylesheet" href="libs/js/jquery/themes/base/jquery.ui.all.css" type="text/css" media="all" />
						<link rel="stylesheet" href="libs/js/jquery/css/smoothness/jquery-ui-1.8.16.custom.css" type="text/css" media="all" />
						<script type="text/javascript" src="libs/js/jquery/jquery-last.js"></script>
						<script src="libs/js/jquery/ui/jquery-ui-1.8.7.custom.js" type="text/javascript"></script>
						<script src="libs/js/jquery/ui/i18n/jquery-ui-i18n.js" type="text/javascript"></script';
	
	$body = '<div id="dialog-form" title="Cancella paziente">
		<p class="validateTips">Tutti i campi sono obbligatori</p>
		
	</div>';
	
	public function __construct(){
		
	}
}


if (EnvironmentCheck::isAjax() === true){
	$canc = new Ajax_cancella_paziente();
	
	return array_to_json( $array );
}


