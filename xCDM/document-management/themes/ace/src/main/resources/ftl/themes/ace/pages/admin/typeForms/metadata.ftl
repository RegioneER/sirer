<#assign templateModal>
        <form id="template-form" class="form-horizontal" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
	        <div class="form-group">
	        	<@textbox "name" "name" "Nome" "" 40/>
	        </div>
            <button class="round-button btn btn-sm btn-warning" type="button" id="template-form-submit">
            	<i class="fa fa-save"></i> Salva
            </button>
        </form>
</#assign>

<@modalbox "template-dialog" "Aggiungi template" templateModal/>