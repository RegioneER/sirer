<@script>

    var action=null;

        action=new ajaXmrTab({
            elementName: "action",
            baseUrl: "${baseUrl}",
            listRow:actionListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/action/save",
            getAllUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/action/getWfAll",
            deleteUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/action/delete",
            getSingleElementUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/action/get",
            dialogWidth: "500px",
            postClearForm: actionPostClearForm,
            listType: "tr",
            postSave: function(){
                flow.get(selectedFlowId, renderFlowData);
            }
        });
        $('#action-dialog #actionType').change(function(){
            if ($(this).val()=='POPULATE_METADATA') {
                $('#templateName').val("");
                $('#addTemplate-data').hide();
                $('#populateAction-data').show();
            }
            if ($(this).val()=='ADD_TEMPLATE'){
                $('#origField').val("");
                $('#destField').val("");
                $('#addTemplate-data').show();
                $('#populateAction-data').hide();
            }
        });
        //action.refreshList();


    function actionPostClearForm(){
        $('#action-form').find('#idFlow').val(selectedFlowId);
        $('#addTemplate-data').hide();
        $('#populateAction-data').hide();
    }

    function actionListRow(jsonRow, flowName){
        console.log(jsonRow);
        var ret="<td>"+jsonRow.action+"</td><td>"+flowName+"</td><td style=\"text-align:left !important\">";
        for (c=0;c<jsonRow.params.length;c++){
            if (c>0) ret+="<br/>";
            ret+=""+jsonRow.params[c].name+" -> "+jsonRow.params[c].value+"";
        }
        ret+="</td>"
        return ret;
    }
</@script>

<div id="action-dialog" title="Aggiungi step">
    <fieldset>
        <form id="action-form" method="POST" enctype="multipart/form-data">
        <@hidden "id" "id"/>
            <div class="field-component">
            <@hidden "idFlow" "idFlow"/>
            </div>
            <div class="field-component">
            <@selectHash "actionType" "actionType" "Tipo di azione" {"POPULATE_METADATA":"Popola campo","ADD_TEMPLATE":"Abilita template"}/>
            </div>
            <div id="populateAction-data" style="display: none">
                <div class="field-component">
                    <@selectHash "origField" "origField" "Campo origine"/>
                </div>
                <div class="field-component">
                <@singleAutoCompleteFB "destField" "destField" "Campo destinazione" "${baseUrl}/app/rest/admin/template/searchTemplateField" "extendedName"/>
                </div>
            </div>
            <div id="addTemplate-data" style="display: none">
                <div class="field-component">
                <@singleAutoCompleteFB "templateName" "templateName" "Template da aggiungere" "${baseUrl}/app/rest/admin/template/searchTemplate" "name"/>
                </div>

            </div>
            <input class="round-button blue" type="button" value="Salva" id="action-form-submit"/>
        </form>

    </fieldset>
</div>

