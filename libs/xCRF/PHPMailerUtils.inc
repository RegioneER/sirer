<?php
//echo "PHPMAIL - PRE-INCLUDE";
require_once("PHPMailer/PHPMailerAutoload.php"); //TEST PHPMAILER
//echo "PHPMAIL - AFTER-INCLUDE";
/* Funzione per invio mail */
function send_email($to = null, $from, $from_name, $subject, $message, $reply_to, $attachments = false, $cc = null, $bcc = null, $content_type = null, $charset = null,$silent=true,$username='genius.suite@exomgroup.com',$password='test123!') {



    $mail = new PHPMailer;

    //$mail->SMTPDebug = 3;                               // Enable verbose debug output

    //$mail->isSMTP();                                      // Set mailer to use SMTP
    //$mail->Host = 'mail.cineca.it';  // Specify main and backup SMTP servers
    //$mail->SMTPAuth = true;                               // Enable SMTP authentication
    #$mail->Username = $username;                 // SMTP username
    #$mail->Password = $password;                           // SMTP password
    //$mail->SMTPSecure = 'tls';                            // Enable TLS encryption, `ssl` also accepted
    //$mail->Port = 25;                                    // TCP port to connect to
	if (!$charset){
		$charset = "UTF-8";
	}
	$charset = strtoupper($charset);
	$mail->CharSet = $charset;
	
	$mail->setFrom($from, $from_name);
	
	$to_array=explode(",", $to);
	foreach($to_array as $_to){
		$mail->addAddress($_to);	
	}
	
	$mail->addReplyTo($reply_to);
	$cc_array=explode(",", $cc);
	foreach($cc_array as $_cc){
		$mail->addCC($_cc);	
	}
	
	$bcc_array=explode(",", $bcc);
	foreach($bcc_array as $_bcc){
		$mail->addBCC($_bcc);
	}
	if ($attachments != false) {
		for($i = 0; $i < count ( $attachments ); $i ++) {
			$mail->addAttachment($attachments [$i] ['src'], $attachments [$i] ['name'],'base64',returnMIMEType($attachments [$i] ['name']));
		}
	}	
	
	$mail->isHTML(true);                                  // Set email format to HTML
	
	$mail->Subject = $subject;
	$mail->Body    = $message;
	//$mail->AltBody = $row['MESSAGE'];
	$retval=$mail->send();
	if(!$silent){
		if(!$retval) {
			common_add_message('Message could not be sent. Mailer Error: ' . $mail->ErrorInfo,WARNING);
		} else {
	    	common_add_message('Message to '.$to.' has been sent',INFO);
		}
	}
	return $retval;
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

function checkEmail($email) {
  
  /* Controllo prima che sia presenta la @ che la lunghezza non superi i 255 caratteri  */
  if (!ereg("^[^@]{1,64}@[^@]{1,255}$", $email)) {
    
    /* E-mail non valida, numero di caratteri errato in una delle sezioni o numero di @ errato */
    return false;
  }
  
  $email_array = explode("@", $email);
  $local_array = explode(".", $email_array[0]);
  for ($i = 0; $i < sizeof($local_array); $i++) {
    if(!ereg("^(([A-Za-z0-9!#$%&'*+/=?^_`{|}~-][A-Za-z0-9!#$%&'*+/=?^_`{|}~\.-]{0,63})|(\"[^(\\|\")]{0,62}\"))$",$local_array[$i])) {
      return false;
    }
  }
  /* Controlla che il DNS sia un numero IP o che sia un DNS valido */
  if (!ereg("^\[?[0-9\.]+\]?$", $email_array[1])) {
    $domain_array = explode(".", $email_array[1]);
    if (sizeof($domain_array) < 2) {
        return false; // Non abbastanza token
    }
    for ($i = 0; $i < sizeof($domain_array); $i++) {
      if(!ereg("^(([A-Za-z0-9][A-Za-z0-9-]{0,61}[A-Za-z0-9])|([A-Za-z0-9]+))$",$domain_array[$i])) {
        return false;
      }
    }
  }
  return true;
}

?>
