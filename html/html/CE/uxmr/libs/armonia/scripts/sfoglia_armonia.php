// <?php
// function var_glob($value) {
// 	global $in;
// 	global $inputval;
// 	if (isset ( $inputval [$value] ) && $inputval [$value] != '')
// 	return $inputval [$value];
// 	if (isset ( $in [$value] ) && $in [$value] != '')
// 	return $in [$value];
// 	if (isset ( $GLOBALS [$value] ) && $GLOBALS [$value] != '')
// 	return $GLOBALS [$value];
// }
// //**************INCLUDES ***************************
// require_once "../../http_lib.inc";
// include_once "../../db.inc";
// include_once "../../xml_parser_wl.inc";
// include_once "../..//HTML_Parser.inc";

// include_once "../../page.inc";
// include_once "../../vlist.inc";
// include_once "../../list.inc";
// include_once "../../legend.inc";
// include_once "../../esams_list.inc";
// include_once "../../form.inc";
// include_once "../../study_prototype.inc";
// include_once "../../xmrwf.inc.php";
// //****************FINE INCLUDES *********************

// $list = $_GET['list'];
// if (isset($list)){

// 	$body="<br/><br/>";
// 	$script='';
// 	$onload='';
	
// 	$list_o= new xml_list_prototype(getXMRPath($list).'/'.$list);
	
	
// 	$body.="<p class=titolo>{$list_o->list['TITOLO']}</p>";
//   $body.=$list_o->list_html();
//   $filetxt = file_get_contents($template_dir.'/template_sfoglia.htm');
//   $filetxt=preg_replace("/<!--body-->/", $body, $filetxt);

// echo 'ciao'.$filetxt;

// }




// function getXMRPath($filename){
// 	$ret='';
	
// 	$dir_lib = '../xml/';

// 	if ($filename != '' && file_exists ($dir_lib.$filename)){
// 		$ret = $dir_lib;
// 	}
// 	else{
// 		$ret = '../../../xml';
// 	}

// 	$ret=rtrim($ret, "/");
// 	// 		print_r($_SERVER);die();
// 	return $ret;

// }


 