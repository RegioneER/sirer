<?php 

class ProfileConfigurer{

	var $policy;
	var $study_structure_ref;
	var $navbar;
	var $sidebar;
	var $fastSearch;
	
	function __construct($study){
		if (isset($_GET['BUILD_DB'])) return;
		
		if(isset($study->user->profile_code) && $study->user->profile_code!=""){
			$confFilePath="{$study->xml_dir}/../conf/{$study->user->profile_code}.xml";
		}
		elseif(isset($study->config_service['landing_page'])&&$study->config_service['landing_page']!=""){
			//vmazzeo 25.06.2015 se un utente non è stato assegnato allo studio torna errore perchè non trova il file corrispondente al suo profilo 
			//quindi faccio redirect alla landing_page, se configurata
			header("location:https://".$_SERVER['SERVER_NAME']."/".$study->config_service['landing_page']);
		}
		$confFile=file_get_contents($confFilePath);
        if ($confFile) {
            $confs = new SimpleXMLElement($confFile);
            foreach ($confs->study_structure_ref->attributes() as $a => $b) {
                if ($a == "value") $this->study_structure_ref = $b . ".xml";
            }
            $study->CheckVisione();
            if ($this->study_structure_ref != "") {
            $study->visit_structure_xml = $this->study_structure_ref;
            }
            $study->VisitStructure();
            $isImage = false;
            if ((string)$confs->navbar->attributes()->{"image"} != "") {
                $ico_img = (string)$confs->navbar->attributes()->{"image"};
                $isImage = true;
            }
            if ((string)$confs->navbar->attributes()->{"icon"} != "") {
                $ico_img = (string)$confs->navbar->attributes()->{"icon"};
                $isImage = false;
            }
            $text = (string)$confs->navbar->attributes()->{"title"};
            $this->navbar = new NavBar(mlOut("Profile_{$study->user->profile_code}." . $text, $text), $ico_img, $isImage);
            foreach ($confs->navbar->children() as $key => $val) {
                if ((string)$val->attributes()->{"text"} != "") $text = (string)$val->attributes()->{"text"};
                if ((string)$val->text != "") $text = (string)$val->text;
                $text = mlOut("Profile_{$study->user->profile_code}." . $text, $text);
                $item = new NavBarItem(mlOut("Profile_{$study->user->profile_code}." . $text, $text), (string)$val->attributes()->{"icon"}, (string)$val->attributes()->{"color"});
                if ((string)$val->attributes()->{"type"} == "button") {
                    $item->addHref((string)$val->attributes()->{"link"});
                }
                if ((string)$val->attributes()->{"type"} == "dropdown") {
                    foreach ($val->children()->link as $k => $v) {
                        $text = (string)$v->attributes()->{"text"};
                        $item->addLink(new Link(mlOut("Profile_{$study->user->profile_code}." . $text, $text), (string)$v->attributes()->{"icon"}, (string)$v->attributes()->{"value"}));
                    }
                }
                foreach ($study->vlist->esams as $v => $v_) {
                    foreach ($v_ as $esam => $v__) {
                        $patterns[] = "/\[ESAM_NAME\({$v},{$esam}\)\]/";
                        $replaces[] = $v__['TESTO'];
                    }
                }
                if ((string)$val->attributes()->{"type"} == "highlights") {
                	foreach ($val->query as $qk => $qv) {
                        foreach ($study->session_vars as $sk => $sv) {
                            $bind[$sk] = $sv;
                            $bind[strtoupper($sk)] = $sv;
                        }
                        $sql_query = (string)$qv;
                        $sql = new query($study->conn);
                        $sql->exec($sql_query, $bind);
                        while ($sql->get_row()) {
                            $message = $sql->row['MESSAGE'];
                            $message = preg_replace($patterns, $replaces, $message);
                            $item->addLink(new LinkedEvent($message, $sql->row['DT'], $sql->row['LINK'], $sql->row['ICON']));
                        }
                    }
                    $this->navbar->addItem($item);
                    if (isset($study->session_vars[$study->config_service['PK_SERVICE']]) && is_numeric($study->session_vars[$study->config_service['PK_SERVICE']])) {
                        $item = new NavBarItem(mlOut("System.PatientLatestActivities", "Patient's Latest Activities"), "user-md", "blue");
                        foreach ($val->query as $qk => $qv) {
                            foreach ($study->session_vars as $sk => $sv) {
                                $bind[$sk] = $sv;
                                $bind[strtoupper($sk)] = $sv;
                            }
                            $sql_query = (string)$qv;
                            $sql_query = str_replace("--CODPAT_WHERE--", "and c.{$study->config_service['PK_SERVICE']}=:codpat ", $sql_query);
                            $sql = new query($study->conn);
                            $sql->exec($sql_query, $bind);
                            while ($sql->get_row()) {
                                $message = $sql->row['MESSAGE'];
                                $message = preg_replace($patterns, $replaces, $message);
                                $item->addLink(new LinkedEvent($message, $sql->row['DT'], $sql->row['LINK'], $sql->row['ICON']));
                            }
                        }
                        $this->navbar->addItem($item);
                    }
                } else {
                    $this->navbar->addItem($item);
                }
            }
            $userInfo = new NavBarItem("{$study->user->nome_cognome}<br/> <small>" . mlOut("Profile_{$study->user->profile_code}.profileName", $study->user->profilo) . "</small>", "user", "light-blue", false);
			$userInfo->addIconHtml = "<!--inbox_bottone-->";
			
            if (count($study->config_service["aLanguages"]) > 1)
                $userInfo->addLink(new Link(mlOut("System.Change Language", "Change Language"), "flag", "javascript:ChooseLanguage();"));
            if (count($study->user->usersProfiles) > 1) {
                $userInfo->addLink(new Link(mlOut("System.Change Profile", "Change Profile"), "users", "javascript:ChangeProfile();"));
            }
			$sql = new query($study->conn);
            $sql_query="select count(*) as c from utenti_visteammin where userid=:userid";
            $bind['userid']=$study->user->userid;
            $sql->get_row($sql_query, $bind);
            if ($sql->row['C']>0){
            	$adminUser=true;
            }else {
            	$adminUser=false;
            }
            if ($adminUser){
            	$params='';
            	foreach ($_GET as $key=>$val){
            		$params.=$key."=".$val."&";
            	}
            	$params.="enableEditLabelInLine=1";
            	$userInfo->addLink(new Link(mlOut("System.enableEditLabelInLine", "Abilita/Disabilita modifica inline etichette"), "tag", "index.php?".$params));
            }else {
            	if (isset($_SESSION['editLabelInLine'])) unset ($_SESSION['editLabelInLine']);
            }
            if ($_GET['enableEditLabelInLine']){
            	if ($adminUser){	
            		if (isset($_SESSION['editLabelInLine'])) unset ($_SESSION['editLabelInLine']);
            		else $_SESSION['editLabelInLine']=true;
            		$params='';
            		foreach ($_GET as $key=>$val){
            			if ($key!='enableEditLabelInLine'){
            				if ($params!='') $params.="&";
            				$params.=$key."=".$val;
            			}
            		}
            		header("location:index.php?".$params);
            		die();
            	}
            }
            if ($adminUser){
                $params='';
                foreach ($_GET as $key=>$val){
                    $params.=$key."=".$val."&";
                }
                $params.="clearFormLabels=1";
                $userInfo->addLink(new Link(mlOut("System.clearFormLabels", "Resetta etichette per lingua corrente"), "chain-broken", "index.php?".$params, false, null, "return confirm('".mlOut("System.areYouSure", "Are you sure?")."');"));
            }else {
                if (isset($_SESSION['editLabelInLine'])) unset ($_SESSION['editLabelInLine']);
            }
            /*
            $userInfo->addLink(new Link(mlOut("System.Change Password","Change Password"), "key", "?ShibLogOut"));
            //$userInfo->addLink(new Link(mlOut("System.Logout","Logout"), "power-off", "?ShibLogOut"));
            $userInfo->addLink(new Link(mlOut("System.Logout","Logout"), "power-off", "http://log:out@{$_SERVER['SERVER_NAME']}"));
            */
            $userInfo->addLink(new Link(mlOut("System.ContactHD", "Contatta l'help desk"), "envelope", "mailto:help_osservaflu@cineca.it"));
            $userInfo->addLink(new Link(mlOut("System.Change Password", "Change Password"), "key", "/change_password"));
            $userInfo->addLink(new Link(mlOut("System.Logout", "Logout"), "power-off", "?ShibLogOut"));
			if(isset($study->config_service["NoMessages"]) && $study->config_service["NoMessages"]==false){
            	$userInfo->staticAddHtml = "<!--inbox-->";
			}
            //$userInfo->addLink(new Link(mlOut("System.Inbox","See messages"), "envelope", "index.php?inbox"));

            $this->navbar->addItem($userInfo);
            $this->sidebar = new SideBar();
            $this->hasFastSearch = false;
            foreach ($confs->fastSearch->children() as $key => $val) {
                $searchField['FIELD'] = (string)$val->attributes()->{"name"};
                $searchField['TYPE'] = (string)$val->attributes()->{"type"};
                $searchField['SHOW_ALWAYS'] = (string)$val->attributes()->{"showAlways"};
                $searchField['SHOW_NEVER'] = (string)$val->attributes()->{"showNever"};
                $lblVal = (string)$val;
                $searchField['LABEL'] = mlOut("FASTSEARCH.{$lblVal} (Pofile_{$study->user->profile_code}.profileName)", $lblVal);
                $this->fastSearch[] = $searchField;
                $this->hasFastSearch = true;
            }
            foreach ($confs->sidebar->children() as $key => $val) {

                if ((string)$val->attributes()->{"text"} != "") $text = (string)$val->attributes()->{"text"};
                if ((string)$val->text != "") $text = (string)$val->text;
                $text = mlOut("Profile_{$study->user->profile_code}." . $text, $text);
                if ((string)$val->attributes()->{"link"} != "") $link = (string)$val->attributes()->{"link"};
                else $link = "#";
                $thisQs = str_replace("index.php", "", $link);
                $thisQs = str_replace("?", "", $thisQs);
                $activeFlag = false;
                $currQs = trim($_SERVER['QUERY_STRING']," &\t\r\n\0");
                //echo $currQs." / ".$thisQs."<hr/>";

                if ($thisQs == $_SERVER['QUERY_STRING']) {
                	$activeFlag = true;
                } else {
                	//echo ($_SERVER['QUERY_STRING']);
                	if (strlen($thisQs)>0){
	                    if ( (substr($currQs, 0, strlen($thisQs)) === $thisQs) ){
	                    	$activeFlag = true;
	                    } else {
	                    	//False
	                    }
                	}
                }
                $item = new SideBarItem(new Link($text, (string)$val->attributes()->{"icon"}, $link), null, $activeFlag);
                foreach ($val->children()->param as $k1 => $c) {
                    $this->link_params[(string)$c->attributes()->{"name"}] = (string)$c;

                }
                foreach ($val->children()->link as $k => $v) {

                    $text = (string)$v->attributes()->{"text"};
                    $text = mlOut("Profile_{$study->user->profile_code}." . $text, $text);

                    $target = "";
                    if ((string)$v->attributes()->{"target"} != "") $target = (string) $v->attributes()->{"target"} ;
                    if ((string)$v->target != "") $target = (string)$v->target;


                    $link = (string)$v->attributes()->{"value"};
                    $thisQs = str_replace("index.php", "", $link);
                    $thisQs = str_replace("?", "", $thisQs);
                    //if ($thisQs == $_SERVER['QUERY_STRING']) {
                    //    $item->addItem(new SideBarItem(new Link($text, (string)$v->attributes()->{"icon"}, $link), null, true));
                    //} else {
                    //    $item->addItem(new SideBarItem(new Link($text, (string)$v->attributes()->{"icon"}, $link)));
                    //}
                    $activeFlag = false;
                    $currQs = trim($_SERVER['QUERY_STRING']," &\t\r\n\0");
                    //echo $currQs." / ".$thisQs."<hr/>";

                    if ($thisQs == $_SERVER['QUERY_STRING']) {
                    	$activeFlag = true;
                    } else {
                    	//echo ($_SERVER['QUERY_STRING']);
                    	if (strlen($thisQs)>0){
                    		if ( (substr($currQs, 0, strlen($thisQs)) === $thisQs) ){
                    			$activeFlag = true;
                    		} else {
                    			//False
                    		}
                    	}
                    }
                    $item->addItem(new SideBarItem(new Link($text, (string)$v->attributes()->{"icon"}, $link), null, $activeFlag));

                }
                $this->sidebar->addItem($item);
            }
            $showPatientFolder = true;
            if (isset($study->config_service['disablePatientView'][$study->user->profile_code]) && $study->config_service['disablePatientView'][$study->user->profile_code]) $showPatientFolder = false;
            if (isset($_GET[$study->config_service['PK_SERVICE']]) && is_numeric($study->session_vars[$study->config_service['PK_SERVICE']]) && $showPatientFolder) {
                $item = new SideBarItem(new Link(mlOut("System.PatientFolder", "Patient's Folder"), "user-md", "#"), null, true);
                $i = 0;
                //if (!$study->patient_folder["tabs"]){$study->patient_folder["tabs"]=array();}
                //var_dump($study->patient_folder["tabs"]);
                //die();
                foreach ($study->patient_folder["tabs"] as $k => $v) {
                    $selected = false;
                    if ($_GET['VISITNUM'] == $k) $selected = true;
                    $icon = "clipboard ";
                    $subItems[$i] = new SideBarItem(new Link($v, $icon, "#"), null, $selected);
                    foreach ($study->patient_folder["contents"][$k] as $vprogr => $_val2) {
                    	if ($study->patient_folder['visitProgressive'][$k]){
							$visitNumber=$vprogr+1;
							$visitNumberTxt=$visitNumber;
						}else {
							$visitNumberTxt='';
						}
                    	foreach ($_val2 as $esam =>$val2){

	                    	if ($val2['correlated']) continue;
	                        if (isset($val2['corr'])) {
	                            $hasCorrelated = true;
	                            $corrEsam = $val2['corr'];
	                        } else {
	                            $hasCorrelated = false;
	                        }
	                        $progrNumberTxt='';
	                        foreach ($val2 as $progr => $v1) {
	                        	if ($progr . "" != "corr") {
	                                if ($v1['status'] == 'submitted.gif') {
	                                    $linkIcon = "check-square-o green";
	                                }
	                                if ($v1['status'] == NULL || $v1['status'] == "to_be_comp.gif") {
	                                    $linkIcon = "plus blue";
	                                }
	                                if ($v1['status'] == 'saved.gif') {
	                                    $linkIcon = "pencil-square-o orange";
	                                }
									if ($v1['status'] == 'divieto') { //GENHD-44
	                                    $linkIcon = "minus-circle red";
										$v1['link']="#";
	                                }
	                                $progrNumberTxt="$progr";
	                                if ($visitNumberTxt!='') $addNumbers="<sup>".$visitNumberTxt.".".$progrNumberTxt."</sup>";
	                                else $addNumbers="<sup>".$progrNumberTxt."</sup>";
									if (!isset($study->vlist->esams[$k][$esam]['PROGR']) || $study->vlist->esams[$k][$esam]['PROGR']=='' || $form1->form['FIELD_TB_SHOW']) $addNumbers=""; //VMAZZEO 29.01.2016 non faccio vedere i numeri <sup> se ho il field_tb_show
	                                $link = str_replace("<a href=\"", "", $v1['link']);
	                                $link = preg_replace("!\"(.*?)>!", "", $link); 		//VMAZZEO 11.02.2016 modificata replace perchè le schede progressive con FIELD_TB_SHOW non funzionava facendo visualizzare " > accanto al nome della scheda
	                                $selected = false;
	                                if ($_GET['VISITNUM'] == $k && $_GET['ESAM'] == $esam && $_GET['PROGR'] == $progr) $selected = true;
	                                $subItems[$i]->addItem(new SideBarItem(new Link($v1['nome'].$addNumbers, $linkIcon, $link), null, $selected));
	                                if ($hasCorrelated) {
	                                    if (isset($study->patient_folder["contents"][$k][$corrEsam][$progr])) {
	                                        $corrVal = $study->patient_folder["contents"][$k][$corrEsam][$progr];
	                                        if ($corrVal['status'] == 'submitted.gif') {
	                                            $linkIcon = "check-square-o green";
	                                        }
	                                        if ($corrVal['status'] == NULL || $corrVal['status'] == "to_be_comp.gif") {
	                                            $linkIcon = "plus-square blue";
	                                        }
	                                        if ($corrVal['status'] == 'saved.gif') {
	                                            $linkIcon = "pencil-square-o orange";
	                                        }
											if ($corrVal['status'] == 'divieto') { //GENHD-44
	                                            $linkIcon = "minus-circle red";
												$corrVal['link']="#";
	                                        }
	                                        $link = str_replace("<a href=\"", "", $corrVal['link']);
	                                        $link = str_replace("\">", "", $link);
	                                        $selected = false;
	                                        if ($_GET['VISITNUM'] == $k && $_GET['ESAM'] == $corrEsam && $_GET['PROGR'] == $progr) $selected = true;
	                                        $subItems[$i]->addItem(new SideBarItem(new Link($corrVal['nome'].$addNumbers, $linkIcon, $link), null, $selected));
	                                    }
	
	                                }
	                            }
	                        }
	                    }
	                }
                    $i++;
                }
                $item->items = $subItems;
                $this->sidebar->addItem($item);
            }
        }else{
        	$httpCode="401";
        	header("HTTP/1.0 $httpCode Not Found");
        	$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
        	if ($language=='') $language='it';
        	$language=strtoupper($language);
        	if (file_exists("/http/lib/IanusCasDriver/template/httpError_{$httpCode}_{$language}.html")) $errorPage=file_get_contents("/http/lib/IanusCasDriver/template/httpError_{$httpCode}_{$language}.html");
        	else $errorPage=file_get_contents("/http/lib/IanusCasDriver/template/httpError_{$httpCode}_IT.html");
        	die($errorPage);
        }
		return;
	}
	
	
	
	
}

function getEsamName($study, $visitnum, $esam){
	Logger::send("getEsamName - sono qui: $visitnum - $esam");
	return $study->vlist->esams[$visitnum][$esam]['TESTO'];
}

?>