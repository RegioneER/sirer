<?php

function profile_init(){
	dispatch('/profile', 'profile_page_new');
	//dispatch('/profile/new', 'profile_page_new');
	dispatch('/profile/list', 'profile_page_list');
	dispatch('/profile/manage_profile_per_study/:study/:profile','manage_profile_per_study_page');
	dispatch('/profiles/profiles_list_per_study/:study','_profiles_list_per_study');
	dispatch('/profiles/profiles_list_no_global_per_study/:study','_profiles_list_no_global_per_study'); //VAXMR-297
	dispatch('/profiles/study/toggle/:prefix/:username/:profileid/:verbose', 'study_profile_toggle_user'); //VAXMR-297
	dispatch('/profiles/study/toggle_study_profile/:prefix/:profileid/:active', 'study_profile_toggle_study_profile'); //VAXMR-297
	dispatch('/profiles/study/center/toggle/:username/:prefix/:siteid/:profileid/:verbose', 'study_profile_center_toggle_user'); //VAXMR-297
	dispatch('/profiles/study/get_profile_study_users/:prefix/:jqGrid/:profile_code', '_study_profile_load_users'); //VAXMR-297
	dispatch('/profiles/study/get_profile_study_users_centers/:prefix/:jqGrid/:profile_code','_study_profile_load_users_centers');
	dispatch('/profiles/study/get_profile_study_users_not_associated/:prefix/:jqGrid/:profile_code', '_study_profile_load_users_not_associated'); //VAXMR-297
	dispatch('/profiles/study/get_profile_study_center_users_not_associated/:prefix/:jqGrid/:profile_code/:site_id', '_study_profile_load_users_centers_not_associated'); //VAXMR-297
	dispatch('/profiles/study/assoc_new_user_global/:prefix/:username/:profileid', '_study_profile_assoc_new_user_global'); //VAXMR-297
	dispatch('/profiles/study/assoc_new_user_noglobal/:prefix/:username/:profileid/:centerid', '_study_profile_assoc_new_user_noglobal'); //VAXMR-297
	dispatch('/profiles/profiles_list_per_study/:study/:jqGrid','_profiles_list_per_study');
	dispatch('/profiles/studies_profiles/:jqGrid/:study','_studies_profiles');
}

function profile_sidebar($sideBar){
	$itm2=new SideBarItem(new Link(t("Profiles"), "tags", "#"));
	//$itm2->addItem(new SideBarItem(new Link("New ACL profile", "plus", url_for('/profile/new')), null, UIManager::_checkActive('/profile/new')));
	$itm2->addItem(new SideBarItem(new Link(t("Active Profiles per Product Instance"), "list", url_for('/profile/list')), null, UIManager::_checkActive('/profile/list')));
	$sideBar->addItem($itm2);
	
	return $sideBar;
}

function profile_breadcrumb($paths)
{
	if(UIManager::_checkActive('/profile/')){
		$paths[]=array(t("Profiles"),t("Profiles"), url_for('/profile/list'));
// 		if(UIManager::_checkActive('/profile/new')){
// 			$paths[]=array(t("New ACL profile"), t("New ACL profile"), url_for('/profile/new'));
				
// 		}
		if(UIManager::_checkActive('/profile/list')){
			$paths[]=array(t("Active Profiles per Product InstanceProduct Instance"),t("Active Profiles per Product Instance"), url_for('/profile/list'));
		}
		if(UIManager::_checkActive('/profile/manage_profile_per_study')){
			$paths[]=array(t("Manage Users Profiles"),t("Manage Users Profiles"), url_for('/profile/manage_profile_per_study'));
		}
	}

	return $paths;
}

function profile_getPageTitle($page_title){
	if(UIManager::_checkActive('/profile')){
		$page_title=t("Active Profiles per Product Instance");
// 		if(UIManager::_checkActive('/profile/new')){
// 			$page_title=t("New ACL profile");

// 		}
		if(UIManager::_checkActive('/profile/list')){
			$page_title=t("Active Profiles per Product Instance");
		}
		if(UIManager::_checkActive('/profile/manage_profile_per_study')){
			$page_title=t("Manage Users Profiles");
		}
	}
	return $page_title;
}

function profile_page_new(){
	/*
	$d = Dispatcher::getInstance();
	$d->profile_new();
	return html($d->dsp_getPageContent());
	*/
// 	$output = "";
// 	$output .= '<form class="form-horizontal" role="form">
// 				<div class="form-group">
// 					<label class="col-sm-3 control-label no-padding-right" for="form-field-1"> Text Field </label>
		
// 					<div class="col-sm-9">
// 						<input type="text" id="form-field-1" placeholder="Username" class="col-xs-10 col-sm-5" />
// 					</div>
// 				</div>
										
// 				<div class="form-group">
// 					<label class="col-sm-3 control-label no-padding-right" for="form-field-2"> Password Field </label>

// 					<div class="col-sm-9">
// 						<input type="password" id="form-field-2" placeholder="Password" class="col-xs-10 col-sm-5" />
// 						<span class="help-inline col-xs-12 col-sm-7">
// 							<span class="middle">Inline help text</span>
// 						</span>
// 					</div>
// 				</div>
				
// 				<div class="form-group">
// 					<label class="col-sm-3 control-label no-padding-right" for="form-field-6">Tooltip and help button</label>

// 					<div class="col-sm-9">
// 						<input data-rel="tooltip" type="text" id="form-field-6" placeholder="Tooltip on hover" title="Hello Tooltip!" data-placement="bottom" />
// 						<span class="help-button" data-rel="popover" data-trigger="hover" data-placement="left" data-content="More details." title="Popover on hover">?</span>
// 					</div>
// 				</div>
	
// 			</form>';
// 	return html($output);
}
function profile_page_list(){
	$output = '';
	$m = UIManager::getInstance();
	/*
	 * 
	 * VECCHIA GESTIONE
	 * 
	$list = _list_profiles();
 	$labels = array(
 			'Description'=>array('NAME'=>'descrizione','TYPE'=>'TEXT'),
 			'Service type'=>array('NAME'=>'type','TYPE'=>'TEXT'),
 			'Policy'=>array('NAME'=>'policy','TYPE'=>'TEXT'),
 			'multiplicity'=>array('NAME'=>'d_molteplicita','TYPE'=>'TEXT')
 			
 	);
 	$actions = null;
 	$output .=$m->dsp_getTable($labels,$list,$actions);
	*/
	
	
	/*
	 * VAXMR-297 
	 */
	// echo "<pre>";
	// print_r(_study_list());
	// echo "</pre>";
	$grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/profiles/studies_profiles/jqGrid');
    $caption=t("Active Profiles per Product Instances");
	$labels = array(
			'Product instance'=>array('NAME'=>'STUDY_TITLE','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),
 			'Profile'=>array('NAME'=>'CODE','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),/*
 			'Policy'=>array('NAME'=>'POLICY','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),
 			'Scope'=>array('NAME'=>'SCOPE','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),*/
 			'Enabled'=>array('NAME'=>'ACTIVE','TYPE'=>'CHECK'),
 	);
	$output .=$m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels, true); //study_list_users($list);
	
	//inserisco legenda
	$output .="<div style='clear:both'></div>";
	$output .=$m->dsp_getLegend("Legend",_user_profile_pages_get_legend());
	return html($output);
}

function manage_profile_per_study_page($study_prefix,$profile_code){
	$output = '';
	$profile_info="";
	foreach(_profiles_list_per_study($study_prefix,false) as $key=>$profile){
		if($profile['ID']==$profile_code){
			$profile_info=$profile;
		}
	}
	//var_dump($profile_info);
	$m = UIManager::getInstance();
	if($profile_info['SCOPE']==0){
		$output.=manage_profile_per_study_page_global($study_prefix,$profile_code,$profile_info);
		$output .= '<button class="btn btn-info" onclick="showAddProfileStudyUsersGlobal(\''.$study_prefix.'\','.$profile_code.');"  style="width:200px; margin-top:5px;" type="submit" name="assoc_new_users" id="assoc_new_users"><i class="fa fa-upload bigger-110"></i>&nbsp;' . t("Associate new users") . '</button>';
	}
	else{
		$output.=manage_profile_per_study_page_no_global($study_prefix,$profile_code,$profile_info);
		$output .= '<button class="btn btn-info" onclick="showAddProfileStudyUsersNoGlobal(\''.$study_prefix.'\','.$profile_code.');"  style="width:200px; margin-top:5px;" type="submit" name="assoc_new_users" id="assoc_new_users"><i class="fa fa-upload bigger-110"></i>&nbsp;' . t("Associate new users") . '</button>';
	}
	//CREO TABELLA MODALE PER ASSOCIAZIONE NUOVI UTENTI AL PROFILO/STUDIO
	$titolo_modal=t("Associate new users to the product instance ")." ".$study_prefix." ".t("with the profile")." ".$profile_info['CODE'];//." <br/>(Policy: ".$profile_info['POLICY']." - Scope: ".$profile_info['SCOPE'].")";
	$output .="<div style='clear:both'></div>";
	$output .="<div id='not_associated_users_modal' class='modal fade'>
				  <div class='modal-dialog'>
				    <div class='modal-content'>
				      <div class='modal-header'>
				        <button type='button' class='close' data-dismiss='modal'><span aria-hidden='true'>&times;</span><span class='sr-only'>Close</span></button>
				        <h4 class='modal-title'>".$titolo_modal."</h4>
				      </div>
					  <div class='modal-body'>";
					  if($profile_info['SCOPE']!=0){ //solo nel caso in cui il profilo non sia global visualizzo select con siti associati allo studio
				 $output .="<div class='form-group'>
					  			<label for='SITE_ID' class='col-sm-3 control-label no-padding-right'>".t("SITES ENABLED")."</label>
					  				<select style='margin-left:15px' class='col-sx-3' name='SITE_ID' id='SITE_ID'>
					  					<option value=''>&nbsp;</option></select>
					  		</div>";
					  }
				 $output .="<div class='form-group' id='table_not_assoc'>
				 				<table id='user-list-grid-table_not_assoc'></table>
        		   				<div id='user-list-grid-pager_not_assoc'></div>
        		   			</div>
					  </div>
				   	  <!--div class='modal-footer'></div-->
				    </div><!-- /.modal-content -->
				  </div><!-- /.modal-dialog -->
			   </div><!-- /.modal -->";
	//inserisco legenda
	$output .="<div style='clear:both'></div>";
	$output .=$m->dsp_getLegend("Legend",_user_profile_pages_get_legend());
	return html($output);
}
function manage_profile_per_study_page_global($study_prefix,$profile_code,$profile_info){
	$output="";
	$m = UIManager::getInstance();
	//TABELLA JQGRID2 CON UTENTI GIA' ASSOCIATI AL PROFILO PER LO STUDIO ***CASO PROFILO GLOBALE (0)***
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/profiles/study/get_profile_study_users/'.$study_prefix.'/jqGrid/'.$profile_code);
    $caption=t("Users already associated for product instance")." ".$study_prefix." ".t("to the profile")." ".$profile_info['CODE'];//." (Policy: ".$profile_info['POLICY']." - Scope: ".$profile_info['SCOPE'].")" ;
    $labels = array('USERID' => array('NAME' => 'USERID', 'TYPE' => 'TEXT','SEARCH'=>1, 'SORT' => 1),
                    //'PROFILE' => array('NAME' => 'CODE', 'TYPE' => 'TEXT', 'SORT' => 1),
                    'ENABLED' => array('NAME' => 'ENABLED', 'TYPE' => 'CHECK', 'SORT' => 1));
    $actions=true;
    $output .= $m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels,$actions);
	
	return $output;
}

function manage_profile_per_study_page_no_global($study_prefix,$profile_code,$profile_info){
	$output="";
	$m =UIManager::getInstance();
	//TABELLA JQGRID2 CON UTENTI GIA' ASSOCIATI AL PROFILO PER LO STUDIO E CENTRO ***CASO PROFILO NON GLOBALE (1,2)***
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/profiles/study/get_profile_study_users_centers/'.$study_prefix.'/jqGrid/'.$profile_code);
    $caption=t("Users already associated per SITE for product instance")." ".$study_prefix." ".t("to the profile")." ".$profile_info['CODE'];//." (Policy: ".$profile_info['POLICY']." - Scope: ".$profile_info['SCOPE'].")" ;
  	$labels=array('USERID'=>array('NAME'=>'USERID','TYPE'=>'TEXT','SEARCH'=>1,'SORT'=>1),
				  'SITE'=>array('NAME'=>'SITE_DESCR','TYPE'=>'TEXT','SEARCH'=>1,'SORT'=>1),
				  'ACTIVE'=>array('NAME'=>'ACTIVE','TYPE'=>'CHECK','SORT'=>1,'WIDTH'=>'10'));
    $actions = true;
    $output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption, $labels, $actions);
	return $output;
}

function _list_profiles(){
	global $profili;
	global $products;
	$retval = array();
	/*
	if(!isset($profili['CRMS'])){
		$profili['CRMS']=array();
	}
	if(!isset($profili['DRUG_REGISTRY'])){
		$profili['DRUG_REGISTRY']=array();
	}
	if(!isset($profili['CLINICAL_TRIAL'])){
		$profili['CLINICAL_TRIAL']=array();
	}
    if(!isset($profili['LABORATORY_RANGE'])){
        $profili['LABORATORY_RANGE']=array();
    }
    if(!isset($profili['DRUPAL'])){
        $profili['DRUPAL']=array();
    }
    */
	//$retval = array_merge($profili['DRUG_REGISTRY'],$profili['CLINICAL_TRIAL'], $profili['CRMS'], $profili['LABORATORY_RANGE'], $profili['DRUPAL']);
	foreach ($products as $key=>$val){
		foreach ($profili[$key] as $key2=>$val2){
			$val2['type']=$val;
			$retval[$key2]=$val2;
		}
	}
	return $retval;
}


function _profiles_list_no_global_per_study($study,$jqGrid=false){
	$retval = array();
	$select="SELECT * FROM STUDIES_PROFILES WHERE ACTIVE=1";
	$rs = db_query($select);
	
	$profili=_list_profiles();
	while ($row = db_nextrow($rs)){
		$row['D_CODE']=$profili[$row['CODE']]['descrizione'];
		if($row['SCOPE']!=0){ //PRENDO SO
			$retval[$row['STUDY_PREFIX']][] = $row;
		}
	}
	$return="";
	if($study==""){
		$return=$retval;
	}
	else{
		$return=$retval[$study];
	}
	
	
	//echo $study;
	if(isAjax()){
			echo json_encode(array_merge(array("sstatus" => "ok"), $return));
			die();
	}
	else{
		_data_parse($return, sizeof($return), $jqGrid); //-->Qui gestisco l'output json opportuno, oppure non faccio nulla (e quindi ritorno il retval di questo metodo...
		return $return;
		
	}	
}

function _profiles_list_per_study($study,$jqGrid=false){
	$retval = array();
	$select="SELECT * FROM STUDIES_PROFILES WHERE ACTIVE=1";
	$rs = db_query($select);
	$profili=_list_profiles();
	while ($row = db_nextrow($rs)){
		$row['D_CODE']=$profili[$row['CODE']]['descrizione'];
		
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
		_data_parse($return, sizeof($return), $jqGrid); //-->Qui gestisco l'output json opportuno, oppure non faccio nulla (e quindi ritorno il retval di questo metodo...
		return $return;
	}
}

/*
 * VAXMR-297 
 */
function _studies_profiles($jqGrid=false,$study=false,$force_array=false){ 
	$retval = array();
	$bind=array();
	//print_r($study);
	global $profili;
	if($study){
		$bind['STUDY_PREFIX']=$study;
	}
	$actions=array();
	$actions[] = array('LABEL' => 'Manage Users Profiles', 'ICON' => 'list', 'LINK' => url_for('/profile/manage_profile_per_study/[STUDY_PREFIX]/[ID]'), 'COLOR' => '#FF8040'); //" onclick="show_users_profiles_assoc(\'[STUDY_PREFIX]\',\'[CODE]\');
    $actions[] = array('LABEL' => 'Toggle enable', 'ICON' => 'retweet', 'LINK' =>'#" onclick="toggle_study_profile(\'[STUDY_PREFIX]\',\'[ID]\',\'[ACTIVE_TOGGLE]\');', 'COLOR' => '#D32646');
	$select="SELECT  sp.ID AS ID, sp.STUDY_PREFIX as STUDY_PREFIX,sp.CODE as CODE, sp.POLICY as POLICY, sp.SCOPE as SCOPE,sp.ACTIVE AS ACTIVE, DECODE(sp.ACTIVE,1,0,0,1) AS  ACTIVE_TOGGLE, s.TITLE as STUDY_TITLE FROM STUDIES_PROFILES sp, STUDIES s WHERE sp.STUDY_PREFIX=s.PREFIX";
	if($study){
		$select.=" AND sp.STUDY_PREFIX=:STUDY_PREFIX";
		//print_r($study);
	}
	//$data = _data_load($select,$select_count,$bind,array("STUDY_PREFIX"=>"sp.STUDY_PREFIX","CODE"=>"sp.CODE"));
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		$ord_override=array("STUDY_PREFIX"=>"sp.STUDY_PREFIX");
		$retval= _data_retrieve($jqGrid,$select, $bind, $ord_override, array('ID','STUDY_PREFIX','CODE','POLICY'),array('ACTIVE'),$actions,array(),false);
	}
	die($retval);
	if(!$force_array && isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		return $retval;
	}
	
}



function study_profile_toggle_user($prefix, $username, $profileid,$verbose=true) { //VAXMR-297
	$row = _study_load_user($prefix, $username, $profileid);
	if ($row['ENABLED']) {
		$upRow['ABILITATO'] = "0";
		$enab = "DISABLED";
	} else {
		$upRow['ABILITATO'] = "1";
		$enab = "ENABLED";
	}
	$table = "UTENTI_GRUPPIU";
	$upRow['USERID'] = $row['USERID'];
	$upRow['ID_GRUPPOU'] = $row['PROFILE_ID'];
	$action = ACT_MODIFY;
	$keys = array('USERID', 'ID_GRUPPOU');
	//common_add_message(print_r($row,true),INFO);
	$retval=true;
	if (!db_form_updatedb($table, $upRow, $action, $keys,false)) {
		if($verbose){
			common_add_message("Error during privilege toggling", ERROR);
		}
			$retval= false;
	}
	/**VMAZZEO 15.12.2015: quando aggiorno se un utente è abilitato o meno ad uno studio, devo anche aggiornare USERS_PROFILES!*/ 
	$table = "USERS_PROFILES";
	$upRowUS['USERID'] = $row['USERID'];
	$upRowUS['PROFILE_ID'] = $row['PROFILE_ID'];
	$upRowUS['ACTIVE'] = $upRow['ABILITATO'];
	$action = ACT_MODIFY;
	$keys = array('USERID', 'PROFILE_ID');
	if (!db_form_updatedb($table, $upRowUS, $action, $keys, false)) {
		if($verbose){
			common_add_message("Error during privilege toggling", ERROR);
		}
		$retval = false;
	}
	if($retval){
		db_commit();
		if($verbose){
			common_add_message("Privilege $enab", INFO);
		}
	}
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		db_close();
		return $retval;
	}	
	
}

function study_profile_toggle_study_profile($prefix, $profileid, $active) { //VAXMR-297
	$list = _study_load_profiles($prefix);
	// echo "<pre>";
	// print_r($list);
	// echo "</pre>";
	$my_row=array();
	foreach ($list as $profile_code => $profile) {
		if($profile['ID']==$profileid){
			$my_row["ID-".$profile_code]=$profileid;
			if($active==1){
				$my_row["ACTIVE-".$profile_code]="on";
			}
		}
	}
	$retval=study_profiles_form_submit($list,$prefix,$my_row,false);//richiamo la vecchia funzione sotto study.module.php
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		db_close();
		return $retval;
	}
}

function study_profile_center_toggle_user($username,$prefix,$siteid,$profileid,$verbose=true){ //VAXMR.297
	//Toggle enable status
	$row = _user_load_privilege($username,$prefix,$siteid,$profileid,false,true);
	if ($row['ACTIVE']){
		$row['ACTIVE']="0";
		$enab = "DISABLED";
	}else{
		$row['ACTIVE']="1";
		$enab = "ENABLED";
	}
	$retval=true;
	$table = "USERS_SITES_STUDIES";
	$action = ACT_MODIFY;
	$keys = array('USERID','SITE_ID','STUDY_PREFIX','USER_PROFILE_ID');
	//common_add_message(print_r($row,true),INFO);
	if (db_form_updatedb($table, $row, $action, $keys)){
		if($verbose){
			common_add_message("Privilege $enab", INFO);
		}
	}else{
		if($verbose){
			common_add_message("Error during privilege toggling", ERROR);
		}
		$retval=false;
	}
	
	if($retval){
		//prima di modificare utenti_gruppiu controllo se sono rimasti altri profili con stesso id attivi per questo utente/sito per non disabilitare UTENTI_GRUPPIU 
		$rs = db_query_bind("SELECT COUNT(*) AS CONTO FROM USERS_SITES_STUDIES WHERE USERID=:USERID AND STUDY_PREFIX=:STUDY_PREFIX AND USER_PROFILE_ID=:USER_PROFILE_ID AND ACTIVE=1",$row);
		$_row = db_nextrow($rs);
		$do_not_update_utenti_gruppiu=$_row['CONTO'];
		//INSERISCO/MODIFICO IN UTENTI_GRUPPIU
		$table = "UTENTI_GRUPPIU";
		$action = ACT_MODIFY;
		$utenti_gruppiu_row=array();
		$utenti_gruppiu_row['USERID']=$row['USERID'];
		$utenti_gruppiu_row['ID_GRUPPOU']=$row['USER_PROFILE_ID'];
		$utenti_gruppiu_row['ABILITATO']=$row['ACTIVE'];
		$utenti_gruppiu_list=_user_load_gruppiu($row['USERID']);
		$utenti_gruppiu_row = common_booleanCheckBox($utenti_gruppiu_row, 'ABILITATO');
		//common_add_message(print_r($row,true), INFO);
		$keys = array('USERID','ID_GRUPPOU');
		if(!$do_not_update_utenti_gruppiu||$row['ACTIVE']==1){
			if (db_form_updatedb($table, $utenti_gruppiu_row, $action, $keys)){
				db_commit();	
				if($verbose){
					common_add_message("Privilege $enab", INFO);
				}
			}
			else{
				if($verbose){
					common_add_message("Error during privilege toggling", ERROR);
				}
				$retval=false;
			}
		}
	}
	
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		db_close();
		return $retval;
	}
}

function _study_profile_load_users($prefix, $jqGrid = false, $profile_code) {
	$retval = array();
	$bind = array();
	$bind['PROFILE_ID']=$profile_code;
	$fromwhere = " FROM USERS_PROFILES up,utenti_gruppiu ug, STUDIES_PROFILES sp WHERE
	ug.id_gruppou=profile_id
	and ug.userid=up.userid
	and
	PROFILE_ID = ID AND PROFILE_ID IN (:PROFILE_ID) and sp.active=1";
    $select = "SELECT up.*,sp.ID,sp.CODE,sp.STUDY_PREFIX, ug.abilitato as ENABLED ".$fromwhere;
    $select_count = "SELECT COUNT(*) AS CONTO ".$fromwhere;
	// echo "<pre>";
	// echo $select;
	// echo "</pre>";
    $actions = array();
    $actions[] = array('LABEL' => 'Toggle enable', 'ICON' => 'retweet', 'LINK' => '#" onclick="toggle_study_profile_user(\''.$prefix.'\',\'[USERID]\',\'[PROFILE_ID]\');', 'COLOR' => '#D32646');
    $ord_override=array("USERID"=>"up.USERID");
    $data = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('USERID'),array('ENABLED'),$actions,false);
    return $data;
}

function _study_profile_load_users_centers($prefix, $jqGrid = false, $profile_code){
	$retval = array();
    $bind = array();
    $bind['STUDY_PREFIX']=$prefix;
	$bind['PROFILE_CODE']=$profile_code;
    $fromwhere = "
								FROM
								  USERS_SITES_STUDIES uss
								,SITES site
								,STUDIES study
								,STUDIES_PROFILES study_profile
								WHERE
								  uss.SITE_ID       =site.ID
								AND uss.STUDY_PREFIX=study.PREFIX
								AND uss.USER_PROFILE_ID=study_profile.ID
								and uss.STUDY_PREFIX=study_profile.STUDY_PREFIX
								AND study.PREFIX=:STUDY_PREFIX
								AND study_profile.ID=:PROFILE_CODE";

    $select = "SELECT
								  uss.userid
								,site.DESCR  AS SITE_DESCR
								,site.ID  AS SITE_ID
								,study.DESCR AS STUDY_DESCR
								,study.PREFIX
								,study_profile.CODE
								,study_profile.ID AS PROFILE_ID
								,uss.ACTIVE
					". $fromwhere;
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		$actions = array();
    	$actions[] = array('LABEL'=>'Toggle enable','ICON'=>'retweet','LINK'=>'#" onclick="toggle_study_profile_center_user(\'[USERID]\',\'[PREFIX]\',\'[SITE_ID]\',\'[PROFILE_ID]\');','COLOR'=>'#D32646'); //lightblue
    	$ord_override=array("USERID"=>"USERID", "STUDY_PREFIX"=>"STUDY_PREFIX");//array('USERID','STUDY_PREFIX','SITE_ID',);
		$checkicons=array();
		$pkeys=array('userid','ID','PREFIX','PROFILE_ID');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,array('ACTIVE'),$actions,false);	
	}
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		return $retval;
	}

}

function _study_profile_load_users_not_associated($prefix, $jqGrid = false, $profile_code) {
	$retval = array();
	$bind = array();
	$bind['PROFILE_ID']=$profile_code;
	$fromwhere = " FROM USERS_PROFILES up,utenti_gruppiu ug, STUDIES_PROFILES sp WHERE
	ug.id_gruppou=profile_id
	and ug.userid=up.userid
	and
	PROFILE_ID = ID AND PROFILE_ID IN (:PROFILE_ID) and sp.active=1";
    $select = "SELECT USERID,0 AS ENABLED FROM UTENTI WHERE USERID NOT IN (SELECT up.USERID ".$fromwhere.")";
    $select_count = "SELECT COUNT(*) AS CONTO  FROM UTENTI WHERE USERID NOT IN (SELECT up.USERID".$fromwhere.")";
	//echo "<pre>";
    $actions = array();
    $actions[] = array('LABEL' => 'Associate user', 'ICON' => 'retweet', 'LINK' => '#" onclick="assoc_new_user_global(\''.$prefix.'\',\'[USERID]\',\''.$profile_code.'\');', 'COLOR' => '#D32646');
    $ord_override=array("USERID"=>"USERID");
	$checkicons=array("ENABLED");
	$pkeys=array('USERID');
	$data=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
    return $data;
}

function _study_profile_load_users_centers_not_associated($prefix,$jqGrid = false, $profile_id,$site_id=false){
	$retval = array();
    $bind = array();
    $bind['STUDY_PREFIX']=$prefix;
	$bind['PROFILE_CODE']=$profile_id;
	$profile_scope="";
	//print_r(_studies_profiles(false,$prefix,true));
	$studies_profiles=_studies_profiles(false,$prefix,true);
	foreach($studies_profiles as $key => $study_profile){
		if($study_profile['ID']==$profile_id){
			$profile_scope=$study_profile['SCOPE'];
		}
	}
    $fromwhere = "
								FROM
								  USERS_SITES_STUDIES uss
								,SITES site
								,STUDIES study
								,STUDIES_PROFILES study_profile
								WHERE
								  uss.SITE_ID       =site.ID
								AND uss.STUDY_PREFIX=study.PREFIX
								AND uss.USER_PROFILE_ID=study_profile.ID
								and uss.STUDY_PREFIX=study_profile.STUDY_PREFIX
								AND study.PREFIX=:STUDY_PREFIX
								AND study_profile.ID=:PROFILE_CODE";
	if($profile_scope!=1 && $site_id!=false){
		$bind['SITE_ID']=$site_id;
		$fromwhere.=" AND site.ID=:SITE_ID";
	}

    $select = "SELECT USERID,0 AS ENABLED FROM UTENTI WHERE USERID NOT IN (
    							SELECT 
								  uss.userid
								
					". $fromwhere.")";
	$actions = array();
    $actions[] = array('LABEL'=>'Associate user','ICON'=>'retweet','LINK'=>'#" onclick="assoc_new_user_noglobal(\''.$prefix.'\',\'[USERID]\',\''.$profile_id.'\');','COLOR'=>'#D32646'); //lightblue
    $ord_override=array("USERID"=>"USERID");
	$checkicons=array("ENABLED");
	$pkeys=array('USERID');
	$data=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
    return $data;
}
function _study_profile_assoc_new_user_global($prefix, $username, $profileid){
 	$retval=false;
 	$my_row['USERID']=$username;
	// $my_row['STUDY_PREFIX']=$prefix;
	$my_row['PROFILE_ID']=$profileid;
	$my_row['ACTIVE']='ACTIVE';
	// echo "<pre>";
	// print_r($my_row);
	// echo "</pre>";
	$retval=study_users_form_submit($prefix,null,$my_row,false);//richiamo la vecchia funzione sotto study.module.php
	if($retval){
		header("location: " . $_SERVER['HTTP_REFERER']); //VAXMR-297
		db_close();die();		
	}
	db_close();
 	return $retval; 
	
 }

function _study_profile_assoc_new_user_noglobal($prefix, $username, $profileid,$centerid){
 	$retval=false;
 	$my_row['USERID']=$username;
	$my_row['STUDY_PREFIX']=$prefix;
	$my_row['SITE_ID']=$centerid;
	$my_row['USER_PROFILE_ID']=$profileid;
	$my_row['ACTIVE']='ACTIVE';
	 // echo "<pre>";
	 // print_r($my_row);
	 // echo "</pre>";
	$retval=user_privileges_form_submit($username,null,$my_row,false);//richiamo la vecchia funzione sotto user.module.php
	if($retval){
		header("location: " . $_SERVER['HTTP_REFERER']); //VAXMR-297
		db_close();die();		
	}
	db_close();
 	return $retval; 
	
 }

function _study_profile_pages_get_legend(){
	$legend_items=array();
	$legend_item['icon']="";
	$legend_item['testo']="Policy RO: Read Only profile";
	$legend_items[]=$legend_item;
	$legend_item['icon']="";
	$legend_item['testo']="Policy DE: Data Entry profile";
	$legend_items[]=$legend_item;
	$legend_item['icon']="";
	$legend_item['testo']="Policy DM: Data Manager profile";
	$legend_items[]=$legend_item;
	$legend_item['icon']="";
	$legend_item['testo']="Scope 0: Global scope";
	$legend_items[]=$legend_item;
	$legend_item['icon']="";
	$legend_item['testo']="Scope 1: Sigle site scope";
	$legend_items[]=$legend_item;
	$legend_item['icon']="";
	$legend_item['testo']="Scope 2: Multi site scope";
	$legend_items[]=$legend_item;
	return $legend_items;
}
?>