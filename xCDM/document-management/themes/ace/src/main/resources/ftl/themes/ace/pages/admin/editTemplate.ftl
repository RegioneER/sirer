

<div class="mainContent">
<div class="documentMainContent">
     <div class="page-header">
		<h1>Template ${model['template'].name}</h1>
	</div>
	<div class="tabbable">
		<ul id="myTab4" class="nav nav-tabs padding-12 tab-color-blue background-blue">
			<li class="active">
				<a href="#info" data-toggle="tab">Informazioni</a>
			</li>
			<li>
				<a href="#campi" data-toggle="tab">Campi</a>
			</li>
		</ul>
		<div class="tab-content">
			<div id="info" class="tab-pane in active">
				<form id="template-form" class="form-horizontal" method="POST" action="${baseUrl}/app/rest/admin/template/save" enctype="multipart/form-data">
			        <@hidden "id" "id" model['template'].id/>
			            <div class="form-group">
			            <@textbox "name" "name" "Nome" model['template'].name 40/>
			            </div>
			            <div class="form-group">
			            <@textarea "description" "description" "Descrizione" 40 3 model['template'].description/>
			            </div>
			            <div class="form-group">
			            <#if model['template'].auditable?? && model['template'].auditable>
			                <#assign auditable= ["1"]>
			            </#if>
			            <@checkBox "auditable" "auditable" "Auditable" {"1":""} auditable />
			            </div>
			            <button class="round-button btn btn-sm btn-warning" type="button" id="template-form-submit">
			            	<i class="fa fa-save"></i> Salva
			            </button>
			        </form>
			</div>
			<div id="campi" class="tab-pane">
				<input class="submitButton btn btn-sm btn-info" type="button" value="Aggiungi campo" id="add-field" name="add-field"/>
				<table class="table table-striped table-bordered table-hover">
	                <thead>
		                <tr>
		                    <th>Campo</th>
		                    <th>Sposta</th>
		                    <th>Azioni</th>
		                </tr>
	                </thead>
                	<tbody id="field-list-availables"></tbody>
            	</table>

			</div>
		</div>
	</div>

<#assign fieldModal>
                <form id="field-form" class="form-horizontal" method="POST" action="${baseUrl}/app/rest/admin/type/save" enctype="multipart/form-data">
                <@hidden "id" "id" />
                    <div class="form-group">
                <@textbox "name" "name" "Nome" "" 40/>
                    </div>
                    <div class="form-group">
                <@selectHash "type" "type" "Tipo" {"TEXTBOX":"textbox","TEXTAREA":"textarea","DATE":"data","SELECT":"Select","RADIO":"radio","CHECKBOX":"Check", "ELEMENT_LINK":"collegamento elemento", "EXT_DICTIONARY": "Dizionario Esterno"}/>
                    </div>
                    <div id="multiTypeSelector" class="form-group" style="display: none">
                <@multiAutoCompleteFB "typefilters" "typefilters" "Tipi di elementi collegati" "${baseUrl}/app/rest/admin/type/searchElType" "typeId" null "id"/><br/>
                    </div>
                    <div class="form-group">
                <@checkBox "mandatory" "mandatory" "Obbligatorio" {"true":""}/>
                    </div>
                    <div class="form-group">
                    <@textbox "size" "size" "Lunghezza campo"/>
                    </div>
                    <div class="form-group">
                    <@textbox "macro" "macro" "Macro di editing specifica"/>
                    </div>
                    <div class="form-group">
                    <@textbox "macroView" "macroView" "Macro di visualizzazione specifica"/>
                    </div>
                    <div class="form-group">
                    <@textbox "baseNameOra" "baseNameOra" "Nome colonna oracle"/>
                    </div>
                    <div class="form-group">
                    <@textarea "regexpCheck" "regexpCheck" "Espressione regolare di controllo"/>
                    </div>

                    <pre id='samples'>
                    	<label class='regexp_sample' data-sample-id='digit_regexp'>Digit: </label><span class='regexp_sample' data-sample-id='digit_regexp' id='digit_regexp'>\d</span>
                    	<label class='regexp_sample' data-sample-id='int_regexp'>Numero intero: </label><span class='regexp_sample' data-sample-id='int_regexp' id='int_regexp'>[+-]?\d*</span>
                    	<label class='regexp_sample' data-sample-id='float_regexp'>Numero reale: </label><span class='regexp_sample' data-sample-id='float_regexp' id='float_regexp'>[+-]?\d*[\.,]?\d*</span>
                    	<label class='regexp_sample' data-sample-id='mail_regexp'>Mail: </label><span class='regexp_sample' data-sample-id='mail_regexp' id='mail_regexp'>(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])</span>
                    </pre>
                    <style>
                        span.regexp_sample{
                            overflow: hidden;
                            width: 64% !important;
                            text-overflow: ellipsis;
                            white-space: nowrap;
                            display: inline-block;
                            padding-top: 5px;
                            float: right;
                        }

                    </style>
                    <@script>
                    var samples={};
                    samples['digit']={'label':'Digit','exp':'\\d'};
                    samples['int']={'label':'Intero','exp':'[+-]?\\d*'};
                    samples['float']={'label':'Reale','exp':'[+-]?\\d*[\.,]?\\d*'};
                    samples['mail']={'label':'Mail','exp':'(?:[a-z0-9!#$%&\'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&\'*+/=?^_`{|}~-]+)*|"(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21\\x23-\\x5b\\x5d-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21-\\x5a\\x53-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])+)\\])'};
                    samples['codfisc']={'label':'Codice Fiscale','exp':'^[A-Z]{6}\d{2}[A-Z]\d{2}[A-Z]\d{3}[A-Z]$'};

                    $(document).ready(function(){
                    var containerSample=$('#samples');
                    containerSample.html('Esempi\n');

                    for (var idx in samples){
                    	var lbl=$('<label>');
                    	lbl.html(samples[idx].label+": ");
                    	lbl.addClass('regexp_sample');
                    	lbl.attr('data-sample-id',idx+"_regexp");
                    	containerSample.append(lbl);
                    	var spn=$('<span>');
                    	spn.addClass('regexp_sample');
                    	spn.attr('data-sample-id',idx+"_regexp");
                    	spn.attr('id',idx+"_regexp");
                    	spn.html(samples[idx].exp);
                    	containerSample.append(spn);
                    	containerSample.append('\n');
                    }
                    $('.regexp_sample').css('cursor','pointer');
                    	$('.regexp_sample').click(function(){
                    		var sampleId=$(this).attr('data-sample-id');
                    		console.log(sampleId);
                    		var sampleCode=$('#'+sampleId).html();
                    		$('#regexpCheck').val(sampleCode);
                    	});
                    });

					</@script>
                    <div class="form-group">
                <@textarea "availableValues" "availableValues" "Valori possibili"  />
                <@textbox "externalDictionary" "externalDictionary" "Script esterno"  />
                <@textbox "addFilterFields" "addFilterFields" "Filtri aggiuntivi"  />
            </div>

                    <button class="round-button btn btn-sm btn-warning" type="button" id="field-form-submit">
                    	<i class="fa fa-save"></i> Salva
                    </button>
                </form>

        </#assign>
<@modalbox "field-dialog" "Aggiungi campo" fieldModal/>
</div>
 </div>