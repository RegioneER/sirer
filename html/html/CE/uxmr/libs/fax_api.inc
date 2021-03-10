<?php

/**
 * @package Fax
 */

#
# Cineca FAX PHP API, Versione 0.80
#

require_once 'libs/Client.php';
require_once "libs/Request.php";

#Costanti ERRORI
$GLOBALS['ERR_OK'] = 0;
$GLOBALS['ERR_LOGIN']= -1;
$GLOBALS['ERR_DB'] = -2;
$GLOBALS['ERR_UNAUTHORIZED'] = -3;
$GLOBALS['ERR_CREDIT'] = -4;
$GLOBALS['ERR_DESTINATION'] = -5;
$GLOBALS['ERR_NO_ORDER'] = -6;
$GLOBALS['ERR_UNDEFINED_TYPE'] = -7;
$GLOBALS['ERR_NO_PARAMETER'] = -8;
$GLOBALS['ERR_UIN_INCORRECT'] = -9;
$GLOBALS['ERR_DB_ZERO_DELETE'] = -10;
$GLOBALS['ERR_FAX_INTERNATIONAL'] = -11;
$GLOBALS['ERR_FAX_PAY_NUMBER'] = -12;


$GLOBALS['ERR_OPEN_ATTACH'] = -49;
$GLOBALS['ERR_ATTACH'] = -50;
$GLOBALS['ERR_FILE_NOT_SUPPORTED'] = -52;
$GLOBALS['ERR_COMPATIBILTY'] = -53;
$GLOBALS['ERR_NO_FILE'] = -54;

$GLOBALS['ERR_SYSTEM'] = -59;
$GLOBALS['ERR_DATE'] = -60;
$GLOBALS['ERR_NO_FAX_TO_READ'] = -62;
$GLOBALS['ERR_NO_FAX_NUMBER'] = -63;

$GLOBALS['CINECA_FAX_url_send'] = 'https://mcgw.cineca.com/fax/cgi-bin/sendfax.pl';
$GLOBALS['CINECA_FAX_url_status_user'] 	= 'https://mcgw.cineca.com/fax/cgi-bin/statususer.pl';
$GLOBALS['CINECA_FAX_url_detail'] = 'https://mcgw.cineca.com/fax/cgi-bin/statusspool.pl';
$GLOBALS['CINECA_FAX_url_document'] = 'https://mcgw.cineca.com/fax/cgi-bin/getdocument.pl';
$GLOBALS['CINECA_FAX_url_delete']= 'https://mcgw.cineca.com/fax/cgi-bin/deleteorder.pl';
$GLOBALS['CINECA_FAX_url_status_order'] = 'https://mcgw.cineca.com/fax/cgi-bin/statusorder.pl';
$GLOBALS['CINECA_FAX_url_credit'] ='https://mcgw.cineca.com/fax/cgi-bin/checkcredit.pl';
$GLOBALS['CINECA_FAX_url_receive'] ='https://mcgw.cineca.com/fax/cgi-bin/getincoming.pl';
$GLOBALS['CINECA_FAX_url_receive_new'] ='https://mcgw.cineca.com/fax/cgi-bin/get_next_incoming_info.pl';
$GLOBALS['CINECA_FAX_url_num_fax_in'] ='https://mcgw.cineca.com/fax/cgi-bin/countfax_in.pl';
$GLOBALS['CINECA_FAX_url_fax_receive_info'] = 'https://mcgw.cineca.com/fax/cgi-bin/getincoming_info.pl';
$GLOBALS['CINECA_FAX_url_faxin_numbers'] = 'https://mcgw.cineca.com/fax/cgi-bin/getfax_in.pl';
$GLOBALS['CINECA_FAX_url_fax_preferences'] = 'https://mcgw.cineca.com/fax/cgi-bin/getpreferences.pl';
$GLOBALS['CINECA_FAX_url_fax_preferences_mod'] = 'https://mcgw.cineca.com/fax/cgi-bin/modpreferences.pl';
$GLOBALS['CINECA_FAX_url_fax_notread'] = 'https://mcgw.cineca.com/fax/cgi-bin/fax_notread.pl';


/* ****************************************************************************************
	# send_fax()
	
	# Funzione per l'invio di una lettera
	# Input:
	# - $user = il codice utente
	# - $fname = sara' il path dove risiede il file di testo da spedire
	# - $ptr_destinatari = puntatore ad un array dei dati(indirizzo, numero civico ... )
	#	inerenti ai dei destinatari;
	#
	# Output: 
	#	- UIN dell'ordine se la spedizione e' effettuata con successo
	#	- Codice di errore (numero minore di 0) se la spedizione e' errata
	#
	# UIN = UNIVERSAL IDENTIFIER NUMBER
**************************************************************************************** */

function send_fax($user, $password, $fname,$id_servizio,$oggetto,$destinatari = array(), $test, $priorita, $data_sched, $commento,$esito_email) {
	$str_destinatari = create_destinatari($destinatari);
//echo $str_destinatari."<hr>";
 	if($str_destinatari == '') {
		return($ERR_DESTINATION);
	}else {
		$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_send']);
//		echo " Check user authentication<hr>";
		$req->setBasicAuth($user, $password);
		$req->setMethod(HTTP_REQUEST_METHOD_POST);
		
		#---- Creo i dati per il POST
		$req->addPostData('mittente', $user);
		$req->addFile('upfile', $fname);
		$req->addPostData('oggetto', $oggetto);
		$req->addPostData('destinatari', $str_destinatari);
		$req->addPostData('id_servizio', $id_servizio);
		$req->addPostData('test', $test);
		$req->addPostData('data', $data_sched);
		$req->addPostData('commento', $commento);
		$req->addPostData('priorita', $priorita);
		$req->addPostData('esito_email', $esito_email);	
		#----

		$response = $req->sendRequest();
		if (PEAR::isError($response)) {
			return($GLOBALS['ERR_LOGIN']);
		}else{
			$responsecode = $req->getResponseCode();
			if ($responsecode == 200){
				$uin = $req->getResponseBody();
				return($uin);
			}else{
				if ($responsecode == 401){
					return($GLOBALS['ERR_UNAUTHORIZED']);
				}else{
					return($GLOBALS['ERR_LOGIN'].">>$responsecode");
				}
			}
		}
		
	}
}


/* ****************************************************************************************
	# query_status_user_order()

	# Funzione per conoscere lo stato di un ordine
	# Input:  - user di cui si vuole conoscere gli ordini
	#	  - riga di partenza
	#	  - numero massimo di righe restituite
	#
	# Output: Array contenente  
	#	-$status_order[0] = esito richiesta
	#	-$status_order[1...n] : 
	#		.stringa contenente le informazioni nella forma idordine::status::UIN
	#		.vuoto se vi sono stati errori

	# UIN =  UNIVERSAL IDENTIFIER NUMBER
**************************************************************************************** */

function query_status_user_order($user, $password, $start_record, $max_rows,$order_by,$sort_order){

	$status_order = array();
	$status = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_status_user']);
	$req->setBasicAuth($user, $password);// Check user authentication
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$req->addPostData('start', $start_record);
	$req->addPostData('numrows', $max_rows);
	$req->addPostData('orderby', $order_by);
	$req->addPostData('sortorder', $sort_order);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		$status_order[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$status = explode("x80",$req->getResponseBody());
			$status_order[0] = $GLOBALS['ERR_OK'];
			$status_order[1] = $status;
		}else{
			if ($responsecode == 401){
				$status_order[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$status_order[1] = $responsecode;
			}else{
				$status_order[0] = $responsecode;
			}
		}
	}
	return($status_order);
}

/* ****************************************************************************************
	#query_status_spool()

	#Funzione che permette di sapere le lettere in spool associati all'UIN dato in input
	#restituisce l'id_spool e lo status associato, nel seguente formato
	#
	#Input:  - UIN (UIN = UNIVERSAL IDENTIFIER NUMBER)
	#
	#Output: Array contenente  
	#	-$query_spool[0] = esito richiesta
	#	-$query_spool[1] : 
	#		.array di stringhe contenente le informazioni nella forma  <nome><cognome>::<status>::<faxnumber>::faxgw_done::idspool
	#	 	.vuoto se vi sono stati errori
**************************************************************************************** */

function query_status_spool($user, $password, $uin, $start_record, $max_rows,$orderby,$sort_order){

	$query_spool = array();
	$info_status_spool = array();

	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_detail']);
	// Check user authentication
	$req->setBasicAuth($user, $password);
	if ($uin != ''){
		$req->setMethod(HTTP_REQUEST_METHOD_POST);
		$req->addPostData('uin', $uin);
		$req->addPostData('user', $user);
		$req->addPostData('orderby',$orderby);
		$req->addPostData('sortorder', $sort_order);
		$req->addPostData('start', $start_record);
		$req->addPostData('maxrow', $max_rows);
		$response = $req->sendRequest();
		if (PEAR::isError($response)) {
			$query_spool[0] = $GLOBALS['ERR_LOGIN'];
		}else{
			$responsecode=$req->getResponseCode();
			if ($responsecode == 200){
				$info_status_spool = explode("!",$req->getResponseBody());
				if ($info_status_spool[0] < 0 ){
					$query_spool[0] = $info_status_spool[0];
				}else{
					$query_spool[0] = $GLOBALS['ERR_OK'];
					$query_spool[1] = $info_status_spool;
				}
			}else{
				if ($responsecode == 401){
					$query_spool[0] = $GLOBALS['ERR_UNAUTHORIZED'];
					$query_spool[1] = $responsecode;
				}else{
					$query_spool[0] = $responsecode;
				}
			}
		}
	}else{
		$query_spool[0] = $GLOBALS['$ERR_NO_PARAMETER'];
	}
	return($query_spool);
}


/* ****************************************************************************************
	# query_status_user_single_order()
	
	# Funzione per conoscere lo stato di un ordine
	# Input:  
	#	- username di cui si vuole conoscere gli ordini
	# 	- password dello username
	#	- uin dell'ordine di cui si vuole sapere le informazioni
	#
	# Output:
	#	- esito e stato dell' ordini in formato stringa
	#	 idordine::status::UIN::quantita::received_date::scheduled_date::sent_date::credit_spent::comment
	#	- esito e stringa vuota (se vi sono errori)
	
	# UIN =  UNIVERSAL IDENTIFIER NUMBER
 **************************************************************************************** */

function query_status_user_single_order($user, $password, $uin){
	$status_order = array();
	$status = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_status_order']);
	// Check user authentication
	$req->setBasicAuth($user, $password);
	if ($uin != ''){
		$req->setMethod(HTTP_REQUEST_METHOD_POST);
		$req->addPostData('uin', $uin);
		$req->addPostData('user', $user);
		$response = $req->sendRequest();
		if (PEAR::isError($response)) {
			$status_order[0] = $GLOBALS['ERR_LOGIN'];
		}else{
			$responsecode=$req->getResponseCode();
			if ($responsecode == 200){
				$status = explode("!",$req->getResponseBody());
				$status_order[0] = $GLOBALS['ERR_OK'];
				$status_order[1] = $status;
			}else{
				if ($responsecode == 401){
					$status_order[0] = $GLOBALS['ERR_UNAUTHORIZED'];
					$status_order[1] = $responsecode;
				}else{
					$status_order[0] = $responsecode;
				}
			}
		}
	}else{
		$status_order[0] = $GLOBALS['$ERR_NO_PARAMETER'];
	}
	return($status_order);
}
#--------


/*****************************************************************************************
	# create_destinatari()

	# Funzione per la creazione di una stringa contenente i dati dei 
	# destinatari delle lettere
	#
	# Input:  - Array di hash contenente i dati dei destinatari
	#
	# Output: - Stringa nel formato nomecognome*numerofax*company_receiver!
**************************************************************************************** */

function create_destinatari($destinatari = array()){

	$str_destinatari = '';
	while (list($idx, $single_dest) = each($destinatari)){
//		echo $idx;
//		print_r ($single_dest) ;
		$str_destinatari .= 
					$single_dest['receiver']."*".
					$single_dest['faxnumber']."*".
					$single_dest['company_receiver'].
					"!";
	}
 	return ($str_destinatari);

}

/*****************************************************************************************
	# fax_out_get_document()
	
	# Funzione che permette il download del file utilizzato per la spedizione
	# Input:  
	#		- username
	#		- password 
	#		- uin
	# Output: 
	#		-$request_file[0] = esito richiesta
	#		-$request_file[1] = .stringa contenente il file zippato (Content-type:application/zip)
	#		 	      .vuoto se vi sono stati errori
**************************************************************************************** */

function fax_out_get_document($user, $password,$uin){
	
	$request_file = array();

	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_document']);
	// Check user authentication
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	
	#---- Creo i dati per il POST
	$req->addPostData('user', $user);
	$req->addPostData('uin', $uin);
	#----
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		$request_file[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$doc= $req->getResponseBody();
			if ($doc < 0 ){
				$request_file[0] = $GLOBALS['ERR_NO_FILE'];
			}else{
				$request_file[0] = $GLOBALS['ERR_OK'];
				$request_file[1] = $doc;
			}
		}else{
			if ($responsecode == 401){
				$request_file[0] = $GLOBALS['ERR_UNAUTHORIZED'];
			}else{
				$request_file[0] = $GLOBALS['ERR_LOGIN'];
				$request_file[0] = $request_file[0].">>$responsecode";
			}
		}
	}
	return($request_file);
}


/* ****************************************************************************************
	# fax_in_get_document()
	
	# unzione che permette il download del file tiff corrispondete al FAX ricevuto
	# Input:  
	#	- username
	#	- password 
	#	- fax_number
	#	- idspool
	# Output: 
	#	-$request_file[0] = esito richiesta
	#	-$request_file[1] = stringa contenente il file, vuoto se vi sono stati errori
 ****************************************************************************************** */

function fax_in_get_document($user, $password, $fax_number, $idspool){
	
	$request_file = array();

	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_document']);
	// Check user authentication
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	
	#---- Creo i dati per il POST
	$req->addPostData('user', $user);
	$req->addPostData('fax_number', $faxnumber);
	$req->addPostData('idspool', $idspool);
	#----
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		$request_file[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$doc= $req->getResponseBody();
			if ($doc < 0 ){
				$request_file[0] = $GLOBALS['ERR_NO_FILE'];
			}else{
				$request_file[0] = $GLOBALS['ERR_OK'];
				$request_file[1] = $doc;
			}
		}else{
			if ($responsecode == 401){
				$request_file[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				
			}else{
				$request_file[0] = $GLOBALS['ERR_LOGIN'];
				$request_file[0] = $request_file[0].">>$responsecode";
			}
		}
	}
	return($request_file);
}


/* ****************************************************************************************
	# delete_order()
	
	# Funzione che permette la cancellazione di un ordine che è ancora in stato di 
	# waiting,Se in working o delivered, l'operazione non verrà effettuata.
	# Input:  - username
	#	  - password 
	#	  - uin
	# Output:  0  se l'ordine non è stato cancellato 
	#	   1  se l'ordine è stato cancellato 
	#	   ERR_DB  se cè un errore nel DB
	#	   ERR_UIN_INCORRECT  in caso di UIN mancante
 ****************************************************************************************** */

function delete_order($user, $password,$uin){
	
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_delete']);
	// Check user authentication
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	
	#---- Creo i dati per il POST
	$req->addPostData('user', $user);
	$req->addPostData('uin', $uin);
	#----
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		$exitcode = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode = $req->getResponseCode();
		if ($responsecode == 200){
			$exitcode = $req->getResponseBody();
		}else{
			if ($responsecode == 401){
				$exitcode = $GLOBALS['ERR_UNAUTHORIZED'];
			}else{
				$exitcode = $GLOBALS['ERR_LOGIN'].">>$responsecode";
			}
		}
	}
	return($exitcode);
}

/* ****************************************************************************************
	# check_credit()	

	# Funzione per il controllo del credito:il credito viene e' dettagliato per 
	# tipologia di spedizione
	
	# Output: -$check[0] = esito richiesta
	#	  	  -$check[1] : 
	#		.array associativo nella forma $credito_servizio['idservizio'] = credito
	#	 	.vuoto se vi sono stati errori
 ****************************************************************************************** */

function check_credit($user, $password){
	
	$check = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_credit']);
 	// Check user authentication
 	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$response = $req->sendRequest();
	
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check[0] = $GLOBALS['ERR_LOGIN'];
//echo $check[0]."<hr>";
//echo $check[1]."<hr>";
//echo " Uno <hr>";
		return($check);
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$retcode = explode("!",$req->getResponseBody());
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $retcode;
//echo $check[0]."<hr>";
//print_r($check[1]);
//echo " Due <hr>";
			return($check);
		}else{
			if ($responsecode == 401){
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;
//echo $check[0]."<hr>";
//echo $check[1]."<hr>";
//echo " Tre <hr>";
				return($check);
			}else{
				$check[0] = $responsecode;
//echo $check[0]."<hr>";
//echo $check[1]."<hr>";
//echo " quattro <hr>";
				return($check);
			}
		}
	}
//echo $check[0]."<hr>";
//echo $check[1]."<hr>";
}
#---------



/* ****************************************************************************************
	# count_fax_in ()
	# Funzione per ottenere il numero totale di fax in ingresso ricevuti e il numero di fax
	# ancora da leggere su un dato numero di FAX

	# Input:
	# - username
	# - password
	# - numero di fax in ingresso

	# Output:
	# - Esito della richiesta
	# - $retcode[0] = numero totale di fax ricevuti dall'inizio del servizio
	# - $retcode[1] = numero di fax ricevuti ancora da leggere
* ***************************************************************************************** */

function count_fax_in($user, $password, $fax_number){

	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_num_fax_in']);
	# autenticazione
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$req->addPostData('fax_number', $fax_number);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$retcode = explode("::",$req->getResponseBody());
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $retcode;
		}else{
			if ($responsecode == 401){
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;
			}else{
				$check[0] = $responsecode;
			}
		}
	}
	return($check);
}


/* ****************************************************************************************
	# get_faxin_new ()
	# Funzione per ottenere dalla coda dei fax in ingresso, il primo documento
	# fax ancora da leggere.
	# Una volta che il fax e' stato scaricato viene marcato come letto
	# Input: 
	#	- username
	#	- password 
	#	- numero di fax in ingresso
	# Output: 
	#	- $check[0] = Status
	#	- $check[1] = file tiff corrispondente al documento
* ***************************************************************************************** */

function get_faxin_new($user, $password, $fax_number) {
	
	$check = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_receive_new']);
	# autenticazione
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$req->addPostData('fax_number', $fax_number);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$file = explode("::",$req->getResponseBody());
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $file;
		}else{
			if ($responsecode == 401){# user/pass non corrette
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;

			}else{
				$check[0] = $responsecode;
			}
		}
	}
	return($check);
}



/* ****************************************************************************************
	# query_fax_receive_info ()
	# Funzione per ottenere le informazioni (non il documento) sui Fax ricevuti
	# in base al numero in ingresso
	# Input: 
	#	- username
	#	- password 
	#	- numero di fax in ingresso
	#	- record di partenza
	#	- massimo numero di righe restituite
	#	- Ordinato per ('idspool','num_sender','received_ts')
	#	- Ordine crescente (ASC) o decrescente (DESC)
	# Output: 
	#	- Status
	#	- Array contenente le informazioni sul fax
 **************************************************************************************** */

function query_fax_receive_info($user, $password, $fax_number, $start_record, $max_rows,$order_by,$sort_order){
	
	$check = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_fax_receive_info']);
	# autenticazione
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$req->addPostData('fax_number', $fax_number);
	$req->addPostData('start', $start_record);
	$req->addPostData('numrows', $max_rows);
	$req->addPostData('orderby', $order_by);
	$req->addPostData('sortorder', $sort_order);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$info = explode("x80",$req->getResponseBody());
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $info;
		}else{
			if ($responsecode == 401){# user/pass non corrette
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;
			}else{
				$check[0] = $responsecode;
			}
		}
	}
	return($check);
}



/* ****************************************************************************************
	# get_fax_in_numbers()
	# ritorna tutti i numeri di fax in ingresso associati al $user
	# Input:
	#	- username
	#	- password 
	# Output:
	#	- check[0] = status
	#	- check[1] = array numeri telefono
 ****************************************************************************************** */
function get_faxin_numbers($user, $password){
	$check = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_faxin_numbers']);
	# autenticazione
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$info = explode(';',$req->getResponseBody());
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $info;
		}else{
			if ($responsecode == 401){# user/pass non corrette
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;
			}else{
				$check[0] = $responsecode;
			}
		}
	}
	return($check);
}



/* ****************************************************************************************
	# get_fax_preferences()
	# ritorna tutti i settaggi per i numeri di fax in ingresso associati al $user
	# Input:
	#	- username
	#	- password 
	#	- fax_number ( non obbligatorio )
	# Output:
	#		- $default_view = numero fax in ingresso visualizzato di default
	#		- $default_send = numero fax in ingresso utilizzato per le spedizioni
	#		- @info_fax_in_number = array di stringhe cosi' formate: fax_number::notifica::email_notifica
	#	se dato in input un $fax_number allora:
	#		- $default_view = numero fax in ingresso visualizzato di default
	#		- $default_send = numero fax in ingresso utilizzato per le spedizioni
	#		- info_fax_in_number = stringa cosi' formate: fax_number::notifica::email_notifica
****************************************************************************************** */

function get_fax_preferences($user, $password, $fax_number){
	$check = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_fax_preferences']);
	# autenticazione
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check[0] = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$info_fax_in_number = array();
			list($default_view, $default_send, $str_info_fax_in_number) = explode(';',$req->getResponseBody());
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $default_view;
			$check[2] = $default_send;
			$info_fax_in_number = explode("x80",$str_info_fax_in_number); #str_info_fax_in_number
			if ($fax_number != ''){
				$check[3] = $info_fax_in_number[0];
			}else{
				$check[3] = $info_fax_in_number;
			}
		}else{
			if ($responsecode == 401){# user/pass non corrette
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;
			}else{
				$check[0] = $responsecode;
			}
		}
	}
	return($check);
}




/* ****************************************************************************************
	# mod_fax_preferences()
	# modifica i settaggi per il numero di fax in ingresso dato in input
	# Input:
	#	- username
	#	- password 
	#	- fax_number
	#	- esito
	#	- email_esito
	#	- default
	# Output:
	#	- $check[0] = Stato (Se l'aggiornamento e' andato a buon fine resituisce $ERR_OK)
	#	- $check[1] = Se l'aggiornamento si e' completato con errore restituisce il codice di errore
	#		
****************************************************************************************** */

function mod_fax_preference($user, $password,$fax_number,$esito,$email_esito,$default_view,$default_send){

	$check = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_fax_preferences_mod']);
	# autenticazione
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$req->addPostData('fax_number', $fax_number);
	$req->addPostData('esito', $esito);
	$req->addPostData('email_esito', $email_esito);
	$req->addPostData('default_view', $default_view);
	$req->addPostData('default_send', $default_send);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $req->getResponseBody();
		}else{
			if ($responsecode == 401){# user/pass non corrette
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;
			}else{
				$check[0] = $responsecode;
			}
		}
	}
	return($check);
}

/* ****************************************************************************************
	# set_fax_notread()
	# imposta a "non letto" il fax ricevuto corrispondente a $idspool
	#	- username
	#	- password 
	#	- idspool
* **************************************************************************************** */

function set_fax_notread($user, $password,$idspool){

	$check = array();
	$req =& new HTTP_Request($GLOBALS['CINECA_FAX_url_fax_notread']);
	# autenticazione
	$req->setBasicAuth($user, $password);
	$req->setMethod(HTTP_REQUEST_METHOD_POST);
	$req->addPostData('user', $user);
	$req->addPostData('idspool', $idspool);
	$response = $req->sendRequest();
	if (PEAR::isError($response)) {
		# user/pass non corrette
 		$check = $GLOBALS['ERR_LOGIN'];
	}else{
		$responsecode=$req->getResponseCode();
		if ($responsecode == 200){
			$check[0] = $GLOBALS['ERR_OK'];
			$check[1] = $req->getResponseBody();
		}else{
			if ($responsecode == 401){# user/pass non corrette
				$check[0] = $GLOBALS['ERR_UNAUTHORIZED'];
				$check[1] = $responsecode;
			}else{
				$check[0] = $responsecode;
			}
		}
	}
	return($check);
}




/* ****************************************************************************************
	# fax_geterror()

	# Funzione per visualizzare gli exitcode
	# Input:  - exitcode 
	# Output: - stringa contenente il messaggio di errore associato all'exitcode
 **************************************************************************************** */

function fax_geterror($exitcode){

	$mess_errori = array(
		$GLOBALS['ERR_OK'] => "l'operazione ha avuto esito positivo",
		$GLOBALS['ERR_LOGIN'] => "username o password non valide",
		$GLOBALS['ERR_DB'] => "Errore Connessione DB",
		$GLOBALS['ERR_UNAUTHORIZED'] => "l'utente non e' abilitato al servizio",
		$GLOBALS['ERR_CREDIT'] => "Credito insufficiente",
		$GLOBALS['ERR_DESTINATION'] => "Errore nei dati necessari alla composizione della destinazione",
		$GLOBALS['ERR_NO_ORDER'] => "Non ci sono ordini attivi",
		$GLOBALS['ERR_UNDEFINED_TYPE'] => "Spedizione di default non definita per l'utente",
		$GLOBALS['ERR_NO_PARAMETER'] => "Nessun parametro in ingresso",
		$GLOBALS['ERR_UIN_INCORRECT'] => "UIN fornito non corretto o inesistente",
		$GLOBALS['ERR_DB_ZERO_DELETE'] => "Nessun ordine cancellato, controllare i dati immessi",
		$GLOBALS['ERR_FAX_INTERNATIONAL'] => "Destinatario con numero internazionale",
		$GLOBALS['ERR_FAX_PAY_NUMBER'] => "Destinatario con numero a pagamento",
		$GLOBALS['ERR_OPEN_ATTACH'] => "Problemi nell' apertura dell'allegato",
		$GLOBALS['ERR_ATTACH'] => "Allegato non corretto",
		$GLOBALS['ERR_FILE_NOT_SUPPORTED'] => "Errore durante la conversione del file da spedire",
		$GLOBALS['ERR_COMPATIBILTY'] => "Il tipo di invio selezionata non è compatibile con il tipo di file",
		$GLOBALS['ERR_NO_FILE'] => "File non presente nel sistema",
		$GLOBALS['ERR_SYSTEM'] => "Errore di Sistema",
		$GLOBALS['ERR_DATE'] => "La data inserita non è valida",
		$GLOBALS['ERR_NO_FAX_TO_READ'] => "Non vi sono nuovi fax da prelevare",
		$GLOBALS['ERR_NO_FAX_NUMBER'] => "L 'utente non ha numeri di fax in ingresso"
    );
	return $mess_errori[$exitcode];
}



?>
