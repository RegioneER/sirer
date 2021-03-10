<#assign policyModal>
   <form id="policy-form" class="form-horizontal method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
        <@hidden "id" "id" ""/>
        <div class="form-group">
        	<@textbox "name" "name" "Nome" "" 40/>
        </div>
		<div class="form-group">
        	<@textbox "description" "description" "Descrizione" "" 40/>
        </div>
        <div class="form-group">
	    	<@checkBox "view" "view" "Visualizzazione" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "create" "create" "Creazione" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "update" "update" "Aggiornamento" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "addComment" "addComment" "Aggiunta commento" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "moderate" "moderate" "Moderazione commenti" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "delete" "delete" "Eliminazione" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "changePermission" "changePermission" "Cambio permessi" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "addChild" "addChild" "Aggiunta figli" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "removeCheckOut" "removeCheckOut" "Rimozione check.out" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "launchProcess" "launchProcess" "Avvio Processo" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "enableTemplate" "enableTemplate" "Abilitazione template" {"1":""} />
		</div>
		<div class="form-group">
	    	<@checkBox "canBrowse" "canBrowse" "Navigazione" {"1":""} />
	    </div>
            <button class="round-button btn btn-sm btn-warning" type="button" id="policy-form-submit">
            	<i class="fa fa-save"></i> Salva
            </button>
  </form>
</#assign>

<@modalbox "policy-dialog" "Aggiungi policy" policyModal/>
