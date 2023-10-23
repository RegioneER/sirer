
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2","jstree/themes/default/style.min.css"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base","jstree/jstree.min.js"],
	"inline_scripts":[],
	"title" : "Dettaglio",
 	"description" : "Dettaglio" 
} />



<#assign link={
	    		"title":"xCDM Console",
	    		"link":"${baseUrl}/app/admin"
	    	} 
	    	/>  
<#global breadcrumbs={"title":"Localizzazione","links":[]} />
<#global breadcrumbs=breadcrumbs+{"links":breadcrumbs.links+[link]} />

<@addmenuitem>
{
	"class":"",
	"link":"${baseUrl}/app/admin",
	"level_1":true,
	"title":"Console amministrativa",
	"icon":{"icon":"icon-cogs","title":"xCDM Console"},
	"submenu":[
		{
			"class":"",
			"link":"${baseUrl}/app/admin/messages/",
			"level_2":true,
			"title":"Tempi",
			"icon":{"icon":"fa fa-list","title":"Localizzazione"}
		}
	]
	}
</@addmenuitem>

<@addmenuitem>
{
	"class":"",
	"link":"/ACM",
	"level_1":true,
	"title":"Gestione utenti",
	"icon":{"icon":"fa fa-users","title":"Gestione utenti"}
		}
</@addmenuitem>


<@addmenuitem>
{
	"class":"",
	"link":"${baseUrl}/pconsole",
	"level_1":true,
	"title":"Gestione processi",
	"icon":{"icon":"fa fa-code-fork","title":"Gestione processi"}
		}
</@addmenuitem>

<@addmenuitem>
{
	"class":"",
	"link":"${baseUrl}/app/admin/messages/it_IT",
	"level_1":true,
	"title":"Gestione Localizzazione",
	"icon":{"icon":"fa fa-flag","title":"Gestione Localizzazione"}
		}
</@addmenuitem>
<@script>

	 $('.updateProp').change(function(){
             var formData=new FormData();
             var actionUrl="${baseUrl}/app/rest/admin/messages/it_IT";
             formData.append("propName", $(this).attr('name'));
             formData.append("value", $(this).val());
             field_id='icon_'+$(this).attr("id");
             $('#'+field_id).removeClass();
             $('#'+field_id).addClass("icon-spinner");
             $('#'+field_id).addClass("icon-spin");
             $('#'+field_id).addClass("orange");
             $.ajax({
                 type: "POST",
                 url: actionUrl,
                 contentType:false,
                 processData:false,
                 async:false,
                 cache:false,
                 data: formData,
                 success: function(obj){
                 	$('#'+field_id).removeClass();
                     if (obj.result=="OK") {
                        $('#'+field_id).addClass("icon-check");
             			$('#'+field_id).addClass("green"); 
             			setTimeout("clearClasses('"+field_id+"')",1000);
						if (obj.redirect){
                             window.location.href=obj.redirect;
                        }
                     }else {
                     	$('#'+field_id).addClass("icon-warning-sign");
             			$('#'+field_id).addClass("red"); 
             			$('#'+field_id).addClass("bigger-130"); 
                     }
                 },
                 error: function(){
                     	$('#'+field_id).addClass("icon-warning-sign");
             			$('#'+field_id).addClass("red"); 
             			$('#'+field_id).addClass("bigger-130"); 
                 }
             });
             
         });
         
         function clearClasses(field_id){
         	$('#'+field_id).removeClass();
         }





 </@script>