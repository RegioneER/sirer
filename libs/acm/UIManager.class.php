<?php

class UIManager{

    private $page_content = "";

    private $pagination_size = 25;


    private $onload_js = "";
    private $current_url=array();

    private static $instance;
    private function __construct(){
        $this->page_content = "";
        $this->current_url =array();
        //NULLA?
    }
    public static function getInstance() {
        if (!isset(self::$instance)) {
            $c = __CLASS__;
            self::$instance = new $c;
        }
        return self::$instance;
    }

    public static function _checkActive($tocheck){
        if ($tocheck == "/"){
            //echo "<pre>";
            //print_r($_SERVER);
            //echo "</pre>";
            //die();
            $requri = str_replace("/?/","/",$_SERVER['REQUEST_URI']);
            return ($requri."index.php" == $_SERVER['SCRIPT_NAME']);
        }else{
            $requri = preg_replace("|^[^?]*/?/|","/",$_SERVER['REQUEST_URI']);
            //echo "<br/>REQURI".$requri;
            return (stristr($requri,$tocheck)!==false?true:false);
        }
    }


    public function setCurrentUrl($_current_url){

        $this->current_url=explode("/", $_current_url);
        //var_dump($_current_url);
    }

    public function getCurrentUrl($pos=null){
        if(!$pos){
            return $this->current_url;
        }
        else{
            return $this->current_url[$pos];
        }
    }

    public function dsp_sidebar(){
        global $modules;
        $sideBar=new SideBar();

        //$itm1=new SideBarItem(new Link("Dashboard", "dashboard", url_for('/')), null, UIManager::_checkActive('/'));
        //$sideBar->addItem($itm1);

        //Modules
        if ($modules['workspace']) {
            $sideBar = workspace_sidebar($sideBar);
        }
        if ($modules['profile']) {
            $sideBar = profile_sidebar($sideBar);
        }
        if ($modules['study']) {
            $sideBar = study_sidebar($sideBar);
        }
        if ($modules['center']) {
            $sideBar = center_sidebar($sideBar);
        }
        if ($modules['user']) {
            $sideBar = user_sidebar($sideBar);
        }
        if ($modules['strutture']) {
            $sideBar = strutture_sidebar($sideBar);
        }
        if ($modules['personale']) {
            $sideBar = personale_sidebar($sideBar);
        }
        //Custom Modules
        global $custom_modules;
        if( isset($custom_modules['THERAPY']) && $custom_modules['THERAPY']=='1' ){
            $sideBar = therapy_sidebar($sideBar);
        }
        if( isset($custom_modules['DBLOCK']) && $custom_modules['DBLOCK']=='1' ){
            $sideBar = dblock_sidebar($sideBar);
        }
        if( isset($custom_modules['GLOBAL_PROFILES']) && $custom_modules['GLOBAL_PROFILES']=='1' ){
            require_once 'globalProfiles.module.php';
            $sideBar = globalProfiles_sidebar($sideBar);
        }
        if ($modules['tools']) {
            $sideBar = tools_sidebar($sideBar);
        }
        $itm2=new SideBarItem(new Link(t("Help"), "question", url_for('/help')));
        $itm2->addItem(new SideBarItem(new Link(t("Guida ACM V. 1.3 "), "question",'../guide/Guida_ACM_SIRER_v1.3_dicembre2020.pdf',null,"_blank"), null, UIManager::_checkActive('/help')));
        $sideBar->addItem($itm2);
        //$itm3=new SideBarItem(new Link(t("Utenze esterne"), "users", url_for('../registrazione_admin/?/utenze/list')));
        //$itm3->addItem(new SideBarItem(new Link(t("Richieste abilitazione utenze esterne"), "users",'../registrazione_admin/?/utenze/list',null,"_blank"), null, UIManager::_checkActive('../registrazione_admin/?/utenze/list')));
        //$sideBar->addItem($itm3);
        return $sideBar;
    }


    public function dsp_js($vars = false){
        $js="";

        //$itm1=new SideBarItem(new Link("Dashboard", "dashboard", url_for('/')), null, UIManager::_checkActive('/'));
        //$sideBar->addItem($itm1);

        //Modules
        //$js = workspace_js($js,$vars);
        //$js = profile_js($js,$vars);
        $js = study_js($js,$vars);
        //$js = center_js($js,$vars);
        //$js = user_js($js,$vars);
        //Custom Modules
        global $custom_modules;
        if( isset($custom_modules['THERAPY']) && $custom_modules['THERAPY']=='1' ){
            //$js .= therapy_js($js,$vars);
        }
        return $js;
    }

    public function dsp_backLinks(){

        $backLinks="";


        $backLinks = study_backLinks($backLinks);

        return $backLinks;
    }

    public function set_onLoad($onload_js){
        $this ->onload_js .=$onload_js;
    }

    public function get_onLoad(){
        return $this ->onload_js;
    }

    public function dsp_breadcrumb(){

        $paths=array();
        $paths[]=array("home", "Home Page", url_for('/'));
        /**
         * TO IMPLEMENT
         *
         */
        $paths = workspace_breadcrumb($paths);
        $paths = profile_breadcrumb($paths);
        $paths = user_breadcrumb($paths);
        $paths = study_breadcrumb($paths);
        $paths = center_breadcrumb($paths);
        $paths = strutture_breadcrumb($paths);
        $paths = personale_breadcrumb($paths);
        $paths = tools_breadcrumb($paths);
        //Custom Modules
        global $custom_modules;
        if( isset($custom_modules['THERAPY']) && $custom_modules['THERAPY']=='1' ){
            $paths = therapy_breadcrumb($paths);

        }
        if( isset($custom_modules['DBLOCK']) && $custom_modules['DBLOCK']=='1' ){
            $paths = dblock_breadcrumb($paths);

        }
        $breadcrumb = new BreadCrumb($paths);

        return $breadcrumb;

    }

    public function dsp_navbar(){
        $nav=new NavBar($this->dsp_getStudy());
        $actionItem=new NavBarItem("Actions", "plus");
        $actionItem->addLink(new Link("New Workspace", "plus", "#"));

        $nav->addItem($actionItem);

        $userdescr = "";
        if ($_SERVER['REMOTE_USER']){
            //Recupero username (Nome/Cognome) --> Richiede il modulo user!! (dovrebbe essere sempre presente)
            $row =_user_load_user($_SERVER['REMOTE_USER']);
            $userdescr = trim($row['NOME']." ".$row['COGNOME']);
        }
        $userInfo=new NavBarItem("Welcome,<br/>{$userdescr}", "user", "light-blue");
        $userInfo->addLink(new Link("Logout", "off", "?ShibLogOut"));

        $nav->addItem($userInfo);

        return $nav;
    }

    public function dsp_getStudy(){
        $study="<i class=\"fa fa-cog\"></i> Axmr 2.5 Service - Administrative Console";
        return $study;
    }
    public function dsp_getPageTitle(){

        $page_title=t("List existing users");
        $page_title = workspace_getPageTitle($page_title);
        $page_title = profile_getPageTitle($page_title);
        $page_title = user_getPageTitle($page_title);
        $page_title = center_getPageTitle($page_title);
        $page_title = strutture_getPageTitle($page_title);
        $page_title = personale_getPageTitle($page_title);
        $page_title = study_getPageTitle($page_title);
        $page_title = tools_getPageTitle($page_title);
        //Custom Modules
        global $custom_modules;
        if( isset($custom_modules['THERAPY']) && $custom_modules['THERAPY']=='1' ){
            $page_title = therapy_getPageTitle($page_title);

        }
        if( isset($custom_modules['DBLOCK']) && $custom_modules['DBLOCK']=='1' ){
            $page_title = dblock_getPageTitle($page_title);

        }
        return $page_title;
    }

    public function dsp_getPageContent(){
        return $this->page_content;
    }

    public function build_dashboard(){
        $this->page_content='<form class="form-horizontal" role="form">
										<div class="form-group">
											<label class="col-sm-3 control-label no-padding-right" for="form-field-1"> Text Field </label>
	
											<div class="col-sm-9">
												<input type="text" id="form-field-1" placeholder="Username" class="col-xs-10 col-sm-5" />
											</div>
										</div>
										
										<div class="form-group">
											<label class="col-sm-3 control-label no-padding-right" for="form-field-2"> Password Field </label>
	
											<div class="col-sm-9">
												<input type="password" id="form-field-2" placeholder="Password" class="col-xs-10 col-sm-5" />
												<span class="help-inline col-xs-12 col-sm-7">
													<span class="middle">Inline help text</span>
												</span>
											</div>
										</div>
										<div class="form-group">
											<label class="col-sm-3 control-label no-padding-right" for="form-field-6">Tooltip and help button</label>
	
											<div class="col-sm-9">
												<input data-rel="tooltip" type="text" id="form-field-6" placeholder="Tooltip on hover" title="Hello Tooltip!" data-placement="bottom" />
												<span class="help-button" data-rel="popover" data-trigger="hover" data-placement="left" data-content="More details." title="Popover on hover">?</span>
											</div>
			</div>
			<div class="form-group">
			<label class="col-sm-3 control-label no-padding-right" for="form-field-7">Tooltip and help button</label>
			<div class="col-sm-9">
				<input class="ace ace-switch ace-switch-2" type="checkbox" name="switch-field-1">
	<span class="lbl"></span>
			</div>
	</label>
			</div>
			
			
			
				<div class="col-md-offset-3 col-md-9">
												<button class="btn btn-info" type="button">
													<i class="fa fa-check bigger-110"></i>
													Submit
												</button>
	
												&nbsp; &nbsp; &nbsp;
												<button class="btn" type="reset">
													<i class="fa fa-undo bigger-110"></i>
													Reset
												</button>
											</div>
										
			
			</div>		
			</form>';

    }

    public function dsp_getLabelField($text,$class='col-sm-3'){
        $output = '<label class="{$class} control-label no-padding-right" >'.t($text).'</label>';
        return $output;
    }

    public function dsp_getHiddenField($fieldname, $value=false, $datarray=false){
        $output = "";
        $val = "";
        if ($datarray && isset($datarray[$fieldname])){
            $val = $datarray[$fieldname];
        }
        if ($value){
            $val = $value;
        }
        $output .=  '<input type="hidden" name="'.$fieldname.'" id="'.$fieldname.'-field" value="'.$val.'" />';
        return $output;
    }

    public function dsp_getFileField($fieldname,$is_multiple=false){
        $output = "";
        $multiple="";
        if($is_multiple){
            $multiple=' multiple="" ';
            $is_multiple = 1;
        }else{
            $is_multiple = 0;
        }
        $output .=  '<div class="ace-file-input"><input name="'.$fieldname.($is_multiple?'[]':'').'" id="'.$fieldname.'" type="file" '.$multiple.'/></div>';
        $my_js=" file_input('#".$fieldname."',".$is_multiple.");";
        $this->set_onLoad($my_js);
        return $output;
    }

    public function dsp_getTextField($text, $fieldname, $helper, $inline_text=false, $readonly=false, $value=false, $datarray=false, $mandatory = false){
        $output ='<div class="form-group">';
        $output .=  '<label class="col-sm-3 control-label no-padding-right" for="'.$fieldname.'">'.t($text).'</label>';
        $val = "";
        if ($datarray && isset($datarray[$fieldname])){
            $val = $datarray[$fieldname];
        }
        if ($value || $value === '0'){
            $val = $value;
        }
        $rostr = '';
        if ($readonly){
            $rostr = ' readonly="readonly" ';
        }
        $output .= ' <div class="col-sm-9">	<input type="text" name="'.$fieldname.'" id="'.$fieldname.'-field" placeholder="'.t($helper).'" class="col-xs-10 col-sm-5" '.$rostr.' value="'.$val.'" /> ';
        if ($mandatory){
            $output .= ' <span style="font-weight:bold; color:red; padding-left:6px; "><i class="fa fa-asterisk"></i></span> ';
        }
        if ($inline_text){
            $output .=  ' <span class="help-inline col-xs-12 col-sm-7"><span class="middle">'.t($inline_text).'</span> </span> ';
        }
        $output .=  '</div> <!-- col-sm-9 -->';
        $output .=  '</div> <!-- form-group -->';
        return $output;
    }

    public function dsp_getTextArea($text, $fieldname, $helper, $inline_text=false, $readonly=false, $value=false, $datarray=false,$maxlength=null, $mandatory = false){
        $output ='<div class="form-group">';
        $output .=  '<label class="col-sm-3 control-label no-padding-right" for="'.$fieldname.'">'.t($text).'</label>';
        $val = "";
        if ($datarray && isset($datarray[$fieldname])){
            $val = $datarray[$fieldname];
        }
        if ($value){
            $val = $value;
        }
        $rostr = '';
        if ($readonly){
            $rostr = ' readonly="readonly" ';
        }
        if (isset($maxlength)){
            $maxlength = ' maxlength="'.$maxlength.'" ';
        }
        else{
            $maxlength = ' maxlength="150" ';
        }

        $output .=  '<div class="col-sm-9">
						<textarea name="'.$fieldname.'" id="'.$fieldname.'" placeholder="'.t($helper).'" class="col-xs-10 col-sm-5 limited" '.$rostr.' '.$maxlength.' >'.$val.'</textarea>
					';
        if ($mandatory){
            $output .= ' <span style="font-weight:bold; color:red; padding-left:6px; "><i class="fa fa-asterisk"></i></span>';
        }
        if ($inline_text){
            $output .=  '
						<span class="help-inline col-xs-12 col-sm-7">
							<span class="middle">'.t($inline_text).'</span>
						</span>
						';
        }
        $output .=  '</div> <!-- col-sm-9 -->';
        $output .=  '</div> <!-- form-group -->';
        return $output;
    }

    public function dsp_getButtonsSubmitUndo($text_submit, $fieldname_submit, $text_undo=null, $fieldname_undo=null,$class=null){
        if($class===null){
            $class="col-sm-3";
        }
        $output ='<div class="form-group">';
        $output .=  '<label class="'.$class.' control-label no-padding-right" for="'.$fieldname_submit.'">&nbsp</label>';
        $output .=  '
				<div class="col-md-offset-3 ">
						<button class="btn btn-info" type="submit" name="'.$fieldname_submit.'" id="'.$fieldname_submit.'"><i class="fa fa-check bigger-110"></i>'.t($text_submit).'</button>
						&nbsp;&nbsp;&nbsp;		';
        if($text_undo&&$fieldname_undo){
            $output .=  '
						<button class="btn" type="reset" name="'.$fieldname_undo.'" id="'.$fieldname_undo.'"><i class="fa fa-undo bigger-110"></i>'.t($text_undo).'</button>';
        }
        $output .=  '
				</div><!-- col-sm-9 -->';
        $output .=  '</div><!-- form-group -->';
        return $output;
    }

    public function dsp_getCheckbox($text, $fieldname, $helper, $inline_text=false, $readonly=false, $value=false, $datarray=false){
        $output='<div class="form-group">';
        $output .=  '<label class="col-sm-3 control-label no-padding-right" for="'.$fieldname.'">'.t($text).'</label>';
        $rostr = '';
        if ($readonly){
            $rostr = ' disabled ';
        }
        $val = false;
        if ($datarray && isset($datarray[$fieldname])){
            $val = $datarray[$fieldname];
        }
        if ($value){
            $val = $value;
        }
        $checked = "";
        if ($val){
            $checked = ' checked="checked" ';
        }
        $output .=  '<div class="col-sm-9"><input class="ace ace-switch ace-switch-2" type="checkbox" id="'.$fieldname.'" name="'.$fieldname.'" '.$checked.' '.$rostr.' ><span class="lbl"></span> <label>'.t($inline_text).'</label></div>';
        $output .=  '</div><!-- form-group -->';
        return $output;
    }


    public function dsp_getSelectField($text, $fieldname, $helper, $inline_text=false, $readonly=false, $value=false, $options=null,$onaction=null,$mandatory = false){


        $output ='<div class="form-group">';
        $output .=  '<label class="col-sm-3 control-label no-padding-right" for="'.$fieldname.'">'.t($text).'</label>';
        $output .= '<div class="col-sm-9">';
        $rostr = '';
        if ($readonly){
            $rostr = ' disabled="true" ';
        }
        $output .=  '<select id="'.$fieldname.'" name="'.$fieldname.'" '.$rostr.' class="col-sx-3" style="margin-left:15px" '.$onaction.'><option value="">&nbsp;</option>';
        if(!isset($options)){
            $output .=  '<option value="">&nbsp;</option><option value="ZZ">INSERT OPTION HERE</option>/>';
        }
        else{
            foreach($options as $key=>$ovalue){
                $sel = "";
                if ($key==$value){
                    $sel = ' selected="selected" ';
                }
                $output .=  '<option value="'.$key.'" '.$sel.' >'.$ovalue.'</option>';
            }
        }
        $output.='</select>';
        if ($mandatory){
            $output .= ' <span style="font-weight:bold; color:red; padding-left:6px; "><i class="fa fa-asterisk"></i></span>';
        }
// 		$output.='<div id="form_field_select_3_chosen" class="chosen-container chosen-container-single" style="width: 389px;" title="">
// 					<a class="chosen-single" tabindex="-1">	<span> </span> <div> <b> </b> </div> </a>';
// 		$output.='<div class="chosen-drop">
// 					<div class="chosen-search">
// 						<input type="text" autocomplete="off">
// 					</div>
// 					<ul class="chosen-results">
// 						<li class="active-result result-selected" data-option-array-index="0" style=""> </li>';
// 		if(!isset($options)){
// 			$output .=  '<li class="active-result" data-option-array-index="1" style="">INSERT OPTION HERE</li>';
// 		}
// 		else{
// 			$i=1;
// 			foreach($options as $key=>$value){
// 				$output .=  '<li class="active-result" data-option-array-index="'.$i.'" style="">'.$value.'</li>';
// 				$i++;
// 			}
// 		}
// 		$output .='</ul>';
// 		$output .='</div> <!--chosen-drop-->';
// 		$output .='</div> <!--form_field_select_3_chosen-->';

        if ($inline_text){
            $output .=  '
						<span class="help-inline col-xs-10 col-sm-5">
							<span class="middle">'.t($inline_text).'</span>
						</span>
						';
        }


        $output .=  '</div> <!-- col-sm-9 -->';
        $output .=  '</div> <!-- form-group -->';
        $output.="<script type=\"text/javascript\">
					$(document).ready(function(){
						$('#{$fieldname}').select2();
					});
					</script>";

        return $output;
    }

    public function _getTotalPages($list){
        $retval = ceil(count($list)/$this->pagination_size);
        if ($retval<1){$retval = 1;}
        return $retval;
    }

    public function dsp_getTable($list_columns, $list_data, $actions=false, $pagenum = false, $pagelink = false, $userFunc=null, $rowkey=null){
        $output = "";
        if (!$pagelink){
            $pagelink = $_SERVER['REQUEST_URI'];
            //if ($pagenum){
            //	//Trim the page number from the current url
            //	$pagelink = substr($pagelink,0,strrpos($pagelink,'/'));
            //}
            $pagelink = preg_replace("/&page=[0-9]*/","",$pagelink);
        }
        if (!$pagenum){
            $pagenum = 1;
        }
        if (isset($_GET['page']) && $_GET['page']){
            $pagenum = $_GET['page'];
        }
        //print_r($list_data);
        $totpages = $this->_getTotalPages($list_data);
        if ($pagenum>$totpages){
            $pagenum = $totpages;
        }
        //echo $totpages;
        //die();
        //$output = '<div class="row">';
        //$output .= '<div class="col-xs-6 col-sm-9">';
        $output .= '<table border="0" align="center" class="table table-striped table-bordered table-hover" id="table1">';
        $has_actions=false;
        if($actions){
            $has_actions=true;
        }
        $output .= $this->dsp_getTableHeader($list_columns,$has_actions);
        $output .= '	<tbody>';
        $output .= $this->dsp_getTableRows($list_columns, $list_data, $actions, $pagenum, $pagelink, $userFunc, $rowkey);
        // 						<tr>
        // 							<td class="sc4bis">Avastin&nbsp;</td>
        // 							<td class="sc4bis">3&nbsp;</td>
        // 							<td class="sc4bis"><a href="index.php?&amp;list=patients_list.xml&amp;PT=5"><img border="0" src="/images/send-value.gif"></a></td>
        // 						</tr>
        $output .= '	</tbody>';

        $output .="</table>";
        //$output .= '</div> <!-- col-xs-6 col-sm-9 -->';
        //$output .= '</div> <!-- class="row" -->';
        $output .= $this->dsp_getTablePagination($list_columns, $list_data, $pagenum, $pagelink);
        return $output;
    }

    public function dsp_getTableJqGrid2($grid_selector, $pager_selector, $dataurl, $caption, $list_columns, $actions=false){
        $output = "";
        //Table header (Column Names)
        $colNames = array();
        foreach ($list_columns as $label=>$column){
            $colNames[] = t($label);
        }
        if($actions){
            $colNames[] ='&nbsp;';
        }
        //Table fields (Columns model)
        $colModel = array();
        foreach ($list_columns as $label=>$column){
            //if($column['TYPE']=='TEXT'){
            $sortable = false;
            if ($column['SORT'] && $column['SORT']!="no" && $column['SORT']!="false"){
                $sortable = true;
            }
            $searchable = false;
            if ($column['SEARCH'] && $column['SEARCH']!="no" && $column['SEARCH']!="false"){
                $searchable = true;
            }
            $align = 'left';
            if ($column['ALIGN']){
                $align = $column['ALIGN'];
            }
            $width = '20';
            if ($column['WIDTH']){
                $width = $column['WIDTH'];
            }
            $colModel[]  = array('name'=>$column['NAME'],'index'=>$column['NAME'],'width'=>$width,'align'=>$align,'sortable'=>$sortable,'search'=>$searchable,'sorttype'=>'text','firstsortorder'=>'asc','jsonmap'=>$column['NAME']);
            //}
        }
        if ($actions){
            $colModel[]  = array('name'=>'_ACTIONS_','index'=>'_ACTIONS_','sortable'=>false,'search'=>false,'width'=>'20','align'=>'left','jsonmap'=>'_ACTIONS_');
        }

        $output.='<span class="home-table" >';
        $output.='<table id="'.$grid_selector.'"></table>';
        $output.='<div id="'.$pager_selector.'"></div>';
        $output.="<script type=\"text/javascript\">
					$(document).ready(function(){
						var grid_selector=\"#".$grid_selector."\";
						var pager_selector=\"#".$pager_selector."\";
						var url=\"".$dataurl."\";
						var colModel=".json_encode($colModel).";
						var colNames=".json_encode($colNames).";
						var caption=\"".$caption."\";
						setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
					});
					</script>";

        $output.='</span>';
        //echo $colNames."<br/>".$colModel;
        //$this->set_onLoad($setupGrid);
        return $output;

    }

    public function dsp_getTableJqGrid($grid_selector,$pager_selector,$url,$colNames,$colModel,$caption){
        $output = "";
        $output.='<span class="home-table" >';
        $output.='<table id="'.$grid_selector.'"></table>';
        $output.='<div id="'.$pager_selector.'"></div>';
        $output.="<script type=\"text/javascript\">
					$(document).ready(function(){
						var grid_selector=\"#".$grid_selector."\";
						var pager_selector=\"#".$pager_selector."\";
						var url=\"".$url."\";
						var colModel=".$colModel.";
						var colNames=".$colNames.";
						var caption=\"".$caption."\";
						setupGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
					});
					</script>";

        $output.='</span>';
        //echo $colNames."<br/>".$colModel;
        //$this->set_onLoad($setupGrid);
        return $output;

    }

    public function dsp_getTableHeader($list_columns,$has_actions){
        $output='	<thead>
						<tr>';
        foreach ($list_columns as $label=>$column){

            $output.='		<th class="int">'.t($label).'</th>';
        }
        if($has_actions){
            $output.='<th class="int">&nbsp;</th>';
        }
        $output.='  	</tr>
					</thead>';
        return $output;
    }

    public function dsp_getTableRows($list_columns, $list_data, $actions, $pagenum, $pagelink, $userFunc=null, $rowkey=null){
        //$output='	<thead>';
        $output="";
        //var_dump($list_columns);
        $list_data_idx = array_values($list_data);
        //foreach($list_data as $row){
        $start = ($pagenum-1)*$this->pagination_size; //0-based - corretto.
        $end = $start+$this->pagination_size;
        if ($end > count($list_data_idx)){
            $end = count($list_data_idx);
        }
        $baseActions=$actions;
        for($i=$start;$i<$end;$i++){
            $row = $list_data_idx[$i];
            // echo "<pre>";
            // print_r($list_columns);
            // echo "</pre>";
            if (isset($userFunc)){
                $actions=array_merge($baseActions, call_user_func_array($userFunc, array($row[$rowkey])));
            }
            $output.='<tr>';
            foreach ($list_columns as $label=>$column){
                if($column['TYPE']=='TEXT'){
                    $output.='<td>'.$row[$column['NAME']].'</td>';
                }
                else if($column['TYPE']=='CHECK'){
                    if ($row[$column['NAME']]=='1'){
                        $output.='<td><i class="bigger-150 fa fa-check-circle green"></i></td>';
                    }
                    else{
                        $output.='<td><i class="bigger-150 fa fa-times-circle red"></i></td>';
                    }
                }
                else if($column['TYPE']=='LOCK_CENTER'){
                    if ($row[$column['NAME']]=='1'){
                        $output.='<td>';
                        $l='/acm/?/dblock/unlock_center/'.$row['STUDY_PREFIX'].'/'.$column['NAME'].'/'.$row['SITE_ID'];
                        $output.=new Link("", 'lock', $l, 'red');
                        $output.="</td>";
                        //<a hfref="/acm/?/dblock/unlock/'.$column['NAME'].'/'.$row['SITE_ID'].'"><i class="bigger-150 fa fa-lock red"></i></a></td>';
                    }
                    else{
                        $output.='<td>';
                        $l='/acm/?/dblock/lock_center/'.$row['STUDY_PREFIX'].'/'.$column['NAME'].'/'.$row['SITE_ID'];
                        $output.=new Link("", 'unlock', $l, 'green');
                        $output.="</td>";
                        //$output.='<td><a hfref="/acm/?/dblock/lock/'.$column['NAME'].'/'.$row['SITE_ID'].'"><i class="bigger-150 fa fa-unlock green"></i></a></td>';
                    }
                }
                else if($column['TYPE']=='LOCK_CODPAT'){
                    if ($row[$column['NAME']]=='1'){
                        $output.='<td>';
                        $l='/acm/?/dblock/unlock_codpat/'.$row['STUDY_PREFIX'].'/'.$column['NAME'].'/'.$row['CODPAT'];
                        $output.=new Link("", 'lock', $l, 'red');
                        $output.="</td>";
                        //<a hfref="/acm/?/dblock/unlock/'.$column['NAME'].'/'.$row['SITE_ID'].'"><i class="bigger-150 fa fa-lock red"></i></a></td>';
                    }
                    else{
                        $output.='<td>';
                        $l='/acm/?/dblock/lock_codpat/'.$row['STUDY_PREFIX'].'/'.$column['NAME'].'/'.$row['CODPAT'];
                        $output.=new Link("", 'unlock', $l, 'green');
                        $output.="</td>";
                        //$output.='<td><a hfref="/acm/?/dblock/lock/'.$column['NAME'].'/'.$row['SITE_ID'].'"><i class="bigger-150 fa fa-unlock green"></i></a></td>';
                    }
                }
            }
            if ($actions){
                $output.='<td>';
                foreach ($actions as $a){
                    $l = $a['LINK'];
                    foreach ($row as $column=>$value){
                        $l = str_replace("[{$column}]",$value,$l); //standard
                        $l = str_replace("%5B{$column}%5D",$value,$l); //urlencodato
                    }
                    $c = (isset($a['COLOR'])?$a['COLOR']:false);
                    $output.=new Link(t($a['LABEL']), $a['ICON'], $l, $c);
                }
                $output.='</td>';
            }
            $output.='</tr>';
        }
        return $output;
    }

    public function dsp_getTablePagination($list_columns, $list_data, $pagenum, $pagelink){
        $output = "";
        $beforeafterpages = 6;
        //$currpage = $_SERVER['REQUEST_URI'];
        //trim any
        $totpages = $this->_getTotalPages($list_data);
        if ($totpages>1){
            $start = $pagenum - $beforeafterpages;
            if ($start<1){
                $start = 1;
            }
            $end  = $pagenum + $beforeafterpages;
            if ($end>$totpages){
                $end = $totpages;
            }
            $output.= '
						<div class="center">
						<ul class="pagination">
						  <li '.($pagenum==1?'class="disabled"':'').' ><a '.($pagenum!=1?'href="'.$pagelink.'&page=1"':'').' >&laquo;&laquo;</a></li>
						  <li '.($pagenum==1?'class="disabled"':'').' ><a '.($pagenum!=1?'href="'.$pagelink.'&page='.($pagenum-1).'"':'').' >&laquo;</a></li>
					';
            for($i=$start;$i<=$end;$i++){
                $output.= '
						  <li '.($i==$pagenum?'class="active"':'').' ><a '.($i!=$pagenum?'href="'.$pagelink.'&page='.$i.'"':'').' >'.$i.'</a></li>
					';
            }
            $output.= '
						  <li '.($pagenum==$totpages?'class="disabled"':'').' ><a '.($pagenum!=$totpages?'href="'.$pagelink.'&page='.($pagenum+1).'"':'').' >&raquo;</a></li>
						  <li '.($pagenum==$totpages?'class="disabled"':'').' ><a '.($pagenum!=$totpages?'href="'.$pagelink.'&page='.$totpages.'"':'').' >&raquo;&raquo;</a></li>
						</ul>
						</div>
					';
        }
        //var_dump($_SERVER);
        return $output;
    }

    public function dsp_getButtonUndo($text, $fieldname, $helper, $inline_text=false, $readonly=false, $value=false){
        $output =  '<label class="col-sm-3 control-label no-padding-right" for="'.$fieldname.'">&nbsp</label>';
        $output .=  '
                <div class="col-sm-9">
                        <button class="btn " type="reset" id="'.$fieldname.'"><i class="fa fa-undo bigger-110"></i>'.t($text).'</button>
                </div>';
        return $output;
    }

    public function dsp_buttonJs($text, $js, $icon = "save"){
        $output = '';
        $output .=  '
                <div>
                        <button class="btn " onclick="'.$js.'"><i class="fa fa-'.$icon.' bigger-110"></i> '.t($text).'</button>
                </div>';
        return $output;
    }


    public function dsp_getLegend($title="Legenda",$list=array()){ //VAXMR-297
        $output= '';
        $output.='<div class="widget-box">
					<div class="widget-header">';
        $output.='		<h5>'.t($title).'</h5>
					</div>
					<div style="padding:10px" class="widget-body">';
        foreach ($list as $key => $value) {
            $output.=' <p><i class="'.$value['icon'].'"></i>'.$value['testo'].'</p>';
        }
        $output.='
				    </div>
     			  </div>';

        return $output;
    }




}

function isAjax()
{
    if (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && $_SERVER['HTTP_X_REQUESTED_WITH'] == "XMLHttpRequest")
        return true;
    return false;
}

?>