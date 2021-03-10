<?
/**
 * Classe legend_prototype
 * 
 * Classe prototipo che definisce il layout della legenda
 * @package ViewsAndControllers
 *
 */
class legend_prototype{
	var $html_legend_visita;
	var $html_legend_lista;
	var $testi;
	var $config_service;

	/**
	 * Costruttore
	 *
	 * @return legend_prototype
	 */
//	function legend_prototype($config_service){
//		global $in;
//
//		$this->config_service = $config_service;
//
//		if($config_service['lang'] == 'en'){
//			
//			$legend = "Legend";
//			
//		}else{
//			$legend = "Legenda";
//		}
//
//		$this->html_legend_visita="<br><br>
// 	<table border=\"0\" width=\"70%\" align=\"center\">
// <tr>
//  <td width=\"8%\" class=\"titolo\" colspan=\"2\">$legend</td>
// </tr>
//		 <TR>
//          <TD class=\"inputdossier\" width=\"5%\"><IMG src=\"images/to_be_comp.gif\" border=0> </TD>
//          <TD class=\"inputdossier\" width=\"95%\">".$this->testo("Form_da_compilare")." </TD></TR>
//        <TR>
//          <TD class=\"inputdossier\"><IMG src=\"images/saved.gif\" border=0> </TD>
//          <TD class=\"inputdossier\">".$this->testo("Form_salvata")."</TD></TR>
//        <TR>
//          <TD class=\"inputdossier\"><IMG src=\"images/submitted.gif\" border=0> </TD>
//          <TD class=\"inputdossier\">".$this->testo("Form_inviata")."</TD></TR>
//       
//        </TBODY>
//</TABLE>
// 	";
//
//		$this->html_legend_lista="<br><br>
// 	<table border=\"0\" width=\"70%\" align=\"center\">
// <tr>
//  <td width=\"8%\" class=\"titolo\" colspan=\"2\">".$this->testo("Titolo")."</td>
// </tr>
// <tr>
//  <td class=\"inputdossier\" width=\"5%\"><img src=\"/images/f_bianca.gif\" border=\"0\" ></td>
//     <td class=\"inputdossier\" width=\"95%\">".$this->testo("Da_compilare")."</td>
// </tr>
// <tr>
//  <td class=\"inputdossier\"><img src=\"/images/f_gialla.gif\" border=\"0\" ></td>
//     <td class=\"inputdossier\">".$this->testo("Da_completare")."</td>
// </tr>
// <tr>
//  <td class=\"inputdossier\"><img src=\"/images/f_verde.gif\" border=\"0\"></td>
//     <td class=\"inputdossier\">".$this->testo("Tutte_complete")."</td>
// </tr>
// <tr>
//  <td class=\"inputdossier\"><img src=\"/images/f_rossa.gif\" border=\"0\"></td>
//     <td class=\"inputdossier\">".$this->testo("Morte")."</td>
// </tr>
// </table>";
//		if($in['USER_TIP']=='DM'){
//			$this->html_legend_visita="
//				<table border=\"0\" width=\"70%\" align=\"center\">
//					<tr>
//					<td width=\"8%\" class=\"titolo\" colspan=\"2\">$legend</td>
//					</tr>
//				    <TR>
//				      <TD class=\"inputdossier\" width=\"5%\"><IMG src=\"/images/to_be_comp.gif\" border=0> </TD>
//				      <TD class=\"inputdossier\" width=\"95%\">".$this->testo("Form_da_compilare_dm")." </TD></TR>
//				    <TR>
//				      <TD class=\"inputdossier\"><IMG src=\"/images/saved.gif\" border=0> </TD>
//				      <TD class=\"inputdossier\">".$this->testo("Form_salvata_dm")."</TD></TR>
//				    <TR>
//				      <TD class=\"inputdossier\"><IMG src=\"/images/submitted.gif\" border=0> </TD>
//				      <TD class=\"inputdossier\">".$this->testo("Form_inviata_dm")."</TD></TR>
//				    </TBODY>
//				</TABLE>
//		 	";
//			$this->html_legend_lista="
//			 	<table border=\"0\" width=\"70%\" align=\"center\">
//					 <tr>
//					  <td width=\"8%\" class=\"titolo\" colspan=\"2\">$legend</td>
//					 </tr>
//					 <tr>
//					  <td class=\"inputdossier\" width=\"5%\"><img src=\"/images/f_bianca.gif\" border=\"0\" ></td>
//					     <td class=\"inputdossier\" width=\"95%\">Nessuna Scheda compilata.</td>
//					 </tr>
//					 <tr>
//					  <td class=\"inputdossier\"><img src=\"/images/f_gialla.gif\" border=\"0\" ></td>
//					     <td class=\"inputdossier\">Alcune schede devono ancora essere inserite. Cliccare sulla freccia gialla per visualizzare i dati gi&agrave; inseriti.</td>
//					 </tr>
//					 <tr>
//					  <td class=\"inputdossier\"><img src=\"/images/f_verde.gif\" border=\"0\"></td>
//					     <td class=\"inputdossier\">Tutte le schede sono state compilate. Cliccare sulla freccia verde per visualizzare o modificare i dati inseriti.</td>
//					 </tr>
//					 <tr>
//					  <td class=\"inputdossier\"><img src=\"/images/f_rossa.gif\" border=\"0\"></td>
//					     <td class=\"inputdossier\">Fine Studio</td>
//					 </tr>
//				 </table>";
//		}
//
//	}

	function legend_prototype($config_service){
		global $in;

		$this->config_service = $config_service;

		if($config_service['lang'] == 'en'){
			
			$legend = "Legend";
			
		}else{
			$legend = "Legenda";
		}

		$this->html_legend_visita="
				
		<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".$legend."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
							<!--p><i class=\"fa fa-plus blue\"></i> ".$this->testo("Form_da_compilare")."</p>
							<p><i class=\"fa fa-pencil-square-o orange\"></i> ".$this->testo("Form_salvata")."</p>
							<p><i class=\"fa fa-check-square-o green\"></i> ".$this->testo("Form_inviata")."</p-->
							
							<p><IMG src=\"/images/to_be_comp.gif\" border=0> ".$this->testo("Form_da_compilare")."</p>
							<p><IMG src=\"/images/saved.gif\" border=0> ".$this->testo("Form_salvata")."</p>
							<p><IMG src=\"images/submitted.gif\" border=0> ".$this->testo("Form_inviata")."</p>
						
					</div>
			</div>
 	
 	";
		$f_bianca="<i class=\"el-icon-file-new blue\"></i>";
		$f_gialla="<i class=\"fa fa-check orange\"></i>";
		$f_verde="<i class=\"fa fa-check-circle green\"></i>";
		$f_grigia="<i class=\"fa fa-check-square gray\"></i>";
		$f_blue="<i class=\"fa fa-check-circle-o blue\"></i>";
		$f_red="<i class=\"el-icon-remove-circle red\"></i>";
		$this->html_legend_lista="
				<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".$this->testo("Titolo")."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
					
				 	<p>$f_bianca ".$this->testo("Da_compilare")."</p>
				 	<p>$f_gialla  ".$this->testo("Da_completare")."</p>
					<p>$f_verde ".$this->testo("Tutte_complete")."</p>
				 	<!--p>$f_red ".$this->testo("Morte")."</p-->		
				 			</div>
     	</div>";
		if($in['USER_TIP']=='DM'){
			$this->html_legend_visita="
				
		<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".$legend."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
						<p><i class=\"fa fa-minus-circle red\"></i> ".$this->testo("Form_non_inserita")."</p>
						<p><i class=\"fa fa-pencil-square-o orange\"></i> ".$this->testo("Form_salvata")."</p>
						<p><i class=\"fa fa-check-square-o green\"></i> ".$this->testo("Form_inviata")."</p>
					</div>
			</div>
 	
 	";
			$this->html_legend_lista="
				<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".$this->testo("Titolo")."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
					
				 	<p>$f_bianca ".$this->testo("Da_compilare")."</p>
				 	<p>$f_gialla  ".$this->testo("Da_completare")."</p>
					<p>$f_verde ".$this->testo("Tutte_complete")."</p>
				 	<p>$f_red ".$this->testo("Morte")."</p>		
				 			</div>
     	</div>";
		}

	}

function testo($testo){
		//TODO: mettere $this->config_service ['Lista_schede'] nelle frasi in modo da configurarle dallo study.xml

		//HOW TO
		/* Per utilizzare questa funzione chiamarla cosi nel codice:
		 * $this->testo("PAROLACHIAVE")
		 * e qui dentro definire per ogni lingua
		 * $this->testi['PAROLACHIAVE']="Frase da far apparire";
		 */
//		print_r($this->config_service);
		if(!isset($this->testi[$testo])){
			if(strtolower($this->config_service['lang'])=='en'){
				$this->testi['Titolo']="Legend";
				
				$this->testi['Form_da_compilare']="Click on the blank square to fill in data";
				$this->testi['Form_salvata']="Click on red tick to modify data";
				$this->testi['Form_inviata']="Click on green tick to read the inserted data. You cannot modify them.";
				
				$this->testi['Form_da_compilare_dm']="Form to be filled in.";
				$this->testi['Form_salvata_dm']="Saved form. Form to be completed.";
				$this->testi['Form_inviata_dm']="Sent form. Click on green tick to read/modify the inserted data.";
				
				$this->testi['Da_compilare']="Empty forms.";
				$this->testi['Da_completare']="Some forms to be completed.";
				$this->testi['Tutte_complete']="Forms completed.";
				$this->testi['Morte']="Dead patient.";
			}
			else{
				$this->testi['Form_da_compilare']="Form da compilare. Cliccare il riquadro per compilare la form.";
				$this->testi['Form_salvata']="Form salvata. Cliccare sul check rosso per visualizzare/modificare i dati inseriti.";
				$this->testi['Form_inviata']="Form inviata. Cliccare sul check verde per visualizzare i dati inseriti. Non &egrave; possibile la modifica dei dati per questo profilo.";
				
				$this->testi['Form_da_compilare_dm']="Scheda non compilata.";
				$this->testi['Form_salvata_dm']="Scheda parzialmente compilata. Cliccare sul check rosso per visualizzare i dati inseriti.";
				$this->testi['Form_inviata_dm']="Scheda completata e inviata. Cliccare sul check verde per modificare i dati inseriti.";
				
				
				$this->testi['Titolo']="Legenda";
				$this->testi['Da_compilare']="Schede da compilare. Cliccare sulla freccia bianca per iniziare l'inserimento.";
				$this->testi['Da_completare']="Alcune schede devono ancora essere inserite. Cliccare sulla freccia gialla per proseguire l'inserimento.";
				$this->testi['Tutte_complete']="Tutte le schede sono state compilate. Cliccare sulla freccia verde per visualizzare i dati inseriti.";
				$this->testi['Morte']="Fine Studio.";
			}
			if($this->config_service ['Patients_list']!='')$this->testi['Registro Lista Pazienti']=$this->config_service ['Patients_list'];

		}
		return $this->testi[$testo];
	}

}
?>