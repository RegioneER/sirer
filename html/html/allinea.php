<?php

ini_set("memory_limit","1000M");

function utf8ize($d) {
 if (is_array($d)) {
  foreach ($d as $k => $v) {
   $d[$k] = utf8ize($v);
  }
 } else if (is_string ($d)) {
  return utf8_encode($d);
 }
 return $d;
}

//$file="https://gcontino:xxx@nrc-padova.sissdev.cineca.it/NRC-CRMS/services/dm/rest/admin/configuration";
$file="config.json";
$harJson=file_get_contents($file);
$harJson= preg_replace('/[\x00-\x1F\x80-\xFF]/', '', $harJson);
$harJson=utf8ize($harJson);
$json=json_decode($harJson);
echo $_GET['callback']."(".json_encode($json).");";
die();