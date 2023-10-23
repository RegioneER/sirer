<style>
    .jstree-default-contextmenu{
        z-index:9999;
    }
    i.jstree-themeicon-custom {
        background-size: 24px 24px!important;
    }
</style>
<@script>
$.jstree.defaults.search.fuzzy=false;
$.jstree.defaults.search.show_only_matches=true;
function getObjJstree(currObj){
if(outOfTree[currObj.id]){
delete outOfTree[currObj.id];

}
else{
baseTree[baseTree.length]=currObj.id;
}
var children=[];
if(!(!currObj.allowedChilds || !currObj.allowedChilds.length)){
$.each(currObj.allowedChilds,function(i,currChild){
children[children.length]=getObjJstree(currChild);
});
}
return {

text        : currObj.typeId ,
icon		  : currObj.imageBase64,
state       : {
opened    : false
},
children    : children,

a_attr      : {href:'${baseUrl}/app/admin/editType/'+currObj.id,"data-nodeId":currObj.id}
};

}
var tree=[];
var baseTree=[];
var outOfTree={};

/*
{
id          : "string" // will be autogenerated if omitted
text        : "string" // node text
icon        : "string" // string for custom
state       : {
opened    : boolean  // is the node open
disabled  : boolean  // is the node disabled
selected  : boolean  // is the node selected
},
children    : []  // array of strings or objects
li_attr     : {}  // attributes for the generated LI node
a_attr      : {}  // attributes for the generated A node
}
*/

$.getJSON("${baseUrl}/app/rest/admin/type/getAllTree",function(data){
$.each(data,function(i,currObj){
if(currObj.rootAble){
tree[tree.length]=getObjJstree(currObj);
}else{
outOfTree[currObj.id]=currObj;
}

});

$.each(baseTree,function(i,currObj){
delete outOfTree[currObj];

});

var outChildren=[];
$.each(outOfTree,function(i,currObj){
outChildren[outChildren.length]=getObjJstree(currObj);
});
if(outChildren.length>0){
tree[tree.length]={
text        : 'Elementi non configurati' ,
children    : outChildren,
};
}
$('#jstree_div').jstree(
{"core":{'data':tree},
"contextmenu":{"items":function (node){
return [{label:'Edit',action:function(){window.open(node.a_attr.href);}},{label:'Elimina',action:function(){
if(confirm("Sei sicuro di voler eliminare l'oggetto?")){
loadingScreen("Eliminazione in corso...", "${baseUrl}/int/images/loading.gif");
$.ajax({
type: "GET",
url: "${baseUrl}/app/rest/admin/type/delete"+'/'+node.a_attr["data-nodeId"],
success: function(obj){
if (obj.result=="OK") {
loadingScreen("Eliminazione effettuata!", "${baseUrl}/int/images/green_check.jpg",2000);

location.reload(true);
} else {
loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
}
}
});
}
}}];
}},
"plugins" : ["search","contextmenu"]});
var to = false;
$('#jstree_search').keyup(function () {
console.log(to);
if(to) { clearTimeout(to); }
$('#jstree_div').jstree().clear_search();
to = setTimeout(function () {
var v = $('#jstree_search').val();
console.log(v);
$('#jstree_div').jstree(true).search(v);
}, 250);
});
}
);

type=new ajaXmrTab({
elementName: "type",
baseUrl: "${baseUrl}",
listRow:typeListRow,
saveOrUpdateUrl: "${baseUrl}/app/rest/admin/type/save",
getAllUrl: "${baseUrl}/app/rest/admin/type/getAll",
deleteUrl: "${baseUrl}/app/rest/admin/type/delete",
dialogWidth: "500px",
editPage: "${baseUrl}/app/admin/editType",
listType:"tr"
});
type.refreshList();

template=new ajaXmrTab({
elementName: "template",
baseUrl: "${baseUrl}",
listRow:templateListRow,
saveOrUpdateUrl: "${baseUrl}/app/rest/admin/template/save",
getAllUrl: "${baseUrl}/app/rest/admin/template/getAll",
deleteUrl: "${baseUrl}/app/rest/admin/template/delete",
dialogWidth: "500px",
editPage: "${baseUrl}/app/admin/editTemplate",
listType:"tr"
});
template.refreshList();

policy=new ajaXmrTab({
elementName: "policy",
baseUrl: "${baseUrl}",
listRow:policyListRow,
saveOrUpdateUrl: "${baseUrl}/app/rest/admin/policy/save",
getAllUrl: "${baseUrl}/app/rest/admin/policy/getAll",
deleteUrl: "${baseUrl}/app/rest/admin/policy/delete",
getSingleElementUrl: "${baseUrl}/app/rest/admin/policy/get",
dialogWidth: "500px",
postPopulateFunction: policyPostPopulate,
listType:"tr"
});
policy.refreshList();

calendar=new ajaXmrTab({
elementName: "calendar",
baseUrl: "${baseUrl}",
listRow:calendarListRow,
saveOrUpdateUrl: "${baseUrl}/app/rest/admin/calendar/save",
getAllUrl: "${baseUrl}/app/rest/admin/calendar/getAll",
deleteUrl: "${baseUrl}/app/rest/admin/calendar/delete",
getSingleElementUrl: "${baseUrl}/app/rest/admin/calendar/get",
dialogWidth: "500px",
postPopulateFunction: calendarPostPopulate,
listType:"tr"
});
calendar.refreshList();
$('#tabs').tabs();


function calendarListRow(jsonRow){
console.log(jsonRow);
ret="";
ret+="<td>"+jsonRow.name+"</td>";
ret+="<td>"+jsonRow.elementType.typeId+"</td>";
ret+="<td>"+jsonRow.startDateField.extendedName+"</td>";
if (jsonRow.endDateField) ret+="<td>"+jsonRow.endDateField.extendedName+"</td>";
else ret+="<td>&nbsp;</td>";
ret+="<td style='background-color:#"+jsonRow.backgroundColor+"'>&nbsp;</td>";

return ret;
}

function typeListRow(jsonRow){
var img;
$('#elId').append('<option value="'+jsonRow.id+'">'+jsonRow.typeId+'</option>');
if (jsonRow.imageBase64=='') img='<img height="20px" src="${baseUrl}/int/images/document_blank.png">';
else img='<img height="20px" src="'+jsonRow.imageBase64+'">'
//return '<a href="${baseUrl}/app/admin/editType/'+jsonRow.id+'">'+img+'<br/>'+jsonRow.typeId+'</a>';
ret="";
ret+='<td><a href="${baseUrl}/app/admin/editType/'+jsonRow.id+'">'+img+'</a></td>';
ret+='<td><a href="${baseUrl}/app/admin/editType/'+jsonRow.id+'">'+jsonRow.typeId+'</a></td>';
return ret;
}

function templateListRow(jsonRow){
//return '<a href="${baseUrl}/app/admin/editTemplate/'+jsonRow.id+'"><img height="60px" src="${baseUrl}/int/images/metadata.png"><br/>'+jsonRow.name+'</a>';
ret="";
ret+='<td><a href="${baseUrl}/app/admin/editTemplate/'+jsonRow.id+'">'+jsonRow.name+'</a></td>';
return ret;
}



function policyPostPopulate(jsonRow){
$('#view')[0].checked=jsonRow.policy.canView;
$('#create')[0].checked=jsonRow.policy.canCreate;
$('#update')[0].checked=jsonRow.policy.canUpdate;
$('#addComment')[0].checked=jsonRow.policy.canAddComment;
$('#moderate')[0].checked=jsonRow.policy.canModerate;
$('#delete')[0].checked=jsonRow.policy.canDelete;
$('#changePermission')[0].checked=jsonRow.policy.canChangePermission;
$('#addChild')[0].checked=jsonRow.policy.canAddChild;
$('#removeCheckOut')[0].checked=jsonRow.policy.canRemoveCheckOut;
$('#launchProcess')[0].checked=jsonRow.policy.canLaunchProcess;
$('#enableTemplate')[0].checked=jsonRow.policy.canEnableTemplate;
$('#canBrowse')[0].checked=jsonRow.policy.canBrowse;
}

function policyListRow(jsonRow){
ret="";
ret+="<td>"+jsonRow.name+"</td>";
if (jsonRow.policy.canView) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canCreate) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canUpdate) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canAddComment) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canModerate) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canDelete) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canChangePermission) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canAddChild) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canRemoveCheckOut) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canLaunchProcess) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canEnableTemplate) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
if (jsonRow.policy.canBrowse) ret+="<td>&#10004;</td>";
else ret+="<td>&nbsp;</td>";
return ret;
}

var controls=new Object();
var missingControls=new Object();

function getControlList(){
$.getJSON('${baseUrl}/app/rest/admin/getControls', function(data){

for (var i=0;i<data.resultMap.files.length;i++){
file=data.resultMap.files[i];
var tipo=file.replace('.json','');
controls[tipo]=true;
/*
var href='${baseUrl}/app/admin/editControls/'+file;
var liEl=$('<li>');
    var aEl=$('<a>');
        aEl.attr('href',href);
        aEl.html(file);
        liEl.append(aEl);
        container.append(liEl);
        */
        }
        });


        $.getJSON('${baseUrl}/app/rest/admin/type/getAll',function(data){
        var container=$('#controlsList');
        for (var i=0;i<data.length;i++){
        if (controls[data[i].typeId]){
        var href='${baseUrl}/app/admin/editControls/'+data[i].typeId;
        var liEl=$('<li>');
    var aEl=$('<a>');
    aEl.attr('href',href);
    aEl.html(data[i].typeId);
    liEl.append(aEl);
    container.append(liEl);
    }else {
    missingControls[data[i].typeId]=true;
    }
    }
    console.log(missingControls);
    });
    }
    $.ajaxSetup({async:false});
    getControlList();

    $('.addControls').click(function(){
    addControl();
    });

    function addControl(){
    var options=[];
    for (var tipo in missingControls){
    var choice=new Object();
    choice.text=tipo;
    choice.value=tipo;
    options[options.length]=choice;
    }
    bootbox.prompt({
    title: "Seleziona la tipologia di elemento:",
    inputType: 'select',
    inputOptions: options,
    callback: function (result) {
    window.location.href='${baseUrl}/app/admin/editControls/'+result;
    }
    });
    };

</@script>
    <div class="admin-home-main">

        <div class="tabbable">
            <ul id="myTab4" class="nav nav-tabs padding-12 tab-color-blue background-blue">
                <li class="active">
                    <a href="#struct" data-toggle="tab"><i class="fa fa-info"></i> Struttura dati</a>
                </li>
                <li class="">
                    <a href="#tipi" data-toggle="tab"><i class="fa fa-folder"></i> Tipi di dati</a>
                </li>
                <li class="">
                    <a href="#controlli" data-toggle="tab"><i class="fa fa-check-square-o"></i> Controlli</a>
                </li>
                <li class="">
                    <a href="#template" data-toggle="tab"><i class="fa fa-list"></i> Metadati</a>
                </li>
                <li class="">
                    <a href="#policy" data-toggle="tab"><i class="fa fa-shield"></i> Policy</a>
                </li>
                <li class="">
                    <a href="#calendari" data-toggle="tab"><i class="fa fa-calendar"></i> Calendari</a>
                </li>
                <li>
                    <a class="btn btn-xs btn-info" type="button" onclick="window.location.href='/ACM';">
                        <i class="fa fa-users"></i> Gestione utenti
                    </a>
                </li>
                <li>
                    <a class="btn btn-xs btn-info" type="button" onclick="window.location.href='${baseUrl}/pconsole/#processmodel';">
                        <i class="fa fa-code-fork"></i> Gestione Processi
                    </a>
                </li>
                <li>
                    <a class="btn btn-xs btn-info" type="button" onclick="window.location.href='${baseUrl}/app/admin/messages/it_IT';">
                        <i class="fa fa-flag"></i> Gestione localizzazione
                    </a>
                </li>
            </ul>
            <div class="tab-content">
                <div id="struct" class="tab-pane in active">
                    Cerca: <input id='jstree_search' type="text">
                    <div id="jstree_div"></div>
                </div>
                <div id="tipi" class="tab-pane">
                    <input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi una tipologia" id="add-type" name="add-type"/>
                    <table class="table table-striped table-bordered table-hover">
                        <thead>
                        <tr>
                            <th>&nbsp;</th>
                            <th>Tipo</th>
                            <th>Action</th>
                        </tr>
                        </thead>
                        <tbody id="type-list-availables"></tbody>
                    </table>
                </div>
                <div id="controlli" class="tab-pane">
                    <button class="btn btn-info btn-xs addControls">
                        <i class="fa fa-plus"></i> definisci controlli
                    </button>
                    <h5>Lista controlli presenti</h5>
                    <ul id="controlsList"></ul>
                </div>
                <div id="template" class="tab-pane">
                    <input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi un template metadati" id="add-template" name="add-template"/>

                    <table class="table table-striped table-bordered table-hover">
                        <thead>
                        <tr>
                            <th>Template</th>
                            <th>Action</th>
                        </tr>
                        </thead>
                        <tbody id="template-list-availables"></tbody>
                    </table>
                </div>
                <div id="policy" class="tab-pane">
                    <input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi una policy" id="add-policy" name="add-policy"/>

                    <table class="table table-striped table-bordered table-hover">
                        <thead>
                        <tr>
                            <th>Policy</th>
						<#include "helpers/permission-tb-header.ftl"/>
                            <th>Action</th>
                        </tr>
                        </thead>
                        <tbody id="policy-list-availables"></tbody>
                    </table>
                </div>
                <div id="calendari" class="tab-pane">
                    <input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi un calendario" id="add-calendar" name="add-calendar"/>

                    <table class="table table-striped table-bordered table-hover">
                        <thead>
                        <tr>
                            <th>Calendario</th>
                            <th>Tipo di elemento</th>
                            <th>Data inizio</th>
                            <th>Data fine</th>
                            <th>Colore</th>
                            <th>Action</th>
                        </tr>
                        </thead>
                        <tbody id="calendar-list-availables"></tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>



<#include "typeForms/element.ftl"/>
<#include "typeForms/metadata.ftl"/>
<#include "typeForms/policy.ftl"/>
<#include "typeForms/calendar.ftl"/>
