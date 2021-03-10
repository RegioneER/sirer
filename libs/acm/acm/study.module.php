<?php

include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/form.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xml_parser_wl.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/activitiClient.inc";

class xml_form extends xml_form_prototype{
	
}

function study_init() {
	dispatch('/study', 'study_page_new');
	dispatch('/study/new', 'study_page_new');
	dispatch('/study/list', 'study_page_list');
	dispatch_post('/study/new', 'study_page_new');
	dispatch('/study/edit/:prefix', 'study_page_edit');
	dispatch_post('/study/edit/:prefix', 'study_page_edit');
	//dispatch('/profile/list/study/:study', 'profile_page_list_per_study');//VAXMR-302
	dispatch('/study/list/profiles/:study', 'study_page_list_profiles');//VAXMR-302
	//dispatch('/study/dblock/:prefix', 'study_page_dblock');
	
	dispatch('/study/gitrepo/:prefix', 'study_page_gitrepo');
	dispatch_post('/study/gitrepo/:prefix', 'study_page_gitrepo');

	dispatch('/study/export/:prefix', 'study_page_export');
	dispatch_post('/study/export/:prefix', 'study_page_export');

	dispatch('/study/profiles/:prefix', 'study_page_profiles');
	dispatch_post('/study/profiles/:prefix', 'study_page_profiles');
	dispatch('/study/users/:prefix', 'study_page_users');
	dispatch_post('/study/users/:prefix', 'study_page_users');
	dispatch('/study/centers/:prefix', 'study_page_centers');
	dispatch_post('/study/centers/:prefix', 'study_page_centers');

	dispatch('/study/builder/:prefix', 'study_page_builder');
	dispatch_post('/study/builder/:prefix', 'study_page_builder');

	dispatch_post('/study/builder/:prefix/validate', 'study_page_builder_validate');
	dispatch_post('/study/builder/:prefix/copy', 'study_page_builder_copy');
	dispatch_post('/study/builder/:prefix/new_form', 'study_page_builder_new_form');
	dispatch('/study/builder/:prefix/editForm/:form', 'study_page_builder_editForm');
	dispatch_post('/study/builder/:prefix/saveForm', 'study_page_builder_saveForm');
	dispatch_post('/study/builder/:prefix/saveVisiteExam', 'study_page_builder_saveVisiteExam');
	dispatch_post('/study/builder/:prefix/upload', 'study_page_builder_upload');
	dispatch_post('/study/builder/:$study_root/file_exists/:file_xml', 'study_page_builder_file_exists');
	dispatch('/study/builder/:prefix/listImportedFiles', 'study_page_builder_listImportedFiles');

	dispatch('/study/wizard/:prefix/:step', 'study_wizard');
	dispatch_post('/study/wizard/:prefix/:step', 'study_wizard');

	//dispatch('study/toggle/:prefix/:username/:profileid', 'study_toggle_user'); //VAXMR-297 spostata in profile.module.php

	dispatch('/study/builder/:prefix/edit/:item/:id', 'study_editor');
	dispatch_post('/study/builder/:prefix/edit/:item/:id', 'study_editor');

	dispatch('/study/builder/:prefix/buildForm/:form', 'study_form_builder');
	dispatch('/study/builder/:prefix/xBuilder.js', 'study_form_builder_js');
	dispatch_post('/study/builder/:prefix/buildForm/:form/save/:db', 'study_form_builder_save');
	dispatch_get('/study/builder/:prefix/buildForm/:form/save/:db', 'study_form_builder_save');
    dispatch('/study/get_list_study/:jqGrid', '_study_list');
    dispatch('/study/get_list_users/:prefix/:jqGrid/:wizard', '_study_load_users');
    dispatch('/study/get_list_center/:prefix/:jqGrid/:$wizard', '_study_load_centers');
	dispatch('/study/get_list_profiles/:prefix/:jqGrid/', '_study_load_profiles');
	dispatch('/study/get_study/:prefix/:jqGrid/','_study_load');
}

function study_sidebar($sideBar) {
	$itm2 = new SideBarItem(new Link(t("Product Instances"), "gears", "#"));
	$cuser = _user_load_user($_SERVER['REMOTE_USERID']);
	if (in_array("tech-admin",$cuser['PROFILI'])) {//STSANPRJS-570
        $itm2->addItem(new SideBarItem(new Link(t("New product instance"), "plus", url_for('/study/new')), null, UIManager::_checkActive('/study/new')));
    }
	$itm2 -> addItem(new SideBarItem(new Link(t("List existing product instances"), "list", url_for('/study/list')), null, UIManager::_checkActive('/study/list')));
	$sideBar -> addItem($itm2);

	return $sideBar;
}

function study_js($js){
	$js.='
	<script src="?/study/builder/'.params('prefix').'/xBuilder.js"></script>
	';
	return $js;
}

function study_backLinks($backLinks) {
	$m = UIManager::getInstance();
/*	if (UIManager::_checkActive('/study/builder/')) {
		$backLinks = "<a href=\"" . url_for('/study/builder/' . $m -> getCurrentUrl(3)) . "\"><i class=\"fa fa-gears\"></i>" . t("Go back to study builder page") . "</a>";
	}
 */
 	if (UIManager::_checkActive('/buildForm/') || UIManager::_checkActive('/editForm/') || UIManager::_checkActive('/validate')) {
		$backLinks .= "<a href=\"" . url_for('/study/builder/' . $m -> getCurrentUrl(3)) . "/edit/structure\"><i class=\"fa fa-indent bigger-110\"></i>&nbsp;" . t("Go to Edit product instance structure") . "</a>";
	}
	if (UIManager::_checkActive('/study/wizard/')) {
		//var_dump($m->getCurrentUrl());
		$backLinks = "<span class=\"badge " . ($m -> getCurrentUrl(4) == 1 ? "badge-primary" : "badge-grey") . "\"><a style=\"color:white;\" href=\"" . ($m -> getCurrentUrl(4) == 1 ? "#" : url_for('/study/wizard/' . $m -> getCurrentUrl(3) . '/1')) . "\">1</a></span>
					<span class=\"badge " . ($m -> getCurrentUrl(4) == 2 ? "badge-primary" : "badge-grey") . "\"><a style=\"color:white;\" href=\"" . ($m -> getCurrentUrl(4) == 2 ? "#" : url_for('/study/wizard/' . $m -> getCurrentUrl(3) . '/2')) . "\">2</a></span>
					<span class=\"badge " . ($m -> getCurrentUrl(4) == 3 ? "badge-primary" : "badge-grey") . "\"><a style=\"color:white;\" href=\"" . ($m -> getCurrentUrl(4) == 3 ? "#" : url_for('/study/wizard/' . $m -> getCurrentUrl(3) . '/3')) . "\">3</a></span>
					<span class=\"badge " . ($m -> getCurrentUrl(4) == 4 ? "badge-primary" : "badge-grey") . "\"><a style=\"color:white;\" href=\"" . ($m -> getCurrentUrl(4) == 4 ? "#" : url_for('/study/wizard/' . $m -> getCurrentUrl(3) . '/4')) . "\">4</a></span>";
	}

	return $backLinks;
}

function study_breadcrumb($paths) {
	$m = UIManager::getInstance();
	if (UIManager::_checkActive('/study')) {
		$paths[] = array(t("Product Instances"), t("Product Instances"), url_for('/study/list'));

		if (UIManager::_checkActive('/study/new')) {
			$paths[] = array(t("New product instance"), t("New product instance"), url_for('/study/new'));

		}
		if (UIManager::_checkActive('/study/edit')) {
			$paths[] = array(t("Edit product instance"), t("Edit product instance"), url_for('/study/edit'));

		}
		if (UIManager::_checkActive('/study/list/profiles/')) {
			$paths[] = array(t("List Active Profiles per Product Instance"), t("List Active Profiles per Study"), url_for('/study/list'));
		}
		else
		if (UIManager::_checkActive('/study/list')) {
			$paths[] = array(t("List existing product instances"), t("List existing product instances"), url_for('/study/list'));
		}
		
		if (UIManager::_checkActive('/study/profiles')) {
			$paths[] = array(t("Profile Management"), t("Profile Management"), url_for('/study/profiles'));
		}
		if (UIManager::_checkActive('/study/builder')) {
			$paths[] = array(t("Product Instance Builder"), t("Product Instance Builder"), url_for('/study/builder/' . $m -> getCurrentUrl(3)));
		}
		if (UIManager::_checkActive('/edit/structure')) {
			$paths[] = array(t("Edit product instance structure"), t("Edit product instance structure"), url_for('/study/builder/' . $m -> getCurrentUrl(3) . '/edit/structure'));
		}
		if (UIManager::_checkActive('/listImportedFiles')){
			$paths[] = array(t("Import from CDISC ODM file"),t("Import from CDISC ODM file"),url_for('/study/builder/' . $m -> getCurrentUrl(3) . '/listImportedFiles'));
		}

		if (UIManager::_checkActive('/editForm')) {
			$paths[] = array(t("Edit form"), t("Edit form"), url_for('/study/builder/' . $m -> getCurrentUrl(3) . '/edit/structure'));
		}
		if (UIManager::_checkActive('/buildForm')) {
			$paths[] = array(t("Build form"), t("Build form"), url_for('/study/builder/' . $m -> getCurrentUrl(3) . '/buildForm/'.$m -> getCurrentUrl(5)));	
		}
		if (UIManager::_checkActive('/validate')) {
			$paths[] = array(t("Validate"), t("Validate"), url_for('/study/builder/' . $m -> getCurrentUrl(3) . '/validate'));
		}

		if (UIManager::_checkActive('/study/users')) {
			$paths[] = array(t("User Authorization Management"), t("User Authorization Management"), url_for('/study/users'));
		}
		if (UIManager::_checkActive('/study/centers')) {
			$paths[] = array(t("Add/remove centers"), t("Add/remove centers"), url_for('/study/centers'));
		}
		if (UIManager::_checkActive('/study/wizard')) {
			$paths[] = array(t("Wizard Product Instance configurator"), t("Wizard Product Instance configurator"), url_for('/study/wizard'));
		}
	}

	return $paths;
}

function study_getPageTitle($page_title) {
	if (UIManager::_checkActive('/study')) {
		$page_title = t("Product Instances");
		if (UIManager::_checkActive('/study/new')) {
			$page_title = t("New product instance");

		}
		if (UIManager::_checkActive('/study/edit')) {
			$page_title = t("Edit product instance");
		}
		if (UIManager::_checkActive('/study/list/profiles/')) {
			$page_title =t("List Active Profiles per Product Instance");
		}
		else
		if (UIManager::_checkActive('/study/list')) {
			$page_title = t("List existing product instances");
		}

		if (UIManager::_checkActive('/study/profiles')) {
			$page_title = t("Profile Management");
		}

		if (UIManager::_checkActive('/study/users')) {
			$page_title = t("User Authorization Management");
		}

		if (UIManager::_checkActive('/study/centers')) {
			$page_title = t("Add/remove centers");
		}

		if (UIManager::_checkActive('/study/builder')) {
			$page_title = t("Product Instance Builder");
		}
		if (UIManager::_checkActive('/edit/structure')) {
			$page_title = t("Edit product instance structure");
		}
		if (UIManager::_checkActive('/listImportedFiles')){
			$page_title = t("Import from CDISC ODM file");
		}
		
		if (UIManager::_checkActive('/editForm')) {
			$page_title = t("Edit form");
		}
		if (UIManager::_checkActive('/buildForm')) {
			$page_title = t("Build form");
		}
		if (UIManager::_checkActive('/study/wizard')) {
			$page_title = t("Wizard Product Instance configurator");
		}

	}
	return $page_title;
}

function study_form($row, $action) {
	$m = UIManager::getInstance();
	global $products;
	$output = "";
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';
	$output .= '' . $m -> dsp_getTextField('Product Instance Title', 'TITLE', '', '', ($action == ACT_MODIFY), false, $row, true) . '';
	$output .= '' . $m -> dsp_getTextArea('Note', 'NOTE', '', '', ($action == ACT_MODIFY), false, $row, 500, false) . '';
	$output .= '' . $m -> dsp_getTextField('Prefix', 'PREFIX', '', '', ($action == ACT_MODIFY), false, $row, true) . '';
	$output .= '' . $m -> dsp_getHiddenField(OLDPREFIX . 'PREFIX', $row['PREFIX'], false, $row) . '';
	$output .= '' . $m -> dsp_getTextField('Product Instance URL', 'DESCR', 'insert the name of the root directory of the Product Instance', '', ($action == ACT_MODIFY), false, $row, true) . '';
	if ($action == ACT_MODIFY) {
		$output .= '' . $m -> dsp_getTextField('Type', 'TYPE', '', '', ($action == ACT_MODIFY), false, $row, true) . '';
	} else {
		$output .= '' . $m -> dsp_getSelectField('Type', 'TYPE', '', '', false, $row['TYPE'], $products, null, true) . '';
	}
	$output .= '' . $m -> dsp_getCheckbox('STATUS', 'ACTIVE', '', 'Enabled', false, false, $row) . '';

	if ($action==ACT_MODIFY && $row['TYPE']=="CLINICAL_TRIAL") {
		//$output .= '' . $m->dsp_getCheckbox('SDV Requested', 'SDV_REQD', '', 'Requested', false, false, $row) . '';
		//$output .= '' . $m->dsp_getCheckbox('MREVIEW Requested', 'MREVIEW_REQD', '', 'Requested', false, false, $row) . '';
		//$output .= '' . $m->dsp_getCheckbox('DREVIEW Requested', 'DREVIEW_REQD', '', 'Requested', false, false, $row) . '';
		//$output .= '' . $m->dsp_getTextField('Source System', 'SOURCE_SYSTEM', 'defined source system', '', false, false, $row, true) . '';
	}

	$output .= '' . $m -> dsp_getButtonsSubmitUndo('submit', 'submit-button', 'reset', 'reset-button') . '';
	$output .= '</form>';
	if ($action==ACT_INSERT){
		//$output .= '<p style="font-weight: bold; color:red;">If the study is a Clinical trial, additional information may be needed for data export. Please use EDIT function after creation.</p>';
	}
	return $output;
}

function study_form_validate($action) {
	$retval = true;
	$row = $_POST;
	$row['DESCR'] = str_replace(" ", "_", trim($row['DESCR']));
	$row['PREFIX'] = trim(strtoupper($row['PREFIX']));
	if (!$row['PREFIX']) {
		common_add_message(t("Please specify the field ") . " '" . t("Prefix") . "'", WARNING);
		$retval = false;
	} else if (strlen($row['PREFIX']) >= 6) {
		common_add_message(t("The field ") . " '" . t("Prefix") . "' " . t(" can not exceed 5 characters lenght."), WARNING);
		$retval = false;
	} else {
		$studies = _study_list();
		//var_dump($studies);
		foreach ($studies as $key => $study) {
			if ($study['PREFIX'] == $row['PREFIX'] && $study['ID'] != $row['ID']) {
				common_add_message(t("Another Product Instance has the same value for the field ") . " '" . t("Prefix") . "'", WARNING);
				$retval = false;
			}
		}
	}
	/*
	if (!$row['NOTE']) {
		common_add_message(t("Please specify the field ") . " '" . t("Note") . "'", WARNING);
		$retval = false;
	}
	*/
	
	if (!$row['DESCR']) {
		common_add_message(t("Please specify the field ") . " '" . t("Product Instance URL") . "'", WARNING);
		$retval = false;
	} else {
		$studies = _study_list();
		//var_dump($studies);
		foreach ($studies as $key => $study) {
			if ($study['DESCR'] == $row['DESCR'] && $study['ID'] != $row['ID']) {
				common_add_message(t("Another Product Instance has the same value for the field ") . " '" . t("Product Instance URL") . "'", WARNING);
				$retval = false;
			}
		}
	}
	if (!$row['TITLE']) {
		common_add_message(t("Please specify the field ") . " '" . t("Product Instance Title") . "'", WARNING);
		$retval = false;
	}
	if (!$row['TYPE']) {
		common_add_message(t("Please specify the field ") . " '" . t("Product Instance Type") . "'", WARNING);
		$retval = false;
	}
	return $retval;
}

function study_form_submit($action) {
	$retval = false;
	$row = $_POST;
	unset($row['submit-button']);
	unset($row['reset-button']);

	$row = common_booleanCheckBox($row, 'ACTIVE');
	//$row = common_booleanCheckBox($row, 'SDV_REQD');
	//$row = common_booleanCheckBox($row, 'MREVIEW_REQD');
	//$row = common_booleanCheckBox($row, 'DREVIEW_REQD');

	

	$first_install = false;
    $need_git_commit = false;
    $collection_dir = "/";
	if ($action == ACT_INSERT) {
		
		/*Creo la funzione ed il gruppo di funzioni*/
		$table_funz = "FUNZIONI";
		
		$row_funz['NOME']=$row['DESCR'];
		if (!preg_match("!^\/!",$row['DESCR'])){
			$row_funz['NOME']="/".$row['DESCR'];
		}
		if ($row['TYPE']=='DRUPAL') {
			$row_funz['NOME'] = "/portal/" . $row['DESCR'] . '/';
			$collection_dir = "/portal/";
		}
		$row_funz['ABILITATO'] = 1;
		$row_funz['PASSWD_FLAG'] = 1;
		$row_funz['IANUSGATE_FLAG'] = 0;
		$row_funz['SSL_ONLY_FLAG'] = 1;
		$row_funz['CRT_ONLY_FLAG'] = 0;
		$row_funz['ID_VISTA'] = 0;
		$row_funz['UPDATE_ID'] = 0;
		
		
		$table_ana_funz='ANA_FUNZIONI';
		$row_ana_funz['NOME']=$row_funz['NOME'];
		$row_ana_funz['DESCRIZIONE']=$_POST['PREFIX']." - Funzione di gestione servizio ".$_POST['TYPE'];
		$row_ana_funz['UPDATE_ID'] = $row_funz['UPDATE_ID'];
		
		$table_gruppif = "GRUPPIF";
		$row_gruppof = array();
		$id_gruppof = "";
		$rs = db_query("SELECT gruppif_sequence.nextval as NEXT FROM DUAL");
		if ($_row = db_nextrow($rs)) {
			$id_gruppof = $_row['NEXT'];
		}
		$row_gruppof['ID_GRUPPOF'] = $id_gruppof;
		$row_gruppof['ABILITATO'] = 1;
		$row_gruppof['ID_VISTA'] = 0;
		$row_gruppof['UPDATE_ID'] = 0;
		
		$table_ana_gruppif = "ANA_GRUPPIF";
		$row_ana_gruppof['ID_GRUPPOF'] = $id_gruppof;
		$row_ana_gruppof['NOME_GRUPPO'] = $_POST['PREFIX']." - Gruppo - ".$_POST['TYPE'];
		$row_ana_gruppof['DESCRIZIONE'] = $_POST['PREFIX']." - Gruppo di funzioni di gestione servizio ".$_POST['TYPE'];
		$row_ana_gruppof['UPDATE_ID'] = 0;
		
		$table_gruppif_funz="GRUPPIF_FUNZ";
		$row_gruppif_funz['NOME_FUNZ']=$row_ana_funz['NOME'];
		$row_gruppif_funz['ID_GRUPPOF']=$id_gruppof;
		$row_gruppif_funz['ABILITATO']=1;
		$row_gruppif_funz['UPDATE_ID'] = 0;
		
		$row['DESCR'] = str_replace(" ", "_", trim($row['DESCR']));
		$row['PREFIX'] = trim(strtoupper($row['PREFIX']));
		$table = "STUDIES";
		if (!db_form_updatedb($table, $row, $action, 'PREFIX', false)) {
			common_add_message(t("ERROR!"), ERROR);
			return false;
		}
		
		if (!db_form_updatedb($table_funz, $row_funz, $action, 'NOME', false)) {
			common_add_message(t("ERROR!"), ERROR);
			return false;
		}
		if (!db_form_updatedb($table_ana_funz, $row_ana_funz, $action, 'NOME', false)) {
			common_add_message(t("ERROR!"), ERROR);
			return false;
		}
		if (!db_form_updatedb($table_gruppif, $row_gruppof, $action, 'ID_GRUPPOF', false)) {
			common_add_message(t("ERROR!"), ERROR);
			return false;
		}
		if (!db_form_updatedb($table_ana_gruppif, $row_ana_gruppof, $action, 'ID_GRUPPOF', false)) {
			common_add_message(t("ERROR!"), ERROR);
			return false;
		}
		if (!db_form_updatedb($table_gruppif_funz, $row_gruppif_funz, $action, array('ID_GRUPPOF', 'NOME_FUNZ'), false)) {
			common_add_message(t("ERROR!"), ERROR);
			return false;
		}
		$retval=true;
		db_commit();
		common_add_message(t("Operazione completata con successo"), INFO);
		
        $first_install = true;
	}


	if($action==ACT_MODIFY){ //VAXMR-323 vmazzeo 17.02.2016
		// echo "<pre>POST<br/>";
		// print_r($row);
		// echo "</pre>";
		//devo impostare "abilitato" su: studies, funzioni, gruppif
		
		//ottengo id gruppof
		$bind=array();
		$bind['NOME_GRUPPO']=$_POST['PREFIX']." - Gruppo - ".$_POST['TYPE'];
		$rs = db_query_bind("SELECT ID_GRUPPOF FROM ANA_GRUPPIF where NOME_GRUPPO=:NOME_GRUPPO",$bind);
		if ($_row = db_nextrow($rs)) {
			$id_gruppof = $_row['ID_GRUPPOF'];
		}
		// echo "<pre>ID_GRUPPOF<br/>";
		// print_r($id_gruppof);
		// echo "</pre>";
// 		
		//update gruppif
		$table="GRUPPIF";
		$updgruppif[OLDPREFIX . 'ID_GRUPPOF'] = $id_gruppof;
		$updgruppif['ABILITATO']=$row['ACTIVE'];
		if (!db_form_updatedb($table, $updgruppif, $action, 'ID_GRUPPOF')) {
			common_add_message(t("An error occurred during Product Instance editing. (GRUPPIF)"), WARNING);
			$retval = false;
		}
		else{
			//common_add_message(t("Gruppo funzioni modificato con successo"), INFO);
			$retval = true;
		}
		if($retval){
			//update funzioni
			$table="FUNZIONI";
			$nomefunzione['NOME']=$row['DESCR'];
			if (!preg_match("!^\/!",$row['DESCR'])){
				$nomefunzione['NOME']="/".$row['DESCR'];
			}
			if ($row['TYPE']=='DRUPAL') {
				$nomefunzione['NOME'] = "/portal/" . $row['DESCR'] . '/';
				$collection_dir = "/portal/";
			}
			$updfunzioni[OLDPREFIX . 'NOME'] = $nomefunzione['NOME'];
			$updfunzioni['ABILITATO'] = $row['ACTIVE'];
			if (!db_form_updatedb($table, $updfunzioni, $action, 'NOME')) {
				common_add_message(t("An error occurred during Product Instance editing. (FUNZIONI)"), WARNING);
				$retval = false;
			}
			else{
				//common_add_message(t("Funzione modificata con successo"), INFO);
				$retval = true;
			}
		}
		if($retval){
			//update studies
			$table="STUDIES";
			
			$updstudies[OLDPREFIX . 'PREFIX'] = $row[OLDPREFIX . 'PREFIX'];
			$updstudies['ACTIVE'] = $row['ACTIVE'];
			if (!db_form_updatedb($table, $updstudies, $action, 'PREFIX')) {
				common_add_message(t("An error occurred during Product Instance editing. (STUDIES)"), WARNING);
				$retval = false;
			}
			else{
				common_add_message(t("Studio modificato con successo"), INFO);
				$retval = true;
			}
		}
		db_close();
	}
	//PAREXEL EXPORT - CSV Generation
	$parexel_export = false;
	if ($parexel_export) {
		/*
		//Create export folder (if not exists
		if (!is_dir('export')) {
			if (!mkdir('export', 0777, true)){
				common_add_message("Cannot create 'export' folder!",ERROR);
			}
		}
		//Write "config_study_crf.csv" file (this file describes form ECRFs, to be implemented into the builder)
		$headers =  "STUDY_REF_KEY,". //key
					"SYSTEM_CRF_REF_KEY,". //mandatory
					"CRF_NAME,". //mandatory
					"CRF_DISPLAY_NAME,". //string
					"STUDY_CRF_REF_KEY,". //key
					"SDV_REQD,". //number
					"MREVIEW_REQD,". //number
					"DREVIEW_REQD,". //number
					"SOURCE_SYSTEM"; //string
		$data = "{$row['PREFIX']},". //key //ID numerico non ce l'ho, ho solo PREFIX!
				"{$row['PREFIX']},". //mandatory
				"{$row['DESCR']},". //mandatory
				"{$row['TITLE']},". //string
				"{$row['PREFIX']},". //key
				"{$row['SDV_REQD']},". //number
				"{$row['MREVIEW_REQD']},". //number
				"{$row['DREVIEW_REQD']},". //number
				"{$row['SOURCE_SYSTEM']}"; //string
		$csvdata = $headers."\n".$data;
		//Naming convention: <Gateway>_<Interfacename>_<InterfaceFlavor>_<SrcName>_<Version>_<Timestamp>
		//native_study_na_IMPACT_14.1_20120430T123029.csv
		$tstamp = date("YmdTHis");
		file_put_contents('export/'.$row['PREFIX'].".csv",$csvdata);
		file_put_contents('export/native_study_na_IMPACT_14.1_'.$tstamp.'.csv',$csvdata);

		*/

		/*
		//Write "config_study_crf_data_item.csv" file --> Sembra la definizione di una scheda di raccolta dati dello studio
		$headers =  "STUDY_REF_KEY,". //key
			"STUDY_CRF_DATA_ITEM_REF_KEY,". //key
			"ITEM_REF_KEY,".
			"ITEM_GROUP_REF_KEY,".
			"SECONDARY_ITEM_GROUP_REF_KEY,".
			"ITEM_NAME,".
			"ITEM_GROUP_NAME,".
			"QUESTION_ID,".
			"QUESTION_NAME,".
			"QUESTION_PROMPT,".
			"IS_DREVIEW_REQD,".
			"IS_SDV_REQD,".
			"IS_MREVIEW_REQD,".
			"STUDY_CRF_REF_KEY,".
			"SYSTEM_CRF_REF_KEY,".
			"CRF_NAME,".
			"CRF_DISPLAY_NAME,".
			"IS_DELETED,SOURCE_SYSTEM"; //string
		*/
	}

    if ($first_install) {
    	
        //var_dump(SYSTEMBASEURL_LIBRARY);  C:/xampp/htdocs/service/service/html/../libs/acm/
        /*
         * mkdir ./study/[STUDY_NAME]/
         * cp -p  ../libs/cro/installer/index.php .
         * cp -rp ../libs/cro/installer/uxmr/ .
         *
         */
        if ($row['TYPE']=='CLINICAL_TRIAL' || $row['TYPE']=='LABORATORY_RANGE'){
            $prompt = '/(\\$|>)+/'; //Regex prompt pattern (o $ o > e fine linea)
            echo $prompt;
            $gitexec = LOCAL_GIT_BIN;
            //return;
            //Verifica esistenza repo GIT su ssh://cin9361a@cvs.private.cineca.it/cvsroot/siss-git/projects/genes/[nomeservizio].git
            set_include_path(SYSTEMBASEURL_LIBRARY . '../phpseclib/phpseclib');
            include_once('Net/SSH2.php');
            $gitrepo =  $row['DESCR'].".git";
            $sshconn = new Net_SSH2('cvs.private.cineca.it'); //'sissgit', '2NB;ZQ9Y' //'cvssiss3', 'AXRsr51!'
            if (!$sshconn->login('sissgit', '2NB;ZQ9Y')) {
                common_add_message(t("SSH authentication failed!"), ERROR);
                return $retval;
            }
            $gitRepoPath=GITREPO_ROOTFOLDER;
            global $gitRepoBase;
            if ($gitRepoBase!=''){
            	$gitRepoPath="/cvsroot/siss-git/projects/".$gitRepoBase;
            }
            //$output = $sshconn->exec('pwd');
            //echo "\n<br/>".$output."\n<br/>";
            $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            //echo "\n<br/>".$output."\n<br/>";
            $sshconn->write('cd '.$gitRepoPath."\n");
            $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            //echo "\n<br/>".$output."\n<br/>";
            $sshconn->write('pwd'."\n");
            $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            //echo "\n<br/>".$output."\n<br/>";
            $sshconn->write("ls -al {$gitrepo}"."\n");
            $dir = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            //echo "<br/>EXISTING DIR: ".$dir;
            if (stristr($dir, 'No such file or directory')!==FALSE){
                //Init git repo
                $sshconn->write("git init --bare --shared=true {$gitrepo}"."\n");
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                //echo "\n<br/>".$output."\n<br/>";
                common_add_message(t("GIT repository initialized!<br/>"), INFO);
                $need_git_commit = true;
            }
            $sshconn->disconnect();
            //Git clone repo
            //require_once SYSTEMBASEURL_LIBRARY . '../glip/lib/autoload.php';

            $odir = getcwd();
            chdir($_SERVER ['DOCUMENT_ROOT'] . '/study');
            //$output = system();
            //Tento di collegarmi al mio server con l'utenza git in interactive shell...
            $sshconn = new Net_SSH2(LOCAL_SSH_SERVER);
            echo "<br/>".LOCAL_SSH_SERVER."<br/>";
            if (!$sshconn->login('sissgit', '2NB;ZQ9Y')) {
                common_add_message(t("SSH2 authentication failed!"), ERROR);
                return $retval;
                //echo "SSH2 ERROR!<br/>";
            }

            $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            echo "\n<br/>".$output."\n<br/>";
            $sshconn->write('cd '."/http/servizi/".IDP_NAME."/".SERVICE_FOLDER."/html".'/study'."\n"); ///http/servizi/GENIUS/[service]/html/study
            $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            echo "\n<br/>".$output."\n<br/>";
            //echo "{$gitexec} clone ssh://cvs.private.cineca.it/cvsroot/siss-git/projects/genes/{$gitrepo}\n<br/>";
            $sshconn->write("{$gitexec} clone ssh://cvs.private.cineca.it".$gitRepoPath."/{$gitrepo}\n");
            //$output = $sshconn->read("...");
            ////$output = $sshconn->read('/(password:|?|>|\\$)+/', NET_SSH2_READ_REGEX);
            //echo "\n<br/>".$output."\n<br/>";
            //$sshconn->write("AXRsr51!\n");

            $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            //$output = $sshconn->read("!");
            //echo "\n<br/>".$output."\n<br/>";
            //$output = $sshconn->read("done.");
            echo "\n<br/>".$output."\n<br/>";
            $sshconn->write("chmod g+w -R {$row['DESCR']}\n");
            $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
            echo "\n<br/>".$output."\n<br/>";
            $sshconn->disconnect();

            //use Glip\Git
            //$repo = new Git($gitrepo);
            clearstatcache();
            //db_close();die("STOP");
            if ($need_git_commit){
                //Creazione filesystem --> Inserire repository GIT
                $study_dir = $_SERVER ['DOCUMENT_ROOT'] . $row_funz['NOME'];
                //die ($study_dir);
                //mkdir($study_dir, 0775);
                //db_close();die($_SERVER ['DOCUMENT_ROOT'].$row_funz['NOME']);
                $source_dir = SYSTEMBASEURL_LIBRARY . '../xCRF/installer/';
                if ($row['TYPE']=='LABORATORY_RANGE'){
                    $source_dir = SYSTEMBASEURL_LIBRARY . '../xCRF/installer_lab/';
                }
                //echo "<b>" . $study_dir . " " . $source_dir . "</b>";
                //Controllo cartella
                //$odir = getcwd();
                //echo "$odir<br/>\n";
                //chdir($study_dir);
                //$odir = getcwd();
                //echo "$odir<br/>\n";

                if (!_xcopy(rtrim($source_dir,"/"), rtrim($study_dir,"/"))) {
                    common_add_message(t("ERROR DURING FILE SYSTEM CREATION "), ERROR);
                    return false;
                }
                $retval = true;
                //Link simbolico a libs
                symlink($_SERVER ['DOCUMENT_ROOT'] . '/../libs/xCRF/', $study_dir . "/libs"); //target, link


                $study_xml_file = $study_dir . "/study.xml";
                $fhandle = fopen($study_xml_file, "r");
                $content = fread($fhandle, filesize($study_xml_file));
                fclose($fhandle);

                $content = str_replace("[STUDY_NAME]", '/' . $row['DESCR'] . '/', $content);
                $content = str_replace("[PREFIX]", $row['PREFIX'], $content);

                $fhandle = fopen($study_xml_file, "w");
                fwrite($fhandle, $content);
                fclose($fhandle);

                //die ($study_dir);
                //ADDED?
                //FACCIO IL REPLACE PER OGNI OCCORRENZA DI [PREFIX] in tutti i file di configurazione dei profili
                if (is_dir($study_dir.'/conf/')) {
                    if ($handle = opendir($study_dir.'conf/')) {
                        while (false !== ($file = readdir($handle))) {
                            if (!is_dir($study_dir.'conf/'. $file) && $file != "." && $file != ".." && preg_match("/\.xml/i", $file)){
                                //echo $study_dir.'conf/';
                                //echo "<br>".$file;

                                $fhandle = fopen($study_dir.'conf/'.$file, "r");
                                $content = fread($fhandle, filesize($study_dir.'conf/'.$file));
                                fclose($fhandle);
                                $content = str_replace("[PREFIX]", $row['PREFIX'], $content);
                                $content = str_replace("[TITLE]", $row['TITLE'], $content);
                                //echo "<br/>".$content;
                                //db_close();die();
                                $fhandle = fopen($study_dir.'conf/'.$file, "w");
                                fwrite($fhandle, $content);
                                fclose($fhandle);
                            }
                        }
                    }
                }
                //FACCIO IL REPLACE PER OGNI OCCORRENZA DI [PREFIX] in tutti i file di liste equery per i profili
                if (is_dir($study_dir.'/xml/')) {
                    if ($handle = opendir($study_dir.'xml/')) {
                        while (false !== ($file = readdir($handle))) {
                            if (!is_dir($study_dir.'xml/'. $file) && $file != "." && $file != ".." && preg_match("/\.xml/i", $file)){
                                //echo $study_dir.'conf/';
                                //echo "<br>".$file;

                                $fhandle = fopen($study_dir.'xml/'.$file, "r");
                                $content = fread($fhandle, filesize($study_dir.'xml/'.$file));
                                fclose($fhandle);
                                $content = str_replace("[PREFIX]", $row['PREFIX'], $content);
                                //echo "<br/>".$content;
                                //db_close();die();
                                $fhandle = fopen($study_dir.'xml/'.$file, "w");
                                fwrite($fhandle, $content);
                                fclose($fhandle);
                            }
                        }
                    }
                }
                //FINE ADDED?
                system("chmod g+w -R {$study_dir}");
                system("chgrp devj -R {$study_dir}");

                //Committo i files esistenti sul git - connessione al server con utente sissgit
                CommitLocalFiles($row,"Initial commit",true);
                /*
                $sshconn = new Net_SSH2(LOCAL_SSH_SERVER);
                echo "<br/>".LOCAL_SSH_SERVER."<br/>";
                if (!$sshconn->login('sissgit', '2NB;ZQ9Y')) {
                    common_add_message(t("SSH2 authentication failed!"), ERROR);
                    //echo "SSH2 ERROR!<br/>";
                }
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                echo "\n<br/>".$output."\n<br/>";
                $sshconn->write('cd '."/http/servizi/".IDP_NAME."/".SERVICE_FOLDER."/html/study/{$row['DESCR']}"."\n"); ///http/servizi/GENIUS/[service]/html/study
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                echo "\n<br/>".$output."\n<br/>";
                $sshconn->write("{$gitexec} add *\n");
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                echo "\n<br/>".$output."\n<br/>";
                //Setting globals (non si sa mai che qualcuno le cambi....)
                //git config --global user.email "you@example.com"
                //git config --global user.name "Your Name"
                //e modalità di push
                //git config --global push.default simple
                $sshconn->write("{$gitexec} config --global user.email '".GIT_EMAIL."'\n");
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                echo "\n<br/>".$output."\n<br/>";
                $sshconn->write("{$gitexec} config --global user.name '".GIT_USER."'\n");
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                echo "\n<br/>".$output."\n<br/>";
                $sshconn->write("{$gitexec} config --global push.default simple\n");
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                echo "\n<br/>".$output."\n<br/>";
                //Ora posso applicare il mio commit
                $sshconn->write("{$gitexec} commit -m 'Initial commit' \n");
                $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
                echo "\n<br/>".$output."\n<br/>";
                //E fare push
                $sshconn->write("{$gitexec} push \n");
                $output = $sshconn->read("{$row['DESCR']}>");
                echo "\n<br/>".$output."\n<br/>";
                //A questo punto chiudo e mi scollego
                $sshconn->disconnect();
                */
                //Fine commit dei files
            }

            if ($retval) {
                common_add_message(t("Filesystem created!<br/>"), INFO);
            }
        }
        if ($row['TYPE']=='DRUPAL') {
            //Per ora i portali drupal sono fuori da GIT ed installati sotto la cartella /portal/
            //Creazione filesystem --> Inserire repository GIT
            $study_dir = $_SERVER ['DOCUMENT_ROOT'] . $row_funz['NOME'];
            $main_dir = $_SERVER ['DOCUMENT_ROOT'].$collection_dir;
            if (!file_exists($main_dir)){
                mkdir($main_dir, 0775);
                system("chmod g+w {$main_dir}");
                system("chgrp devj  {$main_dir}");
            }
            $source_dir = SYSTEMBASEURL_LIBRARY . '../xCRF/installer_drupal/';

            if (!_xcopy(rtrim($source_dir,"/"), rtrim($study_dir,"/"))) {
                common_add_message(t("ERROR DURING FILE SYSTEM CREATION "), ERROR);
                return false;
            }
            $drp_settings_file = $study_dir . "/sites/default/settings.php";
            //db_close();die($drp_settings_file);
            $fhandle = fopen($drp_settings_file, "r");
            $content = fread($fhandle, filesize($drp_settings_file));
            fclose($fhandle);

            $content = str_replace("[STUDY_NAME]", '/' . $row['DESCR'] . '/', $content);
            $content = str_replace("[PREFIX]", $row['PREFIX'], $content);

            $fhandle = fopen($drp_settings_file, "w");
            fwrite($fhandle, $content);
            fclose($fhandle);

            system("chmod g+w -R {$study_dir}");
            system("chgrp devj  -R {$study_dir}");

            $retval = true;

            //Configurazione DB e prefisso?

            if ($retval) {
                common_add_message(t("Filesystem created!<br/>"), INFO);
            }
        }
    }else{
        //common_add_message(t("Not first installation.<br/>"), INFO);
    }
	if ($action == ACT_INSERT) {
		if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
			header("Location: /study/{$row['DESCR']}/index.php?init_service");
			db_close();die();
		}
		if ($row['TYPE'] == 'DRUPAL') {
			header("Location: /portal/{$row['DESCR']}/install.php");
			db_close();die();
		}
	}
	
	return $retval;

}

//var_dump($_SERVER["SERVER_NAME"]);

/**
 * Copy a file, or recursively copy a folder and its contents
 * @param       string   $source    Source path
 * @param       string   $dest      Destination path
 * @param       string   $permissions New folder creation permissions
 * @return      bool     Returns true on success, false on failure
 */
function _xcopy($source, $dest, $permissions = 0775) {
	// Check for symlinks
	if (is_link($source)) {
		return symlink(readlink($source), $dest);
	}

	// Simple copy for a file
	if (is_file($source)) {
		$res = copy($source, $dest);
		//echo "COPIED: {$source} --> {$dest} -- RESULT: {$res}<br/>\n";
		return $res;
	}

	// Make destination directory
	if (!is_dir($dest)) {
		mkdir($dest, $permissions);
	}

	// Loop through the folder
	$dir = dir($source);
	while (false !== $entry = $dir -> read()) {
		// Skip pointers
		if ($entry == '.' || $entry == '..') {
			continue;
		}

		// Deep copy directories
		_xcopy("$source/$entry", "$dest/$entry");
	}

	// Clean up
	$dir -> close();
	return true;
}

function study_page_new() {
	$output = "";
	/*
	 $d = Dispatcher::getInstance();
	 $d->study_new();
	 return html($d->dsp_getPageContent());
	 */
	// $m = UIManager::getInstance();
	$row = array();
	$row['PREFIX'] = "";
	$row['TYPE'] = "";
	if ($_POST) {
		if (study_form_validate(ACT_INSERT)) {
			if (study_form_submit(ACT_INSERT)) {
				header("location: " . url_for('/study/list'));
				db_close();die();
			} else {
				$output .= t("An error occurred during Product Instance creation.");
			}
		}
		$row = $_POST;
	}
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">
				';
	$output .= study_form($row, ACT_INSERT);
	$output .= '
			</form>';
	return html($output);
}

function study_page_edit($prefix) {
	$output = "";
	$row = _study_load($prefix,false);
	if ($_POST) {
		if (study_form_validate(ACT_MODIFY)) {
			if (study_form_submit(ACT_MODIFY)) {
				header("location: " . url_for('/study/edit/'.$prefix));
				db_close();die();
			} else {
				$output .= t("An error occurred during Product Instance update.");
			}
		}
		$row = $_POST;
	}
	$output .= study_form($row, ACT_MODIFY);
	return html($output);
}

/*function study_page_dblock($prefix) {
    global $base_url;
	header ( "location: {$base_url}DB_Lock.php?study_prefix={$prefix}" );
	//echo url_for ( '/study/list' );
	//header ( "location: " . url_for ( '/study/list' ) );
	db_close();die();
}*/

function study_page_list() {
	$page = false;
	if (isset($_GET['page'])) {
		$page = $_GET['page'];
	}
	$output = '';
	$m = UIManager::getInstance();
	$list = _study_list(false);
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/study/get_list_study/jqGrid');
    $caption=t("Existing product instances");
	$labels = array('PREFIX' => array('NAME' => 'PREFIX', 'TYPE' => 'TEXT', 'SORT' => 1, 'SEARCH'=>1),
                    'URL' => array('NAME' => 'DESCR', 'TYPE' => 'TEXT', 'SORT' => 1, 'SEARCH'=>1),
                    'TITLE' => array('NAME' => 'TITLE', 'TYPE' => 'TEXT', 'SORT' => 1),
                    'STATUS' => array('NAME' => 'ACTIVE', 'TYPE' => 'CHECK', 'SORT' => 1));

	//$output .= $m -> dsp_getTable($labels, $list, $actions, $page, false, "getProductAction", "TYPE");
    $output .= $m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels, true); //study_list_users($list);
    //$data = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('USERID'),array(),$actions,false, "getProductAction", "TYPE");
	
	return html($output);
}

function study_page_list_profiles($study_prefix){
	$output = '';
	$m = UIManager::getInstance();
	$grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/profiles/studies_profiles/jqGrid/'.$study_prefix);
    $caption=t("Active Profiles per Product Instance")." ".$study_prefix;
	$labels = array(
			'Product Instance'=>array('NAME'=>'STUDY_PREFIX','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),
 			'Profile'=>array('NAME'=>'CODE','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),
 			'Policy'=>array('NAME'=>'POLICY','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),
 			'Scope'=>array('NAME'=>'SCOPE','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1),
 			'Enabled'=>array('NAME'=>'ACTIVE','TYPE'=>'CHECK'),
 	);
	$output .=$m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels, true); //study_list_users($list);
	
	//inserisco legenda
	$output .="<div style='clear:both'></div>";
	$output .=$m->dsp_getLegend("Legend",_study_profile_pages_get_legend());
	return html($output);
} 

function _study_list($jqGrid = false) {
	//$retval = array();
	$select = "SELECT * FROM STUDIES";
    $actions = array();
    $actions[] = array('LABEL' => 'Edit', 'ICON' => 'edit', 'LINK' => url_for('/study/edit/[PREFIX]'));
    $dynamic_actions = array("TYPE" => "getProductAction");
    $data = _data_retrieve($jqGrid, $select, array(), array(), array('PREFIX'), array('ACTIVE'), $actions, false, $dynamic_actions);
	return $data;
}

function _study_load($key, $jqGrid) {
	$retval = array();
	$bind = array();
	$bind['KEY'] = $key;
	$rs = db_query_bind("SELECT * FROM STUDIES WHERE PREFIX = :KEY ", $bind);
	if ($row = db_nextrow($rs)) {
		$retval = $row;
	}
	if($jqGrid){
		_data_parse($retval, sizeof($retval), $jqGrid); //-->Qui gestisco l'output json opportuno, oppure non faccio nulla (e quindi ritorno il retval di questo metodo...
	}
	return $retval;
}

//wizard configuratore studio
function study_wizard($prefix, $step) {
	$m = UIManager::getInstance();
	$m -> set_onLoad("setEasyPie();");
	$m -> setCurrentUrl('/study/wizard/' . $prefix . '/' . $step);
	$output = "";
	if ($step == 1) {
		$output .= "<div data-color=\"#6FB3E0\" data-percent=\"0\" class=\"easy-pie-chart percentage\" style=\"height: 75px; width: 75px; line-height: 74px; color: #6FB3E0;\">
												<span class=\"percent\">0</span>%
											<canvas height=\"50\" width=\"50\"></canvas></div>";
		$output .= t("Profile Management");
		$output .= study_page_profiles($prefix, true);
	} else if ($step == 2) {
		$output .= "<div data-color=\"#6FB3E0\" data-percent=\"25\" class=\"easy-pie-chart percentage\" style=\"height: 75px; width: 75px; line-height: 74px; color: #6FB3E0;\">
												<span class=\"percent\">25</span>%
											<canvas height=\"50\" width=\"50\"></canvas></div>";
		$output .= t("User Authorization Management");
		$output .= study_page_users($prefix, true);
	} else if ($step == 3) {
		$output .= "<div data-color=\"#6FB3E0\" data-percent=\"50\" class=\"easy-pie-chart percentage\" style=\"height: 75px; width: 75px; line-height: 74px; color: #6FB3E0;\">
												<span class=\"percent\">50</span>%
											<canvas height=\"50\" width=\"50\"></canvas></div>";
		$output .= t("Add/remove centers");
		$output .= study_page_centers($prefix, true);
	} else if ($step == 4) {
		$output .= "<div class=\"col-xs-12\"><div data-color=\"#6FB3E0\" data-percent=\"75\" class=\"easy-pie-chart percentage\" style=\"height: 75px; width: 75px; line-height: 74px; color: #6FB3E0;\">
												<span class=\"percent\">75</span>%
											<canvas height=\"50\" width=\"50\"></canvas></div>" . t("Product Instance Builder") . "</div>";
		$output .= study_page_builder($prefix, true);
	}

	return html($output);
}

// Gestione profili
function _study_load_profiles($prefix, $jqGrid = false) {
	$retval = array();
	global $profili;
	$study_info = _study_load($prefix,$jqGrid);
	$retval = $profili[$study_info['TYPE']];

	foreach ($profili [$study_info ['TYPE']] as $k => $p) {
		$retval[$k]['ACTIVE'] = "0";
		$retval[$k]['ACTION'] = ACT_INSERT;
		$retval[$k]['ID'] = 0;
	}
	$bind = array();
	$bind['KEY'] = $prefix;
	$select="SELECT * FROM STUDIES_PROFILES WHERE STUDY_PREFIX = :KEY ";
	$rs = db_query_bind($select, $bind);
	while ($row = db_nextrow($rs)) {
		$retval[$row['CODE']]['ACTIVE'] = $row['ACTIVE'];
		$retval[$row['CODE']]['ACTION'] = ACT_MODIFY;
		$retval[$row['CODE']]['ID'] = $row['ID'];
	}
	if($jqGrid){
		_data_parse($retval, sizeof($retval), $jqGrid); //-->Qui gestisco l'output json opportuno, oppure non faccio nulla (e quindi ritorno il retval di questo metodo...
	}
	return $retval;
}

function study_page_profiles($prefix, $wizard = false) {
	$output = "";
	$list = _study_load_profiles($prefix);
	if ($_POST) {
		if (study_profiles_form_validate()) {
			if (study_profiles_form_submit($list, $prefix)) {
				if (!$wizard) {
					header("location: " . url_for('/study/profiles/' . $prefix));
				} else {
					common_add_message(t("Proceed with the next step: ") . " " . t("User Authorization Management"), INFO);
					header("location: " . url_for('/study/wizard/' . $prefix . '/2'));
				}
				db_close();die();
			} else {
				$output .= t("An error occurred during Product Instance update.");
			}
		}
		// $row = $_POST;
		foreach ($list as $k => $p) {
			if (isset($_POST['ACTIVE-' . $k])) {
				$list[$k]['ACTIVE'] = $_POST['ACTIVE-' . $k];
			}
		}
	}
	$output .= study_profiles_form($list);
	if (!$wizard) {
		return html($output);
	} else {
		return $output;
	}
}

function study_profiles_form($list) {
	$m = UIManager::getInstance();
	$output = "";
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';
	// $output .= ''.$m->dsp_getHiddenField('PREFIX', $row['PREFIX'], false,$row).'';
	foreach ($list as $k => $row) {
		$output .= '' . $m -> dsp_getCheckbox($row['descrizione'], 'ACTIVE-' . $k, '', 'Enabled', false, $row['ACTIVE'], false) . '';
		$output .= '' . $m -> dsp_getHiddenField('ID-' . $k, $row['ID'], false);
	}
	$output .= '' . $m -> dsp_getButtonsSubmitUndo('submit', 'submit-button', 'reset', 'reset-button') . '';
	$output .= '</form>';
	return $output;
}

function study_profiles_form_validate() {
	return true;
}

function study_profiles_form_submit($list, $prefix,$row=false,$verbose=true) {
	$retval = true;
	if(!$row){
		$row = $_POST;
	}

	unset($row['submit-button']);
	unset($row['reset-button']);

	$table = "STUDIES_PROFILES";
	// echo "<pre>";
	// print_r($list);
	// print_r($row);
	// echo "</pre>";
	// die();
	foreach ($list as $k => $p) {
		$row = common_booleanCheckBox($row, 'ACTIVE-' . $k);
		// Lancio le query sul db x ogni riga di profilo
		$action = $p['ACTION'];
		$updrow = array();
		$updrow['STUDY_PREFIX'] = $prefix;
		$updrow['CODE'] = $k;
		$updrow['ACTIVE'] = $row['ACTIVE-' . $k];
		$updrow['POLICY'] = $p['policy'];
		$updrow['SCOPE'] = $p['molteplicita'];
		$updrow['ID'] = $row['ID-' . $k];
		if ($action == ACT_INSERT) {
			$id = "";
			$rs = db_query("SELECT GRUPPIU_SEQUENCE.nextval as NEXT FROM DUAL");
			if ($_row = db_nextrow($rs)) {
				$id = $_row['NEXT'];
			}

			$updrow['ID'] = $id;
		}
		if ($action == ACT_MODIFY) {
			$updrow[OLDPREFIX . 'ID'] = $updrow['ID'];
		}
		if (!db_form_updatedb($table, $updrow, $action, 'ID')) {
			if($verbose){
				common_add_message(t("An error occurred during profile updates, please check current data."), WARNING);
			}
			$retval = false;
		}
		// INSERISCO IN GRUPPIU
		$gruppiu_table = "GRUPPIU";
		$gruppiu_row = array();
		// if ($action == ACT_INSERT){
		// $id_gruppiu = "";
		// $rs = db_query("SELECT GRUPPIU_SEQUENCE.nextval as NEXT FROM DUAL");
		// if ($_row = db_nextrow($rs)){
		// $id_gruppiu= $_row['NEXT'];
		// }
		// }
		$gruppiu_row['ID_GRUPPOU'] = $updrow['ID'];
		$gruppiu_row['ABILITATO'] = $updrow['ACTIVE'];
		$gruppiu_row['ID_TIPO'] = 0;
		$gruppiu_row['ID_VISTA'] = 0;
		if ($action == ACT_MODIFY) {
			$gruppiu_row[OLDPREFIX . 'ID_GRUPPOU'] = $gruppiu_row['ID_GRUPPOU'];
		}
		if (!db_form_updatedb($gruppiu_table, $gruppiu_row, $action, 'ID_GRUPPOU')) {
			if($verbose){
				common_add_message(t("An error occurred during profile updates, please check current data."), WARNING);
			}
			$retval = false;
		}

		// INSERISCO IN ANA_GRUPPIU
		$ana_gruppiu_table = "ANA_GRUPPIU";
		$ana_gruppiu_row = array();
		$ana_gruppiu_row['ID_GRUPPOU'] = $gruppiu_row['ID_GRUPPOU'];
		$ana_gruppiu_row['NOME_GRUPPO'] = $prefix . "_" . $k;
		$ana_gruppiu_row['DESCRIZIONE'] = $k;

		if ($action == ACT_MODIFY) {
			$ana_gruppiu_row[OLDPREFIX . 'ID_GRUPPOU'] = $ana_gruppiu_row['ID_GRUPPOU'];
		}
		if (!db_form_updatedb($ana_gruppiu_table, $ana_gruppiu_row, $action, 'ID_GRUPPOU')) {
			if($verbose){
				common_add_message(t("An error occurred during profile updates, please check current data."), WARNING);
			}
			$retval = false;
		}

		// INSERISCO IN GRUPPIU_GRUPPIF
		$gruppiu_table = "GRUPPIU_GRUPPIF";
		$gruppiu_row = array();

		$bind = array();
		$bind['PREFIX'] = $prefix;
		$id_gruppof = "";
		$_study_info=_study_load($prefix,false);
		$_study_type=$_study_info['TYPE'];
		if($_study_type == 'CLINICAL_TRIAL' || $_study_type == 'LABORATORY_RANGE'){
			$query="SELECT s.DESCR,f.ID_GRUPPOF from STUDIES s, ANA_GRUPPIF f WHERE f.NOME_GRUPPO=case when (s.TYPE='CLINICAL_TRIAL' or s.TYPE='LABORATORY_RANGE') then '/study/' else '' end ||s.DESCR||'/' and s.PREFIX=:PREFIX ";
		}
		else{
			$query="select id_gruppof from ana_gruppif where nome_gruppo like :PREFIX||'%'";
		}
		$rs = db_query_bind($query, $bind);
		if ($_row = db_nextrow($rs)) {
			$id_gruppof = $_row['ID_GRUPPOF'];
		}
		$gruppiu_row['ID_GRUPPOF'] = $id_gruppof;
		$gruppiu_row['ID_GRUPPOU'] = $ana_gruppiu_row['ID_GRUPPOU'];
		$gruppiu_row['ABILITATO'] = $updrow['ACTIVE'];
		$gruppiu_row['UPDATE_ID'] = 0;

		if ($action == ACT_MODIFY) {
			$gruppiu_row[OLDPREFIX . 'ID_GRUPPOU'] = $gruppiu_row['ID_GRUPPOU'];
			$gruppiu_row[OLDPREFIX . 'ID_GRUPPOF'] = $gruppiu_row['ID_GRUPPOF'];
		}
		$pkey = array('ID_GRUPPOU', 'ID_GRUPPOF');
		if (!db_form_updatedb($gruppiu_table, $gruppiu_row, $action, $pkey)) {

			if($verbose){
				common_add_message(t("An error occurred during profile updates, please check current data."), WARNING);
			}
			$retval = false;
		}
		// var_dump($gruppiu_row);
		// die("CIAO!");

	}
	if ($retval) {
		if($verbose){
			common_add_message(t("Action completed."), INFO);
		}
	}
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		return $retval;
	}
}

// FINE Gestione profili

// Gestione utenti globali (associati a profilo globale per lo studio)
function _study_load_profiles_filter($prefix, $scope) {
	$s = array();
	if (strstr($scope,",")) { //VAXMR-297 corretta la chiamata a strstr
		$spl = explode(",", $scope);
		foreach ($spl as $item) {
			$s[] = $item;
		}
	} else {
		$s[] = $scope;
	}
	$list = _study_load_profiles($prefix);
	$retval = array();
	foreach ($list as $k => $p) {
		if (in_array($p['molteplicita'], $s)) {
			$retval[$k] = $p;
			// echo "PROFILE ID: {$p['ID']} - SCOPE: {$p['molteplicita']}";
		}
	}
	// print_r($retval);
	return $retval;
}

function _study_load_users($prefix, $jqGrid = false, $wizard = false) {
	$retval = array();
	$glbProfileIdsSET = "";
	$profiles = _study_load_profiles_filter($prefix, PROFILE_GLOBAL);
	foreach ($profiles as $p) {
		if ($glbProfileIdsSET) {
			$glbProfileIdsSET .= ",";
		}
		$glbProfileIdsSET .= "{$p['ID']}";
	}
	//echo "SETSTRING: $glbProfileIdsSET<br/>";
	$bind = array();
	//$bind['SET'] = $glbProfileIdsSET;
    $fromwhere = " FROM USERS_PROFILES up,utenti_gruppiu ug, STUDIES_PROFILES sp WHERE
	ug.id_gruppou=profile_id
	and ug.userid=up.userid
	and
	PROFILE_ID = ID AND PROFILE_ID IN ($glbProfileIdsSET) and sp.active=1";
    $select = "SELECT up.*,sp.ID,sp.CODE,sp.STUDY_PREFIX, ug.abilitato as ENABLED ".$fromwhere;
    $select_count = "SELECT COUNT(*) AS CONTO ".$fromwhere;
	//echo "<pre>";
    if (!$wizard) {
        $actions = array();
        $actions[] = array('LABEL' => 'Toggle enable', 'ICON' => 'retweet', 'LINK' => url_for('/profiles/study/toggle/' . $prefix . '/[USERID]/[PROFILE_ID]'), 'COLOR' => '#D32646');
    }
    //$data = _data_retrieve($jqGrid, $select, array(), array(), array('PREFIX'), array('ACTIVE'), $actions, false);
    $data = _data_load($select,$select_count,$bind,array("D_PROFILE"=>"CODE", "USERID"=>"up.USERID"));
    //$data = _data_retrieve($jqGrid,$select,$select_count,$bind,array("D_CODE"=>"CODE"),array('USERID','PREFIX','SITE_ID','PROFILE_ID'),array('ACTIVE'),$actions,false);
    $rs = $data['DATASET'];
    $count = $data['COUNT'];
    //Codice custom x gestione record specifica e generazione data array.
    while ($row = db_nextrow($rs)){
        $row['D_PROFILE'] = $profiles[$row['CODE']]['descrizione'];
        if($jqGrid) {
            if ($row['ENABLED']==1){
                $row['ENABLED'] = '<i class="bigger-150 fa fa-check-circle green"></i>';
            }else{
                $row['ENABLED'] = '<i class="bigger-150 fa fa-times-circle red"></i>';
            }
            $row['_ACTIONS_']=_data_actions($actions,$row);
            $row[JQGID] = $row['USERID']."|".$row['ID']."|".$row['CODE'];
            $retval[] = $row;
        }else{
            //$retval[$row['USERID']] = $row;
            $retval[$row['CODE']]= $row; //TODO: Verificare questa chiave! (Riportare uguale anche sopra nell'assegnare JQGID?)
        }
    }
	if($jqGrid){
    	_data_parse($retval, $count, $jqGrid); //-->Qui gestisco l'output json opportuno, oppure non faccio nulla (e quindi ritorno il retval di questo metodo...
	}
	//var_dump($profiles);
	//var_dump($retval);
	//echo "</pre>";
	return $retval;
}

function _study_load_user($prefix, $username, $profileid) {
	$retval = array();
	$glbProfileIdsSET = "";
	$profiles = _study_load_profiles_filter($prefix, PROFILE_GLOBAL);
	foreach ($profiles as $p) {
		if ($glbProfileIdsSET) {
			$glbProfileIdsSET .= ",";
		}
		$glbProfileIdsSET .= "{$p['ID']}";
	}
	//echo "SETSTRING: $glbProfileIdsSET<br/>";
	$bind = array();
	$bind['PREFIX'] = $prefix;
	$bind['USERNAME'] = $username;
	$bind['PROFILEID'] = $profileid;
	$rs = db_query_bind("SELECT up.*, ug.abilitato as enabled FROM USERS_PROFILES up, utenti_gruppiu ug, STUDIES_PROFILES sp WHERE
	ug.ID_GRUPPOU=up.PROFILE_ID
	and up.userid=ug.userid
	and up.PROFILE_ID = ID AND up.PROFILE_ID IN ($glbProfileIdsSET)
	AND STUDY_PREFIX = :PREFIX AND up.PROFILE_ID = :PROFILEID AND up.USERID = :USERNAME", $bind);
	if ($row = db_nextrow($rs)) {
		//$row['D_PROFILE'] = $profiles[$row['CODE']]['descrizione'];
		$retval = $row;
	}
	return $retval;
}

function study_page_users($prefix, $wizard = false) {
	$m = UIManager::getInstance();
	$output = "";
	$list = _study_load_users($prefix, false);
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/study/get_list_users/'.$prefix.'/jqGrid/'.$wizard);
    $caption=t("Existing users");
    $labels = array('USERID' => array('NAME' => 'USERID', 'TYPE' => 'TEXT', 'SORT' => 1),
                    'PROFILE' => array('NAME' => 'D_PROFILE', 'TYPE' => 'TEXT', 'SORT' => 1),
                    'ENABLED' => array('NAME' => 'ENABLED', 'TYPE' => 'CHECK', 'SORT' => 1));
    $actions = !$wizard;
	//$output .= $m -> dsp_getTable($labels, $list, $actions);
    $output .= $m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels, $actions);
	//study_list_users($list);
	$row = array();
	$row['USERID'] = "";
	$row['PROFILE_ID'] = 0;
	if ($_POST) {
		if (study_users_form_validate()) {
			if (study_users_form_submit($prefix, $list)) {
				if (!$wizard) {
					header("location: " . url_for('/study/users/' . $prefix));
				} else {
					common_add_message(t("Proceed with the next step: ") . " " . t("Add/remove centers"), INFO);
					header("location: " . url_for('/study/wizard/' . $prefix . '/3'));
				}

				db_close();die();
			} else {
				$output .= t("An error occurred during Product Instance update.");
			}
		}
		$row = $_POST;

	}
	$output .= study_users_form($row, $prefix);
	if (!$wizard) {
		return html($output);
	} else {
		return $output;
	}
}

function study_users_form($row, $prefix) {
	$m = UIManager::getInstance();
	$output = "";
	$output .= "Add new user / profile";
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';

	$users = array_diff_assoc (_user_list_users(),_study_load_users($prefix)); //CARICO SOLO QUELLI NON ANCORA ASSOCIATI //MODIFICA VMAZZEO/CCONTINO 20-01-2015 non caricava tutti gli utenti
	//$users = _user_list_users(false);
	// Carico tutti gli utenti (multiprofilo può esistere!)

	$optusers = array();
	foreach ($users as $u) {
		$optusers[$u['USERID']] = $u['USERID'];
	}
	$profiles = _study_load_profiles_filter($prefix, PROFILE_GLOBAL);
	$optprofiles = array();
	foreach ($profiles as $k => $p) {
		$optprofiles[$p['ID']] = $p['descrizione'];
	}
	$output .= '' . $m -> dsp_getSelectField('USER ID', 'USERID', '', '', false, $row['USERID'], $optusers, null, true);
	$output .= '' . $m -> dsp_getSelectField('PROFILE', 'PROFILE_ID', '', '', false, $row['PROFILE_ID'], $optprofiles, null, true);
	$output .= '' . $m -> dsp_getCheckbox('STATUS', 'ACTIVE', '', 'Enabled', false, false, $row) . '';
	$output .= '' . $m -> dsp_getButtonsSubmitUndo('submit', 'submit-button', 'reset', 'reset-button') . '';
	$output .= '</form>';
	return $output;
}

function study_users_form_validate() {
	$retval = true;
	$row = $_POST;
	if (!$row['USERID']) {
		common_add_message(t("Please specify the field ") . "'" . t("USER ID") . "'", WARNING);
		$retval = false;
	}
	if (!$row['PROFILE_ID']) {
		common_add_message(t("Please specify the field ") . "'" . t("PROFILE") . "'", WARNING);
		$retval = false;
	}
	return $retval;
}

function study_users_form_submit($prefix, $list,$row=false,$verbose=true) { //VAXMR-297
	$retval = false;
	if(!$row){
		$row = $_POST;
	}

	unset($row['submit-button']);
	unset($row['reset-button']);

	// INSERISCO/MODIFICO IN USERS_STUDIES
	$table = "USERS_STUDIES";
	$action = ACT_INSERT;
	$user_studies_row = array();
	$user_studies_row['USERID'] = $row['USERID'];
	$user_studies_row['STUDY_PREFIX'] = $prefix;
	$user_studies_row['ACTIVE'] = $row['ACTIVE'];
	$user_studies_list = _user_load_studies($row['USERID']);
	foreach ($user_studies_list as $up) {
		if ($up['USERID'] == $user_studies_row['USERID'] && $up['STUDY_PREFIX'] == $user_studies_row['STUDY_PREFIX']) {
			$action = ACT_MODIFY;
			break;
		}
	}
	$user_studies_row = common_booleanCheckBox($user_studies_row, 'ACTIVE');
	// common_add_message(print_r($row,true), INFO);
	$keys = array('USERID', 'STUDY_PREFIX');
	if (db_form_updatedb($table, $user_studies_row, $action, $keys)) {
		if ($action == ACT_INSERT) {
			if($verbose){
				common_add_message(t("user correctly associated to the Product Instance."), INFO);
			}
		}
		// else{
		// common_add_message(t("user correctly associated to the Product Instance"), INFO);
		// }
		$retval = true;
	} else {
		$retval = false;
		return $retval;
	}

	// INSERISCO/MODIFICO IN UTENTI_GRUPPIU
	$table = "UTENTI_GRUPPIU";
	$action = ACT_INSERT;
	$utenti_gruppiu_row = array();
	$utenti_gruppiu_row['USERID'] = $row['USERID'];
	$utenti_gruppiu_row['ID_GRUPPOU'] = $row['PROFILE_ID'];
	$utenti_gruppiu_row['ABILITATO'] = $row['ACTIVE'];
	$utenti_gruppiu_list = _user_load_gruppiu($row['USERID']);
	foreach ($utenti_gruppiu_list as $up) {
		if ($up['USERID'] == $utenti_gruppiu_row['USERID'] && $up['ID_GRUPPOU'] == $utenti_gruppiu_row['ID_GRUPPOU']) {
			$action = ACT_MODIFY;
			break;
		}
	}
	$utenti_gruppiu_row = common_booleanCheckBox($utenti_gruppiu_row, 'ABILITATO');
	// common_add_message(print_r($row,true), INFO);
	$keys = array('USERID', 'ID_GRUPPOU');
	if (db_form_updatedb($table, $utenti_gruppiu_row, $action, $keys)) {
		if ($action == ACT_INSERT) {
			if($verbose){
				common_add_message(t("user correctly associated to the Product Instance."), INFO);
			}
		}
		// else{
		// common_add_message(t("user correctly associated to the Product Instance"), INFO);
		// }
		$retval = true;
	} else {
		$retval = false;
		return $retval;
	}

	$table = "USERS_PROFILES";
	$action = ACT_INSERT;
	foreach ($list as $up) {
		if ($up['USERID'] == $row['USERID'] && $up['PROFILE_ID'] == $row['PROFILE_ID']) {
			$action = ACT_MODIFY;
			break;
		}
	}
	$row = common_booleanCheckBox($row, 'ACTIVE');
	// common_add_message(print_r($row,true), INFO);
	$keys = array('USERID', 'PROFILE_ID');
	if (db_form_updatedb($table, $row, $action, $keys)) {
		if ($action == ACT_INSERT) {
			if($verbose){
				common_add_message(t("New user/profile inserted correctly."), INFO);
			}
		} else {
			if($verbose){
				common_add_message(t("Existing user/profile modified."), INFO);
			}
		}
		$retval = true;
	} else {
		$retval = false;
		return $retval;
	}
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		return $retval;
	}
}

// FINE Gestione utenti globali

// GESTIONE CENTRI
function study_page_centers($prefix, $wizard = false) {
	$m = UIManager::getInstance();
	$output = "";
	$output .= "<p>Center list for the current site: " . $prefix . "</p>";
	$list = _study_load_centers($prefix, false);
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/study/get_list_center/'.$prefix.'/jqGrid/'.$wizard);
    $caption=t("Existing centers");
	$labels = array('CODE' => array('NAME' => 'CODE', 'TYPE' => 'TEXT', 'SORT' => 1),
                    'Product Instance URL' => array('NAME' => 'DESCR', 'TYPE' => 'TEXT', 'SORT' => 1),
                    'ACTIVE' => array('NAME' => 'ACTIVE', 'TYPE' => 'CHECK', 'SORT' => 1));
    //$actions = !$wizard;
	$actions = false;
	//$output .= $m -> dsp_getTable($labels, $list, $actions);
    $output .= $m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels, $actions);
	// study_list_users($list);
	$row = array();
	$row['SITE_ID'] = 0;
	if ($_POST) {
		if (study_centers_form_validate()) {
			if (study_centers_form_submit($prefix, $list)) {
				if (!$wizard) {
					header("location: " . url_for('/study/centers/' . $prefix));
				} else {
					common_add_message(t("Proceed with the next step: ") . " " . t("Add/remove centers"), INFO);
					header("location: " . url_for('/study/wizard/' . $prefix . '/4'));
				}
				db_close();die();
			} else {
				$output .= t("An error occurred during Product Instance update.");
			}
		}
		$row = $_POST;

	}
	$output .= study_centers_form($row, $prefix);
	if (!$wizard) {
		return html($output);
	} else {
		return $output;
	}
}

function _study_load_centers($prefix, $jqGrid = false) {
	// echo "SETSTRING: $glbProfileIdsSET<br/>";
	$bind = array();
	$bind['KEY'] = $prefix;
	// $bind['SET'] = $glbProfileIdsSET;
    $select = "SELECT ss.*,s.CODE,s.DESCR FROM SITES_STUDIES ss,SITES s WHERE ss.SITE_ID=s.ID AND ss.STUDY_PREFIX=:KEY ";
    $ord_override=array();
    $data = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('ID'),array('ACTIVE'),array(),false);
	return $data;
}

function study_centers_form($row, $prefix) {
	$m = UIManager::getInstance();
	$output = "";
	$output .= "<p>Add new / edit center</p>";
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';
	// $output .= ''.$m->dsp_getHiddenField('PREFIX', $row['PREFIX'], false,$row).'';
	$centers = _center_list_centers();
	$optcenters = array();
	foreach ($centers as $c) {
		$optcenters[$c['ID']] = $c['CODE'] . " - " . $c['DESCR'];
	}
	// var_dump($row);
	$output .= '' . $m -> dsp_getSelectField('CENTER', 'SITE_ID', '', '', false, $row['SITE_ID'], $optcenters, null, true);
	$output .= '' . $m -> dsp_getCheckbox('STATUS', 'ACTIVE', '', 'Enabled', false, false, $row) . '';
	$output .= '' . $m -> dsp_getHiddenField('STUDY_PREFIX', $prefix);
	$output .= '' . $m -> dsp_getButtonsSubmitUndo('submit', 'submit-button', 'reset', 'reset-button') . '';
	$output .= '</form>';
	return $output;
}

function study_centers_form_validate() {
	$retval = true;
	$row = $_POST;
	if (!$row['SITE_ID']) {
		common_add_message(t("Please specify the field ") . "'" . t("CENTER") . "'", WARNING);
		$retval = false;
	}
	return $retval;
}

function study_centers_form_submit($prefix, $list) {
	$retval = false;
	$row = $_POST;

	unset($row['submit-button']);
	unset($row['reset-button']);

	$table = "SITES_STUDIES";
	$action = ACT_INSERT;
	foreach ($list as $up) {
		if ($up['SITE_ID'] == $row['SITE_ID'] && $up['STUDY_PREFIX'] == $row['STUDY_PREFIX']) {
			$action = ACT_MODIFY;
			break;
		}
	}
	$row = common_booleanCheckBox($row, 'ACTIVE');
	// common_add_message(print_r($row,true), INFO);
	$keys = array('SITE_ID', 'STUDY_PREFIX');
	if (db_form_updatedb($table, $row, $action, $keys)) {
		if ($action == ACT_INSERT) {
			common_add_message(t("New product instance/center inserted correctly."), INFO);
		} else {
			common_add_message(t("Existing Product Instance/center modified."), INFO);
		}
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

//FINE GESTIONE CENTRI

/*function study_toggle_user($prefix, $username, $profileid) { //VAXMR-297 rinominata in study_profile_toggle_user e spostata in profile.module.php
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
			common_add_message("Error during privilege toggling", ERROR);
			$retval= false;
	}
	//VMAZZEO 15.12.2015: quando aggiorno se un utente è abilitato o meno ad uno studio, devo anche aggiornare USERS_PROFILES! 
	$table = "USERS_PROFILES";
	$upRowUS['USERID'] = $row['USERID'];
	$upRowUS['PROFILE_ID'] = $row['PROFILE_ID'];
	$upRowUS['ACTIVE'] = $upRow['ABILITATO'];
	$action = ACT_MODIFY;
	$keys = array('USERID', 'PROFILE_ID');
	if (!db_form_updatedb($table, $upRowUS, $action, $keys, false)) {
		common_add_message("Error during privilege toggling", ERROR);
		$retval = false;
	}
	if($retval){
		db_commit();
		common_add_message("Privilege $enab", INFO);
	}
	header("location: " . url_for('/profile/manage_profile_per_study/' . $prefix.'/'.$profileid)); //VAXMR-297
	db_close();die();	
	
}*/

//GIT Repository!
function study_page_gitrepo($prefix){
    //global $u;
	$m = UIManager::getInstance();
	$row = _study_load($prefix,false);
	$output = "";
	$output .= "<p>Current GIT STATUS " . $prefix . "</p>";
	
	include_once('Git.php');
	$gitexec = LOCAL_GIT_BIN;
	$gitrepo =  $row['DESCR']."";
	if (preg_match("/\.sisslab05\./i",$_SERVER['SERVER_NAME'])){
		//Posso testare in demo-cro.sisslab05
		$repofolder = "/var/www/XMR/service/html".'/study'."/{$gitrepo}";
		$gitexec = "/usr/bin/git";
	}else if (preg_match("/\.sisslocal\./i",$_SERVER['SERVER_NAME'])){
        //Posso testare in demo-cro.sisslab05
        $repofolder = "C:\\XMR\\service\\html".'\\study'."\\{$gitrepo}";
        $gitexec = "\"C:\\Program Files (x86)\\Git\\cmd\\git.EXE\"";
    }else{
		$repofolder = "/http/servizi/".IDP_NAME."/".SERVICE_FOLDER."/html".'/study'."/{$gitrepo}";
	}
	//echo "$repofolder<br/><br/>{$_SERVER['SERVER_NAME']}";

	$repo = Git::open($repofolder); //Posso prima settare la cartella di repository, perche' esiste gia'. Non ho bisogno del binario GIT.
	$repo->setBinFile($gitexec); //ora setto il binario x usare la classe.
	
	//$output .= $repo->status(true);
	//$output .= "<div style=\"clear:both;\">&nbsp;</div>";
	$farray = $repo->statusArray();
    $toaddvals = array();
    $toaddlabels = array();
    $count = 1;
    foreach ($farray['MOD'] as $f) {
        $toaddvals[$count] = $f;
        $toaddlabels[$count] = "<span style=\"color:orange;\" >MOD: {$f}</span>";
        $count++;
    }
    foreach ($farray['NEW'] as $f) {
        $toaddvals[$count] = $f;
        $toaddlabels[$count] = "<span style=\"color:blue;\" >NEW: {$f}</span>";
        $count++;
    }

    if ($_POST && isset($_POST['SUBMIT'])){
        foreach ($_POST as $k=>$v){
            if (common_beginsWith($k,"toadd_")){
                $idx = str_replace("toadd_","",$k);
                //echo "ADDING {$toaddvals[$idx]}<br/>";
                $repo->add($toaddvals[$idx]);
            }
            //echo "ADDED<br/>";
        }
        $msg = "System commit: date ".date("Y-m-d H:i:s").", user ".$_SERVER['REMOTE_USER'];
        $odir = getcwd();
		if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
		 	chdir($_SERVER ['DOCUMENT_ROOT'] . '/study/'.$row['DESCR']); //Entro nella cartella dello studio
        }
		else if (preg_match("!XMR!",$row['TYPE'])){
			chdir($_SERVER ['DOCUMENT_ROOT'] . '/'.$row['DESCR']); //Entro nella cartella dello studio
		}
        system("chmod g+w -R .");
        system("chgrp devj -R .");
        chdir($odir); //Ripristino la directory di lavoro
        //echo "MSG: {$msg}<br/>";
        //$repo->commit($msg,false);
        //echo "COMMITTED<br/>";
        //$repo->pushSimple();
        //Tento di collegarmi al mio server con l'utenza git in interactive shell...
        clearstatcache();
        //die("STOP");
        CommitLocalFiles($row, $msg);
        echo "PUSHED<br/>";
        //Finisco con redirect a me stesso (senza variabili POST)
        common_add_message("Git COMMIT Done",INFO);
        header("location: ".url_for("/study/gitrepo/{$prefix}")); //{$base_url}/study/gitrepo/{$prefix}");
        db_close();die();
    } elseif ($_POST && isset($_POST['PULL'])) {
        //Gestisco il pull
        PullRemoteFiles($row);
        common_add_message("Git PULL Done",INFO);
        header("location: ".url_for("/study/gitrepo/{$prefix}")); //{$base_url}/study/gitrepo/{$prefix}");
        db_close();die();
    } else {
        $output .= "<p>Files already added:</p>";
        $output .= "<form method=\"post\" action=\"#\" >";
        $count = 1;
        foreach ($farray['ADD'] as $f) {
            $output .= '<div class="form-group">';
            $output .= "<label class=\"col-sm-3 control-label no-padding-right\" for=\"addfile_{$count}\"><span style=\"color:green;\" >{$f}</span></label>";
            $output .= "<div class=\"col-sm-9 \"><input type=\"hidden\" name=\"addfile_{$count}\"></div><br/>";
            $output .= '</div>';
            $count++;
        }
        $output .= "<p>Files to add:</p>";
        foreach ($toaddvals as $idx => $val) {
            $output .= $m->dsp_getCheckbox($toaddlabels[$idx], "toadd_{$idx}", false);
            $output .= "<p>&nbsp;</p>";
        }
        $output .= $m->dsp_getButtonsSubmitUndo("COMMIT", "SUBMIT");
        $output .= $m->dsp_getButtonsSubmitUndo("PULL UPDATES", "PULL");
        $output .= "</form>";
        $output .= "<p>&nbsp;</p>";
        //$output .= print_r($farray,true);

        return html($output);
    }
}

function PullRemoteFiles($row)
{
    //"Pullo" le modifiche remote - connessione al server con utente sissgit
    $prompt = '/(\\$|>)+/'; //Regex prompt pattern (o $ o > e fine linea)
    echo $prompt;
    $gitexec = LOCAL_GIT_BIN;
    set_include_path(SYSTEMBASEURL_LIBRARY . '../phpseclib/phpseclib');
    include_once('Net/SSH2.php');
    //Parto con le mie operazioni
    $sshconn = new Net_SSH2(LOCAL_SSH_SERVER);
    echo "<br/>" . LOCAL_SSH_SERVER . "<br/>";
    if (!$sshconn->login('sissgit', '2NB;ZQ9Y')) {
        common_add_message(t("SSH2 authentication failed!"), ERROR);
        //echo "SSH2 ERROR!<br/>";
    }
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>" . $output . "\n<br/>";
	if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
    	$sshconn->write('cd ' . "/http/servizi/" . IDP_NAME . "/" . SERVICE_FOLDER . "/html/study/{$row['DESCR']}" . "\n"); ///http/servizi/GENIUS/[service]/html/study
	}
	else if (preg_match("!XMR!",$row['TYPE'])){
		$sshconn->write('cd ' . "/http/servizi/" . IDP_NAME . "/" . SERVICE_FOLDER . "/html/{$row['DESCR']}" . "\n"); 
	}
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>" . $output . "\n<br/>";
    //E fare pull
    $sshconn->write("{$gitexec} pull \n");
    $output = $sshconn->read("{$row['DESCR']}>");
    echo "\n<br/>".$output."\n<br/>";
    //E dare permessi di gruppo
    $sshconn->write("chmod g+w -R . \n");
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>".$output."\n<br/>";
    //A questo punto chiudo e mi scollego
    $sshconn->disconnect();
    //Fine dei giochi
}
function CommitLocalFiles($row, $msg, $addall = false)
{
    //Committo i files esistenti sul git - connessione al server con utente sissgit
    $prompt = '/(\\$|>)+/'; //Regex prompt pattern (o $ o > e fine linea)
    echo $prompt;
    $gitexec = LOCAL_GIT_BIN;
    set_include_path(SYSTEMBASEURL_LIBRARY . '../phpseclib/phpseclib');
    include_once('Net/SSH2.php');
    //Parto con le mie operazioni
    $sshconn = new Net_SSH2(LOCAL_SSH_SERVER);
    echo "<br/>" . LOCAL_SSH_SERVER . "<br/>";
    if (!$sshconn->login('sissgit', '2NB;ZQ9Y')) {
        common_add_message(t("SSH2 authentication failed!"), ERROR);
        //echo "SSH2 ERROR!<br/>";
    }
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>" . $output . "\n<br/>";
    $sshconn->write('cd ' . "/http/servizi/" . IDP_NAME . "/" . SERVICE_FOLDER . "/html/study/{$row['DESCR']}" . "\n"); ///http/servizi/GENIUS/[service]/html/study
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>" . $output . "\n<br/>";
    if ($addall) {
        $sshconn->write("{$gitexec} add *\n");
        $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
        echo "\n<br/>" . $output . "\n<br/>";
    }
    //Setting globals (non si sa mai che qualcuno le cambi....)
    //git config --global user.email "you@example.com"
    //git config --global user.name "Your Name"
    //e modalità di push
    //git config --global push.default simple
    $sshconn->write("{$gitexec} config --global user.email '".GIT_EMAIL."'\n");
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>".$output."\n<br/>";
    $sshconn->write("{$gitexec} config --global user.name '".GIT_USER."'\n");
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>".$output."\n<br/>";
    $sshconn->write("{$gitexec} config --global push.default simple\n");
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>".$output."\n<br/>";
    //Ora posso applicare il mio commit
    $sshconn->write("{$gitexec} commit -m '{$msg}' \n");
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>".$output."\n<br/>";
    //E fare push
    $sshconn->write("{$gitexec} push \n");
    $output = $sshconn->read("{$row['DESCR']}>");
    echo "\n<br/>".$output."\n<br/>";
    //E dare permessi di gruppo
    $sshconn->write("chmod g+w -R . \n");
    $output = $sshconn->read($prompt, NET_SSH2_READ_REGEX);
    echo "\n<br/>".$output."\n<br/>";
    //A questo punto chiudo e mi scollego
    $sshconn->disconnect();
    //Fine commit dei files
}

//Parexel EXPORT Functionalities!
function study_page_export($prefix){
	//global $u;
	$m = UIManager::getInstance();
	$row = _study_load($prefix,false);
	$output = "";


	//chiamo l'export del servizio
	header("location: /study/{$row['DESCR']}/index.php?EXPORT=1&ONLYSTUDY=1");
	die();

	//Non uso più il codice di seguito.

	//PAREXEL EXPORT - CSV Generation
	$parexel_export = true;
	if ($parexel_export) {
		//Create export folder (if not exists
		if (!is_dir('export')) {
			if (!mkdir('export', 0777, true)) {
				common_add_message("Cannot create 'export' folder!", ERROR);
			}
		}
		//Write "config_study_crf.csv" file (this file describes form eCRFs)
		//Load all XML forms inside study structure
		//folder "/html/study/{$row['DESCR']}"
		$dir = "{$_SERVER['DOCUMENT_ROOT']}/study/{$row['DESCR']}/xml";
		//var_dump($dir);
		$studyxml = simplexml_load_file("{$dir}/visite_exams.xml");
		//var_dump($studyxml);
		//For each form, retrieve each field and write a line in the CSV file
		$headers_study_crf = "STUDY_REF_KEY," . //key
			"SYSTEM_CRF_REF_KEY," . //mandatory
			"CRF_NAME," . //mandatory
			"CRF_DISPLAY_NAME," . //string
			"STUDY_CRF_REF_KEY," . //key
			"SDV_REQD," . //number
			"MREVIEW_REQD," . //number
			"DREVIEW_REQD," . //number
			"SOURCE_SYSTEM"; //string
		$data_study_crf = "";
		$headers_study_crf_data_item = "STUDY_REF_KEY," . //key
			"STUDY_CRF_DATA_ITEM_REF_KEY," . //key
			"ITEM_REF_KEY," . //,string
			"ITEM_GROUP_REF_KEY," . //string
			"SECONDARY_ITEM_GROUP_REF_KEY," . //string
			"ITEM_NAME," . //string
			"ITEM_GROUP_NAME," . //string
			"QUESTION_ID," . //string
			"QUESTION_NAME,". //string
			"QUESTION_PROMPT,". //string
			"IS_DREVIEW_REQD,". //string
			"IS_SDV_REQD,". //string
			"IS_MREVIEW_REQD,". //string
			"STUDY_CRF_REF_KEY,". //string
			"SYSTEM_CRF_REF_KEY,". //string
			"CRF_NAME,". //string
			"CRF_DISPLAY_NAME,". //string
			"IS_DELETED,". //string
			"SOURCE_SYSTEM"; //string
		$data_study_crf_data_item = "";

		$formFiles = array();
		$formAttrs = array();
		foreach ($studyxml->xpath("//visit") as $visit) {
			foreach ($visit->xpath("exam") as $exam) {
				//var_dump($visit);
				//var_dump($exam);
				//echo "<hr/>";
				//echo "<br/>ATTR: {$exam['xml']}<br/>";
				$key = $visit['number']."-".$exam['number'];
				$formFiles[$key] = $exam['xml'];
				$attrs = array();
				$attrs['CRF_NAME'] = "{$visit['text']} - {$exam['xml']}";
				$attrs['CRF_DISPLAYNAME'] = "{$visit['text']} - {$exam->text}";
				$attrs['CRF_UNIQUEID'] = "{$key}-{$attrs['CRF_NAME']}";
				$formAttrs[$key] = $attrs;
			}
		}
		//die();
		//var_dump($formFiles);
		//die();
		//$filesDir = scandir($dir);
		//var_dump($filesDir);
		foreach ($formFiles as $fKey => $fFile){
			if (file_exists("{$dir}/{$fFile}")){
				$formxml = simplexml_load_file("{$dir}/{$fFile}");
				$data_study_crf .= "\"{$row['PREFIX']}\"," . //key
					"\"{$formAttrs[$fKey]['CRF_UNIQUEID']}\"," . //mandatory
					"\"{$formAttrs[$fKey]['CRF_NAME']}\"," . //mandatory
					"\"{$formAttrs[$fKey]['CRF_DISPLAYNAME']}\"," . //string
					"\"{$formAttrs[$fKey]['CRF_UNIQUEID']}\"," . //key
					"\"0\"," . //number //SDV
					"\"0\"," . //number //MREVIEW
					"\"0\"," . //number //DREVIEW
					"\"SOURCE\"\n"; //string //SOURCESYS
				foreach ($formxml->xpath("//field") as $field){
					//var_dump($field);
					if ($field['var'] && $field['tb']!="no"){
						$data_study_crf_data_item .= "\"{$row['PREFIX']}\"," . //key
							"\"{$field['var']}\"," . //key -> versione CRF + chiave field (con versione)
							"\"{$field['var']}\"," . //,string
							"\"{$fFile}\"," . //string
							"," . //string -> opzionale
							"\"".common_strOneLine($field->txt_value)."\"," . //string
							"\"{$fFile}\"," . //string
							"," . //string -> quesiton opzionali?
							",". //string -> quesiton opzionali?
							",". //string -> quesiton opzionali?
							"0,". //string -> DREVIEW
							"0,". //string  -> SDV
							"0,". //string  -> MREVIEW
							"\"{$formAttrs[$fKey]['CRF_UNIQUEID']}\",". //string
							"\"{$formAttrs[$fKey]['CRF_UNIQUEID']}\",". //string
							"\"{$formAttrs[$fKey]['CRF_NAME']}\",". //string
							"\"{$formAttrs[$fKey]['CRF_DISPLAYNAME']}\",". //string
							"0,". //string -> IS_DELETED
							"\"SOURCE\"\n"; //string
					}
				}
			}else{
				echo "File {$fFile} does not exists!";
			}
		}
		//die();

		$csv_study_crf = $headers_study_crf . "\n" . $data_study_crf;
		$csv_study_crf_data_item = $headers_study_crf_data_item . "\n" . $data_study_crf_data_item;
		//Naming convention: <Gateway>_<Interfacename>_<InterfaceFlavor>_<SrcName>_<Version>_<Timestamp>
		//native_study_na_IMPACT_14.1_20120430T123029.csv
		$tstamp = date("YmdTHis");
		file_put_contents('export/' . $row['PREFIX'] . "_study_crf.csv", $csv_study_crf);
		file_put_contents('export/native_study_crf_na_ACM_1.0_' . $tstamp . '.csv', $csv_study_crf);
		file_put_contents('export/' . $row['PREFIX'] . "_study_crf_data_item.csv", $csv_study_crf_data_item);
		file_put_contents('export/native_study_crf_data_item_na_ACM_1.0_' . $tstamp . '.csv', $csv_study_crf_data_item);
	}

	header("location: " . url_for('/study/list'));
	return html($output);

}


// BUILDER!
function study_page_builder($prefix, $wizard = false) {
    $output = "";
	$m = UIManager::getInstance();
	if (!$wizard) {
		$m -> setCurrentUrl('/study/builder/' . $prefix);
	}
	// include_once "Builder.php";
	if (!$prefix) {
		common_add_message(t("Product Instance prefix mandatory to enable Product Instance builder!"), INFO);
		header("location: " . url_for('/study/list'));
		db_close();die();
	}

	// echo $descr;
	$path = 'builder/XMLValidator/xml';

	// echo "CREATA DIRECTORY ".$path."<br/>";
	if (!is_dir($path)) {
		mkdir($path);
	}
	$path .= '/' . session_id();
	if (!is_dir($path)) {
		mkdir($path);
	}
	$path .= '/' . $prefix;
	// echo $path;
	if ($_POST) {

		if (!is_dir($path)) {
			// echo "<br/> non esiste, creo: ".$path;
			mkdir($path);
			// echo "<br/> creata? ".is_dir($path);
		}

		if (isset($_FILES['userfile']['tmp_name'])) {
			$odm = $_FILES['userfile']['tmp_name'];
			try {
				$my_parser = new ODMtoXMR($odm, $path . "/");
				$my_parser -> parse();
				common_add_message(t("CDISC ODM file correctly imported!"), INFO);
			} catch ( Exception $e ) {
				common_add_message($e -> getMessage(), $e -> getCode());
			}
			$path .= '/odm/';
			if (!is_dir($path)) {
				mkdir($path);
			}
			move_uploaded_file($odm, $path . "/" . $_FILES['userfile']['name']);
			header("location: " . url_for('/study/builder/' . $prefix . '/listImportedFiles'));
			db_close();die();
		}

	}

	$path .= '/';
	$output .= study_page_builder_form($prefix);
	if (!$wizard) {
		return html($output);
	} else {
		return $output;
	}
}

function study_page_builder_form($prefix) {
	$m = UIManager::getInstance();
	$row = _study_load($prefix,false);
	// var_dump($row);
	$descr = $row['DESCR'];
	$output = "";

	/** EDIT CURRENT VISITE_EXAMS*/
	$output .= '<div class="col-xs-3">';
	$output .= '	<div class="widget-box">';
	$output .= '		<div class="widget-header"><h5>' . t("Edit Product Instance Structure") . '</h5></div>
					<div class="widget-body" style="padding:15px">';
	//$output .= '<form class="form-horizontal" role="form" method="get" action="' . url_for('/study/builder') . '/' . $prefix . '/edit/structure/">';
	//$output .= '' . $m -> dsp_getHiddenField('study_root', $descr);
	//$output .= '' . $m -> dsp_getHiddenField('study_prefix', $prefix);
	/**
	 *
	 */
	$output .= '<span>' . t("Click on the button below to edit the Product Instance Structure") . '<br/></span><a href="' . url_for('/study/builder') . '/' . $prefix . '/edit/structure/"><button class="btn btn-info"  style="width:200px; margin-top:5px;" type="button" name="submit-button" id="submit-button"><i class="fa fa-code bigger-110"></i>&nbsp;' . t("Edit") . '</button></a>';
	//$output .= '</form>';

	$output .= '  	</div> <!--widget-body-->
			  	</div> <!--widget-box-->
			  </div> <!--col-xs-3-->';

	/** Import from CDISC ODM file */

	$output .= '<div class="col-xs-3">';
	$output .= '<div class="widget-box">';
	$output .= '<div class="widget-header"><h5>' . t("Import from CDISC ODM file") . '</h5></div>
					<div class="widget-body" style="padding:10px">';
	$output .= '<form enctype="multipart/form-data" class="form-horizontal" role="form" method="post" action="#">
					';
	$output .= '' . $m -> dsp_getFileField('userfile');
	$output .= '' . $m -> dsp_getHiddenField('study_root', $descr);
	$output .= '' . $m -> dsp_getHiddenField('study_prefix', $prefix);
	$output .= '<button class="btn btn-info"  style="width:200px; margin-top:5px;" type="submit" name="submit-button" id="submit-button"><i class="fa fa-upload bigger-110"></i>&nbsp;' . t("Import") . '</button>';
	$output .= '
				</form>';
	$output .= '  </div>  
			  </div>
			  </div>';

	/** Upload XML files */
	$output .= '<div class="col-xs-3">';
	$output .= '<div class="widget-box">';
	$output .= '<div class="widget-header"><h5>' . t("Upload files") . '</h5></div>
					<div class="widget-body" style="padding:10px">';
	$output .= '<form enctype="multipart/form-data" class="form-horizontal" role="form" method="post" action="?/study/builder/' . $prefix . '/upload">
					';
	$multiple = true;
	$output .= '' . $m -> dsp_getFileField('drop_userfile', $multiple);
	$output .= '' . $m -> dsp_getHiddenField('study_root', $descr);
	$output .= '' . $m -> dsp_getHiddenField('study_prefix', $prefix);
	$output .= '<button class="btn btn-info"  style="width:200px; margin-top:5px;" type="submit" name="submit-button" id="submit-button"><i class="fa fa-upload bigger-110"></i>&nbsp;' . t("Upload") . '</button>';
	$output .= '
				</form>';
	$output .= '  </div>
			  </div>
			  </div>';
	return $output;
}

function study_page_builder_upload($prefix) {
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/upload');
	for ($i = 0; $i < count($_FILES['drop_userfile']['name']); $i++) {
		$filesUploaded[] = array("name" => $_FILES['drop_userfile']['name'][$i], "type" => $_FILES['drop_userfile']['type'][$i], "tmp_name" => $_FILES['drop_userfile']['tmp_name'][$i], "error" => $_FILES['drop_userfile']['error'][$i], "size" => $_FILES['drop_userfile']['size'][$i]);
	}
	foreach ($filesUploaded as $key => $value) {
		$name = $value['name'];
		$study_info = _study_load($prefix,false);
		if ($study_info['TYPE'] == 'CLINICAL_TRIAL' || $study_info['TYPE'] == 'LABORATORY_RANGE') {
			$xml_dir = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $study_info['DESCR'] . "/xml/";
		}
		else if (preg_match("!XMR!",$study_info['TYPE'])){
			$xml_dir = $_SERVER['DOCUMENT_ROOT'] . "/" . $study_info['DESCR'] . "/xml/";
		}
		$uploadfile = $xml_dir . "" . $name;
		if (move_uploaded_file($value['tmp_name'], $uploadfile)) {
			common_add_message(t("File " . $name . " imported!"), INFO);
		} else {
			common_add_message("Error during file import: " . $name, ERROR);
		}
	}
	header("location: " . url_for('/study/builder/' . $prefix . '/edit/structure/'));
	db_close();die();
}

if (!function_exists('getLanguage')) {
	function getLanguage() {
		if (!isset($_SESSION['language'])) {
			$_SESSION['language'] = "IT";
		}
		// $_SESSION['language'] = "EN";
		$lang = $_SESSION['language'];
		return $lang;
	}

}

function study_page_builder_validate($prefix) {
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/validate');
	$output = "";
	require_once './builder/XMLValidator/libs/xmlValidator.php';
	require_once './builder/XMLValidator/libs/fileInfo.php';
	$structure = $_POST['structure'];
	$study=_study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$xml_dir = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $_POST['study_root'] . "/xml";
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$xml_dir = $_SERVER['DOCUMENT_ROOT'] . "/" . $_POST['study_root'] . "/xml";
	}
	if (!$structure) {
		$xml_dir = 'builder/XMLValidator/xml/' . session_id() . '/' . $prefix;
	}
	$xsd_dir = 'builder/XMLValidator/xsd';
	// echo "<pre>";
	// print_r();
	// echo "</pre>";
	global $ml;
	$conn = new dbconn();
	// $prefix = $study_prefix;
	$lang = getLanguage();
	$ml = new axmr_ml($prefix, $lang, $conn);

	$validation_result = new xmlValidator($xml_dir . "/" . $_POST['file_xml'], $xsd_dir . "/" . $_POST['file_xsd']);
	$validation_result -> validate();

	/* XML file info */
	$xml_file_info = new fileInfo($xml_dir . "/" . $_POST['file_xml']);

	$output .= '<div class="widget-box left col-xs-6">';
	$output .= '<div class="widget-header"><h5>' . t("XML file info") . '</h5></div>
					<div class="widget-body" style="padding:10px">';
	$eol = "";
	$output .= '<pre>';
	foreach ($xml_file_info->file_info as $key => $value) {
		$output .= "{$eol}{$key}: <b>{$value}</b>";
		$eol = "<br/>";
	}
	$output .= '</pre>
				  </div>
			 </div>';

	/* XSD file info */
	$xsd_file_info = new fileInfo($xsd_dir . "/" . $_POST['file_xsd']);
	$output .= '<div class="widget-box right col-xs-6">';
	$output .= '<div class="widget-header"><h5>' . t("XSD file info") . '</h5></div>
					<div class="widget-body" style="padding:10px">';
	$eol = "";
	$output .= '<pre>';
	foreach ($xsd_file_info->file_info as $key => $value) {
		$output .= "{$eol}{$key}: <b>{$value}</b>";
		$eol = "<br/>";
	}
	$output .= '</pre>
				  </div>
			 </div>';

	$output .= "<div style=\"clear:both\" />";

	/* Esito */
	$output .= $validation_result -> get_validation_result();

	/* Errori */
	if (!$validation_result -> isValid()) {
		common_add_message(t("ERRORS: ") . "<br/>" . $validation_result -> get_html_errors(), null);
	}

	/* PREVIEW */
	$output .= '<div class="widget-box right col-xs-12">';
	$output .= '	<div class="widget-header"><h5>' . t("Form Preview") . '</h5></div>
				<div class="widget-body" style="padding:10px">';
	$output .= $validation_result -> form_preview($xml_dir . "/" . $_POST['file_xml'], $_POST['study_prefix']);
	$output .= '	</div>
			  </div>';
	$output .= "<div style=\"clear:both\" />";

	return html($output);
}
function study_page_builder_new_form($prefix) {
	$output = "";
	$m = UIManager::getInstance();
	$row = _study_load($prefix,false);
	//$descr = $row['DESCR'];
	$study_root = $row['DESCR'];
	$result=false;
	//$has_extension=strpos('.xml',);
	if($_POST['form_type']=='standard'){
		$is_xml_extension=strrpos($_POST['form_file_name'], ".xml");//aggiunge l'esensione se non c'è
	  	if($is_xml_extension==0){
			$_POST['form_file_name'].='.xml';
		}
		$_POST['form_file_name']=str_replace(array(" ",$prefix."_"),array("", ""),trim($_POST['form_file_name']));
		// var_dump($has_extension);
		// var_dump($_POST['form_file_name']);
		//die();
		if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
			$file = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $study_root . "/xml/" . $_POST['form_file_name'];
		}
		else if (preg_match("!XMR!",$row['TYPE'])){
			$file = $_SERVER['DOCUMENT_ROOT'] . "/" . $study_root . "/xml/" . $_POST['form_file_name'];
		}
		if(!study_page_builder_file_exists($study_root,$_POST['form_file_name'],false,$prefix)){
			$originale = SYSTEMBASEURL_LIBRARY . '../xCRF/installer/xml/form_base.xml';
			$result = copy($originale,$file);
			system("chmod g+w {$file}");
			system("chgrp devj {$file}");
			
			$fhandle = fopen($file, "r");
            $content = fread($fhandle, filesize($file));
            
            $content = str_replace("[fname]", $_POST['form_file_name'], $content); //inserisco tutti i campi della form
            fclose($fhandle);
           	$fhandle = fopen($file, "w");
            fwrite($fhandle, $content);
            fclose($fhandle);
			echo json_encode(array("sstatus" => "ok", "file" => $_POST['form_file_name']));
			db_close();die();
			
		}
		else{
			echo json_encode(array("sstatus" => "ko", "error" => t("Sorry, there was an error during form creation!"),"detail"=>t("The form file name already exists!")));
			db_close();die();
		}
	}
	elseif($_POST['form_type']=='main_sub'){
		///////CREO MAIN///////
		$is_xml_extension=strrpos($_POST['form_file_name'], ".xml");//aggiunge l'esensione se non c'è
	  	if($is_xml_extension==0){
			$_POST['form_file_name'].='.xml';
		}
		$_POST['form_file_name']=str_replace(array(" ",$prefix."_"),array("", ""),trim($_POST['form_file_name']));
		if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
			$file_main = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $study_root . "/xml/" . $_POST['form_file_name'];
		}
		else if (preg_match("!XMR!",$row['TYPE'])){
			$file_main = $_SERVER['DOCUMENT_ROOT'] . "/" . $study_root . "/xml/" . $_POST['form_file_name'];
		}
		if(!study_page_builder_file_exists($study_root,$_POST['form_file_name'],false,$prefix)){
				
			$originale = SYSTEMBASEURL_LIBRARY . '../xCRF/installer/xml/main_form_base.xml';
			$result = copy($originale,$file_main); //copio la main originale nel filesystem dello studio
			system("chmod g+w {$file_main}");
			system("chgrp devj {$file_main}");
			$fhandle = fopen($file_main, "r");
            $content = fread($fhandle, filesize($file_main));
            
            $content = str_replace("[fname]", $_POST['fname'], $content); //inserisco tutti i campi della form
            $content = str_replace("[table]", strtoupper(preg_replace("/\W/", "", str_replace(array(" ",$prefix."_"),array("", ""),trim($_POST['table'])))), $content); 
			$content = str_replace("[main_field]", strtoupper(preg_replace("/\W/", "", str_replace(array(" ",$prefix."_"),array("", ""),trim($_POST['main_field'])))), $content); 
			$content = str_replace("[main_field_value]", $_POST['main_field_value'], $content);
			$content = str_replace("[table_sub]", strtoupper(preg_replace("/\W/", "", str_replace(array(" ",$prefix."_"),array("", ""),trim($_POST['table_sub'])))), $content); 
			$content = str_replace("[type]", $_POST['type'], $content);
			$content = str_replace("[main_field_label]", $_POST['main_field_label'], $content);
			$content = str_replace("[main_field_yes_value]", $_POST['main_field_yes_value'], $content);
			$content = str_replace("[main_field_no_value]", $_POST['main_field_no_value'], $content);
			$content = str_replace("[main_field_yes_label]", $_POST['main_field_yes_label'], $content);
			$content = str_replace("[main_field_no_label]", $_POST['main_field_no_label'], $content);
			$content = str_replace("[sub_form_file_name]", $_POST['sub_form_file_name'], $content);
            //echo "<br/>".$content;
            //die();
            fclose($fhandle);
            $fhandle = fopen($file_main, "w");
            fwrite($fhandle, $content);
            fclose($fhandle);
			
			
		}
		else{
			echo json_encode(array("sstatus" => "ko", "error" => t("Sorry, there was an error during form creation!"),"detail"=>t("The main form file name already exists!")));
			db_close();die();
		}
		///////CREO SUB///////
		$is_xml_extension=strrpos($_POST['sub_form_file_name'], ".xml");//aggiunge l'esensione se non c'è
	  	if($is_xml_extension==0){
			$_POST['sub_form_file_name'].='.xml';
		}
		$_POST['sub_form_file_name']=str_replace(array(" ",$prefix."_"),array("", ""),trim($_POST['sub_form_file_name']));
		if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
			$file_sub = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $study_root . "/xml/" . $_POST['sub_form_file_name'];
		}
		else if (preg_match("!XMR!",$row['TYPE'])){
			$file_sub = $_SERVER['DOCUMENT_ROOT'] . "/" . $study_root . "/xml/" . $_POST['sub_form_file_name'];
		}
		if(!study_page_builder_file_exists($study_root,$_POST['sub_form_file_name'],false,$prefix)){
				
			$originale = SYSTEMBASEURL_LIBRARY . '../xCRF/installer/xml/sub_form_base.xml';
			$result = copy($originale,$file_sub); //copio la sub originale nel filesystem dello studio
			system("chmod g+w {$file_sub}");
			system("chgrp devj {$file_sub}");
			
			$fhandle = fopen($file_sub, "r");
            $content = fread($fhandle, filesize($file_sub));
            
            $content = str_replace("[sub_fname]", $_POST['sub_fname'], $content); //inserisco tutti i campi della form
            $content = str_replace("[table_sub]", strtoupper(preg_replace("/\W/", "", str_replace(array(" ",$prefix."_"),array("", ""),trim($_POST['table_sub'])))), $content);
			$content = str_replace("[main_form_file_name]", $_POST['form_file_name'], $content); 
			//echo "<br/>".$content;
            //die();
            fclose($fhandle);
            $fhandle = fopen($file_sub, "w");
            fwrite($fhandle, $content);
            fclose($fhandle);
			echo json_encode(array("sstatus" => "ok", "file" => $_POST['sub_form_file_name']));
			db_close();die();
			
		}
		else{
			system("rm {$file_main}"); //se il file name della sub esiste, allora elimino anche la main
			echo json_encode(array("sstatus" => "ko", "error" => t("Sorry, there was an error during form creation!"),"detail"=>t("The sub form file name already exists!")));
			db_close();die();
		}
	}
	//var_dump($result);
	//die();
	/*if ($result) {
		echo json_encode(array("sstatus" => "ok", "file" => $_POST['sub_form_file_name']));
		fclose($result);
		die();
	}
	else {
		echo json_encode(array("sstatus" => "ok", "file" => $_POST['sub_form_file_name']));
		die();
	}*/
}
function study_page_builder_copy($prefix) {
	//$output = "";
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/listImportedFiles');
	$file = SYSTEMBASEURL_LIBRARY . 'builder/XMLValidator/xml/' . session_id() . '/' . $prefix . "/" . $_POST['file_xml'];
	//$file = $_SERVER ['DOCUMENT_ROOT'] . "/ACM/" . $_POST ['xml_dir'] . "/" . $_POST ['file_xml'];
	$study=_study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$dir = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $_POST['study_root'] . "/xml/" . $_POST['file_xml'];
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$dir = $_SERVER['DOCUMENT_ROOT'] . "/" . $_POST['study_root'] . "/xml/" . $_POST['file_xml'];
	}
	$retval = "";
	//echo "<b>" . $file . " " . $dir . "</b>";
	//die();
	$result = copy($file, $dir);
	if ($result) {
		$link_to_study_structure = "<br/><a href=\"" . url_for('/study/builder/' . $m -> getCurrentUrl(3)) . "/edit/structure\"><i class=\"fa fa-indent bigger-110\"></i>&nbsp;" . t("Go to Edit product instance structure") . "</a>";
		common_add_message(t("SUCCESS! The file was correctly copied in the product instance structure")." ".$link_to_study_structure, INFO);
	} else {
		common_add_message(t("ERROR! There was an error during the copy "), ERROR);
	}
	// $output.=print_r($_POST);
	header("location: " . url_for('/study/builder/' . $prefix . '/listImportedFiles/'));
	db_close();die();
	// return html($output);
}

function study_page_builder_file_exists($study_root = false, $file_xml = false, $ajaxCall = true,$prefix) {

	$output = "";
	$m = UIManager::getInstance();
	$study=_study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$file = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $study_root . "/xml/" . $file_xml;
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$file = $_SERVER['DOCUMENT_ROOT'] . "/" . $study_root . "/xml/" . $file_xml;
	}
	//echo file_exists($file);
	//echo $file;
	if (file_exists($file)) {
		if (isAjax() && $ajaxCall) {
			echo json_encode(array("sstatus" => "exists", "file" => $file));
			db_close();die();
		} else {
			return true;
		}
	} else {
		if (isAjax() && $ajaxCall) {
			echo json_encode(array("sstatus" => "not_exists", "file" => $file));
			db_close();die();
		} else {
			return false;
		}

	}
}

function study_page_builder_saveForm($prefix) {
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/saveForm');
	//var_dump($_POST);
	$study=_study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$file = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $_POST['study_root'] . "/xml/" . $_POST['file_xml'];
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$file = $_SERVER['DOCUMENT_ROOT'] . "/" . $_POST['study_root'] . "/xml/" . $_POST['file_xml'];
	}
	//var_dump($dir);
	$saved=file_put_contents($file, $_POST['code']);
	if (file_put_contents($file, $_POST['code']) === false) {
		common_add_message(t("ERROR! There was an error during the saving "), ERROR);
	} else {
		common_add_message(t("SUCCESS! The file was correctly saved"), INFO);

	}
	header("location: " . url_for('/study/builder/' . $prefix . '/editForm/'.$_POST['file_xml']));
	db_close();die();
}

function study_page_builder_saveVisiteExam($prefix) {
	$row = _study_load($prefix,false);
	$study_root = $row['DESCR'];
	$output = "";
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/saveVisiteExam');
	$struttura = $_POST['info'];
	$dom = new DomDocument('1.0', 'utf-8');
	$g = -1;
	$v = -1;
	$e = -1;
	$visit_exam = $dom -> createElement('visit_exam');
	$visit_exam -> preserveWhiteSpace = false;
	$visit_exam -> formatOutput = true;
	$dom -> appendChild($visit_exam);
	//le seguenti variabili servono a controllare che esistano uno ed uno solo numero di visita e di esame
	$v_number_count = array();
	$v_number_duplicated = "";
	$e_number_count = array();
	$e_number_duplicated = "";
	//le seguenti variabili servono a controllare che le main sub siano tutte associate e che ogni sub abbia come numero d'esame il numero della main +1
	$main_sub_ass=array();
	$isValid = true;
	foreach ($struttura as $key => $value) {
		if ($value['type'] == 'G') {
			$g++;
			$group[$g] = $dom -> createElement('group');
			$group[$g] -> setAttribute('text', $value['title']);
			$visit_exam -> appendChild($group[$g]);
		} elseif ($value['type'] == 'V') {
			$v++;
			$visit[$v] = $dom -> createElement('visit');
			$visit[$v] -> setAttribute('text', $value['title']);
			foreach (json_decode($value['attributes']) as $nomeAttr => $valAttr) {
				$visit[$v] -> setAttribute($nomeAttr, $valAttr);
				if ($nomeAttr == 'number') {
					$v_number_count[$valAttr]++;
					if ($v_number_count[$valAttr] > 1) {
						common_add_message(t("Duplicated Visit Number attribute in Visit element!") . "<br/>Visit number: " . $valAttr . " (" . $visit[$v] -> getAttribute("text") . ")", ERROR);
						$isValid = false;

					}
				}
			}
			$group[$g] -> appendChild($visit[$v]);
		} elseif ($value['type'] == 'E') {
			$e++;
			$exam[$e] = $dom -> createElement('exam');
			//$exam[$e] -> setAttribute('text', $value['title']);
			$title="";
			foreach (json_decode($value['attributes']) as $nomeAttr => $valAttr) {
				if ($nomeAttr == 'text') {
					$title=$valAttr;
				}
				else{
					if($valAttr=="on"){ //sostituisco al valore "on" del checkbox il valore yes che si aspetta l'xml
						$valAttr="yes";
					}
					$exam[$e] -> setAttribute($nomeAttr, $valAttr);
				}
				if ($nomeAttr == 'number') {
					$e_number_count[$v][$valAttr]++;
					if ($e_number_count[$v][$valAttr] > 1) {
						common_add_message(t("Duplicated Exam Number attribute in Exam element!") . "<br/>Exam number: " . $valAttr . " (" . $value['title'] . ") - Visit : " . $visit[$v] -> getAttribute("text"), ERROR);
						$isValid = false;

					}
				}
				if ($nomeAttr == 'xml') {

					if (!study_page_builder_file_exists($study_root, $valAttr, false,$prefix)) {
						common_add_message(t("File not found in \"xml\" attribute in Exam element") . "<br/>XML file: " . $valAttr . " - Exam: " . $value['title'], ERROR);
						$isValid = false;
					}
				}
				
			}
			$my_value['attributes']=(array)json_decode($value['attributes']);
			if($my_value['attributes']['main']=='yes'){
				$main_sub_ass[$my_value['attributes']['xml']]['number']=$my_value['attributes']['number']; //metto il numero di esame
				$main_sub_ass[$my_value['attributes']['xml']]['index']=$e; //e l'indice (per controllare che siano consecutivi)
			}
			if($my_value['attributes']['sub']=='yes'){
				// echo "<pre>";	
				// print_r($main_sub_ass);
				// print_r($e);
				// echo "</pre>";
				
				if( array_key_exists($my_value['attributes']['main_form_file_name'], $main_sub_ass)){
					// echo "<pre><b>controllo indici</b><br/>";
					 // print_r(($main_sub_ass[$my_value['attributes']['main_form_file_name']]));
					 // echo "<br/>";
					 // print_r($e);
					 // echo "<br/>";
					 // print_r($my_value['attributes']['number']);
					 // echo "</pre>";
					if((($main_sub_ass[$my_value['attributes']['main_form_file_name']]['number']+1) == $my_value['attributes']['number']) && (($main_sub_ass[$my_value['attributes']['main_form_file_name']]['index']+1) == $e )){
						unset($main_sub_ass[$my_value['attributes']['main_form_file_name']]);
					}
					elseif(($main_sub_ass[$my_value['attributes']['main_form_file_name']]['number']+1) != $my_value['attributes']['number']){
						common_add_message(t("Sub form must be have exam number equal to main exam number +1 ") . "<br/>Exam number: " . $my_value['attributes']['number'] . " should be " . ( $main_sub_ass[$my_value['attributes']['main_form_file_name']]['number'] +1 ) . "  - Exam: " . $value['title'], ERROR);
						$isValid = false;
					}
					elseif(($main_sub_ass[$my_value['attributes']['main_form_file_name']]['index']+1) != $e ){
						common_add_message(t("Sub form must be dropped just next to its main form") . "<br/>Exam form: ". $value['title'] . " after " . $my_value['attributes']['main_form_file_name'], ERROR);
						$isValid = false;
					}
					
				}
				else{
					common_add_message(t("There is no sub/main association for this Exam ") . "<br/>XML file: " . $my_value['attributes']['xml'] . " - Exam: " . $value['title'], ERROR);
					$isValid = false;
				}
			}
			if (_verifCDATA($value['title'])) {
				$funz = 'createCDATASection';
			} else {
				$funz = 'createTextNode';
			}
			$text = $dom -> createElement('text');
			if($title!=""){
				$text -> appendChild($dom -> $funz($title));	
			}
			else{
				$text -> appendChild($dom -> $funz($value['title']));
			}
			$exam[$e] -> appendChild($text);
			$visit[$v] -> appendChild($exam[$e]);
		}
	}
	if(!empty($main_sub_ass)){
		$isValid=false;
		common_add_message(t("Not all main/sub forms association were dropped in the visit structure") . "<br/>", ERROR);
	}
	if ($isValid) {
		$visite_exam_xml = $dom -> saveXML();
		$xsd_dir = 'builder/XMLValidator/xsd';
		libxml_use_internal_errors(true);
		$isValid = $dom -> schemaValidate($xsd_dir . "/visite_exams.xsd");
		$errors = libxml_get_errors();
		foreach ($errors as $error) {
			common_add_message(t("Error level") . " " . $error -> level . " - " . t("line") . " " . $error -> line . " " . t(" column") . " " . $error -> column . " - " . t("Message: ") . " " . $error -> message, ERROR);
		}
	}
	if ($isValid) {
		if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
			$file = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $study_root . "/xml/visite_exams.xml";
		}
		else if (preg_match("!XMR!",$row['TYPE'])){
			$file = $_SERVER['DOCUMENT_ROOT'] . "/" . $study_root . "/xml/visite_exams.xml";
		}
		if (file_put_contents($file, $visite_exam_xml) == true) {
			system("chmod g+w -R {$file}");
            system("chgrp devj -R {$file}");
			//if ($isValid) {
				common_add_message(t("SUCCESS! The file was correctly saved in the product instance structure"), INFO);
			/*} else { NON HA SENSO SALVARE SE NON E' VALIDO!
				common_add_message(t("The file was correctly saved in the Product Instance structure but it contains some errors"), WARNING);
			}*/
		} else {
			common_add_message(t("ERROR! The file is valid but there was an error during the saving "), ERROR);
			$isValid=false;
		}
	}
	if ($isValid) {
		echo json_encode(array("sstatus" => "valid", "messages" => common_print_messages()));
	} else {
		echo json_encode(array("sstatus" => "not_valid", "messages" => common_print_messages()));
	}
	db_close();die();

}

function _verifCDATA($data) {
	$needsCDATA = (strpos($data, '[') !== false || strpos($data, ']') !== false || strpos($data, '<') !== false || strpos($data, '>') !== false || strpos($data, '&') !== false);
	return $needsCDATA;
}

function study_page_builder_editForm($prefix,$form) {
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/validate');
	$m = UIManager::getInstance();
	
	$row = _study_load($prefix,false);
	$descr = $row['DESCR'];
	$study_root = $row['DESCR'];
	
	$m -> set_onLoad(" var editor=CodeMirror.fromTextArea(document.getElementById('code'), {mode: 'xml',lineNumbers: true /*, extraKeys: {'<': completeAfter,
          '/': completeIfAfterLt,
          ' ': completeIfInTag,
          '=': completeIfInTag,
          'Ctrl-Space': function(cm) {
            CodeMirror.showHint(cm, CodeMirror.hint.xml, {schemaInfo: tags});
          }
        }*/
		});
			CodeMirror.commands['selectAll'](editor);
			var range = getSelectedRange(editor);
			editor.autoFormatRange(range.from, range.to); 
			editor.setCursor(1);");
	$output = "";
	
	require_once './builder/XMLValidator/libs/xmlValidator.php';
	
	require_once './builder/XMLValidator/libs/fileInfo.php';
	
	$fileName = $form;
	if ($row['TYPE'] == 'CLINICAL_TRIAL' || $row['TYPE'] == 'LABORATORY_RANGE') {
		$xml_dir = $_SERVER['DOCUMENT_ROOT'] . "/study/" . $study_root . "/xml";
	}
	else if (preg_match("!XMR!",$row['TYPE'])){
		$xml_dir = $_SERVER['DOCUMENT_ROOT'] . "/" . $study_root . "/xml";
	}
	$output .= "<form id=\"saveForm\" class=\"form-horizontal left\" name=\"validation\" action=\"" . url_for('/study/builder') . "/" . $prefix . "/saveForm\" method=\"POST\">";

	$form = $xml_dir . '/' . $fileName;
	// 	ini_set('display_errors',ALL);
	$form_code = "";
	if (file_exists($form)) {
		$form_code = file_get_contents($form);
		//echo htmlspecialchars($form_code);

	}
	$output .= "<div style='float:left'><h3>" . t("Editing") . " " . $fileName . "</h3></div>";
	$output .= "<div style='float:right'><button class=\"btn btn-info\" type=\"submit\" name=\"submit-button\" id=\"submit-button\"><i class=\"fa fa-disk bigger-110\"></i>&nbsp;" . t("Save form") . "</button>";
	$output .= "&nbsp;<button class=\"btn btn-info\"  type=\"button\" onclick=\"window.location='".url_for('/study/builder') .'/'.$prefix.'/buildForm/'.$fileName."'\" name=\"submit-button\" id=\"submit-button\">" . t("Build Form") . "</button></div>";
	$output .= "<div style='clear:both'></div>";
	//$output .='<a href="'. url_for('/study/builder') .'/'.$prefix.'/buildForm/'.$fileName.'" class="blue"><i class="icon-pencil bigger-110"></i></a>';
	$output .= "<pre>";
	$output .= "<textarea cols=\"100\"  form=\"saveForm\" id=\"code\" name=\"code\">";
	$output .= htmlspecialchars($form_code);
	// $output .= ''.$m->dsp_getButtonsSubmitUndo('<i class=\"fa fa-thumbs-up\"></i> validate','submit-button',null,null,"").'';
	$output .= "</textarea>";
	$output .= "</pre>";
	$output .= '' . $m -> dsp_getHiddenField('xml_content', " ");
	$output .= '' . $m -> dsp_getHiddenField('xsd_form_attributes', " ");
	//TODO: inserire contenuto ottenuto da _getAttributesFromXSD('form.xsd') per autocompletamento codice codemirror
	$output .= '' . $m -> dsp_getHiddenField('file_xml', $fileName);
	$output .= '' . $m -> dsp_getHiddenField('study_root', $descr);
	$output .= '' . $m -> dsp_getHiddenField('study_prefix', $prefix);
	//$output .= '' . $m->dsp_getButtonsSubmitUndo ( 'submit', 'submit-button', 'reset', 'reset-button' ) . '';
	$output .= '</form>';
	return html($output);

}

function study_page_builder_listImportedFiles($prefix) {
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/listImportedFiles');
	$output = "";
	$study = _study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$dir = $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] . '/xml/';
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$dir = $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] . '/xml/';
	}
	$xml_dir = 'builder/XMLValidator/xml/' . session_id() . '/' . $prefix;
	$output .= '<div class="row">';
	$output .= "<div style='float:left'><h6>" . t("File list imported during current session") . " " . $fileName . "</h6></div>";
	$output .= "</div>";
	$listImportedFiles = true;
	$output .= _formListViewer($xml_dir, $prefix, $listImportedFiles);
	$output .= '</div>';
	return html($output);
}

function study_editor($prefix, $item, $id = null) {
	$m = UIManager::getInstance();
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/edit/' . $item . '/' . $id);
	$output = "";
	$study = _study_load($prefix,false);
	if ($item == 'structure') {
		if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
			$dir = $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] . '/xml/';
		}
		else if (preg_match("!XMR!",$study['TYPE'])){
			$dir = $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] . '/xml/';
		}
		$visite_exams = $dir . 'visite_exams.xml';
		$output .= '<div class="row">';
		$output .= _visiteExamViewer($visite_exams, $prefix);
		$output .= _formListViewer($dir, $prefix);
		$output .= '</div>';
	}
	return html($output);
}

function _visiteExamViewer($visite_exams, $prefix) {
	$m = UIManager::getInstance();

	$m -> set_onLoad("setNestable('study_structure',3,false,true,true);");
	$visite_exams_dom = simplexml_load_file($visite_exams);
	$output = $m -> dsp_buttonJs("SAVE", "visiteExamSave('{$prefix}');");
	$output .= '<div class="col-sm-8">';
	//$output .='VALIDATE STUDY STRUCTURE '.xmlValidateForm("visite_exams.xml",$prefix);
	$output .= '<div class="dd" id="study_structure">';
	$output .= '<ol class="dd-list">';
	$g = 0;
	$v = 0;
	$e = 0;
	foreach ($visite_exams_dom->group as $id_group => $group) {
		$output .= _getLista('G', $g++, $group -> attributes() -> text, array());
		$output .= '<ol class="dd-list">';
		foreach ($group as $id_visit => $visit) {
			$output .= _getLista('V', $visit -> attributes() -> number, $visit -> attributes() -> text, $visit -> attributes());
			$output .= '<ol class="dd-list">';
			foreach ($visit as $id_exam => $exam) {
				if ($exam) {
					$output .= _getLista('E', $exam->attributes() -> number, $exam -> text, $exam -> attributes());
					$output .= '</li>';

				}
			}
			$output .= '</ol>';
			$output .= '</li>';
		}
		$output .= '</ol>';
		$output .= '</li>';
	}
	$output .= '</ol>';
	$output .= '</div>';
	$output .= '</div>';

	return $output;
}

function _formListViewer($dir, $prefix, $listImportedFiles = false) {
	$output = "";
	$m = UIManager::getInstance();
	//$listImportedFiles mi dice se sto listando i file dello studio o quelli temporanei importati,
	//in questo caso visualizzo soltanto il bottone di copia nello studio
	if (!$listImportedFiles) {

		$m -> set_onLoad("$('.dd-handle a').on('mousedown', function(e){e.stopPropagation();});");

		//INSERISCI NUOVO GRUPPO
		$m -> set_onLoad("setNestable('new_group',1,true,false,false);");
		$output .= '<div class="col-sm-4">';
		$output .= '<div class="dd" id="new_group">';
		$output .= '<ol class="dd-list">';
		$output .= _getLista('G', "New_Group", t("New Group"), null, null, false);
		$output .= "</li>";
		$output .= '</ol>';
		$output .= '</div>';
		$output .= '</div>';

		//INSERISCI NUOVA VISITA
		$m -> set_onLoad("setNestable('new_visit',2,true,false,false);");
		$output .= '<div class="col-sm-4">';
		$output .= '<div class="dd" id="new_visit">';
		$output .= '<ol class="dd-list">';
		$output .= _getLista('V', "New_Visit", t("New Visit"), null, null, false);
		$output .= "</li>";
		$output .= '</ol>';
		$output .= '</div>';
		$output .= '</div>';
		
		$m -> set_onLoad("setNestable('new_form',0,false,false,false);");
		$output .= '<div class="col-sm-4">';
		$output .= '<div class="dd" id="new_form">';
		$output .= '<ol class="dd-list">';
		
		$buttons = '<div class="pull-right action-buttons">
										<span style="float:right;">	';
		$buttons .= xmlEditForm("new_form.xml", $prefix);
		$buttons .= '		</span>
	  				</div>';
		$output .= _getLista('E', "New_Form", t("New Form"), null, $buttons, false,true);
		$output .= "</li>";
		$output .= '</ol>';
		$output .= '</div>';
		$output .= '</div>';

		//LISTA FORM
		$m -> set_onLoad("setNestable('xml_list',3,true,false,false);");
		$output .= '<div class="col-sm-4">';
		$output .= '<div class="dd" id="xml_list">';

	}
	$output .= '<ol class="dd-list">';
	$study = _study_load($prefix,false);
	if (is_dir($dir)) {
		//$output .= '<div class="widget-box">';
		//$output .= '<div class="widget-header"><h5>Latest generated/uploaded forms</h5></div>
		//			 	<div class="widget-body" style="padding:10px">';
		//$divider = "";
		if ($handle = opendir($dir)) {

			while (false !== ($file = readdir($handle))) { //CARICO CONTENUTO DELLA DIRECTORY
				if(!is_dir($dir . "/" . $file) && $file != "." && $file != ".." && preg_match("/\.xml/i", $file) && !preg_match("/form_base/i", $file) && !preg_match("/equery_list_/i", $file) && !preg_match("/home_/i", $file) && !preg_match("/patients_list/i", $file) && !preg_match("/search_/i", $file) && (!preg_match("/visite_exams/i", $file)) || (preg_match("/visite_exams/i", $file) && $listImportedFiles)){
					$dirFiles[]=$file;	
				}
			}
			closedir($handle);
			sort($dirFiles); // ORDINO ALFABETICAMENTE
			foreach($dirFiles as $file)
			{
					$dom = new DOMDocument();
					$dom -> load($dir . $file);
					$output .= $divider;
					$text = $file;
					/*
					 * $output.='<div class="widget-box right col-xs-12">';
					 //$output.='	<div class="widget-header"><h5>'.t("Copy in study structure").'</h5></div>
					 //			<div class="widget-body" style="padding:10px">';
					 $output .= '<form class="form-horizontal" role="form" method="post" action="' . url_for('/study/builder') . "/" . $prefix . "/copy" .'">';
					 //$output .= ''.$m->dsp_getSelectField('CENTER', 'SITE_ID', '', '', false, $row['SITE_ID'], $optcenters,null,true);
					 //$output .= ''.$m->dsp_getCheckbox('STATUS', 'ACTIVE', '', 'Enabled', false, false, $row).'';
					 $output .= ''.$m->dsp_getHiddenField('study_root',$_POST['study_root']);
					 $output .= ''.$m->dsp_getHiddenField('study_prefix', $_POST['study_prefix']);
					 $output .= ''.$m->dsp_getHiddenField('file_xml', $_POST['file_xml']);
					 $output .= ''.$m->dsp_getHiddenField('xml_dir', $xml_dir);
					 $output .= ''.$m->dsp_getButtonsSubmitUndo('<i class=\"fa fa-thumbs-up\"></i> Copy in study structure','submit-button',null,null,"col-sm-5").'';
					 $output .= '</form>';
					 //$output.='	</div>
					 //		  </div>';
					 * */
					$buttons = '<div class="pull-right action-buttons">
										<span style="float:right;">	';
					$buttons .= xmlCopyInStructureForm($file, $prefix);
					$buttons .= '		</span>
									</div>';
					if (!$listImportedFiles) {

						$buttons = '<div class="pull-right action-buttons">
										<span style="float:right;">
								 ';
						$buttons .= xmlValidateForm($file, $prefix);
						$buttons .= '		</span>
								    </div>
									<div class="pull-right action-buttons">
										<span style="float:right;">	
											<a class="blue" href="download.php?file=' . $file . "&study_root=" . $study['DESCR'] . '"><i class="fa fa-download bigger-130"></i></a>
										</span>
									</div>
									<div class="pull-right action-buttons">
										<span style="float:right;">	';
						$buttons .= xmlEditForm($file, $prefix);
						$buttons .= '		</span>
									</div>';
					}
					$form_dom = simplexml_load_file($dir . "/" . $file);
					$form_attributes=array();
					$form_attributes = (array)$form_dom -> attributes();
					$item=array();
					if($form_attributes['@attributes']['main_field']){
						$item['@attributes']["main"]="yes";
						$item['@attributes']["mandatory"]="yes";
						$item['@attributes']['sub_form_file_name']=$form_attributes['@attributes']['sub_form_file_name'];
					}
					if($form_attributes['@attributes']['main_form_file_name']){
						$item['@attributes']["mandatory"]="yes";
						$item['@attributes']["sub"]="yes";
						$item['@attributes']["default"]="yes";
						$item['@attributes']["mainsub"]="yes";
						$item['@attributes']["trash"]="yes";
						$item['@attributes']["all_in"]="yes";
						$item['@attributes']["progr"]="yes";
						$item['@attributes']['main_form_file_name']=$form_attributes['@attributes']['main_form_file_name'];
					}
					$output .= _getLista('E', $file, $text, $item, $buttons, false);
					//TODO: tofix occhio che getLista non chiude <li> per ragioni di annidamento, quindi mettere la chiusura dopo averla chiamata!
					$divider = "</li>";
				
			}
			
		}
	}
	$output .= '</ol>';
	if (!$listImportedFiles) {
		$output .= '</div>';
		$output .= '</div>';
	}

	return $output;
}

function _getLista($type, $id, $text, $item, $buttons = "", $show_attributes_button = true,$not_draggable = false) {
	$m = UIManager::getInstance();
	$m -> set_onLoad("$('[data-rel=tooltip]').tooltip();");
	switch ($type) {
		case 'E' :
			$class = 'item-orange';
			break;
		case 'V' :
			$class = 'item-blue2';
			break;
		case 'G' :
			$class = 'item-red';
			break;
		default :
			$class = 'item-green';
			break;
	}
	$class_handler="dd-handle";
	if($not_draggable){
		$class_handler="dd-nodrag";
	}
	$output = '<li data-id="' . $type . '_' . $id . '" class="dd-item ' . $class . '">';
	$output .= '<div class="'.$class_handler.'" id="handler_' . $type . '_' . $id . '">';

	$output .= '<span class="structName">' . $text . '</span>';

	$attributes_button = "";
	if (!$show_attributes_button) {
		$attributes_button = 'style="display:none"';
	}

	if ($buttons != "") {
		$output .= ' ' . $buttons;
	}

	$output .= '	<div class="pull-right action-buttons" ' . $attributes_button . ' >';
	//if($type!='G'){

	$item = (array)$item;
	$item = $item['@attributes'];

	$veAttr = _getAttributesFromXSD('builder/XMLValidator/xsd/visite_exams.xsd');

	$box_message = "<div>";
	$box_message .='<form class="form-horizontal">';

	$box_message .= '' . $m -> dsp_getTextField("text", "text", '', '', false, $text, '', true) . '';
	
	foreach ($item as $key => $val) {
		//$box_message.= '' . $m->dsp_getTextField ( $key, $key, '', '', false, $val, '', true ) . '';
		$fieldList[] = $key;
	}
	//var_dump($fieldList);
	
	foreach ($veAttr[$type] as $idField => $fieldType) {
		$fieldTypeArr = (array)$fieldType;
		// echo "<pre>";
		// print_r($item);
		// echo "</pre>";
		/*if (in_array($fieldTypeArr[0], $fieldList)) {
		 $val = trim($item[$fieldTypeArr[0]]);
		 } else {
		 $val = '';
		 }*/
		$val = $item[$fieldTypeArr[0]];
		$mandatory = false;
		$mandatories = array('text', 'number', 'xml');
		$main_form_hidden=array("main", "sub","mainsub","progr","sub_form_file_name","main_form_file_name","all_in","progr");
		$checkbox=array("mandatory","default","trash");
		if (in_array($fieldTypeArr[0], $mandatories)) {
			$mandatory = true;
			//echo "<pre>";
			//print_r($fieldTypeArr);
			//echo $mandatory;
			//echo "</pre>";
		}
		if(in_array($fieldTypeArr[0], $main_form_hidden)){
			$box_message .= '' . $m -> dsp_getHiddenField(trim($fieldTypeArr[0]), $val) . '';
		}
		elseif(in_array($fieldTypeArr[0], $checkbox)){
			if( $fieldTypeArr[0]!='trash' || ($fieldTypeArr[0]=='trash' && $item['sub']=="yes") ){
				$box_message .= '' . $m -> dsp_getCheckbox(trim($fieldTypeArr[0]), trim($fieldTypeArr[0]), '', '', false, $val) . '';
			}
		}
		else{
			// echo "<pre>";
			// print_r($item);
			// echo "</pre>";
			if( $fieldTypeArr[0]!='max_all_in' || ($fieldTypeArr[0]=='max_all_in' && $item['sub']=="yes") ){
				$box_message .= '' . $m -> dsp_getTextField(trim($fieldTypeArr[0]), trim($fieldTypeArr[0]), '', '', false, $val, '', $mandatory) . '';
			}
		}
		
	};
	$box_message .= '</form>';
	$box_message .= '</div>';
	$box_message = str_replace("\"", "'", $box_message);
	$box_message = str_replace("'", "\\'", $box_message);

	$output .= '<a id="a_' . $id . '" href="#" onclick="visiteExamEdit(\'' . $type . '\',this,\'' . $box_message . '\');" class="blue"><i class="fa fa-list"></i></a>';
	$row = _study_load($m -> getCurrentUrl(3));
	$study_root = $row['DESCR'];
	if ($type == 'E' && $item['xml'] && $item['xml'] != '' && !study_page_builder_file_exists($study_root, $item['xml'], false,$row['PREFIX'])) {
		$output .= '<a href="#" class="tooltip-error" data-placement="top" data-rel="tooltip" data-original-title="file not found!"><i class="fa fa-exclamation-triangle red"></i></a>';
	}

	$json = json_encode($item);
	//     	var_dump($json);
	//     	echo "<br/>";
	if ($json == "null") {
		$json = "{}";
	}
	$output .= "<input id=\"H_" . $type . '_' . $id . "\" type=\"hidden\" value='" . $json . "'/>";
	//}
	$output .= "		</div>
    			</div>";
	// non chiudo il tag <li> perchè gli elementi sono annidati
	return $output;
}

function _getAttributes($entity) {
	$retAttr = "";
	foreach ($entity as $key => $value) {
		$retAttr .= $key . ':' . $value . ',';
	}
	return $retAttr;
}

function _getAttributesFromXSD($xsd) {
	unset($attributes);
	define('xmlns', 'http://www.w3.org/2001/XMLSchema');
	$xml = simplexml_load_file($xsd, null, null, xmlns);
	$xml_noXS = simplexml_load_string(str_replace('xs:', '', $xml -> saveXML()));

	//VISITE_EXAMS.XSD
	if (preg_match("/visite_exams\.xsd/i", $xsd)) {
		$document = $xml_noXS -> element -> complexType;
		$group = $document -> sequence -> element -> complexType;
		$visit = $group -> sequence -> element -> complexType;
		$esam = $visit -> sequence -> element -> complexType;

		foreach ($group->attribute as $key => $value) {
			if (((string)$value -> attributes() -> name) != 'text') {
				// il titolo lo visualizziamo in un altro modo
				$attributes['G'][] = (string)$value -> attributes() -> name;
			}
		}
		foreach ($visit->attribute as $key => $value) {
			if (((string)$value -> attributes() -> name) != 'text') {
				// il titolo lo visualizziamo in un altro modo
				$attributes['V'][] = (string)$value -> attributes() -> name;
			}
		}
		foreach ($esam->attribute as $key => $value) {
			$attributes['E'][] = (string)$value -> attributes() -> name;
		}
	} elseif (preg_match("/form\.xsd/i", $xsd)) {
		//TODO: implementare per codemirror (autocompletamento del codice)
		$form = $xml_noXS -> element -> complexType;

		$field = $form -> sequence -> element -> complexType;
		foreach ($form->attribute as $key => $value) {
			$attributes['form'][] = (string)$value -> attributes() -> name;
		}
		foreach ($field->attribute as $key => $value) {
			$attributes['field'][] = (string)$value -> attributes() -> name;
		}
		//echo "<pre>";
		//print_r($attributes);
		//echo "</pre>";
	}
	return $attributes;
}

/*
 function _printValidateForm($fileName, $dom, $path = "../../cdisc-upload/", $prefix){
 _printArea($fileName, $dom, $path = "../../cdisc-upload/", $prefix);
 }
 */
function xmlValidateForm($fileName, $prefix) {
	$m = UIManager::getInstance();
	$output = "";
	$row = _study_load($prefix,false);
	$descr = $row['DESCR'];

	$fileXSD = "form.xsd";
	if ($fileName == 'visite_exams.xml') {
		$fileXSD = "visite_exams.xsd";
	}

	$formname = substr($fileName, 0, strrpos($fileName, '.'));
	$output .= "<form name=\"form_validate_" . $formname . "\" class=\"form-horizontal left\" name=\"validation\" action=\"" . url_for('/study/builder') . "/" . $prefix . "/validate\" method=\"POST\">";
	$output .= '<a href="#" class="green" onclick="form_validate_' . $formname . '.submit();" ><i class="fa fa-thumbs-up bigger-110"></i></a>';
	$output .= '' . $m -> dsp_getHiddenField('file_xml', $fileName);
	$output .= '' . $m -> dsp_getHiddenField('file_xsd', $fileXSD);
	$output .= '' . $m -> dsp_getHiddenField('study_root', $descr);
	$output .= '' . $m -> dsp_getHiddenField('study_prefix', $prefix);

	$output .= '' . $m -> dsp_getHiddenField('structure', 'structure');
	$output .= '' . $m -> dsp_getHiddenField('validation', "true");
	$output .= '' . $m -> dsp_getHiddenField('tab', "2");
	$output .= '</form>';
	return $output;
}

function xmlEditForm($fileName, $prefix) {
	$m = UIManager::getInstance();
	$output = "";
	$row = _study_load($prefix,false);
	$descr = $row['DESCR'];
	$onaction="";
	$href=url_for('/study/builder') .'/'.$prefix.'/buildForm/'.$fileName;
	$icon='fa fa-pencil';
	if($fileName=='new_form.xml'){
		
		$box_message = "<div class=\"col-xs-12\">";
		$box_message = "	<form class=\"form-horizontal\">";
		$box_message .='' . $m -> dsp_getSelectField('Form type', 'form_type', null, null, null, "standard", array("standard"=>"Standard Form","main_sub"=>"Main and Sub Form template")); //,"visit_selection"=>"Visit Selection"
		
		$box_message .=' 		<div id="div_standard" style="display:none">';
		$box_message .='' .  $m -> dsp_getTextField('Form file name', 'form_file_name','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Form name', 'form_name','', '', false, null, '', true);
		$box_message .=' 		</div> <!-- div_standard -->';
		
		$box_message .=' 		<div id="div_main_sub" style="display:none">';
		$box_message .=' 		<h4>Main form options</h4>';
		$box_message .='' .  $m -> dsp_getTextField('Form file name', 'form_file_name','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Form name', 'fname','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Table name', 'table','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getSelectField('Field type', 'type',null, null, null, "radio", array("radio"=>"Radio field","checkbox"=>"Checkbox Field"),null,true);
		$box_message .='' .  $m -> dsp_getTextField('Field column name', 'main_field','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Question label', 'main_field_label','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Positive option label', 'main_field_yes_label','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Positive option value', 'main_field_value','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Negative option label', 'main_field_no_label','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Negative option value', 'main_field_no_value','', '', false, null, '', true);
		$box_message .=' 		<h4>Sub form options</h4>';
		$box_message .='' .  $m -> dsp_getTextField('Form file name', 'sub_form_file_name','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Form name', 'sub_fname','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Table name', 'table_sub','', '', false, null, '', true);
		$box_message .=' 		</div> <!-- div_main_sub -->';
		
		$box_message .=' 		<div id="div_visit_selection" style="display:none">';
		$box_message .='' .  $m -> dsp_getTextField('Form file name', 'form_file_name','', '', false, null, '', true);
		$box_message .='' .  $m -> dsp_getTextField('Form name', 'form_name','', '', false, null, '', true);
		$box_message .=' 		</div> <!-- div_visit_selection -->';
		

 		$box_message .= '	</form>';
		$box_message .='' .  $m -> dsp_getLabelField('<span style="font-weight:bold; color:red; padding-left:6px; "><i class="fa fa-asterisk"></i></span>&nbsp;Mandatory',"");
		$box_message .= '</div>';
		$box_message = str_replace("\"", "'", $box_message);
		$box_message = str_replace("'", "\\'", $box_message);
	
		$onaction='onclick="newFormName(\''.t('New form creation').'\',\''.$box_message.'\',\''.url_for('/study/builder') .'/'.$prefix.'/buildForm/\',\''.$prefix.'\');"';
		$href="#";
		$icon='fa fa-plus';
	}
	$formname = substr($fileName, 0, strrpos($fileName, '.'));
	//$output .= "<form name=\"form_edit_" . $formname . "\" class=\"form-horizontal left\" name=\"validation\" action=\"" . url_for('/study/builder') . "/" . $prefix . "/editForm\" method=\"POST\">";
	$output .= '<a href="'. $href.'" '.$onaction.' class="blue"><i class="'.$icon.' bigger-110"></i></a>';
	//$output .= '' . $m -> dsp_getHiddenField('file_xml', $fileName);
	//$output .= '' . $m -> dsp_getHiddenField('study_root', $descr);
	//$output .= '' . $m -> dsp_getHiddenField('study_prefix', $prefix);
	//$output .= '</form>';
	return $output;
}

function xmlCopyInStructureForm($fileName, $prefix) {
	$m = UIManager::getInstance();
	$output = "";
	$row = _study_load($prefix,false);
	$descr = $row['DESCR'];

	$formname = substr($fileName, 0, strrpos($fileName, '.'));
	$output .= "<form name=\"form_edit_" . $formname . "\" class=\"form-horizontal left\" name=\"validation\" action=\"" . url_for('/study/builder') . "/" . $prefix . "/copy\" method=\"POST\">";
	$output .= '<a href="#" class="blue" onclick="if(confirm_copy(\'' . $fileName . '\',\'' . $descr . '\',\'' . $prefix . '\')){form_edit_' . $formname . '.submit();}" ><i class="fa fa-share"></i></a>';
	//$output .= '<a href="#" class="blue" onclick="file_exists(\''.$fileName.'\',\''.$descr.'\',\''.$prefix.'\');" ><i class="fa fa-share"></i></a>';
	$output .= '' . $m -> dsp_getHiddenField('file_xml', $fileName);
	$output .= '' . $m -> dsp_getHiddenField('study_root', $descr);
	$output .= '' . $m -> dsp_getHiddenField('study_prefix', $prefix);
	$output .= '</form>';
	return $output;
}

function _printTitle($title, $path = "") {
	$output = "";
	if ($path != "") {
		$path = ' href="' . $path . '" target="_blank" ';
		$output .= '<a ' . $path . ' >' . $title . '</a>';
	} else {
		$output .= '<h5>' . $title . '</h5>';
	}
	return $output;
}

//form builder drag'n'drop
function study_form_builder_js($prefix) {
	$enabled_fields['field_radio']='../xCRF/field_radio.inc'; //ok
	$enabled_fields['field_checkbox']='../xCRF/field_checkbox.inc'; //ok
	$enabled_fields['field_textbox']='../xCRF/field_textbox.inc'; //ok
	$enabled_fields['field_text']='../xCRF/field_text.inc'; //ok
	$enabled_fields['field_textarea']='../xCRF/field_textarea.inc'; //ok
	$enabled_fields['field_hidden']='../xCRF/field_hidden.inc'; //ok
	$enabled_fields['field_date_cal']='../xCRF/field_date_cal.inc'; //ok
	$enabled_fields['field_ora']='../xCRF/field_ora.inc';
	$enabled_fields['field_select']='../xCRF/field_select.inc'; //ok
	$enabled_fields['field_file']='../xCRF/field_file.inc';

    $js = "";

	foreach ($enabled_fields as $field => $file){
		include_once $file;
		$field_obj=new $field(); //TODO: Potrebbe essere opportuno gestire meglio il costruttore??
		if(method_exists($field_obj,"builder_js")){
			$field_description=$field_obj->builder_js();
			if(is_array($field_description)){
                if (!isset($field_description['addButton']['icon'])){
                    $field_description['addButton']['icon']="";
                }
				$js.="
				(function() {
					Formbuilder.registerField('{$field_description['field']}', {
						order:{$field_description['order']},
						view:{$field_description['view']},
						addButton:\"<span class='symbol'><span class='{$field_description['addButton']['class']}'>{$field_description['addButton']['icon']}</span></span> {$field_description['addButton']['label']}\",
						edit:
								";
						foreach ($field_description['edit'] as $editor){
							$js .= "\"<%= Formbuilder.templates['{$editor}']() %>\\n\"+
									";
						}
						$js.='""
					});
		
				}).call(this);		
						';
			}else{
				$js.=$field_description;
			}
			
		}
	}
	echo $js;
	db_close();die();
}

function study_form_builder($prefix, $form) {
	$m = UIManager::getInstance();
	$m -> set_onLoad("initBuilder();");
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/buildForm/' . $form);
	$output = "";
	$output .= '<div class="fb-main"></div>';
	// 1. CARICO TUTTI I POSSIBILI ATTRIBUTI PER FORM E FIELD DALL'XSD
	$xsd_form_attributes = _getAttributesFromXSD("builder/XMLValidator/xsd/form.xsd");
	$study = _study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$dir = $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] . '/xml/';
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
			$dir = $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] . '/xml/';
	}
	$form = $dir . $form;
	//echo "<pre>esiste? ".$form." : ".file_exists($form)." <br/></pre>";
	if(file_exists($form)){
		// 2. CARICO LA FORM
		$form_dom = simplexml_load_file($form);
		$form_attributes=array();
		$form_attributes = (array)$form_dom -> attributes();
		$form_attributes = $form_attributes['@attributes'];
		// 3. PRENDO TUTTI GLI ATTRIBUTI form DELL'XSD E LI VALORIZZO CON I VALORI DEGLI ATTRIBUTI DELLA FORM
		$my_form_attributes = array();
		foreach ($xsd_form_attributes['form'] as $key => $value) {
	
			$my_form_attributes[$value] = $form_attributes[$value]!=null ? $form_attributes[$value] : "";
		}
		// 4. PER OGNI FIELD DELLA FORM PRENDO TUTTI GLI ATTRIBUTI DELL'XSD E LI VALORIZZO CON QUELLI DEI CAMPI DELLA FORM
		$form_fields = array();
		
		foreach ($form_dom->field as $field) {
			$field_attributes = (array)$field -> attributes();
			$field_attributes = $field_attributes['@attributes'];
			
			//rinomino attributo cols di field in cols_field per ragioni di univocità da inviare al formbuilder.js (cols è già usato come attributo del tag form)
			//$field_attributes['field_cols']=$field_attributes['cols'];
			//unset($field_attributes['cols']);
			
			
				$form_fields[$field_attributes['var']] = $field_attributes;
				//4.1 SE ESISTE CARICO ANCHE IL TXT_VALUE
				$txt_value = htmlspecialchars(trim($field -> txt_value));
				if ($txt_value != "") {
					$form_fields[$field_attributes['var']]['txt_value'] = $txt_value;
				}
				//4.2 CARICO SE ESISTONO I VALUES DEL CAMPO (caso di select, radiobutton)
				$field_values = array();
				$values = array();
				$values = $field -> value;
				$i = 0;
				foreach ($field->value as $my_value) {
					// echo "<pre>";
					// var_dump($my_value);
					// echo "</pre>";
					$_value = (array)$my_value -> attributes();
					$_value = $_value['@attributes'];
					if($field_attributes["type"] == 'radio'){
						$field_values[]=array("label"=>trim($values[$i]),"value" => $_value['val'],"checked"=>$form_fields[$field_attributes['var']]["checked"]==$_value['val'],"disabled_val"=>$form_fields[$field_attributes['var']]["disabled_val"]==$_value['val']);
					}
					else{
						$field_values[]=array("label"=>trim($values[$i]),"value" => $_value['val']);
					}
					
					//$field_values[$_value['val']] = trim($values[$i]);
					$i++;
				}
				if ($field_values) {
					$form_fields[$field_attributes['var']]['value'] = $field_values!=null ? $field_values : "";
				}
				else if ( !$field_values && $field_attributes["type"] == 'hidden') { 
					//se sono un hidden e non ho values (cioè per tutti gli hidden tranne il CODPAT) aggiungo un values vuoto per ragioni di visualizzazione in formbuilder.js
					//$field_values=array("label"=>"","value" => "");
		            //$form_fields[$field_attributes['var']]['value'][] = $field_values;
		    	}

				//4.3 CARICO SE ESISTONO I RANGECHECKS DEL CAMPO 
				$field_rangechecks = array();
				$rangechecks = array();
				$rangechecks = $field -> rangecheck;
				$i = 0;
				foreach ($field->rangecheck as $my_rangecheck) {
					
					$_rangecheck = (array)$my_rangecheck -> attributes();
					$_rangecheck = $_rangecheck['@attributes'];
					$checkValue = (array)($my_rangecheck->checkValue);
					$message = (array)($my_rangecheck->message);
					//TODO: (02.12.2014) al momento ho implementato un solo checkValue ed un solo messaggio (per questo nella riga successiva ho $checkValue[0] e $message[0]) 
					//ma bisognerà inserire più valori (tipo checkValue con operatore IN oppure NOT IN, oppure messaggi tradotti - come ODM CDISC) e quindi si dovrà usare un foreach
					$field_rangechecks[]=array("comparator"=>$_rangecheck['comparator'],"level" => $_rangecheck['level'],"checkValue" => $checkValue[0],"message" => $message[0]);
				}
				if ($field_rangechecks) {
					$form_fields[$field_attributes['var']]['rangecheck'] = $field_rangechecks!=null ? $field_rangechecks : "";
				} 
		    
		}
	
	}
	
	
	//echo "<pre>";
	//var_dump($form_fields);
	
	$fields_to_json=array();
	
	//creo l'array da mandare al js xmrbuilder.js
	//aggiungo tag form con relativi attributi
	$my_json_field=array();
	$my_json_field['label']=$my_form_attributes["fname"];
	$current_table=$my_form_attributes["table"];
	$my_json_field['field_type']="form";
    $my_json_field['required']=true; 
    $my_json_field['form_options']=$my_form_attributes;
    $my_json_field['cid']="form_".$my_form_attributes["fname"];
    $my_json_field['show_send']=false;
    if($form_dom->send){
    	$send=(string)$form_dom->send;
		$my_json_field['send']=$send;
		$my_json_field['show_send']=true;
    }
	$my_json_field['show_save']=false;
    if($form_dom->save){
    	$save=(string)$form_dom->save;
    	$my_json_field['save']=$save;
		$my_json_field['show_save']=true;
    }
	$my_json_field['show_cancel']=false;
    if($form_dom->cancel){
    	$cancel=(string)$form_dom->cancel;
    	$my_json_field['cancel']=$cancel;
		$my_json_field['show_cancel']=true;
    }
    if($form_dom->enable){
    	// echo "<pre>";
		// print_r($my_ex);
		// echo "</pre>";
		foreach($form_dom->enable->exam as $key=>$ex){
		
		$my_ex=(array)($ex->attributes());
		$my_ex=$my_ex['@attributes'];
		// echo "<pre>";
		// print_r($my_ex);
		// echo "</pre>";
		$enable[$my_ex['visitnum']][$my_ex['number']]=true;//=array('visitnum'=>$my_ex['visitnum'],'number'=>$my_ex['number']);//[$my_ex['visitnum']]['exam'][$my_ex['number']]=$my_ex['number'];
		}
		// echo "<pre>";
		// print_r($my_json_field['enable']);
		// echo "</pre>";
		// die();
    	
    }
	//carico anche la visit exams per avere i nomi delle visite e degli esami
	$xsd_form_attributes = _getAttributesFromXSD("builder/XMLValidator/xsd/visite_exams.xsd");
	$study = _study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$dir = $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] . '/xml/';
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$dir = $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] . '/xml/';
	}
	$visite_exams = $dir . 'visite_exams.xml';
	
	$visite_exams_json=array();
	$my_visite_exams=array();
	$structure_db_tables=array(); //mi serve caricare tutte le tabelle delle form attualmente inserite nel visite_exams e relativi campi (devo leggere ogni form e caricare i campi!)
	$structure_forms=array(); //mi serve caricare tutti i nomi delle form attualmente inserite nel visite_exams
	if(file_exists($visite_exams)){
		$visite_exams_dom = simplexml_load_file($visite_exams);
		foreach ($visite_exams_dom->group->visit as $visit) {
			
			$my_visit=(array)($visit->attributes());
			$my_visit=$my_visit['@attributes'];
			$my_visit_number=$my_visit['number'];
			$my_visit_text=$my_visit['text'];
			$my_visit_short_txt=$my_visit['short_txt'];
			 // echo "<pre>";
			 // print_r($visit);
			 // echo "</pre>";
			foreach($visit->exam as $exam){
				$my_exam=(array)($exam->attributes());
				$my_exam=$my_exam['@attributes'];
				$my_exam_number=$my_exam['number'];
				$my_exam_text=(array)$exam->text;
				$my_exam_text=(string)$my_exam_text[0];
				$my_visite_exams[]=array("visit_number"=>$my_visit_number,
										 "visit_text"=>$my_visit_text,
										 "visit_short_txt"=>$my_visit_short_txt,
										 "exam_number"=>$my_exam_number,
										 "exam_text"=>$my_exam_text,
										 "enable"=>isset($enable[$my_visit_number][$my_exam_number]));
				$my_xml_form=$dir .$my_exam['xml'];
				if(file_exists($my_xml_form)){
					$form_dom = simplexml_load_file($my_xml_form);
					$table=(array)($form_dom);//->attributes());
					$table=$table['@attributes'];
					$table=$table['table'];
					$structure_forms[$my_visit_number]["text"]=(string)$my_visit_short_txt;
					$structure_forms[$my_visit_number][$my_exam_number]["text"]=$my_exam_text;
					$structure_forms[$my_visit_number][$my_exam_number]["xml"]=$my_exam['xml'];
					foreach($form_dom->field as $field){
						$my_field=(array)($field->attributes());
						$my_field=$my_field['@attributes'];
						if(!isset($my_field['pk'])&&isset($my_field['var'])){
							// echo "<pre>";
							// print_r($field);
							// echo "</pre>";
							$structure_db_tables[$table][]=$my_field['var'];
						}
					}
					
				}
			}
		}
		 // echo "<pre>";
		 // print_r($structure_db_tables);
		 // echo "</pre>";
	}
	$my_json_field['enable']=$my_visite_exams;
	$fields_to_json[]=$my_json_field;
    	
	//aggiungo tutti i tag field con relativi attributi
	foreach($form_fields as $field){
		//var_dump($field);
		$my_json_field=array();
		$my_json_field['label']=$field["txt_value"];
		//$field['var']=strtoupper($field['var']);
        $type = $field["type"];
        if ($type == '') {
            $type = 'text';
        } 
        unset($field["txt_value"]);//svuoto txt_value per non farlo salvare come attributo del campo field
        $my_json_field['field_type']=$type;
        if($field['value']){
		
			$my_json_field['value']=$field['value'];
			unset($field['value']);
		}
		if($field['rangecheck']){
		
			$my_json_field['rangecheck']=$field['rangecheck'];
			unset($field['rangecheck']);
		}
		$my_json_field['field_options']=$field;
    	$my_json_field['cid']=$field["var"];
		//var_dump(json_encode($my_json_field));
		$fields_to_json[]=$my_json_field;
	}
	
	//echo "</pre>";
	
	//$fields_to_json=htmlspecialchars($fields_to_json);
	$fields_to_json=json_encode($fields_to_json);
	//var_dump($fields_to_json);
	//print_r($fields_to_json);
	$structure_db_tables=json_encode($structure_db_tables);
	$structure_forms=json_encode($structure_forms);
	
	// Includo le f_to_calls ***PHP*** abilitate (rinominate E_) 
	$f_to_calls=array();
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {		
		$f_to_calls_dir =  $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] ."/f_to_calls/";
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$f_to_calls_dir =  $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] ."/f_to_calls/";
	}
	//echo $f_to_calls_dir;
	if (is_dir($f_to_calls_dir)) {
		if ($dh = opendir($f_to_calls_dir)) {
			while (($file = readdir($dh)) !== false) {
				$tmp_file=explode('_', $file);
				if ($tmp_file[0] == "E") {
	        		$f_to_calls[]=str_replace(array("E_",".inc"), array("",""), $file);
	        	}
	        }
	        closedir($dh);
	    }
	}
	//includo le f_to_calls ***ACTIVITI***
	global $activiti_conf;
	$service=new ActivitiService($activiti_conf['AWFBaseURL'], $activiti_conf['AWFUsername'], $activiti_conf['AWFPassword']);
    $vars['connectId']=$activiti_conf['AWFConnectionId'];
    $vars['studyPrefix']=$prefix;
    $vars['pkService']=$activiti_conf['PK_SERVICE'];
    try{
        $processes=$service->getProcesses();
		//print_r($processes);
    }catch (Exception $ex){
        error_page($_SERVER['REMOTE_USER'], $ex->getMessage(), $ex);
    }
	// echo "<pre>";
	// print_r($processes);
	// echo "</pre>";
	// echo "<pre>";
	// print_r($_SERVER['HTTP_HOST']);
	// echo "</pre>";
	$tmp_host=explode(".",$_SERVER['HTTP_HOST']);
	$host=$tmp_host[0];
	foreach($processes['data'] as $key=>$process){
		$tmp_process_key=explode(".",$process['key']);
		$process_key=$tmp_process_key[0];
		if($process_key==$host){
			$f_to_calls[]=str_replace($host.".", "", $process['key']);
		}
	}
	
	$f_to_calls=json_encode($f_to_calls);

	$output .= '<input type="hidden" id="form_fields" value="'.htmlentities($fields_to_json).'"/>';
	$output .= '<input type="hidden" id="current_field" value=""/>';
	$output .= '<input type="hidden" id="current_table" value="'.$current_table.'"/>';
	$output .= '<input type="hidden" id="current_column" value=""/>';
	$output .= '<input type="hidden" id="structure_db_tables" value="'.htmlentities($structure_db_tables).'"/>';
	$output .= '<input type="hidden" id="structure_forms" value="'.htmlentities($structure_forms).'"/>';
	$output .= '<input type="hidden" id="f_to_calls" value="'.htmlentities($f_to_calls).'"/>';
	$output .= '<input type="hidden" id="study_prefix" value="'.$prefix.'"/>';
	return html($output,'html_default_layout',array('prefix' => $prefix));
}

//form builder drag'n'drop
function study_form_builder_save($prefix, $form,$db=null) {
	
	$study = _study_load($prefix,false);
	if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
		$dir = $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] . '/xml/';
	}
	else if (preg_match("!XMR!",$study['TYPE'])){
		$dir = $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] . '/xml/';
	}
	//$form = $dir . $form;
	$xml=new BuilderJson2Xml ($_POST['json'],$prefix);
	
	/*VALIDO FORM
	 * in base a xsd
	 */
	if($db=='update_db'){
			$study_xml_file = $dir . "../study.xml";
            $fhandle = fopen($study_xml_file, "r");
            $content = fread($fhandle, filesize($study_xml_file));
        	fclose($fhandle);
			$my_study=new SimpleXMLElement($content);
		//die(var_dump($my_study->configuration->pk_service));
			/**
			 * CREAZIONE/MODIFICA TABELLA IN DB
			 */
			global $config_service;
			$config_service['lang']=$_SESSION['language'];
			//$lang=$config_service['lang'];
			//$xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
			global $ml;
			$conn = new dbconn();
			// $prefix = $study_prefix;
			$lang = getLanguage();
			$ml = new axmr_ml($prefix, $lang, $conn);
			
			$config_service['PK_SERVICE']=$my_study->configuration->pk_service;
			$config_service ['VISITNUM_PROGR']=1;
			if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
				$xml_form = new xml_form ( $conn, $prefix, $config_service, array('CREATE'=>1), $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] .'/' );
			}
			else if (preg_match("!XMR!",$study['TYPE'])){
				$xml_form = new xml_form ( $conn, $prefix, $config_service, array('CREATE'=>1), $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] .'/' );
			}
			$xml_form->xml_form_by_file ( $dir.$form );
			$isValid=$xml_form->allinea_db ();
			if ($isValid) {
				common_add_message(t("SUCCESS! The database table was correctly updated"), INFO);
			} else {
				//echo json_encode(array("sstatus" => "not_valid", "messages" => common_print_messages()));
			}
			//echo "OK";
			header("location: " . url_for('/study/builder/'. $prefix.'/buildForm/'.$form.'/' ));
			db_close();die();
	}
	elseif($db=='drop_db'){
			/**
			 * DROP TABELLA IN DB
			 */
			$config_service['lang']=$_SESSION['language'];
			//$lang=$config_service['lang'];
			//$xml_form = new xml_form ($this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir);
			global $ml;
			$conn = new dbconn();
			// $prefix = $study_prefix;
			$lang = getLanguage();
			$ml = new axmr_ml($prefix, $lang, $conn);
			global $config_service;
			$config_service ['VISITNUM_PROGR']=1;
			if ($study['TYPE'] == 'CLINICAL_TRIAL' || $study['TYPE'] == 'LABORATORY_RANGE') {
				$xml_form = new xml_form ( $conn, $prefix, $config_service, array('CREATE'=>1), $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] .'/' );
			}
			else if (preg_match("!XMR!",$study['TYPE'])){
				$xml_form = new xml_form ( $conn, $prefix, $config_service, array('CREATE'=>1), $_SERVER['DOCUMENT_ROOT'] . '/' . $study['DESCR'] .'/' );
			}
			$xml_form->xml_form_by_file ( $dir.$form );
			$isValid=$xml_form->drop_db_table ();
			if ($isValid) {
				common_add_message(t("SUCCESS! The database table was correctly dropped"), INFO);
			} else {
				//echo json_encode(array("sstatus" => "not_valid", "messages" => common_print_messages()));
			}
			//echo "OK";
			header("location: " . url_for('/study/builder/'. $prefix.'/buildForm/'.$form.'/' ));
			db_close();die();
	}
	else{
		$form_xml = $xml->getDom();
		//print_r($xml->getDom());
		$xsd_dir = 'builder/XMLValidator/xsd';
		libxml_use_internal_errors(true);
		$isValid = $form_xml -> schemaValidate($xsd_dir . "/form.xsd");
		$errors = libxml_get_errors();
		foreach ($errors as $error) {
			common_add_message( t("Message: ") . " " . $error -> message, ERROR);
		}
		//$isValid=true;
		if($isValid){
			$handle=fopen($dir.$form,"w+");
			fwrite($handle,$xml->getXml());
			fclose($handle);
			common_add_message(t("SUCCESS! The file was correctly saved in the product instance structure"), INFO);
		}
		if ($isValid) {
			echo json_encode(array("sstatus" => "valid", "messages" => common_print_messages()));
		} else {
			echo json_encode(array("sstatus" => "not_valid", "messages" => common_print_messages()));
		}
		//echo "OK";
		db_close();die();
	}
	/*$formArray = json_decode($data,true); 
	$formArray = $formArray['fields'];
	$formTag = array_shift($formArray);
	$m = UIManager::getInstance();
	$m -> set_onLoad("initBuilder();");
	$m -> setCurrentUrl('/study/builder/' . $prefix . '/buildForm/' . $form);
	$xmlArray=
	// 1. CARICO TUTTI I POSSIBILI ATTRIBUTI PER FORM E FIELD DALL'XSD
	$xsd_form_attributes = _getAttributesFromXSD("builder/XMLValidator/xsd/form.xsd");
	// 2. CARICO LA FORM
	$study = _study_load($prefix,false);
	$dir = $_SERVER['DOCUMENT_ROOT'] . '/study/' . $study['DESCR'] . '/xml/';
	$form = $dir . $form;
	$form_dom = simplexml_load_file($form);
	$form_attributes = (array)$form_dom -> attributes();
	$form_attributes = $form_attributes['@attributes'];
	// 3. PRENDO TUTTI GLI ATTRIBUTI form DELL'XSD E LI VALORIZZO CON I VALORI DEGLI ATTRIBUTI DELLA FORM
	$my_form_attributes = array();
	foreach ($xsd_form_attributes['form'] as $key => $value) {

		$my_form_attributes[$value] = $form_attributes[$value]!=null ? $form_attributes[$value] : "";
	}
	// 4. PER OGNI FIELD DELLA FORM PRENDO TUTTI GLI ATTRIBUTI DELL'XSD E LI VALORIZZO CON QUELLI DEI CAMPI DELLA FORM
	$form_fields = array();
	foreach ($form_dom as $field) {
		$field_attributes = (array)$field -> attributes();
		$field_attributes = $field_attributes['@attributes'];
		
		//rinomino attributo cols di field in cols_field per ragioni di univocità da inviare al formbuilder.js (cols è già usato come attributo del tag form)
		$field_attributes['field_cols']=$field_attributes['cols'];
		unset($field_attributes['cols']);
		
		$form_fields[$field_attributes['var']] = $field_attributes;
		//4.1 SE ESISTE CARICO ANCHE IL TXT_VALUE
		$txt_value = htmlspecialchars(trim($field -> txt_value));
		if ($txt_value != "") {
			$form_fields[$field_attributes['var']]['txt_value'] = $txt_value;
		}
		//4.2 CARICO SE ESISTONO I VALUES DEL CAMPO (caso di select, radiobutton)
		$field_values = array();
		$values = (array)$field -> value;
		$i = 0;
		foreach ($field->value as $my_value) {
			$_value = (array)$my_value -> attributes();
			$_value = $_value['@attributes'];
			if($field_attributes["type"] == 'radio'){
				$field_values[]=array("label"=>trim($values[$i]),"value" => $_value['val'],"checked"=>$form_fields[$field_attributes['var']]["checked"]==$_value['val'],"disabled_val"=>$form_fields[$field_attributes['var']]["disabled_val"]==$_value['val']);
			}
			else{
				$field_values[]=array("label"=>trim($values[$i]),"value" => $_value['val']);
			}
			
			//$field_values[$_value['val']] = trim($values[$i]);
			$i++;
		}
		if ($field_values) {
			$form_fields[$field_attributes['var']]['values'] = $field_values!=null ? $field_values : "";
		}
		else if ( !$field_values && $field_attributes["type"] == 'hidden') { 
			//se sono un hidden e non ho values (cioè per tutti gli hidden tranne il CODPAT) aggiungo un values vuoto per ragioni di visualizzazione in formbuilder.js
			$field_values=array("label"=>"","value" => "");
            $form_fields[$field_attributes['var']]['values'][] = $field_values;
    } 
		
	}
	
	
	//echo "<pre>";
	//var_dump($form_fields);
	
	$fields_to_json=array();
	
	//creo l'array da mandare al js xmrbuilder.js
	//aggiungo tag form con relativi attributi
	$my_json_field=array();
	$my_json_field['label']=$my_form_attributes["fname"];
	$my_json_field['field_type']="form";
    $my_json_field['required']=true; 
    $my_json_field['field_options']=$my_form_attributes;
    $my_json_field['cid']="form_".$my_form_attributes["fname"];
	$fields_to_json[]=$my_json_field;
	
	//aggiungo tutti i tag field con relativi attributi
	foreach($form_fields as $field){
		//var_dump($field);
		$my_json_field=array();
		$my_json_field['label']=$field["txt_value"];
        $type = $field["type"];
        if ($type == '') {
            $type = 'text';
        } 
        
        $my_json_field['field_type']=$type;
        
		$my_json_field['field_options']=$field;
    	$my_json_field['cid']=$field["var"];
		//var_dump(json_encode($my_json_field));
		$fields_to_json[]=$my_json_field;
	}
	
	//echo "</pre>";
	
	//$fields_to_json=htmlspecialchars($fields_to_json);
	$fields_to_json=json_encode($fields_to_json);
	//var_dump($fields_to_json);
	
	$output .= '<input type="hidden" id="form_fields" value="'.htmlentities($fields_to_json).'"/>';
	return html($output);*/
}


class BuilderJson2Xml {
	private $xml;
	private $doc;
	private $dataArray;

	function __construct($json,$prefix){
		

		if($json){
			$fieldArray = json_decode($json,true); 
			$fieldArray = $fieldArray['fields'];
			$this->dataArray = array_shift($fieldArray);
			//$this->dataArray['@attributes'] = $rootTag['form_options'];
			foreach ($fieldArray as $key => $field) {
				$fieldArray[$key]['field_options']['var']=strtoupper(preg_replace("/\W/", "", str_replace(" ", "", trim($field['field_options']['var'])))); //correggo eventuali errori nel campo VAR (sarà un nome colonna in DB)
				//print_r($field['field_options']['var']);
				if(isset($field['field_options']['hide']) && $field['field_options']['hide']=="true"){ //vmazzeo correggo valorizzazione "hide" da "true" a "yes" (come richiesto dai fields)
					$fieldArray[$key]['field_options']['hide']="yes";
					//print_r($fieldArray[$key]['field_options']['hide']);
				}
				if(isset($field['field_options']['disabled_always']) && $field['field_options']['disabled_always']=="true"){ //vmazzeo correggo valorizzazione "disabled_always" da "true" a "yes" (come richiesto dai fields)
					$fieldArray[$key]['field_options']['disabled_always']="yes";
					//print_r($fieldArray[$key]['field_options']['hide']);
				}
				if($fieldArray[$key]['field_type']!="hidden" && isset($fieldArray[$key]['value'])){
					
					foreach($fieldArray[$key]['value'] as $option_key => $option_value){
						$fieldArray[$key]['value'][$option_key]['value']=strtoupper(preg_replace("/\W/", "", str_replace(" ", "", trim($fieldArray[$key]['value'][$option_key]['value'])))); //correggo eventuali errori nel campo VALUE  (sarà un nome colonna in DB)
					}
					// var_dump($fieldArray[$key]['field_type']);
					// var_dump($fieldArray[$key]['value']);
				}
			}
			//var_dump($fieldArray);
			$this->dataArray['field']=$fieldArray;
			//print_r($this->dataArray['form_options']['is_main']);
			if(isset($this->dataArray['form_options']['is_main'])){
				//print_r($this->dataArray['form_options']['is_main']);
				unset($this->dataArray['form_options']['is_main']);
			}
			$this->dataArray = $this->convert($this->dataArray, 'form'); 
			$this->dataArray['@attributes']['table']=strtoupper(preg_replace("/\W/", "", str_replace(array(" ",$prefix."_"),array("", ""),trim($this->dataArray['@attributes']['table']))));
			// echo "<pre>";
			// print_r($this->dataArray);
			// echo "</pre>";
			// db_close();die();
			if(isset($this->dataArray['show_save'])){
				if($this->dataArray['save']==""){
					$this->dataArray['save']['@cdata']="Save";
				}
				$this->dataArray=$this->move2bottom($this->dataArray,'save');
				unset($this->dataArray['show_save']); //rimuovo perchè non lo voglio nella form
			}else{
				unset($this->dataArray['save']); //rimuovo perchè non lo voglio nella form se show_save non è stato cliccato
			}
			if(isset($this->dataArray['show_send'])){
				if($this->dataArray['send']==""){
					$this->dataArray['send']['@cdata']="Send";
				}
				$this->dataArray=$this->move2bottom($this->dataArray,'send');
				unset($this->dataArray['show_send']); //rimuovo perchè non lo voglio nella form
			}
			else{
				unset($this->dataArray['send']); //rimuovo perchè non lo voglio nella form se show_send non è stato cliccato
			}
			if(isset($this->dataArray['show_cancel'])){
				if($this->dataArray['cancel']==""){
					$this->dataArray['cancel']['@cdata']="Cancel";
				}
				$this->dataArray=$this->move2bottom($this->dataArray,'cancel');
				unset($this->dataArray['show_cancel']); //rimuovo perchè non lo voglio nella form
			}
			else{
				unset($this->dataArray['cancel']); //rimuovo perchè non lo voglio nella form se show_cancel non è stato cliccato
			}
			$this->dataArray=$this->move2bottom($this->dataArray,'enable');
			// print_r($this->dataArray);
			// db_close();die();
			$this->xml = Array2XML::createXML('form', $this->dataArray);
 	         // print_r($this->xml);
			 // db_close();die();
		}
	}
	
	function move2bottom($array,$index){
		$tmp=$array[$index];
		unset($array[$index]);
		if($tmp)$array[$index]=$tmp;
		return $array;
	}
	
	function convert($array, $tag){
		if(!is_array($array)){
			return array("@cdata" => $array);
		}
		if($tag=='value' && ($array['label'] || $array['value'])){
			$newArray['@attributes']=array("val" => $array['value']);
			if($array['label']){
				$newArray["@cdata"]=$array['label'];
			}
			return $newArray;
		}
		if($tag=='rangecheck' && ($array['checkValue'] || $array['comparator'] || $array['level'] || $array['message'])){
			$newArray['@attributes']=array("comparator" => $array['comparator'],"level" => $array['level']);
			if($array['checkValue']!=null){
				$newArray["checkValue"]=$array['checkValue'];
			}
			if($array['message']){
				$newArray["message"]=$array['message'];
			}
			return $newArray;
		}
		unset($array['cid']);
		unset($array['required']);
		
		if(is_array($array['field_options'])){
			$array['@attributes']=$array['field_options'];
			$array['@attributes']['type']=$array['field_type'];
			unset($array['field_options']);
		}
		if(is_array($array['form_options'])){
			if($array['label']){
				$array['form_options']['fname']=$array['label'];
				unset($array['label']);
			}
			
			$array['@attributes']=$array['form_options'];
			unset($array['form_options']);
		}
		if($array['label']){
			$array['txt_value']=$array['label'];
			unset($array['label']);
		}
		/**
		 * INIZIO
		 * vmazzeo 25.08.2014 gestione tag enable
		 */
		if(is_array($array['enable'])){
			$tmp_array=array();
			//print_r($array['enable']);
			foreach($array['enable'] as $visit=>$to_enable){
			//	print_r($visit);
			//	print_r($to_enable);
				if($to_enable['enable']==1){
					$newTag['@attributes']['number']=(string)$to_enable['exam_number'];
					$newTag['@attributes']['visitnum']=(string)$to_enable['visit_number'];
					$tmp_array['exam'][]=$this->convert($newTag, 'exam');
				}
			}	
		}
		//db_close();die();
		$array['enable']=$tmp_array;
		/**
		 * TODO: c'è un bug sulla gestione degli attributi con valore 0 lo prende come nullo e non salva correttamente il tag: 
		 * esempio <enable>[...]<exam number="0" visitnum="0"/>[...]</enable> diventa <enable>[...]<exam/>[...]</enable>
		 * FINE 
		 * vmazzeo 25.08.2014 gestione tag enable
		 */
		
		unset($array['field_type']);
		foreach($array as $key => $val){
			if(is_numeric($key) || ($key!='@attributes' && $val!='') ){
				if(!is_numeric($key)){
					$newTag=$key;
				}else{
					$newTag=$tag;
				}
				if($newTag=='value' && $tag!='value'){					
					foreach($val as $currVal){
						if($currVal['disabled_val']){
							$array['@attributes']['disabled_val']=$currVal['value'];
						}
						if($currVal['checked']){
							$array['@attributes']['checked']=$currVal['value'];
						}
					}
				}
				$array[$key]=$this->convert($val, $newTag);
			}
			else if (!$val){
				unset($array[$key]);
			}else{
				foreach($val as $akey => $aval){
					
					if(!$aval){
						unset($array['@attributes'][$akey]);
					}
				}
			}
		}
		return $array;
		
	}
	
	function getXml(){
		return $this->xml->saveXML();
	}

	function getDom(){
		return $this->xml;
	}
	
}



/**
 * Array2XML: A class to convert array in PHP to XML
 * It also takes into account attributes names unlike SimpleXML in PHP
 * It returns the XML in form of DOMDocument class for further manipulation.
 * It throws exception if the tag name or attribute name has illegal chars.
 *
 * Author : Lalit Patel
 * Website: http://www.lalit.org/lab/convert-php-array-to-xml-with-attributes
 * License: Apache License 2.0
 *          http://www.apache.org/licenses/LICENSE-2.0
 * Version: 0.1 (10 July 2011)
 * Version: 0.2 (16 August 2011)
 *          - replaced htmlentities() with htmlspecialchars() (Thanks to Liel Dulev)
 *          - fixed a edge case where root node has a false/null/0 value. (Thanks to Liel Dulev)
 * Version: 0.3 (22 August 2011)
 *          - fixed tag sanitize regex which didn't allow tagnames with single character.
 * Version: 0.4 (18 September 2011)
 *          - Added support for CDATA section using @cdata instead of @value.
 * Version: 0.5 (07 December 2011)
 *          - Changed logic to check numeric array indices not starting from 0.
 * Version: 0.6 (04 March 2012)
 *          - Code now doesn't @cdata to be placed in an empty array
 * Version: 0.7 (24 March 2012)
 *          - Reverted to version 0.5
 * Version: 0.8 (02 May 2012)
 *          - Removed htmlspecialchars() before adding to text node or attributes.
 *
 * Usage:
 *       $xml = Array2XML::createXML('root_node_name', $php_array);
 *       echo $xml->saveXML();
 */

class Array2XML {

    private static $xml = null;
	private static $encoding = 'UTF-8';

    /**
     * Initialize the root XML node [optional]
     * @param $version
     * @param $encoding
     * @param $format_output
     */
    public static function init($version = '1.0', $encoding = 'UTF-8', $format_output = true) {
        self::$xml = new DomDocument($version, $encoding);
        self::$xml->formatOutput = $format_output;
		self::$encoding = $encoding;
    }

    /**
     * Convert an Array to XML
     * @param string $node_name - name of the root node to be converted
     * @param array $arr - aray to be converterd
     * @return DomDocument
     */
    public static function &createXML($node_name, $arr=array()) {
        $xml = self::getXMLRoot();
        $xml->appendChild(self::convert($node_name, $arr));

        self::$xml = null;    // clear the xml node in the class for 2nd time use.
        return $xml;
    }

    /**
     * Convert an Array to XML
     * @param string $node_name - name of the root node to be converted
     * @param array $arr - aray to be converterd
     * @return DOMNode
     */
    private static function &convert($node_name, $arr=array()) {

        //print_arr($node_name);
        $xml = self::getXMLRoot();
        $node = $xml->createElement($node_name);

        if(is_array($arr)){
            // get the attributes first.;
            if(isset($arr['@attributes'])) {
                foreach($arr['@attributes'] as $key => $value) {
                    if(!self::isValidTagName($key)) {
                        throw new Exception('[Array2XML] Illegal character in attribute name. attribute: '.$key.' in node: '.$node_name);
                    }
                    $node->setAttribute($key, self::bool2str($value));
                }
                unset($arr['@attributes']); //remove the key from the array once done.
            }

            // check if it has a value stored in @value, if yes store the value and return
            // else check if its directly stored as string
            if(isset($arr['@value'])) {
                $node->appendChild($xml->createTextNode(self::bool2str($arr['@value'])));
                unset($arr['@value']);    //remove the key from the array once done.
                //return from recursion, as a note with value cannot have child nodes.
                return $node;
            } else if(isset($arr['@cdata'])) {
                $node->appendChild($xml->createCDATASection(self::bool2str($arr['@cdata'])));
                unset($arr['@cdata']);    //remove the key from the array once done.
                //return from recursion, as a note with cdata cannot have child nodes.
                return $node;
            }
        }

        //create subnodes using recursion
        if(is_array($arr)){
            // recurse to get the node for that key
            foreach($arr as $key=>$value){
                if(!self::isValidTagName($key)) {
                    throw new Exception('[Array2XML] Illegal character in tag name. tag: '.$key.' in node: '.$node_name);
                }
                if(is_array($value) && is_numeric(key($value))) {
                    // MORE THAN ONE NODE OF ITS KIND;
                    // if the new array is numeric index, means it is array of nodes of the same kind
                    // it should follow the parent key name
                    foreach($value as $k=>$v){
                        $node->appendChild(self::convert($key, $v));
                    }
                } else {
                    // ONLY ONE NODE OF ITS KIND
                    $node->appendChild(self::convert($key, $value));
                }
                unset($arr[$key]); //remove the key from the array once done.
            }
        }

        // after we are done with all the keys in the array (if it is one)
        // we check if it has any text value, if yes, append it.
        if(!is_array($arr)) {
            $node->appendChild($xml->createTextNode(self::bool2str($arr)));
        }

        return $node;
    }

    /*
     * Get the root XML node, if there isn't one, create it.
     */
    private static function getXMLRoot(){
        if(empty(self::$xml)) {
            self::init();
        }
        return self::$xml;
    }

    /*
     * Get string representation of boolean value
     */
    private static function bool2str($v){
        //convert boolean to text value.
        $v = $v === true ? 'true' : $v;
        $v = $v === false ? 'false' : $v;
        return $v;
    }

    /*
     * Check if the tag name or attribute name contains illegal characters
     * Ref: http://www.w3.org/TR/xml/#sec-common-syn
     */
    private static function isValidTagName($tag){
        $pattern = '/^[a-z_]+[a-z0-9\:\-\.\_]*[^:]*$/i';
        return preg_match($pattern, $tag, $matches) && $matches[0] == $tag;
    }
}




// FINE BUILDER
?>
