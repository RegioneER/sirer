<?
/**
 * @package FileAllegati
 */
include_once "field_code_decode.inc";

class field_file extends field_code_decode{

	function open_($value){
		global $in;
//		global $inputval;
		$inputval=$this->db_vars;
		$file_uploaded="";
		if ($value!=''){
			$file_name=$inputval['D_'.$this->attributes['VAR']];
			$file_uploaded="<br>Download file: <a href=\"download.php?nome_file=$file_name&nome_real_file=$value\">$file_name</a>";
		}
		if ($this->attributes['COMPILA_FIELD']!=''){
			if ($this->attributes['COMPILA_VALUE']!='')
			$this->check_js.="
				if (document.forms[0].{$this->attributes['VAR']}.value!=''){
					document.forms[0].{$this->attributes['COMPILA_FIELD']}.value='{$this->attributes['COMPILA_VALUE']}';
				}
			";
			if ($this->attributes['COMPILA_VALUE_ADD']!='')
			$this->check_js.="
				if (document.forms[0].{$this->attributes['VAR']}.value!=''){
					document.forms[0].{$this->attributes['COMPILA_FIELD']}.value+='{$this->attributes['COMPILA_VALUE']}';
				}
			";
			$onblur_agg="cf();";
			$onchange=" onchange=\"cf();\"";
		}
		$txt=$this->testo;
		$input_html="
			<input type=\"file\" name=\"{$this->attributes['VAR']}\" size=\"80\"
			
			onblur=\"
			$onblur_agg
			\"
			$onchange/>
			<input type=\"hidden\" name=\"D_{$this->attributes['VAR']}\" value=\"$file_name\">
			$file_uploaded";
		$this->input_txt=$txt;
		$this->input_field=$input_html;
	}

	function open_send($value){
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning!! It\\'s necessary to attach a file in the box ";
		else
			$alert_msg="Attenzione!!!E\\' necessario allegare un file nel campo:\\n ";
			
		$js_txt=make_js($this->testo);
		$this->invia_js="
			if (document.forms[0].D_{$this->attributes['VAR']}.value=='' && document.forms[0].{$this->attributes['VAR']}.value=='') {
				alert('".$alert_msg." ".$js_txt."');
				document.forms[0].{$this->attributes['VAR']}.focus();
				return false;			
			}
		";		
	}
	
	function open_save($value){
		//traduzione del messaggio di alert in inglese
		if($this->config_service['lang']=="en")
			$alert_msg="Warning!! It\\'s necessary to attach a file in the box ";
		else
			$alert_msg="Attenzione!!!E\\' necessario allegare un file nel campo:\\n ";
			
		$js_txt=make_js($this->testo);
		$this->salva_js="
			if (document.forms[0].D_{$this->attributes['VAR']}.value=='' && document.forms[0].{$this->attributes['VAR']}.value=='') {
				alert('".$alert_msg." ".$js_txt."');
				document.forms[0].{$this->attributes['VAR']}.focus();
				return false;			
			}
		";		
	}

	function close_($value){
		global $in;
		global $inputval;
		//print_r($inputval);
		//global $inputval;
		$file_uploaded="";
		if ($value!=''){
			$file_name=$inputval['D_'.$this->attributes['VAR']];
			$file_uploaded="Download file: <a href=\"download.php?nome_file=$file_name&nome_real_file=$value\">$file_name</a>";
		}
		$txt=$this->testo;
		$input_html="$file_uploaded";
		$this->input_txt=$txt;
		$this->input_field=$input_html;
	}

	function allinea_db(){
		if ($this->attributes['TB']!='no'){
			$ret[0]="{$this->attributes['VAR']} VARCHAR2(400 char)";
			$ret[1]="D_{$this->attributes['VAR']} VARCHAR2(300 char)";
			return $ret;
		}
		else return ;
	}

	function insert_stmt($insert=true){
		global $in;
		global $config_service;
		
		//echo "<hr>insert=$insert<hr>";
		
	
		if (!$insert){
			$this->field_stmt[0]="{$this->attributes['VAR']}";
			$this->field_stmt[1]="D_{$this->attributes['VAR']}";
			//die();
			return;
		}
		if ($this->attributes['TB']!='no' && $_FILES[$this->attributes['VAR']]['size']>0){
			//echo "<hr>".$this->attributes['VAR']."<hr>";
			$filename=$_FILES[$this->attributes['VAR']]['name'];
			$ext=explode(".", $filename);
			if ($config_service['PK_SERVICE']!='') $pk_service=$config_service['PK_SERVICE'];
			else $pk_service='CODPAT';
			$unique_key=$pk_service."_".$in[$pk_service]."_PROGR_".$in['PROGR']."_VISITNUM_".$in['VISITNUM']."_ESAM_".$in['ESAM'];
			if ($config_service['VISITNUM_PROGR']=='1') $unique_key.="_VPROGR_".$in['VISITNUM_PROGR'];
			$file_to_write=$this->attributes['VAR']."_".$unique_key.".".$ext[1];
			$in[$this->fields[$i]['VAR']]=$file_to_write;
			//global $dir;
			$dir='';
			$paths=explode("/", $_SERVER['PATH_TRANSLATED']);

			for ($i=0;$i<count($paths)-1; $i++){
				$dir.=$paths[$i]."/";
			}

			$dir_file=$dir."/uploaded_file/";
			$nome_real_file=$file_to_write;
			$file_to_write=$dir_file.$file_to_write;
			//echo "<hr>".$file_to_write;
			if (!move_uploaded_file($_FILES[$this->attributes['VAR']]['tmp_name'], $file_to_write)) die("ERRORE COPIA FILE");
			$this->field_stmt[0]="{$this->attributes['VAR']}";
			$this->field_stmt[1]="D_{$this->attributes['VAR']}";
			$this->value_stmt[0]=$nome_real_file;
			$this->value_stmt[1]=$filename;
			//print_r($this->value_stmt);
			//die("<hr>");
		}
		return;
	}
}


?>