<?php

function strutture_init(){
    //Aziende
    dispatch('/strutture/aziende_list/:id_azienda', 'strutture_aziende_page_list');
    dispatch('/strutture/get_list_aziende/:jqGrid/:id_azienda','_strutture_list_aziende');
    //Strutture
    dispatch('/strutture', 'strutture_page_new');
    dispatch('/strutture/new', 'strutture_page_new');
    dispatch('/strutture/list/:id_azienda', 'strutture_page_list');
    dispatch_post('/strutture/new', 'strutture_page_new');
    dispatch('/strutture/edit/:id_azienda/:strutture_id', 'strutture_page_edit');
    dispatch_post('/strutture/edit/:id_azienda/:strutture_id', 'strutture_page_edit');
    dispatch('/strutture/get_list_strutture/:jqGrid/:id_azienda','_strutture_list_strutture');
    dispatch('/strutture/load_struttura_from_azienda/:id_azienda/:id_struttura/:jqGrid','_strutture_load_struttura');
    //Dipartimenti
    dispatch('/strutture/dipartimenti', 'strutture_dipa_page_new');
    dispatch('/strutture/dipartimenti/new', 'strutture_dipa_page_new');
    dispatch('/strutture/dipartimenti/list/:id_azienda/:id_struttura', 'strutture_dipa_page_list');
    dispatch_post('/strutture/dipartimenti/new', 'strutture_dipa_page_new');
    dispatch('/strutture/dipartimenti/edit/:id_azienda/:dipa_id', 'strutture_dipa_page_edit');
    dispatch_post('/strutture/dipartimenti/edit/:id_azienda/:dipa_id', 'strutture_dipa_page_edit');
    dispatch('/strutture/get_list_dipartimenti/:jqGrid/:id_azienda/:id_struttura','_strutture_list_dipartimenti');
    dispatch('/strutture/load_dipartimento_from_azienda/:id_azienda/:id_struttura/:jqGrid','_strutture_load_dipartimento');
    //UO
    dispatch('/strutture/uo', 'strutture_uo_page_new');
    dispatch('/strutture/uo/new', 'strutture_uo_page_new');
    dispatch('/strutture/uo/list/:id_azienda/:id_dipartimento', 'strutture_uo_page_list');
    dispatch_post('/strutture/uo/new', 'strutture_uo_page_new');
    dispatch('/strutture/uo/edit/:id_azienda/:uo_id', 'strutture_uo_page_edit');
    dispatch_post('/strutture/uo/edit/:id_azienda/:uo_id', 'strutture_uo_page_edit');
    dispatch('/strutture/get_list_uo/:jqGrid/:id_azienda/:id_dipartimento','_strutture_list_uo');
    dispatch('/strutture/UO/user_assoc/:id_azienda/:uo_id', 'strutture_uo_page_users');
    dispatch_post('/strutture/UO/user_assoc/:id_azienda/:uo_id', 'strutture_uo_page_users');
    dispatch('/strutture/UO/get_list_user/:id_azienda/:uo_id/:jqGrid','_strutture_uo_load_users');
    dispatch('/strutture/UO/get_list_users_not_associated/:id_azienda/:uo_id/:jqGrid/', '_strutture_uo_list_users_not_associated'); //VAXMR-299
    dispatch('/strutture/UO/uo_assoc_new_user/:id_azienda/:uo_id/:username/','_strutture_uo_assoc_new_user');//VAXMR-299
    dispatch('/strutture/UO/users/delete/:id_azienda/:uo_id/:user_id','_uo_user_delete');
}

function strutture_sidebar($sideBar){
    $itm2=new SideBarItem(new Link(t("Organigramma"), "building-o", "#"));
    $itm2->addItem(new SideBarItem(new Link(t("Lista aziende"), "list", url_for('/strutture/aziende_list')), null, UIManager::_checkActive('/strutture/aziende_list')));
    //Strutture
    $itm2->addItem(new SideBarItem(new Link(t("Nuova struttura"), "plus", url_for('/strutture/new')), null, UIManager::_checkActive('/strutture/new')));
    $itm2->addItem(new SideBarItem(new Link(t("Lista strutture"), "list", url_for('/strutture/list')), null, UIManager::_checkActive('/strutture/list')));
    //dipa
    $itm2->addItem(new SideBarItem(new Link(t("Nuovo dipartimento"), "plus", url_for('/strutture/dipartimenti/new')), null, UIManager::_checkActive('/strutture/dipartimenti/new')));
    $itm2->addItem(new SideBarItem(new Link(t("Lista dipartimenti"), "list", url_for('/strutture/dipartimenti/list')), null, UIManager::_checkActive('/strutture/dipartimenti/list')));
    //uo
    $itm2->addItem(new SideBarItem(new Link(t("Nuova UO"), "plus", url_for('/strutture/uo/new')), null, UIManager::_checkActive('/strutture/uo/new')));
    $itm2->addItem(new SideBarItem(new Link(t("Lista UO"), "list", url_for('/strutture/uo/list')), null, UIManager::_checkActive('/strutture/uo/list')));
    //Aggiungi item
    $sideBar->addItem($itm2);

    return $sideBar;
}

function strutture_breadcrumb($paths)
{
    if(UIManager::_checkActive('/strutture')){
        $paths[]=array(t("Strutture"), t("Strutture"), url_for('/strutture/list'));
        if(UIManager::_checkActive('/strutture/new')){
            $paths[]=array(t("Nuova struttura"), t("Nuova struttura"), url_for('/strutture/new'));

        }
        if(UIManager::_checkActive('/strutture/edit')){
            $paths[]=array(t("Modifica struttura"), t("Modifica struttura"), url_for('/strutture/edit'));
        }
        if(UIManager::_checkActive('/strutture/list')){
            $paths[]=array(t("Lista strutture"), t("Lista strutture"), url_for('/strutture/list'));
        }
    }
    if(UIManager::_checkActive('/strutture/dipartimenti')){
        $paths[]=array(t("Dipartimenti"), t("Dipartimenti"), url_for('/strutture/dipartimenti/list'));
        if(UIManager::_checkActive('/strutture/dipartimenti/new')){
            $paths[]=array(t("Nuovo dipartimento"), t("Nuovo dipartimento"), url_for('/strutture/dipartimenti/new'));

        }
        if(UIManager::_checkActive('/strutture/dipartimenti/edit')){
            $paths[]=array(t("Modifica dipartimento"), t("Modifica dipartimento"), url_for('/strutture/dipartimenti/edit'));
        }
        if(UIManager::_checkActive('/strutture/dipartimenti/list')){
            $paths[]=array(t("Lista dipartimenti"), t("Lista dipartimenti"), url_for('/strutture/dipartimenti/list'));
        }
    }
    if(UIManager::_checkActive('/strutture/uo')){
        $paths[]=array(t("UO"), t("UO"), url_for('/strutture/uo/list'));
        if(UIManager::_checkActive('/strutture/uo/new')){
            $paths[]=array(t("Nuovo UO"), t("Nuovo UO"), url_for('/strutture/uo/new'));

        }
        if(UIManager::_checkActive('/strutture/uo/edit')){
            $paths[]=array(t("Modifica UO"), t("Modifica UO"), url_for('/strutture/uo/edit'));
        }
        if(UIManager::_checkActive('/strutture/uo/list')){
            $paths[]=array(t("Lista UO"), t("Lista UO"), url_for('/strutture/uo/list'));
        }
    }

    return $paths;
}

function strutture_getPageTitle($page_title){
    if(UIManager::_checkActive('/strutture')){
        $page_title=t("Strutture");
        if(UIManager::_checkActive('/strutture/new')){
            $page_title=t("Nuova struttura");

        }
        if(UIManager::_checkActive('/strutture/edit')){
            $page_title=t("Modifica struttura");

        }
        if(UIManager::_checkActive('/strutture/list')){
            $page_title=t("Lista strutture");
        }
    }
    if(UIManager::_checkActive('/strutture/dipartimenti')){
        $page_title=t("Dipartimenti");
        if(UIManager::_checkActive('/strutture/dipartimenti/new')){
            $page_title=t("Nuovo dipartimento");

        }
        if(UIManager::_checkActive('/strutture/dipartimenti/edit')){
            $page_title=t("Modifica dipartimento");

        }
        if(UIManager::_checkActive('/strutture/dipartimenti/list')){
            $page_title=t("Lista dipartimenti");
        }
    }
    if(UIManager::_checkActive('/strutture/uo')){
        $page_title=t("UO");
        if(UIManager::_checkActive('/strutture/uo/new')){
            $page_title=t("Nuova UO");

        }
        if(UIManager::_checkActive('/strutture/uo/edit')){
            $page_title=t("Modifica UO");

        }
        if(UIManager::_checkActive('/strutture/uo/list')){
            $page_title=t("Lista UO");
        }
    }
    return $page_title;
}

///////////////////////// AZIENDE   ////////////////////////////////

function strutture_aziende_page_list(){
    $output = '';
    $m = UIManager::getInstance();
    //$list = _strutture_list_strutture();
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/strutture/get_list_aziende/jqGrid/');
    $caption=t("Lista aziende");
    $labels=array('ID'=>array('NAME'=>'ID_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1, 'WIDTH'=>12),
        'DENOMINAZIONE'=>array('NAME'=>'DESCRIZIONE_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
        //,'ID REGIONE'=>array('NAME'=>'ID_REGIONE','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
        //,'IRCSS'=>array('NAME'=>'IRCSS','TYPE'=>'CHECK','SORT' => 1)
    );
    $actions = true;
    $output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption,$labels,$actions);
    //$output .=$m->dsp_getTable($columns,$list);
    return html($output);
}

function _strutture_list_aziende($jqGrid=false){
    //$retval = array();
    $cuser = _user_load_user($_SERVER['REMOTE_USERID']);
    //Actions
    $actions = array();
    $actions[] = array('LABEL'=>'Mostra Strutture/Presidi','ICON'=>'list','LINK'=>url_for('/strutture/list/[ID_AZIENDA]'));
    //$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>url_for('/strutture/delete/[ID]'),'COLOR'=>'#FA3A3A');//VAXMR-154
    //Queries
    $bind = array();
    $select="SELECT DISTINCT ID_AZIENDA, DESCRIZIONE_AZIENDA FROM ANA_STRUTTURE WHERE 1=1 ";

    //if (!in_array("tech-admin",$cuser['PROFILI'])){
    //Filtro per site
    $sites = _user_load_sites($_SERVER['REMOTE_USERID']);
    $sList =  _center_list_centers(false, true, true);
    //var_dump($sites);
    //var_dump($sList);
    $azFilter = "";
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
        $select .= " AND ID_AZIENDA IN ($azFilter)";
    }else{
        //$select .= " AND ID_AZIENDA = '0' "; //Non mostro nulla (in teoria), poichè non ho centri
    }
    //}
    //var_dump($select);

    if(!$jqGrid){ //VAXMR-297
        $select.=" ORDER BY DESCRIZIONE_AZIENDA";
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

function _strutture_load_azienda($key, $jqGrid=false){
    $retval = array();
    $select="SELECT DISTINCT ID_AZIENDA, DESCRIZIONE_AZIENDA FROM ANA_STRUTTURE WHERE ID_AZIENDA = :KEY";
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
///////////////////////// STRUTTURE ////////////////////////////////

function strutture_form($row){
    $output = "";
    $m = UIManager::getInstance();
    $output .= '<form class="form-horizontal" role="form" method="post" action="#">';
    $output .= ''.$m->dsp_getTextField('ID Struttura','ID', '', '', false, false, $row, true).'';
    $output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'ID', $row['ID'], false).'';
    $output .= ''.$m->dsp_getTextField('Denominazione', 'DESCRIZIONE', '', '', false, false,$row,true).'';
    $aziende = _center_list_centers(false);//PRENDO DA CENTRI SOLO QUELLI NON CE (ID>=10)
    $opt_aziende = array();
    foreach($aziende as $azrow){
        if($azrow['ID']>=10) {
            $opt_aziende[$azrow['CODE']] = $azrow['DESCR'];
        }
    }
    //$output .= ''.$m->dsp_getTextField('ID Azienda', 'ID_AZIENDA', '', '', false, false,$row,true).'';
    $output .= ''.$m->dsp_getSelectField('Azienda', 'ID_AZIENDA', '', '', false, $row['ID_AZIENDA'],$opt_aziende, null, true).'';
    $output .= ''.$m->dsp_getTextField('Descrizione Azienda', 'DESCRIZIONE_AZIENDA', '', '', false, false,$row).'';
    //$output .= ''.$m->dsp_getTextField('Centro', 'CENTRO', '', '', false, false,$row).'';
    $output .= ''.$m->dsp_getCheckbox('Visualizza', 'VISUALIZZA', '', 'Enabled', false, false, $row).'';
    //$output .= ''.$m->dsp_getCheckbox('Privata', 'PRIVATA', '', 'Enabled', false, false, $row).'';
    //$output .= ''.$m->dsp_getCheckbox('ULSS', 'ULSS', '', 'Enabled', false, false, $row).'';
    //$output .= ''.$m->dsp_getCheckbox('IRCSS', 'IRCSS', '', 'Enabled', false, false, $row).'';
    //$output .= ''.$m->dsp_getCheckbox('AOUI', 'AOUI', '', 'Enabled', false, false, $row).'';
    //$output .= ''.$m->dsp_getCheckbox('OLD', 'OLD', '', 'Enabled', false, false, $row).'';
    //$output .= ''.$m->dsp_getTextField('CTO_CRMS', 'CTO_CRMS', '', '', false, false,$row).'';
    $output .= ''.$m->dsp_getTextField('ID Regione', 'ID_REGIONE', '', '', false, false,$row).'';


    $output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
    $output .= '</form>';
    return $output;
}
function strutture_form_validate(){
    $retval = true;
    $row = $_POST;
    if (!$row['ID']){
        common_add_message(t("Please specify the field ")."'".t("ID Struttura")."'",WARNING);
        $retval = false;
    }
    if (!$row['DESCRIZIONE']){
        common_add_message(t("Please specify the field ")."'".t("Denominazione")."'",WARNING);
        $retval = false;
    }
    return $retval;
}
function strutture_form_submit($action){
    $retval = false;
    $row = $_POST;
    unset($row['submit-button']);
    unset($row['reset-button']);

    $row = common_booleanCheckBox($row, 'VISUALIZZA');
    $row = common_booleanCheckBox($row, 'PRIVATA');
    $row = common_booleanCheckBox($row, 'ULSS');
    $row = common_booleanCheckBox($row, 'IRCSS');
    $row = common_booleanCheckBox($row, 'AOUI');
    $row = common_booleanCheckBox($row, 'OLD');

    $row['DESCRIZIONE'] = trim($row['DESCRIZIONE']);
    $table = "ANA_STRUTTURE";
    if($action==ACT_INSERT || !$row['CENTRO'] || $row['CENTRO']=""){
        $aziende=_center_list_centers(false);
        foreach($aziende as $azrow){
            if($azrow['CODE']==$row['ID_AZIENDA']) {
                $row['CENTRO']= $azrow['CE_ID'];
            }
        }

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

function strutture_page_new(){
    $output = "";
    /*
     $d = Dispatcher::getInstance();
    $d->strutture_new();
    return html($d->dsp_getPageContent());
    */
    //$m = UIManager::getInstance();
    $row = array();
    $row['ID']="";
    $row['ID_REGIONE']="80";
    if ($_POST){
        if (strutture_form_validate(ACT_INSERT)){
            if (strutture_form_submit(ACT_INSERT)){
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
    $output .= strutture_form($row);
    $output .= '
			</form>';
    return html($output);
}

function strutture_page_edit($azienda_id,$strutture_id){
    $output = "";
    $row =_strutture_load_struttura($azienda_id, $strutture_id)[0];
    if ($_POST){
        if (strutture_form_validate(ACT_MODIFY)){
            if (strutture_form_submit(ACT_MODIFY)){
                header("location: ".url_for('/strutture/list'));
                die();
            }else{
                $output .= t("An error occurred during center update.");
            }
        }
        $row = $_POST;
    }
    $output .= strutture_form($row);
    return html($output);
}


function strutture_page_list($id_azienda = false){
    $output = '';
    $m = UIManager::getInstance();
    //$list = _strutture_list_strutture();
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/strutture/get_list_strutture/jqGrid/'.$id_azienda);
    $caption=t("Lista strutture");
    $labels=array('ID'=>array('NAME'=>'ID','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1, 'WIDTH'=>12),
        'DENOMINAZIONE'=>array('NAME'=>'DESCRIZIONE','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'ID AZIENDA'=>array('NAME'=>'ID_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'DENOMINAZIONE AZIENDA'=>array('NAME'=>'DESCRIZIONE_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
        //,'ID REGIONE'=>array('NAME'=>'ID_REGIONE','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
        //,'IRCSS'=>array('NAME'=>'IRCSS','TYPE'=>'CHECK','SORT' => 1)
    );
    $actions = true;
    $output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption,$labels,$actions);
    //$output .=$m->dsp_getTable($columns,$list);
    return html($output);
}

function _strutture_list_strutture($jqGrid=false, $id_azienda=false){
    //$retval = array();
    $cuser = _user_load_user($_SERVER['REMOTE_USERID']);
    //Actions
    $actions = array();
    $actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/strutture/edit/[ID_AZIENDA]/[ID]'));
    $actions[] = array('LABEL'=>'Mostra dipartimenti','ICON'=>'list','LINK'=>url_for('/strutture/dipartimenti/list/[ID_AZIENDA]/[ID]'));
    //$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>url_for('/strutture/delete/[ID]'),'COLOR'=>'#FA3A3A');//VAXMR-154
    //Queries
    $bind = array();
    $select="SELECT * FROM ANA_STRUTTURE WHERE 1=1 ";

    //if (!in_array("tech-admin",$cuser['PROFILI'])){
    //Filtro per site
    $sites = _user_load_sites($_SERVER['REMOTE_USERID']);
    $sList =  _center_list_centers(false, true, true);
    //var_dump($sites);
    //var_dump($sList);
    $azFilter = "";
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
        $select .= " AND ID_AZIENDA IN ($azFilter)";
    }else{
        //$select .= " AND ID_AZIENDA = '0' "; //Non mostro nulla (in teoria), poichè non ho centri
    }
    //}
    //var_dump($select);

    if ($id_azienda){
        $bind['ID_AZIENDA'] = $id_azienda;
        $select.=" AND ID_AZIENDA = :ID_AZIENDA";
    }
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

function _strutture_load_struttura($azienda, $key=false, $jqGrid=false){
    $retval = array();
    $select="SELECT * FROM ANA_STRUTTURE WHERE ID_AZIENDA = :AZIENDA";
    $bind['AZIENDA'] = $azienda;
    if($key!=false){
        $select.=" AND ID = :KEY";
        $bind['KEY'] = $key;
    }
    $select.=" ORDER BY DESCRIZIONE";
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
        $pkeys=array('ID');
        $retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
    }
    if(isAjax()){
        header('Content-Type: application/json');
        echo json_encode(array_merge(array("sstatus" => "ok"), array("strutture" =>$retval)));
        die();
    }
    else {
        return $retval;
    }
}

/////////////////////////////////// DIPARTIMENTI /////////////////////////////////

function strutture_dipa_form($row){
    $output = "";
    $m = UIManager::getInstance();

    $strutture = _strutture_list_strutture(false);
    $aziende = _strutture_list_aziende(false);

    if($row["ID_AZIENDA"]){
        $azienda_id=$row["ID_AZIENDA"];
        $strutture =_strutture_load_struttura($azienda_id);
    }
    $opt_strutture = array();
    $opt_aziende = array();
    foreach ($strutture as $strow){
        $opt_strutture[$strow['ID']]=$strow['DESCRIZIONE'];
    }
    foreach($aziende as $azrow){
        $opt_aziende[$azrow['ID_AZIENDA']] = $azrow['DESCRIZIONE_AZIENDA'];
    }

    $output .= '<form class="form-horizontal" role="form" method="post" action="#">';
    $output .= ''.$m->dsp_getTextField('ID Dipartimento','ID', '', '', false, false, $row, true).'';
    $output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'ID', $row['ID'], false).'';
    $output .= ''.$m->dsp_getTextField('Denominazione', 'DESCRIZIONE', '', '', false, false,$row,true).'';
    //dsp_getSelectField($text, $fieldname, $helper, $inline_text=false, $readonly=false, $value=false, $options=null,$onaction=null,$mandatory = false)
    $output .= ''.$m->dsp_getSelectField('Azienda', 'ID_AZIENDA', '', '', false, $row['ID_AZIENDA'],$opt_aziende, "onchange=loadStruttureFormAzienda($(this));", true).'';
    $output .= ''.$m->dsp_getSelectField('Struttura', 'ID_STRUTTURA', '', '', false, $row['ID_STRUTTURA'],$opt_strutture, null, true).'';
    //$output .= ''.$m->dsp_getTextField('Codifica', 'CODIFICA', '', '', false, false,$row).'';
    //$output .= ''.$m->dsp_getTextField('Disciplina', 'DISCIPLINA', '', '', false, false,$row).'';
    //$output .= ''.$m->dsp_getTextField('Codice interno azienda', 'CODICE_INTERNO', '', '', false, false,$row).'';


    $output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
    $output .= '</form>';
    $output .= '<script>
                function loadStruttureFormAzienda(azienda){
                    $.ajax({
                        type : "GET",
                        url : "/acm/?/strutture/load_struttura_from_azienda/"+$(azienda).val() ,
                        dataType : "json",
                        async: false, //aspetto che torni dalla chiamata ajax
                        success : function(data) {
                            if(data.sstatus=="ok"){
                                $("#ID_STRUTTURA option").remove();
                                $(data.strutture).each(function(id,dipartimento){
                                    //console.log(dipartimento.ID+" "+dipartimento.DESCRIZIONE);
                                    $("#ID_STRUTTURA").append(new Option(dipartimento.DESCRIZIONE, dipartimento.ID));
                                });
                            }
                            else if(data.sstatus=="ko"){
                                
                            }
                            //console.log(data);
                        }
                    });
                }
                </script>';
    return $output;
}
function strutture_dipa_form_validate(){
    $retval = true;
    $row = $_POST;
    if (!$row['ID']){
        common_add_message(t("Please specify the field ")."'".t("ID Dipartimento")."'",WARNING);
        $retval = false;
    }
    if (!$row['DESCRIZIONE']){
        common_add_message(t("Please specify the field ")."'".t("Name")."'",WARNING);
        $retval = false;
    }
    if (!$row['ID_AZIENDA']){
        common_add_message(t("Please specify the field ")."'".t("Azienda")."'",WARNING);
        $retval = false;
    }
    if (!$row['ID_STRUTTURA']){
        common_add_message(t("Please specify the field ")."'".t("Struttura")."'",WARNING);
        $retval = false;
    }
    return $retval;
}
function strutture_dipa_form_submit($action){
    $retval = false;
    $row = $_POST;
    unset($row['submit-button']);
    unset($row['reset-button']);

    //$row = common_booleanCheckBox($row, 'ACTIVE');
    //$strow = _strutture_load_struttura

    $row['DESCRIZIONE'] = trim($row['DESCRIZIONE']);
    $table = "ANA_DIPARTIMENTI";

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

function strutture_dipa_page_new(){
    $output = "";
    /*
     $d = Dispatcher::getInstance();
    $d->strutture_new();
    return html($d->dsp_getPageContent());
    */
    //$m = UIManager::getInstance();
    $row = array();
    $row['ID']="";
    if ($_POST){
        if (strutture_dipa_form_validate(ACT_INSERT)){
            if (strutture_dipa_form_submit(ACT_INSERT)){
                header("location: ".url_for('/strutture/dipartimenti/list/'.$_POST['ID_AZIENDA'].'/'.$_POST['ID_STRUTTURA']));
                die();
            }else{
                $output .= t("An error occurred during center creation.");
            }
        }
        $row = $_POST;
    }
    $output .= '<form class="form-horizontal" role="form" method="post" action="#">
				';
    $output .= strutture_dipa_form($row);
    $output .= '
			</form>';
    return html($output);
}

function strutture_dipa_page_edit($azienda_id, $dipa_id){
    $output = "";
    $row =_strutture_load_dipartimento($azienda_id, $dipa_id)[0];
    if ($_POST){
        if (strutture_dipa_form_validate(ACT_MODIFY)){
            if (strutture_dipa_form_submit(ACT_MODIFY)){
                header("location: ".url_for('/strutture/dipartimenti/list'));
                die();
            }else{
                $output .= t("An error occurred during center update.");
            }
        }
        $row = $_POST;
    }
    $output .= strutture_dipa_form($row);
    return html($output);
}


function strutture_dipa_page_list($id_azienda=false, $id_struttura=false){
    $output = '';
    $m = UIManager::getInstance();
    $azrow = _strutture_load_azienda($id_azienda);
    $strow = _strutture_load_struttura($id_azienda, $id_struttura);

    //$list = _strutture_list_strutture();
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/strutture/get_list_dipartimenti/jqGrid/'.$id_azienda.'/'.$id_struttura);
    $caption = "";
    $header=t("Tutti i dipartimenti");
    if ($id_struttura){
        $header=t("Dipartimenti per la struttura: {$strow['DESCRIZIONE']}"). " - ".'<a href="'.url_for("/strutture/list/{$id_azienda}").'">Torna a Lista strutture '.$azrow['DESCRIZIONE_AZIENDA'].'</a>';
    }
    $labels=array('ID'=>array('NAME'=>'ID_DIPARTIMENTO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1, 'WIDTH'=>12),
        'DENOMINAZIONE'=>array('NAME'=>'DENOMINAZIONE_DIPARTIMENTO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'ID STRUTTURA'=>array('NAME'=>'ID_STRUTTURA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'STRUTTURA'=>array('NAME'=>'DENOMINAZIONE_STRUTTURA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'AZIENDA'=>array('NAME'=>'DENOMINAZIONE_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
        //,'CODICE_INTERNO'=>array('NAME'=>'CODICE_INTERNO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
        //,'CODIFICA'=>array('NAME'=>'CODIFICA','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1)
        //,'DISCIPLINA'=>array('NAME'=>'DISCIPLINA','TYPE'=>'TEXT','SORT' => 1, 'SEARCH'=>1)
    );
    $actions = true;
    $output .= "<h4>{$header}</h4>";
    $output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption,$labels,$actions);
    //$output .=$m->dsp_getTable($columns,$list);
    return html($output);
}

function _strutture_list_dipartimenti($jqGrid=false, $id_azienda = false, $id_struttura = false){
    //$retval = array();
    $cuser = _user_load_user($_SERVER['REMOTE_USERID']);
    //Actions
    $actions = array();
    $actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/strutture/dipartimenti/edit/[ID_AZIENDA]/[ID]'));
    $actions[] = array('LABEL'=>'Mostra UO','ICON'=>'list','LINK'=>url_for('/strutture/uo/list/[ID_AZIENDA]/[ID]'));
    //$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>url_for('/strutture/delete/[ID]'),'COLOR'=>'#FA3A3A');//VAXMR-154
    //Queries
    $bind=array();
    $select="SELECT d.*,d.ID as ID_DIPARTIMENTO,d.DESCRIZIONE as DENOMINAZIONE_DIPARTIMENTO, a.DESCRIZIONE as DENOMINAZIONE_STRUTTURA, a.DESCRIZIONE_AZIENDA as DENOMINAZIONE_AZIENDA FROM ANA_STRUTTURE a, ANA_DIPARTIMENTI d WHERE d.ID_STRUTTURA = a.ID ";
    if ($id_azienda){
        $select .= " AND d.ID_AZIENDA = :ID_AZIENDA";
        $bind['ID_AZIENDA'] = $id_azienda;
    }
    if ($id_struttura){
        $select .= " AND d.ID_STRUTTURA = :ID_STRUTTURA";
        $bind['ID_STRUTTURA'] = $id_struttura;
    }

    //if (!in_array("tech-admin",$cuser['PROFILI'])){
    //Filtro per site
    $sites = _user_load_sites($_SERVER['REMOTE_USERID']);
    $sList =  _center_list_centers(false, true, true);
    //var_dump($sites);
    //var_dump($sList);
    $azFilter = "";
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
        $select .= " AND d.ID_AZIENDA IN ($azFilter)";
    }else{
        //$select .= " AND d.ID_AZIENDA = '0' "; //Non mostro nulla (in teoria), poichè non ho centri
    }
    //}
    //var_dump($select);

    //var_dump($bind);
    if(!$jqGrid){ //VAXMR-297
        $select.=" ORDER BY d.DESCRIZIONE";
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

function _strutture_load_dipartimento($azienda, $key, $jqGrid=false){
    $retval = array();
    $select="SELECT * FROM ANA_DIPARTIMENTI WHERE ID_AZIENDA = :AZIENDA";
    $bind['AZIENDA'] = $azienda;
    if($key!=false){
        $select.=" AND ID = :KEY";
        $bind['KEY'] = $key;
    }
    $select.=" ORDER BY DESCRIZIONE";
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
        $pkeys=array('ID');
        $retval=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
    }
    if(isAjax()){
        header('Content-Type: application/json');
        echo json_encode(array_merge(array("sstatus" => "ok"), array("strutture" =>$retval)));
        die();
    }
    else {
        return $retval;
    }
}



//////////////////////////////////////// UO //////////////////////////////////////


function strutture_uo_form($row){
    $output = "";
    $m = UIManager::getInstance();

    $dipartimenti = _strutture_list_dipartimenti(false);
    if($row["ID_AZIENDA"]){
        $azienda_id=$row["ID_AZIENDA"];
        $dipartimenti =_strutture_load_dipartimento($azienda_id,false);
    }

    $aziende = _strutture_list_aziende(false);
    $opt_dipartimenti = array();
    $opt_aziende = array();
    foreach ($dipartimenti as $strow){
        $opt_dipartimenti[$strow['ID']]=$strow['DESCRIZIONE'];
    }
    foreach($aziende as $azrow){
        $opt_aziende[$azrow['ID_AZIENDA']] = $azrow['DESCRIZIONE_AZIENDA'];
    }

    $output .= '<form class="form-horizontal" role="form" method="post" action="#">';
    $output .= ''.$m->dsp_getTextField('ID UO','ID', '', '', false, false, $row, true).'';
    $output .= ''.$m->dsp_getHiddenField(OLDPREFIX.'ID', $row['ID'], false).'';
    $output .= ''.$m->dsp_getTextField('Denominazione', 'DESCRIZIONE', '', '', false, false,$row,true).'';
    //dsp_getSelectField($text, $fieldname, $helper, $inline_text=false, $readonly=false, $value=false, $options=null,$onaction=null,$mandatory = false)
    $output .= ''.$m->dsp_getSelectField('Azienda', 'ID_AZIENDA', '', '', false, $row['ID_AZIENDA'],$opt_aziende, "onchange=loadDipartimentoFormAzienda($(this));", true).'';
    $output .= ''.$m->dsp_getSelectField('Dipartimento', 'ID_DIPARTIMENTO', '', '', false, $row['ID_DIPARTIMENTO'],$opt_dipartimenti, null, true).'';
    //$output .= ''.$m->dsp_getTextField('Codice interno azienda', 'CODICE_INTERNO', '', '', false, false,$row).'';

    $output .= ''.$m->dsp_getButtonsSubmitUndo('submit','submit-button','reset','reset-button').'';
    $output .= '</form>';
    $output .= '<script>
                function loadDipartimentoFormAzienda(azienda){
                    $.ajax({
                        type : "GET",
                        url : "/acm/?/strutture/load_dipartimento_from_azienda/"+$(azienda).val() ,
                        dataType : "json",
                        async: false, //aspetto che torni dalla chiamata ajax
                        success : function(data) {
                            if(data.sstatus=="ok"){
                                $("#ID_DIPARTIMENTO option").remove();
                                $(data.strutture).each(function(id,dipartimento){
                                    //console.log(dipartimento.ID+" "+dipartimento.DESCRIZIONE);
                                    $("#ID_DIPARTIMENTO").append(new Option(dipartimento.DESCRIZIONE, dipartimento.ID));
                                });
                            }
                            else if(data.sstatus=="ko"){
                                
                            }
                            //console.log(data);
                        }
                    });
                }
                </script>';
    return $output;
}
function strutture_uo_form_validate(){
    $retval = true;
    $row = $_POST;
    if (!$row['ID']){
        common_add_message(t("Please specify the field ")."'".t("ID UO")."'",WARNING);
        $retval = false;
    }
    if (!$row['DESCRIZIONE']){
        common_add_message(t("Please specify the field ")."'".t("Name")."'",WARNING);
        $retval = false;
    }
    if (!$row['ID_AZIENDA']){
        common_add_message(t("Please specify the field ")."'".t("Azienda")."'",WARNING);
        $retval = false;
    }
    if (!$row['ID_DIPARTIMENTO']){
        common_add_message(t("Please specify the field ")."'".t("Dipartimento")."'",WARNING);
        $retval = false;
    }
    return $retval;
}
function strutture_uo_form_submit($action){
    $retval = false;
    $row = $_POST;
    unset($row['submit-button']);
    unset($row['reset-button']);

    //$row = common_booleanCheckBox($row, 'ACTIVE');

    $row['DESCRIZIONE'] = trim($row['DESCRIZIONE']);
    $table = "ANA_UO";

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

function strutture_uo_page_new(){
    $output = "";
    /*
     $d = Dispatcher::getInstance();
    $d->strutture_new();
    return html($d->dsp_getPageContent());
    */
    //$m = UIManager::getInstance();
    $row = array();
    $row['ID']="";
    if ($_POST){
        if (strutture_uo_form_validate(ACT_INSERT)){
            if (strutture_uo_form_submit(ACT_INSERT)){
                header("location: ".url_for('/strutture/uo/list/'.$_POST['ID_AZIENDA'].'/'.$_POST['ID_DIPARTIMENTO']));
                die();
            }else{
                $output .= t("An error occurred during center creation.");
            }
        }
        $row = $_POST;
    }
    $output .= '<form class="form-horizontal" role="form" method="post" action="#">
				';
    $output .= strutture_uo_form($row);
    $output .= '
			</form>';
    return html($output);
}

function strutture_uo_page_edit($azienda_id, $uo_id){
    $output = "";
    $row =_strutture_load_uo($azienda_id, $uo_id);
    if ($_POST){
        if (strutture_uo_form_validate(ACT_MODIFY)){
            if (strutture_uo_form_submit(ACT_MODIFY)){
                header("location: ".url_for('/strutture/UO/list/'.$row['ID_AZIENDA']));
                die();
            }else{
                $output .= t("An error occurred during center update.");
            }
        }
        $row = $_POST;
    }
    $output .= strutture_uo_form($row);
    return html($output);
}


function strutture_uo_page_list($id_azienda = false, $id_dipartimento = false){
    $output = '';
    $m = UIManager::getInstance();
    $azrow = _strutture_load_azienda($id_azienda);
    $diprow = _strutture_load_dipartimento($id_azienda,$id_dipartimento);
    $strow = _strutture_load_struttura($id_azienda,$diprow['ID_STRUTTURA']);
    //$list = _strutture_list_strutture();
    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/strutture/get_list_uo/jqGrid/'.$id_azienda.'/'.$id_dipartimento);
    $caption = "";
    $header=t("Tutte le UO");
    if ($id_dipartimento){
        $header=t("UO per il dipartimento: {$diprow['DESCRIZIONE']} ({$azrow['DESCRIZIONE_AZIENDA']})"). " - ".'<a href="'.url_for("/strutture/list/{$id_azienda}/{$diprow['ID_STRUTTURA']}").'">Torna a Lista dipartimenti per '.$strow['DESCRIZIONE'].'</a>';
    }
    $labels=array('ID'=>array('NAME'=>'ID_UO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1, 'WIDTH'=>12),
        'DENOMINAZIONE'=>array('NAME'=>'DENOMINAZIONE_UO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'ID DIPARTIMENTO'=>array('NAME'=>'ID_DIPARTIMENTO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'DIPARTIMENTO'=>array('NAME'=>'DENOMINAZIONE_DIPARTIMENTO','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'ID STRUTTURA'=>array('NAME'=>'ID_STRUTTURA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'STRUTTURA'=>array('NAME'=>'DENOMINAZIONE_STRUTTURA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1),
        'AZIENDA'=>array('NAME'=>'DENOMINAZIONE_AZIENDA','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
        //,'CODICE_INTERNO'=>array('NAME'=>'ID_REGIONE','TYPE'=>'TEXT', 'SORT' => 1, 'SEARCH'=>1)
    );
    $actions = true;
    $output .= "<h4>{$header}</h4>";
    $output .=$m->dsp_getTableJqGrid2($grid_selector,$pager_selector,$url,$caption,$labels,$actions);
    //$output .=$m->dsp_getTable($columns,$list);
    return html($output);
}

function _strutture_list_uo($jqGrid=false, $id_azienda = false, $id_dipartimento = false){
    //$retval = array();
    $cuser = _user_load_user($_SERVER['REMOTE_USERID']);
    //Actions
    $actions = array();
    $actions[] = array('LABEL'=>'Edit','ICON'=>'edit','LINK'=>url_for('/strutture/UO/edit/[ID_AZIENDA]/[ID]'));
    $actions[] = array('LABEL'=>'Associazione Utente-UO','ICON'=>'users','LINK'=>url_for('/strutture/UO/user_assoc/[ID_AZIENDA]/[ID]'),'COLOR'=>'darkblue');
    //Queries
    $bind = array();
    $select="SELECT o.*,o.ID as ID_UO,o.DESCRIZIONE AS DENOMINAZIONE_UO, d.DESCRIZIONE as DENOMINAZIONE_DIPARTIMENTO, a.ID as ID_STRUTTURA, a.DESCRIZIONE as DENOMINAZIONE_STRUTTURA, a.DESCRIZIONE_AZIENDA AS DENOMINAZIONE_AZIENDA FROM ANA_STRUTTURE a, ANA_DIPARTIMENTI d, ANA_UO o WHERE d.ID_STRUTTURA = a.ID AND o.ID_DIPARTIMENTO = d.ID ";
    if ($id_azienda){
        $select .= " AND o.ID_AZIENDA = :ID_AZIENDA";
        $bind['ID_AZIENDA'] = $id_azienda;
    }
    if ($id_dipartimento){
        $select .= " AND o.ID_DIPARTIMENTO = :ID_DIPARTIMENTO";
        $bind['ID_DIPARTIMENTO'] = $id_dipartimento;
    }

    //if (!in_array("tech-admin",$cuser['PROFILI'])){
    //Filtro per site
    $sites = _user_load_sites($_SERVER['REMOTE_USERID']);
    $sList =  _center_list_centers(false, true, true);
    //var_dump($sites);
    //var_dump($sList);
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

function _strutture_load_uo($azienda, $key, $jqGrid=false){
    $retval = array();
    $select="SELECT * FROM ANA_UO WHERE ID_AZIENDA = :AZIENDA AND ID = :KEY";
    $bind['AZIENDA'] = $azienda;
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

///////////////////////////////////////////////////////////////////////////////////////
//GESTIONE UTENTI
function strutture_uo_page_users($azienda_id, $uo_id){
    $m = UIManager::getInstance();
    $output = "";
    $uo_info=_strutture_load_uo($azienda_id, $uo_id);
    //print_r($uo_info);
    $output .= "<h2>UO corrente: ".$uo_info['DESCRIZIONE']."</h2>";
    //$list =_strutture_uo_load_users($uo_id, false);

    $grid_selector = "user-list-grid-table";
    $pager_selector = "user-list-grid-pager";
    $url=url_for('/strutture/uo/get_list_user/'.$azienda_id.'/'.$uo_id.'/jqGrid');
    $caption=t("Associazione Utente-UO");
    $labels=array('USERID'=>array('NAME'=>'USERID','TYPE'=>'TEXT','SEARCH'=>1, 'SORT'=>1),
        'Name'=>array('NAME'=>'NOME','TYPE'=>'TEXT','SEARCH'=>1, 'SORT'=>1),
        'Surname'=>array('NAME'=>'COGNOME','TYPE'=>'TEXT','SEARCH'=>1, 'SORT'=>1));
    $actions = true;

    $output .=$m->dsp_getTableJqGrid2($grid_selector, $pager_selector, $url, $caption, $labels,$actions); //study_list_users($list);* /

    $output .= strutture_uo_users_form($row, $azienda_id, $uo_id,$uo_info);
    $output .= '<script>
				function deleteAssocUserUO(azienda_id,uo_id,user_id){
				    bootbox.confirm("Do you confirm to delete the user "+user_id+" from current UO?", function(result){ 
						if(result){
						    location.href="/acm/?/strutture/uo/users/delete/"+azienda_id+"/"+uo_id+"/"+user_id;
						}
					});
				}
				</script>';
    return html($output);
}

function _strutture_uo_load_users($id_azienda,$uo_id, $jqGrid=false){
    //$retval = array();
    $actions = array();
    //TODO: confirm_alert not defined!
    $actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>'javascript:deleteAssocUserUO('.$id_azienda.','.$uo_id.',\'[USERID]\')','COLOR'=>'#FA3A3A'); //VAXMR-154
    //Queries
    $bind = array();
    $bind['KEY']=$uo_id;
    $select="SELECT  us.USERID AS USERID, us.UO_ID AS UO_ID, s.NOME,s.COGNOME FROM USERS_UO us,ANA_UTENTI_1 s WHERE us.USERID=s.USERID AND us.UO_ID=:KEY ";
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

function _strutture_uo_list_users_not_associated($id_azienda, $uo_id, $jqGrid=false){ //VAXMR-299
    //$retval = array();
    $actions = array();
    //TODO: confirm_alert not defined!
    //$actions[] = array('LABEL'=>'Delete','ICON'=>'ban','LINK'=>'javascript:confirm_alert(\'Do you confirm the deletion of the user?\',\'USER DELETION\',\''.url_for('/center/users/delete/'.$uo_id.'/[USERID]').'\')','COLOR'=>'#FA3A3A'); //VAXMR-154
    //Queries
    $bind = array();
    $bind['KEY']=$uo_id;
    $bind['SITE_ID']=$id_azienda;
    $select="SELECT USERID, 0 AS ENABLED FROM ANA_UTENTI_1 WHERE USERID NOT IN (SELECT us.USERID FROM USERS_UO us,ANA_UTENTI_1 s WHERE us.USERID=s.USERID AND us.UO_ID=:KEY )
AND USERID IN (SELECT USERID FROM USERS_PROFILES WHERE PROFILE_ID IN (SELECT ID FROM STUDIES_PROFILES WHERE STUDY_PREFIX='CRMS' AND CODE='COORD'))
AND USERID IN (SELECT USERID FROM USERS_SITES US, SITES S WHERE US.SITE_ID=S.ID AND S.CODE=:SITE_ID)";
    $ord_override=array();
    if(!$jqGrid){
        $rs = db_query_bind($select,$bind);
        while ($row = db_nextrow($rs)){
            $data[] = $row;
        }
    }
    else{
        $actions = array();
        $actions[] = array('LABEL' => 'Associate user', 'ICON' => 'retweet', 'LINK' => '#" onclick="uo_assoc_new_user(\''.$id_azienda.'\',\''.$uo_id.'\',\'[USERID]\');', 'COLOR' => '#D32646');
        $ord_override=array("USERID"=>"USERID");
        $checkicons=array('ENABLED');
        $pkeys=array('USERID');

        $data=_data_retrieve($jqGrid,$select,$bind,$ord_override,$pkeys,$checkicons,$actions,false);
    }
    //$data = _data_load($select,$select_count,$bind,$ord_override);
    //$data = _data_retrieve($jqGrid,$select,$bind,$ord_override,array('USERID'),array(),$actions,false);
    return $data;
}

function _strutture_uo_assoc_new_user($id_azienda,$uo_id, $username){
    $retval=false;
    $my_row['USERID']=$username;
    // $my_row['STUDY_PREFIX']=$prefix;
    $my_row['UO_ID']=$uo_id;
    // echo "<pre>";
    // print_r($my_row);
    // echo "</pre>";
    $retval=strutture_uo_users_form_submit($id_azienda,$uo_id,null,$my_row,false);
    if($retval){
        header("location: " . $_SERVER['HTTP_REFERER']); //VAXMR-297
        db_close();die();
    }
    db_close();die();
    return $retval;

}

function strutture_uo_users_form($row,$azienda_id,$uo_id,$uo_info){ //VAXMR-299
    $m = UIManager::getInstance();
    $output = '<button class="btn btn-info" onclick="showAddUOUsersAssociation(\''.$azienda_id.'\',\''.$uo_id.'\');"  style="width:260px; margin-top:5px;" type="submit" name="assoc_new_UO_users" id="assoc_new_UO_users"><i class="fa fa-user-plus bigger-110"></i>&nbsp;' . t("crea associazione utente-UO") . '</button>';
    $titolo_modal=t("crea associazione utente-UO per la UO: ")." <b>".$uo_info['DESCRIZIONE']."</b>";
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
function strutture_uo_users_form_validate(){
    $retval = true;
    $row = $_POST;
    if (!$row['USERID']){
        common_add_message(t("Please specify the field ")."'".t("USER")."'",WARNING);
        $retval = false;
    }
    return $retval;
}

function strutture_uo_users_form_submit($id_azienda,$uo_id, $list,$row=false,$verbose=true){ //VAXMR-299
    $retval = false;
    if(!$row){
        $row = $_POST;
    }

    unset($row['submit-button']);
    unset($row['reset-button']);

    $table = "USERS_UO";
    $action = ACT_INSERT;
    foreach ($list as $up){
        if ($up['UO_ID']==$row['UO_ID'] && $up['USERID']==$row['USERID']){
            $action = ACT_MODIFY;
            break;
        }
    }
    //$row = common_booleanCheckBox($row, 'ACTIVE');
    //common_add_message(print_r($row,true), INFO);
    $keys = array('UO_ID','USERID');
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
    if(isAjax()){
        echo json_encode(array("sstatus" => $retval ? "ok" : "ko", "return_value"=>$retval));
        db_close();die();
    }
    else{
        return $retval;
    }
}
function _uo_user_delete($id_azienda,$uo_id,$user_id){
    $output="";
    $m = UIManager::getInstance();
    $sql="DELETE FROM USERS_UO WHERE USERID=:USERID AND UO_ID=:UO_ID ";
    $bind=array();
    $bind['USERID']=$user_id;
    $bind['UO_ID']=$uo_id;
    if(db_query_update_bind($sql,$bind,true)){
        common_add_message(t("You have deleted the user id <b>".$user_id."</b> from current UO"), INFO);
    }
    else{
        common_add_message(t("There was an error during the deletion of the user id <b>".$user_id."</b> from current UO"), ERROR);
    }
    header("location: ".url_for('/strutture/UO/user_assoc/'.$id_azienda.'/'.$uo_id.'/'));
    die();
}
//FINE GESTIONE UTENTI


?>
