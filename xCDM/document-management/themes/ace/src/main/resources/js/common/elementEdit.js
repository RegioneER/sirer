function prepareMetadataForPost(inMetadata) {

    var metadata = $.extend(true, {}, inMetadata);
    $.each(metadata, function(key, value) {
        if($.isPlainObject(value[0])) {
            metadata[key] = value[0].id.toString();
        } else {
            if($.isArray(value)) {
                if(value[0] === null || value[0] === undefined)
                    metadata[key] = "";
                else
                    metadata[key] = value[0].toString();
            } else {
                metadata[key] = value.toString();
            }
        }
    });
    return metadata;

}

function prepareElementForPost(element) {
    element = $.extend(true, {}, element);
    return element;
    $.each(element, function(property, value) {
        if(value === null || value === undefined)
            element[property] = "";
        else if(!$.isPlainObject(value) && !$.isArray(value))
            element[property] = value.toString();
    });
    if(element.metadata)
        element.metadata = prepareMetadataForPost(element.metadata);
    return element;
}

function saveElement(element, parent) {
    if(element.id) {
        if (typeof(emendamentoId) != "undefined" && emendamentoId>0){
            return updateElementEme(element)
        }else
        return updateElement(element);
    } else {
        var metadata = prepareMetadataForPost(element.metadata);
        if(!parent && element.parent){
            if($.isPlainObject(element.parent) || $.isArray(element.parent)){
                parent=element.parent.id;
            }
            else{
                parent=element.parent;
            }
        }
        metadata.parentId = parent;
        var metadataPost = {};
        $.each(metadata, function(key,valueObj){
            if (jQuery.isArray(valueObj) && valueObj.length==0){
                metadataPost[key] = "";
            }else{
                metadataPost[key] = valueObj;
            }
        });
        return $.ajax({
            method : 'POST',
            url : baseUrl+'/app/rest/documents/save/' + element.type.id,
            data : metadataPost
        }).done(function(data) {
            element.id = data.ret;
        });
    }
}

function formToElement(form,element,template){
    if(!((typeof form)=='object') && !$.isArray(form)){
        if(!form.match(/^#/)){
            form='#'+form;
        }
        form=$(form);
    }
    var templateFilter="";
    if(template){
        templateFilter="[name^="+template+"]";
    }
    console.log(templateFilter);
    var multiples={};
    var parsedChkboxes=new Array();
    form.find(':input'+templateFilter).each(function (){
        console.log("sono qui su campo ",$(this));
        var $this=$(this);
        var label=$this.attr('name');
        if(label && label.match(/-select$/)){
            label=label.replace(/-select$/,'');
        }
        if(empties[element.type.id].metadata[label]!=undefined){
            if($('[name='+label+'-select]').size()>0){
                $this=$('#'+label+'-select');
            }
            var type=$this.attr('type');
            console.log(type);
            if(type=='checkbox'){
                if (element.metadata[label]==undefined){
                    element.metadata[label]=new Array();
                }
                if ( jQuery.inArray(label, parsedChkboxes) == -1 ){
                    element.metadata[label]=new Array();
                    parsedChkboxes[parsedChkboxes.length]=label;
                }
                console.log("campo "+$this.attr('id')+" label:"+label);
                if($this.is(':checked')) {
                    console.log('Checcato '+this.value);
                    element.metadata[label][element.metadata[label].length]=this.value;//$this.val(); risulta vuoto indagare come mai viene svuotato
                }else{
                    console.log('Non Checcato '+this.value);
                }
                console.log(element.metadata[label]);
            }
            else if(type=='radio'){
                if(!multiples[label]){
                    multiples[label]=true;
                    element.metadata[label]='';
                }
                if(this.checked){
                    element.metadata[label]=this.value;
                }
            }
            else{
                element.metadata[label]=$this.val();
                if($this.val()=='' && $('[name='+label+']').val()!=''){
                    element.metadata[label]=$('[name='+label+']').val();
                }
            }
        }
        else{
            console.log(label);
            console.log(empties[element.type.id].metadata[label]);
        }
        if($ && $.axmr){
            $.axmr.setUpdated(element);
        }
        console.log("controlla",element);
    });
    return element;
}


function updateElement(element) {
    var metadata = element.metadata;
    if(metadata.lenght==0){
        bootbox.alert('Attenzione, non ci sono dati da salvare.');
        return false;
    }
    //metadata=JSON.stringify(metadata);
    var metadataPost = {};
    $.each(metadata, function(key,valueObj){
        if (jQuery.isArray(valueObj) && valueObj.length==0){
            metadataPost[key] = "";
        }else{
            metadataPost[key] = valueObj;
        }
    });
    return $.ajax({
        method : 'POST',
        url :  baseUrl+'/app/rest/documents/update/' + element.id,
        data : metadataPost
    });

}


function updateElementEme(element) {
    var metadata = element.metadata;
    if(metadata.lenght==0){
        bootbox.alert('Attenzione, non ci sono dati da salvare.');
        return false;
    }
    //metadata=JSON.stringify(metadata);
    var metadataPost = {};
    $.each(metadata, function(key,valueObj){
        if (jQuery.isArray(valueObj) && valueObj.length==0){
            metadataPost[key] = "";
        }else{
            metadataPost[key] = valueObj;
        }
    });
    return $.ajax({
        method : 'POST',
        url :  baseUrl+'/app/rest/documents/updateEme/' + element.id,
        data : metadataPost
    });

}


function elementToForm(element, form) {
    $('#' + form).find(':input').each(function() {
        var $this=$(this);
        var label = $this.attr('name');
        //label=label.replace(/^[^_]*_/,'');
        if($this.attr('type') == 'checkbox') {
            if(getDato(element.metadata[label]))
                this.checked = true;
            else
                this.checked = false;
        } else {
            var dato = getDato(element.metadata[label]);
            if(dato !== undefined && dato !== null)
                $this.val(dato);
            else if(element.metadata.hasOwnProperty(label))
                $this.val('');

            if($('[name='+label+'-select]').size()>0){
                $this=$('#'+label+'-select');
                if(dato !== undefined && dato !== null)
                    $this.val(dato);
                else if(element.metadata.hasOwnProperty(label))
                    $this.val('');
            }
        }
    });
}



function showAuditData(elementId, templateName, fieldName) {
    bootbox.dialog({
        message: '<p class="text-center">Recupero audit trail del campo ...</p>',
        closeButton: false
    });
    $.getJSON(baseUrl + '/app/rest/documents/audit/' + elementId + '/' + templateName + '/' + fieldName, function (data) {
        bootbox.hideAll();
        if (data.length == 0) {
            bootbox.alert("Non sono presenti informazioni storiche sul campo");
        } else {
            var table = $('<table>');
            table.addClass("table table-striped table-bordered table-hover no-margin-bottom no-border-top");
            table.css('font-size', "12px");
            var thead = $('<thead>');
            var trThead = $('<tr>');
            trThead.append('<th>Utente</th>');
            trThead.append('<th>Tipo modifica</th>');
            trThead.append('<th>Data</th>');
            trThead.append('<th>Valore vecchio</th>');
            trThead.append('<th>Valore nuovo</th>');
            thead.append(trThead);
            table.append(thead);
            var tbody = $('<tbody>');
            for (i = 0; i < data.length; i++) {
                console.log(data[i]);
                var trRows = $('<tr>');

                var newDate = new Date();
                newDate.setTime(data[i].auditDate);
                var options = {
                    year: 'numeric',
                    month: '2-digit',
                    day: '2-digit',
                    hour: '2-digit',
                    minute: '2-digit',
                    second: "2-digit"
                };
                var auditDate = newDate.toLocaleDateString('it-IT', options);
                if (data[i].userFullName != undefined || data[i].userFullName != null) {
                    trRows.append('<td>' + data[i].userFullName + '</td>');
                } else {
                    trRows.append('<td>' + data[i].userid + '</td>');
                }
                var action = data[i].actionType;
                if (data[i].actionType == 'create') action = "Primo inserimento";
                if (data[i].actionType == 'update') action = "Modifica";
                if (data[i].actionType == 'delete') action = "Eliminazione";
                trRows.append('<td>' + action + '</td>');
                trRows.append('<td>' + auditDate + '</td>');
                if (data[i].oldValues != null) {
                    var oldVal = "";
                    for (v = 0; v < data[i].oldValues.length; v++) {
                        if (data[i].oldValues.length > 1) {
                            oldVal = "<li>";
                        }
                        if (data[i].dataType == 'DATE') {
                            var valDate = new Date();
                            valDate.setTime(data[i].oldValues[v]);
                            oldVal += valDate.toLocaleDateString('it-IT', options);
                        } else {
                            val = data[i].oldValues[v];
                            var idx = val.indexOf("###");
                            if (idx > 0) {
                                var splits = val.split("###");
                                oldVal += splits[1] + " (id: " + splits[0] + ")";
                            } else {
                                oldVal += data[i].oldValues[v];
                            }
                        }
                        if (data[i].oldValues.length > 1) {
                            oldVal = "</li>";
                        }
                    }
                    trRows.append('<td>' + oldVal + '</td>');
                } else {
                    trRows.append('<td>&nbsp;</td>');
                }


                if (data[i].newValues != null) {
                    var newVal = "";
                    for (v = 0; v < data[i].newValues.length; v++) {
                        if (data[i].newValues.length > 1) {
                            newVal = "<li>";
                        }
                        if (data[i].dataType == 'DATE') {
                            var valDate = new Date();
                            valDate.setTime(data[i].newValues[v]);
                            newVal += valDate.toLocaleDateString('it-IT', options);
                        } else {
                            val = data[i].newValues[v];
                            var idx = val.indexOf("###");
                            if (idx > 0) {
                                var splits = val.split("###");
                                newVal += splits[1] + " (id: " + splits[0] + ")";
                            } else {
                                newVal += data[i].oldValues[v];
                            }
                        }
                        if (data[i].newValues.length > 1) {
                            newVal = "</li>";
                        }
                    }
                    trRows.append('<td>' + newVal + '</td>');
                } else {
                    trRows.append('<td>&nbsp;</td>');
                }

                tbody.append(trRows);
            }
            table.append(tbody);
            bootbox.dialog({
                title: "Storico modifiche campo",
                message: table
            });
        }
    });
    return false;
}