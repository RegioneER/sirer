<?php
error_reporting(E_ALL);


define("ADOBE_USERID", 2226946069); // amministrazione / utenti e gruppi / informazioni utente = principal-id
define("ADOBE_USER", "d.saraceno@cineca.it");
define("ADOBE_PWD", "y2wBxjQ3tX");
define("ADOBE_FOLDERID", 2247679948); // riunioni / riunioni personali / VCS = sco-id


$host = "vcs.adobeconnect.com";
$url = "https://" . $host . "/api/xml";

$ch = curl_init();
$xml = simplexml_load_string(curlCall($url, array('action' => 'login', 'login' => ADOBE_USER, 'password' => ADOBE_PWD), null, true));


if (!isset($_GET['sco_id'])) {
     $xml = simplexml_load_string(curlCall($url, array(
     'action' => 'sco-update',
     'name' => "SIRER - " . $_GET['meetingTitle'],
     'type' => 'meeting',
     'folder-id' => ADOBE_FOLDERID,
     'date-begin' => $_GET['dateStart'],
     'date-end' => $_GET['dateEnd']
     ), $cookie));
     
           
        
    if ($xml -> status->attributes()->code == 'invalid') {
        die("ERR:" . $xml->status -> invalid ->attributes()->subcode);
    } elseif ($xml -> status->attributes()->code == 'ok') {
        $url_call = $xml->sco->{'url-path'};
        $attributiCall = $xml->sco->attributes();
        $sco_id = $attributiCall['sco-id'];
     
        header("Location: new_meeting.php?sco_id={$sco_id}&url_call={$url_call}");
        die();
    }
} else {
    $sco_id = $_GET['sco_id']; 
    $url_call = $_GET['url_call']; 
    $xml = simplexml_load_string(curlCall($url, array('action' => 'permissions-update', 'acl-id' => $sco_id, 'principal-id' => 'public-access', 'permission-id' => 'view-hidden' ), $cookie));
    $xml = simplexml_load_string(curlCall($url, array('action' => 'permissions-update', 'acl-id' => $sco_id, 'principal-id' => ADOBE_USERID, 'permission-id' => 'host' ), $cookie));
}  

         
if ($xml -> status -> attributes() == 'ok') {
    die("OK:".$sco_id.":".$url_call);
} else {
    die("ERR:set-permissions:" . $sco_id);
}
curl_close($ch);

function curlCall($url, $params = array(), $cookie = null, $setCookie=false) {
    global $ch;
    curl_setopt($ch, CURLOPT_HEADER, true);
    
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);

    curl_setopt($ch, CURLOPT_MAXREDIRS, 5);

    curl_setopt($ch, CURLOPT_TIMEOUT, 5);

    if (count($params) > 0) {
        $query = http_build_query($params);
        curl_setopt($ch, CURLOPT_URL, "$url?$query");
    } else {
        curl_setopt($ch, CURLOPT_URL, $url);
    }
    if ($cookie) {
        //curl_setopt($ch, CURLOPT_COOKIE, "BREEZESESSION={$cookie}");
        curl_setopt($ch, CURLOPT_HTTPHEADER, array("Cookie: BREEZESESSION={$cookie}"));
        
    }
    $output = curl_exec($ch);
    
    //$info = curl_getinfo($ch);
    $header_size = curl_getinfo($ch, CURLINFO_HEADER_SIZE);
    $header = substr($output, 0, $header_size);
    if ($setCookie){
    $headers=explode("\r", $header);
    foreach ($headers as $key=>$val){
    	if (preg_match("!Set-Cookie:!", $val)){
    		global  $cookie;
    		$cookie=$val;
    		$cookie=str_replace('Set-Cookie: BREEZESESSION=','', $cookie);
    		$cookie=explode(";", $cookie)[0];
    		$cookie=trim($cookie);
    	}
    }
    }
    $body = substr($output, $header_size);
    $errno = curl_errno($ch);

    //curl_close($ch);
    return $body;

}

?>

<!DOCTYPE html>
<html>
    <head>
        <script src="https://code.jquery.com/jquery-3.1.1.min.js" type="text/javascript"></script>
    </head>
    <body></body>
</html>
