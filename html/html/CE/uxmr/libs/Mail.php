<?php 
/**
 * @package CORE
 */


if ( preg_match('/Mail.php/', $_SERVER['REQUEST_URI']) ) 
	die ("Direct access not permitted");

	
	/**
 * Funzione di libreria testata e stra-testata per invio di mail.
 * 
 * @param $to
 * @param $from
 * @param $from_name
 * @param $subject
 * @param $message
 * @param $reply_to
 * @param $attachments --> ATTENZIONE E' ATTESO UN ARRAY del tipo arrray(array('src' => $attach_src, 'name' => $attach_name))
 * @param $cc
 * @param $bcc
 */
function send_email_advanced($to = null, $from, $from_name, $subject, $message, $reply_to, $attachments = false, $cc = null, $bcc = null) {

	$eol = PHP_EOL;

	$headers = "From: " . $from_name . "<" . $from . ">".$eol;
	$now=date("d-m-Y H:i:s");
	$today=date("Y_m_d");
	$from_name=str_replace(" ","_",$from_name);
	$log_dir="logs/email_log/";
	$log_file=$log_dir."email_log_{$today}_{$from_name}.html";
	if ($bcc != ''){
		$headers .= "BCC: $bcc".$eol;
	}
	$headers .= "CC: $cc".$eol;
	$headers .= "Reply-To: " . $reply_to . "<" . $reply_to . ">".$eol;
	$headers .= "Return-Path: " . $from_name . "<" . $from . ">".$eol;
	$headers .= "Message-ID: <" . time () . "-" . $from . ">".$eol;
	//$headers .= "X-Mailer: PHP v" . phpversion ();
	$msg_txt = "";
	$email_txt = $message;
	$semi_rand = md5 ( time () );
	//$mime_boundary = "==Multipart_Boundary_x{$semi_rand}x";
	$mime_boundary = $semi_rand;
	$headers .= "MIME-Version: 1.0".$eol."Content-Type: multipart/mixed;".$eol." boundary=\"$mime_boundary\"".$eol.$eol;
  $email_txt .= $msg_txt;
  $email_message .= "This is a multi-part message in MIME format.".$eol.$eol;
  $email_message .= "--$mime_boundary".$eol;
  $email_message .= "Content-Type:text/html; charset=\"iso-8859-1\"".$eol.$eol;
  $email_message .= $email_txt.$eol.$eol;
	if ($attachments != false) {
		for($i = 0; $i < count ( $attachments ); $i ++) {
			if (true || is_file ( $attachments [$i] ['src'] )) {
				$fileatt = $attachments [$i] ['src'];
		        $fileatt_type = "application/octet-stream";
		        $start = strrpos ( $attachments [$i] ['src'], '/' ) == - 1 ? strrpos ( $attachments [$i] ['src'], '//' ) : strrpos ( $attachments [$i] ['src'], '/' ) + 1;
		        $fileatt_name = $attachments [$i] ['name'];
		        $fileatt_name = str_replace(" ","_",$fileatt_name);
		        $file = fopen ( $fileatt, 'rb' );
						$data = fread ( $file, filesize ( $fileatt ) );
						fclose ( $file );
				$data = chunk_split ( base64_encode ( $data ), 60, $eol );
				$filetype=returnMIMEType($fileatt_name);
				//	    $email_message .= "Content-Type: ".mime_content_type($fileatt_name).";".$eol;
				$email_message .= "--$mime_boundary".$eol;
				$email_message .= "Content-Type: $filetype; name=\"$fileatt_name\"".$eol;
				$email_message .= "Content-Disposition: attachment; filename=\"$fileatt_name\"".$eol;
				$email_message .= "Content-Transfer-Encoding: base64".$eol;
				$email_message .= "X-Attachment-Id: f_".md5_file($fileatt).$eol.$eol;
				$email_message .= $data; //.$eol;
			}
		}
  	}
        $email_message .= "--$mime_boundary--".$eol;

        $log="<p align=center>Email sended at $now</p>
              	<li>to:$to</li>
                <li>headers:$headers</li>
                <li>oggetto:$subject</li>
                <li>testo:$message</li>
                <hr>";
        if(!file_exists($log_dir)) {
                mkdir($log_dir, 0777, true) ;
                $flag="w";
        } else {
                $flag="a";
        }

//      $log.=file_get_contents($log_dir);
        $fp=fopen ($log_file, $flag);
        fwrite($fp,$log);
        fclose($fp);

        return mail ( $to, $subject, $email_message, $headers );
}

/* Mime Type */
function returnMIMEType($filename){
	preg_match("|\.([a-z0-9]{2,4})$|i", $filename, $fileSuffix);

    switch(strtolower($fileSuffix[1])) {
    case "js" :
    	return "application/x-javascript";
	case "json" :
        return "application/json";
	case "jpg" :
    
		case "jpeg" :
        case "jpe" :
        	return "image/jpg";

	case "png" :
    case "gif" :
    case "bmp" :
    case "tiff" :
    	return "image/".strtolower($fileSuffix[1]);
 	case "css" :
    	return "text/css";
	case "xml" :
		return "application/xml";
	case "doc" :
    case "docx" :
    	return "application/msword";

	case "xls" :
    case "xlt" :
    case "xlm" :
    case "xld" :
    case "xla" :
    case "xlc" :
    case "xlw" :
    case "xll" :
    	return "application/vnd.ms-excel";
    	
	case "ppt" :
    case "pps" :
    	return "application/vnd.ms-powerpoint";
    	
	case "rtf" :
    	return "application/rtf";
	case "pdf" :
    return "application/pdf";

	case "html" :
    case "htm" :
    case "php" :
    	return "text/html";

	case "txt" :
    	return "text/plain";

	case "mpeg" :
    case "mpg" :
    case "mpe" :
    	return "video/mpeg";

	case "mp3" :
    	return "audio/mpeg3";

	case "wav" :
    	return "audio/wav";
	case "aiff" :
    case "aif" :
    	return "audio/aiff";

	case "avi" :
        return "video/msvideo";

    case "wmv" :
    	return "video/x-ms-wmv";

	case "mov" :
    	return "video/quicktime";

	case "zip" :
    	return "application/zip";
	
	case "tar" :
    	return "application/x-tar";

	case "swf" :
    	return "application/x-shockwave-flash";

 	default :
        if(function_exists("mime_content_type")){
        	$fileSuffix = mime_content_type($filename);
		}
		
    	return "unknown/" . trim($fileSuffix[0], ".");
	}
}
