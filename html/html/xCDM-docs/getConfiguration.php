<?php 
$service="sirer";
$config=file_get_contents("configurations/{$service}/config.json");
include_once 'libs/parseConfig.php';

foreach ($types as $type){
	
	foreach ($type->associatedWorkflows as $processData){
		
		$processKeys[$processData->processKey]=true;
		
	}
	

}

foreach ($processKeys as $key=>$val){
	
	echo "<li>Processing $key</li>";

	//$processesUrl="https://gdelsignore:xxx@crpms.sissdev.cineca.it/CRPMS/services/process-engine/repository/process-definitions?key={$key}&latest=true";
    $processUrlUserPWD"https://VMAZZEO:TEST123@";
	$processesUrl=$processUrlUserPWD."sirer-test.sissprep.cineca.it/sirer-test/services/process-engine/repository/process-definitions?key={$key}&latest=true";
	
	$processes=file_get_contents($processesUrl);

	$processesObj=json_decode($processes);

	$process=$processesObj->data[0];
	
	$urlImg=str_replace("resources", "resourcedata",  $process->diagramResource);
	
	//$urlImg=str_replace("https://", "https://gdelsignore:xxx@", $urlImg);
		
	$urlImg=str_replace("https://", $processUrlUserPWD, $urlImg);
	
	$pkfile=str_replace(" ", "_", $key);
	
	$filedest="configurations/{$service}/imgs/".$pkfile.".png";
	
	file_put_contents($filedest, file_get_contents($urlImg));

}