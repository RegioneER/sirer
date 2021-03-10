<#assign type=model['docDefinition']/>
<#global page={
    "content": path.pages+"/"+mainContent,
    "styles" : ["jquery-ui-full", "datepicker","pages/form.css","jqgrid"],
    "scripts" : ["jquery-ui-full","datepicker","bootbox", "common/elementEdit.js","token-input","jqgrid","pages/home.js"],
    "inline_scripts":[],
    "title" : "Dettaglio centro",
    "description" : "Dettaglio centro" 
} />
<#assign elStudio=el.getParent() />

<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />

<@script>
var loadedElement=${loadedJson};
loadedElement.id=${el.id};
//loadedElement.type=${el.type.getDummyJson()}.type;
var empties=new Array();
empties[${el.type.id}]=loadedElement;
var dialog=bootbox.dialog({
    message: '<p class="text-center">Caricamento in corso...<br/><i class="icon-spinner icon-spin"></i></p>',
    closeButton: false
});
    $('#form-DatiTeamDiStudio').ready(function() {
        $('#form-DatiTeamDiStudio').addClass("form-horizontal");
        $('div[id^="DatiTeamDiStudio-"]').addClass("col-sm-9")
        if($("input[name=DatiTeamDiStudio_TipoPersonale]").val().split('###')[0]=="1"){
          $('#informations-DatiTeamDiStudio_AltroPersonale').hide();
          $('#informations-DatiTeamDiStudio_NomeCognome').show();
          $('#informations-DatiTeamDiStudio_attivitaDip1').show();
          $('#informations-DatiTeamDiStudio_attivitaDip2').show();
          $('#informations-DatiTeamDiStudio_attivitaNonDip1').hide();
          $('#informations-DatiTeamDiStudio_rapLavNonDip').hide();
          $('#informations-DatiTeamDiStudio_EnteNonDip').hide();
        }
        if($("input[name=DatiTeamDiStudio_TipoPersonale]:checked").val().split('###')[0]=='2'){
          $('#informations-DatiTeamDiStudio_AltroPersonale').show();
          $('#informations-DatiTeamDiStudio_NomeCognome').hide();
          $('#informations-DatiTeamDiStudio_attivitaDip1').hide();
          $('#informations-DatiTeamDiStudio_attivitaDip2').hide();
          $('#informations-DatiTeamDiStudio_attivitaNonDip1').show();
          $('#informations-DatiTeamDiStudio_rapLavNonDip').show();
          $('#informations-DatiTeamDiStudio_EnteNonDip').show();
        }
        dialog.modal('hide');
    });
                
    $("input[name=DatiTeamDiStudio_TipoPersonale]").change(function(){
        if($("input[name=DatiTeamDiStudio_TipoPersonale]:checked").val().split('###')[0]=="1"){
          $('#informations-DatiTeamDiStudio_AltroPersonale').hide();
          $('#informations-DatiTeamDiStudio_NomeCognome').show();
          $('#informations-DatiTeamDiStudio_attivitaDip1').show();
          $('#informations-DatiTeamDiStudio_attivitaDip2').show();
          $('#informations-DatiTeamDiStudio_attivitaNonDip1').hide();
          $('#informations-DatiTeamDiStudio_rapLavNonDip').hide();
          $('#informations-DatiTeamDiStudio_EnteNonDip').hide();
        }
        if($("input[name=DatiTeamDiStudio_TipoPersonale]:checked").val().split('###')[0]=='2'){
          $('#informations-DatiTeamDiStudio_AltroPersonale').show();
          $('#informations-DatiTeamDiStudio_NomeCognome').hide();
          $('#informations-DatiTeamDiStudio_attivitaDip1').hide();
          $('#informations-DatiTeamDiStudio_attivitaDip2').hide();
          $('#informations-DatiTeamDiStudio_attivitaNonDip1').show();
          $('#informations-DatiTeamDiStudio_rapLavNonDip').show();
          $('#informations-DatiTeamDiStudio_EnteNonDip').show();
        }
    });
</@script>