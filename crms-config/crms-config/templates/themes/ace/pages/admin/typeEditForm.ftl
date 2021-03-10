
<#if model['elType'].selfRecursive>
			        <#assign selfRecursive = ["1"]>
			    </#if>
			    <#if model['elType'].container>
			        <#assign container = ["1"]>
			    </#if>
			    <#if model['elType'].rootAble>
			        <#assign rootAble= ["1"]>
			    </#if>
			    <#assign sortable= ["0"]>
			    <#if model['elType'].sortable>
			        <#assign sortable= ["1"]>
			    </#if>
			    <#if model['elType'].hasFileAttached>
			        <#assign hasFileAttached= ["1"]>
			    </#if>
			    <#if model['elType'].checkOutEnabled>
			        <#assign checkOutEnabled= ["1"]>
			    </#if>
			    <#if model['elType'].searchable>
			        <#assign searchable= ["1"]>
			    </#if>
			    <#if model['elType'].noFileinfo>
			        <#assign noFileinfo= ["1"]>
			    </#if>
<div class="admin-home-main">
    <div class="page-header">
    	<h1><#if model['elType'].imageBase64!=""><img height="40px" src="${model['elType'].imageBase64!}"/></#if>Elemento ${model['elType'].typeId}</h1>
	</div>
	 <div class="tabbable">
		<ul id="myTab4" class="nav nav-tabs padding-12 tab-color-blue background-blue">
			<li class="active">
				<a href="#conf" data-toggle="tab"><i class="icon-info bigger-110"></i> Configurazione base</a>
			</li>
			<li>
				<a href="#figli" id="isContainerLi" data-toggle="tab"><i class="fa fa-indent bigger-110"></i> Figli</a>
			</li>
			<li>
				<a href="#metadata" data-toggle="tab"><i class="fa fa-list bigger-110"></i> Metadati</a>
			</li>
			<li>
				<a href="#workflow" data-toggle="tab"><i class="fa fa-code-fork bigger-110"></i> Workflow</a>
			</li>
			<li>
				<a href="#permission" data-toggle="tab"><i class="fa fa-lock bigger-110"></i> Permessi</a>
			</li>
		</ul>
		<div class="tab-content">
			<div id="conf" class="tab-pane in active">
				<form id="type-form" class="form-horizontal" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
			    	<@hidden "id" "id" model['elType'].id/>
			    	<div class="form-group">
			        <@fileChooser "img" "img" "Cambia icona"/>
				    </div>
				    <div class="form-group">
			        <@textbox "typeId" "typeId" "Nome tipologia" model['elType'].typeId 40/>
				    </div>
				    <div class="form-group">
			        <@checkBox "selfRecursive" "selfRecursive" "Pu&ograve; contenere elementi dello stesso tipo" {"1":""} selfRecursive />
			    	</div>
			        <div class="form-group">
			        <@checkBox "container" "container" "Pu&ograve; contenere altri elementi" {"1":""} container/>
			        </div>
			        <div class="form-group">
			        <@checkBox "hasFile" "hasFile" "Prevede file allegato" {"1":""} hasFileAttached/>
			        </div>
			        <div class="form-group">
			        <@checkBox "noFileinfo" "noFileinfo" "File senza informazioni aggiuntive" {"1":""} noFileinfo/>
			        </div>
			        <div class="form-group">
			        <@checkBox "rootAble" "rootAble" "Livello root" {"1":""} rootAble/>
			        </div>
			        <div class="form-group">
			        <@checkBox "checkOutEnabled" "checkOutEnabled" "Abilita modifica con ChekOut e CheckIn" {"1":""} checkOutEnabled/>
			        </div>
			        <div class="form-group">
			        <@checkBox "sortable" "sortable" "Ordinabile" {"1":""} sortable/>
			        </div>
			        <div class="form-group">
			        <@checkBox "searchable" "searchable" "Elemento ricercabile" {"1":""} searchable/>
			        </div>
			        <div class="form-group">
			        <@selectHash "titleField" "titleField" "Campo da utilizzare come titolo"/>
			        </div>
			        <div class="form-group">
			        <@textbox "ftlRowTemplate" "ftlRowTemplate" "Template griglia" model['elType'].ftlRowTemplate 40/>
			        </div>
			        <div class="form-group">
			        <@textbox "ftlDetailTemplate" "ftlDetailTemplate" "Template dettaglio" model['elType'].ftlDetailTemplate 40/>
			        </div>
			        <div class="form-group">
			        <@textbox "ftlFormTemplate" "ftlFormTemplate" "Template form" model['elType'].ftlFormTemplate 40/>
			        </div>
			        <div class="form-group">
			        <@textbox "titleRegex" "titleRegex" "Espressione titolo" model['elType'].titleRegex 40/>
			        </div>
			        <div class="form-group">
			        <@textbox "hashBack" "hashBack" "Hash di navigazione" model['elType'].hashBack 40/>
			        </div>
			        <div class="form-group">
			        <@textbox "groupUpLevel" "groupUpLevel" "Raggruppa a livello superiore" model['elType'].groupUpLevel 40/>
			        </div>
			        <button class="round-button btn btn-warning" type="button" id="editType-form-submit">
				    	<i class="fa fa-save"></i> Salva
				    </button>
			    </form>	
			</div>
		
			<div id="figli" class="tab-pane">
				<div id="isContainer">
				<input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi figlio" id="add-child" name="add-child"/>
            	<table class="table table-striped table-bordered table-hover">
	                <thead>
		                <tr>
		                    <th>Tipo</th>
		                    <th>Elimina</th>
		                </tr>
	                </thead>
                	<tbody id="child-list-availables"></tbody>
            	</table>
            	</div>
			</div>
			<div id="metadata" class="tab-pane">
				<input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi template" id="add-assoctemplate" name="add-assoctemplate"/>
            	<table class="table table-striped table-bordered table-hover">
	                <thead>
		                <tr>
		                    <th>Template</th>
		                    <th>Attivo</th>
		                    <th>Elimina</th>
		                    <th>Permessi</th>
		                </tr>
	                </thead>
                	<tbody id="assoctemplate-list-availables"></tbody>
            	</table>
            	
			</div>
			<div id="workflow" class="tab-pane">
				<input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi Workflow" id="add-assocWorkflow" name="add-assocWorkflow"/>
	            <table class="table table-striped table-bordered table-hover">
	                <thead>
		                <tr>
		                    <th>Workflow</th>
		                    <th>Attivo</th>
		                    <th>Automatico alla creazione</th>
		                    <th>Automatico alla modifica</th>
		                    <th>Automatico all'eliminazione</th>
		                    <th>Elimina associazione</th>
		                </tr>
	                </thead>
                	<tbody id="assocWorkflow-list-availables"></tbody>
            	</table>
            </div>
            <div id="permission" class="tab-pane">
				<input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi permessi" id="add-permission" name="add-permission"/>
	            <table class="table table-striped table-bordered table-hover">
	                <thead>
	                <tr>
	                    <th>Policy</th>
	                <#include "helpers/permission-tb-header.ftl"/>
	                    <th>Gruppi/utenti</th>
	                    <th>Template</th>
	                    <th>Action</th>
	                </tr>
	                </thead>
	                <tbody id="permission-list-availables"></tbody>
	
	            </table>
            </div>
		</div>
	</div>
		
	

    </div>


    <#assign availablesType={}/>
    <#if model['elTypes']??>
        <#list model['elTypes'] as type>
        <#if type.id != model['elType'].id>
            <#assign availablesType= availablesType + {type.id,type.typeId}/>
        </#if>
        </#list>

    </#if>

    <#assign availablesTemplates={}/>
    <#if model['templates']??>
        <#list model['templates'] as type>
                <#assign availablesTemplates= availablesTemplates + {type.id,type.name}/>
            
        </#list>
    </#if>

    <#assign availablesPolicies={"0","ad-hoc"}/>
    <#if model['policies']??>
        <#list model['policies'] as type>
            <#assign availablesPolicies= availablesPolicies + {type.id,type.name}/>
        </#list>

    </#if>

    <#assign childModal>
            <form id="child-form" class="form-horizontal" method="POST" enctype="multipart/form-data">
            	<div class="form-group">
            		<@selectHash "elementId" "elementId" "Documento figlio" availablesType/>
                </div>
                <button class="round-button btn btn-sm btn-warning" type="button" id="child-form-submit">
                <i class="fa fa-save"></i> Salva
                </button>
            </form>
	</#assign>    
    
<@modalbox "child-dialog" "Aggiungi figlio" childModal/>

<#assign tplModal>    
        <form class="form-horizontal" id="assoctemplate-form" method="POST" enctype="multipart/form-data">
            <div class="form-group">
            <@selectHash "templateId" "templateId" "Template" availablesTemplates/>
            </div>
            <div class="form-group">
            <@checkBox "enabled" "enabled" "Attivo" {"1":""} /><br/>
            </div>
            <button class="round-button btn btn-sm btn-warning" type="button" id="assoctemplate-form-submit">
                <i class="fa fa-save"></i> Salva
                </button>
            </form>
</#assign>


<@modalbox "assoctemplate-dialog" "Aggiungi template" tplModal/>



        
<#assign wfModal>
        <form class="form-horizontal" id="assocWorkflow-form" method="POST" enctype="multipart/form-data">
	                <div class="form-group">
	                	<@selectHash "wfId" "wfId" "Processo"/>
	                </div>
	            	<div class="form-group">
	            		<@checkBox "enabled" "enabled" "Attivo" {"1":""} /><br/>
	                </div>
	            	<div class="form-group">
	                	<@checkBox "startOnCreate" "startOnCreate" "Avviato alla creazione" {"1":""} /><br/>
	            	</div>    
	                <div class="form-group">
	                	<@checkBox "startOnUpdate" "startOnUpdate" "Avviato alla modifica" {"1":""} /><br/>
	            	</div>    
	                <div class="form-group">
	                	<@checkBox "startOnDelete" "startOnDelete" "Avviato all'eliminazione" {"1":""} /><br/>
	            	</div>    
	                <button class="round-button btn btn-sm btn-warning" type="button" id="assocWorkflow-form-submit">
	                	<i class="fa fa-save"></i> Salva
	                </button>
                </form>
</#assign>
<@modalbox "assocWorkflow-dialog" "Aggiungi Workflow" wfModal/>


<#assign permModal>
                <form class="form-horizontal" id="permission-form" method="POST" enctype="multipart/form-data">
                <div class="form-group">
                <@checkBox "allUsers" "allUsers" "Tutti gli utenti" {"1":""} />
                </div>
        	<div class="form-group">
                <@checkBox "cuser" "cuser" "Owner" {"1":""} />
                </div>
        		<div class="form-group">
                	<@multiAutoCompleteFB "groups" "groups" "Gruppi" "${baseUrl}/uService/rest/user/searchAuth" "authority"/>
                </div>
        		<div class="form-group">
                	<@multiAutoCompleteFB "users" "users" "Utenti" "${baseUrl}/uService/rest/user/searchUser" "username"/>
                <div class="form-group">
        		<@textbox "templateRef" "templateRef" "Dynamic Team" "" />
                </div>
                <@hidden "id" "id"/>
                </div>
        		<div class="form-group">
                	<@selectHash "policy" "policy" "Policy" availablesPolicies/>
                </div>
                <div id="permission-table">
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
                </div>
                <div class="form-group">
                <@textbox "detailTemplate" "detailTemplate" "Template ad-hoc" "" />
                </div>
                </div>
                    <button class="round-button btn btn-sm btn-warning" type="button" id="permission-form-submit">
	                	<i class="fa fa-save"></i> Salva
	                </button>
                </form>
</#assign>
        
<@modalbox "permission-dialog" "Aggiungi/modifica permessi" permModal/>
        
<#assign templateAclModal> 
           <fieldset>
                <form id="templateAcl-form" method="POST" enctype="multipart/form-data">
                <div class="form-group">
                <@checkBox "allUsers" "allUsers" "Tutti gli utenti" {"1":""} />
                </div>
        	<div class="form-group">
                <@checkBox "cuser" "cuser" "Owner" {"1":""} />
                </div>
        		<div class="form-group">
                <@multiAutoCompleteFB "groups" "groups" "Gruppi" "${baseUrl}/uService/rest/user/searchAuth" "authority"/>
                </div>
        		<div class="form-group">
                <@multiAutoCompleteFB "users" "users" "Utenti" "${baseUrl}/uService/rest/user/searchUser" "username"/>
                </div>
        		<div class="form-group">
                <div id="permission-table">
                <table class="pSchema" >
                    <thead>
                    <tr>
                        <th style="display: none"></th>
                    <#include "helpers/aclPermission-tb-header.ftl"/>
                        <th style="display: none"></th>
                    </tr>
                    </thead>
                    <tbody>
                    <tr>
                        <td style="display: none"></td>
                        <td><@checkBox "view" "view" "" {"1":""} /></td>
                        <td><@checkBox "create" "create" "" {"1":""} /></td>
                        <td><@checkBox "update" "update" "" {"1":""} /></td>
                        <td><@checkBox "delete" "delete" "" {"1":""} /></td>
                        <td style="display: none"></td>
                    </tr>
                    </tbody>
                </table>
                </div>
                </div>
                    <input class="round-button blue" type="button" value="Salva" id="templateAcl-form-submit"/>
                </form>

            </fieldset>
      </#assign>       
<@modalbox "templateAcl-dialog" "Aggiungi/modifica permessi" templateAclModal/>
      


</fieldset>

    </div>
