<?php 
/*


http://www.policlinicogemelli.it/
http://www.policlinicogemelli.it/

i18n?plugin=common-ui&name=resources/web/dojo/pentaho/common/nls/messages
i18n?plugin=common-ui&name=resources/web/dojo/pentaho/common/nls/messages
i18n?plugin=common-ui&name=resources/web/dojo/pentaho/common/nls/messagesplugin=common-ui&name=resources/web/dojo/pentaho/common/nls/messages

i18n?plugin=common-ui&name=resources/web/dojo/pentaho/common/nls/messages
*/

session_start();

$username="public";
$password="test123;";

$request_uri=str_replace("/authzssl/pentaho-public/", "/pentaho/", $_SERVER ['REQUEST_URI']);
#$qs=$_SERVER['QUERY_STRING'];
#echo "<li>$request_uri - $qs</li>";
$request_uri=str_replace("authzssl/pentaho-public", "pentaho", $request_uri);
#echo "<li>$request_uri - $qs</li>";
$proxy_request_url="https://siss-cas.cineca.it".$request_uri;
#die($proxy_request_url);
/* Init CURL */
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $proxy_request_url);
curl_setopt($ch, CURLOPT_AUTOREFERER, 1);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_HEADER, 1);
curl_setopt($ch, CURLOPT_USERPWD, $username . ":" . $password);
curl_setopt($ch, CURLOPT_USERAGENT, $_SERVER['HTTP_USER_AGENT']);
curl_setopt($ch, CURLOPT_HTTPHEADER, array('Expect:'));
curl_setopt($ch, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
if (isset($_POST) && count($_POST)>0){
	$postbody="";
	foreach ($_POST as $k=>$v){
		if ($postbody!='') $postbody.="&";
		$postbody.=$k."=".$v;
	}
	curl_setopt($ch, CURLOPT_POST, 1);
	curl_setopt($ch, CURLOPT_POSTFIELDS,$postbody);
}


/* Collect and pass client request headers */
if(isset($_SERVER['HTTP_COOKIE']))
{
	$hdrs[]="Cookie: " . $_SERVER['HTTP_COOKIE'];
}
if(isset($_SERVER['HTTP_USER_AGENT']))
{
	$hdrs[]="User-Agent: " . $_SERVER['HTTP_USER_AGENT'];
}
curl_setopt($ch, CURLOPT_HTTPHEADER, $hdrs);
if ($_SESSION['add-cookies']!='') curl_setopt($ch, CURLOPT_COOKIE, $_SESSION['add-cookies']);
/* pass POST params */
if( sizeof($_POST) > 0 )
{
	curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($_POST));
}


$res = curl_exec($ch);
curl_close($ch);
list($headers, $body) = explode("\r\n\r\n", $res, 2);
$headers = explode("\r\n", $headers);
$hs = array();
foreach($headers as $header)
{
	if( false !== strpos($header, ':') )
	{ 
		list($h, $v) = explode(':', $header);
		$hs[$h][] = $v;
		if ($h=="Content-Type") header ("Content-Type: $v");
		if ($h=="Set-Cookie") $_SESSION['add-cookies']=$v;
	}
	else
	{
		$header1  = $header;
	}
}
/* set headers */
list($proto, $code, $text) = explode(' ', $header1);
header($_SERVER['SERVER_PROTOCOL'] . ' ' . $code . ' ' . $text);
foreach($proxied_headers as $hname)
{

	if( isset($hs[$hname]) )
	{
		foreach( $hs[$hname] as $v )
		{
			if( $hname === 'Set-Cookie' )
			{
				header($hname.": " . $v, false);
				
			}
			else
			{
				header($hname.": " . $v);
			}
		}
	}
}

$body=str_replace("/pentaho/", "/authzssl/pentaho-public/", $body);

die($body);
