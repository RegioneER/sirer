<?php

#
# Cineca SMS-GW Php API , versione 0.30 Beta
#

// PEAR stuff
ini_set("include_path", ("/http/lib/XMR/hyperlibs/libs/PEAR/:".ini_get("include_path")));
require_once 'HTTP/Client.php';
require_once 'HTTP/Request.php';

#Costanti ERRORI

$GLOBALS['ERR_OK'] = '0';
$GLOBALS['ERR_BADDATE'] = '-1';
$GLOBALS['ERR_INVDATE'] = '-2';
$GLOBALS['ERR_BADTO'] = '-3';
$GLOBALS['ERR_INVLOGIN'] = '-4';
$GLOBALS['ERR_NOCREDITONAZ']= '-5';
$GLOBALS['ERR_INVEXPIRE'] = '-6';
$GLOBALS['ERR_EMPTYDEST'] = '-7'; 
$GLOBALS['ERR_EMPTYTXT'] =  '-8'; 
$GLOBALS['ERR_BADREQ'] = '-9';
$GLOBALS['ERR_BADNOTIFY'] =  '-10';
$GLOBALS['ERR_DATELONG'] = '-11';
$GLOBALS['ERR_NOSMS'] = '-12';
$GLOBALS['ERR_RECSMS'] = '-13';
$GLOBALS['ERR_BADFROM'] = '-14';
$GLOBALS['ERR_NOCREDITOINT']='-15' ;
$GLOBALS['ERR_NOCREDITONOT']='-16' ;
$GLOBALS['ERR_NODATEMSG'] =  '-17' ;
$GLOBALS['ERR_NOMSG'] = '-18';
$GLOBALS['ERR_BADMITT'] = '-19';
$GLOBALS['ERR_SISTEM'] = '-20' ;
$GLOBALS['ERR_SISTEM1'] = '-21';
$GLOBALS['ERR_SISTEM2'] = '-22';
$GLOBALS['ERR_SISTEM3'] = '-23';
$GLOBALS['ERR_SISTEM4'] = '-24';
$GLOBALS['ERR_SISTEM5'] = '-25';
$GLOBALS['ERR_SISTEM6'] = '-26';
$GLOBALS['ERR_SISTEM7'] = '-27';
$GLOBALS['ERR_SISTEM51'] = '-38';
$GLOBALS['ERR_SISTEM52'] = '-39';
$GLOBALS['ERR_SISTEM53'] = '-40';
$GLOBALS['ERR_SISTEM54'] = '-41';
$GLOBALS['ERR_SISTEM55'] = '-44';
$GLOBALS['ERR_SISTEM56'] = '-51';
$GLOBALS['ERR_SISTEM61'] = '-33';
$GLOBALS['ERR_SISTEM62'] = '-34';
$GLOBALS['ERR_SISTEM63'] = '-35';
$GLOBALS['ERR_SISTEM64'] = '-36';
$GLOBALS['ERR_SISTEM65'] = '-37';
$GLOBALS['ERR_SISTEM66'] = '-42';
$GLOBALS['ERR_SISTEM67'] = '-45';
$GLOBALS['ERR_SISTEM68'] = '-47';
$GLOBALS['ERR_SISTEM69'] = '-49';
$GLOBALS['ERR_SISTEM71'] = '-28';
$GLOBALS['ERR_SISTEM72'] = '-29';
$GLOBALS['ERR_SISTEM73'] = '-30';
$GLOBALS['ERR_SISTEM74'] = '-31';
$GLOBALS['ERR_SISTEM75'] = '-32';
$GLOBALS['ERR_SISTEM76'] = '-43';
$GLOBALS['ERR_SISTEM77'] = '-46';
$GLOBALS['ERR_SISTEM78'] = '-48';
$GLOBALS['ERR_SISTEM79'] = '-50';
$GLOBALS['ERR_SISTEM690'] = '-52';
$GLOBALS['ERR_SISTEM790'] = '-53';
$GLOBALS['ERR_NOCREDIT'] = '-59';


#COSTANTI PER LE CHIAMATE HTTP VERSO IL FRONT-END
$GLOBALS['CINECA_SMSGW_url_send']	= 'https://mcgw.cineca.com/sms/cgi-bin/api_sendsms.pl';
$GLOBALS['CINECA_SMSGW_url_receive']= 'https://mcgw.cineca.com/sms/cgi-bin/api_receive_generic.pl';
$GLOBALS['CINECA_SMSGW_url_query']	= 'https://mcgw.cineca.com/sms/cgi-bin/api_querysms.pl';
$GLOBALS['CINECA_SMSGW_url_stat']	= 'https://mcgw.cineca.com/sms/cgi-bin/api_statsms.pl';
$GLOBALS['CINECA_SMSGW_url_credit'] = 'https://mcgw.cineca.com/sms/cgi-bin/api_checkcreditsms.pl';
$GLOBALS['CINECA_SMSGW_url_stat_generic']= 'https://mcgw.cineca.com/sms/cgi-bin/api_stat_generic.pl';

$GLOBALS['MAX_PH_LEN'] = 15;


/* *************************
 * sms_send
 * *************************
 *  funzione per invio sms 
 *  ritorna: 
 *  l'esito e l'identificativo della richiesta
 */

function sms_send ($user, $password, $mail, $mitt, $testo, $destinatari, $sched_invio, $sched_val, $notifica, $email_notifiche) {
	#il campo testo non puo\' essere vuoto
	if($testo == '') {
		return array($GLOBALS['ERR_EMPTYTXT'],0);
	}
	#il campo destinatario non puo\' essere vuoto
	if($destinatari == '') {
		return array($GLOBALS['ERR_EMPTYDEST'],0);
	}
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_send']);
	// Check user authentication
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);

	$req->addPostData('email',$mail);
	$req->addPostData('mittente',$mitt);
	$req->addPostData('testo',$testo);
	$req->addPostData('destinatari',$destinatari);
	$req->addPostData('datainvio',$sched_invio);
	$req->addPostData('validita',$sched_val);
	$req->addPostData('account',$user);
	$req->addPostData('notifica',$notifica);
	$req->addPostData('email_notifiche',$email_notifiche);
	
	# per l'autenticazione
	$response = $req->sendRequest();
	
	if (PEAR::isError($response)) {
		# user/pass non corrette
		return array($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$status = explode(":",$req->getResponseBody());
            $status=chop($status[1]);
			return($status);
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}

/* *************************
 * sms_receive
 * *************************
 * funzione per prelevare gli sms entranti in base al login
 * ritorna:
 *  esito operazione e lista di puntatori ad array contenenti:
 *  message id;
 * 	mittente alfanumerico del messaggio;
 *  destinatario del messaggio
 * 	testo del msg;
 * 	data ricezione in formato unix;
 */
function sms_receive($user, $password) {
	
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_receive']);
	// Check user authentication
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('flag', "pop");
	$req->addPostData('account',$user);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
			# user/pass non corrette
			return array($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$querycode = array();
			$receive_history = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			if ($exit == '0') { # se tutto ok 
				for($i=0; $i<$n-1; $i++) {
					$querycode = explode("\x80",$queryresult[$i+1]);
					$receive_history[$i]['msgid'] = $querycode[0]; # msgid 
					$receive_history[$i]['mittente'] = $querycode[1]; # mittente
					$receive_history[$i]['destinatario'] = $querycode[2]; # recipient 
					$receive_history[$i]['testo'] = $querycode[3]; # testo
					$receive_history[$i]['rec_time'] = $querycode[4]; # receive_time
				}
				#ritorna array
				return array($exit,$receive_history);
			} else { #altrimenti ritorna codice d'errore
				return array($exit,0);
			}
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}




/* *************************
 * sms_receive_history
 * *************************
 * funzione per verificare lo storico degli gli sms ricevuti
 * usage: sms_receive_history($user, $password, [$date, $start_index, $numrows]);
 * ritorna:
 * esito operazione e lista di puntatori ad array contenenti:
 * ['msgid'] = message id;
 * ['mittente'] = mittente alfanumerico del msg
 * ['destinatario'] = destinatario del messaggio
 * ['testo'] = testo del messaggio
 * ['rec_time'] = data ricezione in formato unix
 * ['letto'] = flag che indica se sms Ã¨ stato giÃ  letto
 */

function sms_receive_history ($user, $password, $date, $start_index, $numrows){
	
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_receive']);
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('flag', "list");
	$req->addPostData('date',$date);
	$req->addPostData('start_index',$start_index);
	$req->addPostData('numrows',$numrows);
	$req->addPostData('account',$user);
	$response = $req->sendRequest();

	if (PEAR::isError($response)) {
			# user/pass non corrette
			return array($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$querycode = array();
			$receive_history = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			if ($exit == '0') { # se tutto ok 
				for($i=0; $i<$n-1; $i++) {
					$querycode = explode("\x80",$queryresult[$i+1]);
					$receive_history[$i]['msgid'] = $querycode[0]; # msgid 
					$receive_history[$i]['mittente'] = $querycode[1]; # mittente
					$receive_history[$i]['destinatario'] = $querycode[2]; # recipient 
					$receive_history[$i]['testo'] = $querycode[3]; # testo
					$receive_history[$i]['rec_time'] = $querycode[4]; # receive_time
					$receive_history[$i]['letto'] = $querycode[5]; # letto
				}
				#ritorna array
				return array($exit,$receive_history);
			} else { #altrimenti ritorna codice d'errore
				return array($exit,0);
			}
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}

/* *************************
 * sms_queryrequest
 * *************************
 * funzione per query sms in base all' id della richiesta
 * ritorna:
 * [0] = esito operazione 
 * [1] = array associativo in cui ogni riga contiene:  
 * 	['msgid'] = message id;
 * 	['mittente']= mittente alfanumerico del msg;
 * 	['testo'] = testo del msg;
 * 	['recipient'] = numero telefonico del destinatario del msg;
 * 	['notifica'] = notifica richiesta: 0 o 1;
 * 	['dtime'] = data invio schedulato in formato unix;
 * 	['vtime'] = data validita invio in formato unix;
 * 	['spedito'] = spedito: 0 o datainvio in formato unix; 
 * 	['notificato'] = notificato: 0 o 1;
 */

function sms_queryrequest($user, $password, $reqid) {

	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_query']);
	$req->setBasicAuth($user, $password);# per l'autenticazione
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('reqid', "$reqid");
	$req->addPostData('account',"$user");
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
			# user/pass non corrette
			return array($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$querycode = array();
			$query_status = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			preg_replace("/(\d+):\d+/",'$1',$exit);
			if ($exit == '0') { #se tutto OK
				for($i=1; $i<$n-1; $i++) {
					$querycode = explode("\x80", $queryresult[$i]);
					$query_status[$i-1]['msgid']=$querycode[0];
					$query_status[$i-1]['mittente']=$querycode[1];
					$query_status[$i-1]['testo']=$querycode[2];
					$query_status[$i-1]['recipient']=$querycode[3];
					$query_status[$i-1]['notifica']=$querycode[4];
					$query_status[$i-1]['dtime']=$querycode[5];
					$query_status[$i-1]['vtime']=$querycode[6];
					$query_status[$i-1]['spedito']=$querycode[7];
					$query_status[$i-1]['notificato']=$querycode[8];
				}
			#ritorna array
			return array($exit, $query_status);
			} else { #altrimenti ritorna codice d'errore
					return array($exit, 0);
			}

		} else {
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}


/* *************************
 * sms_querystatus
 * *************************
 * ritorna un array di 2 elementi:
 * [0] = esito operazione 
 * [1] = array associativo in cui ogni riga contiene: 
 * 	['msgid'] = id messaggio
 * 	['notifica'] =  notifica: 0 o 1;
 * 	['data_invio'] = data invio schedulato in formato unix;
 * 	['data_validita'] = data validita invio in formato unix;
 * 	['spedito'] = spedito: 0 o datainvio in formato unix; 
 * 	['notificato'] = notificato: 0 o 1;
 */ 

function sms_querystatus ($user, $password, $reqid, $dest){
	
	#modifica numero destinatario in formato corretto
	if((preg_match("/^(\d)+/", $dest) || preg_match("/^(\+)(\d)+/", $dest)) && (strlen($dest) <= $GLOBALS['MAX_PH_LEN'] )) {
		if(preg_match("/^(\d)+/", $dest)) { #inizia con numeri
			preg_replace("/^00/","\+/",$dest);#sostituisce 00 con +
			if(!preg_match("/^\+/",$dest)) {
				$dest= "+39$dest";
			}
			$destinatario=$dest;
		} else if(preg_match("/^(\+39)(\d)+/",$dest)) { #inizia con +39 nazionale
			$destinatario=$dest;
		} else {
			$destinatario=$dest;
		}
	} else { # destinatario non valido
		return array ($GLOBALS['ERR_BADTO'],0);
	}
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_query']);
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('reqid',$reqid);
	$req->addPostData('to',$destinatario);
	$req->addPostData('account',$user);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
		return array ($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$queryresult = array();
			$query_status = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			preg_replace("/(\d+):\d+/",'$1',$exit);
			if ($exit == '0') { #se tutto OK
			for($i=1; $i < $n-1; $i++) {
					$querycode = explode("\x80", $queryresult[$i]);
					$query_status[$i-1]['msgid'] = $querycode[0];
					$query_status[$i-1]['notifica'] = $querycode[1];
					$query_status[$i-1]['data_invio'] = $querycode[2];
					$query_status[$i-1]['data_validita'] = $querycode[3];
					$query_status[$i-1]['spedito'] = $querycode[4];
					$query_status[$i-1]['notificato'] = $querycode[5];
				}
				#ritorna array
				return array($exit, $query_status);
			} else { #altrimenti ritorna codice d'errore
				return array($exit, 0);
			}
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}



/* *************************
 * sms_stat_by_recipient
 * *************************
 * verifica messaggi inviati ad uno specifico destinatario, dopo una certa data
 * ritorna un array di 2 elementi:
 * [0] = esito operazione 
 * [1] = array associativo in cui ogni riga contiene: 
 *
 * ['reqid'] = reqid;
 * ['msgid'] = id messaggio;
 * ['recipient'] = numero telefonico del destinatario del msg;
 * ['mittente'] = mittente alfanumerico del msg;
 * ['sched_deliverytime']= data invio schedulato in formato unix;
 * ['att_deliverytime'] = data invio in formato unix;
 * ['ack_deliverytime'] = data notifica in formato unix;
 * ['notifica'] = richiesta notifica: 0 o 1;
 * ['notificato'] = sms notificato: 0 o 1;
 * ['validita'] = data validita invio in formato unix;
 * ['email_notifiche'] = email utilizzata per la notifica;
 */

function sms_stat_by_recipient($user, $password, $recipient, $date) {
	
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_stat_generic']);	
	$req->setBasicAuth($user, $password);# per l'autenticazione
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('stat_by',"recipient");
	$req->addPostData('recipient', $recipient);
	$req->addPostData('date', $date);
	$req->addPostData('account',$user);
	$response = $req->sendRequest();

	if (PEAR::isError($response)) {
		# user/pass non corrette
		return array ($GLOBALS['ERR_INVLOGIN'],0);
	}else{
	# per l'autenticazione
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$queryresult = array();
			$query_status = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			preg_replace("/(\d+):\d+/",'$1',$exit);

			if ($exit == '0') { #se tutto OK
				for($i=1; $i < $n-1; $i++) {
					$querycode = explode("\x80", $queryresult[$i]);
					$query_status[$i-1]['reqid']=$querycode[0];
					$query_status[$i-1]['msgid']=$querycode[1];
					$query_status[$i-1]['recipient']=$querycode[2];
					$query_status[$i-1]['mittente']=$querycode[3];
					$query_status[$i-1]['sched_deliverytime']=$querycode[4];
					$query_status[$i-1]['att_deliverytime']=$querycode[5];
					$query_status[$i-1]['ack_deliverytime']=$querycode[6];
					$query_status[$i-1]['notifica']=$querycode[7];
					$query_status[$i-1]['notificato']=$querycode[8];
					$query_status[$i-1]['validita']=$querycode[9];
					$query_status[$i-1]['email_notifiche']=$querycode[10];
				}
				#ritorna array
				return array($exit, $query_status);
			} else { #altrimenti ritorna codice d'errore
				return array($exit, 0);
			}
			
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}


/* *************************
 * sms_stat_by_user
 * *************************
 * verifica messaggi inviati da un utenza sms, dopo una certa data
 * ritorna un array di 2 elementi:
 * [0] = esito operazione 
 * [1] = array associativo in cui ogni riga contiene: 
 *
 * ['reqid'] = reqid;
 * ['msgid'] = id messaggio;
 * ['recipient'] = numero telefonico del destinatario del msg;
 * ['mittente'] = mittente alfanumerico del msg;
 * ['sched_deliverytime']= data invio schedulato in formato unix;
 * ['att_deliverytime'] = data invio in formato unix;
 * ['ack_deliverytime'] = data notifica in formato unix;
 * ['notifica'] = richiesta notifica: 0 o 1;
 * ['notificato'] = sms notificato: 0 o 1;
 * ['validita'] = data validita invio in formato unix;
 * ['email_notifiche'] = email utilizzata per la notifica;
 */

function sms_stat_by_user($user, $password, $date) {
	
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_stat_generic']);	
	$req->setBasicAuth($user, $password);# per l'autenticazione
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('stat_by',"user");
	$req->addPostData('date', $date);
	$req->addPostData('account',$user);
	$response = $req->sendRequest();

	if (PEAR::isError($response)) {
		# user/pass non corrette
		return array ($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$queryresult = array();
			$query_status = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			preg_replace("/(\d+):\d+/",'$1',$exit);

			if ($exit == '0') { #se tutto OK
				for($i=1; $i < $n-1; $i++) {
					$querycode = explode("\x80", $queryresult[$i]);
					$query_status[$i-1]['reqid']=$querycode[0];
					$query_status[$i-1]['msgid']=$querycode[1];
					$query_status[$i-1]['recipient']=$querycode[2];
					$query_status[$i-1]['mittente']=$querycode[3];
					$query_status[$i-1]['sched_deliverytime']=$querycode[4];
					$query_status[$i-1]['att_deliverytime']=$querycode[5];
					$query_status[$i-1]['ack_deliverytime']=$querycode[6];
					$query_status[$i-1]['notifica']=$querycode[7];
					$query_status[$i-1]['notificato']=$querycode[8];
					$query_status[$i-1]['validita']=$querycode[9];
					$query_status[$i-1]['email_notifiche']=$querycode[10];
				}
				##ritorna array
				return array($exit, $query_status);
			} else { #altrimenti ritorna codice d'errore
				return array($exit, 0);
			}
			
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}


/* *************************
 * sms_querylist
 * *************************
 * funzione per query sms a partire dalla data indicata o in base al login 
 * ritorna un array di 2 elementi:
 * [0] = esito operazione 
 * [1] = array associativo in cui ogni riga contiene: 
 * 
 * 	['reqid'] = request id;
 * 	['mittente'] = mittente alfanumerico del msg;
 * 	['testo'] = testo del msg;
 * 	['dest'] = numero dei destinatari del msg;
 * 	['notifica'] = notifica: 0 o 1;
 * 	['dtime'] = data invio schedulato in formato unix;
 * 	['vtime'] = data validita invio in formato unix;
 * 	['spedito'] = spedito: 0 o datainvio in formato unix;
 *
 */

function sms_querylist ($user, $password, $date) {
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_query']);	
	$req->setBasicAuth($user, $password);# per l'autenticazione
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('date', $date);
	$req->addPostData('account',$user);
	$response = $req->sendRequest();# per l'autenticazione

	if (PEAR::isError($response)) {
		# user/pass non corrette
		return array ($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$queryresult = array();
			$query_status = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			preg_replace("/(\d+):\d+/",'$1',$exit);
			if ($exit == '0') { #se tutto OK
				for($i=1; $i < $n-1; $i++) {
					$querycode = explode("\x80", $queryresult[$i]);
					$query_status[$i-1]['reqid']=$querycode[0];
					$query_status[$i-1]['mittente']=$querycode[1];
					$query_status[$i-1]['testo']=$querycode[2];
					$query_status[$i-1]['dest']=$querycode[3];
					$query_status[$i-1]['notifica']=$querycode[4];
					$query_status[$i-1]['dtime']=$querycode[5];
					$query_status[$i-1]['vtime']=$querycode[6];
					$query_status[$i-1]['spedito']=$querycode[7];
				}
				#ritorna array
				return array($exit, $query_status);
			} else { #altrimenti ritorna codice d'errore
				return array($exit, 0);
			}
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}


/* *************************
 * sms_stat
 * *************************
 * funzione per  query sms in base al login e alla data(param. facoltativo)
 * ritorna:
 * [0] = esito operazione 
 * [1] = array associativo in cui ogni riga contiene: 
 * 
 * 	['reqid'] = request id;
 * 	['mittente'] = mittente alfanumerico del msg;
 * 	['testo'] = testo del msg;
 * 	['dest'] = numero dei destinatari del msg;
 * 	['sped'] = numero sms spediti
 * 	['not'] = numero sms notificati
 *  ['submitted_ts'] = data di richiesta spedizione in formato unix;
 *  ['sched_deliverytime'] = data di schedulazione in formato unix;
 *  ['validita'] = data validita messaggio
 *
 */

function sms_stat($user, $password, $date, $start_index, $numrows) {

	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_stat']);	
	$req->setBasicAuth($user, $password);# per l'autenticazione
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('date', $date);
	$req->addPostData('account',$user);
	$req->addPostData('start_index',$start_index);
	$req->addPostData('numrows',$numrows);
	$response = $req->sendRequest();# per l'autenticazione
	if (PEAR::isError($response)) {
		# user/pass non corrette
		return array ($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$queryresult = array();
			$query_status = array();
			$queryresult = explode("\n",$req->getResponseBody());
			$n = count($queryresult);
			#exitcode
			$exit = $queryresult[0];
			preg_replace("/(\d+):\d+/",'$1',$exit);
			if ($exit == '0') { # se tutto ok
				for($i=1; $i < $n-1; $i++) {
					$querycode = explode("\x80", $queryresult[$i]);
					$query_status[$i-1]['msgnum']=$querycode[0];
					$query_status[$i-1]['mittente']=$querycode[1];
					$query_status[$i-1]['testo']=$querycode[2];
					$query_status[$i-1]['dest']=$querycode[3];
					$query_status[$i-1]['sped']=$querycode[4];
					$query_status[$i-1]['not']=$querycode[5];
					$query_status[$i-1]['submitted_ts']=$querycode[6];
					$query_status[$i-1]['sched_deliverytime']=$querycode[7];
					$query_status[$i-1]['validita']=$querycode[8];
				}
			#ritorna array
			return array($exit, $query_status);
			} else { #altrimenti ritorna codice d'errore
				return array($exit, 0);
			}
		}else{# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}
}




/* *************************
 * sms_checkcredit
 * *************************
 * funzione che restituisce il credito per l'utenza
 * ritorna:
 * [0] = esito richiesta
 * [1] = Credito SMS NAZIONALI
 * [2] = Credito SMS INTERNAZIONALI 
 * [3] = Credito NOTIFICHE SMS 
 *
 */
function sms_checkcredit($user, $password) {
	
	$req =& new HTTP_Request($GLOBALS['CINECA_SMSGW_url_credit']);	
	$req->setBasicAuth($user, $password);# per l'autenticazione
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('account',$user);
	$response = $req->sendRequest();# per l'autenticazione

	if (PEAR::isError($response)) {
		# user/pass non corrette
		return array($GLOBALS['ERR_INVLOGIN'],0);
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$querycode = explode(":",$req->getResponseBody());
			$exit = $querycode[0];
			if ($exit == '0') { # se tutto ok
				return($querycode);
			} else { #altrimenti ritorna codice d'errore
				return($exit);
			}
		}else{	# user/pass non corrette
			if ($responsecode == 401){
				return array($GLOBALS['ERR_INVLOGIN'],0);
			}else{
				return array($GLOBALS['ERR_INVLOGIN'].">>$responsecode",0);
			}
		}
	}

}

function sms_geterror($exitcode){
$mess_errori = array(
	'0' => 'l\'operazione ha avuto esito positivo',
	'-1' => 'la data non e\' conforme',
	'-2' => 'la data e\' gia\' trascorsa',
	'-3' => 'il destinatario non e\' valido',
	'-4' => 'username o password non valide',
	'-5' => 'credito nazionale insufficiente',
	'-6' => 'parametro validita\' messaggio non corretto',
	'-7' => 'campo destinatario vuoto',
	'-8' => 'campo testo vuoto',
	'-9' => 'identificativo richiesta errato o numero destinatario errato',
	'-10' => 'campo notifica non valido',
	'-11' => 'invio differito superiore ai 10 giorni',
	'-12' => 'non sono stati ricevuti nuovi messaggi sms',
	'-13' => 'utenza non abilitata alla ricezione di SMS',
	'-14' => 'il mittente non e\' valido',
	'-15' => 'credito internazionale insufficiente',
	'-16' => 'credito notifiche insufficiente',
	'-17' => 'non sono stati inviati sms a partire dalla data indicata',
	'-18' => 'non sono stati inviati sms dalla utenza indicata',
	'-19' => 'mittente non valido',
	'-20' => 'errore di sistema 0',
	'-21' => 'errore di sistema 1',
	'-22' => 'errore di sistema 2',
	'-23' => 'errore di sistema 3',
	'-24' => 'errore di sistema 4',
	'-25' => 'errore di sistema 5: Can\'t connect to smsdb',
	'-38' => 'errore di sistema 5: Can\'t connect to smsdb',
	'-39' => 'errore di sistema 5: Can\'t connect to smsdb',
	'-40' => 'errore di sistema 5: Can\'t connect to smsdb',
	'-41' => 'errore di sistema 5: Can\'t connect to smsdb',
	'-44' => 'errore di sistema 5: Can\'t connect to smsdb',
	'-51' => 'errore di sistema 5: Can\'t connect to smsdb',
	'-26' => 'errore di sistema 6: Can\'t prepare statement',
	'-33' => 'errore di sistema 6: Can\'t prepare statement',
	'-34' => 'errore di sistema 6: Can\'t prepare statement',
	'-35' => 'errore di sistema 6: Can\'t prepare statement',
	'-36' => 'errore di sistema 6: Can\'t prepare statement',
	'-37' => 'errore di sistema 6: Can\'t prepare statement',
	'-42' => 'errore di sistema 6: Can\'t prepare statement',
	'-45' => 'errore di sistema 6: Can\'t prepare statement',
	'-47' => 'errore di sistema 6: Can\'t prepare statement',
	'-49' => 'errore di sistema 6: Can\'t prepare statement',
	'-52' => 'errore di sistema 6: Can\'t prepare statement',
	'-27' => 'errore di sistema 7: Can\'t execute statement',
	'-28' => 'errore di sistema 7: Can\'t execute statement',
	'-29' => 'errore di sistema 7: Can\'t execute statement',
	'-30' => 'errore di sistema 7: Can\'t execute statement',
	'-31' => 'errore di sistema 7: Can\'t execute statement',
	'-32' => 'errore di sistema 7: Can\'t execute statement',
	'-43' => 'errore di sistema 7: Can\'t execute statement',
	'-46' => 'errore di sistema 7: Can\'t execute statement',
	'-48' => 'errore di sistema 7: Can\'t execute statement',
	'-50' => 'errore di sistema 7: Can\'t execute statement',
	'-53' => 'errore di sistema 7: Can\'t execute statement',
	'-59' => 'credito insufficiente');
return $mess_errori{$exitcode};
}

?>
