<?php
// include_once "libs/navigation_bar.inc";
// include_once "libs/audit_trail.inc";



/**
 * Classe Studio
 *
 * Contiene tutte le spcifiche dello studio tra cui il Controller
 *
 * @package XMR 2.0
 */
class Study extends Study_prototype_mxmr { // Utilizzare assolutamente Study_prototype_mxmr e non Study_prototype
	
	function getStudyTitle(){
		$sql_query = "select TITLE FROM STUDIES WHERE PREFIX=:PREFIX";
		$bind ['PREFIX'] = $this->service;
		$sql = new query ( $this->conn );
		$sql->get_row ( $sql_query, $bind );
    	return $sql->row['TITLE'];
    }
		
	/*
	 * Controller Smista le richieste pervenute lanciando gli eventi opportuni
	 */
	function Controller() {
		global $in;
		global $filetxt;
		global $service;
		global $conn;
		// Logger::send ( "controller study.inc.php" );
		parent::Controller ();
		
		$cornice = $this->CorniceHtml ();
		
		if (isset ( $this->session_vars ['ret_registrazione'] ) && $in ['CODPAT'] != '') {
			
			/* Generazione nuova password */
			// $pass=GeneratePassword(8,1);
			
			// while(CheckPasswordExist($pass)==true){
			// $pass=GeneratePassword(8,1);
			// }
			// UpdatePatPassword($xml_form,$pass);
			
			/* Query in db per mostrare la password */
			// $sql_password="select * from {$service}_REGISTRATION where codpat={$in['CODPAT']}";
			// echo $sql_password;
			// $sql_exist=new query($this->conn);
			// $sql_exist->set_sql($sql_password);
			// $sql_exist->exec();
			// $sql_exist->get_row();
			// print_r( $sql_exist->row['PASSWORD']);
			
			if (isset ( $this->session_vars ['recovery_password'] )) {
				$body .= "<TABLE align=center class=\"bordi\" width=\"70%\">
     			<TR>
		           <TD align=center><b><font size=\"3\">Patient  {$sql_exist->row['SUBJID']} </font> <br>
						<br>
						<br>
						<!--<font size=\"4\">PIN CODE:</font>
						<font size=\"4\" color=\"#FF952B\"> {$sql_exist->row['PASSWORD']}</font>-->
						<br><br>
						<br>
					<a href=\"javascript:history.back();\"><u> << Turn back</u></a></TD>
					</TR>
				</TABLE>";
			} else {
				$body .= "<TABLE align=center class=\"bordi\" width=\"70%\">
	     			<TR>
		           <TD align=center><b><font size=\"3\">The Patient  {$sql_exist->row['SUBJID']} has been registered</font> <br>
						<br>
						<br>
						<!--<font size=\"4\">PIN CODE:</font>
						<font size=\"4\" color=\"#FF952B\"> {$sql_exist->row['PASSWORD']}</font>-->
						<br><br>
						<br>
					<!--<b><font size=\"2\"><a href=\"index.php?CENTER={$this->session_vars['CENTER']}&{$this->config_service['PK_SERVICE']}={$this->pk_service}&VISITNUM=1&ESAM=1&form=informed_consent_demog.xml\"><u>Go to the next exam</u></a><br><br><br><br>-->
					<b><font size=\"2\"><a href=\"index.php?CENTER={$this->session_vars['CENTER']}&{$this->config_service['PK_SERVICE']}={$this->pk_service}&exams=visite_exam.xml\"><u>Go to Patient View</u></a><br><br><br><br>
					<a href=\"index.php?list=patients_list_center.xml\"><u>Registered Patients List</u></a></TD>
					</TR>
				</TABLE>";
			}
			$cornice = preg_replace ( "/<!--form-->/", $body, $cornice );
			
			$this->body = $cornice;
		}
		
		if ($this->session_vars ['CODPAT'] != '' && $this->session_vars ['EPRO_REPORT'] == 'yes') {
			if ($this->session_vars ['PATIENT_LANG'] == 'ENG') {
				header ( "Location: https://{$_SERVER['SERVER_NAME']}/uxmrdevice/uxmr/index.php?CRF=1&CODPAT={$this->session_vars['CODPAT']}" );
			} elseif ($this->session_vars ['PATIENT_LANG'] != '') {
				header ( "Location: https://{$_SERVER['SERVER_NAME']}/uxmrdevice/uxmr{$this->session_vars['PATIENT_LANG']}/index.php?CRF=1&CODPAT={$this->session_vars['CODPAT']}" );
			} elseif ($this->session_vars ['PATIENT_LANG'] == '' && isset ( $this->session_vars ['PATIENT_LANG'] )) {
				$cornice = $this->CorniceHtml ();
				$message = "No data yet available for the selected patient";
				$body .= "
				<form name=\"form1\" method=\"post\">
				<TABLE align=center class=\"bordi\" width=\"70%\">
	     			<TR>
			           <TD align=center><b><font size=\"3\">
			           $message
			           <br><br><br>
					<a href=\"javascript:history.back();\"><u> << Turn back</u></a>
					</TD>
						</TR>
					</TABLE>
					</form>";
				
				$cornice = preg_replace ( "/<!--form-->/", $body, $cornice );
				$this->body = $cornice;
			}
		}
		
		if (isset ( $_GET ['eQuery'] ) || isset ( $_POST ['eQuery'] )) {
			$this->body = $this->Equery ();
		}
		
		if (isset ( $_POST ['ID_QUERY'] ) && ! isset ( $_POST ['eform'] ) && $_POST ['ERISP'] == '') {
			$this->eQuerySave ();
		}
	}
	
	/**
	 * Genera il codice HTML della HomePage
	 */
	function HomePage() {
		// var_dump($this);
		// $legend_upper = "";
		// if (preg_match ( "/^MS/", $in ['remote_userid'] ) || preg_match ( "/^AIFA/", $in ['remote_userid'] ))
		// $xml_page = 'home_ms.xml';
		// if ($in ['USER_TIP'] == 'DM')
		// $xml_page = 'home_dm.xml';
		// if ($in ['USER_TIP'] == 'RO')
		// $xml_page = 'home_ro.xml';
		// var_dump($this->configurer);
		// die();
		/*$xml_page = "home_" . $this->user->profilo . ".xml";
		
		$body .= "<!--$xml_page-->";
		$this->xml_page = $xml_page;
		$page = new xml_page ( $this->xml_dir . '/' . $xml_page, $this->admin_profili );
		$body .= $page->page_html ();
		$body .= $this->footer;
		
		// Nuovo modo di generare il menu briciola di pane
		$this->percorso = $this->breadcrumb ( "home" );
		$this->body .= $this->percorso;
		
		$this->body .= $body;
		*/
		
		//VMAZZEO 09.06.2014 uso codice di Carlo (drug-prm) per far caricare un file statico home_[PROFILO].html al posto dell'xml home_[PROFILO].xml
		$home_html=$this->xml_dir . "/home_".$this->user->profilo.".html";
		if (file_exists($home_html)){
			$this->body=file_get_contents($home_html);
		}
		else{
			$xml_page = "home_" . $this->user->profilo . ".xml";
			
			if (file_exists($this->xml_dir . '/' .$xml_page)){
				$body .= "<!--$xml_page-->";
				$this->xml_page = $xml_page;
				$page = new xml_page ( $this->xml_dir . '/' . $xml_page, $this->admin_profili );
				$this->body .= $page->page_html ();
			}
	    	else {
	    		$this->body=file_get_contents("home.html");
			}
		}
		
    	$paths[]=array("home", "Home page", "/index.php");
    	$this->breadcrumb=new BreadCrumb($paths);
		
	}
	function CorniceHtml() {
		$cornice = '
		<style>
		/* Table Layout */
		.main-box{
			margin: 0 auto;
			margin-top:20px; 
			width:500px;
			vertical-align:top;
			height:250px;
			
		}
		
		.main-top-sx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-top-sx.gif) no-repeat bottom right;
		}
		
		.main-top{
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-top.gif) repeat-x bottom;
		}
		
		.main-top-dx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-top-dx.gif) repeat-x bottom left;
		}
		
		.main-sx{
			width:2px;
			background:#ffffff url(../../../LOGIN/images/main-sx.gif) repeat-y;
		}
		
		.main-dx{
			width:2px;
			background:#ffffff url(../../../LOGIN/images/main-dx.gif) repeat-y;
		}
		
		.main-bottom-sx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-bottom-sx.gif) no-repeat;
		}
		
		.main-bottom{
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-bottom.gif) repeat-x;
		}
		
		.main-bottom-dx{
			width:2px;
			height:2px;
			background:#ffffff url(../../../LOGIN/images/main-bottom-dx.gif) repeat-x;
		}
		</style>
		<table class="main-box" cellpadding="7px" cellspacing="0" >
			<!-- START - ROW TOP SX -->
			<tr>
				<td class="main-top-sx"></td>
				<td class="main-top"></td>
				<td class="main-top-dx"></td>
			</tr>
			<!-- FINE - ROW TOP SX -->
			
			<!-- START - ROW CORPO -->
			<tr>
				<td class="main-sx"></td>
				<td class="main-cx" ><!--form--></td>
				<td class="main-dx"></td>
			</tr>
			<!-- FINE - ROW CORPO -->
			
			<!-- START - ROW BOTTOM -->
			<tr>
				<td class="main-bottom-sx"></td>
				<td class="main-bottom"></td>
				<td class="main-bottom-dx"></td>
			</tr>
			<!-- FINE - ROW BOTTOM -->
		</table>';
		return $cornice;
	}
	
	/**
	 * make_patient_table()
	 * Costruisce la tabella riassuntiva del paziente.
	 * Vengono aggunti i pulsanti per le eQuery e l'Audit Trail
	 */
	function make_patient_table() {
		$sql_query = "
        select a.center,
               a.codpat,
               a.siteid,
               a.subjid,
               coor.INSERTDT
               
          from {$this->service}_REGISTRAZIONE a,{$this->service}_coordinate coor
          where 
           a.{$this->config_service['PK_SERVICE']}=:pk_service
           and coor.{$this->config_service['PK_SERVICE']}=a.{$this->config_service['PK_SERVICE']}
           and coor.visitnum=a.visitnum
           and coor.visitnum_progr=a.visitnum_progr
           and coor.esam=a.esam
           and coor.progr=a.progr
           
         
         ";
		$bind ['PK_SERVICE'] = $this->pk_service;
		$sql = new query ( $this->conn );
		$sql->get_row ( $sql_query, $bind );
		
		global $in;
		global $remote_userid;
		global $service;
		
		$service = $this->service;
		$session_vars = $this->session_vars;
		unset ( $session_vars ['VISITNUM'] );
		$vlist = new xml_esams_list ( $this->xml_dir . "/" . $this->visit_structure_xml, $this->config_service, $session_vars, $this->conn, $this->xml_dir );
		//$nav_bar = new navigation_bar_specific_study ( $service, $this->conn, $this->config_service, $vlist );
		//$html_nav = $nav_bar->navigation_bar_html ( $in );
		
		$tabella = "
        		<div class=\"widget-box\">
					<!--div class=\"widget-header header-color-blue\">
						<h5 class=\"bigger lighter\">
						<i class=\"fa fa-user\"></i>
						Patient's data
						</h5>
					</div -->
					<div class=\"widget-body\">
						<div class=\"widget-main no-padding\">
							<table class=\"table table-striped table-bordered table-hover\">
								<tr>             
					                <td class=destra >" . mlOut ( "System.patient_table.center_code", "Center Code" ) . "</td>
					               	<td class=input><b> {$sql->row['SITEID']}&nbsp;</b></td>
					               	
					               	<td class=destra >" . mlOut ( "System.patient_table.patient_code", "Patient Code" ) . "</td>
					               	<td class=input><b> {$sql->row['SUBJID']}&nbsp;</b></td>
					               	
					               	<td class=destra >" . mlOut ( "System.patient_table.registration_date", "Registration Date" ) . "</td>
					               	<td class=input><b> {$sql->row['INSERTDT']}&nbsp;</b></td>
					                "; //Attenzione che poi devo chiudere il TR!
		$is_sub_form=false;
		
		if ($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['SUB'] == "yes" && ! isset ( $in ['PROGR'] )) {
			$is_sub_form = true;
		}
		//echo $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['SUB']." ".$is_sub_form." ?!? ".$in ['PROGR'];
		if ($is_sub_form == false) {
			//echo var_dump($in);
			/**
			 * Creazione dell'istanza dell'oggetto audit_trail, chiamiamo il metodo audit_trail_html($in) che genera l'html con il link che
			 * abilita e disabilita la funzionalit? audit_trail.
			 */
			$html_at = "<td style=\"vertical-align:top;\" colspan=\"2\" >&nbsp;</td>";
            $html_at_small = "<i class=\"fa fa-eye\" style=\"color: lightgray;\"></i>";
			if (isset ( $in ['ESAM'] ) ) {
				$audit_trail = new audit_trail ( $service, $this->conn, $this->config_service, $vlist );
                if (!isset($in ['form']) || !$in ['form']){
                    $in ['form'] = $vlist->esams[$in['VISITNUM']][$in['ESAM']]['XML'];
                }
				$html_at = $audit_trail->audit_trail_html ( $in );
                $html_at = "<td style=\"vertical-align:top;\" colspan=\"1\" >{$html_at}</td>";
                $html_at_small = $audit_trail->audit_trail_html ( $in, true );
			}
			
			$html_eq = "<td style=\"vertical-align:top;\" colspan=\"1\" ><div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;".mlOut ( "System.patient_table.link_eq_on", "Data Quality")."</div>
					<div style=\"float:right\">".mlOut ( "System.patient_table.eq_not_available", "Not Available" )."</div></td>";
            $html_eq_small = "<i class=\"fa fa-comment\" style=\"color: lightgray;\" id=\"html_eq_small\"></i>";

			/**
			 * Creazione della barra per l'apertura o meno delle eQ e della modifica della form da parte del DM
			 */
			
			if (isset ( $in ['ESAM'] ) && isset ( $in ['form'] )) {
				
				/**
				 * Gestione del progr per i field progressivi , in caso di ALL_IN e ADD_BLANK non considero il
				 * progr nella select delle eQ
				 */
				if ($vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ALL_IN'] == 'yes' && $vlist->esams [$in ['VISITNUM']] [$in ['ESAM']] ['ADD_BLANK'] == 'yes') {
					$and_progr = "";
				} elseif (! isset ( $in ['PROGR'] )) {
					$and_progr = "and c.PROGR=1";
				} else {
					$and_progr = "and c.PROGR=:PROGR";
				}
				
				if (! isset ( $in ['VISITNUM_PROGR'] )) {
					$in ['VISITNUM_PROGR'] = 0;
				}
				
				if ($this->config_service ['dblock'] == 1 && isset ( $this->config_service ['dblock'] )) {
					/**
					 * gestione DBLOCK
					 * vmazzeo luglio 2013
					 */
					$query = new query ( $this->conn );

                    $bind['PK_SERVICE'] = $this->pk_service;
                    $bind['ESAM'] = $in['ESAM'];
                    $bind['PROGR'] = $in['PROGR'];
                    $bind['VISITNUM'] = $in['VISITNUM'];
                    $bind['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
                    $bind['CODPAT'] = $in['CODPAT'];
                    $bind['CENTER'] = $in['CENTER'];

                    // CONTROLLO SE QUESTO PAZIENTE E' DISABILITATO
                    $lock_query = 0;
                    $lock_obvious = 0;
					if (isset ( $in ['CODPAT'] ) && $in ['CODPAT'] != 'next' && isset ( $in ['CENTER'] ) && $in ['CENTER'] != '') {
						
						$sql_closed = "select FINE , ABILITATO , l.CENTER ,l.CODPAT, DBLOCK  from {$service}_coordinate c , {$service}_dblock l
						where c.{$this->xmr->pk_service}=:pk_service
						and c.ESAM=:esam
						and c.VISITNUM=:visitnum
						and c.VISITNUM_PROGR=:visitnum_progr
						and l.center=:center
						and l.codpat=:codpat
						$and_progr
						UNION
						select FINE , ABILITATO , l.CENTER ,l.CODPAT, DBLOCK  from {$service}_coordinate c , {$service}_dblock l
						where c.{$this->xmr->pk_service}=:pk_service
						and c.ESAM=:esam
						and c.VISITNUM=:visitnum
						and c.VISITNUM_PROGR=:visitnum_progr
						and l.center=:center
						and l.codpat=-1
						$and_progr
						ORDER BY CODPAT DESC";
						//echo "LIVELLO DI CENTRO <b>$sql_closed</b>";
						
						// PRENDO SOLTANTO IL PRIMO RECORD (se paziente è overridato spunterà per primo, altrimenti ho il dblock generico per il centro)
						if ($query->get_row ( $sql_closed, $bind  )) {
							$patient_to_lock = $query->row ['CENTER'];
							$lock_equery_obvious_buttons = $query->row ['DBLOCK'];
						}
						//echo "<br/>lock_equery_obvious_buttons ".$lock_equery_obvious_buttons;
						$patient_dblock_bin = decbin ( $lock_equery_obvious_buttons );
// 						echo "<br/>patient_dblock_bin ".$patient_dblock_bin;
						
						$patient_dblock_bin = substr ( "00000000" . $patient_dblock_bin, - 1 * sizeof ( $this->config_service ['dblock_functions'] ) );
						$lock_save_send = substr ( $patient_dblock_bin, - 1 * array_search ( 'SAVESEND', $this->config_service ['dblock_functions'] ), 1 );
// 						echo "<br/>lock_save_send ".$lock_save_send; 
						$lock_query = substr ( $patient_dblock_bin, - 1 * array_search ( 'EQUERY', $this->config_service ['dblock_functions'] ), 1 );
// 						echo "<br/>lock_query ".$lock_query;
						$lock_obvious = substr ( $patient_dblock_bin, - 1 * array_search ( 'OBVIOUSCORRECTION', $this->config_service ['dblock_functions'] ), 1 );
// 						echo "<br/>lock_obvious ".$lock_obvious;
						//echo $patient_dblock_bin." QUESTO PAZIENTE E' DISABILITATO QUERY? ".$lock_query." OBVIOUS? : ".$lock_obvious;
					}
					if ($query->numrows == 0 || (! $lock_query && ! $lock_obvious)) {
						$sql_closed = "select FINE , ABILITATO from {$service}_coordinate c
						where c.{$this->xmr->pk_service}=:PK_SERVICE
						and c.ESAM=:ESAM
						and c.VISITNUM=:VISITNUM
						and c.VISITNUM_PROGR=:VISITNUM_PROGR
						$and_progr ";
						//echo "C'è dblock attivo ma non centro bloccato ".$sql_closed;
						$query = new query ( $this->conn );
						$query->exec ( $sql_closed, $bind );
					} else {
                        $sql_closed = "select FINE , ABILITATO from {$service}_coordinate c
                        where c.{$this->xmr->pk_service}=:pk_service
                        and c.ESAM=:esam
                        and c.VISITNUM=:visitnum
                        and c.VISITNUM_PROGR=:visitnum_progr
                        $and_progr ";
                        // echo "NON C'è dblock ".$sql_closed;
                        $query = new query ( $this->conn );
                        $query->exec ( $sql_closed, $bind  );
                    }

                    while ( $query->get_row () ) {
                        //var_dump($query->row);
                        $is_close = $query->row ['FINE'];
                        if ($is_close == 1 && $query->row ['ABILITATO'] != 2) {
                            if ($this->config_service ['dblock'] == 1 && isset ( $this->config_service ['dblock'] )) {
                                //echo "chiamo eqbar ( {$lock_query}, {$lock_obvious} )";
                                $html_eq = $this->eQBar ( $lock_query, $lock_obvious );
                                $html_eq_inner = $this->eQBar ( $lock_query, $lock_obvious, true );
                            } else {
                                //echo "chiamo eqbar ()";
                                $html_eq = $this->eQBar ();
                                $html_eq_inner = $this->eQBar ( 0, 0, true );
                            }
                            $html_eq="<td style=\"vertical-align:top;\" colspan=\"2\" >{$html_eq}</td>";
                        }
                    }


                    /**
                     * VISUALIZZO SPECCHIETTO CON I VARI LOCK*
                     */
                    $dblock_table = "";
                    $label_dblock=mlOut("System.patient_table.label_dblock", "DB LOCK STATUS");
                    $dblock_table .= "
                            <td  style=\"vertical-align:top;\" colspan=\"1\" >
                                <div class=\"center\"><i class=\"fa fa-lock\"></i>&nbsp;".$label_dblock."</div>
                            ";

                    $lock_save_send_label=mlOut("System.patient_table.lock_save_send_label", "Save/Send forms");
                    $dblock_table .= "<div style=\"float:left\">".$lock_save_send_label."</div>";
                    if ($lock_save_send == 1) {
                        $dblock_table .= "<div style=\"float:right\"><i class=\"red fa fa-lock\"></i></div>";
                    } else {
                        $dblock_table .= "<div style=\"float:right\"><i class=\"green fa fa-unlock\"></i></div>";
                    }


                    $lock_query_label=mlOut("System.patient_table.lock_query_label", "eQuery");
                    $dblock_table .= "<div style=\"clear:none\">&nbsp;</div>";//</div><div style=\"float:left\">".$lock_query_label."</div>";
                    $dblock_table .= "<div style=\"float:left\">".$lock_query_label."</div>";
                    if ($lock_query == 1) {
                        $dblock_table .= "<div style=\"float:right\"><i class=\"red fa fa-lock\"></i></div>";
                    } else {
                        $dblock_table .= "<div style=\"float:right\"><i class=\"green fa fa-unlock\"></i></div>";
                    }

                    $lock_obvious_label=mlOut("System.patient_table.lock_obvious_label", "Obvious corrections");
                    $dblock_table .= "<div style=\"clear:none\">&nbsp;</div>";//</div><div style=\"float:left\">".$lock_query_label."</div>";
                    $dblock_table .= "<div style=\"float:left\">".$lock_obvious_label."</div>";
                    if ($lock_obvious == 1) {
                        $dblock_table .= "<div style=\"float:right\"><i class=\"red fa fa-lock\"></i></div>";
                    } else {
                        $dblock_table .= "<div style=\"float:right\"><i class=\"green fa fa-unlock\"></i></div>";
                    }
                    $dblock_table .= "</td>";
                }

                $html_SDV = "<td style=\"vertical-align:top;\" colspan=\"2\" ><div style=\"float:left\"><i class=\"fa fa-search\"></i>&nbsp;SDV</div><div style=\"float:right\">not activated</div></td>";
                $html_SDV_small = "<i class=\"fa fa-search\" style=\"color: lightgray;\"></i>";
                if(class_exists('SDV_module')){
                    $html_SDV_small = "<a href=\"#\" id=\"sdvicon\" onclick=\"return false;\" title=\"\" ><i class=\"fa fa-search\" ></i></a>";
                    $sdv=new SDV_module($this->conn,$this->session_vars,$this->config_service,$this->config_service['service'],$this->vlist,$this->xml_dir);
                    $result=$sdv->after_make_patient_table();
                    if($result!=''){
                        $html_SDV="<td style=\"vertical-align:top;\" colspan=\"2\" >{$result}</td>";;
                    }
                    //Altra roba
                    if (isset ( $in ['ESAM'] ) && isset ( $in ['form'] ) && isset ( $this->config_service ['SDV'] ) && $this->config_service ['SDV'] == "1" ) {
                        $SDV = new SourceDataVerification ( $service, $this->conn, $this->config_service, $vlist );
                        $result = $SDV->SDV_html ( $in );
                        $html_SDV .= "<td style=\"vertical-align:top;\" colspan=\"2\" >{$result}</td>";
                    }
                }
            }
			/**
			 * Creazione della barra di eQpending sulla scheda
			 */
			$eq_approv = $this->eQPendingBar();
            if ($eq_approv){
                $html_eq = str_replace("</td>","<br/><p style=\"text-align: center\">$eq_approv</p></td>",$html_eq);
            }

            //$dblock_table_inline = str_replace('"','"',str_replace("\n","",str_replace("\r","",str_replace("    ","",str_replace("\t","",$dblock_table)))));
            $dblock_table_inline = '<div style=\'width: 240px;\'>'.str_replace('"',"'",str_replace("'","\\''",str_replace("\n","",str_replace("\r","",str_replace("    ","",str_replace("\t","",$dblock_table)))))).'</div>';
            //onclick=\"openCloseDBLockTooltip();return false;\"
            //title=\"{$dblock_table_inline}\"
            $dblock_table_small = "<a href=\"#\" id=\"dblockicon\" onclick=\"return false;\" title=\"\" ><i class=\"fa fa-lock\"></i></a>";
            //$dblock_table_small = "<i class=\"fa fa-lock\" data-dblock=\"\" ></i>";
            //echo $dblock_table_inline;
            //sdv
            $sdv_table_inline = '<div style=\'width: 240px;\'>'.str_replace('"',"'",str_replace("'","\\''",str_replace("\n","",str_replace("\r","",str_replace("    ","",str_replace("\t","",$html_SDV)))))).'</div>';
            //$sdv_table_inline = '<div style=\'width: 240px;\'>'.str_replace("\n","",str_replace("\r","",str_replace("    ","",str_replace("\t","",$html_SDV)))).'</div>';
            //eq
            if ($html_eq_inner) {
                $html_eq_inline = '<div style=\'width: 300px;\'>'.str_replace('"', "'", str_replace("'", "\\''", str_replace("\n", "", str_replace("\r", "", str_replace("    ", "", str_replace("\t", "", $html_eq_inner)))))).'</div>';
                $html_eq_small = "<a href=\"#\" id=\"eqicon\" onclick=\"openCloseEQTooltip(); return false;\" title=\"\" ><i class=\"fa fa-comment\"></i></a>";
            }
			$tabella .= "
                                   <!-- Bottoni x operazioni Audit Trail, equery etc. -->
					               	<td class=\"input\" style=\"width: 120px; text-align: right; \">
					               	$html_at_small&nbsp;
					            	$html_eq_small&nbsp;
					            	$html_SDV_small&nbsp;
					            	$dblock_table_small&nbsp;
					            	</td>
					            </tr>
					            <tr class=\"hide\">
					            	$html_at
					            	$html_eq
					            	$html_SDV
					            	$dblock_table
					            </tr>";
		}
		
		$tabella .= "<!--<tr class=\"hide\"></tr>-->
					        </table>
					    </div>
					</div>
				</div>

				<!--<div class=\"alert alert-warning\" style=\"text-align: center; font-size:1.2em;\">$eq_approv</div>-->
			
                ";
        $tabella .= '
            <script type="text/javascript">
                (function( $ ) {
                  $.widget( "custom.tooltipX", $.ui.tooltip, {
                    options: {
                        autoShow: true,
                        autoHide: true
                    },

                    _create: function() {
                      this._super();
                      if(!this.options.autoShow){
                        this._off(this.element, "mouseover focusin");
                      }
                    },

                    _open: function( event, target, content ) {
                      this._superApply(arguments);

                      if(!this.options.autoHide){
                        this._off(target, "mouseleave focusout");
                      }
                    }
                  });
                }( jQuery ) );

                var ttip = false;
                var ttopen = false;
                var tteqopen = false;
                $(function() {
                    //autoShow:true, autoHide:true,
                    //ttopen = false;
                    //ttip = $("#dblockicon").tooltipX({ autoShow:false, autoHide:false, my: "top center", at: "bottom+2 center", html:true, content: function(){ return "'.$dblock_table_inline.'";} });
                    $("#dblockicon").tooltipX({ autoShow:true, autoHide:true, my: "center top", at: "center bottom+2 ", html:true, content: function(){ return "'.$dblock_table_inline.'";} });
                    $("#eqicon").tooltipX({ autoShow:true, autoHide:false, my: "top center", at: "bottom+2 center", html:true, content: function(){ return "'.$html_eq_inline.'";} });
                    //$("#sdvicon").tooltipX({ autoShow:true, autoHide:true, my: "center top", at: "center bottom+2 ", html:true, content: function(){ return "'.$sdv_table_inline.'";} });
                    $("#sdvicon").tooltipX({ autoShow:true, autoHide:false, my: "top center", at: "bottom+2 center", html:true, content: function(){ return "'.$sdv_table_inline.'";} });
                });
                function openCloseDBLockTooltip(){
                    /*
                    if (ttopen){
                        ttip.tooltipX("close");
                        ttopen = false;
                        ttip.tooltipX("option", "disabled", "false");
                        //ttip = $("#dblockicon").tooltipX({ autoShow:false, autoHide:false, my: "top center", at: "bottom+2 center", html:true, content: function(){ return "'.$dblock_table_inline.'";} });
                    }else{
                        ttip.tooltipX("open");
                        ttopen = true;
                    }
                    */
                    //$("#dblockicon").tooltipX(\'open\');
                    //ttip.tooltipX(\'open\');
                }
                function openCloseEQTooltip(){
                    /*
                    if (tteqopen){
                        $("#eqicon").tooltipX("close");
                        tteqopen = false;
                    }else{
                        $("#eqicon").tooltipX("open");
                        tteqopen = true;
                    }
                    */
                    $("#eqicon").tooltipX("close");
                }
            </script>
        ';
		$this->patient_table = $tabella; // ".$this->PatientBar()."
	}
	
	/**
	 * Gestione Nuove eQuery , aggiungere sulle hyperlibs.
	 *
	 * ////////////////////////
	 *
	 * /**
	 * METODI:
	 *
	 *
	 * make_patient_table(): come quello di libreria ma viene aggiunto l'HTML dello specchietto di approvazione eQ per il DM.
	 *
	 * SaveEqInt(): crea l'oggetto realitvo alla form e chiama il SaveEqInt() di integrazioni.inc.
	 *
	 * GenerateEqDM($eq_DM): effettua il salvataggio in DB dell'eQ fatta dal DM, prende i valori dei commenti ai campi fatti dal DM
	 *
	 * ApprovaEqField($eq_int,$eqfield,$d_eqfield): Viene gestita l'approvazione della eQ a livello di campo per il profilo APPROV_ROLE
	 *
	 * function RifiutaEqField($eq_int,$eqfield,$d_eqfield): Viene gestito il rifiuto della eQ a livello di campo da parte del profilo APPROV_ROLE
	 */
	
	/**
	 * SaveEqInt()
	 * Gestisce la generazione di un eQ a livello di campo associando l'identificativo alla singola eQ e popolando il DB.
	 */
	function SaveEqInt() {
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
		$xml = $this->vlist->esams [$_POST ['VISITNUM']] [$_POST ['ESAM']] ['XML'];
		
		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml );
		// $this->integrazione->SaveEqInt($xml_form);
		
		$this->integrazione->SaveEqDE ( $xml_form );
		header ( "location: index.php?exams=visite_exams.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}" );
		die ();
	}
	
	/**
	 * GenerateEqDM($eq_DM)
	 * Gestisce la generazione di un eQ a livello di campo associando l'identificativo alla singola eQ e popolando il DB.
	 * La gestione � unicamente dedicata al caso del profile APPROV_ROLE.
	 */
	function GenerateEqDM($eq_DM) {
		$vals = '';
		$pk = '';
		$vals2 = '';
		$pk2 = '';
		
		/**
		 * Creazione del field statement e dell'array dei field relativi alla form.
		 */
		$form = $this->vlist->esams [$this->session_vars ['VISITNUM']] [$this->session_vars ['ESAM']] ['XML'];
		$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
		$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
		foreach ( $xml_form->fields as $key => $val ) {
			if ($val ['VAR'] != '' && $val ['TB'] != 'no') {
				if (! isset ( $_POST [$val ['VAR']] ) || $_POST [$val ['VAR']] == '')
					$_POST [$val ['VAR']] = 0;
				$field_type = "field_{$val['TYPE']}";
				include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/field.inc";
				// echo $val['VAR'];
				//echo "class_exists ? {$_SERVER['DOCUMENT_ROOT']}/../libs/{$field_type}.inc ? ".file_exists ( $_SERVER['DOCUMENT_ROOT']."/../libs/"$field_type}.inc");
				// if (file_exists("libs/{$field_type}.inc")) include_once "libs/{$field_type}.inc";
				// else include_once "libs/fields/{$field_type}.inc";
				/**
				 * Modifica 08/09/2011
				 * Carico prima i campi modificati per servizio se esistono
				 * M.
				 * Verrocchio
				 */
				if (! class_exists ( $field_type )) {
					if ($this->config_service ['field_lib'] != '' && file_exists ( $this->config_service ['field_lib'] . $field_type . ".inc" )) {
						include_once $this->config_service ['field_lib'] . $field_type . ".inc";
					} elseif (file_exists ( "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc" )) {
						include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/{$field_type}.inc";
					} else {
						include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/fields/{$field_type}.inc";
					}
				}
				$field_obj = new $field_type ( $xml_form, $xml_form->vars [$val ['VAR']], $this->conn, $xml_form->tb_vals, $this->session_vars, $this->service, $xml_form->errors );
				$field_obj->insert_stmt ();
				
				foreach ( $field_obj->field_stmt as $f => $fv ) {
					$fields [] = $fv;
					$fieldsById [$fv] = $field_obj->id;
					$fieldsByField [$field_obj->id] [$fv] = true;
				}
				foreach ( $field_obj->value_stmt as $f => $fv ) {
					$values [] = $fv;
				}
			}
		}
		/**
		 * Fine creazione del field statement e dell'array dei field relativi alla form.
		 */
		
		foreach ( $eq_DM as $k => $v ) {
			$pattern = '/^EQAREA_/';
			// Prendo solo i commenti che si riferiscono ai campi della form, non le variabli hidden come codpat etc..
			// echo preg_match($pattern,$k);
			if ($v != '' && preg_match ( $pattern, $k )) {
				
				// $vals , per la tabella SERVIZIO_EQ, $vals2 , per la tabella SERVIZIO_EQFIELD:
				$sqlseq = new query ( $this->conn );
				$sequence = "select {$this->service}_eqseq.nextval as eq_int from dual";
				$sqlseq->get_row ( $sequence );
				$vals2 ['EQ_INT'] = $vals ['EQUERY_INT'] = $sqlseq->row ['EQ_INT'];
				
				// print_r($this->config_service['PK_SERVICE']);
				$sql = new query ( $this->conn );
				$vals2 [$this->config_service ['PK_SERVICE']] = $vals [$this->config_service ['PK_SERVICE']] = $eq_DM [$this->config_service ['PK_SERVICE']];
				$vals ['USERID_INS'] = $eq_DM ['USERID_INS'];
				$vals ['INS_DT'] = 'sysdate';
				$vals ['STATO'] = '0';
				$vals ['RICH_DM'] = $eq_DM ['EQCOMMENT'];
				
				// print_r($vals);
				$sql->insert ( $vals, $this->service . "_EQ", $pk );
				$this->conn->commit ();
				// echo $eq_DM['TABLE'];
				
				// EQFIELD
				$sql2 = new query ( $this->conn );
				
				// Prendo i valori dalla banca dati della scheda chiusa
				$sql_table = "select * from {$eq_DM['TABLE']} where {$this->config_service['PK_SERVICE']}={$eq_DM[$this->config_service['PK_SERVICE']]} and esam={$eq_DM['ESAM']}
							and visitnum={$eq_DM['VISITNUM']} and progr={$eq_DM['PROGR']} and visitnum_progr={$eq_DM['VISITNUM_PROGR']}
							";
				$sql2 = new query ( $this->conn );
				$sql2->set_sql ( $sql_table );
				$sql2->exec ();
				$sql2->get_row ();
				$table_vals = $sql2->row;
				// print_r($table_vals);
				
				// Prendo tutto $k tranne le prime sette lettere, sarebbe EQAREA_
				// echo substr($k,7);
				$fieldInEqArea = substr ( $k, 7 );
				$fieldId = $fieldsById [$fieldInEqArea];
				//var_dump ( $fieldsByField [$fieldId] );
				$insertedFields = "";
				foreach ( $fieldsByField [$fieldId] as $eqFk => $eqFv ) {
					$vals2 ['ESAM'] = $eq_DM ['ESAM'];
					$vals2 ['VISITNUM'] = $eq_DM ['VISITNUM'];
					$vals2 ['VISITNUM_PROGR'] = $eq_DM ['VISITNUM_PROGR'];
					$vals2 ['PROGR'] = $eq_DM ['PROGR'];
					$vals2 ['FIELD'] = $eqFk;
					$vals2 ['NOTE'] = $v;
					$vals2 ['VALORE'] = $table_vals [substr ( $k, 7 )];
					$vals2 ['STATOFIELD'] = 0;
					$sql2->insert ( $vals2, $this->service . "_EQFIELD", $pk2 );
					$insertedFields [$eqFk] = true;
				}
				if (! isset ( $insertedFields [$fieldId] )) {
					$vals2 ['ESAM'] = $eq_DM ['ESAM'];
					$vals2 ['VISITNUM'] = $eq_DM ['VISITNUM'];
					$vals2 ['VISITNUM_PROGR'] = $eq_DM ['VISITNUM_PROGR'];
					$vals2 ['PROGR'] = $eq_DM ['PROGR'];
					$vals2 ['FIELD'] = $fieldId;
					$vals2 ['NOTE'] = $v;
					$vals2 ['VALORE'] = $table_vals [substr ( $k, 7 )];
					$vals2 ['STATOFIELD'] = 0;
					$sql2->insert ( $vals2, $this->service . "_EQFIELD", $pk2 );
					$insertedFields [$eqFv] = true;
				}
				
				/*
				 * //Gestione delle decodifiche: foreach($fields as $ke=>$va){ $field_pending=substr($k,7); if("D_{$field_pending}"==$va){ //						echo $va; $vals2['FIELD']="D_{$field_pending}"; $vals2['NOTE']=$v; //				echo $table_vals[substr($k,7)]; $vals2['VALORE']=$table_vals[substr($k,7)]; $vals2['STATOFIELD']=0; //				print_r($vals2); $sql2->insert($vals2, $this->service."_EQFIELD",$pk2); } if($field_pending."RC"==$va){ //						echo $va; $vals2['FIELD']=$field_pending."RC"; $vals2['NOTE']=$v; //				echo $table_vals[substr($k,7)]; $vals2['VALORE']=$table_vals[substr($k,7)."RC"]; $vals2['STATOFIELD']=0; //				print_r($vals2); $sql2->insert($vals2, $this->service."_EQFIELD",$pk2); } }
				 */
			}
		}
		$this->conn->commit ();
		if (!isset($eq_DM['REALTIME_EQUERIES'])){
			header ( "location: index.php?exams=visite_exams.xml&{$this->config_service['PK_SERVICE']}={$this->pk_service}&CENTER={$this->session_vars['CENTER']}" );
		}
		else{
			return true;
		}
	}
	
	/**
	 * ApprovaEqField($eq_int,$eqfield,$d_eqfield)
	 * Viene gestita l'approvazione della eQ a livello di campo per il profilo APPROV_ROLE
	 *
	 * @param number $eq_int        	
	 * @param number $eqfield        	
	 * @param string $d_eqfield        	
	 *
	 */
	function ApprovaEqField($eq_int, $eqfield, $d_eqfield,$REALTIME_EQUERIES=null) {
		
		// echo $eq_int;
		// echo $eqfield;
		$sql2 = new query ( $this->conn );
		$pk ['EQ_INT'] = $eq_int;
		$pk ['FIELD'] = $eqfield;
		$values ['STATOFIELD'] = 1;
		$sql2->update ( $values, "{$this->service}_EQFIELD", $pk );
		$this->conn->commit ();
		
		$sql_decfield = "select count(*) as d_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='D_{$eqfield}'";
		//var_dump ( $sql_decfield );
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['D_EQFIELD'] != '') {
			
			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = "D_$eqfield";
			$values ['STATOFIELD'] = 1;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}
		
		$sql_orafield = "select count(*) as ora_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field in ('{$eqfield}_H','{$eqfield}_M')";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_orafield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['ORA_EQFIELD'] != '') {
			$sqlora = new query ( $this->conn );
			$pk2 = array ();
			$values = array ();
			$pk2 ['EQ_INT'] = $eq_int;
			$pk2 ['FIELD'] = $eqfield . "_H";
			$values ['STATOFIELD'] = 1;
			// print_r($values);print_r($this->conn);print_r($this->service);print_r($pk2);
			$sqlora->update ( $values, "{$this->service}_EQFIELD", $pk2 );
			$this->conn->commit ();
			
			$sqlmin = new query ( $this->conn );
			$pk3 ['EQ_INT'] = $eq_int;
			$pk3 ['FIELD'] = $eqfield . "_M";
			$values ['STATOFIELD'] = 1;
			$sqlmin->update ( $values, "{$this->service}_EQFIELD", $pk3 );
			$this->conn->commit ();
		}
		
		$sql_decfield = "select count(*) as date_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='{$eqfield}RC'";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;die();
		if ($sql1->row ['DATE_EQFIELD'] != '') {
			
			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = $eqfield . "RC";
			$values ['STATOFIELD'] = 1;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}
		
		$sql_table = "select count(*) as conto from {$this->service}_EQFIELD where eq_int={$eq_int} and statofield in (0,2)";
		$sql4 = new query ( $this->conn );
		$sql4->set_sql ( $sql_table );
		$sql4->exec ();
		$sql4->get_row ();
		$eq_pending = $sql4->row ['CONTO'];
		// echo $sql_table;
		// echo $eq_pending;
		if ($eq_pending == 0) {
			$sql5 = new query ( $this->conn );
			$pk5 ['EQUERY_INT'] = $eq_int;
			$values5 ['CLOSE_DT'] = 'sysdate';
			$values5 ['STATO'] = 1;
			$sql5->update ( $values5, "{$this->service}_EQ", $pk5 );
			$this->conn->commit ();
			
			// $this->integrazione->ApprovaEq($this->vlist,$this->xml_dir,$this->config_service, $this->session_vars, $this->uploaded_file_dir);
		}
		
		/*
		 * Riapertura della firma elettronica quando si approva una eQuery Verrocchio 05/07/2011 Verri 05/07/2013
		 */
		global $in;
		if ($in ['USER_TIP'] == 'DM') {
			$electronic_signature_esam = array ();
			$visite_exams_path = str_replace ( "index.php", "", $_SERVER ['SCRIPT_FILENAME'] ) . "xml/visite_exams.xml";
			$vlist = new xml_esams_list ( $visite_exams_path, $config, $session_vars, $conn );
			/* Numero dell'esame skip_visit della visita */
			$visit_num = array ();
			foreach ( $vlist->esams as $key => $val ) {
				foreach ( $val as $k => $v ) {
					if ($v ['XML'] == 'esign.xml') {
						$electronic_signature_esam [$key] = $v ['NUMBER'];
					}
				}
			}
			// Per tutte le signature
			foreach ( $electronic_signature_esam as $visit_num => $esam_num ) {
				$query = new query ( $this->conn );
				unset ( $vals );
				$vals ['PK_SERVICE'] = $in [$this->config_service ['PK_SERVICE']];
				$vals ['VISITNUM'] = $visit_num;
				$vals ['ESAM'] = $esam_num;
				$vals ['PROGR'] = $this->session_vars ['PROGR'];
				$vals ['VISITNUM_PROGR'] = $this->session_vars ['VISITNUM_PROGR'];
				$sql_query = "SELECT * FROM {$this->config_service['service']}_COORDINATE WHERE {$this->config_service['PK_SERVICE']}=:PK_SERVICE AND ESAM=:ESAM and VISITNUM=:VISITNUM AND PROGR=:PROGR AND VISITNUM_PROGR=:VISITNUM_PROGR";
				$query->exec ( $sql_query, $vals );
				$query->get_row ();
				if ($query->row ['FINE'] == 1) {
					// Riapro la Electronic Signature
					$query = new query ( $this->conn );
					unset ( $vals );
					$vals ['CENTER'] = $this->session_vars ['CENTER'];
					$vals ['CODPAT'] = $this->session_vars ['CODPAT'];
					$vals ['VISITNUM'] = $visit_num;
					$vals ['ESAM'] = $esam_num;
					$sql_query = "UPDATE {$this->service}_COORDINATE SET FINE='' WHERE SUBSTR(USERID, 0, 3)=:CENTER AND CODPAT=:CODPAT AND VISITNUM=:VISITNUM AND ESAM=:ESAM";
					$query->exec ( $sql_query, $vals );
					
					$query = new query ( $this->conn );
					unset ( $vals );
					$vals ['CENTER'] = $this->session_vars ['CENTER'];
					$vals ['CODPAT'] = $this->session_vars ['CODPAT'];
					$vals ['VISITNUM'] = $visit_num;
					$sql_query = "UPDATE {$this->service}_COORDINATE SET VISITCLOSE='0' WHERE SUBSTR(USERID, 0, 3)=:CENTER AND CODPAT=:CODPAT AND VISITNUM=:VISITNUM";
					$query->exec ( $sql_query, $vals );
				}
			}
		}
        //REDIRECT?
        if (!isset($REALTIME_EQUERIES)){
			header("location: ?CODPAT={$in['CODPAT']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}");
		}
		else{
			return true;
		}
        
	}
	
	/**
	 * RifiutaEqField($eq_int,$eqfield,$d_eqfield)
	 * Viene gestito il rifiuto della eQ a livello di campo da parte del profilo APPROV_ROLE
	 *
	 * @param number $eq_int        	
	 * @param number $eqfield        	
	 * @param string $d_eqfield        	
	 *
	 */
	function RifiutaEqField($eq_int, $eqfield, $d_eqfield) {
		// echo $eq_int;
		// echo $eqfield;
		$sql2 = new query ( $this->conn );
		$pk ['EQ_INT'] = $eq_int;
		$pk ['FIELD'] = $eqfield;
		$values ['STATOFIELD'] = 3;
		$sql2->update ( $values, "{$this->service}_EQFIELD", $pk );
		$this->conn->commit ();
		// echo $d_eqfield;
		
		$sql_decfield = "select count(*) as d_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='D_{$eqfield}'";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['D_EQFIELD'] != '') {
			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = "D_$eqfield";
			$values ['STATOFIELD'] = 3;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}
		
		$sql_orafield = "select count(*) as ora_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field in ('{$eqfield}_H','{$eqfield}_M')";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_orafield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['ORA_EQFIELD'] != '') {
			$sqlora = new query ( $this->conn );
			$pk2 = array ();
			$values = array ();
			$pk2 ['EQ_INT'] = $eq_int;
			$pk2 ['FIELD'] = $eqfield . "_H";
			$values ['STATOFIELD'] = 3;
			// print_r($values);print_r($this->conn);print_r($this->service);print_r($pk2);
			$sqlora->update ( $values, "{$this->service}_EQFIELD", $pk2 );
			$this->conn->commit ();
			
			$sqlmin = new query ( $this->conn );
			$pk3 ['EQ_INT'] = $eq_int;
			$pk3 ['FIELD'] = $eqfield . "_M";
			$values ['STATOFIELD'] = 3;
			$sqlmin->update ( $values, "{$this->service}_EQFIELD", $pk3 );
			$this->conn->commit ();
		}
		
		$sql_decfield = "select count(*) as date_eqfield from {$this->service}_EQFIELD where eq_int={$eq_int} and field='{$eqfield}RC'";
		$sql1 = new query ( $this->conn );
		$sql1->set_sql ( $sql_decfield );
		$sql1->exec ();
		$sql1->get_row ();
		// echo $sql_decfield;
		if ($sql1->row ['DATE_EQFIELD'] != '') {
			$sql3 = new query ( $this->conn );
			$pk ['EQ_INT'] = $eq_int;
			$pk ['FIELD'] = $eqfield . "RC";
			$values ['STATOFIELD'] = 3;
			$sql3->update ( $values, "{$this->service}_EQFIELD", $pk );
			$this->conn->commit ();
		}
		
		$sql_table = "select count(*) as conto from {$this->service}_EQFIELD where eq_int={$eq_int} and statofield in (0,2)";
		$sql4 = new query ( $this->conn );
		$sql4->set_sql ( $sql_table );
		$sql4->exec ();
		$sql4->get_row ();
		$eq_pending = $sql4->row ['CONTO'];
		// echo $sql_table;
		// echo $eq_pending;
		if ($eq_pending == 0) {
			$sql5 = new query ( $this->conn );
			$pk5 ['EQUERY_INT'] = $eq_int;
			$values5 ['CLOSE_DT'] = 'sysdate';
			$values5 ['STATO'] = 1;
			$sql5->update ( $values5, "{$this->service}_EQ", $pk5 );
			$this->conn->commit ();
		}
        //REDIRECT?
        header("location: ?CODPAT={$in['CODPAT']}&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&ESAM={$in['ESAM']}&PROGR={$in['PROGR']}");
	}
	/**
	 * Fine Gestione Nuove eQuery
	 */
	 /**
	 *  vmazzeo 18.06.2015 elimino dallo study.inc.php di lipigen_registry per renderla di libreria (ho eliminato la funzione sia da study_inc di lipigen_registry che di lipigen)
	
	function eQBar($lock_query = 0, $lock_obvious = 0, $small = false) {
		//echo "eQBar (".$lock_query.",".$lock_obvious.")<br/>";
		global $in;
		global $remote_userid;
		global $service;
		$service = $this->service;
		$session_vars = $this->session_vars;
		
		// Se sono un DM e sono abilitato ad approvare faccio comparire casella in più nella barra degli strumenti

		$link_set_eq = mlOut ( "System.patient_table.link_set_eq", "Open eQ" ) ;
		$link_unset_eq = mlOut ( "System.patient_table.link_unset_eq", "Close eQ");
		$link_set_mod = mlOut ( "System.patient_table.link_set_mod", "Open");
		$link_unset_mod = mlOut ( "System.patient_table.link_unset_mod", "Close");
		$link_eq_on = mlOut ( "System.patient_table.link_eq_on", "Data Quality");
		$link_modify_form = mlOut ( "System.patient_table.link_modify_form", "Modify Form");
		$label_eq_not_available="<i class=\"red fa fa-lock\"></i>"; //mlOut ( "System.patient_table.eq_not_available", "Not Available" );
		
		$html_eq = "";
        //if (!$small) {
            $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;" . $link_eq_on . "</div>";
        //}
        $html_eq .="<div style=\"float:right\">{$label_eq_not_available}</div><div style=\"clear:both\">&nbsp;</div>";
        //if (!$small) {
            $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-pencil-square\"></i>&nbsp;$link_modify_form</div>";
        //}
        $html_eq .="<div style=\"float:right\">{$label_eq_not_available}</div>";
		
		$progr_link = "";
		if ($in ['PROGR'] != '') {
			$progr_link = "&PROGR={$in['PROGR']}";
		}

        $link_mod = "";
        $link_eq = "";
        $index = $_SERVER['SCRIPT_NAME']."";
        //die($index);
		
		if (($in ['USER_TIP'] == 'DM' || $in ['USER_TIP'] == 'RO') && $this->config_service ['eQuery'] == '1') {
            //if (isset ( $_GET ['ESAM'] ) && isset ( $_GET ['exams'] ) || isset ( $_GET ['form'] )) {
			if (isset ( $_GET ['ESAM'] ) ) {
				// ABILITA_MOD_DM
				if (isset ( $in ['ABILITA_MOD_DM'] ) && $in ['ABILITA_MOD_DM'] != '') {
					$link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
					<i class=\"fa fa-circle\"></i>&nbsp;".$link_unset_mod."</a>";
				} else {
					$link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_MOD_DM=1\">
					<i class=\"fa fa-circle-o\"></i>&nbsp;".$link_set_mod."</a>";
				}
				// ABILITA_EQ_DM
				if (isset ( $in ['ABILITA_EQ_DM'] ) && $in ['ABILITA_EQ_DM'] != '') {
					$link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
								 <i class=\"fa fa-circle\"></i>&nbsp;$link_unset_eq</a>";
				} else {
					$link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_EQ_DM=1\">
								 <i class=\"fa fa-circle-o\"></i>&nbsp;$link_set_eq</a>";
				}
                // INSERISCO CONTROLLI SE DBLOCK ESISTE PER EQUERY E OBVIOUS CORRECTION
				if (($lock_obvious != 1) || ($lock_query != 1)) {
                    $html_eq = "";  //Importante, sbianco il testo di default perchè ne inserisco interamente di nuovo!
					if ($in ['USER_TIP'] == 'DM') {
							$html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;$link_eq_on</div>";
						if ($lock_query != 1) {
							
							$html_eq .= "<div style=\"float:right\">".$link_eq."</div><div style=\"clear:both\">&nbsp;</div>";
						}
						else{
							$html_eq .= "<div style=\"float:right\">".$label_eq_not_available."</div><div style=\"clear:both\">&nbsp;</div>";
						}
					
							$html_eq .= "<div style=\"float:left\"><i class=\"fa fa-pencil-square\"></i>&nbsp;$link_modify_form</div>";
						if ($lock_obvious != 1) {
							$html_eq .= "<div style=\"float:right\">".$link_mod."</div>";
						}
						else{
							$html_eq .= "<div style=\"float:right\">".$label_eq_not_available."</div><div style=\"clear:both\">&nbsp;</div>";
						}
						
						$html_eq .= "";
					} 					// Caso del CRA
					elseif ($in ['USER_TIP'] == 'RO') {
						if ($lock_query != 1) {
							$html_eq = "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;".$link_eq_on."</div><div style=\"float:right\">".$link_eq."</div>";
						}
					}
					$html_eq .= "";
				}
			}
		}
		
		// Studio con Dm ma senza eQ, il Dm deve comunque poter modificare la form
		if ($in ['USER_TIP'] == 'DM' && ! isset ( $this->config_service ['eQuery'] ) && isset ( $this->session_vars ['ESAM'] )) {
			
			if (isset ( $in ['ABILITA_MOD_DM'] ) && $in ['ABILITA_MOD_DM'] != '') {
				$link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
							  <i class=\"fa fa-circle\"></i>&nbsp;".$link_unset_mod."</a>";
			} else {
				$link_mod .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_MOD_DM=1\">
							  <i class=\"fa fa-circle-o\"></i>&nbsp;".$link_set_mod."</a>";
			}
			if ($lock_obvious != 1) {
				$html_eq = "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;".$link_modify_form."</div>
				<div style=\"float:right\">{$link_mod}</div>";
			}
		}
		// Fine Studio con Dm ma senza eQ, il Dm deve comunque poter modificare la form
		
		// Se sono un DE e sono abilitato a fare eQ faccio comparire casella in più nella barra degli strumenti
	//	echo $in ['USER_TIP'] ."<br/>";
	//	echo $this->config_service ['eQuerySpec'] ['Integrazione'] ['ROLE'] ."<br/>";
	//	echo $this->config_service ['eQuery']."<br/>";
		if ($in ['USER_TIP'] == 'DE' && $this->config_service ['eQuery'] == '1') {
			
			/**
			 * STATI:
			 * stato 0: eQ proposta dal DM al DE
			 * stato 1: eQ fatta dal DE e approvata dal DM
			 * stato 2: eQ fatta dal DE al DM
			 * stato 3: eQ fatta dal DE e rifiutata dal DM
			 * /

			// ABILITA_EQ_DE
			if (isset ( $_GET ['ESAM'] ) && isset ( $_GET ['exams'] ) || isset ( $_GET ['form'] )) {
				if (isset ( $in ['ABILITA_EQ_DE'] ) && $in ['ABILITA_EQ_DE'] != '') {
 					$link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}\">
								<i class=\"fa fa-circle\"></i>&nbsp;$link_unset_eq
								</a>";
				} else { // &REGISTRY={$this->service} levato...
					$link_eq .= "<a href=\"$index?CENTER={$in['CENTER']}&{$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}&ESAM={$in['ESAM']}$progr_link&VISITNUM={$in['VISITNUM']}&VISITNUM_PROGR={$in['VISITNUM_PROGR']}&form={$in['form']}&ABILITA_EQ_DE=1\">
							<i class=\"fa fa-circle-o\"></i>&nbsp;$link_set_eq
							</a>";
				}
			} else {
				$link_eq .= "&nbsp;";
			}
			if ($lock_query != 1) {
                $html_eq = "";
                //if (!$small) {
                    $html_eq .= "<div style=\"float:left\"><i class=\"fa fa-comment\"></i>&nbsp;" . $link_eq_on . "</div>";
                //}
                $html_eq .= "<div style=\"float:right\">{$link_eq}</div>";
			}
		}
		
		return $html_eq;
	}
	*/
	
	/**
	 * Restituisce lo specchiatto relativo ad una eQ pendig sulla scheda.
	 *
	 * @return HTML
	 *
	 */
	function eQPendingBar() {
		// Gestione specchietto dove non c'è eQ pending
        $eq_approv = "";
		if (isset ( $_GET ['ESAM'] ) && isset ( $_GET ['exams'] ) || isset ( $_GET ['form'] )) {
			if ($this->config_service ['eQuery'] == 1) {
				if (isset ( $_GET ['PROGR'] ) && $_GET ['PROGR'] != "") {
					$and_progr = " and eqfield.progr={$_GET ['PROGR']} ";
				}
				if (isset ( $_GET ['VISITNUM_PROGR'] ) && $_GET ['VISITNUM_PROGR'] != "") {
					$and_progr .= " and eqfield.visitnum_progr={$_GET ['VISITNUM_PROGR']} ";
				}
				// non ho l'eq_int, da rivedere:
				$sql_eqint = "select  eqfield.eq_int,eq.stato,eq.rich_dm,eq.rich_de from {$this->service}_eqfield eqfield, {$this->service}_eq eq where
				eqfield.{$this->xmr->configurations['PK_SERVICE']}={$_GET [$this->xmr->configurations['PK_SERVICE']]}
				and eqfield.esam={$_GET ['ESAM']}
				and eqfield.visitnum={$_GET ['VISITNUM']}
				and eq.stato in (0,2)
				and eqfield.eq_int=eq.equery_int
				$and_progr
				";
				$sql2 = new query ( $this->conn );
				$sql2->set_sql ( $sql_eqint );
				$sql2->exec ();
				
				// echo $sql_eqint;
				
				/**
				 * STATI:
				 * stato 0: eQ proposta dal DM al DE
				 * stato 1: eQ fatta dal DE e approvata dal DM
				 * stato 2: eQ fatta dal DE al DM
				 * stato 3: eQ fatta dal DE e rifiutata dal DM
				 */
				while ( $sql2->get_row () ) {
					$this->integrazione->eq_int = $sql2->row ['EQ_INT'];
					$stato = $sql2->row ['STATO'];
					
					if ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' &&  $stato == '2' && ! isset ( $_GET ['ABILITA_MOD_DM'] )) {
						$ret = $this->integrazione->getEqSpec ( $this->vlist );
						$eq_approv = "<span style=\"color: orange;\"><i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>".mlOut("MESSAGE_EQPENDING","Equery pending")."<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i></span>";
					} elseif ($this->integrazione->eq_enabled && $this->integrazione->eq_int != '' && ($stato == '0' || $stato == '2')) {
						$eq_approv = "<span style=\"color: orange;\"><i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i>".mlOut("MESSAGE_EQPENDING","Equery pending")."<i class=\"fa fa-comments\" style=\"font-size:1.2em;\"></i></span>";
					}
				}
			}
		}
		return $eq_approv;
	}
	/*
	 * function MainSubReOpen ( $visitnum, $visitnum_progr, $esam, $progr , $codpat , $center){ //die("TEST"); $xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir ); $xml_form->xml_form_by_file ( $this->xml_dir . '/' . $this->vlist->esams [$_GET ['VISITNUM']] [$_GET ['ESAM']] ['XML'] ); $table = $xml_form->form ['TABLE']; $_POST['ESAM']=$esam; $_POST['PROGR']=$progr; $_POST['VISITNUM']=$visitnum; $_POST['VISITNUM_PROGR']=$visitnum_progr; $_POST['CODPAT']=$codpat; $_POST['CENTER']=$center; $_POST[$xml_form->form ['MAIN_FIELD']]=1; $_POST['D_'.$xml_form->form ['MAIN_FIELD']]="Yes"; $_POST['EQAREADE_'.$xml_form->form ['MAIN_FIELD']]="Main Form, Obvious correction by Investigator "; $this->session_vars[$xml_form->form ['MAIN_FIELD']]=1; $this->integrazione->SaveEqDE($xml_form); $sql_eqfield="select note_de, eq_int, statofield from {$this->service}_eqfield eqfield, {$this->service}_eq eq where eqfield.{$xml_form->config_service['PK_SERVICE']}={$_GET [$xml_form->config_service['PK_SERVICE']]} and eqfield.esam={$_GET ['ESAM']} and eqfield.visitnum={$_GET ['VISITNUM']} and eqfield.visitnum_progr={$_GET ['VISITNUM_PROGR']} and eqfield.progr={$_GET ['PROGR']} and eqfield.FIELD='{$xml_form->form ['MAIN_FIELD']}' and eq.equery_int=eqfield.eq_int and eq.stato=2 "; //			echo $sql_eqfield; $sql2 = new query ( $this->conn ); $sql2->set_sql($sql_eqfield); $sql2->exec(); $sql2->get_row(); $nota_de=$sql2->row['NOTE_DE']; $eq_int=$sql2->row['EQ_INT']; $d_eqfield=""; // Update del valore 1 e Yes nella EQFIELD $sql4=new query($this->conn); $vals4['VALORE']=$xml_form->form ['MAIN_FIELD_VALUE']; $pk4['ESAM']=$esam; $pk4['VISITNUM']=$visitnum; $pk4['VISITNUM_PROGR']=$visitnum_progr; $pk4['PROGR']=$progr; $pk4['CODPAT']=$codpat; $pk4['EQ_INT']=$eq_int; $pk4['FIELD']=$xml_form->form ['MAIN_FIELD']; $sql4->update($vals4, $this->service."_EQFIELD",$pk4); $pk4['FIELD']='D_'.$xml_form->form ['MAIN_FIELD']; $vals4['VALORE']="Yes"; $sql4->update($vals4, $this->service."_EQFIELD",$pk4); $this->conn->commit(); $to_approve="&EQ_INT_FIELD={$eq_int}&EQFIELD={$xml_form->form ['MAIN_FIELD']}&D_EQFIELD={$d_eqfield}&APPROVA_EQFIELD=1"; $redirect="index.php?CENTER=".$center."&CODPAT=".$codpat."&VISITNUM=".$visitnum."&ESAM={$esam}&form={$_GET['form']}{$to_approve}"; //		echo $redirect; // Riapro la main dal FINE=1: $sql3=new query($this->conn); $pk=''; $vals['FINE']=''; $pk['ESAM']=$esam; $pk['VISITNUM']=$visitnum; $pk['VISITNUM_PROGR']=$visitnum_progr; $pk['PROGR']=$progr; $pk['CODPAT']=$codpat; $sql3->update($vals, $this->service."_COORDINATE",$pk); // Riapro le sub dal INV_QUERY=MAINSUBSENT $vals3['INV_QUERY']=''; $pk3['VISITNUM']=$visitnum; $pk3['CODPAT']=$codpat; $pk3['ESAM']=$esam+1; $pk3['VISITNUM_PROGR']=$visitnum_progr; $sql3->update($vals3, $this->service."_COORDINATE",$pk3); //Poi metto fine null se hanno inizio null (caso di primo inserimento) $sql_update = "update {$this->service}_coordinate set fine='' where visitnum={$pk3['VISITNUM']} and esam={$pk3['ESAM']} and visitnum_progr={$pk3['VISITNUM_PROGR']} and {$this->config_service['PK_SERVICE']}={$codpat} and inizio is null "; //	echo $sql_update; $sql3->set_sql ($sql_update ); $sql3->ins_upd (); $this->conn->commit(); header ( "location:$redirect" ); die (); }
	 */
}
?>