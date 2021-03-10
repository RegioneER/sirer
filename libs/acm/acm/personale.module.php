<?php

function personale_init(){
    //PI
    dispatch('/strutture/PI', 'personale_PI_page_new');
    dispatch('/strutture/PI/new', 'personale_PI_page_new');
    dispatch_post('/strutture/PI/new', 'personale_PI_page_new');
    dispatch('/strutture/PI/list/:id_azienda', 'personale_PI_page_list');
    dispatch('/strutture/PI/edit/:id_azienda/:cf', 'personale_PI_page_edit');
    dispatch_post('/strutture/PI/edit/:id_azienda/:cf', 'personale_PI_page_edit');
    dispatch('/strutture/get_list_pi/:jqGrid/:id_azienda','_personale_list_PI');
    dispatch('/strutture/get_personale_da_cf/:cf/:tokenInput','_personale_load_da_cf');
    //Afferenti
    dispatch('/strutture/personale', 'personale_perso_page_new');
    dispatch('/strutture/personale/new', 'personale_perso_page_new');
    dispatch('/strutture/personale/list/:id_azienda/:id_struttura', 'personale_perso_page_list');
    dispatch_post('/strutture/personale/new', 'personale_perso_page_new');
    dispatch('/strutture/personale/edit/:cf', 'personale_perso_page_edit');
    dispatch_post('/strutture/personale/edit/:cf', 'personale_perso_page_edit');
    dispatch('/strutture/get_list_personale/:jqGrid/:id_azienda/:id_struttura','_personale_list_personale');

    dispatch('/strutture/personale/elimina/:id_azienda/:cf','personale_elimina');
    dispatch('/strutture/personale/disabilita/:id_azienda/:cf','personale_disabilita');

}

function personale_sidebar($sideBar){
    $itm2=new SideBarItem(new Link(t("Personale"), "building-o", "#"));
    //personale
    $itm2->addItem(new SideBarItem(new Link(t("Nuova Persona"), "plus", url_for('/strutture/PI/new')), null, UIManager::_checkActive('/strutture/PI/new')));
    $itm2->addItem(new SideBarItem(new Link(t("Lista personale"), "list", url_for('/strutture/PI/list')), null, UIManager::_checkActive('/strutture/PI/list')));
    $sideBar->addItem($itm2);

    return $sideBar;
}

function personale_breadcrumb($paths)
{

    if(UIManager::_checkActive('/strutture/PI')){
        $paths[]=array(t("PI"), t("PI"), url_for('/strutture/PI/list'));
        if(UIManager::_checkActive('/strutture/PI/new')){
            $paths[]=array(t("Nuova PI"), t("Nuova PI"), url_for('/strutture/PI/new'));

        }
        if(UIManager::_checkActive('/strutture/PI/edit')){
            $paths[]=array(t("Modifica PI"), t("Modifica PI"), url_for('/strutture/PI/edit'));
        }
        if(UIManager::_checkActive('/strutture/PI/list')){
            $paths[]=array(t("Lista personale"), t("Lista personale"), url_for('/strutture/PI/list'));
        }
    }

    return $paths;
}

function personale_getPageTitle($page_title){

    if(UIManager::_checkActive('/strutture/PI')){
        $page_title=t("PI");
        if(UIManager::_checkActive('/strutture/PI/new')){
            $page_title=t("Nuova Persona");

        }
        if(UIManager::_checkActive('/strutture/PI/edit')){
            $page_title=t("Modifica PI");

        }
        if(UIManager::_checkActive('/strutture/PI/list')){
            $page_title=t("Lista personale");
        }
    }
    if(UIManager::_checkActive('/strutture/personale')){
        $page_title=t("Personale");
        if(UIManager::_checkActive('/strutture/personale/new')){
            $page_title=t("Nuova persona");

        }
        if(UIManager::_checkActive('/strutture/personale/edit')){
            $page_title=t("Modifica persona");

        }
        if(UIManager::_checkActive('/strutture/personale/list')){
            $page_title=t("Lista personale");
        }
    }
    return $page_title;
}



//////////////////////////////////// PI ///////////////////////////////////

function personale_PI_form($row,$action){
    $output = "";
    $aziende = _strutture_list_aziende(false);
    $opt_aziende = array();
    foreach($aziende as $azrow){
        $opt_aziende[$azrow['ID_AZIENDA']] = $azrow['DESCRIZIONE_AZIENDA'];
    }
    $readonly=false;
    if($action==ACT_MODIFY){
        $readonly=true;
    }
    $m = UIManager::getInstance();
    $output .= '<form class="form-horizontal" role="form" method="post" action="#">';
    $output .= ''.$m->dsp_getTextField('Codice Fiscale', 'CF', '', '', $readonly, false,$row,true).'';
    $output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'CF', $row['CF'], false).'';
    $output .= ''.$m->dsp_getTextField('Nome', 'NOME', '', '', false, false,$row,true).'';
    $output .= ''.$m->dsp_getTextField('Cognome', 'COGNOME', '', '', false, false,$row,true).'';
    $output .= ''.$m->dsp_getSelectField('Azienda', 'ID_AZIENDA', '', '', $readonly, $row['ID_AZIENDA'],$opt_aziende, null, true).'';
    if($readonly){
        $output .= ''.$m->dsp_getHiddenField('ID_AZIENDA', $row['ID_AZIENDA'], false).'';
    }
    $output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'ID_AZIENDA', $row['ID_AZIENDA'], false).'';
    $output .= ''.$m->dsp_getTextField('Ruolo', 'RUOLO', '', '', false, false,$row,false).'';
    $output .= ''.$m->dsp_getTextField('Qualifica', 'UO_DESCR', '', '', false, false,$row,false).'';

    $output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
    $output .= '</form>';
    return $output;
}
function personale_PI_form_validate($action){
    $retval = true;
    $row = $_POST;
    if (!$row['CF']){
        common_add_message(t("Please specify the field ")."'".t("Codice Fiscale")."'",WARNING);
        $retval = false;
    }
    if (!$row['NOME']){
        common_add_message(t("Please specify the field ")."'".t("Nome")."'",WARNING);
        $retval = false;
    }
    if (!$row['COGNOME']){
        common_add_message(t("Please specify the field ")."'".t("Cognome")."'",WARNING);
        $retval = false;
    }
    if (strlen($row['CF'])>16){
        common_add_message(t("Verificare il campo ")."'".t("Codice Fiscale")."'",WARNING);
        $retval = false;
    }
    if (!$row['ID_AZIENDA']){
        common_add_message(t("Please specify the field ")."'".t("Azienda")."'",WARNING);
        $retval = false;
    }
    if($action==ACT_INSERT) {
        $personale_exits = _personale_load_PI($row['ID_AZIENDA'], $row['CF']);
        if (count($personale_exits)) {
            common_add_message("Persona già presente in azienda", ERROR);
            $retval = false;
        }
    }
    return $retval;
}
function personale_PI_form_submit($action){
    $retval = false;
    $row = $_POST;
    unset($row['submit-button']);
    unset($row['reset-button']);

    //$row = common_booleanCheckBox($row, 'ACTIVE');

    $row['COGNOME'] = trim($row['COGNOME']);
    $row['NOME'] = trim($row['NOME']);
    $row['CF'] = strtoupper(trim($row['CF']));
    $table = "ANA_PI";


    if (db_form_updatedb($table, $row, $action, array('CF','ID_AZIENDA'))){
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

function personale_PI_page_new(){
    $output = "";
    /*
     $d = Dispatcher::getInstance();
    $d->personale_new();
    return html($d->dsp_getPageContent());
    */
    //$m = UIManager::getInstance();
    $row = array();
    $row['ID']="";
    if ($_POST){
        if (personale_PI_form_validate(ACT_INSERT)){
            if (personale_PI_form_submit(ACT_INSERT)){
                header("location: ".url_for('/strutture/PI/list'));
                die();
            }else{
                $output .= t("An error occurred during center creation.");
            }
        }
        $row = $_POST;
    }
    $output .= '<form class="form-horizontal" role="form" method="post" action="#">
				';
    $output .= personale_PI_form($row,ACT_INSERT);
    $output .= '
			</form>';
    return html($output);
}

function personale_PI_page_edit($azienda_id, $cf){
    $output = "";
    $row =_personale_load_PI($azienda_id, $cf);
    if ($_POST){
        if (personale_PI_form_validate(ACT_MODIFY)){
            if (personale_PI_form_submit(ACT_MODIFY)){
                header("location: ".url_for('/strutture/PI/list'));
                die();
            }else{
                $output .= t("An error occurred during center update.");
            }
        }
        $row = $_POST;
    }
    $output .= personale_PI_form($row,ACT_MODIFY);
    return html($output);
}


function personale_PI_page_list(){
    $output = '';
    $m = UIManager::getInstance();
    //$list = _personale_list_strutture();
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/strutture/get_list_pi/jqGrid');
    $caption=""; //t("Lista strutture");
    $labels=array('CF'=>array('NAME'=>'CF','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'COGNOME'=>array('NAME'=>'COGNOME','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'NOME'=>array('NAME'=>'NOME','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'ID AZIENDA'=>array('NAME'=>'ID_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'DENOMINAZIONE AZIENDA'=>array('NAME'=>'DESCRIZIONE_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'PERSONALE ABILITATO'=>array('NAME'=>'ABILITATO','TYPE'=>'CHECK')
    );
    $actions = true;
    $output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption,$labels,$actions);
    //$output .=$m->dsp_getTable($columns,$list);
    return html($output);
}

function _personale_list_PI($jqGrid=false){
    //$sites = _user_load_sites($_SERVER['REMOTE_USERID']);
    //$profiles = _user_load_profiles($_SERVER['REMOTE_USERID']);
    //$gruppiu = _user_load_gruppiu($_SERVER['REMOTE_USERID']);
    $cuser = _user_load_user($_SERVER['REMOTE_USERID']);
    //var_dump($cuser['GRUPPI']);
    //var_dump($cuser['PROFILI']);
    //$retval = array();
    //Actions
    $actions = array();
    $actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/strutture/PI/edit/[ID_AZIENDA]/[CF]'));
    $actions[] = array('LABEL'=>'Add user','ICON'=>'user','LINK'=>url_for('/user/new/[ID_AZIENDA]/[CF]'),'COLOR'=>'#69AA46','NOT_CONDITION'=>'[FLAG_UTENTE_CREATO]');//STSANPRJS-570
    $actions[] = array('LABEL'=>'View user','ICON'=>'user','LINK'=>url_for('/user/view/[CF]'),'COLOR'=>'#337ab7','CONDITION'=>'[FLAG_UTENTE_CREATO]');//STSANPRJS-570
    $actions[] = array('LABEL'=>'Delete','ICON'=>'trash','LINK'=>'javascript:deletePersonale(\'[ID_AZIENDA]\',\'[CF]\')','COLOR'=>'#FA3A3A','NOT_CONDITION'=>'[FLAG_UTENTE_CREATO]'); //STSANSVIL-733
    $actions[] = array('LABEL'=>'Disable','ICON'=>'ban','LINK'=>'javascript:disablePersonale(\'[ID_AZIENDA]\',\'[CF]\',\'[TOGGLE_ABILITATO]\')','COLOR'=>'#FA3A3A','CONDITION'=>'[TOGGLE_ABILITATO]'); //STSANSVIL-733
    $actions[] = array('LABEL'=>'Enable','ICON'=>'user','LINK'=>'javascript:disablePersonale(\'[ID_AZIENDA]\',\'[CF]\',\'[TOGGLE_ABILITATO]\')','COLOR'=>'#69AA46','NOT_CONDITION'=>'[TOGGLE_ABILITATO]'); //STSANSVIL-733

    //Queries
    //$select="SELECT pi.*, s.DESCRIZIONE_AZIENDA FROM ANA_PI pi, (select distinct ID_AZIENDA, DESCRIZIONE_AZIENDA from ANA_STRUTTURE) s WHERE pi.ID_AZIENDA = s.ID_AZIENDA ";
    $select="SELECT pi.*,pi.abilitato as TOGGLE_ABILITATO, s.DESCRIZIONE_AZIENDA, case when u.USERID IS NULL then 0 else 1 end as FLAG_UTENTE_CREATO FROM ANA_PI pi, (select distinct ID_AZIENDA, DESCRIZIONE_AZIENDA from ANA_STRUTTURE) s, UTENTI u WHERE pi.ID_AZIENDA = s.ID_AZIENDA and pi.CF=u.USERID(+) ";//--AND PI.ABILITATO=1 STSANSVIL-733

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
        $select .= " AND pi.ID_AZIENDA IN ($azFilter)";
    }else{
        //$select .= " AND pi.ID_AZIENDA = '0' "; //Non mostro nulla (in teoria), poichè non ho centri
    }
    //}
    // var_dump($select);

    $bind=array();
    if(!$jqGrid){ //VAXMR-297
        $select.=" ORDER BY COGNOME, NOME";
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
        $retval = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('CF'),array('ABILITATO'),$actions,false);
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

function _personale_load_PI($id_azienda, $key, $jqGrid=false){
    $retval = array();
    $select="SELECT * FROM ANA_PI WHERE ID_AZIENDA = :AZIENDA AND CF = :KEY ";//AND ABILITATO=1 STSANSVIL-733 nuove richieste
    $bind['AZIENDA'] = $id_azienda;
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

function _personale_load_da_cf($cf, $tokenInput=false){
    $retval = array();
    $select="SELECT * FROM ANA_PI WHERE UPPER(CF) LIKE UPPER(:CF) ";//AND ABILITATO=1 STSANSVIL-733 nuove richieste
    $bind['CF'] = $cf;
    $rs = db_query_bind($select,$bind);
    $i=0;
    while ($row = db_nextrow($rs)){
        if(!$tokenInput) {
            $retval[] = $row;
        }
        else{
            $retval[$i]['id']=$row['CF'];
            $retval[$i]['title']=$row['NOME']." ".$row["COGNOME"];
        }
        $i++;
    }
    /*var_dump($tokenInput);
    var_dump($retval);*/
    if(isAjax()){
        echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
        db_close();die();
    }
    else{
        return $retval;
    }
    return $retval;
}

//////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////// PERSONALE ///////////////////////////////////

function personale_pers_form($row){
    $output = "";
    $m = UIManager::getInstance();
    $output .= '<form class="form-horizontal" role="form" method="post" action="#">';
    $output .= ''.$m->dsp_getHiddenField('ID', false, $row).'';
    $output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'ID', $row['ID'], false).'';
    $output .= ''.$m->dsp_getTextField('Denominazione', 'DESCRIZIONE', '', '', false, false,$row,true).'';
    $output .= ''.$m->dsp_getTextField('ID Azienda.', 'ID_AZIENDA', '', '', false, false,$row,true).'';
    $output .= ''.$m->dsp_getTextField('Descrizione Azienda', 'DESCRIZIONE_AZIENDA', '', '', false, false,$row).'';
    $output .= ''.$m->dsp_getTextField('Centro', 'CENTRO', '', '', false, false,$row).'';
    $output .= ''.$m->dsp_getCheckbox('Visualizza', 'VISUALIZZA', '', 'Enabled', false, false, $row).'';
    $output .= ''.$m->dsp_getCheckbox('Privata', 'PRIVATA', '', 'Enabled', false, false, $row).'';
    $output .= ''.$m->dsp_getCheckbox('ULSS', 'ULSS', '', 'Enabled', false, false, $row).'';
    $output .= ''.$m->dsp_getCheckbox('IRCSS', 'IRCSS', '', 'Enabled', false, false, $row).'';
    $output .= ''.$m->dsp_getCheckbox('AOUI', 'AOUI', '', 'Enabled', false, false, $row).'';
    $output .= ''.$m->dsp_getCheckbox('OLD', 'OLD', '', 'Enabled', false, false, $row).'';
    $output .= ''.$m->dsp_getTextField('CTO_CRMS', 'CTO_CRMS', '', '', false, false,$row).'';
    $output .= ''.$m->dsp_getTextField('ID Regione', 'ID_REGIONE', '', '', false, false,$row).'';


    $output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
    $output .= '</form>';
    return $output;
}
function personale_pers_form_validate(){
    $retval = true;
    $row = $_POST;
    if (!$row['DESCRIZIONE']){
        common_add_message(t("Please specify the field ")."'".t("Name")."'",WARNING);
        $retval = false;
    }
    return $retval;
}
function personale_pers_form_submit($action){
    $retval = false;
    $row = $_POST;
    unset($row['submit-button']);
    unset($row['reset-button']);

    $row = common_booleanCheckBox($row, 'ACTIVE');

    $row['DESCRIZIONE'] = trim($row['DESCRIZIONE']);
    $table = "ANA_STRUTTURE";

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

function personale_pers_page_new(){
    $output = "";
    /*
     $d = Dispatcher::getInstance();
    $d->personale_new();
    return html($d->dsp_getPageContent());
    */
    //$m = UIManager::getInstance();
    $row = array();
    $row['ID']="";
    if ($_POST){
        if (personale_form_validate(ACT_INSERT)){
            if (personale_form_submit(ACT_INSERT)){
                header("location: ".url_for('/strutture/list'));
                die();
            }else{
                $output .= t("An error occurred during center creation.");
            }
        }
        $row = $_POST;
    }
    $output .= '<form class="form-horizontal" role="form" method="post" action="#">
				';
    $output .= personale_form($row);
    $output .= '
			</form>';
    return html($output);
}

function personale_pers_page_edit($personale_id){
    $output = "";
    $row =_personale_load_struttura($personale_id);
    if ($_POST){
        if (personale_form_validate(ACT_MODIFY)){
            if (personale_form_submit(ACT_MODIFY)){
                header("location: ".url_for('/strutture/list'));
                die();
            }else{
                $output .= t("An error occurred during center update.");
            }
        }
        $row = $_POST;
    }
    $output .= personale_form($row);
    return html($output);
}


function personale_pers_page_list(){
    $output = '';
    $m = UIManager::getInstance();
    //$list = _personale_list_strutture();
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/strutture/get_list_strutture/jqGrid');
    $caption=t("Lista strutture");
    $labels=array('ID'=>array('NAME'=>'ID','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'DENOMINAZIONE'=>array('NAME'=>'DESCRIZIONE','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'ID AZIENDA'=>array('NAME'=>'ID_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'DENOMINAZIONE AZIENDA'=>array('NAME'=>'DESCRIZIONE_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'ID REGIONE'=>array('NAME'=>'ID_REGIONE','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'IRCSS'=>array('NAME'=>'IRCSS','TYPE'=>'CHECK','SORT' => 1)
    );
    $actions = true;
    $output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption,$labels,$actions);
    //$output .=$m->dsp_getTable($columns,$list);
    return html($output);
}

function _personale_list_personale($jqGrid=false){
    //$retval = array();
    //Actions
    $actions = array();
    $actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/strutture/edit/[ID]'));
    //$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>url_for('/strutture/delete/[ID]'),'COLOR'=>'#FA3A3A');//VAXMR-154
    //Queries
    $select="SELECT * FROM ANA_STRUTTURE";
    if(!$jqGrid){ //VAXMR-297
        $select.=" ORDER BY DESCRIZIONE";
        $rs = db_query_bind($select,$bind);
        while ($row = db_nextrow($rs)){
            $retval[] = $row;
        }
    }
    else{
        //$select_count="SELECT COUNT(*) AS CONTO FROM SITES";
        //die($select);
        $bind=array();
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

function _personale_load_personale($key, $jqGrid=false){
    $retval = array();
    $select="SELECT * FROM ANA_STRUTTURE WHERE ID = :KEY";
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


//////////////////////////////////////////////////////////////////////////////////
function personale_disabilita($azienda_id,$cf){ //STSANSVIL-733
    $row =_personale_load_PI($azienda_id, $cf);
    //var_dump($row);
    if ($row['ABILITATO']=="1"){
        $my_row['ABILITATO']="0";
        $force_disable=true;
    }else{
        $my_row['ABILITATO']="1";
    }
    $my_row['CF'] = $row['CF'];
    $my_row['ID_AZIENDA']=$row['ID_AZIENDA'];
    //var_dump($my_row);
    //die();
    $retval = true;
    $table = "ANA_PI";
    $action = ACT_MODIFY;
    $keys = array('CF','ID_AZIENDA');
    //common_add_message(print_r($row,true),INFO);
    if (!db_form_updatedb($table, $my_row, $action, $keys)){
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

function personale_elimina($azienda_id,$cf){
    $retval = true;
    $table = "ANA_PI";
    $sql="DELETE FROM ANA_PI WHERE CF=:CF AND ID_AZIENDA=:ID_AZIENDA ";
    $bind=array();
    $bind['CF'] = $cf;
    $bind['ID_AZIENDA']=$azienda_id;
    //common_add_message(print_r($rw,true),INFO);
    $whereclause=" ID_AZIENDA=:ID_AZIENDA AND CF=:CF ";
    $hsql = 'INSERT INTO {S_'.$table.'} (SELECT acm_storico_id.nextval,SYSDATE,\''.$_SERVER['REMOTE_USER'].'\',t.* FROM '.$table.' t WHERE '.$whereclause.')'; //Inserimento in tabella storico S_$table
    if (!db_query_update_bind($hsql,$bind)){
        common_add_message("Inserimento in tabella storico fallito!",ERROR);
        $retval=false;
    }
    if($retval && !db_query_update_bind($sql,$bind,true)){
        common_add_message("Eliminazione fallita!",ERROR);
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
?>
