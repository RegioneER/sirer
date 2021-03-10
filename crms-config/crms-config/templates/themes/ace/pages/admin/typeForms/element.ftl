<#assign elementModal>
   <form id="type-form" class="form-horizontal" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
		<div class="form-group">
        	<@textbox "typeId" "typeId" "Nome tipologia" "" 40/>
        </div>
        <button class="round-button btn btn-sm btn-warning" type="button" id="type-form-submit">
        	<i class="fa fa-save"></i> Salva
        </button>
  </form>
</#assign>



<@modalbox "type-dialog" "Aggiungi tipologia" elementModal/>