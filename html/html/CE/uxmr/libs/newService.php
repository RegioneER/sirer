<?

$config_service ['SERVICE'] = "";
$config_service ['VISITNUM_PROGR'] = 1;
$config_service ['Menu_paziente'] = '';
$config_service ['Lista_schede'] = '';
$config_service ['Patients_list'] = '';
$config_service ['Torna_lista_schede'] = '';
$config_service ['from_service_email'] = "";
$config_service ['error_email_to'] = "";
include_once ("libs/db_wl.inc");

$conn = new dbconn ( );

$filetxt = file_get_contents ( "template.htm" );

$newsrv = new newService ( $conn );
$body = $newsrv->Controller ();

$filetxt = str_replace ( "<!--body-->", $body, $filetxt );
die ( $filetxt );

class newService {
	
	var $service;
	var $service_root;
	var $conn;
	
	function newService($conn) {
		$this->conn = $conn;
		$sql_create_table ['XMR_SERVICE'] = "
create table XMR_SERVICE
(
  SERVICE_ROOT   varchar2(200),
  SERVICE_SUFFIX varchar2(10),
  DESCR          varchar2(4000)
)
";
		$sql_create_idx ['XMR_SERVICE'] = "
alter table XMR_SERVICE
  add constraint PK_XMR_SERVICE primary key (SERVICE_ROOT, SERVICE_SUFFIX)
";
		
		$sql_query_service = "select count(*) as conto from user_tables where table_name='XMR_SERVICE'";
		
		$sql = new query ( $conn );
		$sql->set_sql ( $sql_query_service );
		$sql->exec ();//non richiede binding
		$sql->get_row ();
		if ($sql->row ['CONTO'] == 0) {
			$sql->set_sql ( $sql_create_table ['XMR_SERVICE'] );
			$sql->ins_upd ();//non richiede binding
			$sql->set_sql ( $sql_create_idx ['XMR_SERVICE'] );
			$sql->ins_upd ();//non richiede binding
		}
	
	}
	
	function Controller() {
		if (isset ( $_POST ['STEP'] )) {
			switch ($_POST ['STEP']) {
				case '1' :
					$values ['SERVICE_SUFFIX'] = $_POST ['SERVICE_SUFFIX'];
					$values ['SERVICE_ROOT'] = $_POST ['SERVICE_ROOT'];
					$values ['DESCR'] = $_POST ['DESCR'];
					$table = "XMR_SERVICE";
					$sql = new query ( $this->conn );
					$pk = '';
					$sql->insert ( $values, $table, $pk );
					$this->conn->commit ();
					break;
			}
		}
		if (! isset ( $_GET ['SERVICE'] ))
			$body = $this->noServicePage ();
		else {
			$body = $this->ServicePage ( $_GET ['SERVICE'] );
		}
		return $body;
	}
	
	function ServicePage($service) {
		
		$body = "<p align=center class=titolo1>Servizio $service</p>";
		$sql_query = "select * from XMR_SERVICE where SERVICE_SUFFIX=:service";
		$sql = new query ( $this->conn );
		//$sql->set_sql ( $sql_query );
		$bind_service['SERVICE']=$service;
		$sql->exec ($sql_query,$bind_service);//binded
		$sql->get_row ();
		$this->service = $sql->row ['SERVICE_SUFFIX'];
		$this->service_root = $sql->row ['SERVICE_ROOT'];
		$folder_service = $_SERVER ['DOCUMENT_ROOT'] . $this->service_root . "/" . $this->service;
		if (isset ( $_GET ['CREATE'] )) {
			switch ($_GET ['CREATE']) {
				case 'Folder' :
					$this->CreatFolders();
					break;
				case 'config_param':
					
					break;
			}
		}
		$exist ['Folder'] = is_dir ( $folder_service );
		$exist ['visit_exams'] = is_file ( $folder_service . "/xml/visite_exams.xml" );
		$exist ['config_param'] = is_file ( $folder_service . "/config_param.inc" );
		
		$body = "
		<table border=0 cellpadding=0 cellspacing=2 width=95% align=center>
			<tr>
				<td class=int>Cartella Servizio</td>
				<td class=int>" . $this->existCheck ( $exist, 'Folder' ) . "</td>
			</tr>
			<tr>
				<td class=int>File di configurazione</td>
				<td class=int>" . $this->existCheck ( $exist, 'config_param' ) . "</td>
			</tr>
			<tr>
				<td class=int>Struttura XMR</td>
				<td class=int>" . $this->existCheck ( $exist, 'visit_exams' ) . "</td>
			</tr>
		</table>		
		";
		return $body;
	}
	
	function createConfigParam(){
		$service="";
	}
	
	function existCheck($exist, $param_name) {
		if ($exist [$param_name]) {
			return "<img src=\"images/check_v.gif\"></td><td class=int>";
		} else
			return "<img src=\"images/check_r.gif\"></td><td class=int><a href=\"newService.php?SERVICE={$this->service}&CREATE=$param_name\">clicca qui per creare l'oggetto</a>";
	}
	
	function CreatFolders() {
		$folder_service = $_SERVER ['DOCUMENT_ROOT'] . $this->service_root . "/" . $this->service;
		
		if (! mkdir ( $folder_service ))
			$body .= "Errore creazione cartella $folder_service";
		if (! mkdir ( "{$folder_service}/xml" ))
			$body .= "Errore creazione cartella {$folder_service}/xml";
		$chmod = "chmod 2770 $folder_service";
		exec ( $chmod );
		$chmod = "chmod 2770 {$folder_service}/xml";
		exec ( $chmod );
		$service_root_dir = $_SERVER ['DOCUMENT_ROOT'] . $this->service_root . "/";
		$link_libs = "ln -s /http/lib/XMR/v2.0/libs $folder_service/libs";
		exec ( $link_libs );
		$link_images = "ln -s {$service_root_dir}images $folder_service/images";
		exec ( $link_images );
		$cp_template = "cp {$service_root_dir}template.htm $folder_service/.";
		exec ( $cp_template );
		$cp_css = "cp {$service_root_dir}*.css $folder_service/.";
		exec ( $cp_css );
		$cp_index = "cp /http/lib/XMR/v2.0/index.php $folder_service/.";
		exec ( $cp_index );
		$cp_study = "cp /http/lib/XMR/v2.0/study.inc.php $folder_service/.";
		exec ( $cp_study );
		$chmod_all = "chmod g+w $folder_service/ -R";
		exec ( $chmod_all );
		refresh ( "newService.php?SERVICE=$this->service" );
	}
	
	function noServicePage() {
		$sql_query = "select * from XMR_SERVICE order by SERVICE_SUFFIX asc";
		$sql = new query ( $this->conn );
		$sql->set_sql ( $sql_query );
		$sql->exec ();//non richiede binding
		while ( $sql->get_row () ) {
			$srv_rows .= "
					<tr>
						<td class=sc4bis valign=top>
						<a href=\"newService.php?SERVICE={$sql->row['SERVICE_SUFFIX']}\">{$sql->row['SERVICE_SUFFIX']}</a></td>
						<td class=sc4bis valign=top>{$sql->row['SERVICE_ROOT']}</td>
						<td class=sc4bis valign=top>{$sql->row['DESCR']}</td>
					</tr>
				";
		}
		if ($srv_rows == '') {
			$srv_rows = "<tr><td class=sc4bis colspan=3 align=center>Non sono definiti servizi XMR</td></tr>";
		}
		
		$body = "
				<p class=titolo>	
					Servizi XMR
				</p>
				<table border=0 cellpadding=0 cellspacing=2 width=95% align=center>
					<tr>
						<td class=int>Suffisso</td>
						<td class=int>Root</td>
						<td class=int>Descrizione</td>
					</tr>
					$srv_rows
				</table>
				<a href=\"#\" onclick=\"show_hide('new_service');return false;\">Crea nuovo servizio</a>
				<div id='new_service' style=\"display:none\">
				" . $this->formStep1 () . "
				</div>
			";
		return $body;
	}
	
	function formStep1() {
		$root_service = rtrim ( $_SERVER ['SCRIPT_NAME'], "/newService.php" );
		$body = "
			<form method='POST'>
						<table border=0 cellpadding=0 cellspacing=2 width=95% align=center>
							<tr>
								<td valign=top class=destra>
								<b>Suffisso del servizio:</b>
								</td>
								<td valign=top class=input>
								<input type='text' name='SERVICE_SUFFIX'>								
								</td>
							</tr>
							<tr>
								<td valign=top class=destra>
									<b>Sottocartella del servizio:</b><br>
									(ad es.: (www.nomeservizio.it/<b>[sottocartella_sistema]</b>)
								</td>
								<td valign=top class=input>
									<input type='text' name='SERVICE_ROOT' value='$root_service' size='80'>	
								</td>
							</tr>
							<tr>
								<td valign=top class=destra>
									<b>Descrizione:</b>
								</td>
								<td valign=top class=input>
									<textarea name='DESCR' rows='10' cols='80'></textarea>
								</td>
							</tr>
							<tr>
								<td colspan=2 valign=top align=center>
									<input type='hidden' name='STEP' value='1'>
									<input type='submit' value='prosegui'>
									<input type='reset' value='annulla' onclick=\"show_hide('new_service');\">
								</td>
							</tr>
						</table>
					</form>
		";
		return $body;
	}

}

function error_page($user, $error, $error_spec) {
	global $filetxt;
	global $in;
	global $SRV;
	global $log_conn;
	global $service;
	global $remote_userid;
	global $session_number;
	global $insert_errors;
	global $config_service;
	
	#echo "<hr>$session_number<br/>$service<br/>".$this->str."<hr>";
	$today = date ( "j/m/Y, H:m:s" );
	$php_debug = debug_backtrace ();
	$php_debug = var_export ( $php_debug, true );
	$php_debug = "<table><tr><th>PHP DEBUG</th></tr><tr><td>$php_debug</td></tr></table>";
	$i_e_debug = var_export ( $insert_errors, true );
	$i_e_debug = "<table><tr><th>I.E. DEBUG</th></tr><tr><td>$i_e_debug</td></tr></table>";
	
	if (is_array ( $error_spec ))
		foreach ( $error_spec as $key => $val )
			$spec .= "\n $key : $val";
	mail ( $config_service ['error_email_to'], "Errore[" . $in ['remote_userid'] . "]", "$today\n $error \n Specifiche errore: \n" . $spec, "From: ERROR_" . $service . "@{$_SERVER['SERVER_NAME']}\r\n$php_debug \r\n$i_e_debug" );
	$body = "<p align=center><font size=4><b>Si � verificato un errore</b></p><br><br>$error_spec<br>$error";
	$filetxt = preg_replace ( "/<!--body-->/", $body, $filetxt );
	die ( $filetxt );
}

function refresh($link) {
	die ( "<html><head><meta http-equiv=\"refresh\" content=\"0; url=$link\"></head></html>" );
}

?>