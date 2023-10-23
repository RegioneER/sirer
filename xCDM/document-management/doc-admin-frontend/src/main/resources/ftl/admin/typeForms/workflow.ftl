
<div id="workflow-dialog" title="Aggiungi processo">
    <fieldset>
        <form id="workflow-form" method="POST" action="${baseUrl}/app/rest/admin/workflow/save" enctype="multipart/form-data">
        <div class="field-component">
        <@textbox "name" "name" "Nome flusso" "" 40/>
        </div>
        <input class="round-button blue" type="button" value="Salva" id="workflow-form-submit"/>
        </form>
    </fieldset>
</div>