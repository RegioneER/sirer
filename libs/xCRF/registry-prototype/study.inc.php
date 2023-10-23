<?php

/**
 * Classe Studio
 * 
 * Contiene tutte le spcifiche dello studio tra cui il Controller
 *
 * @package XMR 2.0
 */
class Study extends Study_prototype_mxmr {
    var $show_gantt=false;
    
    function breadcrumb($type,$dynamic_link_text){
    	if (isset($this->config_service['disablePatientView'][$this->user->profile_code]) && $this->config_service['disablePatientView'][$this->user->profile_code] && $this->area=='EsamPage'){
    		$paths[]=array("el-icon-home", "Home page", "index.php");
    		Logger::send($this->vlist->esams[$_GET['VISITNUM']][$_GET['ESAM']]['TESTO']);
    		$paths[]=array("el-icon-file", $this->vlist->esams[$_GET['VISITNUM']][$_GET['ESAM']]['TESTO'], "");
    		$this->breadcrumb=new BreadCrumb($paths);
    	} else {
    		parent::breadcrumb($type,$dynamic_link_text);
    	}
    }
    
    /*
    function breadcrumb($type,$dynamic_link_text){
        if($this->session_vars['PUBLIC_SEARCH']){
            $type='altra_list';
            $dynamic_link_text='Richiesta farmaco';
        }
        $menu= parent::breadcrumb($type,$dynamic_link_text);
        $menu=str_replace('&gt;&gt;','<img src="images/frecce_p.png" >', $menu);
        return "<span class='breadcrumb'>".$menu."</span>";
    }
    */
    
    /*
    function href($testo_link, $profondita = 0) {
        
        if (! isset ( $this->hrefs [$testo_link] )) {
            if($this->user->profilo=='Farmacia')    
                $this->hrefs ['Home'] = "index4.html";
            else {
                $this->hrefs ['Home'] = "index2.html";
            }
            
        }
        
        return parent::href($testo_link, $profondita );;
    }
    */
    
    
    function ListPage($percorso_base = null){
    	//if ($this->user->profile_code=='LP') {
    	//	$_GET['list']=$this->session_vars['list']="drug_administration_list.xml";
    		//$this->body="<h2>".mlOut("System.OperationNotPermitted", "Operation not permitted")."</h2>";
    		//return;
    	//}
    	parent::ListPage($percorso_base);
    }

    function CustomPage($page) {
    	$pages['eCRFs']['title']=mlOut("System.StaticPage_eCRFs", "eCRFs");
    	$pages['eCRFs']['html']="eCRFs.html";
    	$pages['help']['title']=mlOut("System.StaticPage_help", "Help");
    	$pages['help']['html']="help.html";
    	$this->page_title=$pages[$page]['title'];
    	
    	$this->body=file_get_contents($pages[$page]['html']);
    	$paths[]=array("el-icon-home", "Home page", "index.php");
    	$paths[]=array("", $pages[$page]['title'], "");
    	$this->breadcrumb=new BreadCrumb($paths);
    }
    
    
    function HomePage() {
    	$this->page_title="";
        /*
        $sql_query1="select count(*) as C, round(ratio_to_report(count(*)) over (),4)*100 as CR, CODE from (
			select distinct userid, CODE from (
			select up.*, sp.* from USERS_PROFILES up, STUDIES_PROFILES sp where up.profile_id=sp.id and study_prefix='PT'
			))group by CODE";
        $sql=new query($this->conn);
        $sql->exec($sql_query1);
        
        while ($sql->get_row()){
        	$data[]['label']=mlOut("Profile_{$sql->row['CODE']}.profileName");
        	$data[count($data)-1]['data']=$sql->row['CR'];
        }
        
        $this->body=drawPieChart(mlOut("UsersProfilesPieChart","UsersProfilesPieChart"), "el-icon-address-book", $data, $bottomBoxes);
    	*/
    	if (file_exists("home_".$this->user->profilo.".html")) $this->body=file_get_contents("home_".$this->user->profilo.".html");
    	else $this->body=file_get_contents("home.html");
    	$paths[]=array("el-icon-home", "Home page", "/index.php");
    	$this->breadcrumb=new BreadCrumb($paths);
    }
    
    /*
    function CheckVisione(){
        if($this->user->profilo=='Drug Company' && (count($_GET)>0 || count($_POST)>0)) error_page($this->session_vars['remote_userid'],'Access not allowed','Access not allowed');
        parent::CheckVisione();
        global $in;
        $str="select count(*) conto from pt_utenti_centri where userid=:remote_user and tipologia=:tipologia";
        $query=new query($this->conn);
        $bind['REMOTE_USER']=$this->session_vars['remote_userid'];
        $bind['TIPOLOGIA']='Farmacia';
        $query->get_row($str,$bind);
        if($query->row['CONTO']>0){
            $in['USER_TIP']=$this->session_vars['USER_TIP']='DE';
        }
        
    }
    
    */
    
    /*
    function SearchPage() {

        $this -> session_vars['source'] = str_replace('|', ',', $this -> session_vars['source']);
        $this -> session_vars['dest'] = str_replace('|', ',', $this -> session_vars['dest']);

        $dir = $_SERVER['PATH_TRANSLATED'];

        $dir = preg_replace("/\/index.php/", "", $dir);
        //$filetxt = file_get_contents($dir.'/template.htm');
        if ($this -> session_vars['FORM'] == 1) {
            $file_form = $this -> xml_dir . "/search_paziente.xml";
        } else if ($this -> session_vars['FORM'] == 2)
            $file_form = $this -> xml_dir . "/search_paziente_rich.xml";
        $xml_form = new xml_form($this -> conn, $this -> service, $this -> config_service, $this -> session_vars, $this -> xml_dir);

        $xml_form -> xml_form_by_file($file_form);
        $xml_form -> open_form();
        $body .= $xml_form -> body;
        //          print_r($this->session_vars);
        ///16/03/2009 Giorgio Delsignore : Bisogna togliere la globale!!!!
        global $in;
        $in = $this -> session_vars;
        if ($this -> session_vars['SEARCH'] == '1')
        $in['list'] = $list = "patients_list_search.xml";
        else if ($this -> session_vars['SEARCH'] == '2')
        $in['list'] = $list = "patients_list_search_rich.xml";
        if($this->session_vars['USER_TIP']=='DM')$in['list'] = $list = "patients_list_search_dm.xml";
        $list_o = new xml_list($this -> xml_dir . "/" . $list);
        if (isset($this -> session_vars['TSEARCH']))
            $body .= $list_o -> list_html();
        $filetxt = preg_replace("/<!--body-->/", $body, $filetxt);
        if($this -> session_vars['SEARCH'] == '1')$script = "<script type=\"text/javascript\">
          function invia_f()
          {
          
         
           
           f=document.forms[0];
           el=f.elements;
          
           specifiche='A=ON&L=0&F=0';
           c1=''+
           '<<fd00###NASCITA_DT###Data di nascita>>'+
          
           '';

           rc=contr(c1,specifiche);
           if (rc) {return false}
           document.forms[0].TSEARCH.value='1';
           document.forms[0].action='index.php';
           document.forms[0].submit();
           }
           function cf(){}
         </script>
          ";
        else{
            $script = "<script type=\"text/javascript\">
          function invia_f()
          {
          
         
           
           f=document.forms[0];
           el=f.elements;
           
           specifiche='A=ON&L=0&F=0';
           c1=''+
           '<<np00###NPROG_RIC###Codice richiesta>>'+
          
           '';

           rc=contr(c1,specifiche);
           if (rc) {return false}
           document.forms[0].TSEARCH.value='1';
           document.forms[0].action='index.php';
           document.forms[0].submit();
           }
           function cf(){}
         </script>
          ";
        }
        $script .= $xml_form -> script_js;
        $codice_sis = $remote_userid - 0;
        $user_name = "<p align=right>
    <br><br><br>";
        //echo "<hr>$nome_user";
        $nome_user = str_replace("\\'", "'", $nome_user);

        $this -> percorso = $this -> breadcrumb("search");
        $body = $this -> percorso . $body;

        $this -> body = $body;
        $this -> script = $script;
    }
    */
    
    function GlobalDbBuild(){
    	if (is_dir("xml")) {
    		if ($dh = opendir("xml")) {
    			while (($file = readdir($dh)) !== false) {
    				if (preg_match("/^visite\_exams/", $file)){
    					echo "<li><a href=\"index.php?BUILD_DB&conf=$file\">Costruisci db per configurazione: $file</a></li>";
    				}
    				}
    				closedir($dh);
    			}
    			}
    			$sql="select PT_VALUTAZIONE from PT_LISTA_PT";
			$query=new query($this->conn);
    					$query->exec($sql);
    					$pianiTer="";
    					while ($query->get_row()){
    					$pianiTer[]=$query->row['PT_VALUTAZIONE'];
    					}
    					if (isset($_GET['conf'])){
    					$this->visit_structure_xml=$_GET['conf'];
    					$this->VisitStructure();
    							$body="";
    							$tbs="";
    							foreach ($this->es_form as $visit=>$tmp1){
    							foreach ($tmp1 as $esam=>$f){
    	
    								if (file_exists($this->xml_dir . '/' . $f)){
    								$this->session_vars ['form'] = $f;
    									$vlist = $this->vlist;
    									$in = $this->session_vars;
    									$conn = $this->conn;
    									$service = $this->service;
    									$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
    										
    									$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $f );
    									if (! $xml_form->allinea_db ()) {
    									$tbs[$xml_form->form['TABLE']]=1;
    									}
    									}else {
    									$alert[]="Attenzione il file $f non &egrave; presente!";
    									}
    									foreach ($pianiTer as $key=>$val){
    									$f1=$f;
    									$f1=preg_replace("/\.xml/", "_{$val}.xml", $f1);
    									if (file_exists($this->xml_dir . '/' . $f1)){
    									$this->session_vars ['form'] = $f1;
    											$vlist = $this->vlist;
    											$in = $this->session_vars;
    											$conn = $this->conn;
    											$service = $this->service;
    											$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
    	
    											$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $f1 );
    													if (! $xml_form->allinea_db ()) {
    													$tbs[$xml_form->form['TABLE']]=1;
    													}
    									}
    									}
    	
    	
    								}
    							}
    							if (is_array($alert) && count($alert)>0){
    								foreach ($alert as $k=>$v){
    									echo "<li style='color:red'>$v</li>";
    								}
    							}
    							if (is_array($tbs) && count($tbs)>0){
    							foreach ($tbs as $tb=>$v){
    							$body.="<li>Tabella $tb da creare/aggiornare</li>";
    							}
    							echo $body;
    							echo "<br/><a href=\"index.php?BUILD_DB&conf={$_GET['conf']}&CREATE=true\">Aggiorna</a>";
    							}else {
					echo "La configurazione &egrave allineata con il DB!";
    	}
    	}
    	    		die();
    }
    
    function checkPatientAccess($pk_value){
    	
    	$bind['PK_SERVICE']=$pk_value;
    	$sql_query="select CENTER from ".$this->service."_REGISTRAZIONE where ".$this->config_service['PK_SERVICE']."=:PK_SERVICE";
    	$sql=new query($this->conn);
    	$sql->get_row($sql_query, $bind);
    	$userCannotAccess=true;
    	foreach ($this->user->sites as $key=>$val){
    		if ($key==$sql->row['CENTER']) $userCannotAccess=false;
    	}
    	if ($userCannotAccess){
    		error_page($this->user->userid, "xCRF - DR - Cannot Access to patient with code $pk_value", "xCRF - DRUG - Cannot Access");
    	}
    }
    
    function formTestSteps($xml){
    	$xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
    	$xml_form->xml_form_by_file ( $this->xml_dir . '/' . $xml.".xml" );
    	foreach ($xml_form->fields as $key=>$field){
    		if ($field['TYPE']=='hidden') {
    			$idField=$field['VAR'];
    			$this->fieldIds[]=$idField;
    			$this->fieldLabel[$idField]=mlOut($xml.".".$field['VAR']);
    			continue;
    		}
    		if ($field['VAR']=="") continue;
    		$idField=$field['VAR'];
    		$this->fieldIds[]=$idField;
    		$this->fieldLabel[$idField]=mlOut($xml.".".$field['VAR']);
    		if ($field['TYPE']=='textbox') $fieldType=$field['VAR_TYPE'];
    		else $fieldType=$field['TYPE'];
    		if ($fieldType=="") $fieldType="label";
    		$this->fieldDataType[$idField]=$fieldType;
    		if ($field['SEND']=='obbligatorio') {
    			$this->fieldMandatory[$idField]=true;
    		}else $fieldMandatory[$idField]=false;
    		if (isset($field['VALUE'])){
    			foreach ($field['VALUE'] as $k=>$v){
    				$this->fieldValues[$idField][$k]=$v;
    			}
    		}
    		if (isset($field['MAX'])) $this->maxCondition[$idField]=$field['MAX'];
    		if (isset($field['MIN'])) $this->minCondition[$idField]=$field['MIN'];
    		
    		if (isset($field['CONDITION'])){
    			if (isset($field['HIDE'])) {
    				$conditionValue=$field['CONDITION_VALUE'];
    				$conditionField=$field['CONDITION'];
    				if (!isset($this->fieldDataType[$conditionField])){
    					$checkFound=false;
    					foreach ($this->fieldValues as $checkField => $checkLabel){
    						if ($checkFound) continue;
    						foreach ($checkLabel as $lKey=>$lval){
    							if ($checkFound) continue;
    							if ($conditionField==$lKey){
    								$checkFound=true;
    								$conditionField=$checkField;
    								$conditionValue="$lval checked";
    							}
    						}
    					}
    				}
    				
    				if ($conditionValue=='') $conditionValue="empty string";
    				if ($this->fieldDataType[$conditionField]=='select') $conditionValue="'".$this->fieldValues[$conditionField][$conditionValue]."'";
    				$this->fieldMasterSlave[$conditionField][$conditionValue][]=$idField;
    				$this->fieldSlaveMaster[$idField][$conditionValue]=$conditionField;
    			}
    		}
    	}
    	$ret="<table border=1>";
    	foreach ($this->fieldMasterSlave as $master => $val1){
    		$ret.=$this->printPosCondition($master, $val1);
    		$ret.=$this->printNegCondition($master, $val1);
    	}
    	foreach ($this->fieldIds as $key=>$val){
    		$ret.=$this->maxCheck($val);
    		$ret.=$this->minCheck($val);
    	}
    	$ret.="<tr><td>Fill the form with the following rules:".$this->presubmissionCheck."<br/>
    			Fill in all the mandatory fields and submit the form
    			</td><td>Form correctly submitted</td></tr>";
    	$ret.="</table>";
    	die($ret);
    }
    
    function minCheck($idField){
    	$ret="";
    	if (isset($this->minCondition[$idField]) && !isset($this->minConditionRendered[$idField])){
    		$this->minConditionRendered[$idField]=true;
    		$ret.="<tr><td>Fill the field \"".$this->fieldLabel[$idField]."\" with a value lesser than ".$this->getLabelForField($this->minCondition[$idField])."</td>
    				<td>The system will show a range error</td></tr>
    				";
    		$this->presubmissionCheck.="<li>\"".$this->fieldLabel[$idField]."\" with a value lesser than ".$this->getLabelForField($this->minCondition[$idField])."</li>";
    	}
    	return $ret;
    }
    
    function maxCheck($idField){
    	$ret="";
    	if (isset($this->maxCondition[$idField]) && !isset($this->maxConditionRendered[$idField])){
    		$this->maxConditionRendered[$idField]=true;
    		$ret.= "<tr><td>Fill the field \"".$this->fieldLabel[$idField]."\" with a value greater than ".$this->getLabelForField($this->maxCondition[$idField])."</td>
    				<td>The system will show a range error</td>
    				</tr>";
    		$this->presubmissionCheck.= "<li>\"".$this->fieldLabel[$idField]."\" with a value greater than ".$this->getLabelForField($this->maxCondition[$idField])."</li>";
    	}
    	return $ret;
    }
    
    function getLabelForField($field){
    	$orig_field=$field;
    	if (preg_match("!,!", $field)){
    		$split=explode(",",$field);
    		$ret="";
    		foreach ($split as $k=>$v){
    			if ($ret!="") $ret.=" or ";
    			$ret.=$this->getLabelForField($v);
    		}
    		return $ret;
    	}
    	if ($field=='sysdate') return "today";
    	$field=str_replace("[", "", $field);
    	$field=str_replace("]", "", $field);
    	if (isset($this->fieldLabel[$field])) return $this->fieldLabel[$field];
    	else return $orig_field;
    }
    
    function printPosCondition($master, $val1){
    	
    	foreach ($val1 as $conditionValue=>$fields){
    		if (isset($this->posRendered[$master][$conditionValue]) && $this->posRendered[$master][$conditionValue]) continue;
    		$ret="<tr>";
    		$this->posRendered[$master][$conditionValue]=true;
    		$conditionPassed="";
    		if (count($fields)==1) $singPlur="field is";
    		else $singPlur="fields are";
    		if ($this->fieldLabel[$master]==""){
    			$checkFound=false;
    			foreach ($this->fieldValues as $checkField => $checkLabel){
    				if ($checkFound) continue;
    				foreach ($checkLabel as $lKey=>$lval){
    					if ($checkFound) continue;
    					if ($master==$lKey){
    						$checkFound=true;
    						$label=$this->fieldLabel[$checkField]." -> ".$lval;
    					}
    				}
    			}
    			$ret.="<td>Check the field \"$label\" and verify that the following fields/labels are visible";
    		}
    		else $ret.="<td>Fill the field \"".$this->fieldLabel[$master]."\" with ".$conditionValue." and verify that the following {$singPlur} visible";
    		foreach ($fields as $k=>$v){
    			$conditionPassed[$v]=true;
    			$ret.="<li>\"".$this->fieldLabel[$v]."\"</li>";
    		}
    		$ret.="
    				<td valign=top>".ucfirst($singPlur)." visible</td>
    				</td>
    			</tr>";
    		foreach ($conditionPassed as $k=>$v){
    			$ret.=$this->printPosCondition($k, $this->fieldMasterSlave[$k]);
    			$ret.=$this->maxCheck($k);
    			$ret.=$this->minCheck($k);
    			$ret.=$this->printNegCondition($k, $this->fieldMasterSlave[$k]);	
    		}
    		
    	}
    	return $ret;
    }
    
    function printNegCondition($master, $val1){
    	foreach ($val1 as $conditionValue=>$fields){
    		if (isset($this->negRendered[$master][$conditionValue]) && $this->negRendered[$master][$conditionValue]) continue;
    		$ret="<tr>";
    		 
    		$this->negRendered[$master][$conditionValue]=true;
    		$conditionPassed="";
    		if (count($fields)==1) $singPlur="field is";
    		else $singPlur="fields are";
    		if ($this->fieldLabel[$master]==""){
    			$checkFound=false;
    			foreach ($this->fieldValues as $checkField => $checkLabel){
    				if ($checkFound) continue;
    				foreach ($checkLabel as $lKey=>$lval){
    					if ($checkFound) continue;
    					if ($master==$lKey){
    						$checkFound=true;
    						$label=$this->fieldLabel[$checkField]." -> ".$lval;
    					}
    				}
    			}
    			$ret.= "<td>If \"$label\" is checked then the following fields/label must be hidden";
    		}
    		else $ret.= "<td>Fill the field \"".$this->fieldLabel[$master]."\" with a value different from ".$conditionValue." and verify that the following {$singPlur} not visible";
    		foreach ($fields as $k=>$v){
    			$conditionPassed[$v]=true;
    			$ret.= "<li>\"".$this->fieldLabel[$v]."\"</li>";
    		}
    		$ret.="
    				</td>
    				<td valign=top>".ucfirst($singPlur)." not visible</td>
    			</tr>";
    	}
    	return $ret;
    }
    
    function Controller(){
    	if (isset($_GET['exams']) && $this->user->profilo=='LP'){
    		Logger::send("Mi trovo in questo caso");
			$sql_query="select * from {$this->service}_COORDINATE where {$this->config_service['PK_SERVICE']}=:pkservice and esam=3 and create_user=:userid order by SEND_DT desc";
			$bind['pkservice']=$_GET[$this->config_service['PK_SERVICE']];
			$bind['userid']=$this->user->userid;
			Logger::send($bind);
			$sql=new query($this->conn);
			if ($sql->get_row($sql_query, $bind)){
				Logger::send($sql->row);
				unset($_GET['exams']);
				$_GET['ESAM']=$sql->row['ESAM'];
				$_GET['PROGR']=$sql->row['PROGR'];
				$_GET['VISITNUM_PROGR']=$sql->row['VISITNUM_PROGR'];
				$_GET['VISITNUM']=$sql->row['VISITNUM'];
				$_GET['form']='dispensazione.xml';
				$link_to="index.php?&CODPAT={$_GET[$this->config_service['PK_SERVICE']]}&CENTER&ESAM={$sql->row['ESAM']}&PROGR={$sql->row['PROGR']}&VISITNUM={$sql->row['VISITNUM']}&VISITNUM_PROGR={$sql->row['VISITNUM_PROGR']}&form=dispensazione.xml";
	    		header("location: ".$link_to);
	    		die();
			}
		}
    	if (isset($_GET['page'])){
    		$this->CustomPage($_GET['page']);
    	}
    	if (isset($_GET['BUILD_DB'])){
    		$this->GlobalDbBuild();
    		die();
    	}
    	if (isset($_GET[$this->config_service['PK_SERVICE']]) && $_GET[$this->config_service['PK_SERVICE']]!="next"){
    		$pk_value=$_GET[$this->config_service['PK_SERVICE']];
    		$this->checkPatientAccess($pk_value);
    	}
    	
    	if (isset($_POST[$this->config_service['PK_SERVICE']]) && $_POST[$this->config_service['PK_SERVICE']]!="next"){
    		$pk_value=$_POST[$this->config_service['PK_SERVICE']];
    		$this->checkPatientAccess($pk_value);
    	}
    	
    	if($this->session_vars['home']){
            $this->HomePage ();
        }     
        if($this->session_vars['prendiInCarico']!='' && $this->session_vars['CENTER']){          
            $this->moveObjectTo($this->session_vars['PKToMove'],$this->session_vars['CENTER']);
            $this->conn->commit();
            header("Location:index.php?&exams=visite_exam.xml&{$this->config_service['PK_SERVICE']}={$this->session_vars['PKToMove']}&CENTER={$this->session_vars['CENTER']}");
            die();
        }
        if (isset ( $this->session_vars ['PUBLIC_SEARCH'] ) ) {
            if($this->vlist->esams[$this->session_vars['VISITNUM']][$this->session_vars['ESAM']]['PUBLIC_SEARCH']!='yes'){
                error_page($this->session_vars['remote_userid'],'Accesso non autorizzato');
            }
            $this->pk_service=$this->session_vars [$this->config_service['PK_SERVICE']]=$this->session_vars ['PUBLIC_SEARCH'];
            $this->EsamPage();
            return;
        }
        if (isset($_POST['CHECK_CU'])){
        	$this->checkCU($_POST['CU'], $_POST['PK_SERVICE']);
        }
        parent::Controller();
        if (isset($_GET['testXml'])){
        	$this->formTestSteps($_GET['testXml']);
        }
    }
    
    function checkCU($cu, $pk_service){
    	$sql_query="
select f.* from {$this->service}_RICH_FARMACO f, {$this->service}_REGISTRAZIONE r where f.CU=:CU and r.{$this->config_service['PK_SERVICE']}=f.{$this->config_service['PK_SERVICE']} and f.{$this->config_service['PK_SERVICE']}=:pk_service and r.center in (select center from {$this->service}_UTENTI_CENTRI where userid=:userid)
    	";
    	$bind['CU']=$cu;
    	$bind['PK_SERVICE']=$pk_service;
    	$bind['USERID']=$this->user->userid;
    	Logger::send($bind);
    	Logger::send($sql_query);
    	$sql=new query($this->conn);
    	$result['status']='NOT_FOUND';
    	if ($sql->get_row($sql_query, $bind)){
    		$progr=$sql->row['PROGR'];
    		$center=$sql->row['CENTER'];
    		Logger::send($sql->row);
    		$sql_check2="select * from {$this->service}_COORDINATE where ESAM=3 and PROGR={$progr} and {$this->config_service['PK_SERVICE']}=:pk_service and INIZIO is null and FINE is null";
    		unset($bind['CU']);
    		unset($bind['USERID']);
 			if ($sql->get_row($sql_check2, $bind)){
 				$result['status']='FOUND';
 				$result['link_to']="index.php?CENTER={$center}&CODPAT={$pk_service}&VISITNUM=3&ESAM=3&PROGR={$progr}&form=dispensazione.xml";
 			} else {
 				$result['status']='ALREADY_INSERTED';
 				$sql_data="select A.NOME, A.COGNOME, A.AZIENDA_ENTE, to_char(SEND_DT,'DD/MM/YYYY') as SENDDT from {$this->service}_COORDINATE C, ANA_UTENTI A 
 				where C.ESAM=3 and C.PROGR={$progr} and C.{$this->config_service['PK_SERVICE']}=:pk_service
 				and A.USERID=C.CREATE_USER
 				";
 				$sql->get_row($sql_data,$bind);
 				if ($sql->row['AZIENDA_ENTE']!="") $add="(".$sql->row['AZIENDA_ENTE'].")";
 				$result['insertedBy']="{$sql->row['NOME']} {$sql->row['COGNOME']} {$sql->row['AZIENDA_ENTE']} ".$add;
 				$result['insertedOn']="{$sql->row['SENDDT']}";
 				
 			}	
    	} 
    	header('Content-Type: application/json');
    	echo json_encode($result);
    	die();
    }
    
    
    
    /**
     * Effettua il salvataggio in DB (gestione invio)
     */
    function invia_form($xml_form, $in_s) {
        $conn = $this->conn;
        $in = $this->in;
        //      global $config_service;
        $in = $in_s;
        $debug = 1;
        $f_prepare = $xml_form->form ['FUNC_PREPARE'];
        Logger::send($f_prepare);
         
        if (function_exists ( $f_prepare ))
        $xml_form=$f_prepare ( $xml_form );
        $this->audit_trail($xml_form);
        $query = new query ( $conn );

        $xml_form->query_builder ();
        $this->errors = $xml_form->getErrors ();
        $this->addSendCoordInfo($xml_form, $in);
        $f_to_call = $xml_form->form ['F_TO_CALL'];
		if (function_exists ( $f_to_call )) {
		    $f_to_call ( $xml_form );
        }
        elseif ($f_to_call!=""){
        	if ($xml_form->session_vars['PROGR']=='') $xml_form->session_vars['PROGR']=1;
            if ($xml_form->session_vars['VISITNUM_PROGR']=='') $xml_form->session_vars['VISITNUM_PROGR']=0;
            foreach ($xml_form->session_vars as $key=>$val){
                $vars[$key]=$val;
            }
            include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/activitiClient.inc";
            $service=new ActivitiService("admin", "xxx");
            $vars['connectId']='devService';
            $vars['studyPrefix']='PT';
            $vars['pkService']='CODPAT';
            if (!isset($xml_form->session_vars['ajax_call'])) $vars['ajax_call']='';
            $process=$service->startProcess($f_to_call, $vars);
        }
        for($i = 0; $i < count ( $xml_form->query_enable ); $i ++) {
            $query->set_sql ( $xml_form->query_enable [$i] );
            $query->ins_upd ();//non richiede binding
        }

    }
    
    function moveObjectTo($pk,$center){
       $bind['REMOTE_USERID']=$this->session_vars['remote_userid'];
       $bind['PK_SERVICE']=$pk;
       $bind_center['PK_SERVICE']=$pk;
       $bind_center['CENTER']=$center;
        foreach($this->vlist->esams as $visitnum => $currVisit){
            foreach($this->vlist->esams[$visitnum] as $esam => $currEsam){
                $form=$currEsam['XML'];               
                $xml_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
                $xml_form->xml_form_by_file ( $this->xml_dir . '/' . $form );
                $table=$xml_form->form['TABLE'];
                $sql_storico='insert into S_'.$table.' (select :remote_userid,sysdate,storico_id.nextval,\'T\',null, t.* from '.$table.' t where '.$this->config_service['PK_SERVICE'].'=:pk_service)';
                $query=new query($this->conn);
                $query->exec($sql_storico,$bind);
                $sql='update '.$table.' set center=:center where '.$this->config_service['PK_SERVICE'].'=:pk_service';
                $query->exec($sql,$bind_center);
            }
        }
        
    }

    function evaluate_pt($xml){
        if($this->config_service['PT_FIELD']!=''  ){
            foreach($this->config_service['PT_FIELD'] as $key => $val){
                $pt_visit=$key;
                foreach($val as $key2 => $val2){
                    $pt_esam=$key2;
                    $pt_field=strtoupper($val2);
                    break 2;
                }
            }
            
            //$pt_field=strtoupper($this->config_service['PT_FIELD'][$this->session_vars['VISITNUM']][$this->session_vars['ESAM']]);
            if($this->session_vars[$pt_field]!='' && $this->session_vars['VISITNUM']==$pt_visit &&  $this->session_vars['ESAM']==$pt_esam ){
                $str="select PT_VALUTAZIONE from {$this->service}_{$this->config_service['PT_TABLE']} where PT_CODE=:pt_code";
                $this->session_vars['PT_CONFIG']['PT_FIELD']=$bind['PT_CODE']=$this->session_vars[$pt_field];

                $query=new query($this->conn);
                $query->get_row($str,$bind);
                unset($bind);
                $ret['SUFFIX']=$query->row['PT_VALUTAZIONE'];
                $newXml=str_replace('.xml', '_'.$query->row['PT_VALUTAZIONE'].'.xml', $xml);
                if(file_exists($this->xml_dir.'/'.$newXml))$xml=$newXml;
            }    
            else if (false && $this->session_vars['VISITNUM']==$pt_visit &&  $this->session_vars['ESAM']==$pt_esam ){
                $pt_to_verify=true;
            }else{

                $pt_xml=$this->vlist->esams[$pt_visit][$pt_esam]['XML'];
                $pt_form = new xml_form ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->uploaded_file_dir );
                $pt_form->xml_form_by_file ( $this->xml_dir . '/' . $pt_xml );
                $pt_table=$pt_form->form['TABLE'];
                $str_pt="select {$pt_field} from {$pt_table} where {$this->config_service['PK_SERVICE']}=:pk_service and visitnum=:visitnum and esam=:esam and progr=1 and visitnum_progr=0";
                $bind_pt['PK_SERVICE']=$this->pk_service;
                $bind_pt['VISITNUM']=$pt_visit;
                $bind_pt['ESAM']=$pt_esam;
                $query=new query($this->conn);
                $query->get_row($str_pt,$bind_pt);
                $str="select PT_VALUTAZIONE from {$this->service}_{$this->config_service['PT_TABLE']} where PT_CODE=:pt_code";
                $this->session_vars['PT_CONFIG']['PT_FIELD']=$bind['PT_CODE']=$query->row[$pt_field];

                $query=new query($this->conn);
                $query->get_row($str,$bind);
                unset($bind);
                $newXml=str_replace('.xml', '_'.$query->row['PT_VALUTAZIONE'].'.xml', $xml);
                $ret['SUFFIX']=$query->row['PT_VALUTAZIONE'];
                if(file_exists($this->xml_dir.'/'.$newXml))$xml=$newXml;
                
            }
        }
        $ret['XML']=$xml;
        $ret['PT']=$this->session_vars['PT_CONFIG']['PT_FIELD'];
        if($this->session_vars['USER_TIP']!='DE'){
            $this->session_vars['NOME']='***';
            $this->session_vars['COGNOME']='***';
            $this->session_vars['CODFISC']='***';
            //$this->session_vars['NASCITA_DT']='***';
        }
        return $ret;
    }
     function pt_ivabradina($xml_form){
        $str="ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY'";
            //$excel_sql->set_sql($str);
        $query=new query($this->conn);
        $query->exec($str);
          
        $str='select * from pt_registrazione where codpat=:codpat';
        $bind['CODPAT']=$xml_form->session_vars['CODPAT'];
        $query=new query($this->conn);
        $query->get_row($str,$bind);
        $xml_form->session_vars=array_merge($query->row,$xml_form->session_vars);
        $str='select * from pt_valutazione where codpat=:codpat';
        $bind['CODPAT']=$xml_form->session_vars['CODPAT'];
        $query=new query($this->conn);
        $query->get_row($str,$bind);
        $xml_form->session_vars=array_merge($query->row,$xml_form->session_vars);
        $str="select denom center_denom from PT_CENTRI where center=:center";
        $bind_center['CENTER']=$this->session_vars['CENTER'];
        $query->get_row($str,$bind_center);
        $xml_form->session_vars=array_merge($query->row,$xml_form->session_vars);
        if($xml_form->session_vars['PRECEDENTE_CURA']==2){
            $xml_form->session_vars['PRIMA_PRESCRIZIONE']='X';
            $xml_form->session_vars['PROSECUZIONE']='&nbsp;&nbsp;&nbsp;';
        }
        else{
            $xml_form->session_vars['PRIMA_PRESCRIZIONE']='&nbsp;&nbsp;&nbsp;';
            $xml_form->session_vars['PROSECUZIONE']='X';
        }
        if($xml_form->session_vars['FARMACO']==2){
            $xml_form->session_vars['FARMACO2']='X';
            $xml_form->session_vars['FARMACO1']='&nbsp;&nbsp;&nbsp;';
        }
        else{
            $xml_form->session_vars['FARMACO1']='X';
            $xml_form->session_vars['FARMACO2']='&nbsp;&nbsp;&nbsp;';
        }
        global $in;
        $in=$xml_form->session_vars;
        return $xml_form;
    }
    
    function pt_lamivudina($xml_form){
        $str="ALTER SESSION SET NLS_DATE_FORMAT='DD/MM/YYYY'";
            //$excel_sql->set_sql($str);
        $query=new query($this->conn);
        $query->exec($str);
          
        $str='select * from pt_registrazione where codpat=:codpat';
        $bind['CODPAT']=$xml_form->session_vars['CODPAT'];
        $query=new query($this->conn);
        $query->get_row($str,$bind);
        $xml_form->session_vars=array_merge($query->row,$xml_form->session_vars);
        $str='select * from pt_valutazione where codpat=:codpat';
        $bind['CODPAT']=$xml_form->session_vars['CODPAT'];
        $query=new query($this->conn);
        $query->get_row($str,$bind);
        $xml_form->session_vars=array_merge($query->row,$xml_form->session_vars);
        $str="select denom center_denom from PT_CENTRI where center=:center";
        $bind_center['CENTER']=$this->session_vars['CENTER'];
        $query->get_row($str,$bind_center);
        $xml_form->session_vars=array_merge($query->row,$xml_form->session_vars);
        if($xml_form->session_vars['PRECEDENTE_CURA']==2){
            $xml_form->session_vars['PRIMA_PRESCRIZIONE']='X';
            $xml_form->session_vars['PROSECUZIONE']='&nbsp;&nbsp;&nbsp;';
        }
        else{
            $xml_form->session_vars['PRIMA_PRESCRIZIONE']='&nbsp;&nbsp;&nbsp;';
            $xml_form->session_vars['PROSECUZIONE']='X';
        }
        if($xml_form->session_vars['FARMACO']==3){
            $xml_form->session_vars['FARMACO3']='X';
            $xml_form->session_vars['FARMACO4']='&nbsp;&nbsp;&nbsp;';
        }
        else{
            $xml_form->session_vars['FARMACO4']='X';
            $xml_form->session_vars['FARMACO3']='&nbsp;&nbsp;&nbsp;';
        }
        global $in;
        $in=$xml_form->session_vars;
        return $xml_form;
    }

    //function form($xml, $col_modifica = true, $no_link_back=false){
    //    $pt_info=$this->evaluate_pt($xml);
    //    $xml=$pt_info['XML'];
    //    parent::form($xml, $col_modifica, $no_link_back);
    //}
    //function printable_form($esam, $visitnum, $visitnum_progr, $progr, $footer_header=false) {
	//	echo("printable form<br/>");
    //	return parent::printable_form($esam, $visitnum, $visitnum_progr, $progr, $footer_header);
    //}

    function make_patient_table(){
       
        $sql_query="
        select a.center,
               a.{$this->config_service['PK_SERVICE']},
               a.nome||' '||a.cognome paziente,
               a.d_sesso as sesso,
               to_char(coor.INSERTDT,'DD/MM/YYYY') REG_DT,
               c.denom as site
               
          from {$this->service}_REGISTRAZIONE a,{$this->service}_coordinate coor, {$this->service}_centri c
          where 
           c.center=a.center
           and a.{$this->config_service['PK_SERVICE']}=:pk_service
           and coor.{$this->config_service['PK_SERVICE']}=a.{$this->config_service['PK_SERVICE']}
           and coor.visitnum=a.visitnum
           and coor.visitnum_progr=a.visitnum_progr
           and coor.esam=a.esam
           and coor.progr=a.progr
           
         
         ";
        $bind['PK_SERVICE']=$this->pk_service;
       $sql=new query($this->conn);
        $sql->get_row($sql_query,$bind);
        	$addFields="<td class=destra >".mlOut("SummaryTable.PatName", "Pat. Name").":</td>
					               	<td class=input><b> {$sql->row['PAZIENTE']}&nbsp;</b></td>
					               	";
        $tabella="
        		<div class=\"widget-box\">
					<div class=\"widget-header header-color-blue\">
						<h5 class=\"bigger lighter\">
						<i class=\"fa fa-user\"></i>
						".mlOut("SummaryTable.Header", "Patient summary")."
						</h5>
					</div>
					<div class=\"widget-body\">
						<div class=\"widget-main no-padding\">
							<table class=\"table table-striped table-bordered table-hover\">
								<tr>             
					                <td class=\"destra\" >".mlOut("SummaryTable.Code", "Pat. Code").":</td>
					               	<td class=\"input\"><b> {$sql->row['PTID']}&nbsp;</b></td>
					               	$addFields
					               	<td class=\"destra\" >".mlOut("SummaryTable.SiteName", "Site").":</td>
					               	<td class=\"input\"><b> {$sql->row['SITE']}&nbsp;</b></td>
					               	
					               	
					                <td class=destra >".mlOut("SummaryTable.gdener", "Sesso").":</td>
        							<td class=input><b> {$sql->row['SESSO']}&nbsp;</b></td>
					               
					                
					            </tr>
					        </table>
					    </div>
					</div>
				</div>
			
                ";
        $this->patient_table=$tabella;
    }
    
    function getStudyTitle(){ //TO-REMOVE!!
    	return "Oncology Drug Registry";
    }
    
}

?>