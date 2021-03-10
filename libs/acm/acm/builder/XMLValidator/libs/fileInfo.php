<?php 

class fileInfo{
	/* prende il percorso del file sia xml che xsd, e ne restituisce le informazioni legate a nome, estensione, peso , modfifica, percosro assoluto.
	 * */
	 
	var $file_info;
	var $html_info;
	
	/*
	 *utilizza e primitive di php per generare le info 
	 * */
	function fileInfo($file_path){
		
		if (!(is_dir($file_path)) && file_exists($file_path)){
			//$this->file_info['path']=$file_path;
		
			$path_info=pathinfo($file_path);
			/*$this->file_name=preg_replace("/\.{$path_info['extension']}\$/i", "", $this->file_path);
			print_r(posix_getpwuid(fileowner($directory['csv'].$file)));
			print_r(stat($directory['csv'].$file));
			print_r(posix_getgrgid(filegroup($directory['csv'].$file)));*/
			
			$this->file_info['base']=$path_info['basename'];
			$this->file_info['name']=preg_replace("/\.{$path_info['extension']}\$/i", "", $this->file_info['base']);
			$this->file_info['ext']=$path_info['extension'];
			$this->file_info['creation']=date("d/m/y H:i:s", filectime($file_path));
			$this->file_info['mod']=date("d/m/y H:i:s", filemtime($file_path));
			$this->file_info['size']=byteConvert(filesize($file_path));
			//$this->file_info['abs_path']=realpath($file_path);
			
			$this->html_info="<table class=\"table table-striped table-bordered table-hover\" cellpadding=\"0\" cellspacing=\"0\">";
			$this->html_info.="<tr>";
			$this->html_info.="<td class=\"file_info_header\" colspan=2><h5> {$this->file_info['ext']} file selected</h5></td>";
			$this->html_info.="</tr>";
			
			$this->html_info.="<tr>";
			$this->html_info.="<td class=\"file_info_left\">Name</td><td class=\"file_info_right\" style=\"font-weight:bold;\">{$this->file_info['base']}</td>";
			$this->html_info.="</tr>";
			
			$this->html_info.="<tr>";
			$this->html_info.="<td class=\"file_info_left\">Extension</td><td class=\"file_info_right\">{$this->file_info['ext']}</td>";
			$this->html_info.="</tr>";
			
			$this->html_info.="<tr>";
			$this->html_info.="<td class=\"file_info_left\">Creation</td><td class=\"file_info_right\">{$this->file_info['creation']}</td>";
			$this->html_info.="</tr>";
			
			$this->html_info.="<tr>";
			$this->html_info.="<td class=\"file_info_left\">Modified</td><td class=\"file_info_right\">{$this->file_info['mod']}</td>";
			$this->html_info.="</tr>";
			
			$this->html_info.="<tr>";
			$this->html_info.="<td class=\"file_info_left\">Weight</td><td class=\"file_info_right\">{$this->file_info['size']}</td>";
			$this->html_info.="</tr>";
			
			$this->html_info.="<tr>";
			$this->html_info.="<td class=\"file_info_left\">Absolute Path</td><td class=\"file_info_right\">{$this->file_info['abs_path']}</td>";
			$this->html_info.="</tr>";
			
			$this->html_info.="</table>";	
		} else{
			$this->file_info="No information on file, file not found or could be a directory";
			$this->html_info="<div>No information on file, file not found or could be a directory</div>";
		}
	}
	
	
	function getInfo($property=null){
	/*
	 *  Restituisce la proprieta'� scelta, false se non esiste, tutte le proprietà se non specificato 
	 * anche una singla propriet� , passandogli il parametro
	 */
		if(isset($property) && $property != ""){
		
			if($property == "base" || $property == "name" || $property == "ext" || $property == "creation" || $property == "mod" || $property == "size" || $property == "abs_path"){
			
				return $this->file_info[$property];
			} else{
			
				return "false";	
			}
		
		} else{
		
			return $this->file_info;
		}
	}
	
	/*
	 * rappr html delle informazioni del file, tuttte le info
	 * */
	function getHtmlFileInfo(){
	
		return $this->html_info;
	}
}

/*
 * mi genera il peso
 * */
	function byteConvert($size, $round = 0) {
    	/* La size deve essere espressa in Bytes */
    	$sizes = array('B', 'kB', 'MB', 'GB', 'TB', 'PB', 'EB', 'ZB', 'YB');
    	for ($i=0; $size > 1024 && $i < count($sizes) - 1; $i++) $size /= 1024;
    	
    	return round($size,$round)." ".$sizes[$i];
	} 

?>

