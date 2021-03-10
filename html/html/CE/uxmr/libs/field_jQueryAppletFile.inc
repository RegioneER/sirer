<?php
/**
 * @package FileAllegati
 */
include_once "libs/field_code_decode.inc";
include_once "libs/list.inc";
include_once "libs/field.inc";
include_once "libs/CMELayer.inc";
include_once "libs/document.inc";
class field_jQueryAppletFile extends field_code_decode{

	var $id_area;
	var $agg_progr;
	var $topic;
	var $thread;
	var $conn;
	var $cmeLayer;
	var $wca;
	var $applet;
	
	function __construct($xml_form, $i, $conn=null, $inputval=null, $in=null, $service=null, $errors=null){
		global $in;
		if (isset($conn)) {
			$sql_query="SELECT ID_STATO FROM {$service}WF_STATO WHERE PK_SERVICE={$in[$xml_form->config_service['PK_SERVICE']]}";
			$sql=new query($conn);
			$this->conn=$conn;
			$sql->get_row($sql_query);
			$this->stato_prat= $sql->row['ID_STATO'];
		}
		// if ($this->config_service['eQuery'] == 1) {
		// $sql_query="select STATO,EQUERY_INT from {$service}_EQ where {$xml_form->config_service['PK_SERVICE']}={$in[$xml_form->config_service['PK_SERVICE']]} and equery_int = (select max(equery_int) as equery_int from {$service}_EQ where {$xml_form->config_service['PK_SERVICE']}={$in[$xml_form->config_service['PK_SERVICE']]} )";
		// $sql->get_row($sql_query);
		// $this->stato_eq= $sql->row['STATO'];
		// }
// 		
		$in['SERVICE']=$service;

		parent::field($xml_form, $i, $conn, $inputval, $in, $service, $errors);
		if (isset($this->attributes['XMLTYPEDEFINITION']) && $this->attributes['XMLTYPEDEFINITION']!='') {
			include_once "CMELayer.inc";
			$this->CMELayer=new CMELayerWCA($conn,$configuration,$in,$xml_form->config_service);
			$this->cmeLayer="yes";
		}
		else $this->cmeLayer="no";
		if (isset($this->attributes['NO_WCA']) && $this->attributes['NO_WCA']!='') $this->wca="no";
		else $this->wca="yes";
		if (isset($this->attributes['APPLET']) && $this->attributes['APPLET']=='no') $this->appet="no";
		else $this->applet="yes";
		if ($_GET['PROGR']>1) {
			if ($_GET['VISITNUM_PROGR']>0) $agg_progr="_".$_GET['PROGR']."_".$_GET['VISITNUM_PROGR'];
			else  $agg_progr="_".$_GET['PROGR'];
		}
		if ($_POST['PROGR']>1) {
			if ($_POST['VISITNUM_PROGR']>0) $agg_progr="_".$_POST['PROGR']."_".$_POST['VISITNUM_PROGR'];
			else  $agg_progr="_".$_POST['PROGR'];
		}
		if (isset($this->xml_form->config_service['PRJ']))
		$id_tipo_ref = ($this->xml_form->config_service['PRJ'] * 100000) + $this->session_vars[$this->xml_form->config_service['PK_SERVICE']];
		else $id_tipo_ref = 100000 + $this->session_vars[$this->xml_form->config_service['PK_SERVICE']];
		$this->id_area=$id_tipo_ref;
		$this->agg_progr=$agg_progr;
		
		$thread=$this->attributes['THREAD'];
		$topic=$this->attributes['TOPIC'];
		
		if (function_exists("var_glob")){
		//$thread = preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $thread );
		//$topic= preg_replace ( "/\[(.*?)\]/e", "var_glob('\\1')", $topic );
		$topic = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $topic );
		$thread = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $thread );
		}
		$this->thread=$thread;
		$this->topic=$topic;
		if (isset($this->attributes['XMLTYPEDEFINITION']) && $this->attributes['XMLTYPEDEFINITION']!='' && isset($conn)){
			$this->store=$store=$this->CMELayer->createStore($this->service);
			$lastDoc=$this->CMELayer->queryLastVersion($store,$id_tipo_ref,$this->id.$agg_progr,true,null);
			$this->lastDocArray=$this->CMELayer->docToArray($lastDoc);
		}
	}
	
	function allinea_db(){
		parent::allinea_db();
		if (!file_exists("uploadedFiles")){
			$dir='';
			$paths=explode("/", $_SERVER['PATH_TRANSLATED']);
			for ($i=0;$i<count($paths)-1; $i++){
				$dir.=$paths[$i]."/";
			}
			$FSfolder=$dir."uploadedFiles";
			mkdir($FSfolder);
			Logger::info($FSfolder);
			exec("chmod 2777 $FSfolder -R");
		}
		if (isset($this->conn)){
		$sql=new query($this->conn);
		$sql_checkTb="select count(*) as C from user_all_tables where TABLE_NAME='FILESERVERTB'";
		$sql->get_row($sql_checkTb);
		if ($sql->row['C']==0){
			$sql_command[]="CREATE SEQUENCE  FILESERVERTB_ID  MINVALUE 1 MAXVALUE 99999999999999999999 INCREMENT BY 1 START WITH 1 NOCACHE  NOORDER  NOCYCLE";
			$sql_command[]="CREATE TABLE FILESERVERTB( 
 \"ID\" NUMBER,
 \"USERID\" VARCHAR2(100 CHAR),
 \"NOMEFILE\" VARCHAR2(4000 CHAR),
 \"SIZE\" NUMBER,
 \"CHECKSUM\" VARCHAR2(400 CHAR),
 \"INSDT\" DATE,
 \"FOLDER\" VARCHAR2(1000 CHAR),
 \"CONTENT\" BLOB,
 \"DELETED\" NUMBER
  )";
			//$sql_command[]="CREATE UNIQUE INDEX FILESERVERTB_UK1 ON FILESERVERTB (NOMEFILE, SIZE, CHECKSUM, DELETED)";
			$sql_command[]="ALTER TABLE FILESERVERTB ADD CONSTRAINT PK_FILESERVERTB PRIMARY KEY (ID)";
			$sql_command[]="CREATE OR REPLACE TRIGGER FILESERVERTB_TRG
 before insert on FILESERVERTB
 for each row
 begin
 select FILESERVERTB_ID.nextval into :new.id from dual;
 end;
";
			$sql_command[]="ALTER TRIGGER FILESERVERTB_TRG ENABLE";
			foreach ($sql_command as $key=>$command){
				$sql->ins_upd($command);
			}
		}
		}
		if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']} NUMBER";
			$ret[1]="D_{$this->attributes['VAR']} VARCHAR2(200)";
			return $ret;
		}
		else return ;
	}

	function insert_stmt(){
		global $config_service;
		global $in;
		global $done;
		if(((isset ( $_POST ['invia'] ) && $_POST ['invia'] != '')) || $_POST ['INVIOCO'] == '1' || ((isset ( $_GET ['invia'] ) && $_GET ['invia'] != '')) || $_GET ['INVIOCO'] == '1' || (isset ( $_GET ['salva'] ) && $_GET ['salva'] != '') || $_GET ['INVIOCO'] == '0' || (isset ( $_POST ['salva'] ) && $_POST ['salva'] != '') || $_POST ['INVIOCO'] == '0'){
			if (!isset($_POST['ajax_call']) || $_POST['ajax_call']!='yes') {
				$conn=$this->conn;
				$sql_query="select {$this->id} from {$this->xml_form->form['TABLE']} where esam={$_POST['ESAM']} and visitnum={$_POST['VISITNUM']} and visitnum_progr={$_POST['VISITNUM_PROGR']} and progr={$_POST['PROGR']} and {$this->config_service['PK_SERVICE']}={$in[$this->config_service['PK_SERVICE']]}";
				$sql=new query($this->conn);
				$sql->get_row($sql_query);
				$old_id=$sql->row[$this->id];
				if (!isset($done[$this->id])) $done[$this->id]=false;
				if ($old_id!=$in[$this->attributes['VAR']] && !$done[$this->id]){
					if ($this->wca=='yes'){
						if ($in[$this->attributes['VAR']."_DELETE"]!=''){
							$sql_update="update docs set tipo_doc='Trash' where id={$in[$this->attributes['VAR']."_DELETE"]}";
							$sql=new query($this->conn);
							$sql->set_sql($sql_update);
							$sql->ins_upd();
							}
						}
					if ($in[$this->attributes['VAR']]!='') {
					if ($this->wca=='yes'){
					$done[$this->id]=true;
					$sql_query="select * from FILESERVERTB where userid='{$_SERVER['REMOTE_USER']}' and ID='{$in[$this->attributes['VAR']]}'";
					$sql->get_row($sql_query);
					$nomefile=$sql->row['NOMEFILE'];
					$id_ref=$this->lastDocArray['ID_REF'];
					$sql_query_user="select nome, cognome from ana_utenti where userid='{$_SERVER['REMOTE_USER']}'";
					$sql->get_row($sql_query_user);
					$autore=$sql->row['NOME']." ".$sql->row['COGNOME'];
					$sql_query_id="select docs_id.nextval as id_doc from dual";
					$sql->get_row($sql_query_id);
					$id=$sql->row['ID_DOC'];
					$splits=explode(".", $nomefile);
					$ext=$splits[count($splits)-1];
					
					if ($id_ref=='') $id_ref=$id;
					$values['ID']=$id;
					$values['EXT']=$ext;
					$values['USERID']=$_SERVER['REMOTE_USER'];
					$values['ID_REF']=$id_ref;
					$values['TIPO_DOC']="Doc_Area";
					$values['DATA']="sysdate";
					$values['NOME_FILE']=str_replace(" ", "_", $nomefile);
					$values['AUTORE']=$autore;
					$values['PRJ']=$config_service['prj'];
					$values['ID_TIPO_REF']=$this->id_area;
					$values['KEYWORDS']=$this->id.$this->agg_progr;
					$values['TOPIC']=$this->topic;
					$values['TITOLO']=$this->thread;
					$pk='';
					$sql->insert($values, "DOCS", $pk);
					$this->conn->commit();
					}
					if (isset($config_service['FILESERVER'])){
						$strConfig=file_get_contents("/http/lib/FileServerConfig/config.properties");
						if (is_array($config_service['FILESERVER']['instance'])){
							$istance=$config_service['FILESERVER']['instance'][$config_service['service']];
						}else $istance=$config_service['FILESERVER']['instance'];
						$lines = preg_explode ( "/\n/", $strConfig );
						for($i = 0; $i < count ( $lines ); $i ++) {
							if (preg_match ( "/{$istance}\.fs\.folder/i", $lines [$i] )){
								$FSfolder = preg_replace ( "/{$istance}\.fs\.folder(.*)/i", "\\1", $lines [$i] );
								$FSfolder=str_replace("=", "", $FSfolder);
								$FSfolder=trim($FSfolder, " ");
							}
						}
						$FSfolder.="/content";
					}else {
						$dir='';
						$paths=explode("/", $_SERVER['PATH_TRANSLATED']);
						for ($i=0;$i<count($paths)-1; $i++){
							$dir.=$paths[$i]."/";
						}
						$FSfolder=$dir."tmpUploadedFiles";
						}
						if ($this->wca=='yes') $destFile="WCA/docs/Doc_Area{$id}.{$ext}";
						else $destFile="uploadedFiles/{$id}";
					$system="mv $FSfolder/{$in[$this->attributes['VAR']]} $destFile";
					exec($system);
					if ($this->wca=='yes'){
						$this->session_vars['VAR_NAME']=$this->id.$this->agg_progr;
						$this->session_vars['TOPIC']=$this->topic;
						$this->session_vars['ID']=$id;
						$this->session_vars['ID_REF']=$id_ref;
						$this->session_vars['FOLDER']=$this->id_area;
					}
				}
				}else {
					if ($this->cmeLayer=='yes'){
						$this->session_vars['VAR_NAME']=$this->id.$this->agg_progr;
						$this->session_vars['TOPIC']=$this->topic;
						$this->session_vars['ID']=$this->lastDocArray['ID'];
						$this->session_vars['ID_REF']=$this->lastDocArray['ID_REF'];
						$this->session_vars['FOLDER']=$this->lastDocArray['ID_TIPO_REF'];
					}
				}

			}
		}
		if ($this->cmeLayer=='yes'){
			$document=new xml_document_prototype ( $this->conn, $this->service, $this->config_service, $this->session_vars, $this->xml_form->uploaded_file_dir );
			global $xml_dir;
			$document->xml_document_by_file($xml_dir.'/'.$this->attributes['XMLTYPEDEFINITION']);
			if (! $document->allinea_db ()) {
				$body .= "<p align=center>";
				$body = $document->body;
				$body .= "<form method=post align=center>";

				foreach ( $in as $key => $val )
				$body .= "<input type=\"hidden\" name=\"$key\" value=\"$val\">";
				$body .= "<input type=\"submit\" name=\"CREATE_DOC\" value=\"Update DB\"></form></p>";
				echo $body;
				die();
			}
			$query = new query ( $this->conn );
			if(((isset ( $_POST ['invia'] ) && $_POST ['invia'] != '')) || $_POST ['INVIOCO'] == '1' || ((isset ( $_GET ['invia'] ) && $_GET ['invia'] != '')) || $_GET ['INVIOCO'] == '1' || (isset ( $_GET ['salva'] ) && $_GET ['salva'] != '') || $_GET ['INVIOCO'] == '0' || (isset ( $_POST ['salva'] ) && $_POST ['salva'] != '') || $_POST ['INVIOCO'] == '0'){
				$debug = 1;
				$document->query_builder ();
				$this->errors = $document->getErrors ();
				
			}
		}
		if ($this->attributes['TB']!='no'){
			$this->field_stmt[0]="{$this->attributes['VAR']}";
			$this->field_stmt[1]="D_{$this->attributes['VAR']}";
			$this->value_stmt[0]=$in[$this->attributes['VAR']];
			$this->value_stmt[1]=$in["D_".$this->attributes['VAR']];
			
		}
		return;
	}
	

	
	function gestChangeProgr($conn, $fromProgr){
		global $xml_dir;
		$sql=new query($conn);
		if (!isset($conn)) $conn=$this->conn;
		if (isset($this->attributes['XMLTYPEDEFINITION']) && $this->attributes['XMLTYPEDEFINITION']!=''){
			$document=new xml_document_prototype ( $conn, $this->service, $this->config_service, $this->session_vars, $this->xml_form->uploaded_file_dir );
			$document->xml_document_by_file($xml_dir.'/'.$this->attributes['XMLTYPEDEFINITION']);
			global $xml_dir;
			$bind['userid'] = $this->session_vars['remote_userid'];
			$bind['pk_service'] = $this->db_vars[$this->config_service['PK_SERVICE']];
			$bind['visitnum'] = $this->db_vars['VISITNUM'];
			$bind['visitnum_progr'] = $this->db_vars['VISITNUM_PROGR'];
			$bind['esam'] = $this->db_vars['ESAM'];
			$bind['progr'] = $this->db_vars['PROGR'];
			$table=$document->document['QUERYNAME'];
			
			$sql_storico = "insert into S_{$table}
					select :userid,
					sysdate,
					storico_id.nextval,
					'E',
					null,
					{$table}.*
					from $table
					where {$this->config_service['PK_SERVICE']}=:pk_service and
					VISITNUM=:visitnum and
								VISITNUM_PROGR=:visitnum_progr and 
								ESAM=:esam and 
								PROGR>:progr
								";
			$sql->ins_upd($sql_storico, $bind);
			unset ($bind['userid']);
			
			$sql_update="update $table set progr=progr-1, var_name=
					case 
						when visitnum_progr>0 then '{$this->id}_'||to_char(progr-1)||'_'||visitnum_progr
						when progr>1 then '{$this->id}_'||to_char(progr-1)
						else '{$this->id}_' end
			 		where {$this->config_service['PK_SERVICE']}=:pk_service and
					VISITNUM=:visitnum and
								VISITNUM_PROGR=:visitnum_progr and 
								ESAM=:esam and 
								PROGR>:progr";
			$sql->ins_upd($sql_update, $bind);
				
		}
		if ($this->db_vars['VISITNUM_PROGR']>0) $this->agg_progr="_".$this->db_vars['PROGR']."_".$this->db_vars['VISITNUM_PROGR'];
		else if ($this->db_vars['PROGR']>1) $this->agg_progr="_".$this->db_vars['PROGR'];
		$sql_update_docs="update docs set tipo_doc='Trash' where id_tipo_ref={$this->id_area} and keywords='".$this->id.$this->agg_progr."'";
		$sql->ins_upd($sql_update_docs);
		$bind['pk_service'] = $this->db_vars[$this->config_service['PK_SERVICE']];
		$bind['visitnum'] = $this->db_vars['VISITNUM'];
		$bind['visitnum_progr'] = $this->db_vars['VISITNUM_PROGR'];
		$bind['esam'] = $this->db_vars['ESAM'];
		$bind['progr'] = $this->db_vars['PROGR'];
		$sql_query="select {$this->id}, visitnum_progr, progr from {$this->xml_form->form['TABLE']} where {$this->config_service['PK_SERVICE']}=:pk_service and
					VISITNUM=:visitnum and
								VISITNUM_PROGR=:visitnum_progr and 
								ESAM=:esam and 
								PROGR>:progr";
		$sql->exec($sql_query, $bind);
		while ($sql->get_row()){
			if ($sql->row['VISITNUM_PROGR']>0) {
				$progr_orig=$sql->row['PROGR'];
				$progr_dest=$progr_orig-1;
				$keywords_orig=$this->id."_".$progr_orig."_".$sql->row['VISITNUM_PROGR'];
				$keywords_dest=$this->id."_".$progr_dest."_".$sql->row['VISITNUM_PROGR'];
				$sql_update_docs_[]="update docs set keywords='$keywords_dest' where keywords='$keywords_orig' and id_tipo_ref={$this->id_area} and tipo_doc='Doc_Area'";
			}
			else if ($sql->row['PROGR']>1){
				$progr_orig=$sql->row['PROGR'];
				$progr_dest=$progr_orig-1;
				$keywords_orig=$this->id."_".$progr_orig;
				if ($progr_dest>1)  $keywords_dest=$this->id."_".$progr_dest;
				else $keywords_dest=$this->id;
				$sql_update_docs_[]="update docs set keywords='$keywords_dest' where keywords='$keywords_orig' and id_tipo_ref={$this->id_area} and tipo_doc='Doc_Area'";
			}
			
		}
		foreach ($sql_update_docs_ as $key=>$val){
			$sql->ins_upd($val);
		}
		return;
	}
	
	function gestDelete($conn=null){
		global $xml_dir;
		
		
		$sql=new query($conn);
		if (!isset($conn)) $conn=$this->conn;
		if (isset($this->attributes['XMLTYPEDEFINITION']) && $this->attributes['XMLTYPEDEFINITION']!=''){
			$document=new xml_document_prototype ( $conn, $this->service, $this->config_service, $this->session_vars, $this->xml_form->uploaded_file_dir );
			$document->xml_document_by_file($xml_dir.'/'.$this->attributes['XMLTYPEDEFINITION']);
			global $xml_dir;
			$bind['userid'] = $this->session_vars['remote_userid'];
			$bind['pk_service'] = $this->db_vars[$this->config_service['PK_SERVICE']];
			$bind['visitnum'] = $this->db_vars['VISITNUM'];
			$bind['visitnum_progr'] = $this->db_vars['VISITNUM_PROGR'];
			$bind['esam'] = $this->db_vars['ESAM'];
			$bind['progr'] = $this->db_vars['PROGR'];
			$table=$document->document['QUERYNAME'];
			
			$sql_storico = "insert into S_{$table}
					select :userid,
					sysdate,
					storico_id.nextval,
					'E',
					null,
					{$table}.*
					from $table
					where {$this->config_service['PK_SERVICE']}=:pk_service and
					VISITNUM=:visitnum and
								VISITNUM_PROGR=:visitnum_progr and 
								ESAM=:esam and 
								PROGR=:progr
								";
			$sql->ins_upd($sql_storico, $bind);
			unset ($bind['userid']);
			$sql_delete="delete from $table where {$this->config_service['PK_SERVICE']}=:pk_service and
					VISITNUM=:visitnum and
								VISITNUM_PROGR=:visitnum_progr and 
								ESAM=:esam and 
								PROGR=:progr";
			$sql->ins_upd($sql_delete, $bind);
			
		}
		if ($this->db_vars['VISITNUM_PROGR']>0) $this->agg_progr="_".$this->db_vars['PROGR']."_".$this->db_vars['VISITNUM_PROGR'];
		else if ($this->db_vars['PROGR']>1) $this->agg_progr="_".$this->db_vars['PROGR'];
		$sql_update_docs="update docs set tipo_doc='Trash' where id_tipo_ref={$this->id_area} and keywords='".$this->id.$this->agg_progr."'";
		$sql->ins_upd($sql_update_docs);
		return;
	}



	function open_($value) {
		global $in;
		$inputval = $this->db_vars;
		$optgroup = false;
		$txt = $this->testo;
		$submit = "";
		if (isset ( $in [$this->attributes ['VAR']] ))
		unset ( $inputval [$this->attributes ['VAR']] );
		$disabled = "";
		if ($this->attributes ['DISABLED'] != '' && $value != '')
		$disabled = "disabled";
		$action = "";
		if ($this->attributes ['CALL_CF'] != '')
		$cf_call = "cf();";
		$this_progr = "";
		if ($this->applet=='no'){
			$input_html="
			<input type='hidden' name='{$this->id}' value='{$inputval[$this->id]}'>
		<input type='hidden' name='D_{$this->id}' value='{$inputval['D_'.$this->id]}'>".$this->printField();
			
		}
		else 
		$input_html="
		<input type='hidden' name='{$this->id}' value='{$inputval[$this->id]}'>
		<input type='hidden' name='D_{$this->id}' value='{$inputval['D_'.$this->id]}'>
		<span id='SPAN__{$this->id}'></span>
		<input type='button' value='seleziona il file' onclick=\"
		document.getElementById('SPAN__{$this->id}').innerHTML='<iframe id=\'IFRAME_{$this->id}\' scrolling=no width=\'330\' height=\'35\' frameborder=\'0\' src=\'index.php?XmrFileUpload=open&returnField={$this->id}\'></iframe>';
		\">
		<span id='SPAN_{$this->id}'><a href='WCA/download.php?id={$sql->row['LASTID']}'>{$this->db_vars['D_'.$this->id]}</a></span>
		";
		$this->input_field = $input_html . "&nbsp;" . $this->attributes ['DEF'];
		$this->input_txt = $txt;
	}
	
	function printField(){
		if ($this->attributes['EXT_ALLOWED']!=''){
			$allowsOnly=",acceptFileTypes: /(\\.|\\/)(".str_replace(",", "|", $this->attributes['EXT_ALLOWED']).")$/i";
		
		}else $allowsOnly='';
		if ($this->wca=='yes'){
			$tdAgg='<td class="size">Caricato il {%=file.date%}</td>
					<td class="error">Autore: {%=file.author%}</td>';
		}
		else $tdAgg="";
		$content='
					<link rel="stylesheet" href="libs/jQueryFileUpload/sfogliaButton.css">
					<script>
					function propagateIdAndName(field,id,name){
						if (document.forms[0].elements[field+\'_IDDOC\']){
							document.forms[0].elements[field+\'_DELETE\'].value=document.forms[0].elements[field+\'_IDDOC\'].value;
						}
						document.forms[0].elements[field].value=id;
						document.forms[0].elements[\'D_\'+field].value=name;
						}
					</script>
					 <div class="fileupload" id="'.$this->id.'_fileupload">
					 <input type="hidden" name="'.$this->id.'_DELETE">
					 <input type="hidden" name="'.$this->id.'_IDDOC" value=""/>
		            
					    <span class="btn success fileinput-button"><span>Seleziona File</span><input type="file" name="'.$this->id.'_files"></span>  
					    <span class="progressbar fileupload-progressbar fade"><div style="width:0%;"></div></span>        
				        <br/>
				        <br/>
				        <br/>
				        <table class="zebra-striped"><tbody id="'.$this->id.'_uploadedFiles" class="files"></tbody></table>
				    </div>
				    <script>
		
		var fileUploadErrors = {
		    maxFileSize: \'File troppo grande\',
		    minFileSize: \'File troppo piccolo\',
		    acceptFileTypes: \'Tipo File non accettato\',
		    emptyResult: \'Nessun risultato\'
		};
		</script>
		<script id="template-download" type="text/html">
		{% 
		if (o.files.length==0) { %}
		<tr class="template-download fade"><td colspan="3">Nessun file presente</td>
		{% }
		for (var i=0, files=o.files, l=files.length, file=files[0]; i<l; file=files[++i]) { %}
		    <tr class="template-download fade">
		        {% if (file.error) { %}
		            <td></td>
		            <td class="name">{%=file.name%}</td>
		            <td class="size">{%=o.formatFileSize(file.size)%}</td>
		            <td class="error" colspan="2"><span class="label important">Error</span> {%=fileUploadErrors[file.error] || file.error%}</td>
		        {% } else { %}
		            <td class="name">
		            {% if (file.url) { %}
		                <a href="{%=file.url%}" title="{%=file.name%}">{%=file.name%}</a>
		                 {% } else { %}
		                 {%=file.name%}
		             {% }%}
		            </td>
					'.$tdAgg.'
					<td class="error">
					<a href="#" onclick="
					{% if (file.url) { %}
					//document.getElementById(\'{%=file.field%}_uploadedFiles\').innerHTML=\'<tr><td colspan=3>Nessun file presente</td></tr>\';
		            $(\'#{%=file.field%}_uploadedFiles\').html(\'<tr><td colspan=3>Nessun file presente</td></tr>\');
		            propagateIdAndName(\'{%=file.field%}\',\'\',\'\');
		            document.forms[0].elements[\'{%=file.field%}_DELETE\'].value={%=file.id%};
		            return false;
		            {% } else { %}
		        	//document.getElementById(\'{%=file.field%}_uploadedFiles\').innerHTML=\'<tr><td colspan=3>Nessun file presente</td></tr>\';
		        	$(\'#{%=file.field%}_uploadedFiles\').html(\'<tr><td colspan=3>Nessun file presente</td></tr>\');
		            propagateIdAndName(\'{%=file.field%}\',\'\',\'\');return false;
		            {% }%}
					">elimina</a></td>
					
		        {% } %}
		     	       
		    </tr>
		{% } %}
		</script>
		<script src="libs/jQueryFileUpload/jquery.min.js"></script>
		<script src="libs/jQueryFileUpload/vendor/jquery.ui.widget.js"></script>
		<script src="libs/jQueryFileUpload/tmpl.min.js"></script>
		<script src="libs/jQueryFileUpload/jquery.iframe-transport.js"></script>
		<script src="libs/jQueryFileUpload/jquery.fileupload.js"></script>
		<script src="libs/jQueryFileUpload/jquery.fileupload-ui.js"></script>
		<script>
		var '.$this->id.';
		$(function () {
		    \'use strict\';
		
		    // Initialize the jQuery File Upload widget:
		     '.$this->id.'=$(\'#'.$this->id.'_fileupload\').fileupload();
		     '.$this->id.'=$(\'#'.$this->id.'_fileupload\').fileupload(\'option\', {
		              maxFileSize: undefined,
		              dropZone: $(\'#'.$this->id.'_fileupload\'),
		              add: function (e, data) {
		               data.formData = {XmrFileUpload: "jQueryUpload", field: "'.$this->id.'_files"};
		               data.submit();
		              },
            done: function (e, data) {
            	var that = $(this).data(\'fileupload\'),
                    template,
                    preview;
                if (data.context) {
                	
                    data.context.each(function (index) {
                        var file = ($.isArray(data.result) &&
                                data.result[index]) || {error: \'emptyResult\'};
                        if (file.error) {
                            that._adjustMaxNumberOfFiles(1);
                        }
                        that._transitionCallback(
                            $(this).removeClass(\'in\'),
                            function (node) {
                                template = that._renderDownload([file]);
                                preview = node
                                    .find(\'.preview img, .preview canvas\');
                                if (preview.length) {
                                    template.find(\'.preview img\')
                                        .prop(\'width\', preview.prop(\'width\'))
                                        .prop(\'height\', preview.prop(\'height\'));
                                }
                                template
                                    .replaceAll(node);
                                // Force reflow:
                                that._reflow = that._transition &&
                                    template[0].offsetWidth;
                                template.addClass(\'in\');
                            }
                        );
                    });
                } else {
                	if (document.getElementById(\''.$this->id.'_uploadedFiles\'))
                	$(\'#'.$this->id.'_uploadedFiles\').html(\'\');
                	propagateIdAndName(\''.$this->id.'\',data.result[0].idDoc,data.result[0].name);
                	template = that._renderDownload(data.result).appendTo(that._files);
                    // Force reflow:
                    that._reflow = that._transition && template[0].offsetWidth;
                    template.addClass(\'in\');
                }
            },
            // Callback for failed (abort or error) uploads:
            fail: function (e, data) {
                var that = $(this).data(\'fileupload\'),
                    template;
                that._adjustMaxNumberOfFiles(data.files.length);
                if (data.context) {
                    data.context.each(function (index) {
                        if (data.errorThrown !== \'abort\') {
                            var file = data.files[index];
                            file.error = file.error || data.errorThrown ||
                                true;
                            that._transitionCallback(
                                $(this).removeClass(\'in\'),
                                function (node) {
                                    template = that._renderDownload([file])
                                        .replaceAll(node);
                                    // Force reflow:
                                    that._reflow = that._transition &&
                                        template[0].offsetWidth;
                                    template.addClass(\'in\');
                                }
                            );
                        } else {
                            that._transitionCallback(
                                $(this).removeClass(\'in\'),
                                function (node) {
                                    node.remove();
                                }
                            );
                        }
                    });
                } else if (data.errorThrown !== \'abort\') {
                    that._adjustMaxNumberOfFiles(-data.files.length);
                    $(\'#'.$this->id.'_uploadedFiles\').html(\'\');
                    data.context = that._renderUpload(data.files)
                        .appendTo(that._files)
                        .data(\'data\', data);
                    // Force reflow:
                    that._reflow = that._transition && data.context[0].offsetWidth;
                    data.context.addClass(\'in\');
                }
            }
		    	 '.$allowsOnly.'
		          });
		        // Load existing files:
		        $(document).ready(function(){
		            $.getJSON(\'?XmrFileUpload=getFile&returnField='.$this->id.'&VISITNUM_PROGR_='.$_GET['VISITNUM_PROGR'].'&VISITNUM_='.$_GET['VISITNUM'].'&PROGR_='.$_GET['PROGR'].'&ESAM_='.$_GET['ESAM'].'&PK_SERVICE='.$_GET[$this->config_service['PK_SERVICE']].'&EXT_ALLOWED='.$this->attributes['EXT_ALLOWED'].'&cmeLayer='.$this->cmeLayer.'&wca='.$this->wca.'&table='.$this->xml_form->form['TABLE'].'\', function (files) {
    		            var fu = $(\'#'.$this->id.'_fileupload\').data(\'fileupload\'),
    		                template;
    		            fu._adjustMaxNumberOfFiles(-files.length);
    		            $(\'#'.$this->id.'_uploadedFiles\').html(\'\');
    		            if (files[0] && files[0].id!=\'\') document.forms[0].elements[\''.$this->id.'_IDDOC\'].value=files[0].id;
    		            template = fu._renderDownload(files).appendTo($(\'#'.$this->id.'_fileupload .files\'));
    		            // Force reflow:
    		            fu._reflow = fu._transition && template.length &&
    		                template[0].offsetWidth;
    		            template.addClass(\'in\');
		           });
		        });
		    
		});
		</script>
					';
		return $content;
	}
	
	function close_($value) {
		global $in;
		$inputval = $this->db_vars;
		$txt = $this->testo;
		if (isset ( $in [$this->attributes ['VAR']] ))
		unset ( $inputval [$this->attributes ['VAR']] );
		$disabled = "";
		if ($this->attributes ['DISABLED'] != '' && $value != '')
		$disabled = "disabled";
		$action = "";
		if ($this->attributes ['CALL_CF'] != '')
		$cf_call = "cf();";
		$this_progr = "";
		$sql_query="select max(id) as lastId from docs where tipo_doc=:tipo_doc and topic=:topic and titolo=:thread and keywords=:keywords and id_tipo_ref=:id_tipo_ref";
		$bind['tipo_doc']="Doc_Area";
		$bind['topic']=$this->topic;
		$bind['thread']=$this->thread;
		$bind['keywords']=$this->id.$this->agg_progr;
		$bind['id_tipo_ref']=$this->id_area;
		$sql=new query($this->conn);
		$sql->get_row($sql_query, $bind);
		if ($this->db_vars['D_'.$this->id]!=''){
		  if(true){
		      $input_html=$this->downloadLink();
		  }
          else
		  $input_html="<a href='WCA/download.php?id={$sql->row['LASTID']}'>{$this->db_vars['D_'.$this->id]}</a>";
        }
		else $input_html="Nessun file caricato";
		$this->input_field = $input_html . "&nbsp;" . $this->attributes ['DEF'];
		$this->input_txt = $txt;
		if (isset($this->xml_form->config_service['PRJ']))
		$id_tipo_ref = ($this->xml_form->config_service['PRJ'] * 100000) + $this->db_vars[$this->xml_form->config_service['PK_SERVICE']];
		else $id_tipo_ref = 100000 + $_GET['PK_SERVICE'];
			
		$keyword=$this->id;
		if ($this->db_vars['VISITNUM_PROGR_']>0){
			$keyword=$this->id."_".$this->db_vars['PROGR_']."_".$this->db_vars['VISITNUM_PROGR_'];
		}
		else if ($this->db_vars['PROGR']>1) $keyword=$this->id."_".$this->db_vars['PROGR'];
		if (isset($this->attributes['XMLTYPEDEFINITION']) && $this->attributes['XMLTYPEDEFINITION']!=''){
			$lastDoc=$this->CMELayer->queryLastVersion($this->xml_form->config_service['SERVICE'],$id_tipo_ref,$keyword,true);
			Logger::send($lastDoc);
			if (isset($lastDoc['ID']) && $lastDoc['ID']!=''){
				$info['name']=$lastDoc['NOME_FILE'];
				$info['date']=$lastDoc['DATA'];
				$info['author']=$lastDoc['AUTORE'];
				$info['id']=$lastDoc['ID'];
				$info['url']="WCA/download.php?id={$lastDoc['ID']}";
			}
		}else {
		$sql_query="select * from docs where id =(select max(id) as lastId from docs where tipo_doc=:tipo_doc and  keywords=:keywords and id_tipo_ref=:id_tipo_ref)";
		$bind['tipo_doc']="Doc_Area";
		$bind['keywords']=$keyword;
		$bind['id_tipo_ref']=$id_tipo_ref;
		Logger::send($sql_query);
		Logger::send($bind);
		$sql=new query($this->conn);
			if ($sql->get_row($sql_query, $bind)){
				$info['name']=$sql->row['NOME_FILE'];
				$info['date']=$sql->row['DATA'];
				$info['author']=$sql->row['AUTORE'];
				$info['url']="WCA/download.php?id={$sql->row['ID']}";
			}
		}
		if (is_array($info)){
		$this->input_field="
		File: <a href=\"{$info['url']}\" title=\"{$info['name']}\">{$info['name']}</a>
           caricato il {$info['date']} da {$info['author']} 
    ";
		}
	}

	static function showApplet($study){
		$sql_query="select password from utenti where userid='{$_SERVER['REMOTE_USER']}'";
		$sql=new query($study->conn);
		$sql->get_row($sql_query);
		$password=$sql->row['PASSWORD'];
		if (is_array($study->config_service['FILESERVER']['wsdl'])){
			$wsdlUrl=$study->config_service['FILESERVER']['wsdl'][$study->service];
		}else $wsdlUrl=$study->config_service['FILESERVER']['wsdl'];
		if (is_array($study->config_service['FILESERVER']['instance'])){
			$istance=$study->config_service['FILESERVER']['instance'][$study->service];
		}else $istance=$study->config_service['FILESERVER']['instance'];
		if ($_GET['XmrFileUpload']=='open'){
			echo '
			<html>
			<head>
			<script>
			
			function checkApplet(t){
				if (document.applets[0].isActive()) {
					document.getElementById(\'loading\').style.display=\'none\';
					clearTimeout(t);
				}
			}
			var t=setTimeout("checkApplet(t)",1000);
			</script>
		    </head>
    		<body>
    		<div id="loading" style="display:">Attendere la finestra di selezione del file...</div>
    		<APPLET id="MyApplet" CODE="it/cineca/siss/xmr/applets/XmrFileUpload.class"
				ARCHIVE="
				libs/bigFileApplet/lib/AbsoluteLayout.jar,
				libs/bigFileApplet/lib/ClientLib.jar,
				libs/bigFileApplet/lib/FastInfoset.jar,
				libs/bigFileApplet/lib/activation.jar,
				libs/bigFileApplet/lib/http.jar,
				libs/bigFileApplet/lib/jaxb-api.jar,
				libs/bigFileApplet/lib/jaxb-impl.jar,
				libs/bigFileApplet/lib/jaxb-xjc.jar,
				libs/bigFileApplet/lib/jaxws-api.jar,
				libs/bigFileApplet/lib/jaxws-rt.jar,
				libs/bigFileApplet/lib/jaxws-tools.jar,
				libs/bigFileApplet/lib/jsr250-api.jar,
				libs/bigFileApplet/lib/resolver.jar,
				libs/bigFileApplet/lib/stax-ex.jar,
				libs/bigFileApplet/lib/streambuffer.jar,
				libs/bigFileApplet/lib/woodstox.jar,
				libs/bigFileApplet/XmrFileUploadApplet.jar"
				width="330"
				height="20">
				 <param name="userid" value="'.$_SERVER['REMOTE_USER'].'" />
			     <param name="password" value="'.$password.'" />
			     <param name="appServer" value="'.$wsdlUrl.'" />
			     <param name="istance" value="'.$istance.'" />
			     <param name="returnField" value="'.$_GET['returnField'].'" />
			     <param name="returnUrl" value="https://'.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'].'" />
			</APPLET>
			</body>
			</html>';
			die();

		}
		if ($_GET['XmrFileUpload']=='success'){

			$sql_query="select max(ID) as maxid from FILESERVERTB where userid='{$_SERVER['REMOTE_USER']}' and NOMEFILE='{$_GET['nomeFile']}'";
			$sql->get_row($sql_query);
			$span=$_GET['nomeFile'];
			echo "<script>
		parent.document.forms[0].{$_GET['returnField']}.value='{$sql->row['MAXID']}';
		parent.document.forms[0].D_{$_GET['returnField']}.value='{$_GET['nomeFile']}';
		parent.document.getElementById('SPAN_{$_GET['returnField']}').innerHTML='$span';
		parent.document.getElementById('SPAN__{$_GET['returnField']}').innerHTML='';
		</script>";
			die();
		}
		if ($_GET['XmrFileUpload']=='cancel'){

			echo "<script>
				parent.document.getElementById('SPAN__{$_GET['returnField']}').innerHTML='';
				</script>";
			die();
		}
		if ($_GET['XmrFileUpload']=='error'){
			echo "<script>
							parent.document.getElementById('SPAN__{$_GET['returnField']}').innerHTML='{$_GET['error_spec']}';
							</script>";
			die();
		}
		if ($_GET['XmrFileUpload']=="downloadFile"){
			header("Content-type:*");
			ob_clean();
			$filename=$_GET['fileName'];
			$filename=str_replace(" ", "_",$filename);
			header("Content-Disposition: attachment; filename={$filename}");
			readfile("uploadedFiles/{$_GET['id']}");
			exit();
		}
		if ($_GET['XmrFileUpload']=="getFile"){
			$conn=$study->conn;
			if ($_GET['wca']=="yes"){
			if (isset($study->config_service['PRJ']))
			$id_tipo_ref = ($study->config_service['PRJ'] * 100000) + $_GET['PK_SERVICE'];
			else $id_tipo_ref = 100000 + $_GET['PK_SERVICE'];
			
			$keyword=$_GET['returnField'];
			if ($_GET['VISITNUM_PROGR_']>0){
				$keyword=$_GET['returnField']."_".$_GET['PROGR_']."_".$_GET['VISITNUM_PROGR_'];
			}
			else if ($_GET['PROGR_']>1) $keyword=$_GET['returnField']."_".$_GET['PROGR_'];
			if ($_GET['cmeLayer']=='yes'){
				$CMELayer=new CMELayerWCA($conn);
				
				$lastDoc=$CMELayer->queryLastVersion($study->config_service['SERVICE'],$id_tipo_ref,$keyword,true);
				Logger::send($lastDoc);
				if (isset($lastDoc['ID']) && $lastDoc['ID']!=''){
					$info[0]['name']=$lastDoc['NOME_FILE'];
					$info[0]['date']=$lastDoc['DATA'];
					$info[0]['author']=$lastDoc['AUTORE'];
					$info[0]['id']=$lastDoc['ID'];
					$info[0]['url']="WCA/download.php?id={$lastDoc['ID']}";
					$info[0]['field']=$_GET['returnField'];
					echo json_encode($info);
				}
				else echo "[]";
				die();
			}
			$sql_query="select * from docs where id =(select max(id) as lastId from docs where tipo_doc=:tipo_doc and  keywords=:keywords and id_tipo_ref=:id_tipo_ref)";
			$bind['tipo_doc']="Doc_Area";
			$bind['keywords']=$keyword;
			$bind['id_tipo_ref']=$id_tipo_ref;
			$sql=new query($conn);
			if ($sql->get_row($sql_query, $bind)){
    			/*header('Vary: Accept');
                if (isset($_SERVER['HTTP_ACCEPT']) &&
                    (strpos($_SERVER['HTTP_ACCEPT'], 'application/json') !== false)) {
                    header('Content-type: application/json');
                } else {*/
                    header('Content-type: text/html');
                //}
    		    $info[0]['name']=$sql->row['NOME_FILE'];
    		    $info[0]['date']=$sql->row['DATA'];
    		    $info[0]['author']=$sql->row['AUTORE'];
    		    $info[0]['id']=$sql->row['ID'];
    		    $info[0]['url']="download.php?id={$sql->row['ID']}";
    	        $info[0]['field']=$_GET['returnField'];
		    echo json_encode($info);
			}
			else echo "[]";
			} else {
				
				$sql_query="select {$_GET['returnField']}, D_{$_GET['returnField']} from {$_GET['table']} where 
				{$study->config_service['PK_SERVICE']}=:pk_service
				and ESAM=:ESAM
				and VISITNUM=:VISITNUM
				and VISITNUM_PROGR=:VISITNUM_PROGR
				and PROGR=:PROGR
				";
				$bind['pk_service']=$_GET['PK_SERVICE'];
				$bind['ESAM']=$_GET['ESAM_'];
				$bind['VISITNUM']=$_GET['VISITNUM_'];
				$bind['PROGR']=$_GET['PROGR_'];
				$bind['VISITNUM_PROGR']=$_GET['VISITNUM_PROGR_'];
				$sql=new query($conn);
				if ($sql->get_row($sql_query, $bind)){
					/*header('Vary: Accept');
                    if (isset($_SERVER['HTTP_ACCEPT']) &&
                        (strpos($_SERVER['HTTP_ACCEPT'], 'application/json') !== false)) {
                        header('Content-type: application/json');
                    } else {*/
                        header('Content-type: text/html');
                    //}
					if ($sql->row[$_GET['returnField']]=='') echo "[]";
					else {
					$info[0]['name']=$sql->row['D_'.$_GET['returnField']];
					$info[0]['url']="index.php?XmrFileUpload=downloadFile&fileName={$info[0]['name']}&ESAM={$bind['ESAM']}&VISITNUM={$bind['VISITNUM']}&PROGR={$bind['PROGR']}&VISITNUM_PROGR={$bind['VISITNUM_PROGR']}&{$study->config_service['PK_SERVICE']}={$_GET['PK_SERVICE']}&id={$sql->row[$_GET['returnField']]}";
					$info[0]['field']=$_GET['returnField'];
					$info[0]['id']=$sql->row[$_GET['returnField']];
					echo json_encode($info);
					}
				}
				else echo "[]";
				
			}
            die();
		}
	}

    function downloadLink(){
        $sql_query="select {$this->attributes['VAR']}, D_{$this->attributes['VAR']} from {$this->xml_form->form['TABLE']} where 
        {$this->config_service['PK_SERVICE']}=:pk_service
        and ESAM=:ESAM
        and VISITNUM=:VISITNUM
        and VISITNUM_PROGR=:VISITNUM_PROGR
        and PROGR=:PROGR
        ";
        $bind['pk_service']=$this->session_vars[$this->config_service['PK_SERVICE']];
        $bind['ESAM']=$this->session_vars['ESAM'];
        $bind['VISITNUM']=$this->session_vars['VISITNUM'];
        $bind['PROGR']=$this->session_vars['PROGR'];
        if($this->session_vars['VISITNUM_PROGR']!='0')$bind['VISITNUM_PROGR']=$this->session_vars['VISITNUM_PROGR'];
        else $bind['VISITNUM_PROGR']=0;
        $sql=new query($this->conn);
        //Logger::send($sql_query);
        //Logger::send($bind);
        if ($sql->get_row($sql_query, $bind)){
           
          
            if ($sql->row[$this->attributes['VAR']]=='') return "";
            else {
            $info[0]['name']=$sql->row['D_'.$this->attributes['VAR']];
            $info[0]['url']="index.php?XmrFileUpload=downloadFile&fileName={$info[0]['name']}&ESAM={$bind['ESAM']}&VISITNUM={$bind['VISITNUM']}&PROGR={$bind['PROGR']}&VISITNUM_PROGR={$bind['VISITNUM_PROGR']}&{$study->config_service['PK_SERVICE']}={$_GET['PK_SERVICE']}&id={$sql->row[$this->attributes['VAR']]}";
            $info[0]['field']=$this->attributes['VAR'];
            $info[0]['id']=$sql->row[$this->attributes['VAR']];
           
            return "<a href='{$info[0]['url']}' >{$info[0]['name']}</a>";
            }
        }
        
    }
	
	static function gestSaving($study){
		
		$conn=$study->conn;
		$config_service=$study->config_service;
		if (isset($config_service['FILESERVER'])){
			$strConfig=file_get_contents("/http/lib/FileServerConfig/config.properties");
			if (is_array($config_service['FILESERVER']['instance'])){
				$istance=$config_service['FILESERVER']['instance'][$config_service['service']];
			}else $istance=$config_service['FILESERVER']['instance'];
			$lines = preg_explode ( "/\n/", $strConfig );
			for($i = 0; $i < count ( $lines ); $i ++) {
				if (preg_match ( "/{$istance}\.fs\.folder/i", $lines [$i] )){
					$FSfolder = preg_replace ( "/{$istance}\.fs\.folder(.*)/i", "\\1", $lines [$i] );
					$FSfolder=str_replace("=", "", $FSfolder);
					$FSfolder=trim($FSfolder, " ");
				}
			}
			$FSfolder.="/content";
		}else {
			$dir='';
			$paths=explode("/", $_SERVER['PATH_TRANSLATED']);

			for ($i=0;$i<count($paths)-1; $i++){
				$dir.=$paths[$i]."/";
			}
			
			$FSfolder=$dir."tmpUploadedFiles";
			Logger::send($FSfolder);
			if (!file_exists($FSfolder)){
				mkdir($FSfolder);
				exec("chmod 2777 $FSfolder -R");
			}
		}
		$values['USERID']=$study->user->userid;
		$values['NOMEFILE']=$_FILES[$_POST['field']]['name'];
		$values['FOLDER']=$FSfolder;
		$values['INSDT']="sysdate";
		$values['ID']="FILESERVERTB_ID.nextval";
		$sql=new query($conn);
		$pk='';
		$sql->insert($values, "FILESERVERTB", $pk);
		$conn->commit();
		$sql_query="select * from FILESERVERTB where id=(select max(ID) as maxid from FILESERVERTB where userid=:userid and NOMEFILE=:nomefile)";
		$bind['userid']=$study->user->userid;
		$bind['nomefile']=$_FILES[$_POST['field']]['name'];
		$sql->get_row($sql_query, $bind);
		/*header('Vary: Accept');
        if (isset($_SERVER['HTTP_ACCEPT']) &&
            (strpos($_SERVER['HTTP_ACCEPT'], 'application/json') !== false)) {
            header('Content-type: application/json');
        } else {*/
            header('Content-type: text/html');
        //}
		$info[0]['name']=$sql->row['NOMEFILE'];
		$info[0]['date']=$sql->row['INSDT'];
		$info[0]['author']=$study->user->nome_cognome;
		
		//$system="mv $FSfolder/content/{$in[$this->attributes['VAR']]} WCA/docs/Doc_Area{$id}.{$ext}";
		//exec($system);
			
		if (is_uploaded_file($_FILES[$_POST['field']]['tmp_name'])){
			move_uploaded_file($_FILES[$_POST['field']]['tmp_name'], "$FSfolder/".$sql->row['ID']);
		}
		$size=$_FILES[$_POST['field']]['size']-0;
		$size/=1000;
		$size/=1000;
		$size=number_format($size, 2, '.', '');
		$info[0]['size']=$size;
		$info[0]['idDoc']=$sql->row['ID'];
		$info[0]['field']=preg_replace("!_files$!","",$_POST['field']);
		echo json_encode($info);
		die();
	}

}



?>
