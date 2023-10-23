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
	function legend_prototype($config_service){
		global $in;

		$this->config_service = $config_service;

		//if($config_service['lang'] == 'it'){
		//	$legend = "Legenda";
		//}else{
		//	$legend = "Legend";
		//}
		$appendSDV = "";
		if(class_exists('SDV_module')){
			$appendSDV = "

					<div class=\"widget-body\" style=\"padding:10px\">
							<p><i class=\"fa fa-search\" style=\"font-size:1.2em; color:green; \" title=\"SDV completed\"></i> ".mlOut("System.legend.sdv.completato",$this->testo("SDV completato"))."</p>
							<p><i class=\"fa fa-search\" style=\"font-size:1.2em; color:orange; \" title=\"SDV started\"></i> ".mlOut("System.legend.sdv.iniziato",$this->testo("SDV iniziato"))."</p>
							<p><i class=\"fa fa-search\" style=\"font-size:1.2em; color:#F1F1F1; \" title=\"SDV empty\"></i> ".mlOut("System.legend.sdv.da_iniziare",$this->testo("SDV da iniziare"))."</p>
							<p><i class=\"fa fa-search\" style=\"font-size:1.2em; color:grey; \" title=\"SDV empty\"></i> ".mlOut("System.legend.sdv.vuoto",$this->testo("SDV vuoto form"))."</p>
							<p><i class=\"fa fa-exclamation\" style=\"font-size:1.2em; color:#DD5A43; \" title=\"SDV mandatory\"></i> ".mlOut("System.legend.sdv.mandatory",$this->testo("SDV mandatory"))."</p>
						
					</div>

				";
		}

		$this->html_legend_visita="
				
		<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".mlOut("System.legend.titolo",$this->testo("Titolo"))."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
						<p><i class=\"fa fa-plus blue\"></i> ".mlOut("System.legend.form_non_inserita",$this->testo("Form_da_compilare"))."</p>
						<p><i class=\"fa fa-pencil-square-o orange\"></i> ".mlOut("System.legend.form_salvata",$this->testo("Form_salvata"))."</p>
						<p><i class=\"fa fa-check-square-o green\"></i> ".mlOut("System.legend.form_inviata",$this->testo("Form_inviata"))."</p>
						
					</div>
					{$appendSDV}
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
						<h5>".mlOut("System.legend.titolo",$this->testo("Titolo"))."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
					
						<p>$f_bianca ".mlOut("System.legend.da_compilare",$this->testo("Da_compilare"))."</p>
						<p>$f_gialla  ".mlOut("System.legend.da_completare",$this->testo("Da_completare"))."</p>
						<p>$f_verde ".mlOut("System.legend.tutte_complete",$this->testo("Tutte_complete"))."</p>
						<!--p>$f_red ".mlOut("System.legend.morte",$this->testo("Morte"))."</p-->
				 			</div>
     	</div>";
		if($in['USER_TIP']=='DM'){
			$this->html_legend_visita="
				
		<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".mlOut("System.legend.titolo",$this->testo("Titolo"))."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
						<p><i class=\"fa fa-minus-circle red\"></i> ".mlOut("System.legend.form_non_inserita",$this->testo("Form_non_inserita"))."</p>
						<p><i class=\"fa fa-pencil-square-o orange\"></i> ".mlOut("System.legend.form_salvata",$this->testo("Form_salvata"))."</p>
						<p><i class=\"fa fa-check-square-o green\"></i> ".mlOut("System.legend.form_inviata",$this->testo("Form_inviata"))."</p>
					</div>
					{$appendSDV}
			</div>
 	
 	";
			$this->html_legend_lista="
				<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".mlOut("System.legend.titolo",$this->testo("Titolo"))."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
					
						<p>$f_bianca ".mlOut("System.legend.da_compilare",$this->testo("Da_compilare"))."</p>
						<p>$f_gialla  ".mlOut("System.legend.da_completare",$this->testo("Da_completare"))."</p>
						<p>$f_verde ".mlOut("System.legend.tutte_complete",$this->testo("Tutte_complete"))."</p>
						<p>$f_red ".mlOut("System.legend.morte",$this->testo("Morte"))."</p>
				 			</div>
     	</div>";
		}
        //Legenda SDV
        if (strtoupper($in['SDV_LIST'])/* == "STATUS"*/){
            $this->html_legend_lista="
			 	<table border=\"0\" width=\"70%\" align=\"center\">
					 <tr>
					  <td width=\"8%\" class=\"titolo\" colspan=\"2\">".mlOut("System.legend.titolo",$this->testo("Titolo"))."</td>
					 </tr>
					 <tr>
					  <td class=\"inputdossier\" width=\"5%\">{$f_bianca}</td>
					  <td class=\"inputdossier\" width=\"95%\">".mlOut("System.legend.sdv.da_iniziare",$this->testo("SDV da iniziare"))."</td>
					 </tr>
					 <tr>
					  <td class=\"inputdossier\">{$f_gialla}</td>
					  <td class=\"inputdossier\">".mlOut("System.legend.sdv.iniziato",$this->testo("SDV iniziato"))."</td>
					 </tr>
					 <tr>
					  <td class=\"inputdossier\">{$f_verde}</td>
					  <td class=\"inputdossier\">".mlOut("System.legend.sdv.completato",$this->testo("SDV completato"))."</td>
					 </tr>
					 <tr>
					  <td class=\"inputdossier\">{$f_blue}</td>
					  <td class=\"inputdossier\">".mlOut("System.legend.sdv.skipped",$this->testo("SDV skipped"))."</td>
					 </tr>
					 <tr>
					  <td class=\"inputdossier\">{$f_grigia}</td>
					  <td class=\"inputdossier\">".mlOut("System.legend.sdv.vuoto",$this->testo("SDV vuoto"))."</td>
					 </tr>

				 </table>";
        }

	}

function testo($testo){
		if(!isset($this->testi[$testo])){
			if(strtolower($this->config_service['lang'])=='it'){
				$this->testi['Form_non_inserita']="Questa form non è stata compilata";
				$this->testi['Form_da_compilare']="Form da compilare. Cliccare il riquadro per compilare la form.";
				$this->testi['Form_salvata']="Form salvata. Cliccare sul check rosso per visualizzare/modificare i dati inseriti.";
				$this->testi['Form_inviata']="Form inviata. Cliccare sul check verde per visualizzare i dati inseriti. Non  possibile la modifica dei dati per questo profilo.";

				$this->testi['Form_da_compilare_dm']="Scheda non compilata.";
				$this->testi['Form_salvata_dm']="Scheda parzialmente compilata. Cliccare sul check rosso per visualizzare i dati inseriti.";
				$this->testi['Form_inviata_dm']="Scheda completata e inviata. Cliccare sul check verde per modificare i dati inseriti.";


				$this->testi['Titolo']="Legenda";
				$this->testi['Da_compilare']="Schede da compilare. Cliccare sulla freccia bianca per iniziare l'inserimento.";
				$this->testi['Da_completare']="Alcune schede devono ancora essere inserite. Cliccare sulla freccia gialla per proseguire l'inserimento.";
				$this->testi['Tutte_complete']="Tutte le schede sono state compilate. Cliccare sulla freccia verde per visualizzare i dati inseriti.";
				$this->testi['Morte']="Fine Studio.";

				$this->testi['Skipped']="Visita saltata.";
				$this->testi['SDV da iniziare']="SDV da iniziare";
				$this->testi['SDV iniziato']="SDV iniziato";
				$this->testi['SDV completato']="SDV completo e firmato. Click sulla freccia verde per visualizzare SDV";
				$this->testi['SDV skipped']="Visita saltata, nessun SDV da completare.";
				$this->testi['SDV vuoto']="Visita vuota, SDV da effettuare in seguito.";
				$this->testi['SDV vuoto form']="Form vuota, SDV da effettuare in seguito.";
				$this->testi['SDV mandatory']="La form ha dei campi SDV obbligatori";
			}
			else{
				$this->testi['Titolo']="Legend";

				$this->testi['Form_non_inserita']="This form has not been compiled";
				$this->testi['Form_da_compilare']="Click on the plus icon to fill in data";
				$this->testi['Form_salvata']="Click on red tick to modify data";
				$this->testi['Form_inviata']="Click on green tick to read the inserted data. You cannot modify them.";
				
				$this->testi['Form_da_compilare_dm']="Form to be filled in.";
				$this->testi['Form_salvata_dm']="Saved form. Form to be completed.";
				$this->testi['Form_inviata_dm']="Sent form. Click on green tick to read/modify the inserted data.";
				
				$this->testi['Da_compilare']="Empty forms.";
				$this->testi['Da_completare']="Some forms to be completed.";
				$this->testi['Tutte_complete']="Forms completed.";
				$this->testi['Morte']="Dead patient.";

                $this->testi['Skipped']="Skipped visit.";
                $this->testi['SDV da iniziare']="SDV to be started. Click on the white check to start SDV.";
                $this->testi['SDV iniziato']="SDV started. Click on the yellow check to continue SDV.";
                $this->testi['SDV completato']="SDV completed and signed. Click on the green check to see SDV.";
                $this->testi['SDV skipped']="Visit is skipped, no SDV has to be done.";
                $this->testi['SDV vuoto']="Visit is empty. SDV has to be done in a next moment.";
                $this->testi['SDV vuoto form']="Form is empty. SDV has to be done in a next moment.";
                $this->testi['SDV mandatory']="Form has SDV manatory fields.";
			}
			if($this->config_service ['Patients_list']!='')$this->testi['Registro Lista Pazienti']=$this->config_service ['Patients_list'];

		}
		$testo_id=str_replace(" ", "_", $testo);
		return mlOut("Legend.".$testo_id, $this->testi[$testo]);
	}

}
?>