<?
putenv ( "NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1" );
require_once "libs/http_lib.inc";

include_once "config.inc";
include_once "libs/db.inc";
//include_once "form.inc";
//include_once "xml_page.inc";
include_once "libs/xml_parser_wl.inc";
include_once "libs/HTML_Parser.inc";

//Inizio XMR
include_once "study.inc.php";

$xmr = new xmrwf ( "study.xml", $conn );


$sub_service=str_replace($xmr->dir, "", $dir);
$sub_service=rtrim($sub_service, "/");
$sub_service=ltrim($sub_service, "/");
$xml_dir="$dir/xml";

//print_r($xmr);


if ($sub_service!=''){	
	foreach ($xmr->substudies as $key => $val){
		if ($val->prefix==$sub_service) $xmr=$val;				
		$xml_dir=str_replace("$sub_service/xml", "xml/$sub_service", $xml_dir);			
	}	
}



$xmr->setConfigParam();
$user=new user($conn, $in['remote_userid'], $xmr);

$config_service['filetxt']=$filetxt;

if (class_exists("Study_{$xmr->prefix}")){
	$class_name="Study_".$xmr->prefix;
}
else $class_name="Study";

$study_=new $class_name($xml_dir, $service, "visite_exams.xml", $conn, $in, $config_service, $user,false, $config_service['WF_NAME'], $xmr);


$vlist = $study_->vlist;
$es_name = $study_->es_name;
$es_form = $study_->es_form;
$patients_table = $study_->patient_table;
$coordinate = "{$study_->service}_COORDINATE";
$output = "<table border=1 width=95% align=center>";

$sql_query = "
			select table_name , column_name , data_type , data_length  from user_tab_columns where table_name like '{$xmr->prefix}%' and table_name not like '{$xmr->prefix}WF_%'
			";
//			echo $sql_query;
			$sql = new query ( $conn );
			$sql->exec ( $sql_query );
			$db_fields=array();
			while ( $sql->get_row () ) {
				$db_fields[$sql->row['TABLE_NAME']][$sql->row['COLUMN_NAME']]=$sql->row;
			}
//			print_r($db_fields);
			
			
foreach ( $vlist->visitnums as $key => $val ) {
	$output .= "<tr><td colspan=8 class=int>{$val['TEXT']}</td></tr>";
	
	foreach ( $vlist->esams [$key] as $esam => $v_esam ) {
		if ($in['EXCEL']=='') $style=" class=sc4bis width=20%";
		else $style="";
		
		$form=$v_esam['XML'];
		$xml_form = new xml_form ( $conn, $service, $config_service, $in, $uploaded_file_dir );
		$xml_form->xml_form_by_file ( $xml_dir . '/' . $form );
		
		$output .= "
			<tr>
				<td colspan=8 class=int>N.ro: $esam - XML: {$v_esam['XML']} - Title: {$v_esam['TESTO']} - Table: {$xml_form->form['TABLE']} </td>
			</tr>
			<tr>
				<td $style>Column Name</td>
				<td $style>Data Type</td>
				<td $style>Data Length</td>
				<td $style>Txt</td>
				<td $style>Type</td>
				<td $style>Mandatory</td>
				<td $style>Condition</td>
				<td $style>TB</td>
			</tr>
			";
		
			$xml_form = new xml_form ( );
			$xml_form->xml_form_by_file ( $xml_dir . '/' . $v_esam ['XML'] );
			foreach ( $xml_form->fields as $key => $val ) {
				if ($val ['VAR'] != '') {
					$obbligatorio = 'No';
					$testo = $val ['TESTO'];
					$search = array ("'<script[^>]*?>.*?</script>'si",  // Rimozione del javascript
                 "'<[\/\!]*?[^<>]*?>'si",           // Rimozione dei tag HTML
                 "'([\r\n])[\s]+'",                 // Rimozione degli spazi bianchi
                 "'&(quot|#34);'i",                 // Sostituzione delle entit� HTML
                 "'&(amp|#38);'i",
                 "'&(lt|#60);'i",
                 "'&(gt|#62);'i",
                 "'&(nbsp|#160);'i",
                 "'&(iexcl|#161);'i",
                 "'&(cent|#162);'i",
                 "'&(pound|#163);'i",
                 "'&(copy|#169);'i",
                 "'&#(\d+);'e");                    // Valuta come codice PHP

$replace = array ("",
                  "",
                  "\\1",
                  "\"",
                  "&",
                  "<",
                  ">",
                  " ",
                  chr(161),
                  chr(162),
                  chr(163),
                  chr(169),
                  "chr(\\1)");

$testo = preg_replace($search, $replace, $testo);
					
					$tipo = $val ['TYPE'];
					$variabile = "[{$val ['VAR']}]";
					if ($val ['TYPE'] == 'textbox') {
						$variabile.="<br>{$val['VAR_TYPE']}({$val['VAR_SIZE']})";
					}
					if ($val ['TYPE'] == 'select' || $val ['TYPE'] == 'radio' || $val ['TYPE'] == 'select_hyper' || $val ['TYPE'] == 'radio_hyper') {
						$variabile = "[{$val ['VAR']}](Code)<br>[D_{$val ['VAR']}](decode)";
						foreach ($val['VALUE'] as $idx=>$decode){
							$variabile.="<li>$idx => $decode</li>";
						}
					}
					if ($val ['TYPE'] == 'hidden') {
						$obbligatorio = 'Auto';
					}
					if ($val ['TYPE'] == 'checkbox' || $val ['TYPE'] == 'checkbox_hyper') {
						$variabile='';
						foreach ($val['VALUE'] as $idx=>$decode){
							if ($decode!='') $variabile.="<li>$decode => [$idx]</li>";
							else $variabile.="<li>[$idx]</li>";
						}
					}					
					if ($val ['SEND'] != '')
						$obbligatorio = "Si";
					$condizioni = '';
					if ($val ['CONDITION'] != '') {
						$vars=explode("|", $val ['CONDITION']);
						$vals=explode("|", $val ['CONDITION_VALUE']);
						foreach ($vars as $idx=>$vl){
							if (preg_match("/^!/",$vals[$idx])) {
								$vals[$idx]=str_replace("!", $vals[$idx]);
								if ($vals[$idx]=='') $condizioni.="<li>[{$vars[$idx]}] != null</li>";
								else $condizioni.="<li>[{$vars[$idx]}] != {$vals[$idx]}</li>";
							}
							else $condizioni.="<li>[{$vars[$idx]}] = {$vals[$idx]}</li>";
						}					
					} 
						
					$tb = "Yes";
					if ($val ['TB'] != '')
						$tb = 'No';
					if ($in['EXCEL']=='') $style=" class=input valign=top";
					else {
						$style="";
					}
//					echo $variabile;

					/**
					 * Parte relativa al data type e data length
					 */
					
					if ($val ['TYPE'] == 'select' || $val ['TYPE'] == 'radio' || $val ['TYPE'] == 'select_hyper' || $val ['TYPE'] == 'radio_hyper') {
						$ora_type=$db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_TYPE']."(Code)<br>".$db_fields[$xml_form->form['TABLE']]['D_'.$val ['VAR']]['DATA_TYPE']."(decode)";
						$ora_length=$db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_LENGTH']."(Code)<br>".$db_fields[$xml_form->form['TABLE']]['D_'.$val ['VAR']]['DATA_LENGTH']."(decode)";
					}else{
						$ora_type=$db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_TYPE'];
						$ora_length=$db_fields[$xml_form->form['TABLE']][$val ['VAR']]['DATA_LENGTH'];
					}		
						
					$output .= "
			<tr>
				<td $style>$variabile &nbsp;</td>
				<td $style>$ora_type &nbsp;</td>
				<td $style>$ora_length &nbsp;</td>
				<td $style>$testo &nbsp;</td>
				<td $style>$tipo &nbsp;</td>
				<td $style>$obbligatorio &nbsp;</td>
				<td $style>$condizioni &nbsp;</td>
				<td $style>$tb &nbsp;</td>
			</tr>
			
			";
				
				}
			}
		
	}
}
$output .= "</table>";

if ($in['EXCEL']!=''){
	$export_file = "file_variabili.xls";
    //header('Content-Type: application/vnd.ms-excel;');                 // This should work for IE & Opera
    //header("Content-type: application/x-msexcel");                    // This should work for the rest
    //header('Content-Disposition: attachment; filename="'.basename($export_file).'"');
	//header("Content-type: application/vnd.ms-excel");
	//header("Content-Disposition: attachment; filename=".$export_file);
    $output=str_replace("<li>", "", $output);
    $output=str_replace("</li>", "", $output);
    echo $output;
    exit;
}
$filetxt = preg_replace ( "/<!--body-->/", $output, $filetxt );
echo $filetxt;
?>
