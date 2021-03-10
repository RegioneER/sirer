<?php 
global $MD5AdminMd5Crypt_chars;
$MD5AdminMd5Crypt_chars  = array( '.', '/');
$MD5AdminMd5Crypt_chars=array_merge($MD5AdminMd5Crypt_chars,range(0,9), range('A','Z'), range('a','z'));

function Check($conn, $userid, $plainPWD){
	$userid=strtoupper($userid);
	$password=strtoupper($password);
	$conn=new LoginDBConnection();
	$sql=new LoginSql($conn);
	$sql_query="select password from utenti where upper(userid)='$userid'";
	if ($sql->getRow($sql_query)){
		$db_password=$sql->row['PASSWORD'];
		$seeds=explode('$', $db_password);
		$seed=$seeds[2];
		if (MD5AdminMd5Crypt($plainPWD, $seed)==$db_password){
			return true;
		}
		else {
			return false;
		}
	}
	else return false;
}


function Md5PassStrSplit($str, $nr) {
	//Return an array with 1 less item then the one we have
	return array_slice(explode("-l-", chunk_split($str, $nr, '-l-')), 0, -1);
}

function Md5Hex2Raw( $str ){
	$chunks = Md5PassStrSplit($str, 2);
	$op='';
	for( $i = 0; $i < sizeof($chunks); $i++ ) {
		$op .= chr( hexdec( $chunks[$i] ) );
	}
	return $op;
}

function MD5AdminMd5Crypt($pwd, $salt=null){
	global $MD5AdminMd5Crypt_chars;
	$magic='$apr1$';

	if ($salt!=null) {
		$salt = $salt;
	} else {
		$salt = $MD5AdminMd5Crypt_chars[rand(0,count($MD5AdminMd5Crypt_chars))].$MD5AdminMd5Crypt_chars[rand(0,count($MD5AdminMd5Crypt_chars))].$MD5AdminMd5Crypt_chars[rand(0,count($MD5AdminMd5Crypt_chars))].".....";
		#join ( '', map { $MD5AdminMd5Crypt_chars[ int rand @MD5AdminMd5Crypt_chars ] } ( 0 .. 2 ) )  . ("." x 5);
	}
	$md5=md5($pwd.$salt.$pwd);
	$md5=Md5Hex2Raw($md5);

	$ctx=$pwd.$magic.$salt;
	for ($pl = strlen($pwd); $pl > 0; $pl -= 16) {
		$ctx.=substr($md5, 0, $pl > 16 ? 16 : $pl);
	}

	for ($i = strlen($pwd); $i; $i >>= 1) {
		if ($i & 1) $ctx.=pack("C", 0);
		else $ctx.=substr($pwd, 0, 1);
	}
	$ctx=md5($ctx);
	$ctx=Md5Hex2Raw($ctx);
	$final_ctx1=$ctx;
	for ($i = 0; $i < 1000; $i++) {
		$ctx1='';
		if ($i & 1) { $ctx1.=$pwd; }
		else { $ctx1.=substr($final_ctx1, 0, 16); }
		if ($i % 3) { $ctx1.=$salt; }
		if ($i % 7) { $ctx1.=$pwd; }
		if ($i & 1) { $ctx1.=substr($final_ctx1, 0, 16); }
		else { $ctx1.=$pwd; }
		$final_ctx1=md5($ctx1);
		$final_ctx1=Md5Hex2Raw($final_ctx1);
	}
	$final=$final_ctx1;
	#echo "<hr>".$final."<hr>";
	$passwd = '';
	$unp=unpack("C", (substr($final, 0, 1)));
	$unp1=unpack("C", (substr($final, 6, 1)));
	$unp2=unpack("C", (substr($final, 12, 1)));
	$passwd .= MD5AdminMd5Crypt_to64(floor($unp[1] << 16)
	| floor($unp1[1] << 8)
	| floor($unp2[1]), 4);
	#print "<br>".$passwd;
	$unp=unpack("C", (substr($final, 1, 1)));
	$unp1=unpack("C", (substr($final, 7, 1)));
	$unp2=unpack("C", (substr($final, 13, 1)));
	$passwd .= MD5AdminMd5Crypt_to64(floor($unp[1] << 16)
	| floor($unp1[1] << 8)
	| floor($unp2[1]), 4);
	$unp=unpack("C", (substr($final, 2, 1)));
	$unp1=unpack("C", (substr($final, 8, 1)));
	$unp2=unpack("C", (substr($final, 14, 1)));
	$passwd .= MD5AdminMd5Crypt_to64(floor($unp[1] << 16)
	| floor($unp1[1] << 8)
	| floor($unp2[1]), 4);
	$unp=unpack("C", (substr($final, 3, 1)));
	$unp1=unpack("C", (substr($final, 9, 1)));
	$unp2=unpack("C", (substr($final, 15, 1)));
	$passwd .= MD5AdminMd5Crypt_to64(floor($unp[1] << 16)
	| floor($unp1[1] << 8)
	| floor($unp2[1]), 4);
	$unp=unpack("C", (substr($final, 4, 1)));
	$unp1=unpack("C", (substr($final, 10, 1)));
	$unp2=unpack("C", (substr($final, 5, 1)));
	$passwd .= MD5AdminMd5Crypt_to64(floor($unp[1] << 16)
	| floor($unp1[1] << 8)
	| floor($unp2[1]), 4);
	$unp=unpack("C", substr($final, 11, 1));
	$passwd .= MD5AdminMd5Crypt_to64(floor($unp[1]), 2);
	return $magic.$salt.'$'.$passwd;
}

function MD5AdminMd5Crypt_to64 ($v, $n) {
	global $MD5AdminMd5Crypt_chars;
	$ret = '';

	while (--$n >= 0) {
		$ret .= $MD5AdminMd5Crypt_chars[ $v & 0x3f ];
		$v >>= 6;
	}
	return $ret;
}



?>