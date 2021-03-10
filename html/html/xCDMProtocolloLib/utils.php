<?php

function SendJWTCURLGet($url, $jwtToken){
    //open connection
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $authorization = "Authorization: Bearer " . $jwtToken; // Prepare the authorisation token
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json', $authorization)); // Inject the token into the header
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 30);
    curl_setopt($ch, CURLOPT_TIMEOUT, 600); //timeout in seconds
    //execute call
    $result = curl_exec($ch);
    //close connection
    curl_close($ch);
    return $result;
}

function SendJWTCURLPost($url, $jwtToken, $postData = array()){
//extract data from the post
//set POST variables
//$url = 'http://domain.com/get-post.php';
//$fields = array(
//	'lname' => urlencode($_POST['last_name']),
//	'fname' => urlencode($_POST['first_name']),
//	'title' => urlencode($_POST['title']),
//	'company' => urlencode($_POST['institution']),
//	'age' => urlencode($_POST['age']),
//	'email' => urlencode($_POST['email']),
//	'phone' => urlencode($_POST['phone'])
//);
//url-ify the data for the POST
//foreach($fields as $key=>$value) { $fields_string .= $key.'='.$value.'&'; }
//rtrim($fields_string, '&');

    //open connection
    $ch = curl_init();
    //set the url, number of POST vars, POST data
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $authorization = "Authorization: Bearer " . $jwtToken; // Prepare the authorisation token
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: multipart/form-data', $authorization)); // Inject the token into the header
    //curl_setopt($ch, CURLOPT_POST, count($postData));
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $postData);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 30);
    curl_setopt($ch, CURLOPT_TIMEOUT, 600); //timeout in seconds
    //execute call
    $result = curl_exec($ch);
    //close connection
    curl_close($ch);
    return $result;
}
function SendJWTCURLPostJson($url, $jwtToken, $jsonBody=""){
    //open connection
    $ch = curl_init();
    //set the url, number of POST vars, POST data
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $authorization = "Authorization: Bearer " . $jwtToken; // Prepare the authorisation token
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json', $authorization)); // Inject the token into the header
    //curl_setopt($ch, CURLOPT_POST, count($postData));
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $jsonBody);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 30);
    curl_setopt($ch, CURLOPT_TIMEOUT, 600); //timeout in seconds
    //execute call
    $result = curl_exec($ch);
    //close connection
    curl_close($ch);
    return $result;
}
