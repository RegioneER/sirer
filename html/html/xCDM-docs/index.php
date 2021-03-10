<?php 
require_once 'vendor/autoload.php';

$baseFolder=$_SERVER['DOCUMENT_ROOT']."/xCDM-docs/";
$loader = new Twig_Loader_Filesystem($baseFolder.'templates');
$twig = new Twig_Environment($loader, array(
		'debug' => true,
		//'cache' => $baseFolder.'cache',
));

$vars["titolo"]="Documentazione xCDM";
$config=file_get_contents("configurations/{$_GET['service']}/config.json");
include_once 'libs/parseConfig.php';
$vars['rootAble']=$rootAble;
#$vars['types']=$types;
$vars['processes']=$processes;
$vars['processesDetail']=$processesDetails;
$vars['defaultDiplay']='none';

$vars['types']=[];
$processedTypes=[];
function recursiveExplore($list){
    global $vars;
    global $types;
    foreach ($list as $typeName){
        if (!isset($processedTypes[$typeName])){
            $vars['types'][]=$types[$typeName];
            $processedTypes[$typeName]=true;
            recursiveExplore($types[$typeName]->allowedChildNames);
        }
    }
}

recursiveExplore($rootAble);

$function = new Twig_SimpleFunction('dump', function ($var) {
	return "<pre>".var_export($var, true)."</pre>";
});

$function2 = new Twig_SimpleFunction('booleanToCheck', function ($var) {
	if ($var) return "<strong>X</strong>";
	else return "&nbsp;";
});


$function3 = new Twig_SimpleFunction('base64Decode', function ($var) {
	return base64_decode($var);
});
 
$function4 = new Twig_SimpleFunction('processImage', function ($var) {
	$var=str_replace(" ", "_", $var);
	return "<img src=\"https://sirer-test.sissprep.cineca.it/xCDM-docs/configurations/{$_GET['service']}/imgs/{$var}.png\"/>";
});



$twig->addFunction($function);

$twig->addFunction($function2);

$twig->addFunction($function3);

$twig->addFunction($function4);

echo $twig->render('index.html.twig', $vars);