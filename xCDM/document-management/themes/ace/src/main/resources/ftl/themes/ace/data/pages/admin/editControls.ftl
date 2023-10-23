
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["jquery-ui-full", "colorpicker", "datepicker","pages/studio.css","x-editable","select2","jstree"],
"scripts" : ["jquery-ui-full","colorpicker", "datepicker","bootbox", "token-input" ,"elementEdit","x-editable","select2","base","jstree","assets/js/jquery.nestable.min.js"],
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
<#global breadcrumbs={"title":"Control Edit Page","links":[]} />
<#global breadcrumbs=breadcrumbs+{"links":breadcrumbs.links+[link]} />
<#assign typeIdName= id?split(".")[0]/>
<@script>
console.log('${typeIdName}');

var fields=[];

$('.select2').select2();
$('.dd').nestable();

$('.dd-handle a').on('mousedown', function(e){
e.stopPropagation();
});

$('[data-rel="tooltip"]').tooltip();


$("[data-type='field-select-altro']").hide();

function argFieldAltro(formEl){
fieldSelect=formEl.find("[data-type='field-select']").each(function(){
sEl=$(this);
argValEl=formEl.find("[data-type='field-select-altro'][data-id='"+sEl.attr('data-id')+"']");
if (sEl.val()=='99'){
argValEl.show();
}else {
argValEl.hide();
}
});
}

var decodes=new Object();
decodes['gt']='&gt;';
decodes['ge']='&ge;';
decodes['lt']='&lt;';
decodes['le']='&le;';
decodes['eq']='=';
decodes['ne']='&ne;';
decodes['is_int']='&egrave; intero';
decodes['is_number']='&egrave; numerico';
decodes['disabled']='&egrave; disabilitato';

function opSelection(formEl){
sEl=formEl.find("[data-type='op']");
argEl=formEl.find("[data-type='field-select'][data-id='arg2']");
argValEl=formEl.find("[data-type='field-select-altro'][data-id='arg2']");
if (sEl.val()=='is_number' || sEl.val()=='is_int' || sEl.val()=='disabled'){
argEl.hide();
argValEl.hide();
}else {
argEl.show();
argFieldAltro(formEl);
}

}

function registerAddCondition(){
$('select[name="check"]').unbind('change');
$('select[name="check"]').change(function(){
if ($(this).val()=='isNumeric' || $(this).val()=='isFloat' || $(this).val()=='isInt' || $(this).val()=='isString'){
$(this).parent().find('[name="rightHandFields"]').select2("val", "");
$(this).parent().find('[name="rightHandValues"]').val("");
$(this).parent().find('span[data-hand="right"]').hide();
}else {
$(this).parent().find('span[data-hand="right"]').show();
}

});

$('.addCondition').unbind('click');
$('.addCondition').click(function(){
condType=$(this).attr('data-type');
ruleId=$($(this).parents("[data-type='rule']")[0]).attr('data-id');
if (condType=='mandatory'){
var doPreQuest=true;
for (var i=0;i<jsonData.rules.length;i++){
if (jsonData.rules[i].rule==ruleId){
if(jsonData.rules[i].criteria[condType]){
if (jsonData.rules[i].criteria[condType].conditions){
if (jsonData.rules[i].criteria[condType].conditions.or){
if (jsonData.rules[i].criteria[condType].conditions.or.length>0){
doPreQuest=false;
}
}
}else {
if (jsonData.rules[i].criteria[condType].always){
doPreQuest=false;
}
}
}
}
}
if (doPreQuest){
(function(callElement, condType, ruleId){
bootbox.dialog({
message:'Tipo di controllo',
buttons: {
'Sempre': function(){
var rule=null;
for (var i=0;i<jsonData.rules.length;i++){
if (jsonData.rules[i].rule==ruleId){
rule=jsonData.rules[i];
if (!jsonData.rules[i].criteria.mandatory) jsonData.rules[i].criteria.mandatory={};
jsonData.rules[i].criteria.mandatory.always=true;
}
}
proto=$('[data-type="rule"][data-id="'+ruleId+'"]');
updateRule(proto,rule);
},
'Definisci condizioni': function(){
attachConditionEditor(callElement, true, null, null);
}
}
});
})($(this), condType, ruleId);
}else {
for (var i=0;i<jsonData.rules.length;i++){
console.log(jsonData.rules[i].rule, ruleId);
if (jsonData.rules[i].rule==ruleId){
console.log(jsonData.rules[i], "sono qui");
if(jsonData.rules[i].criteria[condType]){
console.log(jsonData.rules[i].criteria[condType], condType, "sono qui2");

if (jsonData.rules[i].criteria[condType].always){
console.log(jsonData.rules[i].criteria[condType].always, "sono qui3");
var liId=ruleId+'-sep-'+condType+'-sep-always';
if (confirm('proseguendo verra\' eliminata la condizione "always". Proseguire?')){
deleteElementNoConfirm(liId);
}else {
return false;
}
}
}
}
}
attachConditionEditor($(this), true, null, null);
}
}else {
attachConditionEditor($(this), true, null, null);
}
return false;
});
$('.addAndCondition').unbind('click');
$('.addAndCondition').click(function(){
$(this).hide();
attachConditionEditor($(this), false, 0, null);
return false;
});
$('.conditionEditor').unbind('click');
$('.conditionEditor').click(function(){
conditionEditor();
});
$('.condtionEditorClose').unbind('click');
$('.condtionEditorClose').click(function(){
$('[data-id="conditionEditor"]').hide();
$('#condition-widget-main').html("");
});
}

var formIdx=0;

function attachConditionEditor(callElement, isNew, condIdx, data){
proto=$('#prototypes .form-block').clone();
if (isNew){
$('#condition-widget-main').html("");
if (data==undefined){
field=$($(callElement).parents("[data-type='rule']")[0]).attr('data-id');
condType=$(callElement).attr('data-type');
}else {
field=$($(callElement).parents("[data-type='rule']")[0]).attr('data-id');
condType=$(callElement).parent().parent().parent().attr('data-type');
}
$('#condition-widget-main').attr('data-src-id',field);
$('#condition-widget-main').attr('data-src-type',condType);
$('#condition-widget-main').attr('data-src-idx',condIdx);
if (condIdx==null) {
$('#condition-widget-main').attr('data-src-idx',-1);
}

}
else {
$('#condition-widget-main').find('.addAndCondition').remove();
formIdx++;
proto.find('form').attr('data-form-idx',formIdx);
remLink=$('<a>');
    remLink.attr('href','#');
    remLink.html('<i class="fa fa-trash"></i> rimuovi condizione');
    (function(remLink, formIdx){
    remLink.click(function(){
    $('#condition-widget-main').find('form[data-form-idx="'+formIdx+'"]').remove();
    $(this).remove();
    return false;
    });
    })(remLink, formIdx);
    proto.prepend(remLink);
    }

    for (i=0;i<fields.length;i++){
    opt=$('<option>');
    opt.attr('value',fields[i]);
    opt.html(fields[i]);
    proto.find('[name="leftHandField"]').append(opt.clone());
    proto.find('[name="rightHandFields"]').append(opt);
    }
    if (data){
    proto.find('[name="leftHandField"]').val(data.leftHandField);
    proto.find('[name="check"]').val(data.check);
    if (data.rightHandFields) proto.find('[name="rightHandFields"]').val(data.rightHandFields);
    if (data.rightHandValues && data.rightHandValues.length>0){
    var rhvalues='';
    for (var r=0;r<data.rightHandValues.length;r++){
    if (rhvalues!='') rhvalues+='|';
    rhvalues+=data.rightHandValues[r];
    }
    proto.find('[name="rightHandValues"]').val(rhvalues);
    }
    }
    proto.find('select').select2();
    $('#condition-widget-main').append(proto);
    if (isNew){
    $('[data-id="conditionEditor"]').show();
    scrollToTop=$('[data-id="conditionEditor"]').offset().top-200;
    $('html, body').animate({
    scrollTop: scrollToTop
    }, 1000);
    }
    registerAddCondition();
    }

    function conditionEditor(){
    forms=$('#condition-widget-main').find('form');
    srcId=$('#condition-widget-main').attr('data-src-id');
    srcType=$('#condition-widget-main').attr('data-src-type');
    srcIdx=$('#condition-widget-main').attr('data-src-idx');
    srcIdx-=0;
    conds=[];
    for (var i=0;i<forms.length;i++){
    form=$(forms[i]);
    cond=new Object();
    cond.leftHandField=form.find("[name='leftHandField']").val();
    cond.check=form.find("[name='check']").val();
    cond.rightHandFields=form.find("[name='rightHandFields']").val();
    cond.rightHandValues=form.find("[name='rightHandValues']").val().split('|');
    conds[i]=cond;
    }
    var rule=null;
    for (var i=0;i<jsonData.rules.length;i++){
    if (jsonData.rules[i].rule==srcId){
    if (srcIdx>=0){
    jsonData.rules[i].criteria[srcType].conditions.or[srcIdx].and=conds;
    }else {
    if (!jsonData.rules[i].criteria[srcType]) jsonData.rules[i].criteria[srcType]={};
    if (!jsonData.rules[i].criteria[srcType].conditions) jsonData.rules[i].criteria[srcType].conditions={};
    if (!jsonData.rules[i].criteria[srcType].conditions.or) jsonData.rules[i].criteria[srcType].conditions.or=[];
    nxtIdx=jsonData.rules[i].criteria[srcType].conditions.or.length;
    jsonData.rules[i].criteria[srcType].conditions.or[nxtIdx]={};
    jsonData.rules[i].criteria[srcType].conditions.or[nxtIdx].and=conds;
    }
    rule=jsonData.rules[i];
    }
    }
    proto=$('[data-type="rule"][data-id="'+srcId+'"]');
    updateRule(proto,rule);
    $('#condition-widget-main').html("");
    $('[data-id="conditionEditor"]').hide();
    }

    var liIdx=0;

    function writeConditionFromJson(condition, proto, ruleId, conditionType){
    if (condition.always){
    sc='always';
    cnt=$('<li>');
        var liId=ruleId+'-sep-'+conditionType+'-sep-always';
        if ($('#'+liId)) $('#'+liId).remove();
        cnt.attr('id',liId);
        spanElLinkCnt=$('<span>');
			spanElEditLink=$('<a>');
			spanElEditLink.attr('href','#');
			(function(elId, spanElEditLink){
				spanElEditLink.click(function(){
					editElement($(this), liId);
					return false;
				});
			})(liId, spanElEditLink);
			//spanElEditLink.attr('onclick',"editElement('"+liId+"');return false;");
			spanElEditLink.html("<i class='fa fa-pencil'></i> ");
			spanElDelLink=$('<a>');
			spanElDelLink.attr('href','#');
			(function(liId){
				spanElDelLink.click(function(){
					deleteElement(liId);
					return false;
				});
			})(liId)
			//spanElDelLink.attr('onclick',"deleteElement('"+liId+"');return false;");
			spanElDelLink.html("<i class='fa fa-trash'></i> ");
			spanElLinkCnt.append(spanElEditLink);
			spanElLinkCnt.append("&nbsp;");
			spanElLinkCnt.append(spanElDelLink);
			spanElLinkCnt.append("&nbsp;");
			cnt.html(spanElLinkCnt);
			cnt.append(sc);
			dstEl=proto.find('[data-id="conditions"][data-type="'+conditionType+'"]').append(cnt);
			$('[data-rel=popover]').popover({html:true,
		        trigger: 'manual'
		    }).click(function(e) {
		        $(this).popover('toggle');
		        e.preventDefault();
		    });
	}
	if (condition.conditions){
		for (var oIdx=0;oIdx<condition.conditions.or.length;oIdx++){
			liIdx++;
			sc='';
			cnt=$('<li>');
        var liId=ruleId+'-sep-'+conditionType+'-sep-'+oIdx;
        if ($('#'+liId)) $('#'+liId).remove();
        cnt.attr('id',liId);
        orConds=condition.conditions.or[oIdx];
        for (var aIdx=0;aIdx<orConds.and.length;aIdx++){
        if (aIdx>0) sc+=" && ";
        andCond=orConds.and[aIdx];
        sc+=andCond.leftHandField+' ';
        sc+=andCond.check;
        if (andCond.rightHandFields && andCond.rightHandFields.length>0){
        sc+=" fields[";
        for (var fIdx=0;fIdx<andCond.rightHandFields.length;fIdx++){
        if (fIdx>0) sc+=", ";
        sc+=andCond.rightHandFields[fIdx];
        }
        sc+="]";
        }
        if (andCond.rightHandValues && andCond.rightHandValues.length>0){
        sc+=" values[";
        for (var fIdx=0;fIdx<andCond.rightHandValues.length;fIdx++){
        if (fIdx>0) sc+=", ";
        sc+=andCond.rightHandValues[fIdx];
        }
        sc+="]";
        }
        }
        spanElLinkCnt=$('<span>');
			spanElEditLink=$('<a>');
			spanElEditLink.attr('href','#');
			//spanElEditLink.attr('onclick',"editElement('"+liId+"');return false;");
			(function(elId, spanElEditLink){
				spanElEditLink.click(function(){
					editElement($(this), liId);
					return false;
				});
			})(liId, spanElEditLink);

			spanElEditLink.html("<i class='fa fa-pencil'></i> ");
			spanElDelLink=$('<a>');
			spanElDelLink.attr('href','#');
			//spanElDelLink.attr('onclick',"deleteElement('"+liId+"');return false;");

			(function(liId){
				spanElDelLink.click(function(){
					deleteElement(liId);
					return false;
				});
			})(liId)
			spanElDelLink.html("<i class='fa fa-trash'></i> ");
			spanElLinkCnt.append(spanElEditLink);
			spanElLinkCnt.append("&nbsp;");
			spanElLinkCnt.append(spanElDelLink);
			spanElLinkCnt.append("&nbsp;");
			cnt.html(spanElLinkCnt);
			cnt.append(sc);
			dstEl=proto.find('[data-id="conditions"][data-type="'+conditionType+'"]').append(cnt);
			$('[data-rel=popover]').popover({html:true,
		        trigger: 'manual'
		    }).click(function(e) {
		        $(this).popover('toggle');
		        e.preventDefault();
		    });
		}
    }
}

function liIdSplit(id){
	split=id.split('-sep-');
	liIdSpec={};
	liIdSpec.rule=split[0];
	liIdSpec.type=split[1];
	liIdSpec.condIdx=split[2];
	return liIdSpec;
}

function deleteElementNoConfirm(id){
	$('#'+id).remove();
		liIdSpec=liIdSplit(id);
		var rule=null;
		for (var i=0;i<jsonData.rules.length;i++){
			if (liIdSpec.rule==jsonData.rules[i].rule){
				rule=jsonData.rules[i];
				if (liIdSpec.condIdx=='always' || jsonData.rules[i].criteria[liIdSpec.type].conditions.or.length==1){
					jsonData.rules[i].criteria[liIdSpec.type]={}
				}else {
					var conds=jsonData.rules[i].criteria[liIdSpec.type].conditions.or;
					jsonData.rules[i].criteria[liIdSpec.type].conditions.or=[];
					liIdSplit[condIdx]-=0;
					for (var c=0;c<conds.length;c++){
						var nxtIdx=jsonData.rules[i].criteria[liIdSpec.type].conditions.or.length;
						if (c!=liIdSplit[condIdx]) jsonData.rules[i].criteria[liIdSpec.type].conditions.or[nxtIdx]=conds[c];
					}
				}
			}
		}
		proto=$('[data-type="rule"][data-id="'+liIdSpec.rule+'"]');
		updateRule(proto,rule);
}

function deleteElement(id){
	if (confirm('Sei sicuro?')) {
		deleteElementNoConfirm(id);
	}
	$('.popover').each(function() {
		  $(this).hide();
	});
}

function editElement(callElement, id){
	$('.popover').each(function() {
		  $(this).hide();
	});
	liIdSplitted=liIdSplit(id);
	if (liIdSplitted["condIdx"]!='always'){
		for (var i=0;i<jsonData.rules.length;i++){
		  if (jsonData.rules[i].rule==liIdSplitted.rule){
		    orConds=jsonData.rules[i].criteria[liIdSplitted.type].conditions.or;
		    var cond=orConds[liIdSplitted["condIdx"]].and;
		    for (var c=0;c<cond.length;c++){
		    	if (c==0) attachConditionEditor(callElement, true, liIdSplitted["condIdx"], cond[c]);
		    	else {
		    		attachConditionEditor(callElement, false, liIdSplitted["condIdx"], cond[c]);
		    	}
		    }
		  }
		}
	}
}


function addRule(rule){
	container=$('#rules');
	var proto=$("#prototypes [data-type='rule']").clone();
	proto.attr('data-id',rule.rule);
	proto.find('h5').html(rule.rule);
	for (i=0;i<fields.length;i++){
		opt=$('<option>');
    opt.attr('value',fields[i]);
    opt.html(fields[i]);
    proto.find('[name="fields"]').append(opt);
    }
    for (i=0;i<buttons.length;i++){
    opt=$('<option>');
    opt.attr('value',buttons[i]);
    opt.html(buttons[i]);
    proto.find('[name="buttons"]').append(opt.clone());
    }
    (function(proto,rule){
    proto.find('[name="fields"]').change(function(){
    for (var i=0;i<jsonData.rules.length;i++){
    if (jsonData.rules[i].rule==rule.rule){
    jsonData.rules[i].fields=$(this).val();
    }
    }
    });
    proto.find('[name="buttons"]').change(function(){
    for (var i=0;i<jsonData.rules.length;i++){
    if (jsonData.rules[i].rule==rule.rule){
    jsonData.rules[i].buttons=$(this).val();
    }
    }
    });
    })(proto,rule);
    (function(proto,rule){
    proto.find('.delete-rule').click(function(){
    if (confirm('Sei sicuro?')){
    ruleId=proto.attr('data-id');
    var rules=jsonData.rules;
    jsonData.rules=[];
    for (var i=0;i<rules.length;i++){
    if (rules[i].rule!=ruleId){
    jsonData.rules[jsonData.rules.length]=rules[i];
    }
    }
    $('li[data-type="rule"][data-id="'+ruleId+'"]').remove();
    }
    });
    })(proto,rule);
    updateRule(proto, rule);
    proto.find('select').select2();
    container.append(proto);
    registerAddCondition();
    }

    function updateRule(proto, rule){
    if (rule.fields) proto.find('[name="fields"]').val(rule.fields);
    if (rule.buttons) proto.find('[name="buttons"]').val(rule.buttons);
    for (var crit in rule.criteria){
    if (!$.isEmptyObject(rule.criteria[crit])) {
    criteria=rule.criteria[crit];
    writeConditionFromJson(criteria, proto, rule.rule, crit);
    }
    }
    proto.find('.emptyAndHide i').addClass('fa-square-o');
    proto.find('.emptyAndHide').attr('data-rule-id',rule.rule);
    if (rule.criteria){
    if (rule.criteria.empty){
    if (rule.criteria.empty.hide){
    proto.find('.emptyAndHide i').removeClass('fa-square-o');
    proto.find('.emptyAndHide i').addClass('fa-check-square-o');
    }
    }
    }
    proto.find('.emptyAndHide').click(function(){
    var checked=false;
    if ($(this).find('i.fa-square-o').length>0) {
    $(this).find('i').removeClass('fa-square-o');
    $(this).find('i').addClass('fa-check-square-o');
    checked=true;
    }else {
    $(this).find('i').addClass('fa-square-o');
    $(this).find('i').removeClass('fa-check-square-o');
    checked=false;
    }
    for (var i=0;i<jsonData.rules.length;i++){
    if (jsonData.rules[i].rule==$(this).attr('data-rule-id')){
    jsonData.rules[i].criteria.empty.hide=checked;
    }
    }
    console.log($(this).attr('data-rule-id'), checked);
    return false;
    });
    }

    function addNewButton(buttonId, buttonName){
    $('[name="buttons"]').append($('<option>', {
    value: buttonId,
    text : buttonName
    })).select2();
    }

    function deleteButton(buttonId){
    $('[name="buttons"] option[value="'+buttonId+'"]').remove();
    $('[name="buttons"]').select2();
    }


    function addField(fieldId){
    fields[fields.length]=fieldId;
    }

    var buttons=[];

    function addButton(button){
    buttons[buttons.length]=button.name;
    proto=$('#button-prototype').clone();
    proto.attr('data-ref',button.name);
    proto.attr('id','button-'+button.name);
    for (i=0;i<fields.length;i++){
    opt=$('<option>');
    opt.attr('value',fields[i]);
    opt.html(fields[i]);
    proto.find('[name="fields"]').append(opt);
    }
    proto.find('select').select2();
    if (button.fields!=undefined) proto.find('[name="fields"]').select2('val',button.fields);
    if (button.forms!=undefined) proto.find('[name="forms"]').select2('val',button.forms);
    proto.find('[name="txtRGB"]').css('background-color','');
    if (button.bkgrgb!=undefined) {
    proto.find('[name="bkgRGB"]').css('background-color','rgb('+button.bkgrgb[0]+','+button.bkgrgb[1]+','+button.bkgrgb[2]+')');
    proto.find('[name="bkgRGB"]').val(rgbToHex(button.bkgrgb[0],button.bkgrgb[1],button.bkgrgb[2]));
    proto.find('[name="bkgRGB_R"]').val(button.bkgrgb[0]);
    proto.find('[name="bkgRGB_G"]').val(button.bkgrgb[1]);
    proto.find('[name="bkgRGB_B"]').val(button.bkgrgb[2]);
    }
    if (button.txtrgb!=undefined) {
    proto.find('[name="txtRGB"]').css('background-color','rgb('+button.txtrgb[0]+','+button.txtrgb[1]+','+button.txtrgb[2]+')');
    proto.find('[name="txtRGB"]').val(rgbToHex(button.txtrgb[0],button.txtrgb[1],button.txtrgb[2]));
    proto.find('[name="txtRGB_R"]').val(button.txtrgb[0]);
    proto.find('[name="txtRGB_G"]').val(button.txtrgb[1]);
    proto.find('[name="txtRGB_B"]').val(button.txtrgb[2]);
    }
    proto.find('.colorpicker-element').colorpicker();
    proto.find('.colorpicker-element').colorpicker().on('changeColor', function(e) {
    var baseProto=$(this).parent().parent().parent();
    var name=baseProto.attr('data-ref');
    for (var i=0;i<jsonData.submitButtons.length;i++){
    if (jsonData.submitButtons[i].name==name) {
    jsonData.submitButtons[i][$(this).attr('name').toLowerCase()]=[e.color.toRGB().r,e.color.toRGB().g,e.color.toRGB().b];
    }
    }
    $(this).css('background-color',e.color.toHex());
    $(this).parent().find("[name='"+$(this).attr('name')+"_R']").val(e.color.toRGB().r);
    $(this).parent().find("[name='"+$(this).attr('name')+"_G']").val(e.color.toRGB().g);
    $(this).parent().find("[name='"+$(this).attr('name')+"_B']").val(e.color.toRGB().b);
    var button=getButtonJsonObjFromName(baseProto.attr('data-ref'));
    setButtonStyle(button, $(baseProto.find('button.proto')[0]));
    });
    proto.find('.colorpickerEl a').click(function(){
    $(this).parent().parent().find('.colorpicker-element').colorpicker('show');
    return false;
    });
    proto.find('.spanChangeLink a').click(function(){
    var txt='';
    txt=$(this).parent().parent().find('span').html();
    txt = prompt("Modificare il valore", txt);
    $(this).parent().parent().find('span').html(txt);
    if (txt==null) return false;
    var baseProto=$(this).parent().parent().parent();
    var name=baseProto.attr('data-ref');
    for (var i=0;i<jsonData.submitButtons.length;i++){
    if (jsonData.submitButtons[i].name==name) {
    jsonData.submitButtons[i][$(this).parent().parent().find('span').attr('data-ref')]=txt;
    }
    }
    var button=getButtonJsonObjFromName(baseProto.attr('data-ref'));
    setButtonStyle(button, $(baseProto.find('button.proto')[0]));
    return false;
    });

    (function(proto,button){
    proto.find('[name="fields"]').change(function(){
    for (var i=0;i<jsonData.submitButtons.length;i++){
    if (jsonData.submitButtons[i].name==button.name){
    jsonData.submitButtons[i].fields=$(this).val();
    }
    }
    });
    proto.find('[name="forms"]').change(function(){
    for (var i=0;i<jsonData.submitButtons.length;i++){
    if (jsonData.submitButtons[i].name==button.name){
    jsonData.submitButtons[i].forms=$(this).val();
    }
    }
    });
    })(proto,button);


    (function(proto,button){
    proto.find('.delete-button').click(function(){
    if (confirm('Sei sicuro?')){
    var buttons=jsonData.submitButtons;
    jsonData.submitButtons=[];
    for (var i=0;i<buttons.length;i++){
    if (buttons[i].name!=button.name){
    jsonData.submitButtons[jsonData.submitButtons.length]=buttons[i];
    }
    }
    $('div.buttonEl[data-ref="'+button.name+'"]').remove();
    }
    });
    })(proto,button);
    setButtonStyle(button, $(proto.find('button.proto')[0]));
    proto.find('[data-ref="name"]').html(button.name);
    proto.find('[data-ref="label"]').html(button.label);
    proto.find('[data-ref="faIcon"]').html(button.faIcon);
    $('#buttonsList').prepend(proto);
    }

    function getButtonJsonObjFromName(name){
    for (var i=0;i<jsonData.submitButtons.length;i++){
    if (jsonData.submitButtons[i].name==name) return jsonData.submitButtons[i];
    }
    }

    function setButtonStyle(btnSpec, btn){
    styleGen=[];
    styleOut=[];
    styleIn=[];
    btn.html("");
    if (btnSpec.faIcon!=undefined){
    var icon=$('<i>');
        icon.addClass('fa');
        icon.addClass('fa-'+btnSpec.faIcon);
        btn.append(icon);
        btn.append("&nbsp;");
        }
        if (btnSpec.label!=undefined){
        btn.append(btnSpec.label);
        }else {
        btn.append(btnSpec.name);
        }
        if (btnSpec.bkgrgb!=undefined){
        styleGen[styleGen.length]='border-color: rgba('+btnSpec.bkgrgb[0]+','+btnSpec.bkgrgb[1]+','+btnSpec.bkgrgb[2]+', 1) !important;';
        styleOut[styleOut.length]='background-color: rgba('+btnSpec.bkgrgb[0]+','+btnSpec.bkgrgb[1]+','+btnSpec.bkgrgb[2]+', 1) !important;';
        styleIn[styleIn.length]='background-color: rgba('+btnSpec.bkgrgb[0]+','+btnSpec.bkgrgb[1]+','+btnSpec.bkgrgb[2]+', 0.6) !important;';
        }
        if (btnSpec.txtrgb!=undefined){
        styleGen[styleGen.length]='color: rgba('+btnSpec.txtrgb[0]+','+btnSpec.txtrgb[1]+','+btnSpec.txtrgb[2]+', 1) !important;';
        }
        styleGenValue='';
        for (i=0;i<styleGen.length;i++){
        styleGenValue+=styleGen[i];
        }
        for (i=0;i<styleOut.length;i++){
        styleGenValue+=styleOut[i];
        }
        styleInValue='';
        for (i=0;i<styleGen.length;i++){
        styleInValue+=styleGen[i];
        }
        for (i=0;i<styleIn.length;i++){
        styleInValue+=styleIn[i];
        }
        btn.attr('style', styleGenValue);
        (function(btn,styleGenValue, styleInValue){
        btn.hover(function(){
        $(this).attr('style',styleInValue);
        }, function(){
        $(this).attr('style',styleGenValue);
        });
        })(btn,styleGenValue, styleInValue);
        }

        function componentToHex(c) {
        var hex = c.toString(16);
        return hex.length == 1 ? "0" + hex : hex;
        }

        function rgbToHex(r, g, b) {
        return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b);
        }



        $('#addRule').click(function(){
        idRule='';
        while (idRule!=null && idRule==''){
        idRule = prompt("Inserire il codice della regola", "");
        }
        if (idRule==null) return false;
        var idx=jsonData.rules.length;
        jsonData.rules[idx]={};
        jsonData.rules[idx].rule=idRule;
        jsonData.rules[idx].fields=[];
        jsonData.rules[idx].buttons=[];
        jsonData.rules[idx].criteria={};
        addRule(jsonData.rules[idx]);
        });


        var jsonData={}
        var elType={}
        function getFile(){
        $.getJSON('${baseUrl}/app/rest/admin/type/getByTypeId/${id}', function(data){
        elType=data;
        $.getJSON('${baseUrl}/app/documents/getJsonControls/${id}?ts='+new Date().getTime(), function(data){
        jsonData=data;
        dataLoaded();
        }).fail(function() {
        jsonData={};
        jsonData.submitButtons=[];
        jsonData.rules=[];
        dataLoaded();
        });

        });
        }

        function dataLoaded(){
        for (var i=0;i<elType.associatedTemplates.length;i++){
        var itm=elType.associatedTemplates[i].metadataTemplate;
        var fields=itm.fields;
        for (var f=0;f<fields.length;f++){
        addField(itm.name+"_"+fields[f].name);
        }
        }
        for (var i=0;i<jsonData.submitButtons.length;i++){
        addButton(jsonData.submitButtons[i]);
        }
        for (var i=0;i<jsonData.rules.length;i++){
        addRule(jsonData.rules[i]);
        }
        }

        getFile();

        $('#addButton').click(function(){
        var btnIdx=jsonData.submitButtons.length;
        var btnName="";
        while (btnName!=null && btnName==''){
        btnName = prompt("Inserire il nome del pulsante", "");
        }
        if (btnName==null) return false;
        var button={};
        button.name=btnName;
        jsonData.submitButtons[btnIdx]=button;
        addButton(button);
        proto=$('#rules');
        opt=$('<option>');
    opt.attr('value',btnName);
    opt.html(btnName);
    proto.find('[name="buttons"]').append(opt);
    proto.find('[name="buttons"]').select2();
    });



    $('.save-all').click(function(){
    var rules=jsonData.rules;
    jsonData.rules=[];
    for(var i=0;i<$('#rules').find('li').length;i++){
    thisRuleEl=$($('#rules').find('li')[i]);
    ruleId=thisRuleEl.attr('data-id');
    for (var f=0;f<rules.length;f++){
    if (rules[f].rule==ruleId){
    jsonData.rules[jsonData.rules.length]=rules[f];
    }
    }
    }
    bootbox.dialog({
    message: '<p class="text-center"><i class="fa fa-spinner fa-spin fa-fw"></i> Salvataggio in corso...</p>',
    closeButton: false
    });
    $.ajax({
    contentType: 'application/json',
    data: JSON.stringify(jsonData),
    dataType: 'json',
    success: function(data){
    setTimeout(function(){
    bootbox.hideAll();
    bootbox.dialog({
    message: '<p class="text-center"><i class="fa fa-check green"></i> Salvataggio effettuato con successo</p>',
    closeButton: false
    });
    setTimeout(function(){bootbox.hideAll();},1000);
    },500);
    },
    error: function(){
    bootbox.hideAll();
    bootbox.alert('Errore salvataggio controlli');
    },
    processData: false,
    type: 'POST',
    url: '${baseUrl}/app//rest/admin/saveControls/${typeIdName}'
    });
    });



</@script>

