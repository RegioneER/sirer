<?php
include_once "db.inc";

/**
 * Classe per la gestione del Double Data Entry
 *
 * @package Hyper
 *
 */

class SDV_module_prototype {
    /**
     * Connessione al DB
     *
     * @var dbconn
     */
    public $conn;
    /**
     * Array di configurazione del servizio XMR
     *
     * @var array
     */
    public $config_service;
    /**
     * Array di variabili di sessione
     *
     * @var array
     */
    public $session_vars;
    /**
     * Identificativo del servizio XMR
     *
     * @var string
     */
    public $service;
    /**
     * Oggetto di descrizione del visit_exams.xml
     *
     * @var object
     */
    public $vlist;
    public $testi;

    public $strategyTable;
    public $strategyStatusTable;
    public $signTable;
    public $xml_dir;

    public $regTable;

    public $cache;

    //static public $strategy;
    //static public $strategyStatus;
    //static public $strategy;
    //static public $strategyStatus;
    /**
     * Costruttore: inizializza l'oggetto e le configurazioni dello stesso
     *
     * @param dbconn $conn
     * @param array $session_vars
     * @param array $config_service
     * @param string $service
     * @param array $vlist
     * @param string $registrationTable
     */
    public function __construct($conn, $session_vars, $config_service, $service, $vlist, $xml_dir) {
        $this -> conn = $conn;
        $this -> config_service = $config_service;
        $this -> service = $service;
        $this -> session_vars = $session_vars;
        $this -> vlist = $vlist;
        $this -> xml_dir = $xml_dir;
        $this -> strategyTable = $this -> service . '_SDV_STRATEGY';
        $this -> strategyStatusTable = $this -> service . '_SDV_STRATEGY_STATUS';
        $this -> signTable = $this -> service . '_SIGNSDV';
        $this -> regTable = $config_service['RegTable'];
        if ($this->config_service['production']!=1) {
            if (!$this->isDBUpdated()) {
                $this->updateDB();
            }
        }
        //print_r($session_vars);
        //echo "<br/>";
        //print_r($config_service);
        $this -> checkVisione();
    }

    /**
     * Verifica che la banca dati abbia le modifiche alla DDL necessarie
     *
     * @return boolean
     */
    function isDBUpdated() {
    	if (isset($_SESSION['SDV_DB_UPDATED'])){
    		return $_SESSION['SDV_DB_UPDATED'];
    	}
        $str = "select count(*) conto from user_tables where table_name='{$this->signTable}'";
        $query_upd = new query($this -> conn);
        $query_upd -> exec($str);
        $query_upd -> get_row();
        if ($query_upd -> row['CONTO'] > 0) {
        	$_SESSION['SDV_DB_UPDATED']=true;
        } else {
        	$_SESSION['SDV_DB_UPDATED']=false;
        }
        return $_SESSION['SDV_DB_UPDATED'];
    }

    /**
     * Effettua le modifiche alla DDL necessarie
     *
     */
    function updateDB() {
		return;
    }

    function reportSDVStrategy($version=1) {
        $conteggio_esam=null;
        $visit_html=null;
        $array_visite = $this -> reportSDVStrategyStep1(1);
        $css = $this -> getCSS();
        //Logger::send('array_visite');
        //Logger::send($array_visite);
        $pbreak = "page-break-before:always;";
        $first = true;
        $tabheader = '<table class="strategyReport" align="center" width="100%" style="[PBREAK] margin: auto; width:100%;" ><tr class="titolo"><th width="10%">VISIT</th><th  width="20%">ESAM</th><th  width="50%">FIELD LABEL ( FIELD VAR ) </th></tr>';
        $html = $css . ''; //.$tabheader;
        //echo ""
        foreach ($array_visite as $visitnum => $curr_visit) {
            $esam_html = '';

            $conteggio_field_per_visit = 0;
            foreach ($curr_visit['ESAM'] as $esam => $curr_esam) {
                $field_html = '';
                $conteggio_field = 0;
                //var_dump($curr_esam['FIELD']);
                //die();
                foreach ($curr_esam['FIELD'] as $field => $curr_field) {
                    if ($curr_field['FLAG']) {
                        // $checkbox = '<i class="fa fa-check-square-o">';
                    } else {
                        $checkbox = '<i class="fa fa-square-o"></i>';
                    }
                    if ($conteggio_field > 0){
                        $field_html .= '<tr>';
                    }
                    //var_dump($curr_field);
                    $testo= str_replace("__EMPTY_STRING__","",$curr_field['TESTO'])." ( ".$curr_field['VAR']." )" ;  //GENHD-296
                    $field_html .= '<td>' . $testo. ' ' . $checkbox . '</td></tr>';  //GENHD-296
                    //Logger::send('incremento di 1');
                    $conteggio_field++;
                }

                if ($curr_esam['FLAG']) {
                    //$checkbox = '<i class="fa fa-check-square-o">';
                } else {
                    $checkbox = '<i class="fa fa-square-o"></i>';
                }
                if ($conteggio_esam > 0) {
                    $esam_html .= '<tr>';
                }
                if ($conteggio_field == 0) {
                    $esam_html .= "<td rowspan='1'>  {$curr_esam['TESTO']} {$checkbox} </td></tr>";
                } else {
                    $esam_html .= "<td rowspan='{$conteggio_field}'> {$curr_esam['TESTO']} {$checkbox} </td>" . $field_html;
                }
                //Logger::send('Aggiungo: ' . $conteggio_field);
                $conteggio_field_per_visit += $conteggio_field;
            }
            if ($curr_visit['FLAG']) {
                //$checkbox = '<i class="fa fa-check-square-o">';
            } else {
                $checkbox = '<i class="fa fa-square-o"></i>';
            }
            //Logger::send('conteggio:' . $conteggio_field_per_visit);
            $pbstr = "";
            if ($first){
            	$first = false;
            }else{
            	$pbstr = $pbreak;
            }
            if ($conteggio_field_per_visit == 0) {
                $visit_html .= "</table>".str_replace("[PBREAK]",$pbstr,$tabheader)."<tr><td rowspan='1'> {$curr_visit['TESTO']} {$checkbox} </td></tr>";
            } else {
                $visit_html .= "</table>".str_replace("[PBREAK]",$pbstr,$tabheader)."<tr><td rowspan='{$conteggio_field_per_visit}'> {$curr_visit['TESTO']} {$checkbox} </td>" . $esam_html;
            }

        }
        $html .= $visit_html . '</table>';
        if (!$_GET['PDF']){
        	$html.='<a href="'.$_SERVER['REQUEST_URI'].'&PDF=true" target="_blank">Click here to generate PDF</a>';
        }else{
        	//Genero PDF, forzo lo scaricamento e muoio!
            $studyPath = substr($_SERVER['REQUEST_URI'],0,strrpos($_SERVER['REQUEST_URI'],"/"));
            global $study_;
        	//Sistemo html con header ecc
        	//$hypercss = file_get_contents("hypernet.css");
        	//$hypercss = str_replace('../imgserv/','http://'.$_SERVER['HTTP_HOST'].'/imgserv/',$hypercss);
            $css=$_SERVER['DOCUMENT_ROOT']."/../libs/xCRF/css/pdfPrint.css";
            //$css1=$_SERVER['DOCUMENT_ROOT']."/assets/css/bootstrap.min.css";
            $html_css="
						<style type=\"text/css\">".file_get_contents($css)."
								</style>
								<body>";


            $html_css=' <link href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/bootstrap.min.css" rel="stylesheet" />
                        <link href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/font-awesome-4.1.css" rel="stylesheet">
                        <link href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/elusive-webfont.css" rel="stylesheet">
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/font-awesome.min.css" />
                        <!--[if IE 7]>
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/font-awesome-ie7.min.css" />
                        <![endif]-->
                        <!-- page specific plugin styles -->
                        <!-- fonts -->
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/openFont.css" />
                        <!-- ace styles -->
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/ace.min.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/ace-rtl.min.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/ace-skins.min.css" />
                        <!-- forms additional css -->
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/jquery-ui-1.10.3.custom.min.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/chosen.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/datepicker.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/bootstrap-timepicker.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/daterangepicker.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/colorpicker.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/flag-icon.min.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/select2.css" />
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/xCRFcss/pdfPrint.css" />
                        <!--[if lte IE 8]>
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/ace-ie.min.css" />
                        <![endif]-->
                        <!-- inline styles related to this page -->
                        <link rel="stylesheet" href="'.$_SERVER["DOCUMENT_ROOT"].'/casAuthn/assets/css/jquery-ui.css" />
                        <link rel="stylesheet" href="modules.css" />
				';

            $before='
        				<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
						<html>
							<head><TITLE>SDV Strategy Report</TITLE></head>
							'.$html_css.'
							<body>
					';
        	$after = '
        					</body>
        				</html>
        			';
        	$html = $before.$html.$after;
        	//die("Aspetta!");
        	$dir = $_SERVER['DOCUMENT_ROOT'].$studyPath."/tmpdocs";
        	if (!is_dir($dir)){
	        	if (!mkdir($dir, 0775, true)) {
				    die('Failed to create temp folder!');
				}
        		exec("chgrp -R devj {$dir}", $retval);
				exec("chmod -R ug+w {$dir}", $retval);
        	}
        	//die($dir);
        	$filename = $dir."/SDV_SR_".date("Ymd_His"); //Random generated?
        	$filenamehtml=$filename.".htm";

			$fp = fopen($filenamehtml, 'w');
			fwrite($fp, $html);
			fclose($fp);

            //Banner and wkhtmltopdf options
            $filename_header=$dir."/header";
            $filenamehtml_header=$filename_header.".htm";
            $marginTop="20";
            if (!file_exists($filenamehtml_header)){
                $banner="http://".$_SERVER['HTTP_HOST'].$studyPath."/images/study-logo.png";
                $html_header='<img src="'.$banner.'" style="height:45px; padding-right:30px;">'.$study_->getStudyTitle();
                $fp = fopen($filenamehtml_header, 'w');
                fwrite($fp, $html_header);
                fclose($fp);
                exec("chgrp devj $filenamehtml_header", $retval);
                exec("chmod ug+w $filenamehtml_header", $retval);
            }
	
			$header_opt="";
			if(file_exists($filenamehtml_header)){
				$header_opt=" --header-html {$filenamehtml_header} ";
			}
			
						
	// 		$html_cover='<table align=\"center\" width=\"100%\"><tr><td><div  style="width:520px;
	// 								padding:50px;
	// 								border:1px solid gray;
	// 								margin:250px;margin-top:500px;text-align:center;font-size: xx-large;"> THIS IS THE COVER </div></td></tr>
	// 								<tr><td></td></tr>
	// 								<table>';
			//$filename_cover=$dir."/cover";
			//$filenamehtml_cover=$filename_cover.".htm";
			//	
			$cover_opt="";
			//if(file_exists($filenamehtml_cover)){
			//	$cover_opt=" --cover {$filenamehtml_cover} ";
			//}
			$filename .= ".pdf"; 
			
			passthru($_SERVER['DOCUMENT_ROOT']."/../libs/xCRF/wkhtmltopdf-amd64 -O landscape --outline {$header_opt} {$cover_opt} -q --ignore-load-errors --header-spacing 5 --margin-top {$marginTop} --footer-right \"[page]/[topage]\" --footer-left \"[section]  [subsection]\" {$filenamehtml} {$filename} ",$retval);
			//print_r($retval);
			exec("chgrp devj $filenamehtml", $retval);
			exec("chmod ug+w $filenamehtml", $retval);
			exec("chgrp devj $filename", $retval);
			exec("chmod ug+w $filename", $retval);
			ob_clean();
			header("Pragma: public");
			header("Expires: 0");
			header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
			header("Content-Type: application/pdf");
			header("Content-Description: File Transfer");
			header("Content-Disposition: attachment; filename=\"".str_replace($dir."/","",$filename)."\"");
			header("Accept-Ranges: bytes");
			header("Content-Length: ".filesize($filename));
			header("Content-Transfer-Encoding: binary");
			//header("Cache-Control: no-cache");
			
			readfile($filename);
			unlink($filenamehtml);
			unlink($filename);
			die();
        }
    	return $html;
    }

    function reportSDVStrategyStep1($version = null, $readOnly = true) {

        if ($version == null)
            $version = $this -> getNewStrategyVersion();
        $strategy = $this -> getStrategy($version);

        foreach ($this->vlist->visitnums as $visitnum => $currVisit) {
            if ($strategy[$visitnum])
                $checked = ' checked="checked" ';
            else
                $checked = '';

            if ($checked) {
                if ($checked) {
                    $visite_array[$visitnum]['FLAG'] = true;
                    $visite_array[$visitnum]['TESTO'] = $currVisit['TEXT'];

                } else {
                    $visite_array[$visitnum]['FLAG'] = false;
                    $visite_array[$visitnum]['TESTO'] = $currVisit['TEXT'];
                }
                $visite_array[$visitnum]['ESAM'] = $this -> reportSDVStrategyStep2($version, $visitnum);
            }
        }

        return $visite_array;
    }

    function reportSDVStrategyStep2($version, $visitnum) {

        if ($version == null)
            $version = $this -> getNewStrategyVersion();
        $strategy = $this -> getStrategy($version);

        $esami_count = 0;
        foreach ($this->vlist->esams[$visitnum] as $esam => $currEsam) {
            if ($currEsam['SUB'] != '')
                continue;
            if ($strategy[$visitnum][$esam]|| ($this -> isMain( $visitnum, $esam) && $strategy[$visitnum][$esam+1]))
                $checked = ' checked="checked" ';
            else
                $checked = '';

            if ($checked) {
                if ($checked) {
                    $esami_array[$esam]['FLAG'] = true;
                    $esami_array[$esam]['TESTO'] = $currEsam['TESTO'];
                } else {
                    $esami_array[$esam]['FLAG'] = false;
                    $esami_array[$esam]['TESTO'] = $currEsam['TESTO'];
                }

                $esami_array[$esam]['FIELD'] = $this -> reportSDVStrategyStep3($version, $visitnum, $esam);
            }
        }

        return $esami_array;
    }

    function reportSDVStrategyStep3($version, $visitnum, $esam) {

        if ($version == null)
            $version = $this -> getNewStrategyVersion();
        $strategy = $this -> getStrategy($version);

        //Logger::send('qui');

        if ($this -> vlist -> esams[$visitnum][$esam]['MAIN'] == '') {
            $xml = new xml_form();
            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam]['XML']);
            $frozen = false;
            //arrivato qui

            foreach ($xml->fields as $currField) {
                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                    if ($strategy[$visitnum][$esam]['FIELDS'][$currField['VAR']])
                        $checked = ' checked="checked" ';
                    else
                        $checked = '';
                    if ($checked) {
                    	//$testo = $currField['TESTO'];
                    	$testo= str_replace("__EMPTY_STRING__","",$currField['TESTO']);
                    	if (preg_match('/checkbox/i', $currField['TYPE'])) {
                            foreach ($currField['VALUE'] as $check => $check_text) {
                                if (trim($check_text) != '')
                                    $testo .= '<br/>[' . $check_text . ']';
                                //$testo .= '<br/><' . $check . '<';
                            }
                        }
                        if (preg_match('/radio/i', $currField['TYPE'])) { //GENHD-296
                        	foreach ($currField['VALUE'] as $check => $check_text) {
                        		if (trim($check_text) != '')
                        			$testo .= '<br/>[' . mlOut($check_text,null). ']';
                        	}
                        }
                        if (!$testo) {
                            $testo = '[' . $currField['VAR'] . ']';
                        }
                        //$testo .= '<br/>VAR: [' . $currField['VAR'] . ']';
                        //$testo .= '<br/>TYPE: [' . $currField['TYPE'] . ']';

                        if (isset($currField['TESTO_SDV']))
                            $testo = $currField['TESTO_SDV'];

                        if ($checked) {
                            $fields_array[$currField['VAR']]['TESTO'] = $testo;
                            $fields_array[$currField['VAR']]['FLAG'] = true;
                            $fields_array[$currField['VAR']]['VAR'] = $currField['VAR'];
                        } else {
                            $fields_array[$currField['VAR']]['TESTO'] = $testo;
                            $fields_array[$currField['VAR']]['FLAG'] = false;
                            $fields_array[$currField['VAR']]['VAR'] = $currField['VAR'];
                        }
                    }
                }
            }

        } else {
        	$fields = array();
            //$xml = new xml_form();
            //$xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam]['XML']);
        	
            $xml = new xml_form();
            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam]['XML']);
            $frozen = false;
            foreach ($xml->fields as $currField) {
                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                    if ($strategy[$visitnum][$esam]['FIELDS'][$currField['VAR']])
                        $checked = ' checked="checked" ';
                    else
                        $checked = '';
                    if ($checked) {
                        //$testo = $currField['TESTO'];
                        $testo= str_replace("__EMPTY_STRING__","",$currField['TESTO']);
                        if (preg_match('/checkbox/i', $currField['TYPE'])) {
                            foreach ($currField['VALUE'] as $check => $check_text) {
                                if (trim($check_text) != '')
                                    $testo .= '<br/>[' . $check_text . ']';
                                //$testo .= '<br/><' . $check . '<';
                            }
                        }
                        if (preg_match('/radio/i', $currField['TYPE'])) { //GENHD-296
                        	foreach ($currField['VALUE'] as $check => $check_text) {
                        		if (trim($check_text) != '')
                        			$testo .= '<br/>[' . mlOut($check_text,null). ']';
                        	}
                        }
                        if (!$testo) {
                            $testo = '[' . $currField['VAR'] . ']';
                        }
                        //$testo .= '<br/>VAR: [' . $currField['VAR'] . ']';
                        //$testo .= '<br/>TYPE: [' . $currField['TYPE'] . ']';

                        if (isset($currField['TESTO_SDV']))
                            $testo = $currField['TESTO_SDV'];

                        if ($checked) {
                            $fields_array[$currField['VAR']]['TESTO'] = $testo;
                            $fields_array[$currField['VAR']]['FLAG'] = true;
                        } else {
                            $fields_array[$currField['VAR']]['TESTO'] = $testo;
                            $fields_array[$currField['VAR']]['FLAG'] = false;
                        }
                    }
                }
            }
            $xml = new xml_form();
            $esam_sub = $esam + 1;
            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam_sub]['XML']);
            foreach ($xml->fields as $currField) {
            	//echo $visitnum."-".$esam_sub.": ".$currField['VAR'];
                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                    if ($strategy[$visitnum][$esam_sub]['FIELDS'][$currField['VAR']])
                        $checked = ' checked="checked" ';
                    else
                        $checked = '';
                    if ($checked) {
                        $testo = $currField['TESTO'];
                        $testo= str_replace("__EMPTY_STRING__","",$currField['TESTO']);
                        if (preg_match('/checkbox/i', $currField['TYPE'])) {
                            foreach ($currField['VALUE'] as $check => $check_text) {
                                if (trim($check_text) != '')
                                    $testo .= '<br/>[' . $check_text . ']';
                                //$testo .= '<br/><' . $check . '<';
                            }
                        }
                        if (preg_match('/radio/i', $currField['TYPE'])) { //GENHD-296
                        	foreach ($currField['VALUE'] as $check => $check_text) {
                        		if (trim($check_text) != '')
                        			$testo .= '<br/>[' . mlOut($check_text,null). ']';
                        	}
                        }
                        if (!$testo) {
                            $testo = '[' . $currField['VAR'] . ']';
                        }
                        //$testo .= '<br/>VAR: [' . $currField['VAR'] . ']';
                        //$testo .= '<br/>TYPE: [' . $currField['TYPE'] . ']';

                        if (isset($currField['TESTO_SDV']))
                            $testo = $currField['TESTO_SDV'];

                        if ($checked) {
                            $fields_array[$currField['VAR']]['TESTO'] = $testo;
                            $fields_array[$currField['VAR']]['FLAG'] = true;
                        } else {
                            $fields_array[$currField['VAR']]['TESTO'] = $testo;
                            $fields_array[$currField['VAR']]['FLAG'] = false;
                        }
                    }

                }
            }

            /*
            foreach ($fields as $f){
                    if ($frozen || $readOnly) {
                        if ($f['CHECKED'])
                            $html .= '<tr><td class="destra">' . $f['TESTO'] . '</td><td class="input"><span class="checkedImage"></span></td></tr>';
                        else
                            $html .= '<tr><td class="destra">' . $f['TESTO'] . '</td><td class="input"><span class="uncheckedImage"></span></td></tr>';
                    } else {
                        $html .= '<tr><td class="destra">' . $f['TESTO'] . '</td><td class="input"><input type="checkbox" ' . $f['CHECKED'] . ' name="'.$f['FORMARRAY'].'[' . $f['VAR'] . ']" value="1" /></td></tr>';
                    }
            }
            */
            
        }

        return $fields_array;
    }

    /**
     * Effettua controllo di accesso alle funzionalità
     *
     */
    function checkVisione() {
        //if ($this->session_vars['USER_PROFILE']!="DE" && $this->session_vars['USER_PROFILE']!="CO_PI")
            return true;
        //else
        //    return false;
    }

    function checkModifica() {
    	//echo $this->session_vars['USER_PROFILE'];
        if ($this->session_vars['USER_PROFILE']=="CRA") //SOLO CRA! // || $this->session_vars['USER_PROFILE']=="DM" || $this->session_vars['USER_PROFILE']=="PM"
            return true;
        else
            return false;
    }

    function checkAmmin() {
        if ($this->session_vars['USER_PROFILE']=="PM" || $this->session_vars['USER_PROFILE']=="PML")
            return true;
        else
            return false;
    }

    function getStrategy($version = 1) {
    	//TODO!!!!!
    	//$this->config_service['production']
    	if (isset($_SESSION['SDV_STRATEGY_OBJECT'][$version])){
    		return $_SESSION['SDV_STRATEGY_OBJECT'][$version];
    	}else{
    		$stretval = array();
    		if (isset($_SESSION['SDV_STRATEGY_OBJECT'])){
                $stretval = $_SESSION['SDV_STRATEGY_OBJECT'];
            }
    		//if (!isset(self::$strategy) || is_array(self::$strategy) || count(self::$strategy) == 0) {
    		$str = 'select * from ' . $this -> strategyTable . ' where version=:version';
            $bind['VERSION'] = $version;
            $query = new query($this -> conn);
            $query -> exec($str, $bind);
            while ($query -> get_row()) {
                //self::$strategy[$version][$query -> row['VISITNUM']][$query -> row['ESAM']][] = $query -> row;
                //self::$strategy[$version][$query -> row['VISITNUM']][$query -> row['ESAM']]['FIELDS'][$query -> row['FIELD']] = $query -> row;
                //self::$strategy[$version]['COMPLETE'][] = $query -> row;
            	$stretval[$version][$query -> row['VISITNUM']][$query -> row['ESAM']][] = $query -> row;
            	$stretval[$version][$query -> row['VISITNUM']][$query -> row['ESAM']]['FIELDS'][$query -> row['FIELD']] = $query -> row;
            	$stretval[$version]['COMPLETE'][] = $query -> row;
            }
            //echo "RELOADSTRAT<hr/>";
        	//}
            $_SESSION['SDV_STRATEGY_OBJECT']=$stretval;
            return $stretval[$version]; //self::$strategy[$version];
    	}
    }

    function getStrategyStatus($filters = null) {
        $where=null;
        if (!$filters['VERSION'])
            $filters['VERSION'] = 1;
        $parsed = $this -> parseFilters($filters);
        if ($parsed['WHERE'])
            $where .= ' where ' . $parsed['WHERE'];
        $bind = $parsed['BIND'];
        $str = 'select * from ' . $this -> strategyStatusTable . $where;
        $query = new query($this -> conn);
        $query -> exec($str, $bind);
        while ($query -> get_row()) {
            $ret_array[] = $query -> row;
        }
        return $ret_array;
    }

    function numFieldsVerified($filters, $mandatoryOnly=false) {
        $parsed = $this -> parseFilters($filters);
        $where = ' where VALID=1 and nvl(signed,0)<>1';
        $tables = $this -> strategyStatusTable;
        if ($mandatoryOnly){
        	$parsed = $this -> parseFilters($filters,"sst.");
        	$tables = $this -> strategyStatusTable." sst, ".$this->strategyTable." st";
        	$where .= " and SST.VISITNUM = ST.VISITNUM and sst.esam = st.esam and SST.FIELD = st.field and sst.version = st.version and st.mandatory = 1 ";
        }
        if ($parsed['WHERE']){
        	$where .= ' and ' . $parsed['WHERE'];
        }
        $bind = $parsed['BIND'];
        $str = 'select count(*) conto from ' .$tables. $where;

        //if ($parsed['WHERE'])
        //    $where .= ' and ' . $parsed['WHERE'];
        //$bind = $parsed['BIND'];
        //$str = 'select count(*) conto from ' . $this -> strategyStatusTable . $where;


        $query = new query($this -> conn);
        $query -> get_row($str, $bind);
        return $query -> row['CONTO'];
    }

    function numFieldsSigned($filters, $mandatoryOnly=false) {
        unset($filters['VALID']);
        $parsed = $this -> parseFilters($filters);
        $where = ' where  nvl(signed,0)=1 ';
        $tables = $this -> strategyStatusTable;
        if ($mandatoryOnly){
        	$parsed = $this -> parseFilters($filters,"sst.");
        	$tables = $this -> strategyStatusTable." sst, ".$this->strategyTable." st";
        	$where .= " and SST.VISITNUM = ST.VISITNUM and sst.esam = st.esam and SST.FIELD = st.field and sst.version = st.version and st.mandatory = 1 ";
        }
        if ($parsed['WHERE']){
        	$where .= ' and ' . $parsed['WHERE'];
        }
        $bind = $parsed['BIND'];
        $str = 'select count(*) conto from ' .$tables. $where;

        //if ($parsed['WHERE'])
        //    $where .= ' and ' . $parsed['WHERE'];
        //$bind = $parsed['BIND'];
        //$str = 'select count(*) conto from ' . $this -> strategyStatusTable . $where;

        $query = new query($this -> conn);
        $query -> get_row($str, $bind);
        return $query -> row['CONTO'];
    }

    function numFieldsVerifiedArray($filters, $mandatoryOnly=false) {
    	$mandatoryNum = ($mandatoryOnly?1:2);
    	if (isset($this->cache['numFieldsVerifiedArray'][$mandatoryNum])){
    		return $this->cache['numFieldsVerifiedArray'][$mandatoryNum];
    	}
    	//Rendo generico
    	unset($filters['VISITNUM']);
    	unset($filters['VISITNUM_PROGR']);
    	unset($filters['ESAM']);
    	$parsed = $this -> parseFilters($filters);
    	$where = ' where VALID=1 and nvl(signed,0)<>1';
    	$tables = $this -> strategyStatusTable;
    	if ($mandatoryOnly){
    		$parsed = $this -> parseFilters($filters,"sst.");
    		$tables = $this -> strategyStatusTable." sst, ".$this->strategyTable." st";
    		$where .= " and SST.VISITNUM = ST.VISITNUM and sst.esam = st.esam and SST.FIELD = st.field and sst.version = st.version and st.mandatory = 1 ";
    	}
    	if ($parsed['WHERE']){
    		$where .= ' and ' . $parsed['WHERE'];
    	}
    	$bind = $parsed['BIND'];
    	$str = 'select * from ' .$tables. $where;

    	//if ($parsed['WHERE'])
    	//    $where .= ' and ' . $parsed['WHERE'];
    	//$bind = $parsed['BIND'];
    	//$str = 'select count(*) conto from ' . $this -> strategyStatusTable . $where;


    	$query = new query($this -> conn);
    	$query -> exec($str,$bind);
    	//ciclo tutte le righe di status
    	$retval=array();
    	while ($query -> get_row()) {
    		if (!isset($retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']])){
    			$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]=0;
    		}
    		$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]++;
    	}
    	$this->cache['numFieldsVerifiedArray'][$mandatoryNum]=$retval;
    	return $retval;
    }

    function numFieldsSignedArray($filters, $mandatoryOnly=false) {
    	$mandatoryNum = ($mandatoryOnly?1:2);
    	//var_dump($this->cache);
    	if (isset($this->cache['numFieldsSignedArray'][$mandatoryNum])){
    		//echo "<hr/><hr/>CACHED<hr/>";
    		return $this->cache['numFieldsSignedArray'][$mandatoryNum];
    	}//else{
    	//	echo "<hr/><hr/>NOT CACHED<hr/>";
    	//	var_dump($this->cache['numFieldsSignedArray'][$mandatoryNum]);
    	//}

    	unset($filters['VALID']);
    	//Rendo generico
    	unset($filters['VISITNUM']);
    	unset($filters['VISITNUM_PROGR']);
    	unset($filters['ESAM']);
    	$parsed = $this -> parseFilters($filters);
    	$where = ' where  nvl(signed,0)=1 ';
    	$tables = $this -> strategyStatusTable;
    	if ($mandatoryOnly){
    		$parsed = $this -> parseFilters($filters,"sst.");
    		$tables = $this -> strategyStatusTable." sst, ".$this->strategyTable." st";
    		$where .= " and SST.VISITNUM = ST.VISITNUM and sst.esam = st.esam and SST.FIELD = st.field and sst.version = st.version and st.mandatory = 1 ";
    	}
    	if ($parsed['WHERE']){
    		$where .= ' and ' . $parsed['WHERE'];
    	}
    	$bind = $parsed['BIND'];
    	$str = 'select * from ' .$tables. $where;

    	//if ($parsed['WHERE'])
    	//    $where .= ' and ' . $parsed['WHERE'];
    	//$bind = $parsed['BIND'];
    	//$str = 'select count(*) conto from ' . $this -> strategyStatusTable . $where;

    	$query = new query($this -> conn);
    	$query -> exec($str,$bind);
    	//ciclo tutte le righe di status
    	$retval=array();
    	while ($query -> get_row()) {
    		if (!isset($retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']])){
    			$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]=0;
    		}
    		$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]++;
    	}
    	$this->cache['numFieldsSignedArray'][$mandatoryNum]= $retval;
    	//var_dump($this->cache['numFieldsSignedArray'][$mandatoryNum]);
    	//echo "<hr/><hr/>";
    	return $retval;
    }

    function totStrategyFieldsSDV($filters, $mandatoryOnly=false) {
    	unset($filters['DATE_VALIDATION']);
    	unset($filters['VALID']);
    	unset($filters['SIGNED']);
    	unset($filters['CODPAT']);
    	unset($filters['VISITNUM_PROGR']);
    	unset($filters['PROGR']);
    	$parsed = $this -> parseFilters($filters);
    	$where="";
    	$tables = $this -> strategyTable;
    	if ($mandatoryOnly){
    		$where .= " where ";
    		$where .= " mandatory = 1 ";
    	}
    	if ($parsed['WHERE']){
    		if ($where){
    			$where.=" and ";
    		}else{
    			$where.=" where ";
    		}
    		$where .= ' ' . $parsed['WHERE'];
    	}
    	$bind = $parsed['BIND'];

    	$str = 'select count(*) conto from ' .$tables. $where;
    	$query = new query($this -> conn);
    	$query -> get_row($str, $bind);
    	return $query -> row['CONTO'];
    }

    function totStrategyFieldsSDVArray($filters, $mandatoryOnly=false) {
    	$mandatoryNum = ($mandatoryOnly?1:2);
    	if (isset($this->cache['totStrategyFieldsSDVArray'][$mandatoryNum])){
    		return $this->cache['totStrategyFieldsSDVArray'][$mandatoryNum];
    	}
    	unset($filters['DATE_VALIDATION']);
    	unset($filters['VALID']);
    	unset($filters['SIGNED']);
    	unset($filters['CODPAT']);
    	unset($filters['VISITNUM_PROGR']);
    	unset($filters['PROGR']);
    	//Rendo generico
    	unset($filters['VISITNUM']);
    	unset($filters['VISITNUM_PROGR']);
    	unset($filters['ESAM']);
    	$parsed = $this -> parseFilters($filters);
    	$where="";
    	$tables = $this -> strategyTable;
    	if ($mandatoryOnly){
    		$where .= " where ";
    		$where .= " mandatory = 1 ";
    	}
    	if ($parsed['WHERE']){
    		if ($where){
    			$where.=" and ";
    		}else{
    			$where.=" where ";
    		}
    		$where .= ' ' . $parsed['WHERE'];
    	}
    	$bind = $parsed['BIND'];

    	$str = 'select * from ' .$tables. $where;
    	$retval = array();
    	$query = new query($this -> conn);
    	//$query -> get_row($str, $bind);
    	$query -> exec($str,$bind);
    	//ciclo tutte le righe di status
    	while ($query -> get_row()) {
    		if (!isset($retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']])){
    			$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]=0;
    		}
    		$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]++;
    	}
    	$this->cache['totStrategyFieldsSDVArray'][$mandatoryNum]=$retval;
    	return $retval;
    }

    function totFieldsSDVArray($filters, $mandatoryOnly=false) {
    	$mandatoryNum = ($mandatoryOnly?1:2);
    	if (isset($this->cache['totFieldsSDVArray'][$mandatoryNum])){
    		return $this->cache['totFieldsSDVArray'][$mandatoryNum];
    	}
        //unset($filters['VISITNUM_PROGR']);
        //unset($filters['PROGR']);
        //unset($filters[$this->config_service['PK_SERVICE']]);
        unset($filters['DATE_VALIDATION']);
        unset($filters['VALID']);
        unset($filters['SIGNED']);
        //Rendo generico
        unset($filters['VISITNUM']);
        unset($filters['VISITNUM_PROGR']);
        unset($filters['ESAM']);
        $parsed = $this -> parseFilters($filters);
        $where="";
        $tables = $this -> strategyStatusTable;
        if ($mandatoryOnly){
        	$parsed = $this -> parseFilters($filters,"sst.");
        	$tables = $this -> strategyStatusTable." sst, ".$this->strategyTable." st";

        	$where .= " where ";
        	$where .= " SST.VISITNUM = ST.VISITNUM and sst.esam = st.esam and SST.FIELD = st.field and sst.version = st.version and st.mandatory = 1 ";
        }
        if ($parsed['WHERE']){
        	if ($where){
        		$where.=" and ";
        	}else{
        		$where.=" where ";
        	}
            $where .= ' ' . $parsed['WHERE'];
        }
        $bind = $parsed['BIND'];

        $str = 'select * from ' .$tables. $where;
        //echo "<hr/>$str<hr/>";
        //echo "<pre>";
        //print_r($bind);
        //echo "</pre>";
        $retval = array();
        $query = new query($this -> conn);
        //$query -> get_row($str, $bind);
        $query -> exec($str,$bind);
        //ciclo tutte le righe di status
        while ($query -> get_row()) {
        	if (!isset($retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']])){
        		$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]=0;
        	}
        	$retval[$query->row['VISITNUM']][$query->row['VISITNUM_PROGR']][$query->row['ESAM']]++;
        }
        $this->cache['totFieldsSDVArray'][$mandatoryNum]=$retval;
        return $retval;
    }

    function totFieldsSDV($filters, $mandatoryOnly=false) {
    	//unset($filters['VISITNUM_PROGR']);
    	//unset($filters['PROGR']);
    	//unset($filters[$this->config_service['PK_SERVICE']]);
    	unset($filters['DATE_VALIDATION']);
    	unset($filters['VALID']);
    	unset($filters['SIGNED']);
    	$parsed = $this -> parseFilters($filters);
    	$where="";
    	$tables = $this -> strategyStatusTable;
    	if ($mandatoryOnly){
    		$parsed = $this -> parseFilters($filters,"sst.");
    		$tables = $this -> strategyStatusTable." sst, ".$this->strategyTable." st";

    		$where .= " where ";
    		$where .= " SST.VISITNUM = ST.VISITNUM and sst.esam = st.esam and SST.FIELD = st.field and sst.version = st.version and st.mandatory = 1 ";
    	}
    	if ($parsed['WHERE']){
    		if ($where){
    			$where.=" and ";
    		}else{
    			$where.=" where ";
    		}
    		$where .= ' ' . $parsed['WHERE'];
    	}
    	$bind = $parsed['BIND'];

    	$str = 'select count(*) conto from ' .$tables. $where;
    	//echo "<hr/>$str<hr/>";
    	//echo "<pre>";
    	//print_r($bind);
    	//echo "</pre>";
    	$query = new query($this -> conn);
    	$query -> get_row($str, $bind);
    	return $query -> row['CONTO'];
    }

    function oldTotFieldsSDV($filters) {
        $where=null;
        unset($filters['VISITNUM_PROGR']);
        unset($filters['PROGR']);
        unset($filters[$this -> config_service['PK_SERVICE']]);
        unset($filters['DATE_VALIDATION']);
        unset($filters['VALID']);
        $parsed = $this -> parseFilters($filters);
        if ($parsed['WHERE'])
            $where .= ' where ' . $parsed['WHERE'];
        $bind = $parsed['BIND'];
        $str = 'select count(*) conto from ' . $this -> strategyTable . $where;
        $query = new query($this -> conn);
        $query -> get_row($str, $bind);
        return $query -> row['CONTO'];
    }

    function parseFilters($filters, $addTabPrefix="") {
        if (!$filters['VERSION'])
            $bind['VERSION'] = 1;
        $where = '';

        foreach ($filters as $currFilter => $currValue) {
            if ($where != '')
                $where .= ' and ';
            if ($currFilter == 'DATE_VALIDATION') {
            	$where .= $addTabPrefix.$currFilter . ' ' . $currValue;
            } else {
            	$where .= $addTabPrefix.$currFilter . '=:' . $currFilter;
                $bind[$currFilter] = $currValue;
            }
        }
        return array("WHERE" => $where, "BIND" => $bind);
    }

    function before_print_esams($es_val, $es_progr = 1, $vprogr = 0) {
    	$version = $this -> getLastStrategyVersion();
    	$visita = $es_val['VISITNUM'];
    	$esame = $es_val['ESAM'];
    	if (!$this -> isVersionFrozen($version)) {
    		return;
    	}
    	$html = "";
    	$tot = 0;
    	$done = 0;
    	$signed = 0;
    	$verified = 0;
    	$mtot = 0;
    	$mdone = 0;
    	$msigned = 0;
    	$mverified = 0;
    	$mtotdefined = 0;
    	$filters = array();
    	if ($this -> checkVisione()) {
    		$strategy = $this -> getStrategy(1);
    		//echo "VADO QUA?";
    		if ($strategy[$visita][$esame] || ($this -> isMain( $visita, $esame) && $strategy[$visita][$esame+1])) {
    			$filters['VISITNUM'] = $visita = $es_val['VISITNUM'];
    			$filters['ESAM'] = $esame = $es_val['ESAM'];
    			$filters['VALID'] = 1;
    			$filters['VERSION'] = 1;
    			$mtotdefinedArray = $this->totStrategyFieldsSDVArray($filters,true);
    			$mtotdefined = $mtotdefinedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    			if ($this -> isMain($visita, $esame)) {
    				$sub = $this -> getSub($visita, $esame);
    				$str_sub = "select count(*) conto from {$this->service}_coordinate where esam=:esam and visitnum=:visitnum and {$this -> config_service['PK_SERVICE']}=:pk_service";
    				$bind_sub['PK_SERVICE'] = $es_val['PK_SERVICE'];
    				$bind_sub['ESAM'] = $sub;
    				$bind_sub['VISITNUM'] = $es_val['VISITNUM'];
    				$query_sub = new query($this -> conn);
    				$query_sub -> get_row($str_sub, $bind_sub);
    				if ($query_sub -> row['CONTO'] > 0)
    					$there_are_sub = true;
    					else
    						$there_are_sub = false;
    			}
    			//TODO: Caricare i dati qui per tutte le visite/esami e poi fare i conteggi internamente.
    			$filters[$this -> config_service['PK_SERVICE']] = $es_val['PK_SERVICE'];
    			$filters['VISITNUM_PROGR'] = $vprogr;
    			//var_dump($filters);
    			//$filters['ESAM'] = $esame = $es_val['ESAM'];
    			$totArray = $this -> totFieldsSDVArray($filters, false);
    			$signedArray = $this -> numFieldsSignedArray($filters, false);
    			$verifiedArray = $this -> numFieldsVerifiedArray($filters, false);
    			$mtotArray = $this -> totFieldsSDVArray($filters, true);
    			$msignedArray = $this -> numFieldsSignedArray($filters, true);
    			$mverifiedArray = $this -> numFieldsVerifiedArray($filters, true);
    			//die("OK");
    			if ($es_val['FINE'] == '1' || ($this -> isMain($visita, $esame) && $there_are_sub)) {
    				//echo "VADO QUA2?";
    				//$filters[$this -> config_service['PK_SERVICE']] = $this -> session_vars[$this -> config_service['PK_SERVICE']];
    				if ($es_val['FINE'] == '1') {
    					//$tot_OLD = $this -> totFieldsSDV($filters, false);
    					//$signed_OLD= $this -> numFieldsSigned($filters, false);
    					//$verified_OLD= $this -> numFieldsVerified($filters, false);
    					//$mtot_OLD= $this -> totFieldsSDV($filters, true);
    					//$msigned_OLD= $this -> numFieldsSigned($filters, true);
    					//$mverified_OLD= $this -> numFieldsVerified($filters, true);
    					$tot = $totArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$signed = $signedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$verified = $verifiedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$mtot = $mtotArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$msigned = $msignedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$mverified = $mverifiedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					/*
    					if ($tot_OLD != $tot || $signed_OLD != $signed || $verified_OLD != $verified
    							|| $mtot_OLD != $mtot || $msigned_OLD != $msigned || $mverified_OLD != $mverified){
    						var_dump($filters);
    						var_dump($totArray);
    						var_dump($signedArray);
    						var_dump($verifiedArray);
    						var_dump($mtotArray);
    						var_dump($msignedArray);
    						var_dump($mverifiedArray);
    						echo "<hr/>";
    						echo "<p>TOT</p>";
    						var_dump($tot_OLD);
    						var_dump($tot);
    						echo "<hr/>";
    						echo "<p>SIGNED</p>";
    						var_dump($signed_OLD);
    						var_dump($signed);
    						echo "<hr/>";
    						echo "<p>VERIF</p>";
    						var_dump($verified_OLD);
    						var_dump($verified);
    						echo "<hr/>";
    						echo "<p>MAND TOT</p>";
    						var_dump($mtot_OLD);
    						var_dump($mtot);
    						echo "<hr/>";
    						echo "<p>MAND SIGNED</p>";
    						var_dump($msigned_OLD);
    						var_dump($msigned);
    						echo "<hr/>";
    						echo "<p>MAND VERIF</p>";
    						var_dump($mverified_OLD);
    						var_dump($mverified);
    						die("PROBLEMA! ");
    					}
    					Logger::send('fine=1');
    					Logger::send('esam='.$esame);
    					Logger::send('tot:' . $tot);
    					Logger::send('signed:' . $signed);
    					Logger::send('verified:' . $verified);
    					Logger::send($filters);
    					*/
    				} else {
    					$tot = 1;
    					$signed = 0;
    					$verified = 0;
    				}
    				if ($this -> isMain($visita, $esame)) {
    					/*Logger::send('main');
    					 Logger::send('tot:' . $tot);
    					 Logger::send('signed:' . $signed);
    					 Logger::send('verified:' . $verified);
    					 Logger::send($filters);*/
    					$filters['ESAM'] = $this -> getSub($visita, $esame);
    					unset($filters['PROGR']);
    					//$tot_sub_OLD = $this -> totFieldsSDV($filters, false);
    					//$signed_sub_OLD = $this -> numFieldsSigned($filters, false);
    					//$verified_sub_OLD = $this -> numFieldsVerified($filters, false);
    					//$mtot_sub_OLD = $this -> totFieldsSDV($filters, true);
    					//$msigned_sub_OLD = $this -> numFieldsSigned($filters, true);
    					//$mverified_sub_OLD = $this -> numFieldsVerified($filters, true);
    					$tot_sub= $totArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$signed_sub= $signedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$verified_sub= $verifiedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$mtot_sub= $mtotArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$msigned_sub= $msignedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					$mverified_sub= $mverifiedArray[$filters['VISITNUM']][$filters['VISITNUM_PROGR']][$filters['ESAM']]+0;
    					/*Logger::send('sub');
    					 Logger::send('tot:' . $tot_sub);
    					 Logger::send('signed:' . $signed_sub);
    					 Logger::send('verified:' . $verified_sub);
    					 Logger::send($filters);*/

    					$tot += $tot_sub;
    					$signed += $signed_sub;
    					$verified += $verified_sub;
    					$mtot += $mtot_sub;
    					$msigned += $msigned_sub;
    					$mverified += $mverified_sub;
    					/*Logger::send('main/sub');
    					 Logger::send('tot:' . $tot);
    					 Logger::send('signed:' . $signed);
    					 Logger::send('verified:' . $verified);
    					 Logger::send($filters);*/
    				}
    				$done = $signed + $verified;
    				$mdone = $msigned + $mverified;
    				//echo "<br/>T: {$tot}, D: {$done}<br/>";
    				/*
    				 //FIX PER CAMPI OBBLIGATORI (potrei avere una form dove non ho alcun campo obbligatorio
    				 if ($tot==0 && $done==0){
    				 $tot=1;
    				 }
    				 if ($tot==0 && $done>0){
    				 $tot = $done;
    				 }
    				 //FINE FIX PER CAMPI OBBLIGATORI
    				 */
    				//Nuova logica di colorazione
    				//Se esiste almeno un campo obbligatorio, aggiungo un ! all'icona
    				//Se non ho fatto nulla, sempre bianco.
    				//Se ho fatto qualcosa o se non ho fatto tutti i campi obbligatori, icona gialla
    				//Se ho fatto tutta la form o se ho fatto tutti i campi obbligatori, icona verde

    				if ( $tot == $done || ($mtot>0 && $mtot == $mdone) ) {
    					$html = '<i class="fa fa-search" style="font-size:1.2em; color:green; " title="SDV completed"></i>'; //' <img src="images/SDV_green.png" /> ';
    				} else if ($done > 0) {
    					//echo "STEP2<br/>";
    					$html = '<i class="fa fa-search" style="font-size:1.2em; color:orange; " title="SDV started"></i>'; //' <img src="images/SDV_orange.png" /> ';
    				} else {
    					//echo "STEP3<br/>";
    					$html = '<i class="fa fa-search" style="font-size:1.2em; color:white; " title="SDV empty"></i>'; //' <img src="images/SDV_white.png" /> ';
    				}

    				//Eventualmente mettere qua il punto esclamativo dell'obbligatorietà? (Cmq ho SDV solo se ho la form).

    				//echo "SETTED INNER HTML: <pre>{$html}</pre>";
    				//debug_print_backtrace();
    			} else {
    				$html = '<i class="fa fa-search" style="font-size:1.2em; color:grey; " title="SDV empty"></i>'; //#F3F3F3 //' <img src="images/SDV_white.png" /> ';
    			}
    		}
    		//Comunque il totale viene calcolato solo se la form è chiusa (inviata). --> Eventualmente può stare sopra?
    		//Adesso il punto esclamativo compare solo a form inviata, altrimenti solo lente.
    		if ($mtotdefined>0){
    			$html .= '&nbsp;<i class="fa fa-exclamation" style="font-size:1.2em; color:#DD5A43; " title="SDV mandatory"></i>';
    		}
    		//$html="<pre>{$html}\n [{$there_are_sub}] V: {$tot} - {$done} - {$signed} - {$verified} </pre>";
    		return $html;
    	}
    }

    function isFieldInStrategy($visitnum, $esam, $field, $version = 1) {
        $strategy = $this -> getStrategy($version);
        Logger::send('strategia');
        Logger::trace('look');
        //Logger::send($strategy);
        if (isset($strategy[$visitnum][$esam]['FIELDS'][$field])) {
            return true;
        } else {
            return false;
        }
    }
    function isFieldInStrategyCached($strategy, $visitnum, $esam, $field, $version = 1) {
    	//$strategy = $this -> getStrategy($version);
    	Logger::send('strategia');
    	Logger::trace('look');
    	//Logger::send($strategy);
    	if (isset($strategy[$visitnum][$esam]['FIELDS'][$field])) {
    		return true;
    	} else {
    		return false;
    	}
    }

    function isMainSub($visita, $esame) {
        if ($this -> isMain($visita, $esame) || $this -> isSub($visita, $esame))
            return true;
        else
            return false;
    }

    function isMain($visita, $esame) {
        return ($this -> vlist -> esams[$visita][$esame]['MAIN'] != '');
    }

    function isSub($visita, $esame) {
        return ($this -> vlist -> esams[$visita][$esame]['SUB'] != '');
    }

    function getMain($visita, $esame) {
        if ($this -> isMainSub($visita, $esame)) {
            if ($this -> isMain($visita, $esame))
                return $esame;
            else if ($this -> isSub($visita, $esame))
                return $esame - 1;
        }
        return;
    }

    function getSub($visita, $esame) {
        if ($this -> isMainSub($visita, $esame)) {
            if ($this -> isMain($visita, $esame))
                return $esame + 1;
            else if ($this -> isSub($visita, $esame))
                return $esame;
        }
        return;
    }

    function getCSS($area = 'defineStrategy') {
        switch($area) {
            case 'defineStrategy' :
                $css = '<style>
		.strategyDefinition, .strategyReport{
			#border:solid 1px #082A44;
			#border-collapse: collapse;
			#
		}
        .strategyReport, .strategyReport td{
            border:solid 1px #082A44;
            border-collapse: collapse;
            vertical-align:text-top;
            #border-spacing: 0;
        }
		.strategyDefinition th,.strategyReport th {
			#background-color:#439CE3;
			#color:white;
			padding:5px;
			#font-weight:bold;
			font-size:1.1em;
			#border:solid 1px #082A44;
			
		}
		
		.strategyDefinition a,.strategyReport a {
			#color:#082A44;
			width:100%;
			display:block;
			text-decoration:underline;
			
			font-size:1.5em;
			
			
		}
		.strategyDefinition th a,.strategyReport th a{
		 	color:white;
		 	font-size:1em;
		 	display:inline;
		}
		
		.strategyDefinition tr:hover td {
   			background: none repeat scroll 0 0 #98CFF9;
    		color: #333399;
		}
        
		
        
        /*
		.checkedImage {
			background-image:url("images/checkedcheck.gif");
			display:block;
			width:16px;
			height:15px;
		}
		.uncheckedImage {
			background-image:url("images/uncheckedcheck.gif");
			display:block;
			width:16px;
			height:15px;
		}
		*/
		body{
			font-size: 100%;
		}
		td.input{
		    padding-left: 10px;
		    padding-right: 10px;
		}
		</style>';
                break;
            case 'form' :
                $css = '<style>
                /*
				.checkedImage {
					background-image:url("images/checkedcheck.gif");
					display:inline-block;
					width:16px;
					height:15px;
					margin-top:2px;
				}
				.uncheckedImage {
					background-image:url("images/uncheckedcheck.gif");
					display:inline-block;
					width:16px;
					height:15px;
					margin-top:2px;
				}
				*/
				.spanSDV, .spanRPV {
					display:inline-block;
					background-color:white;
					border:solid 1px #082A44;
					padding:5px;
					height:auto;
				}
				.spanSDV{
					margin-left:6px;
					padding-top:8px;
				}
				.labelSDV{
					display:inline-block;
					background-color:#439CE3;
					border:solid 1px #082A44;
					padding:2px;
					color:white;
					font-weight:bold;
				}
				.labelRPV, .toggleRPV{
					display:inline-block;
					background-color:#E33C33;
					border:solid 1px #082A44;
					padding:2px;
					color:white;
					font-weight:bold;
					margin-top:7px;
				}
				.toggleRPV{
					cursor:pointer;
				}
				.textSDV, .textRPV,.spanSDV {
					vertical-align:top;
				}
				.labelRPV , .toggleRPV ,.spanRPV {
					vertical-align:middle;
				}
				.textSDV, .textRPV{
					display:inline-block;
					background-color:#ECF2AB;
					border:solid 1px #9FAD0A;
					padding:2px;
					padding-left:5px;
					padding-right:5px;
					margin-top:7px;
					font-weight:bold;
				}
				</style>';
                break;
        }

        return $css;
    }

    function after_query_tb_foreach($form, $field_obj) {
    	global $study_;
    	global $in;
    	$xml_dir = $study_->xml_dir; //"xml";
    	$visit_structure_xml = "visite_exams.xml";
		$this->vlist = new xml_esams_list ( $xml_dir . '/' . $visit_structure_xml, $this->config_service, $this->session_vars, $this->conn );
    	$version = $this -> getLastStrategyVersion();
        if (!$this -> isVersionFrozen($version)) {
            return;
        }
        $strategy = $this -> getStrategy($version);
        //Logger::send("AFTERQUERY: INVIOCO=".$this -> session_vars['INVIOCO']);
        //echo $this -> session_vars['INVIOCO']."\n";
        //echo $this -> session_vars['VISITNUM']."\n";
        //echo $this -> session_vars['ESAM']."\n";
        //echo $this->isMain($this -> session_vars['VISITNUM'], $this -> session_vars['ESAM'])."\n";
        //echo $this -> vlist -> esams[$this -> session_vars['VISITNUM']][$this -> session_vars['ESAM']]['MAIN']."\n";
        //print_r($this -> vlist -> esams);
        if ($this -> session_vars['INVIOCO'] == '1' || $this->isMain($this -> session_vars['VISITNUM'], $this -> session_vars['ESAM'])) {
            if (strtolower($this -> session_vars[$this->config_service['PK_SERVICE']])=='next'){
                $this -> session_vars[$this->config_service['PK_SERVICE']]=$in[$this->config_service['PK_SERVICE']];
            }
            //debug_print_backtrace();
        	$field_obj -> make_open_html();
            //if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' && ($field_obj -> attributes['CONDITION'] == '' || $field_obj -> condition_passed) && $this -> isFieldInStrategy($this -> session_vars['VISITNUM'], $this -> session_vars['ESAM'], $field_obj -> attributes['VAR'])) {
            //Logger::send("AFTERQUERY: ".$field_obj -> attributes['VAR']);
            //AUTOMATISMO DI FILTRO SUI CAMPI - NON CONSIDERO LA CONDIZIONE (PIERHD-91 27/09/2012)
        	if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' && $this -> isFieldInStrategyCached($strategy, $this -> session_vars['VISITNUM'], $this -> session_vars['ESAM'], $field_obj -> attributes['VAR'])) {
            	//SE HO OBVIOUS CORRECTION (ID_QUERY == -2), ALLORA CONTROLLO IL VALORE PRECEDENTE, ALTRIMENTI VADO CON L'APERTURA STANDARD SDV //PIERHD-2209
            	if ($this -> session_vars['ID_QUERY']==-2){
            		//Confronto il valore precedente, nel caso riapro sdv
					$query_old_value="select * from {$form->form['TABLE']} where
										ESAM={$this->session_vars['ESAM']}
										and VISITNUM={$this->session_vars['VISITNUM']}
										and VISITNUM_PROGR={$this->session_vars['VISITNUM_PROGR']}
										and PROGR={$this->session_vars['PROGR']}
										and {$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}
										";
					$sql3=new query($this->conn);
					$sql3->exec($query_old_value);
					$sql3->get_row();
					$code = $field_obj->attributes['VAR'];
					$decode = "D_".$field_obj->attributes['VAR'];
					$old_value=$sql3->row[$code];
					$d_old_value=$sql3->row[$decode];
            		$new_value = $this->session_vars[$field_obj->attributes['VAR']];
            		if ($field_obj -> attributes['TYPE'] == 'data_hyper'
            		|| $field_obj -> attributes['TYPE'] == 'date_hyper'
            		|| $field_obj -> attributes['TYPE'] == 'data'
            		|| ($this->session_vars[$code.'D'] && $this->session_vars[$code.'M'] && $this->session_vars[$code.'Y']) ){
            			//print_r($this->session_vars);
            			$new_value = $this->session_vars[$code.'D'].$this->session_vars[$code.'M'].$this->session_vars[$code.'Y'];
            			//echo "<br/>OLD: $old_value, NEW: {$new_value}<br/>";
            		}
            		if ($field_obj -> attributes['TYPE'] == 'ora_hyper'){
            			$new_value = $this->session_vars[$code.'_H'].$this->session_vars[$code.'_M'];
            		}
            		if ($old_value != $new_value){
            			//echo "OLD: $old_value, NEW: {$new_value}<br/>";
            			//APRO SDV
                		$this -> setVariableForSDV($this -> session_vars[$this -> config_service['PK_SERVICE']], $this -> session_vars['SITEID'], $this -> session_vars['SUBJID'], $this -> session_vars['VISITNUM'], $this -> session_vars['VISITNUM_PROGR'], $this -> session_vars['ESAM'], $this -> session_vars['PROGR'], $field_obj -> attributes['VAR']);
            		}
            	}else{
            		//Ramo standard
            		//TODO: Anche quando faccio continue (e quindi save) nella main di una mainsub...
                	$this -> setVariableForSDV($this -> session_vars[$this -> config_service['PK_SERVICE']], $this -> session_vars['SITEID'], $this -> session_vars['SUBJID'], $this -> session_vars['VISITNUM'], $this -> session_vars['VISITNUM_PROGR'], $this -> session_vars['ESAM'], $this -> session_vars['PROGR'], $field_obj -> attributes['VAR']);
            	}
            }
        }
        //$pincopalla->cippa();
        //die("UN ATTIMO.");
    }

    function initializeSDV() {
    	//ini_set('max_execution_time', 300*2);
    	Logger::send(__FUNCTION__);
    	$sql=new query($this->conn);
    	$sql->set_sql('alter session set "_optimizer_squ_bottomup"=false');
    	$sql->ins_upd();

        //self::$strategy = null;
        $version = 1;
        $strategy = $this -> getStrategy($version);
        $str = "select * from {$this->service}_coordinate where nvl(fine,0)=1 and nvl(abilitato,0)=1"; //abilitato=2 sono le righe eliminate
        $query = new query($this -> conn);
        $query -> exec($str);
        //ciclo tutti gli esami inviati
        while ($query -> get_row()) {
            //Logger::send('paziente');
            //Logger::send($query -> row);
            $session_vars = $this -> session_vars;
            $session_vars[$this -> config_service['PK_SERVICE']] = $query -> row[$this -> config_service['PK_SERVICE']];
            $session_vars['VISITNUM'] = $query -> row['VISITNUM'];
            $session_vars['VISITNUM_PROGR'] = $query -> row['VISITNUM_PROGR'];
            $session_vars['ESAM'] = $query -> row['ESAM'];
            $session_vars['PROGR'] = $query -> row['PROGR'];
            $patID = $this -> getFullPatID($query -> row[$this -> config_service['PK_SERVICE']]);
            $session_vars['SITEID'] = $patID['SITEID'];
            $session_vars['SUBJID'] = $patID['SUBJID'];
            //se ho definito il file xml per l'esame
            if ($this -> vlist -> esams[$session_vars['VISITNUM']][$session_vars['ESAM']]['XML'] != '') {
                $xml_form = new xml_form($this -> conn, $this -> config_service['service'], $this -> config_service, $session_vars);
                $xml_form -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$session_vars['VISITNUM']][$session_vars['ESAM']]['XML']);
                $xml_form -> closed_form();
                $xml_form -> session_vars = $xml_form -> tb_vals;
                //$xml_form->query_builder();
                //controllo i vari field dell'esame
                foreach ($xml_form->fields as $i => $field) {
                    //Logger::send('fields');
                    unset($xml_form -> fields[$i]['BYTB']);
                    if (isset($field['TYPE']) && $field['TYPE'] != '')
                        $field_type = "field_{$field['TYPE']}";
                    else
                        $field_type = "field";
                    if ($this -> config_service['field_lib'] != '' && file_exists($this -> config_service['field_lib'] . $field_type . ".inc")) {
                        include_once $this -> config_service['field_lib'] . $field_type . ".inc";
                    } else
                        include_once "{$field_type}.inc";
                    //istanzio il field
                    $field_obj = new $field_type($xml_form, $i, $this -> conn, $xml_form -> tb_vals, $xml_form -> session_vars, $xml_form -> service, $xml_form -> errors);
                    $field_obj -> make_open_html();
                    //controllo se è una variabile che viene salvata in DB e non è una hidden. Controllo anche se è condizionata e in tal caso se le condizioni per la sua valorizzazione sono valide
                    //if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' && ($field_obj -> attributes['CONDITION'] == '' || $field_obj -> condition_passed) && $this -> isFieldInStrategy($session_vars['VISITNUM'], $session_vars['ESAM'], $field_obj -> attributes['VAR'])) {
                    Logger::send("INITSDV: ".$field_obj -> attributes['VAR']);
                    //AUTOMATISMO DI FILTRO SUI CAMPI - NON CONSIDERO LA CONDIZIONE (PIERHD-91 27/09/2012)
		            if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' && $this -> isFieldInStrategyCached($strategy, $session_vars['VISITNUM'], $session_vars['ESAM'], $field_obj -> attributes['VAR'])) {
                        $this -> setVariableForSDV($session_vars[$this -> config_service['PK_SERVICE']], $session_vars['SITEID'], $session_vars['SUBJID'], $session_vars['VISITNUM'], $session_vars['VISITNUM_PROGR'], $session_vars['ESAM'], $session_vars['PROGR'], $field_obj -> attributes['VAR']);
                    }

                }
            }
        }
    }

    function initializeEsamSDV($codpat, $visitnum, $esam) {
        Logger::send(__FUNCTION__);
        $sql=new query($this->conn);
        $sql->set_sql('alter session set "_optimizer_squ_bottomup"=false');
        $sql->ins_upd();

        //self::$strategy = null;
        $version = 1;
        $strategy = $this -> getStrategy($version);
        $str = "select * from {$this->service}_coordinate where nvl(fine,0)=1 and codpat=:codpat and esam=:esam and visitnum=:visitnum";
        $bind_init['CODPAT'] = $codpat;
        $bind_init['ESAM'] = $esam;
        $bind_init['VISITNUM'] = $visitnum;
        $query = new query($this -> conn);
        $query -> exec($str, $bind_init);
        Logger::send($query -> tb_res());

        //ciclo tutti gli esami inviati
        while ($query -> get_row()) {
            //Logger::send('paziente');
            //Logger::send($query -> row);
            $session_vars = $this -> session_vars;
            $session_vars[$this -> config_service['PK_SERVICE']] = $query -> row[$this -> config_service['PK_SERVICE']];
            $session_vars['VISITNUM'] = $query -> row['VISITNUM'];
            $session_vars['VISITNUM_PROGR'] = $query -> row['VISITNUM_PROGR'];
            $session_vars['ESAM'] = $query -> row['ESAM'];
            $session_vars['PROGR'] = $query -> row['PROGR'];
            $patID = $this -> getFullPatID($query -> row[$this -> config_service['PK_SERVICE']]);
            $session_vars['SITEID'] = $patID['SITEID'];
            $session_vars['SUBJID'] = $patID['SUBJID'];
            //se ho definito il file xml per l'esame
            if ($this -> vlist -> esams[$session_vars['VISITNUM']][$session_vars['ESAM']]['XML'] != '') {
                $xml_form = new xml_form($this -> conn, $this -> config_service['service'], $this -> config_service, $session_vars);
                $xml_form -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$session_vars['VISITNUM']][$session_vars['ESAM']]['XML']);
                $xml_form -> closed_form();
                $xml_form -> session_vars = $xml_form -> tb_vals;
                //$xml_form->query_builder();
                //controllo i vari field dell'esame
                foreach ($xml_form->fields as $i => $field) {
                    //Logger::send('fields');
                    unset($xml_form -> fields[$i]['BYTB']);
                    if (isset($field['TYPE']) && $field['TYPE'] != '')
                        $field_type = "field_{$field['TYPE']}";
                    else
                        $field_type = "field";
                    if ($this -> config_service['field_lib'] != '' && file_exists($this -> config_service['field_lib'] . $field_type . ".inc")) {
                        include_once $this -> config_service['field_lib'] . $field_type . ".inc";
                    } else
                        include_once "{$field_type}.inc";
                    //istanzio il field
                    $field_obj = new $field_type($xml_form, $i, $this -> conn, $xml_form -> tb_vals, $xml_form -> session_vars, $xml_form -> service, $xml_form -> errors);
                    $field_obj -> make_open_html();
                    //controllo se è una variabile che viene salvata in DB e non è una hidden. Controllo anche se è condizionata e in tal caso se le condizioni per la sua valorizzazione sono valide

                    //if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' && $this -> isFieldInStrategy($session_vars['VISITNUM'], $session_vars['ESAM'], $field_obj -> attributes['VAR'])) {
                    Logger::send("INITESAMSDV: ".$field_obj -> attributes['VAR']);
                    //AUTOMATISMO DI FILTRO SUI CAMPI - NON CONSIDERO LA CONDIZIONE (PIERHD-91 27/09/2012)
            		if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' && $this -> isFieldInStrategyCached($strategy, $session_vars['VISITNUM'], $session_vars['ESAM'], $field_obj -> attributes['VAR'])) {
            			$this -> setVariableForSDV($session_vars[$this -> config_service['PK_SERVICE']], $session_vars['SITEID'], $session_vars['SUBJID'], $session_vars['VISITNUM'], $session_vars['VISITNUM_PROGR'], $session_vars['ESAM'], $session_vars['PROGR'], $field_obj -> attributes['VAR']);
                    }

                }
            }
        }
        $this -> conn -> commit();
    }

    function after_make_close_html($form, $index, $field) {
        $version = $this -> getLastStrategyVersion();
        //
        $version = 1;
        $strategy = $this -> getStrategy(1);
        $fieldname = $form -> fields[$index]['VAR'];

        //echo "PROVA";
        //if ($this -> isVersionFrozen($version) && $this -> session_vars['ACTIVE_SDV'] == 'true' && $field -> attributes['VAR'] != '' && $strategy[$form -> session_vars['VISITNUM']][$form -> session_vars['ESAM']]['FIELDS'][$fieldname] && ($field -> attributes['CONDITION'] == '' || $field -> condition_passed)) {
        //AUTOMATISMO DI FILTRO SUI CAMPI - NON CONSIDERO LA CONDIZIONE (PIERHD-91 27/09/2012)
        if ($this -> isVersionFrozen($version) && $this -> session_vars['ACTIVE_SDV'] == 'true' && $field -> attributes['VAR'] != '' && $strategy[$form -> session_vars['VISITNUM']][$form -> session_vars['ESAM']]['FIELDS'][$fieldname] ) {
        	$filters[$this -> config_service['PK_SERVICE']] = $form -> session_vars[$this -> config_service['PK_SERVICE']];
            $filters['VISITNUM'] = $form -> session_vars['VISITNUM'];
            $filters['VISITNUM_PROGR'] = $form -> session_vars['VISITNUM_PROGR'];
            $filters['ESAM'] = $form -> session_vars['ESAM'];
            $filters['PROGR'] = $form -> session_vars['PROGR'];
            $filters['VERSION'] = 1;
            $filters['FIELD'] = $fieldname;

            $status = $this -> getStrategyStatus($filters);
            if ($status[0]['VALID'])
                $checked = ' checked="checked" ';
            else
                $checked = "";
            if (trim($status[0]['PROTOCOL_VIOLATION']) != '')
                $display = '';
            else
                $display = 'display:none;';
            if (trim($status[0]['SDV_NOTE']) != '')
                $displaySDV = '';
            else
                $displaySDV = 'display:none;';
            //Recupero informazioni da coordinate
            /*
            $str_coord = "select * from {$this->service}_coordinate where esam=:esam and visitnum=:visitnum and {$this -> config_service['PK_SERVICE']}=:pk_service and progr=:progr and visitnum_progr=:vprogr";
            $bind_coord['PK_SERVICE'] = $form -> session_vars[$this -> config_service['PK_SERVICE']];
            $bind_coord['ESAM'] = $form -> session_vars['ESAM'];
            $bind_coord['VISITNUM'] = $form -> session_vars['VISITNUM'];
            $bind_coord['VPROGR'] = $form -> session_vars['VISITNUM_PROGR'];
            $bind_coord['PROGR'] = $form -> session_vars['PROGR'];
            $query_coord = new query($this -> conn);
            $query_coord -> get_row($str_coord, $bind_coord);
            */
            $mandatory = "";
            //var_dump($strategy[$form -> session_vars['VISITNUM']][$form -> session_vars['ESAM']]['FIELDS'][$fieldname]);

            $mandatory_tmp = "";
            if (function_exists("sdv_get_mandatory")) {
				$mandatory_tmp = sdv_get_mandatory($form->form['TABLE'],$form->session_vars['CODPAT'],$form -> session_vars['VISITNUM'],$form -> session_vars['ESAM'],$form -> session_vars['PROGR'],$form -> session_vars['VISITNUM_PROGR'],$fieldname);
			}

			// if ($strategy[$form -> session_vars['VISITNUM']][$form -> session_vars['ESAM']]['FIELDS'][$fieldname]['MANDATORY']){
            if (($strategy[$form -> session_vars['VISITNUM']][$form -> session_vars['ESAM']]['FIELDS'][$fieldname]['MANDATORY']) && ($mandatory_tmp == 1)){
            	$mandatory = " (mandatory)";
            }

            if ($this -> userHasToReportSDV($filters) /* && $query_coord->row['FINE']==1 */ ) { //$form->session_vars['MAIN']=="yes"
            	$da_agg = '<span class="spanSDV" ><input type="checkbox" name="SDV_FIELDS[' . $fieldname . ']" ' . $checked . '  value="1" > <span class="labelSDV">SDV'.$mandatory.'</span> <br/><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="labelSDV" onclick="$(this).next().toggle();" >Note</span><span class="textSDV" style="' . $displaySDV . '"><textarea name="NOTE_FIELDS[' . $fieldname . ']" >' . $status[0]['SDV_NOTE'] . '</textarea></span></span> <span class="spanRPV" ><span class="toggleRPV"  onclick="$(this).next().toggle();">Violation</span> <span class="textRPV" style="' . $display . '"><textarea name="RPV_FIELDS[' . $fieldname . ']" >' . $status[0]['PROTOCOL_VIOLATION'] . '</textarea></span></span>';
            } else {
                if ($checked)
                    $da_agg = ' <span class="spanSDV" ><span class="inlineSpan"><i class="fa fa-check-square-o checkedImage"></i></span> <span class="labelSDV">SDV'.$mandatory.'</span> ';
                else
                    $da_agg = ' <span class="spanSDV" ><span class="inlineSpan" ><i class="fa fa-square-o"></i></span></span> <span class="labelSDV">SDV'.$mandatory.'</span> ';

                if ($displaySDV == '') {
                    $da_agg .= ' <br/><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="labelSDV"  >Note</span><span class="textSDV" >' . $status[0]['SDV_NOTE'] . '</span></span> ';
                } else {
                    $da_agg .= '</span>';
                }
                if ($display == '')
                    $da_agg .= '<span class="spanRPV" ><span class="labelRPV"  style="cursor:pointer" >Violation</span> <span class="textRPV" >' . $status[0]['PROTOCOL_VIOLATION'] . '</span></span>';
            }
            $da_agg = '<span class="aggSpan">' . $da_agg . '</span>';
            //$da_agg.= $fieldname;
            //$html = $this -> str_lreplace('</td>', $da_agg . '</td>', $field -> html);
            $html = $field -> html.'<div class="col-sm-6" style="clear:both; display:block;" ></div><div id="sdv_'.$field->attributes['VAR'].'" class="col-sm-6 no-padding-left" style="">'.$da_agg.'</div>';

        } else {
            $html = $field -> html;
        }
        //$html.= $fieldname;
        return $html;
    }

    function str_lreplace($search, $replace, $subject) {
        $pos = strrpos($subject, $search);

        if ($pos === false) {
            return $subject;
        } else {
            return substr_replace($subject, $replace, $pos, strlen($search));
        }
    }

    function userHasToReportSDV($filters = null, $user = null, $always=false) {
    	//echo "<br/>ENTER REPORT SDV!!";
        if ($user == null) {
            $user = $this -> session_vars['remote_userid'];
        }
        if ($this->session_vars['USER_PROFILE']!="CRA") {
        	//echo "<br/>F0";
            return false;
        } else {
        	//echo "USER OK";
            if ($filters != null) {
                $tot = $this -> totFieldsSDV($filters);
                $signed = $this -> numFieldsSigned($filters);
                //echo "TOT: $tot";
                //echo "SIGNED: $signed";
                if (!$always && $tot == $signed){
                	//echo "<br/>F0bis";
                    return false;
                } else {
                    //echo "<br/>qui report SDV!";
                    if ( (isset($filters['PROGR']) && isset($filters[$this -> config_service['PK_SERVICE']]) ) && (!isset($filters['VISITNUM_PROGR']) || !$filters['VISITNUM_PROGR']) ){
                    	//Se sto utilizzando progr e codpat (quindi verosimilmente sto cercando una form specifica, allora verifico il visitnum_progr (che ad es. per pierrel non viene molto considerato)
                    	$filters['VISITNUM_PROGR'] = 0; //Comunque imposto il visitnum_progr a 0 se non lo utilizzo
                    	//Posso fare questo giochino (e controllare anche se $filters['VISITNUM_PROGR'] passato sia == false (non ===), perchè è cmq zero-based, quindi anche se è 0 (false), imposto comunque 0
                    }
                    if (isset($filters['ESAM']) && isset($filters['VISITNUM']) && isset($filters['VISITNUM_PROGR']) && isset($filters['PROGR']) && isset($filters[$this -> config_service['PK_SERVICE']])) {
                	    //Recupero informazioni da coordinate
			            $str_coord = "select * from {$this->service}_coordinate where esam=:esam and visitnum=:visitnum and {$this -> config_service['PK_SERVICE']}=:pk_service and progr=:progr and visitnum_progr=:vprogr";
			            $bind_coord['PK_SERVICE'] = $filters[$this -> config_service['PK_SERVICE']];
			            $bind_coord['ESAM'] = $filters['ESAM'];
			            $bind_coord['VISITNUM'] = $filters['VISITNUM'];
			            $bind_coord['VPROGR'] = $filters['VISITNUM_PROGR'];
			            $bind_coord['PROGR'] = $filters['PROGR'];
			            $query_coord = new query($this -> conn);
			            $query_coord -> get_row($str_coord, $bind_coord);
			            //$query_coord -> row['CONTO']
                    	if ($query_coord -> row['FINE'] == 1){
		                    if (isset($filters['FIELD']) && isset($filters['ESAM']) && isset($filters['VISITNUM']) && isset($filters['VISITNUM_PROGR']) && isset($filters['PROGR']) && isset($filters[$this -> config_service['PK_SERVICE']])) {
		                        $str = "select count(*) conto  from {$this->service}_EQFIELD where {$this->config_service['PK_SERVICE']}=:pk_service and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field and statofield in (0,2)";
		                        $query = new query($this -> conn);
		                        $bind['PK_SERVICE'] = $filters[$this -> config_service['PK_SERVICE']];
		                        $bind['FIELD'] = $filters['FIELD'];
		                        $bind['ESAM'] = $filters['ESAM'];
		                        $bind['VISITNUM'] = $filters['VISITNUM'];
		                        $bind['VISITNUM_PROGR'] = $filters['VISITNUM_PROGR'];
		                        $bind['PROGR'] = $filters['PROGR'];
		                        $query -> exec($str, $bind);
		                        $query -> get_row();
		                        if ($query -> row['CONTO'] > 0){
		                        	return false;
		                        }else {
		                            return true;
		                        }
		                    } else {
		                    	return true;
		                    }
                    	}else{
                    		return false;
                    	}
                    }else{
                    	return true;
                    }
                }
            }
            return true;
        }
    }

    function before_close_form($form) {
        $version = $this -> getLastStrategyVersion();
        if (!$this -> isVersionFrozen($version)) {
            return;
        }
        if ($this -> session_vars['ACTIVE_SDV'] == 'true') {
            $filters[$this -> config_service['PK_SERVICE']] = $form -> session_vars[$this -> config_service['PK_SERVICE']];
            $filters['VISITNUM'] = $form -> session_vars['VISITNUM'];
            $filters['ESAM'] = $form -> session_vars['ESAM'];
            $filters['PROGR'] = $form -> session_vars['PROGR'];
            $filters['VISITNUM_PROGR'] = $form -> session_vars['VISITNUM_PROGR'];
            $filters['VERSION'] = 1;
            if ($this -> userHasToReportSDV($filters))
                return '
		               <input type="hidden" name="' . $form -> form['TABLE'] . '"/>
		               <input type="hidden" name="link_to" value="' . $form -> form['LINK_TO'] . '"/>
		               <input type="hidden" name="VISITNUM" value="' . $form -> session_vars['VISITNUM'] . '"/>
		               <input type="hidden" name="VISITNUM_PROGR" value="' . $form -> session_vars['VISITNUM_PROGR'] . '"/>
		               <input type="hidden" name="ESAM" value="' . $form -> session_vars['ESAM'] . '"/>
		               <input type="hidden" name="PROGR" value="' . $form -> session_vars['PROGR'] . '"/>
		               <input type="hidden" name="SITEID" value="' . $form -> tb_vals['SITEID'] . '"/>
		               <input type="hidden" name="SUBJID" value="' . $form -> tb_vals['SUBJID'] . '"/>
		               <input type="hidden" name="module" value="SDV"/>
		               <input type="hidden" name="sdv_action" value="saveSDV"/>
		               <input type="hidden" name="' . $this -> config_service['PK_SERVICE'] . '" value="' . $form -> session_vars[$this -> config_service['PK_SERVICE']] . '"/>
		               <input type="hidden" name="SDV" value="1"/>
		               
									 ';
        }
    }

    function after_close_form($form) {
        $version = $this -> getLastStrategyVersion();
        if (!$this -> isVersionFrozen($version)) {
            return;
        }
        $js = '
        	<script language="javascript">
        		function validateSDV(){
        			var mistake=false;
        			var message = "";
        			$(\'.textRPV textarea\').each(
        				function(){
        					var fieldtext = $.trim($(this).val());
        					var fieldname = $.trim($(this).attr("name"));
        					//alert($.trim($(this).attr("name") )); 
        					//alert($(this));       		
        					$(this).css("border", "" ); 			
        					if($.trim($(this).val()) !=\'\' 
        						&& $(this).parent().parent().prev(\'.spanSDV\').find(\':checkbox:checked\').length==0 ){
			        			mistake=true;
			        			$(this).css("border", "2px solid #FF0000" ); 
			        			message+=\'You must check SDV for the Reported Protocol Violations [\'+fieldname+\']: \'+fieldtext+"\n";
						    }
    						if($.trim($(this).val()) !=\'\' 
    							&& $(this).parent().parent().prev(\'.spanSDV\').find(\'textarea\').val()!=\'\' ){
    							mistake=true;
			        			$(this).css("border", "2px solid #FF0000" ); 
    							message+=\'If there is a reported protocol violation on a question the note field must be left empty [\'+fieldname+\']: \'+fieldtext+"\n";
    						}
    					}
				    );
				    $(\'.textSDV textarea\').each(
				    	function(){
        					var fieldtext = $.trim($(this).val());
        					var fieldname = $.trim($(this).attr("name"));
        					$(this).css("border", "" ); 			
        					if($.trim($(this).val()) !=\'\' 
				    			&& $(this).parent().parent().find(\':checkbox:checked\').length==0 ){
				    			mistake=true;
				    			$(this).css("border", "2px solid #FF0000" ); 
				    			message+=\'You must check SDV for the noted fields [\'+fieldname+\']: \'+fieldtext+"\n";
    						}
    					}
    				);
    				if(mistake){
        				alert(message);
    					return false;
    				}
    				return true;
        		}
        	</script>
        ';
        if ($this -> session_vars['ACTIVE_SDV'] == 'true') {
            $filters[$this -> config_service['PK_SERVICE']] = $form -> session_vars[$this -> config_service['PK_SERVICE']];
            $filters['VISITNUM'] = $form -> session_vars['VISITNUM'];
            $filters['ESAM'] = $form -> session_vars['ESAM'];
            $filters['PROGR'] = $form -> session_vars['PROGR'];
            $filters['VISITNUM_PROGR'] = $form -> session_vars['VISITNUM_PROGR'];
            $filters['VERSION'] = 1;
            
            if ($this -> userHasToReportSDV($filters))
                $html = '
                    <div class="col-sm-6" style="clear:both; display:block;" ></div><div id="sdv_invio_btn" class="col-sm-6 no-padding-left" style="">'.
                '		<input type="submit" name="SDV_INVIO" value="Save SDV" onmousedown="return validateSDV();" />'.
                '   </div>';
            $html .= $this -> getCSS('form');
            $html .= $js;
            return $html;
        }
    }

    function after_SendMainSub($codpat, $visitnum, $esam) {
        Logger::send(__FUNCTION__);
        Logger::send('SENDMAINSUB?');
        return $this -> initializeEsamSDV($codpat, $visitnum, $esam);
    }

    function after_ApprovaEq($xml_form, $eq_int, $old_value, $new_value) {
        $version = $this -> getLastStrategyVersion();

        if (!$this -> isVersionFrozen($version)) {
            return;
        }

        $i = $xml_form -> vars[$this -> session_vars['EQFIELD']];
        if (is_null($i)) {
            foreach ($xml_form -> fields as $curr_i => $curr_field) {
                if (preg_match('/checkbox/i', $curr_field['TYPE'])) {
                    $field_type = "field_{$curr_field['TYPE']}";

                    if ($this -> config_service['field_lib'] != '' && file_exists($this -> config_service['field_lib'] . $field_type . ".inc")) {
                        include_once $this -> config_service['field_lib'] . $field_type . ".inc";
                    } else
                        include_once "{$field_type}.inc";
                    $field_obj = new $field_type($xml_form, $curr_i, $this -> conn, $xml_form -> tb_vals, $xml_form -> session_vars, $xml_form -> service, $xml_form -> errors);
                    //                    $field_obj -> make_open_html();
                    foreach ($field_obj->values as $field_check => $value) {
                        if ($this -> session_vars['EQFIELD'] == $field_check) {
                            $i = $curr_i;
                            break 2;
                        }
                    }
                }
            }
        }
        $field = $xml_form -> fields[$i];
        $strategy = $this -> getStrategy(1);
        //die("STO QUA");
        if ($strategy[$this -> session_vars['VISITNUM']][$this -> session_vars['ESAM']]['FIELDS'][$field['VAR']]) {
        	//die("STRATEGY OK!");
            $fullID = $this -> getFullPatID($this -> session_vars[$this -> config_service['PK_SERVICE']]);
            $this -> session_vars['SITEID'] = $fullID['SITEID'];
            $this -> session_vars['SUBJID'] = $fullID['SUBJID'];
            
            //var_dump($fullID);
            //echo $old_value."<hr/>";
            //echo $new_value."<hr/>";
            //debug_print_backtrace();
            //die();
            if ($old_value != $new_value){
                //echo "<pre>";
                //debug_print_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS);
            	//die("RESETTA VARIABILE SDV!");
            	$this -> resetVariableAfterEq($eq_int, $this -> session_vars[$this -> config_service['PK_SERVICE']], $this -> session_vars['SITEID'], $this -> session_vars['SUBJID'], $this -> session_vars['VISITNUM'], $this -> session_vars['VISITNUM_PROGR'], $this -> session_vars['ESAM'], $this -> session_vars['PROGR'], $field['VAR']);
            }
        }

    }

    function testo($testo) {
        if (!$this -> testi[$testo]) {
            if ($this -> config_service['lang'] == 'it') {
                $this -> testi['open_sdv'] = 'Apri&nbsp;SDV';
                $this -> testi['close_sdv'] = 'Chiudi&nbsp;SDV';
                $this -> testi['sign_sdv'] = 'Firma&nbsp;SDV';
                $this -> testi['report_status_sdv'] = "Status";
            } else {
                $this -> testi['open_sdv'] = 'Open&nbsp;SDV';
                $this -> testi['close_sdv'] = 'Close&nbsp;SDV';
                $this -> testi['sign_sdv'] = 'Sign&nbsp;SDV';
                $this -> testi['report_status_sdv'] = "Status";
            }
        }
        return $this -> testi[$testo];
    }

    function verifyStrategyStatusForPat($codpat, $version) {
        $str = "select * from {$this->service}_coordinate where nvl(fine,0)=1 and {$this->config_service['PK_SERVICE']}=:codpat and esam=0 and visitnum=0";
        $bind['CODPAT'] = $codpat;
        $query = new query($this -> conn);
        $query -> exec($str, $bind);
        if ($query -> get_row()) {

            $session_vars = $this -> session_vars;
            $session_vars[$this -> config_service['PK_SERVICE']] = $query -> row[$this -> config_service['PK_SERVICE']];
            $session_vars['VISITNUM'] = $query -> row['VISITNUM'];
            $session_vars['VISITNUM_PROGR'] = $query -> row['VISITNUM_PROGR'];
            $session_vars['ESAM'] = $query -> row['ESAM'];
            $session_vars['PROGR'] = $query -> row['PROGR'];
            $patID = $this -> getFullPatID($query -> row[$this -> config_service['PK_SERVICE']]);
            $session_vars['SITEID'] = $patID['SITEID'];
            $session_vars['SUBJID'] = $patID['SUBJID'];

            $str_check = "select count(codpat) conto from {$this->strategyStatusTable} where codpat=:codpat and visitnum=0 and esam=0 and version=:version";
            $query_check = new query($this -> conn);
            $bind_check['VERSION'] = $version;
            $bind_check['CODPAT'] = $codpat;
            $query_check -> get_row($str_check, $bind_check);
            if ($query_check -> row['CONTO'] == '0') {
                if ($this -> vlist -> esams[$session_vars['VISITNUM']][$session_vars['ESAM']]['XML'] != '') {
                    $xml_form = new xml_form($this -> conn, $this -> config_service['service'], $this -> config_service, $session_vars);
                    $xml_form -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$session_vars['VISITNUM']][$session_vars['ESAM']]['XML']);
                    $xml_form -> closed_form();
                    $xml_form -> session_vars = $xml_form -> tb_vals;
                    //$xml_form->query_builder();
                    foreach ($xml_form->fields as $i => $field) {
                        //Logger::send('fields');
                        unset($xml_form -> fields[$i]['BYTB']);
                        if (isset($field['TYPE']) && $field['TYPE'] != '')
                            $field_type = "field_{$field['TYPE']}";
                        else
                            $field_type = "field";
                        if ($this -> config_service['field_lib'] != '' && file_exists($this -> config_service['field_lib'] . $field_type . ".inc")) {
                            include_once $this -> config_service['field_lib'] . $field_type . ".inc";
                        } else
                            include_once "{$field_type}.inc";
                        $field_obj = new $field_type($xml_form, $i, $this -> conn, $xml_form -> tb_vals, $xml_form -> session_vars, $xml_form -> service, $xml_form -> errors);
                        $field_obj -> make_open_html();
                        //if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' && ($field_obj -> attributes['CONDITION'] == '' || $field_obj -> condition_passed)) {
                        Logger::send("VERIFYSTRATEGY: ".$field_obj -> attributes['VAR']);
                        //AUTOMATISMO DI FILTRO SUI CAMPI - NON CONSIDERO LA CONDIZIONE (PIERHD-91 27/09/2012)
			            if ($field_obj -> attributes['VAR'] != '' && $field_obj -> attributes['TYPE'] != 'hidden' && $field_obj -> attributes['TYPE'] != '' && $field_obj -> attributes['TB'] != 'no' ) {
                            $this -> setVariableForSDV($session_vars[$this -> config_service['PK_SERVICE']], $session_vars['SITEID'], $session_vars['SUBJID'], $session_vars['VISITNUM'], $session_vars['VISITNUM_PROGR'], $session_vars['ESAM'], $session_vars['PROGR'], $field_obj -> attributes['VAR']);
                        }

                    }
                }
                $this -> conn -> commit();
            }
        }

    }

    function after_make_patient_table() {
        $form=null;
        $version = $this -> getLastStrategyVersion();
        if ($this -> isVersionFrozen($version)) {
            $this -> verifyStrategyStatusForPat($this -> session_vars[$this -> config_service['PK_SERVICE']], $this -> getLastStrategyVersion());
        } else {
            return;
        }
        
        $esigLink = '';
        $html = '';
        // PIERHD-2209 - DM - rimuovo il link "sign SDV" quando sono dentro ad una form (ho $in['ESAM'])
        if ($this->session_vars['USER_PROFILE']=="CRA" && !$this->session_vars['ESAM']){
        	$esigLink = '<br/><a href="index.php?module=SDV&sdv_action=eSignature&' . $this -> config_service['PK_SERVICE'] . '=' . $this -> session_vars[$this -> config_service['PK_SERVICE']] . '"> ' . $this -> testo('sign_sdv') . ' </a>';
        }
        if ($this -> checkVisione()) {

            if ((isset($this -> session_vars['form']) || isset($this -> session_vars['ESAM'])) && !isset($this -> session_vars['EQUERY_OBJ']) && !isset($this -> session_vars['eQuery'])) {
                if ($this -> session_vars['ACTIVE_SDV'] == 'true') {
                    $url = str_replace('&ACTIVE_SDV=true', '', $_SERVER['REQUEST_URI']);
                    $html .= '  <div style="float:left"><i class="fa fa-search"></i>&nbsp;SDV</div>
                                <div style="float:right"><a href="' . $url . '"><i class="fa fa-dot-circle-o"></i>&nbsp;' . $this -> testo('close_sdv') . ' </a>'.$esigLink.'</div><div style="clear:both">&nbsp;</div>
                        ';
                    $filters[$this -> config_service['PK_SERVICE']] = $this -> session_vars[$this -> config_service['PK_SERVICE']];
                    $filters['VISITNUM'] = $this -> session_vars['VISITNUM'];
                    $filters['ESAM'] = $this -> session_vars['ESAM'];
                    $filters['PROGR'] = $this -> session_vars['PROGR'];
                    $filters['VISITNUM_PROGR'] = $form -> session_vars['VISITNUM_PROGR'];
                    $filters['VERSION'] = 1;

                    //Qui (e solo qui) c'è il link CHECK/UNCHECK ALL checkboxes...
                    //print_r($filters);
                    //echo "<br/>REPORTSDV: ";
                    //echo $this -> userHasToReportSDV($filters, null, true);
                    if ($this -> userHasToReportSDV($filters, null, true)) {
                        $html .= '  <div style="float:left"><span style="font-size: x-small;">Check/Uncheck all SDV checkboxes</span></div>
                                    <div style="float:right"><span style="font-size: x-small;"><input onclick="sdv_check_all(this);" name="all_sdv" type="checkbox" value="1" /></span></div><div style="clear:both">&nbsp;</div>
                        ';
                    }
                } else {
                    $html .= '  <div style="float:left"><i class="fa fa-search"></i>&nbsp;SDV</div>
                                <div style="float:right"><a href="' . $_SERVER['REQUEST_URI'] . '&ACTIVE_SDV=true"><i class="fa fa-circle-o"></i>&nbsp;' . $this -> testo('open_sdv') . ' </a>'.$esigLink.'</div><div style="clear:both">&nbsp;</div>
                        ';
                 }
            } else {
            	$html = '<td>&nbsp;</td>';
            	//Se ho solo il link di firma, ma questo è spento poichè sono un profilo che non può firmare, nascondo completamente il box SDV
            	if ($esigLink){
                    $html = '  <div style="float:left"><i class="fa fa-search"></i>&nbsp;SDV</div>
                                <div style="float:right">'.$esigLink.'</div><div style="clear:both">&nbsp;</div>
                        ';
            	}
            }
        }
        //Questo è commentato, se serve lo inseriremo con le opportune modifiche
        $html .= '<!--<td><table class="sf" width="100%" align="center">
				<tr>
				<td class="int" nowrap="" align="center" style="vertical-align:top; height:15px;">SDV Reports</td>
				
				</tr>
				<tr>
				<td class="int_pt2" align="center" style="height:50px"><p align="center">
				<a href="index.php?SDV_LIST=status"> ' . $this -> testo('report_status_sdv') . ' </a></td>
				
				</td>
				
				</tr></table></td>-->
				
		';
        return $html;
    }

    function before_signsdv_close_($field_obj) {
        $version = $this -> getLastStrategyVersion();
        if (!$this -> isVersionFrozen(1)) {
            return;
        }
        $str = 'select to_char(SIGNDATE,\'DD/MM/YYYY HH24:MI\') SIGNDATE from ' . $this -> signTable . ' where ' . $this -> config_service['PK_SERVICE'] . '=:pk_service';
        $query = new query($this -> conn);
        $bind['PK_SERVICE'] = $this -> session_vars[$this -> config_service['PK_SERVICE']];
        $query -> exec($str, $bind);
        $query -> get_row();
        return $query -> row['SIGNDATE'];
    }

    function readStrategyStep1($version = 1) {
        if (!$this -> isVersionFrozen(1)) {
            $note = "<center><b>This Strategy is not yet frozen and can still be changed.</b></center>";
        }
        $result = $note . $this -> defineStrategyStep1($version, true);
        return $result;
    }

    function readStrategyStep2($version = 1, $visitnum) {
        if (!$this -> isVersionFrozen(1)) {
            $note = "<center><b>This Strategy is not yet frozen and can still be changed.</b></center>";
        }
        $result = $note . $this -> defineStrategyStep2($version, $visitnum, true);
        return $result;
    }

    function readStrategyStep3($version = 1, $visitnum, $esam) {
        if (!$this -> isVersionFrozen($version)) {
            $note = "<center><b>This Strategy is not yet frozen and can still be changed.</b></center>";
        }
        $result = $note . $this -> defineStrategyStep3($version, $visitnum, $esam, true);
        return $result;
    }

    function before_Controller() {
        if ($this -> session_vars['module'] == 'SDV') {
            $this -> setTabMenu();
            switch($this->session_vars['sdv_action']) {
                case 'initializeSDV' :
                    $this -> initializeSDV();
                    break;
                case 'saveSDV' :
                    /*$link = $this->session_vars ['link_to'];
                     if ($link == '')
                     $link = "index.php";
                     else {
                     $link = str_replace ( "|and|", "&", $link );
                     $link = preg_replace ( "/\\[(.*?)\\]/e", "var_glob('\\1')", $link );
                     }*/
                    $link = "?exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->session_vars[$this->config_service['PK_SERVICE']]}&CENTER={$this->session_vars['CENTER']}";
                    $this -> saveSDV();
                    $this -> conn -> commit();
                    header('Location:' . $link);
                    return 'SAVING...';
                    break;
                case 'defineStrategyStep1' :
                    if (!$this -> checkAmmin())
                        error_page($this -> session_vars['remote_userid'], 'User is not allowed to this function');
                    return $this -> defineStrategyStep1($this -> session_vars['version']);
                    break;
                case 'defineStrategyStep2' :
                    if (!$this -> checkAmmin())
                        error_page($this -> session_vars['remote_userid'], 'User is not allowed to this function');
                    return $this -> defineStrategyStep2($this -> session_vars['version'], $this -> session_vars['VISITNUM']);
                    break;
                case 'defineStrategyStep3' :
                    //die("QUA?");
                    if (!$this -> checkAmmin())
                        error_page($this -> session_vars['remote_userid'], 'User is not allowed to this function');
                    return $this -> defineStrategyStep3($this -> session_vars['version'], $this -> session_vars['VISITNUM'], $this -> session_vars['ESAM']);
                    break;
                case 'readStrategyStep1' :
                    return $this -> readStrategyStep1($this -> session_vars['version']);
                    break;
                case 'readStrategyStep2' :
                    return $this -> readStrategyStep2($this -> session_vars['version'], $this -> session_vars['VISITNUM']);
                    break;
                case 'readStrategyStep3' :
                    return $this -> readStrategyStep3($this -> session_vars['version'], $this -> session_vars['VISITNUM'], $this -> session_vars['ESAM']);
                    break;
                case 'saveStrategyStep1' :
                    if (!$this -> checkAmmin())
                        error_page($this -> session_vars['remote_userid'], 'User is not allowed to this function');
                    $this -> saveStrategyStep1();
                    header('Location:?module=SDV&sdv_action=defineStrategyStep1&version=' . $this -> session_vars['version']);
                    die();
                    break;
                case 'saveStrategyStep2' :
                	//die("Freezo qua?");
                	if (!$this -> checkAmmin())
                        error_page($this -> session_vars['remote_userid'], 'User is not allowed to this function');
                    $this -> saveStrategyStep2();
                    header('Location:?module=SDV&sdv_action=defineStrategyStep2&version=' . $this -> session_vars['version'] . '&VISITNUM=' . $this -> session_vars['VISITNUM']);
                    die();
                    break;
                case 'saveStrategyStep3' :
                    if (!$this -> checkAmmin())
                        error_page($this -> session_vars['remote_userid'], 'User is not allowed to this function');
                    $this -> saveStrategyStep3();
                    header('Location:?module=SDV&sdv_action=defineStrategyStep3&version=' . $this -> session_vars['version'] . '&VISITNUM=' . $this -> session_vars['VISITNUM'] . '&ESAM=' . $this -> session_vars['ESAM']);
                    die();
                    break;
                case 'eSignature' :
                	//PIERHD-2209 - DM - Modifica x nuova gestione firma singola visita o multivisite
                    //if ($this -> isObjectSelected($this -> session_vars[$this -> config_service['PK_SERVICE']])) {
                    //    $html = $this -> eSignature($this -> session_vars[$this -> config_service['PK_SERVICE']]);
                    //} else {
                	if ( $this -> isObjectSelected($this -> session_vars[$this -> config_service['PK_SERVICE']]) && $this -> isObjectSelected($this -> session_vars['VISITNUM']) ) {
                        $html = $this -> eSignature($this -> session_vars[$this -> config_service['PK_SERVICE']], $this -> session_vars['VISITNUM']);
                    } else {
                        $html = $this -> eSignatureObjectSelect();
                    }
                    return $html;
                case 'eSignatureConfirm' :
                    $html = $this -> eSignatureConfirm();
                    return $html;
                    break;
                case 'reportSDVStrategy' :
                    $html = $this -> reportSDVStrategy();
                    return $html;
                    break;
                case 'eSignatureSave' :
                    $this -> eSignatureSave();

                    $link = '?module=SDV&sdv_action=eSignatureConfirm&' . $this -> config_service['PK_SERVICE'] . '=' . $this -> session_vars[$this -> config_service['PK_SERVICE']];
                    header('Location:' . $link);
                    return 'SAVING...';
                    break;
            }
        }
    }

    function eSignatureConfirm() {
        if ($this -> config_service['lang'] == 'it') {
            $testo = 'Source Data Verification firmato!';
        } else {
            $testo = 'Source Data Verification signed!';

        }
        return '<table align=center><tr><td><h1>' . $testo . '</h1></td></tr></table>';
    }

    function eSignatureObjectSelect() {
    	//PIERHD-2209 - DM - Modifica x nuova gestione firma singola visita o multivisite
    	global $in;
    	//global $vlist;
    	//print_r($in);
        $query = new query($this -> conn);
        $str = 'select ' . $this -> config_service['PK_SERVICE'] . ',siteid,subjid,center from ' . $this -> service . '_'.$this->regTable.' where center in (select center from ' . $this -> service . '_UTENTI_CENTRI where userid=:username) order by siteid,subjid';
        $bind['USERNAME'] = $this -> session_vars['remote_userid'];
        $query -> exec($str, $bind);
        $sites = array();
        $centers = array();
        //$pkids = array();
        while ($query -> get_row()) {
            $index = count($sites[$query -> row['SITEID']]);
            $sites[$query -> row['SITEID']][$index]['PK_SERVICE'] = $query -> row[$this -> config_service['PK_SERVICE']];
            $sites[$query -> row['SITEID']][$index]['SUBJID'] = $query -> row['SUBJID'];
            $sites[$query -> row['SITEID']][$index]['CENTER'] = $query -> row['CENTER'];
            $centers[$query -> row['CENTER']] = $query -> row['SITEID'];
            //$pkids[$query ->row[$this -> config_service['PK_SERVICE']] = $query -> row['SUBJID'];
        }
        //echo "<pre>";
        //echo "$str\n";
        //print_r($sites);
        //echo "</pre>";
        //PIERHD-2209 - DM - Carico le visite del paziente (aperte e quindi presenti in coordinate?)
        $str='select distinct '.$this->config_service['PK_SERVICE'].', VISITNUM from '.$this->service.'_COORDINATE 
				where '.$this->config_service['PK_SERVICE'].' in (
				    select '.$this->config_service['PK_SERVICE'].' from '.$this->service.'_'.$this->regTable.'
				    where center in (
				        select center from '.$this->service.'_UTENTI_CENTRI where userid=:username
				        )
				    )
				order by CODPAT,VISITNUM
        ';
        $bind['USERNAME'] = $this -> session_vars['remote_userid'];
        //echo $str;
        $query -> exec($str, $bind);
        $visits = array();
        while ($query -> get_row()) {
        	if (!$visits[$query -> row[$this -> config_service['PK_SERVICE']]]){
        		$visits[$query -> row[$this -> config_service['PK_SERVICE']]] = array();
        	}
        	$visits[$query -> row[$this -> config_service['PK_SERVICE']]][] = $query -> row['VISITNUM'];
        }
        //echo "<pre>";
        //print_r($visits);
        //echo "</pre>";
        //echo "<pre>";
        //print_r($this->vlist->visitnums);
        //echo "</pre>";
                
        $select_site = "<select name='SITEID' id='SITEID'><option></option>"; //Chiudo + in basso.
        $select_subjid = "<select name='{$this->config_service['PK_SERVICE']}' id='{$this->config_service['PK_SERVICE']}'></select><input type='hidden' name='SUBJID' id='SUBJID' /><input type='hidden' name='CENTER' id='CENTER' />";
        $select_visit = "<select name='VISITNUM' id='VISITNUM'></select>";
        $pksvscript = "";
        if ($in[$this->config_service['PK_SERVICE']]){
        	$pksvscript = "
					//if (".$in[$this->config_service['PK_SERVICE']].">0){
						\$('select#{$this->config_service['PK_SERVICE']}').val('".$in[$this->config_service['PK_SERVICE']]."').change();
					//}
        		";
        }
        $script = "
			<script>
				$(document).ready(function(){
				\$('select#SITEID').change(function(){
					\$('select#{$this->config_service['PK_SERVICE']}').html(select_site[\$(this).val()]);
					".$pksvscript."
				});
				\$('select#{$this->config_service['PK_SERVICE']}').change(function(){
					\$('input#CENTER').val(hidden_center[\$(this).val()]);
					\$('input#SUBJID').val(\$(this).find('option:selected').html());
					//Add visits! (PIERHD-2209)
					\$('select#VISITNUM').html(select_codpat[\$(this).val()]);
				});
				var select_site=new Array();
				var hidden_center=new Array();
				var select_codpat=new Array();
				select_site['']='';
				select_codpat['']='';
			";
        foreach ($sites as $currSite => $patients) {
            $script .= "
			select_site['{$currSite}']='<option></option>';
			";
            $select_site .= "<option value=\"{$currSite}\">{$currSite}</option>";
            foreach ($patients as $i => $currpat) {
                $script .= "
				hidden_center['{$currpat['PK_SERVICE']}']='{$currpat['CENTER']}';
				select_site['{$currSite}']+='<option value=\"{$currpat['PK_SERVICE']}\">{$currpat['SUBJID']}</option>';";
            }
        }
        foreach ($visits as $cpat => $varray) {
            $script .= "
				select_codpat['{$cpat}']='<option value=\"-1\">ALL</option>';
	        ";
			foreach ($varray as $vnum){
				if($this->vlist->visitnums[$vnum]){
		            $script .= "
		        		select_codpat['{$cpat}']+='<option value=\"{$vnum}\">{$this->vlist->visitnums[$vnum]['TEXT']}</option>';
			        ";
				}
        	}
        }
        if ($in['CENTER']){
	        $script .= "
	        	\$('select#SITEID').val('".$centers[$in['CENTER']]."').change();
	        	";
        }
        $script .= "
    		});
		</script>";
        $select_site .= "</select>";

        $html = "$script <br/>
		<form>
		<table class=\"sf\" align='center'  >
		<tr>
<td class=\"titolo\" align=\"center\" colspan=\"4\">Select Patient</td>
</tr>
<tr>
<td  class=\"destra\" style=\"text-align:right;\" >Center</td>
<td  class=\"input\" style=\"text-align:left;\" ><input type='hidden' name='module' value='SDV' />
		<input type='hidden' name='sdv_action' value='{$this->session_vars['sdv_action']}' />
		$select_site</td>
</tr>
<tr>
<td  class=\"destra\" style=\"text-align:right;\" >Patient Num.</td>
<td  class=\"input\" style=\"text-align:left;\" >$select_subjid</td>
</tr>
<tr>
<td  class=\"destra\" style=\"text-align:right;\" >Visit Num.</td>
<td  class=\"input\" style=\"text-align:left;\" >$select_visit</td>
</tr>
<tr><td colspan='2' align='center'>
		 <br/> 
		<input type='submit' name='selectPat' value='Select' />
		
		</td></tr>
		</table>
		</form>
		";
        return $html;

    }

    function getFullPatID($shortId) {
        $query = new query($this -> conn);
        $str = 'select siteid,subjid,center from ' . $this -> service . '_'.$this->regTable.' where ' . $this -> config_service['PK_SERVICE'] . '=:pk_service';
        $bind['PK_SERVICE'] = $shortId;
        $query -> get_row($str, $bind);
        //print_r($query -> row);
        //if (!$query->row['SITEID']){
        //	die();
        //}
        return $query -> row;
    }

    function eSignatureSave() {
        if (!$this -> session_vars['form']){
            $this -> session_vars['form']="SDV_esign.xml";
        }
        if ($this -> config_service['lang'] == 'en') {
            $visit_sign = " Source Data Verification must be completed";
            $alert_enable = " Your Username is not able to sign eCRF. ";
            $alert_eqpending = " The electronic signature can be affixed only if there are no query pending in the related visit. At the moment there is at least one query pending in this visit. ";
            $alert_access = " The username inserted does not match with the one used to access.";
            $alert_user = " The username is not valid.";
            $alert_passwd = " The password is not correct.";
            $alert_object = " No Patient has been selected.";
        } else {
            $visit_sign = " il Source Data Verification deve essere completato.";
            $alert_enable = " L'username non corrisponde a quello con cui si è effettuato l'accesso.";
            $alert_eqpending = " La firma elettronica può essere apposto solo se non ci sono query in attesa della visita correlati. Al momento non vi è almeno una query in attesa di questa visita. ";
            $alert_access = " L'username non corrisponde a quello con cui si è effettuato l'accesso.";
            $alert_user = " L' username non è valido.";
            $alert_passwd = " La password inserita non é corretta.";
            $alert_object = " Non è stato selezionato nessun paziente.";
        }
        if ($this -> isObjectSelected($this -> session_vars[$this -> config_service['PK_SERVICE']]) &&
        	$this -> isObjectSelected($this -> session_vars['VISITNUM'])) {
            if ($this -> CheckUserLogged($this -> session_vars['USERNAME'])) {
                //Logger::send("sdjhghjgj");
                if ($this -> CheckUserSignEnable($this -> session_vars['USERNAME'])) {
                	//PIERHD-2209 - Modifica multivisita
                    if ($this -> isSDVComplete($this -> session_vars[$this -> config_service['PK_SERVICE']])) { //isSDVComplete non ha parametri??
                        if ($this -> CheckUserPassword($this -> session_vars['USERNAME'], $this -> session_vars['PASSWORD'])) {
                            if ($this -> session_vars['ajax_call'] != '') {
                                die("link_to: eSignatureSave");
                            }else{
                                $this ->UpdateDbSignature();
                                $this ->conn ->commit();
                            }
                        } else {
                            if ($this -> session_vars['ajax_call'] != '') {
                                echo "Error:#error#";
                                die($alert_passwd);
                            } else {
                                error_page($this -> session_vars['remote_userid'], $alert_passwd);
                            }
                        }
                    } else {
                        if ($this -> session_vars['ajax_call'] != '') {
                            echo "Error:#error#";
                            die($visit_sign);
                        } else {
                            error_page($this -> session_vars['remote_userid'], $visit_sign);
                        }
                    }
                } else {
                    if ($this -> session_vars['ajax_call'] != '') {
                        echo "Error:#error#";
                        die($alert_enable);
                    } else {
                        error_page($this -> session_vars['remote_userid'], $alert_enable);
                    }
                }
            } else {
                if ($this -> session_vars['ajax_call'] != '') {
                    echo "Error:#error#";
                    die($alert_access);
                } else {
                    error_page($this -> session_vars['remote_userid'], $alert_access);
                }
            }
        } else {
            if ($this -> session_vars['ajax_call'] != '') {
                echo "Error:#error#";
                die($alert_object);
            } else {
                error_page($this -> session_vars['remote_userid'], $alert_object);
            }
        }

    }

    function isObjectSelected($objectId) {
        return ($objectId !== '' && is_numeric($objectId));
    }

    function CheckEqVisitPending() {
        $sql_check3=null;
        global $in;
        global $conn;
        global $service;
        global $lang;
        //Controllo che l'utente sia abilitato a firmare
        $sql3 = new query($conn);

        $val['CODPAT'] = $in['CODPAT'];
        $val['VISITNUM'] = $in['VISITNUM'];
        $val['VISITNUM_PROGR'] = $in['VISITNUM_PROGR'];
        $sql3 -> set_sql();
        $sql3 -> exec($sql_check3, $val);
        $sql3 -> get_row();
        $eq_pending = $sql3 -> row['CONTO'];
        // Se $eq_pending Ã¨ 0 , non ci sono eQuery pending nella visita.
        return $eq_pending;
    }

    function isSDVComplete() {
        return true;
    }

    function eSignature($pk_service, $visitnum=-1) {
    	//PIERHD-2209 - DM - Modifica x nuova gestione firma singola visita o multivisite
    	//Se visitnum >= 0, firmo la visita corrispondente
    	//Se visitnum == -1, firmo tutte le visite del paziente.
        unset($this -> session_vars['sdv_action']);
        if ($this -> session_vars['SITEID'] == '' || $this -> session_vars['SUBJID'] == '') {
            $fullID = $this -> getFullPatID($pk_service);
            $this -> session_vars['SITEID'] = $fullID['SITEID'];
            $this -> session_vars['SUBJID'] = $fullID['SUBJID'];
            $this -> session_vars['CENTER'] = $fullID['CENTER'];
            //Logger::send($this -> session_vars['CENTER']);
        }
        $xml = new xml_form($this -> conn, $this -> config_service['service'], $this -> config_service, $this -> session_vars);
        //echo $this -> xml_dir . '/SDV_esign.xml';
        $xml -> xml_form_by_file($this -> xml_dir . '/SDV_esign.xml');

        if (!$this -> checkModifica()) {
            $xml -> open_form(true, true);
            $form = $xml -> body;
            $form = preg_replace('/<input(.*?)>/ie', '', $form);

        } else {
            $xml -> open_form();
            //die($xml -> body);
            $form = $xml -> body;
        }
        //	$form=preg_replace('/<\/?select(.*?)>/ie','',$form);
        //$form=preg_replace('/<\/?option(.*?)>/ie','',$form);
        $addvnumtxt = "You've selected to sign ALL visits for the patient {$this -> session_vars['SITEID']}/{$this -> session_vars['SUBJID']}";
        if ($visitnum >= 0){
        	$addvnumtxt = "You've selected to sign ONLY visit {$visitnum} ({$this->vlist->visitnums[$visitnum]['TEXT']}) for the patient {$this -> session_vars['SITEID']}/{$this -> session_vars['SUBJID']}";
        }
        $form = "<div align=\"center\" class=\"titolo\" style=\"margin:auto; width: 60%;\">{$addvnumtxt}</div>".$form;

        $html = '<script>
		' . $xml -> script_js . $xml -> invia_js . $xml -> salva_js . $xml -> check_js . '$(document).ready(function(){' . $xml -> onload . '});
		</script>' . $form;

        return $html;
    }

    function CheckUserSignEnable($username) {
        if ($this->session_vars['USER_PROFILE']=="CRA") {
            //Controllo che l'utente sia abilitato a firmare
            $sql3 = new query($this -> conn);
            $val['USERNAME'] = strtoupper($username);
            $val['CENTER'] = $this -> session_vars['CENTER'];
            $sql_check3 = "SELECT COUNT(*) AS CONTO FROM {$this->service}_UTENTI_CENTRI WHERE USERID=:USERNAME AND CENTER=:CENTER";
            // Aggiungo la gestione dei ruoli

            $sql3 -> exec($sql_check3, $val);
            $sql3 -> get_row();
            $enabled = ($sql3 -> row['CONTO'] > 0);

            // Se $enabled Ã¨ 0 , l'utente non Ã¨ abilitato a firmare per questo centro.
            return $enabled;
        } else {
            return false;
        }
    }

    function CheckUserPassword($username, $password) {
        //include_once '/http/lib/DriverIanus/libs.inc';
        $driver_conn = new DriverIanusDBConnection();
        //$password = ereg_replace(' ', "+", $password); //2015-11-05 DARIO -> Non serve più in quanto presente urlencoding sui campi inviati.
        //Controllo correttezza passwd immessa rispetto a quella dell'usserid in DB
        if (CheckPWD($driver_conn, strtoupper($username), strtoupper($password))) {
            //    		print_r($in['PASSWORD']);echo "OK";
            return true;
        } else {
            return false;
        }
    }

    function UpdateDbSignature() {
        global $in;
        global $conn;
        global $service;
        global $lang;
        $sql3 = new query($conn);
        //Gestione Audit Trail non so se sia da implementare
        /*$pk='';
         $vals_at['VISITNUM']=$in['VISITNUM'];
         $vals_at['VISITNUM_PROGR']=$in['VISITNUM_PROGR'];
         $vals_at['ESAM']=$in['ESAM'];
         $vals_at['PROGR']=$in['PROGR'];
         $vals_at['CODPAT']=$in['CODPAT'];
         $vals_at['CENTER']=$in['CENTER'];
         $vals_at['VALUE_NEW']="to_char(sysdate , 'DD/MM/YYYY HH24:MI:SS')";
         $vals_at['NOMETAB']=$xml_form->form['TABLE'];
         $vals_at['USERID']=$in['remote_userid'];
         $vals_at['MODDT']="sysdate";
         $vals_at['VAR']='TIME_SIG';
         $vals_at['ACTION']="Change/update by Investigator";
         $sql3->insert($vals_at, "S_X_".$service,$pk);*/
        //	$conn->commit();
        $query = new query($this -> conn);
        
        //Aggiornamento storico e tabella firme globali (SIGNSDV)
        $str = 'insert into S_' . $this -> service . '_SIGNSDV (select :username,sysdate,storico_id.nextval,t.* from ' . $this -> service . '_SIGNSDV t where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' )';
        $bind['USERNAME'] = $this -> session_vars['USERNAME'];
        $bind[$this -> config_service['PK_SERVICE']] = $this -> session_vars[$this -> config_service['PK_SERVICE']];
        $query -> ins_upd($str, $bind);
        $pk[$this -> config_service['PK_SERVICE']] = $values[$this -> config_service['PK_SERVICE']] = $this -> session_vars[$this -> config_service['PK_SERVICE']];
        $values['SITEID'] = $this -> session_vars['SITEID'];
        $values['SUBJID'] = $this -> session_vars['SUBJID'];
        $values['USERNAME'] = $this -> session_vars['USERNAME'];
        $values['SIGNDATE'] = 'sysdate';
        $query -> insertOrUpdate($values, $this -> service . '_SIGNSDV', $pk);
        
        //if (!$values['SITEID']){
	    //    print_r($values);
	    //    die();
        //}
        
		//Aggiornamento storico e tabella stato sdv per campo (SDV_STRATEGY_STATUS)
		//PIERHD-2209 - DM - Gestione firma singola visita!!
		$visitnumcond = "";
		if ($in['VISITNUM']>=0){
			//Singola visita
			$visitnumcond = " and visitnum = :VISITNUM ";
			$bind['VISITNUM'] = $in['VISITNUM'];
		}
        $str = 'insert into S_' . $this -> strategyStatusTable . ' (select sysdate,storico_id.nextval,t.* from ' . $this -> strategyStatusTable . ' t where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' '.$visitnumcond.' and nvl(signed,0)<>1 and nvl(valid,0)=1 )'; //Aggiunto valid anche per le righe da inserire nello storico?!
	    $query -> ins_upd($str, $bind);
	    //Sovrascrivo anche lo username imponendo l'utente che firma (il vecchio è nello storico).
	    $str = 'update ' . $this -> strategyStatusTable . ' set signed=1,last_sign_date=sysdate, userid=:USERNAME where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' '.$visitnumcond.' and nvl(signed,0)<>1 and nvl(valid,0)=1';
        $query -> ins_upd($str, $bind);
    }

    function CheckUserLogged($username) {
        //Controllo corrispondenza con userid loggato
        if (strtolower($username) == strtolower($this -> session_vars['remote_userid'])) {
            return true;
        } else {
            //Controllo corrispondenza con userid loggato
            return false;
        }
    }

    function isVisitFrozen($version, $visitnum) {
        if ($this -> isVersionFrozen($version))
            return true;
        $strategy = $this -> getStrategy($version);
        $primo_esame = array_shift($strategy[$visitnum]);
        if ($primo_esame[0]['FROZEN_VISIT'])
            return true;
        else
            return false;
    }

    function isEsamFrozen($version, $visitnum, $esam) {
        if ($this -> isVisitFrozen($version, $visitnum))
            return true;
        $strategy = $this -> getStrategy($version);
        if ($strategy[$visitnum][$esam][0]['FROZEN_ESAM'])
            return true;
        else
            return false;
    }

    function isVersionFrozen($version) {
        $strategy = $this -> getStrategy($version);
        $prima_visita = array_shift($strategy);
        $primo_esame = array_shift($strategy);
        if ($primo_esame[0]['FROZEN'])
            return true;
        else
            return false;
    }

    function isVisitFrozenCached($strategy, $version, $visitnum) {
    	if ($this -> isVersionFrozenCached($strategy, $version)) {
    		return true;
		}
    		//$strategy = $this -> getStrategy($version);
    		$primo_esame = array_shift($strategy[$visitnum]);
    		if ($primo_esame[0]['FROZEN_VISIT']){
    			return true;
    		}else{
    			return false;
    		}
    }
    function isEsamFrozenCached($strategy, $version, $visitnum, $esam) {
    	if ($this -> isVisitFrozenCached($strategy, $version, $visitnum)) {
    		return true;
		}
    		//$strategy = $this -> getStrategy($version);
    		if ($strategy[$visitnum][$esam][0]['FROZEN_ESAM']){
    			return true;
		    }else{
		    	return false;
		    }
    }
    function isVersionFrozenCached($strategy, $version) {
    	//$strategy = $this -> getStrategy($version);
    	$prima_visita = array_shift($strategy);
    	$primo_esame = array_shift($strategy);
    	if ($primo_esame[0]['FROZEN']){
    		return true;
    	}else{
    		return false;
    	}
    }

    function saveStrategyStep1() {
    	//ini_set('max_execution_time', 300*2);
        $version = $this -> session_vars['version'];
        if ($this -> isVersionFrozen($version)) {
            error_page($this -> session_vars['remote_userid'], 'Strategy already frozen. Go back and refresh the page.');
        }
        if ($version != $this -> getNewStrategyVersion()) {
            error_page($this -> session_vars['remote_userid'], 'Bad request. Go back and refresh the page.');
        }
        foreach ($this->session_vars['VISITS'] as $visitnum => $check) {
            foreach ($this->vlist->esams[$visitnum] as $esam => $currEsam) {
	        	if ($this->vlist->esams[$visitnum][$esam]['HIDESDV']=="yes"){
	        		continue;
	        	}
                $record['VISITNUM'] = $visitnum;
                $record['ESAM'] = $esam;
                $record['VERSION'] = $version;
                $xml = new xml_form();
                $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam]['XML']);
                foreach ($xml->fields as $currField) {
                    if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                        $record['FIELD'] = $currField['VAR'];
                        if($this->session_vars['VISITS_MAND'][$visitnum]){
                        	$record['MANDATORY'] = 1;
                        }else{
                        	$record['MANDATORY'] = 0;
                        }
                        $this -> saveStrategyRecord($record);
                    }
                }
            }
        }
        $this -> freezeVersion($version);
        $this -> conn -> commit();
    }

    function saveStrategyStep2() {
        $version = $this -> session_vars['version'];
        if ($version != $this -> getNewStrategyVersion()) {
            error_page($this -> session_vars['remote_userid'], 'Strategy already frozen. Go back and refresh the page.');
        }
        if ($this -> isVisitFrozen($version, $this -> session_vars['VISITNUM'])) {
            error_page($this -> session_vars['remote_userid'], 'Visit already frozen. Go back and refresh the page.');
        }

        foreach ($this->session_vars['ESAMS'] as $esam => $check) {
            $record['VISITNUM'] = $this -> session_vars['VISITNUM'];
            $record['ESAM'] = $esam;
            $record['VERSION'] = $version;
     		//Imposto esame corrente
            $xml = new xml_form();
            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$this -> session_vars['VISITNUM']][$esam]['XML']);
            foreach ($xml->fields as $currField) {
                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                    $record['FIELD'] = $currField['VAR'];
                    if($this->session_vars['ESAMS_MAND'][$esam]){
                    	$record['MANDATORY'] = 1;
                    }else{
                    	$record['MANDATORY'] = 0;
                    }
                    $this -> saveStrategyRecord($record);
                }
            }
            //Gestione sub se è main-sub
            $vlesam = $this->vlist->esams[$record['VISITNUM']][$record['ESAM']];
            if ($vlesam['MAIN']=="yes"){
            	//Carico la sub e imposto anche quei fields
            	$record['ESAM'] = $esam+1; //Modifico qui la variabile ESAM della riga da salvare!!
	            $xml = new xml_form();
	            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$this -> session_vars['VISITNUM']][$record['ESAM']]['XML']);
	            foreach ($xml->fields as $currField) {
	                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
	                    $record['FIELD'] = $currField['VAR'];
	                    if($this->session_vars['ESAMS_MAND'][$esam]){
	                    	$record['MANDATORY'] = 1;
	                    }else{
	                    	$record['MANDATORY'] = 0;
	                    }
	                    $this -> saveStrategyRecord($record);
	                }
	            }
            }
            //End foreach
        }
        $this -> freezeVisit($version, $this -> session_vars['VISITNUM']);
        $this -> conn -> commit();
    }

    function freezeVisit($version, $visitnum) {
        $str = 'update ' . $this -> strategyTable . ' set frozen_esam=1,frozen_visit=1 where version=:version and visitnum=:visitnum';
        $query = new query($this -> conn);
        $bind['VERSION'] = $version;
        $bind['VISITNUM'] = $visitnum;
        $query -> ins_upd($str, $bind);
        // GENHD-858 aggiungo il commit ad ogni aggiornamento
        $this -> conn -> commit();

    }

    function freezeVersion($version) {
        $str = 'update ' . $this -> strategyTable . ' set DATE_VERSION=sysdate, frozen=1,frozen_esam=1,frozen_visit=1 where version=:version';
        $query = new query($this -> conn);
        $bind['VERSION'] = $version;
        $query -> ins_upd($str, $bind);
        // GENHD-858 aggiungo il commit ad ogni aggiornamento
        $this -> conn -> commit();

        $this -> initializeSDV();
    }

    function saveStrategyStep3() {
        $version = $this -> session_vars['version'];
        if ($version != $this -> getNewStrategyVersion()) {
            error_page($this -> session_vars['remote_userid'], 'Strategy already frozen. Go back and refresh the page.');
        }
        if ($this -> isEsamFrozen($version, $this -> session_vars['VISITNUM'], $this -> session_vars['ESAM'])) {
            error_page($this -> session_vars['remote_userid'], 'Esam already frozen. Go back and refresh the page.');
        }
        if ($this -> session_vars['VISITNUM'] != '' && $this -> session_vars['ESAM'] != '')
            $this -> cleanStrategy($version, $this -> session_vars['VISITNUM'], $this -> session_vars['ESAM']);
        $record['VERSION'] = $version;
        $record['VISITNUM'] = $this -> session_vars['VISITNUM'];
        $record['ESAM'] = $this -> session_vars['ESAM'];
        //var_dump($this->session_vars);
        //die("QUA");
        foreach ($this->session_vars['FIELDS'] as $field => $check) {
            $record['FIELD'] = $field;
            if ($this->session_vars['FIELDS_MAND'][$field]){
            	$record['MANDATORY'] = 1;
            }else{
            	$record['MANDATORY'] = 0;
            }
            if (isset($this->session_vars['MAND_FIELDS'][$field])){
	            if ($this->session_vars['MAND_FIELDS'][$field]){
	            	$record['MANDATORY'] = 1;
	            }else{
	            	$record['MANDATORY'] = 0;
	            }
            }
            if ($this -> session_vars['FREEZE_SDV']){
                $record['FROZEN_ESAM'] = 1;
            }
            //var_dump($record);
            $this -> saveStrategyRecord($record);
        }
        $record['ESAM'] = $record['ESAM'] + 1;
        foreach ($this->session_vars['FIELDS_SUB'] as $field => $check) {
            $record['FIELD'] = $field;
            //die("TODO MAINSUB!");
            if ($this->session_vars['MAND_FIELDS_SUB'][$field]){
            	$record['MANDATORY'] = 1;
            }else{
            	$record['MANDATORY'] = 0;
            }
            if ($this -> session_vars['FREEZE_SDV']){
                $record['FROZEN_ESAM'] = 1;
            }
            $this -> saveStrategyRecord($record);
        }
        $this -> conn -> commit();
    }

    function cleanStrategy($version, $visitnum = null, $esam = null) {
        if ($esam != null) {
            if ($this -> vlist -> esams[$visitnum][$esam]['MAIN'] != '')
                $str = 'delete from ' . $this -> strategyTable . ' where version=:version and visitnum=:visitnum and (esam=:esam or esam=(:esam+1) ) and nvl(frozen_esam,0)<>1';
            else
                $str = 'delete from ' . $this -> strategyTable . ' where version=:version and visitnum=:visitnum and esam=:esam and nvl(frozen_esam,0)<>1';
        } else if ($visitnum != null) {
            $str = 'delete from ' . $this -> strategyTable . ' where version=:version and visitnum=:visitnum and nvl(frozen_esam,0)<>1';
        } else {
            $str = 'delete from ' . $this -> strategyTable . ' where version=:version and nvl(frozen_esam,0)<>1';
        }
        //Logger::send('delete');
        //Logger::send($str);
        $bind['VERSION'] = $version;
        $bind['VISITNUM'] = $visitnum;
        $bind['ESAM'] = $esam;
        $query = new query($this -> conn);
        $query -> ins_upd($str, $bind);
    }

    function getLastStrategyVersion() {
    	if (!isset($_SESSION['SDV_LAST_STRATEGY'])){
	        $str = 'select max(version) VERSION from ' . $this -> strategyTable . ' where frozen=1';
	        $sql = new query($this -> conn);
	        $sql -> get_row($str);
	        $_SESSION['SDV_LAST_STRATEGY'] = $sql -> row['VERSION'] - 0;
    	}
        return $_SESSION['SDV_LAST_STRATEGY'];
    }

    function getNewStrategyVersion() {
        return 1;
        //decommentare quando si creano le versioni
        //return $this->getLastStrategyVersion()+1;
    }

    function setTabMenu() {
        global $filetxt;
        //			echo $in['remote_userid'];
        $filetxt = preg_replace("/<!--fulluserid-->/", $this -> session_vars['remote_userid'], $filetxt);
        $remote_userid = substr($this -> session_vars['remote_userid'], 0, 3);
        $filetxt = preg_replace("/<!--userid-->/", $remote_userid, $filetxt);
    }

    function getStrategyFormJs(){
    	$js = "";
    	$js.='<script language="javascript">';
    	$js .= '
    		function checkStrategy(form){
    			//alert(form);
    			//for (i=0;i<form.length;i++){
    			//	alert(form.elements[i].name+\': \'+form.elements[i].value);
    			//}
    			already_checked = $(form).find(\'i.checkedImage\').length;
    			if($(form).find(\':checkbox:checked\').length==0 && already_checked == 0){
    				alert(\'At least one checkbox must be selected\');
    				return false;
    			}
    			domanda = \'Are you sure? The data will be frozen and you cannot change them anymore. Click on OK to confirm.\';
    			return confirm(domanda);
    		}
    		function checkStrategyEsam(form){
    			domanda = \'Are you sure? The data will be frozen and you cannot change them anymore. Click on OK to confirm.\';
    			if($(form).find(\':checkbox:checked\').length==0){
    				alert(\'At least one field name must be selected\');
    				return false;
    			}
    			if($(\'#sdv_form_button\').val()==\'FREEZE_SDV\' && !confirm(domanda)){
    				return false;
    			}
    			return true;
    		}
			';
    	$js.='</script>';
    	$js.='<script language="javascript">';
    	$js.= '
    		function checkStrategyCheckboxes(form){
    			var nocheck = ($(form).find(\':checkbox:checked\').length==0);
    			var action = $(\'#sdv_form_button\').val();
    			if(nocheck){
    				alert(\'At least one field name must be selected.\');
    				return false;
    			}
    			if(action=="FREEZE_SDV"){
	    			return confirm(\'Are you sure? The data will be frozen and you cannot change them anymore. Click on "ok" to confirm.\');
    			}
    			return true;
    		}
			';
    	$js.='</script>';
    	return $js;
    }
    
    function defineStrategyStep1($version = null, $readOnly = false) {
        if ($readOnly) {
            $actionPrefix = 'readStrategyStep';
        } else {
            $actionPrefix = 'defineStrategyStep';
        }
        //echo($actionPrefix);
        if ($version == null)
            $version = $this -> getNewStrategyVersion();
        $strategy = $this -> getStrategy($version);
        //var_dump($this->session_vars);
        //var_dump($strategy);
        //die();
        $css = $this -> getCSS();
        $js = $this->getStrategyFormJs();
        $html = $css . $js. '<br/><br/><form method="POST" onsubmit="return checkStrategy(this);" ><table class="strategyDefinition" align="center" cellpadding="4"><tr class="titolo"><th>VISIT NAME</th><th>SDV Enabled</th><th>Mandatory</th></tr>';
        foreach ($this->vlist->visitnums as $visitnum => $currVisit) {
        	$checkedSTR="";
        	$checkedMAND="";
            if ($strategy[$visitnum]){
                $checkedSTR = ' checked="checked" ';
            }
            $count_mand_1 = 0;
            $count_mand_0 = 0;
            //var_dump($strategy[$visitnum]);
            foreach ($strategy[$visitnum] as $e => $erow){
            	foreach ($erow['FIELDS'] as $f){
	            	if ($f['MANDATORY']){
	            		$count_mand_1++;
	            	}else{
	            		$count_mand_0++;
	            	}
            	}
            }
            //echo("QUA3<hr/>");
            //echo "VISIT: {$visitnum} ### MAND0: {$count_mand_0} -> MAND1: {$count_mand_1}<hr/>";
            if ($count_mand_0==0 && $count_mand_1>0){
            	$checkedMAND=' checked="checked" ';
            }
            if ($this -> isVisitFrozenCached($strategy, $version, $visitnum)) {
                $frozen_visit = true;
                if ($this -> isVersionFrozenCached($strategy, $version))
                    $frozen = true;
            } else {
                $frozen_visit = false;
                foreach ($this->vlist->esams[$visitnum] as $esam => $esamDetails) {
                	if ($this -> isEsamFrozenCached($strategy, $version, $visitnum, $esam))
                        $frozen_visit = true;
                }
            }
            //die("QUA4<hr/>");
            $html .= '<tr class="titolo">';
            $html .= '<td class="destra" ><a class="linkVisitStrategy linkStrategy" href="?module=SDV&sdv_action=' . $actionPrefix . '2&version=' . $version . '&VISITNUM=' . $visitnum . '" >' . $currVisit['TEXT'] . '</td>';
            if ($frozen_visit || $readOnly) {
            	if ($checkedSTR){
					$html .= '<td class="input" align="center" ><i class="fa fa-check-square-o checkedImage"></i></td>';
                }else{
                    $html .= '<td class="input" align="center" ><i class="fa fa-square-o"></i></td>';
				}
				if ($count_mand_1>0 && $count_mand_0==0){
					$html .= '<td class="input" align="center" ><i class="fa fa-check-square-o checkedImage"></i></td>';
				}else if ($count_mand_1>0 && $count_mand_0>0){
					$html .= '<td class="input" align="center" ><i class="fa fa-check-square"></i></td>';
				}else{
					$html .= '<td class="input" align="center" ><i class="fa fa-square-o"></i></td>';
				}
            } else {
            	$html .= '<td class="input" align="center" ><input type="checkbox" ' . $checkedSTR. ' name="VISITS[' . $visitnum . ']" value="1" /></td>';
            	$html .= '<td class="input" align="center" ><input type="checkbox" ' . $checkedMAND. ' name="VISITS_MAND[' . $visitnum . ']" value="1" /></td>';
            }
            $html .= '</tr>';
            //die("<hr/>QUA2<hr/>");
        }
        $html .= '</table>
		<input type="hidden" name="module" value="SDV"/>
		<input type="hidden" name="sdv_action" value="saveStrategyStep1"/>
		<input type="hidden" name="version" value="' . $version . '"/>
		';
        if (!$frozen && !$readOnly)
            $html .= '
		<table align=center><tr><td>
		<input type="submit" value="FREEZE" name="FREEZE_SDV" /></td></tr></table>';
        $html .= '
		</form>
		
		';

        return $html;
    }

    function defineStrategyStep2($version, $visitnum, $readOnly = false) {
        if ($readOnly) {
            $actionPrefix = 'readStrategyStep';
        } else {
            $actionPrefix = 'defineStrategyStep';
        }
        if ($version == null)
            $version = $this -> getNewStrategyVersion();
        $strategy = $this -> getStrategy($version);

        //echo "<pre>";
        //print_r($this->vlist);
        //echo "</pre>";
        //$vobj = $this->getVisiteExamsData ( $this->xml_dir . '/visite_exams.xml' );
        //echo "<pre>";
        //print_r($this->vlist);
        //echo "</pre>";
        
        $css = $this -> getCSS();
        $js = $this->getStrategyFormJs();
        $html = $css . $js. '<br/><br/><form method="POST" onsubmit="return checkStrategy(this);" ><table align=center class="strategyDefinition" >
		<tr class="titolo"><th colspan=2><a href="index.php?module=SDV&sdv_action=defineStrategyStep1&version='.$version.'" style="color:black;" >Back to visit list</a></th></tr>
		<tr class="titolo"><th colspan=2>VISIT: ' . $this -> vlist -> visitnums[$visitnum]['TEXT'] . '</th></tr>
		<tr class="titolo"><th colspan=2><a href="?module=SDV&sdv_action=' . $actionPrefix . '1&version=' . $version . '">Back to visit page</a></th></tr>
		<tr class="titolo"><th>ESAM NAME</th><th>SDV Enabled</th><th>Mandatory</th></tr>';
        //Logger::send($this -> vlist -> esams[$visitnum]);
        foreach ($this->vlist->esams[$visitnum] as $esam => $currEsam) {
            if ($currEsam['SUB'] != ''){
                continue;
            }
            //Se HideSDV, continue
            if ($currEsam['HIDESDV']=="yes"){
            	continue;
            }
            $checkedSTRAT="";
            $checkedMAND="";
            if ($strategy[$visitnum][$esam] || ($this -> isMain( $visitnum, $esam) && $strategy[$visitnum][$esam+1]) ){
            	$checkedSTRAT= ' checked="checked" ';
            }
            $count_mand_1 = 0;
            $count_mand_0 = 0;
            foreach ($strategy[$visitnum][$esam]['FIELDS'] as $f){
            	if ($f['MANDATORY']){
            		$count_mand_1++;
            	}else{
            		$count_mand_0++;
            	}
            }
            if ($this -> isMain( $visitnum, $esam)){
            	foreach ($strategy[$visitnum][$esam+1]['FIELDS'] as $f){
            		if ($f['MANDATORY']){
            			$count_mand_1++;
            		}else{
            			$count_mand_0++;
            		}
            	}
            }

            if ($count_mand_0==0 && $count_mand_1>0){
            	$checkedMAND=' checked="checked" ';
            }
            //var_dump($strategy[$visitnum][$esam]);
            if ($this -> isEsamFrozenCached($strategy, $version, $visitnum, $esam) || ($this -> isMain( $visitnum, $esam) && $this -> isEsamFrozenCached($strategy, $version, $visitnum, $esam+1)) ) {
                $frozen_esam = true;
                if ($this -> isVisitFrozenCached($strategy, $version, $visitnum))
                    $frozen_visit = true;
            } else {
                $frozen_esam = false;
            }
            $html .= '<tr>';
            $html .= '<td class="destra"><a class="linkEsamStrategy linkStrategy" href="?module=SDV&sdv_action=' . $actionPrefix . '3&version=' . $version . '&VISITNUM=' . $visitnum . '&ESAM=' . $esam . '" >' . $currEsam['TESTO'] . '</td>';
            if ($frozen_esam || $frozen_visit || $readOnly) {
            	if ($checkedSTRAT){
                    $html .= '<td class="input"><i class="fa fa-check-square-o checkedImage"></i></td>';
                }else{
                    $html .= '<td class="input"><i class="fa fa-square-o"></i></td>';
                }
                if ($count_mand_1>0 && $count_mand_0==0){
                	$html .= '<td class="input"><i class="fa fa-check-square-o checkedImage"></i></td>';
                }else if ($count_mand_1>0 && $count_mand_0>0){
                	$html .= '<td class="input"><i class="fa fa-check-square"></i></td>';
                }else{
                	$html .= '<td class="input"><i class="fa fa-square-o"></i></td>';
                }
            } else {
            	$html .= '<td class="input"><input type="checkbox" ' . $checkedSTRAT. ' value="1" name="ESAMS[' . $esam . ']" /></td>';
                $html .= '<td class="input"><input type="checkbox" ' . $checkedMAND . ' value="1" name="ESAMS_MAND[' . $esam . ']" /></td>';
            }
            $html .= '</tr>';
        }
        $html .= '</table>
		<input type="hidden" name="VISITNUM" value="' . $visitnum . '"/>
		<input type="hidden" name="module" value="SDV"/>
		<input type="hidden" name="sdv_action" value="saveStrategyStep2"/>
		<input type="hidden" name="version" value="' . $version . '"/>
		';
        if (!$frozen_visit && !$readOnly)
            $html .= '
		<table align=center><tr><td>
		<input type="submit" value="FREEZE" name="FREEZE_SDV" /></td></tr></table>';
        $html .= '
		</form>';
        return $html;
    }

    function defineStrategyStep3($version, $visitnum, $esam, $readOnly = false) {
        if ($readOnly) {
            $actionPrefix = 'readStrategyStep';
        } else {
            $actionPrefix = 'defineStrategyStep';
        }
        if ($version == null)
            $version = $this -> getNewStrategyVersion();
        $strategy = $this -> getStrategy($version);
        //var_dump($_SESSION['SDV_STRATEGY_OBJECT']);
        //var_dump($version);
        //var_dump($strategy);
        $css = $this -> getCSS();
        $js = $this->getStrategyFormJs();
        ////Logger::send('qui');
        //die("define3");
        $html = $css . $js. '<br/><br/><form method="POST" onsubmit="return checkStrategyCheckboxes(this);" ><table class="strategyDefinition" align=center>
		<tr class="titolo"><th colspan=2><a href="index.php?module=SDV&sdv_action=defineStrategyStep2&version='.$version.'&VISITNUM='.$visitnum.'" style="color:black;" >VISIT: ' . $this -> vlist -> visitnums[$visitnum]['TEXT'] . ' (click to go back)</a></th></tr>
		<tr class="titolo"><th colspan=2>ESAM: ' . $this -> vlist -> esams[$visitnum][$esam]['TESTO'] . '</th></tr>
		<tr class="titolo"><th colspan=2><a href="?module=SDV&sdv_action=' . $actionPrefix . '1&version=' . $version . '">Back to visit page</a> <a href="?module=SDV&sdv_action=' . $actionPrefix . '2&version=' . $version . '&VISITNUM=' . $visitnum . '">Back to exam page</a></th></tr>
		<tr class="titolo"><th>FIELD LABEL ( FIELD VAR ) </th>';
		$html.='<th>SDV Enabled<br/><input onclick="if($(this).prop(\'checked\'))$(\'.ckb_strat\').prop(\'checked\',\'checked\');else $(\'.ckb_strat\').removeAttr(\'checked\');" name="all_sdv" type="checkbox" value="1" />all</th>';
		$html.='<th>Mandatory<br/><input onclick="if($(this).prop(\'checked\'))$(\'.ckb_mand\').prop(\'checked\',\'checked\');else $(\'.ckb_mand\').removeAttr(\'checked\');" name="all_sdv_mand" type="checkbox" value="1" />all</th>';
		$html.='</tr>';
        if (!$this -> vlist -> esams[$visitnum][$esam]['MAIN']) {
            $xml = new xml_form();
            //die ("CIAO");
            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam]['XML']);
            //die("MUOR");
            $frozen = false;
            //arrivato qui
            //Logger::send($xml -> fields);
            foreach ($xml->fields as $currField) {
                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                    $checkedSTRAT="";
                    $checkedMAND="";
                    //var_dump($strategy[$visitnum][$esam]['FIELDS']);
                	if ($strategy[$visitnum][$esam]['FIELDS'][$currField['VAR']]){
                		$checkedSTRAT= ' checked="checked" ';
                	}
                	if ($strategy[$visitnum][$esam]['FIELDS'][$currField['VAR']]['MANDATORY']){
                		$checkedMAND= ' checked="checked" ';
                	}
                    //$testo = $currField['TESTO'];
                	$testo= str_replace("__EMPTY_STRING__","",$currField['TESTO'])." ( ".$currField['VAR']." )" ;
                	if (preg_match('/checkbox/i', $currField['TYPE'])) {
                        foreach ($currField['VALUE'] as $check => $check_text) {
                            if (trim($check_text) != '')
                            	$testo .= '<br/>[' . mlOut($check_text,null). ']';
                        }
                    }
                    if (preg_match('/radio/i', $currField['TYPE'])) { //GENHD-296
                    	foreach ($currField['VALUE'] as $check => $check_text) {
                    		if (trim($check_text) != '')
                    			$testo .= '<br/>[' . mlOut($check_text,null). ']';
                    	}
                    }
                    if (isset($currField['TESTO_SDV']))
                        $testo = $currField['TESTO_SDV'];
                    // if ($this -> isEsamFrozenCached($strategy, $version, $visitnum, $esam)) {
                    if ($this -> isEsamFrozenCached($strategy, $version, $visitnum, $esam)) {
                        $frozen = true;
                        // $frozen= false;
                    }
                    $html .= '<tr>';
                    $html .= '<td class="destra">' . $testo . '</td>';
                    if ($frozen || $readOnly) {
                    	if ($checkedSTRAT){
                            $html .= '<td class="input"><i class="fa fa-check-square-o checkedImage"></i></td>';
                        }else{
                            $html .= '<td class="input"><i class="fa fa-square-o"></i></td>';
                        }
                        if ($checkedMAND){
                        	$html .= '<td class="input"><i class="fa fa-check-square-o checkedImage"></i></td>';
                        }else{
                        	$html .= '<td class="input"><i class="fa fa-square-o"></i></td>';
                        }
                    } else {
                    	$html .= '<td class="input"><input class="ckb_strat" type="checkbox" ' . $checkedSTRAT. ' name="FIELDS[' . $currField['VAR'] . ']" value="1" /></td>';
                        $html .= '<td class="input"><input class="ckb_mand" type="checkbox" ' . $checkedMAND . ' name="FIELDS_MAND[' . $currField['VAR'] . ']" value="1" /></td>';
                    }
                    $html .= '</tr>';
                }
            }
            $html .= '</table>
				<input type="hidden" name="VISITNUM" value="' . $visitnum . '"/>
				<input type="hidden" name="ESAM" value="' . $esam . '"/>
				<input type="hidden" name="module" value="SDV"/>
				<input type="hidden" name="sdv_action" value="saveStrategyStep3"/>
				<input type="hidden" name="version" value="' . $version . '"/>
				<input type="hidden" id="sdv_form_button" name="sdv_form_button" value=""/>
				';
		            if (!$frozen && !$readOnly)
		                $html .= '
				<table align=center><tr><td>
				<input type="submit" value="SAVE" name="SAVE_SDV" onclick="$(\'#sdv_form_button\').val(\'SAVE_SDV\');" />
				<input type="submit" value="FREEZE" name="FREEZE_SDV" onclick="$(\'#sdv_form_button\').val(\'FREEZE_SDV\');" /></td></tr></table>';
		            $html .= '
				</form>';
        } else {
        	//MAIN_SUB!
        	$fields = array();
            $xml = new xml_form();
            //die("MAIN");
            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam]['XML']);
            $frozen = false;
            foreach ($xml->fields as $currField) {
                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                	$checkedSTRAT="";
                	$checkedMAND="";
                    if ($strategy[$visitnum][$esam]['FIELDS'][$currField['VAR']]){
                    	$checkedSTRAT= ' checked="checked" ';
                    }
                    if ($strategy[$visitnum][$esam]['FIELDS'][$currField['VAR']]['MANDATORY']){
                    	$checkedMAND= ' checked="checked" ';
                    }
                    //$testo = $currField['TESTO'];
                    $testo= str_replace("__EMPTY_STRING__","",$currField['TESTO'])." ( ".$currField['VAR']." )" ;
                    if (preg_match('/checkbox/i', $currField['TYPE'])) {
                        foreach ($currField['VALUE'] as $check => $check_text) {
                            if (trim($check_text) != '')
                                $testo .= '<br/>[' . $check_text . ']';
                        }
                    }
                    if (preg_match('/radio/i', $currField['TYPE'])) { //GENHD-296
                    	foreach ($currField['VALUE'] as $check => $check_text) {
                    		if (trim($check_text) != '')
                    			$testo .= '<br/>[' . mlOut($check_text,null). ']';
                    	}
                    }
                    if (isset($currField['TESTO_SDV']))
                        $testo = $currField['TESTO_SDV'];
                    if ($this -> isEsamFrozenCached($strategy, $version, $visitnum, $esam)) {
                        $frozen = true;
                    }
                    $f = array();
                    $f['TESTO'] = $testo;
                    $f['CHECKED_STRAT'] = $checkedSTRAT;
                    $f['CHECKED_MAND'] = $checkedMAND;
                    $f['VAR'] = $currField['VAR'];
                    $f['FORMARRAY'] = "FIELDS";
                    $fields[] = $f;
                }
            }
            $xml = new xml_form();
            $esam_sub = $esam + 1;
            $xml -> xml_form_by_file($this -> xml_dir . '/' . $this -> vlist -> esams[$visitnum][$esam_sub]['XML']);
            foreach ($xml->fields as $currField) {
                if ($currField['VAR'] != '' && $currField['TYPE'] != 'hidden' && $currField['TYPE'] != '' && $currField['TB'] != 'no') {
                	$checkedSTRAT="";
                	$checkedMAND="";
                    if ($strategy[$visitnum][$esam_sub]['FIELDS'][$currField['VAR']]){
                    	$checkedSTRAT= ' checked="checked" ';
                    }
                    if ($strategy[$visitnum][$esam_sub]['FIELDS'][$currField['VAR']]['MANDATORY']){
                    	$checkedMAND= ' checked="checked" ';
                    }
                    //$testo = $currField['TESTO'];
                    $testo= str_replace("__EMPTY_STRING__","",$currField['TESTO'])." ( ".$currField['VAR']." )" ;
                    if (preg_match('/checkbox/i', $currField['TYPE'])) {
                        foreach ($currField['VALUE'] as $check => $check_text) {
                            if (trim($check_text) != '')
                                $testo .= '<br/>[' . $check_text . ']';
                        }
                    }
                    if (preg_match('/radio/i', $currField['TYPE'])) { //GENHD-296
                    	foreach ($currField['VALUE'] as $check => $check_text) {
                    		if (trim($check_text) != '')
                    			$testo .= '<br/>[' . mlOut($check_text,null). ']';
                    	}
                    }
                    if (isset($currField['TESTO_SDV']))
                        $testo = $currField['TESTO_SDV'];
               		if ($this -> isEsamFrozenCached($strategy, $version, $visitnum, $esam_sub)) {
                        $frozen = true;
                    }
                    $f = array();
                    $f['TESTO'] = $testo;
                    $f['CHECKED_STRAT'] = $checkedSTRAT;
                    $f['CHECKED_MAND'] = $checkedMAND;
                    $f['VAR'] = $currField['VAR'];
                    $f['FORMARRAY'] = "FIELDS_SUB";
                    $fields[] = $f;
                }
            }
            foreach ($fields as $f){
            	$html .= '<tr>';
            	$html .= '<td class="destra">' . $f['TESTO']. '</td>';
            	if ($frozen || $readOnly) {
                    if ($f['CHECKED_STRAT']){
                        $html .= '<td class="input"><i class="fa fa-check-square-o checkedImage"></i></td>';
                    }else{
                        $html .= '<td class="input"><i class="fa fa-square-o"></i></td>';
                    }
                    if ($f['CHECKED_MAND']){
                    	$html .= '<td class="input"><i class="fa fa-check-square-o checkedImage"></i></td>';
                    }else{
                    	$html .= '<td class="input"><i class="fa fa-square-o"></i></td>';
                    }
                } else {
                    $html .= '<td class="input"><input class="ckb_strat" type="checkbox" ' . $f['CHECKED_STRAT'] . ' name="'.$f['FORMARRAY'].'[' . $f['VAR'] . ']" value="1" /></td>';
                    $html .= '<td class="input"><input class="ckb_mand" type="checkbox" ' . $f['CHECKED_MAND'] . ' name="MAND_'.$f['FORMARRAY'].'[' . $f['VAR'] . ']" value="1" /></td>';
                }
                $html .= '</tr>';
            }
            
            $html .= '</table>
		<input type="hidden" name="VISITNUM" value="' . $visitnum . '"/>
		<input type="hidden" name="ESAM" value="' . $esam . '"/>
		<input type="hidden" name="module" value="SDV"/>
		<input type="hidden" name="sdv_action" value="saveStrategyStep3"/>
		<input type="hidden" name="version" value="' . $version . '"/>
		<input type="hidden" id="sdv_form_button" name="sdv_form_button" value=""/>
		';
            if (!$frozen && !$readOnly)
                $html .= '
		<table align=center><tr><td>
		<input type="submit" value="SAVE" name="SAVE_SDV" onclick="$(\'#sdv_form_button\').val(\'SAVE_SDV\');" />
		<input type="submit" value="FREEZE" name="FREEZE_SDV" onclick="$(\'#sdv_form_button\').val(\'FREEZE_SDV\');" /></td></tr></table>';
            $html .= '
		</form>';
        }

        return $html;
    }

    function saveSDV() {

        //sistemare controllare questione date
        $bind[$this -> config_service['PK_SERVICE']] = $pk[$this -> config_service['PK_SERVICE']] = $status[$this -> config_service['PK_SERVICE']] = $this -> session_vars[$this -> config_service['PK_SERVICE']];
        $bind['VISITNUM'] = $pk['VISITNUM'] = $status['VISITNUM'] = $this -> session_vars['VISITNUM'];
        if ($this -> session_vars['VISITNUM_PROGR'] == '')
            $this -> session_vars['VISITNUM_PROGR'] = 0;
        $bind['VISITNUM_PROGR'] = $pk['VISITNUM_PROGR'] = $status['VISITNUM_PROGR'] = $this -> session_vars['VISITNUM_PROGR'];
        $bind['ESAM'] = $pk['ESAM'] = $status['ESAM'] = $this -> session_vars['ESAM'];
        if ($this -> session_vars['PROGR'] == '')
            $this -> session_vars['PROGR'] = 1;
        $bind['PROGR'] = $pk['PROGR'] = $status['PROGR'] = $this -> session_vars['PROGR'];
        //$currentStatus=$this->getStrategyStatus($status);
        $strategy = $this -> getStrategy();
        $status['SITEID'] = $this -> session_vars['SITEID'];
        $status['SUBJID'] = $this -> session_vars['SUBJID'];
        $status['VERSION'] = 1;

        //query inserimento nello storico
        $str = 'insert into S_' . $this -> strategyStatusTable . ' (select sysdate,storico_id.nextval,t.* from ' . $this -> strategyStatusTable . ' t where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field )';

        //$bind['USERNAME'] = $this -> session_vars['remote_userid'];
        foreach ($strategy[$this->session_vars['VISITNUM']][$this->session_vars['ESAM']]['FIELDS'] as $field => $currStrategy) {
            $filters[$this -> config_service['PK_SERVICE']] = $bind[$this -> config_service['PK_SERVICE']];
            $filters['VISITNUM'] = $bind['VISITNUM'];
            $filters['VISITNUM_PROGR'] = $bind['VISITNUM_PROGR'];
            $filters['ESAM'] = $bind['ESAM'];
            $filters['PROGR'] = $bind['PROGR'];
            $filters['VERSION'] = 1;
            $filters['FIELD'] = $field;
            if ($this -> userHasToReportSDV($filters)) {
                $bind['FIELD'] = $pk['FIELD'] = $status['FIELD'] = $field;
                $status['DATE_VALIDATION'] = 'sysdate';
                $status['PROTOCOL_VIOLATION'] = $this -> session_vars['RPV_FIELDS'][$field];
                $status['SDV_NOTE'] = $this -> session_vars['NOTE_FIELDS'][$field];
                $status['USERID'] = $this -> session_vars['remote_userid'];
                if ($this -> session_vars['SDV_FIELDS'][$field]) {
                    $status['VALID'] = 1;
                    $status['DATE_VALIDATION'] = 'sysdate';
                } else {
                    $status['VALID'] = '0';
                    $status['DATE_VALIDATION'] = '';
                }
                $query = new query($this -> conn);

                //inserimento nello storico
                $query -> ins_upd($str, $bind);

                $query -> insertOrUpdate($status, $this -> strategyStatusTable, $pk);
            }
        }

    }

    function resetVariableAfterEq($eq_int, $pk_service, $siteid, $subjid, $visitnum, $visitnum_progr, $esam, $progr, $field, $version = 1) {
        //      Logger::send(func_get_args());
        $query = new query($this -> conn);
        $pk[$this -> config_service['PK_SERVICE']] = $bind[$this -> config_service['PK_SERVICE']] = $pk_service;
        $pk['VISITNUM'] = $bind['VISITNUM'] = $visitnum;
        if ($visitnum_progr == '')
            $visitnum_progr = 0;
        $pk['VISITNUM_PROGR'] = $bind['VISITNUM_PROGR'] = $visitnum_progr;
        $pk['ESAM'] = $bind['ESAM'] = $esam;
        if ($progr == '')
            $progr = 1;
        $pk['PROGR'] = $bind['PROGR'] = $progr;
        $pk['FIELD'] = $bind['FIELD'] = $field;
        $pk['VERSION'] = $bind['VERSION'] = $version;

        //Logica di controllo
        $esamdata = $this->vlist->esams[$bind['VISITNUM']][$bind['ESAM']];
		$url = str_replace("index.php", "", $_SERVER['SCRIPT_FILENAME'])."xml/".$esamdata['XML'];
		$form = new xml_form();
		$form->xml_form_by_file($url);
		$table = $form->form['TABLE'];

		//var_dump($bind);
		//var_dump($this->session_vars);
		//die();
		
        $str = 'insert into S_' . $this -> strategyStatusTable . ' (select sysdate,storico_id.nextval,t.* from ' . $this -> strategyStatusTable . ' t where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field )';
        $query -> ins_upd($str, $bind);
        $bind['VALID'] = '';
        $check = 'select valid from ' . $this -> strategyStatusTable . ' where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and esam=:esam and visitnum_progr=:visitnum_progr and progr=:progr and version=:version and field=:field';
        if ($query -> get_row($check, $pk)) {
            if ($query -> row['VALID']) {
                $bind['QUERYID'] = $eq_int;
            }
            if ($query -> row['VALID'] !== '') {
                $bind['VALID'] = '0';
            }
        }
		//Riapro status table
        unset($bind['USERNAME']);
        //      $str='delete '.$this->strategyStatusTable.'  where '.$this->config_service['PK_SERVICE'].'=:'.$this->config_service['PK_SERVICE'].' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field ';
        //      $query->ins_upd($str,$bind);
        $bind['SITEID'] = $siteid;
        $bind['SUBJID'] = $subjid;

        $bind['DATE_VALIDATION'] = '';
        $bind['USERID'] = $this -> session_vars['remote_userid'];
        $bind['SIGNED'] = '';
        $bind['LAST_SIGN_DATE'] = '';
        //Questo update riapre l'SDV
        $query -> insertOrUpdate($bind, $this -> strategyStatusTable, $pk);
		//var_dump($bind);
		//var_dump($pk);
		//die();
        //$bind['FIELD'] = $this->session_vars['EQFIELD'];
		//$bind['EQ_INT'] = $eq_int;
		//$bind['PK_SERVICE'] = $bind[$this->config_service['PK_SERVICE']];
		
		
        /*
		
		$query = new query ( $this->conn );
		$sql_txt = "SELECT {$this->session_vars['EQFIELD']} FROM {$table} WHERE CODPAT=:PK_SERVICE AND VISITNUM=:VISITNUM AND ESAM=:ESAM AND VISITNUM_PROGR=:VISITNUM_PROGR AND PROGR=:PROGR ";
		$query->set_sql($sql_txt);
		$query->exec ( $sql_txt, $bind);
		$query->get_row();
		var_dump($query->row);
		$tabfield = $query->row[$this->session_vars['EQFIELD']]."<br/>";
		
		$query = new query ( $this->conn );
		$sql_txt = "SELECT VALORE FROM {$this->service}_EQFIELD WHERE EQ_INT = :EQ_INT AND FIELD = :TABFIELD AND CODPAT=:PK_SERVICE AND VISITNUM=:VISITNUM AND ESAM=:ESAM AND VISITNUM_PROGR=:VISITNUM_PROGR AND PROGR=:PROGR ";
		$query->set_sql($sql_txt);
		$query->exec ( $sql_txt, $bind);
		$query->get_row();
		var_dump($query->row);
		$eqfield = $query->row['VALORE']."<br/>";
		
		echo("TAB: {$tabfield}-->{$eqfield}");
		die();
		if ($tabfield != $eqfield){
			//echo "AGGIORNAMENTO!";
			//Storico
	        $str = 'insert into S_' . $this -> strategyStatusTable . ' (select sysdate,storico_id.nextval,t.* from ' . $this -> strategyStatusTable . ' t where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field )';
	        $query -> ins_upd($str, $bind);
	        $bind['VALID'] = '';
	        $check = 'select valid from ' . $this -> strategyStatusTable . ' where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and esam=:esam and visitnum_progr=:visitnum_progr and progr=:progr and version=:version and field=:field';
	        if ($query -> get_row($check, $pk)) {
	            if ($query -> row['VALID']) {
	                $bind['QUERYID'] = $eq_int;
	            }
	            if ($query -> row['VALID'] !== '') {
	                $bind['VALID'] = '0';
	            }
	        }
			//Riapro status table
	        unset($bind['USERNAME']);
	        //      $str='delete '.$this->strategyStatusTable.'  where '.$this->config_service['PK_SERVICE'].'=:'.$this->config_service['PK_SERVICE'].' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field ';
	        //      $query->ins_upd($str,$bind);
	        $bind['SITEID'] = $siteid;
	        $bind['SUBJID'] = $subjid;
	
	        $bind['DATE_VALIDATION'] = '';
	        $bind['SIGNED'] = '';
	        $bind['USERID'] = $this -> session_vars['remote_userid'];
			//Questo update riapre l'SDV
	        $query -> insertOrUpdate($bind, $this -> strategyStatusTable, $pk);
		}
        */
    }

    function setVariableForSDV($pk_service, $siteid, $subjid, $visitnum, $visitnum_progr, $esam, $progr, $field, $version = 1) {
    	//Logger::send("SETVARIABLESDV!");
    	//Logger::send(func_get_args());
    	//Logger::trace('setvar');
        //		Logger::send(func_get_args());
        //debug_print_backtrace();
        $query = new query($this -> conn);
        $pk[$this -> config_service['PK_SERVICE']] = $bind[$this -> config_service['PK_SERVICE']] = $pk_service;
        $pk['VISITNUM'] = $bind['VISITNUM'] = $visitnum;
        if ($visitnum_progr == '')
            $visitnum_progr = 0;
        $pk['VISITNUM_PROGR'] = $bind['VISITNUM_PROGR'] = $visitnum_progr;
        $pk['ESAM'] = $bind['ESAM'] = $esam;
        if ($progr == '')
            $progr = 1;
        $pk['PROGR'] = $bind['PROGR'] = $progr;
        $pk['FIELD'] = $bind['FIELD'] = $field;
        $pk['VERSION'] = $bind['VERSION'] = $version;
        $bind['USERNAME'] = $this -> session_vars['remote_userid'];
        $str = 'insert into S_' . $this -> strategyStatusTable . ' (select sysdate,storico_id.nextval,t.* from ' . $this -> strategyStatusTable . ' t where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field )';
        $query -> ins_upd($str, $bind);

        $bind['VALID'] = '';
        $check = 'select valid from ' . $this -> strategyStatusTable . ' where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and esam=:esam and visitnum_progr=:visitnum_progr and progr=:progr and version=:version and field=:field';
        if ($query -> get_row($check, $pk)) {
            if ($query -> row['VALID'] !== '') {
                $bind['VALID'] = '0';
            }
        }

        unset($bind['USERNAME']);
        //		$str='delete '.$this->strategyStatusTable.'  where '.$this->config_service['PK_SERVICE'].'=:'.$this->config_service['PK_SERVICE'].' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr and field=:field ';
        //		$query->ins_upd($str,$bind);
        $bind['SITEID'] = $siteid;
        $bind['SUBJID'] = $subjid;
        
        //if (!$bind['SITEID']){
        //	die("AAASSSDDD");
        //}

        $bind['DATE_VALIDATION'] = '';
        $bind['SIGNED'] = '';
        $bind['LAST_SIGN_DATE'] = '';
        
        $query -> insertOrUpdate($bind, $this -> strategyStatusTable, $pk);
    }

    function saveStrategyRecord($record) {
        //Logger::send($record);
        //sistemare controllare questione date
        $pk['VISITNUM'] = $strategy['VISITNUM'] = $record['VISITNUM'];
        $pk['ESAM'] = $strategy['ESAM'] = $record['ESAM'];
        $pk['VERSION'] = $strategy['VERSION'] = $record['VERSION'];
        $pk['FIELD'] = $strategy['FIELD'] = $record['FIELD'];
        $strategy['FROZEN_ESAM'] = $record['FROZEN_ESAM'];
        $strategy['FROZEN_VISIT'] = $record['FROZEN_VISIT'];
        $strategy['FROZEN'] = $record['FROZEN'];
        $strategy['MANDATORY'] = $record['MANDATORY'];
        $query = new query($this -> conn);
        $query -> insertOrUpdate($strategy, $this -> strategyTable, $pk);
        // GENHD-858 aggiungo il commit ad ogni aggiornamento
        $this -> conn -> commit();
    }
    
    function after_cancella_la_scheda($pk_service, $visitnum, $visitnum_progr, $esam, $progr , $center ){
    	//Logger::send("TRASH!");
    	//Logger::send(func_get_args());
    	//Logger::trace('trashvar');

       	$query = new query($this -> conn);
    	$pk[$this -> config_service['PK_SERVICE']] = $bind[$this -> config_service['PK_SERVICE']] = $pk_service;
    	$pk['VISITNUM'] = $bind['VISITNUM'] = $visitnum;
    	if ($visitnum_progr == '')
    		$visitnum_progr = 0;
    	$pk['VISITNUM_PROGR'] = $bind['VISITNUM_PROGR'] = $visitnum_progr;
    	$pk['ESAM'] = $bind['ESAM'] = $esam;
    	if ($progr == '')
    		$progr = 1;
    	$pk['PROGR'] = $bind['PROGR'] = $progr;
    	$bind['USERNAME'] = $this -> session_vars['remote_userid'];
    	
    	$str = 'insert into S_' . $this -> strategyStatusTable . ' (select sysdate,storico_id.nextval,t.* from ' . $this -> strategyStatusTable . ' t where ' . $this -> config_service['PK_SERVICE'] . '=:' . $this -> config_service['PK_SERVICE'] . ' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr )';
    	$query -> ins_upd($str, $bind);
    	//echo $str;
    	unset($bind['USERNAME']);
    	
    	$str='delete '.$this->strategyStatusTable.'  where '.$this->config_service['PK_SERVICE'].'=:'.$this->config_service['PK_SERVICE'].' and visitnum=:visitnum and visitnum_progr=:visitnum_progr and esam=:esam and progr=:progr ';
    	$query->ins_upd($str,$bind);
    	$this->conn->commit();
    	//echo $str;
    }

    /*
    function getVisiteExamsData($xml_file){
		$xml_parser=new my_xml_parser($xml_file);
		$this_node=new xml_node();
		$g=0;
		$retval = array();
		for ($i=0;$i<count($xml_parser->vals);$i++){
			$this_node->xml_node_by_array($xml_parser->vals[$i]);
			if ($this_node->type!='cdata'){

				if ($this_node->tag=='GROUP') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$retval['group'][$g]=$this_node->attributes;
					}
					if ($this_node->type=='close') {
						$g++;
					}
				}

				if ($this_node->tag=='VISIT') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$vis_num=$this_node->attributes['NUMBER']+0;
						$retval['group'][$g]['VISIT'][$vis_num]=$vis_num;
						$retval['visitnums'][$vis_num]=$this_node->attributes;
					}
				}
				if ($this_node->tag=='EXAM') {
					if ($this_node->type=='open' or $this_node->type=='complete') {
						$es_num=$this_node->attributes['NUMBER']+0;
						$retval['group'][$g]['ESAM'][$es_num]=$es_num;
						$retval['esams'][$vis_num][$es_num]=$this_node->attributes;
						$retval['xml'][$es_num]=$this_node->attributes['XML'];
					}
				}
				
			}
		}
		return $retval;

    }
    */
    
}
?>
