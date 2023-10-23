<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>DB Locking</title>
<meta http-equiv=Content-Type content="text/html; charset=windows-1252">
<link href="/css/hyperstudy_v01.css" type=text/css rel=stylesheet>
<script src="libs/js/jquery/jquery-1.6.js" type="text/javascript"></script>
<meta content="MSHTML 6.00.2800.1226" name=GENERATOR>
<style type="text/css">

/*
 * Web20 Table Style written by Netway Media, http://www.netway-media.com
 */
table {
	border-collapse: collapse;
	border: 1px solid #666666;
	font: normal 11px verdana, arial, helvetica, sans-serif;
	color: #363636;
	background: #f6f6f6;
	text-align: left;
}

FORM TD {
	font-family: Arial, Helvetica, sans-serif;
	font-size: 8pt;
	vertical-align: bottom;
}

caption {
	text-align: center;
	font: bold 16px arial, helvetica, sans-serif;
	background: transparent;
	padding: 6px 4px 8px 0px;
	color: #CC00FF;
	text-transform: uppercase;
}

thead,tfoot {
	background: url(bg1.png) repeat-x;
	text-align: left;
	height: 30px;
}

thead th,tfoot th {
	padding: 5px;
}

table a {
	color: #333333;
	text-decoration: none;
}

table a:hover {
	text-decoration: underline;
}

tr.odd {
	background: #f1f1f1;
}

tbody th,tbody td {
	padding: 5px;
}

.SenzaBordosup {
	border-right-width: thin;
	border-bottom-width: thin;
	border-left-width: thin;
	border-top-style: none;
	border-right-style: solid;
	border-bottom-style: solid;
	border-left-style: solid;
	border-top-width: 0px;
	border-top-color: #FFFFFF;
	border-right-color: #000000;
	border-bottom-color: #000000;
	border-left-color: #000000;
}
</style>
<script type="text/javascript">
	// Ready functions
	$(document).ready(function() {
		$("#loading").hide();
		$("form").submit(function() {
			$("#loading").show();
		});

		$("input[name$='_INHERIT']").each(function() {
			$(this).inheritLock();
		});

		//$("input[name$='_INHERIT']").trigger("click");

	});

	$.fn.inheritLock = function() {
		$(this).unbind('click');
		$(this).bind('click', function() {
			var codpat = $(this).attr("name").split("_")[0];
			//alert($(this).attr("checked"));
			if ($(this).attr("checked") == "checked") {
				$("input[name^='" + codpat + "']").each(function() {
					if (!$(this).attr('name').match(/INHERIT/)) {
						$(this).attr("disabled", true);
						$(this).removeAttr("checked");
					}
				});
			} else {
				$("input[name^='" + codpat + "']").each(function() {
					//alert($(this).attr('name'));
					if (!$(this).attr('name').match(/INHERIT/)) {
						$(this).attr("disabled", false);

					}
				});
			}
			//alert($(this).attr("name")+" "+codpat+" "+$(this).attr("checked"));
		});
	};
</script>
</head>

<body>
	<center>
		<form name="form1" method="post">
			<!--    <input name="CENTRI" type="hidden" id="CENTRI" value="$str_centri">-->
			<!--    <input name="CRA" type="hidden" id="CRA" value="$str_cra">-->
			<!--    <input name="SCELTA" type="hidden" id="CRA" value="">-->
			<table border=1 cellpadding="2" cellspacing="0" bordercolor="#000000">
				<tbody>
					{if $centro!=""}
					<tr>
						<td colspan="5" align="center"><strong>'{$centro_name}'
								Patients List</strong></td>
						<td colspan="2" align="center"><a href="/uxmr/DB_Lock.php"><strong>Go
									to Centers list</strong></a></td>
					</tr>
					<tr>
						<td colspan="3" bgcolor="#00CCFF">Center DB Locks</td> {foreach
						$funzioni as $funzione} {if $funzione!='NEWPATIENT'}
						<td align=middle class="small">{if
							$centro_lock[$centro].$funzione==1} <img src="{$icon_file.red}" />{else}<img
							src="{$icon_file.green}" />{/if}
						</td> {/if} {/foreach}
						<td rowspan="2" align=middle bgcolor="#00CCFF">Inherit
							Center's Lock</td>
					</tr>
					<tr>
						<!-- tr>
				    		<td colspan="6" align=middle bgcolor="#00CCFF">{$testi.lock_patients}</td>
				    	</tr -->
						<td bgcolor="#00CCFF">Codpat</td>
						<td bgcolor="#00CCFF">SiteID</td>
						<td bgcolor="#00CCFF">SubjID</td>

						<td colspan="1" bgcolor="#00CCFF">Save/Send Forms</td>
						<td colspan="1" bgcolor="#00CCFF">Equery</td>
						<td colspan="1" bgcolor="#00CCFF">Obvious Corrections</td>
					</tr>
					{foreach $pazienti as $paziente}
					<tr>
						<td align=right class="small">{$paziente.CODPAT}</td>
						<td class="small">{$paziente.SITEID}</td>
						<td class="small">{$paziente.SUBJID}</td> {foreach $funzioni as
						$funzione} {if $funzione!='NEWPATIENT'}
						<td align=middle class="small"><input type="checkbox"
							name="{$paziente.CODPAT}_{$funzione}" {if $paziente.$funzione==1}
							checked="checked" {/if} {if $paziente.INHERIT==1}
							disabled="disabled"{/if}></td> {/if} {/foreach}
						<td align=middle class="small"><input type="checkbox"
							name="{$paziente.CODPAT}_INHERIT" {if $paziente.INHERIT==1}
							checked="checked"{/if}></td>
					</tr>
					{/foreach}
					<tr>
						<td colspan="6" align=center class="small"><input
							type="submit"
							style="color: #050; font: bold 80% 'trebuchet ms', helvetica, sans-serif; cursor: pointer;"
							name="Submit" value="Submit"> <input type="hidden"
							id="lock_type" name="lock_type" value="PER_CODPAT"> <input
							type="hidden" id="CENTRO" name="CENTRO" value="{$centro}">
							<div id="loading" align="center"
								style="display: none; align: center; text-align: center, width:220px; padding: 30px; margin: 20px;">
								<img src="../images/loading_bar.gif" />
							</div></td>
					</tr>
					{else}
					<tr>
						<td colspan="9" align="center"><strong>Centres</strong></td>
					</tr>
					<tr>
						<td rowspan="2" bgcolor="#00CCFF">{$testi.center}</td>
						<td rowspan="2" bgcolor="#00CCFF">{$testi.center_name}</td>
						<td rowspan="2" bgcolor="#00CCFF">{$testi.principal_investigator}</td>
						<td colspan="4" align=middle bgcolor="#00CCFF">{$testi.lock}</td>
						<td rowspan="2" align=middle bgcolor="#00CCFF">{$testi.go_to_patients}</td>
					</tr>
					<tr>
						<td colspan="1" bgcolor="#00CCFF">New Patients Enrollment</td>
						<td colspan="1" bgcolor="#00CCFF">Save/Send Forms</td>
						<td colspan="1" bgcolor="#00CCFF">Equery</td>
						<td colspan="1" bgcolor="#00CCFF">Obvious Corrections</td>

					</tr>
					{foreach $centri as $centro}
					<tr>
						<td align=right class="small">{$centro.ID_CENTER}</td>
						<td class="small">{$centro.CODE}</td>
						<td class="small">{$centro.PI}</td> {foreach $funzioni as
						$funzione}
						<td align=middle class="small">{if $funzione!='NEWPATIENT' &&
							$centro['OVERRIDED_'|cat:$funzione]>0} <img
							src="{$icon_file.yellow}"
							alt="Some patients has this function overwritten"
							title="Some patients has this function overwritten" /> {/if} <input
							type="checkbox" name="{$centro.ID_CENTER}_{$funzione}"
							{if $centro.$funzione==1} checked="checked"{/if}>
						</td> {/foreach}
						<!--select id="{$centro.ID_CENTER}_DBLOCK" name="{$centro.ID_CENTER}_DBLOCK">
			        		<option value="0" class="option_enabled" {if $centro.SOME_LOCK =="0"&&$centro.DBLOCK == "0"} selected{/if}>None</option>
			      			<option value="1" class="option_enabled" {if $centro.SOME_LOCK =="0"&&$centro.DBLOCK == "1"} selected{/if}>Disable eQuery</option>
			      			<option value="2" class="option_enabled" {if $centro.SOME_LOCK =="0"&&$centro.DBLOCK == "2"} selected{/if}>Disable Save/Send</option>
			      			<option value="3" class="option_enabled" {if $centro.SOME_LOCK =="0"&&$centro.DBLOCK == "3"} selected{/if}>Disable All</option>
      							{if $centro.SOME_LOCK !="0"}<option value="-1" class="option_enabled" style="color:red" selected>Some Patients Locked</option>{/if}
      					</select-->

						<td align=middle>
						{if $funzione!='NEWPATIENT' &&
							$centro['OVERRIDED_EQUAL']>0} <img
							src="{$icon_file.green}"
							alt="Some patients do not inherit DB Lock but have the same locks"
							title="Some patients do not inherit DB Lock but have the same locks" /> {/if} 
						
						<a href="?centro={$centro.ID_CENTER}"> <img
								id="{$centro.ID_CENTER}_LINK" src="{$icon_file.right}"
								width="18" height="18" border="0" />
						</a></td>
						<!-- td align=middle class="small"><input type="checkbox" name="{$centro.ID_CENTER}_SENDSAVE" {if $centro.SENDSAVE==1} checked = "checked"{/if}></td -->
						<!-- td align=middle class="small"><input type="checkbox" name="{$centro.ID_CENTER}_EQUERY" {if $centro.==1} checked = "checked"{/if}></td -->
					</tr>
					{/foreach}
					<tr>
						<td colspan="9" align=center class="small"><input
							type="submit"
							style="color: #050; font: bold 80% 'trebuchet ms', helvetica, sans-serif; cursor: pointer;"
							name="Submit" value="Submit"> <input type="hidden"
							id="lock_type" name="lock_type" value="PER_ID_CENTER">
							<div id="loading" align="center"
								style="display: none; align: center; text-align: center, width:220px; padding: 30px; margin: 20px;">
								<img src="../images/loading_bar.gif" />
							</div></td>
					</tr>
					{/if}
				</tbody>
			</table>
		</form>
		<p></p>
	</center>
</body>
</html>


