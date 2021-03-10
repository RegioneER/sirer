<?php

/**
 * Classe Studio
 * 
 * Contiene tutte le spcifiche dello studio tra cui il Controller
 *
 * @package XMR 2.0
 */
class Study extends Study_mproto {
	
	#GIULIO 11-07-2012#Funzione che mi restituisce 1 se il profilo e' Segreteria o Nucleo e lo studio non e' stato valutato
	function show_link_ritiro($link_ritira=null){
		$array_stati = array(1,2,3,4,5,8);
		$array_profilo = array('SGR','URC');
		if (in_array($this->GetStato(),$array_stati) && in_array($this->getProfilo($this->user->userid),$array_profilo)){$link_ritira=1;}	
		return $link_ritira;
		}
	
	function schede_riapribili(){
		
		global $in;
		
		$link_riapri="";
		$procedi=0;
		$xmr=$this->service;
		$pkid=$this->pk_service;
		$v=$in['VISITNUM'];
		$vprogr=$in['VISITNUM_PROGR'];
		$es=$in['ESAM'];
		if($in['PROGR'] && $in['PROGR']!=""){
			$progr=$in['PROGR'];
			$progr_and="and progr=".$progr;
		}
		
		//controllo compilazione schede successive ai datti amministrativi
		$compilate = false;
		$sql = "select fine from {$this->service}_coordinate where {$this->xmr->pk_service}={$pkid} and (visitnum=5 or visitnum=9) and visitnum_progr=$vprogr";
		$query = new query($this->conn);
		$query->exec($sql);
		while ($query->get_row()){
			if ($query->row['FINE']){
				$compilate = true;
			}
		}
		$sql = "select fine from {$this->service}_coordinate where {$this->xmr->pk_service}={$pkid} and visitnum=22";
		$query = new query($this->conn);
		$query->exec($sql);
		while ($query->get_row()){
			if ($query->row['FINE']){
				$compilate = true;
			}
		}
		
		if($v==0 && $es==1)							 $procedi=1; //Riassunto dello studio interventistico con farmaco (dati_clinici.xml)
		elseif($v==0 && $es==6  && $progr)	 $procedi=1; //Farmaci (studi_farmaco.xml)
		
		elseif($v==0 && $es==9)							 $procedi=1; //Riassunto dello studio interventistico senza farmaco e dispositivo (dati_clinicinf.xml)
		 
		elseif($v==0 && $es==8)							 $procedi=1; //Riassunto dello studio interventistico con dispositivo medico (dati_clinicidm.xml)
		elseif($v==0 && $es==7  && $progr)	 $procedi=1; //Dispositivi medici (studi_dispositivi.xml)
		
		elseif($v==0 && $es==11)						 $procedi=1; //Riassunto dello studio osservazionale con farmaco (dati_clinicios.xml)
		elseif($v==0 && $es==121)	 $procedi=1; //Riassunto dello studio con campioni biologici (dati_clinicicb.xml)
		elseif($v==0 && $es==15 && $progr)	 $procedi=1; //Farmaci in studio osservazionale (studi_farmacoos.xml)
		
		elseif($v==0 && $es==16)						 $procedi=1; //Riassunto dello studio osservazionale senza farmaco e dispositivo (dati_cliniciossf.xml)
		
		elseif($v==0 && $es==17)						 $procedi=1; //Riassunto dello studio osservazionale con dispositivo medico (dati_cliniciosdm.xml)
		elseif($v==0 && $es==18 && $progr)	 $procedi=1; //Dispositivi medici (studi_dispositivios.xml)
		
		elseif($v==0 && $es==19)						 $procedi=1; //Riassunto dello studio terapeutico (dati_cliniocomp.xml)
		elseif($v==0 && $es==60 && $progr)	 $procedi=1; //Farmaci in studio di uso terapeutico (studi_farmacoter.xml)
		
		elseif($v==0 && $es==20)						 $procedi=1; //Riassunto dello studio con impiego di tessuti umani (dati_cliniotessu.xml)
		elseif($v==0 && $es==5  && $progr)	 $procedi=1; //Utilizzo del tessuto umano (studi_tessuto.xml)
		
		elseif($v==0 && $es==24)						 $procedi=1; //Riassunto dello studio (dati_clinioaltro.xml)
		                              	 
		elseif($v==0 && $es==12 && $progr)	 $procedi=1; //Sottostudi (sottostudi.xml)
		elseif($v==0 && $es==10 && $progr)	 $procedi=0; //Centri partecipanti (dati_centri.xml)
		elseif($v==0 && $es==2  && $progr)	 $procedi=1; //Documentazione studio (documentazione_core.xml)
		                              	 
		elseif($v==1 && $es==22)						 $procedi=1; //Dati di gestione locale dello studio (dati_locale_step1.xml)
		elseif($v==1 && $es==23 && $progr)	 $procedi=1; //Documentazione centro specifica (documentazione_centro.xml)
		                              	 
		elseif($v==2)							 $procedi=0; //Verifica documentazione (invio_per_valutazione.xml)
		                              	 
		elseif($v==4)							 $procedi=0; //Inserisci parere (val_dati_valutazione.xml)
		                              	 
		elseif($v==10 && $compilate==false)	 $procedi=1; //Dati amministrativi per avvio studio (val_richiesta_delibera.xml)
		                           
		elseif($v==20)					 	 $procedi=0; //Dati Emendamento (val_emendamenti.xml)
		                              	 
		elseif($v==5 && $es==1)							 $procedi=1; //Avvio studio (dati_monitoraggio.xml)
		elseif($v==5 && $es==3 && $progr)		 $procedi=1; //Rapporti avanzamento studio (rapporti.xml)
		elseif($v==5 && $es==2)							 $procedi=1; //Conclusione studio nel centro (chiusura.xml)
		                              	 
		elseif($v==9 && $es==2 && $progr)		 $procedi=1; //Eventi avversi seri interni (val_susar.xml)
		elseif($v==9 && $es==9 && $progr)		 $procedi=1; //Eventi avversi seri dispositivo (val_susar_dm.xml)
		elseif($v==9 && $es==3 && $progr)		 $procedi=1; //Eventi avversi seri esterni (val_susar_ext.xml)
		elseif($v==9 && $es==4 && $progr)		 $procedi=1; //Rapporti di sicurezza (rapportisic.xml)
		                              	 
		elseif($v==22 && $es==221)	 				 $procedi=1; //Conclusione in toto studio  (conclusione_toto.xml)
		elseif($v==22 && $es==222 && $progr) $procedi=1; //Risultati studio (risultati_toto.xml)
		elseif($v==22 && $es==223 && $progr) $procedi=1; //Pubblicazioni studio (pubblicazioni_toto.xml)
		
			
		if($procedi && isset($es)){
		#Controllo che la scheda in questione sia inviata
		$scheda_chiusa=false;
		$sql = "select fine from {$this->service}_coordinate where {$this->xmr->pk_service}={$pkid} and visitnum=$v and visitnum_progr=$vprogr and esam=$es $progr_and";
		$query = new query($this->conn);
		$query->exec($sql);
		$vc = false;
		while ($query->get_row()){
			if ($query->row['FINE']){
				$scheda_chiusa = true;
			}
		}
		
		if($xmr=="CE" && $this->getProfilo($this->user->userid)=="SGR" && $scheda_chiusa){
			
				$link_riapri="index.php?RIAPRISCHEDADM=yes&VISITNUM=$v&VISITNUM_PROGR=$vprogr&ESAM=$es&PROGR=$progr&ID_STUD=$pkid";
				
			}
		}
		//print($link_riapri);
		return $link_riapri;
	}
	
	function tb_riassuntiva(){
		$sql_query_info_studio = "select * from CE_INFO_STUDIO where id_stud={$this->pk_service}";
		$sql_info_studio = new query ( $this->conn );
		$sql_info_studio->get_row ( $sql_query_info_studio );
		
		$query_clock = "SELECT
				userid_ins,
				azienda_ente,
  			registrazione_dt,
 	 			TRUNC(sysdate -registrazione_dt)                                     AS clock_giorni,
  			TRUNC((sysdate-registrazione_dt-TRUNC(sysdate-registrazione_dt))*24) AS clock_ore
			FROM
  			CE_registrazione,ana_utenti_2
			WHERE
  			id_stud={$this->pk_service}
  			and CE_registrazione.userid_ins=ana_utenti_2.userid";
		$sql_clock = new query ( $this->conn );
		$sql_clock->get_row ( $query_clock );
		$clock="{$sql_clock->row['AZIENDA_ENTE']} ha iniziato la compilazione <br>da {$sql_clock->row['CLOCK_GIORNI']} gg e {$sql_clock->row['CLOCK_ORE']} hh";
		
		$sql_query_info_studio_eudract = "select * from CE_INFO_STUDIO_EUDRACT where id_stud={$this->pk_service}";
		$sql_info_studio_eudract = new query ( $this->conn );
		$sql_info_studio_eudract->get_row ( $sql_query_info_studio_eudract );
		
		$sql_query_segr = "select count(*) as segreteria from CE_COORDINATE where id_stud={$this->pk_service} and visitnum=2";
		$sql_segr = new query ( $this->conn );
		$sql_segr->get_row ( $sql_query_segr );
		$segreteria=$sql_segr->row['SEGRETERIA'];
		
		$output = "";
		$output .= '<table class="table table-striped table-bordered table-hover">';
		$output .= '<thead id="tb_riass">';
		$output .= '<tr>';
		$output .= '<th class="int">ID</th>';
		$output .= '<th class="int">Tipologia studio</th>';
		$output .= '<th class="int">Eudract Number</th>';
		$output .= '<th class="int">Codice studio promotore</th>';
		$output .= '<th class="int">Titolo studio</th>';
		//$output .= '<td class="int">Data di richiesta promotore</td>';
		//$output .= '<td class="int">Em.</td>';
		$output .= '<th class="int">Stato</th>';
		if ($this->dettaglio['STATO_INT']==2) $output .= '<th class="int" align="center"><img src="/images/clock.png"></img></th>';
		if ($this->show_link_ritiro()){$output .= '<th class="int">Azioni</th>';}
		if ($this->schede_riapribili()  && $this->dettaglio['STATO_INT']>=6){$output .= '<th class="int">Azioni</th>';}
		if ($segreteria!=0) {$output .= '<th class="int">Progress report</th>';}
		$output .= '</tr>';
		$output .= '</thead>';
		$output .= '<tr>';
		$stato_chiuso = 9;
		$output .= '<td class="sc4bis">'.$this->dettaglio[$this->xmr->pk_service].'</td>';
		$output .= '<td class="sc4bis">'.$this->dettaglio['D_TIPO_SPER'].'</td>';
		$output .= '<td class="sc4bis">'.$sql_info_studio_eudract->row['EUDRACT_NUM'].'</td>';
		$output .= '<td class="sc4bis">'.$sql_info_studio->row['CODICE_PROT'].'</td>';
		$output .= '<td class="sc4bis">'.$sql_info_studio->row['TITOLO_PROT'].'</td>';
		//$output .= '<td class="sc4bis">'.$sql_info_studio->row['RICH_DT'].'</td>';
		//$output .= '<td class="sc4bis">'.($this->dettaglio['EMENDAMENTO']?$this->dettaglio['EMENDAMENTO']:"-").'</td>';
		//$output .= '<td class="sc4bis">'.($this->dettaglio['VISITNUM_PROGR']>0?$this->dettaglio['VISITNUM_PROGR']:"-").'</td>';
		$output .= '<td class="sc4bis">'.$this->dettaglio['STATO'].'</td>';
		if ($this->dettaglio['STATO_INT']==2) $output .= '<td class="sc4bis">'.$clock.'</td>';
		if ($this->show_link_ritiro()){$output .= '<td class="sc4bis" align="left">'.($this->dettaglio['STATO_INT']<$stato_chiuso?'<a href="index.php?ID_STUD='.$this->dettaglio[$this->xmr->pk_service].'&Ritira=yes" >'."Ritira studio":'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;').'</a></td>';}
		if($this->schede_riapribili()  && $this->dettaglio['STATO_INT']>=6){$output .= '<td class="sc4bis" align="center"><a href="'.$this->schede_riapribili().'" > Riapri scheda </a></td>';}
		if ($segreteria!=0) {$output .= '<td class="sc4bis" align="center"><a target="new" href="/pentaho/api/repos/%3Ahome%3Atsc%3Ace_online%3Aprogress_report_toscana.prpt/viewer?id_stud='.$this->dettaglio[$this->xmr->pk_service].'&userid='.$this->user->userid.'" ><i class="icon-signal bigger-140"></i></a></td>';}
		$output .= '</tr>';
		$output .= '</table>';
		
		//print_r($this);
		//$output .= "PK_SERVICE: ".$this->xmr->pk_service."<br/>";
		//$output .= "PREFIX: ".$this->xmr->prefix."<br/>";
		//print_r($this->pk_service);
		//print_r($this->dettaglio);
		
		/* #Progress report, eventualmente riabilitare
		$output .= $this->SpecchiettoGestionePratiche();
		$output .= "<table class=\"specchiettoGeneralebottoni\" align=\"center\">
		<tr><td colspan=\"2\" style=\"margin:2px; padding:2px;\"><b>Progress report</b></td></tr>";
		$output .= "<td class=\"specchiettoGenerale\" width=50%>{$this->SpecchiettoGestionePraticheButton()}</td>";
		$output .= "<td class=\"specchiettoGenerale\" width=50%>{$this->SpecchiettoAvanzamentoButton()}</td>";
		$output .= "</table>";
		*/
		
		//print_r($this->es_form);
		
		return $output;
	}
	
	function CheckVisione() {
		
		#EMENDAMENTI INIZIO
		if (isset($this->pk_service) && $this->pk_service!='next' && $this->pk_service!=''){
		
			$sql_query_eq = "select * from CE_REGISTRAZIONE where id_stud={$this->pk_service}";
			$sql_eq = new query ( $this->conn );
			$sql_eq->get_row ( $sql_query_eq );
			
			#Per mostrare le matitine alla SEGRETERIA in fase di richiesta emendamento
			if($sql_eq->row['IN_EMENDAMENTO']==1 && $sql_eq->row['IN_EMENDAMENTO_APPROVAZIONE']!=0){
    		$this->config_service['eQuerySpec']['Integrazione']['ROLE']="Unita di ricerca";
  		}
    	
  		$sql_query_eq_s = "select STATO from CE_EQ where id_stud={$this->pk_service} and equery_int=(select max(equery_int) from CE_EQ where id_stud={$this->pk_service})";
			$sql_eq_s = new query ( $this->conn );
			$sql_eq_s->get_row ( $sql_query_eq_s );
			
			#Per mostrare i punti esclamativi alla SEGRETERIA in fase di approvazione emendamento
  		if($sql_eq->row['IN_EMENDAMENTO']==1 && $sql_eq->row['IN_EMENDAMENTO_APPROVAZIONE']!=1 && $sql_eq_s->row['STATO']==2){
    		$this->config_service['eQuerySpec']['Integrazione']['ROLE']="Unita di ricerca";
  		}
  		
  	}
  	#EMENDAMENTI FINE

		parent::CheckVisione();
		
		global $in;
		
		#GIULIO 14-11-2012 Gestione della riassegnazione dei profili DE e RO
		if (isset($this->pk_service) && $this->pk_service!='next' && $this->pk_service!=''){
		$sql_query = "select ID_STATO from CEWF_STATO where pk_service={$this->pk_service}";
		$sql = new query ( $this->conn );
		$sql->get_row ( $sql_query );
		if ($_GET['DEBUG'] == '1') {
				//print_r ($this->session_vars);
				//print_r ($this->user->profilo);
			}
		
		#La segreteria passa da RO a DE nel caso in cui lei stessa richieda una richiesta di documentazione
		if($sql->row ['ID_STATO'] == '4' && $this->session_vars ['USER_TIP'] == 'RO' && $this->user->profilo=='Segreteria CE') {$this->session_vars ['USER_TIP'] = 'DE';}
		
		}
	}


function DelVisitProgr($visitnum, $vprogr, $redir=true) {
        if ($this->integrazione->eq_enabled){
            if ($this->integrazione->eq_int==''){
                $this->integrazione->createEq();
            }
            $bind['PK_SERVICE']=$this->pk_service;
            $bind['VISITNUM']=$visitnum;
            $bind['VISITNUM_PROGR']=$vprogr;
            $sql_delete = "delete from {$this->service}_coordinate
            where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr and eq_action=1";
            $sql=new query($this->conn);
            $sql->ins_upd ($sql_delete,$bind);#binded

            $sql_update="update {$this->service}_coordinate set inv_query={$this->integrazione->eq_int}, eq_action=2 where
            {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr
            ";
            $sql=new query($this->conn);
            $sql->ins_upd($sql_update,$bind);#binded
            $this->conn->commit ();
            $redirect = "index.php?{$this->config['PK_SERVICE']}={$this->pk_service}&exams&VISITNUM=$visitnum";
            header ( "location:$redirect" );
            die ( $redirect );
        }
        $sql = new query ( $this->conn );
        foreach ( $this->vlist->esams [$visitnum] as $key => $val ) {
            $xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
            $xml_form->xml_form_by_file ( $this->xml_dir . '/' . $val ['XML'] );
            $tbs [$xml_form->form ['TABLE']] = true;
        }
        unset($bindInsert);
        $bindInsert['PK_SERVICE']=$this->pk_service;
        $bindInsert['VISITNUM']=$visitnum;
        $bindInsert['VISITNUM_PROGR']=$vprogr;
        foreach ( $tbs as $key => $val ) {
            $sql_storico = "insert into s_{$key} select '{$this->user->userid}', sysdate, storico_id.nextval, 'E', null, {$key}.* from {$key}
            where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
            $sql->ins_upd ($sql_storico,$bindInsert); #binded
        }
        $sql_delete = "delete from {$this->service}_coordinate where {$this->config['PK_SERVICE']}={$this->pk_service} and visitnum=$visitnum and visitnum_progr=$vprogr";
        unset($bindDelete);
        $bindDelete['PK_SERVICE']=$this->pk_service;
        $bindDelete['VISITNUM']=$visitnum;
        $bindDelete['VISITNUM_PROGR']=$vprogr;
        $sql->ins_upd ($sql_delete,$bindDelete);#binded
        if(!$this->config_service['ALLOW_BLANK_VPROGR']){       
            $sql_query = "select max(visitnum_progr) as maxvprogr from {$this->service}_coordinate
            where {$this->config['PK_SERVICE']}={$this->pk_service}
            and visitnum=$visitnum
            ";
            $sql->get_row ( $sql_query );
            $maxvprogr = $sql->row ['MAXVPROGR'];

            for($i = $vprogr; $i < $maxvprogr; $i ++) {
                $nextvprogr = $i + 1;
                $sql_insert_coord = "
                insert into {$this->service}_coordinate
                (VISITNUM,VISITNUM_PROGR,PROGR,ESAM,INIZIO,FINE,INSERTDT,MODDT,USERID,VISITCLOSE,INV_QUERY,{$this->config['PK_SERVICE']},ABILITATO)
                select
                VISITNUM,$i,PROGR,ESAM,INIZIO,FINE,INSERTDT,MODDT,USERID,VISITCLOSE,INV_QUERY,{$this->config['PK_SERVICE']},ABILITATO
                from {$this->service}_coordinate where
                {$this->config['PK_SERVICE']}=:pk_service
                and visitnum=:visitnum
                and visitnum_progr=:visitnum_progr
                ";
                unset($bindInsert);
                $bindInsert['PK_SERVICE']=$this->pk_service;
                $bindInsert['VISITNUM']=$visitnum;
                $bindInsert['VISITNUM_PROGR']=$nextvprogr;
                $sql->ins_upd ($sql_insert_coord,$bindInsert);#binded
                foreach ( $tbs as $key => $val ) {
                    $sql_storico = "insert into s_{$key} select '{$this->user->userid}', sysdate, storico_id.nextval, 'S', null, {$key}.* from {$key}
                    where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
                    $sql->ins_upd ($sql_storico,$bindInsert);#binded
                    $sql_update = "update $key set visitnum_progr=$i
                    where {$this->config['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr";
                    $sql->ins_upd ($sql_update,$bindInsert);#binded
                }
                $sql_delete_coord = "delete from {$this->service}_coordinate
                where
                {$this->config['PK_SERVICE']}=:pk_service
                and visitnum=:visitnum
                and visitnum_progr=:visitnum_progr";
                unset($bindDelete);
                $bindDelete['PK_SERVICE']=$this->pk_service;
                $bindDelete['VISITNUM']=$visitnum;
                $bindDelete['VISITNUM_PROGR']=$nextvprogr;
                $sql->ins_upd ($sql_delete_coord,$bindDelete);#binded
            }
        }
        
        #Luigi gestione della cancellazione dei centri a causa della cancellazione delle visitprogr centrospecifiche.
        #Giulio 09/10/2015 se elimino l'unico centro -> non elimino il record in ce_coordinate ma sbianco INIZIO e FINE altrimenti non ho pi?link per aggiungere un centro
        if ($visitnum==1){
        		
        		$sql_where_coord = "
                where
                {$this->config['PK_SERVICE']}=:pk_service
                and visitnum=:visitnum
                and visitnum_progr=:visitnum_progr
                and esam=:esam
                and progr=:progr
                ";
              unset($bindD);
              $bindD['PK_SERVICE']=$this->pk_service;
              $bindD['VISITNUM']=0;
              $bindD['VISITNUM_PROGR']=0;
              $bindD['ESAM']=10;
              $bindD['PROGR']=$vprogr+1;
        		
        		$sql_count_coord = "select count(*) as C from {$this->service}_coordinate where
              {$this->config['PK_SERVICE']}={$this->pk_service}
              and visitnum=0
              and visitnum_progr=0
              and esam=10
              ";
            $sql->exec($sql_count_coord);
						$sql->get_row();
						$unico_centro=$sql->row['C'];
            if($unico_centro==1) {
            	#Sbianco INIZIO e FINE
            	$sql_upd_coord = "update {$this->service}_coordinate set inizio='', fine='' ".$sql_where_coord;
              $sql->ins_upd ($sql_upd_coord,$bindD);#binded
              #Elimino CE_CENTRILOCALI
              $sql_delete_centriloc = "delete from {$this->service}_centrilocali ".$sql_where_coord;
              $sql->ins_upd ($sql_delete_centriloc,$bindD);#binded
              
            }
        		else{
        		$sql_delete_coord = "delete from {$this->service}_coordinate ".$sql_where_coord;
              $sql->ins_upd ($sql_delete_coord,$bindD);#binded
        	}
        
        	}
        
        $this->conn->commit ();
        
        if($redir==true){
            $redirect = "index.php?{$this->config['PK_SERVICE']}={$this->pk_service}&exams&VISITNUM=$visitnum";
            header ( "location:$redirect" );
            die ( $redirect );
        }
    }
	

	function Controller(){
		
		global $in;

	if ($_GET[$this->xmr->pk_service] && is_numeric($_GET[$this->xmr->pk_service])){
		$this->build_dettaglio();
		//LUIGI: override studi pediatrici. basta questo perch&egrave; la visibilit&agrave; &egrave; tutta gestita dalla vista utenti_centri
		if ($this->dettaglio['PEDIATRICO']==1){
			if($this->getProfilo($this->user->userid)=="SGR"){
				$query_image = "select * from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}'";
				$sql_image=new query($this->conn);
				$sql_image->exec($query_image);
				$sql_image->get_row();
					if ($sql_image->row['ID_CE']==4){
						$this->session_vars ['USER_TIP'] = "DE";
					}
					else{
						if($_GET['VISITNUM'] == 0)
							$this->session_vars ['USER_TIP'] = "RO";
						else
							error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro in quanto si tratta di studio pediatrico di competenza CEP.",'errore di visibilit&agrave;');
						}
			}
		}else{

			if (($_GET['VISITNUM'] == 0 || $_GET['VISITNUM'] == 1) && $this->pk_service != 'next'){
				$profilo = $this->getProfilo($this->user->userid);
				$stato = $this->dettaglio['STATO_INT'];
				$userins = $this->dettaglio['USERID_INS'];
				$profiloins = $this->getProfilo($userins);
				//echo "ST: $stato - UI: $userins";
				//echo $profilo;
				switch ($profilo){
					case "URC":
					#Luigi: solo il nucleo che ha inserito lo studio puo' compilare
						$this->session_vars ['USER_TIP'] = "RO";
						if ($this->user->userid==$this->dettaglio['USERID_INS']) $this->session_vars ['USER_TIP'] = "DE";
					break;
					case "SGR":
					#GC 31-10-2013#SGR di default RO
						$this->session_vars ['USER_TIP'] = "RO";
						#La SGR puo' modificare solo gli studi inseriti da lei stessa (diventa DE)
						$query_userid_1="select count(*) as CONTO from CE_VENETO_SGR_USERID_INS where userid='{$this->session_vars['remote_userid']}' and center='{$this->pk_service}'";
						$sql_user_1=new query($this->conn);
						$sql_user_1->get_row($query_userid_1);
					if ($sql_user_1->row['CONTO']>=1)	$this->session_vars ['USER_TIP'] = "DE";
					break;
				}
				//print_r($this->user);
				//die();
			}
			if ($_GET['VISITNUM'] == 1 && isset($_GET['ESAM'])){
				$profilo = $this->getProfilo($this->user->userid);
				$stato = $this->dettaglio['STATO_INT'];
				$userins = $this->dettaglio['USERID_INS'];
				$profiloins = $this->getProfilo($userins);
				//echo "ST: $stato - UI: $userins";
				//echo $profilo;
				switch ($profilo){
					case "URC":
					#Luigi: il nucleo puo' compilare solo le schede del suo centro
						$this->session_vars ['USER_TIP'] = "RO";
						$progr_ce=$_GET['VISITNUM_PROGR']+1;
						$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_nucleo_userid where id_nucleo=(
						select id_nucleo from ce_veneto_nucleo where id_str=(
						select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
						)
						) and userid='{$this->user->userid}'";
						$sql_ce = new query ( $this->conn );
						$sql_ce->get_row ( $sql_query_ce );
						if ($sql_ce->row['CONTO_CE'] == '1') {
							$this->session_vars ['USER_TIP'] = "DE";
						}
						else{
							error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
						}
					break;
				}
				//print_r($this->user);
				//die();
			}
			if ($_GET['VISITNUM'] == 1 && ($_GET['ESAM']==22 || $_GET['ESAM']==23)){
	
				$profilo = $this->getProfilo($this->user->userid);
				$stato = $this->dettaglio['STATO_INT'];
				$userins = $this->dettaglio['USERID_INS'];
				$profiloins = $this->getProfilo($userins);
				//echo "ST: $stato - UI: $userins";
				//echo $profilo;
				switch ($profilo){
					case "SGR":
						$this->session_vars ['USER_TIP'] = "RO";
					$userins = $this->dettaglio['USERID_INS'];
					$progr_ce=$_GET['VISITNUM_PROGR']+1;
					
					#Controllo se la SGR collegata (o equipollente) ha anche inserito il centro.
					$query_1 = "select count(*)as OK from 
									(select c.userid,l.id_stud,l.progr as center
									from ce_veneto_userid_ce c,
										ce_centrilocali l,
										ana_utenti_2 a
										where c.id=l.centro
										and c.userid=a.userid
										and a.profilo = 'SGR')
								where id_stud='{$this->pk_service}'
								and center={$progr_ce}
								and userid='{$this->session_vars['remote_userid']}'";
						$sql_1 = new query ( $this->conn );
						$sql_1->get_row ( $query_1 );
						//echo $query_1."<br>";
						$query_2 = "select ID_CE from 
									ana_utenti_2
									where userid='{$this->session_vars['remote_userid']}'";
						$sql_2 = new query ( $this->conn );
						$sql_2->get_row ( $query_2 );
						$query_3 = "select PARERE_CEP from 
									ce_valutazione
									where id_stud='{$this->pk_service}'
									and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}
									and progr=(
									select max(progr) from ce_valutazione where id_stud='{$this->pk_service}'
									and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}
									)
									";
						$sql_3 = new query ( $this->conn );
						$sql_3->get_row ( $query_3 );
						#Luigi 11-11-2014#La SGR puo' compilare solo i dati centro specifici dei propri nuclei. Inoltre non puo' visualizzare nulla degli altri
						if($sql_1->row['OK']) $this->session_vars ['USER_TIP'] = "DE";
						else if ($stato==5 && $this->dettaglio['PEDIATRICO']==2 && $sql_2->row['ID_CE']==4 && $_GET['ESAM']==23 && $sql_3->row['PARERE_CEP']==1 ) $this->session_vars ['USER_TIP'] = "DE";
						else if ($stato==5 && $this->dettaglio['PEDIATRICO']==2 && $sql_2->row['ID_CE']==4 && $_GET['ESAM']==22 && $sql_3->row['PARERE_CEP']==1 ) $this->session_vars ['USER_TIP'] = "RO";
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
					case "CMP":
					$userins = $this->dettaglio['USERID_INS'];
					$progr_ce=$_GET['VISITNUM_PROGR']+1;
					
					#Controllo se il componente collegato (o equipollente) e' afferente al centro.
					$query_1 = "select count(*)as OK from 
									(select c.userid,l.id_stud,l.progr as center
									from ce_veneto_userid_ce c,
										ce_centrilocali l,
										ana_utenti_2 a
										where c.id=l.centro
										and c.userid=a.userid
										and a.profilo = 'CMP')
								where id_stud='{$this->pk_service}'
								and center={$progr_ce}
								and userid='{$this->session_vars['remote_userid']}'";
						$sql_1 = new query ( $this->conn );
						$sql_1->get_row ( $query_1 );
						//echo $query_1."<br>";
						#Luigi 17-11-2014# il componente puo' salizzare solo i dati centro specifici dei nuclei afferenti.
						if($sql_1->row['OK']) $this->session_vars ['USER_TIP'] = "RO";
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
				}
				//print_r($this->user);
				//die();
			}
			if ($_GET['VISITNUM'] == 2 && isset($_GET['PROGR'])){
				$profilo = $this->getProfilo($this->user->userid);
				$stato = $this->dettaglio['STATO_INT'];
				$userins = $this->dettaglio['USERID_INS'];
				//echo "ST: $stato - UI: $userins";
				//echo $profilo;
				switch ($profilo){
					case "SGR":
						#Luigi: la segreteria puo' compilare solo le schede del suo centro
						$this->session_vars ['USER_TIP'] = "RO";
						$progr_ce=$_GET['VISITNUM_PROGR']+1;
						$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id in(
						select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
						) and userid='{$this->user->userid}'";
						$sql_ce = new query ( $this->conn );
						$sql_ce->get_row ( $sql_query_ce );
						if ($sql_ce->row['CONTO_CE'] == '1') {
							$this->session_vars ['USER_TIP'] = "DE";
						}
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
					case "URC":
					#Luigi: il nucleo puo' visualizzare solo le schede del suo centro
						$progr_ce=$_GET['VISITNUM_PROGR']+1;
						$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_nucleo_userid where id_nucleo=(
						select id_nucleo from ce_veneto_nucleo where id_str=(
						select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
						)
						) and userid='{$this->user->userid}'";
						$sql_ce = new query ( $this->conn );
						$sql_ce->get_row ( $sql_query_ce );
						if ($sql_ce->row['CONTO_CE'] == '1') {
							$this->session_vars ['USER_TIP'] = "RO";
						}
						else{
							error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
						}
					break;
					case "CMP":
					$userins = $this->dettaglio['USERID_INS'];
					$progr_ce=$_GET['VISITNUM_PROGR']+1;
					
					#Controllo se il componente collegato (o equipollente) e' afferente al centro.
					$query_1 = "select count(*)as OK from 
									(select c.userid,l.id_stud,l.progr as center
									from ce_veneto_userid_ce c,
										ce_centrilocali l,
										ana_utenti_2 a
										where c.id=l.centro
										and c.userid=a.userid
										and a.profilo = 'CMP')
								where id_stud='{$this->pk_service}'
								and center={$progr_ce}
								and userid='{$this->session_vars['remote_userid']}'";
						$sql_1 = new query ( $this->conn );
						$sql_1->get_row ( $query_1 );
						//echo $query_1."<br>";
						#Luigi 17-11-2014# il componente puo' visalizzare solo i dati centro specifici dei nuclei afferenti.
						if($sql_1->row['OK']) $this->session_vars ['USER_TIP'] = "RO";
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
					default:
						$this->session_vars ['USER_TIP'] = "RO"; 
					break;
				}
				//print_r($this->user);
				//die();
			}
			if (($_GET['VISITNUM'] == 8 || $_GET['VISITNUM'] == 10 || $_GET['VISITNUM'] == 5 || $_GET['VISITNUM'] == 9)  && isset($_GET['PROGR'])){
				$profilo = $this->getProfilo($this->user->userid);
				switch ($profilo){
					case "AMM":
					break;
					case "URC":
					#Luigi: il nucleo puo' visualizzare solo le schede del suo centro
						$progr_ce=$_GET['VISITNUM_PROGR']+1;
						$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_nucleo_userid where id_nucleo=(
						select id_nucleo from ce_veneto_nucleo where id_str=(
						select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
						)
						) and userid='{$this->user->userid}'";
						$sql_ce = new query ( $this->conn );
						$sql_ce->get_row ( $sql_query_ce );
						if ($sql_ce->row['CONTO_CE'] == '1') {
							$this->session_vars ['USER_TIP'] = "RO";
						}
						else{
							error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
						}
					break;
					case "SGR":
						#Luigi: la segreteria puo' compilare solo le schede del suo centro
						$this->session_vars ['USER_TIP'] = "RO";
						$progr_ce=$_GET['VISITNUM_PROGR']+1;
						$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id in(
						select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
						) and userid='{$this->user->userid}'";
						$sql_ce = new query ( $this->conn );
						$sql_ce->get_row ( $sql_query_ce );
						if ($sql_ce->row['CONTO_CE'] == '1') {
							$this->session_vars ['USER_TIP'] = "DE";
						}
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
					case "CMP":
					$userins = $this->dettaglio['USERID_INS'];
					$progr_ce=$_GET['VISITNUM_PROGR']+1;
					
					#Controllo se il componente collegato (o equipollente) e' afferente al centro.
					$query_1 = "select count(*)as OK from 
									(select c.userid,l.id_stud,l.progr as center
									from ce_veneto_userid_ce c,
										ce_centrilocali l,
										ana_utenti_2 a
										where c.id=l.centro
										and c.userid=a.userid
										and a.profilo = 'CMP')
								where id_stud='{$this->pk_service}'
								and center={$progr_ce}
								and userid='{$this->session_vars['remote_userid']}'";
						$sql_1 = new query ( $this->conn );
						$sql_1->get_row ( $query_1 );
						//echo $query_1."<br>";
						#Luigi 17-11-2014# il componente puo' visalizzare solo i dati centro specifici dei nuclei afferenti.
						if($sql_1->row['OK']) $this->session_vars ['USER_TIP'] = "RO";
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
					default:
						$this->session_vars ['USER_TIP'] = "RO"; 
					break;
				}
				//echo $this->session_vars ['USER_TIP'];
				//die();
			}
			if ($_GET['VISITNUM'] == 9 || $_GET['VISITNUM'] == 22 || $_GET['VISITNUM'] == 5 ){
				$profilo = $this->getProfilo($this->user->userid);
				//echo $profilo;
				switch ($profilo){
					case "SGR":
						$this->session_vars ['USER_TIP'] = "DE";
					break;
					case "URC":
						$this->session_vars ['USER_TIP'] = "DE";
					break;
					default:
						$this->session_vars ['USER_TIP'] = "RO"; 
					break;
				}
				//print_r($this->user);
				//die();
			}
			if ($_GET['VISITNUM'] == 4 && isset($_GET['PROGR'])){	
				$profilo = $this->getProfilo($this->user->userid);
				switch ($profilo){
					case "SGR":
						#Luigi: la segreteria puo' compilare solo le schede del suo centro
						$this->session_vars ['USER_TIP'] = "RO";
						$progr_ce=$_GET['VISITNUM_PROGR']+1;
						$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id in(
						select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
						) and userid='{$this->user->userid}'";
						$sql_ce = new query ( $this->conn );
						$sql_ce->get_row ( $sql_query_ce );
						if ($sql_ce->row['CONTO_CE'] == '1') {
							$this->session_vars ['USER_TIP'] = "DE";
						}
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
					case "URC":
					#Luigi: il nucleo puo' visualizzare solo le schede del suo centro
						$progr_ce=$_GET['VISITNUM_PROGR']+1;
						$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_nucleo_userid where id_nucleo=(
						select id_nucleo from ce_veneto_nucleo where id_str=(
						select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
						)
						) and userid='{$this->user->userid}'";
						$sql_ce = new query ( $this->conn );
						$sql_ce->get_row ( $sql_query_ce );
						if ($sql_ce->row['CONTO_CE'] == '1') {
							$this->session_vars ['USER_TIP'] = "RO";
						}
						else{
							error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
						}
					break;
					case "CMP":
					$userins = $this->dettaglio['USERID_INS'];
					$progr_ce=$_GET['VISITNUM_PROGR']+1;
					
					#Controllo se il componente collegato (o equipollente) e' afferente al centro.
					$query_1 = "select count(*)as OK from 
									(select c.userid,l.id_stud,l.progr as center
									from ce_veneto_userid_ce c,
										ce_centrilocali l,
										ana_utenti_2 a
										where c.id=l.centro
										and c.userid=a.userid
										and a.profilo = 'CMP')
								where id_stud='{$this->pk_service}'
								and center={$progr_ce}
								and userid='{$this->session_vars['remote_userid']}'";
						$sql_1 = new query ( $this->conn );
						$sql_1->get_row ( $query_1 );
						//echo $query_1."<br>";
						#Luigi 17-11-2014# il componente puo' visalizzare solo i dati centro specifici dei nuclei afferenti.
						if($sql_1->row['OK']) $this->session_vars ['USER_TIP'] = "RO";
						else error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
					break;
					default:
						$this->session_vars ['USER_TIP'] = "RO"; 
					break;
				}
			}
			if ($_GET['VISITNUM'] == 20){
				$profilo = $this->getProfilo($this->user->userid);
				//echo "QUA";
				//echo $profilo;
				switch ($_GET['ESAM']){
					case 1:
						//echo "ENTRO!";
						//echo "<br/>$profilo<br/>";
						switch ($profilo){
							case "SGR":
								$this->session_vars ['USER_TIP'] = "DE";
								//echo "DE!";
							break;
							case "URC":
								$this->session_vars ['USER_TIP'] = "DE";
								//echo "DE!";
							break;
							default:
								$this->session_vars ['USER_TIP'] = "RO"; 
							break;
						}
						//print_r($this->user);
						//die();
						break;
					
					case 10:
						//echo "ENTRO!";
						//echo "<br/>$profilo<br/>";
						switch ($profilo){
							case "SGR":
								$this->session_vars ['USER_TIP'] = "DE";
								//echo "DE!";
							break;
							case "URC":
								$this->session_vars ['USER_TIP'] = "DE";
								//echo "DE!";
							break;
							default:
								$this->session_vars ['USER_TIP'] = "RO"; 
							break;
						}
						if (isset ($_GET['PROGR'])){
							$sql_query_ce = "select RISERVATO from ce_docum_eme
										where id_stud='{$this->pk_service}' and progr={$_GET['PROGR']} and esam=10 and visitnum_progr={$_GET['VISITNUM_PROGR']}";
										$sql_ce = new query ( $this->conn );
										$sql_ce->get_row ( $sql_query_ce );
							
							if ($sql_ce->row['RISERVATO']=="" or $sql_ce->row['RISERVATO']==0) continue;
							else {
								$sql_query_ce2 = "select ID_CE from ana_utenti_2
										where userid='{$this->session_vars['remote_userid']}'";
										$sql_ce2 = new query ( $this->conn );
										$sql_ce2->get_row ( $sql_query_ce2 );
								echo $sql_ce2->row['ID_CE'];
								if ($sql_ce->row['RISERVATO']!=$sql_ce2->row['ID_CE'])
									error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
							}
						}
						
						break;
					
					case 2:
						//echo "ENTRO!";
						//echo "<br/>$profilo<br/>";
						switch ($profilo){
							case "SGR":
								//Controllo se il centro relativo alla scheda corrente e' afferente al comitato etico
								if (isset ($_GET['PROGR'])){
									$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id=(
									select centro from ce_EME_REGINVIO where id_stud='{$this->pk_service}' and progr={$_GET['PROGR']} and esam=2 and visitnum_progr={$_GET['VISITNUM_PROGR']}
										) and userid='{$this->user->userid}'";
									$sql_ce = new query ( $this->conn );
									$sql_ce->get_row ( $sql_query_ce );
									if ($sql_ce->row['CONTO_CE'] ==1) {
										$this->session_vars ['USER_TIP'] = "DE";
									}
									else{
											error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
										}
								}
							break;
							default:
								$this->session_vars ['USER_TIP'] = "RO"; 
							break;
						}
						//print_r($this->user);
						//die();
						break;
					
					case 3:
						//echo "ENTRO!";
						//echo "<br/>$profilo<br/>";
						switch ($profilo){
							case "SGR":
								//Controllo se il centro relativo alla scheda corrente e' afferente al comitato etico
								if (isset ($_GET['PROGR'])){
									$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id=(
									select centro from ce_EME_REGINVIO where id_stud='{$this->pk_service}' and progr={$_GET['PROGR']} and esam=2 and visitnum_progr={$_GET['VISITNUM_PROGR']}
										) and userid='{$this->user->userid}'";
									$sql_ce = new query ( $this->conn );
									$sql_ce->get_row ( $sql_query_ce );
									if ($sql_ce->row['CONTO_CE'] ==1) {
										$this->session_vars ['USER_TIP'] = "DE";
									}
									else{
											error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
										}
								}
							break;
							default:
								$this->session_vars ['USER_TIP'] = "RO"; 
							break;
						}
						//print_r($this->user);
						//die();
						break;
						
						case 4:
						//echo "ENTRO!";
						//echo "<br/>$profilo<br/>";
						switch ($profilo){
							case "SGR":
								//Controllo se il centro relativo alla scheda corrente e' afferente al comitato etico
								if (isset ($_GET['PROGR'])){
									$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id=(
									select centro from ce_EME_REGINVIO where id_stud='{$this->pk_service}' and progr={$_GET['PROGR']} and esam=2 and visitnum_progr={$_GET['VISITNUM_PROGR']}
										) and userid='{$this->user->userid}'";
									$sql_ce = new query ( $this->conn );
									$sql_ce->get_row ( $sql_query_ce );
									if ($sql_ce->row['CONTO_CE'] ==1) {
										$this->session_vars ['USER_TIP'] = "DE";
									}
									else{
											error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
										}
								}
							break;
							default:
								$this->session_vars ['USER_TIP'] = "RO"; 
							break;
						}
						//print_r($this->user);
						//die();
						break;
						
						case 5:
						//echo "ENTRO!";
						//echo "<br/>$profilo<br/>";
						switch ($profilo){
							case "SGR":
								//Controllo se il centro relativo alla scheda corrente e' afferente al comitato etico
								if (isset ($_GET['PROGR'])){
									$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id=(
									select centro from ce_EME_REGINVIO where id_stud='{$this->pk_service}' and progr={$_GET['PROGR']} and esam=2 and visitnum_progr={$_GET['VISITNUM_PROGR']}
										) and userid='{$this->user->userid}'";
									$sql_ce = new query ( $this->conn );
									$sql_ce->get_row ( $sql_query_ce );
									if ($sql_ce->row['CONTO_CE'] ==1) {
										$this->session_vars ['USER_TIP'] = "DE";
									}
									else{
											error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
										}
								}
							break;
							default:
								$this->session_vars ['USER_TIP'] = "RO"; 
							break;
						}
						//print_r($this->user);
						//die();
						break;
						
						case 6:
						//echo "ENTRO!";
						//echo "<br/>$profilo<br/>";
						switch ($profilo){
							case "SGR":
								//Controllo se il centro relativo alla scheda corrente e' afferente al comitato etico
								if (isset ($_GET['PROGR'])){
									$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id=(
									select centro from ce_EME_REGINVIO where id_stud='{$this->pk_service}' and progr={$_GET['PROGR']} and esam=2 and visitnum_progr={$_GET['VISITNUM_PROGR']}
										) and userid='{$this->user->userid}'";
									$sql_ce = new query ( $this->conn );
									$sql_ce->get_row ( $sql_query_ce );
									if ($sql_ce->row['CONTO_CE'] ==1) {
										$this->session_vars ['USER_TIP'] = "DE";
									}
									else{
											error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere ai dati di questo centro",'errore di visibilit&agrave;');
										}
								}
							break;
							default:
								$this->session_vars ['USER_TIP'] = "RO"; 
							break;
						}
						//print_r($this->user);
						//die();
						break;
				}
			}
			
			if (($_GET['mod_lettera_eme']=="yes" || $_GET['mod_istruttoria_ts_eme']=="yes") && !isset($_GET['ESAM']) && isset($_GET['PROGR'])  && isset($_GET['VISITNUM_PROGR']) && isset($_GET['ID_STUD']) ){
				$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_userid_ce where id=(
				select centro from ce_EME_REGINVIO where id_stud='{$this->pk_service}' and progr={$_GET['PROGR']} and esam=2 and visitnum_progr={$_GET['VISITNUM_PROGR']}
					) and userid='{$this->user->userid}'";
				$sql_ce = new query ( $this->conn );
				$sql_ce->get_row ( $sql_query_ce );
				if ($sql_ce->row['CONTO_CE'] ==1) {
					$this->session_vars ['USER_TIP'] = "DE";
				}
				else{
						$this->session_vars ['USER_TIP'] = "RO";
					}
			}
			
			if (isset($_GET['stampa_template']) && $_GET['stampa_template']!=''){
			$this->stampaTemplate($_GET['stampa_template']);
			}
		
		}
		#LUIGI Nuova gestione EME e riapertura schede
			if ($in['RIAPRISCHEDADM'] == "yes"){
				if($this->getProfilo($this->user->userid)=="SGR"){
					$this->session_vars ['USER_TIP'] = $in['USER_TIP'] = 'DM';
				}
			}
		//Luigi: INIZIO BLOCCO PK_OBJ
		//Luigi: TENERE ALLA FINE DI TUTTI GLI ALTRI CONTROLLI DE/RO!!!
		//Luigi: tutti gli userid non afferenti alla sperimentazione vengono buttati fuori, tranne nel caso di iserimento centro forzato
		if (isset($this->pk_service) && $this->pk_service != 'next'){
			$sql_query_ce = "select count(*) as CONTO_USER from ce_utenti_centri where userid='{$this->user->userid}' and center='{$this->pk_service}'";
					$sql_ce = new query ( $this->conn );
					$sql_ce->get_row ( $sql_query_ce );
					if ($sql_ce->row['CONTO_USER'] == 0 && !(isset($_GET['FORCE_CENTRO']) && $_GET['VISITNUM']==0 && $_GET['ESAM']==10)) {
						error_page($this->session_vars['remote_userid'],"L'utente {$this->session_vars['remote_userid']} non pu&ograve; accedere a questo studio",'errore di visibilit&agrave;');
					}
		}
		//Luigi: FINE BLOCCO PK_OBJ
	
	}
		
		//echo "<br/>{$this->session_vars ['USER_TIP']}<br/>";
		$this->vlist_root->session_vars['USER_TIP'] = $this->session_vars ['USER_TIP'];
		$in['USER_TIP'] = $this->session_vars ['USER_TIP'];
		//echo "<br/>{$this->session_vars ['WFact']}<br/>";
		//echo "<br/>{$in['USER_TIP']}<br/>";
		
		if ($_GET['CLOSE_EME_INT'] =="yes" ){
			$array_c['ID_STUD'] = $_GET['ID_STUD'];
			$sql = "update {$this->service}_COORDINATE set FINE=1 where {$this->xmr->pk_service}=:id_stud and esam in (1,10) and visitnum=20";
			$query = new query($this->conn);
			$query->exec($sql, $array_c);
			$this->conn->commit ();
			header("location:index.php?&VISITNUM=20&ID_STUD={$_GET['ID_STUD']}&exams=visite_exams.xml");
			die();
		}
		
		
		if (isset ($_GET['CloseVisitProgr'])){
			$this->CloseSchedeProgr(false);
			$docCentroVisit = 1;
			$profilo = $this->getProfilo($this->user->userid);

			if ($_GET['VISITNUM'] == $docCentroVisit){
				if($this->session_vars['DEBUG']==1) echo "<br/>docCentroVisit=".$docCentroVisit;
				
//				if ($this->dettaglio['STATO_INT'] >= 3){
//					if($this->session_vars['DEBUG']==1) echo "<br/>STATO_INT={$this->dettaglio['STATO_INT']}";
//					
//					$this->openVerificaDocSingle($this->pk_service, $_GET['VISITNUM'], $_GET['VISITNUM_PROGR']);
//				}

			$this->openVerificaDocSingle($this->pk_service, $_GET['VISITNUM'], $_GET['VISITNUM_PROGR']);
			
			#GC 22-10-2013#Valorizzo PRIMO_INVIO con sysdate la prima volta che viene inviato un blocco di dati CS
			$sql_query="select primo_invio from ce_registrazione where id_stud={$this->pk_service}";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
				
			if ($sql->row['PRIMO_INVIO']==''){
				$table = "REGISTRAZIONE";
				$field = "PRIMO_INVIO"; 
				$this->setDate($table,$field,$this->pk_service);
			}
			
			$sql_insert_date = "
                insert into {$this->service}_REP_DATE_INVIO
                (VISITNUM,VISITNUM_PROGR,PROGR,ESAM,MODDT,{$this->config['PK_SERVICE']})
                VALUES (:VISITNUM,:VISITNUM_PROGR,:PROGR,:ESAM,SYSDATE,:ID_STUD)
                ";
                unset($bindInsert);
                $bindInsert['ID_STUD']=$this->pk_service;
                $bindInsert['VISITNUM']=1;
                $bindInsert['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
				$bindInsert['PROGR']=1;
				$bindInsert['ESAM']=22;
                $sql->ins_upd ($sql_insert_date,$bindInsert);#binded
			
			}
			
		}
		
		#Se sto cancellando un centro (esam 10) -> devo eliminare gli esam:
		#22 e 23 (progressiva) della visitnum 1 
		#1 (progressiva) della visitnum 2
		#L'esam 10 verra' cancellato nel controller dello study.inc.mproto.php
		if ($_GET ['ELIMINA_LA_SCHEDA'] == 'yes' && $_GET ['VISITNUM'] == '0' && $_GET ['ESAM'] == '10') {
			$visitnum_progr_new=$_GET ['PROGR']-1;
			$center = $_GET['CENTER'];
			
			if($this->session_vars['DEBUG']==1) echo($_GET ['VISITNUM']." - ".$_GET ['VISITNUM_PROGR']." - ".$_GET ['ESAM']." - ".$_GET ['PROGR']." - ".$this->pk_service." <br> ");
			
			#GIULIO 18-12-2012# Elimino i dati centro specifici (visitnum=1 esam=2,3)
			$this->DelVisitProgr(1, $visitnum_progr_new, false);
			#GIULIO 18-12-2012# Elimino i dati di istruttoria (visitnum=2 esam=1) se ci sono
			$this->DelVisitProgr(2, $visitnum_progr_new, false);
			#GIULIO 20-12-2012# Elimino i dati di parere (visitnum=4 esam=1) se ci sono
			$this->DelVisitProgr(4, $visitnum_progr_new, false);
			
			#GIULIO 20-12-2012# Elimino i dati di FUP (visitnum=5 esam=1) se ci sono
			$this->DelVisitProgr(5, $visitnum_progr_new, false);
			#GIULIO 20-12-2012# Elimino i dati di AMM (visitnum=10 esam=1,2,3,4) se ci sono
			$this->DelVisitProgr(10, $visitnum_progr_new, false);	

			}

	#GENERAZIONE LETTERA DI PARERE	
	if ($_GET ['mod_lettera'] == 'yes') {
		if ($this->session_vars ['USER_TIP'] == "DE"){
			#controllo se il parere e' inviato
			$sql_query_co = "select * from ce_coordinate where id_stud={$_GET['ID_STUD']} and visitnum=4 and visitnum_progr={$_GET['VISITNUM_PROGR']} and esam=1 and progr={$_GET['PROGR']}";
			$sql_co = new query ( $this->conn );
			$sql_co->set_sql ( $sql_query_co );
			$sql_co->exec ();
			$sql_co->get_row ();
			
			//if($sql_co->row['FINE']){
			
			$query_image = "select * from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}'";
			$sql_image=new query($this->conn);
			$sql_image->exec($query_image);
			$sql_image->get_row();
			if ($sql_image->row['ID_CE']==1) {$area_vasta="AREA VASTA SUD EST"; $ubicato="Farmacia Ospedaliera AOUS - Viale Bracci, 16 - 53100 Siena"; $telefono="0577-586358"; $li="Siena"; $email="c.etico@ao-siena.toscana.it";}
			if ($sql_image->row['ID_CE']==2) {$area_vasta="AREA VASTA NORD OVEST"; $ubicato="Stabilimento di Santa Chiara - Via Roma, 67 - 56126 Pisa"; $telefono="050/996392-247-287"; $li="Pisa"; $email="direzione.uslnordovest@postacert.toscana.it";}
			if ($sql_image->row['ID_CE']==3) {$area_vasta="AREA VASTA CENTRO"; $ubicato="Nuovo Ingresso Careggi (NIC) - Largo Brambilla, 3 - 50134 Firenze"; $telefono="055-7947396"; $li="Firenze"; $email="segrcesf@unifi.it";}
			if ($sql_image->row['ID_CE']==4) {$area_vasta="COMITATO ETICO PEDIATRICO"; $ubicato="Meyer - Viale Pieraccini, 28 - 50139 Firenze"; $telefono="055-56621"; $li="Firenze"; $email="comitato.etico@meyer.it";}
			
			if ($_POST ['lettera'] == 'salva') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$sql_insert_storico = "insert into s_ce_lettera_parere select '{$this->user->userid}', sysdate, storico_id.nextval, t.* from ce_lettera_parere t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_insert_storico );
				$sql->ins_upd ();
				$sql_delete = "delete from ce_lettera_parere t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql->set_sql ( $sql_delete );
				$sql->ins_upd ();
				$values ['ID_STUD'] = $this->pk_service;
				$values ['VISITNUM'] = '4';
				$values ['VISITNUM_PROGR'] = $_POST ['VISITNUM_PROGR'];
				$values ['ESAM'] = '1';
				$values ['PROGR'] = $_POST ['PROGR'];
				$values ['USERID_INS'] = $this->user->userid;
				$values ['INSDT'] = "sysdate";
				$values ['LETTERA'] = $_POST ['content'];
				$pk = '';
				print_r ($values);
				$sql->insert ( $values, "ce_lettera_parere", $pk );
				$this->conn->commit ();
				header("location:index.php?mod_lettera=yes&VISITNUM={$_GET['VISITNUM']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&PROGR={$_GET['PROGR']}&ID_STUD={$_GET['ID_STUD']}");
				die();
			}
			if ($_POST ['lettera'] == 'pdf') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$filetxt=$_POST ['content'];
				//echo $filetxt;
				//die();
				$filename = "Parere_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.html";
				$filename_pdf = "Parere_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.pdf";
				$path = $_SERVER ['PATH_TRANSLATED'];
				$images_path = str_replace ( "index.php", "../gendocs/", $path );
				$path = str_replace ( "index.php", "temp_html/", $path );
				$file_html = $path . $filename;
				$html_handle = fopen ( $file_html, "w" );
				$filetxt = str_replace ( "/gendocs/", $images_path, $filetxt );
				$filetxt = str_replace ( "style=\"display:\"", "", $filetxt );
				fwrite ( $html_handle, $filetxt );
				$htmldoc="/http/local/bin/htmldoc_rw";
				system ( "$htmldoc -t pdf14 --fontsize 10 --no-title --size A4 --charset iso-8859-15 --browserwidth 1024 --footer .1. --header .t. --headfootsize 8 --headfootfont Times-Italic--bottom 10mm --top 6mm --left 10mm --right 10mm --path /amministrazione/schede_utente --webpage {$path}/{$filename}> {$path}/{$filename_pdf}" );
				die ( "<html><head><meta http-equiv=\"refresh\" content=\"0;url=temp_html/{$filename_pdf}\"></head><body>Generazione PDF in corso</body></html>" );
				die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=temp_html/{$filename_pdf}\"></head></html>" );
			}
			
			#dati della valutazione
			$sql_query_1 = "select v.*,to_char(v.riunione_ce_dt,'DD/MM/YYYY') as data_sed_dt  from ce_valutazione v where id_stud={$_GET['ID_STUD']} and visitnum=4 and visitnum_progr={$_GET['VISITNUM_PROGR']} and esam=1 and progr={$_GET['PROGR']}";
			$sql_1 = new query ( $this->conn );
			$sql_1->set_sql ( $sql_query_1 );
			$sql_1->exec ();
			$sql_1->get_row ();
			
			#dati della seduta
			$sql_query_sed = "select to_char(data_sed_dt,'DD/MM/YYYY') as data_sed_dt from GSE_REGISTRAZIONE 
				WHERE id_sed=(
				select link_odg from ce_valutazione 
				where id_stud={$_GET['ID_STUD']} 
				and visitnum=4 
				and visitnum_progr={$_GET['VISITNUM_PROGR']} 
				and esam=1 
				and progr={$_GET['PROGR']}
				)";
			$sql_sed = new query ( $this->conn );
			$sql_sed->set_sql ( $sql_query_sed );
			$sql_sed->exec ();
			$sql_sed->get_row ();
			
			#documentazione generale
			$vett_doc_gen=explode("|",$sql_1->row['DOCS_VALUTATI_GEN']);
			
			$sql_query_4 = "select * from ce_documentazione where id_stud={$_GET['ID_STUD']}";
			$sql_4 = new query ( $this->conn );
			$sql_4->set_sql ( $sql_query_4 );
			$sql_4->exec ();
			while($sql_4->get_row ()){
				if(in_array($sql_4->row['PROGR'],$vett_doc_gen)){
					$doc_gen_altro=$descr_agg_gen='';
					if($sql_4->row['DOC_GEN_ALTRO']) $doc_gen_altro=" - ".$sql_4->row['DOC_GEN_ALTRO'];
					if($sql_4->row['DESCR_AGG']) $descr_agg_gen=" - ".$sql_4->row['DESCR_AGG'];
					if($sql_4->row['D_DOC_GEN']=='Altro') $html_doc_gen.="<b><li>".$sql_4->row['DOC_GEN_ALTRO'].$descr_agg_gen."</b>&nbsp;<small>(versione <i>".$sql_4->row['DOC_VERS']."</i> del <i>".$sql_4->row['DOC_DT']."</i>)</small></li></b>";
					else $html_doc_gen.="<b><li>".$sql_4->row['D_DOC_GEN'].$doc_gen_altro.$descr_agg_gen."</b>&nbsp;<small>(versione <i>".$sql_4->row['DOC_VERS']."</i> del <i>".$sql_4->row['DOC_DT']."</i>)</small></li></b>";
				}
			}
			
			#documentazione centro-specifica
			
			#splitto sul |_VISITNUM_PROGR, ma resta un pipe finale...
			$split_var_doc_loc="|".$_GET['VISITNUM_PROGR']."_";
			
			#...elimino l'ultimo pipe |
			$docs_loc=substr($sql_1->row['DOCS_VALUTATI_LOC'],0,strlen($sql_1->row['DOCS_VALUTATI_LOC'])-1);
			
			#esplodo i risultati nel vettore $vett_doc_loc
			$vett_doc_loc=explode($split_var_doc_loc,$docs_loc);
			
			$sql_query_5 = "select * from ce_docum_centro where id_stud={$_GET['ID_STUD']} and visitnum_progr={$_GET['VISITNUM_PROGR']}";
			$sql_5 = new query ( $this->conn );
			$sql_5->set_sql ( $sql_query_5 );
			$sql_5->exec ();
			while($sql_5->get_row ()){
				if(in_array($sql_5->row['PROGR'],$vett_doc_loc)){
					$doc_loc_altro=$descr_agg_loc='';
					if($sql_5->row['DOC_LOC_ALTRO']) $doc_loc_altro=" - ".$sql_5->row['DOC_LOC_ALTRO'];
					if($sql_5->row['DESCR_AGG']) $descr_agg_loc=" - ".$sql_5->row['DESCR_AGG'];
					if($sql_5->row['D_DOC_LOC']=='Altro') $html_doc_loc.="<b><li>".$sql_5->row['DOC_LOC_ALTRO'].$descr_agg_loc."</b>&nbsp;<small>(versione <i>".$sql_5->row['DOC_VERS']."</i> del <i>".$sql_5->row['DOC_DT']."</i>)</small></li></b>";
					else $html_doc_loc.="<b><li>".$sql_5->row['D_DOC_LOC'].$doc_loc_altro.$descr_agg_loc."</b>&nbsp;<small>(versione <i>".$sql_5->row['DOC_VERS']."</i> del <i>".$sql_5->row['DOC_DT']."</i>)</small></li></b>";
				}
			}
			

			#Parere
			if($sql_1->row['RIS_DELIB']==1) {//$parere_ce="(SPER.SENZA PRESCRIZIONI = Parere A)";
																			 $html_parere="FAVOREVOLE";
																			 $testo_parere_3="Si richiede che questo Comitato Etico venga informato dell'inizio della sperimentazione, del suo svolgimento con una relazione annuale e della sua conclusione o eventuale interruzione. Inoltre, dovr&agrave; essere informato di ogni successivo emendamento al protocollo e degli eventi avversi, seri e inattesi, insorti nel corso dello studio, che potrebbero influire sulla sicurezza dei soggetti o sul proseguimento dello studio. In difetto delle suddette relazioni l'efficacia dell'approvazione del protocollo deve intendersi sospesa a tutti gli effetti.";
																			 }
			if($sql_1->row['RIS_DELIB']==2) {//$parere_ce="D = PARERE NON FAVOREVOLE";
																			 $html_parere="NON FAVOREVOLE";
																			 $testo_parere="<i><b><u>motivazioni del rifiuto:</u></b></i>";
																			 $rilievi_generali=$sql_1->row['OBIETTIVO'];
																			 }
			if($sql_1->row['RIS_DELIB']==3) {//$parere_ce="SPERIMENTAZIONE - SOSPENSIVO <br/><br/> C (da utilizzare per modifiche al protocollo/costi/indagini di sicurezza ecc)";
																			 $html_parere="SOSPENSIVO";
																			 $testo_parere="<i><b><u>Il Comitato Etico ha rilevato le seguenti criticit&agrave;:</u></b></i>";
																			 $testo_parere_2="Il protocollo potr&agrave; essere attuato nella ricerca clinica in oggetto solo non appena si sar&agrave; ottemperato alle suddette prescrizioni che, pertanto, dovranno essere preventivamente ripresentate e approvate da questo Comitato.";
																			 $rilievi_generali=$sql_1->row['OBIETTIVO'];
																			 }
			if($sql_1->row['RIS_DELIB']==6) {
																			 $html_parere="SOSPENSIVO FORMALE";
																			 $testo_parere="<i><b><u>lo sperimentatore per la prossima riunione del Comitato Etico prevista per il giorno ../../....  alle ore ..:.., nella sala riunioni n&deg;410 secondo piano Ex Collegio Ioanneum affinch&egrave; possa le seguenti criticit&agrave;:</u></b></i>";
																			 $testo_parere_2="Il protocollo potr&agrave; essere attuato nella ricerca clinica in oggetto solo non appena si sar&agrave; ottemperato alle suddette prescrizioni che, pertanto, dovranno essere preventivamente ripresentate e approvate da questo Comitato.";
																			 }
			if($sql_1->row['RIS_DELIB']==4 || $sql_1->row['RIS_DELIB']==5) { //$parere_ce="SPER. CON PRESCRIZ. <br/><br/> B (da utilizzare se vengono richieste modifiche sulla scheda informativa)";
																			 $html_parere="FAVOREVOLE A CONDIZIONE";
																			 $testo_parere="<i><b><u>con le seguenti prescrizioni:</u></b></i>";
																			 $testo_parere_2="<u>Non sar&agrave; necessario aspettare la seduta successiva del ../../.... al C.E. ma sar&agrave; sufficiente far pervenire la documentazione modificata secondo quanto richiesto, prima dell'inizio effettivo dello studio, contrassegnando la nuova versione della scheda informativa/modulo di consenso con una nuova data di elaborazione ed evidenziando le modifiche richieste per avere una presa d'atto finale.  Le correzioni sono di carattere materiale e non ostano il parere positivo del Comitato Etico.</u>";
																			 $testo_parere_3="Si richiede che questo Comitato Etico venga informato dell'inizio della sperimentazione, del suo svolgimento con una relazione annuale e della sua conclusione o eventuale interruzione. Inoltre, dovr&agrave; essere informato di ogni successivo emendamento al protocollo e degli eventi avversi, seri e inattesi, insorti nel corso dello studio, che potrebbero influire sulla sicurezza dei soggetti o sul proseguimento dello studio. In difetto delle suddette relazioni l'efficacia dell'approvazione del protocollo deve intendersi sospesa a tutti gli effetti.";
																			 }
			if($sql_1->row['RIS_DELIB']==8) { $html_parere="PRESA D'ATTO"; }
			
			#COMPONENTI
			$vett_membri_approv=explode("|",$sql_1->row['MEMBRI_APPROV']);
			$sql_query_2 = "select * from ana_utenti_2 a, utenti u where a.userid=u.userid and u.abilitato=1 and a.id_ce={$this->getIdCe($this->user->userid)} and a.profilo='CMP' and a.subprofilo is null order by cognome";
			$sql_2 = new query ( $this->conn );
			$sql_2->set_sql ( $sql_query_2 );
			$sql_2->exec ();
			$count_vot=0;
			while($sql_2->get_row()){
				#PRESENTI
				if(in_array($sql_2->row['USERID'],$vett_membri_approv)){
					$count_vot++;
					$html_membri_approv.="<b>".$sql_2->row['QUALIFICA']." ".$sql_2->row['NOME']." ".strtoupper($sql_2->row['COGNOME'])."</b>".", <i>".$sql_2->row['RUOLO']."</i><br/>";
				}
				#ASSENTI
				else{
					$html_membri_approv_np.="<b>".$sql_2->row['QUALIFICA']." ".$sql_2->row['NOME']." ".strtoupper($sql_2->row['COGNOME'])."</b>".", <i>".$sql_2->row['RUOLO']."</i><br/>";
				}
			}
			 
			#MEMBRI ESTERNI
			$vett_membri_esterni=explode("|",$sql_1->row['MEMBRI_ESTERNI']);
			$sql_query_6 = "select * from ana_utenti_2 a, utenti u where a.userid=u.userid and u.abilitato=1 and a.id_ce={$this->getIdCe($this->user->userid)} and a.profilo='CMP' and (a.subprofilo='EXT' or a.subprofilo='SPE') order by cognome";
			$sql_6 = new query ( $this->conn );
			$sql_6->set_sql ( $sql_query_6 );
			$sql_6->exec ();
			while($sql_6->get_row()){
				if(in_array($sql_6->row['USERID'],$vett_membri_esterni)){
					$membri_esterni.="<b>".$sql_6->row['QUALIFICA']." ".$sql_6->row['NOME']." ".strtoupper($sql_6->row['COGNOME'])."</b>".", <i>".$sql_6->row['RUOLO']."</i><br/>";
				}
			}
			if($membri_esterni)
				$html_membri_esterni="<b>In relazione allo studio erano inoltre presenti alla discussione i seguenti esperti esterni:</b><br/>".$membri_esterni;
			 
			#MEMBRI ASTENUTI
			$vett_membri_astenuti=explode("|",$sql_1->row['MEMBRI_ASTENUTI']);
			$sql_query_ma = "select * from ana_utenti_2 a, utenti u where a.userid=u.userid and u.abilitato=1 and a.id_ce={$this->getIdCe($this->user->userid)} and a.profilo='CMP' and a.subprofilo is null order by cognome";
			$sql_ma = new query ( $this->conn );
			$sql_ma->set_sql ( $sql_query_ma );
			$sql_ma->exec ();
			$count_ma=0;
			while($sql_ma->get_row()){
				if(in_array($sql_ma->row['USERID'],$vett_membri_astenuti)){
					$count_ma++;
					$html_membri_astenuti.="<b>".$sql_ma->row['QUALIFICA']." ".$sql_ma->row['NOME']." ".strtoupper($sql_ma->row['COGNOME'])."</b>".", <i>".$sql_ma->row['RUOLO']."</i><br/>";
				}
			}
			$tot_presenti=$count_vot+$count_ma;
				
			 #dati minimi studio
			 $sql_query_3 = "select * from ce_info_studio where id_stud={$_GET['ID_STUD']}";
			 $sql_3 = new query ( $this->conn );
			 $sql_3->set_sql ( $sql_query_3 );
			 $sql_3->exec ();
			 $sql_3->get_row ();
			 if($sql_3->row['DESCR_CRO'] != '' && $sql_3->row['DESCR_CRO'] != 'NA')
			 	$info_cro="<i><b>Alla CRO</b></i> {$sql_3->row['DESCR_CRO']}<br><br>";
			 
			 #dati minimi centro
			 $sql_query_4 = "select * from ce_centrilocali where id_stud={$_GET['ID_STUD']} and PROGR={$_GET['VISITNUM_PROGR']}+1";
			 $sql_4 = new query ( $this->conn );
			 $sql_4->set_sql ( $sql_query_4 );
			 $sql_4->exec ();
			 $sql_4->get_row ();	
			 
			 #dati minimi centro
			 if (isset($sql_4->row['CENTRO'])){
			 $sql_query_nrc = "select * from ce_veneto_nucleo where id_str={$sql_4->row['CENTRO']}";
			 $sql_nrc = new query ( $this->conn );
			 $sql_nrc->set_sql ( $sql_query_nrc );
			 $sql_nrc->exec ();
			 $sql_nrc->get_row ();	
			 }
			 
			 #dati verificadoc
			 $sql_query_ver = "select * from ce_reginvio 
			 where id_stud={$_GET['ID_STUD']} and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']} 
			 and progr = (select max(progr) from ce_reginvio where id_stud={$_GET['ID_STUD']} and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']})";
			 $sql_ver = new query ( $this->conn );
			 $sql_ver->set_sql ( $sql_query_ver );
			 $sql_ver->exec ();
			 $sql_ver->get_row ();	
			 
			//LUIGI templates lettere di parere
			
			//LUIGI caso interventistico con farmaco
			if ($this->dettaglio['TIPO_SPER']==1){
				$intestazione="dello studio clinico";
				$intestazione2="della sperimentazione";
				$subordinato="<li>rilascio dell'autorizzazione da parte dell'Autorità Competente (AIFA)</li>";
				$studio_sper="la sperimentazione clinica approvata";
				$studio_sper2="sperimentazione clinica con farmaco";
				$disp_aifa="Il presente parere viene rilasciato secondo le Disposizioni di AIFA in vigore dal 1 ottobre 2014, <i>(specificare se tramite Osservatorio Nazionale sulla Sperimentazione clinica dei Medicinali o in modalit&agrave; cartacea)</i>.";
				$SUSAR="<li>eventuali sospette reazioni avverse gravi ed inattese (Suspected Unexpected Serious Adverse Reaction, SUSAR) ed i rapporti periodici di sicurezza (Drug Safety Update Report, DSUR);</li>";
				$SUSAR2="<li>informazioni relative ad eventi e condizioni potenzialmente in grado di incidere negativamente sul rapporto tra rischi e benefici attesi per i partecipanti (ad es. reazioni avverse serie) e/o che incidano significativamente sulla conduzione dello studio (tutte le reazioni avverse serie).</li>";
			}
			//LUIGI caso interventistico con dispositivo medico premarket
			else if ($this->dettaglio['TIPO_SPER']==3 && $sql_3->row['FASE_SPER']==1){
				$intestazione="della indagine clinica pre-market";
				$intestazione2="della indagine clinica";
				$subordinato="<li>notifica all’Autorità Competente, Ministero della Salute – Direzione Generale dei Dispositivi Medici e del Servizio Farmaceutico, secondo le specifiche modalità indicate per le indagini cliniche pre-market</li>";
				$studio_sper="l'indagine clinica approvata";
				$studio_sper2="indagini cliniche pre-market con dispositivi medici";
				$SUSAR="<li>eventuali sospette reazioni avverse gravi ed inattese, nonché eventuali incidenti o mancati incidenti;</li>";
				$SUSAR2="<li>informazioni relative ad eventi e condizioni potenzialmente in grado di incidere negativamente sul rapporto tra rischi e benefici attesi per i partecipanti (ad es. reazioni avverse serie) e/o che incidano significativamente sulla conduzione dello studio (tutte le reazioni avverse serie).</li>";
			}
			//LUIGI caso interventistico con dispositivo medico postmarket
			else if ($this->dettaglio['TIPO_SPER']==3 && $sql_3->row['FASE_SPER']==3){
				$intestazione="della indagine clinica post-market";
				$intestazione2="della indagine clinica";
				$subordinato="<li>notifica all’Autorità Competente, Ministero della Salute – Direzione Generale dei Dispositivi Medici e del Servizio Farmaceutico, secondo le specifiche modalità indicate per le indagini cliniche post-market</li>";
				$studio_sper="l'indagine clinica approvata";
				$studio_sper2="indagini cliniche post-market con dispositivi medici";
				$SUSAR="<li>eventuali sospette reazioni avverse gravi ed inattese, nonché eventuali incidenti o mancati incidenti;</li>";
				$SUSAR2="<li>informazioni relative ad eventi e condizioni potenzialmente in grado di incidere negativamente sul rapporto tra rischi e benefici attesi per i partecipanti (ad es. reazioni avverse serie) e/o che incidano significativamente sulla conduzione dello studio (tutte le reazioni avverse serie).</li>";
			}
			//LUIGI CASO DEFAULT
			else{
				$intestazione="dello studio clinico";
				$intestazione2="della sperimentazione";
				$studio_sper="lo studio clinico approvato";
				$studio_sper2="studi osservazionali / studi con interventi sanitari diversi da farmaci e dispositivi medici";
			}
			
		
		#Interventistico/Osservazionale/Uso Terapeurico/Tessuti Umani con FARMACO
			$query_farmaco = "select * from CE_LISTA_FARMACI where id_stud='{$this->pk_service}'";
			$sql_farmaco = new query ( $this->conn );
			$sql_farmaco->exec($query_farmaco);
			$farmaci="<ul>";
			while($sql_farmaco->get_row()){
				$farmaci.="
				<li>{$sql_farmaco->row['PRINC_ATT']}</li>
				";
			$farmaci.="</ul>";
			}
			
		#Interventistico/Osservazionale con TRATTAMENTO (senza farmaco e dispositivo)
			$query_trat = "select * from CE_LISTA_TRATTAMENTI where id_stud='{$this->pk_service}'";
			$sql_trat = new query ( $this->conn );
			$sql_trat->exec($query_trat);
			while($sql_trat->get_row()){
				$trattamenti.="
				<p>Trattamento in studio: <b>{$sql_trat->row['D_TIPO_TRAT']}</b></p>
				<p>Se altro, specificare: <b>{$sql_trat->row['ALTROSPEC']}</b></p>
				<p>Descrizione trattamento: <b>{$sql_trat->row['DESCR_TRAT']}</b></p>
				<br/>
				";
			}

		#Interventistico/Osservazionale/terapeutico con DISPOSITIVO
			$query_disp = "select * from CE_LISTA_DISPOSITIVI where id_stud='{$this->pk_service}'";
			$sql_disp = new query ( $this->conn );
			$sql_disp->exec($query_disp);
			$dispositivi="<ul>";
			while($sql_disp->get_row()){
				$dispositivi.="
				<li>{$sql_disp->row['DISPOSITIVO']}</li>
				";
			}
			$dispositivi.="</ul>";

			
			//LUIGI lettera uso terapeutico di farmaco
			if ($this->dettaglio['TIPO_SPER']==8)
				$lettera_default="<style>
								td {
							    font-size: 20px;
							    padding: 20px;
								} 
							</style>
							<table width='90%' cellspacing='0' cellpadding='0' border='0' align='center'>
								<tr>
									<td align='center' colspan='3'>
										<p>
											<b>Comitato Etico Regionale per la Sperimentazione Clinica della Regione Toscana<br></b>
											Sezione: {$area_vasta} <br>
											Segreteria Tecnico Scientifica ubicata c/o: {$ubicato} <br>
											Telefono: {$telefono}<br>
											E-mail: {$email}<br>
										</p>
									</td>
									<hr>
								</tr>
  							<tr>
  								<td colspan='3' align='left'>
										Prot n {$sql_1->row['PROTOCOLLO']}<br><br>
											{$li}, il {$sql_1->row['PROTOCOLLO_DT']}<br>
									</td>
								</tr>
								<tr>
									<td colspan='3' align='right'>
  									<i><b>Al Medico richiedente:</b></i><br><br>		
  									<i><b>e p.c.<br> al Direttore Generale della struttura di afferenza del Medico Richiedente<br>
									all’impresa produttrice che ha dichiarato la disponibilità alla fornitura del/i famaco/i</b></i> <br><br>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='left'>																
										<p><b>Oggetto:</b> Comunicazione del parere relativo alla richiesta di autorizzazione all’uso terapeutico di medicinale sottoposto a sperimentazione clinica.<br>
										<p>Codice Protocollo (in caso di expanded access):  {$sql_3->row['CODICE_PROT']}</p>
										<p>In riferimento alla richiesta di cui all'oggetto, si trasmette il parere del Comitato Etico Regionale per la Sperimentazione Clinica della Toscana - sezione {$area_vasta} riunitosi in data <b>{$sql_1->row['RIUNIONE_CE_DT']}.</b></p>
										<p>Si ricorda che l’avvio del trattamento da parte del Medico richiedente è subordinato a:<br>
											<ul>
												<li>notifica all’Autorità Competente (AIFA).</li>
											</ul>
										</p>
										<p><i>IN CASO DI PARERE FAVOREVOLE</i><br> 
										Il Comitato si riserva la facoltà di monitorare l’andamento del trattamento autorizzato.
										</p>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='right'>
  									<br><br>
										<p><b>Il Responsabile Segreteria Tecnico Scientifica</b></p>
										<p><b>_____________________________</b></p>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='center'>
										<p><b>Il Comitato Etico<br>
											in osservanza alle legislazioni vigenti in materia di<br> 
											uso terapeutico di medicinale sottoposto a sperimentazione clinica, <br>
											con particolare rifermento al Decreto del Ministero della Salute 8 Maggio 2003 <br>
											ha esaminato la richiesta di di autorizzazione all’uso terapeutico di </b><br>
										</p>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='center'>
										<p>Farmaco/i: {$farmaci}</p>
								</td>
							</tr>
							<tr>
  								<td colspan='3' align='left'>
									<p>Medico Richiedente: ..............................................</p>
									<p>UO: ...........................................</p>
									<p>Identificazione pazienti: ...........................................</p>
								</td>
  							</tr>
								<tr>
  								<td align='center' colspan='3'>
  									<p><b>Avendo valutato la seguente documentazione nella seduta del {$sql_ver->row['RIUNIONE_CE_DT']}</b></p>
  									<p>DOCUMENTAZIONE GENERALE
  										{$html_doc_gen}
  									</p>
  									<p>DOCUMENTAZIONE CENTRO-SPECIFICA
  										{$html_doc_loc}
  									</p>
  								</td>
  							</tr>
								<tr>
  								<td colspan='3' align='left'>																
										<p>Data di arrivo della documentazione completa: {$sql_ver->row['RICEZI_DT']}</p>
									</td>
								</tr>
								<tr>
  								<td colspan='3' align='center'>																
										<p><b>Ha espresso il seguente parere:<br>
											PARERE {$html_parere}<br></b>
										</p>
									</td>
								</tr>
								<tr>
									<td colspan='3' align='left'>		
										<p>{$rilievi_generali}</p>
										<p><b>Numero registro pareri del Comitato Etico:</b> {$sql_ver->row['DELIB_NUM']}</p>
  								</td>
  							</tr>
								<tr>
  								<td align='left' colspan='3'>
  									<p>
  										<b>Elenco componenti del CE presenti alla discussione e votanti che hanno dichiarato assenza di conflitti di interessi di tipo diretto o indiretto:</b><br/>
  										{$html_membri_approv}<br/>
  										<b>Elenco componenti del CE presenti non votanti:</b><br/>
										i sottoindicati componenti del Comitato dichiarano di astenersi dal pronunciarsi sul trattamento richiesto, poiché sussiste un conflitto di interessi di tipo diretto e/o indiretto.<br/>
  										{$html_membri_astenuti}<br/>
  										<!--b>Componenti del Comitato Etico assenti:</b><br/>
  										{$html_membri_approv_np}<br/>
  										{$html_membri_esterni}<br/-->
  										<br><b>Sussistenza numero legale (n. $count_vot su $tot_presenti)</b>
  									<p/>
  								</td>
  							</tr>
  							
  							<tr>
  								<td align='left' colspan='3'>
  									<p>
									{$disp_aifa}
  									</p>
  									<p>
											Si ricorda che è obbligo del Medico richiedente:
											<ul>
												<li>fare riferimento alla Farmacia Ospedaliera/altro per rendere disponibile il farmaco secondo le modalità predisposte dall’Azienda Sanitaria presso cui opera il Medico richiedente;</li>
												<li>notificare al Comitato Etico eventuali sospette reazioni avverse gravi ed inattese (SUSAR) ed i rapporti periodici di sicurezza (DSUR).</li>
											</ul>
  									</p>
  								</td>
  							</tr>
  							<!--tr>
									<td colspan='3' align='right'>
										<b>Firma Presidente</b><br/><br/>
										_____________________________
									</td>
							</tr-->
							<tr>
								<td cols='1' valign='top'>
									<p align='left'><br/><br/>
										......................., il {$sql_1->row['DATA_SED_DT']}
									</p>
								</td>
								<td colspan='2' align='right'>
									<b>Il Presidente</b><br/><br/>
										_____________________________
								</td>
							</tr>
							</table>
						";
						
			//LUIGI lettera uso terapeutico di dispositivo medico
			else if ($this->dettaglio['TIPO_SPER']==9)
			$lettera_default="<style>
													td {
												    font-size: 20px;
												    padding: 20px;
													} 
												</style>
												<table width='90%' cellspacing='0' cellpadding='0' border='0' align='center'>
													<tr>
														<td align='center' colspan='3'>
															<p>
																<b>Comitato Etico Regionale per la Sperimentazione Clinica della Regione Toscana<br></b>
																Sezione: {$area_vasta} <br>
											Segreteria Tecnico Scientifica ubicata c/o: {$ubicato} <br>
											Telefono: {$telefono}<br>
											E-mail: {$email}<br>
										</p>
									</td>
									<hr>
								</tr>
  							<tr>
  								<td colspan='3' align='left'>
										Prot n {$sql_1->row['PROTOCOLLO']}<br><br>
											{$li}, il {$sql_1->row['PROTOCOLLO_DT']}<br>
									</td>
								</tr>
								<tr>
									<td colspan='3' align='right'>
  									<i><b>Al Medico richiedente:</b></i><br><br>		
  									<i><b>e p.c.<br> al Direttore Generale della struttura di afferenza del Medico Richiedente<br>
									all’impresa produttrice che ha dichiarato la disponibilità alla fornitura del/i famaco/i</b></i> <br><br>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='left'>																
										<p><b>Oggetto:</b> Comunicazione del parere relativo alla richiesta di autorizzazione all'uso compassionevole di dispositivo/i medico/i privo/i di marcatura CE per la destinazione d'uso richiesta.<br>
										<p>In riferimento alla richiesta di cui all'oggetto, si trasmette il parere del Comitato Etico Regionale per la Sperimentazione Clinica della Toscana - sezione {$area_vasta} riunitosi in data <b>{$sql_1->row['RIUNIONE_CE_DT']}.</b></p>
										<p>Si ricorda che l’avvio del trattamento da parte del Promotore è subordinato a:<br>
											<ul>
												<li>richiesta di autorizzazione all'uso di dispositivo medico privo di marcatura CE redatta su carta intestata della Struttura Sanitaria alla Direzione Generale dei Dispositivi Medici e del servizio Farmaceutico (DGDMF) - Ufficio 6 - Sperimentazione clinica dei dispositivi medici.</li>
											</ul>
										</p>
										<p><i>IN CASO DI PARERE FAVOREVOLE</i><br> 
										Il Comitato ritiene necessario ricevere un follow-up clinico post-operatorio sugli esiti del paziente, data la natura sperimentale della procedura e la mancanza di marcatura CE del Dispositivo Medico. 
										Si ricorda di segnalare eventuali  incidenti ed aventi avversi allo scrivente ed al Ministero della Salute.
										</p>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='right'>
  									<br><br>
										<p><b>Il Responsabile Segreteria Tecnico Scientifica</b></p>
										<p><b>_____________________________</b></p>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='center'>
										<p><b>Il Comitato Etico<br>
											in osservanza alle legislazioni vigenti in materia di<br> 
											uso compassionevole di dispositivo/i medico/i privo/i di marcatura CE<br>
											ha esaminato la richiesta di di autorizzazione all’uso terapeutico di </b><br>
										</p>
  								</td>
  							</tr>
  							<tr>
  								<td colspan='3' align='center'>
										<p>Dispositivo/i: {$dispositivi}</p>
								</td>
							</tr>
							<tr>
  								<td colspan='3' align='left'>
									<p>Medico Richiedente: ..............................................</p>
									<p>UO: ...........................................</p>
									<p>Identificazione pazienti: ...........................................</p>
								</td>
  							</tr>
								<tr>
  								<td align='center' colspan='3'>
  									<p><b>Avendo valutato la seguente documentazione nella seduta del {$sql_ver->row['RIUNIONE_CE_DT']}</b></p>
  									<p>DOCUMENTAZIONE GENERALE
  										{$html_doc_gen}
  									</p>
  									<p>DOCUMENTAZIONE CENTRO-SPECIFICA
  										{$html_doc_loc}
  									</p>
  								</td>
  							</tr>
								<tr>
  								<td colspan='3' align='left'>																
										<p>Data di arrivo della documentazione completa: {$sql_ver->row['RICEZI_DT']}</p>
									</td>
								</tr>
								<tr>
  								<td colspan='3' align='center'>																
										<p><b>Ha espresso il seguente parere:<br>
											PARERE {$html_parere}<br></b>
										</p>
									</td>
								</tr>
								<tr>
									<td colspan='3' align='left'>		
										<p>{$rilievi_generali}</p>
										<p><b>Numero registro pareri del Comitato Etico:</b> {$sql_ver->row['DELIB_NUM']}</p>
  								</td>
  							</tr>
								<tr>
  								<td align='left' colspan='3'>
  									<p>
  										<b>Elenco componenti del CE presenti alla discussione e votanti che hanno dichiarato assenza di conflitti di interessi di tipo diretto o indiretto:</b><br/>
  										{$html_membri_approv}<br/>
  										<b>Elenco componenti del CE presenti non votanti:</b><br/>
										i sottoindicati componenti del Comitato dichiarano di astenersi dal pronunciarsi sul trattamento richiesto, poiché sussiste un conflitto di interessi di tipo diretto e/o indiretto.<br/>
  										{$html_membri_astenuti}<br/>
  										<!--b>Componenti del Comitato Etico assenti:</b><br/>
  										{$html_membri_approv_np}<br/>
  										{$html_membri_esterni}<br/-->
  										<br><b>Sussistenza numero legale (n. $count_vot su $tot_presenti)</b>
  									<p/>
  								</td>
  							</tr>
  							
  							<tr>
  								<td align='left' colspan='3'>
  									<p>
									{$disp_aifa}
  									</p>
  									<p>
											Si ricorda che è obbligo del Medico richiedente:
											<ul>
												<li>fare riferimento alla Farmacia Ospedaliera/altro per rendere disponibile il farmaco secondo le modalità predisposte dall’Azienda Sanitaria presso cui opera il Medico richiedente;</li>
												<li>notificare al Comitato Etico eventuali incidenti e/o mancati incidenti.</li>
											</ul>
  									</p>
  								</td>
  							</tr>
  							<!--tr>
									<td colspan='3' align='right'>
										<b>Firma Presidente</b><br/><br/>
										_____________________________
									</td>
							</tr-->
							<tr>
								<td cols='1' valign='top'>
									<p align='left'><br/><br/>
										......................., il {$sql_1->row['DATA_SED_DT']}
									</p>
								</td>
								<td colspan='2' align='right'>
									<b>Il Presidente</b><br/><br/>
										_____________________________
								</td>
							</tr>
							</table>
						";
			
			//LUIGI LETTERA DINAMICA
			else $lettera_default="<style>
								td {
							    font-size: 20px;
							    padding: 20px;
								} 
							</style>
							<table width='90%' cellspacing='0' cellpadding='0' border='0' align='center'>
								<tr>
									<td align='center' colspan='3'>
										<p>
											<b>Comitato Etico Regionale per la Sperimentazione Clinica della Regione Toscana<br></b>
											Sezione: {$area_vasta} <br>
											Segreteria Tecnico Scientifica ubicata c/o: {$ubicato} <br>
																Telefono: {$telefono}<br>
											E-mail: {$email}<br>
															</p>
														</td>
														<hr>
													</tr>
  												<tr>
  													<td colspan='3' align='left'>
															Prot n {$sql_1->row['PROTOCOLLO']}<br><br>
																{$li}, il {$sql_1->row['PROTOCOLLO_DT']}<br>
														</td>
													</tr>
													<tr>
														<td colspan='3' align='right'>
  														<i><b>Al promotore</b></i> {$sql_3->row['DESCR_SPONSOR']}<br><br>
  														$info_cro		
  									<i><b>Allo sperimentatore Principale locale</b></i> {$sql_4->row['D_PRINC_INV']} <!-- {$sql_4->row['D_UNITA_OP']} - {$sql_4->row['D_CENTRO']}--><br><br>
  									<i><b>e p.c. al Direttore Generale della struttura di afferenza dello Sperimentatore Principale locale</b></i> <!--{$sql_4->row['DIR_UO']}  {$sql_4->row['D_UNITA_OP']} - {$sql_4->row['D_CENTRO']}--><br><br>
  													</td>
  												</tr>
  												<tr>
  													<td colspan='3' align='left'>																
										<p><b>Oggetto:</b> Comunicazione del parere relativo alla richiesta di approvazione alla conduzione $intestazione <br>
										<p>\"{$sql_3->row['TITOLO_PROT']}\"</p>
															<p>Codice Protocollo: {$sql_3->row['CODICE_PROT']}</p>
															<p>Eudract (se applicabile): {$sql_3->row['EUDRACT_NUM']}</p>
										<p>In riferimento alla richiesta di cui all'oggetto, si trasmette il parere del Comitato Etico Regionale per la Sperimentazione Clinica della Toscana - sezione {$area_vasta} riunitosi in data <b>{$sql_1->row['RIUNIONE_CE_DT']}.</b></p>
										<p>Si ricorda che l'avvio {$intestazione2} da parte del Promotore è subordinato a:<br>
																<ul>
												{$subordinato}
												<li>stipula della convenzione economica (se applicabile)</li>
												<li>rilascio della disposizione autorizzativa della Direzione Generale dell'Azienda sanitaria.</li>
																</ul>
															</p>
										<p><i>IN CASO DI PARERE FAVOREVOLE</i><br> 
										Il Comitato si riserva la facoltà di monitorare nel corso del suo svolgimento, in accordo alle disposizioni normative vigenti, {$studio_sper}.
										</p>
  													</td>
  												</tr>
  												<tr>
  													<td colspan='3' align='right'>
  														<br><br>
										<p><b>Il Responsabile Segreteria Tecnico Scientifica</b></p>
															<p><b>_____________________________</b></p>
  													</td>
  												</tr>
  												<tr>
  													<td colspan='3' align='center'>
															<p><b>Il Comitato Etico<br>
																in osservanza alle legislazioni vigenti in materia di<br> 
											{$studio_sper2}<br>
											ha esaminato la richiesta di parere relativa allo studio</b><br>
															</p>
  													</td>
  												</tr>
  												<tr>
  								<td colspan='3' align='center'>
										<p>\"{$sql_3->row['TITOLO_PROT']}\"</p>
								</td>
							</tr>
							<tr>
  													<td colspan='3' align='left'>
															<p>Codice Protocollo: {$sql_3->row['CODICE_PROT']}</p>
															<p>Eudract (se applicabile): {$sql_3->row['EUDRACT_NUM']}</p>
														</td>
  												</tr>
													<tr>
  								<td align='center' colspan='3'>
  									<p><b>Avendo valutato la seguente documentazione nella seduta del {$sql_ver->row['RIUNIONE_CE_DT']}</b></p>
  									<p>DOCUMENTAZIONE GENERALE
  															{$html_doc_gen}
  														</p>
  									<p>DOCUMENTAZIONE CENTRO-SPECIFICA
  															{$html_doc_loc}
  														</p>
  													</td>
  												</tr>
													<tr>
  													<td colspan='3' align='left'>																
										<p>Data di arrivo della documentazione completa: {$sql_ver->row['RICEZI_DT']}</p>
														</td>
													</tr>
													<tr>
  													<td colspan='3' align='center'>																
										<p><b>Ha espresso il seguente parere:<br>
											PARERE {$html_parere}<br></b>
															</p>
														</td>
													</tr>
													<tr>
														<td colspan='3' align='left'>		
										<p>{$rilievi_generali}</p>
															<p><b>Numero registro pareri del Comitato Etico:</b> {$sql_ver->row['DELIB_NUM']}</p>
  													</td>
  												</tr>
													<tr>
  													<td align='left' colspan='3'>
  														<p>
  															<b>Elenco componenti del CE presenti alla discussione e votanti che hanno dichiarato assenza di conflitti di interessi di tipo diretto o indiretto:</b><br/>
  															{$html_membri_approv}<br/>
  										<b>Elenco componenti del CE presenti non votanti:</b><br/>
										i sottoindicati componenti del Comitato dichiarano di astenersi dal pronunciarsi sullo studio, poiché sussiste un conflitto di interessi di tipo diretto e/o indiretto.<br/>
  															{$html_membri_astenuti}<br/>
  															<!--b>Componenti del Comitato Etico assenti:</b><br/>
  										{$html_membri_approv_np}<br/>
  										{$html_membri_esterni}<br/-->
  										<br><b>Sussistenza numero legale (n. $count_vot su $tot_presenti)</b>
  														<p/>
  													</td>
  												</tr>
  												
  												<tr>
  													<td align='left' colspan='3'>
  														<p>
									{$disp_aifa}
  														</p>
  														<p>
											Si ricorda che &egrave; obbligo notificare al Comitato Etico:
																<ul>
												<li>data di arruolamento del primo paziente;</li>
																	<li>stato di avanzamento dello studio, con cadenza semestrale e/o annuale, corredato da una relazione scritta;</li>
												{$SUSAR}
												<li>fine del periodo di arruolamento; </li>
												<li>data di conclusione dello studio studio a livello locale ed a livello globale;</li>
												<li>risultati dello studio, entro un anno dalla conclusione della stessa.</li>
																</ul>
																Il Proponente deve ottemperare alle disposizioni legislative vigenti e riferire immediatamente al Comitato relativamente a:
																<ul>
												<li>deviazioni dal protocollo, anche quando queste si rendano necessarie per eliminare i rischi immediati per i partecipanti</li>
												<li>modifiche al protocollo, che non potranno essere messe in atto senza che il Comitato abbia rilasciato parere favorevole ad uno specifico emendamento, eccetto quando ciò sia necessario per eliminare i rischi immediati per i partecipanti o quando le modifiche riguardino esclusivamente aspetti logistici o amministrativi dello studio.</li>
												{$SUSAR2}
											</ul>
  														</p>
  													</td>
  												</tr>
  							<!--tr>
														<td colspan='3' align='right'>
															<b>Firma Presidente</b><br/><br/>
															_____________________________
														</td>
							</tr-->
							<tr>
														<td cols='1' valign='top'>
															<p align='left'><br/><br/>
										......................., il {$sql_1->row['DATA_SED_DT']}
															</p>
														</td>
								<td colspan='2' align='right'>
									<b>Il Presidente</b><br/><br/>
										_____________________________
														</td>
							</tr>
												</table>
											";
				
			$lettera_default=str_replace("-9944", "Non applicabile", $lettera_default);
			if ($_GET ['lettera'] == 'default') $lettera_parere=$lettera_default;
			else {
				$sql_query = "select lettera from ce_lettera_parere where id_stud={$_GET['ID_STUD']} and visitnum=4 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and esam=1 and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if ($sql->row ['LETTERA']) {$lettera_parere=$sql->row ['LETTERA']; }
					else $lettera_parere=$lettera_default;
			}
			
			include_once ("FCKeditor/fckeditor.php");
			
			$fckeditor = new FCKeditor ( "content" );
//			$fckeditor->ToolbarSet = 'Basic';

//			$dir="{$_SERVER['DOCUMENT_ROOT']}/gendocs";
//			$file = "/odg.html";
//			$letter= file_get_contents($dir.$file);
			
			$fckeditor->Value = $lettera_parere;
			$fckeditor->Height = '1100';
			
			$this->body.= "
			<form  name=\"edit\"  method=\"POST\"  id=\"edit\" >
			<input type=\"hidden\" name=\"lettera\" value=\"salva\">
			<input type=\"hidden\" name=\"VISITNUM_PROGR\" value=\"{$_GET['VISITNUM_PROGR']}\">
			<input type=\"hidden\" name=\"PROGR\" value=\"{$_GET['PROGR']}\">
			<input type=\"hidden\" name=\"ID_STUD\" value=\"{$_GET['ID_STUD']}\">
			<p style=\"font-size:18px\" align=center><b>Lettera di Parere: <br> $azienda_ente</b></p>
			<br>";
			
			$this->body.= "<fieldset style='border-color:#077f7f'>".$fckeditor->CreateHtml ()."</fieldset>";
			
			//$this->body.= "<p>
			//<input type='button' value='Chiudi senza salvare' onclick=\"self.close();\">
			//<input type='button' value='Torna al template predefinito' onclick='location.href=\"index.php?mod_lettera=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&VISITNUM={$_GET['VISITNUM']}&PROGR={$_GET['PROGR']}&lettera=default\"'>
			//<input type='submit' value='Salva'>
			
			$this->body.= "<p>
			<button class='btn btn-undo' type='button' onclick=\"self.close();\"><i class='fa fa-close bigger-110'></i>Chiudi senza salvare</button>
			<button class='btn btn-purple' type='button' onclick='location.href=\"index.php?mod_lettera=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&VISITNUM={$_GET['VISITNUM']}&PROGR={$_GET['PROGR']}&lettera=default\"'><i class='fa fa-refresh bigger-110'></i> Torna al template predefinito</button>
			<button class='btn btn-warning' type='submit' onclick=\"submit\"><i class='fa fa-floppy-o bigger-110'></i>Salva</button>
			
			<div style='float:center; text-align:center;'>
			<a href=\"#\" onclick=\"document.edit.lettera.value='pdf';document.edit.submit();\"><img src=\"images/pdf.png\"></img><br>Genera il file pdf</a>
			</div>
			</p></form><br><br>";
		
//			}
			// }
			// else{
				// $body="<html><head></head><body><font size=3px><b>Attenzione! E' possibile generare la lettera solo dopo l'invio definitivo della scheda di parere</b></font></body></html>";
				// $this->body=$body;
			// }
			
		}else{
			$sql_query = "select lettera from ce_lettera_parere where id_stud={$_GET['ID_STUD']} and visitnum=4 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and esam=1 and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if($this->getProfilo($this->user->userid)=="REG") $this->body.= "
				<fieldset>{$sql->row ['LETTERA']}</fieldset>
				";
				else $this->body.= "
				<fieldset></fieldset>
				";
				
		}		
			
	}	
		
	#GENERAZIONE LETTERA DI PARERE EMENDAMENTO
	if ($_GET ['mod_lettera_eme'] == 'yes') {
		if ($this->session_vars ['USER_TIP'] == "DE"){
			#controllo se il parere all'emendamento e' inviato
			$sql_query_co = "select * from ce_coordinate where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$_GET['VISITNUM_PROGR']} and esam=3 and progr={$_GET['PROGR']}";
			$sql_co = new query ( $this->conn );
			$sql_co->set_sql ( $sql_query_co );
			$sql_co->exec ();
			$sql_co->get_row ();
			
			//Luigi: controllo disabilitato
			//if($sql_co->row['FINE']){
			
			$query_image = "select * from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}'";
			$sql_image=new query($this->conn);
			$sql_image->exec($query_image);
			$sql_image->get_row();
			if ($sql_image->row['ID_CE']==1) {$area_vasta="AREA VASTA SUD EST"; $ubicato="Farmacia Ospedaliera AOUS - Viale Bracci, 16 - 53100 Siena"; $telefono="0577-586358"; $li="Siena"; $email="c.etico@ao-siena.toscana.it";}
			if ($sql_image->row['ID_CE']==2) {$area_vasta="AREA VASTA NORD OVEST"; $ubicato="Stabilimento di Santa Chiara - Via Roma, 67 - 56126 Pisa"; $telefono="050/996392-247-287"; $li="Pisa"; $email="direzione.uslnordovest@postacert.toscana.it";}
			if ($sql_image->row['ID_CE']==3) {$area_vasta="AREA VASTA CENTRO"; $ubicato="Nuovo Ingresso Careggi (NIC) - Largo Brambilla, 3 - 50134 Firenze"; $telefono="055-7947396"; $li="Firenze"; $email="segrcesf@unifi.it";}
			if ($sql_image->row['ID_CE']==4) {$area_vasta="COMITATO ETICO PEDIATRICO"; $ubicato="Meyer - Viale Pieraccini, 28 - 50139 Firenze"; $telefono="055-56621"; $li="Firenze"; $email="comitato.etico@meyer.it";}
			//if ($sql_image->row['ID_CE']==5) {$image_logo="ospvicenza.png";    $intestazione="DELLA PROVINCIA DI VICENZA";}
			//if ($sql_image->row['ID_CE']==6) {$image_logo="ospvenezia.jpg";    $intestazione="DELLA PROVINCIA DI VENEZIA E IRCSS SAN CAMILLO";}
			
			
			if ($_POST ['lettera'] == 'salva') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$sql_insert_storico = "insert into s_ce_lettera_parere_eme select '{$this->user->userid}', sysdate, storico_id.nextval, t.* from ce_lettera_parere_eme t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_insert_storico );
				$sql->ins_upd ();
				$sql_delete = "delete from ce_lettera_parere_eme t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql->set_sql ( $sql_delete );
				$sql->ins_upd ();
				$values ['ID_STUD'] = $this->pk_service;
				$values ['VISITNUM'] = '20';
				$values ['VISITNUM_PROGR'] = $_POST ['VISITNUM_PROGR'];
				$values ['ESAM'] = '3';
				$values ['PROGR'] = $_POST ['PROGR'];
				$values ['USERID_INS'] = $this->user->userid;
				$values ['INSDT'] = "sysdate";
				$values ['LETTERA'] = $_POST ['content'];
				$pk = '';
				print_r ($values);
				$sql->insert ( $values, "ce_lettera_parere_eme", $pk );
				$this->conn->commit ();
				header("location:index.php?mod_lettera_eme=yes&VISITNUM={$_GET['VISITNUM']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&PROGR={$_GET['PROGR']}&ID_STUD={$_GET['ID_STUD']}");
				die();
			}
			
			if ($_POST ['lettera'] == 'pdf') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$filetxt=$_POST ['content'];
				//echo $filetxt;
				//die();
				$filename = "Parere_EME_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.html";
				$filename_pdf = "Parere_EME_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.pdf";
				$path = $_SERVER ['PATH_TRANSLATED'];
				$images_path = str_replace ( "index.php", "../gendocs/", $path );
				$path = str_replace ( "index.php", "temp_html/", $path );
				$file_html = $path . $filename;
				$html_handle = fopen ( $file_html, "w" );
				$filetxt = str_replace ( "/gendocs/", $images_path, $filetxt );
				$filetxt = str_replace ( "style=\"display:\"", "", $filetxt );
				fwrite ( $html_handle, $filetxt );
				
				$wk=new WKPDF();
				$wk->set_page_size("A4"); #formato pagina 
				//$wk->set_toc(true); #aggiunge sommario
				$wk->set_title("Test1"); #aggiugne titolo
				$wk->pageNumber(true); #aggiunge numerazione alle pagine
				$wk->render("{$path}/{$filename}");
				$wk->output(WKPDF::$PDF_DOWNLOAD, $filename_pdf);
				
				//$htmldoc="/http/local/bin/htmldoc_rw";
				//system ( "$htmldoc -t pdf14 --fontsize 10 --no-title --size A4 --charset iso-8859-15 --browserwidth 1024 --footer .1. --header .t. --headfootsize 8 --headfootfont Times-Italic--bottom 10mm --top 6mm --left 10mm --right 10mm --path /amministrazione/schede_utente --webpage {$path}/{$filename}> {$path}/{$filename_pdf}" );
				//die ( "<html><head><meta http-equiv=\"refresh\" content=\"0;url=temp_html/{$filename_pdf}\"></head><body>Generazione PDF in corso</body></html>" );
				//die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=temp_html/{$filename_pdf}\"></head></html>" );
			}

			#GC 10/11/2014# Mostro i PI e UO dei centri selezionati nella scheda "Dati Emendamento"
			$sql_query_dati_eme = "select * from ce_emendamenti where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$_GET['VISITNUM_PROGR']} and esam=1 and progr=1";
			if($in['DEBUG']==1) echo $sql_query_dati_eme;
			$sql_dati_eme = new query ( $this->conn );
			$sql_dati_eme->set_sql ( $sql_query_dati_eme );
			$sql_dati_eme->exec ();
			$sql_dati_eme->get_row ();
			//echo ($sql_dati_eme->row['STRUTTURE']);
			$centri_sel_eme = explode ( "|", $sql_dati_eme->row['STRUTTURE']);
			//print_r ($centri_sel_eme);
			
//			$info_centro="";
//			for($count_strutt=0;$count_strutt<count($centri_sel_eme);$count_strutt++){
//				$progr_centro=$centri_sel_eme[$count_strutt];
//				if($progr_centro){
//					
//					$dipartimento_ko=$info_dipartimento=$istituto_ko=$info_istituto=$unita_operativa_ko=$info_unita_operativa=$info_princ_inv="";
//					
//					$sql_query_7 = "select * from ce_centrilocali where id_stud={$_GET['ID_STUD']} and visitnum='0' and visitnum_progr='0' and esam='10' and progr={$progr_centro}";
//					//echo $sql_query_7."<br>";
//					$sql_7 = new query ( $this->conn );
//					$sql_7->set_sql ( $sql_query_7 );
//					$sql_7->exec ();
//					$sql_7->get_row ();
//					
//					#Escludo i DIPARTIMENTI Non Applicabile/Non disponibile
//					$dipartimento_ko=preg_match('/-99/',$sql_7->row['DIPARTIMENTO']);
//					if(!$dipartimento_ko){
//					$info_dipartimento="<p style='font-family: Times New Roman; text-align: justify; line-height:25px;'>Chiar.mo Prof. {$sql_7->row['DIR_DIPARTIMENTO']}<br/>
//		  												Direttore {$sql_7->row['D_DIPARTIMENTO']}</p>";
//																}
//					
//					#Escludo gli ISTITUTI Non Applicabile/Non disponibile
//					$istituto_ko=preg_match('/-99/',$sql_7->row['ISTITUTO']);
//					if(!$istituto_ko){
//					$info_istituto="<p style='font-family: Times New Roman; text-align: justify; line-height:25px;'>Chiar.mo Prof. {$sql_7->row['DIR_ISTITUTO']}<br/>
//													Direttore {$sql_7->row['D_ISTITUTO']}</p>";
//													 }
//					
//					#Escludo le UNITA' OPERATIVE Non Applicabile/Non disponibile
//					$unita_operativa_ko=preg_match('/-99/',$sql_7->row['UNITA_OP']);
//					if(!$unita_operativa_ko){
//					$info_unita_operativa="<p style='font-family: Times New Roman; text-align: justify; line-height:25px;'>Chiar.mo Prof. {$sql_7->row['DIR_UO']}<br/>
//		  												   Direttore U.O. {$sql_7->row['D_UNITA_OP']}</p>";
//		  												   }
//		  		
//		  		$info_princ_inv="<p style='font-family: Times New Roman; text-align: justify; line-height:25px;'>
//  												 Chiar.mo Prof. {$sql_7->row['D_PRINC_INV']}<br/>
//  												 U.O. {$sql_7->row['D_UNITA_OP']}</p>";									   
//		  												   
//		  		//$info_centro.=$info_dipartimento.$info_istituto.$info_unita_operativa.$info_princ_inv."<br><br>";
//		  		$info_centro.=$info_princ_inv;			
//		  		$tutti_pi.=$sql_7->row['D_PRINC_INV'].",";
//	  			}
//				}
//			$tutti_pi = rtrim($tutti_pi,",");
			
			#dati dell'istruttoria emendamento
			$sql_query_0 = "select * from ce_eme_reginvio where id_stud={$_GET['ID_STUD']} and visitnum_progr={$_GET['VISITNUM_PROGR']} and progr={$_GET['PROGR']}";
			$sql_0 = new query ( $this->conn );
			$sql_0->set_sql ( $sql_query_0 );
			$sql_0->exec ();
			$sql_0->get_row ();
			
			#dati della valutazione emendamento
			$sql_query_1 = "select v.*,to_char(v.riunione_ce_dt,'DD/MM/YYYY') as data_sed_dt from ce_eme_valutazione v where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$_GET['VISITNUM_PROGR']} and esam=3 and progr={$_GET['PROGR']}";
			$sql_1 = new query ( $this->conn );
			$sql_1->set_sql ( $sql_query_1 );
			$sql_1->exec ();
			$sql_1->get_row ();
	
			#documentazione emendamento
			$lista_allegata_eme="";
			//$vett_doc_eme=explode("|",$sql_1->row['DOCS_VALUTATI_EME']);
			$sql_query_doc_eme = "select * from ce_docum_eme where id_stud={$_GET['ID_STUD']} and visitnum_progr={$_GET['VISITNUM_PROGR']}";
			$sql_doc_eme = new query ( $this->conn );
			$sql_doc_eme->set_sql ( $sql_query_doc_eme );
			$sql_doc_eme->exec ();
			while($sql_doc_eme->get_row ()){
				//if(in_array($sql_doc_eme->row['PROGR'],$vett_doc_eme)){
					$doc_eme_altro='';
					if($sql_doc_eme->row['DOC_EME_ALTRO']) $doc_eme_altro=" - ".$sql_doc_eme->row['DOC_EME_ALTRO'];
					if($sql_doc_eme->row['D_DOC_EME']=='Altro') $html_doc_eme.="<b><li>".$sql_doc_eme->row['DOC_EME_ALTRO']."</b>&nbsp;<small>(versione <i>".$sql_doc_eme->row['DOC_VERS']."</i> del <i>".$sql_doc_eme->row['DOC_DT']."</i>)</small></li></b>";
					else $html_doc_eme.="<b><li>".$sql_doc_eme->row['D_DOC_EME'].$doc_eme_altro."</b>&nbsp;<small>(versione <i>".$sql_doc_eme->row['DOC_VERS']."</i> del <i>".$sql_doc_eme->row['DOC_DT']."</i>)</small></li></b>";
				//}
			}
			
			if($html_doc_eme) $lista_allegata_eme=":";
			else $lista_allegata_eme=" (vedi lista allegata)";
			
			$documenti_eme=
			"<p style='font-family: Times New Roman; text-align: justify; font-style: italic;'>
  		 	Il Comitato Etico ha preso atto e approvato la seguente documentazione{$lista_allegata_eme}
  				{$html_doc_eme}
  		 </p>";
			
			#Studio approvato
			if($sql_1->row['RIS_DELIB']==1) {//$parere_ce="(SPER.SENZA PRESCRIZIONI = Parere A)";
																			 $html_parere="PARERE FAVOREVOLE";
																			 #GC 10/11/2014# Secondo me non ?pplicabile
																			 //$testo_parere_3="Si richiede che questo Comitato Etico venga informato dell'inizio della sperimentazione, del suo svolgimento con una relazione annuale e della sua conclusione o eventuale interruzione. Inoltre, dovr&agrave; essere informato di ogni successivo emendamento al protocollo e degli eventi avversi, seri e inattesi, insorti nel corso dello studio, che potrebbero influire sulla sicurezza dei soggetti o sul proseguimento dello studio. In difetto delle suddette relazioni l'efficacia dell'approvazione del protocollo deve intendersi sospesa a tutti gli effetti.";
																			 $testo_parere_3="";
																			 }
			#Studio non approvato
			if($sql_1->row['RIS_DELIB']==2) {//$parere_ce="D = PARERE NON FAVOREVOLE";
																			 $html_parere="PARERE NON FAVOREVOLE";
																			 $testo_parere="<i><b><u>motivazioni del rifiuto:</u></b></i>";
																			 }
			#Studio sospeso
			if($sql_1->row['RIS_DELIB']==10) {//$parere_ce="SPERIMENTAZIONE - SOSPENSIVO <br/><br/> C (da utilizzare per modifiche al protocollo/costi/indagini di sicurezza ecc)";
																			 $html_parere="PARERE SOSPENSIVO";
																			 $testo_parere="<i><b><u>Il Comitato Etico ha rilevato le seguenti criticit&agrave;:</u></b></i>";
																			 $testo_parere_2="L'emendamento potr&agrave; essere attuato nella ricerca clinica in oggetto solo non appena si sar&agrave; ottemperato alle suddette prescrizioni che, pertanto, dovranno essere preventivamente ripresentate e approvate da questo Comitato.";
																			 }
			#Emendamento solo notificato
			if($sql_1->row['RIS_DELIB']==9) {
																			 $html_parere="PARERE NOTIFICATO";
																			 //$testo_parere="<i><b><u>lo sperimentatore per la prossima riunione del Comitato Etico prevista per il giorno ../../....  alle ore ..:.., nella sala riunioni n&deg;410 secondo piano Ex Collegio Ioanneum affinch&egrave; possa le seguenti criticit&agrave;:</u></b></i>";
																			 $testo_parere="";
																			 //$testo_parere_2="Il protocollo potr&agrave; essere attuato nella ricerca clinica in oggetto solo non appena si sar&agrave; ottemperato alle suddette prescrizioni che, pertanto, dovranno essere preventivamente ripresentate e approvate da questo Comitato.";
																			 $testo_parere_2="";
																			 }
			#Emendamento approvato a condizione(4)
			#Emendamento approvato con commento(5)
			if($sql_1->row['RIS_DELIB']==4 || $sql_1->row['RIS_DELIB']==5) { //$parere_ce="SPER. CON PRESCRIZ. <br/><br/> B (da utilizzare se vengono richieste modifiche sulla scheda informativa)";
																			 $html_parere="PARERE FAVOREVOLE";
																			 $testo_parere="<i><b><u>con le seguenti prescrizioni:</u></b></i>";
																			 //$testo_parere_2="<u>Non sar&agrave; necessario aspettare la seduta successiva del ../../.... al C.E. ma sar&agrave; sufficiente far pervenire la documentazione modificata secondo quanto richiesto, prima dell'inizio effettivo dello studio, contrassegnando la nuova versione della scheda informativa/modulo di consenso con una nuova data di elaborazione ed evidenziando le modifiche richieste per avere una presa d'atto finale.  Le correzioni sono di carattere materiale e non ostano il parere positivo del Comitato Etico.</u>";
																			 $testo_parere_3="Si richiede che questo Comitato Etico venga informato dell'inizio della sperimentazione, del suo svolgimento con una relazione annuale e della sua conclusione o eventuale interruzione. Inoltre, dovr&agrave; essere informato di ogni successivo emendamento al protocollo e degli eventi avversi, seri e inattesi, insorti nel corso dello studio, che potrebbero influire sulla sicurezza dei soggetti o sul proseguimento dello studio. In difetto delle suddette relazioni l'efficacia dell'approvazione del protocollo deve intendersi sospesa a tutti gli effetti.";
																			 }
			#Diniego/sospensione AIFA
			if($sql_1->row['RIS_DELIB']==11) {
																			 $html_parere="SOSPENSIONE AIFA";
																			 $testo_parere="";
																			 $testo_parere_2="";
																			 }
			#Presa d'atto
			if($sql_1->row['RIS_DELIB']==12) {
																			 $html_parere="PARERE PRESA D'ATTO";
																			 $testo_parere="";
																			 $testo_parere_2="";
																			 }
			
			#COMPONENTI
			$vett_membri_approv=explode("|",$sql_1->row['MEMBRI_APPROV']);
			$sql_query_2 = "select * from ana_utenti_2 a, utenti u where a.userid=u.userid and u.abilitato=1 and a.id_ce={$this->getIdCe($this->user->userid)} and a.profilo='CMP' and a.subprofilo is null order by cognome";
			$sql_2 = new query ( $this->conn );
			$sql_2->set_sql ( $sql_query_2 );
			$sql_2->exec ();
			$count_vot=0;
			while($sql_2->get_row()){
				#PRESENTI
				if(in_array($sql_2->row['USERID'],$vett_membri_approv)){
					$count_vot++;
					$html_membri_approv.="<b>".$sql_2->row['QUALIFICA']." ".$sql_2->row['NOME']." ".strtoupper($sql_2->row['COGNOME'])."</b>".", <i>".$sql_2->row['RUOLO']."</i><br/>";
				}
				#ASSENTI
				else{
					$html_membri_approv_np.="<b>".$sql_2->row['QUALIFICA']." ".$sql_2->row['NOME']." ".strtoupper($sql_2->row['COGNOME'])."</b>".", <i>".$sql_2->row['RUOLO']."</i><br/>";
				}
			}
			 
			#MEMBRI ESTERNI
			$vett_membri_esterni=explode("|",$sql_1->row['MEMBRI_ESTERNI']);
			$sql_query_6 = "select * from ana_utenti_2 a, utenti u where a.userid=u.userid and u.abilitato=1 and a.id_ce={$this->getIdCe($this->user->userid)} and a.profilo='CMP' and (a.subprofilo='EXT' or a.subprofilo='SPE') order by cognome";
			$sql_6 = new query ( $this->conn );
			$sql_6->set_sql ( $sql_query_6 );
			$sql_6->exec ();
			while($sql_6->get_row()){
				if(in_array($sql_6->row['USERID'],$vett_membri_esterni)){
					$membri_esterni.="<b>".$sql_6->row['QUALIFICA']." ".$sql_6->row['NOME']." ".strtoupper($sql_6->row['COGNOME'])."</b>".", <i>".$sql_6->row['RUOLO']."</i><br/>";
				}
			}
			if($membri_esterni)
				$html_membri_esterni="<b>In relazione allo studio erano inoltre presenti alla discussione i seguenti esperti esterni:</b><br/>".$membri_esterni;
			 
			#MEMBRI ASTENUTI
			$vett_membri_astenuti=explode("|",$sql_1->row['MEMBRI_ASTENUTI']);
			$sql_query_ma = "select * from ana_utenti_2 a, utenti u where a.userid=u.userid and u.abilitato=1 and a.id_ce={$this->getIdCe($this->user->userid)} and a.profilo='CMP' and a.subprofilo is null order by cognome";
			$sql_ma = new query ( $this->conn );
			$sql_ma->set_sql ( $sql_query_ma );
			$sql_ma->exec ();
			$count_ma=0;
			while($sql_ma->get_row()){
				if(in_array($sql_ma->row['USERID'],$vett_membri_astenuti)){
					$count_ma++;
					$html_membri_astenuti.="<b>".$sql_ma->row['QUALIFICA']." ".$sql_ma->row['NOME']." ".strtoupper($sql_ma->row['COGNOME'])."</b>".", <i>".$sql_ma->row['RUOLO']."</i><br/>";
				}
			}
			$tot_presenti=$count_vot+$count_ma;

			$corpo1="<p style='font-family: Times New Roman; text-align: center; font-weight: bold;'>
			  			 	ESPRIME PARERE {$html_parere}
			  			 </p>";
			
			$rilievi_generali="<p style='font-family: Times New Roman; text-align: justify;'>
  											 	{$testo_parere}&nbsp;{$sql_1->row['OBIETTIVO']}
  											 </p>";

  		$text_1="<p style='font-family: Times New Roman; text-align: center; font-weight: bold; font-style: italic; text-decoration: underline;'>
  						 	Riunione del {$sql_1->row['RIUNIONE_CE_DT']}
  						 </p>";
			
			$gcp="<p style='font-family: Times New Roman; text-align: justify;'>
							Si dichiara che questo Comitato &egrave; organizzato ed opera nel rispetto delle norme di buona pratica clinica (GCP-ICH) e degli adempimenti previsti dall'allegato I al Decreto Ministeriale 18.3.1998: &quot;Linee Guida per l'Istituzione ed il funzionamento dei Comitati Etici&quot;.
						</p>";
			
			#dati minimi studio
			$sql_query_3 = "select * from ce_info_studio where id_stud={$_GET['ID_STUD']}";
			$sql_3 = new query ( $this->conn );
			$sql_3->set_sql ( $sql_query_3 );
			$sql_3->exec ();
			$sql_3->get_row ();
			
			#dati minimi centro
			$sql_query_4 = "select * from ce_centrilocali where id_stud={$_GET['ID_STUD']} and PROGR={$_GET['PROGR']}";
			$sql_4 = new query ( $this->conn );
			$sql_4->set_sql ( $sql_query_4 );
			$sql_4->exec ();
			$sql_4->get_row ();	
			
			#dati minimi centro
			if (isset($sql_4->row['CENTRO'])){
			$sql_query_nrc = "select * from ce_veneto_nucleo where id_str={$sql_4->row['CENTRO']}";
			$sql_nrc = new query ( $this->conn );
			$sql_nrc->set_sql ( $sql_query_nrc );
			$sql_nrc->exec ();
			$sql_nrc->get_row ();	
			}
			
			#dati verificadoc
			$sql_query_ver = "select * from ce_reginvio where id_stud={$_GET['ID_STUD']} and VISITNUM_PROGR={$_GET['PROGR']}-1 and progr = 1";
			$sql_ver = new query ( $this->conn );
			$sql_ver->set_sql ( $sql_query_ver );
			$sql_ver->exec ();
			$sql_ver->get_row ();
			
			#dati della seduta
			$sql_query_sed = "select to_char(data_sed_dt,'DD/MM/YYYY') as data_sed_dt from GSE_REGISTRAZIONE 
				WHERE
				id_sed=
				(
				select link_odg from ce_valutazione 
				where id_stud={$_GET['ID_STUD']} 
				and visitnum=4 
				and visitnum_progr={$_GET['VISITNUM_PROGR']} 
				and esam=1 
				and progr={$_GET['PROGR']}
				)";
			$sql_sed = new query ( $this->conn );
			$sql_sed->set_sql ( $sql_query_sed );
			$sql_sed->exec ();
			$sql_sed->get_row ();
			
			#documentazione generale
			$vett_doc_gen=explode("|",$sql_1->row['DOCS_VALUTATI_GEN']);
			
			$sql_query_doc = "select * from ce_documentazione where id_stud={$_GET['ID_STUD']}";
			$sql_doc = new query ( $this->conn );
			$sql_doc->set_sql ( $sql_query_doc );
			$sql_doc->exec ();
			while($sql_doc->get_row ()){
				if(in_array($sql_doc->row['PROGR'],$vett_doc_gen)){
					$doc_gen_altro=$descr_agg_gen='';
					if($sql_doc->row['DOC_GEN_ALTRO']) $doc_gen_altro=" - ".$sql_doc->row['DOC_GEN_ALTRO'];
					if($sql_doc->row['DESCR_AGG']) $descr_agg_gen=" - ".$sql_doc->row['DESCR_AGG'];
					if($sql_doc->row['D_DOC_GEN']=='Altro') $html_doc_gen.="<b><li>".$sql_doc->row['DOC_GEN_ALTRO'].$descr_agg_gen."</b>&nbsp;<small>(versione <i>".$sql_doc->row['DOC_VERS']."</i> del <i>".$sql_doc->row['DOC_DT']."</i>)</small></li></b>";
					else $html_doc_gen.="<b><li>".$sql_doc->row['D_DOC_GEN'].$doc_gen_altro.$descr_agg_gen."</b>&nbsp;<small>(versione <i>".$sql_doc->row['DOC_VERS']."</i> del <i>".$sql_doc->row['DOC_DT']."</i>)</small></li></b>";
				}
			}
			
			#documentazione centro-specifica
			
			#splitto sul |_VISITNUM_PROGR, ma resta un pipe finale...
			$progr_vp=$_GET['PROGR']-1;
			$split_var_doc_loc="|".$progr_vp."_";
			
			#...elimino l'ultimo pipe |
			$docs_loc=substr($sql_1->row['DOCS_VALUTATI_LOC'],0,strlen($sql_1->row['DOCS_VALUTATI_LOC'])-1);
			
			#esplodo i risultati nel vettore $vett_doc_loc
			$vett_doc_loc=explode($split_var_doc_loc,$docs_loc);
			
			$sql_query_5 = "select * from ce_docum_centro where id_stud={$_GET['ID_STUD']} and visitnum_progr={$_GET['PROGR']}-1";
			$sql_5 = new query ( $this->conn );
			$sql_5->set_sql ( $sql_query_5 );
			$sql_5->exec ();
			while($sql_5->get_row ()){
				if(in_array($sql_5->row['PROGR'],$vett_doc_loc)){
					$doc_loc_altro=$descr_agg_loc='';
					if($sql_5->row['DOC_LOC_ALTRO']) $doc_loc_altro=" - ".$sql_5->row['DOC_LOC_ALTRO'];
					if($sql_5->row['DESCR_AGG']) $descr_agg_loc=" - ".$sql_5->row['DESCR_AGG'];
					if($sql_5->row['D_DOC_LOC']=='Altro') $html_doc_loc.="<b><li>".$sql_5->row['DOC_LOC_ALTRO'].$descr_agg_loc."</b>&nbsp;<small>(versione <i>".$sql_5->row['DOC_VERS']."</i> del <i>".$sql_5->row['DOC_DT']."</i>)</small></li></b>";
					else $html_doc_loc.="<b><li>".$sql_5->row['D_DOC_LOC'].$doc_loc_altro.$descr_agg_loc."</b>&nbsp;<small>(versione <i>".$sql_5->row['DOC_VERS']."</i> del <i>".$sql_5->row['DOC_DT']."</i>)</small></li></b>";
				}
			}
			
			$oggetto_em="<p style='font-family: Times New Roman; text-align: justify;'>
  								 	Il Comitato Etico, riunito il {$sql_1->row['RIUNIONE_CE_DT']} per
  								 	esprimere il proprio parere etico motivato sull'emendamento sostanziale <b>{$sql_dati_eme->row['EMEND_CODE']}</b>
  								 	del {$sql_dati_eme->row['EMEND_DT']} presentato dal prof. <b>{$tutti_pi}</b>, relativo al Prot. <b>'{$sql_3->row['TITOLO_PROT']}'</b>
  								 </p>
  								 {$corpo1}
  								 {$rilievi_generali}
  								";
			
			$oggetto_em_farmacologico="";
			#GC 19-12-13# Per gli studi interventistici con farmaco (farmacologici) e con parere pos(1), pos a cond(4), pos con comm(5) e neg(2) il template va personalizzato
			if ($this->dettaglio['TIPO_SPER']==1 && ($sql_1->row['RIS_DELIB']==1 || $sql_1->row['RIS_DELIB']==2 || $sql_1->row['RIS_DELIB']==4 || $sql_1->row['RIS_DELIB']==5)) {
				$text_1="";
				$lista_membri_html="";
				if($sql_1->row['RIS_DELIB']!=2) $rilievi_generali="";
				$string_agg_interv="ha espresso <b>PARERE $html_parere</b>";
				if($sql_1->row['RIS_DELIB']==4) $string_agg_interv.=", con la seguente raccomandazione (vedi pagina .. sezione .. del parere allegato).";
				$oggetto_em="";
				$oggetto_em_farmacologico="
										 <p style='font-family: Times New Roman; text-align: justify; font-weight: bold;'>
										 	OGGETTO: Prot. {$sql_3->row['CODICE_PROT']} Emendamento sostanziale {$sql_dati_eme->row['EMEND_CODE']} - {$sql_dati_eme->row['SINTESI_EM']}
										 </p>
										 <p style='font-family: Times New Roman; text-align: justify;'>
  									 	Si comunica che il Comitato Etico, nella seduta del <b>{$sql_1->row['RIUNIONE_CE_DT']}</b>, dopo aver valutato l'Emendamento sostanziale
  									  relativo al Protocollo in oggetto, {$string_agg_interv} {$rilievi_generali}
  									 </p>
  									 {$documenti_eme}
  									 <p style='font-family: Times New Roman; text-align: justify;'>
										 	Si trasmette in allegato il parere espresso nelle modalit&agrave; previste dall'Agenzia Italiana del Farmaco secondo il Decreto Ministeriale 21/12/2007.
										 </p>";

				$gcp="";
				$corpo1="";
				$testo_parere_3="";
			}

				$text_agg="Si dichiara, altres&igrave, che questo Comitato si &egrave; ricostituito ai sensi del D.M. 8 febbraio 2013 e opera ai sensi della normativa vigente.";
			
			#GC 02-10-2014# Per gli studi interventistici con farmaco con i 3 pareri favorevoli (HDCE-784)
			if ($this->dettaglio['TIPO_SPER']==1 && ($sql_1->row['RIS_DELIB']==1 || $sql_1->row['RIS_DELIB']==4 || $sql_1->row['RIS_DELIB']==5)){
				$autorizzazione_aifa="Si ricorda che l'inizio dell'Emendamento &egrave; vincolato al ricevimento dell'autorizzazione da parte dell'Agenzia Italiana del Farmaco (AIFA).";
			}
			 
			 $info_sponsor="<p style='font-family: Times New Roman; text-align: justify; line-height:25px;'>Egr. Dott.............<br/>
			 									{$sql_3->row['DESCR_SPONSOR']}
			 								</p>";
			 
			 if($sql_3->row['DESCR_CRO'] != ''){
			 	$info_cro="<p style='font-family: Times New Roman; text-align: justify; line-height:25px;'>Egr. Dott.............<br/>
			 						{$sql_3->row['DESCR_CRO']}
			 						</p>";
			 																		}
				#GC 19-12-13# cambiato l'height da 2114 a 500
				$sql_4->row['D_CENTRO']=str_replace(" - CESC VERONA E ROVIGO","",$sql_4->row['D_CENTRO']);
				$sql_4->row['D_CENTRO']=str_replace(" - CESC Verona e Rovigo","",$sql_4->row['D_CENTRO']);
				if ($sql_4->row['D_UNITA_OP']=='') $sql_4->row['D_UNITA_OP']=$sql_4->row['UNITA_OPERATIVA_TEMP'];
				$sirammenta="<p>Si rammenta che per l'attivazione dell'emendamento &egrave; necessario attendere:<br><ol>
																	<li>L'autorizzazione da parte dell'Autorit&agrave; Competente AIFA </li>
																	<li>ove previsto, la ricezione dell'autorizzazione della propria Amministrazione</li>
																</ol></p>";
				if($sql_dati_eme->row['ALTRO']==2) $sirammenta="";
				$identificativo="Emendamento";
				if($sql_dati_eme->row['ALTRO']==2) $identificativo="Presa d'atto";
				$dicosa="dell'emendamento";
				if($sql_dati_eme->row['ALTRO']==2) $dicosa="di presa d'atto";
				$esaminato="L'EMENDAMENTO SOSTANZIALE";
				if($sql_dati_eme->row['ALTRO']==2) $esaminato="LA PRESA D'ATTO";
				
			//templates lettere di parere
			$lettera_default="<style>
													td {
												    font-size: 20px;
												    padding: 20px;
													} 
												</style>
												<table width='90%' cellspacing='0' cellpadding='0' border='0' align='center'>
													<tr>
														<td align='center' colspan='3'>
															<p>
																<b>Comitato Etico Regionale per la Sperimentazione Clinica della Regione Toscana<br></b>
																Sezione: {$area_vasta} <br>
																ubicato c/o: {$ubicato} <br>
																Telefono: {$telefono}<br>
																E-mail: {$email}<br>
															</p>
														</td>
														<hr>
													</tr>
  												<tr>
  													<td colspan='3' align='left'>
															Prot n {$sql_1->row['PROTOCOLLO']}<br><br>
															Firenze, il {$sql_1->row['PROTOCOLLO_DT']}<br>
														</td>
													</tr>
													<tr>
														<td colspan='3' align='right'>
  														<i><b>Al promotore</b></i> {$sql_3->row['DESCR_SPONSOR']}<br><br>
  														$info_cro		
  														<i><b>Allo sperimentatore locale</b></i> {$sql_4->row['D_PRINC_INV']} <!-- {$sql_4->row['D_UNITA_OP']} - {$sql_4->row['D_CENTRO']}--><br><br>
  														<i><b>Al Direttore Generale della struttura di afferenza del P.I.</b></i> <!--{$sql_4->row['DIR_UO']}  {$sql_4->row['D_UNITA_OP']} - {$sql_4->row['D_CENTRO']}--><br><br>
  													</td>
  												</tr>
  												<tr>
  													<td colspan='3' align='left'>																
															<p><b>Oggetto:</b> Comunicazione del <b>PARERE</b> relativo all'emendamento sostanziale dello studio<br>
															<p>Titolo: {$sql_3->row['TITOLO_PROT']}</p>
															<p>Codice Protocollo: {$sql_3->row['CODICE_PROT']}</p>
															<p>Eudract (se applicabile): {$sql_3->row['EUDRACT_NUM']}</p>
															<p>In riferimento alla richiesta di cui all'oggetto, si trasmette la decisione del Comitato Etico Regionale per la Sperimentazione Clinica della Toscana - sezione {$area_vasta} riunitosi in data <b>{$sql_1->row['RIUNIONE_CE_DT']}.</b></p>
															<p>Si ricorda che l'inizio della sperimentazione &egrave; subordinato alla ricezione dei seguenti documenti, da parte del promotore:<br>
																<ul>
																	<li>autorizzazione Autorit&agrave; Competente (AIFA e/o Ministero della Salute)</li>
																	<li>stipula della convenzione (se applicabile)</li>
																	<li>rilascio della disposizione autorizzativa da parte dell'amministrazione aziendale</li>
																</ul>
															</p>
															<p>Il Comitato si riserva la facolt&agrave; di verificare il corso della sperimentazione autorizzata.</p>
  													</td>
  												</tr>
  												<tr>
  													<td colspan='3' align='right'>
  														<br><br>
															<p><b>Firma del Responsabile della STS</b></p>
															<p><b>_____________________________</b></p>
  													</td>
  												</tr>
  												<tr>
  													<td colspan='3' align='center'>
															<p><b>Il Comitato Etico<br>
																in osservanza alle legislazioni vigenti in materia di<br> 
																sperimentazioni cliniche/studi osservazionali/uso compassionevole,<br>
																ha esaminato la richiesta in oggetto relativa allo studio</b><br>
															</p>
  													</td>
  												</tr>
  												<tr>
  													<td colspan='3' align='left'>
															<p>Titolo: {$sql_3->row['TITOLO_PROT']}</p>
															<p>Codice Protocollo: {$sql_3->row['CODICE_PROT']}</p>
															<p>Eudract (se applicabile): {$sql_3->row['EUDRACT_NUM']}</p>
														</td>
  												</tr>
													<tr>
  													<td align='left' colspan='3'>
  														<p><b>Valutando ed approvando la seguente documentazione:</b></p>
  														<p>Documentazione generale
  															{$html_doc_gen}
  														</p>
  														<p>Documentazione centro-specifica
  															{$html_doc_loc}
  														</p>
  													</td>
  												</tr>
													<tr>
  													<td colspan='3' align='left'>																
															<p>La data di <b>arrivo della documentazione completa</b> &egrave; risultata il {$sql_ver->row['RICEZI_DT']}</p>
														</td>
													</tr>
													<tr>
  													<td colspan='3' align='center'>																
															<p>HA ESPRESSO IL SEGUENTE PARERE:<br>
																<b>PARERE {$html_parere}<br>
																nella seduta del {$sql_1->row['RIUNIONE_CE_DT']}</b>
															</p>
														</td>
													</tr>
													<tr>
														<td colspan='3' align='left'>		
															<p><b>Note/richieste/motivazioni (del parere non favorevole):</b> {$rilievi_generali}</p>
															<p><b>Numero registro pareri del Comitato Etico:</b> {$sql_ver->row['DELIB_NUM']}</p>
  													</td>
  												</tr>
													<tr>
  													<td align='left' colspan='3'>
  														<p>
  															<b>Elenco componenti del CE presenti alla discussione e votanti che hanno dichiarato assenza di conflitti di interessi di tipo diretto o indiretto:</b><br/>
  															{$html_membri_approv}<br/>
  															<b>Elenco componenti del CE presenti ma astenuti:</b><br/>
  															{$html_membri_astenuti}<br/>
  															<!--b>Componenti del Comitato Etico assenti:</b><br/>
  															{$html_membri_approv_np}<br/-->
  															{$html_membri_esterni}<br>
  															<b>Sussistenza numero legale (n. $count_vot su $tot_presenti)</b>
  														<p/>
  														<p>I sopraindicati componenti del Comitato dichiarano di astenersi dal pronunciarsi su quelle sperimentazioni per le quali possa sussistere un conflitto di interessi di tipo diretto o indiretto.</p>
  													</td>
  												</tr>
  												
  												<tr>
  													<td align='left' colspan='3'>
  														<p>
	  														<i>(Solo per le sperimentazioni cliniche interventistiche farmacologiche inserire)</i><br>
	  														<b>Il presente parere viene rilasciato secondo le modalit&agrave; comunicate da AIFA con Disposizioni in vigore dal 1 ottobre 2014, <i>(specificare se tramite Osservatorio Nazionale sulla Sperimentazione clinica dei Medicinali o in modalit&agrave; cartacea)</i>.</b>
  														</p>
  														<p>
																Si ricorda con l'occasione che &egrave; obbligo notificare al Comitato Etico:
																<ul>
																	<li>data di inizio arruolamento del primo paziente (se applicabile);</li>
																	<li>stato di avanzamento dello studio, con cadenza semestrale e/o annuale, corredato da una relazione scritta;</li>
																	<li>eventuali sospette reazioni avverse gravi ed inattese (SUSAR) ed i rapporti periodici di sicurezza (DSUR);</li>
																	<li>fine del periodo di arruolamento dei soggetti per la sperimentazione clinica e la conclusione di quest'ultima; </li>
																	<li>data di conclusione dello studio presso il centro e in toto;</li>
																	<li>risultati della sperimentazione clinica entro un anno dalla conclusione della stessa.</li>
																</ul>
																Il Proponente deve ottemperare alle disposizioni legislative vigenti e riferire immediatamente al Comitato relativamente a:
																<ul>
																	<li>deviazioni dal protocollo, o modifiche allo stesso, che pertanto non potranno essere avviate senza che il Comitato abbia espresso, per iscritto, parere favorevole ad uno specifico emendamento, eccetto quando ci&ograve; sia necessario per eliminare i rischi immediati per i soggetti o quando le modifica riguardino esclusivamente aspetti logistici o amministrativi dello studio.</li>
																	<li>modifiche che aumentino il rischio per i soggetti e/o che incidano significativamente sulla conduzione dello studio (tutte le reazioni avverse serie; nuove informazioni che possano incidere negativamente sulla sicurezza dei soggetti o sulla conduzione dello studi).</li>
  														</p>
  													</td>
  												</tr>
  												<tr>
														<td colspan='3' align='right'>
															<b>Firma Presidente</b><br/><br/>
															_____________________________
														</td>
													</tr>
													<!--tr>
														<td cols='1' valign='top'>
															<p align='left'><br/><br/>
																Verona, {$sql_1->row['DATA_SED_DT']}
															</p>
														</td>
														<td colspan='2' align='left'>
															<p align='center'><br/><br/>
															D'Ordine del Presidente del Comitato Etico <br>delle Province di Verona e Rovigo<br>
															L'Ufficio di Segreteria <br>
															Dott.ssa Anna Fratucello
															</p>
														</td>
													</tr-->
												</table>
											";
			
			$lettera_default=str_replace("-9944", "Non applicabile", $lettera_default);
			if ($_GET ['lettera'] == 'default') $lettera_parere=$lettera_default;
			else {
				$sql_query = "select lettera from ce_lettera_parere_eme where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and esam=3 and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if ($sql->row ['LETTERA']) {$lettera_parere=$sql->row ['LETTERA']; }
					else $lettera_parere=$lettera_default;
			}
			
			include_once ("FCKeditor/fckeditor.php");
			
			$fckeditor = new FCKeditor ( "content" );
//			$fckeditor->ToolbarSet = 'Basic';

//			$dir="{$_SERVER['DOCUMENT_ROOT']}/gendocs";
//			$file = "/odg.html";
//			$letter= file_get_contents($dir.$file);
			
			$fckeditor->Value = $lettera_parere;
			$fckeditor->Height = '1100';
			
			$this->body.= "
			<form  name=\"edit\"  method=\"POST\"  id=\"edit\" >
			<input type=\"hidden\" name=\"lettera\" value=\"salva\">
			<input type=\"hidden\" name=\"VISITNUM_PROGR\" value=\"{$_GET['VISITNUM_PROGR']}\">
			<input type=\"hidden\" name=\"PROGR\" value=\"{$_GET['PROGR']}\">
			<input type=\"hidden\" name=\"ID_STUD\" value=\"{$_GET['ID_STUD']}\">
			<p style=\"font-size:18px; font-family: Times New Roman; text-align: center;\"><b>Lettera di Parere Emendamento: <br> $azienda_ente</b></p>
			<br>";
			
			$this->body.= "<fieldset style='border-color:#077f7f'>".$fckeditor->CreateHtml ()."</fieldset>";
			//$this->body.= "<p style=\"font-size:18px; font-family: Times New Roman; text-align: left;\">
			//<input type='button' value='Chiudi senza salvare' onclick=\"self.close();\">
			//<input type='button' value='Torna al template predefinito' onclick='location.href=\"index.php?mod_lettera_eme=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM={$_GET['VISITNUM']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&PROGR={$_GET['PROGR']}&lettera=default\"'>
			//<input type='submit' value='Salva'>
			
			$this->body.= "<p>
			<button class='btn btn-undo' type='button' onclick=\"self.close();\"><i class='fa fa-close bigger-110'></i>Chiudi senza salvare</button>
			<button class='btn btn-purple' type='button' onclick='location.href=\"index.php?mod_lettera_eme=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM={$_GET['VISITNUM']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&PROGR={$_GET['PROGR']}&lettera=default\"'><i class='fa fa-refresh bigger-110'></i> Torna al template predefinito</button>
			<button class='btn btn-warning' type='submit' onclick=\"submit\"><i class='fa fa-floppy-o bigger-110'></i>Salva</button>
			
			<div style='float:center; text-align:center;'>
			<a href=\"#\" onclick=\"document.edit.lettera.value='pdf';document.edit.submit();\"><img src=\"images/pdf.png\"></img><br>Genera il file pdf</a>
			</div>
			</p></form><br><br>";
		
			// }
			// else{
				// $body="<html><head></head><body><font size=3px><b>Attenzione! E' possibile generare la lettera solo dopo l'invio definitivo della scheda di parere</b></font></body></html>";
				// $this->body=$body;
			// }

		}else{
			$sql_query = "select lettera from ce_lettera_parere_eme where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if($this->getProfilo($this->user->userid)=="REG") $this->body.= "
				<fieldset>{$sql->row ['LETTERA']}</fieldset>
				";
				else $this->body.= "
				<fieldset></fieldset>
				";
				
		}		
		
	}
	
	#GENERAZIONE ISTRUTTORIA	
	if ($_GET ['mod_istruttoria_ts'] == 'yes') {
		if ($this->session_vars ['USER_TIP'] == "DE"){
			$esam=21;
			
			if ($_POST ['lettera'] == 'salva') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$sql_insert_storico = "insert into s_ce_lettera_istruttoria_ts select '{$this->user->userid}', sysdate, storico_id.nextval, t.* from ce_lettera_istruttoria_ts t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_insert_storico );
				$sql->ins_upd ();
				$sql_delete = "delete from ce_lettera_istruttoria_ts t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql->set_sql ( $sql_delete );
				$sql->ins_upd ();
				$values ['ID_STUD'] = $this->pk_service;
				$values ['VISITNUM'] = '2';
				$values ['VISITNUM_PROGR'] = $_POST ['VISITNUM_PROGR'];
				$values ['ESAM'] = $esam;
				$values ['PROGR'] = $_POST ['PROGR'];
				$values ['USERID_INS'] = $this->user->userid;
				$values ['INSDT'] = "sysdate";
				$values ['LETTERA'] = $_POST ['content'];
				$pk = '';
				print_r ($values);
				$sql->insert ( $values, "ce_lettera_istruttoria_ts", $pk );
				$this->conn->commit ();
				header("location:index.php?mod_istruttoria_ts=yes&VISITNUM={$_GET['VISITNUM']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&PROGR={$_GET['PROGR']}&ID_STUD={$_GET['ID_STUD']}");
				die();
			}
			if ($_POST ['lettera'] == 'pdf') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$filetxt=$_POST ['content'];
				//echo $filetxt;
				//die();
				$filename = "Istruttoria_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.html";
				$filename_pdf = "Istruttoria_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.pdf";
				$path = $_SERVER ['PATH_TRANSLATED'];
				$images_path = str_replace ( "index.php", "../gendocs/", $path );
				$path = str_replace ( "index.php", "temp_html/", $path );
				$file_html = $path . $filename;
				$html_handle = fopen ( $file_html, "w" );
				$filetxt = str_replace ( "/gendocs/", $images_path, $filetxt );
				$filetxt = str_replace ( "style=\"display:\"", "", $filetxt );
				fwrite ( $html_handle, $filetxt );
				$htmldoc="/http/local/bin/htmldoc_rw";
				system ( "$htmldoc -t pdf14 --fontsize 10 --no-title --size A4 --charset iso-8859-15 --browserwidth 1024 --footer .1. --header .t. --headfootsize 8 --headfootfont Times-Italic--bottom 10mm --top 6mm --left 10mm --right 10mm --path /amministrazione/schede_utente --webpage {$path}/{$filename}> {$path}/{$filename_pdf}" );
				die ( "<html><head><meta http-equiv=\"refresh\" content=\"0;url=temp_html/{$filename_pdf}\"></head><body>Generazione PDF in corso</body></html>" );
				die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=temp_html/{$filename_pdf}\"></head></html>" );
			}
			
			$datiUtente=$this->getDatiUtente2($this->user->userid);
			
			#Registrazione
			$query_reg = "select * from CE_REGISTRAZIONE where id_stud='{$this->pk_service}'";
			$sql_reg = new query ( $this->conn );
			$sql_reg->get_row ( $query_reg );
			
			#Riassunto studio
			$sql_query_rs = "select * from ce_info_studio where id_stud={$_GET['ID_STUD']}";
			$sql_rs = new query ( $this->conn );
			$sql_rs->get_row ( $sql_query_rs );
			
			if($sql_rs->row['ETA_PAZ']) $popolazione.="<li> {$sql_rs->row['D_ETA_PAZ']} </li>";
			if($sql_rs->row['ETA_VOL']) $popolazione.="<li> {$sql_rs->row['D_ETA_VOL']} </li>";
			if($sql_rs->row['ETA_INCA']) $popolazione.="<li> {$sql_rs->row['D_ETA_INCA']} </li>";
			
			$eta_popolazione="";
			for($i=1;$i<5;$i++){
				$da_select="D_ER".$i."_DA_SELECT";
				$da_spec="ER".$i."_DA_SPEC";
				$da="D_ER".$i."_DA";
				$a_select="D_ER".$i."_A_SELECT";
				$a_spec="ER".$i."_A_SPEC";
				$a="D_ER".$i."_A";
				if($sql_rs->row[$da_spec]){
					$eta_popolazione.="<li>".$sql_rs->row[$da_select]." ".$sql_rs->row[$da_spec]." ".$sql_rs->row[$da]." a ".$sql_rs->row[$a_select]." ".$sql_rs->row[$a_spec]." ".$sql_rs->row[$a]."</li>"; 
				}
			}
			
			#dati verificadoc
			$sql_query_ver = "select * from ce_reginvio where id_stud={$_GET['ID_STUD']} and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']} and progr = {$_GET['PROGR']}";
			$sql_ver = new query ( $this->conn );
			$sql_ver->get_row ( $sql_query_ver );
			
			#Documentazione generale
			$sql_query_dg = "select * from ce_documentazione where id_stud={$_GET['ID_STUD']} order by doc_dt";
			$sql_dg = new query ( $this->conn );
			$sql_dg->set_sql ( $sql_query_dg );
			$sql_dg->exec ();
			while($sql_dg->get_row ()){
				if($sql_dg->row['DOC_GEN']==4){
					$versione_prot=$sql_dg->row['DOC_VERS'];
					$data_prot=$sql_dg->row['DOC_DT'];
				}
			}
			
			$sql_query_l01 = "select * from CE_LOCALE01 where id_stud='{$this->pk_service}' and visitnum_progr={$_GET['VISITNUM_PROGR']}";
			$sql_ce_l01 = new query ( $this->conn );
			$sql_ce_l01->get_row ( $sql_query_l01 );
			
			#Istruttoria TS
			$sql_query_ts = "select * from ce_istruttoria_ts where id_stud={$_GET['ID_STUD']} and visitnum={$_GET['VISITNUM']} and visitnum_progr={$_GET['VISITNUM_PROGR']} and esam=$esam and progr={$_GET['PROGR']}";
			$sql_ts = new query($this->conn);
			$sql_ts->get_row( $sql_query_ts );
			
			#Disegno dello studio
			$disegno="";
			if($sql_rs->row['DS3'])	$disegno.="Studio controllato: {$sql_rs->row['D_DS3']}<br>";
			if($sql_rs->row['DS3']==1){
				$disegno.="Studio controllato vs:<ul>";
				if($sql_rs->row['CHECK_DS3_1']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_1']} </li>";
		    if($sql_rs->row['CHECK_DS3_2']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_2']} </li>";
		    if($sql_rs->row['CHECK_DS3_3']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_3']} </li>";
		    if($sql_rs->row['CHECK_DS3_4']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_4']} </li>";
		    if($sql_rs->row['CHECK_DS3_6']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_6']} </li>";
		    if($sql_rs->row['CHECK_DS3_7']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_7']} </li>";
		    if($sql_rs->row['CHECK_DS3_8']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_8']} </li>";
		    if($sql_rs->row['CHECK_DS3_9']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_9']} </li>";
		    if($sql_rs->row['CHECK_DS3_10']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_10']}</li>";
		    if($sql_rs->row['CHECK_DS3_11']) $disegno.="<li>{$sql_rs->row['D_CHECK_DS3_11']}</li>";
		    if($sql_rs->row['DS3']==1)
		    $disegno.="</ul>";
	    }

	    if($sql_rs->row['CTR_DS1']) $disegno.="<li>{$sql_rs->row['D_CTR_DS1']}</li>Rapporto di randomizzazione: {$sql_rs->row['SPEC_DS1']} </li>";
			if($sql_rs->row['CTR_DS2']) $disegno.="<li>{$sql_rs->row['D_CTR_DS2']} </li>";
			if($sql_rs->row['CTR_DS2A']) $disegno.="<li>{$sql_rs->row['D_CTR_DS2A']} </li>";
			if($sql_rs->row['CTR_DS2B']) $disegno.="<li>{$sql_rs->row['D_CTR_DS2B']} </li>";
			if($sql_rs->row['CTR_DS5']) $disegno.="<li>{$sql_rs->row['D_CTR_DS5']} </li>";
			if($sql_rs->row['CTR_DS2C']) $disegno.="<li>{$sql_rs->row['D_CTR_DS2C']} </li>
					Specificare: {$sql_rs->row['SPEC_DS2']} </li>";

	    if($sql_rs->row['TRASVE']) $disegno.="<li>{$sql_rs->row['D_TRASVE']}</li>";
			if($sql_rs->row['COORTE']) $disegno.="<li>{$sql_rs->row['D_COORTE']} </li>";
			if($sql_rs->row['CASOCO']) $disegno.="<li>{$sql_rs->row['D_CASOCO']} </li>";
			if($sql_rs->row['PROSP']) $disegno.="<li>{$sql_rs->row['D_PROSP']} </li>";
			if($sql_rs->row['RETRO']) $disegno.="<li>{$sql_rs->row['D_RETRO']} </li>";
			if($sql_rs->row['DISEGNO_ALTRO']) $disegno.="<li>{$sql_rs->row['D_DISEGNO_ALTRO']} </li>
					Specificare: {$sql_rs->row['ALTRO_SPEC']} </li>";
			
			$protocollo_clinico="";
			if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$protocollo_clinico="
					<br>
					<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
						<tr>
							<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
								PROTOCOLLO CLINICO
							</td>
						</tr>
						<tr>
							<td colspan='2'>
								<i>Il protocollo viene valutato con lo SPIRIT Statement.</i>
							</td>
						</tr>
						<tr>
							<td>
								Nel titolo dello studio &egrave; descritto il disegno dello studio, la popolazione, gli interventi, e se applicabile, l'acronimo del trial
							</td>
							<td>
								{$sql_ts->row['D_TITOLO']}
							</td>
						</tr>
						<tr>
							<td>
								Nel background e razionale:<br>
								&nbsp;&nbsp;a) E' descritto il quesito di ricerca e la giustificazione della conduzione del trial, incluso il riassunto degli studi clinici rilevanti (pubblicati e non pubblicati) e la valutazione dei benefici e dei rischi per ogni intervento.</li>
							</td>
							<td>
								{$sql_ts->row['D_BACKGROUND1']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;b) E' spiegata la scelta dei confronti.
							</td>
							<td>
								{$sql_ts->row['D_BACKGROUND2']}
							</td>
						</tr>
						<tr>
							<td>
								Sono specificati gli obiettivi o le ipotesi di ricerca
							</td>
							<td>
								{$sql_ts->row['D_BACKGROUND3']}
							</td>
						</tr>
						<tr>
							<td>
								E' descritto il disegno del trial includendo la tipologia (es. in doppio cieco, vs. placebo, a gruppi paralleli, fattoriale, crossover, singolo gruppo), il rapporto di allocazione e il contesto (es. superiorit&agrave;, equivalenza, non inferiorit&agrave;, esplorativo)
							</td>
							<td>
								{$sql_ts->row['D_DISEGNO2']}
							</td>
						</tr>
						<tr>
							<td>
								E' descritto il contesto nel quale sar&agrave; condotto lo studio (es. territorio, ospedale) e la lista dei paesi dove saranno raccolti i dati. E' fornita la lista dei siti in cui viene condotto lo studio, anche se presente in altri documenti.
							</td>
							<td>
								{$sql_ts->row['D_CONTESTO']}
							</td>
						</tr>
						<tr>
							<td>
								Sono definiti chiaramente i criteri di inclusione ed esclusione della popolazione partecipante allo studio. Se applicabile, sono indicati i criteri di eleggibilit&agrave; per i centri partecipanti allo studio e gli individui che eseguiranno gli interventi (es. chirurghi, psicoterapeutici).
							</td>
							<td>
								{$sql_ts->row['D_INC_ESC']}
							</td>
						</tr>
						<tr>
							<td>
								Gli interventi:<br>
								&nbsp;&nbsp;a) Sono sufficientemente dettagliati gli interventi per ogni gruppo di partecipanti, in modo da permettere la riproducibilit&agrave; dello studio, includendo modalit&agrave; e tempi in cui saranno somministrati gli interventi
							</td>
							<td>
								{$sql_ts->row['D_INTERVENTI']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;b) Sono ben definiti i criteri standard per sospendere o modificare l'allocazione degli interventi per un dato partecipante al trial (es. per ragioni di sicurezza come l'insorgenza di un danno in risposta ad un farmaco, e/o di efficacia del farmaco e/o dello stato di malattia come un miglioramento/peggioramento, e ritiro del consenso da parte del partecipante).
							</td>
							<td>
								{$sql_ts->row['D_STANDARD']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;c) Sono definite le strategie per migliorare l'aderenza (ossia se il comportamento del partecipante corrisponde a quello previsto dallo studio) ai protocolli di intervento e le procedura per monitorare l'aderenza (es. riconsegna del blister di farmaco, test di laboratorio).
							</td>
							<td>
								{$sql_ts->row['D_STRATEGIE']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;d) E' riportata la lista delle cure concomitanti rilevanti e degli interventi permessi o proibiti durante il trial.
							</td>
							<td>
								{$sql_ts->row['D_CURE']}
							</td>
						</tr>
						<tr>
							<td>
								Sono ben definiti gli esiti primari, secondari e gli altri esiti dello studio, comprese le specifiche variabili di misura (es. pressione sanguigna sistolica), le modalit&agrave; di analisi (es. cambiamento rispetto al basale, valore finale, tempo dell'evento), i metodi di aggregazione (es. mediana, proporzione) e il tempo in cui viene misurato ciascun esito. E' fornita la spiegazione della scelta degli esiti di efficacia e sicurezza da un punto di vista di rilevanza clinica.
							</td>
							<td>
								{$sql_ts->row['D_ESITI']}
							</td>
						</tr>
						<tr>
							<td>
								E' presente un chiaro e conciso diagramma schematico del processo di studio che dettagli la fase di pre-arruolamento, l'arruolamento, gli interventi (eventuali cross-over), le valutazioni e le visite per i partecipanti.
							</td>
							<td>
								{$sql_ts->row['D_DIAGRAMMA']}
							</td>
						</tr>
						<tr>
							<td>
								E' indicata la stima del numero dei partecipanti necessari per realizzare gli obiettivi dello studio e la modalit&agrave; con cui &egrave; stato determinato questo numero, includendo riferimenti clinici e statistici a supporto di qualsiasi calcolo sulla dimensione del campione.
							</td>
							<td>
								{$sql_ts->row['D_STIMA']}
							</td>
						</tr>
						<tr>
							<td>
								Sono indicate le strategie per promuovere l'arruolamento di un adeguato numero di partecipanti per raggiungere il target previsto nella dimensione del campione.
							</td>
							<td>
								{$sql_ts->row['D_STRATEGIE2']}
							</td>
						</tr>
						<tr>
							<td>
								E' descritto il metodo utilizzato per generare la sequenza di allocazione (es. numeri random generati dal computer), il rapporto di allocazione (1:1, 2:1, etc.) e la lista di qualsiasi fattore per la stratificazione (es. randomizzazione stratificata per et&agrave;, per centro in caso il trial sia multicentrico etc). Sono pianificate restrizioni (es. randomizzazione a blocchi) che impediscono agli sperimentatori di prevedere la sequenza di randomizzazione.
							</td>
							<td>
								{$sql_ts->row['D_RANDOM']}
							</td>
						</tr>
						<tr>
							<td>
								E' descritto il metodo usato per implementare la sequenza di allocazione (es. controllo telefonico centrale, buste opache, numerazione sequenziale, etc) e tutti gli step seguiti per mantenere nascosta la sequenza di allocazione sino all'assegnazione degli interventi.
							</td>
							<td>
								{$sql_ts->row['D_RANDOM_SECRET']}
							</td>
						</tr>
						<tr>
							<td>
								E' specificato il personale dello studio responsabile della generazione della sequenza di allocazione, dell'arruolamento dei partecipanti e della loro assegnazione a ciascun gruppo di intervento.
							</td>
							<td>
								{$sql_ts->row['D_PERSONALE']}
							</td>
						</tr>
						<tr>
							<td>
								Mascheramento (cecit&agrave;):<br>
								&nbsp;&nbsp;a) E' descritto il soggetto o il gruppo di soggetti che saranno in cieco dopo l'assegnazione all'intervento (es. i partecipanti al trial, i professionisti sanitari, i valutatori degli esiti, gli analisti dei dati) e la modalit&agrave; di ottenimento di questo requisito. 
							</td>
							<td>
								{$sql_ts->row['D_MASCHERAMENTO1']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;b) Se lo studio &egrave; in cieco, sono descritte chiaramente le circostanze in cui &egrave; permessa l'apertura del cieco e le procedure per rivelare l'intervento a cui &egrave; stato sottoposto il partecipante durante il trial
							</td>
							<td>
								{$sql_ts->row['D_MASCHERAMENTO2']}
							</td>
						</tr>
						<tr>
							<td>
								Metodi di raccolta dati<br>
								&nbsp;&nbsp;a) Sono indicati i metodi per la valutazione e la raccolta dell'esito, del basale, o altri dati del trial, includendo qualsiasi processo correlato a promuovere la qualit&agrave; dei dati (es. misurazioni doppie, formazione degli sperimentatori) e la descrizione degli strumenti di studio (ad esempio, questionari, test di laboratorio) con il loro relativo grado di affidabilit&agrave; e validit&agrave;, se noto. E' possibile trovare il riferimento ad altri documenti diversi dal protocollo in cui sono disponibili queste informazioni.
							</td>
							<td>
								{$sql_ts->row['D_RACCOLTA1']}
							</td>
						</tr>
						<tr>
							<td>
								Metodi di raccolta dati<br>
								&nbsp;&nbsp;b) Sono indicati i metodi per promuovere la partecipazione dei soggetti e la completezza del follow-up, incluso un elenco di tutti i dati di esito che dovrebbero essere raccolti per i partecipanti che interrompono o deviano dal protocollo di intervento.
							</td>
							<td>
								{$sql_ts->row['D_RACCOLTA2']}
							</td>
						</tr>
						<tr>
							<td>
								Gestione dei dati: sono documentati i metodi di immissione dei dati, i processi di codifica, le misure di sicurezza es. per prevenire accessi non autorizzati, e le modalit&agrave; di conservazione dei dati, inclusi eventuali processi correlati per promuovere la qualit&agrave; dei dati (ad esempio, doppio inserimento dei dati, range di controllo dei valori dei dati).
							</td>
							<td>
								{$sql_ts->row['D_GESTIONEDATI1']}
							</td>
						</tr>
						<tr>
							<td>
								Se queste informazioni non sono incluse nel protocollo, &egrave; riportato il riferimento alle procedure di gestione dei dati.
							</td>
							<td>
								{$sql_ts->row['D_GESTIONEDATI2']}
							</td>
						</tr>
						<tr>
							<td>
								Metodi statistici:<br>
								&nbsp;&nbsp;a) Sono indicati esplicitamente i metodi statistici utilizzati per l'analisi degli esiti primari e secondari. Se queste informazioni non sono incluse nel protocollo, &egrave; riportato il riferimento ai documenti  in cui pu&ograve; essere ritrovato il piano di analisi statistico.
							</td>
							<td>
								{$sql_ts->row['D_STATISTICA1']}
							</td>
						</tr>
						<tr>
							<td>
								Metodi statistici:<br>
								&nbsp;&nbsp;b) Sono indicati esplicitamente i metodi utilizzati per le analisi statistiche aggiuntive (es. analisi per sottogruppi e aggiustate).
							</td>
							<td>
								{$sql_ts->row['D_STATISTICA2']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;c) E' definita l'analisi della popolazione relativamente ai soggetti non aderenti al protocollo (esempio analisi Intention-To-Treat, modified Intention To Treat, o per protocol) e qualsiasi metodo statistico per trattare i dati mancanti (es. valutazioni multiple oggetto di successive analisi di sensitivit&agrave;).
							</td>
							<td>
								{$sql_ts->row['D_STATISTICA3']}
							</td>
						</tr>
						<tr>
							<td>
								Monitoraggio dei dati:<br>
								&nbsp;&nbsp;a) Se il trial prevede il controllo degli esiti durante lo studio da parte di un Comitato Indipendente di Monitoraggio dei Dati (IDMC), ne &egrave; indicata la composizione, una sintesi del suo ruolo e dei suoi rapporti con la struttura, una dichiarazione di indipendenza dallo sponsor e di conflitto di interesse, ed eventuali riferimenti documentali dove possono essere trovati altri dettagli, se non presente nel protocollo.
							</td>
							<td>
								{$sql_ts->row['D_MONITORAGGIO1']}
							</td>
						</tr>
						<tr>
							<td>
								In alternativa, se il trial non prevede un IDMC &egrave; riportata una spiegazione per il quale non &egrave; necessario.
							</td>
							<td>
								{$sql_ts->row['D_MONITORAGGIO2']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;b) Sono descritte le analisi intermedie e le regole di interruzione dello studio, incluso chi avr&agrave; accesso a questi risultati intermedi e chi prender&agrave; la decisione definitiva di terminare lo studio.
							</td>
							<td>
								{$sql_ts->row['D_MONITORAGGIO3']}
							</td>
						</tr>
						<tr>
							<td>
								Sicurezza:<br>
								sono descritte le procedure per la raccolta, la valutazione, la segnalazione e la gestione degli eventi avversi sia sollecitati che spontanei e di altri effetti indesiderati correlati alla partecipazione al trial.
							</td>
							<td>
								{$sql_ts->row['D_SICUREZZA']}
							</td>
						</tr>
						<tr>
							<td>
								Revisione (auditing):<br>
								&egrave; descritta la frequenza e le procedure periodiche di revisione dei processi e dei documenti presso i centri partecipanti al trial e se il processo &egrave; indipendente dagli sperimentatori e dallo sponsor.
							</td>
							<td>
								{$sql_ts->row['D_REVISIONE']}
							</td>
						</tr>
						<tr>
							<td>
								E' presente la dichiarazione di ottenimento dell'approvazione dello studio clinico da parte di un Comitato Etico/Institutional Review Board (REC/IRB) e le modalit&agrave; con cui viene richiesta la valutazione.
							</td>
							<td>
								{$sql_ts->row['D_DICH_APPR']}
							</td>
						</tr>
						<tr>
							<td>
								E' dichiarata e descritta la modalit&agrave; di comunicazione di modifiche sostanziali al protocollo (es. cambiamento dei criteri di eleggibilit&agrave;, analisi, outcome) alle parti coinvolte (promotore, partecipanti ai trial, comitato etico, etc).
							</td>
							<td>
								{$sql_ts->row['D_COMUNICAZIONE']}
							</td>
						</tr>
						<tr>
							<td>
								Consenso/assenso:<br>
								&nbsp;&nbsp;a)	E' indicato chi otterr&agrave; il consenso informato o l'assenso da parte di un potenziale partecipante al trial o di un tutore legale e come questo sar&agrave; ottenuto (dettagli del processo).
							</td>
							<td>
								{$sql_ts->row['D_CONSENSO1']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;b) Se applicabile, &egrave; indicato il processo di ottenimento di un consenso informato aggiuntivo per la raccolta e l'utilizzo dei dati dei partecipanti e dei campioni biologici in studi ancillari.
							</td>
							<td>
								{$sql_ts->row['D_CONSENSO2']}
							</td>
						</tr>
						<tr>
							<td>
								E' descritta la modalit&agrave; e lo strumento con cui il personale dello studio raccoglier&agrave;, condivider&agrave; e manterr&agrave; riservate le informazioni sui dati personali dei soggetti eleggibili, prima, durante e dopo il trial.
							</td>
							<td>
								{$sql_ts->row['D_INFO_RIS']}
							</td>
						</tr>
						<tr>
							<td>
								Sono indicati gli interessi finanziari o di altra natura degli sperimentatori per ciascun sito di studio.
							</td>
							<td>
								{$sql_ts->row['D_INTERESSI_FIN']}
							</td>
						</tr>
						<tr>
							<td>
								E' chiaro il personale che avr&agrave; accesso ai dati finali dello studio ed &egrave; indicata la presenza di un eventuale accordo contrattuale che limiter&agrave; l'accesso ai dati per gli sperimentatori.
							</td>
							<td>
								{$sql_ts->row['D_ACCORDO']}
							</td>
						</tr>
						<tr>
							<td>
								E' indicata la fornitura di cure ancillari e post studio ai partecipanti allo studio e la presenza di una polizza assicurativa per la copertura dei danni ai soggetti derivanti dalla partecipazione allo studio.
							</td>
							<td>
								{$sql_ts->row['D_FORNITURA']}
							</td>
						</tr>
						<tr>
							<td>
								Politiche di pubblicazione:<br>
								&nbsp;&nbsp;a) E' delineato un processo e un calendario riguardante la diffusione dei risultati dello studio da parte degli sperimentatori e dello sponsor ai partecipanti del trial, ai professionisti sanitari, al pubblico, e ad altri gruppi rilevanti, includendo qualsiasi restrizione alla pubblicazione
							</td>
							<td>
								{$sql_ts->row['D_PUBBLICAZIONE1']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;b) Sono indicati esplicitamente i contributi di ciascun autore (authorship) al disegno, alla conduzione, all'interpretazione ed al reporting dello studio clinico.
							</td>
							<td>
								{$sql_ts->row['D_PUBBLICAZIONE2']}
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;&nbsp;c) E' indicata la modalit&agrave; con cui vengono resi disponibili i dati dello studio al pubblico ed alle autorit&agrave; competenti e i codici statistici utilizzati.
							</td>
							<td>
								{$sql_ts->row['D_PUBBLICAZIONE3']}
							</td>
						</tr>
						<tr>
							<td>
								Campioni biologici:<br>
								Se applicabile, sono descritti dettagliatamente i metodi per raccogliere i campioni biologici, le modalit&agrave; di analisi (genetica, molecolare), di anonimizzazione dei dati confidenziali, il luogo e le modalit&agrave; di conservazione del materiale (es. biobanche) e la presenza di un Comitato Etico del luogo di deposito
							</td>
							<td>
								{$sql_ts->row['D_CAMPIONI_BIO1']}
							</td>
						</tr>
						<tr>
							<td>
								Sono descritti gli usi futuri del materiale conservato per altri studi
							</td>
							<td>
								{$sql_ts->row['D_CAMPIONI_BIO2']}
							</td>
						</tr>
						<tr>
							<td>
								E' usato il placebo quale gruppo di controllo e ne &egrave; giustificato l'uso
							</td>
							<td>
								{$sql_ts->row['D_PLACEBO']}
							</td>
						</tr>
						$sottostudio
						<tr>
							<td>
								L'analisi dei benefici &egrave; favorevole rispetto ai rischi prevedibili (chiaramente indicati)
							</td>
							<td>
								{$sql_ts->row['D_BENEFICI']}
							</td>
						</tr>
						$items
						$crf2
						
						<tr>
							<td>
								Il protocollo &egrave; conforme alle linee guida EMA in materia
							</td>
							<td>
								{$sql_ts->row['D_EMA1']}
							</td>
						</tr>
						<tr>
							<td>
								Se si al punto precedente, citare i riferimenti (testo libero):
							</td>
							<td>
								{$sql_ts->row['EMA2']}
							</td>
						</tr>
						
						
					</table>
				";
			}
			
			$crf2="";
			if($sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==3 || $sql_reg->row['TIPO_SPER']==7 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$crf2="
					<tr>
						<td>
							Le informazioni che si vogliono raccogliere sono chiare e conformi a quanto riportato nella scheda di raccolta dati (CRF)
						</td>
						<td>
							{$sql_ts->row['D_CRF2']}
						</td>
					</tr>
				";
			}
			
			$gcp="";
			if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$gcp="
				<tr>
					<td>
						Il protocollo &egrave; conforme alle GCP
					</td>
					<td>
						{$sql_ts->row['D_GCP']}
					</td>
				</tr>
				<tr>
					<td>
						Eventuali elementi critici riscontrati (testo libero):
					</td>
					<td>
						{$sql_ts->row['CRITICITA70']}
					</td>
				</tr>
				";
			}
			
			$intervento="<ol>";
			$confronto="<ol>";
			$query_farmaco = "select * from CE_FARMACO where id_stud='{$this->pk_service}' order by categoria asc";
			$sql_farmaco = new query ( $this->conn );
			$sql_farmaco->set_sql ( $query_farmaco );
			$sql_farmaco->exec ();
			while($sql_farmaco->get_row ()){
				#test
				if($sql_farmaco->row['CATEGORIA']==1){
					$intervento.="<li>";
					$intervento.="Categoria: <b>".$sql_farmaco->row['D_CATEGORIA']."</b><br/>";
					$intervento.="Schema terapeutico: <b>".$sql_farmaco->row['SCHEMA_TER']."</b><br/>";
					$intervento.="Natura principio attivo: <b>".$sql_farmaco->row['D_NATURA_PA']."</b><br/>";
					$intervento.="ATC: <b>".$sql_farmaco->row['ATC']." ".$sql_farmaco->row['D_ATC']."</b><br/>";
					$intervento.="Il farmaco &egrave; in commercio: <b>".$sql_farmaco->row['D_AUTO_ITA']."</b><br/>";
					$intervento.="Indicazione: <b>".$sql_farmaco->row['INDICAZIONE']."</b><br/>";
					$intervento.="Il farmaco &egrave; in commercio per l'indicazione in oggetto di studio all'estero: <b>".$sql_farmaco->row['D_AUTO_EST']."</b><br/>";
					$intervento.="Se si, in quali Paesi: <b>".$sql_farmaco->row['PAESI']."</b><br/>";
					$intervento.="Il farmaco &egrave; in commercio per altre indicazioni in Italia: <b>".$sql_farmaco->row['D_AUTO_ITAAI']."</b><br/>";
					$intervento.="Specialit&agrave; medicinale: <b>".$sql_farmaco->row['SPECIALITA']."</b><br/>";
					$intervento.="Codice AIC: <b>".$sql_farmaco->row['AIC']."</b><br/>";
					$intervento.="Confezione: <b>".$sql_farmaco->row['CONFEZIONE']."</b><br/>";
					$intervento.="Principio attivo: <b>".$sql_farmaco->row['PRINC_ATT']."</b><br/>";
					$intervento.="Note: <b>".$sql_farmaco->row['NOTE']."</b><br/>";
					$intervento.="Via di somministrazione: <b>".$sql_farmaco->row['D_VIA_SOMMIN']."</b><br/>";
					$intervento.="Forma farmaceutica: <b>".$sql_farmaco->row['FORMA_FARM']."</b><br/>";
					$intervento.="Il coinvolgimento della farmacia ospedaliera/territoriale &egrave; previsto per: <b>".$sql_farmaco->row['D_FARMACIA']."</b><br/>";
					if($sql_farmaco->row['FARMACIA']==2){
						$intervento.="Opzioni:<ul><b>";
						if($sql_farmaco->row['FAT'])  $intervento.="<li>".$sql_farmaco->row['D_FAT']."</li>";
						if($sql_farmaco->row['ALL'])  $intervento.="<li>".$sql_farmaco->row['D_ALLE']."</li>";
						if($sql_farmaco->row['RIC'])  $intervento.="<li>".$sql_farmaco->row['D_RIC']."</li>";
						if($sql_farmaco->row['CONF']) $intervento.="<li>".$sql_farmaco->row['D_CONF']."</li>";
						if($sql_farmaco->row['SMAL']) $intervento.="<li>".$sql_farmaco->row['D_SMAL']."</li>";
						$intervento.="</b></ul>";
					}
					if($sql_farmaco->row['FARMACIA']==3){
						$intervento.="Altro: <b>".$sql_farmaco->row['ALTRO_FARM']."<br/>";
					}
					
					$intervento.="<br/></li>";
				}
				
				#comparatore attivo
				if($sql_farmaco->row['CATEGORIA']==2 && $sql_farmaco->row['COMPARATORE_SEL']==1){
					$confronto.="<li>";
					$confronto.="Categoria: <b>".$sql_farmaco->row['D_CATEGORIA']."</b><br/>";
					$confronto.="Tipo di comparatore: <b>".$sql_farmaco->row['D_COMPARATORE_SEL']."</b><br/>";
					$confronto.="Schema terapeutico: <b>".$sql_farmaco->row['SCHEMA_TER']."</b><br/>";
					$confronto.="Natura principio attivo: <b>".$sql_farmaco->row['D_NATURA_PA']."</b><br/>";
					$confronto.="ATC: <b>".$sql_farmaco->row['ATC']." ".$sql_farmaco->row['D_ATC']."</b><br/>";
					$confronto.="Il farmaco &egrave; in commercio: <b>".$sql_farmaco->row['D_AUTO_ITA']."</b><br/>";
					$confronto.="Indicazione: <b>".$sql_farmaco->row['INDICAZIONE']."</b><br/>";
					$confronto.="Il farmaco &egrave; in commercio per l'indicazione in oggetto di studio all'estero: <b>".$sql_farmaco->row['D_AUTO_EST']."</b><br/>";
					$confronto.="Se si, in quali Paesi: <b>".$sql_farmaco->row['PAESI']."</b><br/>";
					$confronto.="Il farmaco &egrave; in commercio per altre indicazioni in Italia: <b>".$sql_farmaco->row['D_AUTO_ITAAI']."</b><br/>";
					$confronto.="Specialit&agrave; medicinale: <b>".$sql_farmaco->row['SPECIALITA']."</b><br/>";
					$confronto.="Codice AIC: <b>".$sql_farmaco->row['AIC']."</b><br/>";
					$confronto.="Confezione: <b>".$sql_farmaco->row['CONFEZIONE']."</b><br/>";
					$confronto.="Principio attivo: <b>".$sql_farmaco->row['PRINC_ATT']."</b><br/>";
					$confronto.="Note: <b>".$sql_farmaco->row['NOTE']."</b><br/>";
					$confronto.="Via di somministrazione: <b>".$sql_farmaco->row['D_VIA_SOMMIN']."</b><br/>";
					$confronto.="Forma farmaceutica: <b>".$sql_farmaco->row['FORMA_FARM']."</b><br/>";
					$confronto.="Il coinvolgimento della farmacia ospedaliera/territoriale &egrave; previsto per: <b>".$sql_farmaco->row['D_FARMACIA']."</b><br/>";
					if($sql_farmaco->row['FARMACIA']==2){
						$confronto.="Opzioni:<ul><b>";
						if($sql_farmaco->row['FAT'])  $confronto.="<li>".$sql_farmaco->row['D_FAT']."</li>";
						if($sql_farmaco->row['ALL'])  $confronto.="<li>".$sql_farmaco->row['D_ALLE']."</li>";
						if($sql_farmaco->row['RIC'])  $confronto.="<li>".$sql_farmaco->row['D_RIC']."</li>";
						if($sql_farmaco->row['CONF']) $confronto.="<li>".$sql_farmaco->row['D_CONF']."</li>";
						if($sql_farmaco->row['SMAL']) $confronto.="<li>".$sql_farmaco->row['D_SMAL']."</li>";
						$confronto.="</b></ul>";
					}
					if($sql_farmaco->row['FARMACIA']==3){
						$confronto.="Altro: <b>".$sql_farmaco->row['ALTRO_FARM']."<br/>";
					}
					
					$confronto.="<br/></li>";
				}
				
				#comparatore placebo
				if($sql_farmaco->row['CATEGORIA']==2 && $sql_farmaco->row['COMPARATORE_SEL']==2){
					$confronto.="<li>";
					$confronto.="Categoria: <b>".$sql_farmaco->row['D_CATEGORIA']."</b><br/>";
					$confronto.="Tipo di comparatore: <b>".$sql_farmaco->row['D_COMPARATORE_SEL']."</b><br/>";
					if($sql_farmaco->row['COMPARATORE_SEL']==2){
						$confronto.="Descrizione della motivazione dell'uso del placebo: <b>".$sql_farmaco->row['PLACE_DESCR']."</b><br/>";
						$confronto.="Per quali farmaci viene utilizzato: <b>".$sql_farmaco->row['PLACE_FARM']."</b><br/>";
						$confronto.="Add-On alla terapia standard: <b>".$sql_farmaco->row['PLACE_ADDON']."</b><br/>";
						$confronto.="Via di somministrazione: <b>".$sql_farmaco->row['D_VIA_SOMMIN']."</b><br/>";
						$confronto.="Forma farmaceutica: <b>".$sql_farmaco->row['FORMA_FARM']."</b><br/>";
					}
					
					$confronto.="<br/></li>";
				}
				
				
			}
			$intervento.="</ol>";
			$confronto.="<ol>";
			
			
			$doc_presentata="";
			$elementi_valutare="";
			$medicinale="";
			$sottostudio="";
			$items="";
			$investigators_brochure="";
			if($sql_reg->row['TIPO_SPER']==1){				
				$doc_presentata="
					<tr>
						<td>
							Modulo di domanda (CTA Form - Appendice 5) generata da OsSC (se applicabile), firmato e datato
						</td>
						<td>
							{$sql_ts->row['D_MODULO_CTA']}
						</td>
					</tr>
					<tr>
						<td>
							Lista documentazione conforme (con riferimento a date e versioni) alla lista di controllo presente nella CTA Form generata dal nuovo OsSC o alla lista Ia e Ib (in caso di modalit&agrave; transitoria)
						</td>
						<td>
							{$sql_ts->row['D_DOC_CONFORME']}
						</td>
					</tr>
				";
				
				$elementi_valutare="
					<tr>
						<td>
							La sperimentazione &egrave; parte di un Piano di Indagine Pediatrica (PIP)?
						</td>
						<td>
							{$sql_ts->row['D_PIP']}
						</td>
					</tr>
					<tr>
						<td>
							Se si al punto precedente, il protocollo &egrave; conforme al PIP?
						</td>
						<td>
							{$sql_ts->row['D_PIP2']}
						</td>
					</tr>
					<tr>
						<td>
							Esistono revisioni sistematiche e/o linee guida che sintetizzano le migliori evidenze disponibili (es. COCHRANE COLLABORATION, NICE, PUBMED, NATIONAL GUIDELINE CLEARINGHOUSE, GUIDELINES INTERNATIONAL NETWORK)
						</td>
						<td>
							{$sql_ts->row['D_REV_SIST']}
						</td>
					</tr>
					<tr>
						<td>
							Il trial &egrave; registrato in un database pubblico che permette libero accesso ai risultati della ricerca (CLINICALTRIALSREGISTER.EU*; CLINICALTRIAL.GOV) <b>*La registrazione &egrave; obbligatoria dal 21 Luglio 2014 (2012/C 302/03)</b>
						</td>
						<td>
							{$sql_ts->row['D_DB_PUB']}
						</td>
					</tr>
					<tr>
						<td>
							Eventuali elementi critici riscontrati o altre note (testo libero):
						</td>
						<td>
							{$sql_ts->row['CRITICITA']}
						</td>
					</tr>
				";
				
				$medicinale="
					<br>
					<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
						<tr>
							<td colspan='2' style='background-color: #C4FEFF;'>
								<b>DATI SUL MEDICINALE SPERIMENTALE</b> (Specificare Principio attivo):
							</td>
						</tr>
						<tr>
							<td>
								Specificare propriet&agrave; farmacologiche, forma farmaceutica e via di somministrazione:
							</td>
							<td>
								<!--TOSCANA-51 lasciare testo libero-->
							</td>
						</tr>
						<tr>
							<td>
								Specificare dose massima per somministrazione e posologia massima/die:
							</td>
							<td>
								<!--TOSCANA-51 lasciare testo libero-->
							</td>
						</tr>
						<tr>
							<td>
								Specificare la durata del trattamento: 
							</td>
							<td>
								<!--TOSCANA-51 lasciare testo libero-->
							</td>
						</tr>
						<tr>
							<td>
								Specificare le interazioni farmacologiche:
							</td>
							<td>
								<!--TOSCANA-51 lasciare testo libero-->
							</td>
						</tr>
						<tr>
							<td>
								Specificare i dati sulla sicurezza ed efficacia del farmaco sperimentale:
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Eventuali elementi critici riscontrati o altre osservazioni (testo libero):
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Si tratta di medicinale orfano per malattie rare (secondo il Regolamento (CE) n. 141/2000 del Parlamento europeo e del Consiglio)
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Il medicinale &egrave; destinato all'uso di malattie ultra-rare (ossia destinati a soggetti affetti da malattie gravi, debilitanti e spesso potenzialmente letali che colpiscono non pi&ugrave; di una persona su 50 000 nell'Unione)
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Le informazioni e i dati necessari a supportare la qualit&agrave; dell'IMP sono adeguati (vedi presenza IMPD o IMPD semplificato o RCP)
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Il promotore ha documentato che i prodotti in sperimentazione saranno preparati, gestiti e conservati nel rispetto delle Norme di Buona Fabbricazione (GMP) applicabili
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Esistono presupposti solidi e rilevanti che giustificano l'avvio dello studio (non applicabile per studi di fase I e II)
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Lo studio consentir&agrave; di acquisire maggiori informazioni sull'IMP, di migliorare le procedure profilattiche, diagnostiche e terapeutiche o la comprensione dell'eziologia e della patogenesi delle malattie
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								L'etichettatura &egrave; conforme alle normative vigenti (valutabile se il richiedente &egrave; centro coordinatore)
							</td>
							<td>
								
							</td>
						</tr>
						<tr>
							<td>
								Eventuali elementi critici riscontrati o altre osservazioni (testo libero):
							</td>
							<td>
								
							</td>
						</tr>
					</table>
				";
				
				$sottostudio="
					<tr>
						<td>
							E' presente un sottostudio (studio ancillare) di farmacogenetica/farmacogenomica
						</td>
						<td>
							{$sql_ts->row['D_ANCILLARE']}
						</td>
					</tr>
					";
					
				$items="
					<tr>
						<td>
							Eventuali elementi critici riscontrati nell'analisi degli items o altre osservazioni (testo libero):
						</td>
						<td>
							{$sql_ts->row['CRITICITA71']}
						</td>
					</tr>
				";
				
				$investigators_brochure="
					<br>
					<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
						<tr>
							<td colspan='2' style='background-color: #C4FEFF;'>
								<b>INVESTIGATOR'S BROCHURE</b>
							</td>
						</tr>
						<tr>
							<td>
								Il dossier dello sperimentatore risulta completo e adeguato
							</td>
							<td>
								{$sql_ts->row['D_DOSSIER1']}
							</td>
						</tr>

					</table>
				";
				
			}
			
			$aspetti_etici="";
			if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==5 || $sql_reg->row['TIPO_SPER']==6 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$aspetti_etici="
					<tr>
						<td>
							Il promotore e/o lo sperimentatore locale ha documentato con formale accettazione dello studio che lo stesso verr&agrave; condotto nel rispetto dei diritti fondamentali della dignit&agrave; e dei diritti umani in conformit&agrave; ai principi etici, che traggono la loro origine dalla Dichiarazione di Helsinki e dalla Convenzione di Oviedo nonch&eacute; da tutte le normative internazionali applicabili
						</td>
						<td>
							{$sql_ts->row['D_OVIEDO']}
						</td>
					</tr>
					<tr>
						<td>
							Il promotore dichiara il rispetto delle Good Clinical Practice nonch&eacute; delle disposizione normative applicabili
						</td>
						<td>
							{$sql_ts->row['D_NORMATIVE']}
						</td>
					</tr>
				";
			}
			$dolore="";
			if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==3 || $sql_reg->row['TIPO_SPER']==7 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$aspetti_etici.="
					<tr>
						<td>
							I rischi e gli inconvenienti prevedibili sono stati soppesati rispetto al vantaggio per il soggetto incluso nella sperimentazione e per altri pazienti attuali e futuri
						</td>
						<td>
							{$sql_ts->row['D_VAL_RISCHI']}
						</td>
					</tr>
					<tr>
						<td>
							I benefici previsti dalla sperimentazione, terapeutici e in materia di sanit&agrave; pubblica, ne giustifichino i rischi
						</td>
						<td>
							{$sql_ts->row['D_BENEFICI_RISCHI']}
						</td>
					</tr>					
				";
				
				$dolore="
					<tr>
						<td>
							Sono presenti misure per minimizzare il dolore, il disagio e la paura
						</td>
						<td>
							{$sql_ts->row['D_DOLORE']}
						</td>
					</tr>					
				";
			}
			$aspetti_etici.="
					<tr>
						<td>
							I diritti, la sicurezza e il benessere dei soggetti dello studio hanno costituito le considerazioni pi&ugrave; importanti e sono prevalsi sugli interessi della scienza e della societ&agrave;
						</td>
						<td>
							{$sql_ts->row['D_DIRITTI']}
						</td>
					</tr>
					<tr>
						<td>
							La ricerca su persone che non sono in grado di dare il loro consenso informato &egrave; giustificata
						</td>
						<td>
							{$sql_ts->row['D_RICERCA']}
						</td>
					</tr>
				";
				
			$aspetti_etici.=$dolore;
			
			$aspetti_etici.="
				<tr>
					<td>
						La ricerca su persone che non sono in grado di dare il loro consenso informato &egrave; giustificata
					</td>
					<td>
						{$sql_ts->row['CRITICITA4']}
					</td>
				</tr>
			";
			
			
			$info_soggetti="
				<tr>
					<td>
						Modulo di consenso informato, data e versione (approvate dal CE coordinatore, se applicabile):
					</td>
					<td>
						
					</td>
				</tr>
				<tr>
					<td>
						Se applicabile, i fogli informativi ed i moduli di assenso/consenso informato sono distinti per le diverse fasce di et&agrave; pediatrica
					</td>
					<td>
						{$sql_ts->row['D_FOGLI_INFO']}
					</td>
				</tr>
				<tr>
					<td>
						Se applicabile, la descrizione dello studio &egrave; adeguata alle diverse fasce di et&agrave; considerate
					</td>
					<td>
						{$sql_ts->row['D_FASCE_ETA']}
					</td>
				</tr>
			";
			
			if($sql_reg->row['TIPO_SPER']==3 || $sql_reg->row['TIPO_SPER']==7){
				$info_soggetti.="
				<tr>
					<td>
						L'informativa &egrave; conforme al template del Comitato Etico Regionale
					</td>
					<td>
						{$sql_ts->row['D_TEMPLATE']}
					</td>
				</tr>
				";
			}
			
			if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==5 || $sql_reg->row['TIPO_SPER']==6 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$info_soggetti.="
				<tr>
					<td>
						Se applicabile, l'informativa risponde alle principali domande previste dal CE
					</td>
					<td>
						{$sql_ts->row['D_INFORMATIVA']}
					</td>
				</tr>
				";
			}
			
			$info_soggetti.="
				<tr>
					<td>
						Le informazioni sono conformi al protocollo
					</td>
					<td>
						{$sql_ts->row['D_PROTOCOLLO']}
					</td>
				</tr>
				<tr>
					<td>
						Le informazioni sono conformi al protocollo
					</td>
					<td>
						{$sql_ts->row['D_RECLUTAMENTO']}
					</td>
				</tr>
				<tr>
					<td>
						Il linguaggio utilizzato &egrave; chiaro, privo di termini tecnici e specialistici
					</td>
					<td>
						{$sql_ts->row['D_LINGUAGGIO']}
					</td>
				</tr>
				<tr>
					<td>
						La procedura da seguire per sottoporre al/i soggetto/i il consenso informato &egrave; ben descritta
					</td>
					<td>
						{$sql_ts->row['D_PROCEDURA']}
					</td>
				</tr>
				<tr>
					<td>
						Rischi e benefici sono ben descritti e congruenti 
					</td>
					<td>
						{$sql_ts->row['D_RISCHI_BEN']}
					</td>
				</tr>
				<tr>
					<td>
						Il responsabile della conservazione, l'utilizzo e la durata di uso dei campioni biologici sono aspetti ben descritti (se applicabile)
					</td>
					<td>
						{$sql_ts->row['D_RESP_CONS']}
					</td>
				</tr>
				<tr>
					<td>
						La data e l'ora di consegna del modulo informativo ai pazienti da parte del medico sono presenti, cos&igrave; come la data e l'ora di firma del consenso informato
					</td>
					<td>
						{$sql_ts->row['D_CONSEGNA']}
					</td>
				</tr>
				<tr>
					<td>
						E' presente altro materiale per i soggetti
					</td>
					<td>
						{$sql_ts->row['D_ALTRO_MATERIALE']}
					</td>
				</tr>
				<tr>
					<td>
						Eventuali elementi critici riscontrati o altre osservazioni (testo libero):
					</td>
					<td>
						{$sql_ts->row['CRITICITA5']}
					</td>
				</tr>
				<tr>
					<td>
						La protezione dei dati personali e la confidenzialit&agrave; &egrave; assicurata
					</td>
					<td>
						{$sql_ts->row['D_CONFIDEN']}
					</td>
				</tr>
				<tr>
					<td>
						Eventuali elementi critici riscontrati o altre osservazioni (testo libero):
					</td>
					<td>
						{$sql_ts->row['CRITICITA6']}
					</td>
				</tr>
				<tr>
					<td>
						E' presente la lettera al medico curante/pediatra di libera scelta  (se applicabile)
					</td>
					<td>
						{$sql_ts->row['D_PLS']}
					</td>
				</tr>
				<tr>
					<td>
						Eventuali elementi critici riscontrati o altre osservazioni (testo libero):
					</td>
					<td>
						{$sql_ts->row['CRITICITA7']}
					</td>
				</tr>
				";
			
			$aspetti_economici="
				<tr>
					<td>
						L'idoneit&agrave; dello sperimentatore e dei suoi collaboratori &egrave; stata valutata dal Curriculum Vitae e dalla sua dichiarazione sul conflitto di interessi
					</td>
					<td>
						{$sql_ts->row['D_CV_PI']}
					</td>
				</tr>
				<tr>
					<td>
						L'adeguatezza della struttura sanitaria (in termini di personale, strutture e costi coinvolti nello studio secondo la specifica tipologia) &egrave; stata valutata dall'analisi di impatto aziendale fornita e riportante la firma del Direttore Generale
					</td>
					<td>
						{$sql_ts->row['D_DIR_GEN']}
					</td>
				</tr>
				<tr>
					<td>
						L'adeguatezza della struttura sanitaria (in termini di personale, strutture e costi coinvolti nello studio secondo la specifica tipologia) &egrave; stata valutata dall'analisi di impatto aziendale fornita e riportante la firma del Direttore Generale
					</td>
					<td>
						{$sql_ts->row['D_DIR_GEN']}
					</td>
				</tr>
			";
			
			if($sql_reg->row['TIPO_SPER']==3 || $sql_reg->row['TIPO_SPER']==7){
				$aspetti_economici.="
				<tr>
					<td>
						Per le indagini cliniche post marketing, lo Sperimentatore responsabile localmente dello studio ha fornito anche la checklist per l'istruttoria aziendale, finalizzata alla valutazione delle modalit&agrave; di acquisto del DM richiesti per indagini cliniche post marketing e a firma del Direttore della Farmacia Ospedaliera
					</td>
					<td>
						{$sql_ts->row['D_POST_MAR']}
					</td>
				</tr>
				";
			}
			
			$aspetti_economici.="
				<tr>
					<td>
						Per studi profit, lo sperimentatore locale ha rilasciato dichiarazione attestante che il personale coinvolto svolger&agrave; le relative attivit&agrave; oltre il normale orario di lavoro per tutto il personale coinvolto
					</td>
					<td>
						{$sql_ts->row['D_STRAORDINARI']}
					</td>
				</tr>
				<tr>
					<td>
						Per studi no-profit, lo sperimentatore locale ha rilasciato dichiarazione attestante che il personale coinvolto potr&agrave; svolgere le relative attivit&agrave; nell'orario di lavoro, senza pregiudicare le normali attivit&agrave; assistenziali
					</td>
					<td>
						{$sql_ts->row['D_NO_STRAORDINARI']}
					</td>
				</tr>
				<tr>
					<td>
						Per studi no-profit:<br>
						&nbsp;&nbsp;a) lo sperimentatore locale ha rilasciato dichiarazione attestante che per lo studio non &egrave; previsto alcun contributo economico e che lo studio non comporter&agrave; aggravio di costi a carico del SSN in quanto i costi relativi agli esami strumentali e di laboratorio extraroutinari saranno sostenuti con fondi ad hoc o che il sostenimento di costi aggiuntivi sia autorizzato dalla Direzione Aziendale
					</td>
					<td>
						{$sql_ts->row['D_NO_SSN']}
					</td>
				</tr>
				<tr>
					<td>
						&nbsp;&nbsp;b) lo sperimentatore locale ha rilasciato dichiarazione attestante che per lo studio &egrave; previsto un contributo economico e sono state dettagliatamente descritte le modalit&agrave; di impiego dello stesso, al netto del sostenimento di eventuali costi, per le finalit&agrave; proprie della ricerca
					</td>
					<td>
						{$sql_ts->row['D_CONTRIBUTO']}
					</td>
				</tr>
				<tr>
					<td>
						Esiste un finanziamento per lo studio clinico definito in un contratto tra promotore/supplier e centro clinico, e questo &egrave; stato concordato tra le parti (se applicabile)
					</td>
					<td>
						{$sql_ts->row['D_FINANZIAMENTO']}
					</td>
				</tr>
				";
				
			if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$aspetti_economici.="
				<tr>
					<td>
						L'eventuale rimborso spese per i partecipanti allo studio, secondo le modalit&agrave; previste dal DM 21 dicembre 2007 o altre normative applicabili, &egrave; congruo (se applicabile)
					</td>
					<td>
						{$sql_ts->row['D_RIMBORSO_SPESE']}
					</td>
				</tr>
				";
			}
			
			$aspetti_economici_1="";
			if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==3 || $sql_reg->row['TIPO_SPER']==7 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10 || $sql_reg->row['TIPO_SPER']==12){
				$aspetti_economici.="
					<tr>
						<td>
							Sono presenti una Polizza ed un Certificato Assicurativo specifici per lo studio, in cui siano chiare le disposizioni previste in materia di risarcimento dei danni ai pazienti o di decesso imputabili alla sperimentazione clinica
						</td>
						<td>
							{$sql_ts->row['D_POLIZZA']}
						</td>
					</tr>
					";
				
				$aspetti_economici_1="
					<tr>
						<td>
							Indennit&agrave; per gli sperimentatori (se applicabile)
						</td>
						<td>
							{$sql_ts->row['D_INDENNITA_PI']}
						</td>
					</tr>
					";
				
			}
			
			$aspetti_economici.="
				<tr>
					<td>
						Sono stati valutati gli importi e le eventuali modalit&agrave; di retribuzione o di compenso o di emolumenti di qualsiasi natura da corrispondersi agli sperimentatori (se applicabile)
					</td>
					<td>
						{$sql_ts->row['D_IMPORTI']}
					</td>
				</tr>
				<tr>
					<td>
						Sono stati valutati gli importi e le eventuali modalit&agrave; di retribuzione o di compenso o di emolumenti di qualsiasi natura da corrispondersi agli sperimentatori (se applicabile)
					</td>
					<td>
						{$sql_ts->row['D_IMPORTI']}
					</td>
				</tr>
				";
			$aspetti_economici.=$aspetti_economici_1;
			
			$aspetti_economici.="
				<tr>
					<td>
						Nel caso di enti no-profit &egrave; stato accertato il rispetto dei requisiti previsti dal DM 17/12/2004 (come indicato dall'allegato 1)
					</td>
					<td>
						{$sql_ts->row['D_REQUISITI_DM']}
					</td>
				</tr>
				<tr>
					<td>
						Lo studio presenta  una partnership profit/no-profit, i cui interessi sono chiaramente definiti in un agreement
					</td>
					<td>
						{$sql_ts->row['D_PARTNERSHIP']}
					</td>
				</tr>
				<tr>
					<td>
						Altro, specificare:
					</td>
					<td>
						{$sql_ts->row['ALTRO_SPEC']}
					</td>
				</tr>
			";
			
			
			$lettera_default="<style>
													td {
														font-family: Verdana;
												    font-size: 10px;
												    padding: 10px;
												    text-align: left;
													}
												</style>
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
  												<tr>
  													<td>
															Data e numero di protocollo (assegnato dagli uffici AOUM):
														</td>
														<td>
															{$sql_ver->row['RICEZI_DT']} {$sql_ver->row['DELIB_NUM']}
														</td>
													</tr>
													<tr>
  													<td>
															Inserito in osservatorio AIFA (OSsC):
														</td>
														<td>
															{$sql_ts->row['D_OSSC']}
														</td>
													</tr>
													<tr>
  													<td style='font-weight: bold;'>
															Data di avvio procedura di validazione:
														</td>
														<td>
															{$sql_ver->row['COMPLETEZZA_DT']}
														</td>
													</tr>
													<!--tr>
  													<td style='font-weight: bold;'>
															Data della seduta del Comitato Etico Pediatrico:
														</td>
														<td>
															Tenere presente che questa data &egrave; nota solo se si &egrave; gi&agrave; assegnato lo studio all'ODG di una riunione
														</td>
													</tr-->
													<tr>
  													<td>
															Numero dello studio nell'Ordine del Giorno:
														</td>
														<td>
															{$sql_ts->row['ID_STUD']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															IDENTIFICAZIONE DELLA SPERIMENTAZIONE CLINICA (interventistica)
														</td>
													</tr>
													<tr>
  													<td>
															TITOLO:
														</td>
														<td>
															{$sql_rs->row['TITOLO_PROT']}
														</td>
													</tr>
													<tr>
  													<td>
															Codice, versione e data del protocollo del promotore:
														</td>
														<td>
															{$sql_rs->row['CODICE_PROT']}, versione $versione_prot, data $data_prot
														</td>
													</tr>
													<tr>
  													<td>
															Numero EudraCT:
														</td>
														<td>
															{$sql_rs->row['EUDRACT_NUM']}
														</td>
													</tr>
													<tr>
  													<td>
															Indicazione del promotore (specificare anche se profit o no-profit):
														</td>
														<td>
															{$sql_rs->row['DESCR_SPONSOR']} ({$sql_rs->row['D_PROFIT']})
														</td>
													</tr>
													<tr>
  													<td>
															Centro COORDINATORE (solo per studi multicentrici):
														</td>
														<td>
															{$sql_rs->row['CENTRO_COORD']}
														</td>
													</tr>
													<tr>
  													<td>
															Denominazione del CE Coordinatore e data di rilascio del parere (se applicabile):
														</td>
														<td>
															{$sql_rs->row['CE_COORD']} - {$sql_rs->row['RICH_DT']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															IDENTIFICAZIONE DELLO SPERIMENTATORE RESPONSABILE DELLO STUDIO (richiedente)
														</td>
													</tr>
													<tr>
  													<td>
															(Qualifica) Cognome e Nome:
														</td>
														<td>
															{$sql_ce_l01->row['D_PRINC_INV']}
														</td>
													</tr>
													<tr>
  													<td>
															Sede di svolgimento dello studio:
														</td>
														<td>
															{$sql_ce_l01->row['D_CENTRO']}, {$sql_ce_l01->row['D_UNITA_OP']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>Breve descrizione del DISEGNO DELLO STUDIO, DELL'OBIETTIVO E DELLA POPOLAZIONE INTERESSATA (se applicabile specificarne i sottogruppi)</b>
															Gli elementi essenziali sono riassunti con il termine EPICOT (Evidence, Population, Intervention, Comparison, Outcome, and Time). Vedi articolo: How to formulate research recommendations. BMJ. Oct 14, 2006; 333(7572): 804-806.
														</td>
													</tr>
													<tr>
  													<td>
															DISEGNO DELLO STUDIO:
														</td>
														<td>
															{$disegno}
															Bracci: {$sql_rs->row['BRACCI']} <br>
														</td>
													</tr>
													<tr>
  													<td>
															OBIETTIVO:
														</td>
														<td>
															{$sql_rs->row['OBIETTIVO']}
														</td>
													</tr>
													<tr>
  													<td>
															POPOLAZIONE:
														</td>
														<td>
															{$popolazione}
															<br>Et&agrave;:<br>
															{$eta_popolazione}<br>
															Sesso: {$sql_rs->row['D_SESSO_POP']}<br><br>
															ICD9: {$sql_rs->row['ICD9_CODE']} {$sql_rs->row['ICD9_DECODE']}
														</td>
													</tr>
													<tr>
  													<td>
															INTERVENTO:
														</td>
														<td>
															{$intervento}
														</td>
													</tr>
													<tr>
  													<td>
															CONFRONTO:
														</td>
														<td>
															{$confronto}
														</td>
													</tr>
													<tr>
  													<td>
															OUTCOME:
														</td>
														<td>
															{$sql_rs->row['ENDPOINT_DESCR']}
														</td>
													</tr>
													<tr>
  													<td>
															TIME STOP DELLE EVIDENZE DISPONIBILI:
														</td>
														<td>
															<!--TOSCANA-51 lasciare testo libero-->
														</td>
													</tr>
													<tr>
  													<td>
															Altre informazioni:
														</td>
														<td>
															<!--TOSCANA-51 lasciare testo libero-->
														</td>
													</tr>
													
													<tr>
  													<td>
															Numero ed et&agrave; dei soggetti previsti per centro:
														</td>
														<td>
															{$sql_ce_l01->row['PAZ_NUM']} soggetti<br><br>
														</td>
													</tr>
													<tr>
  													<td>
															Contributo lordo previsto dal promotore (per soggetto completato, ove applicabile):
														</td>
														<td>
															{$sql_ce_l01->row['CORRISPETTIVO']}
														</td>
													</tr>
													<tr>
  													<td>
															Durata dello studio:
														</td>
														<td>
															{$sql_ce_l01->row['DUR_SPER']} {$sql_ce_l01->row['D_DUR_SPER_UNIT']}
														</td>
													</tr>
													<tr>
  													<td>
															Periodo di arruolamento (ove applicabile):
														</td>
														<td>
															{$sql_ce_l01->row['DUR_ARR']} {$sql_ce_l01->row['D_DUR_ARR_UNIT']}
														</td>
													</tr>
													<tr>
  													<td>
															Periodo di Follow-up (ove applicabile):
														</td>
														<td>
															{$sql_ce_l01->row['DUR_FUP']} {$sql_ce_l01->row['D_DUR_FUP_UNIT']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>DOCUMENTAZIONE PRESENTATA</b>
														</td>
													</tr>
													$doc_presentata
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>RICHIESTA DOCUMENTAZIONE INTEGRATIVA</b>
														</td>
													</tr>
													<tr>
  													<td>
															Specificare la data di richiesta dei documenti mancanti e il tipo di documenti:
														</td>
														<td>
															{$sql_ver->row['INTEGRAZ_DT']}
														</td>
													</tr>
													<tr>
  													<td>
															Specificare la data dei documenti ricevuti e il tipo di documenti:
														</td>
														<td>
															{$sql_ver->row['RICEZI_DT']}
														</td>
													</tr>
													<tr>
  													<td>
															Eventuali elementi critici riscontrati o altre osservazioni (testo libero):
														</td>
														<td>
															{$sql_ver->row['OSSERVAZIONI']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>ELEMENTI DA VALUTARE</b>
														</td>
													</tr>
													$elementi_valutare
												</table>
												
												$medicinale
												
												$protocollo_clinico
												
												$investigators_brochure
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>ASPETTI ETICI</b>
														</td>
													</tr>
													$aspetti_etici
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>INFORMAZIONE AI SOGGETTI E PROCEDURE PER IL CONSENSO INFORMATO</b>
														</td>
													</tr>
													$info_soggetti
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>STRUTTURE, PERSONALE ED ASPETTI ECONOMICO-AMMINISTRATIVI</b>
														</td>
													</tr>
													$aspetti_economici
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2'>
															<b>ALTRI ASPETTI PARTICOLARI CHE SI RITIENE DI PORTARE ALL'ATTENZIONE DEL COMITATO ETICO (testo libero):</b><br><br>
															{$sql_ts->row['ALTRI_ASPETTI']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2'>
															<b>Relatori</b><br><br>															
														</td>
													</tr>
												</table>
												
											";	
			

				
			$lettera_default=str_replace("-9944", "Non applicabile", $lettera_default);
			if ($_GET ['lettera'] == 'default') $lettera_istruttoria_ts=$lettera_default;
			else {
				$sql_query = "select lettera from ce_lettera_istruttoria_ts where id_stud={$_GET['ID_STUD']} and visitnum=2 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and esam=21 and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if ($sql->row ['LETTERA']) {$lettera_istruttoria_ts=$sql->row ['LETTERA']; }
					else $lettera_istruttoria_ts=$lettera_default;
			}
			
			include_once ("FCKeditor/fckeditor.php");
			
			$fckeditor = new FCKeditor ( "content" );
//			$fckeditor->ToolbarSet = 'Basic';

//			$dir="{$_SERVER['DOCUMENT_ROOT']}/gendocs";
//			$file = "/odg.html";
//			$letter= file_get_contents($dir.$file);
			
			$fckeditor->Value = $lettera_istruttoria_ts;
			$fckeditor->Height = '1100';
			
			$this->body.= "
			<form  name=\"edit\"  method=\"POST\"  id=\"edit\" >
			<input type=\"hidden\" name=\"lettera\" value=\"salva\">
			<input type=\"hidden\" name=\"VISITNUM_PROGR\" value=\"{$_GET['VISITNUM_PROGR']}\">
			<input type=\"hidden\" name=\"PROGR\" value=\"{$_GET['PROGR']}\">
			<input type=\"hidden\" name=\"ID_STUD\" value=\"{$_GET['ID_STUD']}\">
			<p style=\"font-size:18px\" align=center><b>Istruttoria Tecnico-Scientifica <br> $azienda_ente</b></p>
			<br>";
			
			$this->body.= "<fieldset style='border-color:#077f7f'>".$fckeditor->CreateHtml ()."</fieldset>";
			
			//$this->body.= "<p>
			//<input type='button' value='Chiudi senza salvare' onclick=\"self.close();\">
			//<input type='button' value='Torna al template predefinito' onclick='location.href=\"index.php?mod_istruttoria_ts=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&VISITNUM={$_GET['VISITNUM']}&PROGR={$_GET['PROGR']}&lettera=default\"'>
			//<input type='submit' value='Salva'>
			
			$this->body.= "<p>
			<button class='btn btn-undo' type='button' onclick=\"self.close();\"><i class='fa fa-close bigger-110'></i>Chiudi senza salvare</button>
			<button class='btn btn-purple' type='button' onclick='location.href=\"index.php?mod_istruttoria_ts=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&VISITNUM={$_GET['VISITNUM']}&PROGR={$_GET['PROGR']}&lettera=default\"'><i class='fa fa-refresh bigger-110'></i> Torna al template predefinito</button>
			<button class='btn btn-warning' type='submit' onclick=\"submit\"><i class='fa fa-floppy-o bigger-110'></i>Salva</button>
			
			<div style='float:center; text-align:center;'>
			<a href=\"#\" onclick=\"document.edit.lettera.value='pdf';document.edit.submit();\"><img src=\"images/pdf.png\"></img><br>Genera il file pdf</a>
			</div>
			</p></form><br><br>";
			
		}else{
			$sql_query = "select lettera from ce_lettera_istruttoria_ts where id_stud={$_GET['ID_STUD']} and visitnum=4 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and esam=1 and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if($this->getProfilo($this->user->userid)=="REG") $this->body.= "
				<fieldset>{$sql->row ['LETTERA']}</fieldset>
				";
				else $this->body.= "
				<fieldset></fieldset>
				";
				
		}		
			
	}

	#GENERAZIONE ISTRUTTORIA EMENDAMENTO
	if ($_GET ['mod_istruttoria_ts_eme'] == 'yes') {
		if ($this->session_vars ['USER_TIP'] == "DE"){
			$esam=5;
			
			if ($_POST ['lettera'] == 'salva') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$sql_insert_storico = "insert into S_CE_LETTERA_ITS_EME select '{$this->user->userid}', sysdate, storico_id.nextval, t.* from ce_lettera_istruttoria_ts t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_insert_storico );
				$sql->ins_upd ();
				$sql_delete = "delete from CE_LETTERA_ISTRUTTORIA_TS_EME t where t.ID_STUD='{$this->pk_service}' and VISITNUM_PROGR='{$_GET['VISITNUM_PROGR']}' and PROGR='{$_GET['PROGR']}'";
				$sql->set_sql ( $sql_delete );
				$sql->ins_upd ();
				$values ['ID_STUD'] = $this->pk_service;
				$values ['VISITNUM'] = '2';
				$values ['VISITNUM_PROGR'] = $_POST ['VISITNUM_PROGR'];
				$values ['ESAM'] = $esam;
				$values ['PROGR'] = $_POST ['PROGR'];
				$values ['USERID_INS'] = $this->user->userid;
				$values ['INSDT'] = "sysdate";
				$values ['LETTERA'] = $_POST ['content'];
				$pk = '';
				print_r ($values);
				$sql->insert ( $values, "ce_lettera_istruttoria_ts_eme", $pk );
				$this->conn->commit ();
				header("location:index.php?mod_istruttoria_ts_eme=yes&VISITNUM={$_GET['VISITNUM']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&PROGR={$_GET['PROGR']}&ID_STUD={$_GET['ID_STUD']}");
				die();
			}
			if ($_POST ['lettera'] == 'pdf') {
				$_POST['content']=str_replace("\\\"", "\"", $_POST['content']);
				$filetxt=$_POST ['content'];
				//echo $filetxt;
				//die();
				$filename = "Istruttoria_eme_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.html";
				$filename_pdf = "Istruttoria_eme_{$_GET['ID_STUD']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.pdf";
				$path = $_SERVER ['PATH_TRANSLATED'];
				$images_path = str_replace ( "index.php", "../gendocs/", $path );
				$path = str_replace ( "index.php", "temp_html/", $path );
				$file_html = $path . $filename;
				$html_handle = fopen ( $file_html, "w" );
				$filetxt = str_replace ( "/gendocs/", $images_path, $filetxt );
				$filetxt = str_replace ( "style=\"display:\"", "", $filetxt );
				fwrite ( $html_handle, $filetxt );
				$htmldoc="/http/local/bin/htmldoc_rw";
				system ( "$htmldoc -t pdf14 --fontsize 10 --no-title --size A4 --charset iso-8859-15 --browserwidth 1024 --footer .1. --header .t. --headfootsize 8 --headfootfont Times-Italic--bottom 10mm --top 6mm --left 10mm --right 10mm --path /amministrazione/schede_utente --webpage {$path}/{$filename}> {$path}/{$filename_pdf}" );
				die ( "<html><head><meta http-equiv=\"refresh\" content=\"0;url=temp_html/{$filename_pdf}\"></head><body>Generazione PDF in corso</body></html>" );
				die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=temp_html/{$filename_pdf}\"></head></html>" );
			}
			
			$datiUtente=$this->getDatiUtente2($this->user->userid);
			
			#Registrazione
			$query_reg = "select * from CE_REGISTRAZIONE where id_stud='{$this->pk_service}'";
			$sql_reg = new query ( $this->conn );
			$sql_reg->get_row ( $query_reg );
			
			#Riassunto studio
			$sql_query_rs = "select * from ce_info_studio where id_stud={$_GET['ID_STUD']}";
			$sql_rs = new query ( $this->conn );
			$sql_rs->get_row ( $sql_query_rs );
			
			#Emendamento
			$sql_query_eme = "select * from CE_EMENDAMENTI where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$_GET['VISITNUM_PROGR']}";
			$sql_eme = new query ( $this->conn );
			$sql_eme->get_row ( $sql_query_eme );
			$numero_eme=$sql_eme->row['VISITNUM_PROGR'];
			
			
//			#dati verificadoc
//			$sql_query_ver = "select * from ce_reginvio 
//			where id_stud={$_GET['ID_STUD']} and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']} 
//			and progr = (select max(progr) from ce_reginvio where id_stud={$_GET['ID_STUD']} and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']})";
//			$sql_ver = new query ( $this->conn );
//			$sql_ver->get_row ( $sql_query_ver );
//			
//			#Documentazione generale
//			$sql_query_dg = "select * from ce_documentazione where id_stud={$_GET['ID_STUD']} order by doc_dt";
//			$sql_dg = new query ( $this->conn );
//			$sql_dg->set_sql ( $sql_query_dg );
//			$sql_dg->exec ();
//			while($sql_dg->get_row ()){
//				if($sql_dg->row['DOC_GEN']==4){
//					$versione_prot=$sql_dg->row['DOC_VERS'];
//					$data_prot=$sql_dg->row['DOC_DT'];
//				}
//			}
//			
//			$sql_query_l01 = "select * from CE_LOCALE01 where id_stud='{$this->pk_service}' and visitnum_progr={$_GET['VISITNUM_PROGR']}";
//			$sql_ce_l01 = new query ( $this->conn );
//			$sql_ce_l01->get_row ( $sql_query_l01 );
			
			#Istruttoria TS
			$sql_query_ts = "select * from CE_EME_ITS where id_stud={$_GET['ID_STUD']} and visitnum={$_GET['VISITNUM']} and visitnum_progr={$_GET['VISITNUM_PROGR']} and esam=$esam and progr={$_GET['PROGR']}";
			$sql_ts = new query($this->conn);
			$sql_ts->get_row( $sql_query_ts );			
			
			$lettera_default="<style>
													td {
														font-family: Verdana;
												    font-size: 10px;
												    padding: 10px;
												    text-align: left;
													}
												</style>
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
  												<tr>
  													<td>
															Data e numero di protocollo (assegnato dagli uffici AOUM):
														</td>
														<td>
															{$sql_ver->row['RICEZI_DT']} {$sql_ver->row['DELIB_NUM']}
														</td>
													</tr>
													<tr>
  													<td>
															Inserito in osservatorio AIFA (OSsC):
														</td>
														<td>
															{$sql_ts->row['D_OSSC']}
														</td>
													</tr>
													<tr>
  													<td style='font-weight: bold;'>
															Data di avvio procedura di validazione:
														</td>
														<td>
															
														</td>
													</tr>
													<!--tr>
  													<td style='font-weight: bold;'>
															Data della seduta del Comitato Etico Pediatrico:
														</td>
														<td>
															Tenere presente che questa data &egrave; nota solo se si &egrave; gi&agrave; assegnato lo studio all'ODG di una riunione
														</td>
													</tr-->
													<tr>
  													<td>
															Numero dello studio nell'Ordine del Giorno:
														</td>
														<td>
															{$sql_ts->row['ID_STUD']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															IDENTIFICAZIONE DELL'EMENDAMENTO allo studio clinico
														</td>
													</tr>
													<tr>
  													<td>
															TITOLO:
														</td>
														<td>
															{$sql_rs->row['TITOLO_PROT']}
														</td>
													</tr>
													<tr>
  													<td>
															Codice, versione e data del protocollo del promotore:
														</td>
														<td>
															{$sql_rs->row['CODICE_PROT']}, versione $versione_prot, data $data_prot
														</td>
													</tr>
													<tr>
  													<td>
															Numero EudraCT:
														</td>
														<td>
															{$sql_rs->row['EUDRACT_NUM']}
														</td>
													</tr>
													<tr>
  													<td>
															Indicazione del promotore (specificare anche se profit o no-profit):
														</td>
														<td>
															{$sql_rs->row['DESCR_SPONSOR']} ({$sql_rs->row['D_PROFIT']})
														</td>
													</tr>
													<tr>
  													<td>
															Centro COORDINATORE (solo per studi multicentrici):
														</td>
														<td>
															Tenere presente che, se il centro coord &egrave; fuori dalla regione, l'informazione non &egrave; raccolta nelle schede dello studio; occorre aggiungerla nella scheda di riassunto?
														</td>
													</tr>
													<tr>
  													<td>
															Denominazione del CE Coordinatore e data di rilascio del parere (se applicabile):
														</td>
														<td>
															Tenere presente che, se il centro coord &egrave; fuori dalla regione, l'informazione non &egrave; raccolta nelle schede dello studio; occorre aggiungerla nella scheda di riassunto?
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															IDENTIFICAZIONE DELLO SPERIMENTATORE RESPONSABILE DELLO STUDIO (richiedente)
														</td>
													</tr>
													<tr>
  													<td>
															(Qualifica) Cognome e Nome:
														</td>
														<td>
															{$sql_ce_l01->row['D_PRINC_INV']}
														</td>
													</tr>
													<tr>
  													<td>
															Sede di svolgimento dello studio:
														</td>
														<td>
															{$sql_ce_l01->row['D_CENTRO']}, {$sql_ce_l01->row['D_UNITA_OP']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															<b>ELENCO STORICO DEGLI EMENDAMENTI (SOSTANZIALI E NON SOSTANZIALI), con indicazione della tipologia, del numero e della data di approvazione/notifica da parte del Comitato Etico a cui afferisce lo sperimentatore richiedente</b>
														</td>
													</tr>
													<tr>
  													<td colspan='2'>
															1.
														</td>
													</tr>
													<tr>
  													<td colspan='2'>
															2.
														</td>
													</tr>
													<tr>
  													<td>
															3.
														</td>
													</tr>
													<tr>
  													<td colspan='2'>
															Eventuali note <i>(testo libero)</i>
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															IDENTIFICAZIONE DELL'EMENDAMENTO \"SOSTANZIALE\" DA VALUTARE
														</td>
													</tr>
													<tr>
  													<td>
															Numero emendamento e data:
														</td>
														<td>
															{$numero_eme} - {$sql_eme->row['EMEND_DT']}
														</td>
													</tr>
													<tr>
  													<td>
															Descrizione dell'emendamento e motivi per apportarlo:
														</td>
														<td>
															{$sql_eme->row['SINTESI_EM']}
														</td>
													</tr>
													<tr>
  													<td>
															<i>Eventuali osservazioni (testo libero):</i>
														</td>
														<td>
															
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															DOCUMENTAZIONE PRESENTATA
														</td>
													</tr>
													<tr>
  													<td>
															Lettera di trasmissione, contenente le motivazioni per considerare l'emendamento come sostanziale, firmata e datata
														</td>
														<td>
															{$sql_ts->row['D_LETTERA']}
														</td>
													</tr>
													<tr>
  													<td>
															Appendice 9 (se applicabile)
														</td>
														<td>
															{$sql_ts->row['D_APP9']}
														</td>
													</tr>
													<tr>
  													<td>
															Elenco dei documenti emendati in versione track-change e clean
														</td>
														<td>
															
														</td>
													</tr>
													<tr>
  													<td>
															Informazioni di supporto, se applicabili
														</td>
														<td>
															{$sql_ts->row['NOTE_DOC']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															RICHIESTA DOCUMENTAZIONE INTEGRATIVA
														</td>
													</tr>
													<tr>
  													<td colspan='2'>
															Specificare i documenti mancanti e la data di richiesta:
														</td>
													</tr>
													<tr>
  													<td colspan='2'>
															Specificare i documenti ricevuti e la data di ricezione:
														</td>
													</tr>
													<tr>
  													<td colspan='2'>
															<i>Eventuali elementi critici riscontrati (testo libero):</i>
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															ELEMENTI DA VALUTARE
														</td>
													</tr>
													<tr>
  													<td>
															L'emendamento &egrave; tale da \"incidere sulla sicurezza dei soggetti della sperimentazione o modificare l'interpretazione della documentazione scientifica a sostegno dello svolgimento dello studio oppure siano significativi in relazione allo svolgimento clinico dello studio\" (definizione emendamento sostanziale dal DM 21 dicembre 2007)
														</td>
														<td>
															{$sql_ts->row['D_EME_DM']}
														</td>
													</tr>
													<tr>
  													<td>
															L'emendamento &egrave; stato oggetto di misure urgenti ed adeguate per proteggere i soggetti dello studio contro ogni possibile rischio
														</td>
														<td>
															{$sql_ts->row['D_MIS_URGENTI']}
														</td>
													</tr>
													
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															ELEMENTI MODIFICATI DALL'EMENDAMENTO
														</td>
													</tr>
													<tr>
  													<td>
															Protocollo
														</td>
														<td>
															{$sql_ts->row['D_PROTOCOLLO']}
														</td>
													</tr>
													<tr>
  													<td>
															Dati sulla qualit&agrave; e/o sicurezza dell'IMP
														</td>
														<td>
															{$sql_ts->row['D_QUALITA']}
														</td>
													</tr>
													<tr>
  													<td>
															Informative al paziente/genitore/tutore legale
														</td>
														<td>
															{$sql_ts->row['D_PAZ']}
														</td>
													</tr>
													<tr>
  													<td>
															Informazioni al medico curante
														</td>
														<td>
															{$sql_ts->row['D_MEDICO']}
														</td>
													</tr>
													<tr>
  													<td>
															Sperimentatore principale di un centro
														</td>
														<td>
															{$sql_ts->row['D_PI']}
														</td>
													</tr>
													<tr>
  													<td>
															Polizza assicurativa
														</td>
														<td>
															{$sql_ts->row['D_POLIZZA']}
														</td>
													</tr>
													<tr>
  													<td>
															Bozza di convenzione
														</td>
														<td>
															{$sql_ts->row['D_BOZZA']}
														</td>
													</tr>
													<tr>
  													<td>
															Altro (specificare):
														</td>
														<td>
															{$sql_ts->row['ALTRO2']}
														</td>
													</tr>
													<tr>
  													<td>
															L'emendamento ha conseguenze per i soggetti gi&agrave; inclusi nello studio
														</td>
														<td>
															{$sql_ts->row['D_CONSEGUENZE']}
														</td>
													</tr>
													<tr>
  													<td>
															L'emendamento riguarda la sospensione temporanea dello studio
														</td>
														<td>
															{$sql_ts->row['D_SOSPENSIONE']}
														</td>
													</tr>
													<tr>
  													<td>
															Eventuali note (testo libero):
														</td>
														<td>
															{$sql_ts->row['NOTE']}
														</td>
													</tr>
													
													<br>
													
													<tr>
  													<td colspan='2' style='background-color: #C4FEFF; font-weight: bold;'>
															ELEMENTI MODIFICATI NEL PROTOCOLLO CLINICO (SE APPLICABILE) E RIVALUTATI
														</td>
													</tr>
													<tr>
  													<td>
															Aspetti etici, quali tutela dei diritti, salute, benessere dei soggetti
														</td>
														<td>
															{$sql_ts->row['D_ETICI']}
														</td>
													</tr>
													<tr>
  													<td>
															Procedure per la qualit&agrave; dei dati
														</td>
														<td>
															{$sql_ts->row['D_PROCEDURE']}
														</td>
													</tr>
													<tr>
  													<td>
															Obiettivi dello studio
														</td>
														<td>
															{$sql_ts->row['D_OBIETTIVI']}
														</td>
													</tr>
													<tr>
  													<td>
															Disegno dello Studio
														</td>
														<td>
															{$sql_ts->row['D_DISEGNO']}
														</td>
													</tr>
													<tr>
  													<td>
															Modalit&agrave; di sottomissione del Consenso informato
														</td>
														<td>
															{$sql_ts->row['D_CONSENSO']}
														</td>
													</tr>
													<tr>
  													<td>
															Procedure di arruolamento
														</td>
														<td>
															{$sql_ts->row['D_ARRUOLAMENTO']}
														</td>
													</tr>
													<tr>
  													<td>
															Misurazioni di esito
														</td>
														<td>
															{$sql_ts->row['D_ESITO']}
														</td>
													</tr>
													<tr>
  													<td>
															Tempistica degli esami clinico-diagnostici
														</td>
														<td>
															{$sql_ts->row['D_TEMPI']}
														</td>
													</tr>
													<tr>
  													<td>
															Aggiunta o eliminazione di test o di misurazioni
														</td>
														<td>
															{$sql_ts->row['D_TEST']}
														</td>
													</tr>
													<tr>
  													<td>
															Numero dei partecipanti
														</td>
														<td>
															{$sql_ts->row['D_PARTECIPANTI']}
														</td>
													</tr>
													<tr>
  													<td>
															Intervallo di et&agrave; dei partecipanti
														</td>
														<td>
															{$sql_ts->row['D_ETA_PARTECIPANTI']}
														</td>
													</tr>
													<tr>
  													<td>
															Criteri di inclusione
														</td>
														<td>
															{$sql_ts->row['D_INCLUSIONE']}
														</td>
													</tr>
													<tr>
  													<td>
															Criteri di esclusione
														</td>
														<td>
															{$sql_ts->row['D_ESCLUSIONE']}
														</td>
													</tr>
													<tr>
  													<td>
															Monitoraggio della sicurezza
														</td>
														<td>
															{$sql_ts->row['D_MONITORAGGIO']}
														</td>
													</tr>
													<tr>
  													<td>
															Variazione dei criteri di sicurezza per interrompere il trattamento sperimentale
														</td>
														<td>
															{$sql_ts->row['D_SICUREZZA']}
														</td>
													</tr>
													<tr>
  													<td>
															Durata dell'esposizione al prodotto sperimentale
														</td>
														<td>
															{$sql_ts->row['D_DURATA']}
														</td>
													</tr>
													<tr>
  													<td>
															Variazione di posologia del medicinale sperimentale
														</td>
														<td>
															{$sql_ts->row['D_POSOLOGIA']}
														</td>
													</tr>
													<tr>
  													<td>
															Variazione del prodotto di confronto
														</td>
														<td>
															{$sql_ts->row['D_CONFRONTO']}
														</td>
													</tr>
													<tr>
  													<td>
															Analisi statistica
														</td>
														<td>
															{$sql_ts->row['D_STATISTICA']}
														</td>
													</tr>
													<tr>
  													<td>
															Variazione della definizione di conclusione dello studio
														</td>
														<td>
															{$sql_ts->row['D_CONCLUSIONE']}
														</td>
													</tr>
													<tr>
  													<td>
															Modificazione alla valutazione del rapporto beneficio/rischio
														</td>
														<td>
															{$sql_ts->row['D_RAPPORTO']}
														</td>
													</tr>
													<tr>
  													<td>
															<i>Eventuali note (testo libero):</i>
														</td>
														<td>
															{$sql_ts->row['NOTE2']}
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2'>
															<b>ALTRI ASPETTI PARTICOLARI CHE SI RITIENE DI PORTARE ALL'ATTENZIONE DEL COMITATO ETICO (testo libero):</b><br><br>
														</td>
													</tr>
												</table>
												
												<br>
												
												<table width='90%' cellspacing='0' cellpadding='0' border='1' align='center'>
													<tr>
  													<td colspan='2'>
															<b>Relatori</b><br><br>															
														</td>
													</tr>
												</table>
												
											";	
			

				
			$lettera_default=str_replace("-9944", "Non applicabile", $lettera_default);
			if ($_GET ['lettera'] == 'default') $lettera_istruttoria_ts=$lettera_default;
			else {
				$sql_query = "select lettera from ce_lettera_istruttoria_ts_eme where id_stud={$_GET['ID_STUD']} and visitnum=4 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and esam=1 and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if ($sql->row ['LETTERA']) {$lettera_istruttoria_ts=$sql->row ['LETTERA']; }
					else $lettera_istruttoria_ts=$lettera_default;
			}
			
			include_once ("FCKeditor/fckeditor.php");
			
			$fckeditor = new FCKeditor ( "content" );
//			$fckeditor->ToolbarSet = 'Basic';

//			$dir="{$_SERVER['DOCUMENT_ROOT']}/gendocs";
//			$file = "/odg.html";
//			$letter= file_get_contents($dir.$file);
			
			$fckeditor->Value = $lettera_istruttoria_ts;
			$fckeditor->Height = '1100';
			
			$this->body.= "
			<form  name=\"edit\"  method=\"POST\"  id=\"edit\" >
			<input type=\"hidden\" name=\"lettera\" value=\"salva\">
			<input type=\"hidden\" name=\"VISITNUM_PROGR\" value=\"{$_GET['VISITNUM_PROGR']}\">
			<input type=\"hidden\" name=\"PROGR\" value=\"{$_GET['PROGR']}\">
			<input type=\"hidden\" name=\"ID_STUD\" value=\"{$_GET['ID_STUD']}\">
			<p style=\"font-size:18px\" align=center><b>Istruttoria Tecnico-Scientifica <br> $azienda_ente</b></p>
			<br>";
			
			$this->body.= "<fieldset style='border-color:#077f7f'>".$fckeditor->CreateHtml ()."</fieldset>";
			
			//$this->body.= "<p>
			//<input type='button' value='Chiudi senza salvare' onclick=\"self.close();\">
			//<input type='button' value='Torna al template predefinito' onclick='location.href=\"index.php?mod_istruttoria_ts=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&VISITNUM={$_GET['VISITNUM']}&PROGR={$_GET['PROGR']}&lettera=default\"'>
			//<input type='submit' value='Salva'>
			
			$this->body.= "<p>
			<button class='btn btn-undo' type='button' onclick=\"self.close();\"><i class='fa fa-close bigger-110'></i>Chiudi senza salvare</button>
			<button class='btn btn-purple' type='button' onclick='location.href=\"index.php?mod_istruttoria_ts_eme=yes&ID_STUD={$_GET['ID_STUD']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&VISITNUM={$_GET['VISITNUM']}&PROGR={$_GET['PROGR']}&lettera=default\"'><i class='fa fa-refresh bigger-110'></i> Torna al template predefinito</button>
			<button class='btn btn-warning' type='submit' onclick=\"submit\"><i class='fa fa-floppy-o bigger-110'></i>Salva</button>
			
			<div style='float:center; text-align:center;'>
			<a href=\"#\" onclick=\"document.edit.lettera.value='pdf';document.edit.submit();\"><img src=\"images/pdf.png\"></img><br>Genera il file pdf</a>
			</div>
			</p></form><br><br>";
			
		}else{
			$sql_query = "select lettera from CE_LETTERA_ISTRUTTORIA_TS_EME where id_stud={$_GET['ID_STUD']} and visitnum=20 and visitnum_progr={$this->session_vars['VISITNUM_PROGR']} and esam=1 and progr={$this->session_vars['PROGR']}";
				$sql = new query ( $this->conn );
				$sql->set_sql ( $sql_query );
				$sql->exec ();
				$sql->get_row ();
				if($this->getProfilo($this->user->userid)=="REG") $this->body.= "
				<fieldset>{$sql->row ['LETTERA']}</fieldset>
				";
				else $this->body.= "
				<fieldset></fieldset>
				";
				
		}		
			
	}	
	
	if ($_GET ['insert'] == 'PI' && $this->user->profilo=='Segreteria CE') {
		$_POST['COGNOME']=trim($_POST['COGNOME']);
		$_POST['NOME']=trim($_POST['NOME']);
		if($_POST['PI']=='new' && $_POST['COGNOME'] != "" && $_POST['NOME'] != ""){
			$sql = new query ( $this->conn );
			$query_max = "select max(PROGR_PRINC_INV)+1 as NEXT_PI from CE_VENETO_PRINC_INV";
			$sql->get_row($query_max);
			$bindInsert['PROGR_PRINC_INV']=$sql->row['NEXT_PI'];
			$bindInsert['PRINC_INV']=$_POST['COGNOME']." ".$_POST['NOME'];
			$bindInsert['ID_STR']=$_POST['ID_STR'];
			$bindInsert['DIP_UNI']=$_POST['DIP_UNI'];
			if($_POST['DIP_UNI']==1) $bindInsert['D_DIP_UNI']="Si";
			if($_POST['DIP_UNI']==2) $bindInsert['D_DIP_UNI']="No";
			
			$bind_check['COGNOME']=strtoupper($_POST['COGNOME']);
			$bind_check['NOME']=strtoupper($_POST['NOME']);
			$bind_check['ID_STR']=$_POST['ID_STR'];
			$query_check = "select count(*) as CONTO from CE_VENETO_PRINC_INV where upper(PRINC_INV) like '%'||:NOME and upper(PRINC_INV) like :COGNOME||'%' and ID_STR=:ID_STR";
			$sql_check = new query ( $this->conn );
			$sql_check->get_row($query_check,$bind_check);
			if ($sql_check->row['CONTO']>0){
				error_page('','attenzione, il principal investigator risulta già inserito');
			}else{
			$sql_new = "insert into CE_VENETO_PRINC_INV (PROGR_PRINC_INV,PRINC_INV,ID_STR,DIP_UNI,D_DIP_UNI) VALUES (:PROGR_PRINC_INV,:PRINC_INV,:ID_STR,:DIP_UNI,:D_DIP_UNI) ";
            $sql->ins_upd ($sql_new,$bindInsert);
			$this->conn->commit();
				header ( "location:/uxmr/index.php?list=patients_list_PI.xml&SUCCESS=yes" );
			}
		}else if($_POST['PI']=='new'){
			error_page('','attenzione, compilare correttamente la form','attenzione, compilare correttamente la form');
		}
		
		$query_centri = "select distinct ID, DESCRIZIONE from CE_VENETO_USERID_CE where userid='{$this->session_vars['remote_userid']}' order by descrizione";
			$sql_centri = new query ( $this->conn );
			$sql_centri->exec($query_centri);
			while($sql_centri->get_row()){
				
				if ($_GET['ID_REF_STR']==$sql_centri->row['ID']){
					${checked.$sql_centri->row['ID']}="selected='selected'";
				}
				
				$options.="<option value=\"{$sql_centri->row['ID']}\" ${checked.$sql_centri->row['ID']}>{$sql_centri->row['DESCRIZIONE']}</option>";
			
			}
		
		$this->body.= "
			<form  name=\"edit\"  method=\"POST\"  id=\"edit\" >
			<table border=0 align=center>
			<input type=\"hidden\" name=\"PI\" value=\"new\">
			<p style=\"font-size:18px; font-family: Times New Roman; text-align: center;\"><b>Nuovo Principal Investigator: 
			<br>
			<tr>
				<td class=destra align=\"right\"><b>Nome: </b></td>
				<td class=input>
					<input name=\"NOME\" size=\"20\" maxlength=\"20\" type=\"text\">
				</td>
			</tr>
			<tr>
				<td class=destra align=\"right\"><b>Cognome: </b></td>
				<td class=input>
					<input name=\"COGNOME\" size=\"20\" maxlength=\"20\" type=\"text\">
				</td>
			</tr>
			<tr>
				<td class=destra align=\"right\"><b>Dipendente universitario: </b></td>
				<td class=input>
					<select name='DIP_UNI'\">
						<option value=\"1\">Si</option>
						<option value=\"2\">No</option>
					</select>
				</td>
			</tr>
			<tr>
				<td class=destra align=\"right\"><b>Struttura: </b></td>
				<td class=input>
					<select name='ID_STR'\">
					$options
					</select>
				</td>
			</tr>
			</table>
			";
		$this->body.= "<p style=\"font-size:18px; font-family: Times New Roman; text-align: center;\">
			<!--input type='submit' value='Inserisci'>
			<input type='button' value='Annulla' onclick=\"history.back();\"-->
			<button class=\"btn btn-grey btn-sm\" type=\"button\" onclick=\"history.back();\" style=\"height:42px;\">
				<i class=\"icon-undo btn-sm\"></i>
				Annulla inserimento
			</button>
			<button style=\"margin-top: 2px;\" onclick=\"window.location='index.php?insert=PI&'\" type=\"submit\" class=\"btn btn-info blue\">
				<i class=\"fa fa-plus bigger-110\"></i>
				Inserisci
			</button>
			</form><br><br>";
	}
	
	if ($_GET ['insert'] == 'UO' && $this->user->profilo=='Segreteria CE') {
		$_POST['DESCR_UO']=trim($_POST['DESCR_UO']);
		if($_POST['UO']=='new' && $_POST['DESCR_UO'] != ""){
			$sql = new query ( $this->conn );
			$query_max = "select max(ID_UO)+1 as NEXT_UO from CE_VENETO_DIP";
			$sql->get_row($query_max);
			$bindInsert['ID_UO']=$sql->row['NEXT_UO'];
			$bindInsert['DESCR_UO']=$_POST['DESCR_UO'];
			$bindInsert['ID_REF_STR']=$_POST['ID_REF_STR'];
			
			$bind_check['ID_REF_STR']=$_POST['ID_REF_STR'];
			$bind_check['DESCR_UO']=strtoupper($_POST['DESCR_UO']);
			$query_check = "select count(*) as CONTO from CE_VENETO_DIP where upper(DESCR_UO) like '%'||:DESCR_UO||'%' and ID_REF_STR=:ID_REF_STR";
			$sql_check = new query ( $this->conn );
			$sql_check->get_row($query_check,$bind_check);
			if ($sql_check->row['CONTO']>0){
				error_page('','attenzione, l\'unità operativa risulta già inserita');
			}else{
			$sql_new = "insert into CE_VENETO_DIP (ID_UO,DESCR_UO,ID_REF_STR) VALUES (:ID_UO,:DESCR_UO,:ID_REF_STR) ";
            $sql->ins_upd ($sql_new,$bindInsert);
			$this->conn->commit();
			header ( "location:/uxmr/index.php?list=patients_list_UO.xml&SUCCESS=yes" );
			}
		}else if($_POST['UO']=='new'){
			error_page('','attenzione, compilare correttamente la form','attenzione, compilare correttamente la form');
		}
		
		$query_centri = "select distinct ID, DESCRIZIONE from CE_VENETO_USERID_CE where userid='{$this->session_vars['remote_userid']}' order by descrizione";
			$sql_centri = new query ( $this->conn );
			$sql_centri->exec($query_centri);
			while($sql_centri->get_row()){
				
				if ($_GET['ID_REF_STR']==$sql_centri->row['ID']){
					${checked.$sql_centri->row['ID']}="selected='selected'";
				}
				
				$options.="<option value=\"{$sql_centri->row['ID']}\" ${checked.$sql_centri->row['ID']}>{$sql_centri->row['DESCRIZIONE']}</option>";
			
			}
		
		$this->body.= "
			<form  name=\"edit\"  method=\"POST\"  id=\"edit\" >
			<table border=0 align=center>
			<input type=\"hidden\" name=\"UO\" value=\"new\">
			<p style=\"font-size:18px; font-family: Times New Roman; text-align: center;\"><b>Nuova Unit&agrave; Operativa: 
			<br>
			<tr>
				<td class=destra align=\"right\"><b>Descrizione: </b></td>
				<td class=input>
					<input name=\"DESCR_UO\" size=\"40\" maxlength=\"40\" type=\"text\">
				</td>
			</tr>
			<tr>
				<td class=destra align=\"right\"><b>Struttura: </b></td>
				<td class=input>
					<select name='ID_REF_STR'\">
					$options
					</select>
				</td>
			</tr>
			</table>
			";
		$this->body.= "<p style=\"font-size:18px; font-family: Times New Roman; text-align: center;\">
			<!--input type='submit' value='Inserisci'>
			<input type='button' value='Annulla' onclick=\"history.back();\"-->
			<button class=\"btn btn-grey btn-sm\" type=\"button\" onclick=\"history.back();\" style=\"height:42px;\">
				<i class=\"icon-undo btn-sm\"></i>
				Annulla inserimento
			</button>
			<button style=\"margin-top: 2px;\" onclick=\"window.location='index.php?insert=PI&'\" type=\"submit\" class=\"btn btn-info blue\">
				<i class=\"fa fa-plus bigger-110\"></i>
				Inserisci
			</button>
			</form><br><br>";
	}
		
		
		parent::Controller();
		//echo "<br/>{$this->session_vars ['USER_TIP']}<br/>";
		//echo "<br/>{$this->session_vars ['WFact']}<br/>";

//		if (isset($_GET['DocPrat'])){
//			$this->DocumentazionePratica();
//			$this->body.="<a href=\"index.php\">&lt;&lt;Torna alla home del sistema</a>";
//		}
		
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

	}
	
	function ListPage($percorso_base = null) {

		$list = $_GET ['list'];
		if ($list == '')
			$list = 'patients_list.xml';

		if (isset ( $this->workflow ) && ($list == 'patients_list.xml' || stristr($list,'patients_list'))) {
			$prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
			$list = str_replace ( ".xml", "_{$prof_add}.xml", $list );
		}
		
		if (! isset ( $_GET ['PAGE'] )) $_GET ['PAGE'] = 1;
		$list_o = new xml_list ( $this->xml_dir . "/" . $list, $_GET ['PAGE'], 20, null, null, $this->session_vars, $this->visit_structure );

		//viene chiamato patients_list solo in caso sia davvero patients_list. se no altra_list
		if ($list == 'patients_list.xml') {
			$this->percorso = $this->breadcrumb ( "patients_list" );
			}
		else{
			$titolo = $list_o->list['TITOLO'];
			$this->percorso = $this->breadcrumb ( "altra_list",$titolo );
		}
		
		if ($_GET ['DEBUG'] == 1) echo $list;
		
		if ($_GET['list']=="patients_list_add.xml") $specchietto_ricerca.="<div class=\"well well-sm\" style=\"margin-bottom: 0px;\"><b>Selezionare i parametri di ricerca</b>";
		
		//echo $this->user->profilo;

		if ($_GET['list']=="patients_list_add.xml" && ($this->user->profilo=='Segreteria CE' || $this->user->profilo=='Unita di ricerca')){
			
			if ($_GET['TIPO_SPER']==1) $checked1="selected";
			if ($_GET['TIPO_SPER']==2) $checked2="selected";
			if ($_GET['TIPO_SPER']==3) $checked3="selected";
			if ($_GET['TIPO_SPER']==5) $checked5="selected";
			if ($_GET['TIPO_SPER']==6) $checked6="selected";
			if ($_GET['TIPO_SPER']==7) $checked7="selected";
			if ($_GET['TIPO_SPER']==8) $checked8="selected";
			if ($_GET['TIPO_SPER']==10) $checked10="selected";
			
			if ($_GET['STATO']==1) $checked21="selected";
			if ($_GET['STATO']==2) $checked22="selected";
			if ($_GET['STATO']==3) $checked23="selected";
			if ($_GET['STATO']==4) $checked24="selected";
			if ($_GET['STATO']==5) $checked25="selected";
			if ($_GET['STATO']==6) $checked26="selected";
			if ($_GET['STATO']==7) $checked27="selected";
			if ($_GET['STATO']==8) $checked28="selected";
			if ($_GET['STATO']==9) $checked29="selected";
						
			$specchietto_ricerca.="
				<table width=70% align=center border=0>
				<tr>
				<td>
				<form action=\"index.php\" method=\"GET\">
				<table border=0 align=center>
					<tr>
						<input type='hidden' name='list' value=\"{$_GET['list']}\">
					</tr>
					<tr>
					<!--td class=destra align=\"right\" width=\"150\"><b>ID Studio:</b></td>
					<td class=input width=\"200\"><input type='text' size='30' maxlenght='14' name='ID_STUD' value=\"{$_GET['ID_STUD']}\"></td-->
					<td class=destra align=\"right\" width=\"150\"><b>Sponsor:</b></td>
					<td class=input width=\"200\"><input type='text' size='30' maxlenght='50' name='S2_DESCR_SPONSOR' value=\"{$_GET['S2_DESCR_SPONSOR']}\"></td>
					<td class=destra align=\"right\" width=\"150\"><b>Codice Studio:</b></td>
					<td class=input width=\"200\"><input type='text' size='30' maxlenght='50' name='S2_CODICE_PROT' value=\"{$_GET['S2_CODICE_PROT']}\"></td>
					</tr>
					<tr>
					<td class=destra align=\"right\" width=\"150\"><b>Titolo Studio:</b></td>
					<td class=input width=\"200\"><input type='text' size='30' maxlenght='50' name='S2_TITOLO_PROT' value=\"{$_GET['S2_TITOLO_PROT']}\"></td>
					<td class=destra align=\"right\" width=\"150\"><b>Eudract number:</b></td>
					<td class=input width=\"200\"><input type='text' size='30' maxlenght='14'  name='S2_EUDRACT_NUM' value=\"{$_GET['S2_EUDRACT_NUM']}\"></td>
					</tr>
					<tr>
					<td class=destra align=\"right\" width=\"150\"><b>ID Studio:</b></td>
					<td class=input width=\"200\"><input type='text' size='30' maxlenght='50' name='S2_ID_STUD' value=\"{$_GET['S2_ID_STUD']}\"></td>
					<td class=destra align=\"right\" width=\"150\"><b></b></td>
					<td class=input width=\"200\"></td>
					</tr>
					<tr>
					<td class=destra align=\"right\"><b>Tipo di studio:</b></td>
					<td class=input><select name='TIPO_SPER' value=\"{$_GET['TIPO_SPER']}\">
						<option value=\"\">Tutti</option>
						<option value=\"1\" $checked1>Interventistico con farmaco</option>
						<option value=\"2\" $checked2>Interventistico senza farmaco e dispositivo</option>
						<option value=\"3\" $checked3>Interventistico con dispositivo medico</option>
						<option value=\"5\" $checked5>Osservazionale con farmaco</option>
						<option value=\"6\" $checked6>Osservazionale senza farmaco e dispositivo</option>
						<option value=\"7\" $checked7>Osservazionale con dispositivo medico</option>
						<option value=\"8\" $checked8>Uso Terapeutico</option>
						<option value=\"10\" $checked10>Studi con impiego di tessuti umani</option>
					</select>
					</td>
					<td class=destra align=\"right\"><b>Stato:</b></td>
					<td class=input><select name='STATO' value=\"{$_GET['STATO']}\">
						<option value=\"\">Tutti</option>
						<!--option value=\"1\" $checked21>Iscrizione</option-->
						<!--option value=\"2\" $checked22>In corso di compilazione</option-->
						<option value=\"3\" $checked23>Segreteria</option>
						<!--option value=\"4\" $checked24>In Integrazione</option-->
						<option value=\"5\" $checked25>In Valutazione</option>
						<option value=\"6\" $checked26>Valutato</option>
						<option value=\"7\" $checked27>Attivato</option>
						<!--option value=\"8\" $checked28>Da Approvare</option-->
						<option value=\"9\" $checked29>Chiuso</option>
					</select>
					</td>
					</tr>
				</td>
				</tr>
				</td>
					</tr>
					<tr>
						<td colspan=4 align=center>
						<!--input type='submit' value='Cerca'>
						<input type='button' value='Cancella tutto' title='Cancella tutti i parametri e la lista dei risultati' onclick=\"window.location='index.php?list={$_GET['list']}&'\"-->
						<br>
						<button class='btn btn-purple btn-sm' type='submit' onclick='submit'><i class='icon-search'></i>Cerca</button>
						<button class='btn btn-grey btn-sm' type='submit' title='Cancella tutti i parametri e la lista dei risultati' onclick=\"window.location='index.php?list={$_GET['list']}&'\"><i class='icon-undo btn-sm'></i>Cancella tutto</button>
						</td>
					</tr>
				</table>
				</form>
				</td>
				
				</tr>
				</table>
				</div>
			<br>";
		}
		
		//$this->body .= $this->percorso;
		
		if ($_GET['list']=="patients_list_UO.xml" && $this->user->profilo=='Segreteria CE'){
			
			$query_centri = "select distinct ID, DESCRIZIONE from CE_VENETO_USERID_CE where userid='{$this->session_vars['remote_userid']}' order by descrizione asc";
			$sql_centri = new query ( $this->conn );
			$sql_centri->exec($query_centri);
			while($sql_centri->get_row()){
				
				if ($_GET['ID_REF_STR']==$sql_centri->row['ID']){
					${checked.$sql_centri->row['ID']}="selected='selected'";
				}
				
				$options.="<option value=\"{$sql_centri->row['ID']}\" ${checked.$sql_centri->row['ID']}>{$sql_centri->row['DESCRIZIONE']}</option>";
			
			}
			
			if ($_GET['SUCCESS']=="yes") $alert="<script type=\"text/javascript\">alert('L\'unita\' operativa e\' stata inserita correttamente')</script>";
						
			$this->percorso.="
				$alert
				<table width=70% align=center border=0>
				<tr>
				
				<td>
				<table>
					<tr>
				<td>
						<button style=\"margin-top: 2px;\" onclick=\"window.location='index.php?insert=UO&'\" type=\"button\" class=\"btn btn-info blue\">
							<i class=\"fa fa-plus bigger-110\"></i>
							Inserisci nuova UO
						</button>
						
						</td>
					</tr>
				</table>
				</td>
				
				<td>
				<table border=0 align=center>
				<form action=\"index.php\" method=\"GET\">
					<tr>
						<td colspan=2 align=\"center\"><b>Ricerca per UO già registrate</b>
						<input type='hidden' name='list' value=\"{$_GET['list']}\">
						</td>
					</tr>
					<tr>
						<td class=destra align=\"right\"><b>Unit&agrave; Operativa: </b></td>
						<td class=input width=\"200\">
							<input type='text' size='30' maxlenght='50' name='S2_DESCR_UO' value=\"{$_GET['S2_DESCR_UO']}\">
						</td>
					</tr>
					<tr>
						<td class=destra align=\"right\"><b>Struttura: </b></td>
						<td class=input>
							<select name='ID_REF_STR'\">
								<option value=\"\">Tutti</option>
								$options
							</select>
						</td>
					</tr>
					</tr>
					<tr>
						<td colspan=4 align=center>
						
						<!--input type='button' value='&lt;&lt;Chiudi' onclick=\"window.opener.location.reload();window.close();\" style=\"color:blue;\"-->
						<!--input type='submit' value='Cerca'-->
						<button type=\"submit\" class=\"btn btn-purple btn-sm\" id=\"button-search\" title=\"Cerca\">
							<span id=\"std-label\"><i class=\"icon-search\"></i>Cerca</span>
						</button>
						<!--input type='button' value='Annulla ricerca' title='Cancella tutti i parametri e la lista dei risultati' onclick=\"window.location='index.php?list={$_GET['list']}&'\"-->
						<button class=\"btn btn-grey btn-sm\" type=\"button\" onclick=\"window.location='index.php?list={$_GET['list']}&'\" title=\"Cancella tutti i parametri e la lista dei risultati\">
							<i class=\"icon-undo btn-sm\"></i>
							Annulla ricerca
						</button>
						<!--input type='button' value='Inserisci nuova UO &gt;&gt;' style=\"color:red;\" onclick=\"window.location='index.php?insert=UO&'\"-->
					</form>
						</td>
					</tr>
				</table>
				</td>
				
				
				</tr>
				</table>
				
			<br><br>";
		}
		
		if ($_GET['list']=="patients_list_PI.xml" && $this->user->profilo=='Segreteria CE'){
			
			$query_centri = "select distinct ID, DESCRIZIONE from CE_VENETO_USERID_CE where userid='{$this->session_vars['remote_userid']}' order by descrizione asc";
			$sql_centri = new query ( $this->conn );
			$sql_centri->exec($query_centri);
			while($sql_centri->get_row()){
				
				if ($_GET['ID_REF_STR']==$sql_centri->row['ID']){
					${checked.$sql_centri->row['ID']}="selected='selected'";
				}
				
				$options.="<option value=\"{$sql_centri->row['ID']}\" ${checked.$sql_centri->row['ID']}>{$sql_centri->row['DESCRIZIONE']}</option>";
			
			}
			
			if ($_GET['SUCCESS']=="yes") $alert="<script type=\"text/javascript\">alert('Il principal Investigator e\' stato inserito correttamente')</script>";
			
			$this->percorso.="
				$alert
				<table width=70% align=center border=0>
				<tr>
				<td>
				<table>
					<tr>
						<td>
						<button style=\"margin-top: 2px;\" onclick=\"window.location='index.php?insert=PI&'\" type=\"button\" class=\"btn btn-info blue\">
							<i class=\"fa fa-plus bigger-110\"></i>
							Inserisci nuovo PI
						</button>
						</td>
					</tr>
				</table>
				</td>
				<td>
				<table border=0 align=center>
				<form action=\"index.php\" method=\"GET\">
					<tr>
						<td colspan=2 align=\"center\"><b>Ricerca per PI già registrati</b>
						<input type='hidden' name='list' value=\"{$_GET['list']}\">
						</td>
					</tr>
					<tr>
						<td class=destra align=\"right\"><b>Principal Investigator: </b></td>
						<td class=input width=\"200\">
							<input type='text' size='30' maxlenght='50' name='S2_PRINC_INV' value=\"{$_GET['S2_PRINC_INV']}\">
						</td>
					</tr>
					<tr>
					<td class=destra align=\"right\"><b>Struttura: </b></td>
					<td class=input><select name='ID_STR'\">
						<option value=\"\">Tutti</option>
						$options
					</select>
					</td>
					</tr>
					</tr>
					<tr>
						<td colspan=4 align=center>
						<!--input type='button' value='&lt;&lt;Chiudi' onclick=\"window.opener.location.reload();window.close();\" style=\"color:blue;\"-->
						<!--input type='submit' value='Cerca'-->
						<button type=\"submit\" class=\"btn btn-purple btn-sm\" id=\"button-search\" title=\"Cerca\">
							<span id=\"std-label\"><i class=\"icon-search\"></i>Cerca</span>
						</button>
						<!--input type='button' value='Annulla ricerca' title='Cancella tutti i parametri e la lista dei risultati' onclick=\"window.location='index.php?list={$_GET['list']}&'\"-->
						<button class=\"btn btn-grey btn-sm\" type=\"button\" onclick=\"window.location='index.php?list={$_GET['list']}&'\" title=\"Cancella tutti i parametri e la lista dei risultati\">
							<i class=\"icon-undo btn-sm\"></i>
							Annulla ricerca
						</button>
						<!--input type='button' value='Inserisci nuovo PI &gt;&gt;'  style=\"color:red;\"  onclick=\"window.location='index.php?insert=PI&'\"-->
					</form>
						</td>
					</tr>
				</table>
				</td>
				
				</tr>
				</table>
				
			<br><br>";
		}		
		
		$this->body .=$specchietto_ricerca;
		$this->body .= $list_o->list_html ( $this->session_vars );
		$this->body .="<script>$('#table1').addClass('table table-striped table-bordered table-hover');</script>";
		
		
		
		//$legend = new legend ( $this->config_service );
		//$this->body .= $legend->html_legend_lista;
	}


	
	#Stringhe testuali
	function testo($testo){
		//$txt = parent::testo($testo);
		$this->testi['Home']="Home";
		$this->testi['Vista Paziente']="Dettaglio studio";
		$this->testi['Lista completa'] =""; #"Lista completa delle schede dello studio";
		$this->testi ['userNotCenter'] = "UTENTE NON ABILITATO ALLA VISIONE DI QUESTO STUDIO";
		#LUIGI: controllo sui diritti di cancellazione
		$this->testi ['NOTDELETABLE'] = "Non si hanno i diritti necessari per cancellare la scheda o la visita progressiva";
		#LUIGI: controllo sui diritti di creazione
		$this->testi ['NOTCREABLE'] = "Non si hanno i diritti necessari per creare la visita progressiva";
		$this->testi ['userNotForm'] = "UTENTE NON ABILITATO ALLA VISIONE DI QUESTA SCHEDA";
		$this->testi ['userNotHaveCenter'] = "UTENTE NON ABILITATO ALLA VISIONE DI QUESTO STUDIO";
		
		return parent::testo($testo);
		
		
	}
	
	
	function crea_istruttoria_ts(){
		
		$sql_query_info = "select * from CE_INFO_STUDIO where id_stud='{$this->pk_service}'";
		$sql_info = new query ( $this->conn );
		$sql_info->get_row ( $sql_query_info );
		
		#GIULIO - da sistemare, non va bene per i dispositivi medici
		if ($sql_info->row['FASE_SPER']==1) $faseI='Si\''; else $faseI='No';
		if ($sql_info->row['ETA_VOL']==1) $sani='Si\''; else $sani='No';
		if ($sql_info->row['ETA_INCA']==1) $inca='Si\''; else $inca='No';
		if ($sql_info->row['MINORI']>0) $minori='Si\''; else $minori='No';
		
		if ($sql_info->row['FASE_SPER']=="-9944") $sql_info->row['FASE_SPER']='Non applicabile';
		
		$sql_query_ce = "select * from CE_CENTRILOCALI where id_stud='{$this->pk_service}' and progr={$_GET['VISITNUM_PROGR']}+1";
		$sql_ce = new query ( $this->conn );
		$sql_ce->get_row ( $sql_query_ce );
		
		$sql_query_ce2 = "select * from CE_LOCALE01 where id_stud='{$this->pk_service}' and visitnum_progr={$_GET['VISITNUM_PROGR']}";
		$sql_ce2 = new query ( $this->conn );
		$sql_ce2->get_row ( $sql_query_ce2 );
		
		$query_reg = "select * from CE_REGISTRAZIONE where id_stud='{$this->pk_service}'";
		$sql_reg = new query ( $this->conn );
		$sql_reg->get_row ( $query_reg );
		
		#Interventistico/Osservazionale/Uso Terapeurico/Tessuti Umani con FARMACO
		if($sql_reg->row['TIPO_SPER']==1 || $sql_reg->row['TIPO_SPER']==5 || $sql_reg->row['TIPO_SPER']==8 || $sql_reg->row['TIPO_SPER']==10){
			$query_farmaco = "select * from CE_LISTA_FARMACI where id_stud='{$this->pk_service}'";
			$sql_farmaco = new query ( $this->conn );
			$sql_farmaco->exec($query_farmaco);
			while($sql_farmaco->get_row()){
				$farmaci.="
				<p>Principio attivo: <b>{$sql_farmaco->row['OGGETTO_STUDIO']}</b></p>
				<p>Specialit&agrave; medicinale: <b>{$sql_farmaco->row['SPECIALITA']}</b></p>
				<p>Meccanismo d'azione:</p>
				<p>Indicazione/i registrata/e:</p>
				<p>Posologia e durata del trattamento autorizzate:</p>
				<p>Posologia e durata del trattamento previste dallo studio:</p>
				<p>ATC: <b>{$sql_farmaco->row['ATC']}</b></p>
				<p>AIC o  fase di sviluppo pi&ugrave; avanzata raggiunta (se AIC specificare classificazione/classe rimborsabilit&agrave;): <b>{$sql_farmaco->row['AIC']}</b></p>
				<p>PTO/PTORV:</p>
				<p>Dichiarazione fornitura gratuita/rimborso:</p>
				<p>Specificato in convenzione:</p>
				<br/>
				";
			}
			$farmaci.="<p>Obblighi previsti dal D. Lgs. 211/2003 in merito alla farmacovigilanza:</p>";
		}
		#Interventistico/Osservazionale con TRATTAMENTO (senza farmaco e dispositivo)
		if($sql_reg->row['TIPO_SPER']==2 || $sql_reg->row['TIPO_SPER']==6){
			$query_trat = "select * from CE_LISTA_TRATTAMENTI where id_stud='{$this->pk_service}'";
			$sql_trat = new query ( $this->conn );
			$sql_trat->exec($query_trat);
			while($sql_trat->get_row()){
				$trattamenti.="
				<p>Trattamento in studio: <b>{$sql_trat->row['D_TIPO_TRAT']}</b></p>
				<p>Se altro, specificare: <b>{$sql_trat->row['ALTROSPEC']}</b></p>
				<p>Descrizione trattamento: <b>{$sql_trat->row['DESCR_TRAT']}</b></p>
				<br/>
				";
			}
		}
		#Interventistico/Osservazionale/terapeutico con DISPOSITIVO
		if($sql_reg->row['TIPO_SPER']==3 || $sql_reg->row['TIPO_SPER']==7 || $sql_reg->row['TIPO_SPER']==9){
			$query_disp = "select * from CE_LISTA_DISPOSITIVI where id_stud='{$this->pk_service}'";
			$sql_disp = new query ( $this->conn );
			$sql_disp->exec($query_disp);
			while($sql_disp->get_row()){
				$dispositivi.="
				<p>Nome del dispositivo: <b>{$sql_disp->row['DISPOSITIVO']}</b></p>
				<p>Classe: <b>{$sql_disp->row['D_CLASSE_RISCHIODM']}</b></p>
				<p>Marcatura CE: <b>{$sql_disp->row['D_MARCHIOCE']}</b></p>
				<p>Data termine validit&agrave; marcatura CE:</p>
				<p>Destinazione d'uso autorizzata:</p>
				<p>Destinazione d'uso prevista dal protocollo:</p>
				<p>Modalit&agrave; d'uso prevista da scheda tecnica:</p>
				<p>Notifica indagine al Ministero della Salute:</p>
				<p>Dichiarazione di fornitura gratuita:</p>
				<br>
				<br/>
				";
			}
			$dispositivi.="<p>Obblighi previsti in merito alla vigilanza:</p>";
		}
		
		$query_ss = "select * from CE_SOTTOSTUDI where id_stud='{$this->pk_service}'";
		$sql_ss = new query ( $this->conn );
		$sql_ss->exec($query_ss);
		while($sql_ss->get_row()){
			$sottostudi.="
			<p>Sottostudio facoltativo (s&igrave;/no):</p>
			<p>Tipo del sottostudio: <b>{$sql_ss->row['D_TIPO']}</b> </p>
			<p>Titolo del sottostudio: <b>{$sql_ss->row['TITOLO']}</b> </p>
			<p>Razionale del sottostudio: <b>{$sql_ss->row['OBIETTIVI']}</b> </p>
			<p>Coinvolgimento richiesto per il paziente:</p>
			<p>Luogo di conservazione dei campioni:</p>
			<p>Durata di conservazione dei campioni:</p>
			<p>Possibilit&agrave; di ritiro dal sottostudio di genetica:</p>
			<p>Possibilit&agrave; di richiedere la distruzione del campione:</p>
			<br/>
			";
		}
		
		#dati verificadoc
			 $sql_query_ver = "select * from ce_reginvio where id_stud={$_GET['ID_STUD']} and VISITNUM_PROGR={$_GET['VISITNUM_PROGR']} and progr = 1";
			 $sql_ver = new query ( $this->conn );
			 $sql_ver->set_sql ( $sql_query_ver );
			 $sql_ver->exec ();
			 $sql_ver->get_row ();	
		
		$txt="
		<p><u>Sintesi studio a cura della Segreteria del Comitato Etico</u></p>
		<br>
		<fieldset>Studio: \"{$sql_info->row['TITOLO_PROT']}\" - N. Prog. {$sql_ver->row['DELIB_NUM']}</fieldset> 
		<br>
		<p align=\"center\"><b><u>CENTRO RICHIEDENTE</u></b></p>
		<br>
		<p>Struttura: {$sql_ce->row['D_CENTRO']}</p>
		<p>Dipartimento: {$sql_ce->row['D_DIPARTIMENTO']}</p>
		<p>Sperimentatore principale: {$sql_ce->row['D_PRINC_INV']}</p>
		<p>Unit&agrave; operativa: {$sql_ce->row['D_UNITA_OP']}</p>
		<p align=\"center\"><b><u>CARATTERISTICHE STUDIO</u></b></p>
		<p>Richiesto Parere Unico: {$sql_ce2->row['D_COORDINATORE']}</p>
		<p>Eventuali pareri sospensivi/negativi di altri CE:</p>
		<p>Inserimento in OsSC/RSO:</p>
		<table width=\"98%\">
			<tr>
				<td width=\"60%\">
				Studio di fase I: $faseI
				</td>
				<td width=\"40%\" colspan=\"2\">
				Parere ISS:
				</td>
			</tr>
			<tr>
				<td width=\"60%\">
				Studio con derivati del sangue:
				</td>
				<td width=\"40%\"  colspan=\"2\">
				Parere ISS:
				</td>
			</tr>
			<tr>
				<td width=\"60%\">
				Studio con medicinali per terapia genica, terapia cellulare somatica<br>(inclusa la terapia cellulare xenogenica), medicinali contenenti OGM,<br>radio farmaci:
				</td>
				<td width=\"20%\">
				Parere AIFA/MS:
				</td>
				<td width=\"20%\">
				Copertura assicurativa di 10 anni:
				</td>
			</tr>
		</table>
		<p>Fase dello studio: {$sql_info->row['FASE_SPER']}</p>
		<p>Sintesi delle premesse teoriche/razionale dello studio (con contestualizzazione dello studio rispetto all'attuale pratica clinica):</p>
		<p>Disegno dello studio: {$sql_info->row['DISEGNO']}</p>
		<p>Principali criteri di inclusione: {$sql_info->row['INCLUSIONE']}</p>
		<p>Principali criteri di esclusione:</p>
		<p>Obiettivo principale: {$sql_info->row['OBIETTIVO']}</p>
		<p>Obiettivi secondari:</p>
		<p>End-point I: {$sql_info->row['D_ENDPOINT']}</p>
		<p>End-point II:</p>
		<p>Studio di superiorit&agrave;/equivalenza/non inferiorit&agrave; (esplicitare anche l'ipotesi primaria utilizzata per la stima campionaria e, per gli studi di equivalenza/non inferiorit&agrave;, il vantaggio aggiuntivo per il paziente):</p>
		<p>Elementi principali dell'analisi statistica:</p>
		<p>Durata dello studio e conclusione se diversa dall'ultima visita dell'ultimo soggetto:</p>
		<table width=\"98%\">
			<tr>
				<td width=\"50%\">
				N&deg; di soggetti da arruolare nel centro: {$sql_ce2->row['PAZ_NUM']}
				</td>
				<td width=\"25%\">
				in Italia:
				</td>
				<td width=\"25%\">
				nel mondo:
				</td>
			</tr>
		</table>
		<p>Arruolamento competitivo:</p>
		<p>Conformit&agrave; a linee guida EMA/FDA  in materia (riportando le referenze dei documenti dell'Autorit&agrave; Regolatoria cui si fa riferimento)</p>
		<p>POPOLAZIONI PARTICOLARI:</p>
		<table width=\"98%\">
			<tr>
				<td width=\"60%\">
				Arruolamento di minori: $minori
				</td>
				<td width=\"40%\">
				Copertura assicurativa di 10 anni:
				</td>
			</tr>
			<tr>
				<td width=\"100%\" colspan=\"2\">
				Arruolamento di soggetti incapaci di intendere e volere: $inca
				</td>
			</tr>
			<tr>
				<td width=\"60%\">
				Arruolamento di volontari sani: $sani
				</td>
				<td width=\"40%\">
				Indennizzo previsto:
				</td>
			</tr>
		</table>
		<p>Vincoli alla diffusione e pubblicazione dei risultati della sperimentazione conformi a quanto previsto dall'art. 5, comma 3, punto c) del D.M. 12 maggio 2006:</p>
		<br>
		
		
		<p align=\"center\"><b><u>FARMACO/I IN STUDIO - IMP</u></b></p>
		$farmaci
		<br>
		
		<p align=\"center\"><b><u>TRATTAMENTI IN STUDIO</u></b></p>
		$trattamenti
		<br>
		
		<p align=\"center\"><b><u>DISPOSITIVI MEDICI IN STUDIO</u></b></p>
		$dispositivi
		<br>
		
		
		<p align=\"center\"><b><u>SOTTOSTUDI DI GENETICA e/o altri sottostudi</u></b></p>
		$sottostudi
		<br>
		
		
		<p align=\"center\"><b><u>INFORMATIVE AL PAZIENTE</u></b></p>
		<p><b><u>Informativa studio di base</u></b></p>
		<p>Informativa e consenso alla partecipazione allo studio:</p>
		<p>Informativa e consenso al trattamento dei dati personali:</p>
		<p>Riferimento a massimali e durata di copertura della polizza assicurativa:</p>
		<p>Firma rappresentante legale:</p>
		<p>Firma dei genitori:</p>
		<p>Note al testo:</p>
		<br>
		<p><b><u>Informativa sottostudio di genetica o altro sottostudio</u></b></p>
		<p>Informativa e consenso alla partecipazione allo studio:</p>
		<p>Informativa e consenso al trattamento dei dati personali:</p>
		<p>Riferimento a massimali e durata di copertura della polizza assicurativa:</p>
		<p>Firma rappresentante legale:</p>
		<p>Firma dei genitori:</p>
		<p>Note al testo:</p>
		<br>
		<p><b><u>Materiale informativo al pubblico</u></b></p>
		<p>indicazione della struttura in cui si svolge la sperimentazione:</p>
		<p>citazione del farmaco e/o della sostanza in sperimentazione:</p>
		<p>rispetto delle norme sulla pubblicit&agrave; dei medicinali:</p>
		<br>
		
		
		<p align=\"center\"><b><u>LETTERA AL MEDICO CURANTE</u></b></p>
		<p>Note al testo:</p>
		
		
		<p align=\"center\"><b><u>ASPETTI ASSICURATIVI</u></b></p>
		<i>La conformit&agrave; ai requisiti del D.M. 14/07/09 della polizza assicurativa &egrave; stata preventivamente verificata da</i>
		<p>Polizza assicurativa con specifico riferimento allo studio:</p>
		<p>Polizza assicurativa con specifico riferimento allo studio:</p>
		<p>Termini per la manifestazione dei danni e per la presentazione delle richieste di risarcimento (rispettivamente almeno 24 e 36 mesi dalla data di conclusione dello studio in Italia - LPLV oppure pi&ugrave; lungo in caso di sperimentazioni potenzialmente idonee a causare danni evidenziabili a maggior distanza di tempo):</p>
		<p>Massimali (almeno 1.000.000 euro per persona e per ogni singolo protocollo non inferiori a: a) 5.000.000 euro se i soggetti coinvolti nella sperimentazione in Italia non sono pi&ugrave; di 50; b) 7.500.000 euro se i soggetti coinvolti nella sperimentazione in Italia sono pi&ugrave; di 50 ma meno di 200; c) 10.000.000 euro se i soggetti coinvolti nella sperimentazione in Italia sono pi&ugrave; di 200.):</p>
		<p>Franchigia:</p>
		
		
		<p align=\"center\"><b><u>ASPETTI ECONOMICI</u></b></p>
		<p>Compenso previsto a paziente (se si tratta di studio profit):</p>
		<p>Spese previste per lo studio, con indicazione di eventuali fondi a copertura (se si tratta di studio no profit): </p>
		<p>Previsto il ricorso a laboratori centrali per la valutazione di alcuni parametri e/o la delega a strutture terze per lo svolgimento di alcune funzioni del promotore:</p>
		<p>Descritte le modalit&agrave; di accesso dei pazienti non ricoverati agli esami / visite:</p>
		<p>Tempo dedicato (ore/paziente) dagli sperimentatori:</p>
		<p>In / fuori orario di servizio:</p>
		<p>Materiali ed attrezzature necessari per l'esecuzione dello studio:</p>
		<p>Comodati d'uso: </p>
		<p>Prestazioni/esami strumentali/di laboratorio previsti specificamente per lo studio:</p>
		<p>Coinvolgimento Farmacia Ospedaliera:</p>
		<p>Coinvolgimento altri UU.OO./Servizi:</p>
		<p>Previsione impiego dei proventi (se si tratta di studio profit): </p>
		<p>Previsione impiego finanziamento dedicato (se si tratta di studio no profit):</p>
		<p>Ente finanziatore:</p>
		
		<p align=\"center\"><b><u>ASPETTI PARTICOLARI/CITICITA' RILEVATE</u></b></p>
		<br>
		<br>
		<br>
		<br>
		<br>
		
		";
		
		return $txt;
	}
	
	
	/* Ricerca STUDI */
	function SearchPage(){
		//print_r($this->session_vars);
		$dir=$_SERVER['PATH_TRANSLATED'];
		//die("CERCA!");
		$dir=preg_replace("/\/index.php/", "", $dir);
		//$filetxt = file_get_contents($dir.'/template.htm');
		switch ($this->session_vars['FORM']){
			case 1:
				$file_form=$this->xml_dir."/search_studio.xml";
				$in['list']=$list="patients_list_search.xml";
				break;
			case 2:
				$file_form=$this->xml_dir."/search_centro.xml";
				$in['list']=$list="patients_list_search_centro.xml";
				break;
			case 3:
				$file_form=$this->xml_dir."/search_studio.xml";
				$in['list']=$list="patients_list_search_{$this->session_vars['WFact']}.xml";
				break;
			case 4:
				$file_form=$this->xml_dir."/search_centro.xml";
				$in['list']=$list="patients_list_search_centro_{$this->session_vars['WFact']}.xml";
				break;
				
		}
		$xml_form=new xml_form();

		$xml_form->xml_form_by_file($file_form);
		$xml_form->open_form();
		$body.=$xml_form->body;
		// print_r($this->session_vars);
		// /16/03/2009 Giorgio Delsignore : Bisogna togliere la globale!!!!
		global $in;
		$in=$this->session_vars;
		//echo "<br/>";
		//$in['S_FROM_DT_REGISTRAZIONE_DT'] = $in['S_FROM_DT_REGISTRAZIONE_DTD'].$in['S_FROM_DT_REGISTRAZIONE_DTM'].$in['S_FROM_DT_REGISTRAZIONE_DTY'];
		//$in['S_TO_DT_REGISTRAZIONE_DT'] = $in['S_TO_DT_REGISTRAZIONE_DTD'].$in['S_TO_DT_REGISTRAZIONE_DTM'].$in['S_TO_DT_REGISTRAZIONE_DTY'];
		//print_r($in);
		//echo "<br/>";
		//$in['list']=$list="patients_list_search.xml";
		$list_o=new xml_list($this->xml_dir."/".$list);
		if (isset($this->session_vars['TSEARCH'])){
			$body.=$list_o->list_html();
		}
		$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
		$script="<script type=\"text/javascript\">
		  function invia_f()
		  {
		   f=document.forms[0];
		   el=f.elements;
		   if(f.ID_STUD && !IsNumeric(f.ID_STUD.value)) {
		   		alert(\"Il codice dello studio deve essere numerico\");
		   		f.ID_STUD.focus();
		   		f.ID_STUD.value='';
		   		return false;
		   }
		   specifiche='A=ON&L=1&F=0';
		   
		   if(el['S_FROM_DT_REGISTRAZIONE_DT'] && el['S_TO_DT_REGISTRAZIONE_DT']){
		   c1=''+
		   '<<fd00###S_FROM_DT_REGISTRAZIONE_DT###Registrato da>>'+
		   '<<fd00###S_TO_DT_REGISTRAZIONE_DT###Registrato a>>'+
		   '';
		   
		   rc=contr(c1,specifiche);
		   if (rc) {return false}
		   
		   }
		   
		   document.forms[0].TSEARCH.value='1';
		   document.forms[0].action='index.php';
		   document.forms[0].submit();
		   }
		 </script>
		  ";
		$codice_sis=$remote_userid-0;
		$user_name="<p align=right><br><br><br>";
		//echo "<hr>$nome_user";
		$nome_user=str_replace("\\'","'",$nome_user);

		$this->percorso = $this->breadcrumb("search");
		//$body = $this->percorso . $body;

		$this->body=$body;
		$this->script=$script;
	}
	
	
	function SendMailSgr($mode){
		
		$query_info_ce="select ID_CE from ana_utenti_2 where userid = '{$this->session_vars['remote_userid']}' ";
		$sql_info_ce=new query($this->conn); 
		$sql_info_ce->exec($query_info_ce);
		$sql_info_ce->get_row();
		
		$sql_query="select * from ana_utenti_2 where id_ce = {$sql_info_ce->row['ID_CE']} and PROFILO='SGR'";
		$sql=new query($this->conn); 
		$sql->exec($sql_query);
		
		$to="";
		while($sql->get_row()){
			if ($sql->row ['EMAIL']!=''){
					$to.= $sql->row ['EMAIL'];
					$to.=",";
			}
		}
		
		
		#Metto in cc il nucleo che ha generato l'invio
		$query_email = "select * from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}'";
		$sql_mail=new query($this->conn);
		$sql_mail->exec($query_email);
		$sql_mail->get_row();
		$cc=$sql_mail->row['EMAIL'];
		$nucleo=$sql_mail->row['AZIENDA_ENTE'];
		
		$sql_query_info_studio = "select * from CE_INFO_STUDIO where id_stud={$this->pk_service}";
		$sql_info_studio = new query ( $this->conn );
		$sql_info_studio->get_row ( $sql_query_info_studio );
			
		$email_from="comitati-etici-toscana@no-reply.it";
			
			#Invio studio
			if($mode==1){
				$oggetto="Nucleo $nucleo - Invio studio";
				$testo_mail.="Il nucleo $nucleo ha inviato lo studio '{$sql_info_studio->row['TITOLO_PROT']}'.<br> E' possibile visualizzarne i dettagli tramite il seguente link:<br> <a href=\"https://{$_SERVER['HTTP_HOST']}/uxmr/index.php?&exams=visite_exam.xml&ID_STUD={$this->pk_service}\">Vai allo studio</a>&nbsp;";
			}
			
			#Invio dati centro specifici
			if($mode==2){
				$oggetto="Nucleo $nucleo - Invio dati centro specifici";
				$testo_mail.="Il nucleo $nucleo ha inviato i dati centro specifici per lo studio '{$sql_info_studio->row['TITOLO_PROT']}'.<br> E' possibile visualizzare i dettagli tramite il seguente link:<br> <a href=\"https://{$_SERVER['HTTP_HOST']}/uxmr/index.php?&exams=visite_exam.xml&ID_STUD={$this->pk_service}\">Vai allo studio</a>&nbsp;";
			}
			
			#Invio dati centro specifici
			if($mode==3){
				$oggetto="Nucleo $nucleo - Risposta richiesta di integrazione";
				$testo_mail.="Il nucleo $nucleo ha integrato lo studio '{$sql_info_studio->row['TITOLO_PROT']}'.<br> E' possibile visualizzarne i dettagli tramite il seguente link:<br> <a href=\"https://{$_SERVER['HTTP_HOST']}/uxmr/index.php?&exams=visite_exam.xml&ID_STUD={$this->pk_service}\">Vai allo studio</a>&nbsp;";
			}
		  
			
			$bcc="g.contino@cineca.it";
			send_email($to, $email_from, $email_from, $oggetto, $testo_mail, null, false, $cc, $bcc);
			
			return;
		
		}
		
	function SendMailNcr($mode){
	
	$sql_query="select * from ana_utenti_2 where userid='{$this->dettaglio['USERID_INS']}' or userid in(
	SELECT
	userid
	FROM
	  ce_veneto_nucleo_userid
	WHERE
	  id_nucleo=
	  (
	    SELECT
	      id_nucleo
	    FROM
	      ce_veneto_nucleo
	    WHERE
	      id_str=
	      (
	        SELECT
	          centro
	        FROM
	          ce_centrilocali
	        WHERE
	          id_stud='{$this->pk_service}'
	        AND progr={$this->session_vars['VISITNUM_PROGR']}+1
	      )
	  )
	)";
	$sql=new query($this->conn); 
	$sql->exec($sql_query);
	
	$to="";
	while($sql->get_row()){
		if ($sql->row ['EMAIL']!=''){
				$to.= $sql->row ['EMAIL'];
				$to.=",";
		}
	}
	//echo "okokok";
	//var_dump ($this);
	//die($to);
	
	
	#Metto in cc la segreteria che ha generato l'invio
	$query_email = "select * from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}'";
	$sql_mail=new query($this->conn);
	$sql_mail->exec($query_email);
	$sql_mail->get_row();
	$cc=$sql_mail->row['EMAIL'];
	$segreteria=$sql_mail->row['AZIENDA_ENTE'];
	
	$sql_query_info_studio = "select * from CE_INFO_STUDIO where id_stud={$this->pk_service}";
	$sql_info_studio = new query ( $this->conn );
	$sql_info_studio->get_row ( $sql_query_info_studio );
		
	$email_from="comitati-etici-toscana@no-reply.it";
		
		#Invio richiesta integrazione
		if($mode==1){
			$oggetto="Segreteria $segreteria - Richiesta integrazione";
			$testo_mail.="La segreteria $segreteria ha inviato una richiesta di integrazione per lo studio '{$sql_info_studio->row['TITOLO_PROT']}'.<br> E' possibile visualizzarne i dettagli tramite il seguente link:<br> <a href=\"https://{$_SERVER['HTTP_HOST']}/uxmr/index.php?&exams=visite_exam.xml&ID_STUD={$this->pk_service}\">Vai allo studio</a>&nbsp;";
		}
		
		#Invio parere sospensivo
		if($mode==2){
			$oggetto="Segreteria $segreteria - notifica di parere sospensivo";
			$testo_mail.="La segreteria $segreteria ha inviato parere sospensivo per lo studio '{$sql_info_studio->row['TITOLO_PROT']}'.<br> E' possibile visualizzarne i dettagli tramite il seguente link:<br> <a href=\"https://{$_SERVER['HTTP_HOST']}/uxmr/index.php?&exams=visite_exam.xml&ID_STUD={$this->pk_service}\">Vai allo studio</a>&nbsp;";
		}
		
		#Invio parere positivo
		if($mode==3){
			$oggetto="Segreteria $segreteria - notifica di parere positivo";
			$testo_mail.="La segreteria $segreteria ha inviato parere positivo per lo studio '{$sql_info_studio->row['TITOLO_PROT']}'.<br> E' possibile visualizzarne i dettagli tramite il seguente link:<br> <a href=\"https://{$_SERVER['HTTP_HOST']}/uxmr/index.php?&exams=visite_exam.xml&ID_STUD={$this->pk_service}\">Vai allo studio</a>&nbsp;";
		}
	  
		
		$bcc="g.contino@cineca.it";
		send_email($to, $email_from, $email_from, $oggetto, $testo_mail, null, false, $cc, $bcc);
		
		return;
	
	}
	
	function SendMailCEP(){
		
		$sql_query="select * from ana_utenti_2 where id_ce = 4 and PROFILO='SGR'";
		$sql=new query($this->conn); 
		$sql->exec($sql_query);
		
		$to="";
		while($sql->get_row()){
			if ($sql->row ['EMAIL']!=''){
					$to.= $sql->row ['EMAIL'];
					$to.=",";
			}
		}
		
		#Metto in cc l'utente che ha generato l'invio
		$query_email = "select * from ana_utenti_2 where userid='{$this->session_vars['remote_userid']}'";
		$sql_mail=new query($this->conn);
		$sql_mail->exec($query_email);
		$sql_mail->get_row();
		$cc=$sql_mail->row['EMAIL'];
		$utente=$sql_mail->row['AZIENDA_ENTE'];
		
		$sql_query_info_studio = "select * from CE_INFO_STUDIO where id_stud={$this->pk_service}";
		$sql_info_studio = new query ( $this->conn );
		$sql_info_studio->get_row ( $sql_query_info_studio );
			
		$email_from="comitati-etici-toscana@no-reply.it";

		$oggetto="Richiesta di consulenza CEP da $utente";
		$testo_mail.="Il $utente ha richiesto una consulenza CEP per lo studio ID={$sql_info_studio->row['ID_STUD']}<br>
									Titolo: '{$sql_info_studio->row['TITOLO_PROT']}'.<br> E' possibile visualizzarne i dettagli tramite il seguente link:<br> <a href=\"https://{$_SERVER['HTTP_HOST']}/uxmr/index.php?&exams=visite_exam.xml&ID_STUD={$this->pk_service}\">Vai allo studio</a>&nbsp;";
		
		$bcc="g.contino@cineca.it";
		send_email($to, $email_from, $email_from, $oggetto, $testo_mail, null, false, $cc, $bcc);
		
	}	
	
	
	
//	function openVerificaDoc(){
//		Logger::send('openVerificaDoc');
//		if($this->session_vars['DEBUG']==1) echo "openVerificaDoc";
//		//Inserisco schede di verifica documentazione se non gia' presenti
//		$pkid = $this->pk_service;
//		$curvnum = 0; //Visita principale (registrazione)
//		$vprogr = 0; //Visita singola
//		$curesam = 10; //Centri partecipanti
//		$keyField = "PC_KEY";
//		$centerField = "CENTRO";
//		$sperimField = "PRINC_INV";
//		//echo("Open Valutabile");
//		//Apertura schede parere progressive e centro specifiche
//		$progs = $this->getEsamProgs($pkid,$curvnum,$vprogr,$curesam);
//		$keys = array();
//		$centri = array();
//		$cdesc = array();
//		$sperim = array();
//		$sdesc = array();
//		//echo "<pre>";
//		//print_r($progs);
//		//echo "</pre>";
//		foreach ($progs as $p){
//			$row = $this->loadEsamProgr($pkid,$curvnum,$vprogr,$curesam,$p);
//			if (!in_array($row[$keyField],$keys)){
//				$c = $row[$centerField];
//				//echo "STEP: ".$row[$keyField]."<br/>";
//				if ($c){
//					$keys[] = $row[$keyField];
//					$centri[$p] = $c;
//					$cdesc[$p] = $row["D_".$centerField];
//					$sperim[$p] = $row[$sperimField];
//					$sdesc[$p] = $row["D_".$sperimField];
//				}
//			}
//		}
//		//Recupero centri da aprire (visita documentazione centro specifica chiusa)
//		$progsDocs = $this->getMaxVprogr($pkid,1);
//		for ($i = 0; $i<=$progsDocs; $i++){
//			if (!$this->CheckVisitProgrClosedSpecific($pkid,1,$i)){
//				$row = $this->loadEsamProgr($pkid,1,$i,22,1);
//				$diff = array($row[$keyField]);
//				$keys = array_diff($keys,$diff);
//			}
//		}
//		
//		//echo "<br/>";
//		//print_r($keys);
//		//die("F: ".$found);
//		//recupero le visite progressive x poi verificare la presenza dei centri
//		$parvisit = 2; //Id visita per la verifica documentazione (che devo aprire o modificare)
//		$paresam = 1; //Esam parere
//		$vprogs = $this->getMaxVprogr($pkid,$parvisit);
//		//$vprogs++;
//		foreach ($keys as $k){
//			$found = false;
//			$vpfound = -1;
//			for ($i = 0; $i<=$vprogs; $i++){											
//				$row = $this->loadEsamProgr($pkid,$parvisit,$i,$paresam,1); //Forzo il progressivo a 1 (se c'e', almeno il primo c'e' e mi basta quello)
//				if ($row[$keyField] == $k){
//					$found = true;
//					$vpfound = $i;
//					break;
//				}
//			}
//			//echo "FOUND ($k):".$found;
//			$ovnum = $parvisit;
//			$nextvprogr = $this->getMaxVprogr($pkid,$ovnum);
//			$ep = 0;
//			if (!$found){
//				$ovprogr = $nextvprogr+1;
//				$ep = 1;
//			}else{
//				$ovprogr = $vpfound;
//				//Controlla chiusura ultima scheda progressiva, se e' chiusa devo aggiungere il prossimo progressivo
//				$ep = $this->getMaxProgr($pkid,$ovnum,$ovprogr,1);
//				//Controllo scheda inviata
//				$sql = "select fine from {$this->service}_coordinate where {$this->xmr->pk_service}={$pkid} and visitnum=$ovnum and visitnum_progr = $ovprogr and esam=1 and progr = $ep ";
//				$query = new query($this->conn);
//				//echo $sql;
//				$query->exec($sql);
//				$vc = false;
//				while ($query->get_row()){
//					if ($query->row['FINE']){
//						$vc = true;
//					}
//				}
//				//$row = $this->loadEsamProgr($this->pk_service,1,$p,22,1);
//				//$c = $row[$centerField];
//				//die("VC: $vc");
//				if ($vc){
//					$ep++;
//				}else{
//					$ep = 0;
//				}
//			}
//			//echo "<hr/>$ep<hr/>";
//			if ($ep){
//				$this->openEsamProgr($pkid,$ovnum,$ovprogr,1,$ep,true,false);
//				//update campi pre-compilati
//				$fields = array();
//				$fields[$keyField] = $k;
//				$fields['CENTRO'] = $centri[$k];
//				$fields['PRINC_INV'] = $sperim[$k];
//				$fields['D_CENTRO'] = str_replace("'","''",$cdesc[$k]);
//				$fields['D_PRINC_INV'] = str_replace("'","''",$sdesc[$k]);
//				//print_r($fields);
//				//print_r($in);
//				//die();
//				$this->updateEsamProgr($pkid,$ovnum,$ovprogr,1,$ep,$fields);
//			}		
//		}
//		//die("FINE");
//		$this->conn->commit();
//	}
	
	function openVerificaDocSingle($pkid, $vnum, $vprogr){
		if($this->session_vars['DEBUG']==1) {
			if($this->session_vars['DEBUG']==1) echo "openVerificaDocSingle($pkid, $vnum, $vprogr)";
			Logger::send('openVerificaDocSingle('.$pkid.','.$vnum.','.$vprogr.')');
		}

		$keyField = "PC_KEY";
		$centerField = "CENTRO";
		$sperimField = "PRINC_INV";
		$row = $this->loadEsamProgr($pkid,$vnum,$vprogr,22,1);
		$k = $row[$keyField];
		$c = $row[$centerField];
		$cd = $row["D_".$centerField];
		$s = $row[$sperimField];
		if($row['PRINC_INV']=='-9944')$row['D_PRINC_INV']=$row['SPEC_PI'];
		$sd = $row["D_".$sperimField];
		
		$ovnum = 2;
		$esam = 1;
		$p = $this->getMaxProgr($pkid,$ovnum,$vprogr,$esam); #Controllo se c'e' gia' una scheda istruttoria
		$row = $this->loadEsamProgr($pkid,$ovnum,$vprogr,$esam,$p); #Carico i dati dell'ultima scheda istruttoria
		$oprogr=$p;
		
		if($this->session_vars['DEBUG']==1) echo "<br>p=".$p;
		
		 #Se c'e' gia' una scheda istruttoria devo inserire quella successiva
		 if ($p){
		 	if($this->session_vars['DEBUG']==1) echo "<br/>Inserisco la prossima scheda di istruttoria per questo centro";
			$oprogr++;
		 }
		
		 #Se non c'e' alcuna scaheda istruttoria -> devo inserire la prima
		 if ($p==''){
			if($this->session_vars['DEBUG']==1) echo "<br/>Inserisco la prima scheda di istruttoria per questo centro";
			$oprogr = 1;
		}
		
		$this->openEsamProgr($pkid,$ovnum,$vprogr,$esam,$oprogr,true,false);
			#update campi pre-compilati
			$fields = array();
			$fields[$keyField] = $k;
			$fields['CENTRO'] = $c;
			$fields['D_CENTRO'] = str_replace("'","''",$cd);
			$fields['PRINC_INV'] = $s;
			$fields['D_PRINC_INV'] = str_replace("'","''",$sd);
			$this->updateEsamProgr($pkid,$ovnum,$vprogr,$esam,$oprogr,$fields);
		
		$this->conn->commit();
		//die('fine <b>openVerificaDocSingle</b>');
	}
	
	//////// --- WORKFLOW
	function StatusChangePostOperation($dest) {
//		//$dest e' l'id dello stato destinazione
//		//Operazioni dopo transizione di stato nel WF
		$sql=new query($this->conn); 
//		define("STATO_SEGRETERIA","3");
		define("STATO_INTEGRAZIONE","4");
//		define("STATO_VALUTABILE","5");
//		define("STATO_VALUTATO","6"); //Macrostato
		define("STATO_CHIUSO_RITIRATO","9");
		switch ($dest){
//			case STATO_SEGRETERIA:
//				//Apro la visita numero 2 se non e' gia' aperta
//				/*
//				$vid = 2;
//				//Controllo visita aperta
//				$open = array();
//				$open[] = 1;
//				//TODO: Apertura scheda progressiva...
//				$this->openVisit($vid,$open);
//				*/
//				$this->openVerificaDoc();
//				//Inserimento data in registrazione
//				$table = "REGISTRAZIONE";
//				$field = "SEGRETERIA_DT"; 
//				$this->setDate($table,$field,$this->pk_service);
//				break;
//			case STATO_INTEGRAZIONE:
//				if ($this->session_vars['DEBUG']==1) print_r($this->session_vars);
//				//die("POLLO");
//				$this->reOpenVisit(0);
//				//$this->reOpenVisit(1,true);
//				//die('qui');
//				//GIULIO 18-12-2012// Riapro solo i dati centro specifici(visitnum=1) del centro che ha ricevuto istruttoria negativa!
//				//$this->reOpenVisitProgr(1,$this->session_vars[VISITNUM_PROGR]);
//				
//				//$this->reOpenVisit(2);				
//				$table = "REGISTRAZIONE";
//				$field = "INTEGRAZIONE_DT"; 
//				$this->setDate($table,$field,$this->pk_service);
//				$this->addField($table,"INTEGRAZIONE",$this->pk_service);
//				break;
//			case STATO_VALUTABILE:
//			if($this->session_vars['DEBUG']==1) echo('<br/><b>STATO_VALUTABILE</b><br/>');
//				/*
//				$vid = 4;
//				$open = array();
//				$open[] = 1;
//				$this->openVisit($vid,$open);
//				*/
//				//DIR-AMMIN
//				//La visita 10 e' centro specifica e post valutazione!
//				/*
//				$vid = 10;
//				$open = array();
//				$open[] = 1;
//				$open[] = 2;
//				$open[] = 3;
//				$this->openVisit($vid,$open);
//				*/
//				
//				$pkid = $this->pk_service;
//				$curvnum = 0; //Visita principale (registrazione)
//				$vprogr = 0; //Visita singola
//				$curesam = 10; //Centri partecipanti
//				$keyField = "PC_KEY";
//				$centerField = "CENTRO";
//				$sperimField = "PRINC_INV";
//				//echo("Open Valutabile");
//				//Apertura schede parere progressive e centro specifiche
//				//Logica chiavi anche qui
//				$progs = $this->getEsamProgs($pkid,$curvnum,$vprogr,$curesam);
//				$keys = array();
//				$centri = array();
//				$cdesc = array();
//				$sperim = array();
//				$sdesc = array();
//				if($this->session_vars['DEBUG']==1) print_r($progs);
//				foreach ($progs as $p){
//					echo $progs[$p];
//					$row = $this->loadEsamProgr($pkid,$curvnum,$vprogr,$curesam,$p);
//					echo"<br>";
//					print_r($row);
//					echo "<br/>keys=";
//					print_r($keys);
//					echo "<br/>";
//					if (!in_array($row[$keyField],$keys)){
//						echo "dentro l'if<br>";
//						echo $row[$keyField]."<br/>";
//						print_r ($keys);
//						$c = $row[$centerField];
//						if ($c){
//							$keys[] = $row[$keyField];
//							$centri[$p] = $c;
//							$cdesc[$p] = $row["D_".$centerField];
//							$sperim[$p] = $row[$sperimField];
//							$sdesc[$p] = $row["D_".$sperimField];
//						}
//					}
//				}
//				
//				//print_r($progs);
//				//print_r($centri);
//				//print_r($sperim);
//				//print_r($cdesc);
//				//print_r($sdesc);
//				//Recupero centri da aprire (documentazione approvata)
//				$progsDocs = $this->getMaxVprogr($pkid,2);
//				$docField = "DOC_COMPLETA";
//				for ($i = 0; $i<=$progsDocs; $i++){
//					$p = $this->getMaxProgr($pkid,2,$i,1);
//					$row = $this->loadEsamProgr($pkid,2,$i,1,$p);
//					if ($row[$docField] != 1){
//						echo "<br/>";
//						$diff = array($row[$keyField]);
//						print_r($diff);
//						$keys = array_diff($keys,$diff);
//						echo "<br/>";
//					}
//				}
//				
//				//echo "<br/>";
//				//print_r($centri);
//				//die("F: ".$found);
//				//recupero le visite progressive x poi verificare la presenza dei centri
//				$parvisit = 4; //Id visita del parere (che devo aprire o modificare)
//				$paresam = 1; //Esam parere
//				$vprogs = $this->getMaxVprogr($pkid,$parvisit);
//				echo"<br>progs=".$vprogs."<br>";
//				echo"<br/>keys=";
//				print_r($keys);
//				echo"<br/>";
//				//$vprogs++;
//				foreach ($keys as $k){
//					echo "<b>qui $k</b>";
//					$found = false;
//					for ($i = 0; $i<=$vprogs; $i++){
//						$row = $this->loadEsamProgr($pkid,$parvisit,$i,$paresam,1); //Forzo il progressivo a 1 (se c'e', almeno il primo c'e' e mi basta quello)
//						if (in_array($row[$keyField],$keys)){
//							$found = true;
//							break;
//						}
//					}
//					//echo "FOUND ($c):".$found;
//					//die("$found");
//
//					if (!$found){
//						$ovnum = $parvisit;
//						$nextvprogr = $this->getMaxVprogr($pkid,$ovnum);
//						//echo "NEXT = $nextvprogr";
//						//$ovprogr = 0;
//						$ovprogr = $nextvprogr+1;
//						//$nextprogr = $this->getMaxProgr($pkid,$ovnum,$ovprogr,1);
//						//$oprogr = $nextprogr+1;
//						echo "<br>($pkid,$ovnum,$ovprogr,1,$oprogr)<br>";
//						//$this->openEsamProgr($pkid,$ovnum,$ovprogr,1,$oprogr);
//						$this->openEsamProgr($pkid,$ovnum,$ovprogr,1,1);
//						//update campi pre-compilati
//						$fields = array();
//						$fields[$keyField] = $k;
//						$fields['CENTRO'] = $centri[$k];
//						$fields['PRINC_INV'] = $sperim[$k];
//						$fields['D_CENTRO'] = str_replace("'","''",$cdesc[$k]);
//						$fields['D_PRINC_INV'] = str_replace("'","''",$sdesc[$k]);
//						//print_r($fields);
//						//print_r($in);
//						//die();
//						$this->updateEsamProgr($pkid,$ovnum,$ovprogr,1,1,$fields);
//					}
//				}
//				
//				//die("<br/>STO SVILUPPANDO!<br/>");
//				
//				//Inserimento data in registrazione
//				$table = "REGISTRAZIONE";
//				$field = "VALUTABILE_DT"; 
//				$this->setDate($table,$field,$this->pk_service);
//				break;
//			case STATO_VALUTATO:
//				//La visita 5 e' centro specifica
//				/*
//				$vid = 5;
//				$open = array();
//				$open[] = 1;
//				$open[] = 2;
//				$open[] = 3;
//				$open[] = 4;
//				$this->openVisit($vid,$open);
//				*/
//				
//				
//				/*
//				$vid = 6;
//				$open = array();
//				$open[] = 1;
//				$this->openVisit($vid,$open);
//				*/
//				/*
//				$vid = 8;
//				$open = array();
//				$open[] = 1;
//				//$open[] = 2;
//				//$open[] = 3;
//				$this->openVisit($vid,$open);
//				*/
//				$vid = 9;
//				$open = array();
//				//$open[] = 1;
//				$open[] = 2;
//				$this->openVisit($vid,$open);
//				$vid = 20;
//				$open = array();
//				$open[] = 1;
//				//$open[] = 2;
//				//$open[] = 3;
//				$this->openVisit($vid,$open);
//				/*
//				$vid = 10;
//				$open = array();
//				$open[] = 1;
//				$open[] = 2;
//				$open[] = 3;
//				$open[] = 4;
//				$open[] = 50;
//				$open[] = 60;
//				$open[] = 70;
//				$this->openVisit($vid,$open);
//				*/
//				//Inserimento data in registrazione
//				$table = "REGISTRAZIONE";
//				$field = "VALUTATO_DT"; 
//				$this->setDate($table,$field,$this->pk_service);
//				break;
				
				case STATO_CHIUSO_RITIRATO:
				$visit_array = array();
				$visit_array[] = 0;
				$visit_array[] = 1;
				$visit_array[] = 2;
				$visit_array[] = 3;
				$visit_array[] = 4;
				
				#Chiudo gli esam e tutte le visitclose
				$this->CloseVisit($visit_array);
				
				#Elimino le eventuali schede di istruttoria non inviate
				$sql_delete_1 = "delete from ce_coordinate where ID_STUD='{$this->pk_service}' and VISITNUM=2 and nvl(fine,0)=0";
				$sql->set_sql ( $sql_delete_1 );
				$sql->ins_upd ();

				#Elimino le eventuali schede di parere non inviate
				$sql_delete_2 = "delete from ce_coordinate where ID_STUD='{$this->pk_service}' and VISITNUM=4 and nvl(fine,0)=0";
				$sql->set_sql ( $sql_delete_2 );
				$sql->ins_upd ();

				break;
		}

		$this->conn->commit();
		
		$location = "{$prefix}/uxmr/index.php?{$this->xmr->pk_service}={$this->pk_service}&VISITNUM={$_GET['VISITNUM']}&exams=visite_exams.xml";
		header ( "location:$location" );
		
		return;
	}
	
	function wf_nuovo_passaURC(){
		#Se ho iniziato da unita' di ricerca
		if ($this->pk_service != 'next') {
			//echo ("################PIPPO#############");	 elicitus4  Elicitus113
			//die("QUA");
			$profilo = $this->getProfilo($this->user->userid);
			$isnew = $this->isNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0);
			$sent = $this->isSent("{$this->xmr->prefix}_coordinate", $this->pk_service, 0, 0);			
			if($isnew && $sent && $profilo == "URC"){
				//echo("PASSA!");
				#Valorizzo la variabile isnew dentro il db, cosi' non ho piu' problemi.
				$this->setNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0, false);
				return true;
			}
		}		
		return false;		
	}

	function wf_nuovo_passaSGR(){
		#Se ho iniziato da segreteria
		if ($this->pk_service != 'next') {
			//echo ("################PIPPO#############");	
			//die("QUA");
			$profilo = $this->getProfilo($this->user->userid);
			$isnew = $this->isNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0);
			$sent = $this->isSent("{$this->xmr->prefix}_coordinate", $this->pk_service, 0, 0);			
			if($isnew && $sent && $profilo == "SGR"){
				//echo("PASSA!");
				#Valorizzo la variabile isnew dentro il db, cosi' non ho piu' problemi.
				$this->setNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0, false);
				return true;
			}
		}		
		return false;		
	}
		
	function wf_compilazione_completata(){
		$closed = $this->CheckVisitClosed("0");
		if ($closed){
			$closed = $this->CheckVisitProgrClosed("1");
		}
		return $closed;
		/*
		$closed = 0;
		$vIds = "0";
		if ($this->pk_service != 'next') {
			$sql_query="select min(nvl(visitclose,0)) vc from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum in ({$vIds}) and inizio=1";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$closed=$sql->row['VC'];
	
		}
		return ($closed==1);
		 */
	}
	
	function wf_integrazione_completata(){
		
		Logger::send("wf_integrazione_completata");
		$closed = $this->CheckVisitClosed("0");
		if ($this->pk_service != 'next' && $this->session_vars['VISITNUM_PROGR']!='' && $this->session_vars['VISITNUM']==1 && $closed){
			Logger::send($in['VISITNUM_PROGR']);
			$closed = $this->CheckVisitProgrClosedSpecific($this->pk_service, 1, $this->session_vars['VISITNUM_PROGR']);
		}else{$closed='';}

		Logger::send("CLOSE: ".$closed);

		return $closed;
	}
	
	function wf_segreteria_completata(){
		Logger::send("wf_segreteria_completata - inizio");
		
		if ($this->pk_service != 'next') {

			if($this->session_vars['DOC_COMPLETA']==1 and $this->session_vars['INVIOCO']==1){
			$close=1;			
			}
			
		}
		//die($close);
		Logger::send("wf_segreteria_completata - close=".$close);
		return $close;
		
		//LUIGI 13-06-2017 il passaggio di stato deve avvenire subito al completamento della validazione documentale
		/*
		$close = true;
		$close = $close && $this->CheckVisitClosed("0");
		$close = $close && $this->CheckVisitClosed("1");
		
		$sql_query = "select min(nvl(fine,0)) as fine from {$this->service}_coordinate where VISITNUM=2 and {$this->config_service['PK_SERVICE']}={$this->pk_service}";
		$sql=new query($this->conn);
		$sql->get_row ( $sql_query );
		
		$close = $close && $sql->row['FINE'];
		
		return $close;
		*/
	}
	
	function wf_segreteria_integrazione(){
		Logger::send("wf_segreteria_integrazione");

			if ($this->pk_service != 'next') {
				if($this->session_vars['DOC_COMPLETA']==2 and $this->session_vars['INVIOCO']==1){
			
				$sql_query="select max(nvl(visitclose,0)) vc from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum = 1 and visitnum_progr not in ({$this->session_vars['VISITNUM_PROGR']})";
				$sql=new query($this->conn);
				$sql->get_row($sql_query);
				$closed=$sql->row['VC'];
				Logger::send($sql_query);
			
					if($closed==0){ #Vado in INTEGRAZIONE se e solo se TUTTI i dati locali sono aperti
						$close=1;	
					}	
				}
			}
		Logger::send("close=".$close);
		
		return $close;
	}

	function wf_parere_sospensivo(){
		
		Logger::send('Parere Sospensivo');
		
		if ($this->pk_service != 'next') {
			if(($this->session_vars['RIS_DELIB']==3 || $this->session_vars['RIS_DELIB']==6) && $this->session_vars['INVIOCO']==1){
				
				$sql_query="select max(nvl(visitclose,0)) vc from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum = 1 and visitnum_progr not in ({$this->session_vars['VISITNUM_PROGR']})";
				$sql=new query($this->conn);
				$sql->get_row($sql_query);
				$closed=$sql->row['VC'];
				Logger::send($sql_query);
				
				if($closed==0){ #Vado in INTEGRAZIONE se e solo se TUTTI i dati locali sono APERTI
					$sosp=1;
				}
			}
		}
		return $sosp;

	}
	
	function wf_valutazione_completa(){
		Logger::send('wf_valutazione_completa');
		
		if ($this->pk_service != 'next') {
		
			if(($this->session_vars['RIS_DELIB']==1 || $this->session_vars['RIS_DELIB']==2 || $this->session_vars['RIS_DELIB']==4 || $this->session_vars['RIS_DELIB']==5 || $this->session_vars['RIS_DELIB']==8) and $this->session_vars['INVIOCO']==1){
			$passa=1;			
			}
		
		}
		Logger::send($passa);
		//die();
		
		return $passa;
	}
	
	function wf_chiudi_studio(){
		$passa = false;
		//die("AAA");
		if ($this->pk_service != 'next') {
			$passa = $this->isFlag($this->pk_service,"CHIUSO");
			//echo $passa;
			if (!$passa){
				$passa = $this->isFlag($this->pk_service,"RITIRATO");
				//echo $passa;
			}
		}
		//die($passa);
		return $passa;
	}
	
	//////// --- FINE WORKFLOW
	
	
	function stampaTemplate($type=null) {
		
		$sql_query="select * from CE_ISTRUTTORIA_TS where ID_STUD={$this->pk_service} and VISITNUM_PROGR=:VISITNUM_PROGR and PROGR=:PROGR and VISITNUM=:VISITNUM and ESAM=:ESAM";
		$sql=new query($this->conn);
		
		$bind['PROGR']=$_GET['PROGR'];
		$bind['VISITNUM']=$_GET['VISITNUM'];
		$bind['VISITNUM_PROGR']=$_GET['VISITNUM_PROGR'];
		$bind['ESAM']=$_GET['ESAM'];
		
		//var_dump( $bind);
		$sql->exec($sql_query,$bind);
		$sql->get_row();
		if ($sql->row['ISTRUTTORIA_TS']!=''){
			if($type=="pdf") {
			
				$html = str_replace ( "<hr>", "<hr break>", $sql->row['ISTRUTTORIA_TS'] );
				$html = str_replace ( "<space>", "&nbsp;", $html );
				//			$html = "<br /><br /><br /><br /><br /><br /><br />".$html;
	
				$filename = "temp_html/lettera_{$sql->row['TEMPLATE_TYPE']}_{$_GET['ID_PRAT']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.html";
				$filename_pdf = "temp_html/lettera_{$sql->row['TEMPLATE_TYPE']}_{$_GET['ID_PRAT']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.pdf";
				$filename_pdf_oth = "/uxmr/temp_html/lettera_{$sql->row['TEMPLATE_TYPE']}_{$_GET['ID_PRAT']}_{$_GET['VISITNUM_PROGR']}_{$_GET['PROGR']}.pdf";
	
				$fp = fopen ( $filename, 'w' );
				fwrite ( $fp, $html );
				fclose ( $fp );
	
				$htmldoc = "/http/local/bin/htmldoc";
				$htmldoc_options [] = "--format pdf";
				$htmldoc_options [] = "--no-title";
				$htmldoc_options [] = "--size A4";
				$htmldoc_options [] = "--charset utf-8";
				$htmldoc_options [] = "--browserwidth 1280";
				$htmldoc_options [] = "--footer .1.";
				$htmldoc_options [] = "--header .t.c";
				$htmldoc_options [] = "--headfootsize 8";
				$htmldoc_options [] = "--headfootfont Times-Italic";
				$htmldoc_options [] = "--bottom 5mm";
				$htmldoc_options [] = "--top 5mm";
				$htmldoc_options [] = "--left 5mm";
				$htmldoc_options [] = "--right 5mm";
				$htmldoc_options [] = "--toclevels 3";
				$htmldoc_options [] = "--fontsize 12px";
				foreach ( $htmldoc_options as $key => $val ) {
					$options .= "$val ";
				}
				if (preg_match ( "/\.sissdev\./", $_SERVER ['HTTP_HOST'] ))
				$htmldoc = "/http/local/bin/htmldoc";
				system ( "$htmldoc $options --webpage /http/www/ce_toscana/html/uxmr/{$filename}> /http/www/ce_toscana/html/uxmr/{$filename_pdf}" );
				system ( "chgrp devj temp_html/lettera_istruttoria_*" );
				system ( "chmod g+w temp_html/lettera_istruttoria_*" );
	
				header("Location: $filename_pdf_oth");
				die();
			} else {
				echo "<body onload=\"window.print();\">";
				echo $sql->row['ISTRUTTORIA_TS'];
				echo "</body>";
				die();
			}
		}
		else{
			error_page($this->session_vars['remote_userid'],"Non &egrave; stato salvato nessun documento");
		}
	}
	
}

?>
