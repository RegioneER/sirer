<?php
include("config.inc.php");

include("libs/templateLoader.php");
include("libs/fileLoader.php");
include("libs/fileInfo.php");
include("libs/xmlValidator.php");

/* Carico il template */
$html_template = new templateLoader($template_dir."template.html");

/* Classi tabs */
$class_home="tab-inactive";
$class_validation="tab-inactive";
$class_manage="tab-inactive";
$class_help="tab-inactive";


/* GET popolata quando clicco sui link nella toolbar, POST quando parte la validazione
 * Pressione sul pulsante, il controllo passa ad index con $_POST['tab'] = 2, e $_POST['validation'] = true => hidden)
 */
if((isset($_GET['tab']) && $_GET['tab'] == 2) || (isset($_POST['tab']) && $_POST['tab'] == 2)){
	
	/* Inizializzo il nome della pagina e la classe CSS del tab scelto */
	$class_validation="tab-active";
	$page_name="Validazione";	
	
	/* Listo i file nella directory XML */
	$list_result = new fileLoader($xml_dir, "xml");
	$xml_file_list=$list_result->getHtmlFileList();
	
	/* Listo i file nella directory XSD */
	$list_result = new fileLoader($xsd_dir, "xsd");
	$xsd_file_list=$list_result->getHtmlFileList();
	
	/* Help validazione */
	$body_content="";
	
	/* Html per il tab 2 -> stampo la form di selezione file nella colonna sinistra e il box centrale per il risultato della validazione */
	$body_result="<table class=\"body\" cellpadding=\"0\" cellspacing=\"0\">
       <tr>
       	<!-- Colonna centrale 65% -->
        <td class=\"body-cx\">
        <!-- Box risultato validazione -->
         <div class=\"box-cx\">
          {$body_content}
	      <div id=\"validation_box\">
          <!-- corpo -->
          <!-- xsd_info-->
          <!-- xml_info-->
		  <!-- errors -->
	     </div>
        </div>
       </td>
      </tr>
      <tr>
      <td colspan=\"2\">
      <!-- validation -->
      </td>
      </tr>
     </table>";
	
	/* Sostituisco l'html della navigation bar e del tab 2(VALIDAZIONE) nel template */
	//$html_template->replaceContent("/<!-- navigation -->/", "<a href=\"?tab=1\"><font style=\"font-weight:bold;color:#393939;\">Home</font></a> &raquo; <font style=\"font-weight:bold;color:#315091;font-size:16px;\">".$page_name."</font>");
	$html_template->replaceContent("/<!-- body_result -->/", $body_result);
	
	/* Se viene premuto il pulsante "Valida XML" */
	if(isset($_POST['validation']) && $_POST['validation']== "true"){
		
		/* Inizia la validazione e stampa l'esito e i gli eventuali errori */
		$validation_result = new xmlValidator($xml_dir.$_POST['file_xml'], $xsd_dir.$_POST['file_xsd']);
		$validation_result->validate();
		
		/* Esito */
		$html_validation_result = $validation_result->get_validation_result();
		$html_template->replaceContent("/<!-- validation -->/", $html_validation_result);
		
		/* XSD file info */
		$xsd_file_info = new fileInfo ($xsd_dir.$_POST['file_xsd']);
		$xsd_info = $xsd_file_info->getHtmlFileInfo ();
		$html_template->replaceContent("/<!-- xsd_info-->/", $xsd_info);
		
		/* XML file info */
		$xml_file_info = new fileInfo ($xml_dir.$_POST['file_xml']);
		$xml_info = $xml_file_info->getHtmlFileInfo ();
		$html_template->replaceContent("/<!-- xml_info-->/", $xml_info);
		
		/* Errori */
		$html_errors = $validation_result->get_html_errors();
		$html_template->replaceContent("/<!-- errors -->/", $html_errors);
	}
	
}

/* Stampo i tabs */
//$html_template->replaceContent("/<!-- tabs -->/", $tabs);
/* Prendo e Stampo il template */
$html_result=$html_template->getTemplate();
print($html_result);

?>
