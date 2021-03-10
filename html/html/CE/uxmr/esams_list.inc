<?php

class xml_esams_list extends xml_esams_list_prototype{

var $pincopalla = "PINCOPALLA";

function testo($testo){
	//if(!isset($this->testi[$testo])){
		if($this->lang=='en'){
			$this->testi['Elimina']="Delete from study";
			$this->testi['Sei sicuro di voler chiudere le schede associate al blocco']="Are you sure that you want to close forms associated to block";
			$this->testi['Chiudi Schede']="Close Forms";
		}
		else{
			$this->testi['Elimina']="Elimina";
			$this->testi['Sei sicuro di voler chiudere le schede associate al blocco']="Sei sicuro di voler chiudere le schede associate al blocco";
			$this->testi['Chiudi Schede']="Chiudi Schede";
		}
	//}
	$testo = parent::testo($testo);
	if ($testo){
		return $testo;
	}
	return $this->testi[$testo];
}


function print_esams($es_val, $key, $esam, $vprogr=0){
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		if($es_val['HEADER']!="")$header="<tr><td class=\"sc4bis\"></td><td class=\"int exam_header\" style=\"text-align:left;\">{$es_val['HEADER']}</td></tr>";
		if ($vprogr!=null) $agg_param="&VISITNUM_PROGR={$vprogr}";
		else $agg_param="";
		global $service;
		$nome_form=$es_val['TESTO'];
		//ESAMI NON PROGRESSIVO
		if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
			$img="to_be_comp.gif";
			$progr=1;
			if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
			if ($es_val['RES'][$progr]['INIZIO']=='0' || $es_val['RES'][$progr]['INIZIO']=='') $img="to_be_comp.gif";
			if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
			if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
			$date=$es_val['RES'][$progr]['INSERTDT'];
			if ($es_val['FOTH'] && ($es_val['RES'][$progr]['FINE']=='1' || $es_val['FOTH_ALWAYS']=='yes'))
			{
				if(isset($es_val['EOTH']) && $es_val['EOTH']!=='')$esam_oth=$es_val['EOTH'];
				else $esam_oth=$es_val['NUMBER'];
				$query_data="select {$es_val['FOTH']} as FOTH from {$config_service['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}' and esam={$esam_oth}";
				$sql2=new query($conn);
				$sql2->set_sql($query_data);
				$sql2->exec();
				$sql2->get_row();
				$foth=$sql2->row['FOTH'];
				$nome_esame=$es_val['TESTO'].$foth;
			}
			else{
			$nome_esame=$es_val['TESTO'];
			}
			if($es_val['INS_DATE']=='yes'){
				$nome_esame.=$date;
			}
			if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
			if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1')
			{


				$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=1&amp;form=".$es_val['XML']."{$agg_param}\">";

				$close_href="</a>";


				if ($es_val['INDENT']=='yes') $indent="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
				else $indent="";
				$img_tag="<img src=\"/images/$img\" border=\"0\">";

				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
					$agg_where='';
					if ($vprogr!=null) $agg_where="and VISITNUM_PROGR={$vprogr}";
					$sql_query="select count(*) as c from {$service}_eqfield where
					esam={$esam}
					and visitnum=$key
					and progr=$progr
					$agg_where
					and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
					and eq_int={$this->integrazione->eq_int}
					";
					$sql2=new query($this->conn);
					$sql2->get_row($sql_query);
					if ($sql2->row['C']>0){
						$img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
						//$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
						$nome_esame.="</a><b>(scheda modificata in fase di integrazione)</b>";
					}
				}
				if ($es_val['RES']['1']['EQ_ACTION']==1){
					$img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
					$nome_esame.="</a><b>(scheda aggiunta in fase di integrazione)</b>";
				}
			if ($es_val['RES']['1']['EQ_ACTION']==2){
					$img_tag="<img src=\"images/iphone_delete_icon.png\" width=\"15px\" title=\"La scheda rimossa in fase di integrazione\">".$img_tag;
					$nome_esame.="</a><b>(scheda rimossa in fase di integrazione)</b>";
				}
				$this->body.="{$header}
									<tr>
										 <td class=\"sc4bis\" width=\"10%\" align=\"center\">{$indent}{$href}{$img_tag}{$close_href}
										</td>
										<td class=\"sc4bis\" align=\"left\">{$indent}$href".$nome_esame."$close_href<br/>
										</td>
									</tr>
										";
			}
		}
		//ESAMI PROGRESSIVI
		else {
			$last_progr=0;
			$form_alt='';
			if (isset($es_val['RES']) && !isset($es_val['CORR'])){
				if(isset($es_val['ALL_IN'])){

					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							if ($es_val['DATA']!='') {
								$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								$sql2->set_sql($query_data);
								$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['DATA'];
							}
							if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
						}
						$last_progr=$es_progr;
					}
					$n_progr=0;
					$init=false;
					$all_completed=true;
					$eq_present=false;
					$add_text='';
					$count_added=0;
					$count_deleted=0;
					$all_deleted=true;
					$all_added=true;
					foreach ($es_val['RES'] as $keys => $val) {
						if ($val['INIZIO']=='1') $n_progr++;
						if ($val['INIZIO']=='' || $val['INIZIO']=='0') $img="to_be_comp.gif";
						if ($val['INIZIO']=='1') $init=true;
						if ($val['FINE']!='1') $all_completed=false;
						if ($val['INV_QUERY']!='') $eq_present=true;
						if ($val['EQ_ACTION']==2) {
							$all_added=false;
							$count_deleted++;
						}
						if ($val['EQ_ACTION']==1) {
							$all_deleted=false;
							$count_added++;
						}
						if ($val['EQ_ACTION']==1) $add_text="</a><b>(Schede aggiunte/rimosse in fase di integrazione)</b>";
						if ($val['EQ_ACTION']==2) $add_text="</a><b>(Schede aggiunte/rimosse in fase di integrazione)</b>";
					}
					if ($add_text!='' && $all_added) $add_text="</a><b>(Schede aggiunte in fase di integrazione)</b>";
					if ($add_text!='' && $all_deleted) $add_text="</a><b>(Schede rimosse in fase di integrazione)</b>";
					if ($init) $img="saved.gif";
					if ($all_completed)  $img="submitted.gif";
					if ($n_progr==0) {
						$img="to_be_comp.gif";
						if($this->true_false['configurato'])
						$n_progr=$this->testi['nuovo_inserimento'];
						else
						$n_progr="Nuovo inserimento";
					}
					if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes'){
						$count_fine=0;
						foreach ($es_val['RES'] as $k_idx=>$val_idx){
							if ($val_idx['FINE']==1 || $val_idx['USERID']==$in['remote_userid']) {

								$count_fine++;
							}
						}
						$n_progr=$count_fine;
						if ($count_fine==0){
							$img="to_be_comp.gif";
						}
					}
					$date=" (".$n_progr.") ".$date;
					$nome_esame=$es_val['TESTO']." $date";
					$nome_esame.=$add_text;
					if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){

						$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";
						$close_href="</a>";
						$img_tag="<img src=\"/images/$img\" border=\"0\">";
						if ($eq_present){
							if ($all_deleted) $img_tag="<img src=\"images/iphone_delete_icon.png\" width=15px>".$img_tag;
							else $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;
						}
						
						#INIZIO GESTIONE AGGIUNTA FORZATA DOC GENERALE, FARMACI, TESSUTI e DISPOSTIVI
						$add_doc_gen="";
						$add_farmaci="";
						$add_dispositivi="";
						$add_farmaco_osserv="";
						$add_tessuti="";
						$add_dispositivi_osserv="";
						
						#GIULIO 04/02/13 - Controllo che lo studio non sia nel bel mezzo di un emendamento
						$query_em="select nvl(in_emendamento,0) as check_eme from {$config_service['service']}_registrazione where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
						$sql_em=new query($conn);
						$sql_em->set_sql($query_em);
						$sql_em->exec();
						$sql_em->get_row();
						
						#GIULIO 04/02/13 - Controllo che i dati generali siano stati inviati in BD
						$dati_gen_closed=$this->CheckVisitClosed($in[$config_service['PK_SERVICE']],0,0);
						
						$profilo = $this->getProfilo($conn,$this->session_vars['remote_userid']);
						
						#GC 01/12/2014#Nuova gestione EME. Elimino il filtro sugli emendamenti dall'if
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi documenti generali" in quanto possono inserire tramite l'eme
						//if($dati_gen_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==2 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC')) {
						if($dati_gen_closed && $es_val['NUMBER']==2 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_DOC_GEN=yes";
							$add_doc_gen="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi documenti generali</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi documenti generali\"> </a>";
						}
						
						#GC 01/12/2014#Nuova gestione EME. Elimino il filtro sugli emendamenti dall'if
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi farmaci" in quanto possono inserire tramite l'eme
						//if($dati_gen_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==6 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
						if($dati_gen_closed && $es_val['NUMBER']==6 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_FARMACI=yes";
							$add_farmaci="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi farmaci</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi farmaci\"> </a>";
						}
						
						#GC 01/12/2014#Nuova gestione EME. Elimino il filtro sugli emendamenti dall'if
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi dispositivi medici" in quanto possono inserire tramite l'eme
						//if($dati_gen_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==7 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
						if($dati_gen_closed && $es_val['NUMBER']==7 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_DISPOSITIVI=yes";
							$add_dispositivi="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi dispositivi medici</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi dispositivi medici\"> </a>";
						}
						
						#GC 01/12/2014#Nuova gestione EME. Elimino il filtro sugli emendamenti dall'if
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi farmaci" in quanto possono inserire tramite l'eme
						//if($dati_gen_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==15 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
					  if($dati_gen_closed && $es_val['NUMBER']==15 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_FARMACO_OSSERV=yes";
							$add_farmaco_osserv="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi farmaci</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi farmaci\"> </a>";
						}
						
						#GC 01/12/2014#Nuova gestione EME. Elimino il filtro sugli emendamenti dall'if
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi tessuti" in quanto possono inserire tramite l'eme
						//if($dati_gen_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==5 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
						if($dati_gen_closed && $es_val['NUMBER']==5 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_TESSUTI=yes";
							$add_tessuti="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi tessuti</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi tessuti\"> </a>";
						}
						
						#GC 01/12/2014#Nuova gestione EME. Elimino il filtro sugli emendamenti dall'if
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi dispositivi medici" in quanto possono inserire tramite l'eme
						//if($dati_gen_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==18 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
						if($dati_gen_closed && $es_val['NUMBER']==18 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='FAR')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_DISPOSITIVI_OSSERV=yes";
							$add_dispositivi_osserv="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi dispositivi</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi dispositivi\"> </a>";
						}
						
						#FINE GESTIONE AGGIUNTA FORZATA DOC GENERALE, FARMACI, TESSUTI e DISPOSTIVI
						
						#INIZIO GESTIONE DOWNLOAD ZIP GENERALE
						if($es_val['NUMBER']==2 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='CMP')) {
							$add_doc_gen.="<a href=\"getDocCeZip.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."\"><!--i><font color='red'>Scarica zip dei documenti generali</font></i--> <img src=\"images/zip2.png\" width=\"18px\" title=\"Scarica zip dei documenti generali\"> </a>";	
						}
						#FINE GESTIONE DOWNLOAD ZIP GENERALE
						
						#INIZIO GESTIONE AGGIUNTA FORZATA DOC CENTRO-SPECIFICA
						$add_doc_cs="";
						
						#GIULIO 04/02/13 - Controllo che i dati centro-specifici siano stati inviati in BD
						$dati_cs_closed=$this->CheckVisitProgrEnd($in[$config_service['PK_SERVICE']],1,$vprogr);
						
						#GC 01/12/2014#Nuova gestione EME. Elimino il filtro sugli emendamenti dall'if
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi documenti centro specifici" in quanto possono inserire documenti tramite l'eme
						//if($dati_cs_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==23 && $this->session_vars['VISITNUM']==1 && ($profilo=='SGR' || $profilo=='URC')) {
						if($dati_cs_closed && $es_val['NUMBER']==23 && $this->session_vars['VISITNUM']==1 && ($profilo=='SGR' || $profilo=='URC')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_DOC_CS=yes";
							$add_doc_cs="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi documenti centro specifici</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi documenti centro specifici\"> </a>";
							
						}
						#FINE GESTIONE AGGIUNTA FORZATA DOC CENTRO-SPECIFICA
						
						#INIZIO GESTIONE DOWNLOAD ZIP CENTRO-SPECIFICO
						if($es_val['NUMBER']==23 && $this->session_vars['VISITNUM']==1 && ($profilo=='SGR' || $profilo=='URC' || $profilo=='CMP' )) {
							$add_doc_cs.="<a href=\"getDocCeZipCentro.php?".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;VISITNUM_PROGR=$vprogr\"><!--i><font color='red'>Scarica zip dei documenti centro specifici</font></i--> <img src=\"images/zip2.png\" width=\"18px\" title=\"Scarica zip dei documenti centro specifici\"> </a>";	
						}
						#FINE GESTIONE DOWNLOAD ZIP CENTRO-SPECIFICO
						
						#INIZIO GESTIONE AGGIUNTA FORZATA CENTRO
						$add_centro="";
						
						#LUIGI 13/09/13 - Controllo che i dati generali siano stati inviati in BD
						$dati_centro_closed=$this->CheckVisitClosed($in[$config_service['PK_SERVICE']],0,0);
						
						#Se c'e' un emendamento in corso di compilazione -> elimino il link rosso "aggiungi documenti centro specifici" in quanto possono inserire documenti tramite l'eme
						if($dati_centro_closed && $sql_em->row['CHECK_EME']==0 && $es_val['NUMBER']==10 && $this->session_vars['VISITNUM']==0 && ($profilo=='SGR' || $profilo=='URC')) {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_CENTRO=yes";
							$add_centro="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"><!--i><font color='red'>aggiungi centro</font></i--> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi centro\"> </a>";
							
						}
						#FINE GESTIONE AGGIUNTA FORZATA CENTRO
						

						#INIZIO GESTIONE AGGIUNTA FORZATA DOCUMENTAZIONE VERBALE
						$dati_verbale_closed=$this->CheckVisitClosed($in[$config_service['PK_SERVICE']],2,$vprogr);
						if($dati_verbale_closed && $es_val['NUMBER']==20 && $this->session_vars['VISITNUM']==2 && $profilo=='SGR') {
							$agg_param.="&amp;AUTOPROGR&amp;FORCE_DOC_VERB=yes";
							$add_doc_verbale="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\"> <img src=\"images/add.png\" width=\"15px\" title=\"aggiungi documenti verbale\"> </a>";
							
						}
						#FINE GESTIONE AGGIUNTA FORZATA DOCUMENTAZIONE VERBALE
						

						$this->body.="{$header}
													<tr>
														 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
														</td>
														<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href $add_doc_gen $add_farmaci $add_dispositivi $add_farmaco_osserv $add_tessuti $add_dispositivi_osserv $add_doc_cs $add_centro $add_doc_verbale<br/>
														</td>
														<!--td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
														</td-->
													</tr>
												";
						if($es_val['NUMBER']==301 && $vprogr==0) {
							$this->body="<p style=\"color:red;margin:5 auto;margin-bottom:0px;text-align:center;font-weight:bold;\">ATTENZIONE: le confezioni presenti sono le copie di quelle inserite dall'azienda, divise in \"blocchi medicinali\"<br />
							Il collegamento al CTS e' incluso nel primo blocco.</p>"
							.$this->body;
						}
					}
				}
				else{
					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							if ($es_val['DATA']!='') {
								$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								$sql2->set_sql($query_data);
								$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['DATA'];
							}
							if ($es_val['VAL_AGG']!='') {
								$query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}' and esam='$esam'";
								$sql2->set_sql($query_data);
								$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['VAL_AGG'];
							}

							if ($last_progr+1!=$es_progr)
							while ($last_progr<$es_progr-1){

								$last_progr++;
								$n_progr=$last_progr;
								$img="to_be_comp.gif";
								$form_alt=str_replace(".xml", ".xml", $es_val['XML']);
								if (!file_exists($xml_dir."/".$form_alt)) $form_alt=$es_val['XML'];
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$form_alt."{$agg_param}\">";
								$nome_esame=$es_val['TESTO']." n. $n_progr";
								$close_href="</a>";
								if ($es_val['RES'][$es_progr]['EQ_INT']!=''){
									$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
								}
								if ($es_val['RES'][$es_progr]['INV_QUERY']!=''){

									if ($es_val['RES'][$es_progr]['EQ_ACTION']==2){
										if ($this->integrazione->eq_enabled) continue;
									}
									if ($es_val['RES'][$es_progr]['EQ_ACTION']==1){
										if (!$this->integrazione->eq_enabled) continue;
										$eq_present=true;
									}
								}
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
								if ($eq_present) $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;


								$this->body.="{$header}
																<tr>
																	 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}
							if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
							$n_progr=$es_progr;
							if (isset($es_val['VAL_AGG'])) $nome_esame="{$es_val['TESTO']} {$date}";
							else {
								if ($date!='') $date=" n.{$n_progr} ($date)";
								$nome_esame=$es_val['TESTO']." $date";
							}
							if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
								if ($es_progr!=''){
								}
								$close_href="</a>";
								if ($es_val['RES'][$es_progr]['EQ_INT']!=''){
									$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
								}
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
							if ($es_val['RES'][$es_progr]['INV_QUERY']!=''){

									if ($es_val['RES'][$es_progr]['EQ_ACTION']==2){
										if ($this->integrazione->eq_enabled) $record_deleted=true;
										else $record_deleted=false;
									}
									if ($es_val['RES'][$es_progr]['EQ_ACTION']==1){
										if (!$this->integrazione->eq_enabled) continue;
										$eq_present=true;
										$nome_esame.="</a><b>(Scheda aggiunta)</b>";
									}
								}
								if ($eq_present) $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;
								else {
										$sql_mod="select count(*) as C from {$this->config_service['service']}_EQFIELD
									where
									{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
									and ESAM=$esam
									and VISITNUM={$this->session_vars['VISITNUM']}
									and PROGR=$es_progr
									and VISITNUM_PROGR={$this->session_vars['VISITNUM_PROGR']}
									";
									$sql_mod_=new query($this->conn);
									$sql_mod_->get_row($sql_mod);
									if ($sql_mod_->row['C']>0) $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;

								}
								if ($record_deleted) $img_tag="<img src=\"images/iphone_delete_icon.png\" width=15px>".$img_tag;

								$this->body.="{$header}
																<tr>
																	 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}
							$last_progr=$es_progr;
						}

					}
				}
				if (($es_val['RES'][$es_progr]['FINE']==1 || $es_val['RES'][$es_progr]['INIZIO']=='' || $es_val['NEXT_ENABLED']!='') && !isset($es_val['ALL_IN']) && !$es_val['RES'][$es_progr]['VISITCLOSE']){
					if(!$this->true_false['configurato'])$this->testi['nuovo_inserimento']='Nuovo inserimento';
					if ($es_val['RES'][$es_progr]['INIZIO']!='') $next_progr=$es_progr+1;
					else $next_progr=$es_progr;
					$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."\">";
					$close_href="</a>";
				}
			}
		}
	}


function print_esams_OLD($es_val, $key, $esam, $vprogr=0){
		$in=$this->session_vars;
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		if($es_val['HEADER']!="")$header="<tr><td class=\"sc4bis\"></td><td class=\"int exam_header\" style=\"text-align:left;\">{$es_val['HEADER']}</td></tr>";
		if ($vprogr!=null) $agg_param="&VISITNUM_PROGR={$vprogr}";
		else $agg_param="";
		global $service;
		$nome_form=$es_val['TESTO'];
		//ESAMI NON PROGRESSIVO
		if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
			$img="to_be_comp.gif";
			$progr=1;
			if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
			if ($es_val['RES'][$progr]['INIZIO']=='0' || $es_val['RES'][$progr]['INIZIO']=='') $img="to_be_comp.gif";
			if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
			if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
			$date=$es_val['RES'][$progr]['INSERTDT'];
			if ($es_val['FOTH'] && ($es_val['RES'][$progr]['FINE']=='1' || $es_val['FOTH_ALWAYS']=='yes'))
			{
				if(isset($es_val['EOTH']) && $es_val['EOTH']!=='')$esam_oth=$es_val['EOTH'];
				else $esam_oth=$es_val['NUMBER'];
				$query_data="select {$es_val['FOTH']} as FOTH from {$config_service['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}' and esam={$esam_oth}";
				$sql2=new query($conn);
				$sql2->set_sql($query_data);
				$sql2->exec();
				$sql2->get_row();
				$foth=$sql2->row['FOTH'];
				$nome_esame=$es_val['TESTO'].$foth;
			}
			else{
			$nome_esame=$es_val['TESTO'];
			}
			if($es_val['INS_DATE']=='yes'){
				$nome_esame.=$date;
			}
			if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
			if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1')
			{


				$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=1&amp;form=".$es_val['XML']."{$agg_param}\">";

				$close_href="</a>";


				if ($es_val['INDENT']=='yes') $indent="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
				else $indent="";
				$img_tag="<img src=\"/images/$img\" border=\"0\">";

				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
					$agg_where='';
					if ($vprogr!=null) $agg_where="and VISITNUM_PROGR={$vprogr}";
					$sql_query="select count(*) as c from {$service}_eqfield where
					esam={$esam}
					and visitnum=$key
					and progr=$progr
					$agg_where
					and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
					and eq_int={$this->integrazione->eq_int}
					";
					$sql2=new query($this->conn);
					$sql2->get_row($sql_query);
					if ($sql2->row['C']>0){
						$img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
						//$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
						$nome_esame.="</a><b>(scheda modificata in fase di integrazione)</b>";
					}
				}
				if ($es_val['RES']['1']['EQ_ACTION']==1){
					$img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
					$nome_esame.="</a><b>(scheda aggiunta in fase di integrazione)</b>";
				}
			if ($es_val['RES']['1']['EQ_ACTION']==2){
					$img_tag="<img src=\"images/iphone_delete_icon.png\" width=\"15px\" title=\"La scheda rimossa in fase di integrazione\">".$img_tag;
					$nome_esame.="</a><b>(scheda rimossa in fase di integrazione)</b>";
				}
				$this->body.="{$header}
									<tr>
										 <td class=\"sc4bis\" width=\"10%\" align=\"center\">{$indent}{$href}{$img_tag}{$close_href}
										</td>
										<td class=\"sc4bis\" align=\"left\">{$indent}$href".$nome_esame."$close_href<br/>
										</td>
									</tr>
										";
			}
		}
		//ESAMI PROGRESSIVI
		else {
			//echo "<pre>PICOPALLA!</pre>";
			$last_progr=0;
			$form_alt='';
			if (isset($es_val['RES']) && !isset($es_val['CORR'])){
				if(isset($es_val['ALL_IN'])){

					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							if ($es_val['DATA']!='') {
								$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								$sql2->set_sql($query_data);
								$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['DATA'];
							}
							if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
						}
						$last_progr=$es_progr;
					}
					$n_progr=0;
					$init=false;
					$all_completed=true;
					$eq_present=false;
					$add_text='';
					$count_added=0;
					$count_deleted=0;
					$all_deleted=true;
					$all_added=true;
					foreach ($es_val['RES'] as $keys => $val) {
						echo "GIRO";
						print_r($es_val['RES'][$keys]);
						if ($val['INIZIO']=='1') $n_progr++;
						if ($val['INIZIO']=='' || $val['INIZIO']=='0') $img="to_be_comp.gif";
						if ($val['INIZIO']=='1') $init=true;
						if ($val['FINE']!='1') $all_completed=false;
						if ($val['INV_QUERY']!='') $eq_present=true;
						if ($val['EQ_ACTION']==2) {
							$all_added=false;
							$count_deleted++;
						}
						if ($val['EQ_ACTION']==1) {
							$all_deleted=false;
							$count_added++;
						}
						if ($val['EQ_ACTION']==1) $add_text="</a><b>(Schede aggiunte/rimosse in fase di integrazione)</b>";
						if ($val['EQ_ACTION']==2) $add_text="</a><b>(Schede aggiunte/rimosse in fase di integrazione)</b>";
					}
					if ($add_text!='' && $all_added) $add_text="</a><b>(Schede aggiunte in fase di integrazione)</b>";
					if ($add_text!='' && $all_deleted) $add_text="</a><b>(Schede rimosse in fase di integrazione)</b>";
					if ($init) $img="saved.gif";
					if ($all_completed)  $img="submitted.gif";
					if ($n_progr==0) {
						$img="to_be_comp.gif";
						if($this->true_false['configurato'])
						$n_progr=$this->testi['nuovo_inserimento'];
						else
						$n_progr="Nuovo inserimento";
					}
					if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes'){
						$count_fine=0;
						foreach ($es_val['RES'] as $k_idx=>$val_idx){
							if ($val_idx['FINE']==1 || $val_idx['USERID']==$in['remote_userid']) {

								$count_fine++;
							}
						}
						$n_progr=$count_fine;
						if ($count_fine==0){
							$img="to_be_comp.gif";
						}
					}
					$date=" (".$n_progr.") ".$date;
					$nome_esame=$es_val['TESTO']." $date";
					$nome_esame.=$add_text;
					if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){

						$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";
						$close_href="</a>";
						$img_tag="<img src=\"/images/$img\" border=\"0\">";
						if ($eq_present){
							if ($all_deleted) $img_tag="<img src=\"images/iphone_delete_icon.png\" width=15px>".$img_tag;
							else $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;
						}
						$to_assign="";
						if($es_val['NUMBER']==301) { //AIC3LIST='0' OR MEDICINALI like '%(aic:)%'
							$sql_query="select * from cp_vi_confezioni_uff where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and visitnum_progr={$vprogr}  and (aic6 is null or aic3 is null)";
//							echo $sql_query;
							$sql_aic=new query($this->conn);
							$sql_aic->exec($sql_query);
							$sql_aic->get_row();
							if($sql_aic->numrows>0)
							if($sql_aic->numrows==1)
							$to_assign=" - <b>".$sql_aic->numrows." confezione con aic3/aic6 da associare</b>";
							else
							$to_assign=" - <b>".$sql_aic->numrows." confezioni con aic3/aic6 da associare</b>";
						}

						$this->body.="{$header}
													<tr>
														 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
														</td>
														<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href $to_assign <br/>
														</td>
														<!--td class=\"sc4bis\" align=\"center\">
														</td>
														<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
														</td-->
													</tr>
												";
						if($es_val['NUMBER']==301 && $vprogr==0) {
							$this->body="<p style=\"color:red;margin:5 auto;margin-bottom:0px;text-align:center;font-weight:bold;\">ATTENZIONE: le confezioni presenti sono le copie di quelle inserite dall'azienda, divise in \"blocchi medicinali\"<br />
							Il collegamento al CTS e' incluso nel primo blocco.</p>"
							.$this->body;
						}
					}
				}
				else{
					foreach ($es_val['RES'] as $es_progr => $progr_vals){
						if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
							$sql2=new query($conn);
							if ($es_val['DATA']!='') {
								$query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}'";
								$sql2->set_sql($query_data);
								$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['DATA'];
							}
							if ($es_val['VAL_AGG']!='') {
								$query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."='{$in[$config_service['PK_SERVICE']]}' and  progr='{$es_progr}' and esam='$esam'";
								$sql2->set_sql($query_data);
								$sql2->exec();
								$sql2->get_row();
								$date=$sql2->row['VAL_AGG'];
							}

							if ($last_progr+1!=$es_progr)
							while ($last_progr<$es_progr-1){

								$last_progr++;
								$n_progr=$last_progr;
								$img="to_be_comp.gif";
								$form_alt=str_replace(".xml", ".xml", $es_val['XML']);
								if (!file_exists($xml_dir."/".$form_alt)) $form_alt=$es_val['XML'];
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$form_alt."{$agg_param}\">";
								$nome_esame=$es_val['TESTO']." n. $n_progr";
								$close_href="</a>";
								if ($es_val['RES'][$es_progr]['EQ_INT']!=''){
									$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
								}
								if ($es_val['RES'][$es_progr]['INV_QUERY']!=''){

									if ($es_val['RES'][$es_progr]['EQ_ACTION']==2){
										if ($this->integrazione->eq_enabled) continue;
									}
									if ($es_val['RES'][$es_progr]['EQ_ACTION']==1){
										if (!$this->integrazione->eq_enabled) continue;
										$eq_present=true;
									}
								}
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
								if ($eq_present) $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;


								$this->body.="{$header}
																<tr>
																	 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}
							if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
							if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
							if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
							$n_progr=$es_progr;
							if (isset($es_val['VAL_AGG'])) $nome_esame="{$es_val['TESTO']} {$date}";
							else {
								if ($date!='') $date=" n.{$n_progr} ($date)";
								$nome_esame=$es_val['TESTO']." $date";
							}
							if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
								$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."\">";
								if ($es_progr!=''){
								}
								$close_href="</a>";
								if ($es_val['RES'][$es_progr]['EQ_INT']!=''){
									$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
								}
								$img_tag="<img src=\"/images/$img\" border=\"0\">";
							if ($es_val['RES'][$es_progr]['INV_QUERY']!=''){

									if ($es_val['RES'][$es_progr]['EQ_ACTION']==2){
										if ($this->integrazione->eq_enabled) $record_deleted=true;
										else $record_deleted=false;
									}
									if ($es_val['RES'][$es_progr]['EQ_ACTION']==1){
										if (!$this->integrazione->eq_enabled) continue;
										$eq_present=true;
										$nome_esame.="</a><b>(Scheda aggiunta)</b>";
									}
								}
								if ($eq_present) $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;
								else {
										$sql_mod="select count(*) as C from {$this->config_service['service']}_EQFIELD
									where
									{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
									and ESAM=$esam
									and VISITNUM={$this->session_vars['VISITNUM']}
									and PROGR=$es_progr
									and VISITNUM_PROGR={$this->session_vars['VISITNUM_PROGR']}
									";
									$sql_mod_=new query($this->conn);
									$sql_mod_->get_row($sql_mod);
									if ($sql_mod_->row['C']>0) $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;

								}
								if ($record_deleted) $img_tag="<img src=\"images/iphone_delete_icon.png\" width=15px>".$img_tag;

								$this->body.="{$header}
																<tr>
																	 <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
																	</td>
																	<td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href<br/>
																	</td>
																	<!--td class=\"sc4bis\" align=\"center\">
																	</td>
																	<td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
																	</td-->
																</tr>
															";

							}
							$last_progr=$es_progr;
						}

					}
				}
				if (($es_val['RES'][$es_progr]['FINE']==1 || $es_val['RES'][$es_progr]['INIZIO']=='' || $es_val['NEXT_ENABLED']!='') && !isset($es_val['ALL_IN']) && !$es_val['RES'][$es_progr]['VISITCLOSE']){
					/*
					$show = true;
					echo "<pre>POLLOOO!</pre>";
					if (isset($es_val['next_cond_table']) && isset($es_val['next_cond_field'])){
						//Query data to show button
					}
					if ($show){
					*/
						if(!$this->true_false['configurato'])$this->testi['nuovo_inserimento']='Nuovo inserimento';
						if ($es_val['RES'][$es_progr]['INIZIO']!='') $next_progr=$es_progr+1;
						else $next_progr=$es_progr;
						$href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."\">";
						$close_href="</a>";
					//}
				}
			}
		}
	}


	/*
<div id="droplinetabs1" class="droplinetabs">
<ul>
<li><a href="http://www.dynamicdrive.com/"><span>Home</span></a></li>
<li><a href="http://www.dynamicdrive.com/style/"><span>CSS Examples</span></a></li>
<li><a href="http://tools.dynamicdrive.com"><span>Tools</span></a></li>
<li><a href="http://www.javascriptkit.com/"><span>JavaScript</span></a></li>
<li><a href="http://www.cssdrive.com"><span>Gallery</span></a></li>
</ul>
</div>
	 */
	function esams_list_html($service=null){
		if(isset($service)){
			$parametro_passato=true;
		}
		global $in;
		//$in=$this->session_vars;
		//print_r($in);
		$conn=$this->conn;
		$xml_dir=$this->xml_dir;
		$config_service=$this->config_service;
		global $patient_table;
		$sql=new query($conn);
		if(!$service)global $service;
		$sql_close="select min(visitclose) as chiusa from {$service}_coordinate where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
		$sql->set_sql($sql_close);
		$sql->exec();
		$sql->get_row();
		$chiusa=$sql->row['CHIUSA'];

		if ($config_service['PK_SERVICE']=='') $config_service['PK_SERVICE']=$this->PK_SERVICE;
		if ($config_service['VISITNUM_PROGR']=='1') {
			$add_vprogr="VISITNUM_PROGR,";
			$sql=new query($conn);
			$sql_select="select max(visitnum_progr) as maxvp from ".$service."_COORDINATE where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."'";
			$sql->set_sql($sql_select);
			$sql->exec();
			$sql->get_row();
			$max_vp=$sql->row['MAXVP'];
			foreach($this->visitnums as $visit => $vval){
				if ($vval['PROGR']=='yes') {
					$v_progr_esam_spec=$this->esams[$visit];
					unset($this->esams[$visit]);
					for ($i=0; $i<=$max_vp; $i++){
						$this->esams[$visit][$i]=$v_progr_esam_spec;
					}
				}
			}
		}
		$query="
		select userid,visitclose,visitnum,$add_vprogr esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato
		from ".$service."_COORDINATE
		where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."'
		and (EQ_ACTION is null or EQ_ACTION=2)
		order by visitnum,$add_vprogr esam ,progr";
		/*
		if ($this->config_service['eQuerySpec']['Integrazione']['ON']==1 && $this->session_vars['WFact']==$this->config_service['eQuerySpec']['Integrazione']['ROLE']){
			$sql_query="select * from {$service}_eq where
			stato!=1 and userid_ins='{$this->session_vars['remote_userid']}'
			and {$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}
			";
		$sql=new query($conn);
		if ($sql->get_row($sql_query)) {$eq_int=$sql->row['EQUERY_INT'];
			$query="
			select INV_QUERY,EQ_ACTION,userid,visitclose,visitnum,$add_vprogr esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato
			from ".$service."_COORDINATE
			where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."'
			and (EQ_ACTION is null or (INV_QUERY=$eq_int and EQ_ACTION=1))
			order by visitnum,$add_vprogr esam ,progr";
			}
		}
		*/
		if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
			$query="
			select INV_QUERY,EQ_ACTION,userid,visitclose,visitnum,$add_vprogr esam, progr, inizio, fine, to_char(insertdt, 'DD/MM/YYYY') as insertdt, abilitato
			from ".$service."_COORDINATE
			where {$config_service['PK_SERVICE']}='".$in[$config_service['PK_SERVICE']]."'
			/*
			and (EQ_ACTION is null or (INV_QUERY={$this->integrazione->eq_int} and EQ_ACTION=1))
			*/
			order by visitnum,$add_vprogr esam ,progr";
		}
		//echo $query;
		$sql=new query($conn);
		$sql->set_sql($query);
		$sql->exec();
		while ($sql->get_row()){
			//echo "<br/>";
			//print_r($sql->row);
			//echo "<br/>";
			if ($this->visitnums[$sql->row['VISITNUM']]['PROGR']=='yes') {
				if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']]['ENABLED']=true;
				
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']])){
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA']=$sql->row['VALIDATA'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE']=$sql->row['VISITCLOSE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['USERID']=$sql->row['USERID'];
					if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
						//echo "EQ_EN-INT:{$this->integrazione->eq_int}<br/>";
						$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION']=$sql->row['EQ_ACTION'];
						$this->esams[$sql->row['VISITNUM']][$sql->row['VISITNUM_PROGR']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INV_QUERY']=$sql->row['INV_QUERY'];
					}
					$this->visitnums[$sql->row['VISITNUM']]['CLOSED']=$sql->row['VISITCLOSE'];
				}
			}
			else {
				if (isset($this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']])){
					if ($sql->row['ABILITATO']=='1') $this->visitnums[$sql->row['VISITNUM']]['ENABLED']=true;
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['FINE']=$sql->row['FINE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INIZIO']=$sql->row['INIZIO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INSERTDT']=$sql->row['INSERTDT'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['ABILITATO']=$sql->row['ABILITATO'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VALIDATA']=$sql->row['VALIDATA'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['VISITCLOSE']=$sql->row['VISITCLOSE'];
					$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['USERID']=$sql->row['USERID'];
				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
						$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['EQ_ACTION']=$sql->row['EQ_ACTION'];
						$this->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['RES'][$sql->row['PROGR']]['INV_QUERY']=$sql->row['INV_QUERY'];
					}
					$this->visitnums[$sql->row['VISITNUM']]['CLOSED']=$sql->row['VISITCLOSE'];
				}
			}
		}

		if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && !$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT'][$_GET['VISITNUM']]){
			if($this->integrazione->stato==0)
			$this->body.="
			<div style='font-align:center;color:red;font-weight:bold'>
			Attenzione! le schede contrassegnate con il simbolo <img src=\"images/eq_img.png\" width=20px> hanno subito modifiche
			</div>
				";
			else
			$this->body.="
			<div style='font-align:center;color:#F57900;font-weight:bold'>
			Attenzione! le schede contrassegnate con il simbolo <img src=\"images/eq_img.png\" width=20px> sono in corso di approvazione
			</div>
				";
		}
		$equery_enabled=$this->integrazione->eq_enabled;
		$this->tab="<ul id=\"globalnav\">";
		foreach ($this->visitnums as $key => $val) {
			if ($val['VIEWABLE_ON_CLOSE']=='yes' && $in['USER_TIP']!='DE' && $val['CLOSED']!='1'){
				continue;
			}
			$af_progr="";
			if (isset($in['GROUP'])){
				$in['VISITNUM']='non so';
				if (isset($this->group[$in['GROUP']]['VISIT'][$key])){
					$in['VISITNUM']=$key;
				}
			}
			if ($in['VISITNUM']=='') $in['VISITNUM']=0;
            $controllo=$this->visitnums[$key];
            foreach($controllo as $chiave => $valore){
                if(is_numeric($chiave)){
                    $abilitato=$valore['ENABLED'] ;
                    break;
                }
                else {
                    $abilitato=false;
                }
            }
            
			if ($abilitato || $this->visitnums[$key]['ENABLED']){
				if ($in['VISITNUM']=="$key"){
					$tab_bar[$key]="<li class='active'><a class='selected' href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\"><span class='selected'>{$val['SHORT_TXT']}</span></a></li>";
				} else {
					$tab_bar[$key]="<li><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\"><span>{$val['SHORT_TXT']}</span></a></li>";
				}
			}
			if (!isset($in['VISITNUM']) || $in['VISITNUM']=="$key"){
				if ($val['PROGR']=='yes') {
					if (!$this->isVisitClose($key) && $val['BUTTONS_DISABLED']!='yes' && $in['USER_TIP']=='DE') $aggiungi_visita="<input type='button' value='".$this->testo('Aggiungi')."' onclick=\"
						window.location.href='index.php?CENTER={$in['CENTER']}&VISITNUM={$key}&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&CREATE_VPROGR=yes';
					\">";
					else $aggiungi_visita='';
					if ($aggiungi_visita=='' && $this->config_service['eQuerySpec']['Integrazione']['ON']==1 && $this->session_vars['WFact']==$this->config_service['eQuerySpec']['Integrazione']['ROLE']
					    && $val['BUTTONS_DISABLED']!='yes'){
						$aggiungi_visita="<input type='button' value='Aggiungi (Integrazione domanda)' onclick=\"
							if (confirm('Proseguendo, sara\\' possibile inserire un nuovo blocco di schede come integrazione alla domanda gia\\' inviata! Continuare?'))
							window.location.href='index.php?CENTER={$in['CENTER']}&VISITNUM={$key}&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&CREATE_VPROGR=yes';
							else return false;
							\">";
					}
					global $config_service;
					if (isset($config_service['class_visit_progr']))
					$style_table="class=\"{$config_service['class_visit_progr']}\" ";
					else $style_table="";
					$controllo=$this->visitnums[$key];
                    foreach($controllo as $chiave => $valore){
                        if(is_numeric($chiave)){
                            $abilitato=$valore['ENABLED'] ;
                            break;
                        }
                        else {
                            $abilitato=false;
                        }
                    }
					if ($abilitato)
					{	
						/*GC 23/05/2016 sostituisco la show_all con 2 bottoni per eseguirea anche il nascondi tutte le schede
						$this->body.="
		  				<table $style_table width=\"100%\">
							<tr class=int>
							<td>&nbsp;&nbsp;</td>
								<td width=80%>
								<a href=\"index.php?CENTER={$in['CENTER']}&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&exams=visite_exams.xml\">
									{$this->visitnums[$key]['TEXT']}
								</a>
								{$link_rep_farmacia}
								</td>
								<td align=center>
									$aggiungi_visita<br/>
									<a href=\"#\" onclick=\"
									//--show_all--
									return false;
									\">Mostra tutte le schede</a>
								</td>
							</tr>
						";*/
						
						$this->body.="
		  				<table $style_table width=\"100%\">
							<tr class=int>
							<td>&nbsp;&nbsp;</td>
								<td width=80%>
								<a href=\"index.php?CENTER={$in['CENTER']}&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&exams=visite_exams.xml\">
									{$this->visitnums[$key]['TEXT']}
								</a>
								{$link_rep_farmacia}
								</td>
								<td align=center>
									$aggiungi_visita<br/>
									<a href=\"#\" onclick=\"
									$('table[id^=af]').show();
									return false;
									\">Mostra tutte</a> / 
									<a href=\"#\" onclick=\"
									$('table[id^=af]').hide();
									return false;
									\">Nascondi tutte</a>
								</td>
							</tr>
						";
					}
					foreach($this->esams[$key] as $vprogr => $vesam) {
						if ($max_vprogr<$vprogr) $max_vprogr=$vprogr;
					}
					global $onload;
                    $count_label=1;
					foreach($this->esams[$key] as $vprogr => $vesam){
					    
						$nro=$count_label;                      
						if($val['SET_PROGR_START']=='')$nro_label=$nro;
						else $nro_label=$vprogr+$val['SET_PROGR_START'];
						if ($this->visitnums[$key][$vprogr]['ENABLED']){
						    
						    $count_label++;
							$param="";
							foreach($_GET as $gkey => $gval) if ($gkey!='VISITNUM_PROGR') $param.="$gkey=$gval&";
							if ($in['VISITNUM_PROGR']!=$nro-1 && $this->visitnums[$key]['SHOW_ALWAYS']!="yes") {
								$onload.="
								document.getElementById('af_{$key}_{$nro}').style.display='none';
								";
							}
							$show_all.="
								document.getElementById('af_{$key}_{$nro}').style.display='';
							";
							$not_delete=false;
							foreach ($vesam as $esam => $es_val){
								if ($es_val['RES'][1]['FINE']=='1') $not_delete=true;
							}
							if ($in['USER_TIP']!='DE') $not_delete=true;
							if ($val['BUTTONS_DELETE']!="yes" && ($not_delete || $val['BUTTONS_DISABLED']=='yes')) $delete_button="";
							else{
								//$delete_button="
								//		tasto elimina<input type='button' value='".$this->testo('Elimina')."' onclick=\"
								//			if (confirm('".$this->testo("Sei sicuro di voler eliminare")." {$this->visitnums[$key]['TEXT']} ".$this->testo("numero")." $nro?'))
								//				window.location.href='index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&VISITNUM_PROGR={$vprogr}&DelVisitProgr=yes';
								//			else return false;
								//		\">
								//	";
								$delete_button="
									<button class=\"btn btn-danger\" type=\"button\" onclick=\"
											if (confirm('".$this->testo("Sei sicuro di voler eliminare")." {$this->visitnums[$key]['TEXT']} ".$this->testo("numero")." $nro?'))
												window.location.href='index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&VISITNUM_PROGR={$vprogr}&DelVisitProgr=yes';
											else return false;
										\">
										<i class=\"fa fa-trash bigger-110\"></i>
										{$this->testo('Elimina')}
										</button>	
								";
							}
								
							//GIULIO 31-01-2013// Bottone per eliminare le visite progressive durante un emendamento. Per ora l'ho disabilitato per le visite 1,2,4,5,10,20. Eventualmente togliere le condizioni se deve apparire (ma testare il reale funzionamento)
							//in alternativa usare questa (!in_array($this->session_vars['VISITNUM'],$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT']))
							if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $in['VISITNUM']!='1' && $in['VISITNUM']!='2' && $in['VISITNUM']!='4' && $in['VISITNUM']!='5' && $in['VISITNUM']!='10' && $in['VISITNUM']!='20') $delete_button="<input type='button' value='".$this->testo('Elimina')."' onclick=\"
										if (confirm('".$this->testo("Sei sicuro di voler eliminare")." {$this->visitnums[$key]['TEXT']} ".$this->testo("numero")." $nro?'))
											window.location.href='index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&VISITNUM_PROGR={$vprogr}&DelVisitProgr=yes';
										else return false;
									\">";
							//if ($vprogr==0) $delete_button='';
							$close_button = "";
							//echo "<pre>UTIP: {$in['USER_TIP']}</pre>";
							//print_r($this->session_vars);
							//echo "<pre>SUTIP: {$this->session_vars ['USER_TIP']}</pre>";
							
							//LUIGI: pediatrico? usi terapeutici?
							$sql_query_x="select pediatrico, TIPO_SPER from ce_registrazione where id_stud={$in[$this->PK_SERVICE]}";
							$sql_x=new query($conn);
							$sql_x->exec($sql_query_x);
							$sql_x->get_row();
							
							if ($val['BUTTONS_CLOSE'] && !$this->CheckVisitClosed($in[$this->PK_SERVICE],$key,$vprogr) && ($in['USER_TIP']=='DE' || $this->session_vars['WFact']=='Segreteria CE' || $this->session_vars['WFact']=='Unita di ricerca')){
								$btext = $this->testo('Chiudi Schede');
								//$stato = $this->GetWFState($conn,$service,$in[$config_service['PK_SERVICE']]);
								switch ($service){
									case "CE":
										if ($key == 1){
											$btext = "Invia";
										}
										if ($key == 20){
											$btext = "Invia Emendamento e apri schede di valutazione";
										}
										break;
								}
								$disbutton = "";
								$onclick = "onclick=\"
											if (confirm('".$this->testo("Sei sicuro di voler chiudere le schede associate al blocco")." {$this->visitnums[$key]['TEXT']} ".$this->testo("numero")." $nro?'))
												window.location.href='index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&VISITNUM_PROGR={$vprogr}&CloseVisitProgr=yes';
											else return false;
										\"";
								
								
								#Condizioni di chiusura dei DATI CENTRO SPECIFICI
								if (!$this->CheckVisitClosed($in[$this->PK_SERVICE],0,0) || !$this->CheckVisitSaved($in[$this->PK_SERVICE],$key,$vprogr)){
									//echo "QUA";
									//$disbutton = 'disabled="disabled"';
									$onclick = 'onclick="alert(\'Non e\\\' possibile inviare i dati del centro prima dell\\\'invio dei dati dello studio e senza aver compilato tutte le schede centro specifiche. \')"';
								} #FINE
								
								
								#Condizioni di chiusura del blocco (visitnum_progr) EMENDAMENTI
								if ($key==20){
									
									if(!$this->CheckEsamSaved($in[$this->PK_SERVICE],$key,$vprogr,1)){
										$onclick = 'onclick="alert(\'E\\\' necessario inserire la scheda \\\'Dati Emendamento\\\' \')"';
									}else{
										$onclick = "onclick=\"
											if (confirm('".$this->testo("Sei sicuro di voler chiudere le schede associate al blocco")." {$this->visitnums[$key]['TEXT']} ".$this->testo("number")." $nro?'))
												window.location.href='index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&VISITNUM={$key}&VISITNUM_PROGR={$vprogr}&InviaEmendamento=yes';
											else return false;
										\"";
										}
									
									$query_a = "select min(nvl(FINE,0)) NO_BUTTON from ce_coordinate where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$vprogr} and esam=1";
									$sql_a = new query ( $this->conn );
									$sql_a->set_sql ( $query_a );
									$sql_a->exec ();
									$sql_a->get_row ();
									
								} #FINE
								
								#GC 20/11/2015 NUOVA_GRAFICA
								/*
								$close_button = "
										tasto invia<input type='button' value='".$btext."' $disbutton $onclick />
									";
								*/
								$close_button = "	
									<button class=\"btn btn-info\" type=\"button\" $disbutton $onclick>
										<i class=\"icon icon-lock bigger-110\"></i>{$btext}
									</button>	
								";
								
									
								//GIULIO 19-12-12//Non mostro il bottone di "invio dati centro specifici" se non ho riaperto quel centro tramite ISTRUTTORIA
								if($this->session_var['DEBUG']==1) echo "{$in[$this->PK_SERVICE]},$key,$vprogr<br>";
								//LUIGI: nuova gestione emendamenti nascondo anche il bottone degli eme
								if($this->CheckVisitProgrEnd($in[$this->PK_SERVICE],$key,$vprogr) || ($key==20 && $sql_a->row['NO_BUTTON'])) $close_button="";
								
								//LUIGI: Controllo di pertinenza delle visite progressive x invio. ATTENZIONE per la visita 20 (emendamenti) non deve essere eseguito
								$profilo = $this->getProfilo($conn,$this->session_vars['remote_userid']);
									if($profilo=='URC' && $key!=20){
										$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_nucleo_userid where id_nucleo=(
					  						select id_nucleo from ce_veneto_nucleo where id_str=(
				   							select centro from ce_centrilocali where id_stud='{$in[$this->PK_SERVICE]}' and progr={$vprogr}+1
				  							)
											) and userid='{$this->session_vars['remote_userid']}'";
									}
									if($profilo=='SGR' && $key!=20){
										// $sql_query_ce = "select count(*) as CONTO_CE from ce_centrilocali c,ce_veneto_sgr_userid_ins v
										 // where c.id_stud=v.center
										 // and id_stud='{$in[$this->PK_SERVICE]}' and progr={$vprogr}+1
										 // and userid='{$this->session_vars['remote_userid']}'
										 // and centro in (select id from ce_veneto_userid_ce where userid='{$this->session_vars['remote_userid']}')";
										 $sql_query_ce = "select count(*)as CONTO_CE from 
															(select c.userid,l.id_stud,l.progr as center
															from ce_veneto_userid_ce c,
																ce_centrilocali l,
																ana_utenti_2 a
																where c.id=l.centro
																and c.userid=a.userid
																and a.profilo = 'SGR')
														where id_stud='{$in[$this->PK_SERVICE]}'
														and center={$vprogr}+1
														and userid='{$this->session_vars['remote_userid']}'";
									}
									//echo $sql_query_ce."<br>";
									$sql_ce = new query ( $this->conn );
									$sql_ce->get_row ( $sql_query_ce );
									if ($sql_ce->row['CONTO_CE'] == '0' && $sql_x->row['PEDIATRICO']!=1) {
										$close_button="";
									}
								
							}
							
							if($in['VISITNUM']==1){
								
									if($this->session_vars['WFact']=='Unita di ricerca'){
									
										$sql_query_0="select centro from ce_centrilocali where id_stud={$in[$this->PK_SERVICE]} and progr=$vprogr+1";
										$sql_0=new query($conn);
										$sql_0->exec($sql_query_0);
										$sql_0->get_row();
										
										$sql_query_1="select count(*) as conteggio 
										from ce_centrilocali c, 
										ce_veneto_nucleo n, 
										ce_veneto_nucleo_userid u 
										where c.centro = n.id_str 
										and n.id_nucleo = u.id_nucleo 
										and id_stud={$in[$this->PK_SERVICE]} 
										and centro={$sql_0->row['CENTRO']} 
										and u.userid='{$this->session_vars['remote_userid']}' 
										and progr=$vprogr+1
										and c.stato=0";
										$sql_1=new query($conn);
										$sql_1->exec($sql_query_1);
										$sql_1->get_row();
									//print ($sql_query_0);
									if($sql_1->row['CONTEGGIO']==0)  {$delete_button="";}
										
								}
								
								if($this->session_vars['WFact']=='Segreteria CE'){
									
										$sql_query_0="select stato from ce_centrilocali 
										where id_stud={$in[$this->PK_SERVICE]}
										and progr=$vprogr+1";
										$sql_0=new query($conn);
										$sql_0->exec($sql_query_0);
										$sql_0->get_row();
										
										$sql_query_1="select count(*)as CONTEGGIO from 
													(select c.userid,l.id_stud,l.progr as center
													from ce_veneto_userid_ce c,
														ce_centrilocali l,
														ana_utenti_2 a
														where c.id=l.centro
														and c.userid=a.userid
														and a.profilo = 'SGR'
														and l.stato=0
														)
													where id_stud={$in[$this->PK_SERVICE]}
													and center=$vprogr+1
													and userid='{$this->session_vars['remote_userid']}'
													";
										//echo $sql_query_1."<br>";
										$sql_1=new query($conn);
										$sql_1->exec($sql_query_1);
										$sql_1->get_row();
									if( ($sql_1->row['CONTEGGIO']==0 && $sql_x->row['PEDIATRICO']!=1 ) || ( $sql_x->row['PEDIATRICO']==1 && $sql_0->row['STATO']!=0 ) )  {$delete_button="";}
										
								}
								
								
								//LUIGI: CENTRO INVIATO, SONO SEGRETERIA AFFERENTE O MEYER CON STUDIO PEDIATRICO
								//LUIGI: MA SE LO STUDIO NON E' IN CRMS E LO STATO CENTROSPECIFICO E' DIVERSO DA 0 E 4 POSSO INVIARLO
								//LUIGI: NON DEVE ESSERE USO TERAPEUTICO
								if($this->session_vars['WFact']=='Segreteria CE'){
									
										$sql_query_0="select * from ce_centrilocali 
										where id_stud={$in[$this->PK_SERVICE]}
										and progr=$vprogr+1";
										$sql_0=new query($conn);
										$sql_0->exec($sql_query_0);
										$sql_0->get_row();
										
										$sql_query_1="select count(*)as CONTEGGIO from 
													(select c.userid,l.id_stud,l.progr as center
														from ce_veneto_userid_ce c,
														ce_centrilocali l,
														ana_utenti_2 a
														where c.id=l.centro
														and c.userid=a.userid
														and a.profilo = 'SGR'
														and l.stato not in (0,4)
														and l.crpms_center_progr is null
														)
													where id_stud={$in[$this->PK_SERVICE]}
													and center=$vprogr+1
													and userid='{$this->session_vars['remote_userid']}'
													";
										//echo $sql_query_1."<br>";
										$sql_1=new query($conn);
										$sql_1->exec($sql_query_1);
										$sql_1->get_row();
									if( (($sql_1->row['CONTEGGIO']==1 && $sql_x->row['PEDIATRICO']!=1 ) || ( $sql_x->row['PEDIATRICO']==1 && $sql_0->row['STATO']!=0 && $sql_0->row['CRPMS_CENTER_PROGR']=="")) && $sql_x->row['TIPO_SPER']!=8)  {$delete_button="<button class=\"btn btn-danger\" type=\"button\" onclick=\"
											if (confirm('sei sicuro di voler procedere con l\'invio?')){
												ajax_send_crpms({$in[$this->PK_SERVICE]},{$vprogr});  
											}
											else return false;
											\">
											<i class=\"fa fa-send bigger-110\"></i>
											Invia dati al CRPMS
											</button>
										";}
										
								}
								
								

								if($this->session_vars['WFact']!='Unita di ricerca' && $this->session_vars['WFact']!='Segreteria CE'){$close_button=""; $delete_button="";}
								
							}
							
							if ($this->visitnums[$key]['DATA_TABLE']!=''){
								$sql2=new query($conn);
								$tbs=explode("|", $this->visitnums[$key]['DATA_TABLE']);
								$fields=explode(";", $this->visitnums[$key]['DATA_FIELD']);
								$lbls=explode("|", $this->visitnums[$key]['DATA_HEADER']);
								$alt = false;
								if ($this->visitnums[$key]['DATA_EXAM']){
									$alt = explode("|", $this->visitnums[$key]['DATA_EXAM']);
									for($j=0;$j<count($alt);$j++){
										if ($alt[$j]=="X"){
											$alt[$j]=$vprogr+1;
										}
										if ($alt[$j]=="P"){
											$alt[$j]=$vprogr;
										}
									}
								}
								$align = false;
								if ($this->visitnums[$key]['DATA_ALIGN']){
									$align = explode("|", $this->visitnums[$key]['DATA_ALIGN']);
								}
								$width = false;
								if ($this->visitnums[$key]['DATA_WIDTH']){
									$width = explode("|", $this->visitnums[$key]['DATA_WIDTH']);
								}
								$table='';
								$data='';
								$tb_content='';
								$tb_header='';
								$data_cols='';
								$f_count=0;
								$idx_start=0;
								$idx_end=0;
								$tot_field=0;
								for ($i=0;$i<count($tbs);$i++){
									//TODO: Modificare query!
									//print_r($alt);
									//print_r($fields);
									//print_r
									if ($alt && is_array($alt)){
										$sql_query="select {$fields[$i]} from {$service}_{$tbs[$i]} where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and visitnum={$alt[0]} and visitnum_progr={$alt[1]} and esam={$alt[2]} and progr={$alt[3]}";
									}else{
										$sql_query="select {$fields[$i]} from {$service}_{$tbs[$i]} where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and visitnum=$key and visitnum_progr=$vprogr";
									}
									$sql2->exec($sql_query);
									$fields_count[$i]=count(explode(",", $fields[$i]));
									$idx_start+=$fields_count[$i-1];
									$tot_field+=$fields_count[$i];
									$f_count=0;
									while ($sql2->get_row()){
										if ($sql2->n_r>1)
										$f_count=0;
										foreach ($sql2->row as $k_=>$v_){
											$data[$idx_start+$f_count].=$v_."<br/>";
											$f_count++;
										}
									}
								}
	
								for($i=0;$i<$tot_field;$i++){
									$data[$i]=rtrim($data[$i], "<br/>");
									$calign="right";
									if ($align[$i]) $calign=$align[$i];
									$cwidth="";
									if ($width[$i]) $cwidth='width="'.$width[$i]."\"";
									$tb_content.="<td valign=top align={$calign} $cwidth class=sc4bis>{$data[$i]}</td>";
								}
								foreach ($lbls as $l_idx=>$l_content){
									$tb_header.="<th valign=top class=int>$l_content</th>";
								}
	
								$table="<table width=100%><tr>$tb_header</tr><tr>$tb_content</tr></table>";
								$display="none";
							}
							else {
								$table='';
								$display='';
							}

							$onclick="";
							if ($es_val['RES'][1]['EQ_ACTION']==1 && $es_val['RES'][1]['INV_QUERY']=$eq_int){
								$eq_img_="<img src=\"images/eq_img.png\">";
							}
							
							/*
							$af_number=$nro-1;
							$clona_af="";
							if ($key==2) {
								//LUIGI: mette la clonazione pratica solo se la visitnum 4 e' aperta
							$sql_closed="select min(visitclose) as chiusa from {$service}_coordinate where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}' and visitnum = '{$key}'";
							$sql->set_sql($sql_closed);
							$sql->exec();
							$sql->get_row();
							$clona_chiusa=$sql->row['CHIUSA'];
							if ($clona_chiusa!=1)
							$clona_af="
							<input type=\"button\" value=\"Clona IMP Form $nro\"
												onclick=\"
												if (confirm('Attenzione, clonando questa IMP Form si cloneranno anche le schede relative.\\\nSi consiglia di compilarle prima di procedere alla clonazione.\\\n')) 
												window.location.href='index.php?VISITNUM=2&ID_SPER={$_GET['ID_SPER']}&VISITNUM_PROGR=$af_number&CLONA';
												else return false;
											\">
							
							";
							
							}
							*/
							
							$this->body.="
							<tr>
								<td valign=top class=sc4bis>
									&nbsp;<b>$nro_label. {$eq_img_}</b>
								</td>
								<td colspan=2>
								<table style=\"border:2px solid\" width=100%>
									<tr class=int>
										<td width=80%><!--TABATAB-->
											$table
										</td>
										<td valign=top align=center>
										$delete_button
										$close_button<br/>
										$clona_af
											<a href=\"#\" onclick=\"show_hide('af_{$key}_{$nro}'); return false;\">Mostra/nascondi schede</a>
										</td>
									</tr>
									<tr>
										<td colspan=2>
											<table id='af_{$key}_{$nro}' align=\"center\" style=\"display:;border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        					";
                                
							foreach ($vesam as $esam => $es_val){
								if ($vprogr==null) $vprogr="0";
                                $controllo=$es_val;
                                $abilitato=array_shift($controllo['RES']);
                                $abilitato=$abilitato['ABILITATO'] ;
                               
								if ($abilitato=='1' ) {
									//$this->body .= "QUQUQ";
									
									$this->print_esams($es_val,$key,$esam, $vprogr);
								}
							}
							$this->body.="
											</table>
										</td>
									</tr>
								</table>
							</td>
						</tr>";
						}
					}
					$this->body=str_replace("//--show_all--", $show_all, $this->body);
                    $controllo=$this->visitnums[$key];
                    foreach($controllo as $chiave => $valore){
                        if(is_numeric($chiave)){
                            $abilitato=$valore['ENABLED'] ;
                            break;
                        }
                        else {
                            $abilitato=false;
                        }
                    }
					if ($abilitato) $this->body.="</table>";
				}
				else{
					if ($this->visitnums[$key]['ENABLED']){
						$tbody_close='';
						$tbody_open='';
						$show_hide_link='';
						$count_schede=0;
						$schede_vuote=0;
						foreach ($this->esams[$key] as $esam => $es_val){
						    $controllo=$es_val;
						    $abilitato=array_shift($controllo['RES']);
                            $abilitato=$abilitato['ABILITATO'] ;
							if ($abilitato=='1') {
								$count_schede++;
							}
							if ($abilitato=='1') {
								foreach ($es_val['RES'] as $k_v=>$v_v){
									if ($v_v['INIZIO']!='1')
									$schede_vuote++;
								}
							}
						}
						if (isset($val['SHOW_HIDE'])){
							$tbody_open="<tbody id=\"VISITNUM_{$key}_TBODY\" style=\"display:none\">";
							$tbody_close="</tbody>
							<tbody id=\"VISITNUM_{$key}_TBODY_\" style=\"display:\">
								<tr>
									<td class=sc4bis>
									<ul>
										<li><b>Totale Schede: $count_schede</b></li>
										<li><b><font color=red>Schede vuote: $schede_vuote</font></b></li>
									</ul>
									</td>
							</tbody>
							";
							$show_hide_link="
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<a href=\"#\" onclick=\"
							show_hide('VISITNUM_{$key}_TBODY');
							show_hide('VISITNUM_{$key}_TBODY_');
							return false;
							\">Mostra/Nascondi tutte le schede</a>";
						}

						$this->body.="
		  		<table class=\"tab-content\" border=\"0\" align=\"center\" style=\"border-color:#c0c0c0\" cellpadding=\"2\" cellspacing=\"0\" width=\"100%\">
	        	<tr>
							<td class=\"int\" colspan=2 align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=".$val['NUMBER']."&amp;exams=visite_exams.xml\" class=\"sc2b\">".$val['TEXT']."</a>
						$show_hide_link
							</td>
				</tr>
				$tbody_open
						";

						foreach ($this->esams[$key] as $esam => $es_val){
						    $controllo=$es_val;
                            $abilitato=array_shift($controllo['RES']);
                            $abilitato=$abilitato['ABILITATO'] ;
							if ($abilitato=='1') {
								$this->print_esams($es_val,$key,$esam);
							}
						}
						$this->body.=$tbody_close;
					}
				}
			}

			global $service;
			$sql_close_visit="select nvl(min(visitclose),0) as close from {$service}_coordinate where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and VISITNUM=$key";
			$sql=new query($this->conn);
			$sql->get_row($sql_close_visit);
			if ($this->visitnums[$key]['CLOSE_VISIT']!='' && $sql->row['CLOSE']=='0' && $in['USER_TIP']=='DE' && ($in['VISITNUM']=='' || $in['VISITNUM']==$key)){
				if ($this->visitnums[$key]['CLOSE_VISIT_NOTE']){
					$this->body.="
				<tr>
					<td class=\"int\" colspan=2 align=center>
						<div id='BUTTON_CLOSE_VISIT' style=\"display:\">
						<input type=\"button\" value=\"{$this->visitnums[$key]['CLOSE_VISIT']}\"
						onclick=\"
						document.getElementById('CLOSE_VISIT_NOTE').style.display='';
						document.getElementById('BUTTON_CLOSE_VISIT').style.display='none';
						\"
						>
						</div>
						<div id='CLOSE_VISIT_NOTE' class=\"input\" style=\"display:none\">
						<form method='GET' action=\"index.php\" onsubmit=\"
						if (document.getElementById('NOTE_CHIUSURA_SPEC_ID').value==''){
							alert('Inserire note');
							return false;
						}
						\">
						<input type='hidden' name='{$this->PK_SERVICE}' value=\"{$in[$this->PK_SERVICE]}\">
						<input type='hidden' name='CLOSE_VISIT' value=\"$key\">
						{$this->visitnums[$key]['CLOSE_VISIT_NOTE']}:<br/>
						<textarea id='NOTE_CHIUSURA_SPEC_ID' name='NOTE_CHIUSURA_SPEC' cols=80 rows=5></textarea><br/>
						<input type='submit' value=\"Procedi\" onclick=\"
						if (document.getElementById('NOTE_CHIUSURA_SPEC_ID').value==''){
							alert('Inserire note');
							return false;
						}
						\">
						&nbsp; <input type='button' value=\"Annulla\"
						onclick=\"
						document.getElementById('CLOSE_VISIT_NOTE').style.display='none';
						document.getElementById('BUTTON_CLOSE_VISIT').style.display='';
						\"
						>
						</form>
						</div>
					</td>
				</tr>
					";
				}
				else
				$this->body.="
				<tr>
					<td class=\"int\" colspan=2 align=center>
						<input type=\"button\" value=\"{$this->visitnums[$key]['CLOSE_VISIT']}\"
						onclick=\"window.location.href=window.location.href+'&CLOSE_VISIT=$key';\"
						>
					</td>
				</tr>
				";
				
			}
			//echo "<hr>".$this->body."<hr>";

			/*
			//Dario - inserisco bottone INVIA
			$this->body.='
			<tr>
				<td class="int" colspan=2 align=center>
					<input type="button" name="nextStep" value="Invia" />
				</td>
			</tr>
			';
			*/
				
		}
		$tabs="
		<div id=\"droplinetabs1\" class=\"droplinetabs\">
			<ul class=\"nav nav-tabs\">
		";
			foreach ($tab_bar as $key=>$val){
				$tabs.=$val;
			}
			//if(checkInviataConfig($in[$config_service['PK_SERVICE']])==1) $invia_txt_tab="Ricevuta d'invio della domanda";
			//else $invia_txt_tab="VERIFICA E INVIA CTA";
			/*
			$sql_query="select id_stato from {$service}wf_stato where pk_service='{$in[$config_service['PK_SERVICE']]}'";
			$sql_stato=new query($this->conn);
			$sql_stato->exec($sql_query);
			$sql_stato->get_row();
			if($sql_stato->row['ID_STATO']>1 && $sql_stato->row['ID_STATO']!=5) $invia_txt_tab="Ricevuta d'invio della CTA";
			else 
			$invia_txt_tab="Invia CTA";
			if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='') $invia_txt_tab="Invia integrazione all'AIFA";
			if($this->config_service['service']!="CP_CART" && !($sql_stato->row['ID_STATO']==5 && $in['WFact']=="CE"))
			$tabs.="<li><a class='button' href=\"index.php?CENTER=".$in['CENTER']."&".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;SendAIFA=yes\"><span>$invia_txt_tab</span></a></li>";
			*/
			
			$stato = $this->GetWFState($conn,$service,$in[$config_service['PK_SERVICE']]);
			//echo ("ST: $stato");
			if ($stato == 9){
				$invia_txt_tab="Ritira studio";
				//$form_action = $_SERVER['REQUEST_URI'];
				$tabs.="<li><a class='selected' href=\"index.php?{$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}&amp;ShowRitiro=yes\">
							<span>$invia_txt_tab</span></a>
						</li>";			
			}
			//die("$service");
			if ($service == "GSE"){
				$tabs.="<li><a class='' href=\"index.php?{$config_service['PK_SERVICE']}={$in[$config_service['PK_SERVICE']]}&amp;clista=studi\">
					<span>Lista studi in seduta</span></a>
					</li>";
			}
			
			$tabs.="</ul>
			</div>";
			$this->body=$tabs.$this->body;
		if ($this->body!='')	$this->body.="</table>";
		global $service;
		$sql_close="select min(visitclose) as closed from {$service}_coordinate where {$config_service['PK_SERVICE']}='{$in[$config_service['PK_SERVICE']]}'";
		$sql2=new query($conn);
		$sql2->set_sql($sql_close);
		$sql2->exec();
		$sql2->get_row();
		if (isset($this->esams['CLOSE_ALL']) && $in['USER_TIP']=='DE' && $sql2->row['CLOSED']!='1')
		{
			$sql_query="select max(stato) as stato from {$service}_coordinate where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and abilitato=1";
			$sql=new query($conn);
			$sql->set_sql($sql_query);
			$sql->exec();
			$sql->get_row();
			if ($sql->row['STATO']=='2') {
				$sql_query="select min(fine) as fine from {$service}_coordinate where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and abilitato=1";
				$sql=new query($conn);
				$sql->set_sql($sql_query);
				$sql->exec();
				$sql->get_row();
				if ($sql->row['FINE']=='1')
				$this->body.="
			<p align=center id='close_all_p'>
			<a href=\"index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\">
			Invia revisione
			</a>
			</p>
		<script>
			document.getElementById('close_all_p').innerHTML='<input type=\\'button\\' value=\\'Invia revisione\\' onclick=\"window.location.href=\\'index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\\'\">';
		</script>
		";
			}
			else {
				$js_close_all=make_js($this->esams['CLOSE_ALL']);
				$this->body.="
			<p align=center id='close_all_p'>
			<a href=\"index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\">
			{$this->esams['CLOSE_ALL']}
			</a>
			</p>
		<script>
			document.getElementById('close_all_p').innerHTML='<input type=\"button\" value=\"{$js_close_all}\" onclick=\"if (confirm(\\'Attenzione!Preseguendo non sar? possibile effettuare modifiche alla pratica.\\'))window.location.href=\\'index.php?close_all=yes&{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}\\';else return false;\">';
		</script>
		";
			}
		}
		if ($equery_enabled && $eq_int!='') {
			$alert_int="<div align=\"center\" style=\"color:red;font-weight:bold\">
			Attenzione, ci sono schede in corso di integrazione, per rendere effettive le integrazioni apportate cliccare sul pulsante \"Invia Integrazione\" in basso
			</div>";
			$button="<p align=center><input type='button' value='Invia Integrazione' onclick=\"
						window.location.href='index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&SendAIFA=yes';
						\"></p>";
			$this->body=$alert_int.$this->body.$alert_int.$button;
		}

		
		////// ----Dario - bottone invia pratica
		//print_r($this);
		//die();
		//print_r($this->session_vars);
		//die($service);
		$profilo = $this->getProfilo($conn,$this->session_vars['remote_userid']);
		$stato = $this->GetWFState($conn, $service, $in[$this->PK_SERVICE]);
		$inEmendamento = $this->inEmendamento($conn, $service, $in[$this->PK_SERVICE]);
		$inEmeApprovazione = $this->inEmeApprovazione($conn, $service, $in[$this->PK_SERVICE]);
		
		//$this->body .= "<p>STATO: $stato</p>";
		$visitnum = ($this->session_vars['VISITNUM']?$this->session_vars['VISITNUM']:0);
		//Bottone chiudi visita (invia pratica)
		if (!$this->IsVisitClosed($conn, $service, $in[$this->PK_SERVICE], $visitnum) && (($this->session_vars['USER_TIP'] == "DE" && $stato<5) || ($this->session_vars['WFact']=='Segreteria CE' || $this->session_vars['WFact']=='Unita di ricerca'))){ //Stato minore di valutabile
			//$redir = "https://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
			//$this->body .= $this->PK_SERVICE;
			$redir = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&NextWFStep=yes&VISITNUM=".$visitnum; //Prima visita di default
			//print_r($this); //$pk = $_GET[''];
			
			//testo customizzato
			//$text = "Chiudi schede e procedi allo step successivo";
			$text = "Invia le schede correnti";
			//echo "ST:".$stato."SV:".$service;
			switch ($service){
				case "CE":
					if ($stato == 2){ //in compilazione da parte del nucleo
						//$text = "Invia studio alla segreteria del CE";
						$text = "Invia dati dello studio alla segreteria del CE";
					}
					if ($stato == 3 && $visitnum == 0){ //in compilazione da parte del nucleo
						$text = "Chiudi schede";
					}
					break;
				case "GSE":
					if ($stato == 1){ //da preparare
						$text = "Chiudi schede ODG";
					}
					if ($stato == 4){ //da verbalizzare
						$text = "Chiudi verbalizzazione";
					}
					break;
			}

			if($service == 'CE' && $visitnum == 0){
								
				$visibilita='';
				
				if($profilo=='SGR'){
					$query_userid_1="select count(*) as CONTO from CE_VENETO_SGR_USERID_INS where userid='{$this->session_vars['remote_userid']}' and center='{$in[$this->PK_SERVICE]}'";
					$sql_user_1=new query($conn);
					$sql_user_1->set_sql($query_userid_1);
					$sql_user_1->exec();
					$sql_user_1->get_row();

				  if ($sql_user_1->row['CONTO']>=1) $visibilita=1;
				}
				
				if($profilo=='URC') {
					$query_userid_1="select count(*) as CONTO_URC from ce_veneto_urc_userid_ins where userid='{$this->session_vars['remote_userid']}' and {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}'";
					$sql_user_1=new query($conn);
					$sql_user_1->set_sql($query_userid_1);
					$sql_user_1->exec();
					$sql_user_1->get_row();
						
					if ($sql_user_1->row['CONTO_URC']>=1) $visibilita=1;
				}
				
			}
			
			/* VECCHIA GESTIONE DEI BOTTONI DI INVIO CONVOCAZIONE/INTEGRAZIONI AI COMPONENTI
			#GIULIO 10-10-13# Bottone per l'invio della mail ai componenti
			if ($visitnum == 0 && $service == 'GSE'){
				
				$class_disabled_conv="";
				$convocazione_inviata="";
				$class_disabled_integr="";
				
				#Autorizzazione del Presidente
				$autorizzazione_presidente="";
				//$query_aut_presi="select nvl(AUT_PRESIDENTE,0) AUT_PRESIDENTE from {$service}_registrazione where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and visitnum=0";
				//$sql_aut_presi=new query($conn);
				//$sql_aut_presi->set_sql($query_aut_presi);
				//$sql_aut_presi->exec();
				//$sql_aut_presi->get_row();
				//$autorizzazione_presidente=$sql_aut_presi->row['AUT_PRESIDENTE'];
				
				#Se non hanno salvato la scheda di preparazione odg oppure non c'e' l'autorizzazione del presidente -> disabilito entrambi i bottoni
				$query_preparazione_odg="select nvl(INIZIO,0) INIZIO from {$service}_coordinate where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and visitnum=0 and visitnum_progr=0 and progr=1 and esam=10";
				$sql_prep_odg=new query($conn);
				$sql_prep_odg->set_sql($query_preparazione_odg);
				$sql_prep_odg->exec();
				$sql_prep_odg->get_row();
				if ($sql_prep_odg->row['INIZIO'] != 1 || $autorizzazione_presidente==0){
					$class_disabled_conv='disabled';
					$class_disabled_integr='disabled';
				}
				
				#Se hanno non hanno inviato la convocazione -> disabilito il bottone dell'integrazione
				#Se hanno già inviato la convocazione -> disabilito il bottone della convocazione
				$query_count_conv_odg="select count(*) as ODG_CONV from {$service}_CRONOLOGIA_ODG where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and tipo=1";
				$sql_conv_odg=new query($conn);
				$sql_conv_odg->set_sql($query_count_conv_odg);
				$sql_conv_odg->exec();
				$sql_conv_odg->get_row();
				if ($sql_conv_odg->row['ODG_CONV'] == 0){
					$class_disabled_integr='disabled';
				}
				if ($sql_conv_odg->row['ODG_CONV'] > 0){
					$convocazione_inviata=1;
					$class_disabled_conv='disabled';
				}
				
				
				
				$text_4 = "Invia convocazione ai componenti";
				if($convocazione_inviata) $text_4 = "Convocazione inviata ai componenti";
				$redir_4 = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&SendMailCompConv=yes";
				$this->body.='<table style="margin-top: 10px;" border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
				$this->body.='
				<button class="btn btn-warning '.$class_disabled_conv.' " onclick="if(confirm(\'Proseguire con l\\\'invio della mail ai componenti?\'))location.href=\''.$redir_4.'\'" type="button">
					<i class="fa fa-envelope bigger-110"></i>
					'.$text_4.'
				</button>
				';
				
				$text_2 = "Notifica integrazioni OdG ai componenti";
				$redir_2 = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&SendMailCompIntegra=yes";
				$this->body.='
				<button class="btn btn-warning '.$class_disabled_integr.' " onclick="if(confirm(\'Proseguire con l\\\'invio della mail ai componenti?\')) location.href=\''.$redir_2.'\'" type="button">
					<i class="fa fa-envelope bigger-110"></i>
					'.$text_2.'
				</button>
				';
				
				$this->body.='</td></tr></table>';
			}
			*/
			
			#GC 10/03/2016# Bottone per Richiesta Integrazioni OdG
			$alert_invio="";
			if($service == 'GSE' && $visitnum == 0){				
				$attiva_verbalizzazione="";
				$richiesta_integrazione="";
				$query_att_verb="select nvl(ATTIVA_VERBALIZZAZIONE,0) ATTIVA_VERBALIZZAZIONE from {$service}_registrazione where {$this->PK_SERVICE}='{$in[$this->PK_SERVICE]}' and visitnum=0";
				$sql_att_verb=new query($conn);
				$sql_att_verb->set_sql($query_att_verb);
				$sql_att_verb->exec();
				$sql_att_verb->get_row();
				$attiva_verbalizzazione=$sql_att_verb->row['ATTIVA_VERBALIZZAZIONE'];
				
				if($attiva_verbalizzazione){
					$redir_nc = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&RichiestaIntegrazioneOdG=yes&PROGR={$sql->row[PROGR]}";
					$richiesta_integrazione='
					<button class="btn btn-warning" onclick="if(confirm(\'Proseguire con l\\\'attivazione dell\\\'integrazione all\\\'OdG\'))location.href=\''.$redir_nc.'\'" type="button">
						<i class="fa bigger-110"></i>
						Richiedi integrazione a OdG
					</button>
					';
				}else $alert_invio="alert('Completare la convocazione o le integrazioni all\'OdG prima di attivare la verbalizzazione');return false;";
			}
			
			#GIULIO 29-11-12# Bottone per invio dati
			if (($visitnum == 0 && $visibilita==1) || ($service == 'GSE' && ($visitnum == 2 || $visitnum == 0))){
				$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
				$this->body.=$richiesta_integrazione;
				#GC 18/11/2015 NUOVA_GRAFICA
				//$this->body.='<input type="button" onclick="location.href=\''.$redir.'\'" value="'.$text.'" />';
				$this->body.='
				<button class="btn btn-info" type="button" onclick="'.$alert_invio.'location.href=\''.$redir.'\'">
					<i class="fa fa-lock bigger-110"></i>
					'.$text.'
				</button>';
				$this->body.='</td></tr></table>';
			}
			
		}
		//Emendamenti!!
		$em_state = $this->GetEmendamentoState($conn, $service, $in[$this->PK_SERVICE]); //L'emendamento e' approvabile
		//echo "PRO:$profilo|EME:$inEmendamento|SE:$service|PK:{$in[$this->PK_SERVICE]}|EMST:{$em_state}";
		if (strtoupper($service) == "CE" && $inEmendamento && ($profilo == "URC" || $profilo == "SGR") && ($em_state==0 || $em_state==1 || $em_state==3) && !$inEmeApprovazione){
			//echo "VAI!!";
			$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="50%"><tr><td class="sc4bis" style="text-align: center;">';
			//$redir = "https://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
			//$this->body .= $this->PK_SERVICE;
			$redir = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&InviaEmendamento=yes"; //Prima visita di default
			//print_r($this); //$pk = $_GET[''];

			#GIULIO 22/08/2013#Controllo che sia stato inserito almeno un documento per l'emendamento.
			#DA NON TOGLIERE  altrimenti non e' possibile inserire altri documenti quando l'emendamento e' stato inviato
			//Luigi: corretto problema del visitnum non valorizzato e del mancato controllo sulla presenza di documentazione emendamento
				$pkid=$this->session_vars['ID_STUD'];
				$vid_eme=20;
				$sql_query_eme_0="select max(visitnum_progr) mvpe from {$service}_coordinate where {$this->PK_SERVICE}=$pkid and visitnum=$vid_eme";
				$sql_eme_0=new query($conn);
				$sql_eme_0->get_row($sql_query_eme_0);
				$mvprogr_eme=$sql_eme_0->row['MVPE'];
				
				$sql_query_eme_1="select count(*) as conto_doc from {$service}_coordinate where {$this->PK_SERVICE}=$pkid and visitnum=$vid_eme and visitnum_progr=$mvprogr_eme and esam=10 and inizio=1";
				$sql_eme_1=new query($conn);
				$sql_eme_1->get_row($sql_query_eme_1);
				$doc_eme=$sql_eme_1->row['CONTO_DOC'];
			
			$this->body.='<font size="2px" color="red"><b>ATTENZIONE! E\' possibile emendare i dati dello studio. Una volta completato cliccare su</b></font><br/><input type="button" onclick="if('.$doc_eme.'>=1){location.href=\''.$redir.'\'} else{alert(\'ATTENZIONE\n E\\\' necessario inserire la Documentazione Emendamento\')}" value="Richiedi approvazione emendamento" />';
			$this->body.='</td></tr></table>';
		}
		//Luigi: aggiungo messaggi dell'invio emendamento ed eventuale bottone di chiusura integrazione dell'emendamento
		if (strtoupper($service) == "CE" && $inEmendamento && ($profilo == "URC" || $profilo == "SGR") && ($inEmeApprovazione || $em_state == 2)) {
			$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
			$this->body.='<font color=red><b>Emendamento inviato per approvazione alla segreteria CE</b></font>';
			$this->body.='</td></tr></table>';
			$pkid=$this->session_vars['ID_STUD'];
			$vid_eme=20;
			$sql_query_eme_0="select max(visitnum_progr) mvpe from {$service}_coordinate where {$this->PK_SERVICE}=$pkid and visitnum=$vid_eme";
			$sql_eme_0=new query($conn);
			$sql_eme_0->get_row($sql_query_eme_0);
			$mvprogr_eme=$sql_eme_0->row['MVPE'];
			$sql_query_eme_2="select count(*) as conto_sosp from {$service}_coordinate where {$this->PK_SERVICE}={$this->session_vars['ID_STUD']} and visitnum=20 and visitnum_progr=$mvprogr_eme and esam in (10,1) and nvl(fine,0)=0";
			$sql_eme_2=new query($conn);
			$sql_eme_2->get_row($sql_query_eme_2);
			$sosp_eme=$sql_eme_2->row['CONTO_SOSP'];
			
			if ($sosp_eme > 0) {
				$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
				$this->body.="<input type=\"button\" value=\"Chiudi l'integrazione dell'emendamento\" onclick=\"location.href='?CLOSE_EME_INT=yes&{$this->PK_SERVICE}={$this->session_vars['ID_STUD']}'\">";
				$this->body.='</td></tr></table>';
				}
			
		}
		/*
		$em_state = $this->GetEmendamentoState($conn, $service, $in[$this->PK_SERVICE]); //L'emendamento e' approvabile
		if (strtoupper($service) == "CE" && $inEmendamento && $profilo == "SGR" && $em_state==2){
			$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
			//$redir = "https://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
			//$this->body .= $this->PK_SERVICE;
			$redir = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&ApprovaEmendamento=yes"; //Prima visita di default
			//print_r($this); //$pk = $_GET[''];
			$this->body.='<input type="button" onclick="location.href=\''.$redir.'\'" value="Approva l\'emendamento corrente" />';
			$this->body.='</td></tr></table>';
		}
		*/
		
		////(!!) - Integrazioni e Rendi valutabile automatizzati con chiusura schede e dati dentro scheda valutazione segreteria
		//Bottone integrazioni -> solo per servizio principale (CE) e per uno stato e profilo particolare
		/*
		if (strtoupper($service) == "CE" && $stato == 3 && $profilo == "SGR"){
			$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
			//$redir = "https://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
			//$this->body .= $this->PK_SERVICE;
			$redir = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&Integrazione=yes"; //Prima visita di default
			//print_r($this); //$pk = $_GET[''];
			$this->body.='<input type="button" onclick="location.href=\''.$redir.'\'" value="Richiedi integrazione" />';
			$this->body.='</td></tr></table>';
		}
		*/
		//Bottone rendi valutabile -> solo per servizio principale (CE) e per uno stato e profilo particolare
		/*
		$check = true;
		if (!$this->IsVisitClosed($conn, $service, $in[$this->PK_SERVICE], "0")){$check = false;}
		if (!$this->IsVisitClosed($conn, $service, $in[$this->PK_SERVICE], "2")){$check = false;}
		if (strtoupper($service) == "CE" && $stato == 3 && $profilo == "SGR" && $check){
			$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
			//$redir = "https://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
			//$this->body .= $this->PK_SERVICE;
			$redir = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&Approva=yes"; //Prima visita di default
			//print_r($this); //$pk = $_GET[''];
			$this->body.='<input type="button" onclick="location.href=\''.$redir.'\'" value="Approva lo studio e rendilo valutabile" />';
			$this->body.='</td></tr></table>';
		}
		*/
		////(!!) - Fine bottoni Integrazioni e valutabile
		//Bottone conferma o rifiuta convocazione
		/*
		if (strtoupper($service) == "GSE" && $stato == 4 && $profilo == "CMP"){
			$status = $this->getCalendarStatus($in[$this->PK_SERVICE]);
			if ($status == CAL_RICHIESTO){			
				$this->body.='<table border="0" cellpadding="0" cellspacing="0" width="100%"><tr><td class="sc4bis" style="text-align: center;">';
				//$redir = "https://".$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
				//$this->body .= $this->PK_SERVICE;
				$redir_p = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&Presente=yes"; //Prima visita di default
				$redir_a = "index.php?{$this->PK_SERVICE}={$in[$this->PK_SERVICE]}&Assente=yes"; //Prima visita di default
				//print_r($this); //$pk = $_GET[''];
				$this->body.='<input type="button" onclick="location.href=\''.$redir_p.'\'" value="Conferma Presenza" />';
				$this->body.='<input type="button" onclick="location.href=\''.$redir_a.'\'" value="Conferma Assenza" />';
				$this->body.='</td></tr></table>';
			}
		}
		*/
		////// ----Dario - Fine bottoner invia
		
		if($config_service['Patients_list']!="") {
		$this->body.="<p align=left>";
		if($this->config_service['lang']=="en") {
			$go="Go to ";
		} else {
			$go="Vai alla ";
		}
		if($config_service['Patients_list']!="") {
			$link="index.php?list=patients_list.xml";
			if($in['CENTER']!='') $link.="&CENTER={$in['CENTER']}";
			#GC 19/11/2015 NUOVA_GRAFICA
			//if(!$parametro_passato)	$this->body.="$go
	  	//<a href=\"$link\">{$config_service['Patients_list']} &gt;&gt; </a>";
	  }
		$this->body.="</p>";
		}
		//Bottoni esportazione pdf e html
		//$this->body.= "<p align='right'><a target=\"new\" href=\"index.php?&make_cta_form=yes&ID_SPER={$in[$this->PK_SERVICE]}\">Visualizza la pratica in formato html<img height=\"20\" border=\"0\" src=\"images/htm_1.gif\"></p>";
		//$this->body.= "<p align='right'><a target=\"new\" href=\"index.php?pdf=make&make_cta_form=yes&ID_SPER={$in[$this->PK_SERVICE]}\">Visualizza la pratica in formato pdf<img height=\"20\" border=\"0\" src=\"images/pdf.gif\"></p>";
		//Fine
		return $this->body;
	}

	function IsVisitClosed($conn, $service, $pkid, $vid){
		$closed = 0;
		if ($pkid != 'next') {
			$sql_query="select min(nvl(visitclose,0)) vc from {$service}_coordinate where {$this->PK_SERVICE}={$pkid} and visitnum in ({$vid}) and inizio=1";
			if($_GET['DEBUG']==1) echo $sql_query;
			$sql=new query($conn);
			$sql->get_row($sql_query);
			$closed=$sql->row['VC'];
	
		}
		return ($closed==1);
		
	}
	function GetWFState($conn, $service, $pkid){
		$state = 0;
		if ($pkid != 'next') {
			$sql_query="select id_stato from {$service}wf_stato where pk_service={$pkid}";
			$sql=new query($conn);
			$sql->get_row($sql_query);
			$state=$sql->row['ID_STATO'];
			if (!$state){
				$state = 1;
			}
		}
		return $state;
	}
	
	function getProfilo($conn, $userid){
		$SQL = new query($conn);
		$SQL->get_row("SELECT * FROM ANA_UTENTI_2 WHERE USERID = '{$userid}'");
		return $SQL->row['PROFILO'];
	}
	
	
	function getCalendarArray(){
		global $service;
		$userid = $this->session_vars['remote_userid'];
		$h = array();
		$h['TAB'] = "{$service}_sel_componenti";
		$h['RICHIESTA'] = "CONVOCAZIONI";
		$h['CONFERMA'] = "CONVOCAZIONI_CONFERMATE";
		$h['RIFIUTO'] = "CONVOCAZIONI_RESPINTE";
		$h['USER'] = $userid;
		$h['VID'] = 0;
		return $h;		
	}
	
	function getCalendarStatus($id){
		define("CAL_NESSUNO","0");
		define("CAL_RICHIESTO","1");
		define("CAL_PRESENTE","2");
		define("CAL_ASSENTE","3");
		
		$highlight = $this->getCalendarArray();
		
		$retval = CAL_NESSUNO; //Non richiesta la mia presenza
		$sql_details = "
			select {$this->PK_SERVICE},{$highlight['RICHIESTA']},{$highlight['CONFERMA']},{$highlight['RIFIUTO']} from {$highlight['TAB']} where {$this->PK_SERVICE} = {$id} 
		";
		$query_details = new query($this->conn);
		$query_details->set_sql($sql_details);
		$query_details->exec();
		$query_details->get_row();
		$r = explode("|",$query_details->row[$highlight['RICHIESTA']]);
		if (in_array($highlight['USER'],$r)){
			$retval = CAL_RICHIESTO;
			$r = explode("|",$query_details->row[$highlight['CONFERMA']]);
			if (in_array($highlight['USER'],$r)){
				$retval = CAL_PRESENTE;
			}
			$r = explode("|",$query_details->row[$highlight['RIFIUTO']]);
			if (in_array($highlight['USER'],$r)){
				$retval = CAL_ASSENTE;
			}
		}				
		return $retval;
	}
	
	
	
	
	
	
	
	
	
	////// ----- Gestione Calendario (Parametrizzato sulla base di un campo data, e fornendo query di estrazione dati ////

	//Funzioni per calendario sedute
	function cal_weekly_sedute($highlight = false){
		global $conn;
		global $service;
		$h = false;
		$status = array('tab'=>"GSE_LISTA",'show'=>false);
		if ($highlight == 1){
			$h = $this->getCalendarArray();
		}
		return $this->weekly_visit_bar("DATA_SED_DT","D_TIPO_SED,DESCRIZIONE","{$service}_registrazione",$status,$h);
	}
	function cal_monthly_sedute($highlight = false /*, $showstatus = false */){
		global $conn;
		global $service;
		$h = false;
		$status = array('tab'=>"GSE_LISTA",'show'=>true);
		$status_unlink = false;
		$linkaction = false;
		$profilo = $this->getProfilo($conn,$this->session_vars['remote_userid']);
		//echo "$profilo";
		switch($profilo){
			case "CMP":
				$highlight = 1;
				#GC 03-12-2013# Mostro il link della seduta al componente anche se l'OdG non e' stato inviato per poter caricare le rel/oss
				//$status_unlink = "1";
				$linkaction="clista=studi";
				break;
		}
		if ($highlight == 1){
			$h = $this->getCalendarArray();
			$status['show'] = false;
		}
		$hidelabels = true;
		//ATTENZIONE: Concatenazione senza spazi!
		$orariofield = "'<span style=\"font-size:0.8em;\">'||TO_CHAR(NVL(ORA_INIZIO_H,0),'09')||' :'||TO_CHAR(NVL(ORA_INIZIO_M,0),'09')||' - '||TO_CHAR(NVL(ORA_FINE_H,0),'00')||' :'||TO_CHAR(NVL(ORA_FINE_M,0),'00')||'</span>' AS ORARIO_RIUNIONE";
		//$orariofield = "TO_CHAR(NVL(ORA_INIZIO_H,0),'00')||' :'||TO_CHAR(NVL(ORA_INIZIO_M,0),'00') AS ORA_RIUNIONE";
		return $this->monthly_visit_bar("DATA_SED_DT","D_TIPO_SED#DESCRIZIONE#[NL]#$orariofield","{$service}_registrazione",$status,$h,$hidelabels,$status_unlink,$linkaction);
	}
	//Fine funzioni helper calendario sedute
	
	//Calendario settimanale
	function weekly_visit_bar($dt_field, $details_fields, $details_table, $status, $highlight = false, $hidelabels = false, $status_unlink = false, $linkaction=false){
		
		global $service;
		
		/* Today */
		$today_dt = date ("d-m-Y");
		$today_day = date ("j");
		$today_text_day = date ("D");
		
		/* Calcolo lo scorso Lunedi', se oggi e' Lunedi' uso la today_dt */
		if($today_text_day != "Mon"){
			
			if(isset($_GET['WEEK_FILTER']) && $_GET['WEEK_FILTER'] == "PREV" || $_GET['WEEK_FILTER'] == "CURR" || $_GET['WEEK_FILTER'] == "NEXT"){

				if($_GET['WEEK_FILTER'] == "PREV"){
					$first_monday_time = strtotime('Last Monday-1 week');
					$prev_sel = "selected = \"selected\"";
					$curr_sel = "";
					$next_sel = "";
				}else if($_GET['WEEK_FILTER'] == "CURR"){
					$first_monday_time = strtotime('Last Monday');
					$prev_sel = "";
					$curr_sel = "selected = \"selected\"";
					$next_sel = "";
				}else if($_GET['WEEK_FILTER'] == "NEXT"){
					$first_monday_time = strtotime('Last Monday+1 week');
					$prev_sel = "";
					$curr_sel = "";
					$next_sel = "selected = \"selected\"";
				}
				//echo "POLLO";
			}else{
				$first_monday_time = strtotime('Last Monday');
				$prev_sel = "";
				$curr_sel = "selected = \"selected\"";
				$next_sel = "";
				//echo "POLLO2";
			}
			
		}else{
			
			if(isset($_GET['WEEK_FILTER']) && $_GET['WEEK_FILTER'] == "PREV" || $_GET['WEEK_FILTER'] == "CURR" || $_GET['WEEK_FILTER'] == "NEXT"){

				if($_GET['WEEK_FILTER'] == "PREV"){
					$first_monday_time = strtotime('Last Monday');
					$prev_sel = "selected = \"selected\"";
					$curr_sel = "";
					$next_sel = "";
				}else if($_GET['WEEK_FILTER'] == "CURR"){
					$first_monday_time = strtotime($today_dt);
					$prev_sel = "";
					$curr_sel = "selected = \"selected\"";
					$next_sel = "";
				}else if($_GET['WEEK_FILTER'] == "NEXT"){
					$first_monday_time = strtotime('Last Monday+2 week');
					$prev_sel = "";
					$curr_sel = "";
					$next_sel = "selected = \"selected\"";
				}
				
			}else{
				$first_monday_time = strtotime($today_dt);
				$prev_sel = "";
				$curr_sel = "selected = \"selected\"";
				$next_sel = "";
			}
		}
		
		/* Lunedi' */
		$monday_dt = date ("d/m/Y", $first_monday_time);
		$monday_day = $this->date_day($monday_dt); //date ("j", $first_monday_time);
		
		/* Martedi' */
		$tuesday_dt = $this->dayadd(1, $monday_dt);
		$tuesday_day = $this->date_day($tuesday_dt);
		//echo $tuesday_dt;
		
		/* Mercoledi' */
		$wednesday_dt = $this->dayadd(2, $monday_dt);
		$wednesday_day = $this->date_day($wednesday_dt);
		
		/* Giovedi' */
		$thursday_dt = $this->dayadd(3, $monday_dt);
		$thursday_day = $this->date_day($thursday_dt);
		
		/* Venerdi' */
		$friday_dt = $this->dayadd(4, $monday_dt);
		$friday_day = $this->date_day($friday_dt);
		
		/* Calcolo il mese del Lunedi' e del Venerdi' scelti per visualizzazione intervallo scelto */
		$monday_month = $this->date_month($monday_dt); //date("d M Y", $first_monday_time);
		$friday_month = $this->date_month($friday_dt); //date("d M Y", strtotime($friday_dt));
		
		$this->body="<p><a href=\"index.php\" >Home</a> &gt;&gt; Expected Weekly Visits Calendar</p>";
		
		/* Week filter */
		$this->body.="<form action=\"GET\">";
		$this->body.="<input type=\"hidden\" name=\"SHOW_CAL_WEEKLY\" value=\"1\">";
		$this->body.="<div style=\"text-align:center;font-weight:bold;\">Week Filter&nbsp;&raquo;&nbsp;";
		$this->body.="<select name=\"WEEK_FILTER\">";
		$this->body.="<option {$prev_sel} value=\"PREV\">Previous Week</option>";
		$this->body.="<option {$curr_sel} value=\"CURR\">Current Week</option>";
		$this->body.="<option {$next_sel} value=\"NEXT\">Next Week</option>";
		$this->body.="</select>&nbsp;<input type=\"submit\" value=\"Filter\"><br />";
		$this->body.="</div>";
		$this->body.="</form>";
		$this->body.="<br />";
		
		/* Margin e Padding = 4 solo per generazione PDF */
		if($this->session_vars['EXPORT'] == "pdf"){
			$weekly_table="<table width=95% cellpadding=4 cellspacing=4 align=center border=0>";
		}else{
			$weekly_table="<table width=95% cellpadding=2 cellspacing=2 align=center border=0>";
		}
		
		$weekly_table.="<tr>";
		$weekly_table.="<td width=\"19%\" colspan=5><b>".$monday_month." - ".$friday_month."</b></td>";
		$weekly_table.="</tr>";
		$weekly_table.="<tr>";
		$weekly_table.="<td width=\"19%\" align=center bgcolor=#d9d9d9><br /><b>Mon</b><br />&nbsp;";
		$weekly_table.="</td>";
		$weekly_table.="<td width=\"19%\" align=center bgcolor=#d9d9d9><br /><b>Tue</b><br />&nbsp;";
		$weekly_table.="</td>";
		$weekly_table.="<td width=\"19%\" align=center bgcolor=#d9d9d9><br /><b>Wed</b><br />&nbsp;";
		$weekly_table.="</td>";
		$weekly_table.="<td width=\"19%\" align=center bgcolor=#d9d9d9><br /><b>Thu</b><br />&nbsp;";
		$weekly_table.="</td>";
		$weekly_table.="<td width=\"19%\" align=center bgcolor=#d9d9d9><br /><b>Fri</b><br />&nbsp;";
		$weekly_table.="</td>";
		$weekly_table.="</tr>";
		
		$weekly_table.="<tr>";
		
		/* Estraggo i codpat che hanno almeno una visita nell'intervallo scelto */
		$adata = $this->filter_records($dt_field, $details_fields, $details_table,"$monday_dt","$friday_dt", $status, $highlight, $hidelabels, $status_unlink, $linkaction);
		//echo "<br/>".$monday_dt."--".$friday_dt."<br/>";
		
		if (count($adata[$monday_dt])>0 ){
			foreach ($adata[$monday_dt] as $det ){
				$monday_patient .=$det;
			}
		}
		if (count($adata[$tuesday_dt])>0 ){
			foreach ($adata[$tuesday_dt] as $det ){
				$tuesday_patient .=$det;
			}
		}
		if (count($adata[$wednesday_dt])>0 ){
			foreach ($adata[$wednesday_dt] as $det ){
				$wednesday_patient .=$det;
			}
		}
		if (count($adata[$thursday_dt])>0 ){
			foreach ($adata[$thursday_dt] as $det ){
				$thursday_patient .=$det;
			}
		}
		if (count($adata[$friday_dt])>0 ){
			foreach ($adata[$friday_dt] as $det ){
				$friday_patient .=$det;
			}
		}

		// print($num_tot_pat." - ".$num_in_pat." - ".$num_out_pat);
		
		/* Controllo che oggi sia Lunedi', se si' evidenzio il numero del giorno */
		if($today_day == $monday_day){
			$monday_day = "<font color=#ff0000><u>".$monday_day."</u></font>";
		}
		$weekly_table.="<td valign=top bgcolor=#E4F1E2><b><span>".$monday_day."</b></span><br />";
		$weekly_table.=$monday_patient;
		$weekly_table.="</td>";
		
		/* Controllo che oggi sia Martedi', se si' evidenzio il numero del giorno */
		if($today_day == $tuesday_day){
			$tuesday_day = "<font color=#ff0000><u>".$tuesday_day."</u></font>";
		}
		$weekly_table.="<td valign=top bgcolor=#E4F1E2><span><b>".$tuesday_day."</b></span><br />";
		$weekly_table.=$tuesday_patient;
		$weekly_table.="</td>";
		
		/* Controllo che oggi sia Mercoledi', se si' evidenzio il numero del giorno */
		if($today_day == $wednesday_day){
			$wednesday_day = "<font color=#ff0000><u>".$wednesday_day."</u></font>";
		}
		$weekly_table.="<td valign=top bgcolor=#E4F1E2><span><b>".$wednesday_day."</b></span><br />";
		$weekly_table.=$wednesday_patient;
		$weekly_table.="</td>";
		
		/* Controllo che oggi sia Giovedi', se si' evidenzio il numero del giorno */
		if($today_day == $thursday_day){
			$thursday_day = "<font color=#ff0000><u>".$thursday_day."</u></font>";
		}
		$weekly_table.="<td valign=top bgcolor=#E4F1E2><span><b>".$thursday_day."</b></span><br />";
		$weekly_table.=$thursday_patient;
		$weekly_table.="</td>";
		
		/* Controllo che oggi sia Venerdi', se si' evidenzio il numero del giorno */
		if($today_day == $friday_day){
			$friday_day = "<font color=#ff0000><u>".$friday_day."</u></font>";
		}
		$weekly_table.="<td valign=top bgcolor=#E4F1E2><span><b>".$friday_day."</b></span><br />";
		$weekly_table.=$friday_patient;
		$weekly_table.="</td>";
		
		$weekly_table.="</tr>";
		
		$weekly_table.="</table>";
		
		$this->body.=$weekly_table;
		
		/* Link generazione PDF */
		$exp_params="";
		foreach($_GET as $k_get => $v_get){
			if($k_get == "WEEK_FILTER"){
				$exp_params.="&{$k_get}={$v_get}";
			}
		}
		$this->body.='<table border="0" width="95%" align=center>';
		$this->body.='<tr>';
		$this->body.='<td style="text-align:right;">';
		//$this->body.='<a target="_BLANK" href="?SHOW_CAL_WEEKLY=1&EXPORT=pdf'.$exp_params.'">Export to PDF <img style="border: 0px;" src="images/pdf_light.gif" alt="Export to PDF" title="Export to PDF"></a>';
		$this->body.='</td>';
		$this->body.='<tr>';
		$this->body.='</table>';
		
		/* Export PDF */
		if($this->session_vars['EXPORT'] == "pdf"){
			
			$export_dt = date('d_m_Y');
			
			$exp_weekly_pdf = file_get_contents("html_template/weekly_calendar/weekly_calendar_general.html");
			$exp_weekly_pdf = preg_replace("/<!-- body -->/i", $weekly_table, $exp_weekly_pdf);

			$fp = fopen ( "html_template/weekly_calendar/WEEKLY_CALENDAR_".$export_dt.".html", "w" );
			fwrite ( $fp, $exp_weekly_pdf );
			fclose ( $fp );

			$exp_rand_pdf = file_get_contents("html_template/weekly_calendar/WEEKLY_CALENDAR_".$export_dt.".html");
			//print($exp_rand_pdf."<hr />");die();
			system ( "htmldoc -t pdf14  --no-title --footer . --size A4 --charset iso-8859-15 --browserwidth 1024 --landscape long --headfootsize 8 --headfootfont Times-Italic --bottom 5mm --top 5mm --left 5mm --right 5mm --path /amministrazione/schede_utente --webpage --no-numbered /http/www/earnest/html/uxmr/html_template/weekly_calendar/WEEKLY_CALENDAR_".$export_dt.".html > /http/www/earnest/html/uxmr/html_template/weekly_calendar/pdf/WEEKLY_CALENDAR_".$export_dt.".pdf" );
			
			if(preg_match("/earnest.cineca.org/i", $_SERVER['SERVER_NAME'])){
				header('Location: https://earnest.cineca.org/uxmr/html_template/weekly_calendar/pdf/WEEKLY_CALENDAR_'.$export_dt.'.pdf');
			}else{
				header('Location: https://earnest.sissdev.cineca.it/uxmr/html_template/weekly_calendar/pdf/WEEKLY_CALENDAR_'.$export_dt.'.pdf');
			}
			
			die();
			
		}
		
		$this->body .= "
		<div style=\"text-align:center;font-size:1.2em;font-weight:bold;color:#ff0000;\">
		<p align=\"center\"><a href=\"index.php\"><span style=\"font-size:14px;\">Go To Homepage</b></span></a></p>
		<p align=\"center\"><a href=\"index.php?list=patients_list.xml\"><span style=\"font-size:14px;\">Go To Patient's list</span></a></p>
		</div>";
		
		return $this->body;
		
	}

	//Calendario mensile
	function monthly_visit_bar($dt_field, $details_fields, $details_table, $status, $highlight = false, $hidelabels = false, $status_unlink = false, $linkaction = false){
	    
		global $service;
		
		$current_day = date('j');
		$current_month = date('n');
		$current_month_txt = date('F');
		$current_year = date('Y');
		$current_date = mktime(12, 0, 0, $current_month, 1, $current_year);
	    $current_daysInMonth = date("t", $current_date);
	    $current_offset = date("w", $current_date);
	    $current_today_date = date("Y-m-d");
	    $current_date_format = date("d/m/Y");
	    
	    /* Calcolo la data del mese precedente a partire dalla data attuale */
	    $prev_month_date = strtotime(date("Y-m-d", strtotime($current_today_date)) . " -1 month");
	    
	    /* Calcolo la data del mese successivo a partire dalla data attuale */
	    $next_month_date = strtotime(date("Y-m-d", strtotime($current_today_date)) . " +1 month");
	    
		/* Gestione filtro sul mese */

		$month = $current_month;
		$year = $current_year;
		if (isset($_GET['MONTH'])){
			$month = $_GET['MONTH']+0;
		}
		if (isset($_GET['YEAR'])){
			$year = $_GET['YEAR']+0;
		}
		
		
		//$requested_date_format = date("d/m/Y", strtotime($current_today_date));
		$requested_date_format = date("d/m/Y", strtotime("10/$month/$year"));
		
		//print("Current Date -> ".$current_date_format."<br />");
		//print("Requested Date -> ".$requested_date_format."<br />");
	    
		//print("Month: $month, Year: $year<br/>");
		/* Calcolo variabili per il mese richiesto considerando il filtro */
		// $month = 4; $year = 2011; // Test data
		
		/* Data richiesta */
	    $date = mktime(12, 0, 0, $month, 1, $year);
	    //echo "$date";
	    /* Nome mese richiesto */
	    $month_txt = date("F", $date);
	    /* Numero giorni mese richiesto */
	    $daysInMonth = date("t", $date);
	    /* Numero giorno (Domenica = 0, Sabato = 6) */
	    $offset = date("w", $date);
	    $offset = ($offset == 0?7:$offset);
	    //echo $offset;
	    /* Numero prima settimana del mese */
	    $offset_w = date("W", $date);
	    /* Dati relativi alle celle del mese precedente */
	    $prev_prev_month_date = strtotime(date("Y-m-d", $date) . " -1 month");
	    $next_next_month_date = strtotime(date("Y-m-d", $date) . " +1 month");
	    
	    //Begin output
	    //$this->body="<p><a href=\"index.php\" >Home</a> &gt;&gt; Calendario Mensile</p>";
	    //$this->body="<p><a href=\"index.php\" >Home</a></p>";
	    
	    /* Month filter */
	    /*
		$this->body.="<form action=\"GET\">";
		$this->body.="<input type=\"hidden\" name=\"SHOW_CAL_MONTHLY\" value=\"1\">";
		$this->body.="<div style=\"text-align:center;font-weight:bold;\">Month Filter&nbsp;&raquo;&nbsp;";
		$this->body.="<select name=\"MONTH_FILTER\">";
		$this->body.="<option {$prev_sel} value=\"PREV\">Previous Month</option>";
		$this->body.="<option {$curr_sel} value=\"CURR\">Current Month</option>";
		$this->body.="<option {$next_sel} value=\"NEXT\">Next Month</option>";
		$this->body.="</select>&nbsp;<input type=\"submit\" value=\"Filter\"><br />";
		if ($highlight){
			$this->body.="<input type=\"hidden\" name=\"HIGHLIGHT\" value=\"{$_GET['HIGHLIGHT']}\" />";
		}
		$this->body.="</div>";
		$this->body.="</form>";
		*/
	    $filter = "";
	    $filter.="<div style=\"text-align: center\">
									<ul class=\"pagination\">";
	    $p_month = $month-1;
	    $p_year = $year;
	    if ($p_month<1){
	    	$p_month = 12;
	    	$p_year = $p_year-1;
	    }
	  #GC NUOVA_GRAFICA
		//$filter.="<input type=\"button\" value=\"&lt;&lt;\" onclick=\"location.href='?SHOW_CAL_MONTHLY=1&YEAR=".($year-1)."&MONTH=$month'\" />";
	  $filter.="<li><a href=\"index.php?SHOW_CAL_MONTHLY=1&YEAR=".($year-1)."&MONTH=$month\"><i class=\"icon-double-angle-left\"></i></a></li>";
	 
	  $filter.="&nbsp;";
	  //$filter.="<input type=\"button\" value=\"&lt;\" onclick=\"location.href='?SHOW_CAL_MONTHLY=1&YEAR=$p_year&MONTH=$p_month'\" />";
		$filter.="<li><a href=\"index.php?SHOW_CAL_MONTHLY=1&YEAR=$p_year&MONTH=$p_month\"><i class=\"icon-angle-left\"></i></a></li>";
		
		//$filter.="&nbsp;<b>".$this->t($month_txt)."&nbsp;".$year."</b>&nbsp;";
		$filter.="<li><a><b>".$this->t($month_txt)."&nbsp;".$year."</b></a></li>";
		
	    $n_month = $month+1;
	    $n_year = $year;
	    if ($n_month>12){
	    	$n_month = 1;
	    	$n_year = $n_year+1;
	    }
	    //$filter.="<input type=\"button\" value=\"&gt;\" onclick=\"location.href='?SHOW_CAL_MONTHLY=1&YEAR=$n_year&MONTH=$n_month'\" />";
	    $filter.="<li><a href=\"index.php?SHOW_CAL_MONTHLY=1&YEAR=$n_year&MONTH=$n_month\"><i class=\"icon-angle-right\"></i></a></li>";
	    
	    $filter.="&nbsp;";
	    //$filter.="<input type=\"button\" value=\"&gt;&gt;\" onclick=\"location.href='?SHOW_CAL_MONTHLY=1&YEAR=".($year+1)."&MONTH=$month'\" />";
	    $filter.="<li><a href=\"index.php?SHOW_CAL_MONTHLY=1&YEAR=".($year+1)."&MONTH=$month\"><i class=\"icon-double-angle-right\"></i></a></li>";
	    $filter.="</ul></div>";
		
		//$this->body.="<br />";
	    
	    $monthly_table="<table width=95% cellpadding=2 cellspacing=2 align=center border=0 >";
	    
	    $monthly_table.="<tr>";
		//$monthly_table.="<td width=\"19%\" colspan=5><b>".$month_txt."&nbsp;".$year."</b></td>";
		$monthly_table.="<td colspan=7 style=\"line-height:40px;\">$filter</td>";
		$monthly_table.="</tr>";
		
		$monthly_table.="<tr>";
		// $monthly_table.="<td align=center bgcolor=#d9d9d9><br /><b>Week</b><br />&nbsp;</td>";
		$monthly_table.="<td width=\"14%\" align=center style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#2283c5;\"><br /><b>".$this->t('Mon')."</b><br />&nbsp;</td>";
		$monthly_table.="<td width=\"14%\" align=center style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#2283c5;\"><br /><b>".$this->t('Tue')."</b><br />&nbsp;</td>";
		$monthly_table.="<td width=\"14%\" align=center style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#2283c5;\"><br /><b>".$this->t('Wed')."</b><br />&nbsp;</td>";
		$monthly_table.="<td width=\"14%\" align=center style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#2283c5;\"><br /><b>".$this->t('Thu')."</b><br />&nbsp;</td>";
		$monthly_table.="<td width=\"14%\" align=center style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#2283c5;\"><br /><b>".$this->t('Fri')."</b><br />&nbsp;</td>";
		$monthly_table.="<td width=\"14%\" align=center style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#2283c5;\"><br /><b>".$this->t('Sat')."</b><br />&nbsp;</td>";
		$monthly_table.="<td width=\"14%\" align=center style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#2283c5;\"><br /><b>".$this->t('Sun')."</b><br />&nbsp;</td>";
		$monthly_table.="</tr>";
		
		/* Estraggo i codpat che hanno almeno una visita nell'intervallo scelto */
		$adata = $this->filter_records($dt_field, $details_fields, $details_table,"01/$month/$year","$daysInMonth/$month/$year",$status,$highlight,$hidelabels,$status_unlink, $linkaction);
		//print_r($adata);
		//die($monthly_table);
		/* Calcolo la data dei giorni del mese precedente */
		$prev_monthNumDays = date("t", $prev_prev_month_date);
		
		$prev_cell_day = $prev_monthNumDays - $offset + 1;
		
		$prev_cell_month = date("F", $prev_prev_month_date);
		
		if($month_txt == "January"){
			$prev_cell_year = $year -1;
		}else{
			$prev_cell_year = $year;
		}
		
		$monthly_table.="<tr>";
		
	    /* Numero righe (settimane) */
	    $rows = 1;
	    $vcount = array();
	    $startv = array();
	    $firstpage = true;
	    $writtenlines = 0;
      	$imonth = $month;
    	if(strlen($imonth) < 2){
      		$imonth = "0".($imonth);
      	}
	    //$monthly_table.="\n#SONO QUI#$num_tot_pat\n"."\n";
	    $dcount = 0;
	    $day = 1;
	    $startwday = $day;
	    //$monthly_table.="\n||";
	    for ($i = 0; $i<7-$offset+1; $i++){
	    	$iday = $day+$i;
        	if(strlen($iday) < 2){
	      		$iday = "0".($iday);
	      	}
	        $loop_day_dt = mktime(12, 0, 0, $month, ($day+$i), $year);
	        $loop_day_name = date("l", $loop_day_dt);
	        //$monthly_table.= $loop_day_name;
	        ////if($loop_day_name == "Saturday" || $loop_day_name == "Sunday"){
	        ////	break;
	        ////}
	    	//$monthly_table.= ($month."/".$iday."/".$year);
        	$vcount[$i] = count($adata[$iday."/".$imonth."/".$year]);
        	$startv[$i] = 0;
           	//$monthly_table.=$vcount[$i]."-";
        }
        //$monthly_table.="||";
        $day = 1;
        $dcount = 0;
	    $contagiri = 0;
        while(($day <= $daysInMonth || $continua) /* && $contagiri < 100000 */ ){
			
	        $loop_day_dt = mktime(12, 0, 0, $month, $day, $year);
	        $loop_day_name = date("l", $loop_day_dt);
	        //$monthly_table.="#$loop_day_name#";
			if( ($loop_day_name == "Monday" && $day != 1) || $day > $daysInMonth){
	            $monthly_table.="</tr><tr>";
				
				//LUIGI: elimino l'interruzione di pagina
	            /* Interruzione di pagina */
	            /* $forcenumbers = false;
	            if ($rows == 3 || ($rows-3) % 4 == 0){
	        		
	        		// Stampo nuovamente l'intestazione della tabella SOLO nel file PDF
	        		if($this->session_vars['EXPORT'] == "pdf"){
	        			
	        			$monthly_table.="<td><p style=\"page-break-before:always\"></p></td></tr>";
	        			
	        			$monthly_table.="<tr>";
						// $monthly_table.="<td align=center bgcolor=#d9d9d9><br /><b>Week</b><br />&nbsp;</td>";
						$monthly_table.="<td width=\"14%\" align=center bgcolor=#d9d9d9><br /><b>".$this->t('Mon')."</b><br />&nbsp;</td>";
						$monthly_table.="<td width=\"14%\" align=center bgcolor=#d9d9d9><br /><b>".$this->t('Tue')."</b><br />&nbsp;</td>";
						$monthly_table.="<td width=\"14%\" align=center bgcolor=#d9d9d9><br /><b>".$this->t('Wed')."</b><br />&nbsp;</td>";
						$monthly_table.="<td width=\"14%\" align=center bgcolor=#d9d9d9><br /><b>".$this->t('Thu')."</b><br />&nbsp;</td>";
						$monthly_table.="<td width=\"14%\" align=center bgcolor=#d9d9d9><br /><b>".$this->t('Fri')."</b><br />&nbsp;</td>";
						$monthly_table.="<td width=\"14%\" align=center bgcolor=#d9d9d9><br /><b>".$this->t('Sat')."</b><br />&nbsp;</td>";
						$monthly_table.="<td width=\"14%\" align=center bgcolor=#d9d9d9><br /><b>".$this->t('Sun')."</b><br />&nbsp;</td>";
						$monthly_table.="</tr><tr>";
						
						$forcenumbers = true;
	        		}
	            } */
	            $rows++;

	            //continua --  wcontinua
	        	$wcontinua = false;
	            $icount = count($startv);
	            //$monthly_table.= "V:".$icount;
	            for($i=0; $i<$icount; $i++){
	            	//$monthly_table.= "S:".$startv[$i]."-E:".$vcount[$i];
	            	if ($startv[$i]<$vcount[$i]){
	            		$wcontinua = true;
	            		break;
	            	}
	            }
	            
	            //$monthly_table.="#-".($continua?"TRUE":"FALSE")."-#";
	            if ($continua){
	            	$day = $startwday;
	            }else{
		            //Finisce la settimana, incremento rows e popolo array visite vcount
            	    $startwday = $day;    	
	         	    $vcount = array();
		            //$monthly_table.="\n||";       
				    for ($i = 0; $i<7; $i++){
				    	$iday = $day+$i;
			        	if(strlen($iday) < 2){
				      		$iday = "0".($iday);
				      	}
				        $loop_day_dt = mktime(12, 0, 0, $month, ($day+$i), $year);
				        $loop_day_name = date("l", $loop_day_dt);
			        	$vcount[$i] = count($adata[$iday."/".$imonth."/".$year]);
	                	$startv[$i] = 0;        	
			           	//$monthly_table.=$vcount[$i]."-";
			        }
	            	//$monthly_table.="||";
	            }
	           	//$monthly_table.= "D:".$day;
	            $dcount = 0;
	            
        		if($forcenumbers){
	            	$wcontinua = false;
        		}
	            
	        }
	        
	        $loop_day_dt = mktime(12, 0, 0, $month, $day, $year);
	        $loop_day_name = date("l", $loop_day_dt);
	        $loop_day_en_suffix = date("S", $loop_day_dt);
	        $loop_day_offset = date("w", $loop_day_dt);
	        
	        /* Giorni feriali */
	        //if($loop_day_name != "Saturday" && $loop_day_name != "Sunday"){
	        if (true){
	        	
	        	//Gestione speciale primo giorno
	        	if ($day == 1){
	        		$monthly_table.= $this->week_offset_days($offset,$prev_cell_day,$prev_cell_month,$prev_cell_year, $continua);
	        	}
	        	
	        	if(strlen($day) < 2){
	        		$day = "0".$day;
	        	}
	        	
	        	if ($loop_day_name != "Saturday" && $loop_day_name != "Sunday"){
	        		$monthly_table.="<td valign=top style=\"background-color: #E4F1E2; border-style: solid; border-color: #CED7DB; border-width: 1px; color:#585858;\">";
	        	}else{
	        		$monthly_table.="<td valign=top style=\"background-color: #F2E3E3; border-style: solid; border-color: #CED7DB; border-width: 1px; color:#585858;\">";
	        	}
	        	
	        	if (!$wcontinua){
		        	/* Suffisso inglese (st, nd, rd, th) */
		        	$en_suffix = "&nbsp;<font size=2><sup>".$this->t($loop_day_en_suffix)."</sup></font>";
	        	
		        	/* Evidenzio il giorno attuale solo se siamo nel mese corrente */
					/*LUIGI aggiungo anno corrente...*/
		        	if($day == $current_day && $month == $current_month && $year == $current_year){
		        		$day_color = "color=#ff0000";
		        	}else{
		        		$day_color = "color=#585858";
		        	}
		        	
		        	$monthly_table.="<font {$day_color}><b>{$day}</b></font>&nbsp;<font size=2 {$day_color}><sup>".$this->t($month_txt)." ".$year."</sup></font>";
	        	}
	        	
	        	/* Se il mese e' composto da meno di due cifre concateno lo 0
				 * Es se mese = 2 mese diventa 02
				 */
        		if(strlen($month) < 2){
        			$month = "0".$month;
        		}
        		
        		$icount = count($adata[$day."/".$month."/".$year]);
        		//$monthly_table.= "IS:".$startv[$dcount]."-IE:".$icount; 
        		if ($startv[$dcount] < $icount){
	       			$v_details = $adata[$day."/".$month."/".$year][$startv[$dcount]];
        			$monthly_table.=$v_details;
        			//$monthly_table.=$v_details;
        		}
	       		$startv[$dcount] = $startv[$dcount]+1;

	        	//$monthly_table.="<br />&nbsp;"; //TODO: Eventualmente sostituire con un margin nel div
	        	
	        	/* Gestione giorni mese successivo
	        	 * Controlla l'offset dell'ultimo giorno del mese richiesto
				 * Crea tanti td quanti sono i giorni (del mese successivo) che mancano a completare l'ultima settimana
	        	 */
	        	if($day == $daysInMonth){
		        	
	        		$next_day = 1;
	        		
		        	$next_cell_month = date("F", $next_next_month_date);
			        
		        	if($month_txt == "December"){
						$next_cell_year = $year +1;
					}else{
						$next_cell_year = $year;
					}
	        		
		        	$monthly_table.="</td>";
		        	if ($day_next != 0){
			        	for($day_next = $loop_day_offset; $day_next < 7; $day_next++){
			        		
			        		$next_cell_day = "0".$next_day;
			        		
			        		$monthly_table.="<td valign=top bgcolor=#f0f0f0>";
			        		if (!$wcontinua){
			        			$monthly_table.="<b>{$next_cell_day}</b>&nbsp;<font size=2><sup>".$this->t($next_cell_month)." ".$next_cell_year."</sup></font>";
			        		}
			        		$monthly_table.="<br /></td>";
			        		
			        		$next_day++;
		        	}
		        	}
		        }else{
					$monthly_table.="</td>";		        	
		        }
	        	
	        }
	        /* Domeniche / Numero settimana */
	        ////else if($loop_day_name == "Sunday"){
	        ////}
	        /* Sabati */
	        ////else{
	        	
	        ////}
	        
        	$continua = false;
            $icount = count($startv);
            //$monthly_table.= "V:".$icount;
            for($i=0; $i<$icount; $i++){
            	//$monthly_table.= "S:".$startv[$i]."-E:".$vcount[$i];
            	if ($startv[$i]<$vcount[$i]){
            		$continua = true;
            		break;
            	}
            }
        
	        $day++;
	        $dcount++;
	        $contagiri++;
	    }
	  	$monthly_table.="</tr>";  
		$monthly_table.="</table>";
	    
		////Output tabella
		//$this->body.=$monthly_table;
		
		//Generazione output su 2 colonne
		$body = '<div style="display:block; float:left; width:85%;">'.$monthly_table.'</div>';
		$body .= '<div style="display:block; float:right; width:15%; padding-top:47px;">';
		if ($this->getProfilo($this->conn,$this->session_vars['remote_userid'])=="SGR"){
			$body .= '<table border="0" cellpadding="2" cellspacing="2" style="" align="center" width="100%">';
			$body .= '<tr style="background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#585858;"><td><a href="index.php?VISITNUM=0&ESAM=0" >&nbsp;<img src="images/add.png"></img> Inserisci nuova riunione</a></td></tr>';
			$body .= '</table><br>';
		}
		$nextriunioni = $this->nextRiunioni($dt_field,$linkaction);
		$body .= '<table border="0" cellpadding="2" cellspacing="2" style="" align="center" width="100%"><tr style="background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#585858;"><td><br/><b>&nbsp;Prossime riunioni</b><br/>&nbsp;</td></tr>';
		$body .= $nextriunioni;
		$body .= '</table>';
		$body .= '</div>';
		$this->body.=$body;
		
		
		/* Link generazione PDF */
		$exp_params="";
		foreach($_GET as $k_get => $v_get){
			if($k_get == "MONTH_FILTER"){
				$exp_params.="&{$k_get}={$v_get}";
			}
		}
		$this->body.='<table border="0" width="95%" align=center>';
		$this->body.='<tr>';
		$this->body.='<td style="text-align:right;">';
		//$this->body.='<a target="_BLANK" href="?SHOW_CAL_MONTHLY=1&EXPORT=pdf'.$exp_params.'">Export to PDF <img style="border: 0px;" src="images/pdf_light.gif" alt="Export to PDF" title="Export to PDF"></a>';
		$this->body.='</td>';
		$this->body.='<tr>';
		$this->body.='</table>';
		
		/* Export PDF */
		if($this->session_vars['EXPORT'] == "pdf"){
			
			$export_dt = date('d_m_Y');
			
			$exp_monthly_pdf = file_get_contents("html_template/monthly_calendar/monthly_calendar_general.html");
			
			$exp_monthly_pdf = preg_replace("/<!-- body -->/i", $monthly_table, $exp_monthly_pdf);

			$fp = fopen ( "html_template/monthly_calendar/MONTHLY_CALENDAR_".$export_dt.".html", "w" );
			fwrite ( $fp, $exp_monthly_pdf );
			fclose ( $fp );

			$exp_rand_pdf = file_get_contents("html_template/weekly_calendar/MONTHLY_CALENDAR_".$export_dt.".html");
			//print($exp_rand_pdf."<hr />");die();
			system ( "htmldoc -t pdf14  --no-title --size A4 --charset iso-8859-15 --browserwidth 1024 --landscape long --headfootsize 8 --headfootfont Times-Italic --bottom 5mm --top 10mm --left 5mm --right 5mm --path /amministrazione/schede_utente --webpage --no-numbered /http/www/ce_veneto/html/sedute/html_template/monthly_calendar/MONTHLY_CALENDAR_".$export_dt.".html > /http/www/ce_veneto/html/sedute/html_template/monthly_calendar/pdf/MONTHLY_CALENDAR_".$export_dt.".pdf" );
			
			header('Location: /sedute/html_template/monthly_calendar/pdf/MONTHLY_CALENDAR_'.$export_dt.'.pdf');
			
			die();
			
		}
		
		/*
		$this->body .= "
		<div style=\"text-align:center;font-size:1.2em;font-weight:bold;color:#ff0000;\">
		<p align=\"center\"><a href=\"index.php\"><span style=\"font-size:14px;\">Go To Homepage</b></span></a></p>
		<p align=\"center\"><a href=\"index.php?list=patients_list.xml\"><span style=\"font-size:14px;\">Go To Patient's list</span></a></p>
		</div>";
		*/
		
		return $this->body;
		
	}

	function week_offset_days($offset,$prev_cell_day,$prev_cell_month,$prev_cell_year, $continua){
		$retval = "";
		$pcday = $prev_cell_day;
		for($i = 1; $i <= $offset; $i++){
			
			/* Colonna Week Number */
			if($i==1){
				// $bg_color = "bgcolor=#a1cf9c";
				// $monthly_table.="<td align=center {$bg_color}><b>{$offset_w}</b></td>";	
			}
			/* Giorni del mese precedente */
			else{
				
				$pcday++;
				
				$bg_color = "style=\"background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#585858;\"";
				$retval .= "<td valign=top {$bg_color}>";
				if (!$continua){
					$retval .= "<b>{$pcday}</b>&nbsp;<font size=2><sup>".$this->t($prev_cell_month)." ".$prev_cell_year."</sup></font>";
				}
				$retval .= "<br /></td>";
			}
	    }
		return $retval;
	}
	
	function filter_records($dt_field, $details_fields, $details_table, $from, $to, $status, $highlight, $hidelabels, $status_unlink, $linkaction){
		global $service;
		global $conn;
		//print_r($status);
		//die();
		/* Estraggo i codpat che hanno almeno una visita nell'intervallo scelto */
		$sql_monthly_ids = "
		select {$this->PK_SERVICE},{$dt_field} from {$service}_registrazione 
		where center in (select center from {$service}_utenti_centri where userid ='{$this->session_vars['remote_userid']}')
		and {$dt_field} between to_date('{$from}', 'DD/MM/YYYY') and to_date('{$to}', 'DD/MM/YYYY')
		order by {$this->PK_SERVICE} asc
		";
		//$monthly_table.=$sql_monthly_pat."<br/>";
		
		$query_monthly_ids = new query($this->conn);
		$query_monthly_ids->set_sql($sql_monthly_ids);
		$query_monthly_ids->exec();
		
		$num_tot_pat = 0;
		$num_in_pat = 0;
		$num_out_pat = 0;
		
		$data = array();
		
		$stu = array();
		if ($status_unlink){
			$stu = explode(",",$status_unlink);
		}
		
		while($query_monthly_ids->get_row()){
			$id = $query_monthly_ids->row[$this->PK_SERVICE];
			/* Dettagli paziente */
			$hl = ""; //Non richiesta la mia presenza
			$bgcolor = "#F0F0F0";
			//Query status
			$idst = 0;
			$tabstatus = $status['tab'];
			$showstatus = $status['show'];
			$st = "&nbsp;";
			
			$sql_details = "
				select * from $tabstatus where {$this->PK_SERVICE} = {$id} 
			";
			$query_details = new query($this->conn);
			$query_details->set_sql($sql_details);
			$query_details->exec();
			$query_details->get_row();
			$idst = $query_details->row['STATO'];
			if ($showstatus){
				#GC 02/05/2016 TOSCANA-39#Lo stato "Convocata" non e' piu' quello del WF ma l'invio dell'OdG ai componenti
				$query_status_sed="select userid_invio_odg,invio_odg_dt from gse_cronologia_odg where {$this->PK_SERVICE} = {$id} and progr=(select max(progr) from gse_cronologia_odg where {$this->PK_SERVICE} = {$id})";
				$sql_status_sed = new query($this->conn);
				$sql_status_sed->get_row($query_status_sed);
				if($sql_status_sed->row['USERID_INVIO_ODG'] && $sql_status_sed->row['INVIO_ODG_DT'])
					$st = '<i> Convocata </i>';
				else
					$st = '<i>'.$query_details->row['STATO_DEC'].'</i>';
			}
			//echo $st;
			//Logica di highlighting x richiesta presenza
			if ($highlight && $idst>=4){ //Almeno riunione chiusa e convocata
				$cstatus = $this->getCalendarStatus($id);
				switch ($cstatus){
					case CAL_NESSUNO:
						break;
					case CAL_RICHIESTO:
						$hl = "ATTESA CONFERMA";
						$bgcolor = "#E0E0FF";
						break;
					case CAL_PRESENTE:
						$hl = "CONFERMATO";
						$bgcolor = "#E0FFE0";
						break;
					case CAL_ASSENTE:
						$hl = "DECLINATO";
						$bgcolor = "#FFE0E0";
						break;
				}				
			}
			
			$tolink = true;
			if (count($stu)>0){
				if (in_array($idst,$stu)){
					$tolink = false;
				}
			}
						
			$q_fields = str_replace("#",",",$details_fields);
			$q_fields = str_replace("[NL]","",$q_fields);
			$q_fields = str_replace(",,",",",$q_fields);
			$sql_details = "
				select {$this->PK_SERVICE},{$q_fields} from  $details_table where {$this->PK_SERVICE} = {$id} 
			";
			$query_details = new query($this->conn);
			$query_details->set_sql($sql_details);
			$query_details->exec();
			$query_details->get_row();
			$fields = explode("#",$details_fields);
			
			if (true){ //includo tutti
				/* Pazienti inclusi */
				$num_in_pat++;
				
			$show_seduta=true;
			$profilo = $this->getProfilo($conn,$this->session_vars['remote_userid']);
			#Mostro la seduta al componente se e' stato inviato l'OdG
			//if($idst < 4 && $profilo =='CMP') $show_seduta=false;
			
				if($show_seduta){
				$details = "<br /><div style=\"background-color:$bgcolor; padding-top:15px; padding-bottom:5px; padding-left:5px; padding-right:5px; margin-left:5px; margin-right:5px; margin-bottom:10px; \">";
				$i = 0;
				//print_r($query_details->row);
				foreach ($fields as $field){
					if ($field == "[NL]"){
						$details .= "";
					}else{
						//$details .="-$field-<br/>";
						if (stristr($field," AS ")){
							$field = explode(" AS ",$field);
							$field = $field[1];
							$field = trim($field);
						}
						$val = $query_details->row[$field];
						//if (!$val){
						//	$val = $query_details->row[$i];
						//}
						if ($i==0){
							$details .= "&bull;&nbsp;&nbsp;";
						}else{
							$details .= "&nbsp;&nbsp;&nbsp;";
						}
						if ($i==0 && $tolink){
							if (!$linkaction){
								$linkaction = "exams=visite_exam.xml";
							}
							//$details .='<a href="index.php?&exams=visite_exam.xml&'.$this->PK_SERVICE.'='.$query_details->row[$this->PK_SERVICE].'">';
							$details .='<a href="index.php?&'.$linkaction.'&'.$this->PK_SERVICE.'='.$query_details->row[$this->PK_SERVICE].'">';
														
						}
						if ($hidelabels){
							$details .= "{$val}<br />";
						}else{
							$details .= "{$field}&nbsp;&nbsp;&raquo;&nbsp;{$val}<br />";
						}
						if ($i==0 && $tolink){
							$details .='</a>';
						}
						$i++;
					}
				}
				//echo ("$hl<br/>");
				if ($hl){
					$details .=$hl."<br/>";
				} 
				if ($showstatus){
					$details .="<p>$st</p>"; 
					
				}
				$details .="</div>"; 
				//echo $details;
				$dtvalue = $query_monthly_ids->row[$dt_field];
				$dtvalue = explode(" ",$dtvalue);
				$dtvalue = $dtvalue[0];
				$adata[$dtvalue][] = $details;
				}
				
			}
			
			/* Pazienti totali */
			$num_tot_pat++;
		}
		//$monthly_table .= "OUT:".$num_out_pat."<br/>";
		//$monthly_table .= "IN:".$num_in_pat."<br/>";
		//$monthly_table .= "TOT:".$num_tot_pat."<br/>";
		return $adata;
	}

	function dayadd($days, $date=null, $format="d/m/Y"){
		//Note:
		//Dates in the m/d/y or d-m-y formats are disambiguated by looking at the separator between the various components: if the separator is a slash (/), then the American m/d/y is assumed; whereas if the separator is a dash (-) or a dot (.), then the European d-m-y format is assumed.
		//To avoid potential ambiguity, it's best to use ISO 8601 (YYYY-MM-DD) dates or DateTime::createFromFormat() when possible. 
		//$date = DateTime::createFromFormat($format, $date ? $date : date($format));
		$date = ($date ? $date : date($format));
		if ($format == "d/m/Y"){
			$spl = explode("/",$date);
			$date = $spl[1]."/".$spl[0]."/".$spl[2];
		}
		//echo "D: $days -- DT: $date -- F: $format<br/>";
		$rval = date($format,strtotime($days." days",strtotime($date) ));
		return $rval;
	}
	function date_day($date, $format="d/m/Y"){
		if ($format == "d/m/Y"){
			$spl = explode("/",$date);
			$date = $spl[1]."/".$spl[0]."/".$spl[2];
		}		
		return date("j", strtotime($date));
	}
	function date_month($date, $format="d/m/Y"){
		if ($format == "d/m/Y"){
			$spl = explode("/",$date);
			$date = $spl[1]."/".$spl[0]."/".$spl[2];
		}		
		return date("d M Y", strtotime($date));
	}
	
	function t($s){
		$t['Mon'] = "Lun";
		$t['Tue'] = "Mar";
		$t['Wed'] = "Mer";
		$t['Thu'] = "Gio";
		$t['Fri'] = "Ven";
		$t['Sat'] = "Sab";
		$t['Sun'] = "Dom";
		$t['January'] = "Gennaio";
		$t['February'] = "Febbraio";
		$t['March'] = "Marzo";
		$t['April'] = "Aprile";
		$t['May'] = "Maggio";
		$t['June'] = "Giugno";
		$t['July'] = "Luglio";
		$t['August'] = "Agosto";
		$t['September'] = "Settembre";
		$t['October'] = "Ottobre";
		$t['November'] = "Novembre";
		$t['December'] = "Dicembre";
		$retval = $s;
		if (isset($t[$s])){
			$retval = $t[$s];
		}
		return $retval;
	}
	////// ----- FINE Gestione Calendario ////
	
	
	function nextRiunioni($dt_field, $linkaction){
		global $service;
		global $conn;
		
		$txt = "";
		
		$from = date("d/m/Y");
		//$dt_field = "DATA_SED_DT";
		$sqlq = "
		select {$this->PK_SERVICE},{$dt_field},D_TIPO_SED from {$service}_registrazione 
		where center in (select center from {$service}_utenti_centri where userid ='{$this->session_vars['remote_userid']}')
		and {$dt_field} >= to_date('{$from}', 'DD/MM/YYYY')
		order by {$dt_field} asc
		";
		//$monthly_table.=$sql_monthly_pat."<br/>";
		
		$sql = new query($this->conn);
		$sql->set_sql($sqlq);
		$sql->exec();
		$i = 0;
		while($sql->get_row() && $i<5){ //Max 5 sedute
			$i++;
			$txt.= '<tr style="background-color: #fafafa; border-style: solid; border-color: #e0e8eb; border-width: 1px; color:#585858;"><td style="padding:6px;">';
			if (!$linkaction){
				$linkaction = "exams=visite_exam.xml";
			}
			
			$show_next_seduta=true;
			$profilo = $this->getProfilo($conn,$this->session_vars['remote_userid']);
			$stato = $this->GetWFState($conn,$service,$sql->row[$this->PK_SERVICE]);
			#Mostro la seduta al componente se e' stato inviato l'OdG
			//if($stato < 4 && $profilo =='CMP') $show_next_seduta=false;
		
			if($show_next_seduta){
			
				$txt.= '<a href="index.php?&'.$linkaction.'&'.$this->PK_SERVICE.'='.$sql->row[$this->PK_SERVICE].'">';
				$txt.= $sql->row[$dt_field];
				$txt.= "</a>";
				$txt.= "<br/>{$sql->row['D_TIPO_SED']}";
				$txt.= '</td></tr>';
			
			}
			
		}
		
		
		return $txt;
	}
	
	function inEmendamento($conn, $service, $pkid){
		//print_r($this);
		$config_service=$this->config_service;
		if ($config_service['eQuery']!=1) return false;
		
		$array['ID_STUD'] =  $pkid;
		if (!is_numeric($array['ID_STUD'])){
			return false;
		}
		$sql = "select IN_EMENDAMENTO from {$service}_REGISTRAZIONE where {$this->PK_SERVICE}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($conn);
		$query->exec($sql, $array);
		if ($query->get_row()){
			//echo $query->row['IN_EMENDAMENTO'];
			return ($query->row['IN_EMENDAMENTO'] == 1);
		}else{
			return false;
		}
	}
	
	function inEmeApprovazione($conn, $service, $pkid){
		//print_r($this);
		$config_service=$this->config_service;
		if ($config_service['eQuery']!=1) return false;
		
		$array['ID_VAL'] =  $pkid;
		if (!is_numeric($array['ID_VAL'])){
			return false;
		}
		$sql = "select IN_EMENDAMENTO_APPROVAZIONE from {$service}_REGISTRAZIONE where {$this->PK_SERVICE}=:id_val and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($conn);
		$query->exec($sql, $array);
		if ($query->get_row()){
			//echo $query->row['IN_EMENDAMENTO'];
			return ($query->row['IN_EMENDAMENTO_APPROVAZIONE'] == 1);
		}else{
			return false;
		}
	}
	
	function GetEmendamentoState($conn, $service, $pkid){
		$array['ID_STUD'] =  $pkid;
		if (!is_numeric($array['ID_STUD'])){
			return false;
		}
		if ($this->inEmendamento($conn, $service, $pkid)){
			//$sql=new query($conn);
			$sql = "select MAX(EQUERY_INT) as MAXINT from {$service}_EQ where {$this->PK_SERVICE}=:id_stud and stato <> 1 ";
			$query = new query($conn);
			$query->exec($sql, $array);
			$eqint = 0;
			if ($query->get_row()){
				$eqint = $query->row['MAXINT'];
			}
			if ($eqint){
				$array['EQ_INT'] =  $eqint;
				$sql = "select STATO from {$service}_EQ where {$this->PK_SERVICE}=:id_stud and EQUERY_INT=:eq_int ";
				$query = new query($conn);
				$query->exec($sql, $array);
				if ($query->get_row()){
					return $query->row['STATO'];
				}else{
					return false;
				}
			}else{
				return false;
			}
		}
	}
	
	function CheckVisitClosed($pkId,$vId,$vProgr){
		global $service;
		$closed = 0;
		//$vIds = "2";
		if ($pkId != 'next') {
			$sql_query="select min(nvl(visitclose,0)) vc from {$service}_coordinate where {$this->PK_SERVICE}={$pkId} and visitnum = {$vId} and visitnum_progr={$vProgr} and inizio=1";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$closed=$sql->row['VC'];
	
		}
		return ($closed==1);
	}
	function CheckVisitSaved($pkId,$vId,$vProgr){
		global $service;
		$closed = 0;
		//$vIds = "2";
		if ($pkId != 'next') {
			//ATTENZIONE: Porta male.
			$sql_query="select min(nvl(inizio,0)) vc from {$service}_coordinate where {$this->PK_SERVICE}={$pkId} and visitnum = {$vId} and visitnum_progr={$vProgr} ";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$closed=$sql->row['VC'];
	
		}
		return ($closed==1);
	}
	function CheckVisitProgrEnd($pkId,$vId,$vProgr){
		global $service;
		$closed = 0;
		//$vIds = "2";
		if ($pkId != 'next') {
			//ATTENZIONE: Porta male.
			$sql_query="select min(nvl(fine,0)) vc from {$service}_coordinate where {$this->PK_SERVICE}={$pkId} and visitnum = {$vId} and visitnum_progr={$vProgr} ";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$closed=$sql->row['VC'];
	
		}
		return ($closed==1);
	}
	function CheckEsamSaved($pkId,$vId,$vProgr,$esam){
		global $service;
		$closed = 0;
		if ($pkId != 'next') {
			$sql_query="select min(nvl(inizio,0)) es from {$service}_coordinate where {$this->PK_SERVICE}={$pkId} and visitnum = {$vId} and visitnum_progr={$vProgr} and esam={$esam}";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$closed=$sql->row['ES'];
	
		}
		return ($closed==1);
	}
	
}

?>
