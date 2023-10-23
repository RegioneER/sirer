
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["jquery-ui-full", "colorpicker", "datepicker","pages/studio.css","x-editable","select2","jstree"],
"scripts" : ["jquery-ui-full","colorpicker", "datepicker","bootbox", "token-input" ,"elementEdit","x-editable","select2","base","jstree"],
"inline_scripts":[],
"title" : "Dettaglio",
"description" : "Dettaglio"
} />


<@addmenuitem>
{
"class":"",
"link":"${baseUrl}/app/admin",
"level_1":true,
"title":"Console amministrativa",
"icon":{"icon":"icon-cogs","title":"xCDM Console"}
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
<#assign link={
"title":"xCDM Console",
"link":"${baseUrl}/app/admin"
}
/>
<#global breadcrumbs={"title":"Home","links":[]} />
<#global breadcrumbs=breadcrumbs+{"links":breadcrumbs.links+[link]} />

