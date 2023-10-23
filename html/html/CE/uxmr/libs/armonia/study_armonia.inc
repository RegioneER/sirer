<?php

/**
 * Classe Studio A.R.MON.I.A. (Accorpamento Registri MONitoraggio In Armonia)
 * La classe nasce nel lontano Giugno 2011 per dare un senso al proliferare insensato di tutti
 * i registri dell'Anna (Covezzoli, preciso per limitare la smania di protagonismo della Rigazio,ndG), che stavano prendendo una brutta piega.
 *
 * Venne cosi' un'idea geniale a Giacomo Tufano e a Giorgio Delsignore, che unirono le loro menti (anche se il lavoro sporco tocco' tutto a Giacomo)
 * per realizzare questo gioiellino di classe e tutti i servizi/files/altro annessi e connessi.
 *
 * @package CORE
 */
class Study_armonia extends Study_prototype_mxmr {
	var $field_lib = '/http/lib/XMR/v2.1/libs4bind/';
	var $show_gantt=false;
	var $log_out_button = "<a href='/?ShibLogOut'><b>Log-out</b></a>";

	var $footer="<table width=\"95%\" align=\"center\">
				<tr>
					<td align=\"right\">
						<a href=\"/cgi-bin/ammin_chpwd\">cambia password</a>
						</td>
				</tr>
				<tr>
					<td align=\"center\">
						Powered by
						<br />
						<img src='libs/armonia/imgs/logo_armonia2.png' style='height:100px;' />
						</td>
				</tr>

			</table>";
//TODO: prendere da study_prototype tutte le funzioni che utilizzano $this->xml_dir e portarle qua per sostituire con :
//$this->getXMRPath("xml_dir",$list)."/".$list;

	function Controller(){

		global $visit_exam;
		global $in;
		$in=$this->session_vars;
		global $body;
		global $config_service;
		global $filetxt;
		global $remote_userid;
		$vlist= new xml_esams_list($this->getXMRPath("xml_dir",$visit_exam).'/'.$visit_exam);
		//	echo $visit_exam ."<hr>";

		// 	print_r($this->session_vars);
		if($in['TIPO_MODIF']=='N'||!isset($in['TIPO_MODIF'])){
			//echo "<hr>NADA<hr>";
			//print_r($this->session_vars);
			parent::Controller();
		}
		//inserisci scheda vuota
		if($in['TIPO_MODIF']=='P'){
			//	echo "<hr>AGREGA<hr>";

			$sql=new query($this->conn);
				
			$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
			$xml_form->xml_form_by_file ( $this->getXMRPath("xml_dir",$this->vlist->esams [$in['VISITNUM']] [$in['ESAM']] ['XML'] ) . '/' . $this->vlist->esams [$in['VISITNUM']] [$in['ESAM']] ['XML'] );
			$nome_tabella = $xml_form->form ['TABLE'];
				
			$this->InsertProgrEsamConCorrelate($nome_tabella,$in['VISITNUM'],$in['VISITNUM_PROGR'],$in['ESAM'], $in['PROGR']);
				
			//pulisco il buffer
			ob_clean();
			//re-indirizzo sulla vista paziente
			header("Location: index.php?CENTER={$in['CENTER']}&CODPAT={$in['CODPAT']}&exams=visite_exams.xml");
			die();

		}
		//cancella scheda
		if($in['TIPO_MODIF']=='C'){
			//	print_r($this->vlist->esams);
			// 			echo "<hr>CANCELLA<hr>";die();

			$sql=new query($this->conn);
			$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
			$xml_form->xml_form_by_file ($this->getXMRPath("xml_dir",$this->vlist->esams [$in['VISITNUM']] [$in['ESAM']] ['XML']) . '/' . $this->vlist->esams [$in['VISITNUM']] [$in['ESAM']] ['XML'] );
			$nome_tabella = $xml_form->form ['TABLE'];

			if ($this->vlist->esams[$in['VISITNUM']][$in['ESAM']]['PROGR']=='yes'){
				//				echo "<hr>PROGRESIVO<hr>";die();
				$this->DeleteProgrEsamConCorrelate($nome_tabella,$in['VISITNUM'],$in['VISITNUM_PROGR'],$in['ESAM'], $in['PROGR']);
				//pulisco il buffer
			}
			else   {
				//				 echo "<hr>NORMAL<hr>";die();
				$this->DeleteEsam($nome_tabella,$in['VISITNUM'],$in['VISITNUM_PROGR'],$in['ESAM']);
			}
				
			//metto il salvataggio query per chiudere la query se era questo il caso
			if (isset($in['ID_QUERY']) && !isset($in['eform'])) {
				$query = new query ( $this->conn );
				$sql_equery = "update " . $this->config_service['service']. "_equery set validata=1, val_userid=:userid, val_dt=sysdate, chiusa='1', chiusa_dt=sysdate where id=:id_query";
				$bindUpdate = array();
				$bindUpdate['USERID']=$in ['remote_userid'];
				$bindUpdate['ID_QUERY']=$in ['ID_QUERY'];
				// 				//echo $sql_equery;print_r($bindUpdate);die();
				$query->ins_upd ($sql_equery,$bindUpdate);
				$this->conn->commit();
				ob_clean();
				//re-indirizzo
				header("Location: index.php?eQuery&");
				die();
			}
			else{
				ob_clean();
				//re-indirizzo sulla vista paziente
				header("Location: index.php?CENTER={$in['CENTER']}&CODPAT={$in['CODPAT']}&exams=visite_exams.xml");
				die();
			}

		}
		if ($_GET['JUST_DELETE'] == 'yes'){
			die("avvisare giacomo tufano (g.tufano@cineca.it) se si verifica questa scritta. prego specificare COME si &egrave; arrivati qua.");
			die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=index.php?exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}&CENTER={$in['CENTER']}\"></head></html>" );
		}

		//Gestisco il messaggio dopo la registrazione che re-indirizza sulla pagina di riepilogo registrazione e mostra il menu
		if (isset($this->session_vars['ret_registrazione']) && $this->session_vars['ret_registrazione'] == 'yes'){
			$body.="<TABLE align=center class=\"bordi\" width=\"70%\">
     			<TR>
           <TD align=center><b><font size=\"3\">Il paziente &egrave; stato registrato con</font></b> <br>
				<br>
				<br>
				<font size=\"4\">Codice Paziente:</font>
				<font size=\"4\" color=\"#A60273\"> {$this->pk_service}</font>
				(Numero progressivo)<br><br>
				<br>
			<b><font size=\"2\"><a href=\"index.php?CENTER={$this->session_vars['CENTER']}&CODPAT={$this->session_vars['CODPAT']}&VISITNUM=0&ESAM=1&form=diagnosi.xml\"><u>Procedi con l'inserimento della Diagnosi</u></a><br><br><br><br>
			<a href=\"index.php?list=patients_list.xml\"><u>Lista dei pazienti</u></a></TD>
			</TR>
		</TABLE>";
				
			$link_scheda_succ="index.php?CENTER={$this->session_vars['CENTER']}&CODPAT={$this->session_vars['CODPAT']}&VISITNUM=1&ESAM=1&form=eleggibilita.xml";
			$link_home="index.php";
			$this->body=$body;
		}

		//gestisco il messaggio e la creazione del PDF dopo la richiesta farmaco
		if (isset($this->session_vars['ret_r_farm'])){

			// 			$f_dir=$this->xml_dir."/documents/";
			$f_dir=$this->getXMRPath("xml_dir")."/documents/";

			//nel caso in cui l'esame non sia progressivo.. (PTA)
			if($this->session_vars['PROGR'] == '')
			$this->session_vars['PROGR'] = 1;
			// 			$fmame='r_farm_pdf'.$this->session_vars['CENTER'].'_'.$this->session_vars['CODPAT'].'_1_2'.'_'.$this->session_vars['PROGR'].'.pdf';
			$fmame='r_farm_pdf'.$this->session_vars['CENTER'].'_'.$this->session_vars['CODPAT'].'_1_'.$this->session_vars['ESAM_PDF'].'_'.$this->session_vars['PROGR'].'.pdf';


			$dir_handle = @opendir($f_dir);
			$find=0;
			while ($file = readdir($dir_handle))
			if ($file==$fmame) $find=1;
			if ($find==1){

				$body.="<TABLE align=center class=\"bordi\">
		     			<TR>
		           <TD align=center><b><font size=\"3\"><br><br>
								<a href=\"xml/documents/$fmame\" target=new>
									Stampa richiesta farmaco
								</a></font></b><br><br>
								<a href=\"index.php?CENTER={$this->session_vars['CENTER']}&CODPAT={$this->session_vars['CODPAT']}&exams=visite_exams.xml\" >Lista delle schede del Paziente</a><br><br>
		
					<a href=\"index.php?CENTER={$this->session_vars['CENTER']}&list=patients_list.xml\"><u>Lista pazienti registrati</u></a></TD>
					</TR>
				</TABLE>";
				$this->body=$body;
			}
			else die("<html><head><meta http-equiv=\"refresh\" content=\"1;url=index.php?CENTER={$this->session_vars['CENTER']}&CODPAT={$this->session_vars['CODPAT']}&exams=visite_exams.xml\"></head></html>");
		}

		//gestisco il ritorno alla home della farmacia territoriale
		if (isset($this->session_vars['ret_disp'])){
			if (preg_match("/\b......00.\b/", $remote_userid))
			die("<html><head><meta http-equiv=\"refresh\" content=\"1;url=index.php\"></head></html>");
		}

		//creo il pdf se richiesto
		if($this->session_vars['pdf']=='create'){
			$this->pdf_print();
		}

		//rimuovo i links che non voglio vengano mostrati
		//PER LE FARMA_TERRITORIALI
		if (preg_match("/\b......00.\b/", $remote_userid)){
			$this->body=preg_replace("/<a href(.*?)Lista Paziente<\/a>/sm", "", $this->body);
			$this->body=preg_replace("/<a href(.*?)Vista Paziente<\/a>/sm", "", $this->body);
		}

		//gestisco l'invio del messaggio
		if (isset($in['MSG']) && $in['MSG']!="" && $in['TMSG']==""){

			$file_form=$this->getXMRPath("xml_dir","invio_messaggio.xml")."/invio_messaggio.xml";
			$xml_form=new xml_form();
			$xml_form->xml_form_by_file($file_form);
				
			$xml_form->config_service['field_lib']= $this->field_lib;
			// 			print_r($xml_form);die();
			$xml_form->open_form();
			$body.=$xml_form->body;
			//echo $body;
			$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
			$script="<script type=\"text/javascript\">
  		function invia_f()
 		  {
   			f=document.forms[0];
   			el=f.elements;
  			specifiche='A=ON&L=0&F=0';
  		  c1=''+
   			'<<t###SUBMSG###Oggetto del Messaggio>>'+
  			 '<<t###TXTMSG###Testo del Messaggio>>'+
  			 '';
  
  			 rc=contr(c1,specifiche);
  			 if (rc) {return false}
  			 document.forms[0].TMSG.value='1';
 				 document.forms[0].action='index.php'; 
         document.forms[0].submit();
      }
  
 			 </script>";
			$filetxt=preg_replace("/<!--script-->/", $script, $filetxt);
			$filetxt=preg_replace("/cf\(\)/","", $filetxt);
			//	echo $filetxt;
			$this->body=$body;

		}

		if (isset($in['MSG']) && $in['MSG']!="" && $in['TMSG']=="1"){
			$this->inviaMessaggioAiPartecipanti($in,$config_service);
		}

		//gestisco lo scancellamento pazienti
		if (isset ( $in['NASCPZ_ACTION'] ) &&  $in['NASCPZ_ACTION']== 'edit' ) {
			if ($in['USER_TIP']=='DM' && ($in['CODPAT'] != '' && $in['CENTER'] != ''))
				$this->CancellaPaziente ();
			else die("Accesso non autorizzato o dati mancanti. E' necessario tornare indietro e riprovare. <a href='/'>Back</a>");
		}
		//gestisco lo scancellamento pazienti
		if (isset ( $in['TRASF_ACTION'] ) &&  $in['TRASF_ACTION']== '1' ) {
			if ($in['USER_TIP']=='DM')
				$this->TrasferisciPaziente ();
			else die("Accesso non autorizzato o dati mancanti. E' necessario tornare indietro e riprovare. <a href='/'>Back</a>");
		}
	}

	function check_enable_visit() {
		if ($this->session_vars [$this->config_service ['PK_SERVICE']] == 'next')
		return false;
		parent::check_enable_visit();
		$query= new query($this->conn);
		$in = $this->session_vars;
		$service = $this->service;

		$config_service = $this->config_service;

		foreach ( $this->vlist->esams [$in ['VISITNUM']] as $key => $val ) {
			if (isset ( $val ['MANDATORY'] ) && $val ['MANDATORY'] == 'yes')
			$mand_exams [$key] = "yes";
		}
		foreach ( $mand_exams as $key => $val ) {
			$exams .= "$key,";
		}
		$exams = rtrim ( $exams, "," );

		//TODO SISTEMA METTENDO COSì:
		/*
		$esami = array();
		foreach ( $this->vlist->esams [$in ['VISITNUM']] as $key => $val ) {
		if (isset ( $val ['MANDATORY'] ) && $val ['MANDATORY'] == 'yes')
		$esami[] = $key;
		}
		$exams = implode(",", $esami);
		//non sono ancora soddisfatto devo trovare il modo con array_keys di sistemare ancora meglio. ma ho paura
		* che MANDATORY="no" mi freghi...
		*/


		if ($exams != '') {
			$sql = "select min(nvl(fine,0)) as fine from {$service}_COORDINATE where {$config_service['PK_SERVICE']}=:pk_service and VISITNUM=:visitnum and esam in ($exams)";
				
			unset($bind);
			$bind['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
			$bind['VISITNUM']=$in['VISITNUM'];
				
			echo "$sql ".print_r($bind,true);

			//$query->set_sql ( $sql );
			$query->exec ($sql,$bind);//binded
			$query->get_row ();
			$fine = $query->row ['FINE'];
			//echo "<li>$sql</li>";
			//echo $query->tb_res();
			if ($fine == 1) {
				$close=true;

				foreach ($this->vlist->esams[$in['VISITNUM']] as $esam => $attrib){
					if($attrib['PROGR']=="yes") $close=false;
				}
				if ($close){
					$str="update {$service}_coordinate set visitclose=1 where visitnum=:visitnum and {$config_service['PK_SERVICE']}=:pk_service";
					$bind = array();
					$bind['VISITNUM'] = $in ['VISITNUM'];
					$bind['PK_SERVICE'] = $in[$config_service['PK_SERVICE']];

					$query->exec($str,$bind);//binded
						
				}
			}
		}
	}

	function form($xml, $col_modifica = true, $no_link_back=false) {
		$this->session_vars ['form'] = $xml;
		$vlist = $this->vlist;
		$in = $this->session_vars;
		$conn = $this->conn;
		$service = $this->service;
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );

		$xml_form->xml_form_by_file ( $this->getXMRPath("xml_dir",$xml) . '/' . $xml );

		if (! $xml_form->allinea_db ()) {
			$body .= "<p align=center>";
			$body = $xml_form->body;
			$body .= "<form method=post align=center>";

			foreach ( $in as $key => $val )
			$body .= "<input type=\"hidden\" name=\"$key\" value=\"$val\">";
			$body .= "<input type=\"submit\" name=\"CREATE\" value=\"Update DB\"></form></p>";
		} else {

			if ($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] != '' && !isset($in['PROGR']) ) {
				$ret = $this->all_in_form_view ( $xml_form );
				$body .= $ret ['body'];
			} else {

				if (isset ( $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE'] ) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['VIEWABLE_ON_CLOSE'] != '') {

					if ($_GET ['VISITNUM_PROGR'] == '')
					$_GET ['VISITNUM_PROGR'] = 0;
					$sql_query = "
								select
									fine,
									userid
								from {$service}_coordinate
								where visitnum={$_GET['VISITNUM']}
								and visitnum_progr={$_GET['VISITNUM_PROGR']}
								and esam={$_GET['ESAM']}
								and progr={$_GET ['PROGR']}
								and {$this->config_service['PK_SERVICE']}={$this->pk_service}
								";
					$sql_abil = new query ( $this->conn );
					$sql_abil->get_row ( $sql_query );
					if ($sql_abil->row ['FINE'] != 1 && $sql_abil->row ['USERID'] != $this->user->userid) {
						error_page ( $this->user->userid, $this->testo ( "userNotCenter" ), "" );
					}
				}

				$xml_form->make_html ($no_link_back);

				if ($this->pk_service != '' && $this->pk_service != 'next') {
					$this->make_patient_table ();
					$body = $this->patient_table;
					$body .= "<br><br>" . $this->tb_riassuntiva ();
				} else
				$body = '';

				$body .= $xml_form->body;

				$script = "
				<script type=\"text/javascript\">
				" . $xml_form->salva_js . "
				" . $xml_form->invia_js . "
				" . $xml_form->check_js . "
				" . $xml_form->inrevisione_js . "
				</script>
				";
				$onload .= $xml_form->onload . ";";

			}
			//TODO mettere "testo" e usare una sola variabile
			if ($this->config_service ['lang'] == "en") {
				$link_equery = "Send eQuery on this form";
			} else {
				$link_equery = "Invia eQuery su questa scheda";
			}
			if ($xml_form->closed && $this->config_service ['equery'] == 'yes') {
				//modifica G.Tufano 05/07/2010
				//controllo se sono in un sottostudio o no
				$profond = $this->xmr->depth;
				$lvl_up = "";
				//depth >0 sono in un sottostudio
				if($profond > 0){
					do{
						$lvl_up .= "../";
						$profond--;
					}
					while($profond > 0);
				}

				//			link per l'equery
				$body .= "
			<br>
			<p align=right>
				<a href=\"{$lvl_up}index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&REGISTRY={$this->xmr->prefix}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&eQuery&eform&FIXED=Y\">
				$link_equery
				</a>
			</p>
			";

				$f_dir=$this->xml_dir."/documents/";
				$fmame='r_farm_pdf'.$this->session_vars['CENTER'].'_'.$this->session_vars['CODPAT'].'_'.$this->session_vars['VISITNUM'].'_'.$this->session_vars['ESAM'].'_'.$this->session_vars['PROGR'].'.pdf';
				$dir_handle = @opendir($f_dir);
				$find=0;
				while ($file = readdir($dir_handle))
				if ($file==$fmame) $find=1;
				if ($find==1)
				{

					$body.="
					<p align=right>
						<a href=\"xml/documents/$fmame\" target=new>
							Stampa richiesta farmaco
						</a>						</a>
					</p>
       ";

			 }
				$fmame='pdf'.$this->session_vars['CENTER'].'_'.$this->session_vars['CODPAT'].'_'.$this->session_vars['VISITNUM'].'_'.$this->session_vars['ESAM'].'_'.$this->session_vars['PROGR'].'.pdf';
				$dir_handle = @opendir($f_dir);
				$find=0;
				while ($file = readdir($dir_handle))
				if ($file==$fmame) $find=1;
				if ($find==1)
				{

					$body.="
					<p align=right>
						<a href=\"xml/documents/$fmame\" target=new>
							Stampa modulo di segnalazione di Sospetta Reazione Avversa (ADR)
						</a>						</a>
					</p>
       ";

			 }


			}
		}
		if ($xml_form->closed && $this->config_service['equery_objs']=='yes') {
			//global $config_service;
			$index="index.php";
			foreach ($this->equery_objs as $curr_equery_obj){
				$body .="<br>
					<p align=right>".$curr_equery_obj->link('nuovo')."</p>";
			}
		}
		$this->body = $body;
		$this->onload = $onload;
		$this->script = $script;

	}

	//TODO verificare se vale la pena rimetterla... servirebbe per i sottostudi che non abbiamo!!
	// 		function printable_form($esam, $visitnum, $visitnum_progr, $progr,$service,$vlist){
	// 		$_GET['ESAM']=$this->session_vars['ESAM']=$esam;
	// 		$_GET['VISITNUM']=$this->session_vars['VISITNUM']=$visitnum;
	// 		$_GET['VISITNUM_PROGR']=$this->session_vars['VISITNUM_PROGR']=$visitnum_progr;
	// 		$_GET['PROGR']=$this->session_vars['PROGR']=$progr;

	// 		if($service=='REUMA'){
	// 			//			$vlist= new xml_esams_list ( $this->getXMRPath("xml_dir",$this->visit_structure_xml) .'/'. $this->visit_structure_xml,$config,$this->session_vars, $this->conn);
	// 			$form=$vlist->esams[$visitnum][$esam]['XML'];

	// 			$registro="";
	// 			$titolo=strtoupper($vlist->esams[$visitnum][$esam]['TESTO']);
	// 		}
	// 		else{
	// 			//			$vlist= new xml_esams_list ( $this->getXMRPath("xml_dir",$service.'/'. $this->visit_structure_xml) . '/' .$service.'/'. $this->visit_structure_xml,$config,$this->session_vars, $this->conn);
	// 			$form=$vlist->esams[$visitnum][$esam]['XML'];
	// //			echo "<hr>".$form."<hr>";

	// 			$registro="$service related DB";
	// 			$titolo=strtoupper($vlist->esams[$visitnum][$esam]['TESTO']);

	// 		}
	// //		$form=str_replace(".xml","_pdf.xml",$form);

	// 		if($service=='')
	// 			$service=$this->service;
	// 		$xml_form = new xml_form ( $this->conn, $service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
	// 		$xml_form->xml_form_by_file ( $this->getXMRPath("xml_dir",$form) . '/' . $form );
	// 		$xml_form->make_html (true,true);
	// 		unset($_GET['ESAM']);
	// 		unset($_GET['VISITNUM']);
	// 		unset($_GET['VISITNUM_PROGR']);
	// 		unset($_GET['PROGR']);
	// 		if($titolo)$titolo="<br /><br /><b>$titolo</b>";
	// 		return "$registro $titolo<!-- BREAK PAGE -->".$xml_form->body."<!-- NEW PAGE -->";
	// 	}


	function view_all($service=null,$vlist=null){

		$ret = parent::view_all($service,$vlist);

		$this->make_patient_table();
		$this->patient_table;
		$ret = $this->patient_table.$ret;
		//OSCENITA la lascio per i posteri. è giusto che rimanga.
		// 	    $ret=preg_replace("/class=bordi1/sm", "border=1", $ret);
		return $ret;

	}

	//funzione per gestire quale sia la Homepage
	function HomePage() {
		$in = $this->session_vars;
		if (isset ( $this->workflow )) {
			$prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
			if(isset($_GET['PREFIX']) && $_GET['PREFIX']!="")
			$xml_page = "home_{$_GET['PREFIX']}.xml";
			else
			$xml_page = "home_{$prof_add}.xml";

		} else
		$xml_page = 'home.xml';
		// 		$legend_upper = "";

		if (preg_match("/\b......00.\b/", $in['remote_userid']) && $prof_add=='Data_Entry') $xml_page='home_fter.xml';
		if (preg_match("/\b......0.\b/", $in['remote_userid']) && $prof_add=='Data_Entry') $xml_page='home_far.xml';
		if (preg_match("/^994/", $in['remote_userid']) || preg_match("/^993/", $in['remote_userid'])) $xml_page='home_rep.xml';

		$body.="<!--$xml_page-->";
		$this->xml_page=$xml_page;
		$page = new xml_page ( $this->getXMRPath("xml_dir",$xml_page) . '/' . $xml_page, $this->admin_profili );
		// 		$page = new xml_page ( $this->xml_dir . '/' . $xml_page, $this->admin_profili );
		$body .= $page->page_html ();
		$body .= $this->footer;

		//Nuovo modo di generare il menu briciola di pane
		$this->percorso = $this->breadcrumb ( "home" );
		$this->body .= $this->percorso;

		$this->body .= $body;
	}
	
	
	/**
	 * 
	 * Funzione per la generazione del crf
	 */
	function pdf_print(){
		// 		global $xml_dir;

		global $inputval;
		global $body;
		global $in;
		global $service;
		global $filetxt;
		global $visit_structure_xml;

		$services[]=$this->service;
		$body.=$this->view_all_services($services);

		$body=str_replace("/Print/", '', $body);
		$body=str_replace("/CRFs/", '', $body);

		//creo un eventuale template di stampa per evitare il div "Salvataggio in corso", che da fastidio
		if (file_exists("/http/lib/XMR/v2.1/libs4bind/armonia/crfs/template_stampa.htm"))
			$filetxt = file_get_contents ( "/http/lib/XMR/v2.1/libs4bind/armonia/crf/template_stampa.htm" );

		$filetxt=preg_replace("/<!--script-->/", $script, $filetxt);

		$filetxt=preg_replace("/\/\/<!--onload-->/", $onload, $filetxt);
		$template=preg_replace("/<!--body-->/", $body, $filetxt);

		$template=preg_replace("/\/images\//", "/http/lib/XMR/v2.1/libs4bind/armonia/imgs/",$template);

		$template=preg_replace("/<br><a href=(.*?)\/a>/", "",$template);
		$template=preg_replace("/<br><!a href=(.*?)\/a>/", "",$template);
		$template=preg_replace("/<a href=(.*?)\/a>/", "",$template);
		$template=preg_replace("/<!a href=(.*?)\/a>/", "",$template);
		$template=str_replace("Print&nbsp;CRFs", "",$template);
		$template=str_replace("Contacts", "",$template);

		$f_dir=$this->getXMRPath('dir_servizio').'/crfs/';
		$fd=$this->session_vars['CODPAT'];
		$nomefile= "htm".$fd.'_'.$this->service.".htm";
		$pdffile=  "pdf".$fd.'_'.$this->service.".pdf";

		$linkfile="crfs/".$pdffile;

		$nomefile=$f_dir.$nomefile;
		$pdffile= $f_dir.$pdffile;

		$htmlf = fopen( $nomefile, "w");

		if ($htmlf) {
			fputs ($htmlf, $template);
		}
		fclose ($htmlf);

		//aggiungo il cancella file .htm
		if ($htmlf) {
			//
			//
			$rc=system('/http/local/bin/htmldoc -t pdf14  --no-title --size A4  --browserwidth 800 --footer .t. --header ... --headfootsize 8 --headfootfont Times-Italic --bottom 5mm --top 5mm --left 5mm --right 5mm --path /amministrazione/schede_utente --webpage '.$nomefile.' > '.$pdffile,$ret);
			$this->_elimina_files_e_dirs($nomefile);
			$this->_elimina_files_e_dirs($nomefile.'.bak');
		}

		$testo="
		<HTML>
<HEAD>
<TITLE></TITLE>
</HEAD>
<BODY BGCOLOR=\"#ffdddd\">
</HEAD>
<BODY>
<meta http-equiv=\"refresh\" content=\"0;URL=$linkfile\">
</BODY>
</HTML>
";


		echo $testo;
		die();
	}



	function make_patient_table(){
		global $in;
		global $remote_userid;
		global $tabella;

		$sql_eleg="select ELEG
							from ".$this->service."_DIAGNOSI
							where codpat=:codpat";
		$bind = array();
		$bind['CODPAT'] = $in['CODPAT'];

		$sql=new query($this->conn);

		$sql->exec($sql_eleg,$bind);
		$sql->get_row();
		$elegAux=$sql->row['ELEG'];
		//echo "<hr>".$elegAux."<hr>";
		if($elegAux==null){
			//consulto en coordinate
			$sql_eleg="select FINE
					from ".$this->service."_coordinate
					where codpat=:codpat and visitnum=0 and esam=1";

			$bind = array();
			$bind['CODPAT'] = $in['CODPAT'];
			$sql->exec($sql_eleg,$bind);
			$sql->get_row();
			$elegAux=$sql->row['FINE'];
			//echo "<hr>".$elegAux."<hr>";
			if($elegAux==1)
			$elegAux='00';
			else
			$elegAux='--';
		}
		else{
			if($elegAux==1)
			$elegAux='01';
		}
		//TODO mettere il binding
		$sql_query="
				select a.center,
		       a.codpat,
		       a.nome,
		       a.cognome,
		       centri.DENOM,
		       to_char(a.NASCITA_DT,'DD/MM/YYYY') NASCITA_DT,
		      to_char(c.insertdt,'DD/MM/YYYY')  as INSERTDT
		  from ".$this->service."_REGISTRAZIONE a, ".$this->service."_coordinate c, ".$this->service."_CENTRI centri
		  where c.esam=0 and c.visitnum=0 and c.codpat=a.codpat
		  and a.codpat=:codpat
		  and centri.center=a.center
		 ";

		$bind = array();
		$bind['CODPAT'] = $in['CODPAT'];
		$sql->exec($sql_query,$bind);
		$sql->get_row();
		if (preg_match("!,!",$this->centers)){
			$th_center="<td class=int>Center</td>";
			$td_center="<td>{$sql->row['CENTER']}</td>";
		}
		else {
			$th_center='';
			$td_center="";
		}
		$tabella="
		<table class='bordi1' width='50%' align='center'>
			<tr>
				
				<td class='int' width='10%'>Centro</td>
				<td class='int' width='20%'>Codice Paziente</td>
				<td class='int' width='30%'>Nome Cognome</td>
				<td class='int' width='20%'>Data di nascita</td>
				<td class='int' width='20%'>Data di reg.</td>
			</tr>
			<tr>
				
				<td class='int_pt2'>{$sql->row['CENTER']}&nbsp;</td>
				<td class='int_pt2'>{$sql->row['CODPAT']} ".$elegAux."&nbsp;</td>
		";
		if (preg_match("/^99/", $remote_userid))
		$tabella.="
				<td class='int_pt2'>***&nbsp;</td>
				<td class='int_pt2'>***&nbsp;</td>
				";
		else
		$tabella.="
				<td class='int_pt2'> {$sql->row['NOME']} {$sql->row['COGNOME']}&nbsp;</td>
				<td class='int_pt2'>{$sql->row['NASCITA_DT']}&nbsp;</td>
				";

		$tabella.="
				<td class='int_pt2'>{$sql->row['INSERTDT']}&nbsp;</td>
			</tr>
		</table>	<br>
				";
		$this->patient_table=$tabella;
	}


	//printable_form non lo sto mettendo perché mi sembra uguale uguale alla lib, a parte il fatto che gestisce i sottostudi.
	//cosa che nei registri non serve, dico male?
	/**
	*
	* Funzione per il trasferimento paziente da centro a centro
	*/
	function TrasferisciPaziente(){
		global $remote_userid;
		
		if (preg_match("/^997/", $remote_userid)){
			
			//porcata per evitare che faccia una query in open_form
			//forzo il parametro search (su esplicita richiesta di Carlo Contino)
			$this->session_vars['SEARCH']= '';
			$in=$this->session_vars;
				
			$config_service=$this->config_service;
			// 		$xml_dir=$this->xml_dir;
			$service=$this->xmr->prefix;
				
			//step 1: mostra form per trasferimento
			if ($in['TRASF_ACTION']== '1' && $in['TTRASF']==''){
				$file_form=$this->getXMRPath("xml_dir",'trasferisci_paziente.xml')."/trasferisci_paziente.xml";
					
				$xml_form=new xml_form($this->conn, $service, $config_service, $in, null);
				$xml_form->xml_form_by_file($file_form);
					
				$xml_form->open_form();
				$body.=$xml_form->body;
	
				$script = '
						<script type="text/javascript" src="libs/js/jquery/jquery-last.js"></script>
						<script type="text/javascript" src="libs/armonia/js/trasferimenti.js"></script>		
						<script type="text/javascript">	
						function cf(){
							f=document.forms[0];
							el=f.elements;
							
							//aggiungere controllo sul fatto che i centri siano diversi
							if (el["CENTRO_ORIGINE"].value != "" && el["CENTRO_DESTINAZIONE"].value != "" && el["CENTRO_ORIGINE"].value == el["CENTRO_DESTINAZIONE"].value){
								alert("Impossibile proseguire. Il centro di origine e di destinazione coincidono");
								return false;
							}
							else
								return true;						
						}
												
						function invia_f(){
						 	prepara_decode();
							if (cf() === false) return false;
							f=document.forms[0];
							el=f.elements;
							specifiche="A=ON&L=0&F=0";
							c1=""+
							"<<si###CENTRO_ORIGINE###Centro di origine>>"+
							"<<si###CODPAT###Codice paziente>>"+
							"<<si###CENTRO_DESTINAZIONE###Centro di destinazione>>"+
							"<<si###TIPO_RICHIESTA###Tipo richiesta>>"+
							"";
		  
							rc=contr(c1,specifiche);
							if (rc ) {
						   		return false;
							}
							else
						   		document.forms[0].submit();
						}
					</script>';
					
				$this->percorso = $this->breadcrumb();
				$body = $this->percorso . $body;
					
				$this->body=$body;
				$this->script=$script;
				$this->body=preg_replace("/cf\(\)/","", $this->body);
			}
			//qui arrivo dopo aver selezionato l'azione
			else if ($in['TRASF_ACTION'] && $in['TTRASF']=='1'){

			$sql=new query($this->conn);

				//controllo la coerenza delle info
				if ($in['CENTRO_ORIGINE'] == $in['CENTRO_DESTINAZIONE']){
					$this->body = "<TR><TD align=center><b><font size=\"3\">Impossibile trasferire il paziente.</font> </b><br>
											Il centro di destinazione e di origine coincidono. Tornare indietro e riprovare											
											<br>
											<br>
											<a href='index.php?TRASF_ACTION=1'><u>Indietro </u></a></TD></TR>";	
					return false;
				}
				else{
					$str="select * from {$this->service}_registrazione where {$this->config_service ['PK_SERVICE']}= :pk_service";
					
					$bind = array();
					$bind['pk_service'] = $in[$this->config_service ['PK_SERVICE']];
					
					$sql->exec($str,$bind);
					$sql->get_row();
// 					echo $sql->row['NASCPZ'];die();
					if($sql->row['NASCPZ'] != ''){
						$this->body = "<TR><TD align=center><b><font size=\"3\">Impossibile trasferire il paziente.</font> </b><br>
																	E' stato selezionato un codice paziente non valido. Tornare indietro e riprovare											
																	<br>
																	<br>
																	<a href='index.php?TRASF_ACTION=1'><u>Indietro </u></a></TD></TR>";	
						return false;
					}
					
					//completo il Binding array
					$bind['center'] = $sql->row['CENTER'];
					$bind['userid'] = $in['remote_userid'];
						
					$bind['servizio'] = $this->service;
					$bind['azione'] = 1;
					$bind['d_azione'] = 'Cancella paziente';
					$bind['motivo'] = '-3';
					$bind['d_motivo'] = 'Trasferimento';
					$bind['tipo_richiesta'] = $in['TIPO_RICHIESTA'];
					$bind['d_tipo_richiesta'] = $in['D_TIPO_RICHIESTA'];
					$bind['new_center'] = $in['CENTRO_DESTINAZIONE'];
					
					//mi calcolo il prossimo codpat (pk_service)
					$str="select {$this->config_service['PK_SEQ']}.nextval nuovo_cod from dual";
					$sql->exec($str);
					$sql->get_row();
					
					$bind['new_pk_service'] = $sql->row['NUOVO_COD'];
					
					$str="INSERT into pazienti_canc_trasf
						(ID_RIGA,SERVIZIO,OLD_{$this->config_service ['PK_SERVICE']},OLD_CENTER,USERID,AZIONE_DT,AZIONE,D_AZIONE,MOTIVO,D_MOTIVO,tipo_richiesta,d_tipo_richiesta,new_{$this->config_service ['PK_SERVICE']},new_center)
						values
						(pazienti_canc_trasf_seq.nextval,:servizio, :pk_service,:center,:userid,sysdate,:azione,:d_azione,:motivo,:d_motivo,:tipo_richiesta,:d_tipo_richiesta,:new_pk_service,:new_center)";
					
//  				echo $str.'<hr />'. print_r($bind,true);die();
					
					$sql->ins_upd($str,$bind); 
					$this->conn->commit();
					
					//prima cancello il paziente vecchio
					$err = $this->_deletePatient($bind['pk_service'],$bind['azione'],$bind['motivo'], $bind['d_motivo'], 
												$bind['tipo_richiesta'],$bind['d_tipo_richiesta'],$bind['userid'],$bind['servizio']);
				}
				if($err === true){
					//poi lo clono
					$err2 = $this->_clonePatient($bind['pk_service'],$bind['servizio'],$bind['new_pk_service'], $bind['new_center']);
					
					if($err2 ===true){
						//aggiorno le info nel vecchio paz
						//se è andato tutto ok MOSTRO IL NUOVO CODPAT
						$str="UPDATE {$this->service}_registrazione set new_codpat = :new_pk_service, new_center = :new_center where {$this->config_service ['PK_SERVICE']}= :pk_service";
						
						$sql->ins_upd($str,$bind);
						$this->conn->commit();
						
						$this->body = "<TR><TD align=center><b><font size=\"3\" style='color:red;'>Trasferimento andato a buon fine.</font></b> <br>
								<br>
								<br>
								<br>
								Paziente <b>{$bind['pk_service']}</b> centro {$bind['center']} --&gt; Paziente <b>{$bind['new_pk_service']}</b> centro {$bind['new_center']}
								<br>
								<a href='index.php'><u>Torna alla home </u></a>
								<br>
								<a href='index.php?list=patients_list.xml'><u>Torna alla lista pazienti </u></a></TD></TR>";	
					}
					else{
						$this->body = "<TR><TD align=center><b><font size=\"3\">Impossibile trasferire il paziente.</font></b> <br>
								<br>
								<br>
								<br>
								Si &egrave; verificato un problema! Prego contattare l'assistenza.
								<br>
								<br>
								<a href='index.php?TRASF_ACTION=1'><u>Indietro </u></a></TD></TR>";	
					}				
				}
				else{
					$this->body = "<TR><TD align=center><b><font size=\"3\">Impossibile cancellare il paziente.</font></b> <br>
								<br>
								<br>
								<br>
								Si &egrave; verificato un problema! Contattare l'assistenza.
								<br>
								<br>
								<a href='index.php?TRASF_ACTION=1'><u>Indietro </u></a></TD></TR>";	
				}
			}	
		}
	}
	
	
	

/**
 * 
 * Funzione cancella paziente
 */
	function CancellaPaziente(){
		global $remote_userid;

		if (preg_match("/^997/", $remote_userid)){
			
			//porcata per evitare che faccia una query in open_form
			//forzo il parametro search (su esplicita richiesta di Carlo Contino)
			$this->session_vars['SEARCH']= '';
			$in=$this->session_vars;
			
			$config_service=$this->config_service;
			// 		$xml_dir=$this->xml_dir;
			$service=$this->xmr->prefix;
			
			//step 1: mostra form per cancellazione
			if ($in['NASCPZ_ACTION']== 'edit' && $in['TNASCPZ']==''){
				$file_form=$this->getXMRPath("xml_dir",'cancella_paziente.xml')."/cancella_paziente.xml";
					
				$xml_form=new xml_form($this->conn, $service, $config_service, $in, null);
				$xml_form->xml_form_by_file($file_form);
					
				$xml_form->open_form();
				$body.=$xml_form->body;
				
				$script = '
				<script type="text/javascript">
					function cf(){
						if (document.forms[0].elements["MOTIVO"].value == -3){
							alert("Impossibile modificare lo stato di un paziente trasferito!");
							return false;
						}
						if ((document.forms[0].elements["AZIONE"].value == 1 && document.forms[0].elements["NASCPZ"].value==1) ||
							(document.forms[0].elements["AZIONE"].value == 2 && document.forms[0].elements["NASCPZ"].value=="")){
							alert("Impossibile cancellare un paziente gia\' cancellato ne\' ripristinare un paziente attivo!");
							return false;
						}
						
						
					}
					
					//nascondo la select del motivo nel caso in cui 
					function setMotivo(){
						if (document.forms[0].elements["AZIONE"].value!=1){ 
							document.forms[0].elements["MOTIVO_CANC"].disabled=true;
							document.forms[0].elements["MOTIVO_CANC"].value="";
							//document.getElementById("cell_MOTIVO_CANC").style.display="none";
							//document.getElementById("cell_input_MOTIVO_CANC").style.display="none";
						}
						else{
							document.forms[0].elements["MOTIVO_CANC"].disabled=false;
							//document.getElementById("cell_MOTIVO_CANC").style.display="";
							//document.getElementById("cell_input_MOTIVO_CANC").style.display="";
						}
					}
					
					function invia_f(){
					 	prepara_decode();
						if (cf() === false) return false;
						f=document.forms[0];
						el=f.elements;
						specifiche="A=ON&L=0&F=0";
						c1=""+
						"<<si###AZIONE###Azione>>"+
						"<<ksi###MOTIVO_CANC###v&&&AZIONE&&&=#1$$$Motivo della cancellazione>>"+
						"<<si###TIPO_RICHIESTA###Tipo richiesta>>"+
						"";
	  
						rc=contr(c1,specifiche);
						if (rc) {
					   		return false;
						}
						else
					   		document.forms[0].submit();
					}
				</script>';
					
				$this->percorso = $this->breadcrumb();
				$body = $this->percorso . $body;
					
				$this->body=$body;
				$this->script=$script;
				$this->body=preg_replace("/cf\(\)/","", $this->body);
			}
			//qui arrivo dopo aver selezionato l'azione
			else if ($in['NASCPZ_ACTION']== 'edit' && $in['TNASCPZ']=='1'){
				$sql=new query($this->conn);
				$str="select * from {$this->service}_registrazione where {$this->config_service ['PK_SERVICE']}= :pk_service";
					
				$bind = array();
				$bind['pk_service'] = $in[$this->config_service ['PK_SERVICE']];
					
				$sql->exec($str,$bind);
				$sql->get_row();
				
				//controllo la coerenza delle info
				if (
				($sql->row['NASCPZ'] == '' && $in['AZIONE'] == 2) ||
				($sql->row['NASCPZ'] == 1 && $in['AZIONE'] == 1)
				){
					$this->body = "<TR><TD align=center><b><font size=\"3\">Impossibile cancellare/ripristinare il paziente.</font> </b><br>
											<br>
											<br>
											<br>
											Si &egrave; tentato di ripristinare un paziente gi&agrave; attivo o di cancellare un paziente gi&agrave; cancellato!
											<br>
											<br>
											<a href='javascript:history.back();'><u>Indietro </u></a></TD></TR>";	
					return false;
				}
				if ($sql->row['MOTIVO'] == '-3'){
					$this->body = "<TR><TD align=center><b><font size=\"3\">Impossibile cancellare/ripristinare il paziente.</font> </b><br>
																<br>
																<br>
																<br>
																Si &egrave; tentato di modificare lo stato di un paziente trasferito!
																Il paziente in questione &egrave; stato trasferito al centro {$sql->row['NEW_CENTER']}
																con codice {$sql->row['NEW_CODPAT']}
																<br>
																<br>
																<a href='javascript:history.back();'><u>Indietro </u></a></TD></TR>";	
					return false;
				}
				
					
					$str="INSERT into pazienti_canc_trasf
										(ID_RIGA,SERVIZIO,OLD_{$this->config_service ['PK_SERVICE']},OLD_CENTER,USERID,AZIONE_DT,AZIONE,D_AZIONE,MOTIVO,D_MOTIVO,tipo_richiesta,d_tipo_richiesta)
										values
										(pazienti_canc_trasf_seq.nextval,:servizio, :pk_service,:center,:userid,sysdate,:azione,:d_azione,:motivo,:d_motivo,:tipo_richiesta,:d_tipo_richiesta)";
					
					//completo il Binding array
					$bind['center'] = $sql->row['CENTER'];
					$bind['userid'] = $in['remote_userid'];
					
					$bind['servizio'] = $this->service;
					$bind['azione'] = $in['AZIONE'];
					$bind['d_azione'] = $in['D_AZIONE'];
					$bind['motivo'] = $in['MOTIVO_CANC'];
					$bind['d_motivo'] = $in['D_MOTIVO_CANC'];
					$bind['tipo_richiesta'] = $in['TIPO_RICHIESTA'];
					$bind['d_tipo_richiesta'] = $in['D_TIPO_RICHIESTA'];
					
					//  				echo $str.'<hr />'. print_r($bind,true);
					
					$sql->ins_upd($str,$bind);
					$this->conn->commit();
					$err = $this->_deletePatient($bind['pk_service'],$bind['azione'],$bind['motivo'], $bind['d_motivo'], 
												$bind['tipo_richiesta'],$bind['d_tipo_richiesta'],$bind['userid'],$bind['servizio']);
				
				if($err === true){
					//pulisco il buffer
					ob_clean();
					//re-indirizzo sulla vista paziente
					header("Location: index.php?list=patients_list.xml&CENTER={$in['CENTER']}");
					die();
				}
				else{
					$this->body = "<TR><TD align=center><b><font size=\"3\">Impossibile cancellare il paziente.</font></b> <br>
								<br>
								<br>
								<br>
								Si &egrave; verificato un problema! Contattare l'assistenza.
								<br>
								<br>
								<a href='javascript:history.back();'><u>Indietro </u></a></TD></TR>";	
				}
					
					
			}
		}
		
	}
	
	/**
	 * Funzione che si occupa operativamente di cancellare  pazienti
	 * 
	 * PARAM
	 * pk_service: codpat o similari
	 * azione: 1=cancella, 2=ripristina
	 * d_azione: decode
	 * motivo_canc: motivo della cancellazione
	 * d_motivo_canc: decode
	 * tipo_richiesta: da dove deriva la richiesta (WCA, Helpdesk, equery)
	 * d_tipo_richiesta: decode
	 * remote_userid: auto-esplicativo direi
	 * servizio: prefisso da usare per le tabelle
	 */
	private function _deletePatient($pk_service,$azione,$motivo_canc,$d_motivo_canc,$tipo_richiesta,$d_tipo_richiesta,$remote_userid,$servizio ){
		$sql=new query($this->conn);
		
			//se mi sembra ok...
			//1) insert dentro il LOG
				
			//2) aggiorno la tabella registrazione
			$str="UPDATE {$servizio}_registrazione SET nascpz= :nascpz, motivo=:motivo, d_motivo= :d_motivo
				where {$this->config_service ['PK_SERVICE']}= :pk_service";
	
			$bind = array();
			$bind['pk_service'] = $pk_service;
			$bind['motivo'] = $motivo_canc;
			$bind['d_motivo'] = $d_motivo_canc;
			//azione = 1 allora NASCPZ = 1 cioè cancellato
			//azione = 2 allora NASCPZ = null.
			$bind['nascpz'] = ($azione==1)?1:'';
			$sql->ins_upd($str,$bind);
			$this->conn->commit();

		return true;
	}
	
	/**
	* Funzione che si occupa di clonare un paziente
	*
	* PARAM
	* pk_service: codpat o similari
	* servizio: prefisso da usare per le tabelle
	*/
	private function _clonePatient($pk_service,$servizio,$new_pk_service, $new_center){
		$sql=new query($this->conn);
		
		$bind = array();
		$bind['pk_service'] = $pk_service;
		$bind['new_pk_service'] = $new_pk_service;
		$bind['new_center'] = $new_center;
		$bind['new_nascpz'] = '';
		
		//4) Ora mi occupo di selezionare tutte le tabelle, prendendo da tutte le schede
		$tables = array();
				
		foreach($this->vlist_root->xml as $esame){
			$reg_form = new xml_form ( $this->conn, $this->xmr_root->prefix );
			$reg_form->xml_form_by_file ( $this->getXMRPath("xml_dir",$esame) . "/" . $esame );
			$tables[] = $reg_form->form ['TABLE'];
			$err = $this->_backupPatient($pk_service, $reg_form->form ['TABLE'], $servizio);
			if ($err === false){
				$this->body = "<TR><TD align=center><b><font size=\"3\">
									Impossibile salvare lo storico del paziente in tabella {$reg_form->form ['TABLE']}.</font></b> <br>
									<br>
									<br></TD></TR>";	
				return false;
			}
		}
		array_unshift($tables,$servizio.'_COORDINATE',$servizio.'_EQUERY');
			
		foreach($tables as $table){
			//elenco completo delle colonne con pk all'inizio
			$cols_arr = $this->_getColumnsTable($table);
			$cols_new_arr = $cols_arr;
			
			$cols_new_arr[$this->config_service['PK_SERVICE']] = ':new_pk_service';
			
			//sistemo i campi che non voglio vengano compilati
			if (array_key_exists('CENTER',$cols_new_arr)){
				$cols_new_arr['CENTER'] = ':new_center';
			}
			if (array_key_exists('NASCPZ',$cols_new_arr)){
				$cols_new_arr['NASCPZ'] =':new_nascpz';
			}
			if (array_key_exists('MOTIVO',$cols_new_arr)){
				$cols_new_arr['MOTIVO'] ='null';
			}
			if (array_key_exists('NEW_CODPAT',$cols_new_arr)){
				$cols_new_arr['NEW_CODPAT'] ='null';
			}
			if (array_key_exists('NEW_CENTER',$cols_new_arr)){
				$cols_new_arr['NEW_CENTER'] ='null';
			}
			if (array_key_exists('D_MOTIVO',$cols_new_arr)){
				$cols_new_arr['D_MOTIVO'] ='null';
			}

			$cols = implode(',',$cols_arr);
			$cols_new = implode(',',$cols_new_arr);
			
			$str2="INSERT into $table
								($cols)
									(SELECT $cols_new from $table
									where {$this->config_service ['PK_SERVICE']} =:pk_service)
							";
//  			echo $str2.'<hr />';
			$sql->ins_upd($str2,$bind);
 			$this->conn->commit();
		}
// print_r($bind);die();
		return true;
	}
	
	/**
	 * Funzione per salvare nello storico i dati relativi ad un paziente
	 * 
	 * PARAM:
	 * pk_service: ciò che viene prosaicamente dichiarato "codpat"
	 * table: la tabella da cui prendere i dati da salvare nello storico
	 */
	private function _backupPatient($pk_service, $table,$servizio){
		$sql=new query($this->conn);
		
		$query ="INSERT INTO S_{$table}
		SELECT
  'CINECA',
  sysdate,
  nvl(
  (
    SELECT
      MIN(MODPROG)
    FROM
      S_{$table}
  ) -a.cont,-1) modprog,
  'V',
  -1 id_query,
  R.*
FROM
  {$table} R,
  (
    SELECT
      ROW_NUMBER() OVER (ORDER BY {$this->config_service ['PK_SERVICE']} ASC) AS CONT,
      {$this->config_service ['PK_SERVICE']}
    FROM
      {$table} R
    WHERE
      {$this->config_service ['PK_SERVICE']} = :pk_service
  )
  a
WHERE
  r.{$this->config_service ['PK_SERVICE']}   = a.{$this->config_service ['PK_SERVICE']}
AND r.{$this->config_service ['PK_SERVICE']} = :pk_service
		";
		$bind= array();
		$bind['pk_service'] = $pk_service;
// 		echo $query.print_r($bind,true);die();
		$sql->ins_upd($str,$bind);
		$this->conn->commit();
	}

	/**
	 * Funzione che restituisce tutte le colonne di una data colonna
	 * 
	 * @param $table = il nome della tabella
	 * @param $reorder_pk = se true aggiunge la PK in cima all'array per averla in posizione 0
	 * @return array con l'elenco delle colonne
	 */
	private function _getColumnsTable($table){
		$sql=new query($this->conn);
		
		//eseguo la select per prendere tutte le colonne TRANNE la PK_SERVICE
		$query = "SELECT column_name from user_tab_columns WHERE upper(table_name) = :tabella";
		$bind= array();
		$bind['tabella'] = $table;
		$bind['pk_service_col'] = $this->config_service['PK_SERVICE'];
		
		$sql->exec($query,$bind);
// 		echo print_r($sql->res['COLUMN_NAME'],true).'<hr />'.print_r($bind,true). '<hr />'.$query;die();
		$cols = array();
		foreach($sql->res['COLUMN_NAME'] as $colonna)
			$cols[$colonna] = $colonna;

		return $cols;
	}
	
	
	/**
	* Gestisce la pagine dei listati
	*
	* @param String $percorso_base
	*/
	function ListPage($percorso_base = null) {
		//modifica effettutata da G.Tufano
		//il 26/05/2011. Ora per vedere un pager è sufficiente settare la variabile RPP nel config.inc locale
		//per es: $config_service['RPP'] = 25;
		if (isset($this->config_service['RPP']) && $this->config_service['RPP']  != ''){
			$RPP = $this->config_service['RPP'];
			if($_GET['PAGE']=="")
			$page=1;
			else
			$page=$_GET['PAGE'];
				
			$str="select count(*) conto from {$this->service}_utenti_centri where userid='{$this->user->userid}'";
			$sql=new query($this->conn);
			$sql->get_row($str);

			$list=str_replace ( ".xml", "_center.xml", $_GET['list'] );
			
			if($sql->row['CONTO']>1 && $this->session_vars['CENTER']==''){
				
				if(file_exists($this->getXMRPath("xml_dir",$list)."/".$list))
					$_GET['list']=$list;
				$page = "";
				unset($this->config_service['RPP']);
			}
		}
	
		$list = $_GET ['list'];
		if ($list == ''){
			$list = 'patients_list.xml';
		}
		if (isset ( $this->workflow ) && $list == 'patients_list.xml') {
			$prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
			$list = str_replace ( ".xml", "_{$prof_add}.xml", $list );
		}
		
		$list_o = new xml_list ( $this->getXMRPath("xml_dir",$list)."/".$list, $page,$RPP, null, null, $this->session_vars, $this->visit_structure );
	
		//viene chiamato patients_list solo in caso sia davvero patients_list. se no altra_list
		if ($list == 'patients_list.xml') {
			$this->percorso = $this->breadcrumb ( "patients_list" );
		}
		else{
			$titolo = $list_o->list['TITOLO'];
			$this->percorso = $this->breadcrumb ( "altra_list",$titolo );
		}
			
		$this->body .= $this->percorso;
	
		$this->body .= $list_o->list_html ( $this->session_vars );
		$legend = new legend ( $this->config_service );
		$this->body .= $legend->html_legend_lista;
	}
	
	

	/**
	 * 
	 * Funzione cerca paziente/dispensazione/... tutto
	 */
	function SearchPage(){
		global $remote_userid;
		global $in;
		$dir=$_SERVER['PATH_TRANSLATED'];

		$dir=preg_replace("/\/index.php/", "", $dir);
		//$filetxt = file_get_contents($dir.'/template.htm');
		if($this->session_vars['SEARCH']==1)
		{
			if($this->session_vars['FORM']==1)
			{
				$file_form=$this->getXMRPath("xml_dir","search_paziente.xml")."/search_paziente.xml";
		  if (preg_match("/^99/", $remote_userid))
		  $file_form=$this->getXMRPath("xml_dir","search_paziente_dm.xml")."/search_paziente_dm.xml";
			} else
			if($this->session_vars['FORM']==2)
			$file_form=$this->getXMRPath("xml_dir","search_paziente_2.xml")."/search_paziente_2.xml";
			$xml_form=new xml_form();

			$xml_form->xml_form_by_file($file_form);

			$xml_form->config_service['field_lib']= $this->field_lib;
			//		echo $xml_form->config_service['field_lib'];die();

			$xml_form->open_form();
			$body.=$xml_form->body;
			//			print_r($this->session_vars);

			$in=$this->session_vars;
			$in['list']=$list="patients_list_search.xml";
			$list_o=new xml_list($this->getXMRPath("xml_dir",$list)."/".$list);
			if (isset($this->session_vars['TSEARCH']))
			$body.=$list_o->list_html();
			$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
			$script="<script type=\"text/javascript\">
		  function invia_f()
		  {
		   f=document.forms[0];
		   el=f.elements;
		   if(f.CODPAT && !IsNumeric(f.CODPAT.value)) {
		   		alert(\"Patient code must be numeric\");
		   		f.CODPAT.focus();
		   		f.CODPAT.value='';
		   		return false;
		   	}
		   specifiche='A=ON&L=1&F=0';
		   c1=''+
		   '<<fd00###NASCITA_DT###Data di nascita>>'+
		   '';

		   rc=contr(c1,specifiche);
		   if (rc) {return false}";
			//i 99* non vedono il campo cognome né nome
			if (!preg_match("/^99/", $remote_userid)){
				$script .="f.S_COGNOME.value=f.S_COGNOME.value.toUpperCase();
       f.S_NOME.value=f.S_NOME.value.toUpperCase();";
			}
			$script .="
		   document.forms[0].TSEARCH.value='1';
		   document.forms[0].action='index.php';
		   document.forms[0].submit();
		   }
		 </script>
		  ";
			$codice_sis=$remote_userid-0;
			$user_name="<p align=right>
	<br><br><br>";
			//echo "<hr>$nome_user";
			$nome_user=str_replace("\\'","'",$nome_user);
			/*if(preg_match("/^50/",$in['remote_userid']))$area_collab="|&nbsp;&nbsp;<a href=\"/WCA/index.php\">Area collaborativa</a>&nbsp;&nbsp;";
			 elseif(preg_match("/^999/",$in['remote_userid']))$area_collab="|&nbsp;&nbsp;<a href=\"/WCA/index.php\">Area collaborativa</a>&nbsp;&nbsp;";
			if(!preg_match("/^600/",$in['remote_userid']))$area_clinica="|&nbsp;&nbsp;<a href=\"index.php\">Area Clinica</a>&nbsp;&nbsp;";
			if(!preg_match("/^999/",$in['remote_userid']))$area_spedizioni="|&nbsp;&nbsp;<a href=\"/spedizioni/index.php\">Area Spedizioni</a>&nbsp;&nbsp;";
			else $area_spedizioni="|&nbsp;&nbsp;<a href=\"/sae/index.php\">Area Analisi Eventi Avversi</a>&nbsp;&nbsp;";
			$filetxt=preg_replace("/<!--nav-bar-->/", "$area_collab&nbsp;&nbsp;$area_clinica&nbsp;&nbsp;$area_spedizioni&nbsp;&nbsp;|&nbsp;", $filetxt);

			$filetxt=preg_replace("/<!--user_name-->/", $nome_user, $filetxt);
			$filetxt=preg_replace("/<!--utente-->/", $user_name, $filetxt);
			$filetxt=preg_replace("/<!--script-->/", $script, $filetxt);
			$filetxt=preg_replace("/cf\(\)/","", $filetxt);
			echo $filetxt;*/

			 
			$this->percorso = $this->breadcrumb("search");
			$body = $this->percorso . $body;

			$this->body=$body;
			$this->script=$script;
		}
		if (isset($this->session_vars['SEARCH']) && $this->session_vars['SEARCH']=="2" )
		{
			$file_form=$this->getXMRPath("xml_dir","disp_search.xml")."/disp_search.xml";
			$xml_form=new xml_form();
			$xml_form->config_service['field_lib']= $this->field_lib;

			$xml_form->xml_form_by_file($file_form);
			$xml_form->open_form();
			$body.=$xml_form->body;

			if (isset($this->session_vars['TSEARCH']))
			{
				$sql="SELECT CODPAT, CENTER, PROGR from ".$this->service."_RICH_FARMACO where
				NPROG_RIC=:nprogr_ric";
				$bind = array();
				$bind['NPROGR_RIC'] = $this->session_vars['NPROG_RIC'];
				$query=new query($this->conn);

				$query->exec($sql,$bind);
				$query->get_row();
				if ($query->numrows==0)
				{
					$body.="
   <br><br><br><br><br><br><center>
   <p class=\"sc4bis\"><b>Il Codice Identificativo Unico della richiesta farmaco non &egrave; corretto.</b></p>
   <br><br><br>
	 <a href=\"index.php\">Home Page</a><br/>
	 <a href=\"javascript:history.back();\">Indietro</a><br><br><br>
   ";
				}

				//se trovo, ma ha FINE = 1, allora già inviata
				else
				{
					$link="index.php?CENTER=".$query->row['CENTER']."&CODPAT=".$query->row['CODPAT']."&VISITNUM=1&ESAM=3&PROGR=".$query->row['PROGR']."&form=dispensazione.xml";
					die("<html><head><meta http-equiv=\"refresh\" content=\"0; url=$link\"></head></html>");
				}
			}

			//			$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
			$script="<script type=\"text/javascript\">
  function invia_f()
  {
   f=document.forms[0];
   el=f.elements;
   specifiche='A=ON&L=0&F=0';
   c1=''+
   '<<xp00###NPROG_RIC###Codice Identificativo Unico della Richiesta Farmaco>>'+
   '';
  
   rc=contr(c1,specifiche);
   if (rc) {return false}
   document.forms[0].TSEARCH.value='1';
   document.forms[0].action='index.php'; 
   document.forms[0].submit();
   }
 </script>
  ";
			$this->body=$body;
			$this->script=$script;
		}
		if (isset($this->session_vars['SEARCH']) && $this->session_vars['SEARCH']=="3" ){
				
			$this->session_vars['USERID']=$this->session_vars['remote_userid'];
			$list="disp_list_search.xml";
			$in = $this->session_vars;
			$list_o=new xml_list($this->getXMRPath("xml_dir",$list)."/".$list);
			$body.=$list_o->list_html();
			$body.="<br><br><br><br><a href=\"/".strtolower ($this->service)."/index.php\">Home Page</a>";
			$this->body=$body;
			$this->script=$script;

		}
		if (isset($this->session_vars['SEARCH']) && $this->session_vars['SEARCH']=="4" )
		{
			global $in;
			// 			echo "<hr>hola mundo";die();
				
			$file_form=$this->getXMRPath("xml_dir","search_equery.xml")."/search_equery.xml";
			//echo "<hr>".strlen($remote_userid);


			if (strlen($remote_userid)>9)
			$file_form=$this->getXMRPath("xml_dir","search_equery_center.xml")."/search_equery_center.xml";


			if (preg_match("/\b......0.\b/", $remote_userid)||preg_match("/\b......00.\b/", $remote_userid)){
				$file_form=$this->getXMRPath("xml_dir","search_equery_farma.xml")."/search_equery_farma.xml";

				//echo "<hr>{$remote_userid}";
			}
			if (preg_match("/^99/", $remote_userid))  //997??? o 99???
			$file_form=$this->getXMRPath("xml_dir","search_equery.xml")."/search_equery.xml";

			$xml_form=new xml_form();
			$xml_form->xml_form_by_file($file_form);
			$xml_form->config_service['field_lib']= $this->field_lib;
			$xml_form->open_form();
			$body.=$xml_form->body;
			$in=$this->session_vars;
				
			if (preg_match("/\b......0.\b/", $remote_userid)||preg_match("/\b......00.\b/", $remote_userid))
			$in['list']=$list="equery_search_farma.xml";
				
			if (preg_match("/^99/", $remote_userid))
			$in['list']=$list="equery_search.xml";

			if (strlen($remote_userid)>9)  //997??? o 99???
			$in['list']=$list="equery_search_center.xml";

			$list_o=new xml_list($this->getXMRPath("xml_dir",$list)."/".$list);
			if (isset($this->session_vars['TSEARCH']))
			$body.=$list_o->list_html();
			$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
			$script="<script type=\"text/javascript\">
		  	function invia_f()
		  	{
		   	f=document.forms[0];
		   	el=f.elements;
		   	if(f.CODPAT && !IsNumeric(f.CODPAT.value)) {
		   			alert(\"Patient code must be numeric\");
		   			f.CODPAT.focus();
		   			f.CODPAT.value='';
		   			return false;
		   		}
		   	if(f.ID && !IsNumeric(f.ID.value)) {
		   			alert(\"Patient code must be numeric\");
		   			f.ID.focus();
		   			f.ID.value='';
		   			return false;
		   		}
		   	specifiche='A=ON&L=1&F=0';

		   	document.forms[0].TSEARCH.value='1';
		   	document.forms[0].action='index.php';
		   	document.forms[0].submit();
		   	}
		 	</script>
			  ";
			$codice_sis=$remote_userid-0;
			$user_name="<p align=right>
		<br><br><br>";
			$nome_user=str_replace("\\'","'",$nome_user);
			$this->percorso = $this->breadcrumb("search");
			$body = $this->percorso . $body;
			$this->body=$body;
			$this->script=$script;
		}
			


	}



	function Equery() {
		$in = $this->session_vars;
		$service = $this->service;
		$remote_userid = $in ['remote_userid'];
		//		if(isset($this->config_service['patients_list_substudy']) && $this->config_service['patients_list_substudy'] != ""){
		//			$destination_url="../index.php";
		//			$link_list="<a href=\"../index.php?=&list=patients_list.xml\">{$this->config_service['Patients_list']}</a>&gt;&gt;<b>{$this->config_service['patients_list_substudy']}</b>";
		//		}else{
		//			$destination_url="index.php";
		//			$link_list="<b>{$this->config_service['Patients_list']}</b>";
		//		}

		$percorso="<a href=\"index.php\">Home Page</a>&gt;&gt;";


		if (! isset ( $in ['eform'] )) {
				
			$percorso.="<b>Lista eQuery</b>";
				
			//EQUERY CHIUSE
			if (isset ( $in ['closed'] )) {

				$open = false;
				if (preg_match ( "/^997/", $in ['remote_userid'] )) {
					$sql_rec = "
					select e.ID,
						 e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.CODPAT,
			       e.CENTER CENTER,
			       e.TIPO_EQUERY,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.VAL_USERID,
			       E.QUEST_DT,
			      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
			       E.CHIUSA_DT
			  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			  where e.q_userid not like '997%'
			   and e.chiusa=1
			   and c.center = e.CENTER
			   and uc.center = c.center
			   and uc.userid = '{$remote_userid}'
			   and e.CENTER={$in['CENTER']}
			   order by  e.CENTER,e.TIPO_EQUERY,e.ID
					";
					$sql_sent = "
					select e.ID,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.CODPAT,
			       e.CENTER CENTER,
			       e.TIPO_EQUERY,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.VAL_USERID,
			       E.QUEST_DT,
			       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
			       E.CHIUSA_DT
			  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			  where e.q_userid like '997%'
			   and e.chiusa=1
			   and c.center=e.center
			   and uc.center = c.center
			   and uc.userid = '{$in['remote_userid']}'
			   and e.CENTER={$in['CENTER']}
			   order by  e.CENTER,e.TIPO_EQUERY,e.ID
					";

				}
				else{
					if(preg_match ( "/\b......0.\b/", $in ['remote_userid'] )){

						$sql_rec = "
								 select DISTINCT e.ID,
								 e.REGISTRY,
					       e.ESAM,
					       e.VISITNUM,
					       e.VISITNUM_PROGR,
					       e.PROGR,
					       e.CODPAT,
					       e.CENTER CENTER,
					       e.TIPO_EQUERY,
					       C.DENOM,
					       E.CHIUSA,
					       E.CHIUSA_DT,
					       E.TO_BE_VALIDATE,
					       E.VALIDATA,
					       E.VAL_DT,
					       E.VAL_USERID,
					       E.QUEST_DT,
					      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
					       E.CHIUSA_DT
					  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
					  where e.q_userid like '997%'
					   and e.ANSWER is not null
					   and c.center  = e.CENTER
					   and uc.center = c.center
					   and e.CENTER={$in['CENTER']}
					   order by  e.CENTER,e.TIPO_EQUERY,e.ID
							";
						$sql_sent = "
							select DISTINCT e.ID,
					       e.ESAM,
					       e.VISITNUM,
					       e.VISITNUM_PROGR,
					       e.PROGR,
					       e.CODPAT,
					       e.CENTER CENTER,
					       e.TIPO_EQUERY,
					       C.DENOM,
					       E.CHIUSA,
					       E.CHIUSA_DT,
					       E.TO_BE_VALIDATE,
					       E.VALIDATA,
					       E.VAL_DT,
					       E.VAL_USERID,
					       E.QUEST_DT,
					       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
					       E.CHIUSA_DT
					  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
					  where 
					   e.ANSWER is not null
					   and c.center  = e.CENTER
					   and uc.center = c.center
					   and e.CENTER={$in['CENTER']}
					   order by  e.CENTER,e.TIPO_EQUERY,e.ID
							";
							
					}
					else{ if(preg_match ( "/\b......00.\b/", $in ['remote_userid'] )){
							
						$sql_rec = "
												 select DISTINCT e.ID,
												 e.REGISTRY,
									       e.ESAM,
									       e.VISITNUM,
									       e.VISITNUM_PROGR,
									       e.PROGR,
									       e.CODPAT,
									       e.CENTER CENTER,
									       e.TIPO_EQUERY,
									       C.DENOM,
									       E.CHIUSA,
									       E.CHIUSA_DT,
									       E.TO_BE_VALIDATE,
									       E.VALIDATA,
									       E.VAL_DT,
									       E.VAL_USERID,
									       E.QUEST_DT,
									      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
									       E.CHIUSA_DT
									  from {$service}_equery e, {$service}_centri c
									  where e.q_userid like '997%'
					   and e.ANSWER is not null
									   and e.CENTER = c.center 
									   and e.esam = 3
									   and e.CENTER={$in['CENTER']}
									   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									   
											";
						$sql_sent = "
											select DISTINCT e.ID,
									       e.ESAM,
									       e.VISITNUM,
									       e.VISITNUM_PROGR,
									       e.PROGR,
									       e.CODPAT,
									       e.CENTER CENTER,
									       e.TIPO_EQUERY,
									       C.DENOM,
									       E.CHIUSA,
									       E.CHIUSA_DT,
									       E.TO_BE_VALIDATE,
									       E.VALIDATA,
									       E.VAL_DT,
									       E.VAL_USERID,
									       E.QUEST_DT,
									      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
									       E.CHIUSA_DT
									  from {$service}_equery e, {$service}_centri c
									  where e.q_userid like '{$remote_userid}%'
					   and e.ANSWER is not null
									   and e.CENTER = c.center 
									   and e.esam = 3
									   and e.CENTER={$in['CENTER']}
									   order by  e.CENTER,e.TIPO_EQUERY,e.ID
											";
							
					}
					else{
							
						$sql_rec = "
										 select e.ID,
										 e.REGISTRY,
							       e.ESAM,
							       e.VISITNUM,
							       e.VISITNUM_PROGR,
							       e.PROGR,
							       e.CODPAT,
							       e.CENTER CENTER,
							       e.TIPO_EQUERY,
							       C.DENOM,
							       E.CHIUSA,
							       E.CHIUSA_DT,
							       E.TO_BE_VALIDATE,
							       E.VALIDATA,
							       E.VAL_DT,
							       E.VAL_USERID,
							       E.QUEST_DT,
							      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
							       E.CHIUSA_DT
							  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
							  where e.q_userid like '997%'
					   and e.ANSWER is not null
							   and c.center  = e.CENTER
							   and uc.center = c.center
							   and uc.userid = '{$remote_userid}'
							   and e.CENTER={$in['CENTER']}
							   and e.esam<>3
							   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									";
						$sql_sent = "
									select e.ID,
							       e.ESAM,
							       e.VISITNUM,
							       e.VISITNUM_PROGR,
							       e.PROGR,
							       e.CODPAT,
							       e.CENTER CENTER,
							       e.TIPO_EQUERY,
							       C.DENOM,
							       E.CHIUSA,
							       E.CHIUSA_DT,
							       E.TO_BE_VALIDATE,
							       E.VALIDATA,
							       E.VAL_DT,
							       E.VAL_USERID,
							       E.QUEST_DT,
							       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
							       E.CHIUSA_DT
							  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
							  where e.q_userid not like '997%'
					   and e.ANSWER is not null
							   and c.center  = e.CENTER
							   and uc.center = c.center
							   and uc.userid = '{$in['remote_userid']}'
							   and e.CENTER={$in['CENTER']}
							   and e.esam<>3
							   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									";
					}
						
					}

				}
				if(preg_match ( "/^997/", $in ['remote_userid'] )){
					$html .= "<p align=center><b>" . $this->testo ( 'closedEqL' ) . "</b></p>
											<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
											-- <a href=\"index.php?list=equery_closed.xml\">" . $this->testo ( "closedEq" ) . "
											--<a href=\"index.php?list=equery.xml\">" . $this->testo ( "allEq" ) . "
											-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
											";
				}
				else
				if(preg_match ( "/\b......0.\b/", $in ['remote_userid'] )){
						
					$html .= "
						<p align=center><b>" . $this->testo ( "closedEqL" ) . "</b></p>
							<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
							-- <a href=\"index.php?list=equery_closed_ospe.xml\">" . $this->testo ( "closedEq" ) . "
							--<a href=\"index.php?list=equery_ospe.xml\">" . $this->testo ( "allEq" ) . "
							-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
						";
						
				}
				else{  	if(preg_match ( "/\b......00.\b/", $in ['remote_userid'] )){
						
					$html .= "
									<p align=center><b>" . $this->testo ( "closedEqL" ) . "</b></p>
										<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
										-- <a href=\"index.php?list=equery_closed_terr.xml\">" . $this->testo ( "closedEq" ) . "
										--<a href=\"index.php?list=equery_terr.xml\">" . $this->testo ( "allEq" ) . "
										-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
									";

				}
				else{
					$html .= "<p align=center><b>" . $this->testo ( 'closedEqL' ) . "</b></p>
											<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
											-- <a href=\"index.php?list=equery_closed.xml\">" . $this->testo ( "closedEq" ) . "
											--<a href=\"index.php?list=equery.xml\">" . $this->testo ( "allEq" ) . "
											-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
											";
				}





				}
			}
			else
			//TUTTE LE EQUERY
			if (isset($in['all'])){
				$open=false;
				if(preg_match ( "/^997/", $in ['remote_userid'] )){
					$sql_rec = "
				select e.ID,
					e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.CODPAT,
			       e.CENTER CENTER,
			       e.TIPO_EQUERY,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.VAL_USERID,
			       E.QUEST_DT,
			      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
			       E.CHIUSA_DT
			  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			 where e.q_userid <> '{$remote_userid}'
			   and c.center  = e.CENTER
			   and uc.center = c.center
			   and uc.userid = '{$remote_userid}'
			   and e.CENTER={$in['CENTER']}
			   order by  e.CENTER,e.TIPO_EQUERY,e.ID
					";

					$sql_sent = "
				select e.ID,
				e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.CODPAT,
			       e.CENTER CENTER,
			       e.TIPO_EQUERY,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.VAL_USERID,
			       E.QUEST_DT,
			       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
			       E.CHIUSA_DT
			  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			 where e.q_userid = '{$in['remote_userid']}'
			   and c.center  = e.CENTER
			   and uc.center = c.center
			   and uc.userid = '{$in['remote_userid']}'
			   and e.CENTER={$in['CENTER']}
			   order by  e.CENTER,e.TIPO_EQUERY,e.ID
					";		
				}
				else
				if(preg_match ( "/\b......00.\b/", $in ['remote_userid'] )){
					$sql_rec = "
											 select DISTINCT e.ID,
												 e.REGISTRY,
									       e.ESAM,
									       e.VISITNUM,
									       e.VISITNUM_PROGR,
									       e.PROGR,
									       e.CODPAT,
									       e.CENTER CENTER,
									       e.TIPO_EQUERY,
									       C.DENOM,
									       E.CHIUSA,
									       E.CHIUSA_DT,
									       E.TO_BE_VALIDATE,
									       E.VALIDATA,
									       E.VAL_DT,
									       E.VAL_USERID,
									       E.QUEST_DT,
									      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
									       E.CHIUSA_DT
									  from {$service}_equery e, {$service}_centri c
									  where e.q_userid like '997%'
									   and e.CENTER = c.center 
									   and e.esam = 3
									   and e.CENTER={$in['CENTER']}
									   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									   
											";
					$sql_sent = "
											select DISTINCT e.ID,
									       e.ESAM,
									       e.VISITNUM,
									       e.VISITNUM_PROGR,
									       e.PROGR,
									       e.CODPAT,
									       e.CENTER CENTER,
									       e.TIPO_EQUERY,
									       C.DENOM,
									       E.CHIUSA,
									       E.CHIUSA_DT,
									       E.TO_BE_VALIDATE,
									       E.VALIDATA,
									       E.VAL_DT,
									       E.VAL_USERID,
									       E.QUEST_DT,
									       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
									       E.CHIUSA_DT
									  from {$service}_equery e, {$service}_centri c
									  where e.q_userid like '{$remote_userid}%'
									   and e.CENTER = c.center 
									   and e.esam = 3
									   and e.CENTER={$in['CENTER']}
									   order by  e.CENTER,e.TIPO_EQUERY,e.ID
											";
						
				}
				else
				if(preg_match ( "/\b......0.\b/", $in ['remote_userid'] )){
					$sql_rec = "
								 select DISTINCT e.ID,
								 e.REGISTRY,
					       e.ESAM,
					       e.VISITNUM,
					       e.VISITNUM_PROGR,
					       e.PROGR,
					       e.CODPAT,
					       e.CENTER CENTER,
					       e.TIPO_EQUERY,
					       C.DENOM,
					       E.CHIUSA,
					       E.CHIUSA_DT,
					       E.TO_BE_VALIDATE,
					       E.VALIDATA,
					       E.VAL_DT,
					       E.VAL_USERID,
					       E.QUEST_DT,
					      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
					       E.CHIUSA_DT
					  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
					  where e.q_userid like '997%'
					   and c.center  = e.CENTER
					   and uc.center = c.center
					   and uc.center in (select substr(userid,0,12) 
																from ana_utenti_1 a
																where a.farma = '{$remote_userid}'
																)
					   and e.CENTER={$in['CENTER']}
					   order by  e.CENTER,e.TIPO_EQUERY,e.ID
							";
					$sql_sent = "
							select DISTINCT e.ID,
					       e.ESAM,
					       e.VISITNUM,
					       e.VISITNUM_PROGR,
					       e.PROGR,
					       e.CODPAT,
					       e.CENTER CENTER,
					       e.TIPO_EQUERY,
					       C.DENOM,
					       E.CHIUSA,
					       E.CHIUSA_DT,
					       E.TO_BE_VALIDATE,
					       E.VALIDATA,
					       E.VAL_DT,
					       E.VAL_USERID,
					       E.QUEST_DT,
					      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
					       E.CHIUSA_DT
					  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
					  where 
					   c.center  = e.CENTER
					   and uc.center = c.center
					   and e.CENTER={$in['CENTER']}
					   order by  e.CENTER,e.TIPO_EQUERY,e.ID
							";
						
				}
				else{
					$sql_rec = "
								select e.ID,
									e.REGISTRY,
							       e.ESAM,
							       e.VISITNUM,
							       e.VISITNUM_PROGR,
							       e.PROGR,
							       e.CODPAT,
							       e.CENTER,
							       e.TIPO_EQUERY,
							       C.DENOM,
							       E.CHIUSA,
							       E.CHIUSA_DT,
							       E.TO_BE_VALIDATE,
							       E.VALIDATA,
							       E.VAL_DT,
							       E.VAL_USERID,
							       E.QUEST_DT,
							      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
							       E.CHIUSA_DT
							  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
							 where e.q_userid like '997%'
							   and c.center  = e.CENTER
							   and uc.center = c.center
							   and uc.userid = '{$remote_userid}'
							   and e.CENTER={$in['CENTER']}
							   and e.esam<>3
							   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									";

					$sql_sent = "
								select e.ID,
								e.REGISTRY,
							       e.ESAM,
							       e.VISITNUM,
							       e.VISITNUM_PROGR,
							       e.PROGR,
							       e.CODPAT,
							       e.CENTER CENTER,
							       e.TIPO_EQUERY,
							       C.DENOM,
							       E.CHIUSA,
							       E.CHIUSA_DT,
							       E.TO_BE_VALIDATE,
							       E.VALIDATA,
							       E.VAL_DT,
							       E.VAL_USERID,
							       E.QUEST_DT,
							       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
							       E.CHIUSA_DT
							  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
							 where e.q_userid not like '997%'
							   and c.center  = e.CENTER
							   and uc.center = c.center
							   and uc.userid = '{$in['remote_userid']}'
							   and e.CENTER={$in['CENTER']}
							   and e.esam<>3
							   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									";		
				}



				if(preg_match ( "/^997/", $in ['remote_userid'] )){
					$html .= "<p align=center><b>" . $this->testo ( 'allEqL' ) . "</b></p>
											<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
											-- <a href=\"index.php?list=equery_closed.xml\">" . $this->testo ( "closedEq" ) . "
											--<a href=\"index.php?list=equery.xml\">" . $this->testo ( "allEq" ) . "
											-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
											";
				}
				else
				if(preg_match ( "/\b......0.\b/", $in ['remote_userid'] )){
						
					$html .= "
						<p align=center><b>" . $this->testo ( "allEqL" ) . "</b></p>
							<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
							-- <a href=\"index.php?list=equery_closed_ospe.xml\">" . $this->testo ( "closedEq" ) . "
							--<a href=\"index.php?list=equery_ospe.xml\">" . $this->testo ( "allEq" ) . "
							-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
						";
						
				}
				else{  	if(preg_match ( "/\b......00.\b/", $in ['remote_userid'] )){
						
					$html .= "
									<p align=center><b>" . $this->testo ( "allEqL" ) . "</b></p>
										<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
										-- <a href=\"index.php?list=equery_closed_terr.xml\">" . $this->testo ( "closedEq" ) . "
										--<a href=\"index.php?list=equery_terr.xml\">" . $this->testo ( "allEq" ) . "
										-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
									";

				}
				else{
					$html .= "<p align=center><b>" . $this->testo ( 'allEqL' ) . "</b></p>
											<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
											-- <a href=\"index.php?list=equery_closed.xml\">" . $this->testo ( "closedEq" ) . "
											--<a href=\"index.php?list=equery.xml\">" . $this->testo ( "allEq" ) . "
											-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
											";
				}





				}

			} else {
				//EQUERY APERTE
				$open = true;
				if (preg_match ( "/^997/", $in ['remote_userid'] )) {

					$sql_rec = "
						select e.ID,
			       e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.CODPAT,
			       e.CENTER CENTER,
			       e.TIPO_EQUERY,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.VAL_USERID,
			       E.QUEST_DT,
			      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT
			  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			  where e.q_userid not like '997%'
			   and e.chiusa is null
			   and c.center  = e.CENTER
			   and uc.center = c.center
			   and uc.userid = '{$remote_userid}'
			  order by  e.CENTER,e.TIPO_EQUERY,e.ID
					";
					$sql_sent = "
					select e.ID,
				   e.REGISTRY,
			       e.ESAM,
			       e.VISITNUM,
			       e.VISITNUM_PROGR,
			       e.PROGR,
			       e.CODPAT,
			       e.CENTER CENTER,
			       e.TIPO_EQUERY,
			       C.DENOM,
			       E.CHIUSA,
			       E.CHIUSA_DT,
			       E.TO_BE_VALIDATE,
			       E.VALIDATA,
			       E.VAL_DT,
			       E.VAL_USERID,
			       E.QUEST_DT,
			      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT
			  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
			  where e.q_userid like '997%'
			   and e.chiusa is null
			   and c.center  = e.CENTER
			   and uc.center = c.center
			   and uc.userid = '{$remote_userid}'
			   order by  e.CENTER,e.TIPO_EQUERY,e.ID
					";
				}
				else{
					if(preg_match ( "/\b......0.\b/", $in ['remote_userid'] )){
							
						$sql_rec = "
										 select DISTINCT e.ID,
										 e.REGISTRY,
							       e.ESAM,
							       e.VISITNUM,
							       e.VISITNUM_PROGR,
							       e.PROGR,
							       e.CODPAT,
							       e.CENTER CENTER,
							       e.TIPO_EQUERY,
							       C.DENOM,
							       E.CHIUSA,
							       E.CHIUSA_DT,
							       E.TO_BE_VALIDATE,
							       E.VALIDATA,
							       E.VAL_DT,
							       E.VAL_USERID,
							       E.QUEST_DT,
							      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
							       E.CHIUSA_DT
							  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
							  where e.q_userid like '997%' 
					   and e.ANSWER is  null
							   and c.center  = e.CENTER
							   and uc.center = c.center
							   and uc.center in (select substr(userid,0,12) 
																		from ana_utenti_1 a
																		where a.farma = '{$remote_userid}'
																		)
							   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									";
						$sql_sent = "
									select DISTINCT e.ID,
							       e.ESAM,
							       e.VISITNUM,
							       e.VISITNUM_PROGR,
							       e.PROGR,
							       e.CODPAT,
							       e.CENTER CENTER,
							       e.TIPO_EQUERY,
							       C.DENOM,
							       E.CHIUSA,
							       E.CHIUSA_DT,
							       E.TO_BE_VALIDATE,
							       E.VALIDATA,
							       E.VAL_DT,
							       E.VAL_USERID,
							       E.QUEST_DT,
							       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
							       E.CHIUSA_DT
							  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
							  where e.q_userid not like '997%'
					   and e.ANSWER is  null
							   and c.center  = e.CENTER
							   and uc.center = c.center
							   and uc.center in (select substr(userid,0,12) 
																		from ana_utenti_1 a
																		where a.farma = '{$in['remote_userid']}'
																		)
							   order by  e.CENTER,e.TIPO_EQUERY,e.ID
									";//preguntar por lo del not like del 997

					}
					else{	if(preg_match ( "/\b......00.\b/", $in ['remote_userid'] )){

						$sql_rec = "
															 select DISTINCT e.ID,
															 e.REGISTRY,
												       e.ESAM,
												       e.VISITNUM,
												       e.VISITNUM_PROGR,
												       e.PROGR,
												       e.CODPAT,
												       e.CENTER CENTER,
												       e.TIPO_EQUERY,
												       C.DENOM,
												       E.CHIUSA,
												       E.CHIUSA_DT,
												       E.TO_BE_VALIDATE,
												       E.VALIDATA,
												       E.VAL_DT,
												       E.VAL_USERID,
												       E.QUEST_DT,
												      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
												       E.CHIUSA_DT
												  from {$service}_equery e, {$service}_centri c
												  where e.q_userid like '997%'
					   and e.ANSWER is  null
												   and e.CENTER = c.center 
												   and e.esam = 3
												   and e.codpat in (select codpat
												   									from {$service}_dispensazione dp
												   									where dp.userid_ins = '{$remote_userid}')
												   order by  e.CENTER,e.TIPO_EQUERY,e.ID
												   
														";
						$sql_sent = "
														select e.ID,
												       e.ESAM,
												       e.VISITNUM,
												       e.VISITNUM_PROGR,
												       e.PROGR,
												       e.CODPAT,
												       e.CENTER CENTER,
												       e.TIPO_EQUERY,
												       C.DENOM,
												       E.CHIUSA,
												       E.CHIUSA_DT,
												       E.TO_BE_VALIDATE,
												       E.VALIDATA,
												       E.VAL_DT,
												       E.VAL_USERID,
												       E.QUEST_DT,
												       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT,
												       E.CHIUSA_DT
												  from {$service}_equery e, {$service}_centri c
												  where e.q_userid like '{$remote_userid}%'
					   and e.ANSWER is  null
												   and e.CENTER = c.center 
												   and e.esam = 3
												   and e.codpat in (select codpat
												   									from {$service}_dispensazione dp
												   									where dp.userid_ins = '{$remote_userid}')
												   order by  e.CENTER,e.TIPO_EQUERY,e.ID
														";
							
							
					}
					else{
						$sql_rec = "
																select DISTINCT e.ID,
														     e.REGISTRY,
													       e.ESAM,
													       e.VISITNUM,
													       e.VISITNUM_PROGR,
													       e.PROGR,
													       e.CODPAT,
													       e.CENTER CENTER,
													       e.TIPO_EQUERY,
													       C.DENOM,
													       E.CHIUSA,
													       E.CHIUSA_DT,
													       E.TO_BE_VALIDATE,
													       E.VALIDATA,
													       E.VAL_DT,
													       E.VAL_USERID,
													       E.QUEST_DT,
													      to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT
													  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
													  where e.q_userid like '997%'
						   and e.ANSWER is  null
													   and c.center  = e.CENTER
													   and uc.center = c.center
													   and uc.userid = '{$remote_userid}'
							   and e.esam<>3
													  order by  e.CENTER,e.TIPO_EQUERY,e.ID
															";
						$sql_sent = "
															select e.ID,
														   e.REGISTRY,
													       e.ESAM,
													       e.VISITNUM,
													       e.VISITNUM_PROGR,
													       e.PROGR,
													       e.CODPAT,
													       e.CENTER CENTER,
													       e.TIPO_EQUERY,
													       C.DENOM,
													       E.CHIUSA,
													       E.CHIUSA_DT,
													       E.TO_BE_VALIDATE,
													       E.VALIDATA,
													       E.VAL_DT,
													       E.VAL_USERID,
													       E.QUEST_DT,
													       to_char(E.ANS_DT,'DD/MM/YYYY') as ANS_DT
													  from {$service}_equery e, {$service}_utenti_centri uc, {$service}_centri c
													  where e.q_userid not like '997%' 
					   and e.ANSWER is  null
													   and c.center  = e.CENTER
													   and uc.center = c.center
													   and uc.userid = '{$remote_userid}'
							   and e.esam<>3
													   order by  e.CENTER,e.TIPO_EQUERY,e.ID
															";

					}
						
					}


				}
					
				if(preg_match ( "/^997/", $in ['remote_userid'] )){
					$html .= "<p align=center><b>" . $this->testo ( 'openedEq' ) . "</b></p>
											<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
											-- <a href=\"index.php?list=equery_closed.xml\">" . $this->testo ( "closedEq" ) . "
											--<a href=\"index.php?list=equery.xml\">" . $this->testo ( "allEq" ) . "
											-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
											";
				}
				else
				if(preg_match ( "/\b......0.\b/", $in ['remote_userid'] )){
						
					$html .= "
						<p align=center><b>" . $this->testo ( "openedEq" ) . "</b></p>
							<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
							-- <a href=\"index.php?list=equery_closed_ospe.xml\">" . $this->testo ( "closedEq" ) . "
							--<a href=\"index.php?list=equery_ospe.xml\">" . $this->testo ( "allEq" ) . "
							-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
						";
						
				}
				else{  	if(preg_match ( "/\b......00.\b/", $in ['remote_userid'] )){
						
					$html .= "
									<p align=center><b>" . $this->testo ( "openedEq" ) . "</b></p>
										<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
										-- <a href=\"index.php?list=equery_closed_terr.xml\">" . $this->testo ( "closedEq" ) . "
										--<a href=\"index.php?list=equery_terr.xml\">" . $this->testo ( "allEq" ) . "
										-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
									";

				}
				else{
					$html .= "<p align=center><b>" . $this->testo ( 'openedEq' ) . "</b></p>
											<p align=right><a href=\"index.php?eQuery\">" . $this->testo ( "openedEqS" ) . "
											-- <a href=\"index.php?list=equery_closed.xml\">" . $this->testo ( "closedEq" ) . "
											--<a href=\"index.php?list=equery.xml\">" . $this->testo ( "allEq" ) . "
											-- <a href=\"index.php?SEARCH=4\">" . $this->testo ( "searchEq" ) . "</p>
											";
				}





				}
			}
			//eQuery ricevute
			$sql = new query ( $this->conn );
			$sql->set_sql ( $sql_rec );
			$sql->exec ();
			$rec_list = $this->eList ( $sql, $open );
			$sql = new query ( $this->conn );
			$sql->set_sql ( $sql_sent );
			$sql->exec ();
			$sent_list = $this->eList ( $sql, $open );
			if (! preg_match ( "/^995/", $remote_userid )&&!preg_match ( "/\b......00.\b/", $remote_userid ))
			$html .= "<br><a href=\"index.php?eQuery&eform\">" . $this->testo ( "newEq" ) . "</a><br><br>";
			$html .= "

				<table border=0 cellpadding=0 cellspacing=0 class=titolo align=center width=95%>
					<tr>
						<td>" . $this->testo ( "receivedEq" ) . "</td>
					</tr>
				</table>
				<br>
			$rec_list
				<br><br>
				<table border=0 cellpadding=0 cellspacing=0 class=titolo align=center width=95%>
					<tr>
						<td>" . $this->testo ( "sendedEq" ) . "</td>
					</tr>
				</table>
				<br>
			$sent_list
				<br><br>

				";
			if (! preg_match ( "/^995/", $remote_userid )&&!preg_match ( "/\b......00.\b/", $remote_userid ))
			$html .= "<a href=\"index.php?eQuery&eform\">" . $this->testo ( "newEq" ) . "</a>";
		} else {
			if (! isset ( $in ['ID'] )) {
				$dati_equery = null;
			} else {
				$sql_dati_query="
								SELECT A.ID,
								  A.CENTER,
								  A.CODPAT,
								  A.VISITNUM,
								  A.ESAM,
								  A.PROGR,
								  A.Q_USERID,
								  A.TIPO_EQUERY,
								  b.NOME ||' ' || b.COGNOME Q_NUSERID,
								  b.NOME_RESP ||' ' ||b.COGNOME_RESP PRIMARIO,
								  A.QUESTION,
								  SUBSTR(c.COGNOME, 0, 3) ||' ' || SUBSTR(c.NOME, 0, 3) INIPAZIENTE,
								  TO_CHAR(A.QUEST_DT,'DD/MM/YYYY') QUEST_DT,
								  A.TO_BE_VALIDATE,
								  A.ANSWER,
								  TO_CHAR(A.ANS_DT,'DD/MM/YYYY') ANS_DT,
								  A_USERID,
								  A.VALIDATA,
								  A.CHIUSA,
								  TO_CHAR(A.VAL_DT,'DD/MM/YYYY') VAL_DT,
								  A.VAL_USERID,
								  A.VISITNUM_PROGR,
								  TO_CHAR(A.CHIUSA_DT,'DD/MM/YYYY') CHIUSA_DT
								FROM {$service}_equery a,
								  ana_utenti_1 b,
				{$service}_REGISTRAZIONE c
								WHERE id = {$in['ID']}
								AND a.Q_USERID = b.USERID
								AND a.CODPAT  = C.CODPAT(+)
";				

				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_dati_query );
// 				echo "<hr>".$sql_dati_query;
				$sql->exec ();
				$sql->get_row ();
				$dati_equery = $sql->row;
			}
			$html .= $this->eForm ( $dati_equery );
		}
		//Nuovo modo di generare il menu briciola di pane
		$percorso = $this->breadcrumb ( "equery" );
		return $percorso . $html;
	}

	function searchEquery(){
		// 		echo "<hr> funcion que busca una equery";
		global $remote_userid;
		global $in;
		$dir=$_SERVER['PATH_TRANSLATED'];

		$dir=preg_replace("/\/index.php/", "", $dir);
		//$filetxt = file_get_contents($dir.'/template.htm');
		$file_form=$this->getXMRPath("xml_dir","search_paziente.xml")."/search_paziente.xml";
		if (preg_match("/^99/", $remote_userid))
		$file_form=$this->getXMRPath("xml_dir","search_paziente_dm.xml")."/search_paziente_dm.xml";

		echo "<hr>".$file_form;
		$xml_form=new xml_form();

		$xml_form->xml_form_by_file($file_form);

		$xml_form->config_service['field_lib']= $this->field_lib;
		//		echo "<hr>".$xml_form->config_service['field_lib'];
		die();
		$xml_form->open_form();
		//die();
		$body.=$xml_form->body;
		// 		print_r($xml_form);
		echo "<hr>".$xml_form->body;
	}

	function eList($sql, $open){
		//		print_r($sql);print_r($open); die();
		global $conn;
		$in=$this->session_vars;
		$config_service=$this->config_service;
		if ($open)
		$html="
			<table border='0px' cellpadding='0px' cellspacing='2px' width='95%' align='center'>
				<tr>
					<th class='int'>ID</th>".
		//<th class='int'>".$this->testo("Center")."</th>
					"<th class='int'>".$this->testo("Paziente")."</th>
					<th class='int'>".$this->testo("eQueryType")."</th>
					<th class='int'>".$this->testo("Visit")."</th>
					<th class='int'>".$this->testo("Esam")."</th>
					<th class='int'>".$this->testo("eQueryDate")."</th>
					<th class='int'>Risposta</th>
					<th class='int'>".$this->testo("Dateofanswer")."</th>
					<th class='int'>".$this->testo("Modify")."</th>
				</tr>
		";
		if (!$open){
			$html="
			<table border='0px' cellpadding='0px' cellspacing='2px' width='95%' align='center'>
				<tr>
					<th class='int>ID</th>".
			//<th class='int>".$this->testo("Center")."</th>
					"<th class='int'>".$this->testo("Paziente")."</th>
					<th class='int'>".$this->testo("eQueryType")."</th>
					<th class='int'>".$this->testo("Visit")."</th>
					<th class='int'>".$this->testo("Esam")."</th>
					<th class='int'>".$this->testo("eQueryDate")."</th>
					<th class='int'>Risposta</th>
					<th class='int'>".$this->testo("Dateofanswer")."</th>
					<th class='int'>".$this->testo("closeDate")."</th>
					<th class='int'>".$this->testo("Modify")."</th>
				</tr>
		";
		}
		//raggruppo per centro (G.Tufano)
		$old_center='';
		while ($sql->get_row()){
			$visita=$this->vlist->visitnums[$sql->row['VISITNUM']]['TEXT'];
			$esame=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
			if($sql->row['TIPO_EQUERY']==1)
			{
				$tipo_equery=$this->testo("eQueryType1");
			}
			else
			{
				if($sql->row['TIPO_EQUERY']==2)
				$tipo_equery=$this->testo("eQueryType2");
				else
				$tipo_equery=$this->testo("eQueryTypeNull");
			}
			$link_="<a href=\"index.php?eQuery&eform&ID={$sql->row['ID']}\">{$sql->row['ID']}</a>";
			$link_stat="<a href=\"index.php?eQuery&eform&ID={$sql->row['ID']}&VIS=1\">Visualizza</a>";
			global $config_service;
			if ($sql->row['TO_BE_VALIDATE']=='1' && $in['USER_TIP']=='DM' && $sql->row['VAL_DT']=='') {
				$form="&amp;form={$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['XML']}";
				$link_validazione="
					<a href=\"index.php?CENTER={$sql->row['CENTER']}&amp;{$config_service['PK_SERVICE']}={$sql->row[$config_service['PK_SERVICE']]}&amp;ESAM={$sql->row['ESAM']}&amp;PROGR={$sql->row['PROGR']}&amp;VISITNUM={$sql->row['VISITNUM']}&amp;VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}{$form}\">".$this->testo("ModifyForm")."</a>
					";
			}
			if ($sql->row['TO_BE_VALIDATE']=='1' && $sql->row['VAL_DT']=='' && $in['USER_TIP']!='DM'){
				$link_validazione=$this->testo("ChangeNecessary");
			}
			if ($sql->row['TO_BE_VALIDATE']=='0'){
				$link_validazione=$this->testo("ChangeNotNecessary");
				//				if($this->config_service['lang']=="en") {
				//					$link_validazione='Change is not necessary';
				//				} else {
				//					$link_validazione='Modifica non necessaria';
				//				}
			}
			if ($sql->row['TO_BE_VALIDATE']==''){
				$link_validazione='---';
			}
			if ($sql->row['TO_BE_VALIDATE']=='1' && $sql->row['VAL_DT']!='') {
				$sql_umod=new query($conn);
				$sql_umod_text="select AZIENDA_ENTE||'-'||NOME||' '||COGNOME||' ('||USERID||')' as UMOD  from ANA_UTENTI_1  where  USERID='{$sql->row['VAL_USERID']}'";
				$sql_umod->set_sql($sql_umod_text);
				$sql_umod->exec();
				$sql_umod->get_row();

				$link_validazione=$this->testo("ChangeMadeAt")." ".$sql->row['VAL_DT']."<BR> da ".$sql_umod->row['UMOD'];
				//				if($this->config_service['lang']=="en") {
				//					$link_validazione="Changes made to the {$sql->row['VAL_DT']}";
				//				} else {
				//					$link_validazione="Modifica effettuata il {$sql->row['VAL_DT']} da {$sql->row['VAL_USERID']}";
				//				}
			}
				
			//inserisco il centro raggrupato (G.Tufano)
		 if ($old_center!=$sql->row['DENOM'])
		 {
		 	$old_center=$sql->row['DENOM'];
		 	if ($open){
		 		$html.="<tr><td class=input colspan=9 align=center>
				<b>{$sql->row['DENOM']} ({$sql->row['CENTER']})</b></tD></tr>
      ";
		  }
		  else {
		  	$html.="<tr><td class=input colspan=10 align=center>
				<b>{$sql->row['DENOM']} ({$sql->row['CENTER']})</b></tD></tr>
      ";
		  }
		 }
		 	
			//colonna "risposta"
			$quest_status="<b><font color=\"#FF0000\">No</font></b>";
			if($sql->row['ANS_DT']!='')$quest_status="<b>Si</b>";
			$quest_status.="<br>".$link_stat;

			if ($open){
				$html.="
				<tr>
					<td class='sc4bis' align='center'>$link_</td>".
				//<td class='sc4bis'>{$sql->row['CENTER']}<br>{$sql->row['DENOM']}</td>
					"<td class='sc4bis'>{$sql->row['CODPAT']}</td>
					<td class='sc4bis'>$tipo_equery</td>
					<td class='sc4bis'>$visita</td>
					<td class='sc4bis'>$esame</td>
					<td class='sc4bis'>{$sql->row['QUEST_DT']}</td>
					<td class='sc4bis' align=center>$quest_status</td>
					<td class='sc4bis'>{$sql->row['ANS_DT']}</td>
					<td class='sc4bis' align=center>$link_validazione</td>
				</tr>
					";
			}
			else
			$html.="
				<tr>
					<td class='sc4bis' align='center'>$link_</td>".
			//<td class='sc4bis'>{$sql->row['CENTER']}<br>{$sql->row['DENOM']}</td>
					"<td class='sc4bis'>{$sql->row['CODPAT']}</td>
					<td class='sc4bis'>$tipo_equery</td>
					<td class='sc4bis'>$visita</td>
					<td class='sc4bis'>$esame</td>
					<td class='sc4bis'>{$sql->row['QUEST_DT']}</td>
					<td class='sc4bis' align=center>$quest_status</td>
					<td class='sc4bis'>{$sql->row['ANS_DT']}</td>
					<td class='sc4bis'>{$sql->row['CHIUSA_DT']}</td>
					<td class='sc4bis' align=center>$link_validazione</td>
				</tr>
					";
		}
		$html.="</table>";

		return $html;
	}


	function notifica_equery($switch_notifica, $id) {

		$in = $this->session_vars;
		//		echo "<hr>sono qui";

		$service = $this->service;
		$config_service = $this->config_service;
		$conn = $this->conn;

		$sql = new query ( $conn );

		$query="select CODPAT, VISITNUM, VISITNUM_PROGR,ESAM,PROGR from ".$service."_equery where id=".$id;
		$sql->set_sql($query);
		$sql->exec ();
		$sql->get_row ();
		$codpatEquery=$sql->row['CODPAT'];
		$esamEquery=$sql->row['ESAM'];
		$progrEquery=$sql->row['PROGR'];
		$visitnumEquery=$sql->row['VISITNUM'];
		$visitnumProgrEquery=$sql->row['VISITNUM_PROGR'];
		$query = "select nome||' '||cognome||' - '||azienda_ente as mitt from ana_utenti where userid='{$in['remote_userid']}'";
		$sql->set_sql ( $query );
		$sql->exec ();
		$sql->get_row ();

		if ($_SERVER ['HTTPS'])
		$s = 's';
		$link = "http$s://" . $_SERVER ['HTTP_HOST'] . $_SERVER ['PHP_SELF'] . "?eQuery";

		switch ($switch_notifica) {
			case "1" :
				$where = "where a.userid=uc.userid and uc.center='{$in['CENTER']}' and ";
				if ($this->config_service ['lang'] == "en")
				$testo_mail = "New equery send from {$sql->row['MITT']} query n. $id
					<br /><br />
					Equeries list:<br />
					<a href='$link'>$link</a>
					";
				else
				$testo_mail = "Nuova equery inviata da {$sql->row['MITT']} query n. $id
					<br /><br />
					Elenco equery:<br />
					<a href='$link'>$link</a>
					";
				break;
			case "2" :
				$where = ", {$service}_equery eq where eq.id='{$in['ID']}' and eq.center=uc.center and a.userid=uc.userid and ";
				if ($this->config_service ['lang'] == "en")
				$testo_mail = "Equery answer n. $id
					<br /><br />
					Equeries list:<br />
					<a href='$link'>$link</a>
					";
				else
				$testo_mail = "Risposta query n. $id
					<br /><br />
					Elenco equery:<br />
					<a href='$link'>$link</a>
					";
				break;
			default :
				$where = " where ";
			return '';
		}

		//G.Tufano 27/07/2011
		//modifica: inserita la clausola per evitare di includere le farma territoriali tra i mittenti (lunghezza 9 e penultimo carattere = '0')
		//inoltre già che c'ero ho impostato l'invio affinché usi la libreria avanzata Mail.php
		if ($in ['USER_TIP'] == 'DE') {
			$query = "select email from ana_utenti a, {$service}_utenti_centri uc $where uc.tipologia like '%manager%' and a.userid not like '______00_' and a.userid not like '_______0_' and email is not null";
				
			//			echo "<hr>esta es la query: ".$query;
			$sql->set_sql ( $query );
			$sql->exec ();
			$to = '';

			while ( $sql->get_row () ) {
				if ($to != '')
				$to .= ",";
				$to .= $sql->row ['EMAIL'];
			}
				
		} else {
			//AQUI DEBE IR LA PARTE QUE AGREGA LAS FARMACIAS CUANDO SE TRATE DE UNA DISPENSAZIONE!!!!
			//CORREGIR LA PARTE DE a.userid not like '...
			//AHI DEBERIA FIJARSE SI ES UNA DISPENSAZIONE Y EN BASE A ESO MANDAR EL MAIL A LAS FARMACIAS!!!
			//$query = "select email from ana_utenti a,{$service}_utenti_centri uc $where  uc.tipologia like '%Entry%' and a.userid not like '______00_' and a.userid not like '______0_'";

			if($esamEquery==3 && $visitnumEquery==1)
			{
				$query= "select USERID_INS from ".$service."_dispensazione where VISITNUM=".$visitnumEquery." and visitnum_progr=".$visitnumProgrEquery." and esam=".$esamEquery." and progr=".$progrEquery." and codpat=".$codpatEquery;
				$sql->set_sql($query);
				$sql->exec();
				$sql->get_row();
				$userFarma=$sql->row['USERID_INS'];
				$query = "select email from ana_utenti a,{$service}_utenti_centri uc $where  uc.tipologia like '%Entry%' and a.userid like '{$userFarma}'";
					
			}
			else
			{
				$query = "select email from ana_utenti a,{$service}_utenti_centri uc $where  uc.tipologia like '%Entry%' and a.userid not like '______00_' and a.userid not like '______0_'";
			}
				
				
			$sql->set_sql ( $query );
			$sql->exec ();

			$to = '';
			while ( $sql->get_row () ) {
				if ($to != '')
				$to .= ",";
				$to .= $sql->row ['EMAIL'];
			}
		}

		//**** INVIO MAIL
		include_once 'Mail.php';

		//differenzio se sono in test o no
		if ((preg_match("/sissdev/i",$_SERVER['SERVER_NAME'])) || (preg_match("/sissprep/i",$_SERVER['SERVER_NAME']))){
			$test='***TEST***';
		}
		else{
			$test='';
		}

		//IMPOSTARE NEL CONFIG QUESTI PARAMETRI
		$from_service_email = $config_service ['from_service_email'];
		$from_service_name = $config_service ['from_service_name'];

		$reply_to = 'noreply@cineca.it';

		if ($config_service ['oggetto_notifiche'] != "")
		$oggetto = $test.$config_service ['oggetto_notifiche'] . "- query n. '.$id";
		else
		$oggetto = $test.$_SERVER ['SERVER_NAME'] . ' - query n. ' . $id;
			

		if ($testo_mail != ''){
			//TODO sistemare l'invio della mail
			//		send_email_advanced(null, $from_service_email, $from_service_name, $oggetto, $testo_mail, $reply_to,false, null, $to);
			mail ( $to, $oggetto, $testo_mail, $headers );
			//		echo "<hr>$testo_mail";
			// 		 echo "<hr>Termina ";
		}
	}

	
	function eFormStep2($dati_equery) {
		//TODO ricontrolla... per es l'hidden con hoy
		$sql= new query($this->conn);
		$sql->set_sql("SELECT TO_CHAR(SYSDATE,'YYYYMMDD') AS HOY FROM DUAL");
		$sql->exec();
		$sql->get_row();
		$hoy=$sql->row['HOY'];
	
		$form= file_get_contents($this->getXMRPath("templates_dir","equery_answer.htm").'/'."equery_answer.htm");
	
		$service = $this->service;
		$in = $this->session_vars;
	
		if (isset ( $in ['ANSWER'] ) && $in ['ANSWER'] != '') {
				
			$bind = array();
			// 			$bind['QUEST_DT'] = $dati_equery['QUEST_DT'];
			$bind['A_USERID'] = $in ['remote_userid'];
			$bind['ANSWER'] = $in ['ANSWER'];
			$bind['ANS_DT'] = $in['ANS_DT'];
			if (isset ( $in ['TO_BE_VALIDATE'] )) {
				if ($in ['TO_BE_VALIDATE'] == '0') {
					$bind['CHIUSA'] = '1';
					$bind['CHIUSA_DT'] = 'sysdate';
					$chiusa = ',chiusa = :chiusa,
							  chiusa_dt = :chiusa_dt';
				}
				$bind ['TO_BE_VALIDATE'] = $in ['TO_BE_VALIDATE'];
				$validate = ',TO_BE_VALIDATE=:to_be_validate';
			}
			
			$bind ['PK_ID'] = $in ['ID'];
				
			$table = $service . "_equery";
				
			$sql_upd = "UPDATE {$table}
							SET
							  A_USERID      =:a_userid,
							  ANSWER        =:answer,
							  ANS_DT        =to_date(:ans_dt,'DDMMYYYY')
							  $validate
							  $chiusa
							WHERE
							  ID=:pk_id     ";
				
// 			echo $sql_upd.'<hr />'.print_r($bind,true);die();
			$sql->ins_upd ( $sql_upd, $bind);
				
			$this->conn->commit ();
	
			// Notifiche mail, nuova equery
			if ($this->notifica)
			$this->notifica_equery ( 2, $in ['ID'] );
	
			die ( "<html><head><meta http-equiv=\"refresh\" content=\"0;url=index.php?eQuery\"></head></html>" );
		}
		if (isset ( $in ['TO_BE_VALIDATE'] )) {
			if ($in ['TO_BE_VALIDATE'] == '0') {
				$values ['CHIUSA'] = '1';
				$values ['CHIUSA_DT'] = 'sysdate';
			}
			$values ['TO_BE_VALIDATE'] = $in ['TO_BE_VALIDATE'];
			$pk ['ID'] = $in ['ID'];
			$table = $service . "_equery";
			$sql = new query ( $this->conn );
			$sql->update ( $values, $table, $pk );
			$this->conn->commit ();
			die ( "<html><head><meta http-equiv=\"refresh\" content=\"0;url=index.php?eQuery\"></head></html>" );
		}
		if ($dati_equery ['ANSWER'] == '') {
			if ($in ['remote_userid'] != $dati_equery ['Q_USERID']) {
				if ($this->getTipologia($in ['remote_userid'],$dati_equery['CENTER']) != $this->getTipologia($dati_equery ['Q_USERID'],$dati_equery['CENTER'])) {
					//echo "<hr> ESTE ES EL CENTRO: ".$in ['CENTER'];
					//print_r($dati_equery);
					$answer = "<textarea name='ANSWER' cols='80' ROWS='10'></textarea>
							</td>
				</tr>
								<tr>
							<td width='40%' class='destra'>
								<b>Data risposta:</b>
							</td>
							<td width='60%' class='input'>
								<input type='text'  name='ANS_DTD' value=\"\" size='2' maxlength='2' />&nbsp;
								<input  type='text' name='ANS_DTM' value=\"\" size='2' maxlength='2' />
                <input  type='text' name='ANS_DTY' value='' size='4' maxlength='4' />
                <input type='hidden' name='ANS_DT' value='' />
                <input type='hidden' name='ANS_DTRC'/>
							</td>
				</tr>";
					if ($in ['USER_TIP'] == 'DM'){
					$answer .= "
				<tr>
					<td class='destra'><b>" . $this->testo ( 'ModifyForm' ) . "</b></td>
					<td class='input'>
						<input type='radio' name='TO_BE_VALIDATE' value='0'>" . $this->testo ( 'notNecessary' ) . "<br>
						<input type='radio' name='TO_BE_VALIDATE' value='1'>" . $this->testo ( 'necessary' ) . "

				";
					}
					$sendDate=substr($dati_equery['QUEST_DT'],6).substr($dati_equery['QUEST_DT'],3,2).substr($dati_equery['QUEST_DT'],0,2);
					$form = str_replace ( "<!--answer-->", $answer, $form );
					$html .= "<form method='post' action='index.php'>
					$form
				<p align='center'>
						<input type='hidden' value='{$hoy}' name='HOY'>
						<input type='submit' value='" . $this->testo ( 'sendAnswer' ) . "' onclick=\"
						
f=document.forms[0];
el=f.elements;
specifiche='A=ON&L=0&F=0';

dia=el['ANS_DTD'].value
mes=el['ANS_DTM'].value
ano=el['ANS_DTY'].value
if({$hoy}<ano+mes+dia || ano+mes+dia < {$sendDate}){
	alert('Attenzione prego. Formato non corretto nel campo Data risposta. Formato: GG/MM/AAAA');
	el['ANS_DTY'].focus();
	return false;
	}
c1=''+
'<<t###ANSWER###Risposta>>'+
'<<fd00###ANS_DT###Data risposta>>'+
'';
rc=contr(c1,specifiche);
if (rc) {return false}
						
						\"> &nbsp;
						<input type='reset' value='" . $this->testo ( 'cancel' ) . "'>
					</p>
				</form>	";
				}
			} else
			error_page ( $in ['remote_userid'], $this->testo ( 'userNotCenter' ), $this->testo ( 'userNotCenter' ) );
		} else {
			$ansdate=substr($dati_equery['ANS_DT'],0,10);
			if ($dati_equery ['TO_BE_VALIDATE'] == '') {
				if ($in ['USER_TIP'] == 'DM') {
					$answer = "<b>{$dati_equery['ANSWER']}</b>";
					$answer .= "
					</td>
				</tr>
				<tr>
							<td width='40%' class='destra'>
								<b>Data risposta:</b>
							</td>
							<td width='60%' class='input'>
								<b>". $ansdate."</b>
							</td>
				</tr>
				<tr>
					<td class='destra'><b>". $this->testo ( 'ModifyForm' ) . "</b></td>
					<td class='input'>
						<input type='radio' name='TO_BE_VALIDATE' value='0'>" . $this->testo ( 'notNecessary' ) . "<br>
						<input type='radio' name='TO_BE_VALIDATE' value='1'>" . $this->testo ( 'necessary' ) . "

				";
					$form = str_replace ( "<!--answer-->", $answer, $form );
					$html .= "
				<form method='post' action='index.php'>
					$form
				<p align='center'>
						<input type='submit' value='" . $this->testo ( 'sendAnswer' ) . "'> &nbsp;
						<input type='reset' value='" . $this->testo ( 'cancel' ) . "'>
					</p>
				</form>
				";
				} else {
					$form = str_replace ( "<!--answer-->", "<b>{$dati_equery['ANSWER']}</b>
						<tr>
							<td width='40%' class='destra'>
								<b>Data risposta:</b>
							</td>
							<td width='60%' class='input'>
								<b>". $ansdate."</b>
						</td>
						</tr>", $form );
					$html .= "
					$form
						";
				}
			} else {
				$answer = "<b>{$dati_equery['ANSWER']}</b>";
				$img_not_nec = $img_nec = "<img src='images/uncheckedradio.gif'>";
				if ($dati_equery ['TO_BE_VALIDATE'] == '0')
				$img_not_nec = "<img src='images/checkedradio.gif' />";
				if ($dati_equery ['TO_BE_VALIDATE'] == '1')
				$img_nec = "<img src='images/checkedradio.gif' />";
				$answer .= "
				</td>
				</tr>
				<tr>
							<td width='40%' class='destra'>
								<b>Data risposta:</b>
							</td>
							<td width='60%' class='input'>
								<b>". $ansdate."</b>
							</td>
				</tr>
				<tr>
					<td class='destra'><b>" . $this->testo ( 'ModifyForm' ) . ":</b></td>
					<td class='input'>
				$img_not_nec " . $this->testo ( 'notNecessary' ) . "<br>
				$img_nec " . $this->testo ( 'necessary' ) . "
				";
				$form = str_replace ( "<!--answer-->", $answer, $form );
				$html .= "
				$form
				";
			}
		}
		return $html;
	}

	function eFormStep1($dati_equery = null) {
		$in = $this->session_vars;
		$config_service = $this->config_service;
		$xml_dir = $this->xml_dir;
		$service = $this->xmr->prefix;
		if (!is_null ( $dati_equery )) {
			/*parte per la visualizzazione del progressivo in visualizzazione delle equery /**Giorgio DELSIGNORE**/
			//print_r($dati_equery);
			$sql_query="
					select
						distinct progr
					from {$service}_coordinate
					where
					{$config_service['PK_SERVICE']}=:pk_service
					and abilitato=1
					and visitnum=:visitnum
					and visitnum_progr=:visitnum_progr
					and esam=:esam
					order by progr asc";
			unset($bind);
					$bind['PK_SERVICE']=$dati_equery[$config_service['PK_SERVICE']];
					$bind['VISITNUM']=$dati_equery['VISITNUM'];
					$bind['VISITNUM_PROGR']=$dati_equery['VISITNUM_PROGR'];
					$bind['ESAM']=$dati_equery['ESAM'];
$sql= new query($this->conn);
					//$sql->set_sql($sql_query);
					$sql->exec($sql_query,$bind);//binded
			//				print_R($this->vlist->esams[$dati_equery['VISITNUM']][$dati_equery['ESAM']]['PROGR']);
			if ($this->vlist->esams[$dati_equery['VISITNUM']][$dati_equery['ESAM']]['PROGR']=='yes'){

				//				if ($sql->numrows>1){

				$progressivo="
							</td>
						</tr>
						<tr>
							<td class='destra'>
								<b>Esame n.ro</b>
							</td>
							<td class='input'>
								<b>{$dati_equery['PROGR']}</b>
				";
			}
			/*fine parte per la visualizzazione del progressivo*/
			//TODO binding
			$sql_envio_scheda="
					select
						to_char(insertdt,'DD/MM/YYYY') insertdt,
						to_char(moddt,'DD/MM/YYYY') moddt
					from {$service}_coordinate
					where
			{$config_service['PK_SERVICE']}={$dati_equery[$config_service['PK_SERVICE']]}
					and abilitato=1
					and visitnum={$dati_equery['VISITNUM']}
					and visitnum_progr={$dati_equery['VISITNUM_PROGR']}
					and esam={$dati_equery['ESAM']}
					and progr={$dati_equery['PROGR']}";
				
			$sql=new query($this->conn);
			$sql->set_sql($sql_envio_scheda);
			$sql->exec();
			$sql->get_row();
			//echo substr($sql->row['INSERTDT'],0,10).substr($sql->row['MODDT'],0,10).$sql->row['FINE'];
			$insertAux=$sql->row['INSERTDT'];
			$modificaAux=$sql->row['MODDT'];
			//echo "<hr>".$modificaAux."<hr>";
			//echo $sql_envio_scheda;
			if($modificaAux=='')
			$data_envio_scheda=$insertAux;
			else
			$data_envio_scheda=$modificaAux;
			//TODO binding
			$sql_query="
				select c.*
				from {$service}_centri c,
			{$service}_utenti_centri uc
				where
					uc.userid='{$in['remote_userid']}'
					and uc.center=c.center
					and uc.center='{$dati_equery['CENTER']}'
					";
// 			echo $sql_query;
			$sql->set_sql($sql_query);
			$sql->exec();
			$sql->get_row();

			//print_r($dati_equery);
			//print_r($this->vlist);
			$centro="<b>{$sql->row['DENOM']}</b><input type='hidden' name='CENTER' value='{$dati_equery['CENTER']}'>";
			$data_invio= substr($dati_equery['QUEST_DT'],0,10);
			$data_invio= "<b>".$data_invio."</b>";
			$img_not_nec = $img_nec = "<img src='images/uncheckedradio.gif' />";
			if($dati_equery ['TIPO_EQUERY'] != '')
			{
				if ($dati_equery ['TIPO_EQUERY'] == '1')
				$img_not_nec = "<img src='images/checkedradio.gif' / >";
				if ($dati_equery ['TIPO_EQUERY'] == '2')
				$img_nec = "<img src='images/checkedradio.gif' />";
				$tipo_equery="	$img_not_nec 	<b>".$this->testo("eQueryType1")."</b><br>
				$img_nec 			<b>".$this->testo("eQueryType2")."</b>";
			}
			else
			{
				$tipo_equery="<b>".$this->testo("eQueryTypeNull")."<b>";
			}
			$data_envio_scheda="<b>".$data_envio_scheda."</b>";
			$paziente="<b>{$dati_equery[$config_service['PK_SERVICE']]}</b><input type=\"hidden\" name=\"{$config_service['PK_SERVICE']}\" value=\"{$dati_equery[$config_service['PK_SERVICE']]}\">";
			$visita="<b>{$this->vlist->visitnums[$dati_equery['VISITNUM']]['TEXT']}</b><input type=\"hidden\" name=\"VISITNUM\" value=\"{$dati_equery['VISITNUM']}\">";
			$visit_progr="<input type=\"hidden\" name=\"VISITNUM_PROGR\" value=\"{$dati_equery['VISITNUM_PROGR']}\">";
			$esame="<b>{$this->vlist->esams[$dati_equery['VISITNUM']][$dati_equery['ESAM']]['TESTO']}</b>
						<input type=\"hidden\" name=\"ESAM\" value=\"{$dati_equery['ESAM']}\">
						";
			/*parte per la visualizzazione del progressivo in visualizzazione delle equery /**Giorgio DELSIGNORE**/
			$progressivo.="
						<input type=\"hidden\" name=\"PROGR\" value=\"{$dati_equery['PROGR']}\">
						";
			/*fine parte per la visualizzazione del progressivo*/
			$question="<b>{$dati_equery['QUESTION']}</b>";
			$scheda=$this->vlist->esams[$dati_equery['VISITNUM']][$dati_equery['ESAM']]['XML'];
			if($this->vlist->esams[$dati_equery['VISITNUM']][$dati_equery['ESAM']]['PROGR']=='yes')
			$auxProgr="&PROGR={$dati_equery['PROGR']}";
			else
			$auxProgr="";
			$link_scheda="index.php?CENTER=".$dati_equery['CENTER']."&CODPAT=".$dati_equery[$config_service['PK_SERVICE']]."&VISITNUM=".$dati_equery['VISITNUM']."&ESAM=".$dati_equery['ESAM']."&form=".$scheda.$auxProgr/*."&RO=1"*/;
			$link_html="";
			//echo "<hr>".$link_scheda;
			if (preg_match ( "/^997/", $in ['remote_userid'] ))
			$link_html="
        						<tr>
							<td class=destra colspan=2>
							<a href=\"$link_scheda\" target=_new>{$this->testo("visualizzaScheda")}</a>
							</td>
						</tr>
        ";
			$form= file_get_contents($this->getXMRPath("templates_dir","equery_question.htm").'/'."equery_question.htm");
			$form=str_replace("<!--centro-->", $centro, $form);
			$form=str_replace("<!--paziente-->", $paziente, $form);
			$form=str_replace("<!--data_invio-->", $data_invio, $form);
			$form=str_replace("<!--tipo_equery-->", $tipo_equery, $form);
			$form=str_replace("<!--data_invio_scheda-->", $data_envio_scheda, $form);
			//echo "<hr>".$dati_equery['QUEST_DT']."<hr>";
			//echo "<hr>".$data_invio."<hr>";
			$form=str_replace("<!--registry-->", $this->eRegistryList(), $form);
			$form=str_replace("<!--visita-->", $visita.$visit_progr, $form);
			$form=str_replace("<!--esame-->",$esame.$progressivo, $form);
			$form=str_replace("<!--visualizza_scheda-->",$link_html, $form);
			$form=str_replace("<!--question-->", $question, $form);
			//modifica Giacomo Tufano 18/01/2011
			//inseriti creatore della query e primario
			$form=str_replace("<!--primario-->", $dati_equery['PRIMARIO'], $form);

			$farma_o_medico = (strlen($dati_equery['Q_USERID']) == 8)? 'F':'M';
			$q_nuserid = $dati_equery['Q_NUSERID']." (".$dati_equery['Q_USERID'].")"." (<font color='red'>". $farma_o_medico ."</font>)";
			$form=str_replace("<!--q_nuserid-->", $q_nuserid, $form);
			$html.="
				<p class=titolo>eQuery n. {$in['ID']}</p>

			$form


			";

		}

		if ($dati_equery==null){

			if (
			isset($in['CENTER']) && $in['CENTER']!='' &&
			isset($in[$config_service['PK_SERVICE']]) && $in[$config_service['PK_SERVICE']]!='' &&
			isset($in['VISITNUM']) && $in['VISITNUM']!='' &&
			isset($in['ESAM']) && $in['ESAM']!='' &&
			isset($in['PROGR']) && $in['PROGR']!='' &&
			isset($in['SALVA_EQUERY']) && $in['SALVA_EQUERY']!='' &&
			isset($in['QUESTION']) && $in['QUESTION']!=''
			){


				$sql_query="select max(ID) as maxid from {$this->config['service']}_equery";
				$sql=new query($this->conn);
				$sql->set_sql($sql_query);
				$sql->exec();
				$sql->get_row();
				$maxid=$sql->row['MAXID']-0;
				$maxid++;
				$values['ID']=$maxid;
				$values['QUEST_DT']="sysdate";
				$values['Q_USERID']=$in['remote_userid'];
				$values['CENTER'] = $in['CENTER'];
				$values['CODPAT'] = $in['CODPAT'];
				$values['VISITNUM'] = $in['VISITNUM'];
				$values['ESAM'] = $in['ESAM'];
				$values['PROGR'] = $in['PROGR'];
				$values['TIPO_EQUERY'] = $in['TIPO_EQUERY'];
				$values['QUESTION'] = $in['QUESTION'];
				$values['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
				$values['REGISTRY'] = $in['REGISTRY'];

				$table="{$this->config['service']}_equery";
				$pk['ID']='';
				$sql=new query($this->conn);
				$sql->insert($values, $table, $pk, true);
				$this->conn->commit();

				// Notifiche mail, nuova equery
				if($this->notifica)$this->notifica_equery(1,$maxid);

				die("<html><head><meta http-equiv=\"refresh\" content=\"0;url=index.php?eQuery\"></head></html>");
			}
			$sql=new query($this->conn);
			$sql_envio_scheda="";
			//			  echo $in[$config_service['PK_SERVICE']]."<hr>".$in['VISITNUM']."<hr>".$in['ESAM']."<hr>".$in['PROGR'];
			if ($in[$config_service['PK_SERVICE']]!=''&&$in['VISITNUM']!=''
			&&$in['ESAM']!=''){
				if ($in['VISITNUM_PROGR']=='') $in['VISITNUM_PROGR']=0;
				if ($in['PROGR']=='') $in['PROGR']=1;

				$sql_envio_scheda="select
						to_char(insertdt,'DD/MM/YYYY') insertdt,
						to_char(moddt,'DD/MM/YYYY') moddt
					from {$service}_coordinate
					where
				{$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}
					and abilitato=1
					and visitnum={$in['VISITNUM']}
					and visitnum_progr={$in['VISITNUM_PROGR']}
					and esam={$in['ESAM']}
					and progr={$in['PROGR']}";
// 				echo $sql_envio_scheda."<hr>";
				$sql->set_sql($sql_envio_scheda);
				$sql->exec();
				$sql->get_row();
				$insertAux=$sql->row['INSERTDT'];
				$modificaAux=$sql->row['MODDT'];
			
				if($modificaAux=='')
				$data_envio_scheda=$insertAux;
				else
				$data_envio_scheda=$modificaAux;
			}
			//echo $data_envio_scheda."<hr>";
			$r1ch=$r2ch="";
			if ($in['TIPO_EQUERY']=='1') $r1ch="checked";
			if ($in['TIPO_EQUERY']=='2') $r2ch="checked";
			$tipo_equery="		<input type='radio' name='TIPO_EQUERY' value='1' $r1ch><b>".$this->testo("eQueryType1")."</b><br>
													<input type='radio' name='TIPO_EQUERY' value='2' $r2ch><b>".$this->testo("eQueryType2")."</b>";
			//				echo "<hr".$tipo_equery;
			$sql_invio="select to_char(sysdate,'dd/mm/yyyy') INVIO from dual";
			$sql->set_sql($sql_invio);
			$sql->exec();
			$sql->get_row();
			$data_invio=$sql->row['INVIO'];
			$sql_query="select  wf.* from workflow wf where prefix='{$this->service}WF'";
			$sql_wf=new query($this->conn);
			$sql_wf->get_row($sql_query);
			$question="<textarea name=\"QUESTION\" cols=\"80\" ROWS=\"10\"></textarea>";
			$form= file_get_contents($this->getXMRPath("templates_dir","equery_question.htm").'/'."equery_question.htm");

			$form=str_replace("<!--study-->", "<input type=\"hidden\" value='{$sql_wf->row['ID']}'>", $form);
			$form=str_replace("<!--data_invio-->", $data_invio, $form);
			$form=str_replace("<!--tipo_equery-->", $tipo_equery, $form);
			$form=str_replace("<!--data_invio_scheda-->", $data_envio_scheda, $form);
			$form=str_replace("<!--visualizza_scheda-->",$link_html, $form);

			$form=str_replace("<!--centro-->", $this->eCenterList(), $form);
			$form=str_replace("<!--paziente-->", $this->ePatientList(), $form);
			$form=str_replace("<!--visita-->", $this->eVisitList(), $form);
			$form=str_replace("<!--esame-->", $this->eEsamList(), $form);
			$form=str_replace("<!--question-->", $question, $form);
			if($this->config_service['lang']=='en'){
				$html.="
				<p class=titolo>".$this->testo ( 'newEq' )."</p>
				<form method=post action=\"index.php\">
				$form
				<p align=center>
						<input type='submit' name='SALVA_EQUERY' onclick=\"
							if (document.forms[0].CENTER.value=='') {
								alert('It\\'s necessary to select a centre');
								return false;
							}
							if (document.forms[0].TIPO_EQUERY.value=='') {
								alert('It\\'s necessary to select a type');
								return false;
							}
							if (document.forms[0].{$config_service['PK_SERVICE']}.value=='') {
								alert('It\\'s necessary to select a patient');
								return false;
							}
							if (document.forms[0].VISITNUM.value=='') {
								alert('It\\'s necessary to select a visit');
								return false;
							}
							if (document.forms[0].ESAM.value=='') {
								alert('It\\'s necessary to select an exam');
								return false;
							}
							if (document.forms[0].QUESTION.value=='') {
								alert('Insert the question');
								return false;
							}
						\" value='Send eQuery'> &nbsp;
						<input type='reset' value='Cancel'>
					</p>
				</form>
			";
			}
			else
			$html.="
				<p class=titolo>Nuova eQuery</p>
				<form method=post action=\"index.php\">
			$form
				<p align=center>
						<input type='submit' name='SALVA_EQUERY' onclick=\"
							if (document.forms[0].CENTER.value=='') {
								alert('E\\' necessario selezionare un centro');
								return false;
							}
							if (!document.forms[0].TIPO_EQUERY[0].checked && !document.forms[0].TIPO_EQUERY[1].checked) {
								alert('E\\' necessario selezionare un tipo');
								return false;
							}
							if (document.forms[0].{$config_service['PK_SERVICE']}.value=='') {
								alert('E\\' necessario selezionare un paziente');
								return false;
							}
							if (document.forms[0].VISITNUM.value=='') {
								alert('E\\' necessario selezionare una visita');
								return false;
							}
							if (document.forms[0].ESAM.value=='') {
								alert('E\\' necessario selezionare un esame');
								return false;
							}
							if (document.forms[0].QUESTION.value=='') {
								alert('Inserire la domanda');
								return false;
							}
						\" value='Invia eQuery'> &nbsp;
						<input type='reset' value='Annulla'>
					</p>
				</form>
			";
		}
		//href=\"index.php?eQuery&eform\";
		return $html;
	}


	function eCenterList() {
		//		global $xml_dir;
		//		global $in;
		//		global $config_service;
		//		global $service;
		// 		$xml_dir = $this->xml_dir;
		$in = $this->session_vars;
		$service = $this->service;
		$config_service = $this->config_service;

		//da filtrare con solo centri che hanno pazienti
		$sql_query = "select  distinct c.* from {$service}_centri c, {$service}_utenti_centri uc where uc.userid='{$in['remote_userid']}' and uc.center=c.center ";
		if ($in['FIXED']=='Y')
		$sql_query = "select  distinct c.* from {$service}_centri c, {$service}_utenti_centri uc where uc.center like '%{$in['CENTER']}' and uc.center=c.center ";
		$sql = new query ( $this->conn );
		//$sql->set_sql ( $sql_query );
		unset($bind);
		$bind['USERID']=$in['remote_userid'];
		$sql->exec ($sql_query,$bind);//binded
		$options = '';
		if ($sql->numrows > 1) {

			while ( $sql->get_row () ) {
				if (isset ( $in ['CENTER'] ) && $in ['CENTER'] == $sql->row ['CENTER'])
				$selected = "selected";
				else
				$selected = '';
				$options .= "
						<option value='{$sql->row['CENTER']}' $selected>{$sql->row['DENOM']} {$sql->row['CITTA']}</option>
						";
			}
			$centro = "
					<select name='CENTER' onchange='document.forms[0].submit();'>
						<option value=''></option>
						" . $options . "
						</select>";
		} else {
			$sql->get_row ();
			$centro = "<b>{$sql->row['DENOM']}</b><input type='hidden' name='CENTER' value='{$sql->row['CENTER']}'>";

		}
		//Logger::send($centro);
		return $centro;
	}
	function ePatientList() {
		//		global $xml_dir;
		//		global $in;
		//		global $service;
		//		global $config_service;
		// 		$xml_dir = $this->xml_dir;
		$in = $this->session_vars;
		$service = $this->service;
		$config_service = $this->config_service;

		$in = $this->session_vars;

		if ($this->session_vars ['CENTER'] != '') {
			$reg_form = new xml_form ( $this->conn, $this->xmr_root->prefix );

			$reg_form->xml_form_by_file ( $this->getXMRPath("xml_dir",$this->vlist_root->esams [0] [0] ['XML']) . "/" . $this->vlist_root->esams [0] [0] ['XML'] );
			$table_ana = $reg_form->form ['TABLE'];

			$sql_query = "
					select
						a.{$config_service['PK_SERVICE']}
					from $table_ana a , {$this->service}_coordinate coor
					where a.center=:center and a.{$config_service['PK_SERVICE']}=coor.{$config_service['PK_SERVICE']} and coor.esam=0
					order by {$config_service['PK_SERVICE']} asc";
			if ($in['FIXED']=='Y')
			$sql_query = "
					select
						a.{$config_service['PK_SERVICE']}
					from $table_ana a , {$this->service}_coordinate coor
					where a.center=:center and a.{$config_service['PK_SERVICE']}=coor.{$config_service['PK_SERVICE']} and coor.esam=0
					and a.{$config_service['PK_SERVICE']}='{$in['CODPAT']}'
					order by {$config_service['PK_SERVICE']} asc";
			unset($bind_center);
			$bind_center['CENTER']=$in['CENTER'];
			$sql = new query ( $this->conn );
			$sql->exec ($sql_query,$bind_center);//binded

			$options = '';
			if ($sql->numrows >= 1) {
				while ( $sql->get_row () ) {
					//					print_r($sql->row);
					if (isset ( $in [$config_service ['PK_SERVICE']] ) && $in [$config_service ['PK_SERVICE']] == $sql->row [$config_service ['PK_SERVICE']])
					$selected = "selected";
					else
					$selected = '';
					$options .= "
						<option value=\"{$sql->row[$config_service['PK_SERVICE']]}\" $selected>{$sql->row[$config_service['PK_SERVICE']]}</option>
						";
				}
				$paziente = "
					<select name=\"{$config_service['PK_SERVICE']}\" onchange=\"document.forms[0].submit();\">
						<option value=''></option>
						" . $options . "
						</select>";
			} else {
				if ($sql->numrows > 0) {
					$sql->get_row ();
					$in ['CENTER'] = $sql->row ['CENTER'];
					$paziente = "<b>{$sql->row[$config_service['PK_SERVICE']]}</b><input type=\"hidden\" name=\"{$config_service['PK_SERVICE']}\" value=\"{$in[$config_service['PK_SERVICE']]}\">";
				} else {
					$in [$config_service ['PK_SERVICE']] = '';
					$no_pat = "<b>" . $this->testo ( "noPatient" ) . "</b>";
					//					if($this->config_service['lang']=="en") {
					//						$no_pat="<b>There are no patients in this center</b>";
					//					} else {
					//						$no_pat="<b>Non ci sono pazienti registrati in questo centro</b>";
					//					}
					$paziente = $no_pat;
				}

			}
		}
		return $paziente;
	}


	function eEsamList(){
		// 		$xml_dir = $this->xml_dir;
		$in=$this->session_vars;
		$service=$this->service;
		$config_service=$this->config_service;

		if (!isset($in[$config_service['PK_SERVICE']]) || $in[$config_service['PK_SERVICE']]==''){
			return "";
		}
		if (isset($in['VISITNUM']) && $in['VISITNUM']!=''){
			$vlist=$this->vlist;

			$in_condition = "(";
			foreach ($vlist->esams[$in['VISITNUM']] as $esam_detail){
				$in_condition .= "'".$esam_detail['NUMBER']."', ";
			}
			$in_condition = rtrim($in_condition,", ").")";

			//Esame
			$sql_query="select
						distinct esam
					from {$service}_coordinate
					where {$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}
					and abilitato=1
					and fine=1
					and visitnum={$in['VISITNUM']}
					and visitnum_progr={$in['VISITNUM_PROGR']}
					and esam IN $in_condition
					order by esam asc";
			if ($in['FIXED']=='Y')
			$sql_query="select
						distinct esam
					from {$service}_coordinate
					where {$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}
					and abilitato=1
					and fine=1
					and visitnum={$in['VISITNUM']}
					and visitnum_progr={$in['VISITNUM_PROGR']}
					and esam ={$in['ESAM']}
					order by esam asc";
			$sql= new query($this->conn);
			$sql->set_sql($sql_query);
			$sql->exec();
			$options="";
			if ($sql->numrows>0){
				while ($sql->get_row()){
					if (isset($in['ESAM']) && $in['ESAM']==$sql->row['ESAM']) $selected="selected";
					else $selected='';
						
					$options.="
						<option value=\"{$sql->row['ESAM']}\" $selected>{$vlist->esams[$in['VISITNUM']][$sql->row['ESAM']]['TESTO']}</option>";
				}
				$esame="
					<select name=\"ESAM\" onchange=\"document.forms[0].submit();\">
						<option value=\"\"></option>
				$options
					</select>
				";
			}
			else {
				$sql->get_row();
				$in['ESAM']=$sql->row['ESAM'];
				$esame="
						<b>{$vlist->esams[$in['VISITNUM']][$sql->row['ESAM']]['TESTO']}</b>
						<input type=\"hidden\" name=\"ESAM\" value=\"{$in['ESAM']}\">
						";
			}
		}

		if (isset($in['VISITNUM']) && $in['VISITNUM']!='' && isset($in['ESAM']) && $in['ESAM']!=''){
			$sql_query="
					select
						distinct progr
					from {$service}_coordinate
					where
			{$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}
					and abilitato=1
					and visitnum={$in['VISITNUM']}
					and visitnum_progr={$in['VISITNUM_PROGR']}
					and esam={$in['ESAM']}
					order by progr asc";
			$sql= new query($this->conn);
			$sql->set_sql($sql_query);
			$sql->exec();
			$options="";
			//					print_R($in);
			if ($this->vlist->esams[$in['VISITNUM']][$in['ESAM']]['PROGR']=='yes'){
				//					if ($sql->numrows>1){
				while ($sql->get_row()){
					if (isset($in['PROGR']) && $in['PROGR']==$sql->row['PROGR']) $selected="selected";
					else $selected='';
					$options.="
						<option value=\"{$sql->row['PROGR']}\" $selected>{$sql->row['PROGR']}</option>";
				}
				$progressivo="
							</td>
						</tr>
						<tr>
							<td class=destra>
								<b>Esame n.ro</b>
							</td>
							<td class=input>
								<select name=\"PROGR\" onchange=\"document.forms[0].submit();\">
									<option value=\"\"></option>
				$options
								</select>
				";
			}
			else {
				$sql->get_row();
				$in['PROGR']=$sql->row['PROGR'];
				$progressivo="
						<input type=\"hidden\" name=\"PROGR\" value=\"{$in['PROGR']}\">
						";
			}
		}
		return $esame.$progressivo;
	}



	function eVisitList(){
		//		global $xml_dir;
		//		global $in;
		//		global $service;
		//		global $config_service;
		// 		$xml_dir = $this->xml_dir;
		$in=$this->session_vars;
		$service=$this->service;
		$config_service=$this->config_service;
		//		if (!isset($in['REGISTRY']) || $in['REGISTRY']=='' || $this->session_vars[$this->config_service['PK_SERVICE']]==''){
		//			return "";
		//		}
		//Visita
		//	if (isset($in['REGISTRY']) && $in['REGISTRY']!=''){
		if ($this->session_vars['CODPAT']!=''){
			/*$str="select prefix from workflow where id={$in['STUDY']}";
			 $sql_study=new query($this->conn);
			$sql_study->get_row($str);
			$prefix=substr($sql_study->row['PREFIX'],0,strlen($sql_study->row['PREFIX'])-2);

			if($prefix==$this->xmr->prefix){
			$vlist=$this->vlist;
			}
			else{
			//				print_r($this->xmr);
			$vlist= new xml_esams_list ( $this->xml_dir . '/' .$prefix.'/'. $this->visit_structure_xml,$config,$this->session_vars, $this->conn);;
			}*/
			$vlist=$this->vlist;

			$sql_query="
					select
						distinct visitnum
					from {$this->service}_coordinate
					where {$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}
					and abilitato=1
					and fine=1
					order by visitnum asc";
			if ($in['FIXED']=='Y')
			$sql_query="
					select
						distinct visitnum
					from {$this->service}_coordinate
					where {$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}
					and abilitato=1
					and fine=1
					AND visitnum={$in['VISITNUM']}
					order by visitnum asc";
			$sql= new query($this->conn);
			$sql->set_sql($sql_query);
			$sql->exec();
			$options="";
			if ($sql->numrows>0){
				while ($sql->get_row()){
					if (isset($in['VISITNUM']) && $in['VISITNUM']==$sql->row['VISITNUM']) $selected="selected";
					else $selected='';
					$options.="
						<option value=\"{$sql->row['VISITNUM']}\" $selected>{$vlist->visitnums[$sql->row['VISITNUM']]['TEXT']}</option>";
				}
				$visita="
					<select name=\"VISITNUM\" onchange=\"document.forms[0].submit();\">
						<option value=\"\"></option>
				$options
					</select>
				";
			}
			else {
				$sql->get_row();
				$in['VISITNUM']=$sql->row['VISITNUM'];
				$visita="
						<b>{$vlist->visitnums[$sql->row['VISITNUM']]['TEXT']}</b>
						<input type=\"hidden\" name=\"VISITNUM\" value=\"{$in['VISITNUM']}\">
						";

			}
		}
		return $visita;
		}

		private function inviaMessaggioAiPartecipanti($in,$config_service){
			$sql=new query($this->conn);
			$Where="";
			$bind=array();
			$bind['NOVENOVESETTE'] = '997';

			if ($in['MEDICI']=="1"){
				$Where.="( ana_utenti_1.userid in (select distinct userid from {$this->service}_utenti_centri where userid not like :novenovesette || '%') and ana_utenti_1.farma is not null)";
			}

			if ($in['AIFA']=="1"){
				if ($Where!="")
				$Where.=" OR ";
				$Where.="(ana_utenti_1.userid LIKE :novenovesette || '%')";
			}

			if ($in['FAR']=="1"){
				if ($Where!="")
				$Where.=" OR ";
				$Where.="( ana_utenti_1.userid in (select distinct farma from ana_utenti_1 where farma is not null) )";
			}

			//non ho selezionato  nulla, blocco l'invio
			if ($Where == ''){
				die("<html><body>Impossibile inviare il messaggio.
							<br />Selezionare almeno un destinatario!<br />
							<a href=\"javascript:history.back();\">Indietro</a></body></html>");
			}

			//SETTO I PARAMETRI DI INVIO MAIL
			$destinatari = array();
			$avvisi = '';
			$oggetto=$in['SUBMSG'];
			$testo_mail=$in['TXTMSG'];
			$in['TXTMSG']=preg_replace("/'/", "''", $in['TXTMSG']);
			$in['SUBMSG']=preg_replace("/'/", "''", $in['SUBMSG']);
			$from="From: help@cineca.it".PHP_EOL;
				
			if ($oggetto=="")
			$oggetto="Registro farmaci {$this->config_service['nome_registro']} - {$this->config_service['nome_farmaco']}";
				
			//DESTINATARI
			$sql_q="SELECT DISTINCT rtrim(ltrim(email)) as EMAIL, userid  from ana_utenti_1 where ".$Where;
			// 			echo print_r($bind,true)."<hr />$sql_q<hr>";die();
			$sql->exec($sql_q,$bind);
			$avvisi = 'Mail non valide: <ul>';
			while ($sql->get_row()){
				$pattern = "/^([\w\!\#$\%\&\'\*\+\-\/\=\?\^\`{\|\}\~]+\.)*[\w\!\#$\%\&\'\*\+\-\/\=\?\^\`{\|\}\~]+@((((([a-z0-9]{1}[a-z0-9\-]{0,62}[a-z0-9]{1})|[a-z])\.)+[a-z]{2,6})|(\d{1,3}\.){3}\d{1,3}(\:\d{1,5})?)$/i";

				if(preg_match($pattern,$sql->row['EMAIL'])){
					$destinatari[] = $sql->row['EMAIL'];
				}
				else
				$avvisi .= '<li>'.$sql->row['USERID'].' --> "'.$sql->row['EMAIL'].'"</li>';
			}
				
			$avvisi .= '</ul> Destinatari: '. implode(", ", $destinatari) ;
				
			//SE SONO ONLINE
			if((preg_match("/agenziafarmaco/i",$_SERVER['SERVER_NAME']))){
				$toarr = $destinatari;
			}
			//ALTRIMENTI IN TEST LA MANDO SOLO A NOI
			else{
				$toarr = array($this->config_service['email_admin']);
				$oggetto= 'TEST - ' . $oggetto ;
			}
				

			// 			foreach ($in as $key => $val)
			// 			{
			// 				$in[$key]=str_replace("'", "''", $in[$key]);
				// 				//echo "$key: $in[$key]<hr>";
				// 			}
			$query=new query($this->conn);
			$sql_q="select MSG_ID.nextval prossimo from DUAL";

			$query->exec($sql_q);
			$query->get_row();

			$in['MSG_ID']=$query->row['PROSSIMO']+1;
				
			$sql_q="select COLUMN_NAME,DATA_TYPE from user_tab_columns where table_name=upper(:tabella) order by column_name";
			$bind = array();
			$bind['TABELLA'] = $this->service.'_MESSAGGI';
			$query->exec($sql_q,$bind);
				
			while ($query->get_row())
			{
				$qval=$query->row['COLUMN_NAME'];
				//echo $qval."<hr>";
				$st_campi.=$qval.",";
				if ($query->row['DATA_TYPE']=='DATE'){
					if ($qval=='INVIO_DT')
					{
						$st_valori.="sysdate,";
					}
					else
					{
						$st_valori.="to_date('$in[$qval]','DDMMYYYY'),";
					}
				}
				else{
					$st_valori.="'$in[$qval]',";
				}
			}
				
			$st_campi = substr("$st_campi", 0, -1);
			//echo $st_campi."<hr>";
			$st_valori = substr("$st_valori", 0, -1);
			// 			echo $st_valori."<hr>";die();
			//TODO mettere il binding
			$sql="insert into {$this->service}_MESSAGGI ($st_campi) values ($st_valori)";

			$query->exec($sql);
			$this->conn->commit();
				
			//salvo l'allegato se presente
			if ($_FILES['ATAMSG']['error'] === 0){
				//TODO capire se posso usare $this->uploaded_file_dir
				$dir='';
				$paths=explode("/", $_SERVER['PATH_TRANSLATED']);

				for ($i=0;$i<count($paths)-1; $i++){
					$dir.=$paths[$i]."/";
				}
				$dir .='uploaded_file/';

				$filename=$_FILES['ATAMSG']['name'];
				$file_to_write= $dir . "MSG_ATTACH_".$in['MSG_ID'];

				if (!move_uploaded_file($_FILES['ATAMSG']['tmp_name'], $file_to_write))
				die("ERRORE COPIA ALLEGATO $file_to_write ".$_FILES['ATAMSG']['tmp_name']);
				$in['ATAMSG']=$file_to_write;
				$in['D_ATAMSG']=$filename;

				$attach_src = $in['ATAMSG'];
				$attach_name = $in['D_ATAMSG'];
				// 			$filenameorg=$in['D_ATAMSG'];

				$attach = array(array('src' => $attach_src, 'name' => $attach_name));
			}
			else
			$attach = false;
				
				
			include_once 'libs/Mail.php';
				
			//IMPOSTARE NEL CONFIG QUESTI PARAMETRI
			$from_service_email = $config_service ['from_service_email'];
			$from_service_name = $config_service ['from_service_name'];
				
			$reply_to = $config_service ['from_service_email'];
				
			//spezzo l'array dei destinatari in blocchi da 10. per evitare che la mail non arrivi per troppi destinatari
			$to_array = array_chunk($toarr,10);
				
			foreach($to_array as $to){
				// 				send_email_advanced($to, $from, $from_name, $subject, $message, $reply_to, $attachments , $cc , $bcc)
				$dest_bcc = implode(',',$to);
				$esito = send_email_advanced(null, $from_service_email, $from_service_name, $oggetto, $testo_mail, $reply_to, $attach, null, $dest_bcc);
				if ($esito ===false){
					$avvisi .= "<li>Invio mail fallito: $dest_bcc</li>";
				}
				sleep(2);
			}
				
			//infine invio il resoconto dell'invio se richiesto
			if ($in['RESOCONTO'] == "1"){

				$sql_q="select email from ana_utenti_1 where userid= :userid";
				$bind = array();
				$bind['USERID'] = $in['remote_userid'];
				$query->exec($sql_q,$bind);

				$query->get_row();
				$oggetto =  'Resoconto invio messaggio nr. '.$in['MSG_ID'];
				$testo_mail = 'CORPO MESS INVIATO<hr />'.$testo_mail.'<hr />'.'AVVISI:'.$avvisi;
				$to = $query->row['EMAIL'];

				send_email_advanced($to, $from_service_email, $from_service_name,$oggetto, $testo_mail, $reply_to, $attach, null,null);
			}
				
			// 			for ($k=0;$k<$i;$k++) {mail ($toarr[$k], $oggetto, $testo_mail,$from);}
				
				
			$body="<br><bR><bR>
		<p align=\"center\"><b><font size=\"4\">
		Messaggio inviato correttamente</font></b></p>"; //.
					"<br><br><a href=\"index.php?list=messag_list.xml\">Visualizza messaggi inviati </a><br><br>
		<a href='index.php'>Home</a><br><br>";
			echo $body;
			//TODO correggere con obclean
			die("<html><head><meta http-equiv=\"refresh\" content=\"3;url=index.php\"></head></html>");
		}


}



?>