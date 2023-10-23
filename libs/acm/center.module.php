<?php

function center_init(){
	dispatch('/center', 'center_page_new');
	dispatch('/center/new', 'center_page_new');
	dispatch('/center/list', 'center_page_list');
	dispatch_post('/center/new', 'center_page_new');
	dispatch('/center/edit/:center_id', 'center_page_edit');
	dispatch_post('/center/edit/:center_id', 'center_page_edit');
	dispatch('/center/users/:center_id', 'center_page_users');
	dispatch_post('/center/users/:center_id', 'center_page_users');
	dispatch('/center/centers_list_per_study/:study','_centers_list_per_study');
	dispatch('/center/centers_list_per_study_and_user/:study/:user','_centers_list_per_study_and_user');
	dispatch('/center/users/delete/:center_id/:user_id','_centers_user_delete');//STSANSVIL-1260

	dispatch('center/get_list_center/:jqGrid','_center_list_centers');
	dispatch('center/get_list_user/:center_id/:jqGrid','_center_load_users');
	dispatch('/center/study/get_list_users_not_associated/:centerid/:jqGrid/', '_center_list_users_not_associated'); //VAXMR-299
	dispatch('/center/study/center_assoc_new_user/:centerid/:username/','_center_assoc_new_user');//VAXMR-299//STSANSVIL-1260
	dispatch('countries/get_list_countries/:jqGrid','_get_countries');
	dispatch('center/load_center/:center_id/:jqGrid','_center_load_center');
	dispatch('/center/centers_list_per_study/:study/:jqGrid','_centers_list_per_study');
	dispatch('/center/centers_list_per_study_and_user/:study/:user/:jqGrid','_centers_list_per_study_and_user');
	dispatch('center/center_get_users_from_ce/:center_id','_center_get_users_from_ce');//STSANSVIL-1260
}

function center_sidebar($sideBar){
	$itm2=new SideBarItem(new Link(t("Sites"), "building-o", "#"));
	$itm2->addItem(new SideBarItem(new Link(t("New site"), "plus", url_for('/center/new')), null, UIManager::_checkActive('/center/new')));
	$itm2->addItem(new SideBarItem(new Link(t("List existing sites"), "list", url_for('/center/list')), null, UIManager::_checkActive('/center/list')));
	$sideBar->addItem($itm2);

	return $sideBar;
}

function center_breadcrumb($paths)
{
	if(UIManager::_checkActive('/center')){
		$paths[]=array(t("Sites"), t("Sites"), url_for('/center/list'));
		if(UIManager::_checkActive('/center/new')){
			$paths[]=array(t("New site"), t("New site"), url_for('/center/new'));

		}
		if(UIManager::_checkActive('/center/edit')){
			$paths[]=array(t("Edit center"), t("Edit center"), url_for('/center/edit'));
		}
		if(UIManager::_checkActive('/center/users')){
			$paths[]=array(t("User-site associations"), t("User-site associations"), url_for('/center/edit'));
		}

		if(UIManager::_checkActive('/center/list')){
			$paths[]=array(t("List existing sites"), t("List existing sites"), url_for('/center/list'));
		}
	}

	return $paths;
}

function center_getPageTitle($page_title){
	if(UIManager::_checkActive('/center')){
		$page_title=t("Center");
		if(UIManager::_checkActive('/center/new')){
			$page_title=t("New site");

		}
		if(UIManager::_checkActive('/center/edit')){
			$page_title=t("Edit center");

		}
		if(UIManager::_checkActive('/center/users')){
			$page_title=t("User-site associations");
		}
		if(UIManager::_checkActive('/center/list')){
			$page_title=t("List existing sites");
		}
	}
	return $page_title;
}

/*function center_page_new(){
	$m = UIManager::getInstance();
	$output = "";
	$output .= '<form class="form-horizontal" role="form">
					<div class="form-group">';
	//$output .= ''.$m->dsp_getLabelField('Site ID','siteid-field').'';
	$output .= ''.$m->dsp_getTextField('Code', 'code-field', '', '', false, false).'';
	$output .= ''.$m->dsp_getTextField('Site ID', 'siteid-field', 'insert SITEID code', '', false, false).'';
	$output .= ''.$m->dsp_getTextField('Name', 'name-field', 'insert center name', 'name of the center', false, false).'';
	$output .= ''.$m->dsp_getTextField('P.I.', 'pi-field', 'insert P.I. name and surname', '', false, false).'';
	$output .= ''.$m->dsp_getTextField('Address', 'address-field', 'insert center name', '', false, false).'';
	$output .= ''.$m->dsp_getTextField('Phone', 'phone-field', 'insert center name', '', false, false).'';
	$output .= ''.$m->dsp_getTextField('Fax', 'fax-field', 'insert center name', '', false, false).'';


	$countries=array("1"=>"Italy","2"=>"Germany");
	$output .= ''.$m->dsp_getSelectField('Country', 'country-field', 'choose a country', '', false, false,$countries).'';
	$output .= ''.$m->dsp_getCheckbox('STATUS', 'status-field', '', 'Enabled', false, null).'';
	$output .= '
					</div>';
	$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
	$output .= '
				</form>';
	return html($output);
}
*/

function center_form($row){
	$output = "";
	$m = UIManager::getInstance();
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';
	$output .= ''.$m->dsp_getHiddenField('ID', false, $row).'';
	$output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'ID', $row['ID'], false).'';
	$output .= ''.$m->dsp_getTextField('Code', 'CODE', '', '', false, false,$row,true).'';
	$output .= ''.$m->dsp_getTextField('Name', 'DESCR', '', '', false, false,$row,true).'';
	$output .= ''.$m->dsp_getTextField('P.I.', 'PI', '', '', false, false,$row,true).'';
	$output .= ''.$m->dsp_getTextField('Address', 'ADDRESS', '', '', false, false,$row).'';
	$output .= ''.$m->dsp_getTextField('Phone', 'PHONE', '', '', false, false,$row).'';
	$output .= ''.$m->dsp_getTextField('Fax', 'FAX', '', '', false, false,$row).'';
	$countries=_get_countries();//array("1"=>"Italy","2"=>"Germany");
	$output .= ''.$m->dsp_getSelectField('Country', 'COUNTRY', 'choose a country', '', false, $row['COUNTRY'],$countries).'';
	$output .= ''.$m->dsp_getCheckbox('ACTIVE', 'ACTIVE', '', 'Enabled', false, false, $row).'';
	if(!$row['ID'] || ($row['ID'] && $row['ID']>10)){
		$centri=_center_list_centers();
		$ce_opt=array();
		foreach($centri as $id => $centro){//PRENDO SOLO I CE (ID<10)
			if($centro['ID']<10){
				$ce_opt[$centro['ID']]=$centro['DESCR'];
			}
		}
		$output .= ''.$m->dsp_getSelectField('Comitato Etico di Riferimento', 'CE_ID', '', '', false, $row['CE_ID'],$ce_opt,null,true).'';

	}

	$output .= '<div id="messages" class="panel panel-info"><div class="panel-heading"><h3 class="panel-title center">INTEGRAZIONE COL SISTEMA AZIENDALE DI PROTOCOLLO</h3></div><div class="panel-body">';
	$protocolli=array();
	$protocolli["Archiflow"]="Archiflow";
	$protocolli["Babel"]="Babel";
	$protocolli["Docsuite"]="Docsuite";
	$protocolli["Iride"]="Iride";
	$output .= ''.$m->dsp_getSelectField('Sistema', 'INTEGRAZIONE_PROTOCOLLO', '', '', false, $row['INTEGRAZIONE_PROTOCOLLO'],$protocolli,null,false).'';
	$output .= ''.$m->dsp_getTextField('Codice Azienda', 'INTEGRAZIONE_COD_AZ', '', '', false, false,$row,false).'';
	$output .= ''.$m->dsp_getTextField('Codice Registro', 'INTEGRAZIONE_COD_REGISTRO', '', '', false, false,$row,false).'';
	$style='';
	if($row['INTEGRAZIONE_PROTOCOLLO']!='Babel'){
		$style='display:none';
	}
	$output .= '<div id="Babel" style="'.$style.'">';
	$output .= ''.$m->dsp_getTextField('Struttura', 'INTEGRAZIONE_STRUTTURA', '', '', false, false,$row,false).'';
	$output .= ''.$m->dsp_getTextArea('Assegnatari', 'INTEGRAZIONE_ASSEGNATARI', '', '', false, false,$row,1000,false).'';
	$output .= ''.$m->dsp_getTextField('Classificazione', 'INTEGRAZIONE_CLASSIFICAZIONE', '', '', false, false,$row,false).'';
	$output .= ''.$m->dsp_getTextField('Tipo fascicolo', 'INTEGRAZIONE_TIPOFASCICOLO', '', '', false, false,$row,false).'';
	$output .= ''.$m->dsp_getTextField('Utente responsabile', 'INTEGRAZIONE_RESPONSABILE', '', '', false, false,$row,false).'';
	$output .= ''.$m->dsp_getTextArea('Altri responsabili', 'INTEGRAZIONE_VICARI', '', '', false, false,$row,1000,false).'';
	$output .= ''.$m->dsp_getTextArea('Permessi', 'INTEGRAZIONE_PERMESSI', '', '', false, false,$row,1000,false).'';

	$output .= '</div></div></div>';
	$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
	$output .= '</form>';
	$output .='<script>
				$(document).ready(function(){
				    $("#INTEGRAZIONE_PROTOCOLLO").change(function(){
				        if($(this).val()=="Babel"){
				            $("#Babel").show();
				        }
				        else{
				            $("input[name=INTEGRAZIONE_STRUTTURA]").val("");
				            $("input[name=INTEGRAZIONE_ASSEGNATARI]").val("");
				            $("input[name=INTEGRAZIONE_CLASSIFICAZIONE]").val("");
				            $("input[name=INTEGRAZIONE_TIPOFASCICOLO]").val("");
				            $("input[name=INTEGRAZIONE_RESPONSABILE]").val("");
				            $("input[name=INTEGRAZIONE_VICARI]").val("");
				            $("input[name=INTEGRAZIONE_PERMESSI]").val("");
				            $("#Babel").hide();
				        }
				    });
				});
				</script>';
	return $output;
}
function center_form_validate(){
	$retval = true;
	$row = $_POST;
	if (!$row['CODE']){
		common_add_message(t("Please specify the field ")." '".t("Code")."'",WARNING);
		$retval = false;
	}
	if (!$row['DESCR']){
		common_add_message(t("Please specify the field ")." '".t("Name")."'",WARNING);
		$retval = false;
	}
	if (!$row['PI']){
		common_add_message(t("Please specify the field ")." '".t("P.I.")."'",WARNING);
		$retval = false;
	}
	if(!$row['ID'] || ($row['ID'] && $row['ID']>10)){
		if (!$row['CE_ID']){
			common_add_message(t("Please specify the field ")." '".t("Comitato Etico di Riferimento")."'",WARNING);
			$retval = false;
		}
	}
	/* SDSANIT-76816 TOLGO OBBLIGATORIETA'
		if (!$row['INTEGRAZIONE_PROTOCOLLO']){
            common_add_message(t("Please specify the field ")." '".t("Sistema di integrazione protocollo")."'",WARNING);
            $retval = false;
        }
        if (!$row['INTEGRAZIONE_COD_AZ']){
            common_add_message(t("Please specify the field ")." '".t("Codice Azienda")."'",WARNING);
            $retval = false;
        }
        if (!$row['INTEGRAZIONE_COD_REGISTRO']){
            common_add_message(t("Please specify the field ")." '".t("Codice Registro")."'",WARNING);
            $retval = false;
        }

        if ($row['INTEGRAZIONE_PROTOCOLLO']=="Babel"){
            if(!$row['INTEGRAZIONE_STRUTTURA']) {
                common_add_message(t("Please specify the field ") . " '" . t("Struttura") . "'", WARNING);
                $retval = false;
            }
            if(!$row['INTEGRAZIONE_ASSEGNATARI']) {
                common_add_message(t("Please specify the field ") . " '" . t("Assegnatari") . "'", WARNING);
                $retval = false;
            }
            if(!$row['INTEGRAZIONE_CLASSIFICAZIONE']) {
                common_add_message(t("Please specify the field ") . " '" . t("Classificazione") . "'", WARNING);
                $retval = false;
            }
            if(!$row['INTEGRAZIONE_TIPOFASCICOLO']) {
                common_add_message(t("Please specify the field ") . " '" . t("Tipo fascicolo") . "'", WARNING);
                $retval = false;
            }
            if(!$row['INTEGRAZIONE_RESPONSABILE']) {
                common_add_message(t("Please specify the field ") . " '" . t("Utente responsabile") . "'", WARNING);
                $retval = false;
            }
            if(!$row['INTEGRAZIONE_VICARI']) {
                common_add_message(t("Please specify the field ") . " '" . t("Altri responsabili") . "'", WARNING);
                $retval = false;
            }
            if(!$row['INTEGRAZIONE_PERMESSI']) {
                common_add_message(t("Please specify the field ") . " '" . t("Permessi") . "'", WARNING);
                $retval = false;
            }
        }
	*/
	return $retval;
}
function center_form_submit($action){
	$retval = false;
	$row = $_POST;
	unset($row['submit-button']);
	unset($row['reset-button']);

	$row = common_booleanCheckBox($row, 'ACTIVE');

	$row['DESCR'] = trim($row['DESCR']);
	$row['PI'] = trim($row['PI']);
	$countries=_get_countries();
	$row['D_COUNTRY']=$countries[$row['COUNTRY']];
	$table = "SITES";

	if ($action == ACT_INSERT){
		$row['ID'] = db_getnextsequencevalue($table);
		$_POST['ID'] = $row['ID'];

	}

	if (db_form_updatedb($table, $row, $action, 'ID')){
		common_add_message(t("Action executed!"), INFO);
		$retval = true;
	}
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		return $retval;
	}

}

function center_page_new(){
	$output = "";
	/*
     $d = Dispatcher::getInstance();
    $d->center_new();
    return html($d->dsp_getPageContent());
    */
	//$m = UIManager::getInstance();
	$row = array();
	$row['ID']="";
	$row['COUNTRY']="";
	if ($_POST){
		if (center_form_validate(ACT_INSERT)){
			if (center_form_submit(ACT_INSERT)){
				header("location: ".url_for('/center/list'));
				die();
			}else{
				$output .= t("An error occurred during center creation.");
			}
		}
		$row = $_POST;
	}
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">
				';
	$output .= center_form($row);
	$output .= '
			</form>';
	return html($output);
}

function center_page_edit($center_id){
	$output = "";
	$row =_center_load_center($center_id);
	if ($_POST){
		if (center_form_validate(ACT_MODIFY)){
			if (center_form_submit(ACT_MODIFY)){
				header("location: ".url_for('/center/list'));
				die();
			}else{
				$output .= t("An error occurred during center update.");
			}
		}
		$row = $_POST;
	}
	$output .= center_form($row);
	return html($output);
}


function center_page_list(){
	$output = '';
	$m = UIManager::getInstance();
	//$list = _center_list_centers();
	$grid_selector = "user-list-grid-table";
	$pager_selector = "user-list-grid-pager";
	$url=url_for('/center/get_list_center/jqGrid');
	$caption=t("List existing sites");
	$labels=array('CENTER ID'=>array('NAME'=>'ID','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
		'CODE'=>array('NAME'=>'CODE','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
		'NAME'=>array('NAME'=>'DESCR','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
		//'P.I.'=>array('NAME'=>'PI','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
		'ACTIVE'=>array('NAME'=>'ACTIVE','TYPE'=>'CHECK','SORT' => 1),
		'COUNTRY'=>array('NAME'=>'D_COUNTRY','TYPE'=>'TEXT','SORT' => 1));
	$actions = true;
	$output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption,$labels,$actions);
	//$output .=$m->dsp_getTable($columns,$list);
	return html($output);
}

function _center_list_centers($jqGrid = false, $forceArray = false, $idKey=false){
	//$retval = array();
	//Actions
	$actions = array();
	$actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/center/edit/[ID]'));
	$actions[] = array('LABEL'=>'User-site associations','ICON'=>'users','LINK'=>url_for('/center/users/[ID]'),'COLOR'=>'darkblue');
	//$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>url_for('/center/delete/[ID]'),'COLOR'=>'#FA3A3A');//VAXMR-154
	//Queries
	$select="SELECT * FROM SITES";
	//INIZIO GESTIONE FILTRO PER AZIENDA STSANPRJS-570
	$select_count="SELECT COUNT(*) as CONTO FROM USERS_SITES WHERE USERID = :USERID ";
	$bind = array();
	$bind['USERID']=$_SERVER['REMOTE_USERID'];
	$rs_count = db_query_bind($select_count,$bind);
	if ($row = db_nextrow($rs_count)){
		//var_dump($row);
		if ($row['CONTO'] && $row['CONTO']!="0"){
			$select="SELECT s.* from USERS_SITES us, SITES s WHERE us.SITE_ID=s.ID and us.USERID=:USERID";
		}
	}
	//$select="SELECT au.*,u.ABILITATO AS STATUS FROM ANA_UTENTI_1 au, UTENTI u WHERE au.USERID=u.USERID";//VECCHIA QUERY SENZA FILTRO
	if(!$jqGrid){ //VAXMR-297
		$select.=" ORDER BY DESCR";
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			if ($idKey){
				$retval[$row['ID']] = $row;
			}else {
				$retval[] = $row;
			}
		}
	}
	else{
		//$select_count="SELECT COUNT(*) AS CONTO FROM SITES";
		//$bind=array();
		$ord_override=array();
		//$data = _data_load($select,$select_count,$bind,$ord_override);
		$retval = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('ID'),array('ACTIVE'),$actions,false);
	}
	if(isAjax() && !$forceArray){
		header('Content-Type: application/json');
		echo json_encode(array_merge(array("sstatus" => "ok"), $retval));
		die();
	}
	else{
		return $retval;
	}
}
function _get_countries($jqGrid=false){
	$retval = array();
	if(!$jqGrid){
		$rs = db_query("SELECT ISO,COUNTRY FROM CMM_ISO_COUNTRY_LIST");
		while ($row = db_nextrow($rs)){
			$retval[$row['ISO']] = $row['COUNTRY'];
		}
	}
	else{
		$actions = array();
		$select="SELECT ISO,COUNTRY FROM CMM_ISO_COUNTRY_LIST";
		$bind=array();
		$ord_override=array();
		$checkicons=array();
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,array('ISO'),$checkicons,$actions,false);
	}
	return $retval;
}

function _center_load_center($key, $jqGrid=false){
	$retval = array();
	$select="SELECT * FROM SITES WHERE ID = :KEY";
	$bind['KEY'] = $key;
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		if ($row = db_nextrow($rs)){
			$retval = $row;
		}
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('ID');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	return $retval;
}
/*
 * mai usata - da eliminare? anche perchè esiste in study_module una versione migliore di questa _study_list
 */
function _center_get_studies($jqGrid=false){
	$retval = array();
	$select="SELECT PREFIX,DESCR FROM STUDIES WHERE ACTIVE=1";
	if(!$jqGrid){
		$rs = db_query($select);
		while ($row = db_nextrow($rs)){
			$retval[$row['PREFIX']] = $row['DESCR']." (".$row['PREFIX'].")";
		}
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('PREFIX');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	return $retval;
}

function _centers_list_per_study($study, $jqGrid=false){
	$retval = array();
	$select="SELECT ss.*,s.DESCR FROM SITES_STUDIES ss,SITES s WHERE ss.SITE_ID=s.ID and ss.STUDY_PREFIX=:STUDY_PREFIX ORDER BY s.DESCR";
	$bind = array();
	$bind['STUDY_PREFIX']=$study;
	if(!$jqGrid){
		$rs = db_query_bind($select, $bind);
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
	}
	else{
		$actions = array();
		$ord_override=array("SITE_ID"=>"SITE_ID");
		$checkicons=array();
		$pkeys=array('STUDY_PREFIX','SITE_ID');
		$return=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//echo $study;
	//var_dump($return);
	if(isAjax()){
		header('Content-Type: application/json');
		echo json_encode(array_merge(array("sstatus" => "ok"), $return));
		die();
	}
	else{
		return $return;
	}
}


function _centers_list_per_study_and_user($study, $user, $jqGrid=false){
	$retval = array();
	$select="SELECT ss.*,s.DESCR FROM SITES_STUDIES ss,SITES s, USERS_SITES us WHERE ss.SITE_ID=s.ID and ss.STUDY_PREFIX=:STUDY_PREFIX and us.SITE_ID=s.ID and us.USERID=:USERID";
	$bind = array();
	$bind['STUDY_PREFIX']=$study;
	$bind['USERID']=$user;
	if(!$jqGrid){
		$rs = db_query_bind($select, $bind);
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
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('STUDY_PREFIX','SITE_ID');
		$return=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//echo $study;
	//var_dump($return);
	if(isAjax()){
		header('Content-Type: application/json');
		if ($return!=null)
			echo json_encode(array_merge(array("sstatus" => "ok"), $return));
		else
			echo json_encode(array("sstatus"=>"no_center", "detail"=>"Nessun centro associabile"));
		die();
	}
	else{
		return $return;
	}
}

//GESTIONE UTENTI
function center_page_users($center_id){
	$m = UIManager::getInstance();
	$output = "";
	$center_info=_center_load_center($center_id);
	//print_r($center_info);
	$output .= "<h2>Current site: ".$center_info['DESCR']."</h2>";
	//$list =_center_load_users($center_id, false);
	$grid_selector = "user-list-grid-table";
	$pager_selector = "user-list-grid-pager";
	$url=url_for('/center/get_list_user/'.$center_id.'/jqGrid');
	$caption=t("User-site associations");
	$labels=array('USERID'=>array('NAME'=>'USERID','TYPE'=>'TEXT','SEARCH'=>1, 'SORT'=>1),
		'Name'=>array('NAME'=>'NOME','TYPE'=>'TEXT','SEARCH'=>1, 'SORT'=>1),
		'Surname'=>array('NAME'=>'COGNOME','TYPE'=>'TEXT','SEARCH'=>1, 'SORT'=>1));
	$actions = true;

	$output .=$m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels,$actions); //study_list_users($list);*/

	$output .= center_users_form($row, $center_id,$center_info);
	$output .= '<script>
				function deleteAssocUserSite(center_id,user_id){
				    bootbox.confirm("Do you confirm to delete the user "+user_id+" from current site?", function(result){ 
						if(result){
						    location.href="/acm/?/center/users/delete/"+center_id+"/"+user_id;
						}
					});
				}
				</script>';
	return html($output);
}

function _center_load_users($center_id, $jqGrid=false){
	//$retval = array();
	$actions = array();
	//TODO: confirm_alert not defined!
	$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>'javascript:deleteAssocUserSite('.$center_id.',\'[USERID]\')','COLOR'=>'#FA3A3A'); //VAXMR-154
	//Queries
	$bind = array();
	$bind['KEY']=$center_id;
	$select="SELECT  us.USERID AS USERID, us.SITE_ID AS SITE_ID, s.NOME,s.COGNOME FROM USERS_SITES us,ANA_UTENTI_1 s WHERE us.USERID=s.USERID AND us.SITE_ID=:KEY ";
	$ord_override=array();
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$data[] = $row;
		}
	}
	else{
		$ord_override=array("USERID"=>"USERID");
		$checkicons=array();
		$pkeys=array('USERID');

		$data=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//$data = _data_load($select,$select_count,$bind,$ord_override);
	//$data = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('USERID'),array(),$actions,false);
	return $data;
}

function _center_list_users_not_associated($center_id, $jqGrid=false){ //VAXMR-299
	//$retval = array();
	$actions = array();
	//TODO: confirm_alert not defined!
	//$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>'javascript:confirm_alert(\'Do you confirm the deletion of the user?\',\'USER DELETION\',\''.url_for('/center/users/delete/'.$center_id.'/[USERID]').'\')','COLOR'=>'#FA3A3A'); //VAXMR-154
	//Queries
	$bind = array();
	$bind['KEY']=$center_id;
	$select="SELECT USERID, 0 AS ENABLED FROM ANA_UTENTI_1 WHERE USERID NOT IN (SELECT us.USERID FROM USERS_SITES us,ANA_UTENTI_1 s WHERE us.USERID=s.USERID AND us.SITE_ID=:KEY )";
	$ord_override=array();
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$data[] = $row;
		}
	}
	else{
		$actions = array();
		$actions[] = array('LABEL' => 'Associate user', 'ICON' => 'retweet', 'LINK' => '#" onclick="center_assoc_new_user(\''.$center_id.'\',\'[USERID]\');', 'COLOR' => '#D32646');
		$ord_override=array("USERID"=>"USERID");
		$checkicons=array('ENABLED');
		$pkeys=array('USERID');

		$data=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//$data = _data_load($select,$select_count,$bind,$ord_override);
	//$data = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('USERID'),array(),$actions,false);
	return $data;
}

function _center_assoc_new_user($centerid, $username){
	$retval=false;
	$my_row['USERID']=$username;
	// $my_row['STUDY_PREFIX']=$prefix;
	$my_row['SITE_ID']=$centerid;

	/*STSANSVIL-1260
    Gli user (e solo quelli) segnati con
        ruolo Segreteria CE (modulo SIRER), SEGRETERIA	CRMS
        Componente CE (modulo CE), CMP CE
        Regione (modulo CE ?)  e REGIONE CRMS
        Segreteria CE (modulo CE) SGR CE
    inseriti nel site di Area Vasta vengano copiati all’interno di tutti i “site” che fanno riferimento a quella area vasta.
    */
	if($centerid<10){//PRENDO SOLO I CE (ID<10)
		$bind=array();
		$bind['USERID']=$username;
		//PRENDO I PROFILI DELL'UTENTE
		$select="select * from ACM_USERS_ASSOC where userid=:USERID";
		$rsp = db_query_bind($select,$bind);
		_centers_user_delete($centerid,$username,true);//IMPORTANTE: richiamo sempre il delete per evitare problemi con le chiavi primarie
		while ($profile = db_nextrow($rsp)){

			//echo "<pre>";
			if(
				($profile["STUDY_TYPE"]=="CRMS" && $profile["PROFILE_CODE"]=="SEGRETERIA") ||
				($profile["STUDY_TYPE"]=="CRMS" && $profile["PROFILE_CODE"]=="REGIONE") ||
				($profile["STUDY_TYPE"]=="CE" && $profile["PROFILE_CODE"]=="SGR") ||
				($profile["STUDY_TYPE"]=="CE" && $profile["PROFILE_CODE"]=="CMP"))
			{
				//print_r($profile);
				$bind=array();
				$bind['CENTERID']=$centerid;
				//PRENDO I CENTRI AFFERENTI A QUESTO CE
				$select="select * from SITES where CE_ID=:CENTERID";
				$rsc = db_query_bind($select,$bind);

				while ($center = db_nextrow($rsc)){
					//print_r($center);
					$my_row['SITE_ID']=$center['ID'];
					//ASSOCIO :$username A CIASCUN CENTRO AFFERENTE IL CE :$centerid
					$retval=center_users_form_submit($center['ID'], null, $my_row, false,true);//richiamo la vecchia funzione sotto study.module.php

				}
			}
		}
		//echo "</pre>";
		//die();
	}
	$my_row['SITE_ID']=$centerid;
	$retval = center_users_form_submit($centerid, null, $my_row, false);//richiamo la vecchia funzione sotto study.module.php



	if($retval){
		header("location: " . $_SERVER['HTTP_REFERER']); //VAXMR-297
		db_close();die();
	}
	db_close();die();
	return $retval;

}

function center_users_form($row,$center_id,$center_info){ //VAXMR-299
	$m = UIManager::getInstance();
	$output = '<button class="btn btn-info" onclick="showAddStudyUsersAssociation(\''.$center_id.'\');"  style="width:260px; margin-top:5px;" type="submit" name="assoc_new_study_users" id="assoc_new_study_users"><i class="fa fa-user-plus bigger-110"></i>&nbsp;' . t("Create new user-site association") . '</button>';
	if($center_id>=10) {
		$output .= '&nbsp;<button class="btn btn-info" onclick="ereditaUtentiDaCE(\'' . $center_id . '\');"  style="width:260px; margin-top:5px;" type="submit" name="assoc_new_study_users" id="assoc_new_study_users"><i class="fa fa-users bigger-110"></i>&nbsp;' . t("Scarica utenti da CE") . '</button>';
	}
	$titolo_modal=t("Create new user-site association for site: ")." <b>".$center_info['DESCR']."</b>";
	$output .="<div style='clear:both'></div>";
	$output .="<div id='not_associated_users_modal' class='modal fade'>
				  <div class='modal-dialog'>
				    <div class='modal-content'>
				      <div class='modal-header'>
				        <button type='button' class='close' data-dismiss='modal'><span aria-hidden='true'>&times;</span><span class='sr-only'>Close</span></button>
				        <h4 class='modal-title'>".$titolo_modal."</h4>
				      </div>
					  <div class='modal-body'>
					  		<table id='user-list-grid-table_not_assoc'></table>
        		   			<div id='user-list-grid-pager_not_assoc'></div>
					  </div>
				   	  <!--div class='modal-footer'></div-->
				    </div><!-- /.modal-content -->
				  </div><!-- /.modal-dialog -->
			   </div><!-- /.modal -->";
	return $output;
}
function center_users_form_validate(){
	$retval = true;
	$row = $_POST;
	if (!$row['USERID']){
		common_add_message(t("Please specify the field ")."'".t("USER")."'",WARNING);
		$retval = false;
	}
	return $retval;
}
function center_users_form_submit($center_id, $list,$row=false,$verbose=true,$forceArray = false){ //VAXMR-299
	$retval = false;
	if(!$row){
		$row = $_POST;
	}

	unset($row['submit-button']);
	unset($row['reset-button']);

	$table = "USERS_SITES";
	$action = ACT_INSERT;
	foreach ($list as $up){
		if ($up['SITE_ID']==$row['SITE_ID'] && $up['USERID']==$row['USERID']){
			$action = ACT_MODIFY;
			break;
		}
	}
	//$row = common_booleanCheckBox($row, 'ACTIVE');
	//common_add_message(print_r($row,true), INFO);
	$keys = array('SITE_ID','USERID');
	if (db_form_updatedb($table, $row, $action, $keys)){
		if ($action == ACT_INSERT){
			if($verbose){
				common_add_message(t("New user inserted correctly."), INFO);
			}
		}else{
			if($verbose){
				common_add_message(t("Existing user correctly modified."), INFO);
			}
		}
		$retval = true;
	}

	if(isAjax() && !$forceArray){
		//print_r(isAjax()." ".$forceArray);
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		//echo __LINE__." ".print_r($retval);
		return $retval;
	}
}
function _centers_user_delete($center_id,$user_id,$noreload=false){
	$output="";
	$m = UIManager::getInstance();
	/*STSANSVIL-1260
	   Gli user (e solo quelli) segnati con ruolo
		Componente CE (modulo CE),
		Regione (modulo CE)  e
		Segreteria CE (modulo CE)
		che vengono eliminati dal site di Area Vasta
		vengano eliminati anche  all’interno di tutti i “site” che fanno riferimento a quella area vasta.
		NB: MANCA SEGRETERIA CRMS, la metto lo stesso per congruità con inserimento
    */
	$add_delete=" SITE_ID=:SITE_ID ";
	$bind=array();
	$bind['USERID']=$user_id;
	$bind['SITE_ID']=$center_id;

	if($center_id<10){//PRENDO SOLO I CE (ID<10)
		$bindp=array();
		$bindp['USERID']=$user_id;
		//PRENDO I PROFILI DELL'UTENTE
		$select="select * from ACM_USERS_ASSOC where userid=:USERID";
		$rsp = db_query_bind($select,$bindp);

		while ($profile = db_nextrow($rsp)){

			//echo "<pre>";
			if(
				($profile["STUDY_TYPE"]=="CRMS" && $profile["PROFILE_CODE"]=="SEGRETERIA") ||
				($profile["STUDY_TYPE"]=="CRMS" && $profile["PROFILE_CODE"]=="REGIONE") ||
				($profile["STUDY_TYPE"]=="CE" && $profile["PROFILE_CODE"]=="SGR") ||
				($profile["STUDY_TYPE"]=="CE" && $profile["PROFILE_CODE"]=="CMP"))
			{
				//print_r($profile);
				$bindc=array();
				$bindc['CENTERID']=$center_id;
				//PRENDO I CENTRI AFFERENTI A QUESTO CE
				$select="select * from SITES where CE_ID=:CENTERID";
				$rsc = db_query_bind($select,$bindc);
				$i=0;
				while ($center = db_nextrow($rsc)){
					//print_r($center);

					$add_delete.=" OR SITE_ID=:SITE_ID".$i." ";
					$bind["SITE_ID".$i]=$center['ID'];
					$i++;
				}
			}
		}
		//echo "</pre>";
		//die();
	}
	$sql="DELETE FROM USERS_SITES WHERE USERID=:USERID AND ( ".$add_delete.")";
	/*echo "<pre>";
	echo "".$sql;
	 print_r($bind);
	echo "</pre>";
	die();*/
	if(db_query_update_bind($sql,$bind,true)){
		if(!$noreload){
			common_add_message(t("You have deleted the user id <b>".$user_id."</b> from current site"), INFO);
		}
	}
	else{
		if(!$noreload) {
			common_add_message(t("There was an error during the deletion of the user id <b>" . $user_id . "</b> from current site"), ERROR);

		}
	}
	if(!$noreload){
		header("location: ".url_for('/center/users/'.$center_id.'/'));
		die();
	}
}
function _center_get_users_from_ce($center_id){
	/*STSANSVIL-1260
	associazione utenti/centri con pulsante a livello di centro per scaricarsi tutti gli utenti del padre
	*/
	$bind['SITE_ID']=$center_id;
	$center_info=_center_load_center($center_id);
	$sql="DELETE FROM USERS_SITES WHERE SITE_ID=:SITE_ID";
	//var_dump($sql);die();
	if(db_query_update_bind($sql,$bind)) {
		$bind['CE_ID']=$center_info['CE_ID'];
		$sql2="insert into users_sites  select userid,:SITE_ID from users_sites where site_id in (:CE_ID)";
		if(db_query_update_bind($sql2,$bind,true)) {
			common_add_message(t("Operazione eseguita con successo"), INFO);
			if(isAjax()){
				echo json_encode(array("sstatus" => "ok" ));
				db_close();die();
			}
			else{
				return "ok";
			}
		}
	}
}
//FINE GESTIONE UTENTI
?>
