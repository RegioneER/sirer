<#include "macros.ftl">
<#macro includeLayout layoutPart >
	<#include layoutPart>
</#macro>

<#macro renderPage >	
	<#include path.pageData+"/"+mainContent />
	<#if !page.end?? >
		<#if !page.layout?? ><#global page=page+{"layout":"default"} /></#if>
		<#include path.layouts+"/"+page.layout+".ftl" >
	</#if>
</#macro>

<#macro script >
    <#if page??>
    <#assign scriptJS>
   	<#nested>
   	</#assign>
   	<#global page=page+{"inline_scripts":page.inline_scripts+[scriptJS]} />
    <#else>
    <script>
    var oldOnload=window.onload;
    window.onload=function(){
        if (typeof oldOnload == 'function') {
            oldOnload();
        }
        <#nested>
    };
    </script>
	</#if>
</#macro>

<#macro addmenuitem >
	<#assign navitem>
	<#nested>
	</#assign>
	<#global layout=layout+{"sidenav_navList":layout.sidenav_navList+[navitem?eval]} />
	
</#macro>

<#macro addmenulist >
	<#assign navlist>
	<#nested>
	</#assign>
	<#global layout=layout+{"sidenav_navList":layout.sidenav_navList+[navlist?eval]} />
	
</#macro>

<#macro menureplace >
	<#assign navlist>
	<#nested>
	</#assign>
	<#global layout=layout+{"sidenav_navList":[navlist?eval]} />
	
</#macro>

<#macro getmenu >
	<#assign navlist>
	<#nested>
	</#assign>
	<#global layout=layout+{"sidenav_navList":[navlist?eval]} />
	
</#macro>

<#macro style>
	<#assign styleCSS>
	<#nested>
	</#assign>
	<#global page=page+{"inline_styles":page.inline_styles![]+[styleCSS]} />
	
</#macro>

<#macro footer >
	<#assign footerAppend>
	<#nested>
	</#assign>
	<#if page.footer??><#assign currFooter=page.footer /><#else><#assign currFooter=[] /></#if>
	<#global page=page+{"footer":currFooter+[footerAppend]} />
	
</#macro>

<#macro createLinkFunction link="">${link}</#macro>


<#global path=
{
	"assets":"${baseUrl}/int/js/assets",
	"base":"/",
	"_shared":"layouts/partials/_shared",
	"_template":"layouts/partials/_shared/_template",
	"sidenav":"layouts/partials/_shared/sidenav",
	"topbar":"layouts/partials/_shared/topbar",
	"data":"data",
	"commonData":"data/common",
	"pageData":"data/pages",
	"pages":"pages",
	"layouts":"layouts",
	"custom":{
		"assets":"${baseUrl}/int",
		"baseUrl":"${baseUrl}",
		"static":"${baseUrl}/int"
	}
}
/>

<#if mainContent="documents/detail/dispatcher.ftl" >
	<#include path.pages+"/"+mainContent />
</#if>


<#include path.data+"/common/script-mapping.ftl" />

<#include path.data+"/common/style-mapping.ftl" />

<#include path.data+"/common/static-mapping.ftl" />


<#include path.data+"/common/site.ftl" />
<#if userDetails??  >

<#attempt>
 <#global user={
 	"name":userDetails.firstName+" "+userDetails.lastName
 }
 />
 <#recover>
<#global user={
 	"name":"Pinco Pallo "
 }
 />
 </#attempt>

</#if>
<#global breadcrumbs=
{
	"title":site.brand_text,
	"links":[]
}
/>

<#global layout=
{
	"_template"  :{
		"fonts" : path._template + "/fonts.ftl",
		"footer": path._template + "/footer.ftl",
		"header": path._template + "/header.ftl",
		"jquery": path._template + "/jquery.ftl"
	},
	"_sidenav"   :{
		"shortcuts":path.sidenav + "/shortcuts.ftl",
		"items":path.sidenav + "/items.ftl"
	},
	"_topbar"   :{
		"actions"		: path.topbar + "/actions.ftl",
		"links"		: path.topbar + "/links.ftl",
		"tasks"			: path.topbar + "/tasks.ftl",
		"notifications"	: path.topbar + "/notifications.ftl",
		"messages"		: path.topbar + "/messages.ftl",
		"user_menu"		: path.topbar + "/user_menu.ftl",
		"shortcuts":[]
	},
	"sidenav"    	: path._shared + "/sidenav.ftl",
	"notifications" : path._shared + "/notifications.ftl",
	"settings"   	: path._shared + "/settings.ftl",
	"breadcrumbs"	: path._shared + "/breadcrumbs.ftl",
	"topbar"     	: path._shared + "/topbar.ftl",
	"sidenav_navList":[
		{
			"class":"",
			"link":"${baseUrl}/app/documents",
			"level_1":true,
			"title":"Home",
			"icon":{"icon":"icon-home","title":"Home"}
		}
	],
	"_topbar_messages":{
		"count":0,
		"latest":[
				{
					"name":"Giorgio Delsignore",
					"img":"avatar4.png",
					"summary":"Ciao sociis natoque penatibus et auctor ...",
					"time":"now"
				},
				{
					"name":"Giulio Contino",
					"img":"avatar4.png",
					"summary":"Ciao sociis natoque penatibus et auctor ...",
					"time":"now"
				},
				{
					"name":"Federica Ronchetti",
					"img":"avatar4.png",
					"summary":"Ciao sociis natoque penatibus et auctor ...",
					"time":"now"
				}
			]
		},
	"_topbar_notifications":{
		"count":0,
		"latest":[
			{
					"badge":"+12",
					"badge_class":"badge-warning",
					"icon":"icon-comment",
					"icon_class":"btn-warning",
					"title":"Commenti"
				},
			{
				"badge":"3",
				"badge_class":"badge-success",
				"icon":"icon-user",
				"icon_class":"btn-success",
				"title":"Messaggi"
			}
		]
	},
	"_topbar_actions":{
		
		"list":[
			
		]
	},
	"_topbar_tasks":{
		"count":2,
		"latest":[
			{
					"title":"Studio XYZ",
					"percentage":"10",
					"progress_bar_class":"progress-bar-warning"
					
				},
				{
					"title":"Studio XYZ",
					"percentage":"10",
					"progress_bar_class":""
					
				}	
			]
	}
}
 />

 <#if model['rootBrowse']??>
    <#list model['rootBrowse'] as elType>
    <#if elType.getUserPolicy(userDetails).canCreate>
	    <#assign testoLink ><@msg "type."+elType.typeId/></#assign>
    	 <#global layout=layout+{"_topbar_actions": layout._topbar_actions+{"list":layout._topbar_actions.list+[
    	 	{
				"icon":"icon-edit",
				
				"title":testoLink,
				"link":baseUrl+"/app/documents/new/"+elType.id
			}
    	 ]}} />
    	</#if>
    </#list>
    
</#if>
 
<#global ie={"version":"8"} />


<#global page={
	"layout":"default",
	"content":"pages/error-404.ftl",
	"no-header":false
} />

<@renderPage />
