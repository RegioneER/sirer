<?php 

define("SYSTEMBASEURL_LIBRARY",$_SERVER['DOCUMENT_ROOT']."/../libs/acm/");
define("GITREPO_ROOTFOLDER","/cvsroot/siss-git/projects/genes");
define("LOCAL_GIT_BIN",'/http/local/bin/git');
define("IDP_NAME","GENIUS"); //CTP
define("SERVICE_FOLDER","demogst"); //aieop
define("GIT_EMAIL","geniussuite@cineca.it");
define("GIT_USER","GENIUS System");

if ( preg_match("/\.dev\./i",$_SERVER['HTTP_HOST']) || preg_match("/\.sissdev\./i",$_SERVER['HTTP_HOST']) || preg_match("/\.sisslocal\./i",$_SERVER['HTTP_HOST']) || preg_match("/axmr-local/i",$_SERVER['HTTP_HOST']) ) {
	define("LOCAL_SSH_SERVER","siss01.private.cineca.it");
} elseif (preg_match("/\.test\./i",$_SERVER['HTTP_HOST']) || preg_match("/\.sissprep\./i",$_SERVER['HTTP_HOST'])) {
	define("LOCAL_SSH_SERVER","siss03.private.cineca.it");
} else {
	define("LOCAL_SSH_SERVER","siss05.private.cineca.it");
}
if ( preg_match("/\.sisslocal\./i",$_SERVER['HTTP_HOST']) || preg_match("/axmr-local/i",$_SERVER['HTTP_HOST']) || preg_match("/localhost/i",$_SERVER['HTTP_HOST']) ) {
	define("BUILDER_ACTIVITI",0); //false
}else{
    define("BUILDER_ACTIVITI",1); //true
}