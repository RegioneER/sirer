<?php
/**
 * Example Application
 *
 * @package Example-application
 */
require 'libs/Smarty.class.php';
include_once "db_wl.inc";
function error_page($a, $b, $c){
	var_dump($a, $b, $c);
	die();
}
global $queries;
global $singleResultQueries;

global $cssAdded;
global $jsAdded;
global $reportTitle;
global $parameters;
global $inlineJs;

foreach ($_GET as $key=>$val){
	$parameters[$key]=$val;
}

foreach ($_POST as $key=>$val){
	$parameters[$key]=$val;
}

$parameters['remote_userid']=$_SERVER['REMOTE_USER'];

$cssAdded[]="/casAuthn/assets/css/bootstrap.min.css";
$jsAdded[]="/casAuthn/assets/js/jquery.min.js";
$jsAdded[]="/casAuthn/assets/js/bootstrap.min.js";
$conn=new dbconn();
$container=file_get_contents("/http/lib/IanusCasDriver/reps/baseContainer.html");
$content=file_get_contents($_SERVER['DOCUMENT_ROOT']."/../reports/$reportFile.html");
$content=str_replace("\n", "", $content);
$content=str_replace("\r", "", $content);
$content=preg_replace('/<!--query (.*?)-->/e', 'addQuery("\\1")', $content);
$content=preg_replace('/<!--ExecQuery (.*?)-->/e', 'execQuery("\\1")', $content);
$content=preg_replace('/<!--gchart:(.*?) (.*?)-->/e', 'gChart("\\1", "\\2")', $content);
$content=preg_replace('/<!--ExecQuerySingleRow (.*?)-->/e', 'execQuerySingleRow("\\1")', $content);
$content=preg_replace('/<!--css:(.*?)-->/e', 'addCss("\\1")', $content);
$content=preg_replace('/<!--js:(.*?)-->/e', 'addJs("\\1")', $content);
$content=preg_replace('/<!--title:(.*?)-->/e', 'setTitle("\\1")', $content);
$content=preg_replace('/<!--cycle (.*?):start-->/e', 'processCycleStart("\\1")', $content);
$content=preg_replace('/<!--cycle (.*?):end-->/e', 'processCycleStop("\\1")', $content);
$template=str_replace("<!--body-->", $content, $container);
$template=str_replace("<!--inlineJs-->", $inlineJs, $template);

$templateDir=$_SERVER['DOCUMENT_ROOT']."/../reports/smarty/templates";
file_put_contents("$templateDir/$reportFile.tpl", $template);

$smarty = new Smarty;
$smarty->setTemplateDir($templateDir);
$smarty->setCompileDir($templateDir."/../compiled");
$smarty->setCacheDir($templateDir."/../cache");
$smarty->force_compile = true;
$smarty->debugging = false;
$smarty->caching = false;
$smarty->cache_lifetime = 120;


$smarty->assign("reportTitle", $reportTitle);
$smarty->assign("cssAdded", $cssAdded);
$smarty->assign("jsAdded", $jsAdded);


$smarty->display($reportFile.".tpl");


function addQuery($arg){
	global $queries;
	$split=explode(":", $arg);
	$query=str_replace($split[0].":", "", $arg);
	$query=str_replace("\t", " ", $query);
	$query=str_replace("\\'", "'", $query);
	$queries[$split[0]]=$query;
}


function execQuery($arg){
	return "\n{assign var={$arg}Result value=Utils::ExecQuery('".$arg."')}\n";
}

function execQuerySingleRow($arg){
	return "\n{assign var={$arg} value=Utils::ExecQuerySingleRow('".$arg."')}\n";
}

function addCss($arg){
	global $cssAdded;
	$split=explode(":", $arg);
	$cssAdded[]=str_replace($split[0].":", "", $arg);
	
}

function addJs($arg){
	global $jsAdded;
	$split=explode(":", $arg);
	$jsAdded[]=str_replace($split[0].":", "", $arg);
}

function singleResultQuery($arg){
	global $singleResultQueries;
	$split=explode(":", $arg);
	$query=str_replace($split[0].":", "", $arg);
	$query=str_replace("\t", " ", $query);
	$singleResultQueries[$split[0]]=$query;
}

function processCycleStart($arg){
	return "\n{foreach \${$arg}Result as \${$arg}}\n{Utils::setParameters('$arg', \${$arg})}\n";
}


function setTitle($title){
	global $reportTitle;
	$reportTitle=$title;
}


function processCycleStop($arg){
	return "\n{/foreach}\n";
}



function var_glob($value){
	global $parameters;
	if (isset($parameters[$value]) && $parameters[$value]!='') return $parameters[$value];
}

function gChart($type, $qKey){
	global $inlineJs;
	$qRes=Utils::ExecQuery($qKey);
	$firstColumn=true;
	$chartColumns='';
	foreach($qRes[0] as $key=>$val){
		if ($firstColumn){
			$chartColumns.="data.addColumn('string', '{$key}');
		    ";
		}else {
			$chartColumns.="data.addColumn('number', '{$key}');
	        ";
			
		}
		$firstColumn=false;
	}
	$rowCount=1;
	$dataRows="data.addRows([";
	foreach($qRes as $key=>$val){
		$dataRows.="[";
		$colCount=1;
		foreach ($val as $k1=>$v1){
			if ($colCount==1) $dataRows.="'{$v1}'";
			else $dataRows.="{$v1}";
			if (count($val)!=$colCount) $dataRows.=","; 
			$colCount++;
		}
		$dataRows.="]";
		if (count($qRes)!=$rowCount){
			$dataRows.=",
			";
		}
		$rowCount++;
	}
	$dataRows.="]);";
	$inlineJs.="
	  google.charts.setOnLoadCallback(draw_{$qKey}_{$type}_Chart);
	  function draw_{$qKey}_{$type}_Chart() {
	      // Define the chart to be drawn.
	      var data = new google.visualization.DataTable();
	      {$chartColumns}
	      {$dataRows}
	      var chart = new google.visualization.{$type}(document.getElementById('draw_{$qKey}_{$type}_Chart_Area'));
	      chart.draw(data, null);
	  }";
	
	return "<h4>Impostazione grafico di tipo $type per query $qKey</h4>
	<div id='draw_{$qKey}_{$type}_Chart_Area'></div>
	";
}

class Utils{
	
	static function ExecQuery($qKey){
		global $conn;
		global $parameters;
		global $queries;
		$val=$queries[$qKey];
		$query=new query($conn);
		$queryParsed=preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $val );
		$query->exec($queryParsed, $parameters);
		while ($query->get_row()){
			$result[]=$query->row;
		}
		return $result;
	}
	
	static function ExecQuerySingleRow($qKey){
		global $conn;
		global $parameters;
		global $queries;
		$val=$queries[$qKey];
		$query=new query($conn);
		$queryParsed=preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $val );
		$query->exec($queryParsed, $parameters);
		if ($query->get_row()){
			$result=$query->row;
		}
		return $result;
	}
	
	static function setParameters($qKey, $row){
		global $parameters;
		foreach ($row as $k=>$v){
			$parameters[$qKey."_".$k]=$v;
		}
		
	}
	
	
}
