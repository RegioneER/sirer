<?
/**
 * @package Fields
 */
include_once "field.inc";

class field_dossier_files extends field{

	function open_($value){
		global $in;
		$txt=$this->testo;

		if (isset($this->values)) foreach ($this->values as $key => $val) $value=$val;
		if ($this->attributes['SQL_TYPE']=='data') $value_display=substr($value,0,2)."/".substr($value,2,2)."/".substr($value,4,4);
		else $value_display=$value;
		$this->input_field="<b>".$value_display."</b>";
		$this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
		$value=str_replace("\"", "&quot;", $value);
		
		$arrayfile=$this->elencafiles("/documenti/aifa-trasparenza/eCTD/");
		
//		print_R($arrayfile);
		foreach($arrayfile as $key=>$val) {
			if(preg_match("/{$_GET['ID_PRAT']}_/",$val)) {
			$temp=str_replace("{$_GET['ID_PRAT']}_","",$val);
//			if(!preg_match("/_PROGR_/",$temp))
				$str[]=$temp;
			} 
//			else if(preg_match("/{$_GET['ID_PRAT']}/",$val)) {
//				$str[]=$val."_0";
//			}
		}
		rsort($str);
//		print_r($str);
//		$dir="/documenti/aifa-trasparenza/eCTD/{$_GET['ID_PRAT']}_".$str[0]."_PROGR_{$_GET['PROGR']}/";
//		$dir_web="/CheckPoint/eCTD_docs/{$_GET['ID_PRAT']}_".$str[0]."_PROGR_{$_GET['PROGR']}/";
		$dir="/documenti/aifa-trasparenza/eCTD/{$_GET['ID_PRAT']}_".$str[0]."/";
		$dir_web="/CheckPoint/eCTD_docs/{$_GET['ID_PRAT']}_".$str[0]."/";
//		echo $dir;
		$files=$this->elencafiles($dir, true);
		$this->input_txt.="<div align=\"center\">";
		foreach($files as $key=>$val) {
			$this->input_txt.="<a href=\"$dir_web{$val}\" class=\"normal_link\"><span>".$val."</span></a><br />";
		}
		$this->input_txt.="</div><br />";
		
		if ($this->attributes['TB']!='no') $this->input_txt.="<input type=\"hidden\" name=\"{$this->attributes['VAR']}\" value=\"{$value}\">";
	}

	function close_($value){
		global $in;

		$txt=$this->testo;
		
		
		if (isset($this->values) && $value=='') foreach ($this->values as $key => $val) $value=$val;
		else $value_display=$value;
//		if ($value=='') $value="n.d.";
		if ($this->attributes['SQL_TYPE']=='data') $value_display=substr($value,0,2)."/".substr($value,2,2)."/".substr($value,4,4);
		else $value_display=$value;
		$this->input_field="<b>".$value_display."</b>";
		$this->input_txt=$txt;
		if ($this->attributes['AF']!='' && $in['make_appl_form']!='') {
			$this->input_txt='';
			$this->input_field='';
		}
		
		$arrayfile=$this->elencafiles("/documenti/aifa-trasparenza/eCTD/");
		foreach($arrayfile as $key=>$val) {
			$str[]=str_replace("{$_GET['ID_PRAT']}_","",$val);
			rsort($str);
		}
//		print($str[0]);
		$dir="/documenti/aifa-trasparenza/eCTD/{$_GET['ID_PRAT']}_".$str[0]."/";
		$dir_web="/CheckPoint/eCTD_docs/{$_GET['ID_PRAT']}_".$str[0]."/";
		$files=$this->elencafiles($dir, true);
		$this->input_txt.="<div align=\"center\">";
		foreach($files as $key=>$val) {
			$this->input_txt.="<a href=\"$dir_web{$val}\" class=\"normal_link\"><span>".$val."</span></a><br />";
		}
		$this->input_txt.="</div><br />";
		
	}
	
	function all_in($var, $i, $row, $this_closed) {
		$ret['body']="<td class=sc4bis><b>{$row[$var]}</b></td>";
		return $ret;
	}

	static function S_all_in($field, $m_p, $xml_form){
	if ($xml_form->form ['TOT_NOT_ENABLED'] != 'yes') {
										$tr_agg .= "<td class=int>&nbsp;</td>";
									}
									return $tr_agg;
	}
	
	function elencafiles($dirname, $flag=null){
		$arrayfiles=Array();
		if(file_exists($dirname)){
			$handle = opendir($dirname);
			while (false !== ($file = readdir($handle))) { 
				if(preg_match("/^{$_GET['ID_PRAT']}_[0-9]*/",$file) || $flag || preg_match("/^{$_GET['ID_PRAT']}/",$file)){
					if($file!="." && $file!="..")
					 array_push($arrayfiles,$file);
				}
			}
			$handle = closedir($handle);
		}
//		sort($arrayfiles);
		return $arrayfiles;
	}


}


?>