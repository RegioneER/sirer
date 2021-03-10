<#include "../helpers/macroGemelli.ftl"/>
<#include "../helpers/MetadataTemplate.ftl"/>
<style>

    .xCDM-modalForm .col-sm-3,
    .xCDM-modalForm .col-sm-9{
        float:left;
    }

    .xCDM-modalForm .form-group > div{
        text-align:left;
    }

    .xCDM-modalForm .radio, .xCDM-modalForm .checkbox {
        padding-left: 0px;
    }

    .xCDM-modalForm input[type='text'], .xCDM-modalForm textarea{
        width: 90%;
        max-width: 90%;
    }

    .bootbox-body .xCDM-modalForm {
        font-size: 14px;
    }

    .select2-drop{
        z-index: 100000 !important;
    }

    .ui-autocomplete.ui-menu {
        z-index: 1000000 !important;
    }

    .ui-jqgrid tr.jqgrow td {
        white-space:normal;
    }
    .ui-jqgrid .ui-jqgrid-htable th div {
        white-space:normal;
        height:auto;
        margin-bottom:3px;
    }
    .ui-icon{
        position:relative !important;
    }

    .home-table .ui-jqgrid{
        margin:10px;

    }

    tr.jqgrow{
        cursor:pointer;
    }

    .home-table {
        float:left;
    }
    .infobox {
        cursor:pointer;
    }

    td.subgrid-data{
        padding:10px !important;
    }

</style>
<@script>

var messages=null;
$.getJSON(baseUrl+'/app/rest/documents/messages', function(data){
messages=data.resultMap;
});
</@script>
<div class="home-container">
    <h3>Gestione Magazzino <a href="#" onclick="farmacoModalEngine.formByElement(myDepotFarmaco);return false;">${el.getFieldDataElement("depotFarmaco_linkFarmaco")[0].getTitleString()}</a></h3>


    <button id="chiudiGestioneButton" style="float:right;margin:0 10px;"  class="submitButton round-button blue btn btn-info" onclick="chiudiGestioneFarmaco('${el.id}');return false;"  ><i class="fa fa-close bigger-160"  ></i>&nbsp;<b>Chiudi Gestione</b></button>


    <button style="float:right;margin:0 10px;" class="submitButton round-button blue btn btn-info" onclick="location.href='${baseUrl}/app/documents/custom/DepotFarmacoDoc/${el.id}';"  ><i class="fa fa-folder-open bigger-160"  ></i>&nbsp;<b>Area Documentale Magazzino</b></button>


    <#if model['getCreatableElementTypes']??>
    <#list model['getCreatableElementTypes'] as docType>
    <#if docType.typeId="DepotFarmacoScarico" >
    <button id="ScaricoButton" style="float:right;margin:0 10px;" class="submitButton round-button blue btn btn-info" onclick="farmacoScaricoModalEngine.formByParentId('${el.id}');return false;"  ><i class="icon-download bigger-160"  ></i><b>Aggiungi nuovo scarico</b></button>
</#if>
<#if docType.typeId="DepotFarmacoCarico" >
<button id="CaricoButton" style="float:right;margin:0 10px;"  class="submitButton round-button blue btn btn-info" onclick="farmacoCaricoModalEngine.formByParentId('${el.id}');return false;"  ><i class="icon-upload bigger-160"  ></i><b>Aggiungi nuovo carico</b></button>
</#if>
</#list>
</#if>


<div class="row" style="clear: both;padding:10px 0px;">
    <div class="col-xs-12">
            <span class="DepotFarmacoCarico-table" >
		        <table id="DepotFarmacoCarico-grid-table" class="grid-table" ></table>
                <div id="DepotFarmacoCarico-grid-pager"></div>
	        </span>
    </div>
</div>
<div class="row" style="clear: both;padding:10px 0px;">
    <div class="col-xs-12">
                <span class="DepotFarmacoScarico-table" >
                    <table id="DepotFarmacoScarico-grid-table" class="grid-table" ></table>
                    <div id="DepotFarmacoScarico-grid-pager"></div>
                </span>
    </div>
</div>
</div>






