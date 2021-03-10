<#assign type=model['docDefinition']/>
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid"],
"scripts" : [ "select2","jquery-ui-full","bootbox" ,"datepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag"],

"inline_scripts":[],
"title" : "Dettaglio studio",
"description" : "Dettaglio studio"
} />
<@script>
$.ajaxSetup({
async: false
});

//PROVA CARLO!!!!

var myFields={};
//array supporto per ELEMENT_LINK
var elementLinks={};
var elementLinksValue={};
//array supporto per EXT_DICTIONARY
externalDictionaries={};

var templatesParsed= new Array ();
//OTTENGO STRUTTURA ELEMENTO IN MODIFICA
$.getJSON('${baseUrl}/app/rest/documents/${model["element"].id}/createFormSpecByElementId',function(data){
//dentro data ho tutta la struttura dell'albero per come dovrà essere visualizzata (campi, tipocampo ecc)

var myTreeHtml='<h1 id="titleString"></h1>';
myFields=data;
//VAXMR-306 aggiungo i campi creationDt, lastUpdateDt, createUser
//come fields in modo tale da mutuare il codice sottostante per la creazione automatica di tab-pane e tab-content
var jsonLastUpdateDt='{"templateName":"infoOggetto","fieldName":"lastUpdateDt","multiple":false,"possibleValues":{},"type":"DATE","id":-1,"label":"infoOggetto_lastUpdateDt","templateLabel":"infoOggetto"}';
var objLastUpdateDt=JSON.parse(jsonLastUpdateDt);
myFields.fieldList.unshift(objLastUpdateDt); //metto in prime posizioni

var jsonLastUpdateUser='{"templateName":"infoOggetto","fieldName":"lastUpdateUser","multiple":false,"possibleValues":{},"type":"TEXTBOX","id":-4,"label":"infoOggetto_lastUpdateUser","templateLabel":"infoOggetto"}';
var objLastUpdateUser=JSON.parse(jsonLastUpdateUser);
myFields.fieldList.unshift(objLastUpdateUser); //metto in prime posizioni

var jsonCreationDt='{"templateName":"infoOggetto","fieldName":"creationDt","multiple":false,"possibleValues":{},"type":"DATE","id":-2,"label":"infoOggetto_creationDt","templateLabel":"infoOggetto"}';
var objCreationDt=JSON.parse(jsonCreationDt);
myFields.fieldList.unshift(objCreationDt); //metto in prime posizioni

var jsoncreateUser='{"templateName":"infoOggetto","fieldName":"createUser","multiple":false,"possibleValues":{},"type":"TEXTBOX","id":-3,"label":"infoOggetto_createUser","templateLabel":"infoOggetto"}';
var objcreateUser=JSON.parse(jsoncreateUser);
myFields.fieldList.unshift(objcreateUser); //metto in prime posizioni

//console.log("STRUTTURA");
//console.log(myFields);

//CREO LE NAVTABS

$(myFields.fieldList).each(function(){
var myField=$(this)[0];
if(templatesParsed.indexOf(myField.templateName)==-1){
var myNavTabHtml='<li><a data-toggle="tab" href="#'+myField.templateName+'">'+myField.templateLabel+'</a></li>';
$('#templatesNavTab').append(myNavTabHtml);
var myTabContentHtml='<div id="'+myField.templateName+'" class="tab-pane">';
    myTabContentHtml+='<table class="table table-bordered" id="checklist"> '+
        '    <thead> '+
        '        <tr><th colspan="1">Nome Campo</th><th>Valore Campo</th><th>Modifica</th></tr> '+
        '    </thead> '+
        '    <tbody> '+
        '    </tbody> '+
        '</table>';
    myTabContentHtml+='</div>';
$('#templatesTabContent').append(myTabContentHtml);
templatesParsed.push(myField.templateName);
}
});

//aggiungo tab eventuali allegati (in coda sempre!!!)
var myNavTabHtml='<li><a data-toggle="tab" href="#ALLEGATI">file allegato</a></li>';
$('#templatesNavTab').append(myNavTabHtml);
var myTabContentHtml='<div id="ALLEGATI" class="tab-pane">';
    myTabContentHtml+='<h3>file allegato</h3><div id="ATTACHED_FILE"></div>';
    myTabContentHtml+='</div>';
$('#templatesTabContent').append(myTabContentHtml);
if(data.hasFile===true){
container_active=$("#ATTACHED_FILE");
container_active.html("");
var myTabContentHtml='<div id="FileAllegato" class="tab-pane">'+
    '<div id="actualFile"></div>';
    myTabContentHtml+='<table class="table table-bordered" id="checklist"> '+
        '    <thead> '+
        '        <tr><th colspan="1">Nome Campo</th><th>Valore Campo</th><th>Modifica</th></tr> '+
        '    </thead> '+
        '    <tbody> ';
        myTabContentHtml+='</div>';
var myFieldHtml='<tr><td>File name:</td><td>'+
    '<form id="updateFilename" onsubmit="return false;" enctype="multipart/form-data" action="#" method="POST" name="update-updateFilename" >'+
        '<input type="hidden" name="elId" value="${model["element"].id}"/>'+
        '<input type="file" name="file" id="myFileFileName" value="" />'+
        '</td><td><button id="salvaForm-updateFilename" class="btn btn-warning" data-rel="#update-updateFilename" name="salvaForm-updateFilename">'+
    '<i class="icon-save"></i></button></form></td></tr>';//FILE


myFieldHtml+='<tr><td>Versione:</td><td>'+
    '<form id="updateVersion" onsubmit="return false;" action="#" method="POST" name="update-updateVersion" >'+
        '<input type="hidden" name="elId" value="${model["element"].id}"/>'+
        '<input data-type="textbox" type="text" id="myFileVersion" value="" name="version"/>'+
        '</td><td><button id="salvaForm-updateVersion" class="btn btn-warning" data-rel="#update-updateVersion" name="salvaForm-updateVersion">'+
    '<i class="icon-save"></i></button></form></td></tr>';//versione

myFieldHtml+='<tr><td>Note:</td><td>'+
    '<form id="updateNote" onsubmit="return false;" action="#" method="POST" name="update-updateNote" >'+
        '<input type="hidden" name="elId" value="${model["element"].id}"/>'+
        '<input data-type="textbox" type="text" id="myFileNote" value="" name="note"/>'+
        '</td><td><button id="salvaForm-updateNote" class="btn btn-warning" data-rel="#update-updateNote" name="salvaForm-updateNote">'+
    '<i class="icon-save"></i></button></form></td></tr>';//note

myFieldHtml+='<tr><td>Autore:</td><td>'+
    '<form id="updateAutore" onsubmit="return false;" action="#" method="POST" name="update-updateAutore" >'+
        '<input type="hidden" name="elId" value="${model["element"].id}"/>'+
        '<input data-type="textbox" type="text" id="myFileAutore" value=""  name="autore"/>'+
        '</td><td><button id="salvaForm-updateAutore" class="btn btn-warning" data-rel="#update-updateAutore" name="salvaForm-updateAutore">'+
    '<i class="icon-save"></i></button></form></td></tr>';//autore

myFieldHtml+='<tr><td>Data:</td><td>'+
    '<form id="updateDate" onsubmit="return false;"  action="#" method="POST" name="update-updateDate" >'+
        '<input type="hidden" name="elId" value="${model["element"].id}"/>'+
        '<input data-type="textbox" type="text" id="myFileDate" value="" name="date" />'+
        '</td><td><button id="salvaForm-updateDate" class="btn btn-warning" data-rel="#update-updateAutore" name="salvaForm-updateDate">'+
    '<i class="icon-save"></i></button></form></td></tr>';//date

myTabContentHtml+=myFieldHtml+'    </tbody> '+
'</table>';
container_active.append(myTabContentHtml);

$("#myFileDate").datepicker({
format: 'dd/mm/yyyy'
});


$('#salvaForm-updateFilename').on('click',function(){attachFile(this);});
$('#salvaForm-updateVersion').on('click',function(){attachFile(this);});
$('#salvaForm-updateNote').on('click',function(){attachFile(this);});
$('#salvaForm-updateAutore').on('click',function(){attachFile(this);});
$('#salvaForm-updateDate').on('click',function(){attachFile(this);});
}
else{
container_active=$("#ATTACHED_FILE");
container_active.html("Questo ogetto non prevede un file allegato.");
}
//aggiungo tab workflow in coda sempre!!!
var myNavTabHtml='<li><a data-toggle="tab" href="#WORKFLOWS">WORKFLOWS</a></li>';
$('#templatesNavTab').append(myNavTabHtml);
var myTabContentHtml='<div id="WORKFLOWS" class="tab-pane">';
    myTabContentHtml+='<h3>Processi Attivi</h3><ul id="ACTIVE_PROCESSES"></ul>';
    myTabContentHtml+='<i id="ACTIVE_PROCESSES_SPAN" class="icon-spinner icon-spin"></i>';
    myTabContentHtml+='<h3>Processi Disponibili</h3><ul id="AVAILABLE_PROCESSES"></ul>';
    myTabContentHtml+='<i id="AVAILABLE_PROCESSES_SPAN" class="icon-spinner icon-spin"></i>';
    myTabContentHtml+='<h3 style="display:none">Processi Terminati</h3><ul style="display:none" id="TERMINATED_PROCESSES"></ul>'; //TODO: togliere display:none, al momento non li vogliamo far vedere!
    myTabContentHtml+='</div>';
$('#templatesTabContent').append(myTabContentHtml);

//aggiungo tab figli in coda sempre!!!
var myNavTabHtml='<li><a data-toggle="tab" href="#CHILD_TAB">CHILDREN</a></li>';
$('#templatesNavTab').append(myNavTabHtml);
var myTabContentHtml='<div id="CHILD_TAB" class="tab-pane">';
    myTabContentHtml+='<h3>Lista figli</h3><ul id="CHILD_LIST"></ul>';
    myTabContentHtml+='<i id="CHILD_LIST_SPAN" class="icon-spinner icon-spin"></i>';
    myTabContentHtml+='<h3>Lista figli disponibili</h3><ul id="CHILD_ALLOWED_LIST"></ul>';
    myTabContentHtml+='<i id="CHILD_ALLOWED_LIST_SPAN" class="icon-spinner icon-spin"></i>';
    myTabContentHtml+='</div>';
$('#templatesTabContent').append(myTabContentHtml);

//aggiungo tab policy in coda sempre!!!
var myNavTabHtml='<li><a data-toggle="tab" href="#POLICY_TAB">POLICIES</a></li>';
$('#templatesNavTab').append(myNavTabHtml);
$("#pane-POLICY_TAB").prop("id","POLICY_TAB");
$('#templatesTabContent').find('div:first').parent().append($("#POLICY_TAB")); //sposto policy tab in coda
$("#templatesNavTab li:first-child a").trigger("click");//visualizzo infoOggetto come primo tab attivo al caricamento


//aggiungo tab templates disabilitati in coda sempre!!!
var myNavTabHtml='<li><a data-toggle="tab" href="#DISABLED_TEMPLATES_TAB">TEMPLATES DISABILITATI</a></li>';
$('#templatesNavTab').append(myNavTabHtml);
var myTabContentHtml='<div id="DISABLED_TEMPLATES_TAB" class="tab-pane">';
    myTabContentHtml+='<h3>Lista Templates disabilitati</h3><ul id="DISABLED_TEMPLATES_LIST"></ul>';
    myTabContentHtml+='<i id="DISABLED_TEMPLATES_LIST_SPAN" class="icon-spinner icon-spin"></i>';
    myTabContentHtml+='</div>';
$('#templatesTabContent').append(myTabContentHtml);

//aggiungo tab ELIMINA OGGETTO in coda sempre!!!
var myNavTabDeleteElement=$('<li ><a style="color:red;background-color:red" id="delete-element" title="Elimina Oggetto" href="#"><i class="icon icon-remove"></i></a></li>');
myNavTabDeleteElement.click(function(){
bootbox.dialog( {
title: "Eliminazione Oggetto",
message:"Sei Sicuro?",
buttons: {
success: {
label: "Conferma",
className: "btn-success",
callback: function() {
loadingScreen("Eliminazione in corso...", "${baseUrl}/int/images/delete.png");
$.ajax({
    type: "GET",
    url: "${baseUrl}/app/rest/dm/deleteElement/${model["element"].id}",
    async:false,
    cache:false,
    success: function(obj){
        if (obj.result=="OK") {
            loadingScreen("Eliminazione effettuata", "${baseUrl}/int/images/delete.png",1000);
            //STSANSVIL-679 forzo ultima modifica per far partire l'elk e indicizzare correttamente l'elemento
            current_datetime = new Date();
            formatted_date = current_datetime.getDate() + "/" + (current_datetime.getMonth() + 1) + "/" + current_datetime.getFullYear();
            $.ajax({
            method : 'POST',
            url :  '${baseUrl}/app/rest/dm/updateMetdata/${model["element"].id}/-1',
            data : {'value':formatted_date}
            })
            if (obj.redirect){
                window.location.href=obj.redirect;
            }
        }else {
            loadingScreen("Errore eliminazione!", "${baseUrl}/int/images/alerta.gif", 3000);
        }
    },
error: function(){
loadingScreen("Errore eliminazione!", "${baseUrl}/int/images/alerta.gif", 3000);
}
});
}
},
cancel: {
label: "Annulla",
className: "btn-cancel",
callback: function(){
$("#permission-div").append($("#permission-dialog"));
}
}
},
onEscape: function(){
$("#permission-div").append($("#permission-dialog"));
}
});
return false;
});
$('#templatesNavTab').append(myNavTabDeleteElement);

//selezioni la prima tab di default
$('#templatesNavTab').find('li:first').addClass('active');
$('#templatesTabContent').find('div:first').addClass('active');

$(myFields.fieldList).each(function(){
var myField=$(this)[0];
var myFieldHtml='<div class="field-component view-mode">';
    var myFieldId=myField.templateName+'_'+myField.fieldName;
    var myFieldIdentifier=myField.id;
    switch(myField.type){
    case 'TEXTBOX':
    myFieldHtml+='<div id="'+myField.templateName+'-'+myFieldId+'" class=" field-editable">'+
        '<input data-type="'+myField.type+'" type="text" id="'+myFieldId+'" name="value" /><br/>'+
        '</div>';
    break;
    case 'TEXTAREA':
    myFieldHtml+='<div id="'+myField.templateName+'-'+myFieldId+'" class=" field-editable">'+
        '<textarea type="'+myField.type+'" id="'+myFieldId+'" name="value" > </textarea><br/>';
        '</div>';
    break;
    case 'SELECT':
    myFieldHtml+='<div id="'+myField.templateName+'-'+myFieldId+'" class=" field-editable">'+
        '<select id="'+myFieldId+'" name="value" >';
            myFieldHtml+='<option value="">&nbsp;</option>';
            $.each(myField.possibleValues,function(key,value){
            myFieldHtml+='<option value="'+key+'###'+value+'">'+value+'</option>';
            });
            myFieldHtml+='</select>'+
        '</div>';
    break;
    case 'RADIO':
    myFieldHtml+='<div id="'+myField.templateName+'-'+myFieldId+'" class=" field-editable">';
        $.each(myField.possibleValues,function(key,value){
        myFieldHtml+='<span class="x-radio-input x-field-'+myFieldId+'">'+
                                    '<div class="radio">'+
                                    '<label>'+
                                    '   <input data-type="'+myField.type+'" type="'+myField.type+'" title="'+value+'" checked="" value="'+key+'###'+value+'" name="value" id="'+myFieldId+'" class="ace"><span class="lbl">'+value+'</span>'+
                                    '</label>'+
                                    '</div>'+
                                '</span>';
        //    myFieldHtml+='<input data-type="'+myField.type+'" type="'+myField.type+'" id="'+myFieldId+'" name="'+myFieldId+'" value="value">'+value+'</input><br/>';
        });
        myFieldHtml+='<span id="radioClear-'+myFieldId+'" name="radioClear-'+myFieldId+'">'+
                                     '  <div class="radio">'+
                                     '      <a href="#" onclick="$(\'[id='+myFieldId+'\').prop(\'checked\', false); return false;"><i class="fa fa-eraser"></i> deseleziona</a>'+
                                     '  </div>'+
                                     '</span>'+
        '</div>';
    break;
    case 'CHECKBOX':
    myFieldHtml+='<div id="'+myField.templateName+'-'+myFieldId+'" class=" field-editable">';
        $.each(myField.possibleValues,function(key,value){
        myFieldHtml+='<span class="x-checkbox-input x-field-'+myFieldId+'">'+
                                         '<div class="checkbox">'+
                                         '  <label>'+
                                         '      <input data-type="'+myField.type+'" type="'+myField.type+'" title="'+value+'" value="'+key+'###'+value+'" name="value" id="'+myFieldId+'" class="ace" autocomplete="off"><span class="lbl">'+value+'</span>'+
                                         '  </label>'+
                                         '</div>'+
                                         '</span>';
        });
        myFieldHtml+='</div>';
    break;
    case 'DATE':
    myFieldHtml+='<input data-type="'+myField.type+'" type="text" id="'+myFieldId+'" name="value" /><br/>';
    break;
    case 'ELEMENT_LINK':
    myFieldHtml+='<input data-type="'+myField.type+'" type="text" id="'+myFieldId+'" name="value" /><br/>';
    var myElement={};
    myElement.id=myField.id;
    myElement.value=myField.values[0];
    elementLinks[myFieldId]=myElement;
    break;
    case 'EXT_DICTIONARY':
    var myDict={};
    myDict.macro=myField.macro;
    myDict.extDicLink=myField.extDicLink;
    myDict.extDicAddFilters=myField.extDicAddFilters;
    if(myField.values.length>0){
    myValue={};
    myValue.id=myField.values[0].split("###")[0];
    myValue.title=myField.values[0].split("###")[1];
    myDict.value=myValue;
    }
    externalDictionaries[myFieldId]=myDict;
    //if(myField.macro!=null && myField.macro=="extDictionaryAutocomplete"){
    myFieldHtml+='<input data-type="'+myField.type+'" type="text" id="'+myFieldId+'" name="value" ></input><br/>';
    /*}
    else{
    myFieldHtml+='<div id="'+myFieldId+'" class=" field-editable">'+
        '<select id="'+myFieldId+'-select" name="'+myFieldId+'" ></select>'+
        '<input type="hidden" id="'+myFieldId+'" name="'+myFieldId+'"/>'+
        '</div>';
    }*/
    break;
    default:
    myFieldHtml+='<input data-type="'+myField.type+'" type="'+myField.type+'" id="'+myFieldId+'" name="value" >'+myFieldId+'</input><br/>';
    }
    myFieldHtml+="</div>";
myTR='<tr id="informations-'+myFieldId+'">'+
    '<td id="td-label'+myFieldId+'">'+myField.label+'</td>'+
    '<td id="td-field-'+myFieldId+'">'+
        '<form id="update-'+myFieldId+'" onsubmit="return false;" action="#" method="POST" name="update-'+myFieldId+'" >'+
            '   <input type="hidden" name="elId" value="${model["element"].id}"/>'+
            '   <input type="hidden" name="mdId" value="'+myFieldIdentifier+'"/>'+
            myFieldHtml+
            '</td><td>   <button id="salvaForm-'+myFieldId+'" class="btn btn-warning" data-rel="#update-'+myFieldId+'" name="salvaForm-'+myFieldId+'"><i class="icon-save"></i></button>'+
        '</form>'+
        '</td>'+
    '</tr>';
$('#'+myField.templateName+' tbody').append(myTR);
$('#salvaForm-'+myFieldId).on('click',function(){submitForm(this);});
if(myField.type=='SELECT'){
$('#'+myFieldId).select2({allowClear:true});
}
else if(myField.type=='DATE'){
$('#'+myFieldId).datepicker({
format: 'dd/mm/yyyy'
});
}
});
});

//OTTENGO DATI ELEMENTO IN MODIFICA
//var myType;
$.getJSON('${baseUrl}/app/rest/dm/getElementJSON/${model["element"].id}?mode=complete-without-parent',function(data){
//adesso compilo l'html creato prima in #myContentTree con i valori che che ho appena chiesto.
//console.log("VALORI");
//console.log(data);
$('#titleString').html('Editing '+data.titleString);
var myFieldsMetadata=data.metadata;
//VAXMR-306 aggiungo i campi creationDt, lastUpdateDt, createUser
//come fields in modo tale da mutuare il codice sottostante per la compilazione dei campi
myFieldsMetadata['infoOggetto_lastUpdateDt']=[data.lastUpdateDt];
myFieldsMetadata['infoOggetto_creationDt']=[data.creationDt];
myFieldsMetadata['infoOggetto_createUser']=[data.createUser];
myFieldsMetadata['infoOggetto_lastUpdateUser']=[data.lastUpdateUser];

var myType=data.type.id;
var myId=data.id;

var allowedChildNotShow= [];
allowedChildNotShow.push("BudgetBracci");//STSANPRJS-707 nascondo figli non disponibili in SIRER
allowedChildNotShow.push("Safety");
allowedChildNotShow.push("DSUR");
allowedChildNotShow.push("PropostaSponsor");
allowedChildNotShow.push("FolderTpxp");
allowedChildNotShow.push("FolderTimePoint");
allowedChildNotShow.push("FolderPXS");
allowedChildNotShow.push("FolderPrestazioni");
allowedChildNotShow.push("FolderBracci");
allowedChildNotShow.push("FolderApprovazione");
allowedChildNotShow.push("LettAccFirmaContr");
allowedChildNotShow.push("LettAccFirmaContr2");

//OTTENGO FIGLI GIA' CREATI
container_Childs=$("#CHILD_LIST");
container_Childs.html("");
var myChilds=data.children;

    $.each(myChilds,function(key,myChild){
        if(jQuery.inArray(myChild.type.typeId, allowedChildNotShow) === -1){
            addChildItem=$("<li>"+myChild.type.typeId+" "+myChild.titleString+" </li>");
            addChildLinkView=$('<a>');
    addChildLinkView.attr('child-id', myChild.id);
    addChildLinkView.attr('href', '${baseUrl}/app/documents/detail/'+myChild.id);
    addChildLinkView.html("<i class='fa fa-eye'></i> Visualizza");
    addChildItem=$("<li>"+myChild.type.typeId+" "+myChild.titleString+" </li>");

    addChildItem.append(addChildLinkView);
    addChildItem.append('&nbsp;');

    addChildLinkEdit=$('<a>');
        addChildLinkEdit.attr('child-id', myChild.id);
        addChildLinkEdit.attr('href', '${baseUrl}/app/documents/dm/edit/'+myChild.id);
        addChildLinkEdit.html("<i class='fa fa-edit'></i> Modifica");

        addChildItem.append(addChildLinkEdit);
        container_Childs.append(addChildItem);
        }
        });
        $("#CHILD_LIST_SPAN").remove();


        container_allowedChilds=$("#CHILD_ALLOWED_LIST");
        container_allowedChilds.html("");


        //OTTENGO FIGLI DISPONIBILI
        $.getJSON('${baseUrl}/app/rest/admin/type/'+myType+'/getChilds',function(myAllowedChilds){
            //console.log("FIGLI DISPONIBILI");
            //console.log(myAllowedChilds);



            $.each(myAllowedChilds,function(key,myAllowedChild){
                if(jQuery.inArray(myAllowedChild.typeId, allowedChildNotShow) === -1){
                    addChildLink=$('<a>');
                    addChildLink.attr('child-id', myAllowedChild.id);
                    addChildLink.attr('parent-element-it', myId);
                    addChildLink.html("<i class='fa fa-plus'></i> Aggiungi");
                    addChildLink.click(function(){
                        bootboxShowAddChildUserPrompt (myAllowedChild.id,myId);
                    });

                    addChildItem=$("<li>"+myAllowedChild.typeId+" </li>");
                    addChildItem.append(addChildLink);
                    //console.log(addChildItem);
                    container_allowedChilds.append(addChildItem);
                }
            });

            $("#CHILD_ALLOWED_LIST_SPAN").remove();

        });


        $.each(myFieldsMetadata,function(key,value){
            if(value.length>0){
            if($('#'+key).is("input") && $('#'+key).attr('data-type')=='CHECKBOX'){
            console.log(key+" "+value);
            $(value).each(function(k,my_val){
            $('input[id='+key+'][value="'+my_val+'"]').prop('checked',true);
            });
            }
            else if ($('#'+key).is("input") && $('#'+key).attr('data-type')=='RADIO' ){
            //console.log(key+" "+value);
            if(value.length==1){
            $('input[id='+key+'][value="'+value[0]+'"]').prop('checked',true);
            }
            }
            else if($('#'+key).is("input") && ( $('#'+key).attr('data-type') == 'DATE' )){
            var my_date=new Date(parseInt(value[0]));
            var d=my_date.getDate();
            var m=my_date.getMonth()+1;
            var y=my_date.getFullYear();
            if (d<10) d='0'+d;
            if (m<10) m='0'+m;
            var dateString=d+'/'+m+'/'+y;
            $('#'+key).val(dateString);
            }
            else if($('#'+key).is("input") && ( $('#'+key).attr('data-type') == 'ELEMENT_LINK' ) ){
            //elementLinksValue[key]=value[0];
            }
            else if($('#'+key).is("input") && ( $('#'+key).attr('data-type') == 'EXT_DICTIONARY' ) ){
            //externalDictionaries[key]=value[0];
            }
            else if($('#'+key).is("select")){
            var my_values=value[0].split('###');
            $('#'+key).val(value[0]).change();
            }
            else{ // if($('#'+key).is("input") && $('#'+key).attr('data-type')=='TEXTBOX' ){
            $('#'+key).val(value[0]);
            }
            }
            });
            //inserisco allegato
            if(data.file!==undefined && data.file!==null){
            var myFile=data.file;

            attachedFileLink=$('<a>');
                attachedFileLink.attr('element-id', myFile.id);
                attachedFileLink.attr('href','${baseUrl}/app/documents/getAttach/'+myId);
                attachedFileLink.html(myFile.fileName);
                $("#actualFile").append(attachedFileLink);//LINK AL FILE
                $("#myFileVersion").val(myFile.version);//versione
                $("#myFileNote").val(myFile.note);//note
                $("#myFileAutore").val(myFile.autore);//autore


                var my_date=new Date(parseInt(myFile.date));
                var d=my_date.getDate();
                var m=my_date.getMonth()+1;
                var y=my_date.getFullYear();
                if (d<10) d='0'+d;
                if (m<10) m='0'+m;
                var dateString=d+'/'+m+'/'+y;
                $("#myFileDate").val(dateString);//date
                }
                //ATTIVO GESTIONE TOKEN INPUT PER GLI ELEMENT_LINK
                $.each(elementLinks,function(key,elementLink){
                $('#'+key).attr('isTokenInput',true);
                $('#'+key).tokenInput('${baseUrl}/app/rest/documents/getLinkableElements/'+elementLink.id, {
                queryParam: 'term',
                hintText: 'Digitare almeno 2 caratteri',
                minChars: 2,
                searchingText: 'ricerca in corso...',
                noResultsText: 'Nessun risultato',
                tokenLimit: 1,
                theme: 'facebook',
                preventDuplicates: true,
                onResult: function (results) {
                $.each(results, function (index, value) {
                value.name = value.title;
                value.id=value.id;
                });
                return results;
                }
                });
                if(elementLink.value!==undefined){

                $('#'+key).tokenInput("add", {id: elementLink.value.id, name: elementLink.value.value});
                }
                });
                //ATTIVO GESTIONE TOKEN INPUT PER GLI EXT_DICTIONARY
                $.each(externalDictionaries,function(key,externalDictionary){
                $('#'+key).attr('isTokenInput',true);
                var url=externalDictionary.extDicLink;//
                if(externalDictionary.extDicAddFilters!=undefined || externalDictionary.extDicAddFilters!=null){
                url+="?"+externalDictionary.extDicAddFilters.replace(",","&");
                //pulisco da eventuali filtri parametrizzati (vedi p.es UO su PI in RegCentro
                url=url.replace(/\[(.*?)\]/g,"");
                url=url.replace(/\&(.*?)=/g,"&");
                }//
                $('#'+key).tokenInput(url, {
                queryParam: 'term',
                hintText: 'Digitare almeno 2 caratteri',
                minChars: 2,
                searchingText: 'ricerca in corso...',
                noResultsText: 'Nessun risultato',
                tokenLimit: 1,
                theme: 'facebook',
                preventDuplicates: true,
                onResult: function (results) {
                $.each(results, function (index, value) {
                value.name = value.title!==undefined ? value.title : value.text; //alcuni script restituiscono title, altri text (è più certo avere text che non title)
                value.id=value.id.split("###")[1]!==undefined ? value.id : value.id+"###"+value.name;
                });
                return results;
                }
                });
                if(externalDictionary.value!==undefined){
                $('#'+key).tokenInput("add", {id: externalDictionary.value.id+'###'+externalDictionary.value.title, name: externalDictionary.value.title});
                }
                });
                container_allowedTemplates=$("#DISABLED_TEMPLATES_LIST");
                container_allowedTemplates.html("");
                //prendo templates disponibili
                getTemplates(myType,myId);
                });

                function getTemplates(myType,myId){
                var allowedTemplateNotShow= [];
                allowedTemplateNotShow.push("TeamRicerca");//STSANPRJS-707 nascondo template non disponibili in SIRER
                allowedTemplateNotShow.push("AnalisiCentro");
                $.getJSON('${baseUrl}/app/rest/dm/getElementTemplatesACL/'+myId,function(myAllowedTemplates){
                //console.log("TEMPLATES DISPONIBILI");
                //console.log(myAllowedTemplates);
                //console.log(templatesParsed);
                $.each(myAllowedTemplates.resultMap.acls,function(key,myAllowedTemplate){
                if($.inArray(key, allowedTemplateNotShow) === -1)//STSANPRJS-707 metto qui senza graffe perchè vale sia per if che per then
                if($.inArray(key,templatesParsed)<0){
                enableTemplateLink=$('<a>');
                    enableTemplateLink.attr('template-id', key);
                    enableTemplateLink.attr('element-id', myId);
                    enableTemplateLink.html("<i class='fa fa-check'></i> Abilita");
                    enableTemplateLink.click(function(){
                    loadingScreen("Abilitazione template in corso...", "loading");
                    elId=$(this).attr('element-id');
                    templateId=$(this).attr('template-id');
                    //console.log('Id Elemento: ',elId);
                    //console.log('Key Processo: ',pKey);

                    $.post( '${baseUrl}/app/rest/dm/'+elId+'/addTemplate/'+templateId, { elId: elId, templateId: templateId } ).done(function( data ) {
                    //bootbox.hideAll();
                    if(data.result=="OK"){
                    location.href=data.redirect;
                    }
                    });


                    });

                    addChildItem=$("<li>"+key+" </li>");
                    addChildItem.append(enableTemplateLink);
                    //console.log(addChildItem);
                    container_allowedTemplates.append(addChildItem);
                    }
                    else{ //TEMPLATE GIA' ATTIVO, inserisco tabella ACLTEMPLATE
                    $('#table_'+key).remove();//svuoto (se vengo richiamato dopo un update delle policy dei template per aggiornare la tabella
                    $('#add-templateACL_'+key).remove();//svuoto (se vengo richiamato dopo un update delle policy dei template per aggiornare la tabella
                    var templatePolicyTable=$('<table>');
                        templatePolicyTable.attr('id','table_'+key);
                        templatePolicyTable.addClass('table table-striped table-bordered table-hover');
                        var myThead=$("<thead>");
                        var myTr=$("<tr>");


                            var myTh=$("<th title='Container'>")
                                myTh.html("Container");
                                myTr.append(myTh);
                                myThead.append(myTr);



                                myTh=$("<th title='Visualizzazione'>");
                                myTh.html("V");
                                myTr.append(myTh);
                                myThead.append(myTr);


                                myTh=$("<th title='Creazione'>");
                                myTh.html("C");
                                myTr.append(myTh);
                                myThead.append(myTr);


                                myTh=$("<th title='Modifica'>");
                                myTh.html("M");
                                myTr.append(myTh);
                                myThead.append(myTr);

                                myTh=$("<th title='Eliminazione'>");
                                myTh.html("E");
                                myTr.append(myTh);
                                myThead.append(myTr);
                                templatePolicyTable.append(myThead);
                                myTh=$("<th>");
                                myTh.html("Action");
                                myTr.append(myTh);
                                myThead.append(myTr);
                                templatePolicyTable.append(myThead);
                                myButtonNewACL=$('<input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi una ACL al template" id="add-templateACL_'+key+'" name="add-templateACL_'+key+'"/>');
                                myButtonNewACL.click(function(){
                                loadingScreen("Creazione Template ACL  in corso...", "loading");
                                $.post ( '${baseUrl}/app/rest/dm/'+myId+'/aclTemplate/newAcl/'+key,
                                {   elId: ${model["element"].id},
                                templateName: key
                                }
                                ).done(function( data ) {
                                getTemplates(myType,myId);
                                bootbox.hideAll();
                                });

                                });
                                $("#"+key).append(myButtonNewACL);
                                $("#"+key).append(templatePolicyTable);

                                var myTr=$("<tr>");
                            var ContainersTD=$("<td>");
                                $(myAllowedTemplate).each(function(k,tACLs){ //per ogni acl di tutti i template
                                myTr=$("<tr>");
                            ContainersTD=$("<td>");
                                $(tACLs.containers).each(function(k,container){ //per ogni container di una ACL
                                //TD CONTAINER
                                if(container.authority){
                                ContainersTD.html(ContainersTD.html()+"g:");
                                }
                                else{
                                ContainersTD.html(ContainersTD.html()+"u:");
                                }
                                ContainersTD.html(ContainersTD.html()+container.container);
                                updateLink=$('<a style="float:right;" title="Rimuovi Container">');
                                    updateLink.html("<i class='fa fa-remove'></i>&nbsp;");
                                    updateLink.attr('href','#');
                                    updateLink.click(function (){
                                    loadingScreen("Eliminazione container in corso...", "loading");
                                    $.post('${baseUrl}/app/rest/dm/'+myId+'/templateAcl/'+tACLs.id+'/removeContainer/'+container.id, { value: true } ).done(function( data ) {
                                    getTemplates(myType,myId);
                                    bootbox.hideAll();
                                    });
                                    return false;
                                    });
                                    ContainersTD.append(updateLink);
                                    ContainersTD.append($("<br/>"));
                                    myTr.append(ContainersTD);

                                    });
                                    //icona aggiungi template
                                    updateLink=$('<a style="float:right;" title="Aggiungi Container">');
                                        updateLink.html("<i class='fa fa-plus'></i>&nbsp;");
                                        updateLink.attr('href','#');
                                        updateLink.click(function (){
                                        bootbox_message=$("#permission-dialog");
                                        bootbox.dialog( {
                                        title: "Aggiungi Container",
                                        message:bootbox_message,
                                        buttons: {
                                        success: {
                                        label: "Aggiungi Container",
                                        className: "btn-success",
                                        callback: function() {
                                        $("#permission-div").append($("#permission-dialog"));
                                        loadingScreen("Aggiungo Container...", "loading");
                                        $.post( '${baseUrl}/app/rest/dm/'+myId+'/templateAcl/addContainers/'+tACLs.id,
                                        {   groups: $('#groups').val(),
                                        users: $("#users").val(),
                                        allUsers: $("#allUsers").prop("checked") ? true: null,
                                        cuser: $("#cuser").prop("checked") ? true: null
                                        }
                                        ).done(function( data ) {
                                        getTemplates(myType,myId);
                                        bootbox.hideAll();
                                        });
                                        }
                                        },
                                        cancel: {
                                        label: "Annulla",
                                        className: "btn-cancel",
                                        callback: function(){
                                        $("#permission-div").append($("#permission-dialog"));
                                        }
                                        }
                                        },
                                        onEscape: function(){
                                        $("#permission-div").append($("#permission-dialog"));
                                        }
                                        });
                                        return false;
                                        });
                                        ContainersTD.append(updateLink);
                                        myTr.append(ContainersTD);
                                        //TD POLICY CANVIEW
                                        var actionTD=$('<td>');
                                var updateLink;
                                updateLink=$('<a>');
                                    updateLink.attr('update-template-id', myAllowedTemplate.id);
                                    updateLink.attr('update-aclId', tACLs.id);
                                    if (tACLs.policy.canView){
                                    updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                    }
                                    else{
                                    updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                    }
                                    updateLink.attr('href','#');
                                    updateLink.click(function (){
                                    loadingScreen("Aggiornamento policy template in corso...", "loading");
                                    aclId=$(this).attr('update-aclId');
                                    templateId=$(this).attr('update-template-id');
                                    $.post('${baseUrl}/app/rest/dm/'+myId+'/aclTemplate/'+aclId, { view: !tACLs.policy.canView, create: tACLs.policy.canCreate, update: tACLs.policy.canUpdate, delete: tACLs.policy.canDelete } ).done(function( data ) {
                                    getTemplates(myType,myId);
                                    bootbox.hideAll();
                                    });
                                    return false;
                                    });
                                    actionTD.append(updateLink);
                                    myTr.append(actionTD);

                                    //TD POLICY CANCREATE
                                    var actionTD=$('<td>');
                                var updateLink;
                                updateLink=$('<a>');
                                    updateLink.attr('update-template-id', myAllowedTemplate.id);
                                    updateLink.attr('update-aclId', tACLs.id);
                                    if (tACLs.policy.canCreate){
                                    updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                    }
                                    else{
                                    updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                    }
                                    updateLink.attr('href','#');
                                    updateLink.click(function (){
                                    loadingScreen("Aggiornamento policy template in corso...", "loading");
                                    aclId=$(this).attr('update-aclId');
                                    templateId=$(this).attr('update-template-id');
                                    $.post('${baseUrl}/app/rest/dm/'+myId+'/aclTemplate/'+aclId, { view: tACLs.policy.canView, create: !tACLs.policy.canCreate, update: tACLs.policy.canUpdate, delete: tACLs.policy.canDelete } ).done(function( data ) {
                                    getTemplates(myType,myId);
                                    bootbox.hideAll();
                                    });
                                    return false;
                                    });
                                    actionTD.append(updateLink);
                                    myTr.append(actionTD);

                                    //TD POLICY CANUPDATE
                                    var actionTD=$('<td>');
                                var updateLink;
                                updateLink=$('<a>');
                                    updateLink.attr('update-template-id', myAllowedTemplate.id);
                                    updateLink.attr('update-aclId', tACLs.id);
                                    if (tACLs.policy.canUpdate){
                                    updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                    }
                                    else{
                                    updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                    }
                                    updateLink.attr('href','#');
                                    updateLink.click(function (){
                                    loadingScreen("Aggiornamento policy template in corso...", "loading");
                                    aclId=$(this).attr('update-aclId');
                                    templateId=$(this).attr('update-template-id');
                                    $.post('${baseUrl}/app/rest/dm/'+myId+'/aclTemplate/'+aclId, { view: tACLs.policy.canView, create: tACLs.policy.canCreate, update: !tACLs.policy.canUpdate, delete: tACLs.policy.canDelete } ).done(function( data ) {
                                    getTemplates(myType,myId);
                                    bootbox.hideAll();
                                    });
                                    return false;
                                    });
                                    actionTD.append(updateLink);
                                    myTr.append(actionTD);

                                    //TD POLICY CANDELETE
                                    var actionTD=$('<td>');
                                var updateLink;
                                updateLink=$('<a>');
                                    updateLink.attr('update-template-id', myAllowedTemplate.id);
                                    updateLink.attr('update-aclId', tACLs.id);
                                    if (tACLs.policy.canDelete){
                                    updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                    }
                                    else{
                                    updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                    }
                                    updateLink.attr('href','#');
                                    updateLink.click(function (){
                                    loadingScreen("Aggiornamento policy template in corso...", "loading");
                                    aclId=$(this).attr('update-aclId');
                                    templateId=$(this).attr('update-template-id');
                                    $.post('${baseUrl}/app/rest/dm/'+myId+'/aclTemplate/'+aclId, { view: tACLs.policy.canView, create: tACLs.policy.canCreate, update: tACLs.policy.canUpdate, delete: !tACLs.policy.canDelete } ).done(function( data ) {
                                    getTemplates(myType,myId);
                                    bootbox.hideAll();
                                    });
                                    return false;
                                    });
                                    actionTD.append(updateLink);
                                    myTr.append(actionTD);

                                    actionTD=$('<td>');
                                var deleteLink=$('<a>');
                                    deleteLink.attr('remove-aclId', tACLs.id);
                                    deleteLink.attr('remove-templateId', myAllowedTemplate.id);
                                    deleteLink.attr('remove-myElementId', myId);
                                    deleteLink.html("<i class='fa fa-trash'></i> Elimina");
                                    deleteLink.click(function (){
                                    loadingScreen("Eliminazione policy in corso...", "loading");
                                    aclId=$(this).attr('remove-aclId');
                                    templateId=$(this).attr('remove-templateId');
                                    myId=$(this).attr('remove-myElementId');
                                    $.get( '${baseUrl}/app/rest/dm/'+myId+'/templateAcl/remove/'+aclId, { aclId: aclId } ).done(function( data ) {
                                    if(data.result=="KO"){
                                    loadingScreen("Errore durante l'eliminazione...");
                                    }
                                    else{
                                    getTemplates(myType,myId);
                                    bootbox.hideAll();
                                    }

                                    });
                                    });
                                    actionTD.append(deleteLink);
                                    myTr.append(actionTD);

                                    templatePolicyTable.append(myTr);
                                    });
                                    }
                                    });
                                    $("#DISABLED_TEMPLATES_LIST_SPAN").remove();
                                    });
                                    }

                                    function bootboxShowAddChildUserPrompt(myAllowedChildId,myId){
                                    bootbox.prompt( {
                                    title: "Inserisci username",
                                    value: "",
                                    callback: function(result) {
                                    if (result !== null) {
                                    if(result===""){
                                    bootbox.confirm("username obbligatorio", function(result) {bootboxShowAddChildUserPrompt(myAllowedChildId,myId);});

                                    }
                                    else{
                                    loadingScreen("Creazione figlio in corso...", "loading");

                                    childTypeId=myAllowedChildId;
                                    parentElementId=myId;
                                    userId=result;
                                    //console.log('Tipo figlio: ',childTypeId);
                                    //console.log('Id padre: ',parentElementId);
                                    $.post( '${baseUrl}/app/rest/dm/addChild/'+parentElementId+'/'+childTypeId+'/'+userId, { parentElementId: parentElementId, childTypeId : childTypeId,userId : userId} ).done(function( data ) {

                                    var childCreatedId=data.ret;

                                    addChildItem=$("<li>"+childCreatedId.type.typeId+" "+childCreatedId.titleString+" </li>");

                                    addChildLinkView=$('<a>');
                                        addChildLinkView.attr('child-id', childCreatedId.id);
                                        addChildLinkView.attr('href', '${baseUrl}/app/documents/detail/'+childCreatedId.id);
                                        addChildLinkView.html("<i class='fa fa-eye'></i> Visualizza");
                                        addChildItem=$("<li>"+childCreatedId.type.typeId+" "+childCreatedId.titleString+" </li>");
                                        addChildItem.append(addChildLinkView);

                                        addChildItem.append('&nbsp;');

                                        addChildLinkEdit=$('<a>');
                                            addChildLinkEdit.attr('child-id', childCreatedId);
                                            addChildLinkEdit.attr('href', '${baseUrl}/app/documents/dm/edit/'+childCreatedId.id);
                                            addChildLinkEdit.html("<i class='fa fa-edit'></i> Modifica");

                                            addChildItem.append(addChildLinkEdit);

                                            container_Childs.append(addChildItem);
                                            bootbox.hideAll();
                                            //alert("CIAO!");
                                            });
                                            }
                                            }
                                            else{
                                            //window.setTimeout(function(){bootbox.hideAll();}, 3000);
                                            }
                                            }
                                            });
                                            }
                                            var empties=new Array();
                                            function submitForm(buttonClicked){
                                            var $form=$($(buttonClicked).data('rel'));
                                            if($(buttonClicked).attr('id')){
                                            var formName=$(buttonClicked).attr('id').replace("salvaForm-", "");
                                            }else{
                                            formName="formNonEsistente"
                                            }
                                            loadingScreen("Salvataggio in corso...", "loading");
                                            var templateName=formName.substring(0,formName.indexOf('_'));
                                            try{
                                            var myElement={};
                                            myElement.id=formName; //formName adesso è uguale al campo che sto modificando
                                            myElement.type=$('#'+formName).is("input") ? $('#'+formName).attr('type') : $('#'+formName).prop('nodeName') ;
                                            myElement.metadata={};
                                            label= $('#'+formName).attr('name');
                                            if(myElement.type=='CHECKBOX'){
                                            var my_val=new Array();//prendo tutti quelly checked
                                            var and=false;
                                            $('input[type="checkbox"][id="'+formName+'"]:checked').each(function(key,myChecked){
                                            if(and){
                                            my_val+="&";
                                            }
                                            my_val+=label+"="+$(myChecked).val();
                                            and=true;
                                            });
                                            console.log(my_val);
                                            if(my_val.length==0){
                                            my_val="";
                                            myElement.metadata[label]=my_val;
                                            }
                                            else{
                                            myElement.metadata=my_val;
                                            }
                                            }
                                            else if(myElement.type=='RADIO'){
                                            if($('#'+formName+':checked').length>0){
                                            myElement.metadata[label]=$('#'+formName+':checked').val();
                                            }
                                            else {
                                            myElement.metadata[label]='';
                                            }
                                            }
                                            else{
                                            myElement.metadata[label]=$('#'+formName).val();
                                            }
                                            // myElement.metadata=JSON.stringify(myElement.metadata);
                                            $.ajax({
                                            method : 'POST',
                                            url :  '${baseUrl}/app/rest/dm/updateMetdata/' + $('#update-'+formName+' [name^="elId"]').val()+'/'+$('#update-'+formName+' [name^="mdId"]').val(),
                                            data : myElement.metadata
                                            }).done(function(data){
                                            bootbox.hideAll();
                                            if (data.result=="OK") {
                                            loadingScreen("Salvataggio effettuato", "green_check");
                                            //Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
                                            window.setTimeout(function(){
                                            bootbox.hideAll();
                                            }, 3000);
                                            if (data.redirect){
                                            window.location.href=data.redirect;
                                            }
                                            }else {
                                            loadingScreen("Errore salvataggio!", "alerta");
                                            }
                                            }).fail(function(){
                                            bootbox.hideAll();
                                            loadingScreen("Errore salvataggio!", "alerta");
                                            });
                                            }catch(err){
                                            bootbox.hideAll();
                                            loadingScreen("Errore salvataggio!", "alerta");
                                            console.log(err);
                                            }
                                            }

                                            function attachFile(buttonClicked){
                                            var $form=$($(buttonClicked).data('rel'));
                                            if($(buttonClicked).attr('id')){
                                            var formName=$(buttonClicked).attr('id').replace("salvaForm-", "");
                                            }else{
                                            formName="formNonEsistente";
                                            }
                                            loadingScreen("Salvataggio in corso...", "loading");
                                            var templateName=formName.substring(0,formName.indexOf('_'));
                                            try{
                                            var formData=new FormData($("#"+formName)[0]);
                                            var paramID=formName.replace("update","myFile");
                                            var go=false;
                                            if(paramID=='fileName'){
                                            if($("#"+paramID).prop("files").length>0){
                                            var file=$("#"+paramID).prop("files")[0];
                                            formData.append("file",file);
                                            go=true;
                                            }
                                            else{
                                            alert("E' necessario allegare un file");
                                            }
                                            }
                                            else{
                                            go=true;
                                            formData=new FormData($('#'+formName)[0]);
                                            }
                                            if(go){
                                            $.ajax({
                                            method : 'POST',
                                            url :  '${baseUrl}/app/rest/dm/attachFile/' + $('#'+formName+' [name^="elId"]').val(),
                                            data : formData,
                                            contentType:false,
                                            processData:false,
                                            async:false,
                                            cache:false
                                            }).done(function(data){
                                            bootbox.hideAll();
                                            if (data.result=="OK") {
                                            loadingScreen("Salvataggio effettuato", "green_check");
                                            //Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
                                            window.setTimeout(function(){
                                            bootbox.hideAll();
                                            }, 3000);
                                            if (data.redirect){
                                            //window.location.href=data.redirect;
                                            }
                                            }else {
                                            loadingScreen("Errore salvataggio!", "alerta");
                                            }
                                            }).fail(function(){
                                            bootbox.hideAll();
                                            loadingScreen("Errore salvataggio!", "alerta");
                                            });
                                            }
                                            }catch(err){
                                            bootbox.hideAll();
                                            loadingScreen("Errore salvataggio!", "alerta");
                                            console.log(err);
                                            }
                                            }

                                            function refreshProcesses(){ //richiamata dai bottoni per start e stop
                                            //OTTENGO WORKLOWS (in esecuzione)
                                            $.getJSON('${baseUrl}/app/rest/documents/activeProcesses/${model["element"].id}',function(data){
                                            //console.log("ATTIVI ",data);
                                            var activeProcesses=data;
                                            container_active=$("#ACTIVE_PROCESSES");
                                            container_active.html("");
                                            for (i=0;i<activeProcesses.length;i++){
                                            stopLink=$('<a>');
                                                stopLink.attr('data-process-id', activeProcesses[i].id);
                                                stopLink.attr('data-process-key', activeProcesses[i].definition.key);
                                                stopLink.attr('data-element-id', '${model["element"].id}');
                                                stopLink.html("<i class='fa fa-trash'></i> Termina");
                                                stopLink.click(function(){
                                                loadingScreen("Terminazione processo in corso...", "loading");
                                                elId=$(this).attr('data-element-id');
                                                pKey=$(this).attr('data-process-key');
                                                pId=$(this).attr('data-process-id');
                                                //console.log('Key Processo: ',pId);
                                                $.post( '${baseUrl}/app/rest/dm/terminateProcess', { elId : elId, pKey: pKey, pId: pId } ).done(function( data ) {
                                                refreshProcesses();
                                                bootbox.hideAll();
                                                });
                                                });
                                                processItem=$("<li>Processo: "+activeProcesses[i].definition.key+" Id Istanza: "+activeProcesses[i].id+" </li>");
                                                processItem.append(stopLink);
                                                container_active.append(processItem);
                                                }
                                                if(activeProcesses.length>0){
                                                stopLink=$('<a>');
                                                    stopLink.attr('data-element-id', '${model["element"].id}');
                                                    stopLink.html("<i class='fa fa-trash'></i> Termina");
                                                    stopLink.click(function(){
                                                    loadingScreen("Terminazione processo in corso...", "loading");
                                                    elId=$(this).attr('data-element-id');
                                                    $.post( '${baseUrl}/app/rest/dm/terminateAllProcesses', { elId : elId} ).done(function( data ) {
                                                    refreshProcesses();
                                                    bootbox.hideAll();
                                                    });
                                                    });
                                                    processItem=$("<li><b>Termina tutti i processi attivi</b></li>");
                                                    processItem.append(stopLink);
                                                    container_active.append(processItem);
                                                    }
                                                    $("#ACTIVE_PROCESSES_SPAN").remove();
                                                    });

                                                    //OTTENGO WORKLOWS (in disponibili)
                                                    $.getJSON('${baseUrl}/app/rest/documents/availableProcesses/${model["element"].id}',function(data){
                                                    //console.log("disponibili ",data);
                                                    var availableProcesses=data;
                                                    container_available=$("#AVAILABLE_PROCESSES");
                                                    container_available.html("");
                                                    for (i=0;i<availableProcesses.length;i++){
                                                    startLink=$('<a>');
                                                        startLink.attr('data-process-key', availableProcesses[i].key);
                                                        startLink.attr('data-element-id', '${model["element"].id}');
                                                        startLink.attr('href', '#');
                                                        startLink.html("<i class='fa fa-play'></i> Avvia");
                                                        startLink.click(function(){
                                                        elId=$(this).attr('data-element-id');
                                                        pKey=$(this).attr('data-process-key');
                                                        bootbox.dialog( {
                                                        title: "Modalità user override",
                                                        message:'<div class="form-group"><label for="overrideUser" class="control-label no-padding-right">User override:</label>&nbsp;<input type="text" size="25" value="" id="overrideUser" name="overrideUser"></div><div class="form-group"><span style="font-size:small">lascia vuoto per avviarlo con utenza corrente</span></div>',
                                                        buttons: {
                                                        success: {
                                                        label: "Avvia processo",
                                                        className: "btn-success",
                                                        callback: function() {
                                                        loadingScreen("Avvio processo in corso...", "loading");

                                                        //console.log('Id Elemento: ',elId);
                                                        //console.log('Key Processo: ',pKey);

                                                        $.post( '${baseUrl}/app/rest/dm/startProcess', { elId: elId, pKey: pKey, overrideUser: $('#overrideUser').val() } ).done(function( data ) {
                                                        if(data.result=='ERROR'){
                                                        bootbox.hideAll();
                                                        bootbox.alert(data.errorMessage);
                                                        }
                                                        else{
                                                        refreshProcesses();
                                                        bootbox.hideAll();
                                                        }
                                                        });
                                                        }
                                                        },
                                                        cancel: {
                                                        label: "Annulla",
                                                        className: "btn-cancel",
                                                        callback: function(){
                                                        }
                                                        }
                                                        },
                                                        onEscape: function(){
                                                        }
                                                        });
                                                        });
                                                        processItem=$("<li>Processo: "+availableProcesses[i].key+" </li>");
                                                        processItem.append(startLink);
                                                        //console.log(processItem);
                                                        container_available.append(processItem);
                                                        $("#AVAILABLE_PROCESSES_SPAN").remove();
                                                        }
                                                        });

                                                        //OTTENGO WORKLOWS (in terminati)
                                                        $.getJSON('${baseUrl}/app/rest/documents/terminatedProcesses/${model["element"].id}',function(data){
                                                        //console.log(data);
                                                        var terminatedProcesses=data;
                                                        container_terminated=$("#TERMINATED_PROCESSES");
                                                        container_terminated.html("");
                                                        for (i=0;i<terminatedProcesses.length;i++){

                                                        container_terminated.append("<li>Processo: "+terminatedProcesses[i].key+" </li>");
                                                        }
                                                        });
                                                        }

                                                        refreshProcesses();

                                                        refreshPolicies();
                                                        $("#POLICY_TAB").append($("#policy_tb").html());
                                                        $("#add-policy").click(function(){
                                                        loadingScreen("Creazione policy in corso...", "loading");
                                                        $.post ( '${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/create/',
                                                        {   policyId: null,
                                                        groups: null,
                                                        users: null,
                                                        allUsers: null,
                                                        cuser: null
                                                        }
                                                        ).done(function( data ) {
                                                        refreshPolicies();
                                                        bootbox.hideAll();
                                                        });

                                                        });
                                                        //GESTIONE POLICY
                                                        function refreshPolicies(){
                                                        $("#policy-list-availables").html("");
                                                        $.getJSON('${baseUrl}/app/rest/documents/${model["element"].id}/acl/getAll',function(policies){
                                                        //console.log("POLICY");
                                                        //console.log(policies);
                                                        $(policies).each(function(){
                                                        $("#policy-list-availables").append(policyListRow(this));
                                                        });
                                                        });
                                                        bootbox.hideAll();
                                                        }
                                                        var policies_div=$('<div>');
                                                            var policies_select=$('<select style="font-size:14px;">');
                                                                var option_policy=$("<option>");
                                                                    policies_select.attr("id","policies_select");
                                                                    policies_select.append(option_policy);

                                                                    $.get( "${baseUrl}/app/rest/admin/policy/getAll").done(function( pol ) {
                                                                    //console.log(pol);
                                                                    $(pol).each(function(){
                                                                    option_policy=$("<option>");
                                                                    option_policy.val(this.id);
                                                                    option_policy.html(this.name);
                                                                    policies_select.append(option_policy);
                                                                    });

                                                                    });
                                                                    $("#cuser").change(function(){
                                                                    if($("#cuser").prop("checked")){
                                                                    $(".token-input-list-facebook").parent().hide();
                                                                    }
                                                                    else{
                                                                    $(".token-input-list-facebook").parent().show();
                                                                    }
                                                                    });

                                                                    policies_div.append(policies_select);
                                                                    function policyListRow(jsonRow){
                                                                    checkEnabled=true;
                                                                    ret=$('<tr>');
                            //PRIMA COLONNA: POLICY
                            if(jsonRow.predPolicy){
                            policyName=$('<td>');
                                policyName.html(jsonRow.predPolicy.name);
                                updateLink=$('<a style="float:right;" title="Rimuovi Policy">');
                                    updateLink.attr('update-aclId', jsonRow.id);
                                    updateLink.html("<i class='fa fa-remove'></i>&nbsp;");
                                    updateLink.attr('href','#');
                                    updateLink.click(function (){
                                    loadingScreen("Aggiornamento policy in corso...", "loading");
                                    aclId=$(this).attr('update-aclId');
                                    $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/removePolicy', { value: true } ).done(function( data ) {
                                    refreshPolicies();
                                    bootbox.hideAll();
                                    });
                                    return false;
                                    });
                                    policyName.append(updateLink);
                                    ret.append(policyName);
                                    checkEnabled=false;//se ho una policy non posso disabilitare/abilitare le varie voci
                                    }
                                    else{
                                    policyName=$('<td>');
                                updateLink=$('<a style="float:right;" title="Aggiungi Policy">');
                                    updateLink.attr('addPolicy-aclId', jsonRow.id);
                                    updateLink.html("<i class='fa fa-plus'></i>&nbsp;");
                                    updateLink.attr('href','#');
                                    updateLink.click(function(){
                                    bootbox.dialog( {
                                    title: "Aggiungi Policy",
                                    message:"Policy: "+$(policies_div).html(),
                                    buttons: {
                                    success: {
                                    label: "Aggiungi Policy",
                                    className: "btn-success",
                                    callback: function() {
                                    loadingScreen("Aggiunta Policy in corso...", "loading");
                                    //aclId=$(this).attr('addPolicy-aclId').val();
                                    $.post( '${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+jsonRow.id+'/addPolicy',
                                    {   policyId: $('#policies_select').val(), value:true}
                                    ).done(function( data ) {
                                    refreshPolicies();
                                    bootbox.hideAll();
                                    });
                                    }
                                    },
                                    cancel: {
                                    label: "Annulla",
                                    className: "btn-cancel",
                                    callback: function(){
                                    }
                                    }
                                    },
                                    onEscape: function(){
                                    }
                                    });
                                    return false;
                                    });
                                    policyName.append(updateLink);
                                    ret.append(policyName);
                                    }
                                    //SECONDA COLONNA: CONTAINER
                                    var ContainersTD=$("<td>");
                                $(jsonRow.containers).each(function(k,itm){
                                if(itm.authority){
                                ContainersTD.html(ContainersTD.html()+"g:");
                                }
                                else{
                                ContainersTD.html(ContainersTD.html()+"u:");
                                }
                                ContainersTD.html(ContainersTD.html()+itm.container);
                                updateLink=$('<a style="float:right;" title="Rimuovi Container">');
                                    updateLink.html("<i class='fa fa-remove'></i>&nbsp;");
                                    updateLink.attr('href','#');
                                    updateLink.click(function (){
                                    loadingScreen("Eliminazione container in corso...", "loading");
                                    $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+jsonRow.id+'/removeContainer/'+itm.id, { value: true } ).done(function( data ) {
                                    refreshPolicies();
                                    bootbox.hideAll();
                                    });
                                    return false;
                                    });
                                    ContainersTD.append(updateLink);
                                    ContainersTD.append("<br/>");
                                    });
                                    //ContainersTD+="</td>";
                            updateLink=$('<a style="float:right;" title="Aggiungi Container">');
                                updateLink.html("<i class='fa fa-plus'></i>&nbsp;");
                                updateLink.attr('href','#');
                                updateLink.click(function (){
                                bootbox_message=$("#permission-dialog");
                                bootbox.dialog( {
                                title: "Aggiungi Container",
                                message:bootbox_message,
                                buttons: {
                                success: {
                                label: "Aggiungi Container",
                                className: "btn-success",
                                callback: function() {
                                $("#permission-div").append($("#permission-dialog"));
                                loadingScreen("Aggiungo Container...", "loading");
                                $.post( '${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+jsonRow.id+'/addContainer',
                                {   groups: $('#groups').val(),
                                users: $("#users").val(),
                                allUsers: $("#allUsers").prop("checked") ? true: null,
                                cuser: $("#cuser").prop("checked") ? true: null
                                }
                                ).done(function( data ) {
                                refreshPolicies();
                                bootbox.hideAll();
                                });
                                }
                                },
                                cancel: {
                                label: "Annulla",
                                className: "btn-cancel",
                                callback: function(){
                                $("#permission-div").append($("#permission-dialog"));
                                }
                                }
                                },
                                onEscape: function(){
                                $("#permission-div").append($("#permission-dialog"));
                                }
                                });
                                return false;
                                });
                                ContainersTD.append(updateLink);
                                ContainersTD.append("<br/>");
                                ret.append(ContainersTD);

                                //COLONNE OPZIONI
                                var actionTD=$('<td>');
                                    var updateLink;
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        if (jsonRow.policy.canView){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.attr('href','#');
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canView', { value: !jsonRow.policy.canView } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canView){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
            updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canCreate){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canCreate', { value: !jsonRow.policy.canCreate } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canCreate){
           updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canUpdate){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canUpdate', { value: !jsonRow.policy.canUpdate } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canUpdate){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canAddComment){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canAddComment', { value: !jsonRow.policy.canAddComment } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canAddComment){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canModerate){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canModerate', { value: !jsonRow.policy.canModerate } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canModerate){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canDelete){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canDelete', { value: !jsonRow.policy.canDelete } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canDelete){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canChangePermission){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canChangePermission', { value: !jsonRow.policy.canChangePermission } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canChangePermission){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canAddChild){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canAddChild', { value: !jsonRow.policy.canAddChild } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canAddChild){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canRemoveCheckOut){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canRemoveCheckOut', { value: !jsonRow.policy.canRemoveCheckOut } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canRemoveCheckOut){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canLaunchProcess){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canLaunchProcess', { value: !jsonRow.policy.canLaunchProcess } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canLaunchProcess){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canEnableTemplate){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canEnableTemplate', { value: !jsonRow.policy.canEnableTemplate } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canEnableTemplate){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
           updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    actionTD=$('<td>');
                                    if(checkEnabled){
                                    updateLink=$('<a>');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.attr('href','#');
                                        if (jsonRow.policy.canBrowse){
                                        updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
                                        }
                                        else{
                                        updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
                                        }
                                        updateLink.click(function (){
                                        loadingScreen("Aggiornamento policy in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/canBrowse', { value: !jsonRow.policy.canBrowse } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        }
                                        else{
                                        updateLink=$('<span>');
        if (jsonRow.policy.canBrowse){
            updateLink.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        }
        else{
            updateLink.html("<i class='fa fa-square-o'></i>&nbsp;");
        }
    }
    actionTD.append(updateLink);
    ret.append(actionTD);

    //PENULTIMA COLONNA: TEMPLATE
    if(jsonRow.detailTemplate){
        templateName=$('<td>');
                                    templateName.html(jsonRow.detailTemplate);
                                    updateLink=$('<a style="float:right;" title="Rimuovi Policy">');
                                        updateLink.attr('update-aclId', jsonRow.id);
                                        updateLink.html("<i class='fa fa-remove'></i>&nbsp;");
                                        updateLink.attr('href','#');
                                        updateLink.click(function (){
                                        loadingScreen("Rimozione template ad hoc in corso...", "loading");
                                        aclId=$(this).attr('update-aclId');
                                        $.post('${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+aclId+'/removeTemplatePolicy', { templateToRemove: jsonRow.detailTemplate } ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        return false;
                                        });
                                        templateName.append(updateLink);
                                        ret.append(templateName);
                                        checkEnabled=false;//se ho una policy non posso disabilitare/abilitare le varie voci
                                        }
                                        else{
                                        templateName=$('<td>');
                                    updateLink=$('<a style="float:right;" title="Aggiungi Template ad hoc">');
                                        updateLink.attr('addPolicy-aclId', jsonRow.id);
                                        updateLink.html("<i class='fa fa-plus'></i>&nbsp;");
                                        updateLink.attr('href','#');
                                        updateLink.click(function(){
                                        bootbox.dialog( {
                                        title: "Aggiungi Template ad hoc",
                                        message:'<div class="form-group"><label for="detailTemplate" class="control-label no-padding-right">Template ad-hoc:</label>&nbsp;<input type="text" size="25" value="" id="detailTemplate" name="detailTemplate"></div>',
                                        buttons: {
                                        success: {
                                        label: "Aggiungi Template ad hoc",
                                        className: "btn-success",
                                        callback: function() {
                                        loadingScreen("Aggiunta Policy in corso...", "loading");
                                        //aclId=$(this).attr('addPolicy-aclId').val();
                                        $.post( '${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/edit/'+jsonRow.id+'/addTemplatePolicy',
                                        {   templateToAdd: $('#detailTemplate').val()}
                                        ).done(function( data ) {
                                        refreshPolicies();
                                        bootbox.hideAll();
                                        });
                                        }
                                        },
                                        cancel: {
                                        label: "Annulla",
                                        className: "btn-cancel",
                                        callback: function(){
                                        }
                                        }
                                        },
                                        onEscape: function(){
                                        }
                                        });
                                        return false;
                                        });
                                        templateName.append(updateLink);
                                        ret.append(templateName);
                                        }

                                        //COLONNA ELIMINA POLICY
                                        actionTD=$('<td>');
                                    var deleteLink=$('<a>');
                                        deleteLink.attr('remove-aclId', jsonRow.id);
                                        deleteLink.html("<i class='fa fa-trash'></i> Elimina");
                                        deleteLink.click(function (){
                                        loadingScreen("Eliminazione policy in corso...", "loading");
                                        aclId=$(this).attr('remove-aclId');
                                        $.get( '${baseUrl}/app/rest/dm/'+${model["element"].id}+'/acl/delete/'+aclId, { aclId: aclId } ).done(function( data ) {
                                        if(data.result=="KO"){
                                        loadingScreen("Errore durante l'eliminazione...");
                                        }
                                        else{
                                        refreshPolicies();
                                        }

                                        });
                                        });
                                        actionTD.append(deleteLink);
                                        ret.append(actionTD);
                                        return ret;
                                        }


                                    </@script>
                                    <@breadcrumbsData model['element'] page.description />


