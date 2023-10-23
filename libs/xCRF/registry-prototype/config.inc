<?
error_reporting(E_ERROR);
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/http_lib.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/db.inc";
if(file_exists('xmr_arno.inc')){
    $conn=new dbconn();
    include_once('xmr_arno.inc');
}
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xml_parser_wl.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/HTML_Parser.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/page.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/vlist.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/list.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/legend.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/esams_list.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/form.inc";

include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/study_prototype.inc";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/xmrwf.inc.php";
include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/send_email_common.inc";


$config_service['ALLOW_BLANK_VPROGR']=true;
$config_service['ALLOW_BLANK_PROGR']=true;
$config_service['mostraDataInvio']=true;
$editing=false;
$email_admin="c.contino@cineca.it";
$root=$_SERVER['DOCUMENT_ROOT'];
$dir=$_SERVER['PATH_TRANSLATED'];
$dirs=explode("/", $dir);
$dir='';
for ($i=0;$i<count($dirs)-1;$i++){
	$dir.=$dirs[$i]."/";
}
$dir=rtrim($dir, "/");
$config_service['ammetti_parentesi_js']=true;
$config_service['PARSER_CHARSET']='none';
$config_service['checkConsistence']=false;
$config_service['SHOW_MANDATORY_ON_HIDE']=true;
$config_service['auto_facoltativi']=true;

$config_service['RPP']='10';


//landscape_mode per crf pdf
$config_service['LANDSCAPE_MODE']=true;
//data nell'header per crf pdf
$config_service['HEADER_DATE']=true;
//Centro e Paziente per crf pdf (necessario anche il parametro GET)
$config_service['PATID']=true; 
//pdf generato tramite libreria avanzata
$config_service['CRF_AUDIT_TRAIL']=false;

/* Nuova gestione log_trace sulla partizione data */
require_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/log_trace.php";

//if (!is_dir($GLOBALS['dir']."/log_trace")) {
//	mkdir($GLOBALS['dir']."/log_trace", 0777);
//	chmod($file_log, 0777);
//	chmod($GLOBALS['dir']."/log_trace", 0777);
//}

$xml_dir=$dir."/xml";
$file_log=$dir."/log_trace/".strtoupper($in['remote_userid']).".log";
$log_conn=new dbconn();
$q_log=new query($log_conn);
$str="select count(*) conto from user_sequences where sequence_name='SESSIONS_SEQ'";
$q_log->get_row($str);
if($q_log->row['CONTO']==0){
    $sql="select max(id) as ID from sessions";
    $q_log->set_sql($sql);
    $q_log->exec();
    $q_log->get_row();
    $max=$q_log->row['ID']+1;
    $seq_create="CREATE SEQUENCE SESSIONS_SEQ INCREMENT BY 1 START WITH {$max} NOCACHE";
    $q_log->ins_upd($seq_create);
}
$sql="select SESSIONS_SEQ.nextval as ID from dual";
$q_log->set_sql($sql);
$q_log->exec();
$q_log->get_row();
$session_number=$q_log->row['ID']+1;
$log_str="<session $session_number><hr><b>Script : index.php</b><br><b>Parametri di input</b><ul>";
foreach($in as $key=> $val) $log_str.="<li>$key: $val</li>";
$log_str.="</ul></session>";
$handle = fopen($file_log, 'a+');
fwrite($handle, $log_str);
fclose($handle);
$sql="insert into sessions(id, userid, data) values($session_number, '".$remote_userid."', sysdate)";
$q_log->set_sql($sql);
$q_log->ins_upd();
$log_conn->commit();
$template_dir=$dir;

$conn=new dbconn();
$sql=new query($conn);

$sql->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
$sql->ins_upd();

// function registrazione($xml_form){
    // $in=$xml_form->session_vars;
    // $conn=$xml_form->conn;
    // $service=$xml_form->service;
    // $config_service=$xml_form->config_service;

    // if($in['USER_TIP']=='DE'){
        // $str="select count({$config_service['PK_SERVICE']}) conto from {$service}_registrazione where codfisc=:codfisc and pt=:pt";
        // $bind['CODFISC']=$in['CODFISC'];
        // $bind['PT']=$in['PT'];
        // $query=new query($conn);
        // $query->get_row($str,$bind);
        // Logger::send($str);
        // Logger::send($bind);
        // Logger::send($query->row);
       
        // if($query->row['CONTO']>0){
            // if($query->row['CONTO']>1){
                // mail("g.delsignore@cineca.it", "Errore[".$in['remote_userid']."] - PT duplicato","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n");
            // }
            // $str="select {$config_service['PK_SERVICE']},(select count(center) from {$service}_utenti_centri where userid=:remote_userid and center=r.center) is_mine from {$service}_registrazione r where codfisc=:codfisc and pt=:pt";
            // $query=new query($conn);
            // $bind['REMOTE_USERID']=$in['remote_userid'];
            // $query->get_row($str,$bind);
            // Logger::send($str);
            // Logger::send($bind);
            // Logger::send($query->row);
            // if($query->row['IS_MINE']=='0'){
                // $body="Il paziente indicato &egrave; gi&agrave; seguito per il piano terapeutico presso un'altra struttura. Si vuole procedere con la presa in carico del paziente? <br>
                // <form method='POST' ><input type='hidden' name='PKToMove' value='{$query->row[$config_service['PK_SERVICE']]}' /><input type='submit' name='prendiInCarico' value='S&igrave;, prendi in carico' /><input type='button' name='tornaHome' value='No, torna alla home' onclick='location.href=\"index.php\";' /></form>
                // ";
            // }else{
                // $body="Il paziente indicato &egrave; gi&agrave; seguito per il piano terapeutico presso questa struttura. <br>
                // <a href='index.php?&exams=visite_exam.xml&{$config_service['PK_SERVICE']}={$query->row[$config_service['PK_SERVICE']]}'>Vai al piano terapeutico</a>
                // ";
            // }
            // global $filetxt;
            // $filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
            // echo $filetxt;
            
            // die();
        // }
        
    // }
    // return $xml_form;
// }


function registrazione($xml_form){

    global $conn, $in, $service;

    $session_vars = $xml_form->session_vars;

    if (isset($in['ID_QUERY']) || ($in['USER_TIP']=='DM')){
        return;
    }
    if ($_POST['OMO_CHECK_OK']=='1'){
        return;
    }

    if (!isset($in['ajax_call'])){
//      foreach ($_POST as $key => $val)
//      {
//          $_POST[$key]=str_replace("'", "''", $_POST[$key]);
//          //echo "$key: $in[$key]<hr>";
//      }
        $array_bind = array();
        $array_bind['CODPAT']= $session_vars['CODPAT'];
        $array_bind['NOME']= $session_vars['NOME'];
        $array_bind['COGNOME']= $session_vars['COGNOME'];
        $array_bind['NASCITA_DT']= $session_vars['NASCITA_DT'];
		$array_bind['PT']= $session_vars['PT'];

        $sql_query="
        select codpat, nome, cognome,codfisc, NASCITA_DT, gender
        from {$service}_REGISTRAZIONE
        where codpat<> :codpat
        and (nome= :nome
        and cognome= :cognome
        and to_char(NASCITA_DT, 'DDMMYYYY')= :nascita_dt 
		and PT= :PT)
        ";
        
//      echo 'param'. print_r($array_bind,true).'<hr />'. $sql_query;die();
        $sql=new query($conn);

        $sql->exec($sql_query, $array_bind);
        if ($sql->numrows>0){
            $codpats='';
            while ($sql->get_row()){
                $codpats.="'".$sql->row['CODPAT']."',";
            }
            $codpats=rtrim($codpats, ",");
//          $sql->set_sql("alter session set NLS_DATE_FORMAT='DD/MM/YYYY'");
//          $sql->exec();

            //con questa query controllo i casi di omocodia, e se esiste un fine_trat
            $sql_query="
                    SELECT a.codpat,
                      a.center,
                      NOME,
                      COGNOME,
                      CODFISC,
                      to_char(NASCITA_DT,'DD/MM/YYYY') NASCITA_DT,
                      D_GENDER,
                      to_char(c.insertdt,'DD/MM/YYYY') AS INSERTDT,
					  D_PT
                    FROM {$service}_REGISTRAZIONE a,
                      {$service}_COORDINATE c
                    
                    WHERE c.esam  =0
                    AND c.visitnum=0
                    AND c.codpat  =a.codpat
                    
                    AND a.codpat IN ($codpats)
        ";
//          echo 'param'. print_r($array_bind,true).'<hr />'. $sql_query;die();
            $sql=new query($conn);
            $sql->set_sql($sql_query);
            $sql->exec();

            $th_center="<td class='int'>Centro</td>";

            $tabella="
       <table class='bordi' width='95%' align='center'>
           <tr>
           $th_center
               <td class='int'>Patient Id</td>
               <td class='int'>Full name</td>
               <td class='int'>Social Security Number</td>
               <td class='int'>Birth Date (dd/mm/yyyy)</td>
               <td class='int'>Gender</td>
               <td class='int'>Registration date (dd/mm/yyyy)</td>
			   <td class='int'>Drug</td>
               
           </tr>
           ";
           while ($sql->get_row()){
            $td_center="<td class='sc4bis'>{$sql->row['CENTER']}</td>";
           
            $tabella.="
                       <tr>
                            $td_center
                           <td class='sc4bis' style=\"font-weight:bold;\">{$sql->row['CODPAT']}</td>
                           <td class='sc4bis'>{$sql->row['NOME']} - {$sql->row['COGNOME']}</td>
                           <td class='sc4bis'>{$sql->row['CODFISC']}</td>
                           <td class='sc4bis'>{$sql->row['NASCITA_DT']}</td>
                           <td class='sc4bis'>{$sql->row['D_GENDER']}</td>
                           <td class='sc4bis'>{$sql->row['INSERTDT']}</td>
                           <td class='sc4bis'>{$sql->row['D_PT']}</td>
                           ";
                       $tabella.="</tr>";

           }
           $tabella.="</table><br><br>";
           $body.="<p align=\"center\"><br>
               <font color=\"#FF0000\"><b>Attention!</b></font><br>
               <b>The system found other patients with same first name, last name, date of birth and drug.</b>
           </p>
           
           ";
           $body.=$tabella;
           //$body.="<br/><p align='center'><a href='#' onclick='history.back();'>&lt;&lt; Go Back</a></p>";
             $body.="<p align=\"center\">
                           <b>If it is an coincidence of names click the following button:</b>
                       </p>";
             $body.="<form method='post' action='index.php' align=center>";

//           print_r($in);die();
             foreach ($_POST as $key => $val){
            
                //notare che uso value="" <- virgolette, altrimenti nel campo hidden viene troncato il valore!
                if ($key!='CODPAT') $body.="<input type='hidden' name='$key' value=\"{$in[$key]}\">";
             }
			 $body.="<input type='hidden' name='CODPAT' value=\"next\">";
             $body.="<p align=\"center\">
                       <input type='hidden' name='OMO_CHECK_OK' value='1'>
					   <button class=\"btn btn-info\" onclick=\"submit();\" type=\"button\">
						<i class=\"fa fa-lock bigger-110\"></i>
						Register the new patient
						</button></p>";
            $body.="</form>";
        
           $body.="<p align=\"center\">
               <b><br><br>
               If the patient has been already registered you can use one of the following links:<br><br>
               <a href='#' onclick='history.back();'> Torna alla scheda di registrazione</a>                 <br><br><br> <a href=\"index.php?list=patients_list.xml\">Vai alla lista dei pazienti registrati</a></b>
           </p>";
          
           global $filetxt;
		   global $study_;
		   do_render($study_,$body);
        }
    }
}


function do_render($study_, $body=null){

global $conn;
global $filetxt;

if ($body!=null) $study_->body=$body;
	
$onload=$study_->onload;
$script=$study_->script;
$body="".$body;
$user_name="<p class='profile-block' align=right>
	<b>Profile:</b> {$user->profilo}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b>{$user->nome_azienda}&nbsp;User: </b>{$user->nome_cognome}&nbsp;&nbsp;&nbsp;&nbsp;<br>
	<b><a href='/change_password'>Change password</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
    <b><a href='/ShibLogOut'>Logout</a>&nbsp;&nbsp;&nbsp;&nbsp;<br>
	</p>
	
	";

$filetxt=preg_replace("/<!--script-->/", $script, $filetxt);
$filetxt=str_replace("<!--breadcrumb-->", $study_->breadcrumb, $filetxt);

$filetxt=str_replace("<!--navbar-->", $study_->configurer->navbar, $filetxt);
/*
if ($study_->configurer->sidebar->__toString()==""){
	$customStyle.=".main-content-no-sidebar{margin-left:0px;}\n";
	$customStyle.=".breadcrumb-no-sidebar{left:0px !important;}\n";
}
*/
$filetxt=str_replace("<!--title-->", $study_->title, $filetxt);
$pageTitleHtml="";
if ($study_->page_title!="") $pageTitleHtml="<div class=\"page-header\"><h1>".$study_->page_title."</h1></div>";
$filetxt=str_replace("<!--page_title-->", $pageTitleHtml, $filetxt);

$inbox = new inbox($conn);
$filetxt=str_replace("<!--inbox-->", $inbox->get_navbar(), $filetxt);
$filetxt=str_replace("<!--inbox_bottone-->", $inbox->get_navbarbtn(), $filetxt);

$searchBox=' <div class="nav-search" id="nav-search">
                            <span class="input-icon">
                                <input type="text" placeholder="'.mlOut("System.Search","Search").' ..." class="nav-search-input" id="nav-search-input" autocomplete="off" />
                                <i class="fa fa-search nav-search-icon"></i>
                                <i id=\'search-icon\' class=""></i> 
                                </span>
                        </div>';
if (!$study_->configurer->hasFastSearch) $addSerachBox=" style='display:none'";
	
	$searchBox=' <div class="nav-search" id="nav-search"'.$addSerachBox.'>
                            <span class="input-icon">
                                <input type="text" placeholder="'.mlOut("System.Search","Search").' ..." class="nav-search-input" id="nav-search-input" autocomplete="off" />
                                <i class="fa fa-search nav-search-icon"></i>
                                <i id=\'search-icon\' class=""></i>
                                </span>
                        </div>';

$filetxt=str_replace("<!--searchBox-->", $searchBox, $filetxt);

$filetxt=str_replace("<!--customStyle-->", $customStyle, $filetxt);
$filetxt=str_replace("<!--sidebar-->", $study_->configurer->sidebar, $filetxt);
$filetxt=preg_replace("/<!--lang-->/", $study_->xmr->config_service['lang'], $filetxt);
$filetxt=preg_replace("/<!--utente-->/", $user_name, $filetxt);
$onload.=";\nif (document.forms[0]) document.forms[0].action='';";
$filetxt=preg_replace("/\/\/<!--onload-->/", $onload, $filetxt);
$filetxt=preg_replace("/<!--user_name-->/", $nome_user, $filetxt);
$filetxt=preg_replace("/<!--page_content-->/", $body, $filetxt);
$filetxt=preg_replace("/<!--legend_lower-->/", $legend_lower->html_legend_lower, $filetxt);
$filetxt=preg_replace("/<!--legend_upper-->/", $legend_upper->html_legend_upper, $filetxt);
$filetxt=str_replace("<br>", "<br/>", $filetxt);

die($filetxt);

}


function richiesta_farmaco($xml_form){
	
    if($xml_form->session_vars['INVIOCO']==1 && $xml_form->session_vars['USER_TIP']=='DE' && $_POST['ajax_call']!="yes"){
        $str="select NPROG_SEQ.nextval NPROG from dual";
        $query=new query($xml_form->conn);
        $query->get_row($str);
        $xml_form->session_vars['NPROG_RIC']=$query->row['NPROG'];
    }
    return $xml_form;
}

class audit_trail extends audit_trail_core_prototype{}

class xml_form extends xml_form_prototype{}

class xml_vlist extends xml_vlist_prototype{}

class xml_page extends xml_page_prototype{}

class xml_list extends xml_list_prototype{
    function list_html_($session_vars=null) {
        # echo "<hr>list_html<hr>";
        global $remote_userid;
        global $in;
        global $conn;
        global $xml_dir;
        if(strtoupper($in['oper'])!='AND' && strtoupper($in['oper'])!='OR'){
            $in['oper']='';
        }
        //global $config_service;
        //if($session_vars)$in=$session_vars;
        if($in['PAGE']>0)$this->page=$in['PAGE'];
        if ($this->config_service ['PK_SERVICE'] == '')
        $pk_service = "CODPAT";
        else
        $pk_service = $this->config_service ['PK_SERVICE'];

        $html = "<table border=\"0\" id=\"table1\" width=\"95%\" align=center><tr>";
        $sql = new query ( $conn );
        $sql->set_sql ( "ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY'" );
        $sql->ins_upd ();//non richiede binding
        for($i = 0; $i < count ( $this->cols ); $i ++) {
            if ($this->cols [$i] ['GROUP_BY'] != '') {
                if (! isset ( $group_by ))
                $group_by = $this->cols [$i] ['VAR'];
                else
                $group_by .= "," . $this->cols [$i] ['VAR'];
            }
            if ($this->cols [$i] ['ORDER_BY'] != '') {
                if($this->cols [$i] ['ORDER_BY']=='asc' || $this->cols [$i] ['ORDER_BY']=='desc')$ord_t = $this->cols [$i] ['ORDER_BY'];
                else $ord_t='';
                if (! isset ( $order_by ))
                $order_by = $this->cols [$i] ['NOME'] ." ".$ord_t;
                else
                $order_by .= "," . $this->cols [$i] ['NOME'];
            }
            if ($in ['ORD'] != '') {
            $checkOrdPassed=false;
                foreach ($this->cols as $idx=>$ordValFor){
                    if ($ordValFor['ORD_ARROW']==yes) {
                        if ($in['ORD']==$ordValFor['NOME']) $checkOrdPassed=true;
                    }else {
                        if ($in['ORD']==$ordValFor['ORD_ARROW']) $checkOrdPassed=true;
                    }
                }
                if (strtoupper($in['ORD_TYPE'])!='ASC' && strtoupper($in['ORD_TYPE'])!='DESC') $checkOrdPassed=false;
                if ($checkOrdPassed) {
                    $order_by = "{$in['ORD']} {$in['ORD_TYPE']}";
                }
            }
            if ($this->cols [$i] ['WHERE'] != '') {
                if (! isset ( $where ))
                $where = $this->cols [$i] ['WHERE'];
                else
                $where .= " and " . $this->cols [$i] ['WHERE'];
            }
            if ($this->cols [$i] ['PT_FILTER'] != '') {
                if (isset ( $where ))
                $where .= " and " ;
                $where .= "{$this->cols [$i] ['VAR']} in (select pt_code from {$this->config_service['service']}_{$this->config_service['PT_MEDICO_TABLE']} where medico='[remote_userid]')";
               
            }
            if ($this->cols [$i] ['VAR'] != '') {
                if (! isset ( $fields ))
                $fields = $this->cols [$i] ['VAR'] . " as " . $this->cols [$i] ['NOME'];
                else
                $fields .= "," . $this->cols [$i] ['VAR'] . " as " . $this->cols [$i] ['NOME'];
            }
            if ($this->cols [$i] ['TIPO'] == 'studio_simple_text'){
                if($fields!='')$fields.=", ";
                $this->cols [$i] ['TABLE_REF'] = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $this->cols [$i] ['TABLE_REF'] );
                $fields.="(select count(*) as conto from {$this->cols [$i]['STUDIO']}_coordinate where $pk_service={$this->cols [$i]['TABLE_REF']}.$pk_service) as {$this->cols [$i]['STUDIO']}";
            }
            if ($this->cols [$i] ['TIPO'] == 'all_substudies'){
                //              if($fields!='')$fields.=", ";
                //              $this->cols [$i] ['TABLE_REF'] = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $this->cols [$i] ['TABLE_REF'] );
                //              $fields.="(select count(*) as conto from {$this->cols [$i]['STUDIO']}_coordinate where $pk_service={$this->cols [$i]['TABLE_REF']}.$pk_service) as {$this->cols [$i]['STUDIO']}";
                //              $xmr = new xmrwf ( "study.xml", $conn );
                //              print_r($xmr);
            }

            if ($this->cols [$i] ['TIPO'] == 'visite_gruppo') {
                $visit = new xml_esams_list ( $xml_dir . '/visite_exams.xml' );
                foreach ( $visit->group as $key => $val ) {
                    $in_sql = '';
                    foreach ( $val ['VISIT'] as $vis => $visval ) {
                        if ($in_sql != '')
                        $in_sql .= ",";
                        $in_sql .= "'$vis'";
                    }
                    if($this->cols[$i]['REF_TABLE']!='')$ref_table=$this->cols[$i]['REF_TABLE'];
                    else $ref_table=$GLOBALS['patients_table'];
                    if (! isset ( $fields ))
                    $fields = "
                        (
                            select
                                max(nvl(inizio,nvl2(abilitato,0,null)))||' - '||max(nvl(fine,nvl2(abilitato,0,null)))||' - '||min(visitclose)||' - '||max(abilitato)
                            from " . $GLOBALS ['service'] . "_COORDINATE
                            where " . $GLOBALS ['service'] . "_COORDINATE.visitnum in ($in_sql)
                            and " . $ref_table . ".{$pk_service}=" . $GLOBALS ['service'] . "_COORDINATE.{$pk_service}) as v" . $key;
                    else
                    $fields .= ",
                        (
                            select
                                max(nvl(inizio,nvl2(abilitato,0,null)))||' - '||max(nvl(fine,nvl2(abilitato,0,null)))||' - '||min(visitclose)||' - '||max(abilitato)
                            from " . $GLOBALS ['service'] . "_COORDINATE
                            where " . $GLOBALS ['service'] . "_COORDINATE.visitnum in ($in_sql)
                            and " . $ref_table . ".{$pk_service}=" . $GLOBALS ['service'] . "_COORDINATE.{$pk_service}) as v" . $key;
                }
            }
            $this->cols [$i] ['TABLE'] = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $this->cols [$i] ['TABLE'] );
            if (! preg_match ( "/" . $this->cols [$i] ['TABLE'] . "/i", $tables )) {
                if ($tables != '')
                $tables .= ",";
                $tables .= $this->cols [$i] ['TABLE'];
            }
            $function_to_call = "col_th_" . $this->cols [$i] ['TIPO'];
            if (method_exists ( $this, $function_to_call ))
            $html .= $this->{$function_to_call} ( $i );
            $nome = $this->cols [$i] ['NOME'];
            if (var_glob ( $nome,$session_vars ) != '' && var_glob ( $nome,$session_vars ) != 'next') {
                if ($where != '')
                $where .= " and ";
                $where .=  $this->cols [$i] ['VAR'] . "=:session_" . $this->cols [$i] ['NOME'] . " ";
                $binded_vars["session_".$this->cols [$i] ['NOME']]=var_glob ( $nome, $session_vars );
            }
        }

        $html .= "</tr>";
        $query = "select $fields from $tables";
//      echo "<!-- ".$query."<hr> -->";
//      echo "<hr />". print_r($in,true) ."<hr /> ";
        foreach ( $in as $key => $val ) {
            $val=trim($val," ");
            if (preg_match ( "/^SW_/", $key )) {
                //Start with
                $skey = preg_replace ( "/^SW_/", "", $key );
                if ($where != '')
                $where .= " and ";
                $where .= "lower($skey) like lower(:sw_{$skey}||'%')";
                $binded_vars["sw_".$skey]=$val;
            }
            if (preg_match ( "/^S_/", $key )) {
                $key = preg_replace ( "/^S_/", "", $key );
                if (preg_match ( "/^FROM_DT_/", $key )) {
                    $key = preg_replace ( "/^FROM_DT_/", "", $key );
                    $trovato = false;

                    for($i = 0; $i < count ( $this->cols ); $i ++) {
                        if ($this->cols [$i] ['NOME'] == $key)
                        $trovato = true;
                    }
                    if ($trovato) {
                        $val_to = $in ['S_TO_DT_' . $key];
                        
                        if ($val != '' and $val_to != '') {
                            $val = preg_replace ( "/\//", "", $val );
                            $val_to = preg_replace ( "/\//", "", $val_to );
                            if ($where != '')
                            $where .= " and ";
                            $where .= "$key between to_date(:search_from_{$key}, 'DDMMYYYY') and to_date(:search_to_{$key}, 'DDMMYYYY')+1";
                            $binded_vars['search_from_'.$key]=$val;
                            $binded_vars['search_to_'.$key]=$val_to;
                    }
                    }
                } else {

                    $trovato = false;
                    
                    for($i = 0; $i < count ( $this->cols ); $i ++) {
                        if ($this->cols [$i] ['NOME'] == $key)
                        $trovato = true;

                    }
                    if ($trovato && $val != '') {
                        $val = preg_replace ( "/à/", "a'", $val );
                        $val = preg_replace ( "/è/", "e'", $val );
                        $val = preg_replace ( "/ì/", "i'", $val );
                        $val = preg_replace ( "/ù/", "u'", $val );
                        $val = preg_replace ( "/ò/", "o'", $val );
                        $val = preg_replace ( "/\\'/", "''", $val );
                        if ($where != '' && $in ['oper'] == '')
                        $where .= " and ";
                        if ($where != '' && $in ['oper'] != '')
                        $where .= " {$in['oper']} ";
                        if ($val == 'null')
                        $where .= " $key is null";
                        else
                        $where .= "lower($key) like lower('%'||:search_{$key}||'%')";
                        $binded_vars["search_".$key]=$val;
                    }
                }
            }
            if (preg_match ( "/^IN_S_/", $key )) {
                $key = preg_replace ( "/^IN_S_/", "", $key );
                if ($where != '' && $in ['oper'] == '')
                $where .= " and ";
                $split='';
                /*
                 * Prima di splittare sulla virgola controlliamo che il parametro passato non sia del tipo
                 * 
                 */
                if (preg_match("!'!", $val)){ 
                    $val=preg_replace("!'(.*?)'!e",  "str_replace(',','###virgola###','\\1')", $val);
                }
                $split=explode(",", $val);
                $ins='';
                foreach ($split as $h=>$w){
                    $w=preg_replace("!^'!", "",$w);
                    $w=preg_replace("!'$!", "",$w);
                    $w=str_replace("###virgola###", ",", $w);
                    $binded_vars['in_s_'.$key.'_'.$h]=$w;
                    if ($ins!='') $ins.=",";
                    $ins.=':in_s_'.$key.'_'.$h;
                }
                $where .= "$key in ($ins)";
            }
            if (preg_match ( "/^IN_S2_/", $key )) {
                $key = preg_replace ( "/^IN_S2_/", "", $key );
                unset($curr_index);
                for($i = 0; $i < count ( $this->cols ); $i ++) {
                        if ($this->cols [$i] ['NOME'] == $key){
                            $curr_index = $i;
                            break;
                        }
                }
                if(isset($curr_index)){
                    if ($where != '' && $in ['oper'] == '')
                    $where .= " and ";
                    $split='';
                if (preg_match("!'!", $val)){
                    $val=preg_replace("!'(.*?)'!e",  "str_replace(',','###virgola###','\\1')", $val);
                }
                $split=explode(",", $val);
                $ins='';
                foreach ($split as $h=>$w){
                    $w=preg_replace("!^'!", "",$w);
                    $w=preg_replace("!'$!", "",$w);
                    $w=str_replace("###virgola###", ",", $w);
                    $binded_vars['in_s2_'.$key.'_'.$h]=$w;
                    if ($ins!='') $ins.=",";
                    $ins.=':in_s2_'.$key.'_'.$h;
                }
                    $where .= "{$this->cols [$i] ['VAR']} in ($ins)";
                }
            }
        }
        
        $replaceRet=query::varGlobReplace($where);
        $where=$replaceRet['sql'];
        foreach ($replaceRet['binded'] as $key=>$val){
            $binded_vars[$key]=$val;
        }
        if ($where != '')
        $query .= " where $where";
        if ($group_by != '')
        $query .= " group by $group_by";
        if ($order_by != '')
        $query .= " order by $order_by";
        $query = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $query );
        /**DEBUG OLD WAY**/

        if ($this->page!=''){
            $sql_count="select count(*) as conto from ($query)";
            $sql = new query ( $conn );
            $sql->get_row($sql_count, $binded_vars);
            $conto=$sql->row['CONTO']-0;
            $npages=ceil($conto/$this->rpp);
            $first=(($this->page-1)*$this->rpp)+1;
            if ($conto > $this->rpp) $last=$this->page*$this->rpp;
            if ($conto <= $this->rpp) $last=$conto;
            $pages=21;
            $first_page_bar=$this->page-(($pages-1)/2);
            if ($first_page_bar<=0) $first_page_bar=1;
            $last_page_bar=$first_page_bar+($pages-1);
            if ($last_page_bar>$npages){
                $last_page_bar=$npages;
                $first_page_bar=$last_page_bar-($pages-1);
                if ($first_page_bar<=0) $first_page_bar=1;
            }
            $url_base="index.php?";
            $prev_page=$this->page-1;
            $next_page=$this->page+1;
            foreach ($_GET as $key => $val){
                if ($key!='PAGE') $url_base.=urlencode($key)."=".urlencode($val)."&";
            }
            foreach ($_POST as $key => $val){
                if ($key!='PAGE' && $key!='form' && $key!='ESAM') $url_base.=urlencode($key)."=".urlencode($val)."&";
            }

            if ($this->page!=1){
                $navigation_bar.="<a href=\"{$url_base}PAGE=1\">|&lt;</a>&nbsp;<a href=\"{$url_base}PAGE=$prev_page\">&lt;</a>";
            }
            if ($first_page_bar!=1){
                $navigation_bar.="...";
            }
            for ($i=$first_page_bar;$i<=$last_page_bar;$i++){
                if ($i==$this->page) $navigation_bar.=" <b>$i</b>";
                else $navigation_bar.=" <a href=\"{$url_base}PAGE=$i\">$i</a>";
            }

            if ($last_page_bar!=$npages){
                $navigation_bar.="...";
            }
            if ($this->page!=$npages){
                $navigation_bar.=" <a href=\"{$url_base}PAGE=$next_page\">&gt;</a>&nbsp;<a href=\"{$url_base}PAGE=$npages\">&gt;|</a>";
            }
            
            /* Se siamo nell'ultima pagina il "to"($last) corrisponde al numero di risultati */
            if($_GET['PAGE'] == $last_page_bar){
                $last=$conto;
            }else{
                $last=$this->page*$this->rpp;
            }
            
            if($this->config_service ['lang'] == "en"){
                $specchietto_riassuntivo="
                Total Number of Records: <b>$conto</b><br>
                Records displayed on this page from <b>$first</b> to <b>$last</b><br>
                Go to page (1-$npages): <input type='text' id='to_page' value=\"{$_GET['PAGE']}\"><input type='button' value='Go' onclick=\"
                    page=document.getElementById('to_page').value-0;
                    if (page>$npages || page<=0) {
                        alert('Warning! Please, select page in the range 1-$npages!');
                        return false;
                    }
                    window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
                \">
                ";
            }else{
                $_GET['PAGE']=htmlentities($_GET['PAGE']);
                $specchietto_riassuntivo="
                Numero totale records: <b>$conto</b><br>
                Record mostrati in questa pagina dal <b>$first</b> al <b>$last</b><br>
                Salta a pagina (1-$npages): <input type='text' id='to_page' value=\"{$_GET['PAGE']}\"><input type='button' value='Vai' onclick=\"
                    page=document.getElementById('to_page').value-0;
                    if (page>$npages || page<=0) {
                        alert('Attenzione! Selezionare una pagina nel range 1-$npages!');
                        return false;
                    }
                    window.location.href='{$url_base}&PAGE='+document.getElementById('to_page').value;
                \">
                ";  
            }
            
            $query="select * from (select t.*, rownum as n_r from ($query) t) where n_r between $first and $last";
            $html="$specchietto_riassuntivo<p align=center>$navigation_bar</p>$html";
        }
        
        $this->sql = new query ( $conn );
        $this->sql->exec ($query, $binded_vars); //binded
        if ($this->count_items) {
            $this->n_item_returned = $this->sql->numrows;
            $html = "<p align=center style='font-size:14px'>$this->presenti_string <b>{$this->n_item_returned}</b> {$this->items_name}</p>" . $html;
        }

        $tot = 0;
        while ( $this->sql->get_row () ) {
            if ($this->list ['TOTALE'] != '')
            $tot += $this->sql->row [strtoupper ( $this->list ['TOTALE'] )];
            $this->empty = false;
            $html .= "\n<tr>";
            for($i = 0; $i < count ( $this->cols ); $i ++) {
                $txt = "";
                $function_to_call = "col_td_" . $this->cols [$i] ['TIPO'];
                if (method_exists ( $this, $function_to_call ))
                $txt .= "\n" . $this->{$function_to_call} ( $i );
                if ($this->cols [$i] ['SCRIPT'] != '') {
                    $link = $this->col_script ( $i );
                    $txt = $link . $txt . "</a>";
                }
                if ($txt != '')
                $html .= "<td class=\"sc4bis\" {$this->cols [$i] ['ALIGN']}>$txt</td>";
            }
            $html .= "</tr>";
        }
        if (isset ( $in ['CODPAT'] )) {
            $param = "CODPAT=" . $in ['CODPAT'];
            $txt;
        }
        $param .= "&amp;CENTER=" . $in ['CENTER'];
        if ($in ['v_list'] == '') {
            //if ($in['list']=="patients_group_list.xml") $html.="<p align=right><a href=\"index.php?list=patients_list.xml&amp;$param\">Lista Pazienti</a></p>";
            //else  $html.="<p align=right><a href=\"index.php?list=patients_group_list.xml&amp;$param\">Lista Pazienti</a></p>";
        }
        if ($this->list ['TOTALE'] != '') {
            $colsp = count ( $this->cols ) - 3;
            if($this->config_service ['lang'] != "en"){
                $html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Totale</b></td>";
            }else{
                $html .= "<tr><td class=\"sc4bis\" colspan=$colsp><b>Total</b></td>";
            }

            $html .= "<td class=\"sc4bis\"><b>$tot</b></td>
                 <td class=\"sc4bis\"></td>
                 </tr>
                ";
        }
        $html .= "</table>";
//echo $html."<hr>";
//echo "<!--$query-->";
        return $html;

    }
}

class legend extends legend_prototype{}

class user extends user_prototype{}

class xml_esams_list extends xml_esams_list_prototype{
    function print_esams_($es_val, $key, $esam, $vprogr=0){
        
        if($es_val['HEADER']!="")$header="<tr><td class=\"sc4bis\"></td><td class=\"int exam_header\" style=\"text-align:left;\">{$es_val['HEADER']}</td></tr>";
        if ($vprogr!=null) $agg_param="&VISITNUM_PROGR={$vprogr}";
        else $agg_param="";
        $in=$this->session_vars;
        $conn=$this->conn;
        $xml_dir=$this->xml_dir;
        $config_service=$this->config_service;
        global $service;
        
        $nome_form=$es_val['TESTO'];
        //ESAMI NON PROGRESSIVO
        if ((!isset($es_val['PROGR']) || $es_val['PROGR']!='yes') && !isset($es_val['CORR'])){
            $img="to_be_comp.gif";
            $progr=1;
            if ($es_val['PROGR']!='') $progr=$es_val['PROGR'];
            if ($es_val['RES'][$progr]['INIZIO']=='0' || $es_val['RES'][$progr]['INIZIO']=='') $img="to_be_comp.gif";
            if ($es_val['RES'][$progr]['INIZIO']=='1') $img="saved.gif";
            if ($es_val['RES'][$progr]['FINE']=='1') $img="submitted.gif";
            
            if($this->config_service['mostraDataInvio']){
                $file_form=$es_val['XML'];
                $form1= new xml_form( $this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir );
                $form1->xml_form_by_file($xml_dir."/".$file_form);
                $f_table=$form1->form['TABLE'];
                $dateinv=$this->getInsData($f_table,$in[$config_service['PK_SERVICE']],$key,$vprogr,$esam, $progr );
                $agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
                                            </td>
                                            <td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
                                            </td>";
            }
            $date=$es_val['RES'][$progr]['INSERTDT'];
            if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes' && $es_val['RES'][$progr]['FINE']!='1' ){
                if($in['USER_TIP']!='DE' && $es_val['RES'][$progr]['USERID']!=$in['remote_userid']) return;
            }
            //agg da mod  di alejandra nelle lib vecchie
            if ($es_val['FOTH'] && ($es_val['RES'][$progr]['FINE']=='1' || $es_val['FOTH_ALWAYS']=='yes'))
            {
                if(isset($es_val['EOTH']) && $es_val['EOTH']!=='')$esam_oth=$es_val['EOTH'];
                else $esam_oth=$es_val['NUMBER'];
                //per ottenere un foth preciso
                if($es_val['FOTH_SAME_FORM']!=""){
                    $add_foth_where=" and visitnum_progr=:visitnum_progr and progr=:progr";
                    unset($bind_data);
                    $bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
                    $bind_data['ESAM']=$esam_oth;
                    $bind_data['VISITNUM_PROGR']=$vprogr;
                    $bind_data['PROGR']=$progr;
                }
                else {
                    $add_foth_where="";
                    unset($bind_data);
                    $bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
                    $bind_data['ESAM']=$esam_oth;
                    
                }
                $query_data="select {$es_val['FOTH']} as FOTH from {$config_service['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}=:pk_service and esam=:esam {$add_foth_where}";
//              echo "$query_data";
                $sql2=new query($conn);
                //$sql2->set_sql($query_data);
                
                $sql2->exec($query_data,$bind_data);//binded
                $sql2->get_row();
                $foth=$sql2->row['FOTH'];
                $nome_esame=$es_val['TESTO'].$foth;
//              echo $date;
            }
            else{
            $nome_esame=$es_val['TESTO'];
            }
            if($es_val['INS_DATE']=='yes'){
                $nome_esame.=$date;
            }
            //end alej mod


            if ($es_val['RES'][$progr]['FINE']=='1') $nome_esame.="</a>";
            if ($es_val['RES'][$progr]['ABILITATO']=='1' || $es_val['RES']['']['ABILITATO']=='1')
            {
                $href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=1&amp;form=".$es_val['XML']."{$agg_param}\">";
                $close_href="</a>";
                if ($es_val['INDENT']=='yes') $indent="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
                else $indent="";
                $img_tag="<img src=\"/images/$img\" border=\"0\">";
                //if ($in['USER_TIP']=='DM') $img_tag='';
                if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
                    $agg_where='';
                    if ($vprogr!=null) $agg_where="and VISITNUM_PROGR={$vprogr}";
                    $sql_query="select count(*) as c from {$service}_eqfield where
                    esam={$esam}
                    and visitnum=$key
                    and progr=$progr
                    $agg_where
                    and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
                    and eq_int={$this->integrazione->eq_int}
                    ";
                    $sql2=new query($this->conn);
                    $sql2->get_row($sql_query);
                    if ($sql2->row['C']>0){
                        $img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
                        //$nome_esame.="$href<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">$close_href";
                        $nome_esame.="</a><b>(scheda modificata in fase di integrazione)</b>";
                    }
                }
                if ($es_val['RES']['1']['EQ_ACTION']==1){
                    $img_tag="<img src=\"images/eq_img.png\" width=\"15px\" title=\"La scheda e' in fase di integrazione\">".$img_tag;
                    $nome_esame.="</a><b>(scheda aggiunta in fase di integrazione)</b>";
                }
                if ($es_val['RES']['1']['EQ_ACTION']==2){
                        $img_tag="<img src=\"images/iphone_delete_icon.png\" width=\"15px\" title=\"La scheda rimossa in fase di integrazione\">".$img_tag;
                        $nome_esame.="</a><b>(scheda rimossa in fase di integrazione)</b>";
                    }
                if ($es_val['RES'][1]['FINE']=='1' && $es_val['LINK_PDF']=='yes'){
                     
                    $image_pdf="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$progr}&amp;form=".$es_val['XML']."&pdf_esame=true\"><img src='/images/pdf.gif' width='20px' /></a>";
                }
                else{
                     
                    $image_pdf='';
                }
                $this->body.="{$header}
                                    <tr>
                                         <td class=\"sc4bis\" width=\"10%\" align=\"center\">{$indent}{$href}{$img_tag}{$close_href}
                                         </td>
                                        <td class=\"sc4bis\" align=\"left\">{$indent}$href".$nome_esame."$close_href $image_pdf<br/>
                                        </td>
{$agg_dateinv}
                                    </tr>
                                        ";
            }
        }
        //ESAMI PROGRESSIVI
        else {
//          print_r($es_val);
            //echo "<li>$key, $esam, $vprogr</li>";
            $last_progr=0;
            $form_alt='';
            //print_r($es_val);
            if (isset($es_val['RES']) && !isset($es_val['CORR'])){
                //print_r($es_val);
                if((isset($es_val['CONT_FORM']) && $es_val['CONT_FORM']=='yes') || isset($es_val['ALL_IN'])){
                    
                    $sql2=new query($conn);
                        
                    //MODIFICO VAL_AGG AFFINCHE' ESEGUA SOLO LA QUERY, SENZA ANDARE SUL PROGR
                    //modifica G.Tufano 20/02/2012
                    if ($es_val['VAL_AGG']!='') {
                        $where_agg = $es_val['WHERE_AGG'];
                        $query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$GLOBALS['service']}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and esam=:esam $where_agg";
                        
                        unset($bind_agg);
                        $bind_agg['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
                        $bind_agg['ESAM']=$esam;
//                      echo "$query_data<hr />";print_r($bind_agg);
                        
                        $sql2->exec($query_data,$bind_agg);
                        $sql2->get_row();
                        $date=$sql2->row['VAL_AGG'];
                    }

                    foreach ($es_val['RES'] as $es_progr => $progr_vals){
//                      echo "<hr>$last_progr -  $es_progr";
                        //print_r($es_val);
                        
                        if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
                        if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
                        if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";

                        $last_progr=$es_progr;
                    }
                    $n_progr=0;
                    $init=false;
                    $all_completed=true;
                    $eq_present=false;
                    $add_text='';
                    $count_added=0;
                    $count_deleted=0;
                    $all_deleted=true;
                    $all_added=true;
                    
                    $deleted=false;
                $added=false;
                $modified=false;
                
                if ($this->integrazione->eq_enabled && $this->integrazione->eq_int!=''){
                    $agg_where='';
                    if ($vprogr!=null) $agg_where="and VISITNUM_PROGR={$vprogr}";
                    $sql_query="select count(*) as c from {$service}_eqfield where
                    esam={$esam}
                    and visitnum=$key
                    $agg_where
                    and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}
                    and eq_int={$this->integrazione->eq_int}
                    and action=0
                    ";
                    $sql2=new query($this->conn);
                    $sql2->get_row($sql_query);
                    if ($sql2->row['C']>0){
                        $modified=true;
                    }
                }
                
                    $unset_viewable_on_close=false;
                    foreach ($es_val['RES'] as $keys => $val) {
                        if(isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes' && $in['USER_TIP']!='DE'){
                            if ($val['FINE']=='1' || $val['USERID']==$this->session_vars['remote_userid']) $n_progr++;
                            if( $val['USERID']==$this->session_vars['remote_userid'])$unset_viewable_on_close=true;
                        }
                        else{
                            if ($val['INIZIO']=='1') $n_progr++;
                        }
                        if ($val['INIZIO']=='' || $val['INIZIO']=='0') $img="to_be_comp.gif";
                        if ($val['INIZIO']=='1') $init=true;
                        if ($val['FINE']!='1') $all_completed=false;
                        if ($val['INV_QUERY']!='') $eq_present=true;
                        if ($val['EQ_ACTION']==2) {
                            $all_added=false;
                            $count_deleted++;
                            $deleted=true;
                        }
                        if ($val['EQ_ACTION']==1) {
                            $all_deleted=false;
                            $count_added++;
                            $added=true;
                        }
                        
                    }
                    if($unset_viewable_on_close)unset($es_val['VIEWABLE_ON_CLOSE']);
                    if ($add_text!='' && $all_added) $add_text="</a><b>(Schede aggiunte in fase di integrazione)</b>";
                    if ($add_text!='' && $all_deleted) $add_text="</a><b>(Schede rimosse in fase di integrazione)</b>";
                    if ($modified||$added||$deleted){
                        $kind="";
                        if ($deleted){
                            if ($kind!='') $kind.="/";
                            $kind.="eliminate";
                        }
                        if ($added){
                            if ($kind!='') $kind.="/";
                            $kind.="aggiunte";
                        }
                        if ($modified){
                            if ($kind!='') $kind.="/";
                            $kind.="modificate";
                        }
                        $add_text="</a><b>(Schede $kind in fase di integrazione)</b>";
                    }

            
                    if(isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes' && $in['USER_TIP']!='DE'){
                        if($n_progr==0){
                            return ;
                        }
                        else{
                            $all_completed=true;
                        }
                    }
                    if ($init) $img="saved.gif";
                    if ($all_completed)  $img="submitted.gif";
                    if ($n_progr==0) {
                        $img="to_be_comp.gif";
                        if($this->true_false['configurato'])
                        $n_progr=$this->testi['nuovo_inserimento'];
                        else
                        $n_progr="Nuovo inserimento";
                    }

                    if (isset($es_val['VIEWABLE_ON_CLOSE']) && $es_val['VIEWABLE_ON_CLOSE']=='yes'){
                        $count_fine=0;
                        foreach ($es_val['RES'] as $k_idx=>$val_idx){
                            if ($val_idx['FINE']==1 || $val_idx['USERID']==$in['remote_userid']) {

                                $count_fine++;
                            }
                        }
                        $n_progr=$count_fine;
                        if ($count_fine==0){
                            $img="to_be_comp.gif";
                        }
                    }
                    if ($es_val['RES'][$progr]['FINE']=='1' && $es_val['LINK_PDF']=='yes'){
                        $image_pdf="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$progr}&amp;form=".$es_val['XML']."&pdf_esame=true\"><img src='/images/pdf.gif' width='20px' /></a>";
                    }
                    else{
                        $image_pdf='';
                    }
                    $date=" (".$n_progr.") ".$date;
                    $nome_esame=$es_val['TESTO']." $date";
                    $nome_esame.=$add_text;
                    if ($progr!='') {
                        $sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]}
                        and visitnum=$key and esam=$esam and progr=$progr  and nvl(chiusa,0)<>1 and visitnum_progr=$vprogr";
                        
                        unset($bind_chiusa);
                        $bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
                        $bind_chiusa['VISITNUM']=$key;
                        $bind_chiusa['ESAM']=$esam;
                        $bind_chiusa['VISITNUM_PROGR']=$vprogr;
                        $bind_chiusa['PROGR']=$progr;
                    }
                    else {
                        /*$sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery
                                    where {$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and visitnum=$key and esam=$esam and nvl(chiusa,0)<>1 and visitnum_progr=$vprogr";*/
                        $sql_query="
                        select nvl(e.chiusa,0) as chiusa, min(c.fine) as fine from {$service}_equery e, {$service}_coordinate c
                        where c.{$this->PK_SERVICE}={$in[$this->PK_SERVICE]} and c.visitnum=$key and c.esam=$esam and nvl(e.chiusa,0)<>1 and c.visitnum_progr=$vprogr
                        and e.{$this->PK_SERVICE}=c.{$this->PK_SERVICE} and e.esam=c.esam and c.visitnum=e.visitnum and c.visitnum_progr=e.visitnum_progr
                        group by e.chiusa
                        ";
                        unset($bind_chiusa);
                        $bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
                        $bind_chiusa['VISITNUM']=$key;
                        $bind_chiusa['ESAM']=$esam;
                        $bind_chiusa['VISITNUM_PROGR']=$vprogr;
                        
                    }
                    
                    $sql2=new query($conn);
                    //$sql2->set_sql($sql_query);
                    $sql2->exec($sql_query,$bind_chiusa);//binded
                    if ($sql2->numrows>0){
                        $sql2->get_row();
                        if ($in['USER_TIP']=='DE' && !$archiviata  && $sql2->row['CHIUSA']=='0' && ($es_val['RES'][$es_progr]['FINE']!='1' || $sql2->row['FINE']=='0')) {
                            $nome_esame.="<font color=red>(da revisionare)</font>";
                        }
                    }
                    if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
                        $href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val['XML']."{$agg_param}\">";
                        if ($es_progr!=''){
                                }

                        $close_href="</a>";
                        $img_tag="<img src=\"/images/$img\" border=\"0\">";
                        if ($deleted||$modified||$added){
                            $img_tag="<img src=\"images/eq_img.png\" width=15px>".$img_tag;
                        }

                        $this->body.="{$header}
                                                    <tr>
                                                         <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
                                                        </td>
                                                        <td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href $image_pdf<br/>
                                                        </td>
                                                        <!--td class=\"sc4bis\" align=\"center\">
                                                        </td>
                                                        <td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
                                                        </td-->
                                                    </tr>
                                                ";
                    }
                }
                else{
                    foreach ($es_val['RES'] as $es_progr => $progr_vals){
                        if ($es_val['RES'][$es_progr]['INIZIO']=='1'){
                            $sql2=new query($conn);
                            $date="";
                            if($this->config_service['mostraDataInvio']){
                                $file_form=$es_val['XML'];
                                $form1= new xml_form( $this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir );
                                $form1->xml_form_by_file($xml_dir."/".$file_form);
                                $f_table=$form1->form['TABLE'];
                                $dateinv=$this->getInsData($f_table,$in[$config_service['PK_SERVICE']],$key,$vprogr,$esam, $es_progr );
                                $agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
                                            </td>
                                            <td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
                                            </td>";
                            }
                            if ($es_val['DATA']!='') {
                                $query_data="select to_char({$es_val['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and  progr=:progr";
                                unset($bind_data);
                                $bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
                                $bind_data['PROGR']=$es_progr;
                                //$sql2->set_sql($query_data);
                                $sql2->exec($query_data,$bind_data);//binded
                                $sql2->get_row();
                                $date=$sql2->row['DATA'];
                            }
                            if ($es_val['VAL_AGG']!='') {
                                $query_data="select {$es_val['VAL_AGG']} as VAL_AGG from {$service}_{$es_val['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and  progr=:progr and esam=:esam ";
                                unset($bind_agg);
                                $bind_agg['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
                                $bind_agg['PROGR']=$es_progr;
                                $bind_agg['ESAM']=$esam;
                                //$sql2->set_sql($query_data);
                                $sql2->exec($query_data,$bind_agg);//binded
                                $sql2->get_row();
                                $date=$sql2->row['VAL_AGG'];
                            }
                            if ($es_val['FOTH'])
                            {
                                if($es_val['WOTH']!=''){
                                    $add_foth_where="and ({$es_val['WOTH']})";
                                }
                                else{
                                    $add_foth_where="";
                                }
                                $query_data="select {$es_val['FOTH']} as FOTH from {$GLOBALS['service']}_{$es_val['TOTH']} where {$config_service['PK_SERVICE']}=:pk_service and  progr=:progr and visitnum_progr=:visitnum_progr ".$add_foth_where;
                                #echo "<hr>$query_data";
                                unset($bind_data);
                                $bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
                                $bind_data['PROGR']=$es_progr;
                                $bind_data['VISITNUM_PROGR']=$vprogr;
                                //$sql2->set_sql($query_data);
                                $sql2->exec($query_data,$bind_data);//binded
                                $sql2->get_row();
                                $date.=$sql2->row['FOTH'];
                            }
                            if ($last_progr+1!=$es_progr)
                            while ($last_progr<$es_progr-1){
                                $last_progr++;
                                $n_progr=$last_progr;
                                $img="to_be_comp.gif";
                                $form_alt=str_replace(".xml", ".xml", $es_val['XML']);
                                if (!file_exists($xml_dir."/".$form_alt)) $form_alt=$es_val['XML'];
                                $href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$form_alt."{$agg_param}\">";
                                $nome_esame=$es_val['TESTO']." n. $n_progr";
                                if ($progr!=''){
                                    $sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam and progr=:progr";
                                    $sql2=new query($conn);
                                    unset($bind_chiusa);
                                    $bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
                                    $bind_chiusa['VISITNUM']=$key;
                                    $bind_chiusa['ESAM']=$esam;
                                    $bind_chiusa['PROGR']=$progr;
                                    if ($es_val['RES'][$progr]['FINE']=='1' && $es_val['LINK_PDF']=='yes'){
                                        $image_pdf="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$progr}&amp;form=".$es_val['XML']."&pdf_esame=true\"><img src='/images/pdf.gif' width='20px' /></a>";
                                    }
                                    else{
                                        $image_pdf='';
                                    }
                                    //$sql2->set_sql($sql_query);
                                    $sql2->exec($sql_query,$bind_chiusa);//binded
                                    if ($sql2->numrows>0){
                                        $sql2->get_row();
                                        if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare)</font>";
                                        //if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare)</font>";
                                    }
                                }
                                $close_href="</a>";
                                $img_tag="<img src=\"/images/$img\" border=\"0\">";
                                $this->body.="{$header}
                                                                <tr>
                                                                     <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
                                                                    </td>
                                                                    <td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href $image_pdf<br/>
                                                                    </td>
                                                                    <!--td class=\"sc4bis\" align=\"center\">
                                                                    </td>
                                                                    <td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
                                                                    </td-->
                                                                </tr>
                                                            ";

                            }
                            if ($es_val['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
                            if ($es_val['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
                            if ($es_val['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
                            $n_progr=$es_progr;
                            if (isset($es_val['VAL_AGG'])) $nome_esame="{$es_val['TESTO']} {$date}";
                            else {
                                if ($date!='') $date=" n.{$n_progr} ($date)";
                                $nome_esame=$es_val['TESTO']." $date";
                            }
                            if ($es_val['RES'][$es_progr]['ABILITATO']=='1'){
                                $href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR=$es_progr&amp;form=".$es_val['XML']."{$agg_param}\">";
                                if ($es_progr!=''){
                                }
                                if ($es_val['RES'][$es_progr]['FINE']=='1' && $es_val['LINK_PDF']=='yes'){
                                    $image_pdf="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$es_progr}&amp;form=".$es_val['XML']."&pdf_esame=true\"><img src='/images/pdf.gif' width='20px' /></a>";
                                }
                                else{
                                    $image_pdf='';
                                }
                                $close_href="</a>";
                                $img_tag="<img src=\"/images/$img\" border=\"0\">";
                                $this->body.="{$header}
                                                                <tr>
                                                                     <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href{$img_tag}$close_href
                                                                    </td>
                                                                    <td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href $image_pdf<br/>
                                                                    </td>
                                                                    {$agg_dateinv}
                                                                    <!--td class=\"sc4bis\" align=\"center\">
                                                                    </td>
                                                                    <td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
                                                                    </td-->
                                                                </tr>
                                                            ";

                            }

                            foreach ($this->esams[$key] as $esam_corr => $es_val_corr){
                                if ($es_val_corr['CORR']!='' && $es_val_corr['CORR']==$esam && ($es_val_corr['CORR_ON_SEND']!='yes' || $es_val['RES'][$es_progr]['FINE']==1)){
                                    # echo "<hr> Esame correlato per $esam : ".$esam_corr;
                                    $img="to_be_comp.gif";
                                    #echo "<hr>$esam - ".$es_val['RES'][0]['INIZIO']." - ".$es_val['RES'][0]['FINE'];
                                    if ($es_val_corr['RES'][$es_progr]['INIZIO']=='0') $img="to_be_comp.gif";
                                    if ($es_val_corr['RES'][$es_progr]['INIZIO']=='1') $img="saved.gif";
                                    if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $img="submitted.gif";
                                    #$date=$es_val_corr['RES'][$es_progr]['INSERTDT'];
                                    $dtp='';
                                    $query_data="select to_char({$es_val_corr['DATA']}, 'DD/MM/YYYY') as data from {$service}_{$es_val_corr['TABLE']} where ".$config_service['PK_SERVICE']."=:pk_service and  progr=:progr";
                                    #echo "<hr>$query_data";
                                    unset($bind_data);
                                    $bind_data['PK_SERVICE']=$in[$config_service['PK_SERVICE']];
                                    $bind_data['PROGR']=$es_progr;
                                    //$sql2->set_sql($query_data);
                                    $sql2->exec($query_data,$bind_data);//binded
                                    $sql2->get_row();
                                    $date=$sql2->row['DATA'];
                                    //echo "<hr>$date<hr>";
                                    $n_progr=$es_progr;
                                    if ($date!='')  $dtp=" n.{$n_progr} ($date)";
                                    $nome_esame=$es_val_corr['TESTO']." $dtp";
                                    if ($progr!=''){
                                        $sql_query="select nvl(chiusa,0) as chiusa from {$service}_equery where {$this->PK_SERVICE}=:pk_service and visitnum=:visitnum and esam=:esam and progr=:progr";
                                        $sql2=new query($conn);
                                        //$sql2->set_sql($sql_query);
                                        unset($bind_chiusa);
                                        $bind_chiusa['PK_SERVICE']=$in[$this->PK_SERVICE];
                                        $bind_chiusa['VISITNUM']=$key;
                                        $bind_chiusa['ESAM']=$esam;
                                        $bind_chiusa['PROGR']=$progr;
                                        $sql2->exec($sql_query,$bind_chiusa);//binded
                                        if ($sql2->numrows>0){
                                            $sql2->get_row();
                                            if ($in['USER_TIP']=='DE'  && !$archiviata && $sql2->row['CHIUSA']=='0' && $es_val['RES'][$es_progr]['FINE']!='1') $nome_esame.="<font color=red>(da revisionare)</font>";
                                            //if ($sql2->row['CHIUSA']=='0') $nome_esame.="<font color=red>(da revisionare)</font>";
                                        }
                                    }
                                    //if ($es_val_corr['RES'][$es_progr]['FINE']=='1') $nome_esame.="</a>&nbsp;-&nbsp;<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;form=".$es_val_corr['XML']."\">";
                                    if($this->config_service['mostraDataInvio']){
                                        $file_form=$es_val_corr['XML'];
                                        $form1= new xml_form( $this->conn, $this->config_service['service'], $this->config_service, $this->session_vars, $this->uploaded_file_dir );
                                        $form1->xml_form_by_file($xml_dir."/".$file_form);
                                        $f_table=$form1->form['TABLE'];
                                        $dateinv=$this->getInsData($f_table,$in[$config_service['PK_SERVICE']],$key,$vprogr,$es_val_corr['NUMBER'], $es_progr );
                                        $agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;$dateinv[0]</b>
                                            </td>
                                            <td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;$dateinv[1]</b><br/>
                                            </td>";
                                    }
                                     if ($es_val['RES'][$progr]['FINE']=='1' && $es_val['LINK_PDF']=='yes'){
                                        $image_pdf="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$progr}&amp;form=".$es_val['XML']."&pdf_esame=true\"><img src='/images/pdf.gif' width='20px' /></a>";
                                    }
                                    else{
                                        $image_pdf='';
                                    }
                                    $href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=".$es_val_corr['NUMBER']."&amp;PROGR=$es_progr&amp;form=".$es_val_corr['XML']."\">";
                                    $close_href="</a>";
                                    $this->body.="{$header}
                                        <tr>
                                             <td class=\"sc4bis\" width=\"10%\" align=\"center\">$href<img src=\"/images/$img\" border=\"0\">$close_href
                                            </td>
                                            <td class=\"sc4bis\" align=\"left\">$href".$nome_esame." $close_href $image_pdf<br/>
                                            </td>
                                            {$agg_dateinv}
                                            <!--td class=\"sc4bis\" align=\"center\">
                                            </td>
                                            <td class=\"sc4bis\" align=\"center\"><b>&nbsp;$date</b><br/>
                                            </td-->
                                            </tr>
                                            ";
                                }
                            }
                            #echo "<hr>ultimo progr $es_progr";
                            $last_progr=$es_progr;
                        }

                    }
                }
                //echo "<li>$key - $esam - ";
                //print_r($es_val);
                //echo "</li>";
                //print_r($this->esams[$key][$esam]['NEXT_ENABLED']);
                if (($es_val['RES'][$es_progr]['FINE']==1 || $es_val['RES'][$es_progr]['INIZIO']=='' || $es_val['NEXT_ENABLED']!='') && !isset($es_val['ALL_IN']) && !$es_val['RES'][$es_progr]['VISITCLOSE']){
                    //print_r($es_val);
                    if(!$this->true_false['configurato'])$this->testi['nuovo_inserimento']='Nuovo inserimento';
                    if ($es_val['RES'][$es_progr]['INIZIO']!='') $next_progr=$es_progr+1;
                    else $next_progr=$es_progr;
                    $href="<a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."{$agg_param}\">";
                    $close_href="</a>";
                    if (!isset($form_alt) || $form_alt=='') $form_alt=$es_val['XML'];
                    if($this->config_service['mostraDataInvio']){
                        
                        $agg_dateinv="<td class=\"sc4bis\" align=\"left\" width=\"30%\"><b>&nbsp;</b>
                                            </td>
                                            <td class=\"sc4bis\" align=\"left\" width=\"10%\"><b>&nbsp;</b><br/>
                                            </td>";
                    }
                    
                    if ($es_val['CONT_FORM']!='yes' && $es_val['DISABLE_NEW']=='' && $in['USER_TIP']!='RO')$this->body.="
                                                    <tr>
                                                        <td class=\"sc4bis\" width=\"10%\" align=\"center\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$es_val['XML']."{$agg_param}\"><img src=\"/images/to_be_comp.gif\" border=\"0\"></a>
                                                        </td>
                                                        <td class=\"sc4bis\" align=\"left\"><a href=\"index.php?CENTER=".$in['CENTER']."&amp;".$config_service['PK_SERVICE']."=".$in[$config_service['PK_SERVICE']]."&amp;VISITNUM=$key&amp;ESAM=$esam&amp;PROGR={$next_progr}&amp;form=".$form_alt."{$agg_param}\">{$this->testi['nuovo_inserimento']}: ".$es_val['TESTO']."</a> <br/>
                                                        </td>
                                                        {$agg_dateinv}
                                                        <!--td class=\"sc4bis\" align=\"center\">
                                                        </td>
                                                        <td class=\"sc4bis\" align=\"center\">&nbsp;<br/>
                                                        </td-->
                                                    </tr>
                                            ";
                }
            }
        }
    }    
}

function var_glob($value){
	global $in;
	global $inputval;
	if (isset($inputval[$value]) && $inputval[$value]!='') return $inputval[$value];
	if (isset($in[$value]) && $in[$value]!='') return $in[$value];
	if (isset($GLOBALS[$value]) && $GLOBALS[$value]!='') return $GLOBALS[$value];
}

function error_page($user, $error, $error_spec){
    global $filetxt;
    global $in;
    global $SRV;
    global $log_conn;
    global $service;
    global $remote_userid;
    global $session_number;
    #echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
    $today = date("j/m/Y, H:m:s");
    Logger::trace('error');
    if (is_array($error_spec)) foreach ($error_spec as $key => $val) $spec.="\n $key : $val";
    mail("c.contino@cineca.it, l.verri@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n");
    $body="<p align=center><font size=4><b>An error occurred</b></p><br><br>";
    $filetxt=preg_replace("/<!--body-->/", $body, $filetxt);
    var_dump($error);
    global $study_;
    do_render($study_, "<div class=\"alert alert-danger\"><i class=\"icon-remove\"></i><strong>Error: </strong>".$error."</div>");
    //die(print_r(array("d.saraceno@cineca.it", "Errore[".$in['remote_userid']."]","$today\n $error \n Specifiche errore: \n".$spec, "From: ERROR_".$service."@{$_SERVER['SERVER_NAME']}\r\n"),1)); 
}

function error_pageNO($user, $error, $error_spec) {    
    die($user . '-' . $error . '-' . print_r($error_spec));
}


function eleg_ivabradina($xml_form){
    if($xml_form->session_vars['FREQ_BASALE']>60){
        $xml_form->session_vars['ELEG']=1;
    }
    return $xml_form;
}


function drawPieChart($title, $iconClass, $data, $bottomBoxes){
	foreach ($data as $key=>$val){
		$data[$key]['color']=randomColor();
	}
	$jData=json_encode($data);
	$pieChart="
	<div class=\"widget-box col-sm-5\">
		<div class=\"widget-header widget-header-flat widget-header-small\">
			<h5><i class=\"$iconClass\"></i> $title</h5>
		</div>
		<div class=\"widget-body\">
			<div class=\"widget-main\">
				<div id=\"piechart-placeholder\"></div>
			</div>";
	if (count($bottomBoxes)>0)
		$pieChart.="
			<div class=\"hr hr8 hr-double\"></div>
				<div class=\"clearfix\">
				";
	foreach ($bottomBoxes as $key=>$val){
		$c=count($bottomBoxes);
		$pieChart.="
					<div class=\"grid{$c}\">
						<span class=\"grey\"><i class=\"{$val['icon']} blue\"></i>&nbsp; {$val['text']}</span>
					</div>
		
				";	
	}
	if (count($bottomBoxes)>0)
		$pieChart.="
	
					
				</div>
				";
	$pieChart.="
			</div>
		
	</div>




<script>
jQuery(function($) {
var placeholder = $('#piechart-placeholder').css({'width':'90%' , 'min-height':'150px'});
var data=$jData;

drawBarChart(placeholder, data);

placeholder.data('chart', data);
placeholder.data('draw', drawPieChart);
});

</script>		
";
	return $pieChart;
}

function randomColor(){
	return sprintf("#%06s", strtoupper(dechex(rand(0,10000000))));
}


function dispensazione($xml){
		
}


function check_f_tratt($xml){
	
}

function sae($xml){
	if ($_POST["ajax_call"]!="") return;
	if ($_POST['INVIOCO']==0) return;
	$sql_query="
		select email from ana_utenti where userid in (
		select p.userid from PT_USER_PROFILES p, PT_UTENTI_CENTRI c 
		where p.userid=c.userid 
		and p.profile_id=9
		and c.center=:CENTER
		)
		 ";
	$sql=new query($xml->conn);
	$bind['CENTER']=$_POST['CENTER'];
	Logger::send($bind);
	$sql->exec($sql_query,$bind);
	$to="";
		while($sql->get_row()){
			if ($sql->row ['EMAIL']!=''){
					$to.= $sql->row ['EMAIL'];
					$to.=",";
			}
		}
	$email_from="roche@drug_registry.it";
	$testo_mail="<b>Adverse event notification</b>
			<br><br>
			Center: {$_POST['CENTER']}<br>
			Patient code: {$_POST['CODPAT']}
			<br><br>
			<a href=\"http://{$_SERVER['HTTP_HOST']}/prm-phase2/index.php?CENTER={$_POST['CENTER']}&CODPAT={$_POST['CODPAT']}&VISITNUM={$_POST['VISITNUM']}&ESAM=99&PROGR={$_POST['PROGR']}&form=sae.xml\">Go to adverse event data</a>
			";
	$oggetto="Adverse event notification";
	$bcc="l.verri@cineca.it,c.contino@cineca.it";
	send_email($to, $email_from, $email_from, $oggetto, $testo_mail, null, false, null, $bcc);
}

function fine_trattamento($xml){
	if ($_POST["ajax_call"]!="") return;
	$sql_query="
		select REAZIONI_AVVERSE
		  from PT_FINE_TRATT
		where
		  codpat=:CODPAT
		 ";
	$sql=new query($xml->conn);
	$bind['CODPAT']=$_POST['CODPAT'];
	Logger::send($bind);
	$sql->exec($sql_query,$bind);
	$sql->get_row();
	if ($sql->row['REAZIONI_AVVERSE']==1){
		$sql_update = "update PT_COORDINATE set visitclose=1 where visitnum in (0,1,2,4) and CODPAT=:CODPAT";
		$sql1 = new query ( $xml->conn );
		$sql1->ins_upd ($sql_update, $bind);
	}else{
		$sql_update = "update PT_COORDINATE set visitclose=1 where visitnum in (0,1,2,4,99) and CODPAT=:CODPAT";
		$sql1 = new query ( $xml->conn );
		$sql1->ins_upd ($sql_update, $bind);
	}
}

function generateRandomString($length = 8) {
	$characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
	$randomString = '';
	for ($i = 0; $i < $length; $i++) {
		$randomString .= $characters[rand(0, strlen($characters) - 1)];
	}
	return $randomString;
}

function richiestaFarmaco($xml){
	if ($_POST["ajax_call"]!="") return;
	if ($_POST['INVIOCO']==0) return;
	$cu=generateRandomString();
	$sql_check="select count(*) as C from PT_RICH_FARMACO where CU=:cu";
	$bind['CU']=$cu;
	$sql=new query($xml->conn);
	while ($sql->get_row($sql_check, $bind)){
		if ($sql->row['C']==0) break;
		$cu=generateRandomString();
		$bind['CU']=$cu;
	}
	$sql_upd="update PT_RICH_FARMACO set CU=:cu where PROGR=:PROGR and CODPAT=:CODPAT";
	$bind['CODPAT']=$_POST['CODPAT'];
	$bind['PROGR']=$_POST['PROGR'];
	$sql->ins_upd($sql_upd, $bind);
	
	$sql_query="
		select email from ana_utenti where userid in (
		select p.userid from PT_USER_PROFILES p, PT_UTENTI_CENTRI c 
		where p.userid=c.userid 
		and p.profile_id=7
		and c.center=(select center from PT_REGISTRAZIONE where codpat=:CODPAT)
		)
		 ";
	$sql=new query($xml->conn);
	$bind['CODPAT']=$_POST['CODPAT'];
	Logger::send($bind);
	$sql->exec($sql_query,$bind);
	$to="";
		while($sql->get_row()){
			if ($sql->row ['EMAIL']!=''){
					$to.= $sql->row ['EMAIL'];
					$to.=",";
			}
		}
	$email_from="roche@drug_registry.it";
	$testo_mail="<b>Drug request notification</b>
			<br><br>
			Center: {$_POST['CENTER']}<br>
			Patient code: {$_POST['CODPAT']}
			<br><br>
			<a href=\"http://{$_SERVER['HTTP_HOST']}/prm-phase2/index.php?CENTER={$_POST['CENTER']}&CODPAT={$_POST['CODPAT']}&VISITNUM={$_POST['VISITNUM']}&ESAM=3&PROGR={$_POST['PROGR']}&form=dispensazione.xml\">Go to drug dispensation form</a>
			";
	$oggetto="Drug request notification";
	$bcc="l.verri@cineca.it,c.contino@cineca.it";
	send_email($to, $email_from, $email_from, $oggetto, $testo_mail, null, false, null, $bcc);
		
	
}

include_once "{$_SERVER['DOCUMENT_ROOT']}/../libs/xCRF/integrazioni_ct.inc";
class integrazioni extends integrazioni_prototype_ct{}


?>
