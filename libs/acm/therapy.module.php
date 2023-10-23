<?php 

function therapy_init(){
	dispatch('/therapy', 'therapy_page_new');
	dispatch('/therapy/new', 'therapy_page_new');
	dispatch('/therapy/list', 'therapy_page_list');
	dispatch('/therapy/list/:study', 'therapy_page_list');
	dispatch_post('/therapy/new', 'therapy_page_new');
	dispatch('/therapy/edit/:therapy_id/:study', 'therapy_page_edit');
	dispatch_post('/therapy/edit/:therapy_id/:study', 'therapy_page_edit');
	dispatch('/therapy/users/:therapy_id/:study', 'therapy_page_users');
	dispatch_post('/therapy/users/:therapy_id/:study', 'therapy_page_users');
	dispatch('/therapy/therapies_list_per_study/:study','_therapies_list_per_study');
	
	dispatch('/therapy/users/delete/:therapy_id/:study/:user_id','_therapy_user_delete');
}

function therapy_sidebar($sideBar){
	$itm2=new SideBarItem(new Link(t("Therapies"), "medkit", "#"));
	$itm2->addItem(new SideBarItem(new Link(t("New therapy"), "plus", url_for('/therapy/new')), null, UIManager::_checkActive('/therapy/new')));
	$itm2->addItem(new SideBarItem(new Link(t("List existing therapies"), "list", url_for('/therapy/list')), null, UIManager::_checkActive('/therapy/list')));
	$sideBar->addItem($itm2);
	
	return $sideBar;
}

function therapy_breadcrumb($paths)
{
	if(UIManager::_checkActive('/therapy')){
		$paths[]=array(t("Therapies"), t("Therapies"), url_for('/therapy/list'));
		if(UIManager::_checkActive('/therapy/new')){
			$paths[]=array(t("New therapy"), t("New therapy"), url_for('/therapy/new'));
				
		}
		if(UIManager::_checkActive('/therapy/edit')){
			$paths[]=array(t("Edit therapy"), t("Edit therapy"), url_for('/therapy/edit'));
		}
		if(UIManager::_checkActive('/therapy/users')){
			$paths[]=array(t("Add users"), t("Add users"), url_for('/therapy/edit'));
		}
		
		if(UIManager::_checkActive('/therapy/list')){
			$paths[]=array(t("List existing therapies"), t("List existing therapies"), url_for('/therapy/list'));
		}
	}

	return $paths;
}

function therapy_getPageTitle($page_title){
	if(UIManager::_checkActive('/therapy')){
		$page_title=t("Therapy");
		if(UIManager::_checkActive('/therapy/new')){
			$page_title=t("New therapy");

		}
		if(UIManager::_checkActive('/therapy/edit')){
			$page_title=t("Edit therapy");
		
		}
		if(UIManager::_checkActive('/therapy/users')){
			$page_title=t("Add users to the therapy");
		}
		if(UIManager::_checkActive('/therapy/list')){
			$page_title=t("List existing therapies");
		}
	}
	return $page_title;
}

function therapy_form($row){
	$output = "";
	$m = UIManager::getInstance();
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';
//	var_dump($row);
// 	$row['PT_CODE']="";
// 	$row['STUDY_PREFIX']="";
	$studies = _therapy_get_studies();
	$optstudies = array();
	//var_dump($studies);
	foreach ($studies as $k=>$p){
		$optstudies[$k] = $p;
	}
	//var_dump($optstudies);
	$readonly=false;
	if(UIManager::_checkActive('/therapy/edit')){
		$readonly=true;
		$output .= ''.$m->dsp_getTextField('Study', 'STUDY_PREFIX', '', '', $readonly, $row['STUDY_PREFIX'], false,true);
	}
	else{
		$output .= ''.$m->dsp_getSelectField('Study', 'STUDY_PREFIX', '', '', false, $row['STUDY_PREFIX'], $optstudies,false,true);
	}
	
	
	$output .= ''.$m->dsp_getHiddenField('PT_CODE', false, $row).'';
	$output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'PT_CODE', $row['PT_CODE'], false).'';
	$output .= ''.$m->dsp_getTextField('Name', 'PT_DECODE', '', '', false, false,$row,true).'';
	$output .= ''.$m->dsp_getTextField('Valutazione', 'PT_VALUTAZIONE', '', '', false, false,$row,false).'';
	$output .= ''.$m->dsp_getTextField('F_TO_CALL_ELEG', 'F_TO_CALL_ELEG', '', '', false, false,$row,false).'';
	$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
	$output .= '</form>';
	return $output;	
}
function therapy_form_validate(){
	$retval = true;
	$row = $_POST;
	if (!isset($row['STUDY_PREFIX'])||!$row['STUDY_PREFIX']){
		common_add_message(t("Please specify the field ")."'".t("Study")."'",WARNING);
		$retval = false;
	}
	if (!$row['PT_DECODE']){
		common_add_message(t("Please specify the field ")."'".t("Name")."'",WARNING);
		$retval = false;
	}
	return $retval;
}
function therapy_form_submit($action){
	$retval = false;
	$row = $_POST;
	unset($row['submit-button']);
	unset($row['reset-button']);

	//$row = common_booleanCheckBox($row, 'ACTIVE');

	$row['PT_DECODE'] = trim($row['PT_DECODE']);
	$row['PT_VALUTAZIONE'] = trim($row['PT_VALUTAZIONE']);
	$row['F_TO_CALL_ELEG'] = trim($row['F_TO_CALL_ELEG']);
	$table = $row['STUDY_PREFIX']."_LISTA_PT";
	
	unset($row['STUDY_PREFIX']);
	
	if ($action == ACT_INSERT){
		$id = db_getmaxdbvalue($table,'PT_CODE');
		$row['PT_CODE'] = common_nextId($id,1);
		$_POST['PT_CODE'] = $row['PT_CODE'];
		
	}

	if (db_form_updatedb($table, $row, $action, 'PT_CODE')){
		common_add_message(t("Action executed!"), INFO);
		$retval = true;
	}
	return $retval;

}

function therapy_page_new(){
	$output = "";
	/*
	 $d = Dispatcher::getInstance();
	$d->therapy_new();
	return html($d->dsp_getPageContent());
	*/
	//$m = UIManager::getInstance();
	$row = array();
	$row['PT_CODE']="";
	$row['STUDY_PREFIX']="";
	//$row['COUNTRY']="";
	if ($_POST){
		if (therapy_form_validate(ACT_INSERT)){
			if (therapy_form_submit(ACT_INSERT)){
				header("location: ".url_for('/therapy/list'));
				die();
			}else{
				$output .= t("An error occurred during therapy creation.");
			}
		}
		$row = $_POST;
	}
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">
				';
	$output .= therapy_form($row);
	$output .= '
			</form>';
	return html($output);
}

function therapy_page_edit($therapy_id,$study_prefix){
	$output = "";
	$row =_therapy_load_therapy($therapy_id,$study_prefix);
	if ($_POST){
		if (therapy_form_validate(ACT_MODIFY)){
			if (therapy_form_submit(ACT_MODIFY)){
				header("location: ".url_for('/therapy/list'));
				die();
			}else{
				$output .= t("An error occurred during therapy update.");
			}
		}
		$row = $_POST;
	}
	$row['STUDY_PREFIX']=$study_prefix;
	$output .= therapy_form($row);
	return html($output);
}
/*
function therapy_pageglobal_list($page){
	if (!isset($page)){
		$page = false;
	}
	return therapy_page_list(null, $page);
}
function therapy_pagestudy_list($study,$page){
	if (!isset($page)){
		$page = false;
	}
	if (!isset($study) || is_numeric($study)){
		header("location: ".url_for('/therapy/list/'));
		die();
	}
	return therapy_page_list($study, $page);
}
*/
function therapy_page_list($study=null){
	$page = false;
	if (isset($_GET['page'])){
		$page = $_GET['page'];
	}
	$output = '';
	$m = UIManager::getInstance();
	$studies = _study_list();
	$optstudies = array();
	//var_dump($studies);
	foreach ($studies as $k=>$p){
		$optstudies[$p['PREFIX']] = $p['PREFIX']." - ".$p['DESCR'];
	}
	$onaction= 'onchange="document.location=\''.url_for('/therapy/list/').'/\'+$(\'#STUDY_PREFIX\').val()";';
	$output .= ''.$m->dsp_getSelectField('Filter by Study ', 'STUDY_PREFIX', '', '', false, $study, $optstudies,$onaction);
	$output .= '<p>&nbsp;</p>';
	$list = _therapy_list_therapies($study);
	$labels=array('Study Prefix'=>array('NAME'=>'STUDY_PREFIX','TYPE'=>'TEXT'),'PT_CODE'=>array('NAME'=>'PT_CODE','TYPE'=>'TEXT'),'PT_DECODE'=>array('NAME'=>'PT_DECODE','TYPE'=>'TEXT'));
 	$actions = array();
 	$aedit = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/therapy/edit/[PT_CODE]/[STUDY_PREFIX]'));
 	$a_addusers = array('LABEL'=>'Add users','ICON'=>'users','LINK'=>url_for('/therapy/users/[PT_CODE]/[STUDY_PREFIX]'),'COLOR'=>'darkblue');
 	//$adelete = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>url_for('/therapy/delete/[ID]'),'COLOR'=>'#FA3A3A');
 	$actions[] = $aedit;
 	$actions[] = $a_addusers;
 	//$actions[] = $adelete;
 	$output .=$m->dsp_getTable($labels,$list,$actions,$page);
 	//$output .=$m->dsp_getTable($columns,$list);
	return html($output);
}

function _therapy_list_therapies($filter_study=null){
	$retval = array();
	
	$query=" ";
	$union=" ";
	if(!isset($filter_study)){
		$studies = _study_list();
		$optstudies = array();
		//var_dump($studies);
		foreach ($studies as $k=>$p){
			$table=$p['PREFIX']."_LISTA_PT";
			//echo $table."<br/>";
			if(db_table_exists($table)){
				$query.=$union." SELECT '".$p['PREFIX']."' as STUDY_PREFIX, lista.* FROM  ".$table." lista ";
				$union=" UNION ";
			}
			else{
				_therapy_create_tables($p['PREFIX']);
			}
		}
	}
	else{
		$table=$filter_study."_LISTA_PT";
		if(db_table_exists($table)){
			$query=" SELECT '".$filter_study."' as STUDY_PREFIX, lista.* FROM  ".$table." lista ";
		}
		else{
			_therapy_create_tables($filter_study);
		}
	}
	//echo $query;
	$bind=array();
	$rs = db_query_bind($query,$bind);
	while ($row = db_nextrow($rs)){
		$retval[] = $row;
	}
	return $retval;
}


function _therapy_load_therapy($therapy_id,$study_prefix){
	$retval = array();
	$bind = array();
	$bind['KEY'] = $therapy_id;
	$rs = db_query_bind("SELECT * FROM ".$study_prefix."_LISTA_PT WHERE PT_CODE = :KEY ",$bind);
	if ($row = db_nextrow($rs)){
		$retval = $row;
	}
	return $retval;
}

// function center_page_users_selstudy($center_id){
// 	$output = "";
// 	$output .="<p>".t('Select the study ')."</p>";
// 	/*if ($_POST){
// 		if (center_users_selstudy_validate()){
// 				header("location: ".url_for('/center/list'));
// 				die();
// 			}else{
// 				$output .= t("An error occurred during study selection.");
// 			}
// 		}
// 	*/
// 	$output .= center_users_selstudy_form();
// 	return html($output);
// }

// function center_user_selstudy_validate(){
// 	return true;
// }

// function center_users_selstudy_form(){
// 	$output = "";
// 	$m = UIManager::getInstance();
// 	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';
// 	$studies=_center_get_studies();
// 	$output .= ''.$m->dsp_getSelectField('Study', 'STUDY', 'choose a study', '', false, false,$studies).'';
// 	$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
// 	$output .= '</form>';
// 	return $output;
// }

function _therapy_get_studies(){
	$retval = array();
	$bind = array();
	$bind['KEY']="DRUG_REGISTRY";
	//$bind['SET'] = $glbProfileIdsSET;
	$rs = db_query_bind('SELECT PREFIX,DESCR FROM STUDIES WHERE ACTIVE=1 AND TYPE=:KEY',$bind);
	while ($row = db_nextrow($rs)){
		$retval[$row['PREFIX']] = $row['DESCR']." (".$row['PREFIX'].")";
	}
	return $retval;
}

function _therapies_list_per_study($study){
	$retval = array();
	$bind['KEY']="DRUG_REGISTRY";
	//$bind['SET'] = $glbProfileIdsSET;
	$rs = db_query_bind("SELECT ss.*,s.DESCR FROM SITES_STUDIES ss,SITES s,STUDIES st WHERE ss.SITE_ID=s.ID AND ss.STUDY_PREFIX=st.PREFIX and st.TYPE=:KEY",$bind);
	while ($row = db_nextrow($rs)){
			$retval[$row['STUDY_PREFIX']][] = $row;
	}
	$return="";
	if($study==""){
		$return=$retval;
	}
	else{
		$return=$retval[$study];
	}
	//echo $study;
	//var_dump($return);
	if(isAjax()){
		echo json_encode(array_merge(array("sstatus" => "ok"), $return));
		die();
	}
	else{
		return $return;
	}
}

function _therapy_create_tables($prefix){
	global $custom_modules;
	//var_dump($custom_modules["THERAPY_TABLES"]);
	foreach($custom_modules["THERAPY_TABLES"] as $table=>$columns){
		$SQL="CREATE TABLE {$prefix}_{$table} (";
		$comma="";
		foreach($columns as $name=>$type){
			
			$SQL.="{$comma} $name $type";
			$comma=",";
		}
		$SQL.=")";
		//var_dump($SQL);
		$rs=db_query($SQL);
		//var_dump($rs);
	}
	
	
}
//GESTIONE UTENTI
function therapy_page_users($therapy_id,$study_prefix){
	$m = UIManager::getInstance();
	$_therapy=_therapy_load_therapy($therapy_id,$study_prefix);
	$therapy_decode=$_therapy['PT_DECODE'];
	$output = "";
	$output .= "<p>User list for the therapy <b>".$therapy_decode."</b> of the study <b>".$study_prefix."</b></p>";
	$list =_therapy_load_users($therapy_id,$study_prefix);
	$labels=array('USERID'=>array('NAME'=>'MEDICO','TYPE'=>'TEXT'),'Name'=>array('NAME'=>'NOME','TYPE'=>'TEXT'),'Surname'=>array('NAME'=>'COGNOME','TYPE'=>'TEXT'));
	$adelete = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>'javascript:confirm_alert(\'Do you confirm the deletion of the user?\',\'USER DELETION\',\''.url_for('/therapy/users/delete/'.$therapy_id.'/'.$study_prefix.'/[MEDICO]').'\')','COLOR'=>'#FA3A3A');
 	$actions[] = $adelete;
	$output .=$m->dsp_getTable($labels,$list,$actions); //study_list_users($list);
	$row = array();
	$row['MEDICO'] = "";
	if ($_POST){
		if (therapy_users_form_validate()){
			if (therapy_users_form_submit($therapy_id,$study_prefix,$list)){
				header("location: ".url_for('/therapy/users/'.$therapy_id.'/'.$study_prefix));
				die();
			}else{
				$output .= t("An error occurred during study update.");
			}
		}
		$row = $_POST;

	}
	$output .= therapy_users_form($row, $therapy_id,$study_prefix);
	return html($output);
}

function _therapy_load_users($therapy_id,$study_prefix){
	$retval = array();
	//echo "SETSTRING: $glbProfileIdsSET<br/>";
	$bind = array();
	$bind['KEY']=$therapy_id;
	//$bind['SET'] = $glbProfileIdsSET;
	$rs = db_query_bind("SELECT medico.MEDICO,s.NOME,s.COGNOME FROM ".$study_prefix."_MEDICO_PT medico,ANA_UTENTI_1 s WHERE medico.MEDICO=s.USERID AND medico.PT_CODE=:KEY ",$bind);
	while ($row = db_nextrow($rs)){
		//$row['D_PROFILE'] = $profiles[$row['CODE']]['descrizione'];
		$retval[] = $row;
	}
	//var_dump($retval);
	return $retval;
}

function therapy_users_form($row,$therapy_id,$study_prefix){
	$m = UIManager::getInstance();
	$output = "";
	$output .= "<p>Add new / edit therapy</p>";
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';
	//$output .= ''.$m->dsp_getHiddenField('PREFIX', $row['PREFIX'], false,$row).'';
	$users = _user_list_users();
	$optusers = array();
	foreach ($users as $u){
		$optusers[$u['USERID']] = $u['USERID'];
	}
	//var_dump($row);
	$output .= ''.$m->dsp_getSelectField('USER', 'MEDICO', '', '', false, $row['MEDICO'], $optusers,null,true);
	//$output .= ''.$m->dsp_getCheckbox('STATUS', 'ACTIVE', '', 'Enabled', false, false, $row).'';
	$output .= ''.$m->dsp_getHiddenField('PT_CODE', $therapy_id);
	$output .= ''.$m->dsp_getHiddenField('STUDY_PREFIX', $study_prefix);
	$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
	$output .= '</form>';
	return $output;
}
function therapy_users_form_validate(){
	$retval=true;
	$row = $_POST;
	if (!$row['MEDICO']){
		common_add_message(t("Please specify the field ")."'".t("USERID")."'",WARNING);
		$retval = false;
	}
	return $retval;
}
function therapy_users_form_submit($therapy_id,$study_prefix, $list){
	$retval = false;
	$row = $_POST;

	unset($row['submit-button']);
	unset($row['reset-button']);

	$table = $study_prefix."_MEDICO_PT";
	$action = ACT_INSERT;
	foreach ($list as $up){
		if ($up['MEDICO']==$row['MEDICO'] && $up['PT_CODE']==$row['PT_CODE']){
			$action = ACT_MODIFY;
			break;
		}
	}
	unset($row['STUDY_PREFIX']);
	//$row = common_booleanCheckBox($row, 'ACTIVE');
	//common_add_message(print_r($row,true), INFO);
	$keys = array('MEDICO','PT_CODE');
	if (db_form_updatedb($table, $row, $action, $keys)){
		if ($action == ACT_INSERT){
			common_add_message(t("New user/therapy inserted correctly."), INFO);
		}else{
			common_add_message(t("Existing user/therapy modified."), INFO);
		}
		$retval = true;
	}
	return $retval;
}

function _therapy_user_delete($therapy_id,$study_prefix,$user_id){
	$output="";
	$m = UIManager::getInstance();
	$table = $study_prefix."_MEDICO_PT";
	$sql="DELETE FROM {$table} WHERE MEDICO=:USERID AND PT_CODE=:THERAPY_ID ";
	$bind=array();
	$bind['USERID']=$user_id;
	$bind['THERAPY_ID']=$therapy_id;
	if(db_query_update_bind($sql,$bind,true)){
		common_add_message(t("You have deleted the user id <b>".$user_id."</b> from therapy <b>".$therapy_id."</b>"), INFO);
	}
	else{
		common_add_message(t("There was an error during the deletion of the user id <b>".$user_id."</b> from therapy id <b>".$therapy_id."</b>"), ERROR);
	}
	header("location: ".url_for('/therapy/users/'.$therapy_id.'/'.$study_prefix));
	die();
}
//FINE GESTIONE UTENTI
?>