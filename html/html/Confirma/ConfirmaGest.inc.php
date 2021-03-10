<?php

include_once "libs/db.inc";

class ConfirmaGest{

	var $servizio;
	var $tid;
	var $id;
	var $url_tomcat;

	function ConfirmaGest(){
		if (preg_match("!\.sissprep\.!",$_SERVER['HTTP_HOST']))
		$this->url_tomcat="http://appserv-siss.dev.cineca.it/ConfirmaSISS/WS?wsdl";
		else $this->url_tomcat="https://appserv-siss.cineca.it/ConfirmaSISS/WS?wsdl";
	}

	function TransactionExists($servizio, $id){
		$tid="{$servizio}_{$id}";
		if(preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
				$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_dev");
		}
		if(!preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
				$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_prod");
		}
		$sql_dati_firma="select count(*) as conto from confirma_server_transaction where tid='{$tid}'";
		$sql=new query($conn);
		$sql->get_row($sql_dati_firma);
		if ($sql->row['CONTO']==1) return true;
		else return false;		
	}
	
	function CreateTransaction($servizio, $cf, $spec, $files, $fileNames, $specs, $modes, $urls){
		$ini = ini_set("soap.wsdl_cache_enabled","1");
		try {
			$client = new SoapClient ( $this->url_tomcat );
		} catch(Exception $e) {
			die("Problemi di comunicazione con il server di Confirma.<br />{$this->url_tomcat}");
		}
		$param['servizio']=$servizio;
		$param['cf']=$cf;
		$param['spec']=$spec;
		$param['error_url']=$urls[0];
		$param['cancel_url']=$urls[1];
		$param['success_url']=$urls[2];
		$struct = new SOAPStruct($param);
		$result=$client->NewTransaction($struct);
		$tid=$result->return;
		$this->id=str_replace("{$servizio}_","", $tid);
		foreach($files as $key=>$val){
			if ($modes[$key]==2) continue;
			$fileNames[$key]=utf8_encode($fileNames[$key]);
			$param='';
			$param['TID']=$tid;
			$param['filePath']=$val;
			$param['spec']=$specs[$key];
			$param['name']=$fileNames[$key];
			$param['mode']=$modes[$key];
			$struct=new SOAPStruct($param);
			$result=$client->addDocument($param);
		}
		
		$param='';
		$param['TID']=$tid;
		$struct=new SOAPStruct($param);
		$result=$client->RegisterTransaction($struct);
		$this->servizio=$servizio;
		return $this->id;
	}

	function getApplet($servizio, $id){
		$ini = ini_set("soap.wsdl_cache_enabled","0");
		try {
			$client = new SoapClient ( $this->url_tomcat );
		} catch(Exception $e) {
			die("Problemi di comunicazione con il server di Confirma.<br />{$this->url_tomcat}");
		}
		$tid="{$servizio}_{$id}";
		$param['TID']=$tid;
		$struct=new SOAPStruct($param);
		$result=$client->getErrorUrl($param);
		$errorUrl=$result->return;
		$result=$client->getCancelUrl($param);
		$cancelUrl=$result->return;
		$result=$client->getSuccessUrl($param);
		$successUrl=$result->return;
		$url_encoded=urlencode($successUrl);
		if(preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
				$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_dev");
		}
		if(!preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
				$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_prod");
		}
		$sql_dati_firma="select spec, cf, to_char(insdt,'DD/MM/YYYY') as insdt from confirma_server_transaction where tid='{$tid}'";
		$sql=new query($conn);
		$sql->exec($sql_dati_firma);
		$sql->get_row();
		$spec=$sql->row['SPEC'];
		$cf=$sql->row['CF'];
		$insdt=$sql->row['INSDT'];
		$applet="
		<table border=0 align=center>
			<tr>
				<td colspan=3 class=int>Dettagli Firma digitale</td>
			</tr>
			<tr>
				<td class=sc4bis>{$spec}</td>
				<td class=sc4bis>Codice fiscale: {$cf}</td>
				<td class=sc4bis>{$insdt}</td>
			</tr>
			<tr>
				<td colspan=2 class=int>Documenti</td>
				<td class=int><a href=\"#\" onclick=\"
				if (document.getElementById('ConfirmaFileSpec').style.display=='none')
					document.getElementById('ConfirmaFileSpec').style.display='';
				else document.getElementById('ConfirmaFileSpec').style.display='none';
				return false;
				\">Mostra/nascondi</a></td>
			</tr>
			<tbody id='ConfirmaFileSpec' style='display:none'>
			<tr>
				<td class=sc4bis><b>File</b></td>
				<td class=sc4bis><b>Tipo di operazione</b></td>
				<td class=sc4bis><b>Dimensione</b></td>
			</tr>
			
		";
			$sql_docs="select doc_desc, length(DOC_CONTENT)/1024 as dim, sign, ts from confirma_server_docs where tid='{$tid}'";
		$sql->exec($sql_docs);
		while ($sql->get_row()){
			if ($sql->row['SIGN']==1 && $sql->row['TS']==1){
					$tipo="Firma e marcatura temporale";
			}else {
				if ($sql->row['SIGN']==1) $tipo="Firma";
				if ($sql->row['TS']==1) $tipo="Marcatura Temporale";
			}
			$dim=number_format($sql->row['DIM'],2);
			$applet.="
			<tr>
				<td class=sc4bis>{$sql->row['DOC_DESC']}</td>
				<td class=sc4bis>$tipo</td>
				<td class=sc4bis>$dim Kb</td>
			</tr>
			
			";
		}
		$applet.="
		</tbody>
		<tr>
			<td colspan=3 align=center>
		<applet code=\"cin.confirma.applet.ConfirmaAppletLoader\"
			archive=\"https://dosign.cineca.it/ConfirmaSuite/applets/ConfirmaApplet_9-1.jar,https://dosign.cineca.it/ConfirmaSuite/applets/lib/jks.jar\"
			width=\"300\" height=\"130\">
			<param name=\"TRANSACTION_ID\" value=\"{$tid}\" />
			<!--
			<param name=\"SERVICE_URL\"
				value=\"https://dosign-ssl.cineca.it/SissService/ssl-restricted/MainService\" />
			-->
			<param name=\"SERVICE_URL\"
				value=\"https://dosign.cineca.it/SissService/http-restricted/MainService\" />
			<param name=\"JAVA_5_LIBS_URL\"
				value=\"https://dosign.cineca.it/ConfirmaSuite/applets/lib/java_1-5_to_1-6_libs.jar\" />
			<!--
			<param name=\"AUTHENTICATION_METHOD\"
				value=\"SSL\" />
			-->
			<param name=\"AUTHENTICATION_METHOD\"
				value=\"USERNAME-PASSWORD\" />

			<param name=\"HTTP_USERNAME\" value=\"{$tid}\" />

			<param name=\"HTTP_PASSWORD\" value=\"{$tid}\" />
			<param name=\"TOKEN_CONFIGURATION_URL\"
				value=\"https://dosign.cineca.it/ConfirmaSuite/token-resources/configuration/SISSTokenEnvironment03.jsp\" />
			<param name=\"REDIRECT_URL\"
				value=\"https://{$_SERVER['HTTP_HOST']}/ConfirmaGestSuccess?TID={$tid}&URL={$url_encoded}\" />
			<param name=\"ERROR_URL\"
				value=\"{$errorUrl}\" />
			<param name=\"CANCEL_URL\"
				value=\"{$cancelUrl}\" />

			<param name=\"WINDOW_WIDTH\" value=\"800\" />
			<param name=\"WINDOW_HEIGHT\" value=\"600\" />
		</applet>
		</td>
		</tr>
		</table>
		";

	/*
		$applet_="
		<applet code=\"cin.confirma.applet.ConfirmaAppletLoader\"
			archive=\"http://ades.cineca.it/ConfirmaSuite/applets/ConfirmaApplet_9-0.jar,http://ades.cineca.it/ConfirmaSuite/applets/lib/jks.jar\"
			width=\"300\" height=\"130\">
			<param name=\"TRANSACTION_ID\" value=\"{$tid}\" />
			<param name=\"SERVICE_URL\"
				value=\"http://ades.cineca.it/SISSTest/http-restricted/MainService\" />
			<param name=\"JAVA_5_LIBS_URL\"
				value=\"http://ades.cineca.it:80/ConfirmaSuite/applets/lib/java_1-5_to_1-6_libs.jar\" />
			<param name=\"AUTHENTICATION_METHOD\"
				value=\"USERNAME-PASSWORD\" />

			<param name=\"HTTP_USERNAME\" value=\"{$tid}\" />

			<param name=\"HTTP_PASSWORD\" value=\"{$tid}\" />

			<param name=\"TOKEN_CONFIGURATION_URL\"
				value=\"http://ades.cineca.it:80/ConfirmaSuite/token-resources/configuration/DefaultTokenEnvironment.jsp\" />
			<param name=\"REDIRECT_URL\"
				value=\"https://{$_SERVER['HTTP_HOST']}/ConfirmaGestSuccess?TID={$tid}&URL={$url_encoded}\" />
			<param name=\"ERROR_URL\"
				value=\"{$errorUrl}\" />
			<param name=\"CANCEL_URL\"
				value=\"{$cancelUrl}\" />
			<param name=\"WINDOW_WIDTH\" value=\"800\" />
			<param name=\"WINDOW_HEIGHT\" value=\"600\" />
		</applet>";
		$myApplet="
		<applet code=\"cin.confirma.applet.ConfirmaAppletLoader\"
			archive=\"http://ades.cineca.it/ConfirmaSuite/applets/ConfirmaApplet_9-0.jar,http://ades.cineca.it/ConfirmaSuite/applets/lib/jks.jar\"
			width=\"300\" height=\"130\">
			<param name=\"TRANSACTION_ID\" value=\"{$tid}\" />
			<param name=\"SERVICE_URL\"
				value=\"http://ades.cineca.it/SISSTest/http-restricted/MainService\" />
			<param name=\"JAVA_5_LIBS_URL\"
				value=\"http://ades.cineca.it:80/ConfirmaSuite/applets/lib/java_1-5_to_1-6_libs.jar\" />
			<param name=\"AUTHENTICATION_METHOD\"
				value=\"USERNAME-PASSWORD\" />
			<param name=\"HTTP_USERNAME\"
				value=\"test\" />
			<param name=\"HTTP_PASSWORD\"
				value=\"test\" />


			<param name=\"TOKEN_CONFIGURATION_URL\"
				value=\"http://ades.cineca.it:80/ConfirmaSuite/token-resources/configuration/DefaultTokenEnvironment.jsp\" />
			<param name=\"REDIRECT_URL\"
				value=\"https://{$_SERVER['HTTP_HOST']}/ConfirmaGestSuccess?TID={$tid}&URL={$url_encoded}\" />
			<param name=\"ERROR_URL\"
				value=\"{$errorUrl}\" />
			<param name=\"CANCEL_URL\"
				value=\"{$cancelUrl}\" />

			<param name=\"WINDOW_WIDTH\" value=\"800\" />
			<param name=\"WINDOW_HEIGHT\" value=\"600\" />
		</applet>
		";
		*/
		return $applet;
	}

	function gestSuccess(){
		$tid=$_GET['TID'];
		$redirect=$_GET['URL'];
		$ini = ini_set("soap.wsdl_cache_enabled","0");
		try {
			$client = new SoapClient ( $this->url_tomcat );
		} catch(Exception $e) {
			die("Problemi di comunicazione con il server di Confirma.<br />{$this->url_tomcat}");
		}
		$param['TID']=$tid;
		$struct=new SOAPStruct($param);
		$result=$client->GestSuccess($param);
		$redirect=$redirect."&TID={$tid}";
		$redirect=urldecode($redirect);
		header("Location: $redirect");
		die();
	}

	#LUIGI: metodo get_links restituisce i link per il download dei file firmati
	function get_links($tid){
		if(preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
			$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_dev");
		}
		if(!preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
			$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_prod");
		}
		$sql=new query($conn);
		$query_conf="select * from CONFIRMA_SERVER_DOCS where tid='{$tid}' and SIGNED is not null ";
		$sql->set_sql($query_conf);
		$sql->exec();
		while($sql->get_row()){
			$stringa_visual.="<tr><td align=\"center\" bgcolor=\"#CCCCCC\" COLSPAN=\"2\"><a href=\"https://{$_SERVER['HTTP_HOST']}/ConfirmaDownload?&TID={$tid}&DOCID={$sql->row['DOC_ID']}\">{$sql->row['NOME_FILE']}</a></td></tr>";
		}
		return $stringa_visual;
	}
	
	function get_url($tid){
		if(preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
			$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_dev");
		}
		if(!preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
			$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_prod");
		}
		$sql=new query($conn);
		$query_conf="select * from CONFIRMA_SERVER_DOCS where tid='{$tid}' and SIGNED is not null ";
		$sql->set_sql($query_conf);
		$sql->exec();
		$urls=array();
		while($sql->get_row()){
			$urls[]="https://{$_SERVER['HTTP_HOST']}/ConfirmaDownload?&TID={$tid}&DOCID={$sql->row['DOC_ID']}";
		}
		return $urls;
	}

	#LUIGI: metodo get_signed restituisce i file firmati senza passare da filesystem,
	# direttamente da campi BLOB in confirma db
	function get_signed($tid,$doc_id){
		if(preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
				$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_dev");
		}
		if(!preg_match("/\.sissprep\./", $_SERVER['HTTP_HOST'])){
				$conn=new dbconn("confirma", "MRF1509!", "aifa_regolatori_prod");
		}
		
	  $query_conf="select c.SIGNED,c.NOME_FILE from CONFIRMA_SERVER_DOCS c where tid='$tid' and DOC_ID='$doc_id' ";

		$statement=OCIParse($conn->conn,$query_conf);

 		OCIExecute($statement) or die($query_conf.'<hr>');

		$arr = oci_fetch_assoc($statement);
		$result = $arr['SIGNED']->load();

		header('Content-type: application/octet-stream;');
		header("Content-disposition: attachment;filename={$arr['NOME_FILE']}");

		print $result; 
//	      header("Content-Disposition: attachment; filename={$sql->row['NOME_FILE']}");
//	      header('Content-length: '.$sql->row['LENGTH']);
//		  	header('Content-type: application/pdf');
//	      echo $sql->row['SIGNED'];
	      exit;
	}



}

class SOAPStruct {
    function SOAPStruct($a)
    {
    	foreach ($a as $key=>$val){
    		$this->{$key}=$val;
    	}
    }
}




?>