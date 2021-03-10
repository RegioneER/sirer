<?php 

require_once 'limonade-dist/lib/limonade.php';
require_once 'UIManager.class.php';
include_once 'builder/cdisc/ODMtoXMR.php';
//Common files and database connection
require_once 'dbconfig.php';
require_once 'database.php';
require_once 'multilanguage.php';
require_once 'utils.php';

//Modules
require_once 'workspace.module.php';
require_once 'profile.module.php';
require_once 'user.module.php';
require_once 'study.module.php';
require_once 'center.module.php';
require_once 'strutture.module.php';
require_once 'personale.module.php';
require_once 'tools.module.php';

//Custom Modules
require_once 'custom_modules.inc';
//Profiles
require_once 'profiles.inc';

require_once 'products.inc';
if (file_exists($_SERVER['DOCUMENT_ROOT']."/../config/acm-config.php")) {

	include_once $_SERVER['DOCUMENT_ROOT']."/../config/acm-config.php";
}else {
	include_once 'default-config.php';
}

function limonade_init(){
	limonade_configure();
	dispatch('/', 'home_page');
	global $modules;
	//Modules
	if ($modules['profile']) {
		profile_init();
	}
	if ($modules['workspace']) {
		workspace_init();
	}
	if ($modules['user']) {
		user_init();
	}
	if ($modules['study']) {
		study_init();
	}
	if ($modules['center']) {
		center_init();
	}
	if ($modules['strutture']) {
		strutture_init();
	}
    if ($modules['personale']) {
        personale_init();
    }
	if ($modules['tools']) {
		tools_init();
	}
	//Custom Modules
	global $custom_modules;
	if( isset($custom_modules['THERAPY']) && $custom_modules['THERAPY']=='1' ){
		require_once 'therapy.module.php';
		therapy_init();
	}
	if( isset($custom_modules['GLOBAL_PROFILES']) && $custom_modules['GLOBAL_PROFILES']=='1' ){
		require_once 'globalProfiles.module.php';
		globalProfiles_init();
	}
	if( isset($custom_modules['DBLOCK']) && $custom_modules['DBLOCK']=='1' ){
		require_once 'dblock.module.php';
		dblock_init();
	}
}
function limonade_configure()
{
	//option('env', ENV_DEVELOPMENT);
	layout('html_default_layout');
}

function home_page(){
	header("location: ".url_for('/user/list'));
	die();
}

function menu_dashboard(){
	$m = UIManager::getInstance();
	//print_r($d);
	//die("CIAO!");
	$m->build_dashboard();
	//$d->outputData();
	//print_r($d);
	return html($m->dsp_getPageContent());	
}


function html_default_layout($vars){ 
	extract($vars);
	//die("CIPPA");
	$uim = UIManager::getInstance();
	$output=file_get_contents("container.html");
	$study = $uim->dsp_getStudy();
	$page_title = $uim->dsp_getPageTitle();
	$title=$study." - ".$page_title;
	$onload=$uim->get_onLoad();
	$nav = $uim->dsp_navbar();
	$js = $uim->dsp_js();
	
	$breadcrumb = $uim->dsp_breadcrumb();
	$back_links = $uim->dsp_backLinks();
	$sideBar = $uim->dsp_sidebar();
	
	$page_content = $content; //$dispatcher->dsp_getPageContent();

	//System messages
	$mstr=common_print_messages();
	
	//echo($mstr);
	
	//$output = str_replace('[MESSAGES_PLACEHOLDER]',$mstr,$output);
	//$page_content.= $mstr;
	//End of system messages
	
	$output=str_replace("<!--title-->", $title, $output);
	
	$output=str_replace("<!--navbar-->", $nav, $output);
	
	$output=str_replace("<!--sidebar-->", $sideBar, $output);
	$output=str_replace("<!--breadcrumb-->", $breadcrumb, $output);
	$output=str_replace("<!--page_title-->", $page_title, $output);
	$output=str_replace("<!--back_links-->", $back_links, $output);
	$output=str_replace("<!--page_content-->", $page_content, $output);
	$output=str_replace("<!--page_js-->", $js, $output);
	$output=str_replace("<!--system_messages-->",$mstr,$output);
	$output=str_replace("<!--onload-->",$onload,$output);

    //Footer con versione repository git
    include_once('Git.php');
    $gitexec = LOCAL_GIT_BIN;
    if (preg_match("/\.sisslab05\./i",$_SERVER['SERVER_NAME'])){
        //Posso testare in demo-cro.sisslab05
        $repofolder = "/var/www/XMR/service/libs/acm";
        $gitexec = "/usr/bin/git";
    }else if (preg_match("/\.sisslocal\./i",$_SERVER['SERVER_NAME'])){
        //Posso testare in demo-cro.sisslab05
        $repofolder = "C:\\XMR\\service\\libs\\acm";
        $gitexec = "\"C:\\Program Files (x86)\\Git\\cmd\\git.EXE\"";
    }else{
        $repofolder = "/http/servizi/".IDP_NAME."/".SERVICE_FOLDER."/libs/acm";
    }
    //echo "$repofolder<br/><br/>{$_SERVER['SERVER_NAME']}";

    //$repo = Git::open($repofolder); //Posso prima settare la cartella di repository, perche' esiste gia'. Non ho bisogno del binario GIT.
    //$repo->setBinFile($gitexec); //ora setto il binario x usare la classe.
    $version = file_get_contents("version.txt");
    //$chash = $repo->getCurrentHash();
    $chash=trim($chash);
    $version = str_replace("[BUILD]",$chash,$version);
    $output .= '<div style="clear:both; text-align:center;"><hr/>'.$version.'<br/>&nbsp;</div>';

    echo $output;
}


function err_can_show(){
	return true;
}


define ("ERROR",0);
define ("WARNING",1);
define ("INFO",2);
function common_add_message($string, $status){
	if (!isset($_SESSION['MESSAGES'])){
		$_SESSION['MESSAGES'] = array();
	}
	$newmsg = array('STATUS'=>$status,'TEXT'=>$string);
	$_SESSION['MESSAGES'][] = $newmsg;
	//echo $string;
}
function common_getandclear_messages(){
	if (!isset($_SESSION['MESSAGES'])){
		$_SESSION['MESSAGES'] = array();
	}
	$msg = $_SESSION['MESSAGES'];
	$_SESSION['MESSAGES'] = array();
	return $msg;
}
function common_print_messages(){
	$messages = common_getandclear_messages();
	$mstr = '';
	if (count($messages)>0){
		$mstr .= "<div id=\"messages\" class=\"panel panel-info\" >";
		$mstr .= "<div class=\"panel-heading\"><h3 class=\"panel-title center\">System messages</h3></div>";
		$mstr .= "<div class=\"panel-body\">";
		foreach ($messages as $m){
			$ico = "";
			$color = '#000000';
			switch ($m['STATUS']){
				case INFO:
					//$ico = '<i class="fa fa-check-circle-o"></i>';
					$ico = '<i class="fa fa-info-circle"></i>';
					$color = '#16C016';
					break;
				case WARNING:
					$ico = '<i class="fa fa-exclamation-triangle"></i>';
					$color = '#E6C614';
					break;
				case ERROR:
					$ico = '<i class="fa fa-exclamation-circle"></i>';
					$color = '#F03030';
					break;
			}
			$mstr .= "<p style=\"color: $color;\">$ico {$m['TEXT']}</p>";
		}
		$mstr .= "</div>";
		$mstr .= "</div>";
	}
	return $mstr;
}
function common_nextId($id, $startId = 0){
	$retval = $startId;
	if ($id === 0 || is_numeric($id)){ //$id !=="" || $is !== false
		$retval = $id+1;
	}
	return $retval;	
}
function common_computeCheckBoxes($array, $name, $length){
	$total = 0;
	for ($i = 0; $i<$length;$i++){
		$value = $array[$name."_$i"];
		$total += $value;
		unset($array[$name."_$i"]);
	}
	$array[$name] = $total;
	return $array;
}
function common_booleanCheckBox($array, $name){
	if (!isset($array[$name])){
		$array[$name] = 0;
	}else{
		if ($array[$name]){
			$array[$name] = 1;
		}else{
			$array[$name] = 0;
		}
	}
	return $array;
}
function common_appendCheckBoxes($array, $name){
	$total = "";
	$length = $array["COUNT_".$name];
	unset($array["COUNT_".$name]);
	//die($length);
	for ($i = 0; $i<$length;$i++){
		$value = $array[$name."_$i"];
		//echo $value;
		if ($value){
			$total .= "|".$value;
		}
		unset($array[$name."_$i"]);
	}
	$total .= "|";
	//die($total);
	$array[$name] = $total;
	return $array;
	
}

function common_strToHex($string)
{
    $hex='';
    for ($i=0; $i < strlen($string); $i++)
    {
        $hex .= dechex(ord($string[$i]));
    }
    return $hex;
}
function common_hexToStr($hex)
{
    $string='';
    for ($i=0; $i < strlen($hex)-1; $i+=2)
    {
        $string .= chr(hexdec($hex[$i].$hex[$i+1]));
    }
    return $string;
}

function common_beginsWith( $str, $sub ) {
    return ( substr( $str, 0, strlen( $sub ) ) === $sub );
}

function common_endsWith( $str, $sub ) {
    return ( substr( $str, strlen( $str ) - strlen( $sub ) ) === $sub );
}


function install_acm(){

    include_once "Installer.inc";
    $conn = new dbconn();
    $inst = new Installer("CMM", $conn);
    $inst->CreateCMMTable();
    $conn->commit();
}

?>
