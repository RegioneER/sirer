<?php

function user_init(){
	dispatch('/user', 'user_page_new');
	dispatch('/user/new', 'user_page_new');
	dispatch('/user/new/:ID_AZIENDA/:CF', 'user_page_new');
	dispatch_post('/user/new', 'user_page_new');

	dispatch('/user/list', 'user_page_list');

	dispatch('/user/view/:username', 'user_page_view');
	dispatch_post('/user/view/:username', 'user_page_view');
	dispatch('/user/get_user_view/:username/:jqGrid','_user_get_view');//VAXMR-300
	dispatch('/user/view/toggle/hub/:scope/:username/:study_prefix/:siteid/:profileid/:active_toggle','_user_toggle_privilege_hub');//VAXMR-300
	dispatch('/user/edit/:username', 'user_page_edit');
	dispatch_post('/user/edit/:username', 'user_page_edit');

	dispatch('/user/clone/:username', 'user_clone');
	dispatch('/user/clone/:from/:to', 'user_clone_fromto');

	dispatch('/user/sendcredentials/:username/:type', 'user_page_sendcredentials');
	dispatch('/user/resetcredentials/:username/page', 'user_page_resetcredentials');

	dispatch('user/privileges/:username', 'user_page_privileges');
	dispatch_post('user/privileges/:username', 'user_page_privileges');

	dispatch('user/toggle/:username/:prefix/:siteid/:profileid', 'user_toggle_privileges');//VAXMR-297 spostata in profile.module.php

	dispatch('user/get_list_user/:jqGrid','_user_list_users');
	dispatch('user/get_list_privileges/:username/:jqGrid','_user_load_privileges');

	dispatch('user/get_user_data/:username/:jqGrid','_user_load_user');
	dispatch('user/get_list_privilege/:username/:$prefix/:siteid/:profileid/:jqGrid','_user_load_privilege');
	dispatch('user/get_user_gruppiu/:username/:jqGrid','_user_load_gruppiu');
	dispatch('user/get_user_studies/:username/:jqGrid','_user_load_studies');
	dispatch('user/get_user_sites/:username/:jqGrid','_user_load_sites');
	dispatch('user/get_user_profiles/:username/:jqGrid','_user_load_profiles');

	dispatch('user/get_user_uo/:username/:jqGrid','_user_get_uo');//VAXMR-300)
	dispatch('user/delete/:username','_user_delete');
}

function user_sidebar($sideBar){
	$itm2=new SideBarItem(new Link(t("Users"), "user", url_for('/user')));
	$itm2->addItem(new SideBarItem(new Link(t("New user"), "plus", url_for('/user/new')), null, UIManager::_checkActive('/user/new')));
	//$itm2->addItem(new SideBarItem(new Link("Edit existing user", "edit", url_for('/user/list')), null, UIManager::_checkActive('/user/list')));
	$itm2->addItem(new SideBarItem(new Link(t("List existing users"), "list", url_for('/user/list')), null, UIManager::_checkActive('/user/list')));
	$sideBar->addItem($itm2);

	return $sideBar;
}

function user_breadcrumb($paths)
{
	if(UIManager::_checkActive('/user')){
		$paths[]=array(t("Users"), t("Users"), url_for('/user/list'));
		if(UIManager::_checkActive('/user/new')){
			$paths[]=array(t("New user"),t("New user"), url_for('/user/new'));

		}
		if(UIManager::_checkActive('/user/edit')){
			$paths[]=array(t("Edit user"),t("Edit user"), url_for('/user/edit'));

		}
		if(UIManager::_checkActive('/user/view')){
			$paths[]=array(t("User details"),t("User details"), url_for('/user/view'));

		}
		if(UIManager::_checkActive('/user/list')){
			$paths[]=array(t("List existing users"),t("List existing users"), url_for('/user/list'));
		}
		if(UIManager::_checkActive('/user/privileges')){
			$paths[]=array(t("Add/remove user privileges"),t("Add/remove user privileges"), url_for('/user/privileges'));

		}
	}

	return $paths;
}

function user_getPageTitle($page_title){

	if(UIManager::_checkActive('/user')){
		$page_title=t("Users");
		if(UIManager::_checkActive('/user/new')){
			$page_title=t("New user");

		}
		if(UIManager::_checkActive('/user/edit')){
			$page_title=t("Edit user");

		}
		if(UIManager::_checkActive('/user/view')){
			$page_title=t("User details");

		}
		if(UIManager::_checkActive('/user/list')){
			$page_title=t("List existing users");
		}
		if(UIManager::_checkActive('/user/privileges')){
			$page_title=t("Add/remove user privileges");
		}
	}

	return $page_title;
}

function user_form($row, $action){
	$output = "";
	$m = UIManager::getInstance();
	$form_action='/acm/?/user/new/';
	if($action==ACT_MODIFY){
		$form_action='/acm/?/user/edit/'.$row['USERID'];
	}
	$output .= '<form class="form-horizontal" role="form" method="post" action="'.$form_action.'">';
	$output .= ''.$m->dsp_getCheckbox('UTENTE INTERNO ALLA REGIONE', 'UTENTE_INTERNO', '', '', false, false, $row).'';
	$output .= ''.$m->dsp_getTextField('CODICE FISCALE', 'CODICE_FISCALE', '', '<div id="loadCF"  style="display:none"><i class="fa fa-spin fa-cog"></i> Cerco tra il personale</div>', false, false, $row, true).'';
	$output .= ''.$m->dsp_getTextField('USER ID', 'USERID', '', '', ($action==ACT_MODIFY), false, $row, true).'';
	$output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'USERID', $row['USERID'], false).'';
	//$output .= ''.$m->dsp_getTextField('PROFILE', 'profile-field', 'select profile', '', false, false).'';
	$output .= ''.$m->dsp_getTextField('NAME', 'NOME', '', '', false, false, $row, true).'';
	$output .= ''.$m->dsp_getTextField('SURNAME', 'COGNOME', '', '', false, false, $row, true).'';
	$output .= ''.$m->dsp_getTextField('COMPANY', 'AZIENDA_ENTE', '', '', false, false, $row, true).'';

	$optstites=array();
	$sites=_strutture_list_aziende();
	/*echo "<pre>";
    var_dump($sites);
    echo "</pre>";*/
	foreach ($sites as $site_id=> $site_descr){
		$optstites[$site_descr['ID_AZIENDA']]=$site_descr['DESCRIZIONE_AZIENDA'];
	}

	$output .= ''.$m->dsp_getSelectField('AZIENDA DI RIFERIMENTO', 'COD_AZIENDA', '', '', false, $row['COD_AZIENDA'], $optstites,null,false);
	$output .= ''.$m->dsp_getTextField('EMAIL', 'EMAIL', '', '', false, false, $row, true).'';
	$output .= ''.$m->dsp_getTextField('PHONE', 'TELEFONO', '', '', false, false, $row).'';
	$output .= ''.$m->dsp_getTextField('FAX', 'FAX', '', '', false, false, $row).'';
	$output .= ''.$m->dsp_getTextField('ADDRESS', 'VIA', '', '', false, false, $row).'';

	$output .= ''.$m->dsp_getCheckbox('STATUS', 'STATUS', '', 'Enabled', false, false, $row).'';
	$cuser = _user_load_user($_SERVER['REMOTE_USERID']);
	if (in_array("tech-admin",$cuser['PROFILI'])) {//STSANPRJS-570
		$output .= '' . $m->dsp_getCheckbox('ADMIN USER', 'ADMIN_USER', '', 'Access to ACM allowed', false, false, $row) . ''; //GENHD-129 added flag in user form to allow access to acm and study inizialization to the user
	}
	$output .= ''.$m->dsp_getTextField('SUBPROFILO', 'SUBPROFILO', '', '', false, false, $row).'';
	$output .= ''.$m->dsp_getTextField('PARTITA IVA', 'P_IVA', '', '', false, false, $row).'';
	$output .= ''.$m->dsp_getTextField('RUOLO', 'RUOLO', '', '', false, false, $row).'';
	$output .= ''.$m->dsp_getTextField('QUALIFICA', 'QUALIFICA', '', '', false, false, $row).'';
	$output .= ''.$m->dsp_getTextField('MEMO', 'MEMO', '', '', false, false, $row).'';
	//$output .= ''.$m->dsp_getTextField('SIGN eCRF', 'signecrf-field', '', '', false, false).'';
	//$output .= ''.$m->dsp_getTextField('SIGN eSAE', 'signsae-field', '', '', false, false).'';
	$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
	$output .= '</form>';
	$output .= '<script>
						  $(document).ready(function(){
						      $("#UTENTE_INTERNO").on("change",function(){
								  if(!$(this).prop("checked")){
									  $("#P_IVA-field").parents(".form-group").show();
								  }
								  else{
									  $("#P_IVA-field").parents(".form-group").hide();
									  $("#CODICE_FISCALE-field").trigger("change");
								  }
								  $("#SUBPROFILO-field").parents(".form-group").hide();
						      });
						      $("#UTENTE_INTERNO").trigger("change");
							  $("#CODICE_FISCALE-field").on("change",function(){
							  	if($("#UTENTE_INTERNO").prop("checked") && $("#CODICE_FISCALE-field").val()!="" ){//STSANSVIL-733 faccio partire recupero info e controlli su CF solo se utente interno
							      $("#loadCF").show();
									$.ajax({
										type : "GET",
										url : "/acm/?/strutture/get_personale_da_cf/"+$(this).val() ,
										dataType : "json",
										async: false, //aspetto che torni dalla chiamata ajax
										success : function(data) {
											if(data.sstatus=="ok"){
												//console.log("TROVATO! "+data);
												personale=data.return_value[0];
												$("#NOME-field").val(personale.NOME);
												$("#COGNOME-field").val(personale.COGNOME);
												$("#COD_AZIENDA").val(personale.ID_AZIENDA).trigger("change");
												if(!$("#UTENTE_INTERNO").prop("checked")){
													$("#UTENTE_INTERNO").prop("checked",true);
													$("#UTENTE_INTERNO").trigger("change");
												}
												$("#QUALIFICA-field").val(personale.UO_DESCR);
												$("#RUOLO-field").val(personale.RUOLO);';
	if($action==ACT_INSERT){
		$output .= '$("#USERID-field").val($("#CODICE_FISCALE-field").val());
													';
	}
	$output .= '}
											else if(data.sstatus=="ko"){
											    alert("Nessun personale trovato");
											    /*$("#NOME-field").val("");
												$("#COGNOME-field").val("");
												$("#COD_AZIENDA").val("").trigger("change");
												if($("#UTENTE_INTERNO").prop("checked")){
													$("#UTENTE_INTERNO").prop("checked",false);
													$("#UTENTE_INTERNO").trigger("change");
												}
												$("#QUALIFICA-field").val("");
												$("#RUOLO-field").val("");
												*/
											}
										}
									});
									$("#loadCF").hide();
								}
							  });
						  });
						  </script>';
	return $output;
}
function user_form_validate(){
	$retval = true;
	$row = $_POST;
	$row = common_booleanCheckBox($row, 'UTENTE_INTERNO');
	if (!$row['CODICE_FISCALE']){
		common_add_message(t("Please specify the field ")." '".t("CODICE FISCALE")."'",WARNING);
		$retval = false;
	}
	if (strlen($row['CODICE_FISCALE'])>16){
		common_add_message(t("Verificare il campo ")."'".t("Codice Fiscale")."': la lunghezza massima prevista è di 16 caratteri",WARNING);
		$retval = false;
	}
	if (!$row['USERID']){
		common_add_message(t("Please specify the field ")." '".t("USER ID")."'",WARNING);
		$retval = false;
	}

	if($row['UTENTE_INTERNO']) {
		if (!preg_match("/[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]/", $row['CODICE_FISCALE'])) {
			common_add_message(t("Codice fiscale formalmente non valido "), WARNING);
			$retval = false;
		}
		if ($row['USERID'] != $row['CODICE_FISCALE']) {
			common_add_message(t("Utilizzare il Codice Fiscale come user id") . " '" . t("USER ID") . "'", WARNING);
			$retval = false;
		}
	}
	if (!$row['NOME']){
		common_add_message(t("Please specify the field ")." '".t("NAME")."'",WARNING);
		$retval = false;
	}
	if (!$row['COGNOME']){
		common_add_message(t("Please specify the field ")." '".t("SURNAME")."'",WARNING);
		$retval = false;
	}
	if (!$row['AZIENDA_ENTE']){
		common_add_message(t("Please specify the field ")." '".t("COMPANY")."'",WARNING);
		$retval = false;
	}
	if (!$row['EMAIL']){
		common_add_message(t("Please specify the field ")." '".t("EMAIL")."'",WARNING);
		$retval = false;
	}
	if(!preg_match('/[a-z0-9_]+@[a-z0-9\-]+\.[a-z0-9\-\.]+/', $row['EMAIL'])){
		common_add_message(t("inserire un indirizzo email valido "),WARNING);
		$retval = false;
	}
	return $retval;
}
function user_form_submit($action,$old_row=false){
	$retval = false;
	$row = $_POST;
	unset($row['submit-button']);
	unset($row['reset-button']);

	//var_dump($_POST);
	//die("sono qui");
	$row = common_booleanCheckBox($row, 'STATUS');
	$cuser = _user_load_user($_SERVER['REMOTE_USERID']);

	if (in_array("tech-admin",$cuser['PROFILI'])) {//STSANPRJS-570
		$row = common_booleanCheckBox($row, 'ADMIN_USER'); //GENHD-129 added flag in user form to allow access to acm and study inizialization to the user
	}
	else{
		unset($row['ADMIN_USER']);
	}
	$row = common_booleanCheckBox($row, 'UTENTE_INTERNO');
	//unset($row['STATUS']);

	$row['NOME'] = trim($row['NOME']);
	$row['COGNOME'] = trim($row['COGNOME']);
	$row['EMAIL'] = trim($row['EMAIL']);
	$row['AZIENDA_ENTE'] = trim($row['AZIENDA_ENTE']);

	$table = "ANA_UTENTI_1";

	$row['USERID'] = strtoupper(trim($row['USERID']));
	$row['CODICE_FISCALE'] = strtoupper(trim($row['CODICE_FISCALE']));
	//$row['USERID'] = $row['USERID'];
	//unset($row['USERID']);
	if ($action == ACT_INSERT){
		//$id = db_getmaxdbvalue($table,'ID');
		//$row['ID'] = common_nextId($id,1);
		//$_POST['ID'] = $row['ID'];
		//die("sono qui");
		$bind['USERID']=$row['USERID'];
		$rs = db_query_bind("SELECT u.USERID FROM UTENTI u WHERE u.USERID= :USERID ",$bind);
		$present=false;
		while ($ckrow = db_nextrow($rs)){ //Attenzione a non sovrascrivere la variabile $row. Forse $ckrow può anche non servire...
			$present=true;
		}
		if ($present){
			common_add_message(t("UserId already present in the system!"),ERROR);
			return;
		}
		$row['CREATEDT']="[SYSDATE]";
	}

	$change_pwd=false;

	if($action == ACT_INSERT||($row['STATUS']&&!$old_row['STATUS'])){
		$new_user_password = _generatePassword();
		$bCryptedPass = password_hash($new_user_password, PASSWORD_BCRYPT, array("cost" => 12));
		$bCryptedPass = str_replace('$2y$', '$2a$', $bCryptedPass);

		$row['FIRST_PASSWORD']=$bCryptedPass;
		$expirepwd = "[SYSDATE]-1";
		//$row['CREATED_ON']="[SYSDATE]";
		$row['EXPDT']="TO_DATE(to_char(sysdate+180,'DD/MM/YYYY'),'DD/MM/YYYY')";
		$change_pwd=true;

	}

	//if (db_form_updatedb($table, $row, $action, 'USERID', false)){

	// Insert dell'utente in UTENTI
	$table_user="UTENTI";
	$vals_user=array();
	if($action == ACT_INSERT){
		$vals_user['USERID']=$row['USERID'];
		$vals_user[OLDPREFIX.'USERID']=$row['USERID'];
		$vals_user['PASSWORD']=$row['FIRST_PASSWORD'];
		$vals_user['ABILITATO']=$row['STATUS'];
		$vals_user['ID_TIPOLOGIA']=1;
		$vals_user['BUDGET']=0;
		$vals_user['CONSUMO']=0;
		$vals_user['SCADENZAPWD']=8;
		//$vals_user['DTTM_SCADENZAPWD']= //Da gestire correttamente la data se si vuole inserire qui ;//SDSANIT-36430 non aggiorniamo data scadenza per sirer perchè si collegano da LDAP con loro credenziali
		$vals_user['DTTM_ULTIMOACCESSO']="";
		$vals_user['SBLOCCOPWD']="";
		$vals_user['ID_VISTA']=0;
		$vals_user['UPDATE_ID']=0;
		$vals_user['CREATED_ON']="[SYSDATE]";
	}
	else{
		$vals_user['USERID']=$row['USERID'];
		$vals_user[OLDPREFIX.'USERID']=$row['USERID'];
		$vals_user['ABILITATO']=$row['STATUS'];
		/*if($change_pwd){//SDSANIT-36430 non aggiorniamo data scadenza per sirer perchè si collegano da LDAP con loro credenziali
			$vals_user['DTTM_SCADENZAPWD']=$row['EXPDT'];
			$vals_user['PASSWORD']=$row['FIRST_PASSWORD'];
		}*/
	}
	if (db_form_updatedb($table_user, $vals_user, $action, 'USERID', false)){

		// Insert dell'utente in ANA_UTENTI_1
		$table_user="ANA_UTENTI_1";
		$vals_user=array();
		$vals_user['USERID']=$row['USERID'];
		$vals_user['ID_TIPOLOGIA']=1;
		$vals_user['COGNOME']=$row['COGNOME'];
		$vals_user['NOME']=$row['NOME'];
		$vals_user['CODICE_FISCALE']=$row['CODICE_FISCALE'];
		$vals_user['AZIENDA_ENTE']=$row['AZIENDA_ENTE'];
		$vals_user['EMAIL']=$row['EMAIL'];
		$vals_user['TELEFONO']=$row['TELEFONO'];
		$vals_user['FAX']=$row['FAX'];
		$vals_user['VIA']=$row['VIA'];
		$vals_user['COD_AZIENDA'] = $row['COD_AZIENDA'];
		$vals_user['SUBPROFILO']=$row['SUBPROFILO'];
		$vals_user['QUALIFICA']=$row['QUALIFICA'];
		$vals_user['RUOLO']=$row['RUOLO'];
		$vals_user['MEMO']=$row['MEMO'];
		$vals_user['UTENTE_INTERNO']=$row['UTENTE_INTERNO'];
		$vals_user['P_IVA']=$row['P_IVA'];

		$vals_user['UPDATE_ID']=0;
		db_form_updatedb($table_user, $vals_user, $action, 'USERID',false);

		$retval = true;
	}

	if($retval==true){ //GENHD-129 added flag in user form to allow access to acm and study inizialization to the user
		// check if the user is already and admin user
		$user_is_admin_info= _user_is_admin_user($row['USERID']);

		$table_uva="UTENTI_VISTEAMMIN";
		$vals_uva=array();
		$vals_uva['USERID']=$row['USERID'];
		$descrizione_vista=array();
		$descrizione_vista['DESCRIZIONE']='Super-amministratore';
		$rs = db_query_bind("SELECT ID_VISTA from VISTEAMMIN where DESCRIZIONE=:DESCRIZIONE", $descrizione_vista);
		$id_vista=0;
		if ($row_visteammin = db_nextrow($rs)) {
			$id_vista=$row_visteammin['ID_VISTA'];
		}
		$vals_uva['ID_VISTA']=$id_vista;
		$vals_uva['UPDATE_ID']=0;
		if (in_array("tech-admin",$cuser['PROFILI'])) {//STSANPRJS-570
			if ($row['ADMIN_USER'] == 1) {
				$retval = db_form_updatedb($table_uva, $vals_uva, (empty($user_is_admin_info) ? ACT_INSERT : ACT_MODIFY), 'USERID', false);
				if ($retval) {
					$table_ugu = "UTENTI_GRUPPIU";
					$vals_ugu = array();
					$vals_ugu['USERID'] = $row['USERID'];
					$nome_gruppo = array();
					$nome_gruppo['NOME_GRUPPO'] = 'PROFILO AMMINISTRATORE';
					$rs = db_query_bind("SELECT ID_GRUPPOU from ANA_GRUPPIU where UPPER(NOME_GRUPPO)=:NOME_GRUPPO", $nome_gruppo);
					$id_gruppou = 0;
					if ($row_ana_gruppiu = db_nextrow($rs)) {
						$id_gruppou = $row_ana_gruppiu['ID_GRUPPOU'];
					}
					if ($id_gruppou == 0) {
						common_add_message(t("Group 'Profilo Amministratore' not found"), ERROR);
						$retval = false;
					} else {
						$vals_ugu['ID_GRUPPOU'] = $id_gruppou;
						$vals_ugu['ABILITATO'] = $row['ADMIN_USER'];
						$vals_ugu['UPDATE_ID'] = 0;
						// echo "<pre>";
						// print_r($user_is_admin_info);
						// echo "</pre>";
						$bind_id_gruppou = array();
						$bind_id_gruppou['ID_GRUPPOU'] = $id_gruppou;
						$bind_id_gruppou['USERID'] = $row['USERID'];
						$rs = db_query_bind("SELECT COUNT(*) AS UPDATE_RECORD from {$table_ugu} where ID_GRUPPOU=:ID_GRUPPOU AND USERID=:USERID", $bind_id_gruppou);
						$action_ugu = ACT_INSERT;
						$update = 0;
						if ($row_update_gruppiu = db_nextrow($rs)) {
							$update = $row_update_gruppiu['UPDATE_RECORD'];
						}
						if ($update == 1) {
							$action_ugu = ACT_MODIFY;
						}

						if (db_form_updatedb($table_ugu, $vals_ugu, $action_ugu, array('USERID', 'ID_GRUPPOU'), true)) {
							common_add_message(t("Action executed!"), INFO);
							$retval = true;
						} else {
							$retval = false;
						}
					}
				}
			} else {
				$bind_delete_uva['USERID'] = $row['USERID'];
				$sql_delete_uva = "DELETE FROM {$table_uva} WHERE USERID=:USERID";
				$retval = db_query_update_bind($sql_delete_uva, $bind_delete_uva, false);
				if ($retval) {
					common_add_message(t("Action executed!"), INFO);
					db_commit();
				}
			}
		}
		else{
			if ($retval) {
				common_add_message(t("Action executed!"), INFO);
				db_commit();
			}
		}

	}

	return $retval;

}

function user_page_new($id_azienda_from_personale=null, $cf_from_personale=null){
	$output = "";
	/*
    $d = Dispatcher::getInstance();
    $d->center_new();
    return html($d->dsp_getPageContent());
    */
	//$m = UIManager::getInstance();
	$row = array();
	$row['USERID']="";
	if ($_POST){
		if (user_form_validate(ACT_INSERT)){
			if (user_form_submit(ACT_INSERT,$row)){
				header("location: ".url_for('/user/view/'.strtoupper(trim($_POST['USERID']))));
				die();
			}else{
				common_add_message(t("An error occurred during user creation."),WARNING);
			}
		}
		$row = $_POST;
	}
	if($id_azienda_from_personale && $id_azienda_from_personale!=null && $cf_from_personale && $cf_from_personale!=""){
		$row =_personale_load_PI($id_azienda_from_personale, $cf_from_personale);
		$row['COD_AZIENDA']=$row['ID_AZIENDA'];
		$row['USERID']=$cf_from_personale;
		$row['CODICE_FISCALE']=$cf_from_personale;
		$row['UTENTE_INTERNO']=1;
		$row['QUALIFICA']=$row['UO_DESCR'];
		/*echo "<pre>";
        print_r($row);
        echo "</pre>";*/
	}
	$output .= user_form($row,ACT_INSERT);
	return html($output);
}
function user_page_edit($username){
	$output = "";
	$row =_user_load_user($username);
	if ($_POST){
		if (user_form_validate(ACT_MODIFY)){
			if (user_form_submit(ACT_MODIFY,$row)){
				header("location: ".url_for('/user/edit/'.$username));
				die();
			}else{
				common_add_message(t("An error occurred during user updating."),WARNING);
			}
		}
		$row = $_POST;
	}
	$output .= user_form($row,ACT_MODIFY);
	return html($output);
}

function user_clone($username){
	unset($scriptSQL);
	$output = "User permissions to clone: <strong>{$username}</strong><br>";
	$output .= " Please specify which user you want to assign permissions:<br><input type='text' id='userToClone' /><button onclick='
		  
		  window.location=   window.location += \"/\" + $(\"#userToClone\").val();
		  ' >Assign</button>";

	return html($output);


}

function user_clone_fromto($from, $to){
	$bind['USERDACLONARE']=$from;
	$bind['NUOVOUSER']=$to;

	$scriptSQL[] = "delete from users_profiles where userid = :nuovouser";
	$scriptSQL[] = "insert into users_profiles select :nuovouser userid, profile_id, active from users_profiles where userid = :userdaclonare";

	$scriptSQL[] = "delete from utenti_gruppiu where userid = :nuovouser";
	$scriptSQL[] = "insert into utenti_gruppiu select :nuovouser userid, id_gruppou, abilitato, 0 update_id from utenti_gruppiu where userid = :userdaclonare";

	$scriptSQL[] = "delete from users_sites_studies where userid = :nuovouser";
	$scriptSQL[] = "insert into users_sites_studies select :nuovouser userid, site_id, study_prefix, active, user_profile_id from users_sites_studies where userid = :userdaclonare";

	$scriptSQL[] = "delete from users_sites where userid = :nuovouser";
	$scriptSQL[] = "insert into users_sites select :nuovouser userid, site_id from users_sites where userid = :userdaclonare";

	$scriptSQL[] = "delete from users_studies where userid = :nuovouser";
	$scriptSQL[] = "insert into users_studies select :nuovouser userid, study_prefix, active from users_studies where userid = :userdaclonare";

	foreach ($scriptSQL as $key => $value) {
		db_query_bind($value,$bind, true);
	}

	common_add_message(t("Permissions cloned."), INFO);
	header("location: ".url_for('/user/list'));
	die();

}
function _user_delete($username){
	$bind['username']=$username;

	$scriptSQL[] = "delete from users_profiles where userid = :username";

	$scriptSQL[] = "delete from utenti_gruppiu where userid = :username";

	$scriptSQL[] = "delete from users_sites_studies where userid = :username";

	$scriptSQL[] = "delete from users_sites where userid = :username";

	$scriptSQL[] = "delete from users_studies where userid = :username";

	$scriptSQL[] = "delete from ana_utenti_1 where userid = :username";

	$scriptSQL[] = "delete from utenti where userid = :username";

	$scriptSQL[] = "delete from cas5_users where username like :username||'@%'";

	$retval=true;
	foreach ($scriptSQL as $key => $value) {
		if($retval){
			$retval = db_query_update_bind($value,$bind, true);
		}
	}
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else {
		if($retval) {
			common_add_message(t("Utente eliminato."), INFO);
		}
		else{
			common_add_message(t("Si sono verificati errori durante l'eliminazione."), INFO);
		}
		header("location: " . url_for('/user/list'));
		db_close();die();
	}
}

function user_page_view($username){
	//STSANSVIL-109 INIZIO
	if ($_POST){
		$row = $_POST;
		if (_user_delegate($username,$row)){
			header("location: ".url_for('/user/view/'.$username));
			die();
		}else{
			common_add_message(t("An error occurred during user updating."),WARNING);
		}
	}
	//STSANSVIL-109 FINE
	$output = "";
	$row =_user_load_user($username);

	$m = UIManager::getInstance();

	$bind['USERID']=$row['USERID'];

	$data_p=_data_retrieve(false, "select * from ACM_USERS_ASSOC where userid=:USERID", $bind);


	$authzCnt='<div class="table-responsive">
							<table id="sample-table-1" class="table table-striped table-bordered table-hover">
								<thead>
									<tr>
										<th>'.t("PRODUCT INSTANCE").'</th>
										<th>'.t("PROFILE").'</th>
										<th>'.t("SITE").'</th>
										<th>'.t("STATUS").'</th>
										<th>'.t("SCOPE").'</th>
									<tr>
								</thead>	
								<tbody>
					';
	foreach ($data_p as $key=>$val){

		$authzCnt.="<tr>";
		$authzCnt.="<td>{$val['STUDY_DESCR']}</td>";
		$authzCnt.="<td>{$val['PROFILE_CODE']}</td>";
		$authzCnt.="<td>{$val['SITE_DESCR']}</td>";
		if ($val['ACTIVE']) $active="active";
		else $active="not active";
		$authzCnt.="<td>".t($active)."</td>";
		if ($val['PROFILE_SCOPE']=='0') $d_scope="global";
		if ($val['PROFILE_SCOPE']=='1') $d_scope="single";
		if ($val['PROFILE_SCOPE']=='2') $d_scope="multiplicity";
		$authzCnt.="<td>".t($d_scope)."</td>";


		$authzCnt.="</tr>";
	}

	$authzCnt.="</tbody></table></div>";


	if ($row['STATUS']=='1') $status="ACTIVE";
	else $status="NON_ACTIVE";

	$userDataCnt="
					<dl id=\"dt-list-1\" class=\"dl-horizontal\">
						<dt>".t("USER ID")."</dt>
						<dd>".$row['USERID']."</dd>
						<dt>".t("NAME")."</dt>
						<dd>".$row['NOME']."</dd>
						<dt>".t("SURNAME")."</dt>
						<dd>".$row['COGNOME']."</dd>
						<dt>".t("COMPANY")."</dt>
						<dd>".$row['AZIENDA_ENTE']."</dd>
						<dt>".t("EMAIL")."</dt>
						<dd>".$row['EMAIL']."</dd>
						<dt>".t("PHONE")."</dt>
						<dd>".$row['TELEFONO']."</dd>
						<dt>".t("FAX")."</dt>
						<dd>".$row['FAX']."</dd>
						<dt>".t("ADDRESS")."</dt>
						<dd>".$row['VIA']."</dd>
						<dt>".t("STATUS")."</dt>
						<dd>".t($status)."</dd>						
					</dl>
					";


	$output="";
	$output.='<div class="widget-box transparent">
						<div class="widget-header">
							<h4 class="lighter">User details</h4>
						</div>
						<div class="widget-body">'.
		$userDataCnt.'
						</div>
					  </div>';
	//STSANSVIL-109 inizio

	$user_delegation_userid = _user_delegation_userid();
	$is_delegated_by=_is_delegated_by($username);
	//var_dump($user_delegation_userid);
	//var_dump($is_delegated_by);
	$output .= '<div class="widget-box transparent">
				<div class="widget-header col-sm-12">
					<h4 class="lighter">User Delegation (Valida solo per profili PI e Promotore)</h4>
				</div>';
	$output .= '<div class="widget-body ">';
	$output .= '<form class="form-horizontal col-sm-6" role="form" method="post" action="#">';
	$output .= ''.$m->dsp_getLabelField("&nbsp;<br/>Leave blank to delete delegation<br/>&nbsp;",'');
	$output .= ''.$m->dsp_getSelectField('<b>'.$username.'</b><br/>is delegated by', 'DELEGATED_BY', '', '', false, $is_delegated_by, $user_delegation_userid,null,false);
	$output .= ''.$m->dsp_getButtonsSubmitUndo('delegate','submit-button').'';
	$output .= '</form>';
	$output .= '</div>';
	$output .= '</div>';
	$output .= '<div style="clear:both"></div>';
	$output .= '
				<div class="widget-box transparent">
				<div class="widget-header col-sm-12">
					<h4 class="lighter">Profile Association</h4>
				</div>';

	//STSANSVIL-109 fine
	$grid_selector = "user-list-grid-table";//VAXMR-300
	$pager_selector = "user-list-grid-pager";
	$url=url_for('/user/get_user_view/'.$username.'/jqGrid');
	$caption=t("Profiles associated");
	$labels=array('PRODUCT INSTANCE'=>array('NAME'=>'STUDY_TITLE','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		'PROFILE'=>array('NAME'=>'PROFILE_CODE','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		//'SITE'=>array('NAME'=>'SITE_DESCR','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		//'SCOPE'=>array('NAME'=>'PROFILE_SCOPE','TYPE'=>'TEXT','SORT'=>1),
		'STATUS'=>array('NAME'=>'ACTIVE','TYPE'=>'CHECK','SORT'=>1));
	$has_actions = true;
	$output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption, $labels, $has_actions);
	//inserisco bottone per visualizzazione finestra modale creazione nuovi privilegi
	$output .= '<button class="btn btn-info" onclick="showAddProfileUsers(\''.$username.'\');"  style="width:200px; margin-top:5px;" type="submit" name="add_user_profile" id="add_user_profile"><i class="fa fa-upload bigger-110"></i>&nbsp;' . t("Associate new profiles") . '</button>';
	//CREO TABELLA MODALE PER ASSOCIAZIONE NUOVI UTENTI AL PROFILO/STUDIO
	$studies = _study_list();
	$optstudies = array();
	//var_dump($studies);
	foreach ($studies as $k=>$p){
		$optstudies[$p['PREFIX']] = $p['PREFIX']." - ".$p['DESCR'];
	}
	$optscopes=array();
	$optscopes[PROFILE_GLOBAL]="Global scope";
	$optscopes[PROFILE_SINGLE]="Sigle site scope";
	$optscopes[PROFILE_MULTIPLE]="Multi site scope";
	$titolo_modal=t("Associate new profiles to the user")." ".$username;
	$output .="<div style='clear:both'></div>";
	$output .="<div id='not_associated_profiles_modal' class='modal fade'>
						  <div class='modal-dialog'>
							<div class='modal-content'>
							  <div class='modal-header'>
								<button type='button' class='close' data-dismiss='modal'><span aria-hidden='true'>&times;</span><span class='sr-only'>Close</span></button>
								<h4 class='modal-title'>".$titolo_modal."</h4>
							  </div>
							  <div class='modal-body'>";
	$output .= ''.$m->dsp_getTextField('USER ID', 'USERID', '', '', true, $row['USERID']);
	$onaction='';
	//$onaction= 'onchange="if($(this).val()!=0){$(\'#SITE_ID\').parent().show();changeStudyPrefix_GetSitesListPerStudyAndUser();}else{$(\'#SITE_ID\').parent().hide();}"';
	//$output .= ''.$m->dsp_getSelectField('PROFILE SCOPE', 'SCOPE', '', '', false, $row['SCOPE'], $optscopes,$onaction,true);
	//$onaction= 'onchange="changeStudyPrefix_GetProfilesListPerStudy();"';
	$output .= ''.$m->dsp_getSelectField('PROD INSTANCE', 'STUDY_PREFIX', '', '', false, $row['STUDY_PREFIX'], $optstudies,$onaction,true);
	$output .= ''.$m->dsp_getSelectField('PROFILE', 'USER_PROFILE_ID', '', '', false, $row['USER_PROFILE_ID'], array(),false,true);
	$output .= ''.$m->dsp_getSelectField('SITE/CENTER', 'SITE_ID', '', '', false, $row['SITE_ID'], array(),false,true);
	//$output .= ''.$m->dsp_getCheckbox('STATUS', 'ACTIVE', '', 'Enabled', false, false, $row).'';
	//$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
	$output .= '<button class="btn btn-info" onclick="assoc_new_user_privilege();"  style="width:200px; margin-top:5px;" type="submit" name="assoc_new_user_privilege" id="assoc_new_user_privilege"><i class="fa fa-upload bigger-110"></i>&nbsp;' . t("Associate profile") . '</button>';
	$output .="  	  </div>
							  <!--div class='modal-footer'></div-->
							</div><!-- /.modal-content -->
						  </div><!-- /.modal-dialog -->
					   </div><!-- /.modal -->";
	if(_user_check_profile($username,'COORD')){
		$output .="<div style='clear:both'></div>";
		$output .= '
				<div class="widget-box transparent">
				<div class="widget-header col-sm-12">
					<h4 class="lighter">UO Associate (valide solo per profilo Clinical Trial Coordinator)</h4>
				</div>';
		$uo_grid_selector = "user_uo-list-grid-table";//VAXMR-300
		$uo_pager_selector = "user_uo-list-grid-pager";
		$url=url_for('/user/get_user_uo/'.$username.'/jqGrid');
		$caption=t("UO associate");
		$labels=array('ID'=>array('NAME'=>'ID_UO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1, 'WIDTH'=>12),
			'DENOMINAZIONE'=>array('NAME'=>'DENOMINAZIONE_UO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
			'ID DIPARTIMENTO'=>array('NAME'=>'ID_DIPARTIMENTO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
			'DIPARTIMENTO'=>array('NAME'=>'DENOMINAZIONE_DIPARTIMENTO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
			'ID STRUTTURA'=>array('NAME'=>'ID_STRUTTURA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
			'STRUTTURA'=>array('NAME'=>'DENOMINAZIONE_STRUTTURA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
			'AZIENDA'=>array('NAME'=>'DENOMINAZIONE_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
		);
		$has_actions = false;
		$output .=$m->dsp_getTableJqGrid2($uo_grid_selector,$uo_pager_selector,$url,$caption, $labels, $has_actions);
		$output .='<script type="text/javascript">
					//forzo il reload della lista profili perchè la lista UO potrebbe bloccarne la richiesta
					    setTimeout(function(){$("#user-list-grid-table").trigger("reloadGrid")},2000);
					</script>';
	}

	//inserisco legenda
	$output .="<div style='clear:both'></div>";
	$output .=$m->dsp_getLegend("Legend",_user_profile_pages_get_legend());
	return html($output);
}
function _user_delegation_userid(){//STSANSVIL-109
	$retval = array();
	$select="select * FROM USER_DELEGATION_USERID";
	$rs = db_query_bind($select);

	while ($row = db_nextrow($rs)){
		$retval[$row['USERID']] = $row['COGNOME']." ".$row['NOME'];
	}
	return $retval;
}

function _is_delegated_by($username){//STSANSVIL-109
	$retval = "";
	$select="select DELEGATED_BY FROM USER_DELEGATION where userid=:USERID";
	$bind = array();
	$bind['USERID'] = $username;
	$rs = db_query_bind($select,$bind);
	while ($row = db_nextrow($rs)){
		$retval = $row['DELEGATED_BY'];
	}
	return $retval;
}
function _user_delegate($username,$row){//STSANSVIL-109 INIZIO
	$retval = false;
	$row = $_POST;
	unset($row['submit-button']);
	unset($row['reset-button']);

	$table_delegation="USER_DELEGATION";
	$bind['USERID']=$username;
	$sql_delete_delegation="DELETE FROM {$table_delegation} WHERE USERID=:USERID";
	$retval = db_query_update_bind($sql_delete_delegation,$bind,false);//ELIMINO SEMPRE
	if($retval){
		db_commit();
		if($row['DELEGATED_BY']!="") {
			$bind['DELEGATED_BY'] = $row['DELEGATED_BY'];
			$retval = db_form_updatedb($table_delegation, $bind, ACT_INSERT, array("USERID"), true,false,true);
		}
	}
	return $retval;
}
function _user_get_view($username,$jqGrid=false){ //VAXMR-300
	$retval = array();
	$select="select ACM_USERS_ASSOC.*,DECODE(ACM_USERS_ASSOC.ACTIVE,1,0,0,1) AS  ACTIVE_TOGGLE from ACM_USERS_ASSOC where userid=:USERID";
	$bind = array();
	$bind['USERID'] = $username;
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		$actions = array();
		$actions[] = array('LABEL'=>'Toggle enable','ICON'=>'retweet','LINK'=>'" onclick="toggle_user_view_hub(\'[PROFILE_SCOPE]\',\''.$username.'\',\'[STUDY_PREFIX]\',\'[SITE_ID]\',\'[PROFILE_ID]\',\'[ACTIVE_TOGGLE]\')','COLOR'=>'#D32646'); //lightblue
		$ord_override=array("USERID"=>"USERID", "STUDY_PREFIX"=>"STUDY_PREFIX");//array('USERID','STUDY_PREFIX','SITE_ID',);
		$checkicons=array();
		$pkeys=array('USERID','STUDY_PREFIX','PROFILE_ID');
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
function _user_get_uo($username, $jqGrid=false){
	//$retval = array();
	$cuser = _user_load_user($_SERVER['REMOTE_USERID']);
	//Actions
	$actions = array();
	$actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/strutture/UO/edit/[ID_AZIENDA]/[ID]'));
	$actions[] = array('LABEL'=>'Associazione Utente-UO','ICON'=>'users','LINK'=>url_for('/strutture/UO/user_assoc/[ID_AZIENDA]/[ID]'),'COLOR'=>'darkblue');
	//Queries
	$bind = array();
	$bind['USERID']=$username;
	$select="SELECT o.*,o.ID as ID_UO,o.DESCRIZIONE AS DENOMINAZIONE_UO, d.DESCRIZIONE as DENOMINAZIONE_DIPARTIMENTO, a.ID as ID_STRUTTURA, a.DESCRIZIONE as DENOMINAZIONE_STRUTTURA, a.DESCRIZIONE_AZIENDA AS DENOMINAZIONE_AZIENDA FROM ANA_STRUTTURE a, ANA_DIPARTIMENTI d, ANA_UO o, USERS_UO u WHERE u.USERID=:USERID AND u.UO_ID=o.ID  AND d.ID_STRUTTURA = a.ID AND o.ID_DIPARTIMENTO = d.ID ";


	//if (!in_array("tech-admin",$cuser['PROFILI'])){
	//Filtro per site
	$sites = _user_load_sites($_SERVER['REMOTE_USERID']);
	$sList =  _center_list_centers(false, true, true);
	//var_dump($sites);
	//var_dump($sList);
	$azFilter = "";
	foreach ($sites as $s){
		$azId = $sList[$s['SITE_ID']]['CODE'];
		if ($azFilter){$azFilter.",";}
		$azFilter.="'{$azId}'";
		//var_dump($azId);
	}
	if ($azFilter) {
		$select .= " AND o.ID_AZIENDA IN ($azFilter)";
	}else{
		//$select .= " AND o.ID_AZIENDA = '0' "; //Non mostro nulla (in teoria), poichè non ho centri
	}
	//}
	//var_dump($select);

	if(!$jqGrid){ //VAXMR-297
		$select.=" ORDER BY o.DESCRIZIONE";
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		//$select_count="SELECT COUNT(*) AS CONTO FROM SITES";
		//die($select);
		$ord_override=array();
		//$data = _data_load($select,$select_count,$bind,$ord_override);
		$retval = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('ID'),array('IRCSS'),$actions,false);
	}
	if(isAjax()){
		header('Content-Type: application/json');
		echo json_encode(array_merge(array("sstatus" => "ok"), $retval));
		die();
	}
	else{
		return $retval;
	}
}
function _user_toggle_privilege_hub($scope,$username,$study_prefix,$siteid,$profileid,$active_toggle){ //VAXMR-300
	$retval=false;
	if($scope==-1){ //scope globale: richiamo study_profile_toggle_user
		$retval=toggle_user($username);
	}
	else if($scope==0){ //scope globale: richiamo study_profile_toggle_user
		$retval=study_profile_toggle_user($study_prefix, $username, $profileid,false);
	}
	else{ //scope singolo o multiplo: richiamo
		$retval=study_profile_center_toggle_user($username,$study_prefix,$siteid,$profileid,false);
	}
	return $retval;
}
function user_page_list(){
	$page = false;
	if (isset($_GET['page'])){
		$page = $_GET['page'];
	}
	$output = '';
	$m = UIManager::getInstance();
	//$list = _user_list_users(false);
	$grid_selector = "user-list-grid-table";
	$pager_selector = "user-list-grid-pager";
	$url=url_for('/user/get_list_user/jqGrid');
	$caption=t("Existing users");
	$labels=array('USER ID'=>array('NAME'=>'USERID','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		'NAME'=>array('NAME'=>'NOME','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		'SURNAME'=>array('NAME'=>'COGNOME','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		'COMPANY'=>array('NAME'=>'AZIENDA_ENTE','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		'EMAIL'=>array('NAME'=>'EMAIL','TYPE'=>'TEXT','SORT'=>1,'SEARCH'=>1),
		'STATUS'=>array('NAME'=>'STATUS','TYPE'=>'CHECK','SORT'=>1,'WIDTH'=>'10'));
	$has_actions = true;
	$output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption, $labels, $has_actions);

	return html($output);
}

function _user_list_users($jqGrid=false){
	$retval = array();
	$actions = array();
	$actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/user/edit/[USERID]'));
	$actions[] = array('LABEL'=>'Detail','ICON'=>'eye','LINK'=>url_for('/user/view/[USERID]'));
	$actions[] = array('LABEL'=>'Clone permissions','ICON'=>'adjust','LINK'=>url_for('/user/clone/[USERID]'));
	$actions[] = array('LABEL'=>'Toggle enable','ICON'=>'retweet','LINK'=>'#" onclick="toggle_user_view_hub(\'-1\',\'[USERID]\',\'\',\'\',\'\',\'\');$(this).find(\'i.fa-retweet\').addClass(\'fa-spin\');','COLOR'=>'#26D346'); //lightgreen
	// $actions[] = array('LABEL'=>'Add/remove privileges','ICON'=>'tags','LINK'=>url_for('/user/privileges/[USERID]'),'COLOR'=>'#942494'); //VAXMR-300
	$actions[] = array('LABEL'=>'Send USER E-Mail','ICON'=>'envelope','ONCLICK'=>"return confirm('".t("Are you sure that you want to proceed with the operation?")."')",'LINK'=>url_for('/user/sendcredentials/[USERID]/user'),'COLOR'=>'#D32646'); //envelope-o
	$actions[] = array('LABEL'=>'Reset PWD and send recovery link','ICON'=>'envelope','ONCLICK'=>"return confirm('".t("Are you sure that you want to proceed with the operation?")."')",'LINK'=>url_for('/user/sendcredentials/[USERID]/password'),'COLOR'=>'#D32646'); //envelope-o
	$actions[] = array('LABEL'=>'Reset PWD and view credentials','ICON'=>'lock','ONCLICK'=>"return confirm('".t("Are you sure that you want to proceed with the operation?")."')",'LINK'=>url_for('/user/resetcredentials/[USERID]/page'),'COLOR'=>'#D32646'); //envelope-o
	$actions[] = array('LABEL'=>'Delete user','ICON'=>'trash','LINK'=>'#" onclick="deleteUser([ACCESSO_ESEGUITO],\'[USERID]\');$(this).find(\'i.fa-retweet\').addClass(\'fa-spin\');','COLOR'=>'#D32646'); //lightgreen

	//INIZIO GESTIONE FILTRO PER AZIENDA STSANPRJS-570
	$select="SELECT au.*,u.ABILITATO AS STATUS,CASE WHEN DTTM_ULTIMOACCESSO IS NULL THEN 0 ELSE 1 END AS ACCESSO_ESEGUITO  FROM ANA_UTENTI_1 au, UTENTI u WHERE au.USERID=u.USERID";//VECCHIA QUERY SENZA FILTRO
	//$select="SELECT au.*,u.ABILITATO AS STATUS FROM ANA_UTENTI_1 au, UTENTI u,USERS_SITES us, SITES s WHERE au.USERID=u.USERID and au.USERID=us.USERID and us.SITE_ID=s.ID";
	//$cuser = _user_load_user($_SERVER['REMOTE_USERID']);
	//if (!in_array("tech-admin",$cuser['PROFILI'])){
	//Filtro per site
	$sites = _user_load_sites($_SERVER['REMOTE_USERID']);
	$sList =  _center_list_centers(false, true, true);
	//var_dump($sites);
	//var_dump($sList);
	$azFilter="";
	$comma=false;
	foreach ($sites as $s){
		$azId = $sList[$s['SITE_ID']]['CODE'];
		if($comma){
			$azFilter.=',';
		}
		$comma=true;
		$azFilter.="'{$azId}'";
		//var_dump($azId);
	}
	if ($azFilter) {
		$select .= " and (au.userid in (select aau.userid from ANA_UTENTI_1 aau, UTENTI uu,USERS_SITES us, SITES s WHERE aau.USERID=uu.USERID and aau.USERID=us.USERID and us.SITE_ID=s.ID and s.code in ($azFilter))
						  or au.userid in (SELECT pi.CF FROM ana_pi pi, ( SELECT DISTINCT id_azienda, descrizione_azienda FROM ana_strutture) s, utenti u WHERE pi.id_azienda = s.id_azienda AND   pi.cf = u.userid (+) AND pi.ID_AZIENDA IN ($azFilter) and pi.ABILITATO=1))";
	}else{
		//$select .= " and s.code in = '0' "; //Non mostro nulla (in teoria), poichè non ho centri
	}
	//}
	//var_dump($select);
	//FINE GESTIONE FILTRO PER AZIENDA STSANPRJS-570
	//$select_count="SELECT COUNT(*) AS CONTO FROM ANA_UTENTI_1 au, UTENTI u WHERE au.USERID=u.USERID";
	$bind=array();
	$data = _data_retrieve($jqGrid,$select,$bind,array("USERID"=>"u.USERID"),array('USERID'),array('STATUS'),$actions,true); //+key,+checkboxes,+actions,+assignkey
	return $data;
}
function _user_load_user($key,$jqGrid=false){
	$retval = array();
	$select="SELECT au.*,u.ABILITATO AS STATUS  FROM ANA_UTENTI_1 au,UTENTI u WHERE au.USERID=u.USERID AND au.USERID = :KEY ";
	$bind = array();
	$bind['KEY'] = $key;
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		if ($row = db_nextrow($rs)){
			$retval = $row;
		}
		//Carico i gruppi
		$select="SELECT ugu.*, agu.NOME_GRUPPO, agu.DESCRIZIONE FROM UTENTI_GRUPPIU ugu, ANA_GRUPPIU agu WHERE ugu.ID_GRUPPOU=agu.ID_GRUPPOU AND ugu.ABILITATO=1 AND ugu.USERID = :KEY ";
		$bind = array();
		$bind['KEY'] = $key;
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval['GRUPPI'][$row['ID_GRUPPOU']] = $row['DESCRIZIONE'];
		}
		//Carico i profili
		$select="SELECT sp.* FROM USERS_PROFILES up, STUDIES_PROFILES sp WHERE sp.ID=up.PROFILE_ID AND up.ACTIVE=1 AND up.USERID = :KEY ";
		$bind = array();
		$bind['KEY'] = $key;
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval['PROFILI'][$row['ID']] = $row['CODE'];
		}
		//Carico flag ADMIN_USER
		$select="SELECT COUNT(*) as CONTO FROM UTENTI_VISTEAMMIN WHERE USERID = :KEY ";
		$bind = array();
		$bind['KEY'] = $key;
		$rs = db_query_bind($select,$bind);
		if ($row = db_nextrow($rs)){
			if ($row['CONTO']){
				$retval['ADMIN_USER'] = true;
			}
		}
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('USERID');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	return $retval;
}
function _generatePassword($length=8, $strength=8) {
	$vowels = "AEUY";
	$consonants = 'BDGHJLMNPQRSTVWXZ';
	$numbers = '1234567890';
	$special_chars= '@$%!'; //09/04/2013 - Rimosso ( e ) per problemi con Shibboleth //11/04/2013 rimosso anche # vmazzeo

	$password = '';
	for ($i = 0; $i < $length; $i++) {
		$alt = mt_rand(0, 3);
		switch($alt) {
			case 0:
				$password .= $consonants[(rand() % strlen($consonants))];
				break;
			case 1:
				$password .= $vowels[(rand() % strlen($vowels))];
				break;
			case 2:
				$password .= $numbers[(rand() % strlen($numbers))];
				break;
			case 3:
				$password .= $special_chars[(rand() % strlen($special_chars))];
				break;
		}
	}
	//$password="SIRER2019!";//SDSANIT-76816 bugfix veniva forzata solo in randomPassword() enon anche in questa funzione
	return $password;
}

function _createForgetPasswordGUID($username){
	//INSERISCO/MODIFICO IN UTENTI_GRUPPIU
	$table = "FORGET_PASS";
	$action = ACT_INSERT;
	//check existing row
	$row=array();
	$row['USERID']=$username;
	$rs = db_query_bind("SELECT COUNT(*) AS CONTO FROM {$table} WHERE USERID=:USERID",$row);
	$cntr = db_nextrow($rs);
	if ($cntr['CONTO']){
		$action = ACT_MODIFY;
	}
	$ssid = ""; //kcabru97kp3r3gaurg6hqgt2n40iebt5_20150122020125_94752
	//generato identificativo univoco
	//phpsessid+date+random
	$date = date("Ymdhms");
	$rand = rand();
	$begin_string = uniqid("acm_",true);
	$begin_string = str_replace(".","_",$begin_string);
	$ssid = $begin_string . "_" . $date . "_" . substr($rand, 0, 5);
	//Popolare la riga in tabella FORGET_PASS con USERID, SSID, ATTIVO=1, REQ_DT = sysdate
	$row['SSID']=$ssid;
	$row['ATTIVO']=1;
	$row['REQ_DT']="[SYSDATE]";
	$keys = array('USERID');
	if (db_form_updatedb($table, $row, $action, $keys, true, true, false)){
		return $ssid;
	}else{
		return false;
	}
}
function _resetUserPassword($username)
{
	$retval = false;
	$table_user = "UTENTI";
	$vals_user = array();
	$action = ACT_MODIFY;
	//Genera nuova pwd
	$newpwd = _generatePassword();
	$newpwd = strtolower($newpwd);
	$bCryptedPass = password_hash($newpwd, PASSWORD_BCRYPT, array("cost" => 12));
	$bCryptedPass = str_replace('$2y$', '$2a$', $bCryptedPass);
	$expirepwd = "[SYSDATE]-1";
	//Vai con l'update
	//$vals_user['DTTM_SCADENZAPWD'] = $expirepwd;//SDSANIT-36430 non aggiorniamo data scadenza per sirer perchè si collegano da LDAP con loro credenziali
	$vals_user['PASSWORD'] = $bCryptedPass;
	if (db_form_updatedb($table_user, $vals_user, $action, 'USERID')) {
		common_add_message(t("Password reset for user") ." ". $username, INFO);
		$retval = true;
	}
	return $retval;
}
function user_page_resetcredentials($username){
	header('Content-type: text/html; charset=utf-8');
	require_once "./smarty/Smarty.class.php";
	if (file_exists($_SERVER['DOCUMENT_ROOT']."/../config/acm-credentials.tpl")){
		$tplFile=$_SERVER['DOCUMENT_ROOT']."/../config/acm-credentials.tpl";
	}else {
		$tplFile="./templates/credentials.tpl";
	}
	define('SMARTY_DIR', '/http/lib/php_utils/smarty/');
	global $siteInfo;
	$user = _user_load_user($username);

	if (!isset($siteInfo['disclaimer'])){
		$siteInfo['disclaimer']="Le password inserite vengono conservate in modo criptato all'interno dei sistemi. Solo l'utente conosce la propria password, nel caso la dimentichi si consiglia di contattare l'amministratore che provveder&agrave; a fornire una nuova password.";
	}
	if (!isset($siteInfo['logoSite'])){
		$siteInfo['logoSite']="./images/logoSite.png";
	}
	if (!isset($siteInfo['logoCineca'])){
		$siteInfo['logoCineca']="./images/logoCineca.jpg";
	}

	require_once 'password_compat_lib/password.php';

	$password="SIRER2019!";//IMPOSTO SEMPRE A QUELLA DI DEFAULT //randomPassword();
	$bCryptedPass = password_hash($password, PASSWORD_BCRYPT, array("cost" => 12));
	$bCryptedPass = str_replace('$2y$', '$2a$', $bCryptedPass);
	$row['PASSWORD']=$bCryptedPass;
	//$row['DTTM_SCADENZAPWD']='[SYSDATE]-1';//SDSANIT-36430 non aggiorniamo data scadenza per sirer perchè si collegano da LDAP con loro credenziali
	$row['USERID']=$user['USERID'];
	$key[]="USERID";

	if (!db_update_row("UTENTI", $row, $key)){
		die("Errore");
	}
	$template = new Smarty();
	$template->assign("user", $user);
	$template->assign("siteInfo", $siteInfo);
	$template->assign("clearPassword", $password);
	$template->display($tplFile);
}

function randomPassword() {
	$alphabet = "abcdefghijklmnopqrstuwxyz";
	$alphabet=strtoupper($alphabet);
	$pass = array(); //remember to declare $pass as an array
	$alphaLength = strlen($alphabet) - 1; //put the length -1 in cache
	for ($i = 0; $i < 8; $i++) {
		$n = rand(0, $alphaLength);
		$pass[] = $alphabet[$n];
	}
	$n=rand(1,8);
	$pass[$n]=rand(0,9);
	do {
		$n1 = rand(1,8);
		$specialChar="!";
	} while($n1==$n);
	$pass[$n1]=$specialChar;
	$pass="SIRER2019!";
	return implode($pass); //turn the array into a string
}


function user_page_sendcredentials($username,$type)
{
	//$m = UIManager::getInstance();
	//$output = "";
	//return html($output);
	$errors = false;
	$user = _user_load_user($username);
	$body = "Your username to access the ".$_SERVER['SERVER_NAME']." site is: ".$username."<br/>\r\n<br/>\r\nKind Regards,<br/>\r\nSupport Team.";
	if ($type == "password"){
		//resetta la password e invia link di recupero...
		//Probabilmente bisogna anche inserire una riga da qualche parte per attivare il recupero pwd per quell'utente con il token da inviare nel link
		if (_resetUserPassword($username)) {
			$sid = _createForgetPasswordGUID($username);
			if ($sid) {
				$body = "Your password (associated to user {$username} for " . $_SERVER['SERVER_NAME'] . " site) has been reset and can be re-created by following this link:<br/>\r\n";
				$body .= "http://" . $_SERVER['SERVER_NAME'] . "/forget_password/?CheckSID={$sid}<br/>\r\n";
				$body .= "In case of the link is disabled by e-mail application, please copy-paste the URL on a new browser window.";
			}else{
				$errors[] = t("Error during activation token generation.");
			}
		}else{
			$errors[] = t("Error during password reset procedure.");
		}
	}
	$headers = "" .
		"Reply-To:" . "no-reply@{$_SERVER['SERVER_NAME']}" . "\r\n" .
		"X-Mailer: PHP/" . phpversion()."\r\n";
	$headers .= 'MIME-Version: 1.0' . "\r\n";
	$headers .= 'Content-type: text/html; charset=utf-8' . "\r\n";
	$headers .= 'From: ' . "automatic.email@{$_SERVER['SERVER_NAME']}" . "\r\n";
	//Invio mail
	if (!$errors) {
		if (mail($user['EMAIL'], t("Your user credentials"), $body, $headers)) {
			common_add_message(t("E-Mail sent"), INFO);
			//Log in tabella DB
			$table = "ACM_LOG";
			$action = ACT_INSERT;
			$row['ID']="[ACM_LOG_ID.NEXTVAL]";
			$row['USERID']=$_SERVER['REMOTE_USER'];
			$row['TIMESTAMP']="[SYSDATE]";
			$row['ACTION']="SENDMAIL_".strtoupper($type);
			$row['DESCRIPTION']="Sent mail to user {$username} ({$user['EMAIL']}) to manage credentials";

			$keys = array('ID');
			if (db_form_updatedb($table, $row, $action, $keys, true, true, false)){
				//niente
			}else{
				common_add_message(t("Failed to LOG activity into ACM_LOG table."), WARNING);
			}
		} else {
			//Invio fallito
			common_add_message(t("An error occurred when sending the e-mail, please try again later or use another method."), WARNING);
		}
	}else{
		$msgbody = t("E-Mail not sent (See errors below).");
		foreach ($errors as $err){
			$msgbody.= "\n".t($err);
		}
		common_add_message($msgbody, WARNING);
	}

	//Redirect
	header("location: ".url_for('/user/list'));
	die();
}

/**
 * GESTIONE PRIVILEGI UTENTE
 */
function user_page_privileges($username){

	$m = UIManager::getInstance();
	$output = "";
	$list =_user_load_privileges($username, false);
	$labels=array('SITE'=>array('NAME'=>'SITE_DESCR','TYPE'=>'TEXT','SORT'=>1),'PRODUCT INSTANCE'=>array('NAME'=>'STUDY_DESCR','TYPE'=>'TEXT','SORT'=>1, 'WIDTH'=>'10'),'PROFILE'=>array('NAME'=>'D_CODE','TYPE'=>'TEXT','SORT'=>1),'ACTIVE'=>array('NAME'=>'ACTIVE','TYPE'=>'CHECK','SORT'=>1,'WIDTH'=>'10'));
	$actions = true;

	$grid_selector = "user-list-grid-table";
	$pager_selector = "user-list-grid-pager";
	$url=url_for('/user/get_list_privileges/'.$username.'/jqGrid');
	$caption=t("Existing privileges");
	$output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption, $labels, $actions);

	//FORM
	$row = array();
	$row['USERID'] = $username;
	$row['STUDY_PREFIX']="";
	$row['SITE_ID']="";
	$row['USER_PROFILE_ID']="";
	$row['ACTIVE']=0;

	if ($_POST){
		if (user_privileges_form_validate()){
			if (user_privileges_form_submit($username,$list)){
				header("location: ".url_for('/user/privileges/'.$username));
				die();
			}else{
				$output .= t("An error occurred during user privileges update.");
			}
		}
		$row = $_POST;

	}
	// 	var_dump($row);
	// 	var_dump($_POST);
	$output .= user_privileges_form($row, $username);

	return html($output);
}

function _user_load_privileges($username, $jqGrid=false){
	$retval = array();
	$bind = array();
	$bind['KEY']=$username;
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
										AND USERID          =:KEY";

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

	$select_count = "SELECT COUNT(*) AS CONTO ".$fromwhere;

	$data = _data_load($select,$select_count,$bind,array("D_CODE"=>"CODE"));
	//$data = _data_retrieve($jqGrid,$select,$select_count,$bind,array("D_CODE"=>"CODE"),array('USERID','PREFIX','SITE_ID','PROFILE_ID'),array('ACTIVE'),$actions,false);
	$rs = $data['DATASET'];
	$count = $data['COUNT'];
	//Codice custom x gestione record specifica e generazione data array.
	$profili=_list_profiles();
	$actions = array();
	$actions[] = array('LABEL'=>'Toggle enable','ICON'=>'retweet','LINK'=>url_for('profiles/study/center/toggle/'.$username.'/[PREFIX]/[SITE_ID]/[PROFILE_ID]'),'COLOR'=>'#D32646'); //lightblue
	while ($row = db_nextrow($rs)){
		$row['D_CODE']=$profili[$row['CODE']]['descrizione'];
		if($jqGrid) {
			if ($row['ACTIVE']==1){
				$row['ACTIVE'] = '<i class="bigger-150 fa fa-check-circle green"></i>';
			}else{
				$row['ACTIVE'] = '<i class="bigger-150 fa fa-times-circle red"></i>';
			}
			$row['_ACTIONS_']=_data_actions($actions,$row);
			$row[JQGID] = $row['USERID']."|".$row['PREFIX']."|".$row['SITE_ID']."|".$row['PROFILE_ID'];
			$retval[] = $row;
		}else{
			//$retval[$row['USERID']] = $row;
			$retval[]= $row;
		}
	}
	_data_parse($retval, $count, $jqGrid); //-->Qui gestisco l'output json opportuno, oppure non faccio nulla (e quindi ritorno il retval di questo metodo...
	return $retval;
}
function _user_load_privilege($username,$prefix,$siteid,$profileid,$jqGrid=false,$force_array=false){
	$retval = array();
	$bind = array();
	$bind['USERID']=$username;
	$bind['PREFIX']=$prefix;
	$bind['SITEID']=$siteid;
	$bind['PROFILEID']=$profileid;
	$SQL = "SELECT
							 USERID
							,SITE_ID
							,STUDY_PREFIX
							,PROFILE_ID AS USER_PROFILE_ID
							,ACTIVE
							FROM
							  ACM_USERS_ASSOC 
							WHERE
								userid = :USERID
							AND STUDY_PREFIX = :PREFIX
							AND SITE_ID = :SITEID
							AND PROFILE_ID = :PROFILEID
					";
	// echo "<pre>";
	// print_r($bind);
	// echo $SQL;
	// echo "</pre>";
	// die();
	if(!$jqGrid){
		$rs = db_query_bind($SQL,$bind);
		if ($row = db_nextrow($rs)){
			$retval = $row;
		}
	}else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('USERID','SITE_ID','STUDY_PREFIX','USER_PROFILE_ID');
		$retval=_data_retrieve($jqGrid,$SQL,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	if(!$force_array && isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else{
		return $retval;
	}
}
function user_privileges_form_validate(){
	$retval = true;
	$row = $_POST;

	if (!isset($row['STUDY_PREFIX'])||!$row['STUDY_PREFIX']){
		common_add_message(t("Please specify the field ")."'".t("STUDY")."'",WARNING);
		$retval = false;
	}
	if (!isset($row['SITE_ID'])||!$row['SITE_ID']){
		common_add_message(t("Please specify the field ")."'".t("SITE/CENTER")."'",WARNING);
		$retval = false;
	}
	if (!isset($row['USER_PROFILE_ID'])||!$row['USER_PROFILE_ID']){
		common_add_message(t("Please specify the field ")."'".t("PROFILE")."'",WARNING);
		$retval = false;
	}
	return $retval;

}
function user_privileges_form_submit($username, $list,$row=false,$verbose=true){
	$retval = false;
	if(!$row){
		$row = $_POST;
	}


	unset($row['submit-button']);
	unset($row['reset-button']);

	$action = ACT_INSERT;
	// echo "<pre>";
	// print_r($row);
	foreach ($list as $up){
		//print_r($up);
		if ($up['USERID']==$row['USERID'] && $up['SITE_ID']==$row['SITE_ID'] && $up['PREFIX']==$row['STUDY_PREFIX'] && $up['PROFILE_ID']==$row['USER_PROFILE_ID']){
			$action = ACT_MODIFY;
			break;
		}
	}
	// echo "ACTION: ".$action;
	// echo "</pre>";
	// die();
	if($action==ACT_INSERT){
		//echo "<pre>E' una insert</pre>";
		//var_dump($list);
		//INSERISCO/MODIFICO IN USERS_STUDIES
		$table = "USERS_STUDIES";
		$action = ACT_INSERT;
		$user_studies_row=array();
		$user_studies_row['USERID']=$row['USERID'];
		$user_studies_row['STUDY_PREFIX']=$row['STUDY_PREFIX'];
		$user_studies_row['ACTIVE']=$row['ACTIVE'];
		$user_studies_list=_user_load_studies($username);
		foreach ($user_studies_list as $up){
			if ($up['USERID']==$user_studies_row['USERID'] && $up['STUDY_PREFIX']==$user_studies_row['STUDY_PREFIX']){
				$action = ACT_MODIFY;
				break;
			}
		}
		$user_studies_row = common_booleanCheckBox($user_studies_row, 'ACTIVE');
		//common_add_message(print_r($row,true), INFO);
		$keys = array('USERID','STUDY_PREFIX');
		if (db_form_updatedb($table, $user_studies_row, $action, $keys)){
			if ($action == ACT_INSERT){
				if($verbose){
					common_add_message(t("user correctly associated to the Product Instance."), INFO);
				}
			}
			// 		else{
			// 			common_add_message(t("user correctly associated to the study"), INFO);
			// 		}
			$retval = true;
		}
		else{
			if($verbose){
				common_add_message("Error: ", ERROR);
			}
			return false;

		}

		//INSERISCO/MODIFICO IN USERS_SITES
		$table = "USERS_SITES";
		$action = ACT_INSERT;
		$user_sites_row=array();
		$user_sites_row['USERID']=$row['USERID'];
		$user_sites_row['SITE_ID']=$row['SITE_ID'];
		$user_sites_list=_user_load_sites($username);
		foreach ($user_sites_list as $up){
			if ($up['USERID']==$user_sites_row['USERID'] && $up['SITE_ID']==$user_sites_row['SITE_ID']){
				$action = ACT_MODIFY;
				break;
			}
		}
		// echo "<pre>";
		// print_r($user_sites_row);
		// echo "</pre>";
		$keys = array('USERID','SITE_ID');
		if (db_form_updatedb($table, $user_sites_row, $action, $keys)){
			if ($action == ACT_INSERT){
				if($verbose){
					common_add_message(t("user correctly associated to the site."), INFO);
				}
			}
			// 		else{
			// 			common_add_message(t("user correctly associated to the study"), INFO);
			// 		}
			$retval = true;
		}
		else{
			if($verbose){
				common_add_message("Error: ", ERROR);
			}
			return false;

		}

		//INSERISCO/MODIFICO IN USERS_PROFILES
		$table = "USERS_PROFILES";
		$action = ACT_INSERT;
		$user_profiles_row=array();
		$user_profiles_row['USERID']=$row['USERID'];
		$user_profiles_row['PROFILE_ID']=$row['USER_PROFILE_ID'];
		$user_profiles_row['ACTIVE']=$row['ACTIVE'];
		$user_profiles_list=_user_load_profiles($username);
		foreach ($user_profiles_list as $up){
			if ($up['USERID']==$user_profiles_row['USERID'] && $up['PROFILE_ID']==$user_profiles_row['PROFILE_ID']){
				$action = ACT_MODIFY;
				break;
			}
		}
		$user_profiles_row = common_booleanCheckBox($user_profiles_row, 'ACTIVE');
		$keys = array('USERID','PROFILE_ID');
		if (db_form_updatedb($table, $user_profiles_row, $action, $keys)){
			if ($action == ACT_INSERT){
				if($verbose){
					common_add_message(t("user correctly associated to the profile."), INFO);
				}
			}
			// 		else{
			// 			common_add_message(t("user correctly associated to the study"), INFO);
			// 		}
			$retval = true;
		}
		else{
			if($verbose){
				common_add_message("Error: ", ERROR);
			}
			return false;

		}

	}


	$table = "SITES_STUDIES";
	$action = ACT_INSERT;
	$sites_studies_row=array();
	$sites_studies_row['SITE_ID']=$row['SITE_ID'];
	$sites_studies_row['STUDY_PREFIX']=$row['STUDY_PREFIX'];
	$sites_studies_row['ACTIVE']=$row['ACTIVE'];

	$bind = array();
	$bind['KEY'] = $row['STUDY_PREFIX'];
	$select = "SELECT ss.*,s.CODE,s.DESCR FROM SITES_STUDIES ss,SITES s WHERE ss.SITE_ID=s.ID AND ss.STUDY_PREFIX=:KEY ";
	$rs = db_query_bind($select,$bind);
	while ($site_study_assoc = db_nextrow($rs)){
		$list[] = $site_study_assoc;
	}

	//$list = _study_load_centers($row['STUDY_PREFIX'], false);
	foreach ($list as $up) {
		if ($up['SITE_ID'] == $sites_studies_row['SITE_ID'] && $up['STUDY_PREFIX'] == $sites_studies_row['STUDY_PREFIX']) {
			$action = ACT_MODIFY;
			break;
		}
	}
	$sites_studies_row = common_booleanCheckBox($sites_studies_row, 'ACTIVE');
	// common_add_message(print_r($row,true), INFO);
	$keys = array('SITE_ID', 'STUDY_PREFIX');
	if (db_form_updatedb($table, $sites_studies_row, $action, $keys)) {
		if ($action == ACT_INSERT) {
			if($verbose){
				common_add_message(t("New product instance/center inserted correctly."), INFO);
			}
		} else {
			if($verbose){
				common_add_message(t("Existing product instance/center modified."), INFO);
			}
		}
		$retval = true;
	}
	else{
		if($verbose){
			common_add_message("Error: ", ERROR);
		}
		return false;

	}

	$table = "USERS_SITES_STUDIES";
	$action = ACT_INSERT;

	//var_dump($row);
	foreach ($list as $up){
		// 		var_dump($up);
		if ($up['USERID']==$row['USERID'] && $up['SITE_ID']==$row['SITE_ID'] && $up['PREFIX']==$row['STUDY_PREFIX'] && $up['PROFILE_ID']==$row['USER_PROFILE_ID']){
			$action = ACT_MODIFY;
			break;
		}
	}

	$row = common_booleanCheckBox($row, 'ACTIVE');
	//common_add_message(print_r($row,true), INFO);
	$keys = array('USERID','SITE_ID','STUDY_PREFIX','USER_PROFILE_ID');
	// 	var_dump($row);
	// 	var_dump($action);
	// 	die();
	if (db_form_updatedb($table, $row, $action, $keys)){
		if ($action == ACT_INSERT){
			if($verbose){
				common_add_message(t("New user privilege inserted correctly."), INFO);
			}
		}else{
			if($verbose){
				common_add_message(t("Existing user privilege modified."), INFO);
			}
		}
		$retval = true;
	}
	else{
		if($verbose){
			common_add_message("Error: ", ERROR);
		}
		return false;

	}

	//prima di modificare utenti_gruppiu controllo se sono rimasti altri profili con stesso id attivi per questo utente/sito per non disabilitare UTENTI_GRUPPIU
	$rs = db_query_bind("SELECT COUNT(*) AS CONTO FROM USERS_SITES_STUDIES WHERE USERID=:USERID AND STUDY_PREFIX=:STUDY_PREFIX AND USER_PROFILE_ID=:USER_PROFILE_ID AND ACTIVE=1",$row);
	$_row = db_nextrow($rs);
	$do_not_update_utenti_gruppiu=$_row['CONTO'];
	//INSERISCO/MODIFICO IN UTENTI_GRUPPIU
	$table = "UTENTI_GRUPPIU";
	$action = ACT_INSERT;
	$utenti_gruppiu_row=array();
	$utenti_gruppiu_row['USERID']=$row['USERID'];
	$utenti_gruppiu_row['ID_GRUPPOU']=$row['USER_PROFILE_ID'];
	$utenti_gruppiu_row['ABILITATO']=$row['ACTIVE'];
	$utenti_gruppiu_list=_user_load_gruppiu($row['USERID']);

	foreach ($utenti_gruppiu_list as $up){
		if ($up['USERID']==$utenti_gruppiu_row['USERID'] && $up['ID_GRUPPOU']==$utenti_gruppiu_row['ID_GRUPPOU']){
			$action = ACT_MODIFY;
			break;
		}
	}
	$utenti_gruppiu_row = common_booleanCheckBox($utenti_gruppiu_row, 'ABILITATO');
	//common_add_message(print_r($row,true), INFO);
	$keys = array('USERID','ID_GRUPPOU');
	if(!$do_not_update_utenti_gruppiu||$row['ACTIVE']==1){
		if (db_form_updatedb($table, $utenti_gruppiu_row, $action, $keys)){
			if ($action == ACT_INSERT){
				if($verbose){
					common_add_message(t("user correctly associated to the Product Instance."), INFO);
				}
			}else {
				if($verbose){
					common_add_message ( t ( "Existing user privilege modified." ), INFO );
				}
			}
			$retval = true;
		}
		else{
			$retval =false;
			return $retval;
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
function user_privileges_form($row,$username){
	$m = UIManager::getInstance();
	$output = "";
	$output .= t("Add new / edit user privilege");
	$output .= '<form class="form-horizontal" role="form" method="post" action="#">';

	$studies = _study_list();
	$optstudies = array();
	//var_dump($studies);
	foreach ($studies as $k=>$p){
		$optstudies[$p['PREFIX']] = $p['PREFIX']." - ".$p['DESCR'];
	}

	//$profiles = _profile_list_per_study();
	//$optprofiles = array();
	// 	foreach ($profiles as $k=>$p){
	// 		$optprofiles[$p['ID']] = $p['descrizione'];
	// 	}
	$output .= ''.$m->dsp_getTextField('USER ID', 'USERID', '', '', true, $row['USERID']);
	$onaction= 'onchange="changeStudyPrefix_GetProfilesListPerStudy();changeStudyPrefix_GetSitesListPerStudyAndUser();"';
	$output .= ''.$m->dsp_getSelectField('PRODUCT INSTANCE', 'STUDY_PREFIX', '', '', false, $row['STUDY_PREFIX'], $optstudies,$onaction,true);
	$output .= ''.$m->dsp_getSelectField('SITE/CENTER', 'SITE_ID', '', '', false, $row['SITE_ID'], array(),false,true);
	$output .= ''.$m->dsp_getSelectField('PROFILE', 'USER_PROFILE_ID', '', '', false, $row['USER_PROFILE_ID'], array(),false,true);
	$output .= ''.$m->dsp_getCheckbox('STATUS', 'ACTIVE', '', 'Enabled', false, false, $row).'';
	$output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
	$output .= '</form>';


	return $output;
}
function _user_load_gruppiu($username,$jqGrid=false){
	$retval = array();
	$select="SELECT * FROM UTENTI_GRUPPIU WHERE USERID=:KEY";
	$bind = array();
	$bind['KEY']=$username;
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('USERID','ID_GRUPPOU');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//var_dump($retval);
	return $retval;
}
function _user_load_studies($username,$jqGrid=false){
	$retval = array();
	$select="SELECT * FROM USERS_STUDIES WHERE USERID=:KEY";
	$bind = array();
	$bind['KEY']=$username;
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('STUDY_PREFIX','USERID');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//var_dump($retval);
	return $retval;
}
function _user_load_sites($username,$jqGrid=false){
	$retval = array();
	$select="SELECT * FROM USERS_SITES WHERE USERID=:KEY";
	$bind = array();
	$bind['KEY']=$username;
	if(!$jqGrid){
		$rs = db_query_bind($select,$bind);
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('SITE_ID','USERID');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//var_dump($retval);
	return $retval;
}
function _user_load_profiles($username,$jqGrid=false){
	$retval = array();
	$select="SELECT * FROM USERS_PROFILES WHERE USERID=:KEY";
	$bind = array();
	$bind['KEY']=$username;
	$rs = db_query_bind($select,$bind);
	if(!$jqGrid){
		while ($row = db_nextrow($rs)){
			$retval[] = $row;
		}
	}
	else{
		$actions = array();
		$ord_override=array();
		$checkicons=array();
		$pkeys=array('PROFILE_ID','USERID');
		$retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
	}
	//var_dump($retval);
	return $retval;
}

function toggle_user($username,$force_disable=false){ //STSANSVIL-733 disabilita utente con toggle

	//Toggle enable status
	$my_row=array();
	$row =_user_load_user($username);
	//var_dump($row);
	if ($row['STATUS']=="1"){
		$my_row['ABILITATO']="0";
		$enab = "DISABLED";
	}else{
		$my_row['ABILITATO']="1";
		$enab = "ENABLED";
	}
	if($force_disable){
		$my_row['ABILITATO']="0";
		$enab = "DISABLED";
	}
	$my_row['USERID'] = $row['USERID'];
	//var_dump($my_row);
	$retval = true;
	$table = "UTENTI";
	$action = ACT_MODIFY;
	$keys = array('USERID');
	//common_add_message(print_r($row,true),INFO);
	if (db_form_updatedb($table, $my_row, $action, $keys)){
		//common_add_message("Privilege $enab", INFO);
	}else{
		//common_add_message("Error during privilege toggling", ERROR);
		$retval = false;
	}
	if($retval){
		db_commit();

	}
	if(isAjax()){
		echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
		db_close();die();
	}
	else {
		db_close();
		return $retval;
	}
}

/**RIPRISTINATA FUNZIONE ELIMINATA TRAMITE MERGE - VMAZZEO 22.01.2016*/
function _user_is_admin_user($key){ //GENHD-129 added flag in user form to allow access to acm and study inizialization to the user
	$retval = array();
	$bind = array();
	$bind['KEY'] = $key;
	$rs = db_query_bind("select ugu.userid, ugu.id_gruppou, ugu.abilitato from utenti_gruppiu ugu, gruppiu gu, ana_gruppiu agu, utenti_visteammin uva where gu.id_gruppou=agu.id_gruppou and ugu.id_gruppou=gu.id_gruppou and gu.abilitato=1 and upper(agu.nome_gruppo) in ('PROFILO AMMINISTRATORE','ACM_ADMIN') and uva.userid=ugu.userid and ugu.userid=:KEY",$bind);
	//echo "<b>select ugu.userid, ugu.id_gruppou, ugu.abilitato from utenti_gruppiu ugu, gruppiu gu, ana_gruppiu agu, utenti_visteammin uva where gu.id_gruppou=agu.id_gruppou and ugu.id_gruppou=gu.id_gruppou and gu.abilitato=1 and agu.nome_gruppo='Profilo amministratore' and uva.userid=ugu.userid and ugu.userid=".$bind['KEY']."</b>";
	if ($row = db_nextrow($rs)){
		$retval = $row;
	}
	// echo "<pre>";
	// print_r($retval);
	// echo "</pre>";
	return $retval;
}



function _user_check_profile($username,$profile_code){
	$retval = false;
	$bind = array();
	$bind['USERID'] = $username;
	$bind['PROFILE_CODE'] = $profile_code;
	$rs = db_query_bind("SELECT count(*) as CONTO FROM ACM_USERS_ASSOC 
						 WHERE
						 userid =:USERID and profile_code=:PROFILE_CODE and ACTIVE=1",$bind);
	//echo \"<b>select ugu.userid, ugu.id_gruppou, ugu.abilitato from utenti_gruppiu ugu, gruppiu gu, ana_gruppiu agu, utenti_visteammin uva where gu.id_gruppou=agu.id_gruppou and ugu.id_gruppou=gu.id_gruppou and gu.abilitato=1 and agu.nome_gruppo='Profilo amministratore' and uva.userid=ugu.userid and ugu.userid=\".$bind['KEY'].\"</b>\";
	$row = db_nextrow($rs);

	$retval = $row['CONTO']==1 ? true : false;
	// echo \"<pre>\";
	// print_r($retval);
	// echo \"</pre>\";
	return $retval;
}

function _user_profile_pages_get_legend(){
	global $profili;
	$legend_items=array();
	foreach($profili as $instance => $profiles){
		foreach($profiles as $profile=>$descr) {
			$legend_item['icon'] = "";
			$legend_item['testo'] = "<b>".$profile."</b> : ".$descr['descrizione'];
			$legend_items[] = $legend_item;
		}
	}
	/*
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
        $legend_items[]=$legend_item;*/
	return $legend_items;
}
?>
