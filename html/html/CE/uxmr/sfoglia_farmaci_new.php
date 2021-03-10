<?php

include_once 'libs/db_wl.inc';

$debug=$_GET{'DEBUG'};

$conn = new dbconn ( "farmaci_bduf", "sibdfc1$", "farmaci_prod" );

foreach ($_GET as $key=>$val){
	
	$_GET[$key]=str_replace("\\'", "'", $val);
	if ($debug) echo "$key=$_GET[$key]<br>";
}

function error_page($a, $b, $c) {
	print_r ( $a );
	print_r ( $b );
	print_r ( $c );
	die ();
}

function js_escape($str){
	$str=str_replace("'", "\\'", $str);
	return $str;
}

function SfogliaAtc($livello, $conn, $pattern = null) {
	if ($_GET{'DEBUG'}) echo "<hr>sono in SfogliaAtc $livello, $conn, $pattern <br>" ;
	if ($pattern != '')	$where_agg = "and ATC like '$pattern%'";
	$sql_query = "select atc, datc, inn from atc_sfoglia where length(atc)='$livello' $where_agg";
	if ($_GET{'DEBUG'}) echo "<br>$sql_query" ;
	$sql = new query ( $conn );
	$sql->exec ( $sql_query );
	return $sql;
}

function SfogliaSpec($atc, $conn) {
	if ($_GET{'DEBUG'}) echo "<hr>sono in SfogliaSpec $atc, $conn <br>" ;
	$sql_query = "select distinct f.aic_spec, f.spec, f.cod_dtt1, ditta from 
	farmaci_sfoglia f
	where atc='$atc'";
	if ($_GET{'DEBUG'}) echo "<br>$sql_query" ;
	$sql = new query ( $conn );
	$sql->exec ( $sql_query );
	return $sql;
}

function SfogliaConf($aic6, $conn, $spec) {
	if ($_GET{'DEBUG'}) echo "<hr>sono in SfogliaConf $atc, $conn <br>" ;
	$sql_query = "
	select aic_conf, conf, dsost, sostanza
	from farmaci_sfoglia
	where aic_spec='$aic6'
	and spec='$spec'";
	if ($_GET{'DEBUG'}) echo "<br>$sql_query" ;
	$sql = new query ( $conn );
	$sql->exec ( $sql_query );
	return $sql;
}


if ($_GET ['livello'] == '')
	$livello = "1";
else
	$livello = $_GET ['livello'];

$pattern = $_GET ['pattern'];

$sql = SfogliaAtc ( $livello, $conn, $pattern );

$script_name = $_SERVER ['SCRIPT_NAME'];

$livelli_atc [] = "1";
$livelli_atc [] = "3";
$livelli_atc [] = "4";
$livelli_atc [] = "5";
$livelli_atc [] = "7";

foreach ( $_GET as $key => $val ) {
	if ($key != 'pattern' && $key != "livello" && $key != 'show_spec' && $key != 'show_conf' && ! preg_match ( "!^livello_!", $key ) && ! preg_match ( "!^pattern_!", $key ))
		$param .= "$key=$val&";
}

foreach ( $livelli_atc as $key => $val ) {
	if ($livello == $val) {
		break;
	} else {
		$param_call_back .= "livello_{$val}={$_GET['livello_'.$val]}&pattern_{$val}={$_GET['pattern_'.$val]}&";
	}
}
/*
echo "<pre>";
print_r ( $_GET );
echo "</pre>";
*/

$link_script = $script_name . "?" . $param . $param_call_back;

switch ($livello) {
	case "1" :
		$next_livello = "3";
		break;
	case "3" :
		$next_livello = "4";
		break;
	case "4" :
		$next_livello = "5";
		break;
	case "5" :
		$next_livello = "7";
		break;

}

foreach ( $_GET as $key => $val ) {
	if (preg_match ( "!^livello_!", $key )) {
		$livello_nav = str_replace ( "livello_", "", $key );
		$nav_param = "";
		foreach ( $livelli_atc as $k => $v ) {
			if ($livello_nav == $v) {
				break;
			} else {
				$nav_param .= "livello_{$v}={$_GET['livello_'.$v]}&pattern_{$v}={$_GET['pattern_'.$v]}&";
			}
		}
		$menu_nav .= "<li style=\"margin-left: 10px;\"><a href=\"{$script_name}?{$param}{$nav_param}&pattern={$_GET['pattern_'.$livello_nav]}&livello=$livello_nav\">$val</a></li>";
	}
}
$nav_bar="
<div class=\"well well-sm\" style=\"margin-bottom: 0px;\">
	<table border=0 cellpadding=0 cellspacing=0 >
		<tr>
			<td>
				<li style=\"margin-left: 10px;\"><a href=\"{$script_name}?{$param}\">Home</a></li>".$menu_nav."
			</td>
		</tr>
	</table>
</div>";

while ( $sql->get_row () ) {
	$livello_atc=$livello;
	$catc=$sql->row['ATC'];
	$datc=$sql->row['DATC'];
	$atc_inn=$sql->row['INN'];
	if ($livello == '4' || $livello == '5' || $livello == '7') {
		$check = "<input type='checkbox' onclick=\"
			if ('{$_GET['ATC_LIVELLO']}'!='') window.opener.document.forms[0].{$_GET['ATC_LIVELLO']}.value='".js_escape($livello_atc)."';
			if ('{$_GET['ATC_CODE']}'!='') window.opener.document.forms[0].{$_GET['ATC_CODE']}.value='".js_escape($catc)."';
			if ('{$_GET['ATC_DECODE']}'!='') window.opener.document.forms[0].{$_GET['ATC_DECODE']}.value='".js_escape($datc)."';
			if ('{$_GET['ATC_INN']}'!='') window.opener.document.forms[0].{$_GET['ATC_INN']}.value='';
			if ('{$_GET['AIC']}'!='') window.opener.document.forms[0].{$_GET['AIC']}.value='';
			if ('{$_GET['AIC6_SPEC']}'!='') window.opener.document.forms[0].{$_GET['AIC6_SPEC']}.value='';
			if ('{$_GET['AIC6_CSOST']}'!='') window.opener.document.forms[0].{$_GET['AIC6_CSOST']}.value='';
			if ('{$_GET['AIC6_DSOST']}'!='') window.opener.document.forms[0].{$_GET['AIC6_DSOST']}.value='';
			if ('{$_GET['AIC6_CDITTA']}'!='') window.opener.document.forms[0].{$_GET['AIC6_CDITTA']}.value='';
			if ('{$_GET['AIC6_DDITTA']}'!='') window.opener.document.forms[0].{$_GET['AIC6_DDITTA']}.value='';
			if ('{$_GET['AIC9_CONF']}'!='') window.opener.document.forms[0].{$_GET['AIC9_CONF']}.value='';
			window.close();
			window.opener.document.forms[0].CHECK_ATC.checked=false;
		\">";
		$specialita = "";
		$sql_spec = SfogliaSpec ( $sql->row ['ATC'], $conn );
		if ($sql_spec->numrows > 0)
			$hasSpecialita = true;
		else
			$hasSpecialita = false;
		if ($_GET ['show_spec'] == $sql->row ['ATC']) {
			while ( $sql_spec->get_row () ) {
				$aic_spec=$sql_spec->row['AIC_SPEC'];
				$spec=$sql_spec->row['SPEC'];
				
				$cod_ditta=$sql_spec->row['COD_DTT1'];
				$rag_soc=$sql_spec->row['DITTA'];				
				$specialita .= "
	<tr>
		<td class=input style=\"background-color:#7FFFD4\">&nbsp;</td>
		<td class=input style=\"background-color:#7FFFD4\"><input type='checkbox'  onclick=\"
			if ('{$_GET['ATC_LIVELLO']}'!='') window.opener.document.forms[0].{$_GET['ATC_LIVELLO']}.value='".js_escape($livello_atc)."';
			if ('{$_GET['ATC_CODE']}'!='') window.opener.document.forms[0].{$_GET['ATC_CODE']}.value='".js_escape($catc)."';
			if ('{$_GET['ATC_DECODE']}'!='') window.opener.document.forms[0].{$_GET['ATC_DECODE']}.value='".js_escape($datc)."';
			if ('{$_GET['ATC_INN']}'!='') window.opener.document.forms[0].{$_GET['ATC_INN']}.value='".js_escape($atc_inn)."';
			if ('{$_GET['AIC']}'!='') window.opener.document.forms[0].{$_GET['AIC']}.value='".js_escape($aic_spec)."';
			if ('{$_GET['AIC6_SPEC']}'!='') window.opener.document.forms[0].{$_GET['AIC6_SPEC']}.value='".js_escape($spec)."';
			if ('{$_GET['AIC6_CSOST']}'!='') window.opener.document.forms[0].{$_GET['AIC6_CSOST']}.value='';
			if ('{$_GET['AIC6_DSOST']}'!='') window.opener.document.forms[0].{$_GET['AIC6_DSOST']}.value='';
			if ('{$_GET['AIC6_CDITTA']}'!='') window.opener.document.forms[0].{$_GET['AIC6_CDITTA']}.value='".js_escape($cod_ditta)."';
			if ('{$_GET['AIC6_DDITTA']}'!='') window.opener.document.forms[0].{$_GET['AIC6_DDITTA']}.value='".js_escape($rag_soc)."';
			if ('{$_GET['AIC9_CONF']}'!='') window.opener.document.forms[0].{$_GET['AIC9_CONF']}.value='';
			window.close();
			window.opener.document.forms[0].CHECK_ATC.checked=false;
		\"></td>
		<td class=input style=\"background-color:#7FFFD4\">{$sql_spec->row['AIC_SPEC']}</td>
		<td class=input style=\"background-color:#7FFFD4\">{$sql_spec->row['SPEC']} </td>
		<td class=input style=\"background-color:#7FFFD4\"><a href=\"{$link_script}livello={$_GET['livello']}&pattern={$_GET['pattern']}&show_spec={$sql->row['ATC']}&show_conf={$sql_spec->row['AIC_SPEC']}&spec={$sql_spec->row['SPEC']}\">(mostra confezioni)</a></td>
	</tr>
		";
				if ($sql_spec->row ['AIC_SPEC'] == $_GET ['show_conf'] && $sql_spec->row ['SPEC'] == $_GET ['spec']) {
					$sql_conf = SfogliaConf ( $sql_spec->row ['AIC_SPEC'], $conn, $sql_spec->row['SPEC'] );
					while ( $sql_conf->get_row () ) {
						$aic_conf=$sql_conf->row['AIC_CONF'];
						$confezione=$sql_conf->row['CONF'];
						$princ_att=$sql_conf->row['SOSTANZA'];
						$d_princ_att=$sql_conf->row['DSOST'];
						$specialita .= "
				<tr>
					<td class=input style=\"background-color:#FFE4C4\">&nbsp;</td>
					<td class=input style=\"background-color:#FFE4C4\">&nbsp;</td>
					<td class=input style=\"background-color:#FFE4C4\"><input type='checkbox' onclick=\"
			if ('{$_GET['ATC_LIVELLO']}'!='') window.opener.document.forms[0].{$_GET['ATC_LIVELLO']}.value='".js_escape($livello_atc)."';
			if ('{$_GET['ATC_CODE']}'!='') window.opener.document.forms[0].{$_GET['ATC_CODE']}.value='".js_escape($catc)."';
			if ('{$_GET['ATC_DECODE']}'!='') window.opener.document.forms[0].{$_GET['ATC_DECODE']}.value='".js_escape($datc)."';
			if ('{$_GET['ATC_INN']}'!='') window.opener.document.forms[0].{$_GET['ATC_INN']}.value='".js_escape($atc_inn)."';
			if ('{$_GET['AIC']}'!='') window.opener.document.forms[0].{$_GET['AIC']}.value='".js_escape($aic_spec.$aic_conf)."';
			if ('{$_GET['AIC6_SPEC']}'!='') window.opener.document.forms[0].{$_GET['AIC6_SPEC']}.value='".js_escape($spec)."';
			if ('{$_GET['AIC6_CSOST']}'!='') window.opener.document.forms[0].{$_GET['AIC6_CSOST']}.value='".js_escape($princ_att)."';
			if ('{$_GET['AIC6_DSOST']}'!='') window.opener.document.forms[0].{$_GET['AIC6_DSOST']}.value='".js_escape($d_princ_att)."';
			if ('{$_GET['AIC6_CDITTA']}'!='') window.opener.document.forms[0].{$_GET['AIC6_CDITTA']}.value='".js_escape($cod_ditta)."';
			if ('{$_GET['AIC6_DDITTA']}'!='') window.opener.document.forms[0].{$_GET['AIC6_DDITTA']}.value='".js_escape($rag_soc)."';
			if ('{$_GET['AIC9_CONF']}'!='') window.opener.document.forms[0].{$_GET['AIC9_CONF']}.value='".js_escape($sql_conf->row['CONF'])."';			
			window.close();
			window.opener.document.forms[0].CHECK_ATC.checked=false;
		\">{$sql_spec->row['AIC_SPEC']}{$sql_conf->row['AIC_CONF']}</td>
					<td class=input style=\"background-color:#FFE4C4\">{$sql_spec->row['SPEC']} </td>
					<td class=input style=\"background-color:#FFE4C4\">{$sql_conf->row['CONF']}</td>
				</tr>
					";
					}
				}
			}
			
			if ($specialita != '') {
				$specialita = "
			
				<tr> 
					<td colspan=4>
					<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
						<thead>
							<tr>
								<td class=int>&nbsp;</td>
								<td class=int>Seleziona</td>
								<td class=int>AIC</td>
								<td class=int>Specialit&agrave;</td>
								<td class=int>Confezione</td>
							</tr>
						</thead>
						$specialita
					</table>
					</td>
				</tr>
			
			";
			}
		}
	} else
		$check = "";
	if ($hasSpecialita != '') {
		$mostra_spec = "<a href=\"{$link_script}livello={$_GET['livello']}&pattern={$_GET['pattern']}&show_spec={$sql->row['ATC']}\">(mostra specialit&agrave;)</a>";
	} else
		$mostra_spec = "";
	if ($livello == "7") {
		$tb .= "	
	<tr>
		<td class=sc4bis>$check&nbsp;</td>
		<td class=sc4bis>{$sql->row['ATC']}</td>
		<td class=sc4bis>{$sql->row['DATC']}</td>
		<td class=sc4bis>$mostra_spec</td>
	</tr>";
	} else {
		$tb .= "	
	<tr>
		<td class=sc4bis>$check&nbsp;</td>
		<td class=sc4bis>{$sql->row['ATC']}</td>
		<td class=sc4bis><a href=\"{$link_script}pattern_{$livello}={$_GET['pattern']}&livello_{$livello}={$sql->row['DATC']}&livello={$next_livello}&pattern={$sql->row['ATC']}\">{$sql->row['DATC']}</a></td>
		<td class=sc4bis>$mostra_spec</td>
	</tr>";
	}
	$tb .= $specialita;

}

$tabella_risultati = "
	<table class=\"table table-striped table-bordered table-hover\" width=\"95%\" border=\"0\" align=\"center\">
		<thead>
			<tr>
				<th>Seleziona</th>
				<th>Codice ATC</th>
				<th>Descrizione</th>
				<th>Seleziona Specialit&agrave;</th>
			</tr>	
		</thead>
	$tb
	</table>";

	$body=$nav_bar."<br/><br/>".$tabella_risultati;
	
	
	$html=file_get_contents("template.htm");
	$html=str_replace("<!--body-->", $body, $html);
	die($html);

?>