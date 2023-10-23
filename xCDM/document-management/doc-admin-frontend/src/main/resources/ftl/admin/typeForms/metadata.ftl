
<div id="template-dialog" title="Aggiungi template">
    <fieldset>
        <form id="template-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <@textbox "name" "name" "Nome" "" 40/>
        <br/>
            <input class="round-button blue" type="button" value="Salva" id="template-form-submit"/>
        </form>
    </fieldset>
</div>