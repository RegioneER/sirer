<?

include_once "libs/field.inc";

define("AREA_OFFSET", 10000000);

class field_file_doc extends field {

	var $input_field_rev;
	var $id_rev;

	function open_($value) {
		global $in;
//		global $inputval;

		$inputval=$this->db_vars;
		$txt = $this->testo;

		if ($this->attributes ['EXT_ALLOWED'] != ''){
			///$txt .= "<br><font color=red>Attenzione: si prega di allegare solo file in formato {$this->attributes['EXT_ALLOWED']}</font>";
		}else{
			///$txt .= "<br><font color=red>Attenzione: si prega di allegare solo file in formato word, PDF e TIFF (per le immagini)</font>";
		}
		//$txt .= "<br>CENTER: ".$in['CENTER'];
		//$txt .= "<br>PK_SERV: ".$in [$this->xml_form->config_service['PK_SERVICE']];
		if (isset($this->xml_form->config_service['PRJ'])){
			//$id_area = $in ['CENTER'] + (10*$this->xml_form->config_service['PRJ']);
			$id_area = 1;
		}else{
			//$id_area = $in ['CENTER'] + 1000;
			$id_area = 1;
		}
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (AREA_OFFSET*$id_area);
		//$txt .= "<br>AREA: ".$id_area;
		$this->input_txt = $txt . ":<br>";
		
		//if (isset($this->xml_form->config_service['PRJ']))
		//$id_area = $in [$this->xml_form->config_service['CENTER']] + (10*$this->xml_form->config_service['PRJ']);
		//else $id_area = $in [$this->xml_form->config_service['CENTER']] + 10;
		
		
		//$txt .= "<br>".print_r($this->xml_form->config_service);
		
		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];

		$topic = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $topic);
		$thread = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $thread);
		global $config_service;
		$display = '';
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1)
				$display = "none";
		}
		$vprogr = "_0";
		if (is_numeric($_GET['VISITNUM_PROGR'])){
			$vprogr = "_".($_GET['VISITNUM_PROGR']+0);
		}
		if (is_numeric($_POST['VISITNUM_PROGR'])){
			$vprogr = "_".($_POST['VISITNUM_PROGR']+0);
		}
		if ($_GET['PROGR']>1) {
			$i=$_GET['PROGR'];
			$agg_progr="_".$_GET['PROGR'];
		}
		if ($_POST['PROGR']>1) {
			$i=$_POST['PROGR'];
			$agg_progr="_".$_POST['PROGR'];
		}
		
		$txtmsg=field_file_doc::getAttachedDoc($this->conn, $id_area, "{$this->id}{$vprogr}{$agg_progr}");
		
		/*
		$this->input_field = "
		
		<iframe id='{$this->id}_file_doc' style=\"display:$display;width:500px\"
		frameborder=\"no\"
		src=\"WCA/index.php?AF=1&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\"
		width=\"100%\"
		height=\"150\"
		>Contenuto alternativo per i browser che non leggono gli iframe.
		</iframe>
		";
		*/
		
		if (preg_match("!firefox!i",$_SERVER['HTTP_USER_AGENT']) ||
			preg_match("!safari!i",$_SERVER['HTTP_USER_AGENT']) ||
			preg_match("!chrome!i",$_SERVER['HTTP_USER_AGENT'])){
			$click_text="Clicca qui per selezionare il file da caricare o trascina il file in questa area";
		}else{
			$click_text="Clicca qui per selezionare il file da caricare";
		}
		$drag_text="Trascina il file in questa area per caricarlo";
		$fail_text="caricato fallito";
		$cancel_text="annulla";
		$this->input_field = "
		<link href=\"mylibs/css/fileuploader.css\" rel=\"stylesheet\" type=\"text/css\">	
		<div id=\"{$this->id}\" style=\"display:$display\">
		<div id=\"{$this->id}{$vprogr}{$agg_progr}_TEXT\">$txtmsg</div>
		<div id=\"{$this->id}_Uploader\"></div>
		<script type=\"text/javascript\" src=\"libs/js/jquery/jquery.min.js\"></script>
		<script src=\"mylibs/js/fileuploader.js\" type=\"text/javascript\"></script>
		<script src=\"mylibs/js/encoder.js\" type=\"text/javascript\"></script>
    <script>        
        function createUploader_{$this->id}{$vprogr}{$agg_progr}(){            
            var uploader = new qq.FileUploader({
                element: document.getElementById('{$this->id}_Uploader'),
                action: 'index.php?field_file_doc=Upload&id_area=$id_area&thread={$thread}&keywords={$this->id}{$vprogr}{$agg_progr}&topic={$topic}',
                debug: false
            },'{$this->id}{$vprogr}{$agg_progr}', '{$click_text}', '{$drag_text}', '{$fail_text}', '{$cancel_text}');           
        }
        
        // in your app create uploader as soon as the DOM is ready
        // don't wait for the window to load  
    </script>  
    </div> ";
    $this->check_js.="
    createUploader_{$this->id}{$vprogr}{$agg_progr}();";
		/*
		if ($i>1){
			$keyword="{$this->id}_{$i}";
		$where_agg=" and keywords='{$this->id}_{$i}'";
		$agg_progr="_{$i}";
		}else {
			$keyword="{$this->id}";
			$where_agg=" and keywords='{$this->id}'";
		}
		
		
		$sql_query="
		select * from docs where id=(
		select max(id) from docs
		where id_tipo_ref=$id_area and topic='$topic' and titolo = '$thread'
		$where_agg
		)";
		$sql=new query($this->xml_form->conn);
		$sql->get_row($sql_query);
		$this->input_field="
		<a id=\"{$keyword}_link\" href=\"WCA/download.php?id={$sql->row['ID']}\">{$sql->row['NOME_FILE']}</a>
		<br/><div id=\"{$keyword}_new\" style=\"z-index:2;position:absolute;background-color:white;border:2px solid;display:none;\"></div>
		<input type='button' onclick=\"
		if (document.getElementById('{$keyword}_new')){
					var top=posBottom()-(pageHeight()/2)-40;
					left=(pageWidth()/2)-100;
					document.getElementById('{$keyword}_new').style.left=''+left+'px';
					document.getElementById('{$keyword}_new').style.top=''+top+'px';
					document.getElementById('{$keyword}_new').style.display='';
					document.getElementById('{$keyword}_new').innerHTML='<iframe id=\'{$keyword}_file_doc\' style=\'display:$display;width:400px\' frameborder=\'no\' src=\'WCA/index.php?AF=1&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\' width=\'100%\' height=\'120\'>Contenuto alternativo per i browser che non leggono gli iframe.</iframe>';
		}
		\" value=\"Allega file\">
		";
*/
		/*
		$this->input_field="
		<span id='{$this->id}_file_id'></span>
		<a href=\"#\" onclick=\"
		ajax_file_call('ajaxUpload','id_tipo_ref=$id_area&titolo=$thread&keywords={$this->id}&topic={$topic}');
		return false;\">Carica nuovo file</a>
		";
*/
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1)
				$checked = "checked"; else
				$checked = "";
				//echo "<li>{$this->id} - {$inputval["{$this->id}_FD_CK"]}</li>";
			$this->input_field .= "
			<input type='checkbox' $checked name='{$this->id}_FD_CK' value=\"1\" onclick=\"
			if (this.checked) document.getElementById('{$this->id}_file_doc').style.display='none';
			else document.getElementById('{$this->id}_file_doc').style.display='';
		\">Non applicabile
		";
		}
		//$this->validata = true;
	}

	function open_send() {
		global $insert_errors;
		global $conn;
		global $in;
		global $inputval;
		$thread = $this->attributes ['THREAD'];
		//echo("INVIOCO: {$in ['INVIOCO']}");
		//die("OPENSEND");
		if ($in ['INVIOCO'] == 1) {
			//die("STO QUI");
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

			//echo "VALIDO!";
			//echo "<br/>$this->condition_passed<br/>";
			//echo "<br/>{$config_service ['FILE_DOC_NA']}<br/>";
			//die();
			/*
			global $config_service;
			if ($this->condition_passed && isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
				if ($inputval ["{$this->id}_FD_CK"] == '1' || $in ["{$this->id}_FD_CK"] == '1'){
					die("QUAA");
					$this->validata=true;
					return;
				}
			}
			*/
			$this->validata=true;
			//$id_tipo_ref = AREA_OFFSET + $in [$this->xml_form->config_service['PK_SERVICE']];
			if (isset($this->xml_form->config_service['PRJ'])){
				//$id_area = $in ['CENTER'] + (10*$this->xml_form->config_service['PRJ']);
				$id_area = 1;
			}else{
				//$id_area = $in ['CENTER'] + 1000;
				$id_area = 1;
			}
			$id_tipo_ref = $in [$this->xml_form->config_service['PK_SERVICE']] + (AREA_OFFSET*$id_area);

			$vprogr = "_0";
			if (is_numeric($_GET['VISITNUM_PROGR'])) $vprogr = "_".($_GET['VISITNUM_PROGR']+0);
			if (is_numeric($_POST['VISITNUM_PROGR'])) $vprogr = "_".($_POST['VISITNUM_PROGR']+0);
			
			if ($_GET['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
			if ($_POST['PROGR']>1) $agg_progr="_".$_POST['PROGR'];
			$sql_query = "select count(*) as conto from docs where KEYWORDS='{$this->id}{$vprogr}{$agg_progr}' and id_tipo_ref=$id_tipo_ref";
			//echo $sql_query;
			$sql = new query ( $conn );
			$sql->set_sql ( $sql_query );
			$sql->exec ();
			$sql->get_row ();
			if ($sql->row ['CONTO'] == 0 && $this->condition_passed) {
				//echo "STO QUA?";
				$this->validata = false;
				$insert_errors [$this->id] = "Allegare file $thread";
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
			if (isset($this->xml_form->config_service['PRJ'])){
				//$id_area = $in ['CENTER'] + (10*$this->xml_form->config_service['PRJ']);
				$id_area = 1;
			}else{
				//$id_area = $in ['CENTER'] + 1000;
				$id_area = 1;
			}
			$id_tipo_ref = $in [$this->xml_form->config_service['PK_SERVICE']] + (AREA_OFFSET*$id_area);
			$vprogr = "_0";
			if (is_numeric($_GET['VISITNUM_PROGR'])) $vprogr = "_".($_GET['VISITNUM_PROGR']+0);
			if (is_numeric($_POST['VISITNUM_PROGR'])) $vprogr = "_".($_POST['VISITNUM_PROGR']+0);
			if ($_GET['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
			if ($_POST['PROGR']>1) $agg_progr="_".$_POST['PROGR'];
			$sql_query = "select count(*) as conto from docs where KEYWORDS='{$this->id}{$vprogr}{$agg_progr}' and id_tipo_ref=$id_tipo_ref";
			$sql = new query ( $conn );
			$sql->set_sql ( $sql_query );
			$sql->exec ();
			$sql->get_row ();
			if ($sql->row ['CONTO'] == 0 && $this->condition_passed)
				$insert_errors [$this->id] = "Allegare file $thread";
		}
	}

	function close_($value) {
		global $in;
		global $inputval;
		$txt = $this->testo;

		$this->input_txt = $txt . ":<br>";
		//$id_area = $in ['ID_PRAT'] + AREA_OFFSET;
		//nuova tecnica per mettere suffisso alle id dei doc WCA
		if (isset($this->xml_form->config_service['PRJ'])){
			//$id_area = $in ['CENTER'] + (10*$this->xml_form->config_service['PRJ']);
			$id_area = 1;
		}else{
			//$id_area = $in ['CENTER'] + 1000;
			$id_area = 1;
		}
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (AREA_OFFSET*$id_area);
		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];
		$topic = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $topic);
		$thread = preg_replace_callback ( "/\[(.*?)\]/", function($matches){return var_glob($matches[1]);}, $thread);
		global $config_service;
		$display = '';
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			if ($inputval ["{$this->id}_FD_CK"] == 1) {
				$this->input_field = "<img src=\"/images/checkedcheck.gif\">Non applicabile";
				return;
			}
		}
		$vprogr = "_0";
		if (is_numeric($_GET['VISITNUM_PROGR'])) $vprogr = "_".($_GET['VISITNUM_PROGR']+0);
		if (is_numeric($_POST['VISITNUM_PROGR'])) $vprogr = "_".($_POST['VISITNUM_PROGR']+0);
		if ($_GET['PROGR']>1) $agg_progr="_".$_GET['PROGR'];
		if ($_POST['PROGR']>1) $agg_progr="_".$_POST['PROGR'];
		$this->input_field = "
		<iframe
		frameborder=\"no\"
		src=\"WCA/index.php?AF=2&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$vprogr}{$agg_progr}&topic={$topic}\"
		width=\"100%\"
		height=\"90\"
		>Vedi File Allegato
		</iframe>
		";
		$this->input_field=field_file_doc::getAttachedDoc($this->conn, $id_area, "{$this->id}{$vprogr}{$agg_progr}",false);

//		$sql_query = "select * from docs where id_tipo_ref=$id_area and approved is not null and keywords='{$this->id}{$agg_progr}'";
//		echo $sql_query."<br>";
//		$sql = new query ( $this->conn );
//		$sql->set_sql ( $sql_query );
//		$sql->exec ();
//		$sql->get_row ();
//		if($sql->numrows>0) {
//			$this->input_field_rev = "
//			<iframe
//			frameborder=\"no\"
//			src=\"WCA/index.php?AF=2&tab=3&id_area=$id_area&thread={$thread}&id={$sql->row['ID']}{$agg_progr}&topic={$topic}\"
//			width=\"100%\"
//			height=\"90\"
//			>Vedi File Allegato
//			</iframe>
//			";
//		}
	}
	
	function allinea_db() {
		global $config_service;
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			$ret [0] = "{$this->id}_FD_CK NUMBER";
			return $ret;
		} else
			return;
	}

	function insert_stmt() {
		if ($this->session_vars ['USER_TIP'] == 'DM' && ($this->attributes['NO_DM_CHANGE']!='' || $this->attributes['CRYPTO']!='')){
   		return;
  	}
		global $config_service;
		global $in;
		if (isset ( $config_service ['FILE_DOC_NA'] ) && $config_service ['FILE_DOC_NA']) {
			$this->field_stmt [0] = "{$this->id}_FD_CK";
			$this->value_stmt [0] = "{$in["{$this->id}_FD_CK"]}";
		} else
			return;
	}
	
	function all_in($var, $i, $row, $this_closed) {
		global $in;
		//print_r($in);
		//print_r($row);
		if (isset($this->xml_form->config_service['PRJ'])){
			//$id_area = $in ['CENTER'] + (10*$this->xml_form->config_service['PRJ']);
			$id_area = 1;
		}else{
			//$id_area = $in ['CENTER'] + 1000;
			$id_area = 1;
		}
		$id_area = $in [$this->xml_form->config_service['PK_SERVICE']] + (AREA_OFFSET*$id_area);
		
		$topic = $this->attributes ['TOPIC'];
		$thread = $this->attributes ['THREAD'];
		//Conversione campi [] in topic e thread
		foreach ($in as $k=>$v){
			$topic = str_replace("[{$k}]","$v",$topic);
			$thread = str_replace("[{$k}]","$v",$thread);
		}
		$vprogr = "_0";
		if (is_numeric($in['VISITNUM_PROGR'])) $vprogr = "_".($in['VISITNUM_PROGR']+0);
		if ($i>1){
			$keyword="{$this->id}{$vprogr}_{$i}";
			$where_agg=" and keywords='{$this->id}{$vprogr}_{$i}'";
			//$agg_progr="{$vprogr}_{$i}";
		}else {
			$keyword="{$this->id}{$vprogr}";
			$where_agg=" and keywords='{$this->id}{$vprogr}'";
		}
		$sql_query="
		select * from docs where id=(
		select max(id) from docs
		where id_tipo_ref=$id_area and topic='$topic' and titolo = '$thread' and tipo_doc= 'Doc_Area'
		$where_agg
		)";
		//echo $sql_query."<br/>";
		$sql=new query($this->xml_form->conn);
		$ret['body']="
			<td class=\"sc4bis\" align=\"center\" >
			";
		if ($sql->get_row($sql_query))
		{
			$ret['body'].="<a id=\"{$keyword}_link\" href=\"/WCA/download.php?id={$sql->row['ID']}\"><img src=\"images/pdf.png\" border=\"0\" /><br/>&nbsp;{$sql->row['NOME_FILE']}</a>";
			//$ret['body'].="PIPPO";
			/*
			$ret['body'].="
				<br/><div id=\"{$keyword}_new\" style=\"z-index:2;position:absolute;background-color:white;border:2px solid;display:none;\"></div>
				<input type='button' onclick=\"
				if (document.getElementById('{$keyword}_new')){
							var top=posBottom()-(pageHeight()/2)-40;
							left=(pageWidth()/2)-100;
							document.getElementById('{$keyword}_new').style.left=''+left+'px';
							document.getElementById('{$keyword}_new').style.top=''+top+'px';
							document.getElementById('{$keyword}_new').style.display='';
							document.getElementById('{$keyword}_new').innerHTML='<iframe id=\'{$keyword}_file_doc\' style=\'display:$display;width:400px\' frameborder=\'no\' src=\'WCA/index.php?AF=1&tab=3&id_area=$id_area&thread={$thread}&keywords={$this->id}{$agg_progr}&topic={$topic}\' width=\'100%\' height=\'120\'>Contenuto alternativo per i browser che non leggono gli iframe.</iframe>';
				}
				\" value=\"Allega file\">&nbsp;&nbsp;
				<a title=\"visualizza storico\" target=\"_blank\" href=\"WCA/index.php?tab=3&id_area=$id_area&id_doc={$sql->row['ID']}&id_ref={$sql->row['ID_REF']}\"><img src=\"../images/copia.gif\"></a>
			";
			*/
		}else{
			$ret['body'].="Nessun allegato";
		}
		$ret['body'].="
		</td>
		";
		return $ret;
	}
	
	static function S_all_in($field, $m_p, $xml_form){
		$tr_agg = "<td class=int>&nbsp;</td>";
		return $tr_agg;
	}
	
	static function getAttachedDoc($conn, $id_area, $keywords, $edit=true){
	$sql=new query($conn);
	//if ($edit)
	$sql_query="select * from docs where tipo_doc='Doc_Area' and id_tipo_ref='$id_area' and keywords='{$keywords}' and id = 
		(select max(id) from docs where tipo_doc='Doc_Area' and id_tipo_ref='$id_area' and keywords='{$keywords}')";
	//else $sql_query="select * from docs where tipo_doc='Doc_Area' and id_tipo_ref='$id_area' and keywords='{$keywords}' and id = (select max(id) from docs where tipo_doc='Doc_Area' and id_tipo_ref='$id_area' and keywords='{$keywords}' and approved=1)";
	//echo "<li>$sql_query</li>";
	if ($sql->get_row($sql_query)){
		$data = $sql->row['DATA'];
		if (strpos($data,"/") === FALSE){
			$data = substr($data,0,2)."/".substr($data,2,2)."/".substr($data,4);
		}
		//echo "//$data";
		//$data = str_replace("/","-",$data);
		$txtmsg="E' stato allegato il file <a target=\"_new\" href=\"WCA/download.php?id={$sql->row['ID']}\">{$sql->row['NOME_FILE']}</a> in data: <b>{$data}</b>";
		if($edit)
		$txtmsg.="(<a href=\"#\" onclick=\"
		$.ajax({
		  url: 'index.php?field_file_doc&DeleteIdDoc={$sql->row['ID']}',
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
		\">elimina</a>)";
	}
	else $txtmsg='Nessun documento presente';
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
    function handleUpload($uploadDirectory, $fname = false, $replaceOldFile = FALSE){
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
        
        if ($size > $this->sizeLimit) {
            return array('error' => 'File is too large');
        }
        
        $pathinfo = pathinfo($this->file->getName());
        if (!$fname){
        	$fname = $pathinfo['filename'];
        	$ext = $pathinfo['extension'];
        }else{
        	$ext = substr(strrpos($fname,"."));
        }
        //$filename = md5(uniqid());
		//$filename = false;
        if($this->allowedExtensions && !in_array(strtolower($ext), $this->allowedExtensions)){
            $these = implode(', ', $this->allowedExtensions);
            return array('error' => 'File has an invalid extension, it should be one of '. $these . '.');
        }
        
        if(!$replaceOldFile){
            /// don't overwrite previous files that were uploaded
            while (file_exists($uploadDirectory . $fname . '.' . $ext)) {
                $fname .= rand(10, 99);
            }
        }
        
        //if ($this->file->save($uploadDirectory . $fname . '.' . $ext)){
        if ($this->file->save($uploadDirectory . $fname)){
            return array('success'=>true);
        } else {
            return array('error'=> 'Could not save uploaded file.' .
                'The upload was cancelled, or server error encountered');
        }
        
    }    
}

class field_file_doc_gest{
	function Controller(){
		if (isset($_GET['DeleteIdDoc'])){
			include_once "WCA/wom_config.inc";
			$conn=new dbconn();
			$sql=new query($conn);
			$sql_query="select id_tipo_ref, keywords from docs where id='{$_GET['DeleteIdDoc']}'";
			$sql->get_row($sql_query);
			$id_area=$sql->row['ID_TIPO_REF'];
			$keywords=$sql->row['KEYWORDS'];
			$result['success']=true;
			$result['div']=$keywords."_TEXT";
			$result['txtmsg']="ciao";
			$sql_update="update docs set tipo_doc='Trash', delete_date=sysdate, delete_user='{$_SERVER['REMOTE_USER']}' where id='{$_GET['DeleteIdDoc']}'";
			$sql->set_sql($sql_update);
			$sql->ins_upd();
			$conn->commit();
			$result['success']=true;
			$result['div']=$keywords."_TEXT";
			$result['txtmsg']=field_file_doc::getAttachedDoc($conn, $id_area, $keywords);
			echo htmlspecialchars(json_encode($result), ENT_NOQUOTES);
			die();
		}
		
		if (isset($_GET['id_area'])){
		
			// list of valid extensions, ex. array("jpeg", "xml", "bmp")
			$allowedExtensions = array();
			// max file size in bytes
			$sizeLimit = 10 * 1024 * 1024;
			
			include_once "WCA/wom_config.inc";
			
			$splits=explode(",", $testo_config['doc_ext_list']);
			foreach ($splits as $key=>$val){
				
				if ($val!='') $ExtAllowed[strtolower($val)]=true;
			}
			
			if (!isset($_GET['qqfile']))
			$fileName=$_FILES['qqfile']['name'];
			else $fileName=$_GET['qqfile'];
			$splits=explode(".", $fileName);
			$ext=$splits[count($splits)-1];
			$ext=strtolower($ext);
			if (count($ExtAllowed)){
				if ($ExtAllowed[".".$ext]){
					
				}else {
					die('{error: '.json_encode("Estensione \"$ext\" non supportata").'}');
				}
			}
			//die('{success: true, fileName: '.json_encode($fileName).', keywords: '.json_encode($_GET['keywords']).', txtmsg: '.json_encode($txtmsg).'}');
			
			$conn=new dbconn();
			$sql=new query($conn);
			
			$sql_query="select distinct id_ref as id_ref from docs where titolo='{$_GET['thread']}' and id_tipo_ref='{$_GET['id_area']}'";
			$sql->exec($sql_query);
			if ($sql->get_row($sql_query)) {
				$id_ref=$sql->row['ID_REF'];
			}
			
			while ($sql->get_row()){
				print_r($sql->row);
			}
			
			$id_area=$_GET['id_area'];
			
			$sql_query_user="select nome, cognome from ana_utenti where userid='{$_SERVER['REMOTE_USER']}'";
			$sql->get_row($sql_query_user);
			$autore=$sql->row['NOME']." ".$sql->row['COGNOME'];
			
			
			$sql_query_id="select docs_id.nextval as id_doc from dual";
			$sql->get_row($sql_query_id);
			$id=$sql->row['ID_DOC'];
			if ($id_ref=='') $id_ref=$id;
			
			$values['ID']=$id;
			$values['EXT']=$ext;
			$values['USERID']=$_SERVER['REMOTE_USER'];
			$values['ID_REF']=$id_ref;
			$values['TIPO_DOC']="Doc_Area";
			$values['DATA']="sysdate";
			$values['NOME_FILE']=str_replace(" ", "_", $fileName);
			$values['AUTORE']=$autore;
			$values['PRJ']=1; //$this->xml_form->config_service['PRJ']; //100; //PRJ DELLA WCA!
			$values['ID_TIPO_REF']=$id_area;
			$values['KEYWORDS']=$_GET['keywords'];
			$values['TOPIC']=$_GET['topic'];
			$values['TITOLO']=$_GET['thread'];
			
			$pk='';
			$sql->insert($values, "DOCS", $pk);
			
			$conn->commit();
			
			//if (isset($_GET['qqfile'])){
			//	"Doc_Area{$id}.{$ext}";
			//}else{
			//	$_FILES['qqfile']['name']="Doc_Area{$id}.{$ext}";
			//}
			$fname = "Doc_Area{$id}.{$ext}";
			$uploader = new qqFileUploader($allowedExtensions, $sizeLimit);
			$result = $uploader->handleUpload('WCA/docs/',$fname, true);
			
			
			$txtmsg="<a href='#'>pippo</a>";
			
			$result['fileName']=$fileName;
			$result['keywords']=$_GET['keywords'];
			
			$result['txtmsg']=field_file_doc::getAttachedDoc($conn, $_GET['id_area'], $_GET['keywords']);
			
			
			//$result='{success: '.json_encode("true").', fileName: '.json_encode($fileName).',id: '.json_encode($id).', keywords: '.json_encode($_GET['keywords']).', txtmsg:  '.json_encode($txtmsg).'}';
			
			echo htmlspecialchars(json_encode($result), ENT_NOQUOTES);
			//die("{success:true}");
			die(); //Attenzione, per farlo funzionare bisogna che in generale il servizio non abbia degli echo in cima alle pagine!
		}
	}
}




?>
