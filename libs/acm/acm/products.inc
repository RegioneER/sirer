<?php 

$products=array("DRUG_REGISTRY" => "Drug Registry", "CLINICAL_TRIAL" => "Clinical Trial", "CRMS"=>"Clinical Research Management System", "LABORATORY_RANGE" => "Laboratory Ranges Management", "DRUPAL"=>"Drupal CMS Portal","SIMPLE_FOLDER"=>"Simple Folder"); //


function getProductAction($pType){
	$actions=array();
	if ($pType=="CLINICAL_TRIAL" || $pType=="LABORATORY_RANGE"){
		$wizard = array('LABEL' => 'Wizard study configurator', 'ICON' => 'magic', 'LINK' => url_for('study/wizard/[PREFIX]/1'), 'COLOR' => '#4060FF');
		$actions[] = $wizard;
		$aprofiles = array('LABEL' => 'Profile Management', 'ICON' => 'tags', 'LINK' => url_for('/study/profiles/[PREFIX]'), 'COLOR' => '#942494');
		$actions[] = $aprofiles;
		$ausers = array('LABEL' => 'User Profile Management', 'ICON' => 'users', 'LINK' => url_for('/study/list/profiles/[PREFIX]'), 'COLOR' => 'darkblue');
		$actions[] = $ausers;
		$acusers = array('LABEL' => 'Add/remove centers', 'ICON' => 'h-square', 'LINK' => url_for('/study/centers/[PREFIX]'), 'COLOR' => '#D32646'); //VAXMR-302
		// lightblue
		$actions[] = $acusers;
		if (preg_match("/\.dev\./i",$_SERVER['HTTP_HOST'])){ //GENHD-130 visualize Open Builder link only in development environment
			$abuilder = array('LABEL' => 'Open Builder', 'ICON' => 'gears', 'LINK' => url_for('/study/builder/[PREFIX]'), 'COLOR' => '#24A454');
			$actions[] = $abuilder;
		}
		$dblock = array('LABEL' => 'DB Lock', 'ICON' => 'lock', 'LINK' => url_for('/dblock/[PREFIX]'), 'COLOR' => '#333333');
		$actions[] = $dblock;
		$gitrepo = array('LABEL' => 'Manage GIT Repository', 'ICON' => 'git', 'LINK' => url_for('/study/gitrepo/[PREFIX]'), 'COLOR' => '#E0D50A');
		$actions[] = $gitrepo;
		$export = array('LABEL' => 'Export eCRFs', 'ICON' => 'line-chart', 'LINK' => url_for('/study/export/[PREFIX]').'" target="_blank', 'COLOR' => '#24A454'); //exchange
		$actions[] = $export;
        $gotostudy = array('LABEL' => 'Go to instance', 'ICON' => 'hand-o-right', 'LINK' => '../study/[DESCR]" target="_blank', 'COLOR' => '#FF8040');
        $actions[] = $gotostudy;

	} else if ($pType=="DRUPAL") {
        $gotostudy = array('LABEL' => 'Go to instance', 'ICON' => 'hand-o-right', 'LINK' => '../portal/[DESCR]" target="_blank', 'COLOR' => '#FF8040');
        $actions[] = $gotostudy;

    } else {
        $aprofiles = array('LABEL' => 'Profile Management', 'ICON' => 'tags', 'LINK' => url_for('/study/profiles/[PREFIX]'), 'COLOR' => '#942494');
        $actions[] = $aprofiles;
        $ausers = array('LABEL' => 'User Profile Management', 'ICON' => 'users', 'LINK' => url_for('/study/list/profiles/[PREFIX]'), 'COLOR' => 'darkblue');
        $actions[] = $ausers;
        if ($pType=='DRUG_REGISTRY'||preg_match("!XMR!",$pType)){
            $acusers = array('LABEL' => 'Add/remove centers', 'ICON' => 'h-square', 'LINK' => url_for('/study/centers/[PREFIX]'), 'COLOR' => '#D32646'); //VAXMR-302
            $actions[] = $acusers;
			$abuilder = array('LABEL' => 'Open Builder', 'ICON' => 'gears', 'LINK' => url_for('/study/builder/[PREFIX]'), 'COLOR' => '#24A454');
			$actions[] = $abuilder;
        }
        $gotostudy = array('LABEL' => 'Go to instance', 'ICON' => 'hand-o-right', 'LINK' => '../[DESCR]" target="_blank', 'COLOR' => '#FF8040');
        $actions[] = $gotostudy;
    }
	return $actions;
}



?>