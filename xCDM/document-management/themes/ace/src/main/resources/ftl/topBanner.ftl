<style>

.menuBar-gemelli{
background: url("/sfondo.png") repeat scroll 0 0 / 100% auto rgba(0, 0, 0, 0);
    margin-top: -8px;
    padding-bottom: 2px;
    padding-top: 4px;
    text-align: right;
    border-radius: 0 0 10px 10px;
    }
.gemelli-userDetails{
	color:white;
	float:left;
	}

.gemelli-title{
	color: #FFFFFF;
    float: left;
    font-family: candara;
    font-size: 1.5em;
    padding-left: 10px;
	}


</style>

<div class="banner-gemmelli" style="min-height:100px">
 
    
 <script>
	
	function ceUrl(a,d){

		var b;
		var c;
		
		
		b=a.replace("ctcgemelli","comitatoeticogemelli");
		c="https://"+b+d;
		
		//window.location.href=c;
		
		window.open(
		c,
		'_blank'
		)
		
	}
</script>   	
      
   
<img alt="logo" src="/banner.png" width="100%"/>
    <div id="menuBar-gemelli" class="menuBar-gemelli">
	 <span class="gemelli-title">
	 	<span style="font-weight:bold"/>C</span>linical <span style="font-weight:bold"/>R</span>esearch <span style="font-weight:bold"/>M</span>anagement <span style="font-weight:bold"/>S</span>ystem
	</span>
	<ul style="
  	margin:0px">
        <li class="<#if !model['typeId']?? && model['area']?? && model['area']=="documents">selected </#if>mainMenu_1_item"><a href="${baseUrl}/app/documents" target="_top" ><@msg "system.home"/></a></li>
    <#if model['rootBrowse']??>
    <#list model['rootBrowse'] as elType>
    	<li class="mainMenu_1_item<#if model['typeId']?? && model['typeId']==elType.id> selected</#if>"><a href="${baseUrl}/app/documents/${elType.id}"  target="_top"><@msg "type."+elType.typeId/></a></li>
    </#list>
    </#if>
    <#if model['hasCalendars']?? && model['hasCalendars']>
        <li class="<#if model['area']?? && model['area']=="calendar">selected </#if>mainMenu_1_item"><a href="${baseUrl}/app/calendar"><@msg "system.calendar"/></a></li>
    </#if>
    <li class="mainMenu_1_item"><a href="/reports/">Reports</a></li>
    
    <#if getUserGroups(userDetails)=='CTC'>
    	<li class="mainMenu_1_item"><a target="_blank" onclick="ceUrl(window.location.hostname,'');return false;" href="#">CE</a></li>
  	<#else>
  		<li class="mainMenu_1_item"><a target="_blank" href="https://www.policlinicogemelli.it/Policlinico_Gemelli.aspx?p=B9B01C95-2808-4D9C-873A-A437044A57A9&n=P_comitato_etico">CE</a></li>
  	</#if>
    <li class="mainMenu_1_item"><a href="#" onclick="document.cookie='theme=ace; expires=Thu, 19 Dec 2015 12:00:00 GMT; path=/';location.reload(true);return false;">Grafica</a></li>
    <li class="mainMenu_1_item"><a href="${baseUrl}/app/documents/custom/search">Ricerca avanzata</a></li>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <li style="display:inline;">
    <form class="form-wrapper cf" id="searchForm" action="${baseUrl}/app/documents/search" method="GET">
        <input type="text" id="searchField" name="pattern" placeholder="Search here..." required>
        <button type="submit">Search</button>
    </form>
    </li>

    </ul>
    </div>
    <#if userDetails??>
     <span class="userDetails">
		<#include "userDetails.ftl"/>
    </span>
	</#if>
  	
   
</div>
