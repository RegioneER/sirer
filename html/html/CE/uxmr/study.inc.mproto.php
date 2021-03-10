<?php

include_once "uploadZip.php";

/**
 * Classe Studio
 * 
 * Contiene tutte le spcifiche dello studio tra cui il Controller
 *
 * @package XMR 2.0
 */
class Study_mproto extends Study_prototype_mxmr {

	/*
	function listPage(){
	    $prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
	    $list = str_replace ( ".xml", "_{$prof_add}.xml", $list );
		
	    die ($this->session_vars ['WFact']);
	}
	*/

	function all_in_form_view($xml_form) {
		
		$this->session_vars ['form'] = $xml;
		$vlist = $this->vlist;
		$in = $this->session_vars;
		$conn = $this->conn;
		$service = $this->service;
		$sql_query = "select max(progr) as max_p from {$service}_coordinate where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and esam={$in['ESAM']} and visitnum={$in['VISITNUM']} and VISITNUM_PROGR={$in['VISITNUM_PROGR']} and inizio is not null";
//		echo $sql_query;
		$sql = new query ( $conn );
		$sql->set_sql ( $sql_query );
		$sql->exec ();
		$sql->get_row ();
		
		$sql->row['MAX_P']-=0;
		if ($this->session_vars['USER_TIP']=='DE' && $sql->row['MAX_P']<1 && $this->vlist->esams[$_GET['VISITNUM']][$_GET ['ESAM']]['QUICKACCESS']=='yes' && !isset($_GET['NoQuickAccess'])){
			$linkff="{$_SERVER['REQUEST_URI']}&PROGR=1";
			
			header("Location: $linkff");
			die();
		}
		$m_p = $sql->row ['MAX_P'];
		$max = $m_p - 0;
		if ($m_p == '' || $m_p == 0)
		$m_p ++;
		$real_progr = $_GET ['PROGR'];
		$next = $m_p + 1;
		if (isset ( $_GET ['PROGR'] )) {
			/*Controllo di visibilita*/
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
				Logger::send("myLog:".$sql_query);
				$sql_abil = new query ( $this->conn );
				$sql_abil->get_row ( $sql_query );
				if ($sql_abil->row ['FINE'] != 1 && ($sql_abil->row ['USERID'] != $this->user->userid && $in ['USER_TIP'] != 'DE')) {
					error_page ( $this->user->userid, $this->testo ( "userNotCenter" ), "" );
				}
			}
			$xml_form->make_html ();
			$script = "
				<script type=\"text/javascript\">
				" . $xml_form->salva_js . "
				" . $xml_form->invia_js . "
				" . $xml_form->check_js . "
				" . $xml_form->inrevisione_js . "
				</script>
				";
			$onload .= $xml_form->onload . ";";
			if ($this->pk_service != '' && $this->pk_service != 'next') {
				$this->make_patient_table ();
				$body = $this->patient_table;
				$body .= "<br>" . $this->tb_riassuntiva ();
			} else
			$body = '';
			$body .= $xml_form->body;
		} else {
			$colspan = 4;
			if (isset ( $xml_form->form ['FIELD_AGG'] )) {
				/*Modalita' con modifica diretta dei valori in schema riassuntivo*/
				$tr_agg = "<tr>";
				$fields_agg = explode ( "|", $xml_form->form ['FIELD_AGG'] );
				$fields_agg_txt = explode ( "|", $xml_form->form ['FIELD_AGG_TXT'] );
				if (isset ( $_GET ['ADDBLANK'] )) { /*Aggiunta di scheda vuota*/
					//echo $sql->row['MAX_P'];
					if($sql->row['MAX_P']!="") {
						if($sql->row['MAX_P']>=$_GET ['ADDBLANK'] || $sql->row['MAX_P']+1<$_GET ['ADDBLANK']) {
							error_page ( $remote_userid, "La scheda numero {$_GET ['ADDBLANK']} ?i?tata inserita. Non utilizzare il tasto back del browser o ritornare alla lista schede aggiornata.", "La scheda numero {$_GET ['ADDBLANK']} ?i?tata inserita. Non utilizzare il tasto back del browser o ritornare alla lista schede aggiornata." );
						}
					}
					if (! isset ( $_GET ['VISITNUM_PROGR'] ) || $_GET ['VISITNUM_PROGR'] == '')
					$_GET ['VISITNUM_PROGR'] = 0;
					$redirect = $_SERVER ['REQUEST_URI'];
					$redirect = str_replace ( "&ADDBLANK={$_GET['ADDBLANK']}", "", $redirect );
					$values ['INIZIO'] = 1;
					$values ['ABILITATO'] = 1;
					$values ['USERID'] = $this->user->userid;
					$values ['INSERTDT'] = sysdate;
					$values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
					$tb_prefix = "{$this->service}";
					$sql_query = "
								select count(*) as conto from {$tb_prefix}_coordinate
								where
									VISITNUM={$_GET['VISITNUM']}
									and
									VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}
									and
									ESAM={$_GET['ESAM']}
									and
									PROGR={$_GET['ADDBLANK']}
									and
									{$this->config['PK_SERVICE']}={$_GET[$this->config['PK_SERVICE']]}
							";
									$sql->get_row ( $sql_query );
									if ($this->integrazione->eq_enabled){
										if ($this->integrazione->eq_int=='') $this->integrazione->CreateEq();
										$values['INV_QUERY']=$this->integrazione->eq_int;
										$values['EQ_ACTION']=1;
									}
									if ($sql->row ['CONTO'] == 0) {
										$values ['VISITNUM'] = $_GET ['VISITNUM'];
										$values ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
										$values ['ESAM'] = $_GET ['ESAM'];
										$values ['PROGR'] = $_GET ['ADDBLANK'];
										$values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
										$tb_coord = $tb_prefix . "_coordinate";
										$pk = '';
										$sql->insert ( $values, $tb_coord, $pk );
									} else {

										$tb_coord = $tb_prefix . "_coordinate";
										$pk ['VISITNUM'] = $_GET ['VISITNUM'];
										$pk ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
										$pk ['ESAM'] = $_GET ['ESAM'];
										$pk ['PROGR'] = $_GET ['ADDBLANK'];

										$pk [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
										$sql->update ( $values, $tb_coord, $pk );
									}
									$pk = '';
									$values = '';
									$values ['VISITNUM'] = $_GET ['VISITNUM'];
									$values ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
									$values ['ESAM'] = $_GET ['ESAM'];
									$values ['PROGR'] = $_GET ['ADDBLANK'];
									$values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
									$tb_ = $xml_form->form ['TABLE'];

									$sql->insert ( $values, $tb_, $pk );

									if ((isset ( $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['SFOGLIA_CALL'] )) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['SFOGLIA_CALL'] == 'yes') {
										$redirect .= "&CALL_Sfoglia";
									}

									$this->conn->commit ();
									header ( "location:$redirect" );
									die ();
				}
				if (isset ( $_POST ['ApplMod'] )) {/*Applico le modifiche*/
					$redirect = $_SERVER ['REQUEST_URI'];
					$param='';
					foreach ($_GET as $key => $val){
						if ($key!='CALL_Sfoglia')
						$param.="$key=$val&";
					}
					$param=rtrim($param, "&");
					$redirect="index.php?{$param}";
					$table = $xml_form->form ['TABLE'];
					$visitnum = $_GET ['VISITNUM'];
					$esam = $_GET ['ESAM'];
					if ($_GET ['VISITNUM_PROGR'] != '')
					$visitnum_progr = $_GET ['VISITNUM_PROGR'];
					else
					$visitnum_progr = 0;
					foreach ( $fields_agg as $fk => $field ) {
						foreach ( $xml_form->fields as $key => $val ) {
							if ($val ['VAR'] == $field) {

								foreach ( $_POST as $pkey => $pval ) {
									$field = new field ( $xml_form, $key );

									if (preg_match ( "!^{$val ['VAR']}_PROGR_!", $pkey ) && ! preg_match ( "!D$!", $pkey ) && ! preg_match ( "!M$!", $pkey ) && ! preg_match ( "!Y$!", $pkey ) && ! preg_match ( "!RC$!", $pkey )) {
										$progr = str_replace ( "{$val ['VAR']}_PROGR_", "", $pkey );
										if ($val ['TYPE'] == 'radio') {
											$values [$progr] ["D_" . $val ['VAR']] = $field->values [$_POST [$val ['VAR'] . "_PROGR_" . $progr]];
										}
										if ($val ['TYPE'] == 'select') {
											$values [$progr] ["D_" . $val ['VAR']] = $field->values [$_POST [$val ['VAR'] . "_PROGR_" . $progr]];

										}
										$values [$progr] [$val ['VAR']] = $pval;
										if ($val ['TYPE'] == 'data') {
											if ($pval != '') {
												$values [$progr] [$val ['VAR']] = "to_date('{$pval}','DDMMYYYY')";
												$values [$progr] [$val ['VAR'] . "RC"] = "OKOKOK";
											} else
											unset ( $values [$progr] [$val ['VAR']] );
										}
									}
								}
							}
						}
					}
					foreach ( $values as $progr => $values_ ) {
						$pk [$this->config_service ['PK_SERVICE']] = $this->pk_service;
						$pk ['VISITNUM'] = $visitnum;
						$pk ['VISITNUM_PROGR'] = $visitnum_progr;
						$pk ['ESAM'] = $esam;
						$pk ['PROGR'] = $progr;
						if (count ( $values_ ) > 0) {
							//echo "<hr>$progr";
							$sql = new query ( $this->conn );
							$sql->update ( $values_, $table, $pk );
						}
					}
					if ($xml_form->form ['F_TO_CALL'] != '') {
						$f_to_call = $xml_form->form ['F_TO_CALL'];
						$f_to_call ( $xml_form );
					}
					$this->conn->commit ();
//					die("hiri");
					header ( "location:$redirect" );
					die ();
				}
				/*Header della tabella*/
				foreach ( $fields_agg_txt as $key => $val ) {
					$field_agg_txt .= "<th class=int>$val</td>";
				}
				foreach ( $fields_agg as $fk => $field ) {
					$colspan ++;
					foreach ( $xml_form->fields as $key => $val ) {
						if ($val ['VAR'] == $field) {
							$nextrow = count ( $type_fields_agg );
							foreach ( $val as $k => $v ) {
								$type_fields_agg [$nextrow] [$k] = $v;
							}
							$field_tot = '';
							$field_type="field_".$val['TYPE'];

							if ($val['TYPE']!='file_doc')
							$select_field .= "$field,";
							if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
								include_once $this->config_service['field_lib'] . $field_type . ".inc";
							} else {
								include_once "libs/{$field_type}.inc";
							}
							//include_once "libs/$field_type.inc";
							$tr_agg.=call_user_func(array($field_type, "S_all_in"), $field, $m_p, $xml_form);
						}
					}
				}

				$rowspan = " rowspan='2'";
				$tr_agg .= "</tr>";
			}
			$sql = new query ( $this->conn );
			if ($_GET ['VISITNUM_PROGR'] == '')
			$visitnum_progr = 0;
			else
			$visitnum_progr = $_GET ['VISITNUM_PROGR'];
			$where_agg_eq='';
			if ($this->config_service['eQuerySpec']['Integrazione']['ON'] && (!$this->integrazione->eq_enabled || $this->integrazione->eq_int=='')) $where_agg_eq="and (INV_QUERY is null or EQ_ACTION=2)";
			$sql_query = "select min(nvl(fine,0)) as fine from {$this->service}_coordinate where
			VISITNUM={$_GET['VISITNUM']}
			and esam={$_GET['ESAM']}
			and {$this->config_service['PK_SERVICE']}={$this->pk_service}
			and visitnum_progr=$visitnum_progr
			$where_agg_eq
			";
			$sql->get_row ( $sql_query );
			
//			#GIULIO 7/5/2013 Mostro il CESTINO al profilo CMP per poter eliminare una relazione inserita da quel CMP stesso (e non per le altre relazioni)
//			if(isset($this->config_service['PK_SERVICE']) && $this->config_service['PK_SERVICE']=='ID_SED'){
//			$sql_query_trash = "select * from gse_coordinate where
//			VISITNUM=1
//			and esam={$_GET['ESAM']}
//			and {$this->config_service['PK_SERVICE']}={$this->pk_service}
//			and visitnum_progr=$visitnum_progr
//			$where_agg_eq
//			";
//			$sql_trash = new query ( $this->conn );
//			$sql_trash-> exec ( $sql_query_trash );
//			$flag_cestino='';
//			while($sql_trash->get_row()){
//				if($this->session_vars['remote_userid']==$sql_trash->row['USERID']){
//					$flag_cestino=1;
//					}
//				}
//			}
			
			if (($sql->row ['FINE'] == 1 || ($this->session_vars ['USER_TIP'] != 'DE' && $flag_cestino!=1)) && !($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo)) {
				$closed_all = true;
				$rowspan = "";
				$tr_agg = "";
				$colspan --;
				$elimina_col = "";
			} else {
				$closed_all = false;
				if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TRASH'] != '' && ($this->session_vars ['USER_TIP'] == 'DE' || $this->integrazione->eq_enabled || $flag_cestino==1))
				$elimina_col = "<th class='int' width='40' align='center' $rowspan>Elimina</td>";
			
			}
			//LUIGI: nuovi emendamenti
			#GC 18/112014# RF.CE_EV008 CES59 possibilit?i eliminare i documenti studio,centro,emendamenti
			$trash_doc=0;
			if($this->getProfilo($this->user->userid)=='SGR' && $this->session_vars ['USER_TIP'] == 'DE' && $this->config_service['PK_SERVICE']=='ID_STUD' && (($this->session_vars ['VISITNUM']==0 && $this->session_vars ['ESAM']==2) || ($this->session_vars ['VISITNUM']==1 && $this->session_vars ['ESAM']==23) || ($this->session_vars ['VISITNUM']==20 && $this->session_vars ['ESAM']==10))&& $sql->row ['FINE'] == 1){
					$elimina_col = "<td class='int' width='40' align='center' $rowspan>Elimina</td>";
					$trash_doc=1;
			}
			$body.=$this->tb_riassuntiva();
			$body .= "
				<p align=center><b>{$vlist->esams[$in['VISITNUM']][$in['ESAM']]['TESTO']}</b></p>
				<form method=\"POST\" name=\"ALL_IN_FORMS\" action=\"index.php?VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&{$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}&ESAM={$_GET['ESAM']}&VISITNUM={$_GET['VISITNUM']}\">
				<table class=\"table table-striped table-bordered table-hover\" border=0 cellpadding=0 cellspacing=2 width=95%>";
			$col_modifica=true;
			if ($xml_form->form ['NO_MOD_COL'] != '')
			$col_modifica = false;
			if ($col_modifica)
			if (strtolower ( $this->config_service ['lang'] ) == 'en') {
				$col_modifica_header = "<th class=int width=40 align=center $rowspan>View/Update </th>";
				$col_num_txt = "Number";
			} else {
				$col_modifica_header = "<th class=int width=40 align=center $rowspan>Modifica/visualizza </th>";
				$col_num_txt = "N.ro";
			}
			if ($max > 0) {
				$tb_header = "";
				if ($xml_form->form ['TB_HEADER'] != '')
				$tbsspl = explode(",",$xml_form->form['TB_HEADER']);
				for ($j = 0; $j<count($tbsspl); $j++){
					$tb_header .= "<th class=int $rowspan>{$tbsspl[$j]}</td>";
				}
				
				if(isset($xml_form->form['FIELD_TB_PLUS'])) {
				$tb_header_split=explode("|",$xml_form->form['FIELD_TB_PLUS_DECODE']);
				//				print_r($tb_header_split);
						$tb_plus_header="";
						foreach($tb_header_split as $key => $val) {
				$val=str_replace("'","",$val);
				$tb_plus_header.="<th class=int nowrap>$val</td>";
				}
				}
				
				$body .= "
				<!--thead-->
						<tr>
							<th class=int $rowspan>$col_num_txt</td>
							$tb_header
							$field_agg_txt
							$col_modifica_header
							$elimina_col
						</tr>
					<!--/thead-->
						$tr_agg
						";
			}
			if ($in ['PROGR'] > $m_p)
			$m_p = $in ['PROGR'];
			if ($max > 0)
			$all_closed = true;
			$counter=0;

			//Multi tbShow..??
			$sql_query = "select $select_field ";
			$tbsspl = explode(",",$xml_form->form['FIELD_TB_SHOW']);
			$tbsnum = count($tbsspl);
			for ($j = 0; $j<$tbsnum;$j++){
				if ($j>0){
					$sql_query .=",";
				}
				$sql_query .=" {$tbsspl[$j]} as FIELD_TB_SHOW_$j ";
			}
			//$sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW
			$sql_query .=" from {$xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']}
				and visitnum_progr={$in['VISITNUM_PROGR']}
				and esam={$in['ESAM']}
				--and progr=$i
			order by progr
				";

			$sql = new query ( $conn );
			$sql->set_sql ( $sql_query );

			$sql->exec ();

			//die("QUI");
			for($i = 1; $i <= $max; $i ++) {

				if ($_GET ['VISITNUM_PROGR'] == '')
				$_GET ['VISITNUM_PROGR'] = 0;
				$sql_query = "
								select
									*
								from {$service}_coordinate
								where visitnum={$_GET['VISITNUM']}
								and visitnum_progr={$_GET['VISITNUM_PROGR']}
								and esam={$_GET['ESAM']}
								and progr=$i
								and {$this->config_service['PK_SERVICE']}={$this->pk_service}
								";
				$sql_abil = new query ( $this->conn );
				if (!$sql_abil->get_row ( $sql_query )) continue;
				if ($sql_abil->row['ABILITATO']!=1) continue;
				
				#GC 18-12-13#Nascondo le relazioni/osservazioni non salvate, in quanto creo il record all'accesso alla scheda, quindi potrebbero non salvarla 
				if($_GET['VISITNUM']==1 && $service=='GSE'){
					if ($sql_abil->row['INIZIO']!=1) {
						$sql->get_row();
						continue;
						}
				}
				
				$eq_new=false;
				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
					if ($sql_abil->row['EQ_ACTION']==1) {
						$eq_new=true;
					}
					//if ($sql_abil->row['EQ_ACTION']==2) continue;
				}else {
					if ($sql_abil->row['EQ_ACTION']==1) continue;
				}

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
								and progr=$i
								and {$this->config_service['PK_SERVICE']}={$this->pk_service}
								";
					$sql_abil = new query ( $this->conn );
					$sql_abil->get_row ( $sql_query );
					if ($sql_abil->row ['FINE'] != 1 && $sql_abil->row ['USERID'] != $this->user->userid)
					continue;
					$sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW
				from {$xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']}
				and visitnum_progr={$in['VISITNUM_PROGR']}
				and esam={$in['ESAM']}
				and progr=$i
				";
					$sql = new query ( $conn );
					$sql->set_sql ( $sql_query );

					$sql->exec ();
				}

				if ($sql_abil->row['FINE']==1) $this_close=true;
				else $this_close=false;
				$body .= "<tr>";
				$counter++;
				if ($i != $real_progr) {
					$in ['PROGR'] = $i;

					/*
					 $sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW from {$xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']} and visitnum_progr={$in['VISITNUM_PROGR']} and progr=$i";

					 $sql = new query ( $conn );
					 $sql->set_sql ( $sql_query );

					 $sql->exec ();
					 */
					$sql->get_row ();
					$tb_content = "";
					for ($j = 0; $j<$tbsnum;$j++){
					
						$TXT = $sql->row ["FIELD_TB_SHOW_$j"];
						$TXT = preg_replace ( "!#(.*?)#!m", "<$1>", $TXT );
						if ($TXT != ''){
							$tb_content .= "<td class=sc4bis $css_style>$TXT</td>";
						}else{
							$tb_content .= "<td class=sc4bis $css_style>&nbsp;</td>";
						}
						//echo $tb_content;
					}
					
					if(isset($xml_form->form['FIELD_TB_PLUS'])) {
	
						$where_plus=$xml_form->form['FIELD_TB_PLUS_WHERE'];
						$where_tb_field=preg_replace("/(.*)\[(.*?)\](.*)/",'$2',$where_plus);
	
						$sql_query_field="select $where_tb_field from {$xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']} and visitnum_progr={$in['VISITNUM_PROGR']} and progr=$i";
						$sql_f = new query ( $conn );
						$sql_f->set_sql ( $sql_query_field );
						$sql_f->exec ();
							$sql_f->get_row ();
						$where_original_cond=$sql_f->row[$where_tb_field];
	
							$where_plus=str_replace("[$where_tb_field]","'".$where_original_cond."'",$where_plus);
	
						$field_plus=str_replace("|",",",$xml_form->form['FIELD_TB_PLUS']);
						$sql_query = "select $field_plus from {$xml_form->form['FIELD_TB_PLUS_VIEW']} where $where_plus";
						$sql = new query ( $conn );
						$sql->set_sql ( $sql_query );
						$sql->exec ();
						$sql->get_row ();
						$td_plus="";
							foreach($sql->row as $key => $val) {
						$td_plus.="<td class=sc4bis $css_style>$val</td>";
							}
						}
					
					$add_txt='';
					
//					if ($eq_new) $add_txt="<img src=\"images/eq_img.png\" width=15px>";
//					if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $sql_abil->row['EQ_ACTION']=='2') {
//
//						$add_txt="<img src=\"images/iphone_delete_icon.png\">";
//					}
					
					if(!$exclude_visit) {
					if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $sql_abil->row['EQ_ACTION']=='2') {
						$add_txt="<img src=\"images/iphone_delete_icon.png\">";
				}
						if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $sql_abil->row['EQ_ACTION']=='1') {
						$add_txt="<img src=\"images/plus-icon.png\" width=15px>";
						}
						if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && count($eqValues[$i])>o) {
						$add_txt="<img src=\"images/eq_img.png\" width=15px>";
						}

						/*if( $this->session_vars['WFact']!=$this->config_service['eQuerySpec']['Integrazione']['ROLE'][$this->config_service['service']]){
						$add_txt="";
					}*/
						}
					
					$body .= "
							<td class=sc4bis $css_style><b>$add_txt $counter</b></td>
							$tb_content
							";
							$progr = $in ['PROGR'];
							//if (($xml_form->closed_form ( $progr ) || $this->session_vars ['USER_TIP'] != 'DE') && !($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo)) {
							//	$this_closed = true;
							//} else
							//	$this_closed = false;

//							se questo if lo mettiamo dentro al prossimo if e anche dentro al prossimo else valorizza le var anche alla progr = 1
							if (isset ( $type_fields_agg )) {
								foreach ( $type_fields_agg as $key => $val ) {
									//										print_r($val);
									$var = $val ['VAR'];
									$field_type = "field_{$val['TYPE']}";
									if ($this->config_service['field_lib'] != '' && file_exists ( $this->config_service['field_lib'] . $field_type . ".inc" )) {
										include_once $this->config_service['field_lib'] . $field_type . ".inc";
									} else {
										include_once "libs/{$field_type}.inc";
									}
									//include_once "libs/$field_type.inc";
									$field_obj = new $field_type ( $xml_form, $xml_form->vars [$var], $xml_form->conn, $xml_form->tb_vals, $xml_form->session_vars, $xml_form->service, $xml_form->errors );
									$ret = $field_obj->all_in ( $var, $i, $sql->row, $this_close );

									if ($sql_abil->row['EQ_ACTION']=='') $ret = $field_obj->all_in ( $var, $i, $sql->row, $this_close );
									if ($sql_abil->row['EQ_ACTION']=='2') $ret = $field_obj->all_in ( $var, $i, $sql->row, true );
									$body .= $ret ['body'];
									$c1_agg .= $ret ['c1_agg'];
									if ($ret['last_call_sfoglia']!=''){
										$last_call_sfoglia=$ret['last_call_sfoglia'];
									}
								}
							}

							$progr = $in ['PROGR'];
							if (! $xml_form->closed_form ( $progr ) || ($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo)) {
								$all_closed = false;
								if ($col_modifica)
								$col_modifica_td = "<td class=sc4bis align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}\"><img src=\"images/pen.png\" border=0></a></td>";
								$col_modifica_td = "<td class=sc4bis align=center>
																			<button class=\"btn btn-xs btn-info\" type=\"button\" onclick=\"location.href='index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}' \">
																				<i class=\"fa fa-edit bigger-120\"></i>
																			</button>
																		</td>";
								
								$body .= $col_modifica_td;

								if (! $xml_form->closed_form ( $progr ) || $this->integrazione->eq_enabled)

								if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TRASH'] != '' &&
								((($this->session_vars ['USER_TIP'] == 'DE' && $sql_abil->row['USERID']=='') || $sql_abil->row['USERID']==$this->user->userid) || ($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo) || !$this->integrazione->eq_enabled)
								) {
									if ($sql_abil->row['EQ_ACTION']=='2')
									$body .= "
							<td class=sc4bis align=center>
							{$add_txt}Scheda eliminata
							</td>";
							else if($this->integrazione->stato!=2)
							
							{
								if($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo && !$exclude_visit) $add_eq="&per_integrazione=true";
								else $add_eq="";
							if(($elimina_col && $this->session_vars ['WFact'] != 'Componente CE') || ($sql_abil->row ['USERID'] == $this->user->userid && $this->session_vars ['WFact'] == 'Componente CE' && $this->session_vars ['VISITNUM']==1 && ($this->session_vars ['ESAM']==1 || $this->session_vars ['ESAM']==2) && $this->config_service['PK_SERVICE']=='ID_SED'))
							$body .= "
							<td class=sc4bis align=center>
								<!--a onclick=\"if (!confirm('E\\' sicuro di voler eliminare la scheda: {$this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TESTO']}?')) return false;\" href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&ELIMINA_LA_SCHEDA=yes{$add_eq}\">
								<img src=\"images/trash.png\" border=0>
								</a-->
								<button class=\"btn btn-xs btn-danger\" type=\"button\" onclick=\"if (!confirm('E\\' sicuro di voler eliminare la scheda: {$this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TESTO']}?')) return false; location.href='index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&ELIMINA_LA_SCHEDA=yes{$add_eq}' \">
									<i class=\"fa fa-trash bigger-120\"></i>
								</button>
							</td>";
							else if($sql_abil->row ['USERID'] != $this->user->userid && $this->session_vars ['WFact'] == 'Componente CE' && $this->session_vars ['VISITNUM']==1 && ($this->session_vars ['ESAM']==1 || $this->session_vars ['ESAM']==2) && $this->config_service['PK_SERVICE']=='ID_SED'){
								$body .="<td class=sc4bis align=center></td>";}
							
						}
							else $body .= "<td class=sc4bis align=center>&nbsp;</td>";
	
									//							else {
									//								$body .= "<td class=sc4bis align=center>&nbsp;</td>";
										//	
								}
							} else {
								if ($col_modifica)
								$col_modifica_td = "<td class=sc4bis align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}\"><i class=\"btn btn-xs btn-info icon-zoom-in bigger-130\"></i></a></td>";
								$body .= "
								$col_modifica_td
						";
								if (! $closed_all)
								$body .= "<!--td class=sc4bis>&nbsp;</td-->";
							}
							
							//LUIGI: nuovi emendamenti
							#GC 18/112014# RF.CE_EV008 CES59 possibilit?i eliminare i documenti studio,centro,emendamenti
							if($trash_doc){
								$body .= "
											<td class=sc4bis align=center><a onclick=\"if (!confirm('E\\' sicuro di voler eliminare la scheda: {$this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TESTO']}?')) return false;\" href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&ELIMINA_LA_SCHEDA=yes{$add_eq}\">
												<i class=\"btn btn-xs btn-danger icon-trash bigger-120\"></i>
											</a></td>";
							}
								
							$body .= "</tr>";
				}
			}
			
			//die("QAU");
			if ($max == 0)
			$next = 1;
			if (isset ( $xml_form->form ['FIELD_AGG'] ) && ($this->session_vars ['USER_TIP'] == 'DE' || $this->integrazione->eq_enabled)) {
				if (isset ( $_GET ['CALL_Sfoglia'] ) && $last_call_sfoglia != '')
				$body .= "
							<script>
							apri_window('/$last_call_sfoglia');
							</script>";
				if (isset ( $_GET ['JUST_DELETE'] ) )
				$body .= "
							<script>
							document.forms['ALL_IN_FORMS'].submit();
							</script>";
				
				#GC 27/05/2015# controllo che ci sia almeno un vero documento inserito (e non il primo record vuoto di default)
				#Capire se questa condizione si applica bene anche alle schede diverse da quelle documentali
				$primo_record=getMaxProgrInizio($this->pk_service,$in['VISITNUM'],$in['VISITNUM_PROGR'],$in['ESAM'],$conn);
				
				//if ($xml_form->form ['HIDE_ALL_IN_BUTTON']!= "yes" && (! $all_closed &&  $this->integrazione->stato!=2) )
				if ($xml_form->form ['HIDE_ALL_IN_BUTTON']!= "yes" && (!$all_closed &&  $this->integrazione->stato!=2) && $primo_record>0)
				$body .= "
							<tr>
								<td colspan=$colspan align=center>
								<font color=red><b>Attenzione &egrave; necessario applicare le modifiche con il pulsante apposito</b></font>
									<input type='hidden' name='ApplMod' value='Salva le modifiche'>
									
									<!--input type='submit' name='ApplMod_button' value='Applica Modifiche' style=\"color: red; font-weight:bold;\" onclick=\"
										f=document.forms[0];
										el=f.elements;
										specifiche='A=ON&L=0&F=0';
								  		c1='';
								  		$c1_agg;
										rc=contr(c1,specifiche);
								  		if (rc) return false;
									\"-->
									<button class=\"btn btn-warning\" name=\"ApplMod_button\" type=\"submit\" onclick=\"
										f=document.forms[0];
										el=f.elements;
										specifiche='A=ON&L=0&F=0';
								  		c1='';
								  		$c1_agg;
										rc=contr(c1,specifiche);
								  		if (rc) return false;
									\">
										<i class=\"fa fa-floppy-o bigger-110\"></i>
										Applica Modifiche
									</button>
									
								</td>
							</tr>";
			}
			$add_progr = $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['ADD_PROGR'];
			if (! isset ( $this->config_service ['Aggiungi_nuova_scheda'] )) {
				$this->config_service ['Aggiungi_nuova_scheda'] = 'Aggiungi nuova scheda';
			}
			$where_agg_eq='';
			if ($this->config_service['eQuerySpec']['Integrazione']['ON'] && (!$this->integrazione->eq_enabled || $this->integrazione->eq_int=='')) $where_agg_eq="and (INV_QUERY is null or EQ_ACTION=2)";
			$sql_visitclose = "select min(visitclose) as closed
			from {$service}_coordinate where visitnum={$_GET['VISITNUM']}
			and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
			$where_agg_eq
			";

			//die("DIE");
			$sql_c = new query ( $this->conn );
			$sql_c->get_row ( $sql_visitclose );
			if ($sql_c->row ['CLOSED'] == 1)
			$visit_closed = true;
			else
			$visit_closed = false;
			//die("VC: $visit_closed - ADDPROGF: $add_progr - NE: {$this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['NEXT_ENABLED']}");
			//echo("UTIP: {$in ['USER_TIP'] }");
			if (
			(
			(!$visit_closed && $in ['USER_TIP'] == 'DE')
			|| ($this->integrazione->eq_enabled  && $this->integrazione->stato!=2 && $this->integrazione->role==$this->user->profilo)
			)
			&& $add_progr != 'no' && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['NEXT_ENABLED'] != 'no') {
				//die("AUS");
				$show = true;
				//echo "<pre>POLLOOO!</pre>";
				//print_r($this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']]);
				$cond_tab = $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['NEXT_COND_TABLE'];
				$cond_field = $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['NEXT_COND_FIELD'];
				if ($cond_tab && $cond_field ){
					//Query data to show button
					//echo "<pre>POLLOSSSOO!</pre>";
					$sql_cnext = new query ( $this->conn );
					$sql_cnext->get_row ( "SELECT $cond_field FROM {$this->service}_$cond_tab WHERE {$this->xmr->pk_service} = {$this->pk_service} and ESAM = 0 and VISITNUM = 0 and VISITNUM_PROGR = 0 and PROGR = 1 ");
					if ($sql_cnext->row [$cond_field] == 1){
						$show = false;
					}
				}
				//die("S: $show");
				if ($show){
					//GIULIO 31/01/2013 - Elimino (non entro nel prossimo if) il bottone di aggiunta nuova scheda progressiva se sono in emendamento e sono in una visita esclusa dall'emendamento.
					//In altre parole, posso aggiungere schede progressive per quelle visite che non sono escluse e che non siano la visita dell'emendamento stesso.
					
					//if ($this->integrazione->eq_enabled  && $this->integrazione->stato=0 && $this->integrazione->role==$this->user->profilo && (!in_array($this->session_vars['VISITNUM'],$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT']) || in_array($this->session_vars['VISITNUM'],$this->config_service['eQuerySpec']['Integrazione']['EXCLUDE_VISIT']['EME_VISIT']) )){
						
						if (isset ( $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['ADD_BLANK'] )) {
							//echo "<li>{$_SERVER['REQUEST_URI']}&ADDBLANK=$next</li>";
							$button = "<input type=\"button\"
										onclick=\"window.location.href='{$_SERVER['REQUEST_URI']}&ADDBLANK=$next'\"
									value=\"{$this->config_service['Aggiungi_nuova_scheda']}\">";
						} else
						
						#GC NUOVA_GRAFICA
						//$button = "<input type=\"button\" onclick=\"window.location.href='index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$next}'\" value=\"{$this->config_service['Aggiungi_nuova_scheda']}\">";	
						$button = "
							<button class=\"btn btn-info blue\" type=\"button\" onclick=\"window.location.href='index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$next}'\">
								<i class=\"fa fa-plus bigger-110\"></i>
								".$this->config_service['Aggiungi_nuova_scheda']."
								</button>";	
						
						$body .= "
								<tr>
									<td colspan=$colspan align=center>
									$button
									</td>
								</tr>";
					//}
				}
			}

			if (isset ( $this->config_service ['Note'] [$_GET ['VISITNUM']] [$_GET ['ESAM']] )) {
				$body .= "<tr><td colspan=$colspan align=center style=\"color:red\">{$this->config_service['Note'][$_GET['VISITNUM']][$_GET['ESAM']]}</td></tr>";
			}
			$body .= "</table></form>";
			
			//echo $in['USER_TIP'];
			#GC 26/05/2015 upload file zip
			$upload_zip="";
			if($_GET['VISITNUM']==0 and $_GET['ESAM']==2) $upload_zip=1;
			if($_GET['VISITNUM']==1 and $_GET['ESAM']==23) $upload_zip=2;
			if($_GET['VISITNUM']==20 and $_GET['ESAM']==10) $upload_zip=3;
			
			if ($_GET ['VISITNUM_PROGR'] == '')
				$_GET ['VISITNUM_PROGR'] = 0;
			
			#GC 19/04/2016# Se lo studio e' chiuso -> non posso mostrare il caricamento da file zip in quanto non si potrebbero editare le schede.
			$sql_query = "select max(FINE) as FINE from {$service}_COORDINATE where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$_GET['VISITNUM']} and esam={$_GET['ESAM']} and visitnum_progr={$_GET['VISITNUM_PROGR']}";
			$sql = new query ( $conn );
			$sql->get_row ($sql_query);
			$doc_chiusi=$sql->row['FINE'];
			
			if($upload_zip!="" && $in['USER_TIP']=='DE' /*&& !$doc_chiusi*/){
				$body .= "<style>
									.fileUpload {
									    position: relative;
									    overflow: hidden;
									    margin: 10px;
									}
									.fileUpload input.upload {
									    position: absolute;
									    top: 0;
									    right: 0;
									    margin: 0;
									    padding: 0;
									    font-size: 20px;
									    cursor: pointer;
									    opacity: 0;
									    filter: alpha(opacity=0);
									}
									</style>
									<table class=\"table table-bordered\" width=\"95%\" cellspacing=\"2\" cellpadding=\"0\" border=\"0\" align=\"center\">
										<tr>
											<td colspan=$colspan align=center>
												<body>
													<form name=\"giulio\" id=\"g\" enctype=\"multipart/form-data\" method=\"post\" action=\"uploadZip.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&VISITNUM={$_GET['VISITNUM']}&VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&ESAM={$_GET['ESAM']}&USERID={$this->user->userid}&UPLOAD_ZIP={$upload_zip}\">
														<div class=\"fileUpload btn btn-primary\">
														<label>Selezionare il file zip:
															<input type=\"file\" name=\"zip_file\" />
															<!--button class=\"btn btn-purple\" type=\"file\" name=\"zip_file\" >
																<i class=\"fa fa-folder-open bigger-110\"></i>
																Sfoglia...
															</button-->
														</label>
														</div>
														
														<!--input type=\"submit\" name=\"submit\" value=\"Upload\" /-->
														<button class=\"btn btn-purple\" type=\"submit\">
															<i class=\"fa fa-cloud-upload bigger-110\"></i>
															Upload
														</button>
														
														</form>
													</body>
											</td>
										</tr>
									</table>";
			}
			$body .= "<br><br><a href=\"index.php?VISITNUM={$_GET['VISITNUM']}&CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&exams=visite_exams.xml\">&lt;&lt; {$this->config_service ['Torna_lista_schede']}</a>";
		}
		$ret ['body'] = $body;
		return $ret;
	}
	/**
	 * Genera il codice HTML della scheda
	 *
	 * @param String $xml
	 * @param boolean $col_modifica
	 * @param boolean $no_link_back
	 */
	function form($xml, $col_modifica = true, $no_link_back=false) {
		$this->session_vars ['form'] = $xml;
		$vlist = $this->vlist;
		$in = $this->session_vars;
		$conn = $this->conn;
		$service = $this->service;
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );

		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );

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
				
				else if (isset($_GET['FORCE_DOC_GEN'])){
					if ($in['VISITNUM']==0 && $in['ESAM']==2){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_DOC_CS'])){
					if ($in['VISITNUM']==1 && $in['ESAM']==23){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_CENTRO'])){
					if ($in['VISITNUM']==0 && $in['ESAM']==10){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_FARMACI'])){
					if ($in['VISITNUM']==0 && $in['ESAM']==6){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_DISPOSITIVI'])){
					if ($in['VISITNUM']==0 && $in['ESAM']==7){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_FARMACO_OSSERV'])){
					if ($in['VISITNUM']==0 && $in['ESAM']==15){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_TESSUTI'])){
					if ($in['VISITNUM']==0 && $in['ESAM']==5){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_DISPOSITIVI_OSSERV'])){
					if ($in['VISITNUM']==0 && $in['ESAM']==18){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}else if (isset($_GET['FORCE_DOC_VERB']) && isset($_GET['ID_SED'])){
					if ($in['VISITNUM']==2 && $in['ESAM']==20){
						$xml_form->make_html ($no_link_back,0,1);
					}
				}
				else
				$xml_form->make_html ($no_link_back);

				if ($this->pk_service != '' && $this->pk_service != 'next') {
					$this->make_patient_table ();
					$body = $this->patient_table;
					$body .= "<br>" . $this->tb_riassuntiva ();
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

				$body .= "
					<br>
					<p align=right>
						<a href=\"{$lvl_up}index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&REGISTRY={$this->xmr->prefix}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&eQuery&eform\">
						$link_equery
						</a>
					</p>
				";
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
	function all_in_form_view2($xml_form) {
		
		$this->session_vars ['form'] = $xml;
		$vlist = $this->vlist;
		$in = $this->session_vars;
		$conn = $this->conn;
		$service = $this->service;
		$sql_query = "select max(progr) as max_p from {$service}_coordinate where {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]} and esam={$in['ESAM']} and visitnum={$in['VISITNUM']} and VISITNUM_PROGR={$in['VISITNUM_PROGR']} and inizio is not null";
//		echo $sql_query;
		$sql = new query ( $conn );
		$sql->set_sql ( $sql_query );
		$sql->exec ();
		$sql->get_row ();
		$m_p = $sql->row ['MAX_P'];
		$max = $m_p - 0;
		if ($m_p == '' || $m_p == 0)
		$m_p ++;
		$real_progr = $_GET ['PROGR'];
		$next = $m_p + 1;
		if (isset ( $_GET ['PROGR'] )) {
			/*Controllo di visibilita*/
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
				Logger::send("myLog:".$sql_query);
				$sql_abil = new query ( $this->conn );
				$sql_abil->get_row ( $sql_query );
				if ($sql_abil->row ['FINE'] != 1 && ($sql_abil->row ['USERID'] != $this->user->userid && $in ['USER_TIP'] != 'DE')) {
					error_page ( $this->user->userid, $this->testo ( "userNotCenter" ), "" );
				}
			}
			$xml_form->make_html ();
			$script = "
				<script type=\"text/javascript\">
				" . $xml_form->salva_js . "
				" . $xml_form->invia_js . "
				" . $xml_form->check_js . "
				" . $xml_form->inrevisione_js . "
				</script>
				";
			$onload .= $xml_form->onload . ";";
			if ($this->pk_service != '' && $this->pk_service != 'next') {
				$this->make_patient_table ();
				$body = $this->patient_table;
				$body .= "<br>" . $this->tb_riassuntiva ();
			} else
			$body = '';
			$body .= $xml_form->body;
		} else {
			$colspan = 4;
			if (isset ( $xml_form->form ['FIELD_AGG'] )) {
				/*Modalita' con modifica diretta dei valori in schema riassuntivo*/
				$tr_agg = "<tr>";
				$fields_agg = explode ( "|", $xml_form->form ['FIELD_AGG'] );
				$fields_agg_txt = explode ( "|", $xml_form->form ['FIELD_AGG_TXT'] );
				if (isset ( $_GET ['ADDBLANK'] )) { /*Aggiunta di scheda vuota*/
					//echo $sql->row['MAX_P'];
					if($sql->row['MAX_P']!="") {
						if($sql->row['MAX_P']>=$_GET ['ADDBLANK'] || $sql->row['MAX_P']+1<$_GET ['ADDBLANK']) {
							error_page ( $remote_userid, "La scheda numero {$_GET ['ADDBLANK']} ?i?tata inserita. Non utilizzare il tasto back del browser o ritornare alla lista schede aggiornata.", "La scheda numero {$_GET ['ADDBLANK']} ?i?tata inserita. Non utilizzare il tasto back del browser o ritornare alla lista schede aggiornata." );
						}
					}
					if (! isset ( $_GET ['VISITNUM_PROGR'] ) || $_GET ['VISITNUM_PROGR'] == '')
					$_GET ['VISITNUM_PROGR'] = 0;
					$redirect = $_SERVER ['REQUEST_URI'];
					$redirect = str_replace ( "&ADDBLANK={$_GET['ADDBLANK']}", "", $redirect );
					$values ['INIZIO'] = 1;
					$values ['ABILITATO'] = 1;
					$values ['USERID'] = $this->user->userid;
					$values ['INSERTDT'] = sysdate;
					$values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
					$tb_prefix = "{$this->service}";
					$sql_query = "
								select count(*) as conto from {$tb_prefix}_coordinate
								where
									VISITNUM={$_GET['VISITNUM']}
									and
									VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}
									and
									ESAM={$_GET['ESAM']}
									and
									PROGR={$_GET['ADDBLANK']}
									and
									{$this->config['PK_SERVICE']}={$_GET[$this->config['PK_SERVICE']]}
							";
									$sql->get_row ( $sql_query );
									if ($this->integrazione->eq_enabled){
										if ($this->integrazione->eq_int=='') $this->integrazione->CreateEq();
										$values['INV_QUERY']=$this->integrazione->eq_int;
										$values['EQ_ACTION']=1;
									}
									if ($sql->row ['CONTO'] == 0) {
										$values ['VISITNUM'] = $_GET ['VISITNUM'];
										$values ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
										$values ['ESAM'] = $_GET ['ESAM'];
										$values ['PROGR'] = $_GET ['ADDBLANK'];
										$values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
										$tb_coord = $tb_prefix . "_coordinate";
										$pk = '';
										$sql->insert ( $values, $tb_coord, $pk );
									} else {

										$tb_coord = $tb_prefix . "_coordinate";
										$pk ['VISITNUM'] = $_GET ['VISITNUM'];
										$pk ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
										$pk ['ESAM'] = $_GET ['ESAM'];
										$pk ['PROGR'] = $_GET ['ADDBLANK'];

										$pk [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
										$sql->update ( $values, $tb_coord, $pk );
									}
									$pk = '';
									$values = '';
									$values ['VISITNUM'] = $_GET ['VISITNUM'];
									$values ['VISITNUM_PROGR'] = $_GET ['VISITNUM_PROGR'];
									$values ['ESAM'] = $_GET ['ESAM'];
									$values ['PROGR'] = $_GET ['ADDBLANK'];
									$values [$this->config ['PK_SERVICE']] = $_GET [$this->config ['PK_SERVICE']];
									$tb_ = $xml_form->form ['TABLE'];

									$sql->insert ( $values, $tb_, $pk );

									if ((isset ( $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['SFOGLIA_CALL'] )) && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['SFOGLIA_CALL'] == 'yes') {
										$redirect .= "&CALL_Sfoglia";
									}

									$this->conn->commit ();
									header ( "location:$redirect" );
									die ();
				}
				if (isset ( $_POST ['ApplMod'] )) {/*Applico le modifiche*/
					$redirect = $_SERVER ['REQUEST_URI'];
					$param='';
					foreach ($_GET as $key => $val){
						if ($key!='CALL_Sfoglia')
						$param.="$key=$val&";
					}
					$param=rtrim($param, "&");
					$redirect="index.php?{$param}";
					$table = $xml_form->form ['TABLE'];
					$visitnum = $_GET ['VISITNUM'];
					$esam = $_GET ['ESAM'];
					if ($_GET ['VISITNUM_PROGR'] != '')
					$visitnum_progr = $_GET ['VISITNUM_PROGR'];
					else
					$visitnum_progr = 0;
					foreach ( $fields_agg as $fk => $field ) {
						foreach ( $xml_form->fields as $key => $val ) {
							if ($val ['VAR'] == $field) {

								foreach ( $_POST as $pkey => $pval ) {
									$field = new field ( $xml_form, $key );

									if (preg_match ( "!^{$val ['VAR']}_PROGR_!", $pkey ) && ! preg_match ( "!D$!", $pkey ) && ! preg_match ( "!M$!", $pkey ) && ! preg_match ( "!Y$!", $pkey ) && ! preg_match ( "!RC$!", $pkey )) {
										$progr = str_replace ( "{$val ['VAR']}_PROGR_", "", $pkey );
										if ($val ['TYPE'] == 'radio') {
											$values [$progr] ["D_" . $val ['VAR']] = $field->values [$_POST [$val ['VAR'] . "_PROGR_" . $progr]];
										}
										if ($val ['TYPE'] == 'select') {
											$values [$progr] ["D_" . $val ['VAR']] = $field->values [$_POST [$val ['VAR'] . "_PROGR_" . $progr]];

										}
										$values [$progr] [$val ['VAR']] = $pval;
										if ($val ['TYPE'] == 'data') {
											if ($pval != '') {
												$values [$progr] [$val ['VAR']] = "to_date('{$pval}','DDMMYYYY')";
												$values [$progr] [$val ['VAR'] . "RC"] = "OKOKOK";
											} else
											unset ( $values [$progr] [$val ['VAR']] );
										}
									}
								}
							}
						}
					}
					foreach ( $values as $progr => $values_ ) {
						$pk [$this->config_service ['PK_SERVICE']] = $this->pk_service;
						$pk ['VISITNUM'] = $visitnum;
						$pk ['VISITNUM_PROGR'] = $visitnum_progr;
						$pk ['ESAM'] = $esam;
						$pk ['PROGR'] = $progr;
						if (count ( $values_ ) > 0) {
							//echo "<hr>$progr";
							$sql = new query ( $this->conn );
							$sql->update ( $values_, $table, $pk );
						}
					}
					if ($xml_form->form ['F_TO_CALL'] != '') {
						$f_to_call = $xml_form->form ['F_TO_CALL'];
						$f_to_call ( $xml_form );
					}
					$this->conn->commit ();
//					die("hiri");
					header ( "location:$redirect" );
					die ();
				}
				/*Header della tabella*/
				foreach ( $fields_agg_txt as $key => $val ) {
					$field_agg_txt .= "<td class=int>$val</td>";
				}
				foreach ( $fields_agg as $fk => $field ) {
					$colspan ++;
					foreach ( $xml_form->fields as $key => $val ) {
						if ($val ['VAR'] == $field) {
							$nextrow = count ( $type_fields_agg );
							foreach ( $val as $k => $v ) {
								$type_fields_agg [$nextrow] [$k] = $v;
							}
							$field_tot = '';
							$field_type="field_".$val['TYPE'];

							if ($val['TYPE']!='file_doc')
							$select_field .= "$field,";
							if (!class_exists($field_type)){
								include_once "libs/$field_type.inc";
							}
							$tr_agg.=call_user_func(array($field_type, "S_all_in"), $field, $m_p, $xml_form);
						}
					}
				}

				$rowspan = " rowspan='2'";
				$tr_agg .= "</tr>";
			}
			$sql = new query ( $this->conn );
			if ($_GET ['VISITNUM_PROGR'] == '')
			$visitnum_progr = 0;
			else
			$visitnum_progr = $_GET ['VISITNUM_PROGR'];
			$where_agg_eq='';
			if ($this->config_service['eQuerySpec']['Integrazione']['ON'] && (!$this->integrazione->eq_enabled || $this->integrazione->eq_int=='')) $where_agg_eq="and (INV_QUERY is null or EQ_ACTION=2)";
			$sql_query = "select min(fine) as fine from {$this->service}_coordinate where
			VISITNUM={$_GET['VISITNUM']}
			and esam={$_GET['ESAM']}
			and {$this->config_service['PK_SERVICE']}={$this->pk_service}
			and visitnum_progr=$visitnum_progr
			$where_agg_eq
			";
			$col_elimina = true;
			$sql->get_row ( $sql_query );
			if (($sql->row ['FINE'] == 1 || $this->session_vars ['USER_TIP'] != 'DE') && !($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo)) {
				$col_elimina = false;
				$closed_all = true;
				$rowspan = "";
				$tr_agg = "";
				$colspan --;
				$elimina_col = "";
			} else {
				$col_elimina = true;
				$closed_all = false;
				if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TRASH'] != '' && ($this->session_vars ['USER_TIP'] == 'DE' || $this->integrazione->eq_enabled))
				$elimina_col = "<td class='int' width='40' align='center' $rowspan>Elimina</td>";
			}
			$body.=$this->tb_riassuntiva();
			$body .= "
				<p align=center><b>{$vlist->esams[$in['VISITNUM']][$in['ESAM']]['TESTO']}</b></p>
				<form method=\"POST\" name=\"ALL_IN_FORMS\" action=\"index.php?VISITNUM_PROGR={$_GET['VISITNUM_PROGR']}&{$this->config_service['PK_SERVICE']}={$_GET[$this->config_service['PK_SERVICE']]}&ESAM={$_GET['ESAM']}&VISITNUM={$_GET['VISITNUM']}\">
				<table border=0 cellpadding=0 cellspacing=2 width=95%>";
			$col_modifica=true;
			if ($xml_form->form ['NO_MOD_COL'] != '')
			$col_modifica = false;
			if ($col_modifica)
			if (strtolower ( $this->config_service ['lang'] ) == 'en') {
				$col_modifica_header = "<td class=int width=40 align=center $rowspan>View/Update </td>";
				$col_num_txt = "Number";
			} else {
				$col_modifica_header = "<td class=int width=40 align=center $rowspan>Modifica/visualizza </td>";
				$col_num_txt = "N.ro";
			}
			$col_doc_header = "";
			$col_documento = false;
			if ($xml_form->form ['DOC_FIELD'] != ''){
				$col_documento = true;
				if (strtolower ( $this->config_service ['lang'] ) == 'en') {
					$col_doc_header = "<td class=int width=40 align=center $rowspan>Download Doc.</td>";
				} else {
					$col_doc_header = "<td class=int width=40 align=center $rowspan>Scarica Doc.</td>";
				}
			}
			if ($max > 0) {
				if ($xml_form->form ['TB_HEADER'] != '')
				$tb_header = "<td class=int $rowspan>{$xml_form->form['TB_HEADER']}</td>";
				else
				$tb_header = "";

				$body .= "
						<tr>
							<td class=int $rowspan>$col_num_txt</td>
							$tb_header
							$field_agg_txt
							$col_modifica_header
							$col_doc_header
							$elimina_col
						</tr>
						$tr_agg
						";
			}
			if ($in ['PROGR'] > $m_p)
			$m_p = $in ['PROGR'];
			if ($max > 0)
			$all_closed = true;
			$counter=0;

			$sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW
				from {$xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']}
				and visitnum_progr={$in['VISITNUM_PROGR']}
				and esam={$in['ESAM']}
				--and progr=$i
			order by progr
				";

			$sql = new query ( $conn );
			$sql->set_sql ( $sql_query );

			$sql->exec ();

			for($i = 1; $i <= $max; $i ++) {

				if ($_GET ['VISITNUM_PROGR'] == '')
				$_GET ['VISITNUM_PROGR'] = 0;
				$sql_query = "
								select
									*
								from {$service}_coordinate
								where visitnum={$_GET['VISITNUM']}
								and visitnum_progr={$_GET['VISITNUM_PROGR']}
								and esam={$_GET['ESAM']}
								and progr=$i
								and {$this->config_service['PK_SERVICE']}={$this->pk_service}
								";
				$sql_abil = new query ( $this->conn );
				if (!$sql_abil->get_row ( $sql_query )) continue;
				if ($sql_abil->row['ABILITATO']!=1) continue;
				$eq_new=false;
				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
					if ($sql_abil->row['EQ_ACTION']==1) {
						$eq_new=true;
					}
					//if ($sql_abil->row['EQ_ACTION']==2) continue;
				}else {
					if ($sql_abil->row['EQ_ACTION']==1) continue;
				}

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
								and progr=$i
								and {$this->config_service['PK_SERVICE']}={$this->pk_service}
								";
					$sql_abil = new query ( $this->conn );
					$sql_abil->get_row ( $sql_query );
					if ($sql_abil->row ['FINE'] != 1 && $sql_abil->row ['USERID'] != $this->user->userid)
					continue;
					$sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW
				from {$xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']}
				and visitnum_progr={$in['VISITNUM_PROGR']}
				and esam={$in['ESAM']}
				and progr=$i
				";
					$sql = new query ( $conn );
					$sql->set_sql ( $sql_query );

					$sql->exec ();
				}

				if ($sql_abil->row['FINE']==1) $this_close=true;
				else $this_close=false;
				$body .= "<tr>";
				$counter++;
				if ($i != $real_progr) {
					$in ['PROGR'] = $i;

					/*
					 $sql_query = "select $select_field {$xml_form->form['FIELD_TB_SHOW']} as FIELD_TB_SHOW from {$xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}='{$in[$this->config_service['PK_SERVICE']]}' and visitnum={$in['VISITNUM']} and visitnum_progr={$in['VISITNUM_PROGR']} and progr=$i";

					 $sql = new query ( $conn );
					 $sql->set_sql ( $sql_query );

					 $sql->exec ();
					 */
					$sql->get_row ();
					$TXT = $sql->row ['FIELD_TB_SHOW'];
					$TXT = preg_replace ( "!#(.*?)#!m", "<$1>", $TXT );

					if ($TXT != '')
					$tb_content = "<td class=sc4bis $css_style>$TXT</td>";
					else
					$tb_content = "";
					$add_txt='';
					if ($eq_new) $add_txt="<img src=\"images/eq_img.png\" width=15px>";
					if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $sql_abil->row['EQ_ACTION']=='2') {

						$add_txt="<img src=\"images/iphone_delete_icon.png\">";
					}
					$body .= "
							<td class=sc4bis $css_style><b>$add_txt $counter</b></td>
							$tb_content
							";
							$progr = $in ['PROGR'];
							//if (($xml_form->closed_form ( $progr ) || $this->session_vars ['USER_TIP'] != 'DE') && !($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo)) {
							//	$this_closed = true;
							//} else
							//	$this_closed = false;

							if (isset ( $type_fields_agg )) {
								foreach ( $type_fields_agg as $key => $val ) {
									//										print_r($val);
									$var = $val ['VAR'];
									$field_type = "field_{$val['TYPE']}";
									if (!class_exists($field_type)){
										include_once "libs/$field_type.inc";
									}
									$field_obj = new $field_type ( $xml_form, $xml_form->vars [$var], $xml_form->conn, $xml_form->tb_vals, $xml_form->session_vars, $xml_form->service, $xml_form->errors );
									$ret = $field_obj->all_in ( $var, $i, $sql->row, $this_close );

									if ($sql_abil->row['EQ_ACTION']=='') $ret = $field_obj->all_in ( $var, $i, $sql->row, $this_close );
									if ($sql_abil->row['EQ_ACTION']=='2') $ret = $field_obj->all_in ( $var, $i, $sql->row, true );
									$body .= $ret ['body'];
									$c1_agg .= $ret ['c1_agg'];
									if ($ret['last_call_sfoglia']!=''){
										$last_call_sfoglia=$ret['last_call_sfoglia'];
									}
								}
							}

							$progr = $in ['PROGR'];
							if (! $xml_form->closed_form ( $progr ) || ($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo)) {
								$all_closed = false;
								if ($col_modifica){
									$col_modifica_td = "<td class=sc4bis align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}\"><img src=\"images/pen.png\" border=0></a></td>";
								}
								$body .= $col_modifica_td;
								
								if ($col_documento){
									$body .= "
											<td class=sc4bis align=center width=\"100px;\">
											<a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&ELIMINA_LA_SCHEDA=yes\">
												<img src=\"images/pdf.png\" border=\"0\" />
											</a>
											</td>";
								}
								
								if (! $xml_form->closed_form ( $progr ) || $this->integrazione->eq_enabled){
									if ($this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TRASH'] != '' &&
									((($this->session_vars ['USER_TIP'] == 'DE' && $sql_abil->row['USERID']=='') || $sql_abil->row['USERID']==$this->user->userid) || ($this->integrazione->eq_enabled && $this->integrazione->role==$this->user->profilo) || !$this->integrazione->eq_enabled)
									) {
										if ($sql_abil->row['EQ_ACTION']=='2'){
											$body .= "
											<td class=sc4bis align=center>
											{$add_txt}Scheda eliminata
											</td>";
										}else if ($col_elimina){//if($this->integrazione->stato!=2){
											$body .= "
											<td class=sc4bis align=center><a onclick=\"if (!confirm('E\\' sicuro di voler eliminare la scheda: {$this->vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['TESTO']}?')) return false;\" href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}&ELIMINA_LA_SCHEDA=yes\">
												1<img src=\"images/trash.png\" border=0>
											</a></td>";
										}else{
											//$body .= "<td class=sc4bis align=center>&nbsp;</td>";
										}
									}
								}
							} else {
								if ($col_modifica)
									$col_modifica_td = "<td class=sc4bis align=center><a href=\"index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$i}\"><img src=\"images/lente.gif\" border=0></a></td>";
								$body .= "$col_modifica_td";
								if (! $closed_all)
									$body .= "<!--td class=sc4bis>&nbsp;</td-->";
							}
							$body .= "</tr>";
				}
			}

			if ($max == 0)
			$next = 1;
			if (isset ( $xml_form->form ['FIELD_AGG'] ) && ($this->session_vars ['USER_TIP'] == 'DE' || $this->integrazione->eq_enabled)) {
				if (isset ( $_GET ['CALL_Sfoglia'] ) && $last_call_sfoglia != '')
				$body .= "
							<script>
							apri_window('/$last_call_sfoglia');
							</script>";
				if (isset ( $_GET ['JUST_DELETE'] ) )
				$body .= "
							<script>
							document.forms['ALL_IN_FORMS'].submit();
							</script>";
				if (! $all_closed &&  $this->integrazione->stato!=2 )
				$body .= "
							<tr>
								<td colspan=$colspan align=center>
								<font color=red><b>Attenzione &egrave; necessario applicare le modifiche con il pulsante apposito</b></font><br>
									<input type='hidden' name='ApplMod' value='Salva le modifiche'>
									<input type='submit' name='ApplMod_button' value='Applica Modifiche' onclick=\"
										f=document.forms[0];
										el=f.elements;
										specifiche='A=ON&L=0&F=0';
								  		c1='';
								  		$c1_agg;
										rc=contr(c1,specifiche);
								  		if (rc) return false;
									\">
								</td>
							</tr>";
			}
			$add_progr = $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['ADD_PROGR'];
			if (! isset ( $this->config_service ['Aggiungi_nuova_scheda'] )) {
				$this->config_service ['Aggiungi_nuova_scheda'] = 'Aggiungi nuova scheda';
			}
			$where_agg_eq='';
			if ($this->config_service['eQuerySpec']['Integrazione']['ON'] && (!$this->integrazione->eq_enabled || $this->integrazione->eq_int=='')) $where_agg_eq="and (INV_QUERY is null or EQ_ACTION=2)";
			$sql_visitclose = "select min(visitclose) as closed
			from {$service}_coordinate where visitnum={$_GET['VISITNUM']}
			and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
			$where_agg_eq
			";

			$sql_c = new query ( $this->conn );
			$sql_c->get_row ( $sql_visitclose );
			if ($sql_c->row ['CLOSED'] == 1)
			$visit_closed = true;
			else
			$visit_closed = false;
			if (
			(
			(!$visit_closed && $in ['USER_TIP'] == 'DE')
			|| ($this->integrazione->eq_enabled  && $this->integrazione->stato!=2 && $this->integrazione->role==$this->user->profilo)
			)
			&& $add_progr != 'no' && $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['NEXT_ENABLED'] != 'no') {
				if (isset ( $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['ADD_BLANK'] )) {
					//echo "<li>{$_SERVER['REQUEST_URI']}&ADDBLANK=$next</li>";
					$button = "<input type=\"button\"
								onclick=\"window.location.href='{$_SERVER['REQUEST_URI']}&ADDBLANK=$next'\"
							value=\"{$this->config_service['Aggiungi_nuova_scheda']}\">";
				} else
				$button = "<input type=\"button\" onclick=\"window.location.href='index.php?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&PROGR={$next}'\" value=\"{$this->config_service['Aggiungi_nuova_scheda']}\">";
				$body .= "
						<tr>
							<td colspan=$colspan align=center>
							$button
							</td>
						</tr>";
			}

			if (isset ( $this->config_service ['Note'] [$_GET ['VISITNUM']] [$_GET ['ESAM']] )) {
				$body .= "<tr><td colspan=$colspan align=center style=\"color:red\">{$this->config_service['Note'][$_GET['VISITNUM']][$_GET['ESAM']]}</td></tr>";
			}
			$body .= "</table></form>";
			$body .= "<br><br><a href=\"index.php?VISITNUM={$_GET['VISITNUM']}&CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&exams=visite_exams.xml\">&lt;&lt; {$this->config_service ['Torna_lista_schede']}</a>";
		}
		$ret ['body'] = $body;
		return $ret;
	}
	
	
	var $show_gantt = false;
	
	var $dettaglio;
	
	function build_dettaglio(){
		//global $service;
		$SQL = new query($this->conn);
		$SQL->get_row("SELECT * FROM {$this->service}_REGISTRAZIONE WHERE {$this->xmr->pk_service} = '{$this->pk_service}'");
		$this->dettaglio = $SQL->row;
		//STATO
		$q = "
			SELECT NVL (s.id_stato, 1) AS stato, ss.DECODE AS stato_dec
			FROM   {$this->service}_registrazione r, {$this->service}wf_stato s, {$this->service}wf_stati ss
			WHERE  s.pk_service(+) = r.{$this->xmr->pk_service} AND ss.id = NVL (s.id_stato, 1) AND r.{$this->xmr->pk_service}='{$this->pk_service}'";
		$SQL->get_row($q);		
		$this->dettaglio['STATO'] = $SQL->row['STATO_DEC'];
		$this->dettaglio['STATO_INT'] = $SQL->row['STATO'];
		
		if ($this->service == "CE"){
			$q = "
				SELECT *
				FROM   {$this->service}_reginvio r
				WHERE r.{$this->xmr->pk_service}='{$this->pk_service}'";
			$SQL->get_row($q);
			$this->dettaglio['RICEZI_DT'] = $SQL->row['RICEZI_DT'];		
			$this->dettaglio['DELIB_NUM'] = $SQL->row['DELIB_NUM'];
		}
		
	}
	function tb_riassuntiva(){
		$output = "";
		return $output;
	}
		
	function getProfilo($userid){
		$SQL = new query($this->conn);
		$SQL->get_row("SELECT * FROM ANA_UTENTI_2 WHERE USERID = '{$userid}'");
		return $SQL->row['PROFILO'];
	}

	function getIdCe($userid){
		$SQL = new query($this->conn);
		$SQL->get_row("SELECT * FROM ANA_UTENTI_2 WHERE USERID = '{$userid}'");
		return $SQL->row['ID_CE'];
	}

	function isNew($table, $pkid, $visitnum, $esam){
		$array['ID_STUD'] =  $pkid;
		$array['ESAM'] = $esam;
		$array['VISITNUM'] = $visitnum;
		$sql = "select not_new from ".$table." where {$this->xmr->pk_service}=:id_stud and visitnum=:visitnum and esam=:esam ";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		$query->get_row();
		return ($query->row['NOT_NEW'] != 1);
	}

	function isSent($table, $pkid, $visitnum, $esam){
		$array['ID_STUD'] =  $pkid;
		$array['ESAM'] = $esam;
		$array['VISITNUM'] = $visitnum;
		$sql = "
			select fine from ".$table." where {$this->xmr->pk_service}=:id_stud and visitnum=:visitnum and esam=:esam ";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		$query->get_row();
		return ($query->row['FINE'] == 1);
	}
	
	function setNew($table, $pkid, $visitnum, $esam, $value){
		$array['ID_STUD'] =  $pkid;
		$array['ESAM'] = $esam;
		$array['VISITNUM'] = $visitnum;
		$array['VALUE'] = "1";
		if ($value){
			$array['VALUE'] = "";
		}
		$sql = "
			update ".$table." set not_new=:value where {$this->xmr->pk_service}=:id_stud and visitnum=:visitnum and esam=:esam ";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		return true;
	}
	
	function isNewGeneric($table, $pkid, $pairs){
		//$array['ID_STUD'] =  $pkid;
		$sql = "select not_new from ".$table." where {$this->xmr->pk_service}={$pkid} ";
		$keys = array_keys($pairs);
		foreach ($keys as $k){
			$sql .= " and $k='{$pairs[$k]}' ";
		}
		$query = new query($this->conn);
		//echo $sql;
		$query->exec($sql);
		if ($query->get_row()){
			return ($query->row['NOT_NEW'] != 1);
		}else{
			return false;
		}
	}
	function setNewGeneric($table, $pkid, $pairs, $value){
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "1";
		if ($value){
			$array['VALUE'] = "";
		}
		$sql = "update ".$table." set not_new=:value where {$this->xmr->pk_service}=:id_stud ";
		$keys = array_keys($pairs);
		foreach ($keys as $k){
			$sql .= " and $k='{$pairs[$k]}' ";
		}
		$query = new query($this->conn);
		$query->exec($sql, $array);
		return true;
	}
	
	function openEmendamento($pkid){
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "1";
		$sql = "update {$this->service}_REGISTRAZIONE set IN_EMENDAMENTO=:value where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		return true;		
	}
	function inEmendamento($pkid){
		$array['ID_STUD'] =  $pkid;
		$sql = "select IN_EMENDAMENTO from {$this->service}_REGISTRAZIONE where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		if ($query->get_row()){
			return ($query->row['IN_EMENDAMENTO'] == 1);
		}else{
			return false;
		}
	}
	function inviaEmendamento($pkid){
		//LUIGI: disattivo vecchia tipologia emendamento
		#GC 06/11/2014# Bypasso le operazioni delle integrazioni
		/*$this->integrazione->inviaPerApprovazione();
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "1";
		$sql = "update {$this->service}_REGISTRAZIONE set IN_EMENDAMENTO_APPROVAZIONE=:value where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);*/
		#FINE
		
		/*
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "0";
		$sql = "update {$this->service}_REGISTRAZIONE set IN_EMENDAMENTO=:value where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		*/
		//GIULIO 31-01-2013// Chiudo la scheda di documentazione EME quando invio la richiesta di EME per evitare ulteriori inserimenti di docs in fase di verifica documentazione.
		$v_num=20;
		//$array_c['LAST_EME'] = $this->getMaxVprogr($pkid,$v_num);
//		$array_c['CURR_EME'] = $this->session_vars ['VISITNUM_PROGR'];
//		$array_c['ID_STUD'] =  $pkid;
//		$array_c['VALUE'] = "1";
//		$array_c['E_NUM'] = "10";
//		$array_c['V_NUM'] = "20";
//		$sql = "update {$this->service}_COORDINATE set FINE=:value where {$this->xmr->pk_service}=:id_stud and esam=:e_num and visitnum=:v_num and visitnum_progr=:curr_eme";
//		$query = new query($this->conn);
//		$query->exec($sql, $array_c);
		
		#Apro la prossima richiesta di emendamento
		$vprogr=$_GET['VISITNUM_PROGR'];
		$esam=1;
		$progr=1;
		$this->openEsamProgr($pkid,$v_num,$vprogr+1,$esam,$progr, false, false);
		
		//$esam=10;
		//$this->openEsamProgr($pkid,$v_num,$vprogr+1,$esam,$progr, false, false);
		
		
	}
	function integraEmendamento($pkid){
		
		//GIULIO 31/01/2013 - Riapro la scheda docs eme se ho un'istruttoria negativa o parere sospensivo.
		$v_num=20;
		//LUIGI: disattivo vecchia tipologia emendamento
		#GC 06/11/2014# Nuova gestione EME e riapertura schede. Non ho bisogno di riaprire i docs. Posso sempre inserirne
		/*
		$array_c['LAST_EME'] = $this->getMaxVprogr($pkid,$v_num);
		$array_c['ID_STUD'] =  $pkid;
		$array_c['VALUE'] = "0";
		$array_c['E_NUM'] = "10";
		$array_c['V_NUM'] = "20";
		$sql = "update {$this->service}_COORDINATE set FINE=:value where {$this->xmr->pk_service}=:id_stud and esam=:e_num and visitnum=:v_num and visitnum_progr=:last_eme";
		$query = new query($this->conn);
		$query->exec($sql, $array_c);*/
		#FINE
		
		//Luigi: non andiamo pi?integrazione emendamento bens?iapriamo la scheda iniziale
		//$this->integrazione->stornaPerIntegrazione();
		
		//print_r($_POST);
		//echo $pkid;
		//echo $this->session_vars ['VISITNUM_PROGR'];
		
		$array_eme['ID_STUD'] =  $pkid;
		$array_eme['VALUE'] = "0";
		$array_eme['VISITNUM_PROGR']=$this->session_vars ['VISITNUM_PROGR'];
		$sql = "update {$this->service}_COORDINATE set FINE=:value where {$this->xmr->pk_service}=:id_stud and esam=1 and visitnum=$v_num and visitnum_progr =:visitnum_progr and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array_eme);		
		#FINE

		
		/*
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "0";
		$sql = "update {$this->service}_REGISTRAZIONE set IN_EMENDAMENTO=:value where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		*/
	}
	function closeEmendamento($pkid, $accetta = false){
		//echo $accetta;
		//echo "<br/><br/>";
		//print_r($this->xml_dir);
		//die("ALT!");
		if ($accetta){
			$this->integrazione->ApprovaEq($this->vlist,$this->xml_dir,$this->xmr->config_service,$this->session_vars,$this->uploaded_file_dir);
		}else{
			$this->integrazione->respingiEq($this->vlist,$this->xml_dir,$this->xmr->config_service,$this->session_vars,$this->uploaded_file_dir);
		}
		//die("ALT!");
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "0";
		$sql = "update {$this->service}_REGISTRAZIONE set IN_EMENDAMENTO=:value, IN_EMENDAMENTO_APPROVAZIONE=:value where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		//TODO: Accetta modifiche integrazione
		return true;		
	}
	
	function Controller(){
		
	//Luigi: controlli di accesso sulle force
	if ($this->pk_service != 'next'){
		if ((isset($_GET['FORCE_DOC_GEN']) || isset($_GET['FORCE_FARMACI']) || isset($_GET['FORCE_DISPOSITIVI']) || isset($_GET['FORCE_FARMACO_OSSERV']) || isset($_GET['FORCE_TESSUTI']) || isset($_GET['FORCE_DISPOSITIVI_OSSERV'])) && ($this->user->profilo!='Segreteria CE' && $this->user->userid!=$this->dettaglio['USERID_INS'])) {
	  	$this->body.="<p align='center' style=\"color:#077f7f;font-size:18px;\"><b>		Funzione non disponibile all'utente corrente </b></p><br>
	  	<a href=\"javascript:history.back();\">&lt;&lt;Torna indietro</a>
	  	";
	  	return;
	  }
	  $nucleoabilitato = false;
	  $progr_ce=$_GET['VISITNUM_PROGR']+1;
		$sql_query_ce = "select count(*) as CONTO_CE from ce_veneto_nucleo_userid where id_nucleo=(
					  select id_nucleo from ce_veneto_nucleo where id_str=(
				    select centro from ce_centrilocali where id_stud='{$this->pk_service}' and progr='{$progr_ce}'
				  	)
					) and userid='{$this->user->userid}'";
		$sql_ce = new query ( $this->conn );
		$sql_ce->get_row ( $sql_query_ce );
		if ($sql_ce->row['CONTO_CE'] == '1') {
			$nucleoabilitato = true;
		}
	  if (isset($_GET['FORCE_DOC_CS']) && ($this->user->profilo!='Segreteria CE' && !($this->user->profilo=='Unita di ricerca' && $nucleoabilitato==true))) {
	  	$this->body.="<p align='center' style=\"color:#077f7f;font-size:18px;\"><b>		Funzione non disponibile all'utente corrente </b></p><br>
	  	<a href=\"javascript:history.back();\">&lt;&lt;Torna indietro</a>
	  	";
	  	return;
	  }
	}



		//echo "UT: {$this->session_vars ['USER_TIP']}";
		if ($_GET['VISITNUM'] == 0 && $_GET['ESAM'] == 0 && !$_GET[$this->xmr->pk_service]){
			//Insert in coordinate
			$profilo = $this->getProfilo($this->user->userid);
			switch ($profilo){
				case "PRI":
				case "URC":
				case "SGR":
					$this->session_vars ['USER_TIP'] = "DE";
					break;
				default:
					break;
			}
			//print_r($this->user);
			//die();
		}
		
		if ($_GET[$this->xmr->pk_service] && is_numeric($_GET[$this->xmr->pk_service])){
			$this->build_dettaglio();
		}
		
		//Cancellazione
		if ($_GET ['delete'] == 'delete') {
			if (is_numeric($_GET[$this->xmr->pk_service])){
				//$sql_query="select primo_invio from {$this->service}_registrazione where {$this->xmr->pk_service}={$_GET[$this->xmr->pk_service]}";
				//$query=new query($this->conn);
				//$query->get_row($sql_query);
				//if ($query->row['PRIMO_INVIO']!=''){	
				//	header ( "location: index.php?deleted=no" );
				//	die ();
				//}else{
					$sql_delete = "delete from {$this->service}_coordinate where {$this->xmr->pk_service}={$_GET[$this->xmr->pk_service]}";
					$sql = new query ( $this->conn );
					$sql->set_sql ( $sql_delete );
					$sql->ins_upd ();
					$this->conn->commit ();
					header ( "location: index.php?deleted=yes" );
					die ();
				//}
			}else{
				die ("ID Non riconosciuto.");
			}
		}
		
		if ($_GET ['deleted'] == 'yes') {
			$this->body.= "<br><br><p style=\"font-size:20px\" align=center><b>Lo studio &egrave; stato eliminato con successo!<br>
			<a href='index.php'>Torna alla home page</a>
			</p>";
		}
		
		if ($_GET ['deleted'] == 'no') {
			$this->body.= "<br><br><p style=\"font-size:20px\" align=center><b>Non &egrave; possibile eliminare questo studio!<br>
			<a href='index.php'>Torna alla home page</a>
			</p>";
		}
		
		//Fine cancellazione

		if (isset($_POST['EQUERY_INT'])){
			//die("PINCOPALLO");
			$this->SaveEqInt();
		}

		if ($_GET ['ELIMINA_LA_SCHEDA'] == 'yes') {
			$this->pk_service = $_GET [$this->config_service ['PK_SERVICE']];
			$esam = $_GET ['ESAM'];
			$visitnum = $_GET ['VISITNUM'];
			$visitnum_progr = $_GET ['VISITNUM_PROGR'];
			$progr = $_GET ['PROGR'];
			$center = $_GET['CENTER'];
			
			//Luigi: commento la forzatura del center perch?rea problemi sotto ce_veneto per la cancellazione
			/* if (!$center){
				$center = $this->config_service['CENTER_TB'];
			} */
			
			//print_r($this->config_service);
			//die($visitnum." - ".$visitnum_progr." - ".$esam." - ".$progr);
			
			//Vecchia funzione di elimina esam progressivo che utilizzava dario
			//$this->DeleteProgrEsam_dario ( $visitnum, $visitnum_progr, $esam, $progr, $center, false );
			
			//Nuova
			$this->DeleteProgrEsam ("", $visitnum, $visitnum_progr, $esam, $progr);
			
			//die($visitnum." - ".$visitnum_progr." - ".$esam." - ".$progr);
			header("location: index.php?CENTER=$center&{$this->config_service['PK_SERVICE']}={$this->pk_service}&VISITNUM=$visitnum&ESAM=$esam&VISITNUM_PROGR=$visitnum_progr");
			//die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=index.php?exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}&CENTER=$center&JUST_DELETE=yes\"></head></html>" );
			
			die();
			
		}
				
		//echo "UT: {$this->session_vars ['USER_TIP']}";
		
		
		
		parent::Controller();
		
		
		////////// --- MUTUATI DA OSSC --- ////////				
		

		if (isset($_GET['NextWFStep'])){
			$this->body .= $this->WF_next_step();
		}
		if (isset ( $_GET ['CheckSchede'] )) {
			$this->WF_check();
		}
		if (isset ($_GET['CloseSchede'])){
			$this->CloseSchede();
		}
		if (isset ($_GET['CloseVisitProgr'])){
			$this->CloseSchedeProgr();
		}
		
		/* Chiama la funzione per gestire L'expected weekly visit list */
		if($this->session_vars['SHOW_CAL_WEEKLY'] == 1){
			// $vlist = new xml_esams_list ( $this->xml_dir."/".$this->visit_structure_xml,$this->config_service, $session_vars,$this->conn, $this->xml_dir);
			$out=$this->vlist->cal_weekly_sedute($this->session_vars['HIGHLIGHT']);
			// Logger::send($this->vlist);
			$this->body = $out;
		}
		
		/* Chiama la funzione per gestire L'expected monthly visit list */
		if($this->session_vars['SHOW_CAL_MONTHLY'] == 1){
			// $vlist = new xml_esams_list ( $this->xml_dir."/".$this->visit_structure_xml,$this->config_service, $session_vars,$this->conn, $this->xml_dir);
			$out=$this->vlist->cal_monthly_sedute($this->session_vars['HIGHLIGHT']);
			// Logger::send($this->vlist);
			$this->body = $out;
		}
		
		if (isset($_GET['Integrazione'])){
			$this->body .= $this->WF_integrazione();
		}
		
		if (isset($_GET['Approva'])){
			$this->body .= $this->WF_valutabile();
		}
		
		if (isset($_GET['InviaEmendamento'])){
			$this->emendamento_invia_per_approvazione();
		}
		
		if (isset($_GET['Ritira'])){
			$this->body .= $this->ritiraPage();
		}
		
		if (isset($_GET['ShowRitiro'])){
			$this->body .= $this->mostraRitiro();
		}
		
		if (isset($_GET['Contatti'])){
			$this->body .= "			
						<table id='tab_contentfaq' width='80%' cellpadding='2' cellspacing='2' >
						<tr>
							<td align='center' width='80' valign='top' border='10' style='height: 10px;'> </td>
						</tr>
							<tr>
								<td class='titolo' valign='top' align='center'>Contatti</td>
							</tr>
							<tr>
								<td>
									<ul>
										<li>
										Email: <a href='mailto:help_comitatietici@cineca.it'>help_comitatietici@cineca.it</a>
										</li>
										<br>
										<li>
										Telefono: 051-6171822
										</li>
									</ul>
								</td>
							</tr>
						</table>";
		}
		
		if (isset($_GET['Help'])){
			$help_file = fopen("help.htm", "r") or die("Unable to open file!");
			$help_txt= fread($help_file,filesize("help.htm"));
			fclose($help_file);
			//$this->body .= "qui luigi";			
			$this->body .= $help_txt;					
		} 
		  
		//Riapertura??? - da mutuare?
		
		////////// --- FINE MUTUATI DA OSSC --- ////////
		
		//Debug
		//$this->body .= "CPS: ".$config_param['service'];
		//$this->body .= "INTEG_EN ".$this->integrazione->eq_enabled;
		
		if (isset($this->session_vars['CMELayer'])){
			$this->body.='<br>';
			$this->body.=$this->tb_riassuntiva();
			$this->body.='<br>';
			include_once("CMELayer.inc");
			$configuration['baseUri']=$_SERVER['PHP_SELF'].'?ID_STUD='.$_GET['ID_STUD'].'&';
			$configuration['SERVICE']=$this->service;
			$configuration['PK_SERVICE']='ID_STUD';
			if(isset($this->session_vars['ID_STUD']) && !isset($this->session_vars['CMELFolder']))$this->session_vars['CMELFolder']=$this->session_vars['ID_STUD'];
			$configuration['ID_STUD']=$this->session_vars['ID_STUD'];
			$configuration['queryNames'][]='DOC_CORE_CME';
			$configuration['queryNames'][]='DOC_CENTRO_CME';
			$configuration['queryNames'][]='DOC_DELIB_AMM_CME';
			$configuration['queryNames'][]='DOC_DELIB_ASS_CME';
			$configuration['queryNames'][]='DOC_DELIB_POL_CME';
			$configuration['queryNames'][]='DOC_DELIB_STIP_CME';
			
//			$configuration['queryNames'][]='DOCUMENTAZIONE_SAT';
//			$configuration['queryNames'][]='RAPPORTO_VALUT';
//			$configuration['queryNames'][]='RAPPORTO_VALUT_SAT';
//			$configuration['queryNames'][]='RAPPORTO_VALUT_ISS';
//			$configuration['queryNames'][]='DOCUMENTAZIONE_EME';
			//print_r($configuration);
			$CME=new CMELayerWCA($this->conn,$configuration,$this->session_vars,$this->config_service);
			$CME->controller();
			$this->body.=$CME->html;

			//vecchio sistema:
			//$this->DocumentazionePratica();
			//$this->body.="<a href=\"index.php\">&lt;&lt;Torna alla home del sistema</a>";
		}
		
	}


	/**
	 * Menu a briciola di pane
	 *
	 * @param String $type
	 * @param array $dynamic_link_text
	 * @return String
	 */
	function breadcrumb($type, $dynamic_link_text='') {
		/*
		 * Il termine inglese 'breadcrumb'
		 * (letteralmente 'briciola di pane')
		 * fa riferimento alla favola di Grimm, Hansel e Gretel,
		 * che racconta la storia di due bambini perduti nel bosco che ...
		 * ...
		 * ...
		 * e poi sono morti tutti.
		 *
		 */
		$in = $this->session_vars;
		$percorso [0] ['TESTO'] = $this->testo ( 'Home' );
		$percorso [0] ['HREF'] = $this->href ( 'Home', $this->xmr->depth );

		switch ($type) {
			case 'form' :
				if (isset ( $this->session_vars ['CENTER'] )) {
					if ($this->xmr->depth > 0) {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti', $this->xmr->depth );
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' ) . "($this->service)";
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );
					} else {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );
					}
				} else if (isset ( $this->centers )) {
					if ($this->xmr->depth > 0) {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri', $this->xmr->depth );
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' ) . " ($this->service)";
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri' );

					} else {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri' );
					}
				}

				if ($this->pk_service != '' && $this->pk_service != "next") {
					if ($this->xmr->depth > 0)
					$percorso [] ['TESTO'] = $this->testo ( 'Vista Paziente' ) . " ($this->service)";
					else
					$percorso [] ['TESTO'] = $this->testo ( 'Vista Paziente' );
					$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Vista Paziente' );

				}
				$percorso [] ['TESTO'] = $dynamic_link_text;
				break;
			case 'patients_list' :
				//nuovo modo, solo lista centri valorizzato
				if ((isset ( $this->session_vars ['list'] ) && $this->session_vars ['list'] == 'patients_list.xml') || isset ( $_GET ['lista'] )) {
					if (isset ( $this->session_vars ['CENTER'] )) {
						if ($this->xmr->depth > 0) {
							$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
							$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti', $this->xmr->depth );
							$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' ) . " ($this->service)";
							$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );

						} else {
							$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
							$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );
						}
					} else if (isset ( $this->centers )) {
						if ($this->xmr->depth > 0) {
							$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' );
							$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri', $this->xmr->depth );
							$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' ) . " ($this->service)";
							$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri' );

						} else {
							$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' );
							$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri' );
						}
					}
				}else {
					if ($this->xmr->depth > 0) {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti', $this->xmr->depth );
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' ) . " ($this->service)";
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );

					} else {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );
					}
				}

				//type=exam_list
				break;
			case 'altra_list' :
				//tutto uguale a patients_list, ma prendo un altro titolo (dalla scheda stessa)
				//nuovo modo, solo lista centri valorizzato
						$percorso [] ['TESTO'] = $dynamic_link_text;
						$percorso [count ( $percorso ) - 1] ['HREF'] = $dynamic_link_text;

				//type=exam_list
				break;
			case 'exam_list' :
				if (isset ( $this->session_vars ['CENTER'] )) {
					if ($this->xmr->depth > 0) {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti', $this->xmr->depth );
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' ) . " ($this->service)";
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );
					} else {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Pazienti' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Pazienti' );
					}
				} else if (isset ( $this->centers )) {
					if ($this->xmr->depth > 0) {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri', $this->xmr->depth );
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' ) . " ($this->service)";
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri' );

					} else {
						$percorso [] ['TESTO'] = $this->testo ( 'Registro Lista Centri' );
						$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'Registro Lista Centri' );
					}
				}
				if (isset ( $this->session_vars ['exams'] ) && isset ( $this->session_vars ['CENTER'] )) {

					$percorso [] ['TESTO'] = $this->testo ( 'Vista Paziente' );

				}
				break;
			case 'search' :
				$percorso [] ['TESTO'] = $this->testo ( 'Search' );
				break;
			case 'equery' :
				//				print_r($in);
				//				$percorso[]['TESTO']=$this->testo('Equery');
				if (! isset ( $in ['eform'] ) && ! isset ( $in ['eform'] )) {
					$percorso [] ['TESTO'] = "<b>" . $this->testo ( 'eQueryList' ) . "</b>";
				} else {
					$percorso [] ['TESTO'] = $this->testo ( 'eQueryList' );
					$percorso [count ( $percorso ) - 1] ['HREF'] = $this->href ( 'eQuery List' );
					if (! isset ( $in ['ID'] )) {
						$percorso [] ['TESTO'] = '<b>'.$this->testo ( 'newEquery' ).'</b>';
					} else {
						$sql_dati_query = "select * from {$this->xmr_root->prefix}_equery where id=:eq_id";
						$sql = new query ( $this->conn );
						//$sql->set_sql ( $sql_dati_query );
						unset($bind);
						$bind['EQ_ID']=$in['ID'];
						$sql->exec ($sql_dati_query,$bind);//binded
						$sql->get_row ();
						$dati_equery = $sql->row;
						$percorso [] ['TESTO'] = "<b>eQuery n.ro {$sql->row['ID']}</b>";
					}
				}
				break;
				case 'gest_profili' :
					$percorso [] ['TESTO'] = "<b>" . $this->testo ( 'gest_prof' ) . "</b>";

		}

		$percorso_html = "";
		$n_links = count ( $percorso );
		foreach ( $percorso as $key => $link ) {
			if ($key != $n_links - 1)
			$percorso_html .= "<a href=\"{$link['HREF']}\" >{$link['TESTO']}</a> &gt; ";
			else
			$percorso_html .= $link ['TESTO'];
		}
		
		#GC 19/11/2015 NUOVA_GRAFICA
		//$percorso_html = "<div id=\"breadcrumbs\" class=\"breadcrumbs\">$percorso_html</div>";
		$percorso_html = "<div id=\"breadcrumbs\" class=\"breadcrumbs\">
												<ul class=\"breadcrumb\">
													<li>
														<i class=\"icon-home home-icon\"></i> $percorso_html 
													</li>
												</ul>	
											</div>";
											
		return $percorso_html;
	}	
	
	////////// --- MUTUATI DA OSSC --- ////////
	
	//Luigi 5/12/2014 ListPage disattivata in favore della ListPage in study.inc.php
	
	/* function ListPage($percorso_base = null) {
	
		
		$list = $_GET ['list'];
		if ($list == '')
		$list = 'patients_list.xml';
		if (isset ( $this->workflow ) && ($list == 'patients_list.xml' || stristr($list,'patients_list'))) {
			$prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
			$list = str_replace ( ".xml", "_{$prof_add}.xml", $list );
		}
		$list_o = new xml_list ( $this->xml_dir . "/" . $list, null, null, null, null, $this->session_vars, $this->visit_structure );

		//Nuovo modo di generare il menu briciola di pane
		$this->percorso = $this->breadcrumb ( "patients_list" );
		$this->body .= $this->percorso;

		$this->body .= $list_o->list_html ( $this->session_vars );
		if ($list_o->list['LEGEND']!= 'no'){
			$legend = new legend ( $this->config_service );
			$this->body .= $legend->html_legend_lista;
			//print_r($list_o);
		}
		
	} */

	function DocumentazionePratica(){
		if (isset($_GET[$this->xmr->pk_service])){
			$this->body.=$this->tb_riassuntiva();
			$id_area=200000+$this->pk_service;
			$this->body.="<iframe src=\"WCA/index.php?tab=3&id_area=$id_area\" style=\"width:100%;border:none;height:400px\"></iframe>";
			return; 
		}else{
			$this->body.="<iframe src=\"WCA/index.php\" style=\"width:100%;border:none;height:400px\"></iframe>";
			return; 
		}
		
	}

	//GESTIONE CALENDARIO - INIZIO
	
	function ShowCalendar($m,$y)
	{	
	  if ((!isset($_GET['d']))||($_GET['d'] == ""))
	  {
	    $m = $m;
	    $y = $y;
	
	  }else{
	    $m = (int)@strftime( "%m" ,(int)$_GET['d']);
	    $y = (int)@strftime( "%Y" ,(int)$_GET['d']);
	    $m = $m;
	    $y = $y;
	  }
	
	  $precedente = @mktime(0, 0, 0, $m -1, 1, $y);
	  $successivo = @mktime(0, 0, 0, $m +1, 1, $y);
	
	  $nomi_mesi = array(
	    "Gennaio",
	    "Febbraio",
	    "Marzo",
	    "Aprile",
	    "Maggio",
	    "Giugno", 
	    "Luglio",
	    "Agosto",
	    "Settembre",
	    "Ottobre",
	    "Novembre",
	    "Dicembre"
	  );
	
	  $nomi_giorni = array(
	    "Lun",
	    "Mar",
	    "Mer",
	    "Gio",
	    "Ven",
	    "Sab",
	    "Dom"
	  );
	
	  $cols = 7;
	  $days = @date("t",@mktime(0, 0, 0, $m, 1, $y)); 
	  $lunedi= @date("w",@mktime(0, 0, 0, $m, 1, $y));
	  if($lunedi==0) $lunedi = 7;
	
	  
	  
	  $temp.= "<table align=\"center\" >\n
	  <tr><td colspan=\"$cols\"><b>Calendario delle sedute del Comitato Etico</b><br><br></td></tr>
	  <tr>\n
	  <td align='center' style='background-color:#CEDBEF' colspan=\"".$cols."\">
	  <a href=\"?CalSed&d=".$precedente . "\">prec. &lt;&lt; </a>
	  <b>" . $nomi_mesi[$m-1] . " " . $y . "</b> 
	  <a href=\"?CalSed&d=" . $successivo . "\">&gt;&gt; succ.</a></td></tr>";
	  
	  $temp.= "<tr><td colspan='$cols'>
	  <table style='background-color:#EFF3F7; width:100%; border-collapse:collapse; border:solid 1px;'>
	  <tr>
	  ";
	  foreach($nomi_giorni as $v)
	  {
	    $temp.= "<td><b>".$v."</b></td>\n";
	  }
	  $temp.= "</tr>";
	  
	  for($j = 1; $j<$days+$lunedi; $j++)
	  {
	    if($j%$cols+1==0)
	    {
	      $temp.= "<tr style='background-color:#CEDBEF'>\n";
	    }
	
	    if($j<$lunedi)
	    {
	      $temp.= "<td> </td>\n";
	    }else{
	      $day= $j-($lunedi-1);
	      $data = @strtotime(@date($y."-".$m."-".$day));
	      $oggi = @strtotime(@date("Y-m-d"));
	  
	     $sql_query="SELECT riunione_dt,inizio_acc_dt,fine_acc_dt FROM riunioni_ce";
	      $sql = new query ( $this->conn );
	      $sql-> exec ( $sql_query );
	      while ( $sql->get_row () ) {
	    	$riunione_dt=$sql->row ['RIUNIONE_DT'];
	    	$inizio_acc_dt=$sql->row ['INIZIO_ACC_DT'];
	    	$fine_acc_dt=$sql->row ['FINE_ACC_DT'];
	    	if ($riunione_dt == $data)
	          {
	            $day = "<a style='background-color:#FF6900; color:white;' href=\"index.php?VisCal&day=$riunione_dt\">$day</a>";
	          }
	         /* Codice per evidenziare solo le date di inizio e fine accettazione
	        if ($inizio_acc_dt == $data)
	          {
	            $day = "<a style='background-color:#F7D742;'\">$day</a>";
	          }
	        if ($fine_acc_dt == $data)
	          {
	            $day = "<a style='background-color:#F7D742;'\">$day</a>";
	          }
	          */
	         if (($data <= $fine_acc_dt) and ($data >= $inizio_acc_dt))
	          {
	            $day = "<a style='background-color:#F7D742;'\">$day</a>";
	          }  	
	      }
	     
	      if($data != $oggi)
	      {
	        $temp.= "<td>".$day."</td>";
	      }else{
	        $temp.= "<td style='font-size:10px'><font color=#088F00><b>".$day."</b></font></td>";
	      }
	    }
	
	    if($j%$cols==0)
	    {
	      $temp.= "</tr>";
	    }
	  }
	  $temp.= "<tr></tr>";
	  $temp.= "</table>";
	  $temp.= "</td></tr></table>";
	  $temp.= "
	  <table align=\"center\">
	  <tr><br>
	  <td colspan=2 align=left><b>Legenda:</b></td>
	  </tr>
	  <tr>
	  <td style='background-color:#088F00'>&nbsp;&nbsp;&nbsp;</td>
	  <td>Data odierna</td>
	  </tr>
	  <tr>
	  <td style='background-color:#FF6900'>&nbsp;&nbsp;&nbsp;</td>
	  <td>Seduta del Comitato Etico</td>
	  </tr>
	  <tr>
	  <td style='background-color:#F7D742'>&nbsp;&nbsp;&nbsp;</td>
	  <td>Accettazione sperimentazioni</td>
	  </tr>
	  <tr><td align=center colspan=2><br>
	  <!--a href=\"index.php?InsSed\">Inserisci nuova seduta del Comitato Etico</a-->
	  <input type='button' value='Inserisci nuova seduta' onclick='location.href=\"index.php?InsSed\"'>
	  <br><br>
	  </td></tr>
	  <tr><td align=center colspan=2>
	  <!--a href=\"index.php?VisCal\">Visualizza tutte le sedute del Comitato Etico</a-->
	  <input type='button' value='Visualizza tutte le sedute' onclick='location.href=\"index.php?VisCal\"'>
	  <br><br>
	  </td></tr>
	  </table>";
	  
	  $this->body.=$temp;
	}
	
	function ins_riunione(){
	
	if (isset($_POST['submit']) && $_POST['submit']=="salva")
	{   
		//echo "riunione_dt".$riunione_dt;
	  $riunione_dt = @strtotime($_POST['riunione_dt']);
	  $inizio_acc_dt = @strtotime($_POST['inizio_acc_dt']);
	  $fine_acc_dt = @strtotime($_POST['fine_acc_dt']);
	  $note = @addslashes($_POST['note']);
	  
	  $sql_insert = "insert into riunioni_ce (id,riunione_dt,inizio_acc_dt,fine_acc_dt,note) VALUES (id_riunioni_ce.nextval,'$riunione_dt','$inizio_acc_dt','$fine_acc_dt','$note')";
	  $sql = new query ( $this->conn );
	  $sql->set_sql ( $sql_insert );
	  $sql->ins_upd ();
	  $this->conn->commit();
	  header("Location:index.php?VisCal&day=$riunione_dt");
	  
	}else {
	$body_riunione="
	<form action=\"{$_SERVER['PHP_SELF']}\" method=\"post\">
	<table align=\"center\">
	<tr>
	<td>
	<!--Titolo:<br>
	<input name=\"titolo\" type=\"text\"><br><br>-->
	Data seduta Comitato Etico:<br>
	<FONT size=5px height=20px>
	<input name=\"riunione_dt\" type=\"text\" value=\"\" readOnly style=\"font-size:15 height: 20;\">
	</FONT>
	";
	
	$data_var="riunione_dt";
	$body_riunione.='
	   <script>
			 var '.$data_var.'_cal=new CalendarPopup(\''.$data_var.'_cal_div\');
			 '.$data_var.'_cal.showNavigationDropdowns();
			 '.$data_var.'_cal.setReturnFunction("setMultipleValues_'.$data_var.'");
			 function setMultipleValues_'.$data_var.' (y,m,d) {
			 if(m<10 && m>0){m="0"+m;}
			 if(d<10 && d>0){d="0"+d;}
			     document.forms[0].'.$data_var.'.value=d+\'-\'+m+\'-\'+y;
	    	 }
	    	 document.write(\'<a href="#" name="'.$data_var.'_cal_anchor" id="'.$data_var.'_cal_anchor" onclick="'.$data_var.'_cal.showCalendar(\\\''.$data_var.'_cal_anchor\\\');return false;" >&nbsp;<img width="30"  style="vertical-align:bottom;" height="30" src="/images/calendar_icon.gif"></a><span id="'.$data_var.'_cal_div" STYLE="position:absolute;visibility:hidden;background-color:white;layer-background-color:white;"></span>\');
	    	 </script>';
	
	$body_riunione.="
	<br>
	<br>
	<br>
	Data inizio accettazione sperimentazioni:<br>
	<FONT size=5px height=20px>
	<input name=\"inizio_acc_dt\" type=\"text\" value=\"\" readOnly>
	</FONT>
	";
	$data_var="inizio_acc_dt";
	$body_riunione.='
	   <script>
			 var '.$data_var.'_cal=new CalendarPopup(\''.$data_var.'_cal_div\');
			 '.$data_var.'_cal.showNavigationDropdowns();
			 '.$data_var.'_cal.setReturnFunction("setMultipleValues_'.$data_var.'");
			 function setMultipleValues_'.$data_var.' (y,m,d) {
			 if(m<10 && m>0){m="0"+m;}
			 if(d<10 && d>0){d="0"+d;}
			     document.forms[0].'.$data_var.'.value=d+\'-\'+m+\'-\'+y;
	    	 }
	    	 document.write(\'<a href="#" name="'.$data_var.'_cal_anchor" id="'.$data_var.'_cal_anchor" onclick="'.$data_var.'_cal.showCalendar(\\\''.$data_var.'_cal_anchor\\\');return false;" >&nbsp;<img width="30"  style="vertical-align:bottom;" height="30" src="/images/calendar_icon.gif"></a><span id="'.$data_var.'_cal_div" STYLE="position:absolute;visibility:hidden;background-color:white;layer-background-color:white;"></span>\');
	    	 </script>';
	
	$body_riunione.="
	<br><br><br>
	Data fine accettazione sperimentazioni:<br>
	<FONT size=5px height=20px>
	<input name=\"fine_acc_dt\" type=\"text\" value=\"\" readOnly>
	</FONT>
	";
	
	$data_var="fine_acc_dt";
	$body_riunione.='
	   <script>
			 var '.$data_var.'_cal=new CalendarPopup(\''.$data_var.'_cal_div\');
			 '.$data_var.'_cal.showNavigationDropdowns();
			 '.$data_var.'_cal.setReturnFunction("setMultipleValues_'.$data_var.'");
			 function setMultipleValues_'.$data_var.' (y,m,d) {
			 if(m<10 && m>0){m="0"+m;}
			 if(d<10 && d>0){d="0"+d;}
			     document.forms[0].'.$data_var.'.value=d+\'-\'+m+\'-\'+y;
	    	 }
	    	 document.write(\'<a href="#" name="'.$data_var.'_cal_anchor" id="'.$data_var.'_cal_anchor" onclick="'.$data_var.'_cal.showCalendar(\\\''.$data_var.'_cal_anchor\\\');return false;" >&nbsp;<img width="30"  style="vertical-align:bottom;" height="30" src="/images/calendar_icon.gif"></a><span id="'.$data_var.'_cal_div" STYLE="position:absolute;visibility:hidden;background-color:white;layer-background-color:white;"></span>\');
	    	 </script>';
	
	$body_riunione.="
	<br><br>
	Note:<br>
	<textarea name=\"note\" cols=\"30\" rows=\"3\"></textarea><br>
	</td>
	</tr>
	<tr><td align=center>
	<input name=\"submit\" type=\"submit\" value=\"salva\">
	</tr></td>
	</table>
	</form>
	";
	
	
	$this->script.='<script type="text/javascript" src="libs/js_tooltip/calendar.js"></script>
	    <script type="text/javascript" src="libs/js_tooltip/calendar_en.js"></script>
	    <link  href="libs/js_tooltip/calendar.css" rel="stylesheet" type="text/css" />';
	
	$this->body.=$body_riunione;
	}
	
	
	}
	
	function mod_riunione(){
		
	if(@isset($_POST['mod_id'])&&(@is_numeric($_POST['mod_id'])))
	{
	  $id = $_POST['mod_id'];
	  $riunione_dt = @strtotime($_POST['riunione_dt']);
	  $inizio_acc_dt = @strtotime($_POST['inizio_acc_dt']);
	  $fine_acc_dt = @strtotime($_POST['fine_acc_dt']);
	  $note = @addslashes($_POST['note']);
	
	  $sql_update = "UPDATE riunioni_ce SET riunione_dt='$riunione_dt', inizio_acc_dt='$inizio_acc_dt', fine_acc_dt='$fine_acc_dt', note='$note' WHERE id = $id";
	  $sql = new query ( $this->conn );
	  $sql->set_sql ( $sql_update );
	  $sql->ins_upd ();
	  $this->conn->commit();
	  header("Location:index.php?VisCal&id=$id");
	}
	elseif (@isset($_GET['id']) && @is_numeric($_GET['id']))
	{
	  $id = $_GET['id'];
	  $query = "SELECT riunione_dt,inizio_acc_dt,fine_acc_dt,note FROM riunioni_ce WHERE id = $id";
	  $sql = new query ( $this->conn );
	      $sql-> exec ( $query );
	      $sql-> get_row ();
	      
	      	$riunione_dt=@date("d-m-Y",$sql->row ['RIUNIONE_DT']);
	      	$inizio_acc_dt=@date("d-m-Y",$sql->row ['INIZIO_ACC_DT']);
	      	$fine_acc_dt=@date("d-m-Y",$sql->row ['FINE_ACC_DT']);
	      	$note=$sql->row ['NOTE'];
	
	$body_riunione_mod="
	<form action=\"{$_SERVER['PHP_SELF']}\" method=\"post\">
	<table align=\"center\">
	<tr>
	<td>
	<!--Titolo:<br>
	<input name=\"titolo\" type=\"text\"><br><br>-->
	Data seduta Comitato Etico:<br>
	<input name=\"riunione_dt\" type=\"text\" value=\"$riunione_dt\"><br>
	<br>
	Accettazione documentazione sperimentazioni: <br>
	<br>
	Data inizio:<br>
	<input name=\"inizio_acc_dt\" type=\"text\" value=\"$inizio_acc_dt\"><br>
	Data fine:<br>
	<input name=\"fine_acc_dt\" type=\"text\" value=\"$fine_acc_dt\"><br><br>
	Note:<br>
	<textarea name=\"note\" cols=\"30\" rows=\"3\">$note</textarea><br>
	<br><input name=\"mod_id\" type=\"hidden\" value=\"$id\">
	<input name=\"submit\" type=\"submit\" value=\"modifica\">
	</td>
	</tr>
	</table>
	</form>
	";
	$this->body.=$body_riunione_mod;
	}	
	}
	
	function canc_riunione(){
		
	if (@isset($_GET['id']) && @is_numeric($_GET['id']))
	{
	  $del_id = $_GET['id'];
	  $query = "SELECT riunione_dt,inizio_acc_dt,fine_acc_dt,note FROM riunioni_ce WHERE id ='$del_id'";
	  $sql = new query ( $this->conn );
	  $sql-> exec ( $query );
	  $sql-> get_row ();
	  $riunione_dt=@date("d-m-Y",$sql->row ['RIUNIONE_DT']);
	  $inizio_acc_dt=@date("d-m-Y",$sql->row ['INIZIO_ACC_DT']);
	  $fine_acc_dt=@date("d-m-Y",$sql->row ['FINE_ACC_DT']);
	  $note=$sql->row ['NOTE'];
	
	$body_riunione_elimina="
	<form method=\"post\" action=\"{$_SERVER['PHP_SELF']}\">
	<table align=\"center\">
	<tr>
	<td>
	<h1>Attenzione!</h1>
	Si sta per eliminare la seguente seduta:<br>
	<b>$riunione_dt</b> ($note)<br><br>
	Confermare per eseguire l'operazione.<br>
	<br>
	<input name=\"del_id\" type=\"hidden\" value=\"$del_id\">
	<input name=\"submit\" type=\"submit\" value=\"Cancella\">
	</tr>
	</td>
	</table>
	</form>
	";
	$this->body.=$body_riunione_elimina;
	
	
	if(isset($_POST['del_id']) && is_numeric($_POST['del_id']))
	  {
	    $del_id2 = $_POST['del_id'];
	    $sql_del="DELETE FROM riunioni_ce WHERE id = '$del_id2'";
	    $sql = new query ( $this->conn );
	    $sql->set_sql ( $sql_del );
	    $sql->ins_upd ();
	    $this->conn->commit();
	    header("Location:index.php?VisCal");
	
	}
	
	}
	}
	
	function vis_riunione() {
	
	$filtro='';
	$seduta='';
	
	if(@isset($_GET['day']) && @is_numeric($_GET['day'])) {
	  $day = $_GET['day'];
	  $filtro="WHERE riunione_dt=$day";
	}
	
	if(@isset($_GET['id']) && @is_numeric($_GET['id'])) {
	  $id = $_GET['id'];
	  $filtro="WHERE id=$id";
	}
	
	  $header_seduta="<table align=\"center\"><tr><td>
	  <table align=\"center\"><tr><td><br>
	  <font size=2><b> Lista delle sedute del Comitato Etico</b></font><br>
	  </td></tr></table>
	  <ol>";
	  
	  $sql_query="SELECT * FROM riunioni_ce $filtro";
	      $sql = new query ( $this->conn );
	      $sql-> exec ( $sql_query );
	      while ( $sql->get_row () ) {
	      	$id=$sql->row ['ID'];
	      	$riunione_dt=@date("d-m-Y",$sql->row ['RIUNIONE_DT']);
	      	$inizio_acc_dt=@date("d-m-Y",$sql->row ['INIZIO_ACC_DT']);
	      	$fine_acc_dt=@date("d-m-Y",$sql->row ['FINE_ACC_DT']);
	      	$note=$sql->row ['NOTE'];
	
	      $seduta_utile.="
	      <li>
	      Seduta del: <b>$riunione_dt</b><br> 
	      Inizio accettazione documentazione: <b>$inizio_acc_dt</b> <br> 
	      Fine accettazione documentazione: <b>$fine_acc_dt</b> <br>
	      Note: $note <br><br>
	      <a href=\"index.php?CanSed&id=$id\">Cancella</a> |
	      <a href=\"index.php?ModSed&id=$id\">Modifica</a></li><hr><br><br>
	      ";
	      }
	      
	      $footer_seduta="
	      <!--a href=\"index.php?InsSed\">Inserisci altra seduta</<a> - 
	      <a href=\"index.php?CalSed\">Torna al calendario</a-->
	      <input type='button' value='Inserisci nuova seduta' onclick='location.href=\"index.php?InsSed\"'>
	      <input type='button' value='Torna al calendario' onclick='location.href=\"index.php?CalSed\"'>
	      </ol>
	      </td></tr></table>
	      <hr>";
	      
	      $seduta=$header_seduta;
	      $seduta.=$seduta_utile;
	      $seduta.=$footer_seduta;
	      
	      $this->body.=$seduta;
	
	}
	
	//GESTIONE CALENDARIO - FINE	

	/*
	//Stringhe testuali
	function testo($testo){
		//$txt = parent::testo($testo);
		$this->testi['Home']="Home";
		$this->testi['Vista Paziente']="Dettaglio studio";

		return parent::testo($testo);;
	}
	*/

	/*
	//Gestione lista esami - custom
	function ExamsLists($percorso_base = null) {
		$this->patient_table = "";

		//Nuovo modo di generare il menu briciola di pane
		$this->percorso = $this->breadcrumb ( "exam_list" );
		$body .= $this->percorso;

		$exams = $this->visit_structure_xml;
		global $xml_forms_not_valid;
		$this->make_patient_table ();
		$body .= $this->patient_table;
		$body .= "<br><br>" . $this->tb_riassuntiva ();
		//if (isset ( $this->workflow ) && (! isset ( $this->show_gantt ) || $this->show_gantt))
		//$body .= "
		//	<p align=center>
		//		<a href=\"#\" onclick=\"show_hide('img_rep');return false;\">Mostra/nascondi diagramma temporale</a><br>
		//		<img style=\"display:none\" id='img_rep' src=\"gantt.php?WF_ID={$this->workflow->id}&PK_SERVICE={$this->pk_service}\">
		//	</p>";
		//else
		$body .= "<br><br>";

		if ($this->xmr->depth > 0 && $this->session_vars ['VISITNUM'] == '' && $this->mostra_ana_comune) {
			//	$dir= str_replace("/".$this->service,"",$this->xml_dir);
			$xmr = new xmrwf ( "study.xml", $conn );
			$xmr->setConfigParam ( true );
			$config = $xmr->getConfigService ();
			//	$vlist_2 = new xml_esams_list ( $dir . '/' . $exams,$config,$this->session_vars, $this->conn);
			$body .= str_replace ( "index.php", "../index.php", $this->vlist_root->esams_list_html ( $config ['service'] ) );
			$body .= "<table width='95%' align=center><tr><td>";
		}

		$vlist = new xml_esams_list ( $this->xml_dir . '/' . $exams );
		$body .= $this->vlist->esams_list_html ();


		$ret = "";
		if ($this->config_service ['lang'] == "en") {
			$go = "Enter ";
			$data = " data";
		} else {
			$go = "Entra nei dati ";
			$data = "";
		}
		if (isset($this->xmr->substudies) && is_array($this->xmr->substudies)) foreach ( $this->xmr->substudies as $curr_study ) {
			$str = "select count(*) conto from {$curr_study->configurations['PREFIX']}_coordinate where  {$curr_study->configurations['PK_SERVICE']}='{$this->pk_service}'";
			$sql = new query ( $this->conn );
			$sql->get_row ( $str );
			$link = $curr_study->configurations ['PREFIX'] . "/" . $this->hrefs ['Vista Paziente'];
			if ($sql->row ['CONTO'] > 0)
			$ret .= "<p align=\"left\">$go<a href=\"$link\">" . $curr_study->workflow ['DESCR'] . "$data&nbsp;&gt;&gt;</a></p>";
		}
		if($this->xmr->depth!='0'){
			$link = "../" . $this->hrefs ['Vista Paziente'];
			$ret .= "<p align=\"left\">$go<a href=\"$link\">" . $this->xmr_root->workflow ['DESCR'] . "$data&nbsp;&gt;&gt;</a></p>";
		}
		$body .= $ret;
		if($this->xmr->depth > 0 && $this->session_vars ['VISITNUM'] == '' && $this->mostra_ana_comune) {
			$body.="</td></tr></table>";
		}
		$legend = new legend ( $this->config_service );
		if($this->session_vars['VISITNUM']!="" || $this->session_vars['GROUP']!="")
		$body.='<p align="right"><a href="index.php?exams=visite_exam.xml&'.$this->config_service['PK_SERVICE'].'='.$this->session_vars[$this->config_service['PK_SERVICE']].'&CENTER='.$this->session_vars['CENTER'].'">'.$this->testo("Lista completa").'</a></p>';

		$body .= $legend->html_legend_visita;
		if (isset ( $xml_forms_not_valid ) && is_array ( $xml_forms_not_valid ))
		foreach ( $xml_forms_not_valid as $key => $val ) {
			$forms_not_valid .= "<li>$val</li>";
		}
		if ($forms_not_valid != '') {
			$forms_not_valid = "<font color='red'><b>Attention: these forms can't be sent:</b></font><ul>$forms_not_valid</ul>Compile all mandatory fields";
		}
		$body = $forms_not_valid . $body;
		$body = $percorso . $body;
		$this->body = $body;
	}
	*/
	function ExamsLists($percorso_base = null) {
		parent::ExamsLists($percorso_base);
		//$this->body .= "<p>Appendo qui!</p>"; 
	}
	
	//Gestisce la generazione dell'Home Page
	function HomePage_old() {
		if (isset ( $this->workflow )) {
			$prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
			//die($prof_add);
			$xml_page = "home_{$prof_add}.xml";
		} else
			$xml_page = 'home.xml';
		$legend_upper = "";
		if (preg_match ( "/^MS/", $in ['remote_userid'] ) || preg_match ( "/^AIFA/", $in ['remote_userid'] ))
			$xml_page = 'home_ms.xml';
		if ($in ['USER_TIP'] == 'DM')
			$xml_page = 'home_dm.xml';
		if ($in ['USER_TIP'] == 'RO')
			$xml_page = 'home_ro.xml';
		$page = new xml_page ( $this->xml_dir . '/' . $xml_page );
		$body = '<div class="xmr_home_contenuto" >'.$page->page_html ()."</div>";
		//$body .= $this->footer;
		
		//Sostituzione campo [USERID]
		$body = str_replace("[USERID]",$this->user->userid,$body);
		
		
		//Da prototype
		//$body.="<!--$xml_page-->";
		//$this->xml_page=$xml_page;
		//$page = new xml_page ( $this->xml_dir . '/' . $xml_page, $this->admin_profili );
		//$body .= $page->page_html ();
		//$body .= $this->footer;
		//Fine prototype
		
		//Nuovo modo di generare il menu briciola di pane
		//$this->percorso = $this->breadcrumb ( "home" );
		$this->body .= $this->percorso;
	    
		/*
	    if (preg_match ( "/Unita_di_ricerca/", $prof_add )) {
	    $form = file_get_contents ( "menu_dx_URC.htm" );
	    }
	    elseif (preg_match ( "/Segreteria_CE/", $prof_add )) {
	    $form = file_get_contents ( "menu_dx_SGR.htm" );
	    }
	    elseif (preg_match ( "/Componente_CE/", $prof_add )) {
	    $form = file_get_contents ( "menu_dx_CMP.htm" );
	    }
	    elseif (preg_match ( "/Principal_Investigator/", $prof_add )) {
	    $form = file_get_contents ( "menu_dx_PRI.htm" );
	    }
		
	    $this->body .= str_replace("<!--body-->",$body,$form);
		*/
		$this->body .= $body;
		
		
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
	
	}
	
	//Gestisce la generazione dell'Home Page
	function HomePage() {
		/* if (isset ( $this->workflow )) {
			$prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
			//die($prof_add);
			$xml_page = "home_{$prof_add}.xml";
		} else
			$xml_page = 'home.xml';
		$legend_upper = "";
		if (preg_match ( "/^MS/", $in ['remote_userid'] ) || preg_match ( "/^AIFA/", $in ['remote_userid'] ))
			$xml_page = 'home_ms.xml';
		if ($in ['USER_TIP'] == 'DM')
			$xml_page = 'home_dm.xml';
		if ($in ['USER_TIP'] == 'RO')
			$xml_page = 'home_ro.xml';
		$page = new xml_page ( $this->xml_dir . '/' . $xml_page );
		$body = '<div class="xmr_home_contenuto" >'.$page->page_html ()."</div>";
		//$body .= $this->footer;
		
		//Sostituzione campo [USERID]
		$body = str_replace("[USERID]",$this->user->userid,$body); */
		
		
		//Da prototype
		//$body.="<!--$xml_page-->";
		//$this->xml_page=$xml_page;
		//$page = new xml_page ( $this->xml_dir . '/' . $xml_page, $this->admin_profili );
		//$body .= $page->page_html ();
		//$body .= $this->footer;
		//Fine prototype
		
		//Nuovo modo di generare il menu briciola di pane
		$this->percorso = $this->breadcrumb ( "home" );
		
		$prof_add = str_replace ( " ", "_", $this->session_vars ['WFact'] );
		//echo $prof_add;

			//$this->body .= $this->percorso;
			
			$sql=new query($this->conn);
			
			$this->body .= "
			<style>
			.select2-container {
			min-width:330px;
			}
			
			.infobox{
				width: 150px;
				height: 105px;
				text-align: center;
				cursor: pointer;
			}
			
			.infobox > .infobox-data {
				text-align: center;
				padding-left: 0px;
			}
			
			div#budget div{
			
			}
			</style>
			<br><br>";
			
		$bind['USERID']=$this->session_vars['remote_userid'];
		
		$datiUtente=$this->getDatiUtente2($this->user->userid);
		$id_ce=$datiUtente['ID_CE'];
		
		#GC 21/03/2016 Toscana-4# Nascondo gli studi pediatrici nelle liste in HP, tranne nella prima lista "Studi"
		#LUIGI TOSCANA-71 TOSCANA-57 nuovo sistema per migliorare le prestazioni, commento tutto
		//if($id_ce!=4) $filtro_ped="and pediatrico<>1";
		//if($id_ce==4) $filtro_ped1="or pediatrico=1";
		
		if ($prof_add=='Segreteria_CE'){
			$sql_query="SELECT
						COUNT(distinct R.ID_STUD) AS num_row
						FROM
						CE_TUTTI_STUDI R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$tuttiglistudi=$sql->row['NUM_ROW'];
		
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_COMPILAZIONE_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped
						$filtro_ped1";
			$sql->get_row($sql_query,$bind);
			$studicompilazione=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_ISTRUTTORIA_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped
						$filtro_ped1";
			$sql->get_row($sql_query,$bind);
			$studiverificare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_PARERE_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped
						$filtro_ped1";
			$sql->get_row($sql_query,$bind);
			$studivalutare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_SOSPESI_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped
						$filtro_ped1";
			$sql->get_row($sql_query,$bind);
			$studisospesi=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_APPROVATI_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped
						$filtro_ped1";
			$sql->get_row($sql_query,$bind);
			$studiapprovati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_NON_APPROVATI_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped";
			$sql->get_row($sql_query,$bind);
			$studinonapprovati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(R.ID_STUD) AS num_row
						FROM
						CE_STUDI_EME_VALUTAZIONE R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped";
			$sql->get_row($sql_query,$bind);
			$emendamentivalutare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_RITIRATI R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped";
			$sql->get_row($sql_query,$bind);
			$studiritirati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_CHIUSI_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID
						$filtro_ped
						$filtro_ped1";
			$sql->get_row($sql_query,$bind);
			$studichiusi=$sql->row['NUM_ROW'];
			
			
			$this->body .= "
			<div class=\"col-sm-12 infobox-container\">
			
			<div id=\"studi_ins\" class=\"infobox infobox-blue infobox-dark\" title=\"Lista di tutti gli studi inseriti in BD\" onclick=\"location.href='index.php?list=patients_list.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-folder-open\"></i>
				</div>
				
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$tuttiglistudi</span>
					<div class=\"infobox-content\">Studi</div>
				</div>
			</div>
			
			<div id=\"tutti_centri\" class=\"infobox infobox-pink\" title=\"Studi in corso di compilazione\" onclick=\"location.href='index.php?list=patients_list_compilazione.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-edit\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studicompilazione</span>
					<div class=\"infobox-content\">In compilazione</div>
				</div>
			</div>
			
			<div id=\"feasibility\" class=\"infobox infobox-green\" title=\"Studi con centri da verificare (istruttoria)\" onclick=\"location.href='index.php?list=patients_list_istruttoria.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-file-text\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiverificare</span>
					<div class=\"infobox-content\">In istruttoria</div>
				</div>
			</div>
			
			<div id=\"budget\" class=\"infobox infobox-orange\" title=\"Studi con centri da valutare (parere)\" onclick=\"location.href='index.php?list=patients_list_parere.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-group\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studivalutare</span>
					<div class=\"infobox-content\">In valutazione</div>
				</div>
			</div>
			
			<div id=\"contratto\" class=\"infobox infobox-red\" title=\"Studi con centri sospesi\" onclick=\"location.href='index.php?list=patients_list_sospesi.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-time\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studisospesi</span>
					<div class=\"infobox-content\">Sospesi</div>
				</div>
			</div>
			
			<div id=\"valutazione_ce\" class=\"infobox infobox-orange2\" title=\"Studi con centri approvati\" onclick=\"location.href='index.php?list=patients_list_approvati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-legal\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiapprovati</span>
					<div class=\"infobox-content\">Approvati</div>
				</div>
			</div>
			
			<div id=\"approvati_ce\" class=\"infobox infobox-brown\" title=\"Studi con centri non approvati\" onclick=\"location.href='index.php?list=patients_list_non_approvati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-ban-circle\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studinonapprovati</span>
					<div class=\"infobox-content\">Non approvati</div>
				</div>
			</div>
			
			<div id=\"studi_fatt\" class=\"infobox infobox-blue2\" title=\"Studi con emendamenti da valutare\" onclick=\"location.href='index.php?list=patients_list_eme_valutazione.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-eraser\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$emendamentivalutare</span>
					<div class=\"infobox-content\">In emendamento</div>
				</div>
			</div>
			
			<div id=\"studi_fatt\" class=\"infobox infobox-purple\" title=\"Studi ritirati\" onclick=\"location.href='index.php?list=patients_list_ritirati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon-lock\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiritirati</span>
					<div class=\"infobox-content\">Ritirati</div>
				</div>
			</div>
			
			<div id=\"studi_fatt\" class=\"infobox infobox-grey\" title=\"Studi con centri chiusi\" onclick=\"location.href='index.php?list=patients_list_chiusi.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon-check\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studichiusi</span>
					<div class=\"infobox-content\">Chiusi</div>
				</div>
			</div>
			</div>
			";
		}
		
		if ($prof_add=='Unita_di_ricerca'){			
			$sql_query="SELECT
						COUNT(distinct R.ID_STUD) AS num_row
						FROM
						CE_TUTTI_STUDI R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$tuttiglistudi=$sql->row['NUM_ROW'];
		
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_COMPILAZIONE_URC R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studicompilazione=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_ISTRUTTORIA_URC R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studiverificare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_PARERE_URC R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studivalutare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_SOSPESI_URC R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studisospesi=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_APPROVATI_URC R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studiapprovati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_NON_APPROVATI_URC R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studinonapprovati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(R.ID_STUD) AS num_row
						FROM
						CE_STUDI_EME_VALUTAZIONE R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$emendamentivalutare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_RITIRATI R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studiritirati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_CHIUSI_URC R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studichiusi=$sql->row['NUM_ROW'];
			
			
			$this->body .= "
			<div class=\"col-sm-12 infobox-container\">
			
			<div id=\"studi_ins\" class=\"infobox infobox-blue infobox-dark\" title=\"Lista di tutti gli studi inseriti in BD\" onclick=\"location.href='index.php?list=patients_list.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-folder-open\"></i>
				</div>
				
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$tuttiglistudi</span>
					<div class=\"infobox-content\">Studi</div>
				</div>
			</div>
			
			<div id=\"tutti_centri\" class=\"infobox infobox-pink\" title=\"Studi in corso di compilazione\" onclick=\"location.href='index.php?list=patients_list_compilazione.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-edit\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studicompilazione</span>
					<div class=\"infobox-content\">In compilazione</div>
				</div>
			</div>
			
			<div id=\"feasibility\" class=\"infobox infobox-green\" title=\"Studi con centri da verificare (istruttoria)\" onclick=\"location.href='index.php?list=patients_list_istruttoria.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-file-text\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiverificare</span>
					<div class=\"infobox-content\">In istruttoria</div>
				</div>
			</div>
			
			<div id=\"budget\" class=\"infobox infobox-orange\" title=\"Studi con centri da valutare (parere)\" onclick=\"location.href='index.php?list=patients_list_parere.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-group\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studivalutare</span>
					<div class=\"infobox-content\">In valutazione</div>
				</div>
			</div>
			
			<div id=\"contratto\" class=\"infobox infobox-red\" title=\"Studi con centri sospesi\" onclick=\"location.href='index.php?list=patients_list_sospesi.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-time\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studisospesi</span>
					<div class=\"infobox-content\">Sospesi</div>
				</div>
			</div>
			
			<div id=\"valutazione_ce\" class=\"infobox infobox-orange2\" title=\"Studi con centri approvati\" onclick=\"location.href='index.php?list=patients_list_approvati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-legal\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiapprovati</span>
					<div class=\"infobox-content\">Approvati</div>
				</div>
			</div>
			
			<div id=\"approvati_ce\" class=\"infobox infobox-brown\" title=\"Studi con centri non approvati\" onclick=\"location.href='index.php?list=patients_list_non_approvati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-ban-circle\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studinonapprovati</span>
					<div class=\"infobox-content\">Non approvati</div>
				</div>
			</div>
			
			<div id=\"studi_fatt\" class=\"infobox infobox-blue2\" title=\"Studi con emendamenti da valutare\" onclick=\"location.href='index.php?list=patients_list_eme_valutazione.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-eraser\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$emendamentivalutare</span>
					<div class=\"infobox-content\">In emendamento</div>
				</div>
			</div>
			
			<div id=\"studi_fatt\" class=\"infobox infobox-purple\" title=\"Studi ritirati\" onclick=\"location.href='index.php?list=patients_list_ritirati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon-lock\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiritirati</span>
					<div class=\"infobox-content\">Ritirati</div>
				</div>
			</div>
			<div id=\"studi_fatt\" class=\"infobox infobox-grey\" title=\"Studi con centri chiusi\" onclick=\"location.href='index.php?list=patients_list_chiusi.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon-check\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studichiusi</span>
					<div class=\"infobox-content\">Chiusi</div>
				</div>
			</div>
			</div>
			";
		}
		
		if ($prof_add=='Componente_CE'){
			$sql_query="SELECT
						COUNT(distinct R.ID_STUD) AS num_row
						FROM
						CE_TUTTI_STUDI R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$tuttiglistudi=$sql->row['NUM_ROW'];
			
			$this->body .= "
			<div class=\"col-sm-12 infobox-container\">
			
			<div id=\"studi_ins\" class=\"infobox infobox-blue infobox-dark\" title=\"Lista di tutti gli studi inseriti in BD\" onclick=\"location.href='index.php?list=patients_list.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-folder-open\"></i>
				</div>
				
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$tuttiglistudi</span>
					<div class=\"infobox-content\">Studi</div>
				</div>
			</div>
			
			</div>
			";
			
		}
		
		if ($prof_add=='Regione'){
			$sql_query="SELECT
						COUNT(distinct R.ID_STUD) AS num_row
						FROM
						CE_TUTTI_STUDI R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$tuttiglistudi=$sql->row['NUM_ROW'];
		
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_ISTRUTTORIA_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studiverificare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_PARERE_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studivalutare=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_SOSPESI_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studisospesi=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_APPROVATI_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studiapprovati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(DISTINCT R.ID_STUD) AS num_row
						FROM
						CE_STUDI_NON_APPROVATI_SGR R,
						ce_utenti_centri U
						WHERE
						R.USERID=:USERID
						AND r.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$studinonapprovati=$sql->row['NUM_ROW'];
			
			$sql_query="SELECT
						COUNT(R.ID_STUD) AS num_row
						FROM
						CE_STUDI_EME_VALUTAZIONE R,
						ce_utenti_centri U
						WHERE
						R.id_stud=U.CENTER
						and U.userid=:USERID";
			$sql->get_row($sql_query,$bind);
			$emendamentivalutare=$sql->row['NUM_ROW'];
			
			$this->body .= "
			<div class=\"col-sm-12 infobox-container\">
			
			<div id=\"studi_ins\" class=\"infobox infobox-blue infobox-dark\" title=\"Lista di tutti gli studi inseriti in BD\" onclick=\"location.href='index.php?list=patients_list.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-folder-open\"></i>
				</div>
				
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$tuttiglistudi</span>
					<div class=\"infobox-content\">Studi</div>
				</div>
			</div>
			
			<div id=\"feasibility\" class=\"infobox infobox-green\" title=\"Studi con centri da verificare (istruttoria)\" onclick=\"location.href='index.php?list=patients_list_istruttoria.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-file-text\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiverificare</span>
					<div class=\"infobox-content\">In istruttoria</div>
				</div>
			</div>
			
			<div id=\"budget\" class=\"infobox infobox-orange\" title=\"Studi con centri da valutare (parere)\" onclick=\"location.href='index.php?list=patients_list_parere.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-group\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studivalutare</span>
					<div class=\"infobox-content\">In valutazione</div>
				</div>
			</div>
			
			<div id=\"contratto\" class=\"infobox infobox-red\" title=\"Studi con centri sospesi\" onclick=\"location.href='index.php?list=patients_list_sospesi.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-time\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studisospesi</span>
					<div class=\"infobox-content\">Sospesi</div>
				</div>
			</div>
			
			<div id=\"valutazione_ce\" class=\"infobox infobox-orange2\" title=\"Studi con centri approvati\" onclick=\"location.href='index.php?list=patients_list_approvati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-legal\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studiapprovati</span>
					<div class=\"infobox-content\">Approvati</div>
				</div>
			</div>
			
			<div id=\"approvati_ce\" class=\"infobox infobox-brown\" title=\"Studi con centri non approvati\" onclick=\"location.href='index.php?list=patients_list_non_approvati.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-ban-circle\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$studinonapprovati</span>
					<div class=\"infobox-content\">Non approvati</div>
				</div>
			</div>
			
			<div id=\"studi_fatt\" class=\"infobox infobox-blue2\" title=\"Studi con emendamenti da valutare\" onclick=\"location.href='index.php?list=patients_list_eme_valutazione.xml&'\">
				<div class=\"infobox-icon\">
					<i class=\"ace-icon icon icon-eraser\"></i>
				</div>
		
				<div class=\"infobox-data\">
					<span class=\"infobox-data-number\">$emendamentivalutare</span>
					<div class=\"infobox-content\">In emendamento</div>
				</div>
			</div>
					
			</div>
			";
			
		}
	}

	////////// OVERLAY //////////
	function SpecchiettoAvanzamentoButton() {
		//ALERT: Occhio alla cartella!
		//Il parametro VIEW e' una vista sul db?
		$gestione_avanzamento.="
				<script type=\"text/javascript\" src=\"/uxmr/fusionChart/gantt_swf.php?get_js=yes&popup=yes&ID={$_GET[$this->xmr->pk_service]}&VIEW={$this->xmr->prefix}_fusion_view&TITOLO=Avanzamento\"></script>
			";
		
		return $gestione_avanzamento;
	}	
	
	function SpecchiettoGestionePraticheButton(){
		$gestione_avanzamento="<p style=\"margin:0 auto;text-align:center;\"><input type=\"button\" value=\"Storico Stati\"
		onclick=\"
		//show_hide('hided_div');show_hide_text('hided_div','hided_text');
		$.newWindow({id:'ajaxwindow3',title:'Storico Stati',content:document.getElementById('gestvalutaz').innerHTML,width: 600,height: 200,posx:200,posy:200});
		document.getElementById('ajaxwindow3').style.borderCollapse='collapse';
		\" /></p>";
		return $gestione_avanzamento;
	}

	function SpecchiettoGestionePratiche(){
		$gestione_avanzamento .= "<div id=\"gestvalutaz\" style=\"display:none;\">
		<table cellpadding=1 cellspacing=1 align=center
		class=\"specchiettoGenerale\">
		<tr>
				<th class=int width=\"150px\" style=\"border:1px solid #2B6285\">Data</th>
				<th class=int width=\"150px\" style=\"border:1px solid #2B6285\">Stato</th>
		</tr>
		";
		$sql_query="select to_char(INSERTDT,'DD-MM-YYYY') as INSERTDT from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}='{$this->pk_service}' and esam=0";
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		$sql->get_row();
		
		$gestione_avanzamento.="
			<tr id='gest_prat' style='display:;'>
				<td width=\"150px\" style=\"text-align:center;border:1px solid #2B6285\">{$sql->row['INSERTDT']}</td>
				<td width=\"150px\" style=\"text-align:center;border:1px solid #2B6285\">Inizio compilazione</td>
			</tr>";
		
		//Modificare questo decode sulla base del workflow
		$sql_query="select decode(ID_DEST,	1,'Iscrizione',
											2,'In compilazione',
											3,'Segreteria',
											4,'Approvato',
											5,' -- ',
											6,' -- ',
											7,' -- ') as stato,
							to_char(DT_CHANGE,'DD-MM-YYYY') as DT_CHANGE from {$this->xmr->prefix}WF_REP where pk_service='{$this->pk_service}' order by {$this->xmr->prefix}WF_REP.DT_CHANGE asc";
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			$gestione_avanzamento.="
			<tr id='gest_prat' style='display:;'>
				<td width=\"150px\" style=\"text-align:center;border:1px solid #2B6285\">{$sql->row['DT_CHANGE']}</td>
				<td width=\"150px\" style=\"text-align:center;border:1px solid #2B6285\">{$sql->row['STATO']}</td>
			</tr>";
		}


			$gestione_avanzamento.="
			<tr id='gest_prat' style='display:;'>
				<td width=\"150px\" style=\"text-align:center;border:1px solid #2B6285\">-</td>
				<td width=\"150px\" style=\"text-align:center;border:1px solid #2B6285\">-</td>
			</tr>";



		$gestione_avanzamento .= "</table></div>";

		return $gestione_avanzamento;
	}
	////////// FINE OVERLAY //////////
	
	
	////////// --- FINE MUTUATI DA OSSC --- ////////
	
	function reOpenVisit($vid, $allprogs = false){
		//Controllo visita aperta
		$sql=new query($this->conn);
		$sql_query="select * from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid"; // and esam=1";
		$sql->exec($sql_query);
		$esams = array();
		while ($sql->get_row()){
			$esams[] = $sql->row['ESAM'];
		}
		if ($vid == 0){
			//Tolgo esam 0 che e' registrazione.
			$sub = array();
			$sub[] = 0;
			$esams = array_diff($esams,$sub);
		}
		//print_r($open);
		//die();
		$maxvprogr = $this->getMaxVprogr($this->pk_service,$vid);
		$start = 0;
		if (!$allprogs){
			$start = $maxvprogr;
		}
		for ($i = 0; $i<=$maxvprogr;$i++){
			//Apertura esami
			foreach ($esams as $o){
				//$sql_close="update {$this->xmr->prefix}_coordinate set fine='0' where visitnum = $vid and visitnum_progr = $maxvprogr and progr = 1 and esam = $o and {$this->xmr->pk_service} = {$this->pk_service} ";
				$sql_close="update {$this->xmr->prefix}_coordinate set fine='0' where visitnum = $vid and visitnum_progr = $i and esam = $o and {$this->xmr->pk_service} = {$this->pk_service} ";
				$sql->set_sql($sql_close);
				$sql->ins_upd();
			}
		}
		//Apertura visita generale
		$sql_close="update {$this->xmr->prefix}_coordinate SET visitclose = 0 WHERE {$this->xmr->pk_service} = {$this->pk_service} and visitnum = $vid "; //and inizio=1";
		$sql->set_sql($sql_close);
		$sql->ins_upd();
	}
	function reOpenVisitProgr($vid, $vprogr){
		Logger::send('reOpenVisitProgr');
		//Controllo visita aperta
		$sql=new query($this->conn);
		$sql_query="select * from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid and visitnum_progr=$vprogr"; // and esam=1";
		$sql->exec($sql_query);
		$esams = array();
		while ($sql->get_row()){
			$esams[] = $sql->row['ESAM'];
		}
//		if ($vid == 0){
//			//Tolgo esam 0 che e' registrazione.
//			$sub = array();
//			$sub[] = 0;
//			$esams = array_diff($esams,$sub);
//		}
		//print_r($open);
		//die();
		//$maxvprogr = $this->getMaxVprogr($this->pk_service,$vid);
		//$start = 0;
//		if (!$allprogs){
//			$start = $maxvprogr;
//		}
//		for ($i = 0; $i<=$maxvprogr;$i++){
//			//Apertura esami
//			foreach ($esams as $o){
				//$sql_close="update {$this->xmr->prefix}_coordinate set fine='0' where visitnum = $vid and visitnum_progr = $maxvprogr and progr = 1 and esam = $o and {$this->xmr->pk_service} = {$this->pk_service} ";
				$sql_close="update {$this->xmr->prefix}_coordinate set fine='0' where {$this->xmr->pk_service} = {$this->pk_service} and visitnum = $vid and visitnum_progr = $vprogr ";
				$sql->set_sql($sql_close);
				$sql->ins_upd();
//			}
//		}
			
		//Apertura visita generale
		$sql_close="update {$this->xmr->prefix}_coordinate SET visitclose = 0 where {$this->xmr->pk_service} = {$this->pk_service} and visitnum = $vid and visitnum_progr = $vprogr "; //and inizio=1";
		$sql->set_sql($sql_close);
		$sql->ins_upd();
	}
	function openVisit($vid,$open, $newvprogr = false){
		//Apertura visita (id, array esami da aprire)
		$sql=new query($this->conn);
		$sql_query="select * from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid"; // and esam=1";
		$sql->exec($sql_query);
		$esams = array();
		while ($sql->get_row()){
			$esams[] = $sql->row['ESAM'];
		}
		$open = array_diff($open, $esams);
		//print_r($open);
		//die();
		$vprogr = 0;
		if ($newvprogr){
			$vprogr = $newvprogr;
		}
		foreach ($open as $o){
			$sql_close="insert into {$this->xmr->prefix}_coordinate(visitnum,visitnum_progr,progr,esam,{$this->xmr->pk_service},abilitato) values ($vid,$vprogr,1,$o,{$this->pk_service},1) ";
			$sql->set_sql($sql_close);
			$sql->ins_upd();
		}
		$this->reOpenVisit($vid);

	}
	function openEsamProgr($pkid,$vid,$vprogr,$esam,$progr,$insert = true, $writeuser=true){
		//Apertura visita (id, array esami da aprire)
		//print_r($this);
		if($this->session_vars['DEBUG']==1) echo "<br>openEsamProgr($pkid,$vid,$vprogr,$esam,$progr,$insert = true, $writeuser=true)<br>";
		$userid = "";
		if ($writeuser){
			$userid = $this->session_vars['remote_userid'];
		}
		//die($userid);
		$inizio = 0;
		if (!$insert){
			$inizio = "NULL";
		}
		$sql=new query($this->conn);
		$sql_check="select * from {$this->service}_coordinate where {$this->xmr->pk_service} = '{$pkid}' AND VISITNUM = '{$vid}' AND VISITNUM_PROGR = '{$vprogr}' AND ESAM = '{$esam}' AND PROGR = '{$progr}' ";
		//echo "$sql_check";
		$sql->set_sql($sql_check);
		$sql->exec ();
		$sql->get_row ();
		//die($insert);
		if($sql->numrows==0){
			if($this->session_vars['DEBUG']==1) echo "<br>prima dell'insert in ce_coordinate<br>";
			$sql=new query($this->conn);
			$sql_close="insert into {$this->service}_coordinate(USERID,{$this->xmr->pk_service},ABILITATO,VISITCLOSE, VISITNUM,VISITNUM_PROGR,ESAM,PROGR, INIZIO,INSERTDT,MODDT) ";
			$sql_close.=" VALUES ('$userid',{$pkid},1,0,{$vid},{$vprogr},{$esam},{$progr}, {$inizio}, SYSDATE, SYSDATE) "; //INIZIO = 1?
			//die($sql_close);
			$sql->set_sql($sql_close);
			//echo("$sql_close<br/>");
			$sql->ins_upd();
		}else{
			$insert = false;
		}
		//Inserisci riga in tabella
		$xml = $this->es_form[$vid][$esam];
		if ($xml){
			$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
			$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
			$ftab = $xml_form->form['TABLE'];
			//Check esistenza tabella, se esiste inserisco altrimenti non faccio nulla (aspetto la updatedb)
			$query_check_existence = "select table_name from user_tables where table_name=upper('{$ftab}')";
			$query = new query ( $this->conn );
			$query->set_sql ( $query_check_existence );
			$query->exec ();
			$query->get_row ();
			//die($insert);
			if($query->numrows!=0 && $insert){
				$sql_tb="insert into $ftab(USERID_INS,{$this->xmr->pk_service}, VISITNUM,VISITNUM_PROGR,ESAM,PROGR) "; //GUID?
				$sql_tb.=" VALUES ('$userid',{$pkid},{$vid},{$vprogr},{$esam},{$progr}) ";
				$sql->set_sql($sql_tb);
				$sql->ins_upd();
				//die($sql_tb);
			}
		}		
	}
	function updateEsamProgr($pkid,$vid,$vprogr,$esam,$progr,$fields){
		$sql=new query($this->conn);
		//lancia query di update su determinati campi per forzarne il valore
		$xml = $this->es_form[$vid][$esam];
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
		$ftab = $xml_form->form['TABLE'];
		if (count($fields)>0){
			$sql_tb="update $ftab SET ";
			$i = 0;
			foreach ($fields as $k=>$v){
				if ($i>0){
					$sql_tb.=",";
				}
				switch ($v){
					case "SYSDATE":
						$sql_tb.="$k = $v";
						break;
					default:
						//$sql_tb.="$k = '$v'";
						#GC 17/06/2013# Binding
						$bind[$k]=$v;
						//echo "<li>".$bind[$k]."</li>";
						$sql_tb.="$k = :$k";
						break;
				}
				$i++;
			}
			$sql_tb.=" WHERE {$this->xmr->pk_service} = {$pkid} AND VISITNUM = {$vid} AND VISITNUM_PROGR = {$vprogr} AND ESAM = {$esam} AND PROGR = {$progr} "; //GUID?
			//$sql->set_sql($sql_tb);
			#GC 17/06/2013# Binding
			$sql->ins_upd($sql_tb,$bind);
		}
	}
	function loadEsamProgr($pkid,$vid,$vprogr,$esam,$progr){
		Logger::send('loadEsamProgr('.$pkid.','.$vid.','.$vprogr.','.$esam.','.$progr.')');
		$sql=new query($this->conn);
		//Caricamento xml
		$xml = $this->es_form[$vid][$esam];
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
		$ftab = $xml_form->form['TABLE'];
		
		$sql_q="select * from {$ftab} ";
		$sql_q.=" WHERE {$this->xmr->pk_service} = {$pkid} AND VISITNUM = {$vid} AND VISITNUM_PROGR = {$vprogr} AND ESAM = {$esam} AND PROGR = {$progr} "; //GUID?
		$sql->get_row ( $sql_q );
		//$this->center = $sql->row ['CENTER'];
		if($this->session_vars['DEBUG']==1) echo "<br>$sql_q<br>";
		Logger::send($sql_q);
		return $sql->row;		
	}
	function getEsamProgs($pkid,$vid,$vprogr,$esam){
		$sql=new query($this->conn);
		//Caricamento xml
		$sql_query="select * from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid and visitnum_progr=$vprogr and esam=$esam"; // and esam=1";
		$sql->exec($sql_query);
		$progs = array();
		while ($sql->get_row()){
			$progs[] = $sql->row['PROGR'];
		}	
		return $progs;	
	}
	function getMaxProgr($pkid,$vid,$vprogr,$esam){
		if($this->session_vars['DEBUG']==1) echo "getMaxProgr($pkid,$vid,$vprogr,$esam) <br/>";
		$retval = 0;
		$sql=new query($this->conn);
		//Caricamento xml
		$sql_query="select max(PROGR) as MAXP from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid and visitnum_progr=$vprogr and esam=$esam"; // and esam=1";
		$sql->exec($sql_query);
		$progs = array();
		if($this->session_vars['DEBUG']==1) echo $sql_query."<br/>";
		if ($sql->get_row()){
			//echo "MAXVPROGR: {$sql->row['MAXVP']}";
			if (is_numeric($sql->row['MAXP'])){
				$retval = $sql->row['MAXP'];
			}
			//echo $retval."<br/>";
		}	
		//echo $retval."<br/>";
		return $retval;	
	}
	function getMaxVprogr($pkid,$vid){
		if($this->session_vars['DEBUG']==1) echo "getMaxVprogr($pkid,$vid) <br/>";
		$retval = -1;
		$sql=new query($this->conn);
		//Caricamento xml
		$sql_query="select max(VISITNUM_PROGR) as MAXVP, count(*) as COUNT from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid "; // and esam=1";
		if($this->session_vars['DEBUG']==1){
		//echo $sql_query."<br/>";
		Logger::send("getMaxVprogr=".$sql_query);
		}
		$sql->exec($sql_query);
		//$progs = array();
		//echo $sql_query."<br/>";
		if ($sql->get_row()){
			//echo "MAXVPROGR: {$sql->row['MAXVP']}";
			if (is_numeric($sql->row['MAXVP'])){
				$retval = $sql->row['MAXVP'];
			}
			//echo $retval."<br/>";
		}	
		if($this->session_vars['DEBUG']==1) echo $retval."<br/>";
		Logger::send("retval=".$retval);
		return $retval;	
		
	}
	
	function cloneVisit($pkid,$vid,$counterField){
		$sql=new query($this->conn);
		//Recupero max visitnum progr
		$sql_q="select max(visitnum_progr) as MAXVP from {$this->service}_COORDINATE WHERE {$this->xmr->pk_service} = {$pkid} AND VISITNUM = {$vid} ";
		$sql->get_row ( $sql_q );
		$src_vprogr = $sql->row['MAXVP'];
		$vprogr = $src_vprogr+1;
		//die("VP: $vprogr");
		//caricamento esami compilati da coordinate (della visita)
		$sql_q="select * from {$this->service}_COORDINATE WHERE {$this->xmr->pk_service} = {$pkid} AND VISITNUM = {$vid} ";
		$sql->exec($sql_q);
		$esams = array();
		while ($sql->get_row()){
			$esams[] = $sql->row['ESAM'];
		}
		//print_r($esams);
		//////$this->openVisit($vid,$esams,$vprogr);
		//Caricamento xml e clonazione con il nuovo vprogr
		foreach ($esams as $esam){
			//echo "<br/>ESAM: $esam";
			$xml = $this->es_form[$vid][$esam];
			$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
			$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
			$ftab = $xml_form->form['TABLE'];
			
			$sql_q="select * from {$ftab} ";
			$sql_q.=" WHERE {$this->xmr->pk_service} = {$pkid} AND VISITNUM = {$vid} AND VISITNUM_PROGR = {$src_vprogr} AND ESAM = {$esam} "; //GUID?
			$sql->exec($sql_q);
			while ($sql->get_row()){
				$progr = $sql->row['PROGR'];
				$sql->row['VISITNUM_PROGR'] = $vprogr;
				//$sql->row[$counterField] = "".$vprogr;
				$this->openEsamProgr($pkid,$vid,$vprogr,$esam,$progr);
				$this->updateEsamProgr($pkid,$vid,$vprogr,$esam,$progr,$sql->row);
				//echo "<br/>$sql_q";
			}
		}
		//return $sql->row;
				
	}
	
	//WORKFLOW
	function StatusChangePostOperation($dest) {
		//$dest e' l'id dello stato destinazione
		//Operazioni dopo transizione di stato nel WF
		/*
		$sql=new query($this->conn); 
		define("STATO_SEGRETERIA","3");
		define("STATO_INTEGRAZIONE","4");
		switch ($dest){
			case STATO_SEGRETERIA:
				//Apro la visita numero 2 se non e' gia' aperta
				$vid = 2;
				//Controllo visita aperta
				$sql_query="select * from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vid"; // and esam=1";
				$sql->exec($sql_query);
				$esams = array();
				while ($sql->get_row()){
					$esams[] = $sql->row['ESAM'];
				}
				$open = array();
				$open[] = 1;
				$open = array_diff($open, $esams);
				//print_r($open);
				//die();
				foreach ($open as $o){
					$sql_close="insert into {$this->xmr->prefix}_coordinate(visitnum,visitnum_progr,progr,esam,userid,{$this->xmr->pk_service},abilitato) values ($vid,0,1,$o,'{$this->userid}',{$this->pk_service},1) ";
					$sql->set_sql($sql_close);
					$sql->ins_upd();
				}
				
				break;
			case STATO_INTEGRAZIONE:
				//die("POLLO");
				$this->reOpenVisit(0);
				$this->reOpenVisit(2);				
				break;
		}
		*/
		$this->conn->commit();
		
		$location = "{$prefix}/uxmr/index.php?{$this->xmr->pk_service}={$this->pk_service}&exams";
		header ( "location:$location" );
		
		return;
	}
	/*
	function wf_nuovo_passaURC(){
		//Se ho iniziato da unita' di ricerca
		if ($this->pk_service != 'next') {
			//echo ("################PIPPO#############");	 elicitus4  Elicitus113
			//die("QUA");
			$profilo = $this->getProfilo($this->user->userid);
			$isnew = $this->isNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0);
			$sent = $this->isSent("{$this->xmr->prefix}_coordinate", $this->pk_service, 0, 0);			
			if($isnew && $sent && $profilo == "URC"){
				//echo("PASSA!");
				//Valorizzo la variabile isnew dentro il db, cosi' non ho piu' problemi.
				$this->setNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0, false);
				return true;
			}
		}		
		return false;		
	}

	function wf_nuovo_passaSGR(){
		//Se ho iniziato da segreteria
		if ($this->pk_service != 'next') {
			//echo ("################PIPPO#############");	
			//die("QUA");
			$profilo = $this->getProfilo($this->user->userid);
			$isnew = $this->isNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0);
			$sent = $this->isSent("{$this->xmr->prefix}_coordinate", $this->pk_service, 0, 0);			
			if($isnew && $sent && $profilo == "SGR"){
				//echo("PASSA!");
				//Valorizzo la variabile isnew dentro il db, cosi' non ho piu' problemi.
				$this->setNew("{$this->xmr->prefix}_registrazione", $this->pk_service, 0, 0, false);
				return true;
			}
		}		
		return false;		
	}
		
	function wf_compilazione_completata(){
		return $this->CheckVisitClosed("0");
	}
	
	function wf_segreteria_completata(){
		$close = true;
		$close = $close && $this->CheckVisitClosed("0");
		$close = $close && $this->CheckVisitClosed("2");
		return $close;
	}
	*/
	
	
	//Funzione bottone INVIA
	function WF_next_step(){
		//$vIds = "0,2,8,10";
		$vIds = $_GET['VISITNUM'];
		//die($vIds);
		$sql_query="select min(nvl(visitclose,0)) vc from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum in ({$vIds}) and inizio=1";
		$sql=new query($this->conn);
		$sql->get_row($sql_query);
		$closed=$sql->row['VC'];

		/*
		if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $this->integrazione->stato==0) {

			$closed=0;
		}
		*/
		
		if ($closed==1){
			//echo "sono nell'if se la VISITCLOSE=1";
			$closed_txt="OK";
			$closed_txt_="OK";
			
			/*
			if ($af_generated==1){
				
				
				$af_txt="OK";
			
//				echo "Primo invio: ".$primo_invio;
				if((isset($_COOKIE['equeryRichiesta']) && $_COOKIE['equeryRichiesta']=="yes") || ($primo_invio=="" && $sql->row['PROT_INVIO']!="") ) {
					$prot_iniziale="<p><b>Protocollo integrazione: $last_prot_invio</b></p>";
				}

				if ($prot_invio!='' && $primo_invio!="eq"){
					$prot_txt="Protocollo n.ro: $prot_invio ($prot_invio_dt) <br/>Codice Studio: {$this->registrazione['COD_PRA']} $prot_iniziale";
				} else {
					$prot_txt="<input type='button' value='Protocolla e Invia' onclick='if(confirm(\"Attenzione, si sta inviando la pratica ad AIFA, procedere?\")==true) window.location=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&ProtocollaPrat=yes&\"; else return false;'>";
				}
			} else {
				$link_af="&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' value='Genera PDF AF' onclick=\"
				this.style.display='none';
				ajax_call_('BuildAF','{$this->xmr->pk_service}={$this->pk_service}&BuildAF');
			\">";
				$closed_txt_.=$link_af;

			}
			*/

			$sql_query="select stato from {$this->service}_lista where {$this->xmr->pk_service}={$this->pk_service}";
			$sql_stato=new query($this->conn);
			$sql_stato->get_row($sql_query);
			
			/*
			if (($sql_stato->row['STATO']==1 || $sql_stato->row['STATO']==5) && $this->user->profilo=='Applicant'){
				
				$sql_lista_centri="select ce_denom,ce_userid,coordinatore from ossc3_centri_sc where {$this->xmr->pk_service}={$this->pk_service} order by coordinatore";
				$sql_centri=new query($this->conn);
	            $sql_centri->exec($sql_lista_centri);
	            $invio_centri="<form method='GET'><table><tr><td colspan=3 align=\"center\"><b>Selezionare i centri a cui inviare la CTA</b></tr></td>";
				while ($sql_centri->get_row()){
					if ($sql_centri->row['COORDINATORE']==1) {
						$invio_centri.="<tr><td><img src=\"images/checkedcheck.gif\"><input type=\"hidden\" name=\"{$sql_centri->row['CE_USERID']}\" value='1' ></td>
				                    <td><b>COORDINATORE:</b> {$sql_centri->row['CE_DENOM']}</td>
				                    <td><input type=\"button\" value=\"visualizza/aggiorna lettera di trasmissione\" onclick=\"window.open('index.php?mod_lettera=yes&CE={$sql_centri->row['CE_USERID']}&{$this->xmr->pk_service}={$this->pk_service}')\"></td>
				               </tr>";
					}
					else {
					$invio_centri.="<tr><td><input type=\"checkbox\" name=\"{$sql_centri->row['CE_USERID']}\" value='1' checked ></td>
				                    <td>{$sql_centri->row['CE_DENOM']}</td>
				                    <td><input type=\"button\" value=\"visualizza/aggiorna lettera di trasmissione\" onclick=\"window.open('index.php?mod_lettera=yes&CE={$sql_centri->row['CE_USERID']}&{$this->xmr->pk_service}={$this->pk_service}')\"></td>
				               </tr>";
					}
				}
				$invio_centri.="</table>";
					
				$invio_txt.=$invio_centri;
				$invio_txt.="<input type='hidden' name='inviaPrat'>
				<input type='hidden' name='{$this->xmr->pk_service}' value='{$this->pk_service}'>
				<input type='submit' value='Invia CTA'>
				</form>
				";
			}
			
			else {
				if ($this->user->profilo=='Applicant') {
					
					$sql_query="select CES from ossc3_registrazione where {$this->xmr->pk_service}={$this->pk_service}";
					$sql=new query($this->conn);
					$sql->exec($sql_query);
					$sql->get_row();
					$ces=$sql->row['CES'];
					$ces=rtrim($ces, "|");
					$array_ces=explode ('|',$ces);
					//print_r ($array_ces);
					$invio_txt="<p align=center><b>Comitati Etici selezionati:</b></p>";
					$invio_txt.="<p align=left>";
					foreach ( $array_ces as $index => $valore ) {
						$sql_query="select AZIENDA_ENTE from ana_utenti_3 where userid='$valore'";
						$sql=new query($this->conn);
						$sql->exec($sql_query);
						$sql->get_row();
						$invio_txt.="&nbsp&nbsp;<img src=\"images/checkedcheck.gif\"></img> &nbsp&nbsp;";
						$invio_txt.=$sql->row['AZIENDA_ENTE'];
						$invio_txt.="<br><br>";
					}
					$invio_txt.="<p align=center><a href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&add_center=yes\">Aggiungi la visibilita' ad altri CE</a></p></p>";
						
					$sql_query="select PROT_INVIO,ULTIMO_INVIO from ossc3_registrazione where {$this->xmr->pk_service}={$this->pk_service}";
					$sql=new query($this->conn);
					$sql->exec($sql_query);
					$sql->get_row();
					if ($sql->row['ULTIMO_INVIO']=='')
					$invio_txt.="<br><b>Domanda inviata elettronicamente il {$this->registrazione['PRIMO_INVIO']}<br>
					</b><br><br>
					";
					else
					$invio_txt.="<br><b>Domanda inviata elettronicamente per la prima volta il {$this->registrazione['PRIMO_INVIO']}<br>
					<br><br>
					Domanda reinviata elettronicamente il: {$sql->row['ULTIMO_INVIO']} (causa integrazione)</b><br><br>
					";
					//$invio_txt.="<b>Codice Studio: {$sql->row['PROT_INVIO']}</b>";
				}
				else {
					if($sql_stato->row['STATO']!=1) {
					    $sql_query="select PROT_INVIO,ULTIMO_INVIO from ossc3_registrazione where {$this->xmr->pk_service}={$this->pk_service}";
						$sql=new query($this->conn);
						$sql->exec($sql_query);
						$sql->get_row();
						if ($sql->row['ULTIMO_INVIO']=='')
						$invio_txt="<br><b>Domanda inviata elettronicamente il {$this->registrazione['PRIMO_INVIO']}<br>
						</b><br><br>
						";
						else
						$invio_txt="<br><b>Domanda inviata elettronicamente per la prima volta il {$this->registrazione['PRIMO_INVIO']}<br>
						<br><br>
						Domanda reinviata elettronicamente il: {$sql->row['ULTIMO_INVIO']} (causa integrazione)</b><br><br>
						";
						//$invio_txt.="<b>Codice Studio: {$sql->row['PROT_INVIO']}</b>";
					}
				}
			}
			*/
		}
		else {
			$closed_txt='';
			$closed_txt_='';
		}

		$html ="";
		
		#GC NUOVA_GRAFICA - Aggiungo breadcrumb e tabellina riassuntiva
		$this->percorso = $this->breadcrumb ( "exam_list" );
		$html .= "<br>" . $this->tb_riassuntiva ();
		
		$html .= "
		<div id=\"droplinetabs1\" class=\"droplinetabs\">
			<ul class=\"nav nav-tabs\">";
		// --and userid = '{$this->registrazione['USERID_INS']}'
		$sql_query="select distinct visitnum,esam from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service}";
		//echo $sql_query;
		
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			if (isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]))
			$visit_enabled[$sql->row['VISITNUM']]=true;
		}

		foreach ($this->vlist->visitnums as $key=>$val){
			if ($visit_enabled[$key])
			$html.="
			<li><a  href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;VISITNUM={$key}&amp;exams=visite_exams.xml\">
				<span class='selected'>{$this->vlist->visitnums[$key]['SHORT_TXT']}</span></a>
			</li>
			";
		}
		
		
//		$alert_prot="";
//		if($this->CheckInviata()!=1)
//		$alert_prot="<p style=\"width:60%;color:red;\"><b>ATTENZIONE:</b>
//		A causa di problemi con la protocollazione del Ministero della Salute, potrebbero verificarsi dei malfunzionamenti
//		nell'invio della pratiche.
//		</p>";

		$sql_query="select id_stato from {$this->service}wf_stato where pk_service={$this->pk_service}";
		$sql_stato=new query($this->conn);
		$sql_stato->exec($sql_query);
		$sql_stato->get_row();
		//if($sql_stato->row['ID_STATO']>1 && $sql_stato->row['ID_STATO']!=5) 
		//$invia_txt_tab="Ricevuta d'invio della CTA";
		//else 
		$invia_txt_tab="Invia Studio";

		if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $this->integrazione->stato==0 && $this->user->profilo=="Applicant") {

			$invia_txt_tab="Invia integrazione";
			$integrazione="
			<tr>
				<td colspan=2 align=center class=int>
					<img src=\"images/eq_img.png\" width=20px>
					Resoconto integrazione
					<img src=\"images/eq_img.png\" width=20px>
				</td>
			</tr>
			<tr>
				<td class=int>
					Schede modificate
				</td>
				<td class=int>
					Modifica
				</td>
			</tr>
			";
			$ret=$this->integrazione->getEqSpec($this->vlist);

			foreach ($ret as $key=>$val){
				$scheda=$this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]['TESTO'];
				$integrazione.="
				<tr>
					<td>
					<a href=\"index.php?ESAM={$val['PK']['ESAM']}&VISITNUM={$val['PK']['VISITNUM']}&VISITNUM_PROGR={$val['PK']['VISITNUM_PROGR']}&PROGR={$val['PK']['PROGR']}&{$this->xmr->pk_service}={$this->pk_service}\">{$val['SCHEDA']}</a>
					</td>
					<td>
					{$val['MODIFICA']}
					</td>
				</tr>
				";
			}
			$integrazione.="
				<tr>
							<td valign=\"top\" width=\"50%\">Verifica Completezza AF</td>
							<td valign=\"top\" width=\"50%\" id='CheckSchede'>$closed_txt
							</td>
				</tr>
				<tr>
							<td valign=\"top\" width=\"50%\">Chiusura Schede</td>
							<td valign=\"top\" width=\"50%\" id='CloseSchede'>$closed_txt_
							</td>
						</tr>
						<tr>
							<td valign=\"top\" width=\"50%\">Preparazione AF</td>
							<td valign=\"top\" width=\"50%\" id='BuildAF'>$af_txt
							</td>
						</tr>
						<!--
						<tr>
							<td valign=\"top\" width=\"50%\">Firma (<a href=\"javascript:window.location.reload();\">aggiorna</a>)</td>
							<td valign=\"top\" width=\"50%\" id='Firma'>$firma_txt
							</td>
						</tr>
						-->
						<tr>
							<td valign=\"top\" width=\"50%\">Protocollazione ed Invio</td>
							<td valign=\"top\" width=\"50%\" id='Prot' style=\"padding:5px;\">$prot_txt
							</td>
						</tr>
						$avviso_invio
			";
		}
		
		/*
		$html.="<li><a class='selected' href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;NextWFStep=yes\">
					<span>$invia_txt_tab</span></a>
				</li>
				";
		*/
		$html.="</ul>
		</div>
		
		<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=100%>
			<tr>
				<td align=center>$alert_prot
				<br/>$alert_jvm
					<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=70%>";

		$force_check="";
		if($closed_txt!="OK") $force_check="(<a target=\"_new\" href=\"index.php?HTML_ID=CheckSchede&{$this->xmr->pk_service}={$this->pk_service}&VISITNUM={$vIds}&CheckSchede=yes&forSend=yes\"
							onclick=\"alert('Attenzione, verra\' aperta una nuova finestra per forzare la verifica dei dati.\\nChiuderla per tornare all\'invio dello studio.');\"> Riprova</a>)";


		if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!='' && $this->integrazione->stato==0)
		$html.=$integrazione."</table>";
		else { //NO-INTEGRAZIONE
			
			//uxmr
			if ($this->service=='CE') $titolo="Invia Studio";
			
			//sedute
			if ($this->service=='GSE' && $this->session_vars['VISITNUM']==0) {
				$titolo="Attiva verbalizzazione";
				$html.="<script>
									$('#integrazione_open').hide();
								</script>";
				}
			if ($this->service=='GSE' && $this->session_vars['VISITNUM']==2) $titolo="Chiudi verbalizzazione";
			
			$html.="
							<!--integrazione-->
							<tr>
								<th colspan=3 class=int>$titolo</th>
							</tr>
							<tr>
								<td valign=\"top\" width=\"50%\">Verifica Completezza $force_check</td>
								<td valign=\"top\" width=\"50%\" id='CheckSchede'>$closed_txt
								</td>
							</tr>
							<!--
							<tr>
								<td valign=\"top\" width=\"50%\">Firma (<a href=\"javascript:window.location.reload();\">aggiorna</a>)</td>
								<td valign=\"top\" width=\"50%\" id='Firma'>$firma_txt
								</td>
							</tr>
							-->
							<tr>
								<td colspan=2 align=center id='InvioBox'>
									$invio_txt
								</td>
							</tr>
						</table>
					<br/>
    	
    	
					</td>
				</tr>
			</table>
			";
		}
		if ($closed==0) {
			$this->onload = "ajax_call_('CheckSchede','{$this->xmr->pk_service}={$this->pk_service}&VISITNUM={$vIds}&CheckSchede=yes&forSend=yes');";
		}
		return $html;		
		
	}
	//

	function getLastIntegrazioneId($id){
		$sql=new query($this->conn);
		$nextId = 0;
		$sql_query="select max(INTEGRAZIONE) as INTEGRAZIONE from {$this->service}_integrazioni where {$this->xmr->pk_service}={$id}";
		//echo $sql_query;
		$sql->exec($sql_query);
		if ($sql->get_row()){
			$nextId = $sql->row['INTEGRAZIONE'];
		}
		return $nextId;
	}
	
	function WF_integrazione(){

		$html = "";
		if (isset($_POST['submit'])){
			//Inserimento integrazione e ricaricamento pagina.
			$sql=new query($this->conn);
			/*
			$nextId = 0;
			$sql_query="select max(INTEGRAZIONE) from {$this->service}_integrazioni where {$this->xmr->pk_service}={$this->pk_service}";
			$sql->exec($sql_query);
			if ($sql->get_row()){
				$nextId = $sql->row['INTEGRAZIONE'];
			}
			*/
			$nextId = $this->getLastIntegrazioneId($this->pk_service);
			$nextId++;
			$testo = $_POST['testo'];
			$testo = str_replace("'","\\'",$testo);
			$sql_query="insert into {$this->service}_integrazioni({$this->xmr->pk_service},INTEGRAZIONE,TESTO) values ({$this->pk_service},{$nextId},'$testo')";
			$sql->set_sql($sql_query);
			$sql->ins_upd();
			
			//Salvo i dati e ricarico lo studio
			$this->conn->commit();
			$url = explode("?",$_SERVER['REQUEST_URI']);
			$location = "{$url[0]}?{$this->xmr->pk_service}={$this->pk_service}&exams";
			header ( "location:$location" );
		}else{
			//Form di inserimento richiesta integrazione
		
			$sql_query="select stato from {$this->service}_lista where {$this->xmr->pk_service}={$this->pk_service}";
			$sql_stato=new query($this->conn);
			$sql_stato->get_row($sql_query);
				
		
			$html = "
			<div id=\"droplinetabs1\" class=\"droplinetabs\">
				<ul>";
			
			// --and userid = '{$this->registrazione['USERID_INS']}'
			$sql_query="select distinct visitnum,esam from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service}";
		
			$sql=new query($this->conn);
			$sql->exec($sql_query);
			while ($sql->get_row()){
				if (isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]))
				$visit_enabled[$sql->row['VISITNUM']]=true;
			}
		
			foreach ($this->vlist->visitnums as $key=>$val){
				if ($visit_enabled[$key])
				$html.="
				<li><a  href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;VISITNUM={$key}&amp;exams=visite_exams.xml\">
					<span class='selected'>{$this->vlist->visitnums[$key]['SHORT_TXT']}</span></a>
				</li>
				";
			}

			/*
			$sql_query="select id_stato from {$this->service}wf_stato where pk_service={$this->pk_service}";
			$sql_stato=new query($this->conn);
			$sql_stato->exec($sql_query);
			$sql_stato->get_row();
			*/
			$invia_txt_tab="Richiesta INTEGRAZIONE";
			
			$form_action = $_SERVER['REQUEST_URI'];
			$html.="<li><a class='selected' href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;NextWFStep=yes\">
						<span>$invia_txt_tab</span></a>
					</li>
				</ul>
			</div>
			<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=100%>
				<tr>
					<td align=center>$alert_prot
					<br/>
						<form action=\"$form_action\" method=\"POST\">
						<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=70%>
							<!--integrazione-->
							<tr>
								<th colspan=3 class=int>Richiedi Integrazione</th>
							</tr>
							<tr>
								<td valign=\"top\" align=\"center\" width=\"90%\" colspan=3><textarea name=\"testo\" cols=\"100\" rows=\"10\"></textarea></td>
							</tr>
							<tr>
								<td valign=\"top\" align=\"center\" width=\"90%\" colspan=3><input type=\"submit\" name=\"submit\" value=\"Invia richiesta\" /></td>
							</tr>
						</table>
						</form>
					<br/>
		
		
					</td>
				</tr>
			</table>
			";
		}
		return $html;		
		
	}
	//
	function WF_valutabile(){

		$html = "";
		if (isset($_POST['submit'])){
			//Inserimento integrazione e ricaricamento pagina.
			$sql=new query($this->conn);

			$testo = $_POST['testo'];
			$testo = str_replace("'","\\'",$testo);
			$sql_query="update {$this->service}_registrazione set VALUTABILE=1, VALUTABILE_TEXT = '$testo' where {$this->xmr->pk_service} = {$this->pk_service} ";
			$sql->set_sql($sql_query);
			$sql->ins_upd();
			
			//Salvo i dati e ricarico lo studio
			$this->conn->commit();
			$url = explode("?",$_SERVER['REQUEST_URI']);
			$location = "{$url[0]}?{$this->xmr->pk_service}={$this->pk_service}&exams";
			header ( "location:$location" );
		}else{
			//Form di inserimento richiesta integrazione
		
			$sql_query="select stato from {$this->service}_lista where {$this->xmr->pk_service}={$this->pk_service}";
			$sql_stato=new query($this->conn);
			$sql_stato->get_row($sql_query);
				
		
			$html = "
			<div id=\"droplinetabs1\" class=\"droplinetabs\">
				<ul>";
			
			// --and userid = '{$this->registrazione['USERID_INS']}'
			$sql_query="select distinct visitnum,esam from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service}";
		
			$sql=new query($this->conn);
			$sql->exec($sql_query);
			while ($sql->get_row()){
				if (isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]))
				$visit_enabled[$sql->row['VISITNUM']]=true;
			}
		
			foreach ($this->vlist->visitnums as $key=>$val){
				if ($visit_enabled[$key])
				$html.="
				<li><a  href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;VISITNUM={$key}&amp;exams=visite_exams.xml\">
					<span class='selected'>{$this->vlist->visitnums[$key]['SHORT_TXT']}</span></a>
				</li>
				";
			}

			/*
			$sql_query="select id_stato from {$this->service}wf_stato where pk_service={$this->pk_service}";
			$sql_stato=new query($this->conn);
			$sql_stato->exec($sql_query);
			$sql_stato->get_row();
			*/
			$invia_txt_tab="Rendi studio valutabile";
			
			$form_action = $_SERVER['REQUEST_URI'];
			$html.="<li><a class='selected' href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;NextWFStep=yes\">
						<span>$invia_txt_tab</span></a>
					</li>
				</ul>
			</div>
			<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=100%>
				<tr>
					<td align=center>$alert_prot
					<br/>
						<form action=\"$form_action\" method=\"POST\">
						<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=70%>
							<!--integrazione-->
							<tr>
								<th colspan=3 class=int>Approva studio e rendi valutabile</th>
							</tr>
							<tr>
								<td valign=\"top\" align=\"center\" width=\"90%\" colspan=3><textarea name=\"testo\" cols=\"100\" rows=\"10\"></textarea></td>
							</tr>
							<tr>
								<td valign=\"top\" align=\"center\" width=\"90%\" colspan=3><input type=\"submit\" name=\"submit\" value=\"Rendi Valutabile\" /></td>
							</tr>
						</table>
						</form>
					<br/>
		
		
					</td>
				</tr>
			</table>
			";
		}
		return $html;		
		
	}
	//
	
	function WF_check() {
		
		//$visits[]=0;
		$visits[]=$_GET['VISITNUM'];
		//$visits[]=1;
		//$visits[]=2;
		//$visits[]=4;
		//$visits[]=5;
		//$visits[]=6;
		//$visits[]=7;
		
		//In questa funzione viene controllata l'obbligatorieta' dei campi nelle schede (potrei fare send), anche se sono salvate
		$ret = $this->CheckClosure ($visits);
		ob_clean();
		echo $_GET ['HTML_ID'] . "#DIV#";
		//DEBUG
		//		$ret ['Check']=1;
		//print_r($ret);
		//die();
		
		if ($ret ['Check']) {
			if ($_GET['forSend']!=''){
				if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
					$js_action="window.location.href='index.php?{$this->xmr->pk_service}={$this->pk_service}&SendEqInt=yes';";
					if ($this->integrazione->non_appr_states[$this->registrazione['STATO']]) $txt_button="Effettua Modifiche";
					else $txt_button="Invia richiesta di integrazione";
				}
				else {
					$js_action="ajax_call_('CheckSchede','{$this->xmr->pk_service}={$this->pk_service}&CloseSchede=yes&VISITNUM={$_GET['VISITNUM']}');";
					$txt_button="Prosegui";
				}
				#GC NUOVA_GRAFICA
				//$link_close="<input type='button' id='sendAifaButton' onclick=\"
				//if (confirm('Attenzione! Proseguendo verranno chiuse tutte le schede. Proseguire?')) {
				//	this.style.display='none';
				//	$js_action
				//}
				//else return false;
				//\" value='$txt_button &gt;&gt;'>";
				
				$link_close="<button type=\"button\" id='sendAifaButton' class=\"btn btn-info\" onclick=\"
				if (confirm('Attenzione! Proseguendo verranno chiuse tutte le schede. Proseguire?')) {
					this.style.display='none';
					$js_action
				}
				else return false;
				\">
					<i class=\"fa fa-lock bigger-110\"></i>
					".$txt_button ."
				</button>
				";
				
				
					die("OK &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$link_close");
			}
			die ( "OK" );
		} else {
			foreach ( $ret ['AggInfo'] as $key => $val ) {
				$url_encoded=urlencode("index.php?{$this->xmr->pk_service}={$this->pk_service}|and|NextWFStep=yes|and|VISITNUM={$_GET['VISITNUM']}");
				$html .= "<li><a href=\"{$val['href']}&link_to=$url_encoded\">{$val['TEXT']}</a>";
			}
			$html .=$html_agg;
			die ( $html );
		}
	
	}//


	function CloseSchede(){
		$sql=new query($this->conn);
	////Inserimento data di invio - ci serve?////
		//$sql_check_prot="select prot_invio from ossc3_registrazione where {$this->xmr->pk_service}={$this->pk_service}";
		//$sql->get_row($sql_check_prot);
		//if ($sql->row['PROT_INVIO']==''){
		//	$sql_update="update ossc3_registrazione set PROT_INVIO='OSSC/'||to_char(sysdate,'YYYY')||'/'||OSSC3_PROT.nextval, PROT_INVIO_DT=sysdate where {$this->xmr->pk_service}={$this->pk_service}";
		//	$sql=new query($this->conn);
		//	$sql->set_sql($sql_update);
		//	$sql->ins_upd();
		//}
	////Fine Inserimento data di invio////
		
	////Generazione AF in pdf e salvataggio in WCA////
		////Creazione pdf
		//$this->session_vars['pdf']="make";
		//$filePDF=$this->make_cta_form($this->pk_service, true, true);
		////Inserimento in wca
		//$doc_id_query="select docs_id.nextval as id_doc from dual";
		//$sql2=new query($this->conn);
		//$sql2->get_row($doc_id_query);
		//$id_doc=$sql2->row['ID_DOC'];
		//$docsValues['ID']=$id_doc;
		//$docsValues['EXT']="pdf";
		//$docsValues['USERID']=$this->user->userid;
		//$id_tipo_ref=200000+$this->pk_service;
		//$sql2=new query($this->conn);
		//$sql2_id_ref="select id_ref from docs where id_tipo_ref=$id_tipo_ref and topic='CTA' and keywords='CTA_FORM'";
		//if ($sql2->get_row($sql2_id_ref)) $id_ref=$sql2->row['ID_REF'];
		//else $id_ref=$id_doc;
		////controllo da fare prima
		//$docsValues['ID_REF']=$id_ref;
		//$docsValues['TIPO_DOC']="Doc_Area";
		//$docsValues['DATA']="sysdate";
		//$docsValues['TITOLO']="CTA";
		//$docsValues['NOME_FILE']="CTA_Form.pdf";
		//$docsValues['AUTORE']=$this->user->nome_cognome;
		//$docsValues['PRJ']="2";
		//$docsValues['ID_TIPO_REF']=200000+$this->pk_service;
		//$docsValues['KEYWORDS']="CTA_FORM";
		//$docsValues['TOPIC']="CTA";
		////$docsValues['APPROVED']="1";
		////$docsValues['APPROV_DT']="sysdate";
		////$docsValues['APPROV_COMM']="Invio domanda";
		////$docsValues['APPROVED_BY']=$this->user->userid;
		//$tb="docs";
		//$sql2=new query($this->conn);
		//$pk='';
		//$sql2->insert($docsValues, $tb, $pk);
		//$file_dest=$docsValues['NOME_FILE'];
		//$file_dest="/http/www/ossc/html/ossc3/WCA/docs/Doc_Area{$id_doc}.pdf";
		//$cpCommand="cp /http/www/ossc/html/ossc3/$filePDF $file_dest";
		//system ("cp /http/www/ossc/html/ossc3/$filePDF $file_dest");
		//system ("chgrp devj /http/www/ossc/html/ossc3/temp_html/*");
		//system ("chmod g+w /http/www/ossc/html/ossc3/temp_html/*");
	////Fine Generazione AF in pdf e salvataggio in WCA////
		
//		//Pulizia WCA
//		$id_tipo_ref=1000000+$this->pk_service;
//		$sql_update_pulizia_wca="update docs d set d.id_ref=(select min(d1.id) from docs d1 where d1.id_tipo_ref=d.id_tipo_ref and d1.titolo=d.titolo) where d.id_tipo_ref=$id_tipo_ref";
//		$sql_update_1="update docs set approv_comm='Invio Domanda', approved=1, approv_dt=sysdate, approved_by='{$this->user->userid}' where id in (
//			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
//			)";
//		$sql_update_2="update docs set tipo_doc='Trash' where id not in (
//			select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
//			) and id_tipo_ref=1000282";
//		$sql->set_sql($sql_update_pulizia_wca);
//		$sql->ins_upd();
//		$sql=new query($this->conn);
//		$sql->set_sql($sql_update_1);
//		$sql->ins_upd();
//		$sql->set_sql($sql_update_2);
//		$sql->ins_upd();		

		//Chiudo tutte le schede
		$vIds = $_GET['VISITNUM'];
		$sql_close="update {$this->xmr->prefix}_coordinate set fine=1, visitclose=1 where {$this->xmr->pk_service}={$this->pk_service} and visitnum in ($vIds)";
		$sql->set_sql($sql_close);
		$sql->ins_upd();
		//if ($_GET['VISITNUM']==0 && $this->service=='CE' && $this->dettaglio['STATO_INT']==2) $this->SendMailSgr(1);
		//else if ($_GET['VISITNUM']==0 && $this->service=='CE') $this->SendMailSgr(3);
		////Flag generazione cta - non mi serve	
		//$sql_af_generated="update {$this->xmr->prefix}_registrazione set cta_generated=1 where {$this->xmr->pk_service}={$this->pk_service}";
		//$sql->set_sql($sql_af_generated);
		//$sql->ins_upd();
		
		//Approvazione Documenti Generali
		
		$id_area = 1;
		$id_tipo_ref = $this->pk_service + (AREA_OFFSET*$id_area);
		$sql_update_1="update docs set approv_comm='Invio Schede generali', approved=1, approv_dt=sysdate, approved_by='{$this->user->userid}' where id in (
   	select id from (select max(id) as id, id_ref  from docs where id_tipo_ref=$id_tipo_ref group by id_ref)
   	) and tipo_doc='Doc_Area' and (keywords like 'DOC_CORE%')";
		$sql_1=new query($this->conn);
		$sql_1->set_sql($sql_update_1);
		$sql_1->ins_upd();

		//Passaggio di stato.
		
		
		//Chiudo e genero html di risposta
		$this->conn->commit();
		ob_clean();
		echo $_GET ['HTML_ID'] . "#DIV#";
		//$go_fwd = $this->FirmaAF(true);
		
		#GC NUOVA_GRAFICA
		//$go_fwd = "Operazione completata con successo.&nbsp;&nbsp;&nbsp;<input type='button' id='go_firma' onclick=\"window.location.reload();\" value='Prosegui &gt;&gt;' />";
		$go_fwd = "Operazione completata con successo.&nbsp;&nbsp;&nbsp;<button class='btn btn-info' type='button' onclick=\"window.location.reload();\"><i class='icon icon-lock bigger-110'></i>Prosegui</button>";
		$go_fwd .= "<script language=\"javascript\">alert('Operazione completata.');</script>";
		die("$go_fwd");
	}//


	function CloseSchedeProgr($redirect=true){
		$sql=new query($this->conn);

		//Chiudo tutte le schede
		$vId = $_GET['VISITNUM'];
		$vProgr = $_GET['VISITNUM_PROGR'];
		$sql_close="update {$this->xmr->prefix}_coordinate set fine=1, visitclose=1 where {$this->xmr->pk_service}={$this->pk_service} and visitnum = $vId and visitnum_progr = $vProgr";
		$sql->set_sql($sql_close);
		$sql->ins_upd();
		//Chiudo e genero html di risposta
		
		//Approvo i documenti centro specifici
		$id_area = 1;
		$id_tipo_ref = $this->pk_service + (AREA_OFFSET*$id_area);
		$sql_update_1="update docs set approv_comm='Invio Schede centro specifiche', approved=1, approv_dt=sysdate, approved_by='{$this->user->userid}' where id in (
   	select id from (select id from {$this->xmr->prefix}_DOC_CENTRO_CME where {$this->xmr->pk_service}={$this->pk_service} and visitnum=$vId and visitnum_progr=$vProgr)
   	) and tipo_doc='Doc_Area'";
		$sql_1=new query($this->conn);
		$sql_1->set_sql($sql_update_1);
		$sql_1->ins_upd();
		
		$new_vprogr=$vProgr+1;
		$sql_update_2="update {$this->xmr->prefix}_CENTRILOCALI set stato=1 where {$this->xmr->pk_service}={$this->pk_service} and visitnum=0 and visitnum_progr=0 and progr=$new_vprogr";
		Logger::send($sql_update_2);
		$sql_2=new query($this->conn);
		$sql_2->set_sql($sql_update_2);
		$sql_2->ins_upd();
		
		//if ($_GET['VISITNUM']==1 && $this->service=='CE') $this->SendMailSgr(2);
		
		$this->conn->commit();
		ob_clean();

		if ($redirect){
			header("Location: ?{$this->xmr->pk_service}={$this->pk_service}&VISITNUM={$vId}&VISITNUM_PROGR={$vProgr}&exams");
			die();
		}
	}//

	function CloseVisit($vIdArr){

		foreach ($vIdArr as $vId){
		
		//Chiudo la visita
		$sql_close="update {$this->xmr->prefix}_coordinate set visitclose=1 where {$this->xmr->pk_service}={$this->pk_service} and visitnum = $vId";
		$sql=new query($this->conn);
		$sql->set_sql($sql_close);
		$sql->ins_upd();

		//Chiudo gli esam salvati della visita
		$sql_close="update {$this->xmr->prefix}_coordinate set fine=1 where {$this->xmr->pk_service}={$this->pk_service} and visitnum = $vId and inizio=1";
		$sql=new query($this->conn);
		$sql->set_sql($sql_close);
		$sql->ins_upd();
		
		$this->conn->commit();
		ob_clean();

//		if ($redirect){
//			header("Location: ?{$this->xmr->pk_service}={$this->pk_service}&VISITNUM={$vId}&VISITNUM_PROGR={$vProgr}&exams");
//			die();
//		}
		}
	}
	
	function CheckVisitClosed($vIds){
		$closed = 0;
		//$vIds = "2";
		if ($this->pk_service != 'next') {
			$sql_query="select min(nvl(visitclose,0)) vc from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum in ({$vIds}) and inizio=1";
			Logger::send($sql_query);
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$closed=$sql->row['VC'];
	
		}
		return ($closed==1);
	}
	
	function CheckVisitProgrClosed($vIds){
		$closed = 0;
		//$vIds = "2";
		$spl = explode(",",$vIds);
		foreach ($spl as $vId){
			$maxprogr = $this->getMaxVprogr($this->pk_service,$vId);
			for ($i = 0; $i<=$maxprogr;$i++){
				$cval = 0;
				if ($this->pk_service != 'next') {
					$sql_query="select min(nvl(visitclose,0)) vc from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}={$this->pk_service} and visitnum in ({$vId}) and visitnum_progr = $i and inizio=1";
					$sql=new query($this->conn);
					$sql->get_row($sql_query);
					$cval=$sql->row['VC'];
				}
				$closed = ($cval==1);
				if ($closed){
					break;
				}
			}
			if ($closed){
				break;
			}
		}
		return $closed;
	}
	
	function CheckVisitProgrClosedSpecific($pkid, $vId, $vprogr){
		Logger::send('CheckVisitProgrClosedSpecific');
		$closed = 0;
		$cval = 0;
		if ($this->pk_service != 'next') {
			$sql_query="select min(nvl(visitclose,0)) vc from {$this->xmr->prefix}_coordinate where {$this->xmr->pk_service}={$pkid} and visitnum in ({$vId}) and visitnum_progr = $vprogr and inizio=1";
			$sql=new query($this->conn);
			$sql->get_row($sql_query);
			$cval=$sql->row['VC'];
		}
		$closed = ($cval==1);
		Logger::send($closed);
		return $closed;
	}
	
	function getDatiUtente($userid) {
		$sql_str="select * from ana_utenti where userid =:userid";
		$bindVars["userid"]=$userid;
		$sql=new query($this->conn);
		$sql->exec($sql_str, $bindVars);
		$sql->get_row();
		return $sql->row;
	}

	function getDatiAna2($userid) {
		$sql_str="select * from ana_utenti_2 where userid =:userid";
		$bindVars["userid"]=$userid;
		$sql=new query($this->conn);
		$sql->exec($sql_str, $bindVars);
		$sql->get_row();
		return $sql->row;
	}
		
	function getDatiUtente2($userid) {
		$sql_str="select * from ana_utenti_2 where userid =:userid";
		$bindVars["userid"]=$userid;
		$sql=new query($this->conn);
		$sql->exec($sql_str, $bindVars);
		$sql->get_row();
		return $sql->row;
	}
	
	function setDate($table,$field,$pkid){
		$sql=new query($this->conn);
		$sql_close="update {$this->xmr->prefix}_{$table} set {$field}=sysdate where {$this->xmr->pk_service} = {$pkid} and progr=1 ";
		$sql->set_sql($sql_close);
		$sql->ins_upd();		
	}
	
	function setText($table,$field,$pkid, $value){
		$sql=new query($this->conn);
		$sql_close="update {$this->xmr->prefix}_{$table} set {$field}=:field_value where {$this->xmr->pk_service} = {$pkid} and progr=1 ";
		$bindVars["field_value"]=$value;
		//$sql->set_sql($sql_close, $bindVars);
		$sql->ins_upd($sql_close, $bindVars);		
	}
	
	function addField($table,$field,$pkid,$val = 1){
		$sql=new query($this->conn);
		$sql_close="update {$this->xmr->prefix}_{$table} set {$field}=nvl({$field},0)+$val where {$this->xmr->pk_service} = {$pkid} and progr=1 ";
		$sql->set_sql($sql_close);
		$sql->ins_upd();
	}
	
	function suppressEmpty($array){
		$retval = array();
		foreach ($array as $a){
			if ($a != ""){
				$retval[] = $a;
			}
		}
		return $retval;
	}
	
	function SaveEqInt(){
		
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
		$xml=$this->vlist->esams[$_POST['VISITNUM']][$_POST['ESAM']]['XML'];
		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
		//die("QUI");
		$this->integrazione->SaveEqInt($xml_form);
		//die("QUA");
		header("location: index.php?{$this->xmr->pk_service}={$this->pk_service}&exams&VISITNUM={$_POST['VISITNUM']}");
		die();

	}
	
	function emendamento_invia_per_approvazione(){
		//Se ho INVIATO la form, lancio aggiornamento nuovo emendamento
		//Apro integrazioni per quello studio?!
		$pkid = $this->pk_service;
		$curvnum = 20;
		
		//LUIGI: disattivo vecchia tipologia emendamento
		#GC 06/11/2014# Nuova gestione EME e riapertura schede - Non prendo pi?getMaxVprogr perch?osso avere + EME in parellelo e quindi devo riaprire la scheda dell'emendamento in oggetto
		//$vprogr = $this->getMaxVprogr($pkid,$curvnum);
		$vprogr = $this->session_vars ['VISITNUM_PROGR'];
		#FINE
		
		$this->inviaEmendamento($pkid);
		//die("INVIO X APPROVAZIONE");
		
		//Apro schede verifica doc e parere
		
		$sql_query_eme_1="select count(*) as conto_val_eme from {$this->service}_coordinate where {$this->xmr->pk_service}=$pkid and visitnum=$curvnum and visitnum_progr=$vprogr and esam=2";
		$sql_eme_1=new query($this->conn);
		$sql_eme_1->get_row($sql_query_eme_1);
		$conto_val_eme=$sql_eme_1->row['CONTO_VAL_EME'];
		if ($conto_val_eme == 0) {
			
			//Luigi:creo le scheda di valutazione doc col progressivo dei soli centri selezionati
			$sql_query_centri="select strutture 
				from ce_emendamenti 
				where
				{$this->xmr->pk_service}=$pkid
				and visitnum_progr=$vprogr";
			$sql_centri=new query($this->conn);
			$sql_centri->get_row($sql_query_centri);
			$centri=str_replace('|',',',$sql_centri->row['STRUTTURE']);
			$centri=trim($centri,',');
			
			$sql_query_progr="select progr,centro,d_centro from ce_centrilocali 
				where
				{$this->xmr->pk_service}=$pkid
				and centro in ($centri)";
			$sql_progr=new query($this->conn);
			$sql_progr->exec($sql_query_progr);
			
			while ($sql_progr->get_row()){
			
			$this->openEsamProgr($pkid,$curvnum,$vprogr,2,$sql_progr->row['PROGR'], true, false);
			
			//Luigi:salvo il centro relativo alla progressiva
			$fields = array();
			$fields['INVIO_DT'] = "SYSDATE";
			$fields['CENTRO'] = $sql_progr->row['CENTRO'];
			$fields['D_CENTRO'] = $sql_progr->row['D_CENTRO'];
			$this->updateEsamProgr($pkid,$curvnum,$vprogr,2,$sql_progr->row['PROGR'],$fields);
			}
		}
		
		#GC 06/11/2014# Nuova gestione EME e riapertura schede. Chiudo "Dati Emendamento" per far scomparire il bottone "Procedi con la verifica amministrativa"
		$array_eme['ID_STUD'] =  $pkid;
		$array_eme['VALUE'] = "1";
		$array_eme['VISITNUM_PROGR']=$vprogr;
		$sql = "update {$this->service}_COORDINATE set FINE=:value where {$this->xmr->pk_service}=:id_stud and esam=1 and visitnum=20 and visitnum_progr =:visitnum_progr and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array_eme);		
		#FINE
		
		//die("INVIO X APPROVAZIONE");
		$this->conn->commit();
		header("location: index.php?{$this->xmr->pk_service}={$this->pk_service}&exams&VISITNUM={$curvnum}");
		die();
				
	}
	
	function ritiraPage(){
		//Se ho INVIATO la form, lancio aggiornamento nuovo emendamento
		//Apro integrazioni per quello studio?!
		$html = "";
		if (isset($_POST['submit'])){
			//Inserimento ritiro e ricaricamento pagina.
			$this->ritira($_POST['testo']);
		}else{
			//Form di inserimento richiesta integrazione
		
			$sql_query="select stato from {$this->service}_lista where {$this->xmr->pk_service}={$this->pk_service}";
			$sql_stato=new query($this->conn);
			$sql_stato->get_row($sql_query);
				
			#GC NUOVA_GRAFICA - Aggiungo breadcrumb e tabellina riassuntiva
			$this->percorso = $this->breadcrumb ( "exam_list" );
			$html .= "<br>" . $this->tb_riassuntiva ();
			
			$html .= "
			<div id=\"droplinetabs1\" class=\"droplinetabs\">
				<ul class=\"nav nav-tabs\">";
			
			// --and userid = '{$this->registrazione['USERID_INS']}'
			$sql_query="select distinct visitnum,esam from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service}";
		
			$sql=new query($this->conn);
			$sql->exec($sql_query);
			while ($sql->get_row()){
				if (isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]))
				$visit_enabled[$sql->row['VISITNUM']]=true;
			}
		
			foreach ($this->vlist->visitnums as $key=>$val){
				if ($visit_enabled[$key])
				$html.="
				<li><a  href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;VISITNUM={$key}&amp;exams=visite_exams.xml\">
					<span class='selected'>{$this->vlist->visitnums[$key]['SHORT_TXT']}</span></a>
				</li>
				";
			}

			/*
			$sql_query="select id_stato from {$this->service}wf_stato where pk_service={$this->pk_service}";
			$sql_stato=new query($this->conn);
			$sql_stato->exec($sql_query);
			$sql_stato->get_row();
			*/
			$invia_txt_tab="Ritira studio";
			
			$form_action = $_SERVER['REQUEST_URI'];
			//GIULIO 08/05/2013 - NextWFStep=yes genera errore
			//$html.="<li><a class='selected' href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;NextWFStep=yes\">
			$html.="<li><a class='selected' href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;Ritira=yes\">
						<span>$invia_txt_tab</span></a>
					</li>
				</ul>
			</div>
			<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=100%>
				<tr>
					<td align=center>$alert_prot
					<br/>
						<form action=\"$form_action\" method=\"POST\">
						<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=70%>
							<!--integrazione-->
							<tr>
								<th colspan=3 class=int>Ritira studio</th>
							</tr>
							<tr>
								<td valign=\"top\" align=\"center\" width=\"90%\" colspan=3><textarea name=\"testo\" cols=\"100\" rows=\"10\"></textarea></td>
							</tr>
							<tr>
								<td valign=\"top\" align=\"center\" width=\"90%\" colspan=3>
								<!--input type=\"submit\" name=\"submit\" value=\"Ritira\" onclick=\"return confirm('Ritirare lo studio?');\" /-->
								<button class=\"btn btn-info\" type=\"submit\" name=\"submit\" onclick=\"return confirm('Ritirare lo studio?');\">
									<i class=\"fa fa-lock bigger-110\"></i> Ritira
								</button>
								</td>
							</tr>
						</table>
						</form>
					<br/>
		
		
					</td>
				</tr>
			</table>
			";
		}
		return $html;		
				
	}
	function ritira($motivo){
		//Se ho INVIATO la form, lancio aggiornamento nuovo emendamento
		//Apro integrazioni per quello studio?!
		$pkid = $this->pk_service;
		$field = "RITIRATO";
		$this->setFlag($pkid,$field);		
		$this->setDate("REGISTRAZIONE","CHIUSURA_DT",$pkid);
		$this->setText("REGISTRAZIONE","CHIUSURA_TEXT",$pkid,$motivo);
		//die("RITIRA!");		
		$this->conn->commit();
		header("location: index.php?{$this->xmr->pk_service}={$this->pk_service}&exams&VISITNUM=0");
		die();
				
	}
	function mostraRitiro(){
		$html = "";
		
		//Form di inserimento richiesta integrazione
		$sql_query="select stato from {$this->service}_lista where {$this->xmr->pk_service}={$this->pk_service}";
		$sql_stato=new query($this->conn);
		$sql_stato->get_row($sql_query);
		
		#GC NUOVA_GRAFICA - Aggiungo breadcrumb e tabellina riassuntiva
		$this->percorso = $this->breadcrumb ( "exam_list" );
		$html .= "<br>" . $this->tb_riassuntiva ();
		
		$html .= "
		<br>
		<div id=\"droplinetabs1\" class=\"droplinetabs\">
			<ul class=\"nav nav-tabs\">";
		
		// --and userid = '{$this->registrazione['USERID_INS']}'
		$sql_query="select distinct visitnum,esam from {$this->service}_coordinate where {$this->xmr->pk_service}={$this->pk_service}";
	
		$sql=new query($this->conn);
		$sql->exec($sql_query);
		while ($sql->get_row()){
			if (isset($this->vlist->esams[$sql->row['VISITNUM']][$sql->row['ESAM']]))
			$visit_enabled[$sql->row['VISITNUM']]=true;
		}
	
		foreach ($this->vlist->visitnums as $key=>$val){
			if ($visit_enabled[$key])
			$html.="
			<li><a  href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;VISITNUM={$key}&amp;exams=visite_exams.xml\">
				<span class='selected'>{$this->vlist->visitnums[$key]['SHORT_TXT']}</span></a>
			</li>
			";
		}

		$invia_txt_tab="Ritira studio";
		
		//Carica dati ritiro
		$sql_datiq="select * from {$this->service}_registrazione where {$this->xmr->pk_service}={$this->pk_service}";
		$sql_dati=new query($this->conn);
		$sql_dati->get_row($sql_datiq);
		$data = $sql_dati->row['CHIUSURA_DT'];
		$motivo = $sql_dati->row['CHIUSURA_TEXT'];
		//Mostra tabella e pagina
		
		//GIULIO 03/05/2013 Link commentato in quanto non e' corretto (e genera anche errore)
		//$html.="<li><a class='selected' href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;NextWFStep=yes\">
		$html.="<li class='active'><a class='selected' href=\"index.php?{$this->xmr->pk_service}={$this->pk_service}&amp;ShowRitiro=yes\">
					<span>$invia_txt_tab</span></a>
				</li>
			</ul>
		</div>
		<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=100%>
			<tr>
				<td align=center>$alert_prot
				<br/>
					
					<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=70%>
						<!--integrazione-->
						<tr>
							<th colspan=3 class=int>Studio Ritirato in data $data</th>
						</tr>
						<tr>
							<td valign=\"top\" align=\"center\" width=\"90%\" colspan=3><textarea name=\"testo\" cols=\"100\" rows=\"10\" readonly=\"readonly\">$motivo</textarea></td>
						</tr>
						
					</table>

				<br/>
	
	
				</td>
			</tr>
		</table>
		";
		
		return $html;		
		
	}
	
	
	/*
	function getCalendarArray(){
		$service = $this->service;
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
			select {$this->xmr->pk_service},{$highlight['RICHIESTA']},{$highlight['CONFERMA']},{$highlight['RIFIUTO']} from {$highlight['TAB']} where {$this->xmr->pk_service} = {$id} 
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
	*/
	
	function isFlag($pkid,$field){
		$array['ID_STUD'] =  $pkid;
		$sql = "select $field from {$this->service}_REGISTRAZIONE where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		if ($query->get_row()){
			return ($query->row[$field] == 1);
		}else{
			return false;
		}
	}
	function setFlag($pkid,$field){
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "1";
		$sql = "
			update {$this->service}_REGISTRAZIONE set $field=:value where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		return true;		
	}
	function resetFlag($pkid,$field){
		$array['ID_STUD'] =  $pkid;
		$array['VALUE'] = "0";
		$sql = "
			update {$this->service}_REGISTRAZIONE set $field=:value where {$this->xmr->pk_service}=:id_stud and esam=0 and visitnum=0 and visitnum_progr = 0 and progr=1";
		$query = new query($this->conn);
		$query->exec($sql, $array);
		return true;		
	}
	
	function DeleteProgrEsam_dario($visitnum, $visitnum_progr, $esam, $progr, $center=null, $redir = true) {
		//		print_R($this->integrazione);
		if (isset($this->integrazione) && $this->integrazione->eq_enabled && $this->integrazione->profilo==$this->integrazione->role){
			if ($this->integrazione->eq_int=='') $this->integrazione->CreateEq();
			$sql_update="update {$this->service}_coordinate set
			inv_query={$this->integrazione->eq_int},
			EQ_ACTION=2
			where
			esam=$esam
			and progr=$progr
			and visitnum=$visitnum
			and visitnum_progr=$visitnum_progr
			and {$this->config_service['PK_SERVICE']}={$this->pk_service}
			";
			$sql=new query($this->conn);
			$sql->set_sql($sql_update);
			$sql->ins_upd();
			$this->conn->commit();
			die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=index.php?VISITNUM_PROGR=$visitnum_progr&{$this->config_service['PK_SERVICE']}={$this->pk_service}&ESAM=$esam&VISITNUM=$visitnum&JUST_DELETE=yes\"></head></html>" );
		}
		//innanzitutto mi occupo di capire se esistono esami correlati (del tipo dispensazione e richiesta farmaco, che sono strettamente legate)
		
		//estrazione tabella dell'esame
		$sql=new query($this->conn);
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['XML'] );
		$table = $xml_form->form ['TABLE'];
		echo ($table."<br>");

		//LO STORICO!!!
		$sql_storico = "insert into S_{$table} select '{$this->user->userid}', sysdate, storico_id.nextval, 'E', null, {$table}.*  from $table where {$this->config_service['PK_SERVICE']}='{$_GET[$this->config_service['PK_SERVICE']]}' and VISITNUM={$visitnum} and VISITNUM_PROGR={$visitnum_progr} and ESAM={$esam} and PROGR={$progr}";
		$sql->set_sql ( $sql_storico );
		$sql->ins_upd ();

		//Fields file docs (WCA)
		$id_area = 1;
		//$id_area = $this->pk_service + (AREA_OFFSET*$id_area);
		$id_tipo_ref = $this->pk_service + (AREA_OFFSET*$id_area);
		$wca_docs='';
		foreach ($xml_form->fields as $key=>$val){
			if ($val['TYPE']=="file_doc"){
				$wca_docs[$val['VAR']]=true;
			}
		}
		print_r($wca_docs);
		//die();
		foreach ($wca_docs as $key => $val){
			$key = "{$key}_{$visitnum_progr}";
			if ($progr!=1) $key="{$key}_{$progr}";
			//$id_tipo_ref=700000+$this->pk_value;
			$sql_update="update docs set tipo_doc='Trash' where id_tipo_ref=$id_tipo_ref and keywords='$key'";
			//die($sql_update);
			$sql3=new query($this->conn);
			$sql3->set_sql($sql_update);
			$sql3->ins_upd();
		}
		//TODO: Bisognerebbe sistemare il progressivo mettendo -1 nel key per tutti i doc con _ID > $progr
		
		//se ce ne sta una sola, bisogna rimuovere solo dalla tabella di origine
		$sql_query = "
			select
				count(*) as conto
			from {$this->service}_coordinate
			where esam=$esam
			and visitnum=$visitnum
			and visitnum_progr=$visitnum_progr
			and {$this->config_service['PK_SERVICE']}={$this->pk_service}";
		echo ($sql_query."<br>");
		$sql = new query ( $this->conn );
		$sql->set_sql ( $sql_query );
		$sql->exec ();
		$sql->get_row ();
		$n = $sql->row ['CONTO'];
		echo ($n."<br>");
		
		if($n==1) {
			$sql_delete = "
				delete from {$table}
				where esam=$esam
				and visitnum=$visitnum
				and visitnum_progr=$visitnum_progr
				and {$this->config_service['PK_SERVICE']}={$this->pk_service}
				and progr=$progr
				";
			if ($progr==1) {
				$sql_update = "
				update {$this->service}_coordinate
				set fine=null,
				inizio=null
				where esam=$esam
				and visitnum=$visitnum
				and visitnum_progr=$visitnum_progr
				and {$this->config_service['PK_SERVICE']}={$this->pk_service}
				and progr=$progr
				";
				
				$sql_update_riapre_visita = "
				update {$this->service}_coordinate
				set visitclose=null
				where visitnum=$visitnum
				and visitnum_progr=$visitnum_progr
				and {$this->config_service['PK_SERVICE']}={$this->pk_service}
				and progr=$progr
				";
			} else {
				$sql_update = "
				delete from {$this->service}_coordinate
				where esam=$esam
				and visitnum=$visitnum
				and visitnum_progr=$visitnum_progr
				and {$this->config_service['PK_SERVICE']}={$this->pk_service}
				and progr=$progr
				";
			}
			$sql->set_sql ( $sql_delete );
			$sql->ins_upd ();
			$sql->set_sql ( $sql_update );
			$sql->ins_upd ();
			if ($progr==1) {
				$sql->set_sql ( $sql_update_riapre_visita );
				$sql->ins_upd ();
			}
			$this->conn->commit();
		} else {

			//delete della progressiva dalle coordinate
			$sql_query = "DELETE FROM {$this->service}_coordinate
		WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service}
		AND progr=$progr
		AND esam=$esam
		AND visitnum_progr=$visitnum_progr
		AND visitnum=$visitnum";
			$sql = new query ( $this->conn );
			$sql->set_sql ( $sql_query );
			$sql->ins_upd ();
			$this->conn->commit();

			//aggiunta di una coordinata alla fine (max(progr)+1) per non rompere le costraints
			$sql_query = "INSERT
		INTO {$this->service}_coordinate
		  (
		    VISITNUM,
		    VISITNUM_PROGR,
		    PROGR,
		    ESAM,
		    INIZIO,
		    FINE,
		    INSERTDT,
		    MODDT,
		    USERID,
		    VISITCLOSE,
		    INV_QUERY,
		    {$this->config_service['PK_SERVICE']},
		    ABILITATO
		  )
		  (SELECT VISITNUM,
		      VISITNUM_PROGR,
		      (SELECT MAX(progr)+1 AS PROGR FROM {$this->service}_coordinate WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service} AND esam=$esam and visitnum_progr=$visitnum_progr and visitnum=$visitnum) as PROGR,
		      ESAM,
		      INIZIO,
		      FINE,
		      INSERTDT,
		      MODDT,
		      USERID,
		      VISITCLOSE,
		      INV_QUERY,
		      {$this->config_service['PK_SERVICE']},
		      ABILITATO
		    FROM {$this->service}_coordinate
		    WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service}
		    AND esam     =$esam
		    and visitnum_progr=$visitnum_progr
				and visitnum=$visitnum
		    AND progr    =
		      (SELECT MAX(progr) FROM {$this->service}_coordinate WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service} AND esam=$esam and visitnum_progr=$visitnum_progr and visitnum=$visitnum)
		      )
		";
		      $sql = new query ( $this->conn );
		      $sql->set_sql ( $sql_query );
		      $sql->ins_upd ();
		      $this->conn->commit();

		      //update della progressiva dalle coordinate
		      $sql_query = "UPDATE {$this->service}_coordinate
	    SET progr    =progr-1
	    WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service}
	    AND progr    >$progr
	    AND esam     =$esam
	    AND VISITNUM_PROGR=$visitnum_progr
		and visitnum=$visitnum";
		      $sql = new query ( $this->conn );
		      $sql->set_sql ( $sql_query );
		      $sql->ins_upd ();
		      $this->conn->commit();

		      //update della progressiva dall'esame
		      $sql_query = "UPDATE $table
	    SET progr    =progr-1
	    WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service}
	    AND progr    >$progr
	    AND esam     =$esam
	    AND VISITNUM_PROGR=$visitnum_progr
		and visitnum=$visitnum";
		      $sql = new query ( $this->conn );
		      $sql->set_sql ( $sql_query );
		      $sql->ins_upd ();
		      $this->conn->commit();

		      //delete della progressiva ultima di coordinate
		      $sql_query = "DELETE FROM {$this->service}_coordinate
	    WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service}
	    AND esam     =$esam
		AND VISITNUM_PROGR=$visitnum_progr
		and visitnum=$visitnum
    	AND progr    =
    	(SELECT MAX(progr) FROM {$this->service}_coordinate WHERE {$this->config_service['PK_SERVICE']}={$this->pk_service} AND esam=$esam
    	AND VISITNUM_PROGR=$visitnum_progr AND visitnum=$visitnum)";
		      //		echo $sql_query;
		      $sql = new query ( $this->conn );
		      $sql->set_sql ( $sql_query );
		      $sql->ins_upd ();
		      $this->conn->commit();

		}
		//Se ci sono campi file_doc, bisognerebbe rimuovere anche il documento associato
		
		
		if ($redir === true)
			die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=index.php?exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}&CENTER=$center&JUST_DELETE=yes\"></head></html>" );
	}
	
	function SaveForm($xml_form_file, $ajax_call = false) {
		$sql_query="select nvl(r.in_emendamento,0) in_emendamento, r.in_emendamento_approvazione 
		from {$this->config_service['service']}_registrazione r
		where r.{$this->config_service['PK_SERVICE']}='{$this->pk_service}'
		";
		$sql=new query($this->conn);
		$sql->get_row($sql_query);
		$forceSave=false;
		Logger::send($_POST['VISITNUM']);
		Logger::send($_POST['ESAM']);
		if(($sql->row['IN_EMENDAMENTO']=="0" || $sql->row['IN_EMENDAMENTO_APPROVAZIONE']=="1") && $this->config_service['ALWAYS_SAVEABLE'][$_POST['VISITNUM']][$_POST['ESAM']] )
			$forceSave=true;	
			parent::SaveForm($xml_form_file, $ajax_call, $forceSave);
		}
	//LUIGI: disattivo vecchia tipologia emendamento
	#GC 05/11/2014# Nuova gestione EME e riapertura schede. Funzione importata da study_prototype
	function invia_db_dm($xml_form, $debug = null) {
		
		global $filetxt;
		global $body;
		$filetxt = preg_replace ( "/<!--user_name-->/", "Loading...", $filetxt );
		//		print($body);
		$conn = $this->conn;
		$in = $this->session_vars;
		$service = $this->service;
		//		foreach ( $in as $key => $val )
		//		$in [$key] = ora_escape ( $in [$key] );
		
		$this->invia_form ( $xml_form, $in );
		Logger::trace();
		
//		$this->conn->commit();
//		$sql_query="select * from {$this->config_service['service']}_coordinate 
//		where id_stud=1006 and visitnum=0 and esam=1";
//		$sql=new query($this->conn);
//		$sql->get_row($sql_query);
//		echo $sql->row['VISITCLOSE'];
//	  header("Location:index.php?CENTER=9&ID_STUD=1006&VISITNUM=0&ESAM=1&PROGR=1&form=dati_clinici.xml");
	  
	//	die();
		
		
		
		
		if ($in ['ID_QUERY'] > 0) {
			$query = new query ( $this->conn );
			$sql_equery = "update " . $this->config_service['service_root']. "_equery set validata=1, val_userid=:userid, val_dt=sysdate, chiusa='1', chiusa_dt=sysdate where id=:id_query";
			unset($bindUpdate);
			$bindUpdate['USERID']=$in ['remote_userid'];
			$bindUpdate['ID_QUERY']=$in ['ID_QUERY'];
			$query->ins_upd ($sql_equery,$bindUpdate);//binded
		}

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

		if ($in ['ID_QUERY'] > 0) {
			
			#GC 05/11/2014# Nuova gestione EME e riapertura schede. Cambio il redirect link di ritorno dopo una riapertura forzata
			//$link = "{$lvl_up}index.php?eQuery";
			$link = "{$lvl_up}index.php?exams=visite_exams.xml&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&CENTER={$in['CENTER']}&VISITNUM={$in['VISITNUM']}";
			#FINE
			
		} else {
			$link = "{$lvl_up}index.php?exams=visite_exams.xml&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&CENTER={$in['CENTER']}&VISITNUM={$in['VISITNUM']}";
		}
		if (isset ( $in ['ajax_call'] )) {
			die ( "link_to:" . $link );
		} else {
			$this->check_visit_closure ();
			if (! ($debug == 1))
			$filetxt = preg_replace ( "/<!--meta refresh-->/", "<meta http-equiv=\"refresh\" content=\"1;url=$link\">", $filetxt );
		}

		$this->conn->commit ();
		$in ['invia'] = '';
		$in ['INVIOCO'] = '';
		$in ['ESAM'] = '';
		$form = '';
		$in ['form'] = '';
		if ($debug != 1)
		$filetxt = preg_replace ( "/<!--meta refresh-->/", "<meta http-equiv=\"refresh\" content=\"1;url=$link\">", $filetxt );
		$script = "";
		$onload = '';
		$body = ' &nbsp; SAVING...';
	}
	
}

?>
