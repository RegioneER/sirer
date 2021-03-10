<!DOCTYPE img PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<title>Scheda di abilitazione</title>
	</head>
	<style>

  html, body {
    width: 210mm;
    height: 297mm;
margin: 10px auto;
  }
		h1{
			text-align:center;
		}
		h2{
			text-align:center;
		}
		h3{
			text-align:center;
		}
		#logoSite{
			float: left;
    		height: 50px;
    		padding-bottom:10px;
		}
		#logoCineca{
			float: right;
			height: 50px;
			padding-bottom:10px;
		}
		#utente{
			float:right;
		}
		#cred{
			margin-left:70mm;
		}
	</style>

	<body>
		<img id='logoSite' src='{$siteInfo.logoSite}'/>
		<img id='logoCineca' src="{$siteInfo.logoCineca}"/>
		<div style="clear:both"/>
		<h1>{$siteInfo.title}</h1>
		<h2>Scheda abilitazione</h2>
		<div id='utente'>
			A: {$user.NOME} {$user.COGNOME}<br/>
			Email: {$user.EMAIL}
		</div>
<br/><br/>
		<h3>Credenziali di accesso</h3>
		<hr>
		<div id='cred'>
			<label>Username</label>: {$user.USERID}<br/>
			<label>Password</label>: {$clearPassword}	
		</div>
		<hr>
		<div id='disclaimer'>
			{$siteInfo.disclaimer}
		</div>
		<div style="text-align:center">
		<a href="javascript:history.back()";>Go Back</a>
		</div>
	</body>
</html>