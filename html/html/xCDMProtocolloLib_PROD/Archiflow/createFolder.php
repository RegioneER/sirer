<?php
/**
 * Created by PhpStorm.
 * User: d.mengoli
 * Date: 16/05/2019
 * Time: 15:31
 */

require_once __DIR__ . '/authentication.php';

echo "NA";//ARCHIFLOW NON UTILIZZA IL CREATEFOLDER, RESTITUIAMO NA PER UNIFORMARE INTERFACCIAMENTO - vmazzeo 24.09.2019

/*
print_r($response);
if (!is_object($response)) {
    $response = json_decode($response);
}

foreach ($response as $item){
    print_r($item);
    echo "\n";
}
*/


/*
$decoded = JWT::decode($jwt, $publicKey, array('RS256'));

// NOTE: This will now be an object instead of an associative array. To get
// an associative array, you will need to cast it as such:

$decoded_array = (array) $decoded;
echo "Decode:\n" . print_r($decoded_array, true) . "\n";

*/

