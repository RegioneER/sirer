<?php 

function tools_init(){
	dispatch('/tools', 'tools_page_new');
	//dispatch('/profile/new', 'tools_page_new');
	dispatch('/profile/list', 'tools_page_list');
	dispatch('/profiles/profiles_list_per_study/:study','_profiles_list_per_study');
	dispatch('/profiles/profiles_list_no_global_per_study/:study','_profiles_list_no_global_per_study');
}

function tools_sidebar($sideBar){
	$itm2=new SideBarItem(new Link(t("Other Tools"), "external-link", url_for('/external')));
	$itm2->addItem(new SideBarItem(new Link(t("Pentaho"), "external-link", str_replace("acm/?/", "", url_for('/pentaho/Home')),null,"_blank"), null, UIManager::_checkActive('/pentaho/Home')));
	$itm2->addItem(new SideBarItem(new Link(t("OTRS"), "external-link", "http://otrs".substr($_SERVER['HTTP_HOST'],strpos($_SERVER['HTTP_HOST'], ".")),null,"_blank"), null, UIManager::_checkActive('/otrs')));
	$itm2->addItem(new SideBarItem(new Link(t("Jira"), "external-link", "https://jira-siss.cineca.it/",null,"_blank"), null, UIManager::_checkActive('/jira')));
	$itm2->addItem(new SideBarItem(new Link(t("xWM"), "external-link", "http://appserv-siss.dev.cineca.it/GeniusWM/",null,"_blank"), null, UIManager::_checkActive('/xWM')));
	//$itm2->addItem(new SideBarItem(new Link("Edit existing user", "edit", url_for('/user/list')), null, UIManager::_checkActive('/user/list')));
	//$itm2->addItem(new SideBarItem(new Link(t("List existing users"), "list", url_for('/user/list')), null, UIManager::_checkActive('/user/list')));
	$sideBar->addItem($itm2);
		
	return $sideBar;
}

function tools_breadcrumb($paths)
{
	/*VAXMR-297 vmazzeo 22.01.2016 non c'è più bisogno di questi breadcrumb per i profili a livello di tools*/
	/*if(UIManager::_checkActive('/profile')){
		$paths[]=array(t("Profiles"),t("Profiles"), url_for('/profile/list'));
// 		if(UIManager::_checkActive('/profile/new')){
// 			$paths[]=array(t("New ACL profile"), t("New ACL profile"), url_for('/profile/new'));
				
// 		}
		if(UIManager::_checkActive('/profile/list')){
			$paths[]=array(t("List existing profiles"),t("List existing profiles"), url_for('/profile/list'));
		}
	}*/

	return $paths;
}

function tools_getPageTitle($page_title){
	/*VAXMR-297 vmazzeo 22.01.2016 non c'è più bisogno di questi titoli per i profili a livello di tools*/
	/*if(UIManager::_checkActive('/profile')){
		$page_title=t("Profiles");
// 		if(UIManager::_checkActive('/profile/new')){
// 			$page_title=t("New ACL profile");

// 		}
		if(UIManager::_checkActive('/profile/list')){
			$page_title=t("List existing profiles");
		}
	}*/
	return $page_title;
}
?>