<?
include_once "config.inc";
include_once "study.inc.php";
$config_service['filetxt']=$filetxt;
$study_=new Study($xml_dir, $service, "visite_exams.xml", $conn, $in, $config_service, $user, true, "<!--nome workflow-->");
$filetxt=preg_replace("/<!--body-->/", $study_->body, $filetxt);
die ($filetxt)


?>