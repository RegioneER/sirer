<?php 

function workspace_init(){
	dispatch('/workspace', 'workspace_page_new');
	dispatch('/workspace/new', 'workspace_page_new');
	dispatch('/workspace/list', 'workspace_page_list');
	
}

function workspace_sidebar($sideBar){
	$itm2=new SideBarItem(new Link("Workspaces", "cloud", "#"));
	//$itm2->addItem(new SideBarItem(new Link("New Workspace", "plus", url_for('/workspace/new')), null, UIManager::_checkActive('/workspace/new')));
	$itm2->addItem(new SideBarItem(new Link("List existing workspaces", "list", url_for('/workspace/list')), null, UIManager::_checkActive('/workspace/list')));
	$sideBar->addItem($itm2);
	
	return $sideBar;
}

function workspace_breadcrumb($paths)
{
	if(UIManager::_checkActive('/workspace')){
		$paths[]=array("Workspaces", "Workspaces", url_for('/workspace'));
		if(UIManager::_checkActive('/workspace/new')){
			$paths[]=array("New Workspace", "New Workspace", url_for('/workspace/new'));

		}
		if(UIManager::_checkActive('/workspace/list')){
			$paths[]=array("List existing workspaces", "List existing workspace", url_for('/workspace/list'));
		}
	}

	return $paths;
}

function workspace_getPageTitle($page_title){
	if(UIManager::_checkActive('/workspace')){
		$page_title="Workspaces";
		if(UIManager::_checkActive('/workspace/new')){
			$page_title="New Workspace";

		}
		if(UIManager::_checkActive('/workspace/list')){
			$page_title="List existing workspaces";
		}
	}
	return $page_title;
}

function workspace_page_new(){
	/*
	$d = Dispatcher::getInstance();
	$d->workspace_new();
	return html($d->dsp_getPageContent());
	*/
	$output = "";
	$output .= '<form class="form-horizontal" role="form">
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
	
			</form>';
	return html($output);
}
function workspace_page_list(){
	$output = "";
	$m = UIManager::getInstance();
 	$list = _list_workspaces();
 	$labels = array('Name'=>array('NAME'=>'NAME','TYPE'=>'TEXT'),'Description'=>array('NAME'=>'DESCRIPTION','TYPE'=>'TEXT'));
 	$actions = null;
 	$output .=$m->dsp_getTable($labels,$list,$actions);
	return html($output);
}
function _list_workspaces(){
	$retval = array();
	$ws = array('NAME'=>'SERVICE', 'DESCRIPTION'=>'Servizio demo');
	$retval[] = $ws;
	//var_dump($retval);
	return $retval;
}
?>