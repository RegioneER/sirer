<div>

<span class="dropdown-anchor" data-dropdown="#dropdown-12"><img style="width:15px;height:15px;float:none" src="${baseUrl}/int/images/settings.png" width="10px" height="10px"/></span>
            <div id="dropdown-12" class="dropdown dropdown-tip" style="z-index:100">
                <ul class="dropdown-menu">
                <@security.authorize ifAnyGranted="tech-admin"> 
                	 <li><a href="${baseUrl}/app/admin"><@msg "system.admin"/></a></li>
                	 <li><a href="${baseUrl}/pconsole"><@msg "system.pconsole"/></a></li>
                	 <li><a href="#" onclick="document.cookie='theme=ace; expires=Thu, 19 Dec 2015 12:00:00 GMT; path=/';location.reload(true);return false;"><@msg "system.aceTheme"/></a></li>
                	 <!--li><a href="#" onclick="document.cookie='theme=default';location.reload(true);return false;"><@msg "system.defaultTheme"/></a></li-->
                </@security.authorize>
                	 <li><a href="/change_password"><@msg "system.changePassword"/></a></li>
                	 <li><a href="/ShibLogOut"><@msg "system.logout"/></a></li>
                </ul>
            </div>
Logged as ${userDetails.username}


</div>

<div align="right">
Profilo ${getUserGroups(userDetails)}
</div>