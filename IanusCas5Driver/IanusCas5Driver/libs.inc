<?php
//define("IDM_LIBS","/http/lib/IDM/");
//include_once IDM_LIBS."libs/MonitorLibs.inc.php";

function inactivityCron($conn){
	$query=new DriverIanusSql($conn);
	$fileLog=preg_replace("!html$!","inactivityCron.log", $_SERVER['DOCUMENT_ROOT']);
	$sql = "select inactivity_check from idp_servizi where URL=:URL";
	$binded='';
	$binded['URL']=strtoupper ( $_SERVER ['SERVER_NAME'] );
	$query->getRow($sql,$binded);
	file_put_contents($fileLog,"\n".date("d/m/y h:i:s")." ---- Eseguo controllo di inattivita' ---", FILE_APPEND );
	if($query->row['INACTIVITY_CHECK']=='1'){
		file_put_contents($fileLog,"\n ---Inattivita' abilitata", FILE_APPEND );
		$query=new DriverIanusSql($conn);
		$sql="select count(*) PRESENTE from user_tab_cols where table_name='UTENTI' and column_name in ('INACTIVE','CREATED_ON') ";
		$query->getRow($sql);
		if($query->row['PRESENTE']==0){
			file_put_contents($fileLog,"\n ---Campi non presenti nella tabella utenti", FILE_APPEND );
			echo "\n ---Campi non presenti nella tabella utenti";
			$str="alter table UTENTI add inactive number(1) default 0";
			$query->doCommand($str);
			$str="alter table UTENTI add created_on date default sysdate";
			$query->doCommand($str);
			$str="alter table UTENTI add constraint CK_UTENTI_INACTIVE  check (INACTIVE in (0,1))";
			$query->doCommand($str);
			$sql="select UPPER(comments) commento from user_col_comments where table_name ='UTENTI' and column_name='ABILITATO'";
			$query->getRow($sql);
			if($query->row['COMMENTO']=='ABILITAZIONE'){
				$str="comment on column UTENTI.inactive is 'Utente disabilitato per inattività'";
			}
			else{
				$str="comment on column UTENTI.inactive is 'User disabled because inactive'";
			}
			file_put_contents($fileLog,"\n ---Campi creati nella tabella utenti", FILE_APPEND );
			echo "\n ---Campi creati nella tabella utenti";
			$query->doCommand($str);
		}
		file_put_contents($fileLog,"\n ---Estraggo utenti da disattivare", FILE_APPEND );
		$sql_query="
				select u.userid, u.data_controllo, u.dttm_scadenzapwd, u.dttm_ultimoaccesso, a.nome, a.cognome, a.azienda_ente from (
select 
  userid,
  GREATEST(nvl(dttm_ultimoaccesso,to_date('01012011','DDMMYYYY')), nvl(dttm_scadenzapwd,to_date('01012011','DDMMYYYY'))-90,nvl(created_on,to_date('01012011','DDMMYYYY'))) as data_controllo,
  dttm_scadenzapwd, 
  dttm_ultimoaccesso, 
  created_on, 
  inactive, 
  abilitato from utenti where nvl(inactive,0)=0 and abilitato=1) u, 
  ana_utenti a
  where 
  a.userid(+)=u.userid
  and
  u.data_controllo<sysdate-180
  ";
		$query->Exec($sql_query);
		file_put_contents($fileLog,"\n ---Utenti da disabilitare: ".$query->numRows, FILE_APPEND );
		echo "\n ---Utenti da disabilitare: ".$query->numRows;
		while ($query->getRow()){
			file_put_contents($fileLog,"\n -----Disabilito utente ".$query->row['NOME']." ".$query->row['COGNOME']." (".$query->row['AZIENDA_ENTE'].") ".$query->row['USERID']." Data controllo: ".$query->row['DATA_CONTROLLO']." - DTTM_ULTIMOACCESSO: ".$query->row['DTTM_ULTIMOACCESSO']." - DTTM_SCADENZAPWD: ".$query->row['DTTM_SCADENZAPWD'], FILE_APPEND );
			$queryUpdate=new DriverIanusSql($conn);
			//$values['DTTM_ULTIMOACCESSO']='sysdate';
			$values['INACTIVE']=1;
			$pk['USERID']=$query->row['USERID'];
			$queryUpdate->Update($values,'UTENTI',$pk);
		}
		$conn->commit();
	}else {
		file_put_contents($fileLog,"\n ---Inattivita' disabilitata", FILE_APPEND );
		echo "\n ---Inattivita' disabilitata";

	}
	file_put_contents($fileLog,"\n ---Script terminato con successo ".date("d/m/y h:i:s")."---", FILE_APPEND );
	die();
}

function ServiceTimeReport($conn){
	global $enableServiceTime;
	global $startTime;
	global $startms;
	global $serviceTimeEvents;
	global $serviceTimeName;
	if (!$enableServiceTime){
		die("Servizio di reporting non attivato sul sistema");
	}
	echo "<html>
			<head>
				<title>Reports Tempi di risposta $serviceTimeName</title>";
	foreach ($serviceTimeEvents as $key=>$val){
		foreach ($val as $k=>$v) {
			$events[$v]=true;
		}
	}
	$sql1 = new DriverIanusSql($conn);
	if (isset($_GET['EXEC_TIME'])){
		$selected['EXEC_TIME']="id=\"activelink\"";
		$title="$serviceTimeName (Tempi di risposta X data)";
		$axis['h']="Data";
		$axis['v']="Secondi";
		$columns="data.addColumn('string', 'Data');\n";
		foreach ($events as $key=>$val){
			$columns.="data.addColumn('number', '$key');\n";
			$sql_query="
				select to_char(DATE_REP,'DD/MM/YYYY') DATE_, 
				AVG (EXEC_TIME) TS from (
				select SERVICE_NAME, EVENT, to_date(to_char(REQ_TIME,'DD/MM/YYYY'),'DD/MM/YYYY') DATE_REP, count(*) N_REQ, avg(EXEC_TIME) as EXEC_TIME 
  				from LOGEVENTSTIME group by SERVICE_NAME, EVENT, to_date(to_char(REQ_TIME,'DD/MM/YYYY'),'DD/MM/YYYY')
				) where SERVICE_NAME='$serviceTimeName' and EVENT='$key' group by  DATE_REP
			";
			$sql1->Exec($sql_query);
			while ($sql1->getRow()){
				$level1[$sql1->row['DATE_']]=true;
				$data[$key][$sql1->row['DATE_']]=$sql1->row['TS'];
			}
		}
		foreach ($level1 as $key=>$val){
			$data_.="['$key'";
			foreach ($events as $e=>$ev){
				$data_.=",";
				$data_.=$data[$e][$key]-0;
			}
			$data_.="],";
		}
		$data_=rtrim($data_, ",");
		drawChart($title, $axis, $columns, $data_);
	}else if (isset($_GET['REQ_SPEC'])){
		
		$selected['REQ_SPEC']="id=\"activelink\"";
		$title="$serviceTimeName (Tempi di risposta X richiesta)";
		$axis['h']="Eventi";
		$axis['v']="Secondi";
		$columns="data.addColumn('string', 'Eventi');\n";
		//$columns.="data.addColumn('number', 'Media');\n";
		//$columns.="data.addColumn('number', 'Minimo');\n";
		//$columns.="data.addColumn('number', 'Massimo');\n";
		foreach ($events as $key=>$val){
			$columns.="data.addColumn('number', '$key');\n";
		}
		$sql_query="
		select 
		  EVENT,
		  avg (EXEC_TIME) TS,
		  min (EXEC_TIME) MinTS,
		  max (EXEC_TIME) MaxTS
		  from LOGEVENTSTIME
		  where SERVICE_NAME='CheckPoint' group by EVENT
		";
		$sql1->Exec($sql_query);
		while ($sql1->getRow()){
			$level1[$sql1->row['EVENT']]=true;
			$data[$sql1->row['EVENT']]['AVG']=$sql1->row['TS'];
			$data[$sql1->row['EVENT']]['MIN']=$sql1->row['MINTS'];
			$data[$sql1->row['EVENT']]['MAX']=$sql1->row['MAXTS'];
		}
		$level1='';
		$level1['MIN']=true;
		$level1['MAX']=true;
		$level1['AVG']=true;
		foreach ($level1 as $key=>$val){
			$data_.="\n['$key'";
			foreach ($events as $e=>$ev){
				$data_.=",";
				$data_.=$data[$e][$key]-0;
			}
			$data_.="],";
		}
		//foreach ($level1 as $key=>$val){
		//	$data_.="\n['$key',{$data[$key]['AVG']},{$data[$key]['MIN']},{$data[$key]['MAX']}],";
		//}
		//die();
		$data_=rtrim($data_, ",");
		drawChart($title, $axis, $columns, $data_);
	}else if (isset($_GET['N_REQ'])){
		$selected['N_REQ']="id=\"activelink\"";
		$title="$serviceTimeName (N.ro Richieste X data)";
		$axis['h']="Data";
		$axis['v']="N.ro richieste";
		$columns="data.addColumn('string', 'Data');\n";
		foreach ($events as $key=>$val){
			$columns.="data.addColumn('number', '$key');\n";
			$sql_query="
						select to_char(DATE_REP,'DD/MM/YYYY') DATE_, 
						SUM (N_REQ) TS from (
						select SERVICE_NAME, EVENT, to_date(to_char(REQ_TIME,'DD/MM/YYYY'),'DD/MM/YYYY') DATE_REP, count(*) N_REQ, avg(EXEC_TIME) as EXEC_TIME 
		  				from LOGEVENTSTIME group by SERVICE_NAME, EVENT, to_date(to_char(REQ_TIME,'DD/MM/YYYY'),'DD/MM/YYYY')
						) where SERVICE_NAME='$serviceTimeName' and EVENT='$key' group by  DATE_REP
					";
			$sql1->Exec($sql_query);
			while ($sql1->getRow()){
				$level1[$sql1->row['DATE_']]=true;
				$data[$key][$sql1->row['DATE_']]=$sql1->row['TS'];
			}
		}
		foreach ($level1 as $key=>$val){
			$data_.="['$key'";
			foreach ($events as $e=>$ev){
				$data_.=",";
				$data_.=$data[$e][$key]-0;
			}
			$data_.="],";
		}
		$data_=rtrim($data_, ",");
		drawChart($title, $axis, $columns, $data_);
	}else if (isset($_GET['USERS'])){
		
		$selected['USERS']="id=\"activelink\"";
		$title="$serviceTimeName (Giornaliero X Utente)";
		$columns="data.addColumn('string', 'Utente');\n";
		$axis['h']="Utenti";
		$axis['v']="Secondi";
		foreach ($events as $key=>$val){
			$columns.="data.addColumn('number', '$key');\n";
			$sql_query="select USERID, AVG(EXEC_TIME) TS  from LOGEVENTSTIME where SERVICE_NAME='$serviceTimeName' and EVENT='$key' group by USERID";
			$sql1->Exec($sql_query);
			while ($sql1->getRow()){
				$level1[$sql1->row['USERID']]=true;
				$data[$key][$sql1->row['USERID']]=$sql1->row['TS'];
			}
		}
		foreach ($level1 as $key=>$val){
			$data_.="['$key'";
			foreach ($events as $e=>$ev){
				$data_.=",";
				$data_.=$data[$e][$key]-0;
			}
			$data_.="],";
		}
		$data_=rtrim($data_, ",");
		drawChart($title, $axis, $columns, $data_);
	}
	echo "
	<style>
	html,body{margin:0;padding:0}
body{font: 100.01% \"Trebuchet MS\",Arial,sans-serif}

div#header h1{margin:0;line-height:70px;margin-left:20px}
div#navigation{border-bottom: 1px solid #787878;padding-left: 20px}
div#navigation ul{list-style-type: none;margin: 0;padding: 0;white-space: nowrap}
div#navigation li{display: inline;margin: 0;padding:0}
div#navigation li a{text-decoration: none;border: 1px solid #787878;padding: 0px 0.3em;
    background: #ccc;color: #036}
div#navigation li a:hover{background-color: #f0f0f0}
div#navigation li#activelink a{border-bottom: 1px solid #fff;background-color: #fff;color: #603}
    </style>
	  </head>
			<body>
			<h1>Reports Tempi di risposta $serviceTimeName</h1>
				<div id=\"navigation\">
				<ul>
				    <li {$selected['USERS']}><a href=\"?MonitorReportChart&USERS\">Giornaliero X Utente</a></li>
				    <li {$selected['EXEC_TIME']}><a href=\"?MonitorReportChart&EXEC_TIME\">Tempi di risposta X data</a></li>
				    <li {$selected['N_REQ']}><a href=\"?MonitorReportChart&N_REQ\">N.ro Richieste X data</a></li>
				    <li {$selected['REQ_SPEC']}><a href=\"?MonitorReportChart&REQ_SPEC\">Tempi X richiesta</a></li>
				</ul>
				</div> 
			
	    <div id=\"chart_div\"></div>
	  </body>
	</html>";
	die();
}

function drawChart($title, $axis, $columns, $data_, $chartType='Column'){
	echo "
		<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>
	    <script type=\"text/javascript\">
	      google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});
	      google.setOnLoadCallback(drawChart);
	      function drawChart() {
	        var data = new google.visualization.DataTable();
	$columns
	        data.addRows([
	$data_
	        ]);
	        var options = {
	          width: 1200,
	          height: 600,
	          title: '$title',
	          hAxis: {title: '{$axis['h']}', titleTextStyle: {color: 'red'}},
	          vAxis: {title: '{$axis['v']}', titleTextStyle: {color: 'red'}},
	          legend: {position: 'right',textStyle: {fontSize: 12}}
	        };
	        var chart = new google.visualization.{$chartType}Chart(document.getElementById('chart_div'));
	        chart.draw(data, options);
	      }
	    </script>
	  
		";

}
function ShibJmeterTest($DriverIanusConnection){
	$sql_query = "select * from idp_spec";
	session_start();
	$id_session=session_id();
	$sql = new DriverIanusSql ( $DriverIanusConnection );
	$sql->getRow ( $sql_query );
	$config_service ['IDP-SERVER'] = $sql->row ['URL'];
	$jmxProbe=file_get_contents("/http/lib/DriverIanus/jmeter/testcase/testCaseParam.jmx");
	$jmxProbe=str_replace("[HTTP-HOST]", $_SERVER['HTTP_HOST'],$jmxProbe);
	$jmxProbe=str_replace("[IDP-SERVER]", $sql->row ['URL'],$jmxProbe);
	$jmxProbe=str_replace("[USERNAME]", $_SERVER['PHP_AUTH_USER'],$jmxProbe);
	$jmxProbe=str_replace("[PASSWORD]", $_SERVER['PHP_AUTH_PW'],$jmxProbe);
	$jmx_file="/http/lib/DriverIanus/jmeter/testcase/JmxFiles/{$id_session}.jmx";
	file_put_contents($jmx_file, $jmxProbe);
	$logFile="/http/lib/DriverIanus/jmeter/testcase/testResult/{$id_session}.log";
	$cmd="/http/lib/DriverIanus/jmeter/bin/jmeter.sh  -n -t $jmx_file -l $logFile";
	$cmds=$cmd."\n";
	$cmds.="rm -f $logFile\n";
	$cmds.="rm -f $jmx_file\n";
	//file_put_contents($logFile, $cmds);
	exec($cmd . " > /dev/null");
	$testResultFile=file_get_contents($logFile);
	exec("rm -f $logFile");
	exec("rm -f $jmx_file");
	if (preg_match("!<failure>false</failure>!", $testResultFile)){
		die("Test Ok");
	}
	else {
		header("HTTP/1.0 404 Not Found");
		die("Test Error");
	}
	
	
}

function SSOCheck($DriverIanusConnection){
	$sql_query="select count(*) as C from idp_servizi where upper(url)=upper('{$_SERVER['HTTP_HOST']}') and ID={$_SERVER['ID_PRINC_SERV']}";
	$sql=new DriverIanusSql($DriverIanusConnection);
	$sql->getRow($sql_query);
	if ($sql->row['C']=='0'){
		$sql_query="select count(*) as C from user_objects where OBJECT_NAME ='IDP_UTENTI_SERVIZI'";
		
		$sql=new DriverIanusSql($DriverIanusConnection);
		$sql->getRow($sql_query);
		if ($sql->row['C']=='1'){ 
			$sql_query="select USERID_DEST, ID_SERV from IDP_UTENTI_SERVIZI where ID_SERV=(select ID from idp_servizi where upper(url)=upper('{$_SERVER['HTTP_HOST']}')) and userid='{$_SERVER['REMOTE_USER']}' and ID_PRINC_SERV={$_SERVER['ID_PRINC_SERV']}";
		
			$sql=new DriverIanusSql($DriverIanusConnection);
			if ($sql->getRow($sql_query)){
				$goon=true;
				$_SERVER ['PHP_AUTH_USER']= $_SERVER['REMOTE_USER']=$sql->row['USERID_DEST'];
				$_SERVER['ID_PRINC_SERV']=$sql->row['ID_SERV'];
			}else {
				$sql_query="select USERID, ID_PRINC_SERV from IDP_UTENTI_SERVIZI where ID_PRINC_SERV=(select ID from idp_servizi where upper(url)=upper('{$_SERVER['HTTP_HOST']}')) and USERID_DEST='{$_SERVER['REMOTE_USER']}' and ID_SERV={$_SERVER['ID_PRINC_SERV']}";
				$sql=new DriverIanusSql($DriverIanusConnection);
				if ($sql->getRow($sql_query)){
					$goon=true;
					$_SERVER ['PHP_AUTH_USER']= $_SERVER['REMOTE_USER']=$sql->row['USERID'];
					$_SERVER['ID_PRINC_SERV']=$sql->row['ID_PRINC_SERV'];
				}
				$goon=false;
			}
			if ($goon){
			$sql_query="select ID_GRUPPOU from utenti_gruppiu where userid='{$_SERVER['REMOTE_USER']}'";
			$sql=new DriverIanusSql($DriverIanusConnection);
			$sql->Exec($sql_query);
			while ($sql->getRow()){
				$gruppi.="{$_SERVER['ID_PRINC_SERV']}.{$sql->row['ID_GRUPPOU']}|";
			}
			if ($gruppi!='') {
				$gruppi="|".$gruppi;
			}
			$_SERVER['GRUPPI']=$gruppi;
		}
		}
	}
}

function CheckPWD($conn, $userid, $plainPWD,$sso_user=false){
    require_once 'password_compat/lib/password.php';
//die("QUA!");    
    $userid=strtoupper($userid);
    $caseSensitivePassword = $plainPWD;
    $password = $plainPWD;
	$sql=new DriverIanusSql($conn);
	$upperPWD=strtoupper($plainPWD);
    $sql_query="select password from cas5_users where upper(userid)=:USERID||'@{$_SERVER['SID']}'";
	
	$binded=[];
	$binded['USERID']=$userid;
	if ($sql->getRow($sql_query,$binded)){
		$db_password=$sql->row['PASSWORD'];
        //die("$db_password");
        $seeds=explode('$', $db_password);
        $seed=$seeds[2];
        if ($password==$db_password || crypt($password,substr($password, 0,2))==$db_password || MonMD5AdminMd5Crypt($upperPWD, $seed)==$db_password || MonMD5AdminMd5Crypt($password, $seed)==$db_password){
            return true;
        }elseif (password_verify($password, $db_password)) {
            return true;
        }else {
            return false;
        }
	}
	else return false;
}


function CheckMalformedPass($password, $old_password){
	$password_flaws = array();
	$strlen = strlen($password);
	$ret_code[1]=false;
	$ret_code[2]=false;
	$ret_code[3]=false;
	$ret_code[4]=false;
	$ret_code[5]=false;
	$ret_code[6]=false;
	
	if (strtoupper($password)==strtoupper($old_password)) $ret_code[6]=true;
	if($strlen <= 7)
            $ret_code[1] = true;

         $count_chars = count_chars($password, 3);

         if(strlen($count_chars) < $strlen / 2)
            $ret_code[2] = true;
	$special_chars='!"#$%&\'()*+,-./:;<=>?@[\]^{|}~';
	$count_special=0;
	for ($i=0;$i<strlen($special_chars);$i++){
		for ($k=0;$k<strlen($password);$k++) if ($password[$k]==$special_chars[$i]) $count_special++;
	}
	$count_number=0;
	for ($k=0;$k<strlen($password);$k++) if (is_numeric($password[$k])) $count_number++;
    if ($count_special==0) $ret_code[3]=true;
    if ($count_number==0) $ret_code[4]=true;
    if (!preg_match("!^[a-zA-Z]!", $password)) $ret_code[5]=true;
    return $ret_code;
}

function ChangePassword($DriverIanusConnection){
	/* Controllo la lingua del browser */
	$lang = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
	
	/* Se la lingua del browser non è nè inglese nè italiano imposto la lingua inglese. */
	if(strtoupper($lang) != strtoupper("en") && strtoupper($lang) != strtoupper("it")){
		$lang = "en";
	}
	
	$lang=strtoupper($lang);
	$bind_arno['NEW_PASSWORD']=MonMD5AdminMd5Crypt($_POST['NEW_PWD']);
	//$_POST['NEW_PWD']=strtoupper($_POST['NEW_PWD']);
	//$_POST['NEW_PWD_CHECK']=strtoupper($_POST['NEW_PWD_CHECK']);
	require_once '/http/lib/IanusCas5Driver/change_password/config.inc';
	$change_pwd['NEW_PWD'][$lang]=$_POST['NEW_PWD'];
	$change_pwd['NEW_PWD_CHECK'][$lang]=$_POST['NEW_PWD_CHECK'];
	$password_rule="<h4 class='header blue lighter bigger'><i class='fa green fa-list'></i> ".$change_pwd['Password Validation'][$lang]."</h4>";
	foreach ($change_pwd['Password malformate'][$lang] as $key=>$val){
		$password_rule.="<li>$val</li>";
	}
	$change_pwd['OLD_PWD'][$lang]=$_POST['OLD_PWD'];
	$change_pwd['NEW_PWD'][$lang]=$_POST['NEW_PWD'];
	$change_pwd['NEW_PWD_CHECK'][$lang]=$_POST['NEW_PWD_CHECK'];
	$global_template_file="/http/lib/IanusCas5Driver/LOGIN/template/change_password.html";
	$common_service_template_file=$_SERVER['DOCUMENT_ROOT']."/change_pwd_it.htm";
	$fully_custom_file=$_SERVER['DOCUMENT_ROOT']."/change_pwd_".strtolower($lang).".htm";
	
	$template_form=file_get_contents($global_template_file);
	if (file_exists($common_service_template_file)) $template_form=file_get_contents($common_service_template_file);
	if (file_exists($fully_custom_file)) $template_form=file_get_contents($fully_custom_file);
	
	$form=file_get_contents("/http/lib/IanusCas5Driver/change_password/changePWD_form.html");
	
	$template_form=str_replace("<!--body-->", $form, $template_form);
	
		
	if ($_POST['ChangePWD']!=''){
		$change_pwd['OLD_PWD'][$lang]=$_POST['OLD_PWD'];
		$change_pwd['NEW_PWD'][$lang]=$_POST['NEW_PWD'];
		$change_pwd['NEW_PWD_CHECK'][$lang]=$_POST['NEW_PWD_CHECK'];
		if($_SERVER['SSO_USERID']=='')$userid=$_SERVER['REMOTE_USERID'];
		else {
			$userid=$_SERVER['SSO_USERID'];
			$sso_user=true;
		}
		$plainPWD=$_POST['OLD_PWD']; //strtoupper($_POST['OLD_PWD']);
		
		if (CheckPWD($DriverIanusConnection, $userid, $plainPWD,$sso_user)){
			if ($_POST['NEW_PWD']=='' || $_POST['NEW_PWD_CHECK']==''){
				$change_pwd['Messaggio Errore'][$lang]=$change_pwd['Compilare tutti i campi'][$lang];
			}else {
				$ret_code = CheckMalformedPass($_POST['NEW_PWD'], $plainPWD);
				$all_check_passed=true;
				foreach ($ret_code as $key=>$val){
					if ($val) $all_check_passed=false;
				}
				if (!$all_check_passed){
				$password_rule="<h4 class='header blue lighter bigger'><i class='fa green fa-list'></i> ".$change_pwd['Password Validation'][$lang]."</h4>";
				foreach ($change_pwd['Password malformate'][$lang] as $key=>$val){
					if ($ret_code[$key]) $password_rule.="<li style=\"color:red;font-weight:bold\">$val</li>";
					else $password_rule.="<li>$val</li>";
				}
					$change_pwd['Messaggio Errore'][$lang]=$change_pwd['Errore Password malformate'][$lang];
				}
				else{
					if ($_POST['NEW_PWD']!=$_POST['NEW_PWD_CHECK']){
					$change_pwd['Messaggio Errore'][$lang]=$change_pwd['Password non coincidono'][$lang];
					}
					else {
						//echo "NO2";
						$_POST['NEW_PWD']=ltrim($_POST['NEW_PWD'], " ");
						$_POST['NEW_PWD']=rtrim($_POST['NEW_PWD'], " ");
                        //require_once 'password_compat_lib/password.php';
                        //echo "QUA";
                        $bCryptedPass = password_hash($_POST['NEW_PWD'], PASSWORD_BCRYPT, array("cost" => 12));
                        $bCryptedPass = str_replace('$2y$', '$2a$', $bCryptedPass);
						//echo "LI";
                        $values['PASSWORD']=$bCryptedPass;
						
						$pk['USERID']=$_SERVER['REMOTE_USERID'];
						if(preg_match("/hypernetproject/i",$_SERVER['HTTP_HOST']))$values['DTTM_SCADENZAPWD']="sysdate+decode(SCADENZAPWD,'3',90,'8',90,180)";
						else $values['DTTM_SCADENZAPWD']="sysdate+90";
						if(!$sso_user){
							$table="UTENTI";
							$sql=new DriverIanusSql($DriverIanusConnection);
							$sql->Update($values, $table, $pk);
							$DriverIanusConnection->commit();
						}
						else{
							//Da gestire
							
							//$str="update CAS_USERS set ";
							$sql2=new DriverIanusSql($DriverIanusConnection);
							$sso_pk['USERID']=$_SERVER['SSO_USERID'];
							$sql2->Update($values,'CAS_USERS',$sso_pk);
							$DriverIanusConnection->commit();
							
						}
						if(preg_match("/arno-bundle-01/i",$_SERVER['DOCUMENT_ROOT'])){
							$str_arno="UPDATE autenticazione_utente
							SET
							password = :new_password,
							abilitato = 1,
							old_password1 = '',
							old_password2 = '',
							old_password3 = '',
							old_password4 = '',
							scadenza_password = sysdate+90,
							password_recover_random = NULL,
							password_recover_date = NULL
							WHERE nome_utente = :utente AND abilitato!=0";
							if(!$sso_user){
								$bind_arno['UTENTE']=$pk['USERID'];
							}else{
								$bind_arno['UTENTE']=$sso_pk['USERID'];
							}
							$sql_arno=new DriverIanusSql($DriverIanusConnection);
							$sql_arno->Exec($str_arno,$bind_arno);
						}
						$DriverIanusConnection->commit();
						$template_form="
						<html>
							<head>
							</head>
							<body>
							<h1><!-- SUCCESS --></h1>
							<a href=\"https://{$_SERVER['HTTP_HOST']}/ShibLogOut\"><!-- RELOGIN --></a>
						";//vecchia gestione superata con codice sottostante - STSANSVIL-628
						//STSANSVIL-628 vmazzeo 30.04.2020
						$template_form=file_get_contents($global_template_file);
						if (file_exists($common_service_template_file)) $template_form=file_get_contents($common_service_template_file);
						if (file_exists($fully_custom_file)) $template_form=file_get_contents($fully_custom_file);
						$form_success=file_get_contents("/http/lib/IanusCas5Driver/change_password/changePWD_SUCCESS.html");
						$template_form=str_replace("<!--body-->", $form_success, $template_form);
					}
				}
			}
		}
		else {
			$change_pwd['Messaggio Errore'][$lang]=$change_pwd['Password errata'][$lang];	
		}
	}
	$change_pwd['Messaggio Errore'][$lang]="<span style=\"color:red; font-weight:bold\">{$change_pwd['Messaggio Errore'][$lang]}</span>";
	
	foreach ($change_pwd as $key=>$val){
		$template_form=str_replace("<!-- $key -->", $val[$lang], $template_form);
	}
	$title=$change_pwd['Titolo'][$lang];
	$template_form=str_replace("<!-- password_rule -->", $password_rule, $template_form);
	$template_form=str_replace("<!-- titolo -->", $title, $template_form);
	die($template_form);	
}

function LocalLogout($DriverIanusConnection) {
	
	header('P3P: CP="IDC DSP COR CURa ADMa OUR IND PHY ONL COM STA"');
	foreach ( $_COOKIE as $key => $val ) {
		$cookies.="<li>$key".print_r($val,true);
		setcookie ( $key, "", time()-3600, "/" ); //, ".example.com", 0);
		setcookie ( $key, "", time()-3600, "/idp" ); //, ".example.com", 0);
		$js_delete_cookie.= "Delete_Cookie('{$key}' , '/idp' );\n";
		$js_delete_cookie.= "Delete_Cookie('{$key}' , '/' );\n";
	}
	
	session_start();
	$_SESSION = array();
	if (isset($_COOKIE[session_name()])) {
		setcookie(session_name(), '', time()-42000, '/');
	}               
	session_destroy();
	/**
	 * Modifica per l'inserimento delle righe di logout nella tabella SESSIONS del servizio,
	 * solo nei servizi PIERREL
	 *
	 * M. Verrocchio 22/08/2011
	 */
	if (preg_match("/\.hypernetproject\.com$/i", $_SERVER ['HTTP_HOST'])) {
		// Alter della tabella
		$sessions_cols = array ('ID' => 'NUMBER not null',
										'SESSION_ID' => 'CHAR(32)',
										'USERID' => 'VARCHAR2(20)',
										'DATA' => 'DATE',
										'URL' => 'VARCHAR2(2000)',
										'REFERER' => 'VARCHAR2(2000)',
										'TIPO' => 'VARCHAR2(20)' );
		$query = new DriverIanusSql ($DriverIanusConnection);
		$query_check_existence = "SELECT COLUMN_NAME FROM USER_TAB_COLUMNS WHERE TABLE_NAME='SESSIONS'";
		$query->Exec($query_check_existence);
		while ($query->getRow()) {
			$tb_vals[$query->row['COLUMN_NAME']] = $query->row['COLUMN_NAME'];
		}
		foreach ($sessions_cols as $key => $val) {
			if (!in_array($key, $tb_vals)) {
				$alter_sessions_table = "ALTER TABLE SESSIONS ADD $key $val";
				$query->doCommand ($alter_sessions_table);
			}
		}
	
		// Prendo i valori
		$remote_userid=substr($_SERVER['REMOTE_USERID'], 0, strpos($_SERVER['REMOTE_USERID'], "@"));
		$url = "https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
		$url_from = $_SERVER['HTTP_REFERER'];
		$url_tipo = "O";
		$session_id = substr($_SERVER['HTTP_SHIB_SESSION_ID'], 1, 32);
	
		if ($session_id != '' && $remote_userid != '') {
			// Prendo l'ultimo id
			$sql = new DriverIanusSql ( $DriverIanusConnection );
			$sql_query = "select ID from (select * from sessions t order by data desc) where rownum=1";
			$sql->getRow ( $sql_query );
			$session_number = $sql->row['ID']+1;
	
			// Inserisco la riga per il logout
			$sql = new DriverIanusSql ( $DriverIanusConnection );
			$sql->doCommand("insert into sessions(id, session_id, userid, data, url, referer, tipo) values(".$session_number.", '".$session_id."', '".$remote_userid."', sysdate , '".$url."', '".$url_from."', '".$url_tipo."')");
			$DriverIanusConnection->commit();
		}
	}
	
	if (! isset ( $_GET ['iframe'] )) {
		$sql = new DriverIanusSql ( $DriverIanusConnection );
		$host = strtoupper ( $_SERVER ['HTTP_HOST'] );
		$iframes = '';
			//if ($sql->row ['URL'] != $host)
				$iframes .= "
			<iframe src=\"https://" . $host . "/Shibboleth.sso/Logout\" style=\"display:none\"></iframe>
			";
		$sql = new DriverIanusSql ( $DriverIanusConnection );
		$sql_query = "select URL from idp_spec";
		$sql->getRow ( $sql_query );
		
		//$linkLogoutIDP="https://{$sql->row ['URL']}/idp/logout.jsp?redirect=http://{$_SERVER['HTTP_HOST']}";
		$iframes .= "<iframe src=\"https://{$sql->row ['URL']}/idp/logout.jsp\" style=\"display:none\" ></iframe>";
		
		/* Carico la configurazione */
		if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc")){
			
			/* File personalizzato per il singolo servizio
			 * SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
			 */
			include("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc");
		}else{
			
			/* Carico la configurazione standard */
			include("/http/lib/DriverIanus/LOGIN/login.conf.inc");
			//$login_template = file_get_contents("/http/lib/DriverIanus/LOGIN/template/login.html");
			//$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		}
		
		$lang=strtoupper($language);

	if (file_exists($_SERVER['DOCUMENT_ROOT']."/logout.htm")) 
		$body=file_get_contents($_SERVER['DOCUMENT_ROOT']."/logout.htm");
	else{
		
		if (file_exists("/http/lib/DriverIanus/template/accessError_{$lang}.html"))
			$body=file_get_contents("/http/lib/DriverIanus/template/logout_{$lang}.html");
		else $body=file_get_contents("/http/lib/DriverIanus/template/logout_EN.html");
	
	}
		if (file_exists($_SERVER['DOCUMENT_ROOT']."/template.htm")) $html=file_get_contents($_SERVER['DOCUMENT_ROOT']."/template.htm");
		else $html="
		<html>
			<head>
				<title>Logout Confederated</title>
				<SCRIPT TYPE=\"text/javascript\" LANGUAGE=\"javascript\">
					function waitPreloadPage() { //DOM
					if (document.getElementById){
						document.getElementById('prepage').style.visibility='hidden';
					}else{
						if (document.layers){ //NS4
							document.prepage.visibility = 'hidden';
						}
						else { //IE4
							document.all.prepage.style.visibility = 'hidden';
						}
					}
				}
				</SCRIPT>
			</head>
			<body onLoad=\"waitPreloadPage();\">
			<DIV id=\"prepage\" style=\"position:absolute; font-family:arial;
			 font-size:16; left:0px; top:0px; background-color:white; 
			 layer-background-color:white; height:100%; width:100%;\"> 
				<TABLE width=100%>
					<TR>
						<TD>
							<B>Loading ... ... Please wait!</B>
						</TD>
					</TR>
				</TABLE>
			</DIV>
				<!--body-->
			</body>
		</html>
		";
		$body=$iframes.$body;
		$linkHome="http://{$_SERVER['HTTP_HOST']}";
		$html=preg_replace("!https:\/\/(.*?)\/!", "http://{$_SERVER['HTTP_HOST']}/", $html);
		$html=str_replace("<!--body-->", $body, $html);
		$html=str_replace("<!--linkHome-->", $linkHome, $html);
		$html=str_replace("<!--url-->", $_SERVER['HTTP_HOST'], $html);
		die ( $html );
	}
	die ();
}

function GlobalLogout($DriverIanusConnection) {
	if ($_SERVER['REQUEST_URI']!='/authzssl/ShibLogOut'){
		header("Location: /authzssl/ShibLogOut");
		die();
	}
	header('P3P: CP="IDC DSP COR CURa ADMa OUR IND PHY ONL COM STA"');
	setcookie ( "JSESSIONID", "", time()-3600, "/pentaho" );
	foreach ( $_COOKIE as $key => $val ) {
		$cookies.="<li>$key = ".print_r($val,true)."</li>";
		setcookie ( $key, "", time()-3600, "/" ); //, ".example.com", 0);
		setcookie ( $key, "", time()-3600, "/idp" ); //, ".example.com", 0);
		$js_delete_cookie.= "Delete_Cookie('{$key}' , '/idp' );\n";
		$js_delete_cookie.= "Delete_Cookie('{$key}' , '/' );\n";
	}
	session_start();
	$_SESSION = array();
	if (isset($_COOKIE[session_name()])) {
		setcookie(session_name(), '', time()-42000, '/');
	}               
	session_destroy();
	
	if (! isset ( $_GET ['iframe'] )) {
		$sql = new DriverIanusSql ( $DriverIanusConnection );
		$host = strtoupper ( $_SERVER ['HTTP_HOST'] );
		$sql_query = "select URL from cas_services where enabled=1 and URL not in ('pentaho','cas')";
		$sql->Exec ( $sql_query );
		//die($_SERVER['CAS_URL']);
		$iframes = "<iframe src=\"{$_SERVER['CAS_URL']}/logout\" style=\"display:none\"></iframe>";
		while ( $sql->getRow () ) {
			if (!preg_match("!hypernetproject.com!",strtolower ( $sql->row ['URL'] ))){ //Franz 10/06/2016 esclusione di hypernet dal logout globale
				$iframes .= "
				<iframe src=\"http://" . strtolower ( $sql->row ['URL'] ) . "/ShibLogOut&iframe\" style=\"display:none\"></iframe>
				";
			}//Franz 10/06/2016 esclusione di hypernet dal logout globale
		}
		$iframes .= "
			<iframe src=\"{$_SERVER['CAS_URL']}/logout\" style=\"display:none\"></iframe>
			";
		$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		$language=strtolower($language);
		if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/logout.conf.inc")){
			include_once "{$_SERVER['DOCUMENT_ROOT']}/logout.conf.inc";
		}
		else if (file_exists("/http/lib/IanusCas5Driver/LOGIN/logout_messages_{$language}.inc")){
			include_once "/http/lib/IanusCas5Driver/LOGIN/logout_messages_{$language}.inc";
		}else {
			include_once "/http/lib/IanusCas5Driver/LOGIN/logout_messages_en.inc"; //Modifica franz 10/06/2016, prima c'era logout_messages_it.inc e funzionava a rovescio
		}
		
		$template=file_get_contents("/http/lib/IanusCas5Driver/LOGIN/template/logout_page.html");
		$template=str_replace("__iframes__", $iframes, $template);
		$message="<div id='prepage'><h1><i class=\"fa fa-spinner fa-spin\"></i> {$logout_messages['logging_out']}</h1></div>
				<div id='postpage' style='display:none'><h1><i class='fa fa-power-off'></i> {$logout_messages['logged_out']}</h1>
				<a href='http://{$_SERVER['HTTP_HOST']}'><i class='fa fa-home'></i> {$logout_messages['go_to_home']}</a>
				</div>";
		$title=$logout_messages['title']; 
		$template=str_replace("__logout_message__", $message, $template);
		$template=str_replace("__title_page__", $title, $template);
		if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login.css")) {
			$template=str_replace("<!--custom_css-->", "<link rel=\"stylesheet\" href=\"/authzssl/login.css\" />", $template);
		}
		//vmazzeo 30.03.2016 inserisco replace per logo
		if (file_exists($_SERVER['DOCUMENT_ROOT']."/authzssl/login-logo.png")) {
			$template=str_replace("<!--login_logo-->", "<div class=\"center\"><img src=\"/authzssl/login-logo.png\"/></div>", $template);
		}
		die($template);
	}
	die ();
}


function AccessError() {
	/* Carico la configurazione */
	if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc")){
		
		/* File personalizzato per il singolo servizio
		 * SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
		 */
		include("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc");
	}else{
		
		/* Carico la configurazione standard */
		include("/http/lib/DriverIanus/LOGIN/login.conf.inc");
		//$login_template = file_get_contents("/http/lib/DriverIanus/LOGIN/template/login.html");
		//$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
	}
	
	$lang=strtoupper($language);
	if (file_exists("/http/lib/DriverIanus/template/accessError_{$lang}.html"))
		$body=file_get_contents("/http/lib/DriverIanus/template/accessError_{$lang}.html");
	else $body=file_get_contents("/http/lib/DriverIanus/template/accessError_EN.html");
	if (file_exists($_SERVER['DOCUMENT_ROOT']."/template.htm")) $html=file_get_contents($_SERVER['DOCUMENT_ROOT']."/template.htm");
	else $html="
	<html>
	<head>
		<title><!--url--> (Errore di accesso)</title>
	</head>
	<body>
		<!--body-->
	</body>
	</html>
	";
	$logoutLink="https://{$_SERVER['HTTP_HOST']}/ShibLogOut";
	$html=preg_replace("!https:\/\/(.*?)\/!", "http://{$_SERVER['HTTP_HOST']}/", $html);
	$html=str_replace("<!--body-->", $body, $html);
	$html=str_replace("<!--logoutLink-->", $logoutLink, $html);
	$html=str_replace("<!--url-->", $_SERVER['HTTP_HOST'], $html);
	die ( $html );
}


function forbidden($script, $lang, $reason = null){
if (preg_match("!authzssl!",$script)){
		
			if (preg_match("/\.css$/",$script)) header ( "Content-type:text/css" );
			elseif (preg_match("/\.xls$/",$script)) header('Content-Disposition: attachment;');
			elseif (preg_match("!/SHIB_DOWNLOAD/!", $script)) header('Content-Disposition: attachment;');
			else header ( "Content-type:*" );
		
		readfile ( "{$_SERVER ['DOCUMENT_ROOT']}{$script}" );
		
		die();
	}
		/* Carico la configurazione */
		if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc")){
			
			/* File personalizzato per il singolo servizio
			 * SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
			 */
			include("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc");
		}else{
			/* Carico la configurazione standard */
			include("/http/lib/DriverIanus/LOGIN/login.conf.inc");
			//$login_template = file_get_contents("/http/lib/DriverIanus/LOGIN/template/login.html");
			//$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		}
		
		$lang=strtoupper($language);
	
	if (file_exists("/http/lib/DriverIanus/template/accessError_{$lang}.html"))
		$body=file_get_contents("/http/lib/DriverIanus/template/accessError_{$lang}.html");
	else $body=file_get_contents("/http/lib/DriverIanus/template/accessError_EN.html");
	if (file_exists($_SERVER['DOCUMENT_ROOT']."/template.htm")) $html=file_get_contents($_SERVER['DOCUMENT_ROOT']."/template.htm");
	else $html="
	<html>
	<head>
		<title><!--url--> (Errore di accesso)</title>
	</head>
	<body>
		<!--body-->
	</body>
	</html>
	";
	if (file_exists("/http/lib/DriverIanus/template/forbidden_{$lang}.html"))
		$body=file_get_contents("/http/lib/DriverIanus/template/forbidden_{$lang}.html");
	else $body=file_get_contents("/http/lib/DriverIanus/template/forbidden_EN.html");
	
	$body=str_replace("<!--_reason_-->", '(<b>Reason</b>: '.$reason.')',$body );
	$body.="<br/>{$_SERVER['REMOTE_USERID']}";
	$body.="<br/>{$reason}";
	
	$html=preg_replace("!https:\/\/(.*?)\/!", "http://{$_SERVER['HTTP_HOST']}/", $html);
	$html=str_replace("<!--body-->", $body, $html);
	$html=str_replace("<!--url-->", $_SERVER['HTTP_HOST'], $html);
	$script=$_SERVER['HTTP_HOST'].$script;
	//$html=str_replace("<!--script-->", $script, $html);
	die($html);
}

function pageNotFound($script, $lang){
	
		/* Carico la configurazione */
		if(file_exists("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc")){
			
			/* File personalizzato per il singolo servizio
			 * SETTARE LA VARIABILE $language al suo interno e i corrispondenti valori nella lingua scelta!!!
			 */
			include("{$_SERVER['DOCUMENT_ROOT']}/login.conf.inc");
		}else{
			/* Carico la configurazione standard */
			include("/http/lib/DriverIanus/LOGIN/login.conf.inc");
			//$login_template = file_get_contents("/http/lib/DriverIanus/LOGIN/template/login.html");
			//$language = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
		}
		
		$lang=strtoupper($language);
	
	if (file_exists("/http/lib/DriverIanus/template/accessError_{$lang}.html"))
		$body=file_get_contents("/http/lib/DriverIanus/template/accessError_{$lang}.html");
	else $body=file_get_contents("/http/lib/DriverIanus/template/accessError_EN.html");
	if (file_exists($_SERVER['DOCUMENT_ROOT']."/template.htm")) $html=file_get_contents($_SERVER['DOCUMENT_ROOT']."/template.htm");
	else $html="
	<html>
	<head>
		<title><!--url--> (Errore di accesso)</title>
	</head>
	<body>
		<!--body-->
	</body>
	</html>
	";
	if (file_exists("/http/lib/DriverIanus/template/pageNotFound_{$lang}.html"))
		$html=file_get_contents("/http/lib/DriverIanus/template/pageNotFound_{$lang}.html");
	else $html=file_get_contents("/http/lib/DriverIanus/template/pageNotFound_EN.html");
	$html=preg_replace("!https:\/\/(.*?)\/!", "http://{$_SERVER['HTTP_HOST']}/", $html);
	$html=str_replace("<!--body-->", $body, $html);
	$html=str_replace("<!--url-->", $_SERVER['HTTP_HOST'], $html);
	$script=$_SERVER['HTTP_HOST'].$script;
	$html=str_replace("<!--script-->", $script, $html);
	die($html);
}

function MonMD5PassStrSplit($str, $nr) {
     //Return an array with 1 less item then the one we have
     return array_slice(explode("-l-", chunk_split($str, $nr, '-l-')), 0, -1);
}

function MonMD5Hex2Raw( $str ){
  $chunks = MonMD5PassStrSplit($str, 2);
  $op='';
  for( $i = 0; $i < sizeof($chunks); $i++ ) {
       $op .= chr( hexdec( $chunks[$i] ) );
   }
   return $op;
}

function MonMD5AdminMd5Crypt($pwd, $salt=null){
global $MonMD5AdminMd5Crypt_chars;
$magic='$apr1$';

  if ($salt!=null) {
	$salt = $salt;
    } else {
	$salt = $MonMD5AdminMd5Crypt_chars[rand(0,count($MonMD5AdminMd5Crypt_chars))].$MonMD5AdminMd5Crypt_chars[rand(0,count($MonMD5AdminMd5Crypt_chars))].$MonMD5AdminMd5Crypt_chars[rand(0,count($MonMD5AdminMd5Crypt_chars))].".....";
	#join ( '', map { $MD5AdminMd5Crypt_chars[ int rand @MD5AdminMd5Crypt_chars ] } ( 0 .. 2 ) )  . ("." x 5);
    }
$MonMD5=md5($pwd.$salt.$pwd);
$MonMD5=MonMD5Hex2Raw($MonMD5);

$ctx=$pwd.$magic.$salt;
for ($pl = strlen($pwd); $pl > 0; $pl -= 16) {
	$ctx.=substr($MonMD5, 0, $pl > 16 ? 16 : $pl);
    }

for ($i = strlen($pwd); $i; $i >>= 1) {
	if ($i & 1) $ctx.=pack("C", 0);
	else $ctx.=substr($pwd, 0, 1);
}
$ctx=md5($ctx);
$ctx=MonMD5Hex2Raw($ctx);
$final_ctx1=$ctx;
for ($i = 0; $i < 1000; $i++) {
			$ctx1='';
			if ($i & 1) { $ctx1.=$pwd; }
			else { $ctx1.=substr($final_ctx1, 0, 16); }
			if ($i % 3) { $ctx1.=$salt; }
			if ($i % 7) { $ctx1.=$pwd; }
			if ($i & 1) { $ctx1.=substr($final_ctx1, 0, 16); }
			else { $ctx1.=$pwd; }
			$final_ctx1=md5($ctx1);
			$final_ctx1=MonMD5Hex2Raw($final_ctx1);
    }
    $final=$final_ctx1;
    #echo "<hr>".$final."<hr>";
	$passwd = '';
		$unp=unpack("C", (substr($final, 0, 1)));
		$unp1=unpack("C", (substr($final, 6, 1)));
		$unp2=unpack("C", (substr($final, 12, 1)));
    $passwd .= MonMD5AdminMd5Crypt_to64(floor($unp[1] << 16)
		    | floor($unp1[1] << 8)
		    | floor($unp2[1]), 4);
		#print "<br>".$passwd;
		$unp=unpack("C", (substr($final, 1, 1)));
		$unp1=unpack("C", (substr($final, 7, 1)));
		$unp2=unpack("C", (substr($final, 13, 1)));
    $passwd .= MonMD5AdminMd5Crypt_to64(floor($unp[1] << 16)
		    | floor($unp1[1] << 8)
		    | floor($unp2[1]), 4);
		$unp=unpack("C", (substr($final, 2, 1)));
		$unp1=unpack("C", (substr($final, 8, 1)));
		$unp2=unpack("C", (substr($final, 14, 1)));
    $passwd .= MonMD5AdminMd5Crypt_to64(floor($unp[1] << 16)
		    | floor($unp1[1] << 8)
		    | floor($unp2[1]), 4);
		$unp=unpack("C", (substr($final, 3, 1)));
		$unp1=unpack("C", (substr($final, 9, 1)));
		$unp2=unpack("C", (substr($final, 15, 1)));
    $passwd .= MonMD5AdminMd5Crypt_to64(floor($unp[1] << 16)
		    | floor($unp1[1] << 8)
		    | floor($unp2[1]), 4);
		$unp=unpack("C", (substr($final, 4, 1)));
		$unp1=unpack("C", (substr($final, 10, 1)));
		$unp2=unpack("C", (substr($final, 5, 1)));
    $passwd .= MonMD5AdminMd5Crypt_to64(floor($unp[1] << 16)
		    | floor($unp1[1] << 8)
		    | floor($unp2[1]), 4);
		$unp=unpack("C", substr($final, 11, 1));
    $passwd .= MonMD5AdminMd5Crypt_to64(floor($unp[1]), 2);
		return $magic.$salt.'$'.$passwd;
}

function MonMD5AdminMd5Crypt_to64 ($v, $n) {
	  global $MonMD5AdminMd5Crypt_chars;
    $ret = '';

    while (--$n >= 0) {
		$ret .= $MonMD5AdminMd5Crypt_chars[ $v & 0x3f ];
		$v >>= 6;
    }
    return $ret;
}

$MonMD5AdminMd5Crypt_chars  = array( '.', '/');
$MonMD5AdminMd5Crypt_chars=array_merge($MonMD5AdminMd5Crypt_chars,range(0,9), range('A','Z'), range('a','z'));


function ForceChangeUserGest($DriverIanusConnection, $auths) {
	$sql = new DriverIanusSql ( $DriverIanusConnection );
	$sql_query = "select count(*) as conto from user_tables where TABLE_NAME in ('SHIBFORCEUSER','SUPERSHIBUSERS')";
	$sql->getRow ( $sql_query );

	if ($sql->row ['CONTO'] == '2') {

		$sql_query = "select count(*) as conto from SUPERSHIBUSERS where userid='{$auths [0]}'";
		$sql->getRow ( $sql_query );


		if ($sql->row ['CONTO'] == '1') {

			$error_msg = '';
			$sql_query = "select USERID_FORCED from SHIBFORCEUSER where USERID='{$auths [0]}'";

			if ($sql->getRow ( $sql_query )) {
				
				$_SERVER ['REMOTE_USER'] = $sql->row ['USERID_FORCED'];
				$_SERVER ['PHP_AUTH_USER'] = $sql->row ['USERID_FORCED'];
				$sql_query = "select * from utenti_gruppiu where userid='{$sql->row['USERID_FORCED']}'";
				$sql->Exec ( $sql_query );

				while ( $sql->getRow () ) {
					if (!isset($gruppi)) $gruppi='';
					$gruppi .= "{$_SERVER ['ID_PRINC_SERV']}.{$sql->row['ID_GRUPPOU']}|";
				}
				if ($gruppi != '')
					$gruppi = "|" . $gruppi;
				$_SERVER ['GRUPPI'] = $gruppi;
			}
			if (isset ( $_GET ['USERID_FORCED'] )) {
				//echo "sono qui".$_GET ['USERID_FORCED'] ;
				//die();
				$sql_query = "select count(*) as conto from utenti where userid='" . strtoupper ( $_GET ['USERID_FORCED'] ) . "'";
				$sql->getRow ( $sql_query );

				if ($sql->row ['CONTO'] > 0) {
					$values ['USERID'] = strtoupper ( $auths [0] );
					$values ['USERID_FORCED'] = strtoupper ( $_GET ['USERID_FORCED'] );
					$values ['DT'] = "sysdate";
					$tb = "SHIBFORCEUSER";
					$sql->Save ( $values, $tb );

					$DriverIanusConnection->commit ();
					$url = urldecode ( $_GET ['URL_ENCODED'] );
					header ( "Location:$url" );
					exit;
				} else {
					$url = urldecode ( $_GET ['URL_ENCODED'] );
					$error_msg = "
					<br/><span style='color:red'>User {$_GET['USERID_FORCED']} inesistente</span>
					<br/><a href=\"$url\">back</a>
					";
				}
			}
			
			header("X-forced-user:".$_SERVER ['REMOTE_USER']);
			if (isset ( $_GET ['URL_ENCODED'] )){
				$url_encode = $_GET ['URL_ENCODED'];
			}
			else
				$url_encode = urlencode ( $_SERVER ['REQUEST_URI'] );

			if ($error_msg != '')
				die ( "$error_msg" );
				
		}
		else{
			header("X-no-forced-user:".$_SERVER ['REMOTE_USER']);
		}
		

	} else {
		$create_table = "
					CREATE TABLE SHIBFORCEUSER(
						USERID VARCHAR2(40 CHAR),
						USERID_FORCED VARCHAR2(40 CHAR),
						DT DATE
					)
				";
		$sql_pk = "alter table SHIBFORCEUSER add constraint PK_SHIBFORCEUSER primary key(USERID)";
		$sql->doCommand ( $create_table );
		$sql->doCommand ( $sql_pk );
		$create_table_2 = "
				create table SUPERSHIBUSERS(
				  USERID VARCHAR2(40 CHAR)
				)";
		$sql_pk_2 = "alter table SUPERSHIBUSERS add constraint PK_SUPERSHIBUSERS primary key (USERID)";
		$sql->doCommand ( $create_table_2 );
		$sql->doCommand ( $sql_pk_2 );
	}
}

function isPublic($script_name, $oraconn) {
	return check_ammin ( $script_name, $oraconn );
}

function userDisabledForInactivity($user,$conn){
	$query=new DriverIanusSql($conn);
	$sql = "select inactivity_check from idp_servizi where URL=:URL";
	$binded='';
	$binded['URL']=strtoupper ( $_SERVER ['SERVER_NAME'] );
	$query->getRow($sql,$binded);
	if($query->row['INACTIVITY_CHECK']=='1'){
		$query=new DriverIanusSql($conn);
		$sql="select count(*) PRESENTE from user_tab_cols where table_name='UTENTI' and column_name in ('INACTIVE','CREATED_ON') ";
		$query->getRow($sql);
		if($query->row['PRESENTE']==0){
			$str="alter table UTENTI add inactive number(1) default 0";
			$query->doCommand($str);
			$str="alter table UTENTI add created_on date default sysdate";
			$query->doCommand($str);
			$str="alter table UTENTI add constraint CK_UTENTI_INACTIVE  check (INACTIVE in (0,1))";
			$query->doCommand($str);
			$sql="select UPPER(comments) commento from user_col_comments where table_name ='UTENTI' and column_name='ABILITATO'";
			$query->getRow($sql);
			if($query->row['COMMENTO']=='ABILITAZIONE'){
				$str="comment on column UTENTI.inactive is 'Utente disabilitato per inattività'";
			}
			else{
				$str="comment on column UTENTI.inactive is 'User disabled because inactive'";
			}
			$query->doCommand($str);
		}

		$query=new DriverIanusSql($conn);
		/*$pk ['USERID'] = $data_tb ['USERID'] ['VALUE']=$user;
		$data_tb['USERID']['TYPE']=SQLT_CHR;
		$data_tb['USERID']['PK']=true;
		$data_tb['USERID']['ORA_TYPE']='VARCHAR2';
		$data_tb['USERID']['LEN']='200';
		//$query->getRow("select 1 prova from dual");
		$where=DriverIanusSql::BuildWhereBinded ( $pk, $data_tb );
		$pk_where = $where ['WhereString'];*/
		$sql="select  months_between(sysdate,nvl(DTTM_ULTIMOACCESSO,nvl(CREATED_ON,to_date('01012011','DDMMYYYY'))) ) MONTHS, DTTM_ULTIMOACCESSO, ABILITATO,INACTIVE  from utenti t where userid='{$user}' ";
		$query->getRow($sql);

		if($query->row['INACTIVE']=='1'){
			$inactive=true;
		}
		if($query->row['MONTHS']>=6){
			if(!$inactive){
				$queryUpdate=new DriverIanusSql($conn);
				$values['DTTM_ULTIMOACCESSO']='sysdate';
				$values['INACTIVE']=1;
				$pk['USERID']=$user;
				$queryUpdate->Update($values,'UTENTI',$pk);
				$conn->commit();
				$inactive=true;
			}

		}
		if($inactive)
		return true;
		else
		return false;
	}
	else{
		return false;
	}
}

function UserAuthorized($user, $server_gruppi, $script_name, $conn) {
	return check_user_access ( $script_name, $user, $server_gruppi, $conn );
}

function check_user_access($script, $userid, $server_gruppi, $conn) {
	$sql_query="select abilitato from utenti where userid=:USERID";
	$binded='';
	$binded['USERID']=$userid;
 	$sql = new DriverIanusSql ( $conn );
	$sql->getRow ( $sql_query, $binded);
//  if ($_SERVER['HTTP_HOST']=='diva.sissdev.cineca.it'){
//  	echo $sql->row['ABILITATO']."<hr>";
//  }
	if ($sql->row['ABILITATO']!=1){
		return false;
	}

	$sql_query = "select sid,idp_group from cas_services where upper(URL)=:URL";
	$binded='';
	$binded['URL']=strtoupper ( $_SERVER ['SERVER_NAME'] );
 	$sql = new DriverIanusSql ( $conn );
	$sql->getRow ( $sql_query , $binded);
	$servizi_gruppi = explode ( "|", $server_gruppi );
	
	$gruppi = '';
	$i=0;
	$binded='';
	foreach ( $servizi_gruppi as $key => $val ) {
		if (strpos ($val, "@{$sql->row['SID']}" )!==false) {
			$gruppo = str_replace ( "@{$sql->row['SID']}", "", $val );
			$thisvar="IN_IDX_$i";
			$gruppi .= ":$thisvar,";
			$binded[$thisvar]=$gruppo;
			
			$servizi_gruppi_ianus [] = $gruppo;
			$i++;
			
		}
	}
	
	$gruppi = rtrim ( $gruppi, "," );
	$gruppi_where = " and id_gruppou is null";
	$gruppi=" select id_gruppou from utenti_gruppiu where userid=:USERID and abilitato=1 ";
	if ($gruppi != '')
		$gruppi_where = " and id_gruppou in ($gruppi)";
	
	$sql_query_base = "
	select nome, passwd_flag from funzioni where abilitato = 1 and nome in
       (select nome_funz from gruppif_funz where nome_funz=:SCRIPT and abilitato = 1 and id_gruppof in
               (select id_gruppof from gruppiu_gruppif where abilitato = 1 $gruppi_where))
	-- eccezioni gruppi
	union
	select nome, passwd_flag from funzioni where abilitato = 1 and nome in
		(select nome_funz from gruppiu_funz where nome_funz=:SCRIPT $gruppi_where)
	-- eccezioni utente
	union
	select nome, passwd_flag from funzioni where abilitato = 1 and nome in
		(select nome_funz from utenti_funz where nome_funz=:SCRIPT and userid=:USERID)
	";
 	$binded['SCRIPT']=$script;
	$binded['USERID']=$userid;
	
	$sql = new DriverIanusSql ( $conn );
	if ($sql->getRow ( $sql_query_base,$binded )) {
		return true;
	} else {
		return false;
	}
}

function check_ammin($script, $conn) {
	if(preg_match("/^\/casAuthn\//",$script)) return true;
	$script=preg_replace("/[\/]*\/[\/]*/","/",$script);
	
	$sql_query = "
	select nome, passwd_flag
  		from funzioni
  	where nome =:SCRIPT
  	union
  	select nome, passwd_flag
  		from funzioni
  	where nome =:SCRIPT_
  	";
	
	$binded='';
	$binded['SCRIPT']=$script;
	$binded['SCRIPT_']="{$script}/";

	$sql = new DriverIanusSql ( $conn );
	$sql->Exec ( $sql_query,$binded );
	if ($sql->getRow ()) {

		$ret ['script_ammin'] = $sql->row ['NOME'];
		$ret ['passwd_flag'] = $sql->row ['PASSWD_FLAG'];
		return $ret;
	} else {
		if ($script == '') {
			$ret ['script_ammin'] = "";
			$ret ['passwd_flag'] = 0;
			return $ret;
		}
		$script = rtrim ( $script, "/" );
		$splits = explode ( "/", $script );
		$url = '';
		
		for($i = 0; $i < count ( $splits ) - 1; $i ++) {
			$url .= $splits [$i] . "/";
		}
		return check_ammin ( $url, $conn );
	}

}

function getDir($script) {
	if (! is_dir ( $script )) {
		$dirs = explode ( "/", $script );
		$dir = '';
		for($i = 0; $i < count ( $dirs ) - 1; $i ++) {
			$dir .= "/" . $dirs [$i];
		}
		return $dir;
	} else
		return $script;
}

function LoginGest($DriverIanusConnection) {
	global $authzsslEnabled;
	if (	
	$authzsslEnabled[$_SERVER['HTTP_HOST']]
	){
		
		if (!is_dir($_SERVER['DOCUMENT_ROOT']."/authzssl")){
			$system[]="mkdir ".$_SERVER['DOCUMENT_ROOT']."/authzssl";
			$system[]="chgrp devj ".$_SERVER['DOCUMENT_ROOT']."/authzssl -R";
			$system[]="chmod g+rw ".$_SERVER['DOCUMENT_ROOT']."/authzssl -R";
		}
		if (!is_link($_SERVER['DOCUMENT_ROOT']."/authzssl/LOGIN")){
			$filesToCheck[]='LOGIN';
			$filesToCheck[]='login_template.htm';
			$filesToCheck[]='LOGIN_CSS';
			$filesToCheck[]='LOGIN_IMAGES';
			$filesToCheck[]='LOGIN_MEDISHARE';
			$filesToCheck[]='css';
			$filesToCheck[]='css_login';
			$filesToCheck[]='images_login';
			$filesToCheck[]='images';
			$filesToCheck[]='themes';
			$filesToCheck[]='text.js';
			$filesToCheck[]='images_episouth';
			$filesToCheck[]='NWA/images_episouth';
		
			foreach ($filesToCheck as $key=>$val){
				if (file_exists($_SERVER['DOCUMENT_ROOT']."/$val")){
					//echo "<li>Sono qui - $val</li>";
					//echo "<li>ln -s ".$_SERVER['DOCUMENT_ROOT']."/$val ".$_SERVER['DOCUMENT_ROOT']."/authzssl/$val</li>";
					if (preg_match("!\/!", $val)){
						$dirs=preg_split("!\/!", $val);
						$lastPath=$_SERVER['DOCUMENT_ROOT']."/authzssl";
						foreach ($dirs as $k=>$v){
							if ($k<count($dirs)-1){
								$system[]="mkdir {$lastPath}/$v";
								$system[]="chgrp devj {$lastPath}/$v -R";
								$system[]="chmod g+rw {$lastPath}/$v -R";
								$lastPath.="/$v";
							}
						}
					}
					$system[]="ln -s ".$_SERVER['DOCUMENT_ROOT']."/$val ".$_SERVER['DOCUMENT_ROOT']."/authzssl/$val";
				}else {
					if ($val=='LOGIN'){
						$system[]="ln -s /http/lib/DriverIanus/LOGIN ".$_SERVER['DOCUMENT_ROOT']."/authzssl/LOGIN";
					}
				}	
			}
		}
		foreach ($system as $key=>$val){
			$ret=exec($val);
			//echo $val."<br/>";
			
		}
		//die();
		
	}
	foreach ( $_SERVER as $key => $val ) {
		$new_key = preg_replace ( "!^REDIRECT_!", "", $key );
		$_SERVER [$new_key] = $val;
	}
	foreach ( $_GET as $key => $val ) {
		$HTTP_GET_VARS [$key] = $val;
	}
	foreach ( $_POST as $key => $val ) {
		$HTTP_POST_VARS [$key] = $val;
	}

	$link_to = $_SERVER ['REQUEST_URI'];
	$script = explode ( "?", $link_to );
	$script = $script [0];

	$is_cgi = false;
	$found = false;

	$service_script_dir = $_SERVER ['DOCUMENT_ROOT'];

	$_SERVER ['SCRIPT_NAME'] = $script;
	$_SERVER ['SCRIPT_FILENAME'] = $script;
	$_SERVER ['PHP_SELF'] = $script;

	$_SERVER ['HTTP_SHIB_MAIL'] = "c.contino@cineca.it";

	chdir ( getDir ( "{$service_script_dir}{$script}" ) );

	$sql_query = "select * from idp_spec";
	$sql = new DriverIanusSql ( $DriverIanusConnection );
	$sql->getRow ( $sql_query );
	global $config_service;
	$config_service ['AUTH_TYPE'] = 'LOGIN-FORM';
	$config_service ['IDP-SERVER'] = $sql->row ['URL'];
	$config_service ['IDP-PORTAL'] = $sql->row ['PORTAL'];
	$config_service ['LOGIN-ERROR'] = "Userid o Password Errate.";
	$sql_query = "select id from idp_servizi where upper(url) =:URL";
	$binded='';
	$binded['URL']=strtoupper($_SERVER['HTTP_HOST']);
	$sql = new DriverIanusSql ( $DriverIanusConnection );
	$sql->getRow ( $sql_query, $binded );
	$config_service['ID_SERVIZIO']=$sql->row['ID'];
	
	$authServlet = $sql->row ['AUTHSERVLET'];
	$login_error = $config_service ['LOGIN-ERROR'];
	
	include_once "/http/lib/DriverIanus/login.common.php";
	die ();
}

function ForgetPassword($DriverIanusConnection) {
	//ini_set("display_errors", 1);
	//error_reporting(E_ALL);
	foreach ( $_SERVER as $key => $val ) {
		$new_key = preg_replace ( "!^REDIRECT_!", "", $key );
		$_SERVER [$new_key] = $val;
	}
	foreach ( $_GET as $key => $val ) {
		$HTTP_GET_VARS [$key] = $val;
	}
	foreach ( $_POST as $key => $val ) {
		$HTTP_POST_VARS [$key] = $val;
	}

	$link_to = $_SERVER ['REQUEST_URI'];
	$script = explode( "?", $link_to );
	$script = $script [0];

	$is_cgi = false;
	$found = false;

	$service_script_dir = $_SERVER ['DOCUMENT_ROOT'];

	$_SERVER ['SCRIPT_NAME'] = $script;
	$_SERVER ['SCRIPT_FILENAME'] = $script;
	$_SERVER ['PHP_SELF'] = $script;

	$_SERVER ['HTTP_SHIB_MAIL'] = "c.contino@cineca.it";

	chdir ( getDir ( "{$service_script_dir}{$script}" ) );

	$sql = new DriverIanusSql ( $DriverIanusConnection );
	$host = strtoupper ( $_SERVER ['HTTP_HOST'] );
	/*
	$sql_query = "select PORTAL from idp_spec";
	$sql->getRow ( $sql_query );
	$url_portal_idp = $sql->row ['PORTAL'];
	*/
	
	
	include_once '/http/lib/IanusCas5Driver/forget_password/index.php';
	die ();
}

function ForgetUserid($DriverIanusConnection) {
	foreach ( $_SERVER as $key => $val ) {
		$new_key = preg_replace ( "!^REDIRECT_!", "", $key );
		$_SERVER [$new_key] = $val;
	}
	foreach ( $_GET as $key => $val ) {
		$HTTP_GET_VARS [$key] = $val;
	}
	foreach ( $_POST as $key => $val ) {
		$HTTP_POST_VARS [$key] = $val;
	}

	$link_to = $_SERVER ['REQUEST_URI'];
	$script = explode ( "?", $link_to );
	$script = $script [0];

	$is_cgi = false;
	$found = false;

	$service_script_dir = $_SERVER ['DOCUMENT_ROOT'];

	$_SERVER ['SCRIPT_NAME'] = $script;
	$_SERVER ['SCRIPT_FILENAME'] = $script;
	$_SERVER ['PHP_SELF'] = $script;

	$_SERVER ['HTTP_SHIB_MAIL'] = "c.contino@cineca.it";

	chdir ( getDir ( "{$service_script_dir}{$script}" ) );

	$sql = new DriverIanusSql ( $DriverIanusConnection );
	$host = strtoupper ( $_SERVER ['HTTP_HOST'] );
	$sql_query = "select PORTAL from idp_spec";
	$sql->getRow ( $sql_query );
	$url_portal_idp = $sql->row ['PORTAL'];
	include_once 'forget_userid/forget_userid.php';
	die ();
}

function PerlMonitor($DriverIanusConnection) {  
	$sql_query="select * from CAS_SERVICES where upper(URL)='".strtoupper($_SERVER['HTTP_HOST'])."'";
	$sql=new DriverIanusSql($DriverIanusConnection);
	$sql->getRow($sql_query);
	$sid=$sql->row['SID'];
	$gruppi="|";
	$gruppi_split_1=explode("|", $_GET['GRUPPI']);
	for ($i=1;$i<count($gruppi_split_1)-1;$i++){
		$gruppo_split_2=explode(".", $gruppi_split_1[$i]);
		$gruppo_el=$gruppo_split_2[1]."@".$sid;
		$gruppi.=$gruppo_el."|";
	}
	if ($sql->row['ENABLED']!='1'){
		die ( "DISABLED" );
	}
	$ret = isPublic ( $_GET ['URI'], $DriverIanusConnection );
	if ($ret ['passwd_flag'] == '1')
		$public = false;
	else
		$public = true;
	if (! $public && ! isset ( $_GET ['HTTPS'] )) {
		die ( "REDIRECT" );
	}
	if (! $public) {
		if(userDisabledForInactivity($_GET ['USERID'],$DriverIanusConnection)){
			die ( "FORBIDDEN" );
		}
		if (! UserAuthorized ( $_GET ['USERID'], $gruppi, $ret ['script_ammin'], $DriverIanusConnection )) {
			die ( "FORBIDDEN" );
		}
	}
	$SQL_SCADENZA_PWD="select case when nvl(dttm_scadenzapwd,sysdate) < sysdate then 1 else 0 end as REDIRECT from utenti
where userid=:USERID
";
	$binded='';
	$binded['USERID']=$_GET['USERID'];

$sql = new DriverIanusSql ( $DriverIanusConnection );
$sql->getRow ( $SQL_SCADENZA_PWD ,$binded);

if ($sql->row['REDIRECT']==1){
	if (
	$script!='/cgi-bin/ammin_chpwd' 
	&& !preg_match("!\.css$!", $script)
	&& !preg_match("!\.jpg$!", $script)
	&& !preg_match("!\.gif$!", $script)
	&& !preg_match("!\.png$!", $script)
	) {
		die("PASSWORD_EXPIRED");
	}
	
}
	
	die ( "OK" );
}

/*Classe connessione Oracle*/
class DriverIanusDBConnection {
	protected $resource;

	public $Error_Launched = false;

	public function __construct($user = null, $pass = null, $host = null) {
		if (! isset ( $user )) {
			$ammin_file = $_SERVER ['DOCUMENT_ROOT'];
			$ammin_file = preg_replace ( "/html/i", "config/amministrazione.cfg", $ammin_file );
			//$ammin_file.="/config/amministrazione.cfg";
			$handle = fopen ( $ammin_file, "r" );
			$contents = fread ( $handle, filesize ( $ammin_file ) );
			fclose ( $handle );
			$ammin_config_line = preg_split ( "/\n/", $contents );
			for($i = 0; $i < count ( $ammin_config_line ); $i ++) {
				if (preg_match ( "/OraUserid/i", $ammin_config_line [$i] ))
					$Ora_Userid = preg_replace ( "/OraUserid (.*)/i", "\\1", $ammin_config_line [$i] );
				if (preg_match ( "/OraPassword/i", $ammin_config_line [$i] ))
					$Ora_Pass = preg_replace ( "/OraPassword (.*)/i", "\\1", $ammin_config_line [$i] );
				if (preg_match ( "/OraInstance/i", $ammin_config_line [$i] ))
					$Ora_Host = preg_replace ( "/OraInstance (.*)/i", "\\1", $ammin_config_line [$i] );
			}

			$Ora_Userid = preg_replace ( "/\s/ ", "", $Ora_Userid );
			$Ora_Pass = preg_replace ( "/\s/", "", $Ora_Pass );
			$Ora_Host = preg_replace ( "/\s/", "", $Ora_Host );
			$user = $Ora_Userid;
			$pass = $Ora_Pass;
			$host = $Ora_Host;
			
		}
		try {
			if (!($this->resource = oci_connect ( $user, $pass, $host ))){
				throw new Exception ( "Errore connessione DB: ".$user."  ".$host." ".oci_error(), 1 );
			}
		} catch ( Exception $e ) {
			throw new Exception ( "Errore connessione DB: ".$user."  ".$host." ".oci_error(), 1 );
		}
	}

	public function commit() {
		try {
			oci_commit ( $this->resource );
			return true;
		} catch ( Exception $e ) {
			throw new Exception ( "Errore Commit", 2 );
		}
	}

	public function close() {
		oci_close ( $this->resource );
	}

	public function getConnection() {
		return $this->resource;
	}

	public function rollback() {
		try {
			oci_rollback ( $this->resource );
		} catch ( Exception $e ) {
			throw new Exception ( "Errore Rollback", 3 );
		}
	}

	function __destruct() {
		if ($this->resource) {
			try {
				oci_rollback ( $this->resource );
				oci_close ( $this->resource );
			} catch ( Exception $e ) {
				throw new Exception ( "Errore Rollback in chiusura", 4 );
			}
		}
	}

}

class DriverIanusSql {

	protected $Conn;
	protected $Stmt;
	protected $Row;
	protected $Sql_Str;
	protected $numRows;
	protected $numCols;
	protected $colsType;
	protected $colsLength;
	protected $colsName;
	protected $result;
	protected $idx;
	public $insert_errors;

	public function __construct(DriverIanusDBConnection $db) {
		$this->Conn = $db;
	}

	public function SetSql($sql_str) {
		$this->Sql_Str = $sql_str;
	}

	public function getSql() {
		return $this->Sql_Str;
	}

	public function Exec($sql_str = null, $bind_array=null) {
		if (isset ( $sql_str )) {
			$this->Sql_Str = $sql_str;
		}
		if (! isset ( $this->Sql_Str )) {
			throw new DriverIanusSqlException ( "Query non definita", 1 );
		}

		$this->Parse ();
		$this->ExecuteSelectStmt ($bind_array);
	}

	public function getRow($sql_str = null, $bind_array=null) {
		if (isset ( $sql_str ))
			$this->Exec ( $sql_str, $bind_array );
		if ($this->idx >= $this->numRows)
			return false;
		foreach ( $this->result as $key => $val ) {
			$this->Row [$key] = $val [$this->idx];
		}
		$this->idx += 1;
		return $this->Row;
	}

	function getRowByIndex($index) {
		if ($index > $this->numRows)
			return false;
		else {
			foreach ( $this->result as $key => $val ) {
				$this->Row [$key] = $this->result [$key] [$index];
			}
			return true;
		}
	}

	public function __get($name_var) {
		switch ($name_var) {
			case "Row" :
				return $this->{$name_var};
				break;
			case "row" :
				return $this->Row;
				break;
			case "numCols" :
				return $this->{$name_var};
				break;
			case "numRows" :
				return $this->{$name_var};
				break;
			case "colsName" :
				return $this->{$name_var};
				break;
			case "colsType" :
				return $this->{$name_var};
				break;
			case "colsLength" :
				return $this->{$name_var};
				break;
			case "Stmt" :
				return $this->{$name_var};
				break;
			default :
				throw new Exception ( "Errore proprietà inesistente", "10" );
				break;
		}
	}

	public function getPk($tb_name) {
		$tb_name = strtoupper ( $tb_name );
		$sql_query = "select COLUMN_NAME from user_cons_columns where constraint_name=(select constraint_name from user_constraints where TABLE_NAME='{$tb_name}' and CONSTRAINT_TYPE='P')";
		$this->Exec ( $sql_query );
		while ( $this->getRow () ) {
			$pk [$this->row ['COLUMN_NAME']] = true;
		}
		return $pk;
	}

	public function getTbStruct($tb_name, $array_assoc = null) {
		$tb_name = strtoupper ( $tb_name );
		if($tb_name=="IDP_SSO_USERS" || $tb_name=="CAS_USERS"){
			if($array_assoc ['DTTM_SCADENZAPWD'])$data_tb['DTTM_SCADENZAPWD']['VALUE']=$array_assoc ['DTTM_SCADENZAPWD'];
			$data_tb['DTTM_SCADENZAPWD']['PK']=false;
			$data_tb['DTTM_SCADENZAPWD']['ORA_TYPE']='DATE';
			$data_tb['USERID']['TYPE']=SQLT_CHR;
			$data_tb['USERID']['PK']=true;
			if($array_assoc ['USERID'])$data_tb['USERID']['VALUE']=$array_assoc ['USERID'];
			$data_tb['USERID']['ORA_TYPE']='VARCHAR2';
			$data_tb['USERID']['LEN']='200';
			$data_tb['PASSWORD']['TYPE']=SQLT_CHR;
			$data_tb['PASSWORD']['PK']=false;
			if($array_assoc ['PASSWORD'])$data_tb['PASSWORD']['VALUE']=$array_assoc ['PASSWORD'];
			$data_tb['PASSWORD']['ORA_TYPE']='VARCHAR2';
			$data_tb['PASSWORD']['LEN']='200';
			return $data_tb;
		}	
		$pk = $this->getPk ( $tb_name );
		$sql_query = "select upper(COLUMN_NAME) as column_name, DATA_TYPE, CHAR_LENGTH from USER_TAB_COLUMNS where table_name='{$tb_name}'";
		$this->Exec ( $sql_query );
		while ( $this->getRow () ) {
			if (isset ( $array_assoc )) {
				if (isset ( $array_assoc [$this->row ['COLUMN_NAME']] ))
					$data_tb [$this->row ['COLUMN_NAME']] ['VALUE'] = $array_assoc [$this->row ['COLUMN_NAME']];
			}
			if ($pk [$this->row ['COLUMN_NAME']])
				$data_tb [$this->row ['COLUMN_NAME']] ['PK'] = true;
			else
				$data_tb [$this->row ['COLUMN_NAME']] ['PK'] = false;
			switch ($this->row ['DATA_TYPE']) {
				case 'VARCHAR2' :
					$data_tb [$this->row ['COLUMN_NAME']] ['TYPE'] = SQLT_CHR;
					break;
				case 'NUMBER' :
					$data_tb [$this->row ['COLUMN_NAME']] ['LEN'] = - 1;
					$data_tb [$this->row ['COLUMN_NAME']] ['TYPE'] = SQLT_LNG;
					break;
				case 'CLOB' :
					$data_tb [$this->row ['COLUMN_NAME']] ['LEN'] = - 1;
					$data_tb [$this->row ['COLUMN_NAME']] ['TYPE'] = SQLT_CLOB;
					break;
				case 'BLOB' :
					$data_tb [$this->row ['COLUMN_NAME']] ['LEN'] = - 1;
					$data_tb [$this->row ['COLUMN_NAME']] ['TYPE'] = SQLT_BLOB;
					break;
			}
			$data_tb [$this->row ['COLUMN_NAME']] ['ORA_TYPE'] = $this->row ['DATA_TYPE'];
			if ($this->row ['DATA_TYPE'] == 'VARCHAR2')
				$data_tb [$this->row ['COLUMN_NAME']] ['LEN'] = $this->row ['CHAR_LENGTH'];
		}
		return $data_tb;
	}

	protected static function prepeare_bind($field_name, $value,$not_forced=true) {
		if ($not_forced && (preg_match ( "/^to_date/i", $value ) || preg_match ( "/sysdate/i", $value ) || preg_match ( "/nextval$/i", $value ) || preg_match ( "/currval$/i", $value ))) {
			$ret ['field_name'] = $field_name;
			$ret ['value'] = $value;
			$ret ['binded'] = false;
		} else {
			$ret ['field_name'] = $field_name;
			$ret ['value'] = ":{$field_name}";
			$ret ['binded'] = true;
		}
		return $ret;
	}

	public static function Upper($array) {
		foreach ( $array as $key => $val ) {
			if (strtoupper ( $key ) != $key) {
				$key = strtoupper ( $key );
			}
			$ret_array [$key] = $val;
		}
		return $ret_array;
	}
	public static function BuildWhereBinded($pk, $data_tb) {
		foreach ( $pk as $key => $val ) {
			$binded = DriverIanusSql::prepeare_bind ( $field_name, $valore );
			$pk_ [$key] ['BINDED'] = $binded ['binded'];
			$pk_ [$key] ['VALUE'] = $val;
			$pk_ [$key] ['TYPE'] = $data_tb [$key] ['TYPE'];
			$pk_ [$key] ['LEN'] = $data_tb [$key] ['LEN'];
			$pk_where .= "{$key}=:PK_B_{$key}_ and ";
		}
		$pk_where = rtrim ( $pk_where, " and " );
		if ($pk_where != '')
			$pk_where = "where $pk_where";
		$ret ['PK_'] = $pk_;
		$ret ['WhereString'] = $pk_where;
		return $ret;
	}

	public function Save($array_assoc, $table_name) {
		$table_name = strtoupper ( $table_name );
		$values_array = DriverIanusSql::Upper ( $array_assoc );
		$data_tb = $this->getTbStruct ( $table_name, $values_array );
		foreach ( $data_tb as $field => $val ) {
			if ($data_tb [$field] ['PK']) {
				$pk [$field] = $data_tb [$field] ['VALUE'];
			}
		}
		$retpk = DriverIanusSql::BuildWhereBinded ( $pk, $data_tb );
		$pk_where = $retpk ['WhereString'];
		$pk_ = $retpk ['PK_'];
		$this->SetSql ( "select count(*) as conto from {$table_name} $pk_where" );
		$this->Stmt = oci_parse ( $this->Conn->getConnection (), $this->Sql_Str );
		if (! $this->Stmt) {
			throw new DriverIanusSqlException ( "Errore parse oracle", "7" );
		}
		foreach ( $pk_ as $key => $val ) {
			if ($pk_ [$key] ['BINDED']) {
				if (! oci_bind_by_name ( $this->Stmt, ":PK_B_{$key}_", $pk_ [$key] ['VALUE'], $retpk ['PK_'] [$key] ['LEN'], $retpk ['PK_'] [$key] ['TYPE'] )) {
					throw new DriverIanusSqlException ( "Errore Binding Variabili", "10" );
				}
			}
		}

		if (! oci_execute ( $this->Stmt, OCI_DEFAULT )) {
			throw new DriverIanusSqlException ( "Errore Execute", "14" );
		}
		$row = oci_fetch_assoc ( $this->Stmt );
		if ($row ['CONTO'] > 0) {

			return $this->Update ( $array_assoc, $table_name, $pk );
		} else {

			return $this->Insert ( $array_assoc, $table_name );
		}
	}

	public function Update($array_assoc, $table_name, $pk) {

		$table_name = strtoupper ( $table_name );
		$values_array = DriverIanusSql::Upper ( $array_assoc );
		$data_tb = $this->getTbStruct ( $table_name, $values_array );
		//$blob = oci_new_descriptor($this->Conn->getConnection(), OCI_D_LOB);
		foreach ( $values_array as $field_name => $valore ) {
			$binded = DriverIanusSql::prepeare_bind ( $field_name, $valore );
			$this->CheckValueField ( $data_tb, $field_name );
			switch ($data_tb [$field_name] ['TYPE']) {
				case SQLT_BLOB :
					$lob_obj [$field_name] = oci_new_descriptor ( $this->Conn->getConnection (), OCI_D_LOB );
					$return_field .= ",{$field_name}";
					$return_var_bind .= ",:{$field_name}";
					$fields .= $binded ['field_name'] . "=EMPTY_BLOB(),";
					break;
				case SQLT_CLOB :
					$lob_obj [$field_name] = oci_new_descriptor ( $this->Conn->getConnection (), OCI_D_LOB );
					$return_field .= ",{$field_name}";
					$return_var_bind .= ",:{$field_name}";
					$fields .= $binded ['field_name'] . "=EMPTY_CLOB(),";
					break;
				default :
					$fields .= $binded ['field_name'] . "=" . $binded ['value'] . ",";
					break;
			}
			$data_tb [$field_name] ['BINDED'] = $binded ['binded'];
		}
		if (count ( $this->insert_errors ) > 0) {
			throw new DriverIanusSqlException ( "Errore Campi", 100 );
		}
		$fields = rtrim ( $fields, "," );
		$retpk = DriverIanusSql::BuildWhereBinded ( $pk, $data_tb );
		$pk_where = $retpk ['WhereString'];
		$pk_ = $retpk ['PK_'];
		$this->SetSql ( "update {$table_name} set {$fields} $pk_where RETURNING ROWID$return_field INTO :rid$return_var_bind" );
		$this->Parse ();
		$rowid = oci_new_descriptor ( $this->Conn->getConnection (), OCI_D_ROWID );
		if (! $rowid) {
			throw new DriverIanusSqlException ( "Errore descrittore rowid", "8" );
		}
		if (! oci_bind_by_name ( $this->Stmt, ":rid", $rowid, - 1, OCI_B_ROWID )) {
			throw new DriverIanusSqlException ( "Errore Binding Variabili", "9" );
		}
		foreach ( $pk_ as $key => $val ) {
			if ($pk_ [$key] ['BINDED']) {
				if (! oci_bind_by_name ( $this->Stmt, ":PK_B_{$key}_", $pk_ [$key] ['VALUE'], $retpk ['PK_'] [$key] ['LEN'], $retpk ['PK_'] [$key] ['TYPE'] )) {
					throw new DriverIanusSqlException ( "Errore Binding Variabili", "10" );
				}
			}
		}
		foreach ( $data_tb as $field_name => $val ) {
			if ($data_tb [$field_name] ['BINDED']) {
				switch ($data_tb [$field_name] ['TYPE']) {
					case SQLT_BLOB :
						oci_bind_by_name ( $this->Stmt, ":{$field_name}", $lob_obj [$field_name], - 1, OCI_B_BLOB );
						break;
					case SQLT_CLOB :
						oci_bind_by_name ( $this->Stmt, ":{$field_name}", $lob_obj [$field_name], - 1, OCI_B_CLOB );
						break;
					default :
						if (! oci_bind_by_name ( $this->Stmt, ":{$field_name}", $data_tb [$field_name] ['VALUE'], $data_tb [$field_name] ['LEN'], $data_tb [$field_name] ['TYPE'] )) {
							throw new DriverIanusSqlException ( "Errore Binding Variabili", "10" );
						}
						break;
				}
			}
		}
		$this->ExecuteStmt ();
		if (count ( $lob_obj ) > 0)
			foreach ( $lob_obj as $field_name => $obj ) {
				$lob_obj [$field_name]->save ( $data_tb [$field_name] ['VALUE'] );
				$lob_obj [$field_name]->free;
			}
		foreach ( $data_tb as $field_name => $value ) {
			if ($value ['PK']) {
				$pks .= $field_name . ",";
			}
		}
		$pks = rtrim ( $pks, "," );
		if ($pks == '')
			$pks = "ROWIDTOCHAR(t.ROWID) as RID";
		$this->SetSql ( "select {$pks} from {$table_name} t WHERE ROWID = :rid" );
		$this->Parse ();
		if (! oci_bind_by_name ( $this->Stmt, ":rid", $rowid, - 1, OCI_B_ROWID )) {
			throw new DriverIanusSqlException ( "Errore Binding", "13" );
		}
		$this->ExecuteStmt ();
		$row = oci_fetch_assoc ( $this->Stmt );
		oci_free_statement ( $this->Stmt );
		
		return $row;
	}

	public function CheckValueField($data_tb, $field) {
		switch ($data_tb [$field] ['ORA_TYPE']) {
			case 'VARCHAR2' :
				if (strlen ( $data_tb [$field] ['VALUE'] ) > $data_tb [$field] ['LEN']) {
					$this->insert_errors [$field] ['ERROR_SPEC'] = "Valore troppo lungo";
					$this->insert_errors [$field] ['ERROR'] = "TOO_LARGE";
					$this->insert_errors [$field] ['VALUE'] = $data_tb [$field] ['VALUE'];
				}
				break;
			case 'NUMBER' :
				if (! is_numeric ( $data_tb [$field] ['VALUE'] ) && ! preg_match ( "!nextval$!", $data_tb [$field] ['VALUE'] ) && ! preg_match ( "!currval$!", $data_tb [$field] ['VALUE'] )) {
					$this->insert_errors [$field] ['ERROR_SPEC'] = "Valore non numerico";
					$this->insert_errors [$field] ['ERROR'] = "NOT_NUM";
					$this->insert_errors [$field] ['VALUE'] = $data_tb [$field] ['VALUE'];
				}
				break;
			case 'CLOB' :
				break;
			case 'BLOB' :
				break;
		}
	}

	public function doCommand($sql_command = null, $bind_array=null) {
		if (isset ( $sql_command ))
			$this->SetSql ( $sql_command );
		$this->Parse ();
		$this->ExecuteStmt ($bind_array);
	}

	public function Insert($array_assoc, $table_name) {
		$table_name = strtoupper ( $table_name );
		$values_array = DriverIanusSql::Upper ( $array_assoc );
		$data_tb = $this->getTbStruct ( $table_name, $values_array );
		foreach ( $values_array as $field_name => $valore ) {
			if(is_array($valore)){
				if (isset($valore['bind']))$bind_type=$valore['bind'];
				else $bind_type=true;
				$data_tb[$field_name]['VALUE']=$valore=$valore['valore'];
			}
			else{
				$bind_type=true;
			}
			$binded = DriverIanusSql::prepeare_bind ( $field_name, $valore ,$bind_type);
			$this->CheckValueField ( $data_tb, $field_name );
			switch ($data_tb [$field_name] ['TYPE']) {
				case SQLT_BLOB :
					$lob_obj [$field_name] = oci_new_descriptor ( $this->Conn->getConnection (), OCI_D_LOB );
					$return_field .= ",{$field_name}";
					$return_var_bind .= ",:{$field_name}";
					$fields .= "\"" . $binded ['field_name'] . "\"" . ",";
					$vals .= "EMPTY_BLOB(),";
					break;
				case SQLT_CLOB :
					$lob_obj [$field_name] = oci_new_descriptor ( $this->Conn->getConnection (), OCI_D_LOB );
					$return_field .= ",{$field_name}";
					$return_var_bind .= ",:{$field_name}";
					$fields .= "\"" . $binded ['field_name'] . "\"" . ",";
					$vals .= "EMPTY_CLOB(),";
					break;
				default :
					$fields .= "\"" . $binded ['field_name'] . "\"" . ",";
					$vals .= $binded ['value'] . ",";
					break;
			}
			$data_tb [$field_name] ['BINDED'] = $binded ['binded'];
		}
		if (count ( $this->insert_errors ) > 0) {
			var_dump ( $this->insert_errors );
			throw new DriverIanusSqlException ( "Errore Campi", 100 );
		}
		$fields = rtrim ( $fields, "," );
		$vals = rtrim ( $vals, "," );
		$this->Sql_Str = "insert into {$table_name} ($fields) values ($vals)  RETURNING ROWID$return_field INTO :rid$return_var_bind";
		$this->Parse ();
		$rowid = oci_new_descriptor ( $this->Conn->getConnection (), OCI_D_ROWID );
		if (! $rowid) {
			throw new DriverIanusSqlException ( "Errore descrittore rowid", "8" );
		}
		if (! oci_bind_by_name ( $this->Stmt, ":rid", $rowid, - 1, OCI_B_ROWID )) {

			throw new DriverIanusSqlException ( "Errore Binding Variabili", "9" );
		}
		foreach ( $data_tb as $field_name => $val ) {
			if ($data_tb [$field_name] ['BINDED']) {
				switch ($data_tb [$field_name] ['TYPE']) {
					case SQLT_BLOB :
						oci_bind_by_name ( $this->Stmt, ":{$field_name}", $lob_obj [$field_name], - 1, OCI_B_BLOB );
						break;
					case SQLT_CLOB :
						oci_bind_by_name ( $this->Stmt, ":{$field_name}", $lob_obj [$field_name], - 1, OCI_B_CLOB );
						break;
					default :
						if (! oci_bind_by_name ( $this->Stmt, ":{$field_name}", $data_tb [$field_name] ['VALUE'], $data_tb [$field_name] ['LEN'], $data_tb [$field_name] ['TYPE'] )) {
							throw new DriverIanusSqlException ( "Errore Binding Variabili", "10" );
						}
						break;
				}

			}
		}
		$this->ExecuteStmt ();
		if (count ( $lob_obj ) > 0)
			foreach ( $lob_obj as $field_name => $obj ) {
				$lob_obj [$field_name]->save ( $data_tb [$field_name] ['VALUE'] );
				$lob_obj [$field_name]->free;
			}
		foreach ( $data_tb as $field_name => $value ) {
			if ($value ['PK']) {
				$pks .= $field_name . ",";
			}
		}
		$pks = rtrim ( $pks, "," );
		if ($pks == '')
			$pks = "ROWIDTOCHAR(t.ROWID) as RID";
		$this->SetSql ( "select {$pks} from {$table_name} t WHERE ROWID = :rid" );
		$this->Parse ();
		if (! oci_bind_by_name ( $this->Stmt, ":rid", $rowid, - 1, OCI_B_ROWID )) {
			throw new DriverIanusSqlException ( "Errore Binding", "13" );
		}
		$this->ExecuteStmt ();
		$row = oci_fetch_assoc ( $this->Stmt );
		return $row;
	}

	function tb_res() {
		$tb = "<table border=1 cellpadding=0 cellspacing=0><tr>";
		for($i = 0; $i < $this->numCols; $i ++)
			$tb .= "<th>" . $this->colsName [$i] . "</th>";
		$tb .= "</tr>";
		for($r = 0; $r < $this->numRows; $r ++) {
			$tb .= "<tr>";
			for($i = 0; $i < $this->numCols; $i ++)
				$tb .= "<td>" . $this->result [$this->colsName [$i]] [$r] . "</td>";
			$tb .= "</tr>";
		}
		$tb .= "</table>";
		return $tb;
	}

	function make_select_option($name, $selected) {
		$option = "<select name=\"$name\">\n<option value=''>&nbsp;</option>";
		$option .= $this->make_option ( $name, $values );
		$option .= "</select>";
		return $option;
	}

	function make_option($name, $values) {
		while ( $this->get_row () ) {
			$selected = "";
			if ($values [$name] == $this->Row ['VALUE'])
				$selected = "selected";
			$option .= "<option value=\"" . $this->Row ['VALUE'] . "\" $selected>" . $this->Row ['DECODE'] . "</option>\n";
		}
		return $option;
	}

	function make_check($cols, $values) {
		$i = 0;
		$check = "<table border=0 cellpadding=0 cellpsacing=0><tr>";
		while ( $this->get_row () ) {
			if ($i == $cols) {
				$i = 0;
				$check .= "</tr><tr>";
			}
			$i ++;
			$checked = "";

			if (isset ( $values [$this->Row ['VALUE']] ))
				$checked = "checked";
			$check .= "<td><input type=\"checkbox\" name=\"" . $this->Row ['VALUE'] . "\" value=\"1\" $checked><input type=\"hidden\" name=\"D_" . $this->Row ['VALUE'] . "\" value=\"" . $this->Row ['DECODE'] . "\">" . $this->row ['DECODE'] . "</td>";
		}
		$check .= "</tr></table>";
		return $check;
	}

	function Select($fields, $table_name, $wheres = null, $ords = null) {
		if ($fields == '*') {
			$campi = "*";
		} else {
			foreach ( $fields as $key => $val ) {
				$campi .= "$key as \"$val\",";
			}
		}
		if (count ( $wheres ) > 0)
			foreach ( $wheres as $key => $val ) {
				$where .= "$key =:w_c_{$key},";
			}
		if (count ( $ords ) > 0)
			foreach ( $ords as $key => $val ) {
				$order .= " {$val['FIELD']} {$val['ORD_TYPE']},";
			}
		$campi = rtrim ( $campi, "," );
		$where = rtrim ( $where, "," );
		$order = rtrim ( $order, "," );
		if ($where != '')
			$where = "where $where";
		if ($order != '')
			$order = "order by $order";
		$sql_query = "select $campi from $table_name $where $order";
		$this->SetSql ( $sql_query );
		$this->Parse ();
		if (count ( $wheres ) > 0)
			foreach ( $wheres as $key => $val ) {
				$where .= "$key =:w_c_{$key},";
			}
		if ($wheres != null)
			foreach ( $wheres as $key => $val ) {
				ocibindbyname ( $this->stmt, ":w_c_{$key}", $wheres [$key] );
			}
		$this->ExecuteSelectStmt ();
	}

	protected function Parse() {
		try {
			$this->Stmt = oci_parse ( $this->Conn->getConnection (), $this->Sql_Str );
		} catch ( Exception $e ) {
			throw new DriverIanusSqlException ( "Errore esecuzione Query", 2 );
		}
	}

	protected function ExecuteSelectStmt($bind_array=null) {
		$this->ExecuteStmt ($bind_array);
		$this->idx = 0;
		oci_fetch_all ( $this->Stmt, $this->result );
		$this->numRows = oci_num_rows ( $this->Stmt );
		$this->numCols = oci_num_fields ( $this->Stmt );
		for($i = 1; $i <= $this->numCols; $i ++) {
			$this->colsName [$i] = oci_field_name ( $this->Stmt, $i );
			$this->colsType [$i] = oci_field_type ( $this->Stmt, $i );
			$this->colsLength [$i] = oci_field_size ( $this->Stmt, $i );
		}
	}

	protected function ExecuteStmt($bind_array=null) {
		try {
			if (isset ( $bind_array ))
				foreach ( $bind_array as $key => $val ) {
				ocibindbyname ( $this->Stmt, ":{$key}", $bind_array [$key], - 1 );
				
			}
			oci_execute ( $this->Stmt, OCI_DEFAULT );
		} catch ( Exception $e ) {
			throw new DriverIanusSqlException ( "Errore esecuzione Query", 3 );
		}
	}

}

class DriverIanusSqlException extends Exception {

}

function PassiveLogoutCheck($DriverIanusConnection,$secondsBeforeLogout){
	if($secondsBeforeLogout<1) return;
	else{
		$curr_time=time();
		session_start();
		$sid=session_id();
		if($_COOKIE['SPL_'.$sid]!=""){
			$time_passed=$curr_time-$_COOKIE['SPL_'.$sid];
			if($time_passed>$secondsBeforeLogout){
				header("Location: /ShibLogOut");
				die();
			}
			else{
				setcookie('SPL_'.$sid,time());
			}
		}
		else{
			setcookie('SPL_'.$sid,time());
		}
		return;
	}
}

function buildSSOSyns($DriverIanusConnection){
	$sql_query="select count(*) as c from user_synonyms where synonym_name='IDP_SSO_USERS'";
	$sql=new DriverIanusSql($DriverIanusConnection);
	$sql->SetSql($sql_query);
	$sql->Exec();
	$sql->getRow();
	if ($sql->row['C']==0){
		$sql2=new DriverIanusSql($DriverIanusConnection);
		$sql_query="select TABLE_OWNER from user_synonyms where synonym_name='IDP_SPEC'";
		$sql2->SetSql($sql_query);
		$sql2->Exec();
		$sql2->getRow();
		$idp_db=$sql2->row['TABLE_OWNER'];
		$sql_create_syns[]="CREATE OR REPLACE SYNONYM IDP_SSO_ASSOCIATIONS FOR \"$idp_db\".\"SSO_ASSOCIATIONS\"";		
		$sql_create_syns[]="CREATE OR REPLACE SYNONYM IDP_SSO_USERS FOR \"$idp_db\".\"SSO_USERS\"";
		foreach ($sql_create_syns as $key => $val){
			$sql3=new DriverIanusSql($DriverIanusConnection);
			$sql3->SetSql($val);
			$sql3->doCommand();
		}
	}
}

function prepareForNewAmmin($DriverIanusConnection){
	$sql2=new DriverIanusSql($DriverIanusConnection);
	$sql_query="select TABLE_OWNER from user_synonyms where synonym_name='IDP_SPEC'";
	$sql2->SetSql($sql_query);
	$sql2->Exec();
	$sql2->getRow();
	$idp_db=$sql2->row['TABLE_OWNER'];
	$sql2=new DriverIanusSql($DriverIanusConnection);
	$str="grant all on UTENTI_VISTEAMMIN to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on ANA_FUNZIONI to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on ANA_GRUPPIU to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on GRUPPIU to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on ANA_UTENTI to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on UTENTI_FUNZ to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on UTENTI_VISTEAMMIN to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on ANA_GRUPPIF to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on GRUPPIF to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
	$str="grant all on UTENTI to $idp_db";
	$sql2->SetSql($str);
	$sql2->doCommand();
}

?>
