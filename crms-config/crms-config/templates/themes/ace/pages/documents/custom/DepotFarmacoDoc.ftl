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
    <h3>Gestione Documentale Magazzino <a href="${baseUrl}/app/documents/detail/${el.id}" target="_blank">${el.getFieldDataElement("depotFarmaco_linkFarmaco")[0].getTitleString()}</a></h3>
    <#if model['getCreatableElementTypes']??>
    <#list model['getCreatableElementTypes'] as docType>
    <#if docType.typeId="DepotFarmacoDoc" >
    <button style="float:right;margin-top: 17px;" class="btn btn-sm btn-info" id='addDocument'><i class="fa fa-plus"></i> Aggiungi nuovo Documento</button>
    <@script>
    $('button#addDocument').click(function(){addDocument();});
</@script>
</#if>
</#list>
</#if>


<div class="row" style="clear: both;padding:10px 0px;">
    <div class="col-xs-12">
            <span class="DepotFarmacoDoc-table" >
		        <table id="DepotFarmacoDoc-grid-table" class="grid-table" ></table>
                <div id="DepotFarmacoDoc-grid-pager"></div>
	        </span>
    </div>
</div>
</div>






