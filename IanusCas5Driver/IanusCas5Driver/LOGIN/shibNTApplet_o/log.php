<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="it" xml:lang="it" xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>.:: med3-service.cineca.it - Login ::.</title>
<!--link rel="shortcut icon" href="LOGIN/images/favicon.ico" type="image/x-icon" /-->
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="Description" content="Cineca WEB Login" />
<!-- link rel="stylesheet" type="text/css" href="LOGIN/css/login.css" /-->
<link rel="stylesheet" type="text/css" href="LOGIN/css/login.css" />
<script type="text/javascript" src="LOGIN/js/login.js"></script>
<script>
//enter refresh time in "minutes:seconds" Minutes should range from 0 to inifinity. Seconds should range from 0 to 59
var limit="10:00";
var url = window.location.href;  
url = url.replace("http://", "https://");
url = url.replace("login.php", "");
if (document.images){
var parselimit=limit.split(":");
parselimit=parselimit[0]*60+parselimit[1]*1;
}
function beginrefresh(){
if (!document.images){
return}
if (parselimit==1){
window.location.href = url;}
else{ 
parselimit-=1;
curmin=Math.floor(parselimit/60);
cursec=parselimit%60;
if (curmin!=0)
curtime=curmin+" minutes and "+cursec+" seconds left until page refresh!";
else
curtime=cursec+" seconds left until page refresh!";
window.status=curtime;
setTimeout("beginrefresh()",1000);
}
}

window.onload=beginrefresh
</script>

<script>
	function ShowMsg(username,pwd) {
		//alert("Your username is " + username + " and your password is "+pwd);
		document.forms[0].j_username.value = username;
		document.forms[0].j_password.value = pwd;
		document.forms[0].submit();
	} 
</script>

</head>
<body>

<center>
<table class="main-box" cellpadding="0" cellspacing="0">
	<!-- START - ROW TOP SX -->
	<tr>
		<td class="main-top-sx"></td>
		<td class="main-top"></td>
		<td class="main-top-dx"></td>
	</tr>
	<!-- FINE - ROW TOP SX -->

	
	<!-- START - ROW CORPO -->
	<tr>
		<td class="main-sx"></td>
		<td class="main-cx">
		
			<!-- START - Login Box -->
			<div class="login-box">
				<!-- START - Input Box -->
				<center>
				<div class="input-box">

					<form  action="https://idp-net.cineca.it/login.php" method="post">
					
	<input type='hidden' name='URL_HOST' value='MED3-SERVICE.CINECA.IT'/>
	<input type='hidden' name='CWD_DIR' value='/http/servizi/NET/med3-service/html'/>
	
					<table class="input-tb">
						<tr>
							<td style="height:70px;"><!-- <img src="images/cineca-logo-box.gif" /> --></td>
							<td></td>
						</tr>
						<tr>

							<td style="text-align:right;"><label for="j_username" class="bold">Nome utente&nbsp;&raquo;</label></td>
							<td class="center">
								<table style="margin:0 auto;" cellpadding="0" cellspacing="0">
									<tr>
										<td class="textbox-sx-user"></td>
										<td class="textbox-cx"><input type="text" class="textbox" id="j_username" name="j_username"/></td>
										<td class="textbox-dx"></td>
									</tr>

								</table>
							</td>
						</tr>
						<tr>
							<td style="text-align:right;"><label for="j_password" class="bold">Parola chiave&nbsp;&raquo;</label></td>
							<td class="center">
								<table style="margin:0 auto;" cellpadding="0" cellspacing="0">
									<tr>

										<td class="textbox-sx-pass"></td>
										<td class="textbox-cx"><input type="password" class="textbox" id="j_password" name="j_password"/></td>
										<td class="textbox-dx"></td>
									</tr>
								</table>
							</td>
						</tr>
						<!-- captcha -->
						<tr>

							<td></td>
							<td colspan="2" class="center">
								<table style="margin:0 auto;" cellpadding="0" cellspacing="0">
									<tr>
										<td id="TD-LOGIN-SX" class="button-sx"></td>
										<td id="TD-LOGIN-CX" class="button-cx">
											<input onmousedown="change_img('TD-LOGIN-SX', 'LOGIN/images/button-sx-dark-down.gif');change_img('TD-LOGIN-CX', 'LOGIN/images/button-cx-dark-down.gif');change_img('TD-LOGIN-DX', 'LOGIN/images/button-dx-dark-down.gif');" onmouseover="change_img('TD-LOGIN-SX', 'LOGIN/images/button-sx-dark-hover.gif');change_img('TD-LOGIN-CX', 'LOGIN/images/button-cx-dark-hover.gif');change_img('TD-LOGIN-DX', 'LOGIN/images/button-dx-dark-hover.gif');" onmouseout="change_img('TD-LOGIN-SX', 'LOGIN/images/button-sx-dark.gif');change_img('TD-LOGIN-CX', 'LOGIN/images/button-cx-dark.gif');change_img('TD-LOGIN-DX', 'LOGIN/images/button-dx-dark.gif');" type="submit" class="button" id="LOGIN" name="LOGIN" value="Accedi"/>
										</td>
										<td id="TD-LOGIN-DX" class="button-dx"></td>

										
										<td>&nbsp;</td>
										<td>&nbsp;</td>
										
										<td id="TD-PASS-SX" class="button-sx"></td>
										<td id="TD-PASS-CX" class="button-cx">
											<input onmousedown="change_img('TD-PASS-SX', 'LOGIN/images/button-sx-dark-down.gif');change_img('TD-PASS-CX', 'LOGIN/images/button-cx-dark-down.gif');change_img('TD-PASS-DX', 'LOGIN/images/button-dx-dark-down.gif');" onmouseover="change_img('TD-PASS-SX', 'LOGIN/images/button-sx-dark-hover.gif');change_img('TD-PASS-CX', 'LOGIN/images/button-cx-dark-hover.gif');change_img('TD-PASS-DX', 'LOGIN/images/button-dx-dark-hover.gif');" onmouseout="change_img('TD-PASS-SX', 'LOGIN/images/button-sx-dark.gif');change_img('TD-PASS-CX', 'LOGIN/images/button-cx-dark.gif');change_img('TD-PASS-DX', 'LOGIN/images/button-dx-dark.gif');" type="reset" class="button" id="CANCELLA" name="CANCELLA" value="Cancella"/>
										</td>
										<td id="TD-PASS-DX" class="button-dx"></td>
									</tr>
								</table>

							</td>
						</tr>
						<tr><td colspan="2" style="text-align:center;font-weight:bold;font-size:16px;color:#e60000;"></td></tr>
						<tr><td colspan="2" style="text-align:left;">&nbsp;&nbsp;&nbsp;<a class="link" href="forget_password/">Recupero Password ?</a></td></tr>
						<tr><td colspan="2"><applet code="NTUser.NTUserApplet" archive="ShibAuthApplet.jar" height="200" width="400" CODEBASE="." name="NTLogApplet" mayscript="mayscript"></applet></td></tr>
					</table>
					</form>
				</div>
				</center>

				<!-- FINE - Input Box -->
			</div>
			<!-- FINE - Login Box -->
		</td>
		<td class="main-dx"></td>
	</tr>
	<!-- FINE - ROW CORPO -->
	
	<!-- START - ROW BOTTOM -->
	<tr>

		<td class="main-bottom-sx"></td>
		<td class="main-bottom"></td>
		<td class="main-bottom-dx"></td>
	</tr>
	<!-- FINE - ROW BOTTOM -->
</table>
</center>
<div class="footer">&copy; Sistemi Informativi e Servizi per la Sanit&agrave; 2010 - Tutti i diritti riservati.</div>

<!-- out_code -->
</body>
</html>
