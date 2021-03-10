<?
/**
 * @package FileAllegati
 */
include_once "libs/field.inc";
include_once "CMELayer.inc";
include_once "libs/document.inc";

class field_file_cme extends field {

	var $input_field_rev;
	var $id_rev;
	var $CMELayer;
	var $lastDocArray;
	var $store;
	var $id_area;

	function field_file_cme($xml_form, $i, $conn=null, $inputval=null, $in=null, $service=null, $errors=null){
		$this->CMELayer=new CMELayerWCA($conn,$configuration,$in,$xml_form->config_service);
		parent::field($xml_form, $i, $conn, $inputval, $in, $service, $errors);
		if ($_GET['PROGR']>1 || $_GET['VISITNUM_PROGR']>0) {
			if ($_GET['VISITNUM_PROGR']>0) $agg_progr="_".$_GET['PROGR']."_".$_GET['VISITNUM_PROGR'];
			else  $agg_progr="_".$_GET['PROGR'];
		}
		if ($_POST['PROGR']>1 || $_POST['VISITNUM_PROGR']>0) {
			if ($_POST['VISITNUM_PROGR']>0) $agg_progr="_".$_POST['PROGR']."_".$_POST['VISITNUM_PROGR'];
			else  $agg_progr="_".$_POST['PROGR'];
		}
		$this->inputval=$inputval;
		if ($this->inputval['PROGR']>1 || $this->inputval['VISITNUM_PROGR']>0) {
			if ($this->inputval['VISITNUM_PROGR']>0) $agg_progr="_".$this->inputval['PROGR']."_".$this->inputval['VISITNUM_PROGR'];
			else  $agg_progr="_".$this->inputval['PROGR'];
		}
		if (isset($this->xml_form->config_service['PRJ']))
		$id_tipo_ref = ($this->xml_form->config_service['PRJ'] * 100000) + $this->session_vars[$this->xml_form->config_service['PK_SERVICE']];
		else $id_tipo_ref = 100000 + $this->session_vars[$this->xml_form->config_service['PK_SERVICE']];
		$this->id_area=$id_tipo_ref;
		$this->store=$store=$this->CMELayer->createStore($this->service);
		if (isset($conn)) $lastDoc=$this->CMELayer->queryLastVersion($store,$id_tipo_ref,$this->id.$agg_progr,true);
		$this->lastDocArray=$this->CMELayer->docToArray($lastDoc);
		
	}

	function open_($value) {
		global $in;
		//global $inputval;
		
		$inputval=$this->db_vars;
		$txt = $this->testo;

		if ($this->attributes ['EXT_ALLOWED'] != '')
		$txt .= "<br><font color=red>Attenzione: si prega di allegare solo file in formato {$this->attributes['EXT_ALLOWED']}</font>";/* else
		$txt .= "<br><font color=red>Attenzione: si prega di allegare solo file in formato word, PDF e TIFF (per le immagini)</font>";*/

		$this->input_txt = $txt . ":<br />";
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;

		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];

		$topic = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $topic );
		$thread = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $thread );
		global $config_service;
		$display = '';
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1)
			$display = "none";
		}
		if ($_GET['PROGR']>1 || $_GET['VISITNUM_PROGR']>0) {
			$i=$_GET['PROGR'];
			if ($_GET['VISITNUM_PROGR']>0) $agg_progr="_".$_GET['PROGR']."_".$_GET['VISITNUM_PROGR'];
			else  $agg_progr="_".$_GET['PROGR'];
		}
		if ($_POST['PROGR']>1 || $_POST['VISITNUM_PROGR']>0) {
			$i=$_POST['PROGR'];
			if ($_POST['VISITNUM_PROGR']>0) $agg_progr="_".$_POST['PROGR']."_".$_POST['VISITNUM_PROGR'];
			else  $agg_progr="_".$_POST['PROGR'];
		}

		$txtmsg=field_file_cme::getAttachedDoc($this->conn,$this->service, $id_area, "{$this->id}{$agg_progr}",true);
//		$this->input_field = "		
//		<iframe id='{$this->id}_file_doc' style=\"display:$display;width:500px\"
//		frameborder=\"no\"
//		src=\"WCA/index.php?AF=1&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\"
//		width=\"100%\"
//		height=\"150\"
//		>Contenuto alternativo per i browser che non leggono gli iframe.
//		</iframe>
//		";
		if (preg_match("!firefox!i",$_SERVER['HTTP_USER_AGENT']) ||
			preg_match("!safari!i",$_SERVER['HTTP_USER_AGENT'])	 ||
			preg_match("!chrome!i",$_SERVER['HTTP_USER_AGENT'])) {
				$click_text="Clicca qui per selezionare il file da caricare o trascina il file in questa area";
		} else {
				$click_text="Clicca qui per selezionare il file da caricare";
		}
		$drag_text="Trascina il file in questa area per caricarlo";
		$fail_text="caricato fallito";
		$cancel_text="annulla";
		
		$this->input_field = "
		<link href=\"libs/css/fileuploader.css\" rel=\"stylesheet\" type=\"text/css\">	
		<div id=\"{$this->id}\" style=\"display:$display\">
		<div id=\"{$this->id}{$agg_progr}_TEXT\">$txtmsg</div>
		<div id=\"{$this->id}_Uploader\"></div>
		<!--script type=\"text/javascript\" src=\"libs/js/jquery/jquery.min.js\"></script-->
		<script src=\"libs/js/fileuploader.js\" type=\"text/javascript\"></script>
		<script src=\"libs/js/encoder.js\" type=\"text/javascript\"></script>
    	<script>        
        function createUploader_{$this->id}{$agg_progr}(){       
        	if($('#{$this->id}_Uploader .qq-uploader').size()==0) {          
	            var uploader = new qq.FileUploader({
	                field_id: '{$this->id}',
			element: document.getElementById('{$this->id}_Uploader'),
	                action: 'index.php?field_file_cme=Upload&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}',
	                debug: false
	            },'{$this->id}{$agg_progr}', '{$click_text}', '{$drag_text}', '{$fail_text}', '{$cancel_text}');      
            }     
        }
        
        // in your app create uploader as soon as the DOM is ready
        // don't wait for the window to load  
    </script>  
    </div> ";
		$this->check_js.="createUploader_{$this->id}{$agg_progr}();";

		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1)
				$checked = "checked"; 
			else
				$checked = "";
			//echo "<li>{$this->id} - {$inputval["{$this->id}_FD_CK"]}</li>";
			$this->input_field .= "
			<input type='checkbox' $checked name='{$this->id}_FD_CK' value=\"1\" onclick=\"
			if (this.checked) document.getElementById('{$this->id}_file_doc').style.display='none';
			else document.getElementById('{$this->id}_file_doc').style.display='';
			\">Non applicabile
			";
		}

	}

	function open_send() {
		global $insert_errors;
		global $conn;
		global $in;
		global $inputval;
		$thread = $this->attributes ['THREAD'];

		if ($in ['INVIOCO'] == 1) {
			if (isset ( $this->attributes ['CONDITION'] ) && $this->attributes ['CONDITION'] != '') {
				$conds_var = explode ( ",", $this->attributes ['CONDITION'] );
				$conds_val = explode ( ",", $this->attributes ['CONDITION_VALUE'] );
				$this->condition_passed = true;
				foreach ( $conds_var as $key => $var ) {
					$val = $conds_val [$key];
					if ($in [$var] != $val) {
						$this->condition_passed = false;
					}
				}
			}

			global $config_service;
			if ($this->condition_passed && isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
				if ($inputval ["{$this->id}_FD_CK"] == '1' || $in ["{$this->id}_FD_CK"] == '1'){
					$this->validata=true;
					return;
				}
			}

			$id_tipo_ref = 100000 + $in [$this->xml_form->config_service['PK_SERVICE']];
			if (isset($this->xml_form->config_service['PRJ']))
			$id_tipo_ref = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
			if ($_GET['PROGR']>1 || $_GET['VISITNUM_PROGR']>0) {
				if ($_GET['VISITNUM_PROGR']>0) $agg_progr="_".$_GET['PROGR']."_".$_GET['VISITNUM_PROGR'];
				else  $agg_progr="_".$_GET['PROGR'];
		}
			if ($_POST['PROGR']>1 || $_POST['VISITNUM_PROGR']>0) {
				if ($_POST['VISITNUM_PROGR']>0) $agg_progr="_".$_POST['PROGR']."_".$_POST['VISITNUM_PROGR'];
				else  $agg_progr="_".$_POST['PROGR'];
		}
			$store=$this->CMELayer->createStore($this->service);
			$lastDoc=$this->CMELayer->queryLastVersion($store,$id_tipo_ref,$this->id.$agg_progr);
			$this->lastDocArray=$this->CMELayer->docToArray($lastDoc);
		if (!$lastDoc && $this->condition_passed){
				$insert_errors [$this->id] = "Allegare file $thread";
				$this->validata=false;
				$this->errors[$this->id] = "Allegare file $thread";
			}
		} 
		
	}

	function open_save() {
		global $insert_errors;
		global $conn;
		global $in;
		$thread = $this->attributes ['THREAD'];
		if ($in ['INVIOCO'] == 0) {
			if (isset ( $this->attributes ['CONDITION'] ) && $this->attributes ['CONDITION'] != '') {
				$conds_var = explode ( ",", $this->attributes ['CONDITION'] );
				$conds_val = explode ( ",", $this->attributes ['CONDITION_VALUE'] );
				$this->condition_passed = true;
				foreach ( $conds_var as $key => $var ) {
					$val = $conds_val [$key];
					if ($in [$var] != $val) {
						$this->condition_passed = false;
					}
				}
			}
			$id_tipo_ref = 100000 + $in [$this->xml_form->config_service['PK_SERVICE']];
			if (isset($this->xml_form->config_service['PRJ']))
			$id_tipo_ref = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
			if ($_GET['PROGR']>1 || $_GET['VISITNUM_PROGR']>0) {
				if ($_GET['VISITNUM_PROGR']>0) $agg_progr="_".$_GET['PROGR']."_".$_GET['VISITNUM_PROGR'];
				else  $agg_progr="_".$_GET['PROGR'];
		}
			if ($_POST['PROGR']>1 || $_POST['VISITNUM_PROGR']>0) {
				if ($_POST['VISITNUM_PROGR']>0) $agg_progr="_".$_POST['PROGR']."_".$_POST['VISITNUM_PROGR'];
				else  $agg_progr="_".$_POST['PROGR'];
		}
        if ($this->session_vars['PROGR']>1 || $this->session_vars['VISITNUM_PROGR']>0) {
                if ($this->session_vars['VISITNUM_PROGR']>0) $agg_progr="_".$this->session_vars['PROGR']."_".$this->session_vars['VISITNUM_PROGR'];
                else  $agg_progr="_".$this->session_vars['PROGR'];
        }
			$store=$this->CMELayer->createStore($this->service);
			$lastDoc=$this->CMELayer->queryLastVersion($store,$id_tipo_ref,$this->id.$agg_progr);

		if (!$lastDoc && $this->condition_passed){
				$insert_errors [$this->id] = "Allegare file $thread";
				$this->validata=false;
				$this->errors[$this->id] = "Allegare file $thread";
			}
		}
	}

	function close_($value,$showInt=false) {
		global $in;
		global $inputval;
		$txt = $this->testo;

		$this->input_txt = $txt . ":<br>";
		//$id_area = $in ['ID_PRAT'] + 100000;
		//nuova tecnica per mettere suffisso alle id dei doc WCA
		if (isset($this->xml_form->config_service['PRJ']))
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (100000*$this->xml_form->config_service['PRJ']);
		else $id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + 100000;
		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];
		$topic = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $topic );
		$thread = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $thread );
		global $config_service;
		$display = '';
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1) {
				$this->input_field = "<img src=\"/images/checkedcheck.gif\">Non applicabile";
				return;
			}
		}
		if ($_GET['PROGR']>1 || $_GET['VISITNUM_PROGR']>0) {
			if ($_GET['VISITNUM_PROGR']>0) $agg_progr="_".$_GET['PROGR']."_".$_GET['VISITNUM_PROGR'];
			else  $agg_progr="_".$_GET['PROGR'];
		}
		if ($_POST['PROGR']>1 || $_POST['VISITNUM_PROGR']>0) {
			if ($_POST['VISITNUM_PROGR']>0) $agg_progr="_".$_POST['PROGR']."_".$_POST['VISITNUM_PROGR'];
			else  $agg_progr="_".$_POST['PROGR'];
		}
		if ($this->inputval['PROGR']>1 || $this->inputval['VISITNUM_PROGR']>0) {
			if ($this->inputval['VISITNUM_PROGR']>0) $agg_progr="_".$this->inputval['PROGR']."_".$this->inputval['VISITNUM_PROGR'];
			else  $agg_progr="_".$this->inputval['PROGR'];
		}
		$this->input_field = "
		<iframe
		frameborder=\"no\"
		src=\"WCA/index.php?AF=2&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\"
		width=\"100%\"
		height=\"90\"
		>Vedi File Allegato
		</iframe>
		";
		$this->input_field=field_file_cme::getAttachedDoc($this->conn,$this->service, $id_area, "{$this->id}{$agg_progr}",$edit,$showInt);
		//Logger::send('FINE CLOSE_');
	}

	function allinea_db() {

		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			$ret [0] = "{$this->id}_FD_CK NUMBER";
			$ret [1] = "{$this->id} NUMBER";
			return $ret;
		} else{
				$ret [0] = "{$this->id} NUMBER";
			return $ret;
			}
	}

	function insert_stmt() {
		if ($this->session_vars ['USER_TIP'] == 'DM' && ($this->attributes['NO_DM_CHANGE']!='' || $this->attributes['CRYPTO']!='')){
   		return;
  	}
		global $config_service;
		global $in;
		global $config_service;
		
		
		$this->session_vars['VAR_NAME']=$this->attributes['VAR'];
		$this->session_vars['TOPIC']=$this->attributes['TOPIC'];
		$this->session_vars['ID']=$this->lastDocArray['ID'];
		$this->session_vars['ID_REF']=$this->lastDocArray['ID_REF'];
		$this->session_vars['FOLDER']=$this->lastDocArray['ID_TIPO_REF'];
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
		//		global $config_service;
		$this->field_stmt [0] = "{$this->id}";
		$this->value_stmt [0] = $this->lastDocArray['ID'];
        if($this->attributes['AUTO_APPROVE']=='yes'){
            CMELayerWCA::approveDocument($this->value_stmt [0],$this->conn);
        }
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			$this->field_stmt [1] = "{$this->id}_FD_CK";
			$this->value_stmt [1] = "{$in["{$this->id}_FD_CK"]}";
		} else
		return;
	}

	function all_in($var, $i, $row, $this_closed) {
		$this->CMELayer=new CMELayerWCA($this->conn,$configuration,$this->session_vars,$this->xml_form->config_service);
        
        
        if ($i>1 || $this->session_vars['VISITNUM_PROGR']>0) {
            if ($this->session_vars['VISITNUM_PROGR']>0) $agg_progr="_".$i."_".$this->session_vars['VISITNUM_PROGR'];
            else  $agg_progr="_".$i;
        }
        if (isset($this->xml_form->config_service['PRJ']))
        $id_tipo_ref = ($this->xml_form->config_service['PRJ'] * 100000) + $this->session_vars[$this->xml_form->config_service['PK_SERVICE']];
        else $id_tipo_ref = 100000 + $this->session_vars[$this->xml_form->config_service['PK_SERVICE']];
        $this->id_area=$id_tipo_ref;
        $this->store=$store=$this->CMELayer->createStore($this->service);
         $lastDoc=$this->CMELayer->queryLastVersion($store,$id_tipo_ref,$this->id.$agg_progr,true);
        
        
		$ret['body']="
		<td class=sc4bis align=center>
		<a id=\"{$keyword}_link\" href=\"".(CMELayerWCA::downloadHref($lastDoc['ID']))."\">
		{$lastDoc['NOME_FILE']}
		</a>
		</td>
		";
		return $ret;
	}

	function gestDelete($conn=null){
		global $xml_dir;
		//Logger::send(__CLASS__." - gestDelete");
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
			//Logger::send($sql_storico);
			//Logger::send($bind);
			$sql->ins_upd($sql_storico, $bind);
			unset ($bind['userid']);
			$sql_delete="delete from $table where {$this->config_service['PK_SERVICE']}=:pk_service and
					VISITNUM=:visitnum and
								VISITNUM_PROGR=:visitnum_progr and 
								ESAM=:esam and 
								PROGR=:progr";
			$sql->ins_upd($sql_delete, $bind);
			//Logger::send($sql_delete);
			//Logger::send($bind);
			
		}
		if ($this->db_vars['VISITNUM_PROGR']>0) $this->agg_progr="_".$this->db_vars['PROGR']."_".$this->db_vars['VISITNUM_PROGR'];
		else if ($this->db_vars['PROGR']>1) $this->agg_progr="_".$this->db_vars['PROGR'];
		$sql_update_docs="update docs set tipo_doc='Trash' where id_tipo_ref={$this->id_area} and keywords='".$this->id.$this->agg_progr."'";
		$sql->ins_upd($sql_update_docs);
		//Logger::send($sql_update_docs);
		
		//Logger::send("FINE: ".__CLASS__." - gestDelete");
		return;
	}
	function gestChangeProgr($conn, $fromProgr){
		global $xml_dir;
		//Logger::send(__CLASS__." - gestChangeProgr");
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
			//Logger::send($sql_storico);
			//Logger::send($bind);
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
			//Logger::send($sql_update);
			//Logger::send($bind);
			$sql->ins_upd($sql_update, $bind);
				
		}
		if ($this->db_vars['VISITNUM_PROGR']>0) $this->agg_progr="_".$this->db_vars['PROGR']."_".$this->db_vars['VISITNUM_PROGR'];
		else if ($this->db_vars['PROGR']>1) $this->agg_progr="_".$this->db_vars['PROGR'];
		$sql_update_docs="update docs set tipo_doc='Trash' where id_tipo_ref={$this->id_area} and keywords='".$this->id.$this->agg_progr."'";
		//Logger::send($sql_update_docs);
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
		//Logger::send($sql_query);
		//Logger::send($bind);
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
			//Logger::send($val);
			$sql->ins_upd($val);
		}
		//Logger::send("FINE: ".__CLASS__." - gestChangeProgr");
		return;
	}
	/*
	static function S_all_in($field, $m_p, $xml_form){
		$tr_agg = "<td class=int>&nbsp;</td>";
		return $tr_agg;
	}*/
		static function S_all_in($field, $m_p, $xml_form){
		if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes'){
			$tr_agg = "<td class=int>&nbsp;</td>";
		  return $tr_agg;}
		  else return;
		}

	static function getAttachedDoc($conn,$store, $id_area, $keywords, $edit=true,$showInt=false){
	     $session=new query($conn);
         $session->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DD/MM/YYYY HH24:MI:SS'");
         $session->ins_upd();
		/*if(!isset($lastDoc)){
			if(!isset($CMELayer)){
		$CMELayer=new CMELayerWCA($conn);
				$lastDoc=$CMELayer->queryLastVersion($store,$id_area,$keywords,$edit);
			}
			else{
				$lastDoc=$CMELayer->queryLastVersion($store,$id_area,$keywords,$edit);
			}
		}*/
		$CMELayer=new CMELayerWCA($conn);
		if($showInt) $lastDoc=$CMELayer->queryLastVersion($store,$id_area,$keywords,true);
		else $lastDoc=$CMELayer->queryLastVersion($store,$id_area,$keywords,$edit);

		if($lastDoc){
			$lastDocArray=$CMELayer->docToArray($lastDoc);
			$txtmsg="E' stato allegato il file <a target=\"_new\" href=\"".(CMELayerWCA::downloadHref($lastDocArray['ID']))."\">{$lastDocArray['NOME_FILE']}</a> in data: <b>{$lastDocArray['DATA']}</b>";
			/*Decommentare per riavere il link all'eliminazione del documento
             * 
             if($edit)
			$txtmsg.="(<a href=\"#\" onclick=\"
		$.ajax({
		  url: 'index.php?field_file_cme&DeleteIdDoc={$lastDocArray['ID']}',
		  dataType: 'json',
		  beforeSend: function(){
		  	$('#{$keywords}_TEXT').html('Eliminazione file in corso...');
		  },
		  success: function(data){
		  	if (data.success) {
		  		$('#'+data.div).html(Encoder.htmlDecode(data.txtmsg));
			}else {
				$('#{$keywords}_TEXT').html('Errore eliminazione file!!!');
			}
		  },
		  error: function(){
		  	$('#{$keywords}_TEXT').html('Errore eliminazione file!!!');
		  }
		});
		return false;
		\">elimina</a>)";*/
		}
		else $txtmsg='Nessun documento presente';
        $session=new query($conn);
        $session->set_sql("ALTER SESSION SET NLS_DATE_FORMAT = 'DDMMYYYY'");
        $session->ins_upd();
		return $txtmsg;
	}



}


/**
 * Handle file uploads via XMLHttpRequest
 */
class qqUploadedFileXhr {
	/**
     * Save the file to the specified path
     * @return boolean TRUE on success
     */
	function save($path) {
		$input = fopen("php://input", "r");
		$temp = tmpfile();
		$realSize = stream_copy_to_stream($input, $temp);
		fclose($input);

		if ($realSize != $this->getSize()){
			return false;
		}

		$target = fopen($path, "w");
		fseek($temp, 0, SEEK_SET);
		stream_copy_to_stream($temp, $target);
		fclose($target);

		return true;
	}
	function getName() {
		return $_GET['qqfile'];
	}
	function getSize() {
		if (isset($_SERVER["CONTENT_LENGTH"])){
			return (int)$_SERVER["CONTENT_LENGTH"];
		} else {
			throw new Exception('Getting content length is not supported.');
		}
	}
}

/**
 * Handle file uploads via regular form post (uses the $_FILES array)
 */
class qqUploadedFileForm {
	/**
     * Save the file to the specified path
     * @return boolean TRUE on success
     */
	function save($path) {
		if(!move_uploaded_file($_FILES['qqfile']['tmp_name'], $path)){
			return false;
		}
		return true;
	}
	function getName() {
		return $_FILES['qqfile']['name'];
	}
	function getSize() {
		return $_FILES['qqfile']['size'];
	}
}

class qqFileUploader {
	private $allowedExtensions = array();
	private $sizeLimit = 10485760;
	private $file;

	function __construct(array $allowedExtensions = array(), $sizeLimit = 10485760){
		$allowedExtensions = array_map("strtolower", $allowedExtensions);

		$this->allowedExtensions = $allowedExtensions;
		$this->sizeLimit = $sizeLimit;

		$this->checkServerSettings();

		if (isset($_GET['qqfile'])) {
			$this->file = new qqUploadedFileXhr();
		} elseif (isset($_FILES['qqfile'])) {
			$this->file = new qqUploadedFileForm();
		} else {
			$this->file = false;
		}
	}

	private function checkServerSettings(){
		$postSize = $this->toBytes(ini_get('post_max_size'));
		$uploadSize = $this->toBytes(ini_get('upload_max_filesize'));

		if ($postSize < $this->sizeLimit || $uploadSize < $this->sizeLimit){
			$size = max(1, $this->sizeLimit / 1024 / 1024) . 'M';
			die("{'error':'increase post_max_size and upload_max_filesize to $size'}");
		}
	}

	private function toBytes($str){
		$val = trim($str);
		$last = strtolower($str[strlen($str)-1]);
		switch($last) {
			case 'g': $val *= 1024;
			case 'm': $val *= 1024;
			case 'k': $val *= 1024;
		}
		return $val;
	}

	/**
     * Returns array('success'=>true) or array('error'=>'error message')
     */
	function handleUpload($uploadDirectory, $replaceOldFile = TRUE){
		if (!is_writable($uploadDirectory)){
			return array('error' => "Server error. Upload directory isn't writable.");
		}

		if (!$this->file){
			return array('error' => 'No files were uploaded.');
		}

		$size = $this->file->getSize();

		if ($size == 0) {
			return array('error' => 'File is empty');
		}

		//if ($size > $this->sizeLimit) {
		//	return array('error' => 'File is too large');
		//}

		$pathinfo = pathinfo($this->file->getName());
		$filename = $pathinfo['filename'];
		//$filename = md5(uniqid());
		$ext = $pathinfo['extension'];

		if($this->allowedExtensions && !in_array(strtolower($ext), $this->allowedExtensions)){
			$these = implode(', ', $this->allowedExtensions);
			return array('error' => 'File has an invalid extension, it should be one of '. $these . '.');
		}

		if(!$replaceOldFile){
			/// don't overwrite previous files that were uploaded
			while (file_exists($uploadDirectory . $filename . '.' . $ext)) {
				$filename .= rand(10, 99);
			}
		}

		if ($this->file->save($uploadDirectory . $filename . '.' . $ext)){
			return array('success'=>true);
		} else {
			return array('error'=> 'Could not save uploaded file.' .
			'The upload was cancelled, or server error encountered');
		}

	}
}

class field_file_cme_gest{
	function Controller(){
		if (isset($_GET['DeleteIdDoc'])){
			include_once "WCA/wom_config.inc";
			$conn=new dbconn();
			$CMELayer=new CMELayerWCA($conn);
			$CMELayer->delete($_GET['DeleteIdDoc']);

		}

		if (isset($_GET['id_area'])){
			global $service;
			$conn=new dbconn();
			$CMELayer=new CMELayerWCA($conn);
			$CMELayer->save($service,$_GET['id_area'],$_GET['keywords']);
		}
	}
}




?>
