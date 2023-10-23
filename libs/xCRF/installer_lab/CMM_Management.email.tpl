<html>
<head></head>
<body>
	<div id="divuserinfo">
	{if $send_password == TRUE}
		<div style="text-align: center; border-bottom: 1px dotted; margin-bottom: 20px; padding-bottom: 3px; font-weight: bold; font-size: large;">
			User password
		</div>
		<div id="divpasswordtable" style="display: table;">
			<div id="divpasswordtext" style="text-align: left; width: 120px; display: table-cell;">First password:</div>
			<div id="divpassword" style="text-align: left; display: table-cell; font-weight: bold;">{$userinfo.FIRST_PASSWORD}</div>
		</div>
	{else}
					<div style="text-align: center; border-bottom: 1px dotted; margin-bottom: 20px; padding-bottom: 3px; font-weight: bold; font-size: large;">
						User info
					</div>
		        	<div id="divuserinfotable" style="display: table;">
		        		<div id="divurltext" style="text-align: left; width: 120px; display: table-cell;">url:</div>
	        			<div id="divurl" style="text-align: left; display: table-cell; font-weight: bold;">{$userinfo.url}</div>
	        		</div>
		        	<div id="divusernametable" style="display: table;">
		        		<div id="divusernametext" style="text-align: left; width: 120px; display: table-cell;">Username:</div>
	        			<div id="divusername" style="text-align: left; display: table-cell; font-weight: bold;">{$userinfo.CMM_USERID}</div>
	        		</div>
		        	<div id="diveroletable" style="display: table;">
		        		<div id="diveroletext" style="text-align: left; width: 120px; display: table-cell;">Role:</div>
	        			<div id="divrole" style="text-align: left; display: table-cell;">{$userinfo.D_ROLE}</div>
	        		</div>
		        	<div id="divecreationdatetable" style="display: table;">
		        		<div id="divecreationdatetext" style="text-align: left; width: 120px; display: table-cell;">Creation date:</div>
	        			<div id="divcreationdate" style="text-align: left; display: table-cell;">{$userinfo.CREATEDT}</div>
	        		</div>
		        	<div id="divfirstnametable" style="display: table;">
		        		<div id="divfirstnametext" style="text-align: left; width: 120px; display: table-cell;">Name:</div>
	        			<div id="divfirstname" style="text-align: left; display: table-cell;">{$userinfo.NAME}</div>
	        		</div>
		        	<div id="divlastnametable" style="display: table;">
		        		<div id="divlastnametext" style="text-align: left; width: 120px; display: table-cell;">Surname:</div>
	        			<div id="divlastname" style="text-align: left; display: table-cell;">{$userinfo.SURNAME}</div>
	        		</div>
		        	<div id="divemailtable" style="display: table;">
		        		<div id="divemailtext" style="text-align: left; width: 120px; display: table-cell;">email:</div>
	        			<div id="divemail" style="text-align: left; display: table-cell;">{$userinfo.EMAIL}</div>
	        		</div>
	        	{/if}
				</div>
</body>
</html>