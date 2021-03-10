<?php
/**
 * @package FileAllegati
 */
if (isset($_GET['XmrFileUpload'])){

	$sql_query="select password from utenti where userid='{$_SERVER['REMOTE_USER']}'";
	$sql=new query($this->conn);
	$sql->get_row($sql_query);
	$password=$sql->row['PASSWORD'];


	if ($_GET['XmrFileUpload']=='success'){
		echo '
	 <APPLET CODE="it/cineca/siss/xmr/applets/XmrFileUpload.class"
			ARCHIVE="lib/AbsoluteLayout.jar,lib/ClientLib.jar,lib/FastInfoset.jar,lib/InternetChecker.jar,lib/activation.jar,lib/http.jar,lib/jaxb-api.jar,lib/jaxb-impl.jar,lib/jaxb-xjc.jar,lib/jaxws-api.jar,lib/jaxws-rt.jar,lib/jaxws-tools.jar,lib/jsr250-api.jar,lib/mimepull.jar,lib/resolver.jar,lib/saaj-api.jar,lib/saaj-impl.jar,lib/stax-ex.jar,lib/streambuffer.jar,lib/swing-layout-1.0.4.jar,lib/woodstox.jar,XmrFileUploadApplet.jar"
		width="340"
		height="60">
		 <param name="userid" value="'.$_SERVER['REMOTE_USER'].'" />
	     <param name="password" value="'.$password.'" />
	     <param name="appServer" value="'.$_SERVER['REMOTE_USER'].'" />
	     <param name="istance" value="'.$password.'" />
	     <param name="returnField" value="'.$_GET['returnField'].'" />
	     <param name="returnUrl" value="https://'.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'].'" />
	</APPLET>';
		die();
	}else {
		$sql_query="select max(ID) as maxid from FILESERVERTB where userid='{$_SERVER['REMOTE_USER']}' and NOMEFILE='{$_GET['nomeFile']}'";
		$sql->get_row($sql_query);
		echo "<script>
	window.opener.document.forms[0].{$_GET['returnField']}.value='{$sql->row['MAXID']}';
	window.opener.document.forms[0].D_{$_GET['returnField']}.value='{$_GET['nomeFile']}';
	window.close();	
	</script>";
		die();
	}
}

?>