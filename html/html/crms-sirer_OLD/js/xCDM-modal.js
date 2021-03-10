function xCDM_Modal(baseUrl, typeId, initFunction, compilationChecks, postSaveCallBack, loadingMessage, savingMessage,readOnly){
    this.baseUrl=baseUrl;
    this.typeId=typeId;

    this.loadingMessage="caricamento form in corso...";
    if (loadingMessage) this.loadingMessage=loadingMessage;
    this.savingMessage="salvataggio in corso ...";
    if (savingMessage) this.loadingMessage=savingMessage;

    if (initFunction!=null) this.initFunction=initFunction;
    if (compilationChecks!=null) this.compilationChecks=compilationChecks;
    if (postSaveCallBack!=null) this.postSaveCallBack=postSaveCallBack;
    this.readOnly=function(){return false};
    if (readOnly!=null) this.readOnly=readOnly;

    this.formBySpec=function(data, parentId, elementId) {

        var object = this;
        //object.readOnly=object.readOnly(object);
        var formEl = $('<form>');
        if (elementId) {
            formEl.attr('elementId', elementId);
        }
        formEl.attr('enctype', 'multipart/form-data');
        formEl.addClass('form-horizontal');
        formEl.attr('id', this.typeId + "-modal-form");
        var fieldParent = $('<input>');
        fieldParent.attr('type', 'hidden');
        fieldParent.attr('name', 'parentId');
        fieldParent.val(parentId);
        formEl.append(fieldParent);
        for (var i = 0; i < data.fieldList.length; i++) {
            var field = data.fieldList[i];
            var fieldEl = $('<div>');
            fieldEl.addClass('form-group');
            fieldEl.attr('data-field-ref', field.templateName + "_" + field.fieldName);
            var lbl = $('<label>');
            lbl.addClass('col-sm-3 control-label no-padding-right');
            lbl.attr('for', field.templateName + "_" + field.fieldName);
            var lblText = field.fieldName;
            if (messages[field.templateName + "." + field.fieldName]) lblText = messages[field.templateName + "." + field.fieldName];
            if (field.mandatory) {
                fieldEl.attr("data-field-mandatory", "true");
                lbl.html(lblText + "<sup style='color:red;'>*</sup>");
            } else {
                fieldEl.attr("data-field-mandatory", "false");
                lbl.html(lblText);
            }
            var fieldLabel = $('<span>');
            fieldLabel.attr('data-field-label', field.templateName + "_" + field.fieldName);
            fieldLabel.hide();
            fieldLabel.html(lblText);
            fieldEl.append(fieldLabel);
            var fieldContainer = $('<div>');
            fieldContainer.addClass('col-sm-9');
            var fieldInput = null;
            if (field.type == 'SELECT') {
                fieldInput = $('<select>');
                fieldInput.attr('name', field.templateName + "_" + field.fieldName);
                if (field.multiple) fieldInput.attr('multiple', true);
                if (field.possibleValues != undefined) {
                    var option = $('<option>');
                    fieldInput.append(option);
                    for (var optionKey in field.possibleValues) {
                        var option = $('<option>');
                        option.attr('value', optionKey + "###" + field.possibleValues[optionKey]);
                        option.html(field.possibleValues[optionKey]);
                        fieldInput.append(option);
                    }
                }
                if (object.readOnly()) {
                    fieldInput.attr('disabled', 'disabled');
                }
            }
            if (field.type == 'TEXTBOX') {
                fieldInput = $('<input>');
                fieldInput.attr('type', 'text');
                fieldInput.attr('name', field.templateName + "_" + field.fieldName);
                if (object.readOnly()) {
                    fieldInput.attr('disabled', 'disabled');
                }
            }
            if (field.type == 'TEXTAREA') {
                fieldInput = $('<textarea>');
                fieldInput.attr('type', 'text');
                fieldInput.attr('name', field.templateName + "_" + field.fieldName);
                if (object.readOnly()) {
                    fieldInput.attr('disabled', 'disabled');
                }
            }
            if (field.type == 'RADIO') {
                fieldInput = $('<span>');
                for (var optionKey in field.possibleValues) {
                    var radioItm = $('<div>');
                    radioItm.addClass('radio');
                    var radioLbl = $('<label>');
                    var radioInput = $('<input>');
                    radioInput.attr('name', field.templateName + "_" + field.fieldName);
                    radioInput.addClass('ace');
                    radioInput.attr('type', 'radio');
                    radioInput.attr('value', optionKey + "###" + field.possibleValues[optionKey]);
                    if (object.readOnly()) {
                        radioInput.attr('disabled', 'disabled');
                    }
                    var radioSpan = $('<span>');
                    radioSpan.addClass('lbl');
                    radioSpan.html(field.possibleValues[optionKey]);
                    radioItm.append(radioLbl);
                    radioLbl.append(radioInput);
                    radioLbl.append(radioSpan);
                    fieldInput.append(radioItm);
                }
            }
            if (field.type == 'DATE') {
                fieldInput = $('<div>');
                fieldInput.attr("class", "input-group input-group-sm input-append date");
                //var fieldInputCalendar=$("<span>");
                //fieldInputCalendar.attr("class","input-group-addon add-on");
                //fieldInputCalendar.html("<i class=\"icon-calendar\"></i>");
                var fieldInputText = $('<input>');
                fieldInputText.attr('type', 'text');
                fieldInputText.attr('data-date-format', 'dd/mm/yyyy hh:mm');
                fieldInputText.attr('name', field.templateName + "_" + field.fieldName).datetimepicker();//({autoclose:true, format:"dd/mm/yyyy"});
                if (object.readOnly()) {
                    fieldInputText.attr('disabled', 'disabled');
                }
                fieldInput.append(fieldInputText);
                //fieldInput.append(fieldInputCalendar);
            }
            if (field.type == 'EXT_DICTIONARY') {
                fieldInput = $('<span>');
                var fieldInputText = $('<input>');
                fieldInputText.attr('type', 'text');
                fieldInputText.attr('data-autocomplete-for', field.templateName + "_" + field.fieldName);
                if (object.readOnly()) {
                    fieldInputText.attr('disabled', 'disabled');
                }
                var fieldInputHidden = $('<input>');
                fieldInputHidden.attr('data-form-id', formEl.attr('id'));
                fieldInputHidden.attr('type', 'hidden');
                fieldInputHidden.attr('name', field.templateName + "_" + field.fieldName);
                fieldInput.append(fieldInputText);
                fieldInput.append(fieldInputHidden);
                (function (fieldInputText, fieldInputHidden, field) {
                    fieldInputText.autocomplete({
                        minLength: 2,
                        select: function (event, ui) {
                            fieldInputHidden.val(ui.item.id);
                        },
                        source: function (request, response) {
                            fieldInputText.next('i.icon-spinner').remove();
                            fieldInputText.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:6px' ></i>");
                            var filters = field.extDicAddFilters.split(",");
                            for (f = 0; f < filters.length; f++) {
                                if (filters[f].indexOf("[") !== -1) {
                                    var my_term = filters[f].split("=[")[0];
                                    var my_value = filters[f].split("=[")[1];
                                    my_value = my_value.split("]")[0];
                                    request[my_term] = $('#' + fieldInputHidden.attr('data-form-id')).find('[name="' + my_value + '"]').val();
                                }
                                else {
                                    var my_term = filters[f].split("=")[0];
                                    var my_value = filters[f].split("=")[1];
                                    request[my_term] = my_value;
                                }
                            }

                            var term = request.term;
                            $.getJSON(field.extDicLink, request, function (data, status, xhr) {
                                var dataFormatted = [];
                                for (var i = 0; i < data.length; i++) {
                                    dataFormatted[i] = {};
                                    dataFormatted[i].id = data[i].id;
                                    dataFormatted[i].label = data[i].title;
                                }
                                response(dataFormatted);
                                fieldInputText.next('i.icon-spinner').remove();
                            });
                        }
                    });
                })(fieldInputText, fieldInputHidden, field);
            }
            if (field.type == 'ELEMENT_LINK') {
                if (field.values && field.values[0]) {
                    fieldInput = $('<span>');
                    var fieldInputText = $('<span>');
                    var fieldInputLink = $('<a>');
                    fieldInputLink.prop("href", baseUrl + "/app/documents/detail/" + field.values[0].id);
                    fieldInputLink.prop("target", "_blank");
                    fieldInputLink.html(field.values[0].value);
                    fieldInputText.append(fieldInputLink);
                    fieldInput.append(fieldInputText);
                }

            }
            fieldContainer.append(fieldInput);
            fieldEl.append(lbl);
            fieldEl.append(fieldContainer);
            formEl.append(fieldEl);
        }
        if (data.hasFile && !this.update) {
            var fieldEl = $('<div>');
            var fieldContainer = $('<div>');
            fieldEl.addClass('form-group');
            fieldEl.attr('data-field-ref', "file");
            var lbl = $('<label>');
            lbl.addClass('col-sm-3 control-label no-padding-right');
            lbl.attr('for', "file");
            lbl.html("Attach file here");
            var fieldInput = $('<input>');
            fieldInput.attr('type', 'file');
            fieldInput.attr('name', "file");
            if (object.readOnly()) {
                fieldInput.attr('disabled', 'disabled');
            }
            fieldContainer.append(fieldInput);
            fieldEl.append(lbl);
            fieldEl.append(fieldContainer);
            formEl.append(fieldEl);
        }
        formEl.find('select').css('max-width', '90%');
        if(!object.readOnly()){
            var buttonsContainer = $('<div>');
            buttonsContainer.addClass('form-group');
            var saveButton = $('<button>');
            saveButton.attr('type', 'submit');

            saveButton.html('Salva');
            saveButton.addClass('btn btn-primary');
            (function (saveButton, formEl, fieldList, object) {
                saveButton.click(function (e) {
                    e.preventDefault();

                    for (var i = 0; i < fieldList.length; i++) {
                        var field = fieldList[i];
                        var fieldName = field.templateName + "_" + field.fieldName;
                        if (object.isMandatory(fieldName) && object.isEmpty(fieldName)) {
                            bootbox.alert('Attenzione campo obbligatorio<br/>' + formEl.find('[data-field-label="' + fieldName + '"]').html());
                            if (formEl.find('[name="' + fieldName + '"]').attr('type') == 'radio' || formEl.find('[name="' + fieldName + '"]').attr('type') == 'checkbox') {
                                $(formEl.find('[name="' + fieldName + '"]')[0]).focus();
                            } else formEl.find('[name="' + fieldName + '"]').focus();
                            return false;
                        }
                    }
                    if (object.compilationChecks) {
                        checksPassed = object.compilationChecks(object);
                        if (!checksPassed) {
                            return false;
                        }
                    }

                    var url = formEl.attr('action');
                    bootbox.dialog({message: object.savingMessage, closeButton: false});
                    $.ajax({
                        type: "POST",
                        url: url,
                        data: new FormData(formEl[0]),
                        processData: false,
                        contentType: false,
                        success: function (data) {

                            if (data.result == 'OK') {
                                object.postSaveCallBack(object, data);
                                bootbox.hideAll();
                            } else {
                                bootbox.hideAll();
                                bootbox.alert('Errore salvataggio');
                            }
                        },
                        error: function () {
                            bootbox.hideAll();
                            bootbox.alert('Errore salvataggio');
                        }
                    });


                    return false;
                });
            })(saveButton, formEl, data.fieldList, this);
            var cancelButton = $('<button>');
            cancelButton.attr('type', 'reset');
            cancelButton.html('Annulla');
            cancelButton.addClass('btn btn-cancel');
            cancelButton.click(function () {
                bootbox.hideAll();
            });

            buttonsContainer.append(cancelButton);
            buttonsContainer.append('&nbsp;');
            buttonsContainer.append(saveButton);
            formEl.append(buttonsContainer);
        }
        formEl.find('select').select2();
        $('#modalForm'+object.typeId).html("");
        var h2=$('<h2>');
        var h2Label='type.create.'+data.typeId;
        h2.html(messages[h2Label]);
        $('#modalForm'+object.typeId).append(h2);
        $('#modalForm'+object.typeId).append(formEl);
    }

    this.formByParentId=function(parentId){
        bootbox.dialog({
            message: '<div class="xCDM-modalForm" id="modalForm'+this.typeId+'" class="text-center"><i class="fa fa-spin fa-spinner"></i> '+this.loadingMessage+'</div>'//,
            //closeButton: false
        });
        var object=this;
        $.getJSON(baseUrl+'/app/rest/documents/'+this.typeId+'/createFormSpec', function(data){
            var container=$('#modalForm'+object.typeId);
            object.formBySpec(data, parentId);
            container.find('form').attr('action',baseUrl+'/app/rest/documents/save/'+object.typeId);
            if (object.initFunction) object.initFunction(object);
            //if (object.compilationChecks) object.compilationChecks(object);
        });
    }

    this.formByElement=function(element){
        bootbox.dialog({
            message: '<div class="xCDM-modalForm" id="modalForm'+this.typeId+'" class="text-center"><i class="fa fa-spin fa-spinner"></i> '+this.loadingMessage+'</div>'//,
            //closeButton: false
        });
        var object=this;
        if (element.id) elementId=element.id;
        else elementId=element;
        $.getJSON(baseUrl+'/app/rest/documents/'+elementId+'/createFormSpecByElementId', function(data){
            var container=$('#modalForm'+object.typeId);
            if (element.id) object.formBySpec(data, element.parentId, element.id);
            else object.formBySpec(data, null , element);
            container.find('form').attr('action',baseUrl+'/app/rest/documents/update/'+elementId);
            if (element.id) {
                object.populateForm(element);
            }
            if (object.initFunction) object.initFunction(object);
            //if (object.compilationChecks) object.compilationChecks(object);
        });
    }



    this.populateForm=function(element){
        for (var f in element.metadata){
            if (element.metadata[f] && element.metadata[f][0]){
                this.setFieldValue(f, element.metadata[f]);
            }
        }
    }

    this.setFieldValue=function(fieldName, value){
        var form=$('#modalForm'+this.typeId+' form');
        var fieldInput=form.find('[name="'+fieldName+'"]');
        if (fieldInput.attr('type')=='radio' || fieldInput.attr('type')=='checkbox'){
            for (var i=0;i<fieldInput.length;i++){
                var singleField=$(fieldInput[i]);
                for (var c=0;c<value.length;c++){
                    if (value[c]==singleField.val()) singleField.prop('checked', true);
                }
            }
        }else {
            if(fieldInput.parent().hasClass('date')){
                value[0]=formatDate(value[0]);
            }
            fieldInput.val(value[0]);
            if (fieldInput.prop("tagName")=='SELECT'){
                fieldInput.select2();
            }
            if (form.find('[data-autocomplete-for="'+fieldName+'"]').length>0){
                form.find('[data-autocomplete-for="'+fieldName+'"]').val(value[0].split("###")[1]);
            }
        }

    }



    this.clearField=function(fieldName){
        var form=$('#modalForm'+this.typeId+' form');
        if (form.find('[name="'+fieldName+'"]').attr('type')!='radio' && form.find('[name="'+fieldName+'"]').attr('type')!='checkbox') {
            form.find('[name="'+fieldName+'"]').val("").trigger('change');
        }else {
            for (var i=0;i<form.find('[name="'+fieldName+'"]').length;i++){
                form.find('[name="'+fieldName+'"]').prop('checked',false);
                $(form.find('[name="'+fieldName+'"]')[0]).prop('checked',false);
            }
        }
    }



    this.isMandatory=function(fieldName){
        var form=$('#modalForm'+this.typeId+' form');
        if (form.find('[data-field-ref="'+fieldName+'"][data-field-mandatory="true"]').length>0 && form.find('[data-field-ref="'+fieldName+'"]').is(':visible')){
            return true;
        }else return false;
    }


    this.isEmpty=function(fieldName){
        var form=$('#modalForm'+this.typeId+' form');
        var fieldInput=form.find('[name="'+fieldName+'"]');
        if (fieldInput.attr('type')!='radio' && fieldInput.attr('type')!='checkbox'){
            if (fieldInput.val()!="") return false;
            else return true;
        }else {
            if (form.find('[name="'+fieldName+'"]:checked').length>0) return false;
            else return true;
        }
    }

    this.getForm=function(){
        return $('#modalForm'+this.typeId+' form');
    }

}







