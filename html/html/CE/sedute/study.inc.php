<?php

/**
 * Classe Studio
 * 
 * Contiene tutte le spcifiche dello studio tra cui il Controller
 *
 * @package XMR 2.0
 */
class Study extends Study_mproto {

function Study($xml_dir=null, $service=null, $visit_structure_xml=null, $conn=null, $session_vars=null, $config_service=null, $user=null, $configure = false, $workflow_name = null,$xmr=null,$mxmr=null) {
		parent::Study_prototype_mxmr($xml_dir, $service, $visit_structure_xml, $conn, $session_vars, $config_service, $user, $configure , $workflow_name,$xmr,$mxmr);
		

		if ($this->getProfilo($this->user->userid)=='CMP' && isset($this->pk_service) && $this->pk_service!='next'){
			
			$this->visit_structure_xml='visite_exams_cmp.xml';
			$this->VisitStructure ();
			
		}

		if ($_GET ['DEBUG'] == 1) echo $this->visit_structure_xml;
		
	}

	/*
	function listPage(){
	    $prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
	    $list = str_replace ( ".xml", "_{$prof_add}.xml", $list );
		
	    die ($this->session_vars ['WFact']);
	}
	*/
	
	var $show_gantt = false;
	
	var $dettaglio;
	
	function tb_riassuntiva(){
		$profilo = $this->getProfilo($this->user->userid);
		$output_odg="";
		$output = "";
		$output .= '<table class="table table-striped table-bordered table-hover">';
		$output .= '<thead id="tb_riass">';
		$output .= '<tr>';
		$output .= '<th class="int" height="26">ID</td>';
		$output .= '<th class="int">Tipologia seduta</th>';
		$output .= '<th class="int">Data</th>';
		$output .= '<th class="int">Orario</th>';
		$output .= '<th class="int center">Ultimo OdG pubblicato</th>';
		$pdf="ODG non pubblicato";
		
		#Prendo direttamente il file odg_$id_sed.pdf
		//if (file_exists(realpath('../gendocs/documents/odg_'.$this->dettaglio[$this->xmr->pk_service].'.pdf'))){
		//	$pdf = '<a target="_blank" href="/gendocs/documents/odg_'.$this->dettaglio[$this->xmr->pk_service].'.pdf"><img src="/images/pdf_small.png" alt="PDF ODG" title="PDF ODG" /></a>';
		//}
		
		#Prendo l'ultimo OdG inviato ai componenti
		$query_count_conv_odg="select FILE_PDF from {$this->service}_CRONOLOGIA_ODG where {$this->xmr->pk_service}={$this->pk_service} and progr=(select max(progr) from {$this->service}_CRONOLOGIA_ODG where {$this->xmr->pk_service}={$this->pk_service} and userid_invio_odg is not null and invio_odg_dt is not null)";
		$sql_conv_odg=new query ( $this->conn );
		$sql_conv_odg->set_sql($query_count_conv_odg);
		$sql_conv_odg->exec();
		$sql_conv_odg->get_row();
		if($sql_conv_odg->row['FILE_PDF']){
			$pdf = '<a target="_blank" href="/gendocs/documents/'.$sql_conv_odg->row['FILE_PDF'].'"><img src="/images/pdf_small.png" alt="PDF ODG" title="PDF ODG" /></a>';
			ini_set('date.timezone', 'Europe/Rome');
			$pdf_filename_odg='../gendocs/documents/'.$sql_conv_odg->row['FILE_PDF'];
			$pdf_date = (date ("d/m/Y H:i:s", filemtime($pdf_filename_odg)));
		}
		
		$td_odg= '<td class="int center">'.$pdf.'<br>'.$pdf_date.'</td>';
		
		$date_bozza_file = "";
		$link_bozza_file = "bozza non salvata";
		if (file_exists(realpath('../gendocs/documents/odg_'.$this->dettaglio[$this->xmr->pk_service].'.pdf'))){
			$filename_bozza_odg='../gendocs/documents/odg_'.$this->dettaglio[$this->xmr->pk_service].'.pdf';
			ini_set('date.timezone', 'Europe/Rome');
			$date_bozza_file = (date ("d/m/Y H:i:s", filemtime($filename_bozza_odg)));
			$link_mod_bozza_file='<a href="index.php?CENTER='.$this->session_vars['CENTER'].'&ID_SED='.$this->pk_service.'&VISITNUM=0&ESAM=10&PROGR=1&form=creazione_odg.xml"><img src="/images/pen.png" alt="Modifica PDF ODG" title="Modifica PDF ODG" /></a>';
			$link_bozza_file='<a target="_blank" href="/gendocs/documents/odg_'.$this->dettaglio[$this->xmr->pk_service].'.pdf"><img src="/images/pdf_small.png" alt="PDF ODG" title="PDF ODG" /></a>';
			$pdf_bozza_file=$link_mod_bozza_file.'&nbsp;/&nbsp;'.$link_bozza_file.'<br>'.$date_bozza_file;
		}
		
		#Ultima bozza OdG Segreteria
		//if($this->getProfilo($this->user->userid)=='SGR'){
		//		$output_odg.='
		//			<tr>
		//				<td class="sc4bis"> Ultima bozza OdG segreteria</td>
		//				<td class="sc4bis"> Draft </td>
		//				<td class="sc4bis center"> '.$pdf_bozza_file.' </td>
		//				<td class="sc4bis"> Non prevista </td>
		//				<td class="sc4bis"> Non prevista </td>
		//			</tr>
		//			';
		//}
		
		if ($this->dettaglio['STATO_INT'] >=4){
			$output .= '<th class="int">Verbale</th>';
			$verb = "Verbale non salvato";
			if (file_exists(realpath('../gendocs/documents/verbale_'.$this->dettaglio[$this->xmr->pk_service].'.pdf'))){
				$verb = '<a target="_blank" href="/gendocs/documents/verbale_'.$this->dettaglio[$this->xmr->pk_service].'.pdf"><img src="/images/pdf_small.png" alt="PDF Verbale" title="PDF Verbale" /></a>';
			}
			$td_verbale .= '<td class="int">'.$verb.'</td>';
		}else	$td_verbale="";
		if ($this->dettaglio['STATO_INT'] >=4 && $profilo == "SGR"){
			//LUIGI modal window for confirmations 
			$output .= '<th class="int">Conferme</th>';
			$output .= '<th class="int">Webconference</th>';
		}
		$output .= '</tr>';
		$output .= '</thead>';
		$output .= '<tr>';
		$output .= '<td class="sc4bis"><a href="?clista=studi&'.$this->xmr->pk_service.'='.$this->dettaglio[$this->xmr->pk_service].'" id="field_sed_id">'.$this->dettaglio[$this->xmr->pk_service].'</a></td>';
		$output .= '<td class="sc4bis" id="field_sed_tipo" >'.$this->dettaglio['D_TIPO_SED'].'</td>';
		$output .= '<td class="sc4bis" id="field_sed_data" >'.$this->dettaglio['DATA_SED_DT'].'</td>';
		$orario = sprintf("%02d:%02d - %02d:%02d", $this->dettaglio['ORA_INIZIO_H'], $this->dettaglio['ORA_INIZIO_M'], $this->dettaglio['ORA_FINE_H'], $this->dettaglio['ORA_FINE_M']);
		$output .= '<td class="sc4bis" id="field_sed_ora" >'.$orario.'</td>';
		$output .= $td_odg;
		$output .= $td_verbale;
		if ($this->dettaglio['STATO_INT'] >=4 && $profilo == "SGR"){
			//LUIGI modal window for confirmations 
			$output .= '<td class="int" rowspan="2" valign="middle" align="center" height="60" width="90" ><a href="#" onclick="dialog();"><img src="/images/confirm.png" width="28px"></img><br>Visualizza</a></td>';
			//var_dump($this->dettaglio);
			if ($this->dettaglio['MEETING_URL']){
				$output .= '<td class="int" rowspan="2" valign="middle" align="center" height="60" width="90" ><a href="https://vcs.adobeconnect.com'.$this->dettaglio['MEETING_URL'].'" target="_blank" >https://vcs.adobeconnect.com'.$this->dettaglio['MEETING_URL'].'</a></td>';
			}else{
				$output .= '<td class="int" rowspan="2" valign="middle" align="center" height="60" width="90" ><button class="btn btn-info" type="button" onclick="return creaTeleconference('.$this->dettaglio[$this->xmr->pk_service].');" >Avvia</button></td>';
			}
		}
		$output .= '</tr>';
		$output .= '</table>';
		
		//LUIGI modal window for confirmations 
		$componenti='';
		$componenti_1='';
		$componenti_2='';
		$sql_query_c="select * from GSE_SEL_COMPONENTI where id_sed={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql_c=new query($this->conn);
		$sql_c->exec($sql_query_c);
		$sql_c->get_row();
		$cnv[0] = $this->getArray($sql_c,"CONVOCAZIONI_CONFERMATE");
		$cnv[1] = $this->getArray($sql_c,"CONVOCAZIONI_RESPINTE");
		for ($i = 0; $i<2; $i++){
			foreach ($cnv[$i] as $p){
				$nome = $this->getDatiUtente2($p);	
				$sql_query_p="select * from GSE_MOTIV_COMPONENTI where id_sed={$this->pk_service} and userid='{$p}'";
				$sql_p=new query($this->conn);
				$sql_p->exec($sql_query_p);
				$sql_p->get_row();
				#componenti confermati
				if($i==0){
					$componenti_1.="<li>".$nome['QUALIFICA']." ".$nome['NOME']." ".$nome['COGNOME']." <i> ".$nome['RUOLO']."</i><br>Motivazione: {$sql_p->row['MOTIVAZIONE']}</li>";
				}
				#componenti respinti
				if($i==1){
					$componenti_2.="<li>".$nome['QUALIFICA']." ".$nome['NOME']." ".$nome['COGNOME']." <i> ".$nome['RUOLO']."</i><br>Motivazione: {$sql_p->row['MOTIVAZIONE']}</li>";
				}
			}
		}
		
		$output .= "<div id=\"dialog\" style=\"display:none;\" title=\"componenti che hanno confermato\">
					<p><b>Hanno confermato la presenza:</b><br>
					{$componenti_1}<br><br>
					<b>Hanno respinto la presenza:</b><br>
					{$componenti_2}
					</p>
					</div>";
		$stato = $this->dettaglio['STATO_INT'];
		$profilo = $this->getProfilo($this->user->userid);
		
		
		$query_invio_odg="select INVIO_ODG_DT from {$this->service}_CRONOLOGIA_ODG where {$this->xmr->pk_service}={$this->pk_service} and progr=(select max(progr) from {$this->service}_CRONOLOGIA_ODG where {$this->xmr->pk_service}={$this->pk_service})";
		$sql_inv_odg=new query ( $this->conn );
		$sql_inv_odg->set_sql($query_invio_odg);
		$sql_inv_odg->exec();
		$sql_inv_odg->get_row();
		
		
		if (strtoupper($this->service) == "GSE" && $sql_inv_odg->row['INVIO_ODG_DT']!='' && $profilo == "CMP"){
			$status = $this->vlist->getCalendarStatus($this->pk_service);
			//echo "ST:$status - ".CAL_RICHIESTO."<br/>";
			if ($status == CAL_RICHIESTO){
				$output.='<br/>';			
				$output.='<table border="0" cellpadding="0" cellspacing="0" align="center"><tr><td style="text-align: center;">';
				//$redir = "https://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
				//$this->body .= $this->PK_SERVICE;
				$redir_p = "index.php?{$this->xmr->pk_service}={$this->pk_service}&Presente=yes&"; //Prima visita di default
				$redir_a = "index.php?{$this->xmr->pk_service}={$this->pk_service}&Assente=yes&"; //Prima visita di default
				//print_r($this); //$pk = $_GET[''];
				//$output.='<input type="button" onclick="location.href=\''.$redir_p.'\'" value="Conferma Presenza" />';
				$output.='&nbsp;&nbsp;&nbsp;';
				$output.="<textarea id=\"testo_motivazione\" rows=\"3\" cols=\"50\" placeholder=\"Inserire qui la motivazione\" maxlength=\"200\"></textarea><br><br>";
				$output.='<button class="btn btn-info" type="button" onclick="location.href=\''.$redir_p.'motivazione=\'+$(\'textarea#testo_motivazione\').val()+\'\'">
										<i class="fa fa-lock bigger-110"></i>
										Conferma Presenza
									</button>';
				$output.='&nbsp;&nbsp;&nbsp;';
				//$output.='<input type="button" onclick="location.href='.$redir_a.'" value="Conferma Assenza" />';
				$output.='<button class="btn btn-danger" type="button" onclick="location.href=\''.$redir_a.'motivazione=\'+$(\'textarea#testo_motivazione\').val()+\'\' ">
										<i class="fa fa-trash bigger-110"></i>
										Conferma Assenza
									</button>';
				$output.='</td></tr></table>';
			}
		}
		
		#Tabellina OdG
		$datiUtente=$this->getDatiUtente2($this->user->userid);
		$sql_query_coord = "select * from {$this->service}_coordinate c where {$this->xmr->pk_service}={$this->pk_service} and VISITNUM=0 and VISITNUM_PROGR=0 and ESAM=11 order by progr";
		$sql_coord = new query ( $this->conn );
		$sql_coord->exec($sql_query_coord);
		while($sql_coord->get_row()){
			if($filename_bozza_odg){
				$richista_aut_presi="";
				$autorizzazione_presidente="";
				$invio_odg="";
				
				$sql_query = "select progr,tipo,d_tipo,file_pdf,userid_rich_aut,to_char(rich_aut_dt,'DD/MM/YYYY HH24:MI:SS') rich_aut_dt, userid_autorizzazione, to_char(autorizzazione_dt,'DD/MM/YYYY HH24:MI:SS') autorizzazione_dt, userid_invio_odg,to_char(invio_odg_dt,'DD/MM/YYYY HH24:MI:SS') invio_odg_dt from {$this->service}_cronologia_odg where {$this->xmr->pk_service}={$this->pk_service} and VISITNUM=0 and VISITNUM_PROGR=0 and ESAM=11 and PROGR={$sql_coord->row['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->exec($sql_query);
				$sql->get_row();
				$d_tipo=$sql->row['D_TIPO'];
				$versione=$sql->row['PROGR'];
				if($stato == 4 && (!$sql->row['USERID_RICH_AUT'] || !$sql->row['RICH_AUT_DT'])) continue;
				
				$file_pdf_odg="";
				#Se ho gia' inviato la conv/integr -> mostro il pdf reale
				if($sql->row['FILE_PDF']) {
					$file_pdf_odg='<a target="_blank" href="/gendocs/documents/'.$sql->row['FILE_PDF'].'"><img src="/images/pdf_small.png" alt="PDF ODG" title="PDF ODG"></a>';
					$nomefile=$sql->row['FILE_PDF'];
					if (file_exists(realpath('../gendocs/documents/'.$nomefile))){
						$filename_odg='../gendocs/documents/'.$nomefile;
						ini_set('date.timezone', 'Europe/Rome');
						$date_file = (date ("d/m/Y H:i:s", filemtime($filename_odg)));
						$link_file='<a target="_blank" href="/gendocs/documents/'.$nomefile.'"><img src="/images/pdf_small.png" alt="PDF ODG" title="PDF ODG" /></a>';
						$file_pdf_odg=$link_file."<br>".$date_file;
					}
				}
				#Se non ho ancora inviato la conv/integr -> mostro il pdf bozza
				else{
					if($profilo == "SGR" || ($profilo == "CMP" && ($datiUtente['MEMO']=="Presidente" || $datiUtente['MEMO']=="Vicepresidente"))) $file_pdf_odg=$pdf_bozza_file;
				}
				
				#Richista autorizzazione Presidente
				if((!$sql->row['USERID_RICH_AUT'] || !$sql->row['RICH_AUT_DT'])){
					
					if($sql->row['TIPO']=='2') $tr_id="integrazione_open";
					
					if($profilo == "SGR"){
						$redir_rap = "index.php?{$this->xmr->pk_service}={$this->pk_service}&RichAutoPresi=yes&PROGR={$sql->row[PROGR]}";
						$richista_aut_presi='<button class="btn btn-warning" onclick="if(confirm(\'Proseguire con l\\\'invio della mail al presidente?\'))location.href=\''.$redir_rap.'\'" type="button">
																	<i class="fa fa-envelope bigger-110"></i>
																		Richiedi Autorizzazione
																 </button>';
					}else if ($profilo == "CMP" && ($datiUtente['MEMO']=="Presidente" || $datiUtente['MEMO']=="Vicepresidente")){
						$richista_aut_presi='';
					}
					else continue;
				}
				
				#Rilascio autorizzazione Presidente
				if($sql->row['USERID_RICH_AUT'] && $sql->row['RICH_AUT_DT']){
					$richista_aut_presi="<i class='icon-ok bigger-110 green'></i>Richiesta in data {$sql->row['RICH_AUT_DT']}";
					$autorizzazione_presidente="<br><i class='icon-ok bigger-110 green'></i>Autorizzata in data {$sql->row['AUTORIZZAZIONE_DT']}";
					if(!$sql->row['USERID_AUTORIZZAZIONE'] || !$sql->row['AUTORIZZAZIONE_DT']){
						if($profilo == "SGR"){
								$autorizzazione_presidente="<br><i class='icon-warning-sign bigger-110 orange'></i> Attesa di autorizzazione";
						}
						if(($profilo == "CMP" && ($datiUtente['MEMO']=="Presidente" || $datiUtente['MEMO']=="Vicepresidente")) || $profilo == "SGR"){
							$redir_aut = "index.php?{$this->xmr->pk_service}={$this->pk_service}&AutoPresidente=yes&PROGR={$sql->row[PROGR]}";
							$autorizzazione_presidente='<br><button class="btn btn-info" type="button" onclick="location.href=\''.$redir_aut.'\'">
																					 	<i class="fa fa-lock bigger-110"></i>
																						Autorizza
																					 </button>';
						}
						if($profilo == "CMP" && !($datiUtente['MEMO']=="Presidente" || $datiUtente['MEMO']=="Vicepresidente")) continue;
					}
				}
				
				#Notifica ai componenti
				if($sql->row['USERID_AUTORIZZAZIONE'] && $sql->row['AUTORIZZAZIONE_DT']){
					$invio_odg="<i class='icon-ok bigger-110 green'></i>Inviata in data {$sql->row['INVIO_ODG_DT']}";
					if(!$sql->row['USERID_INVIO_ODG'] || !$sql->row['INVIO_ODG_DT']){
						if($profilo == "SGR"){
							$redir_nc = "index.php?{$this->xmr->pk_service}={$this->pk_service}&SendMailCompConv=yes&PROGR={$sql->row[PROGR]}";
							$invio_odg='
							<button class="btn btn-warning" onclick="if(confirm(\'Proseguire con l\\\'invio della mail ai componenti?\'))location.href=\''.$redir_nc.'\'" type="button">
								<i class="fa fa-envelope bigger-110"></i>
								Notifica ai componenti
							</button>
							';
						}
						if($profilo == "CMP" && ($datiUtente['MEMO']=="Presidente" || $datiUtente['MEMO']=="Vicepresidente")){
							$invio_odg="<i class='icon-warning-sign bigger-110 orange'></i> Attesa di notifica ai componenti";
						}
						if($profilo == "CMP" && !($datiUtente['MEMO']=="Presidente" || $datiUtente['MEMO']=="Vicepresidente")) continue;
					}
				}
				
				$output_odg.='
					<tr id='.$tr_id.'>
						<td class="sc4bis">'.$d_tipo.'</td>
						<td class="sc4bis">'.$versione.'</td>
						<td class="sc4bis center">'.$file_pdf_odg.'</td>
						<td class="sc4bis center">'.$richista_aut_presi.$autorizzazione_presidente.'</td>
						<td class="sc4bis center">'.$invio_odg.'</td>
					</tr>
				';
			}
		}
		
		#Per vedere la tabella espolsa di default togliere 'collapsed' dal secondo div e settare 'icon-chevron-up'
		#Per vedere la tabella chiusa  di default mettere 'collapsed' al secondo div e settare 'icon-chevron-down'
		$output.='<div>
								<div class="widget-box transparent">
									<div class="widget-header widget-header-flat">
										<h6 class="lighter">
											<i class="icon-time"></i>
											Cronologia OdG
											<a data-action="collapse" href="#">
												<i class="icon-chevron-up"></i>
											</a>								
										</h6>
									</div>	
									<div class="widget-body">
										<div class="widget-main no-padding">
											<table class="table table-bordered table-striped">
												<thead class="thin-border-bottom">
													<tr>
														<th>
															<i class="icon-caret-right blue"></i>
															Tipologia
														</th>
														<th>
															<i class="icon-caret-right blue"></i>
															Versione
														</th>
														<th class="hidden-480">
															<i class="icon-caret-right blue"></i>
															Modifica / Visualizza
														</th>
														<th class="hidden-480">
															<i class="icon-caret-right blue"></i>
															Autorizzazione Presidente
														</th>
														<th class="hidden-480">
															<i class="icon-caret-right blue"></i>
															Convocazione/Integrazione ai componenti
														</th>
													</tr>
												</thead>
												<tbody>
													'.$output_odg.'
												</tbody>
											</table>
										</div>
									</div>
								</div>
							</div>';
		
		return $output;
	}

		function CheckVisione() {
  		
		parent::CheckVisione();
		
		//GIULIO 14-11-2012 Gestione della riassegnazione dei profili DE e RO
		if (isset($this->pk_service) && $this->pk_service!='next'){

			if($this->session_vars['DEBUG']==1) print_r($this->session_vars);
			
			if(isset($this->session_vars['ID_STUD']) && $this->session_vars['VISITNUM'] == 1 && $this->session_vars['ESAM'] == 1){
				$agg_and_centro="";
				if($this->session_vars['PROGR_CENTRO']) $agg_and_centro="and progr_centro={$this->session_vars['PROGR_CENTRO']}";
				$sql_query = "select USERID_INS from {$this->service}_relazioni where {$this->xmr->pk_service}={$this->pk_service} and VISITNUM=1 and ESAM=1 and userid_ins='{$this->session_vars['remote_userid']}' and id_stud={$this->session_vars['ID_STUD']} $agg_and_centro";
				$sql = new query ( $this->conn );
				$sql->get_row ( $sql_query );
				//echo $sql_query;
				$user_control=$sql->row ['USERID_INS'];
				
				//Il componente passa da RO a DE nel caso in cui debba inserire la sua relazione allo studio. Non puo' scrivere sulle relazioni di altri componenti (raggiungibili dal TAB RELAZIONI/OSSERVAZIONI) 
				if(($user_control==$this->session_vars['remote_userid'] || !$user_control) && $this->session_vars ['USER_TIP'] == 'RO' && $this->user->profilo=='Componente CE') {$this->session_vars ['USER_TIP'] = 'DE';}
			}
			if(isset($this->session_vars['ID_SED']) && $this->session_vars['VISITNUM'] == 1 && $this->session_vars['ESAM'] == 1){
				
				//La segreteria deve essere sempre RO sulle schede di Relazioni
				if($this->session_vars['WFact']!='Componente CE')	{$this->session_vars ['USER_TIP'] = 'RO';}
				
			}
			
			if(isset($this->session_vars['ID_STUD']) && $this->session_vars['VISITNUM'] == 1 && $this->session_vars['ESAM'] == 2){
				$agg_and_centro="";
				if($this->session_vars['PROGR_CENTRO']) $agg_and_centro="and progr_centro={$this->session_vars['PROGR_CENTRO']}";
				$sql_query = "select USERID_INS from {$this->service}_osservazioni where {$this->xmr->pk_service}={$this->pk_service} and VISITNUM=1 and ESAM=2 and userid_ins='{$this->session_vars['remote_userid']}' and id_stud={$this->session_vars['ID_STUD']} $agg_and_centro";
				$sql = new query ( $this->conn );
				$sql->get_row ( $sql_query );
				//echo $sql_query;
				$user_control=$sql->row ['USERID_INS'];
				
				//Il componente passa da RO a DE nel caso in cui debba inserire un'osservazione allo studio. Puo' modificare solo proprie osservazioni (raggiungibili anche dal TAB RELAZIONI/OSSERVAZIONI) 
				if(($user_control==$this->session_vars['remote_userid'] || !$user_control) && $this->session_vars ['USER_TIP'] == 'RO' && $this->user->profilo=='Componente CE') {$this->session_vars ['USER_TIP'] = 'DE';}
			}
			if(isset($this->session_vars['ID_SED']) && $this->session_vars['VISITNUM'] == 1 && $this->session_vars['ESAM'] == 2){
				
				//La segreteria deve essere sempre RO sulle schede di Relazioni
				if($this->session_vars['WFact']!='Componente CE')	{$this->session_vars ['USER_TIP'] = 'RO';}
				
			}
			
		}
		
	}
	
	function Controller(){
		
//		if ($_GET['VISITNUM'] == 1){
//			//Insert in coordinate
//			$profilo = $this->getProfilo($this->user->userid);
//			switch ($profilo){
//				case "CMP":
//					$this->session_vars ['USER_TIP'] = "DE";
//					break;
//				default:
//					break;
//			}
//			//print_r($this->user);
//			//die();
//		}
		if (isset($_GET['MEETING_URL']) && isset($_GET[$this->xmr->pk_service]) && is_numeric($this->pk_service)){
			$murl = str_replace("'","''",$_GET['MEETING_URL']);
			$mscoid = str_replace("'","''",$_GET['MEETING_SCOID']);
			$sql_insert_meeting="update {$this->service}_registrazione SET MEETING_URL='{$murl}', MEETING_SCOID='{$mscoid}' WHERE {$this->xmr->pk_service}={$this->pk_service} ";
			$sql=new query($this->conn);
			$sql->set_sql($sql_insert_meeting);
			$sql->ins_upd();
			
			$this->conn->commit();
			
			header("location: /sedute/index.php?&exams=visite_exam.xml&ID_SED={$this->pk_service}");
			die();
		}
		
		if (isset($_GET['PARAM_REDIR_REL']) && $_GET['PARAM_REDIR_REL']=="yes"){
			
			$sql=new query($this->conn); 
			
			if($this->session_vars['ESAM']==1) $tab_rel="relazioni";
			if($this->session_vars['ESAM']==3) {
				$tab_rel="relazioni_eme";
				 $field_vprogr_eme=",VPROGR_EME";
				 $vprogr_eme=", {$this->session_vars['VPROGR_EME']}";
				 $field_progr_val_eme=",PROGR_VAL_EME";
				 $progr_val_eme=", {$this->session_vars['PROGR_VAL_EME']}";
			}
			
			$sql_query="select * from {$this->service}_$tab_rel where {$this->xmr->pk_service}={$this->pk_service} and visitnum=1 and esam={$this->session_vars['ESAM']} and userid_ins='{$this->session_vars['remote_userid']}' and id_stud={$this->session_vars['ID_STUD']} and progr_centro='{$this->session_vars['PROGR_CENTRO']}'";
			Logger::send($sql_query);
			$sql->exec($sql_query);

			#se trovo il record
			if($sql->get_row()){
				$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&ESAM={$this->session_vars['ESAM']}&VISITNUM=1&VISITNUM_PROGR=0&PROGR={$sql->row['PROGR']}&ID_STUD={$this->session_vars['ID_STUD']}";
				header ( "location:$location" );
			}
			#se il record non esiste
			else{
				$progr = $this->NextProgrRelazione($this->pk_service,$this->session_vars['ESAM']);
				$sql_insert_coord="insert into gse_coordinate(visitnum,visitnum_progr,progr,esam,inizio,fine,insertdt,moddt,userid,visitclose,inv_query,id_sed,abilitato,eq_action) values ({$this->session_vars['VISITNUM']},{$this->session_vars['VISITNUM_PROGR']},$progr,{$this->session_vars['ESAM']},'','',sysdate,'','{$this->session_vars['remote_userid']}',0,'',{$this->session_vars['ID_SED']},1,'') ";
				$sql->set_sql($sql_insert_coord);
				$sql->ins_upd();
				
				$sql_insert_rel="insert into {$this->service}_$tab_rel(id_sed,userid_ins,esam,progr,visitnum,visitnum_progr,center,id_stud,progr_centro) values ({$_GET['ID_SED']},'{$this->session_vars['remote_userid']}',{$this->session_vars['ESAM']},$progr,{$this->session_vars['VISITNUM']},{$this->session_vars['VISITNUM_PROGR']},{$this->session_vars['CENTER']},{$this->session_vars['ID_STUD']},'{$this->session_vars['PROGR_CENTRO']}') ";
				Logger::send($sql_insert_rel);
				$sql->set_sql($sql_insert_rel);
				$sql->ins_upd();
				
				$this->conn->commit();
				
				$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&ESAM={$this->session_vars['ESAM']}&VISITNUM=1&VISITNUM_PROGR=0&PROGR=$progr&ID_STUD={$this->session_vars['ID_STUD']}";
				header ( "location:$location" );
				}
			
		}

		if (isset($_GET['PARAM_REDIR_OSS']) && $_GET['PARAM_REDIR_OSS']=="yes"){
			
			$sql=new query($this->conn); 
			
			if($this->session_vars['ESAM']==2) $tab_oss="osservazioni";
			if($this->session_vars['ESAM']==4){
				 $tab_oss="osservazioni_eme";
				 $field_vprogr_eme=",VPROGR_EME";
				 $vprogr_eme=", {$this->session_vars['VPROGR_EME']}";
				 $field_progr_val_eme=",PROGR_VAL_EME";
				 $progr_val_eme=", {$this->session_vars['PROGR_VAL_EME']}";
			}
			
			$sql_query="select * from {$this->service}_$tab_oss where {$this->xmr->pk_service}={$this->pk_service} and visitnum=1 and esam={$this->session_vars['ESAM']} and userid_ins='{$this->session_vars['remote_userid']}' and id_stud={$this->session_vars['ID_STUD']} and progr_centro='{$this->session_vars['PROGR_CENTRO']}'";
			$sql->exec($sql_query);

			#se trovo il record
			if($sql->get_row()){
				$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&ESAM={$this->session_vars['ESAM']}&VISITNUM=1&VISITNUM_PROGR=0&PROGR={$sql->row['PROGR']}&ID_STUD={$this->session_vars['ID_STUD']}";
				header ( "location:$location" );
			}
			#se il record non esiste
			else{
				$progr = $this->NextProgrOsservazione($this->pk_service,$this->session_vars['ESAM']);
				
				$sql_insert_coord="insert into gse_coordinate(visitnum,visitnum_progr,progr,esam,inizio,fine,insertdt,moddt,userid,visitclose,inv_query,id_sed,abilitato,eq_action) values ({$this->session_vars['VISITNUM']},{$this->session_vars['VISITNUM_PROGR']},$progr,{$this->session_vars['ESAM']},'','',sysdate,'','{$this->session_vars['remote_userid']}',0,'',{$this->session_vars['ID_SED']},1,'') ";
				$sql->set_sql($sql_insert_coord);
				$sql->ins_upd();
				
				$sql_insert_rel="insert into {$this->service}_$tab_oss(id_sed,userid_ins,esam,progr,visitnum,visitnum_progr,center,id_stud,progr_centro) values ({$_GET['ID_SED']},'{$this->session_vars['remote_userid']}',{$this->session_vars['ESAM']},$progr,{$this->session_vars['VISITNUM']},{$this->session_vars['VISITNUM_PROGR']},{$this->session_vars['CENTER']},{$this->session_vars['ID_STUD']},'{$this->session_vars['PROGR_CENTRO']}' ) ";
				$sql->set_sql($sql_insert_rel);
				$sql->ins_upd();
				
				$this->conn->commit();
				
				$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&ESAM={$this->session_vars['ESAM']}&VISITNUM=1&VISITNUM_PROGR=0&PROGR=$progr&ID_STUD={$this->session_vars['ID_STUD']}";
				header ( "location:$location" );
				}
			
		}
		
		if (isset($_GET['clista']) && $_GET['clista']=="studi"){
			$this->body = $this->ListaStudi();
		}
		
		parent::Controller();

		define("PRESENTE","2");
		define("ASSENTE","3");
	
		
		if (isset($_GET['Presente'])){
			//echo "-- {$this->session_vars['remote_userid']} --";
			//die(print_r($this->session_vars));
			$data['TAB'] = "SEL_COMPONENTI";
			$data['RICHIESTA'] = "CONVOCAZIONI";
			$data['CONFERMA'] = "CONVOCAZIONI_CONFERMATE";
			$data['RIFIUTO'] = "CONVOCAZIONI_RESPINTE";
			$data['USER'] = $this->session_vars['remote_userid'];
			$data['VID'] = 0;
			$data['MOTIVAZIONE'] = $_GET['motivazione'];
			$this->ConfermaRiunione(PRESENTE, $data);
			//TODO: Ricarico pagina visita
		}
		
		if (isset($_GET['Assente'])){
			//echo "-- {$this->session_vars['remote_userid']} --";
			//die(print_r($this->session_vars));
			$data['TAB'] = "SEL_COMPONENTI";
			$data['RICHIESTA'] = "CONVOCAZIONI";
			$data['CONFERMA'] = "CONVOCAZIONI_CONFERMATE";
			$data['RIFIUTO'] = "CONVOCAZIONI_RESPINTE";
			$data['USER'] = $this->session_vars['remote_userid']; //$this->userid;
			$data['VID'] = 0;
			$data['MOTIVAZIONE'] = $_GET['motivazione'];
			$this->ConfermaRiunione(ASSENTE, $data);
			//TODO: Ricarico pagina visita
		}
		
		if (isset($_GET['RichAutoPresi'])){
			
			$tab_rel="CRONOLOGIA_ODG";
			$id_sed=$this->session_vars['ID_SED'];
			$vnum=0;
			$vnum_progr=0;
			$esam=11;
			$progr=$this->session_vars['PROGR'];
			
			$mode=2; #integrazione
			if($progr==1) $mode=1; #convocazione 
			$source_path="../gendocs/documents";
			$source_file=$source_path."/odg_{$id_sed}.pdf";
			$dest_file="odg_{$id_sed}_{$mode}_{$progr}.pdf";
			if(file_exists(realpath($source_file)))
			system ("cp $source_file $source_path/$dest_file");
			
			$insert_crono="update {$this->service}_$tab_rel set CENTER='{$this->session_vars['CENTER']}', TIPO='{$mode}', FILE_PDF='{$dest_file}', USERID_RICH_AUT='{$this->session_vars['remote_userid']}' ,RICH_AUT_DT=SYSDATE where ID_SED={$id_sed} and VISITNUM={$vnum} and VISITNUM_PROGR={$vnum_progr} and ESAM={$esam} and PROGR={$progr}";
			//die($insert_crono);
			$sql_crono=new query($this->conn);
			$sql_crono->set_sql($insert_crono);
			$sql_crono->ins_upd();
			
			$this->conn->commit();
			
			$this->SendMailComp(5); #Mail al presidente
			
			$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&VISITNUM=0&exams=visite_exams.xml";
			header ( "location:$location" );
			}
		
		if (isset($_GET['AutoPresidente'])){
			
			#New
			$tab_rel="CRONOLOGIA_ODG";
			$id_sed=$this->session_vars['ID_SED'];
			$vnum=0;
			$vnum_progr=0;
			$esam=11;
			$progr=$this->session_vars['PROGR'];
			$insert_crono="update {$this->service}_$tab_rel set userid_autorizzazione='{$this->session_vars['remote_userid']}',autorizzazione_dt=SYSDATE where ID_SED={$id_sed} and VISITNUM={$vnum} and VISITNUM_PROGR={$vnum_progr} and ESAM={$esam} and PROGR={$progr}";
			//die($insert_crono);
			$sql_crono=new query($this->conn);
			$sql_crono->set_sql($insert_crono);
			$sql_crono->ins_upd();
			
			$this->conn->commit();
			
			$this->SendMailComp(6); #Mail alla segreteria
			
			$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&VISITNUM=0&exams=visite_exams.xml";
			header ( "location:$location" );
			
		}
		
		if (isset($_GET['RichiestaIntegrazioneOdG'])){
			$this->RichiestaIntegrazioneOdG($this->session_vars['ID_SED']);
		}
		
		if (isset($_GET['azzera_fcn'])){
			$out = $this->$_GET['azzera_fcn']();
			die ($out);
		}
		
		
		////////// --- MUTUATI DA OSSC --- ////////				
		
		if (isset($_GET['DocSed'])){
			$this->DocumentazioneSeduta();
			$this->body.="<a href=\"index.php\">&lt;&lt;Torna alla home del sistema</a>";
		}
		
		if (isset($_GET['CalSed'])){
			$this->ShowCalendar(@date("m"),@date("Y"));
		}
		
		if (isset($_GET['InsSed'])){
			$this->ins_riunione();
		}
		
		if (isset($_GET['VisCal'])){
			$this->vis_riunione();
		}
		
		if (isset($_GET['ModSed'])){
			$this->mod_riunione();
		}
		
		if (isset($_GET['CanSed'])){
			$this->canc_riunione();
		}
		
		if (isset($_GET['SendMailCompConv'])){
			$this->SendMailComp(1,$this->session_vars['PROGR']);
		}
		
		if (isset($_GET['SendMailCompIntegra'])){
			$this->SendMailComp(2);
		}
		
		if (isset($_GET['SendMailCompVerb'])){
			$this->SendMailComp(4);
		}
		
	}

	function ConfermaRiunione($operation, $data){
		$sql=new query($this->conn); 
		$sql_query="select * from {$this->service}_{$data['TAB']} where {$this->xmr->pk_service}={$this->pk_service} and visitnum={$data['VID']}"; // and esam=1";
		$sql->exec($sql_query);
		$richiesta = array();
		$conferma = array();
		$rifiuto = array();
		$userid = $data['USER'];
		
		echo "PARAMS: ($operation)($userid) - ".PRESENTE."-".ASSENTE."<br/>";
		if ($userid)
		{
			if ($sql->get_row()){
				$richiesta = $sql->row[$data['RICHIESTA']];
				$richiesta = explode("|",$richiesta);
				$conferma = $sql->row[$data['CONFERMA']];
				$conferma = explode("|",$conferma);
				$rifiuto = $sql->row[$data['RIFIUTO']];
				$rifiuto = explode("|",$rifiuto);
			}
			echo "QUA.";
			//Check dati e iscrizione in base all'operazione da eseguire
			if (in_array($userid, $richiesta)){
				$bind['MOTIVAZIONE']=$data['MOTIVAZIONE'];
				//Se ero richiesto...
				echo "RICHIESTO ($operation)($userid) - ".PRESENTE."-".ASSENTE;
				switch ($operation){
					case PRESENTE:
						if (!in_array($userid,$conferma) && !in_array($userid,$rifiuto)){
							$sql_close="update {$this->service}_{$data['TAB']} set {$data['CONFERMA']} = {$data['CONFERMA']} || '|{$userid}' WHERE {$this->xmr->pk_service}={$this->pk_service} and visitnum={$data['VID']}";
							$sql->set_sql($sql_close);
							$sql->ins_upd();
							//LUIGI MOTIVAZIONE
							$sql_insert="insert into GSE_MOTIV_COMPONENTI VALUES({$this->pk_service} , '{$userid}' , 0, :MOTIVAZIONE , SYSDATE)";
							$sql->ins_upd($sql_insert,$bind);
							echo "PRESENTE!";
						}
						break;
					case ASSENTE:
						print_r($conferma);
						print_r($rifiuto);
						if (!in_array($userid,$conferma) && !in_array($userid,$rifiuto)){
							$sql_close="update {$this->service}_{$data['TAB']} set {$data['RIFIUTO']} = {$data['RIFIUTO']} || '|{$userid}' WHERE {$this->xmr->pk_service}={$this->pk_service} and visitnum={$data['VID']}";
							$sql->set_sql($sql_close);
							$sql->ins_upd();
							
							//LUIGI MOTIVAZIONE
							$sql_insert="insert into GSE_MOTIV_COMPONENTI VALUES({$this->pk_service} , '{$userid}' , 1, :MOTIVAZIONE , SYSDATE)";
							$sql->ins_upd($sql_insert,$bind);
							echo "ASSENTE!";
						}
						break;
					default:
						echo "DEFAULTING";
						break;
				}
			}else{
				echo "NON ERO RICHIESTO!";
			}
		
			//die($sql_close);
			//Chiudo e ridireziono
			$this->conn->commit();
		}
		//print_r($this);
		//die("FINE");
		$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&exams";
		header ( "location:$location" );
				
		
	}
		
	//WORKFLOW
	function StatusChangePostOperation($dest) {
		//$dest ?'id dello stato destinazione
		//Operazioni dopo transizione di stato nel WF
		$sql=new query($this->conn); 
		define("STATO_INVIATA","4");
		define("VERBALIZZATA","5");
		
		switch ($dest){
			case STATO_INVIATA:
				//Invio mail + sms + apertura visita?
				//Flag studio in seduta
				$vid = 0;
				$sql_query="select * from {$this->service}_sel_studi where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid"; // and esam=1";
				$sql->exec($sql_query);
				$studi = "";
				$campi = array();
				$campi[] = "STUDI";
				$campi[] = "STUDI_EMENDAMENTI";
				$campi[] = "STUDI_SOSPESI";
				$campi[] = "STUDI_AGGIORNAMENTI";
				//echo "<pre>";
				if ($sql->get_row()){
					foreach ($campi as $campo){
						$studi = $sql->row[$campo];
						//echo("STUDISTRING: ".$studi."\n");
						if ($studi){
							$studi = explode("|",$studi);
							//print_r($studi);
							//foreach ($studi as $s){
							for ($k = 0; $k<count($studi);$k++){
								$s = $studi[$k];
								$s = trim($s);
								
								$stud_center = explode("_",$s);
								$id_stud=$stud_center[0];
								$param_center=$stud_center[1];
								
								//echo "PRINT_R";
								//print_r($s);
								//echo "\n---\n";
								//echo("$s<br/>");
								if ($s != ""){
									$k++;//Salto un record (?'utente)...
									$sql_close="update ce_registrazione set in_seduta = 1 where id_stud = {$id_stud} ";
									$sql->set_sql($sql_close);
									//echo("$sql_close<br/>");
									$sql->ins_upd();
								}
							}
						}
					}
				}
				//echo "</pre>";
				
				//Apertura visita valutazione
				$vid = 2;
				//Controllo visita aperta
				$open = array();
				$open[] = 1;
				$open[] = 2;
				$open[] = 10;
				
				#GC 16/02/2016 TOSCANA-3 - Area documentale per verbale firmato
				$open[] = 20;
				$this->openVisit($vid,$open);

				//$this->SendMailComp(3);

				break;
				
			case VERBALIZZATA:
			
				//$this->SendMailComp(4);
				
				$sql_close="update {$this->service}_coordinate set fine = 1 where {$this->xmr->pk_service}={$this->pk_service} and visitnum=1 ";
				$sql->set_sql($sql_close);
				echo("$sql_close<br/>");
				$sql->ins_upd();
			
			break;
		}
		
		$this->conn->commit();
		
		$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&exams";
		header ( "location:$location" );
		
		return;
	}
	
	function SendMailComp($mode,$param1=null){
					$query_info_sed="select * from gse_registrazione where id_sed = {$this->pk_service} ";
					$sql_info_sed=new query($this->conn); 
					$sql_info_sed->exec($query_info_sed);
					$sql_info_sed->get_row();
					$ora = sprintf("%02d:%02d", $sql_info_sed->row['ORA_INIZIO_H'], $sql_info_sed->row['ORA_INIZIO_M']);
					$luogo=$sql_info_sed->row['LUOGO'];
					
					$sql_query="select * from gse_sel_componenti where id_sed = {$this->pk_service} ";
					$sql=new query($this->conn); 
					$sql->exec($sql_query);
					$dval = "";
					
					if ($sql->get_row()){
						$dval = $sql->row['CONVOCAZIONI'];
						$dval = explode("|",$dval);
						$components='';
						foreach ($dval as $key=>$val){
							if ($val!=''){
								$components.="'";
								$components.=$val;
								$components.="'";
								$components.=',';
							}
						}
						$components=rtrim($components,',');
						$components=ltrim($components,',');
						//print ($components);
						$sql_query = "select email from ana_utenti where userid in ($components)";
						$sql->exec($sql_query);
						$to="";
						while($sql->get_row()){
							if ($sql->row ['EMAIL']!=''){
								$to.= $sql->row ['EMAIL'];
								$to.=",";
							}
						}
						
						#Metto in cc la segreteria che ha premuto il bottone di invio alert ai componenti nella pagina di OdG
						$query_email = "select email,id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}'";
						$sql_mail=new query($this->conn);
						$sql_mail->exec($query_email);
						$sql_mail->get_row();
						//$cc=$sql_mail->row['EMAIL'];
						$id_ce=$sql_mail->row['ID_CE'];
						
						#Mail Presidente
						$sql_query = "select email from ana_utenti_2 where PROFILO='CMP' and MEMO in ('Presidente','Vicepresidente') and id_ce={$id_ce}";
						$sql->exec($sql_query);
						$to_presi="";
						while($sql->get_row()){
							if ($sql->row ['EMAIL']!=''){
								$to_presi.= $sql->row ['EMAIL'];
								$to_presi.=",";
							}
						}
						
						#Mail Segreteria
						$sql_query = "select email from ana_utenti_2 where PROFILO='SGR' and id_ce={$id_ce}";
						$sql->exec($sql_query);
						$to_sgr="";
						while($sql->get_row()){
							if ($sql->row ['EMAIL']!=''){
								$to_sgr.= $sql->row ['EMAIL'];
								$to_sgr.=",";
							}
						}
                        //STSANSVIL-506 invio mail anche all'utente corrente
                        $sql_query = "select email from ana_utenti_1 where userid='{$this->session_vars['remote_userid']}'";
                        $sql->exec($sql_query);
                        while($sql->get_row()){
                            if ($sql->row ['EMAIL']!=''){
                                $to.= $sql->row ['EMAIL'];
                                $to_presi.=$sql->row ['EMAIL'];
                                $to_sgr.=$sql->row ['EMAIL'];
                            }
                        }
						$email_from="sirer@no-reply.it";
						if($luogo!='') $luogo="presso:&nbsp;".$luogo;
						
						#$bcc="g.contino@cineca.it";
						#$cc="g.contino@cineca.it";
						#$pattern = '/siss.*/'; #ambiente di devel o prep
						#if (preg_match($pattern,$_SERVER['HTTP_HOST'])) {
					  #}
						
						#Mail di convocazione ai componenti
						if($mode==1) {
							$oggetto="Convocazione Riunione Comitato Etico";
							$testo_mail.="{$sql_info_sed->row['DATA_SED_DT']} - {$sql_info_sed->row['D_TIPO_SED']}<br>La Segreteria del Comitato Etico ha inviato la convocazione per la riunione del giorno {$sql_info_sed->row['DATA_SED_DT']} alle ore $ora {$luogo}<br><br>
							Si prega di accedere alla riunione <a href=\"https://{$_SERVER['HTTP_HOST']}/sedute/index.php?&ID_SED={$this->pk_service}&clista=studi\">cliccando qui</a>&nbsp;
							per confermare la propria presenza ed inserire relazioni e/o osservazioni agli studi/emendamenti in seduta.";
							$progr=$param1;
							$storicizzato = $this->storicizza_odg($this->pk_service,0,0,11,$progr,$mode);
							if($storicizzato) 
								send_email($to, $email_from, $email_from, $oggetto, $testo_mail, null, false, $cc, $bcc);
						}
						
						#Mail di notifica integrazioni OdG ai componenti
						if($mode==2){
							$oggetto="Comitato Etico - Notifica integrazioni OdG ai componenti";
							$testo_mail.="{$sql_info_sed->row['DATA_SED_DT']} - {$sql_info_sed->row['D_TIPO_SED']}<br>La Segreteria del Comitato Etico ha integrato l'OdG della riunione del giorno {$sql_info_sed->row['DATA_SED_DT']}<br/><br/>
							Si prega di inserire le proprie relazioni e/o osservazioni <a href=\"https://{$_SERVER['HTTP_HOST']}/sedute/index.php?&ID_SED={$this->pk_service}&clista=studi\">cliccando qui</a>&nbsp;";
							$progr=$param1;
							$storicizzato = $this->storicizza_odg($this->pk_service,0,0,11,$progr,$mode);
							if($storicizzato) send_email($to, $email_from, $email_from, $oggetto, $testo_mail, null, false, $cc, $bcc);
						}
						
						#Chiusura OdG 
						//if($mode==3) {
						//	$oggetto="Nuova riunione Comitato Etico";
						//	$testo_mail.="La Segreteria del Comitato Etico ha inviato la convocazione per la riunione del giorno {$sql_info_sed->row['DATA_SED_DT']} alle ore $ora {$luogo}<br><br>
						//	Si prega di accedere alla riunione <a href=\"https://{$_SERVER['HTTP_HOST']}/sedute/index.php?&ID_SED={$this->pk_service}&clista=studi\">cliccando qui</a>&nbsp;
						//	per confermare la propria presenza ed inserire relazioni e/o osservazioni agli studi/emendamenti in seduta.";
						//}
						
						#Chiusura Verbale
						//if($mode==4) {
						//	$oggetto="Verbale riunione Comitato Etico";
						//	$testo_mail.="La Segreteria del Comitato Etico ha inserito il verbale della riunione del giorno {$sql_info_sed->row['DATA_SED_DT']} tenuta alle ore $ora {$luogo}<br><br>
						//	Si prega di accedere alla riunione <a href=\"https://{$_SERVER['HTTP_HOST']}/sedute/index.php?&ID_SED={$this->pk_service}&clista=studi\">cliccando qui</a>&nbsp;
						//	e prendere visione del verbale.";
						//}
						
						#Mail al Presidente per autorizzazione OdG
						if($mode==5){
							$oggetto="Comitato Etico - Richiesta autorizzazione OdG";
							$testo_mail.="{$sql_info_sed->row['DATA_SED_DT']} - {$sql_info_sed->row['D_TIPO_SED']}<br>La Segreteria del Comitato Etico ha inviato una richiesta di autorizzazione per l'OdG della riunione del giorno {$sql_info_sed->row['DATA_SED_DT']}<br/><br/>
							Si prega di inserire l'autorizzazione <a href=\"https://{$_SERVER['HTTP_HOST']}/sedute/index.php?&ID_SED={$this->pk_service}&clista=studi\">cliccando qui</a>&nbsp;";
							send_email($to_presi, $email_from, $email_from, $oggetto, $testo_mail, null, false, $cc, $bcc);
						}
						
						#Mail di ritorno a segreteria dopo autorizzazione Presidente
						if($mode==6){
							$oggetto="Comitato Etico - Notifica ricezione autorizzazione OdG da Presidente";
							$testo_mail.="{$sql_info_sed->row['DATA_SED_DT']} - {$sql_info_sed->row['D_TIPO_SED']}<br>Il Presidente del Comitato Etico ha rilasciato l'autorizzazione all'OdG per la riunione del {$sql_info_sed->row['DATA_SED_DT']}<br/><br/>
							Si prega di inviare l'OdG ai componenti <a href=\"https://{$_SERVER['HTTP_HOST']}/sedute/index.php?&ID_SED={$this->pk_service}&clista=studi\">cliccando qui</a>&nbsp;";
							send_email($to_sgr, $email_from, $email_from, $oggetto, $testo_mail, null, false, $cc, $bcc);
						}

					}
			
			$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&exams";
			header ( "location:$location" );
			
			return;
		
	}
	
	#GC 24/02/2016 (TOSCANA-24) Storicizzo OdG
	function storicizza_odg($id_sed,$vnum,$vnum_progr,$esam,$progr,$mode){
		$storicizzato=0;
		$tab_rel="CRONOLOGIA_ODG";
		
		//$source_path="../gendocs/documents";
		//$source_file=$source_path."/odg_{$id_sed}.pdf";
		//$dest_file="odg_{$id_sed}_{$mode}_{$progr}.pdf";
		if(file_exists(realpath($source_file))){
			//system ("cp $source_file $source_path/$dest_file");
			
			#Aggiorno registrazione
			$update_crono_reg="update {$this->service}_registrazione set attiva_verbalizzazione=1 where id_sed={$id_sed} and visitnum='0'";
			$sql_upd_crono_reg=new query($this->conn);
			$sql_upd_crono_reg->set_sql($update_crono_reg);
			$sql_upd_crono_reg->ins_upd();
			
			#Aggiorno coordinate
			$update_crono_coord="update {$this->service}_coordinate set inizio=1, fine=1, insertdt=SYSDATE ,moddt=SYSDATE ,userid='{$this->session_vars['remote_userid']}' where id_sed={$id_sed} and visitnum={$vnum} and visitnum_progr={$vnum_progr} and esam={$esam} and progr={$progr}";
			$sql_upd_crono_coord=new query($this->conn);
			$sql_upd_crono_coord->set_sql($update_crono_coord);
			$sql_upd_crono_coord->ins_upd();
			
			#Aggiorno i campi
			#$update_crono="update {$this->service}_$tab_rel set TIPO='{$mode}', FILE_PDF='{$dest_file}', USERID_INVIO_ODG='{$this->session_vars['remote_userid']}', INVIO_ODG_DT=SYSDATE where PROGR={$progr}";
			$update_crono="update {$this->service}_$tab_rel set USERID_INVIO_ODG='{$this->session_vars['remote_userid']}', INVIO_ODG_DT=SYSDATE where id_sed={$id_sed} and PROGR={$progr}";
			$sql_crono=new query($this->conn);
			$sql_crono->set_sql($update_crono);
			$sql_crono->ins_upd();
						
			$this->conn->commit();
			$storicizzato=1;
		}
		return $storicizzato;
	}
	
	function RichiestaIntegrazioneOdG($id_sed){
		$vnum=0;
		$vnum_progr=0;
		$esam=11;
		$mode=2;
		
		$next_progr=$this->getMaxProgr($id_sed,$vnum,$vnum_progr,$esam);
		$next_progr++;
		
		#Aggiorno registrazione
		$update_crono_reg="update {$this->service}_registrazione set attiva_verbalizzazione='' where id_sed={$id_sed} and visitnum='0'";
		$sql_upd_crono_reg=new query($this->conn);
		$sql_upd_crono_reg->set_sql($update_crono_reg);
		$sql_upd_crono_reg->ins_upd();
			
		#Inserisco il record della prossima integrazione
		$insert_crono_coord="insert into {$this->service}_coordinate(visitnum,visitnum_progr,progr,esam,inizio,fine,insertdt,moddt,userid,visitclose,id_sed,abilitato) values ({$vnum},{$vnum_progr},{$next_progr},{$esam},'','',SYSDATE,SYSDATE,'{$this->session_vars['remote_userid']}','0',{$id_sed},'1') ";
		$sql_crono_coord=new query($this->conn);
		$sql_crono_coord->set_sql($insert_crono_coord);
		$sql_crono_coord->ins_upd();
		
		#Inserisco in record anche in tabella dati
		$insert_crono_odg="insert into {$this->service}_cronologia_odg (id_sed,visitnum,visitnum_progr,esam,progr,userid_ins,tipo,d_tipo) values ({$id_sed},'{$vnum}','{$vnum_progr}','11','{$next_progr}','{$this->session_vars['remote_userid']}','2','Integrazione') ";
		$sql_crono_odg=new query($this->conn);
		$sql_crono_odg->set_sql($insert_crono_odg);
		$sql_crono_odg->ins_upd();
		
		$this->conn->commit();
		
		$location = "{$prefix}/sedute/index.php?{$this->xmr->pk_service}={$this->pk_service}&exams";
		header ( "location:$location" );
		
		return;
	}
	
	function wf_seduta_inviata(){
		//Controllo chiusura visita
		//Setto campo IN_SEDUTA di CE_REGISTRAZIONE a 1
		//Elimino studio da altre sedute eventuali non ancora chiuse.
		return $this->CheckVisitClosed("0");		
	}

	function wf_seduta_archiviata(){
		//Controllo chiusura visita
		return $this->CheckVisitClosed("2");		
	}
	
	/////FUNZIONI HELPER CONTENUTI
		function crea_ODG(){
		$txt = "";
		$sql=new query($this->conn);
		//$sql_query="select TO_CHAR(DATA_SED_DT,'DD-MM-YYYY') as DATA_SED_DT from {$this->service}_registrazione where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql_query="select * from {$this->service}_registrazione where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql->exec($sql_query);
		$data = "";
		$ora = "";
		$luogo = "";
		if ($sql->get_row()){
			$data = $sql->row['DATA_SED_DT'];
			$ora_inizio = sprintf("%02d:%02d", $sql->row['ORA_INIZIO_H'], $sql->row['ORA_INIZIO_M']);
			$ora_fine = sprintf("%02d:%02d", $sql->row['ORA_FINE_H'], $sql->row['ORA_FINE_M']);
			$luogo = $sql->row['LUOGO'];
		}
		

		$sql=new query($this->conn);
		$sql_query="select * from {$this->service}_sel_studi where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql->exec($sql_query);
		if($in['DEBUG']==1) {print $sql_query;}

		//$i = 0;
		$studi = "";
		if ($sql->get_row()){
			
			$studi = "";
			$studi = $sql->row['STUDI_SOSPESI'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				//print_r($studi);
				
//				#GC 06/05/2015# Ordino gli studi per delib_num 
//				#In teoria questo codice non serve piu' in quanto ordino giÃ  i risultati per delib_num nella scheda scelta_studi.xml
//				$studi_ordinati=array();
//				if($studi!=""){
//					
//					#ricavo tutti gli studi sospesi
//					for($cs=0;$cs<=count($studi);$cs++){
//						if($studi[$cs]!=""){
//							if(preg_match("/_/",$studi[$cs])){
//								//echo "studio ".$studi[$cs]."<br>";
//								$studio = $studi[$cs];
//								$studio = trim($studio);
//								$studio_tot = explode("_",$studio);
//								$id_stud=$studio_tot[0];		
//								$lista_studi.=$id_stud.",";
//							}
//							else{
//								$relatore[$studio]=$studi[$cs];
//								}
//						}
//					}
//					
//					#poi li ordino secondo il delib_num
//					$lista_studi=substr($lista_studi, 0, strlen($lista_studi)-1); #elimino gli ultimi caratteri
//					$query_sql_ordinamento="select id_stud from ce_reginvio where visitnum_progr = 0 and progr = 1 and id_stud in ($lista_studi) order by delib_num";
//					$sql_ord=new query($this->conn);
//					$sql_ord->exec($query_sql_ordinamento);
//					
//					#costruisco l'array ordinato ($studi_ordinati) a partire dall'array non ordinato ($studi)
//					while($sql_ord->get_row()){
//						
//						for($cs=0;$cs<=count($studi);$cs++){
//							//echo "<br>".$studi[$cs];
//							if($studi[$cs]!=""){
//								if(preg_match("/".$sql_ord->row['ID_STUD']."_/",$studi[$cs])){
//									array_push($studi_ordinati,$studi[$cs]);
//									array_push($studi_ordinati,$relatore[$studi[$cs]]);
//									
//								}
//							}
//						}
//					}
//					print_r($studi_ordinati);
//				}
//				#FINE
				
				
				$txt.= "<hr break><p align='center'><b><u>ELENCO MATERIALE IN VALUTAZIONE SEDUTA DEL ../../....</u></b></p>";
				$txt.= "<p><b><u>STUDI SOSPESI IN PRECEDENTI SEDUTE:</u></b></p>";
				$param='progr';
				$txt.= $this->elenco_studi_centri_ODG_relatore($studi,$param);
			}
			
			$txt.="<hr break>";
			
			$studi = "";
			$studi = $sql->row['STUDI'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				$txt .= "<p><b><u>VALUTAZIONE DEI NUOVI PROTOCOLLI DI STUDIO</u></b></p>";
				$param='progr';
				$new_studies=1;
				$txt.= $this->elenco_studi_centri_ODG_relatore($studi,$param,$new_studies);
			}

			$studi = "";
			$studi = $sql->row['STUDI_EMENDAMENTI'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				$txt .= "<hr break><p><b><u>EMENDAMENTI SOSTANZIALI</u></b></p>";
				$param2="STUDI_EMENDAMENTI";
				$txt.= $this->elenco_studi_eme_ODG($studi, $param2);
			}
			
			$studi = "";
			$studi = $sql->row['STUDI_EME_SOSP'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				$txt .= "<hr break><p><b><u>EMENDAMENTI SOSPESI</u></b></p>";
				$param2="STUDI_EME_SOSP";
				$txt.= $this->elenco_studi_eme_ODG($studi, $param2);
			}
			//GIULIO 10-01-2013 Il Gemelli non vuole queste info
			//$studi = "";
			//$studi = $sql->row['STUDI_AGGIORNAMENTI'];
			//$studi = explode("|",$studi);
			//$txt.= "<p><b>Ulteriori Aggiornamenti:</b></p>";
			//$txt.= $this->elenco_studi_ODG($studi);
			//
			//$studi = "";
			//$studi = $sql->row['STUDI_DATI_AMMIN'];
			//$studi = explode("|",$studi);
			//$txt.= "<p><b>Dati amministrativi:</b></p>";
			//$param='progr';
			//$txt.= $this->elenco_studi_centri_ODG($studi,$param);
			//
			//$studi = "";
			//$studi = $sql->row['STUDI_AVVIO'];
			//$studi = explode("|",$studi);
			//$txt.= "<p><b>Dati avvio:</b></p>";
			//$txt.= $this->elenco_studi_centri_ODG($studi,$param);
			//
			//$studi = "";
			//$studi = $sql->row['STUDI_CONCLUSIONE'];
			//$studi = explode("|",$studi);
			//$txt .= "<p><b>Dati conclusione:</b></p>";
			//$txt.= $this->elenco_studi_centri_ODG($studi,$param);
			//
			//$studi = "";
			//$studi = $sql->row['STUDI_SAE'];
			//$studi = explode("|",$studi);
			//$txt.= "<p><b>Ulteriori SAE:</b></p>";
			//$txt.= $this->elenco_studi_centri_ODG($studi,$param);
		}
		
		//$txt .= "<hr><p><b>Varie ed eventuali:</b></p>";
		
		return $txt;
	}
	
	
	function crea_ODG_intestazione(){
		$txt = "";
		$sql=new query($this->conn);
		//$sql_query="select TO_CHAR(DATA_SED_DT,'DD-MM-YYYY') as DATA_SED_DT from {$this->service}_registrazione where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql_query="select * from {$this->service}_registrazione where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql->exec($sql_query);
		$data = "";
		$ora = "";
		$luogo = "";
		if ($sql->get_row()){
			$data = $sql->row['DATA_SED_DT'];
			$ora_inizio = sprintf("%02d:%02d", $sql->row['ORA_INIZIO_H'], $sql->row['ORA_INIZIO_M']);
			$ora_fine = sprintf("%02d:%02d", $sql->row['ORA_FINE_H'], $sql->row['ORA_FINE_M']);
			$luogo = $sql->row['LUOGO'];
		}
		$txt="<table width='100%' border=0 cellspacing='0' cellpadding='2' border='0' align='center'>
						<tr>
							
							
							<td width='70%' valign='top'>
								<i>
								<div align='right'>
									../../....
								</div>
								
								<br/>
								
								<div align='left'>
									Prot. N.  ..../.... <br/>
									File:  Convocazione <br/>
								</div>
								
								<br/>
								
								<div align='right'>
									Ai Componenti del Comitato Etico  <br/>
							    <u>Loro sedi</u>
								</div>
								
								<br/>
								</i>
								<div align='left'>
									<b>OGGETTO: Convocazione seduta n. .. del {$data}</b>
								</div>
								
								<br/>
								<i>
								<div align='left'>
									Pregiatissimi,<br/>
										la seduta di Comitato Etico &egrave; convocata per il prossimo</i><b> {$data}
										dalle ore {$ora_inizio} alle ore {$ora_fine} presso la {$luogo} </b><i>.										
										Si precisa che tutti gli studi sono conformi per completezza di documentazione
										ai sensi del D.M. 21.12.2007 e per caratteristiche della Polizza Assicurativa,
										in applicazione delle direttive del D.M. 14.07.2009.<br/><br/>
							
							L'ordine del giorno della seduta &egrave; il seguente: 
							
							<font color='#00079B'>
							<ul>
							<li>
							Apertura della seduta, approfondimenti di temi specifici e comunicazioni del Presidente relativamente a: 
							</li>
							<li>
							Approvazione del verbale della seduta n. ... del ../../...
							</li>
							<li>
							Richieste di farmaci ad Uso Terapeutico: <br/>
								-	Ratifica delle richieste di Uso Terapeutico pervenute ed approvate con procedura accelerata sulla base di richiesta di valutazione con urgenza;
							</li>
							<li>
							Verifica  di assenza di &quot;conflitto di interessi&quot; dei componenti del CE relativamente agli studi in esame in seduta odierna;
							</li>
							<li>
							Valutazione dei protocolli di studio, come da elenco allegato;
							</li>
							</ul>
							</font>
							
							Per valutare la fattibilit&agrave; della seduta, coloro che eventualmente
							 non potessero partecipare all'incontro, pur avendo gi&agrave; acquisito tale informazione,
							 sono invitati ad avvisare la Segreteria Amministrativa
							 nel pi&ugrave; breve tempo possibile.<br/>
							
							<br/><br/>
							Cordiali saluti.
							<br/><br/>
								</div>
								
							<div align='right'>
									La Segreteria Tecnico-Scientifica <br/>
								</div>
							</td>
						</tr>
						
					</table>
					
						";
		
		return $txt;
	}
	
	
	
	//Vecchia function elenco_studi_ODG() ora valida solo per gli emendamenti
	function elenco_studi_eme_ODG($studi,$param2){
		//$sql=new query($this->conn);
		$i = 0;
		$txt = "";

		for ($k = 0; $k<count($studi);$k++){
			$s = $studi[$k];
			$s = trim($s);
			$stud_center = explode("_",$s);
			$id_stud=$stud_center[0];
			$param_1=$stud_center[1];
			$param_2=$stud_center[2];
			
			if ($s != ""){
				$k++;//Salto un record (Ã¨ l'utente)...
				$i++;
				$rel = trim($studi[$k]); //Recupero userid dell'utente
				/* $qsql="select * from ce_registrazione where id_stud = {$id_stud} ";
				$sql->exec($qsql); */
				
				$query_sql_em="select d.*, to_date(substr(to_char(RICEZ_DOCUM_DT),1,9),'DD-MON-YY') as RICEZ_DOCUM_DT_D from doc_view_emendamenti d where pair = '{$s}' ";
				$sql_em=new query($this->conn);
				$sql_em->exec($query_sql_em);
				//$sql_em->get_row();
				
				$responsabili='';
				
				/* //Recupero tutti i PI dei centro selezionati nell'emendamento
				$strutt = explode("|",$sql_em->row['STRUTTURE']);
				for ($j = 0; $j<count($strutt);$j++){
					if($strutt[$j]){
						$query_sql_cl="select * from ce_centrilocali where id_stud = {$id_stud} and progr={$strutt[$j]}";
						//echo $query_sql_cl."<br>";
						$sql_cl=new query($this->conn);
						$sql_cl->exec($query_sql_cl);
						$sql_cl->get_row();
						$responsabili.="PI: ".$sql_cl->row['D_PRINC_INV'].", UO: ".$sql_cl->row['D_UNITA_OP']."<br>".$sql_cl->row['D_CENTRO']."<br/><br/>";
					}
				}
					
					#Recupero la prima data di ricezione cartacea
					$eme_doc_query="select * from ce_eme_reginvio where id_stud = {$id_stud} and visitnum_progr={$param_1} and progr=1";
					$sql_eme_doc=new query($this->conn);
					$sql_eme_doc->exec($eme_doc_query);
					$sql_eme_doc->get_row();
					
					#Recupero il codice interno CE e la data di ricezione cartacea
					$cod_eme_ce_query="select * from ce_eme_reginvio where id_stud = {$id_stud} and visitnum_progr={$param_1} and progr=(select max(progr) from ce_eme_reginvio where id_stud = {$id_stud} and visitnum_progr={$param_1})";
					$sql_cod_eme_ce=new query($this->conn);
					$sql_cod_eme_ce->exec($cod_eme_ce_query);
					$sql_cod_eme_ce->get_row(); */

					
					#GC 08/05/2015#Vecchia gestione singolo relatore
					//$rel = $this->useridNome($rel);
					//$relrow = $this->getDatiUtente($rel);

					if ($sql_em->get_row()){
					
						#GC 08/05/2015#Nuova gestione multi relatore
						$nrel="";
						$rel_rows = explode("_",$rel);
						//$hl = in_array($this->user->userid,$rel_rows);
						foreach($rel_rows as $kiave => $valore) {$nrel.=$this->useridNome($valore)."<br/>";}
						//$nrel = substr($nrel, 0, -2);
						
						$princ_investig=$sql_em->row['PI'];
						
						$princ_investiga="PI: ".$princ_investig.", CENTRO: ".$sql_em->row['CENTRO']."<br>";
						$rel_studio=$nrel;
						
						$codice_studio_ce=$sql_em->row['CODICE_CE'];
					}
					
					$conto_eme++;
					$conto_romano_eme=$this->numeri_romani($conto_eme);
					$txt.="<br/><br/><b>$conto_romano_eme Reg. Eme. {$codice_studio_ce}</b>";
								
								$txt.= "<TABLE align='center' BORDER=1 WIDTH='100%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
													
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>ID STUDIO</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['UNIQUE_ID']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Codice Emendamento</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['IDE_CODICE']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Data arrivo doc.</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['RICEZ_DOCUM_DT_D']}</td>
													</tr>
													<!--tr>
														<td width='20%' bgcolor='#DAE9ED'>Data arrivo doc. integr.</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['RICEZI_DT']}</td>
													</tr-->
													<tr>
														<td width='30%' bgcolor='#DAE9ED'>Tipologia Studio</td>
														<td width='70%' bgcolor='#D2EFDB'>{$sql_em->row['TIPOLOGIA']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Protocollo</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['COD_STUD']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Titolo studio</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['TITOLO_STUD']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Fase</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['DS_FASE_D']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>EudraCT</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['DS_CODICEEUDRACT']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Promotore</td>
														<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['PROMOTORE']}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Sperimentatore, UO <br/>Centro Locale</td>
														<td width='80%' bgcolor='#D2EFDB'>{$princ_investiga}</td>
													</tr>
													<tr>
														<td width='20%' bgcolor='#DAE9ED'>Relatore</td>
														<td width='80%' bgcolor='#D2EFDB'>{$nrel}</td>
													</tr>
													<br>
													</table>
												 ";
									 

			}
		}
		
		$txt.= "</TABLE>";
		$txt .= "<p>&nbsp;</p>";
		return $txt;
	}
	
	
	function elenco_studi_centri_ODG_relatore($studi,$param,$new_studies=null){
		$sql=new query($this->conn);
		$i = 0;
		$txt = "";
		$titolo_pu_ok="";
		$titolo_pe_ok="";
		$titolo_osserv_ok="";
		
		for ($k=0; $k<count($studi);$k++){
			$s = $studi[$k];
			$s = trim($s);
			$stud_center = explode("_",$s);
			$id_stud=$stud_center[0];
			$param_center=$stud_center[1];

			if ($s != ""){
				$k++;//Salto un record (Ã¨ l'utente)...
				$i++;
				$rel = trim($studi[$k]); //Recupero userid dell'utente
				$qsql="select d.*, to_date(substr(to_char(RICEZ_DOCUM_DT),1,9),'DD-MON-YY') as RICEZ_DOCUM_DT_D, to_date(substr(to_char(RICEZ_DOCUM_INTEGR_DT),1,9),'DD-MON-YY') as RICEZ_DOCUM_INTEGR_DT_D from doc_view_studi d where pair = '{$s}' ";
				$sql->exec($qsql);
				//echo $qsql;
				//echo("$sql_close<br/>");

				if ($sql->get_row()){
					
					#GC 08/05/2015#Nuova gestione multi relatore
					$nrel="";
					$rel_rows = explode("_",$rel);
					//$hl = in_array($this->user->userid,$rel_rows);
					foreach($rel_rows as $kiave => $valore) {$nrel.=$this->useridNome($valore)."<br/>";}
					//$nrel = substr($nrel, 0, -2);
					
					$princ_investig=$sql->row['PI'];
					
					$princ_investiga="PI: ".$princ_investig.", CENTRO: ".$sql->row['CENTRO']."<br>";
					$rel_studio=$nrel;
					
					$codice_studio_ce=$sql->row['CODICE_CE'];
				}

			/* $sql_query_qs="select * from ce_registrazione where id_stud = $key1 ";
			$sql_qs=new query($this->conn);
			$sql_qs->exec($sql_query_qs);
			$sql_qs->get_row(); */
			
			$stud_interv='';
			$stud_osserv='';
			$stud_bio='';
			$stud_altro='';

			/* #Recupero Codice, Titolo e Sponsor
			$sql_query_dett="select * from gse_info_studio_odg where id_stud = $key1";
			$sql_dett=new query($this->conn);
			$sql_dett->exec($sql_query_dett);
			$sql_dett->get_row(); */
			
			//LUIGI classificazione post ordinamento colonna TIPO_ORDINAMENTO e PU_ACC
			if($sql->row['TIPO_SPER']==1 || $sql->row['TIPO_SPER']==2 || $sql->row['TIPO_SPER']==3 || $sql->row['TIPO_SPER']==4) $stud_interv=1;
			if($sql->row['TIPO_SPER']==6) {$stud_interv=1;$stud_bio=1;}
			//if($sql->row['TIPO_SPER']==-9900) {$stud_interv=1;$stud_altro=1;}
			if($sql->row['TIPO_SPER']==5) $stud_osserv=1;
			
			
			#Conteggio studi interventistici
			if($new_studies==1 and $stud_osserv==''){
								
				#Studi interventistici di cui AVR ha indicato essere il Coordinatore
				if ($stud_interv==1 and $sql->row['PARERE_UNICO']==1) {
					if($titolo_pu_ok==''){
						$txt.="<b><u>PARERE UNICO</u></b>";
						$titolo_pu_ok=1;
					}
					$conto_pu++;
					$conto_romano_pu=$this->numeri_romani($conto_pu);
					$txt.="<br/><br/><b>$conto_romano_pu Reg. Sper. {$codice_studio_ce}</b>";
				}
				
				#Studi interventistici di cui AVR ha indicato essere un Satellite
				if (($stud_interv==1 and $sql->row['PARERE_UNICO']==2) || $stud_bio==1 || $stud_altro==1) {
					if($titolo_pe_ok==''){
						$txt.="<hr break><br/><b><u>PARERI DI ETICITA'</u></b>";
						$titolo_pe_ok=1;
					}
					$conto_acc_pu++;
					$conto_romano_acc_pu=$this->numeri_romani($conto_acc_pu);
					$txt.="<br/><br/><b>$conto_romano_acc_pu Reg. Sper. {$codice_studio_ce}</b>";
				}

			}
			
			#Conteggio studi osservazionali
			if($new_studies==1 and $stud_osserv==1){
				if ($titolo_osserv_ok=='') {
					$txt.="<hr break><br/><b><u>STUDI OSSERVAZIONALI</u></b>";
					$titolo_osserv_ok=1;
				}
					$conto_osserv++;
					$conto_romano_osserv=$this->numeri_romani($conto_osserv);
					$txt.="<br/><br/><b>$conto_romano_osserv Reg. Sper. {$codice_studio_ce}</b>";
			}
			
			#Conteggio studi sospesi
			if($new_studies==''){
				$conto_sosp++;
				$conto_romano_sosp=$this->numeri_romani($conto_sosp);
				$txt.="<br/><br/><b>$conto_romano_sosp Reg. Sper. {$codice_studio_ce}</b>";
			}
			
//			#Conteggio studi biologici
//			if($new_studies==1 and $stud_bio==1){
//				
//				#Studi interventistici di cui AVR ha indicato essere il Coordinatore
//					if($titolo_bio_ok==''){
//						$txt.="<br/><b><u>STUDI BIOLOGICI</u></b>";
//						$titolo_bio_ok=1;
//					}
//					$conto_bio++;
//					$conto_romano_bio=$this->numeri_romani($conto_bio);
//					$txt.="<br/><br/><b>$conto_romano_bio Reg. Sper. {$codice_studio_ce[$key1]}</b>";
//
//			}
//			
//			#Conteggio studi 'altro'
//			if($new_studies==1 and $stud_altro==1){
//				
//				#Studi interventistici di cui AVR ha indicato essere il Coordinatore
//					if($titolo_altro_ok==''){
//						$txt.="<br/><b><u>ALTRI STUDI</u></b>";
//						$titolo_altro_ok=1;
//					}
//					$conto_altro++;
//					$conto_romano_altro=$this->numeri_romani($conto_altro);
//					$txt.="<br/><br/><b>$conto_romano_altro Reg. Sper. {$codice_studio_ce[$key1]}</b>";
//
//			}
			
			/* $pi_centro='';
 		 		foreach ($val1 AS $key2 => $val2){
    		//echo "Array di riga $key1, posizione $key2, contenuto $val2<br />\n";
    		//echo $val2."<br>";
    		$pi_centro.=$val2."<br>";
				} */
			
			$txt.= "<TABLE align='center' BORDER=1 WIDTH='100%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>ID STUDIO</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['UNIQUE_ID']}</td>
								</tr>
								<!--tr>
									<td width='20%' bgcolor='#DAE9ED'>Numero di registro sperimentazioni</td>
									<td width='80%' bgcolor='#D2EFDB'>{$codice_studio_ce}</td>
								</tr-->
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Data arrivo doc.</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['RICEZ_DOCUM_DT_D']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Data arrivo doc. integr.</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['RICEZ_DOCUM_INTEGR_DT_D']}</td>
								</tr>
								<tr>
									<td width='30%' bgcolor='#DAE9ED'>Tipologia Studio</td>
									<td width='70%' bgcolor='#D2EFDB'>{$sql->row['TIPOLOGIA']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Protocollo</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['COD_STUD']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['TITOLO_STUD']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Fase</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['DS_FASE_D']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>EudraCT</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['DS_CODICEEUDRACT']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Promotore</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['PROMOTORE']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Sperimentatore, Centro Locale</td>
									<td width='80%' bgcolor='#D2EFDB'>{$princ_investiga}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Relatore</td>
									<td width='80%' bgcolor='#D2EFDB'>{$rel_studio}</td>
								</tr>
								<br>
								</table>
							 ";
			
		
			}
		}
		
		$txt.= "</TABLE>";
		
		$txt .= "<p>&nbsp;</p>";
		
		return $txt;
	}
	
	
	
	
	
	
	
		
	function crea_Verbale(){
		$txt = "";
		$sql=new query($this->conn);
		//$sql_query="select TO_CHAR(DATA_SED_DT,'DD-MM-YYYY') as DATA_SED_DT from {$this->service}_registrazione where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql_query="select * from {$this->service}_registrazione where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		//echo $sql_query;
		$sql->exec($sql_query);
		$data = "";
		$ora = "";
		$luogo = "";
		if ($sql->get_row()){
			$data = $sql->row['DATA_SED_DT'];
			$ora = sprintf("%02d:%02d", $sql->row['ORA_INIZIO_H'], $sql->row['ORA_INIZIO_M']);	
			$luogo = $sql->row['LUOGO'];
		}
		
		$txt.= "<p align='center'>VERBALE DEL <b>{$data}</b></p>";
		// $txt.= "<p> Il giorno {$data}, presso la {$luogo}, si &egrave; svolta la riunione del Comitato Etico per le sperimentazioni
								// cliniche della Facolt&agrave; di Medicina e Chirurgia dell'Universit&agrave; Cattolica del Sacro Cuore.<br/>
								// I lavori hanno avuto inizio alle ore {$ora}.
						// </p>";
		$txt.= "<p>
							<ol>
								<li>Verifica del numero legale</il>
								<li>Approvazione del verbale della seduta precedente e ratifica delle comunicazioni inserite nella seduta istruttoria del ../../....</il>
							 	<li>Verifica dell'assenza di conflitto di interesse per i presenti alla seduta</il>
							</ol>
						</p>";
		$txt.= "<table bgcolor='#C9C3C3' align='center' border='0' cellpadding='0' cellspacing='0' style='width: 100%;'>
							<tbody align='left'>
								<tr>
									<td>Comunicazioni</td>
								</tr>
							</tbody>
						</table>
						<br/><br/><br/>";

		//Compilazione presenze
		////Recupero convocazioni
		$sql_query="select * from {$this->service}_sel_componenti where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql->exec($sql_query);
		$sql->get_row();
		$conv = $this->getArray($sql,"CONVOCAZIONI");
		$cnv[1] = $this->getArray($sql,"CONVOCAZIONI_ESTERNI");
		$cnv[2] = $this->getArray($sql,"CONVOCAZIONI_SPERIMENTATORI");
		$cnv[0] = array_diff($conv,$cnv[1],$cnv[2]);
		//print_r($cnv);
		////Recupero presenze
		$sql_query="select * from {$this->service}_pres_componenti where {$this->xmr->pk_service}={$this->pk_service} and visitnum=2"; // and esam=1";
		$sql->exec($sql_query);
		$sql->get_row();
		$prs[0] = $this->getArray($sql,"PRESENZE");
		$prs[1] = $this->getArray($sql,"PRESENZE_ESTERNI");
		$prs[2] = $this->getArray($sql,"PRESENZE_SPERIMENTATORI");
		$prs[3] = $this->getArray($sql,"PRESENZE_TELE");
		//print_r($prs);
		$txt .= "<table width=\"100%\" border=\"0\">";
		$txt .= "<tr>";
		$txt .= "<td>&nbsp;</td><td>&nbsp;</td><td align=\"center\">Presente</td><td align=\"center\">Via telematica</td><td align=\"center\">Assente</td>";
		$txt .= "</tr>";
		for ($i = 0; $i<4; $i++){
			foreach ($prs[$i] as $p){
				$nome = $this->getDatiUtente($p);
				$nome = $nome['QUALIFICA']." ".$nome['NOME']." ".$nome['COGNOME'];
				$tipo = "componente";
				switch ($i){
					case 1:
						$tipo = "esperto esterno";
						break;
					case 2:
						$tipo = "sperimentatore";
						break;
				}
				if (in_array($p,$conv)){
					//Ero richiesto
				}else{
					//Non ero richiesto
				}
				if($i<=2){
					$txt .= "<tr>";
					$txt .= "<td>$nome</td><td>$tipo</td><td align=\"center\">X</td><td align=\"center\"></td><td align=\"center\"></td>";
					$txt .= "</tr>";
				}
				if($i==3){
					$txt .= "<tr>";
					$txt .= "<td>$nome</td><td>$tipo</td><td align=\"center\"></td><td align=\"center\">X</td><td align=\"center\"></td>";
					$txt .= "</tr>";
					}
			}
			foreach ($cnv[$i] as $p){
				$nome = $this->getDatiUtente($p);
				$nome = $nome['QUALIFICA']." ".$nome['NOME']." ".$nome['COGNOME'];
				$tipo = "componente";
				switch ($i){
					case 1:
						$tipo = "esperto esterno";
						break;
					case 2:
						$tipo = "sperimentatore";
						break;
				}
				#GC 03/02/2016 [TOSCANA-7] I membri assenti sono quelli che non si trovano nei presenti $prs[0] o nei telematici $prs[3]
				if($i==0){
					if (!in_array($p,$prs[$i]) && !in_array($p,$prs[3])){
						//Sono assente ed ero richiesto
						$txt .= "<tr>";
						$txt .= "<td>$nome</td><td>$tipo</td><td align=\"center\"></td><td align=\"center\"></td><td align=\"center\">X</td>";
						$txt .= "</tr>";
					}
				}else{
					if (!in_array($p,$prs[$i])){
						//Sono assente ed ero richiesto
						$txt .= "<tr>";
						$txt .= "<td>$nome</td><td>$tipo</td><td align=\"center\"></td><td align=\"center\"></td><td align=\"center\">X</td>";
						$txt .= "</tr>";
					}
					}
			}
			
		}
		////
		
		$txt .= "</table>";
		//Fine presenze
		$txt .= "<p>&nbsp;</p><p break></p>";
		
		
		//Interrogo momentaneamente gli studi selezionati nell'ODG
		$sql=new query($this->conn);
		$sql_query="select * from {$this->service}_sel_studi where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0"; // and esam=1";
		$sql->exec($sql_query);
		
		//$i = 0;
		//$txt .= "<p><b><i>Sono stati esaminati i seguenti</i></b></p>";
		$studi = "";
		$param = "";
		$param2 = "";
		if ($sql->get_row()){
			$studi = "";
			$studi = $sql->row['STUDI_SOSPESI'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				$txt .= "<p><b>STUDI DA INTEGRARE/MODIFICARE</b></p>";
				$param='progr';
				$param2='SOSPESI';
				$txt.= $this->elenco_studi_centri_Verbale($studi, "CE_VALUTAZIONE", $param, $param2);
			}
			
			$studi = "";
			$studi = $sql->row['STUDI'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				
				$txt .= "<p><b>NUOVI STUDI:</b></p>";
				$param='progr';
				$param2='INIZIALI';
				$txt.= $this->elenco_studi_centri_Verbale($studi, "CE_VALUTAZIONE", $param, $param2);
			}

			$studi = "";
			$studi = $sql->row['STUDI_EMENDAMENTI'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				$txt .= "<p><b>NUOVI EMENDAMENTI:</b></p>";
				$param2='STUDI_EMENDAMENTI';
				$txt.= $this->elenco_studi_eme_Verbale($studi, "CE_EME_VALUTAZIONE", $param2);
			}
			
			$studi = "";
			$studi = $sql->row['STUDI_EME_SOSP'];
			if($studi!='|'){
				$studi = explode("|",$studi);
				$txt .= "<p><b>EMENDAMENTI IN ATTESA D'INTEGRAZIONE/MODIFICA</b></p>";
				$param2='STUDI_EME_SOSP';
				$txt.= $this->elenco_studi_eme_Verbale($studi, "CE_EME_VALUTAZIONE", $param2);
			}
			
//			$studi = "";
//			$studi = $sql->row['STUDI_AGGIORNAMENTI'];
//			$studi = explode("|",$studi);
//			$txt .= "<p><b>AGGIORNAMENTO PROTOCOLLI:</b></p>";
//			$txt.= $this->elenco_studi_Verbale($studi, false);
//			
//			$studi = "";
//			$studi = $sql->row['STUDI_DATI_AMMIN'];
//			$studi = explode("|",$studi);
//			$txt.= "<p><b>Dati amministrativi:</b></p>";
//			$param='progr';
//			$txt.= $this->elenco_studi_centri_Verbale($studi,$param);
//			
//			$studi = "";
//			$studi = $sql->row['STUDI_AVVIO'];
//			$studi = explode("|",$studi);
//			$txt.= "<p><b>Dati avvio:</b></p>";
//			$txt.= $this->elenco_studi_centri_Verbale($studi,$param);
//			
//			$studi = "";
//			$studi = $sql->row['STUDI_CONCLUSIONE'];
//			$studi = explode("|",$studi);
//			$txt .= "<p><b>Dati conclusione:</b></p>";
//			$txt.= $this->elenco_studi_centri_Verbale($studi,$param);
//			
//			$studi = "";
//			$studi = $sql->row['STUDI_SAE'];
//			$studi = explode("|",$studi);
//			$txt.= "<p><b>Ulteriori SAE:</b></p>";
//			$txt.= $this->elenco_studi_centri_Verbale($studi,$param);
			
		}
		
		$txt .= "<p break></p>";
		
		//$txt .=$this->aggiornamenti_studi();
		
		$txt .= "<hr><p><b>Varie ed eventuali:</b></p>";
		$txt=str_replace("-9944", "Non applicabile", $txt);
		return $txt;
	}
	
	function aggiornamenti_studi(){
		
		$txt = "<hr><p><b>Aggiornamento studi in atto:</b></p>";		
		
		//sezione nuovi avvii
		$query_avvio="select t.id_stud, t.APERTO, t.ARRUOLAMENTO, t.APERTO_DT, t.VISITNUM_PROGR, c.moddt from CE_MONITOR t ,ce_coordinate c where t.id_stud in(
			select id_stud from ce_coordinate where moddt between(
				select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service}) 
				and id_sed < {$this->pk_service})
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service})
			and esam=1 and visitnum=5 and fine=1
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}')
		)

		and c.id_stud=t.id_stud and c.visitnum=t.visitnum and c.progr=t.progr and c.visitnum_progr=t.visitnum_progr and t.esam=c.esam
		and c.fine=1
		and c.visitnum_progr in (
			select progr-1 from ce_centrilocali where id_stud=t.id_stud and centro in (
				select id from ce_elenco_centriloc where centro=(select id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}')
			)
		)
		";						
						
		$sql_avvio=new query($this->conn);
		$sql_avvio->exec($query_avvio);
		while($sql_avvio->get_row()){
			$query_studio_centro="select * from ce_tutti_studi_CENTRI_INFO where id_stud={$sql_avvio->row['ID_STUD']} and VISITNUM_PROGR_PARERE='{$sql_avvio->row['VISITNUM_PROGR']}'";
			$sql_studio_centro=new query($this->conn);
			$sql_studio_centro->get_row($query_studio_centro);
			
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_avvio->row['ID_STUD']}";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>ID studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['ID_STUD']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['CODICE_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['TITOLO_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Sperimentatore</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio_centro->row['D_PRINC_INV']}</td>
								</tr>
							";
			$txt .="<tr>
								<td width='10%' bgcolor='#DAE9ED'>Avvio</td>
								<td width='90%' bgcolor='#D2EFDB'>";
			if ($sql_avvio->row['APERTO']==1) $txt .="Il comitato etico recepisce la comunicazione di {$sql_studio->row['DESCR_SPONSOR']} del giorno {$sql_avvio->row['MODDT']} di apertura dello studio nel centro {$sql_studio_centro->row['D_CENTRO']}. Data di avvio: {$sql_avvio->row['APERTO_DT']}";
			else if  ($sql_avvio->row['APERTO']==2) $txt .="Il comitato etico recepisce la comunicazione di {$sql_studio->row['DESCR_SPONSOR']} del giorno {$sql_avvio->row['MODDT']} di rinuncia alla conduzione dello studio nel centro {$sql_studio_centro->row['D_CENTRO']}. Data di avvio: {$sql_avvio->row['APERTO_DT']}";
			$txt .= "</td></tr></table><br><br>";
		}
		
		
		//sezione nuove chiusure
		$query_chiusura="select t.id_stud, t.CONCLUS_DT, t.VISITNUM_PROGR, c.moddt from CE_CHIUSURA t, ce_coordinate c where t.id_stud in(
			select id_stud from ce_coordinate where moddt between 
				(select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service})
				and id_sed < {$this->pk_service})
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service})
			and esam=2 and visitnum=5
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}')
		)
		and c.id_stud=t.id_stud and c.visitnum=t.visitnum and c.progr=t.progr and c.visitnum_progr=t.visitnum_progr and t.esam=c.esam
		and c.fine=1
		and c.visitnum_progr in (
			select progr-1 from ce_centrilocali where id_stud=t.id_stud and centro in (
				select id from ce_elenco_centriloc where centro=(select id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}')
			)
		)
		";						
						
		$sql_chiusura=new query($this->conn);
		$sql_chiusura->exec($query_chiusura);
		while($sql_chiusura->get_row()){
			$query_studio_centro="select * from ce_tutti_studi_CENTRI_INFO where id_stud={$sql_chiusura->row['ID_STUD']} and VISITNUM_PROGR_PARERE='{$sql_chiusura->row['VISITNUM_PROGR']}'";
			$sql_studio_centro=new query($this->conn);
			$sql_studio_centro->get_row($query_studio_centro);
			
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_chiusura->row['ID_STUD']}";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>ID studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['ID_STUD']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['CODICE_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['TITOLO_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Chiusura</td>
									<td width='90%' bgcolor='#D2EFDB'>Il comitato etico recepisce la comunicazione  di {$sql_studio->row['DESCR_SPONSOR']} del giorno {$sql_chiusura->row['MODDT']} di chiusura dello studio nel centro {$sql_studio_centro->row['D_CENTRO']}. Data di chiusura del centro: {$sql_chiusura->row['CONCLUS_DT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Sperimentatore</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio_centro->row['D_PRINC_INV']}</td>
								</tr>
							 </table><br><br>";
		}
		
		
		
		//sezione rapporti di avanzamento
		$query_rapporti="select t.id_stud, t.RELAZ_DT, t.VISITNUM_PROGR, c.moddt from CE_RAPPORTI t, ce_coordinate c where t.id_stud in(
			select id_stud from ce_coordinate where moddt between 
				(select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service})
				and id_sed < {$this->pk_service})
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service})
			and esam=3 and visitnum=5
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}')
			)
			and c.id_stud=t.id_stud and c.visitnum=t.visitnum and c.progr=t.progr and c.visitnum_progr=t.visitnum_progr and t.esam=c.esam
			and c.fine=1
			and c.visitnum_progr in (
				select progr-1 from ce_centrilocali where id_stud=t.id_stud and centro in (
				select id from ce_elenco_centriloc where centro=(select id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}')
				)
			)
			";						
						
		$sql_rapporti=new query($this->conn);
		$sql_rapporti->exec($query_rapporti);
		while($sql_rapporti->get_row()){
			$query_studio_centro="select * from ce_tutti_studi_CENTRI_INFO where id_stud={$sql_rapporti->row['ID_STUD']} and VISITNUM_PROGR_PARERE='{$sql_rapporti->row['VISITNUM_PROGR']}'";
			$sql_studio_centro=new query($this->conn);
			$sql_studio_centro->get_row($query_studio_centro);
			
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_rapporti->row['ID_STUD']}";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>ID studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['ID_STUD']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['CODICE_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['TITOLO_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Avanzamento</td>
									<td width='90%' bgcolor='#D2EFDB'>Il comitato etico recepisce lo stato di avanzamento dello studio inviato dallo sperimentatore {$sql_studio->row['DESCR_SPONSOR']} con lettera del giorno {$sql_rapporti->row['MODDT']} nel centro {$sql_studio_centro->row['D_CENTRO']}. Data della relazione: {$sql_rapporti->row['RELAZ_DT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Sperimentatore</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio_centro->row['D_PRINC_INV']}</td>
								</tr>
							 </table><br><br>";
		}
		
		
		//sezione conclusione
		$query_conclusione="select t.id_stud, t.CONCLUS_ITA_DT, c.moddt from CE_CONCLUSIONE_TOTO t, ce_coordinate c where t.id_stud in(
			select id_stud from ce_coordinate where moddt between 
				(select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service})
				and id_sed < {$this->pk_service})
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service})
			and esam=221 and visitnum=22
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}')
		)
		and c.id_stud=t.id_stud and c.visitnum=t.visitnum and c.progr=t.progr and c.visitnum_progr=t.visitnum_progr and t.esam=c.esam
		and c.fine=1
		";						
						
		$sql_conclusione=new query($this->conn);
		$sql_conclusione->exec($query_conclusione);
		while($sql_conclusione->get_row()){
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_conclusione->row['ID_STUD']}";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>ID studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['ID_STUD']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['CODICE_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['TITOLO_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Conclusione</td>
									<td width='90%' bgcolor='#D2EFDB'>Il comitato etico recepisce la relazione di conclusione dello studio del giorno {$sql_conclusione->row['MODDT']}. Data di conclusione dello studio: {$sql_conclusione->row['CONCLUS_ITA_DT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Sperimentatore</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio_centro->row['D_PRINC_INV']}</td>
								</tr>
							 </table><br><br>";
		}
		
		
		//sezione eventi avversi (SAE)
		$query_susar="select t.id_stud, t.EVENTO_DT, t.VISITNUM_PROGR, c.moddt from CE_SUSAR t, ce_coordinate c where t.id_stud in(
			select id_stud from ce_coordinate where moddt between 
				(select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service})
				and id_sed < {$this->pk_service})
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service})
			and esam=9 and visitnum=9
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}')
		)
		and c.id_stud=t.id_stud and c.visitnum=t.visitnum and c.progr=t.progr and c.visitnum_progr=t.visitnum_progr and t.esam=c.esam
		and c.fine=1
		and c.visitnum_progr in (
			select progr-1 from ce_centrilocali where id_stud=t.id_stud and centro in (
				select id from ce_elenco_centriloc where centro=(select id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}')
			)
		)
		";						
						
		$sql_susar=new query($this->conn);
		$sql_susar->exec($query_susar);
		while($sql_susar->get_row()){
			$query_studio_centro="select * from ce_tutti_studi_CENTRI_INFO where id_stud={$sql_susar->row['ID_STUD']} and VISITNUM_PROGR_PARERE='{$sql_susar->row['VISITNUM_PROGR']}'";
			$sql_studio_centro=new query($this->conn);
			$sql_studio_centro->get_row($query_studio_centro);
			
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_susar->row['ID_STUD']}";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>ID studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['ID_STUD']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['CODICE_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['TITOLO_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Eventi avversi</td>
									<td width='90%' bgcolor='#D2EFDB'>Il comitato etico recepisce la relazione di evento avverso del giorno {$sql_susar->row['EVENTO_DT']} nel centro {$sql_studio_centro->row['D_CENTRO']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Sperimentatore</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio_centro->row['D_PRINC_INV']}</td>
								</tr>
							 </table><br><br>";
		}
		
		//sezione rapporti si sicurezza (DSUR)
		$query_dsur="select t.id_stud, t.RELAZ_DT, t.VISITNUM_PROGR, t.TITOLO_RAP_SIC, to_date(t.PERIODO1,'DD/MM/YYYY') as PERIODO1, to_date(t.PERIODO2,'DD/MM/YYYY') as PERIODO2, t.note, c.moddt from CE_RAPPORTISIC t, ce_coordinate c where t.id_stud in(
			select id_stud from ce_coordinate where moddt between 
				(select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service})
				and id_sed < {$this->pk_service})
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service})
			and esam=4 and visitnum=9
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}')
		)
		and c.id_stud=t.id_stud and c.visitnum=t.visitnum and c.progr=t.progr and c.visitnum_progr=t.visitnum_progr and t.esam=c.esam
		and c.fine=1
		and c.visitnum_progr in (
			select progr-1 from ce_centrilocali where id_stud=t.id_stud and centro in (
				select id from ce_elenco_centriloc where centro=(select id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}')
			)
		)
		";						
						
		$sql_dsur=new query($this->conn);
		$sql_dsur->exec($query_dsur);
		while($sql_dsur->get_row()){
			$query_studio_centro="select * from ce_tutti_studi_CENTRI_INFO where id_stud={$sql_dsur->row['ID_STUD']} and VISITNUM_PROGR_PARERE='{$sql_dsur->row['VISITNUM_PROGR']}'";
			$sql_studio_centro=new query($this->conn);
			$sql_studio_centro->get_row($query_studio_centro);
			
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_dsur->row['ID_STUD']}";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>ID studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['ID_STUD']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['CODICE_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['TITOLO_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Rapporti di sicurezza</td>
									<td width='90%' bgcolor='#D2EFDB'>
									<table align='center' BORDER=1 WIDTH='100%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
										<tr><td>Il comitato etico recepisce la relazione di rapporto di sicurezza {$sql_dsur->row['TITOLO_RAP_SIC']} 
										<br>del periodo {$sql_dsur->row['PERIODO1']} -  {$sql_dsur->row['PERIODO1']} <br>nel centro {$sql_studio_centro->row['D_CENTRO']}</td></tr>
										<tr><td>
										Note DSUR: {$sql_dsur->row['NOTE']}
										</td></tr>
									</table>
									</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Sperimentatore</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio_centro->row['D_PRINC_INV']}</td>
								</tr>
							 </table><br><br>";
		}
		
		
		
		//sezione emendamenti non sostanziali
		$query_eme_sost="select t.id_stud, t.VISITNUM_PROGR, t.PROGR, t.D_CENTRO, t.RIUNIONE_CE_DT, t.D_RIS_DELIB, e.emend_code, e.EMEND_TYPE, 
		c.moddt 
		from CE_EME_VALUTAZIONE t, 
		CE_EMENDAMENTI e, 
		ce_coordinate c where 
		
		t.id_stud in(
			select id_stud from ce_coordinate where moddt between(
				select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service}) 
				and id_sed < {$this->pk_service}) 
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service}) 
			and esam=3 and visitnum=20 and visitnum_progr=t.visitnum_progr and fine=1
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}') 
		)
    
		and
		c.id_stud=t.id_stud 
		and c.visitnum=t.visitnum 
		and c.progr=t.progr 
		and c.visitnum_progr=t.visitnum_progr 
		and c.esam=t.esam
		and e.id_stud=t.id_stud 
		and e.visitnum_progr=t.visitnum_progr 
			and c.fine=1
		and t.ris_delib is not null
			and c.progr in (
				select progr from ce_centrilocali where id_stud=t.id_stud and centro in (
					select id from ce_elenco_centriloc where centro=(select id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}')  
				)
			)
		and e.emend_type=2
		";						
						
		$sql_eme_sost=new query($this->conn);
		$sql_eme_sost->exec($query_eme_sost);
		while($sql_eme_sost->get_row()){
			$query_studio_centro="select * from ce_tutti_studi_CENTRI_INFO where id_stud={$sql_eme_sost->row['ID_STUD']} and VISITNUM_PROGR_PARERE={$sql_eme_sost->row['PROGR']}-1";
			$sql_studio_centro=new query($this->conn);
			$sql_studio_centro->get_row($query_studio_centro);
			
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_eme_sost->row['ID_STUD']}";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>ID studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['ID_STUD']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['CODICE_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio->row['TITOLO_PROT']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Sperimentatore</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_studio_centro->row['D_PRINC_INV']}</td>
								</tr>
								<tr>
									<td width='10%' bgcolor='#DAE9ED'>Codice emendamento</td>
									<td width='90%' bgcolor='#D2EFDB'>{$sql_eme_sost->row['EMEND_CODE']}</td>
								</tr>
							";
			$txt .="<tr>
								<td width='10%' bgcolor='#DAE9ED'>Emendamento non sostanziale</td>
								<td width='90%' bgcolor='#D2EFDB'>";
			$txt .="Il comitato etico recepisce la valutazione dell'emendamento non sostanziale {$sql_eme_sost->row['EMEND_CODE']} nel centro {$sql_studio_centro->row['D_CENTRO']} del giorno {$sql_eme_sost->row['MODDT']}.<br> Esito: {$sql_eme_sost->row['D_RIS_DELIB']}";
			$txt .= "</td></tr></table><br><br>";
		}
		
		
		
		/*
		//sezione documentazione in verbale
		$query_docs="select t.id_stud, t.DOC_DT, t.D_DOC_LOC, t.DESCR_AGG, t.VISITNUM_PROGR, c.moddt from CE_DOCUM_CENTRO t, ce_coordinate c where t.id_stud in(
			select id_stud from ce_coordinate where moddt between 
				(select data_sed_dt from gse_registrazione 
				where id_sed = (select max(id_sed) 
				from gse_registrazione 
				where center=(select center from gse_registrazione where id_sed={$this->pk_service})
				and id_sed < {$this->pk_service})
				)
				and
				(select data_sed_dt from gse_registrazione where id_sed = {$this->pk_service})
			and esam=23 and visitnum=1
			and id_stud in (select center from ce_utenti_centri where userid='{$this->session_vars['remote_userid']}')
		)
		and c.id_stud=t.id_stud and c.visitnum=t.visitnum and c.progr=t.progr and c.visitnum_progr=t.visitnum_progr and t.esam=c.esam
		and c.fine=1
		and c.visitnum_progr in (
			select progr-1 from ce_centrilocali where id_stud=t.id_stud and centro in (
				select id from ce_elenco_centriloc where centro=(select id_ce from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}')
			)
    and t.doc_loc=21
		)
		";						
						
		$sql_docs=new query($this->conn);
		$sql_docs->exec($query_docs);
		while($sql_docs->get_row()){
			$query_studio_centro="select * from ce_tutti_studi_CENTRI_INFO where id_stud={$sql_docs->row['ID_STUD']} and VISITNUM_PROGR_PARERE='{$sql_docs->row['VISITNUM_PROGR']}'";
			$sql_studio_centro=new query($this->conn);
			$sql_studio_centro->get_row($query_studio_centro);
			
			$query_studio="select * from ce_tutti_studi where id_stud={$sql_docs->row['ID_STUD']}";
			if ($sql_docs->row['DOC_DT']!='') $doc_dt="del giorno {$sql_docs->row['DOC_DT']}";
			if ($sql_docs->row['DESCR_AGG']!='') $descr_agg="({$sql_docs->row['DESCR_AGG']})";
			$sql_studio=new query($this->conn);
			$sql_studio->get_row($query_studio);
			$txt .= "<table align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='2'>";
			$txt .= "<tr><td>studio: {$sql_studio->row['CODICE_PROT']}</td></tr>
				<tr><td>Titolo: {$sql_studio->row['TITOLO_PROT']}</td></tr>";
			$txt .= "</table>";
			$txt .="<table align='center' width='90%'><tr><td>Il comitato etico recepisce il documento di comunicazioni varie in verbale $descr_agg $doc_dt nel centro {$sql_studio_centro->row['D_CENTRO']}</tr></td></table>";
			$txt .= "<br><br><br>";
		}
		*/
		return $txt;
		
	}
	

	//Vecchia function elenco_studi_Verbale() ora valida solo per gli emendamenti
	function elenco_studi_eme_Verbale($studi ,$tableParere, $param2){
		//$sql=new query($this->conn);
		$i = 0;
		$txt = "";
		
		//Quero gli emendamenti selezionati nella prima scheda di VERBALE
		$sql_verb=new query($this->conn);
		$sql_query_verb="select * from {$this->service}_pres_studi where {$this->xmr->pk_service}={$this->pk_service} and visitnum=2"; // and esam=1";
		$sql_verb->exec($sql_query_verb);
		$sql_verb->get_row();
		//echo $sql_query_verb;
		
		for ($k = 0; $k<count($studi);$k++){
			$s = $studi[$k];
			$s = trim($s);
			
			$stud_center = explode("_",$s);
			$id_stud=$stud_center[0];
			$param_1=$stud_center[1];
			$param_2=$stud_center[2];			
			
			//Devo controllare che l'eme sia stato confermato nel verbale
			$in_verbale=false;
			if ($tableParere=='CE_EME_VALUTAZIONE'){
				if ($param2=='STUDI_EMENDAMENTI' && preg_match("!{$studi[$k]}!",$sql_verb->row['STUDI_EMENDAMENTI'])) $in_verbale=true;
				if ($param2=='STUDI_EME_SOSP' && preg_match("!{$studi[$k]}!",$sql_verb->row['STUDI_EME_SOSP'])) $in_verbale=true;
			}
			
			if ($s != "" && $in_verbale){
				$k++;//Salto un record (?'utente)...
				$i++;
				$rel = trim($studi[$k]); //Recupero userid dell'utente
				//echo $rel;
				/* $qsql="select * from ce_registrazione where id_stud = {$id_stud} ";
				$sql->exec($qsql); */
				
				
				$query_sql_em="select d.*, to_date(substr(to_char(RICEZ_DOCUM_DT),1,9),'DD-MON-YY') as RICEZ_DOCUM_DT_D from doc_view_emendamenti d where pair = '{$s}' ";
				$sql_em=new query($this->conn);
				$sql_em->exec($query_sql_em);
				//$sql_em->get_row();
				
				$responsabili='';
					
				if ($sql_em->get_row()){
					
					#GC 08/05/2015#Nuova gestione multi relatore
					$nrel="";
					$rel_rows = explode("_",$rel);
					//$hl = in_array($this->user->userid,$rel_rows);
					foreach($rel_rows as $kiave => $valore) {$nrel.=$this->useridNome($valore)."<br/>";}
					//$nrel = substr($nrel, 0, -2);
					
					$princ_investig=$sql_em->row['PI'];
					
					$princ_investiga="PI: ".$princ_investig.", CENTRO: ".$sql_em->row['CENTRO']."<br>";
					$rel_studio=$nrel;
					
					$codice_studio_ce=$sql_em->row['CODICE_CE'];
				}
				/*
				$txt.= "<TABLE align='center' BORDER=1 WIDTH='90%' bordercolor='#99C1CC' cellspacing='0' cellpadding='2' style='border: 1 double #99C1CC'>
									<TR><Th bgcolor='#99C1CC' width='7'>
									 <p style='margin-left: 0'><font color=black size='1px'><B>ID</B></font></p>
									 </Th>
									 <Th bgcolor='#99C1CC' width='150'>
									 <p style='margin-left: 0'><font color=black size='1px'><B>Codice studio</B></font></p>
									 </Th>
									 <Th bgcolor='#99C1CC' width='150'>
									 <p style='margin-left: 0'><font color=black size='1px'><B>CODICE EME</B></font></p>
									 </Th>
									 <Th bgcolor='#99C1CC' width='150'>
									 <p style='margin-left: 0'><font color=black size='1px'><B>Titolo studio</B></font></p>
									 </Th>
									 <Th bgcolor='#99C1CC' width='150'>
									 <p style='margin-left: 0'><font color=black size='1px'><B>Tipologia Studio</B></font></p>
									 </Th>
									 <Th bgcolor='#99C1CC' width='150'>
									 <p style='margin-left: 0'><font color=black size='1px'><B>Sperimentatore</B></font></p>
									 </Th>
									 <Th bgcolor='#99C1CC' width='150'>
									 <p style='margin-left: 0'><font color=black size='1px'><B>Promotore</B></font></p>
									 </Th>
									 <Th bgcolor='#99C1CC' width='150'>
									 <p style='margin-left: 0;'><font color=black size='1px'><B>Relatori</B></font></p>
									 </Th>
									 </tr>";
					*/
				
					
					
					/* $sql_1=new query($this->conn);
					$center_sql="select * from ce_info_studio where id_stud = {$id_stud}";
					$sql_1->exec($center_sql);
					$sql_1->get_row();
 */
					$txt.= "<TABLE align='center' BORDER=1 WIDTH='100%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>ID studio</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['UNIQUE_ID']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Codice Emendamento</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['IDE_CODICE']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Tipologia Studio</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['TIPOLOGIA']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Codice studio</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['COD_STUD']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Titolo studio</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['TITOLO_STUD']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Fase</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['DS_FASE_D']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>EudraCT</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['DS_CODICEEUDRACT']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Promotore</td>
											<td width='80%' bgcolor='#D2EFDB'>{$sql_em->row['PROMOTORE']}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Sperimentatore</td>
											<td width='80%' bgcolor='#D2EFDB'>{$princ_investiga}</td>
										</tr>
										<tr>
											<td width='20%' bgcolor='#DAE9ED'>Relatori</td>
											<td width='80%' bgcolor='#D2EFDB'>$nrel</td>
										</tr>
								 ";
					
					#Relazioni
						$relatore_txt='';
						$query_relazioni="select * from gse_relazioni_eme where {$this->xmr->pk_service}={$this->pk_service} and id_stud = {$id_stud} and vprogr_eme={$param_1} and progr_val_eme={$param_2}";
						$sql_relazioni=new query($this->conn);
						$sql_relazioni->exec($query_relazioni);
						
						while($sql_relazioni->get_row()){
							$relatore = $this->getDatiUtente2($sql_relazioni->row['USERID_INS']);
							if($sql_relazioni->row['NOTE'] != '') $relatore_txt.="<b>Relazione a cura di ".$relatore['QUALIFICA']." ".$relatore['NOME']." ".$relatore['COGNOME'].":</b><br>".$sql_relazioni->row['NOTE']."<br/><br/>";
						}
						
						
						#Osservazioni
						$osservatore_txt='';
						$query_osservazioni="select * from gse_osservazioni_eme where {$this->xmr->pk_service}={$this->pk_service} and id_stud = {$id_stud} and vprogr_eme={$param_1} and progr_val_eme={$param_2}";
						$sql_osservazioni=new query($this->conn);
						$sql_osservazioni->exec($query_osservazioni);
						
						while($sql_osservazioni->get_row()){
							$osservatore = $this->getDatiUtente2($sql_osservazioni->row['USERID_INS']);
							if($sql_osservazioni->row['NOTE'] != '') $osservatore_txt.="<b>Osservazione a cura di ".$osservatore['QUALIFICA']." ".$osservatore['NOME']." ".$osservatore['COGNOME'].":</b><br/>".$sql_osservazioni->row['NOTE']."<br/><br/>";
						}
									
					$txt.= "<tr>
										<td width='20%' bgcolor='#DAE9ED'>Relazioni Componenti</td>
										<td width='80%' bgcolor='#D2EFDB'>$relatore_txt</td>
									</tr>
									<tr>
										<td width='20%' bgcolor='#DAE9ED'>Osservazioni Componenti</td>
										<td width='80%' bgcolor='#D2EFDB'>$osservatore_txt</td>
									</tr>
								 ";
					
				}
//						if ($tableParere){
//						$vid = 4;
//						$esam = 1;
//						$v_pr_par=$param_center-1;
//						switch ($tableParere){
//							case "CE_EME_VALUTAZIONE":
//								$vid = 20;
//								$esam = 3;
//								break;
//						}
//						
//						//GIULIO 10-07-2012// Per ogni studio stampo tutti i pareri dei centri inviati in banca dati
//						$sql_count_pareri="select * from $tableParere v, ce_coordinate c where v.id_stud = {$id_stud} and v.visitnum=$vid and v.esam=$esam 
//															 	and c.fine=1
//															 	and v.id_stud=c.id_stud 
//															 	and v.visitnum=c.visitnum
//															 	and c.visitnum_progr=v.visitnum_progr
//															 	and c.esam=v.esam
//															 	and v.progr=c.progr
//															 	 and v.visitnum_progr = (select max(visitnum_progr)
//                    from CE_EME_VALUTAZIONE
//                   where id_stud = {$id_stud}
//                   and esam=$esam
//                   )
//   and v.progr=(select max(progr) from CE_EME_VALUTAZIONE where visitnum_progr=(
//                   select max(visitnum_progr)
//                    from CE_EME_VALUTAZIONE
//                   where id_stud = {$id_stud}
//                   and esam=$esam))
//																";

					/* 	$sql_count_pareri="select * from CE_EME_VALUTAZIONE where id_stud = {$id_stud} and visitnum_progr={$param_1} and progr={$param_2} and link_verbale={$this->pk_service}";						
						//echo "<br>$sql_count_pareri<br>";
						$sql_cp=new query($this->conn);
						$sql_cp->exec($sql_count_pareri);
						while($sql_cp->get_row()){
							
//							$espressione="";
//							if($sql_cp->row['ESPRESSIONE_PARERE']==1) $espressione="Parere espresso all'{$sql_cp->row['D_ESPRESSIONE_PARERE']}";
//							if($sql_cp->row['ESPRESSIONE_PARERE']==2) $espressione="Parere espresso a {$sql_cp->row['D_ESPRESSIONE_PARERE']}";

							$txt.= "<tr>
												<td width='20%' bgcolor='#DAE9ED'>Centro</td>
												<td width='80%' bgcolor='#D2EFDB'>{$sql_cp->row['D_CENTRO']}</td>
											</tr>
											<tr>
												<td width='20%' bgcolor='#DAE9ED'>Rilievi Generali</td>
												<td width='80%' bgcolor='#D2EFDB'>{$sql_cp->row['OBIETTIVO']}</td>
											</tr>
											<tr>
												<td width='20%' bgcolor='#DAE9ED'>Parere</td>
												<td width='80%' bgcolor='#D2EFDB'>{$sql_cp->row['D_RIS_DELIB']}.&nbsp;$espressione</td>
											</tr>
										 ";
						} */
												
//					}	

	$txt.= "<BR/></TABLE><BR/>";
	
			}
		$txt .= "<p>&nbsp;</p>";
		return $txt;
	}	
	
	function elenco_studi_centri_Verbale($studi, $tableParere, $param, $param2,$new_studies=null){
		$sql=new query($this->conn);
		$i = 0;
		$txt = "";
		$titolo_pu_ok="";
		$titolo_pe_ok="";
		$titolo_osserv_ok="";
		
		#Quero gli studi selezionati nella prima scheda di VERBALE
		$sql_verb=new query($this->conn);
		$sql_query_verb="select * from {$this->service}_pres_studi where {$this->xmr->pk_service}={$this->pk_service} and visitnum=2"; // and esam=1";
		$sql_verb->exec($sql_query_verb);
		$sql_verb->get_row();
		//echo $sql_verb->row['STUDI']."<br>";
		
		for ($k = 0; $k<count($studi);$k++){
			$s = $studi[$k];
			$s = trim($s);
			$stud_center = explode("_",$s);
			$id_stud=$stud_center[0];
			$param_center=$stud_center[1];
			
			/* echo $id_stud;
			echo "_";
			echo $param_center;
			echo "<br>"; */
			
			if ($s != ""){
				$k++;//Salto un record (Ã¨ l'utente)...
				$i++;
				$rel = trim($studi[$k]); //Recupero userid dell'utente
				$qsql="select d.*, to_date(substr(to_char(RICEZ_DOCUM_DT),1,9),'DD-MON-YY') as RICEZ_DOCUM_DT_D, to_date(substr(to_char(RICEZ_DOCUM_INTEGR_DT),1,9),'DD-MON-YY') as RICEZ_DOCUM_INTEGR_DT_D from doc_view_studi d where pair = '{$s}' ";
				$sql->exec($qsql);
				//echo $qsql;
				//echo("$sql_close<br/>");

				if ($sql->get_row()){
					
					#GC 08/05/2015#Nuova gestione multi relatore
					$nrel="";
					$rel_rows = explode("_",$rel);
					//$hl = in_array($this->user->userid,$rel_rows);
					foreach($rel_rows as $kiave => $valore) {$nrel.=$this->useridNome($valore)."<br/>";}
					//$nrel = substr($nrel, 0, -2);
					
					$princ_investig=$sql->row['PI'];
					
					$princ_investiga="PI: ".$princ_investig.", CENTRO: ".$sql->row['CENTRO']."<br>";
					$rel_studio=$nrel;
					
					$codice_studio_ce=$sql->row['CODICE_CE'];
				}
				
			$qsql2="SELECT * from(
					SELECT
						d.*,
						TO_DATE(substr(TO_CHAR(pce_seduta_dt),1,9),'DD-MON-YY') AS pce_seduta_dt_d
					FROM
						doc_viewobj_parerece d
					WHERE
						parent_id = '{$param_center}'
						)
					WHERE pce_seduta_dt_d = (select data_sed_dt from GSE_REGISTRAZIONE where id_sed={$this->pk_service})";
				$sql2=new query($this->conn);
				$sql2->exec($qsql2);
				$sql2->get_row();

			/* $sql_query_qs="select * from ce_registrazione where id_stud = $key1 ";
			$sql_qs=new query($this->conn);
			$sql_qs->exec($sql_query_qs);
			$sql_qs->get_row(); */
			
			$stud_interv='';
			$stud_osserv='';
			$stud_bio='';
			$stud_altro='';

			/* #Recupero Codice, Titolo e Sponsor
			$sql_query_dett="select * from gse_info_studio_odg where id_stud = $key1";
			$sql_dett=new query($this->conn);
			$sql_dett->exec($sql_query_dett);
			$sql_dett->get_row(); */
			
			//LUIGI classificazione post ordinamento colonna TIPO_ORDINAMENTO e PU_ACC
			if($sql->row['TIPO_SPER']==1 || $sql->row['TIPO_SPER']==2 || $sql->row['TIPO_SPER']==3 || $sql->row['TIPO_SPER']==4) $stud_interv=1;
			if($sql->row['TIPO_SPER']==6) {$stud_interv=1;$stud_bio=1;}
			//if($sql->row['TIPO_SPER']==-9900) {$stud_interv=1;$stud_altro=1;}
			if($sql->row['TIPO_SPER']==5) $stud_osserv=1;
			
			
			#Conteggio studi interventistici
			if($new_studies==1 and $stud_osserv==''){
								
				#Studi interventistici di cui AVR ha indicato essere il Coordinatore
				if ($stud_interv==1 and $sql->row['PARERE_UNICO']==1) {
					if($titolo_pu_ok==''){
						$txt.="<b><u>PARERE UNICO</u></b>";
						$titolo_pu_ok=1;
					}
					$conto_pu++;
					$conto_romano_pu=$this->numeri_romani($conto_pu);
					$txt.="<br/><br/><b>$conto_romano_pu Reg. Sper. {$codice_studio_ce}</b>";
				}
				
				#Studi interventistici di cui AVR ha indicato essere un Satellite
				if (($stud_interv==1 and $sql->row['PARERE_UNICO']==2) || $stud_bio==1 || $stud_altro==1) {
					if($titolo_pe_ok==''){
						$txt.="<hr break><br/><b><u>PARERI DI ETICITA'</u></b>";
						$titolo_pe_ok=1;
					}
					$conto_acc_pu++;
					$conto_romano_acc_pu=$this->numeri_romani($conto_acc_pu);
					$txt.="<br/><br/><b>$conto_romano_acc_pu Reg. Sper. {$codice_studio_ce}</b>";
				}

			}
			
			#Conteggio studi osservazionali
			if($new_studies==1 and $stud_osserv==1){
				if ($titolo_osserv_ok=='') {
					$txt.="<hr break><br/><b><u>STUDI OSSERVAZIONALI</u></b>";
					$titolo_osserv_ok=1;
				}
					$conto_osserv++;
					$conto_romano_osserv=$this->numeri_romani($conto_osserv);
					$txt.="<br/><br/><b>$conto_romano_osserv Reg. Sper. {$codice_studio_ce}</b>";
			}
			
			#Conteggio studi sospesi
			if($new_studies==''){
				$conto_sosp++;
				$conto_romano_sosp=$this->numeri_romani($conto_sosp);
				$txt.="<br/><br/><b>$conto_romano_sosp Reg. Sper. {$codice_studio_ce}</b>";
			}
			
//			#Conteggio studi biologici
//			if($new_studies==1 and $stud_bio==1){
//				
//				#Studi interventistici di cui AVR ha indicato essere il Coordinatore
//					if($titolo_bio_ok==''){
//						$txt.="<br/><b><u>STUDI BIOLOGICI</u></b>";
//						$titolo_bio_ok=1;
//					}
//					$conto_bio++;
//					$conto_romano_bio=$this->numeri_romani($conto_bio);
//					$txt.="<br/><br/><b>$conto_romano_bio Reg. Sper. {$codice_studio_ce[$key1]}</b>";
//
//			}
//			
//			#Conteggio studi 'altro'
//			if($new_studies==1 and $stud_altro==1){
//				
//				#Studi interventistici di cui AVR ha indicato essere il Coordinatore
//					if($titolo_altro_ok==''){
//						$txt.="<br/><b><u>ALTRI STUDI</u></b>";
//						$titolo_altro_ok=1;
//					}
//					$conto_altro++;
//					$conto_romano_altro=$this->numeri_romani($conto_altro);
//					$txt.="<br/><br/><b>$conto_romano_altro Reg. Sper. {$codice_studio_ce[$key1]}</b>";
//
//			}
			
			/* $pi_centro='';
 		 		foreach ($val1 AS $key2 => $val2){
    		//echo "Array di riga $key1, posizione $key2, contenuto $val2<br />\n";
    		//echo $val2."<br>";
    		$pi_centro.=$val2."<br>";
				} */
			
			$txt.= "<TABLE align='center' BORDER=1 WIDTH='100%' bordercolor='#99C1CC' cellspacing='0' cellpadding='0' style='border: 1 double #99C1CC'>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>ID STUDIO</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['UNIQUE_ID']}</td>
								</tr>
								<!--tr>
									<td width='20%' bgcolor='#DAE9ED'>Numero di registro sperimentazioni</td>
									<td width='80%' bgcolor='#D2EFDB'>{$codice_studio_ce}</td>
								</tr-->
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Data arrivo doc.</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['RICEZ_DOCUM_DT_D']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Data arrivo doc. integr.</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['RICEZ_DOCUM_INTEGR_DT_D']}</td>
								</tr>
								<tr>
									<td width='30%' bgcolor='#DAE9ED'>Tipologia Studio</td>
									<td width='70%' bgcolor='#D2EFDB'>{$sql->row['TIPOLOGIA']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Protocollo</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['COD_STUD']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Titolo studio</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['TITOLO_STUD']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Fase</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['DS_FASE_D']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>EudraCT</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['DS_CODICEEUDRACT']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Promotore</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql->row['PROMOTORE']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Sperimentatore, Centro Locale</td>
									<td width='80%' bgcolor='#D2EFDB'>{$princ_investiga}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Relatore</td>
									<td width='80%' bgcolor='#D2EFDB'>{$rel_studio}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Esito parere</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql2->row['PCE_ESITO_D']}</td>
								</tr>
								<tr>
									<td width='20%' bgcolor='#DAE9ED'>Note parere</td>
									<td width='80%' bgcolor='#D2EFDB'>{$sql2->row['PCE_NOTE']}</td>
								</tr>
								<br>
								</table>
							 ";
			
		
			}
				 
		
		}
		
		return $txt;
	}

	
	function getArray($sql, $field){
		$a = "";
		//if ($sql->get_row()){
		$a = $sql->row[$field];
		//}
		$a = explode("|",$a);
		$a = $this->suppressEmpty($a);
		return $a;
	}
	
	//Stringhe testuali
	function testo($testo){
		//$txt = parent::testo($testo);
		$this->testi['Home']="Home";
		$this->testi['Vista Paziente']="Dettaglio seduta";
		$this->testi['Lista completa'] =""; //"Lista completa delle schede della seduta";
		
		return parent::testo($testo);
	}

	//Elenco custom per gli studi in seduta
	function ListaStudi(){
		$txt = "";
		//Briciole di pane...
	    //$txt.="<p><a href=\"index.php\" >Home</a> &gt;&gt; ".$this->testo('Vista Paziente')."</p>";
	    //$txt.="<br/>";
	    $this->percorso = $this->breadcrumb ( "exam_list" );
		//Dettaglio
		$this->build_dettaglio();
		$txt .= $this->tb_riassuntiva();
	    $txt.="<br/>";
		//Pagina
	    //$txt.="<br/>";
	    $txt .= "
			<div id=\"droplinetabs1\" class=\"droplinetabs\">
				<ul class=\"nav nav-tabs\">";
    	//$txt .="
		//		<li><a  href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;VISITNUM={$key}&amp;exams=visite_exams.xml\">
		//			<span class='selected'>{$this->vlist->visitnums[$key]['SHORT_TXT']}</span></a>
		//		</li>";
		
    	$sql_query="select distinct visitnum,esam from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service}";
	
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			if (isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]))
			$visit_enabled[$sql->row['VISITNUM']]=true;
		}
	
		foreach ($this->vlist->visitnums as $key=>$val){
			if ($visit_enabled[$key])
			$txt.="
			<li><a  href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;VISITNUM={$key}&amp;exams=visite_exams.xml\">
				<span class='selected'>{$this->vlist->visitnums[$key]['SHORT_TXT']}</span></a>
			</li>
			";
		}    
	    
	    $txt .="<li><a class='selected' href=\"#\">
					<span>Lista studi in seduta</span></a>
				</li>
				</ul>
			</div>";
		
		//Contenuto
		$txt .= $this->TabellaStudi("{$this->service}_sel_studi",'STUDI_SOSPESI',"Studi da integrare/modificare",2);
		$txt .= '<br/>';
		$txt .= $this->TabellaStudi("{$this->service}_sel_studi",'STUDI',"Nuovi Studi",1);
		$txt .= '<br/>';
		$txt .= $this->TabellaStudi("{$this->service}_sel_studi",'STUDI_EMENDAMENTI',"Nuovi Emendamenti",3);
		$txt .= '<br/>';
		$txt .= $this->TabellaStudi("{$this->service}_sel_studi",'STUDI_EME_SOSP',"Emendamenti in attesa d'integrazione/modifica",4);
		$txt .= '<br/>';
		$txt .= "<p>Torna al <a href=\"index.php\">calendario &gt;&gt;</a></p>";
		$txt .= '<br/>';
		return $txt;
	}
	
	function TabellaStudi($tabella, $campo, $titolo, $tipo_oggetto){
		//echo($_SERVER['SERVER_NAME']);
		if ($_SERVER['SERVER_NAME']=="sirer-test.sissprep.cineca.it") $folder="sirer-test";
		else $folder="sirer";
		$txt = "";
		//Tabella contenuto
		$txt .= '
			<table class="table table-striped table-bordered table-hover" width="100%" cellspacing="0" cellpadding="2" border="0" align="center" style="border-color:#c0c0c0">
			<tbody>
				<tr>
					<th class="int" align="left" colspan="2">
						<!--a class="sc2b" href="#">'.$titolo.'</a-->
						'.$titolo.'
					</th>
				</tr>
			';
		
		//$txt .= "<p>Lista studi in seduta</p>";
		$sql=new query($this->conn);
		$qsql="select * from {$tabella} where {$this->xmr->pk_service}={$this->pk_service} "; //and visitnum=0"; // and esam=1";
		//echo "$qsql</br>";
		$sql->exec($qsql);
		$studi = "";
		if ($sql->get_row()){
			$studi = $sql->row[$campo];
		}
		//echo "ST:$studi";
		$studi = explode("|",$studi);
		//$txt .= "<ul>";
		for ($k = 0; $k<count($studi);$k++){
			$s = $studi[$k];
			$s = trim($s);
			
			$stud_center = explode("_",$s);
			$id_stud=$stud_center[0];
			$param_center=$stud_center[1];
			$param_2=$stud_center[2];
			
			//echo("$s<br/>");
			if ($s != ""){
				$k++;//Salto un record (?'utente)...
				$i++;
				$rel = trim($studi[$k]); //Recupero userid dell'utente
				if ($campo=="STUDI" || $campo=="STUDI_SOSPESI") 
					$qsql="select * from gse_VIEW_STUDI_ALL where code = '{$s}'";
				else 
					$qsql="select * from gse_VIEW_EME_ALL where code = '{$s}'";
				$sql->exec($qsql);
				//$sql->set_sql($qsql);
				//echo("$qsql<br/>");
				if ($sql->get_row()){
					
					#GC 08/10/2013#Nuova gestione multi relatore
					$nrel="";
					$rel_rows = explode("_",$rel);
					$hl = in_array($this->user->userid,$rel_rows);
					foreach($rel_rows as $kiave => $valore) {$nrel.=$this->useridNome($valore).", ";}
					$nrel = substr($nrel, 0, -2);
					
					$user_collegato=$this->user->userid;
					$info_user_collegato=$this->getDatiAna2($user_collegato);
					$profilo_user_collegato=$info_user_collegato['PROFILO'];
					
					//Testo
					$txt .= '
						<tr>
							<td class="sc4bis" width="10%" align="center">
								<a href="/'.$folder.'/app/documents/detail/'.$param_center.'" target="_blank">
								<img border="0" src="'.($hl?'/images/submitted.gif':'/images/to_be_comp.gif').'">
								</a>
							</td>
					';
					$txt .= '
							<td class="sc4bis" align="left">
					';
					$txt .= '<br/>
							<a href="/'.$folder.'/app/documents/detail/'.$param_center.'" style="text-decoration: none;" target="_blank">'.$sql->row['DECODE']." $nrel".($hl?'</b>':'').'<br/>
					';
					
					//Relatore -> inserisci relazione
					if ($hl && $profilo_user_collegato=='CMP'){
						
						if($tipo_oggetto==1 || $tipo_oggetto==2) $esam_rel=1;
						if($tipo_oggetto==3 || $tipo_oggetto==4) $esam_rel=3;
						
						$progr = $this->NextProgrRelazione($this->pk_service,$tipo_oggetto);
						$txta = "<font color='red'>Inserisci relazione</font>";
						$param_redir_rel="&PARAM_REDIR_REL=yes&amp;TIPO_OGGETTO=".$tipo_oggetto;
						$exists = $this->EsisteRelazione($this->pk_service,$id_stud,$param_center,$tipo_oggetto);
						if ($exists >0){
							$progr = $exists;
							$txta = "<font color='green'>Modifica relazione inserita</font>";
							$param_redir_rel="";
						}
						//GIULIO 28/01/2013 Condizione centro-specifica che non va bene per gli EMENDAMENTI che sono studio-speficici.
						if($param_center) $param_centro_spec="&PROGR_CENTRO={$param_center}";
						//$txt .= '
						//	<a href="index.php?CENTER=1&'.$this->xmr->pk_service.'='.$this->pk_service.'&ESAM=1&VISITNUM=1&VISITNUM_PROGR=0&PROGR='.$progr.'&ID_STUD='.$s.'"><img src="/images/insert.png" border="0" />'.$txta.'</a><br/>
						//	';
						
						
						
						$txt .= '
							<!--a href="index.php?'.$this->xmr->pk_service.'='.$this->pk_service.'&ESAM=1&VISITNUM=1&VISITNUM_PROGR=0&PROGR='.$progr.'&ID_STUD='.$id_stud.$param_centro_spec.$param_redir_rel.'"><img src="/images/insert.png" border="0" />'.$txta.'</a><br/><br/><br/-->
							<a href="index.php?'.$this->xmr->pk_service.'='.$this->pk_service.'&ESAM='.$esam_rel.'&VISITNUM=1&VISITNUM_PROGR=0&PROGR='.$progr.'&ID_STUD='.$id_stud.$param_centro_spec.$key_eme.$param_redir_rel.'"><img src="/images/insert.png" border="0" />'.$txta.'</a><br/><br/><br/>
							';
					}
					
					//Non relatore -> inserisci osservazione
					if (!$hl && $profilo_user_collegato=='CMP'){
						$progr = $this->NextProgrOsservazione($this->pk_service,$tipo_oggetto);
						$txta = "Inserisci osservazione";
						$param_redir_oss="&PARAM_REDIR_OSS=yes&amp;TIPO_OGGETTO=".$tipo_oggetto;
						$exists = $this->EsisteOsservazione($this->pk_service,$id_stud,$this->user->userid,$param_center,$tipo_oggetto);
						if ($exists >0){
							$progr = $exists;
							$txta = "<font color='green'>Modifica osservazione inserita</font>";
							$param_redir_oss="";
						}
						//GIULIO 28/01/2013 Condizione centro-specifica che non va bene per gli EMENDAMENTI che sono studio-speficici.
						if($param_center) $param_centro_spec="&PROGR_CENTRO={$param_center}";
						//$txt .= '
						//	<a href="index.php?CENTER=1&'.$this->xmr->pk_service.'='.$this->pk_service.'&ESAM=1&VISITNUM=1&VISITNUM_PROGR=0&PROGR='.$progr.'&ID_STUD='.$s.'"><img src="/images/insert.png" border="0" />'.$txta.'</a><br/>
						//	';
						
						if($tipo_oggetto==1 || $tipo_oggetto==2) $esam_oss=2;
						if($tipo_oggetto==3 || $tipo_oggetto==4) $esam_oss=4;
						
						$txt .= '
							<!--a href="index.php?'.$this->xmr->pk_service.'='.$this->pk_service.'&ESAM=2&VISITNUM=1&VISITNUM_PROGR=0&PROGR='.$progr.'&ID_STUD='.$id_stud.$param_centro_spec.$param_redir_oss.'"><img src="/images/reopen.png" border="0" />'.$txta.'</a><br/><br/><br/-->
							<a href="index.php?'.$this->xmr->pk_service.'='.$this->pk_service.'&ESAM='.$esam_oss.'&VISITNUM=1&VISITNUM_PROGR=0&PROGR='.$progr.'&ID_STUD='.$id_stud.$param_centro_spec.$key_eme.$param_redir_oss.'"><img src="/images/reopen.png" border="0" />'.$txta.'</a><br/><br/><br/>
							';
					}
					
					/* //Link diretto al parere degli studi (solo per Segreteria)
					if ($profilo_user_collegato=='SGR' && ($campo=='STUDI' || $campo=='STUDI_SOSPESI')){
						$center_id=$this->session_vars['CENTER'];
						$param_center--;		
									
						$query_max_prgr="select max(progr) progr from ce_valutazione where id_stud={$id_stud} and visitnum=4 and esam=1 and visitnum_progr={$param_center}";
						$sql_mp=new query($this->conn);
						$sql_mp->exec($query_max_prgr);
						$sql_mp->get_row();
						$progr_parere=$sql_mp->row['PROGR'];
						
					} */
					

					$txt .= '
								</td>
					';					
					$txt .= '
						</tr>
					';

					//$txt .= "<li><a href=\"/uxmr/index.php?&exams=visite_exam.xml&ID_STUD=$s\">".($hl?'<b>':'')."{$sql->row['TITOLO_PROT']}".($hl?'</b>':'')."</a><br/>";
					//$txt .= ($hl?'<b>':'')."Relatore: $rel<br/>".($hl?'</b>':'');
					//$txt .= "</li>";
				}
			}
		}
		//$txt .= "</ul>";
		$txt .= '
			</tbody>
			</table>
		';
		
		return $txt;
	}
	
	function EsisteRelazione($id, $stud, $pr_cnt, $tipo_oggetto){
		$retval = 0;
		
		if($tipo_oggetto==1 || $tipo_oggetto==2) $tab="relazioni";
		if($tipo_oggetto==3 || $tipo_oggetto==4) $tab="relazioni_eme";
		
		#GC 14/11/2014# Condizione centro-specifica e per gli emendamenti(in teoria dovrei usare VPROGR_EME per gli emennd).
		if($pr_cnt) $agg_and="and progr_centro={$pr_cnt}";
		
		$sql=new query($this->conn);
		$qsql="select * from {$this->service}_$tab r, {$this->service}_coordinate c where 
					 r.id_sed=c.id_sed and
					 r.visitnum=c.visitnum and
					 r.visitnum_progr=c.visitnum_progr and
					 r.esam=c.esam and
					 r.progr=c.progr and
					 c.inizio=1 and
		       c.{$this->xmr->pk_service}={$id} and 
		       r.id_stud = {$stud}
		       $agg_and";
		$sql->exec($qsql);
		//$sql->set_sql($qsql);
		//echo("$qsql<br/>");
		//if ($sql->get_row()){
		while($sql->get_row()){
			#GC 08/10/2013#Nuova gestione multi relatore. Controllo se esiste una relazione del relatore collegato al sistema
			if($sql->row['USERID_INS']==$this->user->userid) $retval = $sql->row['PROGR'];
		}
		return $retval;
	}
	
	function NextProgrRelazione($id, $tipo_oggetto){
		$retval = 1;
		
		if($tipo_oggetto==1 || $tipo_oggetto==2) $tab="relazioni";
		if($tipo_oggetto==3 || $tipo_oggetto==4) $tab="relazioni_eme";
		
		$sql=new query($this->conn);
		$qsql="select max(progr) as progr from {$this->service}_{$tab} where {$this->xmr->pk_service}={$id} ";
		$sql->exec($qsql);
		//$sql->set_sql($qsql);
		//echo("$sql_close<br/>");
		if ($sql->get_row()){
			$retval = $sql->row['PROGR'];
			$retval++;
		}
		return $retval;
	}

	function EsisteOsservazione($id, $stud, $user_oss, $pr_cnt, $tipo_oggetto){
		$retval = 0;
		
		if($tipo_oggetto==1 || $tipo_oggetto==2) $tab="osservazioni";
		if($tipo_oggetto==3 || $tipo_oggetto==4) $tab="osservazioni_eme";
		
		#GC 14/11/2014# Condizione centro-specifica e per gli emendamenti(in teoria dovrei usare VPROGR_EME per gli emennd).
		if($pr_cnt!="") $agg_and="and progr_centro={$pr_cnt}";
		
		$sql=new query($this->conn);
		$qsql="select * from {$this->service}_$tab o, {$this->service}_coordinate c where 
					 o.id_sed=c.id_sed and
					 o.visitnum=c.visitnum and
					 o.visitnum_progr=c.visitnum_progr and
					 o.esam=c.esam and
					 o.progr=c.progr and
					 c.inizio=1 and
					 c.{$this->xmr->pk_service}={$id} and 
					 o.id_stud = {$stud} and 
					 o.userid_ins='$user_oss' 
					 $agg_and";
		$sql->exec($qsql);
		//$sql->set_sql($qsql);
		//echo("$qsql<br/>");
		//if ($sql->get_row()){
		while($sql->get_row()){
			#GC 08/10/2013#Nuova gestione multi relatore. Controllo se esiste un'osservazione del componente collegato al sistema
			if($sql->row['USERID_INS']==$this->user->userid) $retval = $sql->row['PROGR'];
		}
		return $retval;
	}
	
	function NextProgrOsservazione($id, $tipo_oggetto){
		$retval = 1;
		
		if($tipo_oggetto==1 || $tipo_oggetto==2) $tab="osservazioni";
		if($tipo_oggetto==3 || $tipo_oggetto==4) $tab="osservazioni_eme";
		
		$sql=new query($this->conn);
		$qsql="select max(progr) as progr from {$this->service}_$tab where {$this->xmr->pk_service}={$id} ";
		$sql->exec($qsql);
		//$sql->set_sql($qsql);
		//echo("$qsql<br/>");
		if ($sql->get_row()){
			$retval = $sql->row['PROGR'];
			$retval++;
		}
		return $retval;
	}
		
	/////HOME PAGE
	function HomePage() {
		
		
		$prof = $this->getProfilo($this->user->userid);
		$highlight = "";
		$h = false;
		if ($prof == "CMP"){
			$highlight = "&HIGHLIGHT=1";
			$h = true;
		}
		/*
		else{
			parent::HomePage();
		}	
		*/
		
		/*
		$body = '<div style="display:block; float:left; width:80%;">'.$this->vlist->cal_monthly_sedute($h).'</div>';
		$body .= '<div style="display:block; float:right; width:20%; padding-top:95px;">';
		$body .= '<table border="0" cellpadding="2" cellspacing="2" style="" align="center" width="100%"><tr style="background-color:#999999; "><td><br/><b>Nuova riunione</b><br/>&nbsp;</td></tr>';
		$body .= '<tr style="background-color:#F0F0F0;line-height:2em;"><td><a href="index.php?VISITNUM=0&ESAM=0" >Inserisci nuova riunione</a></td></tr>';
		$body .= '</table>';
		$body .= '<table border="0" cellpadding="2" cellspacing="2" style="" align="center" width="100%"><tr style="background-color:#999999; "><td><br/><b>Prossime riunioni</b><br/>&nbsp;</td></tr>';
		$body .= '<tr style="background-color:#F0F0F0;line-height:2em;"><td>asd</td></tr>';
		$body .= '</table>';
		$body .= '</div>';
		*/
		$body = $this->vlist->cal_monthly_sedute($h);
		$redir = "index.php?SHOW_CAL_MONTHLY=1$highlight";
		//$body = '<script language="javascript">
		//		location.href="'.$redir.'";
		//		</script>';
		
		//$this->body .= $this->percorso;
		$this->percorso = $this->breadcrumb ( "home" );
		//echo $this->breadcrumb ( "home" );
		
		$this->body .= $body;	

		/*
	    $this->body.="    
		    <script>
		    $(\"table\").each(function (){
		    if(!$(this).is(\":has(table)\")){
		        var tabella=$(this);
		        $(\".int_hp\",this).click(function () {
		        		
		        		$(this).toggleClass(\"int_hp_on\");
		            $(\".destra-bis_hp\",tabella).slideToggle(\"fast\");
		        })
		        $(\".destra-bis_hp\",tabella).hide();
		    }
		   }
		  );
		  
		</script>"; 
	
	//Gestione di jquery per il banner scorrevole in HP
	    $this->script.="
	     <script type=\"text/javascript\" src=\"jquery.min.js\"></script>
	    <script>
	   
		 $(document).ready(function() {
		  // broken in IE 6 (wine)
		  $(\".scorrevole\").animate(
		    {left: ($(\".scorrevole\").width() - $(\".scorrevole\").parent().width() - $(\".scorrevole\").parent().width())},
		    20000
		  );
		
		});
		</script>
		";
		
		//Gestione funzioni menu laterale destro (cambio immagini on-off dei bottoni)
		$this->script.="
		<script type=\"text/javascript\">
		function MM_swapImgRestore() { //v3.0
		  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
		}
		
		function MM_preloadImages() { 
		  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
		    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
		    if (a[i].indexOf(\"#\")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
		}
		
		function MM_findObj(n, d) { 
		  var p,i,x;  if(!d) d=document; if((p=n.indexOf(\"?\"))>0&&parent.frames.length) {
		    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
		  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
		  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
		  if(!x && d.getElementById) x=d.getElementById(n); return x;
		}
		
		function MM_swapImage() {
		  var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
		   if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
		}
		
		</script>
		";
		*/
		
	}
	
	
	function numeri_romani($cifra){
  # ricaviamo il numero intero dal parametro passato alla funzione
  $numero = intval($cifra);

  # creo una variabile vuota che utilizzerÃ² per l'output
  $output = '';

  # creaiamo un array di numeri romani
  # giÃ  ordinati progressivamente da piÃ¹ grande al piÃ¹ piccolo
  $numeri_romani = array(
    'M' => 1000,
    'CM' => 900,
    'D' => 500,
    'CD' => 400,
    'C' => 100,
    'XC' => 90,
    'L' => 50,
    'XL' => 40,
    'X' => 10,
    'IX' => 9,
    'V' => 5,
    'IV' => 4,
    'I' => 1
  );

  # cicliamo l'array 
  foreach ($numeri_romani as $val => $v) 
  {
    # dividiamo il parametro della funzione per i valori contenuti
    # nell'array e ricaviamo dal risultato il numero intero 
    $valore = intval($numero / $v);

    # ripetiamo la stringa ottenuta per un numero di volte pari al
    # numero intero ottenuto in precedenza
    $output .= str_repeat($val, $valore);

    # calcoliamo il resto della divisione
    $numero = $numero % $v;
  }

  # valore di ritorno della funzione
  return $output;
}
	
			
}

?>