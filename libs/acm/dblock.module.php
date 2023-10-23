<?php 

function dblock_init(){
	dispatch('/dblock/:study', 'dblock_page_list');
	dispatch('/dblock/list', 'dblock_page_list');
	dispatch('/dblock/list/:study', 'dblock_page_list');
	dispatch('/dblock/lock_center/:center/:function/:site_id', 'dblock_lock_center');
	dispatch('/dblock/unlock_center/:center/:function/:site_id', 'dblock_unlock_center');
	/*dispatch('/dblock/new', 'dblock_page_new');
	dispatch_post('/dblock/new', 'dblock_page_new');
	dispatch('/dblock/edit/:dblock_id/:study', 'dblock_page_edit');
	dispatch_post('/dblock/edit/:dblock_id/:study', 'dblock_page_edit');
	dispatch('/dblock/users/:dblock_id/:study', 'dblock_page_users');
	dispatch_post('/dblock/users/:dblock_id/:study', 'dblock_page_users');
	dispatch('/dblock/therapies_list_per_study/:study','_therapies_list_per_study');*/
}

function dblock_sidebar($sideBar){
	//$itm2=new SideBarItem(new Link(t("DB Lock"), "fa fa-lock", url_for('/dblock')));
	//$itm2->addItem(new SideBarItem(new Link(t("New dblock"), "plus", url_for('/dblock')), null, UIManager::_checkActive('/dblock')));
	//$itm2->addItem(new SideBarItem(new Link(t("List existing therapies"), "list", url_for('/dblock/list')), null, UIManager::_checkActive('/dblock/list')));
	//$sideBar->addItem($itm2);
	
	return $sideBar;
}

function dblock_breadcrumb($paths)
{
	if(UIManager::_checkActive('/dblock')){
		$paths[]=array(t("DB Lock"), t("DB Lock"), url_for('/dblock'));
// 		/*if(UIManager::_checkActive('/dblock/new')){
// 			$paths[]=array(t("New dblock"), t("New dblock"), url_for('/dblock/new'));
				
// 		}
// 		if(UIManager::_checkActive('/dblock/edit')){
// 			$paths[]=array(t("Edit dblock"), t("Edit dblock"), url_for('/dblock/edit'));
// 		}
// 		if(UIManager::_checkActive('/dblock/users')){
// 			$paths[]=array(t("Add users"), t("Add users"), url_for('/dblock/edit'));
// 		}
		
// 		if(UIManager::_checkActive('/dblock/list')){
// 			$paths[]=array(t("List existing therapies"), t("List existing therapies"), url_for('/dblock/list'));
// 		}*/
	}

	return $paths;
}

function dblock_getPageTitle($page_title){
	if(UIManager::_checkActive('/dblock')){
		$page_title=t("dblock");
		if(UIManager::_checkActive('/dblock/new')){
			$page_title=t("DB Lock");

		}
// 		if(UIManager::_checkActive('/dblock/edit')){
// 			$page_title=t("Edit dblock");
		
// 		}
// 		if(UIManager::_checkActive('/dblock/users')){
// 			$page_title=t("Add users to the dblock");
// 		}
// 		if(UIManager::_checkActive('/dblock/list')){
// 			$page_title=t("List existing therapies");
// 		}
	}
	return $page_title;
}


function dblock_page_list($study=null){
	$page = false;
	if (isset($_GET['page'])){
		$page = $_GET['page'];
	}
	$output = '';
	$m = UIManager::getInstance();
	
	if(!isset($study)){
		common_add_message(t("Please specify the study"),ERROR);
		$output.=new Link(t("Go to study list"), 'back', url_for('/study/list'));
		return html($output);
	}
	
	$list = _dblock_list_centers_status($study);
	// echo "<pre>";
	// print_r($list);
	// echo "</pre>";
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/study/dblock/list/'.$prefix);
    $caption=t("DB Lock centers");
	$labels = array('SITE ID' => array('NAME' => 'SITE_ID', 'TYPE' => 'TEXT', 'SORT' => 1),
                    'SITE CODE' => array('NAME' => 'CODE', 'TYPE' => 'TEXT'),
                    'SITE DESCR' => array('NAME' => 'DESCR', 'TYPE' => 'TEXT'),
                    'New Patient Registration' => array('NAME' => 'NEWPATIENT', 'TYPE' => 'LOCK_CENTER'),
					'Data entry' => array('NAME' => 'SAVESEND', 'TYPE' => 'LOCK_CENTER'),
					'Equery' => array('NAME' => 'EQUERY', 'TYPE' => 'LOCK_CENTER'),
					'Obvious Corrections' => array('NAME' => 'OBVIOUSCORRECTION', 'TYPE' => 'LOCK_CENTER')
					);
    //$actions = !$wizard;
	$actions = false;
	$output .= $m -> dsp_getTable($labels, $list, $actions);
    
	
	$output .=_dblock_legend();
	return html($output);
}

function _dblock_list_centers_status($prefix=null){
	global $custom_modules;
	$study_centers=_study_load_centers($prefix); //carico tutti i centri abilitati nel mio studio
	$my_centers=array();
	$dblock_centers=_dblock_load_centers($prefix); //carico i lock per tali centri
	foreach($study_centers as $key => $center){
		$center_dblock=$dblock_centers[$center['SITE_ID']]['DBLOCK'];
		$my_centers[$center['SITE_ID']]=$center;
		$my_centers[$center['SITE_ID']]['DBLOCK']=$center_dblock;
		/**OTTENGO IL VALORE DI DBLOCK COME BITMAP*/
		$center_dblock_bin=decbin($center_dblock);
		$center_dblock_bin=substr("00000000".$center_dblock_bin, -1*sizeof($custom_modules['DBLOCK_FUNCTIONS']));
		foreach($custom_modules['DBLOCK_FUNCTIONS'] as $func=>$value){
			//ASSEGNO IL VALORE PER OGNI FUNZIONE COME BIT (1 blocco abilitato, 0 blocco non abilitato)
			$my_centers[$center['SITE_ID']][$value]=substr($center_dblock_bin,-1*$func,1);
		}
		/** controllo se ci sono lock a livello di paziente o di visita o di esame OVERRIDE DELLE FUNZIONI DA PARTE DEI PAZIENTI*/
		/** prendo i valori presenti attualmente nella tabella relativa al DBLOCK per i pazienti di questo centro */
		$overrided_functions=array();
		$dblock_patients=_dblock_load_patients($prefix,$center['SITE_ID']);
		foreach($dblock_patients as $key=>$patient){
			$patient_dblock=$patient['DBLOCK'];
			$patient_dblock_bin=decbin($patient_dblock);
			$patient_dblock_bin=substr("00000000".$patient_dblock_bin, -1*sizeof($function));
			foreach($custom_modules['DBLOCK_FUNCTIONS'] as $func=>$value){
				//ASSEGNO IL VALORE PER OGNI FUNZIONE COME BIT (1 blocco abilitato, 0 blocco non abilitato) AL PAZIENTE SOVRASCRIVENDO QUELLA EREDITATA DAL CENTRO
				if($my_centers[$center['SITE_ID']][$value]!=substr($patient_dblock_bin,-1*$func,1)){
					//echo "<b>{$value} DIVERSI!!!!</b><br/> ";
					$my_centers[$center['SITE_ID']]['OVERRIDED_'.$value]++;
				}
			}
			//SETTO A 0 IL BIT PER IL BLOCCO DELL'ARRUOLAMENTO IN MODO DA CONTROLLARE L'UGLIAGLIANZA DEI BIT RESTANTI
			$center_dblock_bin=substr_replace($center_dblock_bin,'0',-1*array_search('NEWPATIENT', $custom_modules['DBLOCK_FUNCTIONS']),1);
			if($patient_dblock_bin==$center_dblock_bin){
				$my_centers[$center['SITE_ID']]['OVERRIDED_EQUAL']++;
			}
		 }
	}
	
	
	return $my_centers;
}


function _dblock_load_centers($study_prefix){
	$retval = array();
	$str="select * from {$study_prefix}_dblock  where codpat =-1 and visitnum =-1 and esam =-1";
	$rs = db_query($str);
	while ($row = db_nextrow($rs)){
		$retval[$row['CENTER']] = $row;
	}
	return $retval;
}
function _dblock_load_patients($study_prefix,$center_id){
	$retval = array();
	$str="select * from {$study_prefix}_dblock where CENTER={$center_id} and codpat !=-1";
	$rs = db_query($str);
	while ($row = db_nextrow($rs)){
		$retval[$row['CENTER']] = $row;
	}
	return $retval;
}

function _dblock_legend(){
	$output='';
	$output.="<div class=\"widget-box\">
					<div class=\"widget-header\">
						<h5>".t('Legend')."</h5>
					</div>
					<div class=\"widget-body\" style=\"padding:10px\">
							<p><i class=\"fa fa fa-lock red\"></i> ".t("Functionality locked")."</p>
							<p><i class=\"fa fa-unlock green\"></i> ".t("Functionality unlocked")."</p>
					</div>
			</div>";
	return $output;
}
function dblock_unlock_center($prefix,$function,$id_center){
	dblock_lock_center($prefix,$function,$id_center,false);
}
function dblock_lock_center($prefix,$function,$id_center,$lock=true){
	global $custom_modules;	
	$centers=_dblock_list_centers_status($prefix);
	$my_center=$centers[$id_center];
	
	//sovrascrivo la funziona da disabilitare
	$my_center[$function]=$lock ? 1 : 0;
	$dblockbin="";
	foreach($custom_modules['DBLOCK_FUNCTIONS'] as $func => $funzione){
		if($my_center[$funzione]=="0"){
			$dblockbin="0".$dblockbin;
		}
		else{
			$dblockbin="1".$dblockbin;
		}
	}//funzione
			
	$dblock=bindec($dblockbin);
	
	//print_r($dblock);
	
	$row['DBLOCK'] = $dblock;
	$row['CENTER'] = $id_center;
	$row['CODPAT'] = "-1";
	$row['VISITNUM'] = "-1";
	$row['ESAM'] = "-1";
	$table=$prefix."_DBLOCK";
	$exists=_dblock_load_centers($prefix);
	$action=isset($exists[$id_center]) ? ACT_MODIFY : ACT_INSERT;
	//$retval=db_form_updatedb($table, $row,$action, array('CENTER','CODPAT','VISITNUM','ESAM'));
	if($action==ACT_MODIFY){
		$row[OLDPREFIX . 'CENTER'] = $id_center;
		$row[OLDPREFIX . 'CODPAT'] = "-1";
		$row[OLDPREFIX . 'VISITNUM'] = "-1";
		$row[OLDPREFIX . 'ESAM'] = "-1";
		$retval=db_update_row($table,$row,array('CENTER','CODPAT','VISITNUM','ESAM'));
	}
	else{
		$retval=db_insert_row($table,$row,array('CENTER','CODPAT','VISITNUM','ESAM'));
	}
	$centers=_dblock_list_centers_status($prefix);
	header("location: " . url_for('/dblock/' . $prefix));
	die();	
}
?>