<style>

    .dd {
        max-width:100% !important;
    }

    .select2-container{
        min-width:200px;
    }

    .buttonEl .row .col-sm-3{
        text-align:right;
    }

</style>
<div class="admin-home-main">
    <h1>Interfaccia disegno controlli [${id}]</h1>
    <button class='btn btn-success save-all'><i class='fa fa-floppy-o'></i> Salva controlli</button>


    <div class="row">
        <div class="col-sm-12">
            <div class="widget-box" data-id='conditionEditor' style='display:none;'>
                <div class="widget-header">
                    <h5>Editor condizioni</h5>
                    <div class="widget-toolbar">
                        <button type='button' class='btn btn-info btn-xs conditionEditor'>Salva</button>
                        <button type='button' class='btn btn-cancel btn-xs condtionEditorClose'>Annulla</button>
                    </div>
                </div>
                <div class="widget-body">
                    <div class="widget-main" id='condition-widget-main'>
                    </div>
                </div>
            </div>
        </div>

        <div class="col-sm-7">
            <h3>Controlli</h3>
            <button class='btn btn-sm btn-info' id='addRule'><i class='ace-icon fa fa-plus'></i> Aggiungi regola</button>
            <div class="dd dd-draghandle">
                <ol class="dd-list" id="rules"></ol>
            </div>

        </div>
        <div class='col-sm-5'>
            <h3>Pulsanti</h3>
            <button class='btn btn-sm btn-info' id='addButton'><i class='ace-icon fa fa-plus'></i> Aggiungi pulsante</button>
            <div id='buttonsList'>

            </div>
        </div>

    </div>

    <div style='display:none;' id='prototypes'>

        <div id='button-prototype' class='buttonEl alert alert-info'>

            <button class='btn btn-xs btn-warning delete-button'><i class='fa fa-trash'></i> Elimina bottone</button>
            <div class="row spanChangeLink">
                <div class="col-sm-3">
                    <strong>name</strong>
                </div>
                <div class='col-sm-9'>
                    <span data-ref='name'></span>
                </div>
            </div>
            <div class="row spanChangeLink">
                <div class="col-sm-3">
                    <strong>icon</strong>
                    <a href='#'><i class='fa fa-pencil'></i>&nbsp;</a>:
                </div>
                <div class='col-sm-9'>
                    <span data-ref='faIcon'></span>
                </div>
            </div>
            <div class="row">
                <div class="col-sm-3">
                    <strong>campi</strong>:
                </div>
                <div class='col-sm-9'>
                    <select name='fields' data-type='field-select' data-id='rightHandFields' multiple></select>
                </div>
            </div>
            <div class="row spanChangeLink">
                <div class="col-sm-3">
                    <strong>label</strong>
                    <a href='#'><i class='fa fa-pencil'></i>&nbsp;</a>:
                </div>
                <div class='col-sm-9'>
                    <span data-ref='label'></span>
                </div>
            </div>
            <div class="row">
                <div class="col-sm-3">
                    <strong>tipo form</strong>:
                </div>
                <div class='col-sm-9'>
                    <select name='forms' data-type='field-select' multiple><option value='create'>creazione</option><option value='detail'>dettaglio</option></select>
                </div>
            </div>
            <div class="row colorpickerEl">
                <div class="col-sm-3">
                    <strong>txtRGB</strong>
                    <a href='#'><i class='fa fa-pencil'></i>&nbsp;</a>:
                </div>
                <div class='col-sm-9'>
                    R:<input type='text' name='txtRGB_R' size="2">-
                    G:<input type='text' name='txtRGB_G' size="2">-
                    B:<input type='text' name='txtRGB_B' size="2">
                    <input name="txtRGB" class="input-small colorpicker-element" type="text" size="1">
                </div>
            </div>
            <div class="row colorpickerEl">
                <div class="col-sm-3">
                    <strong>bkgRGB</strong>
                    <a href='#'><i class='fa fa-pencil'></i>&nbsp;</a>:
                </div>
                <div class='col-sm-9'>
                    R:<input type='text' name='bkgRGB_R' size="2">-
                    G:<input type='text' name='bkgRGB_G' size="2">-
                    B:<input type='text' name='bkgRGB_B' size="2">
                    <input name="bkgRGB" class="input-small colorpicker-element" type="text" size="1">
                </div>
            </div>
            <button class='btn btn-sx proto'></button>
        </div>

        <div class='form-block'>
            <form class="form-horizontal" role="form" onsubmit="return false;">
                <div class="row form-group">
                    <div class='col-sm-12'>
                        <select name='leftHandField' data-type='field-select' data-id='leftHandField'>
                        </select>
                        <select data-type='check' name='check'>
                            <option>Seleziona l'operatore</option>
                            <option value="gt">&gt;</option>
                            <option value="ge">&ge;</option>
                            <option value="eq">=</option>
                            <option value="lt">&lt;</option>
                            <option value="le">&le;</option>
                            <option value="ne">&ne;</option>
                            <option value="isNumeric">&egrave; numerico</option>
                            <option value="isFloat">&egrave; Float</option>
                            <option value="isInt">&egrave; Intero</option>
                            <option value="isString">&egrave; Stringa</option>
                        </select>
                        <span data-hand="right">
					<select name='rightHandFields' data-type='field-select' data-id='rightHandFields' multiple>
					</select>
					<br/>
					Lista valori di controllo (separati da "|"):
					<input name='rightHandValues' type="text" size="40" data-id='rightHandValues'>
					</span>
                    </div>
                </div>
            </form>
            <a href='#' class='addAndCondition'>Aggiungi condizione in "and"</a>
        </div>

        <li class="dd-item dd2-item" data-type='rule'>
            <div class="dd-handle dd2-handle">
                <i class="normal-icon fa fa-bars blue bigger-130"></i>
                <i class="drag-icon icon-move bigger-125"></i>
            </div>
            <div class="dd2-content">
                <a href="#" onclick="contentEl=$(this).parent().find('.rule_content'); if (contentEl.is(':visible')) contentEl.hide(); else contentEl.show();return false" style="float:right">
                    mostra/nascondi dettagli
                </a>
                <h5></h5>
                <button class='btn btn-xs btn-warning delete-rule'><i class='fa fa-trash'></i> Elimina regola</button>
                <div class="row rule_content" style="display:">
                    <div class="col-sm-12">
                        <label>
                            <span class="lbl"> empty</span>
                        </label>
                        &nbsp;<a href='#' class='addCondition' data-type='empty'><i class='normal-icon fa fa-plus'></i> aggiungi condizione</a>
                        &nbsp;<a class='emptyAndHide'><i class='fa'></i> Nascondi</a>
                        <ul data-id='conditions' data-type='empty'></ul>
                        <label>
                            <span class="lbl"> disable</span>
                        </label>
                        &nbsp;<a href='#' class='addCondition' data-type='disable'><i class='normal-icon fa fa-plus'></i> aggiungi condizione</a>
                        <ul data-id='conditions' data-type='disable'></ul>
                        <label>
                            <span class="lbl"> mandatory</span>
                        </label>
                        &nbsp;<a href='#' class='addCondition' data-type='mandatory'><i class='normal-icon fa fa-plus'></i> aggiungi condizione</a>
                        <ul data-id='conditions' data-type='mandatory'></ul>
                        <label>
                            <span class="lbl"> confirm</span>
                        </label>
                        &nbsp;<a href='#' class='addCondition' data-type='confirm'><i class='normal-icon fa fa-plus'></i> aggiungi condizione</a>
                        <ul data-id='conditions' data-type='confirm'></ul>
                        <label>
                            <span class="lbl"> warning</span>
                        </label>
                        &nbsp;<a href='#' class='addCondition' data-type='warning'><i class='normal-icon fa fa-plus'></i> aggiungi condizione</a>
                        <ul data-id='conditions' data-type='warning'></ul>
                        <label>
                            <span class="lbl"> validity</span>
                        </label>
                        &nbsp;<a href='#' class='addCondition' data-type='valid'><i class='normal-icon fa fa-plus'></i> aggiungi condizione</a>
                        <ul data-id='conditions' data-type='validity'></ul>
                        <label>
                            Campi:
                        </label>
                        <select name='fields' multiple size="6" style='width:100%;'>
                        </select>
                        <label>
                            Pulsanti:
                        </label>
                        <select name='buttons' multiple size="6" style='width:100%;'>
                        </select>
                    </div>
                </div>
            </div>
        </li>
    </div>

</div>

