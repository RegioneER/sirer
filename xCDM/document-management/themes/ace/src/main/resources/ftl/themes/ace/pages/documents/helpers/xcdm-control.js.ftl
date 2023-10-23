function getValue(obj, idField){
field=$('#'+obj.formId+' [name="'+idField+'"]');
if (field.attr('istokeninput')=='true'){
value=field.tokenInput("get");
if (value.length>0)
return value[0].id;
else return "";
}
if (field.attr('type')=='checkbox'){
ret=[];
if (field.length>1){
for (i=0;i<field.length;i++){
if ($(field[i]).is(':checked')){
ret[ret.length]=$(field[i]).val();
}
}
}
return ret;
}
if (field.attr('type')=='radio'){
ret=null;
for (i=0;i<field.length;i++){
if ($(field[i]).is(':checked')){
ret=$(field[i]).val();
}
}
return ret;
}
return field.val();
}

function getValueDecode(obj, fieldId){
value=getValue(obj, fieldId);
if (value == undefined) return null;
if (value == '') return '';
if (value instanceof Array){
ret=[];
for (i=0;i<value.length;i++){
split=value[i].split('###');
if (split.length>1) ret[i]=split[1];
else ret[i]=split[0];
}
return ret;
}else {
split=value.split('###');
if (split.length>1) return split[1];
else return split[0];
}
}


function getValueCode(obj, fieldId){
value=getValue(obj, fieldId);
if (value == undefined) return null;
if (value == '') return '';
if (value instanceof Array){
ret=[];
for (i=0;i<value.length;i++){
split=value[i].split('###');
ret[i]=split[0];
}
return ret;
}else {
split=value.split('###');
return split[0];
}
}

function ltCheck(obj, arg1, arg2){
val=getValueCode(obj, arg1);
passed=false;
if (val instanceof Array){
for(var idx=0;idx<val.length;idx++){
if (val[idx] < arg2) passed=true;
}
}else {
passed=(val < arg2);
}
return passed;
}

function leCheck(obj, arg1, arg2){
val=getValueCode(obj, arg1);
passed=false;
if (val instanceof Array){
for(var idx=0;idx<val.length;idx++){
if (val[idx] <= arg2) passed=true;
}
}else {
passed=(val <= arg2);
}
return passed;
}

function gtCheck(obj, arg1, arg2){
val=getValueCode(obj, arg1);
passed=false;
if (val instanceof Array){
for(var idx=0;idx<val.length;idx++){
if (val[idx] > arg2) passed=true;
}
}else {
passed=(val > arg2);
}
return passed;
}

function geCheck(obj, arg1, arg2){
val=getValueCode(obj, arg1);
passed=false;
if (val instanceof Array){
for(var idx=0;idx<val.length;idx++){
if (val[idx] >= arg2) passed=true;
}
}else {
passed=(val >= arg2);
}
return passed;
}

function eqCheck(obj, arg1, arg2){
val=getValueCode(obj, arg1);
passed=false;
if (val instanceof Array){
for(var idx=0;idx<val.length;idx++){
if (val[idx] == arg2) passed=true;
}
}else {
passed=(val == arg2);
}
return passed;
}

function neCheck(obj, arg1, arg2){
val=getValueCode(obj, arg1);
passed=false;
if (val instanceof Array){
for(var idx=0;idx<val.length;idx++){
if (val[idx] != arg2) passed=true;
}
}else {
passed=(val != arg2);
}
return passed;
}


function clearField(obj,fieldId){
$('#'+fieldId).val(null);
}

function showField(obj, fieldId){
split=fieldId.split("_");
$('#'+split[0]+"-"+fieldId).show();
$('label[for="'+fieldId+'"]').show();
$('[data-field-id="'+fieldId+'"]').show();
$('#'+fieldId).show();
}

function hideField(obj, fieldId){
split=fieldId.split("_");
$('#'+split[0]+"-"+fieldId).hide();
$('label[for="'+fieldId+'"]').hide();
$('[data-field-id="'+fieldId+'"]').hide();
$('#'+fieldId).hide();
}





function showMessage(obj, msg){
bootbox.alert(msg);
}

function getLabelOfField(obj, fieldId){
console.log(fieldId);
dottedFieldId=fieldId.replace("_", ".");
return "\""+messages[dottedFieldId]+"\"";
}

function focusOn(obj, fieldId){
$('#'+fieldId).focus();
}

function postFields(obj, btn){
actionUrl=$('#'+obj.formId).attr("action");
formElement=$('#'+obj.formId)[0];
var formData=new FormData(formElement);
var toBeDeleted=[];
for (var value of formData) {
var found=false;
for (var i=0;i<check.buttonsFields[btn].length;i++){
if (value[0]==check.buttonsFields[btn][i]) {
console.log("trovata chiave "+value[0]);
found=true;
}
}
if (!found) {
toBeDeleted[toBeDeleted.length]=value[0];
}
}
for (var i=0;i<toBeDeleted.length;i++){
formData.delete(toBeDeleted[i]);
}
bootbox.dialog({
message:'<i class="icon-spinner icon-spin"></i> '+messages['js.Saving'],
backdrop: true,
closeButton: false
});
console.log(formData);
$.ajax({
type: "POST",
url: actionUrl,
contentType:false,
processData:false,
async:false,
cache:false,
data: formData,
success: function(obj){
if (obj.result=="OK") {
bootbox.hideAll();
bootbox.alert(messages['js.SaveSuccess']+' <i class="icon-ok green" ></i>');
if (obj.redirect){
window.location.href=obj.redirect;
}
}else {
bootbox.alert(messages['js.SaveError']+' <i class="icon-warning-sign red"></i>');
}
},
error: function(){
bootbox.alert(messages['js.SaveError']+' <i class="icon-warning-sign red"></i>');
}
});
}

var messages=new Object();
function loadMessages(){
$.getJSON(baseUrl+"/app/rest/documents/messages", function(data){
messages=data.resultMap;
});
}

function buildButtons(check, formName){
$('#'+check.formId+" button").remove();
for (var btnName in check.buttons) {

var found=false;
for (var c=0;c<check.buttons[btnName].forms.length;c++){
if (check.buttons[btnName].forms[c]==formName) found=true;
}
if (!found) continue;
console.log(btnName);
btn=$('<button>');
    btn.addClass('btn');
    btn.attr('id','check-btn-'+btnName);
    if (check.buttons[btnName].faIcon!=undefined) {
    faIcon=$('<i>');
        faIcon.addClass('fa');
        faIcon.addClass('fa-'+check.buttons[btnName].faIcon);
        btn.append(faIcon);
        btn.append('&nbsp;');
        }
        if (check.buttons[btnName].label!=undefined) {
        btn.append(check.buttons[btnName].label);
        }else {
        btn.append(btnName);
        }
        styleGen=[];
        styleOut=[];
        styleIn=[];
        if (check.buttons[btnName].bckRGB!=undefined){
        styleGen[styleGen.length]='border-color: rgba('+check.buttons[btnName].bckRGB[0]+','+check.buttons[btnName].bckRGB[1]+','+check.buttons[btnName].bckRGB[2]+', 1) !important;';
        styleOut[styleOut.length]='background-color: rgba('+check.buttons[btnName].bckRGB[0]+','+check.buttons[btnName].bckRGB[1]+','+check.buttons[btnName].bckRGB[2]+', 1) !important;';
        styleIn[styleIn.length]='background-color: rgba('+check.buttons[btnName].bckRGB[0]+','+check.buttons[btnName].bckRGB[1]+','+check.buttons[btnName].bckRGB[2]+', 0.6) !important;';
        }
        if (check.buttons[btnName].txtRGB!=undefined){
        styleGen[styleGen.length]='color: rgba('+check.buttons[btnName].txtRGB[0]+','+check.buttons[btnName].txtRGB[1]+','+check.buttons[btnName].txtRGB[2]+', 1) !important;';
        }
        (function(btnName){
        btn.click(function(){check.buttonClickActions(btnName)});
        })(btnName);
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
        (function(styleGenValue, styleInValue){
        btn.hover(function(){
        $(this).attr('style',styleInValue);
        }, function(){
        $(this).attr('style',styleGenValue);
        });
        })(styleGenValue, styleInValue);
        $('#'+check.formId+' .button-footer-area').append(btn);
        $('#'+check.formId+' .button-footer-area').append("&nbsp;");
        }
        }


        function loadControls(baseUrl, objName, formId, formName){
        jsControlsScript=baseUrl+"/app/documents/jsControls/"+objName+"/"+formId;
        $.ajax({
        url: jsControlsScript,
        success: function(data){
        jQuery.globalEval(data);
        check=jsControls['ClinicalCase'];
        buildButtons(check, formName);
        check.onLoad();
        for (var field in check.registerEventsOnField){
        $('#'+check.formId+' [name="'+field+'"]').change(function(){
        check.registerEventsOnField[field]();
        });

        }
        }
        });
        }