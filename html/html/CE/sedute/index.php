<?
/* echo "<pre>";
var_dump($_SERVER);
echo "</pre>"; */


include_once "config.inc";
include_once "study.inc.php";


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
$user=new user($conn, $in['remote_userid'], $xmr);
$config_service['filetxt']=$filetxt;

if (class_exists("Study_{$xmr->prefix}")){
	$class_name="Study_".$xmr->prefix;
}
else $class_name="Study";

$study_=new $class_name($xml_dir, $service, "visite_exams.xml", $conn, $in, $config_service, $user,false, $config_service['WF_NAME'], $xmr);
$study_->Controller();





$body=$study_->body;
$onload=$study_->onload;
$script=$study_->script;
$breadcrumb=$study_->percorso;
$body="".$body;
$user_name="<p align=right>
	<b>Utente: </b>{$user->nome_cognome}&nbsp;&nbsp;&nbsp;<br/>
	<b>Email: </b>{$user->email}&nbsp;&nbsp;&nbsp;<br/>
	<b>Profilo:</b> {$user->profilo}&nbsp;&nbsp;&nbsp;&nbsp;<br/>
	<b>{$user->nome_azienda}&nbsp;&nbsp;&nbsp;&nbsp;</b><br/>
	</p>";

#GC 17/11/2015 NUOVA_GRAFICA
$nome_utente="{$user->nome_cognome}";
$filetxt=preg_replace("/<!--nome_utente-->/", $nome_utente, $filetxt);

$profilo_utente="{$user->profilo}";
$filetxt=preg_replace("/<!--profilo_utente-->/", $profilo_utente, $filetxt);

$email_utente="{$user->email}";
$filetxt=preg_replace("/<!--email_utente-->/", $email_utente, $filetxt);

$azienda_utente="{$user->nome_azienda}";
$filetxt=preg_replace("/<!--azienda_utente-->/", $azienda_utente, $filetxt);

$aggiungi='<li style="background-color: #931410; !important">
							<a class="dropdown-toggle" href="#" data-toggle="dropdown">
								<i class="icon-plus"></i>
								<span class="topbar-button-text hidden-900">Aggiungi</span>
								<i class="icon-caret-down"></i>
							</a>
							<ul class="pull-right dropdown-navbar dropdown-menu dropdown-caret dropdown-close">
								<li class="dropdown-header">
									Aggiungi
									<span class="help-button" title="Menu degli oggetti registrabili nel servizio" data-placement="left" data-trigger="hover" data-rel="tooltip" data-original-title="Menu degli oggetti registrabili nel servizio">?</span>
								</li>
								<!--li>
									<a href="/uxmr/index.php?VISITNUM=0&ESAM=0&">
										<div class="clearfix">
											<span class="pull-left">
												<i class="icon-plus"></i>
												Nuovo studio
											</span>
										</div>
									</a>
								</li>
								<li>
									<a href="/uxmr/index.php?list=patients_list_add.xml&">
										<div class="clearfix">
											<span class="pull-left">
												<i class="icon-plus"></i>
												Nuovo centro a studio inviato in BD
											</span>
										</div>
									</a>
								</li-->
								<li>
									<a href="/sedute/index.php?VISITNUM=0&ESAM=0">
										<div class="clearfix">
											<span class="pull-left">
												<i class="icon-plus"></i>
												Nuova riunione
											</span>
										</div>
									</a>
								</li>
								<!--li>
									<a href="/uxmr/index.php?list=patients_list_UO.xml">
										<div class="clearfix">
											<span class="pull-left">
												<i class="icon-plus"></i>
												Nuova Unità Operativa
											</span>
										</div>
									</a>
								</li>
								<li>
									<a href="/uxmr/index.php?list=patients_list_PI.xml">
										<div class="clearfix">
											<span class="pull-left">
												<i class="icon-plus"></i>
												Nuovo Principal Investigator
											</span>
										</div>
									</a>
								</li-->
								<li></li>
							</ul>
						</li>';
if ($profilo_utente=="Segreteria CE") $filetxt=preg_replace("/<!--aggiungi-->/", $aggiungi, $filetxt);

#FINE

$filetxt=preg_replace("/<!--script-->/", $script, $filetxt);
$filetxt=preg_replace("/<!--utente-->/", $user_name, $filetxt);
$onload.=";\nif (document.forms[0]) document.forms[0].action='';";
$filetxt=preg_replace("/\/\/<!--onload-->/", $onload, $filetxt);
$filetxt=preg_replace("/<!--user_name-->/", $nome_user, $filetxt);
$filetxt=preg_replace("/<!--breadcrumb-->/", $breadcrumb, $filetxt);
$filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
$filetxt=preg_replace("/<!--legend_lower-->/", $legend_lower->html_legend_lower, $filetxt);
$filetxt=preg_replace("/<!--legend_upper-->/", $legend_upper->html_legend_upper, $filetxt);
$filetxt=str_replace("<br>", "<br/>", $filetxt);
die($filetxt);
?>
