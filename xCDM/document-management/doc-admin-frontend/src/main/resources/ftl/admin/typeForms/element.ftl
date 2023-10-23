
<div id="type-dialog" title="Aggiungi tipologia">
    <fieldset>
        <form id="type-form" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <@textbox "typeId" "typeId" "Nome tipologia" "" 40/>
        <br/>
        <input class="round-button blue" type="button" value="Salva" id="type-form-submit"/>
        </form>
    </fieldset>
</div>