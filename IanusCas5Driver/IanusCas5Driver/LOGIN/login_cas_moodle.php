<?php


$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
if ($language=='') $language='en';
$language=strtolower($language);


if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login_template_cas.html")) $template=file_get_contents($_SERVER['DOCUMENT_ROOT']."/authzssl/login_template_cas.html");
else $template=file_get_contents("/http/lib/IanusCasDriver/LOGIN/template/login_template.html");

if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login.css")) {
	$template=str_replace("<!--custom_css-->", "<link rel=\"stylesheet\" href=\"/authzssl/login.css\" />", $template);
}
if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login-logo.png")) {
	$template=str_replace("<!--login_logo-->", "<div class=\"center\"><img src=\"/authzssl/login-logo.png\"/></div>", $template);
}

$commonMessageFile="/http/lib/IanusCasDriver/LOGIN/messages_{$language}.inc";
$defaultMessageFile="/http/lib/IanusCasDriver/LOGIN/messages_en.inc"; //Questa è la lingua di default!
$customMessageFile=$_SERVER['DOCUMENT_ROOT']."/authzssl/messages_{$language}.inc";
if (file_exists($customMessageFile)) {
	include_once $customMessageFile;
}
else {
	if (file_exists($commonMessageFile)) {
		include_once $commonMessageFile;
	}
	else {
		include_once $defaultMessageFile; 
	}
}
if ($_SERVER['DOCUMENT_ROOT']."/authzssl/login-copyright.html") {
	$copyright_file_content=file_get_contents($_SERVER['DOCUMENT_ROOT']."/authzssl/login-copyright.html");
}
else {
	$copyright_file_content=file_get_contents("/http/lib/IanusCasDriver/LOGIN/login-copyright.html");
}
if (!isset($_POST) || count($_POST)==0){
	
	if (strtoupper($language) == strtoupper("it")){$language_show='IT';}else {$language_show='EN';}
	$sql_get_msg_ts="select MESSAGGIO_LOGIN_{$language_show} as message from CAS_SERVICES where 
			upper(URL)='".strtoupper($_SERVER['HTTP_HOST'])."'
			and sysdate between messaggio_from_dt and messaggio_to_dt";
	$sql2=new DriverIanusSql($DriverIanusConnection);
	if ($sql2->getRow($sql_get_msg_ts)){
	$loginMsgOut=$sql2->row['MESSAGE'];
		ini_set( 'date.timezone', 'Europe/Rome' );
		$template = preg_replace("/<!-- out_code -->/i", "<center><div style='min-width:340px;width:50% !important' class='alert alert-warning'>".$loginMsgOut."</div></center>", $template);
	}
	
	$cookieSpecFile="cookiespec_".strtolower($language_show).".html";
	$tagCookie=file_get_contents("/http/lib/DriverIanus/cookieConsent/".$cookieSpecFile);
	
	$cssCookie='<link rel="stylesheet" type="text/css" href="/authzssl/cookieConsentCss"/>';
	

	$template=preg_replace("!</head>!i", $cssCookie."</head>", $template);
	$template=preg_replace("!</body>!i", $tagCookie."</body>", $template);
	
	$loginUrl=$_GET['loginCallBack'];
	$form=file_get_contents("/http/lib/IanusCasDriver/LOGIN/template/login_form.html");
	$form=str_replace("__service__", $_GET['service'], $form);
	$form=str_replace("__lt__", $_GET['lt'], $form);
	$form=str_replace("__loginCallBack__", $_GET['loginCallBack'], $form);
	$form=str_replace("__execution__", $_GET['execution'], $form);
	$template=str_replace("__widget_content__", $form, $template);
	$template=str_replace("__title_page__", $messages['__title_page__'], $template);
	$template=str_replace("<!--copyright-->", $copyright_file_content, $template);
	$template=str_replace("__welcome_login_message__", $messages['__welcome_login_message__'], $template);
	$template=str_replace("__username__", $messages['__username__'], $template);
	$template=str_replace("__password__", $messages['__password__'], $template);
	$template=str_replace("__login_button_label__", $messages['__login_button_label__'], $template);
	$template=str_replace("__forgot_password__", $messages['__forgot_password__'], $template);
	$template=str_replace("__forgot_username__", $messages['__forgot_username__'], $template);
	
	if (isset($_GET['loginError']) && $_GET['loginError']=='true'){
		$template=str_replace("__error_message__", "<div class=\"alert alert-danger\">".$messages['__error_message__']."</div>", $template);
	}else {
		$template=str_replace("__error_message__", '', $template);
	}
	
}else {
	$loginUrl=$_POST['loginCallBack']."?service=".urlencode($_POST['service']);
	unset ($_POST['loginCallBack']);
	unset ($_POST['service']);
	$_POST['username'].="@".$_SERVER['HTTP_HOST'];
	$form="<form id='login_form' method='post' name='login' action='$loginUrl' enctype='application/x-www-form-urlencoded'>";
	foreach ($_POST as $key=>$val){
		if ($key=='submit') $form.="<noscript><input type='submit' name='_{$key}' value='$val'/></noscript>";
		else $form.="<input type='hidden' name='$key' value='$val'/>";
	}
	$form.="</form>";
	$loading="<div style=\"padding:4px\"><h2 style=\"padding-right:60px;float:right;\">".$messages['__processing__']."...</h2><i class=\"fa fa-spinner fa-spin fa-4x\"></i> </div>";
	$content=$form.$loading;
	
	$template=str_replace("__widget_content__", $content, $template);
	
	$template.="<script>
		$(document).ready(function(){
			$('#login_form').submit();
		});
	</script>";
}

die($template);
	