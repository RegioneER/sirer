<?php

	$data = false;
	$nomefile = "download";
	$path=$_SERVER ['DOCUMENT_ROOT'] ."/study/" . $_GET ['study_root'] . "/xml/" . $_GET['file'];
	if (substr($path, strrpos($path, '.')) == '.xml'){	
		$nomefile = $_GET['file'];
		$data = file_get_contents($path);
		var_dump($data);
	}
	
	if ($data){
		$ext = strrchr($nomefile, ".");
		switch ($ext) {
	      case "pdf": $ctype="application/pdf"; break;
	      case "exe": $ctype="application/octet-stream"; break;
	      case "zip": $ctype="application/zip"; break;
	      case "doc":
	      case "docx": $ctype="application/msword"; break;
	      case "xls":
	      case "xlsx": $ctype="application/vnd.ms-excel"; break;
	      case "ppt": $ctype="application/vnd.ms-powerpoint"; break;
	      case "gif": $ctype="image/gif"; break;
	      case "png": $ctype="image/png"; break;
	      case "jpeg":
	      case "jpg": $ctype="image/jpg"; break;
	      default: $ctype="application/force-download";
	    }	
		
	    ob_clean();
		header("Pragma: public");
		header("Expires: 0");
		header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
		header("Content-Type: $ctype");
		header("Content-Description: File Transfer");
		header("Content-Disposition: attachment; filename=\"$nomefile\"");
		header("Accept-Ranges: bytes");
		header("Content-Length: ".strlen($data));
		header("Content-Transfer-Encoding: binary");
		
		die($data);
	}
?>