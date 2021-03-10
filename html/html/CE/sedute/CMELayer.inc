<?
include_once("libs/CMELayer.inc");

class CMELayerWCA extends CMELayerWCAPrototype{


function controller(){
	global $conn;
	global $in;
	$this->configuration['ADD_INFO'][0]['TITLE']='Area&nbsp;&nbsp;';
	$this->configuration['ADD_INFO'][0]['VALUE']='[D_AREA_DOC]';
	$this->configuration['ADD_INFO'][1]['TITLE']='Tipo&nbsp;&nbsp;';
	$this->configuration['ADD_INFO'][1]['VALUE']='[D_TIPO_DOC_1][D_TIPO_DOC_2][D_TIPO_DOC_3][D_TIPO_DOC_4][D_TIPO_DOC_5][D_TIPO_DOC_6][D_TIPO_DOC_7][D_TIPO_DOC]';
	$this->configuration['ADD_INFO'][2]['TITLE']='Descrizione&nbsp;&nbsp;<br>aggiuntiva&nbsp;&nbsp;';
	$this->configuration['ADD_INFO'][2]['VALUE']='[DESCR_AGG]';
	//print_r($this->session_vars);
	//print ("<br><br>");
	//print_r($in);
		switch($this->session_vars['CMELAction']){
			
			
			
			
			
		
		##########################################	
		#CASO CLASSICO CON QUERIES PERSONALIZZATE# 
		#PER PROFILO E RUOLO COORD/SAT				   #
		##########################################	
			
			default:
			case'folder':
			if(preg_match("/\//",$this->session_vars['CMELFolder'])){
				
				$folders=explode("/",$this->session_vars['CMELFolder']);
				$topic=array_pop($folders);
				$pk=$folders[0];
				$baseFolder=implode('/',$folders);
				if ($this->session_vars['WFact']=="Applicant" && $topic=="Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)"){
				header("location: index.php?ID_STUD={$this->session_vars['ID_STUD']}&CMELayer=true&CMELAction=folder_ce&CMELFolder={$this->session_vars['ID_STUD']}");
				die();
				}
				
////////////////////////////////////contenuto cartella///////////////////////////////////////////
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':pk_service';
				$query[1]['JOIN']='and';
				$query[1]['TYPE']='SIMPLE';
				$query[1]['PARAM']='TOPIC';
				$query[1]['OPERATOR']='=';
				$query[1]['VALUE']=':topic';
				if ($this->session_vars['WFact']=="CE" && $topic=="Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)"){
					$query[2]['JOIN']='and';
					$query[2]['TYPE']='SIMPLE';
					$query[2]['PARAM']='SAT';
					$query[2]['OPERATOR']='like';
					$query[2]['VALUE']=':CE';
					$query[2]['SELECTIVE_QUERY']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$bind['CE']='%'.$this->session_vars['remote_userid'].'%';
				}
				$bind['pk_service']=$pk;
				$bind['TOPIC']=$topic;
				//print_r ($bind);
				$queryResultSet=array();
////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				Logger::send($this->configuration['queryNames']);
				foreach ($this->configuration['queryNames'] as $queryName){
				Logger::send($queryName);
				$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
				if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);	
				Logger::send($currQueryResultSet);		
				}
				$html=$this->show_area_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$baseFolder);
				
			} else {
				
				
/////////////////////////////////////////////////////lista cartelle////////////////////////////////////////////////////////////////////////////////////////////////////////////
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':'.$this->configuration['PK_SERVICE'];
				if ($this->session_vars['WFact']=="CE"){
					$sql_query="select min(coordinatore) as coord from ossc3_centri_sc where ID_STUD={$this->session_vars['ID_STUD']} and ce_userid='{$this->session_vars['remote_userid']}'";
					$sql=new query($conn);
					$sql->exec($sql_query);
					$sql->get_row($sql_query);
					if ($sql->row[COORD]==2){
						$query[1]['JOIN']='and';
						$query[1]['TYPE']='SIMPLE';
						$query[1]['PARAM']='TOPIC';
						$query[1]['OPERATOR']='not in';
						$query[1]['VALUE']='(:1)';
						$bind['1']='Documentazione solo ad AC centrale - CE che esprime il PU';
					}
					$query[2]['JOIN']='and';
					$query[2]['TYPE']='SIMPLE';
					$query[2]['PARAM']='SAT';
					$query[2]['OPERATOR']='like';
					$query[2]['VALUE']=':CE';
					$query[2]['SELECTIVE_QUERY']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$bind['CE']='%'.$this->session_vars['remote_userid'].'%';
				}
				if ($this->session_vars['WFact']=="AC"){
						$query[1]['JOIN']='and';
						$query[1]['TYPE']='SIMPLE';
						$query[1]['PARAM']='TOPIC';
						$query[1]['OPERATOR']='not in';
						$query[1]['VALUE']='(:1)';
						$bind['1']='Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)';
					}
				//$bind[$this->configuration['PK_SERVICE']]=$this->configuration[$this->configuration['PK_SERVICE']];
				$bind[$this->configuration['PK_SERVICE']]=$this->session_vars['CMELFolder'];
				$queryResultSet=array();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				foreach ($this->configuration['queryNames'] as $queryName){
					$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
					if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);
				}
				$html=$this->folder_doc_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$this->session_vars['CMELFolder']);
			}
			break;
			
			
			
			
			
			
		##########################################	
		#VISIONE LIGHT PER ISS								   # 
		#SENZA CARTELLE 											   #
		##########################################
			
			case'personal':
			$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':pk_service';
				if ($this->session_vars['WFact']=="AC"){
					$query[1]['JOIN']='and(';
					$query[1]['TYPE']='SIMPLE';
					$query[1]['PARAM']='TIPO_DOC_1';
					$query[1]['OPERATOR']='in';
					$query[1]['VALUE']="/*'2','40','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28'*/'42','41','40','5','13','12','23','19','18'";
					$query[1]['SELECTIVE_QUERY']=true;
					$query[1]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[1]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[1]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[2]['JOIN']='or';
					$query[2]['TYPE']='SIMPLE';
					$query[2]['PARAM']='TIPO_DOC_2';
					$query[2]['OPERATOR']='in';
					$query[2]['VALUE']="/*'2','40','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28'*/'42','41','40','5','13','12','23','19','18'";
					$query[2]['SELECTIVE_QUERY']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[3]['JOIN']='or';
					$query[3]['TYPE']='SIMPLE';
					$query[3]['PARAM']='TIPO_DOC_3';
					$query[3]['OPERATOR']='in';
					$query[3]['VALUE']="/*'2','40','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28'*/'42','41','40','5','13','12','23','19','18'";
					$query[3]['SELECTIVE_QUERY']=true;
					$query[3]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[3]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[3]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[4]['JOIN']='or';
					$query[4]['TYPE']='SIMPLE';
					$query[4]['PARAM']='TIPO_DOC_4';
					$query[4]['OPERATOR']='in';
					$query[4]['VALUE']="/*'2','40','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28'*/'42','41','40','5','13','12','23','19','18'";
					$query[4]['SELECTIVE_QUERY']=true;
					$query[4]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[4]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[4]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[5]['JOIN']='or';
					$query[5]['TYPE']='SIMPLE';
					$query[5]['PARAM']='TIPO_DOC_5';
					$query[5]['OPERATOR']='in';
					$query[5]['VALUE']="/*'2','40','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28'*/'42','41','40','5','13','12','23','19','18'";
					$query[5]['SELECTIVE_QUERY']=true;
					$query[5]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[5]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[5]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[6]['JOIN']='or';
					$query[6]['TYPE']='SIMPLE';
					$query[6]['PARAM']='TIPO_DOC_6';
					$query[6]['OPERATOR']='in';
					$query[6]['VALUE']="/*'2','40','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28'*/'42','41','40','5','13','12','23','19','18'";
					$query[6]['SELECTIVE_QUERY']=true;
					$query[6]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[6]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[6]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[7]['JOIN']='or';
					$query[7]['TYPE']='SIMPLE';
					$query[7]['PARAM']='TIPO_DOC_7';
					$query[7]['OPERATOR']='in';
					$query[7]['VALUE']="/*'2','40','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28'*/'42','41','40','5','13','12','23','19','18'";
					$query[7]['SELECTIVE_QUERY']=true;
					$query[7]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[7]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[7]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[8]['JOIN']='or';
					$query[8]['TYPE']='SIMPLE';
					$query[8]['PARAM']='TIPO_DOC_1';
					$query[8]['OPERATOR']='=';
					$query[8]['VALUE']="'1'";
					$query[8]['SELECTIVE_QUERY']=true;
					$query[8]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[9]['JOIN']='or';
					$query[9]['TYPE']='SIMPLE';
					$query[9]['PARAM']='VAR_NAME';
					$query[9]['OPERATOR']='=';
					$query[9]['VALUE']="'CTA')";
					$query[9]['SELECTIVE_QUERY']=true;
					$query[9]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_CORE']=true;
					$query[9]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$query[9]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_COORD']=true;
					$query[10]['JOIN']='and';
					$query[10]['TYPE']='SIMPLE';
					$query[10]['PARAM']='VAR_NAME';
					$query[10]['OPERATOR']='=';
					$query[10]['VALUE']="'da queste tabelle non li prendiamo'";
					$query[10]['SELECTIVE_QUERY']=true;
					$query[10]['SELECTIVE_QUERYNAMES']['RAPPORTO_VALUT']=true;
					$query[10]['SELECTIVE_QUERYNAMES']['RAPPORTO_VALUT_SAT']=true;
					$query[10]['SELECTIVE_QUERYNAMES']['RAPPORTO_VALUT_ISS']=true;
					$query[10]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_EME']=true;
				}
				if ($this->session_vars['WFact']=="CE"){
					$query[1]['JOIN']='and';
					$query[1]['TYPE']='SIMPLE';
					$query[1]['PARAM']='SAT';
					$query[1]['OPERATOR']='like';
					$query[1]['VALUE']=':CE';
					$query[1]['SELECTIVE_QUERY']=true;
					$query[1]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$bind['CE']='%'.$this->session_vars['remote_userid'].'%';
				}
				$bind['pk_service']=$this->session_vars['ID_STUD'];
				//print_r ($bind);
				$queryResultSet=array();	
				Logger::send($this->configuration['queryNames']);
				foreach ($this->configuration['queryNames'] as $queryName){
				Logger::send($queryName);
				$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
				if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);	
				Logger::send($currQueryResultSet);		
				}
				$html=$this->show_area_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$baseFolder);
			break;
			
			
			
			
			
		##########################################	
		#DETTAGLI DOCUMENTO, VERSIONING				   # 
		#E DOWNLOAD			 											   #
		##########################################
			
			case'detail':
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']='ID';
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':id';
				$bind['ID']=$this->session_vars['CMELRequestRef'];
				$bind['pk_service']=$this->session_vars['ID_STUD'];
				$queryResultSet=$this->query($this->configuration['SERVICE'],$this->session_vars['CMELQueryName'],$query,$bind);
				$html=$this->show_doc_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$this->session_vars['CMELRequestRef']);
			break;
			
			
			
			case 'download':
				$this->download($this->configuration['SERVICE'],$this->session_vars['CMELRequestRef']);
			break;
		
		
		
		
		
		##########################################
		#CASO SPECIALE DOCUMENTAZIONE CENTRO	   #
		#SPECIFICA CON SOTTOCARTELLE			 			 #
		##########################################
		
			case'folder_ce':
			unset($this->configuration['queryNames']);
			$this->configuration['queryNames'][]='DOCUMENTAZIONE_SAT';
			if(preg_match("/\//",$this->session_vars['CMELFolder'])){
				
				$folders=explode("/",$this->session_vars['CMELFolder']);
				$sat=array_pop($folders);
				$pk=$folders[0];
				$baseFolder=implode('/',$folders);
				
				
////////////////////////////////////contenuto cartella folder_ce sat///////////////////////////////////////////
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':pk_service';
				$query[1]['JOIN']='and';
				$query[1]['TYPE']='SIMPLE';
				$query[1]['PARAM']='SAT';
				$query[1]['OPERATOR']='like';
				$query[1]['VALUE']="'%|'||:sat||'|%'";
				if ($this->session_vars['WFact']=="CE" && $topic=="Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)"){
					$query[2]['JOIN']='and';
					$query[2]['TYPE']='SIMPLE';
					$query[2]['PARAM']='SAT';
					$query[2]['OPERATOR']='like';
					$query[2]['VALUE']=':CE';
					$query[2]['SELECTIVE_QUERY']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$bind['CE']='%'.$this->session_vars['remote_userid'].'%';
				}
				$bind['pk_service']=$pk;
				$bind['SAT']=$sat;
				//print_r ($bind);
				$queryResultSet=array();
////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				Logger::send($this->configuration['queryNames']);
				foreach ($this->configuration['queryNames'] as $queryName){
				Logger::send($queryName);
				$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
				if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);	
				Logger::send($currQueryResultSet);		
				}
				$html=$this->show_area_mini($nomeArea,$queryResultSet,$this->configuration['baseUri'],$baseFolder);
				
			} else {
				
				
/////////////////////////////////////////////////////lista cartelle folder_ce sat////////////////////////////////////////////////////////////////////////////////////////////////////////////
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':'.$this->configuration['PK_SERVICE'];
				if ($this->session_vars['WFact']=="CE"){
					$sql_query="select min(coordinatore) as coord from ossc3_centri_sc where ID_STUD={$this->session_vars['ID_STUD']} and ce_userid='{$this->session_vars['remote_userid']}'";
					$sql=new query($conn);
					$sql->exec($sql_query);
					$sql->get_row($sql_query);
					if ($sql->row[COORD]==2){
						$query[1]['JOIN']='and';
						$query[1]['TYPE']='SIMPLE';
						$query[1]['PARAM']='TOPIC';
						$query[1]['OPERATOR']='not in';
						$query[1]['VALUE']='(:1)';
						$bind['1']='Documentazione solo ad AC centrale - CE che esprime il PU';
					}
					$query[2]['JOIN']='and';
					$query[2]['TYPE']='SIMPLE';
					$query[2]['PARAM']='SAT';
					$query[2]['OPERATOR']='like';
					$query[2]['VALUE']=':CE';
					$query[2]['SELECTIVE_QUERY']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$bind['CE']='%'.$this->session_vars['remote_userid'].'%';
				}
				if ($this->session_vars['WFact']=="AC"){
						$query[1]['JOIN']='and';
						$query[1]['TYPE']='SIMPLE';
						$query[1]['PARAM']='TOPIC';
						$query[1]['OPERATOR']='not in';
						$query[1]['VALUE']='(:1)';
						$bind['1']='Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)';
					}
				//$bind[$this->configuration['PK_SERVICE']]=$this->configuration[$this->configuration['PK_SERVICE']];
				$bind[$this->configuration['PK_SERVICE']]=$this->session_vars['CMELFolder'];
				$queryResultSet=array();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				foreach ($this->configuration['queryNames'] as $queryName){
					$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
					if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);
				}
				$html=$this->folder_custom($nomeArea,$queryResultSet,$this->configuration['baseUri'],$this->session_vars['CMELFolder'],'SAT');
			}
			break;
			
			
			
			
			
		##########################################
		#FALDONE DOCUMENTALE COMPLETO					   #
		#COMPRENDE QUERIES PERSONALIZZATE	 			 #
		##########################################
			
			case 'downloadAll':
			
			if(preg_match("/\//",$this->session_vars['CMELFolder'])){
				
				$folders=explode("/",$this->session_vars['CMELFolder']);
				$topic=array_pop($folders);
				$pk=$folders[0];
				$baseFolder=implode('/',$folders);
				if ($this->session_vars['WFact']=="Applicant" && $topic=="Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)"){
				header("location: index.php?ID_STUD={$this->session_vars['ID_STUD']}&CMELayer=true&CMELAction=folder_ce&CMELFolder={$this->session_vars['ID_STUD']}");
				die();
				}
				
////////////////////////////////////contenuto cartella///////////////////////////////////////////
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':pk_service';
				$query[1]['JOIN']='and';
				$query[1]['TYPE']='SIMPLE';
				$query[1]['PARAM']='TOPIC';
				$query[1]['OPERATOR']='=';
				$query[1]['VALUE']=':topic';
				if ($this->session_vars['WFact']=="CE" && $topic=="Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)"){
					$query[2]['JOIN']='and';
					$query[2]['TYPE']='SIMPLE';
					$query[2]['PARAM']='SAT';
					$query[2]['OPERATOR']='like';
					$query[2]['VALUE']=':CE';
					$query[2]['SELECTIVE_QUERY']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$bind['CE']='%'.$this->session_vars['remote_userid'].'%';
				}
				$bind['pk_service']=$pk;
				$bind['TOPIC']=$topic;
				//print_r ($bind);
				$queryResultSet=array();
////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				Logger::send($this->configuration['queryNames']);
				foreach ($this->configuration['queryNames'] as $queryName){
				Logger::send($queryName);
				$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
				if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);	
				Logger::send($currQueryResultSet);		
				}
				$this->download_all($queryResultSet,$this->session_vars['CMELFolder']);
				
			} else {
				
				
/////////////////////////////////////////////////////lista cartelle////////////////////////////////////////////////////////////////////////////////////////////////////////////
				$query[0]['TYPE']='SIMPLE';
				$query[0]['PARAM']=$this->configuration['PK_SERVICE'];
				$query[0]['OPERATOR']='=';
				$query[0]['VALUE']=':'.$this->configuration['PK_SERVICE'];
				if ($this->session_vars['WFact']=="CE"){
					$sql_query="select min(coordinatore) as coord from ossc3_centri_sc where ID_STUD={$this->session_vars['ID_STUD']} and ce_userid='{$this->session_vars['remote_userid']}'";
					$sql=new query($conn);
					$sql->exec($sql_query);
					$sql->get_row($sql_query);
					if ($sql->row[COORD]==2){
						$query[1]['JOIN']='and';
						$query[1]['TYPE']='SIMPLE';
						$query[1]['PARAM']='TOPIC';
						$query[1]['OPERATOR']='not in';
						$query[1]['VALUE']='(:1)';
						$bind['1']='Documentazione solo ad AC centrale - CE che esprime il PU';
					}
					$query[2]['JOIN']='and';
					$query[2]['TYPE']='SIMPLE';
					$query[2]['PARAM']='SAT';
					$query[2]['OPERATOR']='like';
					$query[2]['VALUE']=':CE';
					$query[2]['SELECTIVE_QUERY']=true;
					$query[2]['SELECTIVE_QUERYNAMES']['DOCUMENTAZIONE_SAT']=true;
					$bind['CE']='%'.$this->session_vars['remote_userid'].'%';
				}
				if ($this->session_vars['WFact']=="AC"){
						$query[1]['JOIN']='and';
						$query[1]['TYPE']='SIMPLE';
						$query[1]['PARAM']='TOPIC';
						$query[1]['OPERATOR']='not in';
						$query[1]['VALUE']='(:1)';
						$bind['1']='Documentazione centro specifica a tutti i CE (compreso il CE che esprime il parere unico)';
					}
				//$bind[$this->configuration['PK_SERVICE']]=$this->configuration[$this->configuration['PK_SERVICE']];
				$bind[$this->configuration['PK_SERVICE']]=$this->session_vars['CMELFolder'];
				$queryResultSet=array();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				foreach ($this->configuration['queryNames'] as $queryName){
					$currQueryResultSet=$this->query($this->configuration['SERVICE'],$queryName,$query,$bind);
					if(is_array($currQueryResultSet))$queryResultSet=array_merge($queryResultSet,$currQueryResultSet);
				}
				$this->download_all($queryResultSet,$this->session_vars['CMELFolder']);
			}
			break;
			 
		}
		
		$this->html=$html;
	}






function folder_custom($nome_area,$queryResultSet,$baseUri,$folder,$folder_type='TOPIC'){
		if(!$baseUri)$baseUri=$_SERVER['PHP_SELF'].'?';
		global $config_document;
		global $testo_config;
		global $conn;
		$this->tipo_doc="Doc_Area";
		$this->id_tipo_ref=$id_area;
		$sql=new query($this->connection);
		$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
		$sql->ins_upd();
		
		$folder_img="<img src=\"images/cme/folder-doc-mo.gif\" width=30 border=0>";
		/*$sql_query="
			select
				count(*) as n_r_thread,
				topic,
				max(data) as last_ins_dt
			from docs
				where tipo_doc='{$this->tipo_doc}'
				and id_tipo_ref='{$this->id_tipo_ref}'
				and id_ref=id
			group by topic";
//		echo $sql_query;
		$sql->set_sql($sql_query);
		$sql->exec(); //commentata */
		$c=0;
		global $userid_ins;
		$html.="<table border=0 width=100%><tr><td valign=top width=80%>
		<fieldset><legend class=mttl>$nome_area</legend>
		<table border=0 cellpadding=4 width=100% align=center bgcolor=white><tr align=center>
			<tr>
				<td class=mttl2>&nbsp;</td>
				<td class=mttl2  align=\"center\">Tipo Documento</td>
				<td class=mttl2  align=\"center\">N. documenti</td>
			</tr>
			";
		Logger::send($queryResultSet);
		foreach ($queryResultSet as $thread){
			if($folder_type='SAT'){
				$curr_list_sat=$thread[0][$folder_type];
				$curr_list_sat=trim($curr_list_sat,"|");
				$curr_array_sat=explode("|",$curr_list_sat);
				Logger::send($thread[0]['ID']);
				Logger::send($curr_array_sat);
				foreach($curr_array_sat as $curr_sat_value){
					$sql_query="select azienda_ente from ana_utenti_3 where userid='$curr_sat_value'";
					$sql=new query($conn);
					$sql->exec($sql_query);
					$sql->get_row($sql_query);
					$ce_name="<font color='#BC5656'>".$sql->row['AZIENDA_ENTE']."</font>";
					
					//GIULIO
					$info_centro="";
					$sql_query1="select d_qual_princ||' '||nome_princ||' '||cognome_princ as princ_inv, d_strut from ossc3_centri_sc where ce_userid='$curr_sat_value' and ID_STUD={$_GET['ID_STUD']}";
					$sql1=new query($conn);
					$sql1->exec($sql_query1);
					$info_centro="<br><ul>";
					while ($sql1->get_row()){
					$info_centro.="<li>".$sql1->row['D_STRUT']." <br> Principal Investigator: <font color='black'>".$sql1->row['PRINC_INV']."</font></li>";
					}
					$info_centro.="</ul>";
					
					$topics[$curr_sat_value]['NOME_AREA']=$ce_name.$info_centro;
					$topics[$curr_sat_value]['COUNT']++;
					$topics[$curr_sat_value]['ID_AREA']=$thread[0]['ID_TIPO_REF'];
				}
			}
			else{
				$topics[$thread[0][$folder_type]]['COUNT']++;
				$topics[$thread[0][$folder_type]]['ID_AREA']=$thread[0]['ID_TIPO_REF'];
			}
		}
		Logger::send($topics);
		foreach ($topics as $topic => $info){
			$last_doc=$thread[0];
			/*if ($last_doc['TOPIC']=='') $html.=$this->folder_inner_doc_mini("", $c, "", $_GET['VAR'],$_GET['SERVICE'],$_GET['PRJ'],$_GET['USER_TIP']);
			else {*/
			$html.="
				<tr>
				<td>
					<a href=\"{$baseUri}&CMELayer=true&CMELAction={$this->session_vars['CMELAction']}&CMELFolder={$folder}/{$topic}\" title=''>$folder_img</a></td>
				<td width=\"70%\"><a href=\"{$baseUri}&CMELayer=true&CMELAction={$this->session_vars['CMELAction']}&CMELFolder={$folder}/{$topic}\" title=''>{$info['NOME_AREA']}</b></a></td>
				<td align=\"center\"><b>{$info['COUNT']}</b></td>
				</tr>
				";
			/*}*/
			$c++;
		}
		if (count($topics)==0){
			$html.="
				<tr>
					<td colspan=2 align=center><b><font size=3>Non sono presenti documenti</font></b></td>
					<td><b><font size=3>0</font></b></td>
				</tr>
			";
		}
		$html.="</table></fieldset>";
		
//		if (count($queryResultSet)>0){
//			$html.="<br />&nbsp;&nbsp;&nbsp;<a href=\"{$baseUri}CMELayer=true&CMELAction=downloadAll&CMELFolder={$folder}\">Scarica tutti i documenti in formato .zip</a>";
//		}
		return $html;
	}
	
	
	
	
	
function getOjectSpec($pk_value){
	$ret=parent::getOjectSpec($pk_value);
	if (isset($_GET['FORCE_DOC_SAT']) || isset($_POST['FORCE_DOC_SAT'])) $ret['USER_TIP']='DE'; 
	return $ret;
}
	
	

static function downloadHref($id,$baseUri=null){
		if(!$baseUri){
			global $in;
			$baseUri=$_SERVER['PHP_SELF'].'?ID_STUD='.$in['ID_STUD'];
		}
		$href="{$baseUri}&CMELayer=true&CMELAction=download&CMELRequestRef={$id}";
		return $href;
	}
	
	

}

?>