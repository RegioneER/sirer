<?

ini_set('display_errors','1');
error_reporting(E_ALL);
include_once "config.inc";

include_once "study.inc.php";

include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/layout/layoutLibs/NavBar.class.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/layout/layoutLibs/NavBarItem.class.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/layout/layoutLibs/Link.class.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/layout/layoutLibs/LinkedEvent.class.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/layout/layoutLibs/BreadCrumb.class.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/layout/layoutLibs/SideBar.class.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/layout/layoutLibs/SideBarItem.class.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/inbox.php";


$xmr = new xmrwf ( "study.xml", $conn );

$sub_service=str_replace($xmr->dir, "", $dir);
$sub_service=rtrim($sub_service, "/");
$sub_service=ltrim($sub_service, "/");
$xml_dir="$dir/xml";

if ($sub_service!=''){	
	foreach ($xmr->substudies as $key => $val){
		if ($val->prefix==$sub_service) $xmr=$val;				
		$xml_dir=str_replace("$sub_service/xml", "xml/$sub_service", $xml_dir);			
	}	
}



$xmr->setConfigParam();

$config_service['filetxt']=$filetxt;

if (class_exists("Study_{$xmr->prefix}")){
	$class_name="Study_".$xmr->prefix;
}
else $class_name="Study";


$user=new user($conn, $in['remote_userid'], $xmr);

$str="select count(*) conto from {$xmr->prefix}_utenti_centri where userid=:remote_user and tipologia=:tipologia";
$query=new query($conn);
$bind['REMOTE_USER']=$in['remote_userid'];
$bind['TIPOLOGIA']='Farmacia';
$query->get_row($str,$bind);
if($query->row['CONTO']>0){
    $visite_exams='visite_exams_farm.xml';
}
else{
    $visite_exams='visite_exams.xml';
}



$study_=new $class_name($xml_dir, $service, $visite_exams, $conn, $in, $config_service, $user,false, $config_service['WF_NAME'], $xmr);

$study_->Controller();

$body=$study_->body;
$onload=$study_->onload;
$script=$study_->script;
$body="".$body;
$user_name="<p class='profile-block' align=right>
	<b>Profile:</b> {$user->profilo}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b>{$user->nome_azienda}&nbsp;User: </b>{$user->nome_cognome}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b><a href='/change_password'>Change password</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
    <b><a href='/ShibLogOut'>Logout</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
	</p>
	
	";

$filetxt=preg_replace("/<!--script-->/", $script, $filetxt);
$filetxt=str_replace("<!--breadcrumb-->", $study_->breadcrumb, $filetxt);

$filetxt=str_replace("<!--navbar-->", $study_->configurer->navbar, $filetxt);
/*
if ($study_->configurer->sidebar->__toString()==""){
	$customStyle.=".main-content-no-sidebar{margin-left:0px;}\n";
	$customStyle.=".breadcrumb-no-sidebar{left:0px !important;}\n";
}
*/
$filetxt=str_replace("<!--title-->", $study_->title, $filetxt);
$pageTitleHtml="";
if ($study_->page_title!="") $pageTitleHtml="<div class=\"page-header\"><h1>".$study_->page_title."</h1></div>";
$filetxt=str_replace("<!--page_title-->", $pageTitleHtml, $filetxt);

$inbox = new inbox($conn);
$filetxt=str_replace("<!--inbox-->", $inbox->get_navbar(), $filetxt);
$filetxt=str_replace("<!--inbox_bottone-->", $inbox->get_navbarbtn(), $filetxt);

$searchBox=' <div class="nav-search" id="nav-search">
                            <span class="input-icon">
                                <input type="text" placeholder="'.mlOut("System.Search","Search").' ..." class="nav-search-input" id="nav-search-input" autocomplete="off" />
                                <i class="fa fa-search nav-search-icon"></i>
                                <i id=\'search-icon\' class=""></i> 
                                </span>
                        </div>';
if (!$study_->configurer->hasFastSearch) $addSerachBox=" style='display:none'";
	
	$searchBox=' <div class="nav-search" id="nav-search"'.$addSerachBox.'>
                            <span class="input-icon">
                                <input type="text" placeholder="'.mlOut("System.Search","Search").' ..." class="nav-search-input" id="nav-search-input" autocomplete="off" />
                                <i class="fa fa-search nav-search-icon"></i>
                                <i id=\'search-icon\' class=""></i>
                                </span>
                        </div>';

$filetxt=str_replace("<!--searchBox-->", $searchBox, $filetxt);

$filetxt=str_replace("<!--customStyle-->", $customStyle, $filetxt);
$filetxt=str_replace("<!--sidebar-->", $study_->configurer->sidebar, $filetxt);
$filetxt=preg_replace("/<!--lang-->/", $study_->xmr->config_service['lang'], $filetxt);
$filetxt=preg_replace("/<!--utente-->/", $user_name, $filetxt);
$onload.=";\nif (document.forms[0]) document.forms[0].action='';";
$filetxt=preg_replace("/\/\/<!--onload-->/", $onload, $filetxt);
$filetxt=preg_replace("/<!--user_name-->/", $nome_user, $filetxt);
$filetxt=preg_replace("/<!--page_content-->/", $body, $filetxt);
$filetxt=preg_replace("/<!--legend_lower-->/", $legend_lower->html_legend_lower, $filetxt);
$filetxt=preg_replace("/<!--legend_upper-->/", $legend_upper->html_legend_upper, $filetxt);
$filetxt=str_replace("<br>", "<br/>", $filetxt);
die($filetxt);
?>