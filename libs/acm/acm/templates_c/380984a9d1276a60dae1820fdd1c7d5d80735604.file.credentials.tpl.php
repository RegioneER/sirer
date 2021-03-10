<?php /* Smarty version Smarty-3.0.7, created on 2018-05-22 15:26:12
         compiled from "./templates/credentials.tpl" */ ?>
<?php /*%%SmartyHeaderCode:8735426855b041a74f3a070-62582828%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '380984a9d1276a60dae1820fdd1c7d5d80735604' => 
    array (
      0 => './templates/credentials.tpl',
      1 => 1469451132,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '8735426855b041a74f3a070-62582828',
  'function' => 
  array (
  ),
  'has_nocache_code' => false,
)); /*/%%SmartyHeaderCode%%*/?>
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
		<img id='logoSite' src='<?php echo $_smarty_tpl->getVariable('siteInfo')->value['logoSite'];?>
'/>
		<img id='logoCineca' src="<?php echo $_smarty_tpl->getVariable('siteInfo')->value['logoCineca'];?>
"/>
		<div style="clear:both"/>
		<h1><?php echo $_smarty_tpl->getVariable('siteInfo')->value['title'];?>
</h1>
		<h2>Scheda abilitazione</h2>
		<div id='utente'>
			A: <?php echo $_smarty_tpl->getVariable('user')->value['NOME'];?>
 <?php echo $_smarty_tpl->getVariable('user')->value['COGNOME'];?>
<br/>
			Email: <?php echo $_smarty_tpl->getVariable('user')->value['EMAIL'];?>

		</div>
<br/><br/>
		<h3>Credenziali di accesso</h3>
		<hr>
		<div id='cred'>
			<label>Username</label>: <?php echo $_smarty_tpl->getVariable('user')->value['USERID'];?>
<br/>
			<label>Password</label>: <?php echo $_smarty_tpl->getVariable('clearPassword')->value;?>
	
		</div>
		<hr>
		<div id='disclaimer'>
			<?php echo $_smarty_tpl->getVariable('siteInfo')->value['disclaimer'];?>

		</div>
		<div style="text-align:center">
		<a href="javascript:history.back()";>Go Back</a>
		</div>
	</body>
</html>