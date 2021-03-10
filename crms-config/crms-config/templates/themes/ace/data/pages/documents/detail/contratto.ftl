<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
	"inline_scripts":[],
	"title" : "Dettaglio contratto",
 	"description" : "Dettaglio contratto" 
} />
<#assign elStudio=el.getParent().getParent() />
<#assign elCentro=el.getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />

<@script>
function protocollaElement(elementId, docFileName, studioId, fascicoloStudio,centroId) {
<#assign userCF = userDetails.username />
<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
</#if>
var userCF = '${userCF}';//MSRRNT64S69A944K
<#if userDetails.hasRole("CTC") || userDetails.hasRole("SGR") || userDetails.hasRole("UFFAMM") >
var profileProtocollo=true;
<#else>
var profileProtocollo=false;
</#if>

if(!profileProtocollo){
alert("Attenzione: la tua utenza non � abilitata all'invio di documenti al protocollo aziendale");
return false;
}
<#assign userPROTOCOLLO = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO')?? >
<#assign userPROTOCOLLO = userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO') />
</#if>
var userPROTOCOLLO = '${userPROTOCOLLO}';

<#assign userAZI = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ')?? >
<#assign userAZI = userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ') />
</#if>
var userAZI = '${userAZI}';

<#assign userREGISTRO = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO')?? >
<#assign userREGISTRO = userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO') />
</#if>
var userREGISTRO = '${userREGISTRO}';

if(userREGISTRO=='' || userPROTOCOLLO=='' || userAZI=='' ){
	alert('Attenzione: la procedura di integrazione con protocollo aziendale non � attiva per questo centro');
	return false;
}

var anno = new Date();
//alert(elementId);
//alert(studioId);
//alert(fascicoloStudio);
//alert(userCF);
//alert(userPROTOCOLLO);
//alert(userAZI);
//alert(userREGISTRO);
//alert(anno.getFullYear());
//return false;

if (!fascicoloStudio){
$.ajax({
type : "POST",
cache: false,
data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+anno.getFullYear()+"&USERCF="+userCF+"&STUDIO_CODE="+studioId,
url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/createFolder.php',
async:false,
}).done(function(result) {
console.log(result);
alert(result);
if(result.includes('"code" : "500"')){
alert("ERRORE INSERIMENTO FASCICOLO: "+result);
}else{
//Aggiorna oggetto studio
$.ajax({
type: "POST",
cache: false,
url: baseUrl+"/app/rest/documents/update/"+centroId,
data: "IdCentro_ProtocolloFascicolo="+result ,
async: false,
success: function(msg){
//window.location.reload();
fascicoloStudio = result;
}
});
//window.location.reload();
}
});
}
//Inserisci documento effettivo
if (fascicoloStudio){
var attach="";
$.ajax({
type : "GET",
cache: false,
url : baseUrl+'/app/documents/getAttach/'+elementId
}).done(function(content) {
//alert(content);
if (content){
var attach=Base64.encode(content);
$.ajax({
type : "POST",
cache: false,
data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+anno.getFullYear()+"&USERCF="+userCF+"&STUDIO_CODE="+studioId+"&STUDIO_FASCICOLO="+fascicoloStudio+"&DOCUMENTO_CODE="+elementId+"&DOCUMENTO_FILENAME="+docFileName+"&DOCUMENTO_BODY="+attach,
url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/sendFileContentPEBody.php',

}).done(function(result) {
console.log(result);
alert(result);
if(result.includes('"code" : "500"')){
alert("ERRORE INSERIMENTO DOCUMENTO: "+result);
}else{
//Aggiorna oggetto studio
$.ajax({
type: "POST",
cache: false,
url: baseUrl+"/app/rest/documents/update/"+elementId,
data: "tipologiaContratto_numeroProtocollo="+result+"&tipologiaContratto_ProtocolloRegistro="+userREGISTRO+"&tipologiaContratto_ProtocolloAzienda="+userAZI ,
success: function(msg){
window.location.reload();
}
});
//window.location.reload();
}
});
}else{
alert("Contenuto file non disponibile.");
}
});
}else{
alert("Fascicolo per lo studio non presente.");
}
return false;
}

function vediProtocollo(codiceProtocollo) {
<#assign userCF = userDetails.username />
<#if userDetails.getAnaDataValue('CODICE_FISCALE')?? >
<#assign userCF = userDetails.getAnaDataValue('CODICE_FISCALE') />
</#if>
var userCF = '${userCF}';//MSRRNT64S69A944K

<#assign userPROTOCOLLO = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO')?? >
<#assign userPROTOCOLLO = userDetails.getSiteDataValue('INTEGRAZIONE_PROTOCOLLO') />
</#if>
var userPROTOCOLLO = '${userPROTOCOLLO}';

<#assign userAZI = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ')?? >
<#assign userAZI = userDetails.getSiteDataValue('INTEGRAZIONE_COD_AZ') />
</#if>
var userAZI = '${userAZI}';

<#assign userREGISTRO = "" />
<#if userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO')?? >
<#assign userREGISTRO = userDetails.getSiteDataValue('INTEGRAZIONE_COD_REGISTRO') />
</#if>
var userREGISTRO = '${userREGISTRO}';

if(userREGISTRO=='' || userPROTOCOLLO=='' || userAZI=='' ){
alert('Attenzione: la procedura di integrazione con protocollo aziendale non � attiva per questo centro');
return false;
}
alert(codiceProtocollo);
if (codiceProtocollo){
var codiceSplit = codiceProtocollo.split('/');
$.ajax({
type : "POST",
cache: false,
data : "AZIENDA="+userAZI+"&REGISTRO="+userREGISTRO+"&ANNO="+codiceSplit[1]+"&NUMERO="+codiceSplit[0]+"&USERCF="+userCF,
url : '/xCDMProtocolloLib/'+userPROTOCOLLO+'/retrieveFileList.php',
}).done(function(result) {
alert(result);
});
}
}
</@script>