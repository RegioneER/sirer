<?
//Forzo https
if (!$_SERVER['HTTPS'] && $_SERVER['PORT']!="443"){
	$url = "https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
	header('Location: '.$url);
}
/*
ini_set('display_errors','1');
error_reporting(E_ERROR);
*/

define("LOCAL_GIT_BIN",'/http/local/bin/git');

include_once "config.inc";
include_once "study.inc.php";

include_once "../../../libs/layout/layoutLibs/NavBar.class.php";
include_once "../../../libs/layout/layoutLibs/NavBarItem.class.php";
include_once "../../../libs/layout/layoutLibs/Link.class.php";
include_once "../../../libs/layout/layoutLibs/LinkedEvent.class.php";
include_once "../../../libs/layout/layoutLibs/BreadCrumb.class.php";
include_once "../../../libs/layout/layoutLibs/SideBar.class.php";
include_once "../../../libs/layout/layoutLibs/SideBarItem.class.php";
include_once "../../../libs/xCRF/inbox.php";

$xmr = new xmrwf ( "study.xml", $conn );


$sub_service=str_replace($xmr->dir, "", $dir);
$sub_service=rtrim($sub_service, "/");
$sub_service=ltrim($sub_service, "/");
$xml_dir="$dir/xml";

if ($sub_service!=''){
    if (!$xmr->substudies){$xmr->substudies=array();}
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


if(isset($in['install']) ){
	$study_=new $class_name($xml_dir, $service, "visite_exams.xml", $conn, $in, $config_service, $user,true, $config_service['WF_NAME'], $xmr);//parametro TRUE mi richiama la funzione CheckXMR () che crea, tra le altre anche COORDINATE

	$installer = new Installer($xmr->prefix,$conn,$config_service);
	$installer->checkTableExist();
	$installer->checkCreateEqTb();
	
	
	//$installer->fileSystem();
	//$installer->IanusUsers();
	//$installer->PrintReport();
	header('Location: '.$config_service['ACMPath'].'?/study/list');
}
			
$study_=new $class_name($xml_dir, $service, "visite_exams.xml", $conn, $in, $config_service, $user,false, $config_service['WF_NAME'], $xmr);
$study_->Controller();



$body=$study_->body;
$onload=$study_->onload;
$script=$study_->script;
$body="".$body;
$user_name="<p class='profile-block' align=right>
	<b>Profile:</b> {$user->profilo}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b>{$user->nome_azienda}&nbsp;User: </b>{$user->nome_cognome}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b><a href='/change_password'>Change password</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
    <!--<b><a href='/ShibLogOut'>Logout</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>-->
    <b><a href='http://log:out@{$_SERVER['SERVER_NAME']}'>Logout</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
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
$filetxt=str_replace("<!--page_title-->", $study_->page_title, $filetxt);

$inbox = new inbox($conn,mlGetLanguage());
$filetxt=str_replace("<!--inbox-->", $inbox->get_navbar(), $filetxt);
$filetxt=str_replace("<!--inbox_bottone-->", $inbox->get_navbarbtn(), $filetxt);



//Logger::send($study_);
//die();
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
//Close connection and render page!
$conn->closeConnection();

//Footer con versione repository git
include_once("{$_SERVER['DOCUMENT_ROOT']}/../libs/acm/Git.php");
$gitexec = LOCAL_GIT_BIN;
$repofolder = realpath(getcwd());
$libsfolder = "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF";
if (preg_match("/\.sisslab05\./i",$_SERVER['SERVER_NAME'])){
    //Posso testare in demo-cro.sisslab05
    $gitexec = "/usr/bin/git";
}else if (preg_match("/\.sisslocal\./i",$_SERVER['SERVER_NAME'])){
    //Posso testare in demo-cro.sisslab05
    $gitexec = "\"C:\\Program Files (x86)\\Git\\cmd\\git.EXE\"";
}else{
    //Niente
}
//echo "$repofolder";

$repo = Git::open($repofolder); //Posso prima settare la cartella di repository, perche' esiste gia'. Non ho bisogno del binario GIT.
$repo->setBinFile($gitexec); //ora setto il binario x usare la classe.
//$version = file_get_contents("version.txt");
$chash = $repo->getCurrentHash();
$chash=trim($chash);
//$version = str_replace("[BUILD]",$chash,$version);
//$output .= '<div style="clear:both; text-align:center;"><hr/>'.$version.'<br/>&nbsp;</div>';

$repolib = Git::open($libsfolder); //Posso prima settare la cartella di repository, perche' esiste gia'. Non ho bisogno del binario GIT.
$repolib->setBinFile($gitexec); //ora setto il binario x usare la classe.
//$version = file_get_contents("version.txt");
$lhash = $repolib->getCurrentHash();
$lhash=trim($lhash);
$filetxt .= '<div style="clear:both; text-align:center;"><hr/>Study version hash: '.$chash.' - xCRF libs hash: '.$lhash.'<br/>&nbsp;</div>';

die($filetxt);
?>
