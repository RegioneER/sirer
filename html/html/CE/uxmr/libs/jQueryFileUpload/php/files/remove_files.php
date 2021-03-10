<?php
//removeFileURL

$path = str_replace("demo/remove_files.php", "uploaded_files/", $_SERVER["SCRIPT_FILENAME"]);
$path = $path.$_REQUEST['application_token'].'/';
/* Don't do this in production code, it is insecure.   You need to sanitize the applicationToken
 * before considering using it.
 */

while (list($key, $val) = each($_REQUEST['file'])) {
    if (file_exists($path.$val)) {
    	unlink($path.$val);
    }
}

echo "<success/>";
?>