
<#assign wf=model['wf']/>
<script>

    var step;
    var flow;
    var field;

    $(document).ready(function(){
        graphUpdate();

        step=new ajaXmrTab({
            elementName: "step",
            baseUrl: "${baseUrl}",
            listRow:stepListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/step/save",
            getAllUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/step/getAll",
            deleteUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/step/delete",
            getSingleElementUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/step/get",
            dialogWidth: "500px",
            postSave: stepUpdate,
            listType: "br",
            cleaner: stepCleaner

        });
        //step.refreshList();

        flow=new ajaXmrTab({
            elementName: "flow",
            baseUrl: "${baseUrl}",
            listRow:flowListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/flow/save",
            getAllUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/flow/getAll",
            deleteUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/flow/delete",
            getSingleElementUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/flow/get",
            dialogWidth: "500px",
            postRefresh: flowUpdate,
            listType: "br"
        });
        //flow.refreshList();

        field=new ajaXmrTab({
            elementName: "field",
            baseUrl: "${baseUrl}",
            listRow:fieldListRow,
            saveOrUpdateUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/field/save",
            getAllUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/field/getAll",
            deleteUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/field/delete",
            getSingleElementUrl: "${baseUrl}/app/rest/admin/workflow/${wf.id}/field/get",
            dialogWidth: "500px",
            postClearForm: fieldPostClearForm,
            postSave: function(){
                flow.get(selectedFlowId, renderFlowData);
            },
            listType: "br"
        });


    });

    function stepCleaner(){
        $('#flow-form').find('#source').html("<option></option>");
        $('#flow-form').find('#target').html("<option></option>");
    }

    function flowUpdate(){
        graphUpdate();
        field.refreshList();
    }

    function stepUpdate(){
        graphUpdate();
        flow.refreshList();
    }

    function fieldListRow(jsonRow){
        return jsonRow.name+'(Ramo: '+jsonRow.flowName+')';
    }

    function flowListRow(jsonRow){
        $('#field-form').find('#idFlow').append("<option value='"+jsonRow.id+"'>"+jsonRow.name+"</option>");
        $('#action-form').find('#idFlow').append("<option value='"+jsonRow.id+"'>"+jsonRow.name+"</option>");
        return '<b>Ramo  '+jsonRow.name+':</b> '+jsonRow.sourceName+' -> '+jsonRow.targetName;
    }

    function stepListRow(jsonRow){
        $('#flow-form').find('#source').append("<option value='"+jsonRow.id+"'>"+jsonRow.name+"</option>");
        $('#flow-form').find('#target').append("<option value='"+jsonRow.id+"'>"+jsonRow.name+"</option>");
        var ret='<b>Stato:</b> '+jsonRow.name;
        if (jsonRow.startPoint) ret+="(Start)";
        if (jsonRow.endPoint) ret+="(End)";
        if (!jsonRow.startPoint && !jsonRow.endPoint) ret+=' - <a href="#" onclick="setStartStep('+jsonRow.id+');return false;">set as startDate</a> - <a href="#" onclick="setEndStep('+jsonRow.id+');return false;">set as endDate</a>';
        return ret;
    }

    function graphUpdate(){
        d = new Date();
        $('#graph').attr("src","${baseUrl}/app/admin/workflow/${wf.id}/Graph?"+d.getTime());
        $.ajax({
            url: "${baseUrl}/app/admin/workflow/${wf.id}/GraphMap?"+d.getTime(),
            success: function(resp){
                $('#graphMap').html(resp);
                $('#G').find("area").unbind("click");
                $('#G').find("area").click(function(event){
                    console.log(event);
                    event.returnValue = false;
                    event.preventDefault();
                    link=$(this).attr("href");
                    console.log("sono qui");

                    if (link.indexOf("step_")==0) {
                        step.get(link.replace("step_",""), renderStepData);

                    }
                    if (link.indexOf("flow_")==0) {
                        flow.get(link.replace("flow_",""), renderFlowData);
                    }

                });
            }
        });




    }

    function setStartStep(id){
        actionUrl="${baseUrl}/app/rest/admin/workflow/${wf.id}/step/setStart/"+id;
        $.ajax({
            type: "GET",
            url: actionUrl,
            cache:false,
            success: function(obj){
                if (obj.result=="OK") {
                    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                    step.get(id, renderStepData);
                    graphUpdate();
                    if (obj.redirect){
                        window.location.href=obj.redirect;
                    }
                }else {
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            },
            error: function(){
                loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        });
    }

    function unSetStartStep(id){
        actionUrl="${baseUrl}/app/rest/admin/workflow/${wf.id}/step/unSetStart/"+id;
        $.ajax({
            type: "GET",
            url: actionUrl,
            cache:false,
            success: function(obj){
                if (obj.result=="OK") {
                    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                    step.get(id, renderStepData);
                    graphUpdate();
                    if (obj.redirect){
                        window.location.href=obj.redirect;
                    }
                }else {
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            },
            error: function(){
                loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        });
    }

    function setEndStep(id){
        actionUrl="${baseUrl}/app/rest/admin/workflow/${wf.id}/step/setEnd/"+id;
        $.ajax({
            type: "GET",
            url: actionUrl,
            cache:false,
            success: function(obj){
                if (obj.result=="OK") {
                    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                    step.get(id, renderStepData);
                    graphUpdate();
                    if (obj.redirect){
                        window.location.href=obj.redirect;
                    }
                }else {
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            },
            error: function(){
                loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        });

    }

    function unSetEndStep(id){
        actionUrl="${baseUrl}/app/rest/admin/workflow/${wf.id}/step/unSetEnd/"+id;
        $.ajax({
            type: "GET",
            url: actionUrl,
            cache:false,
            success: function(obj){
                if (obj.result=="OK") {
                    loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                    step.get(id, renderStepData);
                    graphUpdate();
                    if (obj.redirect){
                        window.location.href=obj.redirect;
                    }
                }else {
                    loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
                }
            },
            error: function(){
                loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        });
    }

    function renderStepData(data){
        console.log(data);

        $('#detail-step-block').show();
        $('#detail-flow-block').hide();
        $('#detail-step-block legend').html("Specifiche Step: "+data.name);
        step.appendEditIcon(data.id, $('#detail-step-block legend'));
        step.appendDeleteIcon(data.id, $('#detail-step-block legend'));
        $('#detail-step-block #startPoint').each(function(){
            this.checked=data.startPoint;
        });
        $('#detail-step-block #startPoint').unbind("change");
        $('#detail-step-block #startPoint').change(function(){
            if (this.checked) setStartStep(data.id);
            else unSetStartStep(data.id);
        });
        $('#detail-step-block #endPoint').each(function(){
            this.checked=data.endPoint;
        });
        $('#detail-step-block #endPoint').unbind("change");
        $('#detail-step-block #endPoint').change(function(){
            if (this.checked) setEndStep(data.id);
            else unSetEndStep(data.id);
        });

    }

    var selectedFlowId;

    function renderFlowData(data){
        $('#detail-step-block').hide();
        $('#detail-flow-block').show();
        $('#detail-flow-block #flow-field').html("");
        $('#detail-flow-block legend').html("Specifiche ramo: "+data.name);
        flow.appendEditIcon(data.id, $('#detail-flow-block legend'));
        flow.appendDeleteIcon(data.id, $('#detail-flow-block legend'));
        console.log(data.id);
        selectedFlowId=data.id;
        $('#action-dialog #origField').html("<option></option>");

        for (i=0;i<data.fields.length;i++){
            $('#detail-flow-block #flow-field').append("<li id=\"flow-field-"+data.fields[i].id+"\">"+data.fields[i].name+" ("+data.fields[i].type+")</li>");
            $('#action-dialog #origField').append("<option value=\"flow."+data.fields[i].name+"\">"+data.fields[i].name+"</option>");
            //field.appendEditIcon(data.fields[i].id, $("#flow-field-"+data.fields[i].id));
            field.appendDeleteIcon(data.fields[i].id, $("#flow-field-"+data.fields[i].id));
        }
        var tb="<table class=\"pSchema\"><tr><th>Tipo azione</th><th>Ramo</th><th>Parametri</th><th>elimina</th></tr><tbody id=\"flow-actions-rows\"></tbody></table>";
        $('#detail-flow-block #flow-action').html(tb);
        for (i=0;i<data.actions.length;i++){
            console.log(data.actions[i]);
            var row="<tr>"+actionListRow(data.actions[i], data.name);
            row+="<td id=\"action-last-cell-"+data.actions[i].id+"\"></td>";
            row+="</tr>";
            $('#detail-flow-block #flow-actions-rows').append(row);
            //action.appendEditIcon(data.actions[i].id, $('#detail-flow-block #action-last-cell-'+data.actions[i].id));
            action.appendDeleteIcon(data.actions[i].id, $('#detail-flow-block #action-last-cell-'+data.actions[i].id));
        }

    }

    function fieldPostClearForm(){
        $('#field-form').find('#idFlow').val(selectedFlowId);

    }

</script>


<div class="admin-home-main">
    <a class="link-back" href="${baseUrl}/app/admin">Home Page - Console amministrazione</a>
    <br/>
    <fieldset>
        <legend>Workflow ${wf.name}</legend>
         <fieldset id="detail-flow-block" style="display: none;float:right">
                 <legend></legend>
                 <input class="submitButton round-button blue" type="button" value="Aggiungi Campo" id="add-field" name="add-field"/>
                 <input class="submitButton round-button blue" type="button" value="Aggiungi Azione" id="add-action" name="add-action"/>
                 <hr/>
                 <b>Campi</b><br/>
                 <div id="flow-field"></div>
                 <hr/>
                 <b>Azioni</b><br/>
                 <div id="flow-action"></div>
         </fieldset>
         <fieldset id="detail-step-block" style="display: none;float:right">
             <legend></legend>
                 <div class="field-component view-mode">
                     <label id="nome-label" for="nome">Step di partenza:</label>
                     <input type="checkbox" id="startPoint" value=""/>
                 </div>
                 <div class="field-component view-mode">
                     <label id="nome-label" for="nome">Step di fine:</label>
                     <input type="checkbox" id="endPoint" value=""/>
                 </div>
             </fieldset>
        <input class="submitButton round-button blue" type="button" value="Aggiungi Stato" id="add-step" name="add-step"/>
        <input class="submitButton round-button blue" type="button" value="Aggiungi Ramo" id="add-flow" name="add-flow"/>
        <br/>
        <img id="graph" usemap="#G" />
        <div id="graphMap"></div>
         <div style="display: inline-block;width:100%">
             
            

        <!--
        <fieldset class="floatbox">
            <legend>Stati</legend>
            <div id="step-list-availables"></div>
        </fieldset>
        <fieldset class="floatbox">
            <legend>Rami</legend>
            <div id="flow-list-availables"></div>
        </fieldset>
        <fieldset class="floatbox">
            <legend>Campi</legend>
            <input class="submitButton round-button blue" type="button" value="Aggiungi Campo" id="add-field" name="add-field"/>
            <div id="field-list-availables"></div>
        </fieldset>
        -->
    <div id="step-dialog" title="Aggiungi step">
        <fieldset>
            <form id="step-form" method="POST" enctype="multipart/form-data">
            <@hidden "id" "id"/>

                <div class="field-component">
                <@textbox "name" "name" "Nome step" "" 40/>
                    </div>
                <input class="round-button blue" type="button" value="Salva" id="step-form-submit"/>
            </form>

        </fieldset>
    </div>
    <#assign availablesStep={}/>
    <#if wf.steps??>
        <#list wf.steps as step>
            <#assign availablesStep= availablesStep + {step.id,step.name}/>
        </#list>

    </#if>
    <div id="flow-dialog" title="Aggiungi ramo">
        <fieldset>
            <form id="flow-form" method="POST" enctype="multipart/form-data">
                <@hidden "id" "id"/>
                <div class="field-component">
                    <@textbox "name" "name" "Nome ramo" "" 40/>
                </div>
                <div class="field-component">
                    <@selectHash "source" "source" "Origine" availablesStep/>
                </div>
                <div class="field-component">
                    <@selectHash "target" "target" "Destinazione" availablesStep/>
                </div>
                    <div class="field-component">
                    <@textbox "setStatus" "setStatus" "Valore stato" "" 40/>
                    </div>
            <br/>
                <input class="round-button blue" type="button" value="Salva" id="flow-form-submit"/>
            </form>

        </fieldset>
    </div>

<#assign availablesFlows={}/>
<#if wf.flows??>
    <#list wf.flows as flow>
        <#assign availablesFlows= availablesFlows + {flow.id,flow.name}/>
    </#list>

</#if>
    <div id="field-dialog" title="Aggiungi Field">
    <fieldset>
        <form id="field-form" method="POST" enctype="multipart/form-data">
        <@hidden "id" "id" />
            <div class="field-component">
        <@hidden "idFlow" "idFlow"/>
            </div>
            <div class="field-component">
        <@textbox "name" "name" "Nome" "" 20/>
            </div>
            <div class="field-component">
        <@selectHash "type" "type" "Tipo" {"TEXTBOX":"textbox","TEXTAREA":"textarea", "DATE":"data"}/>
            </div>
            <div class="field-component">
        <@checkBox "mandatory" "mandatory" "Obbligatorio" {"true":""}/>
            </div>

            <input class="round-button blue" type="button" value="Salva" id="field-form-submit"/>
        </form>

    </fieldset>
        </div>

    <#include "typeForms/workflowAction.ftl"/>

    </fieldset>
</div>

</div>
